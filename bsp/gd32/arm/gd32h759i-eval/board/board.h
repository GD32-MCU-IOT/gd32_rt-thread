/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-03-17     RT-Thread    first implementation
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "gd32h7xx.h"
#include "drv_gpio.h"
#include "drv_hard_i2c.h"
#include "drv_usart.h"
#include "drv_spi.h"

#include "gd32h7xx_exti.h"

#define EXT_SDRAM_BEGIN    (0xC0000000U) /* the begining address of external SDRAM */
#define EXT_SDRAM_END      (EXT_SDRAM_BEGIN + (32U * 1024 * 1024)) /* the end address of external SDRAM */

/* <o> Internal SRAM memory size[Kbytes] <8-512>*/
/* <i>Default: 512*/
#ifdef __ICCARM__
/* Use *.icf ram symbal, to avoid hardcode.*/
extern char __ICFEDIT_region_RAM_end__;
#define GD32_SRAM_END          &__ICFEDIT_region_RAM_end__
#else
#define GD32_SRAM_SIZE         512
#define GD32_SRAM_END          (0x24000000 + GD32_SRAM_SIZE * 1024)
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
 * 1. Treat config/h7xx/dma_config.h as the family-level truth table.
 * 2. Check the DMA-enabled peripherals selected by rtconfig.h.
 * 3. Add board.h overrides only when the board's intended DMA set shares the
 *    same DMA controller and channel.
 *
 * GD32H759I-EVAL default DMA set from rtconfig.h:
 *   - UART3 RX/TX DMA: DMA1 CH0/1
 *   - SPI3 RX/TX DMA:  DMA1 CH4/5
 *   - I2C1 bus enabled, DMA optional
 *
 * Board decision:
 *   - Keep UART3 on DMA1 CH0/1 for the default DMA demo path.
 *   - Keep SPI3 on DMA1 CH4/5.
 *   - If I2C1 DMA is enabled, move it from the family default DMA1 CH0/1 to
 *     DMA0 CH2/3 so it does not collide with UART3 DMA.
 */

/* I2C1 RX DMA override: DMA0 Channel2 instead of the family default DMA1 CH0 */
#if defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_PERIPH)
#define I2C1_DMA_RX_IRQHandler          DMA0_Channel2_IRQHandler
#define I2C1_RX_DMA_PERIPH              DMA0
#define I2C1_RX_DMA_FLAG                DMA_INTF_FTFIF
#define I2C1_RX_DMA_RCU                 RCU_DMA0
#define I2C1_RX_DMA_CHANNEL             DMA_CH2
#define I2C1_RX_DMA_REQUEST             DMA_REQUEST_I2C1_RX
#define I2C1_RX_DMA_IRQ                 DMA0_Channel2_IRQn
#endif

/* I2C1 TX DMA override: DMA0 Channel3 instead of the family default DMA1 CH1 */
#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_PERIPH)
#define I2C1_DMA_TX_IRQHandler          DMA0_Channel3_IRQHandler
#define I2C1_TX_DMA_PERIPH              DMA0
#define I2C1_TX_DMA_FLAG                DMA_INTF_FTFIF
#define I2C1_TX_DMA_RCU                 RCU_DMA0
#define I2C1_TX_DMA_CHANNEL             DMA_CH3
#define I2C1_TX_DMA_REQUEST             DMA_REQUEST_I2C1_TX
#define I2C1_TX_DMA_IRQ                 DMA0_Channel3_IRQn
#endif

#endif /* __BOARD_H__ */
