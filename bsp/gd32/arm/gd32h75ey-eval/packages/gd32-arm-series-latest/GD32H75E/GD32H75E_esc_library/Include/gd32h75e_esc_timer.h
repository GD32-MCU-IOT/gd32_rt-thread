/*!
    \file    gd32h75e_esc_timer.h
    \brief   ESC timer driver basic configuration

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

#ifndef  ESC_TIMER_H
#define  ESC_TIMER_H

#include "gd32h75e.h"

/* registers definitions */
#define  ESC_TIMER_REG                        ((uint32_t)0x00003800)
#define  ESC_TIMER_CTL0                       ((uint32_t)(ESC_TIMER_REG + 0x00000000))           /*!< ESC BASIC TIMER control register 0 */
#define  ESC_TIMER_CNT                        ((uint32_t)(ESC_TIMER_REG + 0x00000004))           /*!< ESC BASIC TIMER counter register */
#define  ESC_FRC_CNT                          ((uint32_t)(ESC_TIMER_REG + 0x00000008))           /*!< ESC FRC counter register */

/* enable a ESC BASIC TIMER */
void esc_timer_enable(void);
/* disable a ESC BASIC TIMER */
void esc_timer_disable(void);
/* configure ESC BASIC TIMER pre-load register value */
void esc_timer_preload_value_config(uint16_t preload);
/* read ESC BASIC TIMER counter value */
uint32_t esc_timer_counter_read(void);
/* read ESC FRC counter value */
uint32_t esc_frc_counter_read(void);

#endif /* GD32H75E_ESC_TIMER_H */