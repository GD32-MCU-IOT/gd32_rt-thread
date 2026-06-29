/*!
    \file    gd32w51x_f5hc_sqpi.c
    \brief   SQPI driver
    
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

#include "gd32w51x_f5hc_sqpi.h"

/*!
    \brief      reset SQPI (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sqpi_deinit(void)
{
    rcu_periph_reset_enable(RCU_SQPIRST);
    rcu_periph_reset_disable(RCU_SQPIRST);
}

/*!
    \brief      initialize the parameters of SQPI struct with the default values (API_ID(0x0002U))
    \param[in]  sqpi_struct: SQPI parameter struct
    \param[out] none
    \retval     none
*/
void sqpi_struct_para_init(sqpi_parameter_struct* sqpi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(sqpi_struct)) {
        fw_debug_report_err(SQPI_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the SQPI struct with the default values */
        sqpi_struct->polarity = SQPI_SAMPLE_POLARITY_RISING;
        sqpi_struct->id_length = SQPI_ID_LENGTH_64_BITS;
        sqpi_struct->addr_bit = 24U;
        sqpi_struct->clk_div = 2U;
        sqpi_struct->cmd_bit = SQPI_CMDBIT_8_BITS;
    }
}

/*!
    \brief      initialize SQPI parameter (API_ID(0x0003U))
    \param[in]  sqpi_struct: SQPI parameter initialization struct members of the structure 
                            and the member values are shown as below:
                  polarity: SQPI_SAMPLE_POLARITY_RISING, SQPI_SAMPLE_POLARITY_FALLING
                  id_length: SQPI_ID_LENGTH_n_BITS (n=8,16,32,64)
                  addr_bit: 0x00 - 0x1F
                  clk_div: 0x02 - 0x40
                  cmd_bit: SQPI_CMDBIT_n_BITS (n=4,8,16)
    \param[out] none
    \retval     none
*/
void sqpi_init(sqpi_parameter_struct *sqpi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(sqpi_struct)) {
        fw_debug_report_err(SQPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SQPI_INIT = (sqpi_struct->polarity & SQPI_INIT_PL) | 
                    (sqpi_struct->id_length & SQPI_INIT_IDLEN) | 
                    (sqpi_struct->cmd_bit & SQPI_INIT_CMDBIT) | 
                    ((sqpi_struct->addr_bit << 24U) & SQPI_INIT_ADDRBIT) | 
                    (((sqpi_struct->clk_div - 1U) << 18U) & SQPI_INIT_CLKDIV);
    }
}

/*!
    \brief      send SQPI read ID command (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function includes timeout exit scenarios.
                Modify according to the use's actual usage scenarios.
*/
void sqpi_read_id_command(void)
{
    while((SQPI_RCMD & SQPI_RCMD_RID) != RESET){
    }
    
    SQPI_RCMD |=  SQPI_RCMD_RID;
    
    while((SQPI_RCMD & SQPI_RCMD_RID) != RESET){
    }
}

/*!
    \brief      send SQPI special command (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function includes timeout exit scenarios.
                Modify according to the use's actual usage scenarios.
*/
void sqpi_special_command(void)
{
    while((SQPI_WCMD & SQPI_WCMD_SCMD) != RESET){
    }
    
    SQPI_WCMD |=  SQPI_WCMD_SCMD;
    
    while((SQPI_WCMD & SQPI_WCMD_SCMD) != RESET){
    }
}

/*!
    \brief      configure SQPI read command (API_ID(0x0006U))
    \param[in]  rmode: SQPI_MODE_SSQ, SQPI_MODE_SSS, SQPI_MODE_SQQ, SQPI_MODE_QQQ, SQPI_MODE_SSD, SQPI_MODE_SDD
    \param[in]  rwaitcycle: 0x00 - 0x1F
    \param[in]  rcmd: 0x00 - 0xFF
    \param[out] none
    \retval     none
*/
void sqpi_read_command_config(uint32_t rmode, uint32_t rwaitcycle, uint32_t rcmd)
{
    SQPI_RCMD = (rcmd & SQPI_RCMD_RCMD) | ((rwaitcycle << 16U) & SQPI_RCMD_RWAITCYCLE) | (rmode & SQPI_RCMD_RMODE);
}

/*!
    \brief      configure SQPI write command (API_ID(0x0007U))
    \param[in]  wmode: SQPI_MODE_SSQ, SQPI_MODE_SSS, SQPI_MODE_SQQ, SQPI_MODE_QQQ, SQPI_MODE_SSD, SQPI_MODE_SDD
    \param[in]  wwaitcycle: 0x00 - 0x1F
    \param[in]  wcmd: 0x00 - 0xFF
    \param[out] none
    \retval     none
*/
void sqpi_write_command_config(uint32_t wmode, uint32_t wwaitcycle, uint32_t wcmd)
{
    SQPI_WCMD = (wcmd & SQPI_WCMD_WCMD) | ((wwaitcycle << 16U) & SQPI_WCMD_WWAITCYCLE) | (wmode & SQPI_WCMD_WMODE);
}

/*!
    \brief      SQPI receive low ID (API_ID(0x0008U))
    \param[in]  none 
    \param[out] none
    \retval     low ID
*/
uint32_t sqpi_low_id_receive(void)
{
    return SQPI_IDL;
}

/*!
    \brief      SQPI receive high ID (API_ID(0x0009U))
    \param[in]  none 
    \param[out] none
    \retval     high ID
*/
uint32_t sqpi_high_id_receive(void)
{
    return SQPI_IDH;
}
