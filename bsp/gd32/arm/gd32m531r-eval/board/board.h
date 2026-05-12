/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-13     RT-Thread    first implementation for GD32M53x
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "gd32m53x.h"
#include "drv_gpio.h"
#include "drv_hard_i2c.h"
#include "drv_usart.h"
#include "drv_spi.h"

/* Internal SRAM memory configuration for GD32M531R */
/* GD32M531R series contains 32KB on-chip SRAM */
/* <o> Internal SRAM memory size[Kbytes] <32>*/
/* <i>Default: 32*/
#define GD32_SRAM_SIZE         32
#define GD32_SRAM_END          (0x20000000 + GD32_SRAM_SIZE * 1024)

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

#endif /* __BOARD_H__ */
