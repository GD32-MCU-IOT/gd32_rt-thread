/*!
    \file    gd32g5x3_cmp.h
    \brief   definitions for the CMP

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

#ifndef GD32G5X3_CMP_H
#define GD32G5X3_CMP_H

#include "gd32g5x3.h"

/* CMP definitions */
#define CMP                                      CMP_BASE                                           /*!< CMP base address */
                                                                                                   
/* registers definitions */                                                                        
#define CMP_STAT                                 REG32((CMP) + 0x00000000U)                         /*!< CMP status */
#define CMP_IFC                                  REG32((CMP) + 0x00000004U)                         /*!< CMP interrupt flag clear */
#define CMP_CS(CMPx)                             REG32((CMP) + 0x00000008U + (CMPx) * 0x00000004U)  /*!< CMPx control and status register */

/* bits definitions */
/* CMP_STAT */
#define CMP_STAT_CMP0O                           BIT(0)                         /*!< CMP0 output state */
#define CMP_STAT_CMP1O                           BIT(1)                         /*!< CMP1 output state */
#define CMP_STAT_CMP2O                           BIT(2)                         /*!< CMP2 output state */
#define CMP_STAT_CMP3O                           BIT(3)                         /*!< CMP3 output state */
#define CMP_STAT_CMP4O                           BIT(4)                         /*!< CMP4 output state */
#define CMP_STAT_CMP5O                           BIT(5)                         /*!< CMP5 output state */
#define CMP_STAT_CMP6O                           BIT(6)                         /*!< CMP6 output state */
#define CMP_STAT_CMP7O                           BIT(7)                         /*!< CMP7 output state */
#define CMP_STAT_CMP0IF                          BIT(16)                        /*!< CMP0 interrupt flag */
#define CMP_STAT_CMP1IF                          BIT(17)                        /*!< CMP1 interrupt flag */
#define CMP_STAT_CMP2IF                          BIT(18)                        /*!< CMP2 interrupt flag */
#define CMP_STAT_CMP3IF                          BIT(19)                        /*!< CMP3 interrupt flag */
#define CMP_STAT_CMP4IF                          BIT(20)                        /*!< CMP4 interrupt flag */
#define CMP_STAT_CMP5IF                          BIT(21)                        /*!< CMP5 interrupt flag */
#define CMP_STAT_CMP6IF                          BIT(22)                        /*!< CMP6 interrupt flag */
#define CMP_STAT_CMP7IF                          BIT(23)                        /*!< CMP7 interrupt flag */

/* CMP_IFC */
#define CMP_IFC_CMP0IC                           BIT(16)                        /*!< CMP0 interrupt flag clear */
#define CMP_IFC_CMP1IC                           BIT(17)                        /*!< CMP1 interrupt flag clear */
#define CMP_IFC_CMP2IC                           BIT(18)                        /*!< CMP2 interrupt flag clear */
#define CMP_IFC_CMP3IC                           BIT(19)                        /*!< CMP3 interrupt flag clear */
#define CMP_IFC_CMP4IC                           BIT(20)                        /*!< CMP4 interrupt flag clear */
#define CMP_IFC_CMP5IC                           BIT(21)                        /*!< CMP5 interrupt flag clear */
#define CMP_IFC_CMP6IC                           BIT(22)                        /*!< CMP6 interrupt flag clear */
#define CMP_IFC_CMP7IC                           BIT(23)                        /*!< CMP7 interrupt flag clear */

/* CMP_CSx */
#define CMP_CS_CMPXEN                            BIT(0)                         /*!< CMPx enable */
#define CMP_CS_CMPXBEN                           BIT(1)                         /*!< CMPx bridge enable */
#define CMP_CS_CMPXSEN                           BIT(2)                         /*!< CMPx scaler enable */
#define CMP_CS_CMPXPL                            BIT(3)                         /*!< polarity of CMPx output */
#define CMP_CS_CMPXINTEN                         BIT(6)                         /*!< CMPx interrupt enable */
#define CMP_CS_CMPXRSTMD                         BIT(7)                         /*!< CMPx reset mode */
#define CMP_CS_CMPXHST                           BITS(8,10)                     /*!< CMPx hysteresis */
#define CMP_CS_CMPXMSEL                          BITS(16,18)                    /*!< CMPx_IM input selection */
#define CMP_CS_CMPXPSEL                          BIT(20)                        /*!< CMPx_IP input selection */
#define CMP_CS_CMPXBLK                           BITS(24,27)                    /*!< CMPx output blanking source */
#define CMP_CS_CMPXLK                            BIT(31)                        /*!< CMPx lock */

/* consts definitions */
/* CMP units */
typedef enum
{
    CMP0 = 0x00U,                                                               /*!< Comparator 0 */
    CMP1,                                                                       /*!< Comparator 1 */
    CMP2,                                                                       /*!< Comparator 2 */
    CMP3,                                                                       /*!< Comparator 3 */
    CMP4,                                                                       /*!< Comparator 4 */
    CMP5,                                                                       /*!< Comparator 5 */
    CMP6,                                                                       /*!< Comparator 6 */
    CMP7,                                                                       /*!< Comparator 7 */
}cmp_enum;

/* CMP hysteresis */
#define CS_CMPXHST(regval)                       (BITS(8,10) & ((uint32_t)(regval) << 8U))
#define CMP_HYSTERESIS_NO                        CS_CMPXHST(0)                  /*!< CMP output no hysteresis */
#define CMP_HYSTERESIS_10MV                      CS_CMPXHST(1)                  /*!< CMP output 10mv hysteresis */
#define CMP_HYSTERESIS_20MV                      CS_CMPXHST(2)                  /*!< CMP output 20mv hysteresis */
#define CMP_HYSTERESIS_30MV                      CS_CMPXHST(3)                  /*!< CMP output 30mv hysteresis */
#define CMP_HYSTERESIS_40MV                      CS_CMPXHST(4)                  /*!< CMP output 40mv hysteresis */
#define CMP_HYSTERESIS_50MV                      CS_CMPXHST(5)                  /*!< CMP output 50mv hysteresis */
#define CMP_HYSTERESIS_60MV                      CS_CMPXHST(6)                  /*!< CMP output 60mv hysteresis */
#define CMP_HYSTERESIS_70MV                      CS_CMPXHST(7)                  /*!< CMP output 70mv hysteresis */

/* CMP inverting input */
#define CS_CMPXMSEL(regval)                      (BITS(16,18) & ((uint32_t)(regval) << 16U))
#define CMPX_INVERTING_INPUT_1_4VREFINT          CS_CMPXMSEL(0)                /*!< CMP inverting input 1/4 Vrefint */
#define CMPX_INVERTING_INPUT_1_2VREFINT          CS_CMPXMSEL(1)                /*!< CMP inverting input 1/2 Vrefint */
#define CMPX_INVERTING_INPUT_3_4VREFINT          CS_CMPXMSEL(2)                /*!< CMP inverting input 3/4 Vrefint */
#define CMPX_INVERTING_INPUT_VREFINT             CS_CMPXMSEL(3)                /*!< CMP inverting input Vrefint */
#define CMP0_INVERTING_INPUT_DAC2_OUT0           CS_CMPXMSEL(4)                /*!< DAC2_OUT0 input for CMP0 */
#define CMP0_INVERTING_INPUT_DAC0_OUT0           CS_CMPXMSEL(5)                /*!< DAC0_OUT0 input for CMP0 */
#define CMP0_INVERTING_INPUT_PA4                 CS_CMPXMSEL(6)                /*!< PA4 input for CMP0 */
#define CMP0_INVERTING_INPUT_PA0                 CS_CMPXMSEL(7)                /*!< PA0 input for CMP0 */
#define CMP1_INVERTING_INPUT_DAC2_OUT1           CS_CMPXMSEL(4)                /*!< DAC2_OUT1 input for CMP1 */
#define CMP1_INVERTING_INPUT_DAC0_OUT1           CS_CMPXMSEL(5)                /*!< DAC0_OUT1 input for CMP1 */
#define CMP1_INVERTING_INPUT_PA5                 CS_CMPXMSEL(6)                /*!< PA5 input for CMP1 */
#define CMP1_INVERTING_INPUT_PA2                 CS_CMPXMSEL(7)                /*!< PA2 input for CMP1 */
#define CMP2_INVERTING_INPUT_DAC2_OUT0           CS_CMPXMSEL(4)                /*!< DAC2_OUT0 input for CMP2 */
#define CMP2_INVERTING_INPUT_DAC0_OUT0           CS_CMPXMSEL(5)                /*!< DAC0_OUT0 input for CMP2 */
#define CMP2_INVERTING_INPUT_PF1                 CS_CMPXMSEL(6)                /*!< PF1 input for CMP2 */
#define CMP2_INVERTING_INPUT_PC0                 CS_CMPXMSEL(7)                /*!< PC0 input for CMP2 */
#define CMP3_INVERTING_INPUT_DAC2_OUT1           CS_CMPXMSEL(4)                /*!< DAC2_OUT1 input for CMP3 */
#define CMP3_INVERTING_INPUT_DAC0_OUT0           CS_CMPXMSEL(5)                /*!< DAC0_OUT0 input for CMP3 */
#define CMP3_INVERTING_INPUT_PE8                 CS_CMPXMSEL(6)                /*!< PE8 input for CMP3 */
#define CMP3_INVERTING_INPUT_PB2                 CS_CMPXMSEL(7)                /*!< PB2 input for CMP3 */
#define CMP4_INVERTING_INPUT_DAC3_OUT0           CS_CMPXMSEL(4)                /*!< DAC3_OUT0 input for CMP4 */
#define CMP4_INVERTING_INPUT_DAC0_OUT1           CS_CMPXMSEL(5)                /*!< DAC0_OUT1 input for CMP4 */
#define CMP4_INVERTING_INPUT_PB10                CS_CMPXMSEL(6)                /*!< PB10 input for CMP4 */
#define CMP4_INVERTING_INPUT_PD13                CS_CMPXMSEL(7)                /*!< PD13 input for CMP4 */
#define CMP5_INVERTING_INPUT_DAC3_OUT1           CS_CMPXMSEL(4)                /*!< DAC3_OUT1 input for CMP5 */
#define CMP5_INVERTING_INPUT_DAC1_OUT0           CS_CMPXMSEL(5)                /*!< DAC1_OUT0 input for CMP5 */
#define CMP5_INVERTING_INPUT_PD10                CS_CMPXMSEL(6)                /*!< PD10 input for CMP5 */
#define CMP5_INVERTING_INPUT_PB15                CS_CMPXMSEL(7)                /*!< PB15 input for CMP5 */
#define CMP6_INVERTING_INPUT_DAC3_OUT0           CS_CMPXMSEL(4)                /*!< DAC3_OUT0 input for CMP6 */
#define CMP6_INVERTING_INPUT_DAC1_OUT0           CS_CMPXMSEL(5)                /*!< DAC1_OUT0 input for CMP6 */
#define CMP6_INVERTING_INPUT_PD15                CS_CMPXMSEL(6)                /*!< PD15 input for CMP6 */
#define CMP6_INVERTING_INPUT_PB12                CS_CMPXMSEL(7)                /*!< PB12 input for CMP6 */
#define CMP7_INVERTING_INPUT_DAC3_OUT1           CS_CMPXMSEL(4)                /*!< DAC3_OUT1 input for CMP7 */
#define CMP7_INVERTING_INPUT_DAC1_OUT1           CS_CMPXMSEL(5)                /*!< DAC1_OUT1 input for CMP7 */
#define CMP7_INVERTING_INPUT_PD8                 CS_CMPXMSEL(6)                /*!< PD8 input for CMP7 */
#define CMP7_INVERTING_INPUT_PD9                 CS_CMPXMSEL(7)                /*!< PD9 input for CMP7 */

/* CMP noninverting input*/
#define CS_CMPXPSEL(regval)                      (BIT(20) & ((uint32_t)(regval) << 20U))
#define CMP0_NONINVERTING_INPUT_PA1              CS_CMPXPSEL(0)                /*!< CMP noninverting input PA1 for CMP0 */
#define CMP0_NONINVERTING_INPUT_PB1              CS_CMPXPSEL(1)                /*!< CMP noninverting input PB1 for CMP0 */
#define CMP1_NONINVERTING_INPUT_PA7              CS_CMPXPSEL(0)                /*!< CMP noninverting input PA7 for CMP1 */
#define CMP1_NONINVERTING_INPUT_PA3              CS_CMPXPSEL(1)                /*!< CMP noninverting input PA3 for CMP1 */
#define CMP2_NONINVERTING_INPUT_PA0              CS_CMPXPSEL(0)                /*!< CMP noninverting input PA0 for CMP2 */
#define CMP2_NONINVERTING_INPUT_PC1              CS_CMPXPSEL(1)                /*!< CMP noninverting input PC1 for CMP2 */
#define CMP3_NONINVERTING_INPUT_PB0              CS_CMPXPSEL(0)                /*!< CMP noninverting input PB0 for CMP3 */
#define CMP3_NONINVERTING_INPUT_PE7              CS_CMPXPSEL(1)                /*!< CMP noninverting input PE7 for CMP3 */
#define CMP4_NONINVERTING_INPUT_PB13             CS_CMPXPSEL(0)                /*!< CMP noninverting input PB13 for CMP4 */
#define CMP4_NONINVERTING_INPUT_PD12             CS_CMPXPSEL(1)                /*!< CMP noninverting input PD12 for CMP4 */
#define CMP5_NONINVERTING_INPUT_PB11             CS_CMPXPSEL(0)                /*!< CMP noninverting input PB11 for CMP5 */
#define CMP5_NONINVERTING_INPUT_PD11             CS_CMPXPSEL(1)                /*!< CMP noninverting input PD11 for CMP5 */
#define CMP6_NONINVERTING_INPUT_PB14             CS_CMPXPSEL(0)                /*!< CMP noninverting input PB14 for CMP6 */
#define CMP6_NONINVERTING_INPUT_PD14             CS_CMPXPSEL(1)                /*!< CMP noninverting input PD14 for CMP6 */
#define CMP7_NONINVERTING_INPUT_PC2              CS_CMPXPSEL(0)                /*!< CMP noninverting input PC2 for CMP7 */
#define CMP7_NONINVERTING_INPUT_PE9              CS_CMPXPSEL(1)                /*!< CMP noninverting input PE9 for CMP7 */

/* CMP blanking source */
#define CS_CMPXBLK(regval)                       (BITS(24,27) & ((uint32_t)(regval) << 24U))
#define CMPX_BLANKING_NONE                       CS_CMPXBLK(0)                 /*!< CMP no blanking source */
#define CMP0_BLANKING_TIMER0_OC2                 CS_CMPXBLK(1)                 /*!< CMP TIMER0_CH2 output compare signal selected as blanking source for CMP0 */
#define CMP0_BLANKING_TIMER1_OC2                 CS_CMPXBLK(2)                 /*!< CMP TIMER1_CH2 output compare signal selected as blanking source for CMP0 */
#define CMP0_BLANKING_TIMER2_OC2                 CS_CMPXBLK(3)                 /*!< CMP TIMER2_CH2 output compare signal selected as blanking source for CMP0 */
#define CMP0_BLANKING_TIMER7_OC2                 CS_CMPXBLK(4)                 /*!< CMP TIMER7_CH2 output compare signal selected as blanking source for CMP0 */
#define CMP0_BLANKING_TIMER19_OC2                CS_CMPXBLK(5)                 /*!< CMP TIMER19_CH2 output compare signal selected as blanking source for CMP0 */
#define CMP0_BLANKING_TIMER14_OC0                CS_CMPXBLK(6)                 /*!< CMP TIMER14_CH0 output compare signal selected as blanking source for CMP0 */
#define CMP0_BLANKING_TIMER3_OC2                 CS_CMPXBLK(7)                 /*!< CMP TIMER3_CH2 output compare signal selected as blanking source for CMP0 */
#define CMP1_BLANKING_TIMER0_OC2                 CS_CMPXBLK(1)                 /*!< CMP TIMER0_CH2 output compare signal selected as blanking source for CMP1 */
#define CMP1_BLANKING_TIMER1_OC2                 CS_CMPXBLK(2)                 /*!< CMP TIMER1_CH2 output compare signal selected as blanking source for CMP1 */
#define CMP1_BLANKING_TIMER2_OC2                 CS_CMPXBLK(3)                 /*!< CMP TIMER2_CH2 output compare signal selected as blanking source for CMP1 */
#define CMP1_BLANKING_TIMER7_OC2                 CS_CMPXBLK(4)                 /*!< CMP TIMER7_CH2 output compare signal selected as blanking source for CMP1 */
#define CMP1_BLANKING_TIMER19_OC2                CS_CMPXBLK(5)                 /*!< CMP TIMER19_CH2 output compare signal selected as blanking source for CMP1 */
#define CMP1_BLANKING_TIMER14_OC0                CS_CMPXBLK(6)                 /*!< CMP TIMER14_CH0 output compare signal selected as blanking source for CMP1 */
#define CMP1_BLANKING_TIMER3_OC2                 CS_CMPXBLK(7)                 /*!< CMP TIMER3_CH2 output compare signal selected as blanking source for CMP1 */
#define CMP2_BLANKING_TIMER0_OC2                 CS_CMPXBLK(1)                 /*!< CMP TIMER0_CH2 output compare signal selected as blanking source for CMP2 */
#define CMP2_BLANKING_TIMER2_OC2                 CS_CMPXBLK(2)                 /*!< CMP TIMER2_CH2 output compare signal selected as blanking source for CMP2 */
#define CMP2_BLANKING_TIMER1_OC3                 CS_CMPXBLK(3)                 /*!< CMP TIMER1_CH3 output compare signal selected as blanking source for CMP2 */
#define CMP2_BLANKING_TIMER7_OC2                 CS_CMPXBLK(4)                 /*!< CMP TIMER7_CH2 output compare signal selected as blanking source for CMP2 */
#define CMP2_BLANKING_TIMER19_OC2                CS_CMPXBLK(5)                 /*!< CMP TIMER19_CH2 output compare signal selected as blanking source for CMP2 */
#define CMP2_BLANKING_TIMER14_OC0                CS_CMPXBLK(6)                 /*!< CMP TIMER14_CH0 output compare signal selected as blanking source for CMP2 */
#define CMP2_BLANKING_TIMER3_OC2                 CS_CMPXBLK(7)                 /*!< CMP TIMER3_CH2 output compare signal selected as blanking source for CMP2 */
#define CMP3_BLANKING_TIMER2_OC3                 CS_CMPXBLK(1)                 /*!< CMP TIMER2_CH3 output compare signal selected as blanking source for CMP3 */
#define CMP3_BLANKING_TIMER7_OC2                 CS_CMPXBLK(2)                 /*!< CMP TIMER7_CH2 output compare signal selected as blanking source for CMP3 */
#define CMP3_BLANKING_TIMER14_OC1                CS_CMPXBLK(3)                 /*!< CMP TIMER14_CH1 output compare signal selected as blanking source for CMP3 */
#define CMP3_BLANKING_TIMER0_OC2                 CS_CMPXBLK(4)                 /*!< CMP TIMER0_CH2 output compare signal selected as blanking source for CMP3 */
#define CMP3_BLANKING_TIMER19_OC2                CS_CMPXBLK(5)                 /*!< CMP TIMER19_CH2 output compare signal selected as blanking source for CMP3 */
#define CMP3_BLANKING_TIMER14_OC0                CS_CMPXBLK(6)                 /*!< CMP TIMER14_CH0 output compare signal selected as blanking source for CMP3 */
#define CMP3_BLANKING_TIMER3_OC2                 CS_CMPXBLK(7)                 /*!< CMP TIMER3_CH2 output compare signal selected as blanking source for CMP3 */
#define CMP4_BLANKING_TIMER1_OC2                 CS_CMPXBLK(1)                 /*!< CMP TIMER1_CH2 output compare signal selected as blanking source for CMP4 */
#define CMP4_BLANKING_TIMER7_OC2                 CS_CMPXBLK(2)                 /*!< CMP TIMER7_CH2 output compare signal selected as blanking source for CMP4 */
#define CMP4_BLANKING_TIMER2_OC2                 CS_CMPXBLK(3)                 /*!< CMP TIMER2_CH2 output compare signal selected as blanking source for CMP4 */
#define CMP4_BLANKING_TIMER0_OC2                 CS_CMPXBLK(4)                 /*!< CMP TIMER0_CH2 output compare signal selected as blanking source for CMP4 */
#define CMP4_BLANKING_TIMER19_OC2                CS_CMPXBLK(5)                 /*!< CMP TIMER19_CH2 output compare signal selected as blanking source for CMP4 */
#define CMP4_BLANKING_TIMER14_OC0                CS_CMPXBLK(6)                 /*!< CMP TIMER14_CH0 output compare signal selected as blanking source for CMP4 */
#define CMP4_BLANKING_TIMER3_OC2                 CS_CMPXBLK(7)                 /*!< CMP TIMER3_CH2 output compare signal selected as blanking source for CMP4 */
#define CMP5_BLANKING_TIMER7_OC2                 CS_CMPXBLK(1)                 /*!< CMP TIMER7_CH2 output compare signal selected as blanking source for CMP5 */
#define CMP5_BLANKING_TIMER1_OC3                 CS_CMPXBLK(2)                 /*!< CMP TIMER1_CH3 output compare signal selected as blanking source for CMP5 */
#define CMP5_BLANKING_TIMER14_OC1                CS_CMPXBLK(3)                 /*!< CMP TIMER14_CH1 output compare signal selected as blanking source for CMP5 */
#define CMP5_BLANKING_TIMER0_OC2                 CS_CMPXBLK(4)                 /*!< CMP TIMER0_CH2 output compare signal selected as blanking source for CMP5 */
#define CMP5_BLANKING_TIMER19_OC2                CS_CMPXBLK(5)                 /*!< CMP TIMER19_CH2 output compare signal selected as blanking source for CMP5 */
#define CMP5_BLANKING_TIMER14_OC0                CS_CMPXBLK(6)                 /*!< CMP TIMER14_CH0 output compare signal selected as blanking source for CMP5 */
#define CMP5_BLANKING_TIMER3_OC2                 CS_CMPXBLK(7)                 /*!< CMP TIMER3_CH2 output compare signal selected as blanking source for CMP5 */
#define CMP6_BLANKING_TIMER0_OC2                 CS_CMPXBLK(1)                 /*!< CMP TIMER0_CH2 output compare signal selected as blanking source for CMP6 */
#define CMP6_BLANKING_TIMER7_OC2                 CS_CMPXBLK(2)                 /*!< CMP TIMER7_CH2 output compare signal selected as blanking source for CMP6 */
#define CMP6_BLANKING_TIMER2_OC2                 CS_CMPXBLK(3)                 /*!< CMP TIMER2_CH2 output compare signal selected as blanking source for CMP6 */
#define CMP6_BLANKING_TIMER14_OC1                CS_CMPXBLK(4)                 /*!< CMP TIMER14_CH1 output compare signal selected as blanking source for CMP6 */
#define CMP6_BLANKING_TIMER19_OC2                CS_CMPXBLK(5)                 /*!< CMP TIMER19_CH2 output compare signal selected as blanking source for CMP6 */
#define CMP6_BLANKING_TIMER14_OC0                CS_CMPXBLK(6)                 /*!< CMP TIMER14_CH0 output compare signal selected as blanking source for CMP6 */
#define CMP6_BLANKING_TIMER3_OC2                 CS_CMPXBLK(7)                 /*!< CMP TIMER3_CH2 output compare signal selected as blanking source for CMP6 */
#define CMP7_BLANKING_TIMER1_OC2                 CS_CMPXBLK(1)                 /*!< CMP TIMER1_CH2 output compare signal selected as blanking source for CMP7 */
#define CMP7_BLANKING_TIMER7_OC2                 CS_CMPXBLK(2)                 /*!< CMP TIMER7_CH2 output compare signal selected as blanking source for CMP7 */
#define CMP7_BLANKING_TIMER2_OC2                 CS_CMPXBLK(3)                 /*!< CMP TIMER2_CH2 output compare signal selected as blanking source for CMP7 */
#define CMP7_BLANKING_TIMER0_OC2                 CS_CMPXBLK(4)                 /*!< CMP TIMER0_CH2 output compare signal selected as blanking source for CMP7 */
#define CMP7_BLANKING_TIMER19_OC2                CS_CMPXBLK(5)                 /*!< CMP TIMER19_CH2 output compare signal selected as blanking source for CMP7 */
#define CMP7_BLANKING_TIMER14_OC0                CS_CMPXBLK(6)                 /*!< CMP TIMER14_CH0 output compare signal selected as blanking source for CMP7 */
#define CMP7_BLANKING_TIMER3_OC2                 CS_CMPXBLK(7)                 /*!< CMP TIMER3_CH2 output compare signal selected as blanking source for CMP7 */

/* output polarity of comparator */
#define CMP_OUTPUT_POLARITY_INVERTED             ((uint32_t)0x00000001)         /*!< output is inverted */
#define CMP_OUTPUT_POLARITY_NONINVERTED          ((uint32_t)0x00000000)         /*!< output is not inverted */
                                                 
/* comparator output level */
#define CMP_OUTPUTLEVEL_HIGH                     ((uint32_t)0x00000001U)        /*!< comparator output high */
#define CMP_OUTPUTLEVEL_LOW                      ((uint32_t)0x00000000U)        /*!< comparator output low */

/* CMP flags */
#define CMP_FLAG_CMP0F                           CMP_STAT_CMP0IF                /*!< CMP0 interrupt flag */
#define CMP_FLAG_CMP1F                           CMP_STAT_CMP1IF                /*!< CMP1 interrupt flag */
#define CMP_FLAG_CMP2F                           CMP_STAT_CMP2IF                /*!< CMP2 interrupt flag */
#define CMP_FLAG_CMP3F                           CMP_STAT_CMP3IF                /*!< CMP3 interrupt flag */
#define CMP_FLAG_CMP4F                           CMP_STAT_CMP4IF                /*!< CMP4 interrupt flag */
#define CMP_FLAG_CMP5F                           CMP_STAT_CMP5IF                /*!< CMP5 interrupt flag */
#define CMP_FLAG_CMP6F                           CMP_STAT_CMP6IF                /*!< CMP6 interrupt flag */
#define CMP_FLAG_CMP7F                           CMP_STAT_CMP7IF                /*!< CMP7 interrupt flag */

/* CMP flags clear */
#define CMP_FLAG_CMP0F_CLR                       CMP_IFC_CMP0IC                 /*!< CMP0 flag clear */
#define CMP_FLAG_CMP1F_CLR                       CMP_IFC_CMP1IC                 /*!< CMP1 flag clear */
#define CMP_FLAG_CMP2F_CLR                       CMP_IFC_CMP2IC                 /*!< CMP2 flag clear */
#define CMP_FLAG_CMP3F_CLR                       CMP_IFC_CMP3IC                 /*!< CMP3 flag clear */
#define CMP_FLAG_CMP4F_CLR                       CMP_IFC_CMP4IC                 /*!< CMP4 flag clear */
#define CMP_FLAG_CMP5F_CLR                       CMP_IFC_CMP5IC                 /*!< CMP5 flag clear */
#define CMP_FLAG_CMP6F_CLR                       CMP_IFC_CMP6IC                 /*!< CMP6 flag clear */
#define CMP_FLAG_CMP7F_CLR                       CMP_IFC_CMP7IC                 /*!< CMP7 flag clear */

/* CMP interrupt flags */
#define CMP_INT_FLAG_CMP0F                       CMP_STAT_CMP0IF                /*!< CMP0 interrupt flag */
#define CMP_INT_FLAG_CMP1F                       CMP_STAT_CMP1IF                /*!< CMP1 interrupt flag */
#define CMP_INT_FLAG_CMP2F                       CMP_STAT_CMP2IF                /*!< CMP2 interrupt flag */
#define CMP_INT_FLAG_CMP3F                       CMP_STAT_CMP3IF                /*!< CMP3 interrupt flag */
#define CMP_INT_FLAG_CMP4F                       CMP_STAT_CMP4IF                /*!< CMP4 interrupt flag */
#define CMP_INT_FLAG_CMP5F                       CMP_STAT_CMP5IF                /*!< CMP5 interrupt flag */
#define CMP_INT_FLAG_CMP6F                       CMP_STAT_CMP6IF                /*!< CMP6 interrupt flag */
#define CMP_INT_FLAG_CMP7F                       CMP_STAT_CMP7IF                /*!< CMP7 interrupt flag */

/* CMP interrupt flags clear */
#define CMP_INT_FLAG_CMP0F_CLR                   CMP_IFC_CMP0IC                 /*!< CMP0 interrupt flag clear */
#define CMP_INT_FLAG_CMP1F_CLR                   CMP_IFC_CMP1IC                 /*!< CMP1 interrupt flag clear */
#define CMP_INT_FLAG_CMP2F_CLR                   CMP_IFC_CMP2IC                 /*!< CMP2 interrupt flag clear */
#define CMP_INT_FLAG_CMP3F_CLR                   CMP_IFC_CMP3IC                 /*!< CMP3 interrupt flag clear */
#define CMP_INT_FLAG_CMP4F_CLR                   CMP_IFC_CMP4IC                 /*!< CMP4 interrupt flag clear */
#define CMP_INT_FLAG_CMP5F_CLR                   CMP_IFC_CMP5IC                 /*!< CMP5 interrupt flag clear */
#define CMP_INT_FLAG_CMP6F_CLR                   CMP_IFC_CMP6IC                 /*!< CMP6 interrupt flag clear */
#define CMP_INT_FLAG_CMP7F_CLR                   CMP_IFC_CMP7IC                 /*!< CMP7 interrupt flag clear */

/* function declarations */
/* initialization functions */
/* CMP deinit */
void cmp_deinit(void);
/* CMP mode init */
void cmp_mode_init(cmp_enum cmp_periph, uint32_t inverting_input, uint32_t output_hysteresis);
/* CMP noninverting input select */
void cmp_noninverting_input_select(cmp_enum cmp_periph, uint32_t noninverting_input);
/* CMP output init */
void cmp_output_init(cmp_enum cmp_periph, uint32_t output_polarity);
/* CMP output blanking function init */
void cmp_blanking_init(cmp_enum cmp_periph,uint32_t blanking_source_selection);

/* enable functions */
/* enable CMP */
void cmp_enable(cmp_enum cmp_periph);
/* disable CMP */
void cmp_disable(cmp_enum cmp_periph);
/* lock the CMP */
void cmp_lock_enable(cmp_enum cmp_periph);
/* enable the voltage scaler */
void cmp_voltage_scaler_enable(cmp_enum cmp_periph);
/* disable the voltage scaler */
void cmp_voltage_scaler_disable(cmp_enum cmp_periph);
/* enable the scaler bridge */
void cmp_scaler_bridge_enable(cmp_enum cmp_periph);
/* disable the scaler bridge */
void cmp_scaler_bridge_disable(cmp_enum cmp_periph);
/* enable comparator reset persisit mode */
void cmp_reset_persist_mode_enable(cmp_enum cmp_periph);
/* disable comparator reset persisit mode */
void cmp_reset_persist_mode_disable(cmp_enum cmp_periph);

/* get state related functions */
/* get output level */
uint32_t cmp_output_level_get(cmp_enum cmp_periph);

/* flag and interrupt functions */
/* get CMP flag */
FlagStatus cmp_flag_get(uint32_t flag);
/* clear CMP flag */
void cmp_flag_clear(uint32_t flag);
/* enable CMP interrupt */
void cmp_interrupt_enable(cmp_enum cmp_periph);
/* disable CMP interrupt */
void cmp_interrupt_disable(cmp_enum cmp_periph);
/* get CMP interrupt flag */
FlagStatus cmp_interrupt_flag_get(cmp_enum cmp_periph, uint32_t flag);
/* clear CMP interrupt flag */
void cmp_interrupt_flag_clear(uint32_t flag);

#endif /* GD32G5X3_CMP_H */
