/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-24     RT-Thread    first implementation for GD32F207I-EVAL
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "drv_usart.h"
#include "drv_hard_i2c.h"
#include "drv_spi.h"

/* GD32F207I-EVAL board-level MSP initialization.
 *
 * SOC_SERIES_GD32F20x has been added to the exclusion list in
 * drv_usart.c / drv_usart.h, so the shared driver does NOT compile
 * gd32_uart_gpio_init() for GD32F20x. Instead, this file provides the
 * board-specific UART pin configuration using the legacy GD32F20x GPIO API
 * (gpio_init / GPIO_MODE_AF_PP / GPIO_MODE_IN_FLOATING / GPIO_OSPEED_50MHZ),
 * matching the official GD32F207I_EVAL demo suites.
 *
 * Pin assignments (same as GD32F20x Demo Suites):
 *   USART0: PA9 (TX) / PA10 (RX)
 *   USART1: PA2 (TX) / PA3  (RX)
 *   USART2: PB10(TX) / PB11(RX)
 *   UART3 : PC10(TX) / PC11(RX)
 *   UART4 : PC12(TX) / PD2  (RX)
 *   USART5: PC6 (TX) / PC7  (RX)  (requires AFIO remap)
 */

void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    /* enable USART clock */
    rcu_periph_clock_enable(uart->uart_clk);

    switch(uart->uart_periph) {
#ifdef BSP_USING_UART0
    case USART0:
        /* USART0: TX=PA9, RX=PA10 */
        rcu_periph_clock_enable(RCU_GPIOA);

        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        /* USART1: TX=PA2, RX=PA3 */
        rcu_periph_clock_enable(RCU_GPIOA);

        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        /* USART2: TX=PB10, RX=PB11 */
        rcu_periph_clock_enable(RCU_GPIOB);

        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART3
    case UART3:
        /* UART3: TX=PC10, RX=PC11 */
        rcu_periph_clock_enable(RCU_GPIOC);

        gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART4
    case UART4:
        /* UART4: TX=PC12, RX=PD2 */
        rcu_periph_clock_enable(RCU_GPIOC);
        rcu_periph_clock_enable(RCU_GPIOD);

        gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
        gpio_init(GPIOD, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
        break;
#endif
#ifdef BSP_USING_UART5
    case USART5:
        /* USART5: TX=PC6, RX=PC7 */
        rcu_periph_clock_enable(RCU_GPIOC);
        rcu_periph_clock_enable(RCU_AF);

        gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
        gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_7);

        gpio_afio_port_config(AFIO_PC6_USART5_CFG, ENABLE);
        gpio_afio_port_config(AFIO_PC7_USART5_CFG, ENABLE);
        break;
#endif
    default:
        rt_kprintf("invalid UART peripheral. \r\n");
        break;
    }

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}

#ifdef RT_USING_I2C
/**
  * @brief  This function initializes the i2c pin.
  * @param  i2c
  * @retval None
  *
  * SOC_SERIES_GD32F20x has been added to the exclusion list in
  * drv_hard_i2c.c / drv_hard_i2c.h, so the shared driver does NOT compile
  * gd32_i2c_gpio_init() for GD32F20x. Instead, this file provides the
  * board-specific I2C pin configuration using the legacy GD32F20x GPIO API
  * (gpio_init / GPIO_MODE_AF_OD / GPIO_OSPEED_50MHZ), matching the official
  * GD32F207I_EVAL Demo Suite 11_I2C_EEPROM.
  *
  * Pin assignments (GD32F207I-EVAL, no AFIO remap):
  *   I2C0: PB6 (SCL) / PB7 (SDA)   <- EEPROM (AT24C02) on the board
  *   I2C1: PB10(SCL) / PB11(SDA)
  */
void gd32_i2c_gpio_init(const struct gd32_i2c_bus *i2c)
{
    /* enable I2C clock */
    rcu_periph_clock_enable(i2c->i2c_clk);

    switch(i2c->i2c_periph) {
#ifdef BSP_USING_HARD_I2C0
    case I2C0:
        /* I2C0: SCL=PB6, SDA=PB7 */
        rcu_periph_clock_enable(RCU_GPIOB);

        gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
        gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_HARD_I2C1
    case I2C1:
        /* I2C1: SCL=PB10, SDA=PB11 */
        rcu_periph_clock_enable(RCU_GPIOB);

        gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
    default:
        rt_kprintf("invalid I2C peripheral. \r\n");
        break;
    }
}
#endif /* RT_USING_I2C */

#ifdef RT_USING_SPI
/**
* @brief SPI Initialization
* @param gd32_spi: SPI BUS
* @retval None
*
* SOC_SERIES_GD32F20x has been added to the exclusion list in
* drv_spi.c / drv_spi.h, so the shared driver does NOT compile
* gd32_spi_init() for GD32F20x. Instead, this file provides the
* board-specific SPI pin configuration using the legacy GD32F20x GPIO API
* (gpio_init / GPIO_MODE_AF_PP / GPIO_MODE_IN_FLOATING / GPIO_OSPEED_50MHZ),
* matching the official GD32F207I_EVAL Demo Suite 12_SPI_Quad_Flash (standard
* SPI mode, not Quad).
*
* Pin assignments (GD32F207I-EVAL):
*   SPI0: SCK=PA5, MISO=PA6, MOSI=PA7, CS=PB1 (CS handled by rt_spi_device)
*   SPI1: SCK=PB13, MISO=PB14, MOSI=PB15 (not routed on board)
*/
void gd32_spi_init(struct gd32_spi *gd32_spi)
{
    /* enable SPI clock */
    rcu_periph_clock_enable(gd32_spi->spi_clk);

    switch(gd32_spi->spi_periph) {
#ifdef BSP_USING_SPI0
    case SPI0:
        /* SPI0: SCK=PA5, MISO=PA6, MOSI=PA7 */
        rcu_periph_clock_enable(RCU_GPIOA);

        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_SPI1
    case SPI1:
        /* SPI1: SCK=PB13, MISO=PB14, MOSI=PB15 */
        rcu_periph_clock_enable(RCU_GPIOB);

        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
        gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_15);
        break;
#endif
    default:
        rt_kprintf("invalid SPI peripheral. \r\n");
        break;
    }
}
#endif /* RT_USING_SPI */
