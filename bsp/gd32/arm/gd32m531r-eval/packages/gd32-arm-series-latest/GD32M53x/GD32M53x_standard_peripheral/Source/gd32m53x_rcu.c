/*!
    \file    gd32m53x_rcu.c
    \brief   RCU driver

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
#include "gd32m53x_rcu.h"

/* define clock source */
#define SEL_IRC32M                  ((uint16_t)0U)  /* IRC32M is selected as CK_SYS */
#define SEL_HXTAL                   ((uint16_t)1U)  /* HXTAL is selected as CK_SYS */
#define SEL_PLL                     ((uint16_t)2U)  /* PLL is selected as CK_SYS */

/* define startup timeout count */
#define OSC_STARTUP_TIMEOUT         ((uint32_t)0x000FFFFFU)
#define LXTAL_STARTUP_TIMEOUT       ((uint32_t)0x03FFFFFFU)

/* RCU IRC32M adjust value mask and offset */
#define RCU_IRC32M_ADJUST_MASK      ((uint8_t)0x1FU)
#define RCU_IRC32M_ADJUST_OFFSET    ((uint32_t)3U)

#define RCU_CKOUTSEL_MASK           ((uint32_t)0x87000000U)
#define RCU_SYSRST_MASK             ((uint32_t)0x00006400U)

/*!
    \brief      deinitialize the RCU (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_deinit(void)
{
    /* enable IRC32M */
    RCU_CTL |= RCU_CTL_IRC32MEN;
    while(0U == (RCU_CTL & RCU_CTL_IRC32MSTB)) {
    }
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_IRC32M) {
    }
    /* reset CTL register */
    RCU_CTL &= ~(RCU_CTL_HXTALEN | RCU_CTL_CKMEN | RCU_CTL_PLLEN | RCU_CTL_HXTALSCAL | RCU_CTL_PLLMEN);
    RCU_CTL &= ~RCU_CTL_HXTALBPS;

    RCU_CFG0 &= ~(RCU_CFG0_SCS | RCU_CFG0_AHBPSC | RCU_CFG0_APB1PSC | RCU_CFG0_APB2PSC |
                  RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF | RCU_CFG0_CKOUTSEL | RCU_CFG0_PLLDV);

    /* reset INT register */
    RCU_INT = 0x00DD0000U;
}

/*!
    \brief      enable the peripherals clock (API_ID(0x0002U))
    \param[in]  periph: RCU peripherals, refer to rcu_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_TMU: TMU clock
      \arg        RCU_SVPWM: SVPWM clock
      \arg        RCU_GTOC: GTOC clock
      \arg        RCU_POC: POC clock
      \arg        RCU_GPIOx (x = A,B,C,D,E,F,G,N): GPIO ports clock
      \arg        RCU_CRC: CRC clock
      \arg        RCU_DMAMUX: DMAMUX clock
      \arg        RCU_DMAx (x = 0,1): DMA clock
      \arg        RCU_CAN: CAN clock
      \arg        RCU_EVIC: EVIC clock
      \arg        RCU_TIMERx (x = 0,1,2,7): TIMER clock
      \arg        RCU_GPTIMERx (x = 0,1): GPTIMER clock
      \arg        RCU_CPTIMERx (x = 0,1,W): CPTIMER clock
      \arg        RCU_SPI: SPI clock
      \arg        RCU_WWDGT: WWDGT clock
      \arg        RCU_UARTx(x =0,1,2,3): UART clock
      \arg        RCU_I2C: I2C clock
      \arg        RCU_SYSCFG: System configuration clock
      \arg        RCU_PMU: PMU clock
      \arg        RCU_CFMU: CFMU clock
      \arg        RCU_DAC: DAC clock
      \arg        RCU_ADCx (x = 0,2): ADC clock
      \arg        RCU_CMP: CMP clock
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
      \arg        RCU_TMU: TMU clock
      \arg        RCU_SVPWM: SVPWM clock
      \arg        RCU_GTOC: GTOC clock
      \arg        RCU_POC: POC clock
      \arg        RCU_GPIOx (x = A,B,C,D,E,F,G,N): GPIO ports clock
      \arg        RCU_CRC: CRC clock
      \arg        RCU_DMAMUX: DMAMUX clock
      \arg        RCU_DMAx (x = 0,1): DMA clock
      \arg        RCU_CAN: CAN clock
      \arg        RCU_EVIC: EVIC clock
      \arg        RCU_TIMERx (x = 0,1,2,7): TIMER clock
      \arg        RCU_GPTIMERx (x = 0,1): GPTIMER clock
      \arg        RCU_CPTIMERx (x = 0,1,W): CPTIMER clock
      \arg        RCU_SPI: SPI clock
      \arg        RCU_WWDGT: WWDGT clock
      \arg        RCU_UARTx(x =0,1,2,3): UART clock
      \arg        RCU_I2C: I2C clock
      \arg        RCU_SYSCFG: System configuration clock
      \arg        RCU_PMU: PMU clock
      \arg        RCU_CFMU: CFMU clock
      \arg        RCU_DAC: DAC clock
      \arg        RCU_ADCx (x = 0,2): ADC clock
      \arg        RCU_CMP: CMP clock
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
      \arg        RCU_FMC_SLP: FMC clock
      \arg        RCU_SRAM_SLP: SRAM clock
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
      \arg        RCU_TMURST: TMU clock
      \arg        RCU_SVPWMRST: SVPWM clock
      \arg        RCU_GTOCRST: GTOC clock
      \arg        RCU_POCRST: POC clock
      \arg        RCU_GPIOxRST (x = A,B,C,D,E,F,G,N): GPIO ports clock
      \arg        RCU_CRCRST: CRC clock
      \arg        RCU_DMAMUXRST: DMAMUX clock
      \arg        RCU_DMAxRST (x = 0,1): DMA clock
      \arg        RCU_CANRST: CAN clock
      \arg        RCU_TIMERxRST (x = 0,1,2,7): TIMER clock
      \arg        RCU_GPTIMERxRST (x = 0,1): GPTIMER clock
      \arg        RCU_CPTIMERxRST (x = 0,1,W): CPTIMER clock
      \arg        RCU_SPIRST: SPI clock
      \arg        RCU_WWDGTRST: WWDGT clock
      \arg        RCU_UARTxRST(x =0,1,2,3): UART clock
      \arg        RCU_I2CRST: I2C clock
      \arg        RCU_SYSCFGRST: System configuration clock
      \arg        RCU_PMURST: PMU clock
      \arg        RCU_CFMURST: CFMU clock
      \arg        RCU_DACRST: DAC clock
      \arg        RCU_ADCxRST (x = 0,2): ADC clock
      \arg        RCU_CMPRST: CMP clock
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
      \arg        RCU_TMURST: TMU clock
      \arg        RCU_SVPWMRST: SVPWM clock
      \arg        RCU_GTOCRST: GTOC clock
      \arg        RCU_POCRST: POC clock
      \arg        RCU_GPIOxRST (x = A,B,C,D,E,F,G,N): GPIO ports clock
      \arg        RCU_CRCRST: CRC clock
      \arg        RCU_DMAMUXRST: DMAMUX clock
      \arg        RCU_DMAxRST (x = 0,1): DMA clock
      \arg        RCU_CANRST: CAN clock
      \arg        RCU_TIMERxRST (x = 0,1,2,7): TIMER clock
      \arg        RCU_GPTIMERxRST (x = 0,1): GPTIMER clock
      \arg        RCU_CPTIMERxRST (x = 0,1,W): CPTIMER clock
      \arg        RCU_SPIRST: SPI clock
      \arg        RCU_WWDGTRST: WWDGT clock
      \arg        RCU_UARTxRST(x =0,1,2,3): UART clock
      \arg        RCU_I2CRST: I2C clock
      \arg        RCU_SYSCFGRST: System configuration clock
      \arg        RCU_PMURST: PMU clock
      \arg        RCU_CFMURST: CFMU clock
      \arg        RCU_DACRST: DAC clock
      \arg        RCU_ADCxRST (x = 0,2): ADC clock
      \arg        RCU_CMPRST: CMP clock
    \param[out] none
    \retval     none
*/
void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset)
{
    RCU_REG_VAL(periph_reset) &= ~BIT(RCU_BIT_POS(periph_reset));
}

/*!
    \brief      configure the system clock source (API_ID(0x0008U))
    \param[in]  ck_sys: system clock source select
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKSYSSRC_IRC32M: select CK_IRC32M as the CK_SYS source
      \arg        RCU_CKSYSSRC_HXTAL: select CK_HXTAL as the CK_SYS source
      \arg        RCU_CKSYSSRC_PLL: select CK_PLL as the CK_SYS source
    \param[out] none
    \retval     none
*/
void rcu_system_clock_source_config(uint32_t ck_sys)
{
    uint32_t reg;
    reg = RCU_CFG0;
    /* reset the SCS bits and set according to ck_sys */
    reg &= ~RCU_CFG0_SCS;
    RCU_CFG0 = (reg | (ck_sys & RCU_CFG0_SCS));
}

/*!
    \brief      get the system clock source (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     which clock is selected as CK_SYS source
      \arg        RCU_SCSS_IRC32M: CK_IRC32M is selected as the CK_SYS source
      \arg        RCU_SCSS_HXTAL: CK_HXTAL is selected as the CK_SYS source
      \arg        RCU_SCSS_PLL: CK_PLL is selected as the CK_SYS source
*/
uint32_t rcu_system_clock_source_get(void)
{
    return (RCU_CFG0 & RCU_CFG0_SCSS);
}

/*!
    \brief      configure the AHB clock prescaler selection (API_ID(0x000AU))
    \param[in]  ck_ahb: AHB clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_AHB_CKSYS_DIVx (x = 1, 2, 4, 8, 16, 64, 128, 256, 512): select CK_SYS / x as CK_AHB
    \param[out] none
    \retval     none
*/
void rcu_ahb_clock_config(uint32_t ck_ahb)
{
    uint32_t reg;
    reg = RCU_CFG0;
    /* reset the AHBPSC bits and set according to ck_ahb */
    reg &= ~RCU_CFG0_AHBPSC;
    RCU_CFG0 = (reg | (ck_ahb & RCU_CFG0_AHBPSC));
}

/*!
    \brief      configure the APB1 clock prescaler selection (API_ID(0x000BU))
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
    RCU_CFG0 = (reg | (ck_apb1 & RCU_CFG0_APB1PSC));
}

/*!
    \brief      configure the APB2 clock prescaler selection (API_ID(0x000CU))
    \param[in]  ck_apb2: APB2 clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_APB2_CKAHB_DIV1: select CK_AHB as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV2: select CK_AHB/2 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV4: select CK_AHB/4 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV8: select CK_AHB/8 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV16: select CK_AHB/16 as CK_APB2
    \param[out] none
    \retval     none
*/
void rcu_apb2_clock_config(uint32_t ck_apb2)
{
    uint32_t reg;
    reg = RCU_CFG0;

    /* reset the APB2PSC and set according to ck_apb2 */
    reg &= ~RCU_CFG0_APB2PSC;
    RCU_CFG0 = (reg | (ck_apb2 & RCU_CFG0_APB2PSC));
}

/*!
    \brief      configure the CK_OUT clock source (API_ID(0x000DU))
    \param[in]  ckout_src: CK_OUT clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKOUTSRC_NONE: no clock selected
      \arg        RCU_CKOUTSRC_IRC32K: IRC32K selected
      \arg        RCU_CKOUTSRC_CKSYS: system clock selected
      \arg        RCU_CKOUTSRC_IRC32M: high speed 32M internal oscillator clock selected
      \arg        RCU_CKOUTSRC_HXTAL: HXTAL selected
      \arg        RCU_CKOUTSRC_CKPLL_DIV1: CK_PLL selected
      \arg        RCU_CKOUTSRC_CKPLL_DIV8: CK_PLL/8 selected
    \param[in]  ckout_div: CK_OUT divider
      \arg        RCU_CKOUT_DIVx(x=1,2,4,8,16,32,64,128): CK_OUT is divided by x
    \param[out] none
    \retval     none
*/
void rcu_ckout_config(uint32_t ckout_src, uint32_t ckout_div)
{
    uint32_t ckout = 0U;
    ckout = RCU_CFG0;
    /* reset the CKOUTSEL, CKOUTDIV and PLLDV bits and set according to ckout_src and ckout_div */
    ckout &= ~(RCU_CFG0_CKOUTSEL | RCU_CFG0_CKOUTDIV | RCU_CFG0_PLLDV);
    RCU_CFG0 = (ckout | (ckout_src & RCU_CKOUTSEL_MASK) | (ckout_div & RCU_CFG0_CKOUTDIV));
}

/*!
    \brief      configure the main PLL clock (API_ID(0x000EU))
    \param[in]  pll_src: PLL clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLLSRC_IRC32M: IRC32M clock selected as source clock of PLL
      \arg        RCU_PLLSRC_HXTAL: HXTAL selected as source clock of PLL
    \param[in]  predv_div: PREDV division factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PREDV_DIVx, x = 1..8
    \param[in]  pll_mul: PLL clock multiplication factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLL_MULx (x= 4,4.5,5,5.5...63.5,64): PLL clock * x
    \param[out] none
    \retval     none
*/
void rcu_pll_config(uint32_t pll_src, uint32_t predv_div, uint32_t pll_mul)
{
    uint32_t reg0 = 0U, reg1 = 0U;
    reg0 = RCU_CFG0;
    /* PLL clock source and multiplication factor configuration */
    reg0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    reg0 |= ((pll_src & RCU_CFG0_PLLSEL) | (pll_mul & RCU_CFG0_PLLMF));
    RCU_CFG0 = reg0;

    reg1 = RCU_CFG1;
    /* PREDV division factor configuration */
    reg1 &= ~RCU_CFG1_PREDV;
    reg1 |= predv_div & RCU_CFG1_PREDV;
    RCU_CFG1 = reg1;
}

/*!
    \brief      enable RCU system reset (API_ID(0x000FU))
    \param[in]  reset_source: reset source
                one or more parameters can be selected which is shown as below:
      \arg        RCU_SYSRST_LOCKUP: CPU lock-up reset
      \arg        RCU_SYSRST_LOH: lost of HXTAL reset
      \arg        RCU_SYSRST_LOP: lost of PLL reset
    \param[out] none
    \retval     none
*/
void rcu_system_reset_enable(uint32_t reset_source)
{
    RCU_RSTSCK |= reset_source & RCU_SYSRST_MASK;
}

/*!
    \brief      disable RCU system reset (API_ID(0x0010U))
    \param[in]  reset_source: reset source
                one or more parameters can be selected which is shown as below:
      \arg        RCU_SYSRST_LOCKUP: CPU lock-up reset
      \arg        RCU_SYSRST_LOH: lost of HXTAL reset
      \arg        RCU_SYSRST_LOP: lost of PLL reset
    \param[out] none
    \retval     none
*/
void rcu_system_reset_disable(uint32_t reset_source)
{
    RCU_RSTSCK &= ~(reset_source & RCU_SYSRST_MASK);
}

/*!
    \brief      configure the CK_ADCPRE clock source and division factor (API_ID(0x0011U))
    \param[in]  ck_adc: ADC clock source select
                only one parameter can be selected which is shown as below:
      \arg        RCU_CK_ADCPRE_PCLK2: select CK_PCLK2 as the CK_ADC source
      \arg        RCU_CK_ADCPRE_HXTAL: select CK_HXTAL as the CK_ADC source
      \arg        RCU_CK_ADCPRE_PLL: select CK_PLL as the CK_ADC source
      \arg        RCU_CK_ADCPRE_IRC32M: select IRC32M as the CK_ADC source
    \param[in]  adc_psc: ADC prescaler factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_CK_ADCPRE_DIVx(x = 2,3...31,32): ADC prescaler select CK_ADCPRE/ x
    \param[out] none
    \retval     none
*/
void rcu_adc_clock_config(uint32_t ck_adc, uint32_t adc_psc)
{
    uint32_t reg;
    /* reset the ADCPSC bits */
    reg = RCU_CFG2;
    reg &= ~(RCU_CFG2_ADCPSC | RCU_CFG2_ADCSEL);
    reg |= ((adc_psc & RCU_CFG2_ADCPSC) | (ck_adc & RCU_CFG2_ADCSEL));
    RCU_CFG2 = reg;
}

/*!
    \brief      configure the CK_I2C clock source (API_ID(0x0012U))
    \param[in]  ck_i2c: i2c clock source select
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKI2CSRC_PCLK1: select CK_PCLK1 as the CK_I2C source
      \arg        RCU_CKI2CSRC_PLL: select CK_PLL as the CK_I2C source
      \arg        RCU_CKI2CSRC_IRC32M: select CK_IRC32M as the CK_I2C source
      \arg        RCU_CKI2CSRC_HXTAL: select CK_HXTAL as the CK_I2C source
    \param[out] none
    \retval     none
*/
void rcu_i2c_clock_source_config(uint32_t ck_i2c)
{
    uint32_t reg;
    reg = RCU_CFG2;
    /* reset the SCS bits and set according to ck_sys */
    reg &= ~RCU_CFG2_I2CSEL;
    RCU_CFG2 = (reg | (ck_i2c & RCU_CFG2_I2CSEL));
}

/*!
    \brief      wait for oscillator stabilization flags is SET or oscillator startup is timeout (API_ID(0x0013U))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_IRC32M: internal 32M RC oscillators(IRC32M)
      \arg        RCU_IRC32K: internal 32K RC oscillator(IRC32K)
      \arg        RCU_PLL_CK: phase locked loop(PLL)
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
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
    /* wait IRC32M stable */
    case RCU_IRC32M:
        while((RESET == osci_stat) && (IRC32M_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_IRC32MSTB);
            stb_cnt++;
        }
        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_IRC32MSTB)) {
            reval = SUCCESS;
        }
        break;
    /* wait IRC32K stable */
    case RCU_IRC32K:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_IRC32KSTB);
            stb_cnt++;
        }
        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_IRC32KSTB)) {
            reval = SUCCESS;
        }
        break;
    /* wait PLL stable */
    case RCU_PLL_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_PLLSTB);
            stb_cnt++;
        }
        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_PLLSTB)) {
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
    \brief      turn on the oscillator (API_ID(0x0014U))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_IRC32M: internal 32M RC oscillators(IRC32M)
      \arg        RCU_IRC32K: internal 32K RC oscillator(IRC32K)
      \arg        RCU_PLL_CK: phase locked loop(PLL)
    \param[out] none
    \retval     none
*/
void rcu_osci_on(rcu_osci_type_enum osci)
{
    RCU_REG_VAL(osci) |= BIT(RCU_BIT_POS(osci));
}

/*!
    \brief      turn off the oscillator (API_ID(0x0015U))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_IRC32M: internal 32M RC oscillators(IRC32M)
      \arg        RCU_IRC32K: internal 32K RC oscillator(IRC32K)
      \arg        RCU_PLL_CK: phase locked loop(PLL)
    \param[out] none
    \retval     none
*/
void rcu_osci_off(rcu_osci_type_enum osci)
{
    RCU_REG_VAL(osci) &= ~BIT(RCU_BIT_POS(osci));
}

/*!
    \brief      enable the oscillator bypass mode, HXTALEN must be reset before it (API_ID(0x0016U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_osci_bypass_mode_enable(void)
{
    uint32_t reg;
    /* enable HXTAL to bypass mode */
    reg = RCU_CTL;
    RCU_CTL &= ~RCU_CTL_HXTALEN;
    RCU_CTL = (reg | RCU_CTL_HXTALBPS);
}

/*!
    \brief      disable the oscillator bypass mode, HXTALEN must be reset before it (API_ID(0x0017U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_osci_bypass_mode_disable(void)
{
    uint32_t reg;
    reg = RCU_CTL;
    RCU_CTL &= ~RCU_CTL_HXTALEN;
    RCU_CTL = (reg & ~RCU_CTL_HXTALBPS);
}

/*!
    \brief      HXTAL frequency scale select (API_ID(0x0018U))
    \param[in]  hxtal_scal: HXTAL frequency scale
                only one parameter can be selected which is shown as below:
      \arg        HXTAL_SCALE_1M_TO_10M: HXTAL scale is 1-10MHz
      \arg        HXTAL_SCALE_10M_TO_24M: HXTAL scale is 10-24MHz
    \param[out] none
    \retval     none
*/
void rcu_hxtal_frequency_scale_select(uint32_t hxtal_scal)
{
    if(HXTAL_SCALE_1M_TO_10M == hxtal_scal) {
        RCU_CTL &= ~RCU_CTL_HXTALSCAL;
    } else {
        RCU_CTL |= RCU_CTL_HXTALSCAL;
    }
}

/*!
    \brief      set the IRC32M adjust value (API_ID(0x0019U))
    \param[in]  irc32m_adjval: IRC32M adjust value, must be between 0 and 0x1F
      \arg        0x00 - 0x1F
    \param[out] none
    \retval     none
*/
void rcu_irc32m_adjust_value_set(uint32_t irc32m_adjval)
{
    uint32_t reg;

    reg = RCU_CTL;
    /* reset the IRC32MADJ bits and set according to irc32m_adjval */
    reg &= ~RCU_CTL_IRC32MADJ;
    RCU_CTL = (reg | ((irc32m_adjval & RCU_IRC32M_ADJUST_MASK) << RCU_IRC32M_ADJUST_OFFSET));

}

/*!
    \brief      enable the HXTAL clock monitor (API_ID(0x001AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_hxtal_clock_monitor_enable(void)
{
    RCU_CTL |= RCU_CTL_CKMEN;
}

/*!
    \brief      disable the HXTAL clock monitor (API_ID(0x001BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_hxtal_clock_monitor_disable(void)
{
    RCU_CTL &= ~RCU_CTL_CKMEN;
}

/*!
    \brief      enable the PLL clock monitor (API_ID(0x001CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_pll_clock_monitor_enable(void)
{
    RCU_CTL |= RCU_CTL_PLLMEN;
}

/*!
    \brief      disable the PLL clock monitor (API_ID(0x001DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_pll_clock_monitor_disable(void)
{
    RCU_CTL &= ~RCU_CTL_PLLMEN;
}

/*!
    \brief      get the system clock, bus and peripheral clock frequency (API_ID(0x001EU))
    \param[in]  clock: the clock frequency which to get
                only one parameter can be selected which is shown as below:
      \arg        CK_SYS: system clock frequency
      \arg        CK_AHB: AHB clock frequency
      \arg        CK_APB1: APB1 clock frequency
      \arg        CK_APB2: APB2 clock frequency
    \param[out] none
    \retval     clock frequency of system, AHB, APB1, APB2
*/
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock)
{
    uint32_t sws, ck_freq = 0U;
    uint32_t cksys_freq, ahb_freq, apb1_freq, apb2_freq;
    uint32_t pllsel, ck_src, idx, clk_exp;
    uint32_t predv;
    float pllmf;
    float temp;

    /* exponent of AHB, APB1 and APB2 clock divider */
    const uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
    const uint8_t apb1_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    const uint8_t apb2_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};

    sws = GET_BITS(RCU_CFG0, 2, 3);
    switch(sws) {
    /* IRC32M is selected as CK_SYS */
    case SEL_IRC32M:
        cksys_freq = IRC32M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        cksys_freq = HXTAL_VALUE;
        break;
    /* PLL is selected as CK_SYS */
    case SEL_PLL:
        /* PLL clock source selection, HXTAL or IRC32M */
        pllsel = (RCU_CFG0 & RCU_CFG0_PLLSEL);
        if(RCU_PLLSRC_HXTAL == pllsel) {
            /* PLL clock source is HXTAL*/
            ck_src = HXTAL_VALUE;
        } else {
            /* PLL clock source is IRC32M */
            ck_src = IRC32M_VALUE ;
        }
        /* PREVD factor */
        predv = (RCU_CFG1 & RCU_CFG1_PREDV) + 1U;
        /* PLL multiplication factor */
        pllmf = (float)((uint32_t)((RCU_CFG0 & RCU_CFG0_PLLMF) >> ((uint32_t)17U)));
        pllmf = (pllmf + 1.0f) / 2.0f;
        temp = ((float)ck_src * pllmf / (float)predv);
        cksys_freq = (uint32_t)(temp);
        break;
    /* IRC32M is selected as CK_SYS */
    default:
        cksys_freq = IRC32M_VALUE;
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
    default:
        break;
    }
    return ck_freq;
}

/*!
    \brief      get the clock stabilization and peripheral reset flags (API_ID(0x001FU))
    \param[in]  flag: the clock stabilization and peripheral reset flags, refer to rcu_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_IRC32MSTB: IRC32M stabilization flag
      \arg        RCU_FLAG_HXTALSTB: HXTAL stabilization flag
      \arg        RCU_FLAG_PLLSTB: PLL stabilization flag
      \arg        RCU_FLAG_IRC32KSTB: IRC32K stabilization flag
      \arg        RCU_FLAG_LVD0RST: Low Voltage 0 detect error reset flag
      \arg        RCU_FLAG_LOCKUPRST: CPU LOCK UP Error reset flag
      \arg        RCU_FLAG_LVD1RST: Low Voltage 1 Detect Error reset flag
      \arg        RCU_FLAG_LVD2RST: Low Voltage 2 Detect Error reset flag
      \arg        RCU_FLAG_LOHRST: lost of HXTAL Error reset flag
      \arg        RCU_FLAG_LOPRST: lost of PLL Error reset flag
      \arg        RCU_FLAG_V11RST: 1.1V domain Power reset flag
      \arg        RCU_FLAG_OBLRST: option byte loader reset flag
      \arg        RCU_FLAG_EPRST: external PIN reset flag
      \arg        RCU_FLAG_PORRST: power reset flag
      \arg        RCU_FLAG_SWRST: software reset flag
      \arg        RCU_FLAG_FWDGTRST: free watchdog timer reset flag
      \arg        RCU_FLAG_WWDGTRST: window watchdog timer reset flag
      \arg        RCU_FLAG_LPRST: low-power reset flag
    \param[out] none
    \retval     none
*/
FlagStatus rcu_flag_get(rcu_flag_enum flag)
{
    FlagStatus status;
    /* get the rcu flag */
    if(RESET != (RCU_REG_VAL(flag) & BIT(RCU_BIT_POS(flag)))) {
        status = SET;
    } else {
        status = RESET;
    }

    return status;
}

/*!
    \brief      clear all the reset flag (API_ID(0x0020U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_all_reset_flag_clear(void)
{
    RCU_RSTSCK |= RCU_RSTSCK_RSTFC;
}

/*!
    \brief      get the clock stabilization interrupt and ckm flags (API_ID(0x0021U))
    \param[in]  int_flag: interrupt and ckm flags, refer to rcu_int_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_IRC32KSTB: IRC32K stabilization interrupt flag
      \arg        RCU_INT_FLAG_IRC32MSTB: IRC32M stabilization interrupt flag
      \arg        RCU_INT_FLAG_HXTALSTB: HXTAL stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLLSTB: PLL stabilization interrupt flag
      \arg        RCU_INT_FLAG_CKM: HXTAL clock stuck interrupt flag
      \arg        RCU_INT_FLAG_PLLM: PLL clock monitor interrupt flag
      \param[out] none
      \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag)
{
    FlagStatus status;

    /* get the rcu interrupt flag */
    if(RESET != (RCU_REG_VAL(int_flag) & BIT(RCU_BIT_POS(int_flag)))) {
        status = SET;
    } else {
        status = RESET;
    }

    return status;
}

/*!
    \brief      clear the interrupt flags (API_ID(0x0022U))
    \param[in]  int_flag: clock stabilization and stuck interrupt flags clear, refer to rcu_int_flag_clear_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_IRC32KSTB_CLR: IRC32K stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_IRC32MSTB_CLR: IRC32M stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_HXTALSTB_CLR: HXTAL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLLSTB_CLR: PLL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_CKM_CLR: clock stuck interrupt flag clear
      \arg        RCU_INT_FLAG_PLLM_CLR: PLL clock monitor interrupt clear
    \param[out] none
    \retval     none
*/
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag)
{
    RCU_REG_VAL(int_flag) |= BIT(RCU_BIT_POS(int_flag));
}

/*!
    \brief      enable the stabilization interrupt (API_ID(0x0023U))
    \param[in]  interrupt clock stabilization interrupt, refer to rcu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_IRC32KSTB: IRC32K stabilization interrupt enable
      \arg        RCU_INT_IRC32MSTB: IRC32M stabilization interrupt enable
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt enable
      \arg        RCU_INT_PLLSTB: PLL stabilization interrupt enable
      \arg        RCU_INT_PLLM:PLL clock monitor interrupt enable
    \param[out] none
    \retval     none
*/
void rcu_interrupt_enable(rcu_int_enum interrupt)
{
    RCU_REG_VAL(interrupt) |= BIT(RCU_BIT_POS(interrupt));
}

/*!
    \brief      disable the stabilization interrupt (API_ID(0x0024U))
    \param[in]  interrupt clock stabilization interrupt, refer to rcu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_IRC32KSTB: IRC32K stabilization interrupt disable
      \arg        RCU_INT_IRC32MSTB: IRC32M stabilization interrupt disable
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt disable
      \arg        RCU_INT_PLLSTB: PLL stabilization interrupt disable
    \param[out] none
    \retval     none
*/
void rcu_interrupt_disable(rcu_int_enum interrupt)
{
    RCU_REG_VAL(interrupt) &= ~BIT(RCU_BIT_POS(interrupt));
}
