/*!
    \file    gd32g5x3_pmu.c
    \brief   PMU driver

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

#include "gd32g5x3_pmu.h"

/*!
    \brief      reset PMU registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_deinit(void)
{
    /* reset PMU */
    rcu_periph_reset_enable(RCU_PMURST);
    rcu_periph_reset_disable(RCU_PMURST);
}

/*!
    \brief      select low voltage detector threshold
    \param[in]  lvdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVDT_0: voltage threshold is 2.15V
      \arg        PMU_LVDT_1: voltage threshold is 2.3V
      \arg        PMU_LVDT_2: voltage threshold is 2.45V
      \arg        PMU_LVDT_3: voltage threshold is 2.6V
      \arg        PMU_LVDT_4: voltage threshold is 2.75V
      \arg        PMU_LVDT_5: voltage threshold is 2.9V
      \arg        PMU_LVDT_6: voltage threshold is 3.0V
      \arg        PMU_LVDT_7: external input analog voltage
    \param[out] none
    \retval     none
*/
void pmu_lvd_select(uint32_t lvdt_n)
{
    uint32_t temp;
    temp = PMU_CTL0;
    /* clear LVDT bits */
    temp &= ~PMU_CTL0_LVDT;
    /* set LVDT bits according to lvdt_n */
    temp |= lvdt_n;
    PMU_CTL0 = temp;
}

/*!
    \brief      enable PMU lvd
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lvd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_LVDEN;
}

/*!
    \brief      disable PMU lvd
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lvd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_LVDEN;
}

/*!
    \brief      select LDO output voltage
                These bits are set by software when the main PLL closed. And the LDO output voltage selected by 
                LDOVS bits takes effect when the main PLL enabled. If the main PLL closed, the LDO output voltage 
                low mode selected (value of this bit filed not changed).
    \param[in]  ldo_output:
      \arg        PMU_LDOVS_1_1V: LDO output voltage 1.1V
      \arg        PMU_LDOVS_1_15V: LDO output voltage 1.15V
    \param[out] none
    \retval     none
*/
void pmu_ldo_output_select(uint32_t ldo_output)
{
    PMU_CTL0 &= ~PMU_CTL0_LDOVS;
    PMU_CTL0 |= ldo_output;
}

/*!
    \brief      select PMU analog voltage detector threshold
    \param[in]  avdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_AVDT_0: voltage threshold is 1.8V
      \arg        PMU_AVDT_1: voltage threshold is 2.2V
      \arg        PMU_AVDT_2: voltage threshold is 2.6V
      \arg        PMU_AVDT_3: voltage threshold is 2.9V
    \param[out] none
    \retval     none
*/
void pmu_avd_select(uint32_t avdt_n)
{
    uint32_t temp;
    temp = PMU_CTL0;
    /* clear VAVDVC bits */
    temp &= ~PMU_CTL0_VAVDVC;
    /* set VAVDVC bits according to avdt_n */
    temp |= avdt_n;
    PMU_CTL0 = temp;
}

/*!
    \brief      enable PMU analog voltage detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_avd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_VAVDEN;
}

/*!
    \brief      disable PMU analog voltage detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_avd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VAVDEN;
}

/*!
    \brief      select PMU core over voltage detector threshold
    \param[in]  ovdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_OVDT_0: voltage threshold is 1.25V
      \arg        PMU_OVDT_1: voltage threshold is 1.35V
      \arg        PMU_OVDT_2: voltage threshold is 1.45V
      \arg        PMU_OVDT_3: voltage threshold is 1.55V
    \param[out] none
    \retval     none
*/
void pmu_ovd_select(uint32_t ovdt_n)
{
    uint32_t temp;
    temp = PMU_CTL0;
    /* clear VOVDVC bits */
    temp &= ~PMU_CTL0_VOVDVC;
    /* set VOVDVC bits according to ovdt_n */
    temp |= ovdt_n;
    PMU_CTL0 = temp;
}

/*!
    \brief      enable PMU core over voltage detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_ovd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_VOVDEN;
}

/*!
    \brief      disable PMU core over voltage detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_ovd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VOVDEN;
}

/*!
    \brief      select PMU core under voltage detector threshold
    \param[in]  uvdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_UVDT_0: voltage threshold is 0.95V
      \arg        PMU_UVDT_1: voltage threshold is 0.85V
      \arg        PMU_UVDT_2: voltage threshold is 0.75V
      \arg        PMU_UVDT_3: voltage threshold is 0.65V
    \param[out] none
    \retval     none
*/
void pmu_uvd_select(uint32_t uvdt_n)
{
    uint32_t temp;
    temp = PMU_CTL0;
    /* clear VUVDVC bits */
    temp &= ~PMU_CTL0_VUVDVC;
    /* set VUVDVC bits according to uvdt_n */
    temp |= uvdt_n;
    PMU_CTL0 = temp;
}

/*!
    \brief      enable PMU core under voltage detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_uvd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_VUVDEN;
}

/*!
    \brief      disable PMU core under voltage detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_uvd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VUVDEN;
}

/*!
    \brief      PMU core over voltage digital noise filter
    \param[in]  dnf: digital noise filter 0~255
    \param[out] none
    \retval     none
*/
void pmu_ovd_filter(uint32_t dnf)
{
    uint32_t temp;
    temp = PMU_CTL3;
    temp &= ~PMU_CTL3_VOVDO_DNF;
    temp |= dnf;
    PMU_CTL3 = temp;
}

/*!
    \brief      PMU core under voltage digital noise filter
    \param[in]  dnf: digital noise filter 0~255
    \param[out] none
    \retval     none
*/
void pmu_uvd_filter(uint32_t dnf)
{
    uint32_t temp;
    temp = PMU_CTL3;
    temp &= ~PMU_CTL3_VUVDO_DNF;
    temp |= dnf << 8;
    PMU_CTL3 = temp;
}

/*!
    \brief      PMU deepsleep mode voltage selection
    \param[in]  vol:
                only one parameter can be selected which is shown as below:
      \arg        PMU_DSLPVS_0: deepsleep mode voltage 0.8V
      \arg        PMU_DSLPVS_1: deepsleep mode voltage 0.9V
      \arg        PMU_DSLPVS_2: deepsleep mode voltage 1.0V (default)
      \arg        PMU_DSLPVS_3: deepsleep mode voltage 1.1V
    \param[out] none
    \retval     none
*/
void pmu_deepsleep_voltage(uint32_t vol)
{
    uint32_t temp;
    temp = PMU_CTL0;
    /* clear DSLPVS bits */
    temp &= ~PMU_CTL0_DSLPVS;
    /* set DSLPVS bits according to vol */
    temp |= vol;
    PMU_CTL0 = temp;
}


/*!
    \brief      PMU VBAT battery charging resistor selection
    \param[in]  resistor:
                only one parameter can be selected which is shown as below:
      \arg        PMU_VCRSEL_5K: 5 kOhms resistor is selected for charing VBAT battery
      \arg        PMU_VCRSEL_1P5K: 1.5 kOhms resistor is selected for charing VBAT battery
    \param[out] none
    \retval     none
*/
void pmu_vbat_charging_select(uint32_t resistor)
{
    uint32_t temp;
    temp = PMU_CTL2;
    temp &= ~PMU_CTL2_VCRSEL;
    temp |= resistor;
    PMU_CTL2 = temp;
}

/*!
    \brief      enable VBAT battery charging
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_charging_enable(void)
{
    PMU_CTL2 |= PMU_CTL2_VCEN;
}

/*!
    \brief      disable VBAT battery charging
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_charging_disable(void)
{
    PMU_CTL2 &= ~PMU_CTL2_VCEN;
}

/*!
    \brief      VBAT and temperature monitoring enable
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_temp_moniter_enable(void)
{
    PMU_CTL1 |= PMU_CTL1_BKPVSEN;
    while((PMU_CTL1 & PMU_CTL1_BKPVSRF) == 0U) {}
    PMU_CTL1 |= PMU_CTL1_VBTMEN;
}

/*!
    \brief      VBAT and temperature monitoring disable
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_temp_moniter_disable(void)
{
    PMU_CTL1 &= ~PMU_CTL1_VBTMEN;
    PMU_CTL1 &= ~PMU_CTL1_BKPVSEN;
}

/*!
    \brief      enter sleep mode
    \param[in]  sleepmodecmd:
                only one parameter can be selected which is shown as below:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_sleepmode(uint8_t sleepmodecmd)
{
    /* clear sleepdeep bit of Cortex-M33 system control register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    /* select WFI or WFE command to enter sleep mode */
    if(WFI_CMD == sleepmodecmd) {
        __WFI();
    } else {
        __WFE();
        __WFE();
    }
}

/*!
    \brief      enter deepsleep mode
    \param[in]  lowpower:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LDO_NORMAL: LDO normal work when pmu enter deepsleep mode
      \arg        PMU_LDO_LOWPOWER: LDO work at low power mode when pmu enter deepsleep mode
    \param[in]  deepsleepmodecmd:
                only one parameter can be selected which is shown as below:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_deepsleepmode(uint32_t lowpower, uint8_t deepsleepmodecmd)
{
    /* clear standby mode and low power bit and low drive bits */
    PMU_CTL0 &= ~((uint32_t)(PMU_CTL0_STBMOD | PMU_CTL0_LDOLP));

    /* set LDOLP bit according to pmu_ldo */
    PMU_CTL0 |= lowpower;

    /* set sleepdeep bit of Cortex-M33 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* select WFI or WFE command to enter deepsleep mode */
    if(WFI_CMD == deepsleepmodecmd) {
        __WFI();
    } else {
        __SEV();
        __WFE();
        __WFE();
    }
    /* reset sleepdeep bit of Cortex-M33 system control register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/*!
    \brief      enter standby mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_to_standbymode(void)
{
    /* set stbmod bit */
    PMU_CTL0 |= PMU_CTL0_STBMOD;

    /* reset wakeup flag */
    PMU_CTL0 |= PMU_CTL0_WURST;

    /* set sleepdeep bit of Cortex-M33 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    
    REG32(0xE000E010U) &= 0x00010004U;
    REG32(0xE000E180U)  = 0XFFFFFFF7U;
    REG32(0xE000E184U)  = 0XFFFFFDFFU;
    REG32(0xE000E188U)  = 0xFFFFFFFFU;

    /* enter standby mode */
    __WFI();
}

/*!
    \brief      enable wakeup pin
    \param[in]  wakeup_pin:
                one or more parameters can be selected which are shown as below:
      \arg        PMU_WAKEUP_PIN0: WKUP Pin 0 (PA0)
      \arg        PMU_WAKEUP_PIN1: WKUP Pin 1 (PC13)
      \arg        PMU_WAKEUP_PIN2: WKUP Pin 2 (PE6)
      \arg        PMU_WAKEUP_PIN3: WKUP Pin 3 (PA2)
      \arg        PMU_WAKEUP_PIN4: WKUP Pin 4 (PC5)
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_enable(uint32_t wakeup_pin)
{
    PMU_CS |= wakeup_pin;
}

/*!
    \brief      disable wakeup pin
    \param[in]  wakeup_pin:
                one or more parameters can be selected which are shown as below:
      \arg        PMU_WAKEUP_PIN0: WKUP Pin 0 (PA0)
      \arg        PMU_WAKEUP_PIN1: WKUP Pin 1 (PC13)
      \arg        PMU_WAKEUP_PIN2: WKUP Pin 2 (PE6)
      \arg        PMU_WAKEUP_PIN3: WKUP Pin 3 (PA2)
      \arg        PMU_WAKEUP_PIN4: WKUP Pin 4 (PC5)
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_disable(uint32_t wakeup_pin)
{
    PMU_CS &= ~(wakeup_pin);
}

/*!
    \brief      enable backup domain write
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_BKPWEN;
}

/*!
    \brief      disable backup domain write
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_BKPWEN;
}

/*!
    \brief      get flag state
    \param[in]  flag:
      \arg        PMU_FLAG_WAKEUP: wakeup flag
      \arg        PMU_FLAG_STANDBY: standby flag
      \arg        PMU_FLAG_LVDF: low voltage detector status flag
      \arg        PMU_FLAG_VAVDF: VDDA analog voltage detector voltage output on VDDA flag
      \arg        PMU_FLAG_VOVDF0: Over voltage on VDDA detector flag
      \arg        PMU_FLAG_VUVDF0: Under voltage on VDDA detector flag
      \arg        PMU_FLAG_VOVDF1: Over voltage on VDDA detector flag after digital filter
      \arg        PMU_FLAG_VUVDF1: Under voltage on VDDA detector flag after digital filter
      \arg        PMU_FLAG_BKPVSRF: Bandgap Voltage Reference ready
      \arg        PMU_FLAG_VBATLF: VBAT level monitoring versus low threshold
      \arg        PMU_FLAG_VBATHF: VBAT level monitoring versus high threshold
      \arg        PMU_FLAG_TEMPLF: temperature level monitoring versus low threshold
      \arg        PMU_FLAG_TEMPHF: temperature level monitoring versus high threshold
    \param[out] none
    \retval     FlagStatus SET or RESET
*/
FlagStatus pmu_flag_get(uint32_t flag)
{
    if(PMU_REG_VAL(flag) & BIT(PMU_BIT_POS(flag))) {
        return  SET;
    } else {
        return  RESET;
    }
}

/*!
    \brief      clear flag bit
    \param[in]  flag_reset:
      \arg        PMU_FLAG_WAKEUP: wakeup flag
      \arg        PMU_FLAG_STANDBY: standby flag
    \param[out] none
    \retval     none
*/
void pmu_flag_clear(uint32_t flag_reset)
{
    switch(flag_reset) {
        case PMU_FLAG_WAKEUP:
            /* reset wakeup flag */
            PMU_CTL0 |= PMU_CTL0_WURST;
            break;
        case PMU_FLAG_STANDBY:
            /* reset standby flag */
            PMU_CTL0 |= PMU_CTL0_STBRST;
            break;
        default:
            break;
    }
}
