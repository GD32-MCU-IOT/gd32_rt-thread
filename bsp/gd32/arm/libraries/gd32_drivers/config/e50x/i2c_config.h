/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-12     RT-Thread    first implementation for GD32E50x
 */

#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Declare DMA support for GD32E50x hardware I2C driver */
#define GD32_I2C_DMA_SUPPORTED

/* GD32E50x I2C DMA config — no subperiph field (fixed-wired channels)
 *
 * I2C0 TX: DMA0 CH5
 * I2C0 RX: DMA0 CH6
 * I2C1 TX: DMA0 CH3  (conflicts with SPI1_RX — choose only one)
 * I2C1 RX: DMA0 CH4  (conflicts with SPI1_TX — choose only one)
 * I2C2 TX: DMA0 CH3  (conflicts with SPI1_RX / I2C1_TX)
 * I2C2 RX: DMA0 CH4  (conflicts with SPI1_TX / I2C1_RX)
 */

/* I2C0 TX: DMA0 CH5 */
#if defined(BSP_I2C0_TX_USING_DMA)
#ifndef I2C0_TX_DMA_CONFIG
#define I2C0_TX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = I2C0_TX_DMA_PERIPH,                           \
        .rcu        = I2C0_TX_DMA_RCU,                               \
        .channel    = I2C0_TX_DMA_CHANNEL,                           \
        .irq        = I2C0_TX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* I2C0 RX: DMA0 CH6 */
#if defined(BSP_I2C0_RX_USING_DMA)
#ifndef I2C0_RX_DMA_CONFIG
#define I2C0_RX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = I2C0_RX_DMA_PERIPH,                           \
        .rcu        = I2C0_RX_DMA_RCU,                               \
        .channel    = I2C0_RX_DMA_CHANNEL,                           \
        .irq        = I2C0_RX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* I2C1 TX: DMA0 CH3 */
#if defined(BSP_I2C1_TX_USING_DMA)
#ifndef I2C1_TX_DMA_CONFIG
#define I2C1_TX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = I2C1_TX_DMA_PERIPH,                           \
        .rcu        = I2C1_TX_DMA_RCU,                               \
        .channel    = I2C1_TX_DMA_CHANNEL,                           \
        .irq        = I2C1_TX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* I2C1 RX: DMA0 CH4 */
#if defined(BSP_I2C1_RX_USING_DMA)
#ifndef I2C1_RX_DMA_CONFIG
#define I2C1_RX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = I2C1_RX_DMA_PERIPH,                           \
        .rcu        = I2C1_RX_DMA_RCU,                               \
        .channel    = I2C1_RX_DMA_CHANNEL,                           \
        .irq        = I2C1_RX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* I2C2 TX: DMA0 CH3 */
#if defined(BSP_I2C2_TX_USING_DMA)
#ifndef I2C2_TX_DMA_CONFIG
#define I2C2_TX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = I2C2_TX_DMA_PERIPH,                           \
        .rcu        = I2C2_TX_DMA_RCU,                               \
        .channel    = I2C2_TX_DMA_CHANNEL,                           \
        .irq        = I2C2_TX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* I2C2 RX: DMA0 CH4 */
#if defined(BSP_I2C2_RX_USING_DMA)
#ifndef I2C2_RX_DMA_CONFIG
#define I2C2_RX_DMA_CONFIG                                          \
    {                                                               \
        .periph     = I2C2_RX_DMA_PERIPH,                           \
        .rcu        = I2C2_RX_DMA_RCU,                               \
        .channel    = I2C2_RX_DMA_CHANNEL,                           \
        .irq        = I2C2_RX_DMA_IRQ,                               \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __I2C_CONFIG_H__ */
