/*!
    \file    gd32g5x3_syscfg.c
    \brief   SYSCFG driver

    \version 2025-02-10, V1.1.0, firmware for GD32G5x3
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.
    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission

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

#include "gd32g5x3_syscfg.h"
/*!
    \brief      reset the SYSCFG registers
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
    \brief      enable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9)
    \param[in]  i2c_fmp_enable
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_I2C0_FMP: I2C0 fast mode plus
      \arg        SYSCFG_I2C1_FMP: I2C1 fast mode plus
      \arg        SYSCFG_I2C2_FMP: I2C2 fast mode plus
      \arg        SYSCFG_I2C3_FMP: I2C3 fast mode plus
      \arg        SYSCFG_I2C_FMP_PB6: I2C fast mode plus on PB6 pin
      \arg        SYSCFG_I2C_FMP_PB7: I2C fast mode plus on PB7 pin
      \arg        SYSCFG_I2C_FMP_PB8: I2C fast mode plus on PB8 pin
      \arg        SYSCFG_I2C_FMP_PB9: I2C fast mode plus on PB9 pin
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_enable(uint32_t i2c_fmp_enable)
{
    SYSCFG_CFG1 |= i2c_fmp_enable;
}

/*!
    \brief      disable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9)
    \param[in]  i2c_fmp_disable
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_I2C0_FMP: I2C0 fast mode plus
      \arg        SYSCFG_I2C1_FMP: I2C1 fast mode plus
      \arg        SYSCFG_I2C2_FMP: I2C2 fast mode plus
      \arg        SYSCFG_I2C3_FMP: I2C3 fast mode plus
      \arg        SYSCFG_I2C_FMP_PB6: I2C fast mode plus on PB6 pin
      \arg        SYSCFG_I2C_FMP_PB7: I2C fast mode plus on PB7 pin
      \arg        SYSCFG_I2C_FMP_PB8: I2C fast mode plus on PB8 pin
      \arg        SYSCFG_I2C_FMP_PB9: I2C fast mode plus on PB9 pin
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_disable(uint32_t i2c_fmp_disable)
{
    SYSCFG_CFG1 &= (uint32_t)(~i2c_fmp_disable);
}

/*!
    \brief      configure the GPIO pin as EXTI Line
    \param[in]  exti_port: specify the GPIO port used in EXTI
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_GPIOx(x = A,B,C,D,E,F,G): EXTI GPIO port
    \param[in]  exti_pin: specify the EXTI line
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_PINx(GPIOA x = 0..15,GPIOB x = 0..15,GPIOC x = 0..15,GPIOD x = 0..15,GPIOE x = 0..15,
                  GPIOF x = 0..15,GPIOG x = 0..10): EXTI GPIO pin
    \param[out] none
    \retval     none
*/
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin)
{
    uint32_t clear_exti_mask = ~((uint32_t)EXTI_SS_MASK << (EXTI_SS_MSTEP(exti_pin)));
    uint32_t config_exti_mask = ((uint32_t)exti_port) << (EXTI_SS_MSTEP(exti_pin));

    switch (exti_pin / EXTI_SS_JSTEP){
    case EXTISS0:
        /* clear EXTI source line(0..3) */
        SYSCFG_EXTISS0 &= clear_exti_mask;
        /* configure EXTI soure line(0..3) */
        SYSCFG_EXTISS0 |= config_exti_mask;
        break;
    case EXTISS1:
        /* clear EXTI soure line(4..7) */
        SYSCFG_EXTISS1 &= clear_exti_mask;
        /* configure EXTI soure line(4..7) */
        SYSCFG_EXTISS1 |= config_exti_mask;
        break;
    case EXTISS2:
        /* clear EXTI soure line(8..11) */
        SYSCFG_EXTISS2 &= clear_exti_mask;
        /* configure EXTI soure line(8..11) */
        SYSCFG_EXTISS2 |= config_exti_mask;
        break;
    case EXTISS3:
        /* clear EXTI soure line(12..15) */
        SYSCFG_EXTISS3 &= clear_exti_mask;
        /* configure EXTI soure line(12..15) */
        SYSCFG_EXTISS3 |= config_exti_mask;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure GPIO reset mode
    \param[in]  pinmode:
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_PIN_NRST: GPIO pin configuration will retain state across any reset event except for the POR event
      \arg        SYSCFG_PIN_RST: GPIO pin configuration is reset when any reset event occurs 
    \param[out] none
    \retval     none
*/
void syscfg_pin_reset_mode_config(uint32_t syscfg_pin_reset_mode)
{
    uint32_t reg;
    
    reg = SYSCFG_CFG2;
    reg &= ~SYSCFG_CFG2_PIN_RSTMD;
    SYSCFG_CFG2 = (reg | syscfg_pin_reset_mode);
}

/*!
    \brief      configure Trigsel cla reset mode
    \param[in]  pinmode:
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_TRGSEL_CLA_NRST: Trigsel CLA configuration will retain state across any reset event except for the POR event
      \arg        SYSCFG_TRGSEL_CLA_RST: Trigsel CLA configuration is reset when any reset event occurs 
    \param[out] none
    \retval     none
*/
void syscfg_trigsel_cla_reset_mode_config(uint32_t syscfg_trgsel_reset_mode)
{
    uint32_t reg;
    
    reg = SYSCFG_CFG2;
    reg &= ~SYSCFG_CFG2_TRGSEL_RSTMD;
    SYSCFG_CFG2 = (reg | syscfg_trgsel_reset_mode);
}

/*!
    \brief      enable module lockup function (function can be disabled by system reset)
    \param[in]  lockup:
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_LOCKUP_LOCKUP: CPU lockup signal
      \arg        SYSCFG_SRAM0_LOCKUP: SRAM0 ECC double error signal
      \arg        SYSCFG_LVD_LOCKUP: LVD signal
      \arg        SYSCFG_FLASH_LOCKUP: Flash ECC double error signal
      \arg        SYSCFG_SRAM1_LOCKUP: SRAM1 ECC double error signal
      \arg        SYSCFG_TCMSRAM_LOCKUP: TCMSRAM ECC double error signal
    \param[out] none
    \retval     none
*/
void syscfg_lockup_enable(uint32_t lockup)
{
    SYSCFG_CFG2 |= lockup;
}

/*!
    \brief      select timer channel input source
    \param[in]  timer_input:Timer channel input select, refer to timer_channel_input_enum
    \param[out] none
    \retval     none
*/
void syscfg_timer_input_source_select(timer_channel_input_enum timer_input)
{
    uint32_t clear_timer_mask = ~((uint32_t)TIMER_IS_MASK << (TIMER_BIT_POS(timer_input)));
    uint32_t config_timer_mask = (TIMER_SEL_VAL(timer_input) << TIMER_BIT_POS(timer_input));
    
    switch(TIMER_REG_INDEX(timer_input)){
    case TIMERCISEL0:
        /* clear Timer channel input select */
        SYSCFG_TIMERCISEL0 &= clear_timer_mask;
        /* config Timer channel input */
        SYSCFG_TIMERCISEL0 |= config_timer_mask;
        break;
    case TIMERCISEL1:
        /* clear Timer channel input select */
        SYSCFG_TIMERCISEL1 &= clear_timer_mask;
        /* config Timer channel input */
        SYSCFG_TIMERCISEL1 |= config_timer_mask;
        break;
    case TIMERCISEL2:
        /* clear Timer channel input select */
        SYSCFG_TIMERCISEL2 &= clear_timer_mask;
        /* config Timer channel input */
        SYSCFG_TIMERCISEL2 |= config_timer_mask;
        break;
    case TIMERCISEL3:
        /* clear Timer channel input select */
        SYSCFG_TIMERCISEL3 &= clear_timer_mask;
        /* config Timer channel input */
        SYSCFG_TIMERCISEL3 |= config_timer_mask;
        break;
    case TIMERCISEL4:
        /* clear Timer channel input select */
        SYSCFG_TIMERCISEL4 &= clear_timer_mask;
        /* config Timer channel input */
        SYSCFG_TIMERCISEL4 |= config_timer_mask;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable flash bank remap
    \param[in]  value:
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_FLASH_BANK0_MAPPED: Flash Bank 1 mapped at 0x08000000,and Flash Bank 0 mapped at 0x08040000(depend on the specific series of bank size)
      \arg        SYSCFG_FLASH_BANK1_MAPPED: Flash Bank 0 mapped at 0x08000000,and Flash Bank 1 mapped at 0x08040000(depend on the specific series of bank size)
      \param[out] none
    \retval     none
*/
void syscfg_flash_bank_remap_set(uint32_t value)
{
    SYSCFG_CFG0 &= ~SYSCFG_CFG0_FMC_SWP;
    SYSCFG_CFG0 |= value;
}

/*!
    \brief      select bootmode memory mapping
    \param[in]  mem_select:
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_MAIN_FLASH_MEMORY: Main Flash memory mapped at 0x00000000
      \arg        SYSCFG_SYSTEM_FLASH_MEMORY: System Flash memory mapped at 0x00000000
      \arg        SYSCFG_EXMC_MEMORY: EXMC memory mapped at 0x00000000
      \arg        SYSCFG_SRAM0_MEMORY: SRAM0 mapped at 0x00000000
      \arg        SYSCFG_QSPI_MEMORY: QSPI memory mapped at 0x00000000
    \param[out] none
    \retval     none
*/
void syscfg_bootmode_memmap_select(uint32_t mem_select)
{
    SYSCFG_CFG0 &= ~SYSCFG_CFG0_BOOT_MODE;
    SYSCFG_CFG0 |= mem_select;
}

/*!
    \brief      SRAM ECC single correctable bit get
    \param[in]  sram: sram error bits, refer to syscfg_sram_serrbits_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_SRAM0_SERRBITS: SRAM0 SRAM0 ECC single-bit correctable error bits
      \arg        SYSCFG_SRAM1_SERRBITS: SRAM1 ECC single-bit correctable error bits
      \arg        SYSCFG_TCMSRAM_SERRBITS: TCMSRAM ECC single-bit correctable error bits
    \param[out] none
    \retval     none
*/
uint32_t syscfg_sram_ecc_single_correctable_bit_get(syscfg_sram_serrbits_enum sram)
{
    uint32_t error_bits=(uint32_t)0;
    error_bits = (SYSCFG_REG_VAL(sram) >> SYSCFG_BIT_POS(sram)) & (uint32_t)0x3F;
    return error_bits;
}

/*!
    \brief      SRAM ECC error address get
    \param[in]  err_bits: sram error bits, refer to syscfg_sram_erraddr_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_SRAM0_ERR_ADDR: SRAM0 ECC error address
      \arg        SYSCFG_SRAM1_ERR_ADDR: SRAM1 ECC error address
      \arg        SYSCFG_TCMSRAM_ERR_ADDR: TCMSRAM ECC error address
    \param[out] none
    \retval     none
*/
uint32_t syscfg_sram_ecc_error_address_get(syscfg_sram_erraddr_enum sram)
{
    uint32_t addr = 0U;
    addr = SYSCFG_REG_VAL(sram) >> SYSCFG_BIT_POS(sram);
    return addr;
}

/*!
    \brief      erase tcmsram
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_tcmsram_erase(void)
{
    SYSCFG_TCMSRAMCS |= SYSCFG_TCMSRAMCS_TCMSRAMER;
}

/*!
    \brief      lock the TCMSRAM erase
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_tcmsram_erase_lock(void)
{
    SYSCFG_TCMSRAMKEY = WP_LOCK_KEY;
}

/*!
    \brief      unlock the TCMSRAM erase
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_tcmsram_erase_unlock(void)
{
    SYSCFG_TCMSRAMKEY = WP_UNLOCK_KEY0;
    SYSCFG_TCMSRAMKEY = WP_UNLOCK_KEY1;
}

/*!
    \brief      enable TCMSRAM page x write protection 
    \param[in]  pagex
                one or more parameters can be selected which is shown as below: 
      \arg          SYSCFG_TCMSRAM_WP_PAGEx (x = 0..31)
    \param[out] none
    \retval     none
*/
void syscfg_tcmsram_page_wp_enable(uint32_t pagex)
{
    SYSCFG_TCMSRAMWP |= pagex;
}

/*!
    \brief      configure the I/O compensation cell
    \param[in]  syscfg_cps: specifies the I/O compensation cell mode
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_IO_COMPENSATION_ENABLE: I/O compensation cell is enabled
      \arg        SYSCFG_IO_COMPENSATION_DISABLE: I/O compensation cell is disabled
    \param[out] none
    \retval     none
*/
void syscfg_io_compensation_config(uint32_t syscfg_cps)
{
    uint32_t reg;

    reg = SYSCFG_CPSCTL;
    /* reset the SYSCFG_CPSCTL_CPS_EN bit and set according to syscfg_compensation */
    reg &= ~SYSCFG_CPSCTL_CPS_EN;
    SYSCFG_CPSCTL = (reg | syscfg_cps);
}

/*!
    \brief      enable FPU interrupt 
    \param[in]  interrupt:
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_FPUINT_INVALID_OPERATION: Invalid operation interrupt enable
      \arg        SYSCFG_FPUINT_DIV0: Divide-by-zero interrupt enable
      \arg        SYSCFG_FPUINT_UNDERFLOW: Underflow interrupt enable
      \arg        SYSCFG_FPUINT_OVERFLOW: Overflow interrupt enable
      \arg        SYSCFG_FPUINT_INPUT_ABNORMAL: Input abnormal interrupt enable
      \arg        SYSCFG_FPUINT_INEXACT: Inexact interrupt enable
    \param[out] none
    \retval     none
*/
void syscfg_fpu_interrupt_enable(uint32_t interrupt)
{
    SYSCFG_CFG1 |= interrupt;
}

/*!
    \brief      disable FPU interrupt 
    \param[in]  interrupt:
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_FPUINT_INVALID_OPERATION: Invalid operation Interrupt disable
      \arg        SYSCFG_FPUINT_DIV0: Divide-by-zero interrupt disable
      \arg        SYSCFG_FPUINT_UNDERFLOW: Underflow interrupt disable
      \arg        SYSCFG_FPUINT_OVERFLOW: Overflow interrupt disable
      \arg        SYSCFG_FPUINT_INPUT_ABNORMAL: Input abnormal interrupt disable
      \arg        SYSCFG_FPUINT_INEXACT: Inexact interrupt disable
    \param[out] none
    \retval     none
*/
void syscfg_fpu_interrupt_disable(uint32_t interrupt)
{
    SYSCFG_CFG1 &= ~interrupt;
}

/*!
    \brief      get the interrupt flags
    \param[in]  int_flag: interrupt flags, refer to syscfg_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_INT_FLAG_SRAM0ECCME: SRAM0 ECC multi-bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_SRAM0ECCSE: SRAM0 ECC single bit correction event flag
      \arg        SYSCFG_INT_FLAG_FLASHECC: Flash ECC NMI interrupt flag
      \arg        SYSCFG_INT_FLAG_CKMNMI: HXTAL clock moniotor NMI interrupt flag
      \arg        SYSCFG_INT_FLAG_NMIPIN: NMI pin interrupt flag
      \arg        SYSCFG_INT_FLAG_SRAM1ECCME: SRAM1 ECC multi-bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_SRAM1ECCSE: SRAM1 ECC single bit correction event flag
      \arg        SYSCFG_INT_FLAG_TCMSRAMECCME: TCMSRAM ECC multi-bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_TCMSRAMECCSE: TCMSRAM ECC single bit correction event flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_interrupt_flag_get(syscfg_flag_enum int_flag)
{
    /* get the rcu interrupt flag */
    if(RESET != (SYSCFG_REG_VAL(int_flag) & BIT(SYSCFG_BIT_POS(int_flag)))) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear the interrupt flags
    \param[in]  int_flag: interrupt flags clear, refer to syscfg_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_INT_FLAG_SRAM0ECCME: SRAM0 ECC multi-bits non-correction event flag clear
      \arg        SYSCFG_INT_FLAG_SRAM0ECCSE: SRAM0 ECC single bit correction event flag clear
      \arg        SYSCFG_INT_FLAG_FLASHECC: Flash ECC NMI interrupt flag clear
      \arg        SYSCFG_INT_FLAG_CKMNMI: HXTAL clock monitor NMI interrupt flag clear
      \arg        SYSCFG_INT_FLAG_SRAM1ECCME: SRAM1 ECC multi-bits non-correction event flag clear
      \arg        SYSCFG_INT_FLAG_SRAM1ECCSE: SRAM1 ECC single bit correction event flag clear
      \arg        SYSCFG_INT_FLAG_TCMSRAMECCME: TCMSRAM ECC multi-bits non-correction event flag clear
      \arg        SYSCFG_INT_FLAG_TCMSRAMECCSE: TCMSRAM ECC single bit correction event flag clear
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_flag_clear(syscfg_flag_enum int_flag)
{
    SYSCFG_REG_VAL(int_flag) |= BIT(SYSCFG_BIT_POS(int_flag));
}

/*!
    \brief      enable the syscfg peripherals interrupt
    \param[in]  interrupt: SYSCFG peripherals, refer to syscfg_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_INT_SRAM0ECCME: SRAM0 ECC multi-bits non-correction event
      \arg        SYSCFG_INT_SRAM0ECCSE: SRAM0 ECC single bit correction event
      \arg        SYSCFG_INT_FLASHECC: Flash ECC NMI interrupt
      \arg        SYSCFG_INT_CKMNMI: HXTAL clock monitor NMI interrupt
      \arg        SYSCFG_INT_NMIPIN: NMI pin interrupt
      \arg        SYSCFG_INT_SRAM1ECCME: SRAM1 ECC multi-bits non-correction event
      \arg        SYSCFG_INT_SRAM1ECCSE: SRAM1 ECC single bit correction event
      \arg        SYSCFG_INT_TCMSRAMECCME: TCMSRAM ECC multi-bits non-correction event
      \arg        SYSCFG_INT_TCMSRAMECCSE: TCMSRAM ECC single bit correction event
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_enable(syscfg_interrupt_enum interrupt)
{
    SYSCFG_REG_VAL(interrupt) |= BIT(SYSCFG_BIT_POS(interrupt));
}

/*!
    \brief      disable the syscfg peripherals interrupt
    \param[in]  interrupt: SYSCFG peripherals, refer to syscfg_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_INT_SRAM0ECCME: SRAM0 ECC multi-bits non-correction event
      \arg        SYSCFG_INT_SRAM0ECCSE: SRAM0 ECC single bit correction event
      \arg        SYSCFG_INT_FLASHECC: Flash ECC NMI interrupt
      \arg        SYSCFG_INT_CKMNMI: HXTAL clock monitor NMI interrupt
      \arg        SYSCFG_INT_NMIPIN: NMI pin interrupt
      \arg        SYSCFG_INT_SRAM1ECCME: SRAM1 ECC multi-bits non-correction event
      \arg        SYSCFG_INT_SRAM1ECCSE: SRAM1 ECC single bit correction event
      \arg        SYSCFG_INT_TCMSRAMECCME: TCMSRAM ECC multi-bits non-correction event
      \arg        SYSCFG_INT_TCMSRAMECCSE: TCMSRAM ECC single bit correction event
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_disable(syscfg_interrupt_enum interrupt)
{
    SYSCFG_REG_VAL(interrupt) &= ~BIT(SYSCFG_BIT_POS(interrupt));
}

/*!
    \brief      get tcmsram erase busy flag
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: erase status
      \arg        SET: TCMSRAM erase operation is on going
      \arg        RESET: No TCMSRAM erase operation is on going
*/
FlagStatus syscfg_tcmsram_busy_flag_get(void)
{
    if(SYSCFG_TCMSRAMCS & SYSCFG_TCMSRAMCS_TCMSRAMBSY){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      get compensation cell ready flag
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: the status of compensation cell
      \arg        SET: the compensation cell is ready
      \arg        RESET: the compensation cell is not ready
*/
FlagStatus syscfg_compensation_cell_ready_flag_get(void)
{
    if(SYSCFG_CPSCTL & SYSCFG_CPSCTL_CPS_RDY){
        return SET;
    }else{
        return RESET;
    }
}
