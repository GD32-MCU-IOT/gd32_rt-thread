/*!
    \file    gd32f50x_hau.c
    \brief   HAU driver

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

#include "gd32f50x_hau.h"

#define HAU_BSY_TIMEOUT                 ((uint32_t)0x00010000U)

#define HAU_INT_MASK                    ((uint32_t)0x00000003U)     /*!< HAU interrupt enable mask */

/* HAU SHA digest read in HASH mode */
static void hau_sha_digest_read(uint8_t output[]);
/* HAU digest calculate process in HASH mode */
static ErrStatus hau_hash_calculate(uint8_t input[], uint32_t in_length, uint8_t output[]);

/*!
    \brief      reset the HAU peripheral(API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hau_deinit(void)
{
    /* enable HAU reset state */
    rcu_periph_reset_enable(RCU_HAURST);
    /* release HAU from reset state */
    rcu_periph_reset_disable(RCU_HAURST);
}

/*!
    \brief      initialize the HAU peripheral parameters(API_ID(0x0002U))
    \param[in]  datatype: data type mode
                  datatype: HAU_SWAPPING_32BIT, HAU_SWAPPING_16BIT, HAU_SWAPPING_8BIT, HAU_SWAPPING_1BIT
    \param[out] none
    \retval     none
*/
void hau_init(uint32_t datatype)
{
    /* configure the algorithm, mode and the data type */
    HAU_CTL &= (~(uint32_t)(HAU_CTL_DATAM));
    HAU_CTL |= datatype & HAU_CTL_DATAM;

    /* start the digest of a new message */
    HAU_CTL |= HAU_CTL_START;
}

/*!
    \brief      reset the HAU processor core(API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hau_reset(void)
{
    /* set to 1 to reset the HAU processor core, then it is ready to start the digest calculation */
    HAU_CTL |= HAU_CTL_START;
}

/*!
    \brief      configure the number of valid bits in last word of the message(API_ID(0x0004U))
    \param[in]  valid_num: number of valid bits in last word of the message
                only one parameter can be selected which is shown as below:
      \arg        0x00: all 32 bits of the last data written are valid
      \arg        0x01: only bit [31] of the last data written to HAU_DI after data swapping are valid
      \arg        0x02: only bits [31:30] of the last data written to HAU_DI after data swapping are valid
      \arg        0x03: only bits [31:29] of the last data written to HAU_DI after data swapping are valid
                  ...
      \arg        0x1F: only bits [31:1] of the last data written to HAU_DI after data swapping are valid
    \param[out] none
    \retval     none
*/
void hau_last_word_validbits_num_config(uint32_t valid_num)
{
    HAU_CFG &= (~(uint32_t)HAU_CFG_VBL);
    HAU_CFG |= CFG_VBL(valid_num);
}

/*!
    \brief      write data to the IN FIFO(API_ID(0x0005U))
    \param[in]  data: data to write
    \param[out] none
    \retval     none
*/
void hau_data_write(uint32_t data)
{
    HAU_DI = data;
}

/*!
    \brief      return the number of words already written into the IN FIFO(API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     number of words in the input FIFO
*/
uint32_t hau_infifo_words_num_get(void)
{
    uint32_t ret = 0U;
    ret = GET_CTL_NWIF(HAU_CTL);
    return ret;
}

/*!
    \brief      read the message digest result(API_ID(0x0007U))
    \param[in]  none
    \param[out] digestpara: HAU digest parameter struct
                  out[x](x = 0...7): message digest result 0-7
    \retval     none
*/
void hau_digest_read(hau_digest_parameter_struct* digestpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(digestpara)) {
        fw_debug_report_err(HAU_MODULE_ID, API_ID(0x0007U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        digestpara->out[0] = HAU_DO0;
        digestpara->out[1] = HAU_DO1;
        digestpara->out[2] = HAU_DO2;
        digestpara->out[3] = HAU_DO3;
        digestpara->out[4] = HAU_DO4;
        digestpara->out[5] = HAU_DO5;
        digestpara->out[6] = HAU_DO6;
        digestpara->out[7] = HAU_DO7;
    }
}

/*!
    \brief      enable digest calculation(API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hau_digest_calculation_enable(void)
{
    HAU_CFG |= HAU_CFG_CALEN;
}

/*!
    \brief      configure single or multiple DMA is used, and digest calculation at the end of a DMA transfer or not(API_ID(0x0009U))
    \param[in]  multi_single
                only one parameter can be selected which is shown as below:
      \arg        SINGLE_DMA_AUTO_DIGEST: message padding and message digest calculation at the end of a DMA transfer
      \arg        MULTIPLE_DMA_NO_DIGEST: multiple DMA transfers needed and CALEN bit is not automatically set at the end of a DMA transfer
    \param[out] none
    \retval     none
*/
void hau_multiple_single_dma_config(uint32_t multi_single)
{
    HAU_CTL &= (~(uint32_t)HAU_CTL_MDS);
    HAU_CTL |= multi_single & HAU_CTL_MDS;
}
  
/*!
    \brief      enable the HAU DMA interface(API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hau_dma_enable(void)
{
    HAU_CTL |= HAU_CTL_DMAE;
}

/*!
    \brief      disable the HAU DMA interface(API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hau_dma_disable(void)
{
    HAU_CTL &= (~(uint32_t)HAU_CTL_DMAE);
}

/*!
    \brief      calculate digest using SHA256 in HASH mode(API_ID(0x000CU))
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[out] output: the result digest
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hau_hash_sha_256(uint8_t input[], uint32_t in_length, uint8_t output[])
{
    ErrStatus ret = ERROR;
    ret = hau_hash_calculate(input, in_length, output);
    return ret;
}

/*!
    \brief      get the HAU flag status(API_ID(0x000DU))
    \param[in]  flag: HAU flag status
                only one parameter can be selected which is shown as below:
      \arg        HAU_FLAG_DATA_INPUT:           there is enough space (16 bytes) in the input FIFO
      \arg        HAU_FLAG_CALCULATION_COMPLETE: digest calculation is completed
      \arg        HAU_FLAG_DMA:                  DMA is enabled (DMAE =1) or a transfer is processing
      \arg        HAU_FLAG_BUSY:                 data block is in process
      \arg        HAU_FLAG_INFIFO_NO_EMPTY:      the input FIFO is not empty
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hau_flag_get(uint32_t flag)
{
    uint32_t ret = 0U;
    FlagStatus ret_flag = RESET;

    /* check if the flag is in HAU_CTL register */
    if(RESET != (flag & HAU_FLAG_INFIFO_NO_EMPTY)){ 
        ret = HAU_CTL;
    }else{
        ret = HAU_STAT;
    }

    if (RESET != (ret & flag)){
        ret_flag = SET;
    }

    return ret_flag;
}

/*!
    \brief      clear the HAU flag status(API_ID(0x000EU))
    \param[in]  flag: HAU flag status
                one or more parameters can be selected which are shown as below:
      \arg        HAU_FLAG_DATA_INPUT:           there is enough space (16 bytes) in the input FIFO
      \arg        HAU_FLAG_CALCULATION_COMPLETE: digest calculation is completed
    \param[out] none
    \retval     none
*/
void hau_flag_clear(uint32_t flag)
{
    HAU_STAT = ~(uint32_t)(flag);
}

/*!
    \brief      enable the HAU interrupts(API_ID(0x000FU))
    \param[in]  interrupt: specify the HAU interrupt source to be enabled
                one or more parameters can be selected which are shown as below:
      \arg        HAU_INT_DATA_INPUT: a new block can be entered into the IN buffer 
      \arg        HAU_INT_CALCULATION_COMPLETE: calculation complete
    \param[out] none
    \retval     none
*/
void hau_interrupt_enable(uint32_t interrupt)
{
    HAU_INTEN |= interrupt & HAU_INT_MASK;
}

/*!
    \brief      disable the HAU interrupts(API_ID(0x0010U))
    \param[in]  interrupt: specify the HAU interrupt source to be disabled
                one or more parameters can be selected which are shown as below:
      \arg        HAU_INT_DATA_INPUT:           a new block can be entered into the IN buffer
      \arg        HAU_INT_CALCULATION_COMPLETE: calculation complete
    \param[out] none
    \retval     none
*/
void hau_interrupt_disable(uint32_t interrupt)
{
    HAU_INTEN &= ~(uint32_t)(interrupt);
}

/*!
    \brief      get the HAU interrupt flag status(API_ID(0x0011U))
    \param[in]  int_flag: HAU interrupt flag status
                only one parameter can be selected which is shown as below:
      \arg        HAU_INT_FLAG_DATA_INPUT:           there is enough space (16 bytes) in the input FIFO
      \arg        HAU_INT_FLAG_CALCULATION_COMPLETE: digest calculation is completed
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hau_interrupt_flag_get(uint32_t int_flag)
{
    uint32_t ret = 0U;
    FlagStatus flag = RESET;

    /* return the status of the interrupt */
    ret =  HAU_STAT;

    if(RESET != ((HAU_INTEN & ret) & int_flag)){
        flag = SET;
    }

    return flag;
}

/*!
    \brief      clear the HAU interrupt flag status(API_ID(0x0012U))
    \param[in]  int_flag: HAU interrupt flag status
                one or more parameters can be selected which are shown as below:
      \arg        HAU_INT_FLAG_DATA_INPUT:           there is enough space (16 bytes) in the input FIFO
      \arg        HAU_INT_FLAG_CALCULATION_COMPLETE: digest calculation is completed
    \param[out] none
    \retval     none
*/
void hau_interrupt_flag_clear(uint32_t int_flag)
{
    HAU_STAT = ~(uint32_t)(int_flag);
}

/*!
    \brief      HAU digest read
    \param[in]  none
    \param[out] output: the result digest
    \retval     none
*/
static void hau_sha_digest_read(uint8_t output[])
{
    hau_digest_parameter_struct digest_para;
    uint32_t outputaddr = (uint32_t)output;

    /* read the message digest result */
    hau_digest_read(&digest_para);
    /* reverse byte order, copy result to outputaddr */
    *(uint32_t*)(outputaddr)  = __REV(digest_para.out[0]);
    outputaddr += 4U;
    *(uint32_t*)(outputaddr)  = __REV(digest_para.out[1]);
    outputaddr += 4U;
    *(uint32_t*)(outputaddr)  = __REV(digest_para.out[2]);
    outputaddr += 4U;
    *(uint32_t*)(outputaddr)  = __REV(digest_para.out[3]);
    outputaddr += 4U;
    *(uint32_t*)(outputaddr)  = __REV(digest_para.out[4]);
    outputaddr += 4U;
    *(uint32_t*)(outputaddr)  = __REV(digest_para.out[5]);
    outputaddr += 4U;
    *(uint32_t*)(outputaddr)  = __REV(digest_para.out[6]);
    outputaddr += 4U;
    *(uint32_t*)(outputaddr)  = __REV(digest_para.out[7]);
}

/*!
    \brief      HAU digest calculate process in HASH mode
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[out] output: the result digest
    \retval     ErrStatus: SUCCESS or ERROR
    \note       This function includes timeout exit scenarios.
                Modify according to the use's actual usage scenarios.
*/
static ErrStatus hau_hash_calculate(uint8_t input[], uint32_t in_length, uint8_t output[])
{
    uint32_t datatype;
    ErrStatus ret = SUCCESS;

    __IO uint32_t num_last_valid = 0U;
    uint32_t i = 0U;
    __IO uint32_t counter = 0U;
    uint32_t busystatus = 0U;
    uint32_t inputaddr  = (uint32_t)input;

    /* number of valid bits in last word */
    num_last_valid = 8U * (in_length % 4U);

    /* HAU peripheral initialization */
    hau_deinit();

    /* HAU configuration */
    datatype = HAU_SWAPPING_8BIT;
    hau_init(datatype);

    /* configure the number of valid bits in last word of the message */
    hau_last_word_validbits_num_config(num_last_valid);

    /* write data to the IN FIFO */
    for(i = 0U; i < in_length; i += 4U) {
        hau_data_write(*(uint32_t*)inputaddr);
        inputaddr += 4U;
    }

    /* enable digest calculation */
    hau_digest_calculation_enable();

    /* wait until the busy flag is reset */
    do {
        busystatus = hau_flag_get(HAU_FLAG_BUSY);
        counter++;
    } while((HAU_BSY_TIMEOUT != counter) && (RESET != busystatus));

    if(RESET != busystatus) {
        ret = ERROR;
    } else {
        /* read the message digest */
        hau_sha_digest_read(output);
    }
    return ret;
}
