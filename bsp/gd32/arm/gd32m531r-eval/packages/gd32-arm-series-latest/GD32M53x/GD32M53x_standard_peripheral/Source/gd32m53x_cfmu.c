/*!
    \file    gd32m53x_cfmu.c
    \brief   CFMU driver

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

#include "gd32m53x_cfmu.h"

/*!
    \brief      deinitialize the CFMU (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cfmu_deinit(void)
{
    /* reset CFMU */
    rcu_periph_reset_enable(RCU_CFMURST);
    rcu_periph_reset_disable(RCU_CFMURST);
}

/*!
    \brief      enable clock frequency measurement (API_ID(0x0002U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cfmu_enable(void)
{
    /* enable CFMU */
    CFMU_CTL |= CFMU_CTL_CFMEN;
}

/*!
    \brief      disable clock frequency measurement (API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cfmu_disable(void)
{
    /* disable CFMU */
    CFMU_CTL &= ~CFMU_CTL_CFMEN;
}

/*!
    \brief      enable CFMUREF pin input (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cfmu_cfmuref_enable(void)
{
    /* enable the CFMUREF pin */
    CFMU_CTL |= CFMU_CTL_REFINEN;
}

/*!
    \brief      disable CFMUREF pin input (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cfmu_cfmuref_disable(void)
{
    /* disable the CFMUREF pin */
    CFMU_CTL &= ~CFMU_CTL_REFINEN;
}

/*!
    \brief      configure the reference signal (API_ID(0x0006U))
    \param[in]  rssel: reference signal select
      \arg        CFMU_RSSEL_CFMUREF: reference signal select the CFMUREF pin
      \arg        CFMU_RSSEL_INTERNAL_CLOCK: reference signal select the internal clock
    \param[out] none
    \retval     none
*/
void cfmu_reference_signal_config(uint32_t rssel)
{
    uint32_t reg;
    reg = CFMU_CTL;
    /* reset the RSSEL bits */
    reg &= ~CFMU_CTL_RSSEL;
    CFMU_CTL = (reg | (rssel & CFMU_CTL_RSSEL));
}

/*!
    \brief      configure the digital filter (API_ID(0x0007U))
    \param[in]  dfsel: digital filter select
      \arg        CFMU_DFSEL_DISABLE: digital filtering is disabled
      \arg        CFMU_DFSEL_DIV1: sampling clock for the digital filter is the frequency measuring clock divided by 1
      \arg        CFMU_DFSEL_DIV4: sampling clock for the digital filter is the frequency measuring clock divided by 4
      \arg        CFMU_DFSEL_DIV16: sampling clock for the digital filter is the frequency measuring clock divided by 16
    \param[out] none
    \retval     none
*/
void cfmu_digital_filter_config(uint32_t dfsel)
{
    uint32_t reg;
    reg = CFMU_CTL;
    /* reset the RSSEL bits */
    reg &= ~CFMU_CTL_DFSEL;
    CFMU_CTL = (reg | (dfsel & CFMU_CTL_DFSEL));
}

/*!
    \brief      configure the measurement reference clock source (API_ID(0x0008U))
    \param[in]  rck_src:
                only one parameter can be selected which is shown as below:
      \arg        CFMU_RCKSRC_HXTAL: HXTAL selected
      \arg        CFMU_RCKSRC_IRC32M: IRC32M selected
      \arg        CFMU_RCKSRC_IRC32K: IRC32K selected
      \arg        CFMU_RCKSRC_PCLK1: PCLK1 selected
    \param[in]  rck_div: rck divider
      \arg        CFMU_RCK_DIVx(x=32,128,1024,8192): reference clock is divided by x
    \param[in]  val_edge: valid edge
      \arg        CFMU_VAL_RISING: rising edge valid
      \arg        CFMU_VAL_FALLING: falling edge valid
      \arg        CFMU_VAL_BOTH: rising and falling edge valid
    \param[out] none
    \retval     none
*/
void cfmu_reference_clock_config(uint32_t rck_src, uint32_t rck_div, uint32_t val_edge)
{
    uint32_t rck_cfg = 0U;
    rck_cfg = CFMU_CTL;
    /* reset the RCKSEL, RCKDIV and EDGSEL */
    rck_cfg &= ~(CFMU_CTL_RCKSEL | CFMU_CTL_RCKDIV | CFMU_CTL_EDGSEL);
    /* set the RCKSEL, RCKDIV and EDGSEL */
    CFMU_CTL = (rck_cfg | (rck_src & CFMU_CTL_RCKSEL) | (rck_div & CFMU_CTL_RCKDIV) | (val_edge & CFMU_CTL_EDGSEL));
}

/*!
    \brief      configure the measurement target clock source (API_ID(0x0009U))
    \param[in]  mck_src:
                only one parameter can be selected which is shown as below:
      \arg        CFMU_MCKSRC_HXTAL: HXTAL selected
      \arg        CFMU_MCKSRC_IRC32M: IRC32M selected
      \arg        CFMU_MCKSRC_IRC32K: IRC32K selected
      \arg        CFMU_MCKSRC_PCLK1: PCLK1 selected
    \param[in]  mck_div: mck divider
      \arg        CFMU_MCK_DIVx(x=1,4,8,32): MCK is divided by x
    \param[out] none
    \retval     none
*/
void cfmu_measurement_clock_config(uint32_t mck_src, uint32_t mck_div)
{
    uint32_t mck_cfg = 0U;
    mck_cfg = CFMU_CTL;
    /* reset the MCKSEL, MCKDIV */
    mck_cfg &= ~(CFMU_CTL_MCKSEL | CFMU_CTL_MCKDIV);
    /* set the MCKSEL, MCKDIV */
    CFMU_CTL = (mck_cfg | (mck_src & CFMU_CTL_MCKSEL) | (mck_div & CFMU_CTL_MCKDIV));
}

/*!
    \brief    configure CFMU higher-limit value and lower-limit value (API_ID(0x000AU))
    \param[in]  cfmu_hlv: higher-limit value
    \param[in]  cfmu_llv: lower-limit value
    \param[out] none
    \retval     none
*/
void cfmu_limit_value_config(uint32_t cfmu_hlv, uint32_t cfmu_llv)
{
    CFMU_LVCFG &= ~((uint32_t)(CFMU_LVCFG_HLV | CFMU_LVCFG_LLV));
    CFMU_LVCFG |= (uint32_t)CFMU_HLV(cfmu_hlv);
    CFMU_LVCFG |= (uint32_t)CFMU_LLV(cfmu_llv);
}

/*!
    \brief      enable the CFMU interrupt (API_ID(0x000BU))
    \param[in]  cfmu_interrupt: CFMU interrupt, refer to cfmu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        CFMU_INT_OVF: overflow interrupt request
      \arg        CFMU_INT_CFMEND: measurement end interrupt request
      \arg        CFMU_INT_CFERR: frequency error interrupt request
    \param[out] none
    \retval     none
*/
void cfmu_interrupt_enable(cfmu_int_enum cfmu_interrupt)
{
    CFMU_REG_VAL(cfmu_interrupt) |= BIT(CFMU_BIT_POS(cfmu_interrupt));
}

/*!
    \brief      disable the CFMU interrupt (API_ID(0x000CU))
    \param[in]  cfmu_interrupt: CFMU interrupt, refer to cfmu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        CFMU_INT_OVF: overflow interrupt request
      \arg        CFMU_INT_CFMEND: measurement end interrupt request
      \arg        CFMU_INT_CFERR: frequency error interrupt request
    \param[out] none
    \retval     none
*/
void cfmu_interrupt_disable(cfmu_int_enum cfmu_interrupt)
{
    CFMU_REG_VAL(cfmu_interrupt) &= ~BIT(CFMU_BIT_POS(cfmu_interrupt));
}

/*!
    \brief      get the CFMU interrupt flags (API_ID(0x000DU))
    \param[in]  cfmu_int_flag: interrupt flags, refer to cfmu_int_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        CFMU_INT_FLAG_OVF: overflow flag
      \arg        CFMU_INT_FLAG_CFMEND: clock frequency accuracy measurement end flag
      \arg        CFMU_INT_FLAG_CFERR: clock frequency error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cfmu_interrupt_flag_get(cfmu_int_flag_enum cfmu_int_flag)
{
    FlagStatus status;

    /* get the cfmu interrupt flag */
    if(RESET != (CFMU_REG_VAL(cfmu_int_flag) & BIT(CFMU_BIT_POS(cfmu_int_flag)))) {
        status = SET;
    } else {
        status = RESET;
    }

    return status;
}

/*!
    \brief      clear the CFMU interrupt flags (API_ID(0x000EU))
    \param[in]  cfmu_int_flag_clear: interrupt flags, refer to cfmu_int_flag_clear_enum
                only one parameter can be selected which is shown as below:
      \arg        CFMU_INT_FLAG_OVF_CLR: overflow flag clear
      \arg        CFMU_INT_FLAG_CFMEND_CLR: clock frequency accuracy measurement end flag clear
      \arg        CFMU_INT_FLAG_CFERR_CLR: clock frequency error flag clear
    \param[out] none
    \retval     none
*/
void cfmu_interrupt_flag_clear(cfmu_int_flag_clear_enum cfmu_int_flag_clear)
{
    /* clear the cfmu interrupt flag */
    CFMU_REG_VAL(cfmu_int_flag_clear) |= BIT(CFMU_BIT_POS(cfmu_int_flag_clear));
}
