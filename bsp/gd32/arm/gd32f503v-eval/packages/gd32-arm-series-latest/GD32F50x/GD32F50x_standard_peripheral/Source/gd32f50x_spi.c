/*!
    \file    gd32f50x_spi.c
    \brief   SPI driver

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

#include "gd32f50x_spi.h"

/* SPI/I2S parameter initialization mask */
#define SPI_INIT_MASK                   0x00003040U  /*!< SPI parameter initialization mask */
#define I2S_INIT_MASK                   0x0000F047U  /*!< I2S parameter initialization mask */

/* default value */
#define SPI_I2SPSC_DEFAULT_VALUE        0x00000002U  /*!< default value of SPI_I2SPSC register */

/* I2S clock source selection, multiplication and division mask */
#define I2S1_CLOCK_SEL                  0x00020000U  /*!< I2S1 clock source selection */
#define I2S2_CLOCK_SEL                  0x00040000U  /*!< I2S2 clock source selection */
#define I2S_CLOCK_MUL_MASK              0x00003F00U  /*!< I2S clock multiplication mask */
#define I2S_CLOCK_DIV_MASK              0x000000F0U  /*!< I2S clock division mask */
#define I2S1_CLOCK_DIV1_MASK            0x000000F8U  /*!< I2S1 clock division mask */
#define I2S2_CLOCK_DIV1_MASK            0x007C0000U  /*!< I2S2 clock division mask */

/*!
    \brief      reset SPI and I2S (API_ID: 0x0001U) 
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_i2s_deinit(uint32_t spi_periph)
{
    switch(spi_periph){
    case SPI0:
        /* reset SPI0 */
        rcu_periph_reset_enable(RCU_SPI0RST);
        rcu_periph_reset_disable(RCU_SPI0RST);
        break;
    case SPI1:
        /* reset SPI1 and I2S1 */
        rcu_periph_reset_enable(RCU_SPI1RST);
        rcu_periph_reset_disable(RCU_SPI1RST);
        break;
    case SPI2:
        /* reset SPI2 and I2S2 */
        rcu_periph_reset_enable(RCU_SPI2RST);
        rcu_periph_reset_disable(RCU_SPI2RST);
        break;
    default :
        break;
    }
}

/*!
    \brief      initialize the parameters of SPI struct with default values (API_ID: 0x0002U)
    \param[in]  none
    \param[out] spi_parameter_struct: the initialized struct spi_parameter_struct pointer
    \retval     none
*/
void spi_struct_para_init(spi_parameter_struct *spi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(spi_struct)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure the structure with default value */
        spi_struct->device_mode          = SPI_SLAVE;
        spi_struct->trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
        spi_struct->frame_size           = SPI_FRAMESIZE_8BIT;
        spi_struct->nss                  = SPI_NSS_HARD;
        spi_struct->clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
        spi_struct->prescale             = SPI_PSC_2;
        spi_struct->endian               = SPI_ENDIAN_MSB;
    }
}

/*!
    \brief      initialize SPI parameter (API_ID: 0x0003U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  spi_struct: SPI parameter initialization stuct members of the structure 
                            and the member values are shown as below:
                  device_mode: SPI_MASTER, SPI_SLAVE
                  trans_mode: SPI_TRANSMODE_FULLDUPLEX, SPI_TRANSMODE_RECEIVEONLY,
                              SPI_TRANSMODE_BDRECEIVE, SPI_TRANSMODE_BDTRANSMIT
                  frame_size: SPI_FRAMESIZE_16BIT, SPI_FRAMESIZE_8BIT
                  nss: SPI_NSS_SOFT, SPI_NSS_HARD
                  endian: SPI_ENDIAN_MSB, SPI_ENDIAN_LSB
                  clock_polarity_phase: SPI_CK_PL_LOW_PH_1EDGE, SPI_CK_PL_HIGH_PH_1EDGE
                                        SPI_CK_PL_LOW_PH_2EDGE, SPI_CK_PL_HIGH_PH_2EDGE
                  prescale: SPI_PSC_n (n=2,4,8,16,32,64,128,256)
    \param[out] none
    \retval     none
*/
void spi_init(uint32_t spi_periph, spi_parameter_struct* spi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(spi_struct)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg = 0U;
        reg = SPI_CTL0(spi_periph);
        reg &= SPI_INIT_MASK;

        /* select SPI as master or slave */
        reg |= (spi_struct->device_mode & (SPI_CTL0_MSTMOD | SPI_CTL0_SWNSS));
        /* select SPI transfer mode */
        reg |= (spi_struct->trans_mode & (SPI_CTL0_BDEN | SPI_CTL0_BDOEN | SPI_CTL0_RO));
        /* select SPI frame size */
        reg |= (spi_struct->frame_size & SPI_CTL0_FF16);
        /* select SPI NSS use hardware or software */
        reg |= (spi_struct->nss & SPI_CTL0_SWNSSEN);
        /* select SPI LSB or MSB */
        reg |= (spi_struct->endian & SPI_CTL0_LF);
        /* select SPI polarity and phase */
        reg |= (spi_struct->clock_polarity_phase & (SPI_CTL0_CKPL | SPI_CTL0_CKPH));
        /* select SPI prescale to adjust transmit speed */
        reg |= (spi_struct->prescale & SPI_CTL0_PSC);

        /* write to SPI_CTL0 register */
        SPI_CTL0(spi_periph) = reg;

        /* clear the I2SSEL bit in the SPI_I2SCTL register to configure SPI mode */
        SPI_I2SCTL(spi_periph) &= ~SPI_I2SCTL_I2SSEL;
    }
}

/*!
    \brief      enable SPI (API_ID: 0x0004U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_enable(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= SPI_CTL0_SPIEN;
}

/*!
    \brief      disable SPI (API_ID: 0x0005U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_disable(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) &= ~SPI_CTL0_SPIEN;
}

/*!
    \brief      initialize I2S parameter (API_ID: 0x0006U)
    \param[in]  spi_periph: SPIx(x=1,2)
    \param[in]  i2s_mode: I2S operation mode
                only one parameter can be selected which is shown as below:
      \arg        I2S_MODE_SLAVETX: I2S slave transmit mode
      \arg        I2S_MODE_SLAVERX: I2S slave receive mode
      \arg        I2S_MODE_MASTERTX: I2S master transmit mode
      \arg        I2S_MODE_MASTERRX: I2S master receive mode
    \param[in]  i2s_standard: I2S standard
                only one parameter can be selected which is shown as below:
      \arg        I2S_STD_PHILIPS: I2S philips standard
      \arg        I2S_STD_MSB: I2S MSB standard
      \arg        I2S_STD_LSB: I2S LSB standard
      \arg        I2S_STD_PCMSHORT: I2S PCM short standard
      \arg        I2S_STD_PCMLONG: I2S PCM long standard
    \param[in]  i2s_ckpl: I2S idle state clock polarity
                only one parameter can be selected which is shown as below:
      \arg        I2S_CKPL_LOW: I2S clock polarity low level
      \arg        I2S_CKPL_HIGH: I2S clock polarity high level
    \param[out] none
    \retval     none
*/
void i2s_init(uint32_t spi_periph, uint32_t i2s_mode, uint32_t i2s_standard, uint32_t i2s_ckpl)
{
    uint32_t reg= 0U;

    reg = SPI_I2SCTL(spi_periph);
    reg &= I2S_INIT_MASK;

    /* enable I2S mode */
    reg |= SPI_I2SCTL_I2SSEL; 
    /* select I2S mode */
    reg |= (i2s_mode & SPI_I2SCTL_I2SOPMOD);
    /* select I2S standard */
    reg |= (i2s_standard & SPI_I2SCTL_I2SSTD);
    /* select I2S polarity */
    reg |= (i2s_ckpl & SPI_I2SCTL_CKPL);

    /* write to SPI_I2SCTL register */
    SPI_I2SCTL(spi_periph) = reg;
}

/*!
    \brief      configure I2S prescaler (API_ID: 0x0007U)
    \param[in]  spi_periph: SPIx(x=1,2)
    \param[in]  i2s_audiosample: I2S audio sample rate
                only one parameter can be selected which is shown as below:
      \arg        I2S_AUDIOSAMPLE_8K: audio sample rate is 8KHz
      \arg        I2S_AUDIOSAMPLE_11K: audio sample rate is 11KHz
      \arg        I2S_AUDIOSAMPLE_16K: audio sample rate is 16KHz
      \arg        I2S_AUDIOSAMPLE_22K: audio sample rate is 22KHz
      \arg        I2S_AUDIOSAMPLE_32K: audio sample rate is 32KHz
      \arg        I2S_AUDIOSAMPLE_44K: audio sample rate is 44KHz
      \arg        I2S_AUDIOSAMPLE_48K: audio sample rate is 48KHz
      \arg        I2S_AUDIOSAMPLE_96K: audio sample rate is 96KHz
      \arg        I2S_AUDIOSAMPLE_192K: audio sample rate is 192KHz
    \param[in]  i2s_frameformat: I2S data length and channel length
                only one parameter can be selected which is shown as below:
      \arg        I2S_FRAMEFORMAT_DT16B_CH16B: I2S data length is 16 bit and channel length is 16 bit
      \arg        I2S_FRAMEFORMAT_DT16B_CH32B: I2S data length is 16 bit and channel length is 32 bit
      \arg        I2S_FRAMEFORMAT_DT24B_CH32B: I2S data length is 24 bit and channel length is 32 bit
      \arg        I2S_FRAMEFORMAT_DT32B_CH32B: I2S data length is 32 bit and channel length is 32 bit
    \param[in]  i2s_mckout: I2S master clock output
                only one parameter can be selected which is shown as below:
      \arg        I2S_MCKOUT_ENABLE: I2S master clock output enable
      \arg        I2S_MCKOUT_DISABLE: I2S master clock output disable
    \param[out] none
    \retval     none
*/
void i2s_psc_config(uint32_t spi_periph, uint32_t i2s_audiosample, uint32_t i2s_frameformat, uint32_t i2s_mckout)
{
    uint32_t i2sdiv = 2U, i2sof = 0U;
    uint32_t clks = 0U;
    uint32_t i2sclock = 0U;
    uint32_t i2s_sel_div = 0U;
    uint32_t pll1s = 0U;
    
#ifdef FW_DEBUG_ERR_REPORT
    if(0U == i2s_audiosample) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0007U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* deinit SPI_I2SPSC register */
        SPI_I2SPSC(spi_periph) = SPI_I2SPSC_DEFAULT_VALUE;

        /* get the I2S clock source */
        if((spi_periph) == SPI1){
            /* I2S1 clock source selection */
            clks = I2S1_CLOCK_SEL;
        }else{
            /* I2S2 clock source selection */
            clks = I2S2_CLOCK_SEL;
        }
        
        /*get PLL1 clock source*/
        if(0U != (RCU_CFG1 & RCU_CFG1_PLL1SEL)){
            pll1s = IRC48M_VALUE; 
        }else{
            pll1s = HXTAL_VALUE;
        }
        
        if(0U != (RCU_CFG1 & clks)){
            /* get RCU PLL1 clock multiplication factor */
            clks = (uint32_t)((RCU_CFG1 & I2S_CLOCK_MUL_MASK) >> 8U);

            /* get the PREDV1 value */
            i2sclock = (uint32_t)(((RCU_CFG1 & I2S_CLOCK_DIV_MASK) >> 4U) + 1U);
            /* calculate i2sclock based on PLL1 and PREDV1 */
            i2sclock = (uint32_t)((pll1s / i2sclock) * clks); 
       
        }else{
            /* get system clock */
            i2sclock = rcu_clock_freq_get(CK_SYS);
        }
        
        /* get the i2sdiv value after i2ssel */
        if((spi_periph) == SPI1){
            /* I2S1 clock divide selection */
            i2s_sel_div = (uint32_t)(((RCU_ADDCTL & I2S1_CLOCK_DIV1_MASK) >> 3U) + 1U);
        }else{
            /* I2S2 clock divide selection */
            i2s_sel_div = (uint32_t)(((RCU_ADDCTL & I2S2_CLOCK_DIV1_MASK) >> 18U) + 1U);
        }

        /* calculate i2sclock*/
        i2sclock = (uint32_t)(i2sclock / i2s_sel_div);
        
        /* config the prescaler depending on the mclk output state, the frame format and audio sample rate */
        if(I2S_MCKOUT_ENABLE == i2s_mckout){
            clks = (uint32_t)(((i2sclock / 256U) * 10U) / i2s_audiosample);
        }else{
            if(I2S_FRAMEFORMAT_DT16B_CH16B == i2s_frameformat){
                clks = (uint32_t)(((i2sclock / 32U) *10U ) / i2s_audiosample);
            }else{
                clks = (uint32_t)(((i2sclock / 64U) *10U ) / i2s_audiosample);
            }
        }
        
        /* remove the floating point */
        clks   = (clks + 5U) / 10U;
        i2sof  = (clks & 0x00000001U);
        i2sdiv = ((clks - i2sof) / 2U);
        i2sof  = (i2sof << 8U);

        /* set the default values */
        if((i2sdiv < 2U) || (i2sdiv > 255U)){
            i2sdiv = 2U;
            i2sof = 0U;
        }

        /* configure SPI_I2SPSC */
        SPI_I2SPSC(spi_periph) = i2sdiv | i2sof | (i2s_mckout & SPI_I2SPSC_MCKOEN);

        /* clear SPI_I2SCTL_DTLEN and SPI_I2SCTL_CHLEN bits */
        SPI_I2SCTL(spi_periph) &= ~(SPI_I2SCTL_DTLEN | SPI_I2SCTL_CHLEN);
        /* configure data frame format */
        SPI_I2SCTL(spi_periph) |= (i2s_frameformat & (SPI_I2SCTL_DTLEN | SPI_I2SCTL_CHLEN));
    }
}

/*!
    \brief      enable I2S (API_ID: 0x0008U)
    \param[in]  spi_periph: SPIx(x=1,2)
    \param[out] none
    \retval     none
*/
void i2s_enable(uint32_t spi_periph)
{
    SPI_I2SCTL(spi_periph) |= SPI_I2SCTL_I2SEN;
}

/*!
    \brief      disable I2S (API_ID: 0x0009U)
    \param[in]  spi_periph: SPIx(x=1,2)
    \param[out] none
    \retval     none
*/
void i2s_disable(uint32_t spi_periph)
{
    SPI_I2SCTL(spi_periph) &= ~SPI_I2SCTL_I2SEN;
}

/*!
    \brief      enable SPI NSS output (API_ID: 0x000AU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_nss_output_enable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) |= SPI_CTL1_NSSDRV;
}

/*!
    \brief      disable SPI NSS output (API_ID: 0x000BU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_nss_output_disable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) &= ~SPI_CTL1_NSSDRV;
}

/*!
    \brief      SPI NSS pin high level in software mode (API_ID: 0x000CU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_nss_internal_high(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= SPI_CTL0_SWNSS;
}

/*!
    \brief      SPI NSS pin low level in software mode (API_ID: 0x000DU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_nss_internal_low(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) &= ~SPI_CTL0_SWNSS;
}

/*!
    \brief      enable SPI DMA send or receive (API_ID: 0x000EU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  dma: SPI DMA mode
                only one parameter can be selected which is shown as below:
      \arg        SPI_DMA_TRANSMIT: SPI transmit data use DMA
      \arg        SPI_DMA_RECEIVE: SPI receive data use DMA
    \param[out] none
    \retval     none
*/
void spi_dma_enable(uint32_t spi_periph, uint8_t dma)
{
    if(SPI_DMA_TRANSMIT == dma){
        SPI_CTL1(spi_periph) |= SPI_CTL1_DMATEN;
    }else{
        SPI_CTL1(spi_periph) |= SPI_CTL1_DMAREN;
    }
}

/*!
    \brief      disable SPI DMA send or receive (API_ID: 0x000FU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  dma: SPI DMA mode
                only one parameter can be selected which is shown as below:
      \arg        SPI_DMA_TRANSMIT: SPI transmit data use DMA
      \arg        SPI_DMA_RECEIVE: SPI receive data use DMA
    \param[out] none
    \retval     none
*/
void spi_dma_disable(uint32_t spi_periph, uint8_t dma)
{
    if(SPI_DMA_TRANSMIT == dma){
        SPI_CTL1(spi_periph) &= ~SPI_CTL1_DMATEN;
    }else{
        SPI_CTL1(spi_periph) &= ~SPI_CTL1_DMAREN;
    }
}

/*!
    \brief      configure SPI/I2S data frame format (API_ID: 0x0010U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  frame_format: SPI frame size
                only one parameter can be selected which is shown as below:
      \arg        SPI_FRAMESIZE_16BIT: SPI frame size is 16 bits
      \arg        SPI_FRAMESIZE_8BIT: SPI frame size is 8 bits
    \param[out] none
    \retval     none
*/
void spi_i2s_data_frame_format_config(uint32_t spi_periph, uint16_t frame_format)
{
    /* clear SPI_CTL0_FF16 bit */
    SPI_CTL0(spi_periph) &= ~SPI_CTL0_FF16;
    /* configure SPI_CTL0_FF16 bit */
    SPI_CTL0(spi_periph) |= (frame_format & SPI_CTL0_FF16);
}

/*!
    \brief      SPI transmit data (API_ID: 0x0011U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  data: 16-bit data
    \param[out] none
    \retval     none
*/
void spi_i2s_data_transmit(uint32_t spi_periph, uint16_t data)
{
    SPI_DATA(spi_periph) = (uint32_t)data;
}

/*!
    \brief      SPI receive data (API_ID: 0x0012U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     16-bit data
*/
uint16_t spi_i2s_data_receive(uint32_t spi_periph)
{
    return ((uint16_t)SPI_DATA(spi_periph));
}

/*!
    \brief      configure SPI bidirectional transfer direction (API_ID: 0x0013U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  transfer_direction: SPI transfer direction
                only one parameter can be selected which is shown as below:
      \arg        SPI_BIDIRECTIONAL_TRANSMIT: SPI work in transmit-only mode
      \arg        SPI_BIDIRECTIONAL_RECEIVE: SPI work in receive-only mode
    \param[out] none
    \retval     none
*/
void spi_bidirectional_transfer_config(uint32_t spi_periph, uint32_t transfer_direction)
{
    if(SPI_BIDIRECTIONAL_TRANSMIT == transfer_direction){
        /* set the transmit only mode */
        SPI_CTL0(spi_periph) |= SPI_BIDIRECTIONAL_TRANSMIT;
    }else{
        /* set the receive only mode */
        SPI_CTL0(spi_periph) &= SPI_BIDIRECTIONAL_RECEIVE;
    }
}

/*!
    \brief      clear SPI/I2S format error flag status (API_ID: 0x0014U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  flag: SPI/I2S frame format error flag 
      \arg        SPI_FLAG_FERR: only for SPI work in TI mode
      \arg        I2S_FLAG_FERR: for I2S
    \param[out] none
    \retval     none
*/
void spi_i2s_format_error_clear(uint32_t spi_periph, uint32_t flag)
{
    SPI_STAT(spi_periph) = ~(flag & SPI_FLAG_FERR);
}

/*!
    \brief      set SPI CRC polynomial (API_ID: 0x0015U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  crc_poly: CRC polynomial value
    \param[out] none
    \retval     none
*/
void spi_crc_polynomial_set(uint32_t spi_periph,uint16_t crc_poly)
{
    /* set SPI CRC polynomial */
    SPI_CRCPOLY(spi_periph) = (uint32_t)crc_poly;
}

/*!
    \brief      get SPI CRC polynomial (API_ID: 0x0016U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     16-bit CRC polynomial
*/
uint16_t spi_crc_polynomial_get(uint32_t spi_periph)
{
    return (uint16_t)SPI_CRCPOLY(spi_periph);
}

/*!
    \brief      turn on CRC function (API_ID: 0x0017U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_crc_on(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= SPI_CTL0_CRCEN;
}

/*!
    \brief      turn off CRC function (API_ID: 0x0018U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_crc_off(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) &= ~SPI_CTL0_CRCEN;
}

/*!
    \brief      SPI next data is CRC value (API_ID: 0x0019U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_crc_next(uint32_t spi_periph)
{
    SPI_CTL0(spi_periph) |= SPI_CTL0_CRCNT;
}

/*!
    \brief      get SPI CRC send value or receive value (API_ID: 0x001AU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  crc: SPI crc value
                only one parameter can be selected which is shown as below:
      \arg        SPI_CRC_TX: get transmit crc value
      \arg        SPI_CRC_RX: get receive crc value
    \param[out] none
    \retval     16-bit CRC value
*/

uint16_t spi_crc_get(uint32_t spi_periph, uint8_t crc)
{
    uint16_t reval;
    if(SPI_CRC_TX == crc){
        reval = ((uint16_t)(SPI_TCRC(spi_periph)));
    }else{
        reval = ((uint16_t)(SPI_RCRC(spi_periph)));
    }
    return reval;
}

/*!
    \brief      clear SPI CRC error flag status (API_ID: 0x001BU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_crc_error_clear(uint32_t spi_periph)
{
    SPI_STAT(spi_periph) = ~SPI_FLAG_CRCERR;
}

/*!
    \brief      enable SPI TI mode (API_ID: 0x001CU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_ti_mode_enable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) |= SPI_CTL1_TMOD;
}

/*!
    \brief      disable SPI TI mode (API_ID: 0x001DU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_ti_mode_disable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) &= ~SPI_CTL1_TMOD;
}

/*!
    \brief      enable SPI NSS pulse mode (API_ID: 0x001EU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_nssp_mode_enable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) |= SPI_CTL1_NSSP;
}

/*!
    \brief      disable SPI NSS pulse mode (API_ID: 0x001FU)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void spi_nssp_mode_disable(uint32_t spi_periph)
{
    SPI_CTL1(spi_periph) &= ~SPI_CTL1_NSSP;
}

/*!
    \brief      enable quad wire SPI (API_ID: 0x0020U)
    \param[in]  spi_periph: SPIx(only x=0)
    \param[out] none
    \retval     none
*/
void spi_quad_enable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) |= SPI_QCTL_QMOD;
}

/*!
    \brief      disable quad wire SPI (API_ID: 0x0021U)
    \param[in]  spi_periph: SPIx(only x=0)
    \param[out] none
    \retval     none
*/
void spi_quad_disable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) &= ~SPI_QCTL_QMOD;
}

/*!
    \brief      enable quad wire SPI write (API_ID: 0x0022U)
    \param[in]  spi_periph: SPIx(only x=0)
    \param[out] none
    \retval     none
*/
void spi_quad_write_enable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) &= ~SPI_QCTL_QRD;
}

/*!
    \brief      enable quad wire SPI read (API_ID: 0x0023U)
    \param[in]  spi_periph: SPIx(only x=0)
    \param[out] none
    \retval     none
*/
void spi_quad_read_enable(uint32_t spi_periph)
{
    SPI_QCTL(spi_periph) |= SPI_QCTL_QRD;
}

/*!
    \brief      get SPI and I2S flag status (API_ID: 0x0024U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  flag: SPI/I2S flag status
                only one parameter can be selected which is shown as below:
      \arg        SPI_FLAG_TBE: transmit buffer empty flag
      \arg        SPI_FLAG_RBNE: receive buffer not empty flag
      \arg        SPI_FLAG_TRANS: transmit on-going flag
      \arg        SPI_FLAG_RXORERR: receive overrun error flag
      \arg        SPI_FLAG_CONFERR: mode config error flag
      \arg        SPI_FLAG_CRCERR: CRC error flag
      \arg        SPI_FLAG_FERR: format error flag
      \arg        I2S_FLAG_TBE: transmit buffer empty flag
      \arg        I2S_FLAG_RBNE: receive buffer not empty flag
      \arg        I2S_FLAG_TRANS: transmit on-going flag
      \arg        I2S_FLAG_RXORERR: overrun error flag
      \arg        I2S_FLAG_TXURERR: underrun error flag
      \arg        I2S_FLAG_CH: channel side flag
      \arg        I2S_FLAG_FERR: format error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus spi_i2s_flag_get(uint32_t spi_periph, uint32_t flag)
{
    FlagStatus reval = RESET;

    if(RESET != (SPI_STAT(spi_periph) & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      enable SPI and I2S interrupt (API_ID: 0x0025U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  interrupt: SPI/I2S interrupt
                one or more parameters can be selected which is shown as below:
      \arg        SPI_I2S_INT_TBE: transmit buffer empty interrupt
      \arg        SPI_I2S_INT_RBNE: receive buffer not empty interrupt
      \arg        SPI_I2S_INT_ERR: CRC error,configuration error,reception overrun error,
                                   transmission underrun error and format error interrupt
    \param[out] none
    \retval     none
*/
void spi_i2s_interrupt_enable(uint32_t spi_periph, uint8_t interrupt)
{
    SPI_CTL1(spi_periph) |= (interrupt & (SPI_CTL1_TBEIE | SPI_CTL1_RBNEIE | SPI_CTL1_ERRIE));
}

/*!
    \brief      disable SPI and I2S interrupt (API_ID: 0x0026U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  interrupt: SPI/I2S interrupt
                one or more parameters can be selected which is shown as below:
      \arg        SPI_I2S_INT_TBE: transmit buffer empty interrupt
      \arg        SPI_I2S_INT_RBNE: receive buffer not empty interrupt
      \arg        SPI_I2S_INT_ERR: CRC error,configuration error,reception overrun error,
                                   transmission underrun error and format error interrupt
    \param[out] none
    \retval     none
*/
void spi_i2s_interrupt_disable(uint32_t spi_periph, uint8_t interrupt)
{
    SPI_CTL1(spi_periph) &= ~(interrupt & (SPI_CTL1_TBEIE | SPI_CTL1_RBNEIE | SPI_CTL1_ERRIE));
}

/*!
    \brief      get SPI and I2S interrupt flag status (API_ID: 0x0027U)
    \param[in]  spi_periph: SPIx(x=0,1,2)
    \param[in]  int_flag: SPI/I2S interrupt flag status
                only one parameter can be selected which is shown as below:
      \arg        SPI_I2S_INT_FLAG_TBE: transmit buffer empty interrupt flag
      \arg        SPI_I2S_INT_FLAG_RBNE: receive buffer not empty interrupt flag
      \arg        SPI_I2S_INT_FLAG_RXORERR: overrun interrupt flag
      \arg        SPI_INT_FLAG_CONFERR: config error interrupt flag
      \arg        SPI_INT_FLAG_CRCERR: CRC error interrupt flag
      \arg        I2S_INT_FLAG_TXURERR: underrun error interrupt flag
      \arg        SPI_I2S_INT_FLAG_FERR: format error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus spi_i2s_interrupt_flag_get(uint32_t spi_periph, spi_interrupt_flag_enum int_flag)
{
    FlagStatus reval = RESET;
    uint32_t ret1;
    uint32_t ret2;

    /* get the status of interrupt enable bit */
    ret1 = (SPI_CTL1(spi_periph) & BIT(SPI_BIT_POS(int_flag)));
    /* get the status of interrupt flag */
    ret2 = (SPI_STAT(spi_periph) & BIT(SPI_BIT_POS2(int_flag)));

    if ((RESET != ret1) && (RESET != ret2)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}
