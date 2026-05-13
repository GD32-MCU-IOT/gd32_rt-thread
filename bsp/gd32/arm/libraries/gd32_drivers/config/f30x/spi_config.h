/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-29     RT-Thread    first implementation for GD32F30x
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SPI0 DMA configuration */
#ifdef BSP_SPI0_USING_DMA
#ifndef SPI0_TX_DMA_CONFIG
#define SPI0_TX_DMA_CONFIG                          \
    {                                               \
        .periph     = SPI0_TX_DMA_PERIPH,           \
        .dma_flag   = DMA_FLAG_FTF,                 \
        .rcu        = SPI0_TX_DMA_RCU,              \
        .channel    = SPI0_TX_DMA_CHANNEL,          \
        .irq        = SPI0_TX_DMA_IRQ,              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,    \
    }
#endif /* SPI0_TX_DMA_CONFIG */
#ifndef SPI0_RX_DMA_CONFIG
#define SPI0_RX_DMA_CONFIG                          \
    {                                               \
        .periph     = SPI0_RX_DMA_PERIPH,           \
        .dma_flag   = DMA_FLAG_FTF,                 \
        .rcu        = SPI0_RX_DMA_RCU,              \
        .channel    = SPI0_RX_DMA_CHANNEL,          \
        .irq        = SPI0_RX_DMA_IRQ,              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,    \
    }
#endif /* SPI0_RX_DMA_CONFIG */
#endif /* BSP_SPI0_USING_DMA */

/* SPI1 DMA configuration */
#ifdef BSP_SPI1_USING_DMA
#ifndef SPI1_TX_DMA_CONFIG
#define SPI1_TX_DMA_CONFIG                          \
    {                                               \
        .periph     = SPI1_TX_DMA_PERIPH,           \
        .dma_flag   = DMA_FLAG_FTF,                 \
        .rcu        = SPI1_TX_DMA_RCU,              \
        .channel    = SPI1_TX_DMA_CHANNEL,          \
        .irq        = SPI1_TX_DMA_IRQ,              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,    \
    }
#endif /* SPI1_TX_DMA_CONFIG */
#ifndef SPI1_RX_DMA_CONFIG
#define SPI1_RX_DMA_CONFIG                          \
    {                                               \
        .periph     = SPI1_RX_DMA_PERIPH,           \
        .dma_flag   = DMA_FLAG_FTF,                 \
        .rcu        = SPI1_RX_DMA_RCU,              \
        .channel    = SPI1_RX_DMA_CHANNEL,          \
        .irq        = SPI1_RX_DMA_IRQ,              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,    \
    }
#endif /* SPI1_RX_DMA_CONFIG */
#endif /* BSP_SPI1_USING_DMA */

/* SPI2 DMA configuration */
#ifdef BSP_SPI2_USING_DMA
#ifndef SPI2_TX_DMA_CONFIG
#define SPI2_TX_DMA_CONFIG                          \
    {                                               \
        .periph     = SPI2_TX_DMA_PERIPH,           \
        .dma_flag   = DMA_FLAG_FTF,                 \
        .rcu        = SPI2_TX_DMA_RCU,              \
        .channel    = SPI2_TX_DMA_CHANNEL,          \
        .irq        = SPI2_TX_DMA_IRQ,              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,    \
    }
#endif /* SPI2_TX_DMA_CONFIG */
#ifndef SPI2_RX_DMA_CONFIG
#define SPI2_RX_DMA_CONFIG                          \
    {                                               \
        .periph     = SPI2_RX_DMA_PERIPH,           \
        .dma_flag   = DMA_FLAG_FTF,                 \
        .rcu        = SPI2_RX_DMA_RCU,              \
        .channel    = SPI2_RX_DMA_CHANNEL,          \
        .irq        = SPI2_RX_DMA_IRQ,              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,    \
    }
#endif /* SPI2_RX_DMA_CONFIG */
#endif /* BSP_SPI2_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_CONFIG_H__ */
