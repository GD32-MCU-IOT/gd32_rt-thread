/*!
    \file    gd32m53x_evic.h
    \brief   definitions for the EVIC

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

#ifndef GD32M53X_EVIC_H
#define GD32M53X_EVIC_H

#include "gd32m53x.h"

/* EVIC definitions */
#define EVIC                              EVIC_BASE                         /*!< EVIC base address */

/* register definitions */
#define EVIC_SWEV                         REG32((EVIC) + 0x00000000U)       /*!< EVIC software event register */
#define EVIC_SGIO0                        REG32((EVIC) + 0x00000004U)       /*!< EVIC event interconnect for single I/O register 0 */
#define EVIC_SGIO1                        REG32((EVIC) + 0x00000008U)       /*!< EVIC event interconnect for single I/O register 1 */
#define EVIC_SGIO2                        REG32((EVIC) + 0x0000000CU)       /*!< EVIC event interconnect for single I/O register 2 */
#define EVIC_SGIO3                        REG32((EVIC) + 0x00000010U)       /*!< EVIC event interconnect for single I/O register 3 */
#define EVIC_INGRPE                       REG32((EVIC) + 0x00000014U)       /*!< EVIC event interconnect for input group E register */
#define EVIC_INGRPF                       REG32((EVIC) + 0x00000018U)       /*!< EVIC event interconnect for input group F register */
#define EVIC_OUTGRPE                      REG32((EVIC) + 0x0000001CU)       /*!< EVIC event interconnect for output group E register */
#define EVIC_OUTGRPF                      REG32((EVIC) + 0x00000020U)       /*!< EVIC event interconnect for output group F register */
#define EVIC_DAC0COV                      REG32((EVIC) + 0x00000024U)       /*!< EVIC event interconnect for DAC0 conversion register */
#define EVIC_ADC0COV                      REG32((EVIC) + 0x00000028U)       /*!< EVIC event interconnect for ADC0 conversion register */
#define EVIC_ADC2COV                      REG32((EVIC) + 0x0000002CU)       /*!< EVIC event interconnect for ADC2 conversion register */
#define EVIC_RCU                          REG32((EVIC) + 0x00000034U)       /*!< EVIC event interconnect for RCU register */
#define EVIC_TIMER0                       REG32((EVIC) + 0x00000038U)       /*!< EVIC event interconnect for TIMER0 register */
#define EVIC_TIMER7                       REG32((EVIC) + 0x0000003CU)       /*!< EVIC event interconnect for TIMER7 register */
#define EVIC_CPTIMER0                     REG32((EVIC) + 0x00000040U)       /*!< EVIC event interconnect for CPTIMER0 register */
#define EVIC_CPTIMERW                     REG32((EVIC) + 0x00000044U)       /*!< EVIC event interconnect for CPTIMERW register */
#define EVIC_TIMER1                       REG32((EVIC) + 0x00000048U)       /*!< EVIC event interconnect for TIMER1 register */
#define EVIC_TIMER2                       REG32((EVIC) + 0x0000004CU)       /*!< EVIC event interconnect for TIMER2 register */
#define EVIC_GPTIMER_0                    REG32((EVIC) + 0x00000050U)       /*!< EVIC event interconnect for GPTIMER register 0 */
#define EVIC_GPTIMER_1                    REG32((EVIC) + 0x00000054U)       /*!< EVIC event interconnect for GPTIMER register 1 */
#define EVIC_GPTIMER_2                    REG32((EVIC) + 0x00000058U)       /*!< EVIC event interconnect for GPTIMER register 2 */
#define EVIC_GPTIMER_3                    REG32((EVIC) + 0x0000005CU)       /*!< EVIC event interconnect for GPTIMER register 3 */
#define EVIC_DAC0EN                       REG32((EVIC) + 0x00000060U)       /*!< EVIC event interconnect for DAC0 enable register */
#define EVIC_DMAMUX_0                     REG32((EVIC) + 0x00000064U)       /*!< EVIC event interconnect for DMAMUX register 0 */
#define EVIC_DMAMUX_1                     REG32((EVIC) + 0x00000068U)       /*!< EVIC event interconnect for DMAMUX register 1 */
#define EVIC_DMAMUX_2                     REG32((EVIC) + 0x0000006CU)       /*!< EVIC event interconnect for DMAMUX register 2 */
#define EVIC_DMAMUX_3                     REG32((EVIC) + 0x00000070U)       /*!< EVIC event interconnect for DMAMUX register 3 */
#define EVIC_DMAMUX_4                     REG32((EVIC) + 0x00000074U)       /*!< EVIC event interconnect for DMAMUX register 4 */
#define EVIC_DMAMUX_5                     REG32((EVIC) + 0x00000078U)       /*!< EVIC event interconnect for DMAMUX register 5 */
#define EVIC_SMCFG0                       REG32((EVIC) + 0x0000007CU)       /*!< EVIC slave mode configuration register 0 */
#define EVIC_SMCFG1                       REG32((EVIC) + 0x00000080U)       /*!< EVIC slave mode configuration register 1 */
#define EVIC_SGIOCFG0                     REG32((EVIC) + 0x00000084U)       /*!< EVIC single I/O configuration register 0 */
#define EVIC_SGIOCFG1                     REG32((EVIC) + 0x00000088U)       /*!< EVIC single I/O configuration register 1 */
#define EVIC_SGIOCFG2                     REG32((EVIC) + 0x0000008CU)       /*!< EVIC single I/O configuration register 2 */
#define EVIC_SGIOCFG3                     REG32((EVIC) + 0x00000090U)       /*!< EVIC single I/O configuration register 3 */
#define EVIC_GRPECFG                      REG32((EVIC) + 0x00000094U)       /*!< EVIC group E configuration register */
#define EVIC_GRPEDH                       REG32((EVIC) + 0x00000098U)       /*!< EVIC group E data holding register */
#define EVIC_GRPFCFG                      REG32((EVIC) + 0x0000009CU)       /*!< EVIC group F configuration register */
#define EVIC_GRPFDH                       REG32((EVIC) + 0x00000100U)       /*!< EVIC group F data holding register */

/* bit definitions */
/* EVIC_SWEV */
#define EVIC_SWTR_BWEN                    BIT(0)                            /*!< SWEVG bit trigger enable */
#define EVIC_SWTR_SWEVG                   BIT(1)                            /*!< Software trigger generation */
#define EVIC_SWTR_RWEN                    BIT(31)                           /*!< Software event register write disable */

/* Event interconnect register */
#define EVIC_TARGET_EVSEL0                BITS(0,7)                         /*!< Event source selection 0 */
#define EVIC_TARGET_EVSEL1                BITS(8,15)                        /*!< Event source selection 1 */
#define EVIC_TARGET_EVSEL2                BITS(16,23)                       /*!< Event source selection 2 */
#define EVIC_TARGET_LK                    BIT(31)                           /*!< EVIC register lock */

/* EVIC_SMCFG0 */
#define EVIC_SMCFG0_CPTIMER0_SMSEL       BITS(0,1)                          /*!< CPTIMER0 slave mode selection */

/* EVIC_SMCFG1 */
#define EVIC_SMCFG1_CPTIMERW_SMSEL        BITS(0,1)                         /*!< CPTIMERW slave mode selection */

/* EVIC_SGIOCFGx (x=0,1,2,3) */
#define EVIC_SGIOCFGX_SGIOPORT            BITS(0,1)                         /*!< Single I/O port selection */
#define EVIC_SGIOCFGX_SGIOPIN             BITS(2,4)                         /*!< Single I/O pin selection */
#define EVIC_SGIOCFGX_SGIOM               BITS(5,6)                         /*!< Single I/O mode selection */

/* EVIC_GRPECFG */
#define EVIC_GRPECFG_GRPEIND              BITS(0,1)                         /*!< Group E input detection */
#define EVIC_GRPECFG_GRPEOSEL             BITS(2,4)                         /*!< Group E output selection */
#define EVIC_GRPECFG_OVWEN                BIT(5)                            /*!< EVIC_GRPEDH register overwrite enable */
#define EVIC_GRPECFG_PE8SEL               BIT(8)                            /*!< PE8 pin selection */
#define EVIC_GRPECFG_PE9SEL               BIT(9)                            /*!< PE9 pin selection */
#define EVIC_GRPECFG_PE10SEL              BIT(10)                           /*!< PE10 pin selection */
#define EVIC_GRPECFG_PE11SEL              BIT(11)                           /*!< PE11 pin selection */
#define EVIC_GRPECFG_PE12SEL              BIT(12)                           /*!< PE12 pin selection */
#define EVIC_GRPECFG_PE13SEL              BIT(13)                           /*!< PE13 pin selection */
#define EVIC_GRPECFG_PE14SEL              BIT(14)                           /*!< PE14 pin selection */

/* EVIC_GRPEDH */
#define EVIC_GRPE_DH                      BITS(0,6)                         /*!< Group E holding data */

/* EVIC_GRPFCFG */
#define EVIC_GRPFCFG_GRPFIND              EVIC_GRPECFG_GRPEIND              /*!< Group F input detection */
#define EVIC_GRPFCFG_GRPFOSEL             EVIC_GRPECFG_GRPEOSEL             /*!< Group F output selection */
#define EVIC_GRPFCFG_OVWEN                EVIC_GRPECFG_OVWEN                /*!< EVIC_GRPFDH register overwrite enable */
#define EVIC_GRPFCFG_PF8SEL               EVIC_GRPECFG_PE8SEL               /*!< PF8 pin selection */
#define EVIC_GRPFCFG_PF9SEL               EVIC_GRPECFG_PE9SEL               /*!< PF9 pin selection */
#define EVIC_GRPFCFG_PF10SEL              EVIC_GRPECFG_PE10SEL              /*!< PF10 pin selection */
#define EVIC_GRPFCFG_PF11SEL              EVIC_GRPECFG_PE11SEL              /*!< PF11 pin selection */
#define EVIC_GRPFCFG_PF12SEL              EVIC_GRPECFG_PE12SEL              /*!< PF12 pin selection */
#define EVIC_GRPFCFG_PF13SEL              EVIC_GRPECFG_PE13SEL              /*!< PF13 pin selection */
#define EVIC_GRPFCFG_PF14SEL              EVIC_GRPECFG_PE14SEL              /*!< PF14 pin selection */

/* EVIC_GRPFDH */
#define EVIC_GRPF_DH                      EVIC_GRPE_DH                      /*!< Group F holding data */

/* constants definitions */
/* Event source definitions */
typedef enum {
    EVIC_SOURCE_DISABLED                                 = ((uint8_t)0x00U),                /*!< Event signal output is disabled */
    EVIC_SOURCE_SOFTWARE                                 = ((uint8_t)0x01U),                /*!< Software generation event */
    EVIC_SOURCE_SGIO_INPUT_DETECTION0                    = ((uint8_t)0x02U),                /*!< Single I/O input detection 0 */
    EVIC_SOURCE_SGIO_INPUT_DETECTION1                    = ((uint8_t)0x03U),                /*!< Single I/O input detection 1 */
    EVIC_SOURCE_SGIO_INPUT_DETECTION2                    = ((uint8_t)0x04U),                /*!< Single I/O input detection 2 */
    EVIC_SOURCE_SGIO_INPUT_DETECTION3                    = ((uint8_t)0x05U),                /*!< Single I/O input detection 3 */
    EVIC_SOURCE_GRPE_INPUT_DETECTION                     = ((uint8_t)0x06U),                /*!< Group E I/O input detection */
    EVIC_SOURCE_GRPF_INPUT_DETECTION                     = ((uint8_t)0x07U),                /*!< Group F I/O input detection */
    EVIC_SOURCE_TIMER0_OVERFLOW                          = ((uint8_t)0x08U),                /*!< TIMER0 overflow event */
    EVIC_SOURCE_TIMER0_UNDERFLOW                         = ((uint8_t)0x09U),                /*!< TIMER0 underflow event */
    EVIC_SOURCE_TIMER0_CH0_COMPARE                       = ((uint8_t)0x0AU),                /*!< TIMER0_CH0 compare event */
    EVIC_SOURCE_TIMER0_CH1_COMPARE                       = ((uint8_t)0x0BU),                /*!< TIMER0_CH1 compare event */
    EVIC_SOURCE_TIMER0_CH2_COMPARE                       = ((uint8_t)0x0CU),                /*!< TIMER0_CH2 compare event */
    EVIC_SOURCE_TIMER0_CH3_COMPARE                       = ((uint8_t)0x0DU),                /*!< TIMER0_CH3 compare event */
    EVIC_SOURCE_TIMER0_MCH0_COMPARE                      = ((uint8_t)0x0EU),                /*!< TIMER0_MCH0 compare event */
    EVIC_SOURCE_TIMER0_MCH1_COMPARE                      = ((uint8_t)0x0FU),                /*!< TIMER0_MCH1 compare event */
    EVIC_SOURCE_TIMER0_MCH2_COMPARE                      = ((uint8_t)0x10U),                /*!< TIMER0_MCH2 compare event */
    EVIC_SOURCE_TIMER0_MCH3_COMPARE                      = ((uint8_t)0x11U),                /*!< TIMER0_MCH3 compare event */
    EVIC_SOURCE_TIMER0_TRGO                              = ((uint8_t)0x12U),                /*!< TIMER0 TRGO signal */
    EVIC_SOURCE_TIMER7_OVERFLOW                          = ((uint8_t)0x13U),                /*!< TIMER7 overflow event */
    EVIC_SOURCE_TIMER7_UNDERFLOW                         = ((uint8_t)0x14U),                /*!< TIMER7 underflow event */
    EVIC_SOURCE_TIMER7_CH0_COMPARE                       = ((uint8_t)0x15U),                /*!< TIMER7_CH0 compare event */
    EVIC_SOURCE_TIMER7_CH1_COMPARE                       = ((uint8_t)0x16U),                /*!< TIMER7_CH1 compare event */
    EVIC_SOURCE_TIMER7_CH2_COMPARE                       = ((uint8_t)0x17U),                /*!< TIMER7_CH2 compare event */
    EVIC_SOURCE_TIMER7_CH3_COMPARE                       = ((uint8_t)0x18U),                /*!< TIMER7_CH3 compare event */
    EVIC_SOURCE_TIMER7_MCH0_COMPARE                      = ((uint8_t)0x19U),                /*!< TIMER7_MCH0 compare event */
    EVIC_SOURCE_TIMER7_MCH1_COMPARE                      = ((uint8_t)0x1AU),                /*!< TIMER7_MCH1 compare event */
    EVIC_SOURCE_TIMER7_MCH2_COMPARE                      = ((uint8_t)0x1BU),                /*!< TIMER7_MCH2 compare event */
    EVIC_SOURCE_TIMER7_MCH3_COMPARE                      = ((uint8_t)0x1CU),                /*!< TIMER7_MCH3 compare event */
    EVIC_SOURCE_TIMER7_TRGO                              = ((uint8_t)0x1DU),                /*!< TIMER7 TRGO signal */
    EVIC_SOURCE_TIMER1_CH0_COMPARE                       = ((uint8_t)0x1EU),                /*!< TIMER1_CH0 compare event */
    EVIC_SOURCE_TIMER1_CH1_COMPARE                       = ((uint8_t)0x1FU),                /*!< TIMER1_CH1 compare event */
    EVIC_SOURCE_TIMER1_CH2_COMPARE                       = ((uint8_t)0x20U),                /*!< TIMER1_CH2 compare event */
    EVIC_SOURCE_TIMER1_CH3_COMPARE                       = ((uint8_t)0x21U),                /*!< TIMER1_CH3 compare event */
    EVIC_SOURCE_TIMER1_OVERFLOW                          = ((uint8_t)0x22U),                /*!< TIMER1 overflow event */
    EVIC_SOURCE_TIMER1_UNDERFLOW                         = ((uint8_t)0x23U),                /*!< TIMER1 underflow event */
    EVIC_SOURCE_TIMER1_TRGO                              = ((uint8_t)0x24U),                /*!< TIMER1 TRGO signal */
    EVIC_SOURCE_TIMER2_CH0_COMPARE                       = ((uint8_t)0x25U),                /*!< TIMER2_CH0 compare event */
    EVIC_SOURCE_TIMER2_CH1_COMPARE                       = ((uint8_t)0x26U),                /*!< TIMER2_CH1 compare event */
    EVIC_SOURCE_TIMER2_CH2_COMPARE                       = ((uint8_t)0x27U),                /*!< TIMER2_CH2 compare event */
    EVIC_SOURCE_TIMER2_CH3_COMPARE                       = ((uint8_t)0x28U),                /*!< TIMER2_CH3 compare event */
    EVIC_SOURCE_TIMER2_OVERFLOW                          = ((uint8_t)0x29U),                /*!< TIMER2 overflow event */
    EVIC_SOURCE_TIMER2_UNDERFLOW                         = ((uint8_t)0x2AU),                /*!< TIMER2 underflow event */
    EVIC_SOURCE_TIMER2_TRGO                              = ((uint8_t)0x2BU),                /*!< TIMER2 TRGO signal */
    EVIC_SOURCE_CPTIMER0_COUNTER0_OVERFLOW               = ((uint8_t)0x2CU),                /*!< CPTIMER0 counter 0 overflow event */
    EVIC_SOURCE_CPTIMERW_OCH2_COMPARE_MATCH              = ((uint8_t)0x2EU),                /*!< CPTIMERW_OCH2 compare match event */
    EVIC_SOURCE_CPTIMERW_OCH3_COMPARE_MATCH              = ((uint8_t)0x2FU),                /*!< CPTIMERW_OCH3 compare match event */
    EVIC_SOURCE_CPTIMERW_OCH0_COMPARE_MATCH              = ((uint8_t)0x30U),                /*!< CPTIMERW_OCH0 compare match event */
    EVIC_SOURCE_CPTIMERW_OCH1_COMPARE_MATCH              = ((uint8_t)0x31U),                /*!< CPTIMERW_OCH1 compare match event */
    EVIC_SOURCE_GPTIMER0_CH0_COMPARE_MATCH               = ((uint8_t)0x35U),                /*!< GPTIMER0_CH0 compare match event */
    EVIC_SOURCE_GPTIMER0_CH1_COMPARE_MATCH               = ((uint8_t)0x36U),                /*!< GPTIMER0_CH1 compare match event */
    EVIC_SOURCE_GPTIMER0_CH0_ADD_COMPARE_MATCH           = ((uint8_t)0x37U),                /*!< GPTIMER0_CH0 addition compare match event */
    EVIC_SOURCE_GPTIMER0_CH1_ADD_COMPARE_MATCH           = ((uint8_t)0x38U),                /*!< GPTIMER0_CH1 addition compare match event */
    EVIC_SOURCE_GPTIMER0_OVERFLOW                        = ((uint8_t)0x39U),                /*!< GPTIMER0 overflow event */
    EVIC_SOURCE_GPTIMER0_UNDERFLOW                       = ((uint8_t)0x3AU),                /*!< GPTIMER0 underflow event */
    EVIC_SOURCE_GPTIMER0_ADTCV1_MATCH                    = ((uint8_t)0x3BU),                /*!< GPTIMER0 ADTCV1 match event */
    EVIC_SOURCE_GPTIMER0_ADTCV2_MATCH                    = ((uint8_t)0x3CU),                /*!< GPTIMER0 ADTCV2 match event */
    EVIC_SOURCE_GPTIMER0_REPEAT_COUNT_END                = ((uint8_t)0x3DU),                /*!< GPTIMER0 end of repeat count event */
    EVIC_SOURCE_CMP0_OUT                                 = ((uint8_t)0x40U),                /*!< CMP0 output signal */
    EVIC_SOURCE_CMP1_OUT                                 = ((uint8_t)0x41U),                /*!< CMP1 output signal */
    EVIC_SOURCE_CMP2_OUT                                 = ((uint8_t)0x42U),                /*!< CMP2 output signal */
    EVIC_SOURCE_CMP3_OUT                                 = ((uint8_t)0x43U),                /*!< CMP3 output signal */
    EVIC_SOURCE_ADC0_GRP_SCAN_COMPLETE                   = ((uint8_t)0x44U),                /*!< ADC0 group scan complete event */
    EVIC_SOURCE_ADC2_GRP_SCAN_COMPLETE                   = ((uint8_t)0x45U),                /*!< ADC2 group scan complete event */
    EVIC_SOURCE_LVD1_VOLTAGE_DETECTION                   = ((uint8_t)0x46U),                /*!< LVD1 voltage detection */
    EVIC_SOURCE_LVD2_VOLTAGE_DETECTION                   = ((uint8_t)0x47U),                /*!< LVD2 voltage detection */
    EVIC_SOURCE_FWDGT_UNDERFLOW_OR_REFRESH               = ((uint8_t)0x48U),                /*!< FWDGT underflow or refresh */
    EVIC_SOURCE_HXTAL_STUCK                              = ((uint8_t)0x49U),                /*!< HXTAL stuck event */
    EVIC_SOURCE_DMA0_CH0_TRANSFER_FINISH                 = ((uint8_t)0x4AU),                /*!< DMA0 channel 0 full transfer finish event */
    EVIC_SOURCE_DMA0_CH1_TRANSFER_FINISH                 = ((uint8_t)0x4BU),                /*!< DMA0 channel 1 full transfer finish event */
    EVIC_SOURCE_DMA0_CH2_TRANSFER_FINISH                 = ((uint8_t)0x4CU),                /*!< DMA0 channel 2 full transfer finish event */
    EVIC_SOURCE_DMA0_CH3_TRANSFER_FINISH                 = ((uint8_t)0x4DU),                /*!< DMA0 channel 3 full transfer finish event */
    EVIC_SOURCE_DMA0_CH4_TRANSFER_FINISH                 = ((uint8_t)0x4EU),                /*!< DMA0 channel 4 full transfer finish event */
    EVIC_SOURCE_DMA0_CH5_TRANSFER_FINISH                 = ((uint8_t)0x4FU),                /*!< DMA0 channel 5 full transfer finish event */
    EVIC_SOURCE_DMA1_CH0_TRANSFER_FINISH                 = ((uint8_t)0x50U),                /*!< DMA1 channel 0 full transfer finish event */
    EVIC_SOURCE_DMA1_CH1_TRANSFER_FINISH                 = ((uint8_t)0x51U),                /*!< DMA1 channel 1 full transfer finish event */
    EVIC_SOURCE_DMA1_CH2_TRANSFER_FINISH                 = ((uint8_t)0x52U),                /*!< DMA1 channel 2 full transfer finish event */
    EVIC_SOURCE_DMA1_CH3_TRANSFER_FINISH                 = ((uint8_t)0x53U),                /*!< DMA1 channel 3 full transfer finish event */
    EVIC_SOURCE_DMA1_CH4_TRANSFER_FINISH                 = ((uint8_t)0x54U),                /*!< DMA1 channel 4 full transfer finish event */
    EVIC_SOURCE_DMA1_CH5_TRANSFER_FINISH                 = ((uint8_t)0x55U),                /*!< DMA1 channel 5 full transfer finish event */
    EVIC_SOURCE_CAN_TRANSMIT_INT                         = ((uint8_t)0x56U),                /*!< CAN transmit interrupt event */
    EVIC_SOURCE_CAN_FIFO0_INT                            = ((uint8_t)0x57U),                /*!< CAN FIFO0 interrupt event */
    EVIC_SOURCE_CAN_FIFO1_INT                            = ((uint8_t)0x58U),                /*!< CAN FIFO1 interrupt event */
    EVIC_SOURCE_CAN_EWMC_INT                             = ((uint8_t)0x59U),                /*!< CAN EWMC interrupt event */
    EVIC_SOURCE_UART0_ERROR                              = ((uint8_t)0x5CU),                /*!< UART0 error (PERR /FERR /NERR /ORERR) */
    EVIC_SOURCE_UART0_TRANSMIT_COMPLETE                  = ((uint8_t)0x5DU),                /*!< UART0 transmission complete */
    EVIC_SOURCE_UART1_ERROR                              = ((uint8_t)0x5EU),                /*!< UART1 error (PERR /FERR /NERR /ORERR) */
    EVIC_SOURCE_UART1_TRANSMIT_COMPLETE                  = ((uint8_t)0x5FU),                /*!< UART1 transmission complete */
    EVIC_SOURCE_UART2_ERROR                              = ((uint8_t)0x60U),                /*!< UART2 error (PERR /FERR /NERR /ORERR) */
    EVIC_SOURCE_UART2_TRANSMIT_COMPLETE                  = ((uint8_t)0x61U),                /*!< UART2 transmission complete */
    EVIC_SOURCE_UART3_ERROR                              = ((uint8_t)0x62U),                /*!< UART3 error (PERR /FERR /NERR /ORERR) */
    EVIC_SOURCE_UART3_TRANSMIT_COMPLETE                  = ((uint8_t)0x63U),                /*!< UART3 transmission complete */
    EVIC_SOURCE_SPI_ERROR                                = ((uint8_t)0x67U),                /*!< SPI error */
    EVIC_SOURCE_SPI_COMMUNICATION_COMPLETE               = ((uint8_t)0x68U),                /*!< SPI transfer complete event */
    EVIC_SOURCE_I2C_COMMUNICATION_ERROR_OR_EVENT         = ((uint8_t)0x69U),                /*!< I2C communication error/communication event */
    EVIC_SOURCE_I2C_RECEIVE_DATA_NOT_EMPTY               = ((uint8_t)0x6AU),                /*!< I2C_RDATA is not empty during receiving */
    EVIC_SOURCE_I2C_TRANSMIT_INT                         = ((uint8_t)0x6BU),                /*!< I2C transmit interrupt event */
    EVIC_SOURCE_I2C_TRANSFER_COMPLETE                    = ((uint8_t)0x6CU),                /*!< I2C transfer complete event */
    EVIC_SOURCE_GPTIMER1_CH0_COMPARE_MATCH               = ((uint8_t)0x6DU),                /*!< GPTIMER1_CH0 compare match event */
    EVIC_SOURCE_GPTIMER1_CH1_COMPARE_MATCH               = ((uint8_t)0x6EU),                /*!< GPTIMER1_CH1 compare match event */
    EVIC_SOURCE_GPTIMER1_CH0_ADD_COMPARE_MATCH           = ((uint8_t)0x6FU),                /*!< GPTIMER1_CH0 addition compare match event */
    EVIC_SOURCE_GPTIMER1_CH1_ADD_COMPARE_MATCH           = ((uint8_t)0x70U),                /*!< GPTIMER1_CH1 addition compare match event */
    EVIC_SOURCE_GPTIMER1_OVERFLOW                        = ((uint8_t)0x71U),                /*!< GPTIMER1 overflow event */
    EVIC_SOURCE_GPTIMER1_UNDERFLOW                       = ((uint8_t)0x72U),                /*!< GPTIMER1 underflow event */
    EVIC_SOURCE_GPTIMER1_ADTCV1_MATCH                    = ((uint8_t)0x73U),                /*!< GPTIMER1 ADTCV1 match event */
    EVIC_SOURCE_GPTIMER1_ADTCV2_MATCH                    = ((uint8_t)0x74U),                /*!< GPTIMER1 ADTCV2 match event */
    EVIC_SOURCE_GPTIMER1_REPEAT_COUNT_END                = ((uint8_t)0x75U),                /*!< GPTIMER1 end of repeat count event */
} event_source_enum;

/* target peripheral definitions */
typedef enum {
    EVENT_INTERCONNECT_SGIO0                             = ((uint8_t)0x04U),                /*!< single I/O 0 */
    EVENT_INTERCONNECT_SGIO1                             = ((uint8_t)0x08U),                /*!< single I/O 1 */
    EVENT_INTERCONNECT_SGIO2                             = ((uint8_t)0x0CU),                /*!< single I/O 2 */
    EVENT_INTERCONNECT_SGIO3                             = ((uint8_t)0x10U),                /*!< single I/O 3 */
    EVENT_INTERCONNECT_INGRPE                            = ((uint8_t)0x14U),                /*!< input group E */
    EVENT_INTERCONNECT_INGRPF                            = ((uint8_t)0x18U),                /*!< input group F */
    EVENT_INTERCONNECT_OUTGRPE                           = ((uint8_t)0x1CU),                /*!< output group E */
    EVENT_INTERCONNECT_OUTGRPF                           = ((uint8_t)0x20U),                /*!< output group F */
    EVENT_INTERCONNECT_DAC0_OUT0_COV                     = ((uint8_t)0x24U),                /*!< DAC0_OUT0 conversion */
    EVENT_INTERCONNECT_DAC0_OUT1_COV                     = ((uint8_t)0x25U),                /*!< DAC0_OUT1 conversion */
    EVENT_INTERCONNECT_ADC0_GRP_EXTRIG0                  = ((uint8_t)0x28U),                /*!< ADC0 group external trigger 0 */
    EVENT_INTERCONNECT_ADC0_GRP_EXTRIG1                  = ((uint8_t)0x29U),                /*!< ADC0 group external trigger 1 */
    EVENT_INTERCONNECT_ADC2_GRP_EXTRIG0                  = ((uint8_t)0x2CU),                /*!< ADC2 group external trigger 0 */
    EVENT_INTERCONNECT_ADC2_GRP_EXTRIG1                  = ((uint8_t)0x2DU),                /*!< ADC2 group external trigger 1 */
    EVENT_INTERCONNECT_RCU                               = ((uint8_t)0x34U),                /*!< clock switch to IRC32M */
    EVENT_INTERCONNECT_TIMER0                            = ((uint8_t)0x38U),                /*!< TIMER0 */
    EVENT_INTERCONNECT_TIMER7                            = ((uint8_t)0x3CU),                /*!< TIMER7 */
    EVENT_INTERCONNECT_CPTIMER0                          = ((uint8_t)0x40U),                /*!< CPTIMER0 */
    EVENT_INTERCONNECT_CPTIMERW                          = ((uint8_t)0x44U),                /*!< CPTIMERW */
    EVENT_INTERCONNECT_TIMER1                            = ((uint8_t)0x48U),                /*!< TIMER1 */
    EVENT_INTERCONNECT_TIMER2                            = ((uint8_t)0x4CU),                /*!< TIMER2 */
    EVENT_INTERCONNECT_GPTIMER_TRIGIN0                   = ((uint8_t)0x50U),                /*!< GPTIMER trigger input 0 */
    EVENT_INTERCONNECT_GPTIMER_TRIGIN1                   = ((uint8_t)0x51U),                /*!< GPTIMER trigger input 1 */
    EVENT_INTERCONNECT_GPTIMER_TRIGIN2                   = ((uint8_t)0x54U),                /*!< GPTIMER trigger input 2 */
    EVENT_INTERCONNECT_GPTIMER_TRIGIN3                   = ((uint8_t)0x55U),                /*!< GPTIMER trigger input 3 */
    EVENT_INTERCONNECT_GPTIMER_TRIGIN4                   = ((uint8_t)0x58U),                /*!< GPTIMER trigger input 4 */
    EVENT_INTERCONNECT_GPTIMER_TRIGIN5                   = ((uint8_t)0x59U),                /*!< GPTIMER trigger input 5 */
    EVENT_INTERCONNECT_GPTIMER_TRIGIN6                   = ((uint8_t)0x5CU),                /*!< GPTIMER trigger input 6 */
    EVENT_INTERCONNECT_GPTIMER_TRIGIN7                   = ((uint8_t)0x5DU),                /*!< GPTIMER trigger input 7 */
    EVENT_INTERCONNECT_DAC0_OUT0_EN                      = ((uint8_t)0x60U),                /*!< DAC0_OUT0 enable */
    EVENT_INTERCONNECT_DAC0_OUT1_EN                      = ((uint8_t)0x61U),                /*!< DAC0_OUT1 enable */
    EVENT_INTERCONNECT_DMAMUX_0                          = ((uint8_t)0x64U),                /*!< DMAMUX multiplexer input 0 */
    EVENT_INTERCONNECT_DMAMUX_1                          = ((uint8_t)0x65U),                /*!< DMAMUX multiplexer input 1 */
    EVENT_INTERCONNECT_DMAMUX_2                          = ((uint8_t)0x68U),                /*!< DMAMUX multiplexer input 2 */
    EVENT_INTERCONNECT_DMAMUX_3                          = ((uint8_t)0x69U),                /*!< DMAMUX multiplexer input 3 */
    EVENT_INTERCONNECT_DMAMUX_4                          = ((uint8_t)0x6CU),                /*!< DMAMUX multiplexer input 4 */
    EVENT_INTERCONNECT_DMAMUX_5                          = ((uint8_t)0x6DU),                /*!< DMAMUX multiplexer input 5 */
    EVENT_INTERCONNECT_DMAMUX_6                          = ((uint8_t)0x70U),                /*!< DMAMUX multiplexer input 6 */
    EVENT_INTERCONNECT_DMAMUX_7                          = ((uint8_t)0x71U),                /*!< DMAMUX multiplexer input 7 */
    EVENT_INTERCONNECT_DMAMUX_8                          = ((uint8_t)0x74U),                /*!< DMAMUX multiplexer input 8 */
    EVENT_INTERCONNECT_DMAMUX_9                          = ((uint8_t)0x75U),                /*!< DMAMUX multiplexer input 9 */
    EVENT_INTERCONNECT_DMAMUX_10                         = ((uint8_t)0x78U),                /*!< DMAMUX multiplexer input 10 */
    EVENT_INTERCONNECT_DMAMUX_11                         = ((uint8_t)0x79U),                /*!< DMAMUX multiplexer input 11 */
} evic_periph_enum;

/* slave mode selection */
#define EVIC_COUNTER_ENABLE                              (0x00U)                            /*!< Counter is enabled */
#define EVIC_COUNTER_RESTART                             (0x01U)                            /*!< Counter is restarted */
#define EVIC_EVENT_COUNT                                 (0x02U)                            /*!< Event count */
#define EVIC_EVENT_TRIGGER_DISABLE                       (0x03U)                            /*!< Event trigger is disabled */

/* single I/O mode */
#define SGIOM(regval)                                    (BITS(5,6) & ((uint32_t)(regval) << 5))
#define EVIC_SGIO_DETECTION_RISING                       SGIOM(0)                           /*!< Generate event when single I/O input rising edge */
#define EVIC_SGIO_DETECTION_FALLING                      SGIOM(1)                           /*!< Generate event when single I/O input falling edge */
#define EVIC_SGIO_DETECTION_BOTH_EDGE                    SGIOM(2)                           /*!< Generate event when single I/O input both edges */
#define EVIC_SGIO_OUTPUT_LOW                             SGIOM(0)                           /*!< single I/O output low level when event comes */
#define EVIC_SGIO_OUTPUT_HIGH                            SGIOM(1)                           /*!< single I/O output high level when event comes */
#define EVIC_SGIO_OUTPUT_INVERTED                        SGIOM(2)                           /*!< single I/O output inverted level when event comes */

/* single I/O pin */
#define SGIOPIN(regval)                                 (BITS(2,4) & ((uint32_t)(regval) << 2))
#define EVIC_SGIO_PIN_8                                 SGIOPIN(0)                          /*!< single I/O pin 8 is selected */
#define EVIC_SGIO_PIN_9                                 SGIOPIN(1)                          /*!< single I/O pin 9 is selected */
#define EVIC_SGIO_PIN_10                                SGIOPIN(2)                          /*!< single I/O pin 10 is selected */
#define EVIC_SGIO_PIN_11                                SGIOPIN(3)                          /*!< single I/O pin 11 is selected */
#define EVIC_SGIO_PIN_12                                SGIOPIN(4)                          /*!< single I/O pin 12 is selected */
#define EVIC_SGIO_PIN_13                                SGIOPIN(5)                          /*!< single I/O pin 13 is selected */
#define EVIC_SGIO_PIN_14                                SGIOPIN(6)                          /*!< single I/O pin 14 is selected */

/* single I/O port */
#define EVIC_SGIO_PORT_E                                (0x00U)                             /*!< single I/O port E is selected */
#define EVIC_SGIO_PORT_F                                (0x01U)                             /*!< single I/O port F is selected */

/* group I/O pin */
#define EVIC_GRPIO_PIN_8                                 EVIC_GRPFCFG_PF8SEL                /*!< group I/O pin 8 is selected */
#define EVIC_GRPIO_PIN_9                                 EVIC_GRPFCFG_PF9SEL                /*!< group I/O pin 9 is selected */
#define EVIC_GRPIO_PIN_10                                EVIC_GRPFCFG_PF10SEL               /*!< group I/O pin 10 is selected */
#define EVIC_GRPIO_PIN_11                                EVIC_GRPFCFG_PF11SEL               /*!< group I/O pin 11 is selected */
#define EVIC_GRPIO_PIN_12                                EVIC_GRPFCFG_PF12SEL               /*!< group I/O pin 12 is selected */
#define EVIC_GRPIO_PIN_13                                EVIC_GRPFCFG_PF13SEL               /*!< group I/O pin 13 is selected */
#define EVIC_GRPIO_PIN_14                                EVIC_GRPFCFG_PF14SEL               /*!< group I/O pin 14 is selected */

/* group I/O port */
#define EVIC_GRPIO_PORT_E                                (0x00U)                            /*!< group I/O port E is selected */
#define EVIC_GRPIO_PORT_F                                (0x01U)                            /*!< group I/O port F is selected */

/* group I/O output select */
#define GRPxOSEL(regval)                                (BITS(2,4) & ((uint32_t)(regval) << 2))
#define EVIC_GRPIO_OUTPUT_LOW                           GRPxOSEL(0)                         /*!< group I/O output low level when event comes */
#define EVIC_GRPIO_OUTPUT_HIGH                          GRPxOSEL(1)                         /*!< group I/O output high level when event comes */
#define EVIC_GRPIO_OUTPUT_INVERTED                      GRPxOSEL(2)                         /*!< group I/O output inverted level when event comes */
#define EVIC_GRPIO_OUTPUT_DATA                          GRPxOSEL(3)                         /*!< group I/O output holding data when event comes */
#define EVIC_GRPIO_OUTPUT_CIRCULAR_DATA                 GRPxOSEL(4)                         /*!< group I/O circularly shift output holding data when event comes */

/* group I/O input detection edge */
#define EVIC_GRPIO_DETECTION_RISING                      (0x00U)                            /*!< Generate event when group I/O input rising edge */
#define EVIC_GRPIO_DETECTION_FALLING                     (0x01U)                            /*!< Generate event when group I/O input falling edge */
#define EVIC_GRPIO_DETECTION_BOTH_EDGE                   (0x02U)                            /*!< Generate event when group I/O input both edges */

/* CPTIMERW and CPTIMER0 peripheral */
typedef enum {
    TARGET_CPTIMERW = 0,                                                                    /*!< CPTIMERW */
    TARGET_CPTIMER0                                                                         /*!< CPTIMER0 */
} evic_cptimer_enum;

/* Single I/O instance*/
typedef enum {
    SGIO0 = 0,                                                                              /*!< Single I/O 0 */
    SGIO1,                                                                                  /*!< Single I/O 1 */
    SGIO2,                                                                                  /*!< Single I/O 2 */
    SGIO3,                                                                                  /*!< Single I/O 3 */
} evic_single_io_enum;

/* function declarations */
/* set the event source for target peripheral */
void evic_init(evic_periph_enum target_periph, event_source_enum event_source);
/* get the trigger input signal for target peripheral */
event_source_enum evic_event_source_get(evic_periph_enum target_periph);
/* lock the event interconnect register */
void evic_register_lock_set(evic_periph_enum target_periph);
/* get the event interconnect register lock status */
FlagStatus evic_register_lock_get(evic_periph_enum target_periph);

/* select CPTIMERW or CPTIMER0 slave mode */
void evic_cptimer_slave_mode_select(evic_cptimer_enum cptimer_periph, uint32_t slavemode);

/* configure evic group member */
void evic_group_member_config(uint32_t group_pin, uint32_t group_port, ControlStatus newvalue);
/* configure evic group input detection edge */
void evic_group_edge_detection_config(uint32_t group_edge, uint32_t group_port);
/* configure evic group output level */
void evic_group_output_level_config(uint32_t group_level, uint32_t group_port);
/* enable evic group overwrite function */
void evic_group_overwrite_enable(uint32_t group_port);
/* disable evic group overwrite function */
void evic_group_overwrite_disable(uint32_t group_port);

/* set group holding data value */
void evic_data_set(uint8_t data, uint32_t group_port);
/* get group holding data value */
uint8_t evic_data_get(uint32_t group_port);

/* configure evic single I/O */
void evic_single_io_config(uint32_t single_pin, uint32_t single_port, evic_single_io_enum single_io);
/* configure evic single I/O input detection edge */
void evic_single_io_edge_detection_config(uint32_t single_edge, evic_single_io_enum single_io);
/* configure evic single I/O output level */
void evic_single_io_output_level_config(uint32_t single_level, evic_single_io_enum single_io);

/* enable software event register write */
void evic_register_write_enable(void);
/* disable software event register write */
void evic_register_write_disable(void);
/* get software event register write enable status */
FlagStatus evic_register_write_enable_get(void);
/* enable software event generation bit write */
void evic_bit_write_enable(void);
/* disable software event generation bit write */
void evic_bit_write_disable(void);
/* get software event generation bit write enable status */
FlagStatus evic_bit_write_enable_get(void);
/* evic software event generation */
void evic_software_event_generation(void);

#endif /* GD32M53X_EVIC_H */
