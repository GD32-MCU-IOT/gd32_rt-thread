/*!
    \file    gd32f50x_dac.c
    \brief   DAC driver
    
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

#include "gd32f50x_dac.h"

/* DAC register bit offset */
#define OUT1_REG_OFFSET             ((uint32_t)0x00000010U)
#define DH_12BIT_OFFSET             ((uint32_t)0x00000010U)
#define DH_8BIT_OFFSET              ((uint32_t)0x00000008U)

/*!
    \brief      deinitialize DAC (API_ID(0x0001U))
    \param[in]  dac_periph: DACx(x=0)
    \param[out] none
    \retval     none
*/
void dac_deinit(uint32_t dac_periph)
{
    switch(dac_periph){
        case DAC0:
            /* reset DAC0 */
            rcu_periph_reset_enable(RCU_DACRST);
            rcu_periph_reset_disable(RCU_DACRST);
            break;
        default:
            break;
    }
}

/*!
    \brief      enable DAC (API_ID(0x0002U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) |= (uint32_t)DAC_CTL0_DEN0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      disable DAC (API_ID(0x0003U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DEN0);
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      enable DAC DMA function (API_ID(0x0004U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_dma_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) |= (uint32_t)DAC_CTL0_DDMAEN0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      disable DAC DMA function (API_ID(0x0005U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_dma_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DDMAEN0);
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      DAC output pin selection (API_ID(0x0006U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  pin_sel: DAC output pin selection
                only one parameter can be selected which is shown as below:
      \arg        DAC_OUTPUT_CONNECT_PA4: DAC output pin connect PA4
      \arg        DAC_OUTPUT_CONNECT_PA5: DAC output pin connect PA5
    \param[out] none
    \retval     none
*/
void dac_pin_select(uint32_t dac_periph, uint8_t dac_out, uint32_t pin_sel)
{
    if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_OUTSEL0);
        DAC_CTL0(dac_periph) |= (uint32_t)pin_sel & DAC_CTL0_OUTSEL0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      enable DAC output buffer (API_ID(0x0007U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_output_buffer_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DBOFF0);
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      disable DAC output buffer (API_ID(0x0008U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_output_buffer_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) |= (uint32_t)DAC_CTL0_DBOFF0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      get DAC output value (API_ID(0x0009U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     DAC output data: 0~4095
*/
uint16_t dac_output_value_get(uint32_t dac_periph, uint8_t dac_out)
{
    uint16_t data = 0U;

    if(DAC_OUT0 == dac_out){
        /* store the DACx_OUT0 output value */
        data = (uint16_t)DAC_OUT0_DO(dac_periph);
    }else{
        /* illegal parameters */
    }

    return data;
}

/*!
    \brief      set DAC data holding register value (API_ID(0x000AU))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  dac_align: DAC data alignment mode
                only one parameter can be selected which is shown as below:
      \arg        DAC_ALIGN_12B_R: 12-bit right-aligned data
      \arg        DAC_ALIGN_12B_L: 12-bit left-aligned data
      \arg        DAC_ALIGN_8B_R: 8-bit right-aligned data
    \param[in]  data: data to be loaded(0~4095)
    \param[out] none
    \retval     none
*/
void dac_data_set(uint32_t dac_periph, uint8_t dac_out, uint32_t dac_align, uint16_t data)
{
    /* DAC_OUT0 data alignment */
    if(DAC_OUT0 == dac_out){
        switch(dac_align){
        /* 12-bit right-aligned data */
        case DAC_ALIGN_12B_R:
            DAC_OUT0_R12DH(dac_periph) = data;
            break;
        /* 12-bit left-aligned data */
        case DAC_ALIGN_12B_L:
            DAC_OUT0_L12DH(dac_periph) = data;
            break;
        /* 8-bit right-aligned data */
        case DAC_ALIGN_8B_R:
            DAC_OUT0_R8DH(dac_periph) = data;
            break;
        default:
            break;
        }
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      enable DAC trigger (API_ID(0x000BU))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_trigger_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) |= (uint32_t)DAC_CTL0_DTEN0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      disable DAC trigger (API_ID(0x000CU))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_trigger_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DTEN0);
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure DAC trigger source (API_ID(0x000DU))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  triggersource: external trigger of DAC
                only one parameter can be selected which is shown as below:
      \arg        DAC_TRIGGER_EXTERNAL: external trigger selected from TRIGSEL
      \arg        DAC_TRIGGER_SOFTWARE: software trigger
    \param[out] none
    \retval     none
*/
void dac_trigger_source_config(uint32_t dac_periph, uint8_t dac_out, uint32_t triggersource)
{
    if(DAC_OUT0 == dac_out){
        /* configure DACx_OUT0 trigger source */
        DAC_CTL0(dac_periph) &= (uint32_t)(~(DAC_CTL0_DTSEL0));
        DAC_CTL0(dac_periph) |= triggersource & DAC_CTL0_DTSEL0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      enable DAC software trigger (API_ID(0x000EU))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \retval     none
*/
void dac_software_trigger_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_SWT(dac_periph) |= (uint32_t)DAC_SWT_SWTR0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure DAC wave mode (API_ID(0x000FU))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  wave_mode: DAC wave mode
                only one parameter can be selected which is shown as below:
      \arg        DAC_WAVE_DISABLE: wave mode disable
      \arg        DAC_WAVE_MODE_LFSR: LFSR noise mode
      \arg        DAC_WAVE_MODE_TRIANGLE: triangle noise mode
    \param[out] none
    \retval     none
*/
void dac_wave_mode_config(uint32_t dac_periph, uint8_t dac_out, uint32_t wave_mode)
{
    if(DAC_OUT0 == dac_out){
        /* configure DACx_OUT0 wave mode */
        DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DWM0);
        DAC_CTL0(dac_periph) |= wave_mode & DAC_CTL0_DWM0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure DAC LFSR noise mode (API_ID(0x0010U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  unmask_bits: LFSR noise unmask bits
                only one parameter can be selected which is shown as below:
      \arg        DAC_LFSR_BIT0: unmask the LFSR bit0
      \arg        DAC_LFSR_BITS1_0: unmask the LFSR bits[1:0]
      \arg        DAC_LFSR_BITS2_0: unmask the LFSR bits[2:0]
      \arg        DAC_LFSR_BITS3_0: unmask the LFSR bits[3:0]
      \arg        DAC_LFSR_BITS4_0: unmask the LFSR bits[4:0]
      \arg        DAC_LFSR_BITS5_0: unmask the LFSR bits[5:0]
      \arg        DAC_LFSR_BITS6_0: unmask the LFSR bits[6:0]
      \arg        DAC_LFSR_BITS7_0: unmask the LFSR bits[7:0]
      \arg        DAC_LFSR_BITS8_0: unmask the LFSR bits[8:0]
      \arg        DAC_LFSR_BITS9_0: unmask the LFSR bits[9:0]
      \arg        DAC_LFSR_BITS10_0: unmask the LFSR bits[10:0]
      \arg        DAC_LFSR_BITS11_0: unmask the LFSR bits[11:0]
    \param[out] none
    \retval     none
*/
void dac_lfsr_noise_config(uint32_t dac_periph, uint8_t dac_out, uint32_t unmask_bits)
{
    if(DAC_OUT0 == dac_out){
        /* configure DACx_OUT0 LFSR noise mode */
        DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DWBW0);
        DAC_CTL0(dac_periph) |= unmask_bits & DAC_CTL0_DWBW0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure DAC triangle noise mode (API_ID(0x0011U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  amplitude: the amplitude of the triangle
                only one parameter can be selected which is shown as below:
      \arg        DAC_TRIANGLE_AMPLITUDE_1: triangle amplitude is 1
      \arg        DAC_TRIANGLE_AMPLITUDE_3: triangle amplitude is 3
      \arg        DAC_TRIANGLE_AMPLITUDE_7: triangle amplitude is 7
      \arg        DAC_TRIANGLE_AMPLITUDE_15: triangle amplitude is 15
      \arg        DAC_TRIANGLE_AMPLITUDE_31: triangle amplitude is 31
      \arg        DAC_TRIANGLE_AMPLITUDE_63: triangle amplitude is 63
      \arg        DAC_TRIANGLE_AMPLITUDE_127: triangle amplitude is 127
      \arg        DAC_TRIANGLE_AMPLITUDE_255: triangle amplitude is 255
      \arg        DAC_TRIANGLE_AMPLITUDE_511: triangle amplitude is 511
      \arg        DAC_TRIANGLE_AMPLITUDE_1023: triangle amplitude is 1023
      \arg        DAC_TRIANGLE_AMPLITUDE_2047: triangle amplitude is 2047
      \arg        DAC_TRIANGLE_AMPLITUDE_4095: triangle amplitude is 4095
    \param[out] none
    \retval     none
*/
void dac_triangle_noise_config(uint32_t dac_periph, uint8_t dac_out, uint32_t amplitude)
{
    if(DAC_OUT0 == dac_out){
        /* configure DACx_OUT0 triangle noise mode */
        DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DWBW0);
        DAC_CTL0(dac_periph) |= amplitude & DAC_CTL0_DWBW0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      enable DAC output connect to pin (API_ID(0x0012U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_output_connect_to_pin_enable(uint32_t dac_periph, uint8_t dac_out)
{
  if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) &= ~DAC_CTL0_DCSEL0;
        DAC_CTL0(dac_periph) |= DAC_CTL0_DCSEL0;
  }else{
        /* illegal parameters */
  }
}

/*!
    \brief      disable DAC output connect to pin (API_ID(0x0013U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_output_connect_to_pin_disable(uint32_t dac_periph, uint8_t dac_out)
{
  if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) &= ~DAC_CTL0_DCSEL0;
  }else{
        /* illegal parameters */
  }
}

/*!
    \brief      enable DAC interrupt (API_ID(0x0014U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_interrupt_enable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DDUDRIE0);
        DAC_CTL0(dac_periph) |= DAC_CTL0_DDUDRIE0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      disable DAC interrupt (API_ID(0x0015U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_interrupt_disable(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_CTL0(dac_periph) &= ~DAC_CTL0_DDUDRIE0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      get the DAC flag (API_ID(0x0016U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     the state of dac bit(SET or RESET)
*/
FlagStatus dac_flag_get(uint32_t dac_periph, uint8_t dac_out)
{
    FlagStatus status = RESET;
    
    if(DAC_OUT0 == dac_out){
       /* check the DMA underrun flag */
       if((uint8_t)RESET != (DAC_STAT0(dac_periph) & DAC_STAT0_DDUDR0)){
           status = SET;
       }else{
           status = RESET;
       }
    }else{
        /* illegal parameters */
    }
    
    return status;
}

/*!
    \brief      clear the DAC flag (API_ID(0x0017U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_flag_clear(uint32_t dac_periph, uint8_t dac_out)
{
    if(DAC_OUT0 == dac_out){
        DAC_STAT0(dac_periph) |= DAC_STAT0_DDUDR0;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      get the DAC interrupt flag (API_ID(0x0018U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     the state of DAC interrupt flag(SET or RESET)
*/
FlagStatus dac_interrupt_flag_get(uint32_t dac_periph, uint8_t dac_out)
{
    FlagStatus temp_flag = RESET;
    uint32_t ddudr_flag = 0U, ddudrie_flag = 0U;
    /* check the DMA underrun flag and DAC DMA underrun interrupt enable flag */
    if(DAC_OUT0 == dac_out){
        ddudr_flag = DAC_STAT0(dac_periph) & DAC_STAT0_DDUDR0;
        ddudrie_flag = DAC_CTL0(dac_periph) & DAC_CTL0_DDUDRIE0;
    }else{
        /* illegal parameters */
    }
    if((RESET != ddudr_flag) && (RESET != ddudrie_flag)){
        temp_flag = SET;
    }
    return temp_flag;
}

/*!
    \brief      clear the DAC interrupt flag (API_ID(0x0019U))
    \param[in]  dac_periph: DACx(x=0)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_interrupt_flag_clear(uint32_t dac_periph, uint8_t dac_out)
{
  if(DAC_OUT0 == dac_out){
        DAC_STAT0(dac_periph) |= DAC_STAT0_DDUDR0;
  }else{
        /* illegal parameters */
  }
}
