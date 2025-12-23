/*!
    \file    gd32g5x3_rcu.c
    \brief   RCU driver

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

#include "gd32g5x3_rcu.h"

/* define clock source */
#define SEL_IRC8M                    ((uint16_t)0U)                /* IRC8M is selected as CK_SYS */
#define SEL_HXTAL                    ((uint16_t)1U)                /* HXTAL is selected as CK_SYS */
#define SEL_PLLP                     ((uint16_t)3U)                /* PLLP is selected as CK_SYS */
/* define startup timeout count */
#define OSC_STARTUP_TIMEOUT          ((uint32_t)0x000FFFFFU)
#define LXTAL_STARTUP_TIMEOUT        ((uint32_t)0x0FFFFFFFU)
/* RCU IRC8M adjust value mask and offset */
#define RCU_IRC8M_ADJUST_MASK        ((uint8_t)0x1FU)
#define RCU_IRC8M_ADJUST_OFFSET      ((uint32_t)3U)
/* RCU_PLLN, RCU_PLLP, RCU_PLLQ, RCU_PLLR offset */
#define RCU_PLLNOFFSET               ((uint32_t)6U)
#define RCU_PLLPOFFSET               ((uint32_t)16U)
#define RCU_PLLQOFFSET               ((uint32_t)23U)
#define RCU_PLLROFFSET               ((uint32_t)27U)

/* function to calculate the PLL output frequency */
static uint32_t rcu_pll_clock_freq_cal(uint32_t pllinputfreq, uint32_t pll_psc, uint32_t pll_n, uint32_t pll_pqr);

/*!
    \brief      deinitialize the RCU
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_deinit(void)
{
    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;
    while(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)){
    }
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    /* reset CTL register */
    RCU_CTL &= ~(RCU_CTL_HXTALEN | RCU_CTL_CKMEN | RCU_CTL_PLLEN);
    RCU_CTL &= ~(RCU_CTL_HXTALBPS);
    /* reset PLL register */
    RCU_PLL = 0x00000400U;
    /* reset INT register */
    RCU_INT = 0x109F0000U;
    /* reset CFG0 register */
    RCU_CFG0 = 0x00000000U;
    /* reset CFG1 register */
    RCU_CFG1 = 0x00000000U;
    /* reset CFG2 register */
    RCU_CFG2 = 0x00000000U;
}

/*!
    \brief      enable the peripherals clock
    \param[in]  periph: RCU peripherals, refer to rcu_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_DMAx (x = 0,1): DMA clock
      \arg        RCU_DMAMUX: DMAMUX clock
      \arg        RCU_FFT: FFT clock
      \arg        RCU_CLA: CLA clock
      \arg        RCU_CRC: CRC clock
      \arg        RCU_GPIOx (x = A,B,C,D,E,F,G): GPIO ports clock
      \arg        RCU_CAU: CAU clock
      \arg        RCU_FAC: FAC clock
      \arg        RCU_TRNG: TRNG clock
      \arg        RCU_TMU: TMU clock
      \arg        RCU_QSPI : QSPI clock
      \arg        RCU_EXMC: EXMC clock
      \arg        RCU_PMU: PMU clock
      \arg        RCU_I2Cx (x = 0,1,2,3): I2C clock
      \arg        RCU_USARTx (x = 0,1,2): USART clock
      \arg        RCU_UARTx (x = 3,4): UART clock
      \arg        RCU_SPIx (x = 0,1,2): SPI clock
      \arg        RCU_WWDGT: WWDGT clock
      \arg        RCU_LPTIMER: LPTIMER clock
      \arg        RCU_TIMERx (x = 0,1,2,3,4,5,6,7,14,15,16,19): TIMER clock
      \arg        RCU_TRIGSEL: TRIGSEL clock
      \arg        RCU_HRTIMER: HRTIMER clock
      \arg        RCU_HPDF: HPDF clock
      \arg        RCU_SYSCFG: SYSCFG clock
      \arg        RCU_CANx (x = 0,1,2): can clock
      \arg        RCU_CMP: CMP clock
      \arg        RCU_VREF: VREF clock
      \arg        RCU_DACHOLD: DACHOLD clock
      \arg        RCU_DACx (x = 0,1,2,3): DAC clock
      \arg        RCU_ADCx (x = 0,1,2,3): ADC clock
      \arg        RCU_RTC: RTC clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_enable(rcu_periph_enum periph)
{
    RCU_REG_VAL(periph) |= BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      disable the peripherals clock
    \param[in]  periph: RCU peripherals, refer to rcu_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_DMAx (x = 0,1): DMA clock
      \arg        RCU_DMAMUX: DMAMUX clock
      \arg        RCU_FFT: FFT clock
      \arg        RCU_CLA: CLA clock
      \arg        RCU_CRC: CRC clock
      \arg        RCU_GPIOx (x = A,B,C,D,E,F,G): GPIO ports clock
      \arg        RCU_CAU: CAU clock
      \arg        RCU_FAC: FAC clock
      \arg        RCU_TRNG: TRNG clock
      \arg        RCU_TMU: TMU clock
      \arg        RCU_QSPI : QSPI clock
      \arg        RCU_EXMC: EXMC clock
      \arg        RCU_PMU: PMU clock
      \arg        RCU_I2Cx (x = 0,1,2,3): I2C clock
      \arg        RCU_USARTx (x = 0,1,2): USART clock
      \arg        RCU_UARTx (x = 3,4): UART clock
      \arg        RCU_SPIx (x = 0,1,2): SPI clock
      \arg        RCU_WWDGT: WWDGT clock
      \arg        RCU_LPTIMER: LPTIMER clock
      \arg        RCU_TIMERx (x = 0,1,2,3,4,5,6,7,14,15,16,19): TIMER clock
      \arg        RCU_TRIGSEL: TRIGSEL clock
      \arg        RCU_HRTIMER: HRTIMER clock
      \arg        RCU_HPDF: HPDF clock
      \arg        RCU_SYSCFG: SYSCFG clock
      \arg        RCU_CANx (x = 0,1,2): can clock
      \arg        RCU_CMP: CMP clock
      \arg        RCU_VREF: VREF clock
      \arg        RCU_DACHOLD: DACHOLD clock
      \arg        RCU_DACx (x = 0,1,2,3): DAC clock
      \arg        RCU_ADCx (x = 0,1,2,3): ADC clock
      \arg        RCU_RTC: RTC clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_disable(rcu_periph_enum periph)
{
    RCU_REG_VAL(periph) &= ~BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      enable the peripherals clock when sleep and deep-sleep mode
    \param[in]  periph: RCU peripherals, refer to rcu_periph_sleep_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_DMAx_SLP (x = 0,1): DMA clock
      \arg        RCU_DMAMUX_SLP: DMAMUX clock
      \arg        RCU_FFT_SLP: FFT clock
      \arg        RCU_CLA_SLP: CLA clock
      \arg        RCU_CRC_SLP: CRC clock
      \arg        RCU_GPIOx_SLP (x = A,B,C,D,E,F,G): GPIO ports clock
      \arg        RCU_CAU_SLP: CAU clock
      \arg        RCU_FAC_SLP: FAC clock
      \arg        RCU_TRNG_SLP: TRNG clock
      \arg        RCU_TMU_SLP: TMU clock
      \arg        RCU_QSPI_SLP : QSPI clock
      \arg        RCU_EXMC_SLP: EXMC clock
      \arg        RCU_PMU_SLP: PMU clock
      \arg        RCU_I2Cx_SLP (x = 0,1,2,3): I2C clock
      \arg        RCU_USARTx_SLP (x = 0,1,2): USART clock
      \arg        RCU_UARTx_SLP (x = 3,4): UART clock
      \arg        RCU_SPIx_SLP (x = 0,1,2): SPI clock
      \arg        RCU_WWDGT_SLP: WWDGT clock
      \arg        RCU_LPTIMER_SLP: LPTIMER clock
      \arg        RCU_TIMERx_SLP (x = 0,1,2,3,4,5,6,7,14,15,16,19): TIMER clock
      \arg        RCU_TRIGSEL_SLP: TRIGSEL clock
      \arg        RCU_HRTIMER_SLP: HRTIMER clock
      \arg        RCU_HPDF_SLP: HPDF clock
      \arg        RCU_SYSCFG_SLP: SYSCFG clock
      \arg        RCU_CANx_SLP (x = 0,1,2): CAN clock
      \arg        RCU_CMP_SLP: CMP clock
      \arg        RCU_VREF_SLP: VREF clock
      \arg        RCU_DACHOLD_SLP: DACHOLD clock
      \arg        RCU_DACx_SLP (x = 0,1,2,3): DAC clock
      \arg        RCU_ADCx_SLP (x = 0,1,2,3): ADC clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_sleep_enable(rcu_periph_sleep_enum periph)
{
    RCU_REG_VAL(periph) |= BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      disable the peripherals clock when sleep and deep-sleep mode
    \param[in]  periph: RCU peripherals, refer to rcu_periph_sleep_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_DMAx_SLP (x = 0,1): DMA clock
      \arg        RCU_DMAMUX_SLP: DMAMUX clock
      \arg        RCU_FFT_SLP: FFT clock
      \arg        RCU_CLA_SLP: CLA clock
      \arg        RCU_CRC_SLP: CRC clock
      \arg        RCU_GPIOx_SLP (x = A,B,C,D,E,F,G): GPIO ports clock
      \arg        RCU_CAU_SLP: CAU clock
      \arg        RCU_FAC_SLP: FAC clock
      \arg        RCU_TRNG_SLP: TRNG clock
      \arg        RCU_TMU_SLP: TMU clock
      \arg        RCU_QSPI_SLP : QSPI clock
      \arg        RCU_EXMC_SLP: EXMC clock
      \arg        RCU_PMU_SLP: PMU clock
      \arg        RCU_I2Cx_SLP (x = 0,1,2,3): I2C clock
      \arg        RCU_USARTx_SLP (x = 0,1,2): USART clock
      \arg        RCU_UARTx_SLP (x = 3,4): UART clock
      \arg        RCU_SPIx_SLP (x = 0,1,2): SPI clock
      \arg        RCU_WWDGT_SLP: WWDGT clock
      \arg        RCU_LPTIMER_SLP: LPTIMER clock
      \arg        RCU_TIMERx_SLP (x = 0,1,2,3,4,5,6,7,14,15,16,19): TIMER clock
      \arg        RCU_TRIGSEL_SLP: TRIGSEL clock
      \arg        RCU_HRTIMER_SLP: HRTIMER clock
      \arg        RCU_HPDF_SLP: HPDF clock
      \arg        RCU_SYSCFG_SLP: SYSCFG clock
      \arg        RCU_CANx_SLP (x = 0,1,2): CAN clock
      \arg        RCU_CMP_SLP: CMP clock
      \arg        RCU_VREF_SLP: VREF clock
      \arg        RCU_DACHOLD_SLP: DACHOLD clock
      \arg        RCU_DACx_SLP (x = 0,1,2,3): DAC clock
      \arg        RCU_ADCx_SLP (x = 0,1,2,3): ADC clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_sleep_disable(rcu_periph_sleep_enum periph)
{
    RCU_REG_VAL(periph) &= ~BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      reset the peripherals
    \param[in]  periph_reset: RCU peripherals reset, refer to rcu_periph_reset_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_DMAxRST (x = 0,1): reset DMA
      \arg        RCU_DMAMUXRST: reset DMAMUX
      \arg        RCU_FFTRST: reset FFT
      \arg        RCU_CLARST: reset CLA
      \arg        RCU_CRCRST: reset CRC
      \arg        RCU_GPIOxRST (x = A,B,C,D,E,F,G): reset GPIO ports
      \arg        RCU_CAURST: reset CAU
      \arg        RCU_FACRST: reset FAC
      \arg        RCU_TRNGRST: reset TRNG
      \arg        RCU_TMURST: reset TMU
      \arg        RCU_QSPIRST : reset QSPI
      \arg        RCU_EXMCRST: reset EXMC
      \arg        RCU_PMURST: reset PMU
      \arg        RCU_I2CxRST (x = 0,1,2,3): reset I2C
      \arg        RCU_USARTxRST (x = 0,1,2): reset USART
      \arg        RCU_UARTxRST (x = 3,4): reset UART
      \arg        RCU_SPIxRST (x = 0,1,2): reset SPI
      \arg        RCU_WWDGTRST: reset WWDGT
      \arg        RCU_LPTIMERRST: reset LPTIMER
      \arg        RCU_TIMERxRST (x = 0,1,2,3,4,5,6,7,14,15,16,19): reset TIMER
      \arg        RCU_TRIGSELRST: reset TRIGSEL
      \arg        RCU_HRTIMERRST: reset HRTIMER
      \arg        RCU_HPDFRST: reset HPDF
      \arg        RCU_SYSCFGRST: reset SYSCFG
      \arg        RCU_CANxRST (x = 0,1,2): reset CAN
      \arg        RCU_CMPRST: reset CMP
      \arg        RCU_VREFRST: reset VREF
      \arg        RCU_DACHOLDRST: reset DACHOLD
      \arg        RCU_DACxRST (x = 0,1,2,3): reset DAC
      \arg        RCU_ADCxRST (x = 0,1,2,3): reset ADC
    \param[out] none
    \retval     none
*/
void rcu_periph_reset_enable(rcu_periph_reset_enum periph_reset)
{
    RCU_REG_VAL(periph_reset) |= BIT(RCU_BIT_POS(periph_reset));
}

/*!
    \brief      disable reset the peripheral
    \param[in]  periph_reset: RCU peripherals reset, refer to rcu_periph_reset_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_DMAxRST (x = 0,1): reset DMA
      \arg        RCU_DMAMUXRST: reset DMAMUX
      \arg        RCU_FFTRST: reset FFT
      \arg        RCU_CLARST: reset CLA
      \arg        RCU_CRCRST: reset CRC
      \arg        RCU_GPIOxRST (x = A,B,C,D,E,F,G): reset GPIO ports
      \arg        RCU_CAURST: reset CAU
      \arg        RCU_FACRST: reset FAC
      \arg        RCU_TRNGRST: reset TRNG
      \arg        RCU_TMURST: reset TMU
      \arg        RCU_QSPIRST : reset QSPI
      \arg        RCU_EXMCRST: reset EXMC
      \arg        RCU_PMURST: reset PMU
      \arg        RCU_I2CxRST (x = 0,1,2,3): reset I2C
      \arg        RCU_USARTxRST (x = 0,1,2): reset USART
      \arg        RCU_UARTxRST (x = 3,4): reset UART
      \arg        RCU_SPIxRST (x = 0,1,2): reset SPI
      \arg        RCU_WWDGTRST: reset WWDGT
      \arg        RCU_LPTIMERRST: reset LPTIMER
      \arg        RCU_TIMERxRST (x = 0,1,2,3,4,5,6,7,14,15,16,19): reset TIMER
      \arg        RCU_TRIGSELRST: reset TRIGSEL
      \arg        RCU_HRTIMERRST: reset HRTIMER
      \arg        RCU_HPDFRST: reset HPDF
      \arg        RCU_SYSCFGRST: reset SYSCFG
      \arg        RCU_CANxRST (x = 0,1,2): reset CAN
      \arg        RCU_CMPRST: reset CMP
      \arg        RCU_VREFRST: reset VREF
      \arg        RCU_DACHOLDRST: reset DACHOLD
      \arg        RCU_DACxRST (x = 0,1,2,3): reset DAC
      \arg        RCU_ADCxRST (x = 0,1,2,3): reset ADC
    \param[out] none
    \retval     none
*/
void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset)
{
    RCU_REG_VAL(periph_reset) &= ~BIT(RCU_BIT_POS(periph_reset));
}

/*!
    \brief      reset the BKP
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_bkp_reset_enable(void)
{
    RCU_BDCTL |= RCU_BDCTL_BKPRST;
}

/*!
    \brief      disable the BKP reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_bkp_reset_disable(void)
{
    RCU_BDCTL &= ~RCU_BDCTL_BKPRST;
}

/*!
    \brief      configure the system clock source
    \param[in]  ck_sys: system clock source select
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKSYSSRC_IRC8M: select CK_IRC8M as the CK_SYS source
      \arg        RCU_CKSYSSRC_HXTAL: select CK_HXTAL as the CK_SYS source
      \arg        RCU_CKSYSSRC_PLLP: select CK_PLLP as the CK_SYS source
    \param[out] none
    \retval     none
*/
void rcu_system_clock_source_config(uint32_t ck_sys)
{
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the SCS bits and set according to ck_sys */
    reg &= ~RCU_CFG0_SCS;
    RCU_CFG0 = (reg | ck_sys);
}

/*!
    \brief      get the system clock source
    \param[in]  none
    \param[out] none
    \retval     which clock is selected as CK_SYS source
      \arg        RCU_SCSS_IRC8M: CK_IRC8M is selected as the CK_SYS source
      \arg        RCU_SCSS_HXTAL: CK_HXTAL is selected as the CK_SYS source
      \arg        RCU_SCSS_PLLP: CK_PLLP is selected as the CK_SYS source
*/
uint32_t rcu_system_clock_source_get(void)
{
    return (RCU_CFG0 & RCU_CFG0_SCSS);
}

/*!
    \brief      configure the AHB clock prescaler selection
    \param[in]  ck_ahb: AHB clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_AHB_CKSYS_DIVx (x = 1, 2, 4, 8, 16, 64, 128, 256, 512): CK_AHB is CK_SYS/x
    \param[out] none
    \retval     none
*/
void rcu_ahb_clock_config(uint32_t ck_ahb)
{
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the AHBPSC bits and set according to ck_ahb */
    reg &= ~RCU_CFG0_AHBPSC;
    RCU_CFG0 = (reg | ck_ahb);
}

/*!
    \brief      configure the APB1 clock prescaler selection
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
    RCU_CFG0 = (reg | ck_apb1);
}

/*!
    \brief      configure the APB2 clock prescaler selection
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
    RCU_CFG0 = (reg | ck_apb2);
}

/*!
    \brief      configure the APB3 clock prescaler selection
    \param[in]  ck_apb3: APB3 clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_APB3_CKAHB_DIV1: select CK_AHB as CK_APB3
      \arg        RCU_APB3_CKAHB_DIV2: select CK_AHB / 2 as CK_APB3
      \arg        RCU_APB3_CKAHB_DIV4: select CK_AHB / 4 as CK_APB3
      \arg        RCU_APB3_CKAHB_DIV8: select CK_AHB / 8 as CK_APB3
      \arg        RCU_APB3_CKAHB_DIV16: select CK_AHB/ 16 as CK_APB3
    \param[out] none
    \retval     none
*/
void rcu_apb3_clock_config(uint32_t ck_apb3)
{
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the APB3PSC and set according to ck_apb3 */
    reg &= ~RCU_CFG0_APB3PSC;
    RCU_CFG0 = (reg | ck_apb3);
}

/*!
    \brief      configure the CK_OUT clock source and divider
    \param[in]  ckout_src: CK_OUT clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKOUTSRC_IRC32K: IRC32K selected
      \arg        RCU_CKOUTSRC_LXTAL: LXTAL selected
      \arg        RCU_CKOUTSRC_CKSYS: systerm clock selected
      \arg        RCU_CKOUTSRC_IRC8M: IRC8M selected
      \arg        RCU_CKOUTSRC_HXTAL: HXTAL selected
      \arg        RCU_CKOUTSRC_PLLP: PLLP selected
    \param[in]  ckout_div: CK_OUT divider
      \arg        RCU_CKOUT_DIVx (x = 1,2,4,8,16): CK_OUT is divided by x
    \param[out] none
    \retval     none
*/
void rcu_ckout_config(uint32_t ckout_src, uint32_t ckout_div)
{
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the CKOUTSRC, CKOUTDIV and set according to ckout_src and ckout_div */
    reg &= ~(RCU_CFG0_CKOUTSEL | RCU_CFG0_CKOUTDIV);
    RCU_CFG0 = (reg | ckout_src | ckout_div);
}

/*!
    \brief      enable the low speed clock output
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_lsckout_enable(void)
{
    RCU_BDCTL |= RCU_BDCTL_LSCKOUTEN;
}

/*!
    \brief      disable the low speed clock output
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_lsckout_disable(void)
{
    RCU_BDCTL &= ~RCU_BDCTL_LSCKOUTEN;
}

/*!
    \brief      configure the LSCKOUT clock source
    \param[in]  lsc_ckout_src: LSCKOUT clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_LSCKOUTSRC_IRC32K: IRC32K clock selected
      \arg        RCU_LSCKOUTSRC_LXTAL: LXTAL selected
    \param[out] none
    \retval     none
*/
void rcu_lsckout_config(uint32_t lsckout_src)
{
    uint32_t reg;

    reg = RCU_BDCTL;
    /* reset the LSCKOUTSEL */
    reg &= ~(RCU_BDCTL_LSCKOUTSEL);
    RCU_BDCTL = (reg | lsckout_src);
}

/*!
    \brief      configure PLL clock source
    \param[in]  pll_src: PLL clock source selection
      \arg        RCU_PLLSRC_IRC8M: select IRC8M as PLL source clock
      \arg        RCU_PLLSRC_HXTAL: select HXTAL as PLL source clock
    \param[out] none
    \retval     none
*/
void rcu_pll_source_config(uint32_t pll_src)
{
    /* PLL clock source selection */
    RCU_PLL &= ~(RCU_PLL_PLLSEL);
    RCU_PLL |= pll_src;
}

/*!
    \brief      configure the main PLL clock
    \param[in]  pll_psc: the PLL VCO source clock prescaler
      \arg         this parameter should be selected between 1 and 16. When pll_psc=0, the PLL VCO source clock prescaler close.
    \param[in]  pll_n: the PLL VCO clock multi factor
      \arg        this parameter should be selected between 8 and 180
    \param[in]  pll_p: the PLLP output frequency division factor from PLL0 VCO clock
      \arg        this parameter should be selected 2,4,6,8
    \param[in]  pll_q: the PLLQ output frequency division factor from PLL0 VCO clock
      \arg        this parameter should be selected between 2 and 15
    \param[in]  pll_r: the PLLR output frequency division factor from PLL0 VCO clock
      \arg        this parameter should be selected between 2 and 31
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus rcu_pll_config(uint32_t pll_psc, uint32_t pll_n, uint32_t pll_p, uint32_t pll_q, uint32_t pll_r)
{
    /* check the function parameter */
    if(CHECK_PLL_PSC_VALID(pll_psc) && CHECK_PLL_N_VALID(pll_n) &&
            CHECK_PLL_P_VALID(pll_p) && CHECK_PLL_Q_VALID(pll_q) &&
            CHECK_PLL_R_VALID(pll_r)) {
        RCU_PLL &= ~(RCU_PLL_PLLPSC | RCU_PLL_PLLN | RCU_PLL_PLLP | RCU_PLL_PLLR);
        RCU_PLL |= (pll_psc -1U) | (pll_n << RCU_PLLNOFFSET) | (((pll_p >> 1U) - 1U) << RCU_PLLPOFFSET) |
                    ((pll_r) << RCU_PLLROFFSET) | ((pll_q) << RCU_PLLROFFSET);
    } else {
        /* return status */
        return ERROR;
    }

    /* return status */
    return SUCCESS;
}


/*!
    \brief      enable the pllp pllq pllr divider output
    \param[in]  pllx: the output pll enable
      \arg        RCU_PLLP: PLLP divider output enable
      \arg        RCU_PLLQ: PLLQ divider output enable
      \arg        RCU_PLLR: PLLR divider output enable
    \param[out] none
    \retval     none
*/
void rcu_pll_clock_output_enable(uint32_t pllx)
{
    /* PLL divider output enable */
    RCU_PLL |= pllx;
}

/*!
    \brief      disable the pllp pllq pllr divider output
    \param[in]  pllx: the output pll disable
      \arg        RCU_PLLP: PLLP divider output disable
      \arg        RCU_PLLQ: PLLQ divider output disable
      \arg        RCU_PLLR: PLLR divider output disable
    \param[out] none
    \retval     none
*/
void rcu_pll_clock_output_disable(uint32_t pllx)
{
    /* PLL divider output disable */
    RCU_PLL &= ~(pllx);
}

/*!
    \brief      configure the RTC clock source selection
    \param[in]  rtc_clock_source: RTC clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_RTCSRC_NONE: no clock selected
      \arg        RCU_RTCSRC_LXTAL: CK_LXTAL selected as RTC source clock
      \arg        RCU_RTCSRC_IRC32K: CK_IRC32K selected as RTC source clock
      \arg        RCU_RTCSRC_HXTAL_DIV32: CK_HXTAL /32 selected as RTC source clock
    \param[out] none
    \retval     none
*/
void rcu_rtc_clock_config(uint32_t rtc_clock_source)
{
    uint32_t reg;

    reg = RCU_BDCTL;
    /* reset the RTCSRC bits and set according to rtc_clock_source */
    reg &= ~RCU_BDCTL_RTCSRC;
    RCU_BDCTL = (reg | rtc_clock_source);
}

/*!
    \brief      configure the USARTx (x = 0,1,2) clock source selection
    \param[in]  usart_idx: IDX_USARTx (x = 0,1,2)
    \param[in]  ck_usart: USART clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_USARTSRC_APB: CK_USART select CK_APB1(USART1 / USART2) or CK_APB2(USART0)
      \arg        RCU_USARTSRC_CKSYS: CK_USART select CK_SYS
      \arg        RCU_USARTSRC_LXTAL: CK_USART select CK_LXTAL
      \arg        RCU_USARTSRC_IRC8M: CK_USART select CK_IRC8M
    \param[out] none
    \retval     none
*/
void rcu_usart_clock_config(usart_idx_enum usart_idx, uint32_t ck_usart)
{
    switch(usart_idx) {
    case IDX_USART0:
        /* reset the USART0SEL bits and set according to ck_usart */
        RCU_CFG1 &= ~RCU_CFG1_USART0SEL;
        RCU_CFG1 |= ck_usart;
        break;

    case IDX_USART1:
        /* reset the USART1SEL bits and set according to ck_usart */
        RCU_CFG1 &= ~RCU_CFG1_USART1SEL;
        RCU_CFG1 |= (uint32_t)ck_usart << 18U;
        break;

    case IDX_USART2:
        /* reset the USART2SEL bits and set according to ck_usart */
        RCU_CFG1 &= ~RCU_CFG1_USART2SEL;
        RCU_CFG1 |= (uint32_t)ck_usart << 20U;
        break;

    default:
        break;
    }
}

/*!
    \brief      configure the I2Cx (x = 0,1,2,3) clock source selection
    \param[in]  i2c_idx: IDX_I2Cx (x = 0,1,2,3)
    \param[in]  ck_i2c: I2C clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_I2CSRC_APB1: CK_I2C select CK_APB1
      \arg        RCU_I2CSRC_CKSYS: CK_I2C select CK_SYS
      \arg        RCU_I2CSRC_IRC8M: CK_I2C select CK_IRC8M
    \param[out] none
    \retval     none
*/
void rcu_i2c_clock_config(i2c_idx_enum i2c_idx, uint32_t ck_i2c)
{
    switch(i2c_idx) {
    case IDX_I2C0:
        /* reset the I2C0SEL bits and set according to ck_i2c */
        RCU_CFG2 &= ~RCU_CFG2_I2C0SEL;
        RCU_CFG2 |= ck_i2c ;
        break;

    case IDX_I2C1:
        /* reset the I2C1SEL bits and set according to ck_i2c */
        RCU_CFG2 &= ~RCU_CFG2_I2C1SEL;
        RCU_CFG2 |= (uint32_t)ck_i2c << 2U;
        break;

    case IDX_I2C2:
        /* reset the I2C2SEL bits and set according to ck_i2c */
        RCU_CFG2 &= ~RCU_CFG2_I2C2SEL;
        RCU_CFG2 |= (uint32_t)ck_i2c << 4U;
        break;

    case IDX_I2C3:
        /* reset the I2C4SEL bits and set according to ck_i2c */
        RCU_CFG2 &= ~RCU_CFG2_I2C3SEL;
        RCU_CFG2 |= (uint32_t)ck_i2c << 6U;
        break;

    default:
        break;
    }
}

/*!
    \brief      configure the CANx (x = 0,1,2) clock source selection
    \param[in]  can_idx: IDX_CANx (x = 0,1,2)
    \param[in]  ck_can: CAN clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CANSRC_IRC8M: CK_CAN select CK_IRC8M
      \arg        RCU_CANSRC_APB2: CK_CAN select CK_APB2
      \arg        RCU_CANSRC_PLLQ: CK_CAN select CK_PLLQ
      \arg        RCU_CANSRC_HXTAL: CK_CAN select CK_HXTAL
    \param[out] none
    \retval     none
*/
void rcu_can_clock_config(can_idx_enum can_idx, uint32_t ck_can)
{
    switch(can_idx) {
    case IDX_CAN0:
        /* reset the CAN0SEL bits and set according to ck_can */
        RCU_CFG1 &= ~RCU_CFG1_CAN0SEL;
        RCU_CFG1 |= ck_can ;
        break;

    case IDX_CAN1:
        /* reset the CAN1SEL bits and set according to ck_can */
        RCU_CFG1 &= ~RCU_CFG1_CAN1SEL;
        RCU_CFG1 |= (uint32_t)ck_can << 2U;
        break;

    case IDX_CAN2:
        /* reset the CAN2SEL bits and set according to ck_can */
        RCU_CFG1 &= ~RCU_CFG1_CAN2SEL;
        RCU_CFG1 |= (uint32_t)ck_can << 4U;
        break;

    default:
        break;
    }
}

/*!
    \brief      configure the ADCx (x = 0,1,2,3) clock source selection
    \param[in]  adc_idx: IDX_ADCx (x = 0,1,2,3)
    \param[in]  ck_adc: ADC clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_ADCSRC_PLLR: CK_ADC select CK_PLLR
      \arg        RCU_ADCSRC_CKSYS: CK_ADC select CKSYS
    \param[out] none
    \retval     none
*/
void rcu_adc_clock_config(adc_idx_enum adc_idx, uint32_t ck_adc)
{
    switch(adc_idx) {
    case IDX_ADC0:
    case IDX_ADC1:
    case IDX_ADC2:
        /* reset the ADC012SEL bits and set according to ck_adc */
        RCU_CFG2 &= ~RCU_CFG2_ADC0_1_2SEL;
        RCU_CFG2 |= ck_adc ;
        break;

    case IDX_ADC3:
        /* reset the ADC3SEL bits and set according to ck_adc */
        RCU_CFG2 &= ~RCU_CFG2_ADC3SEL;
        RCU_CFG2 |= (uint32_t)ck_adc << 2U;
        break;

    default:
        break;
    }
}

/*!
    \brief      configure the HPDF clock source selection
    \param[in]  ck_hpdf: HPDF clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_HPDFSRC_APB2: CK_HPDF select CK_APB2
      \arg        RCU_HPDFSRC_AHB: CK_HPDF select CK_AHB
    \param[out] none
    \retval     none
*/
void rcu_hpdf_clock_config(uint32_t ck_hpdf)
{
    /* reset the HPDFSEL bits and set according to ck_hpdf */
    RCU_CFG1 &= ~RCU_CFG1_HPDFSEL;
    RCU_CFG1 |= ck_hpdf ;
}

/*!
    \brief      configure the HPDF clock source selection
    \param[in]  ck_hpdf: HPDF clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_HPDFAUDIO_PLLQ: CK_HPDFAUDIO select CK_PLLQ
      \arg        RCU_HPDFAUDIO_EHPDFAUDIOPIN: CK_HPDFAUDIO select CK_EHPDFAUDIOPIN
      \arg        RCU_HPDFAUDIO_IRC8M: CK_HPDFAUDIO select IRC8M
    \param[out] none
    \retval     none
*/
void rcu_hpdfaudio_clock_config(uint32_t ck_hpdfaudio)
{
    /* reset the HPDFAUDIOSEL bits and set according to ck_hpdfaudio */
    RCU_CFG1 &= ~RCU_CFG1_HPDFAUDIOSEL;
    RCU_CFG1 |= ck_hpdfaudio ;
}

/*!
    \brief      configure the TRNG prescaler selection
    \param[in]  ck_trng: TRNG clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_TRNG_CKPLLQ_DIVx (x = 2, 3, 4,... , 15): CK_AHB is CKPLLQ/x
    \param[out] none
    \retval     none
*/
void rcu_trng_clock_config(uint32_t ck_trng)
{
    /* reset the RCU_CFG2_TRNGPSC bits and set according to ck_trng */
    RCU_CFG2 &= ~RCU_CFG2_TRNGPSC;
    RCU_CFG2 |= ck_trng;
}

/*!
    \brief      configure the LPTIMER clock source selection
    \param[in]  ck_lptimer: LPTIMER clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_LPTIMERSRC_APB1: CK_LPTIMER select CK_APB1
      \arg        RCU_LPTIMERSRC_IRC32K: CK_LPTIMER select CK_IRC32K
      \arg        RCU_LPTIMERSRC_LXTAL: CK_LPTIMER select CK_LXTAL
      \arg        RCU_LPTIMERSRC_IRC8M: CK_LPTIMER select CK_IRC8M
    \param[out] none
    \retval     none
*/
void rcu_lptimer_clock_config(uint32_t ck_lptimer)
{
    /* reset the LPTIMERSEL bits and set according to ck_lptimer */
    RCU_CFG2 &= ~RCU_CFG2_LPTIMERSEL;
    RCU_CFG2 |= ck_lptimer;
}

/*!
    \brief      configure the QSPI clock source selection
    \param[in]  ck_qspi: QSPI clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_QSPISRC_CKSYS: CK_QSPI select CK_CKSYS
      \arg        RCU_QSPISRC_IRC8M: CK_QSPI select CK_IRC8M
      \arg        RCU_QSPISRC_PLLQ: CK_QSPI select CK_PLLQ
    \param[out] none
    \retval     none
*/
void rcu_qspi_clock_config(uint32_t ck_qspi)
{
    /* reset the QSPISEL bits and set according to ck_lptimer */
    RCU_CFG2 &= ~RCU_CFG2_QSPISEL;
    RCU_CFG2 |= ck_qspi;
}

/*!
    \brief      configure the HRTIMER clock source selection
    \param[in]  hrtimer_clock_source: HRTIMER clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_HRTIMERSRC_CKAPB2: APB2 clock selected as HRTIMER source clock
      \arg        RCU_HRTIMERSRC_CKSYS: system clock selected as HRTIMER source clock 
    \param[out] none
    \retval     none
*/
void rcu_hrtimer_clock_config(uint32_t hrtimer_clock_source)
{
    uint32_t reg;
    
    reg = RCU_CFG2; 
    /* reset the HRTIMERSEL bit and set according to hrtimer_clock_source */
    reg &= ~RCU_CFG2_HRTIMERSEL;
    RCU_CFG2 = (reg | hrtimer_clock_source);
}

/*!
    \brief      configure the LXTAL drive capability
    \param[in]  lxtal_dricap: drive capability of LXTAL
                only one parameter can be selected which is shown as below:
      \arg        RCU_LXTAL_LOWDRI: lower driving capability
      \arg        RCU_LXTAL_MED_LOWDRI: medium low driving capability
      \arg        RCU_LXTAL_MED_HIGHDRI: medium high driving capability
      \arg        RCU_LXTAL_HIGHDRI: higher driving capability (reset value)
    \param[out] none
    \retval     none
*/
void rcu_lxtal_drive_capability_config(uint32_t lxtal_dricap)
{
    uint32_t reg;

    reg = RCU_BDCTL;

    /* reset the LXTALDRI bits and set according to lxtal_dricap */
    reg &= ~RCU_BDCTL_LXTALDRI;
    RCU_BDCTL = (reg | lxtal_dricap);
}

/*!
    \brief      wait for oscillator stabilization flags is SET or oscillator startup is timeout
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: HXTAL
      \arg        RCU_LXTAL: LXTAL
      \arg        RCU_IRC8M: IRC8M
      \arg        RCU_IRC32K: IRC32K
      \arg        RCU_PLL_CK: PLL
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

        /* check whether flag is set */
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

        /* check whether flag is set */
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

        /* check whether flag is set */
        if(RESET != rcu_flag_get(RCU_FLAG_IRC8MSTB)) {
            reval = SUCCESS;
        }

        break;

    /* wait IRC32K stable */
    case RCU_IRC32K:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_IRC32KSTB);
            stb_cnt++;
        }

        /* check whether flag is set */
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

        /* check whether flag is set */
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
    \brief      turn on the oscillator
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: HXTAL
      \arg        RCU_LXTAL: LXTAL
      \arg        RCU_IRC8M: IRC8M
      \arg        RCU_IRC32K: IRC32K
      \arg        RCU_PLL_CK: PLL
    \param[out] none
    \retval     none
*/
void rcu_osci_on(rcu_osci_type_enum osci)
{
    RCU_REG_VAL(osci) |= BIT(RCU_BIT_POS(osci));
}

/*!
    \brief      turn off the oscillator
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: HXTAL
      \arg        RCU_LXTAL: LXTAL
      \arg        RCU_IRC8M: IRC8M
      \arg        RCU_IRC32K: IRC32K
      \arg        RCU_PLL_CK: PLL
    \param[out] none
    \retval     none
*/
void rcu_osci_off(rcu_osci_type_enum osci)
{
    RCU_REG_VAL(osci) &= ~BIT(RCU_BIT_POS(osci));
}

/*!
    \brief      enable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator (HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator (LXTAL)
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
    \brief      disable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator (HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator (LXTAL)
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
    \brief      scillator stabilization reset
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator (HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator (LXTAL)
    \param[out] none
    \retval     none
*/
void rcu_osci_stablization_reset(rcu_osci_type_enum osci)
{
    switch(osci) {
    /* HXTAL stabilization reset */
    case RCU_HXTAL:
        RCU_CTL |= RCU_CTL_HXTALSTBRST;
        break;

    /* LXTAL stabilization reset */
    case RCU_LXTAL:
        RCU_BDCTL |= RCU_BDCTL_LXTALSTBRST;
        break;

    default:
        break;
    }
}

/*!
    \brief      set the IRC8M adjust value
    \param[in]  irc8M_adjval: IRC8M adjust value, must be between 0 and 0x1F
      \arg        0x00 - 0x1F
    \param[out] none
    \retval     none
*/
void rcu_irc8m_adjust_value_set(uint32_t irc8M_adjval)
{
    uint32_t reg;

    reg = RCU_CTL;
    /* reset the IRC8MADJ bits and set according to irc8m_adjval */
    reg &= ~RCU_CTL_IRC8MADJ;
    RCU_CTL = (reg | ((irc8M_adjval & RCU_IRC8M_ADJUST_MASK) << RCU_IRC8M_ADJUST_OFFSET));
}


/*!
    \brief      enable the HXTAL clock monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_hxtal_clock_monitor_enable(void)
{
    RCU_CTL |= RCU_CTL_CKMEN;
}

/*!
    \brief      disable the HXTAL clock monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_hxtal_clock_monitor_disable(void)
{
    RCU_CTL &= ~RCU_CTL_CKMEN;
}

/*!
    \brief      enable the LXTAL clock monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_lxtal_clock_monitor_enable(void)
{
    RCU_BDCTL |= RCU_BDCTL_LCKMEN;
}

/*!
    \brief      disable the LXTAL clock monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_lxtal_clock_monitor_disable(void)
{
    RCU_BDCTL &= ~RCU_BDCTL_LCKMEN;
}

/*!
    \brief      function to calculate the PLL frequency output
    \param[in]  pllinputfreq: PLL Input frequency
      \arg        this parameter should be selected between HXTAL_VALUE, or IRC8M_VALUE
    \param[in]  pll_psc: the PLL source clock prescaler
      \arg         this parameter should be selected between 1 and 16.
    \param[in]  pll_n: the PLL clock multi factor
      \arg        this parameter should be selected between 8 and 180
    \param[in]  pll_pqr: the PLL P / Q / R output frequency division factor from PLL VCO clock
      \arg        PLL Q / R should be selected between 2 and 15,PLL P should be selected between 2 and 8

    \param[out] none
    \retval     uint32_t: PLL clock frequency
*/
static uint32_t rcu_pll_clock_freq_cal(uint32_t pllinputfreq, uint32_t pll_psc, uint32_t pll_n, uint32_t pll_pqr)
{
    uint32_t freq;

    freq = ((uint32_t)pllinputfreq / (uint32_t)pll_psc) * ((uint32_t)pll_n );

    freq = freq / pll_pqr;

    return (uint32_t)freq;
}

/*!
    \brief    get the system clock, bus and peripheral clock frequency
    \param[in]  clock: the clock frequency which to get
                only one parameter can be selected which is shown as below:
      \arg        CK_SYS: system clock frequency
      \arg        CK_AHB: AHB clock frequency
      \arg        CK_APB1: APB1 clock frequency
      \arg        CK_APB2: APB2 clock frequency
      \arg        CK_APB3: APB3 clock frequency
      \arg        CK_PLLP: PLLP clock frequency
      \arg        CK_PLLQ: PLLQ clock frequency
      \arg        CK_PLLR: PLLR clock frequency
      \arg        CK_USART0: USART0 clock frequency
      \arg        CK_USART1: USART1 clock frequency
      \arg        CK_USART2: USART2 clock frequency
    \param[out] none
    \retval     uint32_t: clock frequency of system, AHB, APB1, APB2, APB3, PLL, USART
*/
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock)
{
    uint32_t sws, ck_freq = 0U;
    uint32_t cksys_freq, ahb_freq, apb1_freq, apb2_freq, apb3_freq;
    uint32_t pllp_freq, pllq_freq, pllr_freq;
    uint32_t pllpsc,plln, pllsel, pllp, pllq, pllr, ck_src, idx, clk_exp;
    uint32_t usart_freq = 0U;

    /* exponent of AHB, APB1 and APB2 clock divider */
    const uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
    const uint8_t apb1_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    const uint8_t apb2_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    const uint8_t apb3_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};

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

    /* PLLP is selected as CK_SYS */
    case SEL_PLLP:
        /* get the value of PLLPSC[3:0] */
        pllpsc = GET_BITS(RCU_PLL, 0U, 3U)+ 1U;
        plln = GET_BITS(RCU_PLL, 6U, 13U);
        pllp = (GET_BITS(RCU_PLL, 16U, 17U) + 1U) * 2U;
        /* PLL clock source selection, HXTAL or IRC8M */
        pllsel = (RCU_PLL & RCU_PLL_PLLSEL);
        if(RCU_PLLSRC_HXTAL == pllsel) {
            ck_src = HXTAL_VALUE;
        } else {
            ck_src = IRC8M_VALUE;
        }
        cksys_freq = ((ck_src / pllpsc) * plln) / pllp;
        break;

    /* IRC8M is selected as CK_SYS */
    default:
        cksys_freq = IRC8M_VALUE;
        break;
    }

    /* calculate AHB clock frequency */
    idx = GET_BITS(RCU_CFG0, 4, 7);
    clk_exp = ahb_exp[idx];
    ahb_freq = cksys_freq >> clk_exp;

    /* calculate APB1 clock frequency */
    idx = GET_BITS(RCU_CFG0, 10, 12);
    clk_exp = apb1_exp[idx];
    apb1_freq = ahb_freq >> clk_exp;

    /* calculate APB2 clock frequency */
    idx = GET_BITS(RCU_CFG0, 13, 15);
    clk_exp = apb2_exp[idx];
    apb2_freq = ahb_freq >> clk_exp;

    /* calculate APB3 clock frequency */
    idx = GET_BITS(RCU_CFG0, 27, 29);
    clk_exp = apb3_exp[idx];
    apb3_freq = ahb_freq >> clk_exp;

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
    case CK_APB3:
        ck_freq = apb3_freq;
        break;
    case CK_PLLP:
        pllp_freq = 0U;
        /* calculate pllp clock frequency */
        pllpsc = GET_BITS(RCU_PLL, 0U, 3U);
        plln = (GET_BITS(RCU_PLL, 6U, 13U));
        pllp = (GET_BITS(RCU_PLL, 16U, 17U) + 1U) * 2U;
        /* PLL clock source selection, HXTAL or IRC8M */
        pllsel = (RCU_PLL & RCU_PLL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel) {
            ck_src = HXTAL_VALUE;
        } else {
            ck_src = IRC8M_VALUE;
        }

        if((RCU_PLL & RCU_PLL_PLLPEN) != 0U) {
            pllp_freq = rcu_pll_clock_freq_cal(ck_src, pllpsc, plln, pllp);
        }


        ck_freq = pllp_freq;
        break;
    case CK_PLLR:
        pllr_freq = 0U;
        /* calculate pllp clock frequency */
        pllpsc = GET_BITS(RCU_PLL, 0U, 3U);
        plln = (GET_BITS(RCU_PLL, 6U, 13U));
        pllr = (GET_BITS(RCU_PLL, 27U, 31U));
        /* PLL clock source selection, HXTAL or IRC8M */
        pllsel = (RCU_PLL & RCU_PLL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel) {
            ck_src = HXTAL_VALUE;
        } else {
            ck_src = IRC8M_VALUE;
        }

        if((RCU_PLL & RCU_PLL_PLLPEN) != 0U) {
            pllr_freq = rcu_pll_clock_freq_cal(ck_src, pllpsc, plln, pllr);
        }


        ck_freq = pllr_freq;
        break;
    case CK_PLLQ:
        pllq_freq = 0U;
        /* calculate pllp clock frequency */
        pllpsc = GET_BITS(RCU_PLL, 0U, 3U);
        plln = (GET_BITS(RCU_PLL, 6U, 13U));
        pllq = (GET_BITS(RCU_PLL, 23U, 26U));
        /* PLL clock source selection, HXTAL or IRC8M */
        pllsel = (RCU_PLL & RCU_PLL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel) {
            ck_src = HXTAL_VALUE;
        } else {
            ck_src = IRC8M_VALUE;
        }

        if((RCU_PLL & RCU_PLL_PLLPEN) != 0U) {
            pllq_freq = rcu_pll_clock_freq_cal(ck_src, pllpsc, plln, pllq);
        }


        ck_freq = pllq_freq;
        break;
    case CK_USART0:
        /* calculate USART0 clock frequency */
        if(RCU_USARTSRC_APB == (RCU_CFG1 & RCU_CFG1_USART0SEL)) {
            usart_freq = apb2_freq;
        } else if(RCU_USARTSRC_CKSYS == (RCU_CFG1 & RCU_CFG1_USART0SEL)) {
            usart_freq = cksys_freq;
        } else if(RCU_USARTSRC_LXTAL == (RCU_CFG1 & RCU_CFG1_USART0SEL)) {
            usart_freq = LXTAL_VALUE;
        } else if(RCU_USARTSRC_IRC8M == (RCU_CFG1 & RCU_CFG1_USART0SEL)) {
            usart_freq = IRC8M_VALUE;
        } else {
        }

        ck_freq = usart_freq;
        break;
    case CK_USART1:
        /* calculate USART1 clock frequency */
        if((RCU_USARTSRC_APB << 18U) == (RCU_CFG1 & RCU_CFG1_USART1SEL)) {
            usart_freq = apb1_freq;
        } else if((RCU_USARTSRC_CKSYS << 18U) == (RCU_CFG1 & RCU_CFG1_USART1SEL)) {
            usart_freq = cksys_freq;
        } else if((RCU_USARTSRC_LXTAL << 18U) == (RCU_CFG1 & RCU_CFG1_USART1SEL)) {
            usart_freq = LXTAL_VALUE;
        } else if((RCU_USARTSRC_IRC8M << 18U) == (RCU_CFG1 & RCU_CFG1_USART1SEL)) {
            usart_freq = IRC8M_VALUE;
        } else {
        }

        ck_freq = usart_freq;
        break;
    case CK_USART2:
        /* calculate USART2 clock frequency */
        if((RCU_USARTSRC_APB << 20U) == (RCU_CFG1 & RCU_CFG1_USART2SEL)) {
            usart_freq = apb1_freq;
        } else if((RCU_USARTSRC_CKSYS << 20U) == (RCU_CFG1 & RCU_CFG1_USART2SEL)) {
            usart_freq = ahb_freq;
        } else if((RCU_USARTSRC_LXTAL << 20U) == (RCU_CFG1 & RCU_CFG1_USART2SEL)) {
            usart_freq = LXTAL_VALUE;
        } else if((RCU_USARTSRC_IRC8M << 20U) == (RCU_CFG1 & RCU_CFG1_USART2SEL)) {
            usart_freq = IRC8M_VALUE;
        } else {
        }

        ck_freq = usart_freq;
        break;
    default:
        break;
    }

    return ck_freq;
}

/*!
    \brief      get the clock stabilization and peripheral reset flags
    \param[in]  flag: the clock stabilization and peripheral reset flags, refer to rcu_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_IRC8MSTB: IRC8M stabilization flag
      \arg        RCU_FLAG_HXTALSTB: HXTAL stabilization flag
      \arg        RCU_FLAG_PLLSTB: PLL stabilization flag
      \arg        RCU_FLAG_LXTALSTB: LXTAL stabilization flag
      \arg        RCU_FLAG_IRC32KSTB: IRC32K stabilization flag
      \arg        RCU_FLAG_LCKMD: LXTAL clock failure detection flag
      \arg        RCU_FLAG_OBLRST: OBL reset flag
      \arg        RCU_FLAG_BORRST: BOR reset flag
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
    /* get the rcu flag */
    if(RESET != (RCU_REG_VAL(flag) & BIT(RCU_BIT_POS(flag)))) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief    clear all the reset flag
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_all_reset_flag_clear(void)
{
    RCU_RSTSCK |= RCU_RSTSCK_RSTFC;
}

/*!
    \brief      enable the stabilization interrupt
    \param[in]  interrupt: clock stabilization interrupt, refer to rcu_int_enum
                Only one parameter can be selected which is shown as below:
      \arg        RCU_INT_IRC32KSTB: IRC32K stabilization interrupt enable
      \arg        RCU_INT_LXTALSTB: LXTAL stabilization interrupt enable
      \arg        RCU_INT_IRC8MSTB: IRC8M stabilization interrupt enable
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt enable
      \arg        RCU_INT_PLLSTB: PLL stabilization interrupt enable
    \param[out] none
    \retval     none
*/
void rcu_interrupt_enable(rcu_int_enum interrupt)
{
    RCU_REG_VAL(interrupt) |= BIT(RCU_BIT_POS(interrupt));
}


/*!
    \brief      disable the stabilization interrupt
    \param[in]  interrupt: clock stabilization interrupt, refer to rcu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_IRC32KSTB: IRC32K stabilization interrupt disable
      \arg        RCU_INT_LXTALSTB: LXTAL stabilization interrupt disable
      \arg        RCU_INT_IRCMSTB: IRC8M stabilization interrupt disable
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt disable
      \arg        RCU_INT_PLLSTB: PLL stabilization interrupt disable
    \param[out] none
    \retval     none
*/
void rcu_interrupt_disable(rcu_int_enum interrupt)
{
    RCU_REG_VAL(interrupt) &= ~BIT(RCU_BIT_POS(interrupt));
}

/*!
    \brief      get the clock stabilization interrupt and ckm flags
    \param[in]  int_flag: interrupt and ckm flags, refer to rcu_int_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_IRC32KSTB: IRC32K stabilization interrupt flag
      \arg        RCU_INT_FLAG_LXTALSTB: LXTAL stabilization interrupt flag
      \arg        RCU_INT_FLAG_IRC8MSTB: IRC8M stabilization interrupt flag
      \arg        RCU_INT_FLAG_HXTALSTB: HXTAL stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLLSTB: PLL stabilization interrupt flag
      \arg        RCU_INT_FLAG_CKM: HXTAL clock stuck interrupt flag
      \arg        RCU_INT_FLAG_LCKM: LXTAL clock stuck interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag)
{
    /* get the rcu interrupt flag */
    if(RESET != (RCU_REG_VAL(int_flag) & BIT(RCU_BIT_POS(int_flag)))) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear the interrupt flags
    \param[in]  int_flag: clock stabilization and stuck interrupt flags clear, refer to rcu_int_flag_clear_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_IRC32KSTB_CLR: IRC32K stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_LXTALSTB_CLR: LXTAL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_IRC8MSTB_CLR: IRC8M stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_HXTALSTB_CLR: HXTAL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLLSTB_CLR: PLL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_CKM_CLR: clock stuck interrupt flag clear
      \arg        RCU_INT_FLAG_LCKM_CLR: LXTAL clock stuck interrupt flag clear
    \param[out] none
    \retval     none
*/
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag)
{
    RCU_REG_VAL(int_flag) |= BIT(RCU_BIT_POS(int_flag));
}
