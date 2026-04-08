/*!
    \file    gd32m53x_pmu.c
    \brief   PMU driver

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

#include "gd32m53x_pmu.h"

#define PMU_LVD_INT_MASK                    0x00000008U       /*!< low voltage detector interrupt mask */
#define PMU_LVD_RESET_MASK                  0x00000040U       /*!< low voltage detector reset mask */
#define PMU_LVD_NEGATION_MASK               0x00000080U       /*!< low voltage detector negation mask */
#define PMU_LVDT_MASK                       0x00000F00U       /*!< low voltage detector threshold mask */
#define PMU_LVDSAMP_MASK                    0x00006000U       /*!< low voltage detector sampling clock mask */

/*!
    \brief      reset PMU registers (API_ID(0x0001U))
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
    \brief      PMU work at sleep mode (API_ID(0x0002U))
    \param[in]  sleepmodecmd: command to enter sleep mode
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
    } else if(WFE_CMD == sleepmodecmd) {
        __SEV();
        __WFE();
        __WFE();
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      PMU work at deepsleep mode (API_ID(0x0003U))
    \param[in]  deepsleepmodecmd: command to enter deepsleep mode
                only one parameter can be selected which is shown as below:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_deepsleepmode(uint8_t deepsleepmodecmd)
{
    static uint32_t reg_snap[ 4 ];
    /* clear stbmod bits */
    PMU_CTL &= ~((uint32_t)PMU_CTL_STBMOD);

    /* set sleepdeep bit of Cortex-M33 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    reg_snap[ 0 ] = REG32(0xE000E010U);
    reg_snap[ 1 ] = REG32(0xE000E100U);
    reg_snap[ 2 ] = REG32(0xE000E104U);
    reg_snap[ 3 ] = REG32(0xE000E108U);

    REG32(0xE000E010U) &= 0x00010004U;
    REG32(0xE000E180U)  = 0xFF7FF839U;
    REG32(0xE000E184U)  = 0xFFFFFEFFU;
    REG32(0xE000E188U)  = 0xFF87FC33U;

    /* select WFI or WFE command to enter deepsleep mode */
    if(WFI_CMD == deepsleepmodecmd) {
        __WFI();
    } else if(WFE_CMD == deepsleepmodecmd) {
        __SEV();
        __WFE();
        __WFE();
    } else {
        /* illegal parameters */
    }

    REG32(0xE000E010U) = reg_snap[ 0 ] ;
    REG32(0xE000E100U) = reg_snap[ 1 ] ;
    REG32(0xE000E104U) = reg_snap[ 2 ] ;
    REG32(0xE000E108U) = reg_snap[ 3 ] ;

    /* reset sleepdeep bit of Cortex-M33 system control register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/*!
    \brief      pmu work at standby mode (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_to_standbymode(void)
{
    /* set sleepdeep bit of Cortex-M33 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* set stbmod bit */
    PMU_CTL |= PMU_CTL_STBMOD;

    /* reset wakeup flag */
    PMU_CTL |= PMU_CTL_WURST;

    REG32(0xE000E010U) &= 0x00010004U;
    REG32(0xE000E180U)  = 0XFFFFFFFFU;
    REG32(0xE000E184U)  = 0XFFFFFFFFU;
    REG32(0xE000E188U)  = 0xFFFFFFFFU;

    /* select WFI or WFE command to enter standby mode */
    __WFI();

}

/*!
    \brief      PMU work in deepsleep mode ldo voltage output select  (API_ID(0x0005U))
    \param[in]  dsldovs: deep-sleep mode voltage scaling selection
                only one parameter can be selected which is shown as below:
      \arg        PMU_DSLDOVS_0: LDO voltage is 0.9V
      \arg        PMU_DSLDOVS_1: LDO voltage is 1.0V
      \arg        PMU_DSLDOVS_2: LDO voltage is 1.1V
      \arg        PMU_DSLDOVS_3: LDO voltage is 1.2V
    \param[out] none
    \retval     none
*/
void pmu_deepsleepmode_vcore_output(uint32_t dsldovs)
{
    PMU_CTL &= ~PMU_CTL_DSLDOVS;
    PMU_CTL |= dsldovs & PMU_CTL_DSLDOVS;
}

/*!
    \brief      enable PMU wakeup pin  (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_enable(void)
{
    PMU_CS |= PMU_CS_WUPEN;
}

/*!
    \brief      disable PMU wakeup pin  (API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_disable(void)
{
    PMU_CS &= ~PMU_CS_WUPEN;
}

/*!
    \brief      enable low voltage detector  (API_ID(0x0008U))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[out] none
    \retval     none
*/
void pmu_lvd_enable(uint8_t lvd_select)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1EN;
        PMU_LVD1CTL |= PMU_LVD1CTL_LVD1EN;
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2EN;
        PMU_LVD2CTL |= PMU_LVD2CTL_LVD2EN;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      disable low voltage detector  (API_ID(0x0009U))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[out] none
    \retval     none
*/
void pmu_lvd_disable(uint8_t lvd_select)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1EN;
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2EN;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      select the interrupt generation condition for the low voltage detector  (API_ID(0x000AU))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[in]  select_condition: Low voltage detector interrupt trigger mode
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_INT_RISING: vcc >= vdetx(rising)
      \arg        PMU_LVD_INT_FALLING: vcc < vdetx(falling)
      \arg        PMU_LVD_INT_BOTH: vcc >= vdetx(rising) or vcc < vdetx(falling)
    \param[out] none
    \retval     none
*/
void pmu_lvd_interrupt_select(uint8_t lvd_select, uint32_t select_condition)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1INTSEL;
        PMU_LVD1CTL |= select_condition;
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2INTSEL;
        PMU_LVD2CTL |= select_condition;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      select the interrupt type for the low voltage detector  (API_ID(0x000BU))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[in]  interrupt_type: low voltage detector interrupt type select
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_INT_MASKABLE: maskable interrupt
      \arg        PMU_LVD_INT_NON_MASKABLE: non-maskable interrupt
    \param[out] none
    \retval     none
*/
void pmu_lvd_interrupt_type(uint8_t lvd_select, uint32_t interrupt_type)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1ITSEL;
        if(PMU_LVD_INT_MASKABLE == interrupt_type) {
            PMU_LVD1CTL |= interrupt_type & PMU_LVD_INT_MASK;
        } else {
            PMU_LVD1CTL &= ~PMU_LVD_INT_MASKABLE;
        }
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2ITSEL;
        if(PMU_LVD_INT_MASKABLE == interrupt_type) {
            PMU_LVD2CTL |= interrupt_type & PMU_LVD_INT_MASK;
        } else {
            PMU_LVD2CTL &= ~PMU_LVD_INT_MASKABLE;
        }
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable low voltage detector interrupt or reset  (API_ID(0x000CU))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[out] none
    \retval     none
*/
void pmu_lvd_interrupt_reset_enable(uint8_t lvd_select)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1IRE;
        PMU_LVD1CTL |= PMU_LVD1CTL_LVD1IRE;
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2IRE;
        PMU_LVD2CTL |= PMU_LVD2CTL_LVD2IRE;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      disable low voltage detector interrupt or reset (API_ID(0x000DU))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[out] none
    \retval     none
*/
void pmu_lvd_interrupt_reset_disable(uint8_t lvd_select)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1IRE;
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2IRE;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable low voltage detector comparison result output (API_ID(0x000EU))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[out] none
    \retval     none
*/
void pmu_lvd_output_enable(uint8_t lvd_select)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1OUTEN;
        PMU_LVD1CTL |= PMU_LVD1CTL_LVD1OUTEN;
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2OUTEN;
        PMU_LVD2CTL |= PMU_LVD2CTL_LVD2OUTEN;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      disable low voltage detector comparison result output  (API_ID(0x000FU))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[out] none
    \retval     none
*/
void pmu_lvd_output_disable(uint8_t lvd_select)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1OUTEN;
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2OUTEN;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      select low voltage detector mode (API_ID(0x0010U))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[in]  mode: low voltage detector mode
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_RESET: low voltage detector reset occurs when the voltage falls below vdetx
      \arg        PMU_LVD_INTERRUPT: low voltage detector interrupt occurs when the voltage falls below vdetx
    \param[out] none
    \retval     none
*/
void pmu_lvd_mode_select(uint8_t lvd_select, uint32_t mode)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1MSEL;
        if(PMU_LVD_RESET == mode) {
            PMU_LVD1CTL |= mode & PMU_LVD_RESET_MASK;
        } else {
            PMU_LVD1CTL &= ~PMU_LVD_RESET;
        }
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD1CTL_LVD1MSEL;
        if(PMU_LVD_RESET == mode) {
            PMU_LVD2CTL |= mode & PMU_LVD_RESET_MASK;
        } else {
            PMU_LVD2CTL &= ~PMU_LVD_RESET;
        }
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      select low voltage detector reset negation (API_ID(0x0011U))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[in]  mode: low voltage detector reset signal negation mode
                only one parameter can be selected which is shown as below(x=1,2):
      \arg        PMU_LVD_RESET_ASSERTION: after the LVD reset signal is asserted, the reset signal will be negated after a stabilization time (tLVDx)
      \arg        PMU_LVD_RESET_RISE: the reset signal will be negated after a stabilization time (tLVDx) following the detection of VCC > Vdetx
    \param[out] none
    \retval     none
*/
void pmu_lvd_reset_select(uint8_t lvd_select, uint32_t mode)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1RSTSEL;
        if(PMU_LVD_RESET_ASSERTION == mode) {
            PMU_LVD1CTL |= mode & PMU_LVD_NEGATION_MASK;
        } else {
            PMU_LVD1CTL &= ~PMU_LVD_RESET_ASSERTION;
        }
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2RSTSEL;
        if(PMU_LVD_RESET_ASSERTION == mode) {
            PMU_LVD2CTL |= mode & PMU_LVD_NEGATION_MASK;
        } else {
            PMU_LVD2CTL &= ~PMU_LVD_RESET_ASSERTION;
        }
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      select low voltage detector threshold (API_ID(0x0012U))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[in]  level: low voltage detector threshold
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVDT_0: low voltage detector level is 4.62v/4.54v
      \arg        PMU_LVDT_1: low voltage detector level is 4.55v/4.47v
      \arg        PMU_LVDT_2: low voltage detector level is 4.40v/4.32v
      \arg        PMU_LVDT_3: low voltage detector level is 3.03v/2.95v
      \arg        PMU_LVDT_4: low voltage detector level is 2.96v/2.88v
    \param[out] none
    \retval     none
*/
void pmu_lvd_level_select(uint8_t lvd_select, uint32_t level)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1T;
        PMU_LVD1CTL |= level & PMU_LVDT_MASK;
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2T;
        PMU_LVD2CTL |= level & PMU_LVDT_MASK;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable low voltage detector digital filter (API_ID(0x0013U))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[out] none
    \retval     none
*/
void pmu_lvd_digital_filter_enable(uint8_t lvd_select)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1DNF;
        PMU_LVD1CTL |= PMU_LVD1CTL_LVD1DNF;
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2DNF;
        PMU_LVD2CTL |= PMU_LVD2CTL_LVD2DNF;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      disable low voltage detector digital filter (API_ID(0x0014U))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[out] none
    \retval     none
*/
void pmu_lvd_digital_filter_disable(uint8_t lvd_select)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1DNF;
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2DNF;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      select low voltage detector sampling clock (API_ID(0x0015U))
    \param[in]  lvd_select: select low voltage detector
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVD_1: select low voltage detector 1
      \arg        PMU_LVD_2: select low voltage detector 2
    \param[in]  clock: low voltage detector sampling clock
                only one parameter can be selected which is shown as below(x=1,2):
      \arg        PMU_LVDSAMP_DIV2: low voltage detector sampling clock select 1/2 pclk1 frequency
      \arg        PMU_LVDSAMP_DIV4: low voltage detector sampling clock select 1/4 pclk1 frequency
      \arg        PMU_LVDSAMP_DIV8: low voltage detector sampling clock select 1/8 pclk1 frequency
      \arg        PMU_LVDSAMP_DIV16: low voltage detector sampling clock select 1/16 pclk1 frequency
    \param[out] none
    \retval     none
*/
void pmu_lvd_sample_clock_select(uint8_t lvd_select, uint32_t clock)
{
    if(PMU_LVD_1 == lvd_select) {
        PMU_LVD1CTL &= ~PMU_LVD1CTL_LVD1SAMP;
        PMU_LVD1CTL |= clock & PMU_LVDSAMP_MASK;
    } else if(PMU_LVD_2 == lvd_select) {
        PMU_LVD2CTL &= ~PMU_LVD2CTL_LVD2SAMP;
        PMU_LVD2CTL |= clock & PMU_LVDSAMP_MASK;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      get flag state (API_ID(0x0016U))
    \param[in]  flag: flag
                only one parameter can be selected which is shown as below:
      \arg        PMU_FLAG_WAKEUP: wakeup flag
      \arg        PMU_FLAG_STANDBY: standby flag
      \arg        PMU_FLAG_LVD1DETF: low voltage detector 1 voltage change detection flag
      \arg        PMU_FLAG_LVD1OSF: low voltage detector 1 output signal flag
      \arg        PMU_FLAG_LVD2DETF: low voltage detector 2 voltage change detection flag
      \arg        PMU_FLAG_LVD2OSF: low voltage detector 2 output signal flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus pmu_flag_get(uint32_t flag)
{
    FlagStatus ret = RESET;

    /* get flag status in PMU_CS0 */
    if(PMU_CS & flag) {
        ret = SET;
    } else {
        ret = RESET;
    }
    return ret;
}

/*!
    \brief      clear flag state (API_ID(0x0017U))
    \param[in]  flag: flag
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
        PMU_CTL |= PMU_CTL_WURST;
        break;
    case PMU_FLAG_RESET_STANDBY:
        /* reset standby flag */
        PMU_CTL |= PMU_CTL_STBRST;
        break;
    default :
        break;
    }
}
