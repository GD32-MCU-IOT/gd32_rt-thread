/*!
    \file    gd32m53x_cmp.h
    \brief   CMP driver

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

#ifndef GD32M53X_CMP_H
#define GD32M53X_CMP_H

#include "gd32m53x.h"

/* CMP definitions */
#define CMP                                      CMP_BASE                        /*!< CMP base address */

/* registers definitions */
#define CMP_STAT                                 REG32((CMP) + 0X00000000U)      /*!< CMP status register */
#define CMP_IFC                                  REG32((CMP) + 0X00000004U)      /*!< CMP interrupt flag clear register */
#define CMP0_CS                                  REG32((CMP) + 0x0000000CU)      /*!< CMP0 control and status register */
#define CMP1_CS                                  REG32((CMP) + 0x00000010U)      /*!< CMP1 control and status register */
#define CMP2_CS                                  REG32((CMP) + 0x00000014U)      /*!< CMP2 control and status register */
#define CMP3_CS                                  REG32((CMP) + 0x00000018U)      /*!< CMP3 control and status register */

/* bits definitions */
/* CMP_STAT */
#define CMP_STAT_CMP0O                           BIT(0)                          /*!< CMP0 output */
#define CMP_STAT_CMP1O                           BIT(1)                          /*!< CMP1 output */
#define CMP_STAT_CMP2O                           BIT(2)                          /*!< CMP2 output */
#define CMP_STAT_CMP3O                           BIT(3)                          /*!< CMP3 output */
#define CMP_STAT_CMP0IF                          BIT(16)                         /*!< CMP0 interrupt flag */
#define CMP_STAT_CMP1IF                          BIT(17)                         /*!< CMP1 interrupt flag */
#define CMP_STAT_CMP2IF                          BIT(18)                         /*!< CMP2 interrupt flag */
#define CMP_STAT_CMP3IF                          BIT(19)                         /*!< CMP3 interrupt flag */

/* CMP_IFC */
#define CMP_IFC_CMP0IC                           BIT(16)                         /*!< CMP0 interrupt flag clear */
#define CMP_IFC_CMP1IC                           BIT(17)                         /*!< CMP1 interrupt flag clear */
#define CMP_IFC_CMP2IC                           BIT(18)                         /*!< CMP2 interrupt flag clear */
#define CMP_IFC_CMP3IC                           BIT(19)                         /*!< CMP3 interrupt flag clear */

/* CMPx_CS */
#define CMP_CS_CMPXEN                            BIT(0)                          /*!< CMPx enable */
#define CMP_CS_CMPXPL                            BIT(3)                          /*!< polarity of CMPx output */
#define CMP_CS_CMPXPOE                           BIT(4)                          /*!< CMPx pin output enable */
#define CMP_CS_CMPXOE                            BIT(5)                          /*!< CMPx output enable */
#define CMP_CS_CMPXINTEN                         BITS(6,7)                       /*!< CMPx interrupt request enable */
#define CMP_CS_CMPXHST                           BITS(8,9)                       /*!< CMPx hysteresis */
#define CMP_CS_CMPXDFSCDIV                       BITS(10,11)                     /*!< CMPx digital filter sampling clock division */
#define CMP_CS_CMPXDFSNUM                        BIT(14)                         /*!< CMPx digital filter sampling number */
#define CMP_CS_CMPXMISEL                         BITS(16,18)                     /*!< CMPx_IM input selection */
#define CMP_CS_CMPXPSEL                          BITS(20,22)                     /*!< CMPx_IP input selection */
#define CMP_CS_CMPXLK                            BIT(31)                         /*!< CMPx lock */


/* constants definitions */
/* CMP units */
typedef enum {
    CMP0 = 0,                                                                    /*!< comparator 0 */
    CMP1,                                                                        /*!< comparator 1 */
    CMP2,                                                                        /*!< comparator 2 */
    CMP3                                                                         /*!< comparator 3 */
} cmp_enum;

/* CMP hysteresis */
#define CS_CMPXHST(regval)                      (BITS(8,9) & ((uint32_t)(regval) << 8))
#define CMP_HYSTERESIS_NO                        CS_CMPXHST(0)                   /*!< CMP output no hysteresis */
#define CMP_HYSTERESIS_LOW                       CS_CMPXHST(1)                   /*!< CMP output low hysteresis */
#define CMP_HYSTERESIS_MIDDLE                    CS_CMPXHST(2)                   /*!< CMP output middle hysteresis */
#define CMP_HYSTERESIS_HIGH                      CS_CMPXHST(3)                   /*!< CMP output high hysteresis */

/* CMP digital filter sampling clock division */
#define CS_CMPXDFSCDIV(regval)                  (BITS(10,11) & ((uint32_t)(regval) << 10))
#define CMP_DIGITAL_FILTER_NOT_USED              CS_CMPXDFSCDIV(0)               /*!< CMP not use digital filter */
#define CMP_SAMPLING_FREQUENCY_DIV8              CS_CMPXDFSCDIV(1)               /*!< CMP digital filter sampling frequency is fCK_CMP/8 */
#define CMP_SAMPLING_FREQUENCY_DIV16             CS_CMPXDFSCDIV(2)               /*!< CMP digital filter sampling frequency is fCK_CMP/16 */
#define CMP_SAMPLING_FREQUENCY_DIV32             CS_CMPXDFSCDIV(3)               /*!< CMP digital filter sampling frequency is fCK_CMP/32 */

/* CMP digital filter sampling number */
#define CS_CMPXDFSNUM(regval)                  (BIT(14) & ((uint32_t)(regval) << 14U))
#define CMP_SAMPLING_NUM_3_TIMES               CS_CMPXDFSNUM(0)                  /*!< CMP digital filter sampling number is three times */
#define CMP_SAMPLING_NUM_4_TIMES               CS_CMPXDFSNUM(1)                  /*!< CMP digital filter sampling number is four times */

/* CMP interrupt request enable */
#define CS_CMPXINTEN(regval)                    (BITS(6,7) & ((uint32_t)(regval) << 6))
#define CMP_INT_DISABLE                          CS_CMPXINTEN(0)                 /*!< CMP interrupt disable */
#define CMP_INT_RISING_EDGE                      CS_CMPXINTEN(1)                 /*!< CMP generate interrupt request when rising edge come */
#define CMP_INT_FALLING_EDGE                     CS_CMPXINTEN(2)                 /*!< CMP generate interrupt request when falling edge come */
#define CMP_INT_BOTH_EDGE                        CS_CMPXINTEN(3)                 /*!< CMP generate interrupt request when both edge come */

/* comparator inverting input */
#define CS_CMPXMISEL(regval)                    (BITS(16,18) & ((uint32_t)(regval) << 16))
#define CMP_INVERTING_INPUT_NONE                 CS_CMPXMISEL(0)                 /*!< CMP inverting input none */
#define CMP_INVERTING_INPUT_PC11                 CS_CMPXMISEL(1)                 /*!< CMP inverting input PC11 */
#define CMP_INVERTING_INPUT_PC12                 CS_CMPXMISEL(2)                 /*!< CMP inverting input PC12 */
#define CMP_INVERTING_INPUT_DAC0_OUT0            CS_CMPXMISEL(3)                 /*!< CMP inverting input DAC0_OUT0 */
#define CMP_INVERTING_INPUT_DAC0_OUT1            CS_CMPXMISEL(4)                 /*!< CMP inverting input DAC0_OUT1 */

/* comparator noninverting input */
#define CS_CMPXPSEL(regval)                       (BITS(20,22) & ((uint32_t)(regval) << 20))
#define CMP_NONINVERTING_INPUT_NONE                CS_CMPXPSEL(0)                /*!< CMP noninverting input none */
#define CMP_NONINVERTING_INPUT_PC0_PC1_PC2_PC3     CS_CMPXPSEL(1)                /*!< CMP noninverting input PC0 for CMP0 or PC1 for CMP1 or PC2 for CMP2 or PC3 for CMP3 */
#define CMP_NONINVERTING_INPUT_PC4_PC5_PC6_PD2     CS_CMPXPSEL(2)                /*!< CMP noninverting input PC4 for CMP0 or PC5 for CMP1 or PC6 for CMP2 or PD2 for CMP3 */
#define CMP_NONINVERTING_INPUT_PC10_PC11_PC12_PD4  CS_CMPXPSEL(3)                /*!< CMP noninverting input PC10 for CMP0 or PC11 for CMP1 or PC12 for CMP2 or PD4 for CMP3 */
#define CMP_NONINVERTING_INPUT_PC7_PC0_PC3_PD5     CS_CMPXPSEL(4)                /*!< CMP noninverting input PC7 for CMP0 or PC0 for CMP1 or PC3 for CMP2 or PD5 for CMP3 */
#define CMP_NONINVERTING_INPUT_PC10_PC9            CS_CMPXPSEL(5)                /*!< CMP noninverting input reserved for CMP0 or reserved for CMP1 or PC10 for CMP2 or PC9 for CMP3 */

/* CMP output polarity */
#define CS_CMPXPL(regval)                        (BIT(3) & ((uint32_t)(regval) << 3U))
#define CMP_OUTPUT_POLARITY_NONINVERTED          CS_CMPXPL(0)                    /*!< CMP output not inverted */
#define CMP_OUTPUT_POLARITY_INVERTED             CS_CMPXPL(1)                    /*!< CMP output inverted */

/* CMP output level */
#define CMP_OUTPUTLEVEL_HIGH                    ((uint32_t)0x00000001)           /*!< comparator output high */
#define CMP_OUTPUTLEVEL_LOW                     ((uint32_t)0x00000000)           /*!< comparator output low */

/* CMP flag definitions */
#define CMP_FLAG_COMPARE                         CMP_STAT_CMP0IF                 /*!< CMP compare flag */

/* CMP interrupt definitions */
#define CMP_INT_COMPARE                          CMP_CS_CMPXINTEN                /*!< CMP compare interrupt */

/* CMP interrupt flag */
#define CMP_INT_FLAG_COMPARE                     CMP_STAT_CMP0IF                 /*!< CMP interrupt flag */

/* function declarations */
/* initialization functions */
/* CMP deinit */
void cmp_deinit(cmp_enum cmp_periph);
/* CMP mode init */
void cmp_mode_init(cmp_enum cmp_periph, uint32_t inverting_input, uint32_t output_hysteresis);
/* CMP non-inverting input select */
void cmp_noninverting_input_select(cmp_enum cmp_periph, uint32_t noninverting_input);
/* CMP output init */
void cmp_output_init(cmp_enum cmp_periph, uint32_t output_polarity);
/* CMP digital filter init */
void cmp_digital_filter_init(cmp_enum cmp_periph, uint32_t sampling_frequency, uint32_t sampling_number);

/* enable functions */
/* enable CMP */
void cmp_enable(cmp_enum cmp_periph);
/* disable CMP */
void cmp_disable(cmp_enum cmp_periph);
/* lock the CMP */
void cmp_lock_enable(cmp_enum cmp_periph);
/* enable CMP output to pin */
void cmp_output_to_pin_enable(cmp_enum cmp_periph);
/* disable CMP output to pin */
void cmp_output_to_pin_disable(cmp_enum cmp_periph);
/* enable CMP output */
void cmp_output_enable(cmp_enum cmp_periph);
/* disable CMP output */
void cmp_output_disable(cmp_enum cmp_periph);

/* get state related functions */
/* get output level */
uint32_t cmp_output_level_get(cmp_enum cmp_periph);

/* flag and interrupt functions */
/* get CMP flag */
FlagStatus cmp_flag_get(cmp_enum cmp_periph, uint32_t flag);
/* clear CMP flag */
void cmp_flag_clear(cmp_enum cmp_periph, uint32_t flag);
/* enable CMP interrupt */
void cmp_interrupt_enable(cmp_enum cmp_periph, uint32_t trigger_mode, uint32_t interrupt);
/* disable CMP interrupt */
void cmp_interrupt_disable(cmp_enum cmp_periph, uint32_t interrupt);
/* get CMP interrupt flag */
FlagStatus cmp_interrupt_flag_get(cmp_enum cmp_periph, uint32_t flag);
/* clear CMP interrupt flag */
void cmp_interrupt_flag_clear(cmp_enum cmp_periph, uint32_t flag);

#endif /* GD32M53X_CMP_H */
