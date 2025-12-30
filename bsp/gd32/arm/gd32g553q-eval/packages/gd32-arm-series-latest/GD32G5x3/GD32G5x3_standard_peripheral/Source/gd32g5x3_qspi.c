/*!
    \file    gd32g5x3_qspi.c
    \brief   QSPI driver

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

#include "gd32g5x3_qspi.h"

/* QSPI register bit offset */
#define CTL_FTL_OFFSET                ((uint32_t)0x00000008U)               /*!< bit offset of FTL in QSPI_CTL */
#define CTL_PSC_OFFSET                ((uint32_t)0x00000018U)               /*!< bit offset of PSC in QSPI_CTL */
#define DCFG_FMSZ_OFFSET              ((uint32_t)0x00000010U)               /*!< bit offset of FMSZ in QSPI_DCFG */
#define TCFG_DUMYC_OFFSET             ((uint32_t)0x00000012U)               /*!< bit offset of DUMYC in QSPI_TCFG */
#define CTL_OUTPUT_CK_DELAY_OFFSET    ((uint32_t)0x0000000CU)               /*!< bit offset of OCKDV in QSPI_CTL */

/* QSPI command config timeout */
#define QSPI_COMMAND_CONFIG_TOMEOUT    ((uint16_t)0xFFFFU)                  /*!< command config timeout */

/* QSPI data transmit timeout */
#define QSPI_DATA_TRANSMIT_TOMEOUT     ((uint16_t)0xFFFFU)                  /*!< data transmi timeout */

/* QSPI data receive timeout */
#define QSPI_DATA_RECEIVE_TOMEOUT      ((uint16_t)0xFFFFU)                  /*!< data receive timeout */

/* configure QSPI functional mode */
static void qspi_config(qspi_command_struct *cmd, uint32_t functionalmode);

/*!
    \brief      reset QSPI
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_deinit(void)
{
    rcu_periph_reset_enable(RCU_QSPIRST);
    rcu_periph_reset_disable(RCU_QSPIRST);
}

/*!
    \brief      initialize the parameters of QSPI structure with the default values
    \param[in]  none
    \param[out] init_para: QSPI parameter structure
    \retval     none
*/
void qspi_struct_para_init(qspi_init_struct *init_para)
{
    /* set the QSPI structure with the default values */
    init_para->clock_mode     = QSPI_CLOCK_MODE_LOW;
    init_para->prescaler      = 3U;
    init_para->fifo_threshold = 16U;
    init_para->sample_shift1  = QSPI_SAMPLE_SHIFTING_NONE;
    init_para->sample_shift2  = QSPI_SHIFTING_NONE;
    init_para->flash_size     = 0x1FU;
    init_para->cs_high_time   = QSPI_CS_HIGH_TIME_1_CYCLE;
}

/*!
    \brief      initialize the parameters of QSPI command structure with the default values
    \param[in]  none
    \param[out] init_para: QSPI command parameter structure
    \retval     none
*/
void qspi_cmd_struct_para_init(qspi_command_struct *init_para)
{
    /* set the QSPI command structure with the default values */
    init_para->instruction_mode = QSPI_INSTRUCTION_NONE;
    init_para->instruction      = 0U;
    init_para->addr_mode        = QSPI_ADDR_NONE;
    init_para->addr_size        = QSPI_ADDR_8_BITS;
    init_para->addr             = 0U;
    init_para->altebytes_mode   = QSPI_ALTE_BYTES_NONE;
    init_para->altebytes_size   = QSPI_ALTE_BYTES_8_BITS;
    init_para->altebytes        = 0U;
    init_para->dummycycles      = 0U;
    init_para->data_mode        = QSPI_DATA_NONE;
    init_para->data_length      = 0U;
    init_para->sioo_mode        = QSPI_SIOO_INST_EVERY_CMD;
    init_para->trans_rate       = 0U;
    init_para->trans_delay      = 0U;
}

/*!
    \brief      initialize the parameters of QSPI read polling structure with the default values
    \param[in]  none
    \param[out] init_para: QSPI read polling parameter structure
    \retval     none
*/
void qspi_polling_struct_para_init(qspi_polling_struct *init_para)
{
    /* set the QSPI read polling structure with the default values */
    init_para->match            = 0U;
    init_para->mask             = 0U;
    init_para->interval         = 0U;
    init_para->statusbytes_size = 1U;
    init_para->match_mode       = QSPI_MATCH_MODE_AND;
    init_para->polling_stop     = QSPI_POLLING_STOP_DISABLE;
}

/*!
    \brief      initialize QSPI
    \param[in]  qspi_struct: QSPI parameter initialization structure
                            and the member values are shown as below:
                  prescaler: between 0 and 255
                  fifo_threshold: between 1 and 16
                  sample_shift1: QSPI_SAMPLE_SHIFTING_NONE, QSPI_SAMPLE_SHIFTING_HALFCYCLE
                  sample_shift2: QSPI_SHIFTING_NONE, QSPI_SHIFTING_1_CYCLE, QSPI_SHIFTING_2_CYCLE, QSPI_SHIFTING_3_CYCLE,
                                 QSPI_SHIFTING_4_CYCLE, QSPI_SHIFTING_5_CYCLE, QSPI_SHIFTING_6_CYCLE, QSPI_SHIFTING_7_CYCLE
                  flash_size: between 0 and 31
                  cs_high_time: QSPI_CS_HIGH_TIME_1_CYCLE, QSPI_CS_HIGH_TIME_2_CYCLE, QSPI_CS_HIGH_TIME_3_CYCLE,
                                QSPI_CS_HIGH_TIME_4_CYCLE, QSPI_CS_HIGH_TIME_5_CYCLE, QSPI_CS_HIGH_TIME_6_CYCLE,
                                QSPI_CS_HIGH_TIME_7_CYCLE, QSPI_CS_HIGH_TIME_8_CYCLE
                  clock_mode: QSPI_CLOCK_MODE_LOW, QSPI_CLOCK_MODE_HIGH
    \param[out] none
    \retval     none
*/
void qspi_init(qspi_init_struct *qspi_struct)
{
    /* configure prescaler, sample_shift, fifo_threshold */
    QSPI_CTL &= ~(QSPI_CTL_PSC | QSPI_CTL_SSAMPLE | QSPI_CTL_FTL);
    QSPI_CTL |= (qspi_struct->prescaler << CTL_PSC_OFFSET) | qspi_struct->sample_shift1 | ((
                    qspi_struct->fifo_threshold - 1U) << CTL_FTL_OFFSET);

    /* configure flash_size, cs_high_time, clock_mode */
    QSPI_DCFG &= ~((QSPI_DCFG_FMSZ) | QSPI_DCFG_CSHC | QSPI_DCFG_CKMOD | QSPI_DCFG_RXSFT);
    QSPI_DCFG |= ((qspi_struct->flash_size << DCFG_FMSZ_OFFSET) | qspi_struct->cs_high_time | qspi_struct->clock_mode |
                  qspi_struct->sample_shift2);
}

/*!
    \brief      enable QSPI
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_enable(void)
{
    QSPI_CTL |= (uint32_t)QSPI_CTL_QSPIEN;
}

/*!
    \brief      disable QSPI
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_disable(void)
{
    QSPI_CTL &= (uint32_t)(~QSPI_CTL_QSPIEN);
}

/*!
    \brief      enable QSPI DMA
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_dma_enable(void)
{
    QSPI_CTL |= (uint32_t)(QSPI_CTL_DMAEN);
}

/*!
    \brief      disable QSPI DMA
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_dma_disable(void)
{
    QSPI_CTL &= (uint32_t)(~QSPI_CTL_DMAEN);
}

/*!
    \brief      configure QSPI command parameters
    \param[in]  cmd: QSPI command parameter structure
                             and the member values are shown as below:
                  instruction_mode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                    QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  instruction: reference flash commands description
                  addr_mode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  addr_size: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  addr: 0-flash size
                  altebytes_mode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                  QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  altebytes_size: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                  QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  altebytes: 0-0xFFFFFFFF
                  dummycycles: between 0 and 31
                  data_mode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  data_length: 0-0xFFFFFFFF
                  sioo_mode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
                  trans_rate: QSPI_SDR_MODE, QSPI_DDR_MODE
                  trans_delay: QSPI_DDR_HOLD_DISABLE, QSPI_DDR_HOLD_ENABLE
    \param[out] none
    \retval     none
*/
void qspi_command_config(qspi_command_struct *cmd)
{
    uint16_t timeout = QSPI_COMMAND_CONFIG_TOMEOUT;
    
    /* call the configuration function */
    qspi_config(cmd, QSPI_NORMAL_WRITE);

    if(cmd->data_mode == QSPI_DATA_NONE) {
        /* when there is no data phase, the transfer start as soon as the configuration is done
        so wait until TC flag is set to go back in idle state */
        while(((QSPI_STAT & QSPI_FLAG_TC ) == 0U) && (timeout > 0U)){
            timeout--;
        }
        QSPI_STATC = QSPI_STATC_TCC;
    }
}

/*!
    \brief      configure QSPI read polling mode
    \param[in]  cmd: QSPI command parameter structure
                             and the member values are shown as below:
                  instruction_mode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                    QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  instruction: reference flash commands description
                  addr_mode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  addr_size: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  addr: 0-flash size
                  altebytes_mode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                  QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  altebytes_size: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                  QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  altebytes: 0-0xFFFFFFFF
                  dummycycles: between 0 and 31
                  data_mode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  data_length: 0-0xFFFFFFFF
                  sioo_mode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
                  trans_rate: QSPI_SDR_MODE, QSPI_DDR_MODE
                  trans_delay: QSPI_DDR_HOLD_DISABLE, QSPI_DDR_HOLD_ENABLE
    \param[in]  cfg: QSPI read polling parameter structure
                             and the member values are shown as below:
                  match: between 0 and 0xFFFFFFFF
                  mask: between 0 and 0xFFFFFFFF
                  interval: between 0 and 0xFFFF
                  statusbytes_size: between 1 and 4
                  match_mode: QSPI_MATCH_MODE_AND, QSPI_MATCH_MODE_OR
                  polling_stop: QSPI_POLLING_STOP_DISABLE,QSPI_POLLING_STOP_ENABLE
    \param[out] none
    \retval     none
*/
void qspi_polling_config(qspi_command_struct *cmd, qspi_polling_struct *cfg)
{
    /* configure the match value */
    QSPI_STATMATCH = cfg->match;
    /* configure the mask value */
    QSPI_STATMK = cfg->mask;
    /* configure the interval cycle */
    QSPI_INTERVAL = cfg->interval;
    /* configure the read polling match mode and read polling mode stop */
    QSPI_CTL &= ~(QSPI_CTL_RPMS | QSPI_CTL_RPMM);
    QSPI_CTL |= (cfg->match_mode | cfg->polling_stop);

    cmd->data_length = cfg->statusbytes_size;
    qspi_config(cmd, QSPI_READ_POLLING);
}

/*!
    \brief      configure QSPI memory mapped mode
    \param[in]  cmd: QSPI command parameter structure
                             and the member values are shown as below:
                  instruction_mode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                    QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  instruction: reference flash commands description
                  addr_mode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  addr_size: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  addr: 0-flash size
                  altebytes_mode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                  QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  altebytes_size: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                  QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  altebytes: 0-0xFFFFFFFF
                  dummycycles: between 0 and 31
                  data_mode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  data_length: 0-0xFFFFFFFF
                  sioo_mode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
                  trans_rate: QSPI_SDR_MODE, QSPI_DDR_MODE
                  trans_delay: QSPI_DDR_HOLD_DISABLE, QSPI_DDR_HOLD_ENABLE
    \param[in]  timeout: 0-0xFFFF
    \param[in]  toen:
      \arg        QSPI_TMOUT_DISABLE: disable timeout counter
      \arg        QSPI_TMOUT_ENABLE: enable timeout counter
    \param[out] none
    \retval     none
*/
void qspi_memorymapped_config(qspi_command_struct *cmd, uint16_t timeout, uint32_t toen)
{
    /* enable timeout */
    QSPI_CTL &= ~QSPI_CTL_TMOUTEN;
    QSPI_CTL |= toen;

    if(toen == QSPI_CTL_TMOUTEN) {
        /* configure the timeout value */
        QSPI_TMOUT = timeout;
        QSPI_STATC = QSPI_STATC_TMOUTC;
        /* enable the QSPI timeout interrupt */
        QSPI_CTL |= QSPI_CTL_TMOUTIE;
    }
    qspi_config(cmd, QSPI_MEMORY_MAPPED);
}

/*!
    \brief      QSPI transmit data function
    \param[in]  tdata: pointer to the data to be transmitted
    \param[out] none
    \retval     none
*/
void qspi_data_transmit(uint8_t tdata[])
{
    uint32_t tx_cnt;
    uint32_t index = 0U;
    uint16_t timeout = QSPI_DATA_TRANSMIT_TOMEOUT;
    
    tx_cnt = QSPI_DTLEN + 1U;

    QSPI_TCFG = (QSPI_TCFG & ~QSPI_TCFG_FMOD) | QSPI_NORMAL_WRITE;

    while(tx_cnt > 0U) {
        while(((QSPI_STAT & QSPI_FLAG_FT ) == 0U) && (timeout > 0U)){
            timeout--;
        }
        /* transmit data */
        *(uint8_t *)(QSPI + 0x00000020U) = tdata[index++];
        tx_cnt--;
    }
}

/*!
    \brief      QSPI receive data function
    \param[in]  none
    \param[out] rdata: pointer to the data to be received
    \retval     none
*/
void qspi_data_receive(uint8_t rdata[])
{
    uint32_t rx_cnt, addr;
    uint32_t index = 0U;
    uint16_t timeout = QSPI_DATA_RECEIVE_TOMEOUT;
    
    rx_cnt = QSPI_DTLEN + 1U;
    addr = QSPI_ADDR;

    QSPI_TCFG = (QSPI_TCFG & ~QSPI_TCFG_FMOD) | QSPI_NORMAL_READ;
    /* start the transfer by re-writing the address in QSPI_ADDR register */
    QSPI_ADDR = addr;

    while(rx_cnt > 0U) {
        while(((QSPI_STAT & (QSPI_FLAG_FT | QSPI_FLAG_TC)) == 0U) && (timeout > 0U)){
            timeout--;
        }
        rdata[index++] = *(uint8_t *)(QSPI + 0x00000020U);
        rx_cnt--;
    }
}

/*!
    \brief      abort the current transmission
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_transmission_abort(void)
{
    QSPI_CTL |= (uint32_t)(QSPI_CTL_ABORT);
}

/*!
    \brief      enable QSPI output clock delay
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_output_clock_delay_enable(void)
{
    QSPI_CTL |= (uint32_t)QSPI_CTL_OCKDEN;
}

/*!
    \brief      disable QSPI output clock delay
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_output_clock_delay_disable(void)
{
    QSPI_CTL &= (uint32_t)(~QSPI_CTL_OCKDEN);
}

/*!
    \brief      configure output clock delay
    \param[in]  ck_delay: 0~15
    \param[out] none
    \retval     none
*/
void qspi_output_clock_delay_config(uint32_t ck_delay)
{
    QSPI_CTL &= (uint32_t)(~QSPI_CTL_OCKDV);
    QSPI_CTL |= (uint32_t)(ck_delay << CTL_OUTPUT_CK_DELAY_OFFSET);
}

/*!
    \brief      configure QSPI sample shift
    \param[in]  sample_shift1: QSPI sample shift1, support use with 2
                only one parameter can be selected which are shown as below:
      \arg        QSPI_SAMPLE_SHIFTING_NONE: no shift when sample data
      \arg        QSPI_SAMPLE_SHIFTING_HALFCYCLE: 1/2 sck cycle shift
    \param[in]  sample_shift2: QSPI sample shift2, support use with 1
                only one parameter can be selected which are shown as below:
      \arg        QSPI_SHIFTING_NONE: no shift when sample data
      \arg        QSPI_SHIFTING_1_CYCLE: 1 sck cycle shift
      \arg        QSPI_SHIFTING_2_CYCLE: 2 sck cycle shift
      \arg        QSPI_SHIFTING_3_CYCLE: 3 sck cycle shift
      \arg        QSPI_SHIFTING_4_CYCLE: 4 sck cycle shift
      \arg        QSPI_SHIFTING_5_CYCLE: 5 sck cycle shift
      \arg        QSPI_SHIFTING_6_CYCLE: 6 sck cycle shift
      \arg        QSPI_SHIFTING_7_CYCLE: 7 sck cycle shift
    \param[out] none
    \retval     none
*/
void qspi_sample_shift_config(uint32_t sample_shift1, uint32_t sample_shift2)
{
    if(QSPI_SAMPLE_SHIFTING_NONE == sample_shift1) {
        QSPI_CTL &= (uint32_t)(~QSPI_CTL_SSAMPLE);
    } else {
        QSPI_CTL |= sample_shift1;
    }

    if(QSPI_SHIFTING_NONE == sample_shift2) {
        QSPI_DCFG &= (uint32_t)(~QSPI_DCFG_RXSFT);
    } else {
        QSPI_DCFG |= sample_shift2;
    }
}

/*!
    \brief      select receive clock
    \param[in]  rcksel: receive clock select
                only one parameter can be selected which are shown as below:
      \arg        QSPI_RECEIVE_CLOCK_SCK: select SCK as receive clock
      \arg        QSPI_RECEIVE_CLOCK_DQS: select DQS as receive clock
    \param[out] none
    \retval     none
*/
void qspi_receive_clock_sel(uint32_t rcksel)
{
    if(QSPI_RECEIVE_CLOCK_SCK == rcksel) {
        QSPI_DCFG &= (uint32_t)(~QSPI_DCFG_RCKSEL);
    } else {
        QSPI_DCFG |= rcksel;
    }
}

/*!
    \brief      enable QSPI delay scan
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_delay_scan_enable(void)
{
    QSPI_DCFG |= (uint32_t)QSPI_DCFG_DLYSCEN;
}

/*!
    \brief      disable QSPI delay scan
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_delay_scan_disable(void)
{
    QSPI_DCFG &= (uint32_t)(~QSPI_DCFG_DLYSCEN);
}

/*!
    \brief      csn falls and rises 1 or 2 sck cycles select
    \param[in]  csn_cycle: receive clock select
                only one parameter can be selected which are shown as below:
      \arg        QSPI_CSN_1_CYCLE: csn falls and rises 1 sck cycle
      \arg        QSPI_CSN_2_CYCLE: csn falls and rises 2 sck cycle
    \param[out] none
    \retval     none
*/
void qspi_csn_edge_cycle(uint32_t csn_cycle)
{
    if(QSPI_CSN_1_CYCLE == csn_cycle) {
        QSPI_DCFG &= (uint32_t)(~QSPI_DCFG_CSNCKM);
    } else {
        QSPI_DCFG |= csn_cycle;
    }
}

/*!
    \brief      get QSPI flag status
    \param[in]  flag: QSPI flag
                only one parameter can be selected which are shown as below:
      \arg        QSPI_FLAG_BUSY: busy flag
      \arg        QSPI_FLAG_TERR: transfer error flag
      \arg        QSPI_FLAG_TC: transfer complete flag
      \arg        QSPI_FLAG_FT: FIFO threshold flag
      \arg        QSPI_FLAG_RPMF: read polling match flag
      \arg        QSPI_FLAG_TMOUT: timeout flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus qspi_flag_get(uint32_t flag)
{
    if(RESET != (QSPI_STAT & flag)) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear QSPI flag status
    \param[in]  flag: QSPI flag
                one or more parameters can be selected which are shown as below:
      \arg        QSPI_FLAG_TERR: transfer error flag
      \arg        QSPI_FLAG_TC: transfer complete flag
      \arg        QSPI_FLAG_RPMF: read polling match flag
      \arg        QSPI_FLAG_TMOUT: timeout flag
    \param[out] none
    \retval     none
*/
void qspi_flag_clear(uint32_t flag)
{
    QSPI_STATC |= (uint32_t)flag;
}

/*!
    \brief      enable QSPI interrupt
    \param[in]  interrupt: QSPI interrupt
                one or more parameters can be selected which is shown as below:
      \arg        QSPI_INT_TC: transfer complete interrupt
      \arg        QSPI_INT_FT: FIFO threshold interrupt
      \arg        QSPI_INT_TERR: transfer error interrupt
      \arg        QSPI_INT_RPMF: read polling match interrupt
      \arg        QSPI_INT_TMOUT: timeout interrupt
    \param[out] none
    \retval     none
*/
void qspi_interrupt_enable(uint32_t interrupt)
{
    QSPI_CTL |= (uint32_t)interrupt;
}

/*!
    \brief      disable QSPI interrupt
    \param[in]  interrupt: QSPI interrupt
                one or more parameters can be selected which is shown as below:
      \arg        QSPI_INT_TC: transfer complete interrupt
      \arg        QSPI_INT_FT: FIFO threshold interrupt
      \arg        QSPI_INT_TERR: transfer error interrupt
      \arg        QSPI_INT_RPMF: read polling match interrupt
      \arg        QSPI_INT_TMOUT: timeout interrupt
    \param[out] none
    \retval     none
*/
void qspi_interrupt_disable(uint32_t interrupt)
{
    QSPI_CTL &= ~(uint32_t)interrupt;
}

/*!
    \brief      get QSPI interrupt flag status
    \param[in]  int_flag: QSPI interrupt flag
                only one parameter can be selected which are shown as below:
      \arg        QSPI_INT_FLAG_TERR: transfer error interrupt flag
      \arg        QSPI_INT_FLAG_TC: transfer complete interrupt flag
      \arg        QSPI_INT_FLAG_FT: FIFO threshold interrupt flag
      \arg        QSPI_INT_FLAG_RPMF: read polling match interrupt flag
      \arg        QSPI_INT_FLAG_TMOUT: timeout interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus qspi_interrupt_flag_get(uint32_t int_flag)
{
    uint32_t reg1 = QSPI_CTL;
    uint32_t reg2 = QSPI_STAT;

    switch(int_flag) {
    /* QSPI transfer error interrupt flag */
    case QSPI_INT_FLAG_TERR:
        reg1 = reg1 & QSPI_STAT_TERR;
        reg2 = reg2 & QSPI_CTL_TERRIE;
        break;
    /* QSPI transfer complete interrupt flag */
    case QSPI_INT_FLAG_TC:
        reg1 = reg1 & QSPI_STAT_TC;
        reg2 = reg2 & QSPI_CTL_TCIE;
        break;
    /* QSPI FIFO threshold interrupt flag */
    case QSPI_INT_FLAG_FT:
        reg1 = reg1 & QSPI_STAT_FT;
        reg2 = reg2 & QSPI_CTL_FTIE;
        break;
    /* QSPI status match interrupt flag */
    case QSPI_INT_FLAG_RPMF:
        reg1 = reg1 & QSPI_STAT_RPMF;
        reg2 = reg2 & QSPI_CTL_RPMFIE;
        break;
    /* QSPI timeout interrupt flag */
    case QSPI_INT_FLAG_TMOUT:
        reg1 = reg1 & QSPI_STAT_TMOUT;
        reg2 = reg2 & QSPI_CTL_TMOUTIE;
        break;
    default :
        break;
    }
    /* get QSPI interrupt flag status */
    if(reg1 && reg2) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear QSPI interrupt flag status
    \param[in]  int_flag: QSPI interrupt flag
                one or more parameters can be selected which are shown as below:
      \arg        QSPI_INT_FLAG_TERR: transfer error interrupt flag
      \arg        QSPI_INT_FLAG_TC: transfer complete interrupt flag
      \arg        QSPI_INT_FLAG_RPMF: read polling match interrupt flag
      \arg        QSPI_INT_FLAG_TMOUT: timeout interrupt flag
    \param[out] none
    \retval     none
*/
void qspi_interrupt_flag_clear(uint32_t int_flag)
{
    QSPI_STATC |= (uint32_t)int_flag;
}

/*!
    \brief      configure QSPI functional mode
    \param[in]  cmd: QSPI command parameter structure
                             and the member values are shown as below:
                  instruction_mode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                    QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  instruction: reference flash commands description
                  addr_mode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  addr_size: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  addr: 0-flash size
                  altebytes_mode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                  QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  altebytes_size: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                  QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  altebytes: 0-0xFFFFFFFF
                  dummycycles: between 0 and 31
                  data_mode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  data_length: 0-0xFFFFFFFF
                  sioo_mode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
                  trans_rate: QSPI_SDR_MODE, QSPI_DDR_MODE
                  trans_delay: QSPI_DDR_HOLD_DISABLE, QSPI_DDR_HOLD_ENABLE
    \param[in]  functionalmode: QSPI functional mode select
                only one parameter can be selected which is shown as below:
      \arg        QSPI_NORMAL_WRITE
      \arg        QSPI_NORMAL_READ
      \arg        QSPI_READ_POLLING
      \arg        QSPI_MEMORY_MAPPED
    \param[out] none
    \retval     none
*/
static void qspi_config(qspi_command_struct *cmd, uint32_t functionalmode)
{
    if((cmd->data_mode != QSPI_DATA_NONE) && (functionalmode != QSPI_MEMORY_MAPPED)) {
        /* configure QSPI_DTLEN register with the number of data to read or write */
        QSPI_DTLEN = cmd->data_length - 1U;
    }

    if(cmd->altebytes_mode != QSPI_ALTE_BYTES_NONE) {
        /* configure QSPI_ALTE register with alternate bytes value */
        QSPI_ALTE = cmd->altebytes;
    }

    if((cmd->data_mode != QSPI_DATA_NONE) || (cmd->altebytes_mode != QSPI_ALTE_BYTES_NONE) || \
            (cmd->addr_mode != QSPI_ADDR_NONE) || (cmd->instruction_mode != QSPI_INSTRUCTION_NONE)) {
        QSPI_TCFG = cmd->data_mode | (cmd->dummycycles << TCFG_DUMYC_OFFSET) | cmd->sioo_mode |
                    cmd->altebytes_size | cmd->altebytes_mode |
                    cmd->addr_size | cmd->addr_mode | cmd->instruction_mode |
                    cmd->instruction | cmd->trans_rate | cmd->trans_delay | functionalmode;
    }

    if((cmd->addr_mode != QSPI_ADDR_NONE) && (functionalmode != QSPI_MEMORY_MAPPED)) {
        /* configure QSPI_ADDR register with address value */
        QSPI_ADDR = cmd->addr;
    }
}
