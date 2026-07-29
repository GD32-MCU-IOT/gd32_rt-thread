/*!
    \file    gd32f50x_trigsel.c
    \brief   TRIGSEL driver

    \version 2026-02-25, V1.0.4, firmware for GD32F50x
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

#include "gd32f50x_trigsel.h"

/* TRIGSEL target register redefine */
#define TRIGSEL_TARGET_REG(target_periph)           (REG32(TRIGSEL + ((uint32_t)(target_periph) & BITS(2,31))))            /*!< target peripheral register */
#define TRIGSEL_TARGET_PERIPH_SHIFT(target_periph)  (((uint32_t)(target_periph) & BITS(0,1)) << 3U)                        /*!< bit offset in target peripheral register */
#define TRIGSEL_TARGET_PERIPH_MASK(target_periph)   ((uint32_t)(BITS(0,7) << TRIGSEL_TARGET_PERIPH_SHIFT(target_periph)))  /*!< bit mask in target peripheral register */

/*!
    \brief      deinitialize TRIGSEL (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trigsel_deinit(void)
{
    rcu_periph_reset_enable(RCU_TRIGSELRST);
    rcu_periph_reset_disable(RCU_TRIGSELRST);
}

/*!
    \brief      set the trigger input signal for target peripheral (API_ID(0x0002U))
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg      TRIGSEL_OUTPUT_TIMER0_ITI: output target peripheral TIMER0_ITI
      \arg      TRIGSEL_OUTPUT_TIMER1_ITI: output target peripheral TIMER1_ITI
      \arg      TRIGSEL_OUTPUT_TIMER2_ITI: output target peripheral TIMER2_ITI
      \arg      TRIGSEL_OUTPUT_TIMER3_ITI: output target peripheral TIMER3_ITI
      \arg      TRIGSEL_OUTPUT_TIMER4_ITI: output target peripheral TIMER4_ITI
      \arg      TRIGSEL_OUTPUT_TIMER7_ITI: output target peripheral TIMER7_ITI
      \arg      TRIGSEL_OUTPUT_TIMER15_ITI: output target peripheral TIMER15_ITI
      \arg      TRIGSEL_OUTPUT_TIMER16_ITI: output target peripheral TIMER16_ITI
      \arg      TRIGSEL_OUTPUT_DAC_OUT_EXTRG: output target peripheral DAC_OUT_EXTRG
      \arg      TRIGSEL_OUTPUT_ADC0_ROUTRG: output target peripheral ADC0_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg      TRIGSEL_OUTPUT_ADC1_ROUTRG: output target peripheral ADC1_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg      TRIGSEL_OUTPUT_ADC2_ROUTRG: output target peripheral ADC2_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg      TRIGSEL_OUTPUT_TIMER0_BRKIN: output target peripheral TIMER0_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH0BRKIN: output target peripheral TIMER0_CH0BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH1BRKIN: output target peripheral TIMER0_CH1BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH2BRKIN: output target peripheral TIMER0_CH2BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_BRKIN: output target peripheral TIMER7_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH0BRKIN: output target peripheral TIMER7_CH0BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH1BRKIN: output target peripheral TIMER7_CH1BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH2BRKIN: output target peripheral TIMER7_CH2BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER15_BRKIN: output target peripheral TIMER15_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER16_BRKIN: output target peripheral TIMER16_BRKIN
    \param[in]  trigger_source: trigger source value
                only one parameter can be selected which is shown as below:
      \arg      TRIGSEL_INPUT_VSS: trigger input source VSS
      \arg      TRIGSEL_INPUT_VDD: trigger input source VDD
      \arg      TRIGSEL_INPUT_TRIGSEL_IN0: trigger input source TRIGSEL_IN0
      \arg      TRIGSEL_INPUT_TRIGSEL_IN1: trigger input source TRIGSEL_IN1
      \arg      TRIGSEL_INPUT_TRIGSEL_IN2: trigger input source TRIGSEL_IN2
      \arg      TRIGSEL_INPUT_TRIGSEL_IN3: trigger input source TRIGSEL_IN3
      \arg      TRIGSEL_INPUT_TRIGSEL_IN4: trigger input source TRIGSEL_IN4
      \arg      TRIGSEL_INPUT_TRIGSEL_IN5: trigger input source TRIGSEL_IN5
      \arg      TRIGSEL_INPUT_TRIGSEL_IN6: trigger input source TRIGSEL_IN6
      \arg      TRIGSEL_INPUT_TRIGSEL_IN7: trigger input source TRIGSEL_IN7
      \arg      TRIGSEL_INPUT_TIMER0_TRGO: trigger input source TIMER0_TRGO
      \arg      TRIGSEL_INPUT_TIMER0_CH0: trigger input source TIMER0_CH0
      \arg      TRIGSEL_INPUT_TIMER0_CH1: trigger input source TIMER0_CH1
      \arg      TRIGSEL_INPUT_TIMER0_CH2: trigger input source TIMER0_CH2
      \arg      TRIGSEL_INPUT_TIMER0_CH3: trigger input source TIMER0_CH3
      \arg      TRIGSEL_INPUT_TIMER7_TRGO: trigger input source TIMER7_TRGO
      \arg      TRIGSEL_INPUT_TIMER7_CH0: trigger input source TIMER7_CH0
      \arg      TRIGSEL_INPUT_TIMER7_CH1: trigger input source TIMER7_CH1
      \arg      TRIGSEL_INPUT_TIMER7_CH2: trigger input source TIMER7_CH2
      \arg      TRIGSEL_INPUT_TIMER7_CH3: trigger input source TIMER7_CH3
      \arg      TRIGSEL_INPUT_TIMER5_TRGO: trigger input source TIMER5_TRGO
      \arg      TRIGSEL_INPUT_TIMER6_TRGO: trigger input source TIMER6_TRGO
      \arg      TRIGSEL_INPUT_TIMER1_TRGO: trigger input source TIMER1_TRGO
      \arg      TRIGSEL_INPUT_TIMER1_CH0: trigger input source TIMER1_CH0
      \arg      TRIGSEL_INPUT_TIMER1_CH1: trigger input source TIMER1_CH1
      \arg      TRIGSEL_INPUT_TIMER1_CH2: trigger input source TIMER1_CH2
      \arg      TRIGSEL_INPUT_TIMER1_CH3: trigger input source TIMER1_CH3
      \arg      TRIGSEL_INPUT_TIMER2_TRGO: trigger input source TIMER2_TRGO
      \arg      TRIGSEL_INPUT_TIMER2_CH0: trigger input source TIMER2_CH0
      \arg      TRIGSEL_INPUT_TIMER2_CH1: trigger input source TIMER2_CH1
      \arg      TRIGSEL_INPUT_TIMER2_CH2: trigger input source TIMER2_CH2
      \arg      TRIGSEL_INPUT_TIMER2_CH3: trigger input source TIMER2_CH3
      \arg      TRIGSEL_INPUT_TIMER3_TRGO: trigger input source TIMER3_TRGO
      \arg      TRIGSEL_INPUT_TIMER3_CH0: trigger input source TIMER3_CH0
      \arg      TRIGSEL_INPUT_TIMER3_CH1: trigger input source TIMER3_CH1
      \arg      TRIGSEL_INPUT_TIMER3_CH2: trigger input source TIMER3_CH2
      \arg      TRIGSEL_INPUT_TIMER3_CH3: trigger input source TIMER3_CH3
      \arg      TRIGSEL_INPUT_TIMER4_TRGO: trigger input source TIMER4_TRGO
      \arg      TRIGSEL_INPUT_TIMER4_CH0: trigger input source TIMER4_CH0
      \arg      TRIGSEL_INPUT_TIMER4_CH1: trigger input source TIMER4_CH1
      \arg      TRIGSEL_INPUT_TIMER4_CH2: trigger input source TIMER4_CH2
      \arg      TRIGSEL_INPUT_TIMER4_CH3: trigger input source TIMER4_CH3
      \arg      TRIGSEL_INPUT_TIMER15_TRGO: trigger input source TIMER15_TRGO
      \arg      TRIGSEL_INPUT_TIMER15_CH0: trigger input source TIMER15_CH0
      \arg      TRIGSEL_INPUT_TIMER15_CH1: trigger input source TIMER15_CH1
      \arg      TRIGSEL_INPUT_TIMER15_MCH0: trigger input source TIMER15_MCH0
      \arg      TRIGSEL_INPUT_TIMER16_TRGO: trigger input source TIMER16_TRGO
      \arg      TRIGSEL_INPUT_TIMER16_CH0: trigger input source TIMER16_CH0
      \arg      TRIGSEL_INPUT_TIMER16_CH1: trigger input source TIMER16_CH1
      \arg      TRIGSEL_INPUT_TIMER16_MCH0: trigger input source TIMER16_MCH0
      \arg      TRIGSEL_INPUT_ADC0_WD0_OUT: trigger input source ADC0_WD0_OUT
      \arg      TRIGSEL_INPUT_ADC0_WD1_OUT: trigger input source ADC0_WD1_OUT
      \arg      TRIGSEL_INPUT_ADC0_WD2_OUT: trigger input source ADC0_WD2_OUT
      \arg      TRIGSEL_INPUT_ADC1_WD0_OUT: trigger input source ADC1_WD0_OUT
      \arg      TRIGSEL_INPUT_ADC1_WD1_OUT: trigger input source ADC1_WD1_OUT
      \arg      TRIGSEL_INPUT_ADC1_WD2_OUT: trigger input source ADC1_WD2_OUT
      \arg      TRIGSEL_INPUT_ADC2_WD0_OUT: trigger input source ADC2_WD0_OUT
      \arg      TRIGSEL_INPUT_ADC2_WD1_OUT: trigger input source ADC2_WD1_OUT
      \arg      TRIGSEL_INPUT_ADC2_WD2_OUT: trigger input source ADC2_WD2_OUT
      \arg      TRIGSEL_INPUT_CMP0_OUT: trigger input source CMP0_OUT
      \arg      TRIGSEL_INPUT_CK_OUT: trigger input source CK_OUT
      \arg      TRIGSEL_INPUT_TIMER0_BKIN: trigger input source TIMER0_BKIN
      \arg      TRIGSEL_INPUT_TIMER0_CH0BKIN: trigger input source TIMER0_CH0BKIN
      \arg      TRIGSEL_INPUT_TIMER0_CH1BKIN: trigger input source TIMER0_CH1BKIN
      \arg      TRIGSEL_INPUT_TIMER0_CH2BKIN: trigger input source TIMER0_CH2BKIN
      \arg      TRIGSEL_INPUT_TIMER7_BKIN: trigger input source TIMER7_BKIN
      \arg      TRIGSEL_INPUT_TIMER7_CH0BKIN: trigger input source TIMER7_CH0BKIN
      \arg      TRIGSEL_INPUT_TIMER7_CH1BKIN: trigger input source TIMER7_CH1BKIN
      \arg      TRIGSEL_INPUT_TIMER7_CH2BKIN: trigger input source TIMER7_CH2BKIN
      \arg      TRIGSEL_INPUT_TIMER15_BKIN: trigger input source TIMER15_BKIN
      \arg      TRIGSEL_INPUT_TIMER16_BKIN: trigger input source TIMER16_BKIN
      \arg      TRIGSEL_INPUT_EXTI9: trigger input source EXTI9
      \arg      TRIGSEL_INPUT_EXTI11: trigger input source EXTI11
      \arg      TRIGSEL_INPUT_EXTI15: trigger input source EXTI15
    \param[out] none
    \retval     none
*/
void trigsel_init(trigsel_periph_enum target_periph, trigsel_source_enum trigger_source)
{
    /* if register write is enabled, set trigger source to target peripheral */
    if(RESET == trigsel_register_lock_get(target_periph)) {
        TRIGSEL_TARGET_REG(target_periph) &= ~TRIGSEL_TARGET_PERIPH_MASK(target_periph);
        TRIGSEL_TARGET_REG(target_periph) |= ((uint32_t)(trigger_source & TRIGSEL_TARGET_INSEL0) << TRIGSEL_TARGET_PERIPH_SHIFT(
                target_periph)) & TRIGSEL_TARGET_PERIPH_MASK(
                        target_periph);
    }
}

/*!
    \brief      get the trigger input signal for target peripheral (API_ID(0x0003U))
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg      TRIGSEL_OUTPUT_TIMER0_ITI: output target peripheral TIMER0_ITI
      \arg      TRIGSEL_OUTPUT_TIMER1_ITI: output target peripheral TIMER1_ITI
      \arg      TRIGSEL_OUTPUT_TIMER2_ITI: output target peripheral TIMER2_ITI
      \arg      TRIGSEL_OUTPUT_TIMER3_ITI: output target peripheral TIMER3_ITI
      \arg      TRIGSEL_OUTPUT_TIMER4_ITI: output target peripheral TIMER4_ITI
      \arg      TRIGSEL_OUTPUT_TIMER7_ITI: output target peripheral TIMER7_ITI
      \arg      TRIGSEL_OUTPUT_TIMER15_ITI: output target peripheral TIMER15_ITI
      \arg      TRIGSEL_OUTPUT_TIMER16_ITI: output target peripheral TIMER16_ITI
      \arg      TRIGSEL_OUTPUT_DAC_OUT_EXTRG: output target peripheral DAC_OUT_EXTRG
      \arg      TRIGSEL_OUTPUT_ADC0_ROUTRG: output target peripheral ADC0_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg      TRIGSEL_OUTPUT_ADC1_ROUTRG: output target peripheral ADC1_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg      TRIGSEL_OUTPUT_ADC2_ROUTRG: output target peripheral ADC2_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg      TRIGSEL_OUTPUT_TIMER0_BRKIN: output target peripheral TIMER0_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH0BRKIN: output target peripheral TIMER0_CH0BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH1BRKIN: output target peripheral TIMER0_CH1BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH2BRKIN: output target peripheral TIMER0_CH2BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_BRKIN: output target peripheral TIMER7_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH0BRKIN: output target peripheral TIMER7_CH0BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH1BRKIN: output target peripheral TIMER7_CH1BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH2BRKIN: output target peripheral TIMER7_CH2BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER15_BRKIN: output target peripheral TIMER15_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER16_BRKIN: output target peripheral TIMER16_BRKIN
    \param[out] none
    \retval  trigger_source: trigger source value(0~0x4E)
*/
trigsel_source_enum trigsel_trigger_source_get(trigsel_periph_enum target_periph)
{
    trigsel_source_enum trigger_source;

    trigger_source = (trigsel_source_enum)((TRIGSEL_TARGET_REG(target_periph) & TRIGSEL_TARGET_PERIPH_MASK(target_periph)) >> TRIGSEL_TARGET_PERIPH_SHIFT(
            target_periph));

    return trigger_source;
}

/*!
    \brief      lock the trigger register (API_ID(0x0004U))
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg      TRIGSEL_OUTPUT_TIMER0_ITI: output target peripheral TIMER0_ITI
      \arg      TRIGSEL_OUTPUT_TIMER1_ITI: output target peripheral TIMER1_ITI
      \arg      TRIGSEL_OUTPUT_TIMER2_ITI: output target peripheral TIMER2_ITI
      \arg      TRIGSEL_OUTPUT_TIMER3_ITI: output target peripheral TIMER3_ITI
      \arg      TRIGSEL_OUTPUT_TIMER4_ITI: output target peripheral TIMER4_ITI
      \arg      TRIGSEL_OUTPUT_TIMER7_ITI: output target peripheral TIMER7_ITI
      \arg      TRIGSEL_OUTPUT_TIMER15_ITI: output target peripheral TIMER15_ITI
      \arg      TRIGSEL_OUTPUT_TIMER16_ITI: output target peripheral TIMER16_ITI
      \arg      TRIGSEL_OUTPUT_DAC_OUT_EXTRG: output target peripheral DAC_OUT_EXTRG
      \arg      TRIGSEL_OUTPUT_ADC0_ROUTRG: output target peripheral ADC0_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg      TRIGSEL_OUTPUT_ADC1_ROUTRG: output target peripheral ADC1_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg      TRIGSEL_OUTPUT_ADC2_ROUTRG: output target peripheral ADC2_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg      TRIGSEL_OUTPUT_TIMER0_BRKIN: output target peripheral TIMER0_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH0BRKIN: output target peripheral TIMER0_CH0BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH1BRKIN: output target peripheral TIMER0_CH1BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH2BRKIN: output target peripheral TIMER0_CH2BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_BRKIN: output target peripheral TIMER7_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH0BRKIN: output target peripheral TIMER7_CH0BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH1BRKIN: output target peripheral TIMER7_CH1BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH2BRKIN: output target peripheral TIMER7_CH2BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER15_BRKIN: output target peripheral TIMER15_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER16_BRKIN: output target peripheral TIMER16_BRKIN
    \param[out] none
    \retval     none
*/
void trigsel_register_lock_set(trigsel_periph_enum target_periph)
{
    /*!< lock target peripheral register */
    TRIGSEL_TARGET_REG(target_periph) |= TRIGSEL_TARGET_LK;
}

/*!
    \brief      get the trigger register lock status (API_ID(0x0005U))
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg      TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg      TRIGSEL_OUTPUT_TIMER0_ITI: output target peripheral TIMER0_ITI
      \arg      TRIGSEL_OUTPUT_TIMER1_ITI: output target peripheral TIMER1_ITI
      \arg      TRIGSEL_OUTPUT_TIMER2_ITI: output target peripheral TIMER2_ITI
      \arg      TRIGSEL_OUTPUT_TIMER3_ITI: output target peripheral TIMER3_ITI
      \arg      TRIGSEL_OUTPUT_TIMER4_ITI: output target peripheral TIMER4_ITI
      \arg      TRIGSEL_OUTPUT_TIMER7_ITI: output target peripheral TIMER7_ITI
      \arg      TRIGSEL_OUTPUT_TIMER15_ITI: output target peripheral TIMER15_ITI
      \arg      TRIGSEL_OUTPUT_TIMER16_ITI: output target peripheral TIMER16_ITI
      \arg      TRIGSEL_OUTPUT_DAC_OUT_EXTRG: output target peripheral DAC_OUT_EXTRG
      \arg      TRIGSEL_OUTPUT_ADC0_ROUTRG: output target peripheral ADC0_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg      TRIGSEL_OUTPUT_ADC1_ROUTRG: output target peripheral ADC1_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg      TRIGSEL_OUTPUT_ADC2_ROUTRG: output target peripheral ADC2_ROUTRG
      \arg      TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg      TRIGSEL_OUTPUT_TIMER0_BRKIN: output target peripheral TIMER0_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH0BRKIN: output target peripheral TIMER0_CH0BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH1BRKIN: output target peripheral TIMER0_CH1BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER0_CH2BRKIN: output target peripheral TIMER0_CH2BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_BRKIN: output target peripheral TIMER7_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH0BRKIN: output target peripheral TIMER7_CH0BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH1BRKIN: output target peripheral TIMER7_CH1BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER7_CH2BRKIN: output target peripheral TIMER7_CH2BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER15_BRKIN: output target peripheral TIMER15_BRKIN
      \arg      TRIGSEL_OUTPUT_TIMER16_BRKIN: output target peripheral TIMER16_BRKIN
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus trigsel_register_lock_get(trigsel_periph_enum target_periph)
{
    FlagStatus flag;
    if(RESET != (TRIGSEL_TARGET_REG(target_periph) & TRIGSEL_TARGET_LK)) {
        flag = SET;
    } else {
        flag = RESET;
    }
    return flag;
}
