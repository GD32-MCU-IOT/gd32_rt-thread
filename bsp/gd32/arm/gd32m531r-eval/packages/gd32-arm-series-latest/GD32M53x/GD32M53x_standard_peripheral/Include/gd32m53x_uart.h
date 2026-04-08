/*!
    \file    gd32m53x_uart.h
    \brief   UART driver

    \version 2026-03-04, V1.0.0, firmware for GD32M53x
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

#ifndef GD32M53X_UART_H
#define GD32M53X_UART_H

#include "gd32m53x.h"

/* UART definitions */
#define UART0                        UART_BASE                      /*!< UART0 base address */
#define UART1                       (UART_BASE+0x00000400U)         /*!< UART1 base address */
#define UART2                       (UART_BASE+0x00002C00U)         /*!< UART2 base address */
#define UART3                       (UART_BASE+0x00003000U)         /*!< UART3 base address */

/* registers definitions */
#define UART_STAT0(uartx)            REG32((uartx) + 0x00U)         /*!< UART status register 0 */
#define UART_DATA(uartx)             REG32((uartx) + 0x04U)         /*!< UART data register */
#define UART_BAUD(uartx)             REG32((uartx) + 0x08U)         /*!< UART baud rate register */
#define UART_CTL0(uartx)             REG32((uartx) + 0x0CU)         /*!< UART control register 0 */
#define UART_CTL1(uartx)             REG32((uartx) + 0x10U)         /*!< UART control register 1 */
#define UART_CTL2(uartx)             REG32((uartx) + 0x14U)         /*!< UART control register 2 */
#define UART_GP(uartx)               REG32((uartx) + 0x18U)         /*!< UART guard time and prescaler register */
#define UART_CHC(uartx)              REG32((uartx) + 0xC0U)         /*!< UART coherence control register */

/* bits definitions */
/* UARTx_STAT0 */
#define UART_STAT0_PERR              BIT(0)                         /*!< parity error flag */
#define UART_STAT0_FERR              BIT(1)                         /*!< frame error flag */
#define UART_STAT0_NERR              BIT(2)                         /*!< noise error flag */
#define UART_STAT0_ORERR             BIT(3)                         /*!< overrun error */
#define UART_STAT0_IDLEF             BIT(4)                         /*!< IDLE frame detected flag */
#define UART_STAT0_RBNE              BIT(5)                         /*!< read data buffer not empty */
#define UART_STAT0_TC                BIT(6)                         /*!< transmission complete */
#define UART_STAT0_TBE               BIT(7)                         /*!< transmit data buffer empty */
#define UART_STAT0_LBDF              BIT(8)                         /*!< LIN break detected flag */

/* UARTx_DATA */
#define UART_DATA_DATA               BITS(0,9)                      /*!< transmit or read data value */

/* UARTx_BAUD */
#define UART_BAUD_FRADIV             BITS(0,3)                      /*!< fraction part of baud-rate divider */
#define UART_BAUD_INTDIV             BITS(4,19)                     /*!< integer part of baud-rate divider */

/* UARTx_CTL0 */
#define UART_CTL0_SBKCMD             BIT(0)                         /*!< send break command */
#define UART_CTL0_RWU                BIT(1)                         /*!< receiver wakeup from mute mode */
#define UART_CTL0_REN                BIT(2)                         /*!< enable receiver */
#define UART_CTL0_TEN                BIT(3)                         /*!< enable transmitter */
#define UART_CTL0_IDLEIE             BIT(4)                         /*!< enable idle line detected interrupt */
#define UART_CTL0_RBNEIE             BIT(5)                         /*!< enable read data buffer not empty interrupt and overrun error interrupt */
#define UART_CTL0_TCIE               BIT(6)                         /*!< enable transmission complete interrupt */
#define UART_CTL0_TBEIE              BIT(7)                         /*!< enable transmitter buffer empty interrupt */
#define UART_CTL0_PERRIE             BIT(8)                         /*!< enable parity error interrupt */
#define UART_CTL0_PM                 BIT(9)                         /*!< parity mode */
#define UART_CTL0_PCEN               BIT(10)                        /*!< enable parity check function */
#define UART_CTL0_WM                 BIT(11)                        /*!< wakeup method in mute mode */
#define UART_CTL0_WL0                BIT(12)                        /*!< word length bit 0*/
#define UART_CTL0_MEN                BIT(13)                        /*!< mute mode enable */
#define UART_CTL0_UEN                BIT(14)                        /*!< enable UART */
#define UART_CTL0_OVSMOD             BIT(15)                        /*!< oversample mode */
#define UART_CTL0_WL1                BIT(28)                        /*!< word length bit 1*/

/* UARTx_CTL1 */
#define UART_CTL1_ADDR               BITS(0,3)                      /*!< address of UART */
#define UART_CTL1_LBLEN              BIT(5)                         /*!< LIN break frame length */
#define UART_CTL1_LBDIE              BIT(6)                         /*!< enable LIN break detected interrupt */
#define UART_CTL1_STB                BITS(12,13)                    /*!< STOP bits length */
#define UART_CTL1_LMEN               BIT(14)                        /*!< enable LIN mode */

/* UARTx_CTL2 */
#define UART_CTL2_ERRIE              BIT(0)                         /*!< enable error interrupt */
#define UART_CTL2_IREN               BIT(1)                         /*!< enable IrDA mode */
#define UART_CTL2_IRLP               BIT(2)                         /*!< IrDA low-power */
#define UART_CTL2_HDEN               BIT(3)                         /*!< enable half-duplex */
#define UART_CTL2_DENR               BIT(6)                         /*!< enable DMA request for reception */
#define UART_CTL2_DENT               BIT(7)                         /*!< enable DMA request for transmission */
#define UART_CTL2_OSB                BIT(11)                        /*!< one sample bit method */
#define UART_CTL2_RINV               BIT(12)                        /*!< RX pin level inversion */
#define UART_CTL2_TINV               BIT(13)                        /*!< TX pin level inversion */
#define UART_CTL2_DINV               BIT(14)                        /*!< data bit level inversion */
#define UART_CTL2_MSBF               BIT(15)                        /*!< most significant bit first */

/* UARTx_GP */
#define UART_GP_PSC                  BITS(0,7)                      /*!< prescaler value for dividing the system clock */

/* UARTx_CHC */
#define UART_CHC_PCM                 BIT(1)                         /*!< parity check coherence mode */
#define UART_CHC_EPERR               BIT(8)                         /*!< early parity error flag */

/* constants definitions */
/* define the UART bit position and its register index offset */
#define UART_REGIDX_BIT(regidx, bitpos)    (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define UART_REG_VAL(uartx, offset)       (REG32((uartx) + (((uint32_t)(offset) & 0xFFFFU) >> 6)))
#define UART_BIT_POS(val)                  ((uint32_t)(val) & 0x1FU)
#define UART_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                              | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define UART_REG_VAL2(uartx, offset)      (REG32((uartx) + ((uint32_t)(offset) >> 22)))
#define UART_BIT_POS2(val)                 (((uint32_t)(val) & 0x1F0000U) >> 16)

/* register offset */
#define UART_STAT0_REG_OFFSET              0x00U                       /*!< STAT0 register offset */
#define UART_CTL0_REG_OFFSET               0x0CU                       /*!< CTL0 register offset */
#define UART_CTL1_REG_OFFSET               0x10U                       /*!< CTL1 register offset */
#define UART_CTL2_REG_OFFSET               0x14U                       /*!< CTL2 register offset */
#define UART_CHC_REG_OFFSET                0xC0U                       /*!< CHC register offset */

/* UART flags */
typedef enum {
    /* flags in STAT0 register */
    UART_FLAG_LBD = UART_REGIDX_BIT(UART_STAT0_REG_OFFSET, 8U),      /*!< LIN break detected flag */
    UART_FLAG_TBE = UART_REGIDX_BIT(UART_STAT0_REG_OFFSET, 7U),      /*!< transmit data buffer empty */
    UART_FLAG_TC = UART_REGIDX_BIT(UART_STAT0_REG_OFFSET, 6U),       /*!< transmission complete */
    UART_FLAG_RBNE = UART_REGIDX_BIT(UART_STAT0_REG_OFFSET, 5U),     /*!< read data buffer not empty */
    UART_FLAG_IDLE = UART_REGIDX_BIT(UART_STAT0_REG_OFFSET, 4U),     /*!< IDLE frame detected flag */
    UART_FLAG_ORERR = UART_REGIDX_BIT(UART_STAT0_REG_OFFSET, 3U),    /*!< overrun error */
    UART_FLAG_NERR = UART_REGIDX_BIT(UART_STAT0_REG_OFFSET, 2U),     /*!< noise error flag */
    UART_FLAG_FERR = UART_REGIDX_BIT(UART_STAT0_REG_OFFSET, 1U),     /*!< frame error flag */
    UART_FLAG_PERR = UART_REGIDX_BIT(UART_STAT0_REG_OFFSET, 0U),     /*!< parity error flag */
    /* flags in CHC register */
    UART_FLAG_EPERR = UART_REGIDX_BIT(UART_CHC_REG_OFFSET, 8U),      /*!< early parity error flag */
} uart_flag_enum;

/* UART interrupt flags */
typedef enum {
    /* interrupt flags in CTL0 register */
    UART_INT_FLAG_PERR = UART_REGIDX_BIT2(UART_CTL0_REG_OFFSET, 8U, UART_STAT0_REG_OFFSET, 0U),       /*!< parity error interrupt and flag */
    UART_INT_FLAG_TBE = UART_REGIDX_BIT2(UART_CTL0_REG_OFFSET, 7U, UART_STAT0_REG_OFFSET, 7U),        /*!< transmitter buffer empty interrupt and flag */
    UART_INT_FLAG_TC = UART_REGIDX_BIT2(UART_CTL0_REG_OFFSET, 6U, UART_STAT0_REG_OFFSET, 6U),         /*!< transmission complete interrupt and flag */
    UART_INT_FLAG_RBNE = UART_REGIDX_BIT2(UART_CTL0_REG_OFFSET, 5U, UART_STAT0_REG_OFFSET, 5U),       /*!< read data buffer not empty interrupt and flag */
    UART_INT_FLAG_RBNE_ORERR = UART_REGIDX_BIT2(UART_CTL0_REG_OFFSET, 5U, UART_STAT0_REG_OFFSET, 3U), /*!< read data buffer not empty interrupt and overrun error flag */
    UART_INT_FLAG_IDLE = UART_REGIDX_BIT2(UART_CTL0_REG_OFFSET, 4U, UART_STAT0_REG_OFFSET, 4U),       /*!< IDLE line detected interrupt and flag */
    /* interrupt flags in CTL1 register */
    UART_INT_FLAG_LBD = UART_REGIDX_BIT2(UART_CTL1_REG_OFFSET, 6U, UART_STAT0_REG_OFFSET, 8U),        /*!< LIN break detected interrupt and flag */
    /* interrupt flags in CTL2 register */
    UART_INT_FLAG_ERR_ORERR = UART_REGIDX_BIT2(UART_CTL2_REG_OFFSET, 0U, UART_STAT0_REG_OFFSET, 3U),  /*!< error interrupt and overrun error */
    UART_INT_FLAG_ERR_NERR = UART_REGIDX_BIT2(UART_CTL2_REG_OFFSET, 0U, UART_STAT0_REG_OFFSET, 2U),   /*!< error interrupt and noise error flag */
    UART_INT_FLAG_ERR_FERR = UART_REGIDX_BIT2(UART_CTL2_REG_OFFSET, 0U, UART_STAT0_REG_OFFSET, 1U),   /*!< error interrupt and frame error flag */
} uart_interrupt_flag_enum;

/* UART interrupt enable or disable */
typedef enum {
    /* interrupt in CTL0 register */
    UART_INT_PERR = UART_REGIDX_BIT(UART_CTL0_REG_OFFSET, 8U),      /*!< parity error interrupt */
    UART_INT_TBE = UART_REGIDX_BIT(UART_CTL0_REG_OFFSET, 7U),       /*!< transmitter buffer empty interrupt */
    UART_INT_TC = UART_REGIDX_BIT(UART_CTL0_REG_OFFSET, 6U),        /*!< transmission complete interrupt */
    UART_INT_RBNE = UART_REGIDX_BIT(UART_CTL0_REG_OFFSET, 5U),      /*!< read data buffer not empty interrupt and overrun error interrupt */
    UART_INT_IDLE = UART_REGIDX_BIT(UART_CTL0_REG_OFFSET, 4U),      /*!< IDLE line detected interrupt */
    /* interrupt in CTL1 register */
    UART_INT_LBD = UART_REGIDX_BIT(UART_CTL1_REG_OFFSET, 6U),       /*!< LIN break detected interrupt */
    /* interrupt in CTL2 register */
    UART_INT_ERR = UART_REGIDX_BIT(UART_CTL2_REG_OFFSET, 0U),       /*!< error interrupt */
} uart_interrupt_enum;

/* configure UART invert */
typedef enum {
    /* data bit level inversion */
    UART_DINV_ENABLE,                             /*!< data bit level inversion */
    UART_DINV_DISABLE,                            /*!< data bit level not inversion */
    /* TX pin level inversion */
    UART_TXPIN_ENABLE,                            /*!< TX pin level inversion */
    UART_TXPIN_DISABLE,                           /*!< TX pin level not inversion */
    /* RX pin level inversion */
    UART_RXPIN_ENABLE,                            /*!< RX pin level inversion */
    UART_RXPIN_DISABLE,                           /*!< RX pin level not inversion */
} uart_invert_enum;

/* configure UART receiver */
#define CTL0_REN(regval)              (BIT(2) & ((uint32_t)(regval) << 2))
#define UART_RECEIVE_ENABLE           CTL0_REN(1)                      /*!< enable receiver */
#define UART_RECEIVE_DISABLE          CTL0_REN(0)                      /*!< disable receiver */

/* configure UART transmitter */
#define CTL0_TEN(regval)              (BIT(3) & ((uint32_t)(regval) << 3))
#define UART_TRANSMIT_ENABLE          CTL0_TEN(1)                      /*!< enable transmitter */
#define UART_TRANSMIT_DISABLE         CTL0_TEN(0)                      /*!< disable transmitter */

/* UART parity bits definitions */
#define CTL0_PM(regval)               (BITS(9,10) & ((uint32_t)(regval) << 9))
#define UART_PM_NONE                  CTL0_PM(0)                       /*!< no parity */
#define UART_PM_EVEN                  CTL0_PM(2)                       /*!< even parity */
#define UART_PM_ODD                   CTL0_PM(3)                       /*!< odd parity */

/* UART wakeup method in mute mode */
#define CTL0_WM(regval)               (BIT(11) & ((uint32_t)(regval) << 11))
#define UART_WM_IDLE                  CTL0_WM(0)                       /*!< idle Line */
#define UART_WM_ADDR                  CTL0_WM(1)                       /*!< address mask */

/* UART word length definitions */
#define UART_WL_8BIT                  0x00000000U                      /*!< 8 bits */
#define UART_WL_9BIT                  0x00001000U                      /*!< 9 bits */
#define UART_WL_7BIT                  0x10000000U                      /*!< 7 bits */
#define UART_WL_10BIT                 0x10001000U                      /*!< 10 bits */

/* UART oversampling mode definitions */
#define CTL0_OVSMOD(regval)           (BIT(15) & ((uint32_t)(regval) << 15))
#define UART_OVSMOD_16                CTL0_OVSMOD(0)                   /*!< 16 bits */
#define UART_OVSMOD_8                 CTL0_OVSMOD(1)                   /*!< 8 bits */

/* UART stop bits definitions */
#define CTL1_STB(regval)              (BITS(12,13) & ((uint32_t)(regval) << 12))
#define UART_STB_1BIT                 CTL1_STB(0)                      /*!< 1 bit */
#define UART_STB_2BIT                 CTL1_STB(2)                      /*!< 2 bits */

/* UART LIN break frame length */
#define CTL1_LBLEN(regval)            (BIT(5) & ((uint32_t)(regval) << 5))
#define UART_LBLEN_10B                CTL1_LBLEN(0)                    /*!< 10 bits */
#define UART_LBLEN_11B                CTL1_LBLEN(1)                    /*!< 11 bits */

/* configure UART DMA request for receive */
#define CLT2_DENR(regval)             (BIT(6) & ((uint32_t)(regval) << 6))
#define UART_RECEIVE_DMA_ENABLE       CLT2_DENR(1)                     /*!< DMA request enable for reception */
#define UART_RECEIVE_DMA_DISABLE      CLT2_DENR(0)                     /*!< DMA request disable for reception */

/* configure UART DMA request for transmission */
#define CLT2_DENT(regval)             (BIT(7) & ((uint32_t)(regval) << 7))
#define UART_TRANSMIT_DMA_ENABLE      CLT2_DENT(1)                     /*!< DMA request enable for transmission */
#define UART_TRANSMIT_DMA_DISABLE     CLT2_DENT(0)                     /*!< DMA request disable for transmission */

/* configure UART one sample bit method */
#define CTL2_OSB(regval)              (BIT(11) & ((uint32_t)(regval) << 11))
#define UART_OSB_1bit                 CTL2_OSB(1)                      /*!< 1 bit */
#define UART_OSB_3bit                 CTL2_OSB(0)                      /*!< 3 bits */

/* enable UART IrDA low-power */
#define CTL2_IRLP(regval)             (BIT(2) & ((uint32_t)(regval) << 2))
#define UART_IRLP_LOW                 CTL2_IRLP(1)                     /*!< low-power */
#define UART_IRLP_NORMAL              CTL2_IRLP(0)                     /*!< normal */

/* UART data is transmitted/received with the LSB/MSB first */
#define CTL2_MSBF(regval)             (BIT(15) & ((uint32_t)(regval) << 15))
#define UART_MSBF_LSB                 CTL2_MSBF(0)                     /*!< LSB first */
#define UART_MSBF_MSB                 CTL2_MSBF(1)                     /*!< MSB first */

/* UART parity check coherence mode */
#define CHC_PCM(regval)               (BIT(1) & ((uint32_t)(regval) << 1))
#define UART_PCM_NONE                 CHC_PCM(0)                       /*!< not check parity */
#define UART_PCM_EN                   CHC_PCM(1)                       /*!< check the parity */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check USART baud rate */
#define NOT_UART_BAUDRATE(baudval)   ((baudval) == 0U)
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* initialization functions */
/* reset UART */
void uart_deinit(uint32_t uart_periph);
/* configure uart baud rate value */
void uart_baudrate_set(uint32_t uart_periph, uint32_t baudval);
/* configure uart parity function */
void uart_parity_config(uint32_t uart_periph, uint32_t paritycfg);
/* configure uart word length */
void uart_word_length_set(uint32_t uart_periph, uint32_t wlen);
/* configure uart stop bit length */
void uart_stop_bit_set(uint32_t uart_periph, uint32_t stblen);
/* enable uart */
void uart_enable(uint32_t uart_periph);
/* disable uart */
void uart_disable(uint32_t uart_periph);
/* configure UART transmitter */
void uart_transmit_config(uint32_t uart_periph, uint32_t txconfig);
/* configure UART receiver */
void uart_receive_config(uint32_t uart_periph, uint32_t rxconfig);

/* UART normal mode communication */
/* data is transmitted/received with the LSB/MSB first */
void uart_data_first_config(uint32_t uart_periph, uint32_t msbf);
/* configure UART inverted */
void uart_invert_config(uint32_t uart_periph, uart_invert_enum invertpara);
/* configure the UART oversample mode */
void uart_oversample_config(uint32_t uart_periph, uint32_t oversamp);
/* configure sample bit method */
void uart_sample_bit_config(uint32_t uart_periph, uint32_t osb);
/* UART transmit data function */
void uart_data_transmit(uint32_t uart_periph, uint32_t data);
/* UART receive data function */
uint16_t uart_data_receive(uint32_t uart_periph);

/* multi-processor communication */
/* configure address of the UART */
void uart_address_config(uint32_t uart_periph, uint8_t addr);
/* enable mute mode */
void uart_mute_mode_enable(uint32_t uart_periph);
/* disable mute mode */
void uart_mute_mode_disable(uint32_t uart_periph);
/* configure wakeup method in mute mode */
void uart_mute_mode_wakeup_config(uint32_t uart_periph, uint32_t wmethod);

/* LIN mode communication */
/* enable LIN mode */
void uart_lin_mode_enable(uint32_t uart_periph);
/* disable LIN mode */
void uart_lin_mode_disable(uint32_t uart_periph);
/* LIN break detection length */
void uart_lin_break_detection_length_config(uint32_t uart_periph, uint32_t lblen);
/* send break frame */
void uart_send_break(uint32_t uart_periph);

/* half-duplex communication */
/* enable half-duplex mode */
void uart_halfduplex_enable(uint32_t uart_periph);
/* disable half-duplex mode */
void uart_halfduplex_disable(uint32_t uart_periph);

/* IrDA communication */
/* enable IrDA mode */
void uart_irda_mode_enable(uint32_t uart_periph);
/* disable IrDA mode */
void uart_irda_mode_disable(uint32_t uart_periph);
/* configure the peripheral clock prescaler */
void uart_prescaler_config(uint32_t uart_periph, uint8_t psc);
/* configure IrDA low-power */
void uart_irda_lowpower_config(uint32_t uart_periph, uint32_t irlp);

/* coherence control */
/* configure parity check coherence mode */
void uart_parity_check_coherence_config(uint32_t uart_periph, uint32_t pcm);

/* DMA communication */
/* configure UART DMA for reception */
void uart_dma_receive_config(uint32_t uart_periph, uint32_t dmacmd);
/* configure UART DMA for transmission */
void uart_dma_transmit_config(uint32_t uart_periph, uint32_t dmacmd);

/* flag & interrupt functions */
/* get flag in STAT0/STAT1 register */
FlagStatus uart_flag_get(uint32_t uart_periph, uart_flag_enum flag);
/* clear flag in STAT0/STAT1 register */
void uart_flag_clear(uint32_t uart_periph, uart_flag_enum flag);
/* enable UART interrupt */
void uart_interrupt_enable(uint32_t uart_periph, uart_interrupt_enum interrupt);
/* disable UART interrupt */
void uart_interrupt_disable(uint32_t uart_periph, uart_interrupt_enum interrupt);
/* get UART interrupt and flag status */
FlagStatus uart_interrupt_flag_get(uint32_t uart_periph, uart_interrupt_flag_enum int_flag);
/* clear interrupt flag in STAT0/STAT1 register */
void uart_interrupt_flag_clear(uint32_t uart_periph, uart_interrupt_flag_enum int_flag);

#endif /* GD32M53X_UART_H */
