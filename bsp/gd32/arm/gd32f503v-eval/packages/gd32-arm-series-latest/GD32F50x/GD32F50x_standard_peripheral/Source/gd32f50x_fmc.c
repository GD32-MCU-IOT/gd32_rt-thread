/*!
    \file    gd32f50x_fmc.c
    \brief   FMC driver

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


#include "gd32f50x_fmc.h"

/* OB_USER_RESET_VALUE: Default reset value for the user option byte (0x9F) */
#define OB_USER_RESET_VALUE     ((uint32_t)0x9FU)
/* OB_USER_POS: Bit position of the user option byte (bit 2) */
#define OB_USER_POS             ((uint32_t)2U)
/* OB_DATA_RESET_VALUE: Default reset value for the user data byte (0xFF) */
#define OB_DATA_RESET_VALUE     ((uint32_t)0xFFFFU)
/* OB_DATA_POS: Bit position of the user data byte (bit 10) */
#define OB_DATA_POS             ((uint32_t)10U)

/*!
    \brief      unlock the main FMC operation (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_unlock(void)
{
    if((RESET != (FMC_CTL0 & FMC_CTL0_LK))) {
        /* write the FMC unlock key */
        FMC_KEY0 = UNLOCK_KEY0;
        FMC_KEY0 = UNLOCK_KEY1;
    }
    if(FMC_BANK0_SIZE < FMC_SIZE) {
        /* write the FMC unlock key */
        if(RESET != (FMC_CTL1 & FMC_CTL1_LK)) {
            FMC_KEY1 = UNLOCK_KEY0;
            FMC_KEY1 = UNLOCK_KEY1;
        }
    }
}

/*!
    \brief      unlock the FMC bank0 operation (API_ID(0x0002U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_bank0_unlock(void)
{
    if((RESET != (FMC_CTL0 & FMC_CTL0_LK))) {
        /* write the FMC unlock key */
        FMC_KEY0 = UNLOCK_KEY0;
        FMC_KEY0 = UNLOCK_KEY1;
    }
}

/*!
    \brief      unlock the FMC bank1 operation (API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_bank1_unlock(void)
{
    if((RESET != (FMC_CTL1 & FMC_CTL1_LK))) {
        /* write the FMC unlock key */
        FMC_KEY1 = UNLOCK_KEY0;
        FMC_KEY1 = UNLOCK_KEY1;
    }
}

/*!
    \brief      lock the main FMC operation (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_lock(void)
{
    /* set the LK bit */
    FMC_CTL0 |= FMC_CTL0_LK;
    if(FMC_BANK0_SIZE < FMC_SIZE) {
        /* set the LK bit */
        FMC_CTL1 |= FMC_CTL1_LK;
    }
}

/*!
    \brief      lock the FMC bank0 operation (API_ID(0x0005U))
                this function can be used for all gd32f50x devices.
                for gd32f50x with flash more than 512KB, this function locks bank0.
                for gd32f50x with flash no more than 512KB and it is equivalent to fmc_lock function.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_bank0_lock(void)
{
    /* set the LK bit*/
    FMC_CTL0 |= FMC_CTL0_LK;
}

/*!
    \brief      lock the FMC bank1 operation (API_ID(0x0006U))
                this function can be used for gd32f50x with flash more than 512KB.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_bank1_lock(void)
{
    /* set the LK bit*/
    FMC_CTL1 |= FMC_CTL1_LK;
}

/*!
    \brief      erase page (API_ID(0x0007U))
    \param[in]  page_address: the page address to be erased.
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_page_erase(uint32_t page_address)
{
    fmc_state_enum fmc_state;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_PAGE_VALID_ADDRESS(page_address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(FMC_BANK0_SIZE < FMC_SIZE) {
            if(FMC_BANK0_END_ADDRESS > page_address) {
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                /* if the last operation is completed, start page erase */
                if(FMC_READY == fmc_state) {
                    FMC_CTL0 |= FMC_CTL0_PER;
                    FMC_ADDR0 = page_address;
                    FMC_CTL0 |= FMC_CTL0_START;
                    __NOP();
                    __NOP();
                    /* wait for the FMC ready */
                    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                    /* reset the PER bit */
                    FMC_CTL0 &= ~FMC_CTL0_PER;
                }
            } else {
                /* wait for the FMC ready */
                fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
                /* if the last operation is completed, start page erase */
                if(FMC_READY == fmc_state) {
                    FMC_CTL1 |= FMC_CTL1_PER;
                    FMC_ADDR1 = page_address;
                    FMC_CTL1 |= FMC_CTL1_START;
                    __NOP();
                    __NOP();
                    /* wait for the FMC ready */
                    fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
                    /* reset the PER bit */
                    FMC_CTL1 &= ~FMC_CTL1_PER;
                }
            }
        } else {
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            /* if the last operation is completed, start page erase */
            if(FMC_READY == fmc_state) {
                FMC_CTL0 |= FMC_CTL0_PER;
                FMC_ADDR0 = page_address;
                FMC_CTL0 |= FMC_CTL0_START;
                __NOP();
                __NOP();
                /* wait for the FMC ready */
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PER bit */
                FMC_CTL0 &= ~FMC_CTL0_PER;
            }
        }
    }
    return fmc_state;
}

/*!
    \brief      erase whole chip (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_mass_erase(void)
{
    fmc_state_enum fmc_state;
    if(FMC_BANK0_SIZE < FMC_SIZE) {
        /* erase bank0 */
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
        if(FMC_READY == fmc_state) {
            /* start whole chip erase */
            FMC_CTL0 |= FMC_CTL0_MER;
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the MER bit */
            FMC_CTL0 &= ~FMC_CTL0_MER;
        }
        /* erase bank1 */
        fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
        if(FMC_READY == fmc_state) {
            /* start whole chip erase */
            FMC_CTL1 |= FMC_CTL1_MER;
            FMC_CTL1 |= FMC_CTL1_START;
            /* wait for the FMC ready */
            fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the MER bit */
            FMC_CTL1 &= ~FMC_CTL1_MER;
        }
    } else {
        /* erase bank0 */
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
        if(FMC_READY == fmc_state) {
            /* start whole chip erase */
            FMC_CTL0 |= FMC_CTL0_MER;
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the MER bit */
            FMC_CTL0 &= ~FMC_CTL0_MER;
        }
    }
    /* return the FMC state  */
    return fmc_state;
}

/*!
    \brief      erase bank0 (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_bank0_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        /* start FMC bank0 erase */
        FMC_CTL0 |= FMC_CTL0_MER;
        FMC_CTL0 |= FMC_CTL0_START;
        /* wait for the FMC ready */
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the MER bit */
        FMC_CTL0 &= ~FMC_CTL0_MER;
    }
    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      erase bank1 (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_bank1_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        /* start FMC bank1 erase */
        FMC_CTL1 |= FMC_CTL1_MER;
        FMC_CTL1 |= FMC_CTL1_START;
        /* wait for the FMC ready */
        fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the MER bit */
        FMC_CTL1 &= ~FMC_CTL1_MER;
    }
    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      program a word at the corresponding address (API_ID(0x000BU))
    \param[in]  address: address to program
    \param[in]  data: word to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_FLASH_WORD_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(FMC_BANK0_SIZE < FMC_SIZE) {
            if(FMC_BANK0_END_ADDRESS > address) {
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY == fmc_state) {
                    /* set the PG bit to start program */
                    FMC_CTL0 |= FMC_CTL0_PG;
                    REG32(address) = data;
                    /* wait for the FMC ready */
                    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                    /* reset the PG bit */
                    FMC_CTL0 &= ~FMC_CTL0_PG;
                }
            } else {
                fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY == fmc_state) {
                    /* set the PG bit to start program */
                    FMC_CTL1 |= FMC_CTL1_PG;
                    REG32(address) = data;
                    /* wait for the FMC ready */
                    fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
                    /* reset the PG bit */
                    FMC_CTL1 &= ~FMC_CTL1_PG;
                }
            }
        } else {
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                /* set the PG bit to start program */
                FMC_CTL0 |= FMC_CTL0_PG;
                REG32(address) = data;
                /* wait for the FMC ready */
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PG bit */
                FMC_CTL0 &= ~FMC_CTL0_PG;
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program a half word at the corresponding address (API_ID(0x000CU))
    \param[in]  address: address to program
    \param[in]  data: halfword to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_halfword_program(uint32_t address, uint16_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_FLASH_HALFWORD_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(FMC_BANK0_SIZE < FMC_SIZE) {
            if(FMC_BANK0_END_ADDRESS > address) {
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY == fmc_state) {
                    /* set the PG bit to start program */
                    FMC_CTL0 |= FMC_CTL0_PG;
                    REG16(address) = data;
                    /* wait for the FMC ready */
                    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                    /* reset the PG bit */
                    FMC_CTL0 &= ~FMC_CTL0_PG;
                }
            } else {
                fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY == fmc_state) {
                    /* set the PG bit to start program */
                    FMC_CTL1 |= FMC_CTL1_PG;
                    REG16(address) = data;
                    /* wait for the FMC ready */
                    fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
                    /* reset the PG bit */
                    FMC_CTL1 &= ~FMC_CTL1_PG;
                }
            }
        } else {
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            if(FMC_READY == fmc_state) {
                /* set the PG bit to start program */
                FMC_CTL0 |= FMC_CTL0_PG;
                REG16(address) = data;
                /* wait for the FMC ready */
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PG bit */
                FMC_CTL0 &= ~FMC_CTL0_PG;
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program a word at the OTP address (API_ID(0x000DU))
    \param[in]  address: OTP address to program
    \param[in]  data: word to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_otp_word_program(uint32_t address, uint32_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_OTP_WORD_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000DU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        if(((address >= OTP1_DATA_BLOCK_BASE_ADDRESS) && (address <= OTP1_DATA_BLOCK_END_ADDRESS)) || \
                ((address >= OTP2_DATA_BLOCK_BASE_ADDRESS) && (address <= OTP2_DATA_BLOCK_END_ADDRESS)) || \
                ((address >= OTP3_DATA_BLOCK_BASE_ADDRESS) && (address <= OTP3_DATA_BLOCK_END_ADDRESS)) || \
                ((address >= OTP3_LOCK_BLOCK_BASE_ADDRESS) && (address <= OTP3_LOCK_BLOCK_END_ADDRESS))) {
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            if(FMC_READY == fmc_state) {
                /* set the PG bit to start program */
                FMC_CTL0 |= FMC_CTL0_PG;
                REG32(address) = data;
                /* wait for the FMC ready */
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PG bit */
                FMC_CTL0 &= ~FMC_CTL0_PG;
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program a half word at the OTP address (API_ID(0x000EU))
    \param[in]  address: OTP address to program
    \param[in]  data: halfword to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_otp_half_word_program(uint32_t address, uint16_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_OTP_HALFWORD_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000EU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        if(((address >= OTP1_DATA_BLOCK_BASE_ADDRESS) && (address <= OTP1_DATA_BLOCK_END_ADDRESS)) || \
                ((address >= OTP2_DATA_BLOCK_BASE_ADDRESS) && (address <= OTP2_DATA_BLOCK_END_ADDRESS))) {
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            if(FMC_READY == fmc_state) {
                /* set the PG bit to start program */
                FMC_CTL0 |= FMC_CTL0_PG;
                REG16(address) = data;
                /* wait for the FMC ready */
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PG bit */
                FMC_CTL0 &= ~FMC_CTL0_PG;
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program a byte at the OTP address (API_ID(0x000FU))
    \param[in]  address: OTP address to program
    \param[in]  data: byte to program(0x00 - 0xFF)
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_otp_byte_program(uint32_t address, uint8_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_OTP_BYTE_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000FU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        /* check if address is in valid OTP regions */
        if(((address >= OTP0_DATA_BLOCK_BASE_ADDRESS) && (address <= OTP0_DATA_BLOCK_END_ADDRESS)) || \
                ((address >= OTP0_LOCK_BLOCK_BASE_ADDRESS) && (address <= OTP0_LOCK_BLOCK_END_ADDRESS)) || \
                ((address >= OTP1_DATA_BLOCK_BASE_ADDRESS) && (address <= OTP1_DATA_BLOCK_END_ADDRESS)) || \
                ((address >= OTP1_LOCK_BLOCK_BASE_ADDRESS) && (address <= OTP1_LOCK_BLOCK_END_ADDRESS)) || \
                ((address >= OTP2_DATA_BLOCK_BASE_ADDRESS) && (address <= OTP2_DATA_BLOCK_END_ADDRESS)) || \
                ((address >= OTP2_WLOCK_BLOCK_BASE_ADDRESS) && (address <= OTP2_RLOCK_BLOCK_END_ADDRESS))) {
            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            if(FMC_READY == fmc_state) {
                /* set the PG bit to start program */
                FMC_CTL0 |= FMC_CTL0_PG;
                REG8(address) = data;
                /* wait for the FMC ready */
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PG bit */
                FMC_CTL0 &= ~FMC_CTL0_PG;
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      enable no waiting time area load after system reset (API_ID(0x0010U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_nwa_enable(void)
{
    FMC_CTL0 |= FMC_CTL0_NWLDE;
}

/*!
    \brief      disable no waiting time area load after system reset (API_ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_nwa_disable(void)
{
    FMC_CTL0 &= ~FMC_CTL0_NWLDE;
}

/*!
    \brief      set OTP1 data block not be read (API_ID(0x0012U))
    \param[in]  block: specify OTP1 data block x not be read
                one or more parameters can be selected which are shown as below:
        \arg    OTP1_DATA_BLOCK_x: data block x(x = 0,1,2...15)
        \arg    OTP1_DATA_BLOCK_ALL: all data blocks
    \param[out] none
    \retval     none
*/
void otp1_read_disable(uint32_t block)
{
    FMC_OTP1CFG &= ~block;
}

/*!
    \brief      enable read lock block protection for OTP2 (API_ID(0x0013U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void otp2_rlock_enable(void)
{
    FMC_CTL0 |= FMC_CTL0_RLBE;
}

/*!
    \brief      enable deep power down mode when no operation (API_ID(0x0014U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_deep_power_down_enable(void)
{
    FMC_CTL0 |= FMC_CTL0_PWDN;
}

/*!
    \brief      disable deep power down mode when no operation (API_ID(0x0015U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_deep_power_down_disable(void)
{
    FMC_CTL0 &= ~FMC_CTL0_PWDN;
}

/*!
    \brief      unlock the option byte operation (API_ID(0x0016U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_unlock(void)
{
    if(RESET != (FMC_OBCTL0 & FMC_OBCTL0_OB_LK)) {
        /* write the FMC key */
        FMC_OBKEY = UNLOCK_KEY0;
        FMC_OBKEY = UNLOCK_KEY1;
    }
}

/*!
    \brief      lock the option byte operation (API_ID(0x0017U))
    \param[in]  none
    \param[out] none
    \retval     none
    \Note: Before setting FMC_OBCTL0_OB_LK, FMC_CTL0_LK should first be set using fmc_lock/fmc_bank0_lock.
*/
void ob_lock(void)
{
    /* set the OBWEN bit */
    FMC_OBCTL0 |= FMC_OBCTL0_OB_LK;
}

/*!
    \brief      send option byte change command (API_ID(0x0018U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_start(void)
{
    /* set the OB_START bit in OBCTL0 register */
    FMC_OBCTL0 |= FMC_OBCTL0_OB_START;
}

/*!
    \brief      erase the option byte (API_ID(0x0019U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
    if(FMC_READY == fmc_state) {
        /* reset the OBCTL0_SPC */
        FMC_OBCTL0 &= ~FMC_OBCTL0_SPC;
        FMC_OBCTL0 |= (FMC_NSPC & FMC_OBCTL0_SPC);
        /* reset the NWDG_HW, NRST_DPSLP, NRST_STDBY, BB and DATA*/
        FMC_OBCTL1 = (OB_USER_RESET_VALUE << OB_USER_POS) | (OB_DATA_RESET_VALUE << OB_DATA_POS);
        /* reset wp value */
        FMC_OBCTL2 |= OB_WP_ALL;
    }
}

/*!
    \brief      enable write protection (API_ID(0x001AU))
    \param[in]  ob_wp: specify pages to be write protected
                one or more parameters can be selected which are shown as below:
      \arg        OB_WP_x(x=0..31):page 2*x/ page2*x+1(x = 0,1,2...31)
      \arg        OB_WP_ALL: all pages
    \param[out] none
    \retval     SUCCESS or ERROR
*/
ErrStatus ob_write_protection_enable(uint32_t ob_wp)
{
    ErrStatus revet;
    fmc_state_enum fmc_state;
    /* wait for the FMC ready */
    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
    if(FMC_READY == fmc_state) {
        FMC_OBCTL2 &= ~ob_wp;
        revet = SUCCESS;
    } else {
        revet = ERROR;
    }
    return revet;
}

/*!
    \brief      disable write protection (API_ID(0x001BU))
    \param[in]  ob_wp: specify pages to be write protected
                one or more parameters can be selected which are shown as below:
      \arg        OB_WP_x(x=0..31):page 2*x/ page2*x+1(x = 0,1,2...31)
      \arg        OB_WP_ALL: all pages
    \param[out] none
    \retval     SUCCESS or ERROR
*/
ErrStatus ob_write_protection_disable(uint32_t ob_wp)
{
    ErrStatus revet;
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
    if(FMC_READY == fmc_state) {
        FMC_OBCTL2 |= ob_wp;
        revet = SUCCESS;
    } else {
        revet = ERROR;
    }
    return revet;
}

/*!
    \brief      configure security protection level (API_ID(0x001CU))
    \param[in]  ob_spc: specify security protection level
                only one parameter can be selected which is shown as below:
      \arg        FMC_NSPC: no security protection
      \arg        FMC_LSPC: low security protection
      \arg        FMC_HSPC: high security protection
    \param[out] none
    \retval     none
*/
void ob_security_protection_config(uint32_t ob_spc)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
    if(FMC_READY == fmc_state) {
        /* reset the OBCTL0_SPC, set according to ob_spc */
        FMC_OBCTL0 &= ~FMC_OBCTL0_SPC;
        FMC_OBCTL0 |= (ob_spc & FMC_OBCTL0_SPC);
    }
}

/*!
    \brief      program the FMC user option byte (API_ID(0x001DU))
    \param[in]  ob_fwdgt: option byte watchdog value
                only one parameter can be selected which is shown as below:
      \arg        OB_FWDGT_SW: software free watchdog
      \arg        OB_FWDGT_HW: hardware free watchdog
    \param[in]  ob_deepsleep: option byte deepsleep reset value
                only one parameter can be selected which is shown as below:
      \arg        OB_DEEPSLEEP_NRST: no reset when entering deepsleep mode
      \arg        OB_DEEPSLEEP_RST: generate a reset instead of entering deepsleep mode
    \param[in]  ob_stdby:option byte standby reset value
                only one parameter can be selected which is shown as below:
      \arg        OB_STDBY_NRST: no reset when entering standby mode
      \arg        OB_STDBY_RST: generate a reset instead of entering standby mode
    \param[out] none
    \retval     none
*/
void ob_user_write(uint32_t ob_fwdgt, uint32_t ob_deepsleep, uint32_t ob_stdby)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        /* reset the OB_FWDGT, OB_DEEPSLEEP and OB_STDBY, set according to ob_fwdgt, ob_deepsleep and ob_stdby */
        FMC_OBCTL1 &= ~(FMC_OBCTL1_NWDG_HW | FMC_OBCTL1_NRST_DPSLP | FMC_OBCTL1_NRST_STDBY);
        FMC_OBCTL1 |= ((ob_fwdgt | ob_deepsleep | ob_stdby) & (FMC_OBCTL1_NWDG_HW | FMC_OBCTL1_NRST_DPSLP | FMC_OBCTL1_NRST_STDBY));
    }
}

/*!
    \brief      configure the option byte sram initialize value (API_ID(0x001EU))
    \param[in]  init_mode: specifies the option byte sram initialize value
                only one parameter can be selected which is shown as below:
      \arg        OB_SRAM_INI_ENABLE: sram initialize after power reset
      \arg        OB_SRAM_INI_DISABLE: sram not initialized after power reset
    \param[out] none
    \retval     none
*/
void ob_sram_init_config(uint32_t init_mode)
{
    FMC_OBCTL1 &= ~FMC_OBCTL1_SRAM_RST;
    FMC_OBCTL1 |= (init_mode & FMC_OBCTL1_SRAM_RST);
}

/*!
    \brief      configure the option byte sram ecc enable value (API_ID(0x001FU))
    \param[in]  ecc_mode: specifies the option byte sram ecc function value
                only one parameter can be selected which is shown as below:
      \arg        OB_SRAMECC_DISABLE: SRAM ECC disable
      \arg        OB_SRAMECC_ENABLE: SRAM ECC enable
    \param[out] none
    \retval     none
*/
void ob_sram_ecc_config(uint32_t ecc_mode)
{
    FMC_OBCTL1 &= ~FMC_OBCTL1_ECC_EN;
    FMC_OBCTL1 |= (ecc_mode & FMC_OBCTL1_ECC_EN);
}

/*!
    \brief      configure the option byte the clock for loading no waiting time area (API_ID(0x0020U))
    \param[in]  clock_mode: specifies the clock after Power reset when read flash to memory
                only one parameter can be selected which is shown as below:
      \arg        PLL_CLK_200M: 200M from PLL
      \arg        PLL_CLK_160M: 160M from PLL
      \arg        PLL_CLK_120M: 120M from PLL
      \arg        IRC8M_CLK_8M: 8M from IRC8M
    \param[out] none
    \retval     none
*/
void ob_nwa_clock_config(uint32_t clock_mode)
{
    FMC_OBCTL1 &= ~FMC_OBCTL1_NWLD_SEL;
    FMC_OBCTL1 |= (clock_mode & FMC_OBCTL1_NWLD_SEL);
}

/*!
    \brief      program option bytes data (API_ID(0x0021U))
    \param[in]  data: data to program
    \param[out] none
    \retval     none
*/
void ob_data_write(uint16_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        /* reset the data */
        FMC_OBCTL1 &= ~FMC_OBCTL1_DATA;
        FMC_OBCTL1 |= (((uint32_t)data << OB_DATA_POS) & FMC_OBCTL1_DATA);
    }
}

/*!
    \brief      get the option byte sram initialize value (API_ID(0x0022U))
    \param[in]  none
    \param[out] none
    \retval     the option byte sram initialize value
*/
uint32_t ob_sram_init_get(void)
{
    return (FMC_OBCTL1 & FMC_OBCTL1_SRAM_RST);
}

/*!
    \brief      get the option byte sram ecc enable value (API_ID(0x0023U))
    \param[in]  none
    \param[out] none
    \retval     the option byte sram ecc function value
*/
uint32_t ob_sram_ecc_get(void)
{
    return (FMC_OBCTL1 & FMC_OBCTL1_ECC_EN);
}

/*!
    \brief      get the option byte the clock for loading no waiting time area (API_ID(0x0024U))
    \param[in]  none
    \param[out] none
    \retval     the option byte the clock for loading no waiting time area value
*/
uint32_t ob_nwa_clock_get(void)
{
    return (FMC_OBCTL1 & FMC_OBCTL1_NWLD_SEL);
}

/*!
    \brief      get the FMC data option byte (API_ID(0x0025U))
    \param[in]  none
    \param[out] none
    \retval     the FMC data option byte
*/
uint16_t ob_data_get(void)
{
    return (uint16_t)((FMC_OBCTL1 & FMC_OBCTL1_DATA) >> 10U);
}

/*!
    \brief      get the FMC option byte write protection (API_ID(0x0026U))
    \param[in]  none
    \param[out] none
    \retval     uint32_t: the FMC option byte write protection
*/
uint32_t ob_write_protection_get(void)
{
    return (FMC_OBCTL2);
}

/*!
    \brief      get option byte security protection code value (API_ID(0x0027U))
    \param[in]  none
    \param[out] none
    \retval     uint32_t: the option byte security protection code value
                FMC_NSPC: no security protection
                FMC_LSPC: low security protection
                FMC_HSPC: high security protection
*/
uint32_t ob_spc_get(void)
{
    return (FMC_OBCTL0 & FMC_OBCTL0_SPC);
}

/*!
    \brief      check flag is set or not (API_ID(0x0028U))
    \param[in]  flag: check FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_BANK0_BUSY: FMC bank0 busy flag bit
      \arg        FMC_FLAG_BANK0_PGERR: FMC bank0 operation error flag bit
      \arg        FMC_FLAG_BANK0_WPERR: FMC bank0 erase/program protection error flag bit
      \arg        FMC_FLAG_BANK0_END: FMC bank0 end of operation flag bit
      \arg        FMC_FLAG_OBERR: FMC option bytes read error flag bit
      \arg        FMC_FLAG_BANK1_BUSY: FMC bank1 busy flag bit
      \arg        FMC_FLAG_BANK1_PGERR: FMC bank1 operation error flag bit
      \arg        FMC_FLAG_BANK1_WPERR: FMC bank1 erase/program protection error flag bit
      \arg        FMC_FLAG_BANK1_END: FMC bank1 end of operation flag bit
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flag_get(fmc_flag_enum flag)
{
    FlagStatus revet;
    if(RESET != (FMC_REG_VAL(flag) & BIT(FMC_BIT_POS(flag)))) {
        revet = SET;
    } else {
        revet = RESET;
    }
    return revet;
}

/*!
    \brief      clear the FMC flag (API_ID(0x0029U))
    \param[in]  flag: clear FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_BANK0_PGERR: FMC bank0 operation error flag bit
      \arg        FMC_FLAG_BANK0_WPERR: FMC bank0 erase/program protection error flag bit
      \arg        FMC_FLAG_BANK0_END: FMC bank0 end of operation flag bit
      \arg        FMC_FLAG_BANK1_PGERR: FMC bank1 operation error flag bit
      \arg        FMC_FLAG_BANK1_WPERR: FMC bank1 erase/program protection error flag bit
      \arg        FMC_FLAG_BANK1_END: FMC bank1 end of operation flag bit
    \param[out] none
    \retval     none
*/
void fmc_flag_clear(fmc_flag_enum flag)
{
    FMC_REG_VAL(flag) |= BIT(FMC_BIT_POS(flag));
}

/*!
    \brief      enable FMC interrupt (API_ID(0x002AU))
    \param[in]  interrupt: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_BANK0_END: enable FMC bank0 end of operation
      \arg        FMC_INT_BANK0_ERR: enable FMC bank0 error interrupt
      \arg        FMC_INT_BANK1_END: enable FMC bank1 end of operation
      \arg        FMC_INT_BANK1_ERR: enable FMC bank1 error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_enable(fmc_interrupt_enum interrupt)
{
    FMC_REG_VAL(interrupt) |= BIT(FMC_BIT_POS(interrupt));
}

/*!
    \brief      disable FMC interrupt (API_ID(0x002BU))
    \param[in]  interrupt: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_BANK0_END: enable FMC bank0 end of operation
      \arg        FMC_INT_BANK0_ERR: enable FMC bank0 error interrupt
      \arg        FMC_INT_BANK1_END: enable FMC bank1 end of operation
      \arg        FMC_INT_BANK1_ERR: enable FMC bank1 error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_disable(fmc_interrupt_enum interrupt)
{
    FMC_REG_VAL(interrupt) &= ~BIT(FMC_BIT_POS(interrupt));
}

/*!
    \brief      get FMC interrupt flag state (API_ID(0x002CU))
    \param[in]  flag: FMC interrupt flags, refer to fmc_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_BANK0_PGERR: FMC bank0 operation error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK0_WPERR: FMC bank0 erase/program protection error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK0_END: FMC bank0 end of operation interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_PGERR: FMC bank1 operation error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_WPERR: FMC bank1 erase/program protection error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_END: FMC bank1 end of operation interrupt flag bit
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_interrupt_flag_get(fmc_interrupt_flag_enum flag)
{
    FlagStatus revet;
    uint32_t ret1;
    uint32_t ret2;
    if(FMC_STAT0_REG_OFFSET == FMC_REG_OFFSET_GET(flag)) {
        /* get the status of interrupt flag */
        ret1 = FMC_REG_VALS(flag) & BIT(FMC_BIT_POS0(flag));
        /* get the status of interrupt enable bit */
        ret2 = FMC_CTL0 & BIT(FMC_BIT_POS1(flag));
    } else {
        /* get the status of interrupt flag */
        ret1 = FMC_REG_VALS(flag) & BIT(FMC_BIT_POS0(flag));
        /* get the status of interrupt enable bit */
        ret2 = FMC_CTL1 & BIT(FMC_BIT_POS1(flag));
    }

    if((ret1 != 0U) && (ret2 != 0U)) {
        revet = SET;
    } else {
        revet = RESET;
    }
    return revet;
}

/*!
    \brief      clear FMC interrupt flag state (API_ID(0x002DU))
    \param[in]  flag: FMC interrupt flags, refer to fmc_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_BANK0_PGERR: FMC bank0 operation error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK0_WPERR: FMC bank0 erase/program protection error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK0_END: FMC bank0 end of operation interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_PGERR: FMC bank1 operation error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_WPERR: FMC bank1 erase/program protection error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_END: FMC bank1 end of operation interrupt flag bit
    \param[out] none
    \retval     none
*/
void fmc_interrupt_flag_clear(fmc_interrupt_flag_enum flag)
{
    FMC_REG_VALS(flag) |= BIT(FMC_BIT_POS0(flag));
}

/*!
    \brief      get the FMC bank0 state (API_ID(0x002EU))
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_bank0_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_BUSY)) {
        fmc_state = FMC_BUSY;
    } else {
        if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_WPERR)) {
            fmc_state = FMC_WPERR;
        } else {
            if((uint32_t)0x00U != (FMC_STAT0 & (FMC_STAT0_PGERR))) {
                fmc_state = FMC_PGERR;
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      get the FMC bank1 state (API_ID(0x002FU))
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_bank1_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_BUSY)) {
        fmc_state = FMC_BUSY;
    } else {
        if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_WPERR)) {
            fmc_state = FMC_WPERR;
        } else {
            if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_PGERR)) {
                fmc_state = FMC_PGERR;
            }
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC bank0 is ready or not (API_ID(0x0030U))
    \param[in]  timeout: count of loop
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum fmc_bank0_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for FMC ready */
    do {
        /* get FMC state */
        fmc_state = fmc_bank0_state_get();
        timeout--;
    } while((FMC_BUSY == fmc_state) && (0x00U != timeout));

    if(FMC_BUSY == fmc_state) {
        fmc_state = FMC_TOERR;
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC bank1 is ready or not (API_ID(0x0031U))
    \param[in]  timeout: count of loop
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum fmc_bank1_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for FMC ready */
    do {
        /* get FMC state */
        fmc_state = fmc_bank1_state_get();
        timeout--;
    } while((FMC_BUSY == fmc_state) && (0x00U != timeout));

    if(FMC_BUSY == fmc_state) {
        fmc_state = FMC_TOERR;
    }
    /* return the FMC state */
    return fmc_state;
}

