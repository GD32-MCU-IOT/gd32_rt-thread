/*!
    \file    gd32m53x_tmu.c
    \brief   TMU driver

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


#include "gd32m53x_tmu.h"

#define LOW_HALFWORD_MASK       ((uint32_t)0xFFFF0000U)
#define HIGH_HALFWORD_MASK      ((uint32_t)0x0000FFFFU)
#define TMU_INT_MASK            ((uint32_t)0x20010000U)
#define TMU_INT_OVR_MASK        ((uint32_t)0x60000000U)
#define TMU_INT_END_MASK        ((uint32_t)0x80010000U)

/*!
    \brief      reset the TMU registers (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_deinit(void)
{
    rcu_periph_reset_enable(RCU_TMURST);
    rcu_periph_reset_disable(RCU_TMURST);
}

/*!
    \brief      initialize the parameters of TMU struct with the default values (API_ID(0x0002U))
    \param[in]  init_struct: pointer to init parameter struct
    \param[out] none
    \retval     none
*/
void tmu_struct_para_init(tmu_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(TMU_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the struct with the default values */
        init_struct->mode               = TMU_MODE_COS;
        init_struct->scale              = TMU_SCALING_FACTOR_1;
        init_struct->output_floating    = TMU_OUTPUT_FLOAT_DISABLE;
        init_struct->input_floating     = TMU_INPUT_FLOAT_DISABLE;
        init_struct->dma_read           = TMU_READ_DMA_DISABLE;
        init_struct->dma_write          = TMU_WRITE_DMA_DISABLE;
        init_struct->read_times         = TMU_READ_TIMES_1;
        init_struct->write_times        = TMU_WRITE_TIMES_1;
        init_struct->output_width       = TMU_OUTPUT_WIDTH_32;
        init_struct->input_width        = TMU_INPUT_WIDTH_32;
    }
}

/*!
    \brief      initialize TMU (API_ID(0x0003U))
    \param[in]  init_struct: pointer to init parameter struct
                  mode: TMU_MODE_COS,TMU_MODE_SIN,TMU_MODE_ATAN2,TMU_MODE_MODULUS,TMU_MODE_SQRT
                  scale: TMU_SCALING_FACTOR_x(x=1,2,4,8,16,32,64,128)
                  output_format: TMU_OUTPUT_FIXED_POINT, TMU_OUTPUT_FLOAT_POINT
                  input_format: TMU_INPUT_FIXED_POINT, TMU_INPUT_FLOAT_POINT
                  dma_read: TMU_READ_DMA_DISABLE, TMU_READ_DMA_ENABLE
                  dma_write: TMU_WRITE_DMA_DISABLE, TMU_WRITE_DMA_ENABLE
                  read_times: TMU_READ_TIMES_1, TMU_READ_TIMES_2
                  write_times: TMU_WRITE_TIMES_1, TMU_WRITE_TIMES_2
                  output_width: TMU_OUTPUT_WIDTH_32, TMU_OUTPUT_WIDTH_16
                  input_width: TMU_INPUT_WIDTH_32, TMU_INPUT_WIDTH_16
    \param[out] none
    \retval     none
*/
void tmu_init(tmu_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(TMU_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg = 0x50U;
        reg |= (init_struct->mode & TMU_CS_MODE) | (init_struct->input_width & TMU_CS_IWIDTH) | \
               (init_struct->scale & TMU_CS_FACTOR) | (init_struct->output_floating & TMU_CS_OFLTEN) | \
               (init_struct->input_floating & TMU_CS_IFLTEN) | (init_struct->dma_read & TMU_CS_RDEN) | \
               (init_struct->dma_write & TMU_CS_WDEN) | (init_struct->read_times & TMU_CS_ONUM) | \
               (init_struct->write_times & TMU_CS_INUM) | (init_struct->output_width & TMU_CS_OWIDTH);
        TMU_CS = reg;
    }
}

/*!
    \brief      enable TMU DMA read request (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_dma_read_enable(void)
{
    TMU_CS |= TMU_CS_RDEN;
}

/*!
    \brief      disable TMU DMA read request (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_dma_read_disable(void)
{
    TMU_CS &= ~TMU_CS_RDEN;
}

/*!
    \brief      enable TMU DMA write request (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_dma_write_enable(void)
{
    TMU_CS |= TMU_CS_WDEN;
}

/*!
    \brief      disable TMU DMA write request (API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void tmu_dma_write_disable(void)
{
    TMU_CS &= ~TMU_CS_WDEN;
}

/*!
    \brief      write one data in q1.31 format (API_ID(0x0008U))
    \param[in]  data: the first input data only
    \param[out] none
    \retval     none
*/
void tmu_one_q31_write(uint32_t data)
{
    TMU_IDATA = data;
}

/*!
    \brief      write two data in q1.31 format (API_ID(0x0009U))
    \param[in]  data1: the first input data
    \param[in]  data2: the second input data
    \param[out] none
    \retval     none
*/
void tmu_two_q31_write(uint32_t data1, uint32_t data2)
{
    TMU_IDATA = data1;
    TMU_IDATA = data2;
}

/*!
    \brief      write two data in q1.15 format (API_ID(0x000AU))
    \param[in]  data1: the first input data
    \param[in]  data2: the second input data (this data is meaningless in mode4)
    \param[out] none
    \retval     none
*/
void tmu_two_q15_write(uint16_t data1, uint16_t data2)
{
    TMU_IDATA = ((((uint32_t)data1) & HIGH_HALFWORD_MASK) | (((uint32_t)data2 << 16U) & LOW_HALFWORD_MASK));
}

/*!
    \brief      write one data in floating point format (API_ID(0x000BU))
    \param[in]  data: the input data
    \param[out] none
    \retval     none
*/
void tmu_one_f32_write(float data)
{
    TMU_IDATA = *((uint32_t *)(&data));
}

/*!
    \brief      write two data in floating point format (API_ID(0x000CU))
    \param[in]  data1: the first input data
    \param[in]  data2: the second input data
    \param[out] none
    \retval     none
*/
void tmu_two_f32_write(float data1, float data2)
{
    TMU_IDATA = *((uint32_t *)(&data1));
    TMU_IDATA = *((uint32_t *)(&data2));
}


/*!
    \brief      read one data in q1.31 format (API_ID(0x000DU))
    \param[in]  none
    \param[out] p: pointer to the first output data only
    \retval     none
*/
void tmu_one_q31_read(uint32_t *p)
{
    *p = TMU_ODATA;
}

/*!
    \brief      read two data in q1.31 format (API_ID(0x000EU))
    \param[in]  none
    \param[out] p1: pointer to the first output data
    \param[out] p2: pointer to the second output data
    \retval     none
*/
void tmu_two_q31_read(uint32_t *p1, uint32_t *p2)
{
    *p1 = TMU_ODATA;
    __DSB();
    *p2 = TMU_ODATA;
}

/*!
    \brief      read two data in q1.15 format (API_ID(0x000FU))
    \param[in]  none
    \param[out] p1: pointer to the first output data
    \param[out] p2: pointer to the second output data (this data is meaningless in mode4)
    \retval     none
*/
void tmu_two_q15_read(uint16_t *p1, uint16_t *p2)
{
    uint32_t data;
    data = TMU_ODATA;
    *p1 = (uint16_t)data;
    *p2 = (uint16_t)(data >> 16U);
}

/*!
    \brief      read one data in floating point format (API_ID(0x0010U))
    \param[in]  none
    \param[out] p: pointer to the output data
    \retval     none
*/
void tmu_one_f32_read(float *p)
{
    *p = *((float *)(uint32_t)(&TMU_ODATA));
}

/*!
    \brief      read two data in floating point format (API_ID(0x0011U))
    \param[in]  none
    \param[out] p1: pointer to the first output data
    \param[out] p2: pointer to the second output data
    \retval     none
*/
void tmu_two_f32_read(float *p1, float *p2)
{
    *p1 = *((float *)(uint32_t)(&TMU_ODATA));
    __DSB();
    *p2 = *((float *)(uint32_t)(&TMU_ODATA));
}

/*!
    \brief      get TMU flag (API_ID(0x0012U))
    \param[in]  flag: the TMU flags
                only one parameter can be selected which is shown as below:
      \arg        TMU_FLAG_OVRF: TMU overflow error flag
      \arg        TMU_FLAG_END: end of TMU operation flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus tmu_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

    if(TMU_CS & flag) {
        status = SET;
    } else {
        status = RESET;
    }

    return status;
}

/*!
    \brief      clear TMU flag (API_ID(0x0013U))
    \param[in]  flag: the TMU flags
                only one parameter can be selected which is shown as below:
      \arg        TMU_FLAG_OVRF: TMU overflow flag
    \param[out] none
    \retval     none
*/
void tmu_flag_clear(uint32_t flag)
{
    TMU_CS |= flag & TMU_CS_OVRF;
}

/*!
    \brief      enable TMU interrupt (API_ID(0x0014U))
    \param[in]  interrupt: the TMU interrupt
                one or more parameters can be selected which is shown as below:
      \arg        TMU_INT_OVRF: TMU overflow interrupt
      \arg        TMU_INT_END: TMU request to read TMU_ODATA interrupt
    \param[out] none
    \retval     none
*/
void tmu_interrupt_enable(uint32_t interrupt)
{
    TMU_CS |= (interrupt & TMU_INT_MASK) ;
}

/*!
    \brief      disable TMU interrupt (API_ID(0x0015U))
    \param[in]  interrupt: the TMU interrupt
                one or more parameters can be selected which is shown as below:
      \arg        TMU_INT_OVRF: TMU overflow interrupt
      \arg        TMU_INT_END: TMU request to read TMU_ODATA interrupt
    \param[out] none
    \retval     none
*/
void tmu_interrupt_disable(uint32_t interrupt)
{
    TMU_CS &= ~(interrupt & TMU_INT_MASK);
}

/*!
    \brief      get TMU interrupt flag status (API_ID(0x0016U))
    \param[in]  int_flag: TMU interrupt flag status
                only one parameter can be selected which is shown as below:
      \arg        TMU_INT_FLAG_END: end of TMU operation interrupt flag
      \arg        TMU_INT_FLAG_OVRF: overflow error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus tmu_interrupt_flag_get(uint32_t int_flag)
{
    FlagStatus status = RESET;

    switch(int_flag) {
    /* TMU overflow interrupt */
    case TMU_INT_FLAG_OVRF:
        if(TMU_INT_OVR_MASK == (TMU_CS & TMU_INT_OVR_MASK)) {
            status = SET;
        }
        break;
    /* TMU request to read TMU_ODATA interrupt */
    case TMU_INT_FLAG_END:
        if(TMU_INT_END_MASK == (TMU_CS & TMU_INT_END_MASK)) {
            status = SET;
        }
        break;
    default :
        break;
    }

    return status;
}

/*!
    \brief      clear TMU interrupt flag (API_ID(0x0017U))
    \param[in]  int_flag: TMU interrupt flag
      \arg        TMU_INT_FLAG_OVRF: overflow error interrupt flag
    \param[out] none
    \retval     none
*/
void tmu_interrupt_flag_clear(uint32_t int_flag)
{
    TMU_CS |= int_flag & TMU_CS_OVRF;
}
