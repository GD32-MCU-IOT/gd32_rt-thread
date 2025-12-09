/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     SummerGift   first version
 * 2019-01-05     zylx         modify dma support
 * 2020-05-02     whj4674672   support stm32h7 uart dma
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_UART0_RX_USING_DMA)
#ifndef UART0_DMA_RX_CONFIG
#define UART0_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph   = UART0_RX_DMA_PERIPH,                            \
        .dma_flag = UART0_RX_DMA_FLAG,                              \
        .rcu      = UART0_RX_DMA_RCU,                               \
        .channel  = UART0_RX_DMA_CHANNEL,                           \
        .request  = UART0_RX_DMA_REQUEST,                           \
        .dma_irq  = UART0_RX_DMA_IRQ,                               \
    }
#endif /* UART0_DMA_RX_CONFIG */
#endif /* BSP_UART0_RX_USING_DMA */

#if defined(BSP_UART0_TX_USING_DMA)
#ifndef UART0_DMA_TX_CONFIG
#define UART0_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph   = UART0_TX_DMA_PERIPH,                            \
        .dma_flag = UART0_TX_DMA_FLAG,                              \
        .rcu      = UART0_TX_DMA_RCU,                               \
        .channel  = UART0_TX_DMA_CHANNEL,                           \
        .request  = UART0_TX_DMA_REQUEST,                           \
        .dma_irq  = UART0_TX_DMA_IRQ,                               \
    }
#endif /* UART0_DMA_TX_CONFIG */
#endif /* BSP_UART0_TX_USING_DMA */

#if defined(BSP_UART1_RX_USING_DMA)
#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph   = UART1_RX_DMA_PERIPH,                            \
        .dma_flag = UART1_RX_DMA_FLAG,                              \
        .rcu      = UART1_RX_DMA_RCU,                               \
        .channel  = UART1_RX_DMA_CHANNEL,                           \
        .request  = UART1_RX_DMA_REQUEST,                           \
        .dma_irq  = UART1_RX_DMA_IRQ,                               \
    }
#endif /* UART1_DMA_RX_CONFIG */
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(BSP_UART1_TX_USING_DMA)
#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph   = UART1_TX_DMA_PERIPH,                            \
        .dma_flag = UART1_TX_DMA_FLAG,                              \
        .rcu      = UART1_TX_DMA_RCU,                               \
        .channel  = UART1_TX_DMA_CHANNEL,                           \
        .request  = UART1_TX_DMA_REQUEST,                           \
        .dma_irq  = UART1_TX_DMA_IRQ,                               \
    }
#endif /* UART1_DMA_TX_CONFIG */
#endif /* BSP_UART1_TX_USING_DMA */

#if defined(BSP_UART2_RX_USING_DMA)
#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph   = UART2_RX_DMA_PERIPH,                            \
        .dma_flag = UART2_RX_DMA_FLAG,                              \
        .rcu      = UART2_RX_DMA_RCU,                               \
        .channel  = UART2_RX_DMA_CHANNEL,                           \
        .request  = UART2_RX_DMA_REQUEST,                           \
        .dma_irq  = UART2_RX_DMA_IRQ,                               \
    }
#endif /* UART2_DMA_RX_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(BSP_UART2_TX_USING_DMA)
#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph   = UART2_TX_DMA_PERIPH,                            \
        .dma_flag = UART2_TX_DMA_FLAG,                              \
        .rcu      = UART2_TX_DMA_RCU,                               \
        .channel  = UART2_TX_DMA_CHANNEL,                           \
        .request  = UART2_TX_DMA_REQUEST,                           \
        .dma_irq  = UART2_TX_DMA_IRQ,                               \
    }
#endif /* UART2_DMA_TX_CONFIG */
#endif /* BSP_UART2_TX_USING_DMA */

#if defined(BSP_UART3_RX_USING_DMA)
#ifndef UART3_DMA_RX_CONFIG
#define UART3_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph   = UART3_RX_DMA_PERIPH,                            \
        .dma_flag = UART3_RX_DMA_FLAG,                              \
        .rcu      = UART3_RX_DMA_RCU,                               \
        .channel  = UART3_RX_DMA_CHANNEL,                           \
        .request  = UART3_RX_DMA_REQUEST,                           \
        .dma_irq  = UART3_RX_DMA_IRQ,                               \
    }
#endif /* UART3_DMA_RX_CONFIG */
#endif /* BSP_UART3_RX_USING_DMA */

#if defined(BSP_UART3_TX_USING_DMA)
#ifndef UART3_DMA_TX_CONFIG
#define UART3_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph   = UART3_TX_DMA_PERIPH,                            \
        .dma_flag = UART3_TX_DMA_FLAG,                              \
        .rcu      = UART3_TX_DMA_RCU,                               \
        .channel  = UART3_TX_DMA_CHANNEL,                           \
        .request  = UART3_TX_DMA_REQUEST,                           \
        .dma_irq  = UART3_TX_DMA_IRQ,                               \
    }
#endif /* UART3_DMA_TX_CONFIG */
#endif /* BSP_UART3_TX_USING_DMA */

#if defined(BSP_UART4_RX_USING_DMA)
#ifndef UART4_DMA_RX_CONFIG
#define UART4_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph   = UART4_RX_DMA_PERIPH,                            \
        .dma_flag = UART4_RX_DMA_FLAG,                              \
        .rcu      = UART4_RX_DMA_RCU,                               \
        .channel  = UART4_RX_DMA_CHANNEL,                           \
        .request  = UART4_RX_DMA_REQUEST,                           \
        .dma_irq  = UART4_RX_DMA_IRQ,                               \
    }
#endif /* UART4_DMA_RX_CONFIG */
#endif /* BSP_UART4_RX_USING_DMA */

#if defined(BSP_UART4_TX_USING_DMA)
#ifndef UART4_DMA_TX_CONFIG
#define UART4_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph   = UART4_TX_DMA_PERIPH,                            \
        .dma_flag = UART4_TX_DMA_FLAG,                              \
        .rcu      = UART4_TX_DMA_RCU,                               \
        .channel  = UART4_TX_DMA_CHANNEL,                           \
        .request  = UART4_TX_DMA_REQUEST,                           \
        .dma_irq  = UART4_TX_DMA_IRQ,                               \
    }
#endif /* UART4_DMA_TX_CONFIG */
#endif /* BSP_UART4_TX_USING_DMA */

#if defined(BSP_UART5_RX_USING_DMA)
#ifndef UART5_DMA_RX_CONFIG
#define UART5_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph   = UART5_RX_DMA_PERIPH,                            \
        .dma_flag = UART5_RX_DMA_FLAG,                              \
        .rcu      = UART5_RX_DMA_RCU,                               \
        .channel  = UART5_RX_DMA_CHANNEL,                           \
        .request  = UART5_RX_DMA_REQUEST,                           \
        .dma_irq  = UART5_RX_DMA_IRQ,                               \
    }
#endif /* UART5_DMA_RX_CONFIG */
#endif /* BSP_UART5_RX_USING_DMA */

#if defined(BSP_UART5_TX_USING_DMA)
#ifndef UART5_DMA_TX_CONFIG
#define UART5_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph   = UART5_TX_DMA_PERIPH,                            \
        .dma_flag = UART5_TX_DMA_FLAG,                              \
        .rcu      = UART5_TX_DMA_RCU,                               \
        .channel  = UART5_TX_DMA_CHANNEL,                           \
        .request  = UART5_TX_DMA_REQUEST,                           \
        .dma_irq  = UART5_TX_DMA_IRQ,                               \
    }
#endif /* UART5_DMA_TX_CONFIG */
#endif /* BSP_UART5_TX_USING_DMA */

#if defined(BSP_UART6_RX_USING_DMA)
#ifndef UART6_DMA_RX_CONFIG
#define UART6_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph   = UART6_RX_DMA_PERIPH,                            \
        .dma_flag = UART6_RX_DMA_FLAG,                              \
        .rcu      = UART6_RX_DMA_RCU,                               \
        .channel  = UART6_RX_DMA_CHANNEL,                           \
        .request  = UART6_RX_DMA_REQUEST,                           \
        .dma_irq  = UART6_RX_DMA_IRQ,                               \
    }
#endif /* UART6_DMA_RX_CONFIG */
#endif /* BSP_UART6_RX_USING_DMA */

#if defined(BSP_UART6_TX_USING_DMA)
#ifndef UART6_DMA_TX_CONFIG
#define UART6_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph   = UART6_TX_DMA_PERIPH,                            \
        .dma_flag = UART6_TX_DMA_FLAG,                              \
        .rcu      = UART6_TX_DMA_RCU,                               \
        .channel  = UART6_TX_DMA_CHANNEL,                           \
        .request  = UART6_TX_DMA_REQUEST,                           \
        .dma_irq  = UART6_TX_DMA_IRQ,                               \
    }
#endif /* UART6_DMA_TX_CONFIG */
#endif /* BSP_UART6_TX_USING_DMA */

#if defined(BSP_UART7_RX_USING_DMA)
#ifndef UART7_DMA_RX_CONFIG
#define UART7_DMA_RX_CONFIG                                         \
    {                                                               \
        .periph   = UART7_RX_DMA_PERIPH,                            \
        .dma_flag = UART7_RX_DMA_FLAG,                              \
        .rcu      = UART7_RX_DMA_RCU,                               \
        .channel  = UART7_RX_DMA_CHANNEL,                           \
        .request  = UART7_RX_DMA_REQUEST,                           \
        .dma_irq  = UART7_RX_DMA_IRQ,                               \
    }
#endif /* UART7_DMA_RX_CONFIG */
#endif /* BSP_UART7_RX_USING_DMA */

#if defined(BSP_UART7_TX_USING_DMA)
#ifndef UART7_DMA_TX_CONFIG
#define UART7_DMA_TX_CONFIG                                         \
    {                                                               \
        .periph   = UART7_TX_DMA_PERIPH,                            \
        .dma_flag = UART7_TX_DMA_FLAG,                              \
        .rcu      = UART7_TX_DMA_RCU,                               \
        .channel  = UART7_TX_DMA_CHANNEL,                           \
        .request  = UART7_TX_DMA_REQUEST,                           \
        .dma_irq  = UART7_TX_DMA_IRQ,                               \
    }
#endif /* UART7_DMA_TX_CONFIG */
#endif /* BSP_UART7_TX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif
