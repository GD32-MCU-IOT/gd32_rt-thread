/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-06     RT-Thread    first implementation for GD32307E
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "drv_usart.h"

#if defined RT_USING_SERIAL
/**
  * @brief  UART GPIO Initialization
  * @param  uart: UART handle pointer
  * @retval None
  */
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    rcu_periph_clock_enable(uart->uart_clk);

    switch (uart->uart_periph)
    {
#ifdef BSP_USING_UART0
    case USART0:
        rcu_periph_clock_enable(RCU_GPIOB);
        rcu_periph_clock_enable(RCU_AF);
        /* remap USART0 TX/RX to PB6/PB7 */
        gpio_pin_remap_config(GPIO_USART0_REMAP, ENABLE);
        /* TX=PB6, RX=PB7 */
        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
        gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        rcu_periph_clock_enable(RCU_GPIOA);
        /* TX=PA2, RX=PA3 */
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        rcu_periph_clock_enable(RCU_GPIOB);
        /* TX=PB10, RX=PB11 */
        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART3
    case UART3:
        rcu_periph_clock_enable(RCU_GPIOC);
        /* TX=PC10, RX=PC11 */
        gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART4
    case UART4:
        rcu_periph_clock_enable(RCU_GPIOC);
        rcu_periph_clock_enable(RCU_GPIOD);
        /* TX=PC12, RX=PD2 */
        gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
        gpio_init(GPIOD, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
        break;
#endif
    default:
        break;
    }

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}
#endif
