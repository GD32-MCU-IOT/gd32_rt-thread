/*!
    \file    drv_sd_h7.h
    \brief   SD card driver header for GD32H7xx (RT-Thread adaptation)

             SD card is connected to SDIO0 with 4-bit GPIO (same physical pins as eMMC):
               CLK  : PC12     CMD  : PD2
               D0   : PC8      D1   : PC9      D2   : PC10     D3   : PC11

             Note: SDIO0 is shared with the eMMC driver (drv_emmc_h7.c).
                   Only one of BSP_USING_SD / BSP_USING_EMMC should be active at a time.

             Speed/bus defaults can be overridden before including this header:
               #define SD_CONF_BUSMODE  SDIO_BUSMODE_1BIT
               #define SD_CONF_SPEED    SD_SPEED_DEFAULT
*/

/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_SD_H7_H__
#define __DRV_SD_H7_H__

#include <board.h>

/* -----------------------------------------------------------------------
 * Clock configuration
 * PLL1R = HXTAL(25MHz) / 5 * 40 / 1 = 200MHz
 * ----------------------------------------------------------------------- */
#define SD_CLK_DIV_INIT              ((uint32_t)0x01F4)   /* ~397 kHz  init clock      */
#define SD_CLK_DIV_TRANS_DSPEED      ((uint32_t)0x0008)   /* ~20  MHz  default speed   */
#define SD_CLK_DIV_TRANS_HSPEED      ((uint32_t)0x0004)   /* ~33  MHz  high speed      */
#define SD_CLK_DIV_TRANS_SDR25SPEED  ((uint32_t)0x0004)   /* ~33  MHz  SDR25           */
#define SD_CLK_DIV_TRANS_SDR50SPEED  ((uint32_t)0x0002)   /* ~50  MHz  SDR50           */
#define SD_CLK_DIV_TRANS_SDR104SPEED ((uint32_t)0x0001)   /* ~100 MHz  SDR104          */
#define SD_CLK_DIV_TRANS_DDR50SPEED  ((uint32_t)0x0004)   /* ~33  MHz  DDR50           */
/* backward-compatible alias */
#define SD_CLK_DIV_TRANS             SD_CLK_DIV_TRANS_HSPEED

/* -----------------------------------------------------------------------
 * Speed mode defines (match official sdcard.h reference)
 * ----------------------------------------------------------------------- */
#define SD_SPEED_DEFAULT    ((uint32_t)0x00000000U)   /* up to 25 MHz */
#define SD_SPEED_HIGH       ((uint32_t)0x00000001U)   /* up to 50 MHz, CMD6 switch */
#define SD_SPEED_SDR25      ((uint32_t)0x80FFFF01U)   /* UHS-I SDR25  (1.8 V) */
#define SD_SPEED_SDR50      ((uint32_t)0x80FF1F02U)   /* UHS-I SDR50  (1.8 V) */
#define SD_SPEED_SDR104     ((uint32_t)0x80FF1F03U)   /* UHS-I SDR104 (1.8 V) */
#define SD_SPEED_DDR50      ((uint32_t)0x80FF1F04U)   /* UHS-I DDR50  (1.8 V) */

/* -----------------------------------------------------------------------
 * Transfer mode: DMA (IDMA + SDIO0 interrupt) or Polling (CPU FIFO)
 * ----------------------------------------------------------------------- */
#define SD_DMA_MODE             ((uint32_t)0x00000000U)
#define SD_POLLING_MODE         ((uint32_t)0x00000001U)

#define SD_USE_DMA              0   /* 1 = DMA (IDMA + IRQ),  0 = Polling (FIFO) */

#if SD_USE_DMA
  #define SD_TRANSMODE          SD_DMA_MODE
#else
  #define SD_TRANSMODE          SD_POLLING_MODE
#endif

/* -----------------------------------------------------------------------
 * Bus mode, speed and transfer-mode defaults for rt_sdcard_init().
 * Override with #define before including this header or via Kconfig.
 * ----------------------------------------------------------------------- */
#ifndef SD_CONF_BUSMODE
  #define SD_CONF_BUSMODE   SDIO_BUSMODE_4BIT   /* SDIO_BUSMODE_1BIT or SDIO_BUSMODE_4BIT */
#endif
#ifndef SD_CONF_SPEED
  #define SD_CONF_SPEED     SD_SPEED_HIGH
#endif
#ifndef SD_CONF_DTMODE
  #define SD_CONF_DTMODE    SD_TRANSMODE
#endif

/* -----------------------------------------------------------------------
 * Card capacity type (returned by sd_card_capacity_get())
 * ----------------------------------------------------------------------- */
#define SD_SDSC             ((uint32_t)0U)   /* standard capacity */
#define SD_SDHC_SDXC        ((uint32_t)1U)   /* high / extended capacity */

/* Card command class bits extracted from CSD[95:84] */
#define SD_CCC_ERASE        ((uint16_t)0x0020U)
#define SD_CCC_LOCK_CARD    ((uint16_t)0x0080U)

/* -----------------------------------------------------------------------
 * Card type enum (matches sdcard.h sdio_card_type_enum)
 * ----------------------------------------------------------------------- */
typedef enum {
    SDIO_STD_CAPACITY_SD_CARD_V1_1 = 0,  /* SD 1.x, SDSC */
    SDIO_STD_CAPACITY_SD_CARD_V2_0,      /* SD 2.0, SDSC */
    SDIO_STD_CAPACITY_SD_CARD_V3_0,      /* SD 3.0, SDSC */
    SDIO_HIGH_CAPACITY_SD_CARD,          /* SDHC / SDXC  */
    SDIO_SECURE_DIGITAL_IO_CARD,
    SDIO_HIGH_SPEED_MULTIMEDIA_CARD,
    SDIO_SECURE_DIGITAL_IO_COMBO_CARD,
    SDIO_HIGH_CAPACITY_MMC_CARD,
    SDIO_MULTIMEDIA_CARD,
} sdio_card_type_enum;

/* -----------------------------------------------------------------------
 * CID register fields (matches sdcard.h sd_cid_struct)
 * ----------------------------------------------------------------------- */
typedef struct {
    uint8_t  mid;       /* manufacturer ID */
    uint16_t oid;       /* OEM/application ID */
    uint32_t pnm0;      /* product name bytes [0..3] */
    uint8_t  pnm1;      /* product name byte [4] */
    uint8_t  prv;       /* product revision */
    uint32_t psn;       /* product serial number */
    uint16_t mdt;       /* manufacturing date (BCD YYMM since 2000) */
    uint8_t  cid_crc;   /* CID CRC7 */
} sd_cid_struct;

/* -----------------------------------------------------------------------
 * CSD register fields (matches sdcard.h sd_csd_struct)
 * ----------------------------------------------------------------------- */
typedef struct {
    uint8_t  csd_struct;         /* CSD structure version */
    uint8_t  taac;               /* data read access-time 1 */
    uint8_t  nsac;               /* data read access-time 2 (clocks) */
    uint8_t  tran_speed;         /* max data transfer rate */
    uint16_t ccc;                /* card command classes */
    uint8_t  read_bl_len;        /* max read data block length */
    uint8_t  read_bl_partial;    /* partial blocks for read allowed */
    uint8_t  write_blk_misalign; /* write block misalignment */
    uint8_t  read_blk_misalign;  /* read block misalignment */
    uint8_t  dsp_imp;            /* DSR implemented */
    uint32_t c_size;             /* device size */
    uint8_t  vdd_r_curr_min;     /* max read current @ VDD min */
    uint8_t  vdd_r_curr_max;     /* max read current @ VDD max */
    uint8_t  vdd_w_curr_min;     /* max write current @ VDD min */
    uint8_t  vdd_w_curr_max;     /* max write current @ VDD max */
    uint8_t  c_size_mult;        /* device size multiplier */
    uint8_t  erase_blk_en;       /* erase single block enable */
    uint8_t  sector_size;        /* erase sector size */
    uint8_t  wp_grp_size;        /* write protect group size */
    uint8_t  wp_grp_enable;      /* write protect group enable */
    uint8_t  r2w_factor;         /* write speed factor */
    uint8_t  write_bl_len;       /* max write data block length */
    uint8_t  write_bl_partial;   /* partial blocks for write allowed */
    uint8_t  file_format_grp;    /* file format group */
    uint8_t  copy_flag;          /* copy flag */
    uint8_t  perm_write_protect; /* permanent write protection */
    uint8_t  tmp_write_protect;  /* temporary write protection */
    uint8_t  file_format;        /* file format */
    uint8_t  csd_crc;            /* CSD CRC7 */
} sd_csd_struct;

/* -----------------------------------------------------------------------
 * SD card information (matches sdcard.h sd_card_info_struct)
 * ----------------------------------------------------------------------- */
typedef struct {
    sd_cid_struct       card_cid;       /* parsed CID fields */
    sd_csd_struct       card_csd;       /* parsed CSD fields */
    sdio_card_type_enum card_type;      /* card type enum */
    uint64_t            card_capacity;  /* card capacity in bytes (uint64_t to avoid overflow for >4GB) */
    uint32_t            card_blocksize; /* card block size in bytes */
    uint16_t            card_rca;       /* card relative address */
} sd_card_info_struct;

/* -----------------------------------------------------------------------
 * SD card driver error codes
 * ----------------------------------------------------------------------- */
typedef enum {
    SD_DRV_OK = 0,
    SD_DRV_ERROR,
    SD_DRV_CMD_CRC_ERROR,
    SD_DRV_DATA_CRC_ERROR,
    SD_DRV_CMD_TIMEOUT,
    SD_DRV_DATA_TIMEOUT,
    SD_DRV_TX_UNDERRUN,
    SD_DRV_RX_OVERRUN,
    SD_DRV_PARAM_ERROR,
    SD_DRV_ILLEGAL_CMD,
    SD_DRV_LOCK_FAILED,
    SD_DRV_DMA_ERROR,
    SD_DRV_VOLTRANGE_INVALID,
    SD_DRV_UNSUPPORTED_CARD,
    SD_DRV_OPERATION_IMPROPER,
} sd_drv_err_t;


/* SCR register content (two 32-bit words, global accessible from test code) */
extern uint32_t sd_scr[2];

/* ISR processing function — call from SDIO0_IRQHandler when DMA mode is used */
sd_drv_err_t sd_isr_process(void);

/* -----------------------------------------------------------------------
 * Public API (matches sdcard.h reference functions)
 * ----------------------------------------------------------------------- */

/* bus & transfer mode configuration (called at init; re-callable) */
sd_drv_err_t sd_bus_mode_config(uint32_t busmode, uint32_t speed);
sd_drv_err_t sd_transfer_mode_config(uint32_t txmode);

/* card information */
sd_drv_err_t sd_card_information_get(sd_card_info_struct *pcardinfo);
uint32_t     sd_card_capacity_get(void);
sd_drv_err_t sd_cardstatus_get(uint32_t *pcardstatus);

/* card operations */
sd_drv_err_t sd_erase(uint32_t startaddr, uint32_t endaddr);
sd_drv_err_t sd_transfer_stop(void);
sd_drv_err_t sd_card_select_deselect(uint16_t cardrca);

/* Registration entry point (called automatically via INIT_DEVICE_EXPORT) */
int rt_hw_sdcard_init(void);

#endif /* __DRV_SD_H7_H__ */
