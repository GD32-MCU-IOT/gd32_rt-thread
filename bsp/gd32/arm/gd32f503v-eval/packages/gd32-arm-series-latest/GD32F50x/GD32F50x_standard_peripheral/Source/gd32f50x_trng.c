/*!
    \file    gd32f50x_trng.c
    \brief   TRNG driver

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

#include "gd32f50x_trng.h"

/*!
    \brief      deinitialize the TRNG(API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_deinit(void)
{
    rcu_periph_reset_enable(RCU_TRNGRST);
    rcu_periph_reset_disable(RCU_TRNGRST);
}

/*!
    \brief      enable the TRNG interface(API_ID(0x0002U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_enable(void)
{
    TRNG_CTL |= TRNG_CTL_TRNGEN;
}

/*!
    \brief      disable the TRNG interface(API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_disable(void)
{
    TRNG_CTL &= ~TRNG_CTL_TRNGEN;
}

/*!
    \brief      get the true random data(API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     the generated random data
*/
uint32_t trng_get_true_random_data(void)
{
    return (TRNG_DATA);
}

/*!
    \brief      configure TRNG analog power mode(API_ID(0x0005U))
    \param[in]  powermode: the power mode selection
                only one parameter can be selected which is shown as below:
      \arg        TRNG_NR_ULTRALOW: TRNG analog power mode ultralow
      \arg        TRNG_NR_LOW:      TRNG analog power mode low
      \arg        TRNG_NR_MEDIUM:   TRNG analog power mode medium
      \arg        TRNG_NR_HIGH:     TRNG analog power mode high
    \param[out] none
    \retval     none
*/
void trng_powermode_config(uint32_t powermode)
{
    uint32_t trng_config = TRNG_CTL;

    trng_config &= ~TRNG_CTL_NR;
    trng_config |= powermode & TRNG_CTL_NR;
    TRNG_CTL = trng_config;
}

/*!
    \brief      get the TRNG status flags(API_ID(0x0006U))
    \param[in]  flag: TRNG status flag, refer to trng_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        TRNG_FLAG_DRDY: random data ready status
      \arg        TRNG_FLAG_CECS: clock error current status
      \arg        TRNG_FLAG_SECS: seed error current status
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus trng_flag_get(trng_flag_enum flag)
{
    FlagStatus ret;
    
    if(RESET != (TRNG_STAT & flag)){
        ret = SET;
    }else{
        ret = RESET;
    }
    
    return ret;
}

/*!
    \brief      enable the TRNG interrupt(API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_interrupt_enable(void) 
{
    TRNG_CTL |= TRNG_CTL_TRNGIE;
}

/*!
    \brief      disable the TRNG interrupt(API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trng_interrupt_disable(void)
{
    TRNG_CTL &= ~TRNG_CTL_TRNGIE;
}

/*!
    \brief      get the TRNG interrupt flags(API_ID(0x0009U))
    \param[in]  int_flag: TRNG interrupt flag, refer to trng_int_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        TRNG_INT_FLAG_CEIF: clock error interrupt flag
      \arg        TRNG_INT_FLAG_SEIF: seed error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus trng_interrupt_flag_get(trng_int_flag_enum int_flag)
{
    FlagStatus ret;

    if(RESET != (TRNG_STAT & int_flag)){
        ret = SET;
    }else{
        ret = RESET;
    }

    return ret;
}

/*!
    \brief      clear the TRNG interrupt flags(API_ID(0x000AU))
    \param[in]  int_flag: TRNG interrupt flag, refer to trng_int_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        TRNG_INT_FLAG_CEIF: clock error interrupt flag
      \arg        TRNG_INT_FLAG_SEIF: seed error interrupt flag
    \param[out] none
    \retval     none
*/
void trng_interrupt_flag_clear(trng_int_flag_enum int_flag)
{
    TRNG_STAT &= ~(uint32_t)int_flag;
}
