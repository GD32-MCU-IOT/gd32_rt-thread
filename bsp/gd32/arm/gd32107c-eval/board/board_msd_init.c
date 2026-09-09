/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "drv_hard_i2c.h"
#include "drv_spi.h"
#include "drv_usart.h"

#ifdef RT_USING_I2C
void gd32_i2c_gpio_init(const struct gd32_i2c_bus *i2c)
{
    rcu_periph_clock_enable(i2c->i2c_clk);

    switch (i2c->i2c_periph)
    {
#ifdef BSP_USING_HARD_I2C0
    case I2C0:
        rcu_periph_clock_enable(RCU_GPIOB);
        /* SCL=PB6, SDA=PB7 */
        gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_HARD_I2C1
    case I2C1:
        rcu_periph_clock_enable(RCU_GPIOB);
        /* SCL=PB10, SDA=PB11 */
        gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_10 | GPIO_PIN_11);
        break;
#endif
    default:
        break;
    }
}
#endif

#ifdef RT_USING_SPI
void gd32_spi_init(struct gd32_spi *gd32_spi)
{
    rcu_periph_clock_enable(gd32_spi->spi_clk);

    switch (gd32_spi->spi_periph)
    {
#ifdef BSP_USING_SPI0
    case SPI0:
        rcu_periph_clock_enable(RCU_GPIOA);
        /* SCK=PA5, MISO=PA6, MOSI=PA7 */
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_7);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
        break;
#endif
#ifdef BSP_USING_SPI1
    case SPI1:
        rcu_periph_clock_enable(RCU_GPIOB);
        /* SCK=PB13, MISO=PB14, MOSI=PB15 */
        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13 | GPIO_PIN_15);
        gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
        break;
#endif
#ifdef BSP_USING_SPI2
    case SPI2:
        rcu_periph_clock_enable(RCU_GPIOB);
        rcu_periph_clock_enable(RCU_AF);
        /* PB3(JTDO)/PB4(NJTRST) are JTAG pins by default; remap releases them
           for SPI2. Side effect: JTAG-DP is disabled, only SW-DP remains for
           debugging. PA15(JTDI) is also freed. */
        gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);
        /* SCK=PB3, MISO=PB4, MOSI=PB5 */
        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3 | GPIO_PIN_5);
        gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
        break;
#endif
    default:
        break;
    }
}
#endif

#ifdef RT_USING_SERIAL
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    rcu_periph_clock_enable(uart->uart_clk);

    switch (uart->uart_periph)
    {
#ifdef BSP_USING_UART0
    case USART0:
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART3
    case UART3:
        rcu_periph_clock_enable(RCU_GPIOC);
        gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART4
    case UART4:
        rcu_periph_clock_enable(RCU_GPIOC);
        rcu_periph_clock_enable(RCU_GPIOD);
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
