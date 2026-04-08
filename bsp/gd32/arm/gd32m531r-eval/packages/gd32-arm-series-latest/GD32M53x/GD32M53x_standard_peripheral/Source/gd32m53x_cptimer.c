/*!
    \file    gd32m53x_cptimer.c
    \brief   definitions for the TIMER

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

#include "gd32m53x_cptimer.h"

/*!
    \brief      deinit a CPTIMER (API_ID(0x0001U))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[out] none
    \retval     none
*/
void cptimer_deinit(uint32_t cptimer_periph)
{
    switch(cptimer_periph) {
    case CPTIMER0:
        /* reset CPTIMER0 */
        rcu_periph_reset_enable(RCU_CPTIMER0RST);
        rcu_periph_reset_disable(RCU_CPTIMER0RST);
        break;
    case CPTIMER1:
        /* reset CPTIMER1 */
        rcu_periph_reset_enable(RCU_CPTIMER1RST);
        rcu_periph_reset_disable(RCU_CPTIMER1RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable a CPTIMER (API_ID(0x0002U))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  counter: CPTIMER_COUNTERx(x=0,1)
    \param[out] none
    \retval     none
*/
void cptimer_enable(uint32_t cptimer_periph, uint32_t counter)
{
    if(counter == CPTIMER_COUNTER0) {
        CPTIMER_CTL0(cptimer_periph) |= (uint32_t)CPTIMER_CTL0_CEN0;
    } else if(counter == CPTIMER_COUNTER1) {
        CPTIMER_CTL0(cptimer_periph) |= (uint32_t)CPTIMER_CTL0_CEN1;
    } else {
        /*illegal parameter*/
    }
}

/*!
    \brief      disable a CPTIMER (API_ID(0x0003U))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  counter: CPTIMER_COUNTERx(x=0,1)
    \param[out] none
    \retval     none
*/
void cptimer_disable(uint32_t cptimer_periph, uint32_t counter)
{
    if(counter == CPTIMER_COUNTER0) {
        CPTIMER_CTL0(cptimer_periph) &= ~(uint32_t)CPTIMER_CTL0_CEN0;
    } else if(counter == CPTIMER_COUNTER1) {
        CPTIMER_CTL0(cptimer_periph) &= ~(uint32_t)CPTIMER_CTL0_CEN1;
    } else {
        /*illegal parameter*/
    }
}

/*!
    \brief      configure CPTIMER autoreload value (API_ID(0x0004U))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  counter: CPTIMER_COUNTERx(x=0,1)
    \param[in]  autoreload: autoreload value, 0~65535
    \param[out] none
    \retval     none
*/
void cptimer_autoreload_value_config(uint32_t cptimer_periph, uint32_t counter, uint16_t autoreload)
{
    if(counter == CPTIMER_COUNTER0) {
        CPTIMER_CNT0CAR(cptimer_periph) = (uint32_t)autoreload;
    } else if(counter == CPTIMER_COUNTER1) {
        CPTIMER_CNT1CAR(cptimer_periph) = (uint32_t)autoreload;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure CPTIMER prescaler (API_ID(0x0005U))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  counter: CPTIMER_COUNTERx(x=0,1)
    \param[in]  prescaler: prescaler value,0~65535
    \param[out] none
    \retval     none
*/
void cptimer_prescaler_config(uint32_t cptimer_periph, uint32_t counter, uint16_t prescaler)
{
    if(counter == CPTIMER_COUNTER0) {
        CPTIMER_CNT0PSC(cptimer_periph) = (uint32_t)prescaler;
    } else if(counter == CPTIMER_COUNTER1) {
        CPTIMER_CNT1PSC(cptimer_periph) = (uint32_t)prescaler;
    } else {
        /*illegal parameter */
    }
}

/*!
    \brief      configure CPTIMER counter register value (API_ID(0x0006U))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  counter: CPTIMER_COUNTERx(x=0,1)
    \param[in]  value: the counter value, 0~65535
    \param[out] none
    \retval     none
*/
void cptimer_counter_value_config(uint32_t cptimer_periph, uint32_t counter, uint16_t value)
{
    if(counter == CPTIMER_COUNTER0) {
        CPTIMER_CNT0(cptimer_periph) = (uint32_t)value;
    } else if(counter == CPTIMER_COUNTER1) {
        CPTIMER_CNT1(cptimer_periph) = (uint32_t)value;
    } else {
        /*illegal parameter */
    }
}

/*!
    \brief      read CPTIMER counter value (API_ID(0x0007U))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  counter: CPTIMER_COUNTERx(x=0,1)
    \param[out] none
    \retval     counter value
*/
uint16_t cptimer_counter_read(uint32_t cptimer_periph, uint32_t counter)
{
    uint16_t count_value = 0U;

    if(counter == CPTIMER_COUNTER0) {
        count_value = (uint16_t)CPTIMER_CNT0(cptimer_periph);
    } else if(counter == CPTIMER_COUNTER1) {
        count_value = (uint16_t)CPTIMER_CNT1(cptimer_periph);
    } else {
        /*illegal parameter */
    }

    return count_value;
}

/*!
    \brief      read CPTIMER prescaler value (API_ID(0x0008U))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  counter: CPTIMER_COUNTERx(x=0,1)
    \param[out] none
    \retval     prescaler register value
*/
uint16_t cptimer_prescaler_read(uint32_t cptimer_periph, uint32_t counter)
{
    uint16_t prescaler = 0U;

    if(counter == CPTIMER_COUNTER0) {
        prescaler = (uint16_t)CPTIMER_CNT0PSC(cptimer_periph);
    } else if(counter == CPTIMER_COUNTER1) {
        prescaler = (uint16_t)CPTIMER_CNT1PSC(cptimer_periph);
    } else {
        /*illegal parameter */
    }

    return prescaler;
}

/*!
    \brief      software generate events (API_ID(0x0009U))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  event: the timer software event generation sources
                one or more parameters can be selected which are shown as below:
      \arg        CPTIMER_EVENT_SRC_UPG0: counter 0 update event generation
      \arg        CPTIMER_EVENT_SRC_UPG1: counter 1 update event generation
    \param[out] none
    \retval     none
*/
void cptimer_event_software_generate(uint32_t cptimer_periph, uint32_t event)
{
    CPTIMER_SWEVG(cptimer_periph) = (uint32_t)event;
}

/*!
    \brief      get CPTIMER flags (API_ID(0x000AU))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  flag: the timer flags
                only one parameter can be selected which is shown as below:
      \arg        CPTIMER_FLAG_CNT0UP: CPTIMER counter 0 update flag
      \arg        CPTIMER_FLAG_CNT1UP: CPTIMER counter 1 update flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cptimer_flag_get(uint32_t cptimer_periph, uint32_t flag)
{
    FlagStatus reval = RESET;

    if(RESET != (CPTIMER_INTF(cptimer_periph) & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      clear TIMER flags (API_ID(0x000BU))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  flag: the timer flags
                 one or more parameters can be selected which are shown as below:
      \arg        CPTIMER_FLAG_CNT0UP: CPTIMER counter 0 update flag
      \arg        CPTIMER_FLAG_CNT1UP: CPTIMER counter 1 update flag
    \param[out] none
    \retval     none
*/
void cptimer_flag_clear(uint32_t cptimer_periph, uint32_t flag)
{
    CPTIMER_INTF(cptimer_periph) = (~(uint32_t)flag);
}

/*!
    \brief      enable the CPTIMER interrupt (API_ID(0x000CU))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  interrupt: timer interrupt enable source
                 one or more parameters can be selected which are shown as below:
      \arg        CPTIMER_INT_CNT0UP: CPTIMER counter 0 update interrupt
      \arg        CPTIMER_INT_CNT1UP: CPTIMER counter 1 update interrupt
    \param[out] none
    \retval     none
*/
void cptimer_interrupt_enable(uint32_t cptimer_periph, uint32_t interrupt)
{
    CPTIMER_INTEN(cptimer_periph) |= interrupt;
}

/*!
    \brief      disable CPTIMER interrupt (API_ID(0x000DU))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  interrupt: timer interrupt enable source
                 one or more parameters can be selected which are shown as below:
      \arg        CPTIMER_INT_CNT0UP: CPTIMER counter 0 update interrupt
      \arg        CPTIMER_INT_CNT1UP: CPTIMER counter 1 update interrupt
    \param[out] none
    \retval     none
*/
void cptimer_interrupt_disable(uint32_t cptimer_periph, uint32_t interrupt)
{
    CPTIMER_INTEN(cptimer_periph) &= ~(uint32_t)(interrupt);
}

/*!
    \brief      get CPTIMER interrupt flag (API_ID(0x000EU))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  int_flag: the timer interrupt bits
                only one parameter can be selected which is shown as below:
      \arg        CPTIMER_INT_FLAG_CNT0UP: CPTIMER counter 0 update interrupt flag
      \arg        CPTIMER_INT_FLAG_CNT1UP: CPTIMER counter 1 update interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cptimer_interrupt_flag_get(uint32_t cptimer_periph, uint32_t int_flag)
{
    uint32_t val;
    FlagStatus reval = RESET;

    val = (CPTIMER_INTEN(cptimer_periph) & int_flag);
    if((RESET != (CPTIMER_INTF(cptimer_periph) & int_flag)) && (RESET != val)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      clear CPTIMER interrupt flag (API_ID(0x000FU))
    \param[in]  cptimer_periph: CPTIMER(x=0,1)
    \param[in]  int_flag: the timer interrupt bits
                one or more parameters can be selected which are shown as below:
      \arg        CPTIMER_INT_FLAG_CNT0UP: CPTIMER counter 0 update interrupt flag
      \arg        CPTIMER_INT_FLAG_CNT1UP: CPTIMER counter 1 update interrupt flag
    \param[out] none
    \retval     none
*/
void cptimer_interrupt_flag_clear(uint32_t cptimer_periph, uint32_t int_flag)
{
    CPTIMER_INTF(cptimer_periph) = (~(uint32_t)int_flag);
}
