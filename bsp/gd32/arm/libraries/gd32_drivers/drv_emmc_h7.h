/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-03-16     auto         eMMC driver for GD32H7xx (parallel to SD drv_sdio_h7)
 *
 * eMMC is connected to SDIO0 with 8-bit capable GPIO:
 *   CLK  : PC12     CMD  : PD2
 *   D0   : PC8      D1   : PC9      D2   : PC10     D3   : PC11
 *   D4   : PB8      D5   : PB9      D6   : PC6      D7   : PC7
 *
 * Note: SDIO0 is shared with the SD card driver (drv_sdio_h7.c).
 *       Only one should be active at a time.
 */

#ifndef __DRV_EMMC_H7_H__
#define __DRV_EMMC_H7_H__

#include <board.h>

/* -----------------------------------------------------------------------
 * Clock configuration
 * PLL1R = HXTAL(25MHz) / 5 * 40 / 1 = 200MHz
 * Init   clock: 200MHz / (500+2) ≈ 397kHz
 * Trans  clock: 200MHz / (8+2)   = 20MHz  (high-speed SDR)
 * ----------------------------------------------------------------------- */
#define EMMC_CLK_DIV_INIT    ((uint16_t)0x01F4)
#define EMMC_CLK_DIV_TRANS   ((uint16_t)0x0008)

/* -----------------------------------------------------------------------
 * Bus width: use a plain integer so that #if comparisons work.
 *   1 = 1-bit SDR
 *   4 = 4-bit SDR (default)
 *   8 = 8-bit SDR / DDR
 * Data rate: 0 = SDR (default), 1 = DDR
 * ----------------------------------------------------------------------- */
#define EMMC_BUSWIDTH        4      /* 1 / 4 / 8 */
#define EMMC_USE_DDR         0      /* 0=SDR  1=DDR */

/* Derived SDIO register value for runtime use (not in #if!) */
#if   (EMMC_BUSWIDTH == 8)
  #define EMMC_BUSMODE_REG   SDIO_BUSMODE_8BIT
#elif (EMMC_BUSWIDTH == 4)
  #define EMMC_BUSMODE_REG   SDIO_BUSMODE_4BIT
#else
  #define EMMC_BUSMODE_REG   SDIO_BUSMODE_1BIT
#endif

/* -----------------------------------------------------------------------
 * Transfer mode: select POLLING (CPU FIFO) or DMA (SDIO IDMA + interrupt)
 *   EMMC_DMA_MODE     = 0x00000000  (IDMA + SDIO0 interrupt)
 *   EMMC_POLLING_MODE = 0x00000001  (CPU polls FIFO directly, no ISR)
 * Set EMMC_TRANSMODE to choose the compile-time default.
 * ----------------------------------------------------------------------- */
#define EMMC_DMA_MODE             ((uint32_t)0x00000000U)   /* DMA (IDMA) mode */
#define EMMC_POLLING_MODE         ((uint32_t)0x00000001U)   /* polling mode */

/* Compile-time mode selector for #if guards: set 1 for DMA, 0 for Polling.
 * EMMC_TRANSMODE (runtime initial value) is derived automatically. */
#define EMMC_USE_DMA              0   /* 1 = DMA (IDMA + IRQ),  0 = Polling (FIFO) */

#if EMMC_USE_DMA
  #define EMMC_TRANSMODE          EMMC_DMA_MODE
#else
  #define EMMC_TRANSMODE          EMMC_POLLING_MODE
#endif

/* -----------------------------------------------------------------------
 * eMMC CID register fields (JEDEC JESD84-B51, v4+ format)
 * SDIO RESPONSE0 = CID[127:96], RESPONSE1 = CID[95:64],
 * RESPONSE2 = CID[63:32],  RESPONSE3 = CID[31:0]
 * ----------------------------------------------------------------------- */
typedef struct {
    uint8_t  mid;        /* manufacturer ID [127:120] */
    uint16_t oid;        /* OEM/app ID raw 16-bit: CBX[15:14], rsvd[13:10], OID[7:0] — [119:104] */
    char     pnm[7];     /* product name, 6 ASCII chars, null-terminated [103:56] */
    uint8_t  prv;        /* product revision (high nibble=major, low nibble=minor) [55:48] */
    uint32_t psn;        /* product serial number [47:16] */
    uint8_t  mdt_month;  /* manufacturing month 1-12 [15:12] */
    uint16_t mdt_year;   /* manufacturing year = raw 4-bit + 1997 [11:8] */
    uint8_t  cid_crc;    /* CID CRC7 [7:1] */
} emmc_cid_struct;

/* -----------------------------------------------------------------------
 * eMMC CSD register fields (JEDEC JESD84-B51, CSD v1.x format)
 * For eMMC v4+, capacity must be read from EXT_CSD SEC_CNT, not C_SIZE.
 * ----------------------------------------------------------------------- */
typedef struct {
    uint8_t  csd_struct;          /* CSD structure version [7:6] of byte 0 */
    uint8_t  spec_vers;           /* SPEC_VERS, eMMC version nibble [5:2] of byte 0 */
    uint8_t  taac;                /* data read access-time 1 */
    uint8_t  nsac;                /* data read access-time 2 in clock cycles */
    uint8_t  tran_speed;          /* max data transfer rate */
    uint16_t ccc;                 /* card command classes */
    uint8_t  read_bl_len;         /* max read data block length (log2) */
    uint8_t  read_bl_partial;     /* partial blocks for read allowed */
    uint8_t  write_blk_misalign;  /* write block misalignment */
    uint8_t  read_blk_misalign;   /* read block misalignment */
    uint8_t  dsp_imp;             /* DSR implemented */
    uint32_t c_size;              /* device size, 12 bits */
    uint8_t  vdd_r_curr_min;      /* max read current at VDD min */
    uint8_t  vdd_r_curr_max;      /* max read current at VDD max */
    uint8_t  vdd_w_curr_min;      /* max write current at VDD min */
    uint8_t  vdd_w_curr_max;      /* max write current at VDD max */
    uint8_t  c_size_mult;         /* device size multiplier, 3 bits */
    uint8_t  erase_grp_size;      /* erase group size, 5 bits (eMMC) */
    uint8_t  erase_grp_mult;      /* erase group size multiplier, 5 bits (eMMC) */
    uint8_t  wp_grp_size;         /* write protect group size, 5 bits */
    uint8_t  wp_grp_enable;       /* write protect group enable */
    uint8_t  r2w_factor;          /* write speed factor, 3 bits */
    uint8_t  write_bl_len;        /* max write data block length (log2), 4 bits */
    uint8_t  write_bl_partial;    /* partial blocks for write allowed */
    uint8_t  perm_write_protect;  /* permanent write protection */
    uint8_t  tmp_write_protect;   /* temporary write protection */
    uint8_t  csd_crc;             /* CSD CRC7 */
} emmc_csd_struct;

/* -----------------------------------------------------------------------
 * eMMC card information summary
 * ----------------------------------------------------------------------- */
typedef struct {
    emmc_cid_struct card_cid;      /* parsed CID fields */
    emmc_csd_struct card_csd;      /* parsed CSD fields */
    uint64_t        card_capacity; /* card capacity in bytes (from EXT_CSD SEC_CNT) */
    uint32_t        card_blocksize;/* card block size in bytes (always 512 for eMMC) */
    uint16_t        card_rca;      /* relative card address */
    uint8_t         ext_csd_rev;   /* EXT_CSD[192]: EXT_CSD revision */
    uint8_t         hs_timing;     /* EXT_CSD[185]: HS_TIMING (0=compat,1=HS,2=HS200) */
    uint8_t         bus_width;     /* EXT_CSD[183]: BUS_WIDTH register value */
} emmc_card_info_struct;

/* -----------------------------------------------------------------------
 * eMMC driver error codes
 * ----------------------------------------------------------------------- */
typedef enum {
    EMMC_DRV_OK = 0,
    EMMC_DRV_ERROR,
    EMMC_DRV_CMD_CRC_ERROR,
    EMMC_DRV_DATA_CRC_ERROR,
    EMMC_DRV_CMD_TIMEOUT,
    EMMC_DRV_DATA_TIMEOUT,
    EMMC_DRV_TX_UNDERRUN,
    EMMC_DRV_RX_OVERRUN,
    EMMC_DRV_PARAM_ERROR,
    EMMC_DRV_ILLEGAL_CMD,
    EMMC_DRV_LOCK_FAILED,
    EMMC_DRV_DMA_ERROR,
    EMMC_DRV_VOLTRANGE_INVALID,
    EMMC_DRV_OPERATION_IMPROPER,
} emmc_drv_err_t;

/* ISR processing function — call from SDIO0_IRQHandler when DMA mode is used */
emmc_drv_err_t emmc_isr_process(void);

/* card information — parse CID/CSD/EXT_CSD into a structured result */
emmc_drv_err_t emmc_card_information_get(emmc_card_info_struct *pcardinfo);

/* Registration entry point (called automatically via INIT_DEVICE_EXPORT) */
int rt_hw_emmccard_init(void);

#endif /* __DRV_EMMC_H7_H__ */
