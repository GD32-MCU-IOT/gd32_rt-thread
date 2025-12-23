/*!
    \file    gd32g5x3_hrtimer.c
    \brief   HRTIMER driver

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

#include "gd32g5x3_hrtimer.h"

/* HRTIMER related parameter mask */
#define CNTCKDIV2_0_MASK (uint32_t)(0x00000007)
#define STX_UPDATESOURCE_MASK0_5 (HRTIMER_STXCTL0_UPBST0 | HRTIMER_STXCTL0_UPBST1 | HRTIMER_STXCTL0_UPBST2 | HRTIMER_STXCTL0_UPBST3 | HRTIMER_STXCTL0_UPBST4 | HRTIMER_STXCTL0_UPBST5 | HRTIMER_STXCTL0_UPBMT)
#define STX_UPDATESOURCE_MASK6_7 (HRTIMER_STXACTL_UPBST6 | HRTIMER_STXACTL_UPBST7)
#define STX_FAULTCH_MASK (HRTIMER_STXFLTCTL_FLT0EN | HRTIMER_STXFLTCTL_FLT1EN | HRTIMER_STXFLTCTL_FLT2EN | HRTIMER_STXFLTCTL_FLT3EN | HRTIMER_STXFLTCTL_FLT4EN| HRTIMER_STXFLTCTL_FLT5EN| HRTIMER_STXFLTCTL_FLT6EN| HRTIMER_STXFLTCTL_FLT7EN)

/* configure Master_TIMER timer base */
static void master_timer_base_config(uint32_t hrtimer_periph, hrtimer_baseinit_parameter_struct* master_baseinit);
/* configure Master_TIMER in waveform mode  */
static void master_timer_waveform_config(uint32_t hrtimer_periph, hrtimer_timerinit_parameter_struct * master_timerinit);
/* configure Slave_TIMER timer base */
static void slave_timer_base_config(uint32_t hrtimer_periph, uint32_t slave_id, hrtimer_baseinit_parameter_struct* slave_baseinit);
/* configure Slave_TIMER in waveform mode  */
static void slave_timer_waveform_config(uint32_t hrtimer_periph, uint32_t slave_id, hrtimer_timerinit_parameter_struct * slave_timerinit);
/* configure the an external event channel */
static void external_event_config(uint32_t hrtimer_periph, uint32_t event_id, hrtimer_exeventcfg_parameter_struct* eventcfg);
/* configure the channel output  */
static void channel_output_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t channel, hrtimer_channel_outputcfg_parameter_struct * outcfg);

/*!
    \brief      deinit a HRTIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[out] none
    \retval     none
*/
void hrtimer_deinit(uint32_t hrtimer_periph)
{
    switch(hrtimer_periph){
    case HRTIMER0:
        /* reset HRTIMER0 */
        rcu_periph_reset_enable(RCU_HRTIMERRST);
        rcu_periph_reset_disable(RCU_HRTIMERRST);
        break;
    default:
    break;
    }
}

/*!
    \brief      configure and start DLL calibration
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  calform: specify the calibration form
                only one can be selected which is shown as below:
      \arg          HRTIMER_CALIBRATION_ONCE: DLL calibration start once
      \arg          HRTIMER_CALIBRATION_1048576_PERIOD: DLL periodic calibration, the length of the DLL calibration cycle is 1048576 * tHRTIMER_CK
      \arg          HRTIMER_CALIBRATION_131072_PERIOD: DLL periodic calibration, the length of the DLL calibration cycle is 131072  * tHRTIMER_CK
      \arg          HRTIMER_CALIBRATION_16384_PERIOD: DLL periodic calibration, the length of the DLL calibration cycle is 16384  * tHRTIMER_CK
      \arg          HRTIMER_CALIBRATION_2048_PERIOD: DLL periodic calibration, the length of the DLL calibration cycle is 2048 * tHRTIMER_CK
    \param[out] none
    \retval     none
*/
void hrtimer_dll_calibration_start(uint32_t hrtimer_periph, uint32_t calform)
{
    uint32_t dllcctl_reg;

    /* configure DLL calibration */
    dllcctl_reg = HRTIMER_DLLCCTL(hrtimer_periph);
  
    if (HRTIMER_CALIBRATION_ONCE == calform){
        /* DLL periodic calibration disable */
        dllcctl_reg &= ~(HRTIMER_DLLCCTL_CLBPEREN);
        dllcctl_reg |= HRTIMER_DLLCCTL_CLBSTRT;
    }else{
        /* DLL periodic calibration enable */
        dllcctl_reg &= ~(HRTIMER_DLLCCTL_CLBPER | HRTIMER_DLLCCTL_CLBSTRT);
        dllcctl_reg |= (calform | HRTIMER_DLLCCTL_CLBPEREN);
    }
    
    HRTIMER_DLLCCTL(hrtimer_periph) = dllcctl_reg;
}

/*!
    \brief      initialize HRTIMER time base parameters struct with a default value 
    \param[in]  baseinit: HRTIMER time base parameters struct
    \param[out] none
    \retval     none
*/
void hrtimer_baseinit_struct_para_init(hrtimer_baseinit_parameter_struct* baseinit)
{
    baseinit->counter_mode = HRTIMER_COUNTER_MODE_SINGLEPULSE;
    baseinit->period = 0xFFDFU;
    baseinit->prescaler = HRTIMER_PRESCALER_MUL32;
    baseinit->counterdirection = HRTIMER_COUNTER_UP;
    baseinit->repetitioncounter = 0x00U;
}

/*!
    \brief      initialize Master_TIMER and Slave_TIMER timerbase 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  baseinit: HRTIMER time base parameters struct
                  period: period value, min value: 3*tHRTIMER_CK clock, max value: 0xFFFF �C (1*tHRTIMER_CK)
                  repetitioncounter: the counter repetition value, 0x00~0xFF
                  prescaler: HRTIMER_PRESCALER_MULy(y=32,16,8,4,2), HRTIMER_PRESCALER_DIVy(y=1,2,4)
                  counter_mode: HRTIMER_COUNTER_MODE_CONTINOUS, HRTIMER_COUNTER_MODE_SINGLEPULSE, HRTIMER_COUNTER_MODE_SINGLEPULSE_RETRIGGERABLE
                  counterdirection: HRTIMER_COUNTER_UP,HRTIMER_COUNTER_CENTER_ALIGNED
    \param[out] none
    \retval     none
*/
void hrtimer_timers_base_init(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_baseinit_parameter_struct* baseinit)
{
    if(HRTIMER_MASTER_TIMER == timer_id)
    {
        /* configure Master_TIMER timer base */
        master_timer_base_config(hrtimer_periph, baseinit);
    }else{
        /* configure Slave_TIMER timer base */
        slave_timer_base_config(hrtimer_periph, timer_id, baseinit);
    }
}

/*!
    \brief      enable a counter
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  cntid: specify the counter to configure
                only one can be selected which is shown as below:
      \arg          HRTIMER_MT_COUNTER: the counter of Master_TIMER
      \arg          HRTIMER_ST0_COUNTER: the counter of Slave_TIMER0
      \arg          HRTIMER_ST1_COUNTER: the counter of Slave_TIMER1
      \arg          HRTIMER_ST2_COUNTER: the counter of Slave_TIMER2
      \arg          HRTIMER_ST3_COUNTER: the counter of Slave_TIMER3
      \arg          HRTIMER_ST4_COUNTER: the counter of Slave_TIMER4
      \arg          HRTIMER_ST5_COUNTER: the counter of Slave_TIMER5
      \arg          HRTIMER_ST6_COUNTER: the counter of Slave_TIMER6
      \arg          HRTIMER_ST7_COUNTER: the counter of Slave_TIMER7
    \param[out] none
    \retval     none
*/
void hrtimer_timers_counter_enable(uint32_t hrtimer_periph, uint32_t cntid)
{
    HRTIMER_MTCTL0(hrtimer_periph) |= cntid;
}

/*!
    \brief      disable a counter
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  cntid: specify the counter to configure
                only one can be selected which is shown as below:
      \arg          HRTIMER_MT_COUNTER: the counter of Master_TIMER
      \arg          HRTIMER_ST0_COUNTER: the counter of Slave_TIMER0 
      \arg          HRTIMER_ST1_COUNTER: the counter of Slave_TIMER1 
      \arg          HRTIMER_ST2_COUNTER: the counter of Slave_TIMER2 
      \arg          HRTIMER_ST3_COUNTER: the counter of Slave_TIMER3 
      \arg          HRTIMER_ST4_COUNTER: the counter of Slave_TIMER4 
      \arg          HRTIMER_ST5_COUNTER: the counter of Slave_TIMER5 
      \arg          HRTIMER_ST6_COUNTER: the counter of Slave_TIMER6 
      \arg          HRTIMER_ST7_COUNTER: the counter of Slave_TIMER7 
    \param[out] none
    \retval     none
*/
void hrtimer_timers_counter_disable(uint32_t hrtimer_periph, uint32_t cntid)
{
    HRTIMER_MTCTL0(hrtimer_periph) &= ~(cntid);
}

/*!
    \brief      enable the Master_TIMER or Slave_TIMER update event
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[out] none
    \retval     none
*/
void hrtimer_timers_update_event_enable(uint32_t hrtimer_periph, uint32_t timer_id)
{
    switch(timer_id)
    {
        case HRTIMER_MASTER_TIMER:
            /* enable the Master_TIMER update event */
            HRTIMER_CTL0(hrtimer_periph) &= ~HRTIMER_CTL0_MTUPDIS;
        break;
        case HRTIMER_SLAVE_TIMER0:
            /* enable the Slave_TIMER0 update event */
            HRTIMER_CTL0(hrtimer_periph) &= ~HRTIMER_CTL0_ST0UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER1:
            /* enable the Slave_TIMER1 update event */
            HRTIMER_CTL0(hrtimer_periph) &= ~HRTIMER_CTL0_ST1UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER2:
            /* enable the Slave_TIMER2 update event */
            HRTIMER_CTL0(hrtimer_periph) &= ~HRTIMER_CTL0_ST2UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER3:
            /* enable the Slave_TIMER3 update event */
            HRTIMER_CTL0(hrtimer_periph) &= ~HRTIMER_CTL0_ST3UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER4:
            /* enable the Slave_TIMER4 update event */
            HRTIMER_CTL0(hrtimer_periph) &= ~HRTIMER_CTL0_ST4UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER5:
            /* enable the Slave_TIMER5 update event */
            HRTIMER_CTL0(hrtimer_periph) &= ~HRTIMER_CTL0_ST5UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER6:
            /* enable the Slave_TIMER6 update event */
            HRTIMER_CTL0(hrtimer_periph) &= ~HRTIMER_CTL0_ST6UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER7:
            /* enable the Slave_TIMER7 update event */
            HRTIMER_CTL0(hrtimer_periph) &= ~HRTIMER_CTL0_ST7UPDIS;
        break;
        default:
        break;  
    }
}

/*!
    \brief      disable the Master_TIMER or Slave_TIMER update event
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[out] none
    \retval     none
*/
void hrtimer_timers_update_event_disable(uint32_t hrtimer_periph, uint32_t timer_id)
{
    switch(timer_id)
    {
        case HRTIMER_MASTER_TIMER:
            /* disable the Master_TIMER update event */
            HRTIMER_CTL0(hrtimer_periph) |= HRTIMER_CTL0_MTUPDIS;
        break;
        case HRTIMER_SLAVE_TIMER0:
            /* disable the Slave_TIMER0 update event */
            HRTIMER_CTL0(hrtimer_periph) |= HRTIMER_CTL0_ST0UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER1:
            /* disable the Slave_TIMER1 update event */
            HRTIMER_CTL0(hrtimer_periph) |= HRTIMER_CTL0_ST1UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER2:
            /* disable the Slave_TIMER2 update event */
            HRTIMER_CTL0(hrtimer_periph) |= HRTIMER_CTL0_ST2UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER3:
            /* disable the Slave_TIMER3 update event */
            HRTIMER_CTL0(hrtimer_periph) |= HRTIMER_CTL0_ST3UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER4:
            /* disable the Slave_TIMER4 update event */
            HRTIMER_CTL0(hrtimer_periph) |= HRTIMER_CTL0_ST4UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER5:
            /* disable the Slave_TIMER5 update event */
            HRTIMER_CTL0(hrtimer_periph) |= HRTIMER_CTL0_ST5UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER6:
            /* disable the Slave_TIMER6 update event */
            HRTIMER_CTL0(hrtimer_periph) |= HRTIMER_CTL0_ST6UPDIS;
        break;
        case HRTIMER_SLAVE_TIMER7:
            /* disable the Slave_TIMER7 update event */
            HRTIMER_CTL0(hrtimer_periph) |= HRTIMER_CTL0_ST7UPDIS;
        break;
        default:
        break;  
    }
}

/*!
    \brief      trigger the Master_TIMER and Slave_TIMER registers update by software
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timersrc: which timer to be update by software
                only one can be selected which is shown as below:
      \arg         HRTIMER_UPDATE_SW_MT: Master_TIMER software update
      \arg         HRTIMER_UPDATE_SW_ST0: Slave_TIMER0 software update
      \arg         HRTIMER_UPDATE_SW_ST1: Slave_TIMER1 software update
      \arg         HRTIMER_UPDATE_SW_ST2: Slave_TIMER2 software update
      \arg         HRTIMER_UPDATE_SW_ST3: Slave_TIMER3 software update
      \arg         HRTIMER_UPDATE_SW_ST4: Slave_TIMER4 software update
      \arg         HRTIMER_UPDATE_SW_ST5: Slave_TIMER5 software update
      \arg         HRTIMER_UPDATE_SW_ST6: Slave_TIMER6 software update
      \arg         HRTIMER_UPDATE_SW_ST7: Slave_TIMER7 software update
    \param[out] none
    \retval     none
*/
void hrtimer_software_update(uint32_t hrtimer_periph, uint32_t timersrc)
{
    HRTIMER_CTL1(hrtimer_periph) |= timersrc;
}

/*!
    \brief      reset the Master_TIMER and Slave_TIMER counter by software 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timerrst: which timer to be reset by software
                only one can be selected which is shown as below:
      \arg         HRTIMER_COUNTER_RESET_SW_MT: Master_TIMER software reset
      \arg         HRTIMER_COUNTER_RESET_SW_ST0: Slave_TIMER0 software reset  
      \arg         HRTIMER_COUNTER_RESET_SW_ST1: Slave_TIMER1 software reset
      \arg         HRTIMER_COUNTER_RESET_SW_ST2: Slave_TIMER2 software reset
      \arg         HRTIMER_COUNTER_RESET_SW_ST3: Slave_TIMER3 software reset
      \arg         HRTIMER_COUNTER_RESET_SW_ST4: Slave_TIMER4 software reset
      \arg         HRTIMER_COUNTER_RESET_SW_ST5: Slave_TIMER5 software reset
      \arg         HRTIMER_COUNTER_RESET_SW_ST6: Slave_TIMER6 software reset
      \arg         HRTIMER_COUNTER_RESET_SW_ST7: Slave_TIMER7 software reset
    \param[out] none
    \retval     none
*/
void hrtimer_software_counter_reset(uint32_t hrtimer_periph, uint32_t timerrst)
{
    HRTIMER_CTL1(hrtimer_periph) |= timerrst;
}

/*!
    \brief      exchange Slave_TIMERx outputs 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timerexc: which timer to be exchange output
                only one can be selected which is shown as below:
      \arg         HRTIMER_OUTPUT_EXCHANGE_ST0: Slave_TIMER0 exchange output
      \arg         HRTIMER_OUTPUT_EXCHANGE_ST1: Slave_TIMER1 exchange output
      \arg         HRTIMER_OUTPUT_EXCHANGE_ST2: Slave_TIMER2 exchange output
      \arg         HRTIMER_OUTPUT_EXCHANGE_ST3: Slave_TIMER3 exchange output
      \arg         HRTIMER_OUTPUT_EXCHANGE_ST4: Slave_TIMER4 exchange output
      \arg         HRTIMER_OUTPUT_EXCHANGE_ST5: Slave_TIMER5 exchange output
      \arg         HRTIMER_OUTPUT_EXCHANGE_ST6: Slave_TIMER6 exchange output
      \arg         HRTIMER_OUTPUT_EXCHANGE_ST7: Slave_TIMER7 exchange output
    \param[out] none
    \retval     none
*/
void hrtimer_output_exchange(uint32_t hrtimer_periph, uint32_t timerexc)
{
    HRTIMER_CTL1(hrtimer_periph) |= timerexc;
}
/*!
    \brief      initialize waveform mode initialization parameters struct with a default value
    \param[in]  timerinitpara: HRTIMER waveform mode initialization parameters
    \param[out] none
    \retval     none
*/
void hrtimer_timerinit_struct_para_init(hrtimer_timerinit_parameter_struct* timerinit)
{
    timerinit->cnt_bunch = HRTIMER_TIMERBUNCHNMODE_MAINTAINCLOCK;
    timerinit->dac_trigger = HRTIMER_DAC_TRIGGER_NONE;
    timerinit->half_mode = HRTIMER_HALFMODE_DISABLED;
    timerinit->resynchronized_update = HRTIMER_RSYUPD_DISABLED;
    timerinit->alternate_mode = HRTIMER_ALTERNATE_MODE_DISABLED;   
    timerinit->repetition_update = HRTIMER_UPDATEONREPETITION_DISABLED;
    timerinit->reset_sync = HRTIMER_SYNCRESET_DISABLED;
    timerinit->shadow = HRTIMER_SHADOW_DISABLED;
    timerinit->start_sync = HRTIMER_SYNISTART_DISABLED;
    timerinit->update_selection = HRTIMER_MT_ST_UPDATE_SELECTION_INDEPENDENT;
}

/*!
    \brief      initialize a timer to work in waveform mode 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  timerinitpara: HRTIMER waveform mode initialization parameters
                  half_mode: HRTIMER_HALFMODE_DISABLED, HRTIMER_HALFMODE_ENABLED
                  alternate_mode: HRTIMER_ALTERNATE_MODE_DISABLED,HRTIMER_ALTERNATE_MODE_TRIPLE,HRTIMER_ALTERNATE_MODE_QUAD
                  start_sync: HRTIMER_SYNISTART_DISABLED, HRTIMER_SYNISTART_ENABLED
                  reset_sync: HRTIMER_SYNCRESET_DISABLED, HRTIMER_SYNCRESET_ENABLED
                  dac_trigger: HRTIMER_DAC_TRIGGER_NONE, HRTIMER_DAC_TRIGGER_DACTRIGy(y=0..2)
                  shadow: HRTIMER_SHADOW_DISABLED, HRTIMER_SHADOW_ENABLED
                  update_selection: HRTIMER_MT_ST_UPDATE_SELECTION_INDEPENDENT, for Master_TIMER and Slave_TIMER
                                    HRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE, for Master_TIMER and Slave_TIMER
                                    HRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE_UPDATE, for Master_TIMER and Slave_TIMER
                                    HRTIMER_ST_UPDATE_SELECTION_STXUPINy(y=0..2), for Slave_TIMER
                                    HRTIMER_ST_UPDATE_SELECTION_STXUPINy_UPDATE(y=0..2), for Slave_TIMER
                  cnt_bunch: HRTIMER_TIMERBUNCHNMODE_MAINTAINCLOCK, HRTIMER_TIMERBUNCHMODE_RESETCOUNTER
                  repetition_update: HRTIMER_UPDATEONREPETITION_DISABLED, HRTIMER_UPDATEONREPETITION_ENABLED
                  resynchronized_update:HRTIMER_RSYUPD_DISABLED,HRTIMER_RSYUPD_ENABLED
    \param[out] none
    \retval     none
*/
void hrtimer_timers_waveform_init(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_timerinit_parameter_struct* timerinitpara)
{
    if(HRTIMER_MASTER_TIMER == timer_id)
    {
        /* configure Master_TIMER in waveform mode */
        master_timer_waveform_config(hrtimer_periph, timerinitpara);
    }else{
        /* configure Slave_TIMER in waveform mode */
        slave_timer_waveform_config(hrtimer_periph, timer_id, timerinitpara);
    }
}

/*!
    \brief      initialize Slave_TIMER general behavior configuration struct with a default value
    \param[in]  timercfg: Slave_TIMER general behavior configuration struct
    \param[out] none
    \retval     none
*/
void hrtimer_timercfg_struct_para_init(hrtimer_timercfg_parameter_struct* timercgf)
{
    timercgf->balanced_mode = HRTIMER_STXBALANCEDMODE_DISABLED;
    timercgf->balanced_idle_automatic_resume = HRTIMER_BALANE_IDLE_AUTOMATIC_RESUME_DISABLE;
    timercgf->cnt_reset = HRTIMER_STXCNT_RESET_NONE;
    timercgf->deadtime_enable = HRTIMER_STXDEADTIME_DISABLED;
    timercgf->delayed_idle = HRTIMER_STXDELAYED_IDLE_DISABLED;
    timercgf->fault_enable = HRTIMER_STXFAULTENABLE_NONE;
    timercgf->fault_protect = HRTIMER_STXFAULT_PROTECT_READWRITE;
    timercgf->reset_update = HRTIMER_STXUPDATEONRESET_DISABLED;
    timercgf->update_source = HRTIMER_STXUPDATETRIGGER_NONE;
}

/*!
    \brief      configure the general behavior of a Slave_TIMER which work in waveform mode 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  timercfg: Slave_TIMER general behavior configuration struct
                  balanced_mode: HRTIMER_STXBALANCEDMODE_DISABLED, HRTIMER_STXBALANCEDMODE_ENABLED
                  balanced_idle_automatic_resume: HRTIMER_BALANE_IDLE_AUTOMATIC_RESUME_DISABLE,HRTIMER_BALANE_IDLE_AUTOMATIC_RESUME_ENABLE
                  fault_enable: HRTIMER_STXFAULTENABLE_NONE, HRTIMER_STXFAULTENABLE_FAULT0, HRTIMER_STXFAULTENABLE_FAULT1, HRTIMER_STXFAULTENABLE_FAULT2, HRTIMER_STXFAULTENABLE_FAULT3 ,HRTIMER_STXFAULTENABLE_FAULT4,
                                HRTIMER_STXFAULTENABLE_FAULT5, HRTIMER_STXFAULTENABLE_FAULT6, HRTIMER_STXFAULTENABLE_FAULT7
                  fault_protect: HRTIMER_STXFAULT_PROTECT_READWRITE, HRTIMER_STXFAULT_PROTECT_READONLY
                  deadtime_enable: HRTIMER_STXDEADTIME_DISABLED, HRTIMER_STXDEADTIME_ENABLED
                  delayed_idle: HRTIMER_STXDELAYED_IDLE_DISABLED,HRTIMER_STXDELAYED_IDLE_CH0_EEV57,HRTIMER_STXDELAYED_IDLE_CH1_EEV57,HRTIMER_STXDELAYED_IDLE_BOTH_EEV57,HRTIMER_STXDELAYED_IDLE_BALANCED_EEV57,
                                 HRTIMER_STXDELAYED_IDLE_CH0_DEEV68,HRTIMER_STXDELAYED_IDLE_CH1_DEEV68,HRTIMER_STXDELAYED_IDLE_BOTH_EEV68,HRTIMER_STXDELAYED_IDLE_BALANCED_EEV68
                  update_source: HRTIMER_STXUPDATETRIGGER_NONE, HRTIMER_STXUPDATETRIGGER_MASTER, HRTIMER_STXUPDATETRIGGER_STx(x=0..7)
                  cnt_reset: HRTIMER_STXCNT_RESET_NONE, HRTIMER_STXCNT_RESET_UPDATE, HRTIMER_STXCNT_RESET_CMP1, HRTIMER_STXCNT_RESET_CMP3, HRTIMER_STXCNT_RESET_MASTER_PER, HRTIMER_STXCNT_RESET_MASTER_CMPy(y=0..3),
                             HRTIMER_STXCNT_RESET_EEV_y(y=0..9), HRTIMER_STXCNT_RESET_OTHERx_CMPy(x=0..3, y=0,1,3)
                  reset_update: HRTIMER_STXUPDATEONRESET_DISABLED, HRTIMER_STXUPDATEONRESET_ENABLED
    \param[out] none
    \retval     none
*/
void hrtimer_slavetimer_waveform_config(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_timercfg_parameter_struct * timercfg)
{
    uint32_t stxctl0_reg;
    uint32_t stxfltctl_reg;
    uint32_t stxchoctl_reg;
    uint32_t stxcntrsta_reg;
    uint32_t stxactl_reg;

    /* get the value of registers */
    stxctl0_reg = HRTIMER_STXCTL0(hrtimer_periph, timer_id);
    stxfltctl_reg = HRTIMER_STXFLTCTL(hrtimer_periph, timer_id);
    stxchoctl_reg = HRTIMER_STXCHOCTL(hrtimer_periph, timer_id);
    stxactl_reg = HRTIMER_STXACTL(hrtimer_periph, timer_id);
    
    stxcntrsta_reg = HRTIMER_STXCNTRSTA(hrtimer_periph, timer_id);

    /* set the balanced mode */
    stxctl0_reg &= ~(HRTIMER_STXCTL0_BLNMEN);
    stxctl0_reg |= timercfg->balanced_mode;
  
    /* update event generated by reset event */
    stxctl0_reg &= ~(HRTIMER_STXCTL0_UPRST);
    stxctl0_reg |= timercfg->reset_update;
  
    /* set the timer update source */
    if(timercfg->update_source < HRTIMER_STXUPDATETRIGGER_ST6) {
        stxctl0_reg &= ~(STX_UPDATESOURCE_MASK0_5);
        stxactl_reg &= ~(STX_UPDATESOURCE_MASK6_7);
        stxctl0_reg |= timercfg->update_source;
    }else{
        stxctl0_reg &= ~(STX_UPDATESOURCE_MASK0_5);
        stxactl_reg &= ~(STX_UPDATESOURCE_MASK6_7);
        stxactl_reg |= (timercfg->update_source & 0x7FFFFFFFU);
    }
    /* enable/disable the fault channel (at Slave_TIMER level) */
    stxfltctl_reg &= ~(STX_FAULTCH_MASK);
    stxfltctl_reg |= (timercfg->fault_enable & STX_FAULTCH_MASK);
  
    /* protect fault enable (at Slave_TIMER level) */
    stxfltctl_reg &= ~(HRTIMER_STXFLTCTL_FLTENPROT);
    stxfltctl_reg |= timercfg->fault_protect;
  
    /* enable/disable dead time insertion (at Slave_TIMER level) */
    stxchoctl_reg &= ~(HRTIMER_STXCHOCTL_DTEN);
    stxchoctl_reg |= timercfg->deadtime_enable;

    /* enable/disable delayed IDLE (at Slave_TIMER level) */
    stxchoctl_reg &= ~(HRTIMER_STXCHOCTL_DLYISCH| HRTIMER_STXCHOCTL_DLYISMEN);
    stxchoctl_reg |= timercfg->delayed_idle;
    
    /* balanced idle automatic resumption (at Slave_TIMER level) */
    stxchoctl_reg &= ~(HRTIMER_STXCHOCTL_BALIAR);
    stxchoctl_reg |= timercfg->balanced_idle_automatic_resume;
  
    /* configure the Slave_TIMER counter reset event in HRTIMER_STXCNTRST register */
    HRTIMER_STXCNTRST(hrtimer_periph, timer_id) = (uint32_t)(timercfg->cnt_reset);
    /* configure the Slave_TIMER counter reset event in HRTIMER_STXCNTRSTA register */
    stxcntrsta_reg &= ~0x0000007FU;
    stxcntrsta_reg |= (uint32_t)((timercfg->cnt_reset) >> 32U);
    HRTIMER_STXCNTRSTA(hrtimer_periph, timer_id) = stxcntrsta_reg;

    HRTIMER_STXCTL0(hrtimer_periph, timer_id) = stxctl0_reg;
    HRTIMER_STXFLTCTL(hrtimer_periph, timer_id) = stxfltctl_reg;
    HRTIMER_STXCHOCTL(hrtimer_periph, timer_id) = stxchoctl_reg;
    HRTIMER_STXACTL(hrtimer_periph, timer_id) = stxactl_reg;
}


/*!
    \brief      initialize compare unit configuration struct with a default value
    \param[in]  cmpcfg: compare unit configuration struct definitions
    \param[out] none
    \retval     none
*/
void hrtimer_comparecfg_struct_para_init(hrtimer_comparecfg_parameter_struct* comparecfg)
{
    comparecfg->compare_value = 0x0000U;
    comparecfg->delayed_mode = HRTIMER_DELAYEDMODE_DISABLE;
    comparecfg->timeout_value = 0x0U;
    comparecfg->trigger_half = HRTIMER_TRGHALFM_DISABLE;
    comparecfg->immediately_update_cmp0 = HRTIMER_IMMEDIATELY_UPDATE_CMP0_DISABLE;
    comparecfg->immediately_update_cmp2 = HRTIMER_IMMEDIATELY_UPDATE_CMP2_DISABLE;
    
}

/*!
    \brief      configure the compare unit of a Slave_TIMER which work in waveform mode 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  comparex: HRTIMER_COMPAREy(y=0..3)
    \param[in]  cmpcfg: compare unit configuration struct definitions
                  compare_value: min value: 3*tHRTIMER_CK clock, max value: 0xFFFF �C (1*tHRTIMER_CK)
                  delayed_mode: HRTIMER_DELAYEDMODE_DISABLE, HRTIMER_DELAYEDMODE_NOTIMEOUT, HRTIMER_DELAYEDMODE_TIMEOUTCMP0, HRTIMER_DELAYEDMODE_TIMEOUTCMP2
                  timeout_value: 0x0000~((timeout_value + compare_value) < 0xFFFF)
                  trigger_half: HRTIMER_TRGHALFM_DISABLE,HRTIMER_TRGHALFM_ENABLE
                  immediately_update_cmp0: HRTIMER_IMMEDIATELY_UPDATE_CMP0_DISABLE,HRTIMER_IMMEDIATELY_UPDATE_CMP0_ENABLE
                  immediately_update_cmp2: HRTIMER_IMMEDIATELY_UPDATE_CMP2_DISABLE,HRTIMER_IMMEDIATELY_UPDATE_CMP2_ENABLE
    \param[out] none
    \retval     none
*/
void hrtimer_slavetimer_waveform_compare_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t comparex, hrtimer_comparecfg_parameter_struct* cmpcfg)
{
    uint32_t stxctl0_reg;
    uint32_t stxctl1_reg;
    
    /* configure the compare unit */
    switch (comparex)
    {
        case HRTIMER_COMPARE0:
        {
            /* set the compare value */
            HRTIMER_STXCMP0V(hrtimer_periph, timer_id) = cmpcfg->compare_value;
            /* configure immediately update of compare 0 */
            stxctl1_reg = HRTIMER_STXCTL1(hrtimer_periph, timer_id);
            stxctl1_reg &= ~HRTIMER_STXCTL1_IMUPD0V;
            stxctl1_reg |= cmpcfg->immediately_update_cmp0;
            HRTIMER_STXCTL1(hrtimer_periph, timer_id) = stxctl1_reg;
        }
        break;

        case HRTIMER_COMPARE1:
        {
            /* set the compare value */
            HRTIMER_STXCMP1V(hrtimer_periph, timer_id) = cmpcfg->compare_value;
            /* configure trigger half */
            stxctl1_reg = HRTIMER_STXCTL1(hrtimer_periph, timer_id);
            stxctl1_reg &= ~HRTIMER_STXCTL1_TRGHALFM;
            stxctl1_reg |= cmpcfg->trigger_half;
            HRTIMER_STXCTL1(hrtimer_periph, timer_id) = stxctl1_reg;

            if(HRTIMER_DELAYEDMODE_DISABLE != cmpcfg->delayed_mode){
                /* configure delayed mode */
                stxctl0_reg = HRTIMER_STXCTL0(hrtimer_periph, timer_id);
                stxctl0_reg &= ~HRTIMER_STXCTL0_DELCMP1M;
                stxctl0_reg |= cmpcfg->delayed_mode;
                HRTIMER_STXCTL0(hrtimer_periph, timer_id) = stxctl0_reg;
                /* set the compare value for timeout compare unit */
                if(HRTIMER_DELAYEDMODE_TIMEOUTCMP0 == cmpcfg->delayed_mode){
                    HRTIMER_STXCMP0V(hrtimer_periph, timer_id) = cmpcfg->timeout_value;
                }else if(HRTIMER_DELAYEDMODE_TIMEOUTCMP2 == cmpcfg->delayed_mode){
                    HRTIMER_STXCMP2V(hrtimer_periph, timer_id) = cmpcfg->timeout_value;
                }else{
                }
            }
        }
        break;

        case HRTIMER_COMPARE2:
        {
            /* set the compare value */
            HRTIMER_STXCMP2V(hrtimer_periph, timer_id) = cmpcfg->compare_value;
            /* configure immediately update of compare 2 */
            stxctl1_reg = HRTIMER_STXCTL1(hrtimer_periph, timer_id);
            stxctl1_reg &= ~HRTIMER_STXCTL1_IMUPD2V;
            stxctl1_reg |= cmpcfg->immediately_update_cmp2;
            HRTIMER_STXCTL1(hrtimer_periph, timer_id) = stxctl1_reg;
        }
        break;
        case HRTIMER_COMPARE3:
        {
            /* set the compare value */
            HRTIMER_STXCMP3V(hrtimer_periph, timer_id) = cmpcfg->compare_value;
          
            if(HRTIMER_DELAYEDMODE_DISABLE != cmpcfg->delayed_mode){
                /* configure delayed mode */
                stxctl0_reg = HRTIMER_STXCTL0(hrtimer_periph, timer_id);
                stxctl0_reg &= ~HRTIMER_STXCTL0_DELCMP3M;
                stxctl0_reg |= (cmpcfg->delayed_mode << 2);
                HRTIMER_STXCTL0(hrtimer_periph, timer_id) = stxctl0_reg;
                
                /* set the compare value for timeout compare unit */
                if(HRTIMER_DELAYEDMODE_TIMEOUTCMP0 == cmpcfg->delayed_mode){
                  HRTIMER_STXCMP0V(hrtimer_periph, timer_id) = cmpcfg->timeout_value;
                }else if(HRTIMER_DELAYEDMODE_TIMEOUTCMP2 == cmpcfg->delayed_mode){
                  HRTIMER_STXCMP2V(hrtimer_periph, timer_id) = cmpcfg->timeout_value;
                }else{
                }
            }
        }
        break;

        default:
        break;  
    }
}

/*!
    \brief      initialize channel output configuration struct with a default value 
    \param[in]  channelcfg: channel output configuration struct definitions
    \param[out] none
    \retval     none
*/
void hrtimer_channel_outputcfg_struct_para_init(hrtimer_channel_outputcfg_parameter_struct * channelcfg)
{
    channelcfg->carrier_mode = HRTIMER_CHANNEL_CARRIER_DISABLED;
    channelcfg->deadtime_bunch = HRTIMER_CHANNEL_BUNCH_ENTRY_REGULAR;
    channelcfg->fault_state = HRTIMER_CHANNEL_FAULTSTATE_NONE;
    channelcfg->idle_bunch = HRTIMER_CHANNEL_BUNCH_IDLE_DISABLE;
    channelcfg->idle_state = HRTIMER_CHANNEL_IDLESTATE_INACTIVE;
    channelcfg->polarity = HRTIMER_CHANNEL_POLARITY_HIGH;
    channelcfg->reset_request = HRTIMER_CHANNEL_RESET_NONE;
    channelcfg->set_request = HRTIMER_CHANNEL_SET_NONE;
}

/*!
    \brief      configure the channel output of a Slave_TIMER work in waveform mode 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  channel: HRTIMER_STx_CHy(x=0..7,y=0,1)
    \param[in]  channelcfg: channel output configuration struct definitions
                  polarity: HRTIMER_CHANNEL_POLARITY_HIGH, HRTIMER_CHANNEL_POLARITY_LOW
                  set_request: HRTIMER_CHANNEL_SET_NONE, HRTIMER_CHANNEL_SET_RSTSYNI, HRTIMER_CHANNEL_SET_PER, HRTIMER_CHANNEL_SET_CMPy(y=0..3),
                               HRTIMER_CHANNEL_SET_MTPER, HRTIMER_CHANNEL_SET_MTCMPy(y=0..3), HRTIMER_CHANNEL_SET_STEVy(y=0..8), HRTIMER_CHANNELx_SET_STEVy(x=0,1,y=9,10),
                               HRTIMER_CHANNEL_SET_EXEVy(y=0..9), HRTIMER_CHANNEL_SET_UPDATE, HRTIMER_CHANNELx_SET_STCNTRST(x=0,1)
                  reset_request: HRTIMER_CHANNEL_RESET_NONE, HRTIMER_CHANNEL_RESET_RSTSYNI, HRTIMER_CHANNEL_RESET_PER, HRTIMER_CHANNEL_RESET_CMPy(y=0..3),
                               HRTIMER_CHANNEL_RESET_MTPER, HRTIMER_CHANNEL_RESET_MTCMPy(y=0..3), HRTIMER_CHANNEL_RESET_STEVy(y=0..8), HRTIMER_CHANNELx_RESET_STEVy(x=0,1,y=9,10),
                               HRTIMER_CHANNEL_RESET_EXEVy(y=0..9), HRTIMER_CHANNEL_RESET_UPDATE, HRTIMER_CHANNELx_RESET_STCNTRST(x=0,1)
                  idle_bunch: HRTIMER_CHANNEL_BUNCH_IDLE_DISABLE, HRTIMER_CHANNEL_BUNCH_IDLE_ENABLE
                  idle_state: HRTIMER_CHANNEL_IDLESTATE_INACTIVE, HRTIMER_CHANNEL_IDLESTATE_ACTIVE
                  fault_state: HRTIMER_CHANNEL_FAULTSTATE_NONE, HRTIMER_CHANNEL_FAULTSTATE_ACTIVE, HRTIMER_CHANNEL_FAULTSTATE_INACTIVE, HRTIMER_CHANNEL_FAULTSTATE_HIGHZ
                  carrier_mode: HRTIMER_CHANNEL_CARRIER_DISABLED, HRTIMER_CHANNEL_CARRIER_ENABLED
                  deadtime_bunch: HRTIMER_CHANNEL_BUNCH_ENTRY_REGULAR, HRTIMER_CHANNEL_BUNCH_ENTRY_DEADTIME
    \param[out] none
    \retval     none
*/
void hrtimer_slavetimer_waveform_channel_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t channel, hrtimer_channel_outputcfg_parameter_struct * channelcfg)
{
    channel_output_config(hrtimer_periph, timer_id, channel, channelcfg);
}

/*!
    \brief      software generates channel "set request" or "reset request"
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  channel: HRTIMER_STx_CHy(x=0..7,y=0,1)
    \param[in]  request: "set request" or "reset request"
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_CHANNEL_SOFTWARE_SET: software event cannot generate request
      \arg         HRTIMER_CHANNEL_SOFTWARE_RESET: software event can generate request
    \param[out] none
    \retval     none
*/
void hrtimer_slavetimer_waveform_channel_software_request(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t channel, uint32_t request)
{
    /* configure the output set/reset crossbar */
    switch (channel)
    {
        /* configure the channel 0 output set/reset crossbar */
        case HRTIMER_ST0_CH0:
        case HRTIMER_ST1_CH0:
        case HRTIMER_ST2_CH0:
        case HRTIMER_ST3_CH0:
        case HRTIMER_ST4_CH0:
        case HRTIMER_ST5_CH0:
        case HRTIMER_ST6_CH0:
        case HRTIMER_ST7_CH0:
        {
            if(HRTIMER_CHANNEL_SOFTWARE_SET == request){
                /* software generates channel "set request" */
                HRTIMER_STXCH0SET(hrtimer_periph, timer_id) |= HRTIMER_STXCH0SET_CH0SSEV;
            }else{
                /* software generates channel "reset request" */
                HRTIMER_STXCH0RST(hrtimer_periph, timer_id) |= HRTIMER_STXCH0RST_CH0RSSEV;
            }
        }
        break;
        /* configure the channel 1 output set/reset crossbar */
        case HRTIMER_ST0_CH1:
        case HRTIMER_ST1_CH1:
        case HRTIMER_ST2_CH1:
        case HRTIMER_ST3_CH1:
        case HRTIMER_ST4_CH1:
        case HRTIMER_ST5_CH1:
        case HRTIMER_ST6_CH1:
        case HRTIMER_ST7_CH1:
        {
            if(HRTIMER_CHANNEL_SOFTWARE_SET == request){
                /* software generates channel "set request" */
                HRTIMER_STXCH1SET(hrtimer_periph, timer_id) |= HRTIMER_STXCH1SET_CH1SSEV;
            }else{
                /* software generates channel "reset request" */
                HRTIMER_STXCH1RST(hrtimer_periph, timer_id) |= HRTIMER_STXCH1RST_CH1RSSEV;
            }
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      get Slave_TIMER channel output level
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  channel: HRTIMER_STx_CHy(x=0..7,y=0,1)
    \param[out] none
    \retval     channel output level
*/
uint32_t hrtimer_slavetimer_waveform_channel_output_level_get(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t channel)
{
    uint32_t output_level = HRTIMER_CHANNEL_OUTPUT_INACTIVE;
    
    switch (channel)
    {
        /* get Slave_TIMER channel 0 output level */
        case HRTIMER_ST0_CH0:
        case HRTIMER_ST1_CH0:
        case HRTIMER_ST2_CH0:
        case HRTIMER_ST3_CH0:
        case HRTIMER_ST4_CH0:
        case HRTIMER_ST5_CH0:
        case HRTIMER_ST6_CH0:
        case HRTIMER_ST7_CH0:
        {
            if(RESET != (HRTIMER_STXINTF(hrtimer_periph, timer_id) & HRTIMER_STXINTF_CH0F)){
                output_level = HRTIMER_CHANNEL_OUTPUT_ACTIVE;
            }else{
                output_level = HRTIMER_CHANNEL_OUTPUT_INACTIVE;
            }
        }
        break;
        /* get Slave_TIMER channel 1 output level */
        case HRTIMER_ST0_CH1:
        case HRTIMER_ST1_CH1:
        case HRTIMER_ST2_CH1:
        case HRTIMER_ST3_CH1:
        case HRTIMER_ST4_CH1:
        case HRTIMER_ST5_CH1:
        case HRTIMER_ST6_CH1:
        case HRTIMER_ST7_CH1:
        {
            if(RESET != (HRTIMER_STXINTF(hrtimer_periph, timer_id) & HRTIMER_STXINTF_CH1F)){
                output_level = HRTIMER_CHANNEL_OUTPUT_ACTIVE;
            }else{
                output_level = HRTIMER_CHANNEL_OUTPUT_INACTIVE;
            }
        }
        break;
        default:
        break;
    }
    return output_level;
}

/*!
    \brief      get Slave_TIMER channel run state
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  channel: HRTIMER_STx_CHy(x=0..7,y=0,1)
    \param[out] none
    \retval     channel state
*/
uint32_t hrtimer_slavetimer_waveform_channel_state_get(uint32_t hrtimer_periph, uint32_t channel)
{
    uint32_t enbit = 0U;
    uint32_t state = HRTIMER_CHANNEL_STATE_IDLE;
    
    switch (channel)
    {
        /* get Slave_TIMER0 channel 0 run state */
        case HRTIMER_ST0_CH0:
            enbit = HRTIMER_CHOUTEN_ST0CH0EN;
        break;
        /* get Slave_TIMER0 channel 1 run state */
        case HRTIMER_ST0_CH1:
            enbit = HRTIMER_CHOUTEN_ST0CH1EN;
        break;
        /* get Slave_TIMER1 channel 0 run state */
        case HRTIMER_ST1_CH0:
            enbit = HRTIMER_CHOUTEN_ST1CH0EN;
        break;
        /* get Slave_TIMER1 channel 1 run state */
        case HRTIMER_ST1_CH1:
            enbit = HRTIMER_CHOUTEN_ST1CH1EN;
        break;
        /* get Slave_TIMER2 channel 0 run state */
        case HRTIMER_ST2_CH0:
            enbit = HRTIMER_CHOUTEN_ST2CH0EN;
        break;
        /* get Slave_TIMER2 channel 1 run state */
        case HRTIMER_ST2_CH1:
            enbit = HRTIMER_CHOUTEN_ST2CH1EN;
        break;
        /* get Slave_TIMER3 channel 0 run state */
        case HRTIMER_ST3_CH0:
            enbit = HRTIMER_CHOUTEN_ST3CH0EN;
        break;
        /* get Slave_TIMER3 channel 1 run state */
        case HRTIMER_ST3_CH1:
            enbit = HRTIMER_CHOUTEN_ST3CH1EN;
        break;
        /* get Slave_TIMER4 channel 0 run state */
        case HRTIMER_ST4_CH0:
            enbit = HRTIMER_CHOUTEN_ST4CH0EN;
        break;
        /* get Slave_TIMER4 channel 1 run state */
        case HRTIMER_ST4_CH1:
            enbit = HRTIMER_CHOUTEN_ST4CH1EN;
        break;
        /* get Slave_TIMER5 channel 0 run state */
        case HRTIMER_ST5_CH0:
            enbit = HRTIMER_CHOUTEN_ST5CH0EN;
        break;
        /* get Slave_TIMER5 channel 1 run state */
        case HRTIMER_ST5_CH1:
            enbit = HRTIMER_CHOUTEN_ST5CH1EN;
        break;
        /* get Slave_TIMER6 channel 0 run state */
        case HRTIMER_ST6_CH0:
            enbit = HRTIMER_CHOUTEN_ST6CH0EN;
        break;
        /* get Slave_TIMER6 channel 1 run state */
        case HRTIMER_ST6_CH1:
            enbit = HRTIMER_CHOUTEN_ST6CH1EN;
        break;
        /* get Slave_TIMER7 channel 0 run state */
        case HRTIMER_ST7_CH0:
            enbit = HRTIMER_CHOUTEN_ST7CH0EN;
        break;
        /* get Slave_TIMER7 channel 1 run state */
        case HRTIMER_ST7_CH1:
            enbit = HRTIMER_CHOUTEN_ST7CH1EN;
        break;
        default:
        break;
    }
    if ( RESET != (HRTIMER_CHOUTEN(hrtimer_periph) & enbit)){
        /* Run state*/
        state = HRTIMER_CHANNEL_STATE_RUN;
    }else{
        if (RESET != (HRTIMER_CHOUTDISF(hrtimer_periph) & enbit)){
            /* Fault state */ 
            state = HRTIMER_CHANNEL_STATE_FAULT;
        }else{
            /* Idle state */
            state = HRTIMER_CHANNEL_STATE_IDLE;
        }
    }
    return state;
}

/*!
    \brief      initialize dead time configuration struct with a default value
    \param[in]  dtcfg: dead time configuration struct
    \param[out] none
    \retval     none
*/
void hrtimer_deadtimercfg_struct_para_init(hrtimer_deadtimecfg_parameter_struct * dtcfg)
{
    dtcfg->fallingsign_protect = HRTIMER_DEADTIME_FALLINGSIGN_PROTECT_DISABLE;
    dtcfg->falling_protect = HRTIMER_DEADTIME_FALLING_PROTECT_DISABLE;
    dtcfg->falling_sign = HRTIMER_DEADTIME_FALLINGSIGN_POSITIVE;
    dtcfg->falling_value = 0U;
    dtcfg->prescaler = HRTIMER_DEADTIME_PRESCALER_MUL8;
    dtcfg->risingsign_protect = HRTIMER_DEADTIME_RISINGSIGN_PROTECT_DISABLE;
    dtcfg->rising_protect = HRTIMER_DEADTIME_RISING_PROTECT_DISABLE;
    dtcfg->rising_sign = HRTIMER_DEADTIME_RISINGSIGN_POSITIVE;
    dtcfg->rising_value = 0U;
}

/*!
    \brief      configure the dead time for Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  dtcfg: dead time configuration struct
                  prescaler: HRTIMER_DEADTIME_PRESCALER_MULy(y=32,16,8,4,2), HRTIMER_DEADTIME_PRESCALER_DIVy(y=1,2,4,8,16)
                  rising_value: 0x0000~0x1FF
                  rising_sign: HRTIMER_DEADTIME_RISINGSIGN_POSITIVE, HRTIMER_DEADTIME_RISINGSIGN_NEGATIVE
                  rising_protect: HRTIMER_DEADTIME_RISING_PROTECT_DISABLE, HRTIMER_DEADTIME_RISING_PROTECT_ENABLE
                  risingsign_protect: HRTIMER_DEADTIME_RISINGSIGN_PROTECT_DISABLE, HRTIMER_DEADTIME_RISINGSIGN_PROTECT_ENABLE
                  falling_value: 0x0000~0x1FF
                  falling_sign: HRTIMER_DEADTIME_FALLINGSIGN_POSITIVE, HRTIMER_DEADTIME_FALLINGSIGN_NEGATIVE
                  falling_protect: HRTIMER_DEADTIME_FALLING_PROTECT_DISABLE, HRTIMER_DEADTIME_FALLING_PROTECT_ENABLE
                  fallingsign_protect: HRTIMER_DEADTIME_FALLINGSIGN_PROTECT_DISABLE, HRTIMER_DEADTIME_FALLINGSIGN_PROTECT_ENABLE
    \param[out] none
    \retval     none
*/
void hrtimer_slavetimer_deadtime_config(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_deadtimecfg_parameter_struct* dtcfg)
{
    uint32_t dtctl_reg;
    uint32_t stxactl;

    dtctl_reg = HRTIMER_STXDTCTL(hrtimer_periph, timer_id);
    stxactl = HRTIMER_STXACTL(hrtimer_periph, timer_id);
     
    /* clear dead time configuration */
    dtctl_reg &= ~(HRTIMER_STXDTCTL_DTRCFG8_0 | HRTIMER_STXDTCTL_DTRS | HRTIMER_STXDTCTL_DTGCKDIV |
                 HRTIMER_STXDTCTL_DTRSPROT | HRTIMER_STXDTCTL_DTRSVPROT | HRTIMER_STXDTCTL_DTFCFG8_0 |
                 HRTIMER_STXDTCTL_DTFS | HRTIMER_STXDTCTL_DTFSPROT | HRTIMER_STXDTCTL_DTFSVPROT);
    stxactl &= ~(HRTIMER_STXACTL_DTRCFG15_9 | HRTIMER_STXACTL_DTFCFG15_9);
  
    /* set dead time configuration */
    dtctl_reg |= (dtcfg->prescaler << 10);
    dtctl_reg |= ((dtcfg->rising_value) & HRTIMER_STXDTCTL_DTRCFG8_0);
    stxactl |= (((dtcfg->rising_value) & (~HRTIMER_STXDTCTL_DTRCFG8_0)));
    dtctl_reg |= dtcfg->rising_sign;
    dtctl_reg |= dtcfg->risingsign_protect;
    dtctl_reg |= dtcfg->rising_protect;
    dtctl_reg |= (((dtcfg->falling_value) & HRTIMER_STXDTCTL_DTRCFG8_0) << 16);
    stxactl |= ((dtcfg->falling_value) & (~HRTIMER_STXDTCTL_DTRCFG8_0)) << 16;
    dtctl_reg |= dtcfg->falling_sign;
    dtctl_reg |= dtcfg->fallingsign_protect;
    dtctl_reg |= dtcfg->falling_protect;
    
    HRTIMER_STXACTL(hrtimer_periph, timer_id) = stxactl;
    HRTIMER_STXDTCTL(hrtimer_periph, timer_id) = dtctl_reg;
}

/*!
    \brief      initialize carrier signal configuration struct with a default value
    \param[in]  carriercfg: carrier signal configuration struct
    \param[out] none
    \retval     none
*/
void hrtimer_carriersignalcfg_struct_para_init(hrtimer_carriersignalcfg_parameter_struct* carriercfg)
{
    carriercfg->duty_cycle = 0U;
    carriercfg->first_pulse = 0U;
    carriercfg->period = 0U;
}

/*!
    \brief      configure the carrier signal mode for Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  carriercfg: carrier signal configuration struct
                  period: 0x0~0xF. specifies carrier signal period: (period + 1) * 16 * tHRTIMER_CK
                  duty_cycle: 0x0~0x7. specifies Carrier signal duty cycle: duty_cycle/8
                  first_pulse: 0x0~0xF. specifies first carrier-signal pulse width: (first_pulse+1) * 16 * tHRTIMER_CK
    \param[out] none
    \retval     none
*/
void hrtimer_slavetimer_carriersignal_config(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_carriersignalcfg_parameter_struct* carriercfg)
{
    uint32_t csctl_reg;
  
    csctl_reg = HRTIMER_STXCSCTL(hrtimer_periph, timer_id);
     
    /* clear timer chopper mode configuration */
    csctl_reg &= ~(HRTIMER_STXCSCTL_CSPRD | HRTIMER_STXCSCTL_CSDTY | HRTIMER_STXCSCTL_CSFSTPW);
  
    /* set timer chopper mode configuration */
    csctl_reg |= carriercfg->period;
    csctl_reg |= (carriercfg->duty_cycle << 4);
    csctl_reg |= (carriercfg->first_pulse << 7);
    
    HRTIMER_STXCSCTL(hrtimer_periph, timer_id) = csctl_reg;
}

/*!
    \brief      enable a output channel
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  chid: specify the channel to configure
                only one can be selected which is shown as below:
      \arg          HRTIMER_ST0_CH0: ST0CH0_O output channel
      \arg          HRTIMER_ST0_CH1: ST0CH1_O output channel
      \arg          HRTIMER_ST1_CH0: ST1CH0_O output channel
      \arg          HRTIMER_ST1_CH1: ST1CH1_O output channel
      \arg          HRTIMER_ST2_CH0: ST2CH0_O output channel
      \arg          HRTIMER_ST2_CH1: ST2CH1_O output channel
      \arg          HRTIMER_ST3_CH0: ST3CH0_O output channel
      \arg          HRTIMER_ST3_CH1: ST3CH1_O output channel
      \arg          HRTIMER_ST4_CH0: ST4CH0_O output channel
      \arg          HRTIMER_ST4_CH1: ST4CH1_O output channel
      \arg          HRTIMER_ST5_CH0: ST5CH0_O output channel
      \arg          HRTIMER_ST5_CH1: ST5CH1_O output channel
      \arg          HRTIMER_ST6_CH0: ST6CH0_O output channel
      \arg          HRTIMER_ST6_CH1: ST6CH1_O output channel
      \arg          HRTIMER_ST7_CH0: ST7CH0_O output channel
      \arg          HRTIMER_ST7_CH1: ST7CH1_O output channel
    \param[out] none
    \retval     none
*/
void hrtimer_output_channel_enable(uint32_t hrtimer_periph, uint32_t chid)
{
    HRTIMER_CHOUTEN(hrtimer_periph) = chid;
}

/*!
    \brief      disable a output channel
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  chid: specify the channel to configure
                only one can be selected which is shown as below:
      \arg          HRTIMER_ST0_CH0: ST0CH0_O output channel
      \arg          HRTIMER_ST0_CH1: ST0CH1_O output channel
      \arg          HRTIMER_ST1_CH0: ST1CH0_O output channel
      \arg          HRTIMER_ST1_CH1: ST1CH1_O output channel
      \arg          HRTIMER_ST2_CH0: ST2CH0_O output channel
      \arg          HRTIMER_ST2_CH1: ST2CH1_O output channel
      \arg          HRTIMER_ST3_CH0: ST3CH0_O output channel
      \arg          HRTIMER_ST3_CH1: ST3CH1_O output channel
      \arg          HRTIMER_ST4_CH0: ST4CH0_O output channel
      \arg          HRTIMER_ST4_CH1: ST4CH1_O output channel
      \arg          HRTIMER_ST5_CH0: ST5CH0_O output channel
      \arg          HRTIMER_ST5_CH1: ST5CH1_O output channel
      \arg          HRTIMER_ST6_CH0: ST6CH0_O output channel
      \arg          HRTIMER_ST6_CH1: ST6CH1_O output channel
      \arg          HRTIMER_ST7_CH0: ST7CH0_O output channel
      \arg          HRTIMER_ST7_CH1: ST7CH1_O output channel
    \param[out] none
    \retval     none
*/
void hrtimer_output_channel_disable(uint32_t hrtimer_periph, uint32_t chid)
{
    HRTIMER_CHOUTDIS(hrtimer_periph) = chid;
}

/*!
    \brief      configure the compare value in Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  comparex: HRTIMER_COMPAREy(y=0..3), HRTIMER_COMPARE0_COMPOSITE
    \param[in]  cmpvalue:  min value: 3 tHRTIMER_CK clock, max value: 0xFFFF - (1 tHRTIMER_CK)
    \param[out] none
    \retval     none
*/
void hrtimer_slavetimer_compare_value_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t comparex, uint32_t cmpvalue)
{
    /* configure the compare unit */
    switch (comparex)
    {
        case HRTIMER_COMPARE0:
        {
            /* set the compare 0 value */
            HRTIMER_STXCMP0V(hrtimer_periph, timer_id) = cmpvalue;
        }
        break;
        case HRTIMER_COMPARE1:
        {
            /* set the compare 1 value */
            HRTIMER_STXCMP1V(hrtimer_periph, timer_id) = cmpvalue;
        }
        break;
        case HRTIMER_COMPARE2:
        {
            /* set the compare 2 value */
            HRTIMER_STXCMP2V(hrtimer_periph, timer_id) = cmpvalue;
        }
        break;
        case HRTIMER_COMPARE3:
        {
            /* set the compare 3 value */
            HRTIMER_STXCMP3V(hrtimer_periph, timer_id) = cmpvalue;
        }
        break;
        case HRTIMER_COMPARE0_COMPOSITE:
        {
            /* set the compare 0 composite value */
            HRTIMER_STXCMP0CP(hrtimer_periph, timer_id) = cmpvalue;
        }
        break;
        default:
        break;
    }  
}

/*!
    \brief      get the compare value in Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  comparex: HRTIMER_COMPAREy(y=0..3), HRTIMER_COMPARE0_COMPOSITE
    \param[out] none
    \retval     the compare value
*/
uint32_t hrtimer_slavetimer_compare_value_get(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t comparex)
{
    uint32_t cmpval = 0U;
    /* configure the compare unit */
    switch (comparex)
    {
        case HRTIMER_COMPARE0:
        {
            /* get the compare 0 value */
            cmpval = HRTIMER_STXCMP0V(hrtimer_periph, timer_id);
        }
        break;
        case HRTIMER_COMPARE1:
        {
            /* get the compare 1 value */
            cmpval = HRTIMER_STXCMP1V(hrtimer_periph, timer_id);
        }
        break;
        case HRTIMER_COMPARE2:
        {
            /* get the compare 2 value */
            cmpval = HRTIMER_STXCMP2V(hrtimer_periph, timer_id);
        }
        break;
        case HRTIMER_COMPARE3:
        {
            /* get the compare 3 value */
            cmpval = HRTIMER_STXCMP3V(hrtimer_periph, timer_id);
        }
        break;
        case HRTIMER_COMPARE0_COMPOSITE:
        {
            /* get the compare 0 composite value */
            cmpval = HRTIMER_STXCMP0CP(hrtimer_periph, timer_id);
        }
        break;
        default:
        break;
    }  
    return cmpval;
}

/*!
    \brief      configure the compare value in Master_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  comparex: HRTIMER_COMPAREy(y=0..3)
    \param[in]  cmpvalue: min value: 3*tHRTIMER_CK clock, max value: 0xFFFF - (1*tHRTIMER_CK)
    \param[out] none
    \retval     none
*/
void hrtimer_mastertimer_compare_value_config(uint32_t hrtimer_periph, uint32_t comparex, uint32_t cmpvalue)
{
    /* configure the compare unit */
    switch (comparex)
    {
        case HRTIMER_COMPARE0:
        {
            /* set the compare 0 value */
            HRTIMER_MTCMP0V(hrtimer_periph) = cmpvalue;
        }
        break;
        case HRTIMER_COMPARE1:
        {
            /* set the compare 1 value */
            HRTIMER_MTCMP1V(hrtimer_periph) = cmpvalue;
        }
        break;
        case HRTIMER_COMPARE2:
        {
            /* set the compare 2 value */
            HRTIMER_MTCMP2V(hrtimer_periph) = cmpvalue;
        }
        break;
        case HRTIMER_COMPARE3:
        {
            /* set the compare 3 value */
            HRTIMER_MTCMP3V(hrtimer_periph) = cmpvalue;
        }
        break;
        default:
        break;
    }  
}

/*!
    \brief      get the compare value in Master_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  comparex: HRTIMER_COMPAREy(y=0..3)
    \param[out] none
    \retval     the compare value
*/
uint32_t hrtimer_mastertimer_compare_value_get(uint32_t hrtimer_periph, uint32_t comparex)
{
    uint32_t cmpval = 0U;
    switch (comparex)
    {
        case HRTIMER_COMPARE0:
        {
            /* get the compare 0 value */
            cmpval = HRTIMER_MTCMP0V(hrtimer_periph);
        }
        break;
        case HRTIMER_COMPARE1:
        {
            /* get the compare 1 value */
            cmpval = HRTIMER_MTCMP1V(hrtimer_periph);
        }
        break;
        case HRTIMER_COMPARE2:
        {
            /* get the compare 2 value */
            cmpval = HRTIMER_MTCMP2V(hrtimer_periph);
        }
        break;
        case HRTIMER_COMPARE3:
        {
            /* get the compare 3 value */
            cmpval = HRTIMER_MTCMP3V(hrtimer_periph);
        }
        break;
        default:
        break;
    }  
    return cmpval;
}

/*!
    \brief      configure the counter value in Master_TIMER and Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  cntvalue: min value: 3*tHRTIMER_CK clock, max value: 0xFFFF - (1*tHRTIMER_CK)
    \param[out] none
    \retval     none
*/
void hrtimer_timers_counter_value_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t cntvalue)
{
    /* configure the counter */
    switch (timer_id)
    {
        case HRTIMER_MASTER_TIMER:
        {
            if(RESET == (HRTIMER_MTCTL0(hrtimer_periph) & HRTIMER_MTCTL0_MTCEN)){
                /* set the Master_TIMER counter value */
                HRTIMER_MTCNT(hrtimer_periph) = cntvalue;
            }
        }
        break;
        case HRTIMER_SLAVE_TIMER0:
        {
            if(RESET == (HRTIMER_MTCTL0(hrtimer_periph) & HRTIMER_MTCTL0_ST0CEN)){
                /* set the Slave_TIMER0 compare value */
                HRTIMER_STXCNT(hrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        case HRTIMER_SLAVE_TIMER1:
        {
            if(RESET == (HRTIMER_MTCTL0(hrtimer_periph) & HRTIMER_MTCTL0_ST1CEN)){
                /* set the Slave_TIMER1 compare value */
                HRTIMER_STXCNT(hrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        case HRTIMER_SLAVE_TIMER2:
        {
            if(RESET == (HRTIMER_MTCTL0(hrtimer_periph) & HRTIMER_MTCTL0_ST2CEN)){
                /* set the Slave_TIMER2 compare value */
                HRTIMER_STXCNT(hrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        case HRTIMER_SLAVE_TIMER3:
        {
            if(RESET == (HRTIMER_MTCTL0(hrtimer_periph) & HRTIMER_MTCTL0_ST3CEN)){
                /* set the Slave_TIMER3 compare value */
                HRTIMER_STXCNT(hrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        case HRTIMER_SLAVE_TIMER4:
        {
            if(RESET == (HRTIMER_MTCTL0(hrtimer_periph) & HRTIMER_MTCTL0_ST4CEN)){
                /* set the Slave_TIMER4 counter value */
                HRTIMER_STXCNT(hrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        case HRTIMER_SLAVE_TIMER5:
        {
            if(RESET == (HRTIMER_MTCTL0(hrtimer_periph) & HRTIMER_MTCTL0_ST5CEN)){
                /* set the Slave_TIMER5 counter value */
                HRTIMER_STXCNT(hrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        case HRTIMER_SLAVE_TIMER6:
        {
            if(RESET == (HRTIMER_MTCTL0(hrtimer_periph) & HRTIMER_MTCTL0_ST6CEN)){
                /* set the Slave_TIMER6 counter value */
                HRTIMER_STXCNT(hrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        case HRTIMER_SLAVE_TIMER7:
        {
            if(RESET == (HRTIMER_MTCTL0(hrtimer_periph) & HRTIMER_MTCTL0_ST7CEN)){
                /* set the Slave_TIMER7 counter value */
                HRTIMER_STXCNT(hrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        default:
        break;
    }  
}

/*!
    \brief      get the counter value in Master_TIMER and Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[out] none
    \retval     the counter value
*/
uint32_t hrtimer_timers_counter_value_get(uint32_t hrtimer_periph, uint32_t timer_id)
{
    uint32_t cunval = 0U;
    
    switch (timer_id)
    {
        case HRTIMER_MASTER_TIMER:
        {
            /* get the Master_TIMER counter value */
            cunval = HRTIMER_MTCNT(hrtimer_periph);
        }
        break;
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
        {
            /* get the Slave_TIMER counter value */
            cunval = HRTIMER_STXCNT(hrtimer_periph, timer_id);
        }
        break;
        default:
        break;
    }
    return cunval;
}

/*!
    \brief      configure the counter auto reload value in Master_TIMER and Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  carlvalue: min value: 3*tHRTIMER_CK clock, max value: 0xFFFF - (1*tHRTIMER_CK)
    \param[out] none
    \retval     none
*/
void hrtimer_timers_autoreload_value_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t carlvalue)
{
    /* configure the counter auto reload value */
    switch (timer_id)
    {
        case HRTIMER_MASTER_TIMER:
        {
            /* set the Master_TIMER counter value */
            HRTIMER_MTCAR(hrtimer_periph) = carlvalue;
        }
        break;
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
        {
            /* set the Slave_TIMER compare value */
            HRTIMER_STXCAR(hrtimer_periph, timer_id) = carlvalue;
        }
        break;
        default:
        break;
    }
}
/*!
    \brief      get the counter auto reload value in Master_TIMER and Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[out] none
    \retval     the counter auto reload value
*/
uint32_t hrtimer_timers_autoreload_value_get(uint32_t hrtimer_periph, uint32_t timer_id)
{
    uint32_t cralval = 0U;
    
    switch (timer_id)
    {
        case HRTIMER_MASTER_TIMER:
        {
            /* get the Master_TIMER counter auto reload value value */
            cralval = HRTIMER_MTCAR(hrtimer_periph);
        }
        break;
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
        {
            /* get the Slave_TIMER counter auto reload value value */
            cralval = HRTIMER_STXCAR(hrtimer_periph, timer_id);
        }
        break;
        default:
        break;
    }
    return cralval;
}

/*!
    \brief      configure the counter repetition value in Master_TIMER and Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  replvalue: 0~255
    \param[out] none
    \retval     none
*/
void hrtimer_timers_repetition_value_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t replvalue)
{
    /* configure the counter repetition value */
    switch (timer_id)
    {
        case HRTIMER_MASTER_TIMER:
        {
            /* set the Master_TIMER repetition value */
            HRTIMER_MTCREP(hrtimer_periph) = replvalue;
        }
        break;
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
        {
            /* set the Slave_TIMER repetition value */
            HRTIMER_STXCREP(hrtimer_periph, timer_id) = replvalue;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      get the counter repetition value in Master_TIMER and Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[out] none
    \retval     the counter repetition value
*/
uint32_t hrtimer_timers_repetition_value_get(uint32_t hrtimer_periph, uint32_t timer_id)
{
    uint32_t repval = 0U;
    
    switch (timer_id)
    {
        case HRTIMER_MASTER_TIMER:
        {
            /* get the Master_TIMER counter repetition value value */
            repval = HRTIMER_MTCREP(hrtimer_periph);
        }
        break;
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
        {
            /* get the Slave_TIMER counter repetition value value */
            repval = HRTIMER_STXCREP(hrtimer_periph, timer_id);
        }
        break;
        default:
        break;
    }
    return repval;
}

/*!
    \brief      initialize external event filtering for Slave_TIMER configuration struct with a default value
    \param[in]  exevfilter: external event filtering for Slave_TIMER struct definitions
    \param[out] none
    \retval     none
*/
void hrtimer_exevfilter_struct_para_init(hrtimer_exevfilter_parameter_struct * exevfilter)
{
    exevfilter->filter_mode = HRTIMER_EXEVFILTER_DISABLE;
    exevfilter->memorized = HRTIMER_EXEVMEMORIZED_DISABLE;
}

/*!
    \brief      configure the external event filtering for Slave_TIMER (blanking, windowing)
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  event_id: HRTIMER_EXEVENT_NONE, HRTIMER_EXEVENT_y(y=0..9)
    \param[in]  exevfilter: external event filtering for Slave_TIMER struct definitions
                  filter_mode: HRTIMER_EXEVFILTER_DISABLE, HRTIMER_EXEVFILTER_BLANKINGCMPy(y=0..3), HRTIMER_EXEVFILTER_BLANKINGSRCy(y=0..9), HRTIMER_EXEVFILTER_WINDOWINGCMPy(y=1,2), HRTIMER_EXEVFILTER_WINDOWINGSRC
                  memorized: HRTIMER_EXEVMEMORIZED_DISABLE, HRTIMER_EXEVMEMORIZED_ENABLE
    \param[out] none
    \retval     none
*/
void hrtimer_slavetimer_exevent_filtering_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t event_id, hrtimer_exevfilter_parameter_struct *exevfilter)
{
    uint32_t exevfcfg_reg;

    switch (event_id)
    {
        /* reset external event filtering */
        case HRTIMER_EXEVENT_NONE:
        {
            HRTIMER_STXEXEVFCFG0(hrtimer_periph, timer_id) = 0U;
            HRTIMER_STXEXEVFCFG1(hrtimer_periph, timer_id) = 0U;
        }
        break;
        /* configure external event 0 filtering */
        case HRTIMER_EXEVENT_0:
        {
            exevfcfg_reg = HRTIMER_STXEXEVFCFG0(hrtimer_periph, timer_id);
            exevfcfg_reg &= ~(HRTIMER_STXEXEVFCFG0_EXEV0FM | HRTIMER_STXEXEVFCFG0_EXEV0MEEN);
            exevfcfg_reg |= (exevfilter->filter_mode | exevfilter->memorized);
            HRTIMER_STXEXEVFCFG0(hrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 1 filtering */
        case HRTIMER_EXEVENT_1:
        {
            exevfcfg_reg = HRTIMER_STXEXEVFCFG0(hrtimer_periph, timer_id);
            exevfcfg_reg &= ~(HRTIMER_STXEXEVFCFG0_EXEV1FM | HRTIMER_STXEXEVFCFG0_EXEV1MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 6);
            HRTIMER_STXEXEVFCFG0(hrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 2 filtering */
        case HRTIMER_EXEVENT_2:
        {
            exevfcfg_reg = HRTIMER_STXEXEVFCFG0(hrtimer_periph, timer_id);
            exevfcfg_reg &= ~(HRTIMER_STXEXEVFCFG0_EXEV2FM | HRTIMER_STXEXEVFCFG0_EXEV2MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 12);
            HRTIMER_STXEXEVFCFG0(hrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 3 filtering */
        case HRTIMER_EXEVENT_3:
        {
            exevfcfg_reg = HRTIMER_STXEXEVFCFG0(hrtimer_periph, timer_id);
            exevfcfg_reg &= ~(HRTIMER_STXEXEVFCFG0_EXEV3FM | HRTIMER_STXEXEVFCFG0_EXEV3MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 18);
            HRTIMER_STXEXEVFCFG0(hrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 4 filtering */
        case HRTIMER_EXEVENT_4:
        {
            exevfcfg_reg = HRTIMER_STXEXEVFCFG0(hrtimer_periph, timer_id);
            exevfcfg_reg &= ~(HRTIMER_STXEXEVFCFG0_EXEV4FM | HRTIMER_STXEXEVFCFG0_EXEV4MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 24);
            HRTIMER_STXEXEVFCFG0(hrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 5 filtering */
        case HRTIMER_EXEVENT_5:
        {
            exevfcfg_reg = HRTIMER_STXEXEVFCFG1(hrtimer_periph, timer_id);
            exevfcfg_reg &= ~(HRTIMER_STXEXEVFCFG1_EXEV5FM | HRTIMER_STXEXEVFCFG1_EXEV5MEEN);
            exevfcfg_reg |= (exevfilter->filter_mode | exevfilter->memorized);
            HRTIMER_STXEXEVFCFG1(hrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 6 filtering */
        case HRTIMER_EXEVENT_6:
        {
            exevfcfg_reg = HRTIMER_STXEXEVFCFG1(hrtimer_periph, timer_id);
            exevfcfg_reg &= ~(HRTIMER_STXEXEVFCFG1_EXEV6FM | HRTIMER_STXEXEVFCFG1_EXEV6MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 6);
            HRTIMER_STXEXEVFCFG1(hrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 7 filtering */
        case HRTIMER_EXEVENT_7:
        {
            exevfcfg_reg = HRTIMER_STXEXEVFCFG1(hrtimer_periph, timer_id);
            exevfcfg_reg &= ~(HRTIMER_STXEXEVFCFG1_EXEV7FM | HRTIMER_STXEXEVFCFG1_EXEV7MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 12);
            HRTIMER_STXEXEVFCFG1(hrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 8 filtering */
        case HRTIMER_EXEVENT_8:
        {
            exevfcfg_reg = HRTIMER_STXEXEVFCFG1(hrtimer_periph, timer_id);
            exevfcfg_reg &= ~(HRTIMER_STXEXEVFCFG1_EXEV8FM | HRTIMER_STXEXEVFCFG1_EXEV8MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 18);
            HRTIMER_STXEXEVFCFG1(hrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 9 filtering */
        case HRTIMER_EXEVENT_9:
        {
            exevfcfg_reg = HRTIMER_STXEXEVFCFG1(hrtimer_periph, timer_id);
            exevfcfg_reg &= ~(HRTIMER_STXEXEVFCFG1_EXEV9FM | HRTIMER_STXEXEVFCFG1_EXEV9MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 24);
            HRTIMER_STXEXEVFCFG1(hrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      initialize external event configuration struct with a default value
    \param[in]  exevcfg: external event configuration struct
    \param[out] none
    \retval     none
*/
void hrtimer_exeventcfg_struct_para_init(hrtimer_exeventcfg_parameter_struct * exevcfg)
{
    exevcfg->digital_filter = 0U;
    exevcfg->edge = HRTIMER_EXEV_EDGE_LEVEL;
    exevcfg->fast = HRTIMER_EXEV_FAST_DISABLE;
    exevcfg->polarity = HRTIMER_EXEV_POLARITY_HIGH;
    exevcfg->source = HRTIMER_EXEV_SRC0;
}

/*!
    \brief      configure the an external event
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  event_id: HRTIMER_EXEVENT_NONE, HRTIMER_EXEVENT_y(y=0..9)
    \param[in]  exevcfg: external event configuration struct
                  source: HRTIMER_EXEV_SRCy(y=0..3)
                  polarity: HRTIMER_EXEV_POLARITY_HIGH, HRTIMER_EXEV_POLARITY_LOW
                  edge: HRTIMER_EXEV_EDGE_LEVEL, HRTIMER_EXEV_EDGE_RISING, HRTIMER_EXEV_EDGE_FALLING, HRTIMER_EXEV_EDGE_BOTH
                  digital_filter: 0x0~0xF
                  fast：HRTIMER_EXEV_FAST_DISABLE,HRTIMER_EXEV_FAST_ENABLE
    \param[out] none
    \retval     none
*/
void hrtimer_exevent_config(uint32_t hrtimer_periph, uint32_t event_id, hrtimer_exeventcfg_parameter_struct* exevcfg)
{
    /* configure the an external event channel */
    external_event_config(hrtimer_periph, event_id, exevcfg);
}

/*!
    \brief      configure external event digital filter clock division
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  prescaler: clock division value
                only one parameter can be selected which is shown as below:
      \arg          HRTIMER_EXEV_PRESCALER_DIV1: fHRTIMER_EXEVFCK = fHRTIMER_CK 
      \arg          HRTIMER_EXEV_PRESCALER_DIV2: fHRTIMER_EXEVFCK = fHRTIMER_CK / 2 
      \arg          HRTIMER_EXEV_PRESCALER_DIV4: fHRTIMER_EXEVFCK = fHRTIMER_CK / 4 
      \arg          HRTIMER_EXEV_PRESCALER_DIV8: fHRTIMER_EXEVFCK = fHRTIMER_CK / 8 
    \param[out] none
    \retval     none
*/
void hrtimer_exevent_prescaler(uint32_t hrtimer_periph, uint32_t prescaler)
{
  uint32_t exevdfctl_reg;

  /* set the external event digital filter clock division */
  exevdfctl_reg = HRTIMER_EXEVDFCTL(hrtimer_periph);
  exevdfctl_reg &= ~(HRTIMER_EXEVDFCTL_EXEVFDIV);
  exevdfctl_reg |= prescaler;

  HRTIMER_EXEVDFCTL(hrtimer_periph) = exevdfctl_reg;
}


/*!
    \brief      initialize external event configuration struct with a default value
    \param[in]  exevcfg: external event configuration struct
    \param[out] none
    \retval     none
*/
void hrtimer_exeventx_counter_struct_para_init(hrtimer_exeventcnt_parameter_struct *exevcnt)
{
    exevcnt->reset_mode = HRTIMER_EXEVX_RESET_MODE0;
    exevcnt->event_source = HRTIMER_EXEVX_SOURCE_EXEV0;
    exevcnt->counter_threshold = 0U;
}

/*!
    \brief      configure the external event X counter
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  exevcnt: external event X filter counter configuration struct
                  reset_mode: HRTIMER_EXEVX_RESET_MODE0, HRTIMER_EXEVX_RESET_MODE1
                  event_source: HRTIMER_EXEVX_SOURCE_EXEVy,(y = 0..9)
                  counter_threshold: 0x00~0x3F
    \param[out] none
    \retval     none
*/
void hrtimer_exeventx_counter_config(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_exeventcnt_parameter_struct *exevcnt)
{
    uint32_t exevfcfg2;

    /* configure the external event X counter */
    exevfcfg2 = HRTIMER_STXEXEVFCFG2(hrtimer_periph, timer_id);
    exevfcfg2 &= ~(HRTIMER_STXEXEVFCFG2_EXTEXRSTM|HRTIMER_STXEXEVFCFG2_EXTEXSEL|HRTIMER_STXEXEVFCFG2_EXTEXCNTTHR);
    exevfcfg2 |= ((exevcnt->counter_threshold << 8) | exevcnt->event_source | exevcnt->reset_mode);
    HRTIMER_STXEXEVFCFG2(hrtimer_periph, timer_id) = exevfcfg2;
}

/*!
    \brief      reset external event X counter
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[out] none
    \retval     none
*/
void hrtimer_software_reset_exeventx_counter(uint32_t hrtimer_periph, uint32_t timer_id)
{
    HRTIMER_STXEXEVFCFG2(hrtimer_periph, timer_id) |= HRTIMER_STXEXEVFCFG2_EXTEXCRST;
}

/*!
    \brief      enable external event X counter
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[out] none
    \retval     none
*/
void hrtimer_exeventx_counter_enable(uint32_t hrtimer_periph, uint32_t timer_id)
{
    HRTIMER_STXEXEVFCFG2(hrtimer_periph,timer_id) |= HRTIMER_STXEXEVFCFG2_EXTEXCEN;
}

/*!
    \brief      disable external event X counter
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[out] none
    \retval     none
*/
void hrtimer_exeventx_counter_disable(uint32_t hrtimer_periph, uint32_t timer_id)
{
    HRTIMER_STXEXEVFCFG2(hrtimer_periph,timer_id) &= ~HRTIMER_STXEXEVFCFG2_EXTEXCEN;
}

/*!
    \brief      enable a output channel
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[out] none
    \retval     none
*/
uint32_t hrtimer_exeventx_counter_read(uint32_t hrtimer_periph, uint32_t timer_id)
{
    uint32_t exevfcfg2;
    exevfcfg2 = HRTIMER_STXEXEVFCFG2(hrtimer_periph,timer_id);
    return ((exevfcfg2 & HRTIMER_STXEXEVFCFG2_EXTEXCNT)>> 26);
}

/*!
    \brief      initialize synchronization configuration struct with a default value
    \param[in]  synccfg: synchronization configuration struct
    \param[out] none
    \retval     none
*/
void hrtimer_synccfg_struct_para_init(hrtimer_synccfg_parameter_struct* synccfg)
{
    synccfg->input_source = HRTIMER_SYNCINPUTSOURCE_DISABLE;
    synccfg->output_polarity = HRTIMER_SYNCOUTPUTPOLARITY_DISABLE;
    synccfg->output_source = HRTIMER_SYNCOUTPUTSOURCE_MTSTART;
}

/*!
    \brief      configure the synchronization input/output of the HRTIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  synccfg: synchronization configuration struct
                  input_source: HRTIMER_SYNCINPUTSOURCE_DISABLE, HRTIMER_SYNCINPUTSOURCE_INTERNAL, HRTIMER_SYNCINPUTSOURCE_EXTERNAL
                  output_source: HRTIMER_SYNCOUTPUTSOURCE_MTSTART, HRTIMER_SYNCOUTPUTSOURCE_MTCMP0, HRTIMER_SYNCOUTPUTSOURCE_ST0START, HRTIMER_SYNCOUTPUTSOURCE_ST0CMP0
                  output_polarity: HRTIMER_SYNCOUTPUTPOLARITY_DISABLE, HRTIMER_SYNCOUTPUTPOLARITY_POSITIVE, HRTIMER_SYNCOUTPUTPOLARITY_NEGATIVE
    \param[out] none
    \retval     none
*/
void hrtimer_synchronization_config(uint32_t hrtimer_periph, hrtimer_synccfg_parameter_struct* synccfg)
{
    uint32_t mtctl0_reg;

    mtctl0_reg = HRTIMER_MTCTL0(hrtimer_periph);

    /* set the synchronization input source */
    mtctl0_reg &= ~(HRTIMER_MTCTL0_SYNISRC);
    mtctl0_reg |= synccfg->input_source;
  
    /* set the event to be sent on the synchronization output */
    mtctl0_reg &= ~(HRTIMER_MTCTL0_SYNOSRC);
    mtctl0_reg |= synccfg->output_source;
  
    /* set the polarity of the synchronization output */
    mtctl0_reg &= ~(HRTIMER_MTCTL0_SYNOPLS);
    mtctl0_reg |= synccfg->output_polarity;
  
    HRTIMER_MTCTL0(hrtimer_periph) = mtctl0_reg;
}

/*!
    \brief      initialize double channel trigger struct
    \param[in]  doubletrigger: dac trigger struct
    \param[out] none
    \retval     none
*/
void hrtimer_double_channel_struct_para_init(hrtimer_double_trigger_parameter_struct *doubletrigger)
{
    doubletrigger->trigger_enable = HRTIMER_DOUBLE_TRIG_DISABLE;
    doubletrigger->trigger0 = HRTIMER_DOUBLE_TRIG0_BY_CPV1;
    doubletrigger->trigger1 = HRTIMER_DOUBLE_TRIG1_BY_CNT_RESET;
}
/*!
    \brief      configure Slave_TIMER in double channel trigger
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  trigger_enable: HRTIMER_DOUBLE_TRIG_DISABLE,HRTIMER_DOUBLE_TRIG_ENABLE
    \param[in]  trigger0: HRTIMER_DOUBLE_TRIG0_BY_CPV1,HRTIMER_DOUBLE_TRIG0_BY_CH0_RESET
    \param[in]  trigger1: HRTIMER_DOUBLE_TRIG1_BY_CNT_RESET,HRTIMER_DOUBLE_TRIG1_BY_CH0_SET
    \param[out] none
    \retval     none
*/
void hrtimer_double_trigger_config(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_double_trigger_parameter_struct *doubletrigger)
{
    uint32_t stxctl1;
    stxctl1 = HRTIMER_STXCTL1(hrtimer_periph, timer_id);
    /* clear output config */
    stxctl1 &= ~(HRTIMER_STXCTL1_TRIGEN | HRTIMER_STXCTL1_TRIG0M | HRTIMER_STXCTL1_TRIG1M);
    /* config the trigger enable, step trigger, reset trigger */
    stxctl1 |= (doubletrigger->trigger_enable|doubletrigger->trigger0|doubletrigger->trigger1);
    HRTIMER_STXCTL1(hrtimer_periph, timer_id) = stxctl1;
}

/*!
    \brief      initialize roll over struct with a default value
    \param[in]  rollover: roll over struct
    \param[out] none
    \retval     none
*/
void hrtimer_roll_over_struct_para_init(hrtimer_roll_over_parameter_struct *rollover)
{
    rollover->roll_over_mode = HRTIMER_ROLLOVER_MODE0;
    rollover->output_roll_over_mode = HRTIMER_OUTPUT_ROLLOVER_MODE0;
    rollover->adc_roll_over_mode = HRTIMER_ADC_ROLLOVER_MODE0;
    rollover->bunch_mode_roll_over_mode = HRTIMER_BUNCH_MODE_ROLLOVER_MODE0;
    rollover->fault_event_roll_over_mode = HRTIMER_FAULT_EVENTROLLOVER_MODE0;
}

/*!
    \brief      configure Slave_TIMER in roll over mode
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  rollover: roll over struct definitions
                  roll_over_mode: HRTIMER_ROLLOVER_MODE0, HRTIMER_ROLLOVER_MODE1,HRTIMER_ROLLOVER_MODE2
                  output_roll_over_mode: HRTIMER_OUTPUT_ROLLOVER_MODE0, HRTIMER_OUTPUT_ROLLOVER_MODE1, HRTIMER_OUTPUT_ROLLOVER_MODE2
                  adc_roll_over_mode: HRTIMER_ADC_ROLLOVER_MODE0,HRTIMER_ADC_ROLLOVER_MODE1,HRTIMER_ADC_ROLLOVER_MODE2
                  bunch_mode_roll_over_mode: HRTIMER_BUNCH_MODE_ROLLOVER_MODE0,HRTIMER_BUNCH_MODE_ROLLOVER_MODE1,HRTIMER_BUNCH_MODE_ROLLOVER_MODE2
                  fault_event_roll_over_mode: HRTIMER_FAULT_EVENTROLLOVER_MODE0,HRTIMER_FAULT_EVENTROLLOVER_MODE1,HRTIMER_FAULT_EVENTROLLOVER_MODE1
    \param[out] none
    \retval     none
*/
void hrtimer_roll_over_mode_config(uint32_t hrtimer_periph, uint32_t timer_id,hrtimer_roll_over_parameter_struct *rollover)
{
    uint32_t stxctl1;
    stxctl1 = HRTIMER_STXCTL1(hrtimer_periph, timer_id);
    /* clear output config */
    stxctl1 &= ~(HRTIMER_STXCTL1_ROVM | HRTIMER_STXCTL1_OUTROVM | HRTIMER_STXCTL1_ADCROVM |HRTIMER_STXCTL1_BMROVM | HRTIMER_STXCTL1_FEROVM);
    /* config roll over mode */
    stxctl1 |= (rollover->roll_over_mode | rollover->output_roll_over_mode | rollover->adc_roll_over_mode | rollover->bunch_mode_roll_over_mode | rollover->fault_event_roll_over_mode);
    HRTIMER_STXCTL1(hrtimer_periph, timer_id) = stxctl1;
}

/*!
    \brief      initialize fault input configuration struct with a default value
    \param[in]  faultcfg: fault input configuration struct
    \param[out] none
    \retval     none
*/
void hrtimer_faultcfg_struct_para_init(hrtimer_faultcfg_parameter_struct * faultcfg)
{
    faultcfg->filter = 0x0U;
    faultcfg->polarity = HRTIMER_FAULT_POLARITY_LOW;
    faultcfg->protect = HRTIMER_FAULT_PROTECT_DISABLE;
    faultcfg->source = HRTIMER_FAULT_SOURCE_PIN;
    faultcfg->control = HRTIMER_FAULT_CHANNEL_DISABLE;
    faultcfg->blanksource = HRTIMER_FAULT_COMP_COMP;
    faultcfg->counter = 0U;
    faultcfg->resetmode = HRTIMER_FAULT_COUNTER_RESET_UNCONDITIONAL;
    faultcfg->blanksenable = HRTIMER_FAULT_BLKEN_DISABLE;
}

/*!
    \brief      configure the fault input
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  fault_id: HRTIMER_FAULT_y(y=0..7)
    \param[in]  faultcfg: fault input configuration struct
                  source: HRTIMER_FAULT_SOURCE_PIN, HRTIMER_FAULT_SOURCE_INTERNAL, HRTIMER_FAULT_SOURCE_EXT_EVENT
                  polarity: HRTIMER_FAULT_POLARITY_LOW, HRTIMER_FAULT_POLARITY_HIGH
                  control: HRTIMER_FAULT_CHANNEL_DISABLE, HRTIMER_FAULT_CHANNEL_ENABLE
                  filter: 0x0~0xF
                  protect: HRTIMER_FAULT_PROTECT_DISABLE, HRTIMER_FAULT_PROTECT_ENABLE
                  blanksource: HRTIMER_FAULT_COMP_COMP,HRTIMER_FAULT_RST_COMP
                  blankenable: HRTIMER_FAULT_BLKEN_DISABLE,HRTIMER_FAULT_BLKEN_ENABLE
                  counter: 0x0~0xF
                  resetmode: HRTIMER_FAULT_COUNTER_RESET_UNCONDITIONAL,HRTIMER_FAULT_COUNTER_RESET_CONDITIONAL

    \param[out] none
    \retval     none
*/
void hrtimer_fault_config(uint32_t hrtimer_periph, uint32_t fault_id, hrtimer_faultcfg_parameter_struct* faultcfg)
{
    uint32_t fltincfg0;
    uint32_t fltincfg1;
    uint32_t fltincfg2;
    uint32_t fltincfg3;
    uint32_t fltincfg4;
  
    fltincfg0 = HRTIMER_FLTINCFG0(hrtimer_periph);
    fltincfg1 = HRTIMER_FLTINCFG1(hrtimer_periph);
    fltincfg2 = HRTIMER_FLTINCFG2(hrtimer_periph);
    fltincfg3 = HRTIMER_FLTINCFG3(hrtimer_periph);
    fltincfg4 = HRTIMER_FLTINCFG4(hrtimer_periph);
  
    switch (fault_id)
    {
        case HRTIMER_FAULT_0:
        {
            /* configure fault input 0 */
            fltincfg0 &= ~( HRTIMER_FLTINCFG0_FLT0INP | HRTIMER_FLTINCFG0_FLT0INSRC0 | HRTIMER_FLTINCFG0_FLT0INFC | HRTIMER_FLTINCFG0_FLT0INPROT | HRTIMER_FLTINCFG0_FLT0INEN);
            fltincfg1 &= ~( HRTIMER_FLTINCFG1_FLT0INSRC1);
            fltincfg0 |= (((faultcfg->source & 0x00000001U) << 2) & HRTIMER_FLTINCFG0_FLT0INSRC0);
            fltincfg1 |= (((faultcfg->source & 0x00000002U) << 15) & HRTIMER_FLTINCFG1_FLT0INSRC1);
            fltincfg0 |= faultcfg->polarity;
            fltincfg0 |= ((faultcfg->filter) << 3);
            fltincfg0 |= faultcfg->control;
            fltincfg0 |= faultcfg->protect;
            
            fltincfg2 &= ~(HRTIMER_FLTINCFG2_FLT0BLKEN | HRTIMER_FLTINCFG2_FLT0BLKS | HRTIMER_FLTINCFG2_FLT0CNT | HRTIMER_FLTINCFG2_FLT0RST);
            fltincfg2 |= (faultcfg->blanksenable | faultcfg->blanksource | (faultcfg->counter <<2) | faultcfg->resetmode);
        }
        break;
        case HRTIMER_FAULT_1:
        {
            /* configure fault input 1 */
            fltincfg0 &= ~( HRTIMER_FLTINCFG0_FLT1INP | HRTIMER_FLTINCFG0_FLT1INSRC0 | HRTIMER_FLTINCFG0_FLT1INFC | HRTIMER_FLTINCFG0_FLT1INPROT | HRTIMER_FLTINCFG0_FLT1INEN );
            fltincfg1 &= ~( HRTIMER_FLTINCFG1_FLT1INSRC1);
            fltincfg0 |= (((faultcfg->source & 0x00000001U) << 10) & HRTIMER_FLTINCFG0_FLT1INSRC0);
            fltincfg1 |= (((faultcfg->source & 0x00000002U) << 16) & HRTIMER_FLTINCFG1_FLT1INSRC1);
            fltincfg0 |= ((faultcfg->polarity) << 8);
            fltincfg0 |= ((faultcfg->filter) << 11);
            fltincfg0 |= ((faultcfg->control) << 8);
            fltincfg0 |= ((faultcfg->protect) << 8);
            
            fltincfg2 &= ~(HRTIMER_FLTINCFG2_FLT1BLKEN | HRTIMER_FLTINCFG2_FLT1BLKS | HRTIMER_FLTINCFG2_FLT1CNT | HRTIMER_FLTINCFG2_FLT1RST);
            fltincfg2 |= ((faultcfg->blanksenable << 8) | (faultcfg->blanksource << 8) | (faultcfg->counter << 10) | (faultcfg->resetmode << 8));
        }
        break;
        case HRTIMER_FAULT_2:
        {
            /* configure fault input 2 */
            fltincfg0 &= ~( HRTIMER_FLTINCFG0_FLT2INP | HRTIMER_FLTINCFG0_FLT2INSRC0 | HRTIMER_FLTINCFG0_FLT2INFC | HRTIMER_FLTINCFG0_FLT2INPROT | HRTIMER_FLTINCFG0_FLT2INEN);
            fltincfg1 &= ~( HRTIMER_FLTINCFG1_FLT2INSRC1);
            fltincfg0 |= (((faultcfg->source & 0x00000001U) << 18) & HRTIMER_FLTINCFG0_FLT2INSRC0);
            fltincfg1 |= (((faultcfg->source & 0x00000002U) << 17) & HRTIMER_FLTINCFG1_FLT2INSRC1);
            fltincfg0 |= ((faultcfg->polarity) << 16);
            fltincfg0 |= ((faultcfg->filter) << 19);
            fltincfg0 |= ((faultcfg->control) << 16);
            fltincfg0 |= ((faultcfg->protect) << 16);
            
            fltincfg2 &= ~(HRTIMER_FLTINCFG2_FLT2BLKEN | HRTIMER_FLTINCFG2_FLT2BLKS | HRTIMER_FLTINCFG2_FLT2CNT | HRTIMER_FLTINCFG2_FLT2RST);
            fltincfg2 |= ((faultcfg->blanksenable << 16) | (faultcfg->blanksource << 16) | (faultcfg->counter << 18) | (faultcfg->resetmode << 16));
        }
        break;
        case HRTIMER_FAULT_3:
        {
            /* configure fault input 3 */
            fltincfg0 &= ~( HRTIMER_FLTINCFG0_FLT3INP | HRTIMER_FLTINCFG0_FLT3INSRC0 | HRTIMER_FLTINCFG0_FLT3INFC | HRTIMER_FLTINCFG0_FLT3INPROT | HRTIMER_FLTINCFG0_FLT3INEN);
            fltincfg1 &= ~( HRTIMER_FLTINCFG1_FLT3INSRC1);
            fltincfg0 |= (((faultcfg->source & 0x00000001U) << 26) & HRTIMER_FLTINCFG0_FLT3INSRC0);
            fltincfg1 |= (((faultcfg->source & 0x00000002U) << 18) & HRTIMER_FLTINCFG1_FLT3INSRC1);
            fltincfg0 |= ((faultcfg->polarity) << 24);
            fltincfg0 |= ((faultcfg->filter) << 27);
            fltincfg0 |= ((faultcfg->control) << 24);
            fltincfg0 |= ((faultcfg->protect) << 24);
            
            fltincfg2 &= ~(HRTIMER_FLTINCFG2_FLT3BLKEN | HRTIMER_FLTINCFG2_FLT3BLKS | HRTIMER_FLTINCFG2_FLT3CNT | HRTIMER_FLTINCFG2_FLT3RST);
            fltincfg2 |= ((faultcfg->blanksenable << 24) | (faultcfg->blanksource << 24) | (faultcfg->counter << 26) | (faultcfg->resetmode << 24));
        }
        break;
        case HRTIMER_FAULT_4:
        {
            /* configure fault input 4 */
            fltincfg1 &= ~( HRTIMER_FLTINCFG1_FLT4INP | HRTIMER_FLTINCFG1_FLT4INSRC0 |  HRTIMER_FLTINCFG1_FLT4INSRC1 | HRTIMER_FLTINCFG1_FLT4INFC | HRTIMER_FLTINCFG1_FLT4INPROT | HRTIMER_FLTINCFG1_FLT4INEN);
            fltincfg1 |= (((faultcfg->source & 0x00000001U) << 2) & HRTIMER_FLTINCFG1_FLT4INSRC0);
            fltincfg1 |= (((faultcfg->source & 0x00000002U) << 19) & HRTIMER_FLTINCFG1_FLT4INSRC1);
            fltincfg1 |= faultcfg->polarity;
            fltincfg1 |= ((faultcfg->filter) << 3);
            fltincfg1 |= (faultcfg->control);
            fltincfg1 |= faultcfg->protect;
            
            fltincfg3 &= ~(HRTIMER_FLTINCFG3_FLT4BLKEN | HRTIMER_FLTINCFG3_FLT4BLKS | HRTIMER_FLTINCFG3_FLT4CNT | HRTIMER_FLTINCFG3_FLT4RST);
            fltincfg3 |= (faultcfg->blanksenable | faultcfg->blanksource | (faultcfg->counter << 2) | faultcfg->resetmode);
        }
        break;
        case HRTIMER_FAULT_5:
        {
            /* configure fault input 5 */
            fltincfg1 &= ~( HRTIMER_FLTINCFG1_FLT5INP | HRTIMER_FLTINCFG1_FLT5INSRC0 | HRTIMER_FLTINCFG1_FLT5INSRC1 | HRTIMER_FLTINCFG1_FLT5INFC | HRTIMER_FLTINCFG1_FLT5INPROT | HRTIMER_FLTINCFG1_FLT5INEN);
            fltincfg1 |= (((faultcfg->source & 0x00000001U) << 10) & HRTIMER_FLTINCFG1_FLT5INSRC0);
            fltincfg1 |= (((faultcfg->source & 0x00000002U) << 20) & HRTIMER_FLTINCFG1_FLT5INSRC1);
            fltincfg1 |= (faultcfg->polarity << 8);
            fltincfg1 |= ((faultcfg->filter) << 11);
            fltincfg1 |= ((faultcfg->control) << 8);
            fltincfg1 |= faultcfg->protect;
            
            fltincfg3 &= ~(HRTIMER_FLTINCFG3_FLT5BLKEN | HRTIMER_FLTINCFG3_FLT5BLKS | HRTIMER_FLTINCFG3_FLT5CNT | HRTIMER_FLTINCFG3_FLT5RST);
            fltincfg3 |= ((faultcfg->blanksenable << 8) | (faultcfg->blanksource << 8) | (faultcfg->counter << 10) | (faultcfg->resetmode << 8));
        }
        break;
        case HRTIMER_FAULT_6:
        {
            /* configure fault input 6 */
            fltincfg4 &= ~( HRTIMER_FLTINCFG4_FLT6INP | HRTIMER_FLTINCFG4_FLT6INSRC0 | HRTIMER_FLTINCFG4_FLT6INFC | HRTIMER_FLTINCFG4_FLT6INPROT | HRTIMER_FLTINCFG4_FLT6INEN);
            fltincfg1 &= ~( HRTIMER_FLTINCFG1_FLT6INSRC1);
            fltincfg4 |= (((faultcfg->source & 0x00000001U) << 2) & HRTIMER_FLTINCFG4_FLT6INSRC0);
            fltincfg1 |= (((faultcfg->source & 0x00000002U) << 21) & HRTIMER_FLTINCFG1_FLT6INSRC1);
            fltincfg4 |= faultcfg->polarity;
            fltincfg4 |= ((faultcfg->filter) << 3);
            fltincfg4 |= faultcfg->control;
            fltincfg4 |= faultcfg->protect;
            
            fltincfg3 &= ~(HRTIMER_FLTINCFG3_FLT6BLKEN | HRTIMER_FLTINCFG3_FLT6BLKS | HRTIMER_FLTINCFG3_FLT6CNT | HRTIMER_FLTINCFG3_FLT6RST);
            fltincfg3 |= ((faultcfg->blanksenable << 16) | (faultcfg->blanksource << 16) | (faultcfg->counter << 18) | (faultcfg->resetmode << 16));
        }
        break;
        case HRTIMER_FAULT_7:
        {
            /* configure fault input 7 */
            fltincfg4 &= ~( HRTIMER_FLTINCFG4_FLT7INP | HRTIMER_FLTINCFG4_FLT7INSRC0 | HRTIMER_FLTINCFG4_FLT7INFC | HRTIMER_FLTINCFG4_FLT7INPROT | HRTIMER_FLTINCFG4_FLT7INEN );
            fltincfg1 &= ~( HRTIMER_FLTINCFG1_FLT7INSRC1);
            fltincfg4 |= (((faultcfg->source & 0x00000001U) << 10) & HRTIMER_FLTINCFG4_FLT7INSRC0);
            fltincfg1 |= (((faultcfg->source & 0x00000002U) << 22) & HRTIMER_FLTINCFG1_FLT7INSRC1);
            fltincfg4 |= ((faultcfg->polarity) << 8);
            fltincfg4 |= ((faultcfg->filter) << 11);
            fltincfg4 |= ((faultcfg->control) << 8);
            fltincfg4 |= ((faultcfg->protect) << 8);
            
            fltincfg3 &= ~(HRTIMER_FLTINCFG3_FLT7BLKEN | HRTIMER_FLTINCFG3_FLT7BLKS | HRTIMER_FLTINCFG3_FLT7CNT | HRTIMER_FLTINCFG3_FLT7RST);
            fltincfg3 |= ((faultcfg->blanksenable << 24) | (faultcfg->blanksource << 24) | (faultcfg->counter << 26) | (faultcfg->resetmode << 24));
        }
        break;
        default:
        break;
    }
    
    HRTIMER_FLTINCFG2(hrtimer_periph) = fltincfg2;
    HRTIMER_FLTINCFG3(hrtimer_periph) = fltincfg3;
    HRTIMER_FLTINCFG0(hrtimer_periph) = fltincfg0;
    HRTIMER_FLTINCFG1(hrtimer_periph) = fltincfg1;
    HRTIMER_FLTINCFG4(hrtimer_periph) = fltincfg4;
}

/*!
    \brief      configure the fault input digital filter clock division
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  prescaler: clock division value
                only one parameter can be selected which is shown as below:
      \arg          HRTIMER_FAULT_PRESCALER_DIV1: fHRTIMER_FLTFCK = fHRTIMER_CK 
      \arg          HRTIMER_FAULT_PRESCALER_DIV2: fHRTIMER_FLTFCK = fHRTIMER_CK / 2 
      \arg          HRTIMER_FAULT_PRESCALER_DIV4: fHRTIMER_FLTFCK = fHRTIMER_CK / 4 
      \arg          HRTIMER_FAULT_PRESCALER_DIV8: fHRTIMER_FLTFCK = fHRTIMER_CK / 8 
    \param[out] none
    \retval     none
*/
void hrtimer_fault_prescaler_config(uint32_t hrtimer_periph, uint32_t prescaler)
{
    uint32_t fltincfg1;

    /* configure digital filter clock division */
    fltincfg1 = HRTIMER_FLTINCFG1(hrtimer_periph);
    fltincfg1 &= ~(HRTIMER_FLTINCFG1_FLTFDIV);
    fltincfg1 |= prescaler;
    HRTIMER_FLTINCFG1(hrtimer_periph) = fltincfg1;
}

/*!
    \brief      fault input enable
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  fault_id: HRTIMER_FAULT_y(y=0..7)
    \param[out] none
    \retval     none
*/
void hrtimer_fault_input_enable(uint32_t hrtimer_periph, uint32_t fault_id)
{
    uint32_t fltincfg0;
    uint32_t fltincfg1;
    uint32_t fltincfg4;
    
    fltincfg0 = HRTIMER_FLTINCFG0(hrtimer_periph);
    fltincfg1 = HRTIMER_FLTINCFG1(hrtimer_periph);
    fltincfg4 = HRTIMER_FLTINCFG4(hrtimer_periph);
    
    switch (fault_id)
    {
        case HRTIMER_FAULT_0:
        {
            /* configure fault input 0 */
            fltincfg0 |= HRTIMER_FLTINCFG0_FLT0INEN;
        }
        break;
        case HRTIMER_FAULT_1:
        {
            /* configure fault input 1 */
            fltincfg0 |= HRTIMER_FLTINCFG0_FLT1INEN;
        }
        break;
        case HRTIMER_FAULT_2:
        {
            /* configure fault input 2 */
            fltincfg0 |= HRTIMER_FLTINCFG0_FLT2INEN;
        }
        break;
        case HRTIMER_FAULT_3:
        {
            /* configure fault input 3 */
            fltincfg0 |= HRTIMER_FLTINCFG0_FLT3INEN;
        }
        break;
        case HRTIMER_FAULT_4:
        {
            /* configure fault input 4 */
            fltincfg1 |= HRTIMER_FLTINCFG1_FLT4INEN;
        }
        break;
        case HRTIMER_FAULT_5:
        {
            /* configure fault input 5 */
            fltincfg1 |= HRTIMER_FLTINCFG1_FLT5INEN;
        }
        break;
        case HRTIMER_FAULT_6:
        {
            /* configure fault input 6 */
            fltincfg4 |= HRTIMER_FLTINCFG4_FLT6INEN;
        }
        break;
        case HRTIMER_FAULT_7:
        {
            /* configure fault input 7 */
            fltincfg4 |= HRTIMER_FLTINCFG4_FLT7INEN;
        }
        break;
        default:
        break;
    }

    HRTIMER_FLTINCFG0(hrtimer_periph) = fltincfg0;
    HRTIMER_FLTINCFG1(hrtimer_periph) = fltincfg1;
    HRTIMER_FLTINCFG4(hrtimer_periph) = fltincfg4;
}

/*!
    \brief      fault input disable
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  fault_id: HRTIMER_FAULT_y(y=0..7)
    \param[out] none
    \retval     none
*/
void hrtimer_fault_input_disable(uint32_t hrtimer_periph, uint32_t fault_id)
{
    uint32_t fltincfg0;
    uint32_t fltincfg1;
    uint32_t fltincfg4;
    
    fltincfg0 = HRTIMER_FLTINCFG0(hrtimer_periph);
    fltincfg1 = HRTIMER_FLTINCFG1(hrtimer_periph);
    fltincfg4 = HRTIMER_FLTINCFG4(hrtimer_periph);
    
    switch (fault_id)
    {
        case HRTIMER_FAULT_0:
        {
            /* configure fault input 0 */
            fltincfg0 &= ~HRTIMER_FLTINCFG0_FLT0INEN;
        }
        break;
        case HRTIMER_FAULT_1:
        {
            /* configure fault input 1 */
            fltincfg0 &= ~HRTIMER_FLTINCFG0_FLT1INEN;
        }
        break;
        case HRTIMER_FAULT_2:
        {
            /* configure fault input 2 */
            fltincfg0 &= ~HRTIMER_FLTINCFG0_FLT2INEN;
        }
        break;
        case HRTIMER_FAULT_3:
        {
            /* configure fault input 3 */
            fltincfg0 &= ~HRTIMER_FLTINCFG0_FLT3INEN;
        }
        break;
        case HRTIMER_FAULT_4:
        {
            /* configure fault input 4 */
            fltincfg1 &= ~HRTIMER_FLTINCFG1_FLT4INEN;
        }
        break;
        case HRTIMER_FAULT_5:
        {
            /* configure fault input 5 */
            fltincfg1 &= ~HRTIMER_FLTINCFG1_FLT5INEN;
        }
        break;
        case HRTIMER_FAULT_6:
        {
            /* configure fault input 6 */
            fltincfg4 &= ~HRTIMER_FLTINCFG4_FLT6INEN;
        }
        break;
        case HRTIMER_FAULT_7:
        {
            /* configure fault input 7 */
            fltincfg4 &= ~HRTIMER_FLTINCFG4_FLT7INEN;
        }
        break;
        default:
        break;
    }

    HRTIMER_FLTINCFG0(hrtimer_periph) = fltincfg0;
    HRTIMER_FLTINCFG1(hrtimer_periph) = fltincfg1;
    HRTIMER_FLTINCFG4(hrtimer_periph) = fltincfg4;
}

/*!
    \brief      fault input couter reset
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  fault_id: HRTIMER_FAULT_y(y=0..7)
    \param[out] none
    \retval     none
*/
void hrtimer_fault_counter_reset(uint32_t hrtimer_periph, uint32_t fault_id)
{
    switch (fault_id)
    {
        case HRTIMER_FAULT_0:
        {
            /* reset fault input 0 counter */
            HRTIMER_FLTINCFG2(hrtimer_periph) |= HRTIMER_FLTINCFG2_FLT0CNTRST;
        }
        break;
        case HRTIMER_FAULT_1:
        {
            /* reset fault input 1 counter */
            HRTIMER_FLTINCFG2(hrtimer_periph) |= HRTIMER_FLTINCFG2_FLT1CNTRST;
        }
        break;
        case HRTIMER_FAULT_2:
        {
            /* reset fault input 2 counter */
            HRTIMER_FLTINCFG2(hrtimer_periph) |= HRTIMER_FLTINCFG2_FLT2CNTRST;
        }
        break;
        case HRTIMER_FAULT_3:
        {
            /* reset fault input 3 counter */
            HRTIMER_FLTINCFG2(hrtimer_periph) |= HRTIMER_FLTINCFG2_FLT3CNTRST;
        }
        break;
        case HRTIMER_FAULT_4:
        {
            /* reset fault input 4 counter */
            HRTIMER_FLTINCFG3(hrtimer_periph) |= HRTIMER_FLTINCFG3_FLT4CNTRST;
        }
        break;
        case HRTIMER_FAULT_5:
        {
            /* reset fault input 5 counter */
            HRTIMER_FLTINCFG3(hrtimer_periph) |= HRTIMER_FLTINCFG3_FLT5CNTRST;
        }
        break;
        case HRTIMER_FAULT_6:
        {
            /* reset fault input 6 counter */
            HRTIMER_FLTINCFG3(hrtimer_periph) |= HRTIMER_FLTINCFG3_FLT6CNTRST;
        }
        break;
        case HRTIMER_FAULT_7:
        {
            /* reset fault input 7 counter */
            HRTIMER_FLTINCFG3(hrtimer_periph) |= HRTIMER_FLTINCFG3_FLT7CNTRST;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      fault input blank enable
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  fault_id: HRTIMER_FAULT_y(y=0..7)
    \param[out] none
    \retval     none
*/
void hrtimer_fault_blank_enable(uint32_t hrtimer_periph, uint32_t fault_id)
{
    switch (fault_id)
    {
        case HRTIMER_FAULT_0:
        {
            /* enable fault input 0 blank */
            HRTIMER_FLTINCFG2(hrtimer_periph) |= HRTIMER_FLTINCFG2_FLT0BLKEN;
        }
        break;
        case HRTIMER_FAULT_1:
        {
            /* enable fault input 1 blank */
            HRTIMER_FLTINCFG2(hrtimer_periph) |= HRTIMER_FLTINCFG2_FLT1BLKEN;
        }
        break;
        case HRTIMER_FAULT_2:
        {
            /* enable fault input 2 blank */
            HRTIMER_FLTINCFG2(hrtimer_periph) |= HRTIMER_FLTINCFG2_FLT2BLKEN;
        }
        break;
        case HRTIMER_FAULT_3:
        {
            /* enable fault input 3 blank */
            HRTIMER_FLTINCFG2(hrtimer_periph) |= HRTIMER_FLTINCFG2_FLT3BLKEN;
        }
        break;
        case HRTIMER_FAULT_4:
        {
            /* enable fault input 4 blank */
            HRTIMER_FLTINCFG3(hrtimer_periph) |= HRTIMER_FLTINCFG3_FLT4BLKEN;
        }
        break;
        case HRTIMER_FAULT_5:
        {
            /* enable fault input 5 blank */
            HRTIMER_FLTINCFG3(hrtimer_periph) |= HRTIMER_FLTINCFG3_FLT5BLKEN;
        }
        break;
        case HRTIMER_FAULT_6:
        {
            /* enable fault input 6 blank */
            HRTIMER_FLTINCFG3(hrtimer_periph) |= HRTIMER_FLTINCFG3_FLT6BLKEN;
        }
        break;
        case HRTIMER_FAULT_7:
        {
            /* enable fault input 7 blank */
            HRTIMER_FLTINCFG3(hrtimer_periph) |= HRTIMER_FLTINCFG3_FLT7BLKEN;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      fault input blank disable
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  fault_id: HRTIMER_FAULT_y(y=0..7)
    \param[out] none
    \retval     none
*/
void hrtimer_fault_blank_disable(uint32_t hrtimer_periph, uint32_t fault_id)
{
    switch (fault_id)
    {
        case HRTIMER_FAULT_0:
        {
            /* disable fault input 0 blank */
            HRTIMER_FLTINCFG2(hrtimer_periph) &= ~HRTIMER_FLTINCFG2_FLT0BLKEN;
        }
        break;
        case HRTIMER_FAULT_1:
        {
            /* disable fault input 1 blank */
            HRTIMER_FLTINCFG2(hrtimer_periph) &= ~HRTIMER_FLTINCFG2_FLT1BLKEN;
        }
        break;
        case HRTIMER_FAULT_2:
        {
            /* disable fault input 2 blank */
            HRTIMER_FLTINCFG2(hrtimer_periph) &= ~HRTIMER_FLTINCFG2_FLT2BLKEN;
        }
        break;
        case HRTIMER_FAULT_3:
        {
            /* disable fault input 3 blank */
            HRTIMER_FLTINCFG2(hrtimer_periph) &= ~HRTIMER_FLTINCFG2_FLT3BLKEN;
        }
        break;
        case HRTIMER_FAULT_4:
        {
            /* disable fault input 4 blank */
            HRTIMER_FLTINCFG3(hrtimer_periph) &= ~HRTIMER_FLTINCFG3_FLT4BLKEN;
        }
        break;
        case HRTIMER_FAULT_5:
        {
            /* disable fault input 5 blank */
            HRTIMER_FLTINCFG3(hrtimer_periph) &= ~HRTIMER_FLTINCFG3_FLT5BLKEN;
        }
        break;
        case HRTIMER_FAULT_6:
        {
            /* disable fault input 6 blank */
            HRTIMER_FLTINCFG3(hrtimer_periph) &= ~HRTIMER_FLTINCFG3_FLT6BLKEN;
        }
        break;
        case HRTIMER_FAULT_7:
        {
            /* disable fault input 7 blank */
            HRTIMER_FLTINCFG3(hrtimer_periph) &= ~HRTIMER_FLTINCFG3_FLT7BLKEN;
        }
        break;
        default:
        break;
    }
}
/*!
    \brief      enable the Master_TIMER and Slave_TIMER DMA request
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  dmareq: DMA request source
                only one parameter can be selected which is shown as below:
      \arg          HRTIMER_MT_ST_DMA_CMP0: compare 0 DMA request, for Master_TIMER and Slave_TIMER
      \arg          HRTIMER_MT_ST_DMA_CMP1: compare 1 DMA request, for Master_TIMER and Slave_TIMER 
      \arg          HRTIMER_MT_ST_DMA_CMP2: compare 2 DMA request, for Master_TIMER and Slave_TIMER 
      \arg          HRTIMER_MT_ST_DMA_CMP3: compare 3 DMA request, for Master_TIMER and Slave_TIMER 
      \arg          HRTIMER_MT_ST_DMA_REP: repetition DMA request, for Master_TIMER and Slave_TIMER 
      \arg          HRTIMER_MT_DMA_SYNID: synchronization input DMA request, for Master_TIMER 
      \arg          HRTIMER_MT_ST_DMA_UPD: update DMA request, for Master_TIMER and Slave_TIMER 
      \arg          HRTIMER_ST_DMA_CAP0: capture 0 DMA request, for Slave_TIMER 
      \arg          HRTIMER_ST_DMA_CAP0: capture 1 DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_CH0OA: channel 0 output active DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_CH0ONA: channel 0 output inactive DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_CH1OA: channel 1 output active DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_CH1ONA: channel 1 output inactive DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_CNTRST: counter reset DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_DLYIDLE: delay IDLE DMA request, for Slave_TIMER  
    \param[out] none
    \retval     none
*/
void hrtimer_timers_dma_enable(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t dmareq)
{
    switch(timer_id)
    {
        /* enable the Master_TIMER request */
        case HRTIMER_MASTER_TIMER:
            HRTIMER_MTDMAINTEN(hrtimer_periph) |= dmareq;
        break;
        /* enable the Slave_TIMER DMA request */
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
            HRTIMER_STXDMAINTEN(hrtimer_periph, timer_id) |= dmareq;
        break;
        
        default:
        break;  
    }
}

/*!
    \brief      disable the Master_TIMER and Slave_TIMER DMA request
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  dmareq: DMA request source
                only one parameter can be selected which is shown as below:
      \arg          HRTIMER_MT_ST_DMA_CMP0: compare 0 DMA request, for Master_TIMER and Slave_TIMER
      \arg          HRTIMER_MT_ST_DMA_CMP1: compare 1 DMA request, for Master_TIMER and Slave_TIMER 
      \arg          HRTIMER_MT_ST_DMA_CMP2: compare 2 DMA request, for Master_TIMER and Slave_TIMER 
      \arg          HRTIMER_MT_ST_DMA_CMP3: compare 3 DMA request, for Master_TIMER and Slave_TIMER 
      \arg          HRTIMER_MT_ST_DMA_REP: repetition DMA request, for Master_TIMER and Slave_TIMER 
      \arg          HRTIMER_MT_DMA_SYNID: synchronization input DMA request, for Master_TIMER 
      \arg          HRTIMER_MT_ST_DMA_UPD: update DMA request, for Master_TIMER and Slave_TIMER 
      \arg          HRTIMER_ST_DMA_CAP0: capture 0 DMA request, for Slave_TIMER 
      \arg          HRTIMER_ST_DMA_CAP0: capture 1 DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_CH0OA: channel 0 output active DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_CH0ONA: channel 0 output inactive DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_CH1OA: channel 1 output active DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_CH1ONA: channel 1 output inactive DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_CNTRST: counter reset DMA request, for Slave_TIMER  
      \arg          HRTIMER_ST_DMA_DLYIDLE: delay IDLE DMA request, for Slave_TIMER  
    \param[out] none
    \retval     none
*/
void hrtimer_timers_dma_disable(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t dmareq)
{
    switch(timer_id)
    {
        /* disable the Master_TIMER request */
        case HRTIMER_MASTER_TIMER:
            HRTIMER_MTDMAINTEN(hrtimer_periph) &= ~dmareq;
        break;
        /* disable the Slave_TIMER request */
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
            HRTIMER_STXDMAINTEN(hrtimer_periph, timer_id) &= ~dmareq;
        break;
        
        default:
        break;  
    }
}

/*!
    \brief      configure the DMA mode for Master_TIMER or Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  regupdate: registers to be updated
                one or more parameters can be selected which is shown as below:
      \arg         HRTIMER_DMAMODE_NONE: No register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_DMAMODE_CTL0: MTCTL0 or STxCTL0 register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_DMAMODE_INTC: MT or STx register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_DMAMODE_DMAINTEN: MTINTC or STxINTC register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_DMAMODE_CNT: MTCNT or STxCNT register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_DMAMODE_CAR: MTCAR or STxCAR register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_DMAMODE_CREP: MTCREP or STxCREP register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_DMAMODE_CMP0V: MTCMP0V or STxCMP0V register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_DMAMODE_CMP1V: MTCMP1V or STxCMP1V register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_DMAMODE_CMP2V: MTCMP2V or STxCMP2V register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_DMAMODE_CMP3V: MTCMP3V or STxCMP3V register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_DMAMODE_DTCTL: STxDTCTL register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_CH0SET: STxCH0SET register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_CH0RST: STxCH0RST register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_CH1SET: STxCH1SET register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_CH1RST: STxCH1RST register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_EXEVFCFG0: STxEXEVFCFG0 register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_EXEVFCFG1: STxEXEVFCFG1 register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_CNTRST: STxCNTRST register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_CSCTL: STxCSCTL register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_CHOCTL: STxCHOCTL register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_FLTCTL: STxFLTCTL register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_CTL1: STxCTL1 register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_EXEVFCFG2: STxEXEVFCFG2 register is updated by DMA mode, only for Slave_TIMER
      \arg         HRTIMER_DMAMODE_ACTL: STxACTL register is updated by DMA mode, only for Slave_TIMER
    \param[out] none
    \retval     none
*/
void hrtimer_dmamode_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t regupdate)
{
    switch (timer_id) 
    {
        /* set the DMA mode update Slave_TIMER0 registers */
        case HRTIMER_SLAVE_TIMER0:
        {
            HRTIMER_DMAUPST0R(hrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Slave_TIMER1 registers */
        case HRTIMER_SLAVE_TIMER1:
        {
            HRTIMER_DMAUPST1R(hrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Slave_TIMER2 registers */
        case HRTIMER_SLAVE_TIMER2:
        {
            HRTIMER_DMAUPST2R(hrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Slave_TIMER3 registers */
        case HRTIMER_SLAVE_TIMER3:
        {
            HRTIMER_DMAUPST3R(hrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Slave_TIMER4 registers */
        case HRTIMER_SLAVE_TIMER4:
        {
            HRTIMER_DMAUPST4R(hrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Slave_TIMER5 registers */
        case HRTIMER_SLAVE_TIMER5:
        {
            HRTIMER_DMAUPST5R(hrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Slave_TIMER6 registers */
        case HRTIMER_SLAVE_TIMER6:
        {
            HRTIMER_DMAUPST6R(hrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Slave_TIMER7 registers */
        case HRTIMER_SLAVE_TIMER7:
        {
            HRTIMER_DMAUPST7R(hrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Master_TIMER registers */
        case HRTIMER_MASTER_TIMER:
        {
            HRTIMER_DMAUPMTR(hrtimer_periph) = regupdate;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      initialize bunch mode configuration struct with a default value
    \param[in]  bmcfg: bunch mode configuration struct
    \param[out] none
    \retval     none
*/
void hrtimer_bunchmode_struct_para_init(hrtimer_bunchmode_parameter_struct* bmcfg)
{
    bmcfg->clock_source = HRTIMER_BUNCHMODE_CLOCKSOURCE_MASTER;
    bmcfg->idle_duration = 0U;
    bmcfg->mode = HRTIMER_BUNCHMODE_SINGLE;
    bmcfg->period = 0U;
    bmcfg->prescaler = HRTIMER_BUNCHMODE_PRESCALER_DIV1;
    bmcfg->shadow = HRTIMER_BUNCHMODEPRELOAD_DISABLED;
    bmcfg->trigger[0] = HRTIMER_BUNCHMODE_TRIGGER_NONE;
    bmcfg->trigger[1] = HRTIMER_BUNCHMODE_TRIGGER_NONE;
}

/*!
    \brief      configure bunch mode for the HRTIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  bmcfg: bunch mode configuration struct
                  mode: HRTIMER_BUNCHMODE_SINGLE, HRTIMER_BUNCHMODE_CONTINOUS
                  clock_source: HRTIMER_BUNCHMODE_CLOCKSOURCE_MASTER, HRTIMER_BUNCHMODE_CLOCKSOURCE_STy(y=0..7), HRTIMER_BUNCHMODE_CLOCKSOURCE_TIMER15_CH0_O,
                           HRTIMER_BUNCHMODE_CLOCKSOURCE_TIMER16_CH0_O,HRTIMER_BUNCHMODE_CLOCKSOURCE_TIMER6_TRGO,
                           HRTIMER_BUNCHMODE_CLOCKSOURCE_HRTIMERCK
                  prescaler: HRTIMER_BUNCHMODE_PRESCALER_DIVy(y=1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768)
                  shadow: HRTIMER_BUNCHMODEPRELOAD_DISABLED, HRTIMER_BUNCHMODEPRELOAD_ENABLED
                  trigger[2]: HRTIMER_BUNCHMODE_TRIGGER_NONE, HRTIMER_BUNCHMODE_TRIGGER_MTRESET, HRTIMER_BUNCHMODE_TRIGGER_MTREPETITION, HRTIMER_BUNCHMODE_TRIGGER_MTCMPy(y=0..3),
                           HRTIMER_BUNCHMODE_TRIGGER_STxRESET(x=0..7), HRTIMER_BUNCHMODE_TRIGGER_STxREPETITION(x=0..7), HRTIMER_BUNCHMODE_TRIGGER_STxCMPy(x=0..7, y=0,1), HRTIMER_BUNCHMODE_TRIGGER_ST0EVENT6,
                           HRTIMER_BUNCHMODE_TRIGGER_ST3EVENT7, HRTIMER_BUNCHMODE_TRIGGER_EVENT6, HRTIMER_BUNCHMODE_TRIGGER_EVENT7, HRTIMER_BUNCHMODE_TRIGGER_CHIP
                  idle_duration: 0x0000~0xFFFF
                  period: 0x0001~0xFFFF
    \param[out] none
    \retval     none
*/
void hrtimer_bunchmode_config(uint32_t hrtimer_periph, hrtimer_bunchmode_parameter_struct* bmcfg)
{
    uint32_t bmctl_reg;

    bmctl_reg = HRTIMER_BMCTL(hrtimer_periph);

    /* set the bunch mode operating mode */
    bmctl_reg &= ~(HRTIMER_BMCTL_BMCTN);
    bmctl_reg |= bmcfg->mode;
    
    /* set the bunch mode clock source */
    bmctl_reg &= ~(HRTIMER_BMCTL_BMCLKS);
    bmctl_reg |= bmcfg->clock_source;
  
    /* set the bunch mode prescaler */
    bmctl_reg &= ~(HRTIMER_BMCTL_BMPSC);
    bmctl_reg |= bmcfg->prescaler;
 
    /* enable/disable bunch mode shadow registers */
    bmctl_reg &= ~(HRTIMER_BMCTL_BMSE);
    bmctl_reg |= bmcfg->shadow;
 
    /* set the bunch mode trigger */
    HRTIMER_BMSTRG(hrtimer_periph)  = (uint32_t)bmcfg->trigger[0] ;
    HRTIMER_BMSTRGA(hrtimer_periph) = (uint32_t)bmcfg->trigger[1] ;
  
    /* set the bunch mode compare value */
    HRTIMER_BMCMPV(hrtimer_periph) = bmcfg->idle_duration;
    
    /* set the bunch mode period */
    HRTIMER_BMCAR(hrtimer_periph) = bmcfg->period;
   
    HRTIMER_BMCTL(hrtimer_periph) = bmctl_reg;
}

/*!
    \brief      enable bunch mode for the HRTIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[out] none
    \retval     none
*/
void hrtimer_bunchmode_enable(uint32_t hrtimer_periph)
{
    HRTIMER_BMCTL(hrtimer_periph) |= HRTIMER_BMCTL_BMEN;
}

/*!
    \brief      disable bunch mode for the HRTIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[out] none
    \retval     none
*/
void hrtimer_bunchmode_disable(uint32_t hrtimer_periph)
{
    HRTIMER_BMCTL(hrtimer_periph) &= ~HRTIMER_BMCTL_BMEN;
}

/*!
    \brief      get bunch mode operating flag
    \param[in]  hrtimer_periph: HRTIMER0
    \param[out] none
    \retval     bunch mode operating state
*/
uint32_t hrtimer_bunchmode_flag_get(uint32_t hrtimer_periph)
{
    uint32_t val = HRTIMER_BUNCHMODE_OPERATION_OFF;
    /* judge bunch mode operating state */
    if(RESET != (HRTIMER_BMCTL(hrtimer_periph) & HRTIMER_BMCTL_BMOPTF)){
        val = HRTIMER_BUNCHMODE_OPERATION_ON;
    }else{
        val = HRTIMER_BUNCHMODE_OPERATION_OFF;
    }
    return val;
}

/*!
    \brief      bunch mode started by software
    \param[in]  hrtimer_periph: HRTIMER0
    \param[out] none
    \retval     bunch mode operating state
*/
void hrtimer_bunchmode_software_start(uint32_t hrtimer_periph)
{
    HRTIMER_BMSTRG(hrtimer_periph) |= HRTIMER_BMSTRG_SWTRG;
}

/*!
    \brief      configure the capture source in Slave_TIMER
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  capturex: HRTIMER_CAPTURE_y(y=0, 1)
    \param[in]  trgsource: capture source
                one or more parameters can be selected which is shown as below:
      \arg         HRTIMER_CAPTURETRIGGER_NONE: Capture trigger is disabled
      \arg         HRTIMER_CAPTURETRIGGER_UPDATE: capture triggered by update event
      \arg         HRTIMER_CAPTURETRIGGER_EXEV_0: capture triggered by external event 0
      \arg         HRTIMER_CAPTURETRIGGER_EXEV_1: capture triggered by external event 1
      \arg         HRTIMER_CAPTURETRIGGER_EXEV_2: capture triggered by external event 2
      \arg         HRTIMER_CAPTURETRIGGER_EXEV_3: capture triggered by external event 3
      \arg         HRTIMER_CAPTURETRIGGER_EXEV_4: capture triggered by external event 4
      \arg         HRTIMER_CAPTURETRIGGER_EXEV_5: capture triggered by external event 5
      \arg         HRTIMER_CAPTURETRIGGER_EXEV_6: capture triggered by external event 6
      \arg         HRTIMER_CAPTURETRIGGER_EXEV_7: capture triggered by external event 7
      \arg         HRTIMER_CAPTURETRIGGER_EXEV_8: capture triggered by external event 8
      \arg         HRTIMER_CAPTURETRIGGER_EXEV_9: capture triggered by external event 9
      \arg         HRTIMER_CAPTURETRIGGER_ST0_ACTIVE: capture triggered by ST0CH0_O output inactive to active transition
      \arg         HRTIMER_CAPTURETRIGGER_ST0_INACTIVE: capture triggered by ST0CH0_O output active to inactive transition
      \arg         HRTIMER_CAPTURETRIGGER_ST0_CMP0: capture triggered by compare 0 event of Slave_TIMER0
      \arg         HRTIMER_CAPTURETRIGGER_ST0_CMP1: capture triggered by compare 1 event of Slave_TIMER0
      \arg         HRTIMER_CAPTURETRIGGER_ST1_ACTIVE: capture triggered by ST1CH0_O output inactive to active transition
      \arg         HRTIMER_CAPTURETRIGGER_ST1_INACTIVE: capture triggered by ST1CH0_O output active to inactive transition
      \arg         HRTIMER_CAPTURETRIGGER_ST1_CMP0: capture triggered by compare 0 event of Slave_TIMER1
      \arg         HRTIMER_CAPTURETRIGGER_ST1_CMP1: capture triggered by compare 1 event of Slave_TIMER1
      \arg         HRTIMER_CAPTURETRIGGER_ST2_ACTIVE: capture triggered by ST2CH0_O output inactive to active transition
      \arg         HRTIMER_CAPTURETRIGGER_ST2_INACTIVE: capture triggered by ST2CH0_O output active to inactive transition
      \arg         HRTIMER_CAPTURETRIGGER_ST2_CMP0: capture triggered by compare 0 event of Slave_TIMER2
      \arg         HRTIMER_CAPTURETRIGGER_ST2_CMP1: capture triggered by compare 1 event of Slave_TIMER2
      \arg         HRTIMER_CAPTURETRIGGER_ST3_ACTIVE: capture triggered by ST3CH0_O output inactive to active transition
      \arg         HRTIMER_CAPTURETRIGGER_ST3_INACTIVE: capture triggered by ST3CH0_O output active to inactive transition
      \arg         HRTIMER_CAPTURETRIGGER_ST3_CMP0: capture triggered by compare 0 event of Slave_TIMER3
      \arg         HRTIMER_CAPTURETRIGGER_ST3_CMP1: capture triggered by compare 1 event of Slave_TIMER3
      \arg         HRTIMER_CAPTURETRIGGER_ST4_ACTIVE: capture triggered by ST4CH0_O output inactive to active transition
      \arg         HRTIMER_CAPTURETRIGGER_ST4_INACTIVE: capture triggered by ST4CH0_O output active to inactive transition
      \arg         HRTIMER_CAPTURETRIGGER_ST4_CMP0: capture triggered by compare 0 event of Slave_TIMER4
      \arg         HRTIMER_CAPTURETRIGGER_ST4_CMP1: capture triggered by compare 1 event of Slave_TIMER4
      \arg         HRTIMER_CAPTURETRIGGER_ST5_ACTIVE: capture triggered by ST5CH0_O output inactive to active transition
      \arg         HRTIMER_CAPTURETRIGGER_ST5_INACTIVE: capture triggered by ST5CH0_O output active to inactive transition
      \arg         HRTIMER_CAPTURETRIGGER_ST5_CMP0: capture triggered by compare 0 event of Slave_TIMER5
      \arg         HRTIMER_CAPTURETRIGGER_ST5_CMP1: capture triggered by compare 1 event of Slave_TIMER5
      \arg         HRTIMER_CAPTURETRIGGER_ST6_ACTIVE: capture triggered by ST6CH0_O output inactive to active transition
      \arg         HRTIMER_CAPTURETRIGGER_ST6_INACTIVE: capture triggered by ST6CH0_O output active to inactive transition
      \arg         HRTIMER_CAPTURETRIGGER_ST6_CMP0: capture triggered by compare 0 event of Slave_TIMER6
      \arg         HRTIMER_CAPTURETRIGGER_ST6_CMP1: capture triggered by compare 1 event of Slave_TIMER6
      \arg         HRTIMER_CAPTURETRIGGER_ST7_ACTIVE: capture triggered by ST7CH0_O output inactive to active transition
      \arg         HRTIMER_CAPTURETRIGGER_ST7_INACTIVE: capture triggered by ST7CH0_O output active to inactive transition
      \arg         HRTIMER_CAPTURETRIGGER_ST7_CMP0: capture triggered by compare 0 event of Slave_TIMER7
      \arg         HRTIMER_CAPTURETRIGGER_ST7_CMP1: capture triggered by compare 1 event of Slave_TIMER7
    \param[out] none
    \retval     none
*/
void hrtimer_slavetimer_capture_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t capturex, uint64_t trgsource)
{
    uint32_t stxcaptrgcom_reg;

    /* get the value of registers */
    stxcaptrgcom_reg = HRTIMER_STXCAPTRGCOM(hrtimer_periph, timer_id);
    
    switch (capturex)
    {
        /* configure the capture 0 unit */
        case HRTIMER_CAPTURE_0:
        {
            /* configure the Slave_TIMER capture 0 trigger event in HRTIMER_STXCAP0TRG register */
            HRTIMER_STXCAP0TRG(hrtimer_periph, timer_id) = (uint32_t)trgsource;
            /* configure the Slave_TIMER capture 0 trigger event in HRTIMER_STXCAPTRGCOM register */
            stxcaptrgcom_reg &= ~0x0000FFFFU;
            stxcaptrgcom_reg |= (uint32_t)(trgsource >> 32U);
            HRTIMER_STXCAPTRGCOM(hrtimer_periph, timer_id) = stxcaptrgcom_reg;
        }
        break;
        /* configure the capture 1 unit */
        case HRTIMER_CAPTURE_1:
        {
            /* configure the Slave_TIMER capture 1 trigger event in HRTIMER_STXCAP1TRG register */
            HRTIMER_STXCAP1TRG(hrtimer_periph, timer_id) = (uint32_t)trgsource;
            /* configure the Slave_TIMER capture 1 trigger event in HRTIMER_STXCAPTRGCOM register */
            stxcaptrgcom_reg &= ~0xFFFF0000U;
            stxcaptrgcom_reg |= (uint32_t)((trgsource & 0xFFFFFFFF00000000U) >> 16U);
            HRTIMER_STXCAPTRGCOM(hrtimer_periph, timer_id) = stxcaptrgcom_reg;
        }
        break;
        default:
        break;
  }
}

/*!
    \brief      configure the capture source in Slave_TIMER  
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  capturex: HRTIMER_CAPTURE_y(y=0, 1)
    \param[out] none
    \retval     none
*/
void hrtimer_slavetimer_capture_software(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t capturex)
{
    switch (capturex)
    {
        /* configure the capture 0 unit */
        case HRTIMER_CAPTURE_0:
        {
            HRTIMER_STXCAP0TRG(hrtimer_periph, timer_id) |= HRTIMER_STXCAP0TRG_CP0BSW;
        }
        break;
        /* configure the capture 1 unit */
        case HRTIMER_CAPTURE_1:
        {
            HRTIMER_STXCAP1TRG(hrtimer_periph, timer_id) |= HRTIMER_STXCAP1TRG_CP1BSW;
        }
        break;
        default:
        break;
  }
}

/*!
    \brief      read the capture value 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  capturex: HRTIMER_CAPTURE_y(y=0, 1)
    \param[out] none
    \retval     capture value
*/
hrtimer_capture_value_struct hrtimer_slavetimer_capture_value_read(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t capturex)
{
    uint32_t cap_val = 0U;
    hrtimer_capture_value_struct captured;
    
    switch (capturex)
    {
        /* read capture 0 value */
        case HRTIMER_CAPTURE_0:
        {
          cap_val        = HRTIMER_STXCAP0V(hrtimer_periph, timer_id) ;
          captured.value = cap_val & 0xFFFFU ;
          captured.dir   = (uint32_t)((cap_val &= HRTIMER_STXCAP0V_DIR) >> 16U);
        }
        break;
        /* read capture 1 value */
        case HRTIMER_CAPTURE_1:
        {
          cap_val        = HRTIMER_STXCAP1V(hrtimer_periph, timer_id) ;
          captured.value = cap_val & 0xFFFFU ;
          captured.dir   = (uint32_t)((cap_val &= HRTIMER_STXCAP1V_DIR) >> 16U);
        }
        break;
        default:
        break;
    }
  
    return captured; 
}

/*!
    \brief      initialize ADC trigger configuration struct with a default value
    \param[in]  triggercfg: ADC trigger configuration struct
    \param[out] none
    \retval     none
*/
void hrtimer_adctrigcfg_struct_para_init(hrtimer_adctrigcfg_parameter_struct* triggercfg)
{
    triggercfg->trigger0_3[0] = HRTIMER_ADCTRGI02_EVENT_NONE;
    triggercfg->trigger0_3[1] = HRTIMER_ADCTRGI02_EVENT_NONE;
    triggercfg->trigger4_9 = HRTIMER_ADC_EXT_TRIG_468_BY_MASTER_CMP0;
    triggercfg->update_source = HRTIMER_ADCTRGI_UPDATE_MT;
}

/*!
    \brief      configure the trigger source to ADC and the update source(0..3)
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  trigger_id: HRTIMER_ADCTRIG_y(y=0..3)
    \param[in]  triggercfg: ADC trigger configuration struct
                  update_source: HRTIMER_ADCTRGI_UPDATE_MT, HRTIMER_ADCTRGI_UPDATE_STx(x=0..7)
                  trigger0_3: 
                    for HRTIMER_ADCTRIG_0 and HRTIMER_ADCTRIG_2:
                           HRTIMER_ADCTRGI02_EVENT_NONE, HRTIMER_ADCTRGI02_EVENT_MTCMPy(y=0..3),
                           HRTIMER_ADCTRGI02_EVENT_MTPER, HRTIMER_ADCTRGI02_EVENT_EXEVy(y=0..4),
                           HRTIMER_ADCTRGI02_EVENT_STxCMPy(x=0..7,y=1..3), 
                           HRTIMER_ADCTRGI02_EVENT_STxPER(x=0..7), HRTIMER_ADCTRGI02_EVENT_STxRST(x=0..7)
                    for HRTIMER_ADCTRIG_1 and HRTIMER_ADCTRIG_3:
                           HRTIMER_ADCTRGI13_EVENT_NONE, HRTIMER_ADCTRGI13_EVENT_MTCMPy(y=0..3), 
                           HRTIMER_ADCTRGI13_EVENT_MTPER,HRTIMER_ADCTRGI13_EVENT_EXEVy(y=5..9),
                           HRTIMER_ADCTRGI13_EVENT_STxCMPy(x=0..7, y=1..3),
                           HRTIMER_ADCTRGI13_EVENT_STxPER(x=0..7), HRTIMER_ADCTRGI13_EVENT_STxRST(x=0..7)
    \param[out] none
    \retval     none
*/
void hrtimer_adc_trigger0_3_config(uint32_t hrtimer_periph, uint32_t trigger_id, hrtimer_adctrigcfg_parameter_struct* triggercfg)
{
    uint32_t comctl0_reg;
    
    comctl0_reg = HRTIMER_CTL0(hrtimer_periph);
    switch (trigger_id)
    {
        /* configure the ADC trigger 0 */
        case HRTIMER_ADCTRIG_0:
        {
            /* configure update source */
            comctl0_reg &= (uint32_t)(~(HRTIMER_CTL0_ADTG0USRC0_2 | HRTIMER_CTL0_ADTG0USRC3));
            comctl0_reg |= ((triggercfg->update_source & 0x7U) << 16U);
            comctl0_reg |= ((triggercfg->update_source & 0x8U) << 25U);
            /* set the HRTIMER_ADCTRIG0 source */
            HRTIMER_ADCTRIGS0(hrtimer_periph)  = (uint32_t)triggercfg->trigger0_3[0];
            HRTIMER_ADCTRIGS0A(hrtimer_periph) = (uint32_t)triggercfg->trigger0_3[1]; 
        }
        break;
        /* configure the ADC trigger 1 */
        case HRTIMER_ADCTRIG_1:
        {
            /* configure update source */
            comctl0_reg &= (uint32_t)(~(HRTIMER_CTL0_ADTG1USRC0_2 | HRTIMER_CTL0_ADTG1USRC3 ));
            comctl0_reg |= ((triggercfg->update_source & 0x7U) << 19U);
            comctl0_reg |= ((triggercfg->update_source & 0x8U) << 26U);
          
            /* set the HRTIMER_ADCTRIG1 source */
            HRTIMER_ADCTRIGS1(hrtimer_periph)  = (uint32_t)triggercfg->trigger0_3[0];
            HRTIMER_ADCTRIGS1A(hrtimer_periph) = (uint32_t)triggercfg->trigger0_3[1];  
        }
        break;
        /* configure the ADC trigger 2 */
        case HRTIMER_ADCTRIG_2:
        {
            /* configure update source */
            comctl0_reg &= (uint32_t)(~(HRTIMER_CTL0_ADTG2USRC0_2 | HRTIMER_CTL0_ADTG2USRC3 ));
            comctl0_reg |= ((triggercfg->update_source & 0x7U) << 22U);
            comctl0_reg |= ((triggercfg->update_source & 0x8U) << 27U);
          
            /* set the HRTIMER_ADCTRIG2 source */
            HRTIMER_ADCTRIGS2(hrtimer_periph)  = (uint32_t)triggercfg->trigger0_3[0];
            HRTIMER_ADCTRIGS2A(hrtimer_periph) = (uint32_t)triggercfg->trigger0_3[1];  
        }
        break;
        /* configure the ADC trigger 3 */
        case HRTIMER_ADCTRIG_3:
        {
            /* configure update source */
            comctl0_reg &= (uint32_t)(~(HRTIMER_CTL0_ADTG3USRC0_2 | HRTIMER_CTL0_ADTG3USRC3 ));
            comctl0_reg |= ((triggercfg->update_source & 0x7U) << 25U);
            comctl0_reg |= ((triggercfg->update_source & 0x8U) << 28U);
          
            /* set the HRTIMER_ADCTRIG3 source */
            HRTIMER_ADCTRIGS3(hrtimer_periph)  = (uint32_t)triggercfg->trigger0_3[0];
            HRTIMER_ADCTRIGS3A(hrtimer_periph) = (uint32_t)triggercfg->trigger0_3[1];  
        }
        break;
        
        default:
        break;
    }
    
    HRTIMER_CTL0(hrtimer_periph) = comctl0_reg;
}

/*!
    \brief      configure the trigger source to ADC and the update source(4..9)
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  trigger_id: HRTIMER_ADCTRIG_y(y=4..9)
    \param[in]  triggercfg: ADC trigger configuration struct
                  update_source: HRTIMER_ADCTRGI_UPDATE_MT, HRTIMER_ADCTRGI_UPDATE_STx(x=0..7)
                  trigger4_9: 
                    for HRTIMER_ADCTRIG_4,HRTIMER_ADCTRIG_6,HRTIMER_ADCTRIG_8:
                           HRTIMER_ADC_EXT_TRIG_468_BY_MASTER_CMP0, HRTIMER_ADC_EXT_TRIG_468_BY_MASTER_CMPy(y=0..3), 
                           HRTIMER_ADC_EXT_TRIG_468_BY_MASTER_PERIOD, HRTIMER_ADC_EXT_TRIG_468_BY_EXEV_y(y=0..4), 
                           HRTIMER_ADC_EXT_TRIG_468_BY_STx_CMPy(x=0..7,y=1..3), 
                           HRTIMER_ADC_EXT_TRIG_468_BY_STx_PERIOD(x=0..7), HRTIMER_ADC_EXT_TRIG_468_BY_STx_RESET(x=0,7)
                    for HRTIMER_ADCTRIG_5,HRTIMER_ADCTRIG_7,HRTIMER_ADCTRIG_9:
                           HRTIMER_ADC_EXT_TRIG_579_BY_MASTER_CMP0, HRTIMER_ADC_EXT_TRIG_579_BY_MASTER_CMPy(y=0..3), 
                           HRTIMER_ADC_EXT_TRIG_579_BY_MASTER_PERIOD, HRTIMER_ADC_EXT_TRIG_579_BY_EXEV_y(y=5..9), 
                           HRTIMER_ADC_EXT_TRIG_579_BY_STx_CMPy(x=0..7,y=1..3), 
                           HRTIMER_ADC_EXT_TRIG_579_BY_STx_PERIOD(x=0..7), HRTIMER_ADC_EXT_TRIG_579_BY_STx_RESET(x=0,7)
    \param[out] none
    \retval     none
*/
void hrtimer_adc_trigger4_9_config(uint32_t hrtimer_periph, uint32_t trigger_id, hrtimer_adctrigcfg_parameter_struct* triggercfg)
{
    uint32_t adctrgupd = 0U;
    uint32_t adcexttrg_reg = 0U;
    uint32_t adcexttrga_reg = 0U;
    switch (trigger_id)
    {
        /* configure the ADC trigger 4 */
        case HRTIMER_ADCTRIG_4:
        {
            /* configure update source */
            adctrgupd &= (uint32_t)(~HRTIMER_ADCTRGUPD_ADTG4USRC);
            adctrgupd |= triggercfg->update_source;
            HRTIMER_ADCTRGUPD(hrtimer_periph) = adctrgupd;
            
            /* set the HRTIMER_ADCTRIG4 source */
            adcexttrg_reg = HRTIMER_ADCEXTTRG(hrtimer_periph);
            adcexttrg_reg &= ~(HRTIMER_ADCEXTTRG_ADC4TRG4_0);
            adcexttrg_reg |= ((triggercfg->trigger4_9)&0x0000001FU);
            HRTIMER_ADCEXTTRG(hrtimer_periph) = adcexttrg_reg;

            adcexttrga_reg = HRTIMER_ADCEXTTRGA(hrtimer_periph);
            adcexttrga_reg &= ~(HRTIMER_ADCEXTTRGA_ADC4TRG5);
            adcexttrga_reg |= (triggercfg->trigger4_9 >> 5U);
            HRTIMER_ADCEXTTRGA(hrtimer_periph) = adcexttrga_reg;
        }
        break;
        /* configure the ADC trigger 5 */
        case HRTIMER_ADCTRIG_5:
        {
            /* configure update source */
            adctrgupd &= (uint32_t)(~HRTIMER_ADCTRGUPD_ADTG5USRC);
            adctrgupd |= ((triggercfg->update_source) << 4U);
            HRTIMER_ADCTRGUPD(hrtimer_periph) = adctrgupd;
            
            /* set the HRTIMER_ADCTRIG4 source */
            adcexttrg_reg = HRTIMER_ADCEXTTRG(hrtimer_periph);
            adcexttrg_reg &= ~(HRTIMER_ADCEXTTRG_ADC5TRG4_0);
            adcexttrg_reg |= ((triggercfg->trigger4_9 & 0x0000001FU) << 5U);
            HRTIMER_ADCEXTTRG(hrtimer_periph) = adcexttrg_reg;

            adcexttrga_reg = HRTIMER_ADCEXTTRGA(hrtimer_periph);
            adcexttrga_reg &= ~(HRTIMER_ADCEXTTRGA_ADC4TRG5);
            adcexttrga_reg |= ((triggercfg->trigger4_9 >> 5U) << 1U);
            HRTIMER_ADCEXTTRGA(hrtimer_periph) = adcexttrga_reg;
        }
        break;
        /* configure the ADC trigger 6 */
        case HRTIMER_ADCTRIG_6:
        {
            /* configure update source */
            adctrgupd &= (uint32_t)(~HRTIMER_ADCTRGUPD_ADTG6USRC);
            adctrgupd |= triggercfg->update_source << 8U;
            HRTIMER_ADCTRGUPD(hrtimer_periph) = adctrgupd;
            
            /* set the HRTIMER_ADCTRIG6 source */
            adcexttrg_reg = HRTIMER_ADCEXTTRG(hrtimer_periph);
            adcexttrg_reg &= ~(HRTIMER_ADCEXTTRG_ADC6TRG4_0);
            adcexttrg_reg |= ((triggercfg->trigger4_9 & 0x0000001FU) << 10U);
            HRTIMER_ADCEXTTRG(hrtimer_periph) = adcexttrg_reg;

            adcexttrga_reg = HRTIMER_ADCEXTTRGA(hrtimer_periph);
            adcexttrga_reg &= ~(HRTIMER_ADCEXTTRGA_ADC4TRG5);
            adcexttrga_reg |= ((triggercfg->trigger4_9 >> 5U) << 2U);
            HRTIMER_ADCEXTTRGA(hrtimer_periph) = adcexttrga_reg;
        }
        break;
        /* configure the ADC trigger 7 */
        case HRTIMER_ADCTRIG_7:
        {
            /* configure update source */
            adctrgupd &= (uint32_t)(~HRTIMER_ADCTRGUPD_ADTG7USRC);
            adctrgupd |= triggercfg->update_source << 12U;
            HRTIMER_ADCTRGUPD(hrtimer_periph) = adctrgupd;

            /* set the HRTIMER_ADCTRIG7 source */
            adcexttrg_reg = HRTIMER_ADCEXTTRG(hrtimer_periph);
            adcexttrg_reg &= ~(HRTIMER_ADCEXTTRG_ADC7TRG4_0);
            adcexttrg_reg |= ((triggercfg->trigger4_9 & 0x0000001FU) << 16U);
            HRTIMER_ADCEXTTRG(hrtimer_periph) = adcexttrg_reg;

            adcexttrga_reg = HRTIMER_ADCEXTTRGA(hrtimer_periph);
            adcexttrga_reg &= ~(HRTIMER_ADCEXTTRGA_ADC4TRG5);
            adcexttrga_reg |= ((triggercfg->trigger4_9 >> 5U) << 3U);
            HRTIMER_ADCEXTTRGA(hrtimer_periph) = adcexttrga_reg;
        }
        break;
        /* configure the ADC trigger 8 */
        case HRTIMER_ADCTRIG_8:
        {
            /* configure update source */
            adctrgupd &= (uint32_t)(~HRTIMER_ADCTRGUPD_ADTG8USRC);
            adctrgupd |= triggercfg->update_source << 16U;
            HRTIMER_ADCTRGUPD(hrtimer_periph) = adctrgupd;
            
            /* set the HRTIMER_ADCTRIG8 source */
            adcexttrg_reg = HRTIMER_ADCEXTTRG(hrtimer_periph);
            adcexttrg_reg &= ~(HRTIMER_ADCEXTTRG_ADC8TRG4_0);
            adcexttrg_reg |= ((triggercfg->trigger4_9 & 0x0000001FU) << 21U);
            HRTIMER_ADCEXTTRG(hrtimer_periph) = adcexttrg_reg;

            adcexttrga_reg = HRTIMER_ADCEXTTRGA(hrtimer_periph);
            adcexttrga_reg &= ~(HRTIMER_ADCEXTTRGA_ADC4TRG5);
            adcexttrga_reg |= ((triggercfg->trigger4_9 >> 5U) << 4U);
            HRTIMER_ADCEXTTRGA(hrtimer_periph) = adcexttrga_reg;
        }
        break;
        /* configure the ADC trigger 9 */
        case HRTIMER_ADCTRIG_9:
        {
            /* configure update source */
            adctrgupd &= (uint32_t)(~HRTIMER_ADCTRGUPD_ADTG9USRC);
            adctrgupd |= triggercfg->update_source << 20U;
            HRTIMER_ADCTRGUPD(hrtimer_periph) = adctrgupd;
            
            /* set the HRTIMER_ADCTRIG9 source */
            adcexttrg_reg = HRTIMER_ADCEXTTRG(hrtimer_periph);
            adcexttrg_reg &= ~(HRTIMER_ADCEXTTRG_ADC9TRG4_0);
            adcexttrg_reg |= ((triggercfg->trigger4_9 & 0x0000001FU) << 26U);
            HRTIMER_ADCEXTTRG(hrtimer_periph) = adcexttrg_reg;

            adcexttrga_reg = HRTIMER_ADCEXTTRGA(hrtimer_periph);
            adcexttrga_reg &= ~(HRTIMER_ADCEXTTRGA_ADC4TRG5);
            adcexttrga_reg |= ((triggercfg->trigger4_9 >> 5U) << 5U);
            HRTIMER_ADCEXTTRGA(hrtimer_periph) = adcexttrga_reg;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      configure the trigger source prescaler of ADC (0..9)
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  trigger_id: HRTIMER_ADCTRIG_y(y=0..9)
    \param[in]  psc: ADC trigger prescaler configuration struct (0x00~0x1F)
    \param[out] none
    \retval     none
*/
void hrtimer_adc_prescaler_config(uint32_t hrtimer_periph, uint32_t trigger_id, uint32_t psc)
{
    uint32_t adcpscr0;
    uint32_t adcpscr1;
    switch (trigger_id)
    {
        /* configure the ADC trigger 0 prescaler */
        case HRTIMER_ADCTRIG_0:
        {
            adcpscr0 = HRTIMER_ADCPSCR0(hrtimer_periph);
            adcpscr0 &= ~(HRTIMER_ADCPSCR0_ADC0PSC);
            adcpscr0 |= (psc);
            HRTIMER_ADCPSCR0(hrtimer_periph) = adcpscr0;
        }
        break;
        /* configure the ADC trigger 1 prescaler */
        case HRTIMER_ADCTRIG_1:
        {
            adcpscr0 = HRTIMER_ADCPSCR0(hrtimer_periph);
            adcpscr0 &= ~(HRTIMER_ADCPSCR0_ADC1PSC);
            adcpscr0 |= (psc << 6U);
            HRTIMER_ADCPSCR0(hrtimer_periph) = adcpscr0;
        }
        break;
        /* configure the ADC trigger 2 prescaler */
        case HRTIMER_ADCTRIG_2:
        {
            adcpscr0 = HRTIMER_ADCPSCR0(hrtimer_periph);
            adcpscr0 &= ~(HRTIMER_ADCPSCR0_ADC2PSC);
            adcpscr0 |= (psc << 12U);
            HRTIMER_ADCPSCR0(hrtimer_periph) = adcpscr0;
        }
        break;
        /* configure the ADC trigger 3 prescaler */
        case HRTIMER_ADCTRIG_3:
        {
            adcpscr0 = HRTIMER_ADCPSCR0(hrtimer_periph);
            adcpscr0 &= ~(HRTIMER_ADCPSCR0_ADC3PSC);
            adcpscr0 |= (psc << 18U);
            HRTIMER_ADCPSCR0(hrtimer_periph) = adcpscr0;
        }
        break;
        /* configure the ADC trigger 4 prescaler */
        case HRTIMER_ADCTRIG_4:
        {
            adcpscr0 = HRTIMER_ADCPSCR0(hrtimer_periph);
            adcpscr0 &= ~(HRTIMER_ADCPSCR0_ADC4PSC);
            adcpscr0 |= (psc << 24U);
            HRTIMER_ADCPSCR0(hrtimer_periph) = adcpscr0;
        }
        break;
        /* configure the ADC trigger 5 prescaler */
        case HRTIMER_ADCTRIG_5:
        {
            adcpscr1 = HRTIMER_ADCPSCR1(hrtimer_periph);
            adcpscr1 &= ~(HRTIMER_ADCPSCR1_ADC5PSC);
            adcpscr1 |= (psc);
            HRTIMER_ADCPSCR1(hrtimer_periph) = adcpscr1;
        }
        break;
        /* configure the ADC trigger 6 prescaler */
        case HRTIMER_ADCTRIG_6:
        {
            adcpscr1 = HRTIMER_ADCPSCR1(hrtimer_periph);
            adcpscr1 &= ~(HRTIMER_ADCPSCR1_ADC6PSC);
            adcpscr1 |= (psc << 6U);
            HRTIMER_ADCPSCR1(hrtimer_periph) = adcpscr1;
        }
        break;
        /* configure the ADC trigger 7 prescaler */
        case HRTIMER_ADCTRIG_7:
        {
            adcpscr1 = HRTIMER_ADCPSCR1(hrtimer_periph);
            adcpscr1 &= ~(HRTIMER_ADCPSCR1_ADC7PSC);
            adcpscr1 |= (psc << 12U);
            HRTIMER_ADCPSCR1(hrtimer_periph) = adcpscr1;
        }
        break;
        /* configure the ADC trigger 8 prescaler */
        case HRTIMER_ADCTRIG_8:
        {
            adcpscr1 = HRTIMER_ADCPSCR1(hrtimer_periph);
            adcpscr1 &= ~(HRTIMER_ADCPSCR1_ADC8PSC);
            adcpscr1 |= (psc << 18U);
            HRTIMER_ADCPSCR1(hrtimer_periph) = adcpscr1;
        }
        break;
        /* configure the ADC trigger 8 prescaler */
        case HRTIMER_ADCTRIG_9:
        {
            adcpscr1 = HRTIMER_ADCPSCR1(hrtimer_periph);
            adcpscr1 &= ~(HRTIMER_ADCPSCR1_ADC9PSC);
            adcpscr1 |= (psc << 24U);
            HRTIMER_ADCPSCR1(hrtimer_periph) = adcpscr1;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      get the Slave_TIMER counter direction
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[out] none
    \retval     DirectionStatus: COUNTER_UP or COUNTER_DOWN
*/
DirectionStatus hrtimer_slavetimer_counter_direction_get(uint32_t hrtimer_periph, uint32_t timer_id)
{
    DirectionStatus direction = COUNTER_UP;
    if(((HRTIMER_STXINTF(hrtimer_periph, timer_id) & HRTIMER_STXINTF_DIR) >> 31U) == COUNTER_UP){
        direction = COUNTER_UP;
    }else{
        direction = COUNTER_DOWN;
    }
    return direction;
}
/*!
    \brief      get the Master_TIMER and Slave_TIMER flag
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  flag: flag source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_MT_ST_FLAG_CMP0: compare 0 flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_FLAG_CMP1: compare 1 flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_FLAG_CMP2: compare 2 flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_FLAG_CMP3: compare 3 flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_FLAG_REP: repetition flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_FLAG_SYNI: synchronization input flag, for Master_TIMER
      \arg         HRTIMER_MT_ST_FLAG_UPD: update flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_ST_FLAG_CAP0: capture 0 flag, for Slave_TIMER
      \arg         HRTIMER_ST_FLAG_CAP1: capture 1 flag, for Slave_TIMER
      \arg         HRTIMER_ST_FLAG_CH0OA: channel 0 output active flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH0ONA: channel 0 output inactive flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH1OA: channel 1 output active flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH1ONA: channel 1 output inactive flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CNTRST: counter reset flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_DLYIDLE: delayed IDLE mode entry flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CBLN: current balanced flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_BLNIDLE: balanced IDLE flag, for Slave_TIMER
      \arg         HRTIMER_ST_FLAG_CH0OUTS: channel 0 output status flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH1OUTS: channel 1 output status flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH0OUT: channel 0 output flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH1OUT: channel 1 output flag, for Slave_TIMER 
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hrtimer_timers_flag_get(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t flag)
{
    FlagStatus flag_val = RESET;
    switch(timer_id)
    {
        /* get the Master_TIMER flag */
        case HRTIMER_MASTER_TIMER:
            if(RESET != (HRTIMER_MTINTF(hrtimer_periph) & flag)){
                flag_val = SET;
            }else{
                flag_val = RESET;
            }
        break;
        /* get the Slave_TIMER flag */
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
            if(RESET != (HRTIMER_STXINTF(hrtimer_periph, timer_id) & flag)){
                flag_val = SET;
            }else{
                flag_val = RESET;
            }
        break;
        
        default:
        break;  
    }
    return flag_val;
}

/*!
    \brief      clear the Master_TIMER and Slave_TIMER flag
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  flag: flag source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_MT_ST_FLAG_CMP0: compare 0 flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_FLAG_CMP1: compare 1 flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_FLAG_CMP2: compare 2 flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_FLAG_CMP3: compare 3 flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_FLAG_REP: repetition flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_FLAG_SYNI: synchronization input flag, for Master_TIMER
      \arg         HRTIMER_MT_ST_FLAG_UPD: update flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_ST_FLAG_CAP0: capture 0 flag, for Slave_TIMER
      \arg         HRTIMER_ST_FLAG_CAP1: capture 1 flag, for Slave_TIMER
      \arg         HRTIMER_ST_FLAG_CH0OA: channel 0 output active flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH0ONA: channel 0 output inactive flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH1OA: channel 1 output active flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH1ONA: channel 1 output inactive flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CNTRST: counter reset flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_DLYIDLE: delayed IDLE mode entry flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CBLN: current balanced flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_BLNIDLE: balanced IDLE flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH0OUTS: channel 0 output state flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH1OUTS: channel 1 output state flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH0OUT: channel 0 output flag, for Slave_TIMER 
      \arg         HRTIMER_ST_FLAG_CH1OUT: channel 1 output flag, for Slave_TIMER 
    \param[out] none
    \retval     none
*/
void hrtimer_timers_flag_clear(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t flag)
{
    switch(timer_id)
    {
        /* clear the Master_TIMER flag */
        case HRTIMER_MASTER_TIMER:
            HRTIMER_MTINTC(hrtimer_periph) |= flag;
        break;
        /* clear the Slave_TIMER flag */
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
            HRTIMER_STXINTC(hrtimer_periph, timer_id) |= flag;
        break;
        default:
        break;
    }
}

/*!
    \brief      get the common interrupt flag
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  flag: flag source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_FLAG_FLT0: fault 0 flag
      \arg         HRTIMER_FLAG_FLT1: fault 1 flag
      \arg         HRTIMER_FLAG_FLT2: fault 2 flag
      \arg         HRTIMER_FLAG_FLT3: fault 3 flag
      \arg         HRTIMER_FLAG_FLT4: fault 4 flag
      \arg         HRTIMER_FLAG_FLT5: fault 5 flag
      \arg         HRTIMER_FLAG_FLT6: fault 6 flag
      \arg         HRTIMER_FLAG_FLT7: fault 7 flag
      \arg         HRTIMER_FLAG_SYSFLT: system fault flag
      \arg         HRTIMER_FLAG_DLLCAL: DLL calibration completed flag
      \arg         HRTIMER_FLAG_BMPER: bunch mode period flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hrtimer_common_flag_get(uint32_t hrtimer_periph, uint32_t flag)
{
    /* judge interrupt status */
    if(RESET != (HRTIMER_INTF(hrtimer_periph) & flag)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear the common interrupt flag
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  flag: flag source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_FLAG_FLT0: fault 0 flag
      \arg         HRTIMER_FLAG_FLT1: fault 1 flag
      \arg         HRTIMER_FLAG_FLT2: fault 2 flag
      \arg         HRTIMER_FLAG_FLT3: fault 3 flag
      \arg         HRTIMER_FLAG_FLT4: fault 4 flag
      \arg         HRTIMER_FLAG_FLT5: fault 5 flag
      \arg         HRTIMER_FLAG_FLT6: fault 6 flag
      \arg         HRTIMER_FLAG_FLT7: fault 7 flag
      \arg         HRTIMER_FLAG_SYSFLT: system fault flag
      \arg         HRTIMER_FLAG_DLLCAL: DLL calibration completed flag
      \arg         HRTIMER_FLAG_BMPER: bunch mode period flag
    \param[out] none
    \retval     none
*/
void hrtimer_common_flag_clear(uint32_t hrtimer_periph, uint32_t flag)
{
    HRTIMER_INTC(hrtimer_periph) |= flag;
}

/*!
    \brief      enable the Master_TIMER and Slave_TIMER interrupt 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_MT_ST_INT_CMP0: compare 0 interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_CMP1: compare 1 interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_CMP2: compare 2 interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_CMP3: compare 3 interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_REP: repetition interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_INT_SYNI: synchronization input interrupt, for Master_TIMER
      \arg         HRTIMER_MT_ST_INT_UPD: update interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_ST_INT_CAP0: capture 0 interrupt, for Slave_TIMER
      \arg         HRTIMER_ST_INT_CAP1: capture 1 interrupt, for Slave_TIMER
      \arg         HRTIMER_ST_INT_CH0OA: channel 0 output active interrupt, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_CH0ONA: channel 0 output inactive interrupt, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_CH1OA: channel 1 output active interrupt, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_CH1ONA: channel 1 output inactive interrupt, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_CNTRST: counter reset interrupt, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_DLYIDLE: delayed IDLE mode entry interrupt, for Slave_TIMER 
    \param[out] none
    \retval     none
*/
void hrtimer_timers_interrupt_enable(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t interrupt)
{
    switch(timer_id)
    {
        /* enable the Master_TIMER interrupt */
        case HRTIMER_MASTER_TIMER:
            HRTIMER_MTDMAINTEN(hrtimer_periph) |= interrupt;
        break;
        /* enable the Slave_TIMER interrupt */
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
            HRTIMER_STXDMAINTEN(hrtimer_periph, timer_id) |= interrupt;
        break;
        
        default:
        break;  
    }
}
/*!
    \brief      disable the Master_TIMER and Slave_TIMER interrupt 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_MT_ST_INT_CMP0: compare 0 interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_CMP1: compare 1 interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_CMP2: compare 2 interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_CMP3: compare 3 interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_REP: repetition interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_INT_SYNI: synchronization input interrupt, for Master_TIMER
      \arg         HRTIMER_MT_ST_INT_UPD: update interrupt, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_ST_INT_CAP0: capture 0 interrupt, for Slave_TIMER
      \arg         HRTIMER_ST_INT_CAP1: capture 1 interrupt, for Slave_TIMER
      \arg         HRTIMER_ST_INT_CH0OA: channel 0 output active interrupt, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_CH0ONA: channel 0 output inactive interrupt, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_CH1OA: channel 1 output active interrupt, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_CH1ONA: channel 1 output inactive interrupt, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_CNTRST: counter reset interrupt, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_DLYIDLE: delayed IDLE mode entry interrupt, for Slave_TIMER 
    \param[out] none
    \retval     none
*/
void hrtimer_timers_interrupt_disable(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t interrupt)
{
    switch(timer_id)
    {
        /* disable the Master_TIMER interrupt */
        case HRTIMER_MASTER_TIMER:
            HRTIMER_MTDMAINTEN(hrtimer_periph) &= ~interrupt;
        break;
        /* disable the Slave_TIMER interrupt */
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
            HRTIMER_STXDMAINTEN(hrtimer_periph, timer_id) &= ~interrupt;
        break;

        default:
        break;  
    }
}

/*!
    \brief      get the Master_TIMER and Slave_TIMER interrupt flag
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_MT_ST_INT_FLAG_CMP0: compare 0 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_FLAG_CMP1: compare 1 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_FLAG_CMP2: compare 2 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_FLAG_CMP3: compare 3 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_FLAG_REP: repetition interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_INT_FLAG_SYNI: synchronization input interrupt flag, for Master_TIMER
      \arg         HRTIMER_MT_ST_INT_FLAG_UPD: update interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_ST_INT_FLAG_CAP0: capture 0 interrupt flag, for Slave_TIMER
      \arg         HRTIMER_ST_INT_FLAG_CAP1: capture 1 interrupt flag, for Slave_TIMER
      \arg         HRTIMER_ST_INT_FLAG_CH0OA: channel 0 output active interrupt flag, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_FLAG_CH0ONA: channel 0 output inactive interrupt flag, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_FLAG_CH1OA: channel 1 output active interrupt flag, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_FLAG_CH1ONA: channel 1 output inactive interrupt flag, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_FLAG_CNTRST: counter reset interrupt flag, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_FLAG_DLYIDLE: delayed IDLE mode entry interrupt flag, for Slave_TIMER 
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hrtimer_timers_interrupt_flag_get(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t interrupt)
{
    FlagStatus flag = RESET;
    uint32_t interflag = 0U;
    uint32_t interen = 0U;
    
    switch(timer_id)
    {
        /* get the Master_TIMER interrupt flag */
        case HRTIMER_MASTER_TIMER:
            interflag = (HRTIMER_MTINTF(hrtimer_periph) & interrupt);
            interen = (HRTIMER_MTDMAINTEN(hrtimer_periph) & interrupt);
            if((RESET != interflag) && (RESET != interen)){
                flag = SET;
            }else{
                flag =  RESET;
            }
        break;
        /* get the Slave_TIMER interrupt flag */
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
            interflag = (HRTIMER_STXINTF(hrtimer_periph, timer_id) & interrupt);
            interen = (HRTIMER_STXDMAINTEN(hrtimer_periph, timer_id) & interrupt);
            if((RESET != interflag) && (RESET != interen)){
                flag =  SET;
            }else{
                flag =  RESET;
            }
        break;
        
        default:
        break;  
    }
    return flag;
}

/*!
    \brief      clear the Master_TIMER and Slave_TIMER interrupt flag
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_MASTER_TIMER, HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_MT_ST_INT_FLAG_CMP0: compare 0 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_FLAG_CMP1: compare 1 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_FLAG_CMP2: compare 2 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_FLAG_CMP3: compare 3 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_ST_INT_FLAG_REP: repetition interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_MT_INT_FLAG_SYNI: synchronization input interrupt flag, for Master_TIMER
      \arg         HRTIMER_MT_ST_INT_FLAG_UPD: update interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         HRTIMER_ST_INT_FLAG_CAP0: capture 0 interrupt flag, for Slave_TIMER
      \arg         HRTIMER_ST_INT_FLAG_CAP1: capture 1 interrupt flag, for Slave_TIMER
      \arg         HRTIMER_ST_INT_FLAG_CH0OA: channel 0 output active interrupt flag, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_FLAG_CH0ONA: channel 0 output inactive interrupt flag, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_FLAG_CH1OA: channel 1 output active interrupt flag, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_FLAG_CH1ONA: channel 1 output inactive interrupt flag, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_FLAG_CNTRST: counter reset interrupt flag, for Slave_TIMER 
      \arg         HRTIMER_ST_INT_FLAG_DLYIDLE: delayed IDLE mode entry interrupt flag, for Slave_TIMER 
    \param[out] none
    \retval     none
*/
void hrtimer_timers_interrupt_flag_clear(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t interrupt)
{
    switch(timer_id)
    {
        /* clear the Master_TIMER interrupt flag */
        case HRTIMER_MASTER_TIMER:
            HRTIMER_MTINTC(hrtimer_periph) |= interrupt;
        break;
        /* clear theSlave_TIMER interrupt flag */
        case HRTIMER_SLAVE_TIMER0:
        case HRTIMER_SLAVE_TIMER1:
        case HRTIMER_SLAVE_TIMER2:
        case HRTIMER_SLAVE_TIMER3:
        case HRTIMER_SLAVE_TIMER4:
        case HRTIMER_SLAVE_TIMER5:
        case HRTIMER_SLAVE_TIMER6:
        case HRTIMER_SLAVE_TIMER7:
            HRTIMER_STXINTC(hrtimer_periph, timer_id) |= interrupt;
        break;
        
        default:
        break;  
    }
}

/*!
    \brief      enable HRTIMER common interrupt 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_INT_FLT0 : fault 0 interrupt enable
      \arg         HRTIMER_INT_FLT1 : fault 1 interrupt enable
      \arg         HRTIMER_INT_FLT2 : fault 2 interrupt enable
      \arg         HRTIMER_INT_FLT3 : fault 3 interrupt enable
      \arg         HRTIMER_INT_FLT4 : fault 4 interrupt enable
      \arg         HRTIMER_INT_FLT5 : fault 5 interrupt enable
      \arg         HRTIMER_INT_FLT6 : fault 6 interrupt enable
      \arg         HRTIMER_INT_FLT7 : fault 7 interrupt enable
      \arg         HRTIMER_INT_SYSFLT: system fault interrupt
      \arg         HRTIMER_INT_DLLCAL: DLL calibration completed interrupt
      \arg         HRTIMER_INT_BMPER: bunch mode period interrupt
    \param[out] none
    \retval     none
*/
void hrtimer_common_interrupt_enable(uint32_t hrtimer_periph, uint32_t interrupt)
{
    HRTIMER_INTEN(hrtimer_periph) |= interrupt;
}

/*!
    \brief      disable HRTIMER common interrupt 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_INT_FLT0: fault 0 interrupt
      \arg         HRTIMER_INT_FLT1: fault 1 interrupt
      \arg         HRTIMER_INT_FLT2: fault 2 interrupt
      \arg         HRTIMER_INT_FLT3: fault 3 interrupt
      \arg         HRTIMER_INT_FLT4: fault 4 interrupt
      \arg         HRTIMER_INT_FLT5: fault 5 interrupt
      \arg         HRTIMER_INT_FLT6: fault 6 interrupt
      \arg         HRTIMER_INT_FLT7: fault 7 interrupt
      \arg         HRTIMER_INT_SYSFLT: system fault interrupt
      \arg         HRTIMER_INT_DLLCAL: DLL calibration completed interrupt
      \arg         HRTIMER_INT_BMPER: bunch mode period interrupt
    \param[out] none
    \retval     none
*/
void hrtimer_common_interrupt_disable(uint32_t hrtimer_periph, uint32_t interrupt)
{
    HRTIMER_INTEN(hrtimer_periph) &= ~interrupt;
}

/*!
    \brief      get the common interrupt flag
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_INT_FLAG_FLT0: fault 0 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT1: fault 1 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT2: fault 2 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT3: fault 3 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT4: fault 4 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT5: fault 5 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT6: fault 6 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT7: fault 7 interrupt flag
      \arg         HRTIMER_INT_FLAG_SYSFLT: system fault interrupt flag
      \arg         HRTIMER_INT_FLAG_DLLCAL: DLL calibration completed interrupt flag
      \arg         HRTIMER_INT_FLAG_BMPER: bunch mode period interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hrtimer_common_interrupt_flag_get(uint32_t hrtimer_periph, uint32_t interrupt)
{
    uint32_t interflag = 0U;
    uint32_t interen = 0U;
    
    /* get the interrupt correlation bit value */
    interflag = (HRTIMER_INTF(hrtimer_periph) & interrupt);
    interen = (HRTIMER_INTEN(hrtimer_periph) & interrupt);
    
    /* get the interrupt flag */
    if((RESET != interflag) && (RESET != interen)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear the common interrupt flag
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         HRTIMER_INT_FLAG_FLT0: fault 0 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT1: fault 1 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT2: fault 2 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT3: fault 3 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT4: fault 4 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT5: fault 5 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT6: fault 6 interrupt flag
      \arg         HRTIMER_INT_FLAG_FLT7: fault 7 interrupt flag
      \arg         HRTIMER_INT_FLAG_SYSFLT: system fault interrupt flag
      \arg         HRTIMER_INT_FLAG_DLLCAL: DLL calibration completed interrupt flag
      \arg         HRTIMER_INT_FLAG_BMPER: bunch mode period interrupt flag
    \param[out] none
    \retval     none
*/
void hrtimer_common_interrupt_flag_clear(uint32_t hrtimer_periph, uint32_t interrupt)
{
    HRTIMER_INTC(hrtimer_periph) |= interrupt;
}

/*!
    \brief      configure Master_TIMER timer base 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  master_baseinit: HRTIMER time base parameters struct
                  period: period value, min value: 3*tHRTIMER_CK clock, max value: 0xFFFF - (1*tHRTIMER_CK)
                  repetitioncounter: the counter repetition value, 0x00~0xFF
                  prescaler: HRTIMER_PRESCALER_MULy(y=32,16,8,4,2),HRTIMER_PRESCALER_DIVy(y=1,2,4)
                  counter_mode: HRTIMER_COUNTER_MODE_CONTINOUS, HRTIMER_COUNTER_MODE_SINGLEPULSE, HRTIMER_COUNTER_MODE_SINGLEPULSE_RETRIGGERABLE
    \param[out] none
    \retval     none
*/
static void master_timer_base_config(uint32_t hrtimer_periph, hrtimer_baseinit_parameter_struct* master_baseinit)
{
    /* set counter clock division */
    HRTIMER_MTCTL0(hrtimer_periph) &= (uint32_t) ~(HRTIMER_MTCTL0_CNTCKDIV2_0);
    HRTIMER_MTCTL0(hrtimer_periph) |= (uint32_t)((master_baseinit->prescaler) & CNTCKDIV2_0_MASK);

    /* set the counter operating mode */
    HRTIMER_MTCTL0(hrtimer_periph) &= (uint32_t) ~(HRTIMER_STXCTL0_CTNM | HRTIMER_STXCTL0_CNTRSTM);
    HRTIMER_MTCTL0(hrtimer_periph) |= (uint32_t)master_baseinit->counter_mode;
  
    /* set the period and repetition registers */
    HRTIMER_MTCAR(hrtimer_periph) = master_baseinit->period;
    HRTIMER_MTCREP(hrtimer_periph) = master_baseinit->repetitioncounter;
}

/*!
    \brief      configure Master_TIMER in waveform mode 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  master_timerinit: waveform mode initialization parameters
                  half_mode: HRTIMER_HALFMODE_DISABLED, HRTIMER_HALFMODE_ENABLED
                  alternate_mode: HRTIMER_ALTERNATE_MODE_DISABLED,HRTIMER_ALTERNATE_MODE_TRIPLE,HRTIMER_ALTERNATE_MODE_QUAD
                  start_sync: HRTIMER_SYNISTART_DISABLED, HRTIMER_SYNISTART_ENABLED
                  reset_sync: HRTIMER_SYNCRESET_DISABLED, HRTIMER_SYNCRESET_ENABLED
                  dac_trigger: HRTIMER_DAC_TRIGGER_NONE, HRTIMER_DAC_TRIGGER_DACTRIGy(y=0..2)
                  shadow: HRTIMER_SHADOW_DISABLED, HRTIMER_SHADOW_ENABLED
                  update_selection: HRTIMER_MT_ST_UPDATE_SELECTION_INDEPENDENT, HRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE, HRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE_UPDATE
                  cnt_bunch: HRTIMER_TIMERBUNCHNMODE_MAINTAINCLOCK, HRTIMER_TIMERBUNCHMODE_RESETCOUNTER
                  repetition_update: HRTIMER_UPDATEONREPETITION_DISABLED, HRTIMER_UPDATEONREPETITION_ENABLED
    \param[out] none
    \retval     none
*/
static void master_timer_waveform_config(uint32_t hrtimer_periph, hrtimer_timerinit_parameter_struct * master_timerinit)
{
    uint32_t mtctl0_reg;
    uint32_t bmctl_reg;

    mtctl0_reg = HRTIMER_MTCTL0(hrtimer_periph);
    bmctl_reg = HRTIMER_BMCTL(hrtimer_periph);
  
    /* configure the half mode */
    mtctl0_reg &= ~(uint32_t)(HRTIMER_MTCTL0_HALFM);
    mtctl0_reg |= master_timerinit->half_mode;
  
    /* configure the alternate mode */
    mtctl0_reg &= ~(uint32_t)(HRTIMER_MTCTL0_ALTM);
    mtctl0_reg |= (master_timerinit->alternate_mode >> 1);
  
    /* configure synchronization input start counter */
    mtctl0_reg &= ~(uint32_t)(HRTIMER_MTCTL0_SYNISTRT);
    mtctl0_reg |= master_timerinit->start_sync;
 
    /* configure synchronization input reset counter */
    mtctl0_reg &= ~(uint32_t)(HRTIMER_MTCTL0_SYNIRST);
    mtctl0_reg |= master_timerinit->reset_sync;
  
    /* configure trigger source to DAC */
    mtctl0_reg &= ~(uint32_t)(HRTIMER_MTCTL0_DACTRGS);
    mtctl0_reg |= master_timerinit->dac_trigger;
  
    /* enable/disable shadow registers */
    mtctl0_reg &= ~(uint32_t)(HRTIMER_MTCTL0_SHWEN);
    mtctl0_reg |= master_timerinit->shadow;
  
    /* update event selection */
    mtctl0_reg &= ~(uint32_t)(HRTIMER_MTCTL0_UPSEL);
    mtctl0_reg |= (master_timerinit->update_selection << 2);
  
    /* enable/disable registers update on repetition event */
    mtctl0_reg &= ~(uint32_t)(HRTIMER_MTCTL0_UPREP);
    mtctl0_reg |= (master_timerinit->repetition_update);
  
    /* set the timer bunch mode */
    bmctl_reg &= ~(HRTIMER_BMCTL_BMMT);
    bmctl_reg |= master_timerinit->cnt_bunch;

    HRTIMER_MTCTL0(hrtimer_periph) = mtctl0_reg;
    HRTIMER_BMCTL(hrtimer_periph) = bmctl_reg;
}

/*!
    \brief      configure Slave_TIMER timer base 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  slave_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  slave_baseinit: HRTIMER time base parameters struct
                  period: period value, min value: 3*tHRTIMER_CK clock, max value: 0xFFFF - (1*tHRTIMER_CK)
                  repetitioncounter: the counter repetition value, 0x00~0xFF
                  prescaler: HRTIMER_PRESCALER_MULy(y=32,16,8,4,2),HRTIMER_PRESCALER_DIVy(y=1,2,4)
                  counter_mode: HRTIMER_COUNTER_MODE_CONTINOUS, HRTIMER_COUNTER_MODE_SINGLEPULSE, HRTIMER_COUNTER_MODE_SINGLEPULSE_RETRIGGERABLE
                  counterdirection: HRTIMER_COUNTER_UP,HRTIMER_COUNTER_CENTER_ALIGNED
    \param[out] none
    \retval     none
*/
static void slave_timer_base_config(uint32_t hrtimer_periph, uint32_t slave_id, hrtimer_baseinit_parameter_struct* slave_baseinit)
{
    /* set counter clock division */
    HRTIMER_STXCTL0(hrtimer_periph, slave_id) &= (uint32_t) ~(HRTIMER_MTCTL0_CNTCKDIV2_0);
    HRTIMER_STXCTL0(hrtimer_periph, slave_id) |= (uint32_t)((slave_baseinit->prescaler) & CNTCKDIV2_0_MASK);

    /* set the counter operating mode */
    HRTIMER_STXCTL0(hrtimer_periph, slave_id) &= (uint32_t) ~(HRTIMER_STXCTL0_CTNM | HRTIMER_STXCTL0_CNTRSTM);
    HRTIMER_STXCTL0(hrtimer_periph, slave_id) |= (uint32_t)slave_baseinit->counter_mode;
  
    /* set the period and repetition registers */
    HRTIMER_STXCTL1(hrtimer_periph, slave_id) &= (uint32_t) ~(HRTIMER_STXCTL1_CAM);
    HRTIMER_STXCTL1(hrtimer_periph, slave_id) |= slave_baseinit->counterdirection;
    
    /* set the period and repetition registers */
    HRTIMER_STXCAR(hrtimer_periph, slave_id) = slave_baseinit->period;
    HRTIMER_STXCREP(hrtimer_periph, slave_id) = slave_baseinit->repetitioncounter;
}

/*!
    \brief      configure Slave_TIMER in waveform mode 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  slave_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  slave_timerinit: waveform mode initialization parameters
                  half_mode: HRTIMER_HALFMODE_DISABLED, HRTIMER_HALFMODE_ENABLED
                  alternate_mode: HRTIMER_ALTERNATE_MODE_DISABLED,HRTIMER_ALTERNATE_MODE_TRIPLE,HRTIMER_ALTERNATE_MODE_QUAD
                  start_sync: HRTIMER_SYNISTART_DISABLED, HRTIMER_SYNISTART_ENABLED
                  reset_sync: HRTIMER_SYNCRESET_DISABLED, HRTIMER_SYNCRESET_ENABLED
                  dac_trigger: HRTIMER_DAC_TRIGGER_NONE, HRTIMER_DAC_TRIGGER_DACTRIGy(y=0..2)
                  shadow: HRTIMER_SHADOW_DISABLED, HRTIMER_SHADOW_ENABLED
                  update_selection: HRTIMER_MT_ST_UPDATE_SELECTION_INDEPENDENT, for Master_TIMER and Slave_TIMER
                                    HRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE,  for Master_TIMER and Slave_TIMER
                                    HRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE_UPDATE, for Master_TIMER and Slave_TIMER
                                    HRTIMER_ST_UPDATE_SELECTION_STXUPINy(y=0..2), for Slave_TIMER
                                    HRTIMER_ST_UPDATE_SELECTION_STXUPINy_UPDATE(y=0..2), for Slave_TIMER
                  cnt_bunch: HRTIMER_TIMERBUNCHNMODE_MAINTAINCLOCK, HRTIMER_TIMERBUNCHMODE_RESETCOUNTER
                  repetition_update: HRTIMER_UPDATEONREPETITION_DISABLED, HRTIMER_UPDATEONREPETITION_ENABLED
                  resynchronized_update:HRTIMER_RSYUPD_DISABLED,HRTIMER_RSYUPD_ENABLED
    \param[out] none
    \retval     none
*/
static void slave_timer_waveform_config(uint32_t hrtimer_periph, uint32_t slave_id, hrtimer_timerinit_parameter_struct * slave_timerinit)
{
    uint32_t stxctl0_reg;
    uint32_t bmctl_reg;

    stxctl0_reg = HRTIMER_STXCTL0(hrtimer_periph, slave_id);
    bmctl_reg = HRTIMER_BMCTL(hrtimer_periph);
  
    /* configure the half mode */
    stxctl0_reg &= ~(uint32_t)(HRTIMER_STXCTL0_HALFM);
    stxctl0_reg |= slave_timerinit->half_mode;

    /* configure the alternate mode */
    stxctl0_reg &= ~(uint32_t)(HRTIMER_STXCTL0_ALTM);
    stxctl0_reg |= slave_timerinit->alternate_mode;
  
    /* configure the Re-synchronized update mode */
    stxctl0_reg &= ~(uint32_t)(HRTIMER_STXCTL0_RSYNUPD);
    stxctl0_reg |= slave_timerinit->resynchronized_update;
  
    /* configure synchronization input start counter */
    stxctl0_reg &= ~(uint32_t)(HRTIMER_STXCTL0_SYNISTRT);
    stxctl0_reg |= slave_timerinit->start_sync;
 
    /* configure synchronization input reset counter */
    stxctl0_reg &= ~(uint32_t)(HRTIMER_STXCTL0_SYNIRST);
    stxctl0_reg |= slave_timerinit->reset_sync;
  
    /* configure trigger source to DAC */
    stxctl0_reg &= ~(uint32_t)(HRTIMER_STXCTL0_DACTRGS);
    stxctl0_reg |= slave_timerinit->dac_trigger;
  
    /* enable/disable shadow registers */
    stxctl0_reg &= ~(uint32_t)(HRTIMER_STXCTL0_SHWEN);
    stxctl0_reg |= slave_timerinit->shadow;
  
    /* update event selection */
    stxctl0_reg &= ~(uint32_t)(HRTIMER_STXCTL0_UPSEL);
    stxctl0_reg |= (slave_timerinit->update_selection);
  
    /* enable/disable registers update on repetition event */
    stxctl0_reg &= ~(uint32_t)(HRTIMER_STXCTL0_UPREP);
    if(HRTIMER_UPDATEONREPETITION_ENABLED == slave_timerinit->repetition_update){
        stxctl0_reg |= (HRTIMER_STXCTL0_UPREP);
    }
    
    /* Set the timer bunch mode */
    switch (slave_id)
    {
        case HRTIMER_SLAVE_TIMER0:
        {
            bmctl_reg &= ~(HRTIMER_BMCTL_BMST0);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 1);
        }
        break;
        case HRTIMER_SLAVE_TIMER1:
        {
            bmctl_reg &= ~(HRTIMER_BMCTL_BMST1);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 2);
        }
        break;
        case HRTIMER_SLAVE_TIMER2:
        {
            bmctl_reg &= ~(HRTIMER_BMCTL_BMST2);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 3);
        }
        break;
        case HRTIMER_SLAVE_TIMER3:
        {
            bmctl_reg &= ~(HRTIMER_BMCTL_BMST3);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 4);
        }
        break;
        case HRTIMER_SLAVE_TIMER4:
        {
            bmctl_reg &= ~(HRTIMER_BMCTL_BMST4);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 5);
        }
        break;
        case HRTIMER_SLAVE_TIMER5:
        {
            bmctl_reg &= ~(HRTIMER_BMCTL_BMST5);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 6);
        }
        break;
        case HRTIMER_SLAVE_TIMER6:
        {
            bmctl_reg &= ~(HRTIMER_BMCTL_BMST6);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 7);
        }
        break;
        case HRTIMER_SLAVE_TIMER7:
        {
            bmctl_reg &= ~(HRTIMER_BMCTL_BMST7);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 8);
        }
        break;
        default:
        break;
    }

    HRTIMER_STXCTL0(hrtimer_periph, slave_id) = stxctl0_reg;
    HRTIMER_BMCTL(hrtimer_periph) = bmctl_reg;
}

/*!
    \brief      configure the an external event channel
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  event_id: HRTIMER_EXEVENT_NONE, HRTIMER_EXEVENT_y(y=0..9)
    \param[in]  eventcfg: external event configuration struct
                  source: HRTIMER_EXEV_SRCy(y=0..3)
                  polarity: HRTIMER_EXEV_POLARITY_HIGH, HRTIMER_EXEV_POLARITY_LOW
                  edge: HRTIMER_EXEV_EDGE_LEVEL, HRTIMER_EXEV_EDGE_RISING, HRTIMER_EXEV_EDGE_FALLING, HRTIMER_EXEV_EDGE_BOTH
                  fast:HRTIMER_EXEV_FAST_DISABLE,HRTIMER_EXEV_FAST_ENABLE
                  digital_filter: 0x0~0xF
    \param[out] none
    \retval     none
*/
static void external_event_config(uint32_t hrtimer_periph, uint32_t event_id, hrtimer_exeventcfg_parameter_struct* eventcfg)
{
    uint32_t exevcfg0_reg;
    uint32_t exevcfg1_reg;
    uint32_t exevdfctl_reg;

    exevcfg0_reg = HRTIMER_EXEVCFG0(hrtimer_periph);
    exevcfg1_reg = HRTIMER_EXEVCFG1(hrtimer_periph);
    exevdfctl_reg = HRTIMER_EXEVDFCTL(hrtimer_periph);
  
    switch (event_id)
    {
        case HRTIMER_EXEVENT_0:
        {
            /* configure external event 0 */
            exevcfg0_reg &= ~(HRTIMER_EXEVCFG0_EXEV0SRC | HRTIMER_EXEVCFG0_EXEV0P | HRTIMER_EXEVCFG0_EXEV0EG|HRTIMER_EXEVCFG0_EXEV0FAST);
            exevcfg0_reg |= eventcfg->source;
            exevcfg0_reg |= eventcfg->polarity;
            exevcfg0_reg |= eventcfg->edge;
            exevcfg0_reg |= eventcfg->fast;
            HRTIMER_EXEVCFG0(hrtimer_periph) = exevcfg0_reg;
        }
        break;
        case HRTIMER_EXEVENT_1:
        {
            /* configure external event 1 */
            exevcfg0_reg &= ~(HRTIMER_EXEVCFG0_EXEV1SRC | HRTIMER_EXEVCFG0_EXEV1P | HRTIMER_EXEVCFG0_EXEV1EG|HRTIMER_EXEVCFG0_EXEV1FAST);
            exevcfg0_reg |= ((eventcfg->source) << 6U);
            exevcfg0_reg |= ((eventcfg->polarity) << 6U);
            exevcfg0_reg |= ((eventcfg->edge) << 6U);
            exevcfg0_reg |= ((eventcfg->fast) << 6U);
            HRTIMER_EXEVCFG0(hrtimer_periph) = exevcfg0_reg;
        }
        break;
        case HRTIMER_EXEVENT_2:
        {
            /* configure external event 2 */
            exevcfg0_reg &= ~(HRTIMER_EXEVCFG0_EXEV2SRC | HRTIMER_EXEVCFG0_EXEV2P | HRTIMER_EXEVCFG0_EXEV2EG|HRTIMER_EXEVCFG0_EXEV2FAST);
            exevcfg0_reg |= ((eventcfg->source) << 12U);
            exevcfg0_reg |= ((eventcfg->polarity) << 12U);
            exevcfg0_reg |= ((eventcfg->edge) << 12U);
            exevcfg0_reg |= ((eventcfg->fast) << 12U);
            HRTIMER_EXEVCFG0(hrtimer_periph) = exevcfg0_reg;
        }
        break;
        case HRTIMER_EXEVENT_3:
        {
            /* configure external event 3 */
            exevcfg0_reg &= ~(HRTIMER_EXEVCFG0_EXEV3SRC | HRTIMER_EXEVCFG0_EXEV3P | HRTIMER_EXEVCFG0_EXEV3EG|HRTIMER_EXEVCFG0_EXEV3FAST);
            exevcfg0_reg |= ((eventcfg->source) << 18U);
            exevcfg0_reg |= ((eventcfg->polarity) << 18U);
            exevcfg0_reg |= ((eventcfg->edge) << 18U);
            exevcfg0_reg |= ((eventcfg->fast) << 18U);
            HRTIMER_EXEVCFG0(hrtimer_periph) = exevcfg0_reg;
        }
        break;
        case HRTIMER_EXEVENT_4:
        {
            /* configure external event 4 */
            exevcfg0_reg &= ~(HRTIMER_EXEVCFG0_EXEV4SRC | HRTIMER_EXEVCFG0_EXEV4P | HRTIMER_EXEVCFG0_EXEV4EG|HRTIMER_EXEVCFG0_EXEV4FAST);
            exevcfg0_reg |= ((eventcfg->source) << 24U);
            exevcfg0_reg |= ((eventcfg->polarity) << 24U);
            exevcfg0_reg |= ((eventcfg->edge) << 24U);
            exevcfg0_reg |= ((eventcfg->fast) << 24U);
            HRTIMER_EXEVCFG0(hrtimer_periph) = exevcfg0_reg;
        }
        break;
        case HRTIMER_EXEVENT_5:
        {
            /* configure external event 5 */
            exevcfg1_reg &= ~(HRTIMER_EXEVCFG1_EXEV5SRC | HRTIMER_EXEVCFG1_EXEV5P | HRTIMER_EXEVCFG1_EXEV5EG);
            exevcfg1_reg |= (eventcfg->source);
            exevcfg1_reg |= (eventcfg->polarity);
            exevcfg1_reg |= (eventcfg->edge);
            exevdfctl_reg &= ~(HRTIMER_EXEVDFCTL_EXEV5FC);
            exevdfctl_reg |= (eventcfg->digital_filter);
            HRTIMER_EXEVCFG1(hrtimer_periph) = exevcfg1_reg;
            HRTIMER_EXEVDFCTL(hrtimer_periph) = exevdfctl_reg;
        }
        break;
        case HRTIMER_EXEVENT_6:
        {
            /* configure external event 6 */
            exevcfg1_reg &= ~(HRTIMER_EXEVCFG1_EXEV6SRC | HRTIMER_EXEVCFG1_EXEV6P | HRTIMER_EXEVCFG1_EXEV6EG);
            exevcfg1_reg |= ((eventcfg->source) << 6U);
            exevcfg1_reg |= ((eventcfg->polarity) << 6U);
            exevcfg1_reg |= ((eventcfg->edge) << 6U);
            exevdfctl_reg &= ~(HRTIMER_EXEVDFCTL_EXEV6FC);
            exevdfctl_reg |= ((eventcfg->digital_filter) << 6U);
            HRTIMER_EXEVCFG1(hrtimer_periph) = exevcfg1_reg;
            HRTIMER_EXEVDFCTL(hrtimer_periph) = exevdfctl_reg;
        }
        break;
        case HRTIMER_EXEVENT_7:
        {
            /* configure external event 7 */
            exevcfg1_reg &= ~(HRTIMER_EXEVCFG1_EXEV7SRC | HRTIMER_EXEVCFG1_EXEV7P | HRTIMER_EXEVCFG1_EXEV7EG);
            exevcfg1_reg |= ((eventcfg->source) << 12U);
            exevcfg1_reg |= ((eventcfg->polarity) << 12U);
            exevcfg1_reg |= ((eventcfg->edge) << 12U);
            exevdfctl_reg &= ~(HRTIMER_EXEVDFCTL_EXEV7FC);
            exevdfctl_reg |= ((eventcfg->digital_filter) << 12U);
            HRTIMER_EXEVCFG1(hrtimer_periph) = exevcfg1_reg;
            HRTIMER_EXEVDFCTL(hrtimer_periph) = exevdfctl_reg;
        }
        break;
        case HRTIMER_EXEVENT_8:
        {
            /* configure external event 8 */
            exevcfg1_reg &= ~(HRTIMER_EXEVCFG1_EXEV8SRC | HRTIMER_EXEVCFG1_EXEV8P | HRTIMER_EXEVCFG1_EXEV8EG);
            exevcfg1_reg |= ((eventcfg->source) << 18U);
            exevcfg1_reg |= ((eventcfg->polarity) << 18U);
            exevcfg1_reg |= ((eventcfg->edge) << 18U);
            exevdfctl_reg &= ~(HRTIMER_EXEVDFCTL_EXEV8FC);
            exevdfctl_reg |= ((eventcfg->digital_filter) << 18U);
            HRTIMER_EXEVCFG1(hrtimer_periph) = exevcfg1_reg;
            HRTIMER_EXEVDFCTL(hrtimer_periph) = exevdfctl_reg;
        }
        break;
        case HRTIMER_EXEVENT_9:
        {
            /* configure external event 9 */
            exevcfg1_reg &= ~(HRTIMER_EXEVCFG1_EXEV9SRC | HRTIMER_EXEVCFG1_EXEV9P | HRTIMER_EXEVCFG1_EXEV9EG);
            exevcfg1_reg |= ((eventcfg->source) << 24U);
            exevcfg1_reg |= ((eventcfg->polarity) << 24U);
            exevcfg1_reg |= ((eventcfg->edge) << 24U);
            exevdfctl_reg &= ~(HRTIMER_EXEVDFCTL_EXEV9FC);
            exevdfctl_reg |= ((eventcfg->digital_filter) << 24U);
            HRTIMER_EXEVCFG1(hrtimer_periph) = exevcfg1_reg;
            HRTIMER_EXEVDFCTL(hrtimer_periph) = exevdfctl_reg;
        }
        break;
        default:
        break;
    }
}


/*!
    \brief      configure the channel output 
    \param[in]  hrtimer_periph: HRTIMER0
    \param[in]  timer_id: HRTIMER_SLAVE_TIMERx(x=0..7)
    \param[in]  channel: HRTIMER_STx_CHy(x=0..7,y=0,1)
    \param[in]  outcfg: channel output configuration struct definitions
                  polarity: HRTIMER_CHANNEL_POLARITY_HIGH, HRTIMER_CHANNEL_POLARITY_LOW
                  set_request: HRTIMER_CHANNEL_SET_NONE, HRTIMER_CHANNEL_SET_RSTSYNI, HRTIMER_CHANNEL_SET_PER, HRTIMER_CHANNEL_SET_CMPy(y=0..3),
                               HRTIMER_CHANNEL_SET_MTPER, HRTIMER_CHANNEL_SET_MTCMPy(y=0..3), HRTIMER_CHANNEL_SET_STEVy(y=0..8), HRTIMER_CHANNELx_SET_STEVy(x=0,1,y=9,10),
                               HRTIMER_CHANNEL_SET_EXEVy(y=0..9), HRTIMER_CHANNEL_SET_UPDATE, HRTIMER_CHANNELx_SET_STCNTRST(x=0,1)
                  reset_request: HRTIMER_CHANNEL_RESET_NONE, HRTIMER_CHANNEL_RESET_RSTSYNI, HRTIMER_CHANNEL_RESET_PER, HRTIMER_CHANNEL_RESET_CMPy(y=0..3),
                               HRTIMER_CHANNEL_RESET_MTPER, HRTIMER_CHANNEL_RESET_MTCMPy(y=0..3), HRTIMER_CHANNEL_RESET_STEVy(y=0..8), HRTIMER_CHANNELx_RESET_STEVy(x=0,1,y=9,10),
                               HRTIMER_CHANNEL_RESET_EXEVy(y=0..9), HRTIMER_CHANNEL_RESET_UPDATE, HRTIMER_CHANNELx_RESET_STCNTRST(x=0,1)
                  idle_bunch: HRTIMER_CHANNEL_BUNCH_IDLE_DISABLE, HRTIMER_CHANNEL_BUNCH_IDLE_ENABLE
                  idle_state: HRTIMER_CHANNEL_IDLESTATE_INACTIVE, HRTIMER_CHANNEL_IDLESTATE_ACTIVE
                  fault_state: HRTIMER_CHANNEL_FAULTSTATE_NONE, HRTIMER_CHANNEL_FAULTSTATE_ACTIVE, HRTIMER_CHANNEL_FAULTSTATE_INACTIVE, HRTIMER_CHANNEL_FAULTSTATE_HIGHZ
                  carrier_mode: HRTIMER_CHANNEL_CARRIER_DISABLED, HRTIMER_CHANNEL_CARRIER_ENABLED
                  deadtime_bunch: HRTIMER_CHANNEL_BUNCH_ENTRY_REGULAR, HRTIMER_CHANNEL_BUNCH_ENTRY_DEADTIME
    \param[out] none
    \retval     none
*/
static void channel_output_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t channel, hrtimer_channel_outputcfg_parameter_struct * outcfg)
{
    uint32_t stxchoctl_reg;
    uint32_t stxcntrsta_reg; 
    uint32_t shift = 0U;
  
    stxchoctl_reg = HRTIMER_STXCHOCTL(hrtimer_periph, timer_id);
    /* configure the output set/reset crossbar */
    switch (channel)
    {
        case HRTIMER_ST0_CH0:
        case HRTIMER_ST1_CH0:
        case HRTIMER_ST2_CH0:
        case HRTIMER_ST3_CH0:
        case HRTIMER_ST4_CH0:
        case HRTIMER_ST5_CH0:
        case HRTIMER_ST6_CH0:
        case HRTIMER_ST7_CH0:
        {
            shift = 0U;
            /* configure the output set request in HRTIMER_STXCH0SET register */
            HRTIMER_STXCH0SET(hrtimer_periph, timer_id) = (uint32_t)(outcfg->set_request);
            /* configure the output set request in HRTIMER_STXCNTRSTA register */
            stxcntrsta_reg = HRTIMER_STXCNTRSTA(hrtimer_periph, timer_id);
            stxcntrsta_reg &= ~0x00130000U;
            stxcntrsta_reg |= (uint32_t)(outcfg->set_request >> 32U);
            HRTIMER_STXCNTRSTA(hrtimer_periph, timer_id) = stxcntrsta_reg;

            /* configure the output reset request in HRTIMER_STXCH0RESET register */
            HRTIMER_STXCH0RST(hrtimer_periph, timer_id) = (uint32_t)(outcfg->reset_request);
            /* configure the output reset request in HRTIMER_STXCNTRSTA register */
            stxcntrsta_reg = HRTIMER_STXCNTRSTA(hrtimer_periph, timer_id);
            stxcntrsta_reg &= ~0x13000000U;
            stxcntrsta_reg |= (uint32_t)(outcfg->reset_request >> 32U);
            HRTIMER_STXCNTRSTA(hrtimer_periph, timer_id) = stxcntrsta_reg;
        }
        break;
        case HRTIMER_ST0_CH1:
        case HRTIMER_ST1_CH1:
        case HRTIMER_ST2_CH1:
        case HRTIMER_ST3_CH1:
        case HRTIMER_ST4_CH1:
        case HRTIMER_ST5_CH1:
        case HRTIMER_ST6_CH1:
        case HRTIMER_ST7_CH1:
        {
            shift = 16U;
            /* configure the output set request in HRTIMER_STXCH1SET register */
            HRTIMER_STXCH1SET(hrtimer_periph, timer_id) = (uint32_t)(outcfg->set_request);
            /* configure the output set request in HRTIMER_STXCNTRSTA register */
            stxcntrsta_reg = HRTIMER_STXCNTRSTA(hrtimer_periph, timer_id);
            stxcntrsta_reg &= ~0x002C0000U;
            stxcntrsta_reg |= (uint32_t)(outcfg->set_request >> 32U);
            HRTIMER_STXCNTRSTA(hrtimer_periph, timer_id) = stxcntrsta_reg;

            /* configure the output reset request in HRTIMER_STXCH1RESET register */
            HRTIMER_STXCH1RST(hrtimer_periph, timer_id) = (uint32_t)(outcfg->reset_request);
            /* configure the output reset request in HRTIMER_STXCNTRSTA register */
            stxcntrsta_reg = HRTIMER_STXCNTRSTA(hrtimer_periph, timer_id);
            stxcntrsta_reg &= ~0x2C000000U;
            stxcntrsta_reg |= (uint32_t)(outcfg->reset_request >> 32U);
            HRTIMER_STXCNTRSTA(hrtimer_periph, timer_id) = stxcntrsta_reg;
        }
        break;
        default:
        break;
    }
    /* clear output config */
    stxchoctl_reg &= ~((HRTIMER_STXCHOCTL_CH0P | HRTIMER_STXCHOCTL_BMCH0IEN | HRTIMER_STXCHOCTL_ISO0 | HRTIMER_STXCHOCTL_CH0FLTOS|\
                     HRTIMER_STXCHOCTL_CH0CSEN | HRTIMER_STXCHOCTL_BMCH0DTI)  << shift);
    
    /* config the polarity */
    stxchoctl_reg |= (outcfg->polarity << shift);
  
    /* channel IDLE enable state config in bunch mode */
    stxchoctl_reg |= (outcfg->idle_bunch << shift);
    
    /* config channel output IDLE state */
    stxchoctl_reg |= (outcfg->idle_state << shift);
    
    /* config the FAULT output state */
    stxchoctl_reg |= (outcfg->fault_state << shift);
    
    /* config the channel carrier-signal mode enable state */
    stxchoctl_reg |= (outcfg->carrier_mode << shift);

    /* config channel dead-time insert in bunch mode */
    stxchoctl_reg |= (outcfg->deadtime_bunch << shift);
  
    HRTIMER_STXCHOCTL(hrtimer_periph, timer_id) = stxchoctl_reg;
}
