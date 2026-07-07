/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-12     RT-Thread    first implementation for GD32E51x
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GD32E51x UART DMA config — no subperiph field (fixed-wired channels) */

/* UART0 RX: DMA0 CH4 */
#if defined(BSP_UART0_RX_USING_DMA)
#ifndef UART0_DMA_RX_CONFIG
#define UART0_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART0_RX_DMA_PERIPH,                          \
        .rcu        = UART0_RX_DMA_RCU,                              \
        .channel    = UART0_RX_DMA_CHANNEL,                          \
        .irq        = UART0_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* UART0 TX: DMA0 CH3 */
#if defined(BSP_UART0_TX_USING_DMA)
#ifndef UART0_DMA_TX_CONFIG
#define UART0_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART0_TX_DMA_PERIPH,                          \
        .rcu        = UART0_TX_DMA_RCU,                              \
        .channel    = UART0_TX_DMA_CHANNEL,                          \
        .irq        = UART0_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* UART1 RX: DMA0 CH5 */
#if defined(BSP_UART1_RX_USING_DMA)
#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART1_RX_DMA_PERIPH,                          \
        .rcu        = UART1_RX_DMA_RCU,                              \
        .channel    = UART1_RX_DMA_CHANNEL,                          \
        .irq        = UART1_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* UART1 TX: DMA0 CH6 */
#if defined(BSP_UART1_TX_USING_DMA)
#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART1_TX_DMA_PERIPH,                          \
        .rcu        = UART1_TX_DMA_RCU,                              \
        .channel    = UART1_TX_DMA_CHANNEL,                          \
        .irq        = UART1_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* UART2 TX: DMA0 CH1 */
#if defined(BSP_UART2_TX_USING_DMA)
#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART2_TX_DMA_PERIPH,                          \
        .rcu        = UART2_TX_DMA_RCU,                              \
        .channel    = UART2_TX_DMA_CHANNEL,                          \
        .irq        = UART2_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* UART2 RX: DMA0 CH2 */
#if defined(BSP_UART2_RX_USING_DMA)
#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART2_RX_DMA_PERIPH,                          \
        .rcu        = UART2_RX_DMA_RCU,                              \
        .channel    = UART2_RX_DMA_CHANNEL,                          \
        .irq        = UART2_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* UART3 RX: DMA1 CH2 */
#if defined(BSP_UART3_RX_USING_DMA)
#ifndef UART3_DMA_RX_CONFIG
#define UART3_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART3_RX_DMA_PERIPH,                          \
        .rcu        = UART3_RX_DMA_RCU,                              \
        .channel    = UART3_RX_DMA_CHANNEL,                          \
        .irq        = UART3_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* UART3 TX: DMA1 CH4 */
#if defined(BSP_UART3_TX_USING_DMA)
#ifndef UART3_DMA_TX_CONFIG
#define UART3_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART3_TX_DMA_PERIPH,                          \
        .rcu        = UART3_TX_DMA_RCU,                              \
        .channel    = UART3_TX_DMA_CHANNEL,                          \
        .irq        = UART3_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* UART5 RX: DMA1 CH2 */
#if defined(BSP_UART5_RX_USING_DMA)
#ifndef UART5_DMA_RX_CONFIG
#define UART5_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART5_RX_DMA_PERIPH,                          \
        .rcu        = UART5_RX_DMA_RCU,                              \
        .channel    = UART5_RX_DMA_CHANNEL,                          \
        .irq        = UART5_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

/* UART5 TX: DMA1 CH4 */
#if defined(BSP_UART5_TX_USING_DMA)
#ifndef UART5_DMA_TX_CONFIG
#define UART5_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART5_TX_DMA_PERIPH,                          \
        .rcu        = UART5_TX_DMA_RCU,                              \
        .channel    = UART5_TX_DMA_CHANNEL,                          \
        .irq        = UART5_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPHERAL_WIDTH_8BIT,                     \
    }
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */
