/*!
    \file    gd32w51x_f5hc_fmc.c
    \brief   FMC driver

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

#include "gd32w51x_f5hc_fmc.h"

/* FMC mask */
/* FMC_SECMCFGx mask */
#define FMC_SECM_EPAGE_MASK               ((uint32_t)0x03FF0000U)
/* FMC_OBR_SPC mask */
#define FMC_OBR_SPC_MASK                  ((uint32_t)0xFFFFFF00U)
/* FMC_OBUSER mask */
#define FMC_OBUSER_MASK                   ((uint32_t)0xFFFF0000U)
/* FMC_OBSTAT security protection mask */
#define FMC_OBSTAT_SPCSTAT_MASK           ((uint32_t)0x00000003U)
/* FMC_OBWRPx/FMC_SECMCFGx/FMC_DMPx/FMC_OFRG end page of region offset */
#define FMC_EPAGE_OFFSET                  ((uint32_t)16U)

/* return the FMC state */
static fmc_state_enum fmc_state_get(void);

/*!
    \brief      unlock the main FMC operation (API_ID(0x0001U))
                it is better to used in pairs with fmc_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_unlock(void)
{
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    if(RESET != (FMC_SECCTL & FMC_SECCTL_SECLK)) {
        /* write the FMC secure unlock key */
        FMC_SECKEY = UNLOCK_SECKEY0;
        FMC_SECKEY = UNLOCK_SECKEY1;
    }
    if(RESET != (FMC_CTL & FMC_CTL_LK)) {
        /* write the FMC unlock key */
        FMC_KEY = UNLOCK_KEY0;
        FMC_KEY = UNLOCK_KEY1;
    }
#else
    if(RESET != (FMC_CTL & FMC_CTL_LK)) {
        /* write the FMC unlock key */
        FMC_KEY = UNLOCK_KEY0;
        FMC_KEY = UNLOCK_KEY1;
    }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */
}

/*!
    \brief      lock the main FMC operation (API_ID(0x0002U))
                it is better to used in pairs with fmc_unlock after an operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_lock(void)
{
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    /* set the SECLK bit */
    FMC_SECCTL |= FMC_SECCTL_SECLK;
    /* set the LK bit */
    FMC_CTL |= FMC_CTL_LK;
#else
    /* set the LK bit */
    FMC_CTL |= FMC_CTL_LK;
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */
}

/*!
    \brief      FMC erase page (API_ID(0x0003U))
    \param[in]  page_address: target page address
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OBERR: option bytes error
      \arg        FMC_SECERR: secure program error, only available in secure mode
*/
fmc_state_enum fmc_page_erase(uint32_t page_address)
{
    fmc_state_enum fmc_state = FMC_TOERR;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_FMC_PAGE_VALID_ADDRESS(page_address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0003U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
        if(FMC_READY == fmc_state) {
            /* start page erase */
            FMC_SECCTL |= FMC_SECCTL_SECPER;
            FMC_SECADDR = page_address;
            FMC_SECCTL |= FMC_SECCTL_SECSTART;
            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the SECPER bit */
            FMC_SECCTL &= ~FMC_SECCTL_SECPER;
        }
#else
        if(FMC_READY == fmc_state) {
            /* start page erase */
            FMC_CTL |= FMC_CTL_PER;
            FMC_ADDR = page_address;
            FMC_CTL |= FMC_CTL_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the PER bit */
            FMC_CTL &= ~FMC_CTL_PER;
        }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      FMC erase whole chip (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OBERR: option bytes error
      \arg        FMC_SECERR: secure program error, only available in secure mode
*/
fmc_state_enum fmc_mass_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    if(FMC_READY == fmc_state) {
        /* start chip erase */
        FMC_SECCTL |= FMC_SECCTL_SECMER;
        FMC_SECCTL |= FMC_SECCTL_SECSTART;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the SECMER bit */
        FMC_SECCTL &= ~FMC_SECCTL_SECMER;
    }
#else
    if(FMC_READY == fmc_state) {
        /* start chip erase */
        FMC_CTL |= FMC_CTL_MER;
        FMC_CTL |= FMC_CTL_START;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the MER bit */
        FMC_CTL &= ~FMC_CTL_MER;
    }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */

    /* return the FMC state  */
    return fmc_state;
}

/*!
    \brief      FMC program a word at the corresponding address (API_ID(0x0004U))
    \param[in]  address: address to program
    \param[in]  data: word to program
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OBERR: option bytes error
      \arg        FMC_SECERR: secure program error, only available in secure mode
*/
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data)
{
    fmc_state_enum fmc_state = FMC_TOERR;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_FMC_FLASH_WORD_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0004U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
        if(FMC_READY == fmc_state) {
            /* set the SECPG bit to start program */
            FMC_SECCTL |= FMC_SECCTL_SECPG;
            REG32(address) = data;
            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the SECPG bit */
            FMC_SECCTL &= ~FMC_SECCTL_SECPG;
        }
#else
        if(FMC_READY == fmc_state) {
            /* set the PG bit to start program */
            FMC_CTL |= FMC_CTL_PG;
            REG32(address) = data;
            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the PG bit */
            FMC_CTL &= ~FMC_CTL_PG;
        }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      FMC program data continuously at the corresponding address (API_ID(0x0005U))
    \param[in]  address: address to program, must be 4-byte aligned
    \param[in]  data: data buffer to program
    \param[in]  size: data buffer size in words
    \param[out] none
    \retval     fmc_state_enum
*/
fmc_state_enum fmc_continuous_program(uint32_t address, uint32_t data[], uint32_t size)
{
    fmc_state_enum fmc_state = FMC_TOERR;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(data)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0005U), ERR_PARAM_POINTER);
    } else if(NOT_FMC_FLASH_WORD_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0005U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
        if(FMC_READY == fmc_state) {
            /* set the PG bit to start program */
            FMC_SECCTL |= FMC_SECCTL_SECPG;

            for(uint32_t i = 0U; i < size; i++) {
                REG32(address) = data[i];
                address += 4U;
            }

            /* reset the PG bit */
            FMC_SECCTL &= ~FMC_SECCTL_SECPG;
        }
#else /* __ARM_FEATURE_CMSE */
        if(FMC_READY == fmc_state) {
            /* set the PG bit to start program */
            FMC_CTL |= FMC_CTL_PG;

            for(uint32_t i = 0U; i < size; i++) {
                REG32(address) = data[i];
                address += 4U;
            }

            /* reset the PG bit */
            FMC_CTL &= ~FMC_CTL_PG;
        }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      enable SRAM1 reset automatically function (API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sram1_reset_enable(void)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        FMC_OBR |= (uint32_t)(FMC_OBR_SRAM1_RST);
        /* start option bytes modification */
        FMC_CTL |= FMC_CTL_OBSTART;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }
}

/*!
    \brief      disable SRAM1 reset automatically function (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sram1_reset_disable(void)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        FMC_OBR &= ~(uint32_t)(FMC_OBR_SRAM1_RST);
        /* start option bytes modification */
        FMC_CTL |= FMC_CTL_OBSTART;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }
}

/*!
    \brief      enable the privileged access (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_privilege_enable(void)
{
    FMC_PRIVCFG |= (uint32_t)(FMC_PRIVCFG_FMC_PRIV);
}
/*!
    \brief      disable the privileged access (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_privilege_disable(void)
{
    FMC_PRIVCFG &= ~(uint32_t)(FMC_PRIVCFG_FMC_PRIV);
}

/*!
    \brief      unlock the option bytes operation (API_ID(0x000BU))
                it is better to used in pairs with ob_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_unlock(void)
{
    if(RESET == (FMC_CTL & FMC_CTL_OBWEN)) {
        /* write the FMC ob unlock key */
        FMC_OBKEY = UNLOCK_KEY0;
        FMC_OBKEY = UNLOCK_KEY1;
    }
}

/*!
    \brief      lock the option bytes operation (API_ID(0x000CU))
                it is better to used in pairs with ob_unlock after an operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_lock(void)
{
    /* reset the OBWEN bit */
    FMC_CTL &= ~FMC_CTL_OBWEN;
}

/*!
    \brief      send option bytes modification start command (API_ID(0x000DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_start(void)
{
    /* set the OB_START bit in FMC_CTL register to start option bytes modification */
    FMC_CTL |= FMC_CTL_OBSTART;
}

/*!
    \brief      reload option bytes (API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_reload(void)
{
    /* set the FMC_CTL_OBRLD bit in FMC_CTL register to reload option bytes */
    FMC_CTL |= FMC_CTL_OBRLD;
}

/*!
    \brief      configure security protection (API_ID(0x000FU))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_spc: specify security protection
                only one parameter can be selected which is shown as below:
      \arg        FMC_NSPC: no security protection
      \arg        FMC_SPC_P0_5: security protection level 0.5
      \arg        FMC_SPC_P1: security protection level 1
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OBERR: option bytes error
      \arg        FMC_SECERR: secure program error, only available in secure mode
*/
fmc_state_enum ob_security_protection_config(uint8_t ob_spc)
{
    fmc_state_enum fmc_state = FMC_TOERR;
    
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    if(FMC_READY == fmc_state) {
        FMC_OBR &= FMC_OBR_SPC_MASK;
        FMC_OBR |= ob_spc;
        /* start option bytes modification */
        FMC_CTL |= FMC_CTL_OBSTART;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }
    /* return the FMC state */
    return fmc_state;
}

#if defined (GD32F5HC)
/*!
    \brief      configure the option byte for fwdgt/deepsleep/standby (API_ID(0x0010U))
    \param[in]  ob_fwdgt: option byte watchdog value
                only one parameter can be selected which is shown as below:
      \arg        OB_FWDGT_SW: software free watchdog
      \arg        OB_FWDGT_HW: hardware free watchdog
    \param[in]  ob_deepsleep: option byte deepsleep reset value
                only one parameter can be selected which is shown as below:
      \arg        OB_DEEPSLEEP_RUN: FWDGT is running in system deepsleep mode
      \arg        OB_DEEPSLEEP_SUSPEND: FWDGT is suspend in system deepsleep mode
    \param[in]  ob_stdby: option byte standby reset value
                only one parameter can be selected which is shown as below:
      \arg        OB_STDBY_RUN: FWDGT is running in system standby mode
      \arg        OB_STDBY_SUSPEND: FWDGT is suspend in system standby mode
    \param[out] none
    \retval     none
*/
void ob_wdgt_config(uint32_t ob_fwdgt, uint32_t ob_deepsleep, uint32_t ob_stdby)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        FMC_OBR1 &= ~(FMC_OBR1_NWDG_HW | FMC_OBR1_FWDGSPD_DPSLP | FMC_OBR1_FWDGSPD_STDBY);
        FMC_OBR1 |= (ob_fwdgt | ob_deepsleep | ob_stdby);
        /* start option bytes modification */
        FMC_CTL |= FMC_CTL_OBSTART;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }
}

/*!
    \brief      configure the option byte for boot0/boot1 (API_ID(0x0011U))
    \param[in]  swboot0: SWBOOT0 option bits
                only one parameter can be selected which is shown as below:
      \arg        OB_BOOT0_NBOOT0: Select nBOOT0 as BOOT0 signal
      \arg        OB_BOOT0_PC8: Select PC8 pin as BOOT0 signal
    \param[in]  boot0: BOOT0 option bits (only valid when swboot0 is OB_BOOT0_NBOOT0)
                only one parameter can be selected which is shown as below:
      \arg        OB_BOOT0_1: BOOT0 is 1
      \arg        OB_BOOT0_0: BOOT0 is 0
    \param[in]  swboot1: SWBOOT1 option bit
                only one parameter can be selected which is shown as below:
      \arg        OB_BOOT1_NBOOT1: Select nBOOT1 as BOOT1 signal
      \arg        OB_BOOT1_PA14: Select PA14 pin as BOOT1 signal
    \param[in]  boot1: BOOT1 option bits (only valid when swboot1 is OB_BOOT1_NBOOT1)
                only one parameter can be selected which is shown as below:
      \arg        OB_BOOT1_1: BOOT1 is 1
      \arg        OB_BOOT1_0: BOOT1 is 0
    \param[out] none
    \retval     none
*/
void ob_boot_config(uint32_t swboot0, uint32_t boot0, uint32_t swboot1, uint32_t boot1)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        FMC_OBR1 &= ~(FMC_OBR1_NSWBOOT0 | FMC_OBR1_NBOOT0 | FMC_OBR1_SWBOOT1 | FMC_OBR1_NBOOT1);
        FMC_OBR1 |= (swboot0 | boot0 | swboot1 | boot1);
        /* start option bytes modification */
        FMC_CTL |= FMC_CTL_OBSTART;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }
}
#endif /* defined (GD32F5HC) */

/*!
    \brief      enable trustzone (API_ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OBERR: option bytes error
      \arg        FMC_SECERR: secure program error, only available in secure mode
*/
fmc_state_enum ob_trustzone_enable(void)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        FMC_OBR |= (uint32_t)(FMC_OBR_TZEN);
        /* start option bytes modification */
        FMC_CTL |= FMC_CTL_OBSTART;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      disable trustzone (API_ID(0x0013U))
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus ob_trustzone_disable(void)
{
    ErrStatus err;
    uint32_t reg;
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    FlagStatus flag_spc1 = ob_security_protection_flag_get(OB_FLAG_SPC1);
    FlagStatus flag_spc0_5 = ob_security_protection_flag_get(OB_FLAG_SPC0_5);
    
    if(flag_spc1 || flag_spc0_5) {
        /* TZEN bit must be cleared at the same time that flash security protection return to unprotected */
        reg = FMC_OBR;
        reg &= ~(uint32_t)(FMC_OBR_TZEN);
        reg &= FMC_OBR_SPC_MASK;
        reg |= (uint32_t)(FMC_NSPC);

        if(FMC_READY == fmc_state) {
            FMC_OBR = reg;
            /* start option bytes modification */
            FMC_CTL |= FMC_CTL_OBSTART;
        }
        err = SUCCESS;
    } else {
        err = ERROR;
    }
    return err;
}

/*!
    \brief      program option bytes USER (API_ID(0x0014U))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_user: option bytes user value
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OBERR: option bytes error
      \arg        FMC_SECERR: secure program error, only available in secure mode
*/
fmc_state_enum ob_user_write(uint16_t ob_user)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        FMC_OBUSER &= FMC_OBUSER_MASK;
        FMC_OBUSER |= ob_user ;
        /* start option bytes modification */
        FMC_CTL |= FMC_CTL_OBSTART;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure write protection pages (API_ID(0x0015U))
    \param[in]  wrp_spage: start page of write protection area, 0~512
    \param[in]  wrp_epage: end page of write protection area, 0~512
    \param[in]  wrp_register_index
                only one parameter can be selected which are shown as below:
      \arg        OBWRP_INDEX0: option byte write protection area register 0
      \arg        OBWRP_INDEX1: option byte write protection area register 1
    \param[out] none
    \retval     none
*/
fmc_state_enum ob_write_protection_config(uint32_t wrp_spage, uint32_t wrp_epage, uint32_t wrp_register_index)
{
    fmc_state_enum fmc_state = FMC_TOERR;
    
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    if(FMC_READY == fmc_state) {
        switch(wrp_register_index) {
        case OBWRP_INDEX0:
            FMC_OBWRP0 = 0U;
            FMC_OBWRP0 |= (wrp_spage & FMC_OBWRP0_WRP0_SPAGE);
            FMC_OBWRP0 |= ((wrp_epage << FMC_EPAGE_OFFSET) & FMC_OBWRP0_WRP0_EPAGE);
            break;
        case OBWRP_INDEX1:
            FMC_OBWRP1 = 0U;
            FMC_OBWRP1 |= (wrp_spage & FMC_OBWRP1_WRP1_SPAGE);
            FMC_OBWRP1 |= ((wrp_epage << FMC_EPAGE_OFFSET) & FMC_OBWRP1_WRP1_EPAGE);
            break;
        default :
            break;
        }
        /* start option bytes modification */
        FMC_CTL |= FMC_CTL_OBSTART;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure secure mark pages (API_ID(0x0016U))
    \param[in]  secm_spage: start page of secure mark area, 0~0x03FF
    \param[in]  secm_epage: end page of secure mark area, 0~0x03FF
    \param[in]  secm_register_index
                only one parameter can be selected which are shown as below:
      \arg        SECM_INDEX0: secure mark configuration register 0
      \arg        SECM_INDEX1: secure mark configuration register 1
      \arg        SECM_INDEX2: secure mark configuration register 2
      \arg        SECM_INDEX3: secure mark configuration register 3
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OBERR: option bytes error
      \arg        FMC_SECERR: secure program error, only available in secure mode
*/
void ob_secmark_config(uint32_t secm_spage, uint32_t secm_epage, uint32_t secm_register_index)
{
    fmc_state_enum fmc_state;

    switch(secm_register_index) {
    case SECM_INDEX0:
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        if(FMC_READY == fmc_state) {
            FMC_SECMCFG0 = 0U;
            FMC_SECMCFG0 |= (secm_spage & FMC_SECMCFG0_SECM0_SPAGE);
            FMC_SECMCFG0 |= ((secm_epage << FMC_EPAGE_OFFSET) & FMC_SECMCFG0_SECM0_EPAGE);
            /* start option bytes modification */
            FMC_CTL |= FMC_CTL_OBSTART;
        }
        break;
    case SECM_INDEX1:
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        if(FMC_READY == fmc_state) {
            FMC_SECMCFG1 = 0U;
            FMC_SECMCFG1 |= (secm_spage & FMC_SECMCFG1_SECM1_SPAGE);
            FMC_SECMCFG1 |= ((secm_epage << FMC_EPAGE_OFFSET) & FMC_SECMCFG1_SECM1_EPAGE);
            /* start option bytes modification */
            FMC_CTL |= FMC_CTL_OBSTART;
        }
        break;
    case SECM_INDEX2:
        FMC_SECMCFG2 = 0U;
        FMC_SECMCFG2 |= (secm_spage & FMC_SECMCFG2_SECM2_SPAGE);
        FMC_SECMCFG2 |= ((secm_epage << FMC_EPAGE_OFFSET) & FMC_SECMCFG2_SECM2_EPAGE);
        break;
    case SECM_INDEX3:
        FMC_SECMCFG3 = 0U;
        FMC_SECMCFG3 |= (secm_spage & FMC_SECMCFG3_SECM3_SPAGE);
        FMC_SECMCFG3 |= ((secm_epage << FMC_EPAGE_OFFSET) & FMC_SECMCFG3_SECM3_EPAGE);
        break;
    default :
        break;
    }
}

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
/*!
    \brief      enable DMP region access right (API_ID(0x0017U))
    \param[in]  dmp_register_index
                only one parameter can be selected which are shown as below:
      \arg        DMP_INDEX0: secure DMP configuration register 0
      \arg        DMP_INDEX1: secure DMP configuration register 1
    \param[out] none
    \retval     none
*/
void ob_dmp_access_enable(uint32_t dmp_register_index)
{
    nvic_system_reset();
}

/*!
    \brief      disable DMP region access right (API_ID(0x0018U))
    \param[in]  DMP_register_index
                only one parameter can be selected which are shown as below:
      \arg        DMP_INDEX0: secure DMP configuration register 0
      \arg        DMP_INDEX1: secure DMP configuration register 1
    \param[out] none
    \retval     none
*/
void ob_dmp_access_disable(uint32_t DMP_register_index)
{
    switch(DMP_register_index) {
    case DMP_INDEX0:
        FMC_DMPCTL |= (uint32_t)(FMC_DMPCTL_DMP0_ACCCFG);
        break;
    case DMP_INDEX1:
        FMC_DMPCTL |= (uint32_t)(FMC_DMPCTL_DMP1_ACCCFG);
        break;
    default :
        break;
    }
}
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */

/*!
    \brief      configure DMP pages (API_ID(0x0019U))
    \param[in]  dmp_epage: end page of secure DMP mark area 0~0x03FF
    \param[in]  dmp_register_index
                only one parameter can be selected which are shown as below:
      \arg        DMP_INDEX0: secure DMP configuration register 0
      \arg        DMP_INDEX1: secure DMP configuration register 1
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus ob_dmp_config(uint32_t dmp_epage, uint32_t dmp_register_index)
{
    ErrStatus status = ERROR;
    uint32_t secm_epage;

    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    if(FMC_READY == fmc_state) {
        switch(dmp_register_index) {
        case DMP_INDEX0:
            secm_epage = (FMC_SECMCFG0 & FMC_SECMCFG0_SECM0_EPAGE) >> FMC_EPAGE_OFFSET;
            if(secm_epage > dmp_epage) {
                FMC_DMP0 = 0U;
                FMC_DMP0 |= ((dmp_epage << FMC_EPAGE_OFFSET) & FMC_DMP0_DMP0_EPAGE);
                /* start option bytes modification */
                FMC_CTL |= FMC_CTL_OBSTART;
                status = SUCCESS;
            }
            break;
        case DMP_INDEX1:
            secm_epage = (FMC_SECMCFG1 & FMC_SECMCFG1_SECM1_EPAGE) >> FMC_EPAGE_OFFSET;
            if(secm_epage > dmp_epage) {
                FMC_DMP1 = 0U;
                FMC_DMP1 |= ((dmp_epage << FMC_EPAGE_OFFSET) & FMC_DMP1_DMP1_EPAGE);
                /* start option bytes modification */
                FMC_CTL |= FMC_CTL_OBSTART;
                status = SUCCESS;
            }
            break;
        default :
            break;
        }
    }
    return status;
}

/*!
    \brief      enable DMP function (API_ID(0x001AU))
    \param[in]  dmp_register_index:
                only one parameter can be selected which are shown as below:
      \arg        DMP_INDEX0: secure DMP configuration register 0
      \arg        DMP_INDEX1: secure DMP configuration register 1
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OBERR: option bytes error
      \arg        FMC_SECERR: secure program error, only available in secure mode
*/
fmc_state_enum ob_dmp_enable(uint32_t dmp_register_index)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        switch(dmp_register_index) {
        case DMP_INDEX0:
            FMC_DMP0 |= (uint32_t)(FMC_DMP0_DMP0EN);
            break;
        case DMP_INDEX1:
            FMC_DMP1 |= (uint32_t)(FMC_DMP1_DMP1EN);
            break;
        default :
            break;
        }
        /* start option bytes modification */
        FMC_CTL |= FMC_CTL_OBSTART;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      disable DMP function (API_ID(0x001BU))
    \param[in]  dmp_register_index:
                only one parameter can be selected which are shown as below:
      \arg        DMP_INDEX0: secure DMP configuration register 0
      \arg        DMP_INDEX1: secure DMP configuration register 1
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OBERR: option bytes error
      \arg        FMC_SECERR: secure program error, only available in secure mode
*/
fmc_state_enum ob_dmp_disable(uint32_t dmp_register_index)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        switch(dmp_register_index) {
        case DMP_INDEX0:
            FMC_DMP0 &= (uint32_t)(~FMC_DMP0_DMP0EN);
            break;
        case DMP_INDEX1:
            FMC_DMP1 &= (uint32_t)(~FMC_DMP1_DMP1EN);
            break;
        default :
            break;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure NO-RTDEC pages (API_ID(0x001CU))
    \param[in]  nodec_spage: start page of NO-RTDEC area, 0~0x03FF
    \param[in]  nodec_epage: end page of NO-RTDEC area, 0~0x03FF
    \param[in]  nodec_register_index
                only one parameter can be selected which are shown as below:
      \arg        NODEC_INDEX0: NO-RTDEC region register 0
      \arg        NODEC_INDEX1: NO-RTDEC region register 1
      \arg        NODEC_INDEX2: NO-RTDEC region register 2
      \arg        NODEC_INDEX3: NO-RTDEC region register 3
    \param[out] none
    \retval     none
*/
void fmc_no_rtdec_config(uint32_t nodec_spage, uint32_t nodec_epage, uint32_t nodec_register_index)
{
    switch(nodec_register_index) {
    case NODEC_INDEX0:
        FMC_NODEC0 = 0U;
        FMC_NODEC0 |= (nodec_spage & FMC_NODEC0_NODEC0_SPAGE);
        FMC_NODEC0 |= ((nodec_epage << FMC_EPAGE_OFFSET) & FMC_NODEC0_NODEC0_EPAGE);
        break;
    case NODEC_INDEX1:
        FMC_NODEC1 = 0U;
        FMC_NODEC1 |= (nodec_spage & FMC_NODEC1_NODEC1_SPAGE);
        FMC_NODEC1 |= ((nodec_epage << FMC_EPAGE_OFFSET) & FMC_NODEC1_NODEC1_EPAGE);
        break;
    case NODEC_INDEX2:
        FMC_NODEC2 = 0U;
        FMC_NODEC2 |= (nodec_spage & FMC_NODEC2_NODEC2_SPAGE);
        FMC_NODEC2 |= ((nodec_epage << FMC_EPAGE_OFFSET) & FMC_NODEC2_NODEC2_EPAGE);
        break;
    case NODEC_INDEX3:
        FMC_NODEC3 = 0U;
        FMC_NODEC3 |= (nodec_spage & FMC_NODEC3_NODEC3_SPAGE);
        FMC_NODEC3 |= ((nodec_epage << FMC_EPAGE_OFFSET) & FMC_NODEC3_NODEC3_EPAGE);
        break;
    default :
        break;
    }
}

/*!
    \brief      configure offset region (API_ID(0x001DU))
    \param[in]  of_spage: start page of offset region, 0~0x1FFF
    \param[in]  of_epage: end page of offset region, 0~0x1FFF
    \param[out] none
    \retval     none
*/
void fmc_offset_region_config(uint32_t of_spage, uint32_t of_epage)
{
    FMC_OFRG = 0U;
    FMC_OFRG |= (of_spage & FMC_OFRG_OF_SPAGE);
    FMC_OFRG |= ((of_epage << FMC_EPAGE_OFFSET) & FMC_OFRG_OF_EPAGE);
}

/*!
    \brief      configure offset value (API_ID(0x001EU))
    \param[in]  of_value: offset value, 0~0x1FFF
    \param[out] none
    \retval     none
*/
void fmc_offset_value_config(uint32_t of_value)
{
    FMC_OFVR = 0U;
    FMC_OFVR |= (of_value & FMC_OFVR_OF_VALUE);
}

/*!
    \brief      get option bytes write protection state, only applies to get the status of write/erase protection setting by EFUSE (API_ID(0x001FU))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ob_write_protection_get(void)
{
    FlagStatus status = RESET;

    if(FMC_OBSTAT & FMC_OBSTAT_WP) {
        status = SET;
    } else {
        status = RESET;
    }

    /* return the state of corresponding FMC flag */
    return status;
}

/*!
    \brief      get the value of option bytes USER (API_ID(0x0020U))
    \param[in]  none
    \param[out] none
    \retval     the option bytes USER value
*/
uint16_t ob_user_get(void)
{
    /* return the FMC user option bytes value */
    return (uint16_t)FMC_OBUSER;
}

/*!
    \brief      get the FMC option bytes security protection state (API_ID(0x0021U))
    \param[in]  spc_state
                only one parameter can be selected which is shown as below:
      \arg        OB_FLAG_NSPC: option bytes security protection level 0
      \arg        OB_FLAG_SPC0_5: option bytes security protection level 0.5
      \arg        OB_FLAG_SPC1: option bytes security protection level 1
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ob_security_protection_flag_get(uint32_t spc_state)
{
    FlagStatus state = RESET;

    spc_state &= FMC_OBSTAT_SPCSTAT_MASK; /* MASK for SPC state bits */

    if(OB_FLAG_NSPC == spc_state) {
        if(FMC_OBSTAT & FMC_OBSTAT_SPCSTAT_MASK) {
            state = RESET;
        } else {
            state = SET;
        }
    } else if(OB_FLAG_SPC0_5 == spc_state) {
        if(OB_FLAG_SPC0_5 == (FMC_OBSTAT & FMC_OBSTAT_SPCSTAT_MASK)) {
            state = SET;
        } else {
            state = RESET;
        }
    } else if(OB_FLAG_SPC1 == spc_state) {
        if(OB_FLAG_SPC1 == (FMC_OBSTAT & FMC_OBSTAT_SPCSTAT_MASK)) {
            state = SET;
        } else {
            state = RESET;
        }
    } else {
        state = RESET;
    }

    /* return the state of corresponding FMC flag */
    return state;
}

/*!
    \brief      get trustzone state (API_ID(0x0022U))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ob_trustzone_state_get(void)
{
    FlagStatus state = RESET;

    if(FMC_OBSTAT & FMC_OBSTAT_TZEN_STAT) {
        state = SET;
    } else {
        state = RESET;
    }

    /* return the state of corresponding FMC flag */
    return state;
}

/*!
    \brief      get the state of whether the option byte exist or not (API_ID(0x0023U))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ob_exist_state_get(void)
{
    FlagStatus state = RESET;

    if(FMC_OBSTAT & FMC_OBSTAT_FMCOB) {
        state = SET;
    } else {
        state = RESET;
    }

    /* return the state of corresponding FMC flag */
    return state;
}

/*!
    \brief      get FMC flag status (API_ID(0x0024U))
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_BUSY: FMC busy flag
      \arg        FMC_FLAG_OBERR: FMC option bytes error flag
      \arg        FMC_FLAG_WPERR: FMC erase/program protection error flag
      \arg        FMC_FLAG_END: FMC end of operation flag
      \arg        FMC_FLAG_SECERR: FMC secure error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    if(FMC_FLAG_OBERR == flag) {
        if(FMC_STAT & flag) {
            status = SET;
        }
    } else {
        if(FMC_SECSTAT & flag) {
            status = SET;
        }
    }
#else
    if(FMC_STAT & flag) {
        status = SET;
    }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */
    /* return the state of corresponding FMC flag */
    return status;
}

/*!
    \brief      clear the FMC flag (API_ID(0x0025U))
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_OBERR: FMC option bytes error flag
      \arg        FMC_FLAG_WPERR: FMC erase/program protection error flag
      \arg        FMC_FLAG_END: FMC end of operation flag
      \arg        FMC_FLAG_SECERR: FMC secure error flag
    \param[out] none
    \retval     none
*/
void fmc_flag_clear(uint32_t flag)
{
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    if(FMC_FLAG_OBERR == flag) {
        FMC_STAT = flag;
    } else {
        /* clear the flags */
        FMC_SECSTAT = flag;
    }
#else
    /* clear the flags */
    FMC_STAT = flag;
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */
}

/*!
    \brief      enable FMC interrupt (API_ID(0x0026U))
    \param[in]  interrupt: the FMC interrupt
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END: FMC secure/non-secure end of operation interrupt
      \arg        FMC_INT_ERR: FMC secure/non-secure error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_enable(uint32_t interrupt)
{
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    FMC_SECCTL |= interrupt;
#else
    FMC_CTL |= interrupt;
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */
}

/*!
    \brief      disable FMC interrupt (API_ID(0x0027U))
    \param[in]  interrupt: the FMC interrupt
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END: FMC secure/non-secure end of operation interrupt
      \arg        FMC_INT_ERR: FMC secure/non-secure error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_disable(uint32_t interrupt)
{
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    FMC_SECCTL &= ~(uint32_t)interrupt;
#else
    FMC_CTL &= ~(uint32_t)interrupt;
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */
}

/*!
    \brief      get FMC interrupt flag (API_ID(0x0028U))
    \param[in]  flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_WPERR: FMC secure/non-secure erase/program protection error interrupt flag
      \arg        FMC_INT_FLAG_END: FMC secure/non-secure end of operation interrupt flag
      \arg        FMC_INT_FLAG_SECERR: FMC secure error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_interrupt_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    if(FMC_SECSTAT & flag) {
        status = SET;
    }
#else
    if(FMC_STAT & flag) {
        status = SET;
    }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */
    /* return the state of corresponding FMC flag */
    return status;
}

/*!
    \brief      clear FMC interrupt flag (API_ID(0x0029U))
    \param[in]  flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_WPERR: FMC secure/non-secure erase/program protection error interrupt flag
      \arg        FMC_INT_FLAG_END: FMC secure/non-secure end of operation interrupt flag
      \arg        FMC_INT_FLAG_SECERR: FMC secure error flag
    \param[out] none
    \retval     none
*/
void fmc_interrupt_flag_clear(uint32_t flag)
{
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    /* clear the flags */
    FMC_SECSTAT = flag;
#else
    /* clear the flag */
    FMC_STAT = flag;
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */
}

/*!
    \brief      get the FMC state (API_ID(0x002AU))
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
static fmc_state_enum fmc_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    if((uint32_t)0x00U != (FMC_SECSTAT & (FMC_SECSTAT_SECBUSY))) {
        fmc_state = FMC_BUSY;
    } else {
        if((uint32_t)0x00U != (FMC_SECSTAT & (FMC_SECSTAT_SECERR))) {
            fmc_state = FMC_SECERR;
        } else {
            if((uint32_t)0x00U != (FMC_SECSTAT & (FMC_SECSTAT_SECWPERR))) {
                fmc_state = FMC_WPERR;
            } else {
                if((uint32_t)0x00U != (FMC_STAT & (FMC_STAT_OBERR))) {
                    fmc_state = FMC_OBERR;
                }
            }
        }
    }
#else
    if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_BUSY)) {
        fmc_state = FMC_BUSY;
    } else {
        if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_WPERR)) {
            fmc_state = FMC_WPERR;
        } else {
            if((uint32_t)0x00U != (FMC_STAT & (FMC_STAT_OBERR))) {
                fmc_state = FMC_OBERR;
            }
        }
    }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC is ready or not (API_ID(0x002BU))
    \param[in]  timeout: timeout count
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum fmc_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_BUSY;

    /* wait for FMC ready */
    do {
        /* get FMC state */
        fmc_state = fmc_state_get();
        timeout--;
    } while((FMC_BUSY == fmc_state) && (0x00U != timeout));

    if(FMC_BUSY == fmc_state) {
        fmc_state = FMC_TOERR;
    }

    /* return the FMC state */
    return fmc_state;
}
