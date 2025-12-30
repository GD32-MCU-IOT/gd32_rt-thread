/*!
    \file    gd32g5x3_fmc.c
    \brief   FMC driver

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

#include "gd32g5x3_fmc.h"

/* FMC register bit offset */
#define OBCTL_SPC_OFFSET                  ((uint32_t)0x00000000U)               /*!< bit offset of SPC offset in FMC_OBCTL register */
#define OBCTL_USER_OFFSET                 ((uint32_t)0x00000008U)               /*!< bit offset of USER offset in FMC_OBCTL register */
#define CTL_PNSEL_OFFSET                  ((uint32_t)0x00000003U)               /*!< bit offset of PNSEL offset in FMC_CTL register */

/* return FMC state */
static fmc_state_enum fmc_state_get(void);
/* check FMC ready or not */
static fmc_state_enum fmc_ready_wait(uint32_t timeout);

/*!
    \brief      unlock the main FMC operation
                it is better to used in pairs with fmc_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_unlock(void)
{
    if(RESET != (FMC_CTL & FMC_CTL_LK)){
        /* write the FMC unlock key */
        FMC_KEY = FMC_UNLOCK_KEY0;
        FMC_KEY = FMC_UNLOCK_KEY1;
    }
}

/*!
    \brief      lock the main FMC operation
                it is better to used in pairs with fmc_unlock after an operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_lock(void)
{
    /* set the LK bit */
    FMC_CTL |= FMC_CTL_LK; 
}

/*!
    \brief      set the wait state
    \param[in]  wscnt: wait state
                only one parameter can be selected which is shown as below:
      \arg        FMC_WAIT_STATE_0: 0 wait state added
      \arg        FMC_WAIT_STATE_1: 1 wait state added
      \arg        FMC_WAIT_STATE_2: 2 wait state added
      \arg        FMC_WAIT_STATE_3: 3 wait state added
      \arg        FMC_WAIT_STATE_4: 4 wait state added
      \arg        FMC_WAIT_STATE_5: 5 wait state added
      \arg        FMC_WAIT_STATE_6: 6 wait state added
      \arg        FMC_WAIT_STATE_7: 7 wait state added
    \param[out] none
    \retval     none
*/
void fmc_wscnt_set(uint32_t wscnt)
{
    uint32_t ws;

    ws = FMC_WS;

    /* set the wait state counter value */
    ws &= ~FMC_WS_WSCNT;
    FMC_WS = (ws | wscnt);
}

/*!
    \brief      enable pre-fetch
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_prefetch_enable(void)
{
    FMC_WS |= FMC_WS_PFEN;
}

/*!
    \brief      disable pre-fetch
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_prefetch_disable(void)
{
    FMC_WS &= ~FMC_WS_PFEN;
}

/*!
    \brief      enable IBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_icache_enable(void)
{
    FMC_WS |= FMC_WS_ICEN;
}

/*!
    \brief      disable IBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_icache_disable(void)
{
    FMC_WS &= ~FMC_WS_ICEN;
}

/*!
    \brief      reset IBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_icache_reset(void)
{
    FMC_WS |= FMC_WS_ICRST;
}

/*!
    \brief      enable DBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_dcache_enable(void)
{
    FMC_WS |= FMC_WS_DCEN;
}

/*!
    \brief      disable DBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_dcache_disable(void)
{
    FMC_WS &= ~FMC_WS_DCEN;
}

/*!
    \brief      reset DBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_dcache_reset(void)
{
    FMC_WS |= FMC_WS_DCRST;
}

/*!
    \brief      FMC erase page
    \param[in]  bank: specify which bank the target page is in
                only one parameter can be selected which is shown as below:
      \arg        FMC_BANK0: BANK0 of main flash
      \arg        FMC_BANK1: BANK1 of main flash
    \param[in]  page_number_in_bank: page number in the bank
                only one parameter can be selected which is shown as below:
      \arg        0 ~ (max count of pages in the bank)-1
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
*/
fmc_state_enum fmc_page_erase(uint32_t bank, uint32_t page_number_in_bank)
{
    fmc_state_enum fmc_state;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        /* select the bank page in */
        if(OB_DUAL_BANK_MODE == (FMC_OBCTL & FMC_OBCTL_DBS)){ 
            if(FMC_BANK0 == bank){
                FMC_CTL &= ~FMC_CTL_BKSEL;
            }else{
                FMC_CTL |= FMC_CTL_BKSEL;
            }
        }else{
            FMC_CTL &= ~FMC_CTL_BKSEL;
        }

        FMC_CTL &= ~FMC_CTL_PNSEL;
        FMC_CTL |= page_number_in_bank << CTL_PNSEL_OFFSET;
        FMC_CTL |= FMC_CTL_PER;
        
        /* start page erase */
        FMC_CTL |= FMC_CTL_START;
        
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        
        FMC_CTL &= ~FMC_CTL_PER;
        FMC_CTL &= ~FMC_CTL_PNSEL;
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      FMC erase bank0. It is valid only in dual bank mode.
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress 
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error 
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
*/
fmc_state_enum fmc_bank0_erase(void)
{
    fmc_state_enum fmc_state;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        /* start chip erase */
        FMC_CTL |= FMC_CTL_MER0;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        /* reset the MER bit */
        FMC_CTL &= ~FMC_CTL_MER0;
    }
    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      FMC erase bank1. It is valid only in dual bank mode.
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress  
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error 
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
*/
fmc_state_enum fmc_bank1_erase(void)
{
    fmc_state_enum fmc_state;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        /* start chip erase */
        FMC_CTL |= FMC_CTL_MER1;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        /* reset the MER bit */
        FMC_CTL &= ~FMC_CTL_MER1;
    }
    /* return the fmc state  */
    return fmc_state;
}

/*!
    \brief      FMC erase whole chip
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress  
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error 
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
*/
fmc_state_enum fmc_mass_erase(void)
{
    uint32_t reg_value;
    
    fmc_state_enum fmc_state;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        reg_value = FMC_CTL;
        reg_value |= (FMC_CTL_MER0|FMC_CTL_MER1|FMC_CTL_START);
        FMC_CTL = reg_value;              

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        /* reset the MER bit */
        reg_value = FMC_CTL;
        reg_value &= ~(FMC_CTL_MER0|FMC_CTL_MER1);
        FMC_CTL = reg_value;
    }
    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      program a double word at the given address in main flash
    \param[in]  address: address to program
    \param[in]  data: double word to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress 
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error 
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
*/
fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data)
{
    uint32_t data0, data1;
    fmc_state_enum fmc_state;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    data0 = (uint32_t)(data & 0xFFFFFFFFU);
    data1 = (uint32_t)((data >> 32U) & 0xFFFFFFFFU);

    if(FMC_READY == fmc_state) {
        /* set the PG bit to start program */
        FMC_CTL |= FMC_CTL_PG;
        REG32(address) = data0;
        __ISB();
        REG32(address + 4U) = data1;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        /* reset the PG bit */
        FMC_CTL &= ~FMC_CTL_PG;
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      get base address of bank0
    \param[in]  none
    \param[out] none
    \retval     base address of bank0
*/
uint32_t fmc_bank0_base_address_get(void)
{
    uint32_t base_addr;   

    if(OB_DUAL_BANK_MODE == (FMC_OBCTL & FMC_OBCTL_DBS)){
        /* get the information about the bank swapping in syscfg */
        if(RESET == (SYSCFG_CFG0 & SYSCFG_CFG0_FMC_SWP)){
            base_addr = MAIN_FLASH_BASE_ADDRESS + MAIN_FLASH_BANK_SIZE * 0x400U;
        }else{
            base_addr = MAIN_FLASH_BASE_ADDRESS;
        }
    }else{
        base_addr = MAIN_FLASH_BASE_ADDRESS;
    }

    return base_addr;
}

/*!
    \brief      get base address of bank1. It is only valid when DBS=1.
    \param[in]  none
    \param[out] none
    \retval     base address of bank1
*/
uint32_t fmc_bank1_base_address_get(void)
{
    uint32_t base_addr;
    
    /* get the information about the bank swapping in syscfg */
    if(RESET == (SYSCFG_CFG0 & SYSCFG_CFG0_FMC_SWP)){
        base_addr = MAIN_FLASH_BASE_ADDRESS;
    }else{
        base_addr = MAIN_FLASH_BASE_ADDRESS + MAIN_FLASH_BANK_SIZE * 0x400U;
    }

    return base_addr;
}

/*!
    \brief      get page size
    \param[in]  none
    \param[out] none
    \retval     page size
*/
uint32_t fmc_page_size_get(void)
{
    uint32_t page_size;
    
    if(OB_DUAL_BANK_MODE == (FMC_OBCTL & FMC_OBCTL_DBS)){
        page_size = MAIN_FLASH_PAGE_SIZE_DBANK;
    }else{
        page_size = MAIN_FLASH_PAGE_SIZE_SBANK;
    }

    return page_size; 
}

/*!
    \brief      enable debugger
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_debugger_enable(void)
{
    FMC_WS |= FMC_WS_DBGEN;
}

/*!
    \brief      disable debugger
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_debugger_disable(void)
{
    FMC_WS &= ~FMC_WS_DBGEN;
}

/*!
    \brief      flash enter power down mode when MCU enter sleep mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_slp_pd_mode_enable(void)
{
    FMC_WS |= FMC_WS_SLP_MDSEL;
}

/*!
    \brief      flash exit power down mode when MCU enter sleep mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_slp_pd_mode_disable(void)
{
    FMC_WS &= ~FMC_WS_SLP_MDSEL;
}

/*!
    \brief      enable secure area protection 
    \param[in]  scr_area: secure area
                only one parameter can be selected which is shown as below:
      \arg        SCR_AREA0: the secure area of bank0
      \arg        SCR_AREA1: the secure area of bank1
    \param[out] none
    \retval     none
*/
void fmc_scr_area_enable(uint32_t scr_area)
{
    if(OB_DUAL_BANK_MODE == (FMC_OBCTL & FMC_OBCTL_DBS)){
        /* configure secure area size in dual bank mode */
        if(SCR_AREA0 == scr_area){
            FMC_CTL |= FMC_CTL_SCR0;
        }else{
            FMC_CTL |= FMC_CTL_SCR1;
        }
    }else{
        /* configure secure area size in single bank mode */   
        FMC_CTL |= FMC_CTL_SCR0;
    }
}

/*!
    \brief      unlock the option bytes operation
                it is better to used in pairs with ob_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_unlock(void)
{
    if(RESET != (FMC_CTL & FMC_CTL_OBLK)){
        /* write the FMC ob unlock key */
        FMC_OBKEY = OB_UNLOCK_KEY0;
        FMC_OBKEY = OB_UNLOCK_KEY1;
    }
}

/*!
    \brief      lock the option bytes operation
                it is better to used in pairs with ob_unlock after an operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_lock(void)
{
    /* set the OBLK bit */
    FMC_CTL |= FMC_CTL_OBLK;
}

/*!
    \brief      reload the option bytes operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_reload(void)
{
    /* set the OBRLD bit */
    FMC_CTL |= FMC_CTL_OBRLD;
}

/*!
    \brief      program the option bytes USER
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_user: user option bytes. When write one paramter, the corresponding mask should be set.
                one or more (bitwise OR) parameters can be selected which are shown as below:
      \arg        OB_NRST_PIN_INPUT_MODE/OB_NRST_PIN_NORMAL_GPIO/OB_NRST_PIN_INPUT_OUTPUT_MODE: reset pin mode
      \arg        OB_NBOOT0_VALUE_0/OB_NBOOT0_VALUE_1: boot0 value 0 or value 1
      \arg        OB_NSWBOOT0_FROM_OB_BOOT0/OB_NSWBOOT0_FROM_PIN: boot by option byte value or by PB8/BOOT0 pin
      \arg        OB_TCMSRAM_ERASE_ENABLE/OB_TCMSRAM_ERASE_DISABLE: TCM SRAM erase or not when system reset
      \arg        OB_SRAM_ECC_ENABLE/OB_SRAM_ECC_DISABLE: SRAM and TCM SRAM ECC enable or disable
      \arg        OB_NBOOT1_VALUE_0/OB_NBOOT1_VALUE_1: boot1 value 0 or value 1
      \arg        OB_BB_DISABLE/OB_BB_ENABLE: boot bank value
      \arg        OB_STDBY_FWDGT_SUSPEND/OB_STDBY_FWDGT_RUN: free watchdog is suspended or running in standby mode
      \arg        OB_DPSLP_FWDGT_SUSPEND/OB_DPSLP_FWDGT_RUN: free watchdog is suspended or running in deep-sleep mode
      \arg        OB_FWDGT_HW/OB_FWDGT_SW: hardware or software free watchdog timer 
      \arg        OB_STDBY_RST/OB_STDBY_NRST: reset or not entering standby mode
      \arg        OB_DEEPSLEEP_RST/OB_DEEPSLEEP_NRST: reset or not entering deep sleep mode
      \arg        OB_BOR_TH_VALUE0/OB_BOR_TH_VALUE1/OB_BOR_TH_VALUE2/OB_BOR_TH_VALUE3: BOR threshold value
    \param[in]  ob_user_mask: user bits mask. They correspond to the above paramter value one by one. 
                  one or more (bitwise OR) parameters can be selected which are shown as below
      \arg        FMC_OBCTL_NRST_MDSEL: reset pin mode bit mask
      \arg        FMC_OBCTL_NBOOT0: NBOOT0 option bit mask
      \arg        FMC_OBCTL_NSWBT0: software BOOT0 bit mask
      \arg        FMC_OBCTL_TCMSRAM_ERS: TCM SRAM erase if system reset bit mask
      \arg        FMC_OBCTL_SRAM_ECCEN: SRAM and TCM SRAM ECC enable bit mask
      \arg        FMC_OBCTL_NBOOT1: NBOOT1 option bit mask
      \arg        FMC_OBCTL_BB: dual-bank boot bit mask
      \arg        FMC_OBCTL_FWDGSPD_STDBY: FWDGT suspend option in standby mode configuration bit mask
      \arg        FMC_OBCTL_FWDGSPD_DPSLP: FWDGT suspend option in deepsleep mode configuration bit mask
      \arg        FMC_OBCTL_NFWDG_HW: free watchdog configuration bit mask
      \arg        FMC_OBCTL_NRST_STDBY: option byte standby reset bit mask
      \arg        FMC_OBCTL_NRST_DPSLP: option byte deepsleep reset bit mask
      \arg        FMC_OBCTL_BOR_TH: BOR threshold status bits mask
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress  
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error 
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
      \arg        FMC_OB_HSPC: FMC is under high security protection
      \arg        FMC_OB_LSPC: FMC is under low security protection
*/
fmc_state_enum ob_user_write(uint32_t ob_user, uint32_t ob_user_mask)
{
    uint32_t obctl_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* check the option bytes security protection value */
    if(FMC_HSPC == (FMC_OBCTL & FMC_OBCTL_SPC)){
        return FMC_OB_HSPC;
    }

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        obctl_reg = FMC_OBCTL;
        FMC_OBCTL = (obctl_reg & (~ob_user_mask)) | ob_user;
        FMC_CTL |= FMC_CTL_OBSTART;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }

    return fmc_state;
}

/*!
    \brief      configure security protection
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_spc: specify security protection
                only one parameter can be selected which is shown as below:
      \arg        FMC_NSPC: no security protection
      \arg        FMC_LSPC: low security protection
      \arg        FMC_HSPC: high security protection
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress 
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
*/
fmc_state_enum ob_security_protection_config(uint8_t ob_spc)
{
    uint32_t obctl_reg;
    fmc_state_enum fmc_state = FMC_READY;
        
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        obctl_reg = FMC_OBCTL;

        /* reset the OBCTL_SPC, set according to ob_spc */
        obctl_reg &= ~FMC_OBCTL_SPC;
        obctl_reg |= (uint32_t)ob_spc;
        FMC_OBCTL = obctl_reg;
        FMC_CTL |= FMC_CTL_OBSTART;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure the option byte DCRP area
    \param[in]  dcrp_area: DCRP area
                only one parameter can be selected which is shown as below: 
      \arg        DCRP_AREA0: the DCRP area of bank0 when DBS=1 or the first area of whole memory when DBS=0
      \arg        DCRP_AREA1: the DCRP area of bank1 when DBS=1 or the second area of whole memory when DBS=0
    \param[in]  dcrp_eren: DCRP area erase enable bit
      \arg        OB_DCRP_AREA_ERASE_DISABLE: DCRP area is not erased when low security protection to no security protection
      \arg        OB_DCRP_AREA_ERASE_ENABLE: DCRP area is erased when low security protection to no security protection
    \param[in]  dcrp_start_addr: first doubleword of DCRP area address when DBS=1 or first 2 x doubleword of DCRP area when DBS=0
    \param[in]  dcrp_end_addr: last doubleword of DCRP area address when DBS=1 or last 2 x doubleword of DCRP area when DBS=0
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress   
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error 
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
      \arg        FMC_OB_HSPC: FMC is under high security protection
      \arg        FMC_OB_LSPC: FMC is under low security protection
*/
fmc_state_enum ob_dcrp_config(uint32_t dcrp_area, uint32_t dcrp_eren, uint32_t dcrp_start_addr, uint32_t dcrp_end_addr)
{
    uint32_t reg_value;
    uint32_t base_address;
    uint32_t dcrp_offset;
    fmc_state_enum fmc_state = FMC_READY;

    /* get base address */
    if(OB_SINGLE_BANK_MODE == (FMC_OBCTL & FMC_OBCTL_DBS)){
        base_address = MAIN_FLASH_BASE_ADDRESS;
        dcrp_offset = 4U;
    }else{
        if(DCRP_AREA0 == dcrp_area){
            base_address = fmc_bank0_base_address_get();
        }else{
            base_address = fmc_bank1_base_address_get();
        }
        dcrp_offset = 3U;
    }

    /* check the option bytes security protection value */
    if(FMC_HSPC == (FMC_OBCTL & FMC_OBCTL_SPC)){
        return FMC_OB_HSPC;
    }

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        /* configure DCRP area0 */
        if(DCRP_AREA0 == dcrp_area){
            dcrp_start_addr = ((dcrp_start_addr - base_address) >> dcrp_offset);
            dcrp_end_addr = ((dcrp_end_addr - base_address) >> dcrp_offset);
            if(dcrp_start_addr == dcrp_end_addr){
                return FMC_OPRERR;
            }
            FMC_DCRP_SADDR0 = dcrp_start_addr << DCRP_SADDR_DCRP_SADDR_OFFSET;

            reg_value = FMC_DCRP_EADDR0;
            reg_value &= ~FMC_DCRP_EADDR0_DCRP0_EREN;  
            reg_value &= ~FMC_DCRP_EADDR0_DCRP0_EADDR;  
            reg_value |= (dcrp_end_addr << DCRP_EADDR_DCRP_EADDR_OFFSET);
            FMC_DCRP_EADDR0 = reg_value;
        /* configure DCRP area1 */
        }else{
            dcrp_start_addr = ((dcrp_start_addr - base_address) >> dcrp_offset);
            dcrp_end_addr = ((dcrp_end_addr - base_address) >> dcrp_offset);
            if(dcrp_start_addr == dcrp_end_addr){
                return FMC_OPRERR;
            }
            FMC_DCRP_SADDR1 = dcrp_start_addr << DCRP_SADDR_DCRP_SADDR_OFFSET;
            FMC_DCRP_EADDR1 = dcrp_end_addr << DCRP_EADDR_DCRP_EADDR_OFFSET;
        }

        /* configure EREN */   
        reg_value = FMC_DCRP_EADDR0;
        reg_value &= ~FMC_DCRP_EADDR0_DCRP0_EREN;
        reg_value |= dcrp_eren;       
        FMC_DCRP_EADDR0 = reg_value;

        /* set the OBSTART bit in FMC_CTL register */
        FMC_CTL |= FMC_CTL_OBSTART;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }

    /* return the FMC state */
    return fmc_state;    
}
   
/*!
    \brief      configure the option byte write protection area
    \param[in]  wp_area: write protection area
                only one parameter can be selected which is shown as below:
      \arg        BK0WP_AREA0: the first area of bank0 when DBS=1 or the first area of whole memory when DBS=0
      \arg        BK0WP_AREA1: the second area of bank0 when DBS=1 or the second area of whole memory when DBS=0
      \arg        BK1WP_AREA0: the first area of bank1 when DBS=1 or the third area of whole memory when DBS=0
      \arg        BK1WP_AREA1: the second area of bank1 when DBS=1 or the fourth area of whole memory when DBS=0
    \param[in]  wp_start: first page of write protection area
    \param[in]  wp_end: last page of write protection area
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
      \arg        FMC_OB_HSPC: FMC is under high security protection
      \arg        FMC_OB_LSPC: FMC is under low security protection
*/
fmc_state_enum ob_write_protection_config(uint32_t wp_area, uint32_t wp_start, uint32_t wp_end)
{
    uint32_t value;
    fmc_state_enum fmc_state = FMC_READY;

    /* check the option bytes security protection value */
    if(FMC_HSPC == (FMC_OBCTL & FMC_OBCTL_SPC)){
        return FMC_OB_HSPC;
    }

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        value = (wp_start << BKWP_BKWP_SADDR_OFFSET) | (wp_end << BKWP_BKWP_EADDR_OFFSET);
        value |= 0xFF00FF00U;
        /* configure the write protected area */
        if(BK0WP_AREA0 == wp_area){
            FMC_BK0WP0 = value;
        }else if(BK0WP_AREA1 == wp_area){
            FMC_BK0WP1 = value;
        }else if(BK1WP_AREA0 == wp_area){
            FMC_BK1WP0 = value;
        }else{
            FMC_BK1WP1 = value;
        }

        /* set the OBSTART bit in FMC_CTL register */
        FMC_CTL |= FMC_CTL_OBSTART;
        
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }

    /* return the FMC state */
    return fmc_state;     
}

/*!
    \brief      configure the option byte secure area
    \param[in]  scr_area: secure area 
                only one parameter can be selected which is shown as below:
      \arg        SCR_AREA0: the secure area of bank0
      \arg        SCR_AREA1: the secure area of bank1. It is useful only in dual bank mode.
    \param[in]  secure_size: size of secure area in page unit
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress   
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error 
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
      \arg        FMC_OB_HSPC: FMC is under high security protection
      \arg        FMC_OB_LSPC: FMC is under low security protection
*/
fmc_state_enum ob_scr_area_config(uint32_t scr_area, uint32_t secure_size)
{    
    uint32_t reg_value;
    fmc_state_enum fmc_state = FMC_READY;

    /* check the option bytes security protection value */
    if(FMC_HSPC == (FMC_OBCTL & FMC_OBCTL_SPC)){
        return FMC_OB_HSPC;
    }

    /* check the option bytes security protection value */
    if(FMC_LSPC == (FMC_OBCTL & FMC_OBCTL_SPC)){
        return FMC_OB_LSPC;
    }

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        if(OB_DUAL_BANK_MODE == (FMC_OBCTL & FMC_OBCTL_DBS)){ 
            /* configure secure area in dual bank mode */
            if(SCR_AREA0 == scr_area){
                reg_value = FMC_BK0SCR;
                reg_value &= ~FMC_BK0SCR_SCR_PAGE_CNT0;
                reg_value |= secure_size << BKSCR_SCR_PAGE_CNT_OFFSET;
                FMC_BK0SCR = reg_value;
            }else{
                reg_value = FMC_BK1SCR;
                reg_value &= ~FMC_BK1SCR_SCR_PAGE_CNT1;
                reg_value |= secure_size << BKSCR_SCR_PAGE_CNT_OFFSET;
                FMC_BK1SCR = reg_value;
            }
        }else{
            /* configure secure area in single bank mode */ 
            if(SCR_AREA0 == scr_area){ 
                reg_value = FMC_BK0SCR;
                reg_value &= ~FMC_BK0SCR_SCR_PAGE_CNT0;
                reg_value |= secure_size << BKSCR_SCR_PAGE_CNT_OFFSET;
                FMC_BK0SCR = reg_value;
            }else{
                return fmc_state;
            }
        }

        /* set the OBSTART bit in FMC_CTL register */
        FMC_CTL |= FMC_CTL_OBSTART;
        
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure the option byte boot lock
    \param[in]  boot_config: boot configuration
                only one parameter can be selected which is shown as below:
      \arg        OB_BOOT_LOCK_FROM_MAIN_FLASH: boot from main flash
      \arg        OB_BOOT_UNLOCK: unlock boot
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error 
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
      \arg        FMC_OB_HSPC: FMC is under high security protection
      \arg        FMC_OB_LSPC: FMC is under low security protection
*/
fmc_state_enum ob_boot_lock_config(uint32_t boot_config)
{    
    uint32_t reg_value;
    fmc_state_enum fmc_state = FMC_READY;

    /* check the option bytes security protection value */
    if(FMC_HSPC == (FMC_OBCTL & FMC_OBCTL_SPC)){
        return FMC_OB_HSPC;
    }

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        reg_value = FMC_BK0SCR;
        reg_value &= ~FMC_BK0SCR_BOOTLK;
        reg_value |= boot_config;
        FMC_BK0SCR = reg_value;

        /* set the OBSTART bit in FMC_CTL register */
        FMC_CTL |= FMC_CTL_OBSTART;
        
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure FMC memory mapping swap bit
    \param[in]  swp_config: bank memory mapping swap configuration
                only one parameter can be selected which is shown as below:
      \arg        OB_BANK_MAPPING_SWAP: swap bank memory mapping.
      \arg        OB_BANK_MAPPING_NOT_SWAP: do not swap bank memory mapping.
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error 
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
      \arg        FMC_OB_HSPC: FMC is under high security protection 
      \arg        FMC_OB_LSPC: FMC is under low security protection
*/
fmc_state_enum ob_bank_memory_swap_config(uint32_t swp_config)
{
    uint32_t obctl_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        obctl_reg = FMC_OBCTL;

        /* configure FMC memory mapping swap bit  */
        obctl_reg &= ~FMC_OBCTL_FMC_SWP;
        obctl_reg |= (uint32_t)swp_config;
        FMC_OBCTL = obctl_reg;
        FMC_CTL |= FMC_CTL_OBSTART;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }

    /* return the FMC state */
    return fmc_state;    
}

/*!
    \brief      get the value of option bytes USER
    \param[in]  none
    \param[out] none
    \retval     the option bytes USER value
*/
uint32_t ob_user_get(void)
{
    /* return the FMC user option bytes value */
    return (uint32_t)(FMC_OBCTL >> OBCTL_USER_OFFSET);
}

/*!
    \brief      get the value of FMC option bytes security protection level in FMC_OBCTL register
    \param[in]  none
    \param[out] none
    \retval     protection level
      \arg        FMC_NSPC: no protection
      \arg        FMC_LSPC: protection level low
      \arg        FMC_HSPC: protection level high
*/
uint8_t ob_security_protection_level_get(void)
{
    return (uint8_t)((FMC_OBCTL & FMC_OBCTL_SPC) >> OBCTL_SPC_OFFSET);
}

/*!
    \brief      get configuration of DCRP area 
    \param[in]  dcrp_area: DCRP area
                only one parameter can be selected which is shown as below: 
      \arg        DCRP_AREA0: the DCRP area of bank0 when DBS=1 or the first area of whole memory when DBS=0
      \arg        DCRP_AREA1: the DCRP area of bank1 when DBS=1 or the second area of whole memory when DBS=0
    \param[out] dcrp_erase_option: erase option of DCRP area
    \param[out] dcrp_start_addr: start address of DCRP area
    \param[out] dcrp_end_addr: end address of DCRP area
    \retval     state of address
      \arg        INVLD_AREA_ADDRESS: the area address is invalid
      \arg        VLD_AREA_ADDRESS: the area address is valid
*/
uint32_t ob_dcrp_area_get(uint32_t dcrp_area, uint32_t *dcrp_erase_option, uint32_t *dcrp_area_start_addr, uint32_t *dcrp_area_end_addr)
{
    uint32_t start_dcrp;
    uint32_t end_dcrp;
    uint32_t base_address;
    uint32_t dcrp_size_unit;

    /* get base address */
    if(OB_SINGLE_BANK_MODE == (FMC_OBCTL & FMC_OBCTL_DBS)){
        base_address = MAIN_FLASH_BASE_ADDRESS;
        dcrp_size_unit = 16U;
    }else{
        if(DCRP_AREA0 == dcrp_area){
            base_address = fmc_bank0_base_address_get();
        }else{
            base_address = fmc_bank1_base_address_get();
        }
        dcrp_size_unit = 8U;
    }

    if(DCRP_AREA0 == dcrp_area){
        start_dcrp = (FMC_DCRP_SADDR0 & FMC_DCRP_SADDR0_DCRP0_SADDR) >> DCRP_SADDR_DCRP_SADDR_OFFSET;
        end_dcrp = (FMC_DCRP_EADDR0 & FMC_DCRP_EADDR0_DCRP0_EADDR) >> DCRP_EADDR_DCRP_EADDR_OFFSET;
        *dcrp_erase_option = (FMC_DCRP_EADDR0 & FMC_DCRP_EADDR0_DCRP0_EREN) >> DCRP_EADDR_DCRP_EREN_OFFSET;
    }else{
        start_dcrp = (FMC_DCRP_SADDR1 & FMC_DCRP_SADDR1_DCRP1_SADDR) >> DCRP_SADDR_DCRP_SADDR_OFFSET;
        end_dcrp = (FMC_DCRP_EADDR1 & FMC_DCRP_EADDR1_DCRP1_EADDR) >> DCRP_EADDR_DCRP_EADDR_OFFSET;
    }

    /* get start address and end address of DCRP area */
    *dcrp_area_start_addr = base_address + start_dcrp * dcrp_size_unit;
    *dcrp_area_end_addr = base_address + (end_dcrp + 1U) * dcrp_size_unit - 1U;

    if(start_dcrp <= end_dcrp){
        /* the DCRP area is valid */
        return VLD_AREA_ADDRESS;
    }else{
        /* the DCRP area is invalid */
        return INVLD_AREA_ADDRESS;
    }
}

/*!
    \brief      get address of write protection area
    \param[in]  wp_area: write protection area
                only one parameter can be selected which is shown as below:
      \arg        BK0WP_AREA0: the first area of bank0 when DBS=1 or the first area of whole memory when DBS=0
      \arg        BK0WP_AREA1: the second area of bank0 when DBS=1 or the second area of whole memory when DBS=0
      \arg        BK1WP_AREA0: the first area of bank1 when DBS=1 or the third area of whole memory when DBS=0
      \arg        BK1WP_AREA1: the second area of bank1 when DBS=1 or the fourth area of whole memory when DBS=0
    \param[out] wp_area_start_addr: start address of write protection area
    \param[out] wp_area_end_addr: end address of write protection area
    \retval     state of address
      \arg        INVLD_AREA_ADDRESS: the area address is invalid
      \arg        VLD_AREA_ADDRESS: the area address is valid
*/
uint32_t ob_write_protection_get(uint32_t wp_area, uint32_t *wp_area_start_addr, uint32_t *wp_area_end_addr)
{
    uint32_t start_wp;
    uint32_t end_wp;
    uint32_t base_address;
    uint32_t wp_size_unit;

    /* get base address */
    if(OB_SINGLE_BANK_MODE == (FMC_OBCTL & FMC_OBCTL_DBS)){
        base_address = MAIN_FLASH_BASE_ADDRESS;
        wp_size_unit = MAIN_FLASH_PAGE_SIZE_SBANK;
    }else{
        if((BK0WP_AREA0 == wp_area) || (BK0WP_AREA1 == wp_area)){
            base_address = fmc_bank0_base_address_get();
        }else{
            base_address = fmc_bank1_base_address_get();
        }
        wp_size_unit = MAIN_FLASH_PAGE_SIZE_DBANK;
    }

    if(BK0WP_AREA0 == wp_area){
        start_wp = (FMC_BK0WP0 & FMC_BK0WP0_BK0WP0_SADDR) >> BKWP_BKWP_SADDR_OFFSET;
        end_wp = (FMC_BK0WP0 & FMC_BK0WP0_BK0WP0_EADDR) >> BKWP_BKWP_EADDR_OFFSET;
    }else if(BK0WP_AREA1 == wp_area){
        start_wp = (FMC_BK0WP1 & FMC_BK0WP1_BK0WP1_SADDR) >> BKWP_BKWP_SADDR_OFFSET;
        end_wp = (FMC_BK0WP1 & FMC_BK0WP1_BK0WP1_EADDR) >> BKWP_BKWP_EADDR_OFFSET;
    }else if(BK1WP_AREA0 == wp_area){            
        start_wp = (FMC_BK1WP0 & FMC_BK1WP0_BK1WP0_SADDR) >> BKWP_BKWP_SADDR_OFFSET;
        end_wp = (FMC_BK1WP0 & FMC_BK1WP0_BK1WP0_EADDR) >> BKWP_BKWP_EADDR_OFFSET;
    }else{
        start_wp = (FMC_BK1WP1 & FMC_BK1WP1_BK1WP1_SADDR) >> BKWP_BKWP_SADDR_OFFSET;
        end_wp = (FMC_BK1WP1 & FMC_BK1WP1_BK1WP1_EADDR) >> BKWP_BKWP_EADDR_OFFSET;
    }

    *wp_area_start_addr = base_address + start_wp * wp_size_unit;
    *wp_area_end_addr = base_address + (end_wp + 1U) * wp_size_unit - 1U;

    if(start_wp <= end_wp){
        /* the write protected area is valid */
        return VLD_AREA_ADDRESS;
    }else{
        /* the write protected area is invalid */
        return INVLD_AREA_ADDRESS;
    }
}

/*!
    \brief      get size of secure area 
    \param[in]  scr_area: secure area 
                only one parameter can be selected which is shown as below:
      \arg        SCR_AREA0: the secure area of bank0
      \arg        SCR_AREA1: the secure area of bank1
    \param[out] scr_area_byte_cnt: secure area size in byte unit
    \retval     state of size
      \arg        INVLD_AREA_SIZE: the area size is invalid
      \arg        VLD_AREA_SIZE: the area size is valid
*/
uint32_t ob_scr_area_size_get(uint32_t scr_area, uint32_t *scr_area_byte_cnt)
{
    uint32_t reg_value = 0u;
    uint32_t scr_size_unit;    

    if(OB_DUAL_BANK_MODE == (FMC_OBCTL & FMC_OBCTL_DBS)){
        scr_size_unit = MAIN_FLASH_PAGE_SIZE_DBANK;

        /* get secure area size in dual bank mode */        
        if(SCR_AREA0 == scr_area){
            reg_value = (FMC_BK0SCR & FMC_BK0SCR_SCR_PAGE_CNT0) >> BKSCR_SCR_PAGE_CNT_OFFSET;
        }else{
            reg_value = (FMC_BK1SCR & FMC_BK1SCR_SCR_PAGE_CNT1) >> BKSCR_SCR_PAGE_CNT_OFFSET;
        }
    }else{
        scr_size_unit = MAIN_FLASH_PAGE_SIZE_SBANK;

        /* get secure area size in single bank mode */ 
        if(SCR_AREA0 == scr_area){
            reg_value = (FMC_BK0SCR & FMC_BK0SCR_SCR_PAGE_CNT0) >> BKSCR_SCR_PAGE_CNT_OFFSET;
        }else{
            return INVLD_AREA_SIZE;
        }
    }

    *scr_area_byte_cnt = reg_value * scr_size_unit;
    return VLD_AREA_SIZE;
}

/*!
    \brief      get boot configuration 
    \param[in]  none
    \param[out] none
    \retval     boot configuration
      \arg        OB_BOOT_LOCK_FROM_MAIN_FLASH: boot from main flash
      \arg        OB_BOOT_UNLOCK: unlock boot
*/
uint32_t ob_boot_config_get(void)
{
    return (uint32_t)(FMC_BK0SCR & FMC_BK0SCR_BOOTLK);
}

/*!
    \brief      get FMC flag status
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_BUSY: FMC operation is in progress
      \arg        FMC_FLAG_OBERR: option byte read error
      \arg        FMC_FLAG_WPERR: erase/program protection error
      \arg        FMC_FLAG_PGSERR: program sequence error
      \arg        FMC_FLAG_PGMERR: program size error
      \arg        FMC_FLAG_PGAERR: program alignment error
      \arg        FMC_FLAG_RPERR: read protection error
      \arg        FMC_FLAG_PGERR: program error
      \arg        FMC_FLAG_OPRERR: operation error
      \arg        FMC_FLAG_ENDF: FMC end of operation flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

    if(FMC_STAT & flag){
        status = SET;
    }
    /* return the state of corresponding FMC flag */
    return status;
}

/*!
    \brief      clear the FMC flag
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_OBERR: option byte read error
      \arg        FMC_FLAG_WPERR: erase/program protection error
      \arg        FMC_FLAG_PGSERR: program sequence error
      \arg        FMC_FLAG_PGMERR: program size error
      \arg        FMC_FLAG_PGAERR: program alignment error
      \arg        FMC_FLAG_RPERR: read protection error
      \arg        FMC_FLAG_PGERR: program error
      \arg        FMC_FLAG_OPRERR: operation error
      \arg        FMC_FLAG_ENDF: FMC end of operation flag
    \param[out] none
    \retval     none
*/
void fmc_flag_clear(uint32_t flag)
{
    /* clear the flags */
    FMC_STAT |= flag;
}

/*!
    \brief      enable FMC interrupt
    \param[in]  interrupt: the FMC interrupt
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END: FMC end of operation interrupt
      \arg        FMC_INT_ERR: FMC error interrupt
      \arg        FMC_INT_RPERR: read protection error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_enable(uint32_t interrupt)
{
    FMC_CTL |= interrupt;
}

/*!
    \brief      disable FMC interrupt
    \param[in]  interrupt: the FMC interrupt
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END: FMC end of operation interrupt
      \arg        FMC_INT_ERR: FMC error interrupt
      \arg        FMC_INT_RPERR: read protection error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_disable(uint32_t interrupt)
{
    FMC_CTL &= ~interrupt;
}

/*!
    \brief      get ECC flag status
    \param[in]  flag: ECC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_ECCDET0: two-bit error detected flag(in 64bit LSB when DBS is 0)
      \arg        FMC_FLAG_ECCCOR0: one-bit error detected and corrected flag(in 64bit LSB when DBS is 0)
      \arg        FMC_FLAG_ECCDET1: two-bit error detected flag in 64bit MSB
      \arg        FMC_FLAG_ECCCOR1: one-bit error detected and corrected flag in 64bit MSB
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_ecc_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

    if(FMC_ECCCS & flag){
        status = SET;
    }
    /* return the state of corresponding ECC flag */
    return status;
}

/*!
    \brief      clear the ECC flag
    \param[in]  flag: ECC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_ECCDET0: two-bit error detected flag(in 64bit LSB when DBS is 0)
      \arg        FMC_FLAG_ECCCOR0: one-bit error detected and corrected flag(in 64bit LSB when DBS is 0)
      \arg        FMC_FLAG_ECCDET1: two-bit error detected flag in 64bit MSB
      \arg        FMC_FLAG_ECCCOR1: one-bit error detected and corrected flag in 64bit MSB
    \param[out] none
    \retval     none
*/
void fmc_ecc_flag_clear(uint32_t flag)
{
    uint32_t ecccorie;

    ecccorie = FMC_ECCCS & FMC_ECCCS_ECCCORIE;

    /* clear the flag */
    FMC_ECCCS = (flag | ecccorie);
}

/*!
    \brief      enable ECCCOR interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ecccor_interrupt_enable(void)
{
    FMC_ECCCS |= FMC_ECCCS_ECCCORIE;
}

/*!
    \brief      disable ECCCOR interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ecccor_interrupt_disable(void)
{
    FMC_ECCCS &= ~FMC_ECCCS_ECCCORIE;
}

/*!
    \brief      get ECCCOR interrupt flag 
    \param[in]  flag: ECCCOR interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_ECCCOR0: one-bit error detected and corrected flag
      \arg        FMC_INT_FLAG_ECCCOR1: one-bit error detected and corrected flag in 64bit MSB
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_ecccor_interrupt_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

    if(FMC_ECCCS & flag){
        status = SET;
    }

    /* return the state of ECCCOR interrupt flag */
    return status;
}

/*!
    \brief      clear ECCCOR interrupt flag
    \param[in]  flag: ECCCOR interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_ECCCOR0: one-bit error detected and corrected flag
      \arg        FMC_INT_FLAG_ECCCOR1: one-bit error detected and corrected flag in 64bit MSB
    \param[out] none
    \retval     none
*/
void fmc_ecccor_interrupt_flag_clear(uint32_t flag)
{
    /* clear the flag */
    FMC_ECCCS |= flag;
}

/*!
    \brief      get FMC interrupt flag
    \param[in]  flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_END: FMC end of operation interrupt flag
      \arg        FMC_INT_FLAG_OPRERR: FMC operation error interrupt flag
      \arg        FMC_INT_FLAG_RPERR: read protection error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_interrupt_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

    if(FMC_STAT & flag){
        status = SET;
    }

    /* return the state of corresponding FMC flag */
    return status;
}

/*!
    \brief      clear FMC interrupt flag
    \param[in]  flag: FMC interrupt flag
                one or more parameters can be selected which is shown as below:
      \arg        FMC_INT_FLAG_END: FMC end of operation interrupt flag
      \arg        FMC_INT_FLAG_OPRERR: FMC operation error interrupt flag
      \arg        FMC_INT_FLAG_RPERR: read protection error interrupt flag
    \param[out] none
    \retval     none
*/
void fmc_interrupt_flag_clear(uint32_t flag)
{
    /* clear the flag */
    FMC_STAT |= flag;
}

/*!
    \brief      get the FMC state
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress
      \arg        FMC_OBERR: option byte read error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
*/
static fmc_state_enum fmc_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_BUSY)){
        fmc_state = FMC_BUSY;
    }else{
        if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_WPERR)){
            fmc_state = FMC_WPERR;
        }else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_PGERR)){
            fmc_state = FMC_PGERR;    
        }else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_PGSERR)){
            fmc_state = FMC_PGSERR;   
        }else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_PGAERR)){
            fmc_state = FMC_PGAERR;   
        }else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_RPERR)){
            fmc_state = FMC_RPERR;
        }else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_PGMERR)){
            fmc_state = FMC_PGMERR;
        }else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_OBERR)){
            fmc_state = FMC_OBERR;
        }else {
            /* illegal parameters */
        }
  }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC is ready or not
    \param[in]  timeout: timeout count
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: FMC operation has been completed
      \arg        FMC_BUSY: FMC operation is in progress
      \arg        FMC_OBERR: option byte read error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_PGERR: program error
      \arg        FMC_OPRERR: operation error
      \arg        FMC_TOERR: FMC timeout error
*/
static fmc_state_enum fmc_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_BUSY;

    /* wait for FMC ready */
    do{
        /* get FMC state */
        fmc_state = fmc_state_get();
        timeout--;
    }while((FMC_BUSY == fmc_state) && (0x00U != timeout));

    if(FMC_BUSY == fmc_state){
        fmc_state = FMC_TOERR;
    }
    /* return the FMC state */
    return fmc_state;
}
