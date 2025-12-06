/*!
    \file    gd32h75e_report_err.h
    \brief   Reporting Error driver

    \version 2025-01-24, V1.1.0, firmware for GD32H75E
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
#ifndef ERR_REPORT_H
#define ERR_REPORT_H

#include <stdint.h>

/* define the size of the error report buffer */
#define ERR_REPORT_BUFFER_SIZE          60U

/* define the unique identifier of peripherals */
#define SYSCFG_MODULE_ID                                  ((uint8_t)0x01U)               /*!< SYSCFG module ID */
#define RAMECCMU_MODULE_ID                                ((uint8_t)0x02U)               /*!< RAMECCMU module ID */
#define FMC_MODULE_ID                                     ((uint8_t)0x03U)               /*!< FMC module ID */
#define EFUSE_MODULE_ID                                   ((uint8_t)0x04U)               /*!< EFUSE module ID */
#define PMU_MODULE_ID                                     ((uint8_t)0x05U)               /*!< PMU module ID */
#define RCU_MODULE_ID                                     ((uint8_t)0x06U)               /*!< RCU module ID */
#define CTC_MODULE_ID                                     ((uint8_t)0x07U)               /*!< CTC module ID */
#define EXTI_MODULE_ID                                    ((uint8_t)0x08U)               /*!< EXTI module ID */
#define TRIGSEL_MODULE_ID                                 ((uint8_t)0x09U)               /*!< TRIGSEL module ID */
#define GPIO_MODULE_ID                                    ((uint8_t)0x0AU)               /*!< GPIO module ID */
#define CRC_MODULE_ID                                     ((uint8_t)0x0BU)               /*!< CRC module ID */
#define TRNG_MODULE_ID                                    ((uint8_t)0x0CU)               /*!< TRNG module ID */
#define TMU_MODULE_ID                                     ((uint8_t)0x0DU)               /*!< TMU module ID */
#define DMA_DMAMUX_MODULE_ID                              ((uint8_t)0x0EU)               /*!< DMA and DMAMUX module ID */
#define MDMA_MODULE_ID                                    ((uint8_t)0x0FU)               /*!< MDMA module ID */
#define DBG_MODULE_ID                                     ((uint8_t)0x10U)               /*!< DBG module ID */
#define ADC_MODULE_ID                                     ((uint8_t)0x11U)               /*!< ADC module ID */
#define DAC_MODULE_ID                                     ((uint8_t)0x12U)               /*!< DAC module ID */
#define FWDGT_MODULE_ID                                   ((uint8_t)0x13U)               /*!< FWDGT module ID */
#define WWDGT_MODULE_ID                                   ((uint8_t)0x14U)               /*!< WWDGT module ID */
#define RTC_MODULE_ID                                     ((uint8_t)0x15U)               /*!< RTC module ID */
#define TIMER_MODULE_ID                                   ((uint8_t)0x16U)               /*!< TIMER module ID */
#define USART_MODULE_ID                                   ((uint8_t)0x17U)               /*!< USART module ID */
#define I2C_MODULE_ID                                     ((uint8_t)0x18U)               /*!< I2C module ID */
#define SPI_MODULE_ID                                     ((uint8_t)0x19U)               /*!< SPI module ID */
#define OSPIM_MODULE_ID                                   ((uint8_t)0x1AU)               /*!< OSPIM module ID */
#define OSPI_MODULE_ID                                    ((uint8_t)0x1BU)               /*!< OSPI module ID */
#define EXMC_MODULE_ID                                    ((uint8_t)0x1CU)               /*!< EXMC module ID */
#define VREF_MODULE_ID                                    ((uint8_t)0x1DU)               /*!< VREF module ID */
#define LPDTS_MODULE_ID                                   ((uint8_t)0x1EU)               /*!< LPDTS module ID */
#define EDOUT_MODULE_ID                                   ((uint8_t)0x1FU)               /*!< EDOUT module ID */
#define CAN_MODULE_ID                                     ((uint8_t)0x20U)               /*!< CAN module ID */
#define CMP_MODULE_ID                                     ((uint8_t)0x21U)               /*!< CMP module ID */
#define HPDF_MODULE_ID                                    ((uint8_t)0x22U)               /*!< HPDF module ID */
#define FAC_MODULE_ID                                     ((uint8_t)0x23U)               /*!< FAC module ID */
#define MISC_MODULE_ID                                    ((uint8_t)0x24U)               /*!< MISC module ID */
#define USBHS_MODULE_ID                                   ((uint8_t)0x25U)               /*!< USBHS module ID */
#define ESC_MODULE_ID                                     ((uint8_t)0x26U)               /*!< ESC module ID */

/* define the unique identifier of error type */
#define ERR_PERIPH                                        ((uint8_t)0x01U)               /*!< peripheral error */
#define ERR_PARAM_POINTER                                 ((uint8_t)0x02U)               /*!< invalid pointer */
#define ERR_PARAM_OUT_OF_RANGE                            ((uint8_t)0x03U)               /*!< out of range */
#define ERR_PARAM_INVALID                                 ((uint8_t)0x04U)               /*!< invalid parameter */

/* define the unique identifier of API */
#define API_ID(x)                                         ((uint16_t)(x))               /*!< API ID */

/* definitions for parameter checking */
#define NOT_VALID_POINTER(x)                              ((void *) 0 == (x))           /*!< check the invalid pointer */

/* defining the structure to store the parameters of Report Error function */
typedef struct {
    /* module ID where the error occurred */
    uint16_t moduleid;
    /* API ID associated with the error */
    uint16_t apiid;
    /* error ID indicating the specific error type */
    uint8_t errid;
} err_report_struct;

/* declare external arrays and variables for error reporting */
extern err_report_struct err_report_buffer[ERR_REPORT_BUFFER_SIZE];
/* index to track the next available position in the error report buffer */
extern uint8_t err_report_buff_index;
/* reporting errors in debug mode */
void fw_debug_report_err(uint16_t moduleid, uint16_t apiid, uint8_t errid);

#endif /* ERR_REPORT_H */
