/*!
    \file    gd32m53x_dbg.c
    \brief   DBG driver

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

#include "gd32m53x_dbg.h"

#define DBG_RESET_VAL       ((uint32_t)0x00000000U)   /*!< DBG reset value */
#define DBG_LOWPOWER_MASK   ((uint32_t)0x00000007U)   /*!< DBG low power mask */

/*!
    \brief      deinitialize the DBG (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dbg_deinit(void)
{
    DBG_CTL = DBG_RESET_VAL;
}

/*!
    \brief      read DBG_ID code register (API_ID(0x0002U))
    \param[in]  none
    \param[out] none
    \retval     DBG_ID code
*/
uint32_t dbg_id_get(void)
{
    return DBG_ID;
}

/*!
    \brief      enable low power behavior when the mcu is in debug mode (API_ID(0x0003U))
    \param[in]  dbg_low_power:
                one or more parameters can be selected which are shown as below:
      \arg        DBG_LOW_POWER_SLEEP: keep debugger connection during sleep mode
      \arg        DBG_LOW_POWER_DEEPSLEEP: keep debugger connection during deepsleep mode
      \arg        DBG_LOW_POWER_STANDBY: keep debugger connection during standby mode
    \param[out] none
    \retval     none
*/
void dbg_low_power_enable(uint32_t dbg_low_power)
{
    DBG_CTL |= (dbg_low_power & DBG_LOWPOWER_MASK);
}

/*!
    \brief      disable low power behavior when the mcu is in debug mode (API_ID(0x0004U))
    \param[in]  dbg_low_power:
                one or more parameters can be selected which are shown as below:
      \arg        DBG_LOW_POWER_SLEEP: do not keep debugger connection during sleep mode
      \arg        DBG_LOW_POWER_DEEPSLEEP: do not keep debugger connection during deepsleep mode
      \arg        DBG_LOW_POWER_STANDBY: do not keep debugger connection during standby mode
    \param[out] none
    \retval     none
*/
void dbg_low_power_disable(uint32_t dbg_low_power)
{
    DBG_CTL &= ~(dbg_low_power & DBG_LOWPOWER_MASK);
}

/*!
    \brief      enable peripheral behavior when the mcu is in debug mode (API_ID(0x0005U))
    \param[in]  dbg_periph: refer to dbg_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        DBG_FWDGT_HOLD: hold FWDGT counter when core is halted
      \arg        DBG_WWDGT_HOLD: hold WWDGT counter when core is halted
      \arg        DBG_CAN_HOLD: hold CAN0 receive register counter when core is halted
      \arg        DBG_I2C_HOLD: hold I2C0 smbus timeout when core is halted
      \arg        DBG_TIMERx_HOLD (x=0,1,2,7): hold TIMERx counter when core is halted
      \arg        DBG_GPTIMER0_HOLD: hold GPTIMER0 counter when core is halted
      \arg        DBG_GPTIMER1_HOLD: hold GPTIMER1 counter when core is halted
      \arg        DBG_CPTIMER0_HOLD: hold CPTIMER0 counter when core is halted
      \arg        DBG_CPTIMER1_HOLD: hold CPTIMER1 counter when core is halted
      \arg        DBG_CPTIMERW_HOLD: hold CPTIMERW counter when core is halted
    \param[out] none
    \retval     none
*/
void dbg_periph_enable(dbg_periph_enum dbg_periph)
{

    DBG_REG_VAL(dbg_periph) |= BIT(DBG_BIT_POS(dbg_periph));

}

/*!
    \brief      disable peripheral behavior when the mcu is in debug mode (API_ID(0x0006U))
    \param[in]  dbg_periph: refer to dbg_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        DBG_FWDGT_HOLD: hold FWDGT counter when core is halted
      \arg        DBG_WWDGT_HOLD: hold WWDGT counter when core is halted
      \arg        DBG_CAN_HOLD: hold CAN0 receive register counter when core is halted
      \arg        DBG_I2C_HOLD: hold I2C0 smbus timeout when core is halted
      \arg        DBG_TIMERx_HOLD (x=0,1,2,7): hold TIMERx counter when core is halted
      \arg        DBG_GPTIMER0_HOLD: hold GPTIMER0 counter when core is halted
      \arg        DBG_GPTIMER1_HOLD: hold GPTIMER1 counter when core is halted
      \arg        DBG_CPTIMER0_HOLD: hold CPTIMER0 counter when core is halted
      \arg        DBG_CPTIMER1_HOLD: hold CPTIMER1 counter when core is halted
      \arg        DBG_CPTIMERW_HOLD: hold CPTIMERW counter when core is halted
    \param[out] none
    \retval     none
*/
void dbg_periph_disable(dbg_periph_enum dbg_periph)
{
    DBG_REG_VAL(dbg_periph) &= ~BIT(DBG_BIT_POS(dbg_periph));
}

/*!
    \brief      enable trace pin assignment (API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dbg_trace_pin_enable(void)
{
    DBG_CTL |= DBG_CTL_TRACE_IOEN;
}

/*!
    \brief      disable trace pin assignment (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dbg_trace_pin_disable(void)
{
    DBG_CTL &= ~DBG_CTL_TRACE_IOEN;
}
