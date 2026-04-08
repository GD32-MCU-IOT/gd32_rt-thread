/*!
    \file    gd32m53x_gpio.c
    \brief   GPIO driver

    \version 2026-03-04, V1.0.0, firmware for GD32M53x
*/

/*
    Copyright (c) 2026, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32m53x_gpio.h"

#define GPIO_MODE_PMASK           ((uint32_t)0x00000003U)
#define GPIO_PULL_MODE_PMASK      ((uint32_t)0x00000003U)
#define GPIO_OSPEED_PMASK         ((uint32_t)0x00000003U)
#define GPIO_AF_PMASK             ((uint32_t)0x0000000FU)

/*!
    \brief      reset GPIO port (API_ID(0x0001U))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[out] none
    \retval     none
*/
void gpio_deinit(uint32_t gpio_periph)
{
    switch(gpio_periph) {
    case GPIOA:
        /* reset GPIOA */
        rcu_periph_reset_enable(RCU_GPIOARST);
        rcu_periph_reset_disable(RCU_GPIOARST);
        break;
    case GPIOB:
        /* reset GPIOB */
        rcu_periph_reset_enable(RCU_GPIOBRST);
        rcu_periph_reset_disable(RCU_GPIOBRST);
        break;
    case GPIOC:
        /* reset GPIOC */
        rcu_periph_reset_enable(RCU_GPIOCRST);
        rcu_periph_reset_disable(RCU_GPIOCRST);
        break;
    case GPIOD:
        /* reset GPIOD */
        rcu_periph_reset_enable(RCU_GPIODRST);
        rcu_periph_reset_disable(RCU_GPIODRST);
        break;
    case GPIOE:
        /* reset GPIOE */
        rcu_periph_reset_enable(RCU_GPIOERST);
        rcu_periph_reset_disable(RCU_GPIOERST);
        break;
    case GPIOF:
        /* reset GPIOF */
        rcu_periph_reset_enable(RCU_GPIOFRST);
        rcu_periph_reset_disable(RCU_GPIOFRST);
        break;
    case GPIOG:
        /* reset GPIOG */
        rcu_periph_reset_enable(RCU_GPIOGRST);
        rcu_periph_reset_disable(RCU_GPIOGRST);
        break;
    case GPION:
        /* reset GPION */
        rcu_periph_reset_enable(RCU_GPIONRST);
        rcu_periph_reset_disable(RCU_GPIONRST);
        break;
    default:
        break;
    }
}

/*!
    \brief      set GPIO mode (API_ID(0x0002U))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  mode: gpio pin mode
                only one parameter can be selected which is shown as below:
      \arg        GPIO_MODE_INPUT: input mode
      \arg        GPIO_MODE_OUTPUT: output mode
      \arg        GPIO_MODE_AF: alternate function mode
      \arg        GPIO_MODE_ANALOG: analog mode
    \param[in]  pull_up_down: gpio pin with pull-up or pull-down resistor
                only one parameter can be selected which is shown as below:
      \arg        GPIO_PUPD_NONE: floating mode, no pull-up and pull-down resistors
      \arg        GPIO_PUPD_PULLUP: with pull-up resistor
      \arg        GPIO_PUPD_PULLDOWN:with pull-down resistor
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_mode_set(uint32_t gpio_periph, uint32_t mode, uint32_t pull_up_down, uint32_t pin)
{
    uint16_t i;
    uint32_t ctl, pupd;

    ctl = GPIO_CTL(gpio_periph);
    pupd = GPIO_PUD(gpio_periph);

    for(i = 0U; i < 16U; i++) {
        if((((uint32_t)1U << i)) & pin) {
            /* clear the specified pin mode bits */
            ctl &= ~GPIO_MODE_MASK(i);
            /* set the specified pin mode bits */
            ctl |= GPIO_MODE_SET(i, (mode & GPIO_MODE_PMASK));

            /* clear the specified pin pupd bits */
            pupd &= ~GPIO_PUPD_MASK(i);
            /* set the specified pin pupd bits */
            pupd |= GPIO_PUPD_SET(i, (pull_up_down & GPIO_PULL_MODE_PMASK));
        }
    }

    GPIO_CTL(gpio_periph) = ctl;
    GPIO_PUD(gpio_periph) = pupd;
}

/*!
    \brief      set GPIO output type and speed (API_ID(0x0003U))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  otype: gpio pin output mode
                only one parameter can be selected which is shown as below:
      \arg        GPIO_OTYPE_PP: push pull mode
      \arg        GPIO_OTYPE_OD: open drain mode
    \param[in]  speed: gpio pin output max speed
                only one parameter can be selected which is shown as below:
      \arg        GPIO_OSPEED_LOW: output max speed low drive
      \arg        GPIO_OSPEED_HIGH: output max speed high drive
      \arg        GPIO_OSPEED_LARGE_CURRENT: output max speed high current drive
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_output_options_set(uint32_t gpio_periph, uint8_t otype, uint32_t speed, uint32_t pin)
{
    uint16_t i;
    uint32_t ospeed;

    if(GPIO_OTYPE_OD == (otype)) {
        GPIO_OMODE(gpio_periph) |= (uint32_t)pin;
    } else {
        GPIO_OMODE(gpio_periph) &= (uint32_t)(~pin);
    }

    /* get the specified pin output speed bits value */
    ospeed = GPIO_OSPD(gpio_periph);

    for(i = 0U; i < 16U; i++) {
        if(((uint32_t)1U << i) & pin) {
            /* clear the specified pin output speed bits */
            ospeed &= ~GPIO_OSPEED_MASK(i);
            /* set the specified pin output speed bits */
            ospeed |= GPIO_OSPEED_SET(i, (speed & GPIO_OSPEED_PMASK));
        }
    }
    GPIO_OSPD(gpio_periph) = ospeed;
}

/*!
    \brief      set GPIO pin bit (API_ID(0x0004U))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_set(uint32_t gpio_periph, uint32_t pin)
{

    GPIO_BOP(gpio_periph) = (uint32_t)(pin & GPIO_PIN_ALL);
}

/*!
    \brief      reset GPIO pin bit (API_ID(0x0005U))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_reset(uint32_t gpio_periph, uint32_t pin)
{
    GPIO_BC(gpio_periph) = (uint32_t)(pin & GPIO_PIN_ALL);
}

/*!
    \brief      write data to the specified GPIO pin (API_ID(0x0006U))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[in]  bit_value: SET or RESET
                only one parameter can be selected which is shown as below:
      \arg        RESET: clear the port pin
      \arg        SET: set the port pin
    \param[out] none
    \retval     none
*/
void gpio_bit_write(uint32_t gpio_periph, uint32_t pin, bit_status bit_value)
{

    if(RESET != bit_value) {
        GPIO_BOP(gpio_periph) = (uint32_t)(pin & GPIO_PIN_ALL);
    } else {
        GPIO_BC(gpio_periph) = (uint32_t)(pin & GPIO_PIN_ALL);
    }
}

/*!
    \brief      write data to the specified GPIO port (API_ID(0x0007U))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  data: specify the value to be written to the port output control register
    \param[out] none
    \retval     none
*/
void gpio_port_write(uint32_t gpio_periph, uint16_t data)
{

    GPIO_OCTL(gpio_periph) = (uint32_t)data;

}

/*!
    \brief      get GPIO pin input status (API_ID(0x0008U))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus gpio_input_bit_get(uint32_t gpio_periph, uint32_t pin)
{
    FlagStatus reval = RESET;
    if((uint32_t)RESET != (GPIO_ISTAT(gpio_periph) & (pin & GPIO_PIN_ALL))) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      get GPIO port input status (API_ID(0x0009U))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[out] none
    \retval     state of GPIO all pins
*/
uint16_t gpio_input_port_get(uint32_t gpio_periph)
{
    uint16_t reval = 0U;

    reval = ((uint16_t)GPIO_ISTAT(gpio_periph));
    return reval;
}

/*!
    \brief      get GPIO pin output status (API_ID(0x000AU))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus gpio_output_bit_get(uint32_t gpio_periph, uint32_t pin)
{
    FlagStatus reval = RESET;
    if((uint32_t)RESET != (GPIO_OCTL(gpio_periph) & (pin & GPIO_PIN_ALL))) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      get GPIO port output status (API_ID(0x000BU))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[out] none
    \retval     state of GPIO all pins
*/
uint16_t gpio_output_port_get(uint32_t gpio_periph)
{
    uint16_t reval = 0U;
    reval = ((uint16_t)GPIO_OCTL(gpio_periph));
    return reval;
}

/*!
    \brief      set GPIO alternate function (API_ID(0x000CU))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  alt_func_num: GPIO pin af function, please refer to specific device datasheet
                only one parameter can be selected which is shown as below:
      \arg        GPIO_AF_0: CK_OUT, TRACECK, TRACED0, TRACED1, TRACED2, TRACED3, CPTIMERW
      \arg        GPIO_AF_1: TIMER0, TIMER1, TIMER2, TIMER7
      \arg        GPIO_AF_2: TIMER_ETI, TIMER0, TIMER7
      \arg        GPIO_AF_3: TIMER0, TIMER2, TIMER7
      \arg        GPIO_AF_4: TIMER0, TIMER7, POC
      \arg        GPIO_AF_5: CFMUREF, ADC0, ADC2, ADCSM1, ADCSM2
      \arg        GPIO_AF_6: UART0, UART1, UART2, UART3, POC
      \arg        GPIO_AF_7: UART3, ADC0, ADC2, TIMER0, TIMER7, I2C
      \arg        GPIO_AF_8: CMP0, CMP1, CMP2, CMP3, I2C, CAN
      \arg        GPIO_AF_9: TIMER2, SPI
      \arg        GPIO_AF_10: GTOC0, GPTIMER0, GPTIMER1, UART3, ADCSM3, ADCSM4
      \arg        GPIO_AF_11: GTOC0, GTOC1, SPI, GPTIMER0, GPTIMER1
      \arg        GPIO_AF_12: GTOC2, GPTIMER0, GPTIMER1
      \arg        GPIO_AF_13: GTOC2, GTOC3, CAN, GPTIMER0, GPTIMER1
      \arg        GPIO_AF_14: GPTIMER0, GPTIMER1
      \arg        GPIO_AF_15: EVENT_OUT
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_af_set(uint32_t gpio_periph, uint32_t alt_func_num, uint32_t pin)
{
    uint16_t i;
    uint32_t afrl, afrh;

    afrl = GPIO_AFSEL0(gpio_periph);
    afrh = GPIO_AFSEL1(gpio_periph);

    for(i = 0U; i < 8U; i++) {
        if(((uint32_t)1U << i) & (pin & GPIO_PIN_ALL)) {
            /* clear the specified pin alternate function bits */
            afrl &= ~GPIO_AFR_MASK(i);
            afrl |= GPIO_AFR_SET(i, (alt_func_num & GPIO_AF_PMASK));
        }
    }

    for(i = 8U; i < 16U; i++) {
        if(((uint32_t)1U << i) & (pin & GPIO_PIN_ALL)) {
            /* clear the specified pin alternate function bits */
            afrh &= ~GPIO_AFR_MASK(i - 8U);
            afrh |= GPIO_AFR_SET(i - 8U, (alt_func_num & GPIO_AF_PMASK));
        }
    }

    GPIO_AFSEL0(gpio_periph) = afrl;
    GPIO_AFSEL1(gpio_periph) = afrh;
}
/*!
    \brief      lock GPIO pin bit (API_ID(0x000DU))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_pin_lock(uint32_t gpio_periph, uint32_t pin)
{
    uint32_t lock = 0x00010000U;
    lock |= (pin & GPIO_PIN_ALL);

    /* lock key writing sequence: write 1->write 0->write 1->read 0->read 1 */
    GPIO_LOCK(gpio_periph) = (uint32_t)lock;
    GPIO_LOCK(gpio_periph) = (uint32_t)(pin & GPIO_PIN_ALL);
    GPIO_LOCK(gpio_periph) = (uint32_t)lock;
    GPIO_LOCK(gpio_periph);
    GPIO_LOCK(gpio_periph);
}

/*!
    \brief      toggle GPIO pin status (API_ID(0x000EU))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_toggle(uint32_t gpio_periph, uint32_t pin)
{
    GPIO_TG(gpio_periph) = (uint32_t)(pin & GPIO_PIN_ALL);
}

/*!
    \brief      toggle GPIO port status (API_ID(0x000FU))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[out] none
    \retval     none
*/
void gpio_port_toggle(uint32_t gpio_periph)
{
    GPIO_TG(gpio_periph) = 0x0000FFFFU;
}

/*!
    \brief      enable hold GPIO pin data output (API_ID(0x00010U))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_hold_enable(uint32_t gpio_periph, uint32_t pin)
{
    GPIO_HLD(gpio_periph) |= (uint32_t)(pin & GPIO_PIN_ALL);
}

/*!
    \brief      disable hold GPIO pin data output (API_ID(0x00011U))
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G,N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C,D,E,F,G,N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_hold_disable(uint32_t gpio_periph, uint32_t pin)
{

    GPIO_HLD(gpio_periph) &= (~(uint32_t)(pin & GPIO_PIN_ALL));
}

/*!
    \brief      disable tsel function (API_ID(0x00012U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_tsel_function_disable(void)
{
    GPIO_FUNCSEL |= GPIO_FUNCSEL_GPTSEL;
}

/*!
    \brief      enable tsel function (API_ID(0x00013U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_tsel_function_enable(void)
{
    GPIO_FUNCSEL &= (~GPIO_FUNCSEL_GPTSEL);
}

/*!
    \brief      disable one line function (API_ID(0x00014U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_one_line_function_disable(void)
{
    GPIO_FUNCSEL |= GPIO_FUNCSEL_GPBOOT;
}

/*!
    \brief      enable one line function (API_ID(0x00015U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_one_line_function_enable(void)
{
    GPIO_FUNCSEL &= (~GPIO_FUNCSEL_GPBOOT);
}

/*!
    \brief      enable data output function (API_ID(0x00016U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_sample_hold_enable(void)
{
    GPIO_HLDCTL |= GPIO_HLDCTL_SMP;
}
