/*!
    \file    gd32m53x_evic.c
    \brief   EVIC driver

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

#include "gd32m53x_evic.h"

/* EVIC input parameter mask */
#define GROUP_PIN_MASK         ((uint32_t)0x00007F00U)     /*!< EVIC group pin mask */

/* EVIC target register redefine */
#define EVIC_TARGET_REG(target_periph)           (REG32(EVIC + ((uint32_t)(target_periph) & BITS(2,31))))               /*!< target peripheral register */
#define EVIC_TARGET_PERIPH_SHIFT(target_periph)  (((uint32_t)(target_periph) & BITS(0,1)) << 3U)                        /*!< bit offset in target peripheral register */
#define EVIC_TARGET_PERIPH_MASK(target_periph)   ((uint32_t)(BITS(0,7) << EVIC_TARGET_PERIPH_SHIFT(target_periph)))     /*!< bit mask in target peripheral register */

/*!
    \brief      set the event source for target peripheral (API_ID(0x0001U))
    \param[in]  target_periph: target peripheral value
      \arg        EVENT_INTERCONNECT_SGIO0: single I/O 0
      \arg        EVENT_INTERCONNECT_SGIO1: single I/O 1
      \arg        EVENT_INTERCONNECT_SGIO2: single I/O 2
      \arg        EVENT_INTERCONNECT_SGIO3: single I/O 3
      \arg        EVENT_INTERCONNECT_INGRPE: input group E
      \arg        EVENT_INTERCONNECT_INGRPF: input group F
      \arg        EVENT_INTERCONNECT_OUTGRPE: output group E
      \arg        EVENT_INTERCONNECT_OUTGRPF: output group F
      \arg        EVENT_INTERCONNECT_DAC0_OUT0_COV: DAC0_OUT0 conversion
      \arg        EVENT_INTERCONNECT_DAC0_OUT1_COV: DAC0_OUT1 conversion
      \arg        EVENT_INTERCONNECT_ADC0_GRP_EXTRIG0: ADC0 group external trigger 0
      \arg        EVENT_INTERCONNECT_ADC0_GRP_EXTRIG1: ADC0 group external trigger 1
      \arg        EVENT_INTERCONNECT_ADC2_GRP_EXTRIG0: ADC2 group external trigger 0
      \arg        EVENT_INTERCONNECT_ADC2_GRP_EXTRIG1: ADC2 group external trigger 1
      \arg        EVENT_INTERCONNECT_RCU: clock switch to IRC32M
      \arg        EVENT_INTERCONNECT_TIMER0: TIMER0
      \arg        EVENT_INTERCONNECT_TIMER7: TIMER7
      \arg        EVENT_INTERCONNECT_CPTIMER0: CPTIMER0
      \arg        EVENT_INTERCONNECT_CPTIMERW: CPTIMERW
      \arg        EVENT_INTERCONNECT_TIMER1: TIMER1
      \arg        EVENT_INTERCONNECT_TIMER2: TIMER2
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN0: GPTIMER trigger input 0
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN1: GPTIMER trigger input 1
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN2: GPTIMER trigger input 2
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN3: GPTIMER trigger input 3
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN4: GPTIMER trigger input 4
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN5: GPTIMER trigger input 5
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN6: GPTIMER trigger input 6
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN7: GPTIMER trigger input 7
      \arg        EVENT_INTERCONNECT_DAC0_OUT0_EN: DAC0_OUT0 enable
      \arg        EVENT_INTERCONNECT_DAC0_OUT1_EN: DAC0_OUT1 enable
      \arg        EVENT_INTERCONNECT_DMAMUX_0: DMAMUX multiplexer input 0
      \arg        EVENT_INTERCONNECT_DMAMUX_1: DMAMUX multiplexer input 1
      \arg        EVENT_INTERCONNECT_DMAMUX_2: DMAMUX multiplexer input 2
      \arg        EVENT_INTERCONNECT_DMAMUX_3: DMAMUX multiplexer input 3
      \arg        EVENT_INTERCONNECT_DMAMUX_4: DMAMUX multiplexer input 4
      \arg        EVENT_INTERCONNECT_DMAMUX_5: DMAMUX multiplexer input 5
      \arg        EVENT_INTERCONNECT_DMAMUX_6: DMAMUX multiplexer input 6
      \arg        EVENT_INTERCONNECT_DMAMUX_7: DMAMUX multiplexer input 7
      \arg        EVENT_INTERCONNECT_DMAMUX_8: DMAMUX multiplexer input 8
      \arg        EVENT_INTERCONNECT_DMAMUX_9: DMAMUX multiplexer input 9
      \arg        EVENT_INTERCONNECT_DMAMUX_10: DMAMUX multiplexer input 10
      \arg        EVENT_INTERCONNECT_DMAMUX_11: DMAMUX multiplexer input 11
    \param[in]  event_source: event source value
      \arg        EVIC_SOURCE_DISABLED: Event signal output is disabled
      \arg        EVIC_SOURCE_SOFTWARE: Software generation event
      \arg        EVIC_SOURCE_SGIO_INPUT_DETECTION0: Single I/O input detection 0
      \arg        EVIC_SOURCE_SGIO_INPUT_DETECTION1: Single I/O input detection 1
      \arg        EVIC_SOURCE_SGIO_INPUT_DETECTION2: Single I/O input detection 2
      \arg        EVIC_SOURCE_SGIO_INPUT_DETECTION3: Single I/O input detection 3
      \arg        EVIC_SOURCE_GRPE_INPUT_DETECTION: Group E I/O input detection
      \arg        EVIC_SOURCE_GRPF_INPUT_DETECTION: Group F I/O input detection
      \arg        EVIC_SOURCE_TIMER0_OVERFLOW: TIMER0 overflow event
      \arg        EVIC_SOURCE_TIMER0_UNDERFLOW: TIMER0 underflow event
      \arg        EVIC_SOURCE_TIMER0_CH0_COMPARE: TIMER0_CH0 compare event
      \arg        EVIC_SOURCE_TIMER0_CH1_COMPARE: TIMER0_CH1 compare event
      \arg        EVIC_SOURCE_TIMER0_CH2_COMPARE: TIMER0_CH2 compare event
      \arg        EVIC_SOURCE_TIMER0_CH3_COMPARE: TIMER0_CH3 compare event
      \arg        EVIC_SOURCE_TIMER0_MCH0_COMPARE: TIMER0_MCH0 compare event
      \arg        EVIC_SOURCE_TIMER0_MCH1_COMPARE: TIMER0_MCH1 compare event
      \arg        EVIC_SOURCE_TIMER0_MCH2_COMPARE: TIMER0_MCH2 compare event
      \arg        EVIC_SOURCE_TIMER0_MCH3_COMPARE: TIMER0_MCH3 compare event
      \arg        EVIC_SOURCE_TIMER0_TRGO: TIMER0 TRGO signal
      \arg        EVIC_SOURCE_TIMER7_OVERFLOW: TIMER7 overflow event
      \arg        EVIC_SOURCE_TIMER7_UNDERFLOW: TIMER7 underflow event
      \arg        EVIC_SOURCE_TIMER7_CH0_COMPARE: TIMER7_CH0 compare event
      \arg        EVIC_SOURCE_TIMER7_CH1_COMPARE: TIMER7_CH1 compare event
      \arg        EVIC_SOURCE_TIMER7_CH2_COMPARE: TIMER7_CH2 compare event
      \arg        EVIC_SOURCE_TIMER7_CH3_COMPARE: TIMER7_CH3 compare event
      \arg        EVIC_SOURCE_TIMER7_MCH0_COMPARE: TIMER7_MCH0 compare event
      \arg        EVIC_SOURCE_TIMER7_MCH1_COMPARE: TIMER7_MCH1 compare event
      \arg        EVIC_SOURCE_TIMER7_MCH2_COMPARE: TIMER7_MCH2 compare event
      \arg        EVIC_SOURCE_TIMER7_MCH3_COMPARE: TIMER7_MCH3 compare event
      \arg        EVIC_SOURCE_TIMER7_TRGO: TIMER7 TRGO signal
      \arg        EVIC_SOURCE_TIMER1_CH0_COMPARE: TIMER1_CH0 compare event
      \arg        EVIC_SOURCE_TIMER1_CH1_COMPARE: TIMER1_CH1 compare event
      \arg        EVIC_SOURCE_TIMER1_CH2_COMPARE: TIMER1_CH2 compare event
      \arg        EVIC_SOURCE_TIMER1_CH3_COMPARE: TIMER1_CH3 compare event
      \arg        EVIC_SOURCE_TIMER1_OVERFLOW: TIMER1 overflow event
      \arg        EVIC_SOURCE_TIMER1_UNDERFLOW: TIMER1 underflow event
      \arg        EVIC_SOURCE_TIMER1_TRGO: TIMER1 TRGO signal
      \arg        EVIC_SOURCE_TIMER2_CH0_COMPARE: TIMER2_CH0 compare event
      \arg        EVIC_SOURCE_TIMER2_CH1_COMPARE: TIMER2_CH1 compare event
      \arg        EVIC_SOURCE_TIMER2_CH2_COMPARE: TIMER2_CH2 compare event
      \arg        EVIC_SOURCE_TIMER2_CH3_COMPARE: TIMER2_CH3 compare event
      \arg        EVIC_SOURCE_TIMER2_OVERFLOW: TIMER2 overflow event
      \arg        EVIC_SOURCE_TIMER2_UNDERFLOW: TIMER2 underflow event
      \arg        EVIC_SOURCE_TIMER2_TRGO: TIMER2 TRGO signal
      \arg        EVIC_SOURCE_CPTIMER0_COUNTER0_OVERFLOW: CPTIMER0 counter 0 overflow event
      \arg        EVIC_SOURCE_CPTIMERW_OCH2_COMPARE_MATCH: CPTIMERW_OCH2 compare match event
      \arg        EVIC_SOURCE_CPTIMERW_OCH3_COMPARE_MATCH: CPTIMERW_OCH3 compare match event
      \arg        EVIC_SOURCE_CPTIMERW_OCH0_COMPARE_MATCH: CPTIMERW_OCH0 compare match event
      \arg        EVIC_SOURCE_CPTIMERW_OCH1_COMPARE_MATCH: CPTIMERW_OCH1 compare match event
      \arg        EVIC_SOURCE_GPTIMER0_CH0_COMPARE_MATCH: GPTIMER0_CH0 compare match event
      \arg        EVIC_SOURCE_GPTIMER0_CH1_COMPARE_MATCH: GPTIMER0_CH1 compare match event
      \arg        EVIC_SOURCE_GPTIMER0_CH0_ADD_COMPARE_MATCH: GPTIMER0_CH0 addition compare match event
      \arg        EVIC_SOURCE_GPTIMER0_CH1_ADD_COMPARE_MATCH: GPTIMER0_CH1 addition compare match event
      \arg        EVIC_SOURCE_GPTIMER0_OVERFLOW: GPTIMER0 overflow event
      \arg        EVIC_SOURCE_GPTIMER0_UNDERFLOW: GPTIMER0 underflow event
      \arg        EVIC_SOURCE_GPTIMER0_ADTCV1_MATCH: GPTIMER0 ADTCV1 match event
      \arg        EVIC_SOURCE_GPTIMER0_ADTCV2_MATCH: GPTIMER0 ADTCV2 match event
      \arg        EVIC_SOURCE_GPTIMER0_REPEAT_COUNT_END: GPTIMER0 end of repeat count event
      \arg        EVIC_SOURCE_CMP0_OUT: CMP0 output signal
      \arg        EVIC_SOURCE_CMP1_OUT: CMP1 output signal
      \arg        EVIC_SOURCE_CMP2_OUT: CMP2 output signal
      \arg        EVIC_SOURCE_CMP3_OUT: CMP3 output signal
      \arg        EVIC_SOURCE_ADC0_GRP_SCAN_COMPLETE: ADC0 group scan complete event
      \arg        EVIC_SOURCE_ADC2_GRP_SCAN_COMPLETE: ADC2 group scan complete event
      \arg        EVIC_SOURCE_LVD1_VOLTAGE_DETECTION: LVD1 voltage detection
      \arg        EVIC_SOURCE_LVD2_VOLTAGE_DETECTION: LVD2 voltage detection
      \arg        EVIC_SOURCE_FWDGT_UNDERFLOW_OR_REFRESH: FWDGT underflow or refresh
      \arg        EVIC_SOURCE_HXTAL_STUCK: HXTAL stuck event
      \arg        EVIC_SOURCE_DMA0_CH0_TRANSFER_FINISH: DMA0 channel 0 full transfer finish event
      \arg        EVIC_SOURCE_DMA0_CH1_TRANSFER_FINISH: DMA0 channel 1 full transfer finish event
      \arg        EVIC_SOURCE_DMA0_CH2_TRANSFER_FINISH: DMA0 channel 2 full transfer finish event
      \arg        EVIC_SOURCE_DMA0_CH3_TRANSFER_FINISH: DMA0 channel 3 full transfer finish event
      \arg        EVIC_SOURCE_DMA0_CH4_TRANSFER_FINISH: DMA0 channel 4 full transfer finish event
      \arg        EVIC_SOURCE_DMA0_CH5_TRANSFER_FINISH: DMA0 channel 5 full transfer finish event
      \arg        EVIC_SOURCE_DMA1_CH0_TRANSFER_FINISH: DMA1 channel 0 full transfer finish event
      \arg        EVIC_SOURCE_DMA1_CH1_TRANSFER_FINISH: DMA1 channel 1 full transfer finish event
      \arg        EVIC_SOURCE_DMA1_CH2_TRANSFER_FINISH: DMA1 channel 2 full transfer finish event
      \arg        EVIC_SOURCE_DMA1_CH3_TRANSFER_FINISH: DMA1 channel 3 full transfer finish event
      \arg        EVIC_SOURCE_DMA1_CH4_TRANSFER_FINISH: DMA1 channel 4 full transfer finish event
      \arg        EVIC_SOURCE_DMA1_CH5_TRANSFER_FINISH: DMA1 channel 5 full transfer finish event
      \arg        EVIC_SOURCE_CAN_TRANSMIT_INT: CAN transmit interrupt event
      \arg        EVIC_SOURCE_CAN_FIFO0_INT: CAN FIFO0 interrupt event
      \arg        EVIC_SOURCE_CAN_FIFO1_INT: CAN FIFO1 interrupt event
      \arg        EVIC_SOURCE_CAN_EWMC_INT: CAN EWMC interrupt event
      \arg        EVIC_SOURCE_UART0_ERROR: UART0 error (PERR /FERR /NERR /ORERR)
      \arg        EVIC_SOURCE_UART0_TRANSMIT_COMPLETE: UART0 transmission complete
      \arg        EVIC_SOURCE_UART1_ERROR: UART1 error (PERR /FERR /NERR /ORERR)
      \arg        EVIC_SOURCE_UART1_TRANSMIT_COMPLETE: UART1 transmission complete
      \arg        EVIC_SOURCE_UART2_ERROR: UART2 error (PERR /FERR /NERR /ORERR)
      \arg        EVIC_SOURCE_UART2_TRANSMIT_COMPLETE: UART2 transmission complete
      \arg        EVIC_SOURCE_UART3_ERROR: UART3 error (PERR /FERR /NERR /ORERR)
      \arg        EVIC_SOURCE_UART3_TRANSMIT_COMPLETE: UART3 transmission complete
      \arg        EVIC_SOURCE_SPI_ERROR: SPI error
      \arg        EVIC_SOURCE_SPI_COMMUNICATION_COMPLETE: SPI transfer complete event
      \arg        EVIC_SOURCE_I2C_COMMUNICATION_ERROR_OR_EVENT: I2C communication error/communication event
      \arg        EVIC_SOURCE_I2C_RECEIVE_DATA_NOT_EMPTY: I2C_RDATA is not empty during receiving
      \arg        EVIC_SOURCE_I2C_TRANSMIT_INT: I2C transmit interrupt event
      \arg        EVIC_SOURCE_I2C_TRANSFER_COMPLETE: I2C transfer complete event
      \arg        EVIC_SOURCE_GPTIMER1_CH0_COMPARE_MATCH: GPTIMER1_CH0 compare match event
      \arg        EVIC_SOURCE_GPTIMER1_CH1_COMPARE_MATCH: GPTIMER1_CH1 compare match event
      \arg        EVIC_SOURCE_GPTIMER1_CH0_ADD_COMPARE_MATCH: GPTIMER1_CH0 addition compare match event
      \arg        EVIC_SOURCE_GPTIMER1_CH1_ADD_COMPARE_MATCH: GPTIMER1_CH1 addition compare match event
      \arg        EVIC_SOURCE_GPTIMER1_OVERFLOW: GPTIMER1 overflow event
      \arg        EVIC_SOURCE_GPTIMER1_UNDERFLOW: GPTIMER1 underflow event
      \arg        EVIC_SOURCE_GPTIMER1_ADTCV1_MATCH: GPTIMER1 ADTCV1 match event
      \arg        EVIC_SOURCE_GPTIMER1_ADTCV2_MATCH: GPTIMER1 ADTCV2 match event
      \arg        EVIC_SOURCE_GPTIMER1_REPEAT_COUNT_END: GPTIMER1 end of repeat count event
    \param[out] none
    \retval     none
*/
void evic_init(evic_periph_enum target_periph, event_source_enum event_source)
{

    /* if register write is enabled, set trigger source to target peripheral */
    if(RESET == evic_register_lock_get(target_periph)) {
        EVIC_TARGET_REG(target_periph) &= ~EVIC_TARGET_PERIPH_MASK(target_periph);
        EVIC_TARGET_REG(target_periph) |= ((uint32_t)event_source << EVIC_TARGET_PERIPH_SHIFT(
                                               target_periph)) & EVIC_TARGET_PERIPH_MASK(target_periph);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      get the event source for target peripheral (API_ID(0x0002U))
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        EVENT_INTERCONNECT_SGIO0: single I/O 0
      \arg        EVENT_INTERCONNECT_SGIO1: single I/O 1
      \arg        EVENT_INTERCONNECT_SGIO2: single I/O 2
      \arg        EVENT_INTERCONNECT_SGIO3: single I/O 3
      \arg        EVENT_INTERCONNECT_INGRPE: input group E
      \arg        EVENT_INTERCONNECT_INGRPF: input group F
      \arg        EVENT_INTERCONNECT_OUTGRPE: output group E
      \arg        EVENT_INTERCONNECT_OUTGRPF: output group F
      \arg        EVENT_INTERCONNECT_DAC0_OUT0_COV: DAC0_OUT0 conversion
      \arg        EVENT_INTERCONNECT_DAC0_OUT1_COV: DAC0_OUT1 conversion
      \arg        EVENT_INTERCONNECT_ADC0_GRP_EXTRIG0: ADC0 group external trigger 0
      \arg        EVENT_INTERCONNECT_ADC0_GRP_EXTRIG1: ADC0 group external trigger 1
      \arg        EVENT_INTERCONNECT_ADC2_GRP_EXTRIG0: ADC2 group external trigger 0
      \arg        EVENT_INTERCONNECT_ADC2_GRP_EXTRIG1: ADC2 group external trigger 1
      \arg        EVENT_INTERCONNECT_RCU: clock switch to IRC32M
      \arg        EVENT_INTERCONNECT_TIMER0: TIMER0
      \arg        EVENT_INTERCONNECT_TIMER7: TIMER7
      \arg        EVENT_INTERCONNECT_CPTIMER0: CPTIMER0
      \arg        EVENT_INTERCONNECT_CPTIMERW: CPTIMERW
      \arg        EVENT_INTERCONNECT_TIMER1: TIMER1
      \arg        EVENT_INTERCONNECT_TIMER2: TIMER2
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN0: GPTIMER trigger input 0
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN1: GPTIMER trigger input 1
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN2: GPTIMER trigger input 2
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN3: GPTIMER trigger input 3
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN4: GPTIMER trigger input 4
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN5: GPTIMER trigger input 5
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN6: GPTIMER trigger input 6
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN7: GPTIMER trigger input 7
      \arg        EVENT_INTERCONNECT_DAC0_OUT0_EN: DAC0_OUT0 enable
      \arg        EVENT_INTERCONNECT_DAC0_OUT1_EN: DAC0_OUT1 enable
      \arg        EVENT_INTERCONNECT_DMAMUX_0: DMAMUX multiplexer input 0
      \arg        EVENT_INTERCONNECT_DMAMUX_1: DMAMUX multiplexer input 1
      \arg        EVENT_INTERCONNECT_DMAMUX_2: DMAMUX multiplexer input 2
      \arg        EVENT_INTERCONNECT_DMAMUX_3: DMAMUX multiplexer input 3
      \arg        EVENT_INTERCONNECT_DMAMUX_4: DMAMUX multiplexer input 4
      \arg        EVENT_INTERCONNECT_DMAMUX_5: DMAMUX multiplexer input 5
      \arg        EVENT_INTERCONNECT_DMAMUX_6: DMAMUX multiplexer input 6
      \arg        EVENT_INTERCONNECT_DMAMUX_7: DMAMUX multiplexer input 7
      \arg        EVENT_INTERCONNECT_DMAMUX_8: DMAMUX multiplexer input 8
      \arg        EVENT_INTERCONNECT_DMAMUX_9: DMAMUX multiplexer input 9
      \arg        EVENT_INTERCONNECT_DMAMUX_10: DMAMUX multiplexer input 10
      \arg        EVENT_INTERCONNECT_DMAMUX_11: DMAMUX multiplexer input 11
    \param[out] none
    \retval  event_source: event source value
*/
event_source_enum evic_event_source_get(evic_periph_enum target_periph)
{
    event_source_enum event_source = EVIC_SOURCE_DISABLED;

    event_source = (event_source_enum)((EVIC_TARGET_REG(target_periph) & EVIC_TARGET_PERIPH_MASK(
                                            target_periph)) >> EVIC_TARGET_PERIPH_SHIFT(target_periph));

    return event_source;
}

/*!
    \brief      lock the event interconnect register (API_ID(0x0003U))
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        EVENT_INTERCONNECT_SGIO0: single I/O 0
      \arg        EVENT_INTERCONNECT_SGIO1: single I/O 1
      \arg        EVENT_INTERCONNECT_SGIO2: single I/O 2
      \arg        EVENT_INTERCONNECT_SGIO3: single I/O 3
      \arg        EVENT_INTERCONNECT_INGRPE: input group E
      \arg        EVENT_INTERCONNECT_INGRPF: input group F
      \arg        EVENT_INTERCONNECT_OUTGRPE: output group E
      \arg        EVENT_INTERCONNECT_OUTGRPF: output group F
      \arg        EVENT_INTERCONNECT_DAC0_OUT0_COV: DAC0_OUT0 conversion
      \arg        EVENT_INTERCONNECT_DAC0_OUT1_COV: DAC0_OUT1 conversion
      \arg        EVENT_INTERCONNECT_ADC0_GRP_EXTRIG0: ADC0 group external trigger 0
      \arg        EVENT_INTERCONNECT_ADC0_GRP_EXTRIG1: ADC0 group external trigger 1
      \arg        EVENT_INTERCONNECT_ADC2_GRP_EXTRIG0: ADC2 group external trigger 0
      \arg        EVENT_INTERCONNECT_ADC2_GRP_EXTRIG1: ADC2 group external trigger 1
      \arg        EVENT_INTERCONNECT_RCU: clock switch to IRC32M
      \arg        EVENT_INTERCONNECT_TIMER0: TIMER0
      \arg        EVENT_INTERCONNECT_TIMER7: TIMER7
      \arg        EVENT_INTERCONNECT_CPTIMER0: CPTIMER0
      \arg        EVENT_INTERCONNECT_CPTIMERW: CPTIMERW
      \arg        EVENT_INTERCONNECT_TIMER1: TIMER1
      \arg        EVENT_INTERCONNECT_TIMER2: TIMER2
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN0: GPTIMER trigger input 0
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN1: GPTIMER trigger input 1
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN2: GPTIMER trigger input 2
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN3: GPTIMER trigger input 3
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN4: GPTIMER trigger input 4
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN5: GPTIMER trigger input 5
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN6: GPTIMER trigger input 6
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN7: GPTIMER trigger input 7
      \arg        EVENT_INTERCONNECT_DAC0_OUT0_EN: DAC0_OUT0 enable
      \arg        EVENT_INTERCONNECT_DAC0_OUT1_EN: DAC0_OUT1 enable
      \arg        EVENT_INTERCONNECT_DMAMUX_0: DMAMUX multiplexer input 0
      \arg        EVENT_INTERCONNECT_DMAMUX_1: DMAMUX multiplexer input 1
      \arg        EVENT_INTERCONNECT_DMAMUX_2: DMAMUX multiplexer input 2
      \arg        EVENT_INTERCONNECT_DMAMUX_3: DMAMUX multiplexer input 3
      \arg        EVENT_INTERCONNECT_DMAMUX_4: DMAMUX multiplexer input 4
      \arg        EVENT_INTERCONNECT_DMAMUX_5: DMAMUX multiplexer input 5
      \arg        EVENT_INTERCONNECT_DMAMUX_6: DMAMUX multiplexer input 6
      \arg        EVENT_INTERCONNECT_DMAMUX_7: DMAMUX multiplexer input 7
      \arg        EVENT_INTERCONNECT_DMAMUX_8: DMAMUX multiplexer input 8
      \arg        EVENT_INTERCONNECT_DMAMUX_9: DMAMUX multiplexer input 9
      \arg        EVENT_INTERCONNECT_DMAMUX_10: DMAMUX multiplexer input 10
      \arg        EVENT_INTERCONNECT_DMAMUX_11: DMAMUX multiplexer input 11
    \param[out] none
    \retval     none
*/
void evic_register_lock_set(evic_periph_enum target_periph)
{

    /*!< lock target peripheral register */
    EVIC_TARGET_REG(target_periph) |= EVIC_TARGET_LK;
}

/*!
    \brief      get the event interconnect register lock status (API_ID(0x0004U))
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        EVENT_INTERCONNECT_SGIO0: single I/O 0
      \arg        EVENT_INTERCONNECT_SGIO1: single I/O 1
      \arg        EVENT_INTERCONNECT_SGIO2: single I/O 2
      \arg        EVENT_INTERCONNECT_SGIO3: single I/O 3
      \arg        EVENT_INTERCONNECT_INGRPE: input group E
      \arg        EVENT_INTERCONNECT_INGRPF: input group F
      \arg        EVENT_INTERCONNECT_OUTGRPE: output group E
      \arg        EVENT_INTERCONNECT_OUTGRPF: output group F
      \arg        EVENT_INTERCONNECT_DAC0_OUT0_COV: DAC0_OUT0 conversion
      \arg        EVENT_INTERCONNECT_DAC0_OUT1_COV: DAC0_OUT1 conversion
      \arg        EVENT_INTERCONNECT_ADC0_GRP_EXTRIG0: ADC0 group external trigger 0
      \arg        EVENT_INTERCONNECT_ADC0_GRP_EXTRIG1: ADC0 group external trigger 1
      \arg        EVENT_INTERCONNECT_ADC2_GRP_EXTRIG0: ADC2 group external trigger 0
      \arg        EVENT_INTERCONNECT_ADC2_GRP_EXTRIG1: ADC2 group external trigger 1
      \arg        EVENT_INTERCONNECT_RCU: clock switch to IRC32M
      \arg        EVENT_INTERCONNECT_TIMER0: TIMER0
      \arg        EVENT_INTERCONNECT_TIMER7: TIMER7
      \arg        EVENT_INTERCONNECT_CPTIMER0: CPTIMER0
      \arg        EVENT_INTERCONNECT_CPTIMERW: CPTIMERW
      \arg        EVENT_INTERCONNECT_TIMER1: TIMER1
      \arg        EVENT_INTERCONNECT_TIMER2: TIMER2
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN0: GPTIMER trigger input 0
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN1: GPTIMER trigger input 1
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN2: GPTIMER trigger input 2
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN3: GPTIMER trigger input 3
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN4: GPTIMER trigger input 4
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN5: GPTIMER trigger input 5
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN6: GPTIMER trigger input 6
      \arg        EVENT_INTERCONNECT_GPTIMER_TRIGIN7: GPTIMER trigger input 7
      \arg        EVENT_INTERCONNECT_DAC0_OUT0_EN: DAC0_OUT0 enable
      \arg        EVENT_INTERCONNECT_DAC0_OUT1_EN: DAC0_OUT1 enable
      \arg        EVENT_INTERCONNECT_DMAMUX_0: DMAMUX multiplexer input 0
      \arg        EVENT_INTERCONNECT_DMAMUX_1: DMAMUX multiplexer input 1
      \arg        EVENT_INTERCONNECT_DMAMUX_2: DMAMUX multiplexer input 2
      \arg        EVENT_INTERCONNECT_DMAMUX_3: DMAMUX multiplexer input 3
      \arg        EVENT_INTERCONNECT_DMAMUX_4: DMAMUX multiplexer input 4
      \arg        EVENT_INTERCONNECT_DMAMUX_5: DMAMUX multiplexer input 5
      \arg        EVENT_INTERCONNECT_DMAMUX_6: DMAMUX multiplexer input 6
      \arg        EVENT_INTERCONNECT_DMAMUX_7: DMAMUX multiplexer input 7
      \arg        EVENT_INTERCONNECT_DMAMUX_8: DMAMUX multiplexer input 8
      \arg        EVENT_INTERCONNECT_DMAMUX_9: DMAMUX multiplexer input 9
      \arg        EVENT_INTERCONNECT_DMAMUX_10: DMAMUX multiplexer input 10
      \arg        EVENT_INTERCONNECT_DMAMUX_11: DMAMUX multiplexer input 11
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus evic_register_lock_get(evic_periph_enum target_periph)
{
    FlagStatus reval = RESET;

    if(RESET != (EVIC_TARGET_REG(target_periph) & EVIC_TARGET_LK)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      select CPTIMERW or CPTIMER0 slave mode (API_ID(0x0005U))
    \param[in]  cptimer_periph: TARGET_CPTIMERW, TARGET_CPTIMER0
    \param[in]  slavemode: slave mode
                only one parameter can be selected which is shown as below:
      \arg        EVIC_COUNTER_ENABLE: counter is enabled
      \arg        EVIC_COUNTER_RESTART: counter is restarted
      \arg        EVIC_EVENT_COUNT: event count
      \arg        EVIC_EVENT_TRIGGER_DISABLE: event trigger is disabled
    \param[out] none
    \retval     none
*/
void evic_cptimer_slave_mode_select(evic_cptimer_enum cptimer_periph, uint32_t slavemode)
{
    /* select CPTIMERW slave mode */
    if(TARGET_CPTIMERW == cptimer_periph) {
        EVIC_SMCFG1 &= (~EVIC_SMCFG1_CPTIMERW_SMSEL);
        EVIC_SMCFG1 |= (slavemode & EVIC_SMCFG1_CPTIMERW_SMSEL);
        /* select CPTIMER0 slave mode */
    } else if(TARGET_CPTIMER0 == cptimer_periph) {
        EVIC_SMCFG0 &= (~EVIC_SMCFG0_CPTIMER0_SMSEL);
        EVIC_SMCFG0 |= (slavemode & EVIC_SMCFG0_CPTIMER0_SMSEL);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure evic group member (API_ID(0x0006U))
    \param[in]  group_pin: group I/O pin
                one or more parameters can be selected which are shown as below:
      \arg        EVIC_GRPIO_PIN_x(x=8..14)
    \param[in]  group_port
                only one parameter can be selected which is shown as below:
      \arg        EVIC_GRPIO_PORT_E: group I/O port E is selected
      \arg        EVIC_GRPIO_PORT_F: group I/O port F is selected
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void evic_group_member_config(uint32_t group_pin, uint32_t group_port, ControlStatus newvalue)
{
    if(newvalue == ENABLE) {
        /* configure group E member */
        if(EVIC_GRPIO_PORT_E == group_port) {
            EVIC_GRPECFG |= (group_pin & GROUP_PIN_MASK);
            /* configure group F member */
        } else if(EVIC_GRPIO_PORT_F == group_port) {
            EVIC_GRPFCFG |= (group_pin & GROUP_PIN_MASK);
        } else {
            /* illegal parameters */
        }
    } else {
        /* configure group E member */
        if(EVIC_GRPIO_PORT_E == group_port) {
            EVIC_GRPECFG &= (~(group_pin & GROUP_PIN_MASK));
            /* configure group F member */
        } else if(EVIC_GRPIO_PORT_F == group_port) {
            EVIC_GRPFCFG &= (~(group_pin & GROUP_PIN_MASK));
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      configure evic group input detection edge (API_ID(0x0007U))
    \param[in]  group_edge: group I/O input detection edge
                only one parameter can be selected which is shown as below:
      \arg        EVIC_GRPIO_DETECTION_RISING: Generate event when group I/O input rising edge
      \arg        EVIC_GRPIO_DETECTION_FALLING: Generate event when group I/O input falling edge
      \arg        EVIC_GRPIO_DETECTION_BOTH_EDGE: Generate event when group I/O input both edges
    \param[in]  group_port
                only one parameter can be selected which is shown as below:
      \arg        EVIC_GRPIO_PORT_E: group I/O port E is selected
      \arg        EVIC_GRPIO_PORT_F: group I/O port F is selected
    \param[out] none
    \retval     none
*/
void evic_group_edge_detection_config(uint32_t group_edge, uint32_t group_port)
{
    /* configure group E input detection edge */
    if(EVIC_GRPIO_PORT_E == group_port) {
        EVIC_GRPECFG &= (~EVIC_GRPECFG_GRPEIND);
        EVIC_GRPECFG |= (group_edge & EVIC_GRPECFG_GRPEIND);
        /* configure group F input detection edge */
    } else if(EVIC_GRPIO_PORT_F == group_port) {
        EVIC_GRPFCFG &= (~EVIC_GRPFCFG_GRPFIND);
        EVIC_GRPFCFG |= (group_edge & EVIC_GRPFCFG_GRPFIND);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure evic group output level (API_ID(0x0008U))
    \param[in]  group_level: group I/O output level
                only one parameter can be selected which is shown as below:
      \arg        EVIC_GRPIO_OUTPUT_LOW: group I/O output low level when event comes
      \arg        EVIC_GRPIO_OUTPUT_HIGH: group I/O output high level when event comes
      \arg        EVIC_GRPIO_OUTPUT_INVERTED: group I/O output inverted level when event comes
      \arg        EVIC_GRPIO_OUTPUT_DATA: group I/O output holding data when event comes
      \arg        EVIC_GRPIO_OUTPUT_CIRCULAR_DATA: group I/O circularly shift output holding data when event comes
    \param[in]  group_port
                only one parameter can be selected which is shown as below:
      \arg        EVIC_GRPIO_PORT_E: group I/O port E is selected
      \arg        EVIC_GRPIO_PORT_F: group I/O port F is selected
    \param[out] none
    \retval     none
*/
void evic_group_output_level_config(uint32_t group_level, uint32_t group_port)
{
    /* configure group E output level */
    if(EVIC_GRPIO_PORT_E == group_port) {
        EVIC_GRPECFG &= (~EVIC_GRPECFG_GRPEOSEL);
        EVIC_GRPECFG |= (group_level & EVIC_GRPECFG_GRPEOSEL);
        /* configure group F output level */
    } else if(EVIC_GRPIO_PORT_F == group_port) {
        EVIC_GRPFCFG &= (~EVIC_GRPFCFG_GRPFOSEL);
        EVIC_GRPFCFG |= (group_level & EVIC_GRPFCFG_GRPFOSEL);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable evic group overwrite function (API_ID(0x0009U))
    \param[in]  group_port
                only one parameter can be selected which is shown as below:
      \arg        EVIC_GRPIO_PORT_E: group I/O port E is selected
      \arg        EVIC_GRPIO_PORT_F: group I/O port F is selected
    \param[out] none
    \retval     none
*/
void evic_group_overwrite_enable(uint32_t group_port)
{
    /* enable group E overwrite function */
    if(EVIC_GRPIO_PORT_E == group_port) {
        EVIC_GRPECFG |= EVIC_GRPECFG_OVWEN;
        /* enable group F overwrite function */
    } else if(EVIC_GRPIO_PORT_F == group_port) {
        EVIC_GRPFCFG |= EVIC_GRPFCFG_OVWEN;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      disable evic group overwrite function (API_ID(0x000AU))
    \param[in]  group_port
                only one parameter can be selected which is shown as below:
      \arg        EVIC_GRPIO_PORT_E: group I/O port E is selected
      \arg        EVIC_GRPIO_PORT_F: group I/O port F is selected
    \param[out] none
    \retval     none
*/
void evic_group_overwrite_disable(uint32_t group_port)
{
    /* disable group E overwrite function */
    if(EVIC_GRPIO_PORT_E == group_port) {
        EVIC_GRPECFG &= (~EVIC_GRPECFG_OVWEN);
        /* disable group F overwrite function */
    } else if(EVIC_GRPIO_PORT_F == group_port) {
        EVIC_GRPFCFG &= (~EVIC_GRPFCFG_OVWEN);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      set group holding data value (API_ID(0x000BU))
    \param[in]  data: data to be loaded(0~127)
    \param[in]  group_port
                only one parameter can be selected which is shown as below:
      \arg        EVIC_GRPIO_PORT_E: group I/O port E is selected
      \arg        EVIC_GRPIO_PORT_F: group I/O port F is selected
    \param[out] none
    \retval     none
*/
void evic_data_set(uint8_t data, uint32_t group_port)
{
    /* set group E holding data */
    if(EVIC_GRPIO_PORT_E == group_port) {
        EVIC_GRPEDH = data;
        /* set group F holding data */
    } else if(EVIC_GRPIO_PORT_F == group_port) {
        EVIC_GRPFDH = data;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      get group holding data value (API_ID(0x000CU))
    \param[in]  group_port
                only one parameter can be selected which is shown as below:
      \arg        EVIC_GRPIO_PORT_E: group I/O port E is selected
      \arg        EVIC_GRPIO_PORT_F: group I/O port F is selected
    \param[out] none
    \retval     group holding data: 0~127
*/
uint8_t evic_data_get(uint32_t group_port)
{
    uint8_t data = 0U;

    /* get group E holding data */
    if(EVIC_GRPIO_PORT_E == group_port) {
        data = (uint8_t)EVIC_GRPEDH;
        /* get group F holding data */
    } else if(EVIC_GRPIO_PORT_F == group_port) {
        data = (uint8_t)EVIC_GRPFDH;
    } else {
        /* illegal parameters */
    }
    return data;
}

/*!
    \brief      configure evic single I/O (API_ID(0x000DU))
    \param[in]  single_pin: single I/O pin
                only one parameter can be selected which is shown as below:
      \arg        EVIC_SGIO_PIN_x(x=8..14)
    \param[in]  single_port: single I/O port
                only one parameter can be selected which is shown as below:
      \arg        EVIC_SGIO_PORT_E: single I/O port E is selected
      \arg        EVIC_SGIO_PORT_F: single I/O port F is selected
    \param[in]  single_io: single I/O instance
                only one parameter can be selected which is shown as below:
      \arg        SGIOx (x=0..3)
    \param[out] none
    \retval     none
*/
void evic_single_io_config(uint32_t single_pin, uint32_t single_port, evic_single_io_enum single_io)
{
    switch(single_io) {
    case SGIO0:
        EVIC_SGIOCFG0 &= ~(EVIC_SGIOCFGX_SGIOPORT | EVIC_SGIOCFGX_SGIOPIN);
        EVIC_SGIOCFG0 |= ((single_port & EVIC_SGIOCFGX_SGIOPORT) | (single_pin & EVIC_SGIOCFGX_SGIOPIN));
        break;
    case SGIO1:
        EVIC_SGIOCFG1 &= ~(EVIC_SGIOCFGX_SGIOPORT | EVIC_SGIOCFGX_SGIOPIN);
        EVIC_SGIOCFG1 |= ((single_port & EVIC_SGIOCFGX_SGIOPORT) | (single_pin & EVIC_SGIOCFGX_SGIOPIN));
        break;
    case SGIO2:
        EVIC_SGIOCFG2 &= ~(EVIC_SGIOCFGX_SGIOPORT | EVIC_SGIOCFGX_SGIOPIN);
        EVIC_SGIOCFG2 |= ((single_port & EVIC_SGIOCFGX_SGIOPORT) | (single_pin & EVIC_SGIOCFGX_SGIOPIN));
        break;
    case SGIO3:
        EVIC_SGIOCFG3 &= ~(EVIC_SGIOCFGX_SGIOPORT | EVIC_SGIOCFGX_SGIOPIN);
        EVIC_SGIOCFG3 |= ((single_port & EVIC_SGIOCFGX_SGIOPORT) | (single_pin & EVIC_SGIOCFGX_SGIOPIN));
        break;
    default:
        break;
    }
}

/*!
    \brief      configure evic single I/O input detection edge (API_ID(0x000EU))
    \param[in]  single_edge: single I/O input detection edge
                only one parameter can be selected which is shown as below:
      \arg        EVIC_SGIO_DETECTION_RISING: Generate event when single I/O input rising edge
      \arg        EVIC_SGIO_DETECTION_FALLING: Generate event when single I/O input falling edge
      \arg        EVIC_SGIO_DETECTION_BOTH_EDGE: Generate event when single I/O input both edges
    \param[in]  single_io: single I/O instance
                only one parameter can be selected which is shown as below:
      \arg        SGIOx (x=0..3)
    \param[out] none
    \retval     none
*/
void evic_single_io_edge_detection_config(uint32_t single_edge, evic_single_io_enum single_io)
{
    switch(single_io) {
    case SGIO0:
        EVIC_SGIOCFG0 &= (~EVIC_SGIOCFGX_SGIOM);
        EVIC_SGIOCFG0 |= (single_edge & EVIC_SGIOCFGX_SGIOM);
        break;
    case SGIO1:
        EVIC_SGIOCFG1 &= (~EVIC_SGIOCFGX_SGIOM);
        EVIC_SGIOCFG1 |= (single_edge & EVIC_SGIOCFGX_SGIOM);
        break;
    case SGIO2:
        EVIC_SGIOCFG2 &= (~EVIC_SGIOCFGX_SGIOM);
        EVIC_SGIOCFG2 |= (single_edge & EVIC_SGIOCFGX_SGIOM);
        break;
    case SGIO3:
        EVIC_SGIOCFG3 &= (~EVIC_SGIOCFGX_SGIOM);
        EVIC_SGIOCFG3 |= (single_edge & EVIC_SGIOCFGX_SGIOM);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure evic single I/O input detection edge (API_ID(0x000FU))
    \param[in]  single_level: single I/O output level
                only one parameter can be selected which is shown as below:
      \arg        EVIC_SGIO_OUTPUT_LOW: single I/O output low level when event comes
      \arg        EVIC_SGIO_OUTPUT_HIGH: single I/O output high level when event comes
      \arg        EVIC_SGIO_OUTPUT_INVERTED: single I/O output inverted level when event comes
    \param[in]  single_io: single I/O instance
                only one parameter can be selected which is shown as below:
      \arg        SGIOx (x=0..3)
    \param[out] none
    \retval     none
*/
void evic_single_io_output_level_config(uint32_t single_level, evic_single_io_enum single_io)
{
    switch(single_io) {
    case SGIO0:
        EVIC_SGIOCFG0 &= (~EVIC_SGIOCFGX_SGIOM);
        EVIC_SGIOCFG0 |= (single_level & EVIC_SGIOCFGX_SGIOM);
        break;
    case SGIO1:
        EVIC_SGIOCFG1 &= (~EVIC_SGIOCFGX_SGIOM);
        EVIC_SGIOCFG1 |= (single_level & EVIC_SGIOCFGX_SGIOM);
        break;
    case SGIO2:
        EVIC_SGIOCFG2 &= (~EVIC_SGIOCFGX_SGIOM);
        EVIC_SGIOCFG2 |= (single_level & EVIC_SGIOCFGX_SGIOM);
        break;
    case SGIO3:
        EVIC_SGIOCFG3 &= (~EVIC_SGIOCFGX_SGIOM);
        EVIC_SGIOCFG3 |= (single_level & EVIC_SGIOCFGX_SGIOM);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable software event register write
    \param[in]  none
    \param[out] none
    \retval     none
*/
void evic_register_write_enable(void)
{
    EVIC_SWEV |= EVIC_SWTR_RWEN;
}

/*!
    \brief      disable software event register write
    \param[in]  none
    \param[out] none
    \retval     none
*/
void evic_register_write_disable(void)
{
    EVIC_SWEV &= (~EVIC_SWTR_RWEN);
}

/*!
    \brief      get software event register write enable status
    \param[in]  none
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus evic_register_write_enable_get(void)
{
    FlagStatus reval = RESET;

    if(RESET != (EVIC_SWEV & EVIC_SWTR_RWEN)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      enable software event generation bit write
    \param[in]  none
    \param[out] none
    \retval     none
*/
void evic_bit_write_enable(void)
{
    if(RESET != evic_register_write_enable_get()) {
        EVIC_SWEV |= EVIC_SWTR_BWEN;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      disable software event generation bit write
    \param[in]  none
    \param[out] none
    \retval     none
*/
void evic_bit_write_disable(void)
{
    if(RESET != evic_register_write_enable_get()) {
        EVIC_SWEV &= (~EVIC_SWTR_BWEN);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      get software event generation bit write enable status
    \param[in]  none
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus evic_bit_write_enable_get(void)
{
    FlagStatus reval = RESET;

    if(RESET != (EVIC_SWEV & EVIC_SWTR_BWEN)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      evic software event generation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void evic_software_event_generation(void)
{
    FlagStatus status0 = RESET;
    FlagStatus status1 = RESET;

    status0 = evic_register_write_enable_get();
    status1 = evic_bit_write_enable_get();

    if((RESET != status0) && (RESET != status1)) {
        EVIC_SWEV |= EVIC_SWTR_SWEVG;
    } else {
        /* illegal parameters */
    }
}
