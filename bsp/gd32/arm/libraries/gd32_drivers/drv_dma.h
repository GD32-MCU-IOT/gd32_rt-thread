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


#if defined SOC_SERIES_GD32E23x
#define DRV_DMA_CONFIG(chx)                                                 \
    (struct dma_config) {                                                   \
        .periph  = DMA,                                                     \
        .rcu     = RCU_DMA,                                                 \
        .channel = DMA_CH##chx,                                             \
        .irq     = ((chx) == 0 ? DMA_Channel0_IRQn :                         \
                    (chx) == 1 ? DMA_Channel1_2_IRQn :                         \
                    (chx) == 2 ? DMA_Channel1_2_IRQn :                         \
                    (chx) == 3 ? DMA_Channel3_4_IRQn :                         \
                    (chx) == 4 ? DMA_Channel3_4_IRQn : (IRQn_Type)0)           \
    }
struct dma_config
{
    uint32_t periph;
    uint32_t dma_flag;
    rcu_periph_enum rcu;
    dma_channel_enum channel;
    IRQn_Type irq;
};

#elif defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
/* DMAMUX + MDMA - reqx is DMAMUX request ID or subperipheral index */
#define DRV_DMA_CONFIG(dmax, chx, reqx)     {                                                   \
                                                .periph     = DMA##dmax,                        \
                                                .channel    = DMA_CH##chx,                      \
                                                .rcu        = RCU_DMA##dmax,                    \
                                                .request    = (uint32_t)(reqx),                 \
                                                .irq        = DMA##dmax##_Channel##chx##_IRQn,  \
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

#elif defined(SOC_SERIES_GD32F30x)
/* Fixed DMA channel mapping - no sub-peripheral selection */
#define DRV_DMA_CONFIG(dmax, chx)           {                                                   \
                                                .periph     = DMA##dmax,                        \
                                                .channel    = DMA_CH##chx,                      \
                                                .rcu        = RCU_DMA##dmax,                    \
                                                .irq        = DMA##dmax##_Channel##chx##_IRQn,  \
                                                .data_width = DMA_PERIPHERAL_WIDTH_8BIT,        \
                                            }

struct dma_config
{
    uint32_t periph;
    rcu_periph_enum rcu;
    dma_channel_enum channel;
    IRQn_Type irq;
    uint32_t data_width;
};

#else

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

#endif

#if defined(SOC_SERIES_GD32F30x)
/* DMA init struct type and functions */
#define dma_single_data_parameter_struct     dma_parameter_struct
#define dma_single_data_para_struct_init(s)  dma_struct_para_init(s)
#define dma_single_data_mode_init(p, ch, s)  dma_init(p, ch, s)
/* Direction enums */
#define DMA_PERIPH_TO_MEMORY                 DMA_PERIPHERAL_TO_MEMORY
#define DMA_MEMORY_TO_PERIPH                 DMA_MEMORY_TO_PERIPHERAL
/* Data width enums: F4xx DMA_PERIPH_WIDTH → F30x DMA_PERIPHERAL_WIDTH */
#define DMA_PERIPH_WIDTH_8BIT                DMA_PERIPHERAL_WIDTH_8BIT
#define DMA_PERIPH_WIDTH_16BIT               DMA_PERIPHERAL_WIDTH_16BIT
#define DMA_PERIPH_WIDTH_32BIT               DMA_PERIPHERAL_WIDTH_32BIT
/* DMA error flags: F30x has no FIFO/access error, map to generic DMA_FLAG_ERR */
#define DMA_FLAG_FEE                         DMA_FLAG_ERR
#define DMA_FLAG_TAE                         DMA_FLAG_ERR
/* DMA memory address config: F4xx 4-arg → F30x 3-arg (ignore memory index) */
#define dma_memory_address_config(p, ch, idx, addr) \
    dma_memory_address_config(p, ch, (uint32_t)(addr))
/* DMA init struct field accessors: F30x has different field names than F4xx */
#define GD32_DMA_SET_MEMADDR(s, v)           ((s)->memory_addr = (v))
/* F30x has separate periph_width / memory_width instead of periph_memory_width.
 * CHCTL_MWIDTH(n) = CHCTL_PWIDTH(n) << 2, so shift converts between them. */
#define GD32_DMA_SET_DATAWIDTH(s, v)         do { (s)->periph_width = (v); \
                                                  (s)->memory_width = (v) << 2; } while(0)
/* F30x has no circular_mode field; use dma_circulation_disable() API instead */
#define GD32_DMA_SET_CIRCULAR(s, v)          ((void)0)
/* DMA memory increment: F4xx dma_memory_address_generation_config → F30x APIs */
#define dma_memory_address_generation_config(p, ch, inc) \
    _gd32_dma_mem_inc_##inc(p, ch)
#define _gd32_dma_mem_inc_DMA_MEMORY_INCREASE_ENABLE(p, ch) \
    dma_memory_increase_enable(p, ch)
#define _gd32_dma_mem_inc_DMA_MEMORY_INCREASE_DISABLE(p, ch) \
    dma_memory_increase_disable(p, ch)
#else
/* F4xx/F5xx/H7xx: use native field names */
#define GD32_DMA_SET_MEMADDR(s, v)           ((s)->memory0_addr = (v))
#define GD32_DMA_SET_DATAWIDTH(s, v)         ((s)->periph_memory_width = (v))
#define GD32_DMA_SET_CIRCULAR(s, v)          ((s)->circular_mode = (v))
#endif

#endif /* _DRV_DMA_H_ */
