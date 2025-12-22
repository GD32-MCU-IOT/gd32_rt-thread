/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>

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
        /* I2C GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOB);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_6);
        gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_7);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7);

        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_LEVEL3, GPIO_PIN_6);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_LEVEL3, GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_HARD_I2C1
    case I2C1:
        /* I2C GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOB);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOB, GPIO_AF_2, GPIO_PIN_10);
        gpio_af_set(GPIOB, GPIO_AF_2, GPIO_PIN_11);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);

        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_LEVEL3, GPIO_PIN_10);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_LEVEL3, GPIO_PIN_11);
        break;
#endif      
    default:
        rt_kprintf("invalid I2C peripheral. \r\n");
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
    /* enable SPI clock */
    rcu_periph_clock_enable(gd32_spi->spi_clk);

    switch(gd32_spi->spi_periph) {
#ifdef BSP_USING_SPI0
    case SPI0:
        /* SPI GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOA);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_5);
        gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_6);
        gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_7);

        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);

        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_5);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_6);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_SPI1
    case SPI1:
        /* SPI GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOB);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOB, GPIO_AF_5, GPIO_PIN_13);
        gpio_af_set(GPIOB, GPIO_AF_5, GPIO_PIN_14);
        gpio_af_set(GPIOB, GPIO_AF_5, GPIO_PIN_15);

        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_14);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_15);

        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_13);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_14);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_15);
        break;
#endif
#ifdef BSP_USING_SPI2
    case SPI2:
        /* SPI GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOB);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOB, GPIO_AF_6, GPIO_PIN_3);
        gpio_af_set(GPIOB, GPIO_AF_6, GPIO_PIN_4);
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_5);

        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);

        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_3);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_4);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_5);
        break;
#endif
    default:
        rt_kprintf("invalid SPI peripheral. \r\n");
        break;
    }
}
#endif

#if defined RT_USING_SERIAL
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
        rcu_periph_clock_enable(uart->uart_clk);

       switch(uart->uart_periph) {
#ifdef BSP_USING_UART0
    case USART0:
        /* UART GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOA);
        /*GPIO pin configuration*/
        gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_9);
        gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_10);

        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);

        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_9);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_10);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        /* UART GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOA);
        /*GPIO pin configuration*/
        gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_2);
        gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_3);

        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_3);

        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_2);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        /* UART GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOB);
        /*GPIO pin configuration*/
        gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_10);
        gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_11);

        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);

        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_10);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL3, GPIO_PIN_11);
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
