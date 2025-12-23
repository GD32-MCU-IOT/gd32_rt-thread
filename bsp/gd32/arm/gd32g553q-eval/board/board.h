/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 * 2024-03-19     Evlers       remove the include of drv_usart.h
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "gd32g5x3.h"
#include "drv_gpio.h"
#include "drv_hard_i2c.h"
#include "drv_usart.h"
#include "drv_spi.h"

#include "gd32g5x3_exti.h"

#define EXT_SDRAM_BEGIN    (0xC0000000U) /* the begining address of external SDRAM */
#define EXT_SDRAM_END      (EXT_SDRAM_BEGIN + (32U * 1024 * 1024)) /* the end address of external SDRAM */

/* Internal Flash: 512KB (0x08000000 - 0x0807FFFF) for GD32G553 */
#define GD32_FLASH_START_ADRESS    ((uint32_t)0x08000000)
#define GD32_FLASH_SIZE            (512 * 1024)
#define GD32_FLASH_END_ADDRESS     ((uint32_t)(GD32_FLASH_START_ADRESS + GD32_FLASH_SIZE))

/* Internal SRAM: 128KB (0x20000000 - 0x2001FFFF) for GD32G553 */
/* GD32G553 Peripherals: USART0/1/2, UART3/4, I2C0/1/2/3, SPI0/1/2 */
#ifdef __ICCARM__
/* Use *.icf ram symbol, to avoid hardcode */
extern char __ICFEDIT_region_RAM_end__;
#define GD32_SRAM_END          &__ICFEDIT_region_RAM_end__
#else
#define GD32_SRAM_SIZE         128
#define GD32_SRAM_END          (0x20000000 + GD32_SRAM_SIZE * 1024)
#endif

#ifdef __ARMCC_VERSION
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#endif

#define HEAP_END          GD32_SRAM_END

#endif

