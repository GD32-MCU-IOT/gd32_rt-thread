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
                                                .periph     = DMA##dmax,                         \
                                                .channel    = DMA_CH##chx,                      \
                                                .rcu        = RCU_DMA##dmax,                    \
                                                .request    = (uint32_t)(reqx),                 \
                                                .irq        = DMA##dmax##_Channel##chx##_IRQn,  \
                                            }

struct dma_config
{
    uint32_t periph;
    uint32_t dma_flag;
    rcu_periph_enum rcu;
    dma_channel_enum channel;
    uint32_t request;
    IRQn_Type irq;
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

#endif /* _DRV_DMA_H_ */
