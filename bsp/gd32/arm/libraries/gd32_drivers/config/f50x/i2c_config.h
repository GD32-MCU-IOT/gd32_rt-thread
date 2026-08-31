/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-16     RT-Thread    first implementation for GD32F50x I2C DMA
 */

#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

#include <rtthread.h>
#include "drv_dma.h"
#include "dma_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* This configuration set provides the I2C DMA helper implementation for F50x.
 * F50x uses DMAMUX with 'request' field (like H7xx), so the struct dma_config
 * carries .request and these initializers mirror the H7xx layout. */
#define GD32_I2C_DMA_SUPPORTED

/* I2C0 DMA configuration */
#ifdef BSP_I2C0_TX_USING_DMA
#ifndef I2C0_TX_DMA_CONFIG
#define I2C0_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C0_TX_DMA_PERIPH,               \
        .rcu = I2C0_TX_DMA_RCU,                     \
        .channel = I2C0_TX_DMA_CHANNEL,             \
        .request = I2C0_TX_DMA_REQUEST,             \
        .irq = I2C0_TX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,        \
    }
#endif /* I2C0_TX_DMA_CONFIG */
#endif /* BSP_I2C0_TX_USING_DMA */

#ifdef BSP_I2C0_RX_USING_DMA
#ifndef I2C0_RX_DMA_CONFIG
#define I2C0_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C0_RX_DMA_PERIPH,               \
        .rcu = I2C0_RX_DMA_RCU,                     \
        .channel = I2C0_RX_DMA_CHANNEL,             \
        .request = I2C0_RX_DMA_REQUEST,             \
        .irq = I2C0_RX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,        \
    }
#endif /* I2C0_RX_DMA_CONFIG */
#endif /* BSP_I2C0_RX_USING_DMA */

/* I2C1 DMA configuration */
#ifdef BSP_I2C1_TX_USING_DMA
#ifndef I2C1_TX_DMA_CONFIG
#define I2C1_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C1_TX_DMA_PERIPH,               \
        .rcu = I2C1_TX_DMA_RCU,                     \
        .channel = I2C1_TX_DMA_CHANNEL,             \
        .request = I2C1_TX_DMA_REQUEST,             \
        .irq = I2C1_TX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,        \
    }
#endif /* I2C1_TX_DMA_CONFIG */
#endif /* BSP_I2C1_TX_USING_DMA */

#ifdef BSP_I2C1_RX_USING_DMA
#ifndef I2C1_RX_DMA_CONFIG
#define I2C1_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C1_RX_DMA_PERIPH,               \
        .rcu = I2C1_RX_DMA_RCU,                     \
        .channel = I2C1_RX_DMA_CHANNEL,             \
        .request = I2C1_RX_DMA_REQUEST,             \
        .irq = I2C1_RX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,        \
    }
#endif /* I2C1_RX_DMA_CONFIG */
#endif /* BSP_I2C1_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_CONFIG_H__ */
