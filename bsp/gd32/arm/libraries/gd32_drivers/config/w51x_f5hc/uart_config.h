/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-04     RT-Thread    UART DMA config for GD32W51x_F5HC
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* UART0 DMA configuration */
#if defined(BSP_UART0_RX_USING_DMA)
#ifndef UART0_DMA_RX_CONFIG
#define UART0_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART0_RX_DMA_PERIPH,                          \
        .rcu        = UART0_RX_DMA_RCU,                              \
        .channel    = UART0_RX_DMA_CHANNEL,                          \
        .subperiph  = UART0_RX_DMA_SUBPERI,                          \
        .irq        = UART0_RX_DMA_IRQ,                              \
    }
#endif /* UART0_DMA_RX_CONFIG */
#endif /* BSP_UART0_RX_USING_DMA */

#if defined(BSP_UART0_TX_USING_DMA)
#ifndef UART0_DMA_TX_CONFIG
#define UART0_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART0_TX_DMA_PERIPH,                          \
        .rcu        = UART0_TX_DMA_RCU,                              \
        .channel    = UART0_TX_DMA_CHANNEL,                          \
        .subperiph  = UART0_TX_DMA_SUBPERI,                          \
        .irq        = UART0_TX_DMA_IRQ,                              \
    }
#endif /* UART0_DMA_TX_CONFIG */
#endif /* BSP_UART0_TX_USING_DMA */

/* UART1 DMA configuration */
#if defined(BSP_UART1_RX_USING_DMA)
#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART1_RX_DMA_PERIPH,                          \
        .rcu        = UART1_RX_DMA_RCU,                              \
        .channel    = UART1_RX_DMA_CHANNEL,                          \
        .subperiph  = UART1_RX_DMA_SUBPERI,                          \
        .irq        = UART1_RX_DMA_IRQ,                              \
    }
#endif /* UART1_DMA_RX_CONFIG */
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(BSP_UART1_TX_USING_DMA)
#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART1_TX_DMA_PERIPH,                          \
        .rcu        = UART1_TX_DMA_RCU,                              \
        .channel    = UART1_TX_DMA_CHANNEL,                          \
        .subperiph  = UART1_TX_DMA_SUBPERI,                          \
        .irq        = UART1_TX_DMA_IRQ,                              \
    }
#endif /* UART1_DMA_TX_CONFIG */
#endif /* BSP_UART1_TX_USING_DMA */

/* UART2 DMA configuration */
#if defined(BSP_UART2_RX_USING_DMA)
#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART2_RX_DMA_PERIPH,                          \
        .rcu        = UART2_RX_DMA_RCU,                              \
        .channel    = UART2_RX_DMA_CHANNEL,                          \
        .subperiph  = UART2_RX_DMA_SUBPERI,                          \
        .irq        = UART2_RX_DMA_IRQ,                              \
    }
#endif /* UART2_DMA_RX_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(BSP_UART2_TX_USING_DMA)
#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART2_TX_DMA_PERIPH,                          \
        .rcu        = UART2_TX_DMA_RCU,                              \
        .channel    = UART2_TX_DMA_CHANNEL,                          \
        .subperiph  = UART2_TX_DMA_SUBPERI,                          \
        .irq        = UART2_TX_DMA_IRQ,                              \
    }
#endif /* UART2_DMA_TX_CONFIG */
#endif /* BSP_UART2_TX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */
