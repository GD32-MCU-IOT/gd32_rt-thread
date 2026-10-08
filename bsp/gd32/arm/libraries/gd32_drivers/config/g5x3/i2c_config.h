/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-30     RT-Thread    first implementation for GD32G5x3
 */

#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* I2C0 DMA configuration (DMA0 channels 6-7, DMAMUX 32-33) */
#ifdef BSP_I2C0_RX_USING_DMA
#ifndef I2C0_RX_DMA_CONFIG
#define I2C0_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C0_RX_DMA_PERIPH,               \
        .rcu = I2C0_RX_DMA_RCU,                     \
        .channel = I2C0_RX_DMA_CHANNEL,              \
        .request = I2C0_RX_DMA_REQUEST,    \
        .irq = I2C0_RX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* I2C0_RX_DMA_CONFIG */
#endif /* BSP_I2C0_RX_USING_DMA */

#ifdef BSP_I2C0_TX_USING_DMA
#ifndef I2C0_TX_DMA_CONFIG
#define I2C0_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C0_TX_DMA_PERIPH,               \
        .rcu = I2C0_TX_DMA_RCU,                     \
        .channel = I2C0_TX_DMA_CHANNEL,              \
        .request = I2C0_TX_DMA_REQUEST,    \
        .irq = I2C0_TX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* I2C0_TX_DMA_CONFIG */
#endif /* BSP_I2C0_TX_USING_DMA */

/* I2C1 DMA configuration (DMA1 channels 2-3, DMAMUX 34-35) */
#ifdef BSP_I2C1_RX_USING_DMA
#ifndef I2C1_RX_DMA_CONFIG
#define I2C1_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C1_RX_DMA_PERIPH,               \
        .rcu = I2C1_RX_DMA_RCU,                     \
        .channel = I2C1_RX_DMA_CHANNEL,              \
        .request = I2C1_RX_DMA_REQUEST,    \
        .irq = I2C1_RX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* I2C1_RX_DMA_CONFIG */
#endif /* BSP_I2C1_RX_USING_DMA */

#ifdef BSP_I2C1_TX_USING_DMA
#ifndef I2C1_TX_DMA_CONFIG
#define I2C1_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C1_TX_DMA_PERIPH,               \
        .rcu = I2C1_TX_DMA_RCU,                     \
        .channel = I2C1_TX_DMA_CHANNEL,              \
        .request = I2C1_TX_DMA_REQUEST,    \
        .irq = I2C1_TX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* I2C1_TX_DMA_CONFIG */
#endif /* BSP_I2C1_TX_USING_DMA */

/* I2C2 DMA configuration (DMA1 channels 4-5, DMAMUX 36-37) */
#ifdef BSP_I2C2_RX_USING_DMA
#ifndef I2C2_RX_DMA_CONFIG
#define I2C2_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C2_RX_DMA_PERIPH,               \
        .rcu = I2C2_RX_DMA_RCU,                     \
        .channel = I2C2_RX_DMA_CHANNEL,              \
        .request = I2C2_RX_DMA_REQUEST,    \
        .irq = I2C2_RX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* I2C2_RX_DMA_CONFIG */
#endif /* BSP_I2C2_RX_USING_DMA */

#ifdef BSP_I2C2_TX_USING_DMA
#ifndef I2C2_TX_DMA_CONFIG
#define I2C2_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C2_TX_DMA_PERIPH,               \
        .rcu = I2C2_TX_DMA_RCU,                     \
        .channel = I2C2_TX_DMA_CHANNEL,              \
        .request = I2C2_TX_DMA_REQUEST,    \
        .irq = I2C2_TX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* I2C2_TX_DMA_CONFIG */
#endif /* BSP_I2C2_TX_USING_DMA */

/* I2C3 DMA configuration (DMA1 channels 6-7, DMAMUX 38-39) */
#ifdef BSP_I2C3_RX_USING_DMA
#ifndef I2C3_RX_DMA_CONFIG
#define I2C3_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C3_RX_DMA_PERIPH,               \
        .rcu = I2C3_RX_DMA_RCU,                     \
        .channel = I2C3_RX_DMA_CHANNEL,              \
        .request = I2C3_RX_DMA_REQUEST,    \
        .irq = I2C3_RX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* I2C3_RX_DMA_CONFIG */
#endif /* BSP_I2C3_RX_USING_DMA */

#ifdef BSP_I2C3_TX_USING_DMA
#ifndef I2C3_TX_DMA_CONFIG
#define I2C3_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C3_TX_DMA_PERIPH,               \
        .rcu = I2C3_TX_DMA_RCU,                     \
        .channel = I2C3_TX_DMA_CHANNEL,              \
        .request = I2C3_TX_DMA_REQUEST,    \
        .irq = I2C3_TX_DMA_IRQ,                      \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* I2C3_TX_DMA_CONFIG */
#endif /* BSP_I2C3_TX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_CONFIG_H__ */
