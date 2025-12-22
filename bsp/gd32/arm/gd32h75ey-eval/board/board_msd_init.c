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
        /* enable I2C clock */
        rcu_periph_clock_enable(RCU_GPIOB);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_6);
        gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_7);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7);

        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_6);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_HARD_I2C1
    case I2C1:
        /* enable I2C clock */
        rcu_periph_clock_enable(RCU_GPIOH);
        rcu_periph_clock_enable(RCU_GPIOB);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOH, GPIO_AF_4, GPIO_PIN_4);
        gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_11);
        gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_4);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);

        gpio_output_options_set(GPIOH, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_4);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_HARD_I2C2
    case I2C2:
        /* enable I2C clock */
        rcu_periph_clock_enable(RCU_GPIOA);
        rcu_periph_clock_enable(RCU_GPIOC);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOA, GPIO_AF_4, GPIO_PIN_8);
        gpio_af_set(GPIOC, GPIO_AF_4, GPIO_PIN_9);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);

        gpio_output_options_set(GPIOA, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_8);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_9);
        break;
#endif
#ifdef BSP_USING_HARD_I2C3
    case I2C3:
        /* enable I2C clock */
        rcu_periph_clock_enable(RCU_GPIOH);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOH, GPIO_AF_4, GPIO_PIN_11);
        gpio_af_set(GPIOH, GPIO_AF_4, GPIO_PIN_12);
        gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);
        gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_12);

        gpio_output_options_set(GPIOH, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_11);
        gpio_output_options_set(GPIOH, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_12);
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
        /* enable SPI clock */
        rcu_periph_clock_enable(RCU_GPIOA);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOA, GPIO_AF_5, GPIO_PIN_5);
        gpio_af_set(GPIOA, GPIO_AF_5, GPIO_PIN_6);
        gpio_af_set(GPIOA, GPIO_AF_5, GPIO_PIN_7);

        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);

        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_5);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_6);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_SPI1
    case SPI1:
        /* enable SPI clock */
        rcu_periph_clock_enable(RCU_GPIOI);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOI, GPIO_AF_5, GPIO_PIN_1);
        gpio_af_set(GPIOI, GPIO_AF_5, GPIO_PIN_2);
        gpio_af_set(GPIOI, GPIO_AF_5, GPIO_PIN_3);

        gpio_mode_set(GPIOI, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
        gpio_mode_set(GPIOI, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
        gpio_mode_set(GPIOI, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);

        gpio_output_options_set(GPIOI, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_1);
        gpio_output_options_set(GPIOI, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_2);
        gpio_output_options_set(GPIOI, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_SPI2
    case SPI2:
        /* enable SPI clock */
        rcu_periph_clock_enable(RCU_GPIOB);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOB, GPIO_AF_6, GPIO_PIN_3);
        gpio_af_set(GPIOB, GPIO_AF_6, GPIO_PIN_4);
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_5);

        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);

        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_3);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_4);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_5);
        break;
#endif
#ifdef BSP_USING_SPI3
    case SPI3:
        /* enable SPI clock */
        rcu_periph_clock_enable(RCU_GPIOE);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOE, GPIO_AF_5, GPIO_PIN_2);
        gpio_af_set(GPIOE, GPIO_AF_5, GPIO_PIN_5);
        gpio_af_set(GPIOE, GPIO_AF_5, GPIO_PIN_6);

        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6);

        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_2);
        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_5);
        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_6);
        break;
#endif
#ifdef BSP_USING_SPI4
    case SPI4:
        /* enable SPI clock */
        rcu_periph_clock_enable(RCU_GPIOF);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOF, GPIO_AF_5, GPIO_PIN_7);
        gpio_af_set(GPIOF, GPIO_AF_5, GPIO_PIN_8);
        gpio_af_set(GPIOF, GPIO_AF_5, GPIO_PIN_9);

        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9);

        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_7);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_8);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_9);
        break;
#endif
#ifdef BSP_USING_SPI5
    case SPI5:
        /* enable SPI clock */
        rcu_periph_clock_enable(RCU_GPIOG);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOG, GPIO_AF_5, GPIO_PIN_12);
        gpio_af_set(GPIOG, GPIO_AF_5, GPIO_PIN_13);
        gpio_af_set(GPIOG, GPIO_AF_5, GPIO_PIN_14);

        gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
        gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13);
        gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_14);

        gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_12);
        gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_13);
        gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_14);
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
        /* enable UART clock */
        rcu_periph_clock_enable(RCU_GPIOB);
        /*GPIO pin configuration*/
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_6);
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_7);

        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_6);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        /* enable UART clock */
        rcu_periph_clock_enable(RCU_GPIOA);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_2);
        gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_3);

        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);

        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_2);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        /* enable UART clock */
        rcu_periph_clock_enable(RCU_GPIOB);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_10);
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_11);

        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11);

        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_10);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART3
    case UART3:
        /* enable UART clock */
        rcu_periph_clock_enable(RCU_GPIOC);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_10);
        gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_11);

        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11);

        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_10);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART4
    case UART4:
        /* enable UART clock */
        rcu_periph_clock_enable(RCU_GPIOC);
        rcu_periph_clock_enable(RCU_GPIOD);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_12);
        gpio_af_set(GPIOD, GPIO_AF_8, GPIO_PIN_2);

        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
        gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);

        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_12);
        gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_2);
        break;
#endif
#ifdef BSP_USING_UART5
    case USART5:
        /* enable UART clock */
        rcu_periph_clock_enable(RCU_GPIOC);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOC, GPIO_AF_7, GPIO_PIN_6);
        gpio_af_set(GPIOC, GPIO_AF_7, GPIO_PIN_7);

        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);

        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_6);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_UART6
    case UART6:
        /* enable UART clock */
        rcu_periph_clock_enable(RCU_GPIOE);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOE, GPIO_AF_7, GPIO_PIN_7);
        gpio_af_set(GPIOE, GPIO_AF_7, GPIO_PIN_8);

        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);

        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_7);
        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_8);
        break;
#endif
#ifdef BSP_USING_UART7
    case UART7:
        /* enable UART clock */
        rcu_periph_clock_enable(RCU_GPIOE);

        /*GPIO pin configuration*/
        gpio_af_set(GPIOE, GPIO_AF_8, GPIO_PIN_0);
        gpio_af_set(GPIOE, GPIO_AF_8, GPIO_PIN_1);

        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0);
        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);

        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_0);
        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, GPIO_PIN_1);
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
