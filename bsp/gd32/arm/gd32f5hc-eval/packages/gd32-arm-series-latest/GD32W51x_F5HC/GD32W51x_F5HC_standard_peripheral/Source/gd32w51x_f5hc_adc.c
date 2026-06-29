/*!
    \file    gd32w51x_f5hc_adc.c
    \brief   ADC driver

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

#include "gd32w51x_f5hc_adc.h"

/* discontinuous mode macro*/
#define  ADC_CHANNEL_LENGTH_SUBTRACT_ONE            ((uint8_t)0x01U)

/* ADC routine channel macro */
#define  ADC_ROUTINE_CHANNEL_RANK_SIX               ((uint8_t)0x06U)
#if defined(GD32F5HC)
#define  ADC_ROUTINE_CHANNEL_RANK_TWELVE            ((uint8_t)0x0CU)
#else
#define  ADC_ROUTINE_CHANNEL_RANK_NINE              ((uint8_t)0x09U)
#endif /* defined(GD32F5HC) */
#define  ADC_ROUTINE_CHANNEL_RANK_LENGTH            ((uint8_t)0x05U)

/* ADC sampling time macro */
#define  ADC_CHANNEL_SAMPLE_TEN                     ((uint8_t)0x0AU)
#if defined(GD32F5HC)
#define  ADC_CHANNEL_SAMPLE_FIFTEEN                 ((uint8_t)0x0FU)
#else
#define  ADC_CHANNEL_SAMPLE_ELEVEN                  ((uint8_t)0x0BU)
#endif /* defined(GD32F5HC) */
#define  ADC_CHANNEL_SAMPLE_LENGTH                  ((uint8_t)0x03U)

/* ADC inserted channel macro */
#define  ADC_INSERTED_CHANNEL_RANK_LENGTH           ((uint8_t)0x05U)
#define  ADC_INSERTED_CHANNEL_SHIFT_OFFSET          ((uint8_t)0x0FU)

/* ADC inserted channel offset macro */
#define  ADC_OFFSET_LENGTH                          ((uint8_t)0x03U)
#define  ADC_OFFSET_SHIFT_LENGTH                    ((uint8_t)0x04U)

/* ADC sequence external trigger mode offset macro */
#define ROUTINE_TRIGGER_MODE_OFFSET                 ((uint32_t)0x0000001CU)
#define INSERTED_TRIGGER_MODE_OFFSET                ((uint32_t)0x00000014U)

/* ADC routine sequence length */
#if defined(GD32F5HC)
#define ROUTINE_LENGTH_HIGH_VALUE                  ((uint32_t)0x0000000CU)
#define ROUTINE_RANK_HIGH_VALUE                    ((uint32_t)0x0000000CU)
#else
#define ROUTINE_LENGTH_HIGH_VALUE                  ((uint32_t)0x00000009U)
#define ROUTINE_RANK_HIGH_VALUE                    ((uint32_t)0x00000009U)
#endif /* defined(GD32F5HC) */

#define ADC_CHANNEL_INTERNAL_MASK                  ((uint32_t)0x01C00000U)
#define ADC_LATCH_DATA_MASK                        ((uint32_t)0x00000003U)
#define ADC_FLAG_MASK                              ((uint32_t)0x0000007FU)
#define ADC_INT_MASK                               ((uint32_t)0x0C0000E0U)
#define ADC_INT_FLAG_MASK                          ((uint32_t)0x00000067U)

/*!
    \brief      reset ADC (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_deinit(void)
{
    rcu_periph_reset_enable(RCU_ADCRST);
    rcu_periph_reset_disable(RCU_ADCRST);
}

/*!
    \brief      configure the ADC clock (API_ID(0x0002U))
    \param[in]  prescaler: configure ADC prescaler ratio
                only one parameter can be selected which is shown as below:
      \arg        ADC_ADCCK_PCLK2_DIV2: PCLK2 div2
      \arg        ADC_ADCCK_PCLK2_DIV4: PCLK2 div4
      \arg        ADC_ADCCK_PCLK2_DIV6: PCLK2 div6
      \arg        ADC_ADCCK_PCLK2_DIV8: PCLK2 div8
      \arg        ADC_ADCCK_HCLK_DIV5: HCLK div5
      \arg        ADC_ADCCK_HCLK_DIV6: HCLK div6
      \arg        ADC_ADCCK_HCLK_DIV10: HCLK div10
      \arg        ADC_ADCCK_HCLK_DIV20: HCLK div20
    \param[out] none
    \retval     none
*/
void adc_clock_config(uint32_t prescaler)
{
    ADC_CCTL &= ~((uint32_t)ADC_CCTL_ADCCK);
    ADC_CCTL |= (uint32_t) prescaler;
}

/*!
    \brief      enable ADC interface (API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_enable(void)
{
    if(RESET == (ADC_CTL1 & ADC_CTL1_ADCON)){
        /* enable ADC */
        ADC_CTL1 |= (uint32_t)ADC_CTL1_ADCON;
    }
}

/*!
    \brief      disable ADC interface (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_disable(void)
{
    /* disable ADC */
    ADC_CTL1 &= ~((uint32_t)ADC_CTL1_ADCON);
}


/*!
    \brief      enable DMA request (API_ID(0x0005U))
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence for GD32F5HCxx devices
    \param[out] none
    \retval     none
*/
void adc_dma_mode_enable(uint8_t adc_sequence)
{
    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* enable routine DMA request */
        ADC_CTL1 |= (uint32_t)(ADC_CTL1_RDMA);
    break;
#if defined(GD32F5HC)
    case ADC_INSERTED_CHANNEL:
        /* disable inserted DMA request*/
        ADC_CTL1 |= (uint32_t)(ADC_CTL1_IDMA);
        break;
#endif /* defined(GD32F5HC) */
    default:
        break;
    }
}




/*!
    \brief      disable DMA request (API_ID(0x0006U))
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence for GD32F5HCxx devices
    \param[out] none
    \retval     none
*/
void adc_dma_mode_disable(uint8_t adc_sequence)
{
    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* disable routine DMA request */
        ADC_CTL1 &= ~((uint32_t)ADC_CTL1_RDMA);
    break;
#if defined(GD32F5HC)
    case ADC_INSERTED_CHANNEL:
        /* disable inserted DMA request*/
        ADC_CTL1 &= ~((uint32_t)ADC_CTL1_IDMA);
        break;
#endif /* defined(GD32F5HC) */
    default:
        break;
    }
}



/*!
    \brief      when DMA=1, the DMA engine issues a request at end of each conversion (API_ID(0x0007U))
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence for GD32F5HCxx devices
    \param[out] none
    \retval     none
*/
void adc_dma_request_after_last_enable(uint8_t adc_sequence)
{
    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* issues a request at end of each routine conversion*/
        ADC_CTL1 |= (uint32_t)(ADC_CTL1_RDDM);
    break;
#if defined(GD32F5HC)
    case ADC_INSERTED_CHANNEL:
        /* issues a request at end of each inserted conversion*/
        ADC_CTL1 |= (uint32_t)(ADC_CTL1_IDDM);
        break;
#endif /* defined(GD32F5HC) */
    default:
        break;
    }
}


/*!
    \brief      the DMA engine is disabled after the end of transfer signal from DMA controller is detected (API_ID(0x0008U))
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence for GD32F5HCxx devices
    \param[out] none
    \retval     none
*/
void adc_dma_request_after_last_disable(uint8_t adc_sequence)
{
    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* disable DMA after the end of routine sequence transfer signal*/
        ADC_CTL1 &= ~((uint32_t)ADC_CTL1_RDDM);
    break;
#if defined(GD32F5HC)
    case ADC_INSERTED_CHANNEL:
        /* disable DMA after the end of inserted sequence transfer signal*/
        ADC_CTL1 &= ~((uint32_t)ADC_CTL1_IDDM);
        break;
#endif /* defined(GD32F5HC) */
    default:
        break;
    }
}

/*!
    \brief      configure end of conversion mode (API_ID(0x0009U))
    \param[in]  end_selection: end of conversion mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_EORC_SET_SEQUENCE: only at the end of a sequence of routine conversions, the EORC bit is set. Overflow detection is disabled unless DMA=1.
      \arg        ADC_EORC_SET_CONVERSION: at the end of each routine conversion, the EORC bit is set. Overflow is detected automatically.
    \param[out] none
    \retval     none
*/
void adc_end_of_conversion_config(uint32_t end_selection)
{
    /* only at the end of a sequence of routine conversions, the EORC bit is set */
    ADC_CTL1 &= ~((uint32_t)ADC_CTL1_EORCM);
    /* at the end of each routine conversion, the EORC bit is set. Overflow is detected automatically */
    ADC_CTL1 |= end_selection & ADC_CTL1_EORCM;
}

/*!
    \brief      enable or disable ADC internal channels (API_ID(0x000AU))
    \param[in]  internal_channel: the internal channels
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INTERNAL_VBAT: VBAT channel
      \arg        ADC_CHANNEL_INTERNAL_VREFINT: vrefint channel for GD32F5HCxx devices
      \arg        ADC_CHANNEL_INTERNAL_TEMPSENSOR: vrefint channel for GD32F5HCxx devices
      \arg        ADC_CHANNEL_INTERNAL_TEMP_VREF: vrefint and temperature sensor channel for GD32W515xx devices
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_internal_channel_config(uint32_t internal_channel, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        ADC_CCTL |= (uint32_t)(internal_channel & ADC_CHANNEL_INTERNAL_MASK);
    } else {
        ADC_CCTL &= ~((uint32_t)(internal_channel & ADC_CHANNEL_INTERNAL_MASK));
    }
}

/*!
    \brief      configure ADC discontinuous mode (API_ID(0x000BU))
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
      \arg        ADC_CHANNEL_DISCON_DISABLE: disable discontinuous mode of routine and inserted channel
    \param[in]  length: number of conversions in discontinuous mode,the number can be 1..8
                        for routine sequence ,the number has no effect for inserted sequence
    \param[out] none
    \retval     none
*/
void adc_discontinuous_mode_config(uint8_t adc_sequence, uint8_t length)
{
    /* disable discontinuous mode of routine & inserted channel */
    ADC_CTL0 &= ~((uint32_t)( ADC_CTL0_DISRC | ADC_CTL0_DISIC ));
    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* configure the number of conversions in discontinuous mode  */
        ADC_CTL0 &= ~((uint32_t)ADC_CTL0_DISNUM);
        if((length <= 8U) && (length >= 1U)){
            ADC_CTL0 |= CTL0_DISNUM(((uint32_t)length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
        }
        /* enable routine sequence discontinuous mode */
        ADC_CTL0 |= (uint32_t)ADC_CTL0_DISRC;
        break;
    case ADC_INSERTED_CHANNEL:
        /* enable inserted sequence discontinuous mode */
        ADC_CTL0 |= (uint32_t)ADC_CTL0_DISIC;
        break;
    case ADC_CHANNEL_DISCON_DISABLE:
        /* disable discontinuous mode of routine & inserted sequence */
    default:
        break;
    }
}

/*!
    \brief      configure ADC special function (API_ID(0x000CU))
    \param[in]  function: the function to configure
                one or more parameters can be selected which is shown as below:
      \arg        ADC_SCAN_MODE: scan mode select
      \arg        ADC_INSERTED_CHANNEL_AUTO: inserted sequence convert automatically
      \arg        ADC_CONTINUOUS_MODE: continuous mode select
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_special_function_config(uint32_t function, ControlStatus newvalue)
{
    if(newvalue){
        if(0U != (function & ADC_SCAN_MODE)){
            /* enable scan mode */
            ADC_CTL0 |= ADC_SCAN_MODE;
        }
        if(0U != (function & ADC_INSERTED_CHANNEL_AUTO)){
            /* enable inserted sequence convert automatically */
            ADC_CTL0 |= ADC_INSERTED_CHANNEL_AUTO;
        } 
        if(0U != (function & ADC_CONTINUOUS_MODE)){
            /* enable continuous mode */
            ADC_CTL1 |= ADC_CONTINUOUS_MODE;
        }        
    }else{
        if(0U != (function & ADC_SCAN_MODE)){
            /* disable scan mode */
            ADC_CTL0 &= ~ADC_SCAN_MODE;
        }
        if(0U != (function & ADC_INSERTED_CHANNEL_AUTO)){
            /* disable inserted sequence convert automatically */
            ADC_CTL0 &= ~ADC_INSERTED_CHANNEL_AUTO;
        } 
        if(0U != (function & ADC_CONTINUOUS_MODE)){
            /* disable continuous mode */
            ADC_CTL1 &= ~ADC_CONTINUOUS_MODE;
        }       
    }
}


/*!
    \brief      configure ADC data alignment (API_ID(0x000DU))
    \param[in]  data_alignment: data alignment select
                only one parameter can be selected which is shown as below:
      \arg        ADC_DATAALIGN_RIGHT: right alignment
      \arg        ADC_DATAALIGN_LEFT: left alignment
    \param[out] none
    \retval     none
*/
void adc_data_alignment_config(uint32_t data_alignment)
{
    ADC_CTL1 &= ~((uint32_t)ADC_CTL1_DAL);
    ADC_CTL1 |= data_alignment & ADC_CTL1_DAL;

}

/*!
    \brief      configure the length of routine sequence or inserted sequence (API_ID(0x000EU))
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[in]  length: the length of the channel
                        routine channel 1-12 for GD32F5HCxx devices
                        routine channel 1-9 for GD32W515xx devices
                        inserted channel 1-4
    \param[out] none
    \retval     none
*/
void adc_channel_length_config(uint8_t adc_sequence, uint32_t length)
{
    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* configure the length of routine sequence */
        if((length >= 1U) && (length <= ROUTINE_LENGTH_HIGH_VALUE)){
            ADC_RSQ0 &= ~((uint32_t)ADC_RSQ0_RL);
            ADC_RSQ0 |= RSQ0_RL((uint32_t)(length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
        }
        break;
    case ADC_INSERTED_CHANNEL:
        /* configure the length of inserted sequence */
        if((length >= 1U) && (length <= 4U)){
            ADC_ISQ &= ~((uint32_t)ADC_ISQ_IL);
            ADC_ISQ |= ISQ_IL((uint32_t)(length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      configure ADC routine channel (API_ID(0x000FU))
    \param[in]  rank: the routine sequence rank, this parameter must be between
                0 to 11 for GD32F5HCxx devices, 0 to 8 for GD32W515xx devices
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x: ADC Channelx,x=0..14 for GD32F5HCxx devices,x=0..11 for GD32W515xx devices
    \param[in]  sample_time: the sample time value
                only one parameter can be selected which is shown as below:
      \arg        ADC_SAMPLETIME_1POINT5: 1.5 cycles
      \arg        ADC_SAMPLETIME_14POINT5: 14.5 cycles
      \arg        ADC_SAMPLETIME_27POINT5: 27.5 cycles
      \arg        ADC_SAMPLETIME_55POINT5: 55.5 cycles
      \arg        ADC_SAMPLETIME_83POINT5: 83.5 cycles
      \arg        ADC_SAMPLETIME_111POINT5: 111.5 cycles
      \arg        ADC_SAMPLETIME_143POINT5: 143.5 cycles
      \arg        ADC_SAMPLETIME_479POINT5: 479.5 cycles
    \param[out] none
    \retval     none
*/
void adc_routine_channel_config(uint8_t rank, uint8_t adc_channel, uint32_t sample_time)
{
    uint32_t rsq,sampt;
    
    /* configure ADC routine sequence */
    if(rank < ADC_ROUTINE_CHANNEL_RANK_SIX){
        /* the routine sequence rank is smaller than six */
        rsq = ADC_RSQ2;
        rsq &=  ~((uint32_t)(ADC_RSQX_RSQN << (ADC_ROUTINE_CHANNEL_RANK_LENGTH * rank)));
        /* the channel number is written to these bits to select a channel as the nth conversion in the routine sequence */
        rsq |= ((uint32_t)(adc_channel & ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_RANK_LENGTH*rank));
        ADC_RSQ2 = rsq;
    }
#if defined(GD32F5HC)
    else if(rank < ADC_ROUTINE_CHANNEL_RANK_TWELVE){
#else
    else if(rank < ADC_ROUTINE_CHANNEL_RANK_NINE){
#endif /* defined(GD32F5HC) */
        /* the routine sequence rank is smaller than nine */
        rsq = ADC_RSQ1;
        rsq &= ~((uint32_t)(ADC_RSQX_RSQN << (ADC_ROUTINE_CHANNEL_RANK_LENGTH * (rank - ADC_ROUTINE_CHANNEL_RANK_SIX))));
        /* the channel number is written to these bits to select a channel as the nth conversion in the routine sequence */
        rsq |= ((uint32_t)(adc_channel & ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_RANK_LENGTH*(rank-ADC_ROUTINE_CHANNEL_RANK_SIX)));
        ADC_RSQ1 = rsq;
    }else{
        /* illegal parameters */
    }
    
    /* configure ADC sampling time */
    if(adc_channel < ADC_CHANNEL_SAMPLE_TEN){
        /* the routine sequence rank is smaller than ten */
        sampt = ADC_SAMPT1;
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_CHANNEL_SAMPLE_LENGTH*adc_channel)));
        /* channel sample time set*/
        sampt |= (uint32_t)((sample_time & ADC_SAMPTX_SPTN) << (ADC_CHANNEL_SAMPLE_LENGTH*adc_channel));
        ADC_SAMPT1 = sampt;
    }
#if defined(GD32F5HC)
    else if(adc_channel <= ADC_CHANNEL_SAMPLE_FIFTEEN){
#else
    else if(adc_channel <= ADC_CHANNEL_SAMPLE_ELEVEN){  
#endif /* defined(GD32F5HC) */
        /* the routine sequence rank is smaller than eleven */
        sampt = ADC_SAMPT0;
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_CHANNEL_SAMPLE_LENGTH*(adc_channel-ADC_CHANNEL_SAMPLE_TEN))));
        /* channel sample time set*/
        sampt |= (uint32_t)((sample_time & ADC_SAMPTX_SPTN) << (ADC_CHANNEL_SAMPLE_LENGTH*(adc_channel-ADC_CHANNEL_SAMPLE_TEN)));
        ADC_SAMPT0 = sampt;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure ADC inserted channel (API_ID(0x0010U))
    \param[in]  rank: the inserted sequencer rank,this parameter must be between 0 to 3
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x: ADC Channelx,x=0..14 for GD32F5HCxx devices,x=0..11 for GD32W515xx devices
    \param[in]  sample_time: The sample time value
                only one parameter can be selected which is shown as below:
      \arg        ADC_SAMPLETIME_1POINT5: 1.5 cycles
      \arg        ADC_SAMPLETIME_14POINT5: 14.5 cycles
      \arg        ADC_SAMPLETIME_27POINT5: 27.5 cycles
      \arg        ADC_SAMPLETIME_55POINT5: 55.5 cycles
      \arg        ADC_SAMPLETIME_83POINT5: 83.5 cycles
      \arg        ADC_SAMPLETIME_111POINT5: 111.5 cycles
      \arg        ADC_SAMPLETIME_143POINT5: 143.5 cycles
      \arg        ADC_SAMPLETIME_479POINT5: 479.5 cycles
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_config(uint8_t rank, uint8_t adc_channel, uint32_t sample_time)
{
    uint8_t inserted_length;
    uint32_t isq,sampt;

    /* get inserted sequence length */
    inserted_length = (uint8_t)GET_BITS(ADC_ISQ, 20U, 21U);
     /* the channel number is written to these bits to select a channel as the nth conversion in the inserted sequence */
    if(rank < 4U){
        isq = ADC_ISQ;
        isq &= ~((uint32_t)(ADC_ISQ_ISQN << (ADC_INSERTED_CHANNEL_SHIFT_OFFSET-(inserted_length-rank)*ADC_INSERTED_CHANNEL_RANK_LENGTH)));
        isq |= ((uint32_t)(adc_channel & ADC_ISQ_ISQN) << (ADC_INSERTED_CHANNEL_SHIFT_OFFSET-(inserted_length-rank)*ADC_INSERTED_CHANNEL_RANK_LENGTH));
        ADC_ISQ = isq;
    }

    /* configure ADC sampling time */
    if(adc_channel < ADC_CHANNEL_SAMPLE_TEN){
        /* the inserted sequence rank is smaller than ten */
        sampt = ADC_SAMPT1;
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_CHANNEL_SAMPLE_LENGTH * adc_channel)));
        /* channel sample time set*/
        sampt |= (uint32_t)(sample_time & ADC_SAMPTX_SPTN) << (ADC_CHANNEL_SAMPLE_LENGTH * adc_channel);
        ADC_SAMPT1 = sampt;
    }
#if defined(GD32F5HC)
    else if(adc_channel <= ADC_CHANNEL_SAMPLE_FIFTEEN){
#else
    else if(adc_channel <= ADC_CHANNEL_SAMPLE_ELEVEN){  
#endif /* defined(GD32F5HC) */
        /* the inserted sequence rank is smaller than eighteen */
        sampt = ADC_SAMPT0;
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_CHANNEL_SAMPLE_LENGTH*(adc_channel - ADC_CHANNEL_SAMPLE_TEN))));
        /* channel sample time set*/
        sampt |= ((uint32_t)(sample_time & ADC_SAMPTX_SPTN) << (ADC_CHANNEL_SAMPLE_LENGTH*(adc_channel - ADC_CHANNEL_SAMPLE_TEN)));
        ADC_SAMPT0 = sampt;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure ADC inserted channel offset (API_ID(0x0011U))
    \param[in]  inserted_channel : inserted channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_INSERTED_CHANNEL_0: ADC inserted channel 0
      \arg        ADC_INSERTED_CHANNEL_1: ADC inserted channel 1
      \arg        ADC_INSERTED_CHANNEL_2: ADC inserted channel 2
      \arg        ADC_INSERTED_CHANNEL_3: ADC inserted channel 3
    \param[in]  offset : the offset data
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_offset_config(uint8_t inserted_channel, uint16_t offset)
{
    uint8_t inserted_length;
    uint32_t num = 0U;

    inserted_length = (uint8_t)GET_BITS(ADC_ISQ, 20U, 21U);
    num = ((uint32_t)ADC_OFFSET_LENGTH - ((uint32_t)inserted_length - (uint32_t)inserted_channel));
    
    if(num <= ADC_OFFSET_LENGTH){
        /* calculate the offset of the register */
        num = num * ADC_OFFSET_SHIFT_LENGTH;
        /* configure the offset of the selected channels */
        REG32((ADC) + 0x14U + num) = IOFFX_IOFF((uint32_t)offset);
    }
}

/*!
    \brief      configure ADC external trigger (API_ID(0x0012U))
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[in]  trigger_mode: external trigger mode
                only one parameter can be selected which is shown as below:
      \arg        EXTERNAL_TRIGGER_DISABLE: external trigger disable
      \arg        EXTERNAL_TRIGGER_RISING: rising edge of external trigger
      \arg        EXTERNAL_TRIGGER_FALLING: falling edge of external trigger
      \arg        EXTERNAL_TRIGGER_RISING_FALLING: rising and falling edge of external trigger
    \param[out] none
    \retval     none
*/
void adc_external_trigger_config(uint8_t adc_sequence, uint32_t trigger_mode)
{
        switch(adc_sequence){
        case ADC_ROUTINE_CHANNEL:
            /* configure ADC routine sequence external trigger mode */
            ADC_CTL1 &= ~((uint32_t)ADC_CTL1_ETMRC);
            ADC_CTL1 |= (uint32_t) ((trigger_mode << ROUTINE_TRIGGER_MODE_OFFSET) & ADC_CTL1_ETMRC);
            break;
        case ADC_INSERTED_CHANNEL:
            /* configure ADC inserted sequence external trigger mode */
            ADC_CTL1 &=  ~((uint32_t)ADC_CTL1_ETMIC);
            ADC_CTL1 |= (uint32_t) ((trigger_mode << INSERTED_TRIGGER_MODE_OFFSET) & ADC_CTL1_ETMIC);
            break;
        default:
            break;
        }
}

/*!
    \brief      configure ADC external trigger source (API_ID(0x0013U))
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[in]  external_trigger_source: routine or inserted sequence trigger source
                for routine channel:
                only one parameter can be selected which is shown as below:
      \arg        ADC_EXTTRIG_ROUTINE_T0_CH0: external trigger TIMER0 CH0 event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T0_CH1: external trigger TIMER0 CH1 event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T0_CH2: external trigger TIMER0 CH2 event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T1_CH1: external trigger TIMER1 CH1 event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T1_CH2: external trigger TIMER1 CH2 event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T1_CH3: external trigger TIMER1 CH3 event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T1_TRGO: external trigger TIMER1 TRGO event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T2_CH0 : external trigger TIMER2 CH0 event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T2_TRGO : external trigger TIMER2 TRGO event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T3_CH3: external trigger TIMER3 CH3 event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T4_CH0: external trigger TIMER4 CH0 event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T4_CH1: external trigger TIMER4 CH1 event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_T4_CH2: external trigger TIMER4 CH2 event select for routine channel 
      \arg        ADC_EXTTRIG_ROUTINE_EXTI_11: external trigger extiline 11 select for routine channel 
                for inserted channel:
                only one parameter can be selected which is shown as below:
      \arg        ADC_EXTTRIG_INSERTED_T0_CH3: TIMER0 CH3 event select for inserted channel
      \arg        ADC_EXTTRIG_INSERTED_T0_TRGO: TIMER0 TRGO event event select for inserted channel
      \arg        ADC_EXTTRIG_INSERTED_T1_CH0: TIMER1 CH0 event select for inserted channel
      \arg        ADC_EXTTRIG_INSERTED_T1_TRGO: TIMER1 TRGO event event select for inserted channel 
      \arg        ADC_EXTTRIG_INSERTED_T2_CH1: TIMER2 CH1 event select for inserted channel
      \arg        ADC_EXTTRIG_INSERTED_T2_CH3: TIMER2 CH3 event select for inserted channel
      \arg        ADC_EXTTRIG_INSERTED_T3_CH0: TIMER3 CH0 event select for inserted channel
      \arg        ADC_EXTTRIG_INSERTED_T3_CH1: TIMER3 CH1 event select for inserted channel
      \arg        ADC_EXTTRIG_INSERTED_T3_CH2: TIMER3 CH2 event select for inserted channel
      \arg        ADC_EXTTRIG_INSERTED_T3_TRGO: TIMER3 TRGO event select for inserted channel
      \arg        ADC_EXTTRIG_INSERTED_T4_CH3: TIMER4 CH3 event select for inserted channel
      \arg        ADC_EXTTRIG_INSERTED_T4_TRGO: TIMER4 TRGO event select for inserted channel
      \arg        ADC_EXTTRIG_INSERTED_EXTI_15: external interrupt line 15 event select for inserted channel
    \param[out] none
    \retval     none
*/
void adc_external_trigger_source_config(uint8_t adc_sequence, uint32_t external_trigger_source)
{   
    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* configure ADC routine sequence external trigger source */
        ADC_CTL1 &= ~((uint32_t)ADC_CTL1_ETSRC);
        ADC_CTL1 |= (uint32_t)((uint32_t)(external_trigger_source) & ADC_CTL1_ETSRC);
        break;
    case ADC_INSERTED_CHANNEL:
        /* configure ADC inserted sequence external trigger source */
        ADC_CTL1 &= ~((uint32_t)ADC_CTL1_ETSIC);
        ADC_CTL1 |= (uint32_t)((uint32_t)(external_trigger_source) &  ADC_CTL1_ETSIC);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable ADC software trigger (API_ID(0x0014U))
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[out] none
    \retval     none
*/
void adc_software_trigger_enable(uint8_t adc_sequence)
{
    /* enable routine sequence software trigger */
    if(0U != (adc_sequence & ADC_ROUTINE_CHANNEL)){
        ADC_CTL1 |= ADC_CTL1_SWRCST;
    }
    /* enable inserted sequence software trigger */
    if(0U != (adc_sequence & ADC_INSERTED_CHANNEL)){
        ADC_CTL1 |= ADC_CTL1_SWICST;
    }
}



/*!
    \brief      read ADC routine sequence data register (API_ID(0x0015U))
    \param[in]  none
    \param[out] none
    \retval     the conversion value: 0~0xFFFF
*/
uint16_t adc_routine_data_read(void)
{
    return ((uint16_t)(ADC_RDATA));
}

#if defined(GD32F5HC)
/*!
    \brief      read ADC inserted sequence data register (API_ID(0x0016U))
    \param[in]  none
    \param[out] none
    \retval     the conversion value: 0~0xFFFF
*/
uint16_t adc_inserted_data_read(void)
{
    return ((uint16_t)(ADC_IDATA));
}
#else
/*!
    \brief      read ADC inserted sequence data register (API_ID(0x0017U))
    \param[in]  inserted_channel : inserted channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_INSERTED_CHANNEL_0: inserted channel0
      \arg        ADC_INSERTED_CHANNEL_1: inserted channel1
      \arg        ADC_INSERTED_CHANNEL_2: inserted channel2
      \arg        ADC_INSERTED_CHANNEL_3: inserted channel3
    \param[out] none
    \retval     the conversion value: 0~0xFFFF
*/
uint16_t adc_inserted_data_read(uint8_t inserted_channel)
{
    uint32_t idata;
    /* read the data of the selected channel */
    switch(inserted_channel){
    case ADC_INSERTED_CHANNEL_0:
        /* read the data of channel 0 */
        idata = ADC_IDATA0;
        break;
    case ADC_INSERTED_CHANNEL_1:
        /* read the data of channel 1 */
        idata = ADC_IDATA1;
        break;
    case ADC_INSERTED_CHANNEL_2:
        /* read the data of channel 2 */
        idata = ADC_IDATA2;
        break;
    case ADC_INSERTED_CHANNEL_3:
        /* read the data of channel 3 */
        idata = ADC_IDATA3;
        break;
    default:
        idata = 0U;
        break;
    }
    return (uint16_t)idata;
}
#endif /* defined(GD32F5HC) */

#if defined(GD32F5HC)
/*!
    \brief      read ADC latch data register (API_ID(0x0018U))
    \param[in]  latch_data: latch data select
                only one parameter can be selected which is shown as below:
      \arg        ADC_LATCH_DATA_0: ADC latch data 0
      \arg        ADC_LATCH_DATA_1: ADC latch data 1
      \arg        ADC_LATCH_DATA_2: ADC latch data 2
      \arg        ADC_LATCH_DATA_3: ADC latch data 3
    \param[out] none
    \retval     the conversion value
*/
uint16_t adc_latch_data_read(uint8_t latch_data)
{
    uint32_t ldata = 0U;
    
    /* read the data of the selected channel */
    switch(latch_data){
        case ADC_LATCH_DATA_0:
            ldata = ADC_LDATA0;
            break;
        case ADC_LATCH_DATA_1:
            ldata = ADC_LDATA1;
            break;
        case ADC_LATCH_DATA_2:
            ldata = ADC_LDATA2;
            break;
        case ADC_LATCH_DATA_3:
            ldata = ADC_LDATA3;
            break;
        default:
            break;
    }
    return (uint16_t)ldata;
}

/*!
    \brief      configure ADC latch data source (API_ID(0x0019U))
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
    \param[in]  rank: the routine sequence rank, this parameter must be between 0 to 11 for GD32F5HCxx devices and between 0 to 9 for for GD32W515xx devices
                      the inserted sequencer rank,this parameter must be between 0 to 3
    \param[out] none
    \retval     none
*/
void adc_latch_data_source_config(uint8_t latch_data, uint8_t adc_sequence, uint8_t rank)
{
    uint32_t ldctl;
    ldctl = ADC_LDCTL;
    ldctl &= ~((ADC_LDCTL_COVSELx | ADC_LDCTL_SEQSELx) << (24U - (latch_data & ADC_LATCH_DATA_MASK)*8U));

    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* ADC latch data source selection for routine channel */
        ldctl |= (ADC_LDCTL_SEQSELx << (24U - (latch_data & ADC_LATCH_DATA_MASK)*8U));
        if(rank < ROUTINE_RANK_HIGH_VALUE) {
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

    ADC_LDCTL = ldctl;
}
#endif /* defined(GD32F5HC) */

/*!
    \brief      enable ADC analog watchdog single channel (API_ID(0x001AU))
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x: ADC Channelx,x=0..14 for GD32F5HCxx devices,x=0..11 for GD32W515xx devices
    \param[out] none
    \retval     none
*/
void adc_watchdog0_single_channel_enable(uint8_t adc_channel)
{
    ADC_CTL0 &= (uint32_t)~(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC | ADC_CTL0_WD0CHSEL);

    ADC_CTL0 |= (uint32_t)adc_channel;
    ADC_CTL0 |= (uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC);
}

/*!
    \brief      configure ADC analog watchdog sequence channel (API_ID(0x001BU))
    \param[in]  adc_sequence: the sequence use analog watchdog
                only one parameter can be selected which is shown as below: 
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
      \arg        ADC_ROUTINE_INSERTED_CHANNEL: both routine and inserted sequence
    \param[out] none
    \retval     none
*/
void adc_watchdog0_sequence_channel_enable(uint8_t adc_sequence)
{
    ADC_CTL0 &= ~((uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC));
    /* select the sequence */
    switch(adc_sequence){
    case ADC_ROUTINE_CHANNEL:
        /* routine channel analog watchdog enable */
        ADC_CTL0 |= (uint32_t) ADC_CTL0_RWD0EN;
        break;
    case ADC_INSERTED_CHANNEL:
        /* inserted channel analog watchdog enable */
        ADC_CTL0 |= (uint32_t) ADC_CTL0_IWD0EN;
        break;
    case ADC_ROUTINE_INSERTED_CHANNEL:
        /* routine and inserted channel analog watchdog enable */
        ADC_CTL0 |= (uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN);
        break;
    default:
        break;
    }
}

/*!
    \brief      disable ADC analog watchdog (API_ID(0x001CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_watchdog0_disable(void)
{
    ADC_CTL0 &= (uint32_t)~(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC | ADC_CTL0_WD0CHSEL);
}

/*!
    \brief      configure ADC analog watchdog threshold (API_ID(0x001DU))
    \param[in]  low_threshold: analog watchdog low threshold,0..2^20-1 for GD32F5HCxx devices,0..2^12-1 for GD32W515xx devices
    \param[in]  high_threshold: analog watchdog high threshold,0..2^20-1 for GD32F5HCxx devices,0..2^12-1 for GD32W515xx devices
    \param[out] none
    \retval     none
*/
void adc_watchdog0_threshold_config(uint32_t low_threshold, uint32_t high_threshold)
{
    /* configure ADC analog watchdog low threshold */
    ADC_WD0LT = (uint32_t)WD0LT_WD0LT(low_threshold);
    /* configure ADC analog watchdog high threshold */
    ADC_WD0HT = (uint32_t)WD0HT_WD0HT(high_threshold);
}

/*!
    \brief      configure ADC oversample mode (API_ID(0x001EU))
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
void adc_oversample_mode_config(uint32_t mode, uint16_t shift, uint8_t ratio)
{
    /* configure ADC oversampling mode */
    if(ADC_OVERSAMPLING_ONE_CONVERT == mode){
        ADC_OVSAMPCTL |= (uint32_t)ADC_OVSAMPCTL_TOVS;
    }else{
        ADC_OVSAMPCTL &= ~((uint32_t)ADC_OVSAMPCTL_TOVS);
    }
    /* configure the shift and ratio */
    ADC_OVSAMPCTL &= ~((uint32_t)(ADC_OVSAMPCTL_OVSR | ADC_OVSAMPCTL_OVSS));
    ADC_OVSAMPCTL |= (((uint32_t)shift & ADC_OVSAMPCTL_OVSS) | ((uint32_t)ratio & ADC_OVSAMPCTL_OVSR));
}

/*!
    \brief      enable ADC oversample mode (API_ID(0x001FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_enable(void)
{
    ADC_OVSAMPCTL |= ADC_OVSAMPCTL_OVSEN;
}

/*!
    \brief      disable ADC oversample mode (API_ID(0x0020U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_disable(void)
{
    ADC_OVSAMPCTL &= ~((uint32_t)ADC_OVSAMPCTL_OVSEN);
}

/*!
    \brief      get the ADC flag (API_ID(0x0021U))
    \param[in]  flag: the ADC flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_WD0E: analog watchdog 0 event flag
      \arg        ADC_FLAG_EOC: end of sequence conversion flag(only for GD32W515xx devices)
      \arg        ADC_FLAG_EORC: end of routine sequence conversion flag(only for GD32F5HCxx devices)
      \arg        ADC_FLAG_EOIC: end of inserted sequence conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted sequence
      \arg        ADC_FLAG_STRC: start flag of routine sequence
      \arg        ADC_FLAG_ROVF: routine data register overflow flag
      \arg        ADC_FLAG_IOVF: inserted data register overflow flag(only for GD32F5HCxx devices)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;
    if(0U != (ADC_STAT & flag)){
        reval = SET;
    }
    return reval;
}

/*!
    \brief      clear the ADC flag (API_ID(0x0022U))
    \param[in]  flag: the ADC flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_WD0E: analog watchdog 0 event flag
      \arg        ADC_FLAG_EOC: end of sequence conversion flag(only for GD32W515xx devices)
      \arg        ADC_FLAG_EORC: end of routine sequence conversion flag(only for GD32F5HCxx devices)
      \arg        ADC_FLAG_EOIC: end of inserted sequence conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted sequence
      \arg        ADC_FLAG_STRC: start flag of routine sequence
      \arg        ADC_FLAG_ROVF: routine data register overflow flag
      \arg        ADC_FLAG_IOVF: inserted data register overflow flag(only for GD32F5HCxx devices)
    \param[out] none
    \retval     none
*/
void adc_flag_clear(uint32_t flag)
{
    ADC_STAT &= ~((uint32_t)flag & ADC_FLAG_MASK);
}

/*!
    \brief      enable ADC interrupt (API_ID(0x0023U))
    \param[in]  interrupt: the ADC interrupt
                one or more parameters can be selected which is shown as below:
      \arg        ADC_INT_WD0E: analog watchdog interrupt 
      \arg        ADC_INT_EOC: end of routine sequence conversion interrupt(only for GD32W515xx devices) 
      \arg        ADC_INT_EORC: end of routine sequence conversion interrupt(only for GD32F5HCxx devices) 
      \arg        ADC_INT_EOIC: end of inserted sequence conversion interrupt 
      \arg        ADC_INT_ROVF: routine data register overflow interrupt 
      \arg        ADC_INT_IOVF: inserted data register overflow interrupt(only for GD32F5HCxx devices)
    \param[out] none
    \retval     none
*/
void adc_interrupt_enable(uint32_t interrupt)
{
     ADC_CTL0 |= (uint32_t) interrupt & ADC_INT_MASK;
}

/*!
    \brief      disable ADC interrupt (API_ID(0x0024U))
    \param[in]  interrupt: the ADC interrupt
                one or more parameters can be selected which is shown as below:
      \arg        ADC_INT_WD0E: analog watchdog interrupt 
      \arg        ADC_INT_EOC: end of routine sequence conversion interrupt(only for GD32W515xx devices)
      \arg        ADC_INT_EORC: end of routine sequence conversion interrupt(only for GD32F5HCxx devices)
      \arg        ADC_INT_EOIC: end of inserted sequence conversion interrupt 
      \arg        ADC_INT_ROVF: routine data register overflow interrupt 
      \arg        ADC_INT_IOVF: inserted data register overflow interrupt(only for GD32F5HCxx devices)
    \param[out] none
    \retval     none
*/
void adc_interrupt_disable(uint32_t interrupt)
{
    ADC_CTL0 &= ~((uint32_t)interrupt & ADC_INT_MASK);  
}

/*!
    \brief      get ADC interrupt flag (API_ID(0x0025U))
    \param[in]  int_flag: the ADC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_WD0E: analog watchdog interrupt flag
      \arg        ADC_INT_FLAG_EOC: end of routine sequence conversion interrupt flag (only for GD32W515xx devices)
      \arg        ADC_INT_FLAG_EORC: end of routine sequence conversion interrupt flag (only for GD32F5HCxx devices)
      \arg        ADC_INT_FLAG_EOIC: end of inserted sequence conversion interrupt flag
      \arg        ADC_INT_FLAG_ROVF: routine data register overflow interrupt flag
      \arg        ADC_INT_FLAG_IOVF: inserted data register overflow interrupt flag (only for GD32F5HCxx devices)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_interrupt_flag_get(uint32_t int_flag)
{
    FlagStatus interrupt_flag = RESET;
    uint32_t state;
    /* check the interrupt bits */
    switch(int_flag){
    case ADC_INT_FLAG_WD0E:
        state = ADC_STAT & ADC_STAT_WD0E;
        if((0U != (ADC_CTL0 & ADC_CTL0_WD0EIE)) && (0U != state)){
          interrupt_flag = SET;
        }
        break;
#if defined(GD32F5HC)
    case ADC_INT_FLAG_EORC:
        state = ADC_STAT & ADC_STAT_EORC;
        if((0U != (ADC_CTL0 & ADC_CTL0_EORCIE)) && (0U != state)){
            interrupt_flag = SET;
          }
        break;
#else
    case ADC_INT_FLAG_EOC:
        state = ADC_STAT & ADC_STAT_EOC;
        if((0U != (ADC_CTL0 & ADC_CTL0_EOCIE)) && (0U != state)){
            interrupt_flag = SET;
          }
        break;
#endif /* defined(GD32F5HC) */
    case ADC_INT_FLAG_EOIC:
        state = ADC_STAT & ADC_STAT_EOIC;
        if((0U != (ADC_CTL0 & ADC_CTL0_EOICIE)) && (0U != state)){
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_ROVF:
        state = ADC_STAT & ADC_STAT_ROVF;
        if((0U != (ADC_CTL0 & ADC_CTL0_ROVFIE)) && (0U != state)){
            interrupt_flag = SET;
        }
        break;
#if defined(GD32F5HC)
    case ADC_INT_FLAG_IOVF:
        state = ADC_STAT & ADC_STAT_IOVF;
        if((0U != (ADC_CTL0 & ADC_CTL0_IOVFIE)) && (0U != state)){
            interrupt_flag = SET;
        }
        break;
#endif /* defined(GD32F5HC) */
    default:
        break;
    }
    return interrupt_flag;
}

/*!
    \brief      clear ADC interrupt flag (API_ID(0x0026U))
    \param[in]  int_flag: the ADC interrupt flag
                one or more parameters can be selected which is shown as below:
      \arg        ADC_INT_FLAG_WD0E: analog watchdog interrupt flag
      \arg        ADC_INT_FLAG_EOC: end of routine sequence conversion interrupt flag (only for GD32W515xx devices)
      \arg        ADC_INT_FLAG_EORC: end of routine sequence conversion interrupt flag (only for GD32F5HCxx devices)
      \arg        ADC_INT_FLAG_EOIC: end of inserted sequence conversion interrupt flag
      \arg        ADC_INT_FLAG_ROVF: routine data register overflow interrupt flag
      \arg        ADC_INT_FLAG_IOVF: inserted data register overflow interrupt flag (only for GD32F5HCxx devices)
    \param[out] none
    \retval     none
*/
void adc_interrupt_flag_clear(uint32_t int_flag)
{
    ADC_STAT &= ~((uint32_t)int_flag & ADC_INT_FLAG_MASK);
}


