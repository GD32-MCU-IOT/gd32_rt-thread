/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-10     RT-Thread    first implementation for GD32F10x
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * DMA Channel Allocation Table for GD32F10x:
 * ============================================================
 * GD32F10x has fixed DMA channel mapping (no sub-peripheral selection).
 *
 * DMA0:
 * CH0 - ADC0     / TIM1_CH2  / TIM3_CH0
 * CH1 - SPI0_RX  / USART2_TX / TIM0_CH0 / TIM1_UP  / TIM2_CH2
 * CH2 - SPI0_TX  / USART2_RX / TIM0_CH1 / TIM2_CH3 / TIM2_UP
 * CH3 - SPI1_RX  / USART0_TX / I2C1_TX  / TIM0_CH3 / TIM3_CH1
 * CH4 - SPI1_TX  / USART0_RX / I2C1_RX  / TIM0_UP  / TIM3_CH2
 * CH5 - USART1_RX / I2C0_TX  / TIM0_CH2 / TIM2_CH0
 * CH6 - USART1_TX / I2C0_RX  / TIM1_CH1 / TIM3_UP
 *
 * DMA1 (HD/XD/CL only):
 * CH0 - SPI2_RX  / TIM4_CH3 / TIM7_CH2
 * CH1 - SPI2_TX  / TIM4_CH2 / TIM7_CH3
 * CH2 - UART3_RX / TIM5_UP  / DAC_OUT0
 * CH3 - SDIO     / TIM4_CH1 / TIM6_UP  / DAC_OUT1
 * CH4 - UART3_TX / ADC2     / TIM4_CH0
 *
 * NOTE: UART4 has no DMA request line on GD32F10x.
 * NOTE: on HD/XD, DMA1 CH3 and CH4 share one interrupt vector.
 * ============================================================
 */

/* ==================== UART DMA Channel Configuration ==================== */

/* USART0_TX - DMA0 Channel3 */
#if defined(BSP_UART0_TX_USING_DMA) && !defined(UART0_TX_DMA_PERIPH)
#define UART0_DMA_TX_IRQHandler         DMA0_Channel3_IRQHandler
#define UART0_TX_DMA_PERIPH             DMA0
#define UART0_TX_DMA_RCU                RCU_DMA0
#define UART0_TX_DMA_CHANNEL            DMA_CH3
#define UART0_TX_DMA_IRQ                DMA0_Channel3_IRQn
#endif

/* USART0_RX - DMA0 Channel4 */
#if defined(BSP_UART0_RX_USING_DMA) && !defined(UART0_RX_DMA_PERIPH)
#define UART0_DMA_RX_IRQHandler         DMA0_Channel4_IRQHandler
#define UART0_RX_DMA_PERIPH             DMA0
#define UART0_RX_DMA_RCU                RCU_DMA0
#define UART0_RX_DMA_CHANNEL            DMA_CH4
#define UART0_RX_DMA_IRQ                DMA0_Channel4_IRQn
#endif

/* USART1_TX - DMA0 Channel6 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_PERIPH)
#define UART1_DMA_TX_IRQHandler         DMA0_Channel6_IRQHandler
#define UART1_TX_DMA_PERIPH             DMA0
#define UART1_TX_DMA_RCU                RCU_DMA0
#define UART1_TX_DMA_CHANNEL            DMA_CH6
#define UART1_TX_DMA_IRQ                DMA0_Channel6_IRQn
#endif

/* USART1_RX - DMA0 Channel5 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_PERIPH)
#define UART1_DMA_RX_IRQHandler         DMA0_Channel5_IRQHandler
#define UART1_RX_DMA_PERIPH             DMA0
#define UART1_RX_DMA_RCU                RCU_DMA0
#define UART1_RX_DMA_CHANNEL            DMA_CH5
#define UART1_RX_DMA_IRQ                DMA0_Channel5_IRQn
#endif

/* USART2_TX - DMA0 Channel1 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_PERIPH)
#define UART2_DMA_TX_IRQHandler         DMA0_Channel1_IRQHandler
#define UART2_TX_DMA_PERIPH             DMA0
#define UART2_TX_DMA_RCU                RCU_DMA0
#define UART2_TX_DMA_CHANNEL            DMA_CH1
#define UART2_TX_DMA_IRQ                DMA0_Channel1_IRQn
#endif

/* USART2_RX - DMA0 Channel2 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_PERIPH)
#define UART2_DMA_RX_IRQHandler         DMA0_Channel2_IRQHandler
#define UART2_RX_DMA_PERIPH             DMA0
#define UART2_RX_DMA_RCU                RCU_DMA0
#define UART2_RX_DMA_CHANNEL            DMA_CH2
#define UART2_RX_DMA_IRQ                DMA0_Channel2_IRQn
#endif

/* UART3_TX - DMA1 Channel4 */
#if defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_PERIPH)
#ifdef GD32F10X_CL
#define UART3_DMA_TX_IRQHandler         DMA1_Channel4_IRQHandler
#define UART3_TX_DMA_IRQ                DMA1_Channel4_IRQn
#else
#define UART3_DMA_TX_IRQHandler         DMA1_Channel3_4_IRQHandler
#define UART3_TX_DMA_IRQ                DMA1_Channel3_Channel4_IRQn
#endif
#define UART3_TX_DMA_PERIPH             DMA1
#define UART3_TX_DMA_RCU                RCU_DMA1
#define UART3_TX_DMA_CHANNEL            DMA_CH4
#endif

/* UART3_RX - DMA1 Channel2 */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_PERIPH)
#define UART3_DMA_RX_IRQHandler         DMA1_Channel2_IRQHandler
#define UART3_RX_DMA_PERIPH             DMA1
#define UART3_RX_DMA_RCU                RCU_DMA1
#define UART3_RX_DMA_CHANNEL            DMA_CH2
#define UART3_RX_DMA_IRQ                DMA1_Channel2_IRQn
#endif

/* ==================== SPI DMA Channel Configuration ==================== */

/* SPI0_TX - DMA0 Channel2 */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_TX_DMA_PERIPH)
#define SPI0_DMA_TX_IRQHandler          DMA0_Channel2_IRQHandler
#define SPI0_TX_DMA_PERIPH              DMA0
#define SPI0_TX_DMA_RCU                 RCU_DMA0
#define SPI0_TX_DMA_CHANNEL             DMA_CH2
#define SPI0_TX_DMA_IRQ                 DMA0_Channel2_IRQn
#endif

/* SPI0_RX - DMA0 Channel1 */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_RX_DMA_PERIPH)
#define SPI0_DMA_RX_IRQHandler          DMA0_Channel1_IRQHandler
#define SPI0_RX_DMA_PERIPH              DMA0
#define SPI0_RX_DMA_RCU                 RCU_DMA0
#define SPI0_RX_DMA_CHANNEL             DMA_CH1
#define SPI0_RX_DMA_IRQ                 DMA0_Channel1_IRQn
#endif

/* SPI1_TX - DMA0 Channel4 */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_TX_DMA_PERIPH)
#define SPI1_DMA_TX_IRQHandler          DMA0_Channel4_IRQHandler
#define SPI1_TX_DMA_PERIPH              DMA0
#define SPI1_TX_DMA_RCU                 RCU_DMA0
#define SPI1_TX_DMA_CHANNEL             DMA_CH4
#define SPI1_TX_DMA_IRQ                 DMA0_Channel4_IRQn
#endif

/* SPI1_RX - DMA0 Channel3 */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_RX_DMA_PERIPH)
#define SPI1_DMA_RX_IRQHandler          DMA0_Channel3_IRQHandler
#define SPI1_RX_DMA_PERIPH              DMA0
#define SPI1_RX_DMA_RCU                 RCU_DMA0
#define SPI1_RX_DMA_CHANNEL             DMA_CH3
#define SPI1_RX_DMA_IRQ                 DMA0_Channel3_IRQn
#endif

/* SPI2_TX - DMA1 Channel1 */
#if defined(BSP_SPI2_USING_DMA) && !defined(SPI2_TX_DMA_PERIPH)
#define SPI2_DMA_TX_IRQHandler          DMA1_Channel1_IRQHandler
#define SPI2_TX_DMA_PERIPH              DMA1
#define SPI2_TX_DMA_RCU                 RCU_DMA1
#define SPI2_TX_DMA_CHANNEL             DMA_CH1
#define SPI2_TX_DMA_IRQ                 DMA1_Channel1_IRQn
#endif

/* SPI2_RX - DMA1 Channel0 */
#if defined(BSP_SPI2_USING_DMA) && !defined(SPI2_RX_DMA_PERIPH)
#define SPI2_DMA_RX_IRQHandler          DMA1_Channel0_IRQHandler
#define SPI2_RX_DMA_PERIPH              DMA1
#define SPI2_RX_DMA_RCU                 RCU_DMA1
#define SPI2_RX_DMA_CHANNEL             DMA_CH0
#define SPI2_RX_DMA_IRQ                 DMA1_Channel0_IRQn
#endif

/* ==================== I2C DMA Channel Configuration ==================== */

/* I2C0_TX - DMA0 Channel5 */
#if defined(BSP_I2C0_TX_USING_DMA) && !defined(I2C0_TX_DMA_PERIPH)
#define I2C0_DMA_TX_IRQHandler          DMA0_Channel5_IRQHandler
#define I2C0_TX_DMA_PERIPH              DMA0
#define I2C0_TX_DMA_RCU                 RCU_DMA0
#define I2C0_TX_DMA_CHANNEL             DMA_CH5
#define I2C0_TX_DMA_IRQ                 DMA0_Channel5_IRQn
#endif

/* I2C0_RX - DMA0 Channel6 */
#if defined(BSP_I2C0_RX_USING_DMA) && !defined(I2C0_RX_DMA_PERIPH)
#define I2C0_DMA_RX_IRQHandler          DMA0_Channel6_IRQHandler
#define I2C0_RX_DMA_PERIPH              DMA0
#define I2C0_RX_DMA_RCU                 RCU_DMA0
#define I2C0_RX_DMA_CHANNEL             DMA_CH6
#define I2C0_RX_DMA_IRQ                 DMA0_Channel6_IRQn
#endif

/* I2C1_TX - DMA0 Channel3 */
#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_PERIPH)
#define I2C1_DMA_TX_IRQHandler          DMA0_Channel3_IRQHandler
#define I2C1_TX_DMA_PERIPH              DMA0
#define I2C1_TX_DMA_RCU                 RCU_DMA0
#define I2C1_TX_DMA_CHANNEL             DMA_CH3
#define I2C1_TX_DMA_IRQ                 DMA0_Channel3_IRQn
#endif

/* I2C1_RX - DMA0 Channel4 */
#if defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_PERIPH)
#define I2C1_DMA_RX_IRQHandler          DMA0_Channel4_IRQHandler
#define I2C1_RX_DMA_PERIPH              DMA0
#define I2C1_RX_DMA_RCU                 RCU_DMA0
#define I2C1_RX_DMA_CHANNEL             DMA_CH4
#define I2C1_RX_DMA_IRQ                 DMA0_Channel4_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
