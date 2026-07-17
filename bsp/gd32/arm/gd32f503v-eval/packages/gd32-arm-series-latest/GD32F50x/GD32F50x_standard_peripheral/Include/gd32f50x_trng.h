/*!
    \file    gd32f50x_trng.h
    \brief   definitions for the TRNG

    \version 2026-02-25, V1.0.4, firmware for GD32F50x
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

#ifndef GD32F50X_TRNG_H
#define GD32F50X_TRNG_H

#include "gd32f50x.h"

/* TRNG definitions */
#define TRNG                        TRNG_BASE                        /*!< TRNG base address */

/* registers definitions */
#define TRNG_CTL                    REG32(TRNG + 0x00000000U)        /*!< control register */
#define TRNG_STAT                   REG32(TRNG + 0x00000004U)        /*!< status register */
#define TRNG_DATA                   REG32(TRNG + 0x00000008U)        /*!< data register */

/* bits definitions */
/* TRNG_CTL */
#define TRNG_CTL_TRNGEN             BIT(2)                           /*!< TRNG enable bit */
#define TRNG_CTL_TRNGIE             BIT(3)                           /*!< interrupt enable bit */
#define TRNG_CTL_NR                 BITS(24,25)                      /*!< TRNG analog power mode bits */

/* TRNG_STAT */
#define TRNG_STAT_DRDY              BIT(0)                           /*!< random data ready status bit */
#define TRNG_STAT_CECS              BIT(1)                           /*!< clock error current status */
#define TRNG_STAT_SECS              BIT(2)                           /*!< seed error current status */
#define TRNG_STAT_CEIF              BIT(5)                           /*!< clock error interrupt flag */
#define TRNG_STAT_SEIF              BIT(6)                           /*!< seed error interrupt flag */

/* TRNG_DATA */
#define TRNG_DATA_TRNDATA           BITS(0,31)                       /*!< 32-bit random data */

/* TRNG power mode */
#define CTL_NR(regval)              (BITS(24,25) & ((uint32_t)(regval) << 24U))
#define TRNG_NR_ULTRALOW            CTL_NR(0)                        /*!< TRNG analog power mode ultralow */
#define TRNG_NR_LOW                 CTL_NR(1)                        /*!< TRNG analog power mode low */
#define TRNG_NR_MEDIUM              CTL_NR(2)                        /*!< TRNG analog power mode medium */
#define TRNG_NR_HIGH                CTL_NR(3)                        /*!< TRNG analog power mode high */

/* constants definitions */
/* TRNG status flag */
typedef enum
{ 
    TRNG_FLAG_DRDY = TRNG_STAT_DRDY,                                 /*!< random data ready status */
    TRNG_FLAG_CECS = TRNG_STAT_CECS,                                 /*!< clock error current status */
    TRNG_FLAG_SECS = TRNG_STAT_SECS                                  /*!< seed error current status */
}trng_flag_enum;

/* TRNG interrupt flag */
typedef enum
{
    TRNG_INT_FLAG_CEIF = TRNG_STAT_CEIF,                             /*!< clock error interrupt flag */
    TRNG_INT_FLAG_SEIF = TRNG_STAT_SEIF                              /*!< seed error interrupt flag */
}trng_int_flag_enum;

/* function declarations */
/* initialization functions */
/* deinitialize the TRNG */
void trng_deinit(void);
/* enable the TRNG interface */
void trng_enable(void);
/* disable the TRNG interface */
void trng_disable(void);
/* get the true random data */
uint32_t trng_get_true_random_data(void);
/* configure TRNG analog power mode */
void trng_powermode_config(uint32_t powermode);

/* flag & interrupt functions */
/* get the TRNG status flags */
FlagStatus trng_flag_get(trng_flag_enum flag);
/* enable the TRNG interrupt */
void trng_interrupt_enable(void);
/* disable the TRNG interrupt */
void trng_interrupt_disable(void);
/* get the TRNG interrupt flags */
FlagStatus trng_interrupt_flag_get(trng_int_flag_enum int_flag);
/* clear the TRNG interrupt flags */
void trng_interrupt_flag_clear(trng_int_flag_enum int_flag);

#endif /* GD32F50X_TRNG_H */
