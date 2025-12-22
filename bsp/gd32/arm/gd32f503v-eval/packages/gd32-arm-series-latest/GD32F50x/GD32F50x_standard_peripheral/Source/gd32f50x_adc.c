/*!
    \file    gd32f50x_adc.c
    \brief   ADC driver

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

#include "gd32f50x_adc.h"

/* discontinuous mode macro*/
#define ADC_CHANNEL_LENGTH_SUBTRACT_ONE            ((uint8_t)0x01U)

/* ADC routine channel macro */
#define ADC_ROUTINE_CHANNEL_RANK_SIX               ((uint8_t)0x06U)
#define ADC_ROUTINE_CHANNEL_RANK_TWELVE            ((uint8_t)0x0CU)
#define ADC_ROUTINE_CHANNEL_RANK_LENGTH            ((uint8_t)0x05U)

/* ADC sampling time macro */
#define ADC_CHANNEL_SAMPLE_TEN                     ((uint8_t)0x0AU)
#define ADC_CHANNEL_SAMPLE_LENGTH                  ((uint8_t)0x03U)

/* ADC inserted channel macro */
#define ADC_INSERTED_CHANNEL_RANK_LENGTH           ((uint8_t)0x05U)
#define ADC_INSERTED_CHANNEL_SHIFT_OFFSET          ((uint8_t)0x0FU)

/* ADC inserted channel offset macro */
#define ADC_OFFSET_LENGTH                          ((uint8_t)0x03U)
#define ADC_OFFSET_SHIFT_LENGTH                    ((uint8_t)0x04U)

/* ADC routine sequence length */
#define ROUTINE_LENGTH_HIGH_VALUE                  ((uint32_t)0x00000010U)

/* external trigger mode macro */
#define ROUTINE_TRIGGER_MODE                       ((uint8_t)18U)
#define INSERTED_TRIGGER_MODE                      ((uint8_t)13U)

#define ADC_CHANNEL_INTERNAL_MASK                  (ADC_CHANNEL_INTERNAL_TEMPSENSOR | ADC_CHANNEL_INTERNAL_VREFINT)
#define ADC_FLAG_MASK                              ((uint32_t)0x0000001FU)
#define ADC_INT_MASK                               ((uint32_t)0x000000E0U)
#define ADC_INT_FLAG_MASK                          ((uint32_t)0x00000007U)
#define ADC_LATCH_DATA_MASK                        (ADC_LATCH_DATA_3)

/*!
    \brief      reset ADC (API_ID(0x0001U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_deinit(uint32_t adc_periph)
{
    switch(adc_periph){
    case ADC0:
        rcu_periph_reset_enable(RCU_ADC0RST);
        rcu_periph_reset_disable(RCU_ADC0RST);
        break;
    case ADC1:
        rcu_periph_reset_enable(RCU_ADC1RST);
        rcu_periph_reset_disable(RCU_ADC1RST);
        break;
    case ADC2:
        rcu_periph_reset_enable(RCU_ADC2RST);
        rcu_periph_reset_disable(RCU_ADC2RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable ADC interface (API_ID(0x0002U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_enable(uint32_t adc_periph)
{
    if(RESET == (ADC_CTL1(adc_periph) & ADC_CTL1_ADCON)){
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_ADCON;
    }       
}

/*!
    \brief      disable ADC interface (API_ID(0x0003U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_disable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ADCON);
}

/*!
    \brief      enable DMA request  (API_ID(0x0004U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[out] none
    \retval     none
*/
void adc_dma_mode_enable(uint32_t adc_periph, uint8_t adc_sequence)
{
    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* DMA request enable for routine channel */
            ADC_CTL1(adc_periph) |= (uint32_t)(ADC_CTL1_RDMA);
        break;
    case ADC_INSERTED_CHANNEL:
        /* DMA request enable for inserted channel */
            ADC_CTL1(adc_periph) |= (uint32_t)(ADC_CTL1_IDMA);
        break;
    default:
        break;
    }
}

/*!
    \brief      disable DMA request (API_ID(0x0005U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[out] none
    \retval     none
*/
void adc_dma_mode_disable(uint32_t adc_periph, uint8_t adc_sequence)
{
    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* DMA request disable for routine channel */
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_RDMA);
        break;
    case ADC_INSERTED_CHANNEL:
        /* DMA request disable for inserted channel */
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_IDMA);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure ADC discontinuous mode (API_ID(0x0006U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
      \arg        ADC_CHANNEL_DISCON_DISABLE: disable discontinuous mode of routine and inserted sequence
    \param[in]  length: number of conversions in discontinuous mode,the number can be 1..8
                        for routine sequence, the number has no effect for inserted sequence
    \param[out] none
    \retval     none
*/
void adc_discontinuous_mode_config(uint32_t adc_periph, uint8_t adc_sequence, uint8_t length)
{
    /* disable discontinuous mode of routine & inserted sequence */
    ADC_CTL0(adc_periph) &= ~((uint32_t)(ADC_CTL0_DISRC | ADC_CTL0_DISIC));
    switch(adc_sequence) {
    case ADC_ROUTINE_CHANNEL:
        /* configure the number of conversions in discontinuous mode */
        ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_DISNUM);
        if((length <= 8U) && (length >= 1U)) {
            ADC_CTL0(adc_periph) |= CTL0_DISNUM(((uint32_t)length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
        }
        /* enable routine sequence discontinuous mode */
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_DISRC;
        break;
    case ADC_INSERTED_CHANNEL:
        /* enable inserted sequence discontinuous mode */
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_DISIC;
        break;
    case ADC_CHANNEL_DISCON_DISABLE:
        /* disable discontinuous mode of routine & inserted sequence */
    default:
        break;
    }
}

/*!
    \brief      enable or disable ADC special function (API_ID(0x0007U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  function: the function to configure
                one or more parameters can be selected which is shown as below:
      \arg        ADC_SCAN_MODE: scan mode select
      \arg        ADC_INSERTED_CHANNEL_AUTO: inserted sequence convert automatically
      \arg        ADC_CONTINUOUS_MODE: continuous mode select
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_special_function_config(uint32_t adc_periph, uint32_t function, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        /* enable ADC scan mode */
        if(0U != (function & ADC_SCAN_MODE)) {
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_SCAN_MODE;
        }
        /* enable ADC inserted sequence convert automatically */
        if(0U != (function & ADC_INSERTED_CHANNEL_AUTO)) {
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_INSERTED_CHANNEL_AUTO;
        }
        /* enable ADC continuous mode */
        if(0U != (function & ADC_CONTINUOUS_MODE)) {
            ADC_CTL1(adc_periph) |= (uint32_t)ADC_CONTINUOUS_MODE;
        }
    } else {
        /* disable ADC scan mode */
        if(0U != (function & ADC_SCAN_MODE)) {
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_SCAN_MODE);
        }
        /* disable ADC inserted sequence convert automatically */
        if(0U != (function & ADC_INSERTED_CHANNEL_AUTO)) {
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_INSERTED_CHANNEL_AUTO);
        }
        /* disable ADC continuous mode */
        if(0U != (function & ADC_CONTINUOUS_MODE)) {
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CONTINUOUS_MODE);
        }
    }
}

/*!
    \brief      enable or disable ADC internal channels (API_ID(0x0008U))
    \param[in]  internal_channel: the internal channels
                one or more parameters can be selected which is shown as below:
      \arg        ADC_CHANNEL_INTERNAL_TEMPSENSOR: temperature sensor channel
      \arg        ADC_CHANNEL_INTERNAL_VREFINT: vrefint channel
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_internal_channel_config(uint32_t internal_channel, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        ADC_CTL1(ADC0) |= (uint32_t)(internal_channel & ADC_CHANNEL_INTERNAL_MASK);
    } else {
        ADC_CTL1(ADC0) &= ~((uint32_t)(internal_channel & ADC_CHANNEL_INTERNAL_MASK));
    }
}

/*!
    \brief    configure the ADC sync mode (API_ID(0x0009U))
    \param[in]  sync_mode: ADC sync mode 
                only one parameter can be selected which is shown as below:
      \arg        ADC_MODE_FREE :free mode
      \arg        ADC_DAUL_ROUTINE_PARALLEL_INSERTED_PARALLEL: ADC0 and ADC1 work in combined routine parallel + inserted parallel mode
      \arg        ADC_DAUL_ROUTINE_PARALLEL_INSERTED_ROTATION: ADC0 and ADC1 work in  combined routine parallel + inserted trigger rotation mode
      \arg        ADC_DAUL_INSERTED_PARALLEL_ROUTINE_FOLLOWUP_FAST: ADC0 and ADC1 work in combined inserted parallel + routine follow-up fast mode
      \arg        ADC_DAUL_INSERTED_PARALLEL_ROUTINE_FOLLOWUP_SLOW: ADC0 and ADC1 work in combined inserted parallel + routine follow-up slow mode
      \arg        ADC_DAUL_INSERTED_PARALLEL: ADC0 and ADC1 work in inserted parallel mode
      \arg        ADC_DAUL_ROUTINE_PARALLEL: ADC0 and ADC1 work in routine parallel mode
      \arg        ADC_DAUL_ROUTINE_FOLLOWUP_FAST: ADC0 and ADC1 work in routine follow-up fast mode
      \arg        ADC_DAUL_ROUTINE_FOLLOWUP_SLOW: ADC0 and ADC1 work in routine follow-up slow mode
      \arg        ADC_DAUL_INSERTED_TRIGGER_ROTATION: ADC0 and ADC1 work in inserted trigger rotation mode
    \param[out] none
    \retval     none
*/
void adc_sync_mode_config(uint32_t sync_mode)
{
    ADC_CTL0(ADC0) &= ~((uint32_t)ADC_CTL0_SYNCM);
    ADC_CTL0(ADC0) |= (uint32_t)(sync_mode & ADC_CTL0_SYNCM);
}

/*!
    \brief      read ADC0 and ADC1 routine sequence data in sync mode(API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     the conversion value
*/
uint32_t adc_sync_routine_data_read(void)
{
    /* return conversion value */
    return ADC_RDATA(ADC0);
}

/*!
    \brief      configure ADC data alignment (API_ID(0x000BU))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  data_alignment: data alignment select
                only one parameter can be selected which is shown as below:
      \arg        ADC_DATAALIGN_RIGHT: right alignment
      \arg        ADC_DATAALIGN_LEFT: left alignment
    \param[out] none
    \retval     none
*/
void adc_data_alignment_config(uint32_t adc_periph , uint32_t data_alignment)
{
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_DAL);
    ADC_CTL1(adc_periph) |= (uint32_t)(data_alignment & ADC_CTL1_DAL);
}

/*!
    \brief      configure the channel length of routine sequence or inserted sequence (API_ID(0x000CU))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[in]  length: the channel length of the sequence
                        routine sequence: 1-16
                        inserted sequence 1-4
    \param[out] none
    \retval     none
*/
void adc_channel_length_config(uint32_t adc_periph, uint8_t adc_sequence, uint32_t length)
{
    switch(adc_sequence) {
    case ADC_ROUTINE_CHANNEL:
        /* configure the length of routine sequence */
        if((length >= 1U) && (length <= ROUTINE_LENGTH_HIGH_VALUE)) {
            ADC_RSQ0(adc_periph) &= ~((uint32_t)ADC_RSQ0_RL);
            ADC_RSQ0(adc_periph) |= RSQ0_RL((uint32_t)(length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
        }
        break;
    case ADC_INSERTED_CHANNEL:
        /* configure the length of inserted sequence */
        if((length >= 1U) && (length <= 4U)) {
            ADC_ISQ(adc_periph) &= ~((uint32_t)ADC_ISQ_IL);
            ADC_ISQ(adc_periph) |= ISQ_IL((uint32_t)(length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      configure ADC routine channel (API_ID(0x000DU))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  rank: the routine sequence rank, this parameter must be between 0 to 15
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x: x=0..17 for ADC0, x=0..17 for ADC1, x=0..16 for ADC2 
    \param[in]  sample_time: the sample time value
                only one parameter can be selected which is shown as below:
      \arg        ADC_SAMPLETIME_1POINT5: 1.5 cycles
      \arg        ADC_SAMPLETIME_7POINT5: 7.5 cycles
      \arg        ADC_SAMPLETIME_13POINT5: 13.5 cycles
      \arg        ADC_SAMPLETIME_28POINT5: 28.5 cycles
      \arg        ADC_SAMPLETIME_41POINT5: 41.5 cycles
      \arg        ADC_SAMPLETIME_55POINT5: 55.5 cycles
      \arg        ADC_SAMPLETIME_71POINT5: 71.5 cycles
      \arg        ADC_SAMPLETIME_239POINT5: 239.5 cycles
    \param[out] none
    \retval     none
*/
void adc_routine_channel_config(uint32_t adc_periph, uint8_t rank, uint8_t adc_channel, uint32_t sample_time)
{
    uint32_t rsq, sampt;

    /* configure ADC routine sequence */
    if(rank < ADC_ROUTINE_CHANNEL_RANK_SIX) {
        /* the routine sequence rank is smaller than six */
        rsq = ADC_RSQ2(adc_periph);
        rsq &=  ~((uint32_t)(ADC_RSQX_RSQN << (ADC_ROUTINE_CHANNEL_RANK_LENGTH * rank)));
        /* the channel number is written to these bits to select a channel as the nth conversion in the routine sequence */
        rsq |= ((uint32_t)(adc_channel & ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_RANK_LENGTH * rank));
        ADC_RSQ2(adc_periph) = rsq;
    } else if(rank < ADC_ROUTINE_CHANNEL_RANK_TWELVE) {
        /* the routine sequence rank is smaller than twelve */
        rsq = ADC_RSQ1(adc_periph);
        rsq &= ~((uint32_t)(ADC_RSQX_RSQN << (ADC_ROUTINE_CHANNEL_RANK_LENGTH * (rank - ADC_ROUTINE_CHANNEL_RANK_SIX))));
        /* the channel number is written to these bits to select a channel as the nth conversion in the routine sequence */
        rsq |= ((uint32_t)(adc_channel & ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_RANK_LENGTH * (rank - ADC_ROUTINE_CHANNEL_RANK_SIX)));
        ADC_RSQ1(adc_periph) = rsq;
    } else {
        /* the routine sequence rank is larger than twelve */
        rsq = ADC_RSQ0(adc_periph);
        rsq &= ~((uint32_t)(ADC_RSQX_RSQN << (ADC_ROUTINE_CHANNEL_RANK_LENGTH * (rank - ADC_ROUTINE_CHANNEL_RANK_TWELVE))));
        /* the channel number is written to these bits to select a channel as the nth conversion in the routine sequence */
        rsq |= ((uint32_t)(adc_channel & ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_RANK_LENGTH * (rank - ADC_ROUTINE_CHANNEL_RANK_TWELVE)));
        ADC_RSQ0(adc_periph) = rsq;
    }

    /* configure ADC sampling time */
    if(adc_channel < ADC_CHANNEL_SAMPLE_TEN) {
        /* the adc channel is smaller than ten */
        sampt = ADC_SAMPT1(adc_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_CHANNEL_SAMPLE_LENGTH * adc_channel)));
        /* channel sample time set*/
        sampt |= (uint32_t)((sample_time & ADC_SAMPTX_SPTN) << (ADC_CHANNEL_SAMPLE_LENGTH * adc_channel));
        ADC_SAMPT1(adc_periph) = sampt;
    } else {
        /* the adc channel is larger than ten */
        sampt = ADC_SAMPT0(adc_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_CHANNEL_SAMPLE_LENGTH * (adc_channel - ADC_CHANNEL_SAMPLE_TEN))));
        /* channel sample time set*/
        sampt |= (uint32_t)((sample_time & ADC_SAMPTX_SPTN) << (ADC_CHANNEL_SAMPLE_LENGTH * (adc_channel - ADC_CHANNEL_SAMPLE_TEN)));
        ADC_SAMPT0(adc_periph) = sampt;
    }
}

/*!
    \brief      configure ADC inserted channel (API_ID(0x000EU))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  rank: the inserted sequencer rank,this parameter must be between 0 to 3
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x: x=0..17 for ADC0, x=0..17 for ADC1, x=0..16 for ADC2 
    \param[in]  sample_time: the sample time value
                only one parameter can be selected which is shown as below:
      \arg        ADC_SAMPLETIME_1POINT5: 1.5 cycles
      \arg        ADC_SAMPLETIME_7POINT5: 7.5 cycles
      \arg        ADC_SAMPLETIME_13POINT5: 13.5 cycles
      \arg        ADC_SAMPLETIME_28POINT5: 28.5 cycles
      \arg        ADC_SAMPLETIME_41POINT5: 41.5 cycles
      \arg        ADC_SAMPLETIME_55POINT5: 55.5 cycles
      \arg        ADC_SAMPLETIME_71POINT5: 71.5 cycles
      \arg        ADC_SAMPLETIME_239POINT5: 239.5 cycles
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_config(uint32_t adc_periph, uint8_t rank, uint8_t adc_channel, uint32_t sample_time)
{
    uint8_t inserted_length;
    uint32_t isq, sampt;

    /* get inserted sequence length */
    inserted_length = (uint8_t)GET_BITS(ADC_ISQ(adc_periph), 20U, 21U);
    /* the channel number is written to these bits to select a channel as the nth conversion in the inserted sequence */
    if(rank < 4U) {
        isq = ADC_ISQ(adc_periph);
        isq &= ~((uint32_t)(ADC_ISQ_ISQN << (ADC_INSERTED_CHANNEL_SHIFT_OFFSET - (inserted_length - rank) * ADC_INSERTED_CHANNEL_RANK_LENGTH)));
        isq |= ((uint32_t)(adc_channel & ADC_ISQ_ISQN) << (ADC_INSERTED_CHANNEL_SHIFT_OFFSET - (inserted_length - rank) * ADC_INSERTED_CHANNEL_RANK_LENGTH));
        ADC_ISQ(adc_periph) = isq;
    }

    /* configure ADC sampling time */
    if(adc_channel < ADC_CHANNEL_SAMPLE_TEN) {
        /* the adc channel is smaller than ten */
        sampt = ADC_SAMPT1(adc_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_CHANNEL_SAMPLE_LENGTH * adc_channel)));
        /* channel sample time set*/
        sampt |= (uint32_t)(sample_time & ADC_SAMPTX_SPTN) << (ADC_CHANNEL_SAMPLE_LENGTH * adc_channel);
        ADC_SAMPT1(adc_periph) = sampt;
    } else {
        /* the adc channel is larger than ten */
        sampt = ADC_SAMPT0(adc_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_CHANNEL_SAMPLE_LENGTH * (adc_channel - ADC_CHANNEL_SAMPLE_TEN))));
        /* channel sample time set*/
        sampt |= ((uint32_t)(sample_time & ADC_SAMPTX_SPTN) << (ADC_CHANNEL_SAMPLE_LENGTH * (adc_channel - ADC_CHANNEL_SAMPLE_TEN)));
        ADC_SAMPT0(adc_periph) = sampt;
    }
}

/*!
    \brief      configure ADC inserted channel offset (API_ID(0x000FU))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  inserted_channel: inserted channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_INSERTED_CHANNEL_0: ADC inserted channel 0
      \arg        ADC_INSERTED_CHANNEL_1: ADC inserted channel 1
      \arg        ADC_INSERTED_CHANNEL_2: ADC inserted channel 2
      \arg        ADC_INSERTED_CHANNEL_3: ADC inserted channel 3
    \param[in]  offset: the offset data
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_offset_config(uint32_t adc_periph , uint8_t inserted_channel , uint16_t offset)
{
    uint8_t inserted_length;
    uint32_t num;

    inserted_length = (uint8_t)GET_BITS(ADC_ISQ(adc_periph), 20U, 21U);
    num = ((uint32_t)ADC_OFFSET_LENGTH - ((uint32_t)inserted_length - (uint32_t)inserted_channel));

    if(num <= ADC_OFFSET_LENGTH) {
        /* calculate the offset of the register */
        num = num * ADC_OFFSET_SHIFT_LENGTH;
        /* configure the offset of the selected channels */
        REG32((adc_periph) + 0x14U + num) = (uint32_t)(offset & ADC_IOFFX_IOFF);
    }
}

/*!
    \brief      enable ADC external trigger(API_ID(0x0010U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[in]  trigger_mode: external trigger mode
                only one parameter can be selected which is shown as below:
      \arg        EXTERNAL_TRIGGER_DISABLE: external trigger disable
      \arg        EXTERNAL_TRIGGER_RISING: rising edge of external trigger
    \param[out] none
    \retval     none
*/
void adc_external_trigger_config(uint32_t adc_periph, uint8_t adc_sequence, uint32_t trigger_mode)
{
    switch(adc_sequence) {
    case ADC_ROUTINE_CHANNEL:
        /* configure ADC routine sequence external trigger mode */
        if(trigger_mode == EXTERNAL_TRIGGER_DISABLE){
            ADC_CTL1(adc_periph) |= (uint32_t)(EXTERNAL_TRIGGER_DISABLE << ROUTINE_TRIGGER_MODE);  
        }else if(trigger_mode == EXTERNAL_TRIGGER_RISING){
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ETMRC);
        }else{
            /* illegal parameters */
        }
        break;
    case ADC_INSERTED_CHANNEL:
        /* configure ADC inserted sequence external trigger mode */
        if(trigger_mode == EXTERNAL_TRIGGER_DISABLE){
            ADC_CTL1(adc_periph) |= (uint32_t)(EXTERNAL_TRIGGER_DISABLE<< INSERTED_TRIGGER_MODE);
        }else if(trigger_mode == EXTERNAL_TRIGGER_RISING){
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ETMIC); 
        }else{
            /* illegal parameters */
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      enable ADC software trigger (API_ID(0x0011U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_sequence: select the sequence
                one or more parameters can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[out] none
    \retval     none
*/
void adc_software_trigger_enable(uint32_t adc_periph, uint8_t adc_sequence)
{
    /* enable routine sequence software trigger */
    if(0U != (adc_sequence & ADC_ROUTINE_CHANNEL)) {
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_SWRCST;
    }
    /* enable inserted sequence software trigger */
    if(0U != (adc_sequence & ADC_INSERTED_CHANNEL)) {
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_SWICST;
    }
}

/*!
    \brief      read ADC routine sequence data register (API_ID(0x0012U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     the conversion value: 0~0x0FFF
*/
uint16_t adc_routine_data_read(uint32_t adc_periph)
{
    return ((uint16_t)(ADC_RDATA(adc_periph)));
}

/*!
    \brief      read ADC inserted sequence data register (API_ID(0x0013U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     the conversion value: 0~0x0FFF
*/
uint16_t adc_inserted_data_read(uint32_t adc_periph)
{
    return (uint16_t)(ADC_IDATA(adc_periph));
}

/*!
    \brief      read ADC latch data register (API_ID(0x0014U))
    \param[in]  adc_periph: ADCx, x=0,1
    \param[in]  latch_data: latch data select
                only one parameter can be selected which is shown as below:
      \arg        ADC_LATCH_DATA_0: ADC latch data 0
      \arg        ADC_LATCH_DATA_1: ADC latch data 1
      \arg        ADC_LATCH_DATA_2: ADC latch data 2
      \arg        ADC_LATCH_DATA_3: ADC latch data 3
    \param[out] none
    \retval     the conversion value
*/
uint16_t adc_latch_data_read(uint32_t adc_periph, uint8_t latch_data)
{
    uint32_t ldata = 0U;
    
    /* read the data of the selected channel */
    switch(latch_data){
        case ADC_LATCH_DATA_0:
            ldata = ADC_LDATA0(adc_periph);
            break;
        case ADC_LATCH_DATA_1:
            ldata = ADC_LDATA1(adc_periph);
            break;
        case ADC_LATCH_DATA_2:
            ldata = ADC_LDATA2(adc_periph);
            break;
        case ADC_LATCH_DATA_3:
            ldata = ADC_LDATA3(adc_periph);
            break;
        default:
            break;
    }
    return (uint16_t)ldata;
}

/*!
    \brief      configure ADC latch data source (API_ID(0x0015U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  latch_data: latch data select
                only one parameter can be selected which is shown as below:
      \arg        ADC_LATCH_DATA_0: ADC latch data 0
      \arg        ADC_LATCH_DATA_1: ADC latch data 1
      \arg        ADC_LATCH_DATA_2: ADC latch data 2
      \arg        ADC_LATCH_DATA_3: ADC latch data 3
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[in]  rank: the routine sequence rank, this parameter must be between 0 to 15 
                      the inserted sequencer rank,this parameter must be between 0 to 3
    \param[out] none
    \retval     none
*/
void adc_latch_data_source_config(uint32_t adc_periph, uint8_t latch_data, uint8_t adc_sequence, uint8_t rank)
{
    uint32_t ldctl;
    ldctl = ADC_LDCTL(adc_periph);
    ldctl &= ~((ADC_LDCTL_COVSELx | ADC_LDCTL_SEQSELx) << (24U - (latch_data & ADC_LATCH_DATA_3)*8U));

    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* ADC latch data source selection for routine channel */
        ldctl |= (ADC_LDCTL_SEQSELx << (24U - (latch_data & ADC_LATCH_DATA_MASK)*8U));
        if(rank < 16U){
            ldctl |= ((uint32_t)rank << (24U - (latch_data & ADC_LATCH_DATA_MASK)*8U));
        }
        break;
    case ADC_INSERTED_CHANNEL:
        /* ADC latch data source selection for inserted channel */
        if(rank < 4U) {
            ldctl |= ((uint32_t)rank << (24U - (latch_data & ADC_LATCH_DATA_MASK)*8U));
        }
        break;
    default:
        break;
    }

    ADC_LDCTL(adc_periph) = ldctl;
}

/*!
    \brief      configure ADC analog watchdog single channel (API_ID(0x0016U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x: x=0..17 for ADC0, x=0..17 for ADC1, x=0..16 for ADC2 
    \param[out] none
    \retval     none
*/
void adc_watchdog0_single_channel_enable(uint32_t adc_periph, uint8_t adc_channel)
{
    ADC_CTL0(adc_periph) &= (uint32_t)~(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC | ADC_CTL0_WD0CHSEL);
    ADC_CTL0(adc_periph) |= (uint32_t)(adc_channel & ADC_CTL0_WD0CHSEL);
    ADC_CTL0(adc_periph) |= (uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC);
}

/*!
    \brief      enable ADC analog watchdog 0 sequence channel (API_ID(0x0017U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: the sequence use analog watchdog
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
      \arg        ADC_ROUTINE_INSERTED_CHANNEL: both routine and inserted sequence
    \param[out] none
    \retval     none
*/
void adc_watchdog0_sequence_channel_enable(uint32_t adc_periph, uint8_t adc_sequence)
{
    ADC_CTL0(adc_periph) &= (uint32_t)~(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC);
    
    /* select the sequence */
    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_RWD0EN;
        break;
    case ADC_INSERTED_CHANNEL:
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_IWD0EN;
        break;
    case ADC_ROUTINE_INSERTED_CHANNEL:
        ADC_CTL0(adc_periph) |= (uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN);
        break;
    default:
        break;
    }
}

/*!
    \brief      disable ADC analog watchdog 0 (API_ID(0x0018U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_watchdog0_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= (uint32_t)~(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC | ADC_CTL0_WD0CHSEL);
}

/*!
    \brief      configure ADC analog watchdog 0 threshold (API_ID(0x0019U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  low_threshold: analog watchdog low threshold, 0..2^20-1
    \param[in]  high_threshold: analog watchdog high threshold, 0..2^20-1
    \param[out] none
    \retval     none
*/
void adc_watchdog0_threshold_config(uint32_t adc_periph, uint32_t low_threshold, uint32_t high_threshold)
{
    ADC_WD0LT(adc_periph) = (uint32_t)WD0LT_WD0LT(low_threshold);
    ADC_WD0HT(adc_periph) = (uint32_t)WD0HT_WD0HT(high_threshold);
}

/*!
    \brief      configure ADC resolution (API_ID(0x001AU))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  resolution: ADC resolution
                only one parameter can be selected which is shown as below:
      \arg        ADC_RESOLUTION_12B: 12-bit ADC resolution
      \arg        ADC_RESOLUTION_10B: 10-bit ADC resolution
      \arg        ADC_RESOLUTION_8B: 8-bit ADC resolution
      \arg        ADC_RESOLUTION_6B: 6-bit ADC resolution
    \param[out] none
    \retval     none
*/
void adc_resolution_config(uint32_t adc_periph , uint32_t resolution)
{
    ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)ADC_OVSAMPCTL_DRES);
    ADC_OVSAMPCTL(adc_periph) |= (uint32_t)(resolution & ADC_OVSAMPCTL_DRES);
}

/*!
    \brief      configure ADC oversample mode (API_ID(0x001BU))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  mode: ADC oversampling mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_OVERSAMPLING_ALL_CONVERT: all oversampled conversions for a channel are done consecutively after a trigger
      \arg        ADC_OVERSAMPLING_ONE_CONVERT: each oversampled conversion for a channel needs a trigger
    \param[in]  shift: ADC oversampling shift
                only one parameter can be selected which is shown as below:
      \arg        ADC_OVERSAMPLING_SHIFT_NONE: no oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_1B: 1-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_2B: 2-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_3B: 3-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_4B: 3-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_5B: 5-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_6B: 6-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_7B: 7-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_8B: 8-bit oversampling shift
    \param[in]  ratio: ADC oversampling ratio
                only one parameter can be selected which is shown as below:
      \arg        ADC_OVERSAMPLING_RATIO_MUL2: oversampling ratio multiple 2
      \arg        ADC_OVERSAMPLING_RATIO_MUL4: oversampling ratio multiple 4
      \arg        ADC_OVERSAMPLING_RATIO_MUL8: oversampling ratio multiple 8
      \arg        ADC_OVERSAMPLING_RATIO_MUL16: oversampling ratio multiple 16
      \arg        ADC_OVERSAMPLING_RATIO_MUL32: oversampling ratio multiple 32
      \arg        ADC_OVERSAMPLING_RATIO_MUL64: oversampling ratio multiple 64
      \arg        ADC_OVERSAMPLING_RATIO_MUL128: oversampling ratio multiple 128
      \arg        ADC_OVERSAMPLING_RATIO_MUL256: oversampling ratio multiple 256
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_config(uint32_t adc_periph, uint32_t mode, uint16_t shift, uint8_t ratio)
{
    /* configure ADC oversampling mode */
    if(ADC_OVERSAMPLING_ONE_CONVERT == mode) {
        ADC_OVSAMPCTL(adc_periph) |= (uint32_t)ADC_OVSAMPCTL_TOVS;
    } else {
        ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)ADC_OVSAMPCTL_TOVS);
    }
    /* configure the shift and ratio */
    ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)(ADC_OVSAMPCTL_OVSR | ADC_OVSAMPCTL_OVSS));
    ADC_OVSAMPCTL(adc_periph) |= ((uint32_t)(shift & ADC_OVSAMPCTL_OVSS) | (uint32_t)(ratio & ADC_OVSAMPCTL_OVSR));
}

/*!
    \brief      enable ADC oversample mode (API_ID(0x001CU))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_enable(uint32_t adc_periph)
{
    ADC_OVSAMPCTL(adc_periph) |= ADC_OVSAMPCTL_OVSEN;
}

/*!
    \brief      disable ADC oversample mode (API_ID(0x001DU))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_disable(uint32_t adc_periph)
{
    ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)ADC_OVSAMPCTL_OVSEN);
}

/*!
    \brief      get ADC flag (API_ID(0x001EU))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  flag: ADC flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_WD0E: analog watchdog 0 event flag
      \arg        ADC_FLAG_EORC: end of routine sequence conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted sequence conversion flag
      \arg        ADC_FLAG_STIC: start of inserted sequence conversion flag
      \arg        ADC_FLAG_STRC: start of routine sequence conversion flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_flag_get(uint32_t adc_periph, uint32_t flag)
{
    FlagStatus reval = RESET;

    if(0U != (ADC_STAT(adc_periph) & flag)) {
        reval = SET;
    }
    return reval;
}

/*!
    \brief      clear ADC flag (API_ID(0x001FU))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  flag: ADC flag
                one or more parameter can be selected which is shown as below:
      \arg        ADC_FLAG_WD0E: analog watchdog 0 event flag
      \arg        ADC_FLAG_EORC: end of routine sequence conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted sequence conversion flag
      \arg        ADC_FLAG_STIC: start of inserted sequence conversion flag
      \arg        ADC_FLAG_STRC: start of routine sequence conversion flag
    \param[out] none
    \retval     none
*/
void adc_flag_clear(uint32_t adc_periph , uint32_t flag)
{
    ADC_STAT(adc_periph) = ~((uint32_t)flag & ADC_FLAG_MASK);
}

/*!
    \brief      enable ADC interrupt (API_ID(0x0020U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  interrupt: ADC interrupt
                one or more parameter can be selected which is shown as below:
      \arg        ADC_INT_WD0E: analog watchdog 0 event interrupt
      \arg        ADC_INT_EORC: end of routine sequence conversion interrupt
      \arg        ADC_INT_EOIC: end of inserted sequence conversion interrupt
    \param[out] none
    \retval     none
*/
void adc_interrupt_enable(uint32_t adc_periph , uint32_t interrupt)
{
    ADC_CTL0(adc_periph) |= (uint32_t) interrupt & ADC_INT_MASK;
}

/*!
    \brief      disable ADC interrupt (API_ID(0x0021U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  interrupt: ADC interrupt
                one or more parameter can be selected which is shown as below:
      \arg        ADC_INT_WD0E: analog watchdog 0 event interrupt
      \arg        ADC_INT_EORC: end of routine sequence conversion interrupt
      \arg        ADC_INT_EOIC: end of inserted sequence conversion interrupt
    \param[out] none
    \retval     none
*/
void adc_interrupt_disable(uint32_t adc_periph, uint32_t interrupt)
{  
    ADC_CTL0(adc_periph) &= ~((uint32_t)interrupt & ADC_INT_MASK);
}

/*!
    \brief      get ADC interrupt flag (API_ID(0x0022U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  int_flag: ADC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_WD0E: analog watchdog 0 event interrupt flag
      \arg        ADC_INT_FLAG_EORC: end of routine sequence conversion interrupt flag
      \arg        ADC_INT_FLAG_EOIC: end of inserted sequence conversion interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph , uint32_t int_flag)
{
    FlagStatus interrupt_flag = RESET;
    uint32_t state;

    /* check the interrupt flags */
    switch(int_flag) {
    case ADC_INT_FLAG_WD0E:
        /* get the ADC analog watchdog 0 interrupt flags */
        state = ADC_STAT(adc_periph) & ADC_STAT_WD0E;
        if((0U != (ADC_CTL0(adc_periph) & ADC_CTL0_WD0EIE)) && (0U != state)) {
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_EORC:
        /* get the ADC end of sequence conversion interrupt flags */
        state = ADC_STAT(adc_periph) & ADC_STAT_EORC;
        if((0U != (ADC_CTL0(adc_periph) & ADC_CTL0_EORCIE)) && (0U != state)) {
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_EOIC:
        /* get the ADC end of inserted sequence conversion interrupt flags */
        state = ADC_STAT(adc_periph) & ADC_STAT_EOIC;
        if((0U != (ADC_CTL0(adc_periph) & ADC_CTL0_EOICIE)) && (0U != state)) {
            interrupt_flag = SET;
        }
        break;
    default:
        break;
    }
    return interrupt_flag;
}

/*!
    \brief      clear the ADC flag (API_ID(0x0023U))
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  int_flag: ADC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_WD0E: analog watchdog 0 event interrupt flag
      \arg        ADC_INT_FLAG_EORC: end of routine sequence conversion interrupt flag
      \arg        ADC_INT_FLAG_EOIC: end of inserted sequence conversion interrupt flag
    \param[out] none
    \retval     none
*/
void adc_interrupt_flag_clear(uint32_t adc_periph , uint32_t int_flag)
{
    ADC_STAT(adc_periph) = ~((uint32_t)int_flag & ADC_INT_FLAG_MASK);
}
