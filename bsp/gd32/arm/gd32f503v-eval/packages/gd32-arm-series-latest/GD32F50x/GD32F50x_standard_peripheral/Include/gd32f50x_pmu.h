/*!
    \file    gd32f50x_pmu.h
    \brief   definitions for the PMU

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


#ifndef GD32F50X_PMU_H
#define GD32F50X_PMU_H

#include "gd32f50x.h"

/* PMU definitions */
#define PMU                           PMU_BASE                      /*!< PMU base address */

/* registers definitions */
#define PMU_CTL0                      REG32((PMU) + 0x00000000U)    /*!< PMU control register */
#define PMU_CS                        REG32((PMU) + 0x00000004U)    /*!< PMU control and status register */
#define PMU_CTL1                      REG32((PMU) + 0x00000008U)    /*!< PMU control  register */

/* bits definitions */
/* PMU_CTL0 */
#define PMU_CTL0_LDOLP                BIT(0)                        /*!< LDO low power mode */
#define PMU_CTL0_STBMOD               BIT(1)                        /*!< standby mode */
#define PMU_CTL0_WURST                BIT(2)                        /*!< wakeup flag reset */
#define PMU_CTL0_STBRST               BIT(3)                        /*!< standby flag reset */
#define PMU_CTL0_LVDEN                BIT(4)                        /*!< low voltage detector enable */
#define PMU_CTL0_LVDT                 BITS(5,7)                     /*!< low voltage detector threshold */
#define PMU_CTL0_BKPWEN               BIT(8)                        /*!< backup domain write enable */
#define PMU_CTL0_PDR_LVLSEL           BIT(9)                        /*!< PDR threshold selection signal */
#define PMU_CTL0_LDLP                 BIT(10)                       /*!< low-driver mode when use low power LDO */
#define PMU_CTL0_LDNP                 BIT(11)                       /*!< low-driver mode when use normal power LDO */
#define PMU_CTL0_LDOVS                BITS(12,14)                   /*!< LDO output voltage select */
#define PMU_CTL0_LDEN                 BITS(18,19)                   /*!< low-driver mode enable in deep-sleep mode */
#define PMU_CTL0_VAVDEN               BIT(20)                       /*!< vavd enable */
#define PMU_CTL0_VAVDVC               BITS(21,22)                   /*!< low-driver mode enable in deep-sleep mode */
#define PMU_CTL0_VOVDEN               BIT(23)                       /*!< VCORE over voltage detector enable  */
#define PMU_CTL0_VUVDEN               BIT(24)                       /*!< VCORE under voltage detector enable */
#define PMU_CTL0_VOVDVC               BITS(25,26)                   /*!< VCORE overvoltage detector voltage level configuration */
#define PMU_CTL0_VUVDVC               BITS(27,28)                   /*!< VCORE undervoltage detector voltage level configuration */
#define PMU_CTL0_UNLOCK               BIT(31)                       /*!< PMU register unlock*/

/* PMU_CS */
#define PMU_CS_WUF                    BIT(0)                        /*!< wakeup flag */
#define PMU_CS_STBF                   BIT(1)                        /*!< standby flag */
#define PMU_CS_LVDF                   BIT(2)                        /*!< low voltage detector status flag */
#define PMU_CS_VAVDF                  BIT(3)                        /*!< vavd output signal */
#define PMU_CS_VUVDF0                 BIT(4)                        /*!< vuvd flag 0 */
#define PMU_CS_VOVDF                  BIT(6)                        /*!< VCORE over voltage detector flag */
#define PMU_CS_VUVDF1                 BIT(7)                        /*!< VCORE under voltage detector flag */
#define PMU_CS_WUPEN                  BIT(8)                        /*!< wakeup pin enable */
#define PMU_CS_LDOVSRF                BIT(14)                       /*!< LDO voltage select ready flag */
#define PMU_CS_LDRF                   BITS(18,19)                   /*!< Low-driver mode ready flag */

/* PMU_CTL1 */
#define PMU_CTL1_VOVDO_DNF            BITS(0,7)                     /*!< vovdo analog output digital noise filter */
#define PMU_CTL1_VUVDO_DNF            BITS(8,15)                    /*!< vuvdo analog output digital noise filter */

/* constants definitions */
/* PMU ldo definitions */
#define PMU_LDO_NORMAL              ((uint32_t)0x00000000U)       /*!< LDO normal work when PMU enter deepsleep mode */
#define PMU_LDO_LOWPOWER            PMU_CTL0_LDOLP                /*!< LDO work in low power status when PMU enter deepsleep mode */

/* PMU low voltage detector threshold definitions */
#define CTL0_LVDT(regval)             (BITS(5,7) & ((uint32_t)(regval) << 5U))
#define PMU_LVDT_0                    CTL0_LVDT(0)                  /*!< voltage threshold is 2.1V */
#define PMU_LVDT_1                    CTL0_LVDT(1)                  /*!< voltage threshold is 2.3V */
#define PMU_LVDT_2                    CTL0_LVDT(2)                  /*!< voltage threshold is 2.4V */
#define PMU_LVDT_3                    CTL0_LVDT(3)                  /*!< voltage threshold is 2.6V */
#define PMU_LVDT_4                    CTL0_LVDT(4)                  /*!< voltage threshold is 2.7V */
#define PMU_LVDT_5                    CTL0_LVDT(5)                  /*!< voltage threshold is 2.8V */
#define PMU_LVDT_6                    CTL0_LVDT(6)                  /*!< voltage threshold is 3.0V */
#define PMU_LVDT_7                    CTL0_LVDT(7)                  /*!< voltage threshold is 3.1V */

/* Power down reset threshold selection */
#define CTL0_PDRVS(regval)            (BIT(9) & ((uint32_t)(regval) << 9U))
#define PMU_PDRVS_LEVEL0              CTL0_PDRVS(0)                 /*!< Power down reset threshold select 2.35V */
#define PMU_PDRVS_LEVEL1              CTL0_PDRVS(1)                 /*!< Power down reset threshold select 1.8V */

/* PMU low-driver mode when use low power LDO */
#define CTL0_LDLP(regval)             (BIT(10) & ((uint32_t)(regval) << 10U))
#define PMU_NORMALDR_LOWPWR           CTL0_LDLP(0)                  /*!< normal driver when use low power LDO */
#define PMU_LOWDR_LOWPWR              CTL0_LDLP(1)                  /*!< low-driver mode enabled when LDEN is 11 and use low power LDO */

/* PMU low-driver mode when use normal power LDO */
#define CTL0_LDNP(regval)             (BIT(11) & ((uint32_t)(regval) << 11U))
#define PMU_NORMALDR_NORMALPWR        CTL0_LDNP(0)                  /*!< normal driver when use normal power LDO */
#define PMU_LOWDR_NORMALPWR           CTL0_LDNP(1)                  /*!< low-driver mode enabled when LDEN is 11 and use normal power LDO */

/* PMU LDO output voltage select definitions */
#define CTL0_LDOVS(regval)            (BITS(12,14) & ((uint32_t)(regval) << 12U))
#define PMU_LDOVS_1                   CTL0_LDOVS(1)                 /*!< LDO output voltage 0.9V */
#define PMU_LDOVS_2                   CTL0_LDOVS(2)                 /*!< LDO output voltage 0.95V */
#define PMU_LDOVS_3                   CTL0_LDOVS(3)                 /*!< LDO output voltage 1.0V */
#define PMU_LDOVS_4                   CTL0_LDOVS(4)                 /*!< LDO output voltage 1.05V */
#define PMU_LDOVS_5                   CTL0_LDOVS(5)                 /*!< LDO output voltage 1.1V */
#define PMU_LDOVS_6                   CTL0_LDOVS(6)                 /*!< LDO output voltage 1.15V */
#define PMU_LDOVS_7                   CTL0_LDOVS(7)                 /*!< LDO output voltage 1.2V */

/* PMU VAVD threshold selection signal definitions */
#define CTL0_VAVDVC(regval)           (BITS(21,22) & ((uint32_t)(regval) << 21U))
#define PMU_VAVDVC_0                  CTL0_VAVDVC(0)                /*!< VDDA rising threshold is 2.4V, VDDA falling threshold is 2.3V */
#define PMU_VAVDVC_1                  CTL0_VAVDVC(1)                /*!< VDDA rising threshold is 2.6V, VDDA falling threshold is 2.5V */
#define PMU_VAVDVC_2                  CTL0_VAVDVC(2)                /*!< VDDA rising threshold is 2.8V, VDDA falling threshold is 2.7V */
#define PMU_VAVDVC_3                  CTL0_VAVDVC(3)                /*!< VDDA rising threshold is 3V, VDDA falling threshold is 2.9V */

/* PMU VOVDVC threshold selection signal definitions */
#define CTL0_VOVDVC(regval)           (BITS(25,26) & ((uint32_t)(regval) << 25U))
#define PMU_VOVDVC_0                  CTL0_VOVDVC(0)                /*!< 1.25V rising threshold, 1.225V falling threshold */
#define PMU_VOVDVC_1                  CTL0_VOVDVC(1)                /*!< 1.30V rising threshold, 1.275V falling threshold */
#define PMU_VOVDVC_2                  CTL0_VOVDVC(2)                /*!< 1.35V rising threshold, 1.325V falling threshold */
#define PMU_VOVDVC_3                  CTL0_VOVDVC(3)                /*!< 1.40V rising threshold, 1.375V falling threshold */

/* PMU VUVDVC threshold selection signal definitions */
#define CTL0_VUVDVC(regval)           (BITS(27,28) & ((uint32_t)(regval) << 27U))
#define PMU_VUVDVC_0                  CTL0_VUVDVC(0)                /*!< 1.075V rising threshold, 1.05V falling threshold */
#define PMU_VUVDVC_1                  CTL0_VUVDVC(1)                /*!< 0.975V rising threshold, 0.95V falling threshold */
#define PMU_VUVDVC_2                  CTL0_VUVDVC(2)                /*!< 0.875V rising threshold, 0.85V falling threshold */

/* PMU Low Power mode */
#define CTL0_LDOLP(regval)            (BIT(0) & ((uint32_t)(regval) << 0U))
#define PMU_LOW_POWER_MODE_NORMAL     CTL0_LDOLP(0)                 /*!< LDO operates normally during the Deep-sleep mode */
#define PMU_LOW_POWER_MODE_EN         CTL0_LDOLP(1)                 /*!< LDO is in low power mode during the Deep-sleep mode */

/* low-driver mode in deep-sleep mode */
#define PMU_LOWDRIVER_DISABLE         ((uint32_t)0x00000000U)       /*!< Low-driver mode disable in Deep-sleep mode */
#define PMU_LOWDRIVER_ENABLE          PMU_CTL0_LDEN                 /*!< Low-driver mode enable in Deep-sleep mode */

/* PMU low power mode ready flag definitions */
#define CS_LDRF(regval)               (BITS(18,19) & ((uint32_t)(regval) << 18U))
#define PMU_LDRF_NORMAL               CS_LDRF(0)                    /*!< normal driver in deep-sleep mode */
#define PMU_LDRF_LOWDRIVER            CS_LDRF(3)                    /*!< low-driver mode in deep-sleep mode */

/* PMU flag definitions */
#define PMU_FLAG_WAKEUP               PMU_CS_WUF                    /*!< wakeup flag status */
#define PMU_FLAG_STANDBY              PMU_CS_STBF                   /*!< standby flag status */
#define PMU_FLAG_LVD                  PMU_CS_LVDF                   /*!< lvd flag status */
#define PMU_FLAG_VAVDF                PMU_CS_VAVDF                  /*!< vavd voltage detector flag status */
#define PMU_FLAG_VUVDF0               PMU_CS_VUVDF0                 /*!< VCORE low voltage detector flag 0 */
#define PMU_FLAG_VOVDF                PMU_CS_VOVDF                  /*!< VCORE over voltage detector flag */
#define PMU_FLAG_VUVDF1               PMU_CS_VUVDF1                 /*!< VCORE low voltage detector flag 1 */
#define PMU_FLAG_LDOVSRF              PMU_CS_LDOVSRF                /*!< LDO voltage select ready flag */
#define PMU_FLAG_LDRF                 PMU_CS_LDRF                   /*!< low-driver mode ready flag */

/* PMU flag reset definitions */
#define PMU_FLAG_RESET_WAKEUP         ((uint8_t)0x00U)              /*!< wakeup flag reset */
#define PMU_FLAG_RESET_STANDBY        ((uint8_t)0x01U)              /*!< standby flag reset */

/* PMU command constants definitions */
#define WFI_CMD                       ((uint8_t)0x00U)              /*!< use WFI command */
#define WFE_CMD                       ((uint8_t)0x01U)              /*!< use WFE command */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
    /* check USART baud rate */
    #define NOT_LDO_OUTPUT_VOL(ldovs)             ((ldovs) == 0x00U)
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* reset PMU registers */
void pmu_deinit(void);
/* lock the PMU register */
void pmu_lock(void);
/* unlock the PMU register */
void pmu_unlock(void);

/* select low voltage detector threshold */
void pmu_lvd_select(uint32_t lvdt_n);
/* select power down reset detector threshold */
void pmu_pdrvs_select(uint32_t pdrvl);
/* select LDO output voltage */
void pmu_ldo_output_select(uint32_t ldo_output);

/* enable PMU lvd */
void pmu_lvd_enable(void);
/* disable PMU lvd */
void pmu_lvd_disable(void);
/* enable low-driver mode in deep-sleep mode */
void pmu_lowdriver_mode_enable(void);
/* disable low-driver mode in deep-sleep mode */
void pmu_lowdriver_mode_disable(void);

/* in deep-sleep mode, driver mode when use low power LDO */
void pmu_lowpower_driver_config(uint32_t mode);
/* in deep-sleep mode, driver mode when use normal power LDO */
void pmu_normalpower_driver_config(uint32_t mode);
/* PMU work in sleep mode */
void pmu_to_sleepmode(uint8_t sleepmodecmd);
/* PMU work in deepsleep mode */
void pmu_to_deepsleepmode(uint32_t ldo, uint32_t lowdrive, uint8_t deepsleepmodecmd);
/* PMU work in standby mode */
void pmu_to_standbymode(void);

/* enable PMU wakeup pin */
void pmu_wakeup_pin_enable(void);
/* disable PMU wakeup pin */
void pmu_wakeup_pin_disable(void);

/* enable backup domain write */
void pmu_backup_write_enable(void);
/* disable backup domain write */
void pmu_backup_write_disable(void);

/* enable vavd */
void pmu_vavd_enable(void);
/* disable vavd */
void pmu_vavd_disable(void);
/* enable vovd */
void pmu_vovd_enable(void);
/* disable vovd */
void pmu_vovd_disable(void);
/* enable vuvd */
void pmu_vuvd_enable(void);
/* disable vuvd */
void pmu_vuvd_disable(void);

/* select vavd threshold */
void pmu_vavd_select(uint32_t vavd_select);
/* select vovdvc threshold */
void pmu_vovd_select(uint32_t vovd_select);
/* select vuvdvc threshold */
void pmu_vuvd_select(uint32_t vuvd_select);
/* select vuvdo_dnf */
void pmu_vuvdo_dnf_select(uint32_t vuvdo_value);
/* select vovdo_dnf */
void pmu_vovdo_dnf_select(uint32_t vovdo_value);

/* get flag state */
FlagStatus pmu_flag_get(uint32_t flag);
/* clear flag bit */
void pmu_flag_clear(uint32_t flag);

#endif /* GD32F50X_PMU_H */
