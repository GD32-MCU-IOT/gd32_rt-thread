/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 */

#include "drv_usart.h"

#ifdef RT_USING_SERIAL

#ifndef USART_TRANSMIT_DMA_ENABLE
#define USART_TRANSMIT_DMA_ENABLE USART_DENT_ENABLE
#endif
#ifndef USART_TRANSMIT_DMA_DISABLE
#define USART_TRANSMIT_DMA_DISABLE USART_DENT_DISABLE
#endif
#ifndef USART_RECEIVE_DMA_ENABLE
#define USART_RECEIVE_DMA_ENABLE USART_DENR_ENABLE
#endif
#ifndef USART_RECEIVE_DMA_DISABLE
#define USART_RECEIVE_DMA_DISABLE USART_DENR_DISABLE
#endif

#if defined(SOC_SERIES_GD32H77x)
#define gd32_dma_deinit(periph, ch)                 dma_channel_deinit(periph, ch)
#else
#define gd32_dma_deinit(periph, ch)                 dma_deinit(periph, ch)
#endif

/* ARM Cortex-M7 cache line size for DMA buffer alignment */
#ifndef RT_DMA_CACHE_LINE_SIZE
#define RT_DMA_CACHE_LINE_SIZE  32
#endif

#if defined(SOC_SERIES_GD32F4xx)
#define DMA_INT_FTF                 DMA_CHXCTL_FTFIE
#define DMA_INT_HTF                 DMA_CHXCTL_HTFIE
#endif

/* USART data register address macros for DMA configuration */
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x) \
 || defined(SOC_SERIES_GD32W51x_F5HC)
#define USART_DATA_TX(usartx) (&USART_TDATA(usartx))
#define USART_DATA_RX(usartx) (&USART_RDATA(usartx))
#elif defined(SOC_SERIES_GD32E51x)
/* USART5 has dedicated data registers on E51x, others keep generic USART_DATA */
#define USART_DATA_TX(usartx) (((usartx) == USART5) ? (&USART5_TDATA(usartx)) : (&USART_DATA(usartx)))
#define USART_DATA_RX(usartx) (((usartx) == USART5) ? (&USART5_RDATA(usartx)) : (&USART_DATA(usartx)))
#else
#define USART_DATA_TX(usartx) (&USART_DATA(usartx))
#define USART_DATA_RX(usartx) (&USART_DATA(usartx))
#endif

#ifdef SOC_SERIES_GD32M53x
/* Map legacy USART names to UART for GD32M53x */
#define USART0                     UART0
#define USART1                     UART1
#define USART2                     UART2
#define USART3                     UART3
#define USART0_IRQn                UART0_IRQn
#define USART1_IRQn                UART1_IRQn
#define USART2_IRQn                UART2_IRQn
#define USART3_IRQn                UART3_IRQn
#define RCU_USART0                 RCU_UART0
#define RCU_USART1                 RCU_UART1
#define RCU_USART2                 RCU_UART2
#define RCU_USART3                 RCU_UART3

/* Map USART APIs to UART APIs */
#define usart_baudrate_set         uart_baudrate_set
#define usart_word_length_set      uart_word_length_set
#define usart_stop_bit_set         uart_stop_bit_set
#define usart_parity_config        uart_parity_config
#define usart_receive_config       uart_receive_config
#define usart_transmit_config      uart_transmit_config
#define usart_enable               uart_enable
#define usart_disable              uart_disable
#define usart_interrupt_enable     uart_interrupt_enable
#define usart_interrupt_disable    uart_interrupt_disable
#define usart_flag_get             uart_flag_get
#define usart_flag_clear           uart_flag_clear
#define usart_data_transmit        uart_data_transmit
#define usart_data_receive         uart_data_receive
#define usart_interrupt_flag_get   uart_interrupt_flag_get

/* Map USART enums to UART enums */
#define USART_WL_9BIT              UART_WL_9BIT
#define USART_WL_8BIT              UART_WL_8BIT
#define USART_STB_2BIT             UART_STB_2BIT
#define USART_STB_1BIT             UART_STB_1BIT
#define USART_PM_ODD               UART_PM_ODD
#define USART_PM_EVEN              UART_PM_EVEN
#define USART_PM_NONE              UART_PM_NONE
#define USART_RECEIVE_ENABLE       UART_RECEIVE_ENABLE
#define USART_TRANSMIT_ENABLE      UART_TRANSMIT_ENABLE
#define USART_INT_RBNE             UART_INT_RBNE
#define USART_INT_TC               UART_INT_TC
#define USART_FLAG_RBNE            UART_FLAG_RBNE
#define USART_FLAG_TBE             UART_FLAG_TBE
#define USART_FLAG_TC              UART_FLAG_TC
#define USART_FLAG_ORERR           UART_FLAG_ORERR
#define USART_INT_FLAG_RBNE        UART_INT_FLAG_RBNE
#define USART_INT_FLAG_TC          UART_INT_FLAG_TC
#endif /* SOC_SERIES_GD32M53x */

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && \
    !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7)
#error "Please define at least one UARTx"

#endif

#include <rtdevice.h>

#ifdef RT_SERIAL_USING_DMA
#if !defined(BSP_USING_UART_RX_DMA) && !defined(BSP_USING_UART_TX_DMA)
#warning "RT_SERIAL_USING_DMA is enabled but neither BSP_USING_UART_RX_DMA nor BSP_USING_UART_TX_DMA is defined"
#endif
#ifdef BSP_USING_UART_RX_DMA
static void gd32_dma_config(struct rt_serial_device *serial, rt_ubase_t flag);
static void dma_rx_done_isr(struct rt_serial_device *serial);
#endif
#ifdef BSP_USING_UART_TX_DMA
static void gd32_dma_tx_config(struct rt_serial_device *serial, rt_ubase_t flag);
#endif

/* DMA TX threshold: transfers smaller than this use polling instead of DMA */
#ifdef BSP_UART_DMA_TX_THRESHOLD
#define GD32_DMA_TX_THRESHOLD   BSP_UART_DMA_TX_THRESHOLD
#else
#define GD32_DMA_TX_THRESHOLD   8
#endif
#endif /* RT_SERIAL_USING_DMA - forward declarations */

/* Polling TX timeout in milliseconds */
#ifdef BSP_UART_POLL_TX_TIMEOUT_MS
#define GD32_POLL_TX_TIMEOUT_MS BSP_UART_POLL_TX_TIMEOUT_MS
#else
#define GD32_POLL_TX_TIMEOUT_MS 1000
#endif

static void GD32_UART_IRQHandler(struct rt_serial_device *serial);

/*******************************************************************************
 * Serial device and DMA config declarations
 * (Moved before uart_obj to satisfy initialization dependencies)
 ******************************************************************************/
#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;
#if defined(BSP_UART0_RX_USING_DMA)
static struct dma_config uart0_dma_rx_config = UART0_DMA_RX_CONFIG;
#endif
#if defined(BSP_UART0_TX_USING_DMA)
static struct dma_config uart0_dma_tx_config = UART0_DMA_TX_CONFIG;
#endif
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
struct rt_serial_device serial1;
#if defined(BSP_UART1_RX_USING_DMA)
struct dma_config uart1_rxdma = UART1_DMA_RX_CONFIG;
#endif
#if defined(BSP_UART1_TX_USING_DMA)
struct dma_config uart1_txdma = UART1_DMA_TX_CONFIG;
#endif
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
struct rt_serial_device serial2;
#if defined(BSP_UART2_RX_USING_DMA)
struct dma_config uart2_rxdma = UART2_DMA_RX_CONFIG;
#endif
#if defined(BSP_UART2_TX_USING_DMA)
struct dma_config uart2_txdma = UART2_DMA_TX_CONFIG;
#endif
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
struct rt_serial_device serial3;
#if defined(BSP_UART3_RX_USING_DMA)
struct dma_config uart3_rxdma = UART3_DMA_RX_CONFIG;
#endif
#if defined(BSP_UART3_TX_USING_DMA)
struct dma_config uart3_txdma = UART3_DMA_TX_CONFIG;
#endif
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
struct rt_serial_device serial4;
#if defined(BSP_UART4_RX_USING_DMA)
struct dma_config uart4_rxdma = UART4_DMA_RX_CONFIG;
#endif
#if defined(BSP_UART4_TX_USING_DMA)
struct dma_config uart4_txdma = UART4_DMA_TX_CONFIG;
#endif
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
struct rt_serial_device serial5;
#if defined(BSP_UART5_RX_USING_DMA)
struct dma_config uart5_rxdma = UART5_DMA_RX_CONFIG;
#endif
#if defined(BSP_UART5_TX_USING_DMA)
struct dma_config uart5_txdma = UART5_DMA_TX_CONFIG;
#endif
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
struct rt_serial_device serial6;
#if defined(BSP_UART6_RX_USING_DMA)
struct dma_config uart6_rxdma = UART6_DMA_RX_CONFIG;
#endif
#if defined(BSP_UART6_TX_USING_DMA)
struct dma_config uart6_txdma = UART6_DMA_TX_CONFIG;
#endif
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
struct rt_serial_device serial7;
#if defined(BSP_UART7_RX_USING_DMA)
struct dma_config uart7_rxdma = UART7_DMA_RX_CONFIG;
#endif
#if defined(BSP_UART7_TX_USING_DMA)
struct dma_config uart7_txdma = UART7_DMA_TX_CONFIG;
#endif
#endif /* BSP_USING_UART7 */

/*******************************************************************************
 * uart_obj array definitions
 * (Moved before DMA helper functions for better code organization)
 ******************************************************************************/
#if !defined(SOC_SERIES_GD32H75E) && !defined(SOC_SERIES_GD32E51x) && !defined(SOC_SERIES_GD32F3x0) \
 && !defined(SOC_SERIES_GD32F50x) && !defined(SOC_SERIES_GD32G5x3) && !defined(SOC_SERIES_GD32C11x) \
 && !defined(SOC_SERIES_GD32L23x) && !defined(SOC_SERIES_GD32E23x) && !defined(SOC_SERIES_GD32E11x) \
 && !defined(SOC_SERIES_GD32H77x) && !defined(SOC_SERIES_GD32M53x) && !defined(SOC_SERIES_GD32H7xx) \
 && !defined(SOC_SERIES_GD32F5xx) && !defined(SOC_SERIES_GD32F30x) && !defined(SOC_SERIES_GD32W51x_F5HC) \
 && !defined(SOC_SERIES_GD32F4xx)
static const struct gd32_uart uart_obj[] = {
    #ifdef BSP_USING_UART0
    {
        USART0,                                /* uart peripheral index */
        USART0_IRQn,                           /* uart iqrn */
        RCU_USART0,                            /* uart periph clock */
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32F5xx || defined SOC_SERIES_GD32H7xx
        RCU_GPIOA, RCU_GPIOA,                  /* tx gpio clock, rx gpio clock */
        GPIOA, GPIO_AF_7, GPIO_PIN_9,          /* tx port, tx alternate, tx pin */
        GPIOA, GPIO_AF_7, GPIO_PIN_10,         /* rx port, rx alternate, rx pin */
#elif defined SOC_SERIES_GD32E50x
        RCU_GPIOA, RCU_GPIOA,                  /* tx gpio clock, rx gpio clock */
        GPIOA, 0, GPIO_PIN_9,                  /* tx port, tx alternate, tx pin */
        GPIOA, 0, GPIO_PIN_10,                 /* rx port, rx alternate, rx pin */
        0,                                     /* afio remap cfg */
#elif defined SOC_SERIES_GD32E23x
        RCU_GPIOA, RCU_GPIOA,
        GPIOA, GPIO_AF_1, GPIO_PIN_9,
        GPIOA, GPIO_AF_1, GPIO_PIN_10,
#else
        RCU_GPIOA, RCU_GPIOA,                  /* tx gpio clock, rx gpio clock */
        GPIOA, GPIO_PIN_9,                     /* tx port, tx pin */
        GPIOA, GPIO_PIN_10,                    /* rx port, rx pin */
#endif
#ifdef RT_SERIAL_USING_DMA
        &uart0_rxdma,
#ifdef BSP_USING_UART_TX_DMA
        &uart0_txdma,
#endif
#endif
        &serial0,
        "uart0",
    },
    #endif

    #ifdef BSP_USING_UART1
    {
        USART1,                                 /* uart peripheral index */
        USART1_IRQn,                            /* uart iqrn */
        RCU_USART1,                             /* uart periph clock */
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32F5xx
        RCU_GPIOA, RCU_GPIOA,                   /* tx gpio clock, rx gpio clock */
        GPIOA, GPIO_AF_7, GPIO_PIN_2,           /* tx port, tx alternate, tx pin */
        GPIOA, GPIO_AF_7, GPIO_PIN_3,           /* rx port, rx alternate, rx pin */
#elif defined SOC_SERIES_GD32E50x
        RCU_GPIOA, RCU_GPIOA,                   /* tx gpio clock, rx gpio clock */
        GPIOA, 0, GPIO_PIN_2,                   /* tx port, tx alternate, tx pin */
        GPIOA, 0, GPIO_PIN_3,                   /* rx port, rx alternate, rx pin */
        0,                                      /* afio remap cfg */
#elif defined SOC_SERIES_GD32E23x
        RCU_GPIOA, RCU_GPIOA,
        GPIOA, GPIO_AF_1, GPIO_PIN_14,
        GPIOA, GPIO_AF_1, GPIO_PIN_15,
#else
        RCU_GPIOA, RCU_GPIOA,                   /* periph clock, tx gpio clock, rt gpio clock */
        GPIOA, GPIO_PIN_2,                      /* tx port, tx pin */
        GPIOA, GPIO_PIN_3,                      /* rx port, rx pin */
#endif
#ifdef RT_SERIAL_USING_DMA
        &uart1_rxdma,
#endif
        &serial1,
        "uart1",
    },
    #endif

    #ifdef BSP_USING_UART2
    {
        USART2,                                 /* uart peripheral index */
        USART2_IRQn,                            /* uart iqrn */
        RCU_USART2,                                    /* uart periph clock */
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32F5xx
        RCU_GPIOB, RCU_GPIOB,                   /* tx gpio clock, rt gpio clock */
        GPIOB, GPIO_AF_7, GPIO_PIN_10,          /* tx port, tx alternate, tx pin */
        GPIOB, GPIO_AF_7, GPIO_PIN_11,          /* rx port, rx alternate, rx pin */
#elif defined SOC_SERIES_GD32E50x
        RCU_GPIOB, RCU_GPIOB,                   /* tx gpio clock, rx gpio clock */
        GPIOB, 0, GPIO_PIN_10,                  /* tx port, tx alternate, tx pin */
        GPIOB, 0, GPIO_PIN_11,                  /* rx port, rx alternate, rx pin */
        0,                                      /* afio remap cfg */
#else
        RCU_GPIOB, RCU_GPIOB,                   /* tx gpio clock, rt gpio clock */
        GPIOB, GPIO_PIN_10,                     /* tx port, tx pin */
        GPIOB, GPIO_PIN_11,                     /* rx port, rx pin */
#endif
#ifdef RT_SERIAL_USING_DMA
        &uart2_rxdma,
#ifdef BSP_USING_UART_TX_DMA
        &uart2_txdma,
#endif
#endif
        &serial2,
        "uart2",
    },
    #endif

    #ifdef BSP_USING_UART3
    {
        UART3,                                 /* uart peripheral index */
        UART3_IRQn,                            /* uart iqrn */
        RCU_UART3,                             /* uart periph clock */
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32F5xx || defined SOC_SERIES_GD32H7xx
        RCU_GPIOC, RCU_GPIOC,                  /* tx gpio clock, rt gpio clock */
        GPIOC, GPIO_AF_8, GPIO_PIN_10,         /* tx port, tx alternate, tx pin */
        GPIOC, GPIO_AF_8, GPIO_PIN_11,         /* rx port, rx alternate, rx pin */
#elif defined SOC_SERIES_GD32E50x
        RCU_GPIOC, RCU_GPIOC,                   /* tx gpio clock, rx gpio clock */
        GPIOC, 0, GPIO_PIN_10,                  /* tx port, tx alternate, tx pin */
        GPIOC, 0, GPIO_PIN_11,                  /* rx port, rx alternate, rx pin */
        0,                                      /* afio remap cfg */
#else
        RCU_GPIOC, RCU_GPIOC,                  /* periph clock, tx gpio clock, rt gpio clock */
        GPIOC, GPIO_PIN_10,                    /* tx port, tx pin */
        GPIOC, GPIO_PIN_11,                    /* rx port, rx pin */
#endif
#ifdef RT_SERIAL_USING_DMA
        &uart3_rxdma,
#endif
        &serial3,
        "uart3",
    },
    #endif

    #ifdef BSP_USING_UART4
    {
        UART4,                                 /* uart peripheral index */
        UART4_IRQn,                            /* uart iqrn */
        RCU_UART4, RCU_GPIOC, RCU_GPIOD,       /* periph clock, tx gpio clock, rt gpio clock */
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32F5xx || defined SOC_SERIES_GD32H7xx
        GPIOC, GPIO_AF_8, GPIO_PIN_12,         /* tx port, tx alternate, tx pin */
        GPIOD, GPIO_AF_8, GPIO_PIN_2,          /* rx port, rx alternate, rx pin */
#elif defined SOC_SERIES_GD32E50x
        GPIOC, 0, GPIO_PIN_12,                 /* tx port, tx alternate, tx pin */
        GPIOD, 0, GPIO_PIN_2,                  /* rx port, rx alternate, rx pin */
        0,                                     /* afio remap cfg */
#else
        GPIOC, GPIO_PIN_12,                    /* tx port, tx pin */
        GPIOD, GPIO_PIN_2,                     /* rx port, rx pin */
#endif
        &serial4,
        "uart4",
    },
    #endif

    #ifdef BSP_USING_UART5
    {
        USART5,                                 /* uart peripheral index */
        USART5_IRQn,                            /* uart iqrn */
        RCU_USART5, RCU_GPIOC, RCU_GPIOC,       /* periph clock, tx gpio clock, rt gpio clock */
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32F5xx
        GPIOC, GPIO_AF_8, GPIO_PIN_6,           /* tx port, tx alternate, tx pin */
        GPIOC, GPIO_AF_8, GPIO_PIN_7,           /* rx port, rx alternate, rx pin */
#elif defined (SOC_SERIES_GD32H7xx)
        GPIOC, GPIO_AF_7, GPIO_PIN_6,           /* tx port, tx alternate, tx pin */
        GPIOC, GPIO_AF_7, GPIO_PIN_7,           /* rx port, rx alternate, rx pin */
#elif defined SOC_SERIES_GD32E50x
        GPIOC, AFIO_PC6_USART5_CFG, GPIO_PIN_6, /* tx port, tx alternate, tx pin */
        GPIOC, AFIO_PC7_USART5_CFG, GPIO_PIN_7, /* rx port, rx alternate, rx pin */
        0,                                      /* afio remap cfg */
#else
        GPIOC, GPIO_PIN_6,                      /* tx port, tx pin */
        GPIOC, GPIO_PIN_7,                      /* rx port, rx pin */
#endif
#ifdef RT_SERIAL_USING_DMA
        &uart5_rxdma,
#ifdef BSP_USING_UART_TX_DMA
        &uart5_txdma,
#endif
#endif
        &serial5,
        "uart5",
    },
    #endif

    #ifdef BSP_USING_UART6
    {
        UART6,                                 /* uart peripheral index */
        UART6_IRQn,                            /* uart iqrn */
        RCU_UART6, RCU_GPIOE, RCU_GPIOE,       /* periph clock, tx gpio clock, rt gpio clock */
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32F5xx
        GPIOE, GPIO_AF_8, GPIO_PIN_7,          /* tx port, tx alternate, tx pin */
        GPIOE, GPIO_AF_8, GPIO_PIN_8,          /* rx port, rx alternate, rx pin */
#elif defined (SOC_SERIES_GD32H7xx)
        GPIOE, GPIO_AF_7, GPIO_PIN_8,          // tx port, tx alternate, tx pin
        GPIOE, GPIO_AF_7, GPIO_PIN_7,          // rx port, rx alternate, rx pin
#else
        GPIOE, GPIO_PIN_7,                     /* tx port, tx pin */
        GPIOE, GPIO_PIN_8,                     /* rx port, rx pin */
#endif
#ifdef RT_SERIAL_USING_DMA
        &uart6_rxdma,
#ifdef BSP_USING_UART_TX_DMA
        &uart6_txdma,
#endif
#endif
        &serial6,
        "uart6",
    },
    #endif

    #ifdef BSP_USING_UART7
    {
        UART7,                                 /* uart peripheral index */
        UART7_IRQn,                            /* uart iqrn */
        RCU_UART7, RCU_GPIOE, RCU_GPIOE,       /* periph clock, tx gpio clock, rt gpio clock */
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32F5xx || defined SOC_SERIES_GD32H7xx
        GPIOE, GPIO_AF_8, GPIO_PIN_1,          /* tx port, tx alternate, tx pin */
        GPIOE, GPIO_AF_8, GPIO_PIN_0,          /* rx port, rx alternate, rx pin */
#else
        GPIOE, GPIO_PIN_0,                     /* tx port, tx pin */
        GPIOE, GPIO_PIN_1,                     /* rx port, rx pin */
#endif
#ifdef RT_SERIAL_USING_DMA
        &uart7_rxdma,
#ifdef BSP_USING_UART_TX_DMA
        &uart7_txdma,
#endif
#endif
        &serial7,
        "uart7",
    },
    #endif
};

#else
static struct gd32_uart uart_obj[] = {
    #ifdef BSP_USING_UART0
    {
        USART0,                                /* uart peripheral index */
        RCU_USART0,                            /* uart periph clock */
        USART0_IRQn,                           /* uart iqrn */
        "uart0",
        &serial0,
#ifdef RT_SERIAL_USING_DMA
#ifdef BSP_UART0_TX_USING_DMA
        &uart0_dma_tx_config,
#endif
#ifdef BSP_UART0_RX_USING_DMA
        &uart0_dma_rx_config,
#endif
#endif
    },
    #endif

    #ifdef BSP_USING_UART1
    {
        USART1,                                /* uart peripheral index */
        RCU_USART1,                            /* uart periph clock */
        USART1_IRQn,                           /* uart iqrn */
        "uart1",
        &serial1,
#ifdef RT_SERIAL_USING_DMA
#ifdef BSP_UART1_TX_USING_DMA
        &uart1_txdma,
#endif
#ifdef BSP_UART1_RX_USING_DMA
        &uart1_rxdma,
#endif
#endif
    },
    #endif

    #ifdef BSP_USING_UART2
    {
        USART2,                                /* uart peripheral index */
        RCU_USART2,                            /* uart periph clock */
        USART2_IRQn,                           /* uart iqrn */
        "uart2",
        &serial2,
#ifdef RT_SERIAL_USING_DMA
#ifdef BSP_UART2_TX_USING_DMA
        &uart2_txdma,
#endif
#ifdef BSP_UART2_RX_USING_DMA
        &uart2_rxdma,
#endif
#endif
    },
    #endif

    #ifdef BSP_USING_UART3
    {
        UART3,                                 /* uart peripheral index */
        RCU_UART3,                             /* uart periph clock */
        UART3_IRQn,                            /* uart iqrn */
        "uart3",
        &serial3,
#ifdef RT_SERIAL_USING_DMA
#ifdef BSP_UART3_TX_USING_DMA
        &uart3_txdma,
#endif
#ifdef BSP_UART3_RX_USING_DMA
        &uart3_rxdma,
#endif
#endif
    },
    #endif

    #ifdef BSP_USING_UART4
    {
        UART4,                                 /* uart peripheral index */
        RCU_UART4,                             /* uart periph clock */
        UART4_IRQn,                            /* uart iqrn */
        "uart4",
        &serial4,
#ifdef RT_SERIAL_USING_DMA
#ifdef BSP_UART4_TX_USING_DMA
        &uart4_txdma,
#endif
#ifdef BSP_UART4_RX_USING_DMA
        &uart4_rxdma,
#endif
#endif
    },
    #endif

    #ifdef BSP_USING_UART5
    {
        USART5,                                /* uart peripheral index */
        RCU_USART5,                            /* uart periph clock */
        USART5_IRQn,                           /* uart iqrn */
        "uart5",
        &serial5,
#ifdef RT_SERIAL_USING_DMA
#ifdef BSP_UART5_TX_USING_DMA
        &uart5_txdma,
#endif
#ifdef BSP_UART5_RX_USING_DMA
        &uart5_rxdma,
#endif
#endif
    },
    #endif

    #ifdef BSP_USING_UART6
    {
        UART6,                                 /* uart peripheral index */
        RCU_UART6,                             /* uart periph clock */
        UART6_IRQn,                            /* uart iqrn */
        "uart6",
        &serial6,
#ifdef RT_SERIAL_USING_DMA
#ifdef BSP_UART6_TX_USING_DMA
        &uart6_txdma,
#endif
#ifdef BSP_UART6_RX_USING_DMA
        &uart6_rxdma,
#endif
#endif
    },
    #endif

    #ifdef BSP_USING_UART7
    {
        UART7,                                 /* uart peripheral index */
        RCU_UART7,                             /* uart periph clock */
        UART7_IRQn,                            /* uart iqrn */
        "uart7",
        &serial7,
#ifdef RT_SERIAL_USING_DMA
#ifdef BSP_UART7_TX_USING_DMA
        &uart7_txdma,
#endif
#ifdef BSP_UART7_RX_USING_DMA
        &uart7_rxdma,
#endif
#endif
    },
    #endif
};
#endif

/*******************************************************************************
 * DMA helper functions
 ******************************************************************************/
#ifdef RT_SERIAL_USING_DMA
#ifdef BSP_USING_UART_TX_DMA
static void dma_tx_done_isr(uint32_t dma_periph, dma_channel_enum dma_ch)
{
    dma_channel_disable(dma_periph, dma_ch);
    dma_flag_clear(dma_periph, dma_ch, DMA_FLAG_FTF);
    dma_flag_clear(dma_periph, dma_ch, DMA_FLAG_HTF);
    dma_flag_clear(dma_periph, dma_ch, DMA_FLAG_FEE);
    dma_flag_clear(dma_periph, dma_ch, DMA_FLAG_TAE);
}
#endif /* BSP_USING_UART_TX_DMA */

static void Error_Handler(void)
{
    RT_ASSERT(0);
}
#endif

/*******************************************************************************
 * ISR handlers
 ******************************************************************************/
#if defined(BSP_USING_UART0)

#if defined(BSP_UART0_RX_USING_DMA)
void UART0_DMA_RX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_rx_done_isr(&serial0);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_UART0_TX_USING_DMA)
void UART0_DMA_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_tx_done_isr(UART0_TX_DMA_PERIPH, UART0_TX_DMA_CHANNEL);
    rt_interrupt_leave();
}
#endif

void USART0_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_UART_IRQHandler(&serial0);
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)

#if defined(BSP_UART1_RX_USING_DMA)
void UART1_DMA_RX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_rx_done_isr(&serial1);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_UART1_TX_USING_DMA
void UART1_DMA_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_tx_done_isr(UART1_TX_DMA_PERIPH, UART1_TX_DMA_CHANNEL);
    rt_interrupt_leave();
}
#endif /* RT_SERIAL_USING_DMA */

void USART1_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_UART_IRQHandler(&serial1);
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_UART2_RX_USING_DMA)
void UART2_DMA_RX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_rx_done_isr(&serial2);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_UART2_TX_USING_DMA)
void UART2_DMA_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_tx_done_isr(UART2_TX_DMA_PERIPH, UART2_TX_DMA_CHANNEL);
    rt_interrupt_leave();
}
#endif
#endif /* RT_SERIAL_USING_DMA */

void USART2_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_UART_IRQHandler(&serial2);
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)

#if defined(RT_SERIAL_USING_DMA)
#ifdef BSP_UART3_RX_USING_DMA
void UART3_DMA_RX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_rx_done_isr(&serial3);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_UART3_TX_USING_DMA
void UART3_DMA_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_tx_done_isr(UART3_TX_DMA_PERIPH, UART3_TX_DMA_CHANNEL);
    rt_interrupt_leave();
}
#endif
#endif /* RT_SERIAL_USING_DMA */

void UART3_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_UART_IRQHandler(&serial3);
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)

#if defined(RT_SERIAL_USING_DMA)
#ifdef BSP_UART4_RX_USING_DMA
void UART4_DMA_RX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_rx_done_isr(&serial4);
    rt_interrupt_leave();
}
#endif
#ifdef BSP_UART4_TX_USING_DMA
void UART4_DMA_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_tx_done_isr(UART4_TX_DMA_PERIPH, UART4_TX_DMA_CHANNEL);
    rt_interrupt_leave();
}
#endif
#endif /* RT_SERIAL_USING_DMA */

void UART4_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_UART_IRQHandler(&serial4);
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)

#if defined(RT_SERIAL_USING_DMA)
#ifdef BSP_UART5_RX_USING_DMA
void UART5_DMA_RX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_rx_done_isr(&serial5);
    rt_interrupt_leave();
}
#endif
#ifdef BSP_UART5_TX_USING_DMA
void UART5_DMA_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_tx_done_isr(UART5_TX_DMA_PERIPH, UART5_TX_DMA_CHANNEL);
    rt_interrupt_leave();
}
#endif
#endif /* RT_SERIAL_USING_DMA */

void USART5_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_UART_IRQHandler(&serial5);
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)

#if defined(RT_SERIAL_USING_DMA)
#ifdef BSP_UART6_RX_USING_DMA
void UART6_DMA_RX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_rx_done_isr(&serial6);
    rt_interrupt_leave();
}
#endif
#ifdef BSP_UART6_TX_USING_DMA
void UART6_DMA_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_tx_done_isr(UART6_TX_DMA_PERIPH, UART6_TX_DMA_CHANNEL);
    rt_interrupt_leave();
}
#endif
#endif /* RT_SERIAL_USING_DMA */

void UART6_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_UART_IRQHandler(&serial6);
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)

#if defined(RT_SERIAL_USING_DMA)
#ifdef BSP_UART7_RX_USING_DMA
void UART7_DMA_RX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_rx_done_isr(&serial7);
    rt_interrupt_leave();
}
#endif
#ifdef BSP_UART7_TX_USING_DMA
void UART7_DMA_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    dma_tx_done_isr(UART7_TX_DMA_PERIPH, UART7_TX_DMA_CHANNEL);
    rt_interrupt_leave();
}
#endif
#endif /* RT_SERIAL_USING_DMA */

void UART7_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_UART_IRQHandler(&serial7);
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART7 */

#if !defined(SOC_SERIES_GD32H75E) && !defined(SOC_SERIES_GD32E51x) && !defined(SOC_SERIES_GD32F3x0) \
 && !defined(SOC_SERIES_GD32F50x) && !defined(SOC_SERIES_GD32G5x3) && !defined(SOC_SERIES_GD32C11x) \
 && !defined(SOC_SERIES_GD32L23x) && !defined(SOC_SERIES_GD32E23x) && !defined(SOC_SERIES_GD32E11x) \
 && !defined(SOC_SERIES_GD32H77x) && !defined(SOC_SERIES_GD32M53x) && !defined(SOC_SERIES_GD32H7xx) \
 && !defined(SOC_SERIES_GD32F5xx) && !defined(SOC_SERIES_GD32F30x) && !defined(SOC_SERIES_GD32W51x_F5HC) \
 && !defined(SOC_SERIES_GD32F4xx)
/**
* @brief UART MSP Initialization
*        This function configures the hardware resources used in this example:
*           - Peripheral's clock enable
*           - Peripheral's GPIO Configuration
*           - NVIC configuration for UART interrupt request enable
* @param huart: UART handle pointer
* @retval None
*/
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    /* enable USART clock */
    rcu_periph_clock_enable(uart->tx_gpio_clk);
    rcu_periph_clock_enable(uart->rx_gpio_clk);
    rcu_periph_clock_enable(uart->uart_clk);

#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32E23x
    /* connect port to USARTx_Tx */
    gpio_af_set(uart->tx_port, uart->tx_af, uart->tx_pin);

    /* connect port to USARTx_Rx */
    gpio_af_set(uart->rx_port, uart->rx_af, uart->rx_pin);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(uart->tx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, uart->tx_pin);
    gpio_output_options_set(uart->tx_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, uart->tx_pin);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(uart->rx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, uart->rx_pin);
    gpio_output_options_set(uart->rx_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, uart->rx_pin);

#elif defined SOC_SERIES_GD32H7xx
    /* connect port to USARTx_Tx */
    gpio_af_set(uart->tx_port, uart->tx_af, uart->tx_pin);

    /* connect port to USARTx_Rx */
    gpio_af_set(uart->rx_port, uart->rx_af, uart->rx_pin);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(uart->tx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, uart->tx_pin);
    gpio_output_options_set(uart->tx_port, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, uart->tx_pin);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(uart->rx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, uart->rx_pin);
    gpio_output_options_set(uart->rx_port, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, uart->rx_pin);

#elif defined SOC_SERIES_GD32E50x
    /* configure remap function */
    if (uart->uart_remap != 0 || uart->tx_af != 0 || uart->rx_af != 0)
    {
        rcu_periph_clock_enable(RCU_AF);
        gpio_pin_remap_config(uart->uart_remap, ENABLE);
    }

    /* connect port to USARTx_Tx */
    gpio_init(uart->tx_port, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, uart->tx_pin);

    /* connect port to USARTx_Rx */
    gpio_init(uart->rx_port, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, uart->rx_pin);

    /* configure alternate1 function */
    if (uart->tx_af != 0 || uart->rx_af != 0)
    {
        rcu_periph_clock_enable(RCU_AF);
        gpio_afio_port_config(uart->tx_af, ENABLE);
        gpio_afio_port_config(uart->rx_af, ENABLE);
    }

#else
    /* connect port to USARTx_Tx */
    gpio_init(uart->tx_port, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, uart->tx_pin);

    /* connect port to USARTx_Rx */
    gpio_init(uart->rx_port, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, uart->rx_pin);
#endif

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}
#else
#warning "gd32_uart_gpio_init should be define in board_msd_init.c"
rt_weak void gd32_uart_gpio_init(struct gd32_uart *uart)
{
}
#endif

/**
  * @brief  uart configure
  * @param  serial, cfg
  * @retval None
  */
static rt_err_t gd32_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct gd32_uart *)serial->parent.user_data;

    gd32_uart_gpio_init(uart);

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

/**
  * @brief  uart control
  * @param  serial, arg
  * @retval None
  */
static rt_err_t gd32_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct gd32_uart *uart;

#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irqn);
        /* disable interrupt */
#if defined SOC_SERIES_GD32E51x
        if (uart->uart_periph == USART5)
        {
            usart5_interrupt_disable(USART5, USART5_INT_RBNE);
        }
        else
#endif
        {
            usart_interrupt_disable(uart->uart_periph, USART_INT_RBNE);
        }

#ifdef RT_SERIAL_USING_DMA
        /* disable DMA */
#ifdef BSP_USING_UART_RX_DMA
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) {
            nvic_irq_disable(uart->dma_rx->irq);

            /* disable interrupt */
#if defined SOC_SERIES_GD32E51x
            if (uart->uart_periph == USART5)
            {
                usart5_interrupt_disable(USART5, USART5_INT_IDLE);
            }
            else
#endif
            usart_interrupt_disable(uart->uart_periph, USART_INT_IDLE);

            dma_channel_disable(uart->dma_rx->periph, uart->dma_rx->channel);
            usart_dma_receive_config(uart->uart_periph, USART_RECEIVE_DMA_DISABLE);
            gd32_dma_deinit(uart->dma_rx->periph, uart->dma_rx->channel);

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x) || defined(SOC_SERIES_GD32H75E)
            /* Free cache-aligned DMA buffer */
            if (uart->dma_rx_buffer != RT_NULL)
            {
                rt_free_align(uart->dma_rx_buffer);
                uart->dma_rx_buffer = RT_NULL;
            }
#endif

            uart->last_recv_index = 0;
        }
#endif /* BSP_USING_UART_RX_DMA */
#ifdef BSP_USING_UART_TX_DMA
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX) {
            nvic_irq_disable(uart->dma_tx->irq);

            dma_channel_disable(uart->dma_tx->periph, uart->dma_tx->channel);
            usart_dma_transmit_config(uart->uart_periph, USART_TRANSMIT_DMA_DISABLE);
            gd32_dma_deinit(uart->dma_tx->periph, uart->dma_tx->channel);
        }
#endif
#endif
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irqn);
#if defined SOC_SERIES_GD32E51x
        if (uart->uart_periph == USART5)
        {
            usart5_flag_clear(USART5, USART5_FLAG_RBNE);
            /* enable interrupt */
            usart5_interrupt_enable(USART5, USART5_INT_RBNE);
        }
        else
#endif
        {
            usart_flag_clear(uart->uart_periph, USART_FLAG_RBNE);
            /* enable interrupt */
            usart_interrupt_enable(uart->uart_periph, USART_INT_RBNE);
        }
        break;

#ifdef RT_SERIAL_USING_DMA
    case RT_DEVICE_CTRL_CONFIG:
#ifdef BSP_USING_UART_RX_DMA
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) {
            gd32_dma_config(serial, ctrl_arg);
        }
#endif
#ifdef BSP_USING_UART_TX_DMA
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX) {
            gd32_dma_tx_config(serial, ctrl_arg);
        }
#endif
        break;
#endif

    case RT_DEVICE_CTRL_CLOSE:
        usart_disable(uart->uart_periph);
        break;
    }

    return RT_EOK;
}

/**
  * @brief  uart put char
  * @param  serial, ch
  * @retval RT_EOK on success, -RT_ETIMEOUT on timeout
  */
static int gd32_uart_putc(struct rt_serial_device *serial, char ch)
{
    struct gd32_uart *uart;
    rt_tick_t start_tick;
    rt_tick_t timeout_ticks = rt_tick_from_millisecond(GD32_POLL_TX_TIMEOUT_MS);

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;
    usart_data_transmit(uart->uart_periph, ch);
#if defined SOC_SERIES_GD32E51x
    if (uart->uart_periph == USART5)
    {
        start_tick = rt_tick_get();
        while((usart5_flag_get(USART5, USART5_FLAG_TC) == RESET))
        {
            if ((rt_tick_get() - start_tick) > timeout_ticks)
            {
                return -RT_ETIMEOUT;
            }
        }
    }
    else
#endif
    {
        start_tick = rt_tick_get();
        while((usart_flag_get(uart->uart_periph, USART_FLAG_TBE) == RESET))
        {
            if ((rt_tick_get() - start_tick) > timeout_ticks)
            {
                return -RT_ETIMEOUT;
            }
        }
    }

    return RT_EOK;
}

/**
  * @brief  uart get char
  * @param  serial
  * @retval None
  */
static int gd32_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;

    ch = -1;
#if defined SOC_SERIES_GD32E51x
    if (uart->uart_periph == USART5)
    {
        if (usart5_flag_get(USART5, USART5_FLAG_RBNE) != RESET)
            ch = usart_data_receive(USART5);
    }
    else
#endif
    {
        if (usart_flag_get(uart->uart_periph, USART_FLAG_RBNE) != RESET)
            ch = usart_data_receive(uart->uart_periph);
    }
    return ch;
}

#ifdef RT_SERIAL_USING_DMA

#ifdef BSP_USING_UART_RX_DMA
static void dma_uart_config(struct rt_serial_device *serial, uint32_t setting_recv_len,
                            void *mem_base_addr)
{
    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;
    dma_single_data_parameter_struct dma_init_struct;

    /* rx dma config */
    uart->setting_recv_len = setting_recv_len;
    /* Initialize last_recv_index to DMA counter initial value (circular mode) */
    uart->last_recv_index = setting_recv_len;
    gd32_dma_deinit(uart->dma_rx->periph, uart->dma_rx->channel);

    dma_single_data_para_struct_init(&dma_init_struct);
    dma_init_struct.direction    = DMA_PERIPH_TO_MEMORY;
    GD32_DMA_SET_MEMADDR(&dma_init_struct, (uint32_t)mem_base_addr);
    dma_init_struct.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
    GD32_DMA_SET_DATAWIDTH(&dma_init_struct, DMA_PERIPH_WIDTH_8BIT);
    dma_init_struct.number       = uart->setting_recv_len;
    dma_init_struct.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.priority     = DMA_PRIORITY_HIGH;
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x) || defined(SOC_SERIES_GD32H75E)
    dma_init_struct.request      = uart->dma_rx->request;
#endif
    dma_init_struct.periph_addr  = (uint32_t)USART_DATA_RX(uart->uart_periph);
    dma_single_data_mode_init(uart->dma_rx->periph, uart->dma_rx->channel, &dma_init_struct);
#if defined(SOC_SERIES_GD32F5xx) || defined(SOC_SERIES_GD32W51x_F5HC) || defined(SOC_SERIES_GD32F4xx)
    dma_channel_subperipheral_select(uart->dma_rx->periph, uart->dma_rx->channel, uart->dma_rx->subperiph);
#endif
    /* configure DMA mode - circular mode for continuous reception */
    dma_circulation_enable(uart->dma_rx->periph, uart->dma_rx->channel);

    dma_flag_clear(uart->dma_rx->periph, uart->dma_rx->channel, DMA_FLAG_FTF);
    dma_flag_clear(uart->dma_rx->periph, uart->dma_rx->channel, DMA_FLAG_HTF);
    /* Enable Full-Transfer and Half-Transfer interrupts for circular RX */
    dma_interrupt_enable(uart->dma_rx->periph, uart->dma_rx->channel, DMA_INT_FTF);
    dma_interrupt_enable(uart->dma_rx->periph, uart->dma_rx->channel, DMA_INT_HTF);
}

static void gd32_dma_config(struct rt_serial_device *serial, rt_ubase_t flag)
{
    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;
    struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x) || defined(SOC_SERIES_GD32H75E)
    /*
     * Allocate cache-line aligned DMA buffer to avoid D-Cache coherency issues.
     * ARM Cortex-M7 cache line is 32 bytes. If the DMA buffer shares a cache line
     * with other data (like serial_tx->data_queue), cache invalidate operations
     * will corrupt that data.
     *
     * Buffer size must also be aligned to cache line size to ensure safe
     * cache invalidate operations on the entire buffer.
     */
    if (uart->dma_rx_buffer == RT_NULL)
    {
        /* Align buffer size to cache line size for safe cache operations */
        rt_size_t aligned_bufsz = RT_ALIGN(serial->config.bufsz, RT_DMA_CACHE_LINE_SIZE);
        /* Allocate cache-aligned DMA buffer, keep rx_fifo->buffer unchanged */
        uart->dma_rx_buffer = (rt_uint8_t *)rt_malloc_align(aligned_bufsz, RT_DMA_CACHE_LINE_SIZE);
        RT_ASSERT(uart->dma_rx_buffer != RT_NULL);
        rt_memset(uart->dma_rx_buffer, 0, aligned_bufsz);
    }
#endif
#if defined SOC_SERIES_GD32E51x
    if (uart->uart_periph == USART5)
    {
        if (SET == usart5_flag_get(USART5, USART5_FLAG_IDLE)) {
            usart5_flag_clear(USART5, USART5_FLAG_IDLE);
            usart_data_receive(USART5);
        }

        /* enable idle interrupt */
        usart5_interrupt_enable(USART5, USART5_INT_IDLE);
    }
    else
#endif
    {
        if(SET == usart_flag_get(uart->uart_periph, USART_FLAG_IDLE)) {
            usart_flag_clear(uart->uart_periph, USART_FLAG_IDLE);
            usart_data_receive(uart->uart_periph);
        }

        /* enable idle interrupt */
        usart_interrupt_enable(uart->uart_periph, USART_INT_IDLE);
    }
    /* DMA clock enable */
    if(DMA0 == uart->dma_rx->periph) {
        rcu_periph_clock_enable(RCU_DMA0);
    } else if(DMA1 == uart->dma_rx->periph) {
        rcu_periph_clock_enable(RCU_DMA1);
    } else {
        Error_Handler();
    }

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x) || defined(SOC_SERIES_GD32H75E)
    /* enable DMAMUX clock */
    rcu_periph_clock_enable(RCU_DMAMUX);
    /* clean d-cache */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, uart->dma_rx_buffer, serial->config.bufsz);
    /* rx dma config */
    dma_uart_config(serial, serial->config.bufsz, uart->dma_rx_buffer);
#else
    /* rx dma config */
    dma_uart_config(serial, serial->config.bufsz, rx_fifo->buffer);
#endif

    usart_dma_receive_config(uart->uart_periph, USART_RECEIVE_DMA_ENABLE);
    dma_channel_enable(uart->dma_rx->periph, uart->dma_rx->channel);
    /* rx dma interrupt config */
    nvic_irq_enable(uart->dma_rx->irq, 1, 0);
}
#endif /* BSP_USING_UART_RX_DMA */

#ifdef BSP_USING_UART_TX_DMA
static void gd32_dma_tx_config(struct rt_serial_device *serial, rt_ubase_t flag)
{
    dma_single_data_parameter_struct dma_init_struct;

    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;

    /* DMA clock enable */
    if(DMA0 == uart->dma_tx->periph) {
        rcu_periph_clock_enable(RCU_DMA0);
    } else if(DMA1 == uart->dma_tx->periph) {
        rcu_periph_clock_enable(RCU_DMA1);
    } else {
        Error_Handler();
    }

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x) || defined(SOC_SERIES_GD32H75E)
    /* enable DMAMUX clock */
    rcu_periph_clock_enable(RCU_DMAMUX);
#endif

    /* tx dma config */
    gd32_dma_deinit(uart->dma_tx->periph, uart->dma_tx->channel);

    dma_single_data_para_struct_init(&dma_init_struct);
    dma_init_struct.direction    = DMA_MEMORY_TO_PERIPH;
    dma_init_struct.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
    GD32_DMA_SET_DATAWIDTH(&dma_init_struct, DMA_PERIPH_WIDTH_8BIT);
    dma_init_struct.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.priority     = DMA_PRIORITY_HIGH;
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x) || defined(SOC_SERIES_GD32H75E)
    dma_init_struct.request      = uart->dma_tx->request;
#endif
    dma_init_struct.number       = 0;   /* will be set in transmit function */
    GD32_DMA_SET_MEMADDR(&dma_init_struct, 0);   /* will be set in transmit function */
    GD32_DMA_SET_CIRCULAR(&dma_init_struct, DMA_CIRCULAR_MODE_DISABLE);
    dma_init_struct.periph_addr  = (uint32_t)USART_DATA_TX(uart->uart_periph);
    dma_single_data_mode_init(uart->dma_tx->periph, uart->dma_tx->channel, &dma_init_struct);
#if defined(SOC_SERIES_GD32F5xx) || defined(SOC_SERIES_GD32W51x_F5HC) || defined(SOC_SERIES_GD32F4xx)
    dma_channel_subperipheral_select(uart->dma_tx->periph, uart->dma_tx->channel, uart->dma_tx->subperiph);
#endif
    /* configure DMA mode */
    dma_circulation_disable(uart->dma_tx->periph, uart->dma_tx->channel);
}

static rt_ssize_t gd32_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    struct gd32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    uart = (struct gd32_uart *) serial->parent.user_data;

    if (size == 0)
    {
        return 0;
    }

    if (RT_SERIAL_DMA_TX == direction)
    {
        /* Small transfers: use polling to avoid DMA setup overhead */
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
                    return ret;  /* timeout or error in putc */
                }
            }
            /* wait for last byte fully shifted out with timeout */
            start_tick = rt_tick_get();
#if defined SOC_SERIES_GD32E51x
            if (uart->uart_periph == USART5)
            {
                while (usart5_flag_get(USART5, USART5_FLAG_TC) == RESET)
                {
                    if ((rt_tick_get() - start_tick) > timeout_ticks)
                    {
                        /* timeout error */
                        return -RT_ETIMEOUT;
                    }
                }
            }
            else
#endif
            while (usart_flag_get(uart->uart_periph, USART_FLAG_TC) == RESET)
            {
                if ((rt_tick_get() - start_tick) > timeout_ticks)
                {
                    /* timeout error */
                    return -RT_ETIMEOUT;
                }
            }
            /* notify framework that transmission is complete */
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
            return size;
        }

#ifdef RT_USING_CACHE
        /*
         * Flush D-Cache to ensure DMA reads correct data from memory.
         * rt_hw_cpu_dcache_ops handles non-aligned addresses internally.
         */
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)buf, size);
#endif

        dma_memory_address_config(uart->dma_tx->periph, uart->dma_tx->channel, DMA_MEMORY_0, (uint32_t)buf);
        dma_transfer_number_config(uart->dma_tx->periph, uart->dma_tx->channel, size);

        dma_flag_clear(uart->dma_tx->periph, uart->dma_tx->channel, DMA_FLAG_FTF);
        dma_interrupt_enable(uart->dma_tx->periph, uart->dma_tx->channel, DMA_INT_FTF);

#if defined SOC_SERIES_GD32E51x
        if (uart->uart_periph == USART5)
        {
            usart5_flag_clear(USART5, USART5_FLAG_TBE);
            usart5_flag_clear(USART5, USART5_FLAG_TC);
            /* enable transmit complete interrupt */
            usart5_interrupt_enable(USART5, USART5_INT_TC);
        }
        else
#endif
        {
            usart_flag_clear(uart->uart_periph, USART_FLAG_TBE);
            usart_flag_clear(uart->uart_periph, USART_FLAG_TC);
            /* enable transmit complete interrupt */
            usart_interrupt_enable(uart->uart_periph, USART_INT_TC);
        }

        usart_dma_transmit_config(uart->uart_periph, USART_TRANSMIT_DMA_ENABLE);
        /* tx dma interrupt config */
        nvic_irq_enable(uart->dma_tx->irq, 1, 0);

        dma_channel_enable(uart->dma_tx->periph, uart->dma_tx->channel);

        return size;
    }
    return 0;
}
#endif

#ifdef BSP_USING_UART_RX_DMA
/**
 * Unified DMA receive ISR handler for circular mode.
 * Handles IDLE, Half-Transfer and Full-Transfer interrupt events.
 * last_recv_index stores the DMA remaining counter at last processing point.
 *
 * @param serial serial device
 * @param isr_flag UART_RX_DMA_IT_IDLE_FLAG / UART_RX_DMA_IT_HT_FLAG / UART_RX_DMA_IT_TC_FLAG
 */
static void dma_recv_isr(struct rt_serial_device *serial, rt_uint8_t isr_flag)
{
    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;
    rt_base_t level;
    rt_size_t recv_len = 0;
    rt_size_t counter;

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x) || defined(SOC_SERIES_GD32H75E)
    struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
#endif

    level = rt_hw_interrupt_disable();
    counter = dma_transfer_number_get(uart->dma_rx->periph, uart->dma_rx->channel);

    switch (isr_flag)
    {
    case UART_RX_DMA_IT_IDLE_FLAG:
        /* IDLE: counter may be anywhere, handle both directions */
        if (counter <= uart->last_recv_index)
            recv_len = uart->last_recv_index - counter;
        else
            recv_len = uart->setting_recv_len + uart->last_recv_index - counter;
        break;

    case UART_RX_DMA_IT_HT_FLAG:
        /* Half-transfer: counter is decreasing, should be less than last */
        if (counter < uart->last_recv_index)
            recv_len = uart->last_recv_index - counter;
        break;

    case UART_RX_DMA_IT_TC_FLAG:
        /* Full-transfer: counter just reloaded, should be >= last */
        if (counter >= uart->last_recv_index)
            recv_len = uart->setting_recv_len + uart->last_recv_index - counter;
        break;
    }

    if (recv_len)
    {
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H77x) || defined(SOC_SERIES_GD32H75E)
        /* Invalidate DMA buffer cache, then copy to rx_fifo->buffer */
        rt_size_t recv_start = uart->setting_recv_len - uart->last_recv_index;
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, uart->dma_rx_buffer, serial->config.bufsz);
        if (recv_start + recv_len <= uart->setting_recv_len) {
            rt_memcpy(rx_fifo->buffer + recv_start,
                      uart->dma_rx_buffer + recv_start, recv_len);
        } else {
            rt_size_t first_part = uart->setting_recv_len - recv_start;
            rt_memcpy(rx_fifo->buffer + recv_start,
                      uart->dma_rx_buffer + recv_start, first_part);
            rt_memcpy(rx_fifo->buffer, uart->dma_rx_buffer, recv_len - first_part);
        }
#endif
        uart->last_recv_index = counter;
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
    rt_hw_interrupt_enable(level);
}

/**
 * Serial port receive idle process. This need add to uart idle ISR.
 *
 * @param serial serial device
 */
static void dma_uart_rx_idle_isr(struct rt_serial_device *serial)
{
    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;

    dma_recv_isr(serial, UART_RX_DMA_IT_IDLE_FLAG);

    /* read a data for clear receive idle interrupt flag */
#if defined SOC_SERIES_GD32E51x
    if (uart->uart_periph == USART5)
    {
        usart_data_receive(USART5);
        usart5_flag_clear(USART5, USART5_FLAG_IDLE);
    }
    else
#endif
    {
        usart_data_receive(uart->uart_periph);
        usart_flag_clear(uart->uart_periph, USART_FLAG_IDLE);
    }
}

/**
 * DMA receive done process. This need add to DMA receive done ISR.
 * Uses circular mode: handles both half-transfer and full-transfer interrupts.
 *
 * @param serial serial device
 */
static void dma_rx_done_isr(struct rt_serial_device *serial)
{
    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;

    /* Check and handle half-transfer interrupt */
    if (dma_flag_get(uart->dma_rx->periph, uart->dma_rx->channel, DMA_FLAG_HTF) != RESET) {
        dma_flag_clear(uart->dma_rx->periph, uart->dma_rx->channel, DMA_FLAG_HTF);
        dma_recv_isr(serial, UART_RX_DMA_IT_HT_FLAG);
    }

    /* Check and handle full-transfer interrupt */
    if (dma_flag_get(uart->dma_rx->periph, uart->dma_rx->channel, DMA_FLAG_FTF) != RESET) {
        dma_flag_clear(uart->dma_rx->periph, uart->dma_rx->channel, DMA_FLAG_FTF);
        dma_recv_isr(serial, UART_RX_DMA_IT_TC_FLAG);
    }
}
#endif /* BSP_USING_UART_RX_DMA */

#endif /* RT_SERIAL_USING_DMA */


/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void GD32_UART_IRQHandler(struct rt_serial_device *serial)
{
    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

#if defined SOC_SERIES_GD32E51x
    if (uart->uart_periph == USART5)
    {
        /* USART5 in mode Receiver */
        if ((usart5_interrupt_flag_get(USART5, USART5_INT_FLAG_RBNE) != RESET))
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
            /* Clear RXNE interrupt flag */
            usart5_flag_clear(USART5, USART5_FLAG_RBNE);
        }
#if defined(BSP_USING_UART_RX_DMA)
        if(usart5_interrupt_flag_get(USART5, USART5_INT_FLAG_IDLE) != RESET)
        {
            dma_uart_rx_idle_isr(serial);
        }
#endif
        if (usart5_interrupt_flag_get(USART5, USART5_INT_FLAG_TC) != RESET)
        {
            /* clear interrupt */
            usart5_flag_clear(USART5, USART5_FLAG_TC);
            usart5_interrupt_disable(USART5, USART5_INT_TC);
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
        }
        if (usart5_flag_get(USART5, USART5_FLAG_ORERR) == SET)
        {
            usart5_flag_clear(USART5, USART5_FLAG_ORERR);
        }
    }
    else
#endif
    {
        /* UART in mode Receiver -------------------------------------------------*/
	    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_RBNE) != RESET) &&
	        (usart_flag_get(uart->uart_periph, USART_FLAG_RBNE) != RESET))
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
            /* Clear RXNE interrupt flag */
            usart_flag_clear(uart->uart_periph, USART_FLAG_RBNE);
        }
#if defined(BSP_USING_UART_RX_DMA)
        if(usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_IDLE) != RESET)
        {
            dma_uart_rx_idle_isr(serial);
        }
#endif
        if (usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_TC) != RESET)
        {
            /* clear interrupt */
            usart_flag_clear(uart->uart_periph, USART_FLAG_TC);
            usart_interrupt_disable(uart->uart_periph, USART_INT_TC);
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
        }
        if (usart_flag_get(uart->uart_periph, USART_FLAG_ORERR) == SET)
        {
            usart_flag_clear(uart->uart_periph, USART_FLAG_ORERR);
        }
    }
}
static const struct rt_uart_ops gd32_uart_ops =
{
    .configure = gd32_uart_configure,
    .control = gd32_uart_control,
    .putc = gd32_uart_putc,
    .getc = gd32_uart_getc,
#ifndef BSP_USING_UART_TX_DMA
    NULL,
#else
    .dma_transmit = gd32_dma_transmit,
#endif
};

/**
  * @brief  uart init
  * @param  None
  * @retval None
  */
int rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;

    int result;
    rt_uint32_t flag = 0;

    for (i = 0; i < sizeof(uart_obj) / sizeof(uart_obj[0]); i++)
    {
        uart_obj[i].serial->ops    = &gd32_uart_ops;
        uart_obj[i].serial->config = config;

        flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;
#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART_RX_DMA)
        flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#if defined(BSP_USING_UART_TX_DMA)
        flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif
        /* register UART1 device */
        result = rt_hw_serial_register(uart_obj[i].serial,
                              uart_obj[i].device_name,
                              flag,
                              (void *)&uart_obj[i]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif
