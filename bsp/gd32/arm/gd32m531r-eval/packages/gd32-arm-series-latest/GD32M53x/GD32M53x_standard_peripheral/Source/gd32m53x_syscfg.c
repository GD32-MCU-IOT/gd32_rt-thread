/*!
    \file    gd32m53x_syscfg.c
    \brief   SYSCFG driver

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

#include "gd32m53x_syscfg.h"

/* EXTI source select mask bits definition */
#define EXTI_SS_MASK            BITS(0,3)
/* ADCSMx(x=1,2) select mask bits definition */
#define ADCSMSEL_MASK           BITS(0,3)
/* TIMER input select mask bits definition */
#define TIMER_IS_MASK           BITS(0,3)
/* ECC error address bit offset */
#define ECCEADDR_OFFSET         ((uint32_t)19U)
/* ECC single-bit error bit offset */
#define ECCSEBIT_OFFSET         ((uint32_t)10U)
/* lockup mask bits definition */
#define LOCKUP_MASK             BITS(0,6)
/* SRAM remap size mask bits definition */
#define SRAM_REMAP_SIZE_MASK    (0x00000003U)
/* wp reg mask bits definition */
#define WP_REG_MASK             (0x0000000BU)
/* ADCSM mask bits definition */
#define ADCSM_MASK              (0x00008080U)
/* get INT_FLAG mask bits definition */
#define INT_FLAG_GET_MASK       (0x3C0001FFU)
/* clear INT_FLAG mask bits definition */
#define INT_FLAG_CLEAR_MASK     (0x200001FFU)

/*!
    \brief      reset the SYSCFG registers (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_deinit(void)
{
    rcu_periph_reset_enable(RCU_SYSCFGRST);
    rcu_periph_reset_disable(RCU_SYSCFGRST);
}

/*!
    \brief      enable I2C fast mode plus (API_ID(0x0002U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_enable(void)
{
    SYSCFG_CFG1 |= SYSCFG_CFG1_I2CFMPEN;
}

/*!
    \brief      disable I2C fast mode plus (API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_disable(void)
{
    SYSCFG_CFG1 &= ~SYSCFG_CFG1_I2CFMPEN;
}

/*!
    \brief      configure the GPIO pin as EXTI Line (API_ID(0x0004U))
    \param[in]  exti_gpio: specify the GPIO port and PIN used in EXTI
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_EXTI0_PA8   : EXTI0 PA8
      \arg        EXTI_SOURCE_EXTI0_PC10  : EXTI0 PC10
      \arg        EXTI_SOURCE_EXTI0_PN2   : EXTI0 PN2
      \arg        EXTI_SOURCE_EXTI0_PC8   : EXTI0 PC8
      \arg        EXTI_SOURCE_EXTI1_PA9   : EXTI1 PA9
      \arg        EXTI_SOURCE_EXTI1_PC11  : EXTI1 PC11
      \arg        EXTI_SOURCE_EXTI1_PE13  : EXTI1 PE13
      \arg        EXTI_SOURCE_EXTI1_PC9   : EXTI1 PC9
      \arg        EXTI_SOURCE_EXTI2_PA0   : EXTI2 PA0
      \arg        EXTI_SOURCE_EXTI2_PC12  : EXTI2 PC12
      \arg        EXTI_SOURCE_EXTI2_PF14  : EXTI2 PF14
      \arg        EXTI_SOURCE_EXTI2_PG12  : EXTI2 PG12
      \arg        EXTI_SOURCE_EXTI3_PF12  : EXTI3 PF12
      \arg        EXTI_SOURCE_EXTI4_PA1   : EXTI4 PA1
      \arg        EXTI_SOURCE_EXTI4_PE14  : EXTI4 PE14
      \arg        EXTI_SOURCE_EXTI4_PF9   : EXTI4 PF9
      \arg        EXTI_SOURCE_EXTI4_PF13  : EXTI4 PF13
      \arg        EXTI_SOURCE_EXTI5_PD8   : EXTI5 PD8
      \arg        EXTI_SOURCE_EXTI5_PG14  : EXTI5 PG14
      \arg        EXTI_SOURCE_EXTI5_PN7   : EXTI5 PN7
      \arg        EXTI_SOURCE_EXTI6_PB1   : EXTI6 PB1
      \arg        EXTI_SOURCE_EXTI6_PC6   : EXTI6 PC6
      \arg        EXTI_SOURCE_EXTI6_PD2   : EXTI6 PD2
      \arg        EXTI_SOURCE_EXTI6_PG13  : EXTI6 PG13
      \arg        EXTI_SOURCE_EXTI7_PB0   : EXTI7 PB0
      \arg        EXTI_SOURCE_EXTI7_PC7   : EXTI7 PC7
      \arg        EXTI_SOURCE_EXTI7_PN5   : EXTI7 PN5
      \arg        EXTI_SOURCE_EXTI8_PD4   : EXTI8 PD4
      \arg        EXTI_SOURCE_EXTI8_PE8   : EXTI8 PE8
      \arg        EXTI_SOURCE_EXTI8_PF8   : EXTI8 PF8
      \arg        EXTI_SOURCE_EXTI8_PG15  : EXTI8 PG15
      \arg        EXTI_SOURCE_EXTI9_PD5   : EXTI9 PD5
      \arg        EXTI_SOURCE_EXTI9_PD9   : EXTI9 PD9
      \arg        EXTI_SOURCE_EXTI9_PE9   : EXTI9 PE9
      \arg        EXTI_SOURCE_EXTI9_PF11  : EXTI9 PF11
      \arg        EXTI_SOURCE_EXTI10_PB2  : EXTI10 PB2
      \arg        EXTI_SOURCE_EXTI10_PC0  : EXTI10 PC0
      \arg        EXTI_SOURCE_EXTI10_PD10 : EXTI10 PD10
      \arg        EXTI_SOURCE_EXTI10_PE10 : EXTI10 PE10
      \arg        EXTI_SOURCE_EXTI10_PF10 : EXTI10 PF10
      \arg        EXTI_SOURCE_EXTI11_PC1  : EXTI11 PC1
      \arg        EXTI_SOURCE_EXTI11_PD11 : EXTI11 PD11
      \arg        EXTI_SOURCE_EXTI11_PG11 : EXTI11 PG11
      \arg        EXTI_SOURCE_EXTI12_PC2  : EXTI12 PC2
      \arg        EXTI_SOURCE_EXTI12_PD12 : EXTI12 PD12
      \arg        EXTI_SOURCE_EXTI12_PE12 : EXTI12 PE12
      \arg        EXTI_SOURCE_EXTI13_PC3  : EXTI13 PC3
      \arg        EXTI_SOURCE_EXTI13_PD13 : EXTI13 PD13
      \arg        EXTI_SOURCE_EXTI14_PB14 : EXTI14 PB14
      \arg        EXTI_SOURCE_EXTI14_PC4  : EXTI14 PC4
      \arg        EXTI_SOURCE_EXTI14_PD14 : EXTI14 PD14
      \arg        EXTI_SOURCE_EXTI14_PE11 : EXTI14 PE11
      \arg        EXTI_SOURCE_EXTI15_PB15 : EXTI15 PB15
      \arg        EXTI_SOURCE_EXTI15_PC5  : EXTI15 PC5
    \param[out] none
    \retval     none
*/
void syscfg_exti_line_config(exti_gpio_enum exti_gpio)
{
    uint32_t clear_exti_mask = ~(uint32_t)(EXTI_SS_MASK << (SYSCFG_BIT_POS(exti_gpio)));
    uint32_t config_exti_mask = (uint32_t)(SYSCFG_VALUE(exti_gpio) << SYSCFG_BIT_POS(exti_gpio));

    /* clear EXTI source line */
    SYSCFG_REG_VAL(exti_gpio) &= clear_exti_mask;
    /* configure EXTI source line */
    SYSCFG_REG_VAL(exti_gpio) |= config_exti_mask;
}

/*!
    \brief      select timer channel input source (API_ID(0x0005U))
    \param[in]  timer_input:Timer channel input select, refer to timer_channel_input_enum
    \param[out] none
    \retval     none
*/
void syscfg_timer_input_source_select(timer_channel_input_enum timer_input)
{
    uint32_t clear_timer_mask = ~((uint32_t)TIMER_IS_MASK << (SYSCFG_BIT_POS(timer_input)));
    uint32_t config_timer_mask = (SYSCFG_VALUE(timer_input) << SYSCFG_BIT_POS(timer_input));

    /* clear Timer channel input select */
    SYSCFG_REG_VAL(timer_input) &= clear_timer_mask;
    /* config Timer channel input */
    SYSCFG_REG_VAL(timer_input) |= config_timer_mask;
}

/*!
    \brief      enable module lockup function (function can be disabled by system reset) (API_ID(0x0006U))
    \param[in]  lockup:
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_LOCKUP_LOCKUP : CPU lockup (Hardfault) output enable
      \arg        SYSCFG_LVD_LOCKUP    : Low voltage detector lock
      \arg        SYSCFG_SRAM_LOCKUP   : SRAM ECC multi-bit error lock
      \arg        SYSCFG_CANRX_LOCK    : CAN receive FIFO ECC multi-bit error lock
      \arg        SYSCFG_CANFILTER_LOCK: CAN filter ECC multi-bit error lock
      \arg        SYSCFG_FLASHSRAM_LOCK: Flash SRAM ECC multi-bit error lock
      \arg        SYSCFG_FLASH_LOCKUP  : Flash ECC multi-bit error lock
    \param[out] none
    \retval     none
*/
void syscfg_lockup_enable(uint32_t lockup)
{
    SYSCFG_CFG5 |= (lockup & LOCKUP_MASK);
}

/*!
    \brief      set SRAM remap size (API_ID(0x0007U))
    \param[in]  size:
                only one parameter can be selected which is shown as below:
      \arg        SRAM_REMAP_SIZE_0KB: SRAM Remap 0KB to 0x10000000
      \arg        SRAM_REMAP_SIZE_8KB: SRAM Remap 8KB to 0x10000000
      \arg        SRAM_REMAP_SIZE_16KB: SRAM Remap 16KB to 0x10000000
      \arg        SRAM_REMAP_SIZE_32KB: SRAM Remap 32KB to 0x10000000
    \param[out] none
    \retval     none
*/
void syscfg_sram_remap_set(uint32_t size)
{
    SYSCFG_SRAMCFG &= ~SYSCFG_SRAMCFG_SRAM_REMAP_SEL;
    SYSCFG_SRAMCFG |= (size & SRAM_REMAP_SIZE_MASK);
}

/*!
    \brief      get SRAM remap size (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     SRAM size
      \arg        SRAM_REMAP_SIZE_0KB: SRAM Remap 0KB to 0x10000000
      \arg        SRAM_REMAP_SIZE_8KB: SRAM Remap 8KB to 0x10000000
      \arg        SRAM_REMAP_SIZE_16KB: SRAM Remap 16KB to 0x10000000
      \arg        SRAM_REMAP_SIZE_32KB: SRAM Remap 32KB to 0x10000000
*/
uint32_t syscfg_sram_remap_size_get(void)
{
    return (SYSCFG_SRAMCFG & SYSCFG_SRAMCFG_SRAM_REMAP_SEL);
}

/*!
    \brief      set CK_CMP selection (API_ID(0x0009U))
    \param[in]  sel: CK_CMP selection
                only one parameter can be selected which is shown as below:
      \arg        CK_CMP_DIV2: CK_CMP=fPCLK/2
      \arg        CK_CMP_DIV4: CK_CMP=fPCLK/4
    \param[out] none
    \retval     none
*/
void syscfg_ck_cmp_sel_set(ck_cmp_sel_enum sel)
{
    if(sel == CK_CMP_DIV2) {
        SYSCFG_CFG6 &= ~SYSCFG_CFG6_CK_CMP_SEL;
    } else {
        SYSCFG_CFG6 |= SYSCFG_CFG6_CK_CMP_SEL;
    }
}

/*!
    \brief      get CK_CMP selection (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     ck_cmp_sel_enum: CK_CMP selection
*/
ck_cmp_sel_enum syscfg_ck_cmp_sel_get(void)
{
    ck_cmp_sel_enum sel;
    if(0U != (SYSCFG_CFG6 & SYSCFG_CFG6_CK_CMP_SEL)) {
        sel = CK_CMP_DIV4;
    } else {
        sel = CK_CMP_DIV2;
    }
    return sel;
}

/*!
    \brief      enable register write function (API_ID(0x000BU))
    \param[in]  wp_reg: protected register
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_WRITE_PROTECTION_REG0: RCU_CTL, RCU_CFG0, RCU_INT, RCU_CFG1, RCU_CFG2
      \arg        SYSCFG_WRITE_PROTECTION_REG1: RCU_APB1RST, RCU_APB2RST, RCU_AHBEN, RCU_APB1EN, RCU_APB2EN, RCU_RSTSCK, RCU_AHBRST
      \arg        SYSCFG_WRITE_PROTECTION_REG2: PMU_LVD1CTL, PMU_LVD2CTL
    \param[out] none
    \retval     none
*/
void syscfg_register_write_enable(uint32_t wp_reg)
{
    uint32_t reg;
    reg = (SYSCFG_PRCFG & WP_REG_MASK);
    reg |= (wp_reg & WP_REG_MASK);
    SYSCFG_PRCFG = SYSCFG_WRITE_PROTECTION_KEY | reg;
}

/*!
    \brief      disable register write function (API_ID(0x000CU))
    \param[in]  wp_reg: protected register
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_WRITE_PROTECTION_REG0: RCU_CTL, RCU_CFG0, RCU_INT, RCU_CFG1, RCU_CFG2
      \arg        SYSCFG_WRITE_PROTECTION_REG1: RCU_APB1RST, RCU_APB2RST, RCU_AHBEN, RCU_APB1EN, RCU_APB2EN, RCU_RSTSCK, RCU_AHBRST
      \arg        SYSCFG_WRITE_PROTECTION_REG2: PMU_LVD1CTL, PMU_LVD2CTL
    \param[out] none
    \retval     none
*/
void syscfg_register_write_disable(uint32_t wp_reg)
{
    uint32_t reg;
    reg = (SYSCFG_PRCFG & WP_REG_MASK);
    reg &= ~(wp_reg & WP_REG_MASK);
    SYSCFG_PRCFG = SYSCFG_WRITE_PROTECTION_KEY | reg;
}

/*!
    \brief      Select the ADC trigger source connected to ADCSMx(x=1,2) pin (API_ID(0x000DU))
    \param[in]  timer_signal:
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_ADCSM1_TIMER0_TRGOF  :ADCSM1 Source of monitor is TIMER0_TRGOF
      \arg        SYSCFG_ADCSM1_TIMER0_TRGUF  :ADCSM1 Source of monitor is TIMER0_TRGUF
      \arg        SYSCFG_ADCSM1_TIMER0_TRGA   :ADCSM1 Source of monitor is TIMER0_TRGA
      \arg        SYSCFG_ADCSM1_TIMER0_TRGB   :ADCSM1 Source of monitor is TIMER0_TRGB
      \arg        SYSCFG_ADCSM1_TIMER0_TRGAB  :ADCSM1 Source of monitor is TIMER0_TRGAB
      \arg        SYSCFG_ADCSM1_TIMER7_TRGOF  :ADCSM1 Source of monitor is TIMER7_TRGOF
      \arg        SYSCFG_ADCSM1_TIMER7_TRGUF  :ADCSM1 Source of monitor is TIMER7_TRGUF
      \arg        SYSCFG_ADCSM1_TIMER7_TRGA   :ADCSM1 Source of monitor is TIMER7_TRGA
      \arg        SYSCFG_ADCSM1_TIMER7_TRGB   :ADCSM1 Source of monitor is TIMER7_TRGB
      \arg        SYSCFG_ADCSM1_TIMER7_TRGAB  :ADCSM1 Source of monitor is TIMER7_TRGAB
      \arg        SYSCFG_ADCSM2_TIMER0_TRGOF  :ADCSM2 Source of monitor is TIMER0_TRGOF
      \arg        SYSCFG_ADCSM2_TIMER0_TRGUF  :ADCSM2 Source of monitor is TIMER0_TRGUF
      \arg        SYSCFG_ADCSM2_TIMER0_TRGA   :ADCSM2 Source of monitor is TIMER0_TRGA
      \arg        SYSCFG_ADCSM2_TIMER0_TRGB   :ADCSM2 Source of monitor is TIMER0_TRGB
      \arg        SYSCFG_ADCSM2_TIMER0_TRGAB  :ADCSM2 Source of monitor is TIMER0_TRGAB
      \arg        SYSCFG_ADCSM2_TIMER7_TRGOF  :ADCSM2 Source of monitor is TIMER7_TRGOF
      \arg        SYSCFG_ADCSM2_TIMER7_TRGUF  :ADCSM2 Source of monitor is TIMER7_TRGUF
      \arg        SYSCFG_ADCSM2_TIMER7_TRGA   :ADCSM2 Source of monitor is TIMER7_TRGA
      \arg        SYSCFG_ADCSM2_TIMER7_TRGB   :ADCSM2 Source of monitor is TIMER7_TRGB
      \arg        SYSCFG_ADCSM2_TIMER7_TRGAB  :ADCSM2 Source of monitor is TIMER7_TRGAB

    \param[out] none
    \retval     none
*/
void syscfg_adc_signal_monitor_select(syscfg_adcsm_enum timer_signal)
{
    /* clear the bits */
    SYSCFG_REG_VAL(timer_signal) &= ~(ADCSMSEL_MASK << SYSCFG_BIT_POS(timer_signal));
    /* set the value */
    SYSCFG_REG_VAL(timer_signal) |= (SYSCFG_VALUE(timer_signal) << SYSCFG_BIT_POS(timer_signal));
}

/*!
    \brief      enable ADC signal monitor output (API_ID(0x000EU))
    \param[in]  adcsm: ADC signal monitor
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_TADSRCFG_ADCSM1: ADC SM1 pin output
      \arg        SYSCFG_TADSRCFG_ADCSM2: ADC SM2 pin output
\param[out] none
    \retval     none
*/
void syscfg_adc_signal_monitor_output_enable(uint32_t adcsm)
{
    SYSCFG_TADSRCFG |= (adcsm & ADCSM_MASK);
}

/*!
    \brief      disable ADC signal monitor output (API_ID(0x000FU))
    \param[in]  adcsm: ADC signal monitor
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_TADSRCFG_ADCSM1: ADC SM1 pin output
      \arg        SYSCFG_TADSRCFG_ADCSM2: ADC SM2 pin output
    \param[out] none
    \retval     none
*/
void syscfg_adc_signal_monitor_output_disable(uint32_t adcsm)
{
    SYSCFG_TADSRCFG &= ~(adcsm & ADCSM_MASK);
}

/*!
    \brief      get boot mode (API_ID(0x0010U))
    \param[in]  none
    \param[out] none
    \retval     uint32_t: boot mode
                    SYSCFG_BOOT_SYSTEM_MEMORY: Boot from the system memory
                    SYSCFG_BOOT_MAIN_FLASH   : Boot from the main flash
*/
uint32_t syscfg_boot_mode_get(void)
{
    uint32_t boot_mode;
    if((SYSCFG_CFG0 & SYSCFG_CFG0_BOOT_MODE) == SYSCFG_BOOT_MAIN_FLASH) {
        boot_mode = SYSCFG_BOOT_MAIN_FLASH;
    } else {
        boot_mode = SYSCFG_BOOT_SYSTEM_MEMORY;
    }
    return boot_mode;
}

/*!
    \brief      get sram ecc error address (API_ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     uint32_t: 0-0x1FFF
                SRAM error address
*/
uint32_t syscfg_sram_ecc_error_address_get(void)
{
    return ((SYSCFG_CFG2 & SYSCFG_CFG2_ECCEADDR) >> ECCEADDR_OFFSET);
}

/*!
    \brief      get sram ecc single-bit correction error bit (API_ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     uint8_t: 0-31
                the error bit which one bit has an ECC single-bit correction error
*/
uint8_t syscfg_sram_ecc_error_bit_get(void)
{
    return (uint8_t)((SYSCFG_CFG2 & SYSCFG_CFG2_ECCSEBIT) >> ECCSEBIT_OFFSET);
}

/*!
    \brief      enable the syscfg peripherals interrupt (API_ID(0x0013U))
    \param[in]  interrupt: SYSCFG peripherals, refer to syscfg_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_INT_ECC_ME0: SRAM multi-bit non-correction interrupt enable
      \arg        SYSCFG_INT_ECC_SE0: SRAM single-bit correction interrupt enable
      \arg        SYSCFG_INT_ECC_ME1: CAN receive FIFO multi-bit non-correction interrupt enable
      \arg        SYSCFG_INT_ECC_SE1: CAN receive FIFO single-bit correction interrupt enable
      \arg        SYSCFG_INT_ECC_ME2: CAN filter SRAM multi-bit non-correction interrupt enable
      \arg        SYSCFG_INT_ECC_SE2: CAN filter SRAM single-bit correction interrupt enable
      \arg        SYSCFG_INT_ECC_ME3: Flash SRAM multi-bit non-correction interrupt enable
      \arg        SYSCFG_INT_ECC_SE3: Flash SRAM single-bit correction interrupt enable
      \arg        SYSCFG_INT_ECC_ME4: Flash multi-bit non-correction interrupt enable
      \arg        SYSCFG_INT_NMI_HXTAL: HXTAL clock monitor NMI interrupt enable
      \arg        SYSCFG_INT_NMI_PIN  : NMI pin interrupt enable
      \arg        SYSCFG_INT_NMI_WWDGT: WWDGT NMI interrupt enable
      \arg        SYSCFG_INT_NMI_FWDGT: FWDGT NMI interrupt enable
      \arg        SYSCFG_INT_NMI_LVD2 : LVD2 NMI interrupt enable
      \arg        SYSCFG_INT_NMI_LVD1 : LVD1 NMI interrupt enable
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_enable(syscfg_interrupt_enum interrupt)
{
    SYSCFG_REG_VAL(interrupt) |= BIT(SYSCFG_BIT_POS(interrupt));
}

/*!
    \brief      disable the syscfg peripherals interrupt (API_ID(0x0014U))
    \param[in]  interrupt: SYSCFG peripherals, refer to syscfg_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_INT_ECC_ME0: SRAM multi-bit non-correction interrupt enable
      \arg        SYSCFG_INT_ECC_SE0: SRAM single-bit correction interrupt enable
      \arg        SYSCFG_INT_ECC_ME1: CAN receive FIFO multi-bit non-correction interrupt enable
      \arg        SYSCFG_INT_ECC_SE1: CAN receive FIFO single-bit correction interrupt enable
      \arg        SYSCFG_INT_ECC_ME2: CAN filter SRAM multi-bit non-correction interrupt enable
      \arg        SYSCFG_INT_ECC_SE2: CAN filter SRAM single-bit correction interrupt enable
      \arg        SYSCFG_INT_ECC_ME3: Flash SRAM multi-bit non-correction interrupt enable
      \arg        SYSCFG_INT_ECC_SE3: Flash SRAM single-bit correction interrupt enable
      \arg        SYSCFG_INT_ECC_ME4: Flash multi-bit non-correction interrupt enable
      \arg        SYSCFG_INT_NMI_HXTAL: HXTAL clock monitor NMI interrupt enable
      \arg        SYSCFG_INT_NMI_PIN  : NMI pin interrupt enable
      \arg        SYSCFG_INT_NMI_WWDGT: WWDGT NMI interrupt enable
      \arg        SYSCFG_INT_NMI_FWDGT: FWDGT NMI interrupt enable
      \arg        SYSCFG_INT_NMI_LVD2 : LVD2 NMI interrupt enable
      \arg        SYSCFG_INT_NMI_LVD1 : LVD1 NMI interrupt enable
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_disable(syscfg_interrupt_enum interrupt)
{
    SYSCFG_REG_VAL(interrupt) &= ~BIT(SYSCFG_BIT_POS(interrupt));
}

/*!
    \brief      get the interrupt flags (API_ID(0x0015U))
    \param[in]  int_flag: interrupt flags
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_INT_FLAG_ECC_ME0  :SRAM multi-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_SE0  :SRAM single-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_ME1  :CAN FIFO SRAM multi-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_SE1  :CAN FIFO SRAM single-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_ME2  :CAN filter SRAM multi-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_SE2  :CAN filter SRAM single-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_ME3  :Flash SRAM multi-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_SE3  :Flash SRAM single-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_ME4  :Flash multi-bit error flag
      \arg        SYSCFG_INT_FLAG_NMI_HXTAL:HXTAL clock monitor NMI interrupt flag
      \arg        SYSCFG_INT_FLAG_NMI_PIN  :NMI pin interrupt flag
      \arg        SYSCFG_INT_FLAG_NMI_WWDGT:WWDGT NMI interrupt flag
      \arg        SYSCFG_INT_FLAG_NMI_FWDGT:FWDGT NMI interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_interrupt_flag_get(uint32_t int_flag)
{
    FlagStatus reval;
    /* get the interrupt flag */
    if(0U != (SYSCFG_STAT & (int_flag & INT_FLAG_GET_MASK))) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear the interrupt flags (API_ID(0x0016U))
    \param[in]  int_flag: interrupt flags
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_INT_FLAG_ECC_ME0  :SRAM multi-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_SE0  :SRAM single-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_ME1  :CAN FIFO SRAM multi-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_SE1  :CAN FIFO SRAM single-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_ME2  :CAN filter SRAM multi-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_SE2  :CAN filter SRAM single-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_ME3  :Flash SRAM multi-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_SE3  :Flash SRAM single-bit error flag
      \arg        SYSCFG_INT_FLAG_ECC_ME4  :Flash multi-bit error flag
      \arg        SYSCFG_INT_FLAG_NMI_FWDGT:FWDGT NMI interrupt flag
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_flag_clear(uint32_t int_flag)
{
    SYSCFG_STAT = (int_flag & INT_FLAG_CLEAR_MASK);
}
