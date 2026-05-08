/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-22     RT-Thread    Rework DMA mapping, all peripherals independent
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * DMA Channel Allocation Table for GD32H77x:
 * ============================================================
 * DMA0 Channel0 - UART0_RX
 * DMA0 Channel1 - UART0_TX
 * DMA0 Channel2 - UART1_RX
 * DMA0 Channel3 - UART1_TX
 * DMA0 Channel4 - UART2_RX
 * DMA0 Channel5 - UART2_TX
 * DMA0 Channel6 - UART3_RX / SPI0_RX (conflict)
 * DMA0 Channel7 - UART3_TX / SPI0_TX (conflict)
 * ------------------------------------------------------------
 * DMA1 Channel0 - UART4_RX / SPI1_RX / I2C1_RX (conflict)
 * DMA1 Channel1 - UART4_TX / SPI1_TX / I2C1_TX (conflict)
 * DMA1 Channel2 - UART5_RX / SPI2_RX / I2C2_RX (conflict)
 * DMA1 Channel3 - UART5_TX / SPI2_TX / I2C2_TX (conflict)
 * DMA1 Channel4 - UART6_RX / SPI3_RX / I2C3_RX (conflict)
 * DMA1 Channel5 - UART6_TX / SPI3_TX / I2C3_TX (conflict)
 * DMA1 Channel6 - UART7_RX / I2C0_RX (conflict)
 * DMA1 Channel7 - UART7_TX / I2C0_TX (conflict)
 * ============================================================
 * Note: For conflicts, override in board.h to reassign channels.
 */

/* Definitions below are ordered by DMA channel to match the allocation table above. */

/* ==================== DMA0 Channel Configuration ==================== */

/* DMA0 Channel0 - UART0_RX */
#if defined(BSP_UART0_RX_USING_DMA) && !defined(UART0_RX_DMA_PERIPH)
#define UART0_DMA_RX_IRQHandler          DMA0_Channel0_IRQHandler
#define UART0_RX_DMA_PERIPH              DMA0
#define UART0_RX_DMA_FLAG                DMA_INTF_FTFIF
#define UART0_RX_DMA_RCU                 RCU_DMA0
#define UART0_RX_DMA_CHANNEL             DMA_CH0
#define UART0_RX_DMA_REQUEST             DMA_REQUEST_USART0_RX
#define UART0_RX_DMA_IRQ                 DMA0_Channel0_IRQn
#endif

/* DMA0 Channel1 - UART0_TX */
#if defined(BSP_UART0_TX_USING_DMA) && !defined(UART0_TX_DMA_PERIPH)
#define UART0_DMA_TX_IRQHandler          DMA0_Channel1_IRQHandler
#define UART0_TX_DMA_PERIPH              DMA0
#define UART0_TX_DMA_FLAG                DMA_INTF_FTFIF
#define UART0_TX_DMA_RCU                 RCU_DMA0
#define UART0_TX_DMA_CHANNEL             DMA_CH1
#define UART0_TX_DMA_REQUEST             DMA_REQUEST_USART0_TX
#define UART0_TX_DMA_IRQ                 DMA0_Channel1_IRQn
#endif

/* DMA0 Channel2 - UART1_RX */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_PERIPH)
#define UART1_DMA_RX_IRQHandler          DMA0_Channel2_IRQHandler
#define UART1_RX_DMA_PERIPH              DMA0
#define UART1_RX_DMA_FLAG                DMA_INTF_FTFIF
#define UART1_RX_DMA_RCU                 RCU_DMA0
#define UART1_RX_DMA_CHANNEL             DMA_CH2
#define UART1_RX_DMA_REQUEST             DMA_REQUEST_USART1_RX
#define UART1_RX_DMA_IRQ                 DMA0_Channel2_IRQn
#endif

/* DMA0 Channel3 - UART1_TX */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_PERIPH)
#define UART1_DMA_TX_IRQHandler          DMA0_Channel3_IRQHandler
#define UART1_TX_DMA_PERIPH              DMA0
#define UART1_TX_DMA_FLAG                DMA_INTF_FTFIF
#define UART1_TX_DMA_RCU                 RCU_DMA0
#define UART1_TX_DMA_CHANNEL             DMA_CH3
#define UART1_TX_DMA_REQUEST             DMA_REQUEST_USART1_TX
#define UART1_TX_DMA_IRQ                 DMA0_Channel3_IRQn
#endif

/* DMA0 Channel4 - UART2_RX */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_PERIPH)
#define UART2_DMA_RX_IRQHandler          DMA0_Channel4_IRQHandler
#define UART2_RX_DMA_PERIPH              DMA0
#define UART2_RX_DMA_FLAG                DMA_INTF_FTFIF
#define UART2_RX_DMA_RCU                 RCU_DMA0
#define UART2_RX_DMA_CHANNEL             DMA_CH4
#define UART2_RX_DMA_REQUEST             DMA_REQUEST_USART2_RX
#define UART2_RX_DMA_IRQ                 DMA0_Channel4_IRQn
#endif

/* DMA0 Channel5 - UART2_TX */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_PERIPH)
#define UART2_DMA_TX_IRQHandler          DMA0_Channel5_IRQHandler
#define UART2_TX_DMA_PERIPH              DMA0
#define UART2_TX_DMA_FLAG                DMA_INTF_FTFIF
#define UART2_TX_DMA_RCU                 RCU_DMA0
#define UART2_TX_DMA_CHANNEL             DMA_CH5
#define UART2_TX_DMA_REQUEST             DMA_REQUEST_USART2_TX
#define UART2_TX_DMA_IRQ                 DMA0_Channel5_IRQn
#endif

/* DMA0 Channel6 - UART3_RX / SPI0_RX (conflict) */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_PERIPH)
#define UART3_DMA_RX_IRQHandler          DMA0_Channel6_IRQHandler
#define UART3_RX_DMA_PERIPH              DMA0
#define UART3_RX_DMA_FLAG                DMA_INTF_FTFIF
#define UART3_RX_DMA_RCU                 RCU_DMA0
#define UART3_RX_DMA_CHANNEL             DMA_CH6
#define UART3_RX_DMA_REQUEST             DMA_REQUEST_UART3_RX
#define UART3_RX_DMA_IRQ                 DMA0_Channel6_IRQn
#endif

#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_RX_DMA_PERIPH)
#define SPI0_DMA_RX_IRQHandler          DMA0_Channel6_IRQHandler
#define SPI0_RX_DMA_PERIPH              DMA0
#define SPI0_RX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI0_RX_DMA_RCU                 RCU_DMA0
#define SPI0_RX_DMA_CHANNEL             DMA_CH6
#define SPI0_RX_DMA_REQUEST             DMA_REQUEST_SPI0_RX
#define SPI0_RX_DMA_IRQ                 DMA0_Channel6_IRQn
#endif

/* DMA0 Channel7 - UART3_TX / SPI0_TX (conflict) */
#if defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_PERIPH)
#define UART3_DMA_TX_IRQHandler          DMA0_Channel7_IRQHandler
#define UART3_TX_DMA_PERIPH              DMA0
#define UART3_TX_DMA_FLAG                DMA_INTF_FTFIF
#define UART3_TX_DMA_RCU                 RCU_DMA0
#define UART3_TX_DMA_CHANNEL             DMA_CH7
#define UART3_TX_DMA_REQUEST             DMA_REQUEST_UART3_TX
#define UART3_TX_DMA_IRQ                 DMA0_Channel7_IRQn
#endif

#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_TX_DMA_PERIPH)
#define SPI0_DMA_TX_IRQHandler          DMA0_Channel7_IRQHandler
#define SPI0_TX_DMA_PERIPH              DMA0
#define SPI0_TX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI0_TX_DMA_RCU                 RCU_DMA0
#define SPI0_TX_DMA_CHANNEL             DMA_CH7
#define SPI0_TX_DMA_REQUEST             DMA_REQUEST_SPI0_TX
#define SPI0_TX_DMA_IRQ                 DMA0_Channel7_IRQn
#endif

/* ==================== DMA1 Channel Configuration ==================== */

/* DMA1 Channel0 - UART4_RX / SPI1_RX / I2C1_RX (conflict) */
#if defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_PERIPH)
#define UART4_DMA_RX_IRQHandler          DMA1_Channel0_IRQHandler
#define UART4_RX_DMA_PERIPH              DMA1
#define UART4_RX_DMA_FLAG                DMA_INTF_FTFIF
#define UART4_RX_DMA_RCU                 RCU_DMA1
#define UART4_RX_DMA_CHANNEL             DMA_CH0
#define UART4_RX_DMA_REQUEST             DMA_REQUEST_UART4_RX
#define UART4_RX_DMA_IRQ                 DMA1_Channel0_IRQn
#endif

#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_RX_DMA_PERIPH)
#define SPI1_DMA_RX_IRQHandler          DMA1_Channel0_IRQHandler
#define SPI1_RX_DMA_PERIPH              DMA1
#define SPI1_RX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI1_RX_DMA_RCU                 RCU_DMA1
#define SPI1_RX_DMA_CHANNEL             DMA_CH0
#define SPI1_RX_DMA_REQUEST             DMA_REQUEST_SPI1_RX
#define SPI1_RX_DMA_IRQ                 DMA1_Channel0_IRQn
#endif

#if defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_PERIPH)
#define I2C1_DMA_RX_IRQHandler          DMA1_Channel0_IRQHandler
#define I2C1_RX_DMA_PERIPH              DMA1
#define I2C1_RX_DMA_FLAG                DMA_INTF_FTFIF
#define I2C1_RX_DMA_RCU                 RCU_DMA1
#define I2C1_RX_DMA_CHANNEL             DMA_CH0
#define I2C1_RX_DMA_REQUEST             DMA_REQUEST_I2C1_RX
#define I2C1_RX_DMA_IRQ                 DMA1_Channel0_IRQn
#endif

/* DMA1 Channel1 - UART4_TX / SPI1_TX / I2C1_TX (conflict) */
#if defined(BSP_UART4_TX_USING_DMA) && !defined(UART4_TX_DMA_PERIPH)
#define UART4_DMA_TX_IRQHandler          DMA1_Channel1_IRQHandler
#define UART4_TX_DMA_PERIPH              DMA1
#define UART4_TX_DMA_FLAG                DMA_INTF_FTFIF
#define UART4_TX_DMA_RCU                 RCU_DMA1
#define UART4_TX_DMA_CHANNEL             DMA_CH1
#define UART4_TX_DMA_REQUEST             DMA_REQUEST_UART4_TX
#define UART4_TX_DMA_IRQ                 DMA1_Channel1_IRQn
#endif

#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_TX_DMA_PERIPH)
#define SPI1_DMA_TX_IRQHandler          DMA1_Channel1_IRQHandler
#define SPI1_TX_DMA_PERIPH              DMA1
#define SPI1_TX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI1_TX_DMA_RCU                 RCU_DMA1
#define SPI1_TX_DMA_CHANNEL             DMA_CH1
#define SPI1_TX_DMA_REQUEST             DMA_REQUEST_SPI1_TX
#define SPI1_TX_DMA_IRQ                 DMA1_Channel1_IRQn
#endif

#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_PERIPH)
#define I2C1_DMA_TX_IRQHandler          DMA1_Channel1_IRQHandler
#define I2C1_TX_DMA_PERIPH              DMA1
#define I2C1_TX_DMA_FLAG                DMA_INTF_FTFIF
#define I2C1_TX_DMA_RCU                 RCU_DMA1
#define I2C1_TX_DMA_CHANNEL             DMA_CH1
#define I2C1_TX_DMA_REQUEST             DMA_REQUEST_I2C1_TX
#define I2C1_TX_DMA_IRQ                 DMA1_Channel1_IRQn
#endif

/* DMA1 Channel2 - UART5_RX / SPI2_RX / I2C2_RX (conflict) */
#if defined(BSP_UART5_RX_USING_DMA) && !defined(UART5_RX_DMA_PERIPH)
#define UART5_DMA_RX_IRQHandler          DMA1_Channel2_IRQHandler
#define UART5_RX_DMA_PERIPH              DMA1
#define UART5_RX_DMA_FLAG                DMA_INTF_FTFIF
#define UART5_RX_DMA_RCU                 RCU_DMA1
#define UART5_RX_DMA_CHANNEL             DMA_CH2
#define UART5_RX_DMA_REQUEST             DMA_REQUEST_USART5_RX
#define UART5_RX_DMA_IRQ                 DMA1_Channel2_IRQn
#endif

#if defined(BSP_SPI2_USING_DMA) && !defined(SPI2_RX_DMA_PERIPH)
#define SPI2_DMA_RX_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI2_RX_DMA_PERIPH              DMA1
#define SPI2_RX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI2_RX_DMA_RCU                 RCU_DMA1
#define SPI2_RX_DMA_CHANNEL             DMA_CH2
#define SPI2_RX_DMA_REQUEST             DMA_REQUEST_SPI2_RX
#define SPI2_RX_DMA_IRQ                 DMA1_Channel2_IRQn
#endif

#if defined(BSP_I2C2_RX_USING_DMA) && !defined(I2C2_RX_DMA_PERIPH)
#define I2C2_DMA_RX_IRQHandler          DMA1_Channel2_IRQHandler
#define I2C2_RX_DMA_PERIPH              DMA1
#define I2C2_RX_DMA_FLAG                DMA_INTF_FTFIF
#define I2C2_RX_DMA_RCU                 RCU_DMA1
#define I2C2_RX_DMA_CHANNEL             DMA_CH2
#define I2C2_RX_DMA_REQUEST             DMA_REQUEST_I2C2_RX
#define I2C2_RX_DMA_IRQ                 DMA1_Channel2_IRQn
#endif

/* DMA1 Channel3 - UART5_TX / SPI2_TX / I2C2_TX (conflict) */
#if defined(BSP_UART5_TX_USING_DMA) && !defined(UART5_TX_DMA_PERIPH)
#define UART5_DMA_TX_IRQHandler          DMA1_Channel3_IRQHandler
#define UART5_TX_DMA_PERIPH              DMA1
#define UART5_TX_DMA_FLAG                DMA_INTF_FTFIF
#define UART5_TX_DMA_RCU                 RCU_DMA1
#define UART5_TX_DMA_CHANNEL             DMA_CH3
#define UART5_TX_DMA_REQUEST             DMA_REQUEST_USART5_TX
#define UART5_TX_DMA_IRQ                 DMA1_Channel3_IRQn
#endif

#if defined(BSP_SPI2_USING_DMA) && !defined(SPI2_TX_DMA_PERIPH)
#define SPI2_DMA_TX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI2_TX_DMA_PERIPH              DMA1
#define SPI2_TX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI2_TX_DMA_RCU                 RCU_DMA1
#define SPI2_TX_DMA_CHANNEL             DMA_CH3
#define SPI2_TX_DMA_REQUEST             DMA_REQUEST_SPI2_TX
#define SPI2_TX_DMA_IRQ                 DMA1_Channel3_IRQn
#endif

#if defined(BSP_I2C2_TX_USING_DMA) && !defined(I2C2_TX_DMA_PERIPH)
#define I2C2_DMA_TX_IRQHandler          DMA1_Channel3_IRQHandler
#define I2C2_TX_DMA_PERIPH              DMA1
#define I2C2_TX_DMA_FLAG                DMA_INTF_FTFIF
#define I2C2_TX_DMA_RCU                 RCU_DMA1
#define I2C2_TX_DMA_CHANNEL             DMA_CH3
#define I2C2_TX_DMA_REQUEST             DMA_REQUEST_I2C2_TX
#define I2C2_TX_DMA_IRQ                 DMA1_Channel3_IRQn
#endif

/* DMA1 Channel4 - UART6_RX / SPI3_RX / I2C3_RX (conflict) */
#if defined(BSP_UART6_RX_USING_DMA) && !defined(UART6_RX_DMA_PERIPH)
#define UART6_DMA_RX_IRQHandler          DMA1_Channel4_IRQHandler
#define UART6_RX_DMA_PERIPH              DMA1
#define UART6_RX_DMA_FLAG                DMA_INTF_FTFIF
#define UART6_RX_DMA_RCU                 RCU_DMA1
#define UART6_RX_DMA_CHANNEL             DMA_CH4
#define UART6_RX_DMA_REQUEST             DMA_REQUEST_UART6_RX
#define UART6_RX_DMA_IRQ                 DMA1_Channel4_IRQn
#endif

#if defined(BSP_SPI3_USING_DMA) && !defined(SPI3_RX_DMA_PERIPH)
#define SPI3_DMA_RX_IRQHandler          DMA1_Channel4_IRQHandler
#define SPI3_RX_DMA_PERIPH              DMA1
#define SPI3_RX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI3_RX_DMA_RCU                 RCU_DMA1
#define SPI3_RX_DMA_CHANNEL             DMA_CH4
#define SPI3_RX_DMA_REQUEST             DMA_REQUEST_SPI3_RX
#define SPI3_RX_DMA_IRQ                 DMA1_Channel4_IRQn
#endif

#if defined(BSP_I2C3_RX_USING_DMA) && !defined(I2C3_RX_DMA_PERIPH)
#define I2C3_DMA_RX_IRQHandler          DMA1_Channel4_IRQHandler
#define I2C3_RX_DMA_PERIPH              DMA1
#define I2C3_RX_DMA_FLAG                DMA_INTF_FTFIF
#define I2C3_RX_DMA_RCU                 RCU_DMA1
#define I2C3_RX_DMA_CHANNEL             DMA_CH4
#define I2C3_RX_DMA_REQUEST             DMA_REQUEST_I2C3_RX
#define I2C3_RX_DMA_IRQ                 DMA1_Channel4_IRQn
#endif

/* DMA1 Channel5 - UART6_TX / SPI3_TX / I2C3_TX (conflict) */
#if defined(BSP_UART6_TX_USING_DMA) && !defined(UART6_TX_DMA_PERIPH)
#define UART6_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define UART6_TX_DMA_PERIPH              DMA1
#define UART6_TX_DMA_FLAG                DMA_INTF_FTFIF
#define UART6_TX_DMA_RCU                 RCU_DMA1
#define UART6_TX_DMA_CHANNEL             DMA_CH5
#define UART6_TX_DMA_REQUEST             DMA_REQUEST_UART6_TX
#define UART6_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#endif

#if defined(BSP_SPI3_USING_DMA) && !defined(SPI3_TX_DMA_PERIPH)
#define SPI3_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define SPI3_TX_DMA_PERIPH              DMA1
#define SPI3_TX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI3_TX_DMA_RCU                 RCU_DMA1
#define SPI3_TX_DMA_CHANNEL             DMA_CH5
#define SPI3_TX_DMA_REQUEST             DMA_REQUEST_SPI3_TX
#define SPI3_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#endif

#if defined(BSP_I2C3_TX_USING_DMA) && !defined(I2C3_TX_DMA_PERIPH)
#define I2C3_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define I2C3_TX_DMA_PERIPH              DMA1
#define I2C3_TX_DMA_FLAG                DMA_INTF_FTFIF
#define I2C3_TX_DMA_RCU                 RCU_DMA1
#define I2C3_TX_DMA_CHANNEL             DMA_CH5
#define I2C3_TX_DMA_REQUEST             DMA_REQUEST_I2C3_TX
#define I2C3_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#endif

/* DMA1 Channel6 - UART7_RX / I2C0_RX (conflict) */
#if defined(BSP_UART7_RX_USING_DMA) && !defined(UART7_RX_DMA_PERIPH)
#define UART7_DMA_RX_IRQHandler          DMA1_Channel6_IRQHandler
#define UART7_RX_DMA_PERIPH              DMA1
#define UART7_RX_DMA_FLAG                DMA_INTF_FTFIF
#define UART7_RX_DMA_RCU                 RCU_DMA1
#define UART7_RX_DMA_CHANNEL             DMA_CH6
#define UART7_RX_DMA_REQUEST             DMA_REQUEST_UART7_RX
#define UART7_RX_DMA_IRQ                 DMA1_Channel6_IRQn
#endif

#if defined(BSP_I2C0_RX_USING_DMA) && !defined(I2C0_RX_DMA_PERIPH)
#define I2C0_DMA_RX_IRQHandler          DMA1_Channel6_IRQHandler
#define I2C0_RX_DMA_PERIPH              DMA1
#define I2C0_RX_DMA_FLAG                DMA_INTF_FTFIF
#define I2C0_RX_DMA_RCU                 RCU_DMA1
#define I2C0_RX_DMA_CHANNEL             DMA_CH6
#define I2C0_RX_DMA_REQUEST             DMA_REQUEST_I2C0_RX
#define I2C0_RX_DMA_IRQ                 DMA1_Channel6_IRQn
#endif

/* DMA1 Channel7 - UART7_TX / I2C0_TX (conflict) */
#if defined(BSP_UART7_TX_USING_DMA) && !defined(UART7_TX_DMA_PERIPH)
#define UART7_DMA_TX_IRQHandler          DMA1_Channel7_IRQHandler
#define UART7_TX_DMA_PERIPH              DMA1
#define UART7_TX_DMA_FLAG                DMA_INTF_FTFIF
#define UART7_TX_DMA_RCU                 RCU_DMA1
#define UART7_TX_DMA_CHANNEL             DMA_CH7
#define UART7_TX_DMA_REQUEST             DMA_REQUEST_UART7_TX
#define UART7_TX_DMA_IRQ                 DMA1_Channel7_IRQn
#endif

#if defined(BSP_I2C0_TX_USING_DMA) && !defined(I2C0_TX_DMA_PERIPH)
#define I2C0_DMA_TX_IRQHandler          DMA1_Channel7_IRQHandler
#define I2C0_TX_DMA_PERIPH              DMA1
#define I2C0_TX_DMA_FLAG                DMA_INTF_FTFIF
#define I2C0_TX_DMA_RCU                 RCU_DMA1
#define I2C0_TX_DMA_CHANNEL             DMA_CH7
#define I2C0_TX_DMA_REQUEST             DMA_REQUEST_I2C0_TX
#define I2C0_TX_DMA_IRQ                 DMA1_Channel7_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
