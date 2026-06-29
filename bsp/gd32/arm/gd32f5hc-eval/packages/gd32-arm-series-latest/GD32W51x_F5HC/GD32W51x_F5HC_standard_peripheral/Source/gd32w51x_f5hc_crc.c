/*!
    \file    gd32w51x_f5hc_crc.c
    \brief   CRC driver

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

#include "gd32w51x_f5hc_crc.h"

#define CRC_DATA_RESET_VALUE      ((uint32_t)0xFFFFFFFFU)
#define CRC_FDATA_RESET_VALUE     ((uint32_t)0x00000000U)

/*!
    \brief      deinit CRC calculation unit (API_ID: 0x0001U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void crc_deinit(void)
{
    CRC_DATA  = CRC_DATA_RESET_VALUE;
    CRC_FDATA = CRC_FDATA_RESET_VALUE;
    CRC_CTL   = CRC_CTL_RST;
}

/*!
    \brief      reset the data register (CRC_DATA) to 0xFFFFFFFF (API_ID: 0x0002U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void crc_data_register_reset(void)
{
    CRC_CTL |= CRC_CTL_RST;
}

/*!
    \brief      read the data register (API_ID: 0x0003U)
    \param[in]  none
    \param[out] none
    \retval     32-bit value of the data register
*/
uint32_t crc_data_register_read(void)
{
    uint32_t data;
    data = CRC_DATA;
    return data;
}

/*!
    \brief      read the free data register (API_ID: 0x0004U)
    \param[in]  none
    \param[out] none
    \retval     8-bit value of the free data register
*/
uint8_t crc_free_data_register_read(void)
{
    uint8_t fdata;
    fdata = (uint8_t)CRC_FDATA;
    return fdata;
}

/*!
    \brief      write the free data register (API_ID: 0x0005U)
    \param[in]  free_data: specified 8-bit data
    \param[out] none
    \retval     none
*/
void crc_free_data_register_write(uint8_t free_data)
{
    CRC_FDATA = (uint32_t)free_data;
}

/*!
    \brief      CRC calculate single 32-bit data (API_ID: 0x0006U)
    \param[in]  sdata: specified 32-bit data
    \param[out] none
    \retval     CRC calculate value (0-0xFFFFFFFF)
*/
uint32_t crc_single_data_calculate(uint32_t sdata)
{
    uint32_t crc_val;
    CRC_DATA = sdata;
    crc_val = CRC_DATA;
    return crc_val;
}

/*!
    \brief      CRC calculate a 32-bit data array (API_ID: 0x0007U)
    \param[in]  array: pointer to the 32-bit input data array
    \param[in]  size: size of the array
    \param[out] none
    \retval     CRC calculate value (0-0xFFFFFFFF)
*/
uint32_t crc_block_data_calculate(uint32_t *array, uint32_t size)
{
    uint32_t index;
    uint32_t data;
    uint32_t crc_val = 0xFFFFFFFFU;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(array)) {
        fw_debug_report_err(CRC_MODULE_ID, API_ID(0x0007U), ERR_PARAM_POINTER);
    } else
#endif
    {
        data = (uint32_t)array;

        for(index = 0U; index < size; index++) {
            CRC_DATA = *(uint32_t *)data;
            data += 4U;
        }
        crc_val = CRC_DATA;
    }
    return crc_val;
}
