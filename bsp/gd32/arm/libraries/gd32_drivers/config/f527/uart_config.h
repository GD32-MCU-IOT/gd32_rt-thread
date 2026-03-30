/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-03-20     RT-Thread    first implementation for GD32F5xx
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
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART0_RX_DMA_RCU,                              \
        .channel    = UART0_RX_DMA_CHANNEL,                          \
        .subperiph  = UART0_RX_DMA_SUBPERI,                          \
        .irq        = UART0_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART0_DMA_RX_CONFIG */
#endif /* BSP_UART0_RX_USING_DMA */

#if defined(BSP_UART0_TX_USING_DMA)
#ifndef UART0_DMA_TX_CONFIG
#define UART0_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART0_TX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART0_TX_DMA_RCU,                              \
        .channel    = UART0_TX_DMA_CHANNEL,                          \
        .subperiph  = UART0_TX_DMA_SUBPERI,                          \
        .irq        = UART0_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART0_DMA_TX_CONFIG */
#endif /* BSP_UART0_TX_USING_DMA */

/* UART1 DMA configuration */
#if defined(BSP_UART1_RX_USING_DMA)
#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART1_RX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART1_RX_DMA_RCU,                              \
        .channel    = UART1_RX_DMA_CHANNEL,                          \
        .subperiph  = UART1_RX_DMA_SUBPERI,                          \
        .irq        = UART1_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART1_DMA_RX_CONFIG */
#endif
#if defined(BSP_UART1_TX_USING_DMA)
#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART1_TX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART1_TX_DMA_RCU,                              \
        .channel    = UART1_TX_DMA_CHANNEL,                          \
        .subperiph  = UART1_TX_DMA_SUBPERI,                          \
        .irq        = UART1_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART1_DMA_TX_CONFIG */
#endif
/* UART2 DMA configuration */
#if defined(BSP_UART2_RX_USING_DMA)
#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART2_RX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART2_RX_DMA_RCU,                              \
        .channel    = UART2_RX_DMA_CHANNEL,                          \
        .subperiph  = UART2_RX_DMA_SUBPERI,                          \
        .irq        = UART2_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART2_DMA_RX_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(BSP_UART2_TX_USING_DMA)
#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART2_TX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART2_TX_DMA_RCU,                              \
        .channel    = UART2_TX_DMA_CHANNEL,                          \
        .subperiph  = UART2_TX_DMA_SUBPERI,                          \
        .irq        = UART2_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART2_DMA_TX_CONFIG */
#endif /* BSP_UART2_TX_USING_DMA */

/* UART3 DMA configuration */
#if defined(BSP_UART3_RX_USING_DMA)
#ifndef UART3_DMA_RX_CONFIG
#define UART3_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART3_RX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART3_RX_DMA_RCU,                              \
        .channel    = UART3_RX_DMA_CHANNEL,                          \
        .subperiph  = UART3_RX_DMA_SUBPERI,                          \
        .irq        = UART3_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART3_DMA_RX_CONFIG */
#endif /* BSP_UART3_RX_USING_DMA */

#if defined(BSP_UART3_TX_USING_DMA)
#ifndef UART3_DMA_TX_CONFIG
#define UART3_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART3_TX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART3_TX_DMA_RCU,                              \
        .channel    = UART3_TX_DMA_CHANNEL,                          \
        .subperiph  = UART3_TX_DMA_SUBPERI,                          \
        .irq        = UART3_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART3_DMA_TX_CONFIG */
#endif /* BSP_UART3_TX_USING_DMA */

/* UART4 DMA configuration */
#if defined(BSP_UART4_RX_USING_DMA)
#ifndef UART4_DMA_RX_CONFIG
#define UART4_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART4_RX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART4_RX_DMA_RCU,                              \
        .channel    = UART4_RX_DMA_CHANNEL,                          \
        .subperiph  = UART4_RX_DMA_SUBPERI,                          \
        .irq        = UART4_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART4_DMA_RX_CONFIG */
#endif /* BSP_UART4_RX_USING_DMA */

#if defined(BSP_UART4_TX_USING_DMA)
#ifndef UART4_DMA_TX_CONFIG
#define UART4_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART4_TX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART4_TX_DMA_RCU,                              \
        .channel    = UART4_TX_DMA_CHANNEL,                          \
        .subperiph  = UART4_TX_DMA_SUBPERI,                          \
        .irq        = UART4_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART4_DMA_TX_CONFIG */
#endif /* BSP_UART4_TX_USING_DMA */

/* UART5 DMA configuration */
#if defined(BSP_UART5_RX_USING_DMA)
#ifndef UART5_DMA_RX_CONFIG
#define UART5_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART5_RX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART5_RX_DMA_RCU,                              \
        .channel    = UART5_RX_DMA_CHANNEL,                          \
        .subperiph  = UART5_RX_DMA_SUBPERI,                          \
        .irq        = UART5_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART5_DMA_RX_CONFIG */
#endif /* BSP_UART5_RX_USING_DMA */

#if defined(BSP_UART5_TX_USING_DMA)
#ifndef UART5_DMA_TX_CONFIG
#define UART5_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART5_TX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART5_TX_DMA_RCU,                              \
        .channel    = UART5_TX_DMA_CHANNEL,                          \
        .subperiph  = UART5_TX_DMA_SUBPERI,                          \
        .irq        = UART5_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART5_DMA_TX_CONFIG */
#endif /* BSP_UART5_TX_USING_DMA */

/* UART6 DMA configuration */
#if defined(BSP_UART6_RX_USING_DMA)
#ifndef UART6_DMA_RX_CONFIG
#define UART6_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART6_RX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART6_RX_DMA_RCU,                              \
        .channel    = UART6_RX_DMA_CHANNEL,                          \
        .subperiph  = UART6_RX_DMA_SUBPERI,                          \
        .irq        = UART6_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART6_DMA_RX_CONFIG */
#endif /* BSP_UART6_RX_USING_DMA */

#if defined(BSP_UART6_TX_USING_DMA)
#ifndef UART6_DMA_TX_CONFIG
#define UART6_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART6_TX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART6_TX_DMA_RCU,                              \
        .channel    = UART6_TX_DMA_CHANNEL,                          \
        .subperiph  = UART6_TX_DMA_SUBPERI,                          \
        .irq        = UART6_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART6_DMA_TX_CONFIG */
#endif /* BSP_UART6_TX_USING_DMA */

/* UART7 DMA configuration */
#if defined(BSP_UART7_RX_USING_DMA)
#ifndef UART7_DMA_RX_CONFIG
#define UART7_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph     = UART7_RX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART7_RX_DMA_RCU,                              \
        .channel    = UART7_RX_DMA_CHANNEL,                          \
        .subperiph  = UART7_RX_DMA_SUBPERI,                          \
        .irq        = UART7_RX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART7_DMA_RX_CONFIG */
#endif /* BSP_UART7_RX_USING_DMA */

#if defined(BSP_UART7_TX_USING_DMA)
#ifndef UART7_DMA_TX_CONFIG
#define UART7_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph     = UART7_TX_DMA_PERIPH,                          \
        .dma_flag   = DMA_INTF_FTFIF,                                \
        .rcu        = UART7_TX_DMA_RCU,                              \
        .channel    = UART7_TX_DMA_CHANNEL,                          \
        .subperiph  = UART7_TX_DMA_SUBPERI,                          \
        .irq        = UART7_TX_DMA_IRQ,                              \
        .data_width = DMA_PERIPH_WIDTH_8BIT,                         \
    }
#endif /* UART7_DMA_TX_CONFIG */
#endif /* BSP_UART7_TX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /* __UART_CONFIG_H__ */
