/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2024-03-19   Evlers      first implementation
 */

#ifndef __DRV_USART_V2_H__
#define __DRV_USART_V2_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "drv_dma.h"
#ifdef RT_SERIAL_USING_DMA
#include "drv_config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(RT_SERIAL_USING_DMA) && defined(RT_USING_CACHE) && \
    (defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x))
#define GD32_UART_DMA_DCACHE
#endif

/* GD32 uart driver */
struct gd32_uart
{
    /* common hardware members, same order as V1 */
    uint32_t uart_periph;
    rcu_periph_enum uart_clk;
    IRQn_Type irqn;
    char *device_name;

    struct rt_serial_device serial;

#ifdef RT_SERIAL_USING_DMA
    struct
    {
        struct dma_config rx;
        struct dma_config tx;
        rt_size_t last_index;
#ifdef GD32_UART_DMA_DCACHE
        /* framework ping buffer shares cache lines with other data, so RX DMA targets this one */
        rt_uint8_t *rx_buf;
#endif
    } dma;
#endif
    rt_uint16_t uart_dma_flag;
};

int rt_hw_usart_init(void);
void gd32_uart_gpio_init(struct gd32_uart *uart);
#ifdef __cplusplus
}
#endif

#endif /* __DRV_USART_V2_H__ */

