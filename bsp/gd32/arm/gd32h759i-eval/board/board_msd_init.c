/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * 2026-03-16  first implementation for GD32H759
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

    switch (i2c->i2c_periph) {
#ifdef BSP_USING_HARD_I2C0
    case I2C0:
        /* I2C0: PB6(SCL) / PB7(SDA), AF4 */
        rcu_periph_clock_enable(RCU_GPIOB);

        gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_6);
        gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_7);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_6);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_HARD_I2C1
    case I2C1:
        /* I2C1: PH4(SCL) / PB11(SDA), AF4 */
        rcu_periph_clock_enable(RCU_GPIOH);
        rcu_periph_clock_enable(RCU_GPIOB);

        gpio_af_set(GPIOH, GPIO_AF_4, GPIO_PIN_4);
        gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_4);
        gpio_output_options_set(GPIOH, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_4);

        gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_11);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_HARD_I2C2
    case I2C2:
        /* I2C2: PA8(SCL) / PC9(SDA), AF4 */
        rcu_periph_clock_enable(RCU_GPIOA);
        rcu_periph_clock_enable(RCU_GPIOC);

        gpio_af_set(GPIOA, GPIO_AF_4, GPIO_PIN_8);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_8);

        gpio_af_set(GPIOC, GPIO_AF_4, GPIO_PIN_9);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_9);
        break;
#endif
#ifdef BSP_USING_HARD_I2C3
    case I2C3:
        /* I2C3: PF14(SCL) / PF15(SDA), AF4 */
        rcu_periph_clock_enable(RCU_GPIOF);

        gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_14);
        gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_15);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_14);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_14);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_15);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, GPIO_PIN_15);
        break;
#endif
    default:
        rt_kprintf("invalid I2C peripheral. \r\n");
        break;
    }
    i2c_deinit(i2c->i2c_periph);
}
#endif

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

    switch (gd32_spi->spi_periph) {
#ifdef BSP_USING_SPI0
    case SPI0:
        /* SPI0: PA5(SCK) / PA6(MISO) / PA7(MOSI), AF5 */
        rcu_periph_clock_enable(RCU_GPIOA);

        gpio_af_set(GPIOA, GPIO_AF_5, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_SPI1
    case SPI1:
        /* SPI1: PB13(SCK) / PB14(MISO) / PB15(MOSI), AF5 */
        rcu_periph_clock_enable(RCU_GPIOB);

        gpio_af_set(GPIOB, GPIO_AF_5, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
        break;
#endif
#ifdef BSP_USING_SPI2
    case SPI2:
        /* SPI2: PB3(SCK) / PB4(MISO) / PB5(MOSI), AF6 */
        rcu_periph_clock_enable(RCU_GPIOB);

        gpio_af_set(GPIOB, GPIO_AF_6, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
        break;
#endif
#ifdef BSP_USING_SPI3
    case SPI3:
        /* SPI3: PE2(SCK) / PE5(MISO) / PE6(MOSI), AF5 */
        rcu_periph_clock_enable(RCU_GPIOE);

        gpio_af_set(GPIOE, GPIO_AF_5, GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6);
        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6);
        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6);
        break;
#endif
#ifdef BSP_USING_SPI4
    case SPI4:
        /* SPI4: PF7(SCK) / PF8(MISO) / PF9(MOSI), AF5 */
        rcu_periph_clock_enable(RCU_GPIOF);

        gpio_af_set(GPIOF, GPIO_AF_5, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
        break;
#endif
#ifdef BSP_USING_SPI5
    case SPI5:
        /* SPI5: PG13(SCK) / PG12(MISO) / PG14(MOSI), AF5 */
        rcu_periph_clock_enable(RCU_GPIOG);

        gpio_af_set(GPIOG, GPIO_AF_5, GPIO_PIN_13 | GPIO_PIN_12 | GPIO_PIN_14);
        gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13 | GPIO_PIN_12 | GPIO_PIN_14);
        gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_13 | GPIO_PIN_12 | GPIO_PIN_14);
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
  * @brief  UART GPIO Initialization
  * @param  uart: UART handle pointer
  * @retval None
  */
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    /* enable USART clock */
    rcu_periph_clock_enable(uart->uart_clk);

    switch (uart->uart_periph) {
#ifdef BSP_USING_UART0
    case USART0:
        /* USART0: PA9(TX) / PA10(RX), AF7 */
        rcu_periph_clock_enable(RCU_GPIOA);

        gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9);
        gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_10);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_9);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_10);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        /* USART1: PA2(TX) / PA3(RX), AF7 */
        rcu_periph_clock_enable(RCU_GPIOA);

        gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_2);
        gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_3);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_2);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_3);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        /* USART2: PB10(TX) / PB11(RX), AF7 */
        rcu_periph_clock_enable(RCU_GPIOB);

        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_10);
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_11);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_10);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART3
    case UART3:
        /* UART3: PC10(TX) / PC11(RX), AF8 */
        rcu_periph_clock_enable(RCU_GPIOC);

        gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_10);
        gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_11);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_10);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_11);
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
