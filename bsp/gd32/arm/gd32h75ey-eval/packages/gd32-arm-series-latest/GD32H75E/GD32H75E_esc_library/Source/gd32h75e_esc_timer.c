/*!
    \file    esc_timer.c
    \brief   ESC timer driver basic configuration

    \version 2025-01-24, V1.1.0, firmware for GD32H75E
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

#include "gd32h75e.h"
#include "gd32h75e_esc_ospi.h"
#include "gd32h75e_esc_timer.h"

/*!
    \brief      enable a ESC BASIC TIMER
    \param[in]  none
    \param[out] none
    \retval     none
*/
void esc_timer_enable(void)
{
    uint32_t temp_value = 0U;

    ospi_read(&ospi_init_struct, ESC_TIMER_CTL0, (uint8_t *)&temp_value, 4U);
    temp_value = temp_value | BIT(29);
    ospi_write(&ospi_init_struct, ESC_TIMER_CTL0, (uint8_t *)&temp_value, 4U);
}

/*!
    \brief      disable a ESC BASIC TIMER
    \param[in]  none
    \param[out] none
    \retval     none
*/
void esc_timer_disable(void)
{
    uint32_t temp_value = 0U;

    temp_value = 0x0000FFFFU;
    ospi_write(&ospi_init_struct, ESC_TIMER_CTL0, (uint8_t *)&temp_value, 4U);

}

/*!
    \brief      configure ESC BASIC TIMER pre-load register value
    \param[in]  preload: the counter pre-load value,0~65535
    \param[out] none
    \retval     none
*/
void esc_timer_preload_value_config(uint16_t preload)
{
    uint32_t temp_value = 0U;

    temp_value = 0x20000000U | (uint32_t)preload;
    ospi_write(&ospi_init_struct, ESC_TIMER_CTL0, (uint8_t *)&temp_value, 4U);
}

/*!
    \brief      read ESC BASIC TIMER counter value
    \param[in]  none
    \param[out] none
    \retval     counter value
*/
uint32_t esc_timer_counter_read(void)
{
    uint32_t counter_value = 0U;

    ospi_read(&ospi_init_struct, ESC_TIMER_CNT, (uint8_t *)&counter_value, 4U);

    return counter_value;
}

/*!
    \brief      read ESC FRC counter value
    \param[in]  none
    \param[out] none
    \retval     counter value
*/
uint32_t esc_frc_counter_read(void)
{
    uint32_t counter_value = 0U;

    ospi_read(&ospi_init_struct, ESC_FRC_CNT, (uint8_t *)&counter_value, 4U);

    return counter_value;
}
