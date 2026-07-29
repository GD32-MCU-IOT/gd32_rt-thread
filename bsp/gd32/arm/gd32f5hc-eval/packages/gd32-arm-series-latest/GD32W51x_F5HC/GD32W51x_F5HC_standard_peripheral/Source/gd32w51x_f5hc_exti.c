/*!
    \file    gd32w51x_f5hc_exti.c
    \brief   EXTI driver

    \version 2026-04-15, V2.0.0, firmware for gd32w51x_f5hc
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

#include "gd32w51x_f5hc_exti.h"

#define EXTI_PD_CLEAR_VAL    ((uint32_t)0xFFFFFFFFU)
#define EXTI_REG_RESET_VAL      ((uint32_t)0x00000000U)

/*!
    \brief      deinitialize the EXTI (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exti_deinit(void)
{
    /* disable all EXTI interrupts */
    EXTI_INTEN = EXTI_REG_RESET_VAL;
    /* disable all EXTI events */
    EXTI_EVEN = EXTI_REG_RESET_VAL;
    /* disable all EXTI rising edge triggers */
    EXTI_RTEN = EXTI_REG_RESET_VAL;
    /* disable all EXTI falling edge triggers */
    EXTI_FTEN = EXTI_REG_RESET_VAL;
    /* clear all EXTI software interrupt events */
    EXTI_SWIEV = EXTI_REG_RESET_VAL;
    /* clear all EXTI pending flags */
    EXTI_PD = EXTI_PD_CLEAR_VAL;
    /* reset security configuration */
    EXTI_SECCFG = EXTI_REG_RESET_VAL;
    /* reset privilege configuration */
    EXTI_PRIVCFG = EXTI_REG_RESET_VAL;
    /* reset lock register */
    EXTI_LOCK = EXTI_REG_RESET_VAL;
}

/*!
    \brief      initialize the EXTI (API_ID(0x0002U))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[in]  mode: interrupt or event mode
                only one parameter can be selected which is shown as below:
      \arg        EXTI_INTERRUPT: interrupt mode
      \arg        EXTI_EVENT: event mode
    \param[in]  trig_type: interrupt trigger type
                only one parameter can be selected which is shown as below:
      \arg        EXTI_TRIG_RISING: rising edge trigger
      \arg        EXTI_TRIG_FALLING: falling edge trigger
      \arg        EXTI_TRIG_BOTH: rising and falling edge trigger
      \arg        EXTI_TRIG_NONE: without rising edge or falling edge trigger
    \param[out] none
    \retval     none
*/
void exti_init(exti_line_enum linex, exti_mode_enum mode, exti_trig_type_enum trig_type)
{
    /* reset the EXTI line x */
    EXTI_INTEN &= ~(uint32_t)linex;
    EXTI_EVEN &= ~(uint32_t)linex;
    EXTI_RTEN &= ~(uint32_t)linex;
    EXTI_FTEN &= ~(uint32_t)linex;

    /* set the EXTI mode and enable the interrupts or events from EXTI line x */
    switch(mode) {
    case EXTI_INTERRUPT:
        EXTI_INTEN |= (uint32_t)linex;
        break;
    case EXTI_EVENT:
        EXTI_EVEN |= (uint32_t)linex;
        break;
    default:
        break;
    }

    /* set the EXTI trigger type */
    switch(trig_type) {
    case EXTI_TRIG_RISING:
        EXTI_RTEN |= (uint32_t)linex;
        EXTI_FTEN &= ~(uint32_t)linex;
        break;
    case EXTI_TRIG_FALLING:
        EXTI_RTEN &= ~(uint32_t)linex;
        EXTI_FTEN |= (uint32_t)linex;
        break;
    case EXTI_TRIG_BOTH:
        EXTI_RTEN |= (uint32_t)linex;
        EXTI_FTEN |= (uint32_t)linex;
        break;
    case EXTI_TRIG_NONE:
    default:
        break;
    }
}

/*!
    \brief      enable the interrupts from EXTI line x (API_ID(0x0003U))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_interrupt_enable(exti_line_enum linex)
{
    EXTI_INTEN |= (uint32_t)linex;
}

/*!
    \brief      disable the interrupts from EXTI line x (API_ID(0x0004U))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_interrupt_disable(exti_line_enum linex)
{
    EXTI_INTEN &= ~(uint32_t)linex;
}

/*!
    \brief      enable the events from EXTI line x (API_ID(0x0005U))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_event_enable(exti_line_enum linex)
{
    EXTI_EVEN |= (uint32_t)linex;
}

/*!
    \brief      disable the events from EXTI line x (API_ID(0x0006U))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_event_disable(exti_line_enum linex)
{
    EXTI_EVEN &= ~(uint32_t)linex;
}

/*!
    \brief      enable EXTI software interrupt event (API_ID(0x0007U))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_software_interrupt_enable(exti_line_enum linex)
{
    EXTI_SWIEV |= (uint32_t)linex;
}

/*!
    \brief      disable EXTI software interrupt event (API_ID(0x0008U))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_software_interrupt_disable(exti_line_enum linex)
{
    EXTI_SWIEV &= ~(uint32_t)linex;
}

/*!
    \brief      enable the security attribution from EXTI line x (API_ID(0x0009U))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_security_enable(exti_line_enum linex)
{
    EXTI_SECCFG |= (uint32_t)linex;
}

/*!
    \brief      disable the security attribution from EXTI line x (API_ID(0x000AU))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_security_disable(exti_line_enum linex)
{
    EXTI_SECCFG &= ~(uint32_t)linex;
}

/*!
    \brief      enable the privileged access from EXTI line x (API_ID(0x000BU))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_privilege_enable(exti_line_enum linex)
{
    EXTI_PRIVCFG |= (uint32_t)linex;
}

/*!
    \brief      disable the privileged access from EXTI line x (API_ID(0x000CU))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_privilege_disable(exti_line_enum linex)
{
    EXTI_PRIVCFG &= ~(uint32_t)linex;
}

/*!
    \brief      lock EXTI security attribution and privileged access configuration (API_ID(0x000DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exti_lock_enable(void)
{
    EXTI_LOCK |= EXTI_LOCK_LOCK;
}

/*!
    \brief      get EXTI line x interrupt pending flag (API_ID(0x000EU))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus exti_flag_get(exti_line_enum linex)
{
    FlagStatus reval = RESET;
    
    if(0U != (EXTI_PD & (uint32_t)linex)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    
    return reval;
}

/*!
    \brief      clear EXTI line x interrupt pending flag (API_ID(0x000FU))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_flag_clear(exti_line_enum linex)
{
    EXTI_PD = (uint32_t)linex;
}

/*!
    \brief      get EXTI line x interrupt pending flag (API_ID(0x0010U))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus exti_interrupt_flag_get(exti_line_enum linex)
{
    FlagStatus reval = RESET;
    uint32_t flag_status = 0U;
    uint32_t interrupt_enable = 0U;
    
    flag_status = EXTI_PD & (uint32_t)linex;
    interrupt_enable = EXTI_INTEN & (uint32_t)linex;
    
    if((RESET != flag_status) && (RESET != interrupt_enable)) {
        reval = SET;
    } else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }
    
    return reval;
}

/*!
    \brief      clear EXTI line x interrupt pending flag (API_ID(0x0011U))
    \param[in]  linex: EXTI line number
                only one parameter can be selected which is shown as below:
      \arg        EXTI_0: EXTI line 0
      \arg        EXTI_1: EXTI line 1
      \arg        EXTI_2: EXTI line 2
      \arg        EXTI_3: EXTI line 3
      \arg        EXTI_4: EXTI line 4
      \arg        EXTI_5: EXTI line 5
      \arg        EXTI_6: EXTI line 6
      \arg        EXTI_7: EXTI line 7
      \arg        EXTI_8: EXTI line 8
      \arg        EXTI_9: EXTI line 9
      \arg        EXTI_10: EXTI line 10
      \arg        EXTI_11: EXTI line 11
      \arg        EXTI_12: EXTI line 12
      \arg        EXTI_13: EXTI line 13
      \arg        EXTI_14: EXTI line 14
      \arg        EXTI_15: EXTI line 15
      \arg        EXTI_16: EXTI line 16
      \arg        EXTI_17: EXTI line 17
      \arg        EXTI_18: EXTI line 18
      \arg        EXTI_19: EXTI line 19
      \arg        EXTI_20: EXTI line 20 (only for GD32W515)
      \arg        EXTI_21: EXTI line 21
      \arg        EXTI_22: EXTI line 22
      \arg        EXTI_23: EXTI line 23
      \arg        EXTI_24: EXTI line 24
      \arg        EXTI_25: EXTI line 25
      \arg        EXTI_26: EXTI line 26
      \arg        EXTI_27: EXTI line 27
      \arg        EXTI_28: EXTI line 28
      \arg        EXTI_29: EXTI line 29 (only for GD32F5HC)
    \param[out] none
    \retval     none
*/
void exti_interrupt_flag_clear(exti_line_enum linex)
{
    EXTI_PD = (uint32_t)linex;
}
