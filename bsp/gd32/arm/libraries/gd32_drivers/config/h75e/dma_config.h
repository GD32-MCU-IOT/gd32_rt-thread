/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA0 Channel0 */
#if defined(BSP_UART0_RX_USING_DMA) && !defined(UART0_RX_DMA_PERIPH)
#define UART0_DMA_RX_IRQHandler          DMA0_Channel0_IRQHandler
#define UART0_RX_DMA_PERIPH              DMA0
#define UART0_RX_DMA_FLAG                DMA_INTF_FTFIF
#define UART0_RX_DMA_RCU                 RCU_DMA0
#define UART0_RX_DMA_CHANNEL             Channel0
#define UART0_RX_DMA_REQUEST             DMA_REQUEST_USART0_RX
#define UART0_RX_DMA_IRQ                 DMA0_Channel0_IRQn
#endif

/* DMA0 Channel1 */
#if defined(BSP_UART0_TX_USING_DMA) && !defined(UART0_TX_DMA_PERIPH)
#define UART0_DMA_TX_IRQHandler          DMA0_Channel1_IRQHandler
#define UART0_TX_DMA_PERIPH              DMA0
#define UART0_TX_DMA_FLAG                DMA_INTF_FTFIF
#define UART0_TX_DMA_RCU                 RCU_DMA0
#define UART0_TX_DMA_CHANNEL             Channel1
#define UART0_TX_DMA_REQUEST             DMA_REQUEST_USART0_TX
#define UART0_TX_DMA_IRQ                 DMA0_Channel1_IRQn
#endif

/* DMA0 Channel2 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_PERIPH)
#define UART1_DMA_RX_IRQHandler          DMA0_Channel2_IRQHandler
#define UART1_RX_DMA_PERIPH              DMA0
#define UART1_RX_DMA_FLAG                DMA_INTF_FTFIF
#define UART1_RX_DMA_RCU                 RCU_DMA0
#define UART1_RX_DMA_CHANNEL             Channel2
#define UART1_RX_DMA_REQUEST             DMA_REQUEST_USART1_RX
#define UART1_TX_DMA_IRQ                 DMA0_Channel2_IRQn
#endif

/* DMA0 Channel3 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_PERIPH)
#define UART1_DMA_TX_IRQHandler          DMA0_Channel3_IRQHandler
#define UART1_TX_DMA_PERIPH              DMA0
#define UART1_TX_DMA_FLAG                DMA_INTF_FTFIF
#define UART1_TX_DMA_RCU                 RCU_DMA0
#define UART1_TX_DMA_CHANNEL             Channel3
#define UART1_TX_DMA_REQUEST             DMA_REQUEST_USART1_TX
#define UART1_TX_DMA_IRQ                 DMA0_Channel3_IRQn
#endif

/* DMA0 Channel4 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_PERIPH)
#define UART2_DMA_RX_IRQHandler          DMA0_Channel4_IRQHandler
#define UART2_RX_DMA_PERIPH              DMA0
#define UART2_RX_DMA_FLAG                DMA_INTF_FTFIF
#define UART2_RX_DMA_RCU                 RCU_DMA0
#define UART2_RX_DMA_CHANNEL             Channel4
#define UART2_RX_DMA_REQUEST             DMA_REQUEST_USART2_RX
#define UART2_RX_DMA_IRQ                 DMA0_Channel4_IRQn
#endif

/* DMA0 Channel5 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_PERIPH)
#define UART2_DMA_TX_IRQHandler          DMA0_Channel5_IRQHandler
#define UART2_TX_DMA_PERIPH              DMA0
#define UART2_TX_DMA_FLAG                DMA_INTF_FTFIF
#define UART2_TX_DMA_RCU                 RCU_DMA0
#define UART2_TX_DMA_CHANNEL             Channel5
#define UART2_TX_DMA_REQUEST             DMA_REQUEST_USART2_TX
#define UART2_TX_DMA_IRQ                 DMA0_Channel5_IRQn
#endif


/* DMA0 Channel6 */
#if defined(BSP_SPI0_RX_USING_DMA) && !defined(SPI0_RX_DMA_PERIPH)
#define SPI0_DMA_RX_IRQHandler          DMA0_Channel6_IRQHandler
#define SPI0_RX_DMA_PERIPH              DMA0
#define SPI0_RX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI0_RX_DMA_RCU                 RCU_DMA0
#define SPI0_RX_DMA_CHANNEL             Channel6
#define SPI0_RX_DMA_REQUEST             DMA_REQUEST_SPI0_RX
#define SPI0_RX_DMA_IRQ                 DMA0_Channel6_IRQn
#endif

/* DMA0 Channel7 */
#if defined(BSP_SPI0_TX_USING_DMA) && !defined(SPI0_TX_DMA_PERIPH)
#define SPI0_DMA_TX_IRQHandler          DMA0_Channel7_IRQHandler
#define SPI0_TX_DMA_PERIPH              DMA0
#define SPI0_TX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI0_TX_DMA_RCU                 RCU_DMA0
#define SPI0_TX_DMA_CHANNEL             Channel7
#define SPI0_TX_DMA_REQUEST             DMA_REQUEST_SPI0_TX
#define SPI0_TX_DMA_IRQ                 DMA0_Channel7_IRQn
#endif

/* DMA1 Channel0 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_PERIPH)
#define SPI1_DMA_RX_IRQHandler          DMA1_Channel0_IRQHandler
#define SPI1_RX_DMA_PERIPH              DMA1
#define SPI1_RX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI1_RX_DMA_RCU                 RCU_DMA1
#define SPI1_RX_DMA_CHANNEL             Channel0
#define SPI1_RX_DMA_REQUEST             DMA_REQUEST_SPI1_RX
#define SPI1_RX_DMA_IRQ                 DMA1_Channel0_IRQn
#endif

/* DMA1 Channel1 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_PERIPH)
#define SPI1_DMA_TX_IRQHandler          DMA1_Channel1_IRQHandler
#define SPI1_TX_DMA_PERIPH              DMA1
#define SPI1_TX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI1_TX_DMA_RCU                 RCU_DMA1
#define SPI1_TX_DMA_CHANNEL             Channel1
#define SPI1_TX_DMA_REQUEST             DMA_REQUEST_SPI1_TX
#define SPI1_TX_DMA_IRQ                 DMA1_Channel1_IRQn
#endif

/* DMA1 Channel2 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_PERIPH)
#define SPI2_DMA_RX_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI2_RX_DMA_PERIPH              DMA1
#define SPI2_RX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI2_RX_DMA_RCU                 RCU_DMA1
#define SPI2_RX_DMA_CHANNEL             Channel2
#define SPI2_RX_DMA_REQUEST             DMA_REQUEST_SPI2_RX
#define SPI2_RX_DMA_IRQ                 DMA1_Channel2_IRQn
#endif

/* DMA1 Channel3 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_PERIPH)
#define SPI2_DMA_RX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI2_RX_DMA_PERIPH              DMA1
#define SPI2_RX_DMA_FLAG                DMA_INTF_FTFIF
#define SPI2_RX_DMA_RCU                 RCU_DMA1
#define SPI2_RX_DMA_CHANNEL             Channel3
#define SPI2_RX_DMA_REQUEST             DMA_REQUEST_SPI2_RX
#define SPI1_TX_DMA_IRQ                 DMA1_Channel1_IRQn
#endif

/* DMA1 Channel4 */
#if defined(BSP_I2C0_RX_USING_DMA) && !defined(I2C0_RX_DMA_PERIPH)
#define I2C0_DMA_RX_IRQHandler           DMA1_Channel4_IRQHandler
#define I2C0_RX_DMA_PERIPH               DMA1
#define I2C0_RX_DMA_FLAG                 DMA_INTF_FTFIF
#define I2C0_RX_DMA_RCU                  RCU_DMA1
#define I2C0_RX_DMA_CHANNEL              Channel4
#define I2C0_RX_DMA_REQUEST              DMA_REQUEST_I2C0_RX
#define I2C0_RX_DMA_IRQ                  DMA1_Channel4_IRQn
#endif

/* DMA1 Channel4 */
#if defined(BSP_I2C0_TX_USING_DMA) && !defined(I2C0_TX_DMA_PERIPH)
#define I2C0_DMA_TX_IRQHandler           DMA1_Channel4_IRQHandler
#define I2C0_TX_DMA_PERIPH               DMA1
#define I2C0_TX_DMA_FLAG                 DMA_INTF_FTFIF
#define I2C0_TX_DMA_RCU                  RCU_DMA1
#define I2C0_TX_DMA_CHANNEL              Channel4
#define I2C0_TX_DMA_REQUEST              DMA_REQUEST_I2C0_TX
#define I2C0_TX_DMA_IRQ                  DMA1_Channel4_IRQn
#endif

/* DMA1 Channel6 */
#if defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_PERIPH)
#define I2C1_DMA_RX_IRQHandler           DMA1_Channel6_IRQHandler
#define I2C1_RX_DMA_PERIPH               DMA1
#define I2C1_RX_DMA_FLAG                 DMA_INTF_FTFIF
#define I2C1_RX_DMA_RCU                  RCU_DMA1
#define I2C1_RX_DMA_CHANNEL              Channel6
#define I2C1_RX_DMA_REQUEST              DMA_REQUEST_I2C1_RX
#define I2C1_RX_DMA_IRQ                  DMA1_Channel6_IRQn
#endif

/* DMA1 Channel7 */
#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_PERIPH)
#define I2C1_DMA_TX_IRQHandler           DMA1_Channel7_IRQHandler
#define I2C1_TX_DMA_PERIPH               DMA1
#define I2C1_TX_DMA_FLAG                 DMA_INTF_FTFIF
#define I2C1_TX_DMA_RCU                  RCU_DMA1
#define I2C1_TX_DMA_CHANNEL              Channel7
#define I2C1_TX_DMA_REQUEST              DMA_REQUEST_I2C1_TX
#define I2C1_TX_DMA_IRQ                  DMA1_Channel7_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
