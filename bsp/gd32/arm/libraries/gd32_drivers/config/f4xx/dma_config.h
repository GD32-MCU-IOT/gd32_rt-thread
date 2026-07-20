/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-13     RT-Thread    first implementation for GD32F4xx
 * 2026-07-14     Copilot      rewrite DMA map: order by channel index
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * DMA channel allocation (ordered by DMA0 CH0..CH7, then DMA1 CH0..CH7):
 * ============================================================
 * DMA0 Channel0 - I2C0_RX (subperi1)      [priority]
 * DMA0 Channel1 - UART2_RX (subperi4)     [priority]
 * DMA0 Channel2 - I2C1_RX (subperi7)      [optional]
 * DMA0 Channel3 - UART2_TX (subperi4)     [priority]
 * DMA0 Channel4 - SPI1_TX (subperi0)      [optional]
 * DMA0 Channel5 - UART1_RX (subperi4)     [priority]
 * DMA0 Channel6 - UART1_TX (subperi4)     [priority]
 * DMA0 Channel7 - I2C0_TX (subperi1)      [priority]
 * ------------------------------------------------------------
 * DMA1 Channel0 - SPI0_RX (subperi3)      [optional]
 * DMA1 Channel1 - SPI3_TX (subperi4)      [optional]
 * DMA1 Channel2 - UART0_RX (subperi4)     [optional]
 * DMA1 Channel3 - SPI0_TX (subperi3)      [optional]
 * DMA1 Channel4 - SPI4_TX (subperi2)      [optional]
 * DMA1 Channel5 - SPI5_TX (subperi1)      [priority]
 * DMA1 Channel6 - SPI5_RX (subperi1)      [priority]
 * DMA1 Channel7 - UART0_TX (subperi4)     [optional]
 * ============================================================
 * Priority peripherals UART1/UART2/I2C0/SPI5 sit on dedicated channels
 * and can be enabled together without conflict.
 */

/* ==================== DMA0 Channel Configuration ==================== */

/* DMA0 Channel0 - I2C0_RX (subperi1) */
#if defined(BSP_I2C0_RX_USING_DMA) && !defined(I2C0_RX_DMA_PERIPH)
#define I2C0_DMA_RX_IRQHandler          DMA0_Channel0_IRQHandler
#define I2C0_RX_DMA_PERIPH              DMA0
#define I2C0_RX_DMA_RCU                 RCU_DMA0
#define I2C0_RX_DMA_CHANNEL             DMA_CH0
#define I2C0_RX_DMA_IRQ                 DMA0_Channel0_IRQn
#define I2C0_RX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* DMA0 Channel1 - UART2_RX (subperi4) */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_PERIPH)
#define UART2_DMA_RX_IRQHandler         DMA0_Channel1_IRQHandler
#define UART2_RX_DMA_PERIPH             DMA0
#define UART2_RX_DMA_RCU                RCU_DMA0
#define UART2_RX_DMA_CHANNEL            DMA_CH1
#define UART2_RX_DMA_IRQ                DMA0_Channel1_IRQn
#define UART2_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* DMA0 Channel2 - I2C1_RX (subperi7) */
#if defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_PERIPH)
#define I2C1_DMA_RX_IRQHandler          DMA0_Channel2_IRQHandler
#define I2C1_RX_DMA_PERIPH              DMA0
#define I2C1_RX_DMA_RCU                 RCU_DMA0
#define I2C1_RX_DMA_CHANNEL             DMA_CH2
#define I2C1_RX_DMA_IRQ                 DMA0_Channel2_IRQn
#define I2C1_RX_DMA_SUBPERI             DMA_SUBPERI7
#endif

/* DMA0 Channel3 - UART2_TX (subperi4) */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_PERIPH)
#define UART2_DMA_TX_IRQHandler         DMA0_Channel3_IRQHandler
#define UART2_TX_DMA_PERIPH             DMA0
#define UART2_TX_DMA_RCU                RCU_DMA0
#define UART2_TX_DMA_CHANNEL            DMA_CH3
#define UART2_TX_DMA_IRQ                DMA0_Channel3_IRQn
#define UART2_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* DMA0 Channel4 - SPI1_TX (subperi0) */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_TX_DMA_PERIPH)
#define SPI1_DMA_TX_IRQHandler          DMA0_Channel4_IRQHandler
#define SPI1_TX_DMA_PERIPH              DMA0
#define SPI1_TX_DMA_RCU                 RCU_DMA0
#define SPI1_TX_DMA_CHANNEL             DMA_CH4
#define SPI1_TX_DMA_IRQ                 DMA0_Channel4_IRQn
#define SPI1_TX_DMA_SUBPERI             DMA_SUBPERI0
#endif

/* DMA0 Channel5 - UART1_RX (subperi4) */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_PERIPH)
#define UART1_DMA_RX_IRQHandler         DMA0_Channel5_IRQHandler
#define UART1_RX_DMA_PERIPH             DMA0
#define UART1_RX_DMA_RCU                RCU_DMA0
#define UART1_RX_DMA_CHANNEL            DMA_CH5
#define UART1_RX_DMA_IRQ                DMA0_Channel5_IRQn
#define UART1_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* DMA0 Channel6 - UART1_TX (subperi4) */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_PERIPH)
#define UART1_DMA_TX_IRQHandler         DMA0_Channel6_IRQHandler
#define UART1_TX_DMA_PERIPH             DMA0
#define UART1_TX_DMA_RCU                RCU_DMA0
#define UART1_TX_DMA_CHANNEL            DMA_CH6
#define UART1_TX_DMA_IRQ                DMA0_Channel6_IRQn
#define UART1_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* DMA0 Channel7 - I2C0_TX (subperi1) */
#if defined(BSP_I2C0_TX_USING_DMA) && !defined(I2C0_TX_DMA_PERIPH)
#define I2C0_DMA_TX_IRQHandler          DMA0_Channel7_IRQHandler
#define I2C0_TX_DMA_PERIPH              DMA0
#define I2C0_TX_DMA_RCU                 RCU_DMA0
#define I2C0_TX_DMA_CHANNEL             DMA_CH7
#define I2C0_TX_DMA_IRQ                 DMA0_Channel7_IRQn
#define I2C0_TX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* ==================== DMA1 Channel Configuration ==================== */

/* DMA1 Channel0 - SPI0_RX (subperi3) */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_RX_DMA_PERIPH)
#define SPI0_DMA_RX_IRQHandler          DMA1_Channel0_IRQHandler
#define SPI0_RX_DMA_PERIPH              DMA1
#define SPI0_RX_DMA_RCU                 RCU_DMA1
#define SPI0_RX_DMA_CHANNEL             DMA_CH0
#define SPI0_RX_DMA_IRQ                 DMA1_Channel0_IRQn
#define SPI0_RX_DMA_SUBPERI             DMA_SUBPERI3
#endif

/* DMA1 Channel1 - SPI3_TX (subperi4) */
#if defined(BSP_SPI3_USING_DMA) && !defined(SPI3_TX_DMA_PERIPH)
#define SPI3_DMA_TX_IRQHandler          DMA1_Channel1_IRQHandler
#define SPI3_TX_DMA_PERIPH              DMA1
#define SPI3_TX_DMA_RCU                 RCU_DMA1
#define SPI3_TX_DMA_CHANNEL             DMA_CH1
#define SPI3_TX_DMA_IRQ                 DMA1_Channel1_IRQn
#define SPI3_TX_DMA_SUBPERI             DMA_SUBPERI4
#endif

/* DMA1 Channel2 - UART0_RX (subperi4) */
#if defined(BSP_UART0_RX_USING_DMA) && !defined(UART0_RX_DMA_PERIPH)
#define UART0_DMA_RX_IRQHandler         DMA1_Channel2_IRQHandler
#define UART0_RX_DMA_PERIPH             DMA1
#define UART0_RX_DMA_RCU                RCU_DMA1
#define UART0_RX_DMA_CHANNEL            DMA_CH2
#define UART0_RX_DMA_IRQ                DMA1_Channel2_IRQn
#define UART0_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* DMA1 Channel3 - SPI0_TX (subperi3) */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_TX_DMA_PERIPH)
#define SPI0_DMA_TX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI0_TX_DMA_PERIPH              DMA1
#define SPI0_TX_DMA_RCU                 RCU_DMA1
#define SPI0_TX_DMA_CHANNEL             DMA_CH3
#define SPI0_TX_DMA_IRQ                 DMA1_Channel3_IRQn
#define SPI0_TX_DMA_SUBPERI             DMA_SUBPERI3
#endif

/* DMA1 Channel4 - SPI4_TX (subperi2) */
#if defined(BSP_SPI4_USING_DMA) && !defined(SPI4_TX_DMA_PERIPH)
#define SPI4_DMA_TX_IRQHandler          DMA1_Channel4_IRQHandler
#define SPI4_TX_DMA_PERIPH              DMA1
#define SPI4_TX_DMA_RCU                 RCU_DMA1
#define SPI4_TX_DMA_CHANNEL             DMA_CH4
#define SPI4_TX_DMA_IRQ                 DMA1_Channel4_IRQn
#define SPI4_TX_DMA_SUBPERI             DMA_SUBPERI2
#endif

/* DMA1 Channel5 - SPI5_TX (subperi1) */
#if defined(BSP_SPI5_USING_DMA) && !defined(SPI5_TX_DMA_PERIPH)
#define SPI5_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define SPI5_TX_DMA_PERIPH              DMA1
#define SPI5_TX_DMA_RCU                 RCU_DMA1
#define SPI5_TX_DMA_CHANNEL             DMA_CH5
#define SPI5_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#define SPI5_TX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* DMA1 Channel6 - SPI5_RX (subperi1) */
#if defined(BSP_SPI5_USING_DMA) && !defined(SPI5_RX_DMA_PERIPH)
#define SPI5_DMA_RX_IRQHandler          DMA1_Channel6_IRQHandler
#define SPI5_RX_DMA_PERIPH              DMA1
#define SPI5_RX_DMA_RCU                 RCU_DMA1
#define SPI5_RX_DMA_CHANNEL             DMA_CH6
#define SPI5_RX_DMA_IRQ                 DMA1_Channel6_IRQn
#define SPI5_RX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* DMA1 Channel7 - UART0_TX (subperi4) */
#if defined(BSP_UART0_TX_USING_DMA) && !defined(UART0_TX_DMA_PERIPH)
#define UART0_DMA_TX_IRQHandler         DMA1_Channel7_IRQHandler
#define UART0_TX_DMA_PERIPH             DMA1
#define UART0_TX_DMA_RCU                RCU_DMA1
#define UART0_TX_DMA_CHANNEL            DMA_CH7
#define UART0_TX_DMA_IRQ                DMA1_Channel7_IRQn
#define UART0_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
