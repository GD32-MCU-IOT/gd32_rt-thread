/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-30     RT-Thread    first implementation for GD32G5x3
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * DMA Channel Allocation for GD32G5x3 (with DMAMUX):
 * GD32G5x3 has 2 DMA controllers (DMA0, DMA1) with 8 channels each.
 * DMAMUX allows flexible routing of DMA requests to any channel.
 *
 * Channel allocation table for GD32G5x3:
 * ============================================================
 * DMA0 Channel0 - UART0_RX
 * DMA0 Channel1 - UART0_TX
 * DMA0 Channel2 - UART1_RX
 * DMA0 Channel3 - UART1_TX
 * DMA0 Channel4 - UART2_RX
 * DMA0 Channel5 - UART2_TX
 * DMA0 Channel6 - SPI0_RX
 * DMA0 Channel7 - SPI1_RX
 * ------------------------------------------------------------
 * DMA1 Channel0 - SPI0_TX
 * DMA1 Channel1 - SPI1_TX
 * DMA1 Channel2 - SPI2_RX
 * DMA1 Channel3 - SPI2_TX
 * DMA1 Channel4 - I2C0_RX
 * DMA1 Channel5 - I2C0_TX
 * DMA1 Channel6 - I2C1_RX
 * DMA1 Channel7 - I2C1_TX
 * ============================================================
 * Note: For conflicts, override in board.h to reassign channels.
 */

/* ==================== DMA Request IDs ==================== */
/* Note: These may already be defined in GD32G5x3 standard library headers.
   Use #ifndef guards to avoid redefinition conflicts. */

/* UART0 */
#ifndef DMA_REQUEST_USART0_RX
#define DMA_REQUEST_USART0_RX           (0)
#endif
#ifndef DMA_REQUEST_USART0_TX
#define DMA_REQUEST_USART0_TX           (1)
#endif

/* UART1 */
#ifndef DMA_REQUEST_USART1_RX
#define DMA_REQUEST_USART1_RX           (2)
#endif
#ifndef DMA_REQUEST_USART1_TX
#define DMA_REQUEST_USART1_TX           (3)
#endif

/* UART2 */
#ifndef DMA_REQUEST_USART2_RX
#define DMA_REQUEST_USART2_RX           (4)
#endif
#ifndef DMA_REQUEST_USART2_TX
#define DMA_REQUEST_USART2_TX           (5)
#endif

/* SPI0 */
#ifndef DMA_REQUEST_SPI0_RX
#define DMA_REQUEST_SPI0_RX             (6)
#endif
#ifndef DMA_REQUEST_SPI0_TX
#define DMA_REQUEST_SPI0_TX             (7)
#endif

/* SPI1 */
#ifndef DMA_REQUEST_SPI1_RX
#define DMA_REQUEST_SPI1_RX             (8)
#endif
#ifndef DMA_REQUEST_SPI1_TX
#define DMA_REQUEST_SPI1_TX             (9)
#endif

/* SPI2 */
#ifndef DMA_REQUEST_SPI2_RX
#define DMA_REQUEST_SPI2_RX             (10)
#endif
#ifndef DMA_REQUEST_SPI2_TX
#define DMA_REQUEST_SPI2_TX             (11)
#endif

/* I2C0 */
#ifndef DMA_REQUEST_I2C0_RX
#define DMA_REQUEST_I2C0_RX             (12)
#endif
#ifndef DMA_REQUEST_I2C0_TX
#define DMA_REQUEST_I2C0_TX             (13)
#endif

/* I2C1 */
#ifndef DMA_REQUEST_I2C1_RX
#define DMA_REQUEST_I2C1_RX             (14)
#endif
#ifndef DMA_REQUEST_I2C1_TX
#define DMA_REQUEST_I2C1_TX             (15)
#endif

/* I2C2 */
#ifndef DMA_REQUEST_I2C2_RX
#define DMA_REQUEST_I2C2_RX             (20)
#endif
#ifndef DMA_REQUEST_I2C2_TX
#define DMA_REQUEST_I2C2_TX             (21)
#endif

/* ==================== DMA0 Channel Configuration ==================== */

/* DMA0 Channel0 - UART0_RX */
#if defined(BSP_UART0_RX_USING_DMA) && !defined(UART0_RX_DMA_PERIPH)
#define UART0_DMA_RX_IRQHandler         DMA0_Channel0_IRQHandler
#define UART0_RX_DMA_PERIPH             DMA0
#define UART0_RX_DMA_RCU                RCU_DMA0
#define UART0_RX_DMA_CHANNEL            DMA_CH0
#define UART0_RX_DMA_REQUEST            DMA_REQUEST_USART0_RX
#define UART0_RX_DMA_IRQ                DMA0_Channel0_IRQn
#endif

/* DMA0 Channel1 - UART0_TX */
#if defined(BSP_UART0_TX_USING_DMA) && !defined(UART0_TX_DMA_PERIPH)
#define UART0_DMA_TX_IRQHandler         DMA0_Channel1_IRQHandler
#define UART0_TX_DMA_PERIPH             DMA0
#define UART0_TX_DMA_RCU                RCU_DMA0
#define UART0_TX_DMA_CHANNEL            DMA_CH1
#define UART0_TX_DMA_REQUEST            DMA_REQUEST_USART0_TX
#define UART0_TX_DMA_IRQ                DMA0_Channel1_IRQn
#endif

/* DMA0 Channel2 - UART1_RX */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_PERIPH)
#define UART1_DMA_RX_IRQHandler         DMA0_Channel2_IRQHandler
#define UART1_RX_DMA_PERIPH             DMA0
#define UART1_RX_DMA_RCU                RCU_DMA0
#define UART1_RX_DMA_CHANNEL            DMA_CH2
#define UART1_RX_DMA_REQUEST            DMA_REQUEST_USART1_RX
#define UART1_RX_DMA_IRQ                DMA0_Channel2_IRQn
#endif

/* DMA0 Channel3 - UART1_TX */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_PERIPH)
#define UART1_DMA_TX_IRQHandler         DMA0_Channel3_IRQHandler
#define UART1_TX_DMA_PERIPH             DMA0
#define UART1_TX_DMA_RCU                RCU_DMA0
#define UART1_TX_DMA_CHANNEL            DMA_CH3
#define UART1_TX_DMA_REQUEST            DMA_REQUEST_USART1_TX
#define UART1_TX_DMA_IRQ                DMA0_Channel3_IRQn
#endif

/* DMA0 Channel4 - UART2_RX */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_PERIPH)
#define UART2_DMA_RX_IRQHandler         DMA0_Channel4_IRQHandler
#define UART2_RX_DMA_PERIPH             DMA0
#define UART2_RX_DMA_RCU                RCU_DMA0
#define UART2_RX_DMA_CHANNEL            DMA_CH4
#define UART2_RX_DMA_REQUEST            DMA_REQUEST_USART2_RX
#define UART2_RX_DMA_IRQ                DMA0_Channel4_IRQn
#endif

/* DMA0 Channel5 - UART2_TX */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_PERIPH)
#define UART2_DMA_TX_IRQHandler         DMA0_Channel5_IRQHandler
#define UART2_TX_DMA_PERIPH             DMA0
#define UART2_TX_DMA_RCU                RCU_DMA0
#define UART2_TX_DMA_CHANNEL            DMA_CH5
#define UART2_TX_DMA_REQUEST            DMA_REQUEST_USART2_TX
#define UART2_TX_DMA_IRQ                DMA0_Channel5_IRQn
#endif

/* Placeholder definitions for UART3-7 (support for future expansion) */
/* These will use DMA1 when enabled in future versions */

#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_PERIPH)
/* Placeholder: UART3_RX - Reserve DMA1 Channel ? */
#define UART3_RX_DMA_PERIPH             DMA1
#define UART3_RX_DMA_RCU                RCU_DMA1
#define UART3_RX_DMA_CHANNEL            DMA_CH0
#define UART3_RX_DMA_REQUEST            DMA_REQUEST_USART3_RX
#define UART3_RX_DMA_IRQ                DMA1_Channel0_IRQn
#endif

#if defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_PERIPH)
#define UART3_TX_DMA_PERIPH             DMA1
#define UART3_TX_DMA_RCU                RCU_DMA1
#define UART3_TX_DMA_CHANNEL            DMA_CH1
#define UART3_TX_DMA_REQUEST            DMA_REQUEST_USART3_TX
#define UART3_TX_DMA_IRQ                DMA1_Channel1_IRQn
#endif

#if defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_PERIPH)
#define UART4_RX_DMA_PERIPH             DMA0
#define UART4_RX_DMA_RCU                RCU_DMA0
#define UART4_RX_DMA_CHANNEL            DMA_CH0
#define UART4_RX_DMA_REQUEST            DMA_REQUEST_USART4_RX
#define UART4_RX_DMA_IRQ                DMA0_Channel0_IRQn
#endif

#if defined(BSP_UART4_TX_USING_DMA) && !defined(UART4_TX_DMA_PERIPH)
#define UART4_TX_DMA_PERIPH             DMA0
#define UART4_TX_DMA_RCU                RCU_DMA0
#define UART4_TX_DMA_CHANNEL            DMA_CH1
#define UART4_TX_DMA_REQUEST            DMA_REQUEST_USART4_TX
#define UART4_TX_DMA_IRQ                DMA0_Channel1_IRQn
#endif

#if defined(BSP_UART5_RX_USING_DMA) && !defined(UART5_RX_DMA_PERIPH)
#define UART5_RX_DMA_PERIPH             DMA0
#define UART5_RX_DMA_RCU                RCU_DMA0
#define UART5_RX_DMA_CHANNEL            DMA_CH2
#define UART5_RX_DMA_REQUEST            DMA_REQUEST_USART5_RX
#define UART5_RX_DMA_IRQ                DMA0_Channel2_IRQn
#endif

#if defined(BSP_UART5_TX_USING_DMA) && !defined(UART5_TX_DMA_PERIPH)
#define UART5_TX_DMA_PERIPH             DMA0
#define UART5_TX_DMA_RCU                RCU_DMA0
#define UART5_TX_DMA_CHANNEL            DMA_CH3
#define UART5_TX_DMA_REQUEST            DMA_REQUEST_USART5_TX
#define UART5_TX_DMA_IRQ                DMA0_Channel3_IRQn
#endif

/* DMA0 Channel6 - SPI0_RX */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_RX_DMA_PERIPH)
#define SPI0_DMA_RX_IRQHandler          DMA0_Channel6_IRQHandler
#define SPI0_RX_DMA_PERIPH              DMA0
#define SPI0_RX_DMA_RCU                 RCU_DMA0
#define SPI0_RX_DMA_CHANNEL             DMA_CH6
#define SPI0_RX_DMA_REQUEST             DMA_REQUEST_SPI0_RX
#define SPI0_RX_DMA_IRQ                 DMA0_Channel6_IRQn
#endif

/* DMA0 Channel7 - SPI1_RX */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_RX_DMA_PERIPH)
#define SPI1_DMA_RX_IRQHandler          DMA0_Channel7_IRQHandler
#define SPI1_RX_DMA_PERIPH              DMA0
#define SPI1_RX_DMA_RCU                 RCU_DMA0
#define SPI1_RX_DMA_CHANNEL             DMA_CH7
#define SPI1_RX_DMA_REQUEST             DMA_REQUEST_SPI1_RX
#define SPI1_RX_DMA_IRQ                 DMA0_Channel7_IRQn
#endif

/* ==================== DMA1 Channel Configuration ==================== */

/* DMA1 Channel0 - SPI0_TX */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_TX_DMA_PERIPH)
#define SPI0_DMA_TX_IRQHandler          DMA1_Channel0_IRQHandler
#define SPI0_TX_DMA_PERIPH              DMA1
#define SPI0_TX_DMA_RCU                 RCU_DMA1
#define SPI0_TX_DMA_CHANNEL             DMA_CH0
#define SPI0_TX_DMA_REQUEST             DMA_REQUEST_SPI0_TX
#define SPI0_TX_DMA_IRQ                 DMA1_Channel0_IRQn
#endif

/* DMA1 Channel1 - SPI1_TX */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_TX_DMA_PERIPH)
#define SPI1_DMA_TX_IRQHandler          DMA1_Channel1_IRQHandler
#define SPI1_TX_DMA_PERIPH              DMA1
#define SPI1_TX_DMA_RCU                 RCU_DMA1
#define SPI1_TX_DMA_CHANNEL             DMA_CH1
#define SPI1_TX_DMA_REQUEST             DMA_REQUEST_SPI1_TX
#define SPI1_TX_DMA_IRQ                 DMA1_Channel1_IRQn
#endif

/* DMA1 Channel2 - SPI2_RX */
#if defined(BSP_SPI2_USING_DMA) && !defined(SPI2_RX_DMA_PERIPH)
#define SPI2_DMA_RX_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI2_RX_DMA_PERIPH              DMA1
#define SPI2_RX_DMA_RCU                 RCU_DMA1
#define SPI2_RX_DMA_CHANNEL             DMA_CH2
#define SPI2_RX_DMA_REQUEST             DMA_REQUEST_SPI2_RX
#define SPI2_RX_DMA_IRQ                 DMA1_Channel2_IRQn
#endif

/* DMA1 Channel3 - SPI2_TX */
#if defined(BSP_SPI2_USING_DMA) && !defined(SPI2_TX_DMA_PERIPH)
#define SPI2_DMA_TX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI2_TX_DMA_PERIPH              DMA1
#define SPI2_TX_DMA_RCU                 RCU_DMA1
#define SPI2_TX_DMA_CHANNEL             DMA_CH3
#define SPI2_TX_DMA_REQUEST             DMA_REQUEST_SPI2_TX
#define SPI2_TX_DMA_IRQ                 DMA1_Channel3_IRQn
#endif

/* DMA1 Channel4 - I2C0_RX */
#if defined(BSP_I2C0_RX_USING_DMA) && !defined(I2C0_RX_DMA_PERIPH)
#define I2C0_DMA_RX_IRQHandler          DMA1_Channel4_IRQHandler
#define I2C0_RX_DMA_PERIPH              DMA1
#define I2C0_RX_DMA_RCU                 RCU_DMA1
#define I2C0_RX_DMA_CHANNEL             DMA_CH4
#define I2C0_RX_DMA_REQUEST             DMA_REQUEST_I2C0_RX
#define I2C0_RX_DMA_IRQ                 DMA1_Channel4_IRQn
#endif

/* DMA1 Channel5 - I2C0_TX */
#if defined(BSP_I2C0_TX_USING_DMA) && !defined(I2C0_TX_DMA_PERIPH)
#define I2C0_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define I2C0_TX_DMA_PERIPH              DMA1
#define I2C0_TX_DMA_RCU                 RCU_DMA1
#define I2C0_TX_DMA_CHANNEL             DMA_CH5
#define I2C0_TX_DMA_REQUEST             DMA_REQUEST_I2C0_TX
#define I2C0_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#endif

/* DMA1 Channel6 - I2C1_RX */
#if defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_PERIPH)
#define I2C1_DMA_RX_IRQHandler          DMA1_Channel6_IRQHandler
#define I2C1_RX_DMA_PERIPH              DMA1
#define I2C1_RX_DMA_RCU                 RCU_DMA1
#define I2C1_RX_DMA_CHANNEL             DMA_CH6
#define I2C1_RX_DMA_REQUEST             DMA_REQUEST_I2C1_RX
#define I2C1_RX_DMA_IRQ                 DMA1_Channel6_IRQn
#endif

/* DMA1 Channel7 - I2C1_TX */
#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_PERIPH)
#define I2C1_DMA_TX_IRQHandler          DMA1_Channel7_IRQHandler
#define I2C1_TX_DMA_PERIPH              DMA1
#define I2C1_TX_DMA_RCU                 RCU_DMA1
#define I2C1_TX_DMA_CHANNEL             DMA_CH7
#define I2C1_TX_DMA_REQUEST             DMA_REQUEST_I2C1_TX
#define I2C1_TX_DMA_IRQ                 DMA1_Channel7_IRQn
#endif

/* DMA1 Channel4 - I2C2_RX (using DMAMUX request ID 20) */
#if defined(BSP_I2C2_RX_USING_DMA) && !defined(I2C2_RX_DMA_PERIPH)
#define I2C2_DMA_RX_IRQHandler          DMA1_Channel4_IRQHandler
#define I2C2_RX_DMA_PERIPH              DMA1
#define I2C2_RX_DMA_RCU                 RCU_DMA1
#define I2C2_RX_DMA_CHANNEL             DMA_CH4
#define I2C2_RX_DMA_REQUEST             DMA_REQUEST_I2C2_RX
#define I2C2_RX_DMA_IRQ                 DMA1_Channel4_IRQn
#endif

/* DMA1 Channel5 - I2C2_TX (using DMAMUX request ID 21) */
#if defined(BSP_I2C2_TX_USING_DMA) && !defined(I2C2_TX_DMA_PERIPH)
#define I2C2_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define I2C2_TX_DMA_PERIPH              DMA1
#define I2C2_TX_DMA_RCU                 RCU_DMA1
#define I2C2_TX_DMA_CHANNEL             DMA_CH5
#define I2C2_TX_DMA_REQUEST             DMA_REQUEST_I2C2_TX
#define I2C2_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#endif

/* ==================== Compatibility Aliases ==================== */
#define UART0_RX_DMA_REQUEST            DMA_REQUEST_USART0_RX
#define UART0_TX_DMA_REQUEST            DMA_REQUEST_USART0_TX

/* ==================== DMA Config Macros for SPI/I2C ==================== */
/* These macros create complete struct dma_config initializers for use in driver code */

#ifdef BSP_SPI0_USING_DMA
#define SPI0_RX_DMA_CONFIG  { \
    .periph     = DMA0, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA0, \
    .channel    = DMA_CH6, \
    .request    = (uint32_t)(DMA_REQUEST_SPI0_RX), \
    .irq        = DMA0_Channel6_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}

#define SPI0_TX_DMA_CONFIG  { \
    .periph     = DMA1, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA1, \
    .channel    = DMA_CH0, \
    .request    = (uint32_t)(DMA_REQUEST_SPI0_TX), \
    .irq        = DMA1_Channel0_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}
#endif

#ifdef BSP_SPI1_USING_DMA
#define SPI1_RX_DMA_CONFIG  { \
    .periph     = DMA0, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA0, \
    .channel    = DMA_CH7, \
    .request    = (uint32_t)(DMA_REQUEST_SPI1_RX), \
    .irq        = DMA0_Channel7_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}

#define SPI1_TX_DMA_CONFIG  { \
    .periph     = DMA1, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA1, \
    .channel    = DMA_CH1, \
    .request    = (uint32_t)(DMA_REQUEST_SPI1_TX), \
    .irq        = DMA1_Channel1_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}
#endif

#ifdef BSP_SPI2_USING_DMA
#define SPI2_RX_DMA_CONFIG  { \
    .periph     = DMA1, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA1, \
    .channel    = DMA_CH2, \
    .request    = (uint32_t)(DMA_REQUEST_SPI2_RX), \
    .irq        = DMA1_Channel2_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}

#define SPI2_TX_DMA_CONFIG  { \
    .periph     = DMA1, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA1, \
    .channel    = DMA_CH3, \
    .request    = (uint32_t)(DMA_REQUEST_SPI2_TX), \
    .irq        = DMA1_Channel3_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}
#endif

#ifdef BSP_SPI3_USING_DMA
#define SPI3_RX_DMA_CONFIG  { \
    .periph     = DMA0, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA0, \
    .channel    = DMA_CH0, \
    .request    = (uint32_t)(DMA_REQUEST_SPI3_RX), \
    .irq        = DMA0_Channel0_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}

#define SPI3_TX_DMA_CONFIG  { \
    .periph     = DMA0, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA0, \
    .channel    = DMA_CH1, \
    .request    = (uint32_t)(DMA_REQUEST_SPI3_TX), \
    .irq        = DMA0_Channel1_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}
#endif

#ifdef BSP_SPI4_USING_DMA
#define SPI4_RX_DMA_CONFIG  { \
    .periph     = DMA0, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA0, \
    .channel    = DMA_CH2, \
    .request    = (uint32_t)(DMA_REQUEST_SPI4_RX), \
    .irq        = DMA0_Channel2_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}

#define SPI4_TX_DMA_CONFIG  { \
    .periph     = DMA0, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA0, \
    .channel    = DMA_CH3, \
    .request    = (uint32_t)(DMA_REQUEST_SPI4_TX), \
    .irq        = DMA0_Channel3_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}
#endif

#ifdef BSP_SPI5_USING_DMA
#define SPI5_RX_DMA_CONFIG  { \
    .periph     = DMA0, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA0, \
    .channel    = DMA_CH4, \
    .request    = (uint32_t)(DMA_REQUEST_SPI5_RX), \
    .irq        = DMA0_Channel4_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}

#define SPI5_TX_DMA_CONFIG  { \
    .periph     = DMA0, \
    .dma_flag   = 0, \
    .rcu        = RCU_DMA0, \
    .channel    = DMA_CH5, \
    .request    = (uint32_t)(DMA_REQUEST_SPI5_TX), \
    .irq        = DMA0_Channel5_IRQn, \
    .data_width = DMA_PERIPH_WIDTH_8BIT, \
}
#endif


#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
