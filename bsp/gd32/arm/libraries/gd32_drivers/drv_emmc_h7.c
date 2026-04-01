/*!
    \file    drv_emmc_h7.c
    \brief   eMMC block device driver for GD32H7xx (RT-Thread adaptation)

             Low-level SDIO operations are ported from the official GD32H7xx
             eMMC firmware library (emmc.c) with minimal style changes.
             RT-Thread device callbacks wrap those operations.

    Design notes:
      - Uses SDIO0 (aliased as SDIO) with IDMA, polling on SDIO status flags.
        No SDIO0 interrupt is enabled by this driver.  The SD card driver (drv_sdio_h7.c)
        uses SDIO0_IRQHandler; therefore the SD card and eMMC must NOT be used at the
        same time, as the ISR could clear flags this driver is polling for.
      - DCache is managed explicitly (Cortex-M7):
          Write path: SCB_CleanDCache before IDMA
          Read  path: SCB_InvalidateDCache after IDMA
      - eMMC uses sector addressing (CMD17/18/24/25 address = sector number).
      - Registers "emmc0" as RT_Device_Class_Block device.
*/

/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>

#ifdef BSP_USING_EMMC

#include "drv_emmc_h7.h"

/* #define DRV_DEBUG */
#define LOG_TAG  "drv.emmc"
#include "drv_log.h"

/* SDIO peripheral alias — matches official GD32 eMMC driver (emmc.c) style */
#define SDIO  SDIO0

/* card status of R1 definitions */
#define EMMC_R1_OUT_OF_RANGE              BIT(31)                    /* command's argument was out of the allowed range */
#define EMMC_R1_ADDRESS_ERROR             BIT(30)                    /* misaligned address which did not match the block length */
#define EMMC_R1_BLOCK_LEN_ERROR           BIT(29)                    /* transferred block length is not allowed */
#define EMMC_R1_ERASE_SEQ_ERROR           BIT(28)                    /* an error in the sequence of erase commands occurred */
#define EMMC_R1_ERASE_PARAM               BIT(27)                    /* an invalid selection of write-blocks for erase occurred */
#define EMMC_R1_WP_VIOLATION              BIT(26)                    /* the host attempts to write to a protected block */
#define EMMC_R1_CARD_IS_LOCKED            BIT(25)                    /* the card is locked by the host */
#define EMMC_R1_LOCK_UNLOCK_FAILED        BIT(24)                    /* a sequence or password error has been detected */
#define EMMC_R1_COM_CRC_ERROR             BIT(23)                    /* CRC check of the previous command failed */
#define EMMC_R1_ILLEGAL_COMMAND           BIT(22)                    /* command not legal for the card state */
#define EMMC_R1_CARD_ECC_FAILED           BIT(21)                    /* card internal ECC was applied but failed */
#define EMMC_R1_CC_ERROR                  BIT(20)                    /* internal card controller error */
#define EMMC_R1_GENERAL_UNKNOWN_ERROR     BIT(19)                    /* a general or an unknown error occurred */
#define EMMC_R1_CSD_OVERWRITE             BIT(16)                    /* read only section of the CSD does not match */
#define EMMC_R1_WP_ERASE_SKIP             BIT(15)                    /* partial address space was erased */
#define EMMC_R1_CARD_ECC_DISABLED         BIT(14)                    /* command executed without using internal ECC */
#define EMMC_R1_ERASE_RESET               BIT(13)                    /* an erase sequence was cleared before executing */
#define EMMC_R1_READY_FOR_DATA            BIT(8)                     /* correspond to buffer empty signaling on the bus */
#define EMMC_R1_AKE_SEQ_ERROR             BIT(3)                     /* error in the sequence of the authentication process */
#define EMMC_R1_ERROR_BITS                ((uint32_t)0xFDF9E008U)    /* all the R1 error bits */

/* card state */
#define EMMC_CARDSTATE_IDLE               ((uint8_t)0x00)            /* eMMC is in idle state */
#define EMMC_CARDSTATE_READY              ((uint8_t)0x01)            /* eMMC is in ready state */
#define EMMC_CARDSTATE_IDENTIFICATION     ((uint8_t)0x02)            /* eMMC is in identification state */
#define EMMC_CARDSTATE_STANDBY            ((uint8_t)0x03)            /* eMMC is in standby state */
#define EMMC_CARDSTATE_TRANSFER           ((uint8_t)0x04)            /* eMMC is in transfer state */
#define EMMC_CARDSTATE_DATA               ((uint8_t)0x05)            /* eMMC is in data sending state */
#define EMMC_CARDSTATE_RECEIVING          ((uint8_t)0x06)            /* eMMC is in receiving state */
#define EMMC_CARDSTATE_PROGRAMMING        ((uint8_t)0x07)            /* eMMC is in programming state */
#define EMMC_CARDSTATE_DISCONNECT         ((uint8_t)0x08)            /* eMMC is in disconnect state */

/* eMMC command indices */
#define EMMC_CMD_GO_IDLE_STATE            ((uint8_t)0)
#define EMMC_CMD_SEND_OP_COND             ((uint8_t)1)
#define EMMC_CMD_ALL_SEND_CID             ((uint8_t)2)
#define EMMC_CMD_SEND_RELATIVE_ADDR       ((uint8_t)3)
#define EMMC_CMD_SWITCH_FUNC              ((uint8_t)6)
#define EMMC_CMD_SELECT_DESELECT_CARD     ((uint8_t)7)
#define EMMC_CMD_SEND_EXT_CSD             ((uint8_t)8)
#define EMMC_CMD_SEND_CSD                 ((uint8_t)9)
#define EMMC_CMD_STOP_TRANSMISSION        ((uint8_t)12)
#define EMMC_CMD_SEND_STATUS              ((uint8_t)13)
#define EMMC_CMD_READ_SINGLE_BLOCK        ((uint8_t)17)
#define EMMC_CMD_READ_MULTIPLE_BLOCK      ((uint8_t)18)
#define EMMC_CMD_SET_BLOCK_COUNT          ((uint8_t)23)
#define EMMC_CMD_WRITE_BLOCK              ((uint8_t)24)
#define EMMC_CMD_WRITE_MULTIPLE_BLOCK     ((uint8_t)25)

#define EMMC_DATATIMEOUT                  ((uint32_t)0xFFFFFFFFU)    /* DSM data timeout */
#define EMMC_ALLZERO                      ((uint32_t)0x00000000U)    /* all zero */
#define EMMC_RCA_SHIFT                    ((uint8_t)0x10U)           /* RCA shift bits */
#define EMMC_SECTOR_SIZE                  ((uint32_t)512U)           /* bytes per sector */

#define SDIO_MASK_INTC_FLAGS              ((uint32_t)0x1FE00FFFU)    /* mask flags of SDIO_INTC */
#define SDIO_MASK_CMD_FLAGS               ((uint32_t)0x002000C5U)    /* mask flags of CMD FLAGS */
#define SDIO_MASK_DATA_FLAGS              ((uint32_t)0x18000F3AU)    /* mask flags of DATA FLAGS */

#define EMMC_FIFOHALF_WORDS               ((uint32_t)0x00000008U)    /* words of FIFO half full/empty */
#define EMMC_FIFOHALF_BYTES               ((uint32_t)0x00000020U)    /* bytes of FIFO half full/empty */

/* EXT_CSD SEC_CNT byte offsets [215:212] (little-endian uint32) */
#define EXT_CSD_SEC_CNT_B0                212U                       /* LSB */
#define EXT_CSD_SEC_CNT_B1                213U
#define EXT_CSD_SEC_CNT_B2                214U
#define EXT_CSD_SEC_CNT_B3                215U                       /* MSB */

/* Fixed RCA assigned by host to eMMC */
#define EMMC_DEFAULT_RCA                  ((uint16_t)1U)

/* DCache line size for Cortex-M7 */
#define DCACHE_LINE_SIZE                  32U
#define ALIGN_DOWN_32(x)                  ((uint32_t)(x) & ~(DCACHE_LINE_SIZE - 1U))
#define ALIGN_UP_32(x, base)              (ALIGN_DOWN_32((uint32_t)(base)) + \
                                           (((uint32_t)(x) - ALIGN_DOWN_32((uint32_t)(base)) + \
                                             DCACHE_LINE_SIZE - 1U) & ~(DCACHE_LINE_SIZE - 1U)))

/* -----------------------------------------------------------------------
 * Driver private state
 * ----------------------------------------------------------------------- */
typedef struct {
    struct rt_device  emmc_device;
    struct rt_mutex   emmc_lock;
    char             *device_name;
    uint16_t          rca;           /* relative card address (host-assigned) */
    uint32_t          sector_count;  /* total 512-byte sectors from EXT_CSD   */
    uint32_t          csd[4];
    uint32_t          cid[4];
} gd32_emmc_t;

static gd32_emmc_t emmc0 = {
    .device_name  = "emmc0",
    .rca          = EMMC_DEFAULT_RCA,
    .sector_count = 0U,
};

/* transfer mode and DMA state (cf. emmc.c) */
static uint32_t             transmode     = EMMC_TRANSMODE;  /* EMMC_POLLING_MODE or EMMC_DMA_MODE */
static uint32_t             stopcondition = 0U;              /* 1: ISR shall send CMD12 after multi-block read */
static __IO emmc_drv_err_t  transerror    = EMMC_DRV_OK;     /* error result set by ISR in DMA mode */
static __IO uint32_t        transend      = 0U;              /* set to 1 by ISR when transfer completes */

/* 32-byte aligned static buffers */
/* Used when caller's buffer is not 32-byte aligned (DCache requirement) */
static uint32_t __attribute__((aligned(32))) emmc_dma_buf[EMMC_SECTOR_SIZE / sizeof(uint32_t)];
/* EXT_CSD: 512 bytes, must be 32-byte aligned for IDMA */
static uint8_t  __attribute__((aligned(32))) emmc_ext_csd[512];

/* -----------------------------------------------------------------------
 * Forward declarations (internal functions — mirrors emmc.c style)
 * ----------------------------------------------------------------------- */
static emmc_drv_err_t cmdsent_error_check(void);
static emmc_drv_err_t r1_error_check(uint8_t cmdindex);
static emmc_drv_err_t r1_error_type_check(uint32_t resp);
static emmc_drv_err_t r2_error_check(void);
static emmc_drv_err_t r3_error_check(void);
static emmc_drv_err_t emmc_card_state_get(uint8_t *pcardstate);
rt_weak void          sdio_gpio_config(void);
static emmc_drv_err_t rcu_config(void);
static void           dma_config(uint32_t *buf, uint32_t bufsize);

/* -----------------------------------------------------------------------
 * DCache helpers (Cortex-M7 SCB)
 * ----------------------------------------------------------------------- */
static void emmc_dcache_clean(void *addr, uint32_t size)
{
    uint32_t aligned_addr = ALIGN_DOWN_32((uint32_t)addr);
    uint32_t aligned_size = ALIGN_UP_32(size + ((uint32_t)addr - aligned_addr), 0U);
    SCB_CleanDCache_by_Addr((uint32_t *)aligned_addr, (int32_t)aligned_size);
}

static void emmc_dcache_invalidate(void *addr, uint32_t size)
{
    uint32_t aligned_addr = ALIGN_DOWN_32((uint32_t)addr);
    uint32_t aligned_size = ALIGN_UP_32(size + ((uint32_t)addr - aligned_addr), 0U);
    SCB_InvalidateDCache_by_Addr((uint32_t *)aligned_addr, (int32_t)aligned_size);
}

/* -----------------------------------------------------------------------
 * GPIO / RCU / IDMA hardware configuration
 * ----------------------------------------------------------------------- */
/*!
    \brief      configure the GPIO of SDIO interface
    \param[in]  none
    \param[out] none
    \retval     none
*/
rt_weak void sdio_gpio_config(void)
{
    /*
     * 8-bit mode: above + D4(PB8) D5(PB9) D6(PC6) D7(PC7)
     */
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);

    /* configure the SDIO_DAT0(PC8), SDIO_DAT1(PC9), SDIO_DAT2(PC10), SDIO_DAT3(PC11), SDIO_CLK(PC12) and SDIO_CMD(PD2) */
    gpio_af_set(GPIOC, GPIO_AF_12, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 );
    gpio_af_set(GPIOD, GPIO_AF_12, GPIO_PIN_2);

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_12);

    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_2);

#if (EMMC_BUSWIDTH == 8)
    /* D4-D5: PB8-PB9 */
    gpio_af_set(GPIOB, GPIO_AF_12, GPIO_PIN_8 | GPIO_PIN_9);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8 | GPIO_PIN_9);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_8 | GPIO_PIN_9);
    /* D6-D7: PC6-PC7 */
    gpio_af_set(GPIOC, GPIO_AF_12, GPIO_PIN_6 | GPIO_PIN_7);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6 | GPIO_PIN_7);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_6 | GPIO_PIN_7);
#endif

}
/*!
    \brief      configure the RCU of SDIO (PLL1R = 200MHz)
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t rcu_config(void)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
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
        status = EMMC_DRV_ERROR;
        return status;
    }

    rcu_sdio_clock_config(IDX_SDIO0, RCU_SDIO0SRC_PLL1R);
    rcu_periph_clock_enable(RCU_SDIO0);

#if EMMC_USE_DMA
    /* enable SDIO0 interrupt for DMA transfer completion / error handling */
    nvic_irq_enable(SDIO0_IRQn, 2U, 0U);
#endif

    return status;
}

/*!
    \brief      configure the DMA (IDMA) for SDIO request
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
    \brief      check if the command sent error occurs
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t cmdsent_error_check(void)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t timeout = 100000U;

    /* check command sent flag */
    while((RESET == sdio_flag_get(SDIO, SDIO_FLAG_CMDSEND)) && (timeout > 0U)) {
        --timeout;
    }
    /* command response is timeout */
    if(0U == timeout) {
        status = EMMC_DRV_CMD_TIMEOUT;
        return status;
    }
    /* if the command is sent, clear the CMD_FLAGS flags */
    sdio_flag_clear(SDIO, SDIO_MASK_CMD_FLAGS);
    return status;
}

/*!
    \brief      check if error type for R1 response
    \param[in]  resp: content of response
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t r1_error_type_check(uint32_t resp)
{
    emmc_drv_err_t status = EMMC_DRV_ERROR;

    /* check which error occurs */
    if(resp & EMMC_R1_CARD_IS_LOCKED) {
        status = EMMC_DRV_LOCK_FAILED;
    } else if(resp & EMMC_R1_COM_CRC_ERROR) {
        status = EMMC_DRV_CMD_CRC_ERROR;
    } else if(resp & EMMC_R1_ILLEGAL_COMMAND) {
        status = EMMC_DRV_ILLEGAL_CMD;
    } else if(resp & EMMC_R1_LOCK_UNLOCK_FAILED) {
        status = EMMC_DRV_LOCK_FAILED;
    } else {
        /* if else end */
    }
    return status;
}

/*!
    \brief      check if error occurs for R1 response
    \param[in]  cmdindex: the index of command
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t r1_error_check(uint8_t cmdindex)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t reg_status = 0U, resp_r1 = 0U;

    /* store the content of SDIO_STAT */
    reg_status = SDIO_STAT(SDIO);
    while(!(reg_status & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDTMOUT | SDIO_FLAG_CMDRECV))) {
        reg_status = SDIO_STAT(SDIO);
    }
    /* check whether an error or timeout occurs or command response received */
    if(reg_status & SDIO_FLAG_CCRCERR) {
        status = EMMC_DRV_CMD_CRC_ERROR;
        sdio_flag_clear(SDIO, SDIO_FLAG_CCRCERR);
        return status;
    } else if(reg_status & SDIO_FLAG_CMDTMOUT) {
        status = EMMC_DRV_CMD_TIMEOUT;
        sdio_flag_clear(SDIO, SDIO_FLAG_CMDTMOUT);
        return status;
    } else {
        /* if else end */
    }

    /* check whether the last response command index is the desired one */
    if(sdio_command_index_get(SDIO) != cmdindex) {
        status = EMMC_DRV_ILLEGAL_CMD;
        return status;
    }
    /* clear all the CMD_FLAGS flags */
    sdio_flag_clear(SDIO, SDIO_MASK_CMD_FLAGS);
    /* get the SDIO response register 0 for checking */
    resp_r1 = sdio_response_get(SDIO, SDIO_RESPONSE0);
    if(EMMC_ALLZERO == (resp_r1 & EMMC_R1_ERROR_BITS)) {
        /* no error occurs, return EMMC_DRV_OK */
        return status;
    }
    /* if some error occurs, return the error type */
    status = r1_error_type_check(resp_r1);
    return status;
}

/*!
    \brief      check if error occurs for R2 response
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t r2_error_check(void)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t reg_status = 0U;

    /* store the content of SDIO_STAT */
    reg_status = SDIO_STAT(SDIO);
    while(!(reg_status & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDTMOUT | SDIO_FLAG_CMDRECV))) {
        reg_status = SDIO_STAT(SDIO);
    }
    /* check whether an error or timeout occurs or command response received */
    if(reg_status & SDIO_FLAG_CCRCERR) {
        status = EMMC_DRV_CMD_CRC_ERROR;
        sdio_flag_clear(SDIO, SDIO_FLAG_CCRCERR);
        return status;
    } else if(reg_status & SDIO_FLAG_CMDTMOUT) {
        status = EMMC_DRV_CMD_TIMEOUT;
        sdio_flag_clear(SDIO, SDIO_FLAG_CMDTMOUT);
        return status;
    } else {
        /* if else end */
    }
    /* clear all the CMD_FLAGS flags */
    sdio_flag_clear(SDIO, SDIO_MASK_CMD_FLAGS);
    return status;
}

/*!
    \brief      check if error occurs for R3 response
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t r3_error_check(void)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t reg_status = 0U;

    /* store the content of SDIO_STAT */
    reg_status = SDIO_STAT(SDIO);
    while(!(reg_status & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDTMOUT | SDIO_FLAG_CMDRECV))) {
        reg_status = SDIO_STAT(SDIO);
    }
    if(reg_status & SDIO_FLAG_CMDTMOUT) {
        status = EMMC_DRV_CMD_TIMEOUT;
        sdio_flag_clear(SDIO, SDIO_FLAG_CMDTMOUT);
        return status;
    }
    /* clear all the CMD_FLAGS flags */
    sdio_flag_clear(SDIO, SDIO_MASK_CMD_FLAGS);
    return status;
}

/*
    \brief      get the state which the card is in
    \param[out] pcardstate: a pointer that store the card state
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t emmc_card_state_get(uint8_t *pcardstate)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t reg_status = 0U, response = 0U;

    /* send CMD13(SEND_STATUS), addressed card sends its status register */
    sdio_command_response_config(SDIO, EMMC_CMD_SEND_STATUS, (uint32_t)emmc0.rca << EMMC_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);

    /* store the content of SDIO_STAT */
    reg_status = SDIO_STAT(SDIO);
    while(!(reg_status & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDTMOUT | SDIO_FLAG_CMDRECV))) {
        reg_status = SDIO_STAT(SDIO);
    }
    /* check whether an error or timeout occurs or command response received */
    if(reg_status & SDIO_FLAG_CCRCERR) {
        status = EMMC_DRV_CMD_CRC_ERROR;
        sdio_flag_clear(SDIO, SDIO_FLAG_CCRCERR);
        return status;
    } else if(reg_status & SDIO_FLAG_CMDTMOUT) {
        status = EMMC_DRV_CMD_TIMEOUT;
        sdio_flag_clear(SDIO, SDIO_FLAG_CMDTMOUT);
        return status;
    } else {
        /* if else end */
    }
    sdio_flag_clear(SDIO, SDIO_MASK_INTC_FLAGS);

    response = sdio_response_get(SDIO, SDIO_RESPONSE0);
    *pcardstate = (uint8_t)((response >> 9U) & (uint8_t)0x0FU);

    if(response & EMMC_R1_ERROR_BITS) {
        status = r1_error_type_check(response);
        return status;
    }
    return status;
}

/* -----------------------------------------------------------------------
 * eMMC initialization sequence
 * ----------------------------------------------------------------------- */

/*!
    \brief      configure the clock and the working voltage (CMD0 + CMD1)
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t emmc_power_on(void)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t response = 0U;
    uint32_t timedelay = 0U;

    /* configure the SDIO peripheral */
    sdio_clock_config(SDIO, SDIO_SDIOCLKEDGE_RISING, SDIO_CLOCKPWRSAVE_DISABLE, EMMC_CLK_DIV_INIT);
    sdio_bus_mode_set(SDIO, SDIO_BUSMODE_1BIT);
    sdio_hardware_clock_disable(SDIO);
    sdio_power_state_set(SDIO, SDIO_POWER_ON);

    /* time delay for power up */
    timedelay = 500U;
    while(timedelay > 0U) {
        --timedelay;
    }

    /* send CMD0(GO_IDLE_STATE) to reset the eMMC */
    sdio_command_response_config(SDIO, EMMC_CMD_GO_IDLE_STATE, (uint32_t)0x0, SDIO_RESPONSETYPE_NO);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    /* enable the CSM */
    sdio_csm_enable(SDIO);
    /* check if command sent error occurs */
    status = cmdsent_error_check();
    if(EMMC_DRV_OK != status) {
        return status;
    }

    /* send CMD1(SEND_OP_COND) to poll eMMC busy bit until card ready */
    timedelay = 0x4000U;
    while(timedelay > 0U) {
        --timedelay;
        /* Bit[30]=HCS (host supports high-capacity), bits[23:0]=3.3V window */
        sdio_command_response_config(SDIO, EMMC_CMD_SEND_OP_COND, (uint32_t)0x40FF8000U, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        /* enable the CSM */
        sdio_csm_enable(SDIO);
        /* check if some error occurs */
        status = r3_error_check();
        if(EMMC_DRV_OK != status) {
            return status;
        }
        /* get the response and check card power up status bit(busy) */
        response = sdio_response_get(SDIO, SDIO_RESPONSE0);
        if(0x80000000U == (response & 0x80000000U)) {
            return status;
        }
    }
    status = EMMC_DRV_VOLTRANGE_INVALID;
    return status;
}

/*!
    \brief      initialize the card and get CID, RCA and CSD (CMD2 + CMD3 + CMD9)
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t emmc_card_init(void)
{
    emmc_drv_err_t status = EMMC_DRV_OK;

    /* send CMD2(ALL_SEND_CID) to get the CID numbers */
    sdio_command_response_config(SDIO, EMMC_CMD_ALL_SEND_CID, (uint32_t)0x0, SDIO_RESPONSETYPE_LONG);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    /* check if some error occurs */
    status = r2_error_check();
    if(EMMC_DRV_OK != status) {
        return status;
    }
    /* store the CID numbers */
    emmc0.cid[0] = sdio_response_get(SDIO, SDIO_RESPONSE0);
    emmc0.cid[1] = sdio_response_get(SDIO, SDIO_RESPONSE1);
    emmc0.cid[2] = sdio_response_get(SDIO, SDIO_RESPONSE2);
    emmc0.cid[3] = sdio_response_get(SDIO, SDIO_RESPONSE3);

    /* send CMD3(SET_RELATIVE_ADDR) to assign RCA to eMMC (host assigns for eMMC, unlike SD) */
    sdio_command_response_config(SDIO, EMMC_CMD_SEND_RELATIVE_ADDR, (uint32_t)emmc0.rca << 16U, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    /* check if some error occurs */
    status = r1_error_check(EMMC_CMD_SEND_RELATIVE_ADDR);
    if(EMMC_DRV_OK != status) {
        return status;
    }

    /* send CMD9(SEND_CSD) to get the addressed card's card-specific data (CSD) */
    sdio_command_response_config(SDIO, EMMC_CMD_SEND_CSD, (uint32_t)(emmc0.rca << EMMC_RCA_SHIFT), SDIO_RESPONSETYPE_LONG);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    /* check if some error occurs */
    status = r2_error_check();
    if(EMMC_DRV_OK != status) {
        return status;
    }
    /* store the card-specific data (CSD) */
    emmc0.csd[0] = sdio_response_get(SDIO, SDIO_RESPONSE0);
    emmc0.csd[1] = sdio_response_get(SDIO, SDIO_RESPONSE1);
    emmc0.csd[2] = sdio_response_get(SDIO, SDIO_RESPONSE2);
    emmc0.csd[3] = sdio_response_get(SDIO, SDIO_RESPONSE3);

    return status;
}

/*!
    \brief      select the card and move it to transfer state (CMD7)
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t emmc_card_select(void)
{
    emmc_drv_err_t status = EMMC_DRV_OK;

    /* send CMD7(SELECT_DESELECT_CARD) to select the card */
    sdio_command_response_config(SDIO, EMMC_CMD_SELECT_DESELECT_CARD, (uint32_t)emmc0.rca << EMMC_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    /* check if some error occurs */
    status = r1_error_check(EMMC_CMD_SELECT_DESELECT_CARD);
    return status;
}

/*!
    \brief      get the EXT_CSD register (512 bytes) via IDMA polling (CMD8)
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t emmc_card_extcsd_get(void)
{
    uint32_t buf[128] = {0};
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t count = 0U, *ptempbuff = buf;

    /* configure SDIO data transmission */
    sdio_data_config(SDIO, EMMC_DATATIMEOUT, (uint32_t)512, SDIO_DATABLOCKSIZE_512BYTES);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOSDIO);
    sdio_trans_start_enable(SDIO);

    /* send CMD8(SEND_EXT_CSD) to read the EXT_CSD register */
    sdio_command_response_config(SDIO, EMMC_CMD_SEND_EXT_CSD, (uint32_t)0x0, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    /* check if some error occurs */
    status = r1_error_check(EMMC_CMD_SEND_EXT_CSD);
    if(EMMC_DRV_OK != status) {
        return status;
    }

    /* polling mode: read FIFO half-full (8 words) at a time */
    while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT | SDIO_FLAG_RXORE | SDIO_FLAG_DTBLKEND | SDIO_FLAG_DTEND)) {
        if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RFH)) {
            /* at least 8 words can be read in the FIFO */
            for(count = 0U; count < EMMC_FIFOHALF_WORDS; count++) {
                *(ptempbuff + count) = sdio_data_read(SDIO);
            }
            ptempbuff += EMMC_FIFOHALF_WORDS;
        }
    }
    /* get EXT_CSD register data */
    rt_memcpy(emmc_ext_csd, buf, 512U);

    sdio_trans_start_disable(SDIO);
    /* whether some error occurs and return it */
    if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR)) {
        status = EMMC_DRV_DATA_CRC_ERROR;
        sdio_flag_clear(SDIO, SDIO_FLAG_DTCRCERR);
        return status;
    } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTTMOUT)) {
        status = EMMC_DRV_DATA_TIMEOUT;
        sdio_flag_clear(SDIO, SDIO_FLAG_DTTMOUT);
        return status;
    } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RXORE)) {
        status = EMMC_DRV_RX_OVERRUN;
        sdio_flag_clear(SDIO, SDIO_FLAG_RXORE);
        return status;
    } else {
        /* if else end */
    }
    /* clear the SDIO_INTC flags */
    sdio_flag_clear(SDIO, SDIO_MASK_INTC_FLAGS);
    return status;
}

/*!
    \brief      configure bus width and speed mode in EXT_CSD (CMD13 + CMD6)
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t emmc_bus_mode_config(void)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t switch_arg = 0U;

    /* send CMD13(SEND_STATUS), addressed card sends its status registers */
    sdio_command_response_config(SDIO, EMMC_CMD_SEND_STATUS, (uint32_t)emmc0.rca << EMMC_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    /* check if some error occurs */
    status = r1_error_check(EMMC_CMD_SEND_STATUS);
    if(EMMC_DRV_OK != status) {
        return status;
    }

#if (EMMC_USE_DDR == 1)
    /* send CMD6(SWITCH) to configure bus interface timing — HS_TIMING must be set before DDR */
    sdio_command_response_config(SDIO, EMMC_CMD_SWITCH_FUNC, (uint32_t)0x03B90100U, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    /* enable the CSM */
    sdio_csm_enable(SDIO);
    /* check if some error occurs */
    status = r1_error_check(EMMC_CMD_SWITCH_FUNC);
    if(EMMC_DRV_OK != status) {
        return status;
    }
#endif

    /*
     * CMD6 arg: [31:26]=Access(03h=Write Byte)  [25:16]=Index(B7h=BUS_WIDTH)
     *           [15:8]=Value  [7:0]=CmdSet(0)
     * BUS_WIDTH values: 0=1-bit SDR, 1=4-bit SDR, 2=8-bit SDR, 5=4-bit DDR, 6=8-bit DDR
     */
#if   (EMMC_BUSWIDTH == 8) && (EMMC_USE_DDR == 1)
    switch_arg = 0x03B70600U;
#elif (EMMC_BUSWIDTH == 4) && (EMMC_USE_DDR == 1)
    switch_arg = 0x03B70500U;
#elif (EMMC_BUSWIDTH == 8)
    switch_arg = 0x03B70200U;
#elif (EMMC_BUSWIDTH == 4)
    switch_arg = 0x03B70100U;
#else
    switch_arg = 0x03B70000U;
#endif

    /* send CMD6(SWITCH) to set the bus width */
    sdio_command_response_config(SDIO, EMMC_CMD_SWITCH_FUNC, switch_arg, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    /* enable the CSM */
    sdio_csm_enable(SDIO);
    /* check if some error occurs */
    status = r1_error_check(EMMC_CMD_SWITCH_FUNC);
    if(EMMC_DRV_OK != status) {
        return status;
    }

    /* apply new host-side clock and bus settings */
#if (EMMC_USE_DDR == 1)
    sdio_clock_config(SDIO, SDIO_SDIOCLKEDGE_FALLING, SDIO_CLOCKPWRSAVE_DISABLE, EMMC_CLK_DIV_TRANS);
    sdio_bus_mode_set(SDIO, EMMC_BUSMODE_REG);
    sdio_data_rate_set(SDIO, SDIO_DATA_RATE_DDR);
    sdio_bus_speed_set(SDIO, SDIO_BUSSPEED_HIGH);
#else
    sdio_clock_config(SDIO, SDIO_SDIOCLKEDGE_RISING, SDIO_CLOCKPWRSAVE_DISABLE, EMMC_CLK_DIV_TRANS);
    sdio_bus_mode_set(SDIO, EMMC_BUSMODE_REG);
#endif
    sdio_hardware_clock_enable(SDIO);
    sdio_flag_clear(SDIO, SDIO_MASK_INTC_FLAGS);
    return status;
}

/* -----------------------------------------------------------------------
 * IDMA data-phase completion poll and card-ready helpers
 * ----------------------------------------------------------------------- */

/*!
    \brief      wait for IDMA data transfer to complete
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t wait_data_done(void)
{
    emmc_drv_err_t status = EMMC_DRV_OK;

    /* wait until data transfer ends */
    while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT |
                                SDIO_FLAG_RXORE    | SDIO_FLAG_TXURE  | SDIO_FLAG_DTEND)) {
    }
    /* whether some error occurs and return it */
    if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR)) {
        status = EMMC_DRV_DATA_CRC_ERROR;
        sdio_flag_clear(SDIO, SDIO_FLAG_DTCRCERR);
        return status;
    } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTTMOUT)) {
        status = EMMC_DRV_DATA_TIMEOUT;
        sdio_flag_clear(SDIO, SDIO_FLAG_DTTMOUT);
        return status;
    } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RXORE)) {
        status = EMMC_DRV_RX_OVERRUN;
        sdio_flag_clear(SDIO, SDIO_FLAG_RXORE);
        return status;
    } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_TXURE)) {
        status = EMMC_DRV_TX_UNDERRUN;
        sdio_flag_clear(SDIO, SDIO_FLAG_TXURE);
        return status;
    } else {
        /* if else end */
    }
    /* clear the DATA_FLAGS flags */
    sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);
    return status;
}

/*!
    \brief      wait for card to leave Programming/Receiving state
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t wait_card_ready(void)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint8_t cardstate = 0U;
    uint32_t timeout = 0x80000U;

    /* get the card state and wait the card is out of programming and receiving state */
    status = emmc_card_state_get(&cardstate);
    while((EMMC_DRV_OK == status) && ((EMMC_CARDSTATE_PROGRAMMING == cardstate) || (EMMC_CARDSTATE_RECEIVING == cardstate))) {
        if(0U == --timeout) {
            LOG_E("emmc: card not ready timeout");
            status = EMMC_DRV_ERROR;
            return status;
        }
        status = emmc_card_state_get(&cardstate);
    }
    return status;
}

/*!
    \brief      poll R1 READY_FOR_DATA bit via CMD13
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t wait_ready(void)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t response = 0U;
    uint32_t timeout = 100000U;

    /* send CMD13(SEND_STATUS), addressed card sends its status registers */
    sdio_command_response_config(SDIO, EMMC_CMD_SEND_STATUS, (uint32_t)emmc0.rca << EMMC_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    /* check if some error occurs */
    status = r1_error_check(EMMC_CMD_SEND_STATUS);
    if(EMMC_DRV_OK != status) {
        return status;
    }
    response = sdio_response_get(SDIO, SDIO_RESPONSE0);

    /* continue to send CMD13 to polling the state of card until buffer empty or timeout */
    while((0U == (response & EMMC_R1_READY_FOR_DATA)) && (timeout > 0U)) {
        --timeout;
        sdio_command_response_config(SDIO, EMMC_CMD_SEND_STATUS, (uint32_t)emmc0.rca << EMMC_RCA_SHIFT, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        /* check if some error occurs */
        status = r1_error_check(EMMC_CMD_SEND_STATUS);
        if(EMMC_DRV_OK != status) {
            return status;
        }
        response = sdio_response_get(SDIO, SDIO_RESPONSE0);
    }
    if(0U == timeout) {
        status = EMMC_DRV_ERROR;
    }
    return status;
}

/* -----------------------------------------------------------------------
 * ISR processing for DMA mode (cf. emmc_interrupts_process in emmc.c)
 * ----------------------------------------------------------------------- */

/*!
    \brief      process all the interrupts which the corresponding flags are set
    \param[in]  none
    \param[out] none
    \retval     emmc_drv_err_t
*/
emmc_drv_err_t emmc_isr_process(void)
{
    transerror = EMMC_DRV_OK;
    if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_DTEND)) {
        /* clear DTEND flag */
        sdio_interrupt_flag_clear(SDIO, SDIO_INT_FLAG_DTEND);
        /* disable IDMA */
        sdio_idma_disable(SDIO);
        /* disable all the interrupts */
        sdio_interrupt_disable(SDIO, SDIO_INT_DTCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_DTEND |
                               SDIO_INT_TFH | SDIO_INT_RFH | SDIO_INT_TXURE | SDIO_INT_RXORE);
        sdio_trans_start_disable(SDIO);
        /* send CMD12 to stop data transfer in multiple blocks read operation */
        if(1U == stopcondition) {
            sdio_command_response_config(SDIO, EMMC_CMD_STOP_TRANSMISSION, (uint32_t)0x0, SDIO_RESPONSETYPE_SHORT);
            sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
            sdio_csm_enable(SDIO);
            transerror = r1_error_check(EMMC_CMD_STOP_TRANSMISSION);
        } else {
            transerror = EMMC_DRV_OK;
        }
        transend = 1U;
        /* clear data flags */
        sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);
        return transerror;
    }

    if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_DTCRCERR | SDIO_INT_FLAG_DTTMOUT |
                                              SDIO_INT_FLAG_TXURE | SDIO_INT_FLAG_RXORE)) {
        /* set different errors */
        if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_DTCRCERR)) {
            transerror = EMMC_DRV_DATA_CRC_ERROR;
        }
        if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_DTTMOUT)) {
            transerror = EMMC_DRV_DATA_TIMEOUT;
        }
        if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_TXURE)) {
            transerror = EMMC_DRV_TX_UNDERRUN;
        }
        if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_RXORE)) {
            transerror = EMMC_DRV_RX_OVERRUN;
        }
        /* clear data flags */
        sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);
        /* disable all the interrupts */
        sdio_interrupt_disable(SDIO, SDIO_INT_DTCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_DTEND |
                               SDIO_INT_TXURE | SDIO_INT_RXORE);
        sdio_trans_start_disable(SDIO);
        sdio_fifo_reset_enable(SDIO);
        sdio_fifo_reset_disable(SDIO);
        sdio_flag_clear(SDIO, SDIO_FLAG_DTABORT);
        if(EMMC_DMA_MODE == transmode) {
            sdio_idma_disable(SDIO);
        }
        return transerror;
    }

    if(RESET != sdio_interrupt_flag_get(SDIO, SDIO_INT_FLAG_IDMAERR)) {
        sdio_interrupt_flag_clear(SDIO, SDIO_INT_FLAG_IDMAERR);
        transerror = EMMC_DRV_DMA_ERROR;
        sdio_interrupt_disable(SDIO, SDIO_INT_DTCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_DTEND |
                               SDIO_INT_TXURE | SDIO_INT_RXORE);
        sdio_idma_disable(SDIO);
        return transerror;
    }
    return transerror;
}

#if EMMC_USE_DMA && !defined(BSP_USING_SD)
/*!
    \brief      SDIO0 interrupt service routine (eMMC DMA mode)
    \note       Active only when EMMC_USE_DMA == 1 and BSP_USING_SD is not defined.
                drv_sd_h7.c provides its own SDIO0_IRQHandler when BSP_USING_SD is set.
                The Kconfig choice ensures BSP_USING_EMMC and BSP_USING_SD are mutually exclusive.
*/
void SDIO0_IRQHandler(void)
{
    rt_interrupt_enter();
    emmc_isr_process();
    rt_interrupt_leave();
}
#endif /* EMMC_USE_DMA && !BSP_USING_SD */

/* -----------------------------------------------------------------------
 * Public card-information API
 * ----------------------------------------------------------------------- */

/*!
    \brief      parse CID, CSD, and EXT_CSD raw registers into emmc_card_info_struct
    \param[out] pcardinfo: pointer to the result struct
    \retval     emmc_drv_err_t — EMMC_DRV_PARAM_ERROR if pcardinfo is NULL,
                                  EMMC_DRV_OK on success
    \note       Must be called after rt_hw_emmccard_init() has completed.
                CID/CSD are captured during init; EXT_CSD is captured after
                bus-mode configuration.  All capacity figures come from
                EXT_CSD SEC_CNT (bytes 215:212), as required by JEDEC for
                eMMC v4+ high-density devices.
*/
emmc_drv_err_t emmc_card_information_get(emmc_card_info_struct *pcardinfo)
{
    uint8_t  tempbyte = 0U;
    uint32_t sec_cnt  = 0U;

    if(RT_NULL == pcardinfo) {
        return EMMC_DRV_PARAM_ERROR;
    }

    /* ----------------------------------------------------------------
     * CID parsing — JEDEC JESD84-B51, eMMC v4+ layout
     * emmc0.cid[0] = CID[127:96]   emmc0.cid[1] = CID[95:64]
     * emmc0.cid[2] = CID[63:32]    emmc0.cid[3] = CID[31:0]
     * ------------------------------------------------------------ */

    /* MID: CID[127:120] = cid[0][31:24] */
    pcardinfo->card_cid.mid = (uint8_t)((emmc0.cid[0] >> 24U) & 0xFFU);

    /* OID (16-bit raw, includes CBX[15:14]+rsvd[13:10]+OID[7:0]):
     * CID[119:104] = cid[0][23:8] */
    pcardinfo->card_cid.oid = (uint16_t)((emmc0.cid[0] >> 8U) & 0xFFFFU);

    /* PNM 6 chars: CID[103:56]
     * char0 = CID[103:96] = cid[0][7:0]
     * char1 = CID[95:88]  = cid[1][31:24]
     * char2 = CID[87:80]  = cid[1][23:16]
     * char3 = CID[79:72]  = cid[1][15:8]
     * char4 = CID[71:64]  = cid[1][7:0]
     * char5 = CID[63:56]  = cid[2][31:24] */
    pcardinfo->card_cid.pnm[0] = (char)(emmc0.cid[0] & 0xFFU);
    pcardinfo->card_cid.pnm[1] = (char)((emmc0.cid[1] >> 24U) & 0xFFU);
    pcardinfo->card_cid.pnm[2] = (char)((emmc0.cid[1] >> 16U) & 0xFFU);
    pcardinfo->card_cid.pnm[3] = (char)((emmc0.cid[1] >>  8U) & 0xFFU);
    pcardinfo->card_cid.pnm[4] = (char)(emmc0.cid[1] & 0xFFU);
    pcardinfo->card_cid.pnm[5] = (char)((emmc0.cid[2] >> 24U) & 0xFFU);
    pcardinfo->card_cid.pnm[6] = '\0';

    /* PRV: CID[55:48] = cid[2][23:16] */
    pcardinfo->card_cid.prv = (uint8_t)((emmc0.cid[2] >> 16U) & 0xFFU);

    /* PSN: CID[47:16] = cid[2][15:0] | cid[3][31:16] */
    pcardinfo->card_cid.psn = ((emmc0.cid[2] & 0xFFFFU) << 16U) |
                               ((emmc0.cid[3] >> 16U) & 0xFFFFU);

    /* MDT: CID[15:12]=month, CID[11:8]=year-nibble — in cid[3][15:8] */
    pcardinfo->card_cid.mdt_month = (uint8_t)((emmc0.cid[3] >> 12U) & 0x0FU);
    pcardinfo->card_cid.mdt_year  = (uint16_t)(((emmc0.cid[3] >>  8U) & 0x0FU) + 1997U);

    /* CRC: CID[7:1] = cid[3][7:1] */
    pcardinfo->card_cid.cid_crc = (uint8_t)((emmc0.cid[3] >> 1U) & 0x7FU);

    /* ----------------------------------------------------------------
     * CSD parsing — JEDEC JESD84-B51, CSD v1.x format
     * emmc0.csd[0] = CSD[127:96]   emmc0.csd[1] = CSD[95:64]
     * emmc0.csd[2] = CSD[63:32]    emmc0.csd[3] = CSD[31:0]
     * ------------------------------------------------------------ */

    /* CSD byte 0: CSD[127:120] = csd[0][31:24]
     * [7:6]=CSD_STRUCT  [5:2]=SPEC_VERS (eMMC-specific) */
    tempbyte = (uint8_t)((emmc0.csd[0] >> 24U) & 0xFFU);
    pcardinfo->card_csd.csd_struct = (tempbyte & 0xC0U) >> 6U;
    pcardinfo->card_csd.spec_vers  = (tempbyte & 0x3CU) >> 2U;

    /* CSD byte 1: CSD[119:112] = csd[0][23:16] — TAAC */
    pcardinfo->card_csd.taac = (uint8_t)((emmc0.csd[0] >> 16U) & 0xFFU);

    /* CSD byte 2: CSD[111:104] = csd[0][15:8] — NSAC */
    pcardinfo->card_csd.nsac = (uint8_t)((emmc0.csd[0] >>  8U) & 0xFFU);

    /* CSD byte 3: CSD[103:96] = csd[0][7:0] — TRAN_SPEED */
    pcardinfo->card_csd.tran_speed = (uint8_t)(emmc0.csd[0] & 0xFFU);

    /* CSD byte 4: CSD[95:88] = csd[1][31:24] — CCC[11:4] */
    tempbyte = (uint8_t)((emmc0.csd[1] >> 24U) & 0xFFU);
    pcardinfo->card_csd.ccc = (uint16_t)((uint16_t)tempbyte << 4U);

    /* CSD byte 5: CSD[87:80] = csd[1][23:16] — CCC[3:0] | READ_BL_LEN[3:0] */
    tempbyte = (uint8_t)((emmc0.csd[1] >> 16U) & 0xFFU);
    pcardinfo->card_csd.ccc         |= (uint16_t)((tempbyte & 0xF0U) >> 4U);
    pcardinfo->card_csd.read_bl_len  = tempbyte & 0x0FU;

    /* CSD byte 6: CSD[79:72] = csd[1][15:8]
     * [7]=RBP  [6]=WBM  [5]=RBM  [4]=DSR  [3:2]=rsvd  [1:0]=C_SIZE[11:10] */
    tempbyte = (uint8_t)((emmc0.csd[1] >>  8U) & 0xFFU);
    pcardinfo->card_csd.read_bl_partial    = (tempbyte & 0x80U) >> 7U;
    pcardinfo->card_csd.write_blk_misalign = (tempbyte & 0x40U) >> 6U;
    pcardinfo->card_csd.read_blk_misalign  = (tempbyte & 0x20U) >> 5U;
    pcardinfo->card_csd.dsp_imp            = (tempbyte & 0x10U) >> 4U;
    pcardinfo->card_csd.c_size             = (uint32_t)(tempbyte & 0x03U) << 10U;

    /* CSD byte 7: CSD[71:64] = csd[1][7:0] — C_SIZE[9:2] */
    tempbyte = (uint8_t)(emmc0.csd[1] & 0xFFU);
    pcardinfo->card_csd.c_size |= (uint32_t)tempbyte << 2U;

    /* CSD byte 8: CSD[63:56] = csd[2][31:24]
     * [7:6]=C_SIZE[1:0]  [5:3]=VDD_R_MIN  [2:0]=VDD_R_MAX */
    tempbyte = (uint8_t)((emmc0.csd[2] >> 24U) & 0xFFU);
    pcardinfo->card_csd.c_size        |= (uint32_t)(tempbyte & 0xC0U) >> 6U;
    pcardinfo->card_csd.vdd_r_curr_min = (tempbyte & 0x38U) >> 3U;
    pcardinfo->card_csd.vdd_r_curr_max =  tempbyte & 0x07U;

    /* CSD byte 9: CSD[55:48] = csd[2][23:16]
     * [7:5]=VDD_W_MIN  [4:2]=VDD_W_MAX  [1:0]=C_SIZE_MULT[2:1] */
    tempbyte = (uint8_t)((emmc0.csd[2] >> 16U) & 0xFFU);
    pcardinfo->card_csd.vdd_w_curr_min = (tempbyte & 0xE0U) >> 5U;
    pcardinfo->card_csd.vdd_w_curr_max = (tempbyte & 0x1CU) >> 2U;
    pcardinfo->card_csd.c_size_mult    = (tempbyte & 0x03U) << 1U;   /* bits [2:1] */

    /* CSD byte 10: CSD[47:40] = csd[2][15:8]
     * [7]=C_SIZE_MULT[0]  [6:2]=ERASE_GRP_SIZE[4:0]  [1:0]=ERASE_GRP_MULT[4:3] */
    tempbyte = (uint8_t)((emmc0.csd[2] >>  8U) & 0xFFU);
    pcardinfo->card_csd.c_size_mult   |= (tempbyte & 0x80U) >> 7U;   /* bit [0] */
    pcardinfo->card_csd.erase_grp_size = (tempbyte & 0x7CU) >> 2U;
    pcardinfo->card_csd.erase_grp_mult = (tempbyte & 0x03U) << 3U;   /* bits [4:3] */

    /* CSD byte 11: CSD[39:32] = csd[2][7:0]
     * [7:5]=ERASE_GRP_MULT[2:0]  [4:0]=WP_GRP_SIZE[4:0] */
    tempbyte = (uint8_t)(emmc0.csd[2] & 0xFFU);
    pcardinfo->card_csd.erase_grp_mult |= (tempbyte & 0xE0U) >> 5U;  /* bits [2:0] */
    pcardinfo->card_csd.wp_grp_size     =  tempbyte & 0x1FU;

    /* CSD byte 12: CSD[31:24] = csd[3][31:24]
     * [6]=WP_GRP_ENABLE  [3:1]=R2W_FACTOR[2:0]  [0]=WRITE_BL_LEN[3] */
    tempbyte = (uint8_t)((emmc0.csd[3] >> 24U) & 0xFFU);
    pcardinfo->card_csd.wp_grp_enable = (tempbyte & 0x40U) >> 6U;
    pcardinfo->card_csd.r2w_factor    = (tempbyte & 0x0EU) >> 1U;
    pcardinfo->card_csd.write_bl_len  = (tempbyte & 0x01U) << 3U;    /* bit [3] */

    /* CSD byte 13: CSD[23:16] = csd[3][23:16]
     * [7:5]=WRITE_BL_LEN[2:0]  [4]=WRITE_BL_PARTIAL */
    tempbyte = (uint8_t)((emmc0.csd[3] >> 16U) & 0xFFU);
    pcardinfo->card_csd.write_bl_len    |= (tempbyte & 0xE0U) >> 5U; /* bits [2:0] */
    pcardinfo->card_csd.write_bl_partial = (tempbyte & 0x10U) >> 4U;

    /* CSD byte 14: CSD[15:8] = csd[3][15:8]
     * [5]=PERM_WRITE_PROTECT  [4]=TMP_WRITE_PROTECT */
    tempbyte = (uint8_t)((emmc0.csd[3] >>  8U) & 0xFFU);
    pcardinfo->card_csd.perm_write_protect = (tempbyte & 0x20U) >> 5U;
    pcardinfo->card_csd.tmp_write_protect  = (tempbyte & 0x10U) >> 4U;

    /* CSD byte 15: CSD[7:0] = csd[3][7:0] — CRC[7:1] */
    pcardinfo->card_csd.csd_crc = (uint8_t)((emmc0.csd[3] >> 1U) & 0x7FU);

    /* ----------------------------------------------------------------
     * Capacity: always use EXT_CSD SEC_CNT for eMMC v4+ (JEDEC requirement).
     * SEC_CNT is a 32-bit little-endian value at EXT_CSD[215:212].
     * ------------------------------------------------------------ */
    sec_cnt = ((uint32_t)emmc_ext_csd[EXT_CSD_SEC_CNT_B3] << 24U) |
              ((uint32_t)emmc_ext_csd[EXT_CSD_SEC_CNT_B2] << 16U) |
              ((uint32_t)emmc_ext_csd[EXT_CSD_SEC_CNT_B1] <<  8U) |
              ((uint32_t)emmc_ext_csd[EXT_CSD_SEC_CNT_B0]);

    pcardinfo->card_blocksize = EMMC_SECTOR_SIZE;
    pcardinfo->card_capacity  = (uint64_t)sec_cnt * EMMC_SECTOR_SIZE;
    pcardinfo->card_rca       = emmc0.rca;

    /* ----------------------------------------------------------------
     * EXT_CSD key fields
     * ------------------------------------------------------------ */
    pcardinfo->ext_csd_rev = emmc_ext_csd[192U]; /* EXT_CSD revision       */
    pcardinfo->hs_timing   = emmc_ext_csd[185U]; /* HS_TIMING setting      */
    pcardinfo->bus_width   = emmc_ext_csd[183U]; /* BUS_WIDTH register     */

    return EMMC_DRV_OK;
}

/* -----------------------------------------------------------------------
 * Block Read  (CMD17 / CMD18, FIFO polling / DMA, sector addressing)
 * ----------------------------------------------------------------------- */

/*!

    \brief      read a block data into a buffer from the specified sector of eMMC
    \param[out] buf: a pointer that store a block read data
    \param[in]  sector: the sector address
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t emmc_block_read(uint32_t *buf, uint32_t sector)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t count = 0U, *ptempbuff = buf;

    transerror = EMMC_DRV_OK;
    transend = 0U;
    stopcondition = 0U;

    /* clear all DSM configuration */
    sdio_data_config(SDIO, 0U, 0U, SDIO_DATABLOCKSIZE_1BYTE);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_dsm_disable(SDIO);
    sdio_idma_disable(SDIO);

    if(EMMC_POLLING_MODE == transmode) {
        /* configure SDIO data transmission */
        sdio_data_config(SDIO, EMMC_DATATIMEOUT, EMMC_SECTOR_SIZE, SDIO_DATABLOCKSIZE_512BYTES);
        sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOSDIO);
        sdio_trans_start_enable(SDIO);

        /* send CMD17(READ_SINGLE_BLOCK) to read a block */
        sdio_command_response_config(SDIO, EMMC_CMD_READ_SINGLE_BLOCK, sector, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        /* check if some error occurs */
        status = r1_error_check(EMMC_CMD_READ_SINGLE_BLOCK);
        if(EMMC_DRV_OK != status) {
            return status;
        }

        /* polling mode */
        while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT | SDIO_FLAG_RXORE | SDIO_FLAG_DTBLKEND | SDIO_FLAG_DTEND)) {
            if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RFH)) {
                /* at least 8 words can be read in the FIFO */
                for(count = 0U; count < EMMC_FIFOHALF_WORDS; count++) {
                    *(ptempbuff + count) = sdio_data_read(SDIO);
                }
                ptempbuff += EMMC_FIFOHALF_WORDS;
            }
        }

        sdio_trans_start_disable(SDIO);

        /* whether some error occurs and return it */
        if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR)) {
            status = EMMC_DRV_DATA_CRC_ERROR;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTCRCERR);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTTMOUT)) {
            status = EMMC_DRV_DATA_TIMEOUT;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTTMOUT);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RXORE)) {
            status = EMMC_DRV_RX_OVERRUN;
            sdio_flag_clear(SDIO, SDIO_FLAG_RXORE);
            return status;
        } else {
            /* if else end */
        }

        while((SET != sdio_flag_get(SDIO, SDIO_FLAG_RFE)) && (SET == sdio_flag_get(SDIO, SDIO_FLAG_DATSTA))) {
            *ptempbuff = sdio_data_read(SDIO);
            ++ptempbuff;
        }
        /* clear the DATA_FLAGS flags */
        sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);
    } else if(EMMC_DMA_MODE == transmode) {
        /* DMA mode */
        /* invalidate DCache for read buffer so CPU sees DMA-written data after transfer */
        emmc_dcache_invalidate(buf, EMMC_SECTOR_SIZE);
        /* enable the SDIO corresponding interrupts and DMA function */
        sdio_interrupt_enable(SDIO, SDIO_INT_CCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_RXORE | SDIO_INT_DTEND);
        dma_config(buf, (uint32_t)(EMMC_SECTOR_SIZE >> 5));
        sdio_idma_enable(SDIO);
        /* configure SDIO data transmission */
        sdio_data_config(SDIO, EMMC_DATATIMEOUT, EMMC_SECTOR_SIZE, SDIO_DATABLOCKSIZE_512BYTES);
        sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOSDIO);
        sdio_trans_start_enable(SDIO);

        /* send CMD17(READ_SINGLE_BLOCK) to read a block */
        sdio_command_response_config(SDIO, EMMC_CMD_READ_SINGLE_BLOCK, sector, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        /* check if some error occurs */
        status = r1_error_check(EMMC_CMD_READ_SINGLE_BLOCK);
        if(EMMC_DRV_OK != status) {
            return status;
        }

        while((0U == transend) && (EMMC_DRV_OK == transerror)) {
        }
        if(EMMC_DRV_OK != transerror) {
            return transerror;
        }
    } else {
        status = EMMC_DRV_PARAM_ERROR;
    }
    return status;
}

/*!
    \brief      read multiple blocks data into a buffer from the specified sector of eMMC
    \param[out] buf: a pointer that store multiple blocks read data
    \param[in]  sector: the sector address
    \param[in]  count: number of blocks to read
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t emmc_multiblocks_read(uint32_t *buf, uint32_t sector, uint32_t count)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t wordcount = 0U, *ptempbuff = buf;
    uint32_t total_bytes = count * EMMC_SECTOR_SIZE;

    transerror = EMMC_DRV_OK;
    transend = 0U;
    stopcondition = 0U;

    /* clear all DSM configuration */
    sdio_data_config(SDIO, 0U, 0U, SDIO_DATABLOCKSIZE_1BYTE);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_dsm_disable(SDIO);
    sdio_idma_disable(SDIO);

    if(EMMC_POLLING_MODE == transmode) {
        /* configure SDIO data transmission */
        sdio_data_config(SDIO, EMMC_DATATIMEOUT, total_bytes, SDIO_DATABLOCKSIZE_512BYTES);
        sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOSDIO);
        sdio_trans_start_enable(SDIO);

        /* send CMD18(READ_MULTIPLE_BLOCK) to read multiple blocks */
        sdio_command_response_config(SDIO, EMMC_CMD_READ_MULTIPLE_BLOCK, sector, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        /* check if some error occurs */
        status = r1_error_check(EMMC_CMD_READ_MULTIPLE_BLOCK);
        if(EMMC_DRV_OK != status) {
            return status;
        }

        /* polling mode */
        while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT | SDIO_FLAG_RXORE | SDIO_FLAG_DTBLKEND | SDIO_FLAG_DTEND)) {
            if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RFH)) {
                /* at least 8 words can be read in the FIFO */
                for(wordcount = 0U; wordcount < EMMC_FIFOHALF_WORDS; wordcount++) {
                    *(ptempbuff + wordcount) = sdio_data_read(SDIO);
                }
                ptempbuff += EMMC_FIFOHALF_WORDS;
            }
        }

        /* whether some error occurs and return it */
        if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR)) {
            status = EMMC_DRV_DATA_CRC_ERROR;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTCRCERR);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTTMOUT)) {
            status = EMMC_DRV_DATA_TIMEOUT;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTTMOUT);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_RXORE)) {
            status = EMMC_DRV_RX_OVERRUN;
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
            /* send CMD12(STOP_TRANSMISSION) to stop transmission */
            sdio_command_response_config(SDIO, EMMC_CMD_STOP_TRANSMISSION, (uint32_t)0x0, SDIO_RESPONSETYPE_SHORT);
            sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
            sdio_csm_enable(SDIO);
            /* check if some error occurs */
            status = r1_error_check(EMMC_CMD_STOP_TRANSMISSION);
            if(EMMC_DRV_OK != status) {
                return status;
            }
        }
        /* clear the DATA_FLAGS flags */
        sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);
    } else if(EMMC_DMA_MODE == transmode) {
        /* DMA mode */
        stopcondition = 1U;
        /* invalidate DCache for read buffer so CPU sees DMA-written data after transfer */
        emmc_dcache_invalidate(buf, total_bytes);
        /* enable the SDIO corresponding interrupts and DMA function */
        sdio_interrupt_enable(SDIO, SDIO_INT_CCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_RXORE | SDIO_INT_DTEND);
        dma_config(buf, (uint32_t)(total_bytes >> 5));
        sdio_idma_enable(SDIO);
        /* configure SDIO data transmission */
        sdio_data_config(SDIO, EMMC_DATATIMEOUT, total_bytes, SDIO_DATABLOCKSIZE_512BYTES);
        sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOSDIO);
        sdio_trans_start_enable(SDIO);

        /* send CMD18(READ_MULTIPLE_BLOCK) to read multiple blocks */
        sdio_command_response_config(SDIO, EMMC_CMD_READ_MULTIPLE_BLOCK, sector, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        /* check if some error occurs */
        status = r1_error_check(EMMC_CMD_READ_MULTIPLE_BLOCK);
        if(EMMC_DRV_OK != status) {
            return status;
        }

        while((0U == transend) && (EMMC_DRV_OK == transerror)) {
        }
        if(EMMC_DRV_OK != transerror) {
            return transerror;
        }
    } else {
        status = EMMC_DRV_PARAM_ERROR;
    }
    return status;
}

/* -----------------------------------------------------------------------
 * Block Write (CMD24 / CMD23+CMD25, FIFO polling, sector addressing)
 * ----------------------------------------------------------------------- */

/*!
    \brief      write a block data to the specified sector of eMMC
    \param[in]  buf: a pointer that store a block data to be transferred
    \param[in]  sector: the sector address
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t emmc_block_write(uint32_t *buf, uint32_t sector)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    __IO uint32_t count = 0U, *ptempbuff = buf;
    uint32_t transbytes = 0U, restwords = 0U;

    transerror = EMMC_DRV_OK;
    transend = 0U;
    stopcondition = 0U;

    /* poll READY_FOR_DATA before writing */
    status = wait_ready();
    if(EMMC_DRV_OK != status) {
        return status;
    }

    /* clear all DSM configuration */
    sdio_data_config(SDIO, 0U, 0U, SDIO_DATABLOCKSIZE_1BYTE);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_dsm_disable(SDIO);
    sdio_idma_disable(SDIO);

    /* configure the SDIO data transmission */
    sdio_data_config(SDIO, EMMC_DATATIMEOUT, EMMC_SECTOR_SIZE, SDIO_DATABLOCKSIZE_512BYTES);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_trans_start_enable(SDIO);

    if(EMMC_POLLING_MODE == transmode) {
        /* send CMD24(WRITE_BLOCK) to write a block */
        sdio_command_response_config(SDIO, EMMC_CMD_WRITE_BLOCK, sector, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        /* check if some error occurs */
        status = r1_error_check(EMMC_CMD_WRITE_BLOCK);
        if(EMMC_DRV_OK != status) {
            return status;
        }

        /* polling mode */
        while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT | SDIO_FLAG_TXURE | SDIO_FLAG_DTBLKEND | SDIO_FLAG_DTEND)) {
            if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_TFH)) {
                /* at least 8 words can be written into the FIFO */
                if((EMMC_SECTOR_SIZE - transbytes) < EMMC_FIFOHALF_BYTES) {
                    restwords = (EMMC_SECTOR_SIZE - transbytes) / 4U +
                                (((EMMC_SECTOR_SIZE - transbytes) % 4U == 0U) ? 0U : 1U);
                    for(count = 0U; count < restwords; count++) {
                        sdio_data_write(SDIO, *ptempbuff);
                        ++ptempbuff;
                        transbytes += 4U;
                    }
                } else {
                    for(count = 0U; count < EMMC_FIFOHALF_WORDS; count++) {
                        sdio_data_write(SDIO, *(ptempbuff + count));
                    }
                    /* 8 words(32 bytes) has been transferred */
                    ptempbuff += EMMC_FIFOHALF_WORDS;
                    transbytes += EMMC_FIFOHALF_BYTES;
                }
            }
        }

        sdio_trans_start_disable(SDIO);

        /* whether some error occurs and return it */
        if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR)) {
            status = EMMC_DRV_DATA_CRC_ERROR;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTCRCERR);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTTMOUT)) {
            status = EMMC_DRV_DATA_TIMEOUT;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTTMOUT);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_TXURE)) {
            status = EMMC_DRV_TX_UNDERRUN;
            sdio_flag_clear(SDIO, SDIO_FLAG_TXURE);
            return status;
        } else {
            /* if else end */
        }
    } else if(EMMC_DMA_MODE == transmode) {
        /* DMA mode */
        /* clean DCache so DMA reads the latest CPU-written data from RAM */
        emmc_dcache_clean(buf, EMMC_SECTOR_SIZE);
        /* enable the SDIO corresponding interrupts and DMA function */
        sdio_interrupt_enable(SDIO, SDIO_INT_DTCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_TXURE | SDIO_INT_DTEND);
        dma_config(buf, (uint32_t)(EMMC_SECTOR_SIZE >> 5));
        sdio_idma_enable(SDIO);

        /* send CMD24(WRITE_BLOCK) to write a block */
        sdio_command_response_config(SDIO, EMMC_CMD_WRITE_BLOCK, sector, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        /* check if some error occurs */
        status = r1_error_check(EMMC_CMD_WRITE_BLOCK);
        if(EMMC_DRV_OK != status) {
            return status;
        }

        while((0U == transend) && (EMMC_DRV_OK == transerror)) {
        }
        if(EMMC_DRV_OK != transerror) {
            return transerror;
        }
    } else {
        status = EMMC_DRV_PARAM_ERROR;
        return status;
    }
    /* clear the DATA_FLAGS flags */
    sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);

    /* get the card state and wait the card is out of programming and receiving state */
    status = wait_card_ready();
    return status;
}

/*!
    \brief      write multiple blocks data to the specified sector of eMMC
    \param[in]  buf: a pointer that store multiple blocks data to be transferred
    \param[in]  sector: the sector address
    \param[in]  count: number of blocks to write
    \retval     emmc_drv_err_t
*/
static emmc_drv_err_t emmc_multiblocks_write(uint32_t *buf, uint32_t sector, uint32_t count)
{
    emmc_drv_err_t status = EMMC_DRV_OK;
    uint32_t wordcount = 0U, *ptempbuff = buf;
    uint32_t total_bytes = count * EMMC_SECTOR_SIZE;
    uint32_t transbytes = 0U, restwords = 0U;

    transerror = EMMC_DRV_OK;
    transend = 0U;
    stopcondition = 0U;

    /* poll READY_FOR_DATA before writing */
    status = wait_ready();
    if(EMMC_DRV_OK != status) {
        return status;
    }

    /* send CMD23(SET_BLOCK_COUNT) to pre-set the number of blocks — eMMC uses CMD23 instead of CMD12 */
    sdio_command_response_config(SDIO, EMMC_CMD_SET_BLOCK_COUNT, count, SDIO_RESPONSETYPE_SHORT);
    sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
    sdio_csm_enable(SDIO);
    /* check if some error occurs */
    status = r1_error_check(EMMC_CMD_SET_BLOCK_COUNT);
    if(EMMC_DRV_OK != status) {
        return status;
    }

    /* clear all DSM configuration */
    sdio_data_config(SDIO, 0U, 0U, SDIO_DATABLOCKSIZE_1BYTE);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_dsm_disable(SDIO);
    sdio_idma_disable(SDIO);

    /* configure the SDIO data transmission */
    sdio_data_config(SDIO, EMMC_DATATIMEOUT, total_bytes, SDIO_DATABLOCKSIZE_512BYTES);
    sdio_data_transfer_config(SDIO, SDIO_TRANSMODE_BLOCKCOUNT, SDIO_TRANSDIRECTION_TOCARD);
    sdio_trans_start_enable(SDIO);

    if(EMMC_POLLING_MODE == transmode) {
        /* send CMD25(WRITE_MULTIPLE_BLOCK) to continuously write blocks of data */
        sdio_command_response_config(SDIO, EMMC_CMD_WRITE_MULTIPLE_BLOCK, sector, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        /* check if some error occurs */
        status = r1_error_check(EMMC_CMD_WRITE_MULTIPLE_BLOCK);
        if(EMMC_DRV_OK != status) {
            return status;
        }
        sdio_dsm_enable(SDIO);

        /* polling mode */
        while(!sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR | SDIO_FLAG_DTTMOUT | SDIO_FLAG_TXURE | SDIO_FLAG_DTBLKEND | SDIO_FLAG_DTEND)) {
            if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_TFH)) {
                /* at least 8 words can be written into the FIFO */
                if((total_bytes - transbytes) < EMMC_FIFOHALF_BYTES) {
                    restwords = (total_bytes - transbytes) / 4U +
                                (((total_bytes - transbytes) % 4U == 0U) ? 0U : 1U);
                    for(wordcount = 0U; wordcount < restwords; wordcount++) {
                        sdio_data_write(SDIO, *ptempbuff);
                        ++ptempbuff;
                        transbytes += 4U;
                    }
                } else {
                    for(wordcount = 0U; wordcount < EMMC_FIFOHALF_WORDS; wordcount++) {
                        sdio_data_write(SDIO, *(ptempbuff + wordcount));
                    }
                    /* 8 words(32 bytes) has been transferred */
                    ptempbuff += EMMC_FIFOHALF_WORDS;
                    transbytes += EMMC_FIFOHALF_BYTES;
                }
            }
        }

        sdio_trans_start_disable(SDIO);

        /* whether some error occurs and return it */
        if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTCRCERR)) {
            status = EMMC_DRV_DATA_CRC_ERROR;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTCRCERR);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_DTTMOUT)) {
            status = EMMC_DRV_DATA_TIMEOUT;
            sdio_flag_clear(SDIO, SDIO_FLAG_DTTMOUT);
            return status;
        } else if(RESET != sdio_flag_get(SDIO, SDIO_FLAG_TXURE)) {
            status = EMMC_DRV_TX_UNDERRUN;
            sdio_flag_clear(SDIO, SDIO_FLAG_TXURE);
            return status;
        } else {
            /* if else end */
        }
    } else if(EMMC_DMA_MODE == transmode) {
        /* DMA mode */
        /* clean DCache so DMA reads the latest CPU-written data from RAM */
        emmc_dcache_clean(buf, total_bytes);
        /* enable the SDIO corresponding interrupts and DMA function */
        sdio_interrupt_enable(SDIO, SDIO_INT_DTCRCERR | SDIO_INT_DTTMOUT | SDIO_INT_TXURE | SDIO_INT_DTEND);
        dma_config(buf, (uint32_t)(total_bytes >> 5));
        sdio_idma_enable(SDIO);

        /* send CMD25(WRITE_MULTIPLE_BLOCK) to continuously write blocks of data */
        sdio_command_response_config(SDIO, EMMC_CMD_WRITE_MULTIPLE_BLOCK, sector, SDIO_RESPONSETYPE_SHORT);
        sdio_wait_type_set(SDIO, SDIO_WAITTYPE_NO);
        sdio_csm_enable(SDIO);
        /* check if some error occurs */
        status = r1_error_check(EMMC_CMD_WRITE_MULTIPLE_BLOCK);
        if(EMMC_DRV_OK != status) {
            return status;
        }

        while((0U == transend) && (EMMC_DRV_OK == transerror)) {
        }
        if(EMMC_DRV_OK != transerror) {
            return transerror;
        }
    } else {
        status = EMMC_DRV_PARAM_ERROR;
        return status;
    }
    /* clear the DATA_FLAGS flags */
    sdio_flag_clear(SDIO, SDIO_MASK_DATA_FLAGS);

    /* get the card state and wait the card is out of programming and receiving state */
    status = wait_card_ready();
    return status;
}

/* -----------------------------------------------------------------------
 * RT-Thread block device callbacks
 * ----------------------------------------------------------------------- */
static rt_err_t rt_emmccard_init(rt_device_t dev)
{
    emmc_drv_err_t err = EMMC_DRV_OK;
    rt_err_t       ret = RT_EOK;
    uint16_t       retry = 5U;

    ret = rt_mutex_init(&emmc0.emmc_lock, "emmc_lock", RT_IPC_FLAG_FIFO);
    if(RT_EOK != ret) {
        LOG_E("emmc mutex init failed");
        return ret;
    }

    do {
        /* configure the RCU */
        err = rcu_config();
        if(EMMC_DRV_OK != err) {
            LOG_W("rcu_config fail:%d", err);
            continue;
        }
        /* configure the SDIO GPIO and deinitialize the SDIO */
        sdio_gpio_config();
        sdio_deinit(SDIO);

        /* configure the clock and working voltage */
        err = emmc_power_on();
        if(EMMC_DRV_OK != err) {
            LOG_W("power_on fail:%d", err);
            continue;
        }

        /* initialize the card and get CID and CSD of the card */
        err = emmc_card_init();
        if(EMMC_DRV_OK != err) {
            LOG_W("card_init fail:%d", err);
            continue;
        }

        /* configure the SDIO peripheral */
        sdio_clock_config(SDIO, SDIO_SDIOCLKEDGE_RISING, SDIO_CLOCKPWRSAVE_DISABLE, EMMC_CLK_DIV_INIT);
        sdio_bus_mode_set(SDIO, SDIO_BUSMODE_1BIT);
        sdio_hardware_clock_disable(SDIO);

        /* select the card */
        err = emmc_card_select();
        if(EMMC_DRV_OK != err) {
            LOG_W("select fail:%d", err);
            continue;
        }

        /* get the EXT_CSD register */
        err = emmc_card_extcsd_get();
        if(EMMC_DRV_OK != err) {
            LOG_W("ext_csd fail:%d", err);
            continue;
        }

        /* parse sector count from EXT_CSD[215:212] (little-endian uint32) */
        emmc0.sector_count =
            ((uint32_t)emmc_ext_csd[EXT_CSD_SEC_CNT_B3] << 24) |
            ((uint32_t)emmc_ext_csd[EXT_CSD_SEC_CNT_B2] << 16) |
            ((uint32_t)emmc_ext_csd[EXT_CSD_SEC_CNT_B1] <<  8) |
            ((uint32_t)emmc_ext_csd[EXT_CSD_SEC_CNT_B0]);

        /* configure the bus mode */
        err = emmc_bus_mode_config();
        if(EMMC_DRV_OK != err) {
            LOG_W("bus_mode fail:%d", err);
            continue;
        }

    } while((EMMC_DRV_OK != err) && (--retry > 0U));

    if(0U == retry) {
        LOG_E("eMMC init failed!");
        return -RT_EIO;
    }

    LOG_I("eMMC init OK  sectors:%u (%u MB)", emmc0.sector_count, emmc0.sector_count / 2048U);
    LOG_I("eMMC bus width : %d-bit  DDR:%d", EMMC_BUSWIDTH, EMMC_USE_DDR);
    LOG_I("eMMC transmode : %s", (EMMC_USE_DMA ? "DMA (IDMA)" : "Polling (FIFO)"));
    return RT_EOK;
}

static rt_err_t rt_emmccard_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_emmccard_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_emmccard_read(rt_device_t dev, rt_off_t sector,
                                    void *buffer, rt_size_t count)
{
    emmc_drv_err_t  err = EMMC_DRV_OK;
    gd32_emmc_t    *emmc = (gd32_emmc_t *)dev->user_data;
    rt_size_t       i = 0U;

    LOG_D("read  sector:%d count:%d  bus:%dbit DDR:%d mode:%s",
          (int)sector, (int)count, EMMC_BUSWIDTH, EMMC_USE_DDR,
          (EMMC_USE_DMA ? "DMA" : "Polling"));

    if(NULL == buffer) {
        return 0;
    }

    rt_mutex_take(&emmc->emmc_lock, RT_WAITING_FOREVER);

    if(((uint32_t)buffer & 0x1FU) != 0U) {
        /* buffer not 32-byte aligned — use aligned bounce buffer sector by sector */
        uint8_t *dst = (uint8_t *)buffer;
        for(i = 0U; i < count; i++) {
            err = emmc_block_read(emmc_dma_buf, (uint32_t)(sector + (rt_off_t)i));
            if(EMMC_DRV_OK != err) {
                LOG_E("read fail sector:%d err:%d", (int)(sector + (rt_off_t)i), err);
                rt_mutex_release(&emmc->emmc_lock);
                return 0;
            }
            rt_memcpy(dst, emmc_dma_buf, EMMC_SECTOR_SIZE);
            dst += EMMC_SECTOR_SIZE;
        }
    } else {
        if(1U == count) {
            err = emmc_block_read((uint32_t *)buffer, (uint32_t)sector);
        } else {
            err = emmc_multiblocks_read((uint32_t *)buffer, (uint32_t)sector, (uint32_t)count);
        }
        if(EMMC_DRV_OK != err) {
            LOG_E("read fail sector:%d count:%d err:%d", (int)sector, (int)count, err);
            rt_mutex_release(&emmc->emmc_lock);
            return 0;
        }
    }

    rt_mutex_release(&emmc->emmc_lock);
    return (rt_ssize_t)count;
}

static rt_ssize_t rt_emmccard_write(rt_device_t dev, rt_off_t sector,
                                     const void *buffer, rt_size_t count)
{
    emmc_drv_err_t  err = EMMC_DRV_OK;
    gd32_emmc_t    *emmc = (gd32_emmc_t *)dev->user_data;
    rt_size_t       i = 0U;

    LOG_D("write sector:%d count:%d  bus:%dbit DDR:%d mode:%s",
          (int)sector, (int)count, EMMC_BUSWIDTH, EMMC_USE_DDR,
          (EMMC_USE_DMA ? "DMA" : "Polling"));

    if(NULL == buffer) {
        return 0;
    }

    rt_mutex_take(&emmc->emmc_lock, RT_WAITING_FOREVER);

    if(((uint32_t)buffer & 0x1FU) != 0U) {
        /* buffer not 32-byte aligned — use aligned bounce buffer sector by sector */
        const uint8_t *src = (const uint8_t *)buffer;
        for(i = 0U; i < count; i++) {
            rt_memcpy(emmc_dma_buf, src, EMMC_SECTOR_SIZE);
            err = emmc_block_write(emmc_dma_buf, (uint32_t)(sector + (rt_off_t)i));
            if(EMMC_DRV_OK != err) {
                LOG_E("write fail sector:%d err:%d", (int)(sector + (rt_off_t)i), err);
                rt_mutex_release(&emmc->emmc_lock);
                return 0;
            }
            src += EMMC_SECTOR_SIZE;
        }
    } else {
        if(1U == count) {
            err = emmc_block_write((uint32_t *)buffer, (uint32_t)sector);
        } else {
            err = emmc_multiblocks_write((uint32_t *)buffer, (uint32_t)sector, (uint32_t)count);
        }
        if(EMMC_DRV_OK != err) {
            LOG_E("write fail sector:%d count:%d err:%d", (int)sector, (int)count, err);
            rt_mutex_release(&emmc->emmc_lock);
            return 0;
        }
    }

    rt_mutex_release(&emmc->emmc_lock);
    return (rt_ssize_t)count;
}

static rt_err_t rt_emmccard_control(rt_device_t dev, int cmd, void *args)
{
    gd32_emmc_t *emmc = (gd32_emmc_t *)dev->user_data;

    if(RT_DEVICE_CTRL_BLK_GETGEOME == cmd) {
        struct rt_device_blk_geometry *geo = (struct rt_device_blk_geometry *)args;
        if(NULL == geo) {
            return -RT_ERROR;
        }
        geo->bytes_per_sector = EMMC_SECTOR_SIZE;
        geo->block_size       = EMMC_SECTOR_SIZE;
        geo->sector_count     = emmc->sector_count;
    }
    return RT_EOK;
}

/* -----------------------------------------------------------------------
 * Driver registration
 * ----------------------------------------------------------------------- */
/*!
    \brief      initialize and register the eMMC block device with RT-Thread
    \param[in]  none
    \param[out] none
    \retval     RT_EOK on success, negative value on failure
*/
int rt_hw_emmccard_init(void)
{
    emmc0.emmc_device.type      = RT_Device_Class_Block;
    emmc0.emmc_device.init      = rt_emmccard_init;
    emmc0.emmc_device.open      = rt_emmccard_open;
    emmc0.emmc_device.close     = rt_emmccard_close;
    emmc0.emmc_device.read      = rt_emmccard_read;
    emmc0.emmc_device.write     = rt_emmccard_write;
    emmc0.emmc_device.control   = rt_emmccard_control;
    emmc0.emmc_device.user_data = &emmc0;

    rt_device_register(&emmc0.emmc_device, emmc0.device_name,
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_emmccard_init);

#endif /* BSP_USING_EMMC */
