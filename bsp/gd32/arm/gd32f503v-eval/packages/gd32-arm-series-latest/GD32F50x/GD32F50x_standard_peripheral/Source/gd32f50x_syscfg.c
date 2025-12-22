/*!
    \file    gd32f50x_syscfg.c
    \brief   SYSCFG driver

    \version 2025-11-03, V1.0.0, firmware for GD32F50x
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

#include "gd32f50x_syscfg.h"
#include "gd32f50x_rcu.h"

#define I2C_FMP_MASK     ((uint32_t)0x00000003U)                                                   /*!< I2C fast mode plus mask */
#define BUSTO_MASK       ((uint32_t)0x0000000FU)                                                   /*!< bus timeout mask */
#define BUSTOFLAG_MASK   ((uint32_t)0x0000000FU)                                                   /*!< bus timeout flag mask */
#define LOCKUP_MASK      ((uint32_t)0x00001044U)                                                   /*!< lockup mask */
#define FPU_INT_MASK     ((uint32_t)0x0000003FU)                                                   /*!< FPU interrupt mask */
#define SRAM_WP_MASK     ((uint32_t)0xFFFFFFFFU)                                                   /*!< SRAM write protection mask */
#define SRAM_ECC_MASK    ((uint32_t)0x00000018U)                                                   /*!< SRAM ECC mask */
#define ECC_FLAG_MASK    ((uint32_t)0x00000003U)                                                   /*!< ECC flag mask */

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
    \brief      get current boot mode (API_ID(0x0002U))
    \param[in]  none
    \param[out] none
    \retval     uint32_t: current boot mode
                only one value will be returned which is shown as below:
      \retval     SYSCFG_BOOTMODE_FLASH: boot from main flash
      \retval     SYSCFG_BOOTMODE_BOOTLOADER: boot from bootloader
      \retval     SYSCFG_BOOTMODE_SRAM: boot from embedded SRAM
      \retval     SYSCFG_BOOTMODE_OTP1: boot from embedded OTP1
*/
uint32_t syscfg_bootmode_get(void)
{
    return (SYSCFG_CFG0 & SYSCFG_CFG0_BOOT_MODE);
}

/*!
    \brief      enable I2Cx Fast Mode Plus (API_ID(0x0003U))
    \param[in]  i2c_fmp: I2C fast mode plus
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_I2C0_FMP: I2C0 fast mode plus
      \arg        SYSCFG_I2C1_FMP: I2C1 fast mode plus
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_enable(uint32_t i2c_fmp)
{
    SYSCFG_CFG1 |= (i2c_fmp & I2C_FMP_MASK);
}

/*!
    \brief      disable I2Cx Fast Mode Plus (API_ID(0x0004U))
    \param[in]  i2c_fmp: I2C fast mode plus
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_I2C0_FMP: I2C0 fast mode plus
      \arg        SYSCFG_I2C1_FMP: I2C1 fast mode plus
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_disable(uint32_t i2c_fmp)
{
    SYSCFG_CFG1 &= ~(i2c_fmp & I2C_FMP_MASK);
}

/*!
    \brief      enable module lockup function (API_ID(0x0005U))
    \param[in]  lockup:
                one or more parameters can be selected which is shown as below:
      \arg        SYSCFG_CPU_LOCKUP: CPU lockup signal
      \arg        SYSCFG_SRAM_LOCKUP: SRAM ECC double error signal
      \arg        SYSCFG_LVD_LOCKUP: LVD signal connected
    \param[out] none
    \retval     none
*/
void syscfg_lockup_enable(uint32_t lockup)
{
    SYSCFG_LKCTL |= (lockup & LOCKUP_MASK);
}

/*!
    \brief      enable bus timeout (API_ID(0x0006U))
    \param[in]  busto: bus timeout
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_CPUCBUS_TIMEROUT: CPU Cbus timeout enable bit
      \arg        SYSCFG_CPUSBUS_TIMEROUT: CPU Sbus timeout enable bit
      \arg        SYSCFG_DMA0BUS_TIMEROUT: DMA0 bus timeout enable bit
      \arg        SYSCFG_DMA1BUS_TIMEROUT: DMA1 bus timeout enable bit
    \param[out] none
    \retval     none
*/
void syscfg_bus_timeout_enable(uint32_t busto)
{
    SYSCFG_BUSTO |= (busto & BUSTO_MASK);
}

/*!
    \brief      disable bus timeout (API_ID(0x0007U))
    \param[in]  busto: bus timeout
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_CPUCBUS_TIMEROUT: CPU Cbus timeout enable bit
      \arg        SYSCFG_CPUSBUS_TIMEROUT: CPU Sbus timeout enable bit
      \arg        SYSCFG_DMA0BUS_TIMEROUT: DMA0 bus timeout enable bit
      \arg        SYSCFG_DMA1BUS_TIMEROUT: DMA1 bus timeout enable bit
    \param[out] none
    \retval     none
*/
void syscfg_bus_timeout_disable(uint32_t busto)
{
    SYSCFG_BUSTO &= ~(busto & BUSTO_MASK);
}

/*!
    \brief      Select TIMER channel input source (API_ID(0x0008U))
    \param[in]  timer_input: TIMER channel input selection, refer to timer_channel_input_enum
                only one parameter can be selected which is shown as below:
      \arg        TIMER15_CI0_INPUT_TIMER15_CH0: TIMER15_CH0 input
      \arg        TIMER15_CI0_INPUT_IRC40K: IRC40K
      \arg        TIMER15_CI0_INPUT_LXTAL: LXTAL
      \arg        TIMER16_CI0_INPUT_TIMER16_CH0: TIMER16_CH0 input
      \arg        TIMER16_CI0_INPUT_CKOUT: CKOUT
    \param[out] none
    \retval     none
*/
void syscfg_timer_input_source_select(timer_channel_input_enum timer_input)
{
    uint32_t reg;
    uint32_t timer_id = TIMER_GET_ID(timer_input);
    uint32_t bit_pos = TIMER_GET_BITPOS(timer_input);
    uint32_t sel_value = TIMER_GET_VALUE(timer_input);
    
    reg = SYSCFG_TIMERCISEL;
    
    /* configure based on timer ID */
    if (TIMER15_ID == timer_id) {
        /* clear TIMER15_CI0 input source selection bits */
        reg &= ~SYSCFG_TIMERCISEL_TIMER15_CI0_SEL;
        /* set TIMER15_CI0 input source */
        reg |= (sel_value << bit_pos) & SYSCFG_TIMERCISEL_TIMER15_CI0_SEL;
        SYSCFG_TIMERCISEL = reg;
    } else if (TIMER16_ID == timer_id) {
        /* clear TIMER16_CI0 input source selection bits */
        reg &= ~SYSCFG_TIMERCISEL_TIMER16_CI0_SEL;
        /* set TIMER16_CI0 input source */
        reg |= (sel_value << bit_pos) & SYSCFG_TIMERCISEL_TIMER16_CI0_SEL;
        SYSCFG_TIMERCISEL = reg;
    } else {
        /* invalid timer ID, do nothing */
    }
}

/*!
    \brief      enable SRAM page write protection (API_ID(0x0009U))
    \param[in]  page: SRAM page
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_SRAM_WP_PAGE0: SRAM page 0 write protection
      \arg        SYSCFG_SRAM_WP_PAGE1: SRAM page 1 write protection
      \arg        SYSCFG_SRAM_WP_PAGE2: SRAM page 2 write protection
      \arg        SYSCFG_SRAM_WP_PAGE3: SRAM page 3 write protection
      \arg        SYSCFG_SRAM_WP_PAGE4: SRAM page 4 write protection
      \arg        SYSCFG_SRAM_WP_PAGE5: SRAM page 5 write protection
      \arg        SYSCFG_SRAM_WP_PAGE6: SRAM page 6 write protection
      \arg        SYSCFG_SRAM_WP_PAGE7: SRAM page 7 write protection
      \arg        SYSCFG_SRAM_WP_PAGE8: SRAM page 8 write protection
      \arg        SYSCFG_SRAM_WP_PAGE9: SRAM page 9 write protection
      \arg        SYSCFG_SRAM_WP_PAGE10: SRAM page 10 write protection
      \arg        SYSCFG_SRAM_WP_PAGE11: SRAM page 11 write protection
      \arg        SYSCFG_SRAM_WP_PAGE12: SRAM page 12 write protection
      \arg        SYSCFG_SRAM_WP_PAGE13: SRAM page 13 write protection
      \arg        SYSCFG_SRAM_WP_PAGE14: SRAM page 14 write protection
      \arg        SYSCFG_SRAM_WP_PAGE15: SRAM page 15 write protection
      \arg        SYSCFG_SRAM_WP_PAGE16: SRAM page 16 write protection
      \arg        SYSCFG_SRAM_WP_PAGE17: SRAM page 17 write protection
      \arg        SYSCFG_SRAM_WP_PAGE18: SRAM page 18 write protection
      \arg        SYSCFG_SRAM_WP_PAGE19: SRAM page 19 write protection
      \arg        SYSCFG_SRAM_WP_PAGE20: SRAM page 20 write protection
      \arg        SYSCFG_SRAM_WP_PAGE21: SRAM page 21 write protection
      \arg        SYSCFG_SRAM_WP_PAGE22: SRAM page 22 write protection
      \arg        SYSCFG_SRAM_WP_PAGE23: SRAM page 23 write protection
      \arg        SYSCFG_SRAM_WP_PAGE24: SRAM page 24 write protection
      \arg        SYSCFG_SRAM_WP_PAGE25: SRAM page 25 write protection
      \arg        SYSCFG_SRAM_WP_PAGE26: SRAM page 26 write protection
      \arg        SYSCFG_SRAM_WP_PAGE27: SRAM page 27 write protection
      \arg        SYSCFG_SRAM_WP_PAGE28: SRAM page 28 write protection
      \arg        SYSCFG_SRAM_WP_PAGE29: SRAM page 29 write protection
      \arg        SYSCFG_SRAM_WP_PAGE30: SRAM page 30 write protection
      \arg        SYSCFG_SRAM_WP_PAGE31: SRAM page 31 write protection
    \param[out] none
    \retval     none
    \note       Once SRAM write protection is enabled, it can only be cleared by system reset.
                There is no software method to disable SRAM write protection.
*/
void syscfg_sram_page_wp_enable(uint32_t page)
{
    SYSCFG_SRAMWP |= (page & SRAM_WP_MASK);
}

/*!
    \brief      get SRAM ECC single-bit error bit position (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     uint32_t: error bit position (0-38, 0 means no error)
                bit 0-5: indicates which one bit has an SRAM ECC single-bit correctable error
                000000: no error
                000001: bit 0
                000010: bit 1
                ...
                100111: bit 38
*/
uint32_t syscfg_sram_ecc_error_bit_get(void)
{
    return ((SYSCFG_SRAMECCCS & SYSCFG_SRAMECCCS_SRAMECCSERRBITS) >> 10U);
}

/*!
    \brief      get SRAM ECC error address (API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     uint32_t: faulting system address where the last ECC event on SRAM occurred
*/
uint32_t syscfg_sram_ecc_error_addr_get(void)
{
    return ((SYSCFG_SRAMECCCS & SYSCFG_SRAMECCCS_SRAMECCADDR) >> 19U) << 2U;
}

/*!
    \brief      enable FPU interrupt (API_ID(0x000CU))
    \param[in]  interrupt: FPU interrupt
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_FPUINT_INVALID_OPERATION: invalid operation interrupt enable bit
      \arg        SYSCFG_FPUINT_DIV0: divide by 0 interrupt enable bit
      \arg        SYSCFG_FPUINT_UNDERFLOW: underflow interrupt enable bit
      \arg        SYSCFG_FPUINT_OVERFLOW: overflow interrupt enable bit
      \arg        SYSCFG_FPUINT_INPUT_ABNORMAL: input abnormal interrupt enable bit
      \arg        SYSCFG_FPUINT_INEXACT: inexact interrupt enable bit
    \param[out] none
    \retval     none
*/
void syscfg_fpu_interrupt_enable(uint32_t interrupt)
{
    SYSCFG_FPUINTEN |= (interrupt & FPU_INT_MASK);
}

/*!
    \brief      disable FPU interrupt (API_ID(0x000DU))
    \param[in]  interrupt: FPU interrupt
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_FPUINT_INVALID_OPERATION: invalid operation interrupt enable bit
      \arg        SYSCFG_FPUINT_DIV0: divide by 0 interrupt enable bit
      \arg        SYSCFG_FPUINT_UNDERFLOW: underflow interrupt enable bit
      \arg        SYSCFG_FPUINT_OVERFLOW: overflow interrupt enable bit
      \arg        SYSCFG_FPUINT_INPUT_ABNORMAL: input abnormal interrupt enable bit
      \arg        SYSCFG_FPUINT_INEXACT: inexact interrupt enable bit
    \param[out] none
    \retval     none
*/
void syscfg_fpu_interrupt_disable(uint32_t interrupt)
{
    SYSCFG_FPUINTEN &= ~(interrupt & FPU_INT_MASK);
}

/*!
    \brief      enable SRAM ECC error interrupt (API_ID(0x000EU))
    \param[in]  sram_ecc: SRAM ECC error
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_SRAMECCCS_SRAMECCMEIE: SRAM multi-bit non-correction interrupt enable
      \arg        SYSCFG_SRAMECCCS_SRAMECCSEIE: SRAM single bit correction interrupt enable
    \param[out] none
    \retval     none
*/
void syscfg_sram_ecc_interrupt_enable(uint32_t sram_ecc)
{
    SYSCFG_SRAMECCCS |= (sram_ecc & SRAM_ECC_MASK);
}

/*!
    \brief      disable SRAM ECC error interrupt (API_ID(0x000FU))
    \param[in]  sram_ecc: SRAM ECC error
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_SRAMECCCS_SRAMECCMEIE: SRAM multi-bit non-correction interrupt enable
      \arg        SYSCFG_SRAMECCCS_SRAMECCSEIE: SRAM single bit correction interrupt enable
    \param[out] none
    \retval     none
*/
void syscfg_sram_ecc_interrupt_disable(uint32_t sram_ecc)
{
    SYSCFG_SRAMECCCS &= ~(sram_ecc & SRAM_ECC_MASK);
}

/*!
    \brief      get bus timeout flag (API_ID(0x0010U))
    \param[in]  bustoflag: bus timeout flag
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_BUSTOSTAT_CPUCBUSTOF: CPU Cbus timeout flag
      \arg        SYSCFG_BUSTOSTAT_CPUSBUSTOF: CPU Sbus timeout flag
      \arg        SYSCFG_BUSTOSTAT_DMA0BUSTOF: DMA0 bus timeout flag
      \arg        SYSCFG_BUSTOSTAT_DMA1BUSTOF: DMA1 bus timeout flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_bus_timeout_flag_get(uint32_t bustoflag)
{
    FlagStatus retval = RESET;
    
    if(0U != (SYSCFG_BUSTOSTAT & bustoflag)) {
        retval = SET;
    } else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }
    
    return retval;
}

/*!
    \brief      clear bus timeout flag (API_ID(0x0011U))
    \param[in]  bustoflag: bus timeout flag
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_BUSTOSTAT_CPUCBUSTOF: CPU Cbus timeout flag
      \arg        SYSCFG_BUSTOSTAT_CPUSBUSTOF: CPU Sbus timeout flag
      \arg        SYSCFG_BUSTOSTAT_DMA0BUSTOF: DMA0 bus timeout flag
      \arg        SYSCFG_BUSTOSTAT_DMA1BUSTOF: DMA1 bus timeout flag
    \param[out] none
    \retval     none
*/
void syscfg_bus_timeout_flag_clear(uint32_t bustoflag)
{
    SYSCFG_BUSTOSTAT |= (bustoflag & BUSTOFLAG_MASK);
}

/*!
    \brief      get SRAM ECC error flag (API_ID(0x0012U))
    \param[in]  ecc_flag: SRAM ECC error flag
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_SRAMECCSTAT_SRAMECCMEIF: SRAM non-correction event detected
      \arg        SYSCFG_SRAMECCSTAT_SRAMECCSEIF: SRAM single bit correction event detected
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_sram_ecc_flag_get(uint32_t ecc_flag)
{
    FlagStatus retval = RESET;
    
    if(0U != (SYSCFG_SRAMECCSTAT & ecc_flag)){
        retval = SET;
    } else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }
    
    return retval;
}
 
/*!
    \brief      clear SRAM ECC error flag (API_ID(0x0013U))
    \param[in]  ecc_flag: SRAM ECC error flag
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_SRAMECCSTAT_SRAMECCMEIF: SRAM non-correction event detected
      \arg        SYSCFG_SRAMECCSTAT_SRAMECCSEIF: SRAM single bit correction event detected
    \param[out] none
    \retval     none
*/
void syscfg_sram_ecc_flag_clear(uint32_t ecc_flag)
{
    SYSCFG_SRAMECCSTAT |= (ecc_flag & ECC_FLAG_MASK);
}
