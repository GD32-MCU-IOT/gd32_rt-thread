/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 * 2024-03-19     Evlers       remove the include of drv_usart.h
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "gd32f5xx.h"
#include "drv_gpio.h"

#include "gd32f5xx_exti.h"
#include "drv_hard_i2c.h"
#include "drv_usart.h"
#include "drv_spi.h"

#define EXT_SDRAM_BEGIN    (0xC0000000U) /* the begining address of external SDRAM */
#define EXT_SDRAM_END      (EXT_SDRAM_BEGIN + (32U * 1024 * 1024)) /* the end address of external SDRAM */

// <o> Internal SRAM memory size[Kbytes] <8-512>
//  <i>Default: 448
#ifdef __ICCARM__
// Use *.icf ram symbal, to avoid hardcode.
extern char __ICFEDIT_region_RAM_end__;
#define GD32_SRAM_END          &__ICFEDIT_region_RAM_end__
#else
#define GD32_SRAM_SIZE         448
#define GD32_SRAM_END          (0x20000000 + GD32_SRAM_SIZE * 1024)
#endif

#ifdef __ARMCC_VERSION
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#endif

#define HEAP_END          GD32_SRAM_END

#endif

#ifdef BSP_USING_SPI_DMA
#if defined(BSP_SPI5_USING_DMA) && !defined(SPI5_TX_DMA_PERIPH)
#define SPI5_TX_DMA_PERIPH              DMA1
#define SPI5_DMA_TX_IRQHandler          DMA1_Channel5_IRQHandler
#define SPI5_TX_DMA_RCU                 RCU_DMA1
#define SPI5_TX_DMA_CHANNEL             DMA_CH5
#define SPI5_TX_DMA_IRQ                 DMA1_Channel5_IRQn
#define SPI5_TX_DMA_SUBPERI             DMA_SUBPERI1
#endif

/* SPI5 RX: DMA1 channel6, subperi1 */
#if defined(BSP_SPI5_USING_DMA) && !defined(SPI5_RX_DMA_PERIPH)
#define SPI5_RX_DMA_PERIPH              DMA1
#define SPI5_DMA_RX_IRQHandler          DMA1_Channel6_IRQHandler
#define SPI5_RX_DMA_RCU                 RCU_DMA1
#define SPI5_RX_DMA_CHANNEL             DMA_CH6
#define SPI5_RX_DMA_IRQ                 DMA1_Channel6_IRQn
#define SPI5_RX_DMA_SUBPERI             DMA_SUBPERI1
#endif
#endif

/* UART1 TX DMA configuration override */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_PERIPH)
#define UART1_DMA_TX_IRQHandler         DMA0_Channel6_IRQHandler
#define UART1_TX_DMA_RCU                RCU_DMA0
#define UART1_TX_DMA_PERIPH             DMA0
#define UART1_TX_DMA_CHANNEL            DMA_CH6
#define UART1_TX_DMA_IRQ                DMA0_Channel6_IRQn
#define UART1_TX_DMA_SUBPERI            DMA_SUBPERI4
#endif

/* UART1 RX DMA configuration override */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_PERIPH)
#define UART1_DMA_RX_IRQHandler         DMA0_Channel5_IRQHandler
#define UART1_RX_DMA_RCU                RCU_DMA0
#define UART1_RX_DMA_PERIPH             DMA0
#define UART1_RX_DMA_CHANNEL            DMA_CH5
#define UART1_RX_DMA_IRQ                DMA0_Channel5_IRQn
#define UART1_RX_DMA_SUBPERI            DMA_SUBPERI4
#endif