/*!
    \file    esc_phy.c
    \brief   ESC phy driver basic configuration

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
#include "gd32h75e_esc_phy.h"

/*!
    \brief      phy pdi read register
    \param[in]  readbuffer: pointer to data to be read
    \param[in]  address: read start address
    \param[in]  count: size of data to read
\param[out] none
\retval     none
*/
static void phy_pdi_read(uint8_t *readbuffer, uint16_t address, uint8_t count)
{
    ospi_read_register(readbuffer, address, count);
}

/*!
    \brief      phy pdi write register
    \param[in]  writebuffer: pointer to data to be written
    \param[in]  address: write start address
    \param[in]  count: size of data to write
    \param[out] none
    \retval     none
*/
static void phy_pdi_write(uint8_t *writebuffer, uint16_t address, uint8_t count)
{
    ospi_write_register(writebuffer, address, count);
}

/*!
    \brief      read PHY data from specified register
    \param[in]  phy_addr: PHY address, range: 0...31
    \param[in]  phy_reg:  PHY register address, range: 0...31
    \param[out] none
    \retval     value of PHY data
*/
uint32_t esc_phy_read(uint8_t phy_addr, uint8_t phy_reg)
{
    uint8_t tempreg   = 0U;
    uint32_t value    = 0U;
    uint32_t res      = 0U;

    /* PDI access MDIO allowed */
    tempreg = MII_ACCESS;
    phy_pdi_write(&tempreg, ESC_MII_PDI_STATE, 1U);

    /* check mdio idle state*/
    do {
        phy_pdi_read(&tempreg, ESC_MII_STATUS, 1U);
    } while(tempreg & MII_BUSY_MASK);

    /* write PHY address and PHY register*/
    value = phy_addr | (phy_reg << 8U);
    phy_pdi_write((uint8_t *)&value, ESC_PHY_ADDR, 2U);

    /* write PHY command */
    tempreg = 0x01U;
    phy_pdi_write(&tempreg, ESC_MII_STATUS, 1U);

    /* reset mdio access*/
    tempreg = PDI_ACCESS;
    phy_pdi_write(&tempreg, ESC_MII_PDI_STATE, 1U);

    /* wait for mdio idle and get data*/
    do {
        phy_pdi_read(&tempreg, ESC_MII_STATUS, 1U);
    } while(tempreg & MII_BUSY_MASK);

    phy_pdi_read((uint8_t *)&res, ESC_PHY_DATA, 2U);

    return res;
}

/*!
    \brief      write PHY data to specified register
    \param[in]  phy_addr: PHY address, range: 0...31
    \param[in]  phy_reg:  PHY register address, range: 0...31
    \param[in]  phy_data: PHY data to be write
    \param[out] none
    \retval     value of PHY data
*/
void esc_phy_write(uint8_t phy_addr, uint8_t phy_reg, uint16_t phy_data)
{
    uint8_t tempreg  = 0U;
    uint32_t value   = 0U;

    /* PDI access MDIO allowed */
    tempreg = MII_ACCESS ;
    phy_pdi_write(&tempreg, ESC_MII_PDI_STATE, 1U);

    /* check mdio idle state */
    do {
        phy_pdi_read(&tempreg, ESC_MII_STATUS, 1U);
    } while(tempreg & MII_BUSY_MASK);

    /* write PHY address and PHY register */
    value = phy_addr | (phy_reg << 8U);
    phy_pdi_write((uint8_t *)&value, ESC_PHY_ADDR, 2U);

    /* write PHY data */
    phy_pdi_write((uint8_t *)&phy_data, ESC_PHY_DATA, 2U);

    /* write PHY command and enable */
    value = (MII_WRITE_CMD << 8U) | MII_WRITE_EN;
    phy_pdi_write((uint8_t *)&value, ESC_MII_CONTROL, 2U);

    /* reset mdio access */
    tempreg = MII_ACCESS;
    phy_pdi_write(&tempreg, ESC_MII_PDI_STATE, 1U);

    /* wait for mdio idle */
    do {
        phy_pdi_read(&tempreg, ESC_MII_STATUS, 1U);
    } while(tempreg & MII_BUSY_MASK);
}

/*!
    \brief      read data from specified MMD register
    \param[in]  phy_addr:       PHY address, range: 0...31
    \param[in]  mmd_addr:       PHY register address, range: 0...31
    \param[in]  mmd_addr_index: the index of the MMD register
    \param[out] none
    \retval     value of PHY data
*/
uint32_t esc_mmd_read(uint8_t phy_addr, uint8_t mmd_addr, uint16_t mmd_addr_index)
{
    uint32_t value   = 0U;

    /* write MMD address and MMD address FUNCTION */
    esc_phy_write(phy_addr, PHY_MMD_CTL, mmd_addr | MMD_ADDR_FUN_MASK);

    /* write MMD address index and MMD FUNCTION */
    esc_phy_write(phy_addr, PHY_MMD_ADDR_DATA, mmd_addr_index);

    /* write MMD address and MMD data FUNCTION */
    esc_phy_write(phy_addr, PHY_MMD_CTL, mmd_addr | MMD_DATA_FUN_MASK);

    /* read data from specified MMD register */
    value = esc_phy_read(phy_addr, PHY_MMD_ADDR_DATA);

    return value;
}

/*!
    \brief      write data to specified MMD register
    \param[in]  phy_addr:       PHY address, range: 0...31
    \param[in]  mmd_addr:       PHY register address, range: 0...31
    \param[in]  mmd_addr_index: the index of the MMD register
    \param[in]  mmd_data:       the data to be write to the MMD register
    \param[out] none
    \retval     value of PHY data
*/
void esc_mmd_write(uint8_t phy_addr, uint8_t mmd_addr, uint16_t mmd_addr_index, uint16_t mmd_data)
{
    /* write MMD address and MMD address FUNCTION */
    esc_phy_write(phy_addr, PHY_MMD_CTL, mmd_addr | MMD_ADDR_FUN_MASK);

    /* write MMD address index and MMD FUNCTION */
    esc_phy_write(phy_addr, PHY_MMD_ADDR_DATA, mmd_addr_index);

    /* write MMD address and MMD data FUNCTION */
    esc_phy_write(phy_addr, PHY_MMD_CTL, mmd_addr | MMD_DATA_FUN_MASK);

    /* write MMD address index and MMD FUNCTION */
    esc_phy_write(phy_addr, PHY_MMD_ADDR_DATA, mmd_addr_index);

    /* write MMD data to specified register */
    esc_phy_write(phy_addr, PHY_MMD_ADDR_DATA, mmd_data);
}

