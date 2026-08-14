/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-04     zylx         The first version for STM32F4xx
 * 2023-08-20     yuanzihao    adapter gd32f4xx
 */

#ifndef __SDRAM_PORT_H__
#define __SDRAM_PORT_H__

#include <board.h>

/* parameters for sdram peripheral */
#ifndef SDRAM_DEVICE
#define SDRAM_DEVICE                    EXMC_SDRAM_DEVICE0
#endif
/* Bank1 or Bank2 */
#ifndef SDRAM_TARGET_BANK
#define SDRAM_TARGET_BANK               1
#endif
/* stm32h7 Bank1:0XC0000000  Bank2:0XD0000000 */
#ifndef SDRAM_BANK_ADDR
#define SDRAM_BANK_ADDR                 ((uint32_t)0XC0000000)
#endif
/* data width: 8, 16, 32 */
#ifndef SDRAM_DATA_WIDTH_IN_NUMBER
#define SDRAM_DATA_WIDTH_IN_NUMBER      16
#endif
#ifndef SDRAM_DATA_WIDTH
#define SDRAM_DATA_WIDTH                EXMC_SDRAM_DATABUS_WIDTH_16B
#endif
/* column bit numbers: 8, 9, 10, 11 */
#ifndef SDRAM_COLUMN_BITS
#define SDRAM_COLUMN_BITS               EXMC_SDRAM_COW_ADDRESS_9
#endif
/* row bit numbers: 11, 12, 13 */
#ifndef SDRAM_ROW_BITS
#define SDRAM_ROW_BITS                  EXMC_SDRAM_ROW_ADDRESS_13
#endif
/* cas latency clock number: 1, 2, 3 */
#ifndef SDRAM_CAS_LATENCY
#define SDRAM_CAS_LATENCY               EXMC_CAS_LATENCY_3_SDCLK
#endif
/* read pipe delay: 0, 1, 2 */
#ifndef SDRAM_RPIPE_DELAY
#define SDRAM_RPIPE_DELAY               EXMC_PIPELINE_DELAY_2_HCLK
#endif
/* clock divid: 2, 3 */
#ifndef SDCLOCK_PERIOD
#define SDCLOCK_PERIOD                  EXMC_SDCLK_PERIODS_3_HCLK
#endif
/* refresh rate counter */
#ifndef SDRAM_REFRESH_COUNT
#define SDRAM_REFRESH_COUNT             ((uint32_t)0x02A5)
#endif
#ifndef SDRAM_SIZE
#define SDRAM_SIZE                      ((uint32_t)0x2000000)
#endif
#ifndef SDRAM_TIMEOUT
#define SDRAM_TIMEOUT                   ((uint32_t)0x0000FFFF)
#endif

/* Timing configuration for W9825G6KH-6 */
/* 100 MHz of HCKL3 clock frequency (200MHz/2) */
/* TMRD: 2 Clock cycles */
#ifndef LOADTOACTIVEDELAY
#define LOADTOACTIVEDELAY               2
#endif
/* TXSR: 8x10ns */
#ifndef EXITSELFREFRESHDELAY
#define EXITSELFREFRESHDELAY            8
#endif
/* TRAS: 5x10ns */
#ifndef SELFREFRESHTIME
#define SELFREFRESHTIME                 7
#endif
/* TRC:  7x10ns */
#ifndef ROWCYCLEDELAY
#define ROWCYCLEDELAY                   5
#endif
/* TWR:  2 Clock cycles */
#ifndef WRITERECOVERYTIME
#define WRITERECOVERYTIME               2
#endif
/* TRP:  2x10ns */
#ifndef RPDELAY
#define RPDELAY                         3
#endif
/* TRCD: 2x10ns */
#ifndef RCDDELAY
#define RCDDELAY                        3
#endif

/* memory mode register */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#endif
