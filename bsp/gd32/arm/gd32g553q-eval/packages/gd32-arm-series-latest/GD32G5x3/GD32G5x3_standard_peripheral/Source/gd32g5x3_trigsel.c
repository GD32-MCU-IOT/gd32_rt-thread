/*!
    \file    gd32g5x3_trigsel.c
    \brief   TRIGSEL driver

    \version 2025-02-10, V1.1.0, firmware for GD32G5x3
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

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

#include "gd32g5x3_trigsel.h"

/* TRIGSEL target register redefine */
#define TRIGSEL_TARGET_REG(target_periph)           (REG32(TRIGSEL + ((uint32_t)(target_periph) & BITS(2,31))))            /*!< target peripheral register */
#define TRIGSEL_TARGET_PERIPH_SHIFT(target_periph)  (((uint32_t)(target_periph) & BITS(0,1)) << 3U)                        /*!< bit offset in target peripheral register */
#define TRIGSEL_TARGET_PERIPH_MASK(target_periph)   ((uint32_t)(BITS(0,7) << TRIGSEL_TARGET_PERIPH_SHIFT(target_periph)))  /*!< bit mask in target peripheral register */

/*!
    \brief      deinitialize TRIGSEL
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
    \brief      set the trigger input signal for target peripheral
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_ADC0_ROUTRG: output target peripheral ADC0_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC1_ROUTRG: output target peripheral ADC1_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC2_ROUTRG: output target peripheral ADC2_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC3_ROUTRG: output target peripheral ADC3_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC3_INSTRG: output target peripheral ADC3_INSTRG
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER14_BRKIN0: output target peripheral TIMER14_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER15_BRKIN0: output target peripheral TIMER15_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER16_BRKIN0: output target peripheral TIMER16_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN0: output target peripheral TIMER19_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN1: output target peripheral TIMER19_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN2: output target peripheral TIMER19_BRKIN2
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_TIMER0_ETI: output target peripheral TIMER0_ETI
      \arg        TRIGSEL_OUTPUT_TIMER1_ETI: output target peripheral TIMER1_ETI
      \arg        TRIGSEL_OUTPUT_TIMER2_ETI: output target peripheral TIMER2_ETI
      \arg        TRIGSEL_OUTPUT_TIMER3_ETI: output target peripheral TIMER3_ETI
      \arg        TRIGSEL_OUTPUT_TIMER4_ETI: output target peripheral TIMER4_ETI
      \arg        TRIGSEL_OUTPUT_TIMER7_ETI: output target peripheral TIMER7_ETI
      \arg        TRIGSEL_OUTPUT_TIMER19_ETI: output target peripheral TIMER19_ETI
      \arg        TRIGSEL_OUTPUT_HPDF_ITRG: output target peripheral HPDF_ITRG
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI14: output target peripheral TIMER0_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI14: output target peripheral TIMER1_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI14: output target peripheral TIMER2_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER3_ITI14: output target peripheral TIMER3_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER4_ITI14: output target peripheral TIMER4_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI14: output target peripheral TIMER7_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER14_ITI14: output target peripheral TIMER14_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER19_ITI14: output target peripheral TIMER19_ITI14
      \arg        TRIGSEL_OUTPUT_DAC0_EXTRIG0: output target peripheral DAC0_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC0_EXTRIG1: output target peripheral DAC0_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC1_EXTRIG0: output target peripheral DAC1_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC1_EXTRIG1: output target peripheral DAC1_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC2_EXTRIG0: output target peripheral DAC2_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC2_EXTRIG1: output target peripheral DAC2_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC3_EXTRIG0: output target peripheral DAC3_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC3_EXTRIG1: output target peripheral DAC3_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC0_ST_EXTRIG0: output target peripheral DAC0_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC0_ST_EXTRIG1: output target peripheral DAC0_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC1_ST_EXTRIG0: output target peripheral DAC1_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC1_ST_EXTRIG1: output target peripheral DAC1_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC2_ST_EXTRIG0: output target peripheral DAC2_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC2_ST_EXTRIG1: output target peripheral DAC2_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC3_ST_EXTRIG0: output target peripheral DAC3_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC3_ST_EXTRIG1: output target peripheral DAC3_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_CLA_IN0: output target peripheral CLA_IN0
      \arg        TRIGSEL_OUTPUT_CLA_IN1: output target peripheral CLA_IN1
      \arg        TRIGSEL_OUTPUT_CLA_IN2: output target peripheral CLA_IN2
      \arg        TRIGSEL_OUTPUT_CLA_IN3: output target peripheral CLA_IN3
      \arg        TRIGSEL_OUTPUT_CLA_IN4: output target peripheral CLA_IN4
      \arg        TRIGSEL_OUTPUT_CLA_IN5: output target peripheral CLA_IN5
      \arg        TRIGSEL_OUTPUT_CLA_IN6: output target peripheral CLA_IN6
      \arg        TRIGSEL_OUTPUT_CLA_IN7: output target peripheral CLA_IN7
      \arg        TRIGSEL_OUTPUT_CLA_IN8: output target peripheral CLA_IN8
      \arg        TRIGSEL_OUTPUT_CLA_IN9: output target peripheral CLA_IN9
      \arg        TRIGSEL_OUTPUT_CLA_IN10: output target peripheral CLA_IN10
      \arg        TRIGSEL_OUTPUT_CLA_IN11: output target peripheral CLA_IN11
    \param[in]  trigger_source: trigger source value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_INPUT_0: trigger input source 0
      \arg        TRIGSEL_INPUT_1: trigger input source 1
      \arg        TRIGSEL_INPUT_TRIGSEL_IN0: trigger input source TRIGSEL_IN0 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN1: trigger input source TRIGSEL_IN1 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN2: trigger input source TRIGSEL_IN2 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN3: trigger input source TRIGSEL_IN3 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN4: trigger input source TRIGSEL_IN4 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN5: trigger input source TRIGSEL_IN5 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN6: trigger input source TRIGSEL_IN6 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN7: trigger input source TRIGSEL_IN7 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN8: trigger input source TRIGSEL_IN8 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN9: trigger input source TRIGSEL_IN9 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN10: trigger input source TRIGSEL_IN10 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN11: trigger input source TRIGSEL_IN11 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN12: trigger input source TRIGSEL_IN12 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN13: trigger input source TRIGSEL_IN13 pin
      \arg        TRIGSEL_INPUT_TIMER0_TRGO0: trigger input source TIMER0 TRGO0
      \arg        TRIGSEL_INPUT_TIMER0_TRGO1: trigger input source TIMER0 TRGO1
      \arg        TRIGSEL_INPUT_TIMER0_CH0: trigger input source TIMER0 CH0
      \arg        TRIGSEL_INPUT_TIMER0_CH1: trigger input source TIMER0 CH1
      \arg        TRIGSEL_INPUT_TIMER0_CH2: trigger input source TIMER0 CH2
      \arg        TRIGSEL_INPUT_TIMER0_CH3: trigger input source TIMER0 CH3
      \arg        TRIGSEL_INPUT_TIMER0_MCH0: trigger input source TIMER0 MCH0
      \arg        TRIGSEL_INPUT_TIMER0_MCH1: trigger input source TIMER0 MCH1
      \arg        TRIGSEL_INPUT_TIMER0_MCH2: trigger input source TIMER0 MCH2
      \arg        TRIGSEL_INPUT_TIMER0_MCH3: trigger input source TIMER0 MCH3
      \arg        TRIGSEL_INPUT_TIMER0_ETI: trigger input source TIMER0 ETI
      \arg        TRIGSEL_INPUT_TIMER1_TRGO0: trigger input source TIMER1 TRGO0
      \arg        TRIGSEL_INPUT_TIMER1_CH0: trigger input source TIMER1 CH0
      \arg        TRIGSEL_INPUT_TIMER1_CH1: trigger input source TIMER1 CH1
      \arg        TRIGSEL_INPUT_TIMER1_CH2: trigger input source TIMER1 CH2
      \arg        TRIGSEL_INPUT_TIMER1_CH3: trigger input source TIMER1 CH3
      \arg        TRIGSEL_INPUT_TIMER1_ETI: trigger input source TIMER1 ETI
      \arg        TRIGSEL_INPUT_TIMER2_TRGO0: trigger input source TIMER2 TRGO0
      \arg        TRIGSEL_INPUT_TIMER2_CH0: trigger input source TIMER2 CH0
      \arg        TRIGSEL_INPUT_TIMER2_CH1: trigger input source TIMER2 CH1
      \arg        TRIGSEL_INPUT_TIMER2_CH2: trigger input source TIMER2 CH2
      \arg        TRIGSEL_INPUT_TIMER2_CH3: trigger input source TIMER2 CH3
      \arg        TRIGSEL_INPUT_TIMER2_ETI: trigger input source TIMER2 ETI
      \arg        TRIGSEL_INPUT_TIMER3_TRGO0: trigger input source TIMER3 TRGO0
      \arg        TRIGSEL_INPUT_TIMER3_CH0: trigger input source TIMER3 CH0
      \arg        TRIGSEL_INPUT_TIMER3_CH1: trigger input source TIMER3 CH1
      \arg        TRIGSEL_INPUT_TIMER3_CH2: trigger input source TIMER3 CH2
      \arg        TRIGSEL_INPUT_TIMER3_CH3: trigger input source TIMER3 CH3
      \arg        TRIGSEL_INPUT_TIMER3_ETI: trigger input source TIMER3 ETI
      \arg        TRIGSEL_INPUT_TIMER4_TRGO0: trigger input source TIMER4 TRGO0
      \arg        TRIGSEL_INPUT_TIMER4_CH0: trigger input source TIMER4 CH0
      \arg        TRIGSEL_INPUT_TIMER4_CH1: trigger input source TIMER4 CH1
      \arg        TRIGSEL_INPUT_TIMER4_CH2: trigger input source TIMER4 CH2
      \arg        TRIGSEL_INPUT_TIMER4_CH3: trigger input source TIMER4 CH3
      \arg        TRIGSEL_INPUT_TIMER4_ETI: trigger input source TIMER4 ETI
      \arg        TRIGSEL_INPUT_TIMER5_TRGO0: trigger input source TIMER5 TRGO0
      \arg        TRIGSEL_INPUT_TIMER6_TRGO0: trigger input source TIMER6 TRGO0
      \arg        TRIGSEL_INPUT_TIMER7_TRGO0: trigger input source TIMER7 TRGO0
      \arg        TRIGSEL_INPUT_TIMER7_TRGO1: trigger input source TIMER7 TRGO1
      \arg        TRIGSEL_INPUT_TIMER7_CH0: trigger input source TIMER7 CH0
      \arg        TRIGSEL_INPUT_TIMER7_CH1: trigger input source TIMER7 CH1
      \arg        TRIGSEL_INPUT_TIMER7_CH2: trigger input source TIMER7 CH2
      \arg        TRIGSEL_INPUT_TIMER7_CH3: trigger input source TIMER7 CH3
      \arg        TRIGSEL_INPUT_TIMER7_MCH0: trigger input source TIMER7 MCH0
      \arg        TRIGSEL_INPUT_TIMER7_MCH1: trigger input source TIMER7 MCH1
      \arg        TRIGSEL_INPUT_TIMER7_MCH2: trigger input source TIMER7 MCH2
      \arg        TRIGSEL_INPUT_TIMER7_MCH3: trigger input source TIMER7 MCH3
      \arg        TRIGSEL_INPUT_TIMER7_ETI:trigger input source TIMER7 ETI
      \arg        TRIGSEL_INPUT_TIMER14_TRGO0: trigger input source TIMER14 TRGO0
      \arg        TRIGSEL_INPUT_TIMER14_CH0: trigger input source TIMER14 CH0
      \arg        TRIGSEL_INPUT_TIMER14_CH1: trigger input source TIMER14 CH1
      \arg        TRIGSEL_INPUT_TIMER14_MCH0: trigger input source TIMER14 MCH0
      \arg        TRIGSEL_INPUT_TIMER15_CH0: trigger input source TIMER15 CH0
      \arg        TRIGSEL_INPUT_TIMER15_MCH0: trigger input source TIMER15 MCH0
      \arg        TRIGSEL_INPUT_TIMER16_CH0: trigger input source TIMER16 CH0
      \arg        TRIGSEL_INPUT_TIMER16_MCH0: trigger input source TIMER16 MCH0
      \arg        TRIGSEL_INPUT_TIMER19_TRGO0: trigger input source TIMER19 TRGO0
      \arg        TRIGSEL_INPUT_TIMER19_TRGO1: trigger input source TIMER19 TRGO1
      \arg        TRIGSEL_INPUT_TIMER19_CH0: trigger input source TIMER19 CH0
      \arg        TRIGSEL_INPUT_TIMER19_CH1: trigger input source TIMER19 CH1
      \arg        TRIGSEL_INPUT_TIMER19_CH2: trigger input source TIMER19 CH2
      \arg        TRIGSEL_INPUT_TIMER19_CH3: trigger input source TIMER19 CH3
      \arg        TRIGSEL_INPUT_TIMER19_MCH0: trigger input source TIMER19 MCH0
      \arg        TRIGSEL_INPUT_TIMER19_MCH1: trigger input source TIMER19 MCH1
      \arg        TRIGSEL_INPUT_TIMER19_MCH2: trigger input source TIMER19 MCH2
      \arg        TRIGSEL_INPUT_TIMER19_MCH3: trigger input source TIMER19 MCH3
      \arg        TRIGSEL_INPUT_TIMER19_ETI: trigger input source TIMER19 ETI
      \arg        TRIGSEL_INPUT_TIMER0_BRKIN0: trigger input source TIMER0 BRKIN0
      \arg        TRIGSEL_INPUT_TIMER0_BRKIN1: trigger input source TIMER0 BRKIN1
      \arg        TRIGSEL_INPUT_TIMER0_BRKIN2: trigger input source TIMER0 BRKIN2
      \arg        TRIGSEL_INPUT_TIMER7_BRKIN0: trigger input source TIMER7 BRKIN0
      \arg        TRIGSEL_INPUT_TIMER7_BRKIN1: trigger input source TIMER7 BRKIN1
      \arg        TRIGSEL_INPUT_TIMER7_BRKIN2: trigger input source TIMER7 BRKIN2
      \arg        TRIGSEL_INPUT_TIMER14_BRKIN0: trigger input source TIMER14 BRKIN0
      \arg        TRIGSEL_INPUT_TIMER15_BRKIN0: trigger input source TIMER15 BRKIN0
      \arg        TRIGSEL_INPUT_TIMER16_BRKIN0: trigger input source TIMER16 BRKIN0
      \arg        TRIGSEL_INPUT_TIMER19_BRKIN0: trigger input source TIMER19 BRKIN0
      \arg        TRIGSEL_INPUT_TIMER19_BRKIN1: trigger input source TIMER19 BRKIN1
      \arg        TRIGSEL_INPUT_TIMER19_BRKIN2: trigger input source TIMER19 BRKIN2
      \arg        TRIGSEL_INPUT_LPTIMER_OUT: trigger input source LPTIMER_OUT
      \arg        TRIGSEL_INPUT_LPTIMER_ETI: trigger input source LPTIMER_ETI
      \arg        TRIGSEL_INPUT_HRTIMER_SCOUT: trigger input source HRTIMER_OUT_SCOUT
      \arg        TRIGSEL_INPUT_HRTIMER_OUT_SCIN: trigger input source HRTIMER_SCIN
      \arg        TRIGSEL_INPUT_HRTIMER_ADC_TRIG0: trigger input source HRTIMER_ADC_TRIG0
      \arg        TRIGSEL_INPUT_HRTIMER_ADC_TRIG1: trigger input source HRTIMER_ADC_TRIG1
      \arg        TRIGSEL_INPUT_HRTIMER_ADC_TRIG2: trigger input source HRTIMER_ADC_TRIG2
      \arg        TRIGSEL_INPUT_HRTIMER_ADC_TRIG3: trigger input source HRTIMER_ADC_TRIG3
      \arg        TRIGSEL_INPUT_HRTIMER_ADC_TRIG4: trigger input source HRTIMER_ADC_TRIG4
      \arg        TRIGSEL_INPUT_HRTIMER_ADC_TRIG5: trigger input source HRTIMER_ADC_TRIG5
      \arg        TRIGSEL_INPUT_HRTIMER_ADC_TRIG6: trigger input source HRTIMER_ADC_TRIG6
      \arg        TRIGSEL_INPUT_HRTIMER_ADC_TRIG7: trigger input source HRTIMER_ADC_TRIG7
      \arg        TRIGSEL_INPUT_HRTIMER_ADC_TRIG8: trigger input source HRTIMER_ADC_TRIG8
      \arg        TRIGSEL_INPUT_HRTIMER_ADC_TRIG9: trigger input source HRTIMER_ADC_TRIG9
      \arg        TRIGSEL_INPUT_HRTIMER_DAC_TRIG0: trigger input source HRTIMER_DAC_TRIG0
      \arg        TRIGSEL_INPUT_HRTIMER_DAC_TRIG1: trigger input source HRTIMER_DAC_TRIG1
      \arg        TRIGSEL_INPUT_HRTIMER_DAC_TRIG2: trigger input source HRTIMER_DAC_TRIG2
      \arg        TRIGSEL_INPUT_HRTIMER_ST0_TRIG1: trigger input source HRTIMER_ST0_TRIG0
      \arg        TRIGSEL_INPUT_HRTIMER_ST1_TRIG1: trigger input source HRTIMER_ST1_TRIG0
      \arg        TRIGSEL_INPUT_HRTIMER_ST2_TRIG1: trigger input source HRTIMER_ST2_TRIG0
      \arg        TRIGSEL_INPUT_HRTIMER_ST3_TRIG1: trigger input source HRTIMER_ST3_TRIG0
      \arg        TRIGSEL_INPUT_HRTIMER_ST4_TRIG1: trigger input source HRTIMER_ST4_TRIG0
      \arg        TRIGSEL_INPUT_HRTIMER_ST5_TRIG1: trigger input source HRTIMER_ST5_TRIG0
      \arg        TRIGSEL_INPUT_HRTIMER_ST6_TRIG1: trigger input source HRTIMER_ST6_TRIG0
      \arg        TRIGSEL_INPUT_HRTIMER_ST7_TRIG1: trigger input source HRTIMER_ST7_TRIG0
      \arg        TRIGSEL_INPUT_HRTIMER_SYSFLT: trigger input source HRTIMER_SYSFLT
      \arg        TRIGSEL_INPUT_ADC0_WD0_OUT: trigger input source ADC0 watchdog0 output
      \arg        TRIGSEL_INPUT_ADC0_WD1_OUT: trigger input source ADC0 watchdog1 output
      \arg        TRIGSEL_INPUT_ADC0_WD2_OUT: trigger input source ADC0 watchdog2 output
      \arg        TRIGSEL_INPUT_ADC1_WD0_OUT: trigger input source ADC1 watchdog0 output
      \arg        TRIGSEL_INPUT_ADC1_WD1_OUT: trigger input source ADC1 watchdog1 output
      \arg        TRIGSEL_INPUT_ADC1_WD2_OUT: trigger input source ADC1 watchdog2 output
      \arg        TRIGSEL_INPUT_ADC2_WD0_OUT: trigger input source ADC2 watchdog0 output
      \arg        TRIGSEL_INPUT_ADC2_WD1_OUT: trigger input source ADC2 watchdog1 output
      \arg        TRIGSEL_INPUT_ADC2_WD2_OUT: trigger input source ADC2 watchdog2 output
      \arg        TRIGSEL_INPUT_ADC3_WD0_OUT: trigger input source ADC3 watchdog0 output
      \arg        TRIGSEL_INPUT_ADC3_WD1_OUT: trigger input source ADC3 watchdog1 output
      \arg        TRIGSEL_INPUT_ADC3_WD2_OUT: trigger input source ADC3 watchdog2 output
      \arg        TRIGSEL_INPUT_HXTAL_DIV32_TRIG: trigger input source HXTAL_DIV32
      \arg        TRIGSEL_INPUT_IRC32K_TRIG: trigger input source IRC32K
      \arg        TRIGSEL_INPUT_LXTAL_TRIG: trigger input source LXTAL
      \arg        TRIGSEL_INPUT_CKOUT_TRIG: trigger input source CKOUT
      \arg        TRIGSEL_INPUT_EXTI2_TRIG: trigger input source EXTI2
      \arg        TRIGSEL_INPUT_EXTI3_TRIG: trigger input source EXTI3
      \arg        TRIGSEL_INPUT_EXTI9_TRIG: trigger input source EXTI9
      \arg        TRIGSEL_INPUT_EXTI10_TRIG: trigger input source EXTI10
      \arg        TRIGSEL_INPUT_EXTI11_TRIG: trigger input source EXTI11
      \arg        TRIGSEL_INPUT_EXTI15_TRIG: trigger input source EXTI15
      \arg        TRIGSEL_INPUT_RTC_WAKEUP: trigger input source RTC wakeup
      \arg        TRIGSEL_INPUT_RTC_ALARM0: trigger input source RTC alarm0
      \arg        TRIGSEL_INPUT_RTC_ALARM1: trigger input source RTC alarm1
      \arg        TRIGSEL_INPUT_RTC_TAMP0: trigger input source RTC tamper0
      \arg        TRIGSEL_INPUT_RTC_TAMP1: trigger input source RTC tamper1
      \arg        TRIGSEL_INPUT_RTC_TAMP2: trigger input source RTC tamper2
      \arg        TRIGSEL_INPUT_CMP0_OUT: trigger input source CMP0_OUT
      \arg        TRIGSEL_INPUT_CMP1_OUT: trigger input source CMP1_OUT
      \arg        TRIGSEL_INPUT_CMP2_OUT: trigger input source CMP2_OUT
      \arg        TRIGSEL_INPUT_CMP3_OUT: trigger input source CMP3_OUT
      \arg        TRIGSEL_INPUT_CMP4_OUT: trigger input source CMP4_OUT
      \arg        TRIGSEL_INPUT_CMP5_OUT: trigger input source CMP5_OUT
      \arg        TRIGSEL_INPUT_CMP6_OUT: trigger input source CMP6_OUT
      \arg        TRIGSEL_INPUT_CMP7_OUT: trigger input source CMP7_OUT
      \arg        TRIGSEL_INPUT_CLA_OUT0: trigger input source CLA_OUT0
      \arg        TRIGSEL_INPUT_CLA_OUT1: trigger input source CLA_OUT1
      \arg        TRIGSEL_INPUT_CLA_OUT2: trigger input source CLA_OUT2
      \arg        TRIGSEL_INPUT_CLA_OUT3: trigger input source CLA_OUT3
      \arg        TRIGSEL_INPUT_HRTIMER_ST0_TRIG0: trigger input source HRTIMER_ST0_TRIG1
      \arg        TRIGSEL_INPUT_HRTIMER_ST1_TRIG0: trigger input source HRTIMER_ST1_TRIG1
      \arg        TRIGSEL_INPUT_HRTIMER_ST2_TRIG0: trigger input source HRTIMER_ST2_TRIG1
      \arg        TRIGSEL_INPUT_HRTIMER_ST3_TRIG0: trigger input source HRTIMER_ST3_TRIG1
      \arg        TRIGSEL_INPUT_HRTIMER_ST4_TRIG0: trigger input source HRTIMER_ST4_TRIG1
      \arg        TRIGSEL_INPUT_HRTIMER_ST5_TRIG0: trigger input source HRTIMER_ST5_TRIG1
      \arg        TRIGSEL_INPUT_HRTIMER_ST6_TRIG0: trigger input source HRTIMER_ST6_TRIG1
      \arg        TRIGSEL_INPUT_HRTIMER_ST7_TRIG0: trigger input source HRTIMER_ST7_TRIG1
      \arg        TRIGSEL_INPUT_HRTIMER_ST0_CH0: trigger input source HRTIMER slave0 CH0
      \arg        TRIGSEL_INPUT_HRTIMER_ST0_CH1: trigger input source HRTIMER slave0 CH1
      \arg        TRIGSEL_INPUT_HRTIMER_ST1_CH0: trigger input source HRTIMER slave1 CH0
      \arg        TRIGSEL_INPUT_HRTIMER_ST1_CH1: trigger input source HRTIMER slave1 CH1
      \arg        TRIGSEL_INPUT_HRTIMER_ST2_CH0: trigger input source HRTIMER slave2 CH0
      \arg        TRIGSEL_INPUT_HRTIMER_ST2_CH1: trigger input source HRTIMER slave2 CH1
      \arg        TRIGSEL_INPUT_HRTIMER_ST3_CH0: trigger input source HRTIMER slave3 CH0
      \arg        TRIGSEL_INPUT_HRTIMER_ST3_CH1: trigger input source HRTIMER slave3 CH1
      \arg        TRIGSEL_INPUT_HRTIMER_ST4_CH0: trigger input source HRTIMER slave4 CH0
      \arg        TRIGSEL_INPUT_HRTIMER_ST4_CH1: trigger input source HRTIMER slave4 CH1
      \arg        TRIGSEL_INPUT_HRTIMER_ST5_CH0: trigger input source HRTIMER slave5 CH0
      \arg        TRIGSEL_INPUT_HRTIMER_ST5_CH1: trigger input source HRTIMER slave5 CH1
      \arg        TRIGSEL_INPUT_HRTIMER_ST6_CH0: trigger input source HRTIMER slave6 CH0
      \arg        TRIGSEL_INPUT_HRTIMER_ST6_CH1: trigger input source HRTIMER slave6 CH1
      \arg        TRIGSEL_INPUT_HRTIMER_ST7_CH0: trigger input source HRTIMER slave7 CH0
      \arg        TRIGSEL_INPUT_HRTIMER_ST7_CH1: trigger input source HRTIMER slave7 CH1
      \arg        TRIGSEL_INPUT_ADC0_CONV: trigger input source ADC0 CONV
      \arg        TRIGSEL_INPUT_ADC1_CONV: trigger input source ADC1 CONV
      \arg        TRIGSEL_INPUT_ADC2_CONV: trigger input source ADC2 CONV
      \arg        TRIGSEL_INPUT_ADC3_CONV: trigger input source ADC3 CONV
      \arg        TRIGSEL_INPUT_LCKM_OUT: trigger input source LCKM_OUT
    \param[out] none
    \retval     none
*/
void trigsel_init(trigsel_periph_enum target_periph, trigsel_source_enum trigger_source)
{
    uint32_t reg;
    
    /* if register write is enabled, set trigger source to target peripheral */
    if (RESET == trigsel_register_lock_get(target_periph)){
        reg = TRIGSEL_TARGET_REG(target_periph);
        reg &= ~TRIGSEL_TARGET_PERIPH_MASK(target_periph);
        reg |= ((uint32_t)trigger_source << TRIGSEL_TARGET_PERIPH_SHIFT(target_periph)) & TRIGSEL_TARGET_PERIPH_MASK(target_periph);
        TRIGSEL_TARGET_REG(target_periph) = reg;
    }
}

/*!
    \brief      get the trigger input signal for target peripheral
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_ADC0_ROUTRG: output target peripheral ADC0_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC1_ROUTRG: output target peripheral ADC1_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC2_ROUTRG: output target peripheral ADC2_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC3_ROUTRG: output target peripheral ADC3_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC3_INSTRG: output target peripheral ADC3_INSTRG
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER14_BRKIN0: output target peripheral TIMER14_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER15_BRKIN0: output target peripheral TIMER15_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER16_BRKIN0: output target peripheral TIMER16_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN0: output target peripheral TIMER19_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN1: output target peripheral TIMER19_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN2: output target peripheral TIMER19_BRKIN2
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_TIMER0_ETI: output target peripheral TIMER0_ETI
      \arg        TRIGSEL_OUTPUT_TIMER1_ETI: output target peripheral TIMER1_ETI
      \arg        TRIGSEL_OUTPUT_TIMER2_ETI: output target peripheral TIMER2_ETI
      \arg        TRIGSEL_OUTPUT_TIMER3_ETI: output target peripheral TIMER3_ETI
      \arg        TRIGSEL_OUTPUT_TIMER4_ETI: output target peripheral TIMER4_ETI
      \arg        TRIGSEL_OUTPUT_TIMER7_ETI: output target peripheral TIMER7_ETI
      \arg        TRIGSEL_OUTPUT_TIMER19_ETI: output target peripheral TIMER19_ETI
      \arg        TRIGSEL_OUTPUT_HPDF_ITRG: output target peripheral HPDF_ITRG
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI14: output target peripheral TIMER0_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI14: output target peripheral TIMER1_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI14: output target peripheral TIMER2_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER3_ITI14: output target peripheral TIMER3_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER4_ITI14: output target peripheral TIMER4_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI14: output target peripheral TIMER7_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER14_ITI14: output target peripheral TIMER14_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER19_ITI14: output target peripheral TIMER19_ITI14
      \arg        TRIGSEL_OUTPUT_DAC0_EXTRIG0: output target peripheral DAC0_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC0_EXTRIG1: output target peripheral DAC0_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC1_EXTRIG0: output target peripheral DAC1_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC1_EXTRIG1: output target peripheral DAC1_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC2_EXTRIG0: output target peripheral DAC2_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC2_EXTRIG1: output target peripheral DAC2_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC3_EXTRIG0: output target peripheral DAC3_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC3_EXTRIG1: output target peripheral DAC3_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC0_ST_EXTRIG0: output target peripheral DAC0_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC0_ST_EXTRIG1: output target peripheral DAC0_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC1_ST_EXTRIG0: output target peripheral DAC1_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC1_ST_EXTRIG1: output target peripheral DAC1_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC2_ST_EXTRIG0: output target peripheral DAC2_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC2_ST_EXTRIG1: output target peripheral DAC2_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC3_ST_EXTRIG0: output target peripheral DAC3_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC3_ST_EXTRIG1: output target peripheral DAC3_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_CLA_IN0: output target peripheral CLA_IN0
      \arg        TRIGSEL_OUTPUT_CLA_IN1: output target peripheral CLA_IN1
      \arg        TRIGSEL_OUTPUT_CLA_IN2: output target peripheral CLA_IN2
      \arg        TRIGSEL_OUTPUT_CLA_IN3: output target peripheral CLA_IN3
      \arg        TRIGSEL_OUTPUT_CLA_IN4: output target peripheral CLA_IN4
      \arg        TRIGSEL_OUTPUT_CLA_IN5: output target peripheral CLA_IN5
      \arg        TRIGSEL_OUTPUT_CLA_IN6: output target peripheral CLA_IN6
      \arg        TRIGSEL_OUTPUT_CLA_IN7: output target peripheral CLA_IN7
      \arg        TRIGSEL_OUTPUT_CLA_IN8: output target peripheral CLA_IN8
      \arg        TRIGSEL_OUTPUT_CLA_IN9: output target peripheral CLA_IN9
      \arg        TRIGSEL_OUTPUT_CLA_IN10: output target peripheral CLA_IN10
      \arg        TRIGSEL_OUTPUT_CLA_IN11: output target peripheral CLA_IN11
    \param[out] none
    \retval  trigger_source: trigger source value(0~186)
*/
trigsel_source_enum trigsel_trigger_source_get(trigsel_periph_enum target_periph)
{
    trigsel_source_enum trigger_source;

    trigger_source = (trigsel_source_enum)((TRIGSEL_TARGET_REG(target_periph) & TRIGSEL_TARGET_PERIPH_MASK(target_periph)) >> TRIGSEL_TARGET_PERIPH_SHIFT(target_periph));

    return trigger_source;
}

/*!
    \brief      lock the trigger register
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_ADC0_ROUTRG: output target peripheral ADC0_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC1_ROUTRG: output target peripheral ADC1_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC2_ROUTRG: output target peripheral ADC2_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC3_ROUTRG: output target peripheral ADC3_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC3_INSTRG: output target peripheral ADC3_INSTRG
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER14_BRKIN0: output target peripheral TIMER14_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER15_BRKIN0: output target peripheral TIMER15_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER16_BRKIN0: output target peripheral TIMER16_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN0: output target peripheral TIMER19_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN1: output target peripheral TIMER19_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN2: output target peripheral TIMER19_BRKIN2
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_TIMER0_ETI: output target peripheral TIMER0_ETI
      \arg        TRIGSEL_OUTPUT_TIMER1_ETI: output target peripheral TIMER1_ETI
      \arg        TRIGSEL_OUTPUT_TIMER2_ETI: output target peripheral TIMER2_ETI
      \arg        TRIGSEL_OUTPUT_TIMER3_ETI: output target peripheral TIMER3_ETI
      \arg        TRIGSEL_OUTPUT_TIMER4_ETI: output target peripheral TIMER4_ETI
      \arg        TRIGSEL_OUTPUT_TIMER7_ETI: output target peripheral TIMER7_ETI
      \arg        TRIGSEL_OUTPUT_TIMER19_ETI: output target peripheral TIMER19_ETI
      \arg        TRIGSEL_OUTPUT_HPDF_ITRG: output target peripheral HPDF_ITRG
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI14: output target peripheral TIMER0_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI14: output target peripheral TIMER1_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI14: output target peripheral TIMER2_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER3_ITI14: output target peripheral TIMER3_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER4_ITI14: output target peripheral TIMER4_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI14: output target peripheral TIMER7_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER14_ITI14: output target peripheral TIMER14_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER19_ITI14: output target peripheral TIMER19_ITI14
      \arg        TRIGSEL_OUTPUT_DAC0_EXTRIG0: output target peripheral DAC0_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC0_EXTRIG1: output target peripheral DAC0_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC1_EXTRIG0: output target peripheral DAC1_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC1_EXTRIG1: output target peripheral DAC1_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC2_EXTRIG0: output target peripheral DAC2_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC2_EXTRIG1: output target peripheral DAC2_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC3_EXTRIG0: output target peripheral DAC3_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC3_EXTRIG1: output target peripheral DAC3_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC0_ST_EXTRIG0: output target peripheral DAC0_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC0_ST_EXTRIG1: output target peripheral DAC0_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC1_ST_EXTRIG0: output target peripheral DAC1_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC1_ST_EXTRIG1: output target peripheral DAC1_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC2_ST_EXTRIG0: output target peripheral DAC2_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC2_ST_EXTRIG1: output target peripheral DAC2_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC3_ST_EXTRIG0: output target peripheral DAC3_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC3_ST_EXTRIG1: output target peripheral DAC3_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_CLA_IN0: output target peripheral CLA_IN0
      \arg        TRIGSEL_OUTPUT_CLA_IN1: output target peripheral CLA_IN1
      \arg        TRIGSEL_OUTPUT_CLA_IN2: output target peripheral CLA_IN2
      \arg        TRIGSEL_OUTPUT_CLA_IN3: output target peripheral CLA_IN3
      \arg        TRIGSEL_OUTPUT_CLA_IN4: output target peripheral CLA_IN4
      \arg        TRIGSEL_OUTPUT_CLA_IN5: output target peripheral CLA_IN5
      \arg        TRIGSEL_OUTPUT_CLA_IN6: output target peripheral CLA_IN6
      \arg        TRIGSEL_OUTPUT_CLA_IN7: output target peripheral CLA_IN7
      \arg        TRIGSEL_OUTPUT_CLA_IN8: output target peripheral CLA_IN8
      \arg        TRIGSEL_OUTPUT_CLA_IN9: output target peripheral CLA_IN9
      \arg        TRIGSEL_OUTPUT_CLA_IN10: output target peripheral CLA_IN10
      \arg        TRIGSEL_OUTPUT_CLA_IN11: output target peripheral CLA_IN11
    \param[out] none
    \retval     none
*/
void trigsel_register_lock_set(trigsel_periph_enum target_periph)
{
    /* lock target peripheral register */
    TRIGSEL_TARGET_REG(target_periph) |= TRIGSEL_TARGET_LK;
}

/*!
    \brief      get the trigger register lock status
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_ADC0_ROUTRG: output target peripheral ADC0_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC1_ROUTRG: output target peripheral ADC1_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC2_ROUTRG: output target peripheral ADC2_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC3_ROUTRG: output target peripheral ADC3_ROUTRG
      \arg        TRIGSEL_OUTPUT_ADC3_INSTRG: output target peripheral ADC3_INSTRG
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER14_BRKIN0: output target peripheral TIMER14_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER15_BRKIN0: output target peripheral TIMER15_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER16_BRKIN0: output target peripheral TIMER16_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN0: output target peripheral TIMER19_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN1: output target peripheral TIMER19_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN2: output target peripheral TIMER19_BRKIN2
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK 
      \arg        TRIGSEL_OUTPUT_TIMER0_ETI: output target peripheral TIMER0_ETI
      \arg        TRIGSEL_OUTPUT_TIMER1_ETI: output target peripheral TIMER1_ETI
      \arg        TRIGSEL_OUTPUT_TIMER2_ETI: output target peripheral TIMER2_ETI
      \arg        TRIGSEL_OUTPUT_TIMER3_ETI: output target peripheral TIMER3_ETI
      \arg        TRIGSEL_OUTPUT_TIMER4_ETI: output target peripheral TIMER4_ETI
      \arg        TRIGSEL_OUTPUT_TIMER7_ETI: output target peripheral TIMER7_ETI
      \arg        TRIGSEL_OUTPUT_TIMER19_ETI: output target peripheral TIMER19_ETI
      \arg        TRIGSEL_OUTPUT_HPDF_ITRG: output target peripheral HPDF_ITRG
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI14: output target peripheral TIMER0_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI14: output target peripheral TIMER1_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI14: output target peripheral TIMER2_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER3_ITI14: output target peripheral TIMER3_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER4_ITI14: output target peripheral TIMER4_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI14: output target peripheral TIMER7_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER14_ITI14: output target peripheral TIMER14_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER19_ITI14: output target peripheral TIMER19_ITI14
      \arg        TRIGSEL_OUTPUT_DAC0_EXTRIG0: output target peripheral DAC0_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC0_EXTRIG1: output target peripheral DAC0_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC1_EXTRIG0: output target peripheral DAC1_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC1_EXTRIG1: output target peripheral DAC1_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC2_EXTRIG0: output target peripheral DAC2_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC2_EXTRIG1: output target peripheral DAC2_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC3_EXTRIG0: output target peripheral DAC3_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC3_EXTRIG1: output target peripheral DAC3_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC0_ST_EXTRIG0: output target peripheral DAC0_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC0_ST_EXTRIG1: output target peripheral DAC0_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC1_ST_EXTRIG0: output target peripheral DAC1_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC1_ST_EXTRIG1: output target peripheral DAC1_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC2_ST_EXTRIG0: output target peripheral DAC2_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC2_ST_EXTRIG1: output target peripheral DAC2_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_DAC3_ST_EXTRIG0: output target peripheral DAC3_ST_EXTRIG0
      \arg        TRIGSEL_OUTPUT_DAC3_ST_EXTRIG1: output target peripheral DAC3_ST_EXTRIG1
      \arg        TRIGSEL_OUTPUT_CLA_IN0: output target peripheral CLA_IN0
      \arg        TRIGSEL_OUTPUT_CLA_IN1: output target peripheral CLA_IN1
      \arg        TRIGSEL_OUTPUT_CLA_IN2: output target peripheral CLA_IN2
      \arg        TRIGSEL_OUTPUT_CLA_IN3: output target peripheral CLA_IN3
      \arg        TRIGSEL_OUTPUT_CLA_IN4: output target peripheral CLA_IN4
      \arg        TRIGSEL_OUTPUT_CLA_IN5: output target peripheral CLA_IN5
      \arg        TRIGSEL_OUTPUT_CLA_IN6: output target peripheral CLA_IN6
      \arg        TRIGSEL_OUTPUT_CLA_IN7: output target peripheral CLA_IN7
      \arg        TRIGSEL_OUTPUT_CLA_IN8: output target peripheral CLA_IN8
      \arg        TRIGSEL_OUTPUT_CLA_IN9: output target peripheral CLA_IN9
      \arg        TRIGSEL_OUTPUT_CLA_IN10: output target peripheral CLA_IN10
      \arg        TRIGSEL_OUTPUT_CLA_IN11: output target peripheral CLA_IN11
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus trigsel_register_lock_get(trigsel_periph_enum target_periph)
{
    if(RESET != (TRIGSEL_TARGET_REG(target_periph) & TRIGSEL_TARGET_LK)){
        return SET;
    }else{
        return RESET;
    }
}
