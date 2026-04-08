/*!
    \file    gd32m53x_wwdgt.h
    \brief   definitions for the WWDGT

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

#ifndef GD32M53X_WWDGT_H
#define GD32M53X_WWDGT_H

#include "gd32m53x.h"

/* WWDGT definitions */
#define WWDGT                        WWDGT_BASE                                             /*!< WWDGT base address */

/* registers definitions */
#define WWDGT_CTL                    REG32((WWDGT) + 0x00U)                                 /*!< WWDGT control register */
#define WWDGT_CFG                    REG32((WWDGT) + 0x04U)                                 /*!< WWDGT configuration register */
#define WWDGT_STAT                   REG32((WWDGT) + 0x08U)                                 /*!< WWDGT state register */

/* bits definitions */
/* WWDGT_CTL */
#define WWDGT_CTL_CNT                BITS(0,13)                                             /*!< WWDGT counter value */

/* WWDGT_CFG */
#define WWDGT_CFG_WEPS               BITS(30,31)                                            /*!< WWDGT counter window end position value */
#define WWDGT_CFG_WIN                BITS(16,29)                                            /*!< WWDGT counter window value */
#define WWDGT_CFG_EWIE               BIT(7)                                                 /*!< WWDGT early wakeup interrupt enable */
#define WWDGT_CFG_PSC                BITS(5,6)                                              /*!< WWDGT prescaler divider value */
#define WWDGT_CFG_WDGTEN             BIT(0)                                                 /*!< WWDGT counter enable */

/* WWDGT_STAT */
#define WWDGT_STAT_EWIF              BIT(0)                                                 /*!< WWDGT early wakeup interrupt flag */
#define WWDGT_STAT_REFEF             BIT(1)                                                 /*!< WWDGT underflow error flag */
#define WWDGT_STAT_UNDFF             BIT(2)                                                 /*!< WWDGT refresh error flag */

/* constants definitions */
#define CFG_PSC(regval)              (BITS(5,6) & ((uint32_t)(regval) << 5U))               /*!< write value to WWDGT_CFG_PSC bit field */
#define WWDGT_CFG_PSC_DIV1           ((uint32_t)CFG_PSC(0))                                 /*!< the time base of WWDGT = (PCLK1/4096)/1 */
#define WWDGT_CFG_PSC_DIV2           ((uint32_t)CFG_PSC(1))                                 /*!< the time base of WWDGT = (PCLK1/4096)/2 */
#define WWDGT_CFG_PSC_DIV4           ((uint32_t)CFG_PSC(2))                                 /*!< the time base of WWDGT = (PCLK1/4096)/4 */
#define WWDGT_CFG_PSC_DIV8           ((uint32_t)CFG_PSC(3))                                 /*!< the time base of WWDGT = (PCLK1/4096)/8 */

#define CFG_WEPS(regval)             (BITS(30,31) & ((uint32_t)(regval) << 30U))            /*!< write value to WWDGT_CFG_WEPS bit field */
#define WWDGT_CFG_WEPS_THREE_QUARTER ((uint32_t)CFG_WEPS(0))                                /*!< the window end position of WWDGT = (3/4)*0x3FFF */
#define WWDGT_CFG_WEPS_HALF          ((uint32_t)CFG_WEPS(1))                                /*!< the window end position of WWDGT = (1/2)*0x3FFF */
#define WWDGT_CFG_WEPS_QUARTER       ((uint32_t)CFG_WEPS(2))                                /*!< the window end position of WWDGT = (1/4)*0x3FFF */
#define WWDGT_CFG_WEPS_ZERO          ((uint32_t)CFG_WEPS(3))                                /*!< the window end position of WWDGT = 0*/

/* WWDGT configure structure */
typedef struct {
    uint16_t counter;                                                                       /*!< watchdog timer counter value */
    uint32_t reset_control;                                                                 /*!< WWDGT reset control bit */
    uint32_t ewie_control;                                                                  /*!< WWDGT early wakeup interrupt control bit */
    uint16_t window;                                                                        /*!< WWDGT window start value */
    uint32_t window_end_position;                                                            /*!< WWDGT window end position value */
    uint32_t prescaler;                                                                     /*!< WWDGT prescaler value */
} wwdgt_cfg_parameter_struct;

/* WWDGT_CTL register value */
#define CTL_CNT(regval)              (BITS(0,13) & ((uint32_t)(regval) << 0U))              /*!< write value to WWDGT_CTL_CNT bit field */
/* WWDGT_CFG register value */
#define CFG_WIN(regval)              (BITS(16,29) & ((uint32_t)(regval) << 16U))            /*!< write value to WWDGT_CFG_WIN bit field */

/* WWDGT reset generate*/
#define WWDGT_RESET_DISABLE          ((uint32_t)0x00000000U)                                /* wwdgt reset condition does not produce a reset */
#define WWDGT_RESET_ENABLE           WWDGT_CFG_WDGTEN                                       /* wwdgt reset condition produce a reset */

/* WWDGT interrupt generate*/
#define WWDGT_EWIE_DISABLE           ((uint32_t)0x00000000U)                                /* disable wwdgt early wakeup interrupt */
#define WWDGT_EWIE_ENABLE            WWDGT_CFG_EWIE                                         /* enable wwdgt early wakeup interrupt */

/* WWDGT flag definitions */
#define WWDGT_FLAG_EWIF              WWDGT_STAT_EWIF                                        /*!< early wakeup interrupt flag */
#define WWDGT_FLAG_REFEF             WWDGT_STAT_REFEF                                       /*!< refresh error flag */
#define WWDGT_FLAG_UNDFF             WWDGT_STAT_UNDFF                                       /*!< underflow error flag */

/* function declarations */
/* reset the WWDGT configuration */
void wwdgt_deinit(void);

/* configure the WWDGT counter value */
void wwdgt_counter_update(uint16_t counter_value);
/* initialize the parameters of WWDGT configure structure with the default values */
void wwdgt_struct_para_init(wwdgt_cfg_parameter_struct *cfg_struct);
/* initialize WWDGT configuration and start counter */
void wwdgt_cfg_init(wwdgt_cfg_parameter_struct *cfg_struct);
/* check flag state of WWDGT */
FlagStatus wwdgt_flag_get(uint32_t flag);
/* clear flag state of WWDGT */
void wwdgt_flag_clear(uint32_t flag);

#endif /* GD32M53X_WWDGT_H */
