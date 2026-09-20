/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SOC_SERIES_GD32F10x
/* the GD32F10x firmware library names the IDLE line flag USART_FLAG_IDLEF */
#define USART_FLAG_IDLE               USART_FLAG_IDLEF
#endif


#ifdef RT_SERIAL_USING_DMA
#include "drv_dma.h"
#include "drv_config.h"
#endif

#ifdef RT_SERIAL_USING_DMA
typedef struct
{
    struct dma_config *config;
    /* setting receive len */
    rt_size_t setting_recv_len;
    /* last receive index */
    rt_size_t last_recv_index;
} gd32_uart_dma;
#endif

/* GD32 uart driver */
struct gd32_uart
{
    uint32_t uart_periph;
    rcu_periph_enum uart_clk;
    IRQn_Type irqn;
    char *device_name;
    struct rt_serial_device * serial;

#ifdef RT_SERIAL_USING_DMA
#ifdef BSP_USING_UART_TX_DMA
    struct dma_config *dma_tx;
#endif
#ifdef BSP_USING_UART_RX_DMA
    struct dma_config *dma_rx;
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x) || defined(SOC_SERIES_GD32H75E)
    /* Cache-aligned DMA buffer to avoid D-Cache coherency issues (Cortex-M7 only) */
    rt_uint8_t *dma_rx_buffer;
#endif
    /* setting receive len */
    rt_size_t setting_recv_len;
    /* last receive index */
    rt_size_t last_recv_index;
#endif
#endif
};


void gd32_uart_gpio_init(struct gd32_uart *uart);


#ifdef RT_SERIAL_USING_DMA
/* DMA RX ISR flag types */
#define UART_RX_DMA_IT_IDLE_FLAG    0x00
#define UART_RX_DMA_IT_HT_FLAG      0x01
#define UART_RX_DMA_IT_TC_FLAG      0x02
#endif

int rt_hw_usart_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_USART_H__ */

