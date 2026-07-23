/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-20     RT-Thread    first implementation for GD32L23x DMA support
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * GD32L23x has a single DMA controller with 7 channels (DMA_CH0..DMA_CH6) and a
 * DMAMUX request multiplexer. Any peripheral request can be routed to any channel
 * through the '.request' field (DMA_REQUEST_xxx). The DMAMUX clock is enabled
 * together with RCU_DMA (there is no separate RCU_DMAMUX on this series).
 *
 * Default channel allocation (conflict-free set enabled out-of-box):
 * ============================================================
 * DMA Channel0 - SPI0_RX
 * DMA Channel1 - SPI0_TX
 * DMA Channel2 - I2C1_RX
 * DMA Channel3 - I2C1_TX
 * DMA Channel4 - UART0_RX
 * DMA Channel5 - UART0_TX
 * DMA Channel6 - (spare)
 * ============================================================
 * Only 7 channels exist. The alternate peripheral definitions below reuse some
 * channels; if you enable a combination that needs more than 7 active channels,
 * override the conflicting *_DMA_CHANNEL in board.h.
 */

/* ==================== UART ==================== */

/* UART0 */
#if defined(BSP_UART0_RX_USING_DMA) && !defined(UART0_RX_DMA_PERIPH)
#define UART0_DMA_RX_IRQHandler          DMA_Channel4_IRQHandler
#define UART0_RX_DMA_PERIPH              DMA
#define UART0_RX_DMA_RCU                 RCU_DMA
#define UART0_RX_DMA_CHANNEL             DMA_CH4
#define UART0_RX_DMA_REQUEST             DMA_REQUEST_USART0_RX
#define UART0_RX_DMA_IRQ                 DMA_Channel4_IRQn
#endif

#if defined(BSP_UART0_TX_USING_DMA) && !defined(UART0_TX_DMA_PERIPH)
#define UART0_DMA_TX_IRQHandler          DMA_Channel5_IRQHandler
#define UART0_TX_DMA_PERIPH              DMA
#define UART0_TX_DMA_RCU                 RCU_DMA
#define UART0_TX_DMA_CHANNEL             DMA_CH5
#define UART0_TX_DMA_REQUEST             DMA_REQUEST_USART0_TX
#define UART0_TX_DMA_IRQ                 DMA_Channel5_IRQn
#endif

/* UART1 (alternate: reuses SPI0 channels) */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_PERIPH)
#define UART1_DMA_RX_IRQHandler          DMA_Channel0_IRQHandler
#define UART1_RX_DMA_PERIPH              DMA
#define UART1_RX_DMA_RCU                 RCU_DMA
#define UART1_RX_DMA_CHANNEL             DMA_CH0
#define UART1_RX_DMA_REQUEST             DMA_REQUEST_USART1_RX
#define UART1_RX_DMA_IRQ                 DMA_Channel0_IRQn
#endif

#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_PERIPH)
#define UART1_DMA_TX_IRQHandler          DMA_Channel1_IRQHandler
#define UART1_TX_DMA_PERIPH              DMA
#define UART1_TX_DMA_RCU                 RCU_DMA
#define UART1_TX_DMA_CHANNEL             DMA_CH1
#define UART1_TX_DMA_REQUEST             DMA_REQUEST_USART1_TX
#define UART1_TX_DMA_IRQ                 DMA_Channel1_IRQn
#endif

/* UART3 (alternate: reuses I2C1 channels) */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_PERIPH)
#define UART3_DMA_RX_IRQHandler          DMA_Channel2_IRQHandler
#define UART3_RX_DMA_PERIPH              DMA
#define UART3_RX_DMA_RCU                 RCU_DMA
#define UART3_RX_DMA_CHANNEL             DMA_CH2
#define UART3_RX_DMA_REQUEST             DMA_REQUEST_UART3_RX
#define UART3_RX_DMA_IRQ                 DMA_Channel2_IRQn
#endif

#if defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_PERIPH)
#define UART3_DMA_TX_IRQHandler          DMA_Channel3_IRQHandler
#define UART3_TX_DMA_PERIPH              DMA
#define UART3_TX_DMA_RCU                 RCU_DMA
#define UART3_TX_DMA_CHANNEL             DMA_CH3
#define UART3_TX_DMA_REQUEST             DMA_REQUEST_UART3_TX
#define UART3_TX_DMA_IRQ                 DMA_Channel3_IRQn
#endif

/* UART4 (alternate: reuses UART0 channels) */
#if defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_PERIPH)
#define UART4_DMA_RX_IRQHandler          DMA_Channel4_IRQHandler
#define UART4_RX_DMA_PERIPH              DMA
#define UART4_RX_DMA_RCU                 RCU_DMA
#define UART4_RX_DMA_CHANNEL             DMA_CH4
#define UART4_RX_DMA_REQUEST             DMA_REQUEST_UART4_RX
#define UART4_RX_DMA_IRQ                 DMA_Channel4_IRQn
#endif

#if defined(BSP_UART4_TX_USING_DMA) && !defined(UART4_TX_DMA_PERIPH)
#define UART4_DMA_TX_IRQHandler          DMA_Channel5_IRQHandler
#define UART4_TX_DMA_PERIPH              DMA
#define UART4_TX_DMA_RCU                 RCU_DMA
#define UART4_TX_DMA_CHANNEL             DMA_CH5
#define UART4_TX_DMA_REQUEST             DMA_REQUEST_UART4_TX
#define UART4_TX_DMA_IRQ                 DMA_Channel5_IRQn
#endif

/* ==================== SPI ==================== */

/* SPI0 (default: CH0/CH1) */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_RX_DMA_PERIPH)
#define SPI0_DMA_RX_IRQHandler          DMA_Channel0_IRQHandler
#define SPI0_RX_DMA_PERIPH              DMA
#define SPI0_RX_DMA_RCU                 RCU_DMA
#define SPI0_RX_DMA_CHANNEL             DMA_CH0
#define SPI0_RX_DMA_REQUEST             DMA_REQUEST_SPI0_RX
#define SPI0_RX_DMA_IRQ                 DMA_Channel0_IRQn
#endif

#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_TX_DMA_PERIPH)
#define SPI0_DMA_TX_IRQHandler          DMA_Channel1_IRQHandler
#define SPI0_TX_DMA_PERIPH              DMA
#define SPI0_TX_DMA_RCU                 RCU_DMA
#define SPI0_TX_DMA_CHANNEL             DMA_CH1
#define SPI0_TX_DMA_REQUEST             DMA_REQUEST_SPI0_TX
#define SPI0_TX_DMA_IRQ                 DMA_Channel1_IRQn
#endif

/* SPI1 (alternate: reuses UART0 channels) */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_RX_DMA_PERIPH)
#define SPI1_DMA_RX_IRQHandler          DMA_Channel4_IRQHandler
#define SPI1_RX_DMA_PERIPH              DMA
#define SPI1_RX_DMA_RCU                 RCU_DMA
#define SPI1_RX_DMA_CHANNEL             DMA_CH4
#define SPI1_RX_DMA_REQUEST             DMA_REQUEST_SPI1_RX
#define SPI1_RX_DMA_IRQ                 DMA_Channel4_IRQn
#endif

#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_TX_DMA_PERIPH)
#define SPI1_DMA_TX_IRQHandler          DMA_Channel5_IRQHandler
#define SPI1_TX_DMA_PERIPH              DMA
#define SPI1_TX_DMA_RCU                 RCU_DMA
#define SPI1_TX_DMA_CHANNEL             DMA_CH5
#define SPI1_TX_DMA_REQUEST             DMA_REQUEST_SPI1_TX
#define SPI1_TX_DMA_IRQ                 DMA_Channel5_IRQn
#endif

/* ==================== I2C ==================== */

/* I2C0 (alternate: reuses SPI0 channels) */
#if defined(BSP_I2C0_RX_USING_DMA) && !defined(I2C0_RX_DMA_PERIPH)
#define I2C0_DMA_RX_IRQHandler          DMA_Channel0_IRQHandler
#define I2C0_RX_DMA_PERIPH              DMA
#define I2C0_RX_DMA_RCU                 RCU_DMA
#define I2C0_RX_DMA_CHANNEL             DMA_CH0
#define I2C0_RX_DMA_REQUEST             DMA_REQUEST_I2C0_RX
#define I2C0_RX_DMA_IRQ                 DMA_Channel0_IRQn
#endif

#if defined(BSP_I2C0_TX_USING_DMA) && !defined(I2C0_TX_DMA_PERIPH)
#define I2C0_DMA_TX_IRQHandler          DMA_Channel1_IRQHandler
#define I2C0_TX_DMA_PERIPH              DMA
#define I2C0_TX_DMA_RCU                 RCU_DMA
#define I2C0_TX_DMA_CHANNEL             DMA_CH1
#define I2C0_TX_DMA_REQUEST             DMA_REQUEST_I2C0_TX
#define I2C0_TX_DMA_IRQ                 DMA_Channel1_IRQn
#endif

/* I2C1 (default: CH2/CH3) */
#if defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_PERIPH)
#define I2C1_DMA_RX_IRQHandler          DMA_Channel2_IRQHandler
#define I2C1_RX_DMA_PERIPH              DMA
#define I2C1_RX_DMA_RCU                 RCU_DMA
#define I2C1_RX_DMA_CHANNEL             DMA_CH2
#define I2C1_RX_DMA_REQUEST             DMA_REQUEST_I2C1_RX
#define I2C1_RX_DMA_IRQ                 DMA_Channel2_IRQn
#endif

#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_PERIPH)
#define I2C1_DMA_TX_IRQHandler          DMA_Channel3_IRQHandler
#define I2C1_TX_DMA_PERIPH              DMA
#define I2C1_TX_DMA_RCU                 RCU_DMA
#define I2C1_TX_DMA_CHANNEL             DMA_CH3
#define I2C1_TX_DMA_REQUEST             DMA_REQUEST_I2C1_TX
#define I2C1_TX_DMA_IRQ                 DMA_Channel3_IRQn
#endif

/* I2C2 (alternate: reuses UART0 channels) */
#if defined(BSP_I2C2_RX_USING_DMA) && !defined(I2C2_RX_DMA_PERIPH)
#define I2C2_DMA_RX_IRQHandler          DMA_Channel4_IRQHandler
#define I2C2_RX_DMA_PERIPH              DMA
#define I2C2_RX_DMA_RCU                 RCU_DMA
#define I2C2_RX_DMA_CHANNEL             DMA_CH4
#define I2C2_RX_DMA_REQUEST             DMA_REQUEST_I2C2_RX
#define I2C2_RX_DMA_IRQ                 DMA_Channel4_IRQn
#endif

#if defined(BSP_I2C2_TX_USING_DMA) && !defined(I2C2_TX_DMA_PERIPH)
#define I2C2_DMA_TX_IRQHandler          DMA_Channel5_IRQHandler
#define I2C2_TX_DMA_PERIPH              DMA
#define I2C2_TX_DMA_RCU                 RCU_DMA
#define I2C2_TX_DMA_CHANNEL             DMA_CH5
#define I2C2_TX_DMA_REQUEST             DMA_REQUEST_I2C2_TX
#define I2C2_TX_DMA_IRQ                 DMA_Channel5_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
