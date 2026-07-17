/*!
    \file    gd32f50x_cmp.h
    \brief   definitions for the CMP

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

#ifndef GD32F50X_CMP_H
#define GD32F50X_CMP_H

#include "gd32f50x.h"

/* CMP definitions */
#define CMP                                      CMP_BASE                       /*!< CMP base address */

/* registers definitions */
#define CMP_STAT                                 REG32((CMP) + 0x00000000U)     /*!< CMP status register */
#define CMP_IFC                                  REG32((CMP) + 0x00000004U)     /*!< CMP interrupt flag clear register */
#define CMP0_CS                                  REG32((CMP) + 0x00000008U)     /*!< CMP0 control and status register */

/* bits definitions */
/* CMP_STAT */
#define CMP_STAT_CMP0O                           BIT(0)                         /*!< CMP0 output */
#define CMP_STAT_CMP0IF                          BIT(16)                        /*!< CMP0 interrupt flag */

/* CMP_IFC */
#define CMP_IFC_CMP0IC                           BIT(16)                        /*!< CMP0 interrupt flag clear */

/* CMP0_CS */
#define CMP0_CS_CMP0EN                           BIT(0)                         /*!< CMP0 enable  */
#define CMP0_CS_CMP0BEN                          BIT(1)                         /*!< CMP0 scaler bridge enable bit */
#define CMP0_CS_CMP0SEN                          BIT(2)                         /*!< CMP0 voltage scaler enable bit */
#define CMP0_CS_CMP0PL                           BIT(3)                         /*!< CMP0 output polarity */
#define CMP0_CS_CMP0INTEN                        BIT(6)                         /*!< CMP0 interrupt enable */
#define CMP0_CS_CMP0HST                          BITS(8,9)                      /*!< CMP0 hysteresis */
#define CMP0_CS_CMP0MSEL                         BITS(16,19)                    /*!< CMP_IM input selection */
#define CMP0_CS_CMP0BLK                          BITS(24,27)                    /*!< CMP0 output blanking source */
#define CMP0_CS_CMP0DFSCDIV                      BITS(28,29)                    /*!< CMP0 digital filter sampling clock division */
#define CMP0_CS_CMP0DFSNUM                       BIT(30)                        /*!< CMP0 digital filter sampling number */
#define CMP0_CS_CMP0LK                           BIT(31)                        /*!< CMP0 lock */

/* constants definitions */
/* CMP units */
typedef enum{
    CMP0,                                                                       /*!< comparator 0 */
}cmp_enum;

/* constants definitions */
/* CMP output polarity*/
#define CS_CMPXPL(regval)                        (BIT(3) & ((uint32_t)(regval) << 3U))
#define CMP_OUTPUT_POLARITY_NONINVERTED          CS_CMPXPL(0)                   /*!< CMP output not inverted */
#define CMP_OUTPUT_POLARITY_INVERTED             CS_CMPXPL(1)                   /*!< CMP output inverted */

/* CMP hysteresis */
#define CS_CMPXHST(regval)                       (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define CMP_HYSTERESIS_NO                        CS_CMPXHST(0)                  /*!< CMP output no hysteresis */
#define CMP_HYSTERESIS_LOW                       CS_CMPXHST(1)                  /*!< CMP output low hysteresis */
#define CMP_HYSTERESIS_MIDDLE                    CS_CMPXHST(2)                  /*!< CMP output middle hysteresis */
#define CMP_HYSTERESIS_HIGH                      CS_CMPXHST(3)                  /*!< CMP output high hysteresis */

/* CMP inverting input */
#define CS_CMPXMSEL(regval)                      (BITS(16,19) & ((uint32_t)(regval) << 16U))
#define CMP_INVERTING_INPUT_1_4VREFINT           CS_CMPXMSEL(0)                 /*!< CMP inverting input 1/4 Vrefint */
#define CMP_INVERTING_INPUT_1_2VREFINT           CS_CMPXMSEL(1)                 /*!< CMP inverting input 1/2 Vrefint */
#define CMP_INVERTING_INPUT_3_4VREFINT           CS_CMPXMSEL(2)                 /*!< CMP inverting input 3/4 Vrefint */
#define CMP_INVERTING_INPUT_VREFINT              CS_CMPXMSEL(3)                 /*!< CMP inverting input Vrefint */
#define CMP_INVERTING_INPUT_PA4                  CS_CMPXMSEL(4)                 /*!< CMP inverting input PA4  */
#define CMP_INVERTING_INPUT_PA5                  CS_CMPXMSEL(5)                 /*!< CMP inverting input PA5  */
#define CMP_INVERTING_INPUT_PA2                  CS_CMPXMSEL(6)                 /*!< CMP inverting input PA2  */
#define CMP_INVERTING_INPUT_DAC0_OUT0            CS_CMPXMSEL(7)                 /*!< CMP inverting input DAC_OUT0 */

/* CMP blanking suorce */
#define CS_CMPXBLK(regval)                       (BITS(24,27) & ((uint32_t)(regval) << 24U))
#define CMP_BLANKING_NONE                        CS_CMPXBLK(0)                  /*!< CMP no blanking source */
#define CMP_BLANKING_TIMER0_OC0                  CS_CMPXBLK(1)                  /*!< CMP TIMER0_CH0 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER1_OC2                  CS_CMPXBLK(2)                  /*!< CMP TIMER1_CH2 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER2_OC2                  CS_CMPXBLK(3)                  /*!< CMP TIMER2_CH2 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER2_OC3                  CS_CMPXBLK(4)                  /*!< CMP TIMER2_CH3 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER7_OC0                  CS_CMPXBLK(5)                  /*!< CMP TIMER7_CH0 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER15_OC0                 CS_CMPXBLK(6)                  /*!< CMP TIMER15_CH0 output compare signal selected as blanking source */

/* CMP digital noise sampling */
#define CS_CMPXDNSSEL(regval)                    (BITS(28,29) & ((uint32_t)(regval) << 28U))
#define CMP_NOISE_FILTER_NONE                    CS_CMPXDNSSEL(0)               /*!< CMP no noise filter */
#define CMP_SAMPLING_FREQUENCY_PCLK_DIV8         CS_CMPXDNSSEL(1)               /*!< CMP sampling frequency is PCLK/8 */
#define CMP_SAMPLING_FREQUENCY_PCLK_DIV16        CS_CMPXDNSSEL(2)               /*!< CMP sampling frequency is PCLK/16 */
#define CMP_SAMPLING_FREQUENCY_PCLK_DIV32        CS_CMPXDNSSEL(3)               /*!< CMP sampling frequency is PCLK/32 */

/* comparator noise filter mode select */
#define CMP_FILTER_MODE_3_TIMES                  ((uint32_t)0x00000000U)        /*!< Output changes when the same value is sampled 3 times */
#define CMP_FILTER_MODE_4_TIMES                  ((uint32_t)0x00000001U)        /*!< Output changes when the same value is sampled 4 times */

/* comparator output level */
#define CMP_OUTPUTLEVEL_HIGH                     ((uint32_t)0x00000001U)        /*!< comparator output high */
#define CMP_OUTPUTLEVEL_LOW                      ((uint32_t)0x00000000U)        /*!< comparator output low */

/* CMP flag definitions */
#define CMP_FLAG_COMPARE                         CMP_STAT_CMP0IF                /*!< CMP compare flag */

/* CMP interrupt definitions */
#define CMP_INT_COMPARE                          CMP0_CS_CMP0INTEN               /*!< CMP compare interrupt */

/* CMP interrupt flag */
#define CMP_INT_FLAG_COMPARE                     CMP_STAT_CMP0IF                /*!< CMP interrupt flag */

/* function declarations */
/* initialization functions */
/* CMP deinit */
void cmp_deinit(void);
/* CMP mode init */
void cmp_mode_init(cmp_enum cmp_periph, uint32_t inverting_input, uint32_t output_hysteresis);
/* CMP output init */
void cmp_output_init(cmp_enum cmp_periph, uint32_t output_polarity);
/* CMP output blanking function init */
void cmp_blanking_init(cmp_enum cmp_periph, uint32_t blanking_source_selection);
/* CMP digital filter init */
void cmp_digital_filter_init(cmp_enum cmp_periph, uint32_t sample_frequency_selection, uint32_t filter_mode_selection);

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

/* get state related functions */
/* get output level */
uint32_t cmp_output_level_get(cmp_enum cmp_periph);

/* flag and interrupt functions */
/* get CMP flag */
FlagStatus cmp_flag_get(cmp_enum cmp_periph, uint32_t flag);
/* clear CMP flag */
void cmp_flag_clear(cmp_enum cmp_periph, uint32_t flag);
/* enable CMP interrupt */
void cmp_interrupt_enable(cmp_enum cmp_periph, uint32_t interrupt);
/* disable CMP interrupt */
void cmp_interrupt_disable(cmp_enum cmp_periph, uint32_t interrupt);
/* get CMP interrupt flag */
FlagStatus cmp_interrupt_flag_get(cmp_enum cmp_periph, uint32_t flag);
/* clear CMP interrupt flag */
void cmp_interrupt_flag_clear(cmp_enum cmp_periph, uint32_t flag);


#endif /* gd32f50x_CMP_H */
