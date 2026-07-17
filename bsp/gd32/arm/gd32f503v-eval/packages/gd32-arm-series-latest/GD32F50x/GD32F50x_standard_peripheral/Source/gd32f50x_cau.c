/*!
    \file    gd32f50x_cau.c
    \brief   CAU driver

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

#include "gd32f50x_cau.h"
#include <string.h>

#define AESBSY_TIMEOUT                  ((uint32_t)0x00010000U)
#define BLOCK_DATA_SIZE                 16U

#define CAU_DMA_MASK                    ((uint32_t)0x00000003U)     /*!< CAU DMA enable mask */
#define CAU_INT_MASK                    ((uint32_t)0x00000003U)     /*!< CAU interrupt enable mask */

/* configure AES key structure parameter */
static void cau_aes_key_config(uint8_t *key, uint32_t keysize, cau_key_parameter_struct *cau_key_initpara);
/* AES calculate process */
static ErrStatus cau_aes_calculate(uint8_t *input, uint32_t in_length, uint8_t *output);

/*!
    \brief      reset the CAU peripheral(API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cau_deinit(void)
{
    /* enable CAU reset state */
    rcu_periph_reset_enable(RCU_CAURST);
    /* release CAU from reset state */
    rcu_periph_reset_disable(RCU_CAURST);
}

/*!
    \brief      initialize the CAU encrypt and decrypt parameter struct with the default values(API_ID(0x0002U))
    \param[in]  none
    \param[out] cau_parameter:
                  alg_dir: algorithm directory
                    CAU_ENCRYPT, CAU_DECRYPT
                  key: key
                  key_size: key size in bytes
                  input: input data
                  in_length: input data length in bytes
    \retval     none
*/
void cau_struct_para_init(cau_parameter_struct *cau_parameter)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(cau_parameter)) {
        fw_debug_report_err(CAU_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the CAU encrypt and decrypt parameters struct with the default values */
        cau_parameter->alg_dir     = CAU_ENCRYPT;
        cau_parameter->key         = 0U;
        cau_parameter->key_size    = 0U;
        cau_parameter->input       = 0U;
        cau_parameter->in_length   = 0U;
    }
}

/*!
    \brief      initialize the key parameter structure with the default values(API_ID(0x0003U))
    \param[in]  none
    \param[out] key_initpara:
                  key_0_high: key 0 high
                  key_0_low:  key 0 low
                  key_1_high: key 1 high
                  key_1_low:  key 1 low
                  key_2_high: key 2 high
                  key_2_low:  key 2 low
                  key_3_high: key 3 high
                  key_3_low:  key 3 low
    \retval     none
*/
void cau_key_struct_para_init(cau_key_parameter_struct *key_initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(key_initpara)) {
        fw_debug_report_err(CAU_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the key parameter struct with the default values */
        key_initpara->key_0_high   = 0U;
        key_initpara->key_0_low    = 0U;
        key_initpara->key_1_high   = 0U;
        key_initpara->key_1_low    = 0U;
        key_initpara->key_2_high   = 0U;
        key_initpara->key_2_low    = 0U;
        key_initpara->key_3_high   = 0U;
        key_initpara->key_3_low    = 0U;
    }
}

/*!
    \brief      enable the CAU peripheral(API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cau_enable(void)
{
    /* enable the CAU processor */
    CAU_CTL |= CAU_CTL_CAUEN;
}

/*!
    \brief      disable the CAU peripheral(API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cau_disable(void)
{
    /* disable the CAU processor */
    CAU_CTL &= ~CAU_CTL_CAUEN;
}

/*!
    \brief      enable the CAU DMA interface(API_ID(0x0006U))
    \param[in]  dma_req: specify the CAU DMA transfer request to be enabled
                one or more parameters can be selected which are shown as below:
      \arg        CAU_DMA_INFIFO: DMA for incoming(Rx) data transfer
      \arg        CAU_DMA_OUTFIFO: DMA for outgoing(Tx) data transfer
    \param[out] none
    \retval     none
*/
void cau_dma_enable(uint32_t dma_req)
{
    /* enable the selected CAU DMA request */
    CAU_DMAEN |= dma_req & CAU_DMA_MASK;
}

/*!
    \brief      disable the CAU DMA interface(API_ID(0x0007U))
    \param[in]  dma_req: specify the CAU DMA transfer request to be disabled
                one or more parameters can be selected which are shown as below:
      \arg        CAU_DMA_INFIFO: DMA for incoming(Rx) data transfer
      \arg        CAU_DMA_OUTFIFO: DMA for outgoing(Tx) data transfer
    \param[out] none
    \retval     none
*/
void cau_dma_disable(uint32_t dma_req)
{
    /* disable the selected CAU DMA request */
    CAU_DMAEN &= ~(dma_req);
}

/*!
    \brief      initialize the CAU peripheral(API_ID(0x0008U))
    \param[in]  alg_dir: algorithm direction
                only one parameter can be selected which is shown as below:
      \arg        CAU_ENCRYPT: encrypt
      \arg        CAU_DECRYPT: decrypt
    \param[in]  algo_mode: algorithm mode selection
                only one parameter can be selected which is shown as below:
      \arg        CAU_MODE_AES_ECB: AES-ECB (AES Electronic codebook)
      \arg        CAU_MODE_AES_KEY: AES decryption key preparation mode
    \param[in]  swapping: data swapping selection
                only one parameter can be selected which is shown as below:
      \arg        CAU_SWAPPING_32BIT: no swapping
      \arg        CAU_SWAPPING_16BIT: half-word swapping
      \arg        CAU_SWAPPING_8BIT: bytes swapping
      \arg        CAU_SWAPPING_1BIT: bit swapping
    \param[out] none
    \retval     none
*/
void cau_init(uint32_t alg_dir, uint32_t algo_mode, uint32_t swapping)
{
    /* select algorithm mode */
    CAU_CTL &= ~CAU_CTL_ALGM;
    CAU_CTL |= algo_mode & CAU_CTL_ALGM;

    /* select data swapping */
    CAU_CTL &= ~CAU_CTL_DATAM;
    CAU_CTL |= swapping & CAU_CTL_DATAM;

    /* select algorithm direction */
    CAU_CTL &= ~CAU_CTL_CAUDIR;
    CAU_CTL |= alg_dir & CAU_CTL_CAUDIR;
}

/*!
    \brief      configure key size if use AES algorithm(API_ID(0x0009U))
    \param[in]  key_size: key length selection when aes mode
                only one parameter can be selected which is shown as below:
      \arg        CAU_KEYSIZE_128BIT: 128 bit key length
      \arg        CAU_KEYSIZE_192BIT: 192 bit key length
      \arg        CAU_KEYSIZE_256BIT: 256 bit key length
    \param[out] none
    \retval     none
*/
void cau_aes_keysize_config(uint32_t key_size)
{
    CAU_CTL &= ~CAU_CTL_KEYM;
    CAU_CTL |= key_size & CAU_CTL_KEYM;
}

/*!
    \brief      initialize the key parameters(API_ID(0x000AU))
    \param[in]  key_initpara: key init parameter struct
                  key_0_high: key 0 high
                  key_0_low:  key 0 low
                  key_1_high: key 1 high
                  key_1_low:  key 1 low
                  key_2_high: key 2 high
                  key_2_low:  key 2 low
                  key_3_high: key 3 high
                  key_3_low:  key 3 low
    \param[out] none
    \retval     none
*/
void cau_key_init(cau_key_parameter_struct *key_initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(key_initpara)) {
        fw_debug_report_err(CAU_MODULE_ID, API_ID(0x000AU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CAU_KEY0H = key_initpara->key_0_high;
        CAU_KEY0L = key_initpara->key_0_low;
        CAU_KEY1H = key_initpara->key_1_high;
        CAU_KEY1L = key_initpara->key_1_low;
        CAU_KEY2H = key_initpara->key_2_high;
        CAU_KEY2L = key_initpara->key_2_low;
        CAU_KEY3H = key_initpara->key_3_high;
        CAU_KEY3L = key_initpara->key_3_low;
    }
}

/*!
    \brief      flush the IN and OUT FIFOs(API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cau_fifo_flush(void)
{
    /* reset the read and write pointers of the FIFOs */
    CAU_CTL |= CAU_CTL_FFLUSH;
}

/*!
    \brief      return whether CAU peripheral is enabled or disabled(API_ID(0x000CU))
    \param[in]  none
    \param[out] none
    \retval     ControlStatus: ENABLE or DISABLE
*/
ControlStatus cau_enable_state_get(void)
{
    ControlStatus ret = DISABLE;
    if(RESET != (CAU_CTL & CAU_CTL_CAUEN)) {
        ret = ENABLE;
    }
    return ret;
}

/*!
    \brief      write data to the IN FIFO(API_ID(0x000DU))
    \param[in]  data: data to write (0U - 0xFFFFFFFFU)
    \param[out] none
    \retval     none
*/
void cau_data_write(uint32_t data)
{
    CAU_DI = data;
}

/*!
    \brief      return the last data entered into the output FIFO(API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     last data entered into the output FIFO
*/
uint32_t cau_data_read(void)
{
    return CAU_DO;
}

/*!
    \brief      encrypt and decrypt using AES in ECB mode(API_ID(0x000FU))
    \param[in]  cau_parameter: pointer to the input structure
                  alg_dir: algorithm directory
                    CAU_ENCRYPT, CAU_DECRYPT
                  key: key
                  key_size: key size in bits, must be either 128, 192 or 256
                  input: input data
                  in_length: input data length in bytes, must be a multiple of 16 bytes
    \param[out] output: pointer to the returned buffer
    \retval     ErrStatus: SUCCESS or ERROR
    \note       This function includes timeout exit scenarios.
                Modify according to the use's actual usage scenarios.
*/
ErrStatus cau_aes_ecb(cau_parameter_struct *cau_parameter, uint8_t *output)
{
    ErrStatus ret = SUCCESS;
    cau_key_parameter_struct key_initpara;
    __IO uint32_t counter = 0U;
    uint32_t busystatus = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(cau_parameter)) {
        fw_debug_report_err(CAU_MODULE_ID, API_ID(0x000FU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* key structure initialization */
        cau_key_struct_para_init(&key_initpara);
        /* AES key structure parameter configuration */
        cau_aes_key_config(cau_parameter->key, cau_parameter->key_size, &key_initpara);
        /* key initialization */
        cau_key_init(&key_initpara);

        /* AES decryption */
        if(CAU_DECRYPT == cau_parameter->alg_dir) {
            /* flush the IN and OUT FIFOs */
            cau_fifo_flush();
            /* initialize the CAU peripheral */
            cau_init(CAU_DECRYPT, CAU_MODE_AES_KEY, CAU_SWAPPING_32BIT);

            /* enable the CAU peripheral */
            cau_enable();

            /* wait until the busy flag is RESET */
            do {
                busystatus = cau_flag_get(CAU_FLAG_BUSY);
                counter++;
            } while((AESBSY_TIMEOUT != counter) && (RESET != busystatus));

            if(RESET != busystatus) {
                ret = ERROR;
            }
        }

        if(ERROR != ret) {
            /* initialize the CAU peripheral */
            cau_init(cau_parameter->alg_dir, CAU_MODE_AES_ECB, CAU_SWAPPING_8BIT);

            /* flush the IN and OUT FIFOs */
            cau_fifo_flush();

            /* enable the CAU peripheral */
            cau_enable();
            /* AES calculate process */
            ret = cau_aes_calculate(cau_parameter->input, cau_parameter->in_length, output);
            /* disable the CAU peripheral */
            cau_disable();
        }
    }
    return ret;
}

/*!
    \brief      get the CAU flag status(API_ID(0x0010U))
    \param[in]  flag: CAU flag status
                only one parameter can be selected which is shown as below:
      \arg        CAU_FLAG_INFIFO_EMPTY: input FIFO empty
      \arg        CAU_FLAG_INFIFO_NO_FULL: input FIFO is not full
      \arg        CAU_FLAG_OUTFIFO_NO_EMPTY: output FIFO not empty
      \arg        CAU_FLAG_OUTFIFO_FULL: output FIFO is full
      \arg        CAU_FLAG_BUSY: the CAU core is busy
      \arg        CAU_FLAG_INFIFO: input FIFO flag status
      \arg        CAU_FLAG_OUTFIFO: output FIFO flag status
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cau_flag_get(uint32_t flag)
{
    uint32_t reg = 0U;
    FlagStatus ret_flag = RESET;

    /* check if the flag is in CAU_STAT1 register */
    if(1U == (flag >> 31U)) {
        reg = CAU_STAT1;
    } else {
        /* the flag is in CAU_STAT0 register */
        reg = CAU_STAT0;
    }

    /* check the status of the specified CAU flag */
    if(0U != (reg & flag)) {
        ret_flag = SET;
    }

    return ret_flag;
}

/*!
    \brief      enable the CAU interrupts(API_ID(0x0011U))
    \param[in]  interrupt: specify the CAU interrupt source to be enabled
                one or more parameters can be selected which are shown as below:
      \arg        CAU_INT_INFIFO: input FIFO interrupt
      \arg        CAU_INT_OUTFIFO: output FIFO interrupt
    \param[out] none
    \retval     none
*/
void cau_interrupt_enable(uint32_t interrupt)
{
    /* enable the selected CAU interrupt */
    CAU_INTEN |= interrupt & CAU_INT_MASK;
}

/*!
    \brief      disable the CAU interrupts(API_ID(0x0012U))
    \param[in]  interrupt: specify the CAU interrupt source to be disabled
                one or more parameters can be selected which are shown as below:
      \arg        CAU_INT_INFIFO: input FIFO interrupt
      \arg        CAU_INT_OUTFIFO: output FIFO interrupt
    \param[out] none
    \retval     none
*/
void cau_interrupt_disable(uint32_t interrupt)
{
    /* disable the selected CAU interrupt */
    CAU_INTEN &= ~(interrupt);
}

/*!
    \brief      get the interrupt flag(API_ID(0x0013U))
    \param[in]  interrupt: CAU interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        CAU_INT_FLAG_INFIFO: input FIFO interrupt
      \arg        CAU_INT_FLAG_OUTFIFO: output FIFO interrupt
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cau_interrupt_flag_get(uint32_t interrupt)
{
    FlagStatus flag = RESET;

    /* check the status of the specified CAU interrupt */
    if(RESET != (CAU_INTF & interrupt)) {
        flag = SET;
    }

    return flag;
}

/*!
    \brief      AES key structure parameter configuration
    \param[in]  key: key used for AES algorithm
    \param[in]  keysize: length of the key in bits, must be either 128, 192 or 256
    \param[out] cau_key_initpara: key init parameter struct
                  key_0_high: key 0 high
                  key_0_low:  key 0 low
                  key_1_high: key 1 high
                  key_1_low:  key 1 low
                  key_2_high: key 2 high
                  key_2_low:  key 2 low
                  key_3_high: key 3 high
                  key_3_low:  key 3 low
    \retval     none
*/
static void cau_aes_key_config(uint8_t *key, uint32_t keysize, cau_key_parameter_struct *cau_key_initpara)
{
    uint32_t keyaddr = (uint32_t)key;

    switch(keysize) {
    case 128:
        cau_aes_keysize_config(CAU_KEYSIZE_128BIT);
        cau_key_initpara->key_2_high = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_2_low  = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_high = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_low  = __REV(*(uint32_t *)(keyaddr));
        break;
    case 192:
        cau_aes_keysize_config(CAU_KEYSIZE_192BIT);
        cau_key_initpara->key_1_high = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_1_low  = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_2_high = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_2_low  = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_high = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_low  = __REV(*(uint32_t *)(keyaddr));
        break;
    case 256:
        cau_aes_keysize_config(CAU_KEYSIZE_256BIT);
        cau_key_initpara->key_0_high = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_0_low  = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_1_high = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_1_low  = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_2_high = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_2_low  = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_high = __REV(*(uint32_t *)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_low  = __REV(*(uint32_t *)(keyaddr));
        break;
    default:
        break;
    }
}

/*!
    \brief      AES calculate process
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer in bytes, must be a multiple of 16 bytes
    \param[out] output: pointer to the returned buffer
    \retval     ErrStatus: SUCCESS or ERROR
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the use's actual usage scenarios.
    \note       This function includes timeout exit scenarios.
                Modify according to the use's actual usage scenarios.
*/
static ErrStatus cau_aes_calculate(uint8_t *input, uint32_t in_length, uint8_t *output)
{
    uint32_t inputaddr  = (uint32_t)input;
    uint32_t outputaddr = (uint32_t)output;
    uint32_t i = 0U;
    __IO uint32_t counter = 0U;
    uint32_t busystatus = 0U;
    ErrStatus ret = SUCCESS;

    /* the clock is not enabled or there is no embedded CAU peripheral */
    if(DISABLE == cau_enable_state_get()) {
        ret = ERROR;
    } else {
        for(i = 0U; i < in_length; i += BLOCK_DATA_SIZE) {
            /* wait until the IEM flag is set */
            while(RESET == cau_flag_get(CAU_FLAG_INFIFO_EMPTY)) {
            }

            /* check if the last input data block */
            if(i + BLOCK_DATA_SIZE > in_length) {
                /* the last block data number is less than 128 bits */
                uint32_t block_data_temp[4] = {0};

                /* fill the remaining bits with zero */
                memcpy(block_data_temp, (uint32_t *)inputaddr, in_length - i);
                inputaddr = (uint32_t)block_data_temp;
            }

            /* write data to the IN FIFO */
            cau_data_write(*(uint32_t *)(inputaddr));
            inputaddr += 4U;
            cau_data_write(*(uint32_t *)(inputaddr));
            inputaddr += 4U;
            cau_data_write(*(uint32_t *)(inputaddr));
            inputaddr += 4U;
            cau_data_write(*(uint32_t *)(inputaddr));
            inputaddr += 4U;

            /* wait until the complete message has been processed */
            counter = 0U;
            do {
                busystatus = cau_flag_get(CAU_FLAG_BUSY);
                counter++;
            } while((AESBSY_TIMEOUT != counter) && (RESET != busystatus));

            if(RESET != busystatus) {
                ret = ERROR;
                /* break loop on error */
                break;
            } else {
                /* read the output block from the output FIFO */
                *(uint32_t *)(outputaddr) = cau_data_read();
                outputaddr += 4U;
                *(uint32_t *)(outputaddr) = cau_data_read();
                outputaddr += 4U;
                *(uint32_t *)(outputaddr) = cau_data_read();
                outputaddr += 4U;
                *(uint32_t *)(outputaddr) = cau_data_read();
                outputaddr += 4U;
            }
        }
    }

    return ret;
}
