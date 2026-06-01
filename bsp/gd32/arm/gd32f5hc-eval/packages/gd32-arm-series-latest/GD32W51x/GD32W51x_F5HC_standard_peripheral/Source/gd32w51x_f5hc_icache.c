/*!
    \file    gd32w51x_f5hc_icache.c
    \brief   ICACHE driver

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

#include "gd32w51x_f5hc_icache.h"

#define ICACHE_REGION_NUM_MAX   ((uint32_t)0x03U)

/*!
    \brief      enable icache (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void icache_enable(void)
{
    if(ENABLE != (ICACHE_CTL & ICACHE_CTL_EN)) {
        ICACHE_CTL |= ICACHE_CTL_EN;
    }
}

/*!
    \brief      disable icache (API_ID(0x0002U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void icache_disable(void)
{
    /* disable memory remap */
    icache_remap_disable(ICACHE_REMAP_REGION_0);
    icache_remap_disable(ICACHE_REMAP_REGION_1);
    icache_remap_disable(ICACHE_REMAP_REGION_2);
    icache_remap_disable(ICACHE_REMAP_REGION_3);
    /* reset and disable monitor */
    icache_monitor_reset(ICACHE_MONITOR_RESET_HIT_MISS);
    icache_monitor_disable(ICACHE_MONITOR_HIT_MISS);
    /* disable icache */
    ICACHE_CTL &= ICACHE_CTL_DEFAULT;
}

/*!
    \brief      enable the icache monitor (API_ID(0x0003U))
    \param[in]  monitor_source: the monitor to be enabled
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_MONITOR_HIT: hit monitor
      \arg        ICACHE_MONITOR_MISS: miss monitor
      \arg        ICACHE_MONITOR_HIT_MISS: hit and miss monitor
    \param[out] none
    \retval     none
*/
void icache_monitor_enable(uint32_t monitor_source)
{
    ICACHE_CTL |= (monitor_source & ICACHE_MONITOR_HIT_MISS);
}

/*!
    \brief      disable the icache monitor (API_ID(0x0004U))
    \param[in]  monitor_source: the monitor to be disabled
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_MONITOR_HIT: hit monitor
      \arg        ICACHE_MONITOR_MISS: miss monitor
      \arg        ICACHE_MONITOR_HIT_MISS: hit and miss monitor
    \param[out] none
    \retval     none
*/
void icache_monitor_disable(uint32_t monitor_source)
{
    ICACHE_CTL &= ~(monitor_source & ICACHE_MONITOR_HIT_MISS);
}

/*!
    \brief      reset the icache monitor (API_ID(0x0005U))
    \param[in]  reset_monitor_source: the monitor to be reset
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_MONITOR_RESET_HIT: hit monitor
      \arg        ICACHE_MONITOR_RESET_MISS: miss monitor
      \arg        ICACHE_MONITOR_RESET_HIT_MISS: hit and miss monitor
    \param[out] none
    \retval     none
*/
void icache_monitor_reset(uint32_t reset_monitor_source)
{
    ICACHE_CTL |= (reset_monitor_source & ICACHE_MONITOR_RESET_HIT_MISS);
    ICACHE_CTL &= ~(reset_monitor_source & ICACHE_MONITOR_RESET_HIT_MISS);
}

/*!
    \brief      configure icache way (associativity mode) (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: status of result(SUCCESS or ERROR)
*/
ErrStatus icache_way_configure(void)
{
    ErrStatus err = SUCCESS;
    if(ENABLE == (ICACHE_CTL & ICACHE_CTL_EN)) {
        err = ERROR;
    } else {
        ICACHE_CTL |= ICACHE_CTL_AMSEL;
    }
    return err;
}

/*!
    \brief      select icache burst type (API_ID(0x0007U))
    \param[in]  burst_type: output burst type
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_WRAP_BURST: icache WRAP burst mode
      \arg        ICACHE_INCR_BURST: icache INCR burst mode
    \param[out] none
    \retval     ErrStatus: status of result(SUCCESS or ERROR)
*/
ErrStatus icache_burst_type_select(uint32_t burst_type)
{
    ErrStatus err;
    if(ENABLE == (ICACHE_CTL & ICACHE_CTL_EN)) {
        err = ERROR;
    } else {
        /* select burst type */
        if(ICACHE_WRAP_BURST == burst_type) {
            ICACHE_CTL &= ~ICACHE_CTL_BSTT;
        } else {
            ICACHE_CTL |= ICACHE_CTL_BSTT;
        }
        err = SUCCESS;
    }
    return err;
}

/*!
    \brief      invalidate icache (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: status of result(SUCCESS or ERROR)
    \Note:      This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
ErrStatus icache_invalidation(void)
{
    ErrStatus err = SUCCESS;
    if(ENABLE == (ICACHE_CTL & ICACHE_CTL_EN)) {
        err = ERROR;
    }

    icache_interrupt_flag_clear(ICACHE_ENDC_FLAG);
    /* set the invalidation */
    ICACHE_CTL |= ICACHE_CTL_INVAL;
    /* wait until the operation end */
    while(RESET == (ICACHE_STAT & ICACHE_STAT_END)) {
    }
    return err;
}

/*!
    \brief      get the hit monitor value (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     hit value
*/
uint32_t icache_hitvalue_get(void)
{
    return ICACHE_HMC;
}

/*!
    \brief      get the miss monitor value (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     miss value
*/
uint32_t icache_missvalue_get(void)
{
    return ICACHE_MMC;
}

/*!
    \brief      enable the icache remap function (API_ID(0x000BU))
    \param[in]  icache_remap_config : structure of icache remap parameters
    \param[out] none
    \retval     ErrStatus: status of result(SUCCESS or ERROR)
*/
ErrStatus icache_remap_enable(icache_remap_struct *icache_remap_config)
{
    ErrStatus ret_val = ERROR;
    uint32_t val = 0x80000000U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(icache_remap_config)) {
        fw_debug_report_err(ICACHE_MODULE_ID, API_ID(0x000BU), ERR_PARAM_POINTER);
    } else if(NOT_ICACHE_REMAP_REGION(icache_remap_config->region_num)) {
        fw_debug_report_err(ICACHE_MODULE_ID, API_ID(0x000BU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* the remap can not be configured when icache en is 1 */
        if(ENABLE == (ICACHE_CTL & ICACHE_CTL_EN)) {
            ret_val = ERROR;
        } else {
            /* select the icache region */
            uint32_t reg = (ICACHE + 0x20U + (0x04U * icache_remap_config->region_num));
            /* check if the region is already configured */
            if(0U != (REG32(reg) & 0x1000U)) {
                ret_val = ERROR;
            } else {
                /* set the base address */
                val |= ((icache_remap_config->base_address & 0x1FFE0000U) >> 21U);
                /* set the remap address */
                val |= ((icache_remap_config->remap_address & 0xFFE00000U) >> 5U);
                /* set the remap size select the master and burst type */
                val |= ((icache_remap_config->remap_size << 9U) | (icache_remap_config->master_sel << 28U));
                REG32(reg) = val;
                /* enable remap */
                REG32(reg) |= ICACHE_CFGx_EN;

                ret_val = SUCCESS;
            }
        }
    }
    return ret_val;
}

/*!
    \brief      disable the icache remap function (API_ID(0x000CU))
    \param[in]  region_num : the remap region to be disabled
    \param[out] none
    \retval     ErrStatus: status of result(SUCCESS or ERROR)
*/
ErrStatus icache_remap_disable(uint32_t region_num)
{
    ErrStatus ret_val = ERROR;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ICACHE_REMAP_REGION(region_num)) {
        fw_debug_report_err(ICACHE_MODULE_ID, API_ID(0x000CU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == (ICACHE_CTL & ICACHE_CTL_EN)) {
            ret_val = ERROR;
        } else {
            /* select the icache region */
            ICACHE_CFG(region_num & ICACHE_REGION_NUM_MAX) &= ~ICACHE_CFGx_EN;
            ret_val = SUCCESS;
        }
    }
    return ret_val;
}

/*!
    \brief      get icache flag (API_ID(0x000DU))
    \param[in]  flag: the icache flag to be get
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_BUSY_FLAG: icache busy flag
      \arg        ICACHE_END_FLAG: icache operation end flag
      \arg        ICACHE_ERR_FLAG: icache error flag
    \param[out] none
    \retval     FlagStatus: status of result(SET or RESET)
*/
FlagStatus icache_flag_get(uint32_t flag)
{
    FlagStatus ret_val;
    __IO uint32_t reg = 0U;
    reg = ICACHE_STAT;
    /* check the status of interrupt source */
    if(RESET != (reg & flag)) {
        ret_val = SET;
    } else {
        ret_val = RESET;
    }
    return ret_val;
}

/*!
    \brief      clear icache flag (API_ID(0x000EU))
    \param[in]  flag: the icache flag to be cleared
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_ENDC_FLAG: icache operation end clear flag
      \arg        ICACHE_ERRC_FLAG: icache error clear flag
    \param[out] none
    \retval     none
*/
void icache_flag_clear(uint32_t flag)
{
    ICACHE_FC |= (flag & (ICACHE_ENDC_FLAG | ICACHE_ERRC_FLAG));
}

/*!
    \brief      enable icache interrupt (API_ID(0x000FU))
    \param[in]  interrupt: the interrupt to be enabled
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_ENDIE: icache operation end interrupt
      \arg        ICACHE_ERRIE: icache error interrupt
    \param[out] none
    \retval     none
*/
void icache_interrupt_enable(uint32_t interrupt)
{
    ICACHE_INTEN |= (interrupt & (ICACHE_ENDIE | ICACHE_ERRIE));
}

/*!
    \brief      disable icache interrupt (API_ID(0x0010U))
    \param[in]  interrupt: the interrupt to be disabled
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_ENDIE: icache operation end interrupt
      \arg        ICACHE_ERRIE: icache error interrupt
    \param[out] none
    \retval     none
*/
void icache_interrupt_disable(uint32_t interrupt)
{
    ICACHE_INTEN &= ~(interrupt & (ICACHE_ENDIE | ICACHE_ERRIE));
}

/*!
    \brief      get icache interrupt flag (API_ID(0x0011U))
    \param[in]  interrupt: the interrupt flag to be get
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_END_FLAG: icache operation end interrupt flag
      \arg        ICACHE_ERR_FLAG: icache error interrupt flag
    \param[out] none
    \retval     FlagStatus: status of result(SET or RESET)
*/
FlagStatus icache_interrupt_flag_get(uint32_t interrupt)
{
    FlagStatus ret_val;
    __IO uint32_t reg = 0U;
    reg = ICACHE_STAT;
    /* check the status of interrupt source */
    if(RESET != (reg & interrupt)) {
        ret_val = SET;
    } else {
        ret_val = RESET;
    }
    return ret_val;
}

/*!
    \brief      clear icache interrupt flag (API_ID(0x0012U))
    \param[in]  interrupt: the interrupt flag to be cleared
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_ENDC_FLAG: icache operation end interrupt clear flag
      \arg        ICACHE_ERRC_FLAG: icache error interrupt clear flag
    \param[out] none
    \retval     none
*/
void icache_interrupt_flag_clear(uint32_t interrupt)
{
    ICACHE_FC |= (interrupt & (ICACHE_ENDC_FLAG | ICACHE_ERRC_FLAG));
}

