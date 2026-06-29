/*!
    \file    gd32w51x_f5hc_pmu.c
    \brief   PMU driver

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

#include "gd32w51x_f5hc_pmu.h"

#define PMU_WAKEUP_PIN_ENABLE_DISABLE_MASK       0x07001F00U           /*!< PMU WKUP Pinx enable and disable configuration mask  */
#define PMU_WAKEUP_PIN_EDGE_SELECTION_MASK       0x380080F0U           /*!< PMU WKUP Pinx edge selection configuration mask  */
#define PMU_WIFI_LOW_POWER_CONTROL_MASK          0x0000000CU           /*!< PMU WIFI low power control configuration mask  */
#define PMU_SRAM_LOW_POWER_CONTROL_MASK          0x00006660U           /*!< PMU SRAM low power control configuration mask  */
#define PMU_RF_FORCE_CFG_MASK                    0x00000006U           /*!< PMU RF force configuration mask  */
#define PMU_SECURE_CFG_MASK                      0x00010FFFU           /*!< PMU secure configuration mask  */
#define PMU_FLAG_CLEAR_MASK                      0x0000000CU           /*!< PMU flag clear mask  */

/*!
    \brief      reset PMU register (API_ID(0x0001U))
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
    \brief      select low voltage detector threshold (API_ID(0x0002U))
    \param[in]  lvdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVDT_0: voltage threshold is 2.1V
      \arg        PMU_LVDT_1: voltage threshold is 2.3V
      \arg        PMU_LVDT_2: voltage threshold is 2.4V
      \arg        PMU_LVDT_3: voltage threshold is 2.6V
      \arg        PMU_LVDT_4: voltage threshold is 2.7V
      \arg        PMU_LVDT_5: voltage threshold is 2.9V
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

#if defined (GD32F5HC)
/*!
    \brief      select deep-sleep mode core voltage (API_ID(0x0003U))
    \param[in]  voltage_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_DSLPVS_0_9: core voltage is 0.9V in Deep-sleep mode
      \arg        PMU_DSLPVS_1_0: core voltage is 1.0V in Deep-sleep mode
      \arg        PMU_DSLPVS_1_1: core voltage is 1.1V in Deep-sleep mode
      \arg        PMU_DSLPVS_1_2: core voltage is 1.2V in Deep-sleep mode
    \param[out] none
    \retval     none
*/
void pmu_deepsleep_voltage_select(uint32_t voltage_n)
{
    /* Unlock the configuration of DSLPVS bit field in PMU_CTL0 */
    PMU_DSLVC_ULKKEY = PMU_DSLPVS_UNL_KEY;
    /* clear DSLPVS bits */
    PMU_CTL0 &= ~PMU_CTL0_DSLPVS;
    /* set DSLPVS bits according to voltage_n */
    PMU_CTL0 |= voltage_n & PMU_CTL0_DSLPVS;
}
#endif /* defined GD32F5HC */

/*!
    \brief      disable PMU LVD (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lvd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_LVDEN;
}

/*!
    \brief      enable PMU VLVD (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vlvd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_VLVDEN;
}

/*!
    \brief      disable PMU VLVD (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vlvd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VLVDEN;
}

/*!
    \brief      select LDO output voltage (API_ID(0x0007U))
                this bit set by software when the main PLL closed, before closing PLL, change the system clock to IRC16M or HXTAL
    \param[in]  ldo_output:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LDOVS_LOW: LDO output voltage low mode
      \arg        PMU_LDOVS_HIGH: LDO output voltage high mode
    \param[out] none
    \retval     none
*/
void pmu_ldo_output_select(uint32_t ldo_output)
{
    PMU_CTL0 &= ~PMU_CTL0_LDOVS;
    PMU_CTL0 |= ldo_output & PMU_CTL0_LDOVS;
}

/*!
    \brief      PMU work in sleep mode (API_ID(0x0008U))
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
    if(WFI_CMD == sleepmodecmd){
        __WFI();
    }else{
        __SEV();
        __WFE();
        __WFE();
    }
}

/*!
    \brief      PMU work in deep-sleep mode (API_ID(0x0009U))
    \param[in]  ldo:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LDO_NORMAL: LDO normal work when PMU enter deepsleep mode
      \arg        PMU_LDO_LOWPOWER: LDO work at low power mode when PMU enter deepsleep mode
    \param[in]  lowdrive:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LOWDRIVER_DISABLE: Low-driver mode disable in deep-sleep mode
      \arg        PMU_LOWDRIVER_ENABLE: Low-driver mode enable in deep-sleep mode
    \param[in]  deepsleepmodecmd:
                only one parameter can be selected which is shown as below:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_deepsleepmode(uint32_t ldo, uint32_t lowdrive, uint8_t deepsleepmodecmd)
{   
    /* clear stbmod and ldolp bits and low drive bits */
    PMU_CTL0 &= ~((uint32_t)(PMU_CTL0_STBMOD | PMU_CTL0_LDOLP | PMU_CTL0_LDEN | PMU_CTL0_LDNP | PMU_CTL0_LDLP));
    
    /* set ldolp bit according to pmu_ldo */
    PMU_CTL0 |= ldo & PMU_CTL0_LDOLP;
    
    /* low drive mode config in deep-sleep mode */
    if(PMU_LOWDRIVER_ENABLE == lowdrive){
        if(PMU_LDO_NORMAL == ldo){
            PMU_CTL0 |= (uint32_t)(PMU_CTL0_LDEN | PMU_CTL0_LDNP);
        }else{
            PMU_CTL0 |= (uint32_t)(PMU_CTL0_LDEN | PMU_CTL0_LDLP);
        }
    }
    
    /* set sleepdeep bit of Cortex-M33 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    
    /* select WFI or WFE command to enter deepsleep mode */
    if(WFI_CMD == deepsleepmodecmd){
        __WFI();
    }else{
        __SEV();
        __WFE();
        __WFE();
    }    
    /* reset sleepdeep bit of Cortex-M33 system control register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/*!
    \brief      PMU work in standby mode (API_ID(0x000AU))
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

    REG32( 0xE000E010U ) &= 0x00010004U;
    REG32( 0xE000E180U )  = 0XFF8FFFF3U;
    REG32( 0xE000E184U )  = 0XFFFFFDFFU;
    REG32( 0xE000E188U )  = 0xFFFFFFFFU;
    REG32( 0xE000E18CU )  = 0xFFFFFFFFU;

    /* enter standby mode */
    __WFI();

}

/*!
    \brief      enable wakeup pin (API_ID(0x000BU))
    \param[in]  wakeup_pin:
                one or more parameters can be selected which are shown as below:
      \arg        PMU_WAKEUP_PIN0: WKUP Pin 0 (PA2)
      \arg        PMU_WAKEUP_PIN1: WKUP Pin 1 (PA15)
      \arg        PMU_WAKEUP_PIN2: WKUP Pin 2 (PB2)
      \arg        PMU_WAKEUP_PIN3: WKUP Pin 3 (PA12)
      \arg        PMU_WAKEUP_PIN4: WKUP Pin 4 (PD5)
      \arg        PMU_WAKEUP_PIN5: WKUP Pin 5 (PD4)
      \arg        PMU_WAKEUP_PIN6: WKUP Pin 6 (PB0)
      \arg        PMU_WAKEUP_PIN7: WKUP Pin 7 (PD3)
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_enable(uint32_t wakeup_pin)
{
    PMU_CS0 |= wakeup_pin & PMU_WAKEUP_PIN_ENABLE_DISABLE_MASK;
}

/*!
    \brief      disable wakeup pin (API_ID(0x000CU))
    \param[in]  wakeup_pin:
                one or more parameters can be selected which are shown as below:
      \arg        PMU_WAKEUP_PIN0: WKUP Pin 0 (PA2)
      \arg        PMU_WAKEUP_PIN1: WKUP Pin 1 (PA15)
      \arg        PMU_WAKEUP_PIN2: WKUP Pin 2 (PB2)
      \arg        PMU_WAKEUP_PIN3: WKUP Pin 3 (PA12)
      \arg        PMU_WAKEUP_PIN4: WKUP Pin 4 (PD5)
      \arg        PMU_WAKEUP_PIN5: WKUP Pin 5 (PD4)
      \arg        PMU_WAKEUP_PIN6: WKUP Pin 6 (PB0)
      \arg        PMU_WAKEUP_PIN7: WKUP Pin 7 (PD3)
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_disable(uint32_t wakeup_pin)
{
    PMU_CS0 &= ~(wakeup_pin & PMU_WAKEUP_PIN_ENABLE_DISABLE_MASK);
}

#if defined (GD32F5HC)
/*!
    \brief      wakeup pin edge selection (API_ID(0x000DU))
    \param[in]  wakeup_pin_edge:
                one or more parameters can be selected which are shown as below:
      \arg        PMU_WAKEUP_PIN0_EDGE: WKUP Pin 0 (PA2) edge selection
      \arg        PMU_WAKEUP_PIN1_EDGE: WKUP Pin 1 (PA15) edge selection
      \arg        PMU_WAKEUP_PIN2_EDGE: WKUP Pin 2 (PB2) edge selection
      \arg        PMU_WAKEUP_PIN3_EDGE: WKUP Pin 3 (PA12) edge selection 
      \arg        PMU_WAKEUP_PIN4_EDGE: WKUP Pin 4 (PD5) edge selection
      \arg        PMU_WAKEUP_PIN5_EDGE: WKUP Pin 5 (PD4) edge selection
      \arg        PMU_WAKEUP_PIN6_EDGE: WKUP Pin 6 (PB0) edge selection 
      \arg        PMU_WAKEUP_PIN7_EDGE: WKUP Pin 7 (PD3) edge selection
    \param[in]  edge_type:
                only one parameter can be selected which is shown as below:
      \arg        WAKEUP_PIN_EDGE_RISING: WKUP pin active on rising edge 
      \arg        WAKEUP_PIN_EDGE_FALLING: WKUP pin active on falling edge
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_edge_select(uint32_t wakeup_pin_edge, uint32_t edge_type)
{
    if(WAKEUP_PIN_EDGE_RISING == edge_type)
    {
        PMU_CS0 &= ~(wakeup_pin_edge & PMU_WAKEUP_PIN_EDGE_SELECTION_MASK);
    } else if(WAKEUP_PIN_EDGE_FALLING == edge_type) {
        PMU_CS0 |= wakeup_pin_edge & PMU_WAKEUP_PIN_EDGE_SELECTION_MASK;
    } else {}
}
#endif /* defined GD32F5HC */

/*!
    \brief      enable backup domain write (API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_BKPWEN;
}

/*!
    \brief      disable backup domain write (API_ID(0x000FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_BKPWEN;
}

#if defined (GD32W515)
/*!
    \brief      WIFI power enable (API_ID(0x0010U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_wifi_power_enable(void)
{
    PMU_CTL1 |= PMU_CTL1_WPEN;
}

/*!
    \brief      WIFI power disable (API_ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_wifi_power_disable(void)
{
    PMU_CTL1 &= ~PMU_CTL1_WPEN;
}

/*!
    \brief      WIFI low power control (API_ID(0x0012U))
    \param[in]  wifi_lpwr_cfg: 
                one or more parameters can be selected which are shown as below:
      \arg        PMU_WIFI_SLEEP: WIFI go to sleep
      \arg        PMU_WIFI_WAKE: WIFI wakeup
    \param[out] none
    \retval     none
*/
void pmu_wifi_low_power_control(uint32_t wifi_lpwr_cfg)
{
    PMU_CTL1 |= wifi_lpwr_cfg & PMU_WIFI_LOW_POWER_CONTROL_MASK;
}

#endif /* defined (GD32W515) */

/*!
    \brief      SRAM low power control (API_ID(0x0013U))
    \param[in]  sram_lpwr_cfg: 
                one or more parameters can be selected which are shown as below:
      \arg        PMU_SRAM1_SLEEP: SRAM1 go to sleep
      \arg        PMU_SRAM1_WAKE: SRAM1 wakeup
      \arg        PMU_SRAM2_SLEEP: SRAM2 go to sleep
      \arg        PMU_SRAM2_WAKE: SRAM2 wakeup
      \arg        PMU_SRAM3_SLEEP: SRAM3 go to sleep
      \arg        PMU_SRAM3_WAKE: SRAM3 wakeup
    \param[out] none
    \retval     none
*/
void pmu_sram_low_power_control(uint32_t sram_lpwr_cfg)
{
    PMU_CTL1 |= sram_lpwr_cfg & PMU_SRAM_LOW_POWER_CONTROL_MASK;
}

#if defined (GD32W515)
/*!
    \brief      RF sequence force open/close (API_ID(0x0014U))
    \param[in]  force: 
                only one parameter can be selected which is shown as below:
      \arg        PMU_RF_FORCE_OPEN: Software force start, open RF power
      \arg        PMU_RF_FORCE_CLOSE: Software force close, close RF power
    \param[out] none
    \retval     none
*/
void pmu_rf_force_enable(uint32_t force)
{
    PMU_RFCTL |= force & PMU_RF_FORCE_CFG_MASK;
}

/*!
    \brief      disable RF sequence open/close force (API_ID(0x0015U))
    \param[in]  force: 
                only one parameter can be selected which is shown as below:
      \arg        PMU_RF_FORCE_OPEN: Software force start, open RF power
      \arg        PMU_RF_FORCE_CLOSE: Software force close, close RF power
    \param[out] none
    \retval     none
*/
void pmu_rf_force_disable(uint32_t force)
{
    PMU_RFCTL &= ~(force & PMU_RF_FORCE_CFG_MASK);
}

/*!
    \brief      RF sequence configuration (API_ID(0x0016U))
    \param[in]  mode: 
                only one parameter can be selected which is shown as below:
      \arg        PMU_RF_SOFTWARE: RF software sequence enable
      \arg        PMU_RF_HARDWARE: RF hardware sequence enable
    \param[out] none
    \retval     none
*/
void pmu_rf_sequence_config(uint32_t mode)
{
    PMU_RFCTL &= ~PMU_RFCTL_RFSWEN;
    PMU_RFCTL |= mode & PMU_RFCTL_RFSWEN;
}
#endif /* defined (GD32W515) */

/*!
    \brief      enable the security attribution (API_ID(0x0017U))
    \param[in]  security: 
                one or more parameters can be selected which are shown as below:
      \arg        PMU_SEC_WAKEUP_PIN0: WKUP pin 0 security
      \arg        PMU_SEC_WAKEUP_PIN1: WKUP pin 1 security
      \arg        PMU_SEC_WAKEUP_PIN2: WKUP pin 2 security
      \arg        PMU_SEC_WAKEUP_PIN3: WKUP pin 3 security
      \arg        PMU_SEC_WAKEUP_PIN4: WKUP pin 4 security
      \arg        PMU_SEC_WAKEUP_PIN5: WKUP pin 5 security
      \arg        PMU_SEC_WAKEUP_PIN6: WKUP pin 6 security
      \arg        PMU_SEC_WAKEUP_PIN7: WKUP pin 7 security
      \arg        PMU_SEC_LPLDO_DPSLP_STB: Low-power mode security
      \arg        PMU_SEC_LVD_VLVD: Voltage detection and monitoring security
      \arg        PMU_SEC_BACKUP_WRITE: Backup Domain write access security
      \arg        PMU_SEC_WIFI_SRAM_CONTROL: WIFI_sleep and SRAM_sleep mode security
      \arg        PMU_SEC_RF_SEQUENCE: RF security
    \param[out] none
    \retval     none
*/
void pmu_security_enable(uint32_t security)
{
    PMU_SECCFG |= security & PMU_SECURE_CFG_MASK;
}
/*!
    \brief      disable the security attribution (API_ID(0x0018U))
    \param[in]  security: 
                one or more parameters can be selected which are shown as below:
      \arg        PMU_SEC_WAKEUP_PIN0: WKUP pin 0 security
      \arg        PMU_SEC_WAKEUP_PIN1: WKUP pin 1 security
      \arg        PMU_SEC_WAKEUP_PIN2: WKUP pin 2 security
      \arg        PMU_SEC_WAKEUP_PIN3: WKUP pin 3 security
      \arg        PMU_SEC_WAKEUP_PIN4: WKUP pin 4 security
      \arg        PMU_SEC_WAKEUP_PIN5: WKUP pin 5 security
      \arg        PMU_SEC_WAKEUP_PIN6: WKUP pin 6 security
      \arg        PMU_SEC_WAKEUP_PIN7: WKUP pin 7 security
      \arg        PMU_SEC_LPLDO_DPSLP_STB: Low-power mode security
      \arg        PMU_SEC_LVD_VLVD: Voltage detection and monitoring security
      \arg        PMU_SEC_BACKUP_WRITE: Backup Domain write access security
      \arg        PMU_SEC_WIFI_SRAM_CONTROL: WIFI_sleep and SRAM_sleep mode security
      \arg        PMU_SEC_RF_SEQUENCE: RF security
    \param[out] none
    \retval     none
*/
void pmu_security_disable(uint32_t security)
{
    PMU_SECCFG &= ~(security & PMU_SECURE_CFG_MASK);
}

/*!
    \brief      enable the privileged access only (API_ID(0x0019U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_privilege_enable(void)
{
    PMU_PRICFG |= PMU_PRICFG_PRIV;
}
/*!
    \brief      disable the privileged access only (API_ID(0x001AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_privilege_disable(void)
{
    PMU_PRICFG &= ~PMU_PRICFG_PRIV;
}

/*!
    \brief      get flag state (API_ID(0x001BU))
    \param[in]  flag:
                only one parameter can be selected which is shown as below:
      \arg        PMU_FLAG_WAKEUP: wakeup flag
      \arg        PMU_FLAG_STANDBY: standby flag
      \arg        PMU_FLAG_LVD: VDD low voltage flag
      \arg        PMU_FLAG_VLVD: VDDA low voltage flag
      \arg        PMU_FLAG_LDOVSRF: LDO voltage select ready flag
      \arg        PMU_FLAG_LDRF: low-driver mode ready flag 
      \arg        PMU_FLAG_WIFI_SLEEP: WIFI is in sleep state
      \arg        PMU_FLAG_WIFI_ACTIVE: WIFI is in active state
      \arg        PMU_FLAG_SRAM1_SLEEP: SRAM1 is in sleep state
      \arg        PMU_FLAG_SRAM1_ACTIVE: SRAM1 is in active state
      \arg        PMU_FLAG_SRAM2_SLEEP: SRAM2 is in sleep state
      \arg        PMU_FLAG_SRAM2_ACTIVE: SRAM2 is in active state
      \arg        PMU_FLAG_SRAM3_SLEEP: SRAM3 is in sleep state
      \arg        PMU_FLAG_SRAM3_ACTIVE: SRAM3 is in active state
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus pmu_flag_get(uint32_t flag)
{
    FlagStatus ret = RESET;
    if(flag & BIT(31)){
        flag &= ~BIT(31);
        /* get WIFI SRAM status */
        if(PMU_CS1 & flag){
            ret = SET;
        }else{
            ret = RESET;
        }        
    }else{
        /* get flag status in PMU_CS0 */
        if(PMU_CS0 & flag){
            ret = SET;
        }else{
            ret = RESET;
        }    
    }
    return ret;
}

/*!
    \brief      clear flag bit (API_ID(0x001CU))
    \param[in]  flag:
                only one parameter can be selected which is shown as below:
      \arg        PMU_FLAG_RESET_WAKEUP: reset wakeup flag
      \arg        PMU_FLAG_RESET_STANDBY: reset standby flag
    \param[out] none
    \retval     none
*/
void pmu_flag_clear(uint32_t flag)
{
    PMU_CTL0 |= flag & PMU_FLAG_CLEAR_MASK;
}
