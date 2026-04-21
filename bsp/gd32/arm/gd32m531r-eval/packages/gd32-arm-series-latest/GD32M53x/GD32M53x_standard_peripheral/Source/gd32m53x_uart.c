/*!
    \file    gd32m53x_uart.c
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

#include "gd32m53x_uart.h"

/*!
    \brief      reset UART (API_ID(0x0001U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_deinit(uint32_t uart_periph)
{
    switch(uart_periph) {
    case UART0:
        rcu_periph_reset_enable(RCU_UART0RST);
        rcu_periph_reset_disable(RCU_UART0RST);
        break;
    case UART1:
        rcu_periph_reset_enable(RCU_UART1RST);
        rcu_periph_reset_disable(RCU_UART1RST);
        break;
    case UART2:
        rcu_periph_reset_enable(RCU_UART2RST);
        rcu_periph_reset_disable(RCU_UART2RST);
        break;
    case UART3:
        rcu_periph_reset_enable(RCU_UART3RST);
        rcu_periph_reset_disable(RCU_UART3RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure UART baud rate value (API_ID(0x0002U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  baudval: baud rate value
    \param[out] none
    \retval     none
*/
void uart_baudrate_set(uint32_t uart_periph, uint32_t baudval)
{
    uint32_t uclk = 0U, intdiv, fradiv, udiv;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_UART_BAUDRATE(baudval)) {
        fw_debug_report_err(UART_MODULE_ID, API_ID(0x0002U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        switch(uart_periph) {
        /* get clock frequency */
        case UART0:
            uclk = rcu_clock_freq_get(CK_APB1);
            break;
        case UART1:
            uclk = rcu_clock_freq_get(CK_APB1);
            break;
        case UART2:
            uclk = rcu_clock_freq_get(CK_APB1);
            break;
        case UART3:
            uclk = rcu_clock_freq_get(CK_APB1);
            break;
        default:
            break;
        }
        if(UART_OVSMOD_8 == (UART_CTL0(uart_periph) & UART_CTL0_OVSMOD)) {
            /* when oversampling by 8, configure the value of UART_BAUD */
            udiv = ((2U * uclk) + (baudval / 2U)) / baudval;
            intdiv = udiv & 0x000ffff0U;
            fradiv = (udiv >> 1U) & 0x00000007U;
            UART_BAUD(uart_periph) = ((UART_BAUD_FRADIV | UART_BAUD_INTDIV) & (intdiv | fradiv));
        } else {
            /* when oversampling by 16, configure the value of UART_BAUD */
            udiv = (uclk + (baudval / 2U)) / baudval;
            intdiv = udiv & 0x000ffff0U;
            fradiv = udiv & 0x0000000fU;
            UART_BAUD(uart_periph) = ((UART_BAUD_FRADIV | UART_BAUD_INTDIV) & (intdiv | fradiv));
        }
    }
}

/*!
    \brief     configure UART parity function (API_ID(0x0003))
    \param[in] uart_periph: UARTx(x = 0,1,2,3)
    \param[in] paritycfg: configure UART parity
               only one parameter can be selected which is shown as below:
      \arg       UART_PM_NONE: no parity
      \arg       UART_PM_EVEN: even parity
      \arg       UART_PM_ODD:  odd parity
    \param[out] none
    \retval     none
*/
void uart_parity_config(uint32_t uart_periph, uint32_t paritycfg)
{
    /* clear UART_CTL0 PM,PCEN Bits */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_PM | UART_CTL0_PCEN);
    /* configure UART parity mode */
    UART_CTL0(uart_periph) |= paritycfg & (UART_CTL0_PM | UART_CTL0_PCEN);
}

/*!
    \brief     configure UART word length (API_ID(0x0004U))
    \param[in] uart_periph: UARTx(x = 0,1,2,3)
    \param[in] wlen: UART word length configure
               only one parameter can be selected which is shown as below:
      \arg       UART_WL_8BIT: 8 bits
      \arg       UART_WL_9BIT: 9 bits
      \arg       UART_WL_7BIT: 7 bits
      \arg       UART_WL_10BIT: 10 bits
    \param[out] none
    \retval     none
*/
void uart_word_length_set(uint32_t uart_periph, uint32_t wlen)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    /* clear UART_CTL0 WL bit */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_WL0 | UART_CTL0_WL1);
    /* configure UART word length */
    UART_CTL0(uart_periph) |= wlen & (UART_CTL0_WL0 | UART_CTL0_WL1);

}

/*!
    \brief     configure UART stop bit length (API_ID(0x0005U))
    \param[in] uart_periph: UARTx(x = 0,1,2,3)
    \param[in] stblen: UART stop bit configure
               only one parameter can be selected which is shown as below:
      \arg       UART_STB_1BIT: 1 bit
      \arg       UART_STB_2BIT: 2 bits
    \param[out] none
    \retval     none
*/
void uart_stop_bit_set(uint32_t uart_periph, uint32_t stblen)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    /* clear UART_CTL1 STB bits */
    UART_CTL1(uart_periph) &= ~UART_CTL1_STB;
    /* configure UART stop bits */
    UART_CTL1(uart_periph) |= stblen & UART_CTL1_STB;
}
/*!
    \brief    enable UART (API_ID(0x0006U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_enable(uint32_t uart_periph)
{
    UART_CTL0(uart_periph) |= UART_CTL0_UEN;
}

/*!
    \brief      disable UART (API_ID(0x0007U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_disable(uint32_t uart_periph)
{
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
}

/*!
    \brief    configure UART transmitter (API_ID(0x0008U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  txconfig: enable or disable UART transmitter
                only one parameter can be selected which is shown as below:
      \arg        UART_TRANSMIT_ENABLE: enable UART transmission
      \arg        UART_TRANSMIT_DISABLE: disable UART transmission
    \param[out] none
    \retval     none
*/
void uart_transmit_config(uint32_t uart_periph, uint32_t txconfig)
{
    /* disable transmitter */
    UART_CTL0(uart_periph) &= ~UART_CTL0_TEN;
    /* configure transfer mode */
    UART_CTL0(uart_periph) |= txconfig & UART_CTL0_TEN;
}

/*!
    \brief    configure UART receiver (API_ID(0x0009U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  rxconfig: enable or disable UART receiver
                only one parameter can be selected which is shown as below:
      \arg        UART_RECEIVE_ENABLE: enable UART reception
      \arg        UART_RECEIVE_DISABLE: disable UART reception
    \param[out] none
    \retval     none
*/
void uart_receive_config(uint32_t uart_periph, uint32_t rxconfig)
{
    /* disable receiver */
    UART_CTL0(uart_periph) &= ~UART_CTL0_REN;
    /* configure receiver mode */
    UART_CTL0(uart_periph) |= rxconfig & UART_CTL0_REN;
}

/*!
    \brief    data is transmitted/received with the LSB/MSB first (API_ID(0x000AU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  msbf: LSB/MSB
                only one parameter can be selected which is shown as below:
      \arg        UART_MSBF_LSB: LSB first
      \arg        UART_MSBF_MSB: MSB first
    \param[out] none
    \retval     none
*/
void uart_data_first_config(uint32_t uart_periph, uint32_t msbf)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    /* configure LSB or MSB first */
    UART_CTL2(uart_periph) &= ~(UART_CTL2_MSBF);
    UART_CTL2(uart_periph) |= (UART_CTL2_MSBF & msbf);
}

/*!
    \brief    configure UART inversion (API_ID(0x000BU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  invertpara: refer to enum UART_INVERT_CONFIG
                only one parameter can be selected which is shown as below:
      \arg        UART_DINV_ENABLE: data bit level inversion
      \arg        UART_DINV_DISABLE: data bit level not inversion
      \arg        UART_TXPIN_ENABLE: TX pin level inversion
      \arg        UART_TXPIN_DISABLE: TX pin level not inversion
      \arg        UART_RXPIN_ENABLE: RX pin level inversion
      \arg        UART_RXPIN_DISABLE: RX pin level not inversion
    \param[out] none
    \retval     none
*/
void uart_invert_config(uint32_t uart_periph, uart_invert_enum invertpara)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    /* inverted or not the specified signal */
    switch(invertpara) {
    case UART_DINV_ENABLE:
        UART_CTL2(uart_periph) |= UART_CTL2_DINV;
        break;
    case UART_TXPIN_ENABLE:
        UART_CTL2(uart_periph) |= UART_CTL2_TINV;
        break;
    case UART_RXPIN_ENABLE:
        UART_CTL2(uart_periph) |= UART_CTL2_RINV;
        break;
    case UART_DINV_DISABLE:
        UART_CTL2(uart_periph) &= ~(UART_CTL2_DINV);
        break;
    case UART_TXPIN_DISABLE:
        UART_CTL2(uart_periph) &= ~(UART_CTL2_TINV);
        break;
    case UART_RXPIN_DISABLE:
        UART_CTL2(uart_periph) &= ~(UART_CTL2_RINV);
        break;
    default:
        break;
    }
}

/*!
    \brief    configure the UART oversample mode (API_ID(0x000CU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  oversamp: oversample value
                only one parameter can be selected which is shown as below:
      \arg        UART_OVSMOD_8: 8 bits
      \arg        UART_OVSMOD_16: 16 bits
    \param[out] none
    \retval     none
*/
void uart_oversample_config(uint32_t uart_periph, uint32_t oversamp)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    /*  clear OVSMOD bit */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_OVSMOD);
    UART_CTL0(uart_periph) |= oversamp & UART_CTL0_OVSMOD;
}

/*!
    \brief      configure sample bit method (API_ID(0x000DU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  osb: sample bit
                only one parameter can be selected which is shown as below:
      \arg        UART_OSB_1bit: 1 bit
      \arg        UART_OSB_3bit: 3 bits
    \param[out] none
    \retval     none
*/
void uart_sample_bit_config(uint32_t uart_periph, uint32_t osb)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    /* clear OSB bit */
    UART_CTL2(uart_periph) &= ~(UART_CTL2_OSB);
    UART_CTL2(uart_periph) |= osb & UART_CTL2_OSB;
}

/*!
    \brief    UART transmit data function (API_ID(0x000EU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  data: data of transmission
    \param[out] none
    \retval     none
*/
void uart_data_transmit(uint32_t uart_periph, uint32_t data)
{
    UART_DATA(uart_periph) = (UART_DATA_DATA & data);
}

/*!
    \brief      UART receive data function (API_ID(0x000FU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     data of received
*/
uint16_t uart_data_receive(uint32_t uart_periph)
{
    uint16_t data = 0U;

    data  = (uint16_t)(GET_BITS(UART_DATA(uart_periph), 0U, 9U));
    return data;
}

/*!
    \brief      configure the address of the UART in wake up by address match mode (API_ID(0x0010U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  addr: address of UART
    \param[out] none
    \retval     none
*/
void uart_address_config(uint32_t uart_periph, uint8_t addr)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);

    UART_CTL1(uart_periph) &= ~(UART_CTL1_ADDR);
    UART_CTL1(uart_periph) |= (UART_CTL1_ADDR & (uint32_t)addr);
}

/*!
    \brief      enable mute mode (API_ID(0x0011U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_mute_mode_enable(uint32_t uart_periph)
{
    UART_CTL0(uart_periph) |= UART_CTL0_RWU;
}

/*!
    \brief      disable mute mode (API_ID(0x0012U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_mute_mode_disable(uint32_t uart_periph)
{
    UART_CTL0(uart_periph) &= ~(UART_CTL0_RWU);
}

/*!
    \brief      configure wakeup method in mute mode (API_ID(0x0013U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  wmethod: two method be used to enter or exit the mute mode
                only one parameter can be selected which is shown as below:
      \arg        UART_WM_IDLE: idle line
      \arg        UART_WM_ADDR: address mask
    \param[out] none
    \retval     none
*/
void uart_mute_mode_wakeup_config(uint32_t uart_periph, uint32_t wmethod)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);

    UART_CTL0(uart_periph) &= ~(UART_CTL0_WM);
    UART_CTL0(uart_periph) |= wmethod & UART_CTL0_WM;
}

/*!
    \brief      enable LIN mode (API_ID(0x0014U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_lin_mode_enable(uint32_t uart_periph)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    /* enable LIN mode */
    UART_CTL1(uart_periph) |= UART_CTL1_LMEN;
}

/*!
    \brief      disable LIN mode (API_ID(0x0015U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_lin_mode_disable(uint32_t uart_periph)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    /* disable LIN mode */
    UART_CTL1(uart_periph) &= ~(UART_CTL1_LMEN);
}

/*!
    \brief      configure lin break frame length (API_ID(0x0016U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  lblen: lin break frame length
                only one parameter can be selected which is shown as below:
      \arg        UART_LBLEN_10B: 10 bits
      \arg        UART_LBLEN_11B: 11 bits
    \param[out] none
    \retval     none
*/
void uart_lin_break_detection_length_config(uint32_t uart_periph, uint32_t lblen)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);

    UART_CTL1(uart_periph) &= ~(UART_CTL1_LBLEN);
    UART_CTL1(uart_periph) |= (UART_CTL1_LBLEN & lblen);
}

/*!
    \brief      send break frame (API_ID(0x0017U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_send_break(uint32_t uart_periph)
{
    UART_CTL0(uart_periph) |= UART_CTL0_SBKCMD;
}

/*!
    \brief      enable half duplex mode (API_ID(0x0018U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_halfduplex_enable(uint32_t uart_periph)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    UART_CTL2(uart_periph) |= UART_CTL2_HDEN;
}

/*!
    \brief      disable half duplex mode (API_ID(0x0019U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_halfduplex_disable(uint32_t uart_periph)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    UART_CTL2(uart_periph) &= ~(UART_CTL2_HDEN);
}

/*!
    \brief      enable IrDA mode (API_ID(0x001AU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_irda_mode_enable(uint32_t uart_periph)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    /* enable IrDA mode */
    UART_CTL2(uart_periph) |= UART_CTL2_IREN;
}

/*!
    \brief      disable IrDA mode (API_ID(0x001BU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void uart_irda_mode_disable(uint32_t uart_periph)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);
    /* disable IrDA mode */
    UART_CTL2(uart_periph) &= ~(UART_CTL2_IREN);
}

/*!
    \brief      configure the peripheral clock prescaler in UART IrDA low-power mode (API_ID(0x001CU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  psc: 0-0xFF
    \param[out] none
    \retval     none
*/
void uart_prescaler_config(uint32_t uart_periph, uint8_t psc)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);

    UART_GP(uart_periph) &= ~(UART_GP_PSC);
    UART_GP(uart_periph) |= (uint32_t)psc & UART_GP_PSC;
}

/*!
    \brief      configure IrDA low-power (API_ID(0x001DU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  irlp: IrDA low-power or normal
                only one parameter can be selected which is shown as below:
      \arg        UART_IRLP_LOW: low-power
      \arg        UART_IRLP_NORMAL: normal
    \param[out] none
    \retval     none
*/
void uart_irda_lowpower_config(uint32_t uart_periph, uint32_t irlp)
{
    /* disable UART */
    UART_CTL0(uart_periph) &= ~(UART_CTL0_UEN);

    UART_CTL2(uart_periph) &= ~(UART_CTL2_IRLP);
    UART_CTL2(uart_periph) |= (UART_CTL2_IRLP & irlp);
}

/*!
    \brief      configure parity check coherence mode (API_ID(0x001EU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  pcm:
                only one parameter can be selected which is shown as below:
      \arg        UART_PCM_NONE: not check parity
      \arg        UART_PCM_EN:   check the parity
    \param[out] none
    \retval     none
*/
void uart_parity_check_coherence_config(uint32_t uart_periph, uint32_t pcm)
{
    UART_CHC(uart_periph) &= ~(UART_CHC_PCM);
    UART_CHC(uart_periph) |= (UART_CHC_PCM & pcm);
}

/*!
    \brief      configure UART DMA reception (API_ID(0x001FU))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  dmacmd: enable or disable DMA for reception
                only one parameter can be selected which is shown as below:
      \arg        UART_RECEIVE_DMA_ENABLE: DMA enable for reception
      \arg        UART_RECEIVE_DMA_DISABLE: DMA disable for reception
    \param[out] none
    \retval     none
*/
void uart_dma_receive_config(uint32_t uart_periph, uint32_t dmacmd)
{
    UART_CTL2(uart_periph) &= ~(UART_CTL2_DENR);
    UART_CTL2(uart_periph) |= (UART_CTL2_DENR & dmacmd);
}

/*!
    \brief      configure UART DMA transmission (API_ID(0x0020U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  dmacmd: enable or disable DMA for transmission
                only one parameter can be selected which is shown as below:
      \arg        UART_TRANSMIT_DMA_ENABLE:  DMA enable for transmission
      \arg        UART_TRANSMIT_DMA_DISABLE: DMA disable for transmission
    \param[out] none
    \retval     none
*/
void uart_dma_transmit_config(uint32_t uart_periph, uint32_t dmacmd)
{
    UART_CTL2(uart_periph) &= ~(UART_CTL2_DENT);
    UART_CTL2(uart_periph) |= (UART_CTL2_DENT & dmacmd);
}

/*!
    \brief      get flag in STAT0/CHC register (API_ID(0x0021U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  flag: UART flags, refer to uart_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        UART_FLAG_LBD: LIN break detected flag
      \arg        UART_FLAG_TBE: transmit data buffer empty
      \arg        UART_FLAG_TC: transmission complete
      \arg        UART_FLAG_RBNE: read data buffer not empty
      \arg        UART_FLAG_IDLE: IDLE frame detected flag
      \arg        UART_FLAG_ORERR: overrun error
      \arg        UART_FLAG_NERR: noise error flag
      \arg        UART_FLAG_FERR: frame error flag
      \arg        UART_FLAG_PERR: parity error flag
      \arg        UART_FLAG_EPERR: early parity error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus uart_flag_get(uint32_t uart_periph, uart_flag_enum flag)
{
    FlagStatus status = RESET;

    if((uint32_t)RESET != (UART_REG_VAL(uart_periph, flag) & BIT(UART_BIT_POS(flag)))) {
        status = SET;
    } else {
        status = RESET;
    }
    return status;
}

/*!
    \brief      clear flag in STAT0/CHC register (API_ID(0x0022U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  flag: UART flags, refer to uart_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        UART_FLAG_LBD: LIN break detected flag
      \arg        UART_FLAG_TC: transmission complete
      \arg        UART_FLAG_RBNE: read data buffer not empty
      \arg        UART_FLAG_EPERR: early parity error flag
    \param[out] none
    \retval     none
*/
void uart_flag_clear(uint32_t uart_periph, uart_flag_enum flag)
{
    UART_REG_VAL(uart_periph, flag) &= ~BIT(UART_BIT_POS(flag));
}

/*!
    \brief      enable UART interrupt (API_ID(0x0023U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  interrupt: UART interrupts, refer to uart_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        UART_INT_PERR: parity error interrupt
      \arg        UART_INT_TBE: transmitter buffer empty interrupt
      \arg        UART_INT_TC: transmission complete interrupt
      \arg        UART_INT_RBNE: read data buffer not empty interrupt and overrun error interrupt
      \arg        UART_INT_IDLE: IDLE line detected interrupt
      \arg        UART_INT_LBD: LIN break detected interrupt
      \arg        UART_INT_ERR: error interrupt
    \param[out] none
    \retval     none
*/
void uart_interrupt_enable(uint32_t uart_periph, uart_interrupt_enum interrupt)
{
    UART_REG_VAL(uart_periph, interrupt) |= BIT(UART_BIT_POS(interrupt));
}

/*!
    \brief      disable UART interrupt (API_ID(0x0024U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  interrupt: UART interrupts, refer to uart_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        UART_INT_PERR: parity error interrupt
      \arg        UART_INT_TBE: transmitter buffer empty interrupt
      \arg        UART_INT_TC: transmission complete interrupt
      \arg        UART_INT_RBNE: read data buffer not empty interrupt and overrun error interrupt
      \arg        UART_INT_IDLE: IDLE line detected interrupt
      \arg        UART_INT_LBD: LIN break detected interrupt
      \arg        UART_INT_ERR: error interrupt
    \param[out] none
    \retval     none
*/
void uart_interrupt_disable(uint32_t uart_periph, uart_interrupt_enum interrupt)
{
    UART_REG_VAL(uart_periph, interrupt) &= ~BIT(UART_BIT_POS(interrupt));
}

/*!
    \brief      get UART interrupt and flag status (API_ID(0x0025U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  int_flag: UART interrupt flags, refer to uart_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        UART_INT_FLAG_PERR: parity error interrupt and flag
      \arg        UART_INT_FLAG_TBE: transmitter buffer empty interrupt and flag
      \arg        UART_INT_FLAG_TC: transmission complete interrupt and flag
      \arg        UART_INT_FLAG_RBNE: read data buffer not empty interrupt and flag
      \arg        UART_INT_FLAG_RBNE_ORERR: read data buffer not empty interrupt and overrun error flag
      \arg        UART_INT_FLAG_IDLE: IDLE line detected interrupt and flag
      \arg        UART_INT_FLAG_LBD: LIN break detected interrupt and flag
      \arg        UART_INT_FLAG_ERR_ORERR: error interrupt and overrun error
      \arg        UART_INT_FLAG_ERR_NERR: error interrupt and noise error flag
      \arg        UART_INT_FLAG_ERR_FERR: error interrupt and frame error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus uart_interrupt_flag_get(uint32_t uart_periph, uart_interrupt_flag_enum int_flag)
{
    uint32_t intenable, flagstatus;
    FlagStatus status = RESET;

    /* get the interrupt enable bit status */
    intenable = (UART_REG_VAL(uart_periph, int_flag) & BIT(UART_BIT_POS(int_flag)));
    /* get the corresponding flag bit status */
    flagstatus = (UART_REG_VAL2(uart_periph, int_flag) & BIT(UART_BIT_POS2(int_flag)));

    if((0U != flagstatus) && (0U != intenable)) {
        status =  SET;
    } else {
        status = RESET;
    }
    return status;
}

/*!
    \brief      clear UART interrupt flag in STAT0 register (API_ID(0x0026U))
    \param[in]  uart_periph: UARTx(x = 0,1,2,3)
    \param[in]  int_flag: UART interrupt flags, refer to uart_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        UART_INT_FLAG_LBD: LIN break detected flag
      \arg        UART_INT_FLAG_TC: transmission complete
      \arg        UART_INT_FLAG_RBNE: read data buffer not empty
    \param[out] none
    \retval     none
*/
void uart_interrupt_flag_clear(uint32_t uart_periph, uart_interrupt_flag_enum int_flag)
{
    UART_REG_VAL2(uart_periph, int_flag) &= ~BIT(UART_BIT_POS2(int_flag));
}
