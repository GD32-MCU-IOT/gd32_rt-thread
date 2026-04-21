/*!
    \file    gd32m53x_dbg.h
    \brief   DBG driver

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

#ifndef GD32M53X_DBG_H
#define GD32M53X_DBG_H

#include "gd32m53x.h"

/* DBG definitions */
#define DBG                     DBG_BASE                                             /*!< DBG base address */

/* registers definitions */
#define DBG_ID                  REG32(DBG + 0x00000000U)                             /*!< DBG_ID code register */
#define DBG_CTL                 REG32(DBG + 0x00000004U)                             /*!< DBG control register */

/* bits definitions */
/* DBG_ID */
#define DBG_ID_ID_CODE           BITS(0,31)                                          /*!< DBG ID code */

/* DBG_CTL */
#define DBG_CTL_SLP_HOLD         BIT(0)                                              /*!< keep debugger connection during sleep mode */
#define DBG_CTL_DSLP_HOLD        BIT(1)                                              /*!< keep debugger connection during deepsleep mode */
#define DBG_CTL_STB_HOLD         BIT(2)                                              /*!< keep debugger connection during standby mode */
#define DBG_CTL_TRACE_IOEN       BIT(5)                                              /*!< enable trace pin assignment */
#define DBG_CTL_FWDGT_HOLD       BIT(8)                                              /*!< hold FWDGT counter when core is halted */
#define DBG_CTL_WWDGT_HOLD       BIT(9)                                              /*!< hold WWDGT counter when core is halted */
#define DBG_CTL_TIMER0_HOLD      BIT(10)                                             /*!< hold TIMER0 counter when core is halted */
#define DBG_CTL_TIMER1_HOLD      BIT(11)                                             /*!< hold TIMER1 counter when core is halted */
#define DBG_CTL_TIMER2_HOLD      BIT(12)                                             /*!< hold TIMER2 counter when core is halted */
#define DBG_CTL_GPTIMER0_HOLD    BIT(13)                                             /*!< hold GPTIMER0 counter when core is halted */
#define DBG_CTL_I2C_HOLD         BIT(15)                                             /*!< hold I2C smbus timeout when core is halted */
#define DBG_CTL_GPTIMER1_HOLD    BIT(17)                                             /*!< hold GPTIMER1 counter when core is halted */
#define DBG_CTL_CPTIMER0_HOLD    BIT(18)                                             /*!< hold CPTIMER0 counter when core is halted */
#define DBG_CTL_CPTIMER1_HOLD    BIT(19)                                             /*!< hold CPTIMER1 counter when core is halted */
#define DBG_CTL_TIMER7_HOLD      BIT(20)                                             /*!< hold TIMER7 counter when core is halted */
#define DBG_CTL_CAN_HOLD         BIT(25)                                             /*!< hold CAN receive register counter when core is halted */
#define DBG_CTL_CPTIMERW_HOLD    BIT(30)                                             /*!< hold CPTIMERW counter when core is halted */

/* constants definitions */
#define DBG_LOW_POWER_SLEEP      DBG_CTL_SLP_HOLD                                    /*!< keep debugger connection during sleep mode */
#define DBG_LOW_POWER_DEEPSLEEP  DBG_CTL_DSLP_HOLD                                   /*!< keep debugger connection during deepsleep mode */
#define DBG_LOW_POWER_STANDBY    DBG_CTL_STB_HOLD                                    /*!< keep debugger connection during standby mode */

/* define the peripheral debug hold bit position and its register index offset */
#define DBG_REGIDX_BIT(regidx, bitpos)      (((regidx) << 6U) | (bitpos))
#define DBG_REG_VAL(periph)                 (REG32(DBG + ((uint32_t)(periph) >> 6U)))
#define DBG_BIT_POS(val)                    ((uint32_t)(val) & 0x1FU)

/* register index */
#define DBG_IDX_CTL              ((uint32_t)0x00000004U)

typedef enum {
    DBG_FWDGT_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL, 8U),                    /*!< hold FWDGT counter when core is halted */
    DBG_WWDGT_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL, 9U),                    /*!< hold WWDGT counter when core is halted */
    DBG_TIMER0_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL, 10U),                   /*!< hold TIMER0 counter when core is halted */
    DBG_TIMER1_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL, 11U),                   /*!< hold TIMER1 counter when core is halted */
    DBG_TIMER2_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL, 12U),                   /*!< hold TIMER2 counter when core is halted */
    DBG_GPTIMER0_HOLD          = DBG_REGIDX_BIT(DBG_IDX_CTL, 13U),                   /*!< hold GPTIMER0 counter when core is halted */
    DBG_I2C_HOLD               = DBG_REGIDX_BIT(DBG_IDX_CTL, 15U),                   /*!< hold I2C smbus timeout when core is halted */
    DBG_GPTIMER1_HOLD          = DBG_REGIDX_BIT(DBG_IDX_CTL, 17U),                   /*!< hold GPTIMER1 counter when core is halted */
    DBG_CPTIMER0_HOLD          = DBG_REGIDX_BIT(DBG_IDX_CTL, 18U),                   /*!< hold CPTIMER0 counter when core is halted */
    DBG_CPTIMER1_HOLD          = DBG_REGIDX_BIT(DBG_IDX_CTL, 19U),                   /*!< hold CPTIMER1 counter when core is halted */
    DBG_TIMER7_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL, 20U),                   /*!< hold TIMER7 counter when core is halted */
    DBG_CAN_HOLD               = DBG_REGIDX_BIT(DBG_IDX_CTL, 25U),                   /*!< hold CAN receive register counter when core is halted */
    DBG_CPTIMERW_HOLD          = DBG_REGIDX_BIT(DBG_IDX_CTL, 30U),                   /*!< hold CPTIMERW counter when core is halted */
} dbg_periph_enum;

/* function declarations */
/* deinitialize the DBG */
void dbg_deinit(void);
/* read DBG_ID code register */
uint32_t dbg_id_get(void);

/* enable low power behavior when the MCU is in debug mode */
void dbg_low_power_enable(uint32_t dbg_low_power);
/* disable low power behavior when the MCU is in debug mode */
void dbg_low_power_disable(uint32_t dbg_low_power);

/* enable peripheral behavior when the MCU is in debug mode */
void dbg_periph_enable(dbg_periph_enum dbg_periph);
/* disable peripheral behavior when the MCU is in debug mode */
void dbg_periph_disable(dbg_periph_enum dbg_periph);

/* enable trace pin assignment */
void dbg_trace_pin_enable(void);
/* disable trace pin assignment */
void dbg_trace_pin_disable(void);

#endif /* GD32M53X_DBG_H */
