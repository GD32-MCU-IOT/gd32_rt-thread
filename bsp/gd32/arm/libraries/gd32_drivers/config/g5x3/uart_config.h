/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-30     RT-Thread    first implementation for GD32G5x3
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* UART0 (USART0) DMA configuration */
#ifdef BSP_UART0_RX_USING_DMA
#ifndef UART0_DMA_RX_CONFIG
#define UART0_DMA_RX_CONFIG                         \
    {                                               \
        .periph = UART0_RX_DMA_PERIPH,              \
        .rcu = UART0_RX_DMA_RCU,                    \
        .channel = UART0_RX_DMA_CHANNEL,             \
        .request = UART0_RX_DMA_REQUEST,            \
        .irq = UART0_RX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* UART0_DMA_RX_CONFIG */
#endif /* BSP_UART0_RX_USING_DMA */

#ifdef BSP_UART0_TX_USING_DMA
#ifndef UART0_DMA_TX_CONFIG
#define UART0_DMA_TX_CONFIG                         \
    {                                               \
        .periph = UART0_TX_DMA_PERIPH,              \
        .rcu = UART0_TX_DMA_RCU,                    \
        .channel = UART0_TX_DMA_CHANNEL,             \
        .request = UART0_TX_DMA_REQUEST,            \
        .irq = UART0_TX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* UART0_DMA_TX_CONFIG */
#endif /* BSP_UART0_TX_USING_DMA */

/* UART1 (USART1) DMA configuration */
#ifdef BSP_UART1_RX_USING_DMA
#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG                         \
    {                                               \
        .periph = UART1_RX_DMA_PERIPH,              \
        .rcu = UART1_RX_DMA_RCU,                    \
        .channel = UART1_RX_DMA_CHANNEL,             \
        .request = UART1_RX_DMA_REQUEST,            \
        .irq = UART1_RX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* UART1_DMA_RX_CONFIG */
#endif /* BSP_UART1_RX_USING_DMA */

#ifdef BSP_UART1_TX_USING_DMA
#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG                         \
    {                                               \
        .periph = UART1_TX_DMA_PERIPH,              \
        .rcu = UART1_TX_DMA_RCU,                    \
        .channel = UART1_TX_DMA_CHANNEL,             \
        .request = UART1_TX_DMA_REQUEST,            \
        .irq = UART1_TX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* UART1_DMA_TX_CONFIG */
#endif /* BSP_UART1_TX_USING_DMA */

/* UART2 (USART2) DMA configuration */
#ifdef BSP_UART2_RX_USING_DMA
#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG                         \
    {                                               \
        .periph = UART2_RX_DMA_PERIPH,              \
        .rcu = UART2_RX_DMA_RCU,                    \
        .channel = UART2_RX_DMA_CHANNEL,             \
        .request = UART2_RX_DMA_REQUEST,            \
        .irq = UART2_RX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* UART2_DMA_RX_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#ifdef BSP_UART2_TX_USING_DMA
#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG                         \
    {                                               \
        .periph = UART2_TX_DMA_PERIPH,              \
        .rcu = UART2_TX_DMA_RCU,                    \
        .channel = UART2_TX_DMA_CHANNEL,             \
        .request = UART2_TX_DMA_REQUEST,            \
        .irq = UART2_TX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* UART2_DMA_TX_CONFIG */
#endif /* BSP_UART2_TX_USING_DMA */

/* UART3 DMA configuration */
#ifdef BSP_UART3_RX_USING_DMA
#ifndef UART3_DMA_RX_CONFIG
#define UART3_DMA_RX_CONFIG                         \
    {                                               \
        .periph = UART3_RX_DMA_PERIPH,              \
        .rcu = UART3_RX_DMA_RCU,                    \
        .channel = UART3_RX_DMA_CHANNEL,             \
        .request = UART3_RX_DMA_REQUEST,            \
        .irq = UART3_RX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* UART3_DMA_RX_CONFIG */
#endif /* BSP_UART3_RX_USING_DMA */

#ifdef BSP_UART3_TX_USING_DMA
#ifndef UART3_DMA_TX_CONFIG
#define UART3_DMA_TX_CONFIG                         \
    {                                               \
        .periph = UART3_TX_DMA_PERIPH,              \
        .rcu = UART3_TX_DMA_RCU,                    \
        .channel = UART3_TX_DMA_CHANNEL,             \
        .request = UART3_TX_DMA_REQUEST,            \
        .irq = UART3_TX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* UART3_DMA_TX_CONFIG */
#endif /* BSP_UART3_TX_USING_DMA */

/* UART4 DMA configuration */
#ifdef BSP_UART4_RX_USING_DMA
#ifndef UART4_DMA_RX_CONFIG
#define UART4_DMA_RX_CONFIG                         \
    {                                               \
        .periph = UART4_RX_DMA_PERIPH,              \
        .rcu = UART4_RX_DMA_RCU,                    \
        .channel = UART4_RX_DMA_CHANNEL,             \
        .request = UART4_RX_DMA_REQUEST,            \
        .irq = UART4_RX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* UART4_DMA_RX_CONFIG */
#endif /* BSP_UART4_RX_USING_DMA */

#ifdef BSP_UART4_TX_USING_DMA
#ifndef UART4_DMA_TX_CONFIG
#define UART4_DMA_TX_CONFIG                         \
    {                                               \
        .periph = UART4_TX_DMA_PERIPH,              \
        .rcu = UART4_TX_DMA_RCU,                    \
        .channel = UART4_TX_DMA_CHANNEL,             \
        .request = UART4_TX_DMA_REQUEST,            \
        .irq = UART4_TX_DMA_IRQ,                     \
        .data_width = DMA_PERIPH_WIDTH_8BIT,         \
    }
#endif /* UART4_DMA_TX_CONFIG */
#endif /* BSP_UART4_TX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */
