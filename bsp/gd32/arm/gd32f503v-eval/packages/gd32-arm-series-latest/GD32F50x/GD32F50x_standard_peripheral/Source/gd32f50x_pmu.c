/*!
    \file    gd32f50x_pmu.c
    \brief   PMU driver

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


#include "gd32f50x_pmu.h"

/*!
    \brief      reset PMU register (API ID(0x0001U))
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
    \brief      lock the pmu register (API ID(0x0002U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lock(void)
{
    /* pmu lock bit */
    PMU_CTL0 &= ~PMU_CTL0_UNLOCK;
}

/*!
    \brief      unlock the pmu register (API ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_unlock(void)
{
    /* pmu lock bit */
    PMU_CTL0 |= PMU_CTL0_UNLOCK;
}


/*!
    \brief      select low voltage detector threshold (API ID(0x0004U))
    \param[in]  lvdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVDT_0: voltage threshold is 2.1V
      \arg        PMU_LVDT_1: voltage threshold is 2.3V
      \arg        PMU_LVDT_2: voltage threshold is 2.4V
      \arg        PMU_LVDT_3: voltage threshold is 2.6V
      \arg        PMU_LVDT_4: voltage threshold is 2.7V
      \arg        PMU_LVDT_5: voltage threshold is 2.8V
      \arg        PMU_LVDT_6: voltage threshold is 3.0V
      \arg        PMU_LVDT_7: voltage threshold is 3.1V
    \param[out] none
    \retval     none
*/
void pmu_lvd_select(uint32_t lvdt_n)
{
    /* disable LVD */
    PMU_CTL0 &= ~PMU_CTL0_LVDEN;
    /* clear LVDT bits */
    PMU_CTL0 &= ~PMU_CTL0_LVDT;
    /* set LVDT bits according to lvdt_n */
    PMU_CTL0 |= lvdt_n & PMU_CTL0_LVDT;
    /* enable LVD */
    PMU_CTL0 |= PMU_CTL0_LVDEN;
}

/*!
    \brief      select power down reset voltage detector threshold (API ID(0x0005U))
    \param[in]  pdrvl:
                only one parameter can be selected which is shown as below:
      \arg        PMU_PDRVS_LEVEL0: voltage threshold is 2.35V
      \arg        PMU_PDRVS_LEVEL1: voltage threshold is 1.8V
    \param[out] none
    \retval     none
*/
void pmu_pdrvs_select(uint32_t pdrvl)
{
    /* clear PDRVS bits */
    PMU_CTL0 &= ~PMU_CTL0_PDR_LVLSEL;
    /* set PDRVS bits according to pdrvl */
    PMU_CTL0 |= pdrvl & PMU_CTL0_PDR_LVLSEL;
}

/*!
    \brief      select LDO output voltage (API ID(0x0006U))
                this bit set by software when the main PLL closed, before closing PLL,
                change the system clock to IRC8M or HXTAL
    \param[in]  ldo_output:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LDOVS_x: (x:1-7)LDO output voltage
    \param[out] none
    \retval     none
*/
void pmu_ldo_output_select(uint32_t ldo_output)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LDO_OUTPUT_VOL(ldo_output)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    } else
#endif
    {
        PMU_CTL0 &= ~PMU_CTL0_LDOVS;
        PMU_CTL0 |= ldo_output & PMU_CTL0_LDOVS;
    }
}

/*!
    \brief      enable PMU lvd (API ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lvd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_LVDEN;
}

/*!
    \brief      disable PMU lvd (API ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lvd_disable(void)
{
    /* disable LVD */
    PMU_CTL0 &= ~PMU_CTL0_LVDEN;
}

/*!
    \brief      enable low-driver mode in deep-sleep mode (API ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lowdriver_mode_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_LDEN;
}

/*!
    \brief      disable low-driver mode in deep-sleep mode (API ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lowdriver_mode_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_LDEN;
}

/*!
    \brief      driver mode when use low power LDO (API ID(0x000BU))
    \param[in]  mode:
                only one parameter can be selected which is shown as below:
      \arg        PMU_NORMALDR_LOWPWR: normal driver when use low power LDO
      \arg        PMU_LOWDR_LOWPWR: low-driver mode enabled when LDEN is 11 and use low power LDO
    \param[out] none
    \retval     none
*/
void pmu_lowpower_driver_config(uint32_t mode)
{
    PMU_CTL0 &= ~PMU_CTL0_LDLP;
    PMU_CTL0 |= mode & PMU_CTL0_LDLP;
}

/*!
    \brief      driver mode when use normal power LDO (API ID(0x000CU))
    \param[in]  mode:
                only one parameter can be selected which is shown as below:
      \arg        PMU_NORMALDR_NORMALPWR: normal driver when use normal power LDO
      \arg        PMU_LOWDR_NORMALPWR: low-driver mode enabled when LDEN is 0b11 and use normal power LDO
    \param[out] none
    \retval     none
*/
void pmu_normalpower_driver_config(uint32_t mode)
{
    PMU_CTL0 &= ~PMU_CTL0_LDNP;
    PMU_CTL0 |= mode & PMU_CTL0_LDNP;
}

/*!
    \brief      PMU work in sleep mode (API ID(0x000DU))
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
        __SEV();
        __WFE();
        __WFE();
    }
}

/*!
    \brief      PMU work in deepsleep mode (API ID(0x000EU))
    \param[in]  ldo:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LDO_NORMAL: LDO work in normal power mode when pmu enter deepsleep mode
      \arg        PMU_LDO_LOWPOWER: LDO work in low power mode when pmu enter deepsleep mode
    \param[in]  lowdrive:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LOWDRIVER_ENABLE: low-driver mode enable in deep-sleep mode
      \arg        PMU_LOWDRIVER_DISABLE: low-driver mode disable in deep-sleep mode
    \param[in]  deepsleepmodecmd:
                only one parameter can be selected which is shown as below:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_deepsleepmode(uint32_t ldo, uint32_t lowdrive, uint8_t deepsleepmodecmd)
{
    /* clear stbmod and ldolp bits */
    PMU_CTL0 &= ~((uint32_t)(PMU_CTL0_STBMOD | PMU_CTL0_LDOLP | PMU_CTL0_LDEN | PMU_CTL0_LDNP |
                             PMU_CTL0_LDLP));

    /* set ldolp bit according to pmu_ldo */
    PMU_CTL0 |= ldo;

    /* low drive mode config in deep-sleep mode */
    if(PMU_LOWDRIVER_ENABLE == lowdrive) {
        if(PMU_LDO_NORMAL == ldo) {
            PMU_CTL0 |= (uint32_t)(PMU_CTL0_LDEN | PMU_CTL0_LDNP);
        } else {
            PMU_CTL0 |= (uint32_t)(PMU_CTL0_LDEN | PMU_CTL0_LDLP);
        }
    }

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
    \brief      pmu work in standby mode (API ID(0x000FU))
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
    REG32(0xE000E18CU)  = 0xFFFFFFFFU;

    /* select WFI command to enter standby mode */
    __WFI();
}

/*!
    \brief      enable wakeup pin (API ID(0x0010U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_enable(void)
{
    PMU_CS |= PMU_CS_WUPEN;
}

/*!
    \brief      disable wakeup pin (API ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_disable(void)
{
    PMU_CS &= ~PMU_CS_WUPEN;
}

/*!
    \brief      enable backup domain write (API ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_BKPWEN;
}

/*!
    \brief      disable backup domain write (API ID(0x0013U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_BKPWEN;
}

/*!
    \brief      enable vavd (API ID(0x0015U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vavd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_VAVDEN;
}

/*!
    \brief      disable vavd (API ID(0x0014U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vavd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VAVDEN;
}

/*!
    \brief      enable vovd (API ID(0x0017U))
    \param[in]  none
    \param[out] none
    \retval     none
    \note       Before enabling VOVD, LVD needs to be enabled first, with a delay of at least 50 microseconds, 
                and then VOVD can be enabled.Otherwise, VOVD will generate incorrect trigger signals.
                The subsequent LVD can either remain enabled or be turned off.
*/
void pmu_vovd_enable(void)
{
    uint32_t i;

    if(RESET == (PMU_CTL0 & PMU_CTL0_LVDEN)) {
        pmu_lvd_enable();
    }

    for(i = 0U; i < 2200U; i++) {
        __NOP();
    }

    PMU_CTL0 |= PMU_CTL0_VOVDEN;
}

/*!
    \brief      disable vovd (API ID(0x0016U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vovd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VOVDEN;
}

/*!
    \brief      enable vuvd (API ID(0x0019U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vuvd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_VUVDEN;
}

/*!
    \brief      disable vuvd (API ID(0x0018U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vuvd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VUVDEN;
}

/*!
    \brief      select vavd threshold (API ID(0x001AU))
    \param[in]  vavd_select:
                only one parameter can be selected which is shown as below:
      \arg        PMU_VAVDVC_x: (x:0-3)VAVD threshold
    \param[out] none
    \retval     none
*/
void pmu_vavd_select(uint32_t vavd_select)
{
    PMU_CTL0 &= ~PMU_CTL0_VAVDVC;
    PMU_CTL0 |= vavd_select & PMU_CTL0_VAVDVC;
}

/*!
    \brief      select vovd threshold (API ID(0x001BU))
    \param[in]  vovd_select:
                only one parameter can be selected which is shown as below:
      \arg        PMU_VOVDVC_x: (x:0-3)vovdvc threshold
    \param[out] none
    \retval     none
*/
void pmu_vovd_select(uint32_t vovd_select)
{
    PMU_CTL0 &= ~PMU_CTL0_VOVDVC;
    PMU_CTL0 |= vovd_select & PMU_CTL0_VOVDVC;
}

/*!
    \brief      select vuvd threshold (API ID(0x001CU))
    \param[in]  vuvd_select:
                only one parameter can be selected which is shown as below:
      \arg        PMU_VUVDVC_x: (x:0-2)vuvdvc threshold
    \param[out] none
    \retval     none
*/
void pmu_vuvd_select(uint32_t vuvd_select)
{
    PMU_CTL0 &= ~PMU_CTL0_VUVDVC;
    PMU_CTL0 |= vuvd_select & PMU_CTL0_VUVDVC;
}

/*!
    \brief      select vovdo_dnf (API ID(0x001DU))
    \param[in]  vovdo_value:
                only one parameter can be selected which is shown as below:
      \arg        0~0xff
    \param[out] none
    \retval     none
*/
void pmu_vovdo_dnf_select(uint32_t vovdo_value)
{
    PMU_CTL1 &= ~PMU_CTL1_VOVDO_DNF;
    PMU_CTL1 |= vovdo_value & PMU_CTL1_VOVDO_DNF;
}

/*!
    \brief      select vuvdo_dnf (API ID(0x001EU))
    \param[in]  vuvdo_value:
                only one parameter can be selected which is shown as below:
      \arg       0~0xff
    \param[out] none
    \retval     none
*/
void pmu_vuvdo_dnf_select(uint32_t vuvdo_value)
{
    PMU_CTL1 &= ~PMU_CTL1_VUVDO_DNF;
    PMU_CTL1 |= (vuvdo_value << 8) & PMU_CTL1_VUVDO_DNF;
}

/*!
    \brief      get flag state (API ID(0x001FU))
    \param[in]  flag:
                only one parameter can be selected which is shown as below:
      \arg        PMU_FLAG_WAKEUP: wakeup flag
      \arg        PMU_FLAG_STANDBY: standby flag
      \arg        PMU_FLAG_LVD: lvd flag
      \arg        PMU_FLAG_VAVDF: vavd flag
      \arg        PMU_FLAG_VUVDF0: VCORE low voltage detector flag 0
      \arg        PMU_FLAG_VOVDF:  VCORE over voltage detector flag
      \arg        PMU_FLAG_VUVDF1: VCORE low voltage detector flag 1
      \arg        PMU_FLAG_LDOVSRF: LDO voltage select ready flag
      \arg        PMU_FLAG_LDRF: low-driver mode ready flag
    \param[out] none
    \retval     FlagStatus SET or RESET
*/
FlagStatus pmu_flag_get(uint32_t flag)
{
    FlagStatus ret;

    if(PMU_CS & flag) {
        ret = SET;
    } else {
        ret = RESET;
    }

    return ret;
}

/*!
    \brief      clear flag bit (API ID(0x0020U))
    \param[in]  flag:
                only one parameter can be selected which is shown as below:
      \arg        PMU_FLAG_RESET_WAKEUP: reset wakeup flag
      \arg        PMU_FLAG_RESET_STANDBY: reset standby flag
    \param[out] none
    \retval     none
*/
void pmu_flag_clear(uint32_t flag)
{
    switch(flag) {
        case PMU_FLAG_RESET_WAKEUP:
            /* reset wakeup flag */
            PMU_CTL0 |= PMU_CTL0_WURST;
            break;
        case PMU_FLAG_RESET_STANDBY:
            /* reset standby flag */
            PMU_CTL0 |= PMU_CTL0_STBRST;
            break;
        default :
            break;
    }
}
