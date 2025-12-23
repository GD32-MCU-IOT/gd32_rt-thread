/*!
    \file    gd32g5x3_pmu.h
    \brief   definitions for the PMU

    \version 2025-02-10, V1.1.0, firmware for GD32G5x3
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

#ifndef GD32G5X3_PMU_H
#define GD32G5X3_PMU_H

#include "gd32g5x3.h"

/* PMU definitions */
#define PMU                             PMU_BASE                            /*!< PMU base address */

/* registers definitions */
#define PMU_CTL0                        REG32((PMU) + 0x00000000U)          /*!< PMU control register 0 */
#define PMU_CS                          REG32((PMU) + 0x00000004U)          /*!< PMU control and status register 0 */
#define PMU_CTL1                        REG32((PMU) + 0x00000008U)          /*!< PMU control register 1 */
#define PMU_CTL2                        REG32((PMU) + 0x0000000CU)          /*!< PMU control register 2 */
#define PMU_CTL3                        REG32((PMU) + 0x00000018U)          /*!< PMU control register 3 */

/* bits definitions */
/* PMU_CTL0 */
#define PMU_CTL0_LDOLP                  BIT(0)                              /*!< LDO low power mode */
#define PMU_CTL0_STBMOD                 BIT(1)                              /*!< standby mode */
#define PMU_CTL0_WURST                  BIT(2)                              /*!< wakeup flag reset */
#define PMU_CTL0_STBRST                 BIT(3)                              /*!< standby flag reset */
#define PMU_CTL0_LVDEN                  BIT(4)                              /*!< low voltage detector enable */
#define PMU_CTL0_LVDT                   BITS(5,7)                           /*!< low voltage detector threshold */
#define PMU_CTL0_BKPWEN                 BIT(8)                              /*!< backup domain write enable */
#define PMU_CTL0_LDOVS                  BITS(11,15)                          /*!< LDO output voltage select */
#define PMU_CTL0_DSLPVS                 BITS(16,17)                         /*!< Deepsleep mode voltage scaling selection */
#define PMU_CTL0_VAVDEN                 BIT(20)                             /*!< VDDA analog voltage detector enable */
#define PMU_CTL0_VAVDVC                 BITS(21,22)                         /*!< VDDA analog voltage detector level configure bits */
#define PMU_CTL0_VOVDEN                 BIT(23)                             /*!< VCORE over voltage detector enable */
#define PMU_CTL0_VUVDEN                 BIT(24)                             /*!< VCORE under voltage detector enable */
#define PMU_CTL0_VOVDVC                 BITS(25,26)                         /*!< VCORE over voltage detector voltage level configure */
#define PMU_CTL0_VUVDVC                 BITS(27,28)                         /*!< VCORE under voltage detector voltage level configure */

/* PMU_CS */
#define PMU_CS_WUF                     BIT(0)                              /*!< wakeup flag */
#define PMU_CS_STBF                    BIT(1)                              /*!< standby flag */
#define PMU_CS_LVDF                    BIT(2)                              /*!< low voltage detector status flag */
#define PMU_CS_VAVDF                   BIT(3)                              /*!< Analog voltage detector on VDDA */
#define PMU_CS_VOVDF0                  BIT(4)                              /*!< Over voltage on VCORE detector flag bit */
#define PMU_CS_VUVDF0                  BIT(5)                              /*!< Under voltage on VCORE detector flag bit */
#define PMU_CS_VOVDF1                  BIT(6)                              /*!< Over voltage on VCORE detector flag bit after digital filter */
#define PMU_CS_VUVDF1                  BIT(7)                              /*!< Under voltage on VCORE detector flag bit after digital filter */
#define PMU_CS_WUPEN0                  BIT(8)                              /*!< wakeup pin0(PA0) enable */
#define PMU_CS_WUPEN1                  BIT(9)                              /*!< wakeup pin1(PC13) enable */
#define PMU_CS_WUPEN2                  BIT(10)                             /*!< wakeup pin2(PE6) enable */
#define PMU_CS_WUPEN3                  BIT(11)                             /*!< wakeup pin3(PA2) enable */
#define PMU_CS_WUPEN4                  BIT(12)                             /*!< wakeup pin4(PC5) enable */

/* PMU_CTL1 */
#define PMU_CTL1_BKPVSEN                BIT(0)                              /*!< Backup regulator enable */
#define PMU_CTL1_VBTMEN                 BIT(4)                              /*!< VBAT and temperature monitoring enable */
#define PMU_CTL1_BKPVSRF                BIT(16)                             /*!< Backup regulator ready */
#define PMU_CTL1_VBATLF                 BIT(20)                             /*!< VBAT level monitoring versus low threshold */
#define PMU_CTL1_VBATHF                 BIT(21)                             /*!< VBAT level monitoring versus high threshold */
#define PMU_CTL1_TEMPLF                 BIT(22)                             /*!< temperature level monitoring versus low threshold */
#define PMU_CTL1_TEMPHF                 BIT(23)                             /*!< temperature level monitoring versus high threshold */

/* PMU_CTL2 */
#define PMU_CTL2_VCEN                   BIT(8)                              /*!< VBAT battery charging enable */
#define PMU_CTL2_VCRSEL                 BIT(9)                              /*!< VBAT battery charging resistor selection */

/* PMU_CTL3 */
#define PMU_CTL3_VOVDO_DNF              BITS(0,7)                            /*!< VOVD analog output digital noise filter */
#define PMU_CTL3_VUVDO_DNF              BITS(8,15)                           /*!< VUVD analog output digital noise filter */

/* constants definitions */
/* PMU low power definitions */
#define PMU_LDO_NORMAL                  ((uint32_t)0x00000000U)             /*!< LDO normal work when PMU enter deepsleep/deepsleep1 mode */
#define PMU_LDO_LOWPOWER                PMU_CTL0_LDOLP                      /*!< LDO work at low power status when PMU enter deepsleep/deepsleep1 mode */

/* PMU low voltage detector threshold definitions */
#define CTL0_LVDT(regval)               (BITS(5,7) & ((uint32_t)(regval) << 5U))
#define PMU_LVDT_0                      CTL0_LVDT(0)                        /*!< voltage threshold is 2.15V */
#define PMU_LVDT_1                      CTL0_LVDT(1)                        /*!< voltage threshold is 2.3V */
#define PMU_LVDT_2                      CTL0_LVDT(2)                        /*!< voltage threshold is 2.45V */
#define PMU_LVDT_3                      CTL0_LVDT(3)                        /*!< voltage threshold is 2.6V */
#define PMU_LVDT_4                      CTL0_LVDT(4)                        /*!< voltage threshold is 2.75V */
#define PMU_LVDT_5                      CTL0_LVDT(5)                        /*!< voltage threshold is 2.9V */
#define PMU_LVDT_6                      CTL0_LVDT(6)                        /*!< voltage threshold is 3.0V */
#define PMU_LVDT_7                      CTL0_LVDT(7)                        /*!< PA10 external input analog voltage(compare with 1.2V) */

/* PMU LDO output voltage select definitions */
#define CTL_LDOVS(regval)             (BITS(11,15)&((uint32_t)(regval) << 11U))
#define PMU_LDOVS_1_1V                 CTL_LDOVS(12)                      /*!< LDO output voltage 1.1V */
#define PMU_LDOVS_1_15V                CTL_LDOVS(14)                      /*!< LDO output voltage 1.15V */

/* PMU deepsleep/Deepsleep1 mode voltage definitions */
#define CTL0_DSLPVS(regval)             (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define PMU_DSLPVS_0                    CTL0_DSLPVS(0)                      /*!< deepsleep/Deepsleep1 mode voltage 0.8V */
#define PMU_DSLPVS_1                    CTL0_DSLPVS(1)                      /*!< deepsleep/Deepsleep1 mode voltage 0.9V */
#define PMU_DSLPVS_2                    CTL0_DSLPVS(2)                      /*!< deepsleep/Deepsleep1 mode voltage 1.0V */
#define PMU_DSLPVS_3                    CTL0_DSLPVS(3)                      /*!< deepsleep/Deepsleep1 mode voltage 1.1V */


/* PMU analog voltage detector threshold definitions */
#define CTL0_VAVDVC(regval)             (BITS(21,22) & ((uint32_t)(regval) << 21U))
#define PMU_AVDT_0                      CTL0_VAVDVC(0)                      /*!< voltage threshold is 1.8V */
#define PMU_AVDT_1                      CTL0_VAVDVC(1)                      /*!< voltage threshold is 2.2V */
#define PMU_AVDT_2                      CTL0_VAVDVC(2)                      /*!< voltage threshold is 2.6V */
#define PMU_AVDT_3                      CTL0_VAVDVC(3)                      /*!< voltage threshold is 2.9V */

/* PMU core over voltage detector threshold definitions */
#define CTL0_VOVDVC(regval)             (BITS(25,26) & ((uint32_t)(regval) << 25U))
#define PMU_OVDT_0                      CTL0_VOVDVC(0)                      /*!< voltage threshold is 1.25V */
#define PMU_OVDT_1                      CTL0_VOVDVC(1)                      /*!< voltage threshold is 1.35V */
#define PMU_OVDT_2                      CTL0_VOVDVC(2)                      /*!< voltage threshold is 1.45V */
#define PMU_OVDT_3                      CTL0_VOVDVC(3)                      /*!< voltage threshold is 1.55V */

/* PMU core under voltage detector threshold definitions */
#define CTL0_VUVDVC(regval)             (BITS(27,28) & ((uint32_t)(regval) << 27U))
#define PMU_UVDT_0                      CTL0_VUVDVC(0)                      /*!< voltage threshold is 0.95V */
#define PMU_UVDT_1                      CTL0_VUVDVC(1)                      /*!< voltage threshold is 0.85V */
#define PMU_UVDT_2                      CTL0_VUVDVC(2)                      /*!< voltage threshold is 0.75V */
#define PMU_UVDT_3                      CTL0_VUVDVC(3)                      /*!< voltage threshold is 0.65V */

/* PMU VBAT battery charging resistor selection */
#define PMU_VCRSEL_5K                   ((uint32_t)0x00000000U)             /*!< 5 kOhms resistor is selected for charing VBAT battery */
#define PMU_VCRSEL_1P5K                 PMU_CTL2_VCRSEL                     /*!< 1.5 kOhms resistor is selected for charing VBAT battery */

/* PMU flag definitions */
#define PMU_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define PMU_REG_VAL(periph)             (REG32(PMU + ((uint32_t)(periph) >> 6U)))
#define PMU_BIT_POS(val)                ((uint32_t)(val) & 0x1FU)

#define PMU_CS_OFFSET                   (0x00000004U)                       /*!< PMU control and status register 0 offset */
#define PMU_CTL1_OFFSET                 (0x00000008U)                       /*!< PMU control register 1 offset */

#define PMU_FLAG_WAKEUP                    PMU_REGIDX_BIT(PMU_CS_OFFSET, 0)    /*!< wakeup flag */
#define PMU_FLAG_STANDBY                   PMU_REGIDX_BIT(PMU_CS_OFFSET, 1)    /*!< standby flag */
#define PMU_FLAG_LVDF                   PMU_REGIDX_BIT(PMU_CS_OFFSET, 2)    /*!< low voltage detector status flag */
#define PMU_FLAG_VAVDF                  PMU_REGIDX_BIT(PMU_CS_OFFSET, 3)    /*!< VDDA analog voltage detector voltage output on VDDA flag */
#define PMU_FLAG_VOVDF0                 PMU_REGIDX_BIT(PMU_CS_OFFSET, 4)    /*!< Over voltage on VCORE detector flag */
#define PMU_FLAG_VUVDF0                 PMU_REGIDX_BIT(PMU_CS_OFFSET, 5)    /*!< Under voltage on VCORE detector flag */
#define PMU_FLAG_VOVDF1                 PMU_REGIDX_BIT(PMU_CS_OFFSET, 6)    /*!< Over voltage on VCORE detector flag after digital filter */
#define PMU_FLAG_VUVDF1                 PMU_REGIDX_BIT(PMU_CS_OFFSET, 7)    /*!< Under voltage on VCORE detector flag after digital filter */
#define PMU_FLAG_BKPVSRF                PMU_REGIDX_BIT(PMU_CTL1_OFFSET, 16) /*!< Bandgap Voltage Reference ready */
#define PMU_FLAG_VBATLF                 PMU_REGIDX_BIT(PMU_CTL1_OFFSET, 20) /*!< VBAT level monitoring versus low threshold */
#define PMU_FLAG_VBATHF                 PMU_REGIDX_BIT(PMU_CTL1_OFFSET, 21) /*!< VBAT level monitoring versus high threshold */
#define PMU_FLAG_TEMPLF                 PMU_REGIDX_BIT(PMU_CTL1_OFFSET, 22) /*!< temperature level monitoring versus low threshold */
#define PMU_FLAG_TEMPHF                 PMU_REGIDX_BIT(PMU_CTL1_OFFSET, 23) /*!< temperature level monitoring versus high threshold */

/* PMU wakeup pin definitions */
#define PMU_WAKEUP_PIN0                 PMU_CS_WUPEN0                       /*!< wakeup pin 0 */
#define PMU_WAKEUP_PIN1                 PMU_CS_WUPEN1                       /*!< wakeup pin 1 */
#define PMU_WAKEUP_PIN2                 PMU_CS_WUPEN2                       /*!< wakeup pin 2 */
#define PMU_WAKEUP_PIN3                 PMU_CS_WUPEN3                       /*!< wakeup pin 3 */
#define PMU_WAKEUP_PIN4                 PMU_CS_WUPEN4                       /*!< wakeup pin 4 */

/* PMU command constants definitions */
#define WFI_CMD                         ((uint8_t)0x00U)                    /*!< use WFI command */
#define WFE_CMD                         ((uint8_t)0x01U)                    /*!< use WFE command */

/* function declarations */
/* reset PMU registers */
void pmu_deinit(void);

/* select low voltage detector threshold */
void pmu_lvd_select(uint32_t lvdt_n);
/* enable PMU lvd */
void pmu_lvd_enable(void);
/* disable PMU lvd */
void pmu_lvd_disable(void);
/* select LDO output voltage */
void pmu_ldo_output_select(uint32_t ldo_output);
/* select PMU analog voltage detector threshold */
void pmu_avd_select(uint32_t avdt_n);
/* enable PMU analog voltage detector */
void pmu_avd_enable(void);
/* disable PMU analog voltage detector */
void pmu_avd_disable(void);
/* select PMU core over voltage detector threshold */
void pmu_ovd_select(uint32_t ovdt_n);
/* enable PMU core over voltage detector */
void pmu_ovd_enable(void);
/* disable PMU core over voltage detector */
void pmu_ovd_disable(void);
/* select PMU core under voltage detector threshold */
void pmu_uvd_select(uint32_t uvdt_n);
/* enable PMU core under voltage detector */
void pmu_uvd_enable(void);
/* disable PMU core under voltage detector */
void pmu_uvd_disable(void);
/* PMU core over voltage digital noise filter  */
void pmu_ovd_filter(uint32_t dnf);
/* PMU core under voltage digital noise filter  */
void pmu_uvd_filter(uint32_t dnf);
/* PMU deepsleep mode voltage selection */
void pmu_deepsleep_voltage(uint32_t vol);

/* PMU VBAT battery charging resistor selection */
void pmu_vbat_charging_select(uint32_t resistor);
/* enable VBAT battery charging */
void pmu_vbat_charging_enable(void);
/* disable VBAT battery charging */
void pmu_vbat_charging_disable(void);
/* VBAT and temperature monitoring enable */
void pmu_vbat_temp_moniter_enable(void);
/* VBAT and temperature monitoring disable */
void pmu_vbat_temp_moniter_disable(void);

/* set PMU mode */
/* enter sleep mode */
void pmu_to_sleepmode(uint8_t sleepmodecmd);
/* enter deepsleep mode */
void pmu_to_deepsleepmode(uint32_t lowpower, uint8_t deepsleepmodecmd);
/* enter standby mode */
void pmu_to_standbymode(void);
/* enable PMU wakeup pin */
void pmu_wakeup_pin_enable(uint32_t wakeup_pin);
/* disable PMU wakeup pin */
void pmu_wakeup_pin_disable(uint32_t wakeup_pin);

/* backup related functions */
/* enable backup domain write */
void pmu_backup_write_enable(void);
/* disable backup domain write */
void pmu_backup_write_disable(void);

/* flag functions */
/* get flag state */
FlagStatus pmu_flag_get(uint32_t flag);
/* clear flag bit */
void pmu_flag_clear(uint32_t flag_reset);

#endif /* GD32G5X3_PMU_H */
