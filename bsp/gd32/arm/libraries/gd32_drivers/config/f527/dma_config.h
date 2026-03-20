/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-03-19     RT-Thread    Rework GD32F527 DMA mapping per user manual tables 14-2/14-3
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * DMA Channel Allocation Table for GD32F527:
 * ============================================================
 * DMA0 Channel0 - I2C0_RX    (subperi 1)
 * DMA0 Channel1 - UART0_RX   (subperi 4) / I2C3_RX (subperi 0) / I2C4_RX (subperi 1)
 * DMA0 Channel2 - UART0_TX   (subperi 4) / I2C2_RX (subperi 3) / I2C1_RX (subperi 7)
 * DMA0 Channel3 - SPI0_RX    (subperi 3) / I2C4_TX (subperi 1)
 * DMA0 Channel4 - SPI1_TX    (subperi 0) / I2C2_TX (subperi 3)
 * DMA0 Channel5 - SPI0_TX    (subperi 3) / I2C5_RX (subperi 6)
 * DMA0 Channel6 - I2C0_TX    (subperi 1) / I2C3_TX (subperi 0)
 * DMA0 Channel7 - I2C1_TX    (subperi 7) / I2C5_TX (subperi 6)
 * ------------------------------------------------------------
 * DMA1 Channel0 - SPI3_RX    (subperi 4)
 * DMA1 Channel1 - SPI3_TX    (subperi 4)
 * DMA1 Channel2 - SPI4_RX    (subperi 2)
 * DMA1 Channel3 - SPI1_RX    (subperi 0)
 * DMA1 Channel4 - SPI4_TX    (subperi 2)
 * DMA1 Channel5 - SPI5_TX    (subperi 1)
 * DMA1 Channel6 - SPI5_RX    (subperi 1)
 * DMA1 Channel7 - Reserved
 * ============================================================
 */

/* ==================== DMA0 Channel Configuration ==================== */

/* DMA0 Channel0 - I2C0_RX */
#if defined(BSP_I2C0_RX_USING_DMA) && !defined(I2C0_RX_DMA_PERIPH)
#define I2C0_DMA_RX_IRQHandler          DMA0_Channel0_IRQHandler
#define I2C0_RX_DMA_PERIPH              DMA0
#define I2C0_RX_DMA_RCU                 RCU_DMA0
#define I2C0_RX_DMA_CHANNEL             DMA_CH0
#define I2C0_RX_DMA_IRQ                 DMA0_Channel0_IRQn
#define I2C0_RX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* DMA0 Channel1 - UART0_RX / I2C3_RX / I2C4_RX */
#if defined(BSP_UART0_RX_USING_DMA) && !defined(UART0_RX_DMA_PERIPH)
#define UART0_DMA_RX_IRQHandler         DMA0_Channel1_IRQHandler
#define UART0_RX_DMA_PERIPH             DMA0
#define UART0_RX_DMA_RCU                RCU_DMA0
#define UART0_RX_DMA_CHANNEL            DMA_CH1
#define UART0_RX_DMA_IRQ                DMA0_Channel1_IRQn
#define UART0_RX_DMA_SUBPERI            DMA_SUBPERI4
#elif defined(BSP_I2C3_RX_USING_DMA) && !defined(I2C3_RX_DMA_PERIPH)
#define I2C3_DMA_RX_IRQHandler          DMA0_Channel1_IRQHandler
#define I2C3_RX_DMA_PERIPH              DMA0
#define I2C3_RX_DMA_RCU                 RCU_DMA0
#define I2C3_RX_DMA_CHANNEL             DMA_CH1
#define I2C3_RX_DMA_IRQ                 DMA0_Channel1_IRQn
#define I2C3_RX_DMA_SUBPERI             DMA_SUBPERI0
#elif defined(BSP_I2C4_RX_USING_DMA) && !defined(I2C4_RX_DMA_PERIPH)
#define I2C4_DMA_RX_IRQHandler          DMA0_Channel1_IRQHandler
#define I2C4_RX_DMA_PERIPH              DMA0
#define I2C4_RX_DMA_RCU                 RCU_DMA0
#define I2C4_RX_DMA_CHANNEL             DMA_CH1
#define I2C4_RX_DMA_IRQ                 DMA0_Channel1_IRQn
#define I2C4_RX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* DMA0 Channel2 - UART0_TX / I2C2_RX / I2C1_RX */
#if defined(BSP_UART0_TX_USING_DMA) && !defined(UART0_TX_DMA_PERIPH)
#define UART0_DMA_TX_IRQHandler         DMA0_Channel2_IRQHandler
#define UART0_TX_DMA_PERIPH             DMA0
#define UART0_TX_DMA_RCU                RCU_DMA0
#define UART0_TX_DMA_CHANNEL            DMA_CH2
#define UART0_TX_DMA_IRQ                DMA0_Channel2_IRQn
#define UART0_TX_DMA_SUBPERI            DMA_SUBPERI4
#elif defined(BSP_I2C2_RX_USING_DMA) && !defined(I2C2_RX_DMA_PERIPH)
#define I2C2_DMA_RX_IRQHandler          DMA0_Channel2_IRQHandler
#define I2C2_RX_DMA_PERIPH              DMA0
#define I2C2_RX_DMA_RCU                 RCU_DMA0
#define I2C2_RX_DMA_CHANNEL             DMA_CH2
#define I2C2_RX_DMA_IRQ                 DMA0_Channel2_IRQn
#define I2C2_RX_DMA_SUBPERI             DMA_SUBPERI3
#elif defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_PERIPH)
#define I2C1_DMA_RX_IRQHandler          DMA0_Channel2_IRQHandler
#define I2C1_RX_DMA_PERIPH              DMA0
#define I2C1_RX_DMA_RCU                 RCU_DMA0
#define I2C1_RX_DMA_CHANNEL             DMA_CH2
#define I2C1_RX_DMA_IRQ                 DMA0_Channel2_IRQn
#define I2C1_RX_DMA_SUBPERI             DMA_SUBPERI7
#endif

/* DMA0 Channel3 - SPI0_RX / I2C4_TX */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_RX_DMA_PERIPH)
#define SPI0_DMA_RX_IRQHandler          DMA0_Channel3_IRQHandler
#define SPI0_RX_DMA_PERIPH              DMA0
#define SPI0_RX_DMA_RCU                 RCU_DMA0
#define SPI0_RX_DMA_CHANNEL             DMA_CH3
#define SPI0_RX_DMA_IRQ                 DMA0_Channel3_IRQn
#define SPI0_RX_DMA_SUBPERI             DMA_SUBPERI3
#elif defined(BSP_I2C4_TX_USING_DMA) && !defined(I2C4_TX_DMA_PERIPH)
#define I2C4_DMA_TX_IRQHandler          DMA0_Channel3_IRQHandler
#define I2C4_TX_DMA_PERIPH              DMA0
#define I2C4_TX_DMA_RCU                 RCU_DMA0
#define I2C4_TX_DMA_CHANNEL             DMA_CH3
#define I2C4_TX_DMA_IRQ                 DMA0_Channel3_IRQn
#define I2C4_TX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* DMA0 Channel4 - SPI1_TX / I2C2_TX */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_TX_DMA_PERIPH)
#define SPI1_DMA_TX_IRQHandler          DMA0_Channel4_IRQHandler
#define SPI1_TX_DMA_PERIPH              DMA0
#define SPI1_TX_DMA_RCU                 RCU_DMA0
#define SPI1_TX_DMA_CHANNEL             DMA_CH4
#define SPI1_TX_DMA_IRQ                 DMA0_Channel4_IRQn
#define SPI1_TX_DMA_SUBPERI             DMA_SUBPERI0
#elif defined(BSP_I2C2_TX_USING_DMA) && !defined(I2C2_TX_DMA_PERIPH)
#define I2C2_DMA_TX_IRQHandler          DMA0_Channel4_IRQHandler
#define I2C2_TX_DMA_PERIPH              DMA0
#define I2C2_TX_DMA_RCU                 RCU_DMA0
#define I2C2_TX_DMA_CHANNEL             DMA_CH4
#define I2C2_TX_DMA_IRQ                 DMA0_Channel4_IRQn
#define I2C2_TX_DMA_SUBPERI             DMA_SUBPERI3
#endif

/* DMA0 Channel5 - SPI0_TX / I2C5_RX */
#if defined(BSP_SPI0_USING_DMA) && !defined(SPI0_TX_DMA_PERIPH)
#define SPI0_DMA_TX_IRQHandler          DMA0_Channel5_IRQHandler
#define SPI0_TX_DMA_PERIPH              DMA0
#define SPI0_TX_DMA_RCU                 RCU_DMA0
#define SPI0_TX_DMA_CHANNEL             DMA_CH5
#define SPI0_TX_DMA_IRQ                 DMA0_Channel5_IRQn
#define SPI0_TX_DMA_SUBPERI             DMA_SUBPERI3
#elif defined(BSP_I2C5_RX_USING_DMA) && !defined(I2C5_RX_DMA_PERIPH)
#define I2C5_DMA_RX_IRQHandler          DMA0_Channel5_IRQHandler
#define I2C5_RX_DMA_PERIPH              DMA0
#define I2C5_RX_DMA_RCU                 RCU_DMA0
#define I2C5_RX_DMA_CHANNEL             DMA_CH5
#define I2C5_RX_DMA_IRQ                 DMA0_Channel5_IRQn
#define I2C5_RX_DMA_SUBPERI             DMA_SUBPERI6
#endif

/* DMA0 Channel6 - I2C0_TX / I2C3_TX */
#if defined(BSP_I2C0_TX_USING_DMA) && !defined(I2C0_TX_DMA_PERIPH)
#define I2C0_DMA_TX_IRQHandler          DMA0_Channel6_IRQHandler
#define I2C0_TX_DMA_PERIPH              DMA0
#define I2C0_TX_DMA_RCU                 RCU_DMA0
#define I2C0_TX_DMA_CHANNEL             DMA_CH6
#define I2C0_TX_DMA_IRQ                 DMA0_Channel6_IRQn
#define I2C0_TX_DMA_SUBPERI             DMA_SUBPERI1
#elif defined(BSP_I2C3_TX_USING_DMA) && !defined(I2C3_TX_DMA_PERIPH)
#define I2C3_DMA_TX_IRQHandler          DMA0_Channel6_IRQHandler
#define I2C3_TX_DMA_PERIPH              DMA0
#define I2C3_TX_DMA_RCU                 RCU_DMA0
#define I2C3_TX_DMA_CHANNEL             DMA_CH6
#define I2C3_TX_DMA_IRQ                 DMA0_Channel6_IRQn
#define I2C3_TX_DMA_SUBPERI             DMA_SUBPERI0
#endif

/* DMA0 Channel7 - I2C1_TX / I2C5_TX */
#if defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_PERIPH)
#define I2C1_DMA_TX_IRQHandler          DMA0_Channel7_IRQHandler
#define I2C1_TX_DMA_PERIPH              DMA0
#define I2C1_TX_DMA_RCU                 RCU_DMA0
#define I2C1_TX_DMA_CHANNEL             DMA_CH7
#define I2C1_TX_DMA_IRQ                 DMA0_Channel7_IRQn
#define I2C1_TX_DMA_SUBPERI             DMA_SUBPERI7
#elif defined(BSP_I2C5_TX_USING_DMA) && !defined(I2C5_TX_DMA_PERIPH)
#define I2C5_DMA_TX_IRQHandler          DMA0_Channel7_IRQHandler
#define I2C5_TX_DMA_PERIPH              DMA0
#define I2C5_TX_DMA_RCU                 RCU_DMA0
#define I2C5_TX_DMA_CHANNEL             DMA_CH7
#define I2C5_TX_DMA_IRQ                 DMA0_Channel7_IRQn
#define I2C5_TX_DMA_SUBPERI             DMA_SUBPERI6
#endif

/* ==================== DMA1 Channel Configuration ==================== */

/* DMA1 Channel0 - SPI3_RX */
#if defined(BSP_SPI3_USING_DMA) && !defined(SPI3_RX_DMA_PERIPH)
#define SPI3_DMA_RX_IRQHandler          DMA1_Channel0_IRQHandler
#define SPI3_RX_DMA_PERIPH              DMA1
#define SPI3_RX_DMA_RCU                 RCU_DMA1
#define SPI3_RX_DMA_CHANNEL             DMA_CH0
#define SPI3_RX_DMA_IRQ                 DMA1_Channel0_IRQn
#define SPI3_RX_DMA_SUBPERI             DMA_SUBPERI4
#endif

/* DMA1 Channel1 - SPI3_TX */
#if defined(BSP_SPI3_USING_DMA) && !defined(SPI3_TX_DMA_PERIPH)
#define SPI3_DMA_TX_IRQHandler          DMA1_Channel1_IRQHandler
#define SPI3_TX_DMA_PERIPH              DMA1
#define SPI3_TX_DMA_RCU                 RCU_DMA1
#define SPI3_TX_DMA_CHANNEL             DMA_CH1
#define SPI3_TX_DMA_IRQ                 DMA1_Channel1_IRQn
#define SPI3_TX_DMA_SUBPERI             DMA_SUBPERI4
#endif

/* DMA1 Channel2 - SPI4_RX */
#if defined(BSP_SPI4_USING_DMA) && !defined(SPI4_RX_DMA_PERIPH)
#define SPI4_DMA_RX_IRQHandler          DMA1_Channel2_IRQHandler
#define SPI4_RX_DMA_PERIPH              DMA1
#define SPI4_RX_DMA_RCU                 RCU_DMA1
#define SPI4_RX_DMA_CHANNEL             DMA_CH2
#define SPI4_RX_DMA_IRQ                 DMA1_Channel2_IRQn
#define SPI4_RX_DMA_SUBPERI             DMA_SUBPERI2
#endif

/* DMA1 Channel3 - SPI1_RX */
#if defined(BSP_SPI1_USING_DMA) && !defined(SPI1_RX_DMA_PERIPH)
#define SPI1_DMA_RX_IRQHandler          DMA1_Channel3_IRQHandler
#define SPI1_RX_DMA_PERIPH              DMA1
#define SPI1_RX_DMA_RCU                 RCU_DMA1
#define SPI1_RX_DMA_CHANNEL             DMA_CH3
#define SPI1_RX_DMA_IRQ                 DMA1_Channel3_IRQn
#define SPI1_RX_DMA_SUBPERI             DMA_SUBPERI0
#endif

/* DMA1 Channel4 - SPI4_TX */
#if defined(BSP_SPI4_USING_DMA) && !defined(SPI4_TX_DMA_PERIPH)
#define SPI4_DMA_TX_IRQHandler          DMA1_Channel4_IRQHandler
#define SPI4_TX_DMA_PERIPH              DMA1
#define SPI4_TX_DMA_RCU                 RCU_DMA1
#define SPI4_TX_DMA_CHANNEL             DMA_CH4
#define SPI4_TX_DMA_IRQ                 DMA1_Channel4_IRQn
#define SPI4_TX_DMA_SUBPERI             DMA_SUBPERI2
#endif

/* DMA1 Channel5 - SPI5_TX */
#if defined(BSP_SPI5_USING_DMA) && !defined(SPI5_TX_DMA_PERIPH)
#define SPI5_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define SPI5_TX_DMA_PERIPH              DMA1
#define SPI5_TX_DMA_RCU                 RCU_DMA1
#define SPI5_TX_DMA_CHANNEL             DMA_CH5
#define SPI5_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#define SPI5_TX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* DMA1 Channel6 - SPI5_RX */
#if defined(BSP_SPI5_USING_DMA) && !defined(SPI5_RX_DMA_PERIPH)
#define SPI5_DMA_RX_IRQHandler          DMA1_Channel6_IRQHandler
#define SPI5_RX_DMA_PERIPH              DMA1
#define SPI5_RX_DMA_RCU                 RCU_DMA1
#define SPI5_RX_DMA_CHANNEL             DMA_CH6
#define SPI5_RX_DMA_IRQ                 DMA1_Channel6_IRQn
#define SPI5_RX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* ==================== UART DMA Channel Configuration ==================== */
/*
 * UART DMA Channel Allocation (from GD32F527 reference manual):
 * Note: These channels may conflict with SPI/I2C allocations above.
 *       The !defined() guards allow board-level override.
 *
 * UART0 RX: DMA0 CH1 SUBPERI4 (defined above)
 * UART0 TX: DMA0 CH2 SUBPERI4 (defined above)
 * UART1 RX: DMA0 CH5 SUBPERI4 (conflicts with SPI0_TX)
 * UART1 TX: DMA0 CH6 SUBPERI4 (conflicts with I2C0_TX)
 * UART2 RX: DMA0 CH1 SUBPERI4 (conflicts with UART0_RX)
 * UART2 TX: DMA0 CH3 SUBPERI4 (conflicts with SPI0_RX)
 * UART3 RX: DMA0 CH2 SUBPERI4 (conflicts with UART0_TX)
 * UART3 TX: DMA0 CH4 SUBPERI4 (conflicts with SPI1_TX)
 * UART4 RX: DMA0 CH0 SUBPERI4 (conflicts with I2C0_RX)
 * UART4 TX: DMA0 CH7 SUBPERI4 (conflicts with I2C1_TX)
 * UART5 RX: DMA1 CH1 SUBPERI5 (conflicts with SPI3_TX)
 * UART5 TX: DMA1 CH7 SUBPERI5 (conflicts with I2C1_RX)
 * UART6 RX: DMA0 CH3 SUBPERI5 (conflicts with SPI0_RX)
 * UART6 TX: DMA0 CH1 SUBPERI5 (conflicts with UART0_RX)
 * UART7 RX: DMA0 CH6 SUBPERI5 (conflicts with I2C0_TX)
 * UART7 TX: DMA0 CH0 SUBPERI5 (conflicts with I2C0_RX)
 */

/* UART1_RX - DMA0 Channel5 Subperi4 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_PERIPH)
#define UART1_DMA_RX_IRQHandler         DMA0_Channel5_IRQHandler
#define UART1_RX_DMA_PERIPH             DMA0
#define UART1_RX_DMA_RCU                RCU_DMA0
#define UART1_RX_DMA_CHANNEL            DMA_CH5
#define UART1_RX_DMA_IRQ                DMA0_Channel5_IRQn
#define UART1_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* UART1_TX - DMA0 Channel6 Subperi4 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_PERIPH)
#define UART1_DMA_TX_IRQHandler         DMA0_Channel6_IRQHandler
#define UART1_TX_DMA_PERIPH             DMA0
#define UART1_TX_DMA_RCU                RCU_DMA0
#define UART1_TX_DMA_CHANNEL            DMA_CH6
#define UART1_TX_DMA_IRQ                DMA0_Channel6_IRQn
#define UART1_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* UART2_RX - DMA0 Channel1 Subperi4 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_PERIPH)
#define UART2_DMA_RX_IRQHandler         DMA0_Channel1_IRQHandler
#define UART2_RX_DMA_PERIPH             DMA0
#define UART2_RX_DMA_RCU                RCU_DMA0
#define UART2_RX_DMA_CHANNEL            DMA_CH1
#define UART2_RX_DMA_IRQ                DMA0_Channel1_IRQn
#define UART2_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* UART2_TX - DMA0 Channel3 Subperi4 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_PERIPH)
#define UART2_DMA_TX_IRQHandler         DMA0_Channel3_IRQHandler
#define UART2_TX_DMA_PERIPH             DMA0
#define UART2_TX_DMA_RCU                RCU_DMA0
#define UART2_TX_DMA_CHANNEL            DMA_CH3
#define UART2_TX_DMA_IRQ                DMA0_Channel3_IRQn
#define UART2_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* UART3_RX - DMA0 Channel2 Subperi4 */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_PERIPH)
#define UART3_DMA_RX_IRQHandler         DMA0_Channel2_IRQHandler
#define UART3_RX_DMA_PERIPH             DMA0
#define UART3_RX_DMA_RCU                RCU_DMA0
#define UART3_RX_DMA_CHANNEL            DMA_CH2
#define UART3_RX_DMA_IRQ                DMA0_Channel2_IRQn
#define UART3_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* UART3_TX - DMA0 Channel4 Subperi4 */
#if defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_PERIPH)
#define UART3_DMA_TX_IRQHandler         DMA0_Channel4_IRQHandler
#define UART3_TX_DMA_PERIPH             DMA0
#define UART3_TX_DMA_RCU                RCU_DMA0
#define UART3_TX_DMA_CHANNEL            DMA_CH4
#define UART3_TX_DMA_IRQ                DMA0_Channel4_IRQn
#define UART3_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* UART4_RX - DMA0 Channel0 Subperi4 */
#if defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_PERIPH)
#define UART4_DMA_RX_IRQHandler         DMA0_Channel0_IRQHandler
#define UART4_RX_DMA_PERIPH             DMA0
#define UART4_RX_DMA_RCU                RCU_DMA0
#define UART4_RX_DMA_CHANNEL            DMA_CH0
#define UART4_RX_DMA_IRQ                DMA0_Channel0_IRQn
#define UART4_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* UART4_TX - DMA0 Channel7 Subperi4 */
#if defined(BSP_UART4_TX_USING_DMA) && !defined(UART4_TX_DMA_PERIPH)
#define UART4_DMA_TX_IRQHandler         DMA0_Channel7_IRQHandler
#define UART4_TX_DMA_PERIPH             DMA0
#define UART4_TX_DMA_RCU                RCU_DMA0
#define UART4_TX_DMA_CHANNEL            DMA_CH7
#define UART4_TX_DMA_IRQ                DMA0_Channel7_IRQn
#define UART4_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* UART5_RX - DMA1 Channel1 Subperi5 */
#if defined(BSP_UART5_RX_USING_DMA) && !defined(UART5_RX_DMA_PERIPH)
#define UART5_DMA_RX_IRQHandler         DMA1_Channel1_IRQHandler
#define UART5_RX_DMA_PERIPH             DMA1
#define UART5_RX_DMA_RCU                RCU_DMA1
#define UART5_RX_DMA_CHANNEL            DMA_CH1
#define UART5_RX_DMA_IRQ                DMA1_Channel1_IRQn
#define UART5_RX_DMA_SUBPERI            DMA_SUBPERI5
#endif

/* UART5_TX - DMA1 Channel7 Subperi5 */
#if defined(BSP_UART5_TX_USING_DMA) && !defined(UART5_TX_DMA_PERIPH)
#define UART5_DMA_TX_IRQHandler         DMA1_Channel7_IRQHandler
#define UART5_TX_DMA_PERIPH             DMA1
#define UART5_TX_DMA_RCU                RCU_DMA1
#define UART5_TX_DMA_CHANNEL            DMA_CH7
#define UART5_TX_DMA_IRQ                DMA1_Channel7_IRQn
#define UART5_TX_DMA_SUBPERI            DMA_SUBPERI5
#endif

/* UART6_RX - DMA0 Channel3 Subperi5 */
#if defined(BSP_UART6_RX_USING_DMA) && !defined(UART6_RX_DMA_PERIPH)
#define UART6_DMA_RX_IRQHandler         DMA0_Channel3_IRQHandler
#define UART6_RX_DMA_PERIPH             DMA0
#define UART6_RX_DMA_RCU                RCU_DMA0
#define UART6_RX_DMA_CHANNEL            DMA_CH3
#define UART6_RX_DMA_IRQ                DMA0_Channel3_IRQn
#define UART6_RX_DMA_SUBPERI            DMA_SUBPERI5
#endif

/* UART6_TX - DMA0 Channel1 Subperi5 */
#if defined(BSP_UART6_TX_USING_DMA) && !defined(UART6_TX_DMA_PERIPH)
#define UART6_DMA_TX_IRQHandler         DMA0_Channel1_IRQHandler
#define UART6_TX_DMA_PERIPH             DMA0
#define UART6_TX_DMA_RCU                RCU_DMA0
#define UART6_TX_DMA_CHANNEL            DMA_CH1
#define UART6_TX_DMA_IRQ                DMA0_Channel1_IRQn
#define UART6_TX_DMA_SUBPERI            DMA_SUBPERI5
#endif

/* UART7_RX - DMA0 Channel6 Subperi5 */
#if defined(BSP_UART7_RX_USING_DMA) && !defined(UART7_RX_DMA_PERIPH)
#define UART7_DMA_RX_IRQHandler         DMA0_Channel6_IRQHandler
#define UART7_RX_DMA_PERIPH             DMA0
#define UART7_RX_DMA_RCU                RCU_DMA0
#define UART7_RX_DMA_CHANNEL            DMA_CH6
#define UART7_RX_DMA_IRQ                DMA0_Channel6_IRQn
#define UART7_RX_DMA_SUBPERI            DMA_SUBPERI5
#endif

/* UART7_TX - DMA0 Channel0 Subperi5 */
#if defined(BSP_UART7_TX_USING_DMA) && !defined(UART7_TX_DMA_PERIPH)
#define UART7_DMA_TX_IRQHandler         DMA0_Channel0_IRQHandler
#define UART7_TX_DMA_PERIPH             DMA0
#define UART7_TX_DMA_RCU                RCU_DMA0
#define UART7_TX_DMA_CHANNEL            DMA_CH0
#define UART7_TX_DMA_IRQ                DMA0_Channel0_IRQn
#define UART7_TX_DMA_SUBPERI            DMA_SUBPERI5
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
