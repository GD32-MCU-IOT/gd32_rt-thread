/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-27     RT-Thread    first implementation for GD32F5HC
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "gd32w51x_f5hc.h"
#include "drv_gpio.h"

// <o> Internal SRAM memory size[Kbytes] <8-512>
//  <i>Default: 320
#ifdef __ICCARM__
// Use *.icf ram symbal, to avoid hardcode.
extern char __ICFEDIT_region_RAM_end__;
#define GD32_SRAM_END          &__ICFEDIT_region_RAM_end__
#else
#define GD32_SRAM_SIZE         320
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

/*
 * DMA Channel Allocation for GD32F5HC-EVAL:
 * ============================================================
 * DMA0 Channel0 - I2C0_RX    (subperi 1)
 * DMA0 Channel1 - UART2_RX   (subperi 4)  [console]
 * DMA0 Channel2 - I2C1_RX    (subperi 7)
 * DMA0 Channel3 - UART2_TX   (subperi 4)  [console]
 * DMA0 Channel4 - SPI1_TX    (subperi 0)
 * DMA0 Channel5 - SPI0_TX    (subperi 3)
 * DMA0 Channel6 - I2C0_TX    (subperi 1)
 * DMA0 Channel7 - I2C1_TX    (subperi 7)
 * ------------------------------------------------------------
 * DMA1 Channel3 - SPI1_RX    (subperi 0)
 * ============================================================
 * Note: SPI0_RX (DMA0 CH3 SUBPERI3) conflicts with UART2_TX.
 *       If SPI0 DMA is needed alongside UART2 DMA TX, disable
 *       BSP_UART2_TX_USING_DMA and use polling TX for console.
 */

/* I2C0 DMA: TX on DMA0_CH6, RX on DMA0_CH0 */
#if defined(BSP_I2C0_TX_USING_DMA) && !defined(I2C0_TX_DMA_PERIPH)
#define I2C0_DMA_TX_IRQHandler          DMA0_Channel6_IRQHandler
#define I2C0_TX_DMA_PERIPH              DMA0
#define I2C0_TX_DMA_RCU                 RCU_DMA0
#define I2C0_TX_DMA_CHANNEL             DMA_CH6
#define I2C0_TX_DMA_IRQ                 DMA0_Channel6_IRQn
#define I2C0_TX_DMA_SUBPERI             DMA_SUBPERI1
#endif

#if defined(BSP_I2C0_RX_USING_DMA) && !defined(I2C0_RX_DMA_PERIPH)
#define I2C0_DMA_RX_IRQHandler          DMA0_Channel0_IRQHandler
#define I2C0_RX_DMA_PERIPH              DMA0
#define I2C0_RX_DMA_RCU                 RCU_DMA0
#define I2C0_RX_DMA_CHANNEL             DMA_CH0
#define I2C0_RX_DMA_IRQ                 DMA0_Channel0_IRQn
#define I2C0_RX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* I2C1 DMA: TX on DMA0_CH7, RX on DMA0_CH2 */
#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_PERIPH)
#define I2C1_DMA_TX_IRQHandler          DMA0_Channel7_IRQHandler
#define I2C1_TX_DMA_PERIPH              DMA0
#define I2C1_TX_DMA_RCU                 RCU_DMA0
#define I2C1_TX_DMA_CHANNEL             DMA_CH7
#define I2C1_TX_DMA_IRQ                 DMA0_Channel7_IRQn
#define I2C1_TX_DMA_SUBPERI             DMA_SUBPERI7
#endif

#if defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_PERIPH)
#define I2C1_DMA_RX_IRQHandler          DMA0_Channel2_IRQHandler
#define I2C1_RX_DMA_PERIPH              DMA0
#define I2C1_RX_DMA_RCU                 RCU_DMA0
#define I2C1_RX_DMA_CHANNEL             DMA_CH2
#define I2C1_RX_DMA_IRQ                 DMA0_Channel2_IRQn
#define I2C1_RX_DMA_SUBPERI             DMA_SUBPERI7
#endif

/* SPI0 DMA: TX on DMA0_CH5, RX on DMA0_CH3 */
#ifdef BSP_USING_SPI_DMA
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_TX_DMA_PERIPH)
#define SPI0_DMA_TX_IRQHandler          DMA0_Channel5_IRQHandler
#define SPI0_TX_DMA_PERIPH              DMA0
#define SPI0_TX_DMA_RCU                 RCU_DMA0
#define SPI0_TX_DMA_CHANNEL             DMA_CH5
#define SPI0_TX_DMA_IRQ                 DMA0_Channel5_IRQn
#define SPI0_TX_DMA_SUBPERI             DMA_SUBPERI3
#endif

#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_RX_DMA_PERIPH)
#define SPI0_DMA_RX_IRQHandler          DMA0_Channel3_IRQHandler
#define SPI0_RX_DMA_PERIPH              DMA0
#define SPI0_RX_DMA_RCU                 RCU_DMA0
#define SPI0_RX_DMA_CHANNEL             DMA_CH3
#define SPI0_RX_DMA_IRQ                 DMA0_Channel3_IRQn
#define SPI0_RX_DMA_SUBPERI             DMA_SUBPERI3
#endif

/* SPI1 DMA: TX on DMA0_CH4, RX on DMA1_CH3 */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_TX_DMA_PERIPH)
#define SPI1_DMA_TX_IRQHandler          DMA0_Channel4_IRQHandler
#define SPI1_TX_DMA_PERIPH              DMA0
#define SPI1_TX_DMA_RCU                 RCU_DMA0
#define SPI1_TX_DMA_CHANNEL             DMA_CH4
#define SPI1_TX_DMA_IRQ                 DMA0_Channel4_IRQn
#define SPI1_TX_DMA_SUBPERI             DMA_SUBPERI0
#endif

#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_RX_DMA_PERIPH)
#define SPI1_DMA_RX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI1_RX_DMA_PERIPH              DMA1
#define SPI1_RX_DMA_RCU                 RCU_DMA1
#define SPI1_RX_DMA_CHANNEL             DMA_CH3
#define SPI1_RX_DMA_IRQ                 DMA1_Channel3_IRQn
#define SPI1_RX_DMA_SUBPERI             DMA_SUBPERI0
#endif
#endif /* BSP_USING_SPI_DMA */

/* UART0 DMA: TX on DMA1_CH7, RX on DMA1_CH2 */
#if defined(BSP_UART0_TX_USING_DMA) && !defined(UART0_TX_DMA_PERIPH)
#define UART0_DMA_TX_IRQHandler         DMA1_Channel7_IRQHandler
#define UART0_TX_DMA_PERIPH             DMA1
#define UART0_TX_DMA_RCU                RCU_DMA1
#define UART0_TX_DMA_CHANNEL            DMA_CH7
#define UART0_TX_DMA_IRQ                DMA1_Channel7_IRQn
#define UART0_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

#if defined(BSP_UART0_RX_USING_DMA) && !defined(UART0_RX_DMA_PERIPH)
#define UART0_DMA_RX_IRQHandler         DMA1_Channel2_IRQHandler
#define UART0_RX_DMA_PERIPH             DMA1
#define UART0_RX_DMA_RCU                RCU_DMA1
#define UART0_RX_DMA_CHANNEL            DMA_CH2
#define UART0_RX_DMA_IRQ                DMA1_Channel2_IRQn
#define UART0_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* UART1 DMA: TX on DMA0_CH6, RX on DMA0_CH5 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_PERIPH)
#define UART1_DMA_TX_IRQHandler         DMA0_Channel6_IRQHandler
#define UART1_TX_DMA_PERIPH             DMA0
#define UART1_TX_DMA_RCU                RCU_DMA0
#define UART1_TX_DMA_CHANNEL            DMA_CH6
#define UART1_TX_DMA_IRQ                DMA0_Channel6_IRQn
#define UART1_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_PERIPH)
#define UART1_DMA_RX_IRQHandler         DMA0_Channel5_IRQHandler
#define UART1_RX_DMA_PERIPH             DMA0
#define UART1_RX_DMA_RCU                RCU_DMA0
#define UART1_RX_DMA_CHANNEL            DMA_CH5
#define UART1_RX_DMA_IRQ                DMA0_Channel5_IRQn
#define UART1_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* UART2 DMA (Console): TX on DMA0_CH3, RX on DMA0_CH1 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_PERIPH)
#define UART2_DMA_TX_IRQHandler         DMA0_Channel3_IRQHandler
#define UART2_TX_DMA_PERIPH             DMA0
#define UART2_TX_DMA_RCU                RCU_DMA0
#define UART2_TX_DMA_CHANNEL            DMA_CH3
#define UART2_TX_DMA_IRQ                DMA0_Channel3_IRQn
#define UART2_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_PERIPH)
#define UART2_DMA_RX_IRQHandler         DMA0_Channel1_IRQHandler
#define UART2_RX_DMA_PERIPH             DMA0
#define UART2_RX_DMA_RCU                RCU_DMA0
#define UART2_RX_DMA_CHANNEL            DMA_CH1
#define UART2_RX_DMA_IRQ                DMA0_Channel1_IRQn
#define UART2_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif

#endif /* __BOARD_H__ */
