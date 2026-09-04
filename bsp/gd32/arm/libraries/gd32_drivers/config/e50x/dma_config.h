/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-12     RT-Thread    first implementation for GD32E50x
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * DMA Channel Allocation Table for GD32E50x.
 * GD32E50x has standard DMA — NO DMAMUX, channels are hard-wired to peripherals.
 * Table reused from GD32E51x (pin/peripheral-compatible sibling series, confirmed
 * identical I2C/GPIO IP) — cross-check against the GD32E50x User Manual DMA request
 * mapping table before relying on it in production.
 * ============================================================
 * DMA0 (7 channels: CH0-CH6)
 * CH0: SPI/I2S        •        | USART  •         | I2C  •
 * CH1: SPI/I2S SPI0_RX         | USART  USART2_TX | I2C  •
 * CH2: SPI/I2S SPI0_TX         | USART  USART2_RX | I2C  •
 * CH3: SPI/I2S SPI1/I2S1_RX    | USART  USART0_TX | I2C  I2C1_TX / I2C2_TX
 * CH4: SPI/I2S SPI1/I2S1_TX    | USART  USART0_RX | I2C  I2C1_RX / I2C2_RX
 * CH5: SPI/I2S I2S1ADD_RX      | USART  USART1_RX | I2C  I2C0_TX
 * CH6: SPI/I2S I2S1ADD_TX      | USART  USART1_TX | I2C  I2C0_RX
 * ============================================================
 * DMA1 (5 channels: CH0-CH4)
 * CH0: SPI/I2S SPI2/I2S2_RX   | USART •              | SDIO •
 * CH1: SPI/I2S SPI2/I2S2_TX   | USART •              | SDIO •
 * CH2: SPI/I2S I2S2ADD_RX     | USART UART3_RX/USART5_RX
 * CH3: SPI/I2S I2S2ADD_TX     | USART •
 * CH4: SPI/I2S •              | USART UART3_TX/USART5_TX | SDIO SDIO
 * ============================================================
 * NOTE: Conflicting peripherals on the same channel cannot both use DMA.
 * Recommended conflict-free test set: SPI1 + USART2 + I2C0
 */

/* ==================== DMA0 Channel Configuration ==================== */

/* DMA0 Channel1 - SPI0_RX */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_RX_DMA_PERIPH)
#define SPI0_DMA_RX_IRQHandler          DMA0_Channel1_IRQHandler
#define SPI0_RX_DMA_PERIPH              DMA0
#define SPI0_RX_DMA_RCU                 RCU_DMA0
#define SPI0_RX_DMA_CHANNEL             DMA_CH1
#define SPI0_RX_DMA_IRQ                 DMA0_Channel1_IRQn
#endif

/* DMA0 Channel2 - SPI0_TX */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_TX_DMA_PERIPH)
#define SPI0_DMA_TX_IRQHandler          DMA0_Channel2_IRQHandler
#define SPI0_TX_DMA_PERIPH              DMA0
#define SPI0_TX_DMA_RCU                 RCU_DMA0
#define SPI0_TX_DMA_CHANNEL             DMA_CH2
#define SPI0_TX_DMA_IRQ                 DMA0_Channel2_IRQn
#endif

/* DMA0 Channel3 - SPI1/I2S1_RX / USART0_TX / I2C1_TX / I2C2_TX (conflict) */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_RX_DMA_PERIPH)
#define SPI1_DMA_RX_IRQHandler          DMA0_Channel3_IRQHandler
#define SPI1_RX_DMA_PERIPH              DMA0
#define SPI1_RX_DMA_RCU                 RCU_DMA0
#define SPI1_RX_DMA_CHANNEL             DMA_CH3
#define SPI1_RX_DMA_IRQ                 DMA0_Channel3_IRQn
#endif

#if defined(BSP_UART0_TX_USING_DMA) && !defined(UART0_TX_DMA_PERIPH)
#define UART0_DMA_TX_IRQHandler         DMA0_Channel3_IRQHandler
#define UART0_TX_DMA_PERIPH             DMA0
#define UART0_TX_DMA_RCU                RCU_DMA0
#define UART0_TX_DMA_CHANNEL            DMA_CH3
#define UART0_TX_DMA_IRQ                DMA0_Channel3_IRQn
#endif

#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_PERIPH)
#define I2C1_DMA_TX_IRQHandler          DMA0_Channel3_IRQHandler
#define I2C1_TX_DMA_PERIPH              DMA0
#define I2C1_TX_DMA_RCU                 RCU_DMA0
#define I2C1_TX_DMA_CHANNEL             DMA_CH3
#define I2C1_TX_DMA_IRQ                 DMA0_Channel3_IRQn
#endif

#if defined(BSP_I2C2_TX_USING_DMA) && !defined(I2C2_TX_DMA_PERIPH)
#define I2C2_DMA_TX_IRQHandler          DMA0_Channel3_IRQHandler
#define I2C2_TX_DMA_PERIPH              DMA0
#define I2C2_TX_DMA_RCU                 RCU_DMA0
#define I2C2_TX_DMA_CHANNEL             DMA_CH3
#define I2C2_TX_DMA_IRQ                 DMA0_Channel3_IRQn
#endif

/* DMA0 Channel4 - SPI1/I2S1_TX / USART0_RX / I2C1_RX / I2C2_RX (conflict) */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_TX_DMA_PERIPH)
#define SPI1_DMA_TX_IRQHandler          DMA0_Channel4_IRQHandler
#define SPI1_TX_DMA_PERIPH              DMA0
#define SPI1_TX_DMA_RCU                 RCU_DMA0
#define SPI1_TX_DMA_CHANNEL             DMA_CH4
#define SPI1_TX_DMA_IRQ                 DMA0_Channel4_IRQn
#endif

#if defined(BSP_UART0_RX_USING_DMA) && !defined(UART0_RX_DMA_PERIPH)
#define UART0_DMA_RX_IRQHandler         DMA0_Channel4_IRQHandler
#define UART0_RX_DMA_PERIPH             DMA0
#define UART0_RX_DMA_RCU                RCU_DMA0
#define UART0_RX_DMA_CHANNEL            DMA_CH4
#define UART0_RX_DMA_IRQ                DMA0_Channel4_IRQn
#endif

#if defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_PERIPH)
#define I2C1_DMA_RX_IRQHandler          DMA0_Channel4_IRQHandler
#define I2C1_RX_DMA_PERIPH              DMA0
#define I2C1_RX_DMA_RCU                 RCU_DMA0
#define I2C1_RX_DMA_CHANNEL             DMA_CH4
#define I2C1_RX_DMA_IRQ                 DMA0_Channel4_IRQn
#endif

#if defined(BSP_I2C2_RX_USING_DMA) && !defined(I2C2_RX_DMA_PERIPH)
#define I2C2_DMA_RX_IRQHandler          DMA0_Channel4_IRQHandler
#define I2C2_RX_DMA_PERIPH              DMA0
#define I2C2_RX_DMA_RCU                 RCU_DMA0
#define I2C2_RX_DMA_CHANNEL             DMA_CH4
#define I2C2_RX_DMA_IRQ                 DMA0_Channel4_IRQn
#endif

/* DMA0 Channel5 - I2S1ADD_RX / USART1_RX / I2C0_TX (conflict) */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_PERIPH)
#define UART1_DMA_RX_IRQHandler         DMA0_Channel5_IRQHandler
#define UART1_RX_DMA_PERIPH             DMA0
#define UART1_RX_DMA_RCU                RCU_DMA0
#define UART1_RX_DMA_CHANNEL            DMA_CH5
#define UART1_RX_DMA_IRQ                DMA0_Channel5_IRQn
#endif

#if defined(BSP_I2C0_TX_USING_DMA) && !defined(I2C0_TX_DMA_PERIPH)
#define I2C0_DMA_TX_IRQHandler          DMA0_Channel5_IRQHandler
#define I2C0_TX_DMA_PERIPH              DMA0
#define I2C0_TX_DMA_RCU                 RCU_DMA0
#define I2C0_TX_DMA_CHANNEL             DMA_CH5
#define I2C0_TX_DMA_IRQ                 DMA0_Channel5_IRQn
#endif

/* DMA0 Channel6 - I2S1ADD_TX / USART1_TX / I2C0_RX (conflict) */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_PERIPH)
#define UART1_DMA_TX_IRQHandler         DMA0_Channel6_IRQHandler
#define UART1_TX_DMA_PERIPH             DMA0
#define UART1_TX_DMA_RCU                RCU_DMA0
#define UART1_TX_DMA_CHANNEL            DMA_CH6
#define UART1_TX_DMA_IRQ                DMA0_Channel6_IRQn
#endif

#if defined(BSP_I2C0_RX_USING_DMA) && !defined(I2C0_RX_DMA_PERIPH)
#define I2C0_DMA_RX_IRQHandler          DMA0_Channel6_IRQHandler
#define I2C0_RX_DMA_PERIPH              DMA0
#define I2C0_RX_DMA_RCU                 RCU_DMA0
#define I2C0_RX_DMA_CHANNEL             DMA_CH6
#define I2C0_RX_DMA_IRQ                 DMA0_Channel6_IRQn
#endif

/* DMA0 Channel1 - USART2_TX (no conflict with SPI0_RX if SPI0 DMA not used) */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_PERIPH)
#define UART2_DMA_TX_IRQHandler         DMA0_Channel1_IRQHandler
#define UART2_TX_DMA_PERIPH             DMA0
#define UART2_TX_DMA_RCU                RCU_DMA0
#define UART2_TX_DMA_CHANNEL            DMA_CH1
#define UART2_TX_DMA_IRQ                DMA0_Channel1_IRQn
#endif

/* DMA0 Channel2 - USART2_RX (no conflict with SPI0_TX if SPI0 DMA not used) */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_PERIPH)
#define UART2_DMA_RX_IRQHandler         DMA0_Channel2_IRQHandler
#define UART2_RX_DMA_PERIPH             DMA0
#define UART2_RX_DMA_RCU                RCU_DMA0
#define UART2_RX_DMA_CHANNEL            DMA_CH2
#define UART2_RX_DMA_IRQ                DMA0_Channel2_IRQn
#endif

/* ==================== DMA1 Channel Configuration ==================== */

/* DMA1 Channel0 - SPI2/I2S2_RX */
#if defined(BSP_SPI2_USING_DMA) && !defined(SPI2_RX_DMA_PERIPH)
#define SPI2_DMA_RX_IRQHandler          DMA1_Channel0_IRQHandler
#define SPI2_RX_DMA_PERIPH              DMA1
#define SPI2_RX_DMA_RCU                 RCU_DMA1
#define SPI2_RX_DMA_CHANNEL             DMA_CH0
#define SPI2_RX_DMA_IRQ                 DMA1_Channel0_IRQn
#endif

/* DMA1 Channel1 - SPI2/I2S2_TX */
#if defined(BSP_SPI2_USING_DMA) && !defined(SPI2_TX_DMA_PERIPH)
#define SPI2_DMA_TX_IRQHandler          DMA1_Channel1_IRQHandler
#define SPI2_TX_DMA_PERIPH              DMA1
#define SPI2_TX_DMA_RCU                 RCU_DMA1
#define SPI2_TX_DMA_CHANNEL             DMA_CH1
#define SPI2_TX_DMA_IRQ                 DMA1_Channel1_IRQn
#endif

/* DMA1 Channel2 - UART3_RX / USART5_RX (conflict) */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_PERIPH)
#define UART3_DMA_RX_IRQHandler         DMA1_Channel2_IRQHandler
#define UART3_RX_DMA_PERIPH             DMA1
#define UART3_RX_DMA_RCU                RCU_DMA1
#define UART3_RX_DMA_CHANNEL            DMA_CH2
#define UART3_RX_DMA_IRQ                DMA1_Channel2_IRQn
#endif

#if defined(BSP_UART5_RX_USING_DMA) && !defined(UART5_RX_DMA_PERIPH)
#define UART5_DMA_RX_IRQHandler         DMA1_Channel2_IRQHandler
#define UART5_RX_DMA_PERIPH             DMA1
#define UART5_RX_DMA_RCU                RCU_DMA1
#define UART5_RX_DMA_CHANNEL            DMA_CH2
#define UART5_RX_DMA_IRQ                DMA1_Channel2_IRQn
#endif

/* DMA1 Channel3/4 share a single IRQ vector on GD32E50X_HD (unlike E51x, which has
 * a separate Channel4 vector) - UART3_TX / USART5_TX (conflict) */
#if defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_PERIPH)
#define UART3_DMA_TX_IRQHandler         DMA1_Channel3_4_IRQHandler
#define UART3_TX_DMA_PERIPH             DMA1
#define UART3_TX_DMA_RCU                RCU_DMA1
#define UART3_TX_DMA_CHANNEL            DMA_CH4
#define UART3_TX_DMA_IRQ                DMA1_Channel3_Channel4_IRQn
#endif

#if defined(BSP_UART5_TX_USING_DMA) && !defined(UART5_TX_DMA_PERIPH)
#define UART5_DMA_TX_IRQHandler         DMA1_Channel3_4_IRQHandler
#define UART5_TX_DMA_PERIPH             DMA1
#define UART5_TX_DMA_RCU                RCU_DMA1
#define UART5_TX_DMA_CHANNEL            DMA_CH4
#define UART5_TX_DMA_IRQ                DMA1_Channel3_Channel4_IRQn
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
