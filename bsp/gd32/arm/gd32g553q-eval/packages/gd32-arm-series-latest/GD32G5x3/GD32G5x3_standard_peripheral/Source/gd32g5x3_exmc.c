/*!
    \file    gd32g5x3_exmc.c
    \brief   EXMC driver

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

#include "gd32g5x3_exmc.h"
#include <stdlib.h>

/* EXMC bank0 register reset value */
#define BANK_SNCTL_REGION0_RESET          ((uint32_t)0x000030DAU)
#define BANK_SNCTL_REGION1_2_3_RESET      ((uint32_t)0x000030D2U)
#define BANK_SNTCFG_RESET                 ((uint32_t)0x0FFFFFFFU)
#define BANK_SNWTCFG_RESET                ((uint32_t)0x0FFFFFFFU)
#define BANK_SNLATDEC_RESET               ((uint32_t)0x00000000U)

/* EXMC register bit offset */
#define SNCTL_NRMUX_OFFSET                ((uint32_t)1U)
#define SNCTL_SBRSTEN_OFFSET              ((uint32_t)8U)
#define SNCTL_WRAPEN_OFFSET               ((uint32_t)10U)
#define SNCTL_WREN_OFFSET                 ((uint32_t)12U)
#define SNCTL_NRWTEN_OFFSET               ((uint32_t)13U)
#define SNCTL_EXMODEN_OFFSET              ((uint32_t)14U)
#define SNCTL_ASYNCWAIT_OFFSET            ((uint32_t)15U)
#define SNCTL_BLSET_OFFSET                ((uint32_t)22U)

#define SNTCFG_ASET_OFFSET                ((uint32_t)0U)
#define SNTCFG_AHLD_OFFSET                ((uint32_t)4U)
#define SNTCFG_DSET_OFFSET                ((uint32_t)8U)
#define SNTCFG_BUSLAT_OFFSET              ((uint32_t)16U)

#define SNWTCFG_WAHLD_OFFSET              ((uint32_t)4U)
#define SNWTCFG_WDSET_OFFSET              ((uint32_t)8U)
#define SNWTCFG_WBUSLAT_OFFSET            ((uint32_t)16U)


/*!
    \brief      deinitialize EXMC NOR/SRAM region
    \param[in]  exmc_norsram_region: select the region of bank0
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK0_NORSRAM_REGIONx(x=0..3)
    \param[out] none
    \retval     none
*/
void exmc_norsram_deinit(uint32_t exmc_norsram_region)
{
    /* reset the registers */
    if(EXMC_BANK0_NORSRAM_REGION0 == exmc_norsram_region) {
        EXMC_SNCTL(exmc_norsram_region) = BANK_SNCTL_REGION0_RESET;
    } else {
        EXMC_SNCTL(exmc_norsram_region) = BANK_SNCTL_REGION1_2_3_RESET;
    }
    EXMC_SNTCFG(exmc_norsram_region) = BANK_SNTCFG_RESET;
    EXMC_SNWTCFG(exmc_norsram_region) = BANK_SNWTCFG_RESET;
    EXMC_SNLATDEC(exmc_norsram_region) = BANK_SNLATDEC_RESET;
}

/*!
    \brief      initialize exmc_norsram_parameter_struct with the default values
    \param[in]  none
    \param[out] exmc_norsram_init_struct: the initialized struct exmc_norsram_parameter_struct pointer
    \retval     none
*/
void exmc_norsram_struct_para_init(exmc_norsram_parameter_struct *exmc_norsram_init_struct)
{
    /* configure the structure with default values */
    exmc_norsram_init_struct->norsram_region = EXMC_BANK0_NORSRAM_REGION0;
    exmc_norsram_init_struct->address_data_mux = ENABLE;
    exmc_norsram_init_struct->memory_type = EXMC_MEMORY_TYPE_SRAM;
    exmc_norsram_init_struct->databus_width = EXMC_NOR_DATABUS_WIDTH_8B;
    exmc_norsram_init_struct->burst_mode = DISABLE;
    exmc_norsram_init_struct->nwait_polarity = EXMC_NWAIT_POLARITY_LOW;
    exmc_norsram_init_struct->wrap_burst_mode = DISABLE;
    exmc_norsram_init_struct->nwait_config = EXMC_NWAIT_CONFIG_BEFORE;
    exmc_norsram_init_struct->memory_write = ENABLE;
    exmc_norsram_init_struct->nwait_signal = ENABLE;
    exmc_norsram_init_struct->extended_mode = DISABLE;
    exmc_norsram_init_struct->asyn_wait = DISABLE;
    exmc_norsram_init_struct->write_mode = EXMC_ASYN_WRITE;

    /* read/write timing configure */
    exmc_norsram_init_struct->read_write_timing = (void *)NULL;

    /* write timing configure, when extended mode is used */
    exmc_norsram_init_struct->write_timing = (void *)NULL;
}

/*!
    \brief      initialize EXMC NOR/SRAM region
    \param[in]  exmc_norsram_parameter_struct: configure the EXMC NOR/SRAM parameter
                  norsram_region: EXMC_BANK0_NORSRAM_REGIONx,x=0..3
                  write_mode: EXMC_ASYN_WRITE,EXMC_SYN_WRITE
                  extended_mode: ENABLE or DISABLE
                  asyn_wait: ENABLE or DISABLE
                  nwait_signal: ENABLE or DISABLE
                  memory_write: ENABLE or DISABLE
                  nwait_config: EXMC_NWAIT_CONFIG_BEFORE,EXMC_NWAIT_CONFIG_DURING
                  wrap_burst_mode: ENABLE or DISABLE
                  nwait_polarity: EXMC_NWAIT_POLARITY_LOW,EXMC_NWAIT_POLARITY_HIGH
                  burst_mode: ENABLE or DISABLE
                  databus_width: EXMC_NOR_DATABUS_WIDTH_8B,EXMC_NOR_DATABUS_WIDTH_16B
                  memory_type: EXMC_MEMORY_TYPE_SRAM,EXMC_MEMORY_TYPE_PSRAM,EXMC_MEMORY_TYPE_NOR
                  address_data_mux: ENABLE or DISABLE
                  read_write_timing: struct exmc_norsram_timing_parameter_struct set the time
                    asyn_access_mode: EXMC_ACCESS_MODE_A,EXMC_ACCESS_MODE_B,EXMC_ACCESS_MODE_C,EXMC_ACCESS_MODE_D
                    syn_data_latency: EXMC_DATALAT_n_CLK,(n=2,..,17)
                    syn_data_latency_dec: 0,..,7
                    syn_clk_division: EXMC_SYN_CLOCK_RATIO_DISABLE, EXMC_SYN_CLOCK_RATIO_n_CLK,(n=2,..,16)
                    bus_latency: 0,..,15
                    asyn_data_setuptime: 1,..,255
                    asyn_address_holdtime: 1,..,15
                    asyn_address_setuptime: 0,..,15
                    byte_lane_setuptime: 0,..,3
                  write_timing: struct exmc_norsram_timing_parameter_struct set the time
                    asyn_access_mode: EXMC_ACCESS_MODE_A,EXMC_ACCESS_MODE_B,EXMC_ACCESS_MODE_C,EXMC_ACCESS_MODE_D
                    syn_data_latency: EXMC_DATALAT_n_CLK,(n=2,..,17)
                    syn_data_latency_dec: 0,..,7
                    syn_clk_division: EXMC_SYN_CLOCK_RATIO_DISABLE, EXMC_SYN_CLOCK_RATIO_n_CLK,(n=2,..,16)
                    bus_latency: 0,..,15
                    asyn_data_setuptime: 1,..,255
                    asyn_address_holdtime: 1,..,15
                    asyn_address_setuptime: 0,..,15
                    byte_lane_setuptime: 0,..,3
    \param[out] none
    \retval     none
*/
void exmc_norsram_init(exmc_norsram_parameter_struct *exmc_norsram_init_struct)
{
    uint32_t snctl = 0x00000000U, sntcfg = 0x00000000U, snwtcfg = 0x00000000U, snlatdec = 0x00000000U;

    /* get the register value */
    snctl = EXMC_SNCTL(exmc_norsram_init_struct->norsram_region);

    /* clear relative bits */
    snctl &= ((uint32_t)~(EXMC_SNCTL_NRMUX | EXMC_SNCTL_NRTP | EXMC_SNCTL_NRW | EXMC_SNCTL_SBRSTEN |
                          EXMC_SNCTL_NREN | EXMC_SNCTL_NRWTPOL | EXMC_SNCTL_WRAPEN | EXMC_SNCTL_NRWTCFG |
                          EXMC_SNCTL_WEN | EXMC_SNCTL_NRWTEN | EXMC_SNCTL_EXMODEN | EXMC_SNCTL_ASYNCWAIT |
                          EXMC_SNCTL_SYNCWR | EXMC_SNCTL_BLSET));

    snctl |= (uint32_t)(exmc_norsram_init_struct->address_data_mux << SNCTL_NRMUX_OFFSET) |
             exmc_norsram_init_struct->memory_type |
             exmc_norsram_init_struct->databus_width |
             (exmc_norsram_init_struct->burst_mode << SNCTL_SBRSTEN_OFFSET) |
             exmc_norsram_init_struct->nwait_polarity |
             (exmc_norsram_init_struct->wrap_burst_mode << SNCTL_WRAPEN_OFFSET) |
             exmc_norsram_init_struct->nwait_config |
             (exmc_norsram_init_struct->memory_write << SNCTL_WREN_OFFSET) |
             (exmc_norsram_init_struct->nwait_signal << SNCTL_NRWTEN_OFFSET) |
             (exmc_norsram_init_struct->extended_mode << SNCTL_EXMODEN_OFFSET) |
             (exmc_norsram_init_struct->asyn_wait << SNCTL_ASYNCWAIT_OFFSET) |
             exmc_norsram_init_struct->write_mode |
             (exmc_norsram_init_struct->read_write_timing->byte_lane_setuptime << SNCTL_BLSET_OFFSET);

    sntcfg = (uint32_t)((exmc_norsram_init_struct->read_write_timing->asyn_address_setuptime << SNTCFG_ASET_OFFSET) & EXMC_SNTCFG_ASET) |
             ((exmc_norsram_init_struct->read_write_timing->asyn_address_holdtime << SNTCFG_AHLD_OFFSET) & EXMC_SNTCFG_AHLD) |
             ((exmc_norsram_init_struct->read_write_timing->asyn_data_setuptime << SNTCFG_DSET_OFFSET) & EXMC_SNTCFG_DSET) |
             ((exmc_norsram_init_struct->read_write_timing->bus_latency << SNTCFG_BUSLAT_OFFSET) & EXMC_SNTCFG_BUSLAT) |
             exmc_norsram_init_struct->read_write_timing->syn_clk_division |
             exmc_norsram_init_struct->read_write_timing->syn_data_latency |
             exmc_norsram_init_struct->read_write_timing->asyn_access_mode;

    /* configure data latency decreasing value */
    snlatdec = (uint32_t)(exmc_norsram_init_struct->read_write_timing->syn_data_latency_dec & EXMC_SNLATDEC_LATDEC);

    /* nor flash access enable */
    if(EXMC_MEMORY_TYPE_NOR == exmc_norsram_init_struct->memory_type) {
        snctl |= (uint32_t)EXMC_SNCTL_NREN;
    }

    /* extended mode configure */
    if(ENABLE == exmc_norsram_init_struct->extended_mode) {
        snwtcfg = (uint32_t)(exmc_norsram_init_struct->write_timing->asyn_address_setuptime & EXMC_SNWTCFG_WASET) |
                  ((exmc_norsram_init_struct->write_timing->asyn_address_holdtime << SNWTCFG_WAHLD_OFFSET) & EXMC_SNWTCFG_WAHLD) |
                  ((exmc_norsram_init_struct->write_timing->asyn_data_setuptime << SNWTCFG_WDSET_OFFSET) & EXMC_SNWTCFG_WDSET) |
                  ((exmc_norsram_init_struct->write_timing->bus_latency << SNWTCFG_WBUSLAT_OFFSET) & EXMC_SNWTCFG_WBUSLAT) |
                  exmc_norsram_init_struct->write_timing->asyn_access_mode;
    } else {
        snwtcfg = BANK_SNWTCFG_RESET;
    }

    /* configure the registers */
    EXMC_SNCTL(exmc_norsram_init_struct->norsram_region) = snctl;
    EXMC_SNTCFG(exmc_norsram_init_struct->norsram_region) = sntcfg;
    EXMC_SNWTCFG(exmc_norsram_init_struct->norsram_region) = snwtcfg;
    EXMC_SNLATDEC(exmc_norsram_init_struct->norsram_region) = snlatdec;
}

/*!
    \brief      enable EXMC NOR/PSRAM bank region
    \param[in]  exmc_norsram_region: specifie the region of NOR/PSRAM bank
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK0_NORSRAM_REGIONx(x=0..3)
    \param[out] none
    \retval     none
*/
void exmc_norsram_enable(uint32_t exmc_norsram_region)
{
    EXMC_SNCTL(exmc_norsram_region) |= (uint32_t)EXMC_SNCTL_NRBKEN;
}

/*!
    \brief      disable EXMC NOR/PSRAM bank region
    \param[in]  exmc_norsram_region: specifie the region of NOR/PSRAM Bank
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK0_NORSRAM_REGIONx(x=0..3)
    \param[out] none
    \retval     none
*/
void exmc_norsram_disable(uint32_t exmc_norsram_region)
{
    EXMC_SNCTL(exmc_norsram_region) &= ~(uint32_t)EXMC_SNCTL_NRBKEN;
}

/*!
    \brief    configure consecutive clock
    \param[in]  clock_mode: specify when the clock is generated
                only one parameter can be selected which is shown as below:
      \arg        EXMC_CLOCK_SYNC_ONLY: the clock is generated only during synchronous access
      \arg        EXMC_CLOCK_UNCONDITIONALLY: the clock is generated unconditionally
    \param[out] none
    \retval     none
*/
void exmc_norsram_consecutive_clock_config(uint32_t clock_mode)
{
    EXMC_SNCTL(EXMC_BANK0_NORSRAM_REGION0) &= ~EXMC_SNCTL_CCK;
    EXMC_SNCTL(EXMC_BANK0_NORSRAM_REGION0) |= clock_mode;
}

/*!
    \brief      configure CRAM page size
    \param[in]  exmc_norsram_region: specify the region of NOR/PSRAM bank
                only one parameter can be selected which is shown as below:
      \arg        EXMC_BANK0_NORSRAM_REGIONx(x=0..3)
    \param[in]  page_size: CRAM page size
                only one parameter can be selected which is shown as below:
      \arg        EXMC_CRAM_AUTO_SPLIT: the clock is generated only during synchronous access
      \arg        EXMC_CRAM_PAGE_SIZE_128_BYTES: page size is 128 bytes
      \arg        EXMC_CRAM_PAGE_SIZE_256_BYTES: page size is 256 bytes
      \arg        EXMC_CRAM_PAGE_SIZE_512_BYTES: page size is 512 bytes
      \arg        EXMC_CRAM_PAGE_SIZE_1024_BYTES: page size is 1024 bytes
    \param[out] none
    \retval     none
*/
void exmc_norsram_page_size_config(uint32_t exmc_norsram_region, uint32_t page_size)
{
    /* reset the bits */
    EXMC_SNCTL(exmc_norsram_region) &= ~EXMC_SNCTL_CPS;

    /* set the CPS bits */
    EXMC_SNCTL(exmc_norsram_region) |= page_size;
}

/*!
    \brief    configure EXMC NOR/SRAM(bank0 region0) write FIFO
    \param[in]  wr_fifo: write fifo configuration
                only one parameter can be selected which is shown as below:
      \arg        EXMC_WRITE_FIFO_ENABLE: enable write FIFO
      \arg        EXMC_WRITE_FIFO_DISABLE: disable write FIFO
    \param[out] none
    \retval     none
*/
void exmc_norsram_write_fifo_config(uint32_t wr_fifo)
{
    /* reset the bits */
    EXMC_SNCTL(EXMC_BANK0_NORSRAM_REGION0) &= ~EXMC_SNCTL_WFIFODIS;

    /* set the WFIFODIS bit */
    EXMC_SNCTL(EXMC_BANK0_NORSRAM_REGION0) |= wr_fifo;
}

/*!
    \brief      get EXMC NOR/SRAM(bank0 region0) region FIFO status
    \param[in]  none
    \param[out] none
    \retval     NOR/SRAM write FIFO status
      \arg        EXMC_FIFO_NOT_EMPTY: NOR/SRAM write FIFO is not empty
      \arg        EXMC_FIFO_EMPTY: NOR/SRAM write FIFO is empty
*/
uint32_t exmc_norsram_status_get(void)
{
    return (uint32_t)(EXMC_SNSTAT & EXMC_SNSTAT_FIFOEPT);
}
