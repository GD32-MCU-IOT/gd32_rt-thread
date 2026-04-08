/*!
    \file    gd32m53x_gtoc.h
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

#ifndef GD32M53X_GTOC_H
#define GD32M53X_GTOC_H

#include "gd32m53x.h"

/* GTOC definitions */
#define GTOC0                                  (GTOC_BASE + 0x00000000U)             /*!< GTOC0 base address */
#define GTOC1                                  (GTOC_BASE + 0x00000010U)             /*!< GTOC1 base address */
#define GTOC2                                  (GTOC_BASE + 0x00000020U)             /*!< GTOC2 base address */
#define GTOC3                                  (GTOC_BASE + 0x00000030U)             /*!< GTOC3 base address */

/* registers definitions */
#define GTOC_CFG(GTOCx)                        REG32((GTOCx) + 0x00000000U)          /*!< GTOCx configuration register */
#define GTOC_CFG_7_0(GTOCx)                    REG8((GTOCx) + 0x00000000U)           /*!< GTOCx configuration register low 8 bits */
#define GTOC_CFG_15_0(GTOCx)                   REG16((GTOCx) + 0x00000000U)          /*!< GTOCx configuration register low 16 bits */
#define GTOC_CFG_31_16(GTOCx)                  REG16((GTOCx) + 0x00000002U)          /*!< GTOCx configuration register high 16 bits */
#define GTOC_OCRCTL(GTOCx)                     REG32((GTOCx) + 0x00000004U)          /*!< GTOCx output closing request control register */
#define GTOC_WP(GTOCx)                         REG32((GTOCx) + 0x00000008U)          /*!< GTOCx write protection register */
#define GTOC_ECRCTL(GTOCx)                     REG32((GTOCx) + 0x0000000CU)          /*!< GTOCx extended closing request control register */
#define GTOC_ECRCTL_7_0(GTOCx)                 REG8((GTOCx) + 0x0000000CU)           /*!< GTOCx extended closing request control register 0-7 bits */
#define GTOC_ECRCTL_15_0(GTOCx)                REG16((GTOCx) + 0x0000000CU)          /*!< GTOCx extended closing request control register 0-15 bits */
#define GTOC_ECRCTL_15_8(GTOCx)                REG8((GTOCx) + 0x0000000DU)           /*!< GTOCx extended closing request control register 8-15 bits */

/* bits definitions */
/* GTOCx_CFG */
#define GTOC_CFG_INIF                          BIT(0)                                /*!< GTOCx_IN input interrupt flag */
#define GTOC_CFG_OFVEIF                        BIT(1)                                /*!< GPTIMER output fault or CMP valid edge interrupt flag */
#define GTOC_CFG_HXTALSDF                      BIT(2)                                /*!< HXTAL stuck detection flag */
#define GTOC_CFG_LOCKUPDF                      BIT(3)                                /*!< CPU LOCKUP detection flag */
#define GTOC_CFG_INDEN                         BIT(4)                                /*!< GTOCx_IN input detection enable */
#define GTOC_CFG_GPTIMERFDEN                   BIT(5)                                /*!< GPTIMER output fault detection enable */
#define GTOC_CFG_HXTALSDEN                     BIT(6)                                /*!< HXTAL stuck detection enable */
#define GTOC_CFG_LOCKUPDEN                     BIT(7)                                /*!< CPU LOCKUP detection enable */
#define GTOC_CFG_CMP0EDEN                      BIT(8)                                /*!< CMP0 valid edge detection enable */
#define GTOC_CFG_CMP1EDEN                      BIT(9)                                /*!< CMP1 valid edge detection enable */
#define GTOC_CFG_CMP2EDEN                      BIT(10)                               /*!< CMP2 valid edge detection enable */
#define GTOC_CFG_CMP3EDEN                      BIT(11)                               /*!< CMP3 valid edge detection enable */
#define GTOC_CFG_GPTIMERETIS                   BIT(16)                               /*!< GPTIMER external trigger input x status */
#define GTOC_CFG_SWOCRG                        BIT(17)                               /*!< Software output closing request generation */
#define GTOC_CFG_INDM                          BIT(25)                               /*!< GTOCx_IN input detection mode */
#define GTOC_CFG_DFSNUM                        BITS(26,27)                           /*!< GTOCx digital filter sampling number */
#define GTOC_CFGx_INPL                         BIT(28)                               /*!< Polarity of GTOCx_IN input */
#define GTOC_CFGx_DFEN                         BIT(29)                               /*!< GTOCx digital filter enable */
#define GTOC_CFGx_DFSCDIV                      (BITS(23,24) | BITS(30,31))           /*!< GTOCx digital filter sampling clock division */

/* GTOCx_OCRCTL */
#define GTOC_OCRCTL_OCRMKSEL                   BITS(0,2)                             /*!< Output closing request mask selection */

/* GTOCx_WP */
#define GTOC_WP_WREN                           BIT(0)                                /*!< GTOCx_ECRCTL register write enable */
#define GTOC_WP_WPKEY                          BITS(8,15)                            /*!< Write protect key */

/* GTOCx_ECRCTL */
#define GTOC_ECRCTL_ECREN                      BIT(0)                                /*!< Extended closing request enable */
#define GTOC_ECRCTL_ECRSSEL                    BITS(4,6)                             /*!< Extended closing request source selection */
#define GTOC_ECRCTL_ECRVLSEL                   BIT(8)                                /*!< Extended closing request valid level selection */
#define GTOC_EXTCTL_ECRMKSEL                   BITS(11,13)                           /*!< Extended closing request mask selection */

/* constants definitions */

/* GTOCx_IN pin input detection enable */
#define GTOC_OCR_SOURCE_GTOCPIN                  ((uint16_t)GTOC_CFG_INDEN)            /*!< GTOCx_IN pin input detection */

/* GPTIMER output fault detection enable */
#define GTOC_OCR_SOURCE_GPTIMER                  ((uint16_t)GTOC_CFG_GPTIMERFDEN)      /*!< GTOCx_IN pin input detection */

/* HXTAL stuck detection enable */
#define GTOC_OCR_SOURCE_HXTALSTUCK               ((uint16_t)GTOC_CFG_HXTALSDEN)        /*!< GTOCx_IN pin input detection */

/* CPU LOCKUP detection enable */
#define GTOC_OCR_SOURCE_LOCKUP                   ((uint16_t)GTOC_CFG_LOCKUPDEN)        /*!< CPU LOCKUP detection */

/* CMP0 valid edge detection enable */
#define GTOC_OCR_SOURCE_CMP0                     ((uint16_t)GTOC_CFG_CMP0EDEN)         /*!< CMP0 valid edge detection */

/* CMP1 valid edge detection enable */
#define GTOC_OCR_SOURCE_CMP1                     ((uint16_t)GTOC_CFG_CMP1EDEN)         /*!< CMP1 valid edge detection */

/* CMP2 valid edge detection enable */
#define GTOC_OCR_SOURCE_CMP2                     ((uint16_t)GTOC_CFG_CMP2EDEN)         /*!< CMP2 valid edge detection */

/* CMP3 valid edge detection enable */
#define GTOC_OCR_SOURCE_CMP3                     ((uint16_t)GTOC_CFG_CMP3EDEN)         /*!< CMP3 valid edge detection */

/* GTOCx digital filter sampling number */
#define CFG_DFSNUM(regval)                       (BITS(26,27) & ((uint32_t)(regval) << 26))
#define GTOC_SAMPLING_NUM_3_TIMES                CFG_DFSNUM(0)                       /*!< GTOC digital filter sampling number is three times */
#define GTOC_SAMPLING_NUM_4_TIMES                CFG_DFSNUM(1)                       /*!< GTOC digital filter sampling number is four times */
#define GTOC_SAMPLING_NUM_5_TIMES                CFG_DFSNUM(2)                       /*!< GTOC digital filter sampling number is five times */
#define GTOC_SAMPLING_NUM_6_TIMES                CFG_DFSNUM(3)                       /*!< GTOC digital filter sampling number is six times */

/* GTOCx digital filter sampling frequency */
#define CFG_DFSCDIV(regval0,regval1)             ((BITS(23,24) & ((uint32_t)(regval0) << 23)) | (BITS(30,31) & ((uint32_t)(regval1) << 30)))
#define GTOC_SAMPLING_FREQUENCY_DIV1             CFG_DFSCDIV(0,0)                    /*!< GTOC digital filter sampling is fHCLK/1 */
#define GTOC_SAMPLING_FREQUENCY_DIV8             CFG_DFSCDIV(0,1)                    /*!< GTOC digital filter sampling is fHCLK/8 */
#define GTOC_SAMPLING_FREQUENCY_DIV32            CFG_DFSCDIV(0,2)                    /*!< GTOC digital filter sampling is fHCLK/32 */
#define GTOC_SAMPLING_FREQUENCY_DIV128           CFG_DFSCDIV(0,3)                    /*!< GTOC digital filter sampling is fHCLK/128 */
#define GTOC_SAMPLING_FREQUENCY_DIV2             CFG_DFSCDIV(1,0)                    /*!< GTOC digital filter sampling is fHCLK/2 */
#define GTOC_SAMPLING_FREQUENCY_DIV4             CFG_DFSCDIV(1,1)                    /*!< GTOC digital filter sampling is fHCLK/4 */
#define GTOC_SAMPLING_FREQUENCY_DIV16            CFG_DFSCDIV(1,2)                    /*!< GTOC digital filter sampling is fHCLK/16 */
#define GTOC_SAMPLING_FREQUENCY_DIV64            CFG_DFSCDIV(1,3)                    /*!< GTOC digital filter sampling is fHCLK/64 */
#define GTOC_SAMPLING_FREQUENCY_DIV256           CFG_DFSCDIV(2,0)                    /*!< GTOC digital filter sampling is fHCLK/256 */
#define GTOC_SAMPLING_FREQUENCY_DIV512           CFG_DFSCDIV(2,1)                    /*!< GTOC digital filter sampling is fHCLK/512 */

/* Polarity of GTOCx_IN input */
#define CFG_INPL(regval)                         (BIT(28) & ((uint32_t)(regval) << 28U))
#define GTOC_INPUT_POLARITY_NONINVERTED          CFG_INPL(0)                        /*!< GTOCx_IN input not inverted */
#define GTOC_INPUT_POLARITY_INVERTED             CFG_INPL(1)                        /*!< GTOCx_IN input inverted */

/* Output closing request mask source selection */
#define GTOC_OCRMKSEL_NOT_MASKED                 (0x00000000U)                      /*!< Output closing request is not masked */
#define GTOC_OCRMKSEL_GPTIMER0_CH0               (0x00000001U)                      /*!< Output closing request is masked by GPTIMER0_CH0 */
#define GTOC_OCRMKSEL_GPTIMER0_CH1               (0x00000002U)                      /*!< Output closing request is masked by GPTIMER0_CH1 */
#define GTOC_OCRMKSEL_GPTIMER1_CH0               (0x00000003U)                      /*!< Output closing request is masked by GPTIMER1_CH0 */
#define GTOC_OCRMKSEL_GPTIMER1_CH1               (0x00000004U)                      /*!< Output closing request is masked by GPTIMER1_CH1 */

/* Extended closing request valid level selection */
#define ECRCTL_ECRVLSEL(regval)                 (BIT(8) & ((uint32_t)(regval) << 8U))
#define GTOC_VALID_LEVEL_LOW                    ECRCTL_ECRVLSEL(0)                  /*!< low level is valid */
#define GTOC_VALID_LEVEL_HIGH                   ECRCTL_ECRVLSEL(1)                  /*!< high level is valid */

/* Write protect key */
#define GTOC_WPKEY_VALUE                         (0x0000A500U)                      /*!< Write protect key value */

/* Extended closing request source selection */
#define ECRCTL_ECRSSEL(regval)                   (BITS(4,6) & ((uint32_t)(regval) << 4))
#define GTOC_ECR_SOURCE_CMP0                     ECRCTL_ECRSSEL(0)                  /*!< CMP0 level detection */
#define GTOC_ECR_SOURCE_CMP1                     ECRCTL_ECRSSEL(1)                  /*!< CMP1 level detection */
#define GTOC_ECR_SOURCE_CMP2                     ECRCTL_ECRSSEL(2)                  /*!< CMP2 level detection */
#define GTOC_ECR_SOURCE_CMP3                     ECRCTL_ECRSSEL(3)                  /*!< CMP3 level detection */
#define GTOC_ECR_SOURCE_GTOCPIN                  ECRCTL_ECRSSEL(7)                  /*!< GTOCx_IN input level detection */

/* Extended closing request mask selection */
#define ECRCTL_ECRMKSEL(regval)               (BITS(11,13) & ((uint32_t)(regval) << 11))
#define GTOC_ECRMKSEL_NOT_MASKED              ECRCTL_ECRMKSEL(0)                    /*!< Extended closing request is not masked */
#define GTOC_ECRMKSEL_GPTIMER0_CH0            ECRCTL_ECRMKSEL(1)                    /*!< Extended closing request is masked by GPTIMER0_CH0 */
#define GTOC_ECRMKSEL_GPTIMER0_CH1            ECRCTL_ECRMKSEL(2)                    /*!< Extended closing request is masked by GPTIMER0_CH1 */
#define GTOC_ECRMKSEL_GPTIMER1_CH0            ECRCTL_ECRMKSEL(3)                    /*!< Extended closing request is masked by GPTIMER1_CH0 */
#define GTOC_ECRMKSEL_GPTIMER1_CH1            ECRCTL_ECRMKSEL(4)                    /*!< Extended closing request is masked by GPTIMER1_CH1 */

/* GTOC interrupt flags */
#define GTOC_INT_FLAG_INIF                        GTOC_CFG_INIF                     /*!< GTOCx_IN input interrupt flag */
#define GTOC_INT_FLAG_OFVEIF                      GTOC_CFG_OFVEIF                   /*!< GPTIMER output fault or CMP valid edge interrupt flag */

/* GTOC flags */
#define GTOC_FLAG_INIF                            GTOC_CFG_INIF                     /*!< GTOCx_IN input interrupt flag */
#define GTOC_FLAG_OFVEIF                          GTOC_CFG_OFVEIF                   /*!< GPTIMER output fault or CMP valid edge interrupt flag */
#define GTOC_FLAG_HXTALSDF                        GTOC_CFG_HXTALSDF                 /*!< HXTAL stuck detection flag */
#define GTOC_FLAG_LOCKUPDF                        GTOC_CFG_LOCKUPDF                 /*!< CPU LOCKUP detection flag */

/* GPTIMER external trigger input status */
#define GPTIMER_TRIGGER_STATUS_HIGH               ((uint32_t)0x00000001)            /*!< GPTIMER external trigger input high */
#define GPTIMER_TRIGGER_STATUS_LOW                ((uint32_t)0x00000000)            /*!< GPTIMER external trigger input low */

/* GTOCx_IN input detection mode */
#define GTOC_INPUT_DETECTION_LEVEL               ((uint32_t)0x00000000)             /*!< level detection */
#define GTOC_INPUT_DETECTION_EDGE                ((uint32_t)0x00000001)             /*!< edge detection */

/* function declarations */
/* deinitialize GTOC */
void gtoc_deinit(uint32_t gtoc_periph);
/* enable GTOC output closing request */
void gtoc_output_closing_request_enable(uint32_t gtoc_periph, uint16_t gtoc_ocr_source);
/* get GPTIMER external trigger input status */
uint32_t gtoc_gptimer_trigger_status_get(uint32_t gtoc_periph);
/* generate software output closing request */
void gtoc_software_request_generate(uint32_t gtoc_periph);
/* stop software output closing request */
void gtoc_software_request_stop(uint32_t gtoc_periph);
/* select GTOCx_IN input detection mode */
void gtoc_input_detection_mode_select(uint32_t gtoc_periph, uint32_t detection_mode);
/* configure GTOCx_IN input polarity */
void gtoc_input_polarity_config(uint32_t gtoc_periph, uint32_t input_polarity);
/* enable GTOC digital filter */
void gtoc_digital_filter_enable(uint32_t gtoc_periph);
/* disable GTOC digital filter */
void gtoc_digital_filter_disable(uint32_t gtoc_periph);
/* configure GTOC digital filter */
void gtoc_digital_filter_config(uint32_t gtoc_periph, uint32_t sampling_frequency, uint32_t sampling_number);
/* mask GTOC output closing request */
void gtoc_output_closing_request_mask(uint32_t gtoc_periph, uint32_t mask_source);
/* enable GTOC extended closing request control register write */
void gtoc_register_write_enable(uint32_t gtoc_periph);
/* disable GTOC extended closing request control register write */
void gtoc_register_write_disable(uint32_t gtoc_periph);
/* enable GTOC extended closing request */
void gtoc_extended_closing_request_enable(uint32_t gtoc_periph);
/* disable GTOC extended closing request */
void gtoc_extended_closing_request_disable(uint32_t gtoc_periph);
/* configure GTOC extended closing request */
void gtoc_extended_closing_request_config(uint32_t gtoc_periph, uint32_t gtoc_ecr_source, uint32_t valid_level);
/* mask GTOC extended closing request */
void gtoc_extended_closing_request_mask(uint32_t gtoc_periph, uint32_t mask_source);
/* get GTOC flag */
FlagStatus gtoc_flag_get(uint32_t gtoc_periph, uint32_t flag);
/* clear GTOC flag */
void gtoc_flag_clear(uint32_t gtoc_periph, uint32_t flag);
/* get GTOC interrupt flag */
FlagStatus gtoc_interrupt_flag_get(uint32_t gtoc_periph, uint32_t int_flag);
/* clear GTOC interrupt flag */
void gtoc_interrupt_flag_clear(uint32_t gtoc_periph, uint32_t int_flag);

#endif /* GD32M53X_GTOC_H */
