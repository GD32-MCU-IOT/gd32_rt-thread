/*!
    \file    esc_syscfg.c
    \brief   ESC syscfg driver basic configuration

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
#include "gd32h75e_esc_syscfg.h"

/*!
    \brief      get chip id value
    \param[in]  none
    \param[out] none
    \retval     chip ID value
*/
uint32_t syscfg_get_chip_id(void)
{
    uint32_t temp_value = 0;

    ospi_read(&ospi_init_struct, ESC_SYSCFG_CHIPID, (uint8_t *)&temp_value, 4);

    return temp_value;
}

/*!
    \brief      get chip version value
    \param[in]  none
    \param[out] none
    \retval     chip version value
*/
uint32_t syscfg_get_chip_version(void)
{
    uint32_t temp_value = 0;

    ospi_read(&ospi_init_struct, ESC_SYSCFG_CHIPVER, (uint8_t *)&temp_value, 4);

    return temp_value;
}
