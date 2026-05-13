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

/*
 * Board-level DMA override policy:
 * 1. Treat config/h75e/dma_config.h as the family-level truth table.
 * 2. Check the DMA-enabled peripherals selected by rtconfig.h.
 * 3. Add board.h overrides only when the board's intended DMA set shares the
 *    same DMA controller and channel.
 *
 * GD32H75EY-EVAL default DMA set from rtconfig.h:
 *   - UART3 RX/TX DMA: DMA1 CH0/1
 *   - SPI4 RX/TX DMA:  DMA1 CH6/7
 *   - I2C3 bus enabled, DMA disabled by default
 *
 * Board decision:
 *   - No board-level DMA override is needed for the default configuration.
 *   - If I2C3 DMA is enabled later, it still uses DMA0 CH4/5 and does not
 *     collide with the default UART3 or SPI4 DMA paths.
 *   - Add overrides only if this board later enables another DMA client from
 *     the same family conflict groups, such as UART2 or SPI5 on DMA0 CH4/5.
 */

#endif /* __BOARD_H__ */
