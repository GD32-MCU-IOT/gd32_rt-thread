/*!
    \file    gd32g5x3_cmp.c
    \brief   CMP driver

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

#include "gd32g5x3_cmp.h"

/*!
    \brief      CMP deinit
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cmp_deinit(void)
{
    rcu_periph_reset_enable(RCU_CMPRST);
    rcu_periph_reset_disable(RCU_CMPRST);
}

/*!
    \brief      CMP mode init
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[in]  inverting_input
      \arg        CMPX_INVERTING_INPUT_1_4VREFINT: VREFINT *1/4 input
      \arg        CMPX_INVERTING_INPUT_1_2VREFINT: VREFINT *1/2 input
      \arg        CMPX_INVERTING_INPUT_3_4VREFINT: VREFINT *3/4 input
      \arg        CMPX_INVERTING_INPUT_VREFINT: VREFINT input
      \arg        CMP0_INVERTING_INPUT_DAC2_OUT0: DAC2_OUT0 input for CMP0
      \arg        CMP0_INVERTING_INPUT_DAC0_OUT0: DAC0_OUT0 input for CMP0
      \arg        CMP0_INVERTING_INPUT_PA4: PA4 input for CMP0
      \arg        CMP0_INVERTING_INPUT_PA0: PA0 input for CMP0
      \arg        CMP1_INVERTING_INPUT_DAC2_OUT1: DAC2_OUT1 input for CMP1
      \arg        CMP1_INVERTING_INPUT_DAC0_OUT1: DAC0_OUT1 input for CMP1
      \arg        CMP1_INVERTING_INPUT_PA5: PA5 input for CMP1
      \arg        CMP1_INVERTING_INPUT_PA2: PA2 input for CMP1
      \arg        CMP2_INVERTING_INPUT_DAC2_OUT0: DAC2_OUT0 input for CMP2
      \arg        CMP2_INVERTING_INPUT_DAC0_OUT0: DAC0_OUT0 input for CMP2
      \arg        CMP2_INVERTING_INPUT_PF1: PF1 input for CMP2
      \arg        CMP2_INVERTING_INPUT_PC0: PC0 input for CMP2
      \arg        CMP3_INVERTING_INPUT_DAC2_OUT1: DAC2_OUT1 input for CMP3
      \arg        CMP3_INVERTING_INPUT_DAC0_OUT0: DAC0_OUT0 input for CMP3
      \arg        CMP3_INVERTING_INPUT_PE8: PE8 input for CMP3
      \arg        CMP3_INVERTING_INPUT_PB2: PB2 input for CMP3
      \arg        CMP4_INVERTING_INPUT_DAC3_OUT0: DAC3_OUT0 input for CMP4
      \arg        CMP4_INVERTING_INPUT_DAC0_OUT1: DAC0_OUT1 input for CMP4
      \arg        CMP4_INVERTING_INPUT_PB10: PB10 input for CMP4
      \arg        CMP4_INVERTING_INPUT_PD13: PD13 input for CMP4
      \arg        CMP5_INVERTING_INPUT_DAC3_OUT1: DAC3_OUT1 input for CMP5
      \arg        CMP5_INVERTING_INPUT_DAC1_OUT0: DAC1_OUT0 input for CMP5
      \arg        CMP5_INVERTING_INPUT_PD10: PD10 input for CMP5
      \arg        CMP5_INVERTING_INPUT_PB15: PB15 input for CMP5
      \arg        CMP6_INVERTING_INPUT_DAC3_OUT0: DAC3_OUT0 input for CMP6
      \arg        CMP6_INVERTING_INPUT_DAC1_OUT0: DAC1_OUT0 input for CMP6
      \arg        CMP6_INVERTING_INPUT_PD15: PD15 input for CMP6
      \arg        CMP6_INVERTING_INPUT_PB12: PB12 input for CMP6
      \arg        CMP7_INVERTING_INPUT_DAC3_OUT1: DAC3_OUT1 input for CMP7
      \arg        CMP7_INVERTING_INPUT_DAC1_OUT1: DAC1_OUT1 input for CMP7
      \arg        CMP7_INVERTING_INPUT_PD8: PD8 input for CMP7
      \arg        CMP7_INVERTING_INPUT_PD9: PD9 input for CMP7
    \param[in]  output_hysteresis
      \arg        CMP_HYSTERESIS_NO: CMP output no hysteresis
      \arg        CMP_HYSTERESIS_10MV: CMP output 10mv hysteresis
      \arg        CMP_HYSTERESIS_20MV: CMP output 20mv hysteresis
      \arg        CMP_HYSTERESIS_30MV: CMP output 30mv hysteresis
      \arg        CMP_HYSTERESIS_40MV: CMP output 40mv hysteresis
      \arg        CMP_HYSTERESIS_50MV: CMP output 50mv hysteresis
      \arg        CMP_HYSTERESIS_60MV: CMP output 60mv hysteresis
      \arg        CMP_HYSTERESIS_70MV: CMP output 70mv hysteresis
    \param[out] none
    \retval     none
*/
void cmp_mode_init(cmp_enum cmp_periph, uint32_t inverting_input, uint32_t output_hysteresis)
{
    uint32_t temp = 0U;
    temp = CMP_CS(cmp_periph);
    temp &= ~(uint32_t)(CMP_CS_CMPXMSEL | CMP_CS_CMPXHST);
    temp |= (uint32_t)(inverting_input | output_hysteresis);
    CMP_CS(cmp_periph) = temp;
}

/*!
    \brief      CMP noninverting input select
    \param[in]  cmp_periph:: CMPx(x=0,1,2,3,4,5,6,7)
    \param[in]  noninverting_input
      \arg        CMP0_NONINVERTING_INPUT_PA1: CMP noninverting input PA1 for CMP0 
      \arg        CMP0_NONINVERTING_INPUT_PB1: CMP noninverting input PB1 for CMP0 
      \arg        CMP1_NONINVERTING_INPUT_PA7: CMP noninverting input PA7 for CMP1 
      \arg        CMP1_NONINVERTING_INPUT_PA3: CMP noninverting input PA3 for CMP1 
      \arg        CMP2_NONINVERTING_INPUT_PA0: CMP noninverting input PA0 for CMP2 
      \arg        CMP2_NONINVERTING_INPUT_PC1: CMP noninverting input PC1 for CMP2 
      \arg        CMP3_NONINVERTING_INPUT_PB0: CMP noninverting input PB0 for CMP3 
      \arg        CMP3_NONINVERTING_INPUT_PE7: CMP noninverting input PE7 for CMP3 
      \arg        CMP4_NONINVERTING_INPUT_PB13: CMP noninverting input PB13 for CMP4
      \arg        CMP4_NONINVERTING_INPUT_PD12: CMP noninverting input PD12 for CMP4
      \arg        CMP5_NONINVERTING_INPUT_PB11: CMP noninverting input PB11 for CMP5
      \arg        CMP5_NONINVERTING_INPUT_PD11: CMP noninverting input PD11 for CMP5
      \arg        CMP6_NONINVERTING_INPUT_PB14: CMP noninverting input PB14 for CMP6
      \arg        CMP6_NONINVERTING_INPUT_PD14: CMP noninverting input PD14 for CMP6
      \arg        CMP7_NONINVERTING_INPUT_PC2: CMP noninverting input PC2 for CMP7 
      \arg        CMP7_NONINVERTING_INPUT_PE9: CMP noninverting input PE9 for CMP7 
    \param[out] none
    \retval     none
*/
void cmp_noninverting_input_select(cmp_enum cmp_periph, uint32_t noninverting_input)
{
    uint32_t temp = 0U;
    temp = CMP_CS(cmp_periph);
    temp &= ~(uint32_t)CMP_CS_CMPXPSEL;
    temp |= (uint32_t)noninverting_input;
    CMP_CS(cmp_periph) = temp;
}

/*!
    \brief      CMP output init
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[in]  output_polarity
      \arg        CMP_OUTPUT_POLARITY_INVERTED: output is inverted
      \arg        CMP_OUTPUT_POLARITY_NONINVERTED: output is not inverted
    \param[out] none
    \retval     none
*/
void cmp_output_init(cmp_enum cmp_periph, uint32_t output_polarity)
{
    uint32_t temp = 0U;
    temp = CMP_CS(cmp_periph);
    if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity){
        temp |= (uint32_t)CMP_CS_CMPXPL;
    }else{
        temp &= ~(uint32_t)CMP_CS_CMPXPL;
    }
    CMP_CS(cmp_periph) = temp;
}

/*!
    \brief      CMP output blanking function init
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[in]  blanking_source_selection 
      \arg        CMP_BLANKING_NONE: CMP no blanking source
      \arg        CMP0_BLANKING_TIMER0_OC2: CMP TIMER0_CH2 output compare signal selected as blanking source for CMP0 
      \arg        CMP0_BLANKING_TIMER1_OC2: CMP TIMER1_CH2 output compare signal selected as blanking source for CMP0 
      \arg        CMP0_BLANKING_TIMER2_OC2: CMP TIMER2_CH2 output compare signal selected as blanking source for CMP0 
      \arg        CMP0_BLANKING_TIMER7_OC2: CMP TIMER7_CH2 output compare signal selected as blanking source for CMP0 
      \arg        CMP0_BLANKING_TIMER19_OC2: CMP TIMER19_CH2 output compare signal selected as blanking source for CMP0
      \arg        CMP0_BLANKING_TIMER14_OC0: CMP TIMER14_CH0 output compare signal selected as blanking source for CMP0
      \arg        CMP0_BLANKING_TIMER3_OC2: CMP TIMER3_CH2 output compare signal selected as blanking source for CMP0 
      \arg        CMP1_BLANKING_TIMER0_OC2: CMP TIMER0_CH2 output compare signal selected as blanking source for CMP1 
      \arg        CMP1_BLANKING_TIMER1_OC2: CMP TIMER1_CH2 output compare signal selected as blanking source for CMP1 
      \arg        CMP1_BLANKING_TIMER2_OC2: CMP TIMER2_CH2 output compare signal selected as blanking source for CMP1 
      \arg        CMP1_BLANKING_TIMER7_OC2: CMP TIMER7_CH2 output compare signal selected as blanking source for CMP1 
      \arg        CMP1_BLANKING_TIMER19_OC2: CMP TIMER19_CH2 output compare signal selected as blanking source for CMP1
      \arg        CMP1_BLANKING_TIMER14_OC0: CMP TIMER14_CH0 output compare signal selected as blanking source for CMP1
      \arg        CMP1_BLANKING_TIMER3_OC2: CMP TIMER3_CH2 output compare signal selected as blanking source for CMP1 
      \arg        CMP2_BLANKING_TIMER0_OC2: CMP TIMER0_CH2 output compare signal selected as blanking source for CMP2 
      \arg        CMP2_BLANKING_TIMER2_OC2: CMP TIMER2_CH2 output compare signal selected as blanking source for CMP2 
      \arg        CMP2_BLANKING_TIMER1_OC3: CMP TIMER1_CH3 output compare signal selected as blanking source for CMP2 
      \arg        CMP2_BLANKING_TIMER7_OC2: CMP TIMER7_CH2 output compare signal selected as blanking source for CMP2 
      \arg        CMP2_BLANKING_TIMER19_OC2: CMP TIMER19_CH2 output compare signal selected as blanking source for CMP2
      \arg        CMP2_BLANKING_TIMER14_OC0: CMP TIMER14_CH0 output compare signal selected as blanking source for CMP2
      \arg        CMP2_BLANKING_TIMER3_OC2: CMP TIMER3_CH2 output compare signal selected as blanking source for CMP2 
      \arg        CMP3_BLANKING_TIMER2_OC3: CMP TIMER2_CH3 output compare signal selected as blanking source for CMP3 
      \arg        CMP3_BLANKING_TIMER7_OC2: CMP TIMER7_CH2 output compare signal selected as blanking source for CMP3 
      \arg        CMP3_BLANKING_TIMER14_OC1: CMP TIMER14_CH1 output compare signal selected as blanking source for CMP3
      \arg        CMP3_BLANKING_TIMER0_OC2: CMP TIMER0_CH2 output compare signal selected as blanking source for CMP3 
      \arg        CMP3_BLANKING_TIMER19_OC2: CMP TIMER19_CH2 output compare signal selected as blanking source for CMP3
      \arg        CMP3_BLANKING_TIMER14_OC0: CMP TIMER14_CH0 output compare signal selected as blanking source for CMP3
      \arg        CMP3_BLANKING_TIMER3_OC2: CMP TIMER3_CH2 output compare signal selected as blanking source for CMP3 
      \arg        CMP4_BLANKING_TIMER1_OC2: CMP TIMER1_CH2 output compare signal selected as blanking source for CMP4 
      \arg        CMP4_BLANKING_TIMER7_OC2: CMP TIMER7_CH2 output compare signal selected as blanking source for CMP4 
      \arg        CMP4_BLANKING_TIMER2_OC2: CMP TIMER2_CH2 output compare signal selected as blanking source for CMP4 
      \arg        CMP4_BLANKING_TIMER0_OC2: CMP TIMER0_CH2 output compare signal selected as blanking source for CMP4 
      \arg        CMP4_BLANKING_TIMER19_OC2: CMP TIMER19_CH2 output compare signal selected as blanking source for CMP4
      \arg        CMP4_BLANKING_TIMER14_OC0: CMP TIMER14_CH0 output compare signal selected as blanking source for CMP4
      \arg        CMP4_BLANKING_TIMER3_OC2: CMP TIMER3_CH2 output compare signal selected as blanking source for CMP4 
      \arg        CMP5_BLANKING_TIMER7_OC2: CMP TIMER7_CH2 output compare signal selected as blanking source for CMP5 
      \arg        CMP5_BLANKING_TIMER1_OC3: CMP TIMER1_CH3 output compare signal selected as blanking source for CMP5 
      \arg        CMP5_BLANKING_TIMER14_OC1: CMP TIMER14_CH1 output compare signal selected as blanking source for CMP5
      \arg        CMP5_BLANKING_TIMER0_OC2: CMP TIMER0_CH2 output compare signal selected as blanking source for CMP5 
      \arg        CMP5_BLANKING_TIMER19_OC2: CMP TIMER19_CH2 output compare signal selected as blanking source for CMP5
      \arg        CMP5_BLANKING_TIMER14_OC0: CMP TIMER14_CH0 output compare signal selected as blanking source for CMP5
      \arg        CMP5_BLANKING_TIMER3_OC2: CMP TIMER3_CH2 output compare signal selected as blanking source for CMP5 
      \arg        CMP6_BLANKING_TIMER0_OC2: CMP TIMER0_CH2 output compare signal selected as blanking source for CMP6 
      \arg        CMP6_BLANKING_TIMER7_OC2: CMP TIMER7_CH2 output compare signal selected as blanking source for CMP6 
      \arg        CMP6_BLANKING_TIMER2_OC2: CMP TIMER2_CH2 output compare signal selected as blanking source for CMP6 
      \arg        CMP6_BLANKING_TIMER14_OC1: CMP TIMER14_CH1 output compare signal selected as blanking source for CMP6
      \arg        CMP6_BLANKING_TIMER19_OC2: CMP TIMER19_CH2 output compare signal selected as blanking source for CMP6
      \arg        CMP6_BLANKING_TIMER14_OC0: CMP TIMER14_CH0 output compare signal selected as blanking source for CMP6
      \arg        CMP6_BLANKING_TIMER3_OC2: CMP TIMER3_CH2 output compare signal selected as blanking source for CMP6 
      \arg        CMP7_BLANKING_TIMER1_OC2: CMP TIMER1_CH2 output compare signal selected as blanking source for CMP7 
      \arg        CMP7_BLANKING_TIMER7_OC2: CMP TIMER7_CH2 output compare signal selected as blanking source for CMP7 
      \arg        CMP7_BLANKING_TIMER2_OC2: CMP TIMER2_CH2 output compare signal selected as blanking source for CMP7 
      \arg        CMP7_BLANKING_TIMER0_OC2: CMP TIMER0_CH2 output compare signal selected as blanking source for CMP7 
      \arg        CMP7_BLANKING_TIMER19_OC2: CMP TIMER19_CH2 output compare signal selected as blanking source for CMP7
      \arg        CMP7_BLANKING_TIMER14_OC0: CMP TIMER14_CH0 output compare signal selected as blanking source for CMP7
      \arg        CMP7_BLANKING_TIMER3_OC2: CMP TIMER3_CH2 output compare signal selected as blanking source for CMP7 
    \param[out] none
    \retval     none
*/
void cmp_blanking_init(cmp_enum cmp_periph, uint32_t blanking_source_selection)
{
    uint32_t temp = 0U;
    temp = CMP_CS(cmp_periph);
    temp &= ~(uint32_t)CMP_CS_CMPXBLK;
    temp |= (uint32_t)blanking_source_selection;
    CMP_CS(cmp_periph) = temp;
}

/*!
    \brief      enable CMP
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_enable(cmp_enum cmp_periph)
{
     CMP_CS(cmp_periph) |= CMP_CS_CMPXEN;
}

/*!
    \brief      disable CMP
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_disable(cmp_enum cmp_periph)
{
    CMP_CS(cmp_periph) &= ~CMP_CS_CMPXEN;
}

/*!
    \brief      lock the comparator
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_lock_enable(cmp_enum cmp_periph)
{
    CMP_CS(cmp_periph) |= (uint32_t)CMP_CS_CMPXLK;
}

/*!
    \brief      enable the voltage scaler
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_voltage_scaler_enable(cmp_enum cmp_periph)
{
    CMP_CS(cmp_periph) |= (uint32_t)CMP_CS_CMPXSEN;
}

/*!
    \brief      disable the voltage scaler
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_voltage_scaler_disable(cmp_enum cmp_periph)
{
    CMP_CS(cmp_periph) &= ~(uint32_t)CMP_CS_CMPXSEN;
}

/*! 
    \brief      enable the scaler bridge
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_scaler_bridge_enable(cmp_enum cmp_periph)
{
    CMP_CS(cmp_periph) |= (uint32_t)CMP_CS_CMPXBEN;
}

/*!
    \brief      disable the scaler bridge
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_scaler_bridge_disable(cmp_enum cmp_periph)
{
    CMP_CS(cmp_periph) &= ~(uint32_t)CMP_CS_CMPXBEN;
}

/*!
    \brief      enable comparator reset persisit mode
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_reset_persist_mode_enable(cmp_enum cmp_periph)
{
    CMP_CS(cmp_periph) |= (uint32_t)CMP_CS_CMPXRSTMD;
}

/*!
    \brief      disable comparator reset persisit mode
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_reset_persist_mode_disable(cmp_enum cmp_periph)
{
    CMP_CS(cmp_periph) &= ~(uint32_t)CMP_CS_CMPXRSTMD;
}

/*!
    \brief      get output level
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     the output level
*/
uint32_t cmp_output_level_get(cmp_enum cmp_periph)
{
    if(RESET != (CMP_STAT & (1U << cmp_periph))){
        return CMP_OUTPUTLEVEL_HIGH;
    }else{
        return CMP_OUTPUTLEVEL_LOW;
    }
}

/*!
    \brief      get CMP flag
    \param[in]  flag: CMP_FLAG_CMPxF(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cmp_flag_get(uint32_t flag)
{
    if(0U != (CMP_STAT & flag)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CMP flag
    \param[in]  flag: CMP_FLAG_CMPxF_CLR(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_flag_clear(uint32_t flag)
{
    CMP_IFC = (flag);
}

/*!
    \brief      disable comparator interrupt
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_interrupt_enable(cmp_enum cmp_periph)
{
    CMP_CS(cmp_periph) |= (uint32_t)CMP_CS_CMPXINTEN;
}

/*!
    \brief      disable comparator interrupt
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_interrupt_disable(cmp_enum cmp_periph)
{
    CMP_CS(cmp_periph) &= ~(uint32_t)CMP_CS_CMPXINTEN;
}

/*!
    \brief      get CMP interrupt flag
    \param[in]  cmp_periph: CMPx(x=0,1,2,3,4,5,6,7)
    \param[in]  int_flag: CMP_INT_FLAG_CMPxF(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cmp_interrupt_flag_get(cmp_enum cmp_periph, uint32_t flag)
{
    uint32_t intenable = 0U, flagstatus = 0U;
    
    /* get the corresponding flag bit status */
    flagstatus = CMP_STAT & flag;
    /* get the interrupt enable bit status */
    intenable = CMP_CS(cmp_periph) & CMP_CS_CMPXINTEN;
    
    if((0U != flagstatus) && (0U != intenable)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CMP interrupt flag
    \param[in]  flag: CMP_INT_FLAG_CMPxF_CLR(x=0,1,2,3,4,5,6,7)
    \param[out] none
    \retval     none
*/
void cmp_interrupt_flag_clear(uint32_t flag)
{
    CMP_IFC = (flag);
}
