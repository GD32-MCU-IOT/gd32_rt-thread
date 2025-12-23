/*!
    \file    gd32g5x3_fft.c
    \brief   FFT driver
    
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

#include "gd32g5x3_fft.h"
#include <stdlib.h>

#define FFT_LOOP_LENGTH_SHIFT (16U)

/*!
    \brief      reset the FFT peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fft_deinit(void)
{
    rcu_periph_reset_enable(RCU_FFTRST);
    rcu_periph_reset_disable(RCU_FFTRST);
}

/*!
    \brief      initialize the parameters of FFT struct with the default values
    \param[in]  none
    \param[out] fft_parameter: init parameter struct
    \retval     none
*/
void fft_struct_para_init(fft_parameter_struct* fft_parameter)
{
    fft_parameter->mode_sel        = FFT_MODE;
    fft_parameter->point_num       = FFT_POINT_32;
    fft_parameter->window_enable   = FFT_WINDOW_DISABLE;
    fft_parameter->downsamp_sel    = FFT_DOWNSAMPLE_1;
    fft_parameter->image_source    = FFT_IM_MEMORY;
    fft_parameter->loopbuf_len     = 0x0U;
    fft_parameter->loopbuf_index   = 0x0U;
    fft_parameter->real_addr       = (uint32_t)NULL;
    fft_parameter->image_addr      = (uint32_t)NULL;
    fft_parameter->window_addr     = (uint32_t)NULL;
    fft_parameter->output_addr     = (uint32_t)NULL;
}

/*!
    \brief      initialize the FFT peripheral for calculation
    \param[in]  fft_parameter: the data needed to initialize FFT
                  mode_sel: FFT_MODE, IFFT_MODE
                  point_num: FFT_POINT_32, FFT_POINT_64, FFT_POINT_128,
                             FFT_POINT_256, FFT_POINT_512, FFT_POINT_1024
                  window_enable: FFT_WINDOW_ENABLE, FFT_WINDOW_DISABLE
                  downsamp_sel: FFT_DOWNSAMPLE_x (x = 1..16)
                  image_source: FFT_IM_MEMORY, FFT_IM_ZERO, FFT_IM_MEMORY_OPPOSITE
                  loopbuf_len: loop buffer length
                  loopbuf_index: loop buffer index value, can not more than loopbuf_len
                  real_addr: FFT real part data start address
                  image_addr: FFT image part data start address
                  window_addr: FFT windown function start address
                  output_addr: FFT output data start address
    \param[out] none
    \retval     none
*/
void fft_init(fft_parameter_struct* fft_parameter)
{
    /* config FFT point number */
    FFT_CSR &= ~FFT_CSR_NUMPT;
    FFT_CSR |= CSR_NUMPT(fft_parameter->point_num);

    /* configure FFT down sample */
    FFT_CSR &= ~FFT_CSR_DOWNSAMP;
    FFT_CSR |= CSR_DOWNSAMP(fft_parameter->downsamp_sel);

    /* configure FFT image source */
    FFT_CSR &= ~FFT_CSR_IMSEL;
    FFT_CSR |= CSR_IMSEL(fft_parameter->image_source);

    /* configure FFT window function */
    if(FFT_WINDOW_ENABLE == fft_parameter->window_enable) {
        FFT_CSR |= FFT_CSR_WINEN;
    } else {
        FFT_CSR &= ~FFT_CSR_WINEN;
    }
    
    FFT_CSR &= ~FFT_CSR_IFFTMODE;
    FFT_CSR |= fft_parameter->mode_sel;

    /* configure FFT loop buffer */
    FFT_LOOPLEN = (((uint32_t)fft_parameter->loopbuf_index << FFT_LOOP_LENGTH_SHIFT) | (uint32_t)fft_parameter->loopbuf_len);

    /* configure real part start address */
    FFT_RESADDR = fft_parameter->real_addr;

    /* configure image part start address */
    FFT_IMSADDR = fft_parameter->image_addr;

    /* configure window function start address */
    FFT_WSADDR = fft_parameter->window_addr;

    /* configure output start address */
    FFT_OSADDR = fft_parameter->output_addr;
}

/*!
    \brief      start FFT calculation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fft_calculation_start(void)
{
    FFT_CSR |= FFT_CSR_FFTEN;
}

/*!
    \brief      stop FFT calculation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fft_calculation_stop(void)
{
    FFT_CSR &= ~FFT_CSR_FFTEN;
}

/*!
    \brief      configure FFT calculation point number
    \param[in]  point_num: point number
                only one parameter can be selected which is shown as below:
      \arg        FFT_POINT_32: FFT point number is 32
      \arg        FFT_POINT_64: FFT point number is 64
      \arg        FFT_POINT_128: FFT point number is 128
      \arg        FFT_POINT_256: FFT point number is 256
      \arg        FFT_POINT_512: FFT point number is 512
      \arg        FFT_POINT_1024: FFT point number is 1024
    \param[out] none
    \retval     none
*/
void fft_point_number_config(uint8_t point_num)
{
    FFT_CSR &= ~FFT_CSR_NUMPT;
    FFT_CSR |= CSR_NUMPT(point_num);
}

/*!
    \brief      configure FFT mode
    \param[in]  mode: calculation mode
                only one parameter can be selected which is shown as below:
      \arg        FFT_MODE: excute FFT operation
      \arg        IFFT_MODE: excute FFT inverse operation
    \param[out] none
    \retval     none
*/
void fft_mode_config(uint32_t mode)
{
    FFT_CSR &= ~FFT_CSR_IFFTMODE;
    FFT_CSR |= mode;
}

/*!
    \brief      enable FFT window function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fft_window_enable(void)
{
    FFT_CSR |= FFT_CSR_WINEN;
}

/*!
    \brief      disable FFT window function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fft_window_disable(void)
{
    FFT_CSR &= ~FFT_CSR_WINEN;
}

/*!
    \brief      configure FFT down sample value
    \param[in]  sample_value: down sample value
                only one parameter can be selected which is shown as below:
      \arg        FFT_DOWNSAMPLE_x, x=1..16
    \param[out] none
    \retval     none
*/
void fft_downsample_config(uint8_t sample_value)
{
    FFT_CSR &= ~FFT_CSR_DOWNSAMP;
    FFT_CSR |= CSR_DOWNSAMP(sample_value);
}

/*!
    \brief      configure FFT image part source
    \param[in]  im_src: image source type
                only one parameter can be selected which is shown as below:
      \arg        FFT_IM_MEMORY: image input is from FFT_IMSADDR
      \arg        FFT_IM_ZERO: image input equal to zero
      \arg        FFT_IM_MEMORY_OPPOSITE: image input is the opposite number of image data from FFT_IMSADDR
    \param[out] none
    \retval     none
*/
void fft_image_source_config(uint8_t im_src)
{
    FFT_CSR &= ~FFT_CSR_IMSEL;
    FFT_CSR |= CSR_IMSEL(im_src);
}

/*!
    \brief      configure real part start address
    \param[in]  addr: real memory address
    \param[out] none
    \retval     none
*/
void fft_real_addr_config(uint32_t addr)
{
    FFT_RESADDR = addr;
}

/*!
    \brief      configure image part start address
    \param[in]  addr: image memory address
    \param[out] none
    \retval     none
*/
void fft_image_addr_config(uint32_t addr)
{
    FFT_IMSADDR = addr;
}

/*!
    \brief      configure window function start address
    \param[in]  addr: window function memory address
    \param[out] none
    \retval     none
*/
void fft_window_addr_config(uint32_t addr)
{
    FFT_WSADDR = addr;
}

/*!
    \brief      configure output start address
    \param[in]  addr: output memory address
    \param[out] none
    \retval     none
*/
void fft_output_addr_config(uint32_t addr)
{
    FFT_OSADDR = addr;
}

/*!
    \brief      configure loop buffer length
    \param[in]  length: loop buffer length
    \param[out] none
    \retval     none
*/
void fft_loop_buffer_length_config(uint16_t length)
{
    FFT_LOOPLEN &= ~FFT_LOOPLEN_LENGTH;
    FFT_LOOPLEN |= length;
}

/*!
    \brief      configure loop buffer index
    \param[in]  index:index value
    \param[out] none
    \retval     none
*/
void fft_loop_buffer_index_config(uint16_t index)
{
    FFT_LOOPLEN &= ~FFT_LOOPLEN_INDEX;
    FFT_LOOPLEN |= ((uint32_t)index << 16U);
}

/*!
    \brief      get FFT flag status
    \param[in]  flag: the flag bits
                only one parameter can be selected which is shown as below:
      \arg        FFT_FLAG_DMABSY: DMA busy flag
      \arg        FFT_FLAG_CCF: FFT calculation completion flag
      \arg        FFT_FLAG_TAEIF: FFT transfer access error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fft_flag_get(uint32_t flag)
{
    if(FFT_CSR & flag) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear FFT flag bit
    \param[in]  flag: FFT interrupt flag status
                only one parameter can be selected which is shown as below:
      \arg        FFT_FLAG_CCF: FFT calculation completion flag
      \arg        FFT_FLAG_TAEIF: FFT transfer access error flag
    \param[out] none
    \retval     none
*/
void fft_flag_clear(uint32_t flag)
{
    FFT_CSR |= (uint32_t)flag;
}

/*!
    \brief      enable FFT interrupt
    \param[in]  fft_interrupt: FFT interrupt
                one or more parameters can be selected which are shown as below:
      \arg        FFT_INT_CCF: FFT calculation completion interrupt
      \arg        FFT_INT_TAEIF: FFT transfer access error interrupt
    \param[out] none
    \retval     none
*/
void fft_interrupt_enable(uint32_t fft_interrupt)
{
    FFT_CSR |= (uint32_t)fft_interrupt;
}

/*!
    \brief      disable FFT interrupt
    \param[in]  fft_interrupt: FFT interrupt
                one or more parameters can be selected which are shown as below:
      \arg        FFT_INT_CCF: FFT calculation completion interrupt
      \arg        FFT_INT_TAEIF: FFT transfer access error interrupt
    \param[out] none
    \retval     none
*/
void fft_interrupt_disable(uint32_t fft_interrupt)
{
    FFT_CSR &= ~((uint32_t)fft_interrupt);
}

/*!
    \brief      get FFT interrupt flag status
    \param[in]  int_flag: FFT interrupt flag 
                only one parameter can be selected which is shown as below:
      \arg        FFT_INT_FLAG_CCF: FFT calculation completion interrupt flag
      \arg        FFT_INT_FLAG_TAEIF: FFT transfer access error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fft_interrupt_flag_get(uint32_t int_flag)
{
    uint32_t reg1, reg2;

    switch(int_flag){
    /* calculation completion interrupt */
    case FFT_INT_FLAG_CCF:
        reg1 = FFT_CSR & FFT_CSR_CCIE;
        reg2 = FFT_CSR & FFT_CSR_CCF; 
        break;
    /* transfer access error interrupt */
    case FFT_INT_FLAG_TAEIF:
        reg1 = FFT_CSR & FFT_CSR_TAEIE;
        reg2 = FFT_CSR & FFT_CSR_TAEIF; 
        break;
    default:
        break;
    }

    /*get FFT interrupt flag status */
    if(reg1 && reg2) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear FFT interrupt flag bit
    \param[in]  int_flag: FFT interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FFT_INT_FLAG_CCF: FFT calculation completion interrupt flag
      \arg        FFT_INT_FLAG_TAEIF: FFT transfer access error interrupt flag
    \param[out] none
    \retval     none
*/
void fft_interrupt_flag_clear(uint32_t int_flag)
{
    FFT_CSR |= (uint32_t)int_flag;
}
