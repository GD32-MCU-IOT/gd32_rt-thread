/*!
    \file    gd32m53x_poc.c
    \brief   POC driver

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

#include "gd32m53x_poc.h"

/* POC input parameter mask */
#define PIN_MODE_MASK                    ((uint8_t)0x03U)     /*!< POC pin mode mask */
#define TIMER_SELECT_MASK                ((uint8_t)0x01U)     /*!< POC target timer select mask */
#define CMP0_DREQ_STATUS_MASK            ((uint8_t)0x01U)     /*!< POC CMP0 disabling request status mask */
#define CMP1_DREQ_STATUS_MASK            ((uint8_t)0x02U)     /*!< POC CMP1 disabling request status mask */
#define CMP2_DREQ_STATUS_MASK            ((uint8_t)0x04U)     /*!< POC CMP2 disabling request status mask */
#define CMP3_DREQ_STATUS_MASK            ((uint8_t)0x08U)     /*!< POC CMP3 disabling request status mask */

#define POC_STAT_FLAG_MASK0       (POC_FLAG_IN0IF | POC_FLAG_IN1IF | POC_FLAG_IN2IF | POC_FLAG_IN3IF | POC_FLAG_IN4IF | POC_FLAG_IN5IF \
                                   | POC_FLAG_HXTALSDF | POC_FLAG_LOCKUPDF | POC_FLAG_TIMER0_CCIF | POC_FLAG_TIMER7_CCIF)
#define POC_STAT_FLAG_MASK1       (POC_FLAG_CMP0DF | POC_FLAG_CMP1DF | POC_FLAG_CMP2DF | POC_FLAG_CMP3DF)
#define POC_INT_FLAG_MASK         (POC_INT_FLAG_IN0IF | POC_INT_FLAG_IN1IF | POC_INT_FLAG_IN2IF | POC_INT_FLAG_IN3IF | POC_INT_FLAG_IN4IF | POC_INT_FLAG_IN5IF \
                                   | POC_INT_FLAG_TIMER0_CCIF | POC_INT_FLAG_TIMER7_CCIF)

/*!
    \brief      deinitialize POC (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void poc_deinit(void)
{
    rcu_periph_reset_enable(RCU_POCRST);
    rcu_periph_reset_disable(RCU_POCRST);
}

/*!
    \brief      configure POC_INn input detection (API_ID(0x0002U))
    \param[in]  poc_pin: POC_INn (n=0..5)
    \param[in]  detection_mode: input detection mode
                only one parameter can be selected which are shown as below:
      \arg        POC_EDGE_DETECTION_DIV1: sampling frequency is fHCLK and generate a request on the falling edge (INPL=0) or rising edge (INPL=1)
      \arg        POC_LEVEL_DETECTION_DIV8: sampling frequency is fHCLK/8 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times
      \arg        POC_LEVEL_DETECTION_DIV16: sampling frequency is fHCLK/16 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times
      \arg        POC_LEVEL_DETECTION_DIV128: sampling frequency is fHCLK/128 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times
      \arg        POC_LEVEL_DETECTION_DIV1: sampling frequency is fHCLK and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times
      \arg        POC_LEVEL_DETECTION_DIV2: sampling frequency is fHCLK/2 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times
      \arg        POC_LEVEL_DETECTION_DIV4: sampling frequency is fHCLK/4 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times
      \arg        POC_LEVEL_DETECTION_DIV256: sampling frequency is fHCLK/256 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times
      \arg        POC_LEVEL_DETECTION_DIV512: sampling frequency is fHCLK/512 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times
      \arg        POC_LEVEL_DETECTION_DIV32: sampling frequency is fHCLK/32 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times
      \arg        POC_LEVEL_DETECTION_DIV64: sampling frequency is fHCLK/64 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times
      \arg        POC_EDGE_DETECTION_DIV2: sampling frequency is fHCLK/2 and generate a request on the falling edge (INPL=0) or rising edge (INPL=1)
      \arg        POC_EDGE_DETECTION_DIV4: sampling frequency is fHCLK/4 and generate a request on the falling edge (INPL=0) or rising edge (INPL=1)
    \param[in]  sampling_number: valid sampling number
                only one parameter can be selected which are shown as below:
      \arg        POC_SAMPLING_NUM_16_TIMES: sampling number is 16 times
      \arg        POC_SAMPLING_NUM_4_TIMES: sampling number is 4 times
      \arg        POC_SAMPLING_NUM_8_TIMES: sampling number is 8 times
      \arg        POC_SAMPLING_NUM_9_TIMES: sampling number is 9 times
      \arg        POC_SAMPLING_NUM_10_TIMES: sampling number is 10 times
      \arg        POC_SAMPLING_NUM_11_TIMES: sampling number is 11 times
      \arg        POC_SAMPLING_NUM_12_TIMES: sampling number is 12 times
      \arg        POC_SAMPLING_NUM_13_TIMES: sampling number is 13 times
      \arg        POC_SAMPLING_NUM_14_TIMES: sampling number is 14 times
      \arg        POC_SAMPLING_NUM_15_TIMES: sampling number is 15 times
                  for edge detection, the number has no effect for edge detection
    \param[out] none
    \retval     none
*/
void poc_input_detection_config(poc_pin_enum poc_pin, uint32_t detection_mode, uint32_t sampling_number)
{
    uint8_t reg = 0U;

    switch(poc_pin) {
    case POC_IN0:
        reg = POC_IN0DCFG_7_0;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDMSEL | POC_INnDCFG_INDSNUM));
        reg |= (uint8_t)((detection_mode & POC_INnDCFG_INDMSEL) | (sampling_number & POC_INnDCFG_INDSNUM));
        POC_IN0DCFG_7_0 = reg;
        break;
    case POC_IN1:
        reg = POC_IN1DCFG_7_0;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDMSEL | POC_INnDCFG_INDSNUM));
        reg |= (uint8_t)((detection_mode & POC_INnDCFG_INDMSEL) | (sampling_number & POC_INnDCFG_INDSNUM));
        POC_IN1DCFG_7_0 = reg;
        break;
    case POC_IN2:
        reg = POC_IN2DCFG_7_0;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDMSEL | POC_INnDCFG_INDSNUM));
        reg |= (uint8_t)((detection_mode & POC_INnDCFG_INDMSEL) | (sampling_number & POC_INnDCFG_INDSNUM));
        POC_IN2DCFG_7_0 = reg;
        break;
    case POC_IN3:
        reg = POC_IN3DCFG_7_0;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDMSEL | POC_INnDCFG_INDSNUM));
        reg |= (uint8_t)((detection_mode & POC_INnDCFG_INDMSEL) | (sampling_number & POC_INnDCFG_INDSNUM));
        POC_IN3DCFG_7_0 = reg;
        break;
    case POC_IN4:
        reg = POC_IN4DCFG_7_0;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDMSEL | POC_INnDCFG_INDSNUM));
        reg |= (uint8_t)((detection_mode & POC_INnDCFG_INDMSEL) | (sampling_number & POC_INnDCFG_INDSNUM));
        POC_IN4DCFG_7_0 = reg;
        break;
    case POC_IN5:
        reg = POC_IN5DCFG_7_0;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDMSEL | POC_INnDCFG_INDSNUM));
        reg |= (uint8_t)((detection_mode & POC_INnDCFG_INDMSEL) | (sampling_number & POC_INnDCFG_INDSNUM));
        POC_IN5DCFG_7_0 = reg;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure POC_INn disabling request status (API_ID(0x0003U))
    \param[in]  poc_pin: POC_INn (n=0..5)
    \param[in]  indreq_status: POC_INn disabling request status
                only one parameter can be selected which are shown as below:
      \arg        POC_INn_DREQ_DISABLE: disabling request generated by POC_INn detection is disabled
      \arg        POC_INn_DREQ_ENABLE: disabling request generated by POC_INn detection is enabled
    \param[out] none
    \retval     none
*/
void poc_input_dreq_status_config(poc_pin_enum poc_pin, uint32_t indreq_status)
{
    uint8_t reg = 0U;

    switch(poc_pin) {
    case POC_IN0:
        reg = POC_IN0DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDREN >> 8U));
        reg |= (uint8_t)((indreq_status & POC_INnDCFG_INDREN) >> 8U);
        POC_IN0DCFG_15_8 = reg;
        break;
    case POC_IN1:
        reg = POC_IN1DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDREN >> 8U));
        reg |= (uint8_t)((indreq_status & POC_INnDCFG_INDREN) >> 8U);
        POC_IN1DCFG_15_8 = reg;
        break;
    case POC_IN2:
        reg = POC_IN2DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDREN >> 8U));
        reg |= (uint8_t)((indreq_status & POC_INnDCFG_INDREN) >> 8U);
        POC_IN2DCFG_15_8 = reg;
        break;
    case POC_IN3:
        reg = POC_IN3DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDREN >> 8U));
        reg |= (uint8_t)((indreq_status & POC_INnDCFG_INDREN) >> 8U);
        POC_IN3DCFG_15_8 = reg;
        break;
    case POC_IN4:
        reg = POC_IN4DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDREN >> 8U));
        reg |= (uint8_t)((indreq_status & POC_INnDCFG_INDREN) >> 8U);
        POC_IN4DCFG_15_8 = reg;
        break;
    case POC_IN5:
        reg = POC_IN5DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INDREN >> 8U));
        reg |= (uint8_t)((indreq_status & POC_INnDCFG_INDREN) >> 8U);
        POC_IN5DCFG_15_8 = reg;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure POC_INn input polarity (API_ID(0x0004U))
    \param[in]  poc_pin: POC_INn (n=0..5)
    \param[in]  input_polarity: POC_INn input polarity
                only one parameter can be selected which are shown as below:
      \arg        POC_INPUT_POLARITY_NONINVERTED: POC_INn input not inverted
      \arg        POC_INPUT_POLARITY_INVERTED: POC_INn input inverted
    \param[out] none
    \retval     none
*/
void poc_input_polarity_config(poc_pin_enum poc_pin, uint32_t input_polarity)
{
    uint8_t reg = 0U;

    switch(poc_pin) {
    case POC_IN0:
        reg = POC_IN0DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INPL >> 8U));
        reg |= (uint8_t)((input_polarity & POC_INnDCFG_INPL) >> 8U);
        POC_IN0DCFG_15_8 = reg;
        break;
    case POC_IN1:
        reg = POC_IN1DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INPL >> 8U));
        reg |= (uint8_t)((input_polarity & POC_INnDCFG_INPL) >> 8U);
        POC_IN1DCFG_15_8 = reg;
        break;
    case POC_IN2:
        reg = POC_IN2DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INPL >> 8U));
        reg |= (uint8_t)((input_polarity & POC_INnDCFG_INPL) >> 8U);
        POC_IN2DCFG_15_8 = reg;
        break;
    case POC_IN3:
        reg = POC_IN3DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INPL >> 8U));
        reg |= (uint8_t)((input_polarity & POC_INnDCFG_INPL) >> 8U);
        POC_IN3DCFG_15_8 = reg;
        break;
    case POC_IN4:
        reg = POC_IN4DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INPL >> 8U));
        reg |= (uint8_t)((input_polarity & POC_INnDCFG_INPL) >> 8U);
        POC_IN4DCFG_15_8 = reg;
        break;
    case POC_IN5:
        reg = POC_IN5DCFG_15_8;
        reg &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INPL >> 8U));
        reg |= (uint8_t)((input_polarity & POC_INnDCFG_INPL) >> 8U);
        POC_IN5DCFG_15_8 = reg;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure system fault disabling request status (API_ID(0x0005U))
    \param[in]  hxtalsdreq_status: HXTAL stuck disabling request status
                only one parameter can be selected which are shown as below:
      \arg        HXTALS_DREQ_DISABLE: HXTAL stuck disabling request disable
      \arg        HXTALS_DREQ_ENABLE: HXTAL stuck disabling request enable
    \param[in]  lockupdreq_status: CPU LOCKUP disabling request status
                only one parameter can be selected which are shown as below:
      \arg        LOCKUP_DREQ_DISABLE: CPU LOCKUP disabling request disable
      \arg        LOCKUP_DREQ_ENABLE: CPU LOCKUP disabling request enable
    \param[out] none
    \retval     none
*/
void poc_sys_fault_dreq_status_config(uint32_t hxtalsdreq_status, uint32_t lockupdreq_status)
{
    POC_CTL0 = (uint32_t)((hxtalsdreq_status & POC_CTL0_HXTALS_DREN) | (lockupdreq_status & POC_CTL0_LOCKUP_DREN));
}

/*!
    \brief      generate software disabling request for timer (API_ID(0x0006U))
    \param[in]  target_timer: TARGET_TIMERx(x=0~2,7), TARGET_GPTIMER0, TARGET_GPTIMER1
    \param[out] none
    \retval     none
*/
void poc_software_request_generate(target_timer_enum target_timer)
{
    switch(target_timer) {
    case TARGET_TIMER0:
        POC_SWDRG |= (uint32_t)(POC_SWDRG_TIMER0_SWDRG);
        break;
    case TARGET_TIMER7:
        POC_SWDRG |= (uint32_t)(POC_SWDRG_TIMER7_SWDRG);
        break;
    case TARGET_TIMER1:
        POC_SWDRG |= (uint32_t)(POC_SWDRG_TIMER1_SWDRG);
        break;
    case TARGET_TIMER2:
        POC_SWDRG |= (uint32_t)(POC_SWDRG_TIMER2_SWDRG);
        break;
    case TARGET_GPTIMER0:
        POC_SWDRG |= (uint32_t)(POC_SWDRG_GPTIMER0_SWDRG);
        break;
    case TARGET_GPTIMER1:
        POC_SWDRG |= (uint32_t)(POC_SWDRG_GPTIMER1_SWDRG);
        break;
    default:
        break;
    }
}

/*!
    \brief      stop software disabling request for timer (API_ID(0x0007U))
    \param[in]  target_timer: TARGET_TIMERx(x=0~2,7), TARGET_GPTIMER0, TARGET_GPTIMER1
    \param[out] none
    \retval     none
*/
void poc_software_request_stop(target_timer_enum target_timer)
{
    switch(target_timer) {
    case TARGET_TIMER0:
        POC_SWDRG &= ~(uint32_t)(POC_SWDRG_TIMER0_SWDRG);
        break;
    case TARGET_TIMER7:
        POC_SWDRG &= ~(uint32_t)POC_SWDRG_TIMER7_SWDRG;
        break;
    case TARGET_TIMER1:
        POC_SWDRG &= ~(uint32_t)(POC_SWDRG_TIMER1_SWDRG);
        break;
    case TARGET_TIMER2:
        POC_SWDRG &= ~(uint32_t)(POC_SWDRG_TIMER2_SWDRG);
        break;
    case TARGET_GPTIMER0:
        POC_SWDRG &= ~(uint32_t)(POC_SWDRG_GPTIMER0_SWDRG);
        break;
    case TARGET_GPTIMER1:
        POC_SWDRG &= ~(uint32_t)(POC_SWDRG_GPTIMER1_SWDRG);
        break;
    default:
        break;
    }
}

/*!
    \brief      initialize POC complementary detection struct with a default value (API_ID(0x0008U))
    \param[in]  detpara: POC complementary detection struct parameter
    \param[out] none
    \retval     none
*/
void poc_complementary_detection_struct_para_init(poc_complementary_detection_struct *detpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(detpara)) {
        fw_debug_report_err(POC_MODULE_ID, API_ID(0x0008U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the POC complementary detection struct with the default value */
        detpara->ccdreqstatus = TIMER_CCDREQ_DISABLE;
        detpara->polarityselen = TIMER_POLARITY_SELECTION_DISABLE;
        detpara->ch0polarity = CH0_POLARITY_HIGH;
        detpara->mch0polarity = MCH0_POLARITY_HIGH;
        detpara->ch1polarity = CH1_POLARITY_HIGH;
        detpara->mch1polarity = MCH1_POLARITY_HIGH;
        detpara->ch2polarity = CH2_POLARITY_HIGH;
        detpara->mch2polarity = MCH2_POLARITY_HIGH;
    }
}

/*!
    \brief      configure TIMER0 complementary channel detection (API_ID(0x0009U))
    \param[in]  detpara: timer complementary detection struct
                  ccdreqstatus: TIMER_CCDREQ_DISABLE, TIMER_CCDREQ_ENABLE
                  polarityselen: TIMER_POLARITY_SELECTION_DISABLE, TIMER_POLARITY_SELECTION_ENABLE
                  mch2polarity: MCH2_POLARITY_HIGH, MCH2_POLARITY_LOW
                  ch2polarity: CH2_POLARITY_HIGH, CH2_POLARITY_LOW
                  mch1polarity: MCH1_POLARITY_HIGH, MCH1_POLARITY_LOW
                  ch1polarity: CH1_POLARITY_HIGH, CH1_POLARITY_LOW
                  mch0polarity: MCH0_POLARITY_HIGH, MCH0_POLARITY_LOW
                  ch0polarity: CH0_POLARITY_HIGH, CH0_POLARITY_LOW
    \param[out] none
    \retval     none
*/
void poc_timer0_complementary_detection_config(poc_complementary_detection_struct *detpara)
{
    uint32_t reg = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(detpara)) {
        fw_debug_report_err(POC_MODULE_ID, API_ID(0x0009U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = POC_CDCFG0;
        reg &= ~(uint32_t)(POC_CDCFG0_TIMER0_CCDREN | POC_CDCFG0_TIMER0_PSELEN | POC_CDCFG0_TIMER0_MCH2_APSEL | POC_CDCFG0_TIMER0_CH2_APSEL | \
                           POC_CDCFG0_TIMER0_MCH1_APSEL | POC_CDCFG0_TIMER0_CH1_APSEL | POC_CDCFG0_TIMER0_MCH0_APSEL | POC_CDCFG0_TIMER0_CH0_APSEL);
        reg |= (uint32_t)((detpara->ccdreqstatus & POC_CDCFG0_TIMER0_CCDREN) | (detpara->polarityselen & POC_CDCFG0_TIMER0_PSELEN) | \
                          (detpara->mch2polarity & POC_CDCFG0_TIMER0_MCH2_APSEL) | (detpara->ch2polarity & POC_CDCFG0_TIMER0_CH2_APSEL) | \
                          (detpara->mch1polarity & POC_CDCFG0_TIMER0_MCH1_APSEL) | (detpara->ch1polarity & POC_CDCFG0_TIMER0_CH1_APSEL) | \
                          (detpara->mch0polarity & POC_CDCFG0_TIMER0_MCH0_APSEL) | (detpara->ch0polarity & POC_CDCFG0_TIMER0_CH0_APSEL));
        POC_CDCFG0 = reg;
    }
}

/*!
    \brief      configure TIMER7 complementary channel detection (API_ID(0x000AU))
    \param[in]  detpara: timer complementary detection struct
                  ccdreqstatus: TIMER_CCDREQ_DISABLE, TIMER_CCDREQ_ENABLE
                  polarityselen: TIMER_POLARITY_SELECTION_DISABLE, TIMER_POLARITY_SELECTION_ENABLE
                  mch2polarity: MCH2_POLARITY_HIGH, MCH2_POLARITY_LOW
                  ch2polarity: CH2_POLARITY_HIGH, CH2_POLARITY_LOW
                  mch1polarity: MCH1_POLARITY_HIGH, MCH1_POLARITY_LOW
                  ch1polarity: CH1_POLARITY_HIGH, CH1_POLARITY_LOW
                  mch0polarity: MCH0_POLARITY_HIGH, MCH0_POLARITY_LOW
                  ch0polarity: CH0_POLARITY_HIGH, CH0_POLARITY_LOW
    \param[out] none
    \retval     none
*/
void poc_timer7_complementary_detection_config(poc_complementary_detection_struct *detpara)
{
    uint32_t reg = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(detpara)) {
        fw_debug_report_err(POC_MODULE_ID, API_ID(0x000AU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = POC_CDCFG1;
        reg &= ~(uint32_t)(POC_CDCFG1_TIMER7_CCDREN | POC_CDCFG1_TIMER7_PSELEN | POC_CDCFG1_TIMER7_MCH2_APSEL | POC_CDCFG1_TIMER7_CH2_APSEL | \
                           POC_CDCFG1_TIMER7_MCH1_APSEL | POC_CDCFG1_TIMER7_CH1_APSEL | POC_CDCFG1_TIMER7_MCH0_APSEL | POC_CDCFG1_TIMER7_CH0_APSEL);
        reg |= (uint32_t)((detpara->ccdreqstatus & POC_CDCFG1_TIMER7_CCDREN) | (detpara->polarityselen & POC_CDCFG1_TIMER7_PSELEN) | \
                          (detpara->mch2polarity & POC_CDCFG1_TIMER7_MCH2_APSEL) | (detpara->ch2polarity & POC_CDCFG1_TIMER7_CH2_APSEL) | \
                          (detpara->mch1polarity & POC_CDCFG1_TIMER7_MCH1_APSEL) | (detpara->ch1polarity & POC_CDCFG1_TIMER7_CH1_APSEL) | \
                          (detpara->mch0polarity & POC_CDCFG1_TIMER7_MCH0_APSEL) | (detpara->ch0polarity & POC_CDCFG1_TIMER7_CH0_APSEL));
        POC_CDCFG1 = reg;
    }
}

/*!
    \brief      select output disable mode for TIMER0 (API_ID(0x000BU))
    \param[in]  ch0mch0_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch1mch1_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch2mch2_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch3mch3_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[out] none
    \retval     none
*/
void poc_timer0_output_disable_mode_select(uint8_t ch0mch0_pin_mode, uint8_t ch1mch1_pin_mode, uint8_t ch2mch2_pin_mode, uint8_t ch3mch3_pin_mode)
{
    POC_ODMODE0_TIMER0 = ((uint8_t)((uint8_t)((uint8_t)(ch0mch0_pin_mode & PIN_MODE_MASK) | (uint8_t)((ch1mch1_pin_mode & PIN_MODE_MASK) << 2U)) | \
                                    (uint8_t)((ch2mch2_pin_mode & PIN_MODE_MASK) << 4U)) | (uint8_t)((ch3mch3_pin_mode & PIN_MODE_MASK) << 6U));
}

/*!
    \brief      select output disable mode for TIMER7 (API_ID(0x000CU))
    \param[in]  ch0mch0_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch1mch1_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch2mch2_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch3mch3_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[out] none
    \retval     none
*/
void poc_timer7_output_disable_mode_select(uint8_t ch0mch0_pin_mode, uint8_t ch1mch1_pin_mode, uint8_t ch2mch2_pin_mode, uint8_t ch3mch3_pin_mode)
{
    POC_ODMODE0_TIMER7 = ((uint8_t)((uint8_t)((uint8_t)(ch0mch0_pin_mode & PIN_MODE_MASK) | (uint8_t)((ch1mch1_pin_mode & PIN_MODE_MASK) << 2U)) | \
                                    (uint8_t)((ch2mch2_pin_mode & PIN_MODE_MASK) << 4U)) | (uint8_t)((ch3mch3_pin_mode & PIN_MODE_MASK) << 6U));
}

/*!
    \brief      select output disable mode for TIMER1 (API_ID(0x000DU))
    \param[in]  ch0_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch1_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch2_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch3_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[out] none
    \retval     none
*/
void poc_timer1_output_disable_mode_select(uint8_t ch0_pin_mode, uint8_t ch1_pin_mode, uint8_t ch2_pin_mode, uint8_t ch3_pin_mode)
{
    POC_ODMODE1_TIMER1 = ((uint8_t)((uint8_t)((uint8_t)(ch0_pin_mode & PIN_MODE_MASK) | (uint8_t)((ch1_pin_mode  & PIN_MODE_MASK) << 2U)) | \
                                    (uint8_t)((ch2_pin_mode & PIN_MODE_MASK) << 4U)) | (uint8_t)((ch3_pin_mode & PIN_MODE_MASK) << 6U));
}

/*!
    \brief      select output disable mode for TIMER2 (API_ID(0x000EU))
    \param[in]  ch0_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch1_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch2_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch3_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[out] none
    \retval     none
*/
void poc_timer2_output_disable_mode_select(uint8_t ch0_pin_mode, uint8_t ch1_pin_mode, uint8_t ch2_pin_mode, uint8_t ch3_pin_mode)
{
    POC_ODMODE1_TIMER2 = ((uint8_t)((uint8_t)((uint8_t)(ch0_pin_mode & PIN_MODE_MASK) | (uint8_t)((ch1_pin_mode & PIN_MODE_MASK) << 2U)) | \
                                    (uint8_t)((ch2_pin_mode & PIN_MODE_MASK) << 4U)) | (uint8_t)((ch3_pin_mode & PIN_MODE_MASK) << 6U));
}

/*!
    \brief      select output disable mode for GPTIMER0 (API_ID(0x000FU))
    \param[in]  ch0_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch1_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[out] none
    \retval     none
*/
void poc_gptimer0_output_disable_mode_select(uint8_t ch0_pin_mode, uint8_t ch1_pin_mode)
{
    POC_ODMODE1_GPTIMER0 = ((uint8_t)(ch0_pin_mode & PIN_MODE_MASK) | (uint8_t)((ch1_pin_mode & PIN_MODE_MASK) << 2U));
}

/*!
    \brief      select output disable mode for GPTIMER1 (API_ID(0x0010U))
    \param[in]  ch0_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[in]  ch1_pin_mode:
                only one parameter can be selected which are shown as below:
      \arg        POC_TIMER_CHANNEL_OUT: timer channel output
      \arg        POC_HIGH_IMPEDANCE_OUT: High-impedance output
      \arg        POC_GPIO_OUT: GPIO output
    \param[out] none
    \retval     none
*/
void poc_gptimer1_output_disable_mode_select(uint8_t ch0_pin_mode, uint8_t ch1_pin_mode)
{
    POC_ODMODE1_GPTIMER1 = ((uint8_t)(ch0_pin_mode & PIN_MODE_MASK) | (uint8_t)((ch1_pin_mode & PIN_MODE_MASK) << 2U));
}

/*!
    \brief      initialize POC request struct with a default value (API_ID(0x0011U))
    \param[in]  request: POC request struct parameter
    \param[out] none
    \retval     none
*/
void poc_request_struct_para_init(poc_request_struct *request)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(request)) {
        fw_debug_report_err(POC_MODULE_ID, API_ID(0x0011U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the POC request struct with the default value */
        request->req_pocin0 = TARGET_TIMER_NOT_SELECTED;
        request->req_pocin1 = TARGET_TIMER_NOT_SELECTED;
        request->req_pocin2 = TARGET_TIMER_NOT_SELECTED;
        request->req_pocin3 = TARGET_TIMER_NOT_SELECTED;
        request->req_pocin4 = TARGET_TIMER_NOT_SELECTED;
        request->req_pocin5 = TARGET_TIMER_NOT_SELECTED;
        request->req_comparator = TARGET_TIMER_NOT_SELECTED;
    }
}

/*!
    \brief      request select target timer (API_ID(0x0012U))
    \param[in]  request: poc request struct
      \arg        req_pocin0: TARGET_TIMER_NOT_SELECTED, TARGET_TIMER_SELECTED
      \arg        req_pocin1: TARGET_TIMER_NOT_SELECTED, TARGET_TIMER_SELECTED
      \arg        req_pocin2: TARGET_TIMER_NOT_SELECTED, TARGET_TIMER_SELECTED
      \arg        req_pocin3: TARGET_TIMER_NOT_SELECTED, TARGET_TIMER_SELECTED
      \arg        req_pocin4: TARGET_TIMER_NOT_SELECTED, TARGET_TIMER_SELECTED
      \arg        req_pocin5: TARGET_TIMER_NOT_SELECTED, TARGET_TIMER_SELECTED
      \arg        req_comparator: TARGET_TIMER_NOT_SELECTED, TARGET_TIMER_SELECTED
    \param[in]  target_timer: target timer
      \arg        TARGET_TIMER0: TIMER0
      \arg        TARGET_TIMER7: TIMER7
      \arg        TARGET_TIMER1: TIMER1
      \arg        TARGET_TIMER2: TIMER2
      \arg        TARGET_GPTIMER0: GPTIMER0
      \arg        TARGET_GPTIMER1: GPTIMER1
    \param[out] none
    \retval     none
*/
void poc_request_select(poc_request_struct *request, target_timer_enum target_timer)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(request)) {
        fw_debug_report_err(POC_MODULE_ID, API_ID(0x0012U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(target_timer) {
        case TARGET_TIMER0:
            POC_REQSEL0_TIMER0 = ((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)(request->req_pocin0 & TIMER_SELECT_MASK) | (uint8_t)((request->req_pocin1 & TIMER_SELECT_MASK) << 1U)) | (uint8_t)((
                                                                              request->req_pocin2 & TIMER_SELECT_MASK) << 2U)) | (uint8_t)((request->req_pocin3 & TIMER_SELECT_MASK) << 3U)) | \
                                                      (uint8_t)((request->req_pocin4 & TIMER_SELECT_MASK) << 4U)) | (uint8_t)((request->req_pocin5 & TIMER_SELECT_MASK) << 5U)) | (uint8_t)((request->req_comparator & TIMER_SELECT_MASK) << 6U));
            break;
        case TARGET_TIMER7:
            POC_REQSEL0_TIMER7 = ((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)(request->req_pocin0 & TIMER_SELECT_MASK) | (uint8_t)((request->req_pocin1 & TIMER_SELECT_MASK) << 1U)) | (uint8_t)((
                                                                              request->req_pocin2 & TIMER_SELECT_MASK) << 2U)) | (uint8_t)((request->req_pocin3 & TIMER_SELECT_MASK) << 3U)) | \
                                                      (uint8_t)((request->req_pocin4 & TIMER_SELECT_MASK) << 4U)) | (uint8_t)((request->req_pocin5 & TIMER_SELECT_MASK) << 5U)) | (uint8_t)((request->req_comparator & TIMER_SELECT_MASK) << 6U));
            break;
        case TARGET_TIMER1:
            POC_REQSEL1_TIMER1 = ((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)(request->req_pocin0 & TIMER_SELECT_MASK) | (uint8_t)((request->req_pocin1 & TIMER_SELECT_MASK) << 1U)) | (uint8_t)((
                                                                              request->req_pocin2 & TIMER_SELECT_MASK) << 2U)) | (uint8_t)((request->req_pocin3 & TIMER_SELECT_MASK) << 3U)) | \
                                                      (uint8_t)((request->req_pocin4 & TIMER_SELECT_MASK) << 4U)) | (uint8_t)((request->req_pocin5 & TIMER_SELECT_MASK) << 5U)) | (uint8_t)((request->req_comparator & TIMER_SELECT_MASK) << 6U));
            break;
        case TARGET_TIMER2:
            POC_REQSEL1_TIMER2 = ((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)(request->req_pocin0 & TIMER_SELECT_MASK) | (uint8_t)((request->req_pocin1 & TIMER_SELECT_MASK) << 1U)) | (uint8_t)((
                                                                              request->req_pocin2 & TIMER_SELECT_MASK) << 2U)) | (uint8_t)((request->req_pocin3 & TIMER_SELECT_MASK) << 3U)) | \
                                                      (uint8_t)((request->req_pocin4 & TIMER_SELECT_MASK) << 4U)) | (uint8_t)((request->req_pocin5 & TIMER_SELECT_MASK) << 5U)) | (uint8_t)((request->req_comparator & TIMER_SELECT_MASK) << 6U));
            break;
        case TARGET_GPTIMER0:
            POC_REQSEL1_GPTIMER0 = ((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)(request->req_pocin0 & TIMER_SELECT_MASK) | (uint8_t)((request->req_pocin1 & TIMER_SELECT_MASK) << 1U)) |
                                                                            (uint8_t)((request->req_pocin2 & TIMER_SELECT_MASK) << 2U)) | (uint8_t)((request->req_pocin3 & TIMER_SELECT_MASK) << 3U)) | \
                                                        (uint8_t)((request->req_pocin4 & TIMER_SELECT_MASK) << 4U)) | (uint8_t)((request->req_pocin5 & TIMER_SELECT_MASK) << 5U)) | (uint8_t)((request->req_comparator & TIMER_SELECT_MASK) << 6U));
            break;
        case TARGET_GPTIMER1:
            POC_REQSEL1_GPTIMER1 = ((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)((uint8_t)(request->req_pocin0 & TIMER_SELECT_MASK) | (uint8_t)((request->req_pocin1 & TIMER_SELECT_MASK) << 1U)) |
                                                                            (uint8_t)((request->req_pocin2 & TIMER_SELECT_MASK) << 2U)) | (uint8_t)((request->req_pocin3 & TIMER_SELECT_MASK) << 3U)) | \
                                                        (uint8_t)((request->req_pocin4 & TIMER_SELECT_MASK) << 4U)) | (uint8_t)((request->req_pocin5 & TIMER_SELECT_MASK) << 5U)) | (uint8_t)((request->req_comparator & TIMER_SELECT_MASK) << 6U));
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      configure comparator disabling request status (API_ID(0x0013U))
    \param[in]  cmp0dreq_status: comparator 0 disabling request status
                only one parameter can be selected which are shown as below:
      \arg        CMP0_DREQ_DISABLE: comparator 0 disabling request disable
      \arg        CMP0_DREQ_ENABLE: comparator 0 disabling request enable
    \param[in]  cmp1dreq_status: comparator 1 disabling request status
                only one parameter can be selected which are shown as below:
      \arg        CMP1_DREQ_DISABLE: comparator 1 disabling request disable
      \arg        CMP1_DREQ_ENABLE: comparator 1 disabling request enable
    \param[in]  cmp2dreq_status: comparator 2 disabling request status
                only one parameter can be selected which are shown as below:
      \arg        CMP2_DREQ_DISABLE: comparator 2 disabling request disable
      \arg        CMP2_DREQ_ENABLE: comparator 2 disabling request enable
    \param[in]  cmp3dreq_status: comparator 3 disabling request status
                only one parameter can be selected which are shown as below:
      \arg        CMP3_DREQ_DISABLE: comparator 3 disabling request disable
      \arg        CMP3_DREQ_ENABLE: comparator 3 disabling request enable
    \param[out] none
    \retval     none
*/
void poc_cmp_dreq_status_config(uint32_t cmp0dreq_status, uint32_t cmp1dreq_status, uint32_t cmp2dreq_status, uint32_t cmp3dreq_status)
{
    POC_CTL1 = (uint32_t)((cmp0dreq_status & POC_CTL1_CMP0DREN) | (cmp1dreq_status & POC_CTL1_CMP1DREN) | (cmp2dreq_status & POC_CTL1_CMP2DREN) | (cmp3dreq_status & POC_CTL1_CMP3DREN));
}

/*!
    \brief      configure comparator disabling request status for target timer (API_ID(0x0014U))
    \param[in]  cmp0dreq_status: comparator 0 disabling request status
                only one parameter can be selected which are shown as below:
      \arg        CMP0_DREQ_DISABLE: comparator 0 disabling request disable
      \arg        CMP0_DREQ_ENABLE: comparator 0 disabling request enable
    \param[in]  cmp1dreq_status: comparator 1 disabling request status
                only one parameter can be selected which are shown as below:
      \arg        CMP1_DREQ_DISABLE: comparator 1 disabling request disable
      \arg        CMP1_DREQ_ENABLE: comparator 1 disabling request enable
    \param[in]  cmp2dreq_status: comparator 2 disabling request status
                only one parameter can be selected which are shown as below:
      \arg        CMP2_DREQ_DISABLE: comparator 2 disabling request disable
      \arg        CMP2_DREQ_ENABLE: comparator 2 disabling request enable
    \param[in]  cmp3dreq_status: comparator 3 disabling request status
                only one parameter can be selected which are shown as below:
      \arg        CMP3_DREQ_DISABLE: comparator 3 disabling request disable
      \arg        CMP3_DREQ_ENABLE: comparator 3 disabling request enable
    \param[in]  target_timer: TARGET_TIMERx(x=0~2,7), TARGET_GPTIMER0, TARGET_GPTIMER1
    \param[out] none
    \retval     none
*/
void poc_cmp_dreq_status_extended_config(uint32_t cmp0dreq_status, uint32_t cmp1dreq_status, uint32_t cmp2dreq_status, uint32_t cmp3dreq_status,
                                         target_timer_enum target_timer)
{
    switch(target_timer) {
    case TARGET_TIMER0:
        POC_EXTCTL0_TIMER0 = (uint8_t)((cmp0dreq_status & CMP0_DREQ_STATUS_MASK) | (cmp1dreq_status & CMP1_DREQ_STATUS_MASK) | (cmp2dreq_status & CMP2_DREQ_STATUS_MASK) |
                                       (cmp3dreq_status & CMP3_DREQ_STATUS_MASK));
        break;
    case TARGET_TIMER7:
        POC_EXTCTL0_TIMER7 = (uint8_t)((cmp0dreq_status & CMP0_DREQ_STATUS_MASK) | (cmp1dreq_status & CMP1_DREQ_STATUS_MASK) | (cmp2dreq_status & CMP2_DREQ_STATUS_MASK) |
                                       (cmp3dreq_status & CMP3_DREQ_STATUS_MASK));
        break;
    case TARGET_TIMER1:
        POC_EXTCTL1_TIMER1 = (uint8_t)((cmp0dreq_status & CMP0_DREQ_STATUS_MASK) | (cmp1dreq_status & CMP1_DREQ_STATUS_MASK) | (cmp2dreq_status & CMP2_DREQ_STATUS_MASK) |
                                       (cmp3dreq_status & CMP3_DREQ_STATUS_MASK));
        break;
    case TARGET_TIMER2:
        POC_EXTCTL1_TIMER2 = (uint8_t)((cmp0dreq_status & CMP0_DREQ_STATUS_MASK) | (cmp1dreq_status & CMP1_DREQ_STATUS_MASK) | (cmp2dreq_status & CMP2_DREQ_STATUS_MASK) |
                                       (cmp3dreq_status & CMP3_DREQ_STATUS_MASK));
        break;
    case TARGET_GPTIMER0:
        POC_EXTCTL1_GPTIMER0 = (uint8_t)((cmp0dreq_status & CMP0_DREQ_STATUS_MASK) | (cmp1dreq_status & CMP1_DREQ_STATUS_MASK) | (cmp2dreq_status & CMP2_DREQ_STATUS_MASK) |
                                         (cmp3dreq_status & CMP3_DREQ_STATUS_MASK));
        break;
    case TARGET_GPTIMER1:
        POC_EXTCTL1_GPTIMER1 = (uint8_t)((cmp0dreq_status & CMP0_DREQ_STATUS_MASK) | (cmp1dreq_status & CMP1_DREQ_STATUS_MASK) | (cmp2dreq_status & CMP2_DREQ_STATUS_MASK) |
                                         (cmp3dreq_status & CMP3_DREQ_STATUS_MASK));
        break;
    default:
        break;
    }
}

/*!
    \brief      mask POC_INn input detection (API_ID(0x0015U))
    \param[in]  poc_pin: POC_INn (n=0..5)
    \param[in]  mask_source: mask source selection
                only one parameter can be selected which are shown as below:
      \arg        POC_REQUEST_NOT_MASKED: detection is not masked
      \arg        POC_MASK_SOURCE_TIMER0_CH0: detection is masked by TIMER0_CH0
      \arg        POC_MASK_SOURCE_TIMER0_CH1: detection is masked by TIMER0_CH1
      \arg        POC_MASK_SOURCE_TIMER0_CH2: detection is masked by TIMER0_CH2
      \arg        POC_MASK_SOURCE_TIMER0_CH3: detection is masked by TIMER0_CH3
      \arg        POC_MASK_SOURCE_TIMER0_MCH0: detection is masked by TIMER0_MCH0
      \arg        POC_MASK_SOURCE_TIMER0_MCH1: detection is masked by TIMER0_MCH1
      \arg        POC_MASK_SOURCE_TIMER0_MCH2: detection is masked by TIMER0_MCH2
      \arg        POC_MASK_SOURCE_TIMER0_MCH3: detection is masked by TIMER0_MCH3
      \arg        POC_MASK_SOURCE_TIMER7_CH0: detection is masked by TIMER7_CH0
      \arg        POC_MASK_SOURCE_TIMER7_CH1: detection is masked by TIMER7_CH1
      \arg        POC_MASK_SOURCE_TIMER7_CH2: detection is masked by TIMER7_CH2
      \arg        POC_MASK_SOURCE_TIMER7_CH3: detection is masked by TIMER7_CH3
      \arg        POC_MASK_SOURCE_TIMER7_MCH0: detection is masked by TIMER7_MCH0
      \arg        POC_MASK_SOURCE_TIMER7_MCH1: detection is masked by TIMER7_MCH1
      \arg        POC_MASK_SOURCE_TIMER7_MCH2: detection is masked by TIMER7_MCH2
      \arg        POC_MASK_SOURCE_TIMER7_MCH3: detection is masked by TIMER7_MCH3
      \arg        POC_MASK_SOURCE_TIMER1_CH0: detection is masked by TIMER1_CH0
      \arg        POC_MASK_SOURCE_TIMER1_CH1: detection is masked by TIMER1_CH1
      \arg        POC_MASK_SOURCE_TIMER1_CH2: detection is masked by TIMER1_CH2
      \arg        POC_MASK_SOURCE_TIMER1_CH3: detection is masked by TIMER1_CH3
      \arg        POC_MASK_SOURCE_TIMER2_CH0: detection is masked by TIMER2_CH0
      \arg        POC_MASK_SOURCE_TIMER2_CH1: detection is masked by TIMER2_CH1
      \arg        POC_MASK_SOURCE_TIMER2_CH2: detection is masked by TIMER2_CH2
      \arg        POC_MASK_SOURCE_TIMER2_CH3: detection is masked by TIMER2_CH3
      \arg        POC_MASK_SOURCE_GPTIMER0_CH0: detection is masked by GPTIMER0_CH0
      \arg        POC_MASK_SOURCE_GPTIMER0_CH1: detection is masked by GPTIMER0_CH1
      \arg        POC_MASK_SOURCE_GPTIMER1_CH0: detection is masked by GPTIMER1_CH0
      \arg        POC_MASK_SOURCE_GPTIMER1_CH1: detection is masked by GPTIMER1_CH1
    \param[out] none
    \retval     none
*/
void poc_input_detection_mask(poc_pin_enum poc_pin, uint32_t mask_source)
{
    switch(poc_pin) {
    case POC_IN0:
        POC_IN0DMK = mask_source;
        break;
    case POC_IN1:
        POC_IN1DMK = mask_source;
        break;
    case POC_IN2:
        POC_IN2DMK = mask_source;
        break;
    case POC_IN3:
        POC_IN3DMK = mask_source;
        break;
    case POC_IN4:
        POC_IN4DMK = mask_source;
        break;
    case POC_IN5:
        POC_IN5DMK = mask_source;
        break;
    default:
        break;
    }
}

/*!
    \brief      mask comparator output detection (API_ID(0x0016U))
    \param[in]  cmp_output: CMPx_OUT (n=0..3)
    \param[in]  mask_source: mask source selection
                only one parameter can be selected which are shown as below:
      \arg        POC_REQUEST_NOT_MASKED: detection is not masked
      \arg        POC_MASK_SOURCE_TIMER0_CH0: detection is masked by TIMER0_CH0
      \arg        POC_MASK_SOURCE_TIMER0_CH1: detection is masked by TIMER0_CH1
      \arg        POC_MASK_SOURCE_TIMER0_CH2: detection is masked by TIMER0_CH2
      \arg        POC_MASK_SOURCE_TIMER0_CH3: detection is masked by TIMER0_CH3
      \arg        POC_MASK_SOURCE_TIMER0_MCH0: detection is masked by TIMER0_MCH0
      \arg        POC_MASK_SOURCE_TIMER0_MCH1: detection is masked by TIMER0_MCH1
      \arg        POC_MASK_SOURCE_TIMER0_MCH2: detection is masked by TIMER0_MCH2
      \arg        POC_MASK_SOURCE_TIMER0_MCH3: detection is masked by TIMER0_MCH3
      \arg        POC_MASK_SOURCE_TIMER7_CH0: detection is masked by TIMER7_CH0
      \arg        POC_MASK_SOURCE_TIMER7_CH1: detection is masked by TIMER7_CH1
      \arg        POC_MASK_SOURCE_TIMER7_CH2: detection is masked by TIMER7_CH2
      \arg        POC_MASK_SOURCE_TIMER7_CH3: detection is masked by TIMER7_CH3
      \arg        POC_MASK_SOURCE_TIMER7_MCH0: detection is masked by TIMER7_MCH0
      \arg        POC_MASK_SOURCE_TIMER7_MCH1: detection is masked by TIMER7_MCH1
      \arg        POC_MASK_SOURCE_TIMER7_MCH2: detection is masked by TIMER7_MCH2
      \arg        POC_MASK_SOURCE_TIMER7_MCH3: detection is masked by TIMER7_MCH3
      \arg        POC_MASK_SOURCE_TIMER1_CH0: detection is masked by TIMER1_CH0
      \arg        POC_MASK_SOURCE_TIMER1_CH1: detection is masked by TIMER1_CH1
      \arg        POC_MASK_SOURCE_TIMER1_CH2: detection is masked by TIMER1_CH2
      \arg        POC_MASK_SOURCE_TIMER1_CH3: detection is masked by TIMER1_CH3
      \arg        POC_MASK_SOURCE_TIMER2_CH0: detection is masked by TIMER2_CH0
      \arg        POC_MASK_SOURCE_TIMER2_CH1: detection is masked by TIMER2_CH1
      \arg        POC_MASK_SOURCE_TIMER2_CH2: detection is masked by TIMER2_CH2
      \arg        POC_MASK_SOURCE_TIMER2_CH3: detection is masked by TIMER2_CH3
      \arg        POC_MASK_SOURCE_GPTIMER0_CH0: detection is masked by GPTIMER0_CH0
      \arg        POC_MASK_SOURCE_GPTIMER0_CH1: detection is masked by GPTIMER0_CH1
      \arg        POC_MASK_SOURCE_GPTIMER1_CH0: detection is masked by GPTIMER1_CH0
      \arg        POC_MASK_SOURCE_GPTIMER1_CH1: detection is masked by GPTIMER1_CH1
    \param[out] none
    \retval     none
*/
void poc_cmp_output_detection_mask(cmp_output_enum cmp_output, uint32_t mask_source)
{
    switch(cmp_output) {
    case CMP0_OUT:
        POC_CMP0DMK = mask_source;
        break;
    case CMP1_OUT:
        POC_CMP1DMK = mask_source;
        break;
    case CMP2_OUT:
        POC_CMP2DMK = mask_source;
        break;
    case CMP3_OUT:
        POC_CMP3DMK = mask_source;
        break;
    default:
        break;
    }
}

/*!
    \brief      get the POC flag (API_ID(0x0017U))
    \param[in]  flag: the POC flags, only one parameter can be selected which is shown
                as below:
      \arg        POC_FLAG_IN0IF: POC_IN0 input detection flag
      \arg        POC_FLAG_IN1IF: POC_IN1 input detection flag
      \arg        POC_FLAG_IN2IF: POC_IN2 input detection flag
      \arg        POC_FLAG_IN3IF: POC_IN3 input detection flag
      \arg        POC_FLAG_IN4IF: POC_IN4 input detection flag
      \arg        POC_FLAG_IN5IF: POC_IN5 input detection flag
      \arg        POC_FLAG_HXTALSDF: HXTAL stuck detection flag
      \arg        POC_FLAG_LOCKUPDF: CPU LOCKUP detection flag
      \arg        POC_FLAG_TIMER0_CCIF: TIMER0 concurrent conduction detection flag
      \arg        POC_FLAG_TIMER7_CCIF: TIMER7 concurrent conduction detection flag
      \arg        POC_FLAG_CMP0DF: comparator 0 detection flag
      \arg        POC_FLAG_CMP1DF: comparator 1 detection flag
      \arg        POC_FLAG_CMP2DF: comparator 2 detection flag
      \arg        POC_FLAG_CMP3DF: comparator 3 detection flag
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus poc_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;

    if(flag & POC_STAT_FLAG_MASK0) {
        /* check POC_STAT0 flag */
        if(RESET != (POC_STAT0 & flag)) {
            reval = SET;
        } else {
            reval = RESET;
        }
    } else if(flag & POC_STAT_FLAG_MASK1) {
        /* check POC_STAT1 flag */
        if(RESET != (POC_STAT1 & (flag >> 24U))) {
            reval = SET;
        } else {
            reval = RESET;
        }
    } else {
        /* illegal parameters */
    }

    return reval;
}

/*!
    \brief      clear the POC flag (API_ID(0x0018U))
    \param[in]  flag: the POC flags, only one parameter can be selected which is shown
                as below:
      \arg        POC_FLAG_IN0IF: POC_IN0 input detection flag
      \arg        POC_FLAG_IN1IF: POC_IN1 input detection flag
      \arg        POC_FLAG_IN2IF: POC_IN2 input detection flag
      \arg        POC_FLAG_IN3IF: POC_IN3 input detection flag
      \arg        POC_FLAG_IN4IF: POC_IN4 input detection flag
      \arg        POC_FLAG_IN5IF: POC_IN5 input detection flag
      \arg        POC_FLAG_HXTALSDF: HXTAL stuck detection flag
      \arg        POC_FLAG_LOCKUPDF: CPU LOCKUP detection flag
      \arg        POC_FLAG_TIMER0_CCIF: TIMER0 concurrent conduction detection flag
      \arg        POC_FLAG_TIMER7_CCIF: TIMER7 concurrent conduction detection flag
      \arg        POC_FLAG_CMP0DF: comparator 0 detection flag
      \arg        POC_FLAG_CMP1DF: comparator 1 detection flag
      \arg        POC_FLAG_CMP2DF: comparator 2 detection flag
      \arg        POC_FLAG_CMP3DF: comparator 3 detection flag
    \param[out] none
    \retval     none
*/
void poc_flag_clear(uint32_t flag)
{
    if(flag & POC_STAT_FLAG_MASK0) {
        /* clear POC_STAT0 flag */
        POC_STAT0 = ~(uint32_t)(flag & POC_STAT_FLAG_MASK0);
    } else if(flag & POC_STAT_FLAG_MASK1) {
        /* clear POC_STAT1 flag */
        POC_STAT1 = ~(uint32_t)((flag & POC_STAT_FLAG_MASK1) >> 24U);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable POC interrupt (API_ID(0x0019U))
    \param[in]  interrupt:
                only one parameter can be selected which are shown as below:
      \arg        POC_INT_IN0: POC_IN0 input detection interrupt
      \arg        POC_INT_IN1: POC_IN1 input detection interrupt
      \arg        POC_INT_IN2: POC_IN2 input detection interrupt
      \arg        POC_INT_IN3: POC_IN3 input detection interrupt
      \arg        POC_INT_IN4: POC_IN4 input detection interrupt
      \arg        POC_INT_IN5: POC_IN5 input detection interrupt
      \arg        POC_INT_TIMER0CC: TIMER0 concurrent conduction detection interrupt
      \arg        POC_INT_TIMER7CC: TIMER7 concurrent conduction detection interrupt
    \param[out] none
    \retval     none
*/
void poc_interrupt_enable(poc_interrupt_enum interrupt)
{
    switch(interrupt) {
    /* enable POC_IN0 input detection interrupt */
    case POC_INT_IN0:
        POC_IN0DCFG_15_8 |= (uint8_t)(POC_INnDCFG_INIE >> 8U);
        break;
    /* enable POC_IN1 input detection interrupt */
    case POC_INT_IN1:
        POC_IN1DCFG_15_8 |= (uint8_t)(POC_INnDCFG_INIE >> 8U);
        break;
    /* enable POC_IN2 input detection interrupt */
    case POC_INT_IN2:
        POC_IN2DCFG_15_8 |= (uint8_t)(POC_INnDCFG_INIE >> 8U);
        break;
    /* enable POC_IN3 input detection interrupt */
    case POC_INT_IN3:
        POC_IN3DCFG_15_8 |= (uint8_t)(POC_INnDCFG_INIE >> 8U);
        break;
    /* enable POC_IN4 input detection interrupt */
    case POC_INT_IN4:
        POC_IN4DCFG_15_8 |= (uint8_t)(POC_INnDCFG_INIE >> 8U);
        break;
    /* enable POC_IN5 input detection interrupt */
    case POC_INT_IN5:
        POC_IN5DCFG_15_8 |= (uint8_t)(POC_INnDCFG_INIE >> 8U);
        break;
    /* enable TIMER0 concurrent conduction detection interrupt */
    case POC_INT_TIMER0CC:
        POC_CDCFG0 |= (uint32_t)POC_CDCFG0_TIMER0_CCIE;
        break;
    /* enable TIMER7 concurrent conduction detection interrupt */
    case POC_INT_TIMER7CC:
        POC_CDCFG1 |= (uint32_t)POC_CDCFG1_TIMER7_CCIE;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable POC interrupt (API_ID(0x001AU))
    \param[in]  interrupt:
                only one parameter can be selected which are shown as below:
      \arg        POC_INT_IN0: POC_IN0 input detection interrupt
      \arg        POC_INT_IN1: POC_IN1 input detection interrupt
      \arg        POC_INT_IN2: POC_IN2 input detection interrupt
      \arg        POC_INT_IN3: POC_IN3 input detection interrupt
      \arg        POC_INT_IN4: POC_IN4 input detection interrupt
      \arg        POC_INT_IN5: POC_IN5 input detection interrupt
      \arg        POC_INT_TIMER0CC: TIMER0 concurrent conduction detection interrupt
      \arg        POC_INT_TIMER7CC: TIMER7 concurrent conduction detection interrupt
    \param[out] none
    \retval     none
*/
void poc_interrupt_disable(poc_interrupt_enum interrupt)
{
    switch(interrupt) {
    /* enable POC_IN0 input detection interrupt */
    case POC_INT_IN0:
        POC_IN0DCFG_15_8 &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INIE >> 8U));
        break;
    /* enable POC_IN1 input detection interrupt */
    case POC_INT_IN1:
        POC_IN1DCFG_15_8 &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INIE >> 8U));
        break;
    /* enable POC_IN2 input detection interrupt */
    case POC_INT_IN2:
        POC_IN2DCFG_15_8 &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INIE >> 8U));
        break;
    /* enable POC_IN3 input detection interrupt */
    case POC_INT_IN3:
        POC_IN3DCFG_15_8 &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INIE >> 8U));
        break;
    /* enable POC_IN4 input detection interrupt */
    case POC_INT_IN4:
        POC_IN4DCFG_15_8 &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INIE >> 8U));
        break;
    /* enable POC_IN5 input detection interrupt */
    case POC_INT_IN5:
        POC_IN5DCFG_15_8 &= (uint8_t)(~(uint8_t)(POC_INnDCFG_INIE >> 8U));
        break;
    /* enable TIMER0 concurrent conduction detection interrupt */
    case POC_INT_TIMER0CC:
        POC_CDCFG0 &= (uint32_t)(~(uint32_t)POC_CDCFG0_TIMER0_CCIE);
        break;
    /* enable TIMER7 concurrent conduction detection interrupt */
    case POC_INT_TIMER7CC:
        POC_CDCFG1 &= (uint32_t)(~(uint32_t)POC_CDCFG1_TIMER7_CCIE);
        break;
    default:
        break;
    }
}

/*!
    \brief      get POC interrupt flag (API_ID(0x001BU))
    \param[in]  int_flag: the POC flags, only one parameter can be selected which is shown
                as below:
      \arg        POC_INT_FLAG_IN0IF: POC_IN0 input interrupt flag
      \arg        POC_INT_FLAG_IN1IF: POC_IN1 input interrupt flag
      \arg        POC_INT_FLAG_IN2IF: POC_IN2 input interrupt flag
      \arg        POC_INT_FLAG_IN3IF: POC_IN3 input interrupt flag
      \arg        POC_INT_FLAG_IN4IF: POC_IN4 input interrupt flag
      \arg        POC_INT_FLAG_IN5IF: POC_IN5 input interrupt flag
      \arg        POC_INT_FLAG_TIMER0_CCIF: TIMER0 concurrent conduction interrupt flag
      \arg        POC_INT_FLAG_TIMER7_CCIF: TIMER7 concurrent conduction interrupt flag
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus poc_interrupt_flag_get(uint32_t int_flag)
{
    uint32_t intstatus = 0U, flagstatus = 0U;
    FlagStatus retval = RESET;

    switch(int_flag) {
    case POC_INT_FLAG_IN0IF:
        /* check POC_INT_FLAG_IN0IF flag */
        flagstatus = POC_STAT0 & POC_INT_FLAG_IN0IF;
        intstatus = POC_IN0DCFG & POC_INnDCFG_INIE;
        break;
    case POC_INT_FLAG_IN1IF:
        /* check POC_INT_FLAG_IN1IF flag */
        flagstatus = POC_STAT0 & POC_INT_FLAG_IN1IF;
        intstatus = POC_IN1DCFG & POC_INnDCFG_INIE;
        break;
    case POC_INT_FLAG_IN2IF:
        /* check POC_INT_FLAG_IN2IF flag */
        flagstatus = POC_STAT0 & POC_INT_FLAG_IN2IF;
        intstatus = POC_IN2DCFG & POC_INnDCFG_INIE;
        break;
    case POC_INT_FLAG_IN3IF:
        /* check POC_INT_FLAG_IN3IF flag */
        flagstatus = POC_STAT0 & POC_INT_FLAG_IN3IF;
        intstatus = POC_IN3DCFG & POC_INnDCFG_INIE;
        break;
    case POC_INT_FLAG_IN4IF:
        /* check POC_INT_FLAG_IN4IF flag */
        flagstatus = POC_STAT0 & POC_INT_FLAG_IN4IF;
        intstatus = POC_IN4DCFG & POC_INnDCFG_INIE;
        break;
    case POC_INT_FLAG_IN5IF:
        /* check POC_INT_FLAG_IN5IF flag */
        flagstatus = POC_STAT0 & POC_INT_FLAG_IN5IF;
        intstatus = POC_IN5DCFG & POC_INnDCFG_INIE;
        break;
    case POC_INT_FLAG_TIMER0_CCIF:
        /* check POC_INT_FLAG_TIMER0_CCIF flag */
        flagstatus = POC_STAT0 & POC_INT_FLAG_TIMER0_CCIF;
        intstatus = POC_CDCFG0 & POC_CDCFG0_TIMER0_CCIE;
        break;
    case POC_INT_FLAG_TIMER7_CCIF:
        /* check POC_INT_FLAG_TIMER7_CCIF flag */
        flagstatus = POC_STAT0 & POC_INT_FLAG_TIMER7_CCIF;
        intstatus = POC_CDCFG1 & POC_CDCFG1_TIMER7_CCIE;
        break;
    default:
        break;
    }

    if((0U != flagstatus) && (0U != intstatus)) {
        retval = SET;
    } else {
        retval = RESET;
    }

    return retval;
}

/*!
    \brief      clear POC interrupt flag (API_ID(0x001CU))
    \param[in]  int_flag: the POC flags, one or more parameters can be selected which is shown
                as below:
      \arg        POC_INT_FLAG_IN0IF: POC_IN0 input interrupt flag
      \arg        POC_INT_FLAG_IN1IF: POC_IN1 input interrupt flag
      \arg        POC_INT_FLAG_IN2IF: POC_IN2 input interrupt flag
      \arg        POC_INT_FLAG_IN3IF: POC_IN3 input interrupt flag
      \arg        POC_INT_FLAG_IN4IF: POC_IN4 input interrupt flag
      \arg        POC_INT_FLAG_IN5IF: POC_IN5 input interrupt flag
      \arg        POC_INT_FLAG_TIMER0_CCIF: TIMER0 concurrent conduction interrupt flag
      \arg        POC_INT_FLAG_TIMER7_CCIF: TIMER7 concurrent conduction interrupt flag
    \param[out] none
    \retval     SET or RESET
*/
void poc_interrupt_flag_clear(uint32_t int_flag)
{
    if(int_flag & POC_INT_FLAG_MASK) {
        /* clear interrupt flag */
        POC_STAT0 = ~(uint32_t)(int_flag & POC_INT_FLAG_MASK);
    } else {
        /* illegal parameters */
    }
}
