/*!
    \file    gd32m53x_wwdgt.c
    \brief   WWDGT driver

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

#include "gd32m53x_wwdgt.h"

/*!
    \brief      reset the window watchdog timer configuration (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void wwdgt_deinit(void)
{
    rcu_periph_reset_enable(RCU_WWDGTRST);
    rcu_periph_reset_disable(RCU_WWDGTRST);
}

/*!
    \brief      configure the WWDGT counter value (API_ID(0x0002U))
    \param[in]  counter_value: 0x00 - 0x3FFF
    \param[out] none
    \retval     none
*/
void wwdgt_counter_update(uint16_t counter_value)
{
    WWDGT_CTL = (uint32_t)CTL_CNT(counter_value);
}

/*!
    \brief      initialize the parameters of WWDGT configure structure with the default values (API_ID(0x0003U))
    \param[in]  none
    \param[out] cfg_struct: the initialization data needed to initialize the WWDGT configuration
    \retval     none
*/
void wwdgt_struct_para_init(wwdgt_cfg_parameter_struct *cfg_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(cfg_struct)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif
    {
        /* set the WWDGT cfg struct with the default values */
        cfg_struct->counter            = 0x3FFFU;
        cfg_struct->reset_control      = WWDGT_RESET_DISABLE;
        cfg_struct->ewie_control       = WWDGT_EWIE_DISABLE;
        cfg_struct->window             = 0x3FFFU;
        cfg_struct->window_end_position = WWDGT_CFG_WEPS_ZERO;
        cfg_struct->prescaler          = WWDGT_CFG_PSC_DIV1;
    }
}

/*!
    \brief      initialize WWDGT configuration and start counter (API_ID(0x0004U))
    \param[in]  cfg_struct: the data needed to initialize WWDGT
                  counter: watchdog timer counter value(0x00 - 0x3FFF)
                  reset_control: WWDGT reset control bit
                    only one parameter can be selected which is shown as below:
                    WWDGT_RESET_DISABLE: wwdgt reset condition does not produce a reset
                    WWDGT_RESET_ENABLE: wwdgt reset condition produce a reset
                  ewie_control: WWDGT early wakeup interrupt control bit
                    only one parameter can be selected which is shown as below:
                    WWDGT_EWIE_DISABLE: disable wwdgt early wakeup interrupt
                    WWDGT_EWIE_ENABLE: enable wwdgt early wakeup interrupt
                  window: window start value(0x0000 - 0x3FFF)
                  window_end_position: WWDGT counter window end position value
                    only one parameter can be selected which is shown as below:
                    WWDGT_CFG_WEPS_THREE_QUARTER: the window end position of WWDGT = (3/4)*0x3FFF
                    WWDGT_CFG_WEPS_HALF: the window end position of WWDGT = (1/2)*0x3FFF
                    WWDGT_CFG_WEPS_QUARTER: the window end position of WWDGT = (1/4)*0x3FFF
                    WWDGT_CFG_WEPS_ZERO:  the window end position of WWDGT = 0
                  prescaler: WWDGT prescaler value
                    only one parameter can be selected which is shown as below:
                    WWDGT_CFG_PSC_DIV1: the time base of window watchdog counter = (PCLK1/4096)/1
                    WWDGT_CFG_PSC_DIV2: the time base of window watchdog counter = (PCLK1/4096)/2
                    WWDGT_CFG_PSC_DIV4: the time base of window watchdog counter = (PCLK1/4096)/4
                    WWDGT_CFG_PSC_DIV8: the time base of window watchdog counter = (PCLK1/4096)/8
    \param[out] none
    \retval     none
*/
void wwdgt_cfg_init(wwdgt_cfg_parameter_struct *cfg_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(cfg_struct)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0004U), ERR_PARAM_POINTER);
    } else
#endif
    {
        WWDGT_CFG = ((uint32_t)(cfg_struct->reset_control & WWDGT_CFG_WDGTEN) | \
                     (uint32_t)(cfg_struct->ewie_control & WWDGT_CFG_EWIE) | \
                     (uint32_t)CFG_WIN(cfg_struct->window) | \
                     (uint32_t)(cfg_struct->window_end_position & WWDGT_CFG_WEPS) | \
                     (uint32_t)(cfg_struct->prescaler & WWDGT_CFG_PSC));
        WWDGT_CTL = (uint32_t)(CTL_CNT(cfg_struct->counter));
    }
}

/*!
    \brief      get flag state of WWDGT (API_ID(0x0005U))
    \param[in]  flag: flag to get
                only one parameter can be selected which is shown as below:
      \arg        WWDGT_FLAG_EWIF: early wakeup interrupt flag
      \arg        WWDGT_FLAG_REFEF: refresh error flag
      \arg        WWDGT_FLAG_UNDFF: underflow error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus wwdgt_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;

    if(0U != (WWDGT_STAT & flag)) {
        reval = SET;
    }

    return reval;
}

/*!
    \brief      clear flag state of WWDGT (API_ID(0x0006U))
    \param[in]  flag: flag to get
                only one parameter can be selected which is shown as below:
      \arg        WWDGT_FLAG_EWIF: early wakeup interrupt flag
      \arg        WWDGT_FLAG_REFEF: refresh error flag
      \arg        WWDGT_FLAG_UNDFF: underflow error flag
    \param[out] none
    \retval     none
*/
void wwdgt_flag_clear(uint32_t flag)
{
    WWDGT_STAT &= (~flag);
}
