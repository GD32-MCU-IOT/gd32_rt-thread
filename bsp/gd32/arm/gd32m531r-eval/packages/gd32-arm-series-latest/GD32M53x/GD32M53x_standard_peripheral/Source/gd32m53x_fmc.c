/*!
    \file    gd32m53x_fmc.c
    \brief   FMC driver

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

#include "gd32m53x_fmc.h"

/* FMC mask */
#define LOW_8BITS_MASK             ((uint32_t)0x000000FFU)
#define HIGH_8BITS_MASK            ((uint32_t)0x0000FF00U)
#define LOW_8BITS_MASK1            ((uint32_t)0x00FF0000U)
#define HIGH_8BITS_MASK1           ((uint32_t)0xFF000000U)
#define LOW_16BITS_MASK            ((uint32_t)0x0000FFFFU)
#define HIGH_16BITS_MASK           ((uint32_t)0xFFFF0000U)

/* USER of option bytes mask */
#define OB_USER_MASK               ((uint8_t)0x10U)

/* OB_WP mask */
#define OB_WP0_MASK                ((uint32_t)0x000000FFU)
#define OB_WP1_MASK                ((uint32_t)0x0000FF00U)
#define OB_WP2_MASK                ((uint32_t)0x00FF0000U)
#define OB_WP3_MASK                ((uint32_t)0xFF000000U)

/* option byte default value */
#define OB_DEFAULT                 ((uint32_t)0x00FF00FFU)

/* OB WWDGT&FWDGT mask and offset */
#define OB_WWDG_CNT_MASK0          ((uint16_t)0x003FU)
#define OB_WWDG_CNT_MASK1          ((uint16_t)0x3FC0U)
#define OB_WWDG_CNT_OFFSET0        ((uint16_t)16U)
#define OB_WWDG_CNT_OFFSET1        ((uint16_t)6U)
#define OB_FWDG_WND_MASK0          ((uint16_t)0x000FU)
#define OB_FWDG_WND_MASK1          ((uint16_t)0x0FF0U)
#define OB_FWDG_PSC_MASK           ((uint8_t)0x70U)

/* FMC register bit offset */
#define CTL_CBCMDLEN_OFFSET        ((uint32_t)0x0000001DU)               /*!< CBCMDLEN offset in FMC_CTL register */
#define OBSTAT_PLEVEL_OFFSET       ((uint32_t)0x00000001U)               /*!< PLEVEL offset in FMC_OBSTAT register */
#define OBSTAT_USER_OFFSET         ((uint32_t)0x00000002U)               /*!< USER offset in FMC_OBSTAT register */
#define OBSTAT_DATA_OFFSET         ((uint32_t)0x0000000AU)               /*!< DATA offset in FMC_OBSTAT register */

/* get FMC flash state */
static fmc_state_enum fmc_flash_state_get(void);
/* check FMC main ready or not */
static fmc_state_enum fmc_flash_ready_wait(uint32_t timeout);

/*!
    \brief      unlock the main flash and data flash operation (API_ID(0x0001U))
                it is better to used in pairs with fmc_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_unlock(void)
{
    if((0U != (FMC_CTL & FMC_CTL_LK))) {
        /* write the FMC unlock key */
        FMC_KEY = UNLOCK_KEY0;
        FMC_KEY = UNLOCK_KEY1;
    }
}

/*!
    \brief      lock the main flash and data flash operation (API_ID(0x0002U))
                it is better to used in pairs with fmc_unlock after an operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_lock(void)
{
    /* set the LK bit*/
    FMC_CTL |= FMC_CTL_LK;
}

/*!
    \brief      set the wait state counter value (API_ID(0x0003U))
    \param[in]  wscnt: wait state counter value
                only one parameter can be selected which is shown as below:
      \arg        FMC_WAIT_STATE_0: FMC 0 wait
      \arg        FMC_WAIT_STATE_1: FMC 1 wait
      \arg        FMC_WAIT_STATE_2: FMC 2 wait
      \arg        FMC_WAIT_STATE_3: FMC 3 wait
      \arg        FMC_WAIT_STATE_4: FMC 4 wait
      \arg        FMC_WAIT_STATE_5: FMC 5 wait
      \arg        FMC_WAIT_STATE_6: FMC 6 wait
    \param[out] none
    \retval     none
*/
void fmc_wscnt_set(uint32_t wscnt)
{
    uint32_t reg;

    reg = FMC_WS;
    /* set the wait state counter value */
    reg &= ~FMC_WS_WSCNT;
    FMC_WS = (reg | (wscnt & FMC_WS_WSCNT));
}

/*!
    \brief      enable pre-fetch (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_prefetch_enable(void)
{
    FMC_WS |= FMC_WS_PFEN;
}

/*!
    \brief      disable pre-fetch (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_prefetch_disable(void)
{
    FMC_WS &= ~FMC_WS_PFEN;
}

/*!
    \brief      enable IBUS cache (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ibus_enable(void)
{
    FMC_WS |= FMC_WS_ICEN;
}

/*!
    \brief      disable IBUS cache (API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ibus_disable(void)
{
    FMC_WS &= ~FMC_WS_ICEN;
}

/*!
    \brief      enable DBUS cache (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_dbus_enable(void)
{
    FMC_WS |= FMC_WS_DCEN;
}

/*!
    \brief      disable DBUS cache (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_dbus_disable(void)
{
    FMC_WS &= ~FMC_WS_DCEN;
}

/*!
    \brief      reset IBUS cache enable (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ibus_reset_enable(void)
{
    FMC_WS |= FMC_WS_ICRST;
}

/*!
    \brief      reset IBUS cache disable (API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ibus_reset_disable(void)
{
    FMC_WS &= ~FMC_WS_ICRST;
}

/*!
    \brief      reset DBUS cache (API_ID(0x000CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_dbus_reset_enable(void)
{
    FMC_WS |= FMC_WS_DCRST;
}

/*!
    \brief      reset DBUS cache (API_ID(0x000DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_dbus_reset_disable(void)
{
    FMC_WS &= ~FMC_WS_DCRST;
}

/*!
    \brief      check whether flash page is blank or not by check blank command (API_ID(0x000EU))
    \param[in]  address: start address to check
    \param[in]  length: the read length is 2^length double words, the flash area to be checked must be in one page and should not exceed 1KB boundary
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum fmc_blank_check(uint32_t address, uint8_t length)
{
    fmc_state_enum fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if((NOT_FMC_VALID_ADDRESS(address)) || (0U != ((address) % 16U))) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000EU), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_FMC_VALID_BLANK_ADDRESS_CONFIG(address, length)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else
#endif
    {
        if((address >= MFLASH_BASE_ADDRESS) && (address < (MFLASH_BASE_ADDRESS + MFLASH_SIZE))) {
            FMC_CTL &= ~FMC_CTL_BKSEL;
            /* start check blank command */
            FMC_ADDR = address;
            FMC_CTL &= ~FMC_CTL_CBCMDLEN;
            FMC_CTL |= (uint32_t)length << CTL_CBCMDLEN_OFFSET;
            FMC_CTL |= FMC_CTL_CBCMD;
            FMC_CTL |= FMC_CTL_START;

            /* wait for the FMC ready */
            fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

            /* reset the CBCMD bit */
            FMC_CTL &= ~FMC_CTL_CBCMD;
        } else {
            FMC_CTL |= FMC_CTL_BKSEL;
            /* start check blank command */
            FMC_ADDR = address;
            FMC_CTL &= ~FMC_CTL_CBCMDLEN;
            FMC_CTL |= (uint32_t)length << CTL_CBCMDLEN_OFFSET;
            FMC_CTL |= FMC_CTL_CBCMD;
            FMC_CTL |= FMC_CTL_START;

            /* wait for the FMC ready */
            fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

            /* reset the CBCMD bit */
            FMC_CTL &= ~FMC_CTL_CBCMD;
            /* reset the BKSEL bit */
            FMC_CTL &= ~FMC_CTL_BKSEL;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      erase main flash or data flash page (API_ID(0x000FU))
    \param[in]  page_address: target page start address
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum fmc_page_erase(uint32_t page_address)
{
    fmc_state_enum fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_ADDRESS(page_address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000FU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        if((page_address >= MFLASH_BASE_ADDRESS) && (page_address < (MFLASH_BASE_ADDRESS + MFLASH_SIZE))) {
            fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                /* start page erase */
                FMC_CTL &= ~FMC_CTL_BKSEL;
                FMC_CTL |= FMC_CTL_PER;
                FMC_ADDR = page_address;
                FMC_CTL |= FMC_CTL_START;

                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

                /* reset the PER bit */
                FMC_CTL &= ~FMC_CTL_PER;
            }
        } else {
            fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                /* start page erase */
                FMC_CTL |= FMC_CTL_BKSEL;
                FMC_CTL |= FMC_CTL_PER;
                FMC_ADDR = page_address;
                FMC_CTL |= FMC_CTL_START;

                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

                /* reset the PER bit */
                FMC_CTL &= ~FMC_CTL_PER;
                /* reset the BKSEL bit */
                FMC_CTL &= ~FMC_CTL_BKSEL;
            }
        }
    }

    /* return the FMC state  */
    return fmc_state;
}

/*!
    \brief      erase main flash (API_ID(0x0010U))
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum fmc_mflash_mass_erase(void)
{
    fmc_state_enum fmc_state;
    /* wait for the FMC ready */
    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        /* start whole chip erase */
        FMC_CTL &= ~FMC_CTL_BKSEL;
        FMC_CTL |= FMC_CTL_MER;
        FMC_CTL |= FMC_CTL_START;
        /* wait for the FMC ready */
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the MER bit */
        FMC_CTL &= ~FMC_CTL_MER;
    }

    /* return the FMC state  */
    return fmc_state;
}

/*!
    \brief      erase data flash (API_ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum fmc_dflash_mass_erase(void)
{
    fmc_state_enum fmc_state;
    /* wait for the FMC ready */
    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        /* start chip erase */
        FMC_CTL |= FMC_CTL_BKSEL;
        FMC_CTL |= FMC_CTL_MER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

        /* reset the MER bit */
        FMC_CTL &= ~FMC_CTL_MER;
        /* reset the BKSEL bit */
        FMC_CTL &= ~FMC_CTL_BKSEL;
    }
    /* return the fmc state  */
    return fmc_state;
}

/*!
    \brief      erase whole chip (API_ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum fmc_mass_erase(void)
{
    fmc_state_enum fmc_state;

    /* mass erase main flash */
    fmc_state = fmc_mflash_mass_erase();

    if(FMC_READY == fmc_state) {
        /* mass erase data flash */
        fmc_state = fmc_dflash_mass_erase();
    }

    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      FMC program four words at the corresponding address (API_ID(0x0013U))
    \param[in]  address: address to program
    \param[in]  data_l: low 64-bit to program
    \param[in]  data_h: high 64-bit to program
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum fmc_fourword_program(uint32_t address, uint64_t data_l, uint64_t data_h)
{
    fmc_state_enum fmc_state;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if((NOT_FMC_VALID_ADDRESS(address)) || (0U != ((address) % 16U))) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0013U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        if((address >= MFLASH_BASE_ADDRESS) && (address < (MFLASH_BASE_ADDRESS + MFLASH_SIZE))) {
            /* wait for the FMC ready */
            fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                FMC_CTL &= ~FMC_CTL_BKSEL;
                FMC_CTL |= FMC_CTL_PG;
                REG32(address) = (uint32_t)(data_l & 0x00000000FFFFFFFFU);
                REG32(address + 4U) = (uint32_t)(data_l >> 32U);
                REG32(address + 8U) = (uint32_t)(data_h & 0x00000000FFFFFFFFU);
                REG32(address + 12U) = (uint32_t)(data_h >> 32U);

                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

                /* reset the PG */
                FMC_CTL &= ~FMC_CTL_PG;
            }
        } else {
            /* wait for the FMC ready */
            fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                FMC_CTL |= FMC_CTL_BKSEL;
                FMC_CTL |= FMC_CTL_PG;
                REG32(address) = (uint32_t)(data_l & 0x00000000FFFFFFFFU);
                REG32(address + 4U) = (uint32_t)(data_l >> 32U);
                REG32(address + 8U) = (uint32_t)(data_h & 0x00000000FFFFFFFFU);
                REG32(address + 12U) = (uint32_t)(data_h >> 32U);

                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

                /* reset the PG */
                FMC_CTL &= ~FMC_CTL_PG;
                /* reset the BKSEL bit */
                FMC_CTL &= ~FMC_CTL_BKSEL;
            }
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      FMC fast program one row data (16 four words) starting at the corresponding address (API_ID(0x0014U))
    \param[in]  address: address to program
    \param[in]  data: data buffer to program
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum fmc_fast_program(uint32_t address, uint64_t data[])
{
    uint8_t index;
    fmc_state_enum fmc_state;
    uint8_t cache_en = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if((NOT_FMC_VALID_ADDRESS(address)) || (0U != ((address) % 64U))) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0014U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_VALID_POINTER(data)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0014U), ERR_PARAM_POINTER);
    } else
#endif
    {
        if((address >= MFLASH_BASE_ADDRESS) && (address < (MFLASH_BASE_ADDRESS + MFLASH_SIZE))) {
            /* check the row (16 four words) in flash to confirm all data in main flash is all 0xFF */
            fmc_state = fmc_blank_check(address, CBCMDLEN_OF_ONE_ROW_MAIN);
            if(FMC_CBCMDERR != fmc_state) {
                /* flush the cache if it is enabled */
                if(FMC_WS & FMC_WS_DCEN) {
                    cache_en = 1U;
                    fmc_dbus_disable();
                }
                fmc_dbus_reset_enable();
                fmc_dbus_reset_disable();

                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

                if(FMC_READY == fmc_state) {
                    /* set the FSTPG bit to start program */
                    FMC_CTL |= FMC_CTL_FSTPG;
                    FMC_ADDR = address;
                    /* program the row data */
                    for(index = 0U; index < DOUBLEWORD_CNT_IN_ROW; index++) {
                        FMC_DATA = (uint32_t)(data[index] & 0x00000000FFFFFFFFU);
                        FMC_DATA = (uint32_t)(data[index] >> 32U);
                    }
                    /* set START bit to launch fast program operation to flash */
                    FMC_CTL |= FMC_CTL_START;

                    /* wait for the FMC ready */
                    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

                    /* reset the FSTPG bit */
                    FMC_CTL &= ~FMC_CTL_FSTPG;
                }
            }
        } else {
            /* check the row (8 double-word) in flash to confirm all data in data flash is all 0xFF */
            fmc_state = fmc_blank_check(address, CBCMDLEN_OF_ONE_ROW_DATA);
            if(FMC_CBCMDERR != fmc_state) {
                /* flush the cache if it is enabled */
                if(FMC_WS & FMC_WS_DCEN) {
                    cache_en = 1U;
                    fmc_dbus_disable();
                }
                fmc_dbus_reset_enable();
                fmc_dbus_reset_disable();

                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

                if(FMC_READY == fmc_state) {
                    FMC_CTL |= FMC_CTL_BKSEL;
                    /* set the FSTPG bit to start program */
                    FMC_CTL |= FMC_CTL_FSTPG;
                    FMC_ADDR = address;
                    /* program the row data */
                    for(index = 0U; index < DOUBLEWORD_DATA_CNT_IN_ROW; index++) {
                        FMC_DATA = (uint32_t)(data[index] & 0x00000000FFFFFFFFU);
                        FMC_DATA = (uint32_t)(data[index] >> 32U);
                    }

                    /* set START bit to launch fast program operation to flash */
                    FMC_CTL |= FMC_CTL_START;

                    /* wait for the FMC ready */
                    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

                    /* reset the FSTPG bit */
                    FMC_CTL &= ~FMC_CTL_FSTPG;
                    /* reset the BKSEL bit */
                    FMC_CTL &= ~FMC_CTL_BKSEL;
                }
            }
        }
        if(1U == cache_en) {
            fmc_dbus_enable();
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      FMC program a word at the corresponding address in OTP (API_ID(0x0015U))
    \param[in]  address: address to program
    \param[in]  data_l: low 64-bit data to program
    \param[in]  data_h: high 64-bit data to program
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum fmc_otp_fourword_program(uint32_t address, uint64_t data_l, uint64_t data_h)
{
    fmc_state_enum fmc_state;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_OTP_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0015U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state) {
            FMC_CTL |= FMC_CTL_BKSEL;
            /* set the PG bit to start program */
            FMC_CTL |= FMC_CTL_PG;
            REG32(address) = (uint32_t)(data_l & 0x00000000FFFFFFFFU);
            REG32(address + 4U) = (uint32_t)(data_l >> 32U);
            REG32(address + 8U) = (uint32_t)(data_h & 0x00000000FFFFFFFFU);
            REG32(address + 12U) = (uint32_t)(data_h >> 32U);

            /* wait for the FMC ready */
            fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

            /* reset the PG bit */
            FMC_CTL &= ~FMC_CTL_PG;

            FMC_CTL &= ~FMC_CTL_BKSEL;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      unlock the option byte operation (API_ID(0x0016U))
                it is better to used in pairs with ob_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_unlock(void)
{
    if(RESET == (FMC_CTL & FMC_CTL_OBWEN)) {
        /* write the FMC key */
        FMC_OBKEY = UNLOCK_KEY0;
        FMC_OBKEY = UNLOCK_KEY1;
    }
}

/*!
    \brief      lock the option byte operation (API_ID(0x0017U))
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
    \brief      reload the option byte and generate a system reset (API_ID(0x0018U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_reset(void)
{
    /* set the OBRLD bit */
    FMC_CTL |= FMC_CTL_OBRLD;
}

/*!
    \brief      erase the FMC option bytes (API_ID(0x0019U))
                programmer must ensure FMC & option byte are both unlocked before calling this function
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum ob_erase(void)
{
    uint8_t temp_spc;
    fmc_state_enum fmc_state;

    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

    temp_spc = (uint8_t)OB_SPC_USER;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK))) {
        fmc_state = FMC_OB_HSPC;
    }

    if(FMC_READY == fmc_state) {
        FMC_CTL |= FMC_CTL_BKSEL;
        /* start erase the option bytes */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the BKSEL bit */
        FMC_CTL &= ~FMC_CTL_BKSEL;
        if(FMC_READY == fmc_state) {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_OBPG;

            /* restore the last get option byte security protection code */
            OB_SPC_USER = (temp_spc & LOW_8BITS_MASK) | LOW_8BITS_MASK1;
            OB_DATA = OB_DEFAULT;
            OB_WP0 = OB_DEFAULT;
            OB_WP1 = OB_DEFAULT;
            OB_USER1_WWDGT0 = OB_DEFAULT;
            OB_WWDGT1_WWDGT2 = OB_DEFAULT;
            OB_FWDGT0_FWDGT1 = OB_DEFAULT;
            OB_FWDGT2_FWDGT3 = OB_DEFAULT;

            /* wait for the FMC ready */
            fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        } else {
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      enable write protection (API_ID(0x001AU))
    \param[in]  ob_wp: specify sector to be write protected, refer to fmc_ob_wp_enum
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum ob_write_protection_enable(fmc_ob_wp_enum ob_wp)
{
    uint32_t temp_spc;
    uint32_t temp;
    uint32_t i;
    uint32_t op_byte[8];
    fmc_state_enum fmc_state;

    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

    temp_spc = OB_SPC_USER;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK))) {
        fmc_state = FMC_OB_HSPC;
    }

    for(i = 0U; i < 8U; i++) {
        op_byte[i] = OP_BYTE(i);
    }

    temp      = (uint32_t)(~ob_wp);
    op_byte[2] = (temp & LOW_8BITS_MASK) | ((temp & HIGH_8BITS_MASK) << 8U);
    op_byte[3] = ((temp & LOW_8BITS_MASK1) >> 16U) | ((temp & HIGH_8BITS_MASK1) >> 8U);

    if(FMC_READY == fmc_state) {
        FMC_CTL |= FMC_CTL_BKSEL;
        /* start erase the option byte */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the BKSEL bit */
        FMC_CTL &= ~FMC_CTL_BKSEL;
        if(FMC_READY == fmc_state) {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_OBPG;

            for(i = 0U; i < 8U; i++) {
                OP_BYTE(i) = op_byte[i];
                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY != fmc_state) {
                    break;
                }
            }

            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        } else {
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure security protection (API_ID(0x001BU))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_spc: specify security protection
                only one parameter can be selected which is shown as below:
      \arg        FMC_NSPC: no security protection
      \arg        FMC_LSPC: low security protection
      \arg        FMC_HSPC: high security protection
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum ob_security_protection_config(uint8_t ob_spc)
{
    uint32_t temp_spc;
    uint8_t i;
    uint32_t op_byte[8];
    fmc_state_enum fmc_state;

    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

    temp_spc = OB_SPC_USER & LOW_16BITS_MASK;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK))) {
        fmc_state = FMC_OB_HSPC;
    }

    for(i = 0U; i < 8U; i++) {
        op_byte[i] = OP_BYTE(i);
    }

    op_byte[0] = ((uint32_t)(ob_spc)) | ((op_byte[0] & HIGH_16BITS_MASK));

    if(FMC_READY == fmc_state) {
        FMC_CTL |= FMC_CTL_BKSEL;
        /* start erase the option byte */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the BKSEL bit */
        FMC_CTL &= ~FMC_CTL_BKSEL;
        if(FMC_READY == fmc_state) {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_OBPG;

            for(i = 0U; i < 8U; i++) {
                OP_BYTE(i) = op_byte[i];
                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY != fmc_state) {
                    break;
                }
            }

            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        } else {
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program option bytes USER (API_ID(0x001CU))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  optionbyte_user: option bytes user structure and the member values are shown as below:
                  nfwdg_hw: OB_FWDGT_HW, OB_FWDGT_SW
                  nrst_dpslp: OB_DEEPSLEEP_RST, OB_DEEPSLEEP_NRST
                  nrst_stdby: OB_STDBY_RST, OB_STDBY_NRST
                  lvd0en: OB_LVDOEN_ENABLE, OB_LVDOEN_DISABLE
                  fwdgspd_dpslp: OB_FWDGDPSLP_ENABLE, OB_FWDGDPSLP_DISABLE
                  fwdgt_standby: OB_FWDGSTANDBY_ENABLE, OB_FWDGSTANDBY_DISABLE
                  lvd0t: OB_LVD0T_VALUE2, OB_LVD0T_VALUE3
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum ob_user_write(optionbyte_user_struct *optionbyte_user)
{
    uint32_t temp_spc;
    uint8_t i;
    uint32_t temp;
    uint32_t op_byte[8];
    fmc_state_enum fmc_state;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(optionbyte_user)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x001CU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

        temp_spc = OB_SPC_USER;

        /* check the option bytes security protection value */
        if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK))) {
            fmc_state = FMC_OB_HSPC;
        }

        for(i = 0U; i < 8U; i++) {
            op_byte[i] = OP_BYTE(i);
        }

        temp = (uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)(optionbyte_user->nfwdg_hw & OB_FWDGT_SW)
                                             | (uint8_t)(optionbyte_user->nrst_dpslp & OB_DEEPSLEEP_NRST)) | (uint8_t)(optionbyte_user->nrst_stdby & OB_STDBY_NRST))
                                             | (uint8_t)(optionbyte_user->lvd0en & OB_LVDOEN_DISABLE)) | (uint8_t)(optionbyte_user->fwdgspd_dpslp &
                                                     OB_FWDGDPSLP_DISABLE)) | (uint8_t)(optionbyte_user->lvd0t & OB_LVD0T_VALUE3))
                                             | (uint8_t)(optionbyte_user->fwdgspd_stdby & OB_FWDGSTANDBY_DISABLE));

        op_byte[0] = ((uint32_t)(temp) << 16U) | ((op_byte[0] & LOW_16BITS_MASK));

        if(FMC_READY == fmc_state) {
            FMC_CTL |= FMC_CTL_BKSEL;
            /* start erase the option byte */
            FMC_CTL |= FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_START;

            /* wait for the FMC ready */
            fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the BKSEL bit */
            FMC_CTL &= ~FMC_CTL_BKSEL;
            if(FMC_READY == fmc_state) {
                /* reset the OBER bit and enable the option bytes programming */
                FMC_CTL &= ~FMC_CTL_OBER;
                FMC_CTL |= FMC_CTL_OBPG;

                for(i = 0U; i < 8U; i++) {
                    OP_BYTE(i) = op_byte[i];
                    /* wait for the FMC ready */
                    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
                    if(FMC_READY != fmc_state) {
                        break;
                    }
                }

                /* reset the OBPG bit */
                FMC_CTL &= ~FMC_CTL_OBPG;
            } else {
                /* reset the OBER bit */
                FMC_CTL &= ~FMC_CTL_OBER;
            }
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program option bytes data (API_ID(0x001DU))
    \param[in]  ob_data: the byte to be programmed
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/

fmc_state_enum ob_data_program(uint16_t ob_data)
{
    uint32_t temp_spc;
    uint8_t i;
    uint32_t op_byte[8];

    fmc_state_enum fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

    temp_spc = OB_SPC_USER;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK))) {
        fmc_state = FMC_OB_HSPC;
    }

    for(i = 0U; i < 8U; i++) {
        op_byte[i] = OP_BYTE(i);
    }

    op_byte[1] = (uint32_t)((ob_data & LOW_8BITS_MASK) | ((ob_data & HIGH_8BITS_MASK) << 8U));

    if(FMC_READY == fmc_state) {
        FMC_CTL |= FMC_CTL_BKSEL;
        /* start erase the option byte */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the BKSEL bit */
        FMC_CTL &= ~FMC_CTL_BKSEL;
        if(FMC_READY == fmc_state) {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_OBPG;

            for(i = 0U; i < 8U; i++) {
                OP_BYTE(i) = op_byte[i];
                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY != fmc_state) {
                    break;
                }
            }

            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        } else {
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program option bytes USER1 (API_ID(0x001EU))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_wwdg_hw: window watchdog select hardware or software
                only one parameter can be selected which are shown as below:
      \arg        OB_WWDGT_HW: select hardware window watchdog
      \arg        OB_WWDGT_SW: select software window watchdog
    \param[in]  ob_sram_ecc: sram ECC error check
                only one parameter can be selected which are shown as below:
      \arg        OB_SRAMECC_DISABLE: sram ecc disable
      \arg        OB_SRAMECC_ENABLE: sram ecc enable
    \param[in]  ob_swd_mode: swd off or on
                only one parameter can be selected which are shown as below:
      \arg        OB_SWD_DISABLE: swd disable
      \arg        OB_SWD_ENABLE: swd enable
    \param[in]  ob_nrst_mod: reset input/output
                only one parameter can be selected which are shown as below:
      \arg        OB_NRST_MODE_VALUE1: nrst mode = 1
      \arg        OB_NRST_MODE_VALUE2: nrst mode = 2
      \arg        OB_NRST_MODE_VALUE3: nrst mode = 3
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum ob_user1_write(uint8_t ob_wwdg_hw, uint8_t ob_sram_ecc, uint8_t ob_swd_mode, uint8_t ob_nrst_mod)
{
    uint32_t temp_spc;
    uint8_t i;
    uint32_t temp;
    uint32_t op_byte[8];
    fmc_state_enum fmc_state;

    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

    temp_spc = OB_SPC_USER;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK))) {
        fmc_state = FMC_OB_HSPC;
    }

    for(i = 0U; i < 8U; i++) {
        op_byte[i] = OP_BYTE(i);
    }

    temp = (uint8_t)((uint8_t)((uint8_t)((uint8_t)(ob_wwdg_hw & OB_WWDGT_SW)
                                         | (uint8_t)(ob_sram_ecc & OB_SRAMECC_ENABLE))
                               | (uint8_t)(ob_swd_mode & OB_SWD_ENABLE))
                     | (uint8_t)(ob_nrst_mod & OB_NRST_MODE_VALUE3));

    op_byte[4] = (uint32_t)(temp) | ((op_byte[4] & HIGH_16BITS_MASK));

    if(FMC_READY == fmc_state) {
        FMC_CTL |= FMC_CTL_BKSEL;
        /* start erase the option byte */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the BKSEL bit */
        FMC_CTL &= ~FMC_CTL_BKSEL;
        if(FMC_READY == fmc_state) {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_OBPG;

            for(i = 0U; i < 8U; i++) {
                OP_BYTE(i) = op_byte[i];
                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY != fmc_state) {
                    break;
                }
            }

            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        } else {
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program option bytes WWDGT0 (API_ID(0x001FU))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  optionbyte_wwdg0: option bytes wwdg0 structure and the member values are shown as below:
                  psc: OB_WWDG_PSC8, OB_WWDG_PSC4, OB_WWDG_PSC2, OB_WWDG_PSC1
                  wsps: OB_WSPS_VALUE25, OB_WSPS_VALUE50, OB_WSPS_VALUE75, OB_WSPS_VALUE100
                  weps: OB_WEPS_VALUE75, OB_WEPS_VALUE50, OB_WEPS_VALUE25, OB_WEPS_VALUE0
                  ewie: OB_EWIE_ENABLE, OB_EWIE_DISABLE
                  wdga: OB_WWDGT_RST_DISABLE, OB_WWDGT_RST_ENABLE
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum ob_wwdgt0_write(optionbyte_wwdgt0_struct *optionbyte_wwdg0)
{
    uint32_t temp_spc;
    uint8_t i;
    uint32_t temp;
    uint32_t op_byte[8];
    fmc_state_enum fmc_state;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(optionbyte_wwdg0)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x001FU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

        temp_spc = OB_SPC_USER;

        /* check the option bytes security protection value */
        if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK))) {
            fmc_state = FMC_OB_HSPC;
        }

        for(i = 0U; i < 8U; i++) {
            op_byte[i] = OP_BYTE(i);
        }

        temp = (uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)(optionbyte_wwdg0->psc & OB_WWDG_PSC1) |
                                             (uint8_t)(optionbyte_wwdg0->wsps & OB_WSPS_VALUE100)) |
                                             (uint8_t)(optionbyte_wwdg0->weps & OB_WEPS_VALUE0)) | (uint8_t)(optionbyte_wwdg0->ewie & OB_EWIE_DISABLE)) |
                                             (uint8_t)(optionbyte_wwdg0->wdga & OB_WWDGT_RST_ENABLE));

        op_byte[4] = ((uint32_t)(temp) << 16U) | ((op_byte[4] & LOW_16BITS_MASK));

        if(FMC_READY == fmc_state) {
            FMC_CTL |= FMC_CTL_BKSEL;
            /* start erase the option byte */
            FMC_CTL |= FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_START;

            /* wait for the FMC ready */
            fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the BKSEL bit */
            FMC_CTL &= ~FMC_CTL_BKSEL;
            if(FMC_READY == fmc_state) {
                /* reset the OBER bit and enable the option bytes programming */
                FMC_CTL &= ~FMC_CTL_OBER;
                FMC_CTL |= FMC_CTL_OBPG;

                for(i = 0U; i < 8U; i++) {
                    OP_BYTE(i) = op_byte[i];
                    /* wait for the FMC ready */
                    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
                    if(FMC_READY != fmc_state) {
                        break;
                    }
                }

                /* reset the OBPG bit */
                FMC_CTL &= ~FMC_CTL_OBPG;
            } else {
                /* reset the OBER bit */
                FMC_CTL &= ~FMC_CTL_OBER;
            }
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program option bytes WWDGT1 and WWDGT2 (API_ID(0x0020U))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_wwdg_cnt: value in auto-start mode, 0 ~ 0x00003FFFU
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum ob_wwdgt1_wwdgt2_write(uint16_t ob_wwdg_cnt)
{
    uint32_t temp_spc;
    uint8_t i;
    uint32_t op_byte[8];
    fmc_state_enum fmc_state;

    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);

    temp_spc = OB_SPC_USER & LOW_16BITS_MASK;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK))) {
        fmc_state = FMC_OB_HSPC;
    }

    for(i = 0U; i < 8U; i++) {
        op_byte[i] = OP_BYTE(i);
    }

    op_byte[5] = (uint32_t)((uint32_t)(((uint32_t)ob_wwdg_cnt & OB_WWDG_CNT_MASK0) << OB_WWDG_CNT_OFFSET0) | ((
                                uint32_t)ob_wwdg_cnt & OB_WWDG_CNT_MASK1) >> OB_WWDG_CNT_OFFSET1);

    if(FMC_READY == fmc_state) {
        FMC_CTL |= FMC_CTL_BKSEL;
        /* start erase the option byte */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the BKSEL bit */
        FMC_CTL &= ~FMC_CTL_BKSEL;
        if(FMC_READY == fmc_state) {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_OBPG;

            for(i = 0U; i < 8U; i++) {
                OP_BYTE(i) = op_byte[i];
                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY != fmc_state) {
                    break;
                }
            }

            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        } else {
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program option bytes FWDGT0 and FWDGT1 and FWDGT2 and FWDGT3 (API_ID(0x0021U))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_fwdgt_wnd: hardware free watchdog window value, 0 ~ 0x00000FFFU
    \param[in]  ob_fwdgt_psc: free watchdog timer prescaler selection
                only one parameter can be selected which are shown as below:
      \arg        OB_FWDGT_PSC4: free watchdog timer prescaler selection 1/4
      \arg        OB_FWDGT_PSC8: free watchdog timer prescaler selection 1/8
      \arg        OB_FWDGT_PSC16: free watchdog timer prescaler selection 1/16
      \arg        OB_FWDGT_PSC32: free watchdog timer prescaler selection 1/32
      \arg        OB_FWDGT_PSC64: free watchdog timer prescaler selection 1/64
      \arg        OB_FWDGT_PSC128: free watchdog timer prescaler selection 1/128
      \arg        OB_FWDGT_PSC256: free watchdog timer prescaler selection 1/256
    \param[in]  ob_fwdgt_rst: fwdgt to generate a reset
                only one parameter can be selected which are shown as below:
      \arg        OB_FWDGT_RST_DISABLE: disable fwdgt to generate a reset
      \arg        OB_FWDGT_RST_ENABLE: enable fwdgt to generate a reset
    \param[in]  ob_fwdgt_reload: fwdgt reload value, 0 ~ 0x00000FFFU
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
fmc_state_enum ob_fwdgt_write(uint16_t ob_fwdgt_wnd, uint8_t ob_fwdgt_psc, uint8_t ob_fwdgt_rst,
                              uint16_t ob_fwdgt_reload)
{
    uint32_t temp_spc;
    uint8_t i;
    uint32_t op_byte[8];

    fmc_state_enum fmc_state;

    fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
    temp_spc = OB_SPC_USER & LOW_16BITS_MASK;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK))) {
        fmc_state = FMC_OB_HSPC;
    }

    for(i = 0U; i < 8U; i++) {
        op_byte[i] = OP_BYTE(i);
    }
    op_byte[6] = (uint32_t)(((uint32_t)ob_fwdgt_wnd & OB_FWDG_WND_MASK0) | ((uint32_t)ob_fwdgt_psc & OB_FWDG_PSC_MASK) | ((uint32_t)ob_fwdgt_rst & OB_FWDGT_RST_ENABLE));
    op_byte[7] = (uint32_t)((uint32_t)ob_fwdgt_wnd & OB_FWDG_WND_MASK1);
    op_byte[6] = (uint32_t)(ob_fwdgt_reload & LOW_8BITS_MASK) | (uint32_t)((op_byte[6] << 16U) & LOW_8BITS_MASK1);
    op_byte[7] = (uint32_t)((uint32_t)(op_byte[7] & LOW_8BITS_MASK) | (((uint32_t)ob_fwdgt_reload << 8U) &
                            LOW_8BITS_MASK1));

    if(FMC_READY == fmc_state) {
        FMC_CTL |= FMC_CTL_BKSEL;
        /* start erase the option byte */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the BKSEL bit */
        FMC_CTL &= ~FMC_CTL_BKSEL;
        if(FMC_READY == fmc_state) {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_OBPG;

            for(i = 0U; i < 8U; i++) {
                OP_BYTE(i) = op_byte[i];
                /* wait for the FMC ready */
                fmc_state = fmc_flash_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY != fmc_state) {
                    break;
                }
            }

            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        } else {
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      get OB_USER in register FMC_OBSTAT (API_ID(0x0022U))
    \param[in]  none
    \param[out] none
    \retval     uint8_t, the FMC user option bytes values
*/
uint8_t ob_user_get(void)
{
    /* return the FMC user option bytes value */
    return (uint8_t)((FMC_OBSTAT & FMC_OBSTAT_USER) >> OBSTAT_USER_OFFSET);
}

/*!
    \brief      get OB_DATA in register FMC_OBSTAT (API_ID(0x0023U))
    \param[in]  none
    \param[out] none
    \retval     uint16_t, ob_data
*/
uint16_t ob_data_get(void)
{
    return (uint16_t)((FMC_OBSTAT & FMC_OBSTAT_DATA) >> OBSTAT_DATA_OFFSET);
}

/*!
    \brief      get the FMC option byte write protection (OB_WP) in register FMC_WP (API_ID(0x0024U))
    \param[in]  none
    \param[out] none
    \retval     uint32_t, the FMC write protection option bytes value
*/
uint32_t ob_write_protection_get(void)
{
    /* return the FMC write protection option bytes value */
    return (uint32_t)FMC_WP;
}

/*!
    \brief      get the FMC option bytes security protection state (API_ID(0x0025U))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ob_security_protection_flag_get(void)
{
    FlagStatus spc_state = RESET;

    if(RESET != (FMC_OBSTAT & FMC_OBSTAT_SPC)) {
        spc_state = SET;
    } else {
        spc_state = RESET;
    }
    return spc_state;
}

/*!
    \brief      get the FMC ECC error address in register FMC_ECCCS (API_ID(0x0026U))
    \param[in]  none
    \param[out] none
    \retval     uint16_t, the FMC ECC error address
*/
uint16_t fmc_ecc_error_address_get(void)
{
    /* return the FMC write protection option bytes value */
    return (uint16_t)((FMC_ECCCS & BITS(16U, 31U)) >> 16U);
}

/*!
    \brief      get FMC flag status (API_ID(0x0027U))
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_BUSY: flash busy flag
      \arg        FMC_FLAG_PGSERR: flash program sequence error flag
      \arg        FMC_FLAG_PGERR: flash program error flag
      \arg        FMC_FLAG_PGAERR: flash program alignment error flag
      \arg        FMC_FLAG_WPERR: flash erase/program protection error flag
      \arg        FMC_FLAG_END: flash end of operation flag
      \arg        FMC_FLAG_CBCMDERR: flash checked area by the check blank command is all 0xFF or not flag
      \arg        FMC_FLAG_ECCCOR: single bit ECC error flag
      \arg        FMC_FLAG_ECCDET: double bit ECC error flag
      \arg        FMC_FLAG_SYSECC: system memory flash read ECC error flag
      \arg        FMC_FLAG_MFECC: main flash read ECC error flag
      \arg        FMC_FLAG_OTPECC: OTP read ECC error flag
      \arg        FMC_FLAG_OBECC: OPT read ECC error flag
      \arg        FMC_FLAG_DFECC: data flash read ECC error flag
      \arg        FMC_FLAG_SYSECCBK: ECC error flag in main flash bank or data flash bank
      \arg        FMC_FLAG_OBERR: option bytes error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flag_get(fmc_flag_enum flag)
{
    FlagStatus ret;

    /* get flag */
    if(0U != (FMC_REG_VAL(flag) & BIT(FMC_BIT_POS(flag)))) {
        ret = SET;
    } else {
        ret = RESET;
    }

    return ret;
}

/*!
    \brief      clear FMC flag status (API_ID(0x0028U))
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_PGSERR: flash program sequence error flag
      \arg        FMC_FLAG_PGERR: flash program error flag
      \arg        FMC_FLAG_PGAERR: flash program alignment error flag
      \arg        FMC_FLAG_WPERR: flash erase/program protection error flag
      \arg        FMC_FLAG_END: flash end of operation flag
      \arg        FMC_FLAG_CBCMDERR: flash checked area by the check blank command is all 0xFF or not flag
      \arg        FMC_FLAG_ECCCOR: single bit ECC error flag
      \arg        FMC_FLAG_ECCDET: double bit ECC error flag
      \arg        FMC_FLAG_MFECC: main flash read ECC error flag
      \arg        FMC_FLAG_OTPECC: OTP read ECC error flag
      \arg        FMC_FLAG_OBECC: OPT read ECC error flag
      \arg        FMC_FLAG_DFECC: data flash read ECC error flag
      \arg        FMC_FLAG_SYSECCBK: ECC error flag in main flash bank or data flash bank
      \arg        FMC_FLAG_OBERR: option bytes error flag
    \param[out] none
    \retval     none
*/
void fmc_flag_clear(fmc_flag_enum flag)
{
    /* clear the flags in STAT/ECCCS register */
    FMC_REG_VAL(flag) = BIT(FMC_BIT_POS(flag));
}

/*!
    \brief      enable FMC interrupt (API_ID(0x0029U))
    \param[in]  interrupt: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_ERR: FMC error interrupt
      \arg        FMC_INT_END: FMC end of operation interrupt
      \arg        FMC_INT_ECCCOR: single bit ECC error interrupt
      \arg        FMC_INT_ECCDET: double bit ECC error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_enable(fmc_interrupt_enum interrupt)
{
    /* enable interrupt in CTL0 register */
    FMC_REG_VAL(interrupt) |= BIT(FMC_BIT_POS(interrupt));
}

/*!
    \brief      disable FMC interrupt (API_ID(0x002AU))
    \param[in]  interrupt: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_ERR: FMC error interrupt
      \arg        FMC_INT_END: FMC end of operation interrupt
      \arg        FMC_INT_ECCCOR: single bit ECC error interrupt
      \arg        FMC_INT_ECCDET: double bit ECC error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_disable(fmc_interrupt_enum interrupt)
{
    /* disable interrupt in CTL0 register */
    FMC_REG_VAL(interrupt) &= ~BIT(FMC_BIT_POS(interrupt));
}

/*!
    \brief      get FMC interrupt flag status (API_ID(0x002BU))
    \param[in]  int_flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_PGSERR: flash program sequence error interrupt flag
      \arg        FMC_INT_FLAG_PGERR: flash program error interrupt flag
      \arg        FMC_INT_FLAG_PGAERR: flash program alignment error interrupt flag
      \arg        FMC_INT_FLAG_WPERR: flash erase/program protection error interrupt flag
      \arg        FMC_INT_FLAG_END: flash end of operation interrupt flag
      \arg        FMC_INT_FLAG_CBCMDERR: flash checked area by the check blank command is all 0xFF or not interrupt flag
      \arg        FMC_INT_FLAG_ECCCOR: single bit ECC error interrupt flag
      \arg        FMC_INT_FLAG_ECCDET: double bit ECC error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_interrupt_flag_get(fmc_interrupt_flag_enum int_flag)
{
    uint32_t intenable = 0U, flagstatus = 0U;
    FlagStatus ret;

    /* get the interrupt enable bit status */
    intenable = (FMC_REG_VAL(int_flag) & BIT(FMC_BIT_POS(int_flag)));
    /* get the corresponding flag bit status */
    flagstatus = (FMC_REG_VAL2(int_flag) & BIT(FMC_BIT_POS2(int_flag)));

    if(flagstatus && intenable) {
        ret = SET;
    } else {
        ret = RESET;
    }

    return ret;
}

/*!
    \brief      clear FMC interrupt flag status (API_ID(0x002CU))
    \param[in]  int_flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_PGSERR: flash program sequence error interrupt flag
      \arg        FMC_INT_FLAG_PGERR: flash program error interrupt flag
      \arg        FMC_INT_FLAG_PGAERR: flash program alignment error interrupt flag
      \arg        FMC_INT_FLAG_WPERR: flash erase/program protection error interrupt flag
      \arg        FMC_INT_FLAG_END: flash end of operation interrupt flag
      \arg        FMC_INT_FLAG_CBCMDERR: flash checked area by the check blank command is all 0xFF or not interrupt flag
      \arg        FMC_INT_FLAG_ECCCOR: single bit ECC error interrupt flag
      \arg        FMC_INT_FLAG_ECCDET: double bit ECC error interrupt flag
    \param[out] none
    \retval     none
*/
void fmc_interrupt_flag_clear(fmc_interrupt_flag_enum int_flag)
{
    /* clear the interrupt flag in STAT0/STAT1 register */
    FMC_REG_VAL2(int_flag) = BIT(FMC_BIT_POS2(int_flag));
}

/*!
    \brief      get FMC flash state (API_ID(0x002DU))
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_CBCMDERR: the checked area not blank error
*/
static fmc_state_enum fmc_flash_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_BUSY)) {
        fmc_state = FMC_BUSY;
    } else {
        if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_WPERR)) {
            fmc_state = FMC_WPERR;
        } else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_PGERR)) {
            fmc_state = FMC_PGERR;
        } else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_PGAERR)) {
            fmc_state = FMC_PGAERR;
        } else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_PGSERR)) {
            fmc_state = FMC_PGSERR;
        } else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_CBCMDERR)) {
            fmc_state = FMC_CBCMDERR;
        } else {
            /* illegal parameters */
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC flash is ready or not (API_ID(0x002EU))
    \param[in]  timeout: timeout count
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
static fmc_state_enum fmc_flash_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_BUSY;

    /* wait for FMC ready */
    do {
        /* get FMC state */
        fmc_state = fmc_flash_state_get();
        timeout--;
    } while((FMC_BUSY == fmc_state) && (0U != timeout));

    if(FMC_BUSY == fmc_state) {
        fmc_state = FMC_TOERR;
    }
    /* return the FMC state */
    return fmc_state;
}
