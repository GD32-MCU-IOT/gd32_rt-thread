/*!
    \file    gd32m53x_gtoc.c
    \brief   GTOC driver

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

#include "gd32m53x_gtoc.h"

/* GTOC input parameter mask */
#define INT_FLAG_MASK                    ((uint8_t)0x03U)     /*!< GTOC interrupt flag mask */
#define FLAG_MASK                        ((uint8_t)0x0FU)     /*!< GTOC flag mask */

/*!
\brief      deinitialize GTOC (API_ID(0x0001U))
            note: some register bits can only be written once after reset, so these bits cannot be written after calling this function.
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[out] none
    \retval     none
*/
void gtoc_deinit(uint32_t gtoc_periph)
{
    GTOC_CFG(gtoc_periph) = ((uint32_t)0x00000000U);
    GTOC_OCRCTL(gtoc_periph) = ((uint32_t)0x00000000U);
    GTOC_WP(gtoc_periph) = GTOC_WPKEY_VALUE;
    GTOC_WP(gtoc_periph) = ((uint32_t)0x00000000U);
    GTOC_ECRCTL(gtoc_periph) = ((uint32_t)0x00000000U);
}

/*!
    \brief      enable GTOC output closing request (API_ID(0x0002U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[in]  gtoc_ocr_source: gtoc output closing request source
                one or more parameters can be selected which is shown as below:
    \arg        GTOC_OCR_SOURCE_GTOCPIN: GTOCx_IN pin input detection
    \arg        GTOC_OCR_SOURCE_GPTIMER: GPTIMER output fault detection
    \arg        GTOC_OCR_SOURCE_HXTALSTUCK: HXTAL stuck detection enable
    \arg        GTOC_OCR_SOURCE_LOCKUP: CPU LOCKUP detection
    \arg        GTOC_OCR_SOURCE_CMP0: CMP0 valid edge detection
    \arg        GTOC_OCR_SOURCE_CMP1: CMP1 valid edge detection
    \arg        GTOC_OCR_SOURCE_CMP2: CMP2 valid edge detection
    \arg        GTOC_OCR_SOURCE_CMP3: CMP3 valid edge detection
    \param[out] none
    \retval     none
*/
void gtoc_output_closing_request_enable(uint32_t gtoc_periph, uint16_t gtoc_ocr_source)
{
    GTOC_CFG_15_0(gtoc_periph) = (uint16_t)(0x000FU | gtoc_ocr_source);
}

/*!
    \brief      get GPTIMER external trigger input status (API_ID(0x0003U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[out] none
    \retval     none
*/
uint32_t gtoc_gptimer_trigger_status_get(uint32_t gtoc_periph)
{
    uint32_t reval = GPTIMER_TRIGGER_STATUS_LOW;

    if((uint32_t)RESET != (GTOC_CFG(gtoc_periph) & GTOC_CFG_GPTIMERETIS)) {
        reval = GPTIMER_TRIGGER_STATUS_HIGH;
    } else {
        reval = GPTIMER_TRIGGER_STATUS_LOW;
    }

    return reval;
}

/*!
    \brief      generate software output closing request (API_ID(0x0004U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[out] none
    \retval     none
*/
void gtoc_software_request_generate(uint32_t gtoc_periph)
{
    GTOC_CFG_31_16(gtoc_periph) |= (uint16_t)(GTOC_CFG_SWOCRG >> 16U);
}

/*!
    \brief      stop software output closing request (API_ID(0x0005U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[out] none
    \retval     none
*/
void gtoc_software_request_stop(uint32_t gtoc_periph)
{
    GTOC_CFG_31_16(gtoc_periph) &= (uint16_t)(~((uint16_t)(GTOC_CFG_SWOCRG >> 16U)));
}

/*!
    \brief      select GTOCx_IN input detection mode (API_ID(0x0006U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[in]  detection_mode: GTOCx_IN input detection mode
                only one parameter can be selected which is shown as below:
    \arg        GTOC_INPUT_DETECTION_LEVEL: level detection
    \arg        GTOC_INPUT_DETECTION_EDGE: edge detection
    \param[out] none
    \retval     none
*/
void gtoc_input_detection_mode_select(uint32_t gtoc_periph, uint32_t detection_mode)
{
    if(GTOC_INPUT_DETECTION_LEVEL == detection_mode) {
        GTOC_CFG_31_16(gtoc_periph) &= (uint16_t)(~((uint16_t)(GTOC_CFG_INDM >> 16U)));
    } else if(GTOC_INPUT_DETECTION_EDGE == detection_mode) {
        GTOC_CFG_31_16(gtoc_periph) |= (uint16_t)(GTOC_CFG_INDM >> 16U);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure GTOCx_IN input polarity (API_ID(0x0007U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[in]  input_polarity: GTOCx_IN input polarity
                only one parameter can be selected which is shown as below:
    \arg        GTOC_INPUT_POLARITY_NONINVERTED: GTOCx_IN input not inverted
    \arg        GTOC_INPUT_POLARITY_INVERTED: GTOCx_IN input inverted
    \param[out] none
    \retval     none
*/
void gtoc_input_polarity_config(uint32_t gtoc_periph, uint32_t input_polarity)
{
    if(GTOC_INPUT_POLARITY_NONINVERTED == input_polarity) {
        GTOC_CFG_31_16(gtoc_periph) &= (uint16_t)(~((uint16_t)(GTOC_CFGx_INPL >> 16U)));
    } else if(GTOC_INPUT_POLARITY_INVERTED == input_polarity) {
        GTOC_CFG_31_16(gtoc_periph) |= (uint16_t)(GTOC_CFGx_INPL >> 16U);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable GTOC digital filter (API_ID(0x0008U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[out] none
    \retval     none
*/
void gtoc_digital_filter_enable(uint32_t gtoc_periph)
{
    GTOC_CFG_31_16(gtoc_periph) |= (uint16_t)(GTOC_CFGx_DFEN >> 16U);
}

/*!
    \brief      disable GTOC digital filter (API_ID(0x0009U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[out] none
    \retval     none
*/
void gtoc_digital_filter_disable(uint32_t gtoc_periph)
{
    GTOC_CFG_31_16(gtoc_periph) &= (uint16_t)(~((uint16_t)(GTOC_CFGx_DFEN >> 16U)));
}

/*!
    \brief      configure GTOC digital filter (API_ID(0x000AU))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[in]  sampling_frequency: GTOCx digital filter sampling frequency
                only one parameter can be selected which is shown as below:
    \arg        GTOC_SAMPLING_FREQUENCY_DIV1: GTOC digital filter sampling frequency is fHCLK/1
    \arg        GTOC_SAMPLING_FREQUENCY_DIV8: GTOC digital filter sampling frequency is fHCLK/8
    \arg        GTOC_SAMPLING_FREQUENCY_DIV32: GTOC digital filter sampling frequency is fHCLK/32
    \arg        GTOC_SAMPLING_FREQUENCY_DIV128: GTOC digital filter sampling frequency is fHCLK/128
    \arg        GTOC_SAMPLING_FREQUENCY_DIV2: GTOC digital filter sampling frequency is fHCLK/2
    \arg        GTOC_SAMPLING_FREQUENCY_DIV4: GTOC digital filter sampling frequency is fHCLK/4
    \arg        GTOC_SAMPLING_FREQUENCY_DIV16: GTOC digital filter sampling frequency is fHCLK/16
    \arg        GTOC_SAMPLING_FREQUENCY_DIV64: GTOC digital filter sampling frequency is fHCLK/64
    \arg        GTOC_SAMPLING_FREQUENCY_DIV256: GTOC digital filter sampling frequency is fHCLK/256
    \arg        GTOC_SAMPLING_FREQUENCY_DIV512: GTOC digital filter sampling frequency is fHCLK/512
    \param[in]  sampling_number: GTOCx digital filter sampling number
                only one parameter can be selected which is shown as below:
    \arg        GTOC_SAMPLING_NUM_3_TIMES: GTOC digital filter sampling number is three times
    \arg        GTOC_SAMPLING_NUM_4_TIMES: GTOC digital filter sampling number is four times
    \arg        GTOC_SAMPLING_NUM_5_TIMES: GTOC digital filter sampling number is five times
    \arg        GTOC_SAMPLING_NUM_6_TIMES: GTOC digital filter sampling number is six times
    \param[out] none
    \retval     none
*/
void gtoc_digital_filter_config(uint32_t gtoc_periph, uint32_t sampling_frequency, uint32_t sampling_number)
{
    GTOC_CFG_31_16(gtoc_periph) &= (uint16_t)(~((uint16_t)((GTOC_CFG_DFSNUM | GTOC_CFGx_DFSCDIV) >> 16U)));
    GTOC_CFG_31_16(gtoc_periph) |= (uint16_t)(((sampling_frequency & GTOC_CFGx_DFSCDIV) | (sampling_number & GTOC_CFG_DFSNUM)) >> 16U);
}

/*!
    \brief      mask GTOC output closing request (API_ID(0x000BU))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[in]  mask_source: mask source for output closing request
                only one parameter can be selected which is shown as below:
    \arg        GTOC_OCRMKSEL_NOT_MASKED: Output closing request is not masked
    \arg        GTOC_OCRMKSEL_GPTIMER0_CH0: Output closing request is masked by GPTIMER0_CH0
    \arg        GTOC_OCRMKSEL_GPTIMER0_CH1: Output closing request is masked by GPTIMER0_CH1
    \arg        GTOC_OCRMKSEL_GPTIMER1_CH0: Output closing request is masked by GPTIMER1_CH0
    \arg        GTOC_OCRMKSEL_GPTIMER1_CH1: Output closing request is masked by GPTIMER1_CH1
    \param[out] none
    \retval     none
*/
void gtoc_output_closing_request_mask(uint32_t gtoc_periph, uint32_t mask_source)
{
    GTOC_OCRCTL(gtoc_periph) = (uint32_t)mask_source;
}

/*!
    \brief      enable GTOC extended closing request control register write (API_ID(0x000CU))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[out] none
    \retval     none
*/
void gtoc_register_write_enable(uint32_t gtoc_periph)
{
    GTOC_WP(gtoc_periph) = (uint32_t)GTOC_WPKEY_VALUE;
}

/*!
    \brief      disable GTOC extended closing request control register write (API_ID(0x000DU))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[out] none
    \retval     none
*/
void gtoc_register_write_disable(uint32_t gtoc_periph)
{
    GTOC_WP(gtoc_periph) = (uint32_t)(GTOC_WPKEY_VALUE | GTOC_WP_WREN);
}

/*!
    \brief      enable extended closing request (API_ID(0x000EU))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[out] none
    \retval     none
*/
void gtoc_extended_closing_request_enable(uint32_t gtoc_periph)
{
    GTOC_ECRCTL_7_0(gtoc_periph) |= (uint8_t)GTOC_ECRCTL_ECREN;
}

/*!
    \brief      disable extended closing request (API_ID(0x000FU))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[out] none
    \retval     none
*/
void gtoc_extended_closing_request_disable(uint32_t gtoc_periph)
{
    GTOC_ECRCTL_7_0(gtoc_periph) &= (uint8_t)(~((uint8_t)GTOC_ECRCTL_ECREN));
}

/*!
    \brief      configure extended closing request (API_ID(0x0010U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[in]  gtoc_ecr_source: gtoc extended closing request source
                only one parameter can be selected which is shown as below:
    \arg        GTOC_ECR_SOURCE_CMP0: CMP0 level detection
    \arg        GTOC_ECR_SOURCE_CMP1: CMP1 level detection
    \arg        GTOC_ECR_SOURCE_CMP2: CMP2 level detection
    \arg        GTOC_ECR_SOURCE_CMP3: CMP3 level detection
    \arg        GTOC_ECR_SOURCE_GTOCPIN: GTOCx_IN input level detection
    \param[in]  valid_level: valid level
                only one parameter can be selected which is shown as below:
    \arg        GTOC_VALID_LEVEL_LOW: low level is valid
    \arg        GTOC_VALID_LEVEL_HIGH: high level is valid
    \param[out] none
    \retval     none
*/
void gtoc_extended_closing_request_config(uint32_t gtoc_periph, uint32_t gtoc_ecr_source, uint32_t valid_level)
{
    GTOC_ECRCTL_15_0(gtoc_periph) &= (uint16_t)(~((uint16_t)(GTOC_ECRCTL_ECRSSEL | GTOC_ECRCTL_ECRVLSEL)));
    GTOC_ECRCTL_15_0(gtoc_periph) |= (uint16_t)((gtoc_ecr_source & GTOC_ECRCTL_ECRSSEL) | (valid_level & GTOC_ECRCTL_ECRVLSEL));
}

/*!
    \brief      mask GTOC extended closing request (API_ID(0x0011U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[in]  mask_source: mask source for extended closing request
                only one parameter can be selected which is shown as below:
    \arg        GTOC_ECRMKSEL_NOT_MASKED: Extended closing request is not masked
    \arg        GTOC_ECRMKSEL_GPTIMER0_CH0: Extended closing request is masked by GPTIMER0_CH0
    \arg        GTOC_ECRMKSEL_GPTIMER0_CH1: Extended closing request is masked by GPTIMER0_CH1
    \arg        GTOC_ECRMKSEL_GPTIMER1_CH0: Extended closing request is masked by GPTIMER1_CH0
    \arg        GTOC_ECRMKSEL_GPTIMER1_CH1: Extended closing request is masked by GPTIMER1_CH1
    \param[out] none
    \retval     none
*/
void gtoc_extended_closing_request_mask(uint32_t gtoc_periph, uint32_t mask_source)
{
    GTOC_ECRCTL_15_8(gtoc_periph) &= (uint8_t)(~((uint8_t)(GTOC_EXTCTL_ECRMKSEL >> 8U)));
    GTOC_ECRCTL_15_8(gtoc_periph) |= (uint8_t)((mask_source & GTOC_EXTCTL_ECRMKSEL) >> 8U);
}

/*!
    \brief      get GTOC flag (API_ID(0x0012U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[in]  flag: GTOC flag
                one or more parameter can be selected which is shown as below:
    \arg        GTOC_FLAG_INIF: GTOCx_IN input interrupt flag
    \arg        GTOC_FLAG_OFVEIF: GPTIMER output fault or CMP valid edge interrupt flag
    \arg        GTOC_FLAG_HXTALSDF: HXTAL stuck detection flag
    \arg        GTOC_FLAG_LOCKUPDF: CPU LOCKUP detection flag
    \param[out] none
    \retval     none
*/
FlagStatus gtoc_flag_get(uint32_t gtoc_periph, uint32_t flag)
{
    FlagStatus reval = RESET;

    if(0U != (GTOC_CFG(gtoc_periph) & flag)) {
        reval = SET;
    } else {
        /* illegal parameters */
    }

    return reval;
}

/*!
    \brief      clear GTOC flag (API_ID(0x0013U))
                note: some register bits can only be written once after reset, after calling this function, it is invalid
                to enable GTOCx_IN pin input detection, GPTIMER output fault detection, HXTAL stuck detection, and CPU
                LOCKUP detection by gtoc_output_closing_request_enable function.
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[in]  flag: GTOC flag
                one or more parameter can be selected which is shown as below:
    \arg        GTOC_FLAG_INIF: GTOCx_IN input interrupt flag
    \arg        GTOC_FLAG_OFVEIF: GPTIMER output fault or CMP valid edge interrupt flag
    \arg        GTOC_FLAG_HXTALSDF: HXTAL stuck detection flag
    \arg        GTOC_FLAG_LOCKUPDF: CPU LOCKUP detection flag
    \param[out] none
    \retval     none
*/
void gtoc_flag_clear(uint32_t gtoc_periph, uint32_t flag)
{
    GTOC_CFG_7_0(gtoc_periph) = ((uint8_t)((~((uint8_t)(flag & FLAG_MASK))) & 0x0FU));
}

/*!
    \brief      get GTOC interrupt flag (API_ID(0x0014U))
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[in]  int_flag: GTOC interrupt flag
                one or more parameter can be selected which is shown as below:
    \arg        GTOC_INT_FLAG_INIF: GTOCx_IN input interrupt flag
    \arg        GTOC_INT_FLAG_OFVEIF: GPTIMER output fault or CMP valid edge interrupt flag
    \param[out] none
    \retval     none
*/
FlagStatus gtoc_interrupt_flag_get(uint32_t gtoc_periph, uint32_t int_flag)
{
    FlagStatus reval = RESET;

    if(0U != (GTOC_CFG(gtoc_periph) & int_flag)) {
        reval = SET;
    } else {
        /* illegal parameters */
    }

    return reval;
}

/*!
    \brief      clear GTOC interrupt flag (API_ID(0x0015U))
                note: some register bits can only be written once after reset, after calling this function, it is invalid
                to enable GTOCx_IN pin input detection, GPTIMER output fault detection, HXTAL stuck detection, and CPU
                LOCKUP detection by gtoc_output_closing_request_enable function.
    \param[in]  gtoc_periph: GTOCx (x=0..3)
    \param[in]  int_flag: GTOC interrupt flag
                one or more parameter can be selected which is shown as below:
    \arg        GTOC_INT_FLAG_INIF: GTOCx_IN input interrupt flag
    \arg        GTOC_INT_FLAG_OFVEIF: GPTIMER output fault or CMP valid edge interrupt flag
    \param[out] none
    \retval     none
*/
void gtoc_interrupt_flag_clear(uint32_t gtoc_periph, uint32_t int_flag)
{
    GTOC_CFG_7_0(gtoc_periph) = ((uint8_t)((~((uint8_t)(int_flag & INT_FLAG_MASK)))) & 0x0FU);
}
