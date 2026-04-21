/*!
    \file    gd32m53x_cfmu.c
    \brief   CFMU driver

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

#ifndef GD32M53X_CFMU_H
#define GD32M53X_CFMU_H

#include "gd32m53x.h"

/* CFMU definitions */
#define CFMU                             CFMU_BASE                        /*!< CFMU base address */

/* registers definitions */
#define CFMU_CTL                         REG32(CFMU + 0x00000000U)        /*!< control register */
#define CFMU_STAT                        REG32(CFMU + 0x00000004U)        /*!< status register */
#define CFMU_LVCFG                       REG32(CFMU + 0x00000008U)        /*!< limit value configuration register */
#define CFMU_CNT                         REG32(CFMU + 0x0000000CU)        /*!< counter value register */

/* bits definitions */
/* CFMU_CTL */
#define CFMU_CTL_CFMEN                   BIT(0)                           /*!< clock frequency measurement enable */
#define CFMU_CTL_REFINEN                 BIT(8)                           /*!< CFMUREF pin input enable */
#define CFMU_CTL_RCKSEL                  BITS(9,11)                       /*!< reference clock select */
#define CFMU_CTL_MCKDIV                  BITS(12,13)                      /*!< measurement clock frequency divider */
#define CFMU_CTL_EDGSEL                  BITS(14,15)                      /*!< edge select */
#define CFMU_CTL_RSSEL                   BIT(16)                          /*!< reference signal select */
#define CFMU_CTL_MCKSEL                  BITS(17,19)                      /*!< measurement clock select */
#define CFMU_CTL_RCKDIV                  BITS(20,21)                      /*!< reference clock frequency divider */
#define CFMU_CTL_DFSEL                   BITS(22,23)                      /*!< digital filter select */
#define CFMU_CTL_CFERRIE                 BIT(24)                          /*!< clock frequency error interrupt enable */
#define CFMU_CTL_CFMENDIE                BIT(25)                          /*!< clock frequency measurement end interrupt enable */
#define CFMU_CTL_OVIE                    BIT(26)                          /*!< overflow interrupt interrupt enable */
#define CFMU_CTL_CFERRCLR                BIT(28)                          /*!< clock frequency error flag clear */
#define CFMU_CTL_CFMENDFCLR              BIT(29)                          /*!< clock frequency measurement end flag clear */
#define CFMU_CTL_OVFCLR                  BIT(30)                          /*!< overflow flag clear */

/* CFMU_STAT */
#define CFMU_STAT_OVF                    BIT(0)                           /*!< counter overflow flag */
#define CFMU_STAT_CFMENDF                BIT(1)                           /*!< clock accuracy measurement end flag */
#define CFMU_STAT_CFERRF                 BIT(2)                           /*!< clock frequency error flag */

/* CFMU_LVCFG */
#define CFMU_LVCFG_LLV                   BITS(0,15)                       /*!< lower-limit value */
#define CFMU_LVCFG_HLV                   BITS(16,31)                      /*!< higher-limit value */

/*CFMU_CNT*/
#define CFMU_CNT_CNT                     BITS(0,15)                       /*!< counter value */

/* constants definitions */
/* define the peripheral clock enable bit position and its register index offset */
#define CFMU_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define CFMU_REG_VAL(periph)             (REG32(CFMU + ((uint32_t)(periph) >> 6U)))
#define CFMU_BIT_POS(val)                ((uint32_t)(val) & 0x0000001FU)

/* register offset */
/* CFMU control */
#define CFMU_CTL_REG_OFFSET              0x00000000U                      /*!< CFMU control register offset */
#define CFMU_STAT_REG_OFFSET             0x00000004U                      /*!< CFMU status register offset */

/* CFMU higher-limit value */
#define CFMU_HLV(regval)                 (BITS(16, 31) & ((uint32_t)(regval) << 16U))
/* CFMU lower-limit value */
#define CFMU_LLV(regval)                 (BITS(0, 15)  & ((uint32_t)(regval) <<  0U))

/* CFMU interrupt enable or disable */
typedef enum {
    CFMU_INT_CFERR              = CFMU_REGIDX_BIT(CFMU_CTL_REG_OFFSET, 24U),          /*!< clock frequency error interrupt request */
    CFMU_INT_CFMEND             = CFMU_REGIDX_BIT(CFMU_CTL_REG_OFFSET, 25U),          /*!< clock frequency accuracy measurement end interrupt request */
    CFMU_INT_OVF                = CFMU_REGIDX_BIT(CFMU_CTL_REG_OFFSET, 26U),          /*!< overflow interrupt request */
} cfmu_int_enum;

/* CFMU interrupt flags */
typedef enum {
    CFMU_INT_FLAG_OVF            = CFMU_REGIDX_BIT(CFMU_STAT_REG_OFFSET, 0U),         /*!< overflow flag */
    CFMU_INT_FLAG_CFMEND         = CFMU_REGIDX_BIT(CFMU_STAT_REG_OFFSET, 1U),         /*!< clock frequency accuracy measurement end flag */
    CFMU_INT_FLAG_CFERR          = CFMU_REGIDX_BIT(CFMU_STAT_REG_OFFSET, 2U),         /*!< clock frequency error flag */
} cfmu_int_flag_enum;

/* CFMU interrupt flags clear */
typedef enum {
    CFMU_INT_FLAG_CFERR_CLR      = CFMU_REGIDX_BIT(CFMU_CTL_REG_OFFSET, 28U),         /*!< clock frequency error flag clear */
    CFMU_INT_FLAG_CFMEND_CLR     = CFMU_REGIDX_BIT(CFMU_CTL_REG_OFFSET, 29U),         /*!< clock frequency accuracy measurement end flag clear */
    CFMU_INT_FLAG_OVF_CLR        = CFMU_REGIDX_BIT(CFMU_CTL_REG_OFFSET, 30U),         /*!< overflow flag clear */
} cfmu_int_flag_clear_enum;

/* digital filter select */
#define CTL_DFSEL(regval)                  (BITS(22,23) & ((uint32_t)(regval) << 22U))
#define CFMU_DFSEL_DISABLE                 CTL_DFSEL(0)                        /*!< digital filtering is disabled */
#define CFMU_DFSEL_DIV1                    CTL_DFSEL(1)                        /*!< sampling clock for the digital filter is the frequency measuring clock */
#define CFMU_DFSEL_DIV4                    CTL_DFSEL(2)                        /*!< sampling clock for the digital filter is the frequency measuring clock divided by 4 */
#define CFMU_DFSEL_DIV16                   CTL_DFSEL(3)                        /*!< sampling clock for the digital filter is the frequency measuring clock divided by 16 */

/* reference clock source select */
#define CTL_RCKSEL(regval)                 (BITS(9,11) & ((uint32_t)(regval) << 9U))
#define CFMU_RCKSRC_HXTAL                  CTL_RCKSEL(0)                       /*!<  reference clock source select HXTAL */
#define CFMU_RCKSRC_IRC32M                 CTL_RCKSEL(2)                       /*!<  reference clock source select IRC32M */
#define CFMU_RCKSRC_IRC32K                 CTL_RCKSEL(3)                       /*!<  reference clock source select IRC32K */
#define CFMU_RCKSRC_PCLK1                  CTL_RCKSEL(4)                       /*!<  reference clock source select PCLK1 */

/* reference  clock frequency division ration select */
#define CTL_RCKPSC(regval)                 (BITS(20,21) & ((uint32_t)(regval) << 20U))
#define CFMU_RCK_DIV32                     CTL_RCKPSC(0)                       /*!< reference clock is divided by 32 */
#define CFMU_RCK_DIV128                    CTL_RCKPSC(1)                       /*!< reference clock is divided by 128*/
#define CFMU_RCK_DIV1024                   CTL_RCKPSC(2)                       /*!< reference clock is divided by 1024*/
#define CFMU_RCK_DIV8192                   CTL_RCKPSC(3)                       /*!< reference clock is divided by 8192*/

/* measurement clock source select */
#define CTL_MCKSEL(regval)                 (BITS(17,19) & ((uint32_t)(regval) << 17U))
#define CFMU_MCKSRC_HXTAL                  CTL_MCKSEL(0)                       /*!< measurement clock source select HXTAL */
#define CFMU_MCKSRC_IRC32M                 CTL_MCKSEL(2)                       /*!< measurement clock source select IRC32M */
#define CFMU_MCKSRC_IRC32K                 CTL_MCKSEL(3)                       /*!< measurement clock source select IRC32K */
#define CFMU_MCKSRC_PCLK1                  CTL_MCKSEL(4)                       /*!< measurement clock source select PCLK1 */

/* measurement clock frequency division ration select */
#define CTL_MCKPSC(regval)                 (BITS(12,13) & ((uint32_t)(regval) << 12U))
#define CFMU_MCK_DIV1                      CTL_MCKPSC(0)                       /*!< measurement clock is divided by 1 */
#define CFMU_MCK_DIV4                      CTL_MCKPSC(1)                       /*!< measurement clock is divided by 4 */
#define CFMU_MCK_DIV8                      CTL_MCKPSC(2)                       /*!< measurement clock is divided by 8 */
#define CFMU_MCK_DIV32                     CTL_MCKPSC(3)                       /*!< measurement clock is divided by 32 */

/* cfmu reference_signal select */
#define CFMU_RSSEL_CFMUREF                 ((uint32_t)0x00000000U)             /*!< reference signal select the CFMUREF pin */
#define CFMU_RSSEL_INTERNAL_CLOCK          CFMU_CTL_RSSEL                      /*!< reference signal select the internal clock */

/* cfmu valid edge type */
#define CTL_EDGSEL(regval)                 (BITS(14,15) & ((uint32_t)(regval) << 14U))
#define CFMU_VAL_RISING                    CTL_EDGSEL(0)                       /*!< CFMU rising edge valid */
#define CFMU_VAL_FALLING                   CTL_EDGSEL(1)                       /*!< CFMU falling edge valid */
#define CFMU_VAL_BOTH                      CTL_EDGSEL(2)                       /*!< CFMU rising and falling edge valid */

/* function declarations */
/* deinitialize the CFMU */
void cfmu_deinit(void);
/* enable clock frequency measurement */
void cfmu_enable(void);
/* disable clock frequency measurement */
void cfmu_disable(void);
/* enable CFMUREF pin input */
void cfmu_cfmuref_enable(void);
/* disable CFMUREF pin input */
void cfmu_cfmuref_disable(void);
/* configure the reference signal */
void cfmu_reference_signal_config(uint32_t rssel);
/* configure the digital filter */
void cfmu_digital_filter_config(uint32_t dfsel);
/* configure the measurement reference clock source */
void cfmu_reference_clock_config(uint32_t rck_src, uint32_t rck_div, uint32_t val_edge);
/* configure the measurement target clock source */
void cfmu_measurement_clock_config(uint32_t mck_src, uint32_t mck_div);
/* configure CFMU higher-limit value and lower-limit value */
void cfmu_limit_value_config(uint32_t cfmu_hlv, uint32_t cfmu_llv);

/* interrupt and flag functions */
/* enable the CFMU interrupt */
void cfmu_interrupt_enable(cfmu_int_enum cfmu_interrupt);
/* disable the CFMU interrupt */
void cfmu_interrupt_disable(cfmu_int_enum cfmu_interrupt);
/* get the CFMU interrupt flags */
FlagStatus cfmu_interrupt_flag_get(cfmu_int_flag_enum cfmu_int_flag);
/* clear the CFMU interrupt flags */
void cfmu_interrupt_flag_clear(cfmu_int_flag_clear_enum cfmu_int_flag_clear);

#endif /* GD32M53X_CFMU_H */
