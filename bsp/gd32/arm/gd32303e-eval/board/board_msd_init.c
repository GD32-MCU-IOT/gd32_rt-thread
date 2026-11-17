/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-29     RT-Thread    first implementation for GD32303E
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "drv_hard_i2c.h"
#include "drv_spi.h"
#include "drv_usart.h"
#include "drv_pwm.h"

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
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);
        break;
#endif
#ifdef BSP_USING_HARD_I2C1
    case I2C1:
        rcu_periph_clock_enable(RCU_GPIOB);
        gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_10 | GPIO_PIN_11);
        break;
#endif
    default:
        break;
    }
}
#endif

#ifdef RT_USING_SPI
/**
  * @brief  SPI Initialization
  * @param  gd32_spi: SPI BUS
  * @retval None
  */
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

#if defined RT_USING_SERIAL
/**
  * @brief  UART GPIO Initialization
  * @param  uart: UART handle pointer
  * @retval None
  */
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    rcu_periph_clock_enable(uart->uart_clk);

    switch (uart->uart_periph)
    {
#ifdef BSP_USING_UART0
    case USART0:
        rcu_periph_clock_enable(RCU_GPIOA);
        /* TX=PA9, RX=PA10 */
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        break;
#endif
#ifdef BSP_USING_UART1
    case USART1:
        rcu_periph_clock_enable(RCU_GPIOA);
        /* TX=PA2, RX=PA3 */
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
        break;
#endif
#ifdef BSP_USING_UART2
    case USART2:
        rcu_periph_clock_enable(RCU_GPIOB);
        /* TX=PB10, RX=PB11 */
        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART3
    case UART3:
        rcu_periph_clock_enable(RCU_GPIOC);
        /* TX=PC10, RX=PC11 */
        gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        break;
#endif
#ifdef BSP_USING_UART4
    case UART4:
        rcu_periph_clock_enable(RCU_GPIOC);
        rcu_periph_clock_enable(RCU_GPIOD);
        /* TX=PC12, RX=PD2 */
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

#ifdef RT_USING_PWM
/**
  * @brief  PWM GPIO Initialization
  * @note   Default (not remapped) TIMER pins. Channels sharing a pin with
  *         another peripheral depend on it being disabled in board/Kconfig.
  * @param  timer_periph: TIMERx
  * @param  channel_mask: enabled channels, bit0~bit3 for channel 1~4
  * @retval RT_EOK on success, -RT_EINVAL if the timer is not supported
  */
rt_err_t gd32_pwm_gpio_init(rt_uint32_t timer_periph, rt_uint8_t channel_mask)
{
    rcu_periph_clock_enable(RCU_AF);

    switch (timer_periph)
    {
#ifdef BSP_USING_PWM0
    case TIMER0:
        rcu_periph_clock_enable(RCU_GPIOA);
        if ((channel_mask & (1U << 0)) != 0U)
        {
            /* TIMER0_CH0=PA8 */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
        }
        if ((channel_mask & (1U << 1)) != 0U)
        {
            /* TIMER0_CH1=PA9
             * WARNING: Due to pin sharing conflict, PWM0 channel2 and UART0 TX cannot be enabled simultaneously. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
        }
        if ((channel_mask & (1U << 2)) != 0U)
        {
            /* TIMER0_CH2=PA10
             * WARNING: Due to pin sharing conflict, PWM0 channel3 and UART0 RX cannot be enabled simultaneously. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        }
        if ((channel_mask & (1U << 3)) != 0U)
        {
            /* TIMER0_CH3=PA11
             * WARNING: Due to pin sharing conflict, PWM0 channel4 and USB DM cannot be enabled simultaneously. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
        }
        return RT_EOK;
#endif
#ifdef BSP_USING_PWM1
    case TIMER1:
        rcu_periph_clock_enable(RCU_GPIOA);
        if ((channel_mask & (1U << 0)) != 0U)
        {
            /* TIMER1_CH0=PA0
             * WARNING: PA0 is also connected to the WAKEUP key on this board. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
        }
        if ((channel_mask & (1U << 1)) != 0U)
        {
            /* TIMER1_CH1=PA1 */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
        }
        if ((channel_mask & (1U << 2)) != 0U)
        {
            /* TIMER1_CH2=PA2
             * WARNING: Due to pin sharing conflict, PWM1 channel3 and UART1 TX cannot be enabled simultaneously. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
        }
        if ((channel_mask & (1U << 3)) != 0U)
        {
            /* TIMER1_CH3=PA3
             * WARNING: Due to pin sharing conflict, PWM1 channel4 and UART1 RX cannot be enabled simultaneously. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
        }
        return RT_EOK;
#endif
#ifdef BSP_USING_PWM2
    case TIMER2:
        rcu_periph_clock_enable(RCU_GPIOA);
        rcu_periph_clock_enable(RCU_GPIOB);
        if ((channel_mask & (1U << 0)) != 0U)
        {
            /* TIMER2_CH0=PA6
             * WARNING: Due to pin sharing conflict, PWM2 channel1 and SPI0 MISO cannot be enabled simultaneously. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
        }
        if ((channel_mask & (1U << 1)) != 0U)
        {
            /* TIMER2_CH1=PA7
             * WARNING: Due to pin sharing conflict, PWM2 channel2 and SPI0 MOSI cannot be enabled simultaneously. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
        }
        if ((channel_mask & (1U << 2)) != 0U)
        {
            /* TIMER2_CH2=PB0 */
            gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
        }
        if ((channel_mask & (1U << 3)) != 0U)
        {
            /* TIMER2_CH3=PB1 */
            gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
        }
        return RT_EOK;
#endif
#ifdef BSP_USING_PWM3
    case TIMER3:
        rcu_periph_clock_enable(RCU_GPIOB);
        if ((channel_mask & (1U << 0)) != 0U)
        {
            /* TIMER3_CH0=PB6
             * WARNING: Due to pin sharing conflict, PWM3 channel1 and I2C0 SCL cannot be enabled simultaneously. */
            gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
        }
        if ((channel_mask & (1U << 1)) != 0U)
        {
            /* TIMER3_CH1=PB7
             * WARNING: Due to pin sharing conflict, PWM3 channel2 and I2C0 SDA cannot be enabled simultaneously. */
            gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
        }
        if ((channel_mask & (1U << 2)) != 0U)
        {
            /* TIMER3_CH2=PB8
             * WARNING: Due to pin sharing conflict, PWM3 channel3 and soft I2C1 SCL (default PB8) cannot be enabled simultaneously. */
            gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
        }
        if ((channel_mask & (1U << 3)) != 0U)
        {
            /* TIMER3_CH3=PB9
             * WARNING: Due to pin sharing conflict, PWM3 channel4 and soft I2C1 SDA (default PB9) cannot be enabled simultaneously. */
            gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
        }
        return RT_EOK;
#endif
#ifdef BSP_USING_PWM4
    case TIMER4:
        rcu_periph_clock_enable(RCU_GPIOA);
        if ((channel_mask & (1U << 0)) != 0U)
        {
            /* TIMER4_CH0=PA0
             * WARNING: Due to pin sharing conflict, PWM4 channel1 and PWM1 channel1 cannot be enabled simultaneously.
             * PA0 is also connected to the WAKEUP key on this board. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
        }
        if ((channel_mask & (1U << 1)) != 0U)
        {
            /* TIMER4_CH1=PA1
             * WARNING: Due to pin sharing conflict, PWM4 channel2 and PWM1 channel2 cannot be enabled simultaneously. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
        }
        if ((channel_mask & (1U << 2)) != 0U)
        {
            /* TIMER4_CH2=PA2
             * WARNING: Due to pin sharing conflict, PWM4 channel3 cannot be enabled with UART1 TX or PWM1 channel3. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
        }
        if ((channel_mask & (1U << 3)) != 0U)
        {
            /* TIMER4_CH3=PA3
             * WARNING: Due to pin sharing conflict, PWM4 channel4 cannot be enabled with UART1 RX or PWM1 channel4. */
            gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
        }
        return RT_EOK;
#endif
#ifdef BSP_USING_PWM7
    case TIMER7:
        rcu_periph_clock_enable(RCU_GPIOC);
        if ((channel_mask & (1U << 0)) != 0U)
        {
            /* TIMER7_CH0=PC6
             * WARNING: PC6 is also connected to I2S1 MCK (audio codec) on this board. */
            gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
        }
        if ((channel_mask & (1U << 1)) != 0U)
        {
            /* TIMER7_CH1=PC7 */
            gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
        }
        if ((channel_mask & (1U << 2)) != 0U)
        {
            /* TIMER7_CH2=PC8
             * WARNING: Due to pin sharing conflict, PWM7 channel3 and SDIO D0 cannot be enabled simultaneously. */
            gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
        }
        if ((channel_mask & (1U << 3)) != 0U)
        {
            /* TIMER7_CH3=PC9
             * WARNING: Due to pin sharing conflict, PWM7 channel4 and SDIO D1 cannot be enabled simultaneously. */
            gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
        }
        return RT_EOK;
#endif
    default:
        return -RT_EINVAL;
    }
}
#endif
