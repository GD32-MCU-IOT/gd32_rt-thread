/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-20     RT-Thread    first implementation for GD32L23x SPI DMA support
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_SPI0_USING_DMA)
#ifndef SPI0_TX_DMA_CONFIG
#define SPI0_TX_DMA_CONFIG                              \
    {                                                   \
        .periph     = SPI0_TX_DMA_PERIPH,               \
        .channel    = SPI0_TX_DMA_CHANNEL,              \
        .rcu        = SPI0_TX_DMA_RCU,                  \
        .request    = SPI0_TX_DMA_REQUEST,              \
        .irq        = SPI0_TX_DMA_IRQ,                  \
        .data_width = DMA_PERIPH_WIDTH_8BIT,            \
    }
#endif /* SPI0_TX_DMA_CONFIG */
#ifndef SPI0_RX_DMA_CONFIG
#define SPI0_RX_DMA_CONFIG                              \
    {                                                   \
        .periph     = SPI0_RX_DMA_PERIPH,               \
        .channel    = SPI0_RX_DMA_CHANNEL,              \
        .rcu        = SPI0_RX_DMA_RCU,                  \
        .request    = SPI0_RX_DMA_REQUEST,              \
        .irq        = SPI0_RX_DMA_IRQ,                  \
        .data_width = DMA_PERIPH_WIDTH_8BIT,            \
    }
#endif /* SPI0_RX_DMA_CONFIG */
#endif /* BSP_SPI0_USING_DMA */

#if defined(BSP_SPI1_USING_DMA)
#ifndef SPI1_TX_DMA_CONFIG
#define SPI1_TX_DMA_CONFIG                              \
    {                                                   \
        .periph     = SPI1_TX_DMA_PERIPH,               \
        .channel    = SPI1_TX_DMA_CHANNEL,              \
        .rcu        = SPI1_TX_DMA_RCU,                  \
        .request    = SPI1_TX_DMA_REQUEST,              \
        .irq        = SPI1_TX_DMA_IRQ,                  \
        .data_width = DMA_PERIPH_WIDTH_8BIT,            \
    }
#endif /* SPI1_TX_DMA_CONFIG */
#ifndef SPI1_RX_DMA_CONFIG
#define SPI1_RX_DMA_CONFIG                              \
    {                                                   \
        .periph     = SPI1_RX_DMA_PERIPH,               \
        .channel    = SPI1_RX_DMA_CHANNEL,              \
        .rcu        = SPI1_RX_DMA_RCU,                  \
        .request    = SPI1_RX_DMA_REQUEST,              \
        .irq        = SPI1_RX_DMA_IRQ,                  \
        .data_width = DMA_PERIPH_WIDTH_8BIT,            \
    }
#endif /* SPI1_RX_DMA_CONFIG */
#endif /* BSP_SPI1_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_CONFIG_H__ */
