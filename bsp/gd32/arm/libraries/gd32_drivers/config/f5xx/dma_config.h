/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-01-05     RT-Thread    first implementation for GD32F5xx
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 channel0 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_INSTANCE)
#define SPI2_DMA_RX_IRQHandler          DMA1_Channel0_IRQHandler
#define SPI2_RX_DMA_RCC                 RCU_DMA1
#define SPI2_RX_DMA_INSTANCE            DMA1
#define SPI2_RX_DMA_CHANNEL             DMA_CH0
#define SPI2_RX_DMA_IRQ                 DMA1_Channel0_IRQn
#define SPI2_RX_DMA_SUBPERI             DMA_SUBPERI0
#elif defined(BSP_UART4_TX_USING_DMA) && !defined(UART4_TX_DMA_INSTANCE)
#define UART4_DMA_TX_IRQHandler         DMA1_Channel0_IRQHandler
#define UART4_TX_DMA_RCC                RCU_DMA1
#define UART4_TX_DMA_INSTANCE           DMA1
#define UART4_TX_DMA_CHANNEL            DMA_CH0
#define UART4_TX_DMA_IRQ                DMA1_Channel0_IRQn
#define UART4_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* DMA1 channel1 */
#if defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_INSTANCE)
#define SPI2_DMA_TX_IRQHandler          DMA1_Channel1_IRQHandler
#define SPI2_TX_DMA_RCC                 RCU_DMA1
#define SPI2_TX_DMA_INSTANCE            DMA1
#define SPI2_TX_DMA_CHANNEL             DMA_CH1
#define SPI2_TX_DMA_IRQ                 DMA1_Channel1_IRQn
#define SPI2_TX_DMA_SUBPERI             DMA_SUBPERI0
#elif defined(BSP_UART6_RX_USING_DMA) && !defined(UART6_RX_DMA_INSTANCE)
#define UART6_DMA_RX_IRQHandler         DMA1_Channel1_IRQHandler
#define UART6_RX_DMA_RCC                RCU_DMA1
#define UART6_RX_DMA_INSTANCE           DMA1
#define UART6_RX_DMA_CHANNEL            DMA_CH1
#define UART6_RX_DMA_IRQ                DMA1_Channel1_IRQn
#define UART6_RX_DMA_SUBPERI            DMA_SUBPERI5
#endif

/* DMA1 channel2 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_DMA_RX_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI1_RX_DMA_RCC                 RCU_DMA1
#define SPI1_RX_DMA_INSTANCE            DMA1
#define SPI1_RX_DMA_CHANNEL             DMA_CH2
#define SPI1_RX_DMA_IRQ                 DMA1_Channel2_IRQn
#define SPI1_RX_DMA_SUBPERI             DMA_SUBPERI0
#elif defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_INSTANCE)
#define UART4_DMA_RX_IRQHandler         DMA1_Channel2_IRQHandler
#define UART4_RX_DMA_RCC                RCU_DMA1
#define UART4_RX_DMA_INSTANCE           DMA1
#define UART4_RX_DMA_CHANNEL            DMA_CH2
#define UART4_RX_DMA_IRQ                DMA1_Channel2_IRQn
#define UART4_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* DMA1 channel3 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_DMA_TX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI1_TX_DMA_RCC                 RCU_DMA1
#define SPI1_TX_DMA_INSTANCE            DMA1
#define SPI1_TX_DMA_CHANNEL             DMA_CH3
#define SPI1_TX_DMA_IRQ                 DMA1_Channel3_IRQn
#define SPI1_TX_DMA_SUBPERI             DMA_SUBPERI0
#elif defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_INSTANCE)
#define UART2_DMA_TX_IRQHandler         DMA1_Channel3_IRQHandler
#define UART2_TX_DMA_RCC                RCU_DMA1
#define UART2_TX_DMA_INSTANCE           DMA1
#define UART2_TX_DMA_CHANNEL            DMA_CH3
#define UART2_TX_DMA_IRQ                DMA1_Channel3_IRQn
#define UART2_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* DMA1 channel4 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART2_DMA_RX_IRQHandler         DMA1_Channel4_IRQHandler
#define UART2_RX_DMA_RCC                RCU_DMA1
#define UART2_RX_DMA_INSTANCE           DMA1
#define UART2_RX_DMA_CHANNEL            DMA_CH4
#define UART2_RX_DMA_IRQ                DMA1_Channel4_IRQn
#define UART2_RX_DMA_SUBPERI            DMA_SUBPERI4
#elif defined(BSP_SPI4_RX_USING_DMA) && !defined(SPI4_RX_DMA_INSTANCE)
#define SPI4_DMA_RX_IRQHandler          DMA1_Channel4_IRQHandler
#define SPI4_RX_DMA_RCC                 RCU_DMA1
#define SPI4_RX_DMA_INSTANCE            DMA1
#define SPI4_RX_DMA_CHANNEL             DMA_CH4
#define SPI4_RX_DMA_IRQ                 DMA1_Channel4_IRQn
#define SPI4_RX_DMA_SUBPERI             DMA_SUBPERI2
#endif

/* DMA1 channel5 */
#if defined(BSP_UART0_RX_USING_DMA) && !defined(UART0_RX_DMA_INSTANCE)
#define UART0_DMA_RX_IRQHandler         DMA1_Channel5_IRQHandler
#define UART0_RX_DMA_RCC                RCU_DMA1
#define UART0_RX_DMA_INSTANCE           DMA1
#define UART0_RX_DMA_CHANNEL            DMA_CH5
#define UART0_RX_DMA_IRQ                DMA1_Channel5_IRQn
#define UART0_RX_DMA_SUBPERI            DMA_SUBPERI4
#elif defined(BSP_SPI4_TX_USING_DMA) && !defined(SPI4_TX_DMA_INSTANCE)
#define SPI4_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define SPI4_TX_DMA_RCC                 RCU_DMA1
#define SPI4_TX_DMA_INSTANCE            DMA1
#define SPI4_TX_DMA_CHANNEL             DMA_CH5
#define SPI4_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#define SPI4_TX_DMA_SUBPERI             DMA_SUBPERI2
#elif defined(BSP_SPI5_TX_USING_DMA) && !defined(SPI5_TX_DMA_INSTANCE)
#define SPI5_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define SPI5_TX_DMA_RCC                 RCU_DMA1
#define SPI5_TX_DMA_INSTANCE            DMA1
#define SPI5_TX_DMA_CHANNEL             DMA_CH5
#define SPI5_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#define SPI5_TX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* DMA1 channel6 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_DMA_RX_IRQHandler         DMA1_Channel6_IRQHandler
#define UART1_RX_DMA_RCC                RCU_DMA1
#define UART1_RX_DMA_INSTANCE           DMA1
#define UART1_RX_DMA_CHANNEL            DMA_CH6
#define UART1_RX_DMA_IRQ                DMA1_Channel6_IRQn
#define UART1_RX_DMA_SUBPERI            DMA_SUBPERI4
#elif defined(BSP_UART6_TX_USING_DMA) && !defined(UART6_TX_DMA_INSTANCE)
#define UART6_DMA_TX_IRQHandler         DMA1_Channel6_IRQHandler
#define UART6_TX_DMA_RCC                RCU_DMA1
#define UART6_TX_DMA_INSTANCE           DMA1
#define UART6_TX_DMA_CHANNEL            DMA_CH6
#define UART6_TX_DMA_IRQ                DMA1_Channel6_IRQn
#define UART6_TX_DMA_SUBPERI            DMA_SUBPERI5
#elif defined(BSP_SPI5_RX_USING_DMA) && !defined(SPI5_RX_DMA_INSTANCE)
#define SPI5_DMA_RX_IRQHandler          DMA1_Channel6_IRQHandler
#define SPI5_RX_DMA_RCC                 RCU_DMA1
#define SPI5_RX_DMA_INSTANCE            DMA1
#define SPI5_RX_DMA_CHANNEL             DMA_CH6
#define SPI5_RX_DMA_IRQ                 DMA1_Channel6_IRQn
#define SPI5_RX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* DMA1 channel7 */
#if defined(BSP_UART0_TX_USING_DMA) && !defined(UART0_TX_DMA_INSTANCE)
#define UART0_DMA_TX_IRQHandler         DMA1_Channel7_IRQHandler
#define UART0_TX_DMA_RCC                RCU_DMA1
#define UART0_TX_DMA_INSTANCE           DMA1
#define UART0_TX_DMA_CHANNEL            DMA_CH7
#define UART0_TX_DMA_IRQ                DMA1_Channel7_IRQn
#define UART0_TX_DMA_SUBPERI            DMA_SUBPERI4
#elif defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_INSTANCE)
#define UART1_DMA_TX_IRQHandler         DMA1_Channel7_IRQHandler
#define UART1_TX_DMA_RCC                RCU_DMA1
#define UART1_TX_DMA_INSTANCE           DMA1
#define UART1_TX_DMA_CHANNEL            DMA_CH7
#define UART1_TX_DMA_IRQ                DMA1_Channel7_IRQn
#define UART1_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* DMA0 channel0 */
#if defined(BSP_SPI3_RX_USING_DMA) && !defined(SPI3_RX_DMA_INSTANCE)
#define SPI3_DMA_RX_IRQHandler          DMA0_Channel0_IRQHandler
#define SPI3_RX_DMA_RCC                 RCU_DMA0
#define SPI3_RX_DMA_INSTANCE            DMA0
#define SPI3_RX_DMA_CHANNEL             DMA_CH0
#define SPI3_RX_DMA_IRQ                 DMA0_Channel0_IRQn
#define SPI3_RX_DMA_SUBPERI             DMA_SUBPERI4
#elif defined(BSP_I2C0_RX_USING_DMA) && !defined(I2C0_RX_DMA_INSTANCE)
#define I2C0_DMA_RX_IRQHandler          DMA0_Channel0_IRQHandler
#define I2C0_RX_DMA_RCC                 RCU_DMA0
#define I2C0_RX_DMA_INSTANCE            DMA0
#define I2C0_RX_DMA_CHANNEL             DMA_CH0
#define I2C0_RX_DMA_IRQ                 DMA0_Channel0_IRQn
#define I2C0_RX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* DMA0 channel1 */
#if defined(BSP_SPI3_TX_USING_DMA) && !defined(SPI3_TX_DMA_INSTANCE)
#define SPI3_DMA_TX_IRQHandler          DMA0_Channel1_IRQHandler
#define SPI3_TX_DMA_RCC                 RCU_DMA0
#define SPI3_TX_DMA_INSTANCE            DMA0
#define SPI3_TX_DMA_CHANNEL             DMA_CH1
#define SPI3_TX_DMA_IRQ                 DMA0_Channel1_IRQn
#define SPI3_TX_DMA_SUBPERI             DMA_SUBPERI4
#endif

/* DMA0 channel2 */
#if defined(BSP_I2C2_RX_USING_DMA) && !defined(I2C2_RX_DMA_INSTANCE)
#define I2C2_DMA_RX_IRQHandler          DMA0_Channel2_IRQHandler
#define I2C2_RX_DMA_RCC                 RCU_DMA0
#define I2C2_RX_DMA_INSTANCE            DMA0
#define I2C2_RX_DMA_CHANNEL             DMA_CH2
#define I2C2_RX_DMA_IRQ                 DMA0_Channel2_IRQn
#define I2C2_RX_DMA_SUBPERI             DMA_SUBPERI3
#elif defined(BSP_SPI0_RX_USING_DMA) && !defined(SPI0_RX_DMA_INSTANCE)
#define SPI0_DMA_RX_IRQHandler          DMA0_Channel2_IRQHandler
#define SPI0_RX_DMA_RCC                 RCU_DMA0
#define SPI0_RX_DMA_INSTANCE            DMA0
#define SPI0_RX_DMA_CHANNEL             DMA_CH2
#define SPI0_RX_DMA_IRQ                 DMA0_Channel2_IRQn
#define SPI0_RX_DMA_SUBPERI             DMA_SUBPERI3
#elif defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_INSTANCE)
#define I2C1_DMA_RX_IRQHandler          DMA0_Channel2_IRQHandler
#define I2C1_RX_DMA_RCC                 RCU_DMA0
#define I2C1_RX_DMA_INSTANCE            DMA0
#define I2C1_RX_DMA_CHANNEL             DMA_CH2
#define I2C1_RX_DMA_IRQ                 DMA0_Channel2_IRQn
#define I2C1_RX_DMA_SUBPERI             DMA_SUBPERI7
#endif

/* DMA0 channel3 */
#if defined(BSP_SPI0_TX_USING_DMA) && !defined(SPI0_TX_DMA_INSTANCE)
#define SPI0_DMA_TX_IRQHandler          DMA0_Channel3_IRQHandler
#define SPI0_TX_DMA_RCC                 RCU_DMA0
#define SPI0_TX_DMA_INSTANCE            DMA0
#define SPI0_TX_DMA_CHANNEL             DMA_CH3
#define SPI0_TX_DMA_IRQ                 DMA0_Channel3_IRQn
#define SPI0_TX_DMA_SUBPERI             DMA_SUBPERI3
#endif

/* DMA0 channel4 */
#if defined(BSP_I2C2_TX_USING_DMA) && !defined(I2C2_TX_DMA_INSTANCE)
#define I2C2_DMA_TX_IRQHandler          DMA0_Channel4_IRQHandler
#define I2C2_TX_DMA_RCC                 RCU_DMA0
#define I2C2_TX_DMA_INSTANCE            DMA0
#define I2C2_TX_DMA_CHANNEL             DMA_CH4
#define I2C2_TX_DMA_IRQ                 DMA0_Channel4_IRQn
#define I2C2_TX_DMA_SUBPERI             DMA_SUBPERI3
#endif

/* DMA0 channel5 */
#if defined(BSP_I2C5_RX_USING_DMA) && !defined(I2C5_RX_DMA_INSTANCE)
#define I2C5_DMA_RX_IRQHandler          DMA0_Channel5_IRQHandler
#define I2C5_RX_DMA_RCC                 RCU_DMA0
#define I2C5_RX_DMA_INSTANCE            DMA0
#define I2C5_RX_DMA_CHANNEL             DMA_CH5
#define I2C5_RX_DMA_IRQ                 DMA0_Channel5_IRQn
#define I2C5_RX_DMA_SUBPERI             DMA_SUBPERI6
#endif

/* DMA0 channel6 - I2C0_TX / I2C3_TX */
#if defined(BSP_I2C0_TX_USING_DMA) && !defined(I2C0_TX_DMA_INSTANCE)
#define I2C0_DMA_TX_IRQHandler          DMA0_Channel6_IRQHandler
#define I2C0_TX_DMA_RCC                 RCU_DMA0
#define I2C0_TX_DMA_INSTANCE            DMA0
#define I2C0_TX_DMA_CHANNEL             DMA_CH6
#define I2C0_TX_DMA_IRQ                 DMA0_Channel6_IRQn
#define I2C0_TX_DMA_SUBPERI             DMA_SUBPERI1
#elif defined(BSP_I2C3_TX_USING_DMA) && !defined(I2C3_TX_DMA_INSTANCE)
#define I2C3_DMA_TX_IRQHandler          DMA0_Channel6_IRQHandler
#define I2C3_TX_DMA_RCC                 RCU_DMA0
#define I2C3_TX_DMA_INSTANCE            DMA0
#define I2C3_TX_DMA_CHANNEL             DMA_CH6
#define I2C3_TX_DMA_IRQ                 DMA0_Channel6_IRQn
#define I2C3_TX_DMA_SUBPERI             DMA_SUBPERI0
#endif

/* DMA0 channel7 - I2C1_TX / I2C5_TX */
#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_INSTANCE)
#define I2C1_DMA_TX_IRQHandler          DMA0_Channel7_IRQHandler
#define I2C1_TX_DMA_RCC                 RCU_DMA0
#define I2C1_TX_DMA_INSTANCE            DMA0
#define I2C1_TX_DMA_CHANNEL             DMA_CH7
#define I2C1_TX_DMA_IRQ                 DMA0_Channel7_IRQn
#define I2C1_TX_DMA_SUBPERI             DMA_SUBPERI7
#elif defined(BSP_I2C5_TX_USING_DMA) && !defined(I2C5_TX_DMA_INSTANCE)
#define I2C5_DMA_TX_IRQHandler          DMA0_Channel7_IRQHandler
#define I2C5_TX_DMA_RCC                 RCU_DMA0
#define I2C5_TX_DMA_INSTANCE            DMA0
#define I2C5_TX_DMA_CHANNEL             DMA_CH7
#define I2C5_TX_DMA_IRQ                 DMA0_Channel7_IRQn
#define I2C5_TX_DMA_SUBPERI             DMA_SUBPERI6
#endif

/* DMA0 channel1 - I2C3_RX (per user manual Table 14-2) */
#if defined(BSP_I2C3_RX_USING_DMA) && !defined(I2C3_RX_DMA_INSTANCE)
#define I2C3_DMA_RX_IRQHandler          DMA0_Channel1_IRQHandler
#define I2C3_RX_DMA_RCC                 RCU_DMA0
#define I2C3_RX_DMA_INSTANCE            DMA0
#define I2C3_RX_DMA_CHANNEL             DMA_CH1
#define I2C3_RX_DMA_IRQ                 DMA0_Channel1_IRQn
#define I2C3_RX_DMA_SUBPERI             DMA_SUBPERI0
#endif

/* DMA0 channel3 - I2C4_TX (Table 14-2: CH3, PERIEN=001) */
#if defined(BSP_I2C4_TX_USING_DMA) && !defined(I2C4_TX_DMA_INSTANCE)
#define I2C4_DMA_TX_IRQHandler          DMA0_Channel3_IRQHandler
#define I2C4_TX_DMA_RCC                 RCU_DMA0
#define I2C4_TX_DMA_INSTANCE            DMA0
#define I2C4_TX_DMA_CHANNEL             DMA_CH3
#define I2C4_TX_DMA_IRQ                 DMA0_Channel3_IRQn
#define I2C4_TX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* DMA0 channel1 - I2C4_RX (Table 14-2: CH1, PERIEN=001) */
#if defined(BSP_I2C4_RX_USING_DMA) && !defined(I2C4_RX_DMA_INSTANCE)
#define I2C4_DMA_RX_IRQHandler          DMA0_Channel1_IRQHandler
#define I2C4_RX_DMA_RCC                 RCU_DMA0
#define I2C4_RX_DMA_INSTANCE            DMA0
#define I2C4_RX_DMA_CHANNEL             DMA_CH1
#define I2C4_RX_DMA_IRQ                 DMA0_Channel1_IRQn
#define I2C4_RX_DMA_SUBPERI             DMA_SUBPERI1
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
