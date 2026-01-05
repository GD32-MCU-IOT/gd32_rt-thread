/*!
    \file    gd32l23x_timer.c
    \brief   TIMER driver

    \version 2025-08-08, V2.3.0, firmware for GD32L23x, add support for GD32L235
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

#include "gd32l23x_timer.h"

/*!
    \brief      deinit a TIMER
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_deinit(uint32_t timer_periph)
{
    switch(timer_periph) {
#if defined(GD32L235)
    case TIMER0:
        /* reset TIMER0 */
        rcu_periph_reset_enable(RCU_TIMER0RST);
        rcu_periph_reset_disable(RCU_TIMER0RST);
        break;
#endif /* GD32L235 */
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
    case TIMER8:
        /* reset TIMER8 */
        rcu_periph_reset_enable(RCU_TIMER8RST);
        rcu_periph_reset_disable(RCU_TIMER8RST);
        break;
    case TIMER11:
        /* reset TIMER11 */
        rcu_periph_reset_enable(RCU_TIMER11RST);
        rcu_periph_reset_disable(RCU_TIMER11RST);
        break;
#if defined(GD32L235)
    case TIMER14:
        /* reset TIMER14 */
        rcu_periph_reset_enable(RCU_TIMER14RST);
        rcu_periph_reset_disable(RCU_TIMER14RST);
        break;
    case TIMER40:
        /* reset TIMER40 */
        rcu_periph_reset_enable(RCU_TIMER40RST);
        rcu_periph_reset_disable(RCU_TIMER40RST);
        break;
#endif /* GD32L235 */
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
    initpara->period            = 65535U;
    initpara->clockdivision     = TIMER_CKDIV_DIV1;
#if defined(GD32L235)
    initpara->repetitioncounter = 0U;
#endif /* GD32L235 */
}

/*!
    \brief      initialize TIMER counter
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[in]  initpara: init parameter struct
                  prescaler: prescaler value of the counter clock, 0~65535
                  alignedmode: TIMER_COUNTER_EDGE, TIMER_COUNTER_CENTER_DOWN, TIMER_COUNTER_CENTER_UP, TIMER_COUNTER_CENTER_BOTH
                  counterdirection: TIMER_COUNTER_UP, TIMER_COUNTER_DOWN
                  period: counter auto reload value, 0~65535
                  clockdivision: TIMER_CKDIV_DIV1, TIMER_CKDIV_DIV2, TIMER_CKDIV_DIV4
                  repetitioncounter: counter repetition value, 0~255
    \param[out] none
    \retval     none
*/
void timer_init(uint32_t timer_periph, timer_parameter_struct *initpara)
{
    /* configure the counter prescaler value */
    TIMER_PSC(timer_periph) = (uint16_t)initpara->prescaler;

    /* configure the counter direction and aligned mode */
#if defined(GD32L235)
    if(TIMER0 == timer_periph){
        TIMER_CTL0(timer_periph) &= (~(uint32_t)(TIMER_CTL0_DIR | TIMER_CTL0_CAM));
        TIMER_CTL0(timer_periph) |= (uint32_t)(initpara->alignedmode);
        TIMER_CTL0(timer_periph) |= (uint32_t)(initpara->counterdirection);
    }
#endif /* GD32L235 */
    if((TIMER1 == timer_periph) || (TIMER2 == timer_periph)){
        TIMER_CTL0(timer_periph) &= (~(uint32_t)(TIMER_CTL0_DIR | TIMER_CTL0_CAM));
        TIMER_CTL0(timer_periph) |= (uint32_t)(initpara->alignedmode);
        TIMER_CTL0(timer_periph) |= (uint32_t)(initpara->counterdirection);
    }

    /* configure the autoreload value */
    TIMER_CAR(timer_periph) = (uint32_t)initpara->period;

    if((TIMER5 != timer_periph) || (TIMER6 != timer_periph)){
        /* reset the CKDIV bit */
        TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_CKDIV);
        TIMER_CTL0(timer_periph) |= (uint32_t)(initpara->clockdivision);
    }

#if defined(GD32L235)
    if((TIMER0 == timer_periph) || (TIMER14 == timer_periph) || (TIMER40 == timer_periph)){
        /* configure the repetition counter value */
        TIMER_CREP(timer_periph) = (uint32_t)initpara->repetitioncounter;
    }
#endif /* GD32L235 */
    
    /* generate an update event */
    TIMER_SWEVG(timer_periph) |= (uint32_t)TIMER_SWEVG_UPG;
}

/*!
    \brief      enable a TIMER
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_enable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_CEN;
}

/*!
    \brief      disable a TIMER
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_disable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_CEN;
}

/*!
    \brief      enable the auto reload shadow function
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_auto_reload_shadow_enable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_ARSE;
}

/*!
    \brief      disable the auto reload shadow function
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_auto_reload_shadow_disable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_ARSE;
}

/*!
    \brief      enable the update event
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_update_event_enable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_UPDIS;
}

/*!
    \brief      disable the update event
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_update_event_disable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t) TIMER_CTL0_UPDIS;
}

/*!
    \brief      set TIMER counter alignment mode
    \param[in]  timer_periph: TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
    \param[in]  aligned: alignment mode
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
    \param[in]  timer_periph: TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_counter_up_direction(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_DIR;
}

/*!
    \brief      set TIMER counter down direction
    \param[in]  timer_periph: TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_counter_down_direction(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_DIR;
}

/*!
    \brief      configure TIMER prescaler
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[in]  prescaler: prescaler value, 0~65535
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

#if defined(GD32L235)
/*!
    \brief      configure TIMER repetition register value
    \param[in]  timer_periph: TIMERx(x=0,14,40 for GD32L235)
    \param[in]  repetition: the counter repetition value, 0~255
    \param[out] none
    \retval     none
*/
void timer_repetition_value_config(uint32_t timer_periph, uint16_t repetition)
{
    TIMER_CREP(timer_periph) = (uint32_t)repetition;
}
#endif /* GD32L235 */

/*!
    \brief      configure TIMER autoreload register value
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[in]  autoreload: the counter auto-reload value, 0~65535
    \param[out] none
    \retval     none
*/
void timer_autoreload_value_config(uint32_t timer_periph, uint32_t autoreload)
{
    TIMER_CAR(timer_periph) = (uint32_t)autoreload;
}

/*!
    \brief      configure TIMER counter register value
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[in]  counter: the counter value, 0~65535
    \param[out] none
    \retval     none
*/
void timer_counter_value_config(uint32_t timer_periph, uint32_t counter)
{
    TIMER_CNT(timer_periph) = (uint32_t)counter;
}

/*!
    \brief      read TIMER counter value
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     counter value: 0~65535
*/
uint32_t timer_counter_read(uint32_t timer_periph)
{
    uint32_t count_value = 0U;
    count_value = TIMER_CNT(timer_periph);
    return (count_value);
}

/*!
    \brief      read TIMER prescaler value
    \param[in]  timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     prescaler register value: 0~65535
*/
uint16_t timer_prescaler_read(uint32_t timer_periph)
{
    uint16_t prescaler_value = 0U;
    prescaler_value = (uint16_t)(TIMER_PSC(timer_periph));
    return (prescaler_value);
}

/*!
    \brief      configure TIMER single pulse mode
    \param[in]  timer_periph: TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
    \param[in]  spmode: pulse mode
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
        TIMER_CTL0(timer_periph) &= ~((uint32_t)TIMER_CTL0_SPM);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure TIMER update source
    \param[in]  timer_periph: timer_periph: TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
    \param[in]  update: update source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_UPDATE_SRC_GLOBAL: update generate by setting of UPG bit or the counter overflow/underflow,or the slave mode controller trigger
      \arg        TIMER_UPDATE_SRC_REGULAR: update generate only by counter overflow/underflow
    \param[out] none
    \retval     none
*/
void timer_update_source_config(uint32_t timer_periph, uint32_t update)
{
    if(TIMER_UPDATE_SRC_REGULAR == update) {
        TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_UPS;
    } else if(TIMER_UPDATE_SRC_GLOBAL == update) {
        TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_UPS;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable the TIMER DMA
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  dma: specify which DMA to enable
                only one parameter can be selected which is shown as below:
      \arg        TIMER_DMA_UPD:  update DMA ,TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
      \arg        TIMER_DMA_CH0D: channel 0 DMA request,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_DMA_CH1D: channel 1 DMA request,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_DMA_CH2D: channel 2 DMA request,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_DMA_CH3D: channel 3 DMA request,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_DMA_CMTD: commutation DMA request,TIMERx(x=0,14,40 for GD32L235)
      \arg        TIMER_DMA_TRGD: trigger DMA request,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_dma_enable(uint32_t timer_periph, uint16_t dma)
{
    TIMER_DMAINTEN(timer_periph) |= (uint32_t) dma;
}

/*!
    \brief      disable the TIMER DMA
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  dma: specify which DMA to enable
                one or more parameters can be selected which are shown as below:
      \arg        TIMER_DMA_UPD:  update DMA ,TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
      \arg        TIMER_DMA_CH0D: channel 0 DMA request,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_DMA_CH1D: channel 1 DMA request,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_DMA_CH2D: channel 2 DMA request,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_DMA_CH3D: channel 3 DMA request,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_DMA_CMTD: commutation DMA request,TIMERx(x=0,14,40 for GD32L235)
      \arg        TIMER_DMA_TRGD: trigger DMA request,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_dma_disable(uint32_t timer_periph, uint16_t dma)
{
    TIMER_DMAINTEN(timer_periph) &= (~(uint32_t)(dma));
}

/*!
    \brief      channel DMA request source selection
    \param[in]  timer_periph: TIMERx(x=1,2 for GD32L233, x=0,1,2,14,40 for GD32L235)
    \param[in]  dma_request: channel DMA request source selection
                only one parameter can be selected which is shown as below:
       \arg        TIMER_DMAREQUEST_CHANNELEVENT: DMA request of channel y is sent when channel y event occurs
       \arg        TIMER_DMAREQUEST_UPDATEEVENT: DMA request of channel y is sent when update event occurs
    \param[out] none
    \retval     none
*/
void timer_channel_dma_request_source_select(uint32_t timer_periph, uint32_t dma_request)
{
    if(TIMER_DMAREQUEST_UPDATEEVENT == dma_request) {
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_DMAS;
    } else if(TIMER_DMAREQUEST_CHANNELEVENT == dma_request) {
        TIMER_CTL1(timer_periph) &= ~(uint32_t)TIMER_CTL1_DMAS;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure the TIMER DMA transfer
    \param[in]  timer_periph: TIMERx(x=1,2 for GD32L233, x=0,1,2,14,40 for GD32L235)
    \param[in]  dma_baseaddr: DMA transfer access start address
                only one parameter can be selected which is shown as below:
       \arg        TIMER_DMACFG_DMATA_CTL0: DMA transfer address is TIMER_CTL0
       \arg        TIMER_DMACFG_DMATA_CTL1: DMA transfer address is TIMER_CTL1
       \arg        TIMER_DMACFG_DMATA_SMCFG: DMA transfer address is TIMER_SMCFG
       \arg        TIMER_DMACFG_DMATA_DMAINTEN: DMA transfer address is TIMER_DMAINTEN
       \arg        TIMER_DMACFG_DMATA_INTF: DMA transfer address is TIMER_INTF
       \arg        TIMER_DMACFG_DMATA_SWEVG: DMA transfer address is TIMER_SWEVG
       \arg        TIMER_DMACFG_DMATA_CHCTL0: DMA transfer address is TIMER_CHCTL0
       \arg        TIMER_DMACFG_DMATA_CHCTL1: DMA transfer address is TIMER_CHCTL1
       \arg        TIMER_DMACFG_DMATA_CHCTL2: DMA transfer address is TIMER_CHCTL2
       \arg        TIMER_DMACFG_DMATA_CNT: DMA transfer address is TIMER_CNT
       \arg        TIMER_DMACFG_DMATA_PSC: DMA transfer address is TIMER_PSC
       \arg        TIMER_DMACFG_DMATA_CAR: DMA transfer address is TIMER_CAR
       \arg        TIMER_DMACFG_DMATA_CREP: DMA transfer address is TIMER_CREP
       \arg        TIMER_DMACFG_DMATA_CH0CV: DMA transfer address is TIMER_CH0CV
       \arg        TIMER_DMACFG_DMATA_CH1CV: DMA transfer address is TIMER_CH1CV
       \arg        TIMER_DMACFG_DMATA_CH2CV: DMA transfer address is TIMER_CH2CV
       \arg        TIMER_DMACFG_DMATA_CH3CV: DMA transfer address is TIMER_CH3CV
       \arg        TIMER_DMACFG_DMATA_CCHP: DMA transfer address is TIMER_CCHP, only for GD32L235
       \arg        TIMER_DMACFG_DMATA_DMACFG: DMA transfer address is TIMER_DMACFG
       \arg        TIMER_DMACFG_DMATA_DMATB: DMA transfer address is TIMER_DMATB
    \param[in]  dma_lenth:
                only one parameter can be selected which is shown as below:
       \arg        TIMER_DMACFG_DMATC_xTRANSFER(x=1..18): DMA transfer x time
    \param[out] none
    \retval     none
*/
void timer_dma_transfer_config(uint32_t timer_periph, uint32_t dma_baseaddr, uint32_t dma_lenth)
{
    uint32_t ctl;
    ctl = TIMER_DMACFG(timer_periph);
    ctl &= (~(uint32_t)(TIMER_DMACFG_DMATA | TIMER_DMACFG_DMATC));
    ctl |= (uint32_t)(dma_baseaddr | dma_lenth);
    TIMER_DMACFG(timer_periph) = ctl;
}

/*!
    \brief      software generate events
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  event: the timer software event generation sources
                one or more parameters can be selected which are shown as below:
      \arg        TIMER_EVENT_SRC_UPG: update event,TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
      \arg        TIMER_EVENT_SRC_CH0G: channel 0 capture or compare event generation,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_EVENT_SRC_CH1G: channel 1 capture or compare event generation,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_EVENT_SRC_CH2G: channel 2 capture or compare event generation,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_EVENT_SRC_CH3G: channel 3 capture or compare event generation,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_EVENT_SRC_CMTG: channel commutation event generation,TIMERx(x=0,14,40 for GD32L235)
      \arg        TIMER_EVENT_SRC_TRGG: trigger event generation,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_EVENT_SRC_BRKG: break event generation,TIMERx(x=0,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_event_software_generate(uint32_t timer_periph, uint16_t event)
{
    TIMER_SWEVG(timer_periph) |= (uint32_t)event;
}

#if defined(GD32L235)
/*!
    \brief      initialize TIMER break parameter struct with a default value
    \param[in]  breakpara: TIMER break parameter struct
    \param[out] none
    \retval     none
*/
void timer_break_struct_para_init(timer_break_parameter_struct* breakpara)
{
    /* initialize the break parameter struct member with the default value */
    breakpara->runoffstate     = TIMER_ROS_STATE_DISABLE;
    breakpara->ideloffstate    = TIMER_IOS_STATE_DISABLE;
    breakpara->deadtime        = 0U;
    breakpara->breakpolarity   = TIMER_BREAK_POLARITY_LOW;
    breakpara->outputautostate = TIMER_OUTAUTO_DISABLE;
    breakpara->protectmode     = TIMER_CCHP_PROT_OFF;
    breakpara->breakstate      = TIMER_BREAK_DISABLE;
}

/*!
    \brief      configure TIMER break function 
    \param[in]  timer_periph: TIMERx(x=0,14,40)
    \param[in]  breakpara: TIMER break parameter struct
                runoffstate: TIMER_ROS_STATE_ENABLE,TIMER_ROS_STATE_DISABLE
                ideloffstate: TIMER_IOS_STATE_ENABLE,TIMER_IOS_STATE_DISABLE
                deadtime: 0~255
                breakpolarity: TIMER_BREAK_POLARITY_LOW,TIMER_BREAK_POLARITY_HIGH
                outputautostate: TIMER_OUTAUTO_ENABLE,TIMER_OUTAUTO_DISABLE
                protectmode: TIMER_CCHP_PROT_OFF,TIMER_CCHP_PROT_0,TIMER_CCHP_PROT_1,TIMER_CCHP_PROT_2
                breakstate: TIMER_BREAK_ENABLE,TIMER_BREAK_DISABLE
    \param[out] none
    \retval     none
*/
void timer_break_config(uint32_t timer_periph, timer_break_parameter_struct* breakpara)
{
    TIMER_CCHP(timer_periph) = (uint32_t)(((uint32_t)(breakpara->runoffstate))|
                                          ((uint32_t)(breakpara->ideloffstate))|
                                          ((uint32_t)(breakpara->deadtime))|
                                          ((uint32_t)(breakpara->breakpolarity))|
                                          ((uint32_t)(breakpara->outputautostate)) |
                                          ((uint32_t)(breakpara->protectmode))|
                                          ((uint32_t)(breakpara->breakstate))) ;
}

/*!
    \brief      enable TIMER break function
    \param[in]  timer_periph: TIMERx(x=0,14,40)
    \param[out] none
    \retval     none
*/
void timer_break_enable(uint32_t timer_periph)
{
    TIMER_CCHP(timer_periph) |= (uint32_t)TIMER_CCHP_BRKEN;
}

/*!
    \brief      disable TIMER break function
    \param[in]  timer_periph: TIMERx(x=0,14,40)
    \param[out] none
    \retval     none
*/
void timer_break_disable(uint32_t timer_periph)
{
    TIMER_CCHP(timer_periph) &= ~(uint32_t)TIMER_CCHP_BRKEN;
}

/*!
    \brief      enable TIMER output automatic function
    \param[in]  timer_periph: TIMERx(x=0,14,40)
    \param[out] none
    \retval     none
*/
void timer_automatic_output_enable(uint32_t timer_periph)
{
    TIMER_CCHP(timer_periph) |= (uint32_t)TIMER_CCHP_OAEN;
}

/*!
    \brief      disable TIMER output automatic function
    \param[in]  timer_periph: TIMERx(x=0,14,40)
    \param[out] none
    \retval     none
*/
void timer_automatic_output_disable(uint32_t timer_periph)
{
    TIMER_CCHP(timer_periph) &= ~(uint32_t)TIMER_CCHP_OAEN;
}

/*!
    \brief      configure TIMER primary output function
    \param[in]  timer_periph: TIMERx(x=0,14,40)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_primary_output_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue){
        TIMER_CCHP(timer_periph) |= (uint32_t)TIMER_CCHP_POEN;
    }else{
        TIMER_CCHP(timer_periph) &= (~(uint32_t)TIMER_CCHP_POEN);
    }
}

/*!
    \brief      enable or disable channel capture/compare control shadow register
    \param[in]  timer_periph: TIMERx(x=0,14,40)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_channel_control_shadow_config(uint32_t timer_periph, ControlStatus newvalue)
{
     if(ENABLE == newvalue){
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_CCSE;
    }else{
        TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_CCSE);
    }
}

/*!
    \brief      configure TIMER channel control shadow register update control
    \param[in]  timer_periph: TIMERx(x=0,14,40)
    \param[in]  ccuctl: channel control shadow register update control
                only one parameter can be selected which is shown as below:
      \arg        TIMER_UPDATECTL_CCU: the shadow registers update by when CMTG bit is set
      \arg        TIMER_UPDATECTL_CCUTRI: the shadow registers update by when CMTG bit is set or an rising edge of TRGI occurs 
    \param[out] none
    \retval     none
*/
void timer_channel_control_shadow_update_config(uint32_t timer_periph, uint8_t ccuctl)
{
    if(TIMER_UPDATECTL_CCU == ccuctl){
        TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_CCUC);
    }else if(TIMER_UPDATECTL_CCUTRI == ccuctl){
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_CCUC;
    }else{
        /* illegal parameters */
    }
}
#endif /* GD32L235 */

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
#if defined(GD32L235)
    ocpara->outputnstate = TIMER_CCXN_DISABLE;
#endif /* GD32L235 */
    ocpara->ocpolarity   = TIMER_OC_POLARITY_HIGH;
#if defined(GD32L235)
    ocpara->ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    ocpara->ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    ocpara->ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
#endif /* GD32L235 */
}

/*!
    \brief      configure TIMER channel output function
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
    \param[in]  ocpara: TIMER channeln output parameter struct
                outputstate: TIMER_CCX_ENABLE,TIMER_CCX_DISABLE
                outputnstate: TIMER_CCXN_ENABLE,TIMER_CCXN_DISABLE
                ocpolarity: TIMER_OC_POLARITY_HIGH,TIMER_OC_POLARITY_LOW
                ocnpolarity: TIMER_OCN_POLARITY_HIGH,TIMER_OCN_POLARITY_LOW
                ocidlestate: TIMER_OC_IDLE_STATE_LOW,TIMER_OC_IDLE_STATE_HIGH
                ocnidlestate: TIMER_OCN_IDLE_STATE_LOW,TIMER_OCN_IDLE_STATE_HIGH
    \param[out] none
    \retval     none
*/
void timer_channel_output_config(uint32_t timer_periph, uint16_t channel, timer_oc_parameter_struct *ocpara)
{
    uint32_t ctl;

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        TIMER_CHCTL0(timer_periph) &= ~(uint32_t)TIMER_CHCTL0_CH0MS;
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpara->outputstate;
        /* set the CH0P bit */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH0P);
        ctl |= (uint32_t)ocpara->ocpolarity;
        TIMER_CHCTL2(timer_periph) = ctl;
#if defined(GD32L235)
        if((TIMER0 == timer_periph) || (TIMER14 == timer_periph) || (TIMER40 == timer_periph)){
            /* reset the CH0NEN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NEN);
            /* set the CH0NEN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpara->outputnstate;
            /* reset the CH0NP bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NP);
            /* set the CH0NP bit */
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
#endif /* GD32L235 */
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        TIMER_CHCTL0(timer_periph) &= ~(uint32_t)TIMER_CHCTL0_CH1MS;
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->outputstate) << 4U);
        /* set the CH1P bit */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH1P);
        ctl |= (uint32_t)((uint32_t)(ocpara->ocpolarity) << 4U);
        TIMER_CHCTL2(timer_periph) = ctl;
#if defined(GD32L235)
        if((TIMER0 == timer_periph) ){
            /* reset the CH1NEN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NEN);
            /* set the CH1NEN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->outputnstate) << 4U);
            /* reset the CH1NP bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NP);
            /* set the CH1NP bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocnpolarity) << 4U);
            /* reset the ISO1 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO1);
            /* set the ISO1 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocidlestate) << 2U);
            /* reset the ISO1N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO1N);
            /* set the ISO1N bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocnidlestate) << 2U);
        }
#endif /* GD32L235 */
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        /* reset the CH2EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);
        TIMER_CHCTL1(timer_periph) &= ~(uint32_t)TIMER_CHCTL1_CH2MS;
        /* set the CH2EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->outputstate) << 8U);
        /* set the CH2P bit */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH2P);
        ctl |= (uint32_t)((uint32_t)(ocpara->ocpolarity) << 8U);
        TIMER_CHCTL2(timer_periph) = ctl;
#if defined(GD32L235)
        if((TIMER0 == timer_periph)){
            /* reset the CH2NEN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NEN);
            /* set the CH2NEN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->outputnstate) << 8U);
            /* reset the CH2NP bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NP);
            /* set the CH2NP bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocnpolarity) << 8U);
            /* reset the ISO2 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO2);
            /* set the ISO2 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocidlestate) << 4U);
            /* reset the ISO2N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO2N);
            /* set the ISO2N bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocnidlestate) << 4U);
        }
#endif /* GD32L235 */
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        /* reset the CH3EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);
        TIMER_CHCTL1(timer_periph) &= ~(uint32_t)TIMER_CHCTL1_CH3MS;
        /* set the CH3EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->outputstate) << 12U);
        /* set the CH3P bit */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH3P);
        ctl |= (uint32_t)((uint32_t)(ocpara->ocpolarity) << 12U);
        TIMER_CHCTL2(timer_periph) = ctl;
#if defined(GD32L235)
        if((TIMER0 == timer_periph)){
            /* reset the ISO3 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO3);
            /* set the ISO3 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocidlestate) << 6U);
        }
#endif /* GD32L235 */
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output compare mode
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
    \param[in]  ocmode: channel output compare mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_MODE_TIMING: timing mode
      \arg        TIMER_OC_MODE_ACTIVE: active mode
      \arg        TIMER_OC_MODE_INACTIVE: inactive mode
      \arg        TIMER_OC_MODE_TOGGLE: toggle mode
      \arg        TIMER_OC_MODE_LOW: force low mode
      \arg        TIMER_OC_MODE_HIGH: force high mode
      \arg        TIMER_OC_MODE_PWM0: PWM0 mode
      \arg        TIMER_OC_MODE_PWM1: PWM1 mode
    \param[out] none
    \retval     none
*/
void timer_channel_output_mode_config(uint32_t timer_periph, uint16_t channel, uint16_t ocmode)
{
    uint32_t ctl;

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0COMCTL);
        ctl |= (uint32_t)ocmode;
        TIMER_CHCTL0(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1COMCTL);
        ctl |= (uint32_t)((uint32_t)(ocmode) << 8U);
        TIMER_CHCTL0(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH2COMCTL);
        ctl |= (uint32_t)ocmode;
        TIMER_CHCTL1(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH3COMCTL);
        ctl |= (uint32_t)((uint32_t)(ocmode) << 8U);
        TIMER_CHCTL1(timer_periph) = ctl;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output pulse value
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
    \param[in]  pulse: channel output pulse value
    \param[out] none
    \retval     none
*/
void timer_channel_output_pulse_value_config(uint32_t timer_periph, uint16_t channel, uint32_t pulse)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CH0CV(timer_periph) = (uint32_t)pulse;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CH1CV(timer_periph) = (uint32_t)pulse;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CH2CV(timer_periph) = (uint32_t)pulse;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CH3CV(timer_periph) = (uint32_t)pulse;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output shadow function
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
    \param[in]  ocshadow: channel output shadow state
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_SHADOW_ENABLE: channel output shadow state enable
      \arg        TIMER_OC_SHADOW_DISABLE: channel output shadow state disable
    \param[out] none
    \retval     none
*/
void timer_channel_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow)
{
    uint32_t ctl;

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0COMSEN);
        ctl |= (uint32_t)ocshadow;
        TIMER_CHCTL0(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1COMSEN);
        ctl |= (uint32_t)((uint32_t)(ocshadow) << 8U);
        TIMER_CHCTL0(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH2COMSEN);
        ctl |= (uint32_t)ocshadow;
        TIMER_CHCTL1(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH3COMSEN);
        ctl |= (uint32_t)((uint32_t)(ocshadow) << 8U);
        TIMER_CHCTL1(timer_periph) = ctl;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output fast function
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
    \param[in]  ocfast: channel output fast function
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_FAST_ENABLE: channel output fast function enable
      \arg        TIMER_OC_FAST_DISABLE: channel output fast function disable
    \param[out] none
    \retval     none
*/
void timer_channel_output_fast_config(uint32_t timer_periph, uint16_t channel, uint16_t ocfast)
{
    uint32_t ctl;

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0COMFEN);
        ctl |= (uint32_t)ocfast;
        TIMER_CHCTL0(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1COMFEN);
        ctl |= (uint32_t)((uint32_t)ocfast << 8U);
        TIMER_CHCTL0(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH2COMFEN);
        ctl |= (uint32_t)ocfast;
        TIMER_CHCTL1(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH3COMFEN);
        ctl |= (uint32_t)((uint32_t)ocfast << 8U);
        TIMER_CHCTL1(timer_periph) = ctl;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output clear function
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0 (TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_1: TIMER channel1 (TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_2: TIMER channel2 (TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_3: TIMER channel3 (TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
    \param[in]  occlear: channel output clear function
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_CLEAR_ENABLE: channel output clear function enable
      \arg        TIMER_OC_CLEAR_DISABLE: channel output clear function disable
    \param[out] none
    \retval     none
*/
void timer_channel_output_clear_config(uint32_t timer_periph, uint16_t channel, uint16_t occlear)
{
    uint32_t ctl;

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0COMCEN);
        ctl |= (uint32_t)occlear;
        TIMER_CHCTL0(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1COMCEN);
        ctl |= (uint32_t)((uint32_t)occlear << 8U);
        TIMER_CHCTL0(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH2COMCEN);
        ctl |= (uint32_t)occlear;
        TIMER_CHCTL1(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH3COMCEN);
        ctl |= (uint32_t)((uint32_t)occlear << 8U);
        TIMER_CHCTL1(timer_periph) = ctl;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output polarity
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
    \param[in]  ocpolarity: channel output polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_POLARITY_HIGH: channel output polarity is high
      \arg        TIMER_OC_POLARITY_LOW: channel output polarity is low
    \param[out] none
    \retval     none
*/
void timer_channel_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocpolarity)
{
    uint32_t ctl;

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH0P);
        ctl |= (uint32_t)ocpolarity;
        TIMER_CHCTL2(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH1P);
        ctl |= (uint32_t)((uint32_t)ocpolarity << 4U);
        TIMER_CHCTL2(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH2P);
        ctl |= (uint32_t)((uint32_t)ocpolarity << 8U);
        TIMER_CHCTL2(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH3P);
        ctl |= (uint32_t)((uint32_t)ocpolarity << 12U);
        TIMER_CHCTL2(timer_periph) = ctl;
        break;
    default:
        break;
    }
}

#if defined(GD32L235)
/*!
    \brief      configure TIMER channel complementary output polarity 
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=0,14,40))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=0))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=0))
    \param[in]  ocnpolarity: channel complementary output polarity 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OCN_POLARITY_HIGH: channel complementary output polarity is high
      \arg        TIMER_OCN_POLARITY_LOW: channel complementary output polarity is low
    \param[out] none
    \retval     none
*/
void timer_channel_complementary_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnpolarity)
{
    switch(channel){
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NP);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocnpolarity;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NP);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocnpolarity << 4U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NP);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocnpolarity << 8U);
        break;
    default:
        break;
    }
}
#endif /* GD32L235 */

/*!
    \brief      configure TIMER channel enable state
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
    \param[in]  state: TIMER channel enable state
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CCX_ENABLE: channel enable
      \arg        TIMER_CCX_DISABLE: channel disable
    \param[out] none
    \retval     none
*/
void timer_channel_output_state_config(uint32_t timer_periph, uint16_t channel, uint32_t state)
{
    uint32_t ctl;

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        ctl |= (uint32_t)state;
        TIMER_CHCTL2(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        ctl |= (uint32_t)((uint32_t)state << 4U);
        TIMER_CHCTL2(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH2EN);
        ctl |= (uint32_t)((uint32_t)state << 8U);
        TIMER_CHCTL2(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL2_CH3EN);
        ctl |= (uint32_t)((uint32_t)state << 12U);
        TIMER_CHCTL2(timer_periph) = ctl;
        break;
    default:
        break;
    }
}

#if defined(GD32L235)
/*!
    \brief      configure TIMER channel complementary output enable state
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=0,14,40))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=0))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=0))
    \param[in]  ocnstate: TIMER channel complementary output enable state
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CCXN_ENABLE: channel complementary enable 
      \arg        TIMER_CCXN_DISABLE: channel complementary disable 
    \param[out] none
    \retval     none
*/
void timer_channel_complementary_output_state_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnstate)
{
    switch(channel){
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NEN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocnstate;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NEN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocnstate << 4U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NEN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocnstate << 8U);
        break;
    default:
        break;
    }
}
#endif /* GD32L235 */

/*!
    \brief      initialize TIMER channel input parameter struct with a default value
    \param[in]  icpara: TIMER channel intput parameter struct
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
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
     \param[in]  icpara: TIMER channel intput parameter struct
                 icpolarity: TIMER_IC_POLARITY_RISING,TIMER_IC_POLARITY_FALLING,TIMER_IC_POLARITY_BOTH_EDGE
                 icselection: TIMER_IC_SELECTION_DIRECTTI,TIMER_IC_SELECTION_INDIRECTTI,TIMER_IC_SELECTION_ITS
                 icprescaler: TIMER_IC_PSC_DIV1,TIMER_IC_PSC_DIV2,TIMER_IC_PSC_DIV4,TIMER_IC_PSC_DIV8
                 icfilter: 0~15
    \param[out]  none
    \retval      none
*/
void timer_input_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct *icpara)
{
    uint32_t ctl;

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);

        /* reset the CH0P and CH0NP bits */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        ctl |= (uint32_t)(icpara->icpolarity);
        TIMER_CHCTL2(timer_periph) = ctl;
        /* reset the CH0MS bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        ctl |= (uint32_t)(icpara->icselection);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* reset the CH0CAPFLT bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        ctl |= (uint32_t)((uint32_t)(icpara->icfilter) << 4U);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);

        /* reset the CH1P and CH1NP bits */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
        ctl |= (uint32_t)((uint32_t)(icpara->icpolarity) << 4U);
        TIMER_CHCTL2(timer_periph) = ctl;
        /* reset the CH1MS bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        ctl |= (uint32_t)((uint32_t)(icpara->icselection) << 8U);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* reset the CH1CAPFLT bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        ctl |= (uint32_t)((uint32_t)(icpara->icfilter) << 12U);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        /* reset the CH2EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);

        /* reset the CH2P and CH2NP bits */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)(TIMER_CHCTL2_CH2P | TIMER_CHCTL2_CH2NP));
        ctl |= (uint32_t)((uint32_t)(icpara->icpolarity) << 8U);
        TIMER_CHCTL2(timer_periph) = ctl;
        /* reset the CH2MS bit */
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH2MS);
        ctl |= (uint32_t)((uint32_t)(icpara->icselection));
        TIMER_CHCTL1(timer_periph) = ctl;
        /* reset the CH2CAPFLT bit */
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH2CAPFLT);
        ctl |= (uint32_t)((uint32_t)(icpara->icfilter) << 4U);
        TIMER_CHCTL1(timer_periph) = ctl;
        /* set the CH2EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH2EN;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        /* reset the CH3EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);

        /* reset the CH3P and CH3NP bits */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)(TIMER_CHCTL2_CH3P));
        ctl |= (uint32_t)((uint32_t)(icpara->icpolarity) << 12U);
        TIMER_CHCTL2(timer_periph) = ctl;
        /* reset the CH3MS bit */
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH3MS);
        ctl |= (uint32_t)((uint32_t)(icpara->icselection) << 8U);
        TIMER_CHCTL1(timer_periph) = ctl;
        /* reset the CH3CAPFLT bit */
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH3CAPFLT);
        ctl |= (uint32_t)((uint32_t)(icpara->icfilter) << 12U);
        TIMER_CHCTL1(timer_periph) = ctl;
        /* set the CH3EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH3EN;
        break;
    default:
        break;
    }
    /* configure TIMER channel input capture prescaler value */
    timer_channel_input_capture_prescaler_config(timer_periph, channel, (uint16_t)(icpara->icprescaler));
}

/*!
    \brief      configure TIMER channel input capture prescaler value
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
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
    uint32_t ctl;

    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0CAPPSC);
        ctl |= (uint32_t)prescaler;
        TIMER_CHCTL0(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1CAPPSC);
        ctl |= ((uint32_t)prescaler << 8U);
        TIMER_CHCTL0(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH2CAPPSC);
        ctl |= (uint32_t)prescaler;
        TIMER_CHCTL1(timer_periph) = ctl;
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        ctl = TIMER_CHCTL1(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL1_CH3CAPPSC);
        ctl |= ((uint32_t)prescaler << 8U);
        TIMER_CHCTL1(timer_periph) = ctl;
        break;
    default:
        break;
    }
}

/*!
    \brief      read TIMER channel capture compare register value
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_1: TIMER channel0(TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
    \param[out] none
    \retval     channel capture compare register value: 0~65535
*/
uint32_t timer_channel_capture_value_register_read(uint32_t timer_periph, uint16_t channel)
{
    uint32_t count_value = 0U;

    switch(channel) {
    /* read TIMER channel 0 capture compare register value */
    case TIMER_CH_0:
        count_value = TIMER_CH0CV(timer_periph);
        break;
    /* read TIMER channel 1 capture compare register value */
    case TIMER_CH_1:
        count_value = TIMER_CH1CV(timer_periph);
        break;
    /* read TIMER channel 2 capture compare register value */
    case TIMER_CH_2:
        count_value = TIMER_CH2CV(timer_periph);
        break;
    /* read TIMER channel 3 capture compare register value */
    case TIMER_CH_3:
        count_value = TIMER_CH3CV(timer_periph);
        break;
    default:
        break;
    }
    return (count_value);
}

/*!
    \brief      configure TIMER input pwm capture function
    \param[in]  timer_periph: (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
    \param[in]  channel: channel to be configured
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0
      \arg        TIMER_CH_1: TIMER channel1
     \param[in]  icpwm:TIMER channel intput pwm parameter struct
                 icpolarity: TIMER_IC_POLARITY_RISING,TIMER_IC_POLARITY_FALLING
                 icselection: TIMER_IC_SELECTION_DIRECTTI,TIMER_IC_SELECTION_INDIRECTTI
                 icprescaler: TIMER_IC_PSC_DIV1,TIMER_IC_PSC_DIV2,TIMER_IC_PSC_DIV4,TIMER_IC_PSC_DIV8
                 icfilter: 0~15
    \param[out] none
    \retval     none
*/
void timer_input_pwm_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct *icpwm)
{
    uint32_t ctl;

    uint16_t icpolarity  = 0x0U;
    uint16_t icselection = 0x0U;

    /* Set channel input polarity */
    if(TIMER_IC_POLARITY_RISING == icpwm->icpolarity) {
        icpolarity = TIMER_IC_POLARITY_FALLING;
    } else {
        icpolarity = TIMER_IC_POLARITY_RISING;
    }
    /* Set channel input mode selection */
    if(TIMER_IC_SELECTION_DIRECTTI == icpwm->icselection) {
        icselection = TIMER_IC_SELECTION_INDIRECTTI;
    } else {
        icselection = TIMER_IC_SELECTION_DIRECTTI;
    }

    if(TIMER_CH_0 == channel) {
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        /* set the CH0P and CH0NP bits */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        ctl |= (uint32_t)(icpwm->icpolarity);
        TIMER_CHCTL2(timer_periph) = ctl;
        /* set the CH0MS bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        ctl |= (uint32_t)(icpwm->icselection);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* set the CH0CAPFLT bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        ctl |= ((uint32_t)(icpwm->icfilter) << 4U);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_0, (uint16_t)(icpwm->icprescaler));

        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        /* set the CH1P and CH1NP bits */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
        ctl |= (uint32_t)((uint32_t)icpolarity << 4U);
        TIMER_CHCTL2(timer_periph) = ctl;

        /* set the CH1MS bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        ctl |= (uint32_t)((uint32_t)icselection << 8U);
        TIMER_CHCTL0(timer_periph) = ctl;

        /* set the CH1CAPFLT bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        ctl |= (uint32_t)((uint32_t)(icpwm->icfilter) << 12U);
        TIMER_CHCTL0(timer_periph) = ctl;

        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_1, (uint16_t)(icpwm->icprescaler));
    } else {
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        /* set the CH1P and CH1NP bits */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
        ctl |= (uint32_t)((uint32_t)(icpwm->icpolarity) << 4U);
        TIMER_CHCTL2(timer_periph) = ctl;
        /* set the CH1MS bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        ctl |= (uint32_t)((uint32_t)(icpwm->icselection) << 8U);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* set the CH1CAPFLT bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        ctl |= (uint32_t)((uint32_t)(icpwm->icfilter) << 12U);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_1, (uint16_t)(icpwm->icprescaler));

        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        /* set the CH0P and CH0NP bits */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        ctl |= (uint32_t)icpolarity;
        TIMER_CHCTL2(timer_periph) = ctl;
        /* set the CH0MS bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        ctl |= (uint32_t)icselection;
        TIMER_CHCTL0(timer_periph) = ctl;
        /* set the CH0CAPFLT bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        ctl |= ((uint32_t)(icpwm->icfilter) << 4U);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_0, (uint16_t)(icpwm->icprescaler));
    }
}

/*!
    \brief      configure TIMER hall sensor mode
    \param[in]  timer_periph: (TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
    \param[in]  hallmode: TIMER hall sensor mode state
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
        TIMER_CTL1(timer_periph) &= ~(uint32_t)TIMER_CTL1_TI0S;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      select TIMER input trigger source
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  intrigger: trigger selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SMCFG_TRGSEL_ITI0: internal trigger 0 (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_SMCFG_TRGSEL_ITI1: internal trigger 1 (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_SMCFG_TRGSEL_ITI2: internal trigger 2 (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_SMCFG_TRGSEL_ITI3: internal trigger 3 (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_SMCFG_TRGSEL_CI0F_ED: TI0 edge detector (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_SMCFG_TRGSEL_CI0FE0: filtered TIMER input 0 (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_SMCFG_TRGSEL_CI1FE1: filtered TIMER input 1 (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_SMCFG_TRGSEL_ETIFP: external trigger (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
    \param[out] none
    \retval     none
*/
void timer_input_trigger_source_select(uint32_t timer_periph, uint32_t intrigger)
{
#if defined(GD32L233)
    uint32_t ctl;

    ctl = TIMER_SMCFG(timer_periph);
    ctl &= (~(uint32_t)TIMER_SMCFG_TRGS);
    ctl |= (uint32_t)intrigger;
    TIMER_SMCFG(timer_periph) = ctl;
#endif /* GD32L233 */

#if defined(GD32L235)
    uint32_t TIMERxCFG_temp = 0U;
    volatile uint32_t *TIMERxCFG_addr;
    uint8_t i = 0U;
    switch(timer_periph){
    case TIMER0:
        TIMERxCFG_addr = &SYSCFG_TIMER0CFG;
        break;
    case TIMER1:
        TIMERxCFG_addr = &SYSCFG_TIMER1CFG;
        break;
    case TIMER2:
        TIMERxCFG_addr = &SYSCFG_TIMER2CFG;
        break;
    case TIMER8:
        TIMERxCFG_addr = &SYSCFG_TIMER8CFG;
        break;
    case TIMER11:
        TIMERxCFG_addr = &SYSCFG_TIMER11CFG;
        break;
    case TIMER14:
        TIMERxCFG_addr = &SYSCFG_TIMER14CFG;
        break;
    case TIMER40:
        TIMERxCFG_addr = &SYSCFG_TIMER40CFG;
        break;
    default:
         break;
     }
    TIMERxCFG_temp = REG32(TIMERxCFG_addr);

    if((TIMERxCFG_temp & 0xFFFFFFFFU) == 0U){
        TIMERxCFG_temp = (BITS(28,31) & ((uint32_t)(intrigger) << 28U));
    }else{
        for(i = 0U; i < 8U; i++){
          if((TIMERxCFG_temp & (BITS(0,3) << (i * 4U))) != 0U){
              break;
          }
        }
        TIMERxCFG_temp = ((BITS(0,3) << (i * 4U)) & ((uint32_t)(intrigger) << (i * 4U)));
    }

    REG32(TIMERxCFG_addr) = TIMERxCFG_temp;
#endif /* GD32L235 */
}

/*!
    \brief      select TIMER master mode output trigger source
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  outrigger: master mode control
                only one parameter can be selected which is shown as below:
      \arg        TIMER_TRI_OUT_SRC_RESET: the UPG bit as trigger output (TIMERx(x=1,2,5,6 for GD32L233, x=0,1,2,5,6,14,40 for GD32L235))
      \arg        TIMER_TRI_OUT_SRC_ENABLE: the counter enable signal TIMER_CTL0_CEN as trigger output (TIMERx(x=1,2,5,6 for GD32L233, x=0,1,2,5,6,14,40 for GD32L235))
      \arg        TIMER_TRI_OUT_SRC_UPDATE: update event as trigger output (TIMERx(x=1,2,5,6 for GD32L233, x=0,1,2,5,6,14,40 for GD32L235))
      \arg        TIMER_TRI_OUT_SRC_CH0: a capture or a compare match occurred in channal0 as trigger output TRGO (TIMERx(x=1,2 for GD32L233, x=0,1,2,14,40 for GD32L235))
      \arg        TIMER_TRI_OUT_SRC_O0CPRE: O0CPRE as trigger output (TIMERx(x=1,2 for GD32L233, x=0,1,2,14,40 for GD32L235))
      \arg        TIMER_TRI_OUT_SRC_O1CPRE: O1CPRE as trigger output (TIMERx(x=1,2 for GD32L233, x=0,1,2,14,40 for GD32L235))
      \arg        TIMER_TRI_OUT_SRC_O2CPRE: O2CPRE as trigger output (TIMERx(x=1,2 for GD32L233, x=0,1,2,14,40 for GD32L235))
      \arg        TIMER_TRI_OUT_SRC_O3CPRE: O3CPRE as trigger output (TIMERx(x=1,2 for GD32L233, x=0,1,2,14,40 for GD32L235))
    \param[out] none
    \retval     none
*/
void timer_master_output_trigger_source_select(uint32_t timer_periph, uint32_t outrigger)
{
    uint32_t ctl;

    ctl = TIMER_CTL1(timer_periph);
    ctl &= (~(uint32_t)TIMER_CTL1_MMC);
    ctl |= (uint32_t)outrigger;
    TIMER_CTL1(timer_periph) = ctl;
}

/*!
    \brief      select TIMER slave mode
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  slavemode: slave mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SLAVE_MODE_DISABLE: slave mode disable
      \arg        TIMER_QUAD_DECODER_MODE0: quadrature decoder mode 0 (TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_QUAD_DECODER_MODE1: quadrature decoder mode 1 (TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_QUAD_DECODER_MODE2: quadrature decoder mode 2 (TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235))
      \arg        TIMER_SLAVE_MODE_RESTART: restart mode (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_SLAVE_MODE_PAUSE: pause mode (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_SLAVE_MODE_EVENT: event mode (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
      \arg        TIMER_SLAVE_MODE_EXTERNAL0: external clock mode 0 (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
    \param[out] none
    \retval     none
*/
void timer_slave_mode_select(uint32_t timer_periph, uint32_t slavemode)
{
#if defined(GD32L233)
    uint32_t ctl;

    ctl = TIMER_SMCFG(timer_periph);
    ctl &= (~(uint32_t)TIMER_SMCFG_SMC);
    ctl |= (uint32_t)slavemode;
    TIMER_SMCFG(timer_periph) = ctl;
#endif /* GD32L233 */

#if defined(GD32L235)
    uint32_t TIMERxCFG_temp = 0U;
    volatile uint32_t *TIMERxCFG_addr;
    uint32_t trigger_temp = 0U;
    uint8_t i = 0U;
    switch(timer_periph){
    case TIMER0:
        TIMERxCFG_addr = &SYSCFG_TIMER0CFG;
        break;
    case TIMER1:
        TIMERxCFG_addr = &SYSCFG_TIMER1CFG;
        break;
    case TIMER2:
        TIMERxCFG_addr = &SYSCFG_TIMER2CFG;
        break;
    case TIMER8:
        TIMERxCFG_addr = &SYSCFG_TIMER8CFG;
        break;
    case TIMER11:
        TIMERxCFG_addr = &SYSCFG_TIMER11CFG;
        break;
    case TIMER14:
        TIMERxCFG_addr = &SYSCFG_TIMER14CFG;
        break;
    case TIMER40:
        TIMERxCFG_addr = &SYSCFG_TIMER40CFG;
        break;
    default:
         break;
     }
    TIMERxCFG_temp = REG32(TIMERxCFG_addr);
    if((TIMERxCFG_temp & 0xFFFFFFFFU) == 0U){
        TIMERxCFG_temp = 0xFU << (slavemode * 4U);
    }else{
        for(i = 0U; i < 8U; i++){
            if((TIMERxCFG_temp & (BITS(0,3) << (i * 4U))) != 0U){
                break;
            }
        }
        trigger_temp = (TIMERxCFG_temp & (BITS(0,3) << (i * 4U))) >> (i * 4U);
        TIMERxCFG_temp = trigger_temp << (slavemode * 4U);
    }
    REG32(TIMERxCFG_addr) = TIMERxCFG_temp;
#endif /* GD32L235 */
}

/*!
    \brief      configure TIMER master slave mode
    \param[in]  timer_periph: (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
    \param[in]  masterslave: master slave mode state
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
        TIMER_SMCFG(timer_periph) &= ~(uint32_t)TIMER_SMCFG_MSM;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure TIMER external trigger input
    \param[in]  timer_periph: TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
    \param[in]  extprescaler: external trigger prescaler
                only one parameter can be selected which is shown as below:
      \arg        TIMER_EXT_TRI_PSC_OFF: no divided
      \arg        TIMER_EXT_TRI_PSC_DIV2: divided by 2
      \arg        TIMER_EXT_TRI_PSC_DIV4: divided by 4
      \arg        TIMER_EXT_TRI_PSC_DIV8: divided by 8
    \param[in]  extpolarity:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_ETP_FALLING: active low or falling edge active
      \arg        TIMER_ETP_RISING: active high or rising edge active
    \param[in]  extfilter: a value between 0 and 15
    \param[out] none
    \retval     none
*/
void timer_external_trigger_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter)
{
    uint32_t ctl;

    ctl = TIMER_SMCFG(timer_periph);
    ctl &= (~(uint32_t)(TIMER_SMCFG_ETP | TIMER_SMCFG_ETPSC | TIMER_SMCFG_ETFC));
    ctl |= (uint32_t)(extprescaler | extpolarity);
    ctl |= (uint32_t)(extfilter << 8U);
    TIMER_SMCFG(timer_periph) = ctl;
}

/*!
    \brief      configure TIMER quadrature decoder mode
    \param[in]  timer_periph: TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
    \param[in]  decomode: quadrature decoder mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_QUAD_DECODER_MODE0: counter counts on CI0FE0 edge depending on CI1FE1 level
      \arg        TIMER_QUAD_DECODER_MODE1: counter counts on CI1FE1 edge depending on CI0FE0 level
      \arg        TIMER_QUAD_DECODER_MODE2: counter counts on both CI0FE0 and CI1FE1 edges depending on the level of the other input
    \param[in]  ic0polarity: IC0 polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_IC_POLARITY_RISING: capture rising edge
      \arg        TIMER_IC_POLARITY_FALLING: capture falling edge
      \arg        TIMER_IC_POLARITY_BOTH_EDGE: active both edge
    \param[in]  ic1polarity: IC1 polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_IC_POLARITY_RISING: capture rising edge
      \arg        TIMER_IC_POLARITY_FALLING: capture falling edge
      \arg        TIMER_IC_POLARITY_BOTH_EDGE: active both edge
    \param[out] none
    \retval     none
*/
void timer_quadrature_decoder_mode_config(uint32_t timer_periph, uint32_t decomode, uint16_t ic0polarity, uint16_t ic1polarity)
{
    uint32_t ctl;
#if defined(GD32L233)
    /* configure the quadrature decoder mode */
    ctl = TIMER_SMCFG(timer_periph);
    ctl &= (~(uint32_t)TIMER_SMCFG_SMC);
    ctl |= (uint32_t)decomode;
    TIMER_SMCFG(timer_periph) = ctl;
#endif /* GD32L233 */
#if defined(GD32L235)
    /* configure the quadrature decoder mode */
    timer_slave_mode_select(timer_periph, decomode);
#endif /* GD32L235 */
    /* configure input capture selection */
    ctl = TIMER_CHCTL0(timer_periph);
    ctl &= (uint32_t)(((~(uint32_t)TIMER_CHCTL0_CH0MS)) & ((~(uint32_t)TIMER_CHCTL0_CH1MS)));
    ctl |= (uint32_t)(TIMER_IC_SELECTION_DIRECTTI | ((uint32_t)TIMER_IC_SELECTION_DIRECTTI << 8U));
    TIMER_CHCTL0(timer_periph) = ctl;
    /* configure channel input capture polarity */
    ctl = TIMER_CHCTL2(timer_periph);
    ctl &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
    ctl &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
    ctl |= ((uint32_t)ic0polarity | ((uint32_t)ic1polarity << 4U));
    TIMER_CHCTL2(timer_periph) = ctl;
}

/*!
    \brief      configure TIMER internal clock mode
    \param[in]  timer_periph: TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_internal_clock_config(uint32_t timer_periph)
{
#if defined(GD32L233)
    TIMER_SMCFG(timer_periph) &= ~(uint32_t)TIMER_SMCFG_SMC;
#endif /* GD32L233 */
#if defined(GD32L235)
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_DISABLE);
#endif /* GD32L235 */
}

/*!
    \brief      configure TIMER the internal trigger as external clock input
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  intrigger: trigger selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SMCFG_TRGSEL_ITI0: internal trigger 0 TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_SMCFG_TRGSEL_ITI1: internal trigger 1 TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_SMCFG_TRGSEL_ITI2: internal trigger 2 TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_SMCFG_TRGSEL_ITI3: internal trigger 3 TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_internal_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t intrigger)
{
#if defined(GD32L233)
    uint32_t ctl;
    timer_input_trigger_source_select(timer_periph, intrigger);
    ctl = TIMER_SMCFG(timer_periph);
    ctl &= ~(uint32_t)TIMER_SMCFG_SMC;
    ctl |= (uint32_t)TIMER_SLAVE_MODE_EXTERNAL0;
    TIMER_SMCFG(timer_periph) = ctl;
#endif /* GD32L233 */
#if defined(GD32L235)
    /* select TIMER input trigger source */
    timer_input_trigger_source_select(timer_periph, intrigger);
    /* select TIMER slave mode */
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_EXTERNAL0);
#endif /* GD32L235 */
}

/*!
    \brief      configure TIMER the external trigger as external clock input
    \param[in]  timer_periph: TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
    \param[in]  extrigger: external trigger selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SMCFG_TRGSEL_CI0F_ED: TI0 edge detector TIMERx(x=0,1,2,8,11,14,40)
      \arg        TIMER_SMCFG_TRGSEL_CI0FE0: filtered TIMER input 0 TIMERx(x=0,1,2,8,11,14,40)
      \arg        TIMER_SMCFG_TRGSEL_CI1FE1: filtered TIMER input 1 TIMERx(x=0,1,2,8,11,14,40)
    \param[in]  extpolarity: external trigger polarity
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
    uint32_t ctl;

    if(TIMER_SMCFG_TRGSEL_CI1FE1 == extrigger) {
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        /* set the CH1NP bit */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
        ctl |= (uint32_t)((uint32_t)extpolarity << 4U);
        TIMER_CHCTL2(timer_periph) = ctl;
        /* set the CH1MS bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        ctl |= (uint32_t)((uint32_t)TIMER_IC_SELECTION_DIRECTTI << 8U);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* set the CH1CAPFLT bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        ctl |= (uint32_t)(extfilter << 12U);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
    } else {
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        /* set the CH0P and CH0NP bits */
        ctl = TIMER_CHCTL2(timer_periph);
        ctl &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        ctl |= (uint32_t)extpolarity;
        TIMER_CHCTL2(timer_periph) = ctl;
        /* set the CH0MS bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        ctl |= (uint32_t)TIMER_IC_SELECTION_DIRECTTI;
        TIMER_CHCTL0(timer_periph) = ctl;
        /* reset the CH0CAPFLT bit */
        ctl = TIMER_CHCTL0(timer_periph);
        ctl &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        ctl |= (uint32_t)(extfilter << 4U);
        TIMER_CHCTL0(timer_periph) = ctl;
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
    }
#if defined(GD32L233)
    /* select TIMER input trigger source */
    timer_input_trigger_source_select(timer_periph, extrigger);
    /* set the SMC bit */
    ctl = TIMER_SMCFG(timer_periph);
    ctl &= (~(uint32_t)TIMER_SMCFG_SMC);
    ctl |= (uint32_t)TIMER_SLAVE_MODE_EXTERNAL0;
    TIMER_SMCFG(timer_periph) = ctl;
#endif /* GD32L233 */
#if defined(GD32L235)
    /* select TIMER slave mode */
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_EXTERNAL0);
    /* select TIMER input trigger source */
    timer_input_trigger_source_select(timer_periph, extrigger);
#endif /* GD32L235 */
}

/*!
    \brief      configure TIMER the external clock mode0
    \param[in]  timer_periph: TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
    \param[in]  extprescaler: ETI external trigger prescaler
                only one parameter can be selected which is shown as below:
      \arg        TIMER_EXT_TRI_PSC_OFF: no divided
      \arg        TIMER_EXT_TRI_PSC_DIV2: divided by 2
      \arg        TIMER_EXT_TRI_PSC_DIV4: divided by 4
      \arg        TIMER_EXT_TRI_PSC_DIV8: divided by 8
    \param[in]  extpolarity: ETI external trigger polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_ETP_FALLING: active low or falling edge active
      \arg        TIMER_ETP_RISING: active high or rising edge active
    \param[in]  extfilter: a value between 0 and 15
    \param[out] none
    \retval     none
*/
void timer_external_clock_mode0_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter)
{
#if defined(GD32L233)
    uint32_t ctl;
    /* configure TIMER external trigger input */
    timer_external_trigger_config(timer_periph, extprescaler, extpolarity, extfilter);

    /* set the SMC bit,TRGS bit */
    ctl = TIMER_SMCFG(timer_periph);
    ctl &= (~(uint32_t)(TIMER_SMCFG_SMC | TIMER_SMCFG_TRGS));
    ctl |= (uint32_t)(TIMER_SLAVE_MODE_EXTERNAL0 | TIMER_SMCFG_TRGSEL_ETIFP);
    TIMER_SMCFG(timer_periph) = ctl;
#endif /* GD32L233 */
#if defined(GD32L235)
    /* configure TIMER external trigger input */
    timer_external_trigger_config(timer_periph, extprescaler, extpolarity, extfilter);
    /* select TIMER slave mode */
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_EXTERNAL0);
    /* select TIMER input trigger source */
    timer_input_trigger_source_select(timer_periph, TIMER_SMCFG_TRGSEL_ETIFP);
#endif /* GD32L235 */
}

/*!
    \brief      configure TIMER the external clock mode1
    \param[in]  timer_periph: TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
    \param[in]  extprescaler: ETI external trigger prescaler
                only one parameter can be selected which is shown as below:
      \arg        TIMER_EXT_TRI_PSC_OFF: no divided
      \arg        TIMER_EXT_TRI_PSC_DIV2: divided by 2
      \arg        TIMER_EXT_TRI_PSC_DIV4: divided by 4
      \arg        TIMER_EXT_TRI_PSC_DIV8: divided by 8
    \param[in]  extpolarity: ETI external trigger polarity
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
    \param[in]  timer_periph: TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_external_clock_mode1_disable(uint32_t timer_periph)
{
    TIMER_SMCFG(timer_periph) &= ~(uint32_t)TIMER_SMCFG_SMC1;
}

/*!
    \brief      configure TIMER channel remap function
    \param[in]  timer_periph:  TIMERx(x=8,11)
    \param[in]  remap: remap function selection
                only one parameter can be selected which is shown as below:
      \arg        TIMER8_CI0_RMP_GPIO: timer8 channel 0 input is connected to GPIO(TIMER8_CH0) TIMERx(x=8)
      \arg        TIMER8_CI0_RMP_LXTAL: timer8 channel 0 input is connected to the LXTAL TIMERx(x=8)
      \arg        TIMER8_CI0_RMP_HXTAL_DIV32: timer8 channel 0 input is connected to HXTAL/32 clock TIMERx(x=8)
      \arg        TIMER8_CI0_RMP_CKOUTSEL: timer8 channel 0 input is connected to CKOUTSEL TIMERx(x=8)
      \arg        TIMER11_CI0_RMP_GPIO: timer11 channel 0 input is connected to GPIO(TIMER11_CH0) TIMERx(x=11)
      \arg        TIMER11_CI0_RMP_IRC32K: timer11 channel 0 input is connected to the IRC32K TIMERx(x=11)
      \arg        TIMER11_CI0_RMP_LXTAL: timer11 channel 0 input is connected to LXTAL clock TIMERx(x=11)
      \arg        TIMER11_CI0_RMP_RTC_OUT: timer11 channel 0 input is connected to RTC_OUT TIMERx(x=11)
    \param[out] none
    \retval     none
*/
void timer_channel_remap_config(uint32_t timer_periph, uint32_t remap)
{
    TIMER_IRMP(timer_periph) = (uint32_t)remap;
}

/*!
    \brief      configure TIMER write CHxVAL register selection
    \param[in]  timer_periph: (TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235))
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
        TIMER_CFG(timer_periph) &= ~(uint32_t)TIMER_CFG_CHVSEL;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      get TIMER flags
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  flag: the timer interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        TIMER_FLAG_UP: update flag,TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH0: channel 0 flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH1: channel 1 flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH2: channel 2 flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_FLAG_CH3: channel 3 flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_FLAG_CMT: channel control update flag,TIMERx(x=0,14,40 for GD32L235)
      \arg        TIMER_FLAG_TRG: trigger flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_BRK: break flag,TIMERx(x=0,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH0O: channel 0 overcapture flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH1O: channel 1 overcapture flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH2O: channel 2 overcapture flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_FLAG_CH3O: channel 3 overcapture flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
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
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  flag: the timer interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        TIMER_FLAG_UP: update flag,TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH0: channel 0 flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH1: channel 1 flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH2: channel 2 flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_FLAG_CH3: channel 3 flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_FLAG_CMT: channel control update flag,TIMERx(x=0,14,40 for GD32L235)
      \arg        TIMER_FLAG_TRG: trigger flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_BRK: break flag,TIMERx(x=0,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH0O: channel 0 overcapture flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH1O: channel 1 overcapture flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_FLAG_CH2O: channel 2 overcapture flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_FLAG_CH3O: channel 3 overcapture flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_flag_clear(uint32_t timer_periph, uint32_t flag)
{
    TIMER_INTF(timer_periph) = (~(uint32_t)flag);
}

/*!
    \brief      enable the TIMER interrupt
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  interrupt: timer interrupt enable source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_INT_UP: update interrupt enable, TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_CH0: channel 0 interrupt enable, TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_CH1: channel 1 interrupt enable, TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_CH2: channel 2 interrupt enable, TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_INT_CH3: channel 3 interrupt enable, TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_INT_CMT: commutation interrupt enable, TIMERx(x=0,14,40 for GD32L235)
      \arg        TIMER_INT_TRG: trigger interrupt enable, TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_BRK: break interrupt enable, TIMERx(x=0,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_interrupt_enable(uint32_t timer_periph, uint32_t interrupt)
{
    TIMER_DMAINTEN(timer_periph) |= (uint32_t) interrupt;
}

/*!
    \brief      disable the TIMER interrupt
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  interrupt: timer interrupt source disable
                only one parameter can be selected which is shown as below:
      \arg        TIMER_INT_UP: update interrupt enable, TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_CH0: channel 0 interrupt enable, TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_CH1: channel 1 interrupt enable, TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_CH2: channel 2 interrupt enable, TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_INT_CH3: channel 3 interrupt enable, TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_INT_CMT: commutation interrupt enable, TIMERx(x=0,14,40 for GD32L235)
      \arg        TIMER_INT_TRG: trigger interrupt enable, TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_BRK: break interrupt enable, TIMERx(x=0,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_interrupt_disable(uint32_t timer_periph, uint32_t interrupt)
{
    TIMER_DMAINTEN(timer_periph) &= (~(uint32_t)interrupt);
}

/*!
    \brief      get timer interrupt flag
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  int_flag: the timer interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        TIMER_INT_FLAG_UP: update interrupt flag,TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_FLAG_CH0: channel 0 interrupt flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_FLAG_CH1: channel 1 interrupt flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_FLAG_CH2: channel 2 interrupt flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_INT_FLAG_CH3: channel 3 interrupt flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_INT_FLAG_CMT: channel commutation interrupt flag,TIMERx(x=0,14,40 for GD32L235)
      \arg        TIMER_INT_FLAG_TRG: trigger interrupt flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_FLAG_BRK:  break interrupt flag,TIMERx(x=0,14,40 for GD32L235)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus timer_interrupt_flag_get(uint32_t timer_periph, uint32_t int_flag)
{
    uint32_t val;
    val = (TIMER_DMAINTEN(timer_periph) & int_flag);
    if((RESET != (TIMER_INTF(timer_periph) & int_flag)) && (RESET != val)) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear TIMER interrupt flag
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  int_flag: the timer interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        TIMER_INT_FLAG_UP: update interrupt flag,TIMERx(x=1,2,5,6,8,11 for GD32L233, x=0,1,2,5,6,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_FLAG_CH0: channel 0 interrupt flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_FLAG_CH1: channel 1 interrupt flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_FLAG_CH2: channel 2 interrupt flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_INT_FLAG_CH3: channel 3 interrupt flag,TIMERx(x=1,2 for GD32L233, x=0,1,2 for GD32L235)
      \arg        TIMER_INT_FLAG_CMT: channel commutation interrupt flag,TIMERx(x=0,14,40 for GD32L235)
      \arg        TIMER_INT_FLAG_TRG: trigger interrupt flag,TIMERx(x=1,2,8,11 for GD32L233, x=0,1,2,8,11,14,40 for GD32L235)
      \arg        TIMER_INT_FLAG_BRK:  break interrupt flag,TIMERx(x=0,14,40 for GD32L235)
    \param[out] none
    \retval     none
*/
void timer_interrupt_flag_clear(uint32_t timer_periph, uint32_t int_flag)
{
    TIMER_INTF(timer_periph) = (~(uint32_t)int_flag);
}
