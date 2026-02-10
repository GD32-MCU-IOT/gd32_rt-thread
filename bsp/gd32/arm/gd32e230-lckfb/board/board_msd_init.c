/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-30     RT-Thread    first implementation for GD32E230
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#if defined RT_USING_SERIAL
/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - NVIC configuration for UART interrupt request enable
  * @param uart: UART handle pointer
  * @retval None
  */
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    /* enable USART clock */
    rcu_periph_clock_enable(uart->uart_clk);

    switch(uart->uart_periph) {
#ifdef BSP_USING_UART0
    case USART0:
        /* enable UART GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOA);

        /* USART0: PA9-TX, PA10-RX, AF1 */
        gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9);
        gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_10);

        /* TX: push-pull output */
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

        /* RX: input with pull-up */
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        /* enable UART GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOA);

        /* USART1: PA2-TX, PA3-RX, AF1 */
        gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_2);
        gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_3);

        /* TX: push-pull output */
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

        /* RX: input with pull-up */
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_3);
        break;
#endif
    default:
        rt_kprintf("invalid UART peripheral. \r\n");
        break;
    }

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}
#endif

/*@}*/
