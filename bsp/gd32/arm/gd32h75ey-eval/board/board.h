/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "gd32h75e.h"
#include "drv_gpio.h"
#include "drv_hard_i2c.h"
#include "drv_usart.h"
#include "drv_spi.h"

#define EXT_SDRAM_BEGIN    (0xC0000000U) /* the begining address of external SDRAM */
#define EXT_SDRAM_END      (EXT_SDRAM_BEGIN + (32U * 1024 * 1024)) /* the end address of external SDRAM */

/* Internal SRAM memory configuration for GD32H75E */
/* GD32H75E series contains up to 512KB on-chip SRAM (AXI SRAM) */
/* <o> Internal SRAM memory size[Kbytes] <8-512>*/
/* <i>Default: 512*/
#ifdef __ICCARM__
/* Use *.icf ram symbal, to avoid hardcode.*/
extern char __ICFEDIT_region_RAM_end__;
#define GD32_SRAM_END          &__ICFEDIT_region_RAM_end__
#else

#define GD32_SRAM_SIZE         512  // 512KB AXI SRAM
#define GD32_SRAM_END          (0x24000000 + GD32_SRAM_SIZE * 1024)

#if defined(__ICCARM__) || defined(__IAR_SYSTEMS_ICC__)
    #ifndef __COMPILER_BARRIER
        #define __COMPILER_BARRIER() __asm volatile("" ::: "memory")
    #endif
#endif

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

#endif /* __BOARD_H__ */
