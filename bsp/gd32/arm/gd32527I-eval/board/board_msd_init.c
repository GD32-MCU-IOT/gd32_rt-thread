/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-01-05     RT-Thread    first implementation for GD32F527I
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
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_6 | GPIO_PIN_7);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6 | GPIO_PIN_7);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, GPIO_PIN_6 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_HARD_I2C1
    case I2C1:
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, GPIO_PIN_10 | GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_HARD_I2C2
    case I2C2:
        rcu_periph_clock_enable(RCU_GPIOH);
        gpio_af_set(GPIOH, GPIO_AF_4, GPIO_PIN_7 | GPIO_PIN_8);
        gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7 | GPIO_PIN_8);
        gpio_output_options_set(GPIOH, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, GPIO_PIN_7 | GPIO_PIN_8);
        break;
#endif
#ifdef BSP_USING_HARD_I2C3
    case I2C3:
        /* I2C3: SCL=PF14, SDA=PF15, AF4 */
        rcu_periph_clock_enable(RCU_GPIOF);
        gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_14 | GPIO_PIN_15);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_14 | GPIO_PIN_15);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, GPIO_PIN_14 | GPIO_PIN_15);
        break;
#endif
#ifdef BSP_USING_HARD_I2C4
    case I2C4:
        /* I2C4 alternate pins: SCL=PF1, SDA=PF0, AF4 */
        rcu_periph_clock_enable(RCU_GPIOF);
        gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_0 | GPIO_PIN_1);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0 | GPIO_PIN_1);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, GPIO_PIN_0 | GPIO_PIN_1);
        break;
#endif
#ifdef BSP_USING_HARD_I2C5
    case I2C5:
        /* I2C5: SCL=PF11, SDA=PF12, AF4 */
        rcu_periph_clock_enable(RCU_GPIOF);
        gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_11 | GPIO_PIN_12);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11 | GPIO_PIN_12);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, GPIO_PIN_11 | GPIO_PIN_12);
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
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_af_set(GPIOA, GPIO_AF_5, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_SPI1
    case SPI1:
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_5, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
        break;
#endif
#ifdef BSP_USING_SPI2
    case SPI2:
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_6, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
        break;
#endif
#ifdef BSP_USING_SPI3
    case SPI3:
        rcu_periph_clock_enable(RCU_GPIOE);
        gpio_af_set(GPIOE, GPIO_AF_5, GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6);
        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6);
        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6);
        break;
#endif
#ifdef BSP_USING_SPI4
    case SPI4:
        rcu_periph_clock_enable(RCU_GPIOF);
        gpio_af_set(GPIOF, GPIO_AF_5, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
        break;
#endif
#ifdef BSP_USING_SPI5
    case SPI5:
        rcu_periph_clock_enable(RCU_GPIOG);
        gpio_af_set(GPIOG, GPIO_AF_5, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14);
        gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14);
        gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14);
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
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9 | GPIO_PIN_10);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9 | GPIO_PIN_10);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_9 | GPIO_PIN_10);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_2 | GPIO_PIN_3);
        gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2 | GPIO_PIN_3);
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_2 | GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_10 | GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART3
    case UART3:
        rcu_periph_clock_enable(RCU_GPIOC);
        gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10 | GPIO_PIN_11);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_10 | GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART4
    case UART4:
        rcu_periph_clock_enable(RCU_GPIOC);
        rcu_periph_clock_enable(RCU_GPIOD);
        gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_12);
        gpio_af_set(GPIOD, GPIO_AF_8, GPIO_PIN_2);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_12);
        gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_12);
        gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_2);
        break;
#endif
#ifdef BSP_USING_UART5
    case USART5:
        rcu_periph_clock_enable(RCU_GPIOC);
        gpio_af_set(GPIOC, GPIO_AF_8, GPIO_PIN_6 | GPIO_PIN_7);
        gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6 | GPIO_PIN_7);
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_6 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_UART6
    case UART6:
        rcu_periph_clock_enable(RCU_GPIOE);
        gpio_af_set(GPIOE, GPIO_AF_8, GPIO_PIN_7 | GPIO_PIN_8);
        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7 | GPIO_PIN_8);
        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_7 | GPIO_PIN_8);
        break;
#endif
#ifdef BSP_USING_UART7
    case UART7:
        rcu_periph_clock_enable(RCU_GPIOE);
        gpio_af_set(GPIOE, GPIO_AF_8, GPIO_PIN_0 | GPIO_PIN_1);
        gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0 | GPIO_PIN_1);
        gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_0 | GPIO_PIN_1);
        break;
#endif
    default:
        break;
    }

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}
#endif

#ifdef BSP_USING_SDRAM
/**
  * @brief  This function initializes the SDRAM GPIO pins.
  *         Overrides the weak default in drv_sdram.c because GD32F527I-EVAL
  *         uses a different pin mapping than GD32F4xx boards:
  *           SDNWE  -> PH5  (F4xx: PC0)
  *           SDCKE0 -> PC5  (F4xx: PC3)
  *           SDNE0  -> PC2  (same)
  */
void gd32_sdram_gpio_init(void)
{
    /* enable EXMC clock */
    rcu_periph_clock_enable(RCU_EXMC);

    /* enable GPIO clocks for SDRAM pins */
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);
    rcu_periph_clock_enable(RCU_GPIOH);

    /* SDNE0(PC2), SDCKE0(PC5) */
    gpio_af_set(GPIOC, GPIO_AF_12, GPIO_PIN_2 | GPIO_PIN_5);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2 | GPIO_PIN_5);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2 | GPIO_PIN_5);

    /* D2(PD0), D3(PD1), D13(PD8), D14(PD9), D15(PD10), D0(PD14), D1(PD15) */
    gpio_af_set(GPIOD, GPIO_AF_12, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_8 | GPIO_PIN_9 |
                                   GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_8 | GPIO_PIN_9 |
                                                          GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_8 | GPIO_PIN_9 |
                                                                      GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15);

    /* NBL0(PE0), NBL1(PE1), D4-D12(PE7-PE15) */
    gpio_af_set(GPIOE, GPIO_AF_12, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_7  | GPIO_PIN_8 |
                                   GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
                                   GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_7  | GPIO_PIN_8 |
                                                          GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
                                                          GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_7  | GPIO_PIN_8 |
                                                                      GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
                                                                      GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

    /* A0-A5(PF0-PF5), NRAS(PF11), A6-A9(PF12-PF15) */
    gpio_af_set(GPIOF, GPIO_AF_12, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  |
                                   GPIO_PIN_4  | GPIO_PIN_5  | GPIO_PIN_11 | GPIO_PIN_12 |
                                   GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  |
                                                          GPIO_PIN_4  | GPIO_PIN_5  | GPIO_PIN_11 | GPIO_PIN_12 |
                                                          GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  |
                                                                      GPIO_PIN_4  | GPIO_PIN_5  | GPIO_PIN_11 | GPIO_PIN_12 |
                                                                      GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

    /* A10(PG0), A11(PG1), A12(PG2), A14(PG4), A15(PG5), SDCLK(PG8), NCAS(PG15) */
    gpio_af_set(GPIOG, GPIO_AF_12, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 |
                                   GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15);
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 |
                                                          GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 |
                                                                      GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15);

    /* SDNWE(PH5) */
    gpio_af_set(GPIOH, GPIO_AF_12, GPIO_PIN_5);
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_5);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
}
#endif
