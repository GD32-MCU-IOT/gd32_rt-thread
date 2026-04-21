/*!
    \file    gd32m53x_svpwm.c
    \brief   SVPWM driver

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

#include "gd32m53x_svpwm.h"

/*!
    \brief      reset the SVPWM (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void svpwm_deinit(void)
{
    rcu_periph_reset_enable(RCU_SVPWMRST);
    rcu_periph_reset_disable(RCU_SVPWMRST);
}

/*!
    \brief      initialize the parameters of SVPWM struct with the default values (API_ID(0x0002U))
    \param[in]  init_struct: pointer to init parameter struct
    \param[out] none
    \retval     none
*/
void svpwm_struct_para_init(svpwm_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(SVPWM_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the struct with the default values */
        init_struct->switch_mode        = SVPWM_SWITCH_MODE0;
        init_struct->working_mode       = SVPWM_MODE_SEVEN_SEGMENT;
        init_struct->period_count       = (uint16_t)0xFFFF;
    }
}

/*!
    \brief      initialize SVPWM (API_ID(0x0003U))
    \param[in]  init_struct: pointer to init parameter struct
                  switch_mode: SVPWM_SWITCH_MODE0,SVPWM_SWITCH_MODE1
                  working_mode: SVPWM_MODE_SEVEN_SEGMENT, SVPWM_MODE_FIVE_SEGMENT
                  period_count: uint16_t period count of SVPWM operation
    \param[out] none
    \retval     none
*/
void svpwm_init(svpwm_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(SVPWM_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg = 0U;
        reg |= ((init_struct->switch_mode & SVPWM_CTL0_SM) | (init_struct->working_mode & SVPWM_CTL0_TYPE));
        SVPWM_CTL0 = reg;
        SVPWM_CAR = (uint32_t)(init_struct->period_count);
    }
}

/*!
    \brief      enable the SVPWM (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void svpwm_enable(void)
{
    SVPWM_CTL0 |= SVPWM_CTL0_CEN;
}

/*!
    \brief      check the SVPWM status flag (API_ID(0x0005U))
    \param[in]  flag: the SVPWM status flag
                only one parameter can be selected which is shown as below:
      \arg        SVPWM_FLAG_OAL: the duty cycle of A-phase is less than 0 overflow flag
      \arg        SVPWM_FLAG_OBL: the duty cycle of B-phase is less than 0 overflow flag
      \arg        SVPWM_FLAG_OCL: the duty cycle of C-phase is less than 0 overflow flag
      \arg        SVPWM_FLAG_OAH: the duty cycle of A-phase is greater than the COUNT overflow flag
      \arg        SVPWM_FLAG_OBH: the duty cycle of B-phase is greater than the COUNT overflow flag
      \arg        SVPWM_FLAG_OCH: the duty cycle of C-phase is greater than the COUNT overflow flag
      \arg        SVPWM_FLAG_OSF: the svpwm operation is executed successfully flag
    \param[out] none
    \retval     none
*/
FlagStatus svpwm_flag_get(uint32_t flag)
{
    FlagStatus svpwm_flag = RESET;
    if(SVPWM_STAT & flag) {
        svpwm_flag = SET;
    } else {
        svpwm_flag = RESET;
    }
    return svpwm_flag;
}

/*!
    \brief      write alpha and beta data in iq format (API_ID(0x0006U))
    \param[in]  alpha: the alpha input data
    \param[in]  beta: the beta input data
    \param[out] none
    \retval     none
*/
void svpwm_alpha_beta_write(float alpha, float beta)
{
    SVPWM_UALPHA = alpha;
    SVPWM_UBETA = beta;
}

/*!
    \brief      read ta, tb, tc data in uint16 format (API_ID(0x0007U))
    \param[in]  none
    \param[out] ta: pointer to the ta output data
    \param[out] tb: pointer to the tb output data
    \param[out] tc: pointer to the tc output data
    \retval     none
*/
void svpwm_ta_tb_tc_read(uint16_t *ta, uint16_t *tb, uint16_t *tc)
{
    *ta = (uint16_t)SVPWM_TA;
    *tb = (uint16_t)SVPWM_TB;
    *tc = (uint16_t)SVPWM_TC;
}

/*!
    \brief      read sector data (API_ID(0x0008U))
    \param[in]  none
    \param[out] sector: the sector output data
    \retval     none
*/
uint8_t svpwm_sector_read(void)
{
    return ((uint8_t)SVPWM_SEC + 1U);
}
