/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-30     RT-Thread    first implementation for GD32E235C
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#ifdef RT_USING_I2C
/**
  * @brief  This function initializes the i2c pin.
  * @param  i2c: I2C bus structure
  * @retval None
  */
void gd32_i2c_gpio_init(const struct gd32_i2c_bus *i2c)
{
    /* enable I2C clock */
    rcu_periph_clock_enable(i2c->i2c_clk);

    switch(i2c->i2c_periph) {
#ifdef BSP_USING_HARD_I2C0
    case I2C0:
        /* enable I2C GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOB);

        /* I2C0: PB6-SCL, PB7-SDA, AF1 */
        gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_6);
        gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_7);

        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6);


        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_HARD_I2C1
    case I2C1:
        /* enable I2C GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOB);

        /* I2C1: PB10-SCL, PB11-SDA, AF1 */
        gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_10);
        gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_11);

        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
    default:
        rt_kprintf("invalid I2C peripheral. \r\n");
        break;
    }
    i2c_deinit(i2c->i2c_periph);
}
#endif

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

        /* USART1: PA14-TX, PA15-RX, AF1 
         * WARNING: PA15 is shared with LED4. 
         * If UART1 is enabled, LED4 functionality on PA15 should be disabled to avoid conflicts.
         */
        gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_14);
        gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_15);

        /* TX: push-pull output */
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_14);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_14);

        /* RX: input with pull-up */
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_15);
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
