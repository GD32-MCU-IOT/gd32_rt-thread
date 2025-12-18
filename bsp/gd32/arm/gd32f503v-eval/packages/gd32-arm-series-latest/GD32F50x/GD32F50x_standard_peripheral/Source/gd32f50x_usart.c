/*!
    \file    gd32f50x_usart.c
    \brief   USART driver

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

#include "gd32f50x_usart.h"

/* USART register bit offset */
#define GP_GUAT_OFFSET            ((uint32_t)8U)       /* bit offset of GUAT in USART_GP */
#define CTL3_SCRTNUM_OFFSET       ((uint32_t)1U)       /* bit offset of SCRTNUM in USART_CTL3 */
#define RT_BL_OFFSET              ((uint32_t)24U)      /* bit offset of BL in USART_RT */

/*!
    \brief    reset USART/UART (API ID: 0x0001U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_deinit(uint32_t usart_periph)
{
    switch(usart_periph) {
    case USART0:
        /* reset USART0 */
        rcu_periph_reset_enable(RCU_USART0RST);
        rcu_periph_reset_disable(RCU_USART0RST);
        break;
    case USART1:
        /* reset USART1 */
        rcu_periph_reset_enable(RCU_USART1RST);
        rcu_periph_reset_disable(RCU_USART1RST);
        break;
    case USART2:
        /* reset USART2 */
        rcu_periph_reset_enable(RCU_USART2RST);
        rcu_periph_reset_disable(RCU_USART2RST);
        break;
    case UART3:
        /* reset UART3 */
        rcu_periph_reset_enable(RCU_UART3RST);
        rcu_periph_reset_disable(RCU_UART3RST);
        break;
    case UART4:
        /* reset UART4 */
        rcu_periph_reset_enable(RCU_UART4RST);
        rcu_periph_reset_disable(RCU_UART4RST);
        break;
    default:
        break;
    }
}

/*!
    \brief    configure USART baud rate value (API ID: 0x0002U)
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  baudval: baud rate value
    \param[out] none
    \retval     none
*/
void usart_baudrate_set(uint32_t usart_periph, uint32_t baudval)
{
    uint32_t uclk = 0U, intdiv = 0U, fradiv = 0U, udiv = 0U;
    
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_USART_BAUDRATE(baudval)) {
        fw_debug_report_err(USART_MODULE_ID, API_ID(0x0002U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        switch(usart_periph) {
        /* get clock frequency */
        case USART0:
            /* get USART0 clock */
            uclk = rcu_clock_freq_get(CK_APB2);
            break;
        case USART1:
            /* get USART1 clock */
            uclk = rcu_clock_freq_get(CK_APB1);
            break;
        case USART2:
            /* get USART2 clock */
            uclk = rcu_clock_freq_get(CK_APB1);
            break;
        case UART3:
            /* get UART3 clock */
            uclk = rcu_clock_freq_get(CK_APB1);
            break;
        case UART4:
            /* get UART4 clock */
            uclk = rcu_clock_freq_get(CK_APB1);
            break;
        default:
            break;
        }
        if(USART_CTL0(usart_periph) & USART_CTL0_OVSMOD) {
            /* when oversampling by 8, configure the value of USART_BAUD */
            udiv = ((2U * uclk) + baudval / 2U) / baudval;
            intdiv = udiv & 0x3fff0U;
            fradiv = (udiv >> 1U) & 0x7U;
            USART_BAUD(usart_periph) = ((USART_BAUD_FRADIV | USART_BAUD_INTDIV) & (intdiv | fradiv));
        } else {
            /* when oversampling by 16, configure the value of USART_BAUD */
            udiv = (uclk + baudval / 2U) / baudval;
            intdiv = udiv & 0x3fff0U;
            fradiv = udiv & 0xfU;
            USART_BAUD(usart_periph) = ((USART_BAUD_FRADIV | USART_BAUD_INTDIV) & (intdiv | fradiv));
        }
    }
}

/*!
    \brief   configure USART parity function (API ID: 0x0003U)
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in] paritycfg: configure USART parity
               only one parameter can be selected which is shown as below:
      \arg       USART_PM_NONE: no parity
      \arg       USART_PM_EVEN: even parity
      \arg       USART_PM_ODD:  odd parity
    \param[out] none
    \retval     none
*/
void usart_parity_config(uint32_t usart_periph, uint32_t paritycfg)
{
    /* clear USART_CTL0 PM,PCEN Bits */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_PM | USART_CTL0_PCEN);
    /* configure USART parity mode */
    USART_CTL0(usart_periph) |= paritycfg & (USART_CTL0_PM | USART_CTL0_PCEN);
}

/*!
    \brief   configure USART word length (API ID: 0x0004U)
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in] wlen: USART word length configure
               only one parameter can be selected which is shown as below:
      \arg       USART_WL_8BIT: 8 bits
      \arg       USART_WL_9BIT: 9 bits
    \param[out] none
    \retval     none
*/
void usart_word_length_set(uint32_t usart_periph, uint32_t wlen)
{
    /* clear USART_CTL0 WL bit */
    USART_CTL0(usart_periph) &= ~USART_CTL0_WL;
    /* configure USART word length */
    USART_CTL0(usart_periph) |= wlen & USART_CTL0_WL;
}

/*!
    \brief   configure USART stop bit length (API ID: 0x0005U)
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in] stblen: USART stop bit configure
               only one parameter can be selected which is shown as below:
      \arg       USART_STB_1BIT:   1 bit
      \arg       USART_STB_0_5BIT: 0.5 bit(not available for UARTx(x=3,4))
      \arg       USART_STB_2BIT:   2 bits
      \arg       USART_STB_1_5BIT: 1.5 bits(not available for UARTx(x=3,4))
    \param[out] none
    \retval     none
*/
void usart_stop_bit_set(uint32_t usart_periph, uint32_t stblen)
{
    /* clear USART_CTL1 STB bits */
    USART_CTL1(usart_periph) &= ~USART_CTL1_STB;
    /* configure USART stop bits */
    USART_CTL1(usart_periph) |= stblen & USART_CTL1_STB;
}
/*!
    \brief    enable USART (API ID: 0x0006U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_enable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) |= USART_CTL0_UEN;
}

/*!
    \brief   disable USART (API ID: 0x0007U)
    \param[in]  usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_disable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_UEN);
}

/*!
    \brief    configure USART transmitter (API ID: 0x0008U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  txconfig: enable or disable USART transmitter
                only one parameter can be selected which is shown as below:
      \arg        USART_TRANSMIT_ENABLE: enable USART transmission
      \arg        USART_TRANSMIT_DISABLE: enable USART transmission
    \param[out] none
    \retval     none
*/
void usart_transmit_config(uint32_t usart_periph, uint32_t txconfig)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_TEN);
    USART_CTL0(usart_periph) |= (USART_CTL0_TEN & txconfig);
}

/*!
    \brief    configure USART receiver (API ID: 0x0009U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  rxconfig: enable or disable USART receiver
                only one parameter can be selected which is shown as below:
      \arg        USART_RECEIVE_ENABLE: enable USART reception
      \arg        USART_RECEIVE_DISABLE: disable USART reception
    \param[out] none
    \retval     none
*/
void usart_receive_config(uint32_t usart_periph, uint32_t rxconfig)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_REN);
    USART_CTL0(usart_periph) |= (USART_CTL0_REN & rxconfig);
}

/*!
    \brief    data is transmitted/received with the LSB/MSB first (API ID: 0x000AU)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  msbf: LSB/MSB
                only one parameter can be selected which is shown as below:
      \arg        USART_MSBF_LSB: LSB first
      \arg        USART_MSBF_MSB: MSB first
    \param[out] none
    \retval     none
*/
void usart_data_first_config(uint32_t usart_periph, uint32_t msbf)
{
    USART_CTL3(usart_periph) &= ~(USART_CTL3_MSBF); 
    USART_CTL3(usart_periph) |= msbf & USART_CTL3_MSBF;
}

/*!
    \brief    configure USART inversion (API ID: 0x000BU)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  invertpara: refer to enum USART_INVERT_CONFIG
                only one parameter can be selected which is shown as below:
      \arg        USART_DINV_ENABLE: data bit level inversion
      \arg        USART_DINV_DISABLE: data bit level not inversion
      \arg        USART_TXPIN_ENABLE: TX pin level inversion
      \arg        USART_TXPIN_DISABLE: TX pin level not inversion
      \arg        USART_RXPIN_ENABLE: RX pin level inversion
      \arg        USART_RXPIN_DISABLE: RX pin level not inversion
    \param[out] none
    \retval     none
*/
void usart_invert_config(uint32_t usart_periph, usart_invert_enum invertpara)
{
    /* inverted or not the specified siginal */
    switch(invertpara) {
    case USART_DINV_ENABLE:
        USART_CTL3(usart_periph) |= USART_CTL3_DINV;
        break;
    case USART_TXPIN_ENABLE:
        USART_CTL3(usart_periph) |= USART_CTL3_TINV;
        break;
    case USART_RXPIN_ENABLE:
        USART_CTL3(usart_periph) |= USART_CTL3_RINV;
        break;
    case USART_DINV_DISABLE:
        USART_CTL3(usart_periph) &= ~(USART_CTL3_DINV);
        break;
    case USART_TXPIN_DISABLE:
        USART_CTL3(usart_periph) &= ~(USART_CTL3_TINV);
        break;
    case USART_RXPIN_DISABLE:
        USART_CTL3(usart_periph) &= ~(USART_CTL3_RINV);
        break;
    default:
        break;
    }
}

/*!
    \brief    configure the USART oversample mode (API ID: 0x000CU)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  oversamp: oversample value
                only one parameter can be selected which is shown as below:
      \arg        USART_OVSMOD_8: 8 bits
      \arg        USART_OVSMOD_16: 16 bits
    \param[out] none
    \retval     none
*/
void usart_oversample_config(uint32_t usart_periph, uint32_t oversamp)
{
    /*  clear OVSMOD bit */
    USART_CTL0(usart_periph) &= ~(USART_CTL0_OVSMOD);
    USART_CTL0(usart_periph) |= oversamp & USART_CTL0_OVSMOD;
}

/*!
    \brief    configure sample bit method (API ID: 0x000DU)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  obsm: sample bit
                only one parameter can be selected which is shown as below:
      \arg        USART_OSB_1bit: 1 bit
      \arg        USART_OSB_3bit: 3 bits
    \param[out] none
    \retval     none
*/
void usart_sample_bit_config(uint32_t usart_periph, uint32_t obsm)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_OSB);
    USART_CTL2(usart_periph) |= obsm & USART_CTL2_OSB;
}

/*!
    \brief    enable receiver timeout of USART (API ID: 0x000EU)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void usart_receiver_timeout_enable(uint32_t usart_periph)
{
    USART_CTL3(usart_periph) |= USART_CTL3_RTEN;
}

/*!
    \brief    disable receiver timeout of USART (API ID: 0x000FU)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void usart_receiver_timeout_disable(uint32_t usart_periph)
{
    USART_CTL3(usart_periph) &= ~(USART_CTL3_RTEN);
}

/*!
    \brief    configure receiver timeout threshold (API ID: 0x0010U)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  rtimeout: 0-0x00FFFFFF
    \param[out] none
    \retval     none
*/
void usart_receiver_timeout_threshold_config(uint32_t usart_periph, uint32_t rtimeout)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_USART_RECEIVE_TIMEOUT(rtimeout)) {
        fw_debug_report_err(USART_MODULE_ID, API_ID(0x0010U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        USART_RT(usart_periph) &= ~(USART_RT_RT);
        USART_RT(usart_periph) |= rtimeout & USART_RT_RT;
    }
}

/*!
    \brief    USART transmit data function (API ID: 0x0011U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  data: data of transmission
    \param[out] none
    \retval     none
*/
void usart_data_transmit(uint32_t usart_periph, uint32_t data)
{
    USART_DATA(usart_periph) = ((uint16_t)USART_DATA_DATA & data);
}

/*!
    \brief    USART receive data function (API ID: 0x0012U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     data of received
*/
uint16_t usart_data_receive(uint32_t usart_periph)
{
    return (uint16_t)(GET_BITS(USART_DATA(usart_periph), 0U, 8U));
}

/*!
    \brief    configure address of the USART (API ID: 0x0013U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  addr: address of USART/UART
    \param[out] none
    \retval     none
*/
void usart_address_config(uint32_t usart_periph, uint8_t addr)
{
    USART_CTL1(usart_periph) &= ~(USART_CTL1_ADDR);
    USART_CTL1(usart_periph) |= (USART_CTL1_ADDR & (uint32_t)addr);
}

/*!
    \brief    enable mute mode (API ID: 0x0014U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_mute_mode_enable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) |= USART_CTL0_RWU;
}

/*!
    \brief    disable mute mode (API ID: 0x0015U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_mute_mode_disable(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_RWU);
}

/*!
    \brief    configure wakeup method in mute mode (API ID: 0x0016U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  wmehtod: two method be used to enter or exit the mute mode
                only one parameter can be selected which is shown as below:
      \arg        USART_WM_IDLE: idle line
      \arg        USART_WM_ADDR: address mask
    \param[out] none
    \retval     none
*/
void usart_mute_mode_wakeup_config(uint32_t usart_periph, uint32_t wmehtod)
{
    USART_CTL0(usart_periph) &= ~(USART_CTL0_WM);
    USART_CTL0(usart_periph) |= wmehtod & USART_CTL0_WM;
}

/*!
    \brief    enable LIN mode (API ID: 0x0017U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_lin_mode_enable(uint32_t usart_periph)
{
    USART_CTL1(usart_periph) |= USART_CTL1_LMEN;
}

/*!
    \brief    disable LIN mode (API ID: 0x0018U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_lin_mode_disable(uint32_t usart_periph)
{
    USART_CTL1(usart_periph) &= ~(USART_CTL1_LMEN);
}

/*!
    \brief    configure lin break frame length (API ID: 0x0019U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  lblen: lin break frame length
                only one parameter can be selected which is shown as below:
      \arg        USART_LBLEN_10B: 10 bits
      \arg        USART_LBLEN_11B: 11 bits
    \param[out] none
    \retval     none
*/
void usart_lin_break_detection_length_config(uint32_t usart_periph, uint32_t lblen)
{
    USART_CTL1(usart_periph) &= ~(USART_CTL1_LBLEN);
    USART_CTL1(usart_periph) |= (USART_CTL1_LBLEN & lblen);
}

/*!
    \brief    send break frame (API ID: 0x001AU)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_send_break(uint32_t usart_periph)
{
    USART_CTL0(usart_periph) |= USART_CTL0_SBKCMD;
}

/*!
    \brief    enable half-duplex mode (API ID: 0x001BU)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_halfduplex_enable(uint32_t usart_periph)
{
    USART_CTL2(usart_periph) |= USART_CTL2_HDEN;
}

/*!
    \brief    disable half-duplex mode (API ID: 0x001CU)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_halfduplex_disable(uint32_t usart_periph)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_HDEN);
}

/*!
    \brief    enable CK pin in synchronous mode (API ID: 0x001DU)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void usart_synchronous_clock_enable(uint32_t usart_periph)
{
    USART_CTL1(usart_periph) |= USART_CTL1_CKEN;
}

/*!
    \brief    disable CK pin in synchronous mode (API ID: 0x001EU)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void usart_synchronous_clock_disable(uint32_t usart_periph)
{
    USART_CTL1(usart_periph) &= ~(USART_CTL1_CKEN);
}

/*!
    \brief    configure USART synchronous mode parameters (API ID: 0x001FU)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  clen: CK length
                only one parameter can be selected which is shown as below:
      \arg        USART_CLEN_NONE: there are 7 CK pulses for an 8 bit frame and 8 CK pulses for a 9 bit frame
      \arg        USART_CLEN_EN:   there are 8 CK pulses for an 8 bit frame and 9 CK pulses for a 9 bit frame
    \param[in]  cph: clock phase
                only one parameter can be selected which is shown as below:
      \arg        USART_CPH_1CK: first clock transition is the first data capture edge
      \arg        USART_CPH_2CK: second clock transition is the first data capture edge
    \param[in]  cpl: clock polarity
                only one parameter can be selected which is shown as below:
      \arg        USART_CPL_LOW:  steady low value on CK pin
      \arg        USART_CPL_HIGH: steady high value on CK pin
    \param[out] none
    \retval     none
*/
void usart_synchronous_clock_config(uint32_t usart_periph, uint32_t clen, uint32_t cph, uint32_t cpl)
{
    USART_CTL1(usart_periph) &= ~(USART_CTL1_CLEN | USART_CTL1_CPH | USART_CTL1_CPL);
    USART_CTL1(usart_periph) |= (USART_CTL1_CLEN & clen) | (USART_CTL1_CPH & cph) | (USART_CTL1_CPL & cpl);
}

/*!
    \brief    configure guard time value in smartcard mode (API ID: 0x0020U)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  guat: guard time value, 0-0xFF
    \param[out] none
    \retval     none
*/
void usart_guard_time_config(uint32_t usart_periph, uint32_t guat)
{
    USART_GP(usart_periph) &= ~(USART_GP_GUAT);
    USART_GP(usart_periph) |= (USART_GP_GUAT & ((guat) << GP_GUAT_OFFSET));
}

/*!
    \brief    enable smartcard mode (API ID: 0x0021U)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_enable(uint32_t usart_periph)
{
    USART_CTL2(usart_periph) |= USART_CTL2_SCEN;
}

/*!
    \brief    disable smartcard mode (API ID: 0x0022U)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_disable(uint32_t usart_periph)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_SCEN);
}

/*!
    \brief    enable NACK in smartcard mode (API ID: 0x0023U)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_nack_enable(uint32_t usart_periph)
{
    USART_CTL2(usart_periph) |= USART_CTL2_NKEN;
}

/*!
    \brief    disable NACK in smartcard mode (API ID: 0x0024U)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[out] none
    \retval     none
*/
void usart_smartcard_mode_nack_disable(uint32_t usart_periph)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_NKEN);
}

/*!
    \brief    configure smartcard auto-retry number (API ID: 0x0025U)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  scrtnum: smartcard auto-retry number
    \param[out] none
    \retval     none
*/
void usart_smartcard_autoretry_config(uint32_t usart_periph, uint32_t scrtnum)
{
    USART_CTL3(usart_periph) &= ~(USART_CTL3_SCRTNUM);
    USART_CTL3(usart_periph) |= (USART_CTL3_SCRTNUM & ((scrtnum) << CTL3_SCRTNUM_OFFSET));
}

/*!
    \brief    configure block length in Smartcard T=1 reception (API ID: 0x0026U)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  bl: block length
    \param[out] none
    \retval     none
*/
void usart_block_length_config(uint32_t usart_periph, uint32_t bl)
{
    USART_RT(usart_periph) &= ~(USART_RT_BL);
    USART_RT(usart_periph) |= (USART_RT_BL & ((bl) << RT_BL_OFFSET));
}

/*!
    \brief    enable IrDA mode (API ID: 0x0027U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_irda_mode_enable(uint32_t usart_periph)
{
    USART_CTL2(usart_periph) |= USART_CTL2_IREN;
}

/*!
    \brief    disable IrDA mode (API ID: 0x0028U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[out] none
    \retval     none
*/
void usart_irda_mode_disable(uint32_t usart_periph)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_IREN);
}

/*!
    \brief    configure the peripheral clock prescaler in USART IrDA low-power mode (API ID: 0x0029U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  psc: 0-0xFF
    \param[out] none
    \retval     none
*/
void usart_prescaler_config(uint32_t usart_periph, uint8_t psc)
{
    USART_GP(usart_periph) &= ~(USART_GP_PSC);
    USART_GP(usart_periph) |= (uint32_t)psc & USART_GP_PSC;
}

/*!
    \brief    configure IrDA low-power (API ID: 0x002AU)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  irlp: IrDA low-power or normal
                only one parameter can be selected which is shown as below:
      \arg        USART_IRLP_LOW: low-power
      \arg        USART_IRLP_NORMAL: normal
    \param[out] none
    \retval     none
*/
void usart_irda_lowpower_config(uint32_t usart_periph, uint32_t irlp)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_IRLP);
    USART_CTL2(usart_periph) |= (USART_CTL2_IRLP & irlp);
}

/*!
    \brief    configure hardware flow control RTS (API ID: 0x002BU)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  rtsconfig: enable or disable RTS
                only one parameter can be selected which is shown as below:
      \arg        USART_RTS_ENABLE:  enable RTS
      \arg        USART_RTS_DISABLE: disable RTS
    \param[out] none
    \retval     none
*/
void usart_hardware_flow_rts_config(uint32_t usart_periph, uint32_t rtsconfig)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_RTSEN);
    USART_CTL2(usart_periph) |= (USART_CTL2_RTSEN & rtsconfig);
}

/*!
    \brief    configure hardware flow control CTS (API ID: 0x002CU)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  ctsconfig: enable or disable CTS
                only one parameter can be selected which is shown as below:
      \arg        USART_CTS_ENABLE:  enable CTS
      \arg        USART_CTS_DISABLE: disable CTS
    \param[out] none
    \retval     none
*/
void usart_hardware_flow_cts_config(uint32_t usart_periph, uint32_t ctsconfig)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_CTSEN);
    USART_CTL2(usart_periph) |= (USART_CTL2_CTSEN & ctsconfig);
}

/*!
    \brief    configure break frame coherence mode (API ID: 0x002DU)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  bcm:
                only one parameter can be selected which is shown as below:
      \arg        USART_BCM_NONE: no parity error is detected
      \arg        USART_BCM_EN:   parity error is detected
    \param[out] none
    \retval     none
*/
void usart_break_frame_coherence_config(uint32_t usart_periph, uint32_t bcm)
{
    USART_CHC(usart_periph) &= ~(USART_CHC_BCM);
    USART_CHC(usart_periph) |= (USART_CHC_BCM & bcm);
}

/*!
    \brief    configure parity check coherence mode (API ID: 0x002EU)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  pcm:
                only one parameter can be selected which is shown as below:
      \arg        USART_PCM_NONE: not check parity
      \arg        USART_PCM_EN:   check the parity
    \param[out] none
    \retval     none
*/
void usart_parity_check_coherence_config(uint32_t usart_periph, uint32_t pcm)
{
    USART_CHC(usart_periph) &= ~(USART_CHC_PCM);
    USART_CHC(usart_periph) |= (USART_CHC_PCM & pcm);
}

/*!
    \brief    configure hardware flow control coherence mode (API ID: 0x002FU)
    \param[in]  usart_periph: USARTx(x=0,1,2)
    \param[in]  hcm:
                only one parameter can be selected which is shown as below:
      \arg        USART_HCM_NONE: nRTS signal equals to the rxne status register
      \arg        USART_HCM_EN:   nRTS signal is set when the last data bit has been sampled
    \param[out] none
    \retval     none
*/
void usart_hardware_flow_coherence_config(uint32_t usart_periph, uint32_t hcm)
{
    USART_CHC(usart_periph) &= ~(USART_CHC_HCM);
    USART_CHC(usart_periph) |= (USART_CHC_HCM & hcm);
}

/*!
    \brief    configure USART DMA for reception (API ID: 0x0030U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  dmacmd: enable or disable DMA for reception
                only one parameter can be selected which is shown as below:
      \arg        USART_DENR_ENABLE:  DMA enable for reception
      \arg        USART_DENR_DISABLE: DMA disable for reception
    \param[out] none
    \retval     none
*/
void usart_dma_receive_config(uint32_t usart_periph, uint32_t dmacmd)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_DENR);
    USART_CTL2(usart_periph) |= (USART_CTL2_DENR & dmacmd);
}

/*!
    \brief    configure USART DMA for transmission (API ID: 0x0031U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  dmacmd: enable or disable DMA for transmission
                only one parameter can be selected which is shown as below:
      \arg        USART_DENT_ENABLE:  DMA enable for transmission
      \arg        USART_DENT_DISABLE: DMA disable for transmission
    \param[out] none
    \retval     none
*/
void usart_dma_transmit_config(uint32_t usart_periph, uint32_t dmacmd)
{
    USART_CTL2(usart_periph) &= ~(USART_CTL2_DENT);
    USART_CTL2(usart_periph) |= (USART_CTL2_DENT & dmacmd);
}

/*!
    \brief    get USART flag status (API ID: 0x0032U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  flag: USART flags, refer to usart_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_FLAG_CTS: CTS change flag
      \arg        USART_FLAG_LBD: LIN break detected flag
      \arg        USART_FLAG_TBE: transmit data buffer empty
      \arg        USART_FLAG_TC: transmission complete
      \arg        USART_FLAG_RBNE: read data buffer not empty
      \arg        USART_FLAG_IDLE: IDLE frame detected flag
      \arg        USART_FLAG_ORERR: overrun error
      \arg        USART_FLAG_NERR: noise error flag
      \arg        USART_FLAG_FERR: frame error flag
      \arg        USART_FLAG_PERR: parity error flag
      \arg        USART_FLAG_BSY: busy flag
      \arg        USART_FLAG_EB: end of block flag
      \arg        USART_FLAG_RT: receiver timeout flag
      \arg        USART_FLAG_EPERR: early parity error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus usart_flag_get(uint32_t usart_periph, usart_flag_enum flag)
{
    FlagStatus status = RESET;

    if(RESET != (USART_REG_VAL(usart_periph, flag) & BIT(USART_BIT_POS(flag)))) {
        status = SET;
    } else {
        status = RESET;
    }
    return status;
}

/*!
    \brief    clear USART flag status (API ID: 0x0033U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  flag: USART flags, refer to usart_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_FLAG_CTS: CTS change flag
      \arg        USART_FLAG_LBD: LIN break detected flag
      \arg        USART_FLAG_TC: transmission complete
      \arg        USART_FLAG_RBNE: read data buffer not empty
      \arg        USART_FLAG_EB: end of block flag
      \arg        USART_FLAG_RT: receiver timeout flag
      \arg        USART_FLAG_EPERR: early parity error flag
    \param[out] none
    \retval     none
*/
void usart_flag_clear(uint32_t usart_periph, usart_flag_enum flag)
{
    if (USART_FLAG_EPERR == flag) {
        USART_REG_VAL(usart_periph, flag) &= ~BIT(USART_BIT_POS(flag));
    } else {
        USART_REG_VAL(usart_periph, flag) = ~BIT(USART_BIT_POS(flag));
    }
}

/*!
    \brief    enable USART interrupt (API ID: 0x0034U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  interrupt: USART interrupts, refer to usart_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_PERR: parity error interrupt
      \arg        USART_INT_TBE: transmitter buffer empty interrupt
      \arg        USART_INT_TC: transmission complete interrupt
      \arg        USART_INT_RBNE: read data buffer not empty interrupt and overrun error interrupt
      \arg        USART_INT_IDLE: IDLE line detected interrupt
      \arg        USART_INT_LBD: LIN break detected interrupt
      \arg        USART_INT_ERR: error interrupt
      \arg        USART_INT_CTS: CTS interrupt
      \arg        USART_INT_RT: interrupt enable bit of receive timeout event
      \arg        USART_INT_EB: interrupt enable bit of end of block event
    \param[out] none
    \retval     none
*/
void usart_interrupt_enable(uint32_t usart_periph, usart_interrupt_enum interrupt)
{
    USART_REG_VAL(usart_periph, interrupt) |= BIT(USART_BIT_POS(interrupt));
}

/*!
    \brief    disable USART interrupt (API ID: 0x0035U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  interrupt: USART interrupts, refer to usart_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_PERR: parity error interrupt
      \arg        USART_INT_TBE: transmitter buffer empty interrupt
      \arg        USART_INT_TC: transmission complete interrupt
      \arg        USART_INT_RBNE: read data buffer not empty interrupt and overrun error interrupt
      \arg        USART_INT_IDLE: IDLE line detected interrupt
      \arg        USART_INT_LBD: LIN break detected interrupt
      \arg        USART_INT_ERR: error interrupt
      \arg        USART_INT_CTS: CTS interrupt
      \arg        USART_INT_RT: interrupt enable bit of receive timeout event
      \arg        USART_INT_EB: interrupt enable bit of end of block event
    \param[out] none
    \retval     none
*/
void usart_interrupt_disable(uint32_t usart_periph, usart_interrupt_enum interrupt)
{
    USART_REG_VAL(usart_periph, interrupt) &= ~BIT(USART_BIT_POS(interrupt));
}

/*!
    \brief    get USART interrupt and flag status (API ID: 0x0036U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  int_flag: USART interrupt flags, refer to usart_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_FLAG_PERR: parity error interrupt and flag
      \arg        USART_INT_FLAG_TBE: transmitter buffer empty interrupt and flag
      \arg        USART_INT_FLAG_TC: transmission complete interrupt and flag
      \arg        USART_INT_FLAG_RBNE: read data buffer not empty interrupt and flag
      \arg        USART_INT_FLAG_RBNE_ORERR: read data buffer not empty interrupt and overrun error flag
      \arg        USART_INT_FLAG_IDLE: IDLE line detected interrupt and flag
      \arg        USART_INT_FLAG_LBD: LIN break detected interrupt and flag
      \arg        USART_INT_FLAG_CTS: CTS interrupt and flag
      \arg        USART_INT_FLAG_ERR_ORERR: error interrupt and overrun error
      \arg        USART_INT_FLAG_ERR_NERR: error interrupt and noise error flag
      \arg        USART_INT_FLAG_ERR_FERR: error interrupt and frame error flag
      \arg        USART_INT_FLAG_EB: interrupt enable bit of end of block event and flag
      \arg        USART_INT_FLAG_RT: interrupt enable bit of receive timeout event and flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus usart_interrupt_flag_get(uint32_t usart_periph, usart_interrupt_flag_enum int_flag)
{
    FlagStatus status = RESET;
    uint32_t intenable = 0U, flagstatus = 0U;
    /* get the interrupt enable bit status */
    intenable = (USART_REG_VAL(usart_periph, int_flag) & BIT(USART_BIT_POS(int_flag)));
    /* get the corresponding flag bit status */
    flagstatus = (USART_REG_VAL2(usart_periph, int_flag) & BIT(USART_BIT_POS2(int_flag)));

    if((0U != flagstatus) && (0U != intenable)) {
        status = SET;
    } else {
        status = RESET;
    }
    return status;
}

/*!
    \brief    clear interrupt flag and flag status (API ID: 0x0037U)
    \param[in]   usart_periph: USARTx(x=0,1,2)/UARTx(x=3,4)
    \param[in]  int_flag: USART interrupt flags, refer to usart_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        USART_INT_FLAG_CTS: CTS change flag
      \arg        USART_INT_FLAG_LBD: LIN break detected flag
      \arg        USART_INT_FLAG_TC: transmission complete
      \arg        USART_INT_FLAG_RBNE: read data buffer not empty
      \arg        USART_INT_FLAG_EB: end of block flag
      \arg        USART_INT_FLAG_RT: receiver timeout flag
    \param[out] none
    \retval     none
*/
void usart_interrupt_flag_clear(uint32_t usart_periph, usart_interrupt_flag_enum int_flag)
{
    USART_REG_VAL2(usart_periph, int_flag) = ~BIT(USART_BIT_POS2(int_flag));
}
