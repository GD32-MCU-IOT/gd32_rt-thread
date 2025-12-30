/*!
    \file    gd32g5x3_timer.c
    \brief   TIMER driver

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

#include "gd32g5x3_timer.h"

/* TIMER init parameter mask */
#define ALIGNEDMODE_MASK            ((uint32_t)0x00000060U)   /*!< TIMER init parameter aligne dmode mask */
#define COUNTERDIRECTION_MASK       ((uint32_t)0x00000010U)   /*!< TIMER init parameter counter direction mask */
#define CLOCKDIVISION_MASK          ((uint32_t)0x00000300U)   /*!< TIMER init parameter clock division value mask */
#define TIMER_CNT_UPIFBU_MASK       ((uint32_t)0x80000000U)   /*!< the UPIFBU bit mask */

/*!
    \brief      deinit a TIMER
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     none
*/
void timer_deinit(uint32_t timer_periph)
{
    switch(timer_periph) {
    case TIMER0:
        /* reset TIMER0 */
        rcu_periph_reset_enable(RCU_TIMER0RST);
        rcu_periph_reset_disable(RCU_TIMER0RST);
        break;
    case TIMER1:
        /* reset TIMER1 */
        rcu_periph_reset_enable(RCU_TIMER1RST);
        rcu_periph_reset_disable(RCU_TIMER1RST);
        break;
    case TIMER2:
        /* reset TIMER2 */
        rcu_periph_reset_enable(RCU_TIMER2RST);
        rcu_periph_reset_disable(RCU_TIMER2RST);
        break;
    case TIMER3:
        /* reset TIMER3 */
        rcu_periph_reset_enable(RCU_TIMER3RST);
        rcu_periph_reset_disable(RCU_TIMER3RST);
        break;
    case TIMER4:
        /* reset TIMER4 */
        rcu_periph_reset_enable(RCU_TIMER4RST);
        rcu_periph_reset_disable(RCU_TIMER4RST);
        break;
    case TIMER5:
        /* reset TIMER5 */
        rcu_periph_reset_enable(RCU_TIMER5RST);
        rcu_periph_reset_disable(RCU_TIMER5RST);
        break;
    case TIMER6:
        /* reset TIMER6 */
        rcu_periph_reset_enable(RCU_TIMER6RST);
        rcu_periph_reset_disable(RCU_TIMER6RST);
        break;
    case TIMER7:
        /* reset TIMER7 */
        rcu_periph_reset_enable(RCU_TIMER7RST);
        rcu_periph_reset_disable(RCU_TIMER7RST);
        break;
    case TIMER14:
        /* reset TIMER14 */
        rcu_periph_reset_enable(RCU_TIMER14RST);
        rcu_periph_reset_disable(RCU_TIMER14RST);
        break;
    case TIMER15:
        /* reset TIMER15 */
        rcu_periph_reset_enable(RCU_TIMER15RST);
        rcu_periph_reset_disable(RCU_TIMER15RST);
        break;
    case TIMER16:
        /* reset TIMER16 */
        rcu_periph_reset_enable(RCU_TIMER16RST);
        rcu_periph_reset_disable(RCU_TIMER16RST);
        break;
    case TIMER19:
        /* reset TIMER19 */
        rcu_periph_reset_enable(RCU_TIMER19RST);
        rcu_periph_reset_disable(RCU_TIMER19RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      initialize TIMER init parameter struct with a default value
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void timer_struct_para_init(timer_parameter_struct *initpara)
{
    /* initialize the init parameter struct member with the default value */
    initpara->prescaler         = 0U;
    initpara->alignedmode       = TIMER_COUNTER_EDGE;
    initpara->counterdirection  = TIMER_COUNTER_UP;
    initpara->period            = 0xFFFFFFFFU;
    initpara->clockdivision     = TIMER_CKDIV_DIV1;
    initpara->repetitioncounter = 0U;
}

/*!
    \brief      initialize TIMER counter
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  initpara: init parameter struct
                  prescaler: prescaler value of the counter clock, 0~65535
                  alignedmode: TIMER_COUNTER_EDGE, TIMER_COUNTER_CENTER_DOWN, TIMER_COUNTER_CENTER_UP, TIMER_COUNTER_CENTER_BOTH
                  counterdirection: TIMER_COUNTER_UP, TIMER_COUNTER_DOWN
                  period: the integer part of auto reload value, 0~0xFFFF(adjustment mode disable, TIMERx(x=0,2,3,5~7,14~16,19))
                                                                 0~0xFFFE(adjustment mode enable, TIMERx(x=0,2,3,5~7,14~16,19))
                                                                 0~0xFFFFFFFF(adjustment mode disable, TIMERx(x=1,4))
                                                                 0~0xFFFFFFE(adjustment mode enable, TIMERx(x=1,4))
                  clockdivision: TIMER_CKDIV_DIV1, TIMER_CKDIV_DIV2, TIMER_CKDIV_DIV4(TIMERx(x=0~4,7,14~16,19))
                  repetitioncounter: counter repetition value, 0~0xFF, use TIMER_CREP0 register
                                                               0xFF~0xFFFFFFFF, use TIMER_CREP1 register
    \param[out] none
    \retval     none
*/
void timer_init(uint32_t timer_periph, timer_parameter_struct *initpara)
{
    /* configure the counter prescaler value */
    TIMER_PSC(timer_periph) = (uint16_t)initpara->prescaler;

    /* configure the counter direction and aligned mode */
    if((TIMER0  == timer_periph) || (TIMER7  == timer_periph) || (TIMER19 == timer_periph) || \
            (TIMER1  == timer_periph) || (TIMER2  == timer_periph) || (TIMER3  == timer_periph) || (TIMER4  == timer_periph)) {
        TIMER_CTL0(timer_periph) &= (~(uint32_t)(TIMER_CTL0_DIR | TIMER_CTL0_CAM));
        TIMER_CTL0(timer_periph) |= (uint32_t)(initpara->alignedmode & ALIGNEDMODE_MASK);
        TIMER_CTL0(timer_periph) |= (uint32_t)(initpara->counterdirection & COUNTERDIRECTION_MASK);
    }

    /* configure the auto reload value */
    TIMER_CAR(timer_periph) = (uint32_t)(initpara->period);

    /* configure the clock division value */
    if((TIMER5 != timer_periph) && (TIMER6 != timer_periph)) {
        /* reset the CKDIV bit */
        TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_CKDIV);
        TIMER_CTL0(timer_periph) |= (uint32_t)(initpara->clockdivision & CLOCKDIVISION_MASK);
    }

    if((TIMER0  == timer_periph) || (TIMER7  == timer_periph) || (TIMER19 == timer_periph) || \
            (TIMER14 == timer_periph) || (TIMER15 == timer_periph) || (TIMER16 == timer_periph)) {
        /* configure the repetition counter value */
        if(initpara->repetitioncounter <= 255U) {
            TIMER_CFG(timer_periph) &= (~(uint32_t)TIMER_CFG_CREPSEL);
            TIMER_CREP0(timer_periph) = (uint32_t)initpara->repetitioncounter;
        } else {
            TIMER_CFG(timer_periph) |= (uint32_t)TIMER_CFG_CREPSEL;
            TIMER_CREP1(timer_periph) = (uint32_t)initpara->repetitioncounter;
        }
    }

    /* generate an update event */
    TIMER_SWEVG(timer_periph) |= (uint32_t)TIMER_SWEVG_UPG;
}

/*!
    \brief      enable a TIMER
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     none
*/
void timer_enable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_CEN;
}

/*!
    \brief      disable a TIMER
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     none
*/
void timer_disable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_CEN);
}

/*!
    \brief      enable the auto reload shadow function
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     none
*/
void timer_auto_reload_shadow_enable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_ARSE;
}

/*!
    \brief      disable the auto reload shadow function
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     none
*/
void timer_auto_reload_shadow_disable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_ARSE);
}

/*!
    \brief      enable the update event
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     none
*/
void timer_update_event_enable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_UPDIS);
}

/*!
    \brief      disable the update event
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     none
*/
void timer_update_event_disable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t) TIMER_CTL0_UPDIS;
}

/*!
    \brief      set TIMER counter alignment mode
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  aligned: center-aligned mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_COUNTER_EDGE: edge-aligned mode
      \arg        TIMER_COUNTER_CENTER_DOWN: center-aligned and counting down assert mode
      \arg        TIMER_COUNTER_CENTER_UP: center-aligned and counting up assert mode
      \arg        TIMER_COUNTER_CENTER_BOTH: center-aligned and counting up/down assert mode
    \param[out] none
    \retval     none
*/
void timer_counter_alignment(uint32_t timer_periph, uint16_t aligned)
{
    TIMER_CTL0(timer_periph) &= (uint32_t)(~TIMER_CTL0_CAM);
    TIMER_CTL0(timer_periph) |= (uint32_t)aligned;
}

/*!
    \brief      set TIMER counter up direction
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[out] none
    \retval     none
*/
void timer_counter_up_direction(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_DIR);
}

/*!
    \brief      set TIMER counter down direction
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[out] none
    \retval     none
*/
void timer_counter_down_direction(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_DIR;
}

/*!
    \brief      configure the TIMER adjustment mode function
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_adjustment_mode_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CTL0(timer_periph) |= TIMER_CTL0_ADMEN;
    } else {
        TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_ADMEN);
    }
}

/*!
    \brief      configure TIMER prescaler
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  prescaler: prescaler value, 0~0xFFFF
    \param[in]  pscreload: prescaler reload mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_PSC_RELOAD_NOW: the prescaler is loaded right now
      \arg        TIMER_PSC_RELOAD_UPDATE: the prescaler is loaded at the next update event
    \param[out] none
    \retval     none
*/
void timer_prescaler_config(uint32_t timer_periph, uint16_t prescaler, uint32_t pscreload)
{
    TIMER_PSC(timer_periph) = (uint32_t)prescaler;

    if(TIMER_PSC_RELOAD_NOW == pscreload) {
        TIMER_SWEVG(timer_periph) |= (uint32_t)TIMER_SWEVG_UPG;
    }
}

/*!
    \brief      configure TIMER repetition register value
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  ccsel: repetition register selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CREP0_ENABLE: The update event rate is depended to TIMERx_CREP0 register
      \arg        TIMER_CREP1_ENABLE: The update event rate is depended to TIMERx_CREP1 register
    \param[in]  repetition: the counter repetition value, 0~0xFF, use TIMER_CREP0 register
                                                          0~0xFFFFFFFF, use TIMER_CREP1 register
    \param[out] none
    \retval     none
*/
void timer_repetition_value_config(uint32_t timer_periph, uint16_t ccsel, uint32_t repetition)
{
    if(TIMER_CREP0_ENABLE == ccsel) {
        TIMER_CFG(timer_periph) &= (~(uint32_t)TIMER_CFG_CREPSEL);
        TIMER_CREP0(timer_periph) = (uint32_t)repetition;
    } else if(TIMER_CREP1_ENABLE == ccsel) {
        TIMER_CFG(timer_periph) |= (uint32_t)TIMER_CFG_CREPSEL;
        TIMER_CREP1(timer_periph) = (uint32_t)repetition;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      read TIMER runtime repetition register value
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[out] none
    \retval     counter repetition value in TIMER_CREP1 register, 0~0xFFFFFFFF
*/
uint32_t timer_runtime_repetition_value_read(uint32_t timer_periph)
{
    return (TIMER_CREP1(timer_periph));
}

/*!
    \brief      configure TIMER auto reload register value
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  autoreload: the integer part of auto-reload value, 0~0xFFFF(adjustment mode disable, TIMERx(x=0,2,3,5~7,14~16,19))
                                                                   0~0xFFFE(adjustment mode enable, TIMERx(x=0,2,3,5~7,14~16,19))
                                                                   0~0xFFFFFFFF(adjustment mode disable, TIMERx(x=1,4))
                                                                   0~0xFFFFFFE(adjustment mode enable, TIMERx(x=1,4))
    \param[out] none
    \retval     none
*/
void timer_autoreload_value_config(uint32_t timer_periph, uint32_t autoreload)
{
    uint32_t reg;

    /* configure auto reload register with adjustment mode enable */
    if(TIMER_CTL0(timer_periph) & TIMER_CTL0_ADMEN) {
        reg = TIMER_CAR(timer_periph);
        reg &= (uint32_t)TIMER_CAR_CARL_FRACT;
        reg |= (uint32_t)autoreload;
        TIMER_CAR(timer_periph) = reg;
    } else {
        /* configure auto reload register with adjustment mode disable */
        TIMER_CAR(timer_periph) = (uint32_t)autoreload;
    }
}

/*!
    \brief      configure TIMER fractional part of auto reload register value
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  fract: fractional part of auto reload value, 0~F
    \param[out] none
    \retval     none
*/
void timer_auto_reload_fract_value_config(uint32_t timer_periph, uint32_t fract)
{
    uint32_t reg;

    reg = TIMER_CAR(timer_periph);
    reg &= (~(uint32_t)TIMER_CAR_CARL_FRACT);
    reg |= (uint32_t)(fract << 28U);
    TIMER_CAR(timer_periph) = reg;
}

/*!
    \brief      get TIMER auto reload register value
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     the integer part of auto reload register value, 0~0xFFFF(adjustment mode disable, TIMERx(x=0,2,3,5~7,14~16,19))
                                                                0~0xFFFE(adjustment mode enable, TIMERx(x=0,2,3,5~7,14~16,19))
                                                                0~0xFFFFFFFF(adjustment mode disable, TIMERx(x=1,4))
                                                                0~0xFFFFFFE(adjustment mode enable, TIMERx(x=1,4))
*/
uint32_t timer_autoreload_value_read(uint32_t timer_periph)
{
    uint32_t autoreload = 0U;

    if(TIMER_CTL0(timer_periph) & TIMER_CTL0_ADMEN) {
        autoreload =  TIMER_CAR(timer_periph) & (~TIMER_CAR_CARL_FRACT);
    } else {
        autoreload =  TIMER_CAR(timer_periph);
    }

    return autoreload;
}

/*!
    \brief      read TIMER fractional part of auto reload register value
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     fractional part of auto reload value, 0~F
*/
uint32_t timer_auto_reload_fract_value_read(uint32_t timer_periph)
{
    uint32_t fract;

    fract = (TIMER_CAR(timer_periph) & TIMER_CAR_CARL_FRACT) >> 28U;

    return fract;
}

/*!
    \brief      configure TIMER counter register value
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  counter: the counter value, 0~0xFFFF, TIMERx(x=0,2,3,5~7,14~16,19)
                                            0~0xFFFFFFFF, TIMERx(x=1,4)
    \param[out] none
    \retval     none
*/
void timer_counter_value_config(uint32_t timer_periph, uint32_t counter)
{
    if(TIMER_CTL0(timer_periph) & TIMER_CTL0_UPIFBUEN) {
        counter &= (~TIMER_CNT_UPIFBU_MASK);
    }
    TIMER_CNT(timer_periph) = (uint32_t)counter;
}

/*!
    \brief      read TIMER counter value
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     counter value: 0~0xFFFF, TIMERx(x=0,2,3,5~7,14~16,19)
                               0~0xFFFFFFFF, TIMERx(x=1,4)
*/
uint32_t timer_counter_read(uint32_t timer_periph)
{
    uint32_t count_value = 0U;

    count_value = (uint32_t)TIMER_CNT(timer_periph);
    if((TIMER_CTL0(timer_periph) & TIMER_CTL0_UPIFBUEN)) {
        count_value &= (uint32_t)(~TIMER_CNT_UPIFBU_MASK);
    }

    return (count_value);
}

/*!
    \brief      read TIMER prescaler value
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     prescaler register value, 0~0xFFFF
*/
uint16_t timer_prescaler_read(uint32_t timer_periph)
{
    uint16_t prescaler_value = 0U;
    prescaler_value = (uint16_t)(TIMER_PSC(timer_periph));
    return (prescaler_value);
}

/*!
    \brief      configure TIMER single pulse mode
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  spmode: single pulse mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SP_MODE_SINGLE: single pulse mode
      \arg        TIMER_SP_MODE_REPETITIVE: repetitive pulse mode
    \param[out] none
    \retval     none
*/
void timer_single_pulse_mode_config(uint32_t timer_periph, uint32_t spmode)
{
    if(TIMER_SP_MODE_SINGLE == spmode) {
        TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_SPM;
    } else if(TIMER_SP_MODE_REPETITIVE == spmode) {
        TIMER_CTL0(timer_periph) &= (~((uint32_t)TIMER_CTL0_SPM));
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure timer delayable single pulse mode
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  dspmode: delayable SPM mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_MODE_DSPM0: delayable SPM mode 0
      \arg        TIMER_OC_MODE_DSPM1: delayable SPM mode 1
    \param[in]  cnt_dir: counter direction selection
                only one parameter can be selected which is shown as below:
                  TIMER_COUNTER_UP: count up
                  TIMER_COUNTER_DOWN: count down
    \param[out] none
    \retval     none
*/
void timer_delayable_single_pulse_mode_config(uint32_t timer_periph, uint16_t channel, uint32_t dspmode, uint16_t cnt_dir)
{
    /* timer run in single mode*/
    timer_single_pulse_mode_config(timer_periph, TIMER_SP_MODE_SINGLE);
    /* set the CHxCOMCTL/MCHxCOMCTL bits */
    timer_channel_output_mode_config(timer_periph, channel, dspmode);
    /* set the restart + event slave mode */
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_RESTART_EVENT);
    /* set the counter direction in edge-aligned mode*/
    TIMER_CTL0(timer_periph) &= (~(uint32_t)(TIMER_CTL0_DIR | TIMER_CTL0_CAM));
    TIMER_CTL0(timer_periph) |= (uint32_t)(cnt_dir & COUNTERDIRECTION_MASK);

    /* set the CHxCV/MCHxCV */
    if(TIMER_COUNTER_UP == cnt_dir) {
        switch(channel) {
        /* configure TIMER_CH_0 */
        case TIMER_CH_0:
            TIMER_CH0CV(timer_periph) = 0U;
            break;
        /* configure TIMER_CH_1 */
        case TIMER_CH_1:
            TIMER_CH1CV(timer_periph) = 0U;
            break;
        /* configure TIMER_CH_2 */
        case TIMER_CH_2:
            TIMER_CH2CV(timer_periph) = 0U;
            break;
        /* configure TIMER_CH_3 */
        case TIMER_CH_3:
            TIMER_CH3CV(timer_periph) = 0U;
            break;
        /* configure TIMER_MCH_0 */
        case TIMER_MCH_0:
            TIMER_MCH0CV(timer_periph) = 0U;
            break;
        /* configure TIMER_MCH_1 */
        case TIMER_MCH_1:
            TIMER_MCH1CV(timer_periph) = 0U;
            break;
        /* configure TIMER_MCH_2 */
        case TIMER_MCH_2:
            TIMER_MCH2CV(timer_periph) = 0U;
            break;
        /* configure TIMER_MCH_3 */
        case TIMER_MCH_3:
            TIMER_MCH3CV(timer_periph) = 0U;
            break;
        default:
            break;
        }
    } else if(TIMER_COUNTER_DOWN == cnt_dir) {
        /* read the CAR value */
        uint32_t value = timer_autoreload_value_read(timer_periph);
        switch(channel) {
        /* configure TIMER_CH_0 */
        case TIMER_CH_0:
            TIMER_CH0CV(timer_periph) = (uint32_t)value;
            break;
        /* configure TIMER_CH_1 */
        case TIMER_CH_1:
            TIMER_CH1CV(timer_periph) = (uint32_t)value;
            break;
        /* configure TIMER_CH_2 */
        case TIMER_CH_2:
            TIMER_CH2CV(timer_periph) = (uint32_t)value;
            break;
        /* configure TIMER_CH_3 */
        case TIMER_CH_3:
            TIMER_CH3CV(timer_periph) = (uint32_t)value;
            break;
        /* configure TIMER_MCH_0 */
        case TIMER_MCH_0:
            TIMER_MCH0CV(timer_periph) = (uint32_t)value;
            break;
        /* configure TIMER_MCH_1 */
        case TIMER_MCH_1:
            TIMER_MCH1CV(timer_periph) = (uint32_t)value;
            break;
        /* configure TIMER_MCH_2 */
        case TIMER_MCH_2:
            TIMER_MCH2CV(timer_periph) = (uint32_t)value;
            break;
        /* configure TIMER_MCH_3 */
        case TIMER_MCH_3:
            TIMER_MCH3CV(timer_periph) = (uint32_t)value;
            break;
        default:
            break;
        }
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure TIMER update source
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  update: update source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_UPDATE_SRC_GLOBAL: update generate by setting of UPG bit or the counter overflow/underflow,
                                           or the slave mode controller trigger
      \arg        TIMER_UPDATE_SRC_REGULAR: update generate only by counter overflow/underflow
    \param[out] none
    \retval     none
*/
void timer_update_source_config(uint32_t timer_periph, uint32_t update)
{
    if(TIMER_UPDATE_SRC_REGULAR == update) {
        TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_UPS;
    } else if(TIMER_UPDATE_SRC_GLOBAL == update) {
        TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_UPS);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure timer OCPRE_CLR_INT source
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  clear_source: OCPRE_CLR_INT source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OCPRE_CLR_INT_OCPRE_CLR: OCPRE_CLR_INT is connected to the OCPRE_CLR input
      \arg        TIMER_OCPRE_CLR_INT_ETIF: OCPRE_CLR_INT is connected to ETIF
    \param[out] none
    \retval     none
*/
void timer_ocpre_clear_source_config(uint32_t timer_periph, uint32_t clear_source)
{
    if(clear_source == TIMER_OCPRE_CLR_INT_ETIF) {
        TIMER_SMCFG(timer_periph) |= (uint32_t)TIMER_SMCFG_OCRC;
    } else {
        TIMER_SMCFG(timer_periph) &= (~(uint32_t)TIMER_SMCFG_OCRC);
    }
}

/*!
    \brief      configure timer OCPRE_CLR input
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  clear_input: OCPRE_CLR source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OCPRE_CLR_INPUT_0: OCPRE_CLR_INT is connected to OCPRE_CLR 0
      \arg        TIMER_OCPRE_CLR_INPUT_1: OCPRE_CLR_INT is connected to OCPRE_CLR 1
      \arg        TIMER_OCPRE_CLR_INPUT_2: OCPRE_CLR_INT is connected to OCPRE_CLR 2
      \arg        TIMER_OCPRE_CLR_INPUT_3: OCPRE_CLR_INT is connected to OCPRE_CLR 3
      \arg        TIMER_OCPRE_CLR_INPUT_4: OCPRE_CLR_INT is connected to OCPRE_CLR 4
      \arg        TIMER_OCPRE_CLR_INPUT_5: OCPRE_CLR_INT is connected to OCPRE_CLR 5
      \arg        TIMER_OCPRE_CLR_INPUT_6: OCPRE_CLR_INT is connected to OCPRE_CLR 6
      \arg        TIMER_OCPRE_CLR_INPUT_7: OCPRE_CLR_INT is connected to OCPRE_CLR 7
    \param[out] none
    \retval     none
*/
void timer_ocpre_clear_input_config(uint32_t timer_periph, uint32_t clear_input)
{
    TIMER_AFCTL1(timer_periph) &= (~(uint32_t)TIMER_AFCTL1_OCRINSEL);
    TIMER_AFCTL1(timer_periph) |= (uint32_t)clear_input;
}

/*!
    \brief      configure the TIMER pulse on compare function
    \param[in]  timer_periph: TIMERx(x=0,7,19)
    \param[in]  pulse_width: 0~255
    \param[in]  pulse_prescaler: 0~7
    \param[out] none
    \retval     none
*/
void timer_pulse_on_compare_config(uint32_t timer_periph, uint32_t pulse_width, uint32_t pulse_prescaler)
{
    TIMER_DECCTL(timer_periph) &= (~(uint32_t)(TIMER_DECCTL_OPWID | TIMER_DECCTL_OPPSC));
    TIMER_DECCTL(timer_periph) |= ((uint32_t)((pulse_width << 16U) | (pulse_prescaler << 24U)));
}

/*!
    \brief      enable the TIMER DMA
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  dma: specify which DMA to enable
                one or more parameters can be selected which are shown as below:
      \arg        TIMER_DMA_UPD:  update DMA request, TIMERx(x=0~7,14~16,19)
      \arg        TIMER_DMA_CH0D: channel 0 DMA request, TIMERx(x=0~4,7,14~16,19)
      \arg        TIMER_DMA_CH1D: channel 1 DMA request, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_DMA_CH2D: channel 2 DMA request, TIMERx(x=0~4,7,19)
      \arg        TIMER_DMA_CH3D: channel 3 DMA request, TIMERx(x=0~4,7,19)
      \arg        TIMER_DMA_CMTD: channel commutation DMA request, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_DMA_TRGD: trigger DMA request, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_DMA_MCH0D: multi mode channel 0 DMA request, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_DMA_MCH1D: multi mode channel 1 DMA request, TIMERx(x=0,7,19)
      \arg        TIMER_DMA_MCH2D: multi mode channel 2 DMA request, TIMERx(x=0,7,19)
      \arg        TIMER_DMA_MCH3D: multi mode channel 3 DMA request, TIMERx(x=0,7,19)
    \param[out] none
    \retval     none
*/
void timer_dma_enable(uint32_t timer_periph, uint32_t dma)
{
    TIMER_DMAINTEN(timer_periph) |= (uint32_t) dma;
}

/*!
    \brief      disable the TIMER DMA
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  dma: specify which DMA to enable
                one or more parameters can be selected which are shown as below:
      \arg        TIMER_DMA_UPD:  update DMA request, TIMERx(x=0~7,14~16,19)
      \arg        TIMER_DMA_CH0D: channel 0 DMA request, TIMERx(x=0~4,7,14~16,19)
      \arg        TIMER_DMA_CH1D: channel 1 DMA request, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_DMA_CH2D: channel 2 DMA request, TIMERx(x=0~4,7,19)
      \arg        TIMER_DMA_CH3D: channel 3 DMA request, TIMERx(x=0~4,7,19)
      \arg        TIMER_DMA_CMTD: channel commutation DMA request, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_DMA_TRGD: trigger DMA request, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_DMA_MCH0D: multi mode channel 0 DMA request, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_DMA_MCH1D: multi mode channel 1 DMA request, TIMERx(x=0,7,19)
      \arg        TIMER_DMA_MCH2D: multi mode channel 2 DMA request, TIMERx(x=0,7,19)
      \arg        TIMER_DMA_MCH3D: multi mode channel 3 DMA request, TIMERx(x=0,7,19)
    \param[out] none
    \retval     none
*/
void timer_dma_disable(uint32_t timer_periph, uint32_t dma)
{
    TIMER_DMAINTEN(timer_periph) &= (~(uint32_t)(dma));
}

/*!
    \brief      channel DMA request source selection
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  dma_request: channel DMA request source selection
                only one parameter can be selected which is shown as below:
       \arg        TIMER_DMAREQUEST_CHANNELEVENT: DMA request of channel n is sent when channel n event occurs
       \arg        TIMER_DMAREQUEST_UPDATEEVENT: DMA request of channel n is sent when update event occurs
    \param[out] none
    \retval     none
*/
void timer_channel_dma_request_source_select(uint32_t timer_periph, uint32_t dma_request)
{
    if(TIMER_DMAREQUEST_UPDATEEVENT == dma_request) {
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_DMAS;
    } else if(TIMER_DMAREQUEST_CHANNELEVENT == dma_request) {
        TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_DMAS);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure the TIMER DMA transfer
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  dma_baseaddr: DMA access base address
                only one parameter can be selected which is shown as below:
       \arg        TIMER_DMACFG_DMATA_CTL0: DMA transfer address is TIMER_CTL0, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_CTL1: DMA transfer address is TIMER_CTL1, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_SMCFG: DMA transfer address is TIMER_SMCFG, TIMERx(x=0~4,7,14,19)
       \arg        TIMER_DMACFG_DMATA_DMAINTEN: DMA transfer address is TIMER_DMAINTEN, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_INTF: DMA transfer address is TIMER_INTF, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_SWEVG: DMA transfer address is TIMER_SWEVG, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_CHCTL0: DMA transfer address is TIMER_CHCTL0, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_CHCTL1: DMA transfer address is TIMER_CHCTL1, TIMERx(x=0~4,7,19)
       \arg        TIMER_DMACFG_DMATA_CHCTL2: DMA transfer address is TIMER_CHCTL2, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_CNT: DMA transfer address is TIMER_CNT, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_PSC: DMA transfer address is TIMER_PSC, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_CAR: DMA transfer address is TIMER_CAR, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_CREP0: DMA transfer address is TIMER_CREP0, TIMERx(x=0,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_CH0CV: DMA transfer address is TIMER_CH0CV, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_CH1CV: DMA transfer address is TIMER_CH1CV, TIMERx(x=0~4,7,14,19)
       \arg        TIMER_DMACFG_DMATA_CH2CV: DMA transfer address is TIMER_CH2CV, TIMERx(x=0~4,7,19)
       \arg        TIMER_DMACFG_DMATA_CH3CV: DMA transfer address is TIMER_CH3CV, TIMERx(x=0~4,7,19)
       \arg        TIMER_DMACFG_DMATA_CCHP0: DMA transfer address is TIMER_CCHP0, TIMERx(x=0,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_MCHCTL0: DMA transfer address is TIMER_MCHCTL0, TIMERx(x=0,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_MCHCTL1: DMA transfer address is TIMER_MCHCTL1, TIMERx(x=0,7,19)
       \arg        TIMER_DMACFG_DMATA_MCHCTL2: DMA transfer address is TIMER_MCHCTL2, TIMERx(x=0,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_MCH0CV: DMA transfer address is TIMER_MCH0CV, TIMERx(x=0,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_MCH1CV: DMA transfer address is TIMER_MCH1CV, TIMERx(x=0,7,19)
       \arg        TIMER_DMACFG_DMATA_MCH2CV: DMA transfer address is TIMER_MCH2CV, TIMERx(x=0,7,19)
       \arg        TIMER_DMACFG_DMATA_MCH3CV: DMA transfer address is TIMER_MCH3CV, TIMERx(x=0,7,19)
       \arg        TIMER_DMACFG_DMATA_CH0COMV_ADD: DMA transfer address is TIMER_CH0COMV_ADD, TIMERx(x=0~4,7,14,19)
       \arg        TIMER_DMACFG_DMATA_CH1COMV_ADD: DMA transfer address is TIMER_CH1COMV_ADD, TIMERx(x=0~4,7,14,19)
       \arg        TIMER_DMACFG_DMATA_CH2COMV_ADD: DMA transfer address is TIMER_CH2COMV_ADD, TIMERx(x=0~4,7,19)
       \arg        TIMER_DMACFG_DMATA_CH3COMV_ADD: DMA transfer address is TIMER_CH3COMV_ADD, TIMERx(x=0~4,7,19)
       \arg        TIMER_DMACFG_DMATA_CTL2: DMA transfer address is TIMER_CTL2, TIMERx(x=0~4,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_FCCHP0: DMA transfer address is TIMER_FCCHP0, TIMERx(x=0,7,19)
       \arg        TIMER_DMACFG_DMATA_FCCHP1: DMA transfer address is TIMER_FCCHP1, TIMERx(x=0,7,19)
       \arg        TIMER_DMACFG_DMATA_FCCHP2: DMA transfer address is TIMER_FCCHP2, TIMERx(x=0,7,19)
       \arg        TIMER_DMACFG_DMATA_FCCHP3: DMA transfer address is TIMER_FCCHP3, TIMERx(x=0,7,19)
       \arg        TIMER_DMACFG_DMATA_AFCTL0: DMA transfer address is TIMER_AFCTL0, TIMERx(x=0,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_AFCTL1: DMA transfer address is TIMER_AFCTL1, TIMERx(x=0,7,19)
       \arg        TIMER_DMACFG_DMATA_WDGPER: DMA transfer address is TIMER_WDGPER, TIMERx(x=0~4,7,19)
       \arg        TIMER_DMACFG_DMATA_CREP1: DMA transfer address is TIMER_CREP1, TIMERx(x=0,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_CCHP1: DMA transfer address is TIMER_CCHP1, TIMERx(x=0,7,14~16,19)
       \arg        TIMER_DMACFG_DMATA_DECCTL: DMA transfer address is TIMER_DECCTL, TIMERx(0~4,7,19)
       \arg        TIMER_DMACFG_DMATA_CINITCTL: DMA transfer address is TIMER_CINITCTL, TIMERx(x=0,7,19)
       \arg        TIMER_DMACFG_DMATA_CINITV: DMA transfer address is TIMER_CINITV, TIMERx(x=0,7,19)
    \param[in]  dma_lenth:
                only one parameter can be selected which is shown as below:
       \arg        TIMER_DMACFG_DMATC_xTRANSFER(x=1~42): DMA transfer x time
    \param[out] none
    \retval     none
*/
void timer_dma_transfer_config(uint32_t timer_periph, uint32_t dma_baseaddr, uint32_t dma_lenth)
{
    TIMER_DMACFG(timer_periph) &= (~(uint32_t)(TIMER_DMACFG_DMATA | TIMER_DMACFG_DMATC));
    TIMER_DMACFG(timer_periph) |= (uint32_t)(dma_baseaddr | dma_lenth);
}

/*!
    \brief      software generate events
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  event: the timer software event generation sources
                one or more parameters can be selected which are shown as below:
      \arg        TIMER_EVENT_SRC_UPG: update event generation, TIMERx(x=0~7,14~16,19)
      \arg        TIMER_EVENT_SRC_CH0G: channel 0 capture or compare event generation, TIMERx(x=0~4,7,14~16,19)
      \arg        TIMER_EVENT_SRC_CH1G: channel 1 capture or compare event generation, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_EVENT_SRC_CH2G: channel 2 capture or compare event generation, TIMERx(x=0~4,7,19)
      \arg        TIMER_EVENT_SRC_CH3G: channel 3 capture or compare event generation, TIMERx(x=0~4,7,19)
      \arg        TIMER_EVENT_SRC_CMTG: channel commutation event generation, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_EVENT_SRC_TRGG: trigger event generation, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_EVENT_SRC_BRK0G: BREAK0 event generation, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_EVENT_SRC_BRK1G: BREAK1 event generation, TIMERx(x=0,7,19)
      \arg        TIMER_EVENT_SRC_MCH0G: multi mode channel 0 capture or compare event generation, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_EVENT_SRC_MCH1G: multi mode channel 1 capture or compare event generation, TIMERx(x=0,7,19)
      \arg        TIMER_EVENT_SRC_MCH2G: multi mode channel 2 capture or compare event generation, TIMERx(x=0,7,19)
      \arg        TIMER_EVENT_SRC_MCH3G: multi mode channel 3 capture or compare event generation, TIMERx(x=0,7,19)
      \arg        TIMER_EVENT_SRC_CH0COMADDG: channel 0 additional compare event generation, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_EVENT_SRC_CH1COMADDG: channel 1 additional compare event generation, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_EVENT_SRC_CH2COMADDG: channel 2 additional compare event generation, TIMERx(x=0~4,7,19)
      \arg        TIMER_EVENT_SRC_CH3COMADDG: channel 3 additional compare event generation, TIMERx(x=0~4,7,19)
    \param[out] none
    \retval     none
*/
void timer_event_software_generate(uint32_t timer_periph, uint32_t event)
{
    TIMER_SWEVG(timer_periph) |= (uint32_t)event;
}

/*!
    \brief      initialize TIMER break parameter struct with a default value
    \param[in]  breakpara: TIMER break parameter struct
    \param[out] none
    \retval     none
*/
void timer_break_struct_para_init(timer_break_parameter_struct *breakpara)
{
    /* initialize the break parameter struct member with the default value */
    breakpara->runoffstate           = TIMER_ROS_STATE_DISABLE;
    breakpara->ideloffstate          = TIMER_IOS_STATE_DISABLE;
    breakpara->deadtime              = 0U;
    breakpara->outputautostate       = TIMER_OUTAUTO_DISABLE;
    breakpara->protectmode           = TIMER_CCHP0_PROT_OFF;
    breakpara->break0state           = TIMER_BREAK0_DISABLE;
    breakpara->break0filter          = 0U;
    breakpara->break0polarity        = TIMER_BREAK0_POLARITY_LOW;
    breakpara->break0lock            = TIMER_BREAK0_LK_DISABLE;
    breakpara->break0release         = TIMER_BREAK0_UNRELEASE;
    breakpara->break1state           = TIMER_BREAK1_DISABLE;
    breakpara->break1filter          = 0U;
    breakpara->break1polarity        = TIMER_BREAK1_POLARITY_LOW;
    breakpara->break1lock            = TIMER_BREAK1_LK_DISABLE;
    breakpara->break1release         = TIMER_BREAK1_UNRELEASE;
}

/*!
    \brief      configure TIMER break function
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  breakpara: TIMER break parameter struct
                  runoffstate: TIMER_ROS_STATE_ENABLE, TIMER_ROS_STATE_DISABLE
                  ideloffstate: TIMER_IOS_STATE_ENABLE, TIMER_IOS_STATE_DISABLE
                  deadtime: 0~255
                  outputautostate: TIMER_OUTAUTO_ENABLE, TIMER_OUTAUTO_DISABLE
                  protectmode: TIMER_CCHP0_PROT_OFF, TIMER_CCHP0_PROT_0, TIMER_CCHP0_PROT_1, TIMER_CCHP0_PROT_2
                  break0state: TIMER_BREAK0_ENABLE, TIMER_BREAK0_DISABLE
                  break0filter: 0~15
                  break0polarity: TIMER_BREAK0_POLARITY_LOW, TIMER_BREAK0_POLARITY_HIGH
                  break0lock: TIMER_BREAK0_LK_ENABLE, TIMER_BREAK0_LK_DISABLE
                  break0release: TIMER_BREAK0_RELEASE, TIMER_BREAK0_UNRELEASE
                  break1state: TIMER_BREAK1_ENABLE, TIMER_BREAK1_DISABLE
                  break1filter: 0~15
                  break1polarity: TIMER_BREAK1_POLARITY_LOW, TIMER_BREAK1_POLARITY_HIGH
                  break1lock: TIMER_BREAK1_LK_ENABLE, TIMER_BREAK1_LK_DISABLE
                  break1release: TIMER_BREAK1_RELEASE, TIMER_BREAK1_UNRELEASE
    \param[out] none
    \retval     none
*/
void timer_break_config(uint32_t timer_periph, timer_break_parameter_struct *breakpara)
{
    if((TIMER0 == timer_periph) || (TIMER7 == timer_periph) || (TIMER19 == timer_periph)) {
        TIMER_CCHP0(timer_periph) = (uint32_t)(((uint32_t)(breakpara->runoffstate)) |
                                               ((uint32_t)(breakpara->ideloffstate)) |
                                               ((uint32_t)(breakpara->deadtime)) |
                                               ((uint32_t)(breakpara->outputautostate)) |
                                               ((uint32_t)(breakpara->protectmode)) |
                                               ((uint32_t)(breakpara->break0state)) |
                                               ((uint32_t)(breakpara->break0filter)) |
                                               ((uint32_t)(breakpara->break0polarity)) |
                                               ((uint32_t)(breakpara->break0lock)) |
                                               ((uint32_t)(breakpara->break0release)) |
                                               ((uint32_t)(breakpara->break1state)) |
                                               ((uint32_t)(breakpara->break1filter)) |
                                               ((uint32_t)(breakpara->break1polarity)) |
                                               ((uint32_t)(breakpara->break1lock)) |
                                               ((uint32_t)(breakpara->break1release)));
    } else if((TIMER14 == timer_periph) || (TIMER15 == timer_periph) || (TIMER16 == timer_periph)) {
        TIMER_CCHP0(timer_periph) = (uint32_t)(((uint32_t)(breakpara->runoffstate)) |
                                               ((uint32_t)(breakpara->ideloffstate)) |
                                               ((uint32_t)(breakpara->deadtime)) |
                                               ((uint32_t)(breakpara->outputautostate)) |
                                               ((uint32_t)(breakpara->protectmode)) |
                                               ((uint32_t)(breakpara->break0state)) |
                                               ((uint32_t)(breakpara->break0filter)) |
                                               ((uint32_t)(breakpara->break0polarity)) |
                                               ((uint32_t)(breakpara->break0lock)) |
                                               ((uint32_t)(breakpara->break0release)));
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable TIMER break function
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  break_num: TIMER BREAKx
                only one parameter can be selected which is shown as below:
      \arg        TIMER_BREAK0: BREAK0 input signals, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BREAK1: BREAK1 input signals, TIMERx(x=0,7,19)
    \param[out] none
    \retval     none
*/
void timer_break_enable(uint32_t timer_periph, uint16_t break_num)
{
    if(TIMER_BREAK0 == break_num) {
        TIMER_CCHP0(timer_periph) |= (uint32_t)TIMER_CCHP0_BRK0EN;
    } else if(TIMER_BREAK1 == break_num) {
        TIMER_CCHP0(timer_periph) |= (uint32_t)TIMER_CCHP0_BRK1EN;
    } else {
    }
}

/*!
    \brief      disable TIMER break function
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  break_num: TIMER BREAKx
                only one parameter can be selected which is shown as below:
      \arg        TIMER_BREAK0: BREAK0 input signals, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BREAK1: BREAK1 input signals, TIMERx(x=0,7,19)
    \param[out] none
    \retval     none
*/
void timer_break_disable(uint32_t timer_periph, uint16_t break_num)
{
    if(TIMER_BREAK0 == break_num) {
        TIMER_CCHP0(timer_periph) &= (~(uint32_t)TIMER_CCHP0_BRK0EN);
    } else if(TIMER_BREAK1 == break_num) {
        TIMER_CCHP0(timer_periph) &= (~(uint32_t)TIMER_CCHP0_BRK1EN);
    } else {
    }
}

/*!
    \brief      enable TIMER output automatic function
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[out] none
    \retval     none
*/
void timer_automatic_output_enable(uint32_t timer_periph)
{
    TIMER_CCHP0(timer_periph) |= (uint32_t)TIMER_CCHP0_OAEN;
}

/*!
    \brief      disable TIMER output automatic function
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[out] none
    \retval     none
*/
void timer_automatic_output_disable(uint32_t timer_periph)
{
    TIMER_CCHP0(timer_periph) &= (~(uint32_t)TIMER_CCHP0_OAEN);
}

/*!
    \brief      configure TIMER primary output function
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_primary_output_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CCHP0(timer_periph) |= (uint32_t)TIMER_CCHP0_POEN;
    } else {
        TIMER_CCHP0(timer_periph) &= (~(uint32_t)TIMER_CCHP0_POEN);
    }
}

/*!
    \brief      configure channel commutation control shadow register
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_channel_control_shadow_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_CCSE;
    } else {
        TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_CCSE);
    }
}

/*!
    \brief      configure TIMER channel control shadow register update control
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  ccuctl: channel control shadow register update control
                only one parameter can be selected which is shown as below:
      \arg        TIMER_UPDATECTL_CCU: the shadow registers update by when CMTG bit is set
      \arg        TIMER_UPDATECTL_CCUTRI: the shadow registers update by when CMTG bit is set or an rising edge of TRGI occurs
      \arg        TIMER_UPDATECTL_CCUOVER: the shadow registers update by when the overflow event occurs
      \arg        TIMER_UPDATECTL_CCUUNDER: the shadow registers update by when the underflow event occurs
      \arg        TIMER_UPDATECTL_CCUOVERUNDER: the shadow registers update by when the overflow or underflow event occurs
    \param[out] none
    \retval     none
*/
void timer_channel_control_shadow_update_config(uint32_t timer_periph, uint32_t ccuctl)
{
    TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_CCUC);
    TIMER_CTL1(timer_periph) |= (uint32_t)ccuctl;
}

/*!
    \brief      initialize TIMER channel output parameter struct with a default value
    \param[in]  ocpara: TIMER channel n output parameter struct
    \param[out] none
    \retval     none
*/
void timer_channel_output_struct_para_init(timer_oc_parameter_struct *ocpara)
{
    /* initialize the channel output parameter struct member with the default value */
    ocpara->outputstate  = TIMER_CCX_DISABLE;
    ocpara->outputnstate = TIMER_CCXN_DISABLE;
    ocpara->ocpolarity   = TIMER_OC_POLARITY_HIGH;
    ocpara->ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    ocpara->ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    ocpara->ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
}

/*!
    \brief      configure TIMER channel output function
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
    \param[in]  ocpara: TIMER channel output parameter struct
                  outputstate: TIMER_CCX_ENABLE, TIMER_CCX_DISABLE
                  outputnstate: TIMER_CCXN_ENABLE, TIMER_CCXN_DISABLE
                  ocpolarity: TIMER_OC_POLARITY_HIGH, TIMER_OC_POLARITY_LOW
                  ocnpolarity: TIMER_OCN_POLARITY_HIGH, TIMER_OCN_POLARITY_LOW
                  ocidlestate: TIMER_OC_IDLE_STATE_LOW, TIMER_OC_IDLE_STATE_HIGH
                  ocnidlestate: TIMER_OCN_IDLE_STATE_LOW, TIMER_OCN_IDLE_STATE_HIGH
    \param[out] none
    \retval     none
*/
void timer_channel_output_config(uint32_t timer_periph, uint16_t channel, timer_oc_parameter_struct *ocpara)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpara->outputstate;
        /* reset the CH0P bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0P);
        /* set the CH0P bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpara->ocpolarity;

        if((TIMER0  == timer_periph) || (TIMER7  == timer_periph) || (TIMER19 == timer_periph) || \
                (TIMER14 == timer_periph) || (TIMER15 == timer_periph) || (TIMER16 == timer_periph)) {

            /* reset the MCH0EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH0EN);
            /* set the MCH0EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpara->outputnstate;

            /* reset the MCH0P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH0P);
            /* set the MCH0P bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpara->ocnpolarity;

            /* reset the ISO0 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO0);
            /* set the ISO0 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)ocpara->ocidlestate;

            /* reset the ISO0N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO0N);
            /* set the ISO0N bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)ocpara->ocnidlestate;
        }
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->outputstate) << 4U);
        /* reset the CH1P bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1P);
        /* set the CH1P bit */
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->ocpolarity) << 4U);

        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph) || (TIMER19 == timer_periph)) {
            /* reset the MCH1EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH1EN);
            /* set the MCH1EN bit */
            TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->outputnstate) << 4U);
            /* reset the MCH1P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH1P);
            /* set the MCH1P bit */
            TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->ocnpolarity) << 4U);
            /* reset the ISO1 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO1);
            /* set the ISO1 bit */
            TIMER_CTL1(timer_periph) |= ((uint32_t)(ocpara->ocidlestate) << 2U);
            /* reset the ISO1N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO1N);
            /* set the ISO1N bit */
            TIMER_CTL1(timer_periph) |= ((uint32_t)(ocpara->ocnidlestate) << 2U);
        }

        if(TIMER14 == timer_periph) {
            /* reset the ISO1 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO1);
            /* set the ISO1 bit */
            TIMER_CTL1(timer_periph) |= ((uint32_t)(ocpara->ocidlestate) << 2U);
        }

        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        /* reset the CH2EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);
        /* set the CH2EN bit */
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->outputstate) << 8U);
        /* reset the CH2P bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2P);
        /* set the CH2P bit */
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->ocpolarity) << 8U);

        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph) || (TIMER19 == timer_periph)) {
            /* reset the MCH2EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH2EN);
            /* set the MCH2EN bit */
            TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->outputnstate) << 8U);
            /* reset the MCH2P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH2P);
            /* set the MCH2P bit */
            TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->ocnpolarity) << 8U);
            /* reset the ISO2 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO2);
            /* set the ISO2 bit */
            TIMER_CTL1(timer_periph) |= ((uint32_t)(ocpara->ocidlestate) << 4U);
            /* reset the ISO2N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO2N);
            /* set the ISO2N bit */
            TIMER_CTL1(timer_periph) |= ((uint32_t)(ocpara->ocnidlestate) << 4U);
        }
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2MS);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        /* reset the CH3EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);
        /* set the CH3EN bit */
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->outputstate) << 12U);
        /* reset the CH3P bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3P);
        /* set the CH3P bit */
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->ocpolarity) << 12U);

        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph) || (TIMER19 == timer_periph)) {
            /* reset the MCH3EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH3EN);
            /* set the MCH3EN bit */
            TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->outputnstate) << 12U);
            /* reset the MCH3P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH3P);
            /* set the MCH3P bit */
            TIMER_CHCTL2(timer_periph) |= ((uint32_t)(ocpara->ocnpolarity) << 12U);
            /* reset the ISO3 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO3);
            /* set the ISO3 bit */
            TIMER_CTL1(timer_periph) |= ((uint32_t)(ocpara->ocidlestate) << 6U);
            /* reset the ISO3N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO3N);
            /* set the ISO3N bit */
            TIMER_CTL1(timer_periph) |= ((uint32_t)(ocpara->ocnidlestate) << 6U);
        }
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3MS);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output compare mode
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  ocmode: channel output compare mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_MODE_TIMING: timing mode
      \arg        TIMER_OC_MODE_ACTIVE: active mode
      \arg        TIMER_OC_MODE_INACTIVE: inactive mode
      \arg        TIMER_OC_MODE_TOGGLE: toggle mode
      \arg        TIMER_OC_MODE_LOW: force low mode
      \arg        TIMER_OC_MODE_HIGH: force high mode
      \arg        TIMER_OC_MODE_PWM0: PWM mode 0
      \arg        TIMER_OC_MODE_PWM1: PWM mode 1
      \arg        TIMER_OC_MODE_DSPM0: delayable SPM mode 0
      \arg        TIMER_OC_MODE_DSPM1: delayable SPM mode 1
      \arg        TIMER_OC_MODE_PULSE: pulse on compare(TIMERx(x=0~4,7,19), TIMER_CH_x(x=2~3))
      \arg        TIMER_OC_MODE_DIR: direction bit output(TIMERx(x=0~4,7,19), TIMER_CH_x(x=2~3))
    \param[out] none
    \retval     none
*/
void timer_channel_output_mode_config(uint32_t timer_periph, uint16_t channel, uint32_t ocmode)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMCTL);
        TIMER_CHCTL0(timer_periph) |= ocmode;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMCTL);
        TIMER_CHCTL0(timer_periph) |= ((ocmode) << 8U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMCTL);
        TIMER_CHCTL1(timer_periph) |= ocmode;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMCTL);
        TIMER_CHCTL1(timer_periph) |= ((ocmode) << 8U);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0COMCTL);
        TIMER_MCHCTL0(timer_periph) |= ocmode;
        break;
    /* configure TIMER_MCH_1 */
    case TIMER_MCH_1:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH1COMCTL);
        TIMER_MCHCTL0(timer_periph) |= ((ocmode) << 8U);
        break;
    /* configure TIMER_MCH_2 */
    case TIMER_MCH_2:
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH2COMCTL);
        TIMER_MCHCTL1(timer_periph) |= ocmode;
        break;
    /* configure TIMER_MCH_3 */
    case TIMER_MCH_3:
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH3COMCTL);
        TIMER_MCHCTL1(timer_periph) |= ((ocmode) << 8U);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output pulse value
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  pulse: the integer part of channel output pulse value
                  for TIMER_CH_x(x=0~3):
                    0~0xFFFF(adjustment mode disable, TIMERx(x=0,2,3,5~7,14~16,19))
                    0~0xFFFE(adjustment mode enable, TIMERx(x=0,2,3,5~7,14~16,19))
                    0~0xFFFFFFFF(adjustment mode disable, TIMERx(x=1,4))
                    0~0xFFFFFFE(adjustment mode enable, TIMERx(x=1,4))
                  for TIMER_MCH_x(x=0~3):
                    0~0xFFFF(TIMERx(x=0,7,14~16,19))
    \param[out] none
    \retval     none
*/
void timer_channel_output_pulse_value_config(uint32_t timer_periph, uint16_t channel, uint32_t pulse)
{
    uint32_t reg;

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        reg = TIMER_CH0CV(timer_periph);
        if((TIMER1  == timer_periph) || (TIMER4  == timer_periph)) {
            /* configure channel output value register with adjustment mode enable */
            if(TIMER_CTL0(timer_periph) & TIMER_CTL0_ADMEN) {
                reg &= (~(uint32_t)TIMER_CH0CV_CH0VAL_INTEGER_32);
            } else {
                reg &= (~(uint32_t)TIMER_CH0CV_CH0VAL_32);
            }
        } else {
            reg &= (~(uint32_t)TIMER_CH0CV_CH0VAL);
        }
        reg |= (uint32_t)pulse;
        TIMER_CH0CV(timer_periph) = reg;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        reg = TIMER_CH1CV(timer_periph);
        if((TIMER1  == timer_periph) || (TIMER4  == timer_periph)) {
            /* configure channel output value register with adjustment mode enable */
            if(TIMER_CTL0(timer_periph) & TIMER_CTL0_ADMEN) {
                reg &= (~(uint32_t)TIMER_CH1CV_CH1VAL_INTEGER_32);
            } else {
                reg &= (~(uint32_t)TIMER_CH1CV_CH1VAL_32);
            }
        } else {
            reg &= (~(uint32_t)TIMER_CH0CV_CH0VAL);
        }
        reg |= (uint32_t)pulse;
        TIMER_CH1CV(timer_periph) = reg;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        reg = TIMER_CH2CV(timer_periph);
        if((TIMER1  == timer_periph) || (TIMER4  == timer_periph)) {
            /* configure channel output value register with adjustment mode enable */
            if(TIMER_CTL0(timer_periph) & TIMER_CTL0_ADMEN) {
                reg &= (~(uint32_t)TIMER_CH2CV_CH2VAL_INTEGER_32);
            } else {
                reg &= (~(uint32_t)TIMER_CH2CV_CH2VAL_32);
            }
        } else {
            reg &= (~(uint32_t)TIMER_CH0CV_CH0VAL);
        }
        reg |= (uint32_t)pulse;
        TIMER_CH2CV(timer_periph) = reg;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        reg = TIMER_CH3CV(timer_periph);
        if((TIMER1  == timer_periph) || (TIMER4  == timer_periph)) {
            /* configure channel output value register with adjustment mode enable */
            if(TIMER_CTL0(timer_periph) & TIMER_CTL0_ADMEN) {
                reg &= (~(uint32_t)TIMER_CH3CV_CH3VAL_INTEGER_32);
            } else {
                reg &= (~(uint32_t)TIMER_CH3CV_CH3VAL_32);
            }
        } else {
            reg &= (~(uint32_t)TIMER_CH0CV_CH0VAL);
        }
        reg |= (uint32_t)pulse;
        TIMER_CH3CV(timer_periph) = reg;
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCH0CV(timer_periph) = (uint32_t)pulse;
        break;
    /* configure TIMER_MCH_1 */
    case TIMER_MCH_1:
        TIMER_MCH1CV(timer_periph) = (uint32_t)pulse;
        break;
    /* configure TIMER_MCH_2 */
    case TIMER_MCH_2:
        TIMER_MCH2CV(timer_periph) = (uint32_t)pulse;
        break;
    /* configure TIMER_MCH_3 */
    case TIMER_MCH_3:
        TIMER_MCH3CV(timer_periph) = (uint32_t)pulse;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel fractional part of output pulse value
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
    \param[in]  fract: the fractional part of channel output pulse value, 0~15
    \param[out] none
    \retval     none
*/
void timer_channel_output_pulse_fract_value_config(uint32_t timer_periph, uint16_t channel, uint32_t fract)
{
    uint32_t reg;

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        reg = TIMER_CH0CV(timer_periph);
        reg &= (~(uint32_t)TIMER_CH0CV_CH0VAL_FRACT);
        reg |= (uint32_t)(fract << 28U);
        TIMER_CH0CV(timer_periph) = reg;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        reg = TIMER_CH1CV(timer_periph);
        reg &= (~(uint32_t)TIMER_CH1CV_CH1VAL_FRACT);
        reg |= (uint32_t)(fract << 28U);
        TIMER_CH1CV(timer_periph) = reg;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        reg = TIMER_CH2CV(timer_periph);
        reg &= (~(uint32_t)TIMER_CH2CV_CH2VAL_FRACT);
        reg |= (uint32_t)(fract << 28U);
        TIMER_CH2CV(timer_periph) = reg;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        reg = TIMER_CH3CV(timer_periph);
        reg &= (~(uint32_t)TIMER_CH3CV_CH3VAL_FRACT);
        reg |= (uint32_t)(fract << 28U);
        TIMER_CH3CV(timer_periph) = reg;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output shadow function
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  ocshadow: channel output compare shadow
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_SHADOW_ENABLE: channel output compare shadow enable
      \arg        TIMER_OC_SHADOW_DISABLE: channel output compare shadow disable
      \arg        TIMER_OMC_SHADOW_ENABLE: multi mode channel output compare shadow enable
      \arg        TIMER_OMC_SHADOW_DISABLE: multi mode channel output compare shadow disable
    \param[out] none
    \retval     none
*/
void timer_channel_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMSEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)ocshadow;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMSEN);
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(ocshadow) << 8U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMSEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)ocshadow;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMSEN);
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)(ocshadow) << 8U);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0COMSEN);
        TIMER_MCHCTL0(timer_periph) |= (uint32_t)ocshadow;
        break;
    /* configure TIMER_MCH_1 */
    case TIMER_MCH_1:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH1COMSEN);
        TIMER_MCHCTL0(timer_periph) |= ((uint32_t)(ocshadow) << 8U);
        break;
    /* configure TIMER_MCH_2 */
    case TIMER_MCH_2:
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH2COMSEN);
        TIMER_MCHCTL1(timer_periph) |= (uint32_t)ocshadow;
        break;
    /* configure TIMER_MCH_3 */
    case TIMER_MCH_3:
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH3COMSEN);
        TIMER_MCHCTL1(timer_periph) |= ((uint32_t)(ocshadow) << 8U);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output clear function
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  occlear: channel output clear function
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_CLEAR_ENABLE: channel output clear function enable
      \arg        TIMER_OC_CLEAR_DISABLE: channel output clear function disable
      \arg        TIMER_OMC_CLEAR_ENABLE: multi mode channel output clear function enable
      \arg        TIMER_OMC_CLEAR_DISABLE: multi mode channel output clear function disable
    \param[out] none
    \retval     none
*/
void timer_channel_output_clear_config(uint32_t timer_periph, uint16_t channel, uint16_t occlear)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMCEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)occlear;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMCEN);
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)occlear << 8U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMCEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)occlear;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMCEN);
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)occlear << 8U);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0COMCEN);
        TIMER_MCHCTL0(timer_periph) |= (uint32_t)occlear;
        break;
    /* configure TIMER_MCH_1 */
    case TIMER_MCH_1:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH1COMCEN);
        TIMER_MCHCTL0(timer_periph) |= ((uint32_t)occlear << 8U);
        break;
    /* configure TIMER_MCH_2 */
    case TIMER_MCH_2:
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH2COMCEN);
        TIMER_MCHCTL1(timer_periph) |= (uint32_t)occlear;
        break;
    /* configure TIMER_MCH_3 */
    case TIMER_MCH_3:
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH3COMCEN);
        TIMER_MCHCTL1(timer_periph) |= ((uint32_t)occlear << 8U);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output compare fast function
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  ocfast: channel output compare fast function
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_FAST_ENABLE: channel output compare fast function enable
      \arg        TIMER_OC_FAST_DISABLE: channel output compare fast function disable
      \arg        TIMER_OMC_FAST_ENABLE: multi mode channel output compare fast function enable
      \arg        TIMER_OMC_FAST_DISABLE: multi mode channel output compare fast function disable
    \param[out] none
    \retval     none
*/
void timer_channel_output_compare_fast_config(uint32_t timer_periph, uint16_t channel, uint16_t ocfast)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMFEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)ocfast;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMFEN);
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)ocfast << 8U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMFEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)ocfast;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMFEN);
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)ocfast << 8U);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0COMFEN);
        TIMER_MCHCTL0(timer_periph) |= (uint32_t)ocfast;
        break;
    /* configure TIMER_MCH_1 */
    case TIMER_MCH_1:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH1COMFEN);
        TIMER_MCHCTL0(timer_periph) |= ((uint32_t)ocfast << 8U);
        break;
    /* configure TIMER_MCH_2 */
    case TIMER_MCH_2:
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH2COMFEN);
        TIMER_MCHCTL1(timer_periph) |= (uint32_t)ocfast;
        break;
    /* configure TIMER_MCH_3 */
    case TIMER_MCH_3:
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH3COMFEN);
        TIMER_MCHCTL1(timer_periph) |= ((uint32_t)ocfast << 8U);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output polarity
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  ocpolarity: channel output polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_POLARITY_HIGH: channel output polarity is high
      \arg        TIMER_OC_POLARITY_LOW: channel output polarity is low
      \arg        TIMER_OMC_POLARITY_HIGH: multi mode channel output polarity is high
      \arg        TIMER_OMC_POLARITY_LOW: multi mode channel output polarity is low
    \param[out] none
    \retval     none
*/
void timer_channel_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocpolarity)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0P);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpolarity;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1P);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocpolarity << 4U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2P);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocpolarity << 8U);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3P);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocpolarity << 12U);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)TIMER_MCHCTL2_MCH0FP);
        TIMER_MCHCTL2(timer_periph) |= (uint32_t)ocpolarity;
        break;
    /* configure TIMER_MCH_1 */
    case TIMER_MCH_1:
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)TIMER_MCHCTL2_MCH1FP);
        TIMER_MCHCTL2(timer_periph) |= ((uint32_t)ocpolarity << 2U);
        break;
    /* configure TIMER_MCH_2 */
    case TIMER_MCH_2:
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)TIMER_MCHCTL2_MCH2FP);
        TIMER_MCHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocpolarity << 4U);
        break;
    /* configure TIMER_MCH_3 */
    case TIMER_MCH_3:
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)TIMER_MCHCTL2_MCH3FP);
        TIMER_MCHCTL2(timer_periph) |= ((uint32_t)ocpolarity << 6U);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel complementary output polarity
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
    \param[in]  ocnpolarity: channel complementary output polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OCN_POLARITY_HIGH: channel complementary output polarity is high
      \arg        TIMER_OCN_POLARITY_LOW: channel complementary output polarity is low
    \param[out] none
    \retval     none
*/
void timer_channel_complementary_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnpolarity)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH0P);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocnpolarity;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH1P);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocnpolarity << 4U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH2P);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocnpolarity << 8U);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH3P);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocnpolarity << 12U);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel enable state
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  state: TIMER channel enable state
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CCX_ENABLE: channel enable
      \arg        TIMER_CCX_DISABLE: channel disable
      \arg        TIMER_MCCX_ENABLE: multi mode channel enable
      \arg        TIMER_MCCX_DISABLE: multi mode channel disable
    \param[out] none
    \retval     none
*/
void timer_channel_output_state_config(uint32_t timer_periph, uint16_t channel, uint32_t state)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)state;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)state << 4U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)state << 8U);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)state << 12U);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH0EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)state);
        break;
    /* configure TIMER_MCH_1 */
    case TIMER_MCH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH1EN);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(state << 4U));
        break;
    /* configure TIMER_MCH_2 */
    case TIMER_MCH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH2EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(state << 8U));
        break;
    /* configure TIMER_MCH_3 */
    case TIMER_MCH_3:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH3EN);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(state << 12U));
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel complementary output enable state
    \param[in]  timer_periph: TIMERx(x=0,7,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7,19))
    \param[in]  ocnstate: TIMER channel complementary output enable state
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CCXN_ENABLE: channel complementary enable
      \arg        TIMER_CCXN_DISABLE: channel complementary disable
    \param[out] none
    \retval     none
*/
void timer_channel_complementary_output_state_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnstate)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH0EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocnstate;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH1EN);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocnstate << 4U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH2EN);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocnstate << 8U);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH3EN);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocnstate << 12U);
        break;
    default:
        break;
    }
}

/*!
    \brief      initialize TIMER channel input parameter struct with a default value
    \param[in]  icpara: TIMER channel input parameter struct
    \param[out] none
    \retval     none
*/
void timer_channel_input_struct_para_init(timer_ic_parameter_struct *icpara)
{
    /* initialize the channel input parameter struct member with the default value */
    icpara->icpolarity  = TIMER_IC_POLARITY_RISING;
    icpara->icselection = TIMER_IC_SELECTION_DIRECTTI;
    icpara->icprescaler = TIMER_IC_PSC_DIV1;
    icpara->icfilter    = 0U;
}

/*!
    \brief      configure TIMER input capture parameter
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  icpara: TIMER channel input parameter struct
                  icpolarity: TIMER_IC_POLARITY_RISING, TIMER_IC_POLARITY_FALLING, TIMER_IC_POLARITY_BOTH_EDGE
                  icselection: TIMER_IC_SELECTION_DIRECTTI, TIMER_IC_SELECTION_INDIRECTTI, TIMER_IC_SELECTION_ITS, TIMER_IC_SELECTION_PAIR
                  icprescaler: TIMER_IC_PSC_DIV1, TIMER_IC_PSC_DIV2, TIMER_IC_PSC_DIV4, TIMER_IC_PSC_DIV8
                  icfilter: 0~15
    \param[out] none
    \retval     none
*/
void timer_input_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct *icpara)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);

        /* reset the CH0P and MCH0P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_MCH0P));
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(icpara->icpolarity);

        /* reset the CH0MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        if(TIMER_IC_SELECTION_PAIR == icpara->icselection) {
            TIMER_CHCTL0(timer_periph) |= ((uint32_t)icpara->icselection) << 28U;
        } else {
            TIMER_CHCTL0(timer_periph) |= (uint32_t)(icpara->icselection);
        }

        /* reset the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(icpara->icfilter) << 4U);

        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);

        /* reset the CH1P and MCH1P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_MCH1P));
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(icpara->icpolarity) << 4U);

        /* reset the CH1MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        if(TIMER_IC_SELECTION_PAIR == icpara->icselection) {
            TIMER_CHCTL0(timer_periph) |= ((uint32_t)icpara->icselection) << 29U;
        } else {
            TIMER_CHCTL0(timer_periph) |= (uint32_t)(icpara->icselection) << 8U;
        }

        /* reset the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(icpara->icfilter) << 12U);

        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        /* reset the CH2EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);

        /* reset the CH2P and MCH2P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH2P | TIMER_CHCTL2_MCH2P));
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(icpara->icpolarity) << 8U);

        /* reset the CH2MS bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2MS);
        if(TIMER_IC_SELECTION_PAIR == icpara->icselection) {
            TIMER_CHCTL1(timer_periph) |= ((uint32_t)icpara->icselection) << 28U;
        } else {
            TIMER_CHCTL1(timer_periph) |= (uint32_t)(icpara->icselection);
        }

        /* reset the CH2CAPFLT bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2CAPFLT);
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)(icpara->icfilter) << 4U);

        /* set the CH2EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH2EN;
        break;

    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        /* reset the CH3EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);

        /* reset the CH3P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH3P | TIMER_CHCTL2_MCH3P));
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(icpara->icpolarity) << 12U);

        /* reset the CH3MS bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3MS);
        if(TIMER_IC_SELECTION_PAIR == icpara->icselection) {
            TIMER_CHCTL1(timer_periph) |= ((uint32_t)icpara->icselection) << 29U;
        } else {
            TIMER_CHCTL1(timer_periph) |= ((uint32_t)icpara->icselection) << 8U;
        }

        /* reset the CH3CAPFLT bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3CAPFLT);
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)(icpara->icfilter) << 12U);

        /* set the CH3EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH3EN;
        break;

    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        /* reset the MCH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH0EN);

        /* reset the MCH0FP bits */
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)(TIMER_MCHCTL2_MCH0FP));
        switch(icpara->icpolarity) {
        case TIMER_IC_POLARITY_RISING:
            TIMER_MCHCTL2(timer_periph) |= TIMER_IMC_POLARITY_RISING;
            break;
        case TIMER_IC_POLARITY_FALLING:
            TIMER_MCHCTL2(timer_periph) |= TIMER_IMC_POLARITY_FALLING;
            break;
        case TIMER_IC_POLARITY_BOTH_EDGE:
            TIMER_MCHCTL2(timer_periph) |= TIMER_IMC_POLARITY_BOTH_EDGE;
            break;
        default:
            break;
        }

        /* reset the MCH0MS bit */
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0MS);
        if(TIMER_IC_SELECTION_PAIR == icpara->icselection) {
            TIMER_MCHCTL0(timer_periph) |= ((uint32_t)icpara->icselection << 28U);
        } else {
            TIMER_MCHCTL0(timer_periph) |= (uint32_t)(icpara->icselection);
        }

        /* reset the MCH0CAPFLT bit */
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0CAPFLT);
        TIMER_MCHCTL0(timer_periph) |= ((uint32_t)(icpara->icfilter) << 4U);

        /* set the MCH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_MCH0EN;
        break;

    /* configure TIMER_MCH_1 */
    case TIMER_MCH_1:
        /* reset the MCH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH1EN);

        /* reset the MCH1FP bits */
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)(TIMER_MCHCTL2_MCH1FP));
        switch(icpara->icpolarity) {
        case TIMER_IC_POLARITY_RISING:
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_RISING << 2U;
            break;
        case TIMER_IC_POLARITY_FALLING:
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_FALLING << 2U;
            break;
        case TIMER_IC_POLARITY_BOTH_EDGE:
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_BOTH_EDGE << 2U;
            break;
        default:
            break;
        }

        /* reset the MCH1MS bit */
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH1MS);
        if(TIMER_IC_SELECTION_PAIR == icpara->icselection) {
            TIMER_MCHCTL0(timer_periph) |= ((uint32_t)icpara->icselection << 29U);
        } else {
            TIMER_MCHCTL0(timer_periph) |= ((uint32_t)(icpara->icselection) << 8U);
        }

        /* reset the MCH1CAPFLT bit */
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH1CAPFLT);
        TIMER_MCHCTL0(timer_periph) |= ((uint32_t)(icpara->icfilter) << 12U);

        /* set the MCH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_MCH1EN;
        break;

    /* configure TIMER_MCH_2 */
    case TIMER_MCH_2:
        /* reset the MCH2EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH2EN);

        /* reset the MCH2FP bits */
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)(TIMER_MCHCTL2_MCH2FP));
        switch(icpara->icpolarity) {
        case TIMER_IC_POLARITY_RISING:
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_RISING << 4U;
            break;
        case TIMER_IC_POLARITY_FALLING:
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_FALLING << 4U;
            break;
        case TIMER_IC_POLARITY_BOTH_EDGE:
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_BOTH_EDGE << 4U;
            break;
        default:
            break;
        }

        /* reset the MCH2MS bit */
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH2MS);
        if(TIMER_IC_SELECTION_PAIR == icpara->icselection) {
            TIMER_MCHCTL1(timer_periph) |= ((uint32_t)icpara->icselection << 28U);
        } else {
            TIMER_MCHCTL1(timer_periph) |= ((uint32_t)(icpara->icselection));
        }

        /* reset the MCH2CAPFLT bit */
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH2CAPFLT);
        TIMER_MCHCTL1(timer_periph) |= ((uint32_t)(icpara->icfilter) << 4U);

        /* set the MCH2EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_MCH2EN;
        break;

    /* configure TIMER_MCH_3 */
    case TIMER_MCH_3:
        /* reset the MCH3EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH3EN);

        /* reset the MCH3FP bits */
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)(TIMER_MCHCTL2_MCH3FP));
        switch(icpara->icpolarity) {
        case TIMER_IC_POLARITY_RISING:
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_RISING << 6U;
            break;
        case TIMER_IC_POLARITY_FALLING:
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_FALLING << 6U;
            break;
        case TIMER_IC_POLARITY_BOTH_EDGE:
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_BOTH_EDGE << 6U;
            break;
        default:
            break;
        }

        /* reset the MCH3MS bit */
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH3MS);
        if(TIMER_IC_SELECTION_PAIR == icpara->icselection) {
            TIMER_MCHCTL1(timer_periph) |= ((uint32_t)icpara->icselection << 29U);
        } else {
            TIMER_MCHCTL1(timer_periph) |= ((uint32_t)(icpara->icselection) << 8U);
        }

        /* reset the MCH3CAPFLT bit */
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH3CAPFLT);
        TIMER_MCHCTL1(timer_periph) |= ((uint32_t)(icpara->icfilter) << 12U);

        /* set the MCH3EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_MCH3EN;
        break;
    default:
        break;
    }

    /* configure TIMER channel input capture prescaler value */
    timer_channel_input_capture_prescaler_config(timer_periph, channel, (uint16_t)(icpara->icprescaler));
}

/*!
    \brief      configure TIMER channel input capture prescaler value
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  prescaler: channel input capture prescaler value
                only one parameter can be selected which is shown as below:
      \arg        TIMER_IC_PSC_DIV1: no prescaler
      \arg        TIMER_IC_PSC_DIV2: divided by 2
      \arg        TIMER_IC_PSC_DIV4: divided by 4
      \arg        TIMER_IC_PSC_DIV8: divided by 8
    \param[out] none
    \retval     none
*/
void timer_channel_input_capture_prescaler_config(uint32_t timer_periph, uint16_t channel, uint16_t prescaler)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPPSC);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)prescaler;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPPSC);
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)prescaler << 8U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2CAPPSC);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)prescaler;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3CAPPSC);
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)prescaler << 8U);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0CAPPSC);
        TIMER_MCHCTL0(timer_periph) |= (uint32_t)prescaler;
        break;
    /* configure TIMER_MCH_1 */
    case TIMER_MCH_1:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH1CAPPSC);
        TIMER_MCHCTL0(timer_periph) |= ((uint32_t)prescaler << 8U);
        break;
    /* configure TIMER_MCH_2 */
    case TIMER_MCH_2:
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH2CAPPSC);
        TIMER_MCHCTL1(timer_periph) |= (uint32_t)prescaler;
        break;
    /* configure TIMER_MCH_3 */
    case TIMER_MCH_3:
        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH3CAPPSC);
        TIMER_MCHCTL1(timer_periph) |= ((uint32_t)prescaler << 8U);
        break;
    default:
        break;
    }
}

/*!
    \brief      read TIMER channel capture compare register value
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[out] none
    \retval     channel capture compare register value, 0~0xFFFFFFFF
*/
uint32_t timer_channel_capture_value_register_read(uint32_t timer_periph, uint16_t channel)
{
    uint32_t count_value = 0U;

    switch(channel) {
    case TIMER_CH_0:
        /* read TIMER_CH_0 capture compare register value */
        count_value = TIMER_CH0CV(timer_periph);
        break;
    case TIMER_CH_1:
        /* read TIMER_CH_1 capture compare register value */
        count_value = TIMER_CH1CV(timer_periph);
        break;
    case TIMER_CH_2:
        /* read TIMER_CH_2 capture compare register value */
        count_value = TIMER_CH2CV(timer_periph);
        break;
    case TIMER_CH_3:
        /* read TIMER_CH_3 capture compare register value */
        count_value = TIMER_CH3CV(timer_periph);
        break;
    case TIMER_MCH_0:
        /* read TIMER_MCH_0 capture compare register value */
        count_value = TIMER_MCH0CV(timer_periph);
        break;
    case TIMER_MCH_1:
        /* read TIMER_MCH_1 capture compare register value */
        count_value = TIMER_MCH1CV(timer_periph);
        break;
    case TIMER_MCH_2:
        /* read TIMER_MCH_2 capture compare register value */
        count_value = TIMER_MCH2CV(timer_periph);
        break;
    case TIMER_MCH_3:
        /* read TIMER_MCH_3 capture compare register value */
        count_value = TIMER_MCH3CV(timer_periph);
        break;
    default:
        break;
    }
    return (count_value);
}

/*!
    \brief      configure TIMER input pwm capture function
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0
      \arg        TIMER_CH_1: TIMER channel 1
     \param[in] icpwm: TIMER channel input pwm parameter struct
                  icpolarity: TIMER_IC_POLARITY_RISING, TIMER_IC_POLARITY_FALLING
                  icselection: TIMER_IC_SELECTION_DIRECTTI, TIMER_IC_SELECTION_INDIRECTTI
                  icprescaler: TIMER_IC_PSC_DIV1, TIMER_IC_PSC_DIV2, TIMER_IC_PSC_DIV4, TIMER_IC_PSC_DIV8
                  icfilter: 0~15
    \param[out] none
    \retval     none
*/
void timer_input_pwm_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct *icpwm)
{
    uint16_t icpolarity  = 0U;
    uint16_t icselection = 0U;

    /* set channel input polarity */
    if(TIMER_IC_POLARITY_RISING == icpwm->icpolarity) {
        icpolarity = TIMER_IC_POLARITY_FALLING;
    } else {
        icpolarity = TIMER_IC_POLARITY_RISING;
    }
    /* set channel input mode selection */
    if(TIMER_IC_SELECTION_DIRECTTI == icpwm->icselection) {
        icselection = TIMER_IC_SELECTION_INDIRECTTI;
    } else {
        icselection = TIMER_IC_SELECTION_DIRECTTI;
    }

    if(TIMER_CH_0 == channel) {
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        /* reset the CH0P and MCH0P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_MCH0P));
        /* set the CH0P and MCH0P bits */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(icpwm->icpolarity);
        /* reset the CH0MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        /* set the CH0MS bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(icpwm->icselection);
        /* reset the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        /* set the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(icpwm->icfilter) << 4U);
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_0, (uint16_t)(icpwm->icprescaler));

        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        /* reset the CH1P and MCH1P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_MCH1P));
        /* set the CH1P and MCH1P bits */
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)icpolarity << 4U);
        /* reset the CH1MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        /* set the CH1MS bit */
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)icselection << 8U);
        /* reset the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        /* set the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(icpwm->icfilter) << 12U);
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_1, (uint16_t)(icpwm->icprescaler));
    } else {
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        /* reset the CH1P and MCH1P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_MCH1P));
        /* set the CH1P and MCH1P bits */
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)(icpwm->icpolarity) << 4U);
        /* reset the CH1MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        /* set the CH1MS bit */
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(icpwm->icselection) << 8U);
        /* reset the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        /* set the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(icpwm->icfilter) << 12U);
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_1, (uint16_t)(icpwm->icprescaler));

        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        /* reset the CH0P and MCH0P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_MCH0P));
        /* set the CH0P and MCH0P bits */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)icpolarity;
        /* reset the CH0MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        /* set the CH0MS bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)icselection;
        /* reset the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        /* set the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(icpwm->icfilter) << 4U);
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_0, (uint16_t)(icpwm->icprescaler));
    }
}

/*!
    \brief      configure TIMER hall sensor mode
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  hallmode:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_HALLINTERFACE_ENABLE: TIMER hall sensor mode enable
      \arg        TIMER_HALLINTERFACE_DISABLE: TIMER hall sensor mode disable
    \param[out] none
    \retval     none
*/
void timer_hall_mode_config(uint32_t timer_periph, uint32_t hallmode)
{
    if(TIMER_HALLINTERFACE_ENABLE == hallmode) {
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_TI0S;
    } else if(TIMER_HALLINTERFACE_DISABLE == hallmode) {
        TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_TI0S);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      initialize TIMER multi mode channel output parameter struct
    \param[in]  omcpara: TIMER multi mode channel output parameter struct
    \param[out] none
    \retval     none
*/
void timer_multi_mode_channel_output_parameter_struct_init(timer_omc_parameter_struct *omcpara)
{
    /* initialize the multi mode channel output parameter struct with the default value */
    omcpara->outputmode  = TIMER_MCH_MODE_COMPLEMENTARY;
    omcpara->outputstate = TIMER_MCCX_DISABLE;
    omcpara->ocpolarity  = TIMER_OMC_POLARITY_LOW;
}

/*!
    \brief      configure TIMER multi mode channel output function
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  omcpara: TIMER multi mode channel output parameter struct
                  outputmode: TIMER_MCH_MODE_INDEPENDENTLY, TIMER_MCH_MODE_COMPLEMENTARY
                  outputstate: TIMER_MCCX_ENABLE, TIMER_MCCX_DISABLE
                  ocpolarity: TIMER_OMC_POLARITY_HIGH, TIMER_OMC_POLARITY_LOW
    \param[out] none
    \retval     none
*/
void timer_multi_mode_channel_output_config(uint32_t timer_periph, uint16_t channel, timer_omc_parameter_struct *omcpara)
{
    switch(channel) {
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_CTL2(timer_periph) &= (~(uint32_t)((uint32_t)TIMER_MCH_MODE_MASK << 20U));
        TIMER_CTL2(timer_periph) |= (uint32_t)((uint32_t)(omcpara->outputmode) << 20U);
        /* reset the MCH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH0EN);
        /* set the MCH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(omcpara->outputstate);
        /* reset the MCH0FP bit */
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)TIMER_MCHCTL2_MCH0FP);
        /* set the MCH0FP bit */
        TIMER_MCHCTL2(timer_periph) |= (uint32_t)omcpara->ocpolarity;

        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0MS);
        break;
    /* configure TIMER_MCH_1 */
    case TIMER_MCH_1:
        TIMER_CTL2(timer_periph) &= (~(uint32_t)((uint32_t)TIMER_MCH_MODE_MASK << 22U));
        TIMER_CTL2(timer_periph) |= (uint32_t)((uint32_t)(omcpara->outputmode) << 22U);
        /* reset the MCH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH1EN);
        /* set the MCH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(omcpara->outputstate) << 4U);
        /* reset the MCH1FP bit */
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)TIMER_MCHCTL2_MCH1FP);
        /* set the MCH1FP bit */
        TIMER_MCHCTL2(timer_periph) |= (uint32_t)((uint32_t)(omcpara->ocpolarity) << 2U);

        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH1MS);
        break;
    /* configure TIMER_MCH_2 */
    case TIMER_MCH_2:
        TIMER_CTL2(timer_periph) &= (~(uint32_t)((uint32_t)TIMER_MCH_MODE_MASK << 24U));
        TIMER_CTL2(timer_periph) |= (uint32_t)((uint32_t)(omcpara->outputmode) << 24U);
        /* reset the MCH2EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH2EN);
        /* set the MCH2EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(omcpara->outputstate) << 8U);
        /* reset the MCH2FP bit */
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)TIMER_MCHCTL2_MCH2FP);
        /* set the MCH2FP bit */
        TIMER_MCHCTL2(timer_periph) |= (uint32_t)((uint32_t)(omcpara->ocpolarity) << 4U);

        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH2MS);
        break;
    /* configure TIMER_MCH_3 */
    case TIMER_MCH_3:
        TIMER_CTL2(timer_periph) &= (~(uint32_t)((uint32_t)TIMER_MCH_MODE_MASK << 26U));
        TIMER_CTL2(timer_periph) |= (uint32_t)((uint32_t)(omcpara->outputmode)  << 26U);
        /* reset the MCH3EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH3EN);
        /* set the MCH3EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(omcpara->outputstate) << 12U);
        /* reset the MCH3FP bit */
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)TIMER_MCHCTL2_MCH3FP);
        /* set the MCH3FP bit */
        TIMER_MCHCTL2(timer_periph) |= (uint32_t)((uint32_t)(omcpara->ocpolarity) << 6U);

        TIMER_MCHCTL1(timer_periph) &= (~(uint32_t)TIMER_MCHCTL1_MCH3MS);
        break;
    default:
        break;
    }
}

/*!
    \brief      multi mode channel mode select
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=0,7,14~16,19))
      \arg        TIMER_MCH_1: TIMER multi mode channel 1(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_2: TIMER multi mode channel 2(TIMERx(x=0,7,19))
      \arg        TIMER_MCH_3: TIMER multi mode channel 3(TIMERx(x=0,7,19))
    \param[in]  multi_mode_sel: multi mode channel mode selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER_MCH_MODE_INDEPENDENTLY: multi mode channel work in independently mode
      \arg        TIMER_MCH_MODE_COMPLEMENTARY: multi mode channel work in complementary output mode
    \param[out] none
    \retval     none
*/
void timer_multi_mode_channel_mode_config(uint32_t timer_periph, uint32_t channel, uint32_t multi_mode_sel)
{
    uint32_t reg;
    reg = TIMER_CTL2(timer_periph);

    reg &= (~(uint32_t)((uint32_t)TIMER_MCH_MODE_MASK << (((channel & 0xFU) << 1U) + 20U)));
    reg |= (uint32_t)(multi_mode_sel << (((channel & 0xFU) << 1U) + 20U));

    TIMER_CTL2(timer_periph) = reg;
}

/*!
    \brief      select TIMER input trigger source
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19)
    \param[in]  intrigger: input trigger source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SMCFG_TRGSEL_ITI0: internal trigger 0(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_ITI1: internal trigger 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_ITI2: internal trigger 2(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_ITI3: internal trigger 3(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_CI0F_ED: TI0 edge detector(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_CI0FE0: filtered channel 0 input(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_CI1FE1: filtered channel 1 input(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_ETIFP: filtered external trigger input(TIMERx(x=0~4,7,19))
      \arg        TIMER_SMCFG_TRGSEL_ITI4: internal trigger 4(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_ITI5: internal trigger 5(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_ITI6: internal trigger 6(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_ITI7: internal trigger 7(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_ITI8: internal trigger 8(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_ITI9: internal trigger 9(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_ITI10: internal trigger 10(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_ITI14: internal trigger 14(TIMERx(x=0~4,7,14,19))
    \param[out] none
    \retval     none
*/
void timer_input_trigger_source_select(uint32_t timer_periph, uint32_t intrigger)
{
    uint8_t timerx_temp = 0U;
    uint32_t timer_base_addr = 0U;
    uint32_t reg_temp;
    uint32_t i = 0U;
    uint32_t j = 0U;
    uint32_t j_temp = 0U;
    uint32_t TIMERxCFG0_value, TIMERxCFG1_value, TIMERxCFG2_value;

    switch(timer_periph) {
    case TIMER0:
        timerx_temp = SYSCFG_TIMER0;
        break;
    case TIMER1:
        timerx_temp = SYSCFG_TIMER1;
        break;
    case TIMER2:
        timerx_temp = SYSCFG_TIMER2;
        break;
    case TIMER3:
        timerx_temp = SYSCFG_TIMER3;
        break;
    case TIMER4:
        timerx_temp = SYSCFG_TIMER4;
        break;
    case TIMER7:
        timerx_temp = SYSCFG_TIMER7;
        break;
    case TIMER14:
        timerx_temp = SYSCFG_TIMER14;
        break;
    case TIMER19:
        timerx_temp = SYSCFG_TIMER19;
        break;
    default:
        break;
    }

    timer_base_addr = SYSCFG_TIMERCFG(timerx_temp);

    /* read SYSCFG_TIMERCFG0 register value */
    TIMERxCFG0_value = REG32(timer_base_addr) & 0x7FFF7FFFU;
    /* read SYSCFG_TIMERCFG1 register value */
    TIMERxCFG1_value = REG32(timer_base_addr + 4U) & 0x7FFF7FFFU;
    /* read SYSCFG_TIMERCFG2 register value */
    TIMERxCFG2_value = REG32(timer_base_addr + 8U) & 0x7FFF7FFFU;

    if((0U == TIMERxCFG0_value) && (0U == TIMERxCFG1_value) && (0U == TIMERxCFG2_value)) {
        REG32(timer_base_addr + 8U) = (uint32_t)(intrigger) << 16U;
    } else {
        for(i = 0U; i < 0x0CU; i += 4U) {
            if((REG32(timer_base_addr + i) & 0x7FFF7FFFU) != 0x00000000U) {
                j = 0U;
                reg_temp = REG32(timer_base_addr + i) & 0x7FFFU;
                if(0U == reg_temp) {
                    j = 16U;
                    reg_temp = (REG32(timer_base_addr + i) & 0x7FFF0000U);
                }
                j_temp = j;
                for(j = j_temp; j < 31U; j += 5U) {
                    if(reg_temp & (0x1FU << j)) {
                        REG32(timer_base_addr + i) = (uint32_t)(intrigger) << j;
                        break;
                    }
                }

                break;
            }
        }
    }
}

/*!
    \brief      select TIMER master mode output 0 trigger source
    \param[in]  timer_periph: TIMERx(x=0~7,14,19)
    \param[in]  outrigger: trigger output 0 source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_TRI_OUT0_SRC_RESET: the UPG bit as trigger output 0(TIMERx(x=0~7,14,19))
      \arg        TIMER_TRI_OUT0_SRC_ENABLE: the counter enable signal as trigger output 0(TIMERx(x=0~7,14,19))
      \arg        TIMER_TRI_OUT0_SRC_UPDATE: update event as trigger output 0(TIMERx(x=0~7,14,19))
      \arg        TIMER_TRI_OUT0_SRC_CH0: a capture or a compare match occurred in channel 0 as trigger output 0(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_TRI_OUT0_SRC_O0CPRE: O0CPRE as trigger output 0(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_TRI_OUT0_SRC_O1CPRE: O1CPRE as trigger output 0(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_TRI_OUT0_SRC_O2CPRE: O2CPRE as trigger output 0(TIMERx(x=0~4,7,19))
      \arg        TIMER_TRI_OUT0_SRC_O3CPRE: O3CPRE as trigger output 0(TIMERx(x=0~4,7,19))
      \arg        TIMER_TRI_OUT0_SRC_DECODER_CLOCK: decoder clock as trigger output 0(TIMERx(x=0~4,7,19))
      \arg        TIMER_TRI_OUT0_SRC_SYNC: synchronization event as trigger output 0(TIMERx(x=0,7,19))
    \param[out] none
    \retval     none
*/
void timer_master_output0_trigger_source_select(uint32_t timer_periph, uint32_t outrigger)
{
    uint32_t reg;

    reg  = TIMER_CTL1(timer_periph);
    reg &= (~(uint32_t)TIMER_CTL1_MMC0);
    reg |= (uint32_t)outrigger;
    TIMER_CTL1(timer_periph) = reg;
}

/*!
    \brief      select TIMER master mode output 1 trigger source
    \param[in]  timer_periph: TIMERx(x=0,7,19)
    \param[in]  outrigger: trigger output 1 source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_TRI_OUT1_SRC_RESET: the UPG bit as trigger output 1
      \arg        TIMER_TRI_OUT1_SRC_ENABLE: the counter enable signal TIMER_CTL0_CEN as trigger output 1
      \arg        TIMER_TRI_OUT1_SRC_UPDATE: update event as trigger output 1
      \arg        TIMER_TRI_OUT1_SRC_CH0: a capture or a compare match occurred in channel 0 as trigger output 1
      \arg        TIMER_TRI_OUT1_SRC_O0CPRE: O0CPRE as trigger output 1
      \arg        TIMER_TRI_OUT1_SRC_O1CPRE: O1CPRE as trigger output 1
      \arg        TIMER_TRI_OUT1_SRC_O2CPRE: O2CPRE as trigger output 1
      \arg        TIMER_TRI_OUT1_SRC_O3CPRE: O3CPRE as trigger output 1
    \param[out] none
    \retval     none
*/
void timer_master_output1_trigger_source_select(uint32_t timer_periph, uint32_t outrigger)
{
    uint32_t reg;

    reg  = TIMER_CTL1(timer_periph);
    reg &= (~(uint32_t)TIMER_CTL1_MMC1);
    reg |= (uint32_t)outrigger;
    TIMER_CTL1(timer_periph) = reg;
}

/*!
    \brief      select TIMER slave mode
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19)
    \param[in]  slavemode: slave mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SLAVE_MODE_DISABLE: slave mode disable(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_QUAD_DECODER_MODE0: quadrature decoder mode 0(TIMERx(x=0~4,7,19))
      \arg        TIMER_QUAD_DECODER_MODE1: quadrature decoder mode 1(TIMERx(x=0~4,7,19))
      \arg        TIMER_QUAD_DECODER_MODE2: quadrature decoder mode 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_SLAVE_MODE_RESTART: restart mode(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SLAVE_MODE_PAUSE: pause mode(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SLAVE_MODE_EVENT: event mode(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SLAVE_MODE_EXTERNAL0: external clock mode 0(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SLAVE_MODE_RESTART_EVENT: restart + event mode(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SLAVE_MODE_PAUSE_RESTART: pause + restart mode(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_DECODER_MODE0: decoder mode 0(TIMERx(x=0~4,7,19))
      \arg        TIMER_DECODER_MODE1: decoder mode 1(TIMERx(x=0~4,7,19))
      \arg        TIMER_DECODER_MODE2: decoder mode 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_DECODER_MODE3: decoder mode 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_QUAD_DECODER_MODE3: quadrature decoder mode 3(TIMERx(x=0~4,7,19))
      \arg        TIMER_QUAD_DECODER_MODE4: quadrature decoder mode 4(TIMERx(x=0~4,7,19))
    \param[out] none
    \retval     none
*/
void timer_slave_mode_select(uint32_t timer_periph, uint32_t slavemode)
{
    uint32_t timerx_temp = 0U;
    uint32_t timerxcfg_addr = 0U;
    uint32_t timer_base_addr = 0U;
    uint32_t trigger_temp = 0U;
    uint32_t trigger_off = 0U;
    uint32_t reg_temp;
    uint32_t i = 0U;
    uint32_t j = 0U;
    uint32_t TIMERxCFG0_value, TIMERxCFG1_value, TIMERxCFG2_value;

    switch(timer_periph) {
    case TIMER0:
        timerx_temp = SYSCFG_TIMER0;
        break;
    case TIMER1:
        timerx_temp = SYSCFG_TIMER1;
        break;
    case TIMER2:
        timerx_temp = SYSCFG_TIMER2;
        break;
    case TIMER3:
        timerx_temp = SYSCFG_TIMER3;
        break;
    case TIMER4:
        timerx_temp = SYSCFG_TIMER4;
        break;
    case TIMER7:
        timerx_temp = SYSCFG_TIMER7;
        break;
    case TIMER14:
        timerx_temp = SYSCFG_TIMER14;
        break;
    case TIMER19:
        timerx_temp = SYSCFG_TIMER19;
        break;
    default:
        break;
    }

    timer_base_addr = SYSCFG_TIMERCFG(timerx_temp);
    timerxcfg_addr = (timer_base_addr + (slavemode / 6U) * 4U);
    trigger_off = (((slavemode / 3U) * 16U) + ((slavemode % 3U) * 5U)) % 32U;

    /* read SYSCFG_TIMERCFG0 register value */
    TIMERxCFG0_value = REG32(timer_base_addr) & 0x7FFF7FFFU;
    /* read SYSCFG_TIMERCFG1 register value */
    TIMERxCFG1_value = REG32(timer_base_addr + 4U) & 0x7FFF7FFFU;
    /* read SYSCFG_TIMERCFG2 register value */
    TIMERxCFG2_value = REG32(timer_base_addr + 8U) & 0x7FFF7FFFU;

    if((0U == TIMERxCFG0_value) && (0U == TIMERxCFG1_value) && (0U == TIMERxCFG2_value)) {
        trigger_temp = 0x1FU;
    } else {
        for(i = 0U; i < 0x0CU; i += 4U) {
            if((REG32(timer_base_addr + i) & 0x7FFF7FFFU) != 0x00000000U) {
                reg_temp = REG32(timer_base_addr + i) & 0x7FFFU;
                if(reg_temp == 0U) {
                    reg_temp = (REG32(timer_base_addr + i) & 0x7FFF0000U) >> 16U;
                }
                for(j = 0U; j < 15U; j += 5U) {
                    trigger_temp = (reg_temp >> j) & 0x1FU;
                    if(trigger_temp != 0U) {
                        break;
                    }
                }
                REG32(timer_base_addr + i) = 0x00000000U;
                break;
            }
        }
    }
    REG32(timerxcfg_addr) = trigger_temp << trigger_off;
}

/*!
    \brief      configure TIMER pause+reset mode reset polarity
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19)
    \param[in]  rstpolarity: reset polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CNT_RESET_ON_FALLING_EDGE: counter is reset on falling edge
      \arg        TIMER_CNT_RESET_ON_RISING_EDGE: counter is reset on rising edge
    \param[out] none
    \retval     none
*/
void timer_pause_reset_polarity_config(uint32_t timer_periph, uint32_t rstpolarity)
{
    if(TIMER_CNT_RESET_ON_RISING_EDGE == rstpolarity) {
        TIMER_SMCFG(timer_periph) |= TIMER_SMCFG_PRMRPSEL;
    } else {
        TIMER_SMCFG(timer_periph) &= (~(uint32_t)TIMER_SMCFG_PRMRPSEL);
    }
}

/*!
    \brief      configure TIMER master slave mode
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19)
    \param[in]  masterslave: master slave mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_MASTER_SLAVE_MODE_ENABLE: master slave mode enable
      \arg        TIMER_MASTER_SLAVE_MODE_DISABLE: master slave mode disable
    \param[out] none
    \retval     none
*/
void timer_master_slave_mode_config(uint32_t timer_periph, uint32_t masterslave)
{
    if(TIMER_MASTER_SLAVE_MODE_ENABLE == masterslave) {
        TIMER_SMCFG(timer_periph) |= (uint32_t)TIMER_SMCFG_MSM;
    } else if(TIMER_MASTER_SLAVE_MODE_DISABLE == masterslave) {
        TIMER_SMCFG(timer_periph) &= (~(uint32_t)TIMER_SMCFG_MSM);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure TIMER external trigger input
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  extprescaler: external trigger prescaler
                only one parameter can be selected which is shown as below:
      \arg        TIMER_EXT_TRI_PSC_OFF: no divided
      \arg        TIMER_EXT_TRI_PSC_DIV2: divided by 2
      \arg        TIMER_EXT_TRI_PSC_DIV4: divided by 4
      \arg        TIMER_EXT_TRI_PSC_DIV8: divided by 8
    \param[in]  extpolarity: external trigger polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_ETP_FALLING: active low or falling edge active
      \arg        TIMER_ETP_RISING: active high or rising edge active
    \param[in]  extfilter: a value between 0 and 15
    \param[out] none
    \retval     none
*/
void timer_external_trigger_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter)
{
    TIMER_SMCFG(timer_periph) &= (~(uint32_t)(TIMER_SMCFG_ETP | TIMER_SMCFG_ETPSC | TIMER_SMCFG_ETFC));
    TIMER_SMCFG(timer_periph) |= (uint32_t)(extprescaler | extpolarity);
    TIMER_SMCFG(timer_periph) |= (uint32_t)(extfilter << 8U);
}

/*!
    \brief      configure TIMER quadrature decoder mode
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  decomode: quadrature decoder mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_QUAD_DECODER_MODE0: counter counts on CI0FE0 edge depending on CI1FE1 level
      \arg        TIMER_QUAD_DECODER_MODE1: counter counts on CI1FE1 edge depending on CI0FE0 level
      \arg        TIMER_QUAD_DECODER_MODE2: counter counts on both CI0FE0 and CI1FE1 edges depending on the level of the other input
      \arg        TIMER_QUAD_DECODER_MODE3: counter counts on CI0FE0 edge depending on CI0FE0 level
      \arg        TIMER_QUAD_DECODER_MODE4: counter counts on CI1FE1 edge depending on CI1FE1 level
    \param[in]  ic0polarity: input capture polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_IC_POLARITY_RISING: capture rising edge
      \arg        TIMER_IC_POLARITY_FALLING: capture falling edge
      \arg        TIMER_IC_POLARITY_BOTH_EDGE: active both edge
    \param[in]  ic1polarity: input capture polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_IC_POLARITY_RISING: capture rising edge
      \arg        TIMER_IC_POLARITY_FALLING: capture falling edge
      \arg        TIMER_IC_POLARITY_BOTH_EDGE: active both edge
    \param[out] none
    \retval     none
*/
void timer_quadrature_decoder_mode_config(uint32_t timer_periph, uint32_t decomode, uint16_t ic0polarity, uint16_t ic1polarity)
{
    /* configure the quadrature decoder mode */
    timer_slave_mode_select(timer_periph, decomode);

    /* configure input capture selection */
    TIMER_CHCTL0(timer_periph) &= (uint32_t)(((~(uint32_t)TIMER_CHCTL0_CH0MS)) & ((~(uint32_t)TIMER_CHCTL0_CH1MS)));
    TIMER_CHCTL0(timer_periph) |= (uint32_t)(TIMER_IC_SELECTION_DIRECTTI | ((uint32_t)TIMER_IC_SELECTION_DIRECTTI << 8U));

    /* configure channel input capture polarity */
    if((TIMER0  == timer_periph) || (TIMER7  == timer_periph) || (TIMER19 == timer_periph)) {
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_MCH0P));
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_MCH1P));
    } else if((TIMER1  == timer_periph) || (TIMER2  == timer_periph) || (TIMER3 == timer_periph) || (TIMER4 == timer_periph)) {
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
    } else {
        /* illegal parameters */
    }
    TIMER_CHCTL2(timer_periph) |= ((uint32_t)ic0polarity | ((uint32_t)ic1polarity << 4U));
}

/*!
    \brief      configure TIMER decoder mode
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  decomode: decoder mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_DECODER_MODE0: decoder mode 0
      \arg        TIMER_DECODER_MODE1: decoder mode 1
      \arg        TIMER_DECODER_MODE2: decoder mode 2
      \arg        TIMER_DECODER_MODE3: decoder mode 3
    \param[in]  ic0polarity: input capture polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_IC_POLARITY_RISING: capture rising edge
      \arg        TIMER_IC_POLARITY_FALLING: capture falling edge
      \arg        TIMER_IC_POLARITY_BOTH_EDGE: active both edge
    \param[in]  ic1polarity: input capture polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_IC_POLARITY_RISING: capture rising edge
      \arg        TIMER_IC_POLARITY_FALLING: capture falling edge
      \arg        TIMER_IC_POLARITY_BOTH_EDGE: active both edge
    \param[out] none
    \retval     none
*/
void timer_decoder_mode_config(uint32_t timer_periph, uint32_t decomode, uint16_t ic0polarity, uint16_t ic1polarity)
{
    /* configure the quadrature decoder mode */
    timer_slave_mode_select(timer_periph, decomode);

    /* configure input capture selection */
    TIMER_CHCTL0(timer_periph) &= (uint32_t)(((~(uint32_t)TIMER_CHCTL0_CH0MS)) & ((~(uint32_t)TIMER_CHCTL0_CH1MS)));
    TIMER_CHCTL0(timer_periph) |= (uint32_t)(TIMER_IC_SELECTION_DIRECTTI | ((uint32_t)TIMER_IC_SELECTION_DIRECTTI << 8U));

    /* configure channel input capture polarity */
    if((TIMER0  == timer_periph) || (TIMER7  == timer_periph) || (TIMER19 == timer_periph)) {
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_MCH0P));
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_MCH1P));
    } else if((TIMER1  == timer_periph) || (TIMER2  == timer_periph) || (TIMER3 == timer_periph) || (TIMER4 == timer_periph)) {
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
    } else {
        /* illegal parameters */
    }
    TIMER_CHCTL2(timer_periph) |= ((uint32_t)ic0polarity | ((uint32_t)ic1polarity << 4U));
}

/*!
    \brief      configure TIMER internal clock mode
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19)
    \param[out] none
    \retval     none
*/
void timer_internal_clock_config(uint32_t timer_periph)
{
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_DISABLE);
}

/*!
    \brief      configure TIMER the internal trigger as external clock input
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19)
    \param[in]  intrigger: internal trigger selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SMCFG_TRGSEL_ITI0: internal trigger 0
      \arg        TIMER_SMCFG_TRGSEL_ITI1: internal trigger 1
      \arg        TIMER_SMCFG_TRGSEL_ITI2: internal trigger 2
      \arg        TIMER_SMCFG_TRGSEL_ITI3: internal trigger 3
      \arg        TIMER_SMCFG_TRGSEL_ITI4: internal trigger 4
      \arg        TIMER_SMCFG_TRGSEL_ITI5: internal trigger 5
      \arg        TIMER_SMCFG_TRGSEL_ITI6: internal trigger 6
      \arg        TIMER_SMCFG_TRGSEL_ITI7: internal trigger 7
      \arg        TIMER_SMCFG_TRGSEL_ITI8: internal trigger 8
      \arg        TIMER_SMCFG_TRGSEL_ITI9: internal trigger 9
      \arg        TIMER_SMCFG_TRGSEL_ITI10: internal trigger 10
      \arg        TIMER_SMCFG_TRGSEL_ITI14: internal trigger 14
    \param[out] none
    \retval     none
*/
void timer_internal_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t intrigger)
{
    /* select TIMER slave mode */
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_EXTERNAL0);
    /* select TIMER input trigger source */
    timer_input_trigger_source_select(timer_periph, intrigger);
}

/*!
    \brief      configure TIMER the external trigger as external clock input
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19)
    \param[in]  extrigger: external trigger selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SMCFG_TRGSEL_CI0F_ED: TI0 edge detector(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_CI0FE0: filtered channel 0 input(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_SMCFG_TRGSEL_CI1FE1: filtered channel 1 input(TIMERx(x=0~4,7,14,19))
    \param[in]  extpolarity: external input capture polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_IC_POLARITY_RISING: active high or rising edge active
      \arg        TIMER_IC_POLARITY_FALLING: active low or falling edge active
      \arg        TIMER_IC_POLARITY_BOTH_EDGE: active both edge
    \param[in]  extfilter: a value between 0 and 15
    \param[out] none
    \retval     none
*/
void timer_external_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t extrigger, uint16_t extpolarity, uint32_t extfilter)
{
    if(TIMER_SMCFG_TRGSEL_CI1FE1 == extrigger) {
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        /* reset the CH1P and MCH1P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_MCH1P));
        /* set the CH1P and MCH1P bits */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)extpolarity << 4U);
        /* reset the CH1MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        /* set the CH1MS bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)TIMER_IC_SELECTION_DIRECTTI << 8U);
        /* reset the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        /* set the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(extfilter << 12U);
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
    } else {
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        /* reset the CH0P and MCH0P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_MCH0P));
        /* set the CH0P and MCH0P bits */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)extpolarity;
        /* reset the CH0MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        /* set the CH0MS bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)TIMER_IC_SELECTION_DIRECTTI;
        /* reset the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        /* reset the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(extfilter << 4U);
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
    }

    /* select TIMER slave mode */
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_EXTERNAL0);
    /* select TIMER input trigger source */
    timer_input_trigger_source_select(timer_periph, extrigger);
}

/*!
    \brief      configure TIMER the external clock mode0
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19)
    \param[in]  extprescaler: external trigger prescaler
                only one parameter can be selected which is shown as below:
      \arg        TIMER_EXT_TRI_PSC_OFF: no divided
      \arg        TIMER_EXT_TRI_PSC_DIV2: divided by 2
      \arg        TIMER_EXT_TRI_PSC_DIV4: divided by 4
      \arg        TIMER_EXT_TRI_PSC_DIV8: divided by 8
    \param[in]  extpolarity: external input capture polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_ETP_FALLING: active low or falling edge active
      \arg        TIMER_ETP_RISING: active high or rising edge active
    \param[in]  extfilter: a value between 0 and 15
    \param[out] none
    \retval     none
*/
void timer_external_clock_mode0_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter)
{
    /* configure TIMER external trigger input */
    timer_external_trigger_config(timer_periph, extprescaler, extpolarity, extfilter);
    /* select TIMER slave mode */
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_EXTERNAL0);
    /* select TIMER input trigger source */
    timer_input_trigger_source_select(timer_periph, TIMER_SMCFG_TRGSEL_ETIFP);
}

/*!
    \brief      configure TIMER the external clock mode1
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  extprescaler: external trigger prescaler
                only one parameter can be selected which is shown as below:
      \arg        TIMER_EXT_TRI_PSC_OFF: no divided
      \arg        TIMER_EXT_TRI_PSC_DIV2: divided by 2
      \arg        TIMER_EXT_TRI_PSC_DIV4: divided by 4
      \arg        TIMER_EXT_TRI_PSC_DIV8: divided by 8
    \param[in]  extpolarity: external input capture polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_ETP_FALLING: active low or falling edge active
      \arg        TIMER_ETP_RISING: active high or rising edge active
    \param[in]  extfilter: a value between 0 and 15
    \param[out] none
    \retval     none
*/
void timer_external_clock_mode1_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter)
{
    /* configure TIMER external trigger input */
    timer_external_trigger_config(timer_periph, extprescaler, extpolarity, extfilter);
    TIMER_SMCFG(timer_periph) |= (uint32_t)TIMER_SMCFG_SMC1;
}

/*!
    \brief      disable TIMER the external clock mode1
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[out] none
    \retval     none
*/
void timer_external_clock_mode1_disable(uint32_t timer_periph)
{
    TIMER_SMCFG(timer_periph) &= (~(uint32_t)TIMER_SMCFG_SMC1);
}

/*!
    \brief      configure TIMER write CHxVAL register selection
    \param[in]  timer_periph: TIMERx(x=0~4,14~16,19)
    \param[in]  ccsel: write CHxVAL register selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CHVSEL_DISABLE: no effect
      \arg        TIMER_CHVSEL_ENABLE: when write the CHxVAL register, if the write value is same as the CHxVAL value, the write access is ignored
    \param[out] none
    \retval     none
*/
void timer_write_chxval_register_config(uint32_t timer_periph, uint16_t ccsel)
{
    if(TIMER_CHVSEL_ENABLE == ccsel) {
        TIMER_CFG(timer_periph) |= (uint32_t)TIMER_CFG_CHVSEL;
    } else if(TIMER_CHVSEL_DISABLE == ccsel) {
        TIMER_CFG(timer_periph) &= (~(uint32_t)TIMER_CFG_CHVSEL);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure TIMER output value selection
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  outsel: output value selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OUTSEL_DISABLE: no effect
      \arg        TIMER_OUTSEL_ENABLE: if POEN and IOS is 0, the output disabled
    \param[out] none
    \retval     none
*/
void timer_output_value_selection_config(uint32_t timer_periph, uint16_t outsel)
{
    if(TIMER_OUTSEL_ENABLE == outsel) {
        TIMER_CFG(timer_periph) |= (uint32_t)TIMER_CFG_OUTSEL;
    } else if(TIMER_OUTSEL_DISABLE == outsel) {
        TIMER_CFG(timer_periph) &= (~(uint32_t)TIMER_CFG_OUTSEL);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure commutation control shadow register update selection
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  cssel: commutation control shadow register selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CCUSEL_DISABLE: the shadow registers update when the counter generates an overflow/ underflow event
      \arg        TIMER_CCUSEL_ENABLE: the shadow registers update when the counter generates an overflow/ underflow event and the repetition counter value is zero
    \param[out] none
    \retval     none
*/
void timer_commutation_control_shadow_register_config(uint32_t timer_periph, uint16_t ccssel)
{
    if(TIMER_CCUSEL_ENABLE == ccssel) {
        TIMER_CFG(timer_periph) |= (uint32_t)TIMER_CFG_CCUSEL;
    } else if(TIMER_CCUSEL_DISABLE == ccssel) {
        TIMER_CFG(timer_periph) &= (~(uint32_t)TIMER_CFG_CCUSEL);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure TIMER output match pulse selection
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19))
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
    \param[in]  pulsesel: output match pulse selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER_PULSE_OUTPUT_NORMAL: channel output normal
      \arg        TIMER_PULSE_OUTPUT_CNT_UP: pulse output only when counting up
      \arg        TIMER_PULSE_OUTPUT_CNT_DOWN: pulse output only when counting down
      \arg        TIMER_PULSE_OUTPUT_CNT_BOTH: pulse output when counting up or down
    \param[out] none
    \retval     none
*/
void timer_output_match_pulse_select(uint32_t timer_periph, uint32_t channel, uint16_t pulsesel)
{
    uint32_t reg;
    reg  = TIMER_CTL2(timer_periph);

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        reg &= (~(uint32_t)((uint32_t)TIMER_PULSE_OUTPUT_MASK << 8U));
        reg |= (uint32_t)((uint32_t)pulsesel << 8U);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        reg &= (~(uint32_t)((uint32_t)TIMER_PULSE_OUTPUT_MASK << 10U));
        reg |= (uint32_t)((uint32_t)pulsesel << 10U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        reg &= (~(uint32_t)((uint32_t)TIMER_PULSE_OUTPUT_MASK << 12U));
        reg |= (uint32_t)((uint32_t)pulsesel << 12U);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        reg &= (~(uint32_t)((uint32_t)TIMER_PULSE_OUTPUT_MASK << 14U));
        reg |= (uint32_t)((uint32_t)pulsesel << 14U);
        break;
    default:
        break;
    }
    TIMER_CTL2(timer_periph) = reg;
}

/*!
    \brief      configure the TIMER composite PWM mode
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19))
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_channel_composite_pwm_mode_config(uint32_t timer_periph, uint32_t channel, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CTL2(timer_periph) |= (uint32_t)(TIMER_CTL2_CH0CPWMEN << channel);
    } else {
        TIMER_CTL2(timer_periph) &= (~(uint32_t)(TIMER_CTL2_CH0CPWMEN << channel));
    }
}

/*!
    \brief      configure the TIMER composite PWM mode output pulse value
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19))
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
    \param[in]  pulse: channel compare value, 0~0xFFFFFFFF
    \param[in]  add_pulse: channel additional compare value, 0~0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void timer_channel_composite_pwm_mode_output_pulse_value_config(uint32_t timer_periph, uint32_t channel, uint32_t pulse, uint32_t add_pulse)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CH0CV(timer_periph) = (uint32_t)pulse;
        TIMER_CH0COMV_ADD(timer_periph) = (uint32_t)add_pulse;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CH1CV(timer_periph) = (uint32_t)pulse;
        TIMER_CH1COMV_ADD(timer_periph) = (uint32_t)add_pulse;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CH2CV(timer_periph) = (uint32_t)pulse;
        TIMER_CH2COMV_ADD(timer_periph) = (uint32_t)add_pulse;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CH3CV(timer_periph) = (uint32_t)pulse;
        TIMER_CH3COMV_ADD(timer_periph) = (uint32_t)add_pulse;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel additional compare value
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19))
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
    \param[in]  value: channel additional compare value, 0~0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void timer_channel_additional_compare_value_config(uint32_t timer_periph, uint16_t channel, uint32_t value)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CH0COMV_ADD(timer_periph) = (uint32_t)value;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CH1COMV_ADD(timer_periph) = (uint32_t)value;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CH2COMV_ADD(timer_periph) = (uint32_t)value;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CH3COMV_ADD(timer_periph) = (uint32_t)value;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel additional output shadow function
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
    \param[in]  aocshadow: channel additional output compare shadow
                only one parameter can be selected which is shown as below:
      \arg        TIMER_ADD_SHADOW_ENABLE: channel additional compare output shadow enable
      \arg        TIMER_ADD_SHADOW_DISABLE: channel additional compare output shadow disable
    \param[out] none
    \retval     none
*/
void timer_channel_additional_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t aocshadow)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMADDSEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)aocshadow << 28U);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMADDSEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)aocshadow << 29U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMADDSEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)aocshadow << 28U);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMADDSEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)aocshadow << 29U);
        break;
    default:
        break;
    }
}

/*!
    \brief      select TIMER channel additional output register update source
    \param[in]  timer_periph: TIMERx(x=0~4,7,14~16,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14~16,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
    \param[in]  update: channel additional output register update
                only one parameter can be selected which is shown as below:
      \arg        TIMER_ADD_UPDATE_BY_UPDATE: channel additional compare value register update by update event
      \arg        TIMER_ADD_UPDATE_BY_COM_MATCH: channel additional compare value register update by compare value match event
    \param[out] none
    \retval     none
*/
void timer_channel_additional_output_update_select(uint32_t timer_periph, uint16_t channel, uint16_t update)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0ADDUPS);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)update << 26U);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1ADDUPS);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)update << 27U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2ADDUPS);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)update << 26U);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3ADDUPS);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)update << 27U);
        break;
    default:
        break;
    }
}

/*!
    \brief      read TIMER channel additional compare value
    \param[in]  timer_periph: TIMERx(x=0~4,7,14,19))
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0~4,7,14,19))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0~4,7,19))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0~4,7,19))
    \param[out] none
    \retval     value: channel additional compare value, 0~0xFFFFFFFF
*/
uint32_t timer_channel_additional_compare_value_read(uint32_t timer_periph, uint16_t channel)
{
    uint32_t value = 0U;
    switch(channel) {
    case TIMER_CH_0:
        /* read CH0COMV_ADD value */
        value = TIMER_CH0COMV_ADD(timer_periph);
        break;
    case TIMER_CH_1:
        /* read CH1COMV_ADD value */
        value = TIMER_CH1COMV_ADD(timer_periph);
        break;
    case TIMER_CH_2:
        /* read CH2COMV_ADD value */
        value = TIMER_CH2COMV_ADD(timer_periph);
        break;
    case TIMER_CH_3:
        /* read CH3COMV_ADD value */
        value = TIMER_CH3COMV_ADD(timer_periph);
        break;
    default:
        break;
    }
    return value;
}

/*!
    \brief      configure the TIMER break source
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  break_num: TIMER BREAKx
                only one parameter can be selected which is shown as below:
      \arg        TIMER_BREAK0: BREAK0 input signals, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BREAK1: BREAK1 input signals, TIMERx(x=0,7,19)
    \param[in]  break_src: break source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_BRKIN0: BRKIN0 alternate function input enable, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKIN1: BRKIN1 alternate function input enable, TIMERx(x=0,7,19)
      \arg        TIMER_BRKIN2: BRKIN2 alternate function input enable, TIMERx(x=0,7,19)
      \arg        TIMER_BRKCMP0: CMP0 input enable, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKCMP1: CMP1 input enable, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKCMP2: CMP2 input enable, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKCMP3: CMP3 input enable, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKCMP4: CMP4 input enable, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKCMP5: CMP5 input enable, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKCMP6: CMP6 input enable, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKCMP7: CMP7 input enable, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKHPDF: HPDF input enable, TIMERx(x=0,7,14~16,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_break_external_source_config(uint32_t timer_periph, uint16_t break_num, uint32_t break_src, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        if(TIMER_BREAK0 == break_num) {
            TIMER_AFCTL0(timer_periph) |= break_src;
        } else if(TIMER_BREAK1 == break_num) {
            TIMER_AFCTL1(timer_periph) |= break_src;
        } else {
            /* illegal parameters */
        }
    } else {
        if(TIMER_BREAK0 == break_num) {
            TIMER_AFCTL0(timer_periph) &= (~break_src);
        } else if(TIMER_BREAK1 == break_num) {
            TIMER_AFCTL1(timer_periph) &= (~break_src);
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      configure TIMER break polarity
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  break_num: TIMER BREAKx
                only one parameter can be selected which is shown as below:
      \arg        TIMER_BREAK0: BREAK0 input signal, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BREAK1: BREAK1 input signal, TIMERx(x=0,7,19)
    \param[in]  break_src: break source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_BRKIN0: BRKIN0 alternate function input, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKIN1: BRKIN1 alternate function input, TIMERx(x=0,7,19)
      \arg        TIMER_BRKIN2: BRKIN2 alternate function input, TIMERx(x=0,7,19)
      \arg        TIMER_BRKCMP0: CMP0 input, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKCMP1: CMP1 input, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKCMP2: CMP2 input, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BRKCMP3: CMP3 input, TIMERx(x=0,7,14~16,19)
    \param[in]  bkinpolarity: break polarity
                only one parameter can be selected which is shown as below:
                  TIMER_BRKIN_POLARITY_LOW: input signal will not be inverted
                  TIMER_BRKIN_POLARITY_HIGH: input signal will be inverted
    \param[out] none
    \retval     none
*/
void timer_break_external_polarity_config(uint32_t timer_periph, uint16_t break_num, uint32_t break_src, uint16_t bkinpolarity)
{
    if(TIMER_BREAK0 == break_num) {
        switch(break_src) {
        case TIMER_BRKIN0:
            TIMER_AFCTL0(timer_periph) &= (~(uint32_t)TIMER_BRKIN0P);
            TIMER_AFCTL0(timer_periph) |= ((uint32_t)bkinpolarity << 16U);
            break;
        case TIMER_BRKIN1:
            TIMER_AFCTL0(timer_periph) &= (~(uint32_t)TIMER_BRKIN1P);
            TIMER_AFCTL0(timer_periph) |= ((uint32_t)bkinpolarity << 17U);
            break;
        case TIMER_BRKIN2:
            TIMER_AFCTL0(timer_periph) &= (~(uint32_t)TIMER_BRKIN2P);
            TIMER_AFCTL0(timer_periph) |= ((uint32_t)bkinpolarity << 18U);
            break;
        case TIMER_BRKCMP0:
            TIMER_AFCTL0(timer_periph) &= (~(uint32_t)TIMER_BRKCMP0P);
            TIMER_AFCTL0(timer_periph) |= ((uint32_t)bkinpolarity << 25U);
            break;
        case TIMER_BRKCMP1:
            TIMER_AFCTL0(timer_periph) &= (~(uint32_t)TIMER_BRKCMP1P);
            TIMER_AFCTL0(timer_periph) |= ((uint32_t)bkinpolarity << 26U);
            break;
        case TIMER_BRKCMP2:
            TIMER_AFCTL0(timer_periph) &= (~(uint32_t)TIMER_BRKCMP2P);
            TIMER_AFCTL0(timer_periph) |= ((uint32_t)bkinpolarity << 27U);
            break;
        case TIMER_BRKCMP3:
            TIMER_AFCTL0(timer_periph) &= (~(uint32_t)TIMER_BRKCMP3P);
            TIMER_AFCTL0(timer_periph) |= ((uint32_t)bkinpolarity << 28U);
            break;
        default:
            break;
        }
    } else {
        switch(break_src) {
        case TIMER_BRKIN0:
            TIMER_AFCTL1(timer_periph) &= (~(uint32_t)TIMER_BRKIN0P);
            TIMER_AFCTL1(timer_periph) |= ((uint32_t)bkinpolarity << 16U);
            break;
        case TIMER_BRKIN1:
            TIMER_AFCTL1(timer_periph) &= (~(uint32_t)TIMER_BRKIN1P);
            TIMER_AFCTL1(timer_periph) |= ((uint32_t)bkinpolarity << 17U);
            break;
        case TIMER_BRKIN2:
            TIMER_AFCTL1(timer_periph) &= (~(uint32_t)TIMER_BRKIN2P);
            TIMER_AFCTL1(timer_periph) |= ((uint32_t)bkinpolarity << 18U);
            break;
        case TIMER_BRKCMP0:
            TIMER_AFCTL1(timer_periph) &= (~(uint32_t)TIMER_BRKCMP0P);
            TIMER_AFCTL1(timer_periph) |= ((uint32_t)bkinpolarity << 25U);
            break;
        case TIMER_BRKCMP1:
            TIMER_AFCTL1(timer_periph) &= (~(uint32_t)TIMER_BRKCMP1P);
            TIMER_AFCTL1(timer_periph) |= ((uint32_t)bkinpolarity << 26U);
            break;
        case TIMER_BRKCMP2:
            TIMER_AFCTL1(timer_periph) &= (~(uint32_t)TIMER_BRKCMP2P);
            TIMER_AFCTL1(timer_periph) |= ((uint32_t)bkinpolarity << 27U);
            break;
        case TIMER_BRKCMP3:
            TIMER_AFCTL1(timer_periph) &= (~(uint32_t)TIMER_BRKCMP3P);
            TIMER_AFCTL1(timer_periph) |= ((uint32_t)bkinpolarity << 28U);
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      configure TIMER break lock function
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  break_num: TIMER BREAKx
                only one parameter can be selected which is shown as below:
      \arg        TIMER_BREAK0: enable BREAK0 lock function, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BREAK1: enable BREAK1 lock function, TIMERx(x=0,7,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_break_lock_config(uint32_t timer_periph, uint16_t break_num, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        if(TIMER_BREAK0 == break_num) {
            TIMER_CCHP0(timer_periph) |= (uint32_t)TIMER_CCHP0_BRK0LK;
        } else {
            TIMER_CCHP0(timer_periph) |= (uint32_t)TIMER_CCHP0_BRK1LK;
        }
    } else {
        if(TIMER_BREAK0 == break_num) {
            TIMER_CCHP0(timer_periph) &= (~(uint32_t)TIMER_CCHP0_BRK0LK);
        } else {
            TIMER_CCHP0(timer_periph) &= (~(uint32_t)TIMER_CCHP0_BRK1LK);
        }
    }
}

/*!
    \brief      release the TIMER break lock function
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  break_num: TIMER BREAKx
                only one parameter can be selected which is shown as below:
      \arg        TIMER_BREAK0: release the BREAK0 lock function, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_BREAK1: release the BREAK1 lock function, TIMERx(x=0,7,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_break_lock_release_config(uint32_t timer_periph, uint16_t break_num, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        if(TIMER_BREAK0 == break_num) {
            TIMER_CCHP0(timer_periph) |= (uint32_t)TIMER_CCHP0_BRK0REL;
        } else {
            TIMER_CCHP0(timer_periph) |= (uint32_t)TIMER_CCHP0_BRK1REL;
        }
    } else {
        if(TIMER_BREAK0 == break_num) {
            TIMER_CCHP0(timer_periph) &= (~(uint32_t)TIMER_CCHP0_BRK0REL);
        } else {
            TIMER_CCHP0(timer_periph) &= (~(uint32_t)TIMER_CCHP0_BRK1REL);
        }
    }
}

/*!
    \brief      configure the TIMER falling edge dead time
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  deadtime: 0~255
    \param[out] none
    \retval     none
*/
void timer_dead_time_falling_edge_config(uint32_t timer_periph, uint32_t deadtime)
{
    TIMER_CCHP1(timer_periph) &= (~(uint32_t)TIMER_CCHP1_DTFCFG);
    TIMER_CCHP1(timer_periph) |= (uint32_t)deadtime;
}

/*!
    \brief      configure the TIMER dead time different function
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_dead_time_different_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CCHP1(timer_periph) |= (uint32_t)TIMER_CCHP1_DTDIFEN;
    } else {
        TIMER_CCHP1(timer_periph) &= (~(uint32_t)TIMER_CCHP1_DTDIFEN);
    }
}

/*!
    \brief      configure the TIMER dead time modified on-the-fly function
    \param[in]  timer_periph: TIMERx(x=0,7,14~16,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_dead_time_modify_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CCHP1(timer_periph) |= (uint32_t)TIMER_CCHP1_DTMODEN;
    } else {
        TIMER_CCHP1(timer_periph) &= (~(uint32_t)TIMER_CCHP1_DTMODEN);
    }
}

/*!
    \brief      configure the TIMER channel break function
    \param[in]  timer_periph: TIMERx(x=0,7,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0
      \arg        TIMER_CH_1: TIMER channel 1
      \arg        TIMER_CH_2: TIMER channel 2
      \arg        TIMER_CH_3: TIMER channel 3
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_channel_break_control_config(uint32_t timer_periph, uint32_t channel, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CTL2(timer_periph) |= (uint32_t)(TIMER_CTL2_BRKENCH0 << channel);
    } else {
        TIMER_CTL2(timer_periph) &= (~(uint32_t)(TIMER_CTL2_BRKENCH0 << channel));
    }
}

/*!
    \brief      configure the TIMER channel free dead time function
    \param[in]  timer_periph: TIMERx(x=0,7,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0
      \arg        TIMER_CH_1: TIMER channel 1
      \arg        TIMER_CH_2: TIMER channel 2
      \arg        TIMER_CH_3: TIMER channel 3
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_channel_dead_time_config(uint32_t timer_periph, uint32_t channel, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CTL2(timer_periph) |= (uint32_t)(TIMER_CTL2_DTIENCH0 << channel);
    } else {
        TIMER_CTL2(timer_periph) &= (~(uint32_t)(TIMER_CTL2_DTIENCH0 << channel));
    }
}

/*!
    \brief      initialize TIMER channel free complementary parameter struct with a default value
    \param[in]  freecompara: TIMER channel free complementary parameter struct
    \param[out] none
    \retval     none
*/
void timer_free_complementary_struct_para_init(timer_free_complementary_parameter_struct *freecompara)
{
    /* initialize the channel free complementary parameter struct member with the default value */
    freecompara->freecomstate    = TIMER_FCCHP_STATE_DISABLE;
    freecompara->runoffstate     = TIMER_ROS_STATE_DISABLE;
    freecompara->ideloffstate    = TIMER_IOS_STATE_DISABLE;
    freecompara->deadtime        = 0U;
    freecompara->fallingdeadtime = 0U;
}

/*!
    \brief      configure channel free complementary protection
    \param[in]  timer_periph: TIMERx(x=0,7,19)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0
      \arg        TIMER_CH_1: TIMER channel 1
      \arg        TIMER_CH_2: TIMER channel 2
      \arg        TIMER_CH_3: TIMER channel 3
    \param[in] fcpara: TIMER channel free complementary parameter struct
                freecomstate: TIMER_FCCHP_STATE_ENABLE, TIMER_FCCHP_STATE_DISABLE
                runoffstate: TIMER_ROS_STATE_ENABLE, TIMER_ROS_STATE_DISABLE
                ideloffstate: TIMER_IOS_STATE_ENABLE, TIMER_IOS_STATE_DISABLE
                deadtime: 0~255
                fallingdeadtime: 0~255
    \param[out] none
    \retval     none
*/
void timer_channel_free_complementary_config(uint32_t timer_periph, uint16_t channel, timer_free_complementary_parameter_struct *fcpara)
{
    switch(channel) {
    case TIMER_CH_0:
        TIMER_FCCHP0(timer_periph) &= (~(uint32_t)(TIMER_FCCHP0_DTCFG | TIMER_FCCHP0_IOS | TIMER_FCCHP0_ROS | TIMER_FCCHP0_DTFCFG | TIMER_FCCHP0_FCCHP0EN));
        TIMER_FCCHP0(timer_periph) |= fcpara->deadtime;
        TIMER_FCCHP0(timer_periph) |= fcpara->ideloffstate;
        TIMER_FCCHP0(timer_periph) |= fcpara->runoffstate;
        TIMER_FCCHP0(timer_periph) |= (fcpara->fallingdeadtime << 16U);
        TIMER_FCCHP0(timer_periph) |= fcpara->freecomstate;
        break;
    case TIMER_CH_1:
        TIMER_FCCHP1(timer_periph) &= (~(uint32_t)(TIMER_FCCHP1_DTCFG | TIMER_FCCHP1_IOS | TIMER_FCCHP1_ROS | TIMER_FCCHP1_DTFCFG | TIMER_FCCHP1_FCCHP1EN));
        TIMER_FCCHP1(timer_periph) |= fcpara->deadtime;
        TIMER_FCCHP1(timer_periph) |= fcpara->ideloffstate;
        TIMER_FCCHP1(timer_periph) |= fcpara->runoffstate;
        TIMER_FCCHP1(timer_periph) |= (fcpara->fallingdeadtime << 16U);
        TIMER_FCCHP1(timer_periph) |= fcpara->freecomstate;
        break;
    case TIMER_CH_2:
        TIMER_FCCHP2(timer_periph) &= (~(uint32_t)(TIMER_FCCHP2_DTCFG | TIMER_FCCHP2_IOS | TIMER_FCCHP2_ROS | TIMER_FCCHP2_DTFCFG | TIMER_FCCHP2_FCCHP2EN));
        TIMER_FCCHP2(timer_periph) |= fcpara->deadtime;
        TIMER_FCCHP2(timer_periph) |= fcpara->ideloffstate;
        TIMER_FCCHP2(timer_periph) |= fcpara->runoffstate;
        TIMER_FCCHP2(timer_periph) |= (fcpara->fallingdeadtime << 16U);
        TIMER_FCCHP2(timer_periph) |= fcpara->freecomstate;
        break;
    case TIMER_CH_3:
        TIMER_FCCHP3(timer_periph) &= (~(uint32_t)(TIMER_FCCHP3_DTCFG | TIMER_FCCHP3_IOS | TIMER_FCCHP3_ROS | TIMER_FCCHP3_DTFCFG | TIMER_FCCHP3_FCCHP3EN));
        TIMER_FCCHP3(timer_periph) |= fcpara->deadtime;
        TIMER_FCCHP3(timer_periph) |= fcpara->ideloffstate;
        TIMER_FCCHP3(timer_periph) |= fcpara->runoffstate;
        TIMER_FCCHP3(timer_periph) |= (fcpara->fallingdeadtime << 16U);
        TIMER_FCCHP3(timer_periph) |= fcpara->freecomstate;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure quadrature decoder signal disconnection detection watchdog value
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  value: watchdog counter period value, 0~0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void timer_watchdog_value_config(uint32_t timer_periph, uint32_t value)
{
    TIMER_WDGPER(timer_periph) = value;
}

/*!
    \brief      read quadrature decoder signal disconnection detection watchdog value
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[out] none
    \retval     watchdog counter period register value, 0~0xFFFFFFFF
*/
uint32_t timer_watchdog_value_read(uint32_t timer_periph)
{
    return (TIMER_WDGPER(timer_periph));
}

/*!
    \brief      configure quadrature decoder signal disconnection detection function
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_decoder_disconnection_detection_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CTL2(timer_periph) |= TIMER_DECDISCONNECTDEN;
    } else {
        TIMER_CTL2(timer_periph) &= (~TIMER_DECDISCONNECTDEN);
    }
}

/*!
    \brief      configure quadrature decoder signal jump detection function
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_decoder_jump_detection_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CTL2(timer_periph) |= TIMER_DECJUMPDEN;
    } else {
        TIMER_CTL2(timer_periph) &= (~TIMER_DECJUMPDEN);
    }
}

/*!
    \brief      configure decoder mode modified on-the-fly function
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_decoder_modify_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_SMCFG(timer_periph) |= ((uint32_t)TIMER_SMCFG_DECMODEN);
    } else {
        TIMER_SMCFG(timer_periph) &= (~(uint32_t)TIMER_SMCFG_DECMODEN);
    }
}

/*!
    \brief      configure decoder mode update source
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  source: update source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_DEC_UPDATE_BY_UPDATE: decoder mode is updated by the update event
      \arg        TIMER_DEC_UPDATE_BY_INDEX: decoder mode is updated by the index event
    \param[out] none
    \retval     none
*/
void timer_decoder_mode_update_source_config(uint32_t timer_periph, uint32_t source)
{
    if(TIMER_DEC_UPDATE_BY_UPDATE == source) {
        TIMER_SMCFG(timer_periph) &= (~(uint32_t)TIMER_SMCFG_DECMODS);
    } else {
        TIMER_SMCFG(timer_periph) |= ((uint32_t)TIMER_SMCFG_DECMODS);
    }
}

/*!
    \brief      configure index signal reset counter function
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_index_reset_counter_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_DECCTL(timer_periph) |= ((uint32_t)TIMER_DECCTL_INDRSTEN);
    } else {
        TIMER_DECCTL(timer_periph) &= (~(uint32_t)TIMER_DECCTL_INDRSTEN);
    }
}

/*!
    \brief      configure index signal reset counter direction
    \param[in]  timer_periph: TIMERx(x=0,7,19)
    \param[in]  direction: index signal reset counter direction
                only one parameter can be selected which is shown as below:
      \arg        TIMER_INDEX_RESET_DIRECTION_BOTH: index signal resets the counter when it counts up and down
      \arg        TIMER_INDEX_RESET_DIRECTION_UP: index signal resets the counter when it counts up
      \arg        TIMER_INDEX_RESET_DIRECTION_DOWN: index signal resets the counter when it counts down
    \param[out] none
    \retval     none
*/
void timer_index_reset_direction_config(uint32_t timer_periph, uint32_t direction)
{
    TIMER_DECCTL(timer_periph) &= (~(uint32_t)TIMER_DECCTL_INDRSTDIR);
    TIMER_DECCTL(timer_periph) |= (uint32_t)(direction);
}

/*!
    \brief      configure index position
    \param[in]  timer_periph: TIMERx(x=0,7,19)
    \param[in]  position: index position
                only one parameter can be selected which is shown as below:
                TIMERx works in quadrature decoder modes 0~4:
      \arg        TIMER_INDEX_POSITION_AB_00: when AB inputs are 00, index event will reset the counter
      \arg        TIMER_INDEX_POSITION_AB_01: when AB inputs are 01, index event will reset the counter
      \arg        TIMER_INDEX_POSITION_AB_10: when AB inputs are 10, index event will reset the counter
      \arg        TIMER_INDEX_POSITION_AB_11: when AB inputs are 11, index event will reset the counter
                TIMERx works in decoder modes 0~3:
      \arg        TIMER_INDEX_POSITION_LOW: when clock is low, index event will reset the counter
      \arg        TIMER_INDEX_POSITION_HIGH: when clock is high, index event will reset the counter
    \param[out] none
    \retval     none
*/
void timer_decoder_index_position_config(uint32_t timer_periph, uint32_t position)
{
    TIMER_DECCTL(timer_periph) &= (~(uint32_t)(TIMER_DECCTL_INDP));
    TIMER_DECCTL(timer_periph) |= (uint32_t)(position);
}

/*!
    \brief      configure only the first index signal reset counter function
    \param[in]  timer_periph: TIMERx(x=0~4,7,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_first_index_reset_counter_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_DECCTL(timer_periph) |= ((uint32_t)TIMER_DECCTL_FINDRST);
    } else {
        TIMER_DECCTL(timer_periph) &= (~(uint32_t)TIMER_DECCTL_FINDRST);
    }
}

/*!
    \brief      configure the UPIF bit backup function
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_upif_backup_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_UPIFBUEN;
    } else {
        TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_UPIFBUEN);
    }
}

/*!
    \brief      get the UPIFBU bit in the TIMERx_CNT register
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[out] none
    \retval     UPIFBUStatus: VALID_SET or VALID_RESET or INVALID
      \ret        VALID_SET: the UPIFBU is valid and value is 1
      \ret        VALID_RESET: the UPIFBU is valid and value is 0
      \ret        INVALID: the UPIFBU is invalid
*/
UPIFBUStatus timer_upifbu_bit_get(uint32_t timer_periph)
{
    if((TIMER_CTL0(timer_periph) & TIMER_CTL0_UPIFBUEN)) {
        if(TIMER_CNT(timer_periph) & TIMER_CNT_UPIFBU) {
            return VALID_SET;
        } else {
            return VALID_RESET;
        }
    } else {
        return INVALID;
    }
}

/*!
    \brief      configure counter initial value register
    \param[in]  timer_periph: TIMERx(x=0,7,19)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_counter_initial_register_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_CINITCTL(timer_periph) |= TIMER_CINITCTL_CINITVEN;
    } else {
        TIMER_CINITCTL(timer_periph) &= (~(uint32_t)TIMER_CINITCTL_CINITVEN);
    }
}

/*!
    \brief      configure counter initial value and direction
    \param[in]  timer_periph: TIMERx(x=0,7,19)
    \param[in]  value: counter initial value, 0~0xFFFF
    \param[in]  direction: counter initial direction
                only one parameter can be selected which is shown as below:
      \arg        TIMER_INITIAL_DIRECTION_DOWN: counter count down when synchronization event occurs
      \arg        TIMER_INITIAL_DIRECTION_UP: counter count up when synchronization event occurs
    \param[out] none
    \retval     none
*/
void timer_counter_initial_config(uint32_t timer_periph, uint32_t value, uint32_t direction)
{
    TIMER_CINITV(timer_periph) = (uint32_t)value;

    TIMER_CINITCTL(timer_periph) &= (~(uint32_t)TIMER_CINITCTL_CINITDIR);
    TIMER_CINITCTL(timer_periph) |= (uint32_t)direction;
}

/*!
    \brief      generate soft synchronization event
    \param[in]  timer_periph: TIMERx(x=0,7,19)
    \param[out] none
    \retval     none
*/
void timer_synchronization_event_generate(uint32_t timer_periph)
{
    TIMER_CINITCTL(timer_periph) |= TIMER_CINITCTL_SWSYNCG;
}

/*!
    \brief      get TIMER flags
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  flag: the TIMER flags
                only one parameter can be selected which is shown as below:
      \arg        TIMER_FLAG_UP: update flag, TIMERx(x=0~7,14~16,19)
      \arg        TIMER_FLAG_CH0: channel 0 capture or compare flag, TIMERx(x=0~4,7,14~16,19)
      \arg        TIMER_FLAG_CH1: channel 1 capture or compare flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_FLAG_CH2: channel 2 capture or compare flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_CH3: channel 3 capture or compare flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_CMT: channel commutation flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_FLAG_TRG: trigger flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_FLAG_BRK0: BREAK0 flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_FLAG_BRK1: BREAK1 flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_CH0O: channel 0 overcapture flag, TIMERx(x=0~4,7,14~16,19)
      \arg        TIMER_FLAG_CH1O: channel 1 overcapture flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_FLAG_CH2O: channel 2 overcapture flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_CH3O: channel 3 overcapture flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_SYSB: system source break flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_IND: index flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_DECJ: quadrature decoder signal jump flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_DECDIS: quadrature decoder signal disconnection flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_DIRTRAN: direction transform flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_INDERR: index error flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_MCH0: multi mode channel 0 capture or compare flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_FLAG_MCH1: multi mode channel 1 capture or compare flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_MCH2: multi mode channel 2 capture or compare flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_MCH3: multi mode channel 3 capture or compare flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_MCH0O: multi mode channel 0 overcapture flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_FLAG_MCH1O: multi mode channel 1 overcapture flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_MCH2O: multi mode channel 2 overcapture flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_MCH3O: multi mode channel 3 overcapture flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_CH0COMADD: channel 0 additional compare flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_FLAG_CH1COMADD: channel 1 additional compare flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_FLAG_CH2COMADD: channel 2 additional compare flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_CH3COMADD: channel 3 additional compare flag, TIMERx(x=0~4,7,19)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus timer_flag_get(uint32_t timer_periph, uint32_t flag)
{
    if(RESET != (TIMER_INTF(timer_periph) & flag)) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear TIMER flags
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  flag: the TIMER flags
                one or more parameters can be selected which are shown as below:
      \arg        TIMER_FLAG_UP: update flag, TIMERx(x=0~7,14~16,19)
      \arg        TIMER_FLAG_CH0: channel 0 capture or compare flag, TIMERx(x=0~4,7,14~16,19)
      \arg        TIMER_FLAG_CH1: channel 1 capture or compare flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_FLAG_CH2: channel 2 capture or compare flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_CH3: channel 3 capture or compare flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_CMT: channel commutation flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_FLAG_TRG: trigger flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_FLAG_BRK0: BREAK0 flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_FLAG_BRK1: BREAK1 flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_CH0O: channel 0 overcapture flag, TIMERx(x=0~4,7,14~16,19)
      \arg        TIMER_FLAG_CH1O: channel 1 overcapture flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_FLAG_CH2O: channel 2 overcapture flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_CH3O: channel 3 overcapture flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_SYSB: system source break flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_IND: index flag, (x=0~4,7,19)
      \arg        TIMER_FLAG_DECJ: quadrature decoder signal jump flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_DECDIS: quadrature decoder signal disconnection flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_DIRTRAN: direction transform flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_INDERR: index error flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_MCH0: multi mode channel 0 capture or compare flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_FLAG_MCH1: multi mode channel 1 capture or compare flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_MCH2: multi mode channel 2 capture or compare flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_MCH3: multi mode channel 3 capture or compare flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_MCH0O: multi mode channel 0 overcapture flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_FLAG_MCH1O: multi mode channel 1 overcapture flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_MCH2O: multi mode channel 2 overcapture flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_MCH3O: multi mode channel 3 overcapture flag, TIMERx(x=0,7,19)
      \arg        TIMER_FLAG_CH0COMADD: channel 0 additional compare flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_FLAG_CH1COMADD: channel 1 additional compare flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_FLAG_CH2COMADD: channel 2 additional compare flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_FLAG_CH3COMADD: channel 3 additional compare flag, TIMERx(x=0~4,7,19)
    \param[out] none
    \retval     none
*/
void timer_flag_clear(uint32_t timer_periph, uint32_t flag)
{
    TIMER_INTF(timer_periph) = (~(uint32_t)flag);
}

/*!
    \brief      enable the TIMER interrupt
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  interrupt: timer interrupt source
                one or more parameters can be selected which are shown as below:
      \arg        TIMER_INT_UP: update interrupt, TIMERx(x=0~7,14~16,19)
      \arg        TIMER_INT_CH0: channel 0 capture or compare interrupt, TIMERx(x=0~4,7,14~16,19)
      \arg        TIMER_INT_CH1: channel 1 capture or compareinterrupt, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_CH2: channel 2 capture or compare interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_CH3: channel 3 capture or compare interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_CMT: channel commutation interrupt, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_TRG: trigger interrupt, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_BRK: break interrupt, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_IND: index interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_DECJ: quadrature decoder signal jump interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_DECDIS: quadrature decoder signal disconnection interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_DIRTRAN: direction transform interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_INDERR: index error interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_MCH0: multi mode channel 0 capture or compare interrupt, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_MCH1: multi mode channel 1 capture or compare interrupt, TIMERx(x=0,7,19)
      \arg        TIMER_INT_MCH2: multi mode channel 2 capture or compare interrupt, TIMERx(x=0,7,19)
      \arg        TIMER_INT_MCH3: multi mode channel 3 capture or compare interrupt, TIMERx(x=0,7,19)
      \arg        TIMER_INT_CH0COMADD: channel 0 additional compare interrupt, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_CH1COMADD: channel 1 additional compare interrupt, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_CH2COMADD: channel 2 additional compare interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_CH3COMADD: channel 3 additional compare interrupt, TIMERx(x=0~4,7,19)
    \param[out] none
    \retval     none
*/
void timer_interrupt_enable(uint32_t timer_periph, uint32_t interrupt)
{
    TIMER_DMAINTEN(timer_periph) |= (uint32_t) interrupt;
}

/*!
    \brief      disable the TIMER interrupt
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  interrupt: timer interrupt source
                one or more parameters can be selected which are shown as below:
      \arg        TIMER_INT_UP: update interrupt, TIMERx(x=0~7,14~16,19)
      \arg        TIMER_INT_CH0: channel 0 capture or compare interrupt, TIMERx(x=0~4,7,14~16,19)
      \arg        TIMER_INT_CH1: channel 1 capture or compareinterrupt, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_CH2: channel 2 capture or compare interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_CH3: channel 3 capture or compare interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_CMT: channel commutation interrupt, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_TRG: trigger interrupt, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_BRK: break interrupt, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_IND: index interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_DECJ: quadrature decoder signal jump interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_DECDIS: quadrature decoder signal disconnection interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_DIRTRAN: direction transform interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_INDERR: index error interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_MCH0: multi mode channel 0 capture or compare interrupt, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_MCH1: multi mode channel 1 capture or compare interrupt, TIMERx(x=0,7,19)
      \arg        TIMER_INT_MCH2: multi mode channel 2 capture or compare interrupt, TIMERx(x=0,7,19)
      \arg        TIMER_INT_MCH3: multi mode channel 3 capture or compare interrupt, TIMERx(x=0,7,19)
      \arg        TIMER_INT_CH0COMADD: channel 0 additional compare interrupt, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_CH1COMADD: channel 1 additional compare interrupt, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_CH2COMADD: channel 2 additional compare interrupt, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_CH3COMADD: channel 3 additional compare interrupt, TIMERx(x=0~4,7,19)
    \param[out] none
    \retval     none
*/
void timer_interrupt_disable(uint32_t timer_periph, uint32_t interrupt)
{
    TIMER_DMAINTEN(timer_periph) &= (~(uint32_t)interrupt);
}

/*!
    \brief      get timer interrupt flags
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  int_flag: the timer interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        TIMER_INT_FLAG_UP: update interrupt flag, TIMERx(x=0~7,14~16,19)
      \arg        TIMER_INT_FLAG_CH0: channel 0 capture or compare interrupt flag, TIMERx(x=0~4,7,14~16,19)
      \arg        TIMER_INT_FLAG_CH1: channel 1 capture or compare interrupt flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_FLAG_CH2: channel 2 capture or compare interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_CH3: channel 3 capture or compare interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_CMT: channel commutation interrupt flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_FLAG_TRG: trigger interrupt flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_FLAG_BRK0: BREAK0 interrupt flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_FLAG_BRK1: BREAK1 interrupt flag, TIMERx(x=0,7,19)
      \arg        TIMER_INT_FLAG_SYSB: system source break interrupt flag, TIMERx(x=0,7,19)
      \arg        TIMER_INT_FLAG_IND: index interrupt flag, TIMERx((x=0~4,7,19)
      \arg        TIMER_INT_FLAG_DECJ: quadrature decoder signal jump interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_DECDIS: quadrature decoder signal disconnection interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_DIRTRAN: direction transform interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_INDERR: index error interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_MCH0: multi mode channel 0 capture or compare interrupt flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_FLAG_MCH1: multi mode channel 1 capture or compare interrupt flag, TIMERx(x=0,7,19)
      \arg        TIMER_INT_FLAG_MCH2: multi mode channel 2 capture or compare interrupt flag, TIMERx(x=0,7,19)
      \arg        TIMER_INT_FLAG_MCH3: multi mode channel 3 capture or compare interrupt flag, TIMERx(x=0,7,19)
      \arg        TIMER_INT_FLAG_CH0COMADD: channel 0 additional compare interrupt flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_FLAG_CH1COMADD: channel 1 additional compare interrupt flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_FLAG_CH2COMADD: channel 2 additional compare interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_CH3COMADD: channel 3 additional compare interrupt flag, TIMERx(x=0~4,7,19)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus timer_interrupt_flag_get(uint32_t timer_periph, uint32_t int_flag)
{
    uint32_t val;

    if(TIMER_INT_FLAG_BRK1 == int_flag) {
        val = (TIMER_DMAINTEN(timer_periph) & TIMER_DMAINTEN_BRKIE);
    } else if(TIMER_INT_FLAG_SYSB == int_flag) {
        val = (TIMER_DMAINTEN(timer_periph) & TIMER_DMAINTEN_BRKIE);
    } else {
        val = (TIMER_DMAINTEN(timer_periph) & int_flag);
    }

    if((RESET != (TIMER_INTF(timer_periph) & int_flag)) && (RESET != val)) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear TIMER interrupt flags
    \param[in]  timer_periph: TIMERx(x=0~7,14~16,19)
    \param[in]  int_flag: the timer interrupt flags
                one or more parameters can be selected which are shown as below:
      \arg        TIMER_INT_FLAG_UP: update interrupt flag, TIMERx(x=0~7,14~16,19)
      \arg        TIMER_INT_FLAG_CH0: channel 0 capture or compare interrupt flag, TIMERx(x=0~4,7,14~16,19)
      \arg        TIMER_INT_FLAG_CH1: channel 1 capture or compare interrupt flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_FLAG_CH2: channel 2 capture or compare interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_CH3: channel 3 capture or compare interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_CMT: channel commutation interrupt flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_FLAG_TRG: trigger interrupt flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_FLAG_BRK0: BREAK0 interrupt flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_FLAG_BRK1: BREAK1 interrupt flag, TIMERx(x=0,7,19)
      \arg        TIMER_INT_FLAG_SYSB: system source break interrupt flag, TIMERx(x=0,7,19)
      \arg        TIMER_INT_FLAG_IND: index interrupt flag, TIMERx((x=0~4,7,19)
      \arg        TIMER_INT_FLAG_DECJ: quadrature decoder signal jump interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_DECDIS: quadrature decoder signal disconnection interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_DIRTRAN: direction transform interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_INDERR: index error interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_MCH0: multi mode channel 0 capture or compare interrupt flag, TIMERx(x=0,7,14~16,19)
      \arg        TIMER_INT_FLAG_MCH1: multi mode channel 1 capture or compare interrupt flag, TIMERx(x=0,7,19)
      \arg        TIMER_INT_FLAG_MCH2: multi mode channel 2 capture or compare interrupt flag, TIMERx(x=0,7,19)
      \arg        TIMER_INT_FLAG_MCH3: multi mode channel 3 capture or compare interrupt flag, TIMERx(x=0,7,19)
      \arg        TIMER_INT_FLAG_CH0COMADD: channel 0 additional compare interrupt flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_FLAG_CH1COMADD: channel 1 additional compare interrupt flag, TIMERx(x=0~4,7,14,19)
      \arg        TIMER_INT_FLAG_CH2COMADD: channel 2 additional compare interrupt flag, TIMERx(x=0~4,7,19)
      \arg        TIMER_INT_FLAG_CH3COMADD: channel 3 additional compare interrupt flag, TIMERx(x=0~4,7,19)
    \param[out] none
    \retval     none
*/
void timer_interrupt_flag_clear(uint32_t timer_periph, uint32_t int_flag)
{
    TIMER_INTF(timer_periph) = (~(uint32_t)int_flag);
}
