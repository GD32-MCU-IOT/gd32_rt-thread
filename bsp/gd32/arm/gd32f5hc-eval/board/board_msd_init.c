/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-27     RT-Thread    first implementation for GD32W51x_F5HC
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "drv_hard_i2c.h"
#include "drv_spi.h"
#include "drv_usart.h"

#ifdef RT_USING_I2C
/**
  * @brief  This function initializes the i2c pin.
  * @param  i2c
  * @retval None
  */
void gd32_i2c_gpio_init(const struct gd32_i2c_bus *i2c)
{
    /* enable I2C clock */
    rcu_periph_clock_enable(i2c->i2c_clk);

    switch(i2c->i2c_periph) {
#ifdef BSP_USING_HARD_I2C0
    case I2C0:
        /* I2C0: SCL=PB6, SDA=PB7, AF4 */
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_6 | GPIO_PIN_7);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6 | GPIO_PIN_7);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, GPIO_PIN_6 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_HARD_I2C1
    case I2C1:
        /* I2C1: SDA=PA8 (AF6), SCL=PB15 (AF6) */
        rcu_periph_clock_enable(RCU_GPIOA);
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOA, GPIO_AF_6, GPIO_PIN_8);
        gpio_af_set(GPIOB, GPIO_AF_6, GPIO_PIN_15);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_15);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, GPIO_PIN_8);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, GPIO_PIN_15);
        break;
#endif
    default:
        break;
    }
}
#endif

#ifdef RT_USING_SPI
/**
* @brief SPI Initialization
* @param gd32_spi: SPI BUS
* @retval None
*/
void gd32_spi_init(struct gd32_spi *gd32_spi)
{
    rcu_periph_clock_enable(gd32_spi->spi_clk);

    switch(gd32_spi->spi_periph) {
#ifdef BSP_USING_SPI0
    case SPI0:
        /* SPI0: SCK=PA5, MISO=PA6, MOSI=PA7, AF5 */
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_af_set(GPIOA, GPIO_AF_5, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_SPI1
    case SPI1:
        /* SPI1: SCK=PC11, MISO=PC13, MOSI=PD0, AF9 */
        rcu_periph_clock_enable(RCU_GPIOC);
        rcu_periph_clock_enable(RCU_GPIOD);
        gpio_af_set(GPIOC, GPIO_AF_9, GPIO_PIN_11 | GPIO_PIN_13);
        gpio_af_set(GPIOD, GPIO_AF_9, GPIO_PIN_0);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11 | GPIO_PIN_13);
        gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, GPIO_PIN_11 | GPIO_PIN_13);
        gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, GPIO_PIN_0);
        break;
#endif
    default:
        break;
    }
}
#endif

#if defined RT_USING_SERIAL
/**
* @brief UART GPIO Initialization
* @param uart: UART handle pointer
* @retval None
*/
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    rcu_periph_clock_enable(uart->uart_clk);

    switch(uart->uart_periph) {
#ifdef BSP_USING_UART0
    case USART0:
        /* USART0: TX=PD3, RX=PD4, AF7 */
        rcu_periph_clock_enable(RCU_GPIOD);
        gpio_af_set(GPIOD, GPIO_AF_7, GPIO_PIN_3 | GPIO_PIN_4);
        gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_3 | GPIO_PIN_4);
        gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, GPIO_PIN_3 | GPIO_PIN_4);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        /* USART1: TX=PC0, RX=PC1, AF0 */
        rcu_periph_clock_enable(RCU_GPIOC);
        gpio_af_set(GPIOC, GPIO_AF_0, GPIO_PIN_0 | GPIO_PIN_1);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0 | GPIO_PIN_1);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, GPIO_PIN_0 | GPIO_PIN_1);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        /* USART2: TX=PB10, RX=PB11, AF7 */
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, GPIO_PIN_10 | GPIO_PIN_11);
        break;
#endif
    default:
        break;
    }

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}
#endif
