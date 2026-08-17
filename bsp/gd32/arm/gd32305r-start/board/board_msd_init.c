/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-27     Zhiwei Zhang first implementation for GD32305R-START
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "drv_usart.h"

#if defined RT_USING_SERIAL
/**
* @brief UART GPIO Initialization
*        GD32F30x has no alternate-function mux; USART TX is configured as
*        AF push-pull and RX as floating input via gpio_init().
* @param uart: UART handle pointer
* @retval None
*/
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    /* enable USART clock */
    rcu_periph_clock_enable(uart->uart_clk);

    switch (uart->uart_periph) {
#ifdef BSP_USING_UART0
    case USART0:
        /* USART0: PA9(TX) / PA10(RX) */
        rcu_periph_clock_enable(RCU_GPIOA);

        /* configure USART TX as alternate function push-pull */
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
        /* configure USART RX as input floating */
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        /* USART1: PA2(TX) / PA3(RX) */
        rcu_periph_clock_enable(RCU_GPIOA);

        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        /* USART2: PB10(TX) / PB11(RX) */
        rcu_periph_clock_enable(RCU_GPIOB);

        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART3
    case UART3:
        /* UART3: PC10(TX) / PC11(RX) */
        rcu_periph_clock_enable(RCU_GPIOC);

        gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART4
    case UART4:
        /* UART4: PC12(TX) / PD2(RX) */
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
#endif
