/*!
    \file    gd32m53x_cptimer.h
    \brief   definitions for the TIMER

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

#ifndef GD32M53X_CPTIMER_H
#define GD32M53X_CPTIMER_H

#include "gd32m53x.h"

/* CPTIMERx(x=0,1) definitions */
#define CPTIMER0                                              (CPTIMER_BASE + 0x00000000U)
#define CPTIMER1                                              (CPTIMER_BASE + 0x00000400U)


/* registers definitions */
#define CPTIMER_CTL0(cptimerx)                                REG32((cptimerx) + 0x00U)         /*!< CPTIMER control register 0 */
#define CPTIMER_CNT0(cptimerx)                                REG32((cptimerx) + 0x04U)         /*!< CPTIMER counter 0 register */
#define CPTIMER_CNT1(cptimerx)                                REG32((cptimerx) + 0x08U)         /*!< CPTIMER counter 1 register */
#define CPTIMER_CNT0PSC(cptimerx)                             REG32((cptimerx) + 0x0CU)         /*!< CPTIMER counter 0 prescaler register */
#define CPTIMER_CNT1PSC(cptimerx)                             REG32((cptimerx) + 0x10U)         /*!< CPTIMER counter 1 prescaler register */
#define CPTIMER_INTEN(cptimerx)                               REG32((cptimerx) + 0x14U)         /*!< CPTIMER interrupt enable register */
#define CPTIMER_INTF(cptimerx)                                REG32((cptimerx) + 0x18U)         /*!< CPTIMER interrupt flag register */
#define CPTIMER_SWEVG(cptimerx)                               REG32((cptimerx) + 0x1CU)         /*!< CPTIMER software event generation register */
#define CPTIMER_CNT0CAR(cptimerx)                             REG32((cptimerx) + 0x20U)         /*!< CPTIMER counter 0 autoreload value register */
#define CPTIMER_CNT1CAR(cptimerx)                             REG32((cptimerx) + 0x24U)         /*!< CPTIMER counter 1 autoreload value register */


/* CPTIMER_CTL0 */
#define CPTIMER_CTL0_CEN0                                     BIT(0)                            /*!< CPTIMER counter 0 enable */
#define CPTIMER_CTL0_CEN1                                     BIT(16)                           /*!< CPTIMER counter 1 enable */

/* CPTIMER_INTEN */
#define CPTIMER_INTEN_CNT0UPIE                                BIT(0)                            /*!< CPTIMER counter 0 update interrupt enable */
#define CPTIMER_INTEN_CNT1UPIE                                BIT(16)                           /*!< CPTIMER counter 1 update interrupt enable */

/* CPTIMER_INTF */
#define CPTIMER_INTF_CNT0UPIF                                 BIT(0)                            /*!< CPTIMER counter 0 update interrupt flag */
#define CPTIMER_INTF_CNT1UPIF                                 BIT(16)                           /*!< CPTIMER counter 1 update interrupt flag */

/* CPTIMER_SWEVG */
#define CPTIMER_SWEVG_CNT0UPG                                 BIT(0)                            /*!< CPTIMER counter 0 software update event generate */
#define CPTIMER_SWEVG_CNT1UPG                                 BIT(16)                           /*!< CPTIMER counter 1 software update event generate */

/* constants definitions */
/* specify CPTIMER counter */
#define CPTIMER_COUNTER0                                      ((uint16_t)0x0000U)               /*!< CPTIMER counter 0 */
#define CPTIMER_COUNTER1                                      ((uint16_t)0x0001U)               /*!< CPTIMER counter 1 */

/* CPTIMER flag */
#define CPTIMER_FLAG_CNT0UP                                   CPTIMER_INTF_CNT0UPIF             /*!< CPTIMER counter 0 update flag */
#define CPTIMER_FLAG_CNT1UP                                   CPTIMER_INTF_CNT1UPIF             /*!< CPTIMER counter 1 update flag */

/* CPTIMER interrupt enable or disable */
#define CPTIMER_INT_CNT0UP                                    CPTIMER_INTEN_CNT0UPIE            /*!< CPTIMER counter 0 update interrupt */
#define CPTIMER_INT_CNT1UP                                    CPTIMER_INTEN_CNT1UPIE            /*!< CPTIMER counter 1 update interrupt */

/* CPTIMER interrupt flag */
#define CPTIMER_INT_FLAG_CNT0UP                               CPTIMER_INTF_CNT0UPIF             /*!< CPTIMER counter 0 update interrupt flag */
#define CPTIMER_INT_FLAG_CNT1UP                               CPTIMER_INTF_CNT1UPIF             /*!< CPTIMER counter 1 update interrupt flag */

/* CPTIMER software event generation source */
#define CPTIMER_EVENT_SRC_UPG0                                CPTIMER_SWEVG_CNT0UPG             /*!< CPTIMER counter 0 update event generation */
#define CPTIMER_EVENT_SRC_UPG1                                CPTIMER_SWEVG_CNT1UPG             /*!< CPTIMER counter 1 update event generation */


/* function declarations */
/* CPTIMER BASE*/
/* deinit a TIMER*/
void cptimer_deinit(uint32_t cptimer_periph);
/* enable a CPTIMER */
void cptimer_enable(uint32_t cptimer_periph, uint32_t counter);
/* disable a CPTIMER */
void cptimer_disable(uint32_t cptimer_periph, uint32_t counter);
/* configure CPTIMER prescaler */
void cptimer_prescaler_config(uint32_t cptimer_periph, uint32_t counter, uint16_t prescaler);
/* configure CPTIMER autoreload value */
void cptimer_autoreload_value_config(uint32_t cptimer_periph, uint32_t counter, uint16_t autoreload);
/* configure CPTIMER counter value */
void cptimer_counter_value_config(uint32_t cptimer_periph, uint32_t counter, uint16_t value);
/* read CPTIMER counter value */
uint16_t cptimer_counter_read(uint32_t cptimer_periph, uint32_t counter);
/* read CPTIMER prescaler value */
uint16_t cptimer_prescaler_read(uint32_t cptimer_periph, uint32_t counter);
/* software generate events */
void cptimer_event_software_generate(uint32_t cptimer_periph, uint32_t event);

/* TIMER interrupt and flag*/
/* get CPTIMER flags */
FlagStatus cptimer_flag_get(uint32_t cptimer_periph, uint32_t flag);
/* clear CPTIMER flags */
void cptimer_flag_clear(uint32_t cptimer_periph, uint32_t flag);
/* enable CPTIMER interrupt */
void cptimer_interrupt_enable(uint32_t cptimer_periph, uint32_t interrupt);
/* disable CPTIMER interrupt */
void cptimer_interrupt_disable(uint32_t cptimer_periph, uint32_t interrupt);
/* get CPTIMER interrupt flag */
FlagStatus cptimer_interrupt_flag_get(uint32_t cptimer_periph, uint32_t int_flag);
/* clear CPTIMER interrupt flag */
void cptimer_interrupt_flag_clear(uint32_t cptimer_periph, uint32_t int_flag);
#endif /* GD32M53X_CPTIMER_H */
