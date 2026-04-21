/*!
    \file    gd32m53x_svpwm.h
    \brief   definitions for the SVPWM

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

#ifndef GD32M53X_SVPWM_H
#define GD32M53X_SVPWM_H

#include "gd32m53x.h"

/* SVPWM definitions */
#define SVPWM                       SVPWM_BASE

#define REG32_FLOAT(addr)           (*(volatile float *)(uint32_t)(addr))

/* registers definitions */
#define SVPWM_CTL0                  REG32(SVPWM + 0x00000000U)                /*!< SVPWM control register 0 */
#define SVPWM_UALPHA                REG32_FLOAT(SVPWM + 0x00000004U)          /*!< SVPWM voltage alpha register */
#define SVPWM_UBETA                 REG32_FLOAT(SVPWM + 0x00000008U)          /*!< SVPWM voltage beta register */
#define SVPWM_CAR                   REG32(SVPWM + 0x0000000CU)                /*!< SVPWM counter reload register */
#define SVPWM_TA                    REG32(SVPWM + 0x00000010U)                /*!< SVPWM ta register */
#define SVPWM_TB                    REG32(SVPWM + 0x00000014U)                /*!< SVPWM tb register */
#define SVPWM_TC                    REG32(SVPWM + 0x00000018U)                /*!< SVPWM tc register */
#define SVPWM_SEC                   REG32(SVPWM + 0x0000001CU)                /*!< SVPWM sector register */
#define SVPWM_STAT                  REG32(SVPWM + 0x00000020U)                /*!< SVPWM status register */

/* bits definitions */
/* SVPWM_CTL0 */
#define SVPWM_CTL0_SM               BIT(8)                                    /*!< switch mode selection */
#define SVPWM_CTL0_TYPE             BIT(9)                                    /*!< segment type selection */
#define SVPWM_CTL0_CEN              BIT(11)                                   /*!< algorithm operation enable */

/* SVPWM_UALPHA */
#define SVPWM_UALPHA_UALPHA         BITS(0,31)                                /*!< alpha voltage in SVPWM system */

/* SVPWM_UBETA */
#define SVPWM_UBETA_UBETA           BITS(0,31)                                /*!< beta voltage in SVPWM system */

/* SVPWM_CAR */
#define SVPWM_CAR_CAR               BITS(0,15)                                /*!< the SVPWM period count */

/* SVPWM_TA */
#define SVPWM__TA_TA                BITS(0,15)                                /*!< the A-phase duty cycle calculated by SVPWM */

/* SVPWM_TB */
#define SVPWM_TB_TB                 BITS(0,15)                                /*!< the B-phase duty cycle calculated by SVPWM */

/* SVPWM_TC */
#define SVPWM_TC_TC                 BITS(0,15)                                /*!< the C-phase duty cycle calculated by SVPWM */

/* SVPWM_SEC */
#define SVPWM_SEC_SEC               BITS(0,2)                                 /*!< SVPWM sector value */

/* SVPWM_STAT */
#define SVPWM_STAT_OAL              BIT(0)                                    /*!< the duty cycle of A-phase is less than 0 overflow flag */
#define SVPWM_STAT_OBL              BIT(1)                                    /*!< the duty cycle of B-phase is less than 0 overflow flag */
#define SVPWM_STAT_OCL              BIT(2)                                    /*!< the duty cycle of C-phase is less than 0 overflow flag */
#define SVPWM_STAT_OSF              BIT(6)                                    /*!< the svpwm operation is executed successfully flag*/
#define SVPWM_STAT_OAH              BIT(16)                                   /*!< the duty cycle of A-phase is greater than the COUNT overflow flag */
#define SVPWM_STAT_OBH              BIT(17)                                   /*!< the duty cycle of B-phase is greater than the COUNT overflow flag */
#define SVPWM_STAT_OCH              BIT(18)                                   /*!< the duty cycle of C-phase is greater than the COUNT overflow flag */

/* constants definitions */
/* SVPWM init parameter struct definitions */
typedef struct {
    uint32_t switch_mode;                                                     /*!< switch mode of SVPWM operation */
    uint32_t working_mode;                                                    /*!< working mode of SVPWM operation */
    uint16_t period_count;                                                    /*!< period count of SVPWM operation */
} svpwm_parameter_struct;

/* SVPWM result_mode definitions */
#define SVPWM_SWITCH_MODE0          ((uint32_t)0x00000000U)                   /*!< switch mode0 output result */
#define SVPWM_SWITCH_MODE1          SVPWM_CTL0_SM                             /*!< switch mode1 output result */

/* SVPWM mode definitions */
#define SVPWM_MODE_SEVEN_SEGMENT    ((uint32_t)0x00000000U)                   /*!< seven-stage SVPWM mode */
#define SVPWM_MODE_FIVE_SEGMENT     SVPWM_CTL0_TYPE                           /*!< five-stage SVPWM mode */

/* SVPWM flag definitions */
#define SVPWM_FLAG_OAL              SVPWM_STAT_OAL                            /*!< the duty cycle of A-phase is less than 0 overflow flag */
#define SVPWM_FLAG_OBL              SVPWM_STAT_OBL                            /*!< the duty cycle of B-phase is less than 0 overflow flag */
#define SVPWM_FLAG_OCL              SVPWM_STAT_OCL                            /*!< the duty cycle of C-phase is less than 0 overflow flag */
#define SVPWM_FLAG_OAH              SVPWM_STAT_OAH                            /*!< the duty cycle of A-phase is more than COUNT overflow flag */
#define SVPWM_FLAG_OBH              SVPWM_STAT_OBH                            /*!< the duty cycle of B-phase is more than COUNT overflow flag */
#define SVPWM_FLAG_OCH              SVPWM_STAT_OCH                            /*!< the duty cycle of C-phase is more than COUNT overflow flag */
#define SVPWM_FLAG_OSF              SVPWM_STAT_OSF                            /*!< the svpwm operation is executed successfully flag*/

/* function declarations */
/* initialization functions */
/* reset the SVPWM registers */
void svpwm_deinit(void);
/* initialize the parameters of SVPWM struct with the default values */
void svpwm_struct_para_init(svpwm_parameter_struct *init_struct);
/* initialize SVPWM */
void svpwm_init(svpwm_parameter_struct *init_struct);
/* enable the SVPWM */
void svpwm_enable(void);

/* flag functions */
/* check the SVPWM status flag */
FlagStatus svpwm_flag_get(uint32_t flag);

/* SVPWM data write and read */
/* write alpha and beta data in float format */
void svpwm_alpha_beta_write(float alpha, float beta);
/* read ta, tb, tc data in uint16 format */
void svpwm_ta_tb_tc_read(uint16_t *ta, uint16_t *tb, uint16_t *tc);
/* read sector data */
uint8_t svpwm_sector_read(void);

#endif /* GD32M53X_SVPWM_H */
