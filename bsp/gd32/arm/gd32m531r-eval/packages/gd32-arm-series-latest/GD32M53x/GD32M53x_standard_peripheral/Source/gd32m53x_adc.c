/*!
    \file    gd32m53x_adc.h
    \brief   ADC driver

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

#include "gd32m53x_adc.h"

#define ADC0_CHANNELX_DATA_REGISTER(ch)             (*((uint32_t *)(uint32_t)(ADC0+0xA0U+((ch)*4U))))
#define ADC2_CHANNELX_DATA_REGISTER(ch)             (*((uint32_t *)(uint32_t)(ADC2+0xA0U+((ch)*4U))))
#define ADC_WDACHCFG_WDACHSEL_MASK                  (uint32_t)(0x0FFF0000U)
#define ADC_WDACHCFG_WDACHMODE_MASK                 (uint32_t)(0x00000FFFU)

/*!
    \brief      reset ADC (API_ID(0x0001U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_deinit(uint32_t adc_periph)
{
    switch(adc_periph) {
    case ADC0:
        rcu_periph_reset_enable(RCU_ADC0RST);
        rcu_periph_reset_disable(RCU_ADC0RST);
        break;
    case ADC2:
        rcu_periph_reset_enable(RCU_ADC2RST);
        rcu_periph_reset_disable(RCU_ADC2RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable ADC interface (API_ID(0x0002U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_enable(uint32_t adc_periph)
{
    if(RESET == (ADC_CTL1(adc_periph) & ADC_CTL1_ADCON)) {
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_ADCON;
    }
}

/*!
    \brief      disable ADC interface (API_ID(0x0003U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_disable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ADCON);
}

/*!
    \brief      configure ADC data alignment (API_ID(0x0004U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  data_alignment: data alignment select
                only one parameter can be selected which is shown as below:
      \arg        ADC_DATAALIGN_RIGHT: right alignment (LSB)
      \arg        ADC_DATAALIGN_LEFT: left alignment (MSB)
    \param[out] none
    \retval     none
*/
void adc_data_alignment_config(uint32_t adc_periph, uint32_t data_alignment)
{
    if(ADC_DATAALIGN_RIGHT != data_alignment) {
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_DAL;
    } else {
        ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_DAL);
    }
}

/*!
    \brief      configure ADC resolution (API_ID(0x0005U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  resolution: ADC resolution
                only one parameter can be selected which is shown as below:
      \arg        ADC_RESOLUTION_12B: 12-bit ADC resolution
      \arg        ADC_RESOLUTION_10B: 10-bit ADC resolution
      \arg        ADC_RESOLUTION_8B: 8-bit ADC resolution
      \arg        ADC_RESOLUTION_6B: 6-bit ADC resolution
    \param[out] none
    \retval     none
*/
void adc_resolution_config(uint32_t adc_periph, uint32_t resolution)
{
    uint32_t  adc_ctl1 = 0U;

    adc_ctl1 = ADC_CTL1(adc_periph);
    adc_ctl1 &= ~((uint32_t)ADC_CTL1_DRES);
    adc_ctl1 |= ((uint32_t)resolution & ADC_CTL1_DRES);

    ADC_CTL1(adc_periph) = adc_ctl1;
}

/*!
    \brief      enable self-diagnosis (API_ID(0x0006U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_self_diagnosis_enable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_SDSEN;
}

/*!
    \brief      disable self-diagnosis (API_ID(0x0007U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_self_diagnosis_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= ~(uint32_t)ADC_CTL0_SDSEN;
}

/*!
    \brief      config self-diagnosis (API_ID(0x0008U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  mode: self-diagnosis mode select
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELF_DIAGNOSIS_MODE_ROTATION: rotation mode select for self-diagnosis voltage
      \arg        ADC_SELF_DIAGNOSIS_MODE_FIXED: fixed mode select for self-diagnosis voltage
    \param[in]  voltage_select: configure fix voltage for self-diagnosis conversion
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELF_DIAG_0_V: Uses the voltage of 0 V for self-diagnosis
      \arg        ADC_SELF_DIAG_1_2_VREF: Uses the voltage of reference power supply ��1/2 for self-diagnosis
      \arg        ADC_SELF_DIAG_VREF: Uses the voltage of reference power supply for self-diagnosis
    \param[out] none
    \retval     none
*/
void adc_self_diagnosis_mode_config(uint32_t adc_periph, adc_self_diag_mode_enum mode, adc_self_diag_fixed_voltage_enum voltage_select)
{
    uint32_t adc_ctl0 = 0U;

    adc_ctl0 = ADC_CTL0(adc_periph);

    if(ADC_SELF_DIAGNOSIS_MODE_FIXED == mode) {
        adc_ctl0 |= (uint32_t)ADC_CTL0_SDSFIX;
    } else {
        adc_ctl0 &= ~((uint32_t)ADC_CTL0_SDSFIX);
    }

    adc_ctl0 &= ~ADC_CTL0_SDVOG;
    adc_ctl0 |= (uint32_t)(((uint32_t)voltage_select << 12U) & ADC_CTL0_SDVOG);

    ADC_CTL0(adc_periph) = adc_ctl0;
}

/*!
    \brief      configure disconnection detection assist mode (API_ID(0x0009U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  mode: disconnection detection assist mode select
                only one parameter can be selected which is shown as below:
      \arg        ADC_DISCHARGE_MODE: discharge mode select
      \arg        ADC_PRECHARGE_MODE: precharge mode select
      \arg        ADC_PRECHARGE_DISCHARGE_MODE_DISABLE: disable precharge and discharge mode
    \param[out] none
    \retval     none
*/
void adc_disconnect_detect_mode_config(uint32_t adc_periph, adc_disc_detect_mode_enum mode)
{
    if(mode == ADC_DISCHARGE_MODE) {
        ADC_CTL0(adc_periph) &= ~ADC_CTL0_CHRSEL_MODE;
    } else if(mode == ADC_PRECHARGE_MODE) {
        ADC_CTL0(adc_periph) |= ADC_CTL0_CHRSEL_MODE;
    } else {
        ADC_CTL0(adc_periph) &= ~(uint32_t)ADC_CTL0_CHRSEL;
    }
}

/*!
    \brief      configure disconnect detect period (API_ID(0x000AU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  period: disconnect detect period(0x2~0xF), 0x0~0x1 disable precharge and discharge
    \param[out] none
    \retval     none
*/
void adc_disconnect_detect_period_config(uint32_t adc_periph, uint32_t period)
{
    uint32_t  adc_ctl0 = ADC_CTL0(adc_periph);

    adc_ctl0 &= ~ADC_CTL0_CHRSEL_PERIOD;
    adc_ctl0 |= (uint32_t)((period << 4) & ADC_CTL0_CHRSEL_PERIOD);

    ADC_CTL0(adc_periph) = adc_ctl0;
}

/*!
    \brief      enable automatic clearing data registers (API_ID(0x000BU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_data_auto_clear_enable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) |=  ADC_CTL0_ACDATA;
}

/*!
    \brief      disable automatic clearing data registers (API_ID(0x000CU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_data_auto_clear_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= ~ADC_CTL0_ACDATA;
}

/*!
    \brief      enable automatic setting data registers (API_ID(0x000DU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_data_auto_set_enable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) |=  ADC_CTL0_ASDATA;
}

/*!
    \brief      disable automatic setting data registers (API_ID(0x000EU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_data_auto_set_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= ~ADC_CTL0_ASDATA;
}

/*!
    \brief      configure ADC sample-and-hold channel (API_ID(0x000FU))
    \param[in]  channel: sample-and-hold channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_SH_CHANNEL_IN0: use ADC0_IN0 channel-dedicated sample-and-hold circuits
      \arg        ADC_SH_CHANNEL_IN1: use ADC0_IN1 channel-dedicated sample-and-hold circuits
      \arg        ADC_SH_CHANNEL_IN2: use ADC0_IN2 channel-dedicated sample-and-hold circuits
    \param[in]  ctl: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_sample_hold_channel_config(uint32_t channel, ControlStatus ctl)
{
    uint32_t adc_chctl = 0U;

    adc_chctl = ADC_SHCTL;
    if(ENABLE == ctl) {
        adc_chctl |= channel & ADC_SHCTL_SHEN;
    } else {
        adc_chctl &= ~(channel & ADC_SHCTL_SHEN);
    }

    ADC_SHCTL = adc_chctl;
}

/*!
    \brief      configure ADC sample time for sample-and-hold circuits (API_ID(0x0010U))
    \param[in]  sample_time: 0x08~0xFF. The recommended config value should not be less than 8.
    \param[out] none
    \retval     none
*/
void adc_sh_sample_time_config(uint8_t sample_time)
{
    uint32_t adc_shctl = 0U;

    adc_shctl = ADC_SHCTL;

    adc_shctl &= ~ADC_SHCTL_SHSTIME;
    adc_shctl |= (((uint32_t)sample_time << 24) & ADC_SHCTL_SHSTIME);

    ADC_SHCTL = adc_shctl;
}

/*!
    \brief      configure ADC hold time for sample-and-hold circuits (API_ID(0x0011U))
    \param[in]  hold_time: 0x8~0xF. The recommended config value should not be less than 8.
    \param[out] none
    \retval     none
*/
void adc_sh_hold_time_config(uint8_t hold_time)
{
    uint32_t adc_shctl = 0U;

    adc_shctl = ADC_SHCTL;

    adc_shctl &= ~ADC_SHCTL_SHHTIME;
    adc_shctl |= (((uint32_t)hold_time << 20) & ADC_SHCTL_SHHTIME);

    ADC_SHCTL = adc_shctl;
}

/*!
    \brief      enable ADC constant sampling mode for sample-and-hold circuits (API_ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_sh_constant_sampling_mode_enable(void)
{
    ADC_SHCTL |= ADC_SHCTL_SHMD;
}

/*!
    \brief      disable ADC constant sampling mode for sample-and-hold circuits (API_ID(0x0013U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_sh_constant_sampling_mode_disable(void)
{
    ADC_SHCTL &= ~ADC_SHCTL_SHMD;
}

/*!
    \brief      software start sample-and-hold circuit in constant sampling mode (API_ID(0x0014U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_sh_constant_sampling_start(void)
{
    ADC_SHCTL |= ADC_SHCTL_SHSTART;
}

/*!
    \brief      software end sample-and-hold circuit in constant sampling mode (API_ID(0x0015U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_sh_constant_sampling_stop(void)
{
    ADC_SHCTL |= ADC_SHCTL_SHEND;
}

/*!
    \brief      enable ADC analog watchdog (API_ID(0x0016U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  window: the selected analog watchdog
                only one parameter can be selected which is shown as below:
      \arg        ADC_WATCHDOG_A: enable analog watchdog A
      \arg        ADC_WATCHDOG_B: enable analog watchdog B
      \arg        ADC_WATCHDOG_A_B:enable analog watchdog A & B
    \param[out] none
    \retval     none
*/
void adc_watchdog_enable(uint32_t adc_periph, adc_watchdog_select_enum window)
{
    switch(window) {
    case ADC_WATCHDOG_A:
        ADC_WDCTL(adc_periph) |= (uint32_t)ADC_WDCTL_WDAEN;
        break;
    case ADC_WATCHDOG_B:
        ADC_WDCTL(adc_periph) |= (uint32_t)ADC_WDCTL_WDBEN;
        break;
    case ADC_WATCHDOG_A_B:
        ADC_WDCTL(adc_periph) |= (uint32_t)ADC_WDCTL_WDAEN | ADC_WDCTL_WDBEN;
        break;
    default :
        break;
    }
}

/*!
    \brief      disable ADC analog watchdog (API_ID(0x0017U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  window: the selected analog watchdog
                only one parameter can be selected which is shown as below:
      \arg        ADC_WATCHDOG_A: enable analog watchdog A
      \arg        ADC_WATCHDOG_B: enable analog watchdog B
      \arg        ADC_WATCHDOG_A_B:enable analog watchdog A & B
    \param[out] none
    \retval     none
*/
void adc_watchdog_disable(uint32_t adc_periph, adc_watchdog_select_enum window)
{
    switch(window) {
    case ADC_WATCHDOG_A:
        ADC_WDCTL(adc_periph) &= ~(uint32_t)ADC_WDCTL_WDAEN;
        break;
    case ADC_WATCHDOG_B:
        ADC_WDCTL(adc_periph) &= ~(uint32_t)ADC_WDCTL_WDBEN;
        break;
    case ADC_WATCHDOG_A_B:
        ADC_WDCTL(adc_periph) &= ~(uint32_t)(ADC_WDCTL_WDAEN | ADC_WDCTL_WDBEN);
        break;
    default :
        break;
    }
}

/*!
    \brief      configure ADC analog watchdog A channel (API_ID(0x0018U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INx: select channel ADC_INx, x=0..6 for ADC0, x=0..9 for ADC2
      \arg        ADC_CHANNEL_TEMPERATURE: select temperature sensor channel, for ADC2
      \arg        ADC_CHANNEL_VINT: select internal reference voltage channel, for ADC2
      \arg        ADC_CHANNEL_ALL: select all channel
    \param[in]  compare_mode: watchdog compare conditions mode
                only one parameter parameter can be selected which is shown as below:
      \arg        ADC_OUT_WINDOW: when the WINEN is 0, WDLT[15:0] value > A/D-converted value. when the WINEN is 1, A/D-converted value < WDLT[15:0] value or WDHT[15:0] < A/D-converted value
      \arg        ADC_IN_WINDOW: when the WINEN is 0, WDLT[15:0] value < A/D-converted value. when the WINEN is 1, WDLT[15:0] value < A/D-converted value < WDHT[15:0] value
    \param[out] none
    \retval     none
*/
void adc_watchdog_a_channel_config(uint32_t adc_periph, adc_channel_select_enum channel, adc_watchdog_compare_condition_enum compare_mode)
{
    if(channel < ADC_CHANNEL_ALL) {
        ADC_WDACHCFG(adc_periph) |= ((uint32_t)((uint32_t)0x01U << (channel + 16U)) & ADC_WDACHCFG_WDACHSEL_MASK);
    } else {
        ADC_WDACHCFG(adc_periph) |= ((uint32_t)0x0FFF0000U);
    }

    if(compare_mode == ADC_OUT_WINDOW) {
        if(channel < ADC_CHANNEL_ALL) {
            ADC_WDACHCFG(adc_periph) &= ~((uint32_t)((uint32_t)0x01U << (channel)) & ADC_WDACHCFG_WDACHMODE_MASK);
        } else {
            ADC_WDACHCFG(adc_periph) &= ~((uint32_t)0x00000FFF);
        }
    } else {
        if(channel < ADC_CHANNEL_ALL) {
            ADC_WDACHCFG(adc_periph) |= (uint32_t)((uint32_t)((uint32_t)0x01U << (channel)) & ADC_WDACHCFG_WDACHMODE_MASK);
        } else {
            ADC_WDACHCFG(adc_periph) |= ((uint32_t)0x00000FFF);
        }
    }
}

/*!
    \brief      deselect ADC analog watchdog A channel (API_ID(0x0019U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INx: select channel ADC_INx, x=0..6 for ADC0, x=0..9 for ADC2
      \arg        ADC_CHANNEL_TEMPERATURE: select temperature sensor channel, for ADC2
      \arg        ADC_CHANNEL_VINT: select internal reference voltage channel, for ADC2
      \arg        ADC_CHANNEL_ALL: select all channel
    \param[out] none
    \retval     none
*/
void adc_watchdog_a_channel_deselect(uint32_t adc_periph, adc_channel_select_enum channel)
{
    if(channel < ADC_CHANNEL_ALL) {
        ADC_WDACHCFG(adc_periph) &= ~((uint32_t)((uint32_t)0x01U << (channel + 16U)) & ADC_WDACHCFG_WDACHSEL_MASK);
    } else {
        ADC_WDACHCFG(adc_periph) &= ~((uint32_t)0x0FFF0000U);
    }
}


/*!
    \brief      configure ADC analog watchdog B channel (API_ID(0x001AU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INx: select channel ADC_INx, x=0..6 for ADC0, x=0..9 for ADC2
      \arg        ADC_CHANNEL_TEMPERATURE: select temperature sensor channel, for ADC2
      \arg        ADC_CHANNEL_VINT: select internal reference voltage channel, for ADC2
    \param[in]  compare_mode: watchdog compare conditions mode
                only one parameter parameter can be selected which is shown as below:
      \arg        ADC_OUT_WINDOW: when the WINEN is 0, WDLT[15:0] value > A/D-converted value. when the WINEN is 1, A/D-converted value < WDLT[15:0] value or WDHT[15:0] < A/D-converted value
      \arg        ADC_IN_WINDOW: when the WINEN is 0, WDLT[15:0] value < A/D-converted value. when the WINEN is 1, WDLT[15:0] value < A/D-converted value < WDHT[15:0] value
    \param[out] none
    \retval     none
*/
void adc_watchdog_b_channel_config(uint32_t adc_periph, adc_channel_select_enum channel, adc_watchdog_compare_condition_enum compare_mode)
{
    uint32_t adc_wdgctl = 0U;

    if(channel < ADC_CHANNEL_ALL) {
        adc_wdgctl = ADC_WDCTL(adc_periph);
        adc_wdgctl &= ~ADC_WDCTL_WDBCHSEL;
        adc_wdgctl |= (uint32_t)(((uint32_t)channel << 28) & ADC_WDCTL_WDBCHSEL);
        ADC_WDCTL(adc_periph) = adc_wdgctl;

        if(compare_mode == ADC_OUT_WINDOW) {
            ADC_WDCTL(adc_periph) &= ~ADC_WDCTL_WDBCM;
        } else {
            ADC_WDCTL(adc_periph) |= ADC_WDCTL_WDBCM;
        }
    }
}

/*!
    \brief      configure ADC analog watchdog A threshold (API_ID(0x001BU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  low_threshold: analog watchdog low threshold, 0x0000..0xFFFF
    \param[in]  high_threshold: analog watchdog high threshold, 0x0000..0xFFFF
    \param[out] none
    \retval     none
*/
void adc_watchdog_a_threshold_config(uint32_t adc_periph, uint16_t low_threshold, uint16_t high_threshold)
{
    uint32_t adc_wdat = 0U;

    adc_wdat = ADC_WDATHOLD(adc_periph);

    adc_wdat &= ~(ADC_WDATHOLD_WDALT | ADC_WDATHOLD_WDAHT);
    adc_wdat |= (uint32_t)low_threshold | ((uint32_t)high_threshold << 16U);

    ADC_WDATHOLD(adc_periph) = adc_wdat;
}

/*!
    \brief      configure ADC analog watchdog B threshold (API_ID(0x001CU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  low_threshold: analog watchdog low threshold, 0x0000..0xFFFF
    \param[in]  high_threshold: analog watchdog high threshold, 0x0000..0xFFFF
    \param[out] none
    \retval     none
*/
void adc_watchdog_b_threshold_config(uint32_t adc_periph, uint16_t low_threshold, uint16_t high_threshold)
{
    uint32_t adc_wdbt = 0U;

    adc_wdbt = ADC_WDBTHOLD(adc_periph);
    adc_wdbt &= ~(ADC_WDBTHOLD_WDBLT | ADC_WDBTHOLD_WDBHT);
    adc_wdbt |= (uint32_t)low_threshold | ((uint32_t)high_threshold << 16U);

    ADC_WDBTHOLD(adc_periph) = adc_wdbt;
}

/*!
    \brief      enable ADC analog watchdog window function (API_ID(0x001DU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_watchdog_window_mode_enable(uint32_t adc_periph)
{
    ADC_WDCTL(adc_periph) |= ADC_WDCTL_WINEN;
}

/*!
    \brief      disable ADC analog watchdog window function (API_ID(0x001EU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_watchdog_window_mode_disable(uint32_t adc_periph)
{
    ADC_WDCTL(adc_periph) &= ~ADC_WDCTL_WINEN;
}

/*!
    \brief      configure ADC analog watchdog complex conditions (API_ID(0x001FU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  mode: watchdog A/B complex conditions configuration
                one parameter can be selected which is shown as below:
      \arg        ADC_WATCHDOG_MATCH_A_OR_B: (watchdog A condition matched) OR (watchdog B condition matched)
      \arg        ADC_WATCHDOG_MATCH_A_XOR_B: (watchdog A condition matched) XOR (watchdog B condition matched)
      \arg        ADC_WATCHDOG_MATCH_A_AND_B: (watchdog A condition matched) AND (watchdog B condition matched)
    \param[out] none
    \retval     none
*/
void adc_watchdog_complex_condition_config(uint32_t adc_periph, uint32_t mode)
{
    uint32_t  adc_wdgctl = 0U;

    adc_wdgctl = ADC_WDCTL(adc_periph);
    adc_wdgctl &= ~ADC_WDCTL_WDABCC;
    adc_wdgctl |= (ADC_WDCTL_WDABCC & mode);

    ADC_WDCTL(adc_periph) = adc_wdgctl;
}

/*!
    \brief      configure ADC oversample channel (API_ID(0x0020U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INx: select channel ADC_INx, x=0..6 for ADC0, x=0..9 for ADC2
      \arg        ADC_CHANNEL_TEMPERATURE: select temperature sensor channel, for ADC2
      \arg        ADC_CHANNEL_VINT: select internal reference voltage channel, for ADC2
    \param[in]  ratio: ADC oversampling ratio
                only one parameter can be selected which is shown as below:
      \arg        ADC_OVERSAMPLING_RATIO_MUL_1: oversampling ratio multiple 1
      \arg        ADC_OVERSAMPLING_RATIO_MUL_2: oversampling ratio multiple 2
      \arg        ADC_OVERSAMPLING_RATIO_MUL_3: oversampling ratio multiple 3
      \arg        ADC_OVERSAMPLING_RATIO_MUL_4: oversampling ratio multiple 4
      \arg        ADC_OVERSAMPLING_RATIO_MUL_8: oversampling ratio multiple 8
      \arg        ADC_OVERSAMPLING_RATIO_MUL_16: oversampling ratio multiple 16
      \arg        ADC_OVERSAMPLING_RATIO_MUL_32: oversampling ratio multiple 32
      \arg        ADC_OVERSAMPLING_RATIO_MUL_64: oversampling ratio multiple 64
    \param[out] none
    \retval     none
*/
void adc_oversample_channel_config(uint32_t adc_periph, adc_channel_select_enum channel, uint32_t ratio)
{
    /* configure ADC oversampling ratio */
    if(channel < 8U) {
        ADC_ADDT0(adc_periph) &= ~(ADC_ADDT0_CH0ADDT << (4U * channel));
        ADC_ADDT0(adc_periph) |= (ratio & ADC_ADDT0_CH0ADDT) << (4U * channel);
    } else if(channel < 12U) {
        ADC_ADDT1(adc_periph) &= ~(ADC_ADDT0_CH0ADDT << (4U * (channel - 8U)));
        ADC_ADDT1(adc_periph) |= (ratio & ADC_ADDT0_CH0ADDT) << (4U * (channel - 8U));
    } else {
        /* MISRAC 2004 rule 14.10 */
    }
}

/*!
    \brief      configure ADC oversample mode (API_ID(0x0021U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  mode: A/D conversion data addition mode selection
                only one parameter can be selected which is shown as below:
      \arg        ADC_ACCUMULATION_MODE: accumulation data mode
      \arg        ADC_AVERAGE_MODE: average data mode
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_config(uint32_t adc_periph, adc_oversample_mode_enum mode)
{
    if(ADC_ACCUMULATION_MODE == mode) {
        ADC_CTL0(adc_periph) &= ~(uint32_t)ADC_CTL0_ADDSEL;
    } else {
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_ADDSEL;
    }
}

/*!
    \brief      enable ADC oversample mode (API_ID(0x0022U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_enable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_ADDEN;
}

/*!
    \brief      disable ADC oversample mode (API_ID(0x0023U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= ~(uint32_t)ADC_CTL0_ADDEN;
}

/*!
    \brief      configure the ADC scan mode (API_ID(0x0024U))
    \param[in]  adc_periph: ADCx(x=0,2)
    \param[in]  scan_mode: ADC scan mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1_SCAN_ONCE: Group_pri1 scan once mode
      \arg        ADC_GROUPS_SCAN: Groups scan mode
      \arg        ADC_GROUP_PRI1_SCAN_CONTINUE: Group_pri1 scan continuous mode
    \param[out] none
    \retval     none
*/
void adc_group_scan_mode_config(uint32_t adc_periph, uint32_t scan_mode)
{
    uint32_t temp_mode = 0U;

    temp_mode = ADC_CTL0(adc_periph);
    temp_mode &= ~((uint32_t)ADC_CTL0_GSCAN);
    temp_mode |= (scan_mode & ADC_CTL0_GSCAN);

    ADC_CTL0(adc_periph) = temp_mode ;
}

/*!
    \brief      enable group priority control (API_ID(0x0025U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_group_priority_control_enable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) |=  ADC_CTL0_GPRIEN;
}

/*!
    \brief      disable group priority control (API_ID(0x0026U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_group_priority_control_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= ~ADC_CTL0_GPRIEN;
}

/*!
    \brief      enable A/D conversion operation for Group_pri3 (API_ID(0x0027U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_group_pri3_enable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) |=  ADC_CTL0_GP3EN;
}

/*!
    \brief      disable A/D conversion operation for Group_pri3 (API_ID(0x0028U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_group_pri3_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= ~ADC_CTL0_GP3EN;
}

/*!
    \brief      enable A/D conversion operation for Group_pri4 (API_ID(0x0029U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_group_pri4_enable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) |=  ADC_CTL0_GP4EN;
}

/*!
    \brief      disable A/D conversion operation for Group_pri4 (API_ID(0x002AU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_group_pri4_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= ~ADC_CTL0_GP4EN;
}

/*!
    \brief      enable lowest-priority group scan continuous (API_ID(0x002BU))
    \param[in]  adc_periph: ADCx,x=0,2
    \param[out] none
    \retval     none
*/
void adc_group_lowest_priority_continuous_enable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) |= ADC_CTL0_LPGCNT;
}

/*!
    \brief      disable lowest-priority group scan continuous (API_ID(0x002CU))
    \param[in]  adc_periph: ADCx,x=0,2
    \param[out] none
    \retval     none
*/
void adc_group_lowest_priority_continuous_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= ~ADC_CTL0_LPGCNT;
}

/*!
    \brief      enable low-priority group restart (API_ID(0x002DU))
    \param[in]  adc_periph: ADCx,x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[in]  restart_ch: rescan channel select
      \arg        ADC_RESTART_ON_BEGINNING: rescan the lower priority group scanning from initial channel
      \arg        ADC_RESTART_ON_BREAKING: rescan the lower priority group scanning from the last aborted channel
    \param[out] none
    \retval     none
*/
void adc_group_restart_enable(uint32_t adc_periph, adc_group_select_enum group, adc_restart_channel_enum restart_ch)
{
    switch(group) {
    case ADC_GROUP_PRI2:
        if(restart_ch == ADC_RESTART_ON_BEGINNING) {
            ADC_GPCGF0(adc_periph) &= (~ADC_GPCGF0_GP2RTCH);
        } else {
            ADC_GPCGF0(adc_periph) |= ADC_GPCGF0_GP2RTCH;
        }
        ADC_GPCGF0(adc_periph) |= ADC_GPCGF0_GP2RTEN;
        break;
    case ADC_GROUP_PRI3:
        if(restart_ch == ADC_RESTART_ON_BEGINNING) {
            ADC_GPCGF1(adc_periph) &= (~ADC_GPCGF1_GP3RTCH);
        } else {
            ADC_GPCGF1(adc_periph) |= ADC_GPCGF1_GP3RTCH;
        }
        ADC_GPCGF1(adc_periph) |= ADC_GPCGF1_GP3RTEN;
        break;
    case ADC_GROUP_PRI4:
        if(restart_ch == ADC_RESTART_ON_BEGINNING) {
            ADC_GPCGF1(adc_periph) &= (~ADC_GPCGF1_GP4RTCH);
        } else {
            ADC_GPCGF1(adc_periph) |= ADC_GPCGF1_GP4RTCH;
        }
        ADC_GPCGF1(adc_periph) |= ADC_GPCGF1_GP4RTEN;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable low-priority group restart (API_ID(0x002EU))
    \param[in]  adc_periph: ADCx,x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_restart_disable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI2:
        ADC_GPCGF0(adc_periph) &= (~ADC_GPCGF0_GP2RTEN);
        break;
    case ADC_GROUP_PRI3:
        ADC_GPCGF1(adc_periph) &= (~ADC_GPCGF1_GP3RTEN);
        break;
    case ADC_GROUP_PRI4:
        ADC_GPCGF1(adc_periph) &= (~ADC_GPCGF1_GP4RTEN);
        break;
    default:
        break;
    }
}

/*!
    \brief      select ADC channel for Group_pri x (API_ID(0x002FU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INx: select channel ADC_INx, x=0..6 for ADC0, x=0..9 for ADC2
      \arg        ADC_CHANNEL_TEMPERATURE: select temperature sensor channel, for ADC2
      \arg        ADC_CHANNEL_VINT: select internal reference voltage channel, for ADC2
      \arg        ADC_CHANNEL_ALL: select all channel
    \param[in]  sample_time: 0x02~0xFF. The sample time value 0x02 cycle
    \param[out] none
    \retval     none
*/
void adc_group_channel_config(uint32_t adc_periph, adc_group_select_enum group, adc_channel_select_enum channel, uint32_t sample_time)
{
    uint8_t i = 0U;
    uint32_t chsel_temp = 0U;
    uint32_t sampr_temp = 0U;

    switch(group) {
    case ADC_GROUP_PRI1:
        if(channel < ADC_CHANNEL_ALL) {
            chsel_temp = ADC_CHSEL0(adc_periph);
            chsel_temp |= ((uint32_t)((uint32_t)0x01U << (channel)) & ADC_CHANNEL_GP1_ALL);
            ADC_CHSEL0(adc_periph) = chsel_temp;
        } else {
            ADC_CHSEL0(adc_periph) |= ((uint32_t)0x00000FFFU);
        }
        break;
    case ADC_GROUP_PRI2:
        if(channel < ADC_CHANNEL_ALL) {
            chsel_temp = ADC_CHSEL0(adc_periph);
            chsel_temp |= ((uint32_t)((uint32_t)0x01U << (channel + 16U)) & ADC_CHANNEL_GP2_ALL);
            ADC_CHSEL0(adc_periph) = chsel_temp;
        } else {
            ADC_CHSEL0(adc_periph) |= ((uint32_t)0x0FFF0000U);
        }
        break;
    case ADC_GROUP_PRI3:
        if(channel < ADC_CHANNEL_ALL) {
            chsel_temp = ADC_CHSEL1(adc_periph);
            chsel_temp |= ((uint32_t)((uint32_t)0x01U << (channel)) & ADC_CHANNEL_GP3_ALL);
            ADC_CHSEL1(adc_periph) = chsel_temp;
        } else {
            ADC_CHSEL1(adc_periph) |= ((uint32_t)0x00000FFFU);
        }
        break;
    case ADC_GROUP_PRI4:
        if(channel < ADC_CHANNEL_ALL) {
            chsel_temp = ADC_CHSEL1(adc_periph);
            chsel_temp |= ((uint32_t)((uint32_t)0x01U << (channel + 16U)) & ADC_CHANNEL_GP4_ALL);
            ADC_CHSEL1(adc_periph) = chsel_temp;
        } else {
            ADC_CHSEL1(adc_periph) |= ((uint32_t)0x0FFF0000U);
        }
        break;
    default:
        break;
    }

    i = channel % 4U;
    if(sample_time < 0x02U) {
        sample_time = 0x02U;
    }
    if(channel < 4U) {
        ADC_SAMPR0(adc_periph) &= ~(uint32_t)(ADC_SAMPR0_SPT00 << (i * 8U));
        ADC_SAMPR0(adc_periph) |= (uint32_t)((sample_time & ADC_SAMPR0_SPT00) << (i * 8U));
    } else if(channel < 8U) {
        ADC_SAMPR1(adc_periph) &= ~(uint32_t)(ADC_SAMPR1_SPT04 << (i * 8U));
        ADC_SAMPR1(adc_periph) |= (uint32_t)((sample_time & ADC_SAMPR0_SPT00) << (i * 8U));
    } else if(channel < 12U) {
        ADC_SAMPR2(adc_periph) &= ~(uint32_t)(ADC_SAMPR2_SPT08 << (i * 8U));
        ADC_SAMPR2(adc_periph) |= (uint32_t)((sample_time & ADC_SAMPR0_SPT00) << (i * 8U));
    } else {
        sampr_temp = ((sample_time) | ((sample_time) << 8U) | ((sample_time) << 16U) | ((sample_time) << 24U));
        ADC_SAMPR0(adc_periph) = sampr_temp;
        ADC_SAMPR1(adc_periph) = sampr_temp;
        ADC_SAMPR2(adc_periph) = sampr_temp;
    }
}

/*!
    \brief      deselect ADC group channel (API_ID(0x0030U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INx: select channel ADC_INx, x=0..6 for ADC0, x=0..9 for ADC2
      \arg        ADC_CHANNEL_TEMPERATURE: select temperature sensor channel, for ADC2
      \arg        ADC_CHANNEL_VINT: select internal reference voltage channel, for ADC2
      \arg        ADC_CHANNEL_ALL: select all channel
    \param[out] none
    \retval     none
*/
void adc_group_channel_deselect(uint32_t adc_periph, adc_group_select_enum group, adc_channel_select_enum channel)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        if(channel < ADC_CHANNEL_ALL) {
            ADC_CHSEL0(adc_periph) &= ~(uint32_t)((uint32_t)((uint32_t)0x01U << (channel)) & ADC_CHANNEL_GP1_ALL);
        } else {
            ADC_CHSEL0(adc_periph) &= ~((uint32_t)0x00000FFFU);
        }
        break;
    case ADC_GROUP_PRI2:
        if(channel < ADC_CHANNEL_ALL) {
            ADC_CHSEL0(adc_periph) &= ~((uint32_t)((uint32_t)0x01U << (channel + 16U)) & ADC_CHANNEL_GP2_ALL);
        } else {
            ADC_CHSEL0(adc_periph) &= ~((uint32_t)0x0FFF0000U);
        }
        break;
    case ADC_GROUP_PRI3:
        if(channel < ADC_CHANNEL_ALL) {
            ADC_CHSEL1(adc_periph) &= ~(uint32_t)((uint32_t)((uint32_t)0x01U << (channel)) & ADC_CHANNEL_GP3_ALL);
        } else {
            ADC_CHSEL1(adc_periph) &= ~((uint32_t)0x00000FFFU);
        }
        break;
    case ADC_GROUP_PRI4:
        if(channel < ADC_CHANNEL_ALL) {
            ADC_CHSEL1(adc_periph) &= ~((uint32_t)((uint32_t)0x01U << (channel + 16U)) & ADC_CHANNEL_GP4_ALL);
        } else {
            ADC_CHSEL1(adc_periph) &= ~((uint32_t)0x0FFF0000U);
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      config end of Group_prix conversion round counts flag (API_ID(0x0031U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[in]  num: end of Group_prix conversion round counts, 0~7
    \param[out] none
    \retval     none
*/
void adc_group_end_flag_round_config(uint32_t adc_periph, adc_group_select_enum group, uint8_t num)
{
    uint32_t  adc_eoc_cr = 0U;

    adc_eoc_cr = ADC_EOCCTL(adc_periph);

    switch(group) {
    case ADC_GROUP_PRI1:
        adc_eoc_cr &= ~ADC_EOCCTL_EOC1RCNT;
        adc_eoc_cr |= (((uint32_t)num << 5U) & ADC_EOCCTL_EOC1RCNT);
        break;
    case ADC_GROUP_PRI2:
        adc_eoc_cr &= ~ADC_EOCCTL_EOC2RCNT;
        adc_eoc_cr |= (((uint32_t)num << 13U) & ADC_EOCCTL_EOC2RCNT);
        break;
    case ADC_GROUP_PRI3:
        adc_eoc_cr &= ~ADC_EOCCTL_EOC3RCNT;
        adc_eoc_cr |= (((uint32_t)num << 21U) & ADC_EOCCTL_EOC3RCNT);
        break;
    case ADC_GROUP_PRI4:
        adc_eoc_cr &= ~ADC_EOCCTL_EOC4RCNT;
        adc_eoc_cr |= (((uint32_t)num << 29U) & ADC_EOCCTL_EOC4RCNT);
        break;
    default :
        break;
    }

    ADC_EOCCTL(adc_periph) = adc_eoc_cr;
}

/*!
    \brief      enable ADC external trigger (API_ID(0x0032U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_external_trigger_enable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        ADC_GPCGF0(adc_periph) |= ADC_GPCGF0_G1TRGEN;
        break;
    case ADC_GROUP_PRI2:
        ADC_GPCGF0(adc_periph) |= ADC_GPCGF0_G2TRGEN;
        break;
    case ADC_GROUP_PRI3:
        ADC_GPCGF1(adc_periph) |= ADC_GPCGF1_G3TRGEN;
        break;
    case ADC_GROUP_PRI4:
        ADC_GPCGF1(adc_periph) |= ADC_GPCGF1_G4TRGEN;
        break;
    default:
        break;
    }
}

/*!
    \brief     config ADC external trigger edge (API_ID(0x0033U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[in]  edge_sel: select trigger edge
                only one parameter can be selected which is shown as below:
      \arg        ADC_EXTERNAL_TRIG_RISING_EDGE: rising edge of external trigger enable
      \arg        ADC_EXTERNAL_TRIG_FAILING_EDGE: falling edge of external trigger enable
      \arg        ADC_EXTERNAL_TRIG_BOTH_EDGE: rising and falling edge of external trigger enable
    \param[out] none
    \retval     none
*/
void adc_group_extern_trigger_edge_config(uint32_t adc_periph, adc_group_select_enum group, uint32_t edge_sel)
{
    uint32_t  adc_trigr0 = 0U, adc_trigr1 = 0U;

    adc_trigr0 = ADC_GPCGF0(adc_periph);
    adc_trigr1 = ADC_GPCGF1(adc_periph);

    switch(group) {
    case ADC_GROUP_PRI1:
        adc_trigr0 &= ~ADC_GPCGF0_GP1TRGED;
        adc_trigr0 |= ((edge_sel << 0U) & ADC_GPCGF0_GP1TRGED);
        ADC_GPCGF0(adc_periph) = adc_trigr0;
        break;
    case ADC_GROUP_PRI2:
        adc_trigr0 &= ~ADC_GPCGF0_GP2TRGED;
        adc_trigr0 |= ((edge_sel << 16U) & ADC_GPCGF0_GP2TRGED);
        ADC_GPCGF0(adc_periph) = adc_trigr0;
        break;
    case ADC_GROUP_PRI3:
        adc_trigr1 &= ~ADC_GPCGF1_GP3TRGED;
        adc_trigr1 |= ((edge_sel << 0U) & ADC_GPCGF1_GP3TRGED);
        ADC_GPCGF1(adc_periph) = adc_trigr1;
        break;
    case ADC_GROUP_PRI4:
        adc_trigr1 &= ~ADC_GPCGF1_GP4TRGED;
        adc_trigr1 |= ((edge_sel << 16U) & ADC_GPCGF1_GP4TRGED);
        ADC_GPCGF1(adc_periph) = adc_trigr1;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable ADC external trigger (API_ID(0x0034U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_external_trigger_disable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        ADC_GPCGF0(adc_periph) &= ~ADC_GPCGF0_G1TRGEN;
        break;
    case ADC_GROUP_PRI2:
        ADC_GPCGF0(adc_periph) &= ~ADC_GPCGF0_G2TRGEN;
        break;
    case ADC_GROUP_PRI3:
        ADC_GPCGF1(adc_periph) &= ~ADC_GPCGF1_G3TRGEN;
        break;
    case ADC_GROUP_PRI4:
        ADC_GPCGF1(adc_periph) &= ~ADC_GPCGF1_G4TRGEN;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable ADC synchronous trigger (API_ID(0x0035U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_synchronous_trigger_enable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        ADC_GPCGF0(adc_periph) &= ~ADC_GPCGF0_GP1TRGTY;
        break;
    case ADC_GROUP_PRI2:
        ADC_GPCGF0(adc_periph) &= ~ADC_GPCGF0_GP2TRGTY;
        break;
    case ADC_GROUP_PRI3:
        ADC_GPCGF1(adc_periph) &= ~ADC_GPCGF1_GP3TRGTY;
        break;
    case ADC_GROUP_PRI4:
        ADC_GPCGF1(adc_periph) &= ~ADC_GPCGF1_GP4TRGTY;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure ADC synchronous trigger source (API_ID(0x0036U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[in]  external_trigger_source: trigger source
                only one parameter can be selected which is shown as below:
      \arg        ADC_SYNCTRIG_SOURCE_TIMER0_TRGOF: TIMER0_TRGOF event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER0_TRGUF: TIMER0_TRGUF event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER0_TRGA: TIMER0_TRGA event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER0_TRGB: TIMER0_TRGB event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER0_TRGAB: TIMER0_TRGAB event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER0_TRGAORB: TIMER0_TRGAORB event select (for ADC extend bifurcate trigger source)
      \arg        ADC_SYNCTRIG_SOURCE_TIMER0_TRGO: TIMER0_TRGO event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER7_TRGOF: TIMER7_TRGOF event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER7_TRGUF: TIMER7_TRGUF event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER7_TRGA: TIMER7_TRGA event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER7_TRGB: TIMER7_TRGB event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER7_TRGAB: TIMER7_TRGAB event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER7_TRGAORB: TIMER7_TRGAORB event select (for ADC extend bifurcate trigger source)
      \arg        ADC_SYNCTRIG_SOURCE_TIMER7_TRGO: TIMER7_TRGO event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER1_TRGO: TIMER1_TRGO event select
      \arg        ADC_SYNCTRIG_SOURCE_TIMER2_TRGO: TIMER2_TRGO event select
      \arg        ADC_SYNCTRIG_SOURCE_GPTIMER0_TRGA: GPTIMER0_TRGA event select
      \arg        ADC_SYNCTRIG_SOURCE_GPTIMER0_TRGB: GPTIMER0_TRGB event select
      \arg        ADC_SYNCTRIG_SOURCE_GPTIMER0_TRGAB: GPTIMER0_TRGAB event select (for ADC extend bifurcate trigger source)
      \arg        ADC_SYNCTRIG_SOURCE_GPTIMER1_TRGA: GPTIMER1_TRGA event select
      \arg        ADC_SYNCTRIG_SOURCE_GPTIMER1_TRGB: GPTIMER1_TRGB event select
      \arg        ADC_SYNCTRIG_SOURCE_GPTIMER1_TRGAB: GPTIMER1_TRGAB event select (for ADC extend bifurcate trigger source)
      \arg        ADC_SYNCTRIG_SOURCE_EVIC_EVSEL0: EVIC_EVSEL0 event select
      \arg        ADC_SYNCTRIG_SOURCE_EVIC_EVSEL1: EVIC_EVSEL1 event select
      \arg        ADC_SYNCTRIG_SOURCE_EVIC_EVSEL0_OR_1: EVIC_EVSEL0 or EVIC_EVSEL1 event select
    \param[out] none
    \retval     none
*/
void adc_group_synchronous_trigger_source_config(uint32_t adc_periph, adc_group_select_enum group, uint32_t external_trigger_source)
{
    uint32_t  adc_trigr0 = 0U, adc_trigr1 = 0U;

    adc_trigr0 = ADC_GPCGF0(adc_periph);
    adc_trigr1 = ADC_GPCGF1(adc_periph);

    switch(group) {
    case ADC_GROUP_PRI1:
        adc_trigr0 &= ~ADC_GPCGF0_GP1TRGSRC;
        adc_trigr0 |= ((external_trigger_source << 2) & ADC_GPCGF0_GP1TRGSRC);
        ADC_GPCGF0(adc_periph) = adc_trigr0;
        break;
    case ADC_GROUP_PRI2:
        adc_trigr0 &= ~ADC_GPCGF0_GP2TRGSRC;
        adc_trigr0 |= ((external_trigger_source << 18) & ADC_GPCGF0_GP2TRGSRC);
        ADC_GPCGF0(adc_periph) = adc_trigr0;
        break;
    case ADC_GROUP_PRI3:
        adc_trigr1 &= ~ADC_GPCGF1_GP3TRGSRC;
        adc_trigr1 |= ((external_trigger_source << 2) & ADC_GPCGF1_GP3TRGSRC);
        ADC_GPCGF1(adc_periph) = adc_trigr1;
        break;
    case ADC_GROUP_PRI4:
        adc_trigr1 &= ~ADC_GPCGF1_GP4TRGSRC;
        adc_trigr1 |= ((external_trigger_source << 18) & ADC_GPCGF1_GP4TRGSRC);
        ADC_GPCGF1(adc_periph) = adc_trigr1;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable ADC asynchronous trigger (API_ID(0x0037U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg          ADC_GROUP_PRI1: select Group_pri1
      \arg          ADC_GROUP_PRI2: select Group_pri2
      \arg          ADC_GROUP_PRI3: select Group_pri3
      \arg          ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_asynchronous_trigger_enable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        ADC_GPCGF0(adc_periph) |= ADC_GPCGF0_GP1TRGTY;
        break;
    case ADC_GROUP_PRI2:
        ADC_GPCGF0(adc_periph) |= ADC_GPCGF0_GP2TRGTY;
        break;
    case ADC_GROUP_PRI3:
        ADC_GPCGF1(adc_periph) |= ADC_GPCGF1_GP3TRGTY;
        break;
    case ADC_GROUP_PRI4:
        ADC_GPCGF1(adc_periph) |= ADC_GPCGF1_GP4TRGTY;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable ADC software trigger (API_ID(0x0038U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the channel group class
                only one parameter can be selected which is shown as below:
      \arg          ADC_GROUP_PRI1: select Group_pri1
      \arg          ADC_GROUP_PRI2: select Group_pri2
      \arg          ADC_GROUP_PRI3: select Group_pri3
      \arg          ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_software_trigger_enable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        ADC_EOCCTL(adc_periph) |= ADC_EOCCTL_GP1SWST;
        break;
    case ADC_GROUP_PRI2:
        ADC_EOCCTL(adc_periph) |= ADC_EOCCTL_GP2SWST;
        break;
    case ADC_GROUP_PRI3:
        ADC_EOCCTL(adc_periph) |= ADC_EOCCTL_GP3SWST;
        break;
    case ADC_GROUP_PRI4:
        ADC_EOCCTL(adc_periph) |= ADC_EOCCTL_GP4SWST;
        break;
    default :
        break;
    }
}

/*!
    \brief      software end conversion of all groups (API_ID(0x0039U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     none
*/
void adc_group_software_end_conversion(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) |= ADC_CTL0_SWEND;
}

/*!
    \brief      enable ADC bifurcate trigger mode for Group_pri x (API_ID(0x003AU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg          ADC_GROUP_PRI1: select Group_pri1
      \arg          ADC_GROUP_PRI2: select Group_pri2
      \arg          ADC_GROUP_PRI3: select Group_pri3
      \arg          ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_bifurcate_mode_enable(uint32_t adc_periph, adc_group_select_enum group)
{
    if(group == ADC_GROUP_PRI1) {
        ADC_BITRGCTL(adc_periph) |= ADC_BITRGCTL_GP1BIMEN;
    } else if(group == ADC_GROUP_PRI2) {
        ADC_BITRGCTL(adc_periph) |= ADC_BITRGCTL_GP2BIMEN;
    } else if(group == ADC_GROUP_PRI3) {
        ADC_BITRGCTL(adc_periph) |= ADC_BITRGCTL_GP3BIMEN;
    } else {
        ADC_BITRGCTL(adc_periph) |= ADC_BITRGCTL_GP4BIMEN;
    }
}

/*!
    \brief      disable ADC bifurcate trigger mode for Group_pri x (API_ID(0x003BU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg          ADC_GROUP_PRI1: select Group_pri1
      \arg          ADC_GROUP_PRI2: select Group_pri2
      \arg          ADC_GROUP_PRI3: select Group_pri3
      \arg          ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_bifurcate_mode_disable(uint32_t adc_periph, adc_group_select_enum group)
{
    if(group == ADC_GROUP_PRI1) {
        ADC_BITRGCTL(adc_periph) &= ~ADC_BITRGCTL_GP1BIMEN;
    } else if(group == ADC_GROUP_PRI2) {
        ADC_BITRGCTL(adc_periph) &= ~ADC_BITRGCTL_GP2BIMEN;
    } else if(group == ADC_GROUP_PRI3) {
        ADC_BITRGCTL(adc_periph) &= ~ADC_BITRGCTL_GP3BIMEN;
    } else {
        ADC_BITRGCTL(adc_periph) &= ~ADC_BITRGCTL_GP4BIMEN;
    }
}

/*!
    \brief      ADC bifurcate trigger channel select (API_ID(0x003CU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg          ADC_GROUP_PRI1: select Group_pri1
      \arg          ADC_GROUP_PRI2: select Group_pri2
      \arg          ADC_GROUP_PRI3: select Group_pri3
      \arg          ADC_GROUP_PRI4: select Group_pri4
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INx: select channel ADC_INx, x=0..6 for ADC0, x=0..9 for ADC2
      \arg        ADC_CHANNEL_TEMPERATURE: select temperature sensor channel, for ADC2
      \arg        ADC_CHANNEL_VINT: select internal reference voltage channel, for ADC2
    \param[out] none
    \retval     none
*/
void adc_group_bifurcate_channel_select(uint32_t adc_periph, adc_group_select_enum group, adc_channel_select_enum channel)
{
    uint32_t adc_bifurcate_cr = 0U;

    if(channel < ADC_CHANNEL_ALL) {
        adc_bifurcate_cr = ADC_BITRGCTL(adc_periph);

        if(group == ADC_GROUP_PRI4) {
            adc_bifurcate_cr &= ~ADC_BITRGCTL_GP4BICHSEL;
            adc_bifurcate_cr |= ((((uint32_t)channel) << 27) & ADC_BITRGCTL_GP4BICHSEL);
        } else if(group == ADC_GROUP_PRI3) {
            adc_bifurcate_cr &= ~ADC_BITRGCTL_GP3BICHSEL;
            adc_bifurcate_cr |= ((((uint32_t)channel) << 19) & ADC_BITRGCTL_GP3BICHSEL);
        } else if(group == ADC_GROUP_PRI2) {
            adc_bifurcate_cr &= ~ADC_BITRGCTL_GP2BICHSEL;
            adc_bifurcate_cr |= ((((uint32_t)channel) << 11) & ADC_BITRGCTL_GP2BICHSEL);
        } else {
            adc_bifurcate_cr &= ~ADC_BITRGCTL_GP1BICHSEL;
            adc_bifurcate_cr |= ((((uint32_t)channel) << 3) & ADC_BITRGCTL_GP1BICHSEL);
        }

        ADC_BITRGCTL(adc_periph) = adc_bifurcate_cr;
    }
}

/*!
    \brief      extend bifurcate trigger source select (API_ID(0x003DU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[in]  trigger_source: extend bifurcate trigger source select
                only one parameter can be selected which is shown as below:
      \arg        ADC_SYNCTRIG_SOURCE_TIMER0_TRGAORB: select TIMER0_TRGAORB as bifurcate trigger source for ADCx(x=0,2)
      \arg        ADC_SYNCTRIG_SOURCE_TIMER7_TRGAORB: select TIMER7_TRGAORB as bifurcate trigger source for ADCx(x=0,2)
      \arg        ADC_SYNCTRIG_SOURCE_GPTIMER0_TRGAB: select GPTIMER0_TRGAB as bifurcate trigger source for ADCx(x=0,2)
      \arg        ADC_SYNCTRIG_SOURCE_GPTIMER1_TRGAB: select GPTIMER1_TRGAB as bifurcate trigger source for ADCx(x=0,2)
      \arg        ADC_SYNCTRIG_SOURCE_EVIC_EVSEL0_OR_1: select EVIC_EVSEL0 or EVIC_EVSEL1 for ADC trigger source for ADCx(x=0,2)
    \param[out] none
    \retval     none
*/
void adc_group_bifurcate_extend_trigger_select(uint32_t adc_periph, adc_group_select_enum group, uint32_t trigger_source)
{
    uint32_t adc_trigr = 0U;

    if(group == ADC_GROUP_PRI1) {
        adc_trigr = ADC_GPCGF0(adc_periph);
        adc_trigr &= ~ADC_GPCGF0_GP1TRGSRC;
        adc_trigr |= ((trigger_source << 2) & ADC_GPCGF0_GP1TRGSRC);
        ADC_GPCGF0(adc_periph) = adc_trigr;
    } else if(group == ADC_GROUP_PRI2) {
        adc_trigr = ADC_GPCGF0(adc_periph);
        adc_trigr &= ~ADC_GPCGF0_GP2TRGSRC;
        adc_trigr |= ((trigger_source << 18) & ADC_GPCGF0_GP2TRGSRC);
        ADC_GPCGF0(adc_periph) = adc_trigr;
    } else if(group == ADC_GROUP_PRI3) {
        adc_trigr = ADC_GPCGF1(adc_periph);
        adc_trigr &= ~ADC_GPCGF1_GP3TRGSRC;
        adc_trigr |= ((trigger_source << 2) & ADC_GPCGF1_GP3TRGSRC);
        ADC_GPCGF1(adc_periph) = adc_trigr;
    } else {
        adc_trigr = ADC_GPCGF1(adc_periph);
        adc_trigr &= ~ADC_GPCGF1_GP4TRGSRC;
        adc_trigr |= ((trigger_source << 18) & ADC_GPCGF1_GP4TRGSRC);
        ADC_GPCGF1(adc_periph) = adc_trigr;
    }
}

/*!
    \brief      enable restore of the next trigger during the current A/D conversion round (API_ID(0x003EU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_bifurcate_trigger_restart_enable(uint32_t adc_periph, adc_group_select_enum group)
{
    if(group == ADC_GROUP_PRI1) {
        ADC_BITRGCTL(adc_periph) |= ADC_BITRGCTL_GP1BITGRS;
    } else if(group == ADC_GROUP_PRI2) {
        ADC_BITRGCTL(adc_periph) |= ADC_BITRGCTL_GP2BITGRS;
    } else if(group == ADC_GROUP_PRI3) {
        ADC_BITRGCTL(adc_periph) |= ADC_BITRGCTL_GP3BITGRS;
    } else {
        ADC_BITRGCTL(adc_periph) |= ADC_BITRGCTL_GP4BITGRS;
    }
}

/*!
    \brief      disable restore of the next trigger during the current A/D conversion round (API_ID(0x003FU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg          ADC_GROUP_PRI1: select Group_pri1
      \arg          ADC_GROUP_PRI2: select Group_pri2
      \arg          ADC_GROUP_PRI3: select Group_pri3
      \arg          ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_bifurcate_trigger_restart_disable(uint32_t adc_periph, adc_group_select_enum group)
{
    if(group == ADC_GROUP_PRI1) {
        ADC_BITRGCTL(adc_periph) &= ~ADC_BITRGCTL_GP1BITGRS;
    } else if(group == ADC_GROUP_PRI2) {
        ADC_BITRGCTL(adc_periph) &= ~ADC_BITRGCTL_GP2BITGRS;
    } else if(group == ADC_GROUP_PRI3) {
        ADC_BITRGCTL(adc_periph) &= ~ADC_BITRGCTL_GP3BITGRS;
    } else {
        ADC_BITRGCTL(adc_periph) &= ~ADC_BITRGCTL_GP4BITGRS;
    }
}

/*!
    \brief      enable DMA request (API_ID(0x0040U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_dma_mode_enable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_DMAEN1;
        break;
    case ADC_GROUP_PRI2:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_DMAEN2;
        break;
    case ADC_GROUP_PRI3:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_DMAEN3 ;
        break;
    case ADC_GROUP_PRI4:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_DMAEN4 ;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable DMA request (API_ID(0x0041U))
    \param[in]  adc_periph: ADCx,x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_dma_mode_disable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        ADC_DMACTL(adc_periph) &= ~(uint32_t) ADC_DMACTL_DMAEN1;
        break;
    case ADC_GROUP_PRI2:
        ADC_DMACTL(adc_periph) &= ~(uint32_t) ADC_DMACTL_DMAEN2;
        break;
    case ADC_GROUP_PRI3:
        ADC_DMACTL(adc_periph) &= ~(uint32_t) ADC_DMACTL_DMAEN3;
        break;
    case ADC_GROUP_PRI4:
        ADC_DMACTL(adc_periph) &= ~(uint32_t) ADC_DMACTL_DMAEN4;
        break;
    default:
        break;
    }
}

/*!
    \brief      when DMAENx=1, the DMA engine issues request at end of conversion of Group_prix (API_ID(0x0042U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_dma_request_after_last_enable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_GP1DDM;
        break;
    case ADC_GROUP_PRI2:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_GP2DDM;
        break;
    case ADC_GROUP_PRI3:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_GP3DDM;
        break;
    case ADC_GROUP_PRI4:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_GP4DDM;
        break;
    default:
        break;
    }
}

/*!
    \brief      the DMA engine is disabled after the end of transfer signal from DMA controller is detected (API_ID(0x0043U))
    \param[in]  adc_periph: ADCx,x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_dma_request_after_last_disable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)ADC_DMACTL_GP1DDM;
        break;
    case ADC_GROUP_PRI2:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)ADC_DMACTL_GP2DDM;
        break;
    case ADC_GROUP_PRI3:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)ADC_DMACTL_GP3DDM;
        break;
    case ADC_GROUP_PRI4:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)ADC_DMACTL_GP4DDM;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable dma overrun detect (API_ID(0x0044U))
    \param[in]  adc_periph: ADCx,x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_dma_overrun_detect_enable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        ADC_DMACTL(adc_periph) |= (uint32_t)(ADC_DMACTL_OVREN1);
        break;
    case ADC_GROUP_PRI2:
        ADC_DMACTL(adc_periph) |= (uint32_t)(ADC_DMACTL_OVREN2);
        break;
    case ADC_GROUP_PRI3:
        ADC_DMACTL(adc_periph) |= (uint32_t)(ADC_DMACTL_OVREN3);
        break;
    case ADC_GROUP_PRI4:
        ADC_DMACTL(adc_periph) |= (uint32_t)(ADC_DMACTL_OVREN4);
        break;
    default:
        break;
    }
}

/*!
    \brief      disable dma overrun detect (API_ID(0x0045U))
    \param[in]  adc_periph: ADCx,x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[out] none
    \retval     none
*/
void adc_group_dma_overrun_detect_disable(uint32_t adc_periph, adc_group_select_enum group)
{
    switch(group) {
    case ADC_GROUP_PRI1:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)(ADC_DMACTL_OVREN1);
        break;
    case ADC_GROUP_PRI2:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)(ADC_DMACTL_OVREN2);
        break;
    case ADC_GROUP_PRI3:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)(ADC_DMACTL_OVREN3);
        break;
    case ADC_GROUP_PRI4:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)(ADC_DMACTL_OVREN4);
        break;
    default:
        break;
    }
}

/*!
    \brief      channel priority config (API_ID(0x0046U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  rank: the priority of the selected channel
                  for ADC0: this parameter must be between 0 to 6.
                  for ADC2: this parameter must be between 0 to 11.
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INx: select channel ADC_INx, x=0..6 for ADC0, x=0..9 for ADC2
      \arg        ADC_CHANNEL_TEMPERATURE: select temperature sensor channel, for ADC2
      \arg        ADC_CHANNEL_VINT: select internal reference voltage channel, for ADC2
    \param[out] none
    \retval     none
*/
void adc_channel_priority_config(uint32_t adc_periph, uint8_t rank, adc_channel_select_enum adc_channel)
{
    uint32_t prirx;

    if(adc_channel < ADC_CHANNEL_ALL) {
        if(rank < 8U) {
            prirx = ADC_CHPRI0(adc_periph);
            prirx &= ~((uint32_t)(ADC_CHPRI0_PRI0 << (4U * rank)));
            prirx |= ((uint32_t)adc_channel << (4U * rank));
            ADC_CHPRI0(adc_periph) = prirx;
        } else if(rank < 15U) {
            prirx = ADC_CHPRI1(adc_periph);
            prirx &= ~((uint32_t)(ADC_CHPRI0_PRI0 << (4U * (rank - 8U))));
            prirx |= ((uint32_t)adc_channel << (4U * (rank - 8U)));
            ADC_CHPRI1(adc_periph) = prirx;
        } else {
            /* do nothing */
        }
    }
}

/*!
    \brief      configure ADC channel sample time (API_ID(0x0047U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INx: select channel ADC_INx, x=0..6 for ADC0, x=0..9 for ADC2
      \arg        ADC_CHANNEL_TEMPERATURE: select temperature sensor channel, for ADC2
      \arg        ADC_CHANNEL_VINT: select internal reference voltage channel, for ADC2
      \arg        ADC_CHANNEL_ALL: select all channel
    \param[in]  sample_time: 0x02~0xFF. The sample time value 0x02 cycle.
    \param[out] none
    \retval     none
*/
void adc_channel_sample_time_config(uint32_t adc_periph, adc_channel_select_enum channel, uint32_t sample_time)
{
    uint8_t i = 0U;
    uint32_t sampr_temp = 0U;

    i = channel % 4U;

    if(sample_time < 0x02U) {
        sample_time = 0x02U;
    }

    if(channel < 4U) {
        ADC_SAMPR0(adc_periph) &= ~(uint32_t)(ADC_SAMPR0_SPT00 << (i * 8U));
        ADC_SAMPR0(adc_periph) |= (uint32_t)((sample_time & ADC_SAMPR0_SPT00) << (i * 8U));
    } else if(channel < 8U) {
        ADC_SAMPR1(adc_periph) &= ~(uint32_t)(ADC_SAMPR1_SPT04 << (i * 8U));
        ADC_SAMPR1(adc_periph) |= (uint32_t)((sample_time & ADC_SAMPR0_SPT00) << (i * 8U));
    } else if(channel < 12U) {
        ADC_SAMPR2(adc_periph) &= ~(uint32_t)(ADC_SAMPR2_SPT08 << (i * 8U));
        ADC_SAMPR2(adc_periph) |= (uint32_t)((sample_time & ADC_SAMPR0_SPT00) << (i * 8U));
    } else {
        sampr_temp = ((sample_time) | ((sample_time) << 8U) | ((sample_time) << 16U) | ((sample_time) << 24U));
        ADC_SAMPR0(adc_periph) = sampr_temp;
        ADC_SAMPR1(adc_periph) = sampr_temp;
        ADC_SAMPR2(adc_periph) = sampr_temp;
    }
}

/*!
    \brief      select which event as the EVIC link signal (API_ID(0x0048U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  linksignal: EVIC link signal
                only one parameter can be selected which is shown as below:
      \arg          ADC_EVIC_LINK_GROUP_PRI1: an event signal is generated when scanning for Group_pri1 is completed
      \arg          ADC_EVIC_LINK_GROUP_PRI2: an event signal is generated when scanning for Group_pri2 is completed
      \arg          ADC_EVIC_LINK_GROUP_PRI3: an event signal is generated when scanning for Group_pri3 is completed
      \arg          ADC_EVIC_LINK_GROUP_PRI4: an event signal is generated when scanning for Group_pri4 is completed
      \arg          ADC_EVIC_LINK_GROUP_ALL: an event signal is generated when scanning for Group_pri1, Group_pri2, Group_pri3 or Group_pri4 is completed
    \param[out] none
    \retval     none
*/
void adc_evic_link_signal_event_config(uint32_t adc_periph, uint32_t linksignal)
{
    ADC_CTL0(adc_periph) &= ~ADC_CTL0_EVICCTL;
    ADC_CTL0(adc_periph) |= (linksignal & ADC_CTL0_EVICCTL);
}

/*!
    \brief      select EVIC link signal source for Gruop_pri x (API_ID(0x0049U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[in]  signal_src: EVIC trigger signal source
                only one parameter can be selected which is shown as below:
      \arg        ADC_EVIC_LINK_SOURCE_EOCRF_FLAG: EVIC trigger signal selects EOCxRF of Group_prix
      \arg        ADC_EVIC_LINK_SOURCE_EOCF_FLAG: EVIC trigger signal selects EOCxF of Group_prix
    \param[out] none
    \retval     none
*/
void adc_group_evic_link_signal_source(uint32_t adc_periph, adc_group_select_enum group, adc_evic_link_source_enum signal_src)
{
    if(ADC_EVIC_LINK_SOURCE_EOCF_FLAG == signal_src) {
        switch(group) {
        case ADC_GROUP_PRI1:
            ADC_EOCCTL(adc_periph) |=  ADC_EOCCTL_EVICG1SEL;
            break;
        case ADC_GROUP_PRI2:
            ADC_EOCCTL(adc_periph) |=  ADC_EOCCTL_EVICG2SEL;
            break;
        case ADC_GROUP_PRI3:
            ADC_EOCCTL(adc_periph) |=  ADC_EOCCTL_EVICG3SEL;
            break;
        case ADC_GROUP_PRI4:
            ADC_EOCCTL(adc_periph) |=  ADC_EOCCTL_EVICG4SEL;
            break;
        default:
            break;
        }
    } else {
        switch(group) {
        case ADC_GROUP_PRI1:
            ADC_EOCCTL(adc_periph) &=  ~ADC_EOCCTL_EVICG1SEL;
            break;
        case ADC_GROUP_PRI2:
            ADC_EOCCTL(adc_periph) &=  ~ADC_EOCCTL_EVICG2SEL;
            break;
        case ADC_GROUP_PRI3:
            ADC_EOCCTL(adc_periph) &=  ~ADC_EOCCTL_EVICG3SEL;
            break;
        case ADC_GROUP_PRI4:
            ADC_EOCCTL(adc_periph) &=  ~ADC_EOCCTL_EVICG4SEL;
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      read ADC channel data register (API_ID(0x004AU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INx: select channel ADC_INx, x=0..6 for ADC0, x=0..9 for ADC2
      \arg        ADC_CHANNEL_TEMPERATURE: select temperature sensor channel, for ADC2
      \arg        ADC_CHANNEL_VINT: select internal reference voltage channel, for ADC2
    \param[out] none
    \retval     the conversion value: 0~0xFFFF
*/
uint16_t adc_channel_data_read(uint32_t adc_periph, adc_channel_select_enum channel)
{
    uint16_t data_temp = 0U;

    if(channel < ADC_CHANNEL_ALL) {
        switch(adc_periph) {
        case ADC0:
            data_temp = (uint16_t)(ADC0_CHANNELX_DATA_REGISTER(channel));
            break;
        case ADC2:
            data_temp = (uint16_t)(ADC2_CHANNELX_DATA_REGISTER(channel));
            break;
        default:
            break;
        }
    }

    return data_temp;
}

/*!
    \brief      read ADC self-diagnosis data (API_ID(0x004BU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     the conversion value: 0x0000~0x0FFF (DAL=0,LSB alignment), 0x0000~0xFFF0 (DAL=1,MSB alignment),
*/
uint16_t adc_self_diagnosis_data_read(uint32_t adc_periph)
{
    uint16_t data = 0U;

    if(ADC_CTL0_DAL == (ADC_CTL0_DAL & ADC_CTL0(adc_periph))) {
        /* DAL=1,MSB alignment */
        data = (uint16_t)(ADC_SDDATA(adc_periph) & ((uint32_t)0x0000FFF0));
    } else {
        /* DAL=0,LSB alignment */
        data = (uint16_t)(ADC_SDDATA(adc_periph) & ((uint32_t)0x00000FFF));
    }

    return data;
}

/*!
    \brief      read ADC self-diagnosis status (API_ID(0x004CU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[out] none
    \retval     voltage status converted by self-diagnosis:
      \arg        0x0: self-diagnosis has never been executed since power-on.
      \arg        0x1: 0V converted by self-diagnosis
      \arg        0x2: VREFP/2 converted by self-diagnosis
      \arg        0x3: VREFP converted by self-diagnosis

*/
uint16_t adc_self_diagnosis_status_read(uint32_t adc_periph)
{
    uint16_t status = 0U;

    if(ADC_CTL0_DAL == (ADC_CTL0_DAL & ADC_CTL0(adc_periph))) {
        /* DAL=1,MSB alignment */
        status = (uint16_t)(ADC_SDDATA(adc_periph) & ((uint32_t)0x00000003));
    } else {
        /* DAL=0,LSB alignment */
        status = (uint16_t)((ADC_SDDATA(adc_periph) & ((uint32_t)0x0000C000)) >> 14U);
    }

    return status;
}

/*!
    \brief      read ADC bifurcate data register (API_ID(0x004DU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  group: select the group
                only one parameter can be selected which is shown as below:
      \arg        ADC_GROUP_PRI1: select Group_pri1
      \arg        ADC_GROUP_PRI2: select Group_pri2
      \arg        ADC_GROUP_PRI3: select Group_pri3
      \arg        ADC_GROUP_PRI4: select Group_pri4
    \param[in]  channel:data channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_BIFURCATE_DATA: read bifurcate data select
      \arg        ADC_EXTENDED_BIFURCATE_DATA_1: read bifurcate A data
      \arg        ADC_EXTENDED_BIFURCATE_DATA_2: read  bifurcate B data
    \param[out] none
    \retval     the conversion value: 0~0xFFFF
*/
uint16_t adc_bifurcate_data_read(uint32_t adc_periph, adc_group_select_enum group, adc_bifurcate_data_enum channel)
{
    uint16_t data_temp;

    switch(group) {
    case ADC_GROUP_PRI1:
        data_temp = (uint16_t)(*((uint32_t *)(uint32_t)(adc_periph + 0x60U + ((channel) * 4U))));
        break;
    case ADC_GROUP_PRI2:
        data_temp = (uint16_t)(*((uint32_t *)(uint32_t)(adc_periph + 0x60U + 0xCU + ((channel) * 4U))));
        break;
    case ADC_GROUP_PRI3:
        data_temp = (uint16_t)(*((uint32_t *)(uint32_t)(adc_periph + 0x60U + 0x18U + ((channel) * 4U))));
        break;
    case ADC_GROUP_PRI4:
        data_temp = (uint16_t)(*((uint32_t *)(uint32_t)(adc_periph + 0x60U + 0x24U + ((channel) * 4U))));
        break;
    default:
        break;
    }

    return data_temp;
}

/*!
    \brief      get the ADC flag (API_ID(0x004EU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  flag: the ADC flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_EOC1F: end of Group_pri1 conversion flag
      \arg        ADC_FLAG_EOC1RF: end of Group_pri1 conversion flag
      \arg        ADC_FLAG_EOC2F: end of Group_pri2 conversion flag
      \arg        ADC_FLAG_EOC2RF: round end of Group_pri2 conversion flag
      \arg        ADC_FLAG_EOC3F: round end of Group_pri3 conversion flag
      \arg        ADC_FLAG_EOC3RF: round end of Group_pri3 conversion flag
      \arg        ADC_FLAG_EOC4F: end of Group_pri4 conversion flag
      \arg        ADC_FLAG_EOC4RF: end of Group_pri4 conversion flag
      \arg        ADC_FLAG_PROC: A/D conversion is in process state
      \arg        ADC_FLAG_WDAMF: analog watchdog A monitor  event flag
      \arg        ADC_FLAG_WDBMF: analog watchdog B monitor  event flag
      \arg        ADC_FLAG_WDABMF: analog watchdog AB monitor  combine event flag
      \arg        ADC_FLAG_GP1OVRF: dma overrun flag of Group_pri1
      \arg        ADC_FLAG_GP2OVRF: dma overrun flag of Group_pri2
      \arg        ADC_FLAG_GP3OVRF: dma overrun flag of Group_pri3
      \arg        ADC_FLAG_GP4OVRF: dma overrun flag of Group_pri4
      \arg        ADC_FLAG_WDBEF: analog watchdog B event flag
      \arg        ADC_FLAG_WDA_CH0CMPF: channel ADCx_IN0 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH1CMPF: channel ADCx_IN1 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH2CMPF: channel ADCx_IN2 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH3CMPF: channel ADCx_IN3 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH4CMPF: channel ADCx_IN4 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH5CMPF: channel ADCx_IN5 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH6CMPF: channel ADCx_IN6 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH7CMPF: channel ADCx_IN7 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH8CMPF: channel ADCx_IN8 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH9CMPF: channel ADCx_IN9 compare status in watchdog A
      \arg        ADC_FLAG_WDA_TEMPCMPF: temperature sensor channel compare status in watchdog A
      \arg        ADC_FLAG_WDA_VINTCMPF: internal reference voltage channel compare status in watchdog A
      \arg        ADC_FLAG_WDA_ALL_CHCMPF: all channel compare status in watchdog A
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_flag_get(uint32_t adc_periph, adc_event_flag_enum flag)
{
    FlagStatus reval = RESET;

    switch(flag) {
    case ADC_FLAG_EOC1F:
        if(ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC1F) {
            reval = SET;
        }
        break;
    case ADC_FLAG_EOC1RF:
        if(ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC1RF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_EOC2F:
        if(ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC2F) {
            reval = SET;
        }
        break;
    case ADC_FLAG_EOC2RF:
        if(ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC2RF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_EOC3F:
        if(ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC3F) {
            reval = SET;
        }
        break;
    case ADC_FLAG_EOC3RF:
        if(ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC3RF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_EOC4F:
        if(ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC4F) {
            reval = SET;
        }
        break;
    case ADC_FLAG_EOC4RF:
        if(ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC4RF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_PROC:
        if(ADC_CTL0(adc_periph) & ADC_CTL0_PROCF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDAMF:
        if(ADC_WDCTL(adc_periph) & ADC_WDCTL_WDAMF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDBMF:
        if(ADC_WDCTL(adc_periph) & ADC_WDCTL_WDBMF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDABMF:
        if(ADC_WDCTL(adc_periph) & ADC_WDCTL_WDABMF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_GP1OVRF:
        if(ADC_DMACTL(adc_periph) & ADC_DMACTL_GP1OVRF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_GP2OVRF:
        if(ADC_DMACTL(adc_periph) & ADC_DMACTL_GP2OVRF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_GP3OVRF:
        if(ADC_DMACTL(adc_periph) & ADC_DMACTL_GP3OVRF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_GP4OVRF:
        if(ADC_DMACTL(adc_periph) & ADC_DMACTL_GP4OVRF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDBEF:
        if(ADC_WDCTL(adc_periph) & ADC_WDCTL_WDBEF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_CH0CMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_CH0CMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_CH1CMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_CH1CMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_CH2CMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_CH2CMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_CH3CMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_CH3CMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_CH4CMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_CH4CMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_CH5CMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_CH5CMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_CH6CMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_CH6CMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_CH7CMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_CH7CMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_CH8CMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_CH8CMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_CH9CMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_CH9CMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_TEMPCMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_TEMPCMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_VINTCMPF:
        if(ADC_WDACHSTAT(adc_periph) & ADC_WDACHSTAT_VINTCMPF) {
            reval = SET;
        }
        break;
    case ADC_FLAG_WDA_ALL_CHCMPF:
        if(ADC_WDACHSTAT(adc_periph) & ((uint32_t)0x00000FFF)) {
            reval = SET;
        }
        break;
    default:
        break;
    }

    return reval;
}

/*!
    \brief      clear the ADC flag (API_ID(0x004FU))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  flag: the ADC flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_EOC1F: end of Group_pri1 conversion flag
      \arg        ADC_FLAG_EOC1RF: end of Group_pri1 conversion flag
      \arg        ADC_FLAG_EOC2F: end of Group_pri2 conversion flag
      \arg        ADC_FLAG_EOC2RF: round end of Group_pri2 conversion flag
      \arg        ADC_FLAG_EOC3F: round end of Group_pri3 conversion flag
      \arg        ADC_FLAG_EOC3RF: round end of Group_pri3 conversion flag
      \arg        ADC_FLAG_EOC4F: end of Group_pri4 conversion flag
      \arg        ADC_FLAG_EOC4RF: end of Group_pri4 conversion flag
      \arg        ADC_FLAG_PROC: A/D conversion is in process state
      \arg        ADC_FLAG_WDAMF: analog watchdog A monitor  event flag
      \arg        ADC_FLAG_WDBMF: analog watchdog B monitor  event flag
      \arg        ADC_FLAG_WDABMF: analog watchdog AB monitor  combine event flag
      \arg        ADC_FLAG_GP1OVRF: dma overrun flag of Group_pri1
      \arg        ADC_FLAG_GP2OVRF: dma overrun flag of Group_pri2
      \arg        ADC_FLAG_GP3OVRF: dma overrun flag of Group_pri3
      \arg        ADC_FLAG_GP4OVRF: dma overrun flag of Group_pri4
      \arg        ADC_FLAG_WDBEF: analog watchdog B event flag
      \arg        ADC_FLAG_WDA_CH0CMPF: channel ADCx_IN0 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH1CMPF: channel ADCx_IN1 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH2CMPF: channel ADCx_IN2 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH3CMPF: channel ADCx_IN3 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH4CMPF: channel ADCx_IN4 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH5CMPF: channel ADCx_IN5 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH6CMPF: channel ADCx_IN6 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH7CMPF: channel ADCx_IN7 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH8CMPF: channel ADCx_IN8 compare status in watchdog A
      \arg        ADC_FLAG_WDA_CH9CMPF: channel ADCx_IN9 compare status in watchdog A
      \arg        ADC_FLAG_WDA_TEMPCMPF: temperature sensor channel compare status in watchdog A
      \arg        ADC_FLAG_WDA_VINTCMPF: internal reference voltage channel compare status in watchdog A
      \arg        ADC_FLAG_WDA_ALL_CHCMPF: all channel compare status in watchdog A
    \param[out] none
    \retval     none
*/
void adc_flag_clear(uint32_t adc_periph, adc_event_flag_enum flag)
{
    switch(flag) {
    case ADC_FLAG_EOC1F:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC1F;
        break;
    case ADC_FLAG_EOC1RF:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC1RF;
        break;
    case ADC_FLAG_EOC2F:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC2F;
        break;
    case ADC_FLAG_EOC2RF:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC2RF;
        break;
    case ADC_FLAG_EOC3F:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC3F;
        break;
    case ADC_FLAG_EOC3RF:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC3RF;
        break;
    case ADC_FLAG_EOC4F:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC4F;
        break;
    case ADC_FLAG_EOC4RF:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC4RF;
        break;
    case ADC_FLAG_GP1OVRF:
        ADC_DMACTL(adc_periph) &= ~ADC_DMACTL_GP1OVRF;
        break;
    case ADC_FLAG_GP2OVRF:
        ADC_DMACTL(adc_periph) &= ~ADC_DMACTL_GP2OVRF;
        break;
    case ADC_FLAG_GP3OVRF:
        ADC_DMACTL(adc_periph) &= ~ADC_DMACTL_GP3OVRF;
        break;
    case ADC_FLAG_GP4OVRF:
        ADC_DMACTL(adc_periph) &= ~ADC_DMACTL_GP4OVRF;
        break;
    case ADC_FLAG_WDBEF:
        ADC_WDCTL(adc_periph) &= ~ADC_WDCTL_WDBEF;
        break;
    case ADC_FLAG_WDA_CH0CMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_CH0CMPF;
        break;
    case ADC_FLAG_WDA_CH1CMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_CH1CMPF;
        break;
    case ADC_FLAG_WDA_CH2CMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_CH2CMPF;
        break;
    case ADC_FLAG_WDA_CH3CMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_CH3CMPF;
        break;
    case ADC_FLAG_WDA_CH4CMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_CH4CMPF;
        break;
    case ADC_FLAG_WDA_CH5CMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_CH5CMPF;
        break;
    case ADC_FLAG_WDA_CH6CMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_CH6CMPF;
        break;
    case ADC_FLAG_WDA_CH7CMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_CH7CMPF;
        break;
    case ADC_FLAG_WDA_CH8CMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_CH8CMPF;
        break;
    case ADC_FLAG_WDA_CH9CMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_CH9CMPF;
        break;
    case ADC_FLAG_WDA_TEMPCMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_TEMPCMPF;
        break;
    case ADC_FLAG_WDA_VINTCMPF:
        ADC_WDACHSTAT(adc_periph) &= ~ADC_WDACHSTAT_VINTCMPF;
        break;
    case ADC_FLAG_WDA_ALL_CHCMPF:
        ADC_WDACHSTAT(adc_periph) &= ((uint32_t)0xFFFFF000U);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable ADC interrupt (API_ID(0x0050U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  interrupt: the interrupt select
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_EOC1RF: end of Group_pri1 conversion round interrupt
      \arg        ADC_INT_EOC2RF: end of Group_pri2 conversion round interrupt
      \arg        ADC_INT_EOC3RF: end of Group_pri3 conversion round interrupt
      \arg        ADC_INT_EOC4RF: end of Group_pri4 conversion round interrupt
      \arg        ADC_INT_WDA_CHSTAT: analog watchdog A event interrupt
      \arg        ADC_INT_WDBEF: analog watchdog B event interrupt
      \arg        ADC_INT_GP1OVRF: dma overrun interrupt of Group_pri1
      \arg        ADC_INT_GP2OVRF: dma overrun interrupt of Group_pri2
      \arg        ADC_INT_GP3OVRF: dma overrun interrupt of Group_pri3
      \arg        ADC_INT_GP4OVRF: dma overrun interrupt of Group_pri4
    \param[out] none
    \retval     none
*/
void adc_interrupt_enable(uint32_t adc_periph, adc_interrupt_enum interrupt)
{
    switch(interrupt) {
    /* enable high group sequence scan end interrupt */
    case ADC_INT_EOC1RF:
        ADC_EOCCTL(adc_periph) |= (uint32_t)ADC_EOCCTL_EOC1RIE;
        break;
    /* enable mid group sequence scan end interrupt */
    case ADC_INT_EOC2RF:
        ADC_EOCCTL(adc_periph) |= (uint32_t)ADC_EOCCTL_EOC2RIE;
        break;
    /* enable low group sequence scan end interrupt */
    case ADC_INT_EOC3RF:
        ADC_EOCCTL(adc_periph) |= (uint32_t)ADC_EOCCTL_EOC3RIE;
        break;
    /* enable lowest group sequence scan end interrupt */
    case ADC_INT_EOC4RF:
        ADC_EOCCTL(adc_periph) |= (uint32_t)ADC_EOCCTL_EOC4RIE;
        break;
    /* enable analog watchdog A interrupt */
    case ADC_INT_WDA_CHSTAT:
        ADC_WDCTL(adc_periph) |= (uint32_t)ADC_WDCTL_WDAIE;
        break;
    /* enable analog watchdog B interrupt */
    case ADC_INT_WDBEF:
        ADC_WDCTL(adc_periph) |= (uint32_t)ADC_WDCTL_WDBIE;
        break;
    /* enable high group dma overrun interrupt */
    case ADC_INT_GP1OVRF:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_GP1OVRIE;
        break;
    /* enable mid group dma overrun interrupt */
    case ADC_INT_GP2OVRF:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_GP2OVRIE;
        break;
    /* enable low group dma overrun interrupt */
    case ADC_INT_GP3OVRF:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_GP3OVRIE;
        break;
    /* enable lowest group dma overrun interrupt */
    case ADC_INT_GP4OVRF:
        ADC_DMACTL(adc_periph) |= (uint32_t)ADC_DMACTL_GP4OVRIE;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable ADC interrupt (API_ID(0x0051U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  interrupt: the interrupt select
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_EOC1RF: end of Group_pri1 conversion round interrupt
      \arg        ADC_INT_EOC2RF: end of Group_pri2 conversion round interrupt
      \arg        ADC_INT_EOC3RF: end of Group_pri3 conversion round interrupt
      \arg        ADC_INT_EOC4RF: end of Group_pri4 conversion round interrupt
      \arg        ADC_INT_WDA_CHSTAT: analog watchdog A event interrupt
      \arg        ADC_INT_WDBEF: analog watchdog B event interrupt
      \arg        ADC_INT_GP1OVRF: dma overrun interrupt of Group_pri1
      \arg        ADC_INT_GP2OVRF: dma overrun interrupt of Group_pri2
      \arg        ADC_INT_GP3OVRF: dma overrun interrupt of Group_pri3
      \arg        ADC_INT_GP4OVRF: dma overrun interrupt of Group_pri4
    \param[out] none
    \retval     none
*/
void adc_interrupt_disable(uint32_t adc_periph, adc_interrupt_enum interrupt)
{
    switch(interrupt) {
    /* disable high group sequence scan end interrupt */
    case ADC_INT_EOC1RF:
        ADC_EOCCTL(adc_periph) &= ~(uint32_t)ADC_EOCCTL_EOC1RIE;
        break;
    /* disable mid group sequence scan end interrupt */
    case ADC_INT_EOC2RF:
        ADC_EOCCTL(adc_periph) &= ~(uint32_t)ADC_EOCCTL_EOC2RIE;
        break;
    /* disable low group sequence scan end interrupt */
    case ADC_INT_EOC3RF:
        ADC_EOCCTL(adc_periph) &= ~(uint32_t)ADC_EOCCTL_EOC3RIE;
        break;
    /* disable lowest group sequence scan end interrupt */
    case ADC_INT_EOC4RF:
        ADC_EOCCTL(adc_periph) &= ~(uint32_t)ADC_EOCCTL_EOC4RIE;
        break;
    /* disable analog watchdog A interrupt */
    case ADC_INT_WDA_CHSTAT:
        ADC_WDCTL(adc_periph) &= ~(uint32_t)ADC_WDCTL_WDAIE;
        break;
    /* disable analog watchdog B interrupt */
    case ADC_INT_WDBEF:
        ADC_WDCTL(adc_periph) &= ~(uint32_t)ADC_WDCTL_WDBIE;
        break;
    /* disable high group dma overrun interrupt */
    case ADC_INT_GP1OVRF:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)ADC_DMACTL_GP1OVRIE;
        break;
    /* disable low group dma overrun interrupt */
    case ADC_INT_GP3OVRF:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)ADC_DMACTL_GP3OVRIE;
        break;
    /* disable mid group dma overrun interrupt */
    case ADC_INT_GP2OVRF:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)ADC_DMACTL_GP2OVRIE;
        break;
    /* disable low group dma overrun interrupt */
    case ADC_INT_GP4OVRF:
        ADC_DMACTL(adc_periph) &= ~(uint32_t)ADC_DMACTL_GP4OVRIE;
        break;
    default:
        break;
    }
}

/*!
    \brief      get ADC interrupt flag (API_ID(0x0052U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  int_flag: the ADC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_EOC1RF: end of Group_pri1 conversion round interrupt
      \arg        ADC_INT_FLAG_EOC2RF: end of Group_pri2 conversion round interrupt
      \arg        ADC_INT_FLAG_EOC3RF: end of Group_pri3 conversion round interrupt
      \arg        ADC_INT_FLAG_EOC4RF: end of Group_pri4 conversion round interrupt
      \arg        ADC_INT_FLAG_WDA_CHSTAT: analog watchdog A event interrupt
      \arg        ADC_INT_FLAG_WDBEF: analog watchdog B event interrupt
      \arg        ADC_INT_FLAG_GP1OVRF: dma overrun interrupt of Group_pri1
      \arg        ADC_INT_FLAG_GP2OVRF: dma overrun interrupt of Group_pri2
      \arg        ADC_INT_FLAG_GP3OVRF: dma overrun interrupt of Group_pri3
      \arg        ADC_INT_FLAG_GP4OVRF: dma overrun interrupt of Group_pri4
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph, adc_interrupt_flag_enum int_flag)
{
    FlagStatus interrupt_flag = RESET;
    uint32_t state;

    /* check the interrupt bits */
    switch(int_flag) {
    case ADC_INT_FLAG_EOC1RF:
        state = ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC1RF;
        if((ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC1RIE) && state) {
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_EOC2RF:
        state = ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC2RF;
        if((ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC2RIE) && state) {
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_EOC3RF:
        state = ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC3RF;
        if((ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC3RIE) && state) {
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_EOC4RF:
        state = ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC4RF;
        if((ADC_EOCCTL(adc_periph) & ADC_EOCCTL_EOC4RIE) && state) {
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_WDA_CHSTAT:
        state = (ADC_WDACHSTAT(adc_periph) & ((uint32_t)0x00000FFF));
        if((ADC_WDCTL(adc_periph) & ADC_WDCTL_WDAIE) && state) {
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_WDBEF:
        state = ADC_WDCTL(adc_periph) & ADC_WDCTL_WDBEF;
        if((ADC_WDCTL(adc_periph) & ADC_WDCTL_WDBIE) && state) {
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_GP4OVRF:
        state = ADC_DMACTL(adc_periph) & ADC_DMACTL_GP4OVRF;
        if((ADC_DMACTL(adc_periph) & ADC_DMACTL_GP4OVRIE) && state) {
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_GP3OVRF:
        state = ADC_DMACTL(adc_periph) & ADC_DMACTL_GP3OVRF;
        if((ADC_DMACTL(adc_periph) & ADC_DMACTL_GP3OVRIE) && state) {
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_GP2OVRF:
        state = ADC_DMACTL(adc_periph) & ADC_DMACTL_GP2OVRF;
        if((ADC_DMACTL(adc_periph) & ADC_DMACTL_GP2OVRIE) && state) {
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_GP1OVRF:
        state = ADC_DMACTL(adc_periph) & ADC_DMACTL_GP1OVRF;
        if((ADC_DMACTL(adc_periph) & ADC_DMACTL_GP1OVRIE) && state) {
            interrupt_flag = SET;
        }
        break;
    default:
        break;
    }
    return interrupt_flag;
}

/*!
    \brief      clear ADC interrupt flag (API_ID(0x0053U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  int_flag: the ADC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_EOC1RF: end of Group_pri1 conversion round interrupt
      \arg        ADC_INT_FLAG_EOC2RF: end of Group_pri2 conversion round interrupt
      \arg        ADC_INT_FLAG_EOC3RF: end of Group_pri3 conversion round interrupt
      \arg        ADC_INT_FLAG_EOC4RF: end of Group_pri4 conversion round interrupt
      \arg        ADC_INT_FLAG_WDA_CHSTAT: analog watchdog A event interrupt
      \arg        ADC_INT_FLAG_WDBEF: analog watchdog B event interrupt
      \arg        ADC_INT_FLAG_GP1OVRF: dma overrun interrupt of Group_pri1
      \arg        ADC_INT_FLAG_GP2OVRF: dma overrun interrupt of Group_pri2
      \arg        ADC_INT_FLAG_GP3OVRF: dma overrun interrupt of Group_pri3
      \arg        ADC_INT_FLAG_GP4OVRF: dma overrun interrupt of Group_pri4
    \param[out] none
    \retval     none
*/
void adc_interrupt_flag_clear(uint32_t adc_periph, adc_interrupt_flag_enum int_flag)
{
    switch(int_flag) {
    case ADC_INT_FLAG_EOC1RF:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC1RF;
        break;
    case ADC_INT_FLAG_EOC2RF:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC2RF;
        break;
    case ADC_INT_FLAG_EOC3RF:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC3RF;
        break;
    case ADC_INT_FLAG_EOC4RF:
        ADC_EOCCTL(adc_periph) &= ~ADC_EOCCTL_EOC4RF;
        break;
    case ADC_INT_FLAG_WDA_CHSTAT:
        ADC_WDACHSTAT(adc_periph) &= ((uint32_t)0xFFFFF000U);
        break;
    case ADC_INT_FLAG_WDBEF:
        ADC_WDCTL(adc_periph) &= ~ADC_WDCTL_WDBEF;
        break;
    case ADC_INT_FLAG_GP1OVRF:
        ADC_DMACTL(adc_periph) &= ~ADC_DMACTL_GP1OVRF;
        break;
    case ADC_INT_FLAG_GP2OVRF:
        ADC_DMACTL(adc_periph) &= ~ADC_DMACTL_GP2OVRF;
        break;
    case ADC_INT_FLAG_GP3OVRF:
        ADC_DMACTL(adc_periph) &= ~ADC_DMACTL_GP3OVRF;
        break;
    case ADC_INT_FLAG_GP4OVRF:
        ADC_DMACTL(adc_periph) &= ~ADC_DMACTL_GP4OVRF;
        break;
    default:
        break;
    }
}
