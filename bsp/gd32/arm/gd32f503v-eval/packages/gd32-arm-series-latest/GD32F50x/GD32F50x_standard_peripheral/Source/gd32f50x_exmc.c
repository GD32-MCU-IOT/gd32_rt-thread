/*!
    \file    gd32f50x_exmc.c
    \brief   EXMC driver

    \version 2025-11-03, V1.0.0, firmware for GD32F50x
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

#include "gd32f50x_exmc.h"

/* EXMC bank0 register reset value */
#define BANK0_PNCTL_REGION0_RESET        ((uint32_t)0x000030DBU)
#define BANK0_PNTCFG_RESET               ((uint32_t)0x0FFFFFFFU)

/* EXMC bank1 register reset mask */
#define BANK1_NCTL_RESET                 ((uint32_t)0x00000018U)
#define BANK1_NCTCFG_RESET               ((uint32_t)0xFCFCFCFCU)
#define BANK1_NATCFG_RESET               ((uint32_t)0xFCFCFCFCU)

/* EXMC register bit offset */
#define PNCTL_NRMUX_OFFSET               ((uint32_t)1U)
#define PNCTL_SBRSTEN_OFFSET             ((uint32_t)8U)
#define PNCTL_WRAPEN_OFFSET              ((uint32_t)10U)
#define PNCTL_WREN_OFFSET                ((uint32_t)12U)
#define PNCTL_NRWTEN_OFFSET              ((uint32_t)13U)
#define PNCTL_EXMODEN_OFFSET             ((uint32_t)14U)
#define PNCTL_ASYNCWAIT_OFFSET           ((uint32_t)15U)

#define PNTCFG_AHLD_OFFSET               ((uint32_t)4U)
#define PNTCFG_DSET_OFFSET               ((uint32_t)8U)
#define PNTCFG_BUSLAT_OFFSET             ((uint32_t)16U)

#define NCTL_NDWTEN_OFFSET               ((uint32_t)1U)
#define NCTL_ECCEN_OFFSET                ((uint32_t)6U)

#define NCTCFG_COMWAIT_OFFSET            ((uint32_t)8U)
#define NCTCFG_COMHLD_OFFSET             ((uint32_t)16U)
#define NCTCFG_COMHIZ_OFFSET             ((uint32_t)24U)

#define NATCFG_ATTWAIT_OFFSET            ((uint32_t)8U)
#define NATCFG_ATTHLD_OFFSET             ((uint32_t)16U)
#define NATCFG_ATTHIZ_OFFSET             ((uint32_t)24U)

#define INTEN_INTS_OFFSET                ((uint32_t)3U)

/*!
    \brief      deinitialize EXMC NOR/SRAM region (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_norsram_deinit(void)
{
    /* reset the registers */
    EXMC_PNCTL = BANK0_PNCTL_REGION0_RESET;
    EXMC_PNTCFG = BANK0_PNTCFG_RESET;
}

/*!
    \brief      initialize exmc_norsram_parameter_struct with the default values (API_ID(0x0002U))
    \param[in]  exmc_norsram_init_struct: the initialized struct exmc_norsram_parameter_struct pointer
    \param[out] exmc_norsram_init_struct: the initialized struct exmc_norsram_parameter_struct pointer
    \retval     none
*/
void exmc_norsram_struct_para_init(exmc_norsram_parameter_struct* exmc_norsram_init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(exmc_norsram_init_struct)) {
        fw_debug_report_err(EXMC_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure the structure with default values */
        exmc_norsram_init_struct->address_data_mux = ENABLE;
        exmc_norsram_init_struct->memory_type = EXMC_MEMORY_TYPE_NOR;
        exmc_norsram_init_struct->databus_width = EXMC_NOR_DATABUS_WIDTH_8B;
        exmc_norsram_init_struct->burst_mode = DISABLE;
        exmc_norsram_init_struct->nwait_polarity = EXMC_NWAIT_POLARITY_LOW;
        exmc_norsram_init_struct->wrap_burst_mode = DISABLE;
        exmc_norsram_init_struct->nwait_config = EXMC_NWAIT_CONFIG_BEFORE;
        exmc_norsram_init_struct->memory_write = ENABLE;
        exmc_norsram_init_struct->nwait_signal = ENABLE;
        exmc_norsram_init_struct->asyn_wait = DISABLE;
        exmc_norsram_init_struct->write_mode = EXMC_ASYN_WRITE;

        /* read/write timing configure */
        exmc_norsram_init_struct->read_write_timing->asyn_address_setuptime = 0xFU;
        exmc_norsram_init_struct->read_write_timing->asyn_address_holdtime = 0xFU;
        exmc_norsram_init_struct->read_write_timing->asyn_data_setuptime = 0xFFU;
        exmc_norsram_init_struct->read_write_timing->bus_latency = 0xFU;
        exmc_norsram_init_struct->read_write_timing->syn_clk_division = EXMC_SYN_CLOCK_RATIO_16_CLK;
        exmc_norsram_init_struct->read_write_timing->syn_data_latency = EXMC_DATALAT_17_CLK;
    }
}

/*!
    \brief      initialize EXMC NOR/SRAM region (API_ID(0x0003U))
    \param[in]  exmc_norsram_init_struct: configure the EXMC NOR/SRAM parameter
                  write_mode: EXMC_ASYN_WRITE,EXMC_SYN_WRITE
                  asyn_wait: ENABLE or DISABLE
                  nwait_signal: ENABLE or DISABLE
                  memory_write: ENABLE or DISABLE
                  nwait_config: EXMC_NWAIT_CONFIG_BEFORE,EXMC_NWAIT_CONFIG_DURING
                  wrap_burst_mode: ENABLE or DISABLE
                  nwait_polarity: EXMC_NWAIT_POLARITY_LOW,EXMC_NWAIT_POLARITY_HIGH
                  burst_mode: ENABLE or DISABLE
                  databus_width: EXMC_NOR_DATABUS_WIDTH_8B,EXMC_NOR_DATABUS_WIDTH_16B
                  memory_type: EXMC_MEMORY_TYPE_PSRAM,EXMC_MEMORY_TYPE_NOR
                  address_data_mux: ENABLE or DISABLE
                  read_write_timing: struct exmc_norsram_timing_parameter_struct set the time
    \param[out] none
    \retval     none
*/
void exmc_norsram_init(exmc_norsram_parameter_struct* exmc_norsram_init_struct)
{
    uint32_t pnctl = 0x00000000U,pntcfg = 0x00000000U;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(exmc_norsram_init_struct)) {
        fw_debug_report_err(EXMC_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the register value */
        pnctl = EXMC_PNCTL;

        /* clear relative bits */
        pnctl &= ((uint32_t)~(EXMC_PNCTL_NRMUX | EXMC_PNCTL_NRTP | EXMC_PNCTL_NRW | EXMC_PNCTL_SBRSTEN | 
                              EXMC_PNCTL_NREN | EXMC_PNCTL_NRWTPOL | EXMC_PNCTL_WRAPEN | EXMC_PNCTL_NRWTCFG | 
                              EXMC_PNCTL_WREN | EXMC_PNCTL_NRWTEN | EXMC_PNCTL_ASYNCWAIT | EXMC_PNCTL_SYNCWR ));

        pnctl |= (uint32_t)((exmc_norsram_init_struct->address_data_mux << PNCTL_NRMUX_OFFSET) & EXMC_PNCTL_NRMUX) |
                           (exmc_norsram_init_struct->memory_type & EXMC_PNCTL_NRTP) |
                           (exmc_norsram_init_struct->databus_width & EXMC_PNCTL_NRW) |
                           ((exmc_norsram_init_struct->burst_mode << PNCTL_SBRSTEN_OFFSET) & EXMC_PNCTL_SBRSTEN) |
                           (exmc_norsram_init_struct->nwait_polarity & EXMC_PNCTL_NRWTPOL)|
                           ((exmc_norsram_init_struct->wrap_burst_mode << PNCTL_WRAPEN_OFFSET) & EXMC_PNCTL_WRAPEN) |
                           (exmc_norsram_init_struct->nwait_config & EXMC_PNCTL_NRWTCFG) |
                           ((exmc_norsram_init_struct->memory_write << PNCTL_WREN_OFFSET) & EXMC_PNCTL_WREN) |
                           ((exmc_norsram_init_struct->nwait_signal << PNCTL_NRWTEN_OFFSET) & EXMC_PNCTL_NRWTEN) |
                           ((exmc_norsram_init_struct->asyn_wait << PNCTL_ASYNCWAIT_OFFSET) & EXMC_PNCTL_ASYNCWAIT) |
                           (exmc_norsram_init_struct->write_mode & EXMC_PNCTL_SYNCWR);

        pntcfg = (uint32_t)((exmc_norsram_init_struct->read_write_timing->asyn_address_setuptime - 1U ) & EXMC_PNTCFG_ASET )|
                           (((exmc_norsram_init_struct->read_write_timing->asyn_address_holdtime - 1U ) << PNTCFG_AHLD_OFFSET ) & EXMC_PNTCFG_AHLD ) |
                           (((exmc_norsram_init_struct->read_write_timing->asyn_data_setuptime - 1U ) << PNTCFG_DSET_OFFSET ) & EXMC_PNTCFG_DSET ) |
                           (((exmc_norsram_init_struct->read_write_timing->bus_latency - 1U ) << PNTCFG_BUSLAT_OFFSET ) & EXMC_PNTCFG_BUSLAT )|
                           (exmc_norsram_init_struct->read_write_timing->syn_clk_division & EXMC_PNTCFG_CKDIV) |
                           (exmc_norsram_init_struct->read_write_timing->syn_data_latency & EXMC_PNTCFG_DLAT);

        /* nor flash access enable */
        if(EXMC_MEMORY_TYPE_NOR == exmc_norsram_init_struct->memory_type){
            pnctl |= (uint32_t)EXMC_PNCTL_NREN;
        }

        /* configure the registers */
        EXMC_PNCTL= pnctl;
        EXMC_PNTCFG = pntcfg;
    }
}

/*!
    \brief      enable EXMC NOR/PSRAM bank region (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_norsram_enable(void)
{
    EXMC_PNCTL |= (uint32_t)EXMC_PNCTL_NRBKEN;
}

/*!
    \brief      disable EXMC NOR/PSRAM bank region (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_norsram_disable(void)
{
    EXMC_PNCTL &= ~(uint32_t)EXMC_PNCTL_NRBKEN;
}

/*!
    \brief      deinitialize EXMC NAND bank (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_nand_deinit(void)
{
    /* EXMC_BANK1_NAND or EXMC_BANKNAND */
    EXMC_NCTL= BANK1_NCTL_RESET;
    EXMC_NCTCFG = BANK1_NCTCFG_RESET;
    EXMC_NATCFG = BANK1_NATCFG_RESET;
}

/*!
    \brief      initialize exmc_nand_parameter_struct with the default values (API_ID(0x0007U))
    \param[in]  exmc_nand_init_struct：the initialized struct exmc_nand_parameter_struct pointer
    \param[out] exmc_nand_init_struct：the initialized struct exmc_nand_parameter_struct pointer
    \retval     none
*/
void exmc_nand_struct_para_init(exmc_nand_parameter_struct* exmc_nand_init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(exmc_nand_init_struct)) {
        fw_debug_report_err(EXMC_MODULE_ID, API_ID(0x0007U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure the structure with default values */
        exmc_nand_init_struct->nand_bank = EXMC_BANK1_NAND;
        exmc_nand_init_struct->wait_feature = DISABLE;
        exmc_nand_init_struct->databus_width = EXMC_NAND_DATABUS_WIDTH_8B;
        exmc_nand_init_struct->ecc_logic = DISABLE;
        exmc_nand_init_struct->ecc_size = EXMC_ECC_SIZE_256BYTES;
        exmc_nand_init_struct->ctr_latency = 0x0U;
        exmc_nand_init_struct->atr_latency = 0x0U;
        exmc_nand_init_struct->common_space_timing->setuptime = 0xFCU;
        exmc_nand_init_struct->common_space_timing->waittime = 0xFCU;
        exmc_nand_init_struct->common_space_timing->holdtime = 0xFCU;
        exmc_nand_init_struct->common_space_timing->databus_hiztime = 0xFCU;
        exmc_nand_init_struct->attribute_space_timing->setuptime = 0xFCU;
        exmc_nand_init_struct->attribute_space_timing->waittime = 0xFCU;
        exmc_nand_init_struct->attribute_space_timing->holdtime = 0xFCU;
        exmc_nand_init_struct->attribute_space_timing->databus_hiztime = 0xFCU;
    }
}

/*!
    \brief      initialize EXMC NAND bank (API_ID(0x0008U))
    \param[in]  exmc_nand_init_struct: configure the EXMC NAND parameter
                  ecc_size: EXMC_ECC_SIZE_xBYTES,x=256,512,1024,2048,4096
                  atr_latency: EXMC_ALE_RE_DELAY_x_HCLK,x=1..16
                  ctr_latency: EXMC_CLE_RE_DELAY_x_HCLK,x=1..16
                  ecc_logic: ENABLE or DISABLE
                  databus_width: EXMC_NAND_DATABUS_WIDTH_8B,EXMC_NAND_DATABUS_WIDTH_16B
                  wait_feature: ENABLE or DISABLE
                  common_space_timing: struct exmc_nand_timing_parameter_struct set the time
                  attribute_space_timing: struct exmc_nand_timing_parameter_struct set the time
    \param[out] none
    \retval     none
*/
void exmc_nand_init(exmc_nand_parameter_struct* exmc_nand_init_struct)
{
    uint32_t nctl = 0x00000000U, nctcfg = 0x00000000U, natcfg = 0x00000000U;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(exmc_nand_init_struct)) {
        fw_debug_report_err(EXMC_MODULE_ID, API_ID(0x0008U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        nctl = (uint32_t)((exmc_nand_init_struct->wait_feature << NCTL_NDWTEN_OFFSET) & EXMC_NCTL_NDWTEN)|
                         EXMC_NCTL_NDTP |
                         (exmc_nand_init_struct->databus_width & EXMC_NCTL_NDW) |
                         ((exmc_nand_init_struct->ecc_logic << NCTL_ECCEN_OFFSET) & EXMC_NCTL_ECCEN)|
                         (exmc_nand_init_struct->ecc_size & EXMC_NCTL_ECCSZ) |
                         (exmc_nand_init_struct->ctr_latency & EXMC_NCTL_CTR) |
                         (exmc_nand_init_struct->atr_latency & EXMC_NCTL_ATR);

        nctcfg = (uint32_t)((exmc_nand_init_struct->common_space_timing->setuptime - 1U) & EXMC_NCTCFG_COMSET ) |
                            (((exmc_nand_init_struct->common_space_timing->waittime - 1U) << NCTCFG_COMWAIT_OFFSET) & EXMC_NCTCFG_COMWAIT ) |
                            ((exmc_nand_init_struct->common_space_timing->holdtime << NCTCFG_COMHLD_OFFSET) & EXMC_NCTCFG_COMHLD ) |
                            (((exmc_nand_init_struct->common_space_timing->databus_hiztime - 1U) << NCTCFG_COMHIZ_OFFSET) & EXMC_NCTCFG_COMHIZ );

        natcfg = (uint32_t)((exmc_nand_init_struct->attribute_space_timing->setuptime - 1U) & EXMC_NATCFG_ATTSET ) |
                            (((exmc_nand_init_struct->attribute_space_timing->waittime - 1U) << NATCFG_ATTWAIT_OFFSET) & EXMC_NATCFG_ATTWAIT ) |
                            ((exmc_nand_init_struct->attribute_space_timing->holdtime << NATCFG_ATTHLD_OFFSET) & EXMC_NATCFG_ATTHLD ) |
                            (((exmc_nand_init_struct->attribute_space_timing->databus_hiztime -1U) << NATCFG_ATTHIZ_OFFSET) & EXMC_NATCFG_ATTHIZ );

        /* EXMC_BANK1_NAND or EXMC_BANKNAND initialize */
        EXMC_NCTL = nctl;
        EXMC_NCTCFG = nctcfg;
        EXMC_NATCFG = natcfg;
    }
}

/*!
    \brief      enable NAND bank (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_nand_enable(void)
{
    EXMC_NCTL |= EXMC_NCTL_NDBKEN;
}

/*!
    \brief      disable NAND bank (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_nand_disable(void)
{
    EXMC_NCTL &= ~EXMC_NCTL_NDBKEN;
}


/*!
    \brief      configure CRAM page size (API_ID(0x000BU))
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
void exmc_norsram_page_size_config(uint32_t page_size)
{
    /* reset the bits */
    EXMC_PNCTL &= ~EXMC_PNCTL_CPS;

    /* set the CPS bits */
    EXMC_PNCTL |= (page_size & EXMC_PNCTL_CPS);
}

/*!
    \brief      enable the EXMC NAND ECC function (API_ID(0x000CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_nand_ecc_enable(void)
{
    /* enable the selected NAND bank ECC function */
    EXMC_NCTL |= EXMC_NCTL_ECCEN;
}

/*!
    \brief      disable the EXMC NAND ECC function (API_ID(0x000DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void exmc_nand_ecc_disable(void)
{
    /* disable the selected NAND bank ECC function */
    EXMC_NCTL &= ~EXMC_NCTL_ECCEN;
}

/*!
    \brief      get the EXMC ECC value (API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     the error correction code(ECC) value
*/
uint32_t exmc_ecc_get(void)
{
    return (EXMC_NECC);
}

/*!
    \brief      get EXMC flag status (API_ID(0x000FU))
    \param[in]  flag: EXMC status and flag
                only one parameter can be selected which are shown as below:
      \arg        EXMC_NAND_FLAG_FIFOE: FIFO empty flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus exmc_flag_get(uint32_t flag)
{
    FlagStatus status;
    uint32_t reg;

    reg = EXMC_NSTAT;
    
    if ((reg & flag) != (uint32_t)flag ){
        /* flag is reset */
        status = RESET;
    }else{
        /* flag is set */
        status = SET;
    }
    return status;
}

