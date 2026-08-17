/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-28     Zhiwei Zhang first implementation for GD32470I-EVAL
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "drv_usart.h"

#ifdef RT_USING_SPI
#include "drv_spi.h"
#endif

#ifdef RT_USING_I2C
#include "drv_hard_i2c.h"
#endif

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

    switch (i2c->i2c_periph)
    {
#ifdef BSP_USING_HARD_I2C0
    case I2C0:
        /* I2C0_SCL: PB6, I2C0_SDA: PB7 */
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_6 | GPIO_PIN_7);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6 | GPIO_PIN_7);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, GPIO_PIN_6 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_HARD_I2C1
    case I2C1:
        /* I2C1_SCL: PB10, I2C1_SDA: PB11 */
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, GPIO_PIN_10 | GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_HARD_I2C2
    case I2C2:
        /* I2C2_SCL: PA8, I2C2_SDA: PC9 */
        rcu_periph_clock_enable(RCU_GPIOA);
        rcu_periph_clock_enable(RCU_GPIOC);
        gpio_af_set(GPIOA, GPIO_AF_4, GPIO_PIN_8);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, GPIO_PIN_8);
        gpio_af_set(GPIOC, GPIO_AF_4, GPIO_PIN_9);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, GPIO_PIN_9);
        break;
#endif
    default:
        rt_kprintf("invalid I2C peripheral.\r\n");
        break;
    }
}
#endif /* RT_USING_I2C */

#ifdef RT_USING_SPI
/**
  * @brief  SPI GPIO Initialization
  * @param  gd32_spi: SPI BUS
  * @retval None
  */
void gd32_spi_init(struct gd32_spi *gd32_spi)
{
    /* enable SPI clock */
    rcu_periph_clock_enable(gd32_spi->spi_clk);

    switch (gd32_spi->spi_periph)
    {
#ifdef BSP_USING_SPI0
    case SPI0:
        /* SPI0_SCK: PA5, SPI0_MISO: PA6, SPI0_MOSI: PA7 */
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_af_set(GPIOA, GPIO_AF_5, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_SPI1
    case SPI1:
        /* SPI1_SCK: PB13, SPI1_MISO: PB14, SPI1_MOSI: PB15 */
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_5, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
        break;
#endif
#ifdef BSP_USING_SPI2
    case SPI2:
        /* SPI2_SCK: PB3, SPI2_MISO: PB4, SPI2_MOSI: PB5 */
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_6, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
        break;
#endif
#ifdef BSP_USING_SPI3
    case SPI3:
        /* SPI3_SCK: PE2, SPI3_MISO: PE5, SPI3_MOSI: PE6 */
        rcu_periph_clock_enable(RCU_GPIOE);
        gpio_af_set(GPIOE, GPIO_AF_5, GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6);
        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6);
        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6);
        break;
#endif
#ifdef BSP_USING_SPI4
    case SPI4:
        /* SPI4_SCK: PF7, SPI4_MISO: PF8, SPI4_MOSI: PF9 */
        rcu_periph_clock_enable(RCU_GPIOF);
        gpio_af_set(GPIOF, GPIO_AF_5, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
        break;
#endif
#ifdef BSP_USING_SPI5
    case SPI5:
        /* SPI5_SCK: PG13, SPI5_MISO: PG12, SPI5_MOSI: PG14 */
        rcu_periph_clock_enable(RCU_GPIOG);
        gpio_af_set(GPIOG, GPIO_AF_5, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14);
        gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14);
        gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14);
        break;
#endif
    default:
        rt_kprintf("invalid SPI peripheral.\r\n");
        break;
    }
}
#endif /* RT_USING_SPI */

#if defined RT_USING_SERIAL
/**
  * @brief  UART GPIO Initialization
  * @param  uart: UART handle pointer
  * @retval None
  */
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    /* enable USART clock */
    rcu_periph_clock_enable(uart->uart_clk);

    switch (uart->uart_periph)
    {
#ifdef BSP_USING_UART0
    case USART0:
        /* USART0_TX: PA9, USART0_RX: PA10 */
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9 | GPIO_PIN_10);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9 | GPIO_PIN_10);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_9 | GPIO_PIN_10);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        /* USART1_TX: PA2, USART1_RX: PA3 */
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_2 | GPIO_PIN_3);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2 | GPIO_PIN_3);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_2 | GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        /* USART2_TX: PB10, USART2_RX: PB11 */
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_10 | GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART3
    case UART3:
        /* UART3_TX: PC10, UART3_RX: PC11 */
        rcu_periph_clock_enable(RCU_GPIOC);
        gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_10 | GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART4
    case UART4:
        /* UART4_TX: PC12, UART4_RX: PD2 */
        rcu_periph_clock_enable(RCU_GPIOC);
        rcu_periph_clock_enable(RCU_GPIOD);
        gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_12);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_12);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_12);
        gpio_af_set(GPIOD, GPIO_AF_8, GPIO_PIN_2);
        gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);
        gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_2);
        break;
#endif
#ifdef BSP_USING_UART5
    case USART5:
        /* USART5_TX: PC6, USART5_RX: PC7 */
        rcu_periph_clock_enable(RCU_GPIOC);
        gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_6 | GPIO_PIN_7);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6 | GPIO_PIN_7);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_6 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_UART6
    case UART6:
        /* UART6_TX: PE8, UART6_RX: PE7 */
        rcu_periph_clock_enable(RCU_GPIOE);
        gpio_af_set(GPIOE, GPIO_AF_8, GPIO_PIN_8 | GPIO_PIN_7);
        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8 | GPIO_PIN_7);
        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_8 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_UART7
    case UART7:
        /* UART7_TX: PE1, UART7_RX: PE0 */
        rcu_periph_clock_enable(RCU_GPIOE);
        gpio_af_set(GPIOE, GPIO_AF_8, GPIO_PIN_0 | GPIO_PIN_1);
        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0 | GPIO_PIN_1);
        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_0 | GPIO_PIN_1);
        break;
#endif
    default:
        rt_kprintf("invalid UART peripheral.\r\n");
        /* GPIO pinmux not configured: skip NVIC setup to avoid ghost interrupts
         * on unconfigured RX pins (per path instructions: Kconfig options,
         * pinmux and IRQ config must stay consistent) */
        return;
    }

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}
#endif /* RT_USING_SERIAL */
