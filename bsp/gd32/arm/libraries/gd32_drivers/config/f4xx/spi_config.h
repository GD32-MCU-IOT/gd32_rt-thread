/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-13     RT-Thread    first implementation for GD32F4xx
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
        .periph = SPI0_TX_DMA_PERIPH,               \
        .rcu = SPI0_TX_DMA_RCU,                     \
        .channel = SPI0_TX_DMA_CHANNEL,              \
        .subperiph = SPI0_TX_DMA_SUBPERI,            \
        .irq = SPI0_TX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI0_TX_DMA_CONFIG */
#ifndef SPI0_RX_DMA_CONFIG
#define SPI0_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI0_RX_DMA_PERIPH,               \
        .rcu = SPI0_RX_DMA_RCU,                     \
        .channel = SPI0_RX_DMA_CHANNEL,              \
        .subperiph = SPI0_RX_DMA_SUBPERI,            \
        .irq = SPI0_RX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI0_RX_DMA_CONFIG */
#endif /* BSP_SPI0_USING_DMA */

/* SPI1 DMA configuration */
#ifdef BSP_SPI1_USING_DMA
#ifndef SPI1_TX_DMA_CONFIG
#define SPI1_TX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI1_TX_DMA_PERIPH,               \
        .rcu = SPI1_TX_DMA_RCU,                     \
        .channel = SPI1_TX_DMA_CHANNEL,              \
        .subperiph = SPI1_TX_DMA_SUBPERI,            \
        .irq = SPI1_TX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI1_TX_DMA_CONFIG */
#ifndef SPI1_RX_DMA_CONFIG
#define SPI1_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI1_RX_DMA_PERIPH,               \
        .rcu = SPI1_RX_DMA_RCU,                     \
        .channel = SPI1_RX_DMA_CHANNEL,              \
        .subperiph = SPI1_RX_DMA_SUBPERI,            \
        .irq = SPI1_RX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI1_RX_DMA_CONFIG */
#endif /* BSP_SPI1_USING_DMA */

/* SPI2 DMA configuration */
#ifdef BSP_SPI2_USING_DMA
#ifndef SPI2_TX_DMA_CONFIG
#define SPI2_TX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI2_TX_DMA_PERIPH,               \
        .rcu = SPI2_TX_DMA_RCU,                     \
        .channel = SPI2_TX_DMA_CHANNEL,              \
        .subperiph = SPI2_TX_DMA_SUBPERI,            \
        .irq = SPI2_TX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI2_TX_DMA_CONFIG */
#ifndef SPI2_RX_DMA_CONFIG
#define SPI2_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI2_RX_DMA_PERIPH,               \
        .rcu = SPI2_RX_DMA_RCU,                     \
        .channel = SPI2_RX_DMA_CHANNEL,              \
        .subperiph = SPI2_RX_DMA_SUBPERI,            \
        .irq = SPI2_RX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI2_RX_DMA_CONFIG */
#endif /* BSP_SPI2_USING_DMA */

/* SPI3 DMA configuration */
#ifdef BSP_SPI3_USING_DMA
#ifndef SPI3_TX_DMA_CONFIG
#define SPI3_TX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI3_TX_DMA_PERIPH,               \
        .rcu = SPI3_TX_DMA_RCU,                     \
        .channel = SPI3_TX_DMA_CHANNEL,              \
        .subperiph = SPI3_TX_DMA_SUBPERI,            \
        .irq = SPI3_TX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI3_TX_DMA_CONFIG */
#ifndef SPI3_RX_DMA_CONFIG
#define SPI3_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI3_RX_DMA_PERIPH,               \
        .rcu = SPI3_RX_DMA_RCU,                     \
        .channel = SPI3_RX_DMA_CHANNEL,              \
        .subperiph = SPI3_RX_DMA_SUBPERI,            \
        .irq = SPI3_RX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI3_RX_DMA_CONFIG */
#endif /* BSP_SPI3_USING_DMA */

/* SPI4 DMA configuration */
#ifdef BSP_SPI4_USING_DMA
#ifndef SPI4_TX_DMA_CONFIG
#define SPI4_TX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI4_TX_DMA_PERIPH,               \
        .rcu = SPI4_TX_DMA_RCU,                     \
        .channel = SPI4_TX_DMA_CHANNEL,              \
        .subperiph = SPI4_TX_DMA_SUBPERI,            \
        .irq = SPI4_TX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI4_TX_DMA_CONFIG */
#ifndef SPI4_RX_DMA_CONFIG
#define SPI4_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI4_RX_DMA_PERIPH,               \
        .rcu = SPI4_RX_DMA_RCU,                     \
        .channel = SPI4_RX_DMA_CHANNEL,              \
        .subperiph = SPI4_RX_DMA_SUBPERI,            \
        .irq = SPI4_RX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI4_RX_DMA_CONFIG */
#endif /* BSP_SPI4_USING_DMA */

/* SPI5 DMA configuration */
#ifdef BSP_SPI5_USING_DMA
#ifndef SPI5_TX_DMA_CONFIG
#define SPI5_TX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI5_TX_DMA_PERIPH,               \
        .rcu = SPI5_TX_DMA_RCU,                     \
        .channel = SPI5_TX_DMA_CHANNEL,              \
        .subperiph = SPI5_TX_DMA_SUBPERI,            \
        .irq = SPI5_TX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI5_TX_DMA_CONFIG */
#ifndef SPI5_RX_DMA_CONFIG
#define SPI5_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI5_RX_DMA_PERIPH,               \
        .rcu = SPI5_RX_DMA_RCU,                     \
        .channel = SPI5_RX_DMA_CHANNEL,              \
        .subperiph = SPI5_RX_DMA_SUBPERI,            \
        .irq = SPI5_RX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* SPI5_RX_DMA_CONFIG */
#endif /* BSP_SPI5_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_CONFIG_H__ */
