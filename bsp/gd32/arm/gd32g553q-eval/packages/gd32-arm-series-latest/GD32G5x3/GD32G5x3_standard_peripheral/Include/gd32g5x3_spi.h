/*!
    \file    gd32g5x3_spi.h
    \brief   definitions for the SPI

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

#ifndef GD32G5X3_SPI_H
#define GD32G5X3_SPI_H

#include "gd32g5x3.h"

/* SPIx(x=0,1,2) definitions */
#define SPI0                            (SPI_BASE + 0x0000F800U)
#define SPI1                            SPI_BASE
#define SPI2                            (SPI_BASE + 0x00000400U)

/* SPI registers definitions */
#define SPI_CTL0(spix)                  REG32((spix) + 0x00000000U)             /*!< SPI control register 0 */
#define SPI_CTL1(spix)                  REG32((spix) + 0x00000004U)             /*!< SPI control register 1*/
#define SPI_STAT(spix)                  REG32((spix) + 0x00000008U)             /*!< SPI status register */
#define SPI_DATA(spix)                  REG32((spix) + 0x0000000CU)             /*!< SPI data register */
#define SPI_CRCPOLY(spix)               REG32((spix) + 0x00000010U)             /*!< SPI CRC polynomial register */
#define SPI_RCRC(spix)                  REG32((spix) + 0x00000014U)             /*!< SPI receive CRC register */
#define SPI_TCRC(spix)                  REG32((spix) + 0x00000018U)             /*!< SPI transmit CRC register */
#define SPI_QCTL(spix)                  REG32((spix) + 0x00000080U)             /*!< SPI quad mode control register(only SPI0) */

/* bits definitions */
/* SPI_CTL0 */
#define SPI_CTL0_CKPH                   BIT(0)                                  /*!< clock phase selection*/
#define SPI_CTL0_CKPL                   BIT(1)                                  /*!< clock polarity selection */
#define SPI_CTL0_MSTMOD                 BIT(2)                                  /*!< master mode enable */
#define SPI_CTL0_PSC                    BITS(3,5)                               /*!< master clock prescaler selection */
#define SPI_CTL0_SPIEN                  BIT(6)                                  /*!< SPI enable*/
#define SPI_CTL0_LF                     BIT(7)                                  /*!< LSB first mode */
#define SPI_CTL0_SWNSS                  BIT(8)                                  /*!< NSS pin selection in NSS software mode */
#define SPI_CTL0_SWNSSEN                BIT(9)                                  /*!< NSS software mode selection */
#define SPI_CTL0_RO                     BIT(10)                                 /*!< receive only */
#define SPI_CTL0_CRCL                   BIT(11)                                 /*!< CRC length */
#define SPI_CTL0_CRCNT                  BIT(12)                                 /*!< CRC next transfer */
#define SPI_CTL0_CRCEN                  BIT(13)                                 /*!< CRC calculation enable */
#define SPI_CTL0_BDOEN                  BIT(14)                                 /*!< bidirectional transmit output enable*/
#define SPI_CTL0_BDEN                   BIT(15)                                 /*!< bidirectional enable */

/* SPI_CTL1 */
#define SPI_CTL1_DMAREN                 BIT(0)                                  /*!< receive buffer dma enable */
#define SPI_CTL1_DMATEN                 BIT(1)                                  /*!< transmit buffer dma enable */
#define SPI_CTL1_NSSDRV                 BIT(2)                                  /*!< drive NSS output */
#define SPI_CTL1_NSSP                   BIT(3)                                  /*!< SPI NSS pulse mode enable */
#define SPI_CTL1_TMOD                   BIT(4)                                  /*!< SPI TI mode enable */
#define SPI_CTL1_ERRIE                  BIT(5)                                  /*!< errors interrupt enable */
#define SPI_CTL1_RBNEIE                 BIT(6)                                  /*!< receive buffer not empty interrupt enable */
#define SPI_CTL1_TBEIE                  BIT(7)                                  /*!< transmit buffer empty interrupt enable */
#define SPI_CTL1_DZ                     BITS(8,11)                              /*!< data size */
#define SPI_CTL1_BYTEN                  BIT(12)                                 /*!< Byte access enable */
#define SPI_CTL1_RXDMA_ODD              BIT(13)                                 /*!< Odd bytes in RX DMA channel */
#define SPI_CTL1_TXDMA_ODD              BIT(14)                                 /*!< Odd bytes in TX DMA channel */

/* SPI_STAT */
#define SPI_STAT_RBNE                   BIT(0)                                  /*!< receive buffer not empty */
#define SPI_STAT_TBE                    BIT(1)                                  /*!< transmit buffer empty */
#define SPI_STAT_CRCERR                 BIT(4)                                  /*!< SPI CRC error bit */
#define SPI_STAT_CONFERR                BIT(5)                                  /*!< SPI configuration error bit */
#define SPI_STAT_RXORERR                BIT(6)                                  /*!< SPI reception overrun error bit */
#define SPI_STAT_TRANS                  BIT(7)                                  /*!< transmitting on-going bit */
#define SPI_STAT_FERR                   BIT(8)                                  /*!< format error bit */
#define SPI_STAT_RXLVL                  BITS(9,10)                              /*!< RXFIFO level */
#define SPI_STAT_TXLVL                  BITS(11,12)                             /*!< TXFIFO level */

/* SPI_DATA */
#define SPI_DATA_DATA                   BITS(0,15)                              /*!< data transfer register */

/* SPI_CRCPOLY */
#define SPI_CRCPOLY_CPR                 BITS(0,15)                              /*!< CRC polynomial register */

/* SPI_RCRC */
#define SPI_RCRC_RCR                    BITS(0,15)                              /*!< RX CRC register */

/* SPI_TCRC */
#define SPI_TCRC_TCR                    BITS(0,15)                              /*!< TX CRC register */

/* SPI_QCTL(only for SPI0) */
#define SPI_QCTL_QMOD                   BIT(0)                                  /*!< quad-SPI mode enable */
#define SPI_QCTL_QRD                    BIT(1)                                  /*!< quad-SPI mode read select */
#define SPI_QCTL_IO23_DRV               BIT(2)                                  /*!< drive SPI_IO2 and SPI_IO3 enable */

/* constants definitions */
/* SPI parameter struct definitions */
typedef struct {
    uint32_t device_mode;                                                       /*!< SPI master or slave */
    uint32_t trans_mode;                                                        /*!< SPI transtype */
    uint32_t frame_size;                                                        /*!< SPI frame size */
    uint32_t nss;                                                               /*!< SPI NSS control by handware or software */
    uint32_t endian;                                                            /*!< SPI big endian or little endian */
    uint32_t clock_polarity_phase;                                              /*!< SPI clock phase and polarity */
    uint32_t prescale;                                                          /*!< SPI prescaler factor */
} spi_parameter_struct;

/* SPI mode definitions */
#define SPI_MASTER                      (SPI_CTL0_MSTMOD | SPI_CTL0_SWNSS)      /*!< SPI as master */
#define SPI_SLAVE                       ((uint32_t)0x00000000U)                 /*!< SPI as slave */

/* SPI bidirectional transfer direction */
#define SPI_BIDIRECTIONAL_TRANSMIT      SPI_CTL0_BDOEN                          /*!< SPI work in transmit-only mode */
#define SPI_BIDIRECTIONAL_RECEIVE       (~SPI_CTL0_BDOEN)                       /*!< SPI work in receive-only mode */

/* SPI transmit type */
#define SPI_TRANSMODE_FULLDUPLEX        ((uint32_t)0x00000000U)                 /*!< SPI receive and send data at fullduplex communication */
#define SPI_TRANSMODE_RECEIVEONLY       SPI_CTL0_RO                             /*!< SPI only receive data */
#define SPI_TRANSMODE_BDRECEIVE         SPI_CTL0_BDEN                           /*!< bidirectional receive data */
#define SPI_TRANSMODE_BDTRANSMIT        (SPI_CTL0_BDEN | SPI_CTL0_BDOEN)        /*!< bidirectional transmit data*/

/* SPI NSS control mode */
#define SPI_NSS_SOFT                    SPI_CTL0_SWNSSEN                        /*!< SPI NSS control by software */
#define SPI_NSS_HARD                    ((uint32_t)0x00000000U)                 /*!< SPI NSS control by hardware */

/* SPI transmit way */
#define SPI_ENDIAN_MSB                  ((uint32_t)0x00000000U)                 /*!< SPI transmit way is big endian: transmit MSB first */
#define SPI_ENDIAN_LSB                  SPI_CTL0_LF                             /*!< SPI transmit way is little endian: transmit LSB first */

/* SPI clock phase and polarity */
#define SPI_CK_PL_LOW_PH_1EDGE          ((uint32_t)0x00000000U)                 /*!< SPI clock polarity is low level and phase is first edge */
#define SPI_CK_PL_HIGH_PH_1EDGE         SPI_CTL0_CKPL                           /*!< SPI clock polarity is high level and phase is first edge */
#define SPI_CK_PL_LOW_PH_2EDGE          SPI_CTL0_CKPH                           /*!< SPI clock polarity is low level and phase is second edge */
#define SPI_CK_PL_HIGH_PH_2EDGE         (SPI_CTL0_CKPL | SPI_CTL0_CKPH)         /*!< SPI clock polarity is high level and phase is second edge */

/* SPI clock prescale factor */
#define CTL0_PSC(regval)                (BITS(3,5) & ((uint32_t)(regval) << 3))
#define SPI_PSC_2                       CTL0_PSC(0)                             /*!< SPI clock prescale factor is 2 */
#define SPI_PSC_4                       CTL0_PSC(1)                             /*!< SPI clock prescale factor is 4 */
#define SPI_PSC_8                       CTL0_PSC(2)                             /*!< SPI clock prescale factor is 8 */
#define SPI_PSC_16                      CTL0_PSC(3)                             /*!< SPI clock prescale factor is 16 */
#define SPI_PSC_32                      CTL0_PSC(4)                             /*!< SPI clock prescale factor is 32 */
#define SPI_PSC_64                      CTL0_PSC(5)                             /*!< SPI clock prescale factor is 64 */
#define SPI_PSC_128                     CTL0_PSC(6)                             /*!< SPI clock prescale factor is 128 */
#define SPI_PSC_256                     CTL0_PSC(7)                             /*!< SPI clock prescale factor is 256 */

/* SPIx frame size */
#define CTL1_FRAMESIZE(regval)          (BITS(8,11) & ((uint32_t)(regval) << 8))
#define SPI_FRAMESIZE_4BIT              CTL1_FRAMESIZE(3)                      /*!< SPI frame size is 4 bits */
#define SPI_FRAMESIZE_5BIT              CTL1_FRAMESIZE(4)                      /*!< SPI frame size is 5 bits */
#define SPI_FRAMESIZE_6BIT              CTL1_FRAMESIZE(5)                      /*!< SPI frame size is 6 bits */
#define SPI_FRAMESIZE_7BIT              CTL1_FRAMESIZE(6)                      /*!< SPI frame size is 7 bits */
#define SPI_FRAMESIZE_8BIT              CTL1_FRAMESIZE(7)                      /*!< SPI frame size is 8 bits */
#define SPI_FRAMESIZE_9BIT              CTL1_FRAMESIZE(8)                      /*!< SPI frame size is 9 bits */
#define SPI_FRAMESIZE_10BIT             CTL1_FRAMESIZE(9)                      /*!< SPI frame size is 10 bits */
#define SPI_FRAMESIZE_11BIT             CTL1_FRAMESIZE(10)                     /*!< SPI frame size is 11 bits */
#define SPI_FRAMESIZE_12BIT             CTL1_FRAMESIZE(11)                     /*!< SPI frame size is 12 bits */
#define SPI_FRAMESIZE_13BIT             CTL1_FRAMESIZE(12)                     /*!< SPI frame size is 13 bits */
#define SPI_FRAMESIZE_14BIT             CTL1_FRAMESIZE(13)                     /*!< SPI frame size is 14 bits */
#define SPI_FRAMESIZE_15BIT             CTL1_FRAMESIZE(14)                     /*!< SPI frame size is 15 bits */
#define SPI_FRAMESIZE_16BIT             CTL1_FRAMESIZE(15)                     /*!< SPI frame size is 16 bits */

/* SPIx CRC length(x=1) */
#define SPI_CRC_8BIT                    ((uint32_t)0x00000000U)                 /*!< SPI CRC length is 8 bits */
#define SPI_CRC_16BIT                   SPI_CTL0_CRCL                           /*!< SPI CRC length is 16 bits */

/* SPIx byte access enable(x=1) */
#define SPI_HALFWORD_ACCESS             ((uint32_t)0x00000000U)                 /*!< SPI half-word access to FIFO */
#define SPI_BYTE_ACCESS                 SPI_CTL1_BYTEN                          /*!< SPI byte access to FIFO */

/* SPIx odd bytes in TX DMA channel(x=1) */
#define SPI_TXDMA_EVEN                  ((uint32_t)0x00000000U)                 /*!< SPI number of byte in TX DMA channel is even */
#define SPI_TXDMA_ODD                   SPI_CTL1_TXDMA_ODD                      /*!< SPI number of byte in TX DMA channel is odd */

/* SPIx odd bytes in RX DMA channel(x=1) */
#define SPI_RXDMA_EVEN                  ((uint32_t)0x00000000U)                 /*!< SPI number of byte in RX DMA channel is even */
#define SPI_RXDMA_ODD                   SPI_CTL1_RXDMA_ODD                      /*!< SPI number of byte in RX DMA channel is odd */

/* SPIx TXFIFO level(x=1) */
#define STAT_TXLVL(regval)              (BITS(11,12) & ((uint32_t)(regval) << 11))
#define SPI_TXLVL_EMPTY                 STAT_TXLVL(0)                           /*!< SPI TXFIFO is empty */
#define SPI_TXLVL_QUARTER_FULL          STAT_TXLVL(1)                           /*!< SPI TXFIFO is a quarter of full */
#define SPI_TXLVL_HAlF_FULL             STAT_TXLVL(2)                           /*!< SPI TXFIFO is a half of full */
#define SPI_TXLVL_FULL                  STAT_TXLVL(3)                           /*!< SPI TXFIFO is full */

/* SPIx RXFIFO level(x=1) */
#define STAT_RXLVL(regval)              (BITS(9,10) & ((uint32_t)(regval) << 9))
#define SPI_RXLVL_EMPTY                 STAT_RXLVL(0)                           /*!< SPI RXFIFO is empty */
#define SPI_RXLVL_QUARTER_FULL          STAT_RXLVL(1)                           /*!< SPI RXFIFO is a quarter of full */
#define SPI_RXLVL_HAlF_FULL             STAT_RXLVL(2)                           /*!< SPI RXFIFO is a half of full */
#define SPI_RXLVL_FULL                  STAT_RXLVL(3)                           /*!< SPI RXFIFO is full */

/* SPI DMA constants definitions */
#define SPI_DMA_TRANSMIT                ((uint8_t)0x00U)                        /*!< SPI transmit data use DMA */
#define SPI_DMA_RECEIVE                 ((uint8_t)0x01U)                        /*!< SPI receive data use DMA */

/* SPI CRC constants definitions */
#define SPI_CRC_TX                      ((uint8_t)0x00U)                        /*!< SPI transmit CRC value */
#define SPI_CRC_RX                      ((uint8_t)0x01U)                        /*!< SPI receive CRC value */

/* SPI interrupt enable/disable constants definitions */
#define SPI_INT_TBE                     SPI_CTL1_TBEIE                          /*!< transmit buffer empty interrupt */
#define SPI_INT_RBNE                    SPI_CTL1_RBNEIE                         /*!< receive buffer not empty interrupt */
#define SPI_INT_ERR                     SPI_CTL1_ERRIE                          /*!< error interrupt */

/* SPI interrupt flag constants definitions */
#define SPI_INT_FLAG_TBE                ((uint8_t)0x00U)                        /*!< transmit buffer empty interrupt flag */
#define SPI_INT_FLAG_RBNE               ((uint8_t)0x01U)                        /*!< receive buffer not empty interrupt flag */
#define SPI_INT_FLAG_RXORERR            ((uint8_t)0x02U)                        /*!< overrun interrupt flag */
#define SPI_INT_FLAG_CONFERR            ((uint8_t)0x03U)                        /*!< config error interrupt flag */
#define SPI_INT_FLAG_CRCERR             ((uint8_t)0x04U)                        /*!< CRC error interrupt flag */
#define SPI_INT_FLAG_FERR               ((uint8_t)0x05U)                        /*!< format error interrupt flag */

/* SPI flag definitions */
#define SPI_FLAG_RBNE                   SPI_STAT_RBNE                           /*!< receive buffer not empty flag */
#define SPI_FLAG_TBE                    SPI_STAT_TBE                            /*!< transmit buffer empty flag */
#define SPI_FLAG_CRCERR                 SPI_STAT_CRCERR                         /*!< CRC error flag */
#define SPI_FLAG_CONFERR                SPI_STAT_CONFERR                        /*!< mode config error flag */
#define SPI_FLAG_RXORERR                SPI_STAT_RXORERR                        /*!< receive overrun error flag */
#define SPI_FLAG_TRANS                  SPI_STAT_TRANS                          /*!< transmit on-going flag */
#define SPI_FLAG_FERR                   SPI_STAT_FERR                           /*!< format error flag */

#define SPI_FLAG_TXLVL_EMPTY            SPI_TXLVL_EMPTY                         /*!< SPI TXFIFO is empty */
#define SPI_FLAG_TXLVL_QUARTER_FULL     SPI_TXLVL_QUARTER_FULL                  /*!< SPI TXFIFO is a quarter of full */
#define SPI_FLAG_TXLVL_HAlF_FULL        SPI_TXLVL_HAlF_FULL                     /*!< SPI TXFIFO is a half of full */
#define SPI_FLAG_TXLVL_FULL             SPI_TXLVL_FULL                          /*!< SPI TXFIFO is full */
#define SPI_FLAG_RXLVL_EMPTY            SPI_RXLVL_EMPTY                         /*!< SPI RXFIFO is empty */
#define SPI_FLAG_RXLVL_QUARTER_FULL     SPI_RXLVL_QUARTER_FULL                  /*!< SPI RXFIFO is a quarter of full */
#define SPI_FLAG_RXLVL_HAlF_FULL        SPI_RXLVL_HAlF_FULL                     /*!< SPI RXFIFO is a half of full */
#define SPI_FLAG_RXLVL_FULL             SPI_RXLVL_FULL                          /*!< SPI RXFIFO is full */

/* function declarations */
/* initialization functions */
/* reset SPI */
void spi_deinit(uint32_t spi_periph);
/* initialize the parameters of SPI struct with the default values */
void spi_struct_para_init(spi_parameter_struct *spi_struct);
/* initialize SPI parameter */
ErrStatus spi_init(uint32_t spi_periph, spi_parameter_struct *spi_struct);
/* enable SPI */
void spi_enable(uint32_t spi_periph);
/* disable SPI */
void spi_disable(uint32_t spi_periph);

/* NSS functions */
/* enable SPI NSS output */
void spi_nss_output_enable(uint32_t spi_periph);
/* disable SPI NSS output */
void spi_nss_output_disable(uint32_t spi_periph);
/* SPI NSS pin high level in software mode */
void spi_nss_internal_high(uint32_t spi_periph);
/* SPI NSS pin low level in software mode */
void spi_nss_internal_low(uint32_t spi_periph);

/* SPI DMA functions */
/* enable SPI DMA */
void spi_dma_enable(uint32_t spi_periph, uint8_t spi_dma);
/* disable SPI DMA */
void spi_dma_disable(uint32_t spi_periph, uint8_t spi_dma);
/* configure SPI total number of data transmitting by DMA is odd or not */
void spi_transmit_odd_config(uint32_t spi_periph, uint16_t odd);
/* configure SPI total number of data receiving by DMA is odd or not */
void spi_receive_odd_config(uint32_t spi_periph, uint16_t odd);

/* SPI transfer configure functions */
/* configure SPI data frame format */
ErrStatus spi_data_frame_format_config(uint32_t spi_periph, uint16_t frame_format);
/* configure SPI access size to FIFO(8-bit or 16-bit) */
void spi_fifo_access_size_config(uint32_t spi_periph, uint16_t fifo_access_size);
/* configure SPI bidirectional transfer direction */
void spi_bidirectional_transfer_config(uint32_t spi_periph, uint32_t transfer_direction);
/* SPI transmit data */
void spi_data_transmit(uint32_t spi_periph, uint16_t data);
/* SPI receive data */
uint16_t spi_data_receive(uint32_t spi_periph);

/* SPI CRC functions */
/* set SPI CRC polynomial */
void spi_crc_polynomial_set(uint32_t spi_periph, uint16_t crc_poly);
/* get SPI CRC polynomial */
uint16_t spi_crc_polynomial_get(uint32_t spi_periph);
/* set CRC length */
void spi_crc_length_set(uint32_t spi_periph, uint16_t crc_length);
/* turn on SPI CRC function */
void spi_crc_on(uint32_t spi_periph);
/* turn off SPI CRC function */
void spi_crc_off(uint32_t spi_periph);
/* SPI next data is CRC value */
void spi_crc_next(uint32_t spi_periph);
/* get SPI CRC send value or receive value */
uint16_t spi_crc_get(uint32_t spi_periph, uint8_t crc);
/* clear SPI CRC error flag status */
void spi_crc_error_clear(uint32_t spi_periph);

/* SPI TI mode functions */
/* enable SPI TI mode */
void spi_ti_mode_enable(uint32_t spi_periph);
/* disable SPI TI mode */
void spi_ti_mode_disable(uint32_t spi_periph);

/* SPI NSS pulse mode functions */
/* enable SPI NSS pulse mode */
void spi_nssp_mode_enable(uint32_t spi_periph);
/* disable SPI NSS pulse mode */
void spi_nssp_mode_disable(uint32_t spi_periph);

/* quad wire SPI functions */
/* enable quad wire SPI */
void spi_quad_enable(uint32_t spi_periph);
/* disable quad wire SPI */
void spi_quad_disable(uint32_t spi_periph);
/* enable quad wire SPI write */
void spi_quad_write_enable(uint32_t spi_periph);
/* enable quad wire SPI read */
void spi_quad_read_enable(uint32_t spi_periph);
/* enable quad wire SPI_IO2 and SPI_IO3 pin output */
void spi_quad_io23_output_enable(uint32_t spi_periph);
/* disable quad wire SPI_IO2 and SPI_IO3 pin output */
void spi_quad_io23_output_disable(uint32_t spi_periph);

/* flag and interrupt functions */
/* clear SPI format error flag status */
void spi_format_error_clear(uint32_t spi_periph, uint32_t flag);
/* get SPI flag status */
FlagStatus spi_flag_get(uint32_t spi_periph, uint32_t flag);
/* enable SPI interrupt */
void spi_interrupt_enable(uint32_t spi_periph, uint8_t interrupt);
/* disable SPI interrupt */
void spi_interrupt_disable(uint32_t spi_periph, uint8_t interrupt);
/* get SPI interrupt status */
FlagStatus spi_interrupt_flag_get(uint32_t spi_periph, uint8_t interrupt);

#endif /* GD32G5X3_SPI_H */
