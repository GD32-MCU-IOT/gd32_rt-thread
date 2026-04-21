/*!
    \file    gd32m53x_pmu.h
    \brief   PMU driver

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

#ifndef GD32M53X_PMU_H
#define GD32M53X_PMU_H

#include "gd32m53x.h"

/* PMU definitions */
#define PMU                           PMU_BASE                       /*!< PMU base address */

/* registers definitions */
#define PMU_CTL                       REG32((PMU) + 0x00000000U)     /*!< control register */
#define PMU_CS                        REG32((PMU) + 0x00000004U)     /*!< control and status register */
#define PMU_LVD1CTL                   REG32((PMU) + 0x00000008U)     /*!< low voltage detector 1 control register */
#define PMU_LVD2CTL                   REG32((PMU) + 0x0000000CU)     /*!< low voltage detector 2 control register */

/* bits definitions */
/* PMU_CTL */
#define PMU_CTL_STBMOD                BIT(1)                         /*!< standby mode */
#define PMU_CTL_WURST                 BIT(2)                         /*!< wakeup flag reset */
#define PMU_CTL_STBRST                BIT(3)                         /*!< standby flag reset */
#define PMU_CTL_DSLDOVS               BITS(16,17)                    /*!< deep-sleep mode voltage scaling selection */

/* PMU_CS */
#define PMU_CS_WUF                    BIT(0)                         /*!< wakeup flag */
#define PMU_CS_STBF                   BIT(1)                         /*!< standby flag */
#define PMU_CS_LVD1DETF               BIT(2)                         /*!< low voltage detector 1 voltage change detection flag */
#define PMU_CS_LVD1OSF                BIT(3)                         /*!< low voltage detector 1 output signal flag */
#define PMU_CS_LVD2DETF               BIT(4)                         /*!< low voltage detector 2 voltage change detection flag */
#define PMU_CS_LVD2OSF                BIT(5)                         /*!< low voltage detector 2 output signal flag */
#define PMU_CS_WUPEN                  BIT(8)                         /*!< wakeup pin enable */

/* PMU_LVD1CTL */
#define PMU_LVD1CTL_LVD1EN            BIT(0)                         /*!< low voltage detector 1 enable */
#define PMU_LVD1CTL_LVD1INTSEL        BITS(1,2)                      /*!< low voltage detector 1 interrupt trigger mode */
#define PMU_LVD1CTL_LVD1ITSEL         BIT(3)                         /*!< low voltage detector 1 interrupt type select */
#define PMU_LVD1CTL_LVD1IRE           BIT(4)                         /*!< low voltage detector 1 interrupt or reset enable */
#define PMU_LVD1CTL_LVD1OUTEN         BIT(5)                         /*!< low voltage detector 1 comparison result output enable */
#define PMU_LVD1CTL_LVD1MSEL          BIT(6)                         /*!< low voltage detector 1 mode selection */
#define PMU_LVD1CTL_LVD1RSTSEL        BIT(7)                         /*!< low voltage detector 1 reset signal negation selection */
#define PMU_LVD1CTL_LVD1T             BITS(8,11)                     /*!< low voltage detector 1 threshold */
#define PMU_LVD1CTL_LVD1DNF           BIT(12)                        /*!< low voltage detector 1 digital noise filter enable */
#define PMU_LVD1CTL_LVD1SAMP          BITS(13,14)                    /*!< sampling clock select */

/* PMU_LVD2CTL */
#define PMU_LVD2CTL_LVD2EN            BIT(0)                         /*!< low voltage detector 2 enable */
#define PMU_LVD2CTL_LVD2INTSEL        BITS(1,2)                      /*!< low voltage detector 2 interrupt trigger mode */
#define PMU_LVD2CTL_LVD2ITSEL         BIT(3)                         /*!< low voltage detector 2 interrupt type Select */
#define PMU_LVD2CTL_LVD2IRE           BIT(4)                         /*!< low voltage detector 2 interrupt or reset Enable */
#define PMU_LVD2CTL_LVD2OUTEN         BIT(5)                         /*!< low voltage detector 2 comparison result output enable */
#define PMU_LVD2CTL_LVD2MSEL          BIT(6)                         /*!< low voltage detector 2 mode selection */
#define PMU_LVD2CTL_LVD2RSTSEL        BIT(7)                         /*!< low voltage detector 2 reset signal negation selection */
#define PMU_LVD2CTL_LVD2T             BITS(8,11)                     /*!< low voltage detector 2 threshold */
#define PMU_LVD2CTL_LVD2DNF           BIT(12)                        /*!< low voltage detector 2 digital noise filter enable */
#define PMU_LVD2CTL_LVD2SAMP          BITS(13,14)                    /*!< sampling clock select */

#define CTL_DSLDOVS(regval)           (BITS(16,17)&((uint32_t)(regval) << 16))
#define PMU_DSLDOVS_0                 CTL_DSLDOVS(0)                 /*!< deepsleep mode ldo voltage is 0.9V */
#define PMU_DSLDOVS_1                 CTL_DSLDOVS(1)                 /*!< deepsleep mode ldo voltage is 1.0V */
#define PMU_DSLDOVS_2                 CTL_DSLDOVS(2)                 /*!< deepsleep mode ldo voltage is 1.1V */
#define PMU_DSLDOVS_3                 CTL_DSLDOVS(3)                 /*!< deepsleep mode ldo voltage is 1.2V */

/* PMU flag reset definitions */
#define PMU_FLAG_RESET_WAKEUP          ((uint8_t)0x00U)                /*!< wakeup flag reset */
#define PMU_FLAG_RESET_STANDBY         ((uint8_t)0x01U)                /*!< standby flag reset */

/* select the definitions for low voltage detector x(x=1,2) interrupt generation condition */
#define LVDxCTL_LVDxINTSEL(regval)     (BITS(1,2)&((uint32_t)(regval)<<1))
#define PMU_LVD_INT_RISING              LVDxCTL_LVDxINTSEL(0)          /*!< vcc >= vdetx(rising) */
#define PMU_LVD_INT_FALLING             LVDxCTL_LVDxINTSEL(1)          /*!< vcc < vdetx(falling) */
#define PMU_LVD_INT_BOTH                LVDxCTL_LVDxINTSEL(2)          /*!< vcc >= vdetx(rising) or vcc < vdetx(falling) */

/* select the definitions for low voltage detector x(x=1,2) interrupt type */
#define LVDxCTL_LVDxITSEL(regval)      (BIT(3)&((uint32_t)(regval)<<3))
#define PMU_LVD_INT_MASKABLE            LVDxCTL_LVDxITSEL(1)           /*!< maskable interrupt */
#define PMU_LVD_INT_NON_MASKABLE        LVDxCTL_LVDxITSEL(0)           /*!< non-maskable interrupt */

/* select the definitions for low voltage detector x(x=1,2) mode */
#define LVDxCTL_LVDxMSEL(regval)       (BIT(6)&((uint32_t)(regval)<<6))
#define PMU_LVD_RESET                   LVDxCTL_LVDxMSEL(1)            /*!< low voltage detector reset occurs when the voltage falls below Vdetx */
#define PMU_LVD_INTERRUPT               LVDxCTL_LVDxMSEL(0)            /*!< low voltage detector interrupt occurs when the voltage falls below Vdetx */

/* select the definitions for low voltage detector x (x=1,2) reset signal negation */
#define LVDxCTL_LVDxRSTSEL(regval)     (BIT(7)&((uint32_t)(regval)<<7))
#define PMU_LVD_RESET_ASSERTION         LVDxCTL_LVDxRSTSEL(1)          /*!< after the LVD reset signal is asserted, the reset signal will be negated after a stabilization time (tLVDx) */
#define PMU_LVD_RESET_RISE              LVDxCTL_LVDxRSTSEL(0)          /*!< the reset signal will be negated after a stabilization time (tLVDx) following the detection of VCC > Vdetx */

/* select the definitions for low voltage detector x(x=1,2) threshold (rising or falling) */
#define LVDxCTL_LVDxT(regval)          (BITS(8,11)&((uint32_t)(regval)<<8))
#define PMU_LVDT_0                      LVDxCTL_LVDxT(4)               /*!< low voltage detector threshold is 4.62v/4.54v */
#define PMU_LVDT_1                      LVDxCTL_LVDxT(5)               /*!< low voltage detector threshold is 4.55v/4.47v */
#define PMU_LVDT_2                      LVDxCTL_LVDxT(6)               /*!< low voltage detector threshold is 4.40v/4.32v */
#define PMU_LVDT_3                      LVDxCTL_LVDxT(10)              /*!< low voltage detector threshold is 3.03v/2.95v */
#define PMU_LVDT_4                      LVDxCTL_LVDxT(11)              /*!< low voltage detector threshold is 2.96v/2.88v */

/* select the definitions for low voltage detector x(x=1,2) sampling clock */
#define LVDxCTL_LVDxSAMP(regval)       (BITS(13,14)&((uint32_t)(regval)<<13))
#define PMU_LVDSAMP_DIV2                LVDxCTL_LVDxSAMP(0)            /*!< low voltage detector sampling clock select 1/2 pclk1 frequency */
#define PMU_LVDSAMP_DIV4                LVDxCTL_LVDxSAMP(1)            /*!< low voltage detector sampling clock select 1/4 pclk1 frequency */
#define PMU_LVDSAMP_DIV8                LVDxCTL_LVDxSAMP(2)            /*!< low voltage detector sampling clock select 1/8 pclk1 frequency */
#define PMU_LVDSAMP_DIV16               LVDxCTL_LVDxSAMP(3)            /*!< low voltage detector sampling clock select 1/16 pclk1 frequency */

/* low voltage detector register definitions */
#define PMU_LVD_1                     ((uint8_t)0x00U)                 /*!< low voltage detector 1 */
#define PMU_LVD_2                     ((uint8_t)0x01U)                 /*!< low voltage detector 2 */

/* PMU command constants definitions */
#define WFI_CMD                       ((uint8_t)0x00U)                 /*!< use WFI command */
#define WFE_CMD                       ((uint8_t)0x01U)                 /*!< use WFE command */

/* PMU flag definitions */
#define PMU_FLAG_WAKEUP               PMU_CS_WUF                       /*!< wakeup flag status */
#define PMU_FLAG_STANDBY              PMU_CS_STBF                      /*!< standby flag status */
#define PMU_FLAG_LVD1DETF             PMU_CS_LVD1DETF                  /*!< low voltage detector 1 voltage change detection flag */
#define PMU_FLAG_LVD1OSF              PMU_CS_LVD1OSF                   /*!< low voltage detector 1 output signal flag */
#define PMU_FLAG_LVD2DETF             PMU_CS_LVD2DETF                  /*!< low voltage detector 2 voltage change detection flag */
#define PMU_FLAG_LVD2OSF              PMU_CS_LVD2OSF                   /*!< low voltage detector 2 output signal flag */

/* function declarations */
/* reset PMU registers */
void pmu_deinit(void);

/* set PMU mode */
/* PMU work in sleep mode */
void pmu_to_sleepmode(uint8_t sleepmodecmd);
/* PMU work in deepsleep mode */
void pmu_to_deepsleepmode(uint8_t deepsleepmodecmd);
/* PMU work in standby mode */
void pmu_to_standbymode(void);
/* PMU work in deepsleep mode ldo voltage output configure */
void pmu_deepsleepmode_vcore_output(uint32_t dsldovs);
/* enable PMU wakeup pin */
void pmu_wakeup_pin_enable(void);
/* disable PMU wakeup pin */
void pmu_wakeup_pin_disable(void);

/* voltage monitor functions */
/* enable low voltage detector */
void pmu_lvd_enable(uint8_t lvd_select);
/* disable low voltage detector */
void pmu_lvd_disable(uint8_t lvd_select);
/* select the interrupt generation condition for the low voltage detector */
void pmu_lvd_interrupt_select(uint8_t lvd_select, uint32_t select_condition);
/* select the interrupt type for the low voltage detector */
void pmu_lvd_interrupt_type(uint8_t lvd_select, uint32_t interrupt_type);
/* enable low voltage detector interrupt or reset */
void pmu_lvd_interrupt_reset_enable(uint8_t lvd_select);
/* disable low voltage detector interrupt or reset */
void pmu_lvd_interrupt_reset_disable(uint8_t lvd_select);
/* enable low voltage detector comparison result output */
void pmu_lvd_output_enable(uint8_t lvd_select);
/* disable low voltage detector comparison result output */
void pmu_lvd_output_disable(uint8_t lvd_select);
/* select low voltage detector mode */
void pmu_lvd_mode_select(uint8_t lvd_select, uint32_t mode);
/* select low voltage detector reset negation */
void pmu_lvd_reset_select(uint8_t lvd_select, uint32_t mode);
/* select low voltage detector level */
void pmu_lvd_level_select(uint8_t lvd_select, uint32_t level);
/* enable low voltage detector digital filter */
void pmu_lvd_digital_filter_enable(uint8_t lvd_select);
/* disable low voltage detector digital filter */
void pmu_lvd_digital_filter_disable(uint8_t lvd_select);
/* select low voltage detector sampling clock */
void pmu_lvd_sample_clock_select(uint8_t lvd_select, uint32_t clock);

/* flag functions */
/* get flag state */
FlagStatus pmu_flag_get(uint32_t flag);
/* clear flag bit */
void pmu_flag_clear(uint32_t flag);

#endif /* GD32M53X_PMU_H */
