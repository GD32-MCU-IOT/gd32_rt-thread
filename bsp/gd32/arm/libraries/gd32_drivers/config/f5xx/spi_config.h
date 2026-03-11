/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-03-10     RT-Thread    first implementation for GD32F5xx
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SPI0 bus configuration */
#ifdef BSP_USING_SPI0
#ifndef SPI0_BUS_CONFIG
#define SPI0_BUS_CONFIG                             \
    {                                               \
        .spi_periph = SPI0,                         \
        .spi_clk = RCU_SPI0,                        \
        .irqn = SPI0_IRQn,                          \
        .bus_name = "spi0",                         \
    }
#endif /* SPI0_BUS_CONFIG */
#endif /* BSP_USING_SPI0 */

#ifdef BSP_SPI0_TX_USING_DMA
#ifndef SPI0_TX_DMA_CONFIG
#define SPI0_TX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI0_TX_DMA_INSTANCE,             \
        .rcu = SPI0_TX_DMA_RCC,                     \
        .channel = SPI0_TX_DMA_CHANNEL,             \
        .subperiph = SPI0_TX_DMA_SUBPERI,           \
        .irq = SPI0_TX_DMA_IRQ,                     \
    }
#endif /* SPI0_TX_DMA_CONFIG */
#endif /* BSP_SPI0_TX_USING_DMA */

#ifdef BSP_SPI0_RX_USING_DMA
#ifndef SPI0_RX_DMA_CONFIG
#define SPI0_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI0_RX_DMA_INSTANCE,             \
        .rcu = SPI0_RX_DMA_RCC,                     \
        .channel = SPI0_RX_DMA_CHANNEL,             \
        .subperiph = SPI0_RX_DMA_SUBPERI,           \
        .irq = SPI0_RX_DMA_IRQ,                     \
    }
#endif /* SPI0_RX_DMA_CONFIG */
#endif /* BSP_SPI0_RX_USING_DMA */

/* SPI1 bus configuration */
#ifdef BSP_USING_SPI1
#ifndef SPI1_BUS_CONFIG
#define SPI1_BUS_CONFIG                             \
    {                                               \
        .spi_periph = SPI1,                         \
        .spi_clk = RCU_SPI1,                        \
        .irqn = SPI1_IRQn,                          \
        .bus_name = "spi1",                         \
    }
#endif /* SPI1_BUS_CONFIG */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_SPI1_TX_USING_DMA
#ifndef SPI1_TX_DMA_CONFIG
#define SPI1_TX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI1_TX_DMA_INSTANCE,             \
        .rcu = SPI1_TX_DMA_RCC,                     \
        .channel = SPI1_TX_DMA_CHANNEL,             \
        .subperiph = SPI1_TX_DMA_SUBPERI,           \
        .irq = SPI1_TX_DMA_IRQ,                     \
    }
#endif /* SPI1_TX_DMA_CONFIG */
#endif /* BSP_SPI1_TX_USING_DMA */

#ifdef BSP_SPI1_RX_USING_DMA
#ifndef SPI1_RX_DMA_CONFIG
#define SPI1_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI1_RX_DMA_INSTANCE,             \
        .rcu = SPI1_RX_DMA_RCC,                     \
        .channel = SPI1_RX_DMA_CHANNEL,             \
        .subperiph = SPI1_RX_DMA_SUBPERI,           \
        .irq = SPI1_RX_DMA_IRQ,                     \
    }
#endif /* SPI1_RX_DMA_CONFIG */
#endif /* BSP_SPI1_RX_USING_DMA */

/* SPI2 bus configuration */
#ifdef BSP_USING_SPI2
#ifndef SPI2_BUS_CONFIG
#define SPI2_BUS_CONFIG                             \
    {                                               \
        .spi_periph = SPI2,                         \
        .spi_clk = RCU_SPI2,                        \
        .irqn = SPI2_IRQn,                          \
        .bus_name = "spi2",                         \
    }
#endif /* SPI2_BUS_CONFIG */
#endif /* BSP_USING_SPI2 */

#ifdef BSP_SPI2_TX_USING_DMA
#ifndef SPI2_TX_DMA_CONFIG
#define SPI2_TX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI2_TX_DMA_INSTANCE,             \
        .rcu = SPI2_TX_DMA_RCC,                     \
        .channel = SPI2_TX_DMA_CHANNEL,             \
        .subperiph = SPI2_TX_DMA_SUBPERI,           \
        .irq = SPI2_TX_DMA_IRQ,                     \
    }
#endif /* SPI2_TX_DMA_CONFIG */
#endif /* BSP_SPI2_TX_USING_DMA */

#ifdef BSP_SPI2_RX_USING_DMA
#ifndef SPI2_RX_DMA_CONFIG
#define SPI2_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI2_RX_DMA_INSTANCE,             \
        .rcu = SPI2_RX_DMA_RCC,                     \
        .channel = SPI2_RX_DMA_CHANNEL,             \
        .subperiph = SPI2_RX_DMA_SUBPERI,           \
        .irq = SPI2_RX_DMA_IRQ,                     \
    }
#endif /* SPI2_RX_DMA_CONFIG */
#endif /* BSP_SPI2_RX_USING_DMA */

/* SPI3 bus configuration */
#ifdef BSP_USING_SPI3
#ifndef SPI3_BUS_CONFIG
#define SPI3_BUS_CONFIG                             \
    {                                               \
        .spi_periph = SPI3,                         \
        .spi_clk = RCU_SPI3,                        \
        .irqn = SPI3_IRQn,                          \
        .bus_name = "spi3",                         \
    }
#endif /* SPI3_BUS_CONFIG */
#endif /* BSP_USING_SPI3 */

#ifdef BSP_SPI3_TX_USING_DMA
#ifndef SPI3_TX_DMA_CONFIG
#define SPI3_TX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI3_TX_DMA_INSTANCE,             \
        .rcu = SPI3_TX_DMA_RCC,                     \
        .channel = SPI3_TX_DMA_CHANNEL,             \
        .subperiph = SPI3_TX_DMA_SUBPERI,           \
        .irq = SPI3_TX_DMA_IRQ,                     \
    }
#endif /* SPI3_TX_DMA_CONFIG */
#endif /* BSP_SPI3_TX_USING_DMA */

#ifdef BSP_SPI3_RX_USING_DMA
#ifndef SPI3_RX_DMA_CONFIG
#define SPI3_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI3_RX_DMA_INSTANCE,             \
        .rcu = SPI3_RX_DMA_RCC,                     \
        .channel = SPI3_RX_DMA_CHANNEL,             \
        .subperiph = SPI3_RX_DMA_SUBPERI,           \
        .irq = SPI3_RX_DMA_IRQ,                     \
    }
#endif /* SPI3_RX_DMA_CONFIG */
#endif /* BSP_SPI3_RX_USING_DMA */

/* SPI4 bus configuration */
#ifdef BSP_USING_SPI4
#ifndef SPI4_BUS_CONFIG
#define SPI4_BUS_CONFIG                             \
    {                                               \
        .spi_periph = SPI4,                         \
        .spi_clk = RCU_SPI4,                        \
        .irqn = SPI4_IRQn,                          \
        .bus_name = "spi4",                         \
    }
#endif /* SPI4_BUS_CONFIG */
#endif /* BSP_USING_SPI4 */

#ifdef BSP_SPI4_TX_USING_DMA
#ifndef SPI4_TX_DMA_CONFIG
#define SPI4_TX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI4_TX_DMA_INSTANCE,             \
        .rcu = SPI4_TX_DMA_RCC,                     \
        .channel = SPI4_TX_DMA_CHANNEL,             \
        .subperiph = SPI4_TX_DMA_SUBPERI,           \
        .irq = SPI4_TX_DMA_IRQ,                     \
    }
#endif /* SPI4_TX_DMA_CONFIG */
#endif /* BSP_SPI4_TX_USING_DMA */

#ifdef BSP_SPI4_RX_USING_DMA
#ifndef SPI4_RX_DMA_CONFIG
#define SPI4_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI4_RX_DMA_INSTANCE,             \
        .rcu = SPI4_RX_DMA_RCC,                     \
        .channel = SPI4_RX_DMA_CHANNEL,             \
        .subperiph = SPI4_RX_DMA_SUBPERI,           \
        .irq = SPI4_RX_DMA_IRQ,                     \
    }
#endif /* SPI4_RX_DMA_CONFIG */
#endif /* BSP_SPI4_RX_USING_DMA */

/* SPI5 bus configuration */
#ifdef BSP_USING_SPI5
#ifndef SPI5_BUS_CONFIG
#define SPI5_BUS_CONFIG                             \
    {                                               \
        .spi_periph = SPI5,                         \
        .spi_clk = RCU_SPI5,                        \
        .irqn = SPI5_IRQn,                          \
        .bus_name = "spi5",                         \
    }
#endif /* SPI5_BUS_CONFIG */
#endif /* BSP_USING_SPI5 */

#ifdef BSP_SPI5_TX_USING_DMA
#ifndef SPI5_TX_DMA_CONFIG
#define SPI5_TX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI5_TX_DMA_INSTANCE,             \
        .rcu = SPI5_TX_DMA_RCC,                     \
        .channel = SPI5_TX_DMA_CHANNEL,             \
        .subperiph = SPI5_TX_DMA_SUBPERI,           \
        .irq = SPI5_TX_DMA_IRQ,                     \
    }
#endif /* SPI5_TX_DMA_CONFIG */
#endif /* BSP_SPI5_TX_USING_DMA */

#ifdef BSP_SPI5_RX_USING_DMA
#ifndef SPI5_RX_DMA_CONFIG
#define SPI5_RX_DMA_CONFIG                          \
    {                                               \
        .periph = SPI5_RX_DMA_INSTANCE,             \
        .rcu = SPI5_RX_DMA_RCC,                     \
        .channel = SPI5_RX_DMA_CHANNEL,             \
        .subperiph = SPI5_RX_DMA_SUBPERI,           \
        .irq = SPI5_RX_DMA_IRQ,                     \
    }
#endif /* SPI5_RX_DMA_CONFIG */
#endif /* BSP_SPI5_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_CONFIG_H__ */
