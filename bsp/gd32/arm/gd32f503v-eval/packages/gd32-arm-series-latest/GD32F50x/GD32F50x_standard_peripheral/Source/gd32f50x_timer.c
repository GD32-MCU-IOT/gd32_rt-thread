/*!
    \file    gd32f50x_timer.c
    \brief   TIMER driver

    \version 2026-02-25, V1.0.4, firmware for GD32F50x
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

#include "gd32f50x_timer.h"

/* TIMER init parameter mask */
#define TIMER_DMA_MASK              ((uint32_t)0x01007F00U)   /*!< TIMER dma mask */
#define TIMER_SMCFG_TRGSEL_MASK     ((uint32_t)0x0000001FU)   /*!< TIMER smcfg trigsel mask */
#define TIMER_BREAK_SOURCE_MASK     ((uint32_t)0x00000201U)   /*!< TIMER dma mask */
#define TIMER_CHANNEL_MASK          ((uint16_t)0x0003U)       /*!< TIMER channel mask */

/*!
    \brief      deinit a TIMER (API_ID(0x0001U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[out] none
    \retval     none
*/
void timer_deinit(uint32_t timer_periph)
{
    switch(timer_periph){
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
    default:
        break;
    }
}

/*!
    \brief      initialize TIMER init parameter struct with a default value (API_ID(0x0002U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void timer_struct_para_init(timer_parameter_struct* initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(TIMER_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        initpara->prescaler         = 0U;
        initpara->alignedmode       = TIMER_COUNTER_EDGE;
        initpara->counterdirection  = TIMER_COUNTER_UP;
        initpara->period            = 0xFFFFFFFFU;
        initpara->clockdivision     = TIMER_CKDIV_DIV1;
        initpara->repetitioncounter = 0U;
    }
}

/*!
    \brief      initialize TIMER counter (API_ID(0x0003U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[in]  initpara: init parameter struct
                  prescaler: prescaler value of the counter clock, 0~65535
                  alignedmode: TIMER_COUNTER_EDGE, TIMER_COUNTER_CENTER_DOWN, TIMER_COUNTER_CENTER_UP, TIMER_COUNTER_CENTER_BOTH
                  counterdirection: TIMER_COUNTER_UP, TIMER_COUNTER_DOWN
                  period: counter auto reload value, 0~0xFFFF(TIMERx(x=0,2,3,4,5,6,7,15,16))
                                                     0~0xFFFFFFFF(TIMERx(x=1))
                  clockdivision: TIMER_CKDIV_DIV1, TIMER_CKDIV_DIV2, TIMER_CKDIV_DIV4
                  repetitioncounter: counter repetition value, 0~255
    \param[out] none
    \retval     none
*/
void timer_init(uint32_t timer_periph, timer_parameter_struct* initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(TIMER_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure the counter prescaler value */
        TIMER_PSC(timer_periph) = (uint16_t)initpara->prescaler;
    
        /* configure the counter direction and aligned mode */
        if((TIMER0 == timer_periph) || (TIMER1 == timer_periph) || (TIMER2 == timer_periph)|| (TIMER3 == timer_periph) 
            || (TIMER4 == timer_periph) || (TIMER15 == timer_periph)|| (TIMER16 == timer_periph)||(TIMER7 == timer_periph)){
            TIMER_CTL0(timer_periph) &= ~(uint32_t)(TIMER_CTL0_DIR|TIMER_CTL0_CAM);
            TIMER_CTL0(timer_periph) |= (uint32_t)(initpara->alignedmode & TIMER_CTL0_CAM);
            TIMER_CTL0(timer_periph) |= (uint32_t)(initpara->counterdirection & TIMER_CTL0_DIR);
        }
    
        /* configure the autoreload value */
        TIMER_CAR(timer_periph) = (uint32_t)initpara->period;

    
        /* configure the clock division value */
        if((TIMER5 != timer_periph) && (TIMER6 != timer_periph)){
            /* reset the CKDIV bit */
            TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_CKDIV;
            TIMER_CTL0(timer_periph) |= (uint32_t)(initpara->clockdivision & TIMER_CTL0_CKDIV);
        }
    
        /* configure the repetition counter value */
        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph) || (TIMER15 == timer_periph)|| (TIMER16 == timer_periph)){
            TIMER_CREP0(timer_periph) = (uint32_t)initpara->repetitioncounter;
        }
    
        /* generate an update event */
        TIMER_SWEVG(timer_periph) |= (uint32_t)TIMER_SWEVG_UPG;
    }
}

/*!
    \brief      enable a TIMER (API_ID(0x0004U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[out] none
    \retval     none
*/
void timer_enable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_CEN;
}

/*!
    \brief      disable a TIMER (API_ID(0x0005U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[out] none
    \retval     none
*/
void timer_disable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_CEN);
}

/*!
    \brief      enable the auto reload shadow function (API_ID(0x0006U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[out] none
    \retval     none
*/
void timer_auto_reload_shadow_enable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_ARSE;
}

/*!
    \brief      disable the auto reload shadow function (API_ID(0x0007U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[out] none
    \retval     none
*/
void timer_auto_reload_shadow_disable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_ARSE);
}

/*!
    \brief      enable the update event (API_ID(0x0008U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[out] none
    \retval     none
*/
void timer_update_event_enable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_UPDIS);
}

/*!
    \brief      disable the update event (API_ID(0x0009U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[out] none
    \retval     none
*/
void timer_update_event_disable(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t) TIMER_CTL0_UPDIS;
}

/*!
    \brief      set TIMER counter alignment mode (API_ID(0x000AU))
    \param[in]  timer_periph: TIMERx(x=0..4,7,15,16)
    \param[in]  aligned:
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
    TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_CAM);
    TIMER_CTL0(timer_periph) |= ((uint32_t)aligned & TIMER_CTL0_CAM);
}

/*!
    \brief      set TIMER counter up direction (API_ID(0x000BU))
    \param[in]  timer_periph: TIMERx(x=0..4,7,15,16)
    \param[out] none
    \retval     none
*/
void timer_counter_up_direction(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) &= (~(uint32_t)TIMER_CTL0_DIR);
}

/*!
    \brief      set TIMER counter down direction  (API_ID(0x000CU))
    \param[in]  timer_periph: TIMERx(x=0..4,7,15,16)
    \param[out] none
    \retval     none
*/
void timer_counter_down_direction(uint32_t timer_periph)
{
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_DIR;
}

/*!
    \brief      configure TIMER prescaler  (API_ID(0x000DU))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[in]  prescaler: prescaler value,0~65535
    \param[in]  pscreload: prescaler reload mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_PSC_RELOAD_NOW: the prescaler is loaded right now
      \arg        TIMER_PSC_RELOAD_UPDATE: the prescaler is loaded at the next update event
    \param[out] none
    \retval     none
*/
void timer_prescaler_config(uint32_t timer_periph, uint16_t prescaler, uint8_t pscreload)
{
    TIMER_PSC(timer_periph) = (uint32_t)prescaler;
    
    if(TIMER_PSC_RELOAD_NOW == pscreload){
        TIMER_SWEVG(timer_periph) |= (uint32_t)TIMER_SWEVG_UPG;
    }
}

/*!
    \brief      configure TIMER repetition register value (API_ID(0x000EU))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[in]  repetition: the counter repetition value,0~255
    \param[out] none
    \retval     none
*/
void timer_repetition_value_config(uint32_t timer_periph, uint16_t repetition)
{
    TIMER_CREP0(timer_periph) = (uint32_t)repetition;
} 

/*!
    \brief      read TIMER runtime repetition register value (API_ID(0x000FU))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[out] none
    \retval     counter repetition value in TIMER_CREP0 register, 0~0xFF
*/
uint32_t timer_runtime_repetition_value_read(uint32_t timer_periph)
{
    return (uint32_t)(TIMER_CREP0(timer_periph));
}

/*!
    \brief      configure TIMER autoreload register value  (API_ID(0x0010U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[in]  autoreload: the counter auto-reload value, 0~0xFFFF, TIMERx(x=0,2,3,4,5,6,7,15,16)
                                                           0~0xFFFFFFFF, TIMERx(x=1)
    \param[out] none
    \retval     none
*/
void timer_autoreload_value_config(uint32_t timer_periph, uint32_t autoreload)
{
    /* configure other TIMER autoreload register value (32-bit or 16-bit) */
    TIMER_CAR(timer_periph) = (uint32_t)autoreload;
}

/*!
    \brief      get TIMER autoreload register value (API_ID(0x0011U))
    \param[in]  timer_periph: TIMERx(x=0~7,15,16)
    \param[out] none
    \retval     counter auto reload register value, 0~0xFFFF, TIMERx(x=0,2,3,4,5,6,7,15,16)
                                                    0~0xFFFFFFFF, TIMERx(x=1)
*/
uint32_t timer_autoreload_value_read(uint32_t timer_periph)
{
    return (uint32_t)(TIMER_CAR(timer_periph));
}

/*!
    \brief      configure TIMER counter register value (API_ID(0x0012U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[in]  counter: the counter value: 0~0xFFFF, TIMERx(x=0,2,3,4,5,6,7,15,16)
                                            0~0xFFFFFFFF, TIMERx(x=1)
    \param[out] none
    \retval     none
*/         
void timer_counter_value_config(uint32_t timer_periph, uint32_t counter)
{
    TIMER_CNT(timer_periph) = (uint32_t)counter;
}

/*!
    \brief      read TIMER counter value (API_ID(0x0013U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[out] none
    \retval     counter value: 0~0xFFFF, TIMERx(x=0,2,3,4,5,6,7,15,16)
                               0~0xFFFFFFFF, TIMERx(x=1)
*/
uint32_t timer_counter_read(uint32_t timer_periph)
{
    return (uint32_t)(TIMER_CNT(timer_periph));
}

/*!
    \brief      read TIMER prescaler value (API_ID(0x0014U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[out] none
    \retval     prescaler register value
*/         
uint16_t timer_prescaler_read(uint32_t timer_periph)
{
    uint16_t prescaler_value = 0U;
    prescaler_value = (uint16_t)(TIMER_PSC(timer_periph));
    return (prescaler_value);
}

/*!
    \brief      configure TIMER single pulse mode (API_ID(0x0015U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[in]  spmode:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SP_MODE_SINGLE: single pulse mode
      \arg        TIMER_SP_MODE_REPETITIVE: repetitive pulse mode
    \param[out] none
    \retval     none
*/
void timer_single_pulse_mode_config(uint32_t timer_periph, uint32_t spmode)
{
    if(TIMER_SP_MODE_SINGLE == spmode){
        TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_SPM;
    }else if(TIMER_SP_MODE_REPETITIVE == spmode){
        TIMER_CTL0(timer_periph) &= ~((uint32_t)TIMER_CTL0_SPM);
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure TIMER update source (API_ID(0x0016U))
    \param[in]  timer_periph: TIMERx(x=0..7,15,16)
    \param[in]  update: 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_UPDATE_SRC_GLOBAL: update generate by setting of UPG bit or the counter overflow/underflow,
                                           or the slave mode controller trigger
      \arg        TIMER_UPDATE_SRC_REGULAR: update generate only by counter overflow/underflow
    \param[out] none
    \retval     none
*/
void timer_update_source_config(uint32_t timer_periph, uint32_t update)
{
    if(TIMER_UPDATE_SRC_REGULAR == update){
        TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_UPS;
    }else if(TIMER_UPDATE_SRC_GLOBAL == update){
        TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_UPS;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      enable the TIMER DMA (API_ID(0x0017U))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  dma: specify which DMA to enable
                only one parameter can be selected which is shown as below:
      \arg        TIMER_DMA_UPD:  update DMA enable,TIMERx(x=0,7,1,2,3,4,5,6,15,16)
      \arg        TIMER_DMA_CH0D: channel 0 DMA enable,TIMERx(x=0,7,1,2,3,4,15,16)
      \arg        TIMER_DMA_CH1D: channel 1 DMA enable,TIMERx(x=0,7,1,2,3,4,15,16)
      \arg        TIMER_DMA_CH2D: channel 2 DMA enable,TIMERx(x=0,7,1,2,3,4)
      \arg        TIMER_DMA_CH3D: channel 3 DMA enable,TIMERx(x=0,7,1,2,3,4)
      \arg        TIMER_DMA_CMTD: commutation DMA request enable,TIMERx(x=0,7,15,16)
      \arg        TIMER_DMA_TRGD: trigger DMA enable,TIMERx(x=0,7,1,2,3,4,15,16)
      \arg        TIMER_DMA_MCH0D: multi mode channel 0 DMA request, TIMERx(x=15,16)
    \param[out] none
    \retval     none
*/
void timer_dma_enable(uint32_t timer_periph, uint32_t dma)
{
    TIMER_DMAINTEN(timer_periph) |= (uint32_t)(dma & TIMER_DMA_MASK);
}

/*!
    \brief      disable the TIMER DMA (API_ID(0x0018U))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  dma: specify which DMA to enable
                one or more parameters can be selected which are shown as below:
      \arg        TIMER_DMA_UPD:  update DMA enable,TIMERx(x=0,7,1,2,3,4,5,6,15,16)
      \arg        TIMER_DMA_CH0D: channel 0 DMA enable,TIMERx(x=0,7,1,2,3,4,15,16)
      \arg        TIMER_DMA_CH1D: channel 1 DMA enable,TIMERx(x=0,7,1,2,3,4,15,16)
      \arg        TIMER_DMA_CH2D: channel 2 DMA enable,TIMERx(x=0,7,1,2,3,4)
      \arg        TIMER_DMA_CH3D: channel 3 DMA enable,TIMERx(x=0,7,1,2,3,4)
      \arg        TIMER_DMA_CMTD: commutation DMA request enable,TIMERx(x=0,7,15,16)
      \arg        TIMER_DMA_TRGD: trigger DMA enable,TIMERx(x=0,7,1,2,3,4,15,16)
      \arg        TIMER_DMA_MCH0D: multi mode channel 0 DMA request, TIMERx(x=15,16)
    \param[out] none
    \retval     none
*/
void timer_dma_disable(uint32_t timer_periph, uint32_t dma)
{
    TIMER_DMAINTEN(timer_periph) &= (~(uint32_t)(dma & TIMER_DMA_MASK)); 
}

/*!
    \brief      channel DMA request source selection (API_ID(0x0019U))
    \param[in]  timer_periph: TIMERx(x=0..4,7,15,16)
    \param[in]  dma_request: channel DMA request source selection
                only one parameter can be selected which is shown as below:
       \arg        TIMER_DMAREQUEST_CHANNELEVENT: DMA request of channel y is sent when channel y event occurs
       \arg        TIMER_DMAREQUEST_UPDATEEVENT: DMA request of channel y is sent when update event occurs 
    \param[out] none
    \retval     none
*/
void timer_channel_dma_request_source_select(uint32_t timer_periph, uint8_t dma_request)
{
    if(TIMER_DMAREQUEST_UPDATEEVENT == dma_request){
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_DMAS;
    }else if(TIMER_DMAREQUEST_CHANNELEVENT == dma_request){
        TIMER_CTL1(timer_periph) &= ~(uint32_t)TIMER_CTL1_DMAS;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure the TIMER DMA transfer (API_ID(0x001AU))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  dma_baseaddr:
                only one parameter can be selected which is shown as below:
       \arg        TIMER_DMACFG_DMATA_CTL0: DMA transfer address is TIMER_CTL0, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_CTL1: DMA transfer address is TIMER_CTL1, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_SMCFG: DMA transfer address is TIMER_SMCFG, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_DMAINTEN: DMA transfer address is TIMER_DMAINTEN, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_INTF: DMA transfer address is TIMER_INTF, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_SWEVG: DMA transfer address is TIMER_SWEVG, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_CHCTL0: DMA transfer address is TIMER_CHCTL0, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_CHCTL1: DMA transfer address is TIMER_CHCTL1, TIMERx(x=0,7,1,2,3,4)
       \arg        TIMER_DMACFG_DMATA_CHCTL2: DMA transfer address is TIMER_CHCTL2, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_CNT: DMA transfer address is TIMER_CNT, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_PSC: DMA transfer address is TIMER_PSC, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_CAR: DMA transfer address is TIMER_CAR, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_CREP0: DMA transfer address is TIMER_CREP0, TIMERx(x=0,7,15,16)
       \arg        TIMER_DMACFG_DMATA_CH0CV: DMA transfer address is TIMER_CH0CV, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_CH1CV: DMA transfer address is TIMER_CH1CV, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_CH2CV: DMA transfer address is TIMER_CH2CV, TIMERx(x=0,7,1,2,3,4)
       \arg        TIMER_DMACFG_DMATA_CH3CV: DMA transfer address is TIMER_CH3CV, TIMERx(x=0,7,1,2,3,4)
       \arg        TIMER_DMACFG_DMATA_CCHP0: DMA transfer address is TIMER_CCHP0, TIMERx(x=0,7,15,16)
       \arg        TIMER_DMACFG_DMATA_MCHCTL0: DMA transfer address is TIMER_MCHCTL0, TIMERx(x=15,16)
       \arg        TIMER_DMACFG_DMATA_MCHCTL2: DMA transfer address is TIMER_MCHCTL2, TIMERx(x=15,16)
       \arg        TIMER_DMACFG_DMATA_MCH0CV: DMA transfer address is TIMER_MCH0CV, TIMERx(x=15,16)
       \arg        TIMER_DMACFG_DMATA_CH0COMV_ADD: DMA transfer address is TIMER_CH0COMV_ADD, TIMERx(x=0,7,15,16)
       \arg        TIMER_DMACFG_DMATA_CH1COMV_ADD: DMA transfer address is TIMER_CH1COMV_ADD, TIMERx(x=0,7,15,16)
       \arg        TIMER_DMACFG_DMATA_CH2COMV_ADD: DMA transfer address is TIMER_CH2COMV_ADD, TIMERx(x=0,7)
       \arg        TIMER_DMACFG_DMATA_CH3COMV_ADD: DMA transfer address is TIMER_CH3COMV_ADD, TIMERx(x=0,7)
       \arg        TIMER_DMACFG_DMATA_CTL2: DMA transfer address is TIMER_CTL2, TIMERx(x=0,7,1,2,3,4,15,16)
       \arg        TIMER_DMACFG_DMATA_AFCTL0: DMA transfer address is TIMER_AFCTL0, TIMERx(x=0,7,15,16)
       \arg        TIMER_DMACFG_DMATA_CCHP1: DMA transfer address is TIMER_CCHP1, TIMERx(x=0,7)
       \arg        TIMER_DMACFG_DMATA_WDGPER: DMA transfer address is TIMER_WDGPER, TIMERx(x=1,2,3,4)
       \arg        TIMER_DMACFG_DMATA_CINITCTL: DMA transfer address is TIMER_CINITCTL, TIMERx(x=0,7,15,16)
       \arg        TIMER_DMACFG_DMATA_CINITV: DMA transfer address is TIMER_CINITV, TIMERx(x=0,7,15,16)
       \arg        TIMER_DMACFG_DMATA_CHBRKCTL: DMA transfer address is TIMER_CHBRKCTL, TIMERx(x=0,7)
       \arg        TIMER_DMACFG_DMATA_CHBRKPER: DMA transfer address is TIMER_CHBRKPER, TIMERx(x=0,7)
       \arg        TIMER_DMACFG_DMATA_CHBRKINTF: DMA transfer address is TIMER_CHBRKINTF, TIMERx(x=0,7)
    \param[in]  dma_lenth:
                only one parameter can be selected which is shown as below:
       \arg        TIMER_DMACFG_DMATC_xTRANSFER(x=1..38): DMA transfer x time
    \param[out] none
    \retval     none
*/
void timer_dma_transfer_config(uint32_t timer_periph, uint32_t dma_baseaddr, uint32_t dma_lenth)
{
    TIMER_DMACFG(timer_periph) &= (~(uint32_t)(TIMER_DMACFG_DMATA | TIMER_DMACFG_DMATC));
    TIMER_DMACFG(timer_periph) |= (uint32_t)((dma_baseaddr & TIMER_DMACFG_DMATA) | (dma_lenth & TIMER_DMACFG_DMATC));
}

/*!
    \brief      software generate events (API_ID(0x001BU))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  event: the timer software event generation sources
                one or more parameters can be selected which are shown as below:
      \arg        TIMER_EVENT_SRC_UPG: update event generation, TIMERx(x=0,7,1,2,3,4,5,6,15,16)
      \arg        TIMER_EVENT_SRC_CH0G: channel 0 capture or compare event generation, TIMERx(x=0,7,1,2,3,4,15,16)
      \arg        TIMER_EVENT_SRC_CH1G: channel 1 capture or compare event generation, TIMERx(x=0,7,1,2,3,4,15,16)
      \arg        TIMER_EVENT_SRC_CH2G: channel 2 capture or compare event generation, TIMERx(x=0,7,1,2,3,4)
      \arg        TIMER_EVENT_SRC_CH3G: channel 3 capture or compare event generation, TIMERx(x=0,7,1,2,3,4)
      \arg        TIMER_EVENT_SRC_CMTG: channel commutation event generation, TIMERx(x=0,7,15,16)
      \arg        TIMER_EVENT_SRC_TRGG: trigger event generation, TIMERx(x=0,7,1,2,3,4,15,16)
      \arg        TIMER_EVENT_SRC_BRKG: BREAK event generation, TIMERx(x=0,7,15,16)
      \arg        TIMER_EVENT_SRC_MCH0G: multi mode channel 0 capture or compare event generation, TIMERx(x=15,16)
      \arg        TIMER_EVENT_SRC_CH0COMADDG: channel 0 additional compare event generation, TIMERx(x=0,7,15,16)
      \arg        TIMER_EVENT_SRC_CH1COMADDG: channel 1 additional compare event generation, TIMERx(x=0,7,15,16)
      \arg        TIMER_EVENT_SRC_CH2COMADDG: channel 2 additional compare event generation, TIMERx(x=0,7)
      \arg        TIMER_EVENT_SRC_CH3COMADDG: channel 3 additional compare event generation, TIMERx(x=0,7)
    \param[out] none
    \retval     none
*/
void timer_event_software_generate(uint32_t timer_periph, uint32_t event)
{
    TIMER_SWEVG(timer_periph) |= (uint32_t)event;
}

/*!
    \brief      initialize TIMER break parameter struct with a default value (API_ID(0x001CU))
    \param[in]  breakpara: TIMER break parameter struct
    \param[out] none
    \retval     none
*/
void timer_break_struct_para_init(timer_break_parameter_struct* breakpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(breakpara)) {
        fw_debug_report_err(TIMER_MODULE_ID, API_ID(0x001CU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the break parameter struct member with the default value */
        breakpara->runoffstate           = TIMER_ROS_STATE_DISABLE;
        breakpara->ideloffstate          = TIMER_IOS_STATE_DISABLE;
        breakpara->deadtime              = 0U;
        breakpara->outputautostate       = TIMER_OUTAUTO_DISABLE;
        breakpara->protectmode           = TIMER_CCHP0_PROT_OFF;
        breakpara->breakstate            = TIMER_BREAK_DISABLE;
        breakpara->breakfilter           = 0U;
        breakpara->breakpolarity         = TIMER_BREAK_POLARITY_LOW;
        breakpara->channelbreakstate     = TIMER_CH_BREAK_DISABLE;
        breakpara->channelbreakpolarity  = TIMER_CH_BREAK_POLARITY_LOW;
    }
}

/*!
    \brief      configure TIMER break function (API_ID(0x001DU))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[in]  breakpara: TIMER break parameter struct
                  runoffstate: TIMER_ROS_STATE_ENABLE, TIMER_ROS_STATE_DISABLE
                  ideloffstate: TIMER_IOS_STATE_ENABLE, TIMER_IOS_STATE_DISABLE
                  deadtime: 0~255
                  outputautostate: TIMER_OUTAUTO_ENABLE, TIMER_OUTAUTO_DISABLE
                  protectmode: TIMER_CCHP0_PROT_OFF, TIMER_CCHP0_PROT_0, TIMER_CCHP0_PROT_1, TIMER_CCHP0_PROT_2
                  breakstate: TIMER_BREAK_ENABLE, TIMER_BREAK_DISABLE
                  breakfilter: 0~15
                  breakpolarity: TIMER_BREAK_POLARITY_LOW, TIMER_BREAK_POLARITY_HIGH
                  channelbreakstate: TIMER_CH_BREAK_DISABLE, TIMER_CH_BREAK_ENABLE
                  channelbreakpolarity: TIMER_CH_BREAK_POLARITY_LOW, TIMER_CH_BREAK_POLARITY_HIGH
    \param[out] none
    \retval     none
*/
void timer_break_config(uint32_t timer_periph, timer_break_parameter_struct* breakpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(breakpara)) {
        fw_debug_report_err(TIMER_MODULE_ID, API_ID(0x001DU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph) || (TIMER15 == timer_periph) || (TIMER16 == timer_periph)) {
            TIMER_CCHP0(timer_periph) = (uint32_t)(((uint32_t)(breakpara->runoffstate & TIMER_CCHP0_ROS)) |
                                                ((uint32_t)(breakpara->ideloffstate & TIMER_CCHP0_IOS)) |
                                                ((uint32_t)(breakpara->deadtime & TIMER_CCHP0_DTCFG)) |
                                                ((uint32_t)(breakpara->outputautostate & TIMER_CCHP0_OAEN)) |
                                                ((uint32_t)(breakpara->protectmode & TIMER_CCHP0_PROT)) |
                                                ((uint32_t)(breakpara->breakstate & TIMER_CCHP0_BRKEN)) |
                                                (((uint32_t)(breakpara->breakfilter) << 16U) & TIMER_CCHP0_BRKF) |
                                                ((uint32_t)(breakpara->breakpolarity & TIMER_CCHP0_BRKP)) |
                                                ((uint32_t)(breakpara->channelbreakstate & TIMER_CCHP0_CHBRKEN)) |
                                                ((uint32_t)(breakpara->channelbreakpolarity & TIMER_CCHP0_CHBRKP)));
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      enable TIMER break function (API_ID(0x001EU))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[out] none
    \retval     none
*/
void timer_break_enable(uint32_t timer_periph)
{
    TIMER_CCHP0(timer_periph) |= (uint32_t)TIMER_CCHP0_BRKEN;
}

/*!
    \brief      disable TIMER break function (API_ID(0x001FU))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[out] none
    \retval     none
*/
void timer_break_disable(uint32_t timer_periph)
{
    TIMER_CCHP0(timer_periph) &= (~(uint32_t)TIMER_CCHP0_BRKEN);
}

/*!
    \brief      enable TIMER output automatic function (API_ID(0x0020U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[out] none
    \retval     none
*/
void timer_automatic_output_enable(uint32_t timer_periph)
{
    TIMER_CCHP0(timer_periph) |= (uint32_t)TIMER_CCHP0_OAEN;
}

/*!
    \brief      disable TIMER output automatic function (API_ID(0x0021U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[out] none
    \retval     none
*/
void timer_automatic_output_disable(uint32_t timer_periph)
{
    TIMER_CCHP0(timer_periph) &= (~(uint32_t)TIMER_CCHP0_OAEN);
}

/*!
    \brief      configure TIMER primary output function (API_ID(0x0022U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_primary_output_config(uint32_t timer_periph, ControlStatus newvalue)
{
    if(ENABLE == newvalue){
        TIMER_CCHP0(timer_periph) |= (uint32_t)TIMER_CCHP0_POEN;
    }else{
        TIMER_CCHP0(timer_periph) &= (~(uint32_t)TIMER_CCHP0_POEN);
    }
}

/*!
    \brief      enable or disable channel capture/compare control shadow register (API_ID(0x0023U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
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
    \brief      configure TIMER channel control shadow register update control (API_ID(0x0024U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
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
    TIMER_CTL1(timer_periph) |= (uint32_t)(ccuctl & TIMER_CTL1_CCUC);
}


/*!
    \brief      initialize TIMER channel output parameter struct with a default value (API_ID(0x0025U))
    \param[in]  ocpara: TIMER channel n output parameter struct
    \param[out] none
    \retval     none
*/
void timer_channel_output_struct_para_init(timer_oc_parameter_struct* ocpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(ocpara)) {
        fw_debug_report_err(TIMER_MODULE_ID, API_ID(0x0025U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the channel output parameter struct member with the default value */
        ocpara->outputstate  = TIMER_CCX_DISABLE;
        ocpara->outputnstate = TIMER_CCXN_DISABLE;
        ocpara->ocpolarity   = TIMER_OC_POLARITY_HIGH;
        ocpara->ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
        ocpara->ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
        ocpara->ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    }
}

/*!
    \brief      configure TIMER channel output function (API_ID(0x0026U))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7,1,2,3,4))
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
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(ocpara)) {
        fw_debug_report_err(TIMER_MODULE_ID, API_ID(0x0026U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph) || (TIMER1 == timer_periph) || (TIMER2 == timer_periph) || \
           (TIMER3 == timer_periph) || (TIMER4 == timer_periph) || (TIMER15 == timer_periph) || (TIMER16 == timer_periph)){
            /* reset the CH0EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
            /* set the CH0EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(ocpara->outputstate & TIMER_CHCTL2_CH0EN);
            /* reset the CH0P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0P);
            /* set the CH0P bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(ocpara->ocpolarity & TIMER_CHCTL2_CH0P);
        }

        if((TIMER0  == timer_periph) || (TIMER7  == timer_periph) || (TIMER15  == timer_periph) || (TIMER16  == timer_periph)) {
            /* reset the MCH0EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NEN);
            /* set the MCH0EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(ocpara->outputnstate & TIMER_CHCTL2_CH0NEN);

            /* reset the MCH0P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NP);
            /* set the MCH0P bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(ocpara->ocnpolarity & TIMER_CHCTL2_CH0NP);

            /* reset the ISO0 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO0);
            /* set the ISO0 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)(ocpara->ocidlestate & TIMER_CTL1_ISO0);

            /* reset the ISO0N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO0N);
            /* set the ISO0N bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)(ocpara->ocnidlestate & TIMER_CTL1_ISO0N);
        }

        if((TIMER1 == timer_periph) || (TIMER2 == timer_periph) || (TIMER3 == timer_periph) || (TIMER4 == timer_periph)){
            /* reset the CH0NP bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NP);
            /* set the CH0NP bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(ocpara->ocnpolarity & TIMER_CHCTL2_CH0NP);
        }

        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph) || (TIMER1 == timer_periph) || (TIMER2 == timer_periph) || \
           (TIMER3 == timer_periph) || (TIMER4 == timer_periph) || (TIMER15 == timer_periph) || (TIMER16 == timer_periph)){
            /* reset the CH1EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
            /* set the CH1EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->outputstate) << 4U) & TIMER_CHCTL2_CH1EN);
            /* reset the CH1P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1P);
            /* set the CH1P bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocpolarity) << 4U) & TIMER_CHCTL2_CH1P);
        }
        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph)) {
            /* reset the MCH1EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NEN);
            /* set the MCH1EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->outputnstate) << 4U) & TIMER_CHCTL2_CH1NEN);
            /* reset the MCH1P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NP);
            /* set the MCH1P bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocnpolarity) << 4U) & TIMER_CHCTL2_CH1NP);
            /* reset the ISO1 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO1);
            /* set the ISO1 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocidlestate) << 2U) & TIMER_CTL1_ISO1);
            /* reset the ISO1N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO1N);
            /* set the ISO1N bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocnidlestate) << 2U) & TIMER_CTL1_ISO1N);
        }

        if((TIMER1 == timer_periph) || (TIMER2 == timer_periph) || (TIMER3 == timer_periph) || (TIMER4 == timer_periph)){
            /* reset the CH1NP bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NP);
            /* set the CH1NP bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocnpolarity) << 4U) & TIMER_CHCTL2_CH1NP);
        }

        if((TIMER15 == timer_periph) || (TIMER16 == timer_periph)) {
            /* reset the MCH1P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH1P);
            /* set the MCH1P bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocnpolarity) << 4U) & TIMER_CHCTL2_MCH1P);
            /* reset the ISO1 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO1);
            /* set the ISO1 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocidlestate) << 2U) & TIMER_CTL1_ISO1);
        }

        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph) || (TIMER1 == timer_periph) || (TIMER2 == timer_periph) || \
           (TIMER3 == timer_periph) || (TIMER4 == timer_periph)){
            /* reset the CH2EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);
            /* set the CH2EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->outputstate) << 8U) & TIMER_CHCTL2_CH2EN);
            /* reset the CH2P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2P);
            /* set the CH2P bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocpolarity) << 8U) & TIMER_CHCTL2_CH2P);
        }
        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph)) {
            /* reset the MCH2EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NEN);
            /* set the MCH2EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->outputnstate) << 8U) & TIMER_CHCTL2_CH2NEN);
            /* reset the MCH2P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NP);
            /* set the MCH2P bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocnpolarity) << 8U) & TIMER_CHCTL2_CH2NP);
            /* reset the ISO2 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO2);
            /* set the ISO2 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocidlestate) << 4U) & TIMER_CTL1_ISO2);
            /* reset the ISO2N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO2N);
            /* set the ISO2N bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocnidlestate) << 4U) & TIMER_CTL1_ISO2N);
        }

        if((TIMER1 == timer_periph) || (TIMER2 == timer_periph) || (TIMER3 == timer_periph) || (TIMER4 == timer_periph)){
            /* reset the CH2NP bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NP);
            /* set the CH2NP bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocnpolarity) << 8U) & TIMER_CHCTL2_CH2NP);
        }
    
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2MS);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph) || (TIMER1 == timer_periph) || (TIMER2 == timer_periph) || \
           (TIMER3 == timer_periph) || (TIMER4 == timer_periph)){
            /* reset the CH3EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);
            /* set the CH3EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->outputstate) << 12U) & TIMER_CHCTL2_CH3EN);
            /* reset the CH3P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3P);
            /* set the CH3P bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocpolarity) << 12U) & TIMER_CHCTL2_CH3P);
        }
        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph)) {
            /* reset the MCH3EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3NEN);
            /* set the MCH3EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->outputnstate) << 12U) & TIMER_CHCTL2_CH3NEN);
            /* reset the MCH3P bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3NP);
            /* set the MCH3P bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocnpolarity) << 12U) & TIMER_CHCTL2_CH3NP);
            /* reset the ISO3 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO3);
            /* set the ISO3 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocidlestate) << 6U) & TIMER_CTL1_ISO3);
            /* reset the ISO3N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO3N);
            /* set the ISO3N bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocnidlestate) << 6U) & TIMER_CTL1_ISO3N);
        }

        if((TIMER1 == timer_periph) || (TIMER2 == timer_periph) || (TIMER3 == timer_periph) || (TIMER4 == timer_periph)){
            /* reset the CH3NP bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3NP);
            /* set the CH3NP bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(ocpara->ocnpolarity) << 12U) & TIMER_CHCTL2_CH3NP);
        }

        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3MS);
        break;
     default:
        break;
    }
    }
}

/*!
    \brief      configure TIMER channel output compare mode (API_ID(0x0027U))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=15,16))
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
      \arg        TIMER_OC_MODE_ASYMMETRIC_PWM0: asymmetric PWM mode 0 (TIMERx(x=0,7))
      \arg        TIMER_OC_MODE_ASYMMETRIC_PWM1: asymmetric PWM mode 1 (TIMERx(x=0,7))
    \param[out] none
    \retval     none
*/
void timer_channel_output_mode_config(uint32_t timer_periph, uint16_t channel, uint32_t ocmode)
{
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMCTL);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(ocmode & TIMER_CHCTL0_CH0COMCTL);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMCTL);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)(ocmode) << 8U) & TIMER_CHCTL0_CH1COMCTL);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMCTL);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)(ocmode & TIMER_CHCTL1_CH2COMCTL);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMCTL);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)(((uint32_t)(ocmode) << 8U) & TIMER_CHCTL1_CH3COMCTL);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0COMCTL);
        TIMER_MCHCTL0(timer_periph) |= (uint32_t)(ocmode & TIMER_MCHCTL0_MCH0COMCTL);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output pulse value (API_ID(0x0028U))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=15,16))
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
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCH0CV(timer_periph) = (uint32_t)pulse;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output shadow function (API_ID(0x0029U))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=15,16))
    \param[in]  ocshadow: channel output shadow state
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_SHADOW_ENABLE: channel output shadow state enable
      \arg        TIMER_OC_SHADOW_DISABLE: channel output shadow state disable
      \arg        TIMER_OMC_SHADOW_ENABLE: multi mode channel output compare shadow enable
      \arg        TIMER_OMC_SHADOW_DISABLE: multi mode channel output compare shadow disable
    \param[out] none
    \retval     none
*/
void timer_channel_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow)
{
    switch(channel){
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMSEN);
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)ocshadow & TIMER_CHCTL0_CH0COMSEN);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMSEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)(ocshadow) << 8U) & TIMER_CHCTL0_CH1COMSEN);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMSEN);
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)ocshadow & TIMER_CHCTL1_CH2COMSEN);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMSEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)(((uint32_t)(ocshadow) << 8U) & TIMER_CHCTL1_CH3COMSEN);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0COMSEN);
        TIMER_MCHCTL0(timer_periph) |= ((uint32_t)ocshadow & TIMER_MCHCTL0_MCH0COMSEN);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output fast function (API_ID(0x002AU))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=0..4,7))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=15,16))
    \param[in]  ocfast: channel output fast function
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
    switch(channel){
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMFEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(ocfast & TIMER_CHCTL0_CH0COMFEN);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMFEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)ocfast << 8U) & TIMER_CHCTL0_CH1COMFEN);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMFEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)(ocfast & TIMER_CHCTL1_CH2COMFEN);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMFEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)(((uint32_t)ocfast << 8U) & TIMER_CHCTL1_CH3COMFEN);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0COMFEN);
        TIMER_MCHCTL0(timer_periph) |= (uint32_t)(ocfast & TIMER_MCHCTL0_MCH0COMFEN);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output clear function (API_ID(0x002BU))
    \param[in]  timer_periph: TIMERx(x=0,7,1,2,3,4)
    \param[in]  channel: 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7,1,2,3,4))
    \param[in]  occlear: channel output clear function
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OC_CLEAR_ENABLE: channel output clear function enable
      \arg        TIMER_OC_CLEAR_DISABLE: channel output clear function disable
    \param[out] none
    \retval     none
*/
void timer_channel_output_clear_config(uint32_t timer_periph, uint16_t channel, uint16_t occlear)
{
    switch(channel){
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMCEN);
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)occlear & TIMER_CHCTL0_CH0COMCEN);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMCEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)occlear << 8U) & TIMER_CHCTL0_CH1COMCEN);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMCEN);
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)occlear & TIMER_CHCTL1_CH2COMCEN);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMCEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)(((uint32_t)occlear << 8U) & TIMER_CHCTL1_CH3COMCEN);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel output polarity (API_ID(0x002CU))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=15,16))
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
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocpolarity & TIMER_CHCTL2_CH0P);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1P);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)ocpolarity << 4U) & TIMER_CHCTL2_CH1P);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2P);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)ocpolarity << 8U) & TIMER_CHCTL2_CH2P);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3P);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)ocpolarity << 12U) & TIMER_CHCTL2_CH3P);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)TIMER_MCHCTL2_MCH0FP);
        TIMER_MCHCTL2(timer_periph) |= ((uint32_t)ocpolarity & TIMER_MCHCTL2_MCH0FP);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel complementary output polarity (API_ID(0x002DU))
    \param[in]  timer_periph: TIMERx(x=0,7,1,2,3,4,15,16)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7,1,2,3,4))
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
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NP);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocnpolarity & TIMER_CHCTL2_CH0NP);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NP);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)ocnpolarity << 4U) & TIMER_CHCTL2_CH1NP);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NP);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)ocnpolarity << 8U) & TIMER_CHCTL2_CH2NP);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3NP);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)ocnpolarity << 12U) & TIMER_CHCTL2_CH3NP);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel enable state (API_ID(0x002EU))
    \param[in]  timer_periph: TIMERx(x=0,7,1,2,3,4,15,16)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=15,16))
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
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(state & TIMER_CHCTL2_CH0EN);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)state << 4U) & TIMER_CHCTL2_CH1EN);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)state << 8U) & TIMER_CHCTL2_CH2EN);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)state << 12U) & TIMER_CHCTL2_CH3EN);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH0EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)state) & TIMER_CHCTL2_MCH0EN);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel complementary output enable state (API_ID(0x002FU))
    \param[in]  timer_periph: TIMERx(x=0,7,1,2,3,4,15,16)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7,1,2,3,4))
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
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NEN);
        TIMER_CHCTL2(timer_periph) |= ((uint32_t)ocnstate & TIMER_CHCTL2_CH0NEN);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NEN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)ocnstate << 4U) & TIMER_CHCTL2_CH1NEN);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NEN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)ocnstate << 8U) & TIMER_CHCTL2_CH2NEN);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3NEN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)ocnstate << 12U) & TIMER_CHCTL2_CH3NEN);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel period point match moment OxCPRE level in the composite PWM or asymmetric PWM mode (API_ID(0x0030U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7))
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_channel_composite_asymmetric_pwm_level_config(uint32_t timer_periph, uint16_t channel, ControlStatus newvalue)
{
    switch(channel) {
    case TIMER_CH_0:
        if(ENABLE == newvalue) {
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0PERFOREN);
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0PERFOREN;
        } else {
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0PERFOREN);
        }
        break;
    case TIMER_CH_1:
        if(ENABLE == newvalue) {
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1PERFOREN);
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1PERFOREN;
        } else {
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1PERFOREN);
        }
        break;
    case TIMER_CH_2:
        if(ENABLE == newvalue) {
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2PERFOREN);
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH2PERFOREN;
        } else {
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2PERFOREN);
        }
        break;
    case TIMER_CH_3:
        if(ENABLE == newvalue) {
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3PERFOREN);
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH3PERFOREN;
        } else {
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3PERFOREN);
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      output clear invalid event selection (API_ID(0x0031U))
    \param[in]  timer_periph: TIMERx(x=0,7)
    \param[in]  event:
                only one parameter can be selected which is shown as below:
       \arg       TIMER_OCREFCLR_INVALID_FLOW: output clear invalid by next overflow or underflow event
       \arg       TIMER_OCREFCLR_INVALID_UPDATE: ouput clear invalid by next update event
    \param[out] none
    \retval     none
*/
void timer_channel_output_clear_invalid_selection(uint32_t timer_periph, uint32_t event)
{
    if(TIMER_OCREFCLR_INVALID_UPDATE == event)
    {
        TIMER_CFG(timer_periph) |= TIMER_CFG_OCPRECIVM;
    } else {
        TIMER_CFG(timer_periph) &= (~(uint32_t)TIMER_CFG_OCPRECIVM);
    }
}

/*!
    \brief      initialize TIMER channel input parameter struct with a default value (API_ID(0x0032U))
    \param[in]  icpara: TIMER channel intput parameter struct
    \param[out] none
    \retval     none
*/
void timer_channel_input_struct_para_init(timer_ic_parameter_struct* icpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(icpara)) {
        fw_debug_report_err(TIMER_MODULE_ID, API_ID(0x0032U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the channel input parameter struct member with the default value */
        icpara->icpolarity  = TIMER_IC_POLARITY_RISING;
        icpara->icselection = TIMER_IC_SELECTION_DIRECTTI;
        icpara->icprescaler = TIMER_IC_PSC_DIV1;
        icpara->icfilter    = 0U;
        }
}

/*!
    \brief      configure TIMER input capture parameter (API_ID(0x0033U))
    \param[in]  timer_periph: TIMERx(x=0~4,7,15,16)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=15,16))
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
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(icpara)) {
        fw_debug_report_err(TIMER_MODULE_ID, API_ID(0x0033U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(channel) {
        /* configure TIMER_CH_0 */
        case TIMER_CH_0:
            /* reset the CH0EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
    
            /* reset the CH0P and MCH0P bits */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
            TIMER_CHCTL2(timer_periph) |= ((uint32_t)(icpara->icpolarity) & (TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
    
            /* reset the CH0MS bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
            if(TIMER_IC_SELECTION_PAIR == icpara->icselection) {
                TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)(icpara->icselection) << 28U) & TIMER_CHCTL0_CH0MS);
            } else {
                TIMER_CHCTL0(timer_periph) |= ((uint32_t)(icpara->icselection) & TIMER_CHCTL0_CH0MS);
            }
    
            /* reset the CH0CAPFLT bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
            TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)(icpara->icfilter) << 4U) & TIMER_CHCTL0_CH0CAPFLT);
    
            /* set the CH0EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
            break;
    
        /* configure TIMER_CH_1 */
        case TIMER_CH_1:
            /* reset the CH1EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
    
            /* reset the CH1P and MCH1P bits */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(icpara->icpolarity) << 4U) & (TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
    
            /* reset the CH1MS bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
            TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)(icpara->icselection) << 8U) & TIMER_CHCTL0_CH1MS);
    
            /* reset the CH1CAPFLT bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
            TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)(icpara->icfilter) << 12U) & TIMER_CHCTL0_CH1CAPFLT);
    
            /* set the CH1EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
            break;
    
        /* configure TIMER_CH_2 */
        case TIMER_CH_2:
            /* reset the CH2EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);
    
            /* reset the CH2P and MCH2P bits */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH2P | TIMER_CHCTL2_CH2NP));
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(icpara->icpolarity) << 8U) & (TIMER_CHCTL2_CH2P | TIMER_CHCTL2_CH2NP));
    
            /* reset the CH2MS bit */
            TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2MS);
            TIMER_CHCTL1(timer_periph) |= ((uint32_t)(icpara->icselection) & TIMER_CHCTL1_CH2MS);
    
            /* reset the CH2CAPFLT bit */
            TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2CAPFLT);
            TIMER_CHCTL1(timer_periph) |= (uint32_t)(((uint32_t)(icpara->icfilter) << 4U) & TIMER_CHCTL1_CH2CAPFLT);
    
            /* set the CH2EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH2EN;
            break;
    
        /* configure TIMER_CH_3 */
        case TIMER_CH_3:
            /* reset the CH3EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);
    
            /* reset the CH3P bits */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH3P | TIMER_CHCTL2_CH3NP));
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(icpara->icpolarity) << 12U) & (TIMER_CHCTL2_CH3P | TIMER_CHCTL2_CH3NP));
    
            /* reset the CH3MS bit */
            TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3MS);
            TIMER_CHCTL1(timer_periph) |= (uint32_t)(((uint32_t)(icpara->icselection) << 8U) & TIMER_CHCTL1_CH3MS);
    
            /* reset the CH3CAPFLT bit */
            TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3CAPFLT);
            TIMER_CHCTL1(timer_periph) |= (uint32_t)(((uint32_t)(icpara->icfilter) << 12U) & TIMER_CHCTL1_CH3CAPFLT);
    
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
                TIMER_MCHCTL0(timer_periph) |= (((uint32_t)icpara->icselection << 28U) & TIMER_MCHCTL0_MCH0MS);
            } else {
                TIMER_MCHCTL0(timer_periph) |= ((uint32_t)(icpara->icselection) & TIMER_MCHCTL0_MCH0MS);
            }
    
            /* reset the MCH0CAPFLT bit */
            TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0CAPFLT);
            TIMER_MCHCTL0(timer_periph) |= (uint32_t)(((uint32_t)(icpara->icfilter) << 4U) & TIMER_MCHCTL0_MCH0CAPFLT);
    
            /* set the MCH0EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_MCH0EN;
            break;
        default:
            break;
        }
    
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, channel, (uint16_t)(icpara->icprescaler));
    }
}

/*!
    \brief      configure TIMER channel input capture prescaler value (API_ID(0x0034U))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=15,16))
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
    switch(channel){
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPPSC);
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)prescaler & TIMER_CHCTL0_CH0CAPPSC);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPPSC);
        TIMER_CHCTL0(timer_periph) |= (((uint32_t)prescaler << 8U) & TIMER_CHCTL0_CH1CAPPSC);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2CAPPSC);
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)prescaler & TIMER_CHCTL1_CH2CAPPSC);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3CAPPSC);
        TIMER_CHCTL1(timer_periph) |= (((uint32_t)prescaler << 8U) & TIMER_CHCTL1_CH3CAPPSC);
        break;
    /* configure TIMER_MCH_0 */
    case TIMER_MCH_0:
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0CAPPSC);
        TIMER_MCHCTL0(timer_periph) |= ((uint32_t)prescaler & TIMER_MCHCTL0_MCH0CAPPSC);
        break;
    default:
        break;
    }
}

/*!
    \brief      read TIMER channel capture compare register value (API_ID(0x0035U))
    \param[in]  timer_periph: please refer to the following parameters
    \param[in]  channel: 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel0(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_1: TIMER channel1(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_CH_2: TIMER channel2(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_CH_3: TIMER channel3(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=15,16))
    \param[out] none
    \retval     channel capture compare register value
*/
uint32_t timer_channel_capture_value_register_read(uint32_t timer_periph, uint16_t channel)
{
    uint32_t count_value = 0U;

    switch(channel){
    /* read TIMER channel 0 capture compare register value */
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
    default:
        break;
    }
    return (count_value);
}

/*!
    \brief      configure TIMER input pwm capture function (API_ID(0x0036U))
    \param[in]  timer_periph: TIMERx(x=0..4,7)
    \param[in]  channel: 
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
void timer_input_pwm_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct* icpwm)
{
    uint16_t icpolarity  = 0x0U;
    uint16_t icselection = 0x0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(icpwm)) {
        fw_debug_report_err(TIMER_MODULE_ID, API_ID(0x0036U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* Set channel input polarity */
        if(TIMER_IC_POLARITY_RISING == icpwm->icpolarity){
            icpolarity = TIMER_IC_POLARITY_FALLING;
        }else{
            icpolarity = TIMER_IC_POLARITY_RISING;
        }
    
        /* Set channel input mode selection */
        if(TIMER_IC_SELECTION_DIRECTTI == icpwm->icselection){
            icselection = TIMER_IC_SELECTION_INDIRECTTI;
        }else{
            icselection = TIMER_IC_SELECTION_DIRECTTI;
        }
    
        if(TIMER_CH_0 == channel){
            /* reset the CH0EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
            /* reset the CH0P and CH0NP bits */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P|TIMER_CHCTL2_CH0NP));
            /* set the CH0P and CH0NP bits */
            TIMER_CHCTL2(timer_periph) |= ((uint32_t)(icpwm->icpolarity) & (TIMER_CHCTL2_CH0P | TIMER_CHCTL2_MCH0P));
            /* reset the CH0MS bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
            /* set the CH0MS bit */
            TIMER_CHCTL0(timer_periph) |= ((uint32_t)(icpwm->icselection) & TIMER_CHCTL0_CH0MS);
            /* reset the CH0CAPFLT bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
            /* set the CH0CAPFLT bit */
            TIMER_CHCTL0(timer_periph) |= (((uint32_t)(icpwm->icfilter) << 4U) & TIMER_CHCTL0_CH0CAPFLT);
            /* set the CH0EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
            /* configure TIMER channel input capture prescaler value */
            timer_channel_input_capture_prescaler_config(timer_periph,TIMER_CH_0,(uint16_t)(icpwm->icprescaler));
    
            /* reset the CH1EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
            /* reset the CH1P and CH1NP bits */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P|TIMER_CHCTL2_CH1NP));
            /* set the CH1P and CH1NP bits */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)icpolarity << 4U) & (TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
            /* reset the CH1MS bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
            /* set the CH1MS bit */
            TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)icselection << 8U) & TIMER_CHCTL0_CH1MS);
            /* reset the CH1CAPFLT bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
            /* set the CH1CAPFLT bit */
            TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)(icpwm->icfilter) << 12U) & TIMER_CHCTL0_CH1CAPFLT);
            /* set the CH1EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
            /* configure TIMER channel input capture prescaler value */
            timer_channel_input_capture_prescaler_config(timer_periph,TIMER_CH_1,(uint16_t)(icpwm->icprescaler));
        }else{
            /* reset the CH1EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
            /* reset the CH1P and CH1NP bits */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P|TIMER_CHCTL2_CH1NP));
            /* set the CH1P and CH1NP bits */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(icpwm->icpolarity) << 4U) & (TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
            /* reset the CH1MS bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
            /* set the CH1MS bit */
            TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)(icpwm->icselection) << 8U) & TIMER_CHCTL0_CH1MS);
            /* reset the CH1CAPFLT bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
            /* set the CH1CAPFLT bit */
            TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)(icpwm->icfilter) << 12U) & TIMER_CHCTL0_CH1CAPFLT);
            /* set the CH1EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
            /* configure TIMER channel input capture prescaler value */
            timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_1, (uint16_t)(icpwm->icprescaler));
    
            /* reset the CH0EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
            /* reset the CH0P and CH0NP bits */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P|TIMER_CHCTL2_CH0NP));
            /* set the CH0P and CH0NP bits */
            TIMER_CHCTL2(timer_periph) |= ((uint32_t)icpolarity & (TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
            /* reset the CH0MS bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
            /* set the CH0MS bit */
            TIMER_CHCTL0(timer_periph) |= ((uint32_t)icselection & TIMER_CHCTL0_CH0MS);
            /* reset the CH0CAPFLT bit */
            TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
            /* set the CH0CAPFLT bit */
            TIMER_CHCTL0(timer_periph) |= (((uint32_t)(icpwm->icfilter) << 4U) & TIMER_CHCTL0_CH0CAPFLT);
            /* set the CH0EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
            /* configure TIMER channel input capture prescaler value */
            timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_0, (uint16_t)(icpwm->icprescaler));
        }
    }
}

/*!
    \brief      configure TIMER hall sensor mode (API_ID(0x0037U))
    \param[in]  timer_periph: TIMERx(x=0,7,1,2,3,4,15,16)
    \param[in]  hallmode: 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_HALLINTERFACE_ENABLE: TIMER hall sensor mode enable
      \arg        TIMER_HALLINTERFACE_DISABLE: TIMER hall sensor mode disable
    \param[out] none
    \retval     none
*/
void timer_hall_mode_config(uint32_t timer_periph, uint32_t hallmode)
{
    if(TIMER_HALLINTERFACE_ENABLE == hallmode){
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_TI0S;
    }else if(TIMER_HALLINTERFACE_DISABLE == hallmode){
        TIMER_CTL1(timer_periph) &= ~(uint32_t)TIMER_CTL1_TI0S;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      initialize TIMER multi mode channel output parameter struct (API_ID(0x0038U))
    \param[in]  omcpara: TIMER multi mode channel output parameter struct
    \param[out] none
    \retval     none
*/
void timer_multi_mode_channel_output_parameter_struct_init(timer_omc_parameter_struct *omcpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(omcpara)) {
        fw_debug_report_err(TIMER_MODULE_ID, API_ID(0x0038U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the multi mode channel output parameter struct with the default value */
        omcpara->outputmode  = TIMER_MCH_MODE_COMPLEMENTARY;
        omcpara->outputstate = TIMER_MCCX_DISABLE;
        omcpara->ocpolarity  = TIMER_OMC_POLARITY_LOW;
    }
}

/*!
    \brief      configure TIMER multi mode channel output function (API_ID(0x0039U))
    \param[in]  timer_periph: TIMERx(x=15,16)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=15,16))
    \param[in]  omcpara: TIMER multi mode channel output parameter struct
                  outputmode: TIMER_MCH_MODE_INDEPENDENTLY, TIMER_MCH_MODE_COMPLEMENTARY
                  outputstate: TIMER_MCCX_ENABLE, TIMER_MCCX_DISABLE
                  ocpolarity: TIMER_OMC_POLARITY_HIGH, TIMER_OMC_POLARITY_LOW
    \param[out] none
    \retval     none
*/
void timer_multi_mode_channel_output_config(uint32_t timer_periph, uint16_t channel, timer_omc_parameter_struct *omcpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(omcpara)) {
        fw_debug_report_err(TIMER_MODULE_ID, API_ID(0x0039U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(channel) {
        /* configure TIMER_MCH_0 */
        case TIMER_MCH_0:
            TIMER_CTL2(timer_periph) &= (~(uint32_t)((uint32_t)TIMER_MCH_MODE_MASK << 20U));
            TIMER_CTL2(timer_periph) |= (uint32_t)(((uint32_t)(omcpara->outputmode) & TIMER_MCH_MODE_MASK) << 20U);
            /* reset the MCH0EN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH0EN);
            /* set the MCH0EN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)(omcpara->outputstate)) & TIMER_CHCTL2_MCH0EN);
            /* reset the MCH0FP bit */
            TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)TIMER_MCHCTL2_MCH0FP);
            /* set the MCH0FP bit */
            TIMER_MCHCTL2(timer_periph) |= ((uint32_t)omcpara->ocpolarity & TIMER_MCHCTL2_MCH0FP);
    
            TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0MS);
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      multi mode channel mode select (API_ID(0x003AU))
    \param[in]  timer_periph: TIMERx(x=15,16)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_MCH_0: TIMER multi mode channel 0(TIMERx(x=15,16))
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
    reg |= (uint32_t)((multi_mode_sel & TIMER_MCH_MODE_MASK) << (((channel & 0xFU) << 1U) + 20U));

    TIMER_CTL2(timer_periph) = reg;
}

/*!
    \brief      select TIMER input trigger source (API_ID(0x003BU))
    \param[in]  timer_periph: TIMERx(x=0..4,7,15,16)
    \param[in]  intrigger:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SMCFG_TRGSEL_NONE: event mode disable(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_ITI0: internal trigger 0(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_ITI1: internal trigger 1(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_ITI2: internal trigger 2(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_ITI3: internal trigger 3(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_CI0F_ED: TI0 edge detector(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_CI0FE0: filtered channel 0 input(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_CI1FE1: filtered channel 1 input(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_ETIFP: filtered external trigger input(TIMERx(x=0..4,7))
      \arg        TIMER_SMCFG_TRGSEL_CI2FE2: filtered channel 2 input(TIMERx(x=0..4,7))
      \arg        TIMER_SMCFG_TRGSEL_CI3FE3: filtered channel 3 input(TIMERx(x=0..4,7))
      \arg        TIMER_SMCFG_TRGSEL_MCI0FEM0: filtered multi mode channel 0 input(TIMERx(x=15,16))
      \arg        TIMER_SMCFG_TRGSEL_ITI14: internal trigger 14(TIMERx(x=15,16))
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

    switch(timer_periph){
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
    case TIMER15:
        timerx_temp = SYSCFG_TIMER15;
        break;
    case TIMER16:
        timerx_temp = SYSCFG_TIMER16;
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
        REG32(timer_base_addr + 8U) = (uint32_t)(intrigger & TIMER_SMCFG_TRGSEL_MASK) << 16U;
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
                    REG32(timer_base_addr + i) = (uint32_t)(intrigger & TIMER_SMCFG_TRGSEL_MASK) << j;
                    break;
                    }
                }

                break;
            }
        }
    }
}


/*!
    \brief      select TIMER master mode output trigger source (API_ID(0x003CU))
    \param[in]  timer_periph: TIMERx(x=0,7,1,2,3,4,5,6,15,16)
    \param[in]  outrigger: 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_TRI_OUT_SRC_RESET: the UPG bit as trigger output (TIMERx(x=0,7,1,2,3,4,5,6,15,16))
      \arg        TIMER_TRI_OUT_SRC_ENABLE: the counter enable signal TIMER_CTL0_CEN as trigger output(TIMERx(x=0,7,1,2,3,4,5,6,15,16))
      \arg        TIMER_TRI_OUT_SRC_UPDATE: update event as trigger output(TIMERx(x=0,7,1,2,3,4,5,6,15,16))
      \arg        TIMER_TRI_OUT_SRC_CH0: a capture or a compare match occurred in channal0 as trigger output TRGO(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_TRI_OUT_SRC_O0CPRE: O0CPRE as trigger output(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_TRI_OUT_SRC_O1CPRE: O1CPRE as trigger output(TIMERx(x=0,7,1,2,3,4,15,16))
      \arg        TIMER_TRI_OUT_SRC_O2CPRE: O2CPRE as trigger output(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_TRI_OUT_SRC_O3CPRE: O3CPRE as trigger output(TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_TRI_OUT_SRC_DECODER_CLOCK: decoder clock as trigger output (TIMERx(x=0,7,1,2,3,4))
      \arg        TIMER_TRI_OUT_SRC_SYNC: synchronization event as trigger output (TIMERx(x=0,7,15,16))
    \param[out] none
    \retval     none
*/
void timer_master_output_trigger_source_select(uint32_t timer_periph, uint32_t outrigger)
{
    uint32_t reg;

    reg  = TIMER_CTL1(timer_periph);
    reg &= (~(uint32_t)TIMER_CTL1_MMC);
    reg |= (uint32_t)(outrigger & TIMER_CTL1_MMC);
    TIMER_CTL1(timer_periph) = reg;
}

/*!
    \brief      select TIMER slave mode (API_ID(0x003DU))
    \param[in]  timer_periph: TIMERx(x=0..4,7,15,16)
    \param[in]  slavemode:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SLAVE_MODE_DISABLE: slave mode disable(TIMERx(x=0~4,7,15,16))
      \arg        TIMER_QUAD_DECODER_MODE0: quadrature decoder mode 0(TIMERx(x=0~4,7))
      \arg        TIMER_QUAD_DECODER_MODE1: quadrature decoder mode 1(TIMERx(x=0~4,7))
      \arg        TIMER_QUAD_DECODER_MODE2: quadrature decoder mode 2(TIMERx(x=0~4,7))
      \arg        TIMER_SLAVE_MODE_RESTART: restart mode(TIMERx(x=0~4,7,15,16))
      \arg        TIMER_SLAVE_MODE_PAUSE: pause mode(TIMERx(x=0~4,7,15,16))
      \arg        TIMER_SLAVE_MODE_EVENT: event mode(TIMERx(x=0~4,7,15,16))
      \arg        TIMER_SLAVE_MODE_EXTERNAL0: external clock mode 0(TIMERx(x=0~4,7,15,16))
      \arg        TIMER_NONQUAD_DECODER_MODE0: non-quadrature decoder mode 0(TIMERx(x=1~4))
      \arg        TIMER_NONQUAD_DECODER_MODE1: non-quadrature decoder mode 1(TIMERx(x=1~4))
      \arg        TIMER_NONQUAD_DECODER_MODE2: non-quadrature decoder mode 2(TIMERx(x=1~4))
      \arg        TIMER_NONQUAD_DECODER_MODE3: non-quadrature decoder mode 3(TIMERx(x=1~4))
      \arg        TIMER_QUAD_DECODER_MODE3: quadrature decoder mode 3(TIMERx(x=1~4))
      \arg        TIMER_QUAD_DECODER_MODE4: quadrature decoder mode 4(TIMERx(x=1~4))
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
    case TIMER15:
        timerx_temp = SYSCFG_TIMER15;
        break;
    case TIMER16:
        timerx_temp = SYSCFG_TIMER16;
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
                if(0U == reg_temp) {
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
    \brief      configure TIMER master slave mode (API_ID(0x003EU))
    \param[in]  timer_periph: TIMERx(x=0,7,1,2,3,4,15,16)
    \param[in]  masterslave:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_MASTER_SLAVE_MODE_ENABLE: master slave mode enable
      \arg        TIMER_MASTER_SLAVE_MODE_DISABLE: master slave mode disable
    \param[out] none
    \retval     none
*/ 
void timer_master_slave_mode_config(uint32_t timer_periph, uint32_t masterslave)
{
    if(TIMER_MASTER_SLAVE_MODE_ENABLE == masterslave){
        TIMER_SMCFG(timer_periph) |= (uint32_t)TIMER_SMCFG_MSM;
    }else if(TIMER_MASTER_SLAVE_MODE_DISABLE == masterslave){
        TIMER_SMCFG(timer_periph) &= ~(uint32_t)TIMER_SMCFG_MSM;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure TIMER external trigger input (API_ID(0x003FU))
    \param[in]  timer_periph: TIMERx(x=0,7,1,2,3,4)
    \param[in]  extprescaler:
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
void timer_external_trigger_config(uint32_t timer_periph, uint32_t extprescaler,
                                   uint32_t extpolarity, uint32_t extfilter)
{
    TIMER_SMCFG(timer_periph) &= (~(uint32_t)(TIMER_SMCFG_ETP | TIMER_SMCFG_ETPSC | TIMER_SMCFG_ETFC));
    TIMER_SMCFG(timer_periph) |= (uint32_t)((extprescaler & TIMER_SMCFG_ETPSC) | (extpolarity | TIMER_SMCFG_ETP));
    TIMER_SMCFG(timer_periph) |= (uint32_t)((extfilter << 8U) & TIMER_SMCFG_ETFC);
}

/*!
    \brief      configure TIMER quadrature decoder mode (API_ID(0x0040U))
    \param[in]  timer_periph: TIMERx(x=0..4,7)
    \param[in]  decomode: 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_QUAD_DECODER_MODE0: counter counts on CI0FE0 edge depending on CI1FE1 level(TIMERx(x=0..4,7))
      \arg        TIMER_QUAD_DECODER_MODE1: counter counts on CI1FE1 edge depending on CI0FE0 level(TIMERx(x=0..4,7))
      \arg        TIMER_QUAD_DECODER_MODE2: counter counts on both CI0FE0 and CI1FE1 edges depending on the level of the other input(TIMERx(x=0..4,7))
      \arg        TIMER_QUAD_DECODER_MODE3: counter counts on CI0FE0 edge depending on CI0FE0 level(TIMERx(x=1..4))
      \arg        TIMER_QUAD_DECODER_MODE4: counter counts on CI1FE1 edge depending on CI1FE1 level(TIMERx(x=1..4))
    \param[in]  ic0polarity: 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_IC_POLARITY_RISING: capture rising edge
      \arg        TIMER_IC_POLARITY_FALLING: capture falling edge
      \arg        TIMER_IC_POLARITY_BOTH_EDGE: active both edge
    \param[in]  ic1polarity:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_IC_POLARITY_RISING: capture rising edge
      \arg        TIMER_IC_POLARITY_FALLING: capture falling edge
      \arg        TIMER_IC_POLARITY_BOTH_EDGE: active both edge
    \param[out] none
    \retval     none
*/
void timer_quadrature_decoder_mode_config(uint32_t timer_periph, uint32_t decomode,
                                   uint16_t ic0polarity, uint16_t ic1polarity)
{
    /* configure the quadrature decoder mode */
    timer_slave_mode_select(timer_periph, decomode);

    /* configure input capture selection */
    TIMER_CHCTL0(timer_periph) &= (uint32_t)(((~(uint32_t)TIMER_CHCTL0_CH0MS)) & ((~(uint32_t)TIMER_CHCTL0_CH1MS)));
    TIMER_CHCTL0(timer_periph) |= (uint32_t)(TIMER_IC_SELECTION_DIRECTTI | ((uint32_t)TIMER_IC_SELECTION_DIRECTTI << 8U));
    /* configure channel input capture polarity */
    if((TIMER0  == timer_periph) || (TIMER7  == timer_periph) || (TIMER1  == timer_periph) || (TIMER2  == timer_periph) || (TIMER3 == timer_periph) || (TIMER4 == timer_periph)) {
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
    } else {
        /* illegal parameters */
    }
    TIMER_CHCTL2(timer_periph) |= (((uint32_t)ic0polarity & (TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP)) | (((uint32_t)ic1polarity << 4U) & (TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP)));
}

/*!
    \brief      configure TIMER non-quadrature decoder mode (API_ID(0x0041U))
    \param[in]  timer_periph: TIMERx(x=1~4)
    \param[in]  decomode: non-quadrature decoder mode
                only one parameter can be selected which is shown as below:
      \arg        TIMER_NONQUAD_DECODER_MODE0: non-quadrature decoder mode 0
      \arg        TIMER_NONQUAD_DECODER_MODE1: non-quadrature decoder mode 1
      \arg        TIMER_NONQUAD_DECODER_MODE2: non-quadrature decoder mode 2
      \arg        TIMER_NONQUAD_DECODER_MODE3: non-quadrature decoder mode 3
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
void timer_non_quadrature_decoder_mode_config(uint32_t timer_periph, uint32_t decomode, uint16_t ic0polarity, uint16_t ic1polarity)
{
    /* configure the non-quadrature decoder mode */
    timer_slave_mode_select(timer_periph, decomode);

    /* configure input capture selection */
    TIMER_CHCTL0(timer_periph) &= (uint32_t)(((~(uint32_t)TIMER_CHCTL0_CH0MS)) & ((~(uint32_t)TIMER_CHCTL0_CH1MS)));
    TIMER_CHCTL0(timer_periph) |= (uint32_t)(TIMER_IC_SELECTION_DIRECTTI | ((uint32_t)TIMER_IC_SELECTION_DIRECTTI << 8U));
    /* configure channel input capture polarity */
    if((TIMER1  == timer_periph) || (TIMER2  == timer_periph) || (TIMER3 == timer_periph) || (TIMER4 == timer_periph)) {
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
    } else {
        /* illegal parameters */
    }
    TIMER_CHCTL2(timer_periph) |= (((uint32_t)ic0polarity & (TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP)) | (((uint32_t)ic1polarity << 4U) & (TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP)));
}


/*!
    \brief      configure TIMER internal clock mode (API_ID(0x0042U))
    \param[in]  timer_periph: TIMERx(x=0~4,7,15,16)
    \param[out] none
    \retval     none
*/
void timer_internal_clock_config(uint32_t timer_periph)
{
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_DISABLE);
}

/*!
    \brief      configure TIMER the internal trigger as external clock input (API_ID(0x0043U))
    \param[in]  timer_periph: TIMERx(x=0..4,7,15,16)
    \param[in]  intrigger:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SMCFG_TRGSEL_ITI0: internal trigger 0(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_ITI1: internal trigger 1(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_ITI2: internal trigger 2(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_ITI3: internal trigger 3(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_ITI14: internal trigger 14(TIMERx(x=15,16))
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
    \brief      configure TIMER the external trigger as external clock input (API_ID(0x0044U))
    \param[in]  timer_periph: TIMERx(x=0..4,7,15,16)
    \param[in]  extrigger:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_SMCFG_TRGSEL_CI0F_ED: TI0 edge detector(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_CI0FE0: filtered channel 0 input(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_CI1FE1: filtered channel 1 input(TIMERx(x=0..4,7,15,16))
      \arg        TIMER_SMCFG_TRGSEL_CI2FE2: filtered channel 2 input(TIMERx(x=0..4,7))
      \arg        TIMER_SMCFG_TRGSEL_CI3FE3: filtered channel 3 input(TIMERx(x=0..4,7))
      \arg        TIMER_SMCFG_TRGSEL_MCI0FEM0: filtered multi mode channel 0 input(TIMERx(x=15,16))
    \param[in]  extpolarity: 
                only one parameter can be selected which is shown as below:
      \arg        TIMER_IC_POLARITY_RISING: active high or rising edge active
      \arg        TIMER_IC_POLARITY_FALLING: active low or falling edge active
      \arg        TIMER_IC_POLARITY_BOTH_EDGE: active both edge
    \param[in]  extfilter: a value between 0 and 15
    \param[out] none
    \retval     none
*/
void timer_external_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t extrigger,
                                       uint16_t extpolarity, uint32_t extfilter)
{
    if(TIMER_SMCFG_TRGSEL_CI1FE1 == extrigger) {
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        /* reset the CH1P and MCH1P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
        /* set the CH1P and MCH1P bits */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(((uint32_t)extpolarity << 4U) & (TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
        /* reset the CH1MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        /* set the CH1MS bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)TIMER_IC_SELECTION_DIRECTTI << 8U);
        /* reset the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        /* set the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(extfilter << 12U) & TIMER_CHCTL0_CH1CAPFLT);
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
    } else if(TIMER_SMCFG_TRGSEL_CI2FE2 == extrigger) {
        /* reset the CH2EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);
        /* reset the CH2P and MCH2P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH2P | TIMER_CHCTL2_CH2NP));
        /* set the CH2P and MCH2P bits */
        TIMER_CHCTL2(timer_periph) |= (((uint32_t)extpolarity << 8U) & (TIMER_CHCTL2_CH2P | TIMER_CHCTL2_CH2NP));
        /* reset the CH2MS bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2MS);
        /* set the CH2MS bit */
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)TIMER_IC_SELECTION_DIRECTTI);
        /* reset the CH2CAPFLT bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2CAPFLT);
        /* set the CH2CAPFLT bit */
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)(extfilter << 4U) & TIMER_CHCTL1_CH2CAPFLT);
        /* set the CH2EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH2EN;
    } else if(TIMER_SMCFG_TRGSEL_CI3FE3 == extrigger) {
        /* reset the CH3EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);
        /* reset the CH3P and MCH3P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH3P | TIMER_CHCTL2_CH3NP));
        /* set the CH3P and MCH3P bits */
        TIMER_CHCTL2(timer_periph) |= (((uint32_t)extpolarity << 12U) & (TIMER_CHCTL2_CH3P | TIMER_CHCTL2_CH3NP));
        /* reset the CH3MS bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3MS);
        /* set the CH3MS bit */
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)TIMER_IC_SELECTION_DIRECTTI << 8U);
        /* reset the CH3CAPFLT bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3CAPFLT);
        /* set the CH3CAPFLT bit */
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)(extfilter << 12U) & TIMER_CHCTL1_CH3CAPFLT);
        /* set the CH3EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH3EN;
    } else if(TIMER_SMCFG_TRGSEL_MCI0FEM0 == extrigger) {
        /* reset the MCH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_MCH0EN);
        /* reset the MCH0FP bit */
        TIMER_MCHCTL2(timer_periph) &= (~(uint32_t)TIMER_MCHCTL2_MCH0FP);
        /* set the MCH0FP bit */
        if(TIMER_IC_POLARITY_RISING == extpolarity) {
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_RISING;
        } else if(TIMER_IC_POLARITY_FALLING == extpolarity) {
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_FALLING;
        } else {
            TIMER_MCHCTL2(timer_periph) |= (uint32_t)TIMER_IMC_POLARITY_BOTH_EDGE;
        }
        /* reset the MCH0MS bit */
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0MS);
        /* set the MCH0MS bit */
        TIMER_MCHCTL0(timer_periph) |= (uint32_t)TIMER_IC_SELECTION_DIRECTTI;
        /* reset the MCH0CAPFLT bit */
        TIMER_MCHCTL0(timer_periph) &= (~(uint32_t)TIMER_MCHCTL0_MCH0CAPFLT);
        /* reset the MCH0CAPFLT bit */
        TIMER_MCHCTL0(timer_periph) |= ((uint32_t)(extfilter << 4U) & TIMER_MCHCTL0_MCH0CAPFLT);
        /* set the MCH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_MCH0EN;
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
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(extfilter << 4U) & TIMER_CHCTL0_CH0CAPFLT);
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
    }
    /* select TIMER slave mode */
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_EXTERNAL0);
    /* select TIMER input trigger source */
    timer_input_trigger_source_select(timer_periph, extrigger);
}

/*!
    \brief      configure TIMER the external clock mode0 (API_ID(0x0045U))
    \param[in]  timer_periph: TIMERx(x=0..4,7)
    \param[in]  extprescaler: 
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
void timer_external_clock_mode0_config(uint32_t timer_periph, uint32_t extprescaler,
                                       uint32_t extpolarity, uint32_t extfilter)
{
    /* configure TIMER external trigger input */
    timer_external_trigger_config(timer_periph, extprescaler, extpolarity, extfilter);
    /* select TIMER slave mode */
    timer_slave_mode_select(timer_periph, TIMER_SLAVE_MODE_EXTERNAL0);
    /* select TIMER input trigger source */
    timer_input_trigger_source_select(timer_periph, TIMER_SMCFG_TRGSEL_ETIFP);
}

/*!
    \brief      configure TIMER the external clock mode1 (API_ID(0x0046U))
    \param[in]  timer_periph: TIMERx(x=0..4,7)
    \param[in]  extprescaler: 
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
void timer_external_clock_mode1_config(uint32_t timer_periph, uint32_t extprescaler,
                                       uint32_t extpolarity, uint32_t extfilter)
{
    /* configure TIMER external trigger input */
    timer_external_trigger_config(timer_periph, extprescaler, extpolarity, extfilter);

    TIMER_SMCFG(timer_periph) |= (uint32_t)TIMER_SMCFG_SMC1;
}

/*!
    \brief      disable TIMER the external clock mode1 (API_ID(0x0047U))
    \param[in]  timer_periph: TIMERx(x=0..4,7)
    \param[out] none
    \retval     none
*/
void timer_external_clock_mode1_disable(uint32_t timer_periph)
{
    TIMER_SMCFG(timer_periph) &= ~(uint32_t)TIMER_SMCFG_SMC1;
}

/*!
    \brief      configure TIMER write CHxVAL register selection (API_ID(0x0048U))
    \param[in]  timer_periph: TIMERx(x=0,7,1,2,3,4,15,16)
    \param[in]  ccsel:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CHVSEL_DISABLE: no effect
      \arg        TIMER_CHVSEL_ENABLE: when write the CHxVAL register, if the write value is same as the CHxVAL value, the write access is ignored
    \param[out] none
    \retval     none
*/
void timer_write_chxval_register_config(uint32_t timer_periph, uint16_t ccsel)
{
    if(TIMER_CHVSEL_ENABLE == ccsel){
        TIMER_CFG(timer_periph) |= (uint32_t)TIMER_CFG_CHVSEL;
    }else if(TIMER_CHVSEL_DISABLE == ccsel){
        TIMER_CFG(timer_periph) &= ~(uint32_t)TIMER_CFG_CHVSEL;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure TIMER output value selection (API_ID(0x0049U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[in]  outsel:
                only one parameter can be selected which is shown as below:
      \arg        TIMER_OUTSEL_DISABLE: no effect
      \arg        TIMER_OUTSEL_ENABLE: if POEN and IOS is 0, the output disabled
    \param[out] none
    \retval     none
*/
void timer_output_value_selection_config(uint32_t timer_periph, uint16_t outsel)
{
    if(TIMER_OUTSEL_ENABLE == outsel){
        TIMER_CFG(timer_periph) |= (uint32_t)TIMER_CFG_OUTSEL;
    }else if(TIMER_OUTSEL_DISABLE == outsel){
        TIMER_CFG(timer_periph) &= ~(uint32_t)TIMER_CFG_OUTSEL;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure commutation control shadow register update selection (API_ID(0x004AU))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[in]  ccssel: commutation control shadow register selection
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
    \brief      configure TIMER output match pulse selection (API_ID(0x004BU))
    \param[in]  timer_periph: TIMERx(x=0,7))
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7))
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
        reg |= (uint32_t)(((uint32_t)pulsesel & TIMER_PULSE_OUTPUT_MASK) << 8U);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        reg &= (~(uint32_t)((uint32_t)TIMER_PULSE_OUTPUT_MASK << 10U));
        reg |= (uint32_t)(((uint32_t)pulsesel & TIMER_PULSE_OUTPUT_MASK) << 10U);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        reg &= (~(uint32_t)((uint32_t)TIMER_PULSE_OUTPUT_MASK << 12U));
        reg |= (uint32_t)(((uint32_t)pulsesel & TIMER_PULSE_OUTPUT_MASK) << 12U);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        reg &= (~(uint32_t)((uint32_t)TIMER_PULSE_OUTPUT_MASK << 14U));
        reg |= (uint32_t)(((uint32_t)pulsesel & TIMER_PULSE_OUTPUT_MASK) << 14U);
        break;
    default:
        break;
    }
    TIMER_CTL2(timer_periph) = reg;
}

/*!
    \brief      configure the TIMER composite PWM mode (API_ID(0x004CU))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16))
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7))
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
    \brief      configure the TIMER composite PWM mode output pulse value (API_ID(0x004DU))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16))
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7))
    \param[in]  pulse: channel compare value, 0~65535
    \param[in]  add_pulse: channel additional compare value, 0~65535
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
    \brief      configure the TIMER asymmetric PWM mode output pulse value (API_ID(0x004EU))
    \param[in]  timer_periph: TIMERx(x=0,7)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7))
    \param[in]  pulse: channel compare value, 0~65535
    \param[in]  add_pulse: channel additional compare value, 0~65535
    \param[out] none
    \retval     none
*/
void timer_channel_asymmetric_pwm_pulse_config(uint32_t timer_periph, uint32_t channel, uint32_t pulse, uint32_t add_pulse)
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
    \brief      configure TIMER channel additional compare value (API_ID(0x004FU))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16))
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7))
    \param[in]  value: channel additional compare value, 0~65535
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
    \brief      select TIMER channel additional output register update source (API_ID(0x0050U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7))
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
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)update << 26U) & TIMER_CHCTL0_CH0ADDUPS);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1ADDUPS);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)update << 27U) & TIMER_CHCTL0_CH1ADDUPS);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2ADDUPS);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)(((uint32_t)update << 26U) & TIMER_CHCTL1_CH2ADDUPS);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3ADDUPS);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)(((uint32_t)update << 27U) & TIMER_CHCTL1_CH3ADDUPS);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel additional output shadow function (API_ID(0x0051U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7,))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7))
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
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)aocshadow << 28U) & TIMER_CHCTL0_CH0COMADDSEN);
        break;
    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMADDSEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(((uint32_t)aocshadow << 29U) & TIMER_CHCTL0_CH1COMADDSEN);
        break;
    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMADDSEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)(((uint32_t)aocshadow << 28U) & TIMER_CHCTL1_CH2COMADDSEN);
        break;
    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMADDSEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)(((uint32_t)aocshadow << 29U) & TIMER_CHCTL1_CH3COMADDSEN);
        break;
    default:
        break;
    }
}

/*!
    \brief      read TIMER channel additional compare value (API_ID(0x0052U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16))
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7,15,16))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7))
      \arg        TIMER_CH_3: TIMER channel 3(TIMERx(x=0,7))
    \param[out] none
    \retval     value: channel additional compare value, 0~65535
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
    \brief      configure the TIMER break source (API_ID(0x0053U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[in]  break_src: break source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_BRKIN0: BRKIN0 alternate function input enable, TIMERx(x=0,7,15,16)
      \arg        TIMER_BRKCMP0: CMP0 input enable, TIMERx(x=0,7,15,16)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_break_external_source_config(uint32_t timer_periph, uint32_t break_src, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        TIMER_AFCTL0(timer_periph) |= (break_src & TIMER_BREAK_SOURCE_MASK);
    } else {
        TIMER_AFCTL0(timer_periph) &= (~(break_src & TIMER_BREAK_SOURCE_MASK));
    }
}

/*!
    \brief      configure TIMER break polarity (API_ID(0x0054U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[in]  break_src: break source
                only one parameter can be selected which is shown as below:
      \arg        TIMER_BRKIN0: BRKIN0 alternate function input enable, TIMERx(x=0,7,15,16)
      \arg        TIMER_BRKCMP0: CMP0 input enable, TIMERx(x=0,7,15,16)
    \param[in]  bkinpolarity: break polarity
                only one parameter can be selected which is shown as below:
                  TIMER_BRKIN_POLARITY_LOW: input signal will not be inverted
                  TIMER_BRKIN_POLARITY_HIGH: input signal will be inverted
    \param[out] none
    \retval     none
*/
void timer_break_external_polarity_config(uint32_t timer_periph, uint32_t break_src, uint16_t bkinpolarity)
{
    switch(break_src) {
        case TIMER_BRKIN0:
            TIMER_AFCTL0(timer_periph) &= (~(uint32_t)TIMER_BRKIN0P);
            TIMER_AFCTL0(timer_periph) |= (uint32_t)(((uint32_t)bkinpolarity << 16U) & TIMER_BRKIN0P);
            break;
        case TIMER_BRKCMP0:
            TIMER_AFCTL0(timer_periph) &= (~(uint32_t)TIMER_BRKCMP0P);
            TIMER_AFCTL0(timer_periph) |= (uint32_t)(((uint32_t)bkinpolarity << 25U) & TIMER_BRKCMP0P);
            break;
        default:
        break;
    }
}

/*!
    \brief      configure the TIMER falling edge dead time (API_ID(0x0055U))
    \param[in]  timer_periph: TIMERx(x=0,7)
    \param[in]  deadtime: 0~255
    \param[out] none
    \retval     none
*/
void timer_dead_time_falling_edge_config(uint32_t timer_periph, uint32_t deadtime)
{
    TIMER_CCHP1(timer_periph) &= (~(uint32_t)TIMER_CCHP1_DTFCFG);
    TIMER_CCHP1(timer_periph) |= (uint32_t)(((uint32_t)deadtime) & TIMER_CCHP1_DTFCFG);
}

/*!
    \brief      configure the TIMER dead time different function (API_ID(0x0056U))
    \param[in]  timer_periph: TIMERx(x=0,7)
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
    \brief      configure the TIMER channel break function (API_ID(0x0057U))
    \param[in]  timer_periph: TIMERx(x=0,7)
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
        TIMER_CTL2(timer_periph) |= (uint32_t)(TIMER_CTL2_BRKENCH0 << (channel & TIMER_CHANNEL_MASK));
    } else {
        TIMER_CTL2(timer_periph) &= (~(uint32_t)(TIMER_CTL2_BRKENCH0 << (channel & TIMER_CHANNEL_MASK)));
    }
}

/*!
    \brief      configure the TIMER channel free dead time function (API_ID(0x0058U))
    \param[in]  timer_periph: TIMERx(x=0,7)
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
        TIMER_CTL2(timer_periph) |= (uint32_t)(TIMER_CTL2_DTIENCH0 << (channel & TIMER_CHANNEL_MASK));
    } else {
        TIMER_CTL2(timer_periph) &= (~(uint32_t)(TIMER_CTL2_DTIENCH0 << (channel & TIMER_CHANNEL_MASK)));
    }
}


/*!
    \brief      configure the TIMER channel break (API_ID(0x0059U))
    \param[in]  timer_periph: TIMERx(x=0,7)
    \param[in]  breaken: TIMER channel break enable
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_BREAK_ENABLE: channel BREAK input signal enable
      \arg        TIMER_CH_BREAK_DISABLE: channel BREAK input signal disable
    \param[in] breakpolarity: channel BREAK input signal polarity
      \arg        TIMER_CH_BREAK_POLARITY_HIGH: channel BREAK input active high
      \arg        TIMER_CH_BREAK_POLARITY_LOW: channel BREAK input active low
    \param[in] breakfilter: 0~15
    \param[out] none
    \retval     none
*/
void timer_channel_break_config(uint32_t timer_periph, uint32_t breaken, uint32_t breakpolarity, uint32_t breakfilter)
{
    TIMER_CCHP0(timer_periph) &= (~(uint32_t)(TIMER_CCHP0_CHBRKEN | TIMER_CCHP0_CHBRKP | TIMER_CCHP0_BRKF));
    TIMER_CCHP0(timer_periph) |= (uint32_t)((breaken & TIMER_CCHP0_CHBRKEN) | (breakpolarity & TIMER_CCHP0_CHBRKP)| ((breakfilter << 16U) & TIMER_CCHP0_BRKF));
}

/*!
    \brief      configure TIMER channel break external input enable (API_ID(0x005AU))
    \param[in]  timer_periph: TIMERx(x=0,7)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7))
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_channel_break_external_status_config(uint32_t timer_periph, uint32_t channel, ControlStatus newvalue)
{
    switch(channel) {
    case TIMER_CH_0:
        if(ENABLE == newvalue) {
            TIMER_CHBRKCTL(timer_periph) |= (uint32_t)TIMER_CHBRKCTL_CH0BRKINEN;
        } else {
            TIMER_CHBRKCTL(timer_periph) &= (~(uint32_t)TIMER_CHBRKCTL_CH0BRKINEN);
        }
        break;
    case TIMER_CH_1:
        if(ENABLE == newvalue) {
            TIMER_CHBRKCTL(timer_periph) |= (uint32_t)TIMER_CHBRKCTL_CH1BRKINEN;
        } else {
            TIMER_CHBRKCTL(timer_periph) &= (~(uint32_t)TIMER_CHBRKCTL_CH1BRKINEN);
        }
        break;
    case TIMER_CH_2:
        if(ENABLE == newvalue) {
            TIMER_CHBRKCTL(timer_periph) |= (uint32_t)TIMER_CHBRKCTL_CH2BRKINEN;
        } else {
            TIMER_CHBRKCTL(timer_periph) &= (~(uint32_t)TIMER_CHBRKCTL_CH2BRKINEN);
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel break external input polarity (API_ID(0x005BU))
    \param[in]  timer_periph: TIMERx(x=0,7)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7))
    \param[in]  bkinpolarity: channel x BREAK input signal polarity
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CHx_BREAK_IN_INV: channel x BREAK input signal will be inverted
      \arg        TIMER_CHx_BREAK_IN_NOT_INV: channel x BREAK input signal will not be inverted
    \param[out] none
    \retval     none
*/
void timer_channel_break_external_polarity_config(uint32_t timer_periph, uint32_t channel, uint16_t bkinpolarity)
{
    switch(channel) {
    case TIMER_CH_0:
        if(TIMER_CHx_BREAK_IN_INV == bkinpolarity) {
            TIMER_CHBRKCTL(timer_periph) |= (uint32_t)TIMER_CHBRKCTL_CH0BRKINP;
        } else {
            TIMER_CHBRKCTL(timer_periph) &= (~(uint32_t)TIMER_CHBRKCTL_CH0BRKINP);
        }
        break;
    case TIMER_CH_1:
        if(TIMER_CHx_BREAK_IN_INV == bkinpolarity) {
            TIMER_CHBRKCTL(timer_periph) |= (uint32_t)TIMER_CHBRKCTL_CH1BRKINP;
        } else {
            TIMER_CHBRKCTL(timer_periph) &= (~(uint32_t)TIMER_CHBRKCTL_CH1BRKINP);
        }
        break;
    case TIMER_CH_2:
        if(TIMER_CHx_BREAK_IN_INV == bkinpolarity) {
            TIMER_CHBRKCTL(timer_periph) |= (uint32_t)TIMER_CHBRKCTL_CH2BRKINP;
        } else {
            TIMER_CHBRKCTL(timer_periph) &= (~(uint32_t)TIMER_CHBRKCTL_CH2BRKINP);
        }
        break;
    default:
        break;
    }
}



/*!
    \brief      configure TIMER channel primary output function (API_ID(0x005CU))
    \param[in]  timer_periph: TIMERx(x=0,7)
    \param[in]  channel: TIMER channel
                only one parameter can be selected which is shown as below:
      \arg        TIMER_CH_0: TIMER channel 0(TIMERx(x=0,7))
      \arg        TIMER_CH_1: TIMER channel 1(TIMERx(x=0,7))
      \arg        TIMER_CH_2: TIMER channel 2(TIMERx(x=0,7))
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void timer_channel_primary_output_config(uint32_t timer_periph, uint32_t channel, ControlStatus newvalue)
{
    switch(channel) {
    case TIMER_CH_0:
        if(ENABLE == newvalue) {
            TIMER_CHBRKCTL(timer_periph) |= (uint32_t)TIMER_CHBRKCTL_CHPOEN0;
        } else {
            TIMER_CHBRKCTL(timer_periph) &= (~(uint32_t)TIMER_CHBRKCTL_CHPOEN0);
        }
        break;
    case TIMER_CH_1:
        if(ENABLE == newvalue) {
            TIMER_CHBRKCTL(timer_periph) |= (uint32_t)TIMER_CHBRKCTL_CHPOEN1;
        } else {
            TIMER_CHBRKCTL(timer_periph) &= (~(uint32_t)TIMER_CHBRKCTL_CHPOEN1);
        }
        break;
    case TIMER_CH_2:
        if(ENABLE == newvalue) {
            TIMER_CHBRKCTL(timer_periph) |= (uint32_t)TIMER_CHBRKCTL_CHPOEN2;
        } else {
            TIMER_CHBRKCTL(timer_periph) &= (~(uint32_t)TIMER_CHBRKCTL_CHPOEN2);
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      configure TIMER channel break period value (API_ID(0x005DU))
    \param[in]  timer_periph: TIMERx(x=0,7)
    \param[in]  value: channel break period value, 0~0xFFFF
    \param[out] none
    \retval     none
*/
void timer_channel_break_period_config(uint32_t timer_periph, uint16_t value)
{
    TIMER_CHBRKPER(timer_periph) = (uint32_t)value;
}


/*!
    \brief      configure quadrature decoder signal disconnection detection watchdog value (API_ID(0x005EU))
    \param[in]  timer_periph: TIMERx(x=1~4)
    \param[in]  value: watchdog counter period value, 0~0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void timer_watchdog_value_config(uint32_t timer_periph, uint32_t value)
{
    TIMER_WDGPER(timer_periph) = value;
}

/*!
    \brief      read quadrature decoder signal disconnection detection watchdog value (API_ID(0x005FU))
    \param[in]  timer_periph: TIMERx(x=1~4)
    \param[out] none
    \retval     watchdog counter period register value, 0~0xFFFFFFFF
*/
uint32_t timer_watchdog_value_read(uint32_t timer_periph)
{
    return (TIMER_WDGPER(timer_periph));
}

/*!
    \brief      configure quadrature decoder signal disconnection detection function (API_ID(0x0060U))
    \param[in]  timer_periph: TIMERx(x=1~4)
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
    \brief      configure quadrature decoder signal jump detection function (API_ID(0x0061U))
    \param[in]  timer_periph: TIMERx(x=1~4)
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
    \brief      configure counter initial value register (API_ID(0x0062U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
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
    \brief      configure counter initial value and direction (API_ID(0x0063U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
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
    TIMER_CINITCTL(timer_periph) |= (uint32_t)((uint32_t)direction & TIMER_CINITCTL_CINITDIR);
}

/*!
    \brief      generate soft synchronization event (API_ID(0x0064U))
    \param[in]  timer_periph: TIMERx(x=0,7,15,16)
    \param[out] none
    \retval     none
*/
void timer_synchronization_event_generate(uint32_t timer_periph)
{
    TIMER_CINITCTL(timer_periph) |= TIMER_CINITCTL_SWSYNCG;
}

/*!
    \brief      get TIMER flags (API_ID(0x0065U))
    \param[in]  timer_periph: TIMERx(x=0~7,15,16)
    \param[in]  flag: the TIMER flags
                only one parameter can be selected which is shown as below:
      \arg        TIMER_FLAG_UP: update flag, TIMERx(x=0~7,15,16)
      \arg        TIMER_FLAG_CH0: channel 0 capture or compare flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_FLAG_CH1: channel 1 capture or compare flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_FLAG_CH2: channel 2 capture or compare flag, TIMERx(x=0~4,7)
      \arg        TIMER_FLAG_CH3: channel 3 capture or compare flag, TIMERx(x=0~4,7)
      \arg        TIMER_FLAG_CMT: channel commutation flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_FLAG_TRG: trigger flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_FLAG_BRK: BREAK flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_FLAG_CH0O: channel 0 overcapture flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_FLAG_CH1O: channel 1 overcapture flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_FLAG_CH2O: channel 2 overcapture flag, TIMERx(x=0~4,7)
      \arg        TIMER_FLAG_CH3O: channel 3 overcapture flag, TIMERx(x=0~4,7)
      \arg        TIMER_FLAG_SYSB: system source break flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_DECJ: quadrature decoder signal jump flag, TIMERx(x=1~4)
      \arg        TIMER_FLAG_DECDIS: quadrature decoder signal disconnection flag, TIMERx(x=1~4)
      \arg        TIMER_FLAG_MCH0: multi mode channel 0 capture or compare flag, TIMERx(x=15,16)
      \arg        TIMER_FLAG_MCH0O: multi mode channel 0 overcapture flag, TIMERx(x=15,16)
      \arg        TIMER_FLAG_CH0COMADD: channel 0 additional compare flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_FLAG_CH1COMADD: channel 1 additional compare flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_FLAG_CH2COMADD: channel 2 additional compare flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH3COMADD: channel 3 additional compare flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH0BRKM: channel 0 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH1BRKM: channel 1 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH2BRKM: channel 2 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH0BRK: channel 0 BREAK interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH1BRK: channel 1 BREAK interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH2BRK: channel 2 BREAK interrupt flag, TIMERx(x=0,7)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus timer_flag_get(uint32_t timer_periph, uint32_t flag)
{
    FlagStatus timer_flag = RESET;
    
    if(RESET != (TIMER_REG_VAL1(timer_periph, flag) & BIT(TIMER_BIT_POS1(flag)))){
        timer_flag = SET;
    }else{
        timer_flag = RESET;
    }
    
    return timer_flag;
}

/*!
    \brief      clear TIMER flags (API_ID(0x0066U))
    \param[in]  timer_periph: TIMERx(x=0~7,15,16)
    \param[in]  flag: the TIMER flags
                only one parameter can be selected which are shown as below:
      \arg        TIMER_FLAG_UP: update flag, TIMERx(x=0~7,15,16)
      \arg        TIMER_FLAG_CH0: channel 0 capture or compare flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_FLAG_CH1: channel 1 capture or compare flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_FLAG_CH2: channel 2 capture or compare flag, TIMERx(x=0~4,7)
      \arg        TIMER_FLAG_CH3: channel 3 capture or compare flag, TIMERx(x=0~4,7)
      \arg        TIMER_FLAG_CMT: channel commutation flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_FLAG_TRG: trigger flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_FLAG_BRK: BREAK flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_FLAG_CH0O: channel 0 overcapture flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_FLAG_CH1O: channel 1 overcapture flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_FLAG_CH2O: channel 2 overcapture flag, TIMERx(x=0~4,7)
      \arg        TIMER_FLAG_CH3O: channel 3 overcapture flag, TIMERx(x=0~4,7)
      \arg        TIMER_FLAG_SYSB: system source break flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_DECJ: quadrature decoder signal jump flag, TIMERx(x=1~4)
      \arg        TIMER_FLAG_DECDIS: quadrature decoder signal disconnection flag, TIMERx(x=1~4)
      \arg        TIMER_FLAG_MCH0: multi mode channel 0 capture or compare flag, TIMERx(x=15,16)
      \arg        TIMER_FLAG_MCH0O: multi mode channel 0 overcapture flag, TIMERx(x=15,16)
      \arg        TIMER_FLAG_CH0COMADD: channel 0 additional compare flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_FLAG_CH1COMADD: channel 1 additional compare flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_FLAG_CH2COMADD: channel 2 additional compare flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH3COMADD: channel 3 additional compare flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH0BRKM: channel 0 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH1BRKM: channel 1 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH2BRKM: channel 2 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH0BRK: channel 0 BREAK interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH1BRK: channel 1 BREAK interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_FLAG_CH2BRK: channel 2 BREAK interrupt flag, TIMERx(x=0,7)
    \param[out] none
    \retval     none
*/
void timer_flag_clear(uint32_t timer_periph, uint32_t flag)
{
    TIMER_REG_VAL1(timer_periph, flag) &= (~(uint32_t)BIT(TIMER_BIT_POS1(flag)));
}

/*!
    \brief      enable the TIMER interrupt (API_ID(0x0067U))
    \param[in]  timer_periph: TIMERx(x=0~7,15,16)
    \param[in]  interrupt: timer interrupt source
                only one parameter can be selected which are shown as below:
      \arg        TIMER_INT_UP: update interrupt, TIMERx(x=0~7,15,16)
      \arg        TIMER_INT_CH0: channel 0 capture or compare interrupt, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_CH1: channel 1 capture or compareinterrupt, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_CH2: channel 2 capture or compare interrupt, TIMERx(x=0~4,7)
      \arg        TIMER_INT_CH3: channel 3 capture or compare interrupt, TIMERx(x=0~4,7)
      \arg        TIMER_INT_CMT: channel commutation interrupt, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_TRG: trigger interrupt, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_BRK: break interrupt, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_DECJ: quadrature decoder signal jump interrupt, TIMERx(x=1~4)
      \arg        TIMER_INT_DECDIS: quadrature decoder signal disconnection interrupt, TIMERx(x=1~4)
      \arg        TIMER_INT_MCH0: multi mode channel 0 capture or compare interrupt, TIMERx(x=15,16)
      \arg        TIMER_INT_CH0COMADD: channel 0 additional compare interrupt, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_CH1COMADD: channel 1 additional compare interrupt, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_CH2COMADD: channel 2 additional compare interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH3COMADD: channel 3 additional compare interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH0BRKM: channel 0 BREAK multi-period interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH1BRKM: channel 1 BREAK multi-period interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH2BRKM: channel 2 BREAK multi-period interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH0BRK: channel 0 BREAK interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH1BRK: channel 1 BREAK interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH2BRK: channel 2 BREAK interrupt, TIMERx(x=0,7)
    \param[out] none
    \retval     none
*/
void timer_interrupt_enable(uint32_t timer_periph, uint32_t interrupt)
{
    TIMER_REG_VAL1(timer_periph, interrupt) |= (uint32_t) BIT(TIMER_BIT_POS1(interrupt));
}

/*!
    \brief      disable the TIMER interrupt (API_ID(0x0068U))
    \param[in]  timer_periph: TIMERx(x=0~7,15,16)
    \param[in]  interrupt: timer interrupt source
                only one parameter can be selected which are shown as below:
      \arg        TIMER_INT_UP: update interrupt, TIMERx(x=0~7,15,16)
      \arg        TIMER_INT_CH0: channel 0 capture or compare interrupt, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_CH1: channel 1 capture or compareinterrupt, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_CH2: channel 2 capture or compare interrupt, TIMERx(x=0~4,7)
      \arg        TIMER_INT_CH3: channel 3 capture or compare interrupt, TIMERx(x=0~4,7)
      \arg        TIMER_INT_CMT: channel commutation interrupt, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_TRG: trigger interrupt, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_BRK: break interrupt, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_DECJ: quadrature decoder signal jump interrupt, TIMERx(x=1~4)
      \arg        TIMER_INT_DECDIS: quadrature decoder signal disconnection interrupt, TIMERx(x=1~4)
      \arg        TIMER_INT_MCH0: multi mode channel 0 capture or compare interrupt, TIMERx(x=15,16)
      \arg        TIMER_INT_CH0COMADD: channel 0 additional compare interrupt, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_CH1COMADD: channel 1 additional compare interrupt, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_CH2COMADD: channel 2 additional compare interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH3COMADD: channel 3 additional compare interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH0BRKM: channel 0 BREAK multi-period interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH1BRKM: channel 1 BREAK multi-period interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH2BRKM: channel 2 BREAK multi-period interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH0BRK: channel 0 BREAK interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH1BRK: channel 1 BREAK interrupt, TIMERx(x=0,7)
      \arg        TIMER_INT_CH2BRK: channel 2 BREAK interrupt, TIMERx(x=0,7)
    \param[out] none
    \retval     none
*/
void timer_interrupt_disable(uint32_t timer_periph, uint32_t interrupt)
{
    TIMER_REG_VAL1(timer_periph, interrupt) &= (~(uint32_t)BIT(TIMER_BIT_POS1(interrupt)));
}

/*!
    \brief      get timer interrupt flags (API_ID(0x0069U))
    \param[in]  timer_periph: TIMERx(x=0~7,15,16)
    \param[in]  int_flag: the timer interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        TIMER_INT_FLAG_UP: update interrupt flag, TIMERx(x=0~7,15,16)
      \arg        TIMER_INT_FLAG_CH0: channel 0 capture or compare interrupt flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_FLAG_CH1: channel 1 capture or compare interrupt flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_FLAG_CH2: channel 2 capture or compare interrupt flag, TIMERx(x=0~4,7)
      \arg        TIMER_INT_FLAG_CH3: channel 3 capture or compare interrupt flag, TIMERx(x=0~4,7)
      \arg        TIMER_INT_FLAG_CMT: channel commutation interrupt flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_FLAG_TRG: trigger interrupt flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_FLAG_BRK: BREAK interrupt flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_FLAG_SYSB: system source break interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_DECJ: quadrature decoder signal jump interrupt flag, TIMERx(x=1~4)
      \arg        TIMER_INT_FLAG_DECDIS: quadrature decoder signal disconnection interrupt flag, TIMERx(x=1~4)
      \arg        TIMER_INT_FLAG_MCH0: multi mode channel 0 capture or compare interrupt flag, TIMERx(x=15,16)
      \arg        TIMER_INT_FLAG_CH0COMADD: channel 0 additional compare interrupt flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_FLAG_CH1COMADD: channel 1 additional compare interrupt flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_FLAG_CH2COMADD: channel 2 additional compare interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH3COMADD: channel 3 additional compare interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH0BRKM: channel 0 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH1BRKM: channel 1 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH2BRKM: channel 2 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH0BRK: channel 0 BREAK interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH1BRK: channel 1 BREAK interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH2BRK: channel 2 BREAK interrupt flag, TIMERx(x=0,7)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus timer_interrupt_flag_get(uint32_t timer_periph, uint32_t int_flag)
{
    FlagStatus timer_interrupt_flag = RESET;
    uint32_t intenable = 0U, flagstatus = 0U;
    /* get the interrupt enable bit status */
    intenable = (TIMER_REG_VAL1(timer_periph, int_flag) & BIT(TIMER_BIT_POS1(int_flag)));
    /* get the corresponding flag bit status */
    flagstatus = (TIMER_REG_VAL2(timer_periph, int_flag) & BIT(TIMER_BIT_POS2(int_flag)));

    if(flagstatus && intenable){
        timer_interrupt_flag =  SET;
    }else{
        timer_interrupt_flag =  RESET;
    }
    
    return timer_interrupt_flag;
}

/*!
    \brief      clear TIMER interrupt flags (API_ID(0x006AU))
    \param[in]  timer_periph: TIMERx(x=0~7,15,16)
    \param[in]  int_flag: the timer interrupt flags
                only one parameter can be selected which are shown as below:
      \arg        TIMER_INT_FLAG_UP: update interrupt flag, TIMERx(x=0~7,15,16)
      \arg        TIMER_INT_FLAG_CH0: channel 0 capture or compare interrupt flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_FLAG_CH1: channel 1 capture or compare interrupt flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_FLAG_CH2: channel 2 capture or compare interrupt flag, TIMERx(x=0~4,7)
      \arg        TIMER_INT_FLAG_CH3: channel 3 capture or compare interrupt flag, TIMERx(x=0~4,7)
      \arg        TIMER_INT_FLAG_CMT: channel commutation interrupt flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_FLAG_TRG: trigger interrupt flag, TIMERx(x=0~4,7,15,16)
      \arg        TIMER_INT_FLAG_BRK: BREAK interrupt flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_FLAG_SYSB: system source break interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_DECJ: quadrature decoder signal jump interrupt flag, TIMERx(x=1~4)
      \arg        TIMER_INT_FLAG_DECDIS: quadrature decoder signal disconnection interrupt flag, TIMERx(x=1~4)
      \arg        TIMER_INT_FLAG_MCH0: multi mode channel 0 capture or compare interrupt flag, TIMERx(x=15,16)
      \arg        TIMER_INT_FLAG_CH0COMADD: channel 0 additional compare interrupt flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_FLAG_CH1COMADD: channel 1 additional compare interrupt flag, TIMERx(x=0,7,15,16)
      \arg        TIMER_INT_FLAG_CH2COMADD: channel 2 additional compare interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH3COMADD: channel 3 additional compare interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH0BRKM: channel 0 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH1BRKM: channel 1 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH2BRKM: channel 2 BREAK multi-period interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH0BRK: channel 0 BREAK interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH1BRK: channel 1 BREAK interrupt flag, TIMERx(x=0,7)
      \arg        TIMER_INT_FLAG_CH2BRK: channel 2 BREAK interrupt flag, TIMERx(x=0,7)
    \param[out] none
    \retval     none
*/
void timer_interrupt_flag_clear(uint32_t timer_periph, uint32_t int_flag)
{
    TIMER_REG_VAL2(timer_periph, int_flag) &= (~(uint32_t)BIT(TIMER_BIT_POS2(int_flag)));
}

