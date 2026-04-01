/*!
    \file    drv_sd_h7.c
    \brief   SD card block device driver for GD32H7xx (RT-Thread adaptation)

             Low-level SDIO operations are ported from the official GD32H7xx
             SD_readwrite firmware library (sdcard.c) with minimal style changes.
             RT-Thread device callbacks wrap those operations.

    Design notes:
      - Uses SDIO0 (aliased as SDIO) with IDMA, polling on SDIO status flags.
      - Supports SDSC (v1.x/v2.0) and SDHC/SDXC cards.
      - DCache is managed explicitly (Cortex-M7):
          Write path: SCB_CleanDCache before IDMA
          Read  path: SCB_InvalidateDCache after IDMA
      - SDHC/SDXC: sector addressing (CMD17/18/24/25 arg = sector number).
        SDSC: byte addressing (arg = sector * 512).
      - Registers "sd0" as RT_Device_Class_Block device.
      - SDIO0 is shared with the eMMC driver (drv_emmc_h7.c).
        Only one of BSP_USING_SD / BSP_USING_EMMC should be active (Kconfig enforces this).
*/

/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>

#ifdef BSP_USING_SD

#include "drv_sd_h7.h"

/* #define DRV_DEBUG */
#define LOG_TAG  "drv.sd"
#include "drv_log.h"

/* SDIO peripheral alias — matches official GD32 SD driver (sdcard.c) style */
#define SDIO  SDIO0

/* card status of R1 definitions */
#define SD_R1_OUT_OF_RANGE              BIT(31)
#define SD_R1_ADDRESS_ERROR             BIT(30)
#define SD_R1_BLOCK_LEN_ERROR           BIT(29)
#define SD_R1_ERASE_SEQ_ERROR           BIT(28)
#define SD_R1_ERASE_PARAM               BIT(27)
#define SD_R1_WP_VIOLATION              BIT(26)
#define SD_R1_CARD_IS_LOCKED            BIT(25)
#define SD_R1_LOCK_UNLOCK_FAILED        BIT(24)
#define SD_R1_COM_CRC_ERROR             BIT(23)
#define SD_R1_ILLEGAL_COMMAND           BIT(22)
#define SD_R1_CARD_ECC_FAILED           BIT(21)
#define SD_R1_CC_ERROR                  BIT(20)
#define SD_R1_GENERAL_UNKNOWN_ERROR     BIT(19)
#define SD_R1_CSD_OVERWRITE             BIT(16)
#define SD_R1_WP_ERASE_SKIP             BIT(15)
#define SD_R1_CARD_ECC_DISABLED         BIT(14)
#define SD_R1_ERASE_RESET               BIT(13)
#define SD_R1_READY_FOR_DATA            BIT(8)
#define SD_R1_AKE_SEQ_ERROR             BIT(3)
#define SD_R1_ERROR_BITS                ((uint32_t)0xFDF9E008U)

/* card state */
#define SD_CARDSTATE_IDLE               ((uint8_t)0x00)
#define SD_CARDSTATE_READY              ((uint8_t)0x01)
#define SD_CARDSTATE_IDENTIFICATION     ((uint8_t)0x02)
#define SD_CARDSTATE_STANDBY            ((uint8_t)0x03)
#define SD_CARDSTATE_TRANSFER           ((uint8_t)0x04)
#define SD_CARDSTATE_DATA               ((uint8_t)0x05)
#define SD_CARDSTATE_RECEIVING          ((uint8_t)0x06)
#define SD_CARDSTATE_PROGRAMMING        ((uint8_t)0x07)
#define SD_CARDSTATE_DISCONNECT         ((uint8_t)0x08)

/* SD command indices */
#define SD_CMD_GO_IDLE_STATE            ((uint8_t)0)
#define SD_CMD_ALL_SEND_CID             ((uint8_t)2)
#define SD_CMD_SEND_RELATIVE_ADDR       ((uint8_t)3)
#define SD_CMD_SELECT_DESELECT_CARD     ((uint8_t)7)
#define SD_CMD_SEND_IF_COND             ((uint8_t)8)   /* CMD8: voltage check (SD v2.0+) */
#define SD_CMD_SEND_CSD                 ((uint8_t)9)
#define SD_CMD_STOP_TRANSMISSION        ((uint8_t)12)
#define SD_CMD_SEND_STATUS              ((uint8_t)13)
#define SD_CMD_READ_SINGLE_BLOCK        ((uint8_t)17)
#define SD_CMD_READ_MULTIPLE_BLOCK      ((uint8_t)18)
#define SD_CMD_WRITE_BLOCK              ((uint8_t)24)
#define SD_CMD_WRITE_MULTIPLE_BLOCK     ((uint8_t)25)
#define SD_CMD_APP_CMD                  ((uint8_t)55)  /* CMD55: prefix for ACMDs */
#define SD_ACMD_SET_BUS_WIDTH           ((uint8_t)6)   /* ACMD6: set 1/4-bit bus width */
#define SD_ACMD_SD_SEND_OP_COND         ((uint8_t)41)  /* ACMD41: send operating condition */

/* OCR bit definitions */
#define SD_OCR_CCS                      BIT(30)        /* Card Capacity Status: 1=SDHC/SDXC */
#define SD_OCR_BUSY                     BIT(31)        /* power-up status: 1=ready */
#define SD_VOLTAGEWINDOW                ((uint32_t)0x00100000U) /* 3.2~3.4V window */

/* Card capacity type */
#define SD_HIGH_CAPACITY                ((uint8_t)1)   /* SDHC or SDXC */
#define SD_STD_CAPACITY                 ((uint8_t)0)   /* SDSC */

#define SD_DATATIMEOUT                  ((uint32_t)0xFFFFFFFFU)
#define SD_ALLZERO                      ((uint32_t)0x00000000U)
#define SD_RCA_SHIFT                    ((uint8_t)0x10U)
#define SD_SECTOR_SIZE                  ((uint32_t)512U)

#define SDIO_MASK_INTC_FLAGS            ((uint32_t)0x1FE00FFFU)
#define SDIO_MASK_CMD_FLAGS             ((uint32_t)0x002000C5U)
#define SDIO_MASK_DATA_FLAGS            ((uint32_t)0x18000F3AU)

#define SD_FIFOHALF_WORDS               ((uint32_t)0x00000008U)
#define SD_FIFOHALF_BYTES               ((uint32_t)0x00000020U)

/* SD card locked state bit in card status register */
#define SD_CARDSTATE_LOCKED             ((uint32_t)0x02000000U)

/* byte-lane masks for CID/CSD byte extraction */
#define SD_MASK_0_7BITS                 ((uint32_t)0x000000FFU)
#define SD_MASK_8_15BITS                ((uint32_t)0x0000FF00U)
#define SD_MASK_16_23BITS               ((uint32_t)0x00FF0000U)
#define SD_MASK_24_31BITS               ((uint32_t)0xFF000000U)

/* SCR bus-width support bits */
#define SD_BUS_WIDTH_4BIT               ((uint32_t)0x00040000U)
#define SD_BUS_WIDTH_1BIT               ((uint32_t)0x00010000U)

/* additional SD command indices */
#define SD_CMD_SET_BLOCKLEN             ((uint8_t)16)
#define SD_CMD_ERASE_WR_BLK_START       ((uint8_t)32)
#define SD_CMD_ERASE_WR_BLK_END         ((uint8_t)33)
#define SD_CMD_ERASE                    ((uint8_t)38)
#define SD_APPCMD_SET_WR_BLK_ERASE_COUNT ((uint8_t)23)  /* ACMD23: pre-erase blocks before multi-block write */
#define SD_APPCMD_SEND_SCR              ((uint8_t)51)
/* SD_ACMD_SET_BUS_WIDTH = 6 is also the CMD6 SWITCH_FUNC index */

/* card command class bits from CSD[95:84] */
#define SD_CCC_ERASE                    ((uint16_t)0x0020U)
#define SD_CCC_LOCK_CARD                ((uint16_t)0x0080U)

/* DCache line size for Cortex-M7 */
#define DCACHE_LINE_SIZE                32U
#define ALIGN_DOWN_32(x)                ((uint32_t)(x) & ~(DCACHE_LINE_SIZE - 1U))
#define ALIGN_UP_32(x, base)            (ALIGN_DOWN_32((uint32_t)(base)) + \
                                         (((uint32_t)(x) - ALIGN_DOWN_32((uint32_t)(base)) + \
                                           DCACHE_LINE_SIZE - 1U) & ~(DCACHE_LINE_SIZE - 1U)))

/* -----------------------------------------------------------------------
 * Driver private state
 * ----------------------------------------------------------------------- */
typedef struct {
    struct rt_device    sd_device;
    struct rt_mutex     sd_lock;
    char               *device_name;
    uint8_t             card_type;        /* SD_HIGH_CAPACITY or SD_STD_CAPACITY */
    sdio_card_type_enum card_type_detail; /* fine-grained card type enum */
    uint16_t            rca;              /* relative card address (card-assigned) */
    uint32_t            sector_count;     /* total 512-byte sectors */
    uint32_t            csd[4];
    uint32_t            cid[4];
} gd32_sd_t;

static gd32_sd_t sd0 = {
    .device_name      = "sd0",
    .card_type        = SD_STD_CAPACITY,
    .card_type_detail = SDIO_STD_CAPACITY_SD_CARD_V1_1,
    .rca              = 0U,
    .sector_count     = 0U,
};

/* transfer mode and DMA state (cf. sdcard.c) */
static uint32_t             sd_transmode  = SD_CONF_DTMODE;
static uint32_t             stopcondition = 0U;
static __IO sd_drv_err_t    transerror    = SD_DRV_OK;
static __IO uint32_t        transend      = 0U;

/* SCR register content (two 32-bit words, accessible via extern in header) */
uint32_t sd_scr[2] = {0, 0};

/* 32-byte aligned static bounce buffer for unaligned caller buffers */
static uint32_t __attribute__((aligned(32))) sd_dma_buf[SD_SECTOR_SIZE / sizeof(uint32_t)];

/* -----------------------------------------------------------------------
 * Forward declarations
 * ----------------------------------------------------------------------- */
static sd_drv_err_t cmdsent_error_check(void);
static sd_drv_err_t r1_error_check(uint8_t cmdindex);
static sd_drv_err_t r1_error_type_check(uint32_t resp);
static sd_drv_err_t r2_error_check(void);
static sd_drv_err_t r3_error_check(void);
static sd_drv_err_t r6_error_check(uint8_t cmdindex, uint16_t *prca);
static sd_drv_err_t r7_error_check(void);
static sd_drv_err_t sd_card_state_get(uint8_t *pcardstate);
static sd_drv_err_t sd_scr_get(uint16_t rca, uint32_t *pscr);
static sd_drv_err_t sd_bus_width_config(uint32_t buswidth);
rt_weak void        sdio_gpio_config(void);
static sd_drv_err_t rcu_config(void);
static void         dma_config(uint32_t *buf, uint32_t bufsize);

/* -----------------------------------------------------------------------
 * DCache helpers (Cortex-M7 SCB)
 * ----------------------------------------------------------------------- */
static void sd_dcache_clean(void *addr, uint32_t size)
{
    uint32_t aligned_addr = ALIGN_DOWN_32((uint32_t)addr);
    uint32_t aligned_size = ALIGN_UP_32(size + ((uint32_t)addr - aligned_addr), 0U);
    SCB_CleanDCache_by_Addr((uint32_t *)aligned_addr, (int32_t)aligned_size);
}

static void sd_dcache_invalidate(void *addr, uint32_t size)
{
    uint32_t aligned_addr = ALIGN_DOWN_32((uint32_t)addr);
    uint32_t aligned_size = ALIGN_UP_32(size + ((uint32_t)addr - aligned_addr), 0U);
    SCB_InvalidateDCache_by_Addr((uint32_t *)aligned_addr, (int32_t)aligned_size);
}

/* -----------------------------------------------------------------------
 * GPIO / RCU / IDMA hardware configuration
 * ----------------------------------------------------------------------- */
/*!
    \brief      configure the GPIO of SDIO interface (4-bit SD mode)
    \param[in]  none
    \param[out] none
    \retval     none
*/
rt_weak void sdio_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);

    /* SDIO_DAT0(PC8), SDIO_DAT1(PC9), SDIO_DAT2(PC10), SDIO_DAT3(PC11), SDIO_CLK(PC12) */
    gpio_af_set(GPIOC, GPIO_AF_12, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
    gpio_af_set(GPIOD, GPIO_AF_12, GPIO_PIN_2);

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_12);

    /* SDIO_CMD(PD2) */
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_2);
}

/*!
    \brief      configure the RCU of SDIO0 (PLL1R = 200MHz)
    \param[in]  none
    \param[out] none
    \retval     sd_drv_err_t
*/
static sd_drv_err_t rcu_config(void)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t timeout = 0x10000U;

    /* configure PLL1R = HXTAL(25MHz) / 5 * 40 / 1 = 200MHz */
    rcu_pll_input_output_clock_range_config(IDX_PLL1, RCU_PLL1RNG_4M_8M, RCU_PLL1VCO_192M_836M);
    rcu_pll1_config(5U, 40U, 1U, 1U, 1U);
    rcu_pll_clock_output_enable(RCU_PLL1R);
    rcu_osci_on(RCU_PLL1_CK);

    while((ERROR == rcu_osci_stab_wait(RCU_PLL1_CK)) && (timeout > 0U)) {
        --timeout;
    }
    if(0U == timeout) {
        LOG_E("PLL1 stabilization timeout");
        return SD_DRV_ERROR;
    }

    rcu_sdio_clock_config(IDX_SDIO0, RCU_SDIO0SRC_PLL1R);
    rcu_periph_clock_enable(RCU_SDIO0);

#if SD_USE_DMA
    /* enable SDIO0 interrupt for DMA transfer completion / error handling */
    nvic_irq_enable(SDIO0_IRQn, 2U, 0U);
#endif

    return status;
}

/*!
    \brief      configure the IDMA for SDIO request
    \param[in]  buf: pointer to data buffer (must be 32-byte aligned when DCache is active)
    \param[in]  bufsize: size in units of 32-byte cache blocks (bytes >> 5)
    \param[out] none
    \retval     none
*/
static void dma_config(uint32_t *buf, uint32_t bufsize)
{
    sdio_idma_set(SDIO, SDIO_IDMA_SINGLE_BUFFER, bufsize);
    sdio_idma_buffer0_address_set(SDIO, (uint32_t)buf);
}

/* -----------------------------------------------------------------------
 * SDIO response error checking
 * ----------------------------------------------------------------------- */
/*!
    \brief      check if command sent error occurs (no-response commands)
*/
static sd_drv_err_t cmdsent_error_check(void)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t timeout = 100000U;

    while((RESET == sdio_flag_get(SDIO, SDIO_FLAG_CMDSEND)) && (timeout > 0U)) {
        --timeout;
    }
    if(0U == timeout) {
        return SD_DRV_CMD_TIMEOUT;
    }
    sdio_flag_clear(SDIO, SDIO_MASK_CMD_FLAGS);
    return status;
}

/*!
    \brief      check if error type for R1 response
*/
static sd_drv_err_t r1_error_type_check(uint32_t resp)
{
    sd_drv_err_t status = SD_DRV_ERROR;

    if(resp & SD_R1_CARD_IS_LOCKED) {
        status = SD_DRV_LOCK_FAILED;
    } else if(resp & SD_R1_COM_CRC_ERROR) {
        status = SD_DRV_CMD_CRC_ERROR;
    } else if(resp & SD_R1_ILLEGAL_COMMAND) {
        status = SD_DRV_ILLEGAL_CMD;
    } else if(resp & SD_R1_LOCK_UNLOCK_FAILED) {
        status = SD_DRV_LOCK_FAILED;
    } else {
        /* if else end */
    }
    return status;
}

/*!
    \brief      check if error occurs for R1 response
*/
static sd_drv_err_t r1_error_check(uint8_t cmdindex)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t reg_status = 0U, resp_r1 = 0U;

    reg_status = SDIO_STAT(SDIO);
    while(!(reg_status & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDTMOUT | SDIO_FLAG_CMDRECV))) {
        reg_status = SDIO_STAT(SDIO);
    }
    if(reg_status & SDIO_FLAG_CCRCERR) {
        status = SD_DRV_CMD_CRC_ERROR;
        sdio_flag_clear(SDIO, SDIO_FLAG_CCRCERR);
        return status;
    } else if(reg_status & SDIO_FLAG_CMDTMOUT) {
        status = SD_DRV_CMD_TIMEOUT;
        sdio_flag_clear(SDIO, SDIO_FLAG_CMDTMOUT);
        return status;
    } else {
        /* if else end */
    }

    if(sdio_command_index_get(SDIO) != cmdindex) {
        return SD_DRV_ILLEGAL_CMD;
    }
    sdio_flag_clear(SDIO, SDIO_MASK_CMD_FLAGS);
    resp_r1 = sdio_response_get(SDIO, SDIO_RESPONSE0);
    if(SD_ALLZERO == (resp_r1 & SD_R1_ERROR_BITS)) {
        return status;
    }
    return r1_error_type_check(resp_r1);
}

/*!
    \brief      check if error occurs for R2 response (long response)
*/
static sd_drv_err_t r2_error_check(void)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t reg_status = 0U;

    reg_status = SDIO_STAT(SDIO);
    while(!(reg_status & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDTMOUT | SDIO_FLAG_CMDRECV))) {
        reg_status = SDIO_STAT(SDIO);
    }
    if(reg_status & SDIO_FLAG_CCRCERR) {
        status = SD_DRV_CMD_CRC_ERROR;
        sdio_flag_clear(SDIO, SDIO_FLAG_CCRCERR);
        return status;
    } else if(reg_status & SDIO_FLAG_CMDTMOUT) {
        status = SD_DRV_CMD_TIMEOUT;
        sdio_flag_clear(SDIO, SDIO_FLAG_CMDTMOUT);
        return status;
    } else {
        /* if else end */
    }
    sdio_flag_clear(SDIO, SDIO_MASK_CMD_FLAGS);
    return status;
}

/*!
    \brief      check if error occurs for R3 response (OCR, no CRC)
*/
static sd_drv_err_t r3_error_check(void)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t reg_status = 0U;

    reg_status = SDIO_STAT(SDIO);
    while(!(reg_status & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDTMOUT | SDIO_FLAG_CMDRECV))) {
        reg_status = SDIO_STAT(SDIO);
    }
    if(reg_status & SDIO_FLAG_CMDTMOUT) {
        status = SD_DRV_CMD_TIMEOUT;
        sdio_flag_clear(SDIO, SDIO_FLAG_CMDTMOUT);
        return status;
    }
    /* R3 has no CRC: ignore CCRCERR */
    sdio_flag_clear(SDIO, SDIO_MASK_CMD_FLAGS);
    return status;
}

/*!
    \brief      check if error occurs for R6 response (CMD3: SEND_RELATIVE_ADDR)
    \param[in]  cmdindex: command index
    \param[out] prca: pointer to store the card RCA
    \retval     sd_drv_err_t
*/
static sd_drv_err_t r6_error_check(uint8_t cmdindex, uint16_t *prca)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t reg_status = 0U, response = 0U;

    reg_status = SDIO_STAT(SDIO);
    while(!(reg_status & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDTMOUT | SDIO_FLAG_CMDRECV))) {
        reg_status = SDIO_STAT(SDIO);
    }
    if(reg_status & SDIO_FLAG_CCRCERR) {
        sdio_flag_clear(SDIO, SDIO_FLAG_CCRCERR);
        return SD_DRV_CMD_CRC_ERROR;
    } else if(reg_status & SDIO_FLAG_CMDTMOUT) {
        sdio_flag_clear(SDIO, SDIO_FLAG_CMDTMOUT);
        return SD_DRV_CMD_TIMEOUT;
    } else {
        /* if else end */
    }
    if(sdio_command_index_get(SDIO) != cmdindex) {
        return SD_DRV_ILLEGAL_CMD;
    }
    sdio_flag_clear(SDIO, SDIO_MASK_CMD_FLAGS);
    response = sdio_response_get(SDIO, SDIO_RESPONSE0);
    /* R6 card status error bits: bit15=COM_CRC_ERROR, bit14=ILLEGAL_COMMAND, bit13=ERROR */
    if(response & 0x00008000U) {
        return SD_DRV_CMD_CRC_ERROR;
    }
    if(response & 0x00004000U) {
        return SD_DRV_ILLEGAL_CMD;
    }
    if(response & 0x00002000U) {
        return SD_DRV_ERROR;
    }
    *prca = (uint16_t)(response >> 16U);
    return status;
}

/*!
    \brief      check if error occurs for R7 response (CMD8: SEND_IF_COND)
*/
static sd_drv_err_t r7_error_check(void)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t reg_status = 0U;

    reg_status = SDIO_STAT(SDIO);
    while(!(reg_status & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDTMOUT | SDIO_FLAG_CMDRECV))) {
        reg_status = SDIO_STAT(SDIO);
    }
    if(reg_status & SDIO_FLAG_CMDTMOUT) {
        /* old SD v1.x or non-SD card: no response to CMD8 */
        sdio_flag_clear(SDIO, SDIO_FLAG_CMDTMOUT);
        return SD_DRV_CMD_TIMEOUT;
    } else if(reg_status & SDIO_FLAG_CCRCERR) {
        sdio_flag_clear(SDIO, SDIO_FLAG_CCRCERR);
        return SD_DRV_CMD_CRC_ERROR;
    } else {
        /* if else end */
    }
    sdio_flag_clear(SDIO, SDIO_MASK_CMD_FLAGS);
    return status;
}

/*!
    \brief      get the state which the card is in
    \param[out] pcardstate: a pointer that stores the card state
    \retval     sd_drv_err_t
*/
static sd_drv_err_t sd_card_state_get(uint8_t *pcardstate)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t reg_status = 0U, response = 0U;

    sdio_command_response_config(SDIO, SD_CMD_SEND_STATUS, (uint32_t)sd0.rca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);

    reg_status = SDIO_STAT(SDIO);
    while(!(reg_status & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDTMOUT | SDIO_FLAG_CMDRECV))) {
        reg_status = SDIO_STAT(SDIO);
    }
    if(reg_status & SDIO_FLAG_CCRCERR) {
        status = SD_DRV_CMD_CRC_ERROR;
        sdio_flag_clear(SDIO, SDIO_FLAG_CCRCERR);
        return status;
    } else if(reg_status & SDIO_FLAG_CMDTMOUT) {
        status = SD_DRV_CMD_TIMEOUT;
        sdio_flag_clear(SDIO, SDIO_FLAG_CMDTMOUT);
        return status;
    } else {
        /* if else end */
    }
    sdio_flag_clear(SDIO, SDIO_MASK_INTC_FLAGS);

    response = sdio_response_get(SDIO, SDIO_RESPONSE0);
    *pcardstate = (uint8_t)((response >> 9U) & (uint8_t)0x0FU);

    if(response & SD_R1_ERROR_BITS) {
        return r1_error_type_check(response);
    }
    return status;
}

/* -----------------------------------------------------------------------
 * SD card initialization sequence
 * ----------------------------------------------------------------------- */

/*!
    \brief      configure clock/voltage, CMD0/CMD8/ACMD41, determine card capacity
    \param[in]  none
    \param[out] none
    \retval     sd_drv_err_t
*/
static sd_drv_err_t sd_power_on(void)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t response = 0U;
    uint32_t timedelay = 0U;
    uint8_t  v2_card = 0U;
    uint32_t acmd41_arg = 0U;

    /* configure the SDIO peripheral */
    sdio_clock_config(SDIO, SDIO_SDIOCLKEDGE_RISING, SDIO_CLOCKPWRSAVE_DISABLE, SD_CLK_DIV_INIT);
    sdio_bus_mode_set(SDIO, SDIO_BUSMODE_1BIT);
    sdio_hardware_clock_disable(SDIO);
    sdio_power_state_set(SDIO, SDIO_POWER_ON);

    /* time delay for power-up (same as GD reference) */
    timedelay = 500U;
    while(timedelay > 0U) {
        --timedelay;
    }

    /* send CMD0(GO_IDLE_STATE) to reset all cards */
    sdio_command_response_config(SDIO, SD_CMD_GO_IDLE_STATE, (uint32_t)0x0, SDIO_RESPONSETYPE_NO);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = cmdsent_error_check();
    if(SD_DRV_OK != status) {
        return status;
    }

    /* send CMD8(SEND_IF_COND) to check for SD v2.0+ support
     * arg=0x1AA: VHS=1 (2.7~3.6V), check pattern=0xAA */
    sdio_command_response_config(SDIO, SD_CMD_SEND_IF_COND, (uint32_t)0x000001AAU, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r7_error_check();
    if(SD_DRV_OK == status) {
        /* SD v2.0+: verify card echoes back 0xAA */
        response = sdio_response_get(SDIO, SDIO_RESPONSE0);
        if((response & 0x1FFU) == 0x1AAU) {
            v2_card = 1U;
        }
    }
    /* continue even if CMD8 timed out — SD v1.x cards do not respond */

    /* ACMD41 loop: CMD55 + CMD41 until power-up busy bit clears */
    timedelay = 0x4000U;
    while(timedelay > 0U) {
        --timedelay;

        /* CMD55: APP_CMD — broadcast (RCA=0 here since card not yet published) */
        sdio_command_response_config(SDIO, SD_CMD_APP_CMD, (uint32_t)0x0, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_APP_CMD);
        if(SD_DRV_OK != status) {
            return status;
        }

        /* ACMD41: SD_SEND_OP_COND
         * bit 30 (HCS) = 1 only if the host and card both support SDHC/SDXC
         * bits[23:0] VDD voltage window: 3.2~3.4V */
        acmd41_arg = SD_VOLTAGEWINDOW;
        if(1U == v2_card) {
            acmd41_arg |= (1UL << 30U); /* set HCS bit */
        }
        sdio_command_response_config(SDIO, SD_ACMD_SD_SEND_OP_COND, acmd41_arg, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r3_error_check();
        if(SD_DRV_OK != status) {
            return status;
        }

        response = sdio_response_get(SDIO, SDIO_RESPONSE0);
        /* bit 31: power-up status bit — 1 means card finished power-up */
        if(response & SD_OCR_BUSY) {
            /* CCS (bit 30) determines card type */
            if(response & SD_OCR_CCS) {
                sd0.card_type        = SD_HIGH_CAPACITY;
                sd0.card_type_detail = SDIO_HIGH_CAPACITY_SD_CARD;
            } else {
                sd0.card_type        = SD_STD_CAPACITY;
                sd0.card_type_detail = (1U == v2_card) ?
                                       SDIO_STD_CAPACITY_SD_CARD_V2_0 :
                                       SDIO_STD_CAPACITY_SD_CARD_V1_1;
            }
            return SD_DRV_OK;
        }
    }
    /* loop exhausted without card becoming ready */
    return SD_DRV_VOLTRANGE_INVALID;
}

/*!
    \brief      get CID (CMD2), obtain RCA from card (CMD3), get CSD (CMD9)
*/
static sd_drv_err_t sd_card_init(void)
{
    sd_drv_err_t status = SD_DRV_OK;

    /* send CMD2(ALL_SEND_CID) to read CID */
    sdio_command_response_config(SDIO, SD_CMD_ALL_SEND_CID, (uint32_t)0x0, SDIO_RESPONSETYPE_LONG);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r2_error_check();
    if(SD_DRV_OK != status) {
        return status;
    }
    sd0.cid[0] = sdio_response_get(SDIO, SDIO_RESPONSE0);
    sd0.cid[1] = sdio_response_get(SDIO, SDIO_RESPONSE1);
    sd0.cid[2] = sdio_response_get(SDIO, SDIO_RESPONSE2);
    sd0.cid[3] = sdio_response_get(SDIO, SDIO_RESPONSE3);

    /* send CMD3(SEND_RELATIVE_ADDR) — SD card itself generates and returns its RCA */
    sdio_command_response_config(SDIO, SD_CMD_SEND_RELATIVE_ADDR, (uint32_t)0x0, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r6_error_check(SD_CMD_SEND_RELATIVE_ADDR, &sd0.rca);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* send CMD9(SEND_CSD) to get card-specific data */
    sdio_command_response_config(SDIO, SD_CMD_SEND_CSD, (uint32_t)sd0.rca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_LONG);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r2_error_check();
    if(SD_DRV_OK != status) {
        return status;
    }
    sd0.csd[0] = sdio_response_get(SDIO, SDIO_RESPONSE0);
    sd0.csd[1] = sdio_response_get(SDIO, SDIO_RESPONSE1);
    sd0.csd[2] = sdio_response_get(SDIO, SDIO_RESPONSE2);
    sd0.csd[3] = sdio_response_get(SDIO, SDIO_RESPONSE3);

    return status;
}

/*!
    \brief      parse sector count from CSD register
                CSD v2 (SDHC/SDXC): sector_count = (C_SIZE+1) * 1024
                CSD v1 (SDSC):       sector_count from C_SIZE, C_SIZE_MULT, READ_BL_LEN
*/
static void sd_sector_count_get(void)
{
    uint8_t  csd_version;
    uint32_t c_size, c_size_mult, read_bl_len;
    uint32_t block_nr, block_len;

    /* CSD_STRUCTURE [127:126] = csd[0][31:30] */
    csd_version = (uint8_t)((sd0.csd[0] >> 30U) & 0x03U);

    if(1U == csd_version) {
        /* CSD v2.0 (SDHC/SDXC)
         * C_SIZE [69:48]: 22 bits
         *   CSD[69:64] = response1[5:0]  (SDIO response1 = CSD[95:64])
         *   CSD[63:48] = response2[31:16] (SDIO response2 = CSD[63:32])
         */
        c_size = ((sd0.csd[1] & 0x3FU) << 16U) | ((sd0.csd[2] >> 16U) & 0xFFFFU);
        sd0.sector_count = (c_size + 1U) * 1024U;
    } else {
        /* CSD v1.0 (SDSC)
         * READ_BL_LEN [83:80] = response1[19:16]
         * C_SIZE       [73:62] = response1[9:0] << 2 | response2[31:30]
         * C_SIZE_MULT  [49:47] = response2[17:15]
         */
        read_bl_len = (sd0.csd[1] >> 16U) & 0x0FU;
        c_size = ((sd0.csd[1] & 0x3FFU) << 2U) | (sd0.csd[2] >> 30U);
        c_size_mult = (sd0.csd[2] >> 15U) & 0x07U;
        block_nr = (c_size + 1U) * (1U << (c_size_mult + 2U));
        block_len = (1U << read_bl_len);
        sd0.sector_count = (block_nr * block_len) / SD_SECTOR_SIZE;
    }
}

/*!
    \brief      select the card and move to transfer state (CMD7)
*/
static sd_drv_err_t sd_card_select(void)
{
    sdio_command_response_config(SDIO, SD_CMD_SELECT_DESELECT_CARD, (uint32_t)sd0.rca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    return r1_error_check(SD_CMD_SELECT_DESELECT_CARD);
}

/*!
    \brief      switch to 4-bit bus width via ACMD6 and update SDIO register
*/
static sd_drv_err_t sd_bus_width_4bit(void)
{
    sd_drv_err_t status = SD_DRV_OK;

    /* CMD55: APP_CMD addressed to selected card */
    sdio_command_response_config(SDIO, SD_CMD_APP_CMD, (uint32_t)sd0.rca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_APP_CMD);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* ACMD6: SET_BUS_WIDTH — arg=2 selects 4-bit */
    sdio_command_response_config(SDIO, SD_ACMD_SET_BUS_WIDTH, (uint32_t)0x2, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_ACMD_SET_BUS_WIDTH);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* update SDIO host controller to 4-bit, transfer clock */
    sdio_clock_config(SDIO, SDIO_SDIOCLKEDGE_RISING, SDIO_CLOCKPWRSAVE_DISABLE, SD_CLK_DIV_TRANS);
    sdio_bus_mode_set(SDIO, SDIO_BUSMODE_4BIT);
    sdio_hardware_clock_enable(SDIO);
    sdio_flag_clear(SDIO, SDIO_MASK_INTC_FLAGS);

    return status;
}

/* -----------------------------------------------------------------------
 * SCR read and bus-width configuration helpers
 * ----------------------------------------------------------------------- */

/*!
    \brief      get the SCR register of the addressed card (ACMD51)
    \param[in]  rca: card RCA
    \param[out] pscr: two-word buffer to receive byte-swapped SCR content
    \retval     sd_drv_err_t
*/
static sd_drv_err_t sd_scr_get(uint16_t rca, uint32_t *pscr)
{
    uint32_t temp_scr[2] = {0, 0};
    uint32_t idx_scr = 0U;
    sd_drv_err_t status = SD_DRV_OK;

    /* CMD16: SET_BLOCKLEN to 8 bytes */
    sdio_command_response_config(SDIO, SD_CMD_SET_BLOCKLEN, (uint32_t)8U, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_SET_BLOCKLEN);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* CMD55: APP_CMD (addressed) */
    sdio_command_response_config(SDIO, SD_CMD_APP_CMD, (uint32_t)rca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_APP_CMD);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* configure data transfer: 8 bytes */
    sdio_data_config(SDIO, SD_DATATIMEOUT, (uint32_t)8U, SDIO_DATABLOCKSIZE_8BYTES);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOSDIO);
    sdio_dsm_enable(SDIO);

    /* ACMD51: SEND_SCR */
    sdio_command_response_config(SDIO, SD_APPCMD_SEND_SCR, (uint32_t)0x0, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_APPCMD_SEND_SCR);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* poll and collect 8 bytes */
    while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT | SDIO_FLAG_RXORE |
                         SDIO_FLAG_DTBLKEND | SDIO_FLAG_DTEND)) {
        if((SET != sdio_flag_get(SDIO, SDIO_FLAG_RFE)) &&
           (SET == sdio_flag_get(SDIO, SDIO_FLAG_DATSTA))) {
            *(temp_scr + idx_scr) = sdio_data_read(SDIO);
            ++idx_scr;
        }
    }

    if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR)) {
        status = SD_DRV_DATA_CRC_ERROR;
        sdio_flag_clear(SDIO, SDIO_FLAG_DTCRCERR);
        return status;
    } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTTMOUT)) {
        status = SD_DRV_DATA_TIMEOUT;
        sdio_flag_clear(SDIO, SDIO_FLAG_DTTMOUT);
        return status;
    } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RXORE)) {
        status = SD_DRV_RX_OVERRUN;
        sdio_flag_clear(SDIO, SDIO_FLAG_RXORE);
        return status;
    } else {
        /* if else end */
    }

    sdio_flag_clear(SDIO, SDIO_MASK_INTC_FLAGS);

    /* byte-swap to match SD SCR bit ordering */
    *(pscr + 1U) = ((temp_scr[0] & SD_MASK_0_7BITS) << 24U) |
                   ((temp_scr[0] & SD_MASK_8_15BITS) << 8U)  |
                   ((temp_scr[0] & SD_MASK_16_23BITS) >> 8U) |
                   ((temp_scr[0] & SD_MASK_24_31BITS) >> 24U);
    *(pscr)      = ((temp_scr[1] & SD_MASK_0_7BITS) << 24U) |
                   ((temp_scr[1] & SD_MASK_8_15BITS) << 8U)  |
                   ((temp_scr[1] & SD_MASK_16_23BITS) >> 8U) |
                   ((temp_scr[1] & SD_MASK_24_31BITS) >> 24U);
    return status;
}

/*!
    \brief      send ACMD6 to set the card bus width and optionally update SDIO host
    \param[in]  buswidth: SD_BUS_WIDTH_1BIT or SD_BUS_WIDTH_4BIT
    \retval     sd_drv_err_t
*/
static sd_drv_err_t sd_bus_width_config(uint32_t buswidth)
{
    sd_drv_err_t status = SD_DRV_OK;

    /* check whether the card is locked */
    if(sdio_response_get(SDIO, SDIO_RESPONSE0) & SD_CARDSTATE_LOCKED) {
        return SD_DRV_LOCK_FAILED;
    }

    /* read SCR to verify bus-width support */
    status = sd_scr_get(sd0.rca, sd_scr);
    if(SD_DRV_OK != status) {
        return status;
    }

    if(SD_BUS_WIDTH_1BIT == buswidth) {
        if(SD_ALLZERO != (sd_scr[1] & SD_BUS_WIDTH_1BIT)) {
            /* CMD55: APP_CMD */
            sdio_command_response_config(SDIO, SD_CMD_APP_CMD,
                                         (uint32_t)sd0.rca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
            sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
            sdio_csm_enable(SDIO);
            status = r1_error_check(SD_CMD_APP_CMD);
            if(SD_DRV_OK != status) {
                return status;
            }
            /* ACMD6: arg=0 → 1-bit bus */
            sdio_command_response_config(SDIO, SD_ACMD_SET_BUS_WIDTH,
                                         (uint32_t)0x0, SDIO_RESPONSETYPE_SHORT);
            sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
            sdio_csm_enable(SDIO);
            status = r1_error_check(SD_ACMD_SET_BUS_WIDTH);
        } else {
            status = SD_DRV_OPERATION_IMPROPER;
        }
    } else if(SD_BUS_WIDTH_4BIT == buswidth) {
        if(SD_ALLZERO != (sd_scr[1] & SD_BUS_WIDTH_4BIT)) {
            /* CMD55: APP_CMD */
            sdio_command_response_config(SDIO, SD_CMD_APP_CMD,
                                         (uint32_t)sd0.rca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
            sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
            sdio_csm_enable(SDIO);
            status = r1_error_check(SD_CMD_APP_CMD);
            if(SD_DRV_OK != status) {
                return status;
            }
            /* ACMD6: arg=2 → 4-bit bus */
            sdio_command_response_config(SDIO, SD_ACMD_SET_BUS_WIDTH,
                                         (uint32_t)0x2, SDIO_RESPONSETYPE_SHORT);
            sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
            sdio_csm_enable(SDIO);
            status = r1_error_check(SD_ACMD_SET_BUS_WIDTH);
        } else {
            status = SD_DRV_OPERATION_IMPROPER;
        }
    } else {
        status = SD_DRV_PARAM_ERROR;
    }
    return status;
}

/* -----------------------------------------------------------------------
 * Public API — bus mode, transfer mode, card info, erase, status
 * ----------------------------------------------------------------------- */

/*!
    \brief      configure bus width and clock speed (matches sdcard.c sd_bus_mode_config)
    \param[in]  busmode: SDIO_BUSMODE_1BIT or SDIO_BUSMODE_4BIT
    \param[in]  speed: SD_SPEED_DEFAULT / SD_SPEED_HIGH / SD_SPEED_SDRxx / SD_SPEED_DDR50
    \retval     sd_drv_err_t
*/
sd_drv_err_t sd_bus_mode_config(uint32_t busmode, uint32_t speed)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t count = 0U, clk_div = 0U;

    /* configure bus width on the card and SDIO host */
    if(SDIO_BUSMODE_4BIT == busmode) {
        status = sd_bus_width_config(SD_BUS_WIDTH_4BIT);
        if(SD_DRV_OK == status) {
            sdio_bus_mode_set(SDIO, SDIO_BUSMODE_4BIT);
        }
    } else if(SDIO_BUSMODE_1BIT == busmode) {
        status = sd_bus_width_config(SD_BUS_WIDTH_1BIT);
        if(SD_DRV_OK == status) {
            sdio_bus_mode_set(SDIO, SDIO_BUSMODE_1BIT);
        }
    } else {
        return SD_DRV_PARAM_ERROR;
    }

    if(SD_DRV_OK != status) {
        return status;
    }

    if((speed != SD_SPEED_DEFAULT) && (speed != SD_SPEED_HIGH)) {
        /* UHS-I speed switch via CMD6 (SWITCH_FUNC, command index = 6) */
        switch(speed) {
        case SD_SPEED_SDR25:
            clk_div = SD_CLK_DIV_TRANS_SDR25SPEED;
            break;
        case SD_SPEED_SDR50:
            clk_div = SD_CLK_DIV_TRANS_SDR50SPEED;
            break;
        case SD_SPEED_SDR104:
            clk_div = SD_CLK_DIV_TRANS_SDR104SPEED;
            break;
        case SD_SPEED_DDR50:
            clk_div = SD_CLK_DIV_TRANS_DDR50SPEED;
            break;
        default:
            clk_div = SD_CLK_DIV_TRANS_DSPEED;
            break;
        }

        /* CMD16: SET_BLOCKLEN to 64 bytes (status data block for CMD6 response) */
        sdio_command_response_config(SDIO, SD_CMD_SET_BLOCKLEN, (uint32_t)64U, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_SET_BLOCKLEN);
        if(SD_DRV_OK != status) {
            return status;
        }

        sdio_data_config(SDIO, SD_DATATIMEOUT, 64U, SDIO_DATABLOCKSIZE_64BYTES);
        sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOSDIO);
        sdio_dsm_enable(SDIO);

        /* CMD6 (SWITCH_FUNC): speed argument encodes the function group 1 selection
         * SD_SPEED_SDR25=0x80FFFF01, SDR50=0x80FF1F02, SDR104=0x80FF1F03, DDR50=0x80FF1F04 */
        sdio_command_response_config(SDIO, SD_ACMD_SET_BUS_WIDTH, speed, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_ACMD_SET_BUS_WIDTH);
        if(SD_DRV_OK != status) {
            return status;
        }

        /* drain the 64-byte function switch status block */
        while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT | SDIO_FLAG_RXORE |
                             SDIO_FLAG_DTBLKEND | SDIO_FLAG_DTEND)) {
            if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RFH)) {
                for(count = 0U; count < SD_FIFOHALF_WORDS; count++) {
                    sdio_data_read(SDIO);
                }
            }
        }
        sdio_flag_clear(SDIO, SDIO_MASK_INTC_FLAGS);

        sdio_clock_config(SDIO, SDIO_SDIOCLKEDGE_RISING, SDIO_CLOCKPWRSAVE_DISABLE, clk_div);
        if(SD_SPEED_DDR50 == speed) {
            sdio_data_rate_set(SDIO, SDIO_DATA_RATE_DDR);
        }
        sdio_hardware_clock_enable(SDIO);
    } else if(SD_SPEED_HIGH == speed) {
        sdio_clock_config(SDIO, SDIO_SDIOCLKEDGE_RISING, SDIO_CLOCKPWRSAVE_DISABLE,
                          SD_CLK_DIV_TRANS_HSPEED);
        sdio_hardware_clock_enable(SDIO);
    } else {
        /* SD_SPEED_DEFAULT */
        sdio_clock_config(SDIO, SDIO_SDIOCLKEDGE_RISING, SDIO_CLOCKPWRSAVE_DISABLE,
                          SD_CLK_DIV_TRANS_DSPEED);
        sdio_hardware_clock_enable(SDIO);
    }
    return status;
}

/*!
    \brief      configure the data transfer mode
    \param[in]  txmode: SD_DMA_MODE or SD_POLLING_MODE
    \retval     sd_drv_err_t
*/
sd_drv_err_t sd_transfer_mode_config(uint32_t txmode)
{
    if((SD_DMA_MODE == txmode) || (SD_POLLING_MODE == txmode)) {
        sd_transmode = txmode;
        return SD_DRV_OK;
    }
    return SD_DRV_PARAM_ERROR;
}

/*!
    \brief      stop an ongoing data transfer (CMD12)
    \retval     sd_drv_err_t
*/
sd_drv_err_t sd_transfer_stop(void)
{
    sd_drv_err_t status = SD_DRV_OK;
    sdio_command_response_config(SDIO, SD_CMD_STOP_TRANSMISSION, (uint32_t)0x0, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_trans_stop_enable(SDIO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_STOP_TRANSMISSION);
    sdio_trans_stop_disable(SDIO);
    return status;
}

/*!
    \brief      get card status register via CMD13
    \param[out] pcardstatus: pointer to store the 32-bit card status
    \retval     sd_drv_err_t
*/
sd_drv_err_t sd_cardstatus_get(uint32_t *pcardstatus)
{
    sd_drv_err_t status = SD_DRV_OK;

    if(NULL == pcardstatus) {
        return SD_DRV_PARAM_ERROR;
    }
    sdio_command_response_config(SDIO, SD_CMD_SEND_STATUS,
                                 (uint32_t)sd0.rca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_SEND_STATUS);
    if(SD_DRV_OK != status) {
        return status;
    }
    *pcardstatus = sdio_response_get(SDIO, SDIO_RESPONSE0);
    return status;
}

/*!
    \brief      select or deselect a card via CMD7
    \param[in]  cardrca: card RCA (0 = deselect all)
    \retval     sd_drv_err_t
*/
sd_drv_err_t sd_card_select_deselect(uint16_t cardrca)
{
    sdio_command_response_config(SDIO, SD_CMD_SELECT_DESELECT_CARD,
                                 (uint32_t)cardrca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    return r1_error_check(SD_CMD_SELECT_DESELECT_CARD);
}

/*!
    \brief      get SD card capacity in KBytes
    \retval     capacity in KB (0 if unknown card type)
*/
uint32_t sd_card_capacity_get(void)
{
    uint8_t  tempbyte = 0U, devicesize_mult = 0U, readblklen = 0U;
    uint32_t capacity = 0U, devicesize = 0U;

    if((SDIO_STD_CAPACITY_SD_CARD_V1_1 == sd0.card_type_detail) ||
       (SDIO_STD_CAPACITY_SD_CARD_V2_0 == sd0.card_type_detail)) {
        /* CSD version 1.0 (SDSC) — C_SIZE[73:62], C_SIZE_MULT[49:47], READ_BL_LEN[83:80] */
        tempbyte = (uint8_t)((sd0.csd[1] & SD_MASK_8_15BITS) >> 8U);
        devicesize |= ((uint32_t)tempbyte & 0x03U) << 10U;
        tempbyte = (uint8_t)(sd0.csd[1] & SD_MASK_0_7BITS);
        devicesize |= (uint32_t)((uint32_t)tempbyte << 2U);
        tempbyte = (uint8_t)((sd0.csd[2] & SD_MASK_24_31BITS) >> 24U);
        devicesize |= ((uint32_t)tempbyte & 0xC0U) >> 6U;

        tempbyte = (uint8_t)((sd0.csd[2] & SD_MASK_16_23BITS) >> 16U);
        devicesize_mult = (tempbyte & 0x03U) << 1U;
        tempbyte = (uint8_t)((sd0.csd[2] & SD_MASK_8_15BITS) >> 8U);
        devicesize_mult |= (tempbyte & 0x80U) >> 7U;

        tempbyte = (uint8_t)((sd0.csd[1] & SD_MASK_16_23BITS) >> 16U);
        readblklen = tempbyte & 0x0FU;

        /* capacity = BLOCKNR * BLOCK_LEN; BLOCKNR = (C_SIZE+1)*MULT; MULT = 2^(C_SIZE_MULT+2) */
        capacity = (devicesize + 1U) * (1U << (devicesize_mult + 2U));
        capacity *= (1U << readblklen);
        capacity /= 1024U;  /* convert to KB */
    } else if(SDIO_HIGH_CAPACITY_SD_CARD == sd0.card_type_detail) {
        /* CSD version 2.0 (SDHC/SDXC) — capacity = (C_SIZE+1) * 512 KB */
        tempbyte = (uint8_t)(sd0.csd[1] & SD_MASK_0_7BITS);
        devicesize = ((uint32_t)tempbyte & 0x3FU) << 16U;
        tempbyte = (uint8_t)((sd0.csd[2] & SD_MASK_24_31BITS) >> 24U);
        devicesize |= (uint32_t)((uint32_t)tempbyte << 8U);
        tempbyte = (uint8_t)((sd0.csd[2] & SD_MASK_16_23BITS) >> 16U);
        devicesize |= (uint32_t)tempbyte;
        capacity = (devicesize + 1U) * 512U;
    } else {
        /* if else end */
    }
    return capacity;
}

/*!
    \brief      erase a continuous range of sectors (CMD32 / CMD33 / CMD38)
    \param[in]  startaddr: first sector address
    \param[in]  endaddr:   last sector address (inclusive)
    \retval     sd_drv_err_t
*/
sd_drv_err_t sd_erase(uint32_t startaddr, uint32_t endaddr)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t count = 0U, clkdiv = 0U;
    __IO uint32_t delay = 0U;
    uint8_t  cardstate = 0U, tempbyte = 0U;
    uint16_t tempccc = 0U;

    /* check erase support from CSD command classes */
    tempbyte = (uint8_t)((sd0.csd[1] & SD_MASK_24_31BITS) >> 24U);
    tempccc  = (uint16_t)((uint16_t)tempbyte << 4U);
    tempbyte = (uint8_t)((sd0.csd[1] & SD_MASK_16_23BITS) >> 16U);
    tempccc |= ((uint16_t)tempbyte & 0xF0U) >> 4U;
    if(0U == (tempccc & SD_CCC_ERASE)) {
        return SD_DRV_UNSUPPORTED_CARD;
    }

    clkdiv = (SDIO_CLKCTL(SDIO) & SDIO_CLKCTL_DIV);
    clkdiv *= 2U;
    delay = 168000U / (clkdiv ? clkdiv : 1U);

    if(sdio_response_get(SDIO, SDIO_RESPONSE0) & SD_CARDSTATE_LOCKED) {
        return SD_DRV_LOCK_FAILED;
    }

    /* SDHC/SDXC uses sector addressing; SDSC uses byte addressing */
    if(SD_HIGH_CAPACITY != sd0.card_type) {
        startaddr *= SD_SECTOR_SIZE;
        endaddr   *= SD_SECTOR_SIZE;
    }

    /* CMD32: ERASE_WR_BLK_START */
    sdio_command_response_config(SDIO, SD_CMD_ERASE_WR_BLK_START, startaddr, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_ERASE_WR_BLK_START);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* CMD33: ERASE_WR_BLK_END */
    sdio_command_response_config(SDIO, SD_CMD_ERASE_WR_BLK_END, endaddr, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_ERASE_WR_BLK_END);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* CMD38: ERASE */
    sdio_command_response_config(SDIO, SD_CMD_ERASE, (uint32_t)0x0, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_ERASE);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* erase delay loop */
    for(count = 0U; count < delay; count++) {
    }

    /* wait for card to finish erasing */
    status = sd_card_state_get(&cardstate);
    while((SD_DRV_OK == status) && ((SD_CARDSTATE_PROGRAMMING == cardstate) ||
          (SD_CARDSTATE_RECEIVING == cardstate))) {
        status = sd_card_state_get(&cardstate);
    }
    return status;
}

/*!
    \brief      get detailed card information from stored CID and CSD registers
    \param[out] pcardinfo: pointer to sd_card_info_struct to fill
    \retval     sd_drv_err_t
*/
sd_drv_err_t sd_card_information_get(sd_card_info_struct *pcardinfo)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint8_t tempbyte = 0U;

    if(NULL == pcardinfo) {
        return SD_DRV_PARAM_ERROR;
    }

    pcardinfo->card_type = sd0.card_type_detail;
    pcardinfo->card_rca  = sd0.rca;

    /* ---- CID parsing ---- */
    /* CID byte 0 */
    tempbyte = (uint8_t)((sd0.cid[0] & SD_MASK_24_31BITS) >> 24U);
    pcardinfo->card_cid.mid = tempbyte;

    /* CID bytes 1-2: OID */
    tempbyte = (uint8_t)((sd0.cid[0] & SD_MASK_16_23BITS) >> 16U);
    pcardinfo->card_cid.oid = (uint16_t)((uint16_t)tempbyte << 8U);
    tempbyte = (uint8_t)((sd0.cid[0] & SD_MASK_8_15BITS) >> 8U);
    pcardinfo->card_cid.oid |= (uint16_t)tempbyte;

    /* CID bytes 3-6: PNM[0..3] */
    tempbyte = (uint8_t)(sd0.cid[0] & SD_MASK_0_7BITS);
    pcardinfo->card_cid.pnm0 = (uint32_t)((uint32_t)tempbyte << 24U);
    tempbyte = (uint8_t)((sd0.cid[1] & SD_MASK_24_31BITS) >> 24U);
    pcardinfo->card_cid.pnm0 |= (uint32_t)((uint32_t)tempbyte << 16U);
    tempbyte = (uint8_t)((sd0.cid[1] & SD_MASK_16_23BITS) >> 16U);
    pcardinfo->card_cid.pnm0 |= (uint32_t)((uint32_t)tempbyte << 8U);
    tempbyte = (uint8_t)((sd0.cid[1] & SD_MASK_8_15BITS) >> 8U);
    pcardinfo->card_cid.pnm0 |= (uint32_t)tempbyte;

    /* CID byte 7: PNM[4] */
    tempbyte = (uint8_t)(sd0.cid[1] & SD_MASK_0_7BITS);
    pcardinfo->card_cid.pnm1 = tempbyte;

    /* CID byte 8: PRV */
    tempbyte = (uint8_t)((sd0.cid[2] & SD_MASK_24_31BITS) >> 24U);
    pcardinfo->card_cid.prv = tempbyte;

    /* CID bytes 9-12: PSN */
    tempbyte = (uint8_t)((sd0.cid[2] & SD_MASK_16_23BITS) >> 16U);
    pcardinfo->card_cid.psn = (uint32_t)((uint32_t)tempbyte << 24U);
    tempbyte = (uint8_t)((sd0.cid[2] & SD_MASK_8_15BITS) >> 8U);
    pcardinfo->card_cid.psn |= (uint32_t)((uint32_t)tempbyte << 16U);
    tempbyte = (uint8_t)(sd0.cid[2] & SD_MASK_0_7BITS);
    pcardinfo->card_cid.psn |= (uint32_t)((uint32_t)tempbyte << 8U);
    tempbyte = (uint8_t)((sd0.cid[3] & SD_MASK_24_31BITS) >> 24U);
    pcardinfo->card_cid.psn |= (uint32_t)tempbyte;

    /* CID bytes 13-14: MDT */
    tempbyte = (uint8_t)((sd0.cid[3] & SD_MASK_16_23BITS) >> 16U);
    pcardinfo->card_cid.mdt = ((uint16_t)tempbyte & 0x0FU) << 8U;
    tempbyte = (uint8_t)((sd0.cid[3] & SD_MASK_8_15BITS) >> 8U);
    pcardinfo->card_cid.mdt |= (uint16_t)tempbyte;

    /* CID byte 15: CRC */
    tempbyte = (uint8_t)(sd0.cid[3] & SD_MASK_0_7BITS);
    pcardinfo->card_cid.cid_crc = (tempbyte & 0xFEU) >> 1U;

    /* ---- CSD parsing ---- */
    tempbyte = (uint8_t)((sd0.csd[0] & SD_MASK_24_31BITS) >> 24U);
    pcardinfo->card_csd.csd_struct = (tempbyte & 0xC0U) >> 6U;

    tempbyte = (uint8_t)((sd0.csd[0] & SD_MASK_16_23BITS) >> 16U);
    pcardinfo->card_csd.taac = tempbyte;

    tempbyte = (uint8_t)((sd0.csd[0] & SD_MASK_8_15BITS) >> 8U);
    pcardinfo->card_csd.nsac = tempbyte;

    tempbyte = (uint8_t)(sd0.csd[0] & SD_MASK_0_7BITS);
    pcardinfo->card_csd.tran_speed = tempbyte;

    tempbyte = (uint8_t)((sd0.csd[1] & SD_MASK_24_31BITS) >> 24U);
    pcardinfo->card_csd.ccc = (uint16_t)((uint16_t)tempbyte << 4U);
    tempbyte = (uint8_t)((sd0.csd[1] & SD_MASK_16_23BITS) >> 16U);
    pcardinfo->card_csd.ccc |= ((uint16_t)tempbyte & 0xF0U) >> 4U;
    pcardinfo->card_csd.read_bl_len = tempbyte & 0x0FU;

    tempbyte = (uint8_t)((sd0.csd[1] & SD_MASK_8_15BITS) >> 8U);
    pcardinfo->card_csd.read_bl_partial    = (tempbyte & 0x80U) >> 7U;
    pcardinfo->card_csd.write_blk_misalign = (tempbyte & 0x40U) >> 6U;
    pcardinfo->card_csd.read_blk_misalign  = (tempbyte & 0x20U) >> 5U;
    pcardinfo->card_csd.dsp_imp            = (tempbyte & 0x10U) >> 4U;

    if((SDIO_STD_CAPACITY_SD_CARD_V1_1 == sd0.card_type_detail) ||
       (SDIO_STD_CAPACITY_SD_CARD_V2_0 == sd0.card_type_detail)) {
        /* CSD v1.0 */
        pcardinfo->card_csd.c_size = ((uint32_t)tempbyte & 0x03U) << 10U;
        tempbyte = (uint8_t)(sd0.csd[1] & SD_MASK_0_7BITS);
        pcardinfo->card_csd.c_size |= (uint32_t)((uint32_t)tempbyte << 2U);
        tempbyte = (uint8_t)((sd0.csd[2] & SD_MASK_24_31BITS) >> 24U);
        pcardinfo->card_csd.c_size |= ((uint32_t)tempbyte & 0xC0U) >> 6U;
        pcardinfo->card_csd.vdd_r_curr_min = (tempbyte & 0x38U) >> 3U;
        pcardinfo->card_csd.vdd_r_curr_max = tempbyte & 0x07U;

        tempbyte = (uint8_t)((sd0.csd[2] & SD_MASK_16_23BITS) >> 16U);
        pcardinfo->card_csd.vdd_w_curr_min = (tempbyte & 0xE0U) >> 5U;
        pcardinfo->card_csd.vdd_w_curr_max = (tempbyte & 0x1CU) >> 2U;
        pcardinfo->card_csd.c_size_mult     = (tempbyte & 0x03U) << 1U;

        tempbyte = (uint8_t)((sd0.csd[2] & SD_MASK_8_15BITS) >> 8U);
        pcardinfo->card_csd.c_size_mult |= (tempbyte & 0x80U) >> 7U;

        pcardinfo->card_blocksize = 1U << (pcardinfo->card_csd.read_bl_len);
        pcardinfo->card_capacity  = pcardinfo->card_csd.c_size + 1U;
        pcardinfo->card_capacity *= (1U << (pcardinfo->card_csd.c_size_mult + 2U));
        pcardinfo->card_capacity *= pcardinfo->card_blocksize;
    } else if(SDIO_HIGH_CAPACITY_SD_CARD == sd0.card_type_detail) {
        /* CSD v2.0 */
        tempbyte = (uint8_t)(sd0.csd[1] & SD_MASK_0_7BITS);
        pcardinfo->card_csd.c_size = ((uint32_t)tempbyte & 0x3FU) << 16U;
        tempbyte = (uint8_t)((sd0.csd[2] & SD_MASK_24_31BITS) >> 24U);
        pcardinfo->card_csd.c_size |= (uint32_t)((uint32_t)tempbyte << 8U);
        tempbyte = (uint8_t)((sd0.csd[2] & SD_MASK_16_23BITS) >> 16U);
        pcardinfo->card_csd.c_size |= (uint32_t)tempbyte;

        pcardinfo->card_blocksize = 512U;
        pcardinfo->card_capacity  = (uint64_t)(pcardinfo->card_csd.c_size + 1U) * 512U * 1024U;
    } else {
        /* if else end */
    }

    tempbyte = (uint8_t)((sd0.csd[2] & SD_MASK_8_15BITS) >> 8U);
    pcardinfo->card_csd.erase_blk_en = (tempbyte & 0x40U) >> 6U;
    pcardinfo->card_csd.sector_size   = (tempbyte & 0x3FU) << 1U;

    tempbyte = (uint8_t)(sd0.csd[2] & SD_MASK_0_7BITS);
    pcardinfo->card_csd.sector_size |= (tempbyte & 0x80U) >> 7U;
    pcardinfo->card_csd.wp_grp_size  = tempbyte & 0x7FU;

    tempbyte = (uint8_t)((sd0.csd[3] & SD_MASK_24_31BITS) >> 24U);
    pcardinfo->card_csd.wp_grp_enable  = (tempbyte & 0x80U) >> 7U;
    pcardinfo->card_csd.r2w_factor     = (tempbyte & 0x1CU) >> 2U;
    pcardinfo->card_csd.write_bl_len   = (tempbyte & 0x03U) << 2U;

    tempbyte = (uint8_t)((sd0.csd[3] & SD_MASK_16_23BITS) >> 16U);
    pcardinfo->card_csd.write_bl_len     |= (tempbyte & 0xC0U) >> 6U;
    pcardinfo->card_csd.write_bl_partial  = (tempbyte & 0x20U) >> 5U;

    tempbyte = (uint8_t)((sd0.csd[3] & SD_MASK_8_15BITS) >> 8U);
    pcardinfo->card_csd.file_format_grp  = (tempbyte & 0x80U) >> 7U;
    pcardinfo->card_csd.copy_flag        = (tempbyte & 0x40U) >> 6U;
    pcardinfo->card_csd.perm_write_protect = (tempbyte & 0x20U) >> 5U;
    pcardinfo->card_csd.tmp_write_protect  = (tempbyte & 0x10U) >> 4U;
    pcardinfo->card_csd.file_format        = (tempbyte & 0x0CU) >> 2U;

    tempbyte = (uint8_t)(sd0.csd[3] & SD_MASK_0_7BITS);
    pcardinfo->card_csd.csd_crc = (tempbyte & 0xFEU) >> 1U;

    return status;
}

/* -----------------------------------------------------------------------
 * Card-ready helpers
 * ----------------------------------------------------------------------- */

/*!
    \brief      wait for card to leave Programming/Receiving state
*/
static sd_drv_err_t wait_card_ready(void)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint8_t cardstate = 0U;
    uint32_t timeout = 0x80000U;

    status = sd_card_state_get(&cardstate);
    while((SD_DRV_OK == status) && ((SD_CARDSTATE_PROGRAMMING == cardstate) || (SD_CARDSTATE_RECEIVING == cardstate))) {
        if(0U == --timeout) {
            LOG_E("sd: card not ready timeout");
            return SD_DRV_ERROR;
        }
        status = sd_card_state_get(&cardstate);
    }
    return status;
}

/*!
    \brief      poll R1 READY_FOR_DATA bit via CMD13
*/
static sd_drv_err_t wait_ready(void)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t response = 0U;
    uint32_t timeout = 100000U;

    sdio_command_response_config(SDIO, SD_CMD_SEND_STATUS, (uint32_t)sd0.rca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_SEND_STATUS);
    if(SD_DRV_OK != status) {
        return status;
    }
    response = sdio_response_get(SDIO, SDIO_RESPONSE0);

    while((0U == (response & SD_R1_READY_FOR_DATA)) && (timeout > 0U)) {
        --timeout;
        sdio_command_response_config(SDIO, SD_CMD_SEND_STATUS, (uint32_t)sd0.rca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_SEND_STATUS);
        if(SD_DRV_OK != status) {
            return status;
        }
        response = sdio_response_get(SDIO, SDIO_RESPONSE0);
    }
    if(0U == timeout) {
        status = SD_DRV_ERROR;
    }
    return status;
}

/* -----------------------------------------------------------------------
 * ISR processing for DMA mode (cf. sd_interrupts_process in sdcard.c)
 * ----------------------------------------------------------------------- */

/*!
    \brief      process all the interrupts which the corresponding flags are set
*/
sd_drv_err_t sd_isr_process(void)
{
    transerror = SD_DRV_OK;
    if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_DTEND)) {
        sdio_interrupt_flag_clear(SDIO, SDIO_INT_FLAG_DTEND);
        sdio_idma_disable(SDIO);
        sdio_interrupt_disable(SDIO, SDIO_INT_DTCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_DTEND |
                               SDIO_INT_TFH | SDIO_INT_RFH | SDIO_INT_TXURE | SDIO_INT_RXORE);
        sdio_trans_start_disable(SDIO);
        /* send CMD12 to stop data transfer after multi-block operations */
        if(1U == stopcondition) {
            transerror = sd_transfer_stop();
        } else {
            transerror = SD_DRV_OK;
        }
        transend = 1U;
        sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);
        return transerror;
    }

    if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_DTCRCERR | SDIO_INT_FLAG_DTTMOUT |
                                              SDIO_INT_FLAG_TXURE | SDIO_INT_FLAG_RXORE)) {
        if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_DTCRCERR)) {
            transerror = SD_DRV_DATA_CRC_ERROR;
        }
        if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_DTTMOUT)) {
            transerror = SD_DRV_DATA_TIMEOUT;
        }
        if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_TXURE)) {
            transerror = SD_DRV_TX_UNDERRUN;
        }
        if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_RXORE)) {
            transerror = SD_DRV_RX_OVERRUN;
        }
        sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);
        sdio_interrupt_disable(SDIO, SDIO_INT_DTCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_DTEND |
                               SDIO_INT_TXURE | SDIO_INT_RXORE);
        sdio_trans_start_disable(SDIO);
        sdio_fifo_reset_enable(SDIO);
        sdio_fifo_reset_disable(SDIO);
        /* send CMD12 to abort transfer */
        transerror = sd_transfer_stop();
        sdio_flag_clear(SDIO, SDIO_FLAG_DTABORT);
        if(SD_DMA_MODE == sd_transmode) {
            sdio_idma_disable(SDIO);
        }
        return transerror;
    }

    if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_IDMAERR)) {
        sdio_interrupt_flag_clear(SDIO, SDIO_INT_FLAG_IDMAERR);
        transerror = SD_DRV_DMA_ERROR;
        sdio_interrupt_disable(SDIO, SDIO_INT_DTCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_DTEND |
                               SDIO_INT_TXURE | SDIO_INT_RXORE);
        sdio_trans_start_disable(SDIO);
        sdio_fifo_reset_enable(SDIO);
        sdio_fifo_reset_disable(SDIO);
        transerror = sd_transfer_stop();
        sdio_flag_clear(SDIO, SDIO_FLAG_DTABORT);
        sdio_idma_disable(SDIO);
        return transerror;
    }
    return transerror;
}

#if SD_USE_DMA && !defined(BSP_USING_EMMC)
/*!
    \brief      SDIO0 interrupt service routine (SD DMA mode)
    \note       Active only when SD_USE_DMA == 1 and BSP_USING_EMMC is not defined.
*/
void SDIO0_IRQHandler(void)
{
    rt_interrupt_enter();
    sd_isr_process();
    rt_interrupt_leave();
}
#endif /* SD_USE_DMA && !BSP_USING_EMMC */

/* -----------------------------------------------------------------------
 * Block Read  (CMD17 / CMD18, FIFO polling / DMA)
 * ----------------------------------------------------------------------- */

/*!
    \brief      read a single block from the specified sector
    \param[out] buf: pointer to receive buffer (must be 32-byte aligned for DMA)
    \param[in]  sector: sector address
    \retval     sd_drv_err_t
*/
static sd_drv_err_t sd_block_read(uint32_t *buf, uint32_t sector)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t count = 0U, *ptempbuff = buf;
    /* SDHC/SDXC: sector addressing; SDSC: byte addressing */
    uint32_t addr = (SD_HIGH_CAPACITY == sd0.card_type) ? sector : (sector * SD_SECTOR_SIZE);

    transerror = SD_DRV_OK;
    transend = 0U;
    stopcondition = 0U;

    /* clear all DSM configuration */
    sdio_data_config(SDIO, 0U, 0U, SDIO_DATABLOCKSIZE_1BYTE);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_dsm_disable(SDIO);
    sdio_idma_disable(SDIO);

    /* CMD16: SET_BLOCKLEN to 512 bytes (matches sdcard.c) */
    sdio_command_response_config(SDIO, SD_CMD_SET_BLOCKLEN, SD_SECTOR_SIZE, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_SET_BLOCKLEN);
    if(SD_DRV_OK != status) {
        return status;
    }

    if(SD_POLLING_MODE == sd_transmode) {
        /* configure SDIO data transmission */
        sdio_data_config(SDIO, SD_DATATIMEOUT, SD_SECTOR_SIZE, SDIO_DATABLOCKSIZE_512BYTES);
        sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOSDIO);
        sdio_trans_start_enable(SDIO);

        /* send CMD17(READ_SINGLE_BLOCK) */
        sdio_command_response_config(SDIO, SD_CMD_READ_SINGLE_BLOCK, addr, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_READ_SINGLE_BLOCK);
        if(SD_DRV_OK != status) {
            return status;
        }

        /* polling mode: read FIFO half-full (8 words) at a time */
        while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT | SDIO_FLAG_RXORE | SDIO_FLAG_DTBLKEND | SDIO_FLAG_DTEND)) {
            if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RFH)) {
                for(count = 0U; count < SD_FIFOHALF_WORDS; count++) {
                    *(ptempbuff + count) = sdio_data_read(SDIO);
                }
                ptempbuff += SD_FIFOHALF_WORDS;
            }
        }

        sdio_trans_start_disable(SDIO);

        if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR)) {
            status = SD_DRV_DATA_CRC_ERROR;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTCRCERR);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTTMOUT)) {
            status = SD_DRV_DATA_TIMEOUT;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTTMOUT);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RXORE)) {
            status = SD_DRV_RX_OVERRUN;
            sdio_flag_clear(SDIO, SDIO_FLAG_RXORE);
            return status;
        } else {
            /* if else end */
        }

        while((SET != sdio_flag_get(SDIO, SDIO_FLAG_RFE)) && (SET == sdio_flag_get(SDIO, SDIO_FLAG_DATSTA))) {
            *ptempbuff = sdio_data_read(SDIO);
            ++ptempbuff;
        }
        sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);
    } else if(SD_DMA_MODE == sd_transmode) {
        /* DMA mode */
        /* invalidate DCache for read buffer so CPU sees DMA-written data after transfer */
        sd_dcache_invalidate(buf, SD_SECTOR_SIZE);
        /* enable the SDIO corresponding interrupts and DMA function */
        sdio_interrupt_enable(SDIO, SDIO_INT_CCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_RXORE | SDIO_INT_DTEND);
        dma_config(buf, (uint32_t)(SD_SECTOR_SIZE >> 5));
        sdio_idma_enable(SDIO);
        /* configure SDIO data transmission */
        sdio_data_config(SDIO, SD_DATATIMEOUT, SD_SECTOR_SIZE, SDIO_DATABLOCKSIZE_512BYTES);
        sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOSDIO);
        sdio_trans_start_enable(SDIO);

        /* send CMD17(READ_SINGLE_BLOCK) */
        sdio_command_response_config(SDIO, SD_CMD_READ_SINGLE_BLOCK, addr, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_READ_SINGLE_BLOCK);
        if(SD_DRV_OK != status) {
            return status;
        }

        while((0U == transend) && (SD_DRV_OK == transerror)) {
        }
        if(SD_DRV_OK != transerror) {
            return transerror;
        }
    } else {
        status = SD_DRV_PARAM_ERROR;
    }
    return status;
}

/*!
    \brief      read multiple blocks from the specified sector
    \param[out] buf: pointer to receive buffer
    \param[in]  sector: starting sector address
    \param[in]  count: number of blocks to read
    \retval     sd_drv_err_t
*/
static sd_drv_err_t sd_multiblocks_read(uint32_t *buf, uint32_t sector, uint32_t count)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t wordcount = 0U, *ptempbuff = buf;
    uint32_t total_bytes = count * SD_SECTOR_SIZE;
    uint32_t addr = (SD_HIGH_CAPACITY == sd0.card_type) ? sector : (sector * SD_SECTOR_SIZE);

    transerror = SD_DRV_OK;
    transend = 0U;
    stopcondition = 0U;

    /* clear all DSM configuration */
    sdio_data_config(SDIO, 0U, 0U, SDIO_DATABLOCKSIZE_1BYTE);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_dsm_disable(SDIO);
    sdio_idma_disable(SDIO);

    /* CMD16: SET_BLOCKLEN to 512 bytes (matches sdcard.c) */
    sdio_command_response_config(SDIO, SD_CMD_SET_BLOCKLEN, SD_SECTOR_SIZE, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_SET_BLOCKLEN);
    if(SD_DRV_OK != status) {
        return status;
    }

    if(SD_POLLING_MODE == sd_transmode) {
        /* configure SDIO data transmission */
        sdio_data_config(SDIO, SD_DATATIMEOUT, total_bytes, SDIO_DATABLOCKSIZE_512BYTES);
        sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOSDIO);
        sdio_trans_start_enable(SDIO);

        /* send CMD18(READ_MULTIPLE_BLOCK) */
        sdio_command_response_config(SDIO, SD_CMD_READ_MULTIPLE_BLOCK, addr, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_READ_MULTIPLE_BLOCK);
        if(SD_DRV_OK != status) {
            return status;
        }

        /* polling mode */
        while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT | SDIO_FLAG_RXORE | SDIO_FLAG_DTBLKEND | SDIO_FLAG_DTEND)) {
            if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RFH)) {
                for(wordcount = 0U; wordcount < SD_FIFOHALF_WORDS; wordcount++) {
                    *(ptempbuff + wordcount) = sdio_data_read(SDIO);
                }
                ptempbuff += SD_FIFOHALF_WORDS;
            }
        }

        if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR)) {
            status = SD_DRV_DATA_CRC_ERROR;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTCRCERR);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTTMOUT)) {
            status = SD_DRV_DATA_TIMEOUT;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTTMOUT);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RXORE)) {
            status = SD_DRV_RX_OVERRUN;
            sdio_flag_clear(SDIO, SDIO_FLAG_RXORE);
            return status;
        } else {
            /* if else end */
        }

        while((SET != sdio_flag_get(SDIO, SDIO_FLAG_RFE)) && (SET == sdio_flag_get(SDIO, SDIO_FLAG_DATSTA))) {
            *ptempbuff = sdio_data_read(SDIO);
            ++ptempbuff;
        }

        sdio_trans_start_disable(SDIO);

        if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTEND)) {
            /* send CMD12(STOP_TRANSMISSION) to stop multiblock transfer */
            sdio_command_response_config(SDIO, SD_CMD_STOP_TRANSMISSION, (uint32_t)0x0, SDIO_RESPONSETYPE_SHORT);
            sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
            sdio_csm_enable(SDIO);
            status = r1_error_check(SD_CMD_STOP_TRANSMISSION);
            if(SD_DRV_OK != status) {
                return status;
            }
        }
        sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);
    } else if(SD_DMA_MODE == sd_transmode) {
        /* DMA mode: ISR will send CMD12 after DTEND */
        stopcondition = 1U;
        /* invalidate DCache for read buffer so CPU sees DMA-written data after transfer */
        sd_dcache_invalidate(buf, total_bytes);
        /* enable the SDIO corresponding interrupts and DMA function */
        sdio_interrupt_enable(SDIO, SDIO_INT_CCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_RXORE | SDIO_INT_DTEND);
        dma_config(buf, (uint32_t)(total_bytes >> 5));
        sdio_idma_enable(SDIO);
        /* configure SDIO data transmission */
        sdio_data_config(SDIO, SD_DATATIMEOUT, total_bytes, SDIO_DATABLOCKSIZE_512BYTES);
        sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOSDIO);
        sdio_trans_start_enable(SDIO);

        /* send CMD18(READ_MULTIPLE_BLOCK) */
        sdio_command_response_config(SDIO, SD_CMD_READ_MULTIPLE_BLOCK, addr, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_READ_MULTIPLE_BLOCK);
        if(SD_DRV_OK != status) {
            return status;
        }

        while((0U == transend) && (SD_DRV_OK == transerror)) {
        }
        if(SD_DRV_OK != transerror) {
            return transerror;
        }
    } else {
        status = SD_DRV_PARAM_ERROR;
    }
    return status;
}

/* -----------------------------------------------------------------------
 * Block Write (CMD24 / CMD25 + CMD12, FIFO polling / DMA)
 * ----------------------------------------------------------------------- */

/*!
    \brief      write a single block to the specified sector
    \param[in]  buf: pointer to data buffer
    \param[in]  sector: sector address
    \retval     sd_drv_err_t
*/
static sd_drv_err_t sd_block_write(uint32_t *buf, uint32_t sector)
{
    sd_drv_err_t status = SD_DRV_OK;
    __IO uint32_t count = 0U, *ptempbuff = buf;
    uint32_t transbytes = 0U, restwords = 0U;
    uint32_t addr = (SD_HIGH_CAPACITY == sd0.card_type) ? sector : (sector * SD_SECTOR_SIZE);

    transerror = SD_DRV_OK;
    transend = 0U;
    stopcondition = 0U;

    /* clear all DSM configuration */
    sdio_data_config(SDIO, 0U, 0U, SDIO_DATABLOCKSIZE_1BYTE);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_dsm_disable(SDIO);
    sdio_idma_disable(SDIO);

    /* CMD16: SET_BLOCKLEN to 512 bytes (matches sdcard.c) */
    sdio_command_response_config(SDIO, SD_CMD_SET_BLOCKLEN, SD_SECTOR_SIZE, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_SET_BLOCKLEN);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* poll READY_FOR_DATA before writing */
    status = wait_ready();
    if(SD_DRV_OK != status) {
        return status;
    }

    /* configure the SDIO data transmission */
    sdio_data_config(SDIO, SD_DATATIMEOUT, SD_SECTOR_SIZE, SDIO_DATABLOCKSIZE_512BYTES);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_trans_start_enable(SDIO);

    if(SD_POLLING_MODE == sd_transmode) {
        /* send CMD24(WRITE_BLOCK) */
        sdio_command_response_config(SDIO, SD_CMD_WRITE_BLOCK, addr, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_WRITE_BLOCK);
        if(SD_DRV_OK != status) {
            return status;
        }

        /* polling mode: write FIFO half-empty (8 words) at a time */
        while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT | SDIO_FLAG_TXURE | SDIO_FLAG_DTBLKEND | SDIO_FLAG_DTEND)) {
            if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_TFH)) {
                if((SD_SECTOR_SIZE - transbytes) < SD_FIFOHALF_BYTES) {
                    restwords = (SD_SECTOR_SIZE - transbytes) / 4U +
                                (((SD_SECTOR_SIZE - transbytes) % 4U == 0U) ? 0U : 1U);
                    for(count = 0U; count < restwords; count++) {
                        sdio_data_write(SDIO, *ptempbuff);
                        ++ptempbuff;
                        transbytes += 4U;
                    }
                } else {
                    for(count = 0U; count < SD_FIFOHALF_WORDS; count++) {
                        sdio_data_write(SDIO, *(ptempbuff + count));
                    }
                    ptempbuff += SD_FIFOHALF_WORDS;
                    transbytes += SD_FIFOHALF_BYTES;
                }
            }
        }

        sdio_trans_start_disable(SDIO);

        if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR)) {
            status = SD_DRV_DATA_CRC_ERROR;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTCRCERR);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTTMOUT)) {
            status = SD_DRV_DATA_TIMEOUT;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTTMOUT);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_TXURE)) {
            status = SD_DRV_TX_UNDERRUN;
            sdio_flag_clear(SDIO, SDIO_FLAG_TXURE);
            return status;
        } else {
            /* if else end */
        }
    } else if(SD_DMA_MODE == sd_transmode) {
        /* DMA mode */
        /* clean DCache so DMA reads the latest CPU-written data from RAM */
        sd_dcache_clean(buf, SD_SECTOR_SIZE);
        /* enable the SDIO corresponding interrupts and DMA function */
        sdio_interrupt_enable(SDIO, SDIO_INT_DTCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_TXURE | SDIO_INT_DTEND);
        dma_config(buf, (uint32_t)(SD_SECTOR_SIZE >> 5));
        sdio_idma_enable(SDIO);

        /* send CMD24(WRITE_BLOCK) */
        sdio_command_response_config(SDIO, SD_CMD_WRITE_BLOCK, addr, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_WRITE_BLOCK);
        if(SD_DRV_OK != status) {
            return status;
        }

        while((0U == transend) && (SD_DRV_OK == transerror)) {
        }
        if(SD_DRV_OK != transerror) {
            return transerror;
        }
    } else {
        return SD_DRV_PARAM_ERROR;
    }
    sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);

    /* wait for card to return to transfer state */
    return wait_card_ready();
}


/*!
    \brief      write multiple blocks to the specified sector
    \param[in]  buf: pointer to data buffer
    \param[in]  sector: starting sector address
    \param[in]  count: number of blocks to write
    \retval     sd_drv_err_t
*/
static sd_drv_err_t sd_multiblocks_write(uint32_t *buf, uint32_t sector, uint32_t count)
{
    sd_drv_err_t status = SD_DRV_OK;
    uint32_t wordcount = 0U, *ptempbuff = buf;
    uint32_t total_bytes = count * SD_SECTOR_SIZE;
    uint32_t transbytes = 0U, restwords = 0U;
    uint32_t addr = (SD_HIGH_CAPACITY == sd0.card_type) ? sector : (sector * SD_SECTOR_SIZE);

    transerror = SD_DRV_OK;
    transend = 0U;
    stopcondition = 0U;

    /* clear all DSM configuration */
    sdio_data_config(SDIO, 0U, 0U, SDIO_DATABLOCKSIZE_1BYTE);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_dsm_disable(SDIO);
    sdio_idma_disable(SDIO);

    /* CMD16: SET_BLOCKLEN to 512 bytes (matches sdcard.c) */
    sdio_command_response_config(SDIO, SD_CMD_SET_BLOCKLEN, SD_SECTOR_SIZE, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_SET_BLOCKLEN);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* poll READY_FOR_DATA before writing */
    status = wait_ready();
    if(SD_DRV_OK != status) {
        return status;
    }

    /* CMD55 + ACMD23(SET_WR_BLK_ERASE_COUNT): notify card to pre-erase blocks for faster write */
    sdio_command_response_config(SDIO, SD_CMD_APP_CMD, (uint32_t)sd0.rca << SD_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_CMD_APP_CMD);
    if(SD_DRV_OK != status) {
        return status;
    }
    sdio_command_response_config(SDIO, SD_APPCMD_SET_WR_BLK_ERASE_COUNT, count, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    status = r1_error_check(SD_APPCMD_SET_WR_BLK_ERASE_COUNT);
    if(SD_DRV_OK != status) {
        return status;
    }

    /* configure the SDIO data transmission */
    sdio_data_config(SDIO, SD_DATATIMEOUT, total_bytes, SDIO_DATABLOCKSIZE_512BYTES);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_trans_start_enable(SDIO);

    if(SD_POLLING_MODE == sd_transmode) {
        /* send CMD25(WRITE_MULTIPLE_BLOCK) */
        sdio_command_response_config(SDIO, SD_CMD_WRITE_MULTIPLE_BLOCK, addr, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_WRITE_MULTIPLE_BLOCK);
        if(SD_DRV_OK != status) {
            return status;
        }

        /* polling mode: write FIFO half-empty (8 words) at a time */
        while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT | SDIO_FLAG_TXURE | SDIO_FLAG_DTBLKEND | SDIO_FLAG_DTEND)) {
            if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_TFH)) {
                if((total_bytes - transbytes) < SD_FIFOHALF_BYTES) {
                    restwords = (total_bytes - transbytes) / 4U +
                                (((total_bytes - transbytes) % 4U == 0U) ? 0U : 1U);
                    for(wordcount = 0U; wordcount < restwords; wordcount++) {
                        sdio_data_write(SDIO, *ptempbuff);
                        ++ptempbuff;
                        transbytes += 4U;
                    }
                } else {
                    for(wordcount = 0U; wordcount < SD_FIFOHALF_WORDS; wordcount++) {
                        sdio_data_write(SDIO, *(ptempbuff + wordcount));
                    }
                    ptempbuff += SD_FIFOHALF_WORDS;
                    transbytes += SD_FIFOHALF_BYTES;
                }
            }
        }

        sdio_trans_start_disable(SDIO);

        if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR)) {
            status = SD_DRV_DATA_CRC_ERROR;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTCRCERR);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTTMOUT)) {
            status = SD_DRV_DATA_TIMEOUT;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTTMOUT);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_TXURE)) {
            status = SD_DRV_TX_UNDERRUN;
            sdio_flag_clear(SDIO, SDIO_FLAG_TXURE);
            return status;
        } else {
            /* if else end */
        }

        /* send CMD12(STOP_TRANSMISSION) to end multiblock write */
        sdio_command_response_config(SDIO, SD_CMD_STOP_TRANSMISSION, (uint32_t)0x0, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_STOP_TRANSMISSION);
        if(SD_DRV_OK != status) {
            return status;
        }
    } else if(SD_DMA_MODE == sd_transmode) {
        /* DMA mode: ISR will send CMD12 after DTEND */
        stopcondition = 1U;
        /* clean DCache so DMA reads the latest CPU-written data from RAM */
        sd_dcache_clean(buf, total_bytes);
        /* enable the SDIO corresponding interrupts and DMA function */
        sdio_interrupt_enable(SDIO, SDIO_INT_DTCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_TXURE | SDIO_INT_DTEND);
        dma_config(buf, (uint32_t)(total_bytes >> 5));
        sdio_idma_enable(SDIO);

        /* send CMD25(WRITE_MULTIPLE_BLOCK) */
        sdio_command_response_config(SDIO, SD_CMD_WRITE_MULTIPLE_BLOCK, addr, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        status = r1_error_check(SD_CMD_WRITE_MULTIPLE_BLOCK);
        if(SD_DRV_OK != status) {
            return status;
        }

        while((0U == transend) && (SD_DRV_OK == transerror)) {
        }
        if(SD_DRV_OK != transerror) {
            return transerror;
        }
    } else {
        return SD_DRV_PARAM_ERROR;
    }
    sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);

    /* wait for card to return to transfer state */
    return wait_card_ready();
}

/* -----------------------------------------------------------------------
 * RT-Thread block device callbacks
 * ----------------------------------------------------------------------- */
static rt_err_t rt_sdcard_init(rt_device_t dev)
{
    sd_drv_err_t err = SD_DRV_OK;
    rt_err_t     ret = RT_EOK;
    uint16_t     retry = 5U;

    ret = rt_mutex_init(&sd0.sd_lock, "sd_lock", RT_IPC_FLAG_FIFO);
    if(RT_EOK != ret) {
        LOG_E("sd mutex init failed");
        return ret;
    }

    do {
        /* configure the RCU */
        err = rcu_config();
        if(SD_DRV_OK != err) {
            LOG_W("rcu_config fail:%d", err);
            continue;
        }
        /* configure the SDIO GPIO and deinitialize the SDIO */
        sdio_gpio_config();
        sdio_deinit(SDIO);

        /* configure the clock and working voltage; detect card type */
        err = sd_power_on();
        if(SD_DRV_OK != err) {
            LOG_W("power_on fail:%d", err);
            continue;
        }

        /* get CID, RCA from card, and CSD */
        err = sd_card_init();
        if(SD_DRV_OK != err) {
            LOG_W("card_init fail:%d", err);
            continue;
        }

        /* reconfigure SDIO peripheral (1-bit, init clock) before select */
        sdio_clock_config(SDIO, SDIO_SDIOCLKEDGE_RISING, SDIO_CLOCKPWRSAVE_DISABLE, SD_CLK_DIV_INIT);
        sdio_bus_mode_set(SDIO, SDIO_BUSMODE_1BIT);
        sdio_hardware_clock_disable(SDIO);

        /* select the card (CMD7) */
        err = sd_card_select();
        if(SD_DRV_OK != err) {
            LOG_W("select fail:%d", err);
            continue;
        }

        /* parse sector count from CSD */
        sd_sector_count_get();

        /* switch bus width and clock speed */
        err = sd_bus_mode_config(SD_CONF_BUSMODE, SD_CONF_SPEED);
        if(SD_DRV_OK != err) {
            LOG_W("bus_mode_config fail:%d", err);
            continue;
        }

        /* set data transfer mode */
        sd_transfer_mode_config(SD_CONF_DTMODE);

    } while((SD_DRV_OK != err) && (--retry > 0U));

    if(0U == retry) {
        LOG_E("SD card init failed!");
        return -RT_EIO;
    }

    LOG_I("SD card init OK  type:%s  sectors:%u (%u MB)",
          (SD_HIGH_CAPACITY == sd0.card_type ? "SDHC/SDXC" : "SDSC"),
          sd0.sector_count, sd0.sector_count / 2048U);
    LOG_I("SD bus:%s  speed:%s  transmode:%s",
          (SD_CONF_BUSMODE == SDIO_BUSMODE_4BIT ? "4-bit" : "1-bit"),
          (SD_CONF_SPEED == SD_SPEED_HIGH    ? "High(33MHz)"    :
           SD_CONF_SPEED == SD_SPEED_DEFAULT ? "Default(20MHz)" :
           SD_CONF_SPEED == SD_SPEED_SDR25   ? "SDR25"          :
           SD_CONF_SPEED == SD_SPEED_SDR50   ? "SDR50"          :
           SD_CONF_SPEED == SD_SPEED_SDR104  ? "SDR104"         :
           SD_CONF_SPEED == SD_SPEED_DDR50   ? "DDR50"          : "Unknown"),
          (SD_USE_DMA ? "DMA(IDMA)" : "Polling(FIFO)"));
    return RT_EOK;
}

static rt_err_t rt_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_sdcard_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_sdcard_read(rt_device_t dev, rt_off_t sector,
                                  void *buffer, rt_size_t count)
{
    sd_drv_err_t  err = SD_DRV_OK;
    gd32_sd_t    *sd  = (gd32_sd_t *)dev->user_data;
    rt_size_t     i   = 0U;

    if(NULL == buffer) {
        return 0;
    }

    rt_mutex_take(&sd->sd_lock, RT_WAITING_FOREVER);

    if(((uint32_t)buffer & 0x1FU) != 0U) {
        /* buffer not 32-byte aligned — use aligned bounce buffer sector by sector */
        uint8_t *dst = (uint8_t *)buffer;
        for(i = 0U; i < count; i++) {
            err = sd_block_read(sd_dma_buf, (uint32_t)(sector + (rt_off_t)i));
            if(SD_DRV_OK != err) {
                LOG_E("read fail sector:%d err:%d", (int)(sector + (rt_off_t)i), err);
                rt_mutex_release(&sd->sd_lock);
                return 0;
            }
            rt_memcpy(dst, sd_dma_buf, SD_SECTOR_SIZE);
            dst += SD_SECTOR_SIZE;
        }
    } else {
        if(1U == count) {
            err = sd_block_read((uint32_t *)buffer, (uint32_t)sector);
        } else {
            err = sd_multiblocks_read((uint32_t *)buffer, (uint32_t)sector, (uint32_t)count);
        }
        if(SD_DRV_OK != err) {
            LOG_E("read fail sector:%d count:%d err:%d", (int)sector, (int)count, err);
            rt_mutex_release(&sd->sd_lock);
            return 0;
        }
    }

    rt_mutex_release(&sd->sd_lock);
    return (rt_ssize_t)count;
}

static rt_ssize_t rt_sdcard_write(rt_device_t dev, rt_off_t sector,
                                   const void *buffer, rt_size_t count)
{
    sd_drv_err_t  err = SD_DRV_OK;
    gd32_sd_t    *sd  = (gd32_sd_t *)dev->user_data;
    rt_size_t     i   = 0U;

    if(NULL == buffer) {
        return 0;
    }

    rt_mutex_take(&sd->sd_lock, RT_WAITING_FOREVER);

    if(((uint32_t)buffer & 0x1FU) != 0U) {
        /* buffer not 32-byte aligned — use aligned bounce buffer sector by sector */
        const uint8_t *src = (const uint8_t *)buffer;
        for(i = 0U; i < count; i++) {
            rt_memcpy(sd_dma_buf, src, SD_SECTOR_SIZE);
            err = sd_block_write(sd_dma_buf, (uint32_t)(sector + (rt_off_t)i));
            if(SD_DRV_OK != err) {
                LOG_E("write fail sector:%d err:%d", (int)(sector + (rt_off_t)i), err);
                rt_mutex_release(&sd->sd_lock);
                return 0;
            }
            src += SD_SECTOR_SIZE;
        }
    } else {
        if(1U == count) {
            err = sd_block_write((uint32_t *)buffer, (uint32_t)sector);
        } else {
            err = sd_multiblocks_write((uint32_t *)buffer, (uint32_t)sector, (uint32_t)count);
        }
        if(SD_DRV_OK != err) {
            LOG_E("write fail sector:%d count:%d err:%d", (int)sector, (int)count, err);
            rt_mutex_release(&sd->sd_lock);
            return 0;
        }
    }

    rt_mutex_release(&sd->sd_lock);
    return (rt_ssize_t)count;
}

static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
    gd32_sd_t *sd = (gd32_sd_t *)dev->user_data;

    if(RT_DEVICE_CTRL_BLK_GETGEOME == cmd) {
        struct rt_device_blk_geometry *geo = (struct rt_device_blk_geometry *)args;
        if(NULL == geo) {
            return -RT_ERROR;
        }
        geo->bytes_per_sector = SD_SECTOR_SIZE;
        geo->block_size       = SD_SECTOR_SIZE;
        geo->sector_count     = sd->sector_count;
    }
    return RT_EOK;
}

/* -----------------------------------------------------------------------
 * Driver registration
 * ----------------------------------------------------------------------- */
/*!
    \brief      initialize and register the SD card block device with RT-Thread
    \param[in]  none
    \param[out] none
    \retval     RT_EOK on success, negative value on failure
*/
int rt_hw_sdcard_init(void)
{
    sd0.sd_device.type      = RT_Device_Class_Block;
    sd0.sd_device.init      = rt_sdcard_init;
    sd0.sd_device.open      = rt_sdcard_open;
    sd0.sd_device.close     = rt_sdcard_close;
    sd0.sd_device.read      = rt_sdcard_read;
    sd0.sd_device.write     = rt_sdcard_write;
    sd0.sd_device.control   = rt_sdcard_control;
    sd0.sd_device.user_data = &sd0;

    rt_device_register(&sd0.sd_device, sd0.device_name,
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_sdcard_init);

#endif /* BSP_USING_SD */
