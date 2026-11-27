/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2024-03-19   Evlers      first implementation
 */

#include "drv_usart_v2.h"

#ifdef RT_USING_SERIAL_V2

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && \
    !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7)
#error "Please define at least one UARTx"

#endif

#include <rtdevice.h>

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x) \
 || defined(SOC_SERIES_GD32W51x_F5HC) || defined(SOC_SERIES_GD32L23x) || defined(SOC_SERIES_GD32G5x3)
#define USART_DATA_TX(usartx) (&USART_TDATA(usartx))
#define USART_DATA_RX(usartx) (&USART_RDATA(usartx))
#elif defined(SOC_SERIES_GD32E51x)
/* only USART5 on E51x has separate TX/RX data registers */
#define USART_DATA_TX(usartx) (((usartx) == USART5) ? (&USART5_TDATA(usartx)) : (&USART_DATA(usartx)))
#define USART_DATA_RX(usartx) (((usartx) == USART5) ? (&USART5_RDATA(usartx)) : (&USART_DATA(usartx)))
#else
#define USART_DATA_TX(usartx) (&USART_DATA(usartx))
#define USART_DATA_RX(usartx) (&USART_DATA(usartx))
#endif

#ifndef USART_TRANSMIT_DMA_ENABLE
#define USART_TRANSMIT_DMA_ENABLE   USART_DENT_ENABLE
#endif
#ifndef USART_TRANSMIT_DMA_DISABLE
#define USART_TRANSMIT_DMA_DISABLE  USART_DENT_DISABLE
#endif
#ifndef USART_RECEIVE_DMA_ENABLE
#define USART_RECEIVE_DMA_ENABLE    USART_DENR_ENABLE
#endif
#ifndef USART_RECEIVE_DMA_DISABLE
#define USART_RECEIVE_DMA_DISABLE   USART_DENR_DISABLE
#endif

#ifdef BSP_UART_POLL_TX_TIMEOUT_MS
#define GD32_POLL_TX_TIMEOUT_MS BSP_UART_POLL_TX_TIMEOUT_MS
#else
#define GD32_POLL_TX_TIMEOUT_MS 1000
#endif

/* DMA TX threshold: transfers smaller than this use polling instead of DMA */
#ifdef BSP_UART_DMA_TX_THRESHOLD
#define GD32_DMA_TX_THRESHOLD BSP_UART_DMA_TX_THRESHOLD
#else
#define GD32_DMA_TX_THRESHOLD 8
#endif

/* RCU_DMAMUX is an enum, not a macro; L23x has no separate DMAMUX clock */
#if defined(GD32_DMA_USING_DMAMUX) && !defined(SOC_SERIES_GD32L23x)
#define GD32_DMAMUX_CLOCK_ENABLE()  rcu_periph_clock_enable(RCU_DMAMUX)
#else
#define GD32_DMAMUX_CLOCK_ENABLE()
#endif

enum {
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
#ifdef BSP_USING_UART4
    UART4_INDEX,
#endif
#ifdef BSP_USING_UART5
    UART5_INDEX,
#endif
#ifdef BSP_USING_UART6
    UART6_INDEX,
#endif
#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif
};

static struct gd32_uart uart_obj[] = {
    #ifdef BSP_USING_UART0
    {
        USART0,                                 /* uart peripheral index */
        RCU_USART0,                             /* uart periph clock */
        USART0_IRQn,                            /* uart iqrn */
        "uart0",
#ifdef BSP_UART0_RX_USING_DMA
        .dma.rx = UART0_DMA_RX_CONFIG,
#endif
#ifdef BSP_UART0_TX_USING_DMA
        .dma.tx = UART0_DMA_TX_CONFIG,
#endif
    },
    #endif

    #ifdef BSP_USING_UART1
    {
        USART1,                                 /* uart peripheral index */
        RCU_USART1,                             /* uart periph clock */
        USART1_IRQn,                            /* uart iqrn */
        "uart1",
#ifdef BSP_UART1_RX_USING_DMA
        .dma.rx = UART1_DMA_RX_CONFIG,
#endif
#ifdef BSP_UART1_TX_USING_DMA
        .dma.tx = UART1_DMA_TX_CONFIG,
#endif
    },
    #endif

    #ifdef BSP_USING_UART2
    {
        USART2,                                 /* uart peripheral index */
        RCU_USART2,                             /* uart periph clock */
        USART2_IRQn,                            /* uart iqrn */
        "uart2",
#ifdef BSP_UART2_RX_USING_DMA
        .dma.rx = UART2_DMA_RX_CONFIG,
#endif
#ifdef BSP_UART2_TX_USING_DMA
        .dma.tx = UART2_DMA_TX_CONFIG,
#endif
    },
    #endif

    #ifdef BSP_USING_UART3
    {
        UART3,                                  /* uart peripheral index */
        RCU_UART3,                              /* uart periph clock */
        UART3_IRQn,                             /* uart iqrn */
        "uart3",
#ifdef BSP_UART3_RX_USING_DMA
        .dma.rx = UART3_DMA_RX_CONFIG,
#endif
#ifdef BSP_UART3_TX_USING_DMA
        .dma.tx = UART3_DMA_TX_CONFIG,
#endif
    },
    #endif

    #ifdef BSP_USING_UART4
    {
        UART4,                                  /* uart peripheral index */
        RCU_UART4,                              /* uart periph clock */
        UART4_IRQn,                             /* uart iqrn */
        "uart4",
#ifdef BSP_UART4_RX_USING_DMA
        .dma.rx = UART4_DMA_RX_CONFIG,
#endif
#ifdef BSP_UART4_TX_USING_DMA
        .dma.tx = UART4_DMA_TX_CONFIG,
#endif
    },
    #endif

    #ifdef BSP_USING_UART5
    {
        USART5,                                 /* uart peripheral index */
        RCU_USART5,                             /* uart periph clock */
        USART5_IRQn,                            /* uart iqrn */
        "uart5",
#ifdef BSP_UART5_RX_USING_DMA
        .dma.rx = UART5_DMA_RX_CONFIG,
#endif
#ifdef BSP_UART5_TX_USING_DMA
        .dma.tx = UART5_DMA_TX_CONFIG,
#endif
    },
    #endif

    #ifdef BSP_USING_UART6
    {
        UART6,                                  /* uart peripheral index */
        RCU_UART6,                              /* uart periph clock */
        UART6_IRQn,                             /* uart iqrn */
        "uart6",
#ifdef BSP_UART6_RX_USING_DMA
        .dma.rx = UART6_DMA_RX_CONFIG,
#endif
#ifdef BSP_UART6_TX_USING_DMA
        .dma.tx = UART6_DMA_TX_CONFIG,
#endif
    },
    #endif

    #ifdef BSP_USING_UART7
    {
        UART7,                                  /* uart peripheral index */
        RCU_UART7,                              /* uart periph clock */
        UART7_IRQn,                             /* uart iqrn */
        "uart7",
#ifdef BSP_UART7_RX_USING_DMA
        .dma.rx = UART7_DMA_RX_CONFIG,
#endif
#ifdef BSP_UART7_TX_USING_DMA
        .dma.tx = UART7_DMA_TX_CONFIG,
#endif
    },
    #endif
};

#ifdef RT_SERIAL_USING_DMA
static void dma_recv_isr (struct rt_serial_device *serial)
{
    struct gd32_uart *uart;
    rt_size_t recv_len, counter;
    rt_base_t level;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    level = rt_hw_interrupt_disable();
    counter = gd32_dma_transfer_number_get(uart->dma.rx.periph, uart->dma.rx.channel);
    if (counter <= uart->dma.last_index)
    {
        recv_len = uart->dma.last_index - counter;
    }
    else
    {
        recv_len = serial->config.dma_ping_bufsz + uart->dma.last_index - counter;
    }
#ifdef GD32_UART_DMA_DCACHE
    if (recv_len)
    {
        rt_size_t bufsz = serial->config.dma_ping_bufsz;
        rt_size_t start = (bufsz - uart->dma.last_index) % bufsz;
        rt_size_t first = (start + recv_len > bufsz) ? (bufsz - start) : recv_len;
        rt_uint8_t *ping = RT_NULL;

        /* DMA fills the private rx_buf; copy the new bytes into the framework ping buffer */
        rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_GET_DMA_PING_BUF, (void *)&ping);
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, uart->dma.rx_buf, RT_ALIGN(bufsz, 32));
        rt_memcpy(ping + start, uart->dma.rx_buf + start, first);
        rt_memcpy(ping, uart->dma.rx_buf, recv_len - first);
    }
#endif
    uart->dma.last_index = counter;
    rt_hw_interrupt_enable(level);

    if (recv_len)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
}
#endif

static void usart_isr (struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_RBNE) != RESET)
    {
        rt_uint8_t chr = usart_data_receive(uart->uart_periph);
        rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_PUTC, (void *)&chr);
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    else if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_TBE) != RESET)
    {
        rt_uint8_t put_char = 0;
        if (rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_GETC, (void *)&put_char) == RT_EOK)
        {
            usart_data_transmit(uart->uart_periph, put_char);
        }
        else
        {
            usart_interrupt_disable(uart->uart_periph, USART_INT_TBE);
            usart_interrupt_enable(uart->uart_periph, USART_INT_TC);
        }
    }
    else if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_TC) != RESET)
    {
        usart_interrupt_disable(uart->uart_periph, USART_INT_TC);

        if (serial->parent.open_flag & RT_DEVICE_FLAG_DMA_TX)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
        }
        else
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
        }

        usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_TC);
    }

#ifdef RT_SERIAL_USING_DMA
    else if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_IDLE) != RESET)
    {
        volatile uint8_t idle_clear_dummy = (uint8_t)usart_data_receive(uart->uart_periph);
        RT_UNUSED(idle_clear_dummy);
        dma_recv_isr(serial);
        usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_IDLE);
    }
#endif
    else
    {
        if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_ERR_ORERR) != RESET)
        {
            usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_ERR_ORERR);
        }

        if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_ERR_NERR) != RESET)
        {
            usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_ERR_NERR);
        }

        if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_ERR_FERR) != RESET)
        {
            usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_ERR_FERR);
        }

        if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_RBNE_ORERR) != RESET)
        {
            usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_RBNE_ORERR);
        }

        if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_PERR) != RESET)
        {
            usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_PERR);
        }

        if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_CTS) != RESET)
        {
            usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_CTS);
        }

        if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_LBD) != RESET)
        {
            usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_LBD);
        }

        if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_EB) != RESET)
        {
            usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_EB);
        }

        if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_RT) != RESET)
        {
            usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_RT);
        }
    }
}

#if defined(BSP_UART0_RX_USING_DMA) || \
    defined(BSP_UART1_RX_USING_DMA) || \
    defined(BSP_UART2_RX_USING_DMA) || \
    defined(BSP_UART3_RX_USING_DMA) || \
    defined(BSP_UART4_RX_USING_DMA) || \
    defined(BSP_UART5_RX_USING_DMA) || \
    defined(BSP_UART6_RX_USING_DMA) || \
    defined(BSP_UART7_RX_USING_DMA)

static void dma_rx_isr (struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    if ((gd32_dma_interrupt_flag_get(uart->dma.rx.periph, uart->dma.rx.channel, DMA_INT_FLAG_HTF) != RESET) ||
        (gd32_dma_interrupt_flag_get(uart->dma.rx.periph, uart->dma.rx.channel, DMA_INT_FLAG_FTF) != RESET))
    {
        dma_recv_isr(serial);

        /* clear dma flag */
        gd32_dma_interrupt_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_INT_FLAG_HTF);
        gd32_dma_interrupt_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_INT_FLAG_FTF);
    }
}

#endif

#if defined(BSP_UART0_TX_USING_DMA) || \
    defined(BSP_UART1_TX_USING_DMA) || \
    defined(BSP_UART2_TX_USING_DMA) || \
    defined(BSP_UART3_TX_USING_DMA) || \
    defined(BSP_UART4_TX_USING_DMA) || \
    defined(BSP_UART5_TX_USING_DMA) || \
    defined(BSP_UART6_TX_USING_DMA) || \
    defined(BSP_UART7_TX_USING_DMA)
static void dma_tx_isr (struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);
    #if defined SOC_SERIES_GD32E23x
    {
        rt_size_t trans_total_index;

        /* clear dma flag */
        gd32_dma_interrupt_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_INT_FLAG_FTF);

        /* disable dma tx channel */
        gd32_dma_channel_disable(uart->dma.tx.periph, uart->dma.tx.channel);

        trans_total_index = gd32_dma_transfer_number_get(uart->dma.tx.periph, uart->dma.tx.channel);

        if (trans_total_index == 0)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
        }
    }
    #else
    if (gd32_dma_flag_get(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_FTF) != RESET)
    {
        /* clear dma flag */
        gd32_dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_FTF);

        /* disable dma tx channel */
        gd32_dma_channel_disable(uart->dma.tx.periph, uart->dma.tx.channel);
    }
    #endif
}
#endif

#if defined(BSP_USING_UART0)
void USART0_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART0_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
void USART1_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART1_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void USART2_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART2_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
void UART3_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART3_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
void UART4_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART4_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
void USART5_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART5_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
void UART6_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART6_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
void UART7_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART7_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART7 */
#if defined SOC_SERIES_GD32E23x
#if defined BSP_UART0_RX_USING_DMA || defined BSP_UART0_TX_USING_DMA
void DMA_Channel1_2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (gd32_dma_interrupt_flag_get(DMA, DMA_CH1, DMA_INT_FLAG_FTF) != RESET)
    {
        gd32_dma_interrupt_flag_clear(DMA, DMA_CH1, DMA_INT_FLAG_G);
        dma_tx_isr(&uart_obj[UART0_INDEX].serial);
    }

    if (gd32_dma_interrupt_flag_get(DMA, DMA_CH2, DMA_INT_FLAG_HTF) != RESET)
    {
        gd32_dma_interrupt_flag_clear(DMA, DMA_CH2, DMA_INT_FLAG_HTF);
        dma_recv_isr(&uart_obj[UART0_INDEX].serial);
    }
    else if (gd32_dma_interrupt_flag_get(DMA, DMA_CH2, DMA_INT_FLAG_FTF) != RESET)
    {
        gd32_dma_interrupt_flag_clear(DMA, DMA_CH2, DMA_INT_FLAG_FTF);
        dma_recv_isr(&uart_obj[UART0_INDEX].serial);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#else
#ifdef BSP_UART0_RX_USING_DMA
void UART0_DMA_RX_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART0_INDEX].serial);
}
#endif

#ifdef BSP_UART0_TX_USING_DMA
void UART0_DMA_TX_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART0_INDEX].serial);
}
#endif
#endif

#if defined SOC_SERIES_GD32E23x

#if defined BSP_UART1_RX_USING_DMA || defined BSP_UART1_TX_USING_DMA
void DMA_Channel3_4_IRQHandler(void)
{
    rt_interrupt_enter();

    if (gd32_dma_interrupt_flag_get(DMA, DMA_CH3, DMA_INT_FLAG_FTF) != RESET)
    {
        gd32_dma_interrupt_flag_clear(DMA, DMA_CH3, DMA_INT_FLAG_G);
        dma_tx_isr(&uart_obj[UART1_INDEX].serial);
    }

    if (gd32_dma_interrupt_flag_get(DMA, DMA_CH4, DMA_INT_FLAG_HTF) != RESET)
    {
        gd32_dma_interrupt_flag_clear(DMA, DMA_CH4, DMA_INT_FLAG_HTF);
        dma_recv_isr(&uart_obj[UART1_INDEX].serial);
    }

    if (gd32_dma_interrupt_flag_get(DMA, DMA_CH4, DMA_INT_FLAG_FTF) != RESET)
    {
        gd32_dma_interrupt_flag_clear(DMA, DMA_CH4, DMA_INT_FLAG_FTF);
        dma_recv_isr(&uart_obj[UART1_INDEX].serial);
    }

    rt_interrupt_leave();
}
#endif
#else
#ifdef BSP_UART1_RX_USING_DMA
void UART1_DMA_RX_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART1_INDEX].serial);
}
#endif

#ifdef BSP_UART1_TX_USING_DMA
void UART1_DMA_TX_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART1_INDEX].serial);
}
#endif
#endif

#ifdef BSP_UART2_RX_USING_DMA
void UART2_DMA_RX_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART2_INDEX].serial);
}
#endif

#ifdef BSP_UART2_TX_USING_DMA
void UART2_DMA_TX_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART2_INDEX].serial);
}
#endif

#ifdef BSP_UART3_RX_USING_DMA
void UART3_DMA_RX_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART3_INDEX].serial);
}
#endif

#ifdef BSP_UART3_TX_USING_DMA
void UART3_DMA_TX_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART3_INDEX].serial);
}
#endif

#ifdef BSP_UART4_RX_USING_DMA
void UART4_DMA_RX_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART4_INDEX].serial);
}
#endif

#ifdef BSP_UART4_TX_USING_DMA
void UART4_DMA_TX_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART4_INDEX].serial);
}
#endif

#ifdef BSP_UART5_RX_USING_DMA
void UART5_DMA_RX_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART5_INDEX].serial);
}
#endif

#ifdef BSP_UART5_TX_USING_DMA
void UART5_DMA_TX_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART5_INDEX].serial);
}
#endif

#ifdef BSP_UART6_RX_USING_DMA
void UART6_DMA_RX_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART6_INDEX].serial);
}
#endif

#ifdef BSP_UART6_TX_USING_DMA
void UART6_DMA_TX_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART6_INDEX].serial);
}
#endif

#ifdef BSP_UART7_RX_USING_DMA
void UART7_DMA_RX_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART7_INDEX].serial);
}
#endif

#ifdef BSP_UART7_TX_USING_DMA
void UART7_DMA_TX_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART7_INDEX].serial);
}
#endif

#warning "gd32_uart_gpio_init should be defined in board_msd_init.c"
rt_weak void gd32_uart_gpio_init(struct gd32_uart *uart)
{
}

/**
  * @brief  uart configure
  * @param  serial, cfg
  * @retval None
  */
static rt_err_t gd32_uart_configure (struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    gd32_uart_gpio_init(uart);

    /* H7/H75E ignore BAUD and frame format writes while UEN is set */
    usart_disable(uart->uart_periph);
    usart_baudrate_set(uart->uart_periph, cfg->baud_rate);

    switch (cfg->data_bits)
    {
    case DATA_BITS_9:
        usart_word_length_set(uart->uart_periph, USART_WL_9BIT);
        break;

    default:
        usart_word_length_set(uart->uart_periph, USART_WL_8BIT);
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        usart_stop_bit_set(uart->uart_periph, USART_STB_2BIT);
        break;
    default:
        usart_stop_bit_set(uart->uart_periph, USART_STB_1BIT);
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        usart_parity_config(uart->uart_periph, USART_PM_ODD);
        break;
    case PARITY_EVEN:
        usart_parity_config(uart->uart_periph, USART_PM_EVEN);
        break;
    default:
        usart_parity_config(uart->uart_periph, USART_PM_NONE);
        break;
    }

    usart_receive_config(uart->uart_periph, USART_RECEIVE_ENABLE);
    usart_transmit_config(uart->uart_periph, USART_TRANSMIT_ENABLE);
    usart_enable(uart->uart_periph);

    return RT_EOK;
}

#ifdef RT_SERIAL_USING_DMA
static void _uart_dma_receive (struct gd32_uart *uart, rt_uint8_t *buffer, rt_uint32_t size)
{
    /* clear all the interrupt flags */

    #if defined SOC_SERIES_GD32E23x
    gd32_dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_G);
    gd32_dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_FTF);
    gd32_dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_HTF);
    gd32_dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_ERR);
    gd32_dma_channel_disable(uart->dma.rx.periph, uart->dma.rx.channel);
    gd32_dma_deinit(uart->dma.rx.periph, uart->dma.rx.channel);

    /* configure receive DMA */
    rcu_periph_clock_enable(uart->dma.rx.rcu);
    GD32_DMAMUX_CLOCK_ENABLE();
    gd32_dma_deinit(uart->dma.rx.periph, uart->dma.rx.channel);

    gd32_dma_single_data_parameter_struct dma_init_struct;

    gd32_dma_single_data_para_struct_init(&dma_init_struct);
    dma_init_struct.periph_addr = (uint32_t)&USART_RDATA(uart->uart_periph);
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
    dma_init_struct.number = size;
    dma_init_struct.priority = DMA_PRIORITY_HIGH;
    GD32_DMA_SET_MEMADDR(&dma_init_struct, (uint32_t)buffer);
    GD32_DMA_SET_DATAWIDTH(&dma_init_struct, DMA_PERIPH_WIDTH_8BIT);
    gd32_dma_single_data_mode_init(uart->dma.rx.periph, uart->dma.rx.channel, &dma_init_struct);

    /* enable transmit complete interrupt */
    nvic_irq_enable(uart->dma.rx.irq, 2);
    gd32_dma_interrupt_enable(uart->dma.rx.periph, uart->dma.rx.channel, DMA_CHXCTL_HTFIE);
    gd32_dma_interrupt_enable(uart->dma.rx.periph, uart->dma.rx.channel, DMA_CHXCTL_FTFIE);

    /* enable circular mode */
    gd32_dma_circulation_enable(uart->dma.rx.periph, uart->dma.rx.channel);

    /* enable dma channel */
    gd32_dma_channel_enable(uart->dma.rx.periph, uart->dma.rx.channel);

    /* enable usart idle interrupt */
    usart_interrupt_enable(uart->uart_periph, USART_INT_IDLE);

    /* enable dma receive */
    usart_dma_receive_config(uart->uart_periph, USART_DENR_ENABLE);
    #else
    gd32_dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_FEE);
    gd32_dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_SDE);
    gd32_dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_TAE);
    gd32_dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_HTF);
    gd32_dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_FTF);
    gd32_dma_channel_disable(uart->dma.rx.periph, uart->dma.rx.channel);
    gd32_dma_deinit(uart->dma.rx.periph, uart->dma.rx.channel);

    /* configure receive DMA */
    rcu_periph_clock_enable(uart->dma.rx.rcu);
    GD32_DMAMUX_CLOCK_ENABLE();
    gd32_dma_deinit(uart->dma.rx.periph, uart->dma.rx.channel);

    gd32_dma_single_data_parameter_struct dma_init_struct;

    gd32_dma_single_data_para_struct_init(&dma_init_struct);
    dma_init_struct.number              = size;
    dma_init_struct.periph_addr         = (uint32_t)USART_DATA_RX(uart->uart_periph);
    dma_init_struct.periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_inc          = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.direction           = DMA_PERIPH_TO_MEMORY;
    dma_init_struct.priority            = DMA_PRIORITY_HIGH;
    GD32_DMA_SET_MEMADDR(&dma_init_struct, (uint32_t)buffer);
    GD32_DMA_SET_DATAWIDTH(&dma_init_struct, DMA_PERIPH_WIDTH_8BIT);
    gd32_dma_request_config(&dma_init_struct, &uart->dma.rx);
    gd32_dma_single_data_mode_init(uart->dma.rx.periph, uart->dma.rx.channel, &dma_init_struct);
    gd32_dma_subperiph_config(uart->dma.rx.periph, uart->dma.rx.channel, &uart->dma.rx);
    gd32_dma_circulation_enable(uart->dma.rx.periph, uart->dma.rx.channel);

    /* enable transmit complete interrupt */
    nvic_irq_enable(uart->dma.rx.irq, 2, 0);
    gd32_dma_interrupt_enable(uart->dma.rx.periph, uart->dma.rx.channel, DMA_CHXCTL_HTFIE);
    gd32_dma_interrupt_enable(uart->dma.rx.periph, uart->dma.rx.channel, DMA_CHXCTL_FTFIE);

    /* enable dma channel */
    gd32_dma_channel_enable(uart->dma.rx.periph, uart->dma.rx.channel);

    /* enable usart idle interrupt */
    usart_interrupt_enable(uart->uart_periph, USART_INT_IDLE);

    /* enable dma receive */
    usart_dma_receive_config(uart->uart_periph, USART_RECEIVE_DMA_ENABLE);
    #endif
}

static void _uart_dma_transmit (struct gd32_uart *uart, rt_uint8_t *buffer, rt_uint32_t size)
{
    #if defined SOC_SERIES_GD32E23x
    DMA_CHMADDR(uart->dma.tx.channel) = (uint32_t)buffer;
    DMA_CHCNT(uart->dma.tx.channel) = size;

    usart_dma_transmit_config(uart->uart_periph, USART_DENT_ENABLE);

    gd32_dma_channel_enable(uart->dma.tx.periph, uart->dma.tx.channel);
    #else
#ifdef GD32_UART_DMA_DCACHE
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, buffer, size);
#endif
    /* Set the data length and data pointer */
    gd32_dma_memory_address_config(uart->dma.tx.periph, uart->dma.tx.channel, DMA_MEMORY_0, (uint32_t)buffer);
    gd32_dma_transfer_number_config(uart->dma.tx.periph, uart->dma.tx.channel, size);

    /* enable dma transmit */
    usart_dma_transmit_config(uart->uart_periph, USART_TRANSMIT_DMA_ENABLE);

    /* DMA TX done is reported by USART TC interrupt */
    usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_TC);
    usart_interrupt_enable(uart->uart_periph, USART_INT_TC);

    /* enable dma channel */
    gd32_dma_channel_enable(uart->dma.tx.periph, uart->dma.tx.channel);
    #endif
}

static void gd32_dma_config (struct rt_serial_device *serial, rt_ubase_t flag)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    RT_ASSERT(flag == RT_DEVICE_FLAG_DMA_TX || flag == RT_DEVICE_FLAG_DMA_RX);

    /* enable tx dma */
    if (flag == RT_DEVICE_FLAG_DMA_TX)
    {
        /* DMA TX completion may be delivered by USART TC interrupt. */
        NVIC_EnableIRQ(uart->irqn);

        #if defined SOC_SERIES_GD32E23x
        gd32_dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_G);
        gd32_dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_FTF);
        gd32_dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_HTF);
        gd32_dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_ERR);
        gd32_dma_channel_disable(uart->dma.tx.periph, uart->dma.tx.channel);
        gd32_dma_deinit(uart->dma.tx.periph, uart->dma.tx.channel);
        /* configure receive DMA */
        rcu_periph_clock_enable(uart->dma.tx.rcu);
        GD32_DMAMUX_CLOCK_ENABLE();
        gd32_dma_deinit(uart->dma.tx.periph, uart->dma.tx.channel);

        gd32_dma_single_data_parameter_struct dma_init_struct;

        gd32_dma_single_data_para_struct_init(&dma_init_struct);
        dma_init_struct.periph_addr = (uint32_t)&USART_TDATA(uart->uart_periph);
        dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
        dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
        dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
        dma_init_struct.priority = DMA_PRIORITY_HIGH;
        GD32_DMA_SET_DATAWIDTH(&dma_init_struct, DMA_PERIPH_WIDTH_8BIT);

        gd32_dma_single_data_mode_init(uart->dma.tx.periph, uart->dma.tx.channel, &dma_init_struct);

        /* enable tx dma interrupt */
        nvic_irq_enable(uart->dma.tx.irq, 2);

        /* enable transmit complete interrupt */
        gd32_dma_interrupt_enable(uart->dma.tx.periph, uart->dma.tx.channel, DMA_INT_FTF);
        #else
        /* clear all the interrupt flags */
        gd32_dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_FEE);
        gd32_dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_SDE);
        gd32_dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_TAE);
        gd32_dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_HTF);
        gd32_dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_FTF);
        gd32_dma_channel_disable(uart->dma.tx.periph, uart->dma.tx.channel);
        gd32_dma_deinit(uart->dma.tx.periph, uart->dma.tx.channel);

        /* configure receive DMA */
        rcu_periph_clock_enable(uart->dma.tx.rcu);
        GD32_DMAMUX_CLOCK_ENABLE();
        gd32_dma_deinit(uart->dma.tx.periph, uart->dma.tx.channel);

        gd32_dma_single_data_parameter_struct dma_init_struct;

        gd32_dma_single_data_para_struct_init(&dma_init_struct);
        dma_init_struct.periph_addr         = (uint32_t)USART_DATA_TX(uart->uart_periph);
        dma_init_struct.periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
        dma_init_struct.memory_inc          = DMA_MEMORY_INCREASE_ENABLE;
        dma_init_struct.direction           = DMA_MEMORY_TO_PERIPH;
        dma_init_struct.priority            = DMA_PRIORITY_HIGH;
        GD32_DMA_SET_DATAWIDTH(&dma_init_struct, DMA_PERIPH_WIDTH_8BIT);
        gd32_dma_request_config(&dma_init_struct, &uart->dma.tx);
        gd32_dma_single_data_mode_init(uart->dma.tx.periph, uart->dma.tx.channel, &dma_init_struct);
        gd32_dma_subperiph_config(uart->dma.tx.periph, uart->dma.tx.channel, &uart->dma.tx);
        gd32_dma_circulation_disable(uart->dma.tx.periph, uart->dma.tx.channel);

        /* enable tx dma interrupt */
        nvic_irq_enable(uart->dma.tx.irq, 2, 0);

        /* enable transmit complete interrupt */
        gd32_dma_interrupt_enable(uart->dma.tx.periph, uart->dma.tx.channel, DMA_CHXCTL_FTFIE);
        #endif
    }

    /* enable rx dma */
    if (flag == RT_DEVICE_FLAG_DMA_RX)
    {
        /* RX DMA relies on USART IDLE interrupt for data flush. */
        NVIC_EnableIRQ(uart->irqn);

        rt_uint8_t *ptr = NULL;
        rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_GET_DMA_PING_BUF, (void *)&ptr);

#ifdef GD32_UART_DMA_DCACHE
        if (uart->dma.rx_buf == RT_NULL)
        {
            uart->dma.rx_buf = rt_malloc_align(RT_ALIGN(serial->config.dma_ping_bufsz, 32), 32);
            RT_ASSERT(uart->dma.rx_buf != RT_NULL);
        }
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH | RT_HW_CACHE_INVALIDATE, uart->dma.rx_buf,
                             RT_ALIGN(serial->config.dma_ping_bufsz, 32));
        ptr = uart->dma.rx_buf;
#endif

        /* must be synced before _uart_dma_receive() enables IDLE, a pending IDLE fires at once */
        uart->dma.last_index = serial->config.dma_ping_bufsz;
        /* start dma transfer */
        _uart_dma_receive(uart, ptr, serial->config.dma_ping_bufsz);
    }
}

#endif

/**
  * @brief  uart control
  * @param  serial, arg
  * @retval None
  */
static rt_err_t gd32_uart_control (struct rt_serial_device *serial, int cmd, void *arg)
{
    struct gd32_uart *uart;

    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    if (ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
        if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_RX)
            ctrl_arg = RT_DEVICE_FLAG_DMA_RX;
        else
            ctrl_arg = RT_DEVICE_FLAG_INT_RX;
    }
    else if (ctrl_arg & (RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING))
    {
        if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
            ctrl_arg = RT_DEVICE_FLAG_DMA_TX;
        else
            ctrl_arg = RT_DEVICE_FLAG_INT_TX;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irqn);

        /* disable interrupt */
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
        {
            usart_interrupt_disable(uart->uart_periph, USART_INT_RBNE);
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
        {
            usart_interrupt_disable(uart->uart_periph, USART_INT_TBE);
        }

#ifdef RT_SERIAL_USING_DMA
        /* disable DMA */
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX)
        {
            usart_interrupt_disable(uart->uart_periph, USART_INT_RBNE);
            usart_interrupt_disable(uart->uart_periph, USART_INT_IDLE);
            NVIC_DisableIRQ(uart->dma.rx.irq);
            gd32_dma_channel_disable(uart->dma.rx.periph, uart->dma.rx.channel);
            usart_dma_receive_config(uart->uart_periph, USART_RECEIVE_DMA_DISABLE);
            gd32_dma_deinit(uart->dma.rx.periph, uart->dma.rx.channel);
            serial->parent.open_flag &= ~RT_DEVICE_FLAG_DMA_RX;
#ifdef GD32_UART_DMA_DCACHE
            if (uart->dma.rx_buf != RT_NULL)
            {
                rt_free_align(uart->dma.rx_buf);
                uart->dma.rx_buf = RT_NULL;
            }
#endif
        }
        else if(ctrl_arg == RT_DEVICE_FLAG_DMA_TX)
        {
            usart_interrupt_disable(uart->uart_periph, USART_INT_TBE);
            usart_interrupt_disable(uart->uart_periph, USART_INT_TC);
            NVIC_DisableIRQ(uart->dma.tx.irq);
            gd32_dma_channel_disable(uart->dma.tx.periph, uart->dma.tx.channel);
            usart_dma_transmit_config(uart->uart_periph, USART_TRANSMIT_DMA_DISABLE);
            gd32_dma_deinit(uart->dma.tx.periph, uart->dma.tx.channel);
            serial->parent.open_flag &= ~RT_DEVICE_FLAG_DMA_TX;
        }
#endif
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irqn);

        /* enable interrupt */
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
        {
            usart_interrupt_enable(uart->uart_periph, USART_INT_RBNE);
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
        {
            usart_interrupt_enable(uart->uart_periph, USART_INT_TBE);
        }
        break;

    case RT_DEVICE_CTRL_CONFIG:
        if(ctrl_arg & (RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX))
        {
#ifdef RT_SERIAL_USING_DMA
            if (ctrl_arg & RT_DEVICE_FLAG_DMA_RX)
            {
                gd32_dma_config(serial, RT_DEVICE_FLAG_DMA_RX);
                serial->parent.open_flag |= RT_DEVICE_FLAG_DMA_RX;
            }
            if (ctrl_arg & RT_DEVICE_FLAG_DMA_TX)
            {
                gd32_dma_config(serial, RT_DEVICE_FLAG_DMA_TX);
                serial->parent.open_flag |= RT_DEVICE_FLAG_DMA_TX;
            }
#endif
        }
        else
        {
            gd32_uart_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)ctrl_arg);
        }
        break;

    case RT_DEVICE_CHECK_OPTMODE:
        if(ctrl_arg & RT_DEVICE_FLAG_DMA_TX)
            return RT_SERIAL_TX_BLOCKING_NO_BUFFER;
        else
            return RT_SERIAL_TX_BLOCKING_BUFFER;

    case RT_DEVICE_CTRL_CLOSE:
        usart_deinit(uart->uart_periph);
        break;
    }

    return RT_EOK;
}

/**
  * @brief  uart put char
  * @param  serial, ch
  * @retval None
  */
static int gd32_uart_putc (struct rt_serial_device *serial, char ch)
{
    struct gd32_uart *uart;
    rt_tick_t start_tick;
    rt_tick_t timeout_ticks = rt_tick_from_millisecond(GD32_POLL_TX_TIMEOUT_MS);

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    usart_data_transmit(uart->uart_periph, ch);
    start_tick = rt_tick_get();
    while (usart_flag_get(uart->uart_periph, USART_FLAG_TBE) == RESET)
    {
        if ((rt_tick_get() - start_tick) > timeout_ticks)
        {
            return -RT_ETIMEOUT;
        }
    }

    return RT_EOK;
}

/**
  * @brief  uart get char
  * @param  serial
  * @retval None
  */
static int gd32_uart_getc (struct rt_serial_device *serial)
{
    int ch;
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    ch = -1;
    if (usart_flag_get(uart->uart_periph, USART_FLAG_RBNE) != RESET)
        ch = usart_data_receive(uart->uart_periph);
    return ch;
}

static rt_ssize_t gd32_transmit (struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, rt_uint32_t tx_flag)
{
    struct gd32_uart *uart;

    RT_ASSERT(buf != RT_NULL);
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    if (size == 0)
    {
        return 0;
    }

    if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
#ifdef RT_SERIAL_USING_DMA
        if (size < GD32_DMA_TX_THRESHOLD)
        {
            rt_size_t i;
            int ret;
            rt_tick_t start_tick;
            rt_tick_t timeout_ticks = rt_tick_from_millisecond(GD32_POLL_TX_TIMEOUT_MS);

            for (i = 0; i < size; i++)
            {
                ret = gd32_uart_putc(serial, buf[i]);
                if (ret != RT_EOK)
                {
                    return ret;
                }
            }

            start_tick = rt_tick_get();
            while (usart_flag_get(uart->uart_periph, USART_FLAG_TC) == RESET)
            {
                if ((rt_tick_get() - start_tick) > timeout_ticks)
                {
                    return -RT_ETIMEOUT;
                }
            }

            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
            return size;
        }

        _uart_dma_transmit(uart, buf, size);
        return size;
#endif
    }

    gd32_uart_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)tx_flag);
    return size;
}

static const struct rt_uart_ops gd32_uart_ops =
{
    .configure = gd32_uart_configure,
    .control = gd32_uart_control,
    .putc = gd32_uart_putc,
    .getc = gd32_uart_getc,
    .transmit = gd32_transmit,
};

static void gd32_uart_get_config (void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    uart_obj[UART0_INDEX].uart_dma_flag = 0;
    uart_obj[UART0_INDEX].serial.config = config;
    uart_obj[UART0_INDEX].serial.config.rx_bufsz = BSP_UART0_RX_BUFSIZE;
    uart_obj[UART0_INDEX].serial.config.tx_bufsz = BSP_UART0_TX_BUFSIZE;
#ifdef BSP_UART0_RX_USING_DMA
    uart_obj[UART0_INDEX].serial.config.dma_ping_bufsz = BSP_UART0_DMA_PING_BUFSIZE;
    uart_obj[UART0_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART0_TX_USING_DMA
    uart_obj[UART0_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].uart_dma_flag = 0;
    uart_obj[UART1_INDEX].serial.config = config;
    uart_obj[UART1_INDEX].serial.config.rx_bufsz = BSP_UART1_RX_BUFSIZE;
    uart_obj[UART1_INDEX].serial.config.tx_bufsz = BSP_UART1_TX_BUFSIZE;
#ifdef BSP_UART1_RX_USING_DMA
    uart_obj[UART1_INDEX].serial.config.dma_ping_bufsz = BSP_UART1_DMA_PING_BUFSIZE;
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART1_TX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART2
    uart_obj[UART2_INDEX].uart_dma_flag = 0;
    uart_obj[UART2_INDEX].serial.config = config;
    uart_obj[UART2_INDEX].serial.config.rx_bufsz = BSP_UART2_RX_BUFSIZE;
    uart_obj[UART2_INDEX].serial.config.tx_bufsz = BSP_UART2_TX_BUFSIZE;
#ifdef BSP_UART2_RX_USING_DMA
    uart_obj[UART2_INDEX].serial.config.dma_ping_bufsz = BSP_UART2_DMA_PING_BUFSIZE;
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART2_TX_USING_DMA
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART3
    uart_obj[UART3_INDEX].uart_dma_flag = 0;
    uart_obj[UART3_INDEX].serial.config = config;
    uart_obj[UART3_INDEX].serial.config.rx_bufsz = BSP_UART3_RX_BUFSIZE;
    uart_obj[UART3_INDEX].serial.config.tx_bufsz = BSP_UART3_TX_BUFSIZE;
#ifdef BSP_UART3_RX_USING_DMA
    uart_obj[UART3_INDEX].serial.config.dma_ping_bufsz = BSP_UART3_DMA_PING_BUFSIZE;
    uart_obj[UART3_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART3_TX_USING_DMA
    uart_obj[UART3_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART4
    uart_obj[UART4_INDEX].uart_dma_flag = 0;
    uart_obj[UART4_INDEX].serial.config = config;
    uart_obj[UART4_INDEX].serial.config.rx_bufsz = BSP_UART4_RX_BUFSIZE;
    uart_obj[UART4_INDEX].serial.config.tx_bufsz = BSP_UART4_TX_BUFSIZE;
#ifdef BSP_UART4_RX_USING_DMA
    uart_obj[UART4_INDEX].serial.config.dma_ping_bufsz = BSP_UART4_DMA_PING_BUFSIZE;
    uart_obj[UART4_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART4_TX_USING_DMA
    uart_obj[UART4_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART5
    uart_obj[UART5_INDEX].uart_dma_flag = 0;
    uart_obj[UART5_INDEX].serial.config = config;
    uart_obj[UART5_INDEX].serial.config.rx_bufsz = BSP_UART5_RX_BUFSIZE;
    uart_obj[UART5_INDEX].serial.config.tx_bufsz = BSP_UART5_TX_BUFSIZE;
#ifdef BSP_UART5_RX_USING_DMA
    uart_obj[UART5_INDEX].serial.config.dma_ping_bufsz = BSP_UART5_DMA_PING_BUFSIZE;
    uart_obj[UART5_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART5_TX_USING_DMA
    uart_obj[UART5_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART6
    uart_obj[UART6_INDEX].uart_dma_flag = 0;
    uart_obj[UART6_INDEX].serial.config = config;
    uart_obj[UART6_INDEX].serial.config.rx_bufsz = BSP_UART6_RX_BUFSIZE;
    uart_obj[UART6_INDEX].serial.config.tx_bufsz = BSP_UART6_TX_BUFSIZE;
#ifdef BSP_UART6_RX_USING_DMA
    uart_obj[UART6_INDEX].serial.config.dma_ping_bufsz = BSP_UART6_DMA_PING_BUFSIZE;
    uart_obj[UART6_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART6_TX_USING_DMA
    uart_obj[UART6_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART7
    uart_obj[UART7_INDEX].uart_dma_flag = 0;
    uart_obj[UART7_INDEX].serial.config = config;
    uart_obj[UART7_INDEX].serial.config.rx_bufsz = BSP_UART7_RX_BUFSIZE;
    uart_obj[UART7_INDEX].serial.config.tx_bufsz = BSP_UART7_TX_BUFSIZE;
#ifdef BSP_UART7_RX_USING_DMA
    uart_obj[UART7_INDEX].serial.config.dma_ping_bufsz = BSP_UART7_DMA_PING_BUFSIZE;
    uart_obj[UART7_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART7_TX_USING_DMA
    uart_obj[UART7_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif
}

/**
  * @brief  uart init
  * @param  None
  * @retval None
  */
int rt_hw_usart_init (void)
{
    int i;
    int result;

    gd32_uart_get_config();

    for (i = 0; i < sizeof(uart_obj) / sizeof(uart_obj[0]); i++)
    {
        uart_obj[i].serial.ops    = &gd32_uart_ops;

        /* register UART1 device */
        result = rt_hw_serial_register(&uart_obj[i].serial,
                              uart_obj[i].device_name,
                              RT_DEVICE_FLAG_RDWR |
                              RT_DEVICE_FLAG_INT_RX |
                              uart_obj[i].uart_dma_flag,
                              (void *)&uart_obj[i]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif

