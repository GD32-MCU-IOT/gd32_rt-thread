/*!
    \file    gd32m53x_cptimerw.c
    \brief   definitions for the CPTIMERW

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

#include "gd32m53x_cptimerw.h"

/*!
    \brief      deinit a CPTIMERW (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cptimerw_deinit(void)
{
    /* reset CPTIMERW */
    rcu_periph_reset_enable(RCU_CPTIMERWRST);
    rcu_periph_reset_disable(RCU_CPTIMERWRST);
}

/*!
    \brief      initialize CPTIMERW init parameter struct with a default value (API_ID(0x0002U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void cptimerw_struct_para_init(cptimerw_init_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(CPTIMERW_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        initpara->period = 0U;
        initpara->prescaler = 0U;
        initpara->width = CPTIMERW_CNT_WIDTH_16BIT;
        initpara->clockdivision = CPTIMERW_CKDIV_DIV1;
        initpara->clear_source = CPTIMERW_CNT_CLEAR_DISABLE;
    }
}

/*!
    \brief      initialize CPTIMERW counter (API_ID(0x0003U))
    \param[in]  initpara: cptimerw init parameter struct
                  width: CPTIMERW_CNT_WIDTH_16BIT,CPTIMERW_CNT_WIDTH_32BIT
                  period: the counter autoreload value
                  prescaler: prescaler value of the counter clock, 0~65535
                  clear_source: CPTIMERW_CNT_CLEAR_DISABLE,CPTIMERW_CNT_CLEAR_ICH0,CPTIMERW_CNT_CLEAR_ICH1
                  clockdivision: CPTIMERW_CKDIV_DIV1,CPTIMERW_CKDIV_DIV2,CPTIMERW_CKDIV_DIV4
    \param[out] none
    \retval     none
*/
void cptimerw_init(cptimerw_init_parameter_struct *initpara)
{
    uint32_t tmpreg;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(CPTIMERW_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure the counter prescaler value */
        CPTIMERW_PSC = (uint32_t)initpara->prescaler;

        /* configure the counter width, clear source and clock division */
        tmpreg = CPTIMERW_CTL0;
        tmpreg &= ~((uint32_t)(CPTIMERW_CTL0_CNTWSEL | CPTIMERW_CTL0_CLRSSEL | CPTIMERW_CTL0_CKDIV));
        tmpreg |= (uint32_t)(initpara->width & CPTIMERW_CTL0_CNTWSEL);
        tmpreg |= (uint32_t)(initpara->clear_source & CPTIMERW_CTL0_CLRSSEL);
        tmpreg |= (uint32_t)(initpara->clockdivision & CPTIMERW_CTL0_CKDIV);
        CPTIMERW_CTL0 = tmpreg;

        /* configure the autoreload value */
        CPTIMERW_CAR = (uint32_t)initpara->period;
        /* generate an update event */
        CPTIMERW_SWEVG |= (uint32_t)CPTIMERW_SWEVG_UPG;
    }
}

/*!
    \brief      configure CPTIMERW autoreload register value (API_ID(0x0004U))
    \param[in]  autoreload: the counter autoreload value, 16 or 32-bit based on counter width
    \param[out] none
    \retval     none
*/
void cptimerw_autoreload_value_config(uint32_t autoreload)
{
    CPTIMERW_CAR = (uint32_t)autoreload;
}

/*!
    \brief      configure CPTIMERW prescaler value (API_ID(0x0005U))
    \param[in]  prescaler: prescaler value,0~65535
    \param[out] none
    \retval     none
*/
void cptimerw_prescaler_config(uint16_t prescaler)
{
    CPTIMERW_PSC = (uint32_t)prescaler;
}

/*!
    \brief      configure CPTIMERW counter register value (API_ID(0x0006U))
    \param[in]  value: the counter value, 16 or 32-bit based on counter width
    \param[out] none
    \retval     none
*/
void cptimerw_counter_value_config(uint32_t value)
{
    CPTIMERW_CNT = (uint32_t)value;
}

/*!
    \brief      configure CPTIMERW counter clear source (API_ID(0x0007U))
    \param[in]  clear_source: the counter clear source
                only one parameter can be selected which is shown as below:
      \arg        CPTIMERW_CNT_CLEAR_DISABLE: counter clear disable
      \arg        CPTIMERW_CNT_CLEAR_ICH0: counter clear at channel 0 input capture event
      \arg        CPTIMERW_CNT_CLEAR_ICH1: counter clear at channel 1 input capture event
    \param[out] none
    \retval     none
*/
void cptimerw_counter_clear_source_config(uint32_t clear_source)
{
    CPTIMERW_CTL0 &= ~(uint32_t)CPTIMERW_CTL0_CLRSSEL;
    CPTIMERW_CTL0 |= (uint32_t)clear_source & CPTIMERW_CTL0_CLRSSEL;
}

/*!
    \brief      read CPTIMERW counter value (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     counter value
*/
uint32_t cptimerw_counter_read(void)
{
    uint32_t count_value;

    count_value = CPTIMERW_CNT;

    return count_value;
}

/*!
    \brief      read CPTIMERW prescaler value (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     prescaler value
*/
uint16_t cptimerw_prescaler_read(void)
{
    uint16_t prescaler;

    prescaler = (uint16_t)CPTIMERW_PSC;

    return prescaler;
}

/*!
    \brief      enable the CPTIMERW (API_ID(0x000A))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cptimerw_enable(void)
{
    CPTIMERW_CTL0 |= (uint32_t) CPTIMERW_CTL0_CEN;
}

/*!
    \brief      disable the CPTIMERW (API_ID(0x000B))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cptimerw_disable(void)
{
    CPTIMERW_CTL0 &= ~((uint32_t)CPTIMERW_CTL0_CEN);
}

/*!
    \brief      select CPTIMERW channel output compare mode (API_ID(0x000CU))
    \param[in]  channel: CPTIMERW_OCHx(x=0,1)
    \param[in]  mode: output compare mode
                only one parameter can be selected which is shown as below:
      \arg        CPTIMERW_OC_MODE_DISABLE: output disable
      \arg        CPTIMERW_OC_MODE_MANTAIN: output maintain
      \arg        CPTIMERW_OC_MODE_LOW_TOGGLE: initial level is low and toggle on compare match
      \arg        CPTIMERW_OC_MODE_HIGH_TOGGLE: initial level is high and toggle on compare match
    \param[out] none
    \retval     none
*/
void cptimerw_channel_output_mode_select(uint32_t channel, uint32_t mode)
{
    switch(channel) {
    case CPTIMERW_OCH0:
        CPTIMERW_CTL1 &= ~(uint32_t)CPTIMERW_CTL1_OCH0MS;
        CPTIMERW_CTL1 |= (uint32_t)(mode & CPTIMERW_CTL1_OCH0MS);
        break;
    case CPTIMERW_OCH1:
        CPTIMERW_CTL1 &= ~(uint32_t)CPTIMERW_CTL1_OCH1MS;
        CPTIMERW_CTL1 |= (uint32_t)(mode << 2U) & CPTIMERW_CTL1_OCH1MS;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure CPTIMERW channel output compare value (API_ID(0x000DU))
    \param[in]  channel: CPTIMERW_OCHx(x=0,1,2,3)
    \param[in]  ochcv: channel output compare value, 16 or 32-bit based on counter width
    \param[out] none
    \retval     none
*/
void cptimerw_channel_output_compare_value_config(uint32_t channel, uint32_t ochcv)
{
    switch(channel) {
    case CPTIMERW_OCH0:
        CPTIMERW_OCH0CV = (uint32_t)ochcv;
        break;
    case CPTIMERW_OCH1:
        CPTIMERW_OCH1CV = (uint32_t)ochcv;
        break;
    case CPTIMERW_OCH2:
        CPTIMERW_OCH2CV = (uint32_t)ochcv;
        break;
    case CPTIMERW_OCH3:
        CPTIMERW_OCH3CV = (uint32_t)ochcv;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure CPTIMERW output compare channel enable state (API_ID(0x000EU))
    \param[in]  channel: CPTIMERW_OCHx(x=0,1,2,3)
    \param[in]  state: enable state
                only one parameter can be selected which is shown as below:
      \arg        CPTIMERW_OCX_DISABLE: output compare channel disable
      \arg        CPTIMERW_OCX_ENABLE: output compare channel enable
    \param[out] none
    \retval     none
*/
void cptimerw_channel_output_state_config(uint32_t channel, uint32_t state)
{
    switch(channel) {
    /* configure CPTIMERW OCH0 */
    case CPTIMERW_OCH0:
        CPTIMERW_CTL1 &= (~(uint32_t)CPTIMERW_CTL1_OCH0EN);
        CPTIMERW_CTL1 |= ((uint32_t)(state << 10U) & CPTIMERW_CTL1_OCH0EN);
        break;
    /* configure CPTIMERW OCH1 */
    case CPTIMERW_OCH1:
        CPTIMERW_CTL1 &= (~(uint32_t)CPTIMERW_CTL1_OCH1EN);
        CPTIMERW_CTL1 |= ((uint32_t)(state << 11U) & CPTIMERW_CTL1_OCH1EN);
        break;
    /* configure CPTIMERW OCH2 */
    case CPTIMERW_OCH2:
        CPTIMERW_CTL1 &= (~(uint32_t)CPTIMERW_CTL1_OCH2EN);
        CPTIMERW_CTL1 |= ((uint32_t)(state << 12U) & CPTIMERW_CTL1_OCH2EN);
        break;
    /* configure CPTIMERW OCH3 */
    case CPTIMERW_OCH3:
        CPTIMERW_CTL1 &= (~(uint32_t)CPTIMERW_CTL1_OCH3EN);
        CPTIMERW_CTL1 |= ((uint32_t)(state << 13U) & CPTIMERW_CTL1_OCH3EN);
        break;
    default:
        break;
    }
}

/*!
    \brief      initialize CPTIMERW channel input capture parameter struct with a default value (API_ID(0x000FU))
    \param[in]  icpara: channel input capture parameter struct
    \param[out] none
    \retval     none
*/
void cptimerw_channel_input_struct_para_init(cptimerw_ic_parameter_struct *icpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(icpara)) {
        fw_debug_report_err(CPTIMERW_MODULE_ID, API_ID(0x0007U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        icpara->icedge = CPTIMERW_IC_FALLING_EDGE;
        icpara->icfilter = 0U;
    }
}

/*!
    \brief      configure CPTIMERW input capture parameter (API_ID(0x0010U))
    \param[in]  channel: CPTIMERW_ICHx(x=0,1)
    \param[in]  icpara: cptimerw_ic_parameter_struct pointer
                  icedge: CPTIMERW_IC_FALLING_EDGE,CPTIMERW_IC_RISING_EDGE,CPTIMERW_IC_BOTH_EDGE,CPTIMERW_IC_DISABLE
                  icfilter: input capture filter value, 0~15
    \param[out] none
    \retval     none
*/
void cptimerw_input_capture_config(uint16_t channel, cptimerw_ic_parameter_struct *icpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(icpara)) {
        fw_debug_report_err(CPTIMERW_MODULE_ID, API_ID(0x0010U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(channel) {
        /* configure CPTIMERW ICH0 */
        case CPTIMERW_ICH0:
            /* reset the enable bit */
            CPTIMERW_CTL1 &= (~(uint32_t)CPTIMERW_CTL1_ICH0EN);

            /* set the edge bits */
            CPTIMERW_CTL1 &= (~(uint32_t)CPTIMERW_CTL1_ICH0ES);
            CPTIMERW_CTL1 |= (uint32_t)(icpara->icedge) & CPTIMERW_CTL1_ICH0ES;

            /* set the filter bits */
            CPTIMERW_CTL1 &= ~(uint32_t)(CPTIMERW_CTL1_ICH0FLT);
            CPTIMERW_CTL1 |= ((uint32_t)icpara->icfilter << 16U) & CPTIMERW_CTL1_ICH0FLT;

            /* set the enable bit */
            CPTIMERW_CTL1 |= (uint32_t)CPTIMERW_CTL1_ICH0EN;
            break;
        /* configure CPTIMERW ICH1 */
        case CPTIMERW_ICH1:
            /* reset the enable bit */
            CPTIMERW_CTL1 &= (~(uint32_t)CPTIMERW_CTL1_ICH1EN);

            /* set the edge bits */
            CPTIMERW_CTL1 &= (~(uint32_t)CPTIMERW_CTL1_ICH1ES);
            CPTIMERW_CTL1 |= ((uint32_t)icpara->icedge << 2U) & CPTIMERW_CTL1_ICH1ES;

            /* set the filter bits */
            CPTIMERW_CTL1 &= ~(uint32_t)(CPTIMERW_CTL1_ICH1FLT);
            CPTIMERW_CTL1 |= ((uint32_t)icpara->icfilter << 22U) & CPTIMERW_CTL1_ICH1FLT;

            /* set the enable bit */
            CPTIMERW_CTL1 |= (uint32_t)CPTIMERW_CTL1_ICH1EN;
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      read CPTIMERW channel input capture value (API_ID(0x0011U))
    \param[in]  channel: CPTIMERW_ICHx(x=0,1)
    \param[out] none
    \retval     capture value
*/
uint32_t cptimerw_channel_capture_value_register_read(uint16_t channel)
{
    uint32_t capture_value = 0U;

    switch(channel) {
    /* configure CPTIMERW ICH0 */
    case CPTIMERW_ICH0:
        capture_value = CPTIMERW_ICH0CV;
        break;
    /* configure CPTIMERW ICH0 */
    case CPTIMERW_ICH1:
        capture_value = CPTIMERW_ICH1CV;
        break;
    default:
        break;
    }

    return capture_value;
}

/*!
    \brief      software generate events (API_ID(0x0012U))
    \param[in]  event: the timer software event generation sources
                one or more parameters can be selected which are shown as below:
      \arg        CPTIMERW_EVENT_SRC_UPG: counter update event generation
    \param[out] none
    \retval     none
*/
void cptimerw_event_software_generate(uint32_t event)
{
    CPTIMERW_SWEVG = event;
}

/*!
    \brief      get CPTIMERW flags (API_ID(0x0013U))
    \param[in]  flag: the timer flags
                only one parameter can be selected which is shown as below:
      \arg        CPTIMERW_FLAG_UP  : CPTIMERW update flag
      \arg        CPTIMERW_FLAG_ICH0: CPTIMERW channel0 input capture flag
      \arg        CPTIMERW_FLAG_ICH1: CPTIMERW channel1 input capture flag
      \arg        CPTIMERW_FLAG_OCH0: CPTIMERW channel0 output compare flag
      \arg        CPTIMERW_FLAG_OCH1: CPTIMERW channel1 output compare flag
      \arg        CPTIMERW_FLAG_OCH2: CPTIMERW channel2 output compare flag
      \arg        CPTIMERW_FLAG_OCH3: CPTIMERW channel3 output compare flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cptimerw_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;

    if(RESET != (CPTIMERW_INTF & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      clear CPTIMERW flags (API_ID(0x0014U))
    \param[in]  flag: the timer flags
                 one or more parameters can be selected which are shown as below:
      \arg        CPTIMERW_FLAG_UP  : CPTIMERW update flag
      \arg        CPTIMERW_FLAG_ICH0: CPTIMERW channel0 input capture flag
      \arg        CPTIMERW_FLAG_ICH1: CPTIMERW channel1 input capture flag
      \arg        CPTIMERW_FLAG_OCH0: CPTIMERW channel0 output compare flag
      \arg        CPTIMERW_FLAG_OCH1: CPTIMERW channel1 output compare flag
      \arg        CPTIMERW_FLAG_OCH2: CPTIMERW channel2 output compare flag
      \arg        CPTIMERW_FLAG_OCH3: CPTIMERW channel3 output compare flag
    \param[out] none
    \retval     none
*/
void cptimerw_flag_clear(uint32_t flag)
{
    CPTIMERW_INTF = (~(uint32_t)flag);
}

/*!
    \brief      enable CPTIMERW interrupt (API_ID(0x0015U))
    \param[in]  interrupt: cptimerw interrupt enable source
                 one or more parameters can be selected which are shown as below:
      \arg        CPTIMERW_INT_UP  : CPTIMERW update interrupt
      \arg        CPTIMERW_INT_ICH0: CPTIMERW channel0 input capture interrupt
      \arg        CPTIMERW_INT_ICH1: CPTIMERW channel1 input capture interrupt
      \arg        CPTIMERW_INT_OCH0: CPTIMERW channel0 output compare interrupt
      \arg        CPTIMERW_INT_OCH1: CPTIMERW channel1 output compare interrupt
      \arg        CPTIMERW_INT_OCH2: CPTIMERW channel2 output compare interrupt
      \arg        CPTIMERW_INT_OCH3: CPTIMERW channel3 output compare interrupt
    \param[out] none
    \retval     none
*/
void cptimerw_interrupt_enable(uint32_t interrupt)
{
    CPTIMERW_INTEN |= (uint32_t) interrupt;
}

/*!
    \brief      disable CPTIMERW interrupt (API_ID(0x0016U))
    \param[in]  interrupt: cptimerw interrupt disable source
                 one or more parameters can be selected which are shown as below:
      \arg        CPTIMERW_INT_UP  : CPTIMERW update interrupt
      \arg        CPTIMERW_INT_ICH0: CPTIMERW channel0 input capture interrupt
      \arg        CPTIMERW_INT_ICH1: CPTIMERW channel1 input capture interrupt
      \arg        CPTIMERW_INT_OCH0: CPTIMERW channel0 output compare interrupt
      \arg        CPTIMERW_INT_OCH1: CPTIMERW channel1 output compare interrupt
      \arg        CPTIMERW_INT_OCH2: CPTIMERW channel2 output compare interrupt
      \arg        CPTIMERW_INT_OCH3: CPTIMERW channel3 output compare interrupt
    \param[out] none
    \retval     none
*/
void cptimerw_interrupt_disable(uint32_t interrupt)
{
    CPTIMERW_INTEN &= (~(uint32_t)interrupt);
}

/*!
    \brief      get CPTIMERW interrupt flag (API_ID(0x0017U))
    \param[in]  int_flag: the cptimerw interrupt bits
                only one parameter can be selected which is shown as below:
      \arg        CPTIMERW_INT_FLAG_UP  : CPTIMERW update interrupt flag
      \arg        CPTIMERW_INT_FLAG_ICH0: CPTIMERW channel0 input capture interrupt flag
      \arg        CPTIMERW_INT_FLAG_ICH1: CPTIMERW channel1 input capture interrupt flag
      \arg        CPTIMERW_INT_FLAG_OCH0: CPTIMERW channel0 output compare interrupt flag
      \arg        CPTIMERW_INT_FLAG_OCH1: CPTIMERW channel1 output compare interrupt flag
      \arg        CPTIMERW_INT_FLAG_OCH2: CPTIMERW channel2 output compare interrupt flag
      \arg        CPTIMERW_INT_FLAG_OCH3: CPTIMERW channel3 output compare interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cptimerw_interrupt_flag_get(uint32_t int_flag)
{
    uint32_t val;
    FlagStatus reval = RESET;

    val = (CPTIMERW_INTEN & int_flag);
    if((RESET != (CPTIMERW_INTF & int_flag)) && (RESET != val)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      clear CPTIMERW flags (API_ID(0x0018U))
    \param[in]  int_flag: the cptimerw interrupt bits
                one or more parameters can be selected which are shown as below:
      \arg        CPTIMERW_INT_FLAG_UP  : CPTIMERW update interrupt flag
      \arg        CPTIMERW_INT_FLAG_ICH0: CPTIMERW channel0 input capture interrupt flag
      \arg        CPTIMERW_INT_FLAG_ICH1: CPTIMERW channel1 input capture interrupt flag
      \arg        CPTIMERW_INT_FLAG_OCH0: CPTIMERW channel0 output compare interrupt flag
      \arg        CPTIMERW_INT_FLAG_OCH1: CPTIMERW channel1 output compare interrupt flag
      \arg        CPTIMERW_INT_FLAG_OCH2: CPTIMERW channel2 output compare interrupt flag
      \arg        CPTIMERW_INT_FLAG_OCH3: CPTIMERW channel3 output compare interrupt flag
    \param[out] none
    \retval     none
*/
void cptimerw_interrupt_flag_clear(uint32_t int_flag)
{
    CPTIMERW_INTF = (~(uint32_t)int_flag);
}
