/*!
    \file    gd32f50x_rcu.c
    \brief   RCU driver

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

#include "gd32f50x_rcu.h"

/* define clock source */
#define SEL_IRC8M                   ((uint16_t)0U)  /* IRC8M is selected as CK_SYS */
#define SEL_HXTAL                   ((uint16_t)1U)  /* HXTAL is selected as CK_SYS */
#define SEL_PLL0P                   ((uint16_t)2U)  /* PLL0P is selected as CK_SYS */

/* define startup timeout count */
#define OSC_STARTUP_TIMEOUT         ((uint32_t)0x000FFFFFU)
#define LXTAL_STARTUP_TIMEOUT       ((uint32_t)0x03FFFFFFU)

/* ADC clock prescaler offset */
#define RCU_ADC_PSC_OFFSET          ((uint32_t)14U)

/* RCU IRC8M adjust value mask and offset*/
#define RCU_IRC8M_ADJUST_MASK       ((uint8_t)0x1FU)
#define RCU_IRC8M_ADJUST_OFFSET     ((uint32_t)3U)

/* RCU PLL1 clock multiplication factor offset */
#define RCU_CFG1_PLL1MF_OFFSET      ((uint32_t)8U)
/* RCU PREDIV1 division factor offset*/
#define RCU_CFG1_PREDIV1_OFFSET      ((uint32_t)4U)
/* RCU PREDIV0 division factor offset*/
#define RCU_CFG1_PREDIV0_OFFSET      ((uint32_t)0U)

/* RCU parameter mask */
#define RCU_ADCPSC_MASK            (0x0000000FU)        /* RCU ADC prescaler select mask */

/*!
    \brief      deinitialize the RCU (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_deinit(void)
{
    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;
    rcu_osci_stab_wait(RCU_IRC8M);

    RCU_CFG0 &= ~RCU_CFG0_SCS;

    /* reset CTL register */
    RCU_CTL &= ~(RCU_CTL_HXTALEN | RCU_CTL_HCKMEN | RCU_CTL_PLL0EN | RCU_CTL_PLL1EN);
    RCU_CTL &= ~RCU_CTL_HXTALBPS;

    /* reset CFG0 register */
    RCU_CFG0 &= ~(RCU_CFG0_SCS | RCU_CFG0_AHBPSC | RCU_CFG0_APB1PSC | RCU_CFG0_APB2PSC |
                  RCU_CFG0_ADCPSC | RCU_CFG0_PREDIV0_LSB | RCU_CFG0_PLL0MF_0_3 |
                  RCU_CFG0_USBFSPSC | RCU_CFG0_CKOUTSEL | RCU_CFG0_PLL0MF_4_5 | RCU_CFG0_USBFSPSC_2);
    /* reset INT register */
    RCU_INT = 0x01BF0000U;

    /* reset ADDINT register */
    RCU_ADDINT = 0x00400000U;

    /* reset CFG1 register */
    RCU_CFG1 &= ~(RCU_CFG1_PREDIV0 | RCU_CFG1_PREDIV1 | RCU_CFG1_PLL1MF | RCU_CFG1_PLL1SEL | RCU_CFG1_PLL0SEL
                  | RCU_CFG1_I2S1SEL | RCU_CFG1_I2S2SEL | RCU_CFG1_ADCPSC_3 | RCU_CFG1_HXTALRDYRST);

    /* reset PLLBWCFG register */
    RCU_PLLBWCFG &= ~(RCU_PLLBWCFG_PLL0_BW_CFG | RCU_PLLBWCFG_PLL1_BW_CFG);
    
    /* reset DSV register */
    RCU_DSV = 0x000A0000U;

    /* reset CKFMCFG0 register */
    RCU_CKFMCFG0 = 0x00000010U;
    /* reset CKFMCFG1 register */
    RCU_CKFMCFG1 = 0x80000000U;
    /* reset CKFMCFG2 register */
    RCU_CKFMCFG2 = 0x80000000U;
    /* reset CKFMCFG3 register */
    RCU_CKFMCFG3 = 0x80000000U;

    /* reset ADDCTL register */
    RCU_ADDCTL &= ~(RCU_ADDCTL_CK48MSEL | RCU_ADDCTL_FMCSEL | RCU_ADDCTL_I2S1DIV | RCU_ADDCTL_PLL0DIV 
                    | RCU_ADDCTL_FMCDIV | RCU_ADDCTL_I2S2DIV);
}

/*!
    \brief      enable the peripherals clock (API_ID(0x0002U))
    \param[in]  periph: RCU peripherals, refer to rcu_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_DMAx (x = 0,1): DMA clock
      \arg        RCU_CRC: CRC clock
      \arg        RCU_EXMC: EXMC clock
      \arg        RCU_USBFS: USBFS clock
      \arg        RCU_CAU: CAU clock
      \arg        RCU_HAU: HAU clock
      \arg        RCU_TRNG: TRNG clock
      \arg        RCU_DMAMUX: DMAMUX clock
      \arg        RCU_TIMERx (x = 0,1,2,3,4,5,6,7,16): TIMER clock
      \arg        RCU_WWDGT: WWDGT clock
      \arg        RCU_SPIx (x = 0,1,2): SPI clock
      \arg        RCU_USARTx (x = 0,1,2): USART clock
      \arg        RCU_UARTx (x = 3,4): UART clock
      \arg        RCU_I2Cx (x = 0,1): I2C clock
      \arg        RCU_CMP: CMP clock
      \arg        RCU_BKPI: BKP interface clock
      \arg        RCU_PMU: PMU clock
      \arg        RCU_DAC: DAC clock
      \arg        RCU_RTC: RTC clock
      \arg        RCU_CTC: CTC clock
      \arg        RCU_AF : alternate function clock
      \arg        RCU_GPIOx (x = A,B,C,D,E): GPIO ports clock
      \arg        RCU_ADCx (x = 0,1,2): ADC clock
      \arg        RCU_TRIGSEL: TRIGSEL clock
      \arg        RCU_SYSCFG:SYSCFG clock
      \arg        RCU_CANx (x = 0,1): CAN clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_enable(rcu_periph_enum periph)
{
    RCU_REG_VAL(periph) |= BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      disable the peripherals clock (API_ID(0x0003U))
    \param[in]  periph: RCU peripherals, refer to rcu_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_DMAx (x = 0,1): DMA clock
      \arg        RCU_CRC: CRC clock
      \arg        RCU_EXMC: EXMC clock
      \arg        RCU_USBFS: USBFS clock
      \arg        RCU_CAU: CAU clock
      \arg        RCU_HAU: HAU clock
      \arg        RCU_TRNG: TRNG clock
      \arg        RCU_DMAMUX: DMAMUX clock
      \arg        RCU_TIMERx (x = 0,1,2,3,4,5,6,7,16): TIMER clock
      \arg        RCU_WWDGT: WWDGT clock
      \arg        RCU_SPIx (x = 0,1,2): SPI clock
      \arg        RCU_USARTx (x = 0,1,2): USART clock
      \arg        RCU_UARTx (x = 3,4): UART clock
      \arg        RCU_I2Cx (x = 0,1): I2C clock
      \arg        RCU_CMP: CMP clock
      \arg        RCU_BKPI: BKP interface clock
      \arg        RCU_PMU: PMU clock
      \arg        RCU_DAC: DAC clock
      \arg        RCU_RTC: RTC clock
      \arg        RCU_CTC: CTC clock
      \arg        RCU_AF : alternate function clock
      \arg        RCU_GPIOx (x = A,B,C,D,E): GPIO ports clock
      \arg        RCU_ADCx (x = 0,1,2): ADC clock
      \arg        RCU_TRIGSEL: TRIGSEL clock
      \arg        RCU_SYSCFG:SYSCFG clock
      \arg        RCU_CANx (x = 0,1): CAN clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_disable(rcu_periph_enum periph)
{
    RCU_REG_VAL(periph) &= ~BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      enable the peripherals clock when sleep mode (API_ID(0x0004U))
    \param[in]  periph: RCU peripherals, refer to rcu_periph_sleep_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_SRAM_SLP: SRAM clock
      \arg        RCU_FMC_SLP: FMC clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_sleep_enable(rcu_periph_sleep_enum periph)
{
    RCU_REG_VAL(periph) |= BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      disable the peripherals clock when sleep mode (API_ID(0x0005U))
    \param[in]  periph: RCU peripherals, refer to rcu_periph_sleep_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_SRAM_SLP: SRAM clock
      \arg        RCU_FMC_SLP: FMC clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_sleep_disable(rcu_periph_sleep_enum periph)
{
    RCU_REG_VAL(periph) &= ~BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      reset the peripherals (API_ID(0x0006U))
    \param[in]  periph_reset: RCU peripherals reset, refer to rcu_periph_reset_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_USBFSRST: reset USBFS
      \arg        RCU_CAURST: reset CAU
      \arg        RCU_HAURST: reset HAU
      \arg        RCU_TRNGRST: reset TRNG
      \arg        RCU_DMAMUXRST: reset DMAMUX
      \arg        RCU_DMAxRST (x = 0,1): reset DMA
      \arg        RCU_TIMERxRST (x = 0,1,2,3,4,5,6,7,16): reset TIMER
      \arg        RCU_WWDGTRST: reset WWDGT
      \arg        RCU_SPIxRST (x = 0,1,2): reset SPI
      \arg        RCU_USARTxRST (x = 0,1,2): reset USART
      \arg        RCU_UARTxRST (x = 3,4): reset UART
      \arg        RCU_I2CxRST (x = 0,1): reset I2C
      \arg        RCU_CMPRST: reset CMP
      \arg        RCU_BKPIRST: reset BKPI
      \arg        RCU_PMURST: reset PMU
      \arg        RCU_DACRST: reset DAC
      \arg        RCU_CTCRST: reset CTC
      \arg        RCU_AFRST : reset alternate function
      \arg        RCU_ADCRST (x = 0,1,2): reset ADC
      \arg        RCU_GPIOxRST (x = A,B,C,D,E): reset GPIO ports
      \arg        RCU_TRIGSELRST: reset TRIGSEL
      \arg        RCU_SYSCFGRST:reset SYSCFG
      \arg        RCU_CANxRST (x = 0,1): reset CAN
    \param[out] none
    \retval     none
*/
void rcu_periph_reset_enable(rcu_periph_reset_enum periph_reset)
{
    RCU_REG_VAL(periph_reset) |= BIT(RCU_BIT_POS(periph_reset));
}

/*!
    \brief      disable reset the peripherals (API_ID(0x0007U))
    \param[in]  periph_reset: RCU peripherals reset, refer to rcu_periph_reset_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_USBFSRST: reset USBFS
      \arg        RCU_CAURST: reset CAU
      \arg        RCU_HAURST: reset HAU
      \arg        RCU_TRNGRST: reset TRNG
      \arg        RCU_DMAMUXRST:reset DMAMUX
      \arg        RCU_DMAxRST (x = 0,1): reset DMA
      \arg        RCU_TIMERxRST (x = 0,1,2,3,4,5,6,7,16): reset TIMER
      \arg        RCU_WWDGTRST: reset WWDGT
      \arg        RCU_SPIxRST (x = 0,1,2): reset SPI
      \arg        RCU_USARTxRST (x = 0,1,2): reset USART
      \arg        RCU_UARTxRST (x = 3,4): reset UART
      \arg        RCU_I2CxRST (x = 0,1): reset I2C
      \arg        RCU_CMPRST: reset CMP
      \arg        RCU_BKPIRST: reset BKPI
      \arg        RCU_PMURST: reset PMU
      \arg        RCU_DACRST: reset DAC
      \arg        RCU_CTCRST: reset CTC
      \arg        RCU_AFRST : reset alternate function
      \arg        RCU_ADCRST (x = 0,1,2): reset ADC
      \arg        RCU_GPIOxRST (x = A,B,C,D,E): reset GPIO ports
      \arg        RCU_TRIGSELRST: reset TRIGSEL
      \arg        RCU_SYSCFGRST:reset SYSCFG
      \arg        RCU_CANxRST (x = 0,1): reset CAN
    \param[out] none
    \retval     none
*/
void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset)
{
    RCU_REG_VAL(periph_reset) &= ~BIT(RCU_BIT_POS(periph_reset));
}

/*!
    \brief      reset the BKP domain (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_bkp_reset_enable(void)
{
    RCU_BDCTL |= RCU_BDCTL_BKPRST;
}

/*!
    \brief      disable the BKP domain reset (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_bkp_reset_disable(void)
{
    RCU_BDCTL &= ~RCU_BDCTL_BKPRST;
}

/*!
    \brief      configure the system clock source (API_ID(0x000AU))
    \param[in]  ck_sys: system clock source select
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKSYSSRC_IRC8M: select CK_IRC8M as the CK_SYS source
      \arg        RCU_CKSYSSRC_HXTAL: select CK_HXTAL as the CK_SYS source
      \arg        RCU_CKSYSSRC_PLL0P: select CK_PLL0P as the CK_SYS source
    \param[out] none
    \retval     none
*/
void rcu_system_clock_source_config(uint32_t ck_sys)
{
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the SCS bits and set according to ck_sys */
    reg &= ~RCU_CFG0_SCS;
    RCU_CFG0 = reg | (ck_sys & RCU_CFG0_SCS);
}

/*!
    \brief      get the system clock source (API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     which clock is selected as CK_SYS source
      \arg        RCU_SCSS_IRC8M: CK_IRC8M is selected as the CK_SYS source
      \arg        RCU_SCSS_HXTAL: CK_HXTAL is selected as the CK_SYS source
      \arg        RCU_SCSS_PLL0P: CK_PLL0P is selected as the CK_SYS source
*/
uint32_t rcu_system_clock_source_get(void)
{
    return (RCU_CFG0 & RCU_CFG0_SCSS);
}

/*!
    \brief      configure the AHB clock prescaler selection (API_ID(0x000CU))
    \param[in]  ck_ahb: AHB clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_AHB_CKSYS_DIVx(x = 1, 2, 4, 8, 16, 64, 128, 256, 512): select CK_SYS / x as CK_AHB
    \param[out] none
    \retval     none
*/
void rcu_ahb_clock_config(uint32_t ck_ahb)
{
    uint32_t reg;

    reg = RCU_CFG0;

    /* reset the AHBPSC bits and set according to ck_ahb */
    reg &= ~RCU_CFG0_AHBPSC;
    RCU_CFG0 = reg | (ck_ahb & RCU_CFG0_AHBPSC);
}

/*!
    \brief      configure the APB1 clock prescaler selection (API_ID(0x000DU))
    \param[in]  ck_apb1: APB1 clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_APB1_CKAHB_DIV1: select CK_AHB as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV2: select CK_AHB / 2 as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV4: select CK_AHB / 4 as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV8: select CK_AHB / 8 as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV16: select CK_AHB / 16 as CK_APB1
    \param[out] none
    \retval     none
*/
void rcu_apb1_clock_config(uint32_t ck_apb1)
{
    uint32_t reg;

    reg = RCU_CFG0;

    /* reset the APB1PSC and set according to ck_apb1 */
    reg &= ~RCU_CFG0_APB1PSC;
    RCU_CFG0 = reg | (ck_apb1 & RCU_CFG0_APB1PSC);
}

/*!
    \brief      configure the APB2 clock prescaler selection (API_ID(0x000EU))
    \param[in]  ck_apb2: APB2 clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_APB2_CKAHB_DIV1: select CK_AHB as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV2: select CK_AHB / 2 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV4: select CK_AHB / 4 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV8: select CK_AHB / 8 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV16: select CK_AHB / 16 as CK_APB2
    \param[out] none
    \retval     none
*/
void rcu_apb2_clock_config(uint32_t ck_apb2)
{
    uint32_t reg;

    reg = RCU_CFG0;

    /* reset the APB2PSC and set according to ck_apb2 */
    reg &= ~RCU_CFG0_APB2PSC;
    RCU_CFG0 = reg | (ck_apb2 & RCU_CFG0_APB2PSC);
}

/*!
    \brief      configure the CK_OUT clock source (API_ID(0x000FU))
    \param[in]  ckout_src: CK_OUT clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKOUTSRC_CKSYS: system clock selected
      \arg        RCU_CKOUTSRC_IRC8M: high speed 8M internal oscillator clock selected
      \arg        RCU_CKOUTSRC_HXTAL: HXTAL selected
      \arg        RCU_CKOUTSRC_CKPLL0_DIV2: CK_PLL0 / 2 selected
      \arg        RCU_CKOUTSRC_CKPLL1_DIV2: CK_PLL1 / 2 selected
      \arg        RCU_CKOUTSRC_LXTAL: LXTAL clock selected
      \arg        RCU_CKOUTSRC_IRC48M: high speed 48M internal oscillator clock selected
      \arg        RCU_CKOUTSRC_IRC40K: IRC40K clock selected
    \param[out] none
    \retval     none
*/
void rcu_ckout_config(uint32_t ckout_src)
{
    uint32_t reg;

    reg = RCU_CFG0;

    /* reset the CKOUTSRC, set according to ckout_src */
    reg &= ~RCU_CFG0_CKOUTSEL;
    RCU_CFG0 = reg | (ckout_src & RCU_CFG0_CKOUTSEL);
}

/*!
    \brief      configure the PLL0 clock (API_ID(0x0010U))
    \param[in]  pll0_src: PLL0 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLL0SRC_IRC8M: IRC8M  clock selected as source clock of PLL0
      \arg        RCU_PLL0SRC_IRC48M: IRC48M selected as source clock of PLL0
      \arg        RCU_PLL0SRC_HXTAL: HXTAL selected as source clock of PLL0
      \arg        RCU_PLL0SRC_CKPLL1: CKPLL1 selected as source clock of PLL0
    \param[in]  pll0_mul: PLL0 clock multiplication factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLL0_MULx (x = 4,5,6..63): PLL0 clock multiplication factor
    \param[in]  pll0_div: PLL0 clock division factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLL0_DIVx (x = 1..16): PLL0 clock division division factor
    \param[out] none
    \retval     none
*/
void rcu_pll0_config(uint32_t pll0_src, uint32_t pll0_mul, uint32_t pll0_div)
{
    uint32_t reg = 0U;

    reg = RCU_CFG1;

    /* PLL0 clock source and multiplication factor configuration */
    reg &= ~RCU_CFG1_PLL0SEL;
    reg |= pll0_src & RCU_CFG1_PLL0SEL;
    RCU_CFG1 = reg;

    reg = RCU_CFG0;
    reg &= ~(RCU_CFG0_PLL0MF_0_3 | RCU_CFG0_PLL0MF_4_5);
    reg |=  pll0_mul & (RCU_CFG0_PLL0MF_0_3 | RCU_CFG0_PLL0MF_4_5);
    RCU_CFG0 = reg;

    reg = RCU_ADDCTL;
    reg &= ~RCU_ADDCTL_PLL0DIV;
    reg |= pll0_div & RCU_ADDCTL_PLL0DIV;
    RCU_ADDCTL = reg ;
}

/*!
    \brief      configure the PLL1 clock (API_ID(0x0011U))
    \param[in]  pll1_src: pll1 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLL1SRC_HXTAL: HXTAL  selected as source clock of PLL1
      \arg        RCU_PPLL1SRC_IRC48M: IRC48M selected as source clock of PLL1
    \param[in]  pll1_mul: PLL1 clock multiplication factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLL1_MULx (x = 4,5,6..63): PLL1 clock multiplication factor
    \param[out] none
    \retval     none
*/
void rcu_pll1_config(uint32_t pll1_src, uint32_t pll1_mul)
{
    uint32_t reg = 0U;

    reg = RCU_CFG1;

    reg &= ~(RCU_CFG1_PLL1MF | RCU_CFG1_PLL1SEL);
    reg |= (pll1_mul & RCU_CFG1_PLL1MF) | (pll1_src & RCU_CFG1_PLL1SEL);
    RCU_CFG1 = reg;
}

/*!
    \brief      configure the PREDIV0 division factor (API_ID(0x0012U))
    \param[in]  prediv0_div: PREDIV0 division factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PREDIV0_DIVx (x = 1..16): PREDIV0 input source clock is divided x
    \param[out] none
    \retval     none
*/
void rcu_prediv0_config(uint32_t prediv0_div)
{
    uint32_t reg = 0U;

    reg = RCU_CFG1;
    /* reset PREDIV0SEL and PREDIV0 bits */
    reg &= ~ RCU_CFG1_PREDIV0;
    /* set the PREDIV0SEL and PREDIV0 division factor */
    reg |=  prediv0_div & RCU_CFG1_PREDIV0;

    RCU_CFG1 = reg;
}

/*!
    \brief      configure the PREDIV1 division factor (API_ID(0x0013U))
    \param[in]  prediv1_div: PREDIV1 division factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PREDIV1_DIVx (x = 1..16): PREDIV1 input source clock is divided x
    \param[out] none
    \retval     none
*/
void rcu_prediv1_config(uint32_t prediv1_div)
{
    uint32_t reg = 0U;

    reg = RCU_CFG1;
    /* reset the PREDIV1 bits */
    reg &= ~RCU_CFG1_PREDIV1;
    /* set the PREDIV1 division factor */
    reg |= prediv1_div & RCU_CFG1_PREDIV1;

    RCU_CFG1 = reg;
}

/*!
    \brief      configure the ADC prescaler factor (API_ID(0x0014U))
    \param[in]  adc_psc: ADC prescaler factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKADC_CKAPB2_DIV2: ADC prescaler select CK_APB2 / 2
      \arg        RCU_CKADC_CKAPB2_DIV4: ADC prescaler select CK_APB2 / 4
      \arg        RCU_CKADC_CKAPB2_DIV6: ADC prescaler select CK_APB2 / 6
      \arg        RCU_CKADC_CKAPB2_DIV8: ADC prescaler select CK_APB2 / 8
      \arg        RCU_CKADC_CKAPB2_DIV12: ADC prescaler select CK_APB2 / 12
      \arg        RCU_CKADC_CKAPB2_DIV16: ADC prescaler select CK_APB2 / 16
      \arg        RCU_CKADC_CKAHB_DIV3: ADC prescaler select CK_AHB / 3
      \arg        RCU_CKADC_CKAHB_DIV5: ADC prescaler select CK_AHB / 5
      \arg        RCU_CKADC_CKAHB_DIV6: ADC prescaler select CK_AHB / 6
      \arg        RCU_CKADC_CKAHB_DIV10: ADC prescaler select CK_AHB / 10
      \arg        RCU_CKADC_CKAHB_DIV20: ADC prescaler select CK_AHB / 20
    \param[out] none
    \retval     none
*/
void rcu_adc_clock_config(uint32_t adc_psc)
{
    uint32_t reg0, reg1;

    /* reset the ADCPSC bits */
    reg0 = RCU_CFG0;
    reg0 &= ~(RCU_CFG0_ADCPSC_2 | RCU_CFG0_ADCPSC);
    reg1 = RCU_CFG1;
    reg1 &= ~RCU_CFG1_ADCPSC_3;

    /* set the ADC prescaler factor */
    switch(adc_psc) {
    case RCU_CKADC_CKAPB2_DIV2:
    case RCU_CKADC_CKAPB2_DIV4:
    case RCU_CKADC_CKAPB2_DIV6:
    case RCU_CKADC_CKAPB2_DIV8:
        reg0 |= ((adc_psc & RCU_ADCPSC_MASK) << RCU_ADC_PSC_OFFSET);
        break;

    case RCU_CKADC_CKAPB2_DIV12:
    case RCU_CKADC_CKAPB2_DIV16:
        adc_psc &= ~BIT(2);
        reg0 |= (((adc_psc & RCU_ADCPSC_MASK) << RCU_ADC_PSC_OFFSET) | RCU_CFG0_ADCPSC_2);
        break;

    case RCU_CKADC_CKAHB_DIV3:
        reg1 |= RCU_CFG1_ADCPSC_3;
        break;

    case RCU_CKADC_CKAHB_DIV5:
    case RCU_CKADC_CKAHB_DIV6:
    case RCU_CKADC_CKAHB_DIV10:
    case RCU_CKADC_CKAHB_DIV20:
        adc_psc &= ~BITS(2, 3);
        reg0 |= ((adc_psc & RCU_ADCPSC_MASK) << RCU_ADC_PSC_OFFSET | RCU_CFG0_ADCPSC_2);
        reg1 |= RCU_CFG1_ADCPSC_3;
        break;
    default:
        break;
    }

    /* set the register */
    RCU_CFG0 = reg0;
    RCU_CFG1 = reg1;
}

/*!
    \brief      configure the USBFS prescaler factor (API_ID(0x0015U))
    \param[in]  usb_psc: USB prescaler factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKUSB_CKPLL0_DIV2: USBFS prescaler select CK_PLL0 / 2
      \arg        RCU_CKUSB_CKPLL0_DIV3: USBFS prescaler select CK_PLL0 / 3
      \arg        RCU_CKUSB_CKPLL0_DIV4: USBFS prescaler select CK_PLL0 / 4
      \arg        RCU_CKUSB_CKPLL0_DIV5: USBFS prescaler select CK_PLL0 / 5
      \arg        RCU_CKUSB_CKPLL0_DIV6: USBFS prescaler select CK_PLL0 / 6
      \arg        RCU_CKUSB_CKPLL0_DIV7: USBFS prescaler select CK_PLL0 / 7
      \arg        RCU_CKUSB_CKPLL0_DIV8: USBFS prescaler select CK_PLL0 / 8
    \param[out] none
    \retval     none
*/
void rcu_usb_clock_config(uint32_t usb_psc)
{
    uint32_t reg;

    reg = RCU_CFG0;
    reg &= ~RCU_CFG0_USBFSPSC;
    reg |= usb_psc & RCU_CFG0_USBFSPSC;

    RCU_CFG0 = reg;
}

/*!
    \brief      configure the RTC clock source selection (API_ID(0x0016U))
    \param[in]  rtc_clock_source: RTC clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_RTCSRC_NONE: no clock selected
      \arg        RCU_RTCSRC_LXTAL: CK_LXTAL selected as RTC source clock
      \arg        RCU_RTCSRC_IRC40K: CK_IRC40K selected as RTC source clock
      \arg        RCU_RTCSRC_HXTAL_DIV_128: CK_HXTAL / 128 selected as RTC source clock
    \param[out] none
    \retval     none
*/
void rcu_rtc_clock_config(uint32_t rtc_clock_source)
{
    uint32_t reg;

    reg = RCU_BDCTL;
    /* reset the RTCSRC bits and set according to rtc_clock_source */
    reg &= ~RCU_BDCTL_RTCSRC;
    reg |= rtc_clock_source & RCU_BDCTL_RTCSRC;
    RCU_BDCTL = reg;
}


/*!
    \brief      configure the I2S1 clock source selection (API_ID(0x0017U))
    \param[in]  i2s_clock_source: I2S1 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_I2S1SRC_CKSYS: System clock selected as I2S1 source clock
      \arg        RCU_I2S1SRC_CKPLL1: CK_PLL1 selected as I2S1 source clock
    \param[in]  i2s_clock_div: i2s clock division factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_I2S1_DIVx: (x = 1...32)
    \param[out] none
    \retval     none
*/
void rcu_i2s1_clock_config(uint32_t i2s_clock_source, uint32_t i2s_clock_div)
{
    uint32_t reg;

    reg = RCU_CFG1;
    /* reset the I2S1SEL bit and set according to i2s_clock_source */
    reg &= ~RCU_CFG1_I2S1SEL;
    reg |= i2s_clock_source & RCU_CFG1_I2S1SEL;
    RCU_CFG1 = reg;

    /* reset the I2S1DIV bit and set according to i2s_clock_div */
    reg = RCU_ADDCTL;
    reg &= ~RCU_ADDCTL_I2S1DIV;
    reg |= i2s_clock_div & RCU_ADDCTL_I2S1DIV;
    RCU_ADDCTL = reg;
}

/*!
    \brief      configure the I2S2 clock source selection (API_ID(0x0018U))
    \param[in]  i2s_clock_source: I2S2 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_I2S2SRC_CKSYS: system clock selected as I2S2 source clock
      \arg        RCU_I2S2SRC_CKPLL1: CK_PLL1 selected as I2S1 source clock
    \param[in]  i2s_clock_div: i2s clock division factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_I2S2_DIVx: (x = 1...32)
    \param[out] none
    \retval     none
*/
void rcu_i2s2_clock_config(uint32_t i2s_clock_source, uint32_t i2s_clock_div)
{
    uint32_t reg;

    reg = RCU_CFG1;
    /* reset the I2S2SEL bit and set according to i2s_clock_source */
    reg &= ~RCU_CFG1_I2S2SEL;
    reg |= i2s_clock_source & RCU_CFG1_I2S2SEL;
    RCU_CFG1 = reg;

    /* reset the I2S2DIV bit and set according to i2s_clock_div */
    reg = RCU_ADDCTL;
    reg &= ~(RCU_ADDCTL_I2S2DIV);
    reg |= i2s_clock_div & RCU_ADDCTL_I2S2DIV;
    RCU_ADDCTL = reg;
}

/*!
    \brief      configure the CK48M clock source selection (API_ID(0x0019U))
    \param[in]  ck48m_clock_source: CK48M clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CK48MSRC_CKPLL0: CK_PLL0 selected as CK48M source clock
      \arg        RCU_CK48MSRC_IRC48M: CK_IRC48M selected as CK48M source clock
    \param[out] none
    \retval     none
*/
void rcu_ck48m_clock_config(uint32_t ck48m_clock_source)
{
    uint32_t reg;

    reg = RCU_ADDCTL;
    /* reset the CK48MSEL bit and set according to ck48m_clock_source */
    reg &= ~RCU_ADDCTL_CK48MSEL;
    reg |= ck48m_clock_source & RCU_ADDCTL_CK48MSEL;
    RCU_ADDCTL = reg;
}

/*!
    \brief      configure the FMC clock source selection (API_ID(0x001AU))
    \param[in]  fmc_clock_source: FMC clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_FMC_CK_AHB: CK_AHB clock selected as FMC source clock
      \arg        RCU_FMC_CK_SYS: system clock selected as FMC source clock
      \arg        RCU_FMC_CK_PLL0: CK_PLL0 clock selected as FMC source clock
      \arg        RCU_FMC_CK_PLL1: CK_PLL1 clock selected as FMC source clock
    \param[in]  fmc_clock_div: FMC clock division factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_FMC_DIVx: (x = 1...16)
    \param[out] none
    \retval     none
*/
void rcu_fmc_clock_config(uint32_t fmc_clock_source, uint32_t fmc_clock_div)
{
    uint32_t reg;

    reg = RCU_ADDCTL;
    /* reset the FMC bit and set according to fmc_clock_source */
    reg &= ~(RCU_ADDCTL_FMCSEL | RCU_ADDCTL_FMCDIV);
    reg |= (fmc_clock_source & RCU_ADDCTL_FMCSEL) | (fmc_clock_div & RCU_ADDCTL_FMCDIV);
    RCU_ADDCTL = reg;
}

/*!
    \brief      configure the LXTAL drive capability (API_ID(0x001BU))
    \param[in]  lxtal_dricap: drive capability of LXTAL
                only one parameter can be selected which is shown as below:
      \arg        RCU_LXTAL_LOWDRI: lower driving capability
      \arg        RCU_LXTAL_MED_LOWDRI: medium low driving capability
      \arg        RCU_LXTAL_MED_HIGHDRI: medium high driving capability
      \arg        RCU_LXTAL_HIGHDRI: higher driving capability
    \param[out] none
    \retval     none
*/
void rcu_lxtal_drive_capability_config(uint32_t lxtal_dricap)
{
    uint32_t reg;

    reg = RCU_BDCTL;

    /* reset the LXTALDRI bits and set according to lxtal_dricap */
    reg &= ~RCU_BDCTL_LXTALDRI;
    reg |= lxtal_dricap & RCU_BDCTL_LXTALDRI;
    RCU_BDCTL = reg;
}

/*!
    \brief      wait for oscillator stabilization flags is SET or oscillator startup is timeout (API_ID(0x001CU))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
      \arg        RCU_IRC8M: internal 8M RC oscillators(IRC8M)
      \arg        RCU_IRC48M: internal 48M RC oscillators(IRC48M)
      \arg        RCU_IRC40K: internal 40K RC oscillator(IRC40K)
      \arg        RCU_PLL0_CK: phase locked loop 0
      \arg        RCU_PLL1_CK: phase locked loop 1
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
ErrStatus rcu_osci_stab_wait(rcu_osci_type_enum osci)
{
    uint32_t stb_cnt = 0U;
    ErrStatus reval = ERROR;
    FlagStatus osci_stat = RESET;

    switch(osci) {
    /* wait HXTAL stable */
    case RCU_HXTAL:
        while((RESET == osci_stat) && (HXTAL_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_HXTALSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_HXTALSTB)) {
            reval = SUCCESS;
        }
        break;

    /* wait LXTAL stable */
    case RCU_LXTAL:
        while((RESET == osci_stat) && (LXTAL_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_LXTALSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_LXTALSTB)) {
            reval = SUCCESS;
        }
        break;

    /* wait IRC8M stable */
    case RCU_IRC8M:
        while((RESET == osci_stat) && (IRC8M_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_IRC8MSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_IRC8MSTB)) {
            reval = SUCCESS;
        }
        break;

    /* wait IRC48M stable */
    case RCU_IRC48M:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_IRC48MSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_IRC48MSTB)) {
            reval = SUCCESS;
        }
        break;

    /* wait IRC40K stable */
    case RCU_IRC40K:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_IRC40KSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_IRC40KSTB)) {
            reval = SUCCESS;
        }
        break;

    /* wait PLL0 stable */
    case RCU_PLL0_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_PLL0STB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_PLL0STB)) {
            reval = SUCCESS;
        }
        break;

    /* wait PLL1 stable */
    case RCU_PLL1_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_PLL1STB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_PLL1STB)) {
            reval = SUCCESS;
        }
        break;

    default:
        break;
    }

    /* return value */
    return reval;
}

/*!
    \brief      turn on the oscillator (API_ID(0x001DU))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
      \arg        RCU_IRC8M: internal 8M RC oscillators(IRC8M)
      \arg        RCU_IRC48M: internal 48M RC oscillators(IRC48M)
      \arg        RCU_IRC40K: internal 40K RC oscillator(IRC40K)
      \arg        RCU_PLL0_CK: phase locked loop 0(PLL0)
      \arg        RCU_PLL1_CK: phase locked loop 1(PLL1)
    \param[out] none
    \retval     none
*/
void rcu_osci_on(rcu_osci_type_enum osci)
{
    RCU_REG_VAL(osci) |= BIT(RCU_BIT_POS(osci));
}

/*!
    \brief      turn off the oscillator (API_ID(0x001EU))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
      \arg        RCU_IRC16M: internal 8M RC oscillators(IRC8M)
      \arg        RCU_IRC48M: internal 48M RC oscillators(IRC48M)
      \arg        RCU_IRC40K: internal 40K RC oscillator(IRC40K)
      \arg        RCU_PLL0_CK: phase locked loop 0(PLL0)
      \arg        RCU_PLL1_CK: phase locked loop 1(PLL1)
    \param[out] none
    \retval     none
*/
void rcu_osci_off(rcu_osci_type_enum osci)
{
    RCU_REG_VAL(osci) &= ~BIT(RCU_BIT_POS(osci));
}

/*!
    \brief      enable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it (API_ID(0x001FU))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
    \param[out] none
    \retval     none
*/
void rcu_osci_bypass_mode_enable(rcu_osci_type_enum osci)
{
    uint32_t reg;

    switch(osci) {
    /* enable HXTAL to bypass mode */
    case RCU_HXTAL:
        reg = RCU_CTL;
        RCU_CTL &= ~RCU_CTL_HXTALEN;
        RCU_CTL = (reg | RCU_CTL_HXTALBPS);
        break;
    /* enable LXTAL to bypass mode */
    case RCU_LXTAL:
        reg = RCU_BDCTL;
        RCU_BDCTL &= ~RCU_BDCTL_LXTALEN;
        RCU_BDCTL = (reg | RCU_BDCTL_LXTALBPS);
        break;
    default:
        break;
    }
}

/*!
    \brief      disable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it (API_ID(0x0020U))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
    \param[out] none
    \retval     none
*/
void rcu_osci_bypass_mode_disable(rcu_osci_type_enum osci)
{
    uint32_t reg;

    switch(osci) {
    /* disable HXTAL to bypass mode */
    case RCU_HXTAL:
        reg = RCU_CTL;
        RCU_CTL &= ~RCU_CTL_HXTALEN;
        RCU_CTL = (reg & ~RCU_CTL_HXTALBPS);
        break;
    /* disable LXTAL to bypass mode */
    case RCU_LXTAL:
        reg = RCU_BDCTL;
        RCU_BDCTL &= ~RCU_BDCTL_LXTALEN;
        RCU_BDCTL = (reg & ~RCU_BDCTL_LXTALBPS);
        break;
    default:
        break;
    }
}

/*!
    \brief      set the IRC8M adjust value (API_ID(0x0021U))
    \param[in]  irc8m_adjval: IRC8M adjust value, must be between 0 and 0x1F
      \arg        0x00 - 0x1F
    \param[out] none
    \retval     none
*/
void rcu_irc8m_adjust_value_set(uint32_t irc8m_adjval)
{
    uint32_t reg;

    reg = RCU_CTL;
    /* reset the IRC8MADJ bits and set according to irc8m_adjval */
    reg &= ~RCU_CTL_IRC8MADJ;
    RCU_CTL = (reg | ((irc8m_adjval & RCU_IRC8M_ADJUST_MASK) << RCU_IRC8M_ADJUST_OFFSET));
}

/*!
    \brief      enable the HXTAL clock monitor (API_ID(0x0022U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_hxtal_clock_monitor_enable(void)
{
    RCU_CTL |= RCU_CTL_HCKMEN;
}

/*!
    \brief      disable the HXTAL clock monitor (API_ID(0x0023U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_hxtal_clock_monitor_disable(void)
{
    RCU_CTL &= ~RCU_CTL_HCKMEN;
}

/*!
    \brief      enable the LXTAL clock monitor (API_ID(0x0024U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_lxtal_clock_monitor_enable(void)
{
    RCU_BDCTL |= RCU_BDCTL_LCKMEN;
}

/*!
    \brief      disable the LXTAL clock monitor (API_ID(0x0025U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_lxtal_clock_monitor_disable(void)
{
    RCU_BDCTL &= ~RCU_BDCTL_LCKMEN;
}

/*!
    \brief      enable the clock frequency monitor (API_ID(0x0026U))
    \param[in]  ckfm: clock frequency monitor enable types, refer to rcu_ckfm_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_IRC8MCKFM: IRC8M clock frequency monitor
      \arg        RCU_HXTALCKFM: HXTAL clock frequency monitor
      \arg        RCU_PLL0PCKFM: PLL0P clock frequency monitor
      \arg        RCU_PLL1CKFM: PLL1 clock frequency monitor
    \param[out] none
    \retval     none
*/
void rcu_clock_freq_monitor_enable(rcu_ckfm_enum ckfm)
{
    RCU_REG_VAL(ckfm) |= BIT(RCU_BIT_POS(ckfm));
}

/*!
    \brief      disable the clock frequency monitor (API_ID(0x0027U))
    \param[in]  ckfm: clock frequency monitor enable types, refer to rcu_ckfm_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_IRC8MCKFM: IRC8M clock frequency monitor
      \arg        RCU_HXTALCKFM: HXTAL clock frequency monitor
      \arg        RCU_PLL0PCKFM: PLL0P clock frequency monitor
      \arg        RCU_PLL1CKFM: PLL1 clock frequency monitor
    \param[out] none
    \retval     none
*/
void rcu_clock_freq_monitor_disable(rcu_ckfm_enum ckfm)
{
    RCU_REG_VAL(ckfm) &= ~BIT(RCU_BIT_POS(ckfm));
}

/*!
    \brief      IRC8M clock frequency monitor range configuration (API_ID(0x0028U))
    \param[in]  range: IRC8M clock frequency monitor configuration
                only one parameter can be selected which is shown as below:
      \arg        RCU_IRC8MCKFMC_5_PERCENT: the IRC8M clock frequency monitoring range is ±5%
      \arg        RCU_IRC8MCKFMC_10_PERCENT: the IRC8M clock frequency monitoring range is ±10%
      \arg        RCU_IRC8MCKFMC_15_PERCENT: the IRC8M clock frequency monitoring range is ±15%
      \arg        RCU_IRC8MCKFMC_20_PERCENT: the IRC8M clock frequency monitoring range is ±20%
    \param[out] none
    \retval     none
*/
void rcu_irc8m_freq_monitor_config(uint32_t range)
{
    uint32_t reg;

    reg = RCU_CKFMCFG0;
    reg &= ~RCU_CKFMCFG0_IRC8MCKFMC;
    RCU_CKFMCFG0 = reg | (range & RCU_CKFMCFG0_IRC8MCKFMC);
}

/*!
    \brief      HXTAL clock frequency monitor threshold configuration (API_ID(0x0029U))
    \param[in]  lthreshold: low frequency threshold configuration
      \arg        0x00 - 0xfff
    \param[in]  hthreshold: high frequency threshold configuration
      \arg        0x00 - 0xfff
    \param[out] none
    \retval     none
*/
void rcu_hxtal_monitor_threshold_config(uint32_t lthreshold, uint32_t hthreshold)
{
    uint32_t reg;

    reg = RCU_CKFMCFG1;
    reg &= ~(RCU_CKFMCFG1_HXTALCKFMIN | RCU_CKFMCFG1_HXTALCKFMAX);
    RCU_CKFMCFG1 = reg | ((lthreshold << 13U) & RCU_CKFMCFG1_HXTALCKFMIN) | ((hthreshold << 1U) & RCU_CKFMCFG1_HXTALCKFMAX);
}

/*!
    \brief      PLL0P clock frequency monitor threshold configuration (API_ID(0x002AU))
    \param[in]  lthreshold: low frequency threshold configuration
      \arg        0x00 - 0x3ff
    \param[in]  hthreshold: high frequency threshold configuration
      \arg        0x00 - 0x3ff
    \param[out] none
    \retval     none
*/
void rcu_pll0p_monitor_threshold_config(uint32_t lthreshold, uint32_t hthreshold)
{
    uint32_t reg;

    reg = RCU_CKFMCFG2;
    reg &= ~(RCU_CKFMCFG2_PLL0PCKFMIN | RCU_CKFMCFG2_PLL0PCKFMAX);
    RCU_CKFMCFG2 = reg | ((lthreshold << 12U) & RCU_CKFMCFG2_PLL0PCKFMIN) | ((hthreshold << 1U) & RCU_CKFMCFG2_PLL0PCKFMAX);
}

/*!
    \brief      PLL1 clock frequency monitor threshold configuration (API_ID(0x002BU))
    \param[in]  lthreshold: low frequency threshold configuration
      \arg        0x00 - 0x3ff
    \param[in]  hthreshold: high frequency threshold configuration
      \arg        0x00 - 0x3ff
    \param[out] none
    \retval     none
*/
void rcu_pll1_monitor_threshold_config(uint32_t lthreshold, uint32_t hthreshold)
{
    uint32_t reg;

    reg = RCU_CKFMCFG3;
    reg &= ~(RCU_CKFMCFG3_PLL1CKFMIN | RCU_CKFMCFG3_PLL1CKFMAX);
    RCU_CKFMCFG3 = reg | ((lthreshold << 12U) & RCU_CKFMCFG2_PLL0PCKFMIN) | ((hthreshold << 1U) & RCU_CKFMCFG2_PLL0PCKFMAX);
}

/*!
    \brief      set the deep sleep mode voltage (API_ID(0x002CU))
    \param[in]  dsvol: deep sleep mode voltage
                only one parameter can be selected which is shown as below:
      \arg        RCU_DEEPSLEEP_V_0: the core voltage is default value
      \arg        RCU_DEEPSLEEP_V_1: the core voltage is (default value-0.05)V
      \arg        RCU_DEEPSLEEP_V_2: the core voltage is (default value-0.1)V
      \arg        RCU_DEEPSLEEP_V_3: the core voltage is (default value-0.15)V
      \arg        RCU_DEEPSLEEP_V_4: the core voltage is (default value-0.2)V
      \arg        RCU_DEEPSLEEP_V_5: the core voltage is (default value-0.25)V
      \arg        RCU_DEEPSLEEP_V_6: the core voltage is (default value-0.3)V(customers are not recommended to use it)
      \arg        RCU_DEEPSLEEP_V_7: the core voltage is (default value-0.35)V(customers are not recommended to use it)
    \param[out] none
    \retval     none
*/
void rcu_deepsleep_voltage_set(uint32_t dsvol)
{
    dsvol &= RCU_DSV_DSLPVS;
    RCU_DSV |= dsvol & RCU_DSV_DSLPVS;
}

/*!
    \brief      delay before switch to IRC8M clock and enter deep-sleep mode (API_ID(0x002DU))
    \param[in]  irc8m_cnt: 1 ~ 31
    \param[out] none
    \retval     none
*/
void rcu_deepsleep_switch_delay_set(uint32_t irc8m_cnt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_RCU_SWITCH_DELAY(irc8m_cnt)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002DU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        RCU_DSV &= ~RCU_DSV_SWDLY;
        RCU_DSV |= RCU_SWDLY_COUNT(irc8m_cnt);
    }
}

/*!
    \brief      lock rcu register (API_ID(0x002EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_reg_lock(void)
{
    RCU_LOCK |= RCU_LOCK_LOCK;
}


/*!
    \brief      unlock rcu register (API_ID(0x002FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_reg_unlock(void)
{
    RCU_LOCK &= ~RCU_LOCK_LOCK;
}

/*!
    \brief      config PLL0/PLL1 bandwidth (API_ID(0x0030U))
    \param[in]  pll0_bw: pll0 bandwidth configuration, must be between 0 and 0xF
      \arg        0 ~ 15
    \param[in]  pll1_bw: pll1 bandwidth configuration, must be between 0 and 0xF
      \arg        0 ~ 15
    \param[out] none
    \retval     none
*/
void rcu_pll_bandwidth_config(uint32_t pll0_bw, uint32_t pll1_bw)
{
    uint32_t reg;

    reg = RCU_PLLBWCFG;
    /* reset the PLL0_BW_CFG/PLL1_BW_CFG bits and set according to pll0_bw/pll1_bw */
    reg &= ~(RCU_PLLBWCFG_PLL0_BW_CFG | RCU_PLLBWCFG_PLL1_BW_CFG);
    RCU_PLLBWCFG = (reg | PLL0_BW_CFG(pll0_bw) | PLL1_BW_CFG(pll1_bw));
}

/*!
    \brief      get the system clock, bus and peripheral clock frequency (API_ID(0x0031U))
    \param[in]  clock: the clock frequency which to get
                only one parameter can be selected which is shown as below:
      \arg        CK_SYS: system clock frequency
      \arg        CK_AHB: AHB clock frequency
      \arg        CK_APB1: APB1 clock frequency
      \arg        CK_APB2: APB2 clock frequency
      \arg        CK_PLL0: PLL0 clock frequency
    \param[out] none
    \retval     clock frequency of system, AHB, APB1, APB2
*/
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock)
{
    uint32_t sws, ck_freq = 0U;
    uint32_t cksys_freq, ahb_freq, apb1_freq, apb2_freq, pll0_freq;
    uint32_t pll0sel, pll1sel, prediv0, pll0mf, prediv1, pll1mf, ck_src, idx, clk_exp;

    /* exponent of AHB, APB1 and APB2 clock divider */
    uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
    uint8_t apb1_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    uint8_t apb2_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};

    sws = GET_BITS(RCU_CFG0, 2, 3);
    switch(sws) {
    /* IRC8M is selected as CK_SYS */
    case SEL_IRC8M:
        cksys_freq = IRC8M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        cksys_freq = HXTAL_VALUE;
        break;
    /* PLL0P is selected as CK_SYS */
    case SEL_PLL0P:
        /* PLL0 clock source selection, IRC8M, IRC48M, HXTAL, or PLL1*/
        pll0sel = (RCU_CFG1 & RCU_CFG1_PLL0SEL);

        if(RCU_PLL0SRC_IRC8M == pll0sel) {
            /* PLL0 clock source is IRC8M*/
            ck_src = IRC8M_VALUE;
        } else if(RCU_PLL0SRC_IRC48M == pll0sel) {
            /* PLL0 clock source is IRC48M*/
            ck_src = IRC48M_VALUE;
        } else if(RCU_PLL0SRC_HXTAL == pll0sel) {
            /* PLL0 clock source is HXTAL*/
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLL0SRC_CKPLL1 == pll0sel) {
            /* PLL1 clock source is HXTAL or IRC48M */
            pll1sel = (RCU_CFG1 & RCU_CFG1_PLL1SEL);

            if(RCU_PLL1SRC_HXTAL == pll1sel) {
                /* PLL1 clock source is HXTAL */
                ck_src = HXTAL_VALUE;
            } else {
                /* PLL1 clock source is IRC48 */
                ck_src = IRC48M_VALUE;
            }

            prediv1 = ((RCU_CFG1 & RCU_CFG1_PREDIV1) >> RCU_CFG1_PREDIV1_OFFSET) + 1U;
            /* PLL1 multiplication factor */
            pll1mf = (uint32_t)((RCU_CFG1 & RCU_CFG1_PLL1MF) >> RCU_CFG1_PLL1MF_OFFSET);
            ck_src = (ck_src / prediv1) * pll1mf;
        } else {
        }

        /* PLL0 multiplication factor */
        prediv0 = ((RCU_CFG1 & RCU_CFG1_PREDIV0) >> RCU_CFG1_PREDIV0_OFFSET) + 1U;
        /* PLL0 multiplication factor */
        pll0mf = GET_BITS(RCU_CFG0, 18, 21);
        pll0mf |= GET_BITS(RCU_CFG0, 29, 30) << 4U;

        cksys_freq = ck_src * pll0mf / prediv0;
        break;
    default:
        break;
    }

    /* calculate AHB clock frequency */
    idx = GET_BITS(RCU_CFG0, 4, 7);
    clk_exp = ahb_exp[idx];
    ahb_freq = cksys_freq >> clk_exp;

    /* calculate APB1 clock frequency */
    idx = GET_BITS(RCU_CFG0, 8, 10);
    clk_exp = apb1_exp[idx];
    apb1_freq = ahb_freq >> clk_exp;

    /* calculate APB2 clock frequency */
    idx = GET_BITS(RCU_CFG0, 11, 13);
    clk_exp = apb2_exp[idx];
    apb2_freq = ahb_freq >> clk_exp;

    /* return the clocks frequency */
    switch(clock) {
    case CK_SYS:
        ck_freq = cksys_freq;
        break;
    case CK_AHB:
        ck_freq = ahb_freq;
        break;
    case CK_APB1:
        ck_freq = apb1_freq;
        break;
    case CK_APB2:
        ck_freq = apb2_freq;
        break;
    case CK_PLL0:
        /* PLL0 clock source selection, IRC8M, IRC48M, HXTAL, or PLL1*/
        pll0sel = (RCU_CFG1 & RCU_CFG1_PLL0SEL);

        if(RCU_PLL0SRC_IRC8M == pll0sel) {
            /* PLL0 clock source is IRC8M*/
            ck_src = IRC8M_VALUE;
        } else if(RCU_PLL0SRC_IRC48M == pll0sel) {
            /* PLL0 clock source is IRC48M*/
            ck_src = IRC48M_VALUE;
        } else if(RCU_PLL0SRC_HXTAL == pll0sel) {
            /* PLL0 clock source is HXTAL*/
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLL0SRC_CKPLL1 == pll0sel) {
            /* PLL1 clock source is HXTAL or IRC48M */
            pll1sel = (RCU_CFG1 & RCU_CFG1_PLL1SEL);

            if(RCU_PLL1SRC_HXTAL == pll1sel) {
                /* PLL1 clock source is HXTAL */
                ck_src = HXTAL_VALUE;
            } else {
                /* PLL1 clock source is IRC48 */
                ck_src = IRC48M_VALUE;
            }

            prediv1 = ((RCU_CFG1 & RCU_CFG1_PREDIV1) >> RCU_CFG1_PREDIV1_OFFSET) + 1U;
            /* PLL1 multiplication factor */
            pll1mf = (uint32_t)((RCU_CFG1 & RCU_CFG1_PLL1MF) >> RCU_CFG1_PLL1MF_OFFSET);
            ck_src = (ck_src / prediv1) * pll1mf;
        } else {
        }

        /* PLL0 multiplication factor */
        pll0mf = GET_BITS(RCU_CFG0, 18, 21);
        pll0mf |= GET_BITS(RCU_CFG0, 29, 30) << 4U;

        pll0_freq = ck_src * pll0mf;
        ck_freq = pll0_freq;
        break;
    default:
        break;
    }
    return ck_freq;
}

/*!
    \brief      get the clock stabilization, peripheral reset and clock frequency failure flags (API_ID(0x0032U))
    \param[in]  flag: the clock stabilization and peripheral reset flags, refer to rcu_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_IRC8MSTB: IRC8M stabilization flag
      \arg        RCU_FLAG_HXTALSTB: HXTAL stabilization flag
      \arg        RCU_FLAG_PLL0STB: PLL0 stabilization flag
      \arg        RCU_FLAG_PLL1STB: PLL1 stabilization flag(CL series only)
      \arg        RCU_FLAG_LXTALSTB: LXTAL stabilization flag
      \arg        RCU_FLAG_IRC40KSTB: IRC40K stabilization flag
      \arg        RCU_FLAG_IRC48MSTB: IRC48M stabilization flag
      \arg        RCU_FLAG_EPRST: external PIN reset flag
      \arg        RCU_FLAG_PORRST: power reset flag
      \arg        RCU_FLAG_SWRST: software reset flag
      \arg        RCU_FLAG_FWDGTRST: free watchdog timer reset flag
      \arg        RCU_FLAG_WWDGTRST: window watchdog timer reset flag
      \arg        RCU_FLAG_LPRST: low-power reset flag
      \arg        RCU_FLAG_IRC8MCKFF: IRC8M clock frequency failure flag
      \arg        RCU_FLAG_HXTALCKFF: HXTAL clock frequency failure flag
      \arg        RCU_FLAG_PLL0PCKFF: PLL0P clock frequency failure flag
      \arg        RCU_FLAG_PLL1CKFF: PLL1 clock frequency failure flag
    \param[out] none
    \retval     FlagStatus: status of flag (RESET or SET)
*/
FlagStatus rcu_flag_get(rcu_flag_enum flag)
{
    FlagStatus reval;
    /* get the rcu flag */
    if(RESET != (RCU_REG_VAL(flag) & BIT(RCU_BIT_POS(flag)))) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear clock frequency failure flags (API_ID(0x0033U))
    \param[in]  flag: clock frequency failure flag, refer to rcu_flag_clear_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_IRC8MCKFF_CLR: IRC8M clock frequency failure interrupt flag clear
      \arg        RCU_FLAG_HXTALCKFF_CLR: HXTAL clock frequency failure interrupt flag clear
      \arg        RCU_FLAG_PLL0PCKFF_CLR: PLL0P clock frequency failure interrupt flag clear
      \arg        RCU_FLAG_PLL1CKFF_CLR: PLL1 clock frequency failure interrupt flag clear
    \param[out] none
    \retval     none
*/
void rcu_flag_clear(rcu_flag_clear_enum flag)
{
    RCU_REG_VAL(flag) |= BIT(RCU_BIT_POS(flag));
}

/*!
    \brief      clear all the reset flag (API_ID(0x0034U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_all_reset_flag_clear(void)
{
    RCU_RSTSCK |= RCU_RSTSCK_RSTFC;
}

/*!
    \brief      enable the clock interrupt (API_ID(0x0035U))
    \param[in]  interrupt clock stabilization interrupt, refer to rcu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_IRC40KSTB: IRC40K stabilization interrupt enable
      \arg        RCU_INT_LXTALSTB: LXTAL stabilization interrupt enable
      \arg        RCU_INT_IRC8MSTB: IRC8M stabilization interrupt enable
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt enable
      \arg        RCU_INT_PLL0STB: PLL0 stabilization interrupt enable
      \arg        RCU_INT_PLL1STB: PLL1 stabilization interrupt enable
      \arg        RCU_INT_LCKM: LXTAL clock stuck interrupt enable
      \arg        RCU_INT_IRC48MSTB: IRC48M stabilization interrupt enable
      \arg        RCU_INT_IRC8MCKFF: IRC8M clock frequency failure interrupt enable
      \arg        RCU_INT_HXTALCKFF: HXTAL clock frequency failure interrupt enable
      \arg        RCU_INT_PLL0PCKFF: PLL0P clock frequency failure interrupt enable
      \arg        RCU_INT_PLL1CKFF: PLL1 clock frequency failure interrupt enable
    \param[out] none
    \retval     none
*/
void rcu_interrupt_enable(rcu_int_enum interrupt)
{
    RCU_REG_VAL(interrupt) |= BIT(RCU_BIT_POS(interrupt));
}

/*!
    \brief      disable the clock interrupt (API_ID(0x0036U))
    \param[in]  interrupt clock stabilization interrupt, refer to rcu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_IRC40KSTB: IRC40K stabilization interrupt disable
      \arg        RCU_INT_LXTALSTB: LXTAL stabilization interrupt disable
      \arg        RCU_INT_IRC8MSTB: IRC8M stabilization interrupt disable
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt disable
      \arg        RCU_INT_PLL0STB: PLL0 stabilization interrupt disable
      \arg        RCU_INT_PLL1STB: PLL1 stabilization interrupt disable
      \arg        RCU_INT_LCKM: LXTAL clock stuck interrupt enable
      \arg        RCU_INT_IRC48MSTB: IRC48M stabilization interrupt disable
      \arg        RCU_INT_IRC8MCKFF: IRC8M clock frequency failure interrupt disable
      \arg        RCU_INT_HXTALCKFF: HXTAL clock frequency failure interrupt disable
      \arg        RCU_INT_PLL0PCKFF: PLL0P clock frequency failure interrupt disable
      \arg        RCU_INT_PLL1CKFF: PLL1 clock frequency failure interrupt disable
    \param[out] none
    \retval     none
*/
void rcu_interrupt_disable(rcu_int_enum interrupt)
{
    RCU_REG_VAL(interrupt) &= ~BIT(RCU_BIT_POS(interrupt));
}

/*!
    \brief      get the clock interrupt flags (API_ID(0x0037U))
    \param[in]  int_flag: interrupt and clock stuck flags, refer to rcu_int_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_IRC40KSTB: IRC40K stabilization interrupt flag
      \arg        RCU_INT_FLAG_LXTALSTB: LXTAL stabilization interrupt flag
      \arg        RCU_INT_FLAG_IRC8MSTB: IRC8M stabilization interrupt flag
      \arg        RCU_INT_FLAG_HXTALSTB: HXTAL stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLL0STB: PLL0 stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLL1STB: PLL1 stabilization interrupt flag
      \arg        RCU_INT_FLAG_HCKM: HXTAL clock stuck interrupt flag
      \arg        RCU_INT_FLAG_LCKM: LXTAL clock stuck interrupt flag
      \arg        RCU_INT_FLAG_IRC48MSTB: IRC48M stabilization interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag)
{
    FlagStatus reval;
    /* get the rcu interrupt flag */
    if(RESET != (RCU_REG_VAL(int_flag) & BIT(RCU_BIT_POS(int_flag)))) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear the clock interrupt flags (API_ID(0x0038U))
    \param[in]  int_flag: clock stabilization and stuck interrupt flags clear, refer to rcu_int_flag_clear_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_IRC40KSTB_CLR: IRC40K stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_LXTALSTB_CLR: LXTAL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_IRC8MSTB_CLR: IRC8M stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_HXTALSTB_CLR: HXTAL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLL0STB_CLR: PLL0 stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLL1STB_CLR: PLL1 stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_HCKM_CLR: HXTAL clock stuck interrupt flag clear
      \arg        RCU_INT_FLAG_LCKM_CLR: LXTAL clock stuck interrupt flag clear
      \arg        RCU_INT_FLAG_IRC48MSTB_CLR: IRC48M stabilization interrupt flag clear
    \param[out] none
    \retval     none
*/
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag)
{
    RCU_REG_VAL(int_flag) |= BIT(RCU_BIT_POS(int_flag));
}
