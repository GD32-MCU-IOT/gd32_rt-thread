/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-22     RT-Thread    first implementation for GD32F50x
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "gd32f50x.h"
#include "drv_gpio.h"
#include "drv_hard_i2c.h"
#include "drv_usart.h"
#include "drv_spi.h"
#include "drv_qspi.h"

/* Internal SRAM memory configuration for GD32F503V */
/* GD32F503V series contains up to 128KB on-chip SRAM */
/* <o> Internal SRAM memory size[Kbytes] <8-128>*/
/* <i>Default: 128*/
#ifdef __ICCARM__
/* Use *.icf ram symbal, to avoid hardcode.*/
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

/* SPI/QSPI Flash CS pin definitions */
#ifndef BSP_SPI0_FLASH_CS_PIN
#define BSP_SPI0_FLASH_CS_PIN       GET_PIN(A, 4)
#endif

#ifndef BSP_SPI1_FLASH_CS_PIN
#define BSP_SPI1_FLASH_CS_PIN       GET_PIN(B, 12)
#endif

#ifndef BSP_QSPI0_FLASH_CS_PIN
#define BSP_QSPI0_FLASH_CS_PIN     GET_PIN(A, 4)
#endif

#endif /* __BOARD_H__ */
