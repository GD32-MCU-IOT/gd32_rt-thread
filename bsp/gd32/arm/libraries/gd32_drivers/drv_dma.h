/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2024-03-19   Evlers      first implementation
 */

#ifndef _DRV_DMA_H_
#define _DRV_DMA_H_

#include <rtdef.h>
#include <board.h>

/* ============================================================================
 * Section 0: Per-series DMA feature matrix - the only place series names appear.
 *   USING_DMAMUX / USING_SUBPERIPH : how a request reaches a channel
 *   USING_FIFO       : newer generation, dma_single_data_parameter_struct
 *   SINGLE_PERIPH    : one controller, APIs drop the leading periph argument
 *   MERGED_IRQ       : several channels share one IRQ vector
 *   DEINIT_IS_GLOBAL : dma_deinit() resets the controller, not a channel
 *   no flag          : fixed mapping, old generation, dual controller
 * ============================================================================ */
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E)
#define GD32_DMA_USING_DMAMUX
#define GD32_DMA_USING_FIFO

#elif defined(SOC_SERIES_GD32H77x)
#define GD32_DMA_USING_DMAMUX
#define GD32_DMA_USING_FIFO
#define GD32_DMA_DEINIT_IS_GLOBAL

#elif defined(SOC_SERIES_GD32F50x) || defined(SOC_SERIES_GD32G5x3) \
   || defined(SOC_SERIES_GD32M53x)
#define GD32_DMA_USING_DMAMUX

#elif defined(SOC_SERIES_GD32L23x)
#define GD32_DMA_USING_DMAMUX
#define GD32_DMA_SINGLE_PERIPH

#elif defined(SOC_SERIES_GD32F4xx) || defined(SOC_SERIES_GD32F5xx) \
   || defined(SOC_SERIES_GD32W51x_F5HC)
#define GD32_DMA_USING_SUBPERIPH
#define GD32_DMA_USING_FIFO

#elif defined(SOC_SERIES_GD32E23x) || defined(SOC_SERIES_GD32F3x0)
#define GD32_DMA_SINGLE_PERIPH
#define GD32_DMA_MERGED_IRQ

#endif  /* F10x F20x F30x C11x E11x E50x E51x need no flag */

/* ============================================================================
 * Section 1: Aliases for symbols that only part of the firmware libraries ship.
 * ============================================================================ */

/* DMA transfer direction: families use either DMA_PERIPH_* or DMA_PERIPHERAL_*. */
#ifndef DMA_PERIPH_TO_MEMORY
#define DMA_PERIPH_TO_MEMORY                 DMA_PERIPHERAL_TO_MEMORY
#endif
#ifndef DMA_MEMORY_TO_PERIPH
#define DMA_MEMORY_TO_PERIPH                 DMA_MEMORY_TO_PERIPHERAL
#endif

/* DMA data width: families use either DMA_PERIPH_WIDTH_* or DMA_PERIPHERAL_WIDTH_*. */
#ifndef DMA_PERIPH_WIDTH_8BIT
#define DMA_PERIPH_WIDTH_8BIT                DMA_PERIPHERAL_WIDTH_8BIT
#endif
#ifndef DMA_PERIPH_WIDTH_16BIT
#define DMA_PERIPH_WIDTH_16BIT               DMA_PERIPHERAL_WIDTH_16BIT
#endif
#ifndef DMA_PERIPH_WIDTH_32BIT
#define DMA_PERIPH_WIDTH_32BIT               DMA_PERIPHERAL_WIDTH_32BIT
#endif

/* Pre-FIFO DMA has no FIFO/transfer-access error bit, only a generic DMA_FLAG_ERR. */
#ifndef GD32_DMA_USING_FIFO
#define DMA_FLAG_FEE                         DMA_FLAG_ERR
#define DMA_FLAG_SDE                         DMA_FLAG_ERR
#define DMA_FLAG_TAE                         DMA_FLAG_ERR
#endif

#ifndef DMA0
#define DMA0                                 DMA
#define RCU_DMA0                             RCU_DMA
#endif

/* ============================================================================
 * Section 2: struct dma_config, keyed on how a DMA request reaches a channel.
 * ============================================================================ */
#if defined(GD32_DMA_MERGED_IRQ)
#define GD32_DMA_MERGED_IRQN_0              DMA_Channel0_IRQn
#define GD32_DMA_MERGED_IRQN_1              DMA_Channel1_2_IRQn
#define GD32_DMA_MERGED_IRQN_2              DMA_Channel1_2_IRQn
#define GD32_DMA_MERGED_IRQN_3              DMA_Channel3_4_IRQn
#define GD32_DMA_MERGED_IRQN_4              DMA_Channel3_4_IRQn
/* f3x0 has 7 channels; channels 5/6 share DMA_Channel5_6_IRQn */
#define GD32_DMA_MERGED_IRQN_5              DMA_Channel5_6_IRQn
#define GD32_DMA_MERGED_IRQN_6              DMA_Channel5_6_IRQn
#define GD32_DMA_MERGED_IRQN(chx)           GD32_DMA_MERGED_IRQN_##chx

#define DRV_DMA_CONFIG(chx)                 {                                                   \
                                                .periph     = DMA,                              \
                                                .channel    = DMA_CH##chx,                      \
                                                .rcu        = RCU_DMA,                          \
                                                .irq        = GD32_DMA_MERGED_IRQN(chx),        \
                                                .data_width = DMA_PERIPH_WIDTH_8BIT,            \
                                            }

struct dma_config
{
    uint32_t periph;
    uint32_t dma_flag;
    rcu_periph_enum rcu;
    dma_channel_enum channel;
    IRQn_Type irq;
    uint32_t data_width;
};

#elif defined(GD32_DMA_USING_DMAMUX)
#ifdef GD32_DMA_SINGLE_PERIPH
#define GD32_DMA_CHANNEL_IRQN(dmax, chx)    DMA_Channel##chx##_IRQn
#else
#define GD32_DMA_CHANNEL_IRQN(dmax, chx)    DMA##dmax##_Channel##chx##_IRQn
#endif

#define DRV_DMA_CONFIG(dmax, chx, reqx)     {                                                   \
                                                .periph     = DMA##dmax,                        \
                                                .channel    = DMA_CH##chx,                      \
                                                .rcu        = RCU_DMA##dmax,                    \
                                                .request    = (uint32_t)(reqx),                 \
                                                .irq        = GD32_DMA_CHANNEL_IRQN(dmax, chx), \
                                                .data_width = DMA_PERIPH_WIDTH_8BIT,            \
                                            }

struct dma_config
{
    uint32_t periph;
    uint32_t dma_flag;
    rcu_periph_enum rcu;
    dma_channel_enum channel;
    uint32_t request;
    IRQn_Type irq;
    uint32_t data_width;
};

#elif defined(GD32_DMA_USING_SUBPERIPH)

#define DRV_DMA_CONFIG(dmax, chx, subx)     {                                                   \
                                                .periph     = DMA##dmax,                        \
                                                .channel    = DMA_CH##chx,                      \
                                                .rcu        = RCU_DMA##dmax,                    \
                                                .subperiph  = DMA_SUBPERI##subx,                \
                                                .irq        = DMA##dmax##_Channel##chx##_IRQn,  \
                                                .data_width = DMA_PERIPH_WIDTH_8BIT,            \
                                            }

struct dma_config
{
    uint32_t periph;
    uint32_t dma_flag;
    rcu_periph_enum rcu;
    dma_channel_enum channel;
    dma_subperipheral_enum subperiph;
    IRQn_Type irq;
    uint32_t data_width;    /* DMA transfer data width: DMA_PERIPH_WIDTH_8BIT/16BIT/32BIT */
};

#else
/* Fixed channel mapping: no routing field at all. */
#define DRV_DMA_CONFIG(dmax, chx)           {                                                   \
                                                .periph     = DMA##dmax,                        \
                                                .channel    = DMA_CH##chx,                      \
                                                .rcu        = RCU_DMA##dmax,                    \
                                                .irq        = DMA##dmax##_Channel##chx##_IRQn,  \
                                                .data_width = DMA_PERIPH_WIDTH_8BIT,            \
                                            }

struct dma_config
{
    uint32_t periph;
    uint32_t dma_flag;
    rcu_periph_enum rcu;
    dma_channel_enum channel;
    IRQn_Type irq;
    uint32_t data_width;
};

#endif

/* ============================================================================
 * Section 3: Routing helpers shared by usart/spi/i2c.
 * ============================================================================ */
#ifdef GD32_DMA_USING_DMAMUX
#define gd32_dma_request_config(init_s, dma_cfg)    ((init_s)->request = (dma_cfg)->request)
#else
#define gd32_dma_request_config(init_s, dma_cfg)
#endif

#ifdef GD32_DMA_USING_SUBPERIPH
#define gd32_dma_subperiph_config(periph, ch, cfg)  dma_channel_subperipheral_select(periph, ch, (cfg)->subperiph)
#else
#define gd32_dma_subperiph_config(periph, ch, cfg)  ((void)0)
#endif

#if defined(GD32_DMA_DEINIT_IS_GLOBAL)
#define gd32_dma_deinit(periph, ch)                 dma_channel_deinit(periph, ch)
#elif defined(GD32_DMA_SINGLE_PERIPH)
#define gd32_dma_deinit(periph, ch)                 dma_deinit(ch)
#else
#define gd32_dma_deinit(periph, ch)                 dma_deinit(periph, ch)
#endif

/* ============================================================================
 * Section 4: struct/type redirects, keyed on the DMA generation.
 * ============================================================================ */
#ifdef GD32_DMA_USING_FIFO
#define gd32_dma_single_data_parameter_struct       dma_single_data_parameter_struct
#define gd32_dma_single_data_para_struct_init(s)    dma_single_data_para_struct_init(s)
#define GD32_DMA_SET_MEMADDR(s, v)           ((s)->memory0_addr = (v))
#define GD32_DMA_SET_DATAWIDTH(s, v)         ((s)->periph_memory_width = (v))
#define GD32_DMA_SET_CIRCULAR(s, v)          ((s)->circular_mode = (v))
#else
#define gd32_dma_single_data_parameter_struct       dma_parameter_struct
#define gd32_dma_single_data_para_struct_init(s)    dma_struct_para_init(s)
/* CHCTL_MWIDTH(n) = CHCTL_PWIDTH(n) << 2, so shift converts between widths. */
#define GD32_DMA_SET_MEMADDR(s, v)           ((s)->memory_addr = (v))
#define GD32_DMA_SET_DATAWIDTH(s, v)         do { (s)->periph_width = (v); \
                                                  (s)->memory_width = (v) << 2; } while(0)
/* No circular_mode field; use gd32_dma_circulation_enable/disable() at runtime. */
#define GD32_DMA_SET_CIRCULAR(s, v)          ((void)0)
#endif

/* ============================================================================
 * Section 5: gd32_dma_* facade over the firmware API - callers always pass
 *   (periph, channel, ...) no matter which generation is underneath.
 * ============================================================================ */
#ifdef GD32_DMA_USING_FIFO
#define gd32_dma_single_data_mode_init(p, ch, s)    dma_single_data_mode_init(p, ch, s)
#define gd32_dma_memory_address_config(p, ch, idx, addr) \
        dma_memory_address_config(p, ch, idx, (uint32_t)(addr))
#define gd32_dma_memory_address_generation_config(p, ch, inc) \
        dma_memory_address_generation_config(p, ch, inc)

#elif !defined(GD32_DMA_SINGLE_PERIPH)
#define gd32_dma_single_data_mode_init(p, ch, s)    dma_init(p, ch, s)
#define gd32_dma_memory_address_config(p, ch, idx, addr) \
        dma_memory_address_config(p, ch, (uint32_t)(addr))
#define gd32_dma_memory_address_generation_config(p, ch, inc) \
        gd32_dma_mem_inc_##inc(p, ch)
#define gd32_dma_mem_inc_DMA_MEMORY_INCREASE_ENABLE(p, ch)      dma_memory_increase_enable(p, ch)
#define gd32_dma_mem_inc_DMA_MEMORY_INCREASE_DISABLE(p, ch)     dma_memory_increase_disable(p, ch)

#else
#define gd32_dma_single_data_mode_init(p, ch, s)    dma_init(ch, s)
#define gd32_dma_memory_address_config(p, ch, idx, addr) \
        dma_memory_address_config(ch, (uint32_t)(addr))
#define gd32_dma_memory_address_generation_config(p, ch, inc) \
        gd32_dma_mem_inc_##inc(ch)
#define gd32_dma_mem_inc_DMA_MEMORY_INCREASE_ENABLE(ch)         dma_memory_increase_enable(ch)
#define gd32_dma_mem_inc_DMA_MEMORY_INCREASE_DISABLE(ch)        dma_memory_increase_disable(ch)
#endif

#ifdef GD32_DMA_SINGLE_PERIPH
#define gd32_dma_channel_enable(p, ch)          dma_channel_enable(ch)
#define gd32_dma_channel_disable(p, ch)         dma_channel_disable(ch)
#define gd32_dma_circulation_enable(p, ch)      dma_circulation_enable(ch)
#define gd32_dma_circulation_disable(p, ch)     dma_circulation_disable(ch)
#define gd32_dma_transfer_number_config(p, ch, n)   dma_transfer_number_config(ch, n)
#define gd32_dma_transfer_number_get(p, ch)     dma_transfer_number_get(ch)
#define gd32_dma_flag_get(p, ch, f)             dma_flag_get(ch, f)
#define gd32_dma_flag_clear(p, ch, f)           dma_flag_clear(ch, f)
#define gd32_dma_interrupt_enable(p, ch, src)   dma_interrupt_enable(ch, src)
#define gd32_dma_interrupt_flag_get(p, ch, f)   dma_interrupt_flag_get(ch, f)
#define gd32_dma_interrupt_flag_clear(p, ch, f) dma_interrupt_flag_clear(ch, f)
#else
#define gd32_dma_channel_enable(p, ch)          dma_channel_enable(p, ch)
#define gd32_dma_channel_disable(p, ch)         dma_channel_disable(p, ch)
#define gd32_dma_circulation_enable(p, ch)      dma_circulation_enable(p, ch)
#define gd32_dma_circulation_disable(p, ch)     dma_circulation_disable(p, ch)
#define gd32_dma_transfer_number_config(p, ch, n)   dma_transfer_number_config(p, ch, n)
#define gd32_dma_transfer_number_get(p, ch)     dma_transfer_number_get(p, ch)
#define gd32_dma_flag_get(p, ch, f)             dma_flag_get(p, ch, f)
#define gd32_dma_flag_clear(p, ch, f)           dma_flag_clear(p, ch, f)
#define gd32_dma_interrupt_enable(p, ch, src)   dma_interrupt_enable(p, ch, src)
#define gd32_dma_interrupt_flag_get(p, ch, f)   dma_interrupt_flag_get(p, ch, f)
#define gd32_dma_interrupt_flag_clear(p, ch, f) dma_interrupt_flag_clear(p, ch, f)
#endif

#endif /* _DRV_DMA_H_ */
