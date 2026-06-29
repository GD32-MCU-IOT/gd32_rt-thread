/*!
    \file    gd32w51x_f5hc_qspi.c
    \brief   QSPI driver

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

#include "gd32w51x_f5hc_qspi.h"

/* QSPI timeout */
#define QSPI_TOMEOUT    ((uint16_t)0xFFFFU)                  /*!< command config timeout */

/* configure QSPI functionalmode */
static void qspi_config(qspi_command_struct *cmd, uint32_t functionalmode);

/*!
    \brief      reset QSPI (API_ID(0x0001U))
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
    \brief      initialize the parameters of QSPI struct with the default values (API_ID(0x0002U))
    \param[in]  qspi_struct: QSPI parameter stuct
    \param[out] none
    \retval     none
*/
void qspi_init_struct_para_init(qspi_init_struct *qspi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(qspi_struct)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the QSPI struct with the default values */
        qspi_struct->clock_mode = QSPI_CLOCK_SCK_LOW;
        qspi_struct->prescaler = 0x03U;
        qspi_struct->fifo_threshold = 0x10U;
        qspi_struct->sample_shift = QSPI_SAMPLE_SHIFTING_NONE;
        qspi_struct->flash_size = 0x1FU;
        qspi_struct->cs_high_time = QSPI_CS_HIGH_TIME_1_CYCLE;
    }
}

/*!
    \brief      initialize QSPI parameter (API_ID(0x0003U))
    \param[in]  qspi_struct: QSPI parameter initialization stuct members of the structure
                            and the member values are shown as below:
                  clockmode: QSPI_CLOCK_MODE_0, QSPI_CLOCK_MODE_3
                  fifothreshold: between 1 and 16
                  sampleshift: QSPI_SAMPLE_SHIFTING_NONE, QSPI_SAMPLE_SHIFTING_HALFCYCLE, QSPI_SAMPLE_SHIFTING_ONECYCLE
                  flashsize: between 0 and 28
                  chipselecthightime: QSPI_CS_HIGH_TIME_1_CYCLE, QSPI_CS_HIGH_TIME_2_CYCLE, QSPI_CS_HIGH_TIME_3_CYCLE,
                                      QSPI_CS_HIGH_TIME_4_CYCLE, QSPI_CS_HIGH_TIME_5_CYCLE, QSPI_CS_HIGH_TIME_6_CYCLE,
                                      QSPI_CS_HIGH_TIME_7_CYCLE, QSPI_CS_HIGH_TIME_8_CYCLE
                  prescale: between 0 and 255
    \param[out] none
    \retval     none
    \note       This function may contain scenarios leading to an infinite loop.
                Modify it according to the actual usage requirements.
*/
void qspi_init(qspi_init_struct *qspi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(qspi_struct)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg = 0U;
        uint16_t qtimeout = QSPI_TOMEOUT;

        reg = QSPI_CTL;
        reg &= ~(QSPI_CTL);
        reg |= ((qspi_struct->fifo_threshold - 1U) << 8);
        QSPI_CTL = reg;
        /* wait till BUSY flag reset */
        while(((QSPI_CTL & QSPI_CTL_BUSY) != 0U) && (--qtimeout > 0U)) {
        }

        /* configure prescaler, sampleshift */
        reg = QSPI_CTL;
        reg &= ~((QSPI_CTL_PSC) | QSPI_SAMPLE_SHIFTING_HALFCYCLE);
        reg |= (qspi_struct->prescaler << 24) | qspi_struct->sample_shift;
        QSPI_CTL = reg;

        /* configure flashsize, chipselecthightime, clockmode */
        reg = QSPI_DCFG;
        reg &= ~((QSPI_DCFG_FMSZ) | QSPI_CS_HIGH_TIME_8_CYCLE | QSPI_DCFG_CKMOD);
        reg |= ((qspi_struct->flash_size << 16) | qspi_struct->cs_high_time | qspi_struct->clock_mode);
        QSPI_DCFG = reg;

        QSPI_CTL  |= QSPI_CTL_QSPIEN;
        QSPI_STAT |= QSPI_STAT_TERRIE;
    }
}
/*!
    \brief      enable QSPI (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_enable(void)
{
    QSPI_CTL |= (uint32_t)QSPI_CTL_QSPIEN;
}

/*!
    \brief      disable QSPI (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_disable(void)
{
    QSPI_CTL &= ~(uint32_t)QSPI_CTL_QSPIEN;
}

/*!
    \brief      enable QSPI DMA (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_dma_enable(void)
{
    QSPI_STAT |= (uint32_t)(QSPI_STAT_DMAEN);
}

/*!
    \brief      disable QSPI DMA (API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_dma_disable(void)
{
    QSPI_STAT &= ~(uint32_t)QSPI_STAT_DMAEN;
}

/*!
    \brief      configure QSPI data length
    \param[in]  dtlen: 1 ~ 4294967295 (4G-1)
                Please note that when using this function, the parameter passed in is the actual number of data bytes to be transmitted.
    \param[out] none
    \retval     none
*/
void qspi_data_length_config(uint32_t dtlen)
{
    if(dtlen >= 1U){
        QSPI_DTLEN = (dtlen - 1U);
    } else {
        /* do nothing */
    }
}

/*!
    \brief      QSPI command parameter (API_ID(0x0009U))
    \param[in]  cmd: QSPI command parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  instruction: reference flash commands description
                  address: 0-flash size
                  alternatebytes: 0-0xFFFFFFFF
                  addresssize: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  alternatebytessize: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                      QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  dummycycles: between 0 and 31
                  instructionmode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                   QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  addressmode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  alternatebytemode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                     QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  datamode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  nbdata: 0-0xFFFFFFFF
                  sioomode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
    \param[out] none
    \retval     none
    \note       This function may contain scenarios leading to an infinite loop.
                Modify it according to the actual usage requirements.
*/
void qspi_command(qspi_command_struct *cmd)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(cmd)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0009U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint16_t qtimeout = QSPI_TOMEOUT;

        while(((QSPI_CTL & QSPI_FLAG_BUSY) != 0U) && (--qtimeout > 0U)) {
        }

        /* call the configuration function */
        qspi_config(cmd, QSPI_INDIRECT_WRITE);

        if(cmd->data_mode == QSPI_DATA_NONE) {
            /* when there is no data phase, the transfer start as soon as the configuration is done
            so wait until TC flag is set to go back in idle state */
            while(((QSPI_STAT & QSPI_FLAG_TC) == 0U) && (--qtimeout > 0U)) {
            }
            QSPI_STATC = QSPI_STATC_TCC;
        }
    }
}

/*!
    \brief      QSPI transmit data (API_ID(0x000AU))
    \param[in]  tdata: 8-bit data
    \param[out] none
    \retval     none
    \note       This function may contain scenarios leading to an infinite loop.
                Modify it according to the actual usage requirements.
*/
void qspi_transmit(uint8_t tdata[])
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(tdata)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t TxCounter;
        uint32_t data_index = 0U;
        uint16_t qtimeout = QSPI_TOMEOUT;

        TxCounter = QSPI_DTLEN + 1U;

        QSPI_TCFG = (QSPI_TCFG & ~QSPI_MEMORY_MAPPED) | QSPI_INDIRECT_WRITE;

        while(TxCounter > 0U) {
            while(((QSPI_STAT & QSPI_FLAG_FT) == 0U) && (--qtimeout > 0U)) {
            }
            *(uint8_t *)(QSPI + 0x00000020U) = tdata[data_index];
            data_index++;
            TxCounter--;
        }
        while(((QSPI_STAT & QSPI_FLAG_TC) == 0U) && (--qtimeout > 0U)) {
        }
        QSPI_STATC = QSPI_STATC_TCC;
    }
}

/*!
    \brief      QSPI receive data (API_ID(0x000BU))
    \param[in]  rdata: empty array
    \param[out] 8-bit data array
    \retval     none
    \note       This function may contain scenarios leading to an infinite loop.
                Modify it according to the actual usage requirements.
*/
void qspi_receive(uint8_t rdata[])
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(rdata)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t RxCounter, addr;
        uint32_t data_index = 0U;
        uint16_t qtimeout = QSPI_TOMEOUT;

        RxCounter = QSPI_DTLEN + 1U;
        addr = QSPI_ADDR;

        QSPI_TCFG = (QSPI_TCFG & ~QSPI_MEMORY_MAPPED) | QSPI_INDIRECT_READ;
        /* start the transfer by re-writing the address in ADDR register */
        QSPI_ADDR = addr;

        while(RxCounter > 0U) {
            while(((QSPI_STAT & (QSPI_FLAG_FT | QSPI_FLAG_TC)) == 0U) && (--qtimeout > 0U)) {
            }
            rdata[data_index] = *(uint8_t *)(QSPI + 0x00000020U);
            data_index++;
            RxCounter--;
        }
        while(((QSPI_STAT & QSPI_FLAG_TC) == 0U) && (--qtimeout > 0U)) {
        }
        QSPI_STATC = QSPI_STATC_TCC;
    }
}

/*!
    \brief      configure QSPI autopolling mode (API_ID(0x000CU))
    \param[in]  cmd: QSPI command parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  instruction: reference flash commands description
                  address: 0-flash size
                  alternatebytes: 0-0xFFFFFFFF
                  addresssize: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  alternatebytessize: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                      QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  dummycycles: between 0 and 31
                  instructionmode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                   QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  addressmode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  alternatebytemode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                     QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  datamode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  nbdata: 0-0xFFFFFFFF
                  sioomode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
    \param[in]  cfg: autopolling struct initialization stuct members of the structure
                             and the member values are shown as below:
                  match: between 0 and 0xFFFFFFFF
                  mask: between 0 and 0xFFFFFFFF
                  interval: between 0 and 0xFFFF
                  statusbytes_size: between 1 and 4
                  match_mode: QSPI_MATCH_MODE_AND, QSPI_MATCH_MODE_OR
                  auto_stop: QSPI_AUTO_STOP_DISABLE, QSPI_AUTO_STOP_ENABLE
    \param[out] none
    \retval     none
    \note       This function may contain scenarios leading to an infinite loop.
                Modify it according to the actual usage requirements.
*/
void qspi_autopolling(qspi_command_struct *cmd, qspi_autopolling_struct *cfg)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(cmd)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_POINTER);
    } else if(NOT_VALID_POINTER(cfg)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint16_t qtimeout = QSPI_TOMEOUT;

        /* wait till BUSY flag reset */
        while(((QSPI_CTL & QSPI_FLAG_BUSY) != 0U) && (--qtimeout > 0U)) {
        }
        QSPI_STATMATCH = cfg->match;
        QSPI_STATMK = cfg->mask;
        QSPI_INTERVAL = cfg->interval;
        QSPI_CTL = (QSPI_CTL & (~(QSPI_CTL_SPS | QSPI_CTL_SPMOD))) | (cfg->match_mode | cfg->auto_stop);
        cmd->data_length = cfg->statusbytes_size;
        qspi_config(cmd, QSPI_AUTO_POLLING);

        while(((QSPI_STAT & QSPI_FLAG_SM) == 0U) && (--qtimeout > 0U)) {
        }
        QSPI_STATC = QSPI_STATC_SMC;
    }
}

/*!
    \brief      configure QSPI memorymapped mode (API_ID(0x000DU))
    \param[in]  cmd: QSPI command parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  instruction: reference flash commands description
                  address: 0-flash size
                  alternatebytes: 0-0xFFFFFFFF
                  addresssize: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  alternatebytessize: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                      QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  dummycycles: between 0 and 31
                  instructionmode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                   QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  addressmode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  alternatebytemode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                     QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  datamode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  nbdata: 0-0xFFFFFFFF
                  sioomode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
    \param[in]  timeout: 0-0xFFFF
    \param[in]  toen: QSPI_TOEN_DISABLE, QSPI_TOEN_ENABLE
    \param[out] none
    \retval     none
    \note       This function may contain scenarios leading to an infinite loop.
                Modify it according to the actual usage requirements.
*/
void qspi_memorymapped(qspi_command_struct *cmd, uint16_t timeout, uint32_t toen)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(cmd)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000DU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint16_t qtimeout = QSPI_TOMEOUT;

        while(((QSPI_CTL & QSPI_FLAG_BUSY) != 0U) && (--qtimeout > 0U)) {
        }

        /* configure QSPI: CTL register with timeout counter enable */
        QSPI_CTL = (QSPI_CTL & ~QSPI_CTL_TMOUTEN) | toen;

        if(toen == QSPI_CTL_TMOUTEN) {
            /* configure QSPI: TMOUT register with the timeout value */
            QSPI_TMOUT = timeout;
            QSPI_STATC = QSPI_STATC_TMOUTC;
            /* enable the QSPI TimeOut interrupt */
            QSPI_STAT |= QSPI_FLAG_TMOUTIE;
        }
        qspi_config(cmd, QSPI_MEMORY_MAPPED);
    }
}

/*!
    \brief      abort the current transmission. (API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_abort(void)
{
    QSPI_CTL |= QSPI_CTL_ABORT;
}

/*!
    \brief      enable QSPI interrupt (API_ID(0x000FU))
    \param[in]  interrupt: QSPI interrupt
                only one parameter can be selected which is shown as below:
      \arg        QSPI_INT_TC: transfer complete interrupt
      \arg        QSPI_INT_FT: FIFO threshold interrupt
      \arg        QSPI_INT_TERR: transfer error interrupt
      \arg        QSPI_INT_SM: status match interrupt
      \arg        QSPI_INT_TMOUT: timeout interrupt
      \arg        QSPI_INT_WS: wrong start sequence interrupt
    \param[out] none
    \retval     none
*/
void qspi_interrupt_enable(uint8_t interrupt)
{
    switch(interrupt) {
        /* QSPI transfer complete interrupt */
        case QSPI_INT_TC:
            QSPI_STAT |= (uint32_t)QSPI_STAT_TCIE;
            break;
        /* QSPI FIFO threshold interrupt */
        case QSPI_INT_FT:
            QSPI_STAT |= (uint32_t)QSPI_STAT_FTIE;
            break;
        /* QSPI transfer error interrupt */
        case QSPI_INT_TERR:
            QSPI_STAT |= (uint32_t)QSPI_STAT_TERRIE;
            break;
        /* QSPI status match interrupt */
        case QSPI_INT_SM:
            QSPI_STAT |= (uint32_t)QSPI_STAT_SMIE;
            break;
        /* QSPI timeout interrupt */
        case QSPI_INT_TMOUT:
            QSPI_STAT |= (uint32_t)QSPI_STAT_TMOUTIE;
            break;
        /* QSPI wrong start sequence interrupt */
        case QSPI_INT_WS:
            QSPI_STAT |= (uint32_t)QSPI_STAT_WSIE;
            break;
        default:
            break;
    }
}

/*!
    \brief      disable QSPI interrupt (API_ID(0x0010U))
    \param[in]  interrupt: QSPI interrupt
                only one parameter can be selected which is shown as below:
      \arg        QSPI_INT_TC: transfer complete interrupt
      \arg        QSPI_INT_FT: FIFO threshold interrupt
      \arg        QSPI_INT_TERR: transfer error interrupt
      \arg        QSPI_INT_SM: status match interrupt
      \arg        QSPI_INT_TMOUT: timeout interrupt
      \arg        QSPI_INT_WS: wrong start sequence interrupt
    \param[out] none
    \retval     none
*/
void qspi_interrupt_disable(uint8_t interrupt)
{
    switch(interrupt) {
        /* QSPI transfer complete interrupt */
        case QSPI_INT_TC:
            QSPI_STAT &= ~(uint32_t)QSPI_STAT_TCIE;
            break;
        /* QSPI FIFO threshold interrupt */
        case QSPI_INT_FT:
            QSPI_STAT &= ~(uint32_t)QSPI_STAT_FTIE;
            break;
        /* QSPI transfer error interrupt */
        case QSPI_INT_TERR:
            QSPI_STAT &= ~(uint32_t)QSPI_STAT_TERRIE;
            break;
        /* QSPI status match interrupt */
        case QSPI_INT_SM:
            QSPI_STAT &= ~(uint32_t)QSPI_STAT_SMIE;
            break;
        /* QSPI timeout interrupt */
        case QSPI_INT_TMOUT:
            QSPI_STAT &= ~(uint32_t)QSPI_STAT_TMOUTIE;
            break;
        /* QSPI wrong start sequence interrupt */
        case QSPI_INT_WS:
            QSPI_STAT &= ~(uint32_t)QSPI_STAT_WSIE;
            break;
        default:
            break;
    }
}

/*!
    \brief      get QSPI flag status (API_ID(0x0011U))
    \param[in]  flag: QSPI flag status
                one or more parameters can be selected which are shown as below:
      \arg        QSPI_FLAG_TERR: transfer error flag
      \arg        QSPI_FLAG_TC: transfer complete flag
      \arg        QSPI_FLAG_FT: FIFO threshold flag
      \arg        QSPI_FLAG_SM: status match flag
      \arg        QSPI_FLAG_TMOUT: timeout flag
      \arg        QSPI_FLAG_WS: wrong start sequence flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus qspi_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;

    if(RESET != (QSPI_STAT & flag)) {
        reval = SET;
    }

    return reval;
}

/*!
    \brief      clear QSPI flag status (API_ID(0x0012U))
    \param[in]  flag: QSPI flag status
                one or more parameters can be selected which are shown as below:
      \arg        QSPI_FLAG_TERR: transfer error flag
      \arg        QSPI_FLAG_TC: transfer complete flag
      \arg        QSPI_FLAG_SM: status match flag
      \arg        QSPI_FLAG_TMOUT: timeout flag
      \arg        QSPI_FLAG_WS: wrong start sequence flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
void qspi_flag_clear(uint32_t flag)
{
    QSPI_STATC |= (uint32_t)flag;
}

/*!
    \brief      configure QSPI functionalmode (API_ID(0x0013U))
    \param[in]  cmd: QSPI command parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  instruction: reference flash commands description
                  address: 0-flash size
                  alternatebytes: 0-0xFFFFFFFF
                  addresssize: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  alternatebytessize: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                      QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  dummycycles: between 0 and 31
                  instructionmode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                   QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  addressmode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  alternatebytemode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                     QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  datamode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  nbdata: 0-0xFFFFFFFF
                  sioomode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
    \param[in]  functionalmode: QSPI functionalmode select
                only one parameter can be selected which is shown as below:
      \arg        QSPI_INDIRECT_WRITE
      \arg        QSPI_INDIRECT_READ
      \arg        QSPI_AUTO_POLLING
      \arg        QSPI_MEMORY_MAPPED
    \param[out] none
    \retval     none
*/
static void qspi_config(qspi_command_struct *cmd, uint32_t functionalmode)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(cmd)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0013U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if((cmd->data_mode != QSPI_DATA_NONE) && (functionalmode != QSPI_MEMORY_MAPPED)) {
            /* configure QSPI_DTLEN register with the number of data to read or write */
            QSPI_DTLEN = cmd->data_length - 1U;
        }

        if(cmd->instruction_mode != QSPI_INSTRUCTION_NONE) {
            if(cmd->altebytes_mode != QSPI_ALTE_BYTES_NONE) {
                /* configure QSPI_ALTE register with alternate bytes value */
                QSPI_ALTE = cmd->altebytes;

                if(cmd->addr_mode != QSPI_ADDR_NONE) {
                    /* command with instruction, address and alternate bytes */
                    /* configure QSPI_TCFG register with all communications parameters */
                    QSPI_TCFG = cmd->data_mode | (cmd->dummycycles << 18) | cmd->sioo_mode |
                                cmd->altebytes_size | cmd->altebytes_mode |
                                cmd->addr_size | cmd->addr_mode | cmd->instruction_mode |
                                cmd->instruction | functionalmode;

                    if(functionalmode != QSPI_MEMORY_MAPPED) {
                        /* configure QSPI_ADDR register with address value */
                        QSPI_ADDR = cmd->addr;
                    }
                } else {
                    /* command with instruction and alternate bytes */
                    /* configure QSPI_TCFG register with all communications parameters */
                    QSPI_TCFG = cmd->data_mode | (cmd->dummycycles << 18) | cmd->sioo_mode |
                                cmd->altebytes_size | cmd->altebytes_mode |
                                cmd->addr_mode | cmd->instruction_mode |
                                cmd->instruction | functionalmode;
                }
            } else {
                if(cmd->addr_mode != QSPI_ADDR_NONE) {
                    /* command with instruction and address */
                    /* configure QSPI_TCFG register with all communications parameters */
                    QSPI_TCFG = cmd->data_mode | (cmd->dummycycles << 18) | cmd->sioo_mode |
                                cmd->altebytes_mode | cmd->addr_size | cmd->addr_mode |
                                cmd->instruction_mode | cmd->instruction | functionalmode;

                    if(functionalmode != QSPI_MEMORY_MAPPED) {
                        /* configure QSPI_ADDR register with address value */
                        QSPI_ADDR = cmd->addr;
                    }
                } else {
                    /* command with only instruction */
                    /* configure QSPI_TCFG register with all communications parameters */
                    QSPI_TCFG = cmd->data_mode | (cmd->dummycycles << 18) | cmd->sioo_mode |
                                cmd->altebytes_mode | cmd->addr_mode | cmd->instruction_mode |
                                cmd->instruction | functionalmode;
                }
            }
        } else {
            if(cmd->altebytes_mode != QSPI_ALTE_BYTES_NONE) {
                /* configure QSPI_ALTE register with alternate bytes value */
                QSPI_ALTE = cmd->altebytes;

                if(cmd->addr_mode != QSPI_ADDR_NONE) {
                    /* command with address and alternate bytes */
                    /* configure QSPI_TCFG register with all communications parameters */
                    QSPI_TCFG = cmd->data_mode | (cmd->dummycycles << 18) | cmd->sioo_mode |
                                cmd->altebytes_mode | cmd->altebytes_size | cmd->addr_size |
                                cmd->addr_mode | cmd->instruction_mode | functionalmode;

                    if(functionalmode != QSPI_MEMORY_MAPPED) {
                        /* configure QSPI_ADDR register with address value */
                        QSPI_ADDR = cmd->addr;
                    }
                } else {
                    /* command with only alternate bytes */
                    /* configure QSPI_TCFG register with all communications parameters */
                    QSPI_TCFG = cmd->data_mode | (cmd->dummycycles << 18) | cmd->sioo_mode |
                                cmd->altebytes_mode | cmd->altebytes_size |
                                cmd->addr_mode | cmd->instruction_mode | functionalmode;
                }
            } else {
                if(cmd->addr_mode != QSPI_ADDR_NONE) {
                    /* command with only address */
                    /* configure QSPI_TCFG register with all communications parameters */
                    QSPI_TCFG = cmd->data_mode | (cmd->dummycycles << 18) | cmd->sioo_mode |
                                cmd->altebytes_mode | cmd->addr_size |
                                cmd->addr_mode | cmd->instruction_mode | functionalmode;

                    if(functionalmode != QSPI_MEMORY_MAPPED) {
                        /* configure QSPI_ADDR register with address value */
                        QSPI_ADDR = cmd->addr;
                    }
                } else {
                    /* command with only data phase */
                    if(cmd->data_mode != QSPI_DATA_NONE) {
                        /* configure QSPI_TCFG register with all communications parameters */
                        QSPI_TCFG = cmd->data_mode | (cmd->dummycycles << 18) | cmd->sioo_mode |
                                    cmd->altebytes_mode | cmd->addr_mode |
                                    cmd->instruction_mode | functionalmode;
                    }
                }
            }
        }
    }
}
