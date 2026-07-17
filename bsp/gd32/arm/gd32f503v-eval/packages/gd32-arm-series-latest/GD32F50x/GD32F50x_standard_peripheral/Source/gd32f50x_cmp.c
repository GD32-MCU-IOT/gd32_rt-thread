/*!
    \file    gd32f50x_cmp.c
    \brief   CMP driver

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

#include "gd32f50x_cmp.h"

/*!
    \brief      CMP deinit (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cmp_deinit(void)
{
    /* reset CMP */
    rcu_periph_reset_enable(RCU_CMPRST);
    rcu_periph_reset_disable(RCU_CMPRST);
}

/*!
    \brief      CMP mode init (API_ID(0x0002U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[in]  inverting_input
      \arg        CMP_INVERTING_INPUT_1_4VREFINT: VREFINT * 1/4 input
      \arg        CMP_INVERTING_INPUT_1_2VREFINT: VREFINT * 1/2 input
      \arg        CMP_INVERTING_INPUT_3_4VREFINT: VREFINT * 3/4 input
      \arg        CMP_INVERTING_INPUT_VREFINT: VREFINT input
      \arg        CMP_INVERTING_INPUT_PA4: CMP inverting input PA4
      \arg        CMP_INVERTING_INPUT_PA5: CMP inverting input PA5
      \arg        CMP_INVERTING_INPUT_PA2: CMP inverting input PA2
      \arg        CMP_INVERTING_INPUT_DAC0_OUT0: CMP inverting input DAC0_OUT0
    \param[in]  output_hysteresis
      \arg        CMP_HYSTERESIS_NO: output no hysteresis
      \arg        CMP_HYSTERESIS_LOW: output low hysteresis
      \arg        CMP_HYSTERESIS_MIDDLE: output middle hysteresis
      \arg        CMP_HYSTERESIS_HIGH: output high hysteresis
    \param[out] none
    \retval     none
*/
void cmp_mode_init(cmp_enum cmp_periph, uint32_t inverting_input, uint32_t output_hysteresis)
{
    uint32_t temp = 0U;
    if(CMP0 == cmp_periph){
        /* initialize comparator 0 mode */
        temp = CMP0_CS;
        temp &= ~(uint32_t)(CMP0_CS_CMP0MSEL | CMP0_CS_CMP0HST);
        temp |= (uint32_t)((inverting_input & CMP0_CS_CMP0MSEL)| (output_hysteresis & CMP0_CS_CMP0HST));
        CMP0_CS = temp;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      CMP output init (API_ID(0x0003U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[in]  output_polarity
      \arg        CMP_OUTPUT_POLARITY_INVERTED: output is inverted
      \arg        CMP_OUTPUT_POLARITY_NONINVERTED: output is not inverted
    \param[out] none
    \retval     none
*/
void cmp_output_init(cmp_enum cmp_periph, uint32_t output_polarity)
{
    uint32_t temp = 0U;
    if(CMP0 == cmp_periph){
        /* initialize comparator 0 output */
        temp = CMP0_CS;
        /* output polarity */
        if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity){
            temp |= (uint32_t)CMP0_CS_CMP0PL;
        }else{
            temp &= ~(uint32_t)CMP0_CS_CMP0PL;
        }
        CMP0_CS = temp;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      CMP output blanking function init (API_ID(0x0004U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[in]  blanking_source_selection 
      \arg        CMP_BLANKING_NONE: CMP no blanking source
      \arg        CMP_BLANKING_TIMER0_OC0: CMP TIMER0_CH0 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER1_OC2: CMP TIMER1_CH2 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER2_OC2: CMP TIMER2_CH2 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER2_OC3: CMP TIMER2_CH3 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER7_OC0: CMP TIMER7_CH0 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER15_OC0: CMP TIMER15_CH0 output compare signal selected as blanking source
    \param[out] none
    \retval     none
*/
void cmp_blanking_init(cmp_enum cmp_periph, uint32_t blanking_source_selection)
{
    uint32_t temp = 0U;
    if(CMP0 == cmp_periph){
        temp = CMP0_CS;
        temp &= ~(uint32_t)CMP0_CS_CMP0BLK;
        temp |= (uint32_t)(blanking_source_selection & CMP0_CS_CMP0BLK);
        CMP0_CS = temp;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      CMP digital filter init (API_ID(0x0005U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[in]  sample_frequency_selection 
      \arg        CMP_NOISE_FILTER_NONE: CMP no noise filter
      \arg        CMP_SAMPLING_FREQUENCY_PCLK_DIV8: CMP sampling frequency is PCLK/8
      \arg        CMP_SAMPLING_FREQUENCY_PCLK_DIV16: CMP sampling frequency is PCLK/16
      \arg        CMP_SAMPLING_FREQUENCY_PCLK_DIV32: CMP sampling frequency is PCLK/32
    \param[in]  filter_mode_selection 
      \arg        CMP_FILTER_MODE_3_TIMES: Output changes when the same value is sampled 3 times
      \arg        CMP_FILTER_MODE_4_TIMES: Output changes when the same value is sampled 4 times
    \param[out] none
    \retval     none
*/
void cmp_digital_filter_init(cmp_enum cmp_periph, uint32_t sample_frequency_selection, uint32_t filter_mode_selection)
{
    uint32_t temp = 0U;
    if(CMP0 == cmp_periph){
        temp = CMP0_CS;
        temp &= ~(uint32_t)(CMP0_CS_CMP0DFSCDIV | CMP0_CS_CMP0DFSNUM);
        temp |= (uint32_t)((sample_frequency_selection & CMP0_CS_CMP0DFSCDIV) | (filter_mode_selection & CMP0_CS_CMP0DFSNUM));
        CMP0_CS = temp;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      enable CMP (API_ID(0x0006U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[out] none
    \retval     none
*/
void cmp_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph){
        CMP0_CS |= (uint32_t)CMP0_CS_CMP0EN;
        CMP0_CS |= (uint32_t)CMP0_CS_CMP0SEN;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      disable CMP (API_ID(0x0007U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[out] none
    \retval     none
*/
void cmp_disable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph){
        CMP0_CS &= ~(uint32_t)CMP0_CS_CMP0EN;
        CMP0_CS &= ~(uint32_t)CMP0_CS_CMP0SEN;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      lock the comparator (API_ID(0x0008U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[out] none
    \retval     none
*/
void cmp_lock_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph){
        /* lock CMP0 */
        CMP0_CS |= (uint32_t)CMP0_CS_CMP0LK;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      enable the voltage scaler (API_ID(0x0009U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[out] none
    \retval     none
*/
void cmp_voltage_scaler_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph){
        CMP0_CS |= (uint32_t)CMP0_CS_CMP0SEN;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      disable the voltage scaler (API_ID(0x000AU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[out] none
    \retval     none
*/
void cmp_voltage_scaler_disable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph){
        CMP0_CS &= ~(uint32_t)CMP0_CS_CMP0SEN;
    }else{
        /* illegal parameters */
    }
}

/*! 
    \brief      enable the scaler bridge (API_ID(0x000BU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[out] none
    \retval     none
*/
void cmp_scaler_bridge_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph){
        CMP0_CS |= (uint32_t)CMP0_CS_CMP0BEN;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      disable the scaler bridge (API_ID(0x000CU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[out] none
    \retval     none
*/
void cmp_scaler_bridge_disable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph){
        CMP0_CS &= ~(uint32_t)CMP0_CS_CMP0BEN;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      get output level (API_ID(0x000DU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[out] none
    \retval     the output level: CMP_OUTPUTLEVEL_HIGH or CMP_OUTPUTLEVEL_LOW 
*/
uint32_t cmp_output_level_get(cmp_enum cmp_periph)
{
    uint32_t reval = 0U;
    if(CMP0 == cmp_periph){
        /* get output level of CMP0 */
        if((uint32_t)RESET != (CMP_STAT & CMP_STAT_CMP0O)) {
            reval = CMP_OUTPUTLEVEL_HIGH;
        }else{
            reval = CMP_OUTPUTLEVEL_LOW;
        }
    }else{
        /* illegal parameters */
    }
    return reval;
}

/*!
    \brief      get CMP flag (API_ID(0x000EU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[in]  flag: CMP flags
                only one parameter can be selected which is shown as below:
      \arg        CMP_FLAG_COMPARE: CMP compare flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cmp_flag_get(cmp_enum cmp_periph, uint32_t flag)
{
    FlagStatus reval = RESET;
    if(CMP0 == cmp_periph){
        if(CMP_FLAG_COMPARE == flag){
            if(0U != (CMP_STAT & CMP_STAT_CMP0IF)){
                reval = SET;
            }
        }
    }else{
        /* illegal parameters */
    }

    return reval;
}

/*!
    \brief      clear CMP flag (API_ID(0x000FU))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[in]  flag: CMP flags
                only one parameter can be selected which is shown as below:
      \arg        CMP_FLAG_COMPARE: CMP compare flag
    \param[out] none
    \retval     none
*/
void cmp_flag_clear(cmp_enum cmp_periph, uint32_t flag)
{
    if(CMP0 == cmp_periph){
        if(CMP_FLAG_COMPARE == flag){
            CMP_IFC |= (uint32_t)CMP_IFC_CMP0IC;
        }
        else{
            /* illegal parameters */
        }
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      enable CMP interrupt (API_ID(0x0010U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[in]  interrupt: CMP interrupt enable source
                only one parameter can be selected which is shown as below:
      \arg        CMP_INT_COMPARE: CMP compare interrupt
    \param[out] none
    \retval     none
*/
void cmp_interrupt_enable(cmp_enum cmp_periph, uint32_t interrupt)
{
    if(CMP0 == cmp_periph){
        /* enable CMP0 interrupt */
        CMP0_CS |= (uint32_t)(interrupt & CMP_INT_COMPARE);
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      disable CMP interrupt (API_ID(0x0011U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[in]  interrupt: CMP interrupt enable source
                only one parameter can be selected which is shown as below:
      \arg        CMP_INT_COMPARE: CMP compare interrupt
    \param[out] none
    \retval     none
*/
void cmp_interrupt_disable(cmp_enum cmp_periph, uint32_t interrupt)
{
    if(CMP0 == cmp_periph){
        /* disable CMP0 interrupt */
        CMP0_CS &= ~(uint32_t)(interrupt & CMP_INT_COMPARE);
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      get CMP interrupt flag (API_ID(0x0012U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[in]  flag: CMP flags
      \arg        CMP_INT_FLAG_COMPARE: CMP compare interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cmp_interrupt_flag_get(cmp_enum cmp_periph, uint32_t flag)
{
    uint32_t intstatus = 0U, flagstatus = 0U;
    FlagStatus reval = RESET;
    if(CMP0 == cmp_periph){
        if(CMP_INT_FLAG_COMPARE == flag){
            /* get the corresponding flag bit status */
            flagstatus = CMP_STAT & CMP_STAT_CMP0IF;
            /* get the interrupt enable bit status */
            intstatus = CMP0_CS & CMP0_CS_CMP0INTEN;
        }

        if((0U != flagstatus) && (0U != intstatus)){
            reval = SET;
        }else{
            reval = RESET;
        }
    }else{
        /* illegal parameters */
    }
    return reval;
}

/*!
    \brief      clear CMP interrupt flag (API_ID(0x0013U))
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
    \param[in]  flag: CMP interrupt flags
      \arg        CMP_INT_FLAG_COMPARE: CMP compare interrupt flag
    \param[out] none
    \retval     none
*/
void cmp_interrupt_flag_clear(cmp_enum cmp_periph, uint32_t flag)
{
    if(CMP0 == cmp_periph){
        /* clear CMP interrupt flag */
        if(CMP_INT_FLAG_COMPARE == flag){
            CMP_IFC |= (uint32_t)CMP_IFC_CMP0IC;
        }else{
            /* illegal parameters */
        }
    }else{
        /* illegal parameters */
    }
}
