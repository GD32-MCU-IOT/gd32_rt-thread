/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-15    RT-Thread    first implementation for GD32F50x DMA mapping
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * GD32F50x uses a DMAMUX architecture: any DMA_REQUEST_xxx source can be
 * routed to any DMA channel. There is no subperipheral field.
 *
 * DMA controller overview:
 *   DMA0: Channel0 .. Channel6  (7 channels)
 *   DMA1: Channel0 .. Channel4  (5 channels)
 *
 * Channel allocation table for GD32F50x:
 * ============================================================
 * DMA0 Channel0 - USART0_RX
 * DMA0 Channel1 - USART0_TX
 * DMA0 Channel2 - USART1_RX
 * DMA0 Channel3 - USART1_TX
 * DMA0 Channel4 - USART2_RX
 * DMA0 Channel5 - USART2_TX
 * DMA0 Channel6 - SPI0_RX
 * ------------------------------------------------------------
 * DMA1 Channel0 - SPI0_TX  / UART3_RX / I2C0_RX   (conflict)
 * DMA1 Channel1 - SPI1_RX  / UART3_TX / I2C0_TX   (conflict)
 * DMA1 Channel2 - SPI1_TX  / I2C1_RX              (conflict)
 * DMA1 Channel3 - SPI2_RX  / I2C1_TX              (conflict)
 * DMA1 Channel4 - SPI2_TX
 * ============================================================
 * Note: UART4 has no DMA_REQUEST in the F50x firmware library, so it is not
 *       listed here. For conflict channels, only enable one peripheral's DMA
 *       at a time; or override the defines in board.h to reassign.
 */

/* ==================== DMA0 Channel Configuration ==================== */

/* DMA0 Channel0 - USART0_RX */
#if defined(BSP_UART0_RX_USING_DMA) && !defined(UART0_RX_DMA_PERIPH)
#define UART0_DMA_RX_IRQHandler         DMA0_Channel0_IRQHandler
#define UART0_RX_DMA_PERIPH             DMA0
#define UART0_RX_DMA_RCU                RCU_DMA0
#define UART0_RX_DMA_CHANNEL            DMA_CH0
#define UART0_RX_DMA_REQUEST            DMA_REQUEST_USART0_RX
#define UART0_RX_DMA_IRQ                DMA0_Channel0_IRQn
#endif

/* DMA0 Channel1 - USART0_TX */
#if defined(BSP_UART0_TX_USING_DMA) && !defined(UART0_TX_DMA_PERIPH)
#define UART0_DMA_TX_IRQHandler         DMA0_Channel1_IRQHandler
#define UART0_TX_DMA_PERIPH             DMA0
#define UART0_TX_DMA_RCU                RCU_DMA0
#define UART0_TX_DMA_CHANNEL            DMA_CH1
#define UART0_TX_DMA_REQUEST            DMA_REQUEST_USART0_TX
#define UART0_TX_DMA_IRQ                DMA0_Channel1_IRQn
#endif

/* DMA0 Channel2 - USART1_RX */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_PERIPH)
#define UART1_DMA_RX_IRQHandler         DMA0_Channel2_IRQHandler
#define UART1_RX_DMA_PERIPH             DMA0
#define UART1_RX_DMA_RCU                RCU_DMA0
#define UART1_RX_DMA_CHANNEL            DMA_CH2
#define UART1_RX_DMA_REQUEST            DMA_REQUEST_USART1_RX
#define UART1_RX_DMA_IRQ                DMA0_Channel2_IRQn
#endif

/* DMA0 Channel3 - USART1_TX */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_PERIPH)
#define UART1_DMA_TX_IRQHandler         DMA0_Channel3_IRQHandler
#define UART1_TX_DMA_PERIPH             DMA0
#define UART1_TX_DMA_RCU                RCU_DMA0
#define UART1_TX_DMA_CHANNEL            DMA_CH3
#define UART1_TX_DMA_REQUEST            DMA_REQUEST_USART1_TX
#define UART1_TX_DMA_IRQ                DMA0_Channel3_IRQn
#endif

/* DMA0 Channel4 - USART2_RX */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_PERIPH)
#define UART2_DMA_RX_IRQHandler         DMA0_Channel4_IRQHandler
#define UART2_RX_DMA_PERIPH             DMA0
#define UART2_RX_DMA_RCU                RCU_DMA0
#define UART2_RX_DMA_CHANNEL            DMA_CH4
#define UART2_RX_DMA_REQUEST            DMA_REQUEST_USART2_RX
#define UART2_RX_DMA_IRQ                DMA0_Channel4_IRQn
#endif

/* DMA0 Channel5 - USART2_TX */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_PERIPH)
#define UART2_DMA_TX_IRQHandler         DMA0_Channel5_IRQHandler
#define UART2_TX_DMA_PERIPH             DMA0
#define UART2_TX_DMA_RCU                RCU_DMA0
#define UART2_TX_DMA_CHANNEL            DMA_CH5
#define UART2_TX_DMA_REQUEST            DMA_REQUEST_USART2_TX
#define UART2_TX_DMA_IRQ                DMA0_Channel5_IRQn
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

/* ==================== DMA1 Channel Configuration ==================== */

/* DMA1 Channel0 - SPI0_TX / UART3_RX / I2C0_RX (conflict) */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_TX_DMA_PERIPH)
#define SPI0_DMA_TX_IRQHandler          DMA1_Channel0_IRQHandler
#define SPI0_TX_DMA_PERIPH              DMA1
#define SPI0_TX_DMA_RCU                 RCU_DMA1
#define SPI0_TX_DMA_CHANNEL             DMA_CH0
#define SPI0_TX_DMA_REQUEST             DMA_REQUEST_SPI0_TX
#define SPI0_TX_DMA_IRQ                 DMA1_Channel0_IRQn
#endif

#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_PERIPH)
#define UART3_DMA_RX_IRQHandler         DMA1_Channel0_IRQHandler
#define UART3_RX_DMA_PERIPH             DMA1
#define UART3_RX_DMA_RCU                RCU_DMA1
#define UART3_RX_DMA_CHANNEL            DMA_CH0
#define UART3_RX_DMA_REQUEST            DMA_REQUEST_UART3_RX
#define UART3_RX_DMA_IRQ                DMA1_Channel0_IRQn
#endif

#if defined(BSP_I2C0_RX_USING_DMA) && !defined(I2C0_RX_DMA_PERIPH)
#define I2C0_DMA_RX_IRQHandler         DMA1_Channel0_IRQHandler
#define I2C0_RX_DMA_PERIPH             DMA1
#define I2C0_RX_DMA_RCU                RCU_DMA1
#define I2C0_RX_DMA_CHANNEL            DMA_CH0
#define I2C0_RX_DMA_REQUEST            DMA_REQUEST_I2C0_RX
#define I2C0_RX_DMA_IRQ                DMA1_Channel0_IRQn
#endif

/* DMA1 Channel1 - SPI1_RX / UART3_TX / I2C0_TX (conflict) */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_RX_DMA_PERIPH)
#define SPI1_DMA_RX_IRQHandler          DMA1_Channel1_IRQHandler
#define SPI1_RX_DMA_PERIPH              DMA1
#define SPI1_RX_DMA_RCU                 RCU_DMA1
#define SPI1_RX_DMA_CHANNEL             DMA_CH1
#define SPI1_RX_DMA_REQUEST             DMA_REQUEST_SPI1_RX
#define SPI1_RX_DMA_IRQ                 DMA1_Channel1_IRQn
#endif

#if defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_PERIPH)
#define UART3_DMA_TX_IRQHandler         DMA1_Channel1_IRQHandler
#define UART3_TX_DMA_PERIPH             DMA1
#define UART3_TX_DMA_RCU                RCU_DMA1
#define UART3_TX_DMA_CHANNEL            DMA_CH1
#define UART3_TX_DMA_REQUEST            DMA_REQUEST_UART3_TX
#define UART3_TX_DMA_IRQ                DMA1_Channel1_IRQn
#endif

#if defined(BSP_I2C0_TX_USING_DMA) && !defined(I2C0_TX_DMA_PERIPH)
#define I2C0_DMA_TX_IRQHandler         DMA1_Channel1_IRQHandler
#define I2C0_TX_DMA_PERIPH             DMA1
#define I2C0_TX_DMA_RCU                RCU_DMA1
#define I2C0_TX_DMA_CHANNEL            DMA_CH1
#define I2C0_TX_DMA_REQUEST            DMA_REQUEST_I2C0_TX
#define I2C0_TX_DMA_IRQ                DMA1_Channel1_IRQn
#endif

/* DMA1 Channel2 - SPI1_TX / I2C1_RX (conflict) */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_TX_DMA_PERIPH)
#define SPI1_DMA_TX_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI1_TX_DMA_PERIPH              DMA1
#define SPI1_TX_DMA_RCU                 RCU_DMA1
#define SPI1_TX_DMA_CHANNEL             DMA_CH2
#define SPI1_TX_DMA_REQUEST             DMA_REQUEST_SPI1_TX
#define SPI1_TX_DMA_IRQ                 DMA1_Channel2_IRQn
#endif

#if defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_PERIPH)
#define I2C1_DMA_RX_IRQHandler         DMA1_Channel2_IRQHandler
#define I2C1_RX_DMA_PERIPH             DMA1
#define I2C1_RX_DMA_RCU                RCU_DMA1
#define I2C1_RX_DMA_CHANNEL            DMA_CH2
#define I2C1_RX_DMA_REQUEST            DMA_REQUEST_I2C1_RX
#define I2C1_RX_DMA_IRQ                DMA1_Channel2_IRQn
#endif

/* DMA1 Channel3 - SPI2_RX / I2C1_TX (conflict) */
#if defined(BSP_SPI2_USING_DMA) && !defined(SPI2_RX_DMA_PERIPH)
#define SPI2_DMA_RX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI2_RX_DMA_PERIPH              DMA1
#define SPI2_RX_DMA_RCU                 RCU_DMA1
#define SPI2_RX_DMA_CHANNEL             DMA_CH3
#define SPI2_RX_DMA_REQUEST             DMA_REQUEST_SPI2_RX
#define SPI2_RX_DMA_IRQ                 DMA1_Channel3_IRQn
#endif

#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_PERIPH)
#define I2C1_DMA_TX_IRQHandler         DMA1_Channel3_IRQHandler
#define I2C1_TX_DMA_PERIPH             DMA1
#define I2C1_TX_DMA_RCU                RCU_DMA1
#define I2C1_TX_DMA_CHANNEL            DMA_CH3
#define I2C1_TX_DMA_REQUEST            DMA_REQUEST_I2C1_TX
#define I2C1_TX_DMA_IRQ                DMA1_Channel3_IRQn
#endif

/* DMA1 Channel4 - SPI2_TX */
#if defined(BSP_SPI2_USING_DMA) && !defined(SPI2_TX_DMA_PERIPH)
#define SPI2_DMA_TX_IRQHandler          DMA1_Channel4_IRQHandler
#define SPI2_TX_DMA_PERIPH              DMA1
#define SPI2_TX_DMA_RCU                 RCU_DMA1
#define SPI2_TX_DMA_CHANNEL             DMA_CH4
#define SPI2_TX_DMA_REQUEST             DMA_REQUEST_SPI2_TX
#define SPI2_TX_DMA_IRQ                 DMA1_Channel4_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
