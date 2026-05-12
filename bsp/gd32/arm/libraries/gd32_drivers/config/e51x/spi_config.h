/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-12     RT-Thread    first implementation for GD32E51x
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GD32E51x SPI DMA config — no subperiph field (fixed-wired channels) */

/* SPI0 RX: DMA0 CH1 */
#if defined(BSP_SPI0_USING_DMA)
#ifndef SPI0_RX_DMA_CONFIG
#define SPI0_RX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = SPI0_RX_DMA_PERIPH,                           \
        .rcu        = SPI0_RX_DMA_RCU,                               \
        .channel    = SPI0_RX_DMA_CHANNEL,                           \
        .irq        = SPI0_RX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
/* SPI0 TX: DMA0 CH2 */
#ifndef SPI0_TX_DMA_CONFIG
#define SPI0_TX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = SPI0_TX_DMA_PERIPH,                           \
        .rcu        = SPI0_TX_DMA_RCU,                               \
        .channel    = SPI0_TX_DMA_CHANNEL,                           \
        .irq        = SPI0_TX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif /* BSP_SPI0_USING_DMA */

/* SPI1 RX: DMA0 CH3 */
#if defined(BSP_SPI1_USING_DMA)
#ifndef SPI1_RX_DMA_CONFIG
#define SPI1_RX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = SPI1_RX_DMA_PERIPH,                           \
        .rcu        = SPI1_RX_DMA_RCU,                               \
        .channel    = SPI1_RX_DMA_CHANNEL,                           \
        .irq        = SPI1_RX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
/* SPI1 TX: DMA0 CH4 */
#ifndef SPI1_TX_DMA_CONFIG
#define SPI1_TX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = SPI1_TX_DMA_PERIPH,                           \
        .rcu        = SPI1_TX_DMA_RCU,                               \
        .channel    = SPI1_TX_DMA_CHANNEL,                           \
        .irq        = SPI1_TX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif /* BSP_SPI1_USING_DMA */

/* SPI2 RX: DMA1 CH0 */
#if defined(BSP_SPI2_USING_DMA)
#ifndef SPI2_RX_DMA_CONFIG
#define SPI2_RX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = SPI2_RX_DMA_PERIPH,                           \
        .rcu        = SPI2_RX_DMA_RCU,                               \
        .channel    = SPI2_RX_DMA_CHANNEL,                           \
        .irq        = SPI2_RX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
/* SPI2 TX: DMA1 CH1 */
#ifndef SPI2_TX_DMA_CONFIG
#define SPI2_TX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = SPI2_TX_DMA_PERIPH,                           \
        .rcu        = SPI2_TX_DMA_RCU,                               \
        .channel    = SPI2_TX_DMA_CHANNEL,                           \
        .irq        = SPI2_TX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif /* BSP_SPI2_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_CONFIG_H__ */
