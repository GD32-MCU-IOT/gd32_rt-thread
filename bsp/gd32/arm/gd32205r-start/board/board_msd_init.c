/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-06     upgrade minisystem: provide board-level UART MSP init
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "drv_usart.h"

#ifdef RT_USING_SERIAL
/**
 * @brief UART MSP Initialization
 *        SOC_SERIES_GD32F20x has been added to the exclusion list in
 *        drv_usart.c / drv_usart.h, so the shared driver does NOT compile
 *        the default gd32_uart_gpio_init() for GD32F20x. Instead, this
 *        file provides the board-specific UART pin configuration using the
 *        legacy GD32F20x GPIO API, matching the official GD32F205R_START
 *        demo suites.
 *
 * Pin assignments (GD32F205R-START, default AF, no remap):
 *   USART0: PA9  (TX) / PA10 (RX)
 *   USART1: PA2  (TX) / PA3  (RX)   <- console
 *   USART2: PB10 (TX) / PB11 (RX)
 *   UART3 : PC10 (TX) / PC11 (RX)
 *   UART4 : PC12 (TX) / PD2  (RX)
 */
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    /* enable USART clock */
    rcu_periph_clock_enable(uart->uart_clk);

    switch (uart->uart_periph)
    {
#ifdef BSP_USING_UART0
    case USART0:
        /* USART0: TX=PA9, RX=PA10 */
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        /* USART1: TX=PA2, RX=PA3 */
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        /* USART2: TX=PB10, RX=PB11 */
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART3
    case UART3:
        /* UART3: TX=PC10, RX=PC11 */
        rcu_periph_clock_enable(RCU_GPIOC);
        gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART4
    case UART4:
        /* UART4: TX=PC12, RX=PD2 */
        rcu_periph_clock_enable(RCU_GPIOC);
        rcu_periph_clock_enable(RCU_GPIOD);
        gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
        gpio_init(GPIOD, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
        break;
#endif
    default:
        rt_kprintf("invalid UART peripheral. \r\n");
        return;
    }

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}
#endif /* RT_USING_SERIAL */
