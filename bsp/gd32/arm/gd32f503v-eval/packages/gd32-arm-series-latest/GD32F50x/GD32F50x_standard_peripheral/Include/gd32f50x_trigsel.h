/*!
    \file    gd32f50x_trigsel.h
    \brief   definitions for the TRIGSEL
    
    \version 2025-11-03, V1.0.0, firmware for GD32F50x
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

#ifndef GD32F50X_TRIGSEL_H
#define GD32F50X_TRIGSEL_H

#include "gd32f50x.h"

/* TRIGSEL definitions */
#define TRIGSEL                           TRIGSEL_BASE                      /*!< TRIGSEL base address */

/* register definitions */
#define TRIGSEL_EXTOUT_0                  REG32((TRIGSEL) + 0x00000000U)    /*!< TRIGSEL trigger selection for EXTOUT0 register */
#define TRIGSEL_EXTOUT_1                  REG32((TRIGSEL) + 0x00000004U)    /*!< TRIGSEL trigger selection for EXTOUT1 register */
#define TRIGSEL_EXTOUT_2                  REG32((TRIGSEL) + 0x00000008U)    /*!< TRIGSEL trigger selection for EXTOUT2 register */
#define TRIGSEL_EXTOUT_3                  REG32((TRIGSEL) + 0x0000000CU)    /*!< TRIGSEL trigger selection for EXTOUT3 register */
#define TRIGSEL_TIMER0ITI                 REG32((TRIGSEL) + 0x00000010U)    /*!< TRIGSEL trigger selection for TIMER0ITI register */
#define TRIGSEL_TIMER1ITI                 REG32((TRIGSEL) + 0x00000014U)    /*!< TRIGSEL trigger selection for TIMER1ITI register */
#define TRIGSEL_TIMER2ITI                 REG32((TRIGSEL) + 0x00000018U)    /*!< TRIGSEL trigger selection for TIMER2ITI register */
#define TRIGSEL_TIMER3ITI                 REG32((TRIGSEL) + 0x0000001CU)    /*!< TRIGSEL trigger selection for TIMER3ITI register */
#define TRIGSEL_TIMER4ITI                 REG32((TRIGSEL) + 0x00000020U)    /*!< TRIGSEL trigger selection for TIMER4ITI register */
#define TRIGSEL_TIMER7ITI                 REG32((TRIGSEL) + 0x00000024U)    /*!< TRIGSEL trigger selection for TIMER7ITI register */
#define TRIGSEL_TIMER15ITI                REG32((TRIGSEL) + 0x0000002CU)    /*!< TRIGSEL trigger selection for TIMER15ITI register */
#define TRIGSEL_TIMER16ITI                REG32((TRIGSEL) + 0x00000030U)    /*!< TRIGSEL trigger selection for TIMER16ITI register */
#define TRIGSEL_DAC                       REG32((TRIGSEL) + 0x00000034U)    /*!< TRIGSEL trigger selection for DAC register */
#define TRIGSEL_ADC0_ROUTRG               REG32((TRIGSEL) + 0x00000038U)    /*!< TRIGSEL trigger selection for ADC0_ROUTRG register */
#define TRIGSEL_ADC0_INSTRG               REG32((TRIGSEL) + 0x0000003CU)    /*!< TRIGSEL trigger selection for ADC0_INSTRG register */
#define TRIGSEL_ADC1_ROUTRG               REG32((TRIGSEL) + 0x00000040U)    /*!< TRIGSEL trigger selection for ADC1_ROUTRG register */
#define TRIGSEL_ADC1_INSTRG               REG32((TRIGSEL) + 0x00000044U)    /*!< TRIGSEL trigger selection for ADC1_INSTRG register */
#define TRIGSEL_ADC2_ROUTRG               REG32((TRIGSEL) + 0x00000048U)    /*!< TRIGSEL trigger selection for ADC2_ROUTRG register */
#define TRIGSEL_ADC2_INSTRG               REG32((TRIGSEL) + 0x0000004CU)    /*!< TRIGSEL trigger selection for ADC2_INSTRG register */
#define TRIGSEL_TIMER0BRKIN               REG32((TRIGSEL) + 0x00000050U)    /*!< TRIGSEL trigger selection for TIMER0BRKIN register */
#define TRIGSEL_TIMER0CHBRKIN             REG32((TRIGSEL) + 0x00000054U)    /*!< TRIGSEL trigger selection for TIMER0CHBRKIN register */
#define TRIGSEL_TIMER7BRKIN               REG32((TRIGSEL) + 0x00000058U)    /*!< TRIGSEL trigger selection for TIMER7BRKIN register */
#define TRIGSEL_TIMER7CHBRKIN             REG32((TRIGSEL) + 0x0000005CU)    /*!< TRIGSEL trigger selection for TIMER7CHBRKIN register */
#define TRIGSEL_TIMER15BRKIN              REG32((TRIGSEL) + 0x00000060U)    /*!< TRIGSEL trigger selection for TIMER15BRKIN register */
#define TRIGSEL_TIMER16BRKIN              REG32((TRIGSEL) + 0x00000064U)    /*!< TRIGSEL trigger selection for TIMER16BRKIN register */

/* bit definitions */
/* trigger input source selection */
#define TRIGSEL_TARGET_INSEL0             BITS(0,7)                         /*!< trigger input source selection for output0 */
#define TRIGSEL_TARGET_INSEL1             BITS(8,15)                        /*!< trigger input source selection for output1 */
#define TRIGSEL_TARGET_LK                 BIT(31)                           /*!< TRIGSEL register lock */

/* constants definitions */
/* trigger source definitions */
typedef enum
{
    TRIGSEL_INPUT_VSS                    = ((uint8_t)0x00U),               /*!< trigger input source VSS */
    TRIGSEL_INPUT_VDD                    = ((uint8_t)0x01U),               /*!< trigger input source VDD */
    TRIGSEL_INPUT_TRIGSEL_IN0            = ((uint8_t)0x02U),               /*!< trigger input source TRIGSEL_IN0 */
    TRIGSEL_INPUT_TRIGSEL_IN1            = ((uint8_t)0x03U),               /*!< trigger input source TRIGSEL_IN1 */
    TRIGSEL_INPUT_TRIGSEL_IN2            = ((uint8_t)0x04U),               /*!< trigger input source TRIGSEL_IN2 */
    TRIGSEL_INPUT_TRIGSEL_IN3            = ((uint8_t)0x05U),               /*!< trigger input source TRIGSEL_IN3 */
    TRIGSEL_INPUT_TRIGSEL_IN4            = ((uint8_t)0x06U),               /*!< trigger input source TRIGSEL_IN4 */
    TRIGSEL_INPUT_TRIGSEL_IN5            = ((uint8_t)0x07U),               /*!< trigger input source TRIGSEL_IN5 */
    TRIGSEL_INPUT_TRIGSEL_IN6            = ((uint8_t)0x08U),               /*!< trigger input source TRIGSEL_IN6 */
    TRIGSEL_INPUT_TRIGSEL_IN7            = ((uint8_t)0x09U),               /*!< trigger input source TRIGSEL_IN7 */
    TRIGSEL_INPUT_TIMER0_TRGO            = ((uint8_t)0x0AU),               /*!< trigger input source TIMER0_TRGO */
    TRIGSEL_INPUT_TIMER0_CH0             = ((uint8_t)0x0BU),               /*!< trigger input source TIMER0_CH0 */
    TRIGSEL_INPUT_TIMER0_CH1             = ((uint8_t)0x0CU),               /*!< trigger input source TIMER0_CH1 */
    TRIGSEL_INPUT_TIMER0_CH2             = ((uint8_t)0x0DU),               /*!< trigger input source TIMER0_CH2 */
    TRIGSEL_INPUT_TIMER0_CH3             = ((uint8_t)0x0EU),               /*!< trigger input source TIMER0_CH3 */
    TRIGSEL_INPUT_TIMER7_TRGO            = ((uint8_t)0x0FU),               /*!< trigger input source TIMER7_TRGO */
    TRIGSEL_INPUT_TIMER7_CH0             = ((uint8_t)0x10U),               /*!< trigger input source TIMER7_CH0 */
    TRIGSEL_INPUT_TIMER7_CH1             = ((uint8_t)0x11U),               /*!< trigger input source TIMER7_CH1 */
    TRIGSEL_INPUT_TIMER7_CH2             = ((uint8_t)0x12U),               /*!< trigger input source TIMER7_CH2 */
    TRIGSEL_INPUT_TIMER7_CH3             = ((uint8_t)0x13U),               /*!< trigger input source TIMER7_CH3 */
    TRIGSEL_INPUT_TIMER5_TRGO            = ((uint8_t)0x14U),               /*!< trigger input source TIMER5_TRGO */
    TRIGSEL_INPUT_TIMER6_TRGO            = ((uint8_t)0x15U),               /*!< trigger input source TIMER6_TRGO */
    TRIGSEL_INPUT_TIMER1_TRGO            = ((uint8_t)0x16U),               /*!< trigger input source TIMER1_TRGO */
    TRIGSEL_INPUT_TIMER1_CH0             = ((uint8_t)0x17U),               /*!< trigger input source TIMER1_CH0 */
    TRIGSEL_INPUT_TIMER1_CH1             = ((uint8_t)0x18U),               /*!< trigger input source TIMER1_CH1 */
    TRIGSEL_INPUT_TIMER1_CH2             = ((uint8_t)0x19U),               /*!< trigger input source TIMER1_CH2 */
    TRIGSEL_INPUT_TIMER1_CH3             = ((uint8_t)0x1AU),               /*!< trigger input source TIMER1_CH3 */
    TRIGSEL_INPUT_TIMER2_TRGO            = ((uint8_t)0x1BU),               /*!< trigger input source TIMER2_TRGO */
    TRIGSEL_INPUT_TIMER2_CH0             = ((uint8_t)0x1CU),               /*!< trigger input source TIMER2_CH0 */
    TRIGSEL_INPUT_TIMER2_CH1             = ((uint8_t)0x1DU),               /*!< trigger input source TIMER2_CH1 */
    TRIGSEL_INPUT_TIMER2_CH2             = ((uint8_t)0x1EU),               /*!< trigger input source TIMER2_CH2 */
    TRIGSEL_INPUT_TIMER2_CH3             = ((uint8_t)0x1FU),               /*!< trigger input source TIMER2_CH3 */
    TRIGSEL_INPUT_TIMER3_TRGO            = ((uint8_t)0x20U),               /*!< trigger input source TIMER3_TRGO */
    TRIGSEL_INPUT_TIMER3_CH0             = ((uint8_t)0x21U),               /*!< trigger input source TIMER3_CH0 */
    TRIGSEL_INPUT_TIMER3_CH1             = ((uint8_t)0x22U),               /*!< trigger input source TIMER3_CH1 */
    TRIGSEL_INPUT_TIMER3_CH2             = ((uint8_t)0x23U),               /*!< trigger input source TIMER3_CH2 */
    TRIGSEL_INPUT_TIMER3_CH3             = ((uint8_t)0x24U),               /*!< trigger input source TIMER3_CH3 */
    TRIGSEL_INPUT_TIMER4_TRGO            = ((uint8_t)0x25U),               /*!< trigger input source TIMER4_TRGO */
    TRIGSEL_INPUT_TIMER4_CH0             = ((uint8_t)0x26U),               /*!< trigger input source TIMER4_CH0 */
    TRIGSEL_INPUT_TIMER4_CH1             = ((uint8_t)0x27U),               /*!< trigger input source TIMER4_CH1 */
    TRIGSEL_INPUT_TIMER4_CH2             = ((uint8_t)0x28U),               /*!< trigger input source TIMER4_CH2 */
    TRIGSEL_INPUT_TIMER4_CH3             = ((uint8_t)0x29U),               /*!< trigger input source TIMER4_CH3 */
    TRIGSEL_INPUT_TIMER15_TRGO           = ((uint8_t)0x2FU),               /*!< trigger input source TIMER15_TRGO */
    TRIGSEL_INPUT_TIMER15_CH0            = ((uint8_t)0x30U),               /*!< trigger input source TIMER15_CH0 */
    TRIGSEL_INPUT_TIMER15_CH1            = ((uint8_t)0x31U),               /*!< trigger input source TIMER15_CH1 */
    TRIGSEL_INPUT_TIMER15_MCH0           = ((uint8_t)0x32U),               /*!< trigger input source TIMER15_MCH0 */
    TRIGSEL_INPUT_TIMER16_TRGO           = ((uint8_t)0x33U),               /*!< trigger input source TIMER16_TRGO */
    TRIGSEL_INPUT_TIMER16_CH0            = ((uint8_t)0x34U),               /*!< trigger input source TIMER16_CH0 */
    TRIGSEL_INPUT_TIMER16_CH1            = ((uint8_t)0x35U),               /*!< trigger input source TIMER16_CH1 */
    TRIGSEL_INPUT_TIMER16_MCH0           = ((uint8_t)0x36U),               /*!< trigger input source TIMER16_MCH0 */
    TRIGSEL_INPUT_ADC0_WD0_OUT           = ((uint8_t)0x37U),               /*!< trigger input source ADC0_WD0_OUT */
    TRIGSEL_INPUT_ADC0_WD1_OUT           = ((uint8_t)0x38U),               /*!< trigger input source ADC0_WD1_OUT */
    TRIGSEL_INPUT_ADC0_WD2_OUT           = ((uint8_t)0x39U),               /*!< trigger input source ADC0_WD2_OUT */
    TRIGSEL_INPUT_ADC1_WD0_OUT           = ((uint8_t)0x3AU),               /*!< trigger input source ADC1_WD0_OUT */
    TRIGSEL_INPUT_ADC1_WD1_OUT           = ((uint8_t)0x3BU),               /*!< trigger input source ADC1_WD1_OUT */
    TRIGSEL_INPUT_ADC1_WD2_OUT           = ((uint8_t)0x3CU),               /*!< trigger input source ADC1_WD2_OUT */
    TRIGSEL_INPUT_ADC2_WD0_OUT           = ((uint8_t)0x3DU),               /*!< trigger input source ADC2_WD0_OUT */
    TRIGSEL_INPUT_ADC2_WD1_OUT           = ((uint8_t)0x3EU),               /*!< trigger input source ADC2_WD1_OUT */
    TRIGSEL_INPUT_ADC2_WD2_OUT           = ((uint8_t)0x3FU),               /*!< trigger input source ADC2_WD2_OUT */
    TRIGSEL_INPUT_CMP0_OUT               = ((uint8_t)0x40U),               /*!< trigger input source CMP0_OUT */
    TRIGSEL_INPUT_CK_OUT                 = ((uint8_t)0x41U),               /*!< trigger input source CK_OUT */
    TRIGSEL_INPUT_TIMER0_BKIN            = ((uint8_t)0x42U),               /*!< trigger input source TIMER0_BKIN */
    TRIGSEL_INPUT_TIMER0_CH0BKIN         = ((uint8_t)0x43U),               /*!< trigger input source TIMER0_CH0BKIN */
    TRIGSEL_INPUT_TIMER0_CH1BKIN         = ((uint8_t)0x44U),               /*!< trigger input source TIMER0_CH1BKIN */
    TRIGSEL_INPUT_TIMER0_CH2BKIN         = ((uint8_t)0x45U),               /*!< trigger input source TIMER0_CH2BKIN */
    TRIGSEL_INPUT_TIMER7_BKIN            = ((uint8_t)0x46U),               /*!< trigger input source TIMER7_BKIN */
    TRIGSEL_INPUT_TIMER7_CH0BKIN         = ((uint8_t)0x47U),               /*!< trigger input source TIMER7_CH0BKIN */
    TRIGSEL_INPUT_TIMER7_CH1BKIN         = ((uint8_t)0x48U),               /*!< trigger input source TIMER7_CH1BKIN */
    TRIGSEL_INPUT_TIMER7_CH2BKIN         = ((uint8_t)0x49U),               /*!< trigger input source TIMER7_CH2BKIN */
    TRIGSEL_INPUT_TIMER15_BKIN           = ((uint8_t)0x4AU),               /*!< trigger input source TIMER15_BKIN */
    TRIGSEL_INPUT_TIMER16_BKIN           = ((uint8_t)0x4BU),               /*!< trigger input source TIMER16_BKIN */
    TRIGSEL_INPUT_EXTI9                  = ((uint8_t)0x4CU),               /*!< trigger input source EXTI9 */
    TRIGSEL_INPUT_EXTI11                 = ((uint8_t)0x4DU),               /*!< trigger input source EXTI11 */
    TRIGSEL_INPUT_EXTI15                 = ((uint8_t)0x4EU),               /*!< trigger input source EXTI15 */
}trigsel_source_enum;

/* target peripheral definitions */
typedef enum
{
    TRIGSEL_OUTPUT_TRIGSEL_OUT0      = ((uint8_t)0x00U),   /*!< output target peripheral TRIGSEL_OUT0 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT1      = ((uint8_t)0x01U),   /*!< output target peripheral TRIGSEL_OUT1 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT2      = ((uint8_t)0x04U),   /*!< output target peripheral TRIGSEL_OUT2 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT3      = ((uint8_t)0x05U),   /*!< output target peripheral TRIGSEL_OUT3 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT4      = ((uint8_t)0x08U),   /*!< output target peripheral TRIGSEL_OUT4 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT5      = ((uint8_t)0x09U),   /*!< output target peripheral TRIGSEL_OUT5 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT6      = ((uint8_t)0x0CU),   /*!< output target peripheral TRIGSEL_OUT6 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT7      = ((uint8_t)0x0DU),   /*!< output target peripheral TRIGSEL_OUT7 pin */
    TRIGSEL_OUTPUT_TIMER0_ITI        = ((uint8_t)0x10U),   /*!< output target peripheral TIMER0_ITI */
    TRIGSEL_OUTPUT_TIMER1_ITI        = ((uint8_t)0x14U),   /*!< output target peripheral TIMER1_ITI */
    TRIGSEL_OUTPUT_TIMER2_ITI        = ((uint8_t)0x18U),   /*!< output target peripheral TIMER2_ITI */
    TRIGSEL_OUTPUT_TIMER3_ITI        = ((uint8_t)0x1CU),   /*!< output target peripheral TIMER3_ITI */
    TRIGSEL_OUTPUT_TIMER4_ITI        = ((uint8_t)0x20U),   /*!< output target peripheral TIMER4_ITI */
    TRIGSEL_OUTPUT_TIMER7_ITI        = ((uint8_t)0x24U),   /*!< output target peripheral TIMER7_ITI */
    TRIGSEL_OUTPUT_TIMER15_ITI       = ((uint8_t)0x2CU),   /*!< output target peripheral TIMER15_ITI */
    TRIGSEL_OUTPUT_TIMER16_ITI       = ((uint8_t)0x30U),   /*!< output target peripheral TIMER16_ITI */
    TRIGSEL_OUTPUT_DAC_OUT_EXTRG     = ((uint8_t)0x34U),   /*!< output target peripheral DAC_OUT_EXTRG */
    TRIGSEL_OUTPUT_ADC0_ROUTRG       = ((uint8_t)0x38U),   /*!< output target peripheral ADC0_ROUTRG */
    TRIGSEL_OUTPUT_ADC0_INSTRG       = ((uint8_t)0x3CU),   /*!< output target peripheral ADC0_INSTRG */
    TRIGSEL_OUTPUT_ADC1_ROUTRG       = ((uint8_t)0x40U),   /*!< output target peripheral ADC1_ROUTRG */
    TRIGSEL_OUTPUT_ADC1_INSTRG       = ((uint8_t)0x44U),   /*!< output target peripheral ADC1_INSTRG */
    TRIGSEL_OUTPUT_ADC2_ROUTRG       = ((uint8_t)0x48U),   /*!< output target peripheral ADC2_ROUTRG */
    TRIGSEL_OUTPUT_ADC2_INSTRG       = ((uint8_t)0x4CU),   /*!< output target peripheral ADC2_INSTRG */
    TRIGSEL_OUTPUT_TIMER0_BRKIN      = ((uint8_t)0x50U),   /*!< output target peripheral TIMER0_BRKIN */
    TRIGSEL_OUTPUT_TIMER0_CH0BRKIN   = ((uint8_t)0x54U),   /*!< output target peripheral TIMER0_CH0BRKIN */
    TRIGSEL_OUTPUT_TIMER0_CH1BRKIN   = ((uint8_t)0x55U),   /*!< output target peripheral TIMER0_CH1BRKIN */
    TRIGSEL_OUTPUT_TIMER0_CH2BRKIN   = ((uint8_t)0x56U),   /*!< output target peripheral TIMER0_CH2BRKIN */
    TRIGSEL_OUTPUT_TIMER7_BRKIN      = ((uint8_t)0x58U),   /*!< output target peripheral TIMER7_BRKIN */
    TRIGSEL_OUTPUT_TIMER7_CH0BRKIN   = ((uint8_t)0x5CU),   /*!< output target peripheral TIMER7_CH0BRKIN */
    TRIGSEL_OUTPUT_TIMER7_CH1BRKIN   = ((uint8_t)0x5DU),   /*!< output target peripheral TIMER7_CH1BRKIN */
    TRIGSEL_OUTPUT_TIMER7_CH2BRKIN   = ((uint8_t)0x5EU),   /*!< output target peripheral TIMER7_CH2BRKIN */
    TRIGSEL_OUTPUT_TIMER15_BRKIN     = ((uint8_t)0x60U),   /*!< output target peripheral TIMER15_BRKIN */
    TRIGSEL_OUTPUT_TIMER16_BRKIN     = ((uint8_t)0x64U),   /*!< output target peripheral TIMER16_BRKIN */
}trigsel_periph_enum;

/* function declarations */
/* deinitialize TRIGSEL */
void trigsel_deinit(void);
/* set the trigger input signal for target peripheral */
void trigsel_init(trigsel_periph_enum target_periph, trigsel_source_enum trigger_source);
 /* get the trigger input signal for target peripheral */
trigsel_source_enum trigsel_trigger_source_get(trigsel_periph_enum target_periph);
/* lock the trigger register */
void trigsel_register_lock_set(trigsel_periph_enum target_periph);
/* get the trigger register lock status */
FlagStatus trigsel_register_lock_get(trigsel_periph_enum target_periph);
#endif /* GD32F50X_TRIGSEL_H */
