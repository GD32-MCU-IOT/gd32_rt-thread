/*!
    \file    gd32l23x_vref.h
    \brief   definitions for the VREF

    \version 2025-08-08, V2.3.0, firmware for GD32L23x, add support for GD32L235
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

#ifndef GD32L23X_VREF_H
#define GD32L23X_VREF_H

#include "gd32l23x.h"

/* VREF definitions */
#define VREF                         VREF_BASE                      /*!< VREF base address */

/* registers definitions */
#define VREF_CS                      REG32(VREF + 0x00000000U)      /*!< VREF Control and status register */
#define VREF_CALIB                   REG32(VREF + 0x00000004U)      /*!< VREF Calibration register */

/* bits definitions */
/* VREF_CS */
#define VREF_CS_VREFEN               BIT(0)                         /*!< VREF enable */
#define VREF_CS_HIPM                 BIT(1)                         /*!< High impedance mode */
#ifdef GD32L235
#define VREF_CS_VREFS                BIT(2)                         /*!< VREF voltage reference select */
#endif /* GD32L235 */
#define VREF_CS_VREFRDY              BIT(3)                         /*!< VREF ready */

/* constants definitions */
/* VREF_CALIB */
#define VREF_CALIB_VREFCAL           BITS(0,5)                      /*!< VREF calibration */

/* VREF_CS reset value definition */                                /*!< VREF_CS reset value */
#define VREF_RESET                   ((uint32_t)0x00000002U)

/* VREF bit devinitions */
#define VREF_EN                      VREF_CS_VREFEN                 /*!< VREF enable */
#define VREF_HIGH_IMPEDANCE_MODE     VREF_CS_HIPM                   /*!< High impedance mode */
#define VREF_RDY                     VREF_CS_VREFRDY                /*!< VREF ready */

#ifdef GD32L235
/* VREF voltage reference select */
#define VREF_VOLTAGE_SEL_LEVEL_0     ((uint32_t)0x00000000U)        /*!< VREF voltage reference select 2.048 V */
#define VREF_VOLTAGE_SEL_LEVEL_1     VREF_CS_VREFS                  /*!< VREF voltage reference select 2.5 V */
#endif /* GD32L235 */

/* function declarations */
/* deinitialize the VREF */
void vref_deinit(void);
/* enable VREF */
void vref_enable(void);
/* disable VREF */
void vref_disable(void);
/* enable VREF high impendance mode */
void vref_high_impedance_mode_enable(void);
/* disable VREF high impendance mode */
void vref_high_impedance_mode_disable(void);
#ifdef GD32L235
/* select VREF voltage reference */
void vref_voltage_select(uint32_t vref_voltage);
#endif /* GD32L235 */
/* get the status of VREF */
FlagStatus vref_status_get(void);
/* set the calibration value of VREF */
void vref_calib_value_set(uint8_t value);
/* get the calibration value of VREF */
uint8_t vref_calib_value_get(void);

#endif /* GD32L23X_VREF_H */
