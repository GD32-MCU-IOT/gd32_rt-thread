/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-03-17     RT-Thread    first implementation for GD32F5xx I2C DMA
 */

#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

#include <rtthread.h>
#include "drv_dma.h"
#include "dma_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* I2C DMA transfer threshold (bytes), only use DMA when length >= this value */
/* Keep 1-byte transfers on polling path to avoid DMA overhead and aid diagnostics. */
#define I2C_DMA_TRANS_MIN_LEN   2

/* I2C DMA timeout in milliseconds */
#define I2C_DMA_TIMEOUT_MS      1000

/* I2C0 DMA configuration */
#ifdef BSP_I2C0_TX_USING_DMA
#ifndef I2C0_TX_DMA_CONFIG
#define I2C0_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C0_TX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C0_TX_DMA_RCC,                     \
        .channel = I2C0_TX_DMA_CHANNEL,             \
        .subperiph = I2C0_TX_DMA_SUBPERI,           \
        .irq = I2C0_TX_DMA_IRQ,                     \
    }
#endif /* I2C0_TX_DMA_CONFIG */
#endif /* BSP_I2C0_TX_USING_DMA */

#ifdef BSP_I2C0_RX_USING_DMA
#ifndef I2C0_RX_DMA_CONFIG
#define I2C0_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C0_RX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C0_RX_DMA_RCC,                     \
        .channel = I2C0_RX_DMA_CHANNEL,             \
        .subperiph = I2C0_RX_DMA_SUBPERI,           \
        .irq = I2C0_RX_DMA_IRQ,                     \
    }
#endif /* I2C0_RX_DMA_CONFIG */
#endif /* BSP_I2C0_RX_USING_DMA */

/* I2C1 DMA configuration */
#ifdef BSP_I2C1_TX_USING_DMA
#ifndef I2C1_TX_DMA_CONFIG
#define I2C1_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C1_TX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C1_TX_DMA_RCC,                     \
        .channel = I2C1_TX_DMA_CHANNEL,             \
        .subperiph = I2C1_TX_DMA_SUBPERI,           \
        .irq = I2C1_TX_DMA_IRQ,                     \
    }
#endif /* I2C1_TX_DMA_CONFIG */
#endif /* BSP_I2C1_TX_USING_DMA */

#ifdef BSP_I2C1_RX_USING_DMA
#ifndef I2C1_RX_DMA_CONFIG
#define I2C1_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C1_RX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C1_RX_DMA_RCC,                     \
        .channel = I2C1_RX_DMA_CHANNEL,             \
        .subperiph = I2C1_RX_DMA_SUBPERI,           \
        .irq = I2C1_RX_DMA_IRQ,                     \
    }
#endif /* I2C1_RX_DMA_CONFIG */
#endif /* BSP_I2C1_RX_USING_DMA */

/* I2C2 DMA configuration */
#ifdef BSP_I2C2_TX_USING_DMA
#ifndef I2C2_TX_DMA_CONFIG
#define I2C2_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C2_TX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C2_TX_DMA_RCC,                     \
        .channel = I2C2_TX_DMA_CHANNEL,             \
        .subperiph = I2C2_TX_DMA_SUBPERI,           \
        .irq = I2C2_TX_DMA_IRQ,                     \
    }
#endif /* I2C2_TX_DMA_CONFIG */
#endif /* BSP_I2C2_TX_USING_DMA */

#ifdef BSP_I2C2_RX_USING_DMA
#ifndef I2C2_RX_DMA_CONFIG
#define I2C2_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C2_RX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C2_RX_DMA_RCC,                     \
        .channel = I2C2_RX_DMA_CHANNEL,             \
        .subperiph = I2C2_RX_DMA_SUBPERI,           \
        .irq = I2C2_RX_DMA_IRQ,                     \
    }
#endif /* I2C2_RX_DMA_CONFIG */
#endif /* BSP_I2C2_RX_USING_DMA */

/* I2C3 DMA configuration (New I2C - supports both TX and RX DMA) */
#ifdef BSP_I2C3_TX_USING_DMA
#ifndef I2C3_TX_DMA_CONFIG
#define I2C3_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C3_TX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C3_TX_DMA_RCC,                     \
        .channel = I2C3_TX_DMA_CHANNEL,             \
        .subperiph = I2C3_TX_DMA_SUBPERI,           \
        .irq = I2C3_TX_DMA_IRQ,                     \
    }
#endif /* I2C3_TX_DMA_CONFIG */
#endif /* BSP_I2C3_TX_USING_DMA */

#ifdef BSP_I2C3_RX_USING_DMA
#ifndef I2C3_RX_DMA_CONFIG
#define I2C3_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C3_RX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C3_RX_DMA_RCC,                     \
        .channel = I2C3_RX_DMA_CHANNEL,             \
        .subperiph = I2C3_RX_DMA_SUBPERI,           \
        .irq = I2C3_RX_DMA_IRQ,                     \
    }
#endif /* I2C3_RX_DMA_CONFIG */
#endif /* BSP_I2C3_RX_USING_DMA */

/* I2C4 DMA configuration (New I2C - supports both TX and RX DMA) */
#ifdef BSP_I2C4_TX_USING_DMA
#ifndef I2C4_TX_DMA_CONFIG
#define I2C4_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C4_TX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C4_TX_DMA_RCC,                     \
        .channel = I2C4_TX_DMA_CHANNEL,             \
        .subperiph = I2C4_TX_DMA_SUBPERI,           \
        .irq = I2C4_TX_DMA_IRQ,                     \
    }
#endif /* I2C4_TX_DMA_CONFIG */
#endif /* BSP_I2C4_TX_USING_DMA */

#ifdef BSP_I2C4_RX_USING_DMA
#ifndef I2C4_RX_DMA_CONFIG
#define I2C4_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C4_RX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C4_RX_DMA_RCC,                     \
        .channel = I2C4_RX_DMA_CHANNEL,             \
        .subperiph = I2C4_RX_DMA_SUBPERI,           \
        .irq = I2C4_RX_DMA_IRQ,                     \
    }
#endif /* I2C4_RX_DMA_CONFIG */
#endif /* BSP_I2C4_RX_USING_DMA */

/* I2C5 DMA configuration (New I2C - supports both TX and RX DMA) */
#ifdef BSP_I2C5_TX_USING_DMA
#ifndef I2C5_TX_DMA_CONFIG
#define I2C5_TX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C5_TX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C5_TX_DMA_RCC,                     \
        .channel = I2C5_TX_DMA_CHANNEL,             \
        .subperiph = I2C5_TX_DMA_SUBPERI,           \
        .irq = I2C5_TX_DMA_IRQ,                     \
    }
#endif /* I2C5_TX_DMA_CONFIG */
#endif /* BSP_I2C5_TX_USING_DMA */

#ifdef BSP_I2C5_RX_USING_DMA
#ifndef I2C5_RX_DMA_CONFIG
#define I2C5_RX_DMA_CONFIG                          \
    {                                               \
        .periph = I2C5_RX_DMA_INSTANCE,             \
        .dma_flag = 0,                              \
        .rcu = I2C5_RX_DMA_RCC,                     \
        .channel = I2C5_RX_DMA_CHANNEL,             \
        .subperiph = I2C5_RX_DMA_SUBPERI,           \
        .irq = I2C5_RX_DMA_IRQ,                     \
    }
#endif /* I2C5_RX_DMA_CONFIG */
#endif /* BSP_I2C5_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_CONFIG_H__ */
