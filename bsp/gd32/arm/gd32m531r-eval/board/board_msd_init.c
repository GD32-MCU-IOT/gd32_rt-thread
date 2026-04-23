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
    case I2C:
        /* WARNING: Due to pin sharing conflict, I2C0 and UART2 cannot be enabled simultaneously.
         * I2C0 SCL/SDA (PF9/PF10, AF8) conflicts with UART2 RX/TX (PF9/PF10, AF6).
         * Enable only one peripheral at runtime to avoid pinmux override and communication errors.
         */
        /* I2C GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOF);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOF, GPIO_AF_8, GPIO_PIN_9);
        gpio_af_set(GPIOF, GPIO_AF_8, GPIO_PIN_10);

        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);

        gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_HIGH, GPIO_PIN_9);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_HIGH, GPIO_PIN_10);
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
    case SPI:
        /* SPI GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOF);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOF, GPIO_AF_9, GPIO_PIN_8);
        gpio_af_set(GPIOF, GPIO_AF_9, GPIO_PIN_11);
        gpio_af_set(GPIOF, GPIO_AF_9, GPIO_PIN_12);

        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);

        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PIN_8);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PIN_11);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PIN_12);
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
    case UART0:
        /* UART GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOA);
        /*GPIO pin configuration*/
        gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_9);
        gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_10);

        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);

        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PIN_9);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PIN_10);
        break;
#endif
#ifdef BSP_USING_UART1
    case UART1:
        /* UART GPIO clock */
        rcu_periph_clock_enable(RCU_GPIOA);
        /*GPIO pin configuration*/
        gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_2);
        gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_3);

        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_3);

        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PIN_2);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case UART2:
        /* WARNING: Due to pin sharing conflict, UART2 and I2C0 cannot be enabled simultaneously.
         * UART2 TX/RX (PF10/PF9, AF6) conflicts with I2C0 SCL/SDA (PF9/PF10, AF8).
         * Enable only one peripheral at runtime to avoid pinmux override and communication errors.
         */
        /* UART2_TX: PF10, UART2_RX: PF9, AF6 (GD32M531R-EVAL COM1) */
        rcu_periph_clock_enable(RCU_GPIOF);
        gpio_af_set(GPIOF, GPIO_AF_6, GPIO_PIN_10);
        gpio_af_set(GPIOF, GPIO_AF_6, GPIO_PIN_9);

        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);

        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PIN_10);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PIN_9);
        break;
#endif
#ifdef BSP_USING_UART3
    case UART3:
        /* UART3_TX: PF13, UART3_RX: PF14, AF7 (GD32M531R-EVAL COM0 - Default) */
        rcu_periph_clock_enable(RCU_GPIOF);
        gpio_af_set(GPIOF, GPIO_AF_7, GPIO_PIN_13);
        gpio_af_set(GPIOF, GPIO_AF_7, GPIO_PIN_14);

        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_13);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_14);

        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PIN_13);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PIN_14);
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
