/*!
    \file    gd32g5x3_cpdm.h
    \brief   definitions for the CPDM

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

#ifndef GD32G5X3_CPDM_H
#define GD32G5X3_CPDM_H

#include "gd32g5x3.h"

/* CPDM definitions */
#define CPDM                       CPDM_BASE

/* registers definitions */
#define CPDM_CTL                   REG32(CPDM + 0x00000000U)      /*!< CPDM control register */
#define CPDM_CFG                   REG32(CPDM + 0x00000004U)      /*!< CPDM configuration register */

/* bits definitions */
/* CPDM_CTL */
#define CPDM_CTL_CPDMEN            BIT(0)                         /*!< CPDM enable */
#define CPDM_CTL_DLSEN             BIT(1)                         /*!< CPDM delay line sample module enable */

/* CPDM_CFG */
#define CPDM_CFG_CPSEL             BITS(0,3)                      /*!< select the phase of the output clock */
#define CPDM_CFG_DLSTCNT           BITS(8,14)                     /*!< define a delay step count for a unit delay UNIT */
#define CPDM_CFG_DLLEN             BITS(16,27)                    /*!< delay line length */
#define CPDM_CFG_DLLENF            BIT(31)                        /*!< valid mark of delay line length */

/* constants definitions */
/* output clock phase selection enum definition */
typedef enum {
    CPDM_OUTPUT_PHASE_SELECTION_0 = 0U,                            /*!< output clock phase = input clock */
    CPDM_OUTPUT_PHASE_SELECTION_1,                                 /*!< output clock phase = input clock + 1 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_2,                                 /*!< output clock phase = input clock + 2 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_3,                                 /*!< output clock phase = input clock + 3 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_4,                                 /*!< output clock phase = input clock + 4 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_5,                                 /*!< output clock phase = input clock + 5 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_6,                                 /*!< output clock phase = input clock + 6 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_7,                                 /*!< output clock phase = input clock + 7 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_8,                                 /*!< output clock phase = input clock + 8 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_9,                                 /*!< output clock phase = input clock + 9 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_10,                                /*!< output clock phase = input clock + 10 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_11,                                /*!< output clock phase = input clock + 11 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_12,                                /*!< output clock phase = input clock + 12 * UNIT delay */
} cpdm_output_phase_enum;

#define CPDM_MAX_DELAY_STEP_COUNT  ((uint32_t)0x0000007FU)        /*!< max UNIT value  */
#define CPDM_MAX_PHASE             ((uint32_t)0x0000000CU)        /*!< max select value of the phase */

/* function declarations */
/* deinitialization and initialization functions */
/* enable CPDM */
void cpdm_enable(void);
/* disable CPDM */
void cpdm_disable(void);
/* enable CPDM delay line sample module */
void cpdm_delayline_sample_enable(void);
/* disable CPDM delay line sample module */
void cpdm_delayline_sample_disable(void);

/* output clock configuration functions */
/* select CPDM output clock phase */
void cpdm_output_clock_phase_select(cpdm_output_phase_enum output_clock_phase);
/* configure CPDM delay step */
void cpdm_delay_step_config(uint8_t delay_step);
/* get delay line length valid flag */
FlagStatus cpdm_delayline_length_valid_flag_get(void);
/* get delay line length */
uint16_t cpdm_delayline_length_get(void);

/* clock output function */
/* configure CPDM clock output */
ErrStatus cpdm_clock_output(cpdm_output_phase_enum output_clock_phase);

#endif /* GD32G5X3_CPDM_H */
