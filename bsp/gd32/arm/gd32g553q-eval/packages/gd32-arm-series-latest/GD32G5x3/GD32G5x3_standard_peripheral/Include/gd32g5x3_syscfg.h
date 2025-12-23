/*!
    \file    GD32G5x3_syscfg.h
    \brief   definitions for the SYSCFG
    
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

#ifndef GD32G5X3_SYSCFG_H
#define GD32G5X3_SYSCFG_H

#include "gd32g5x3.h"

/* SYSCFG definitions */
#define SYSCFG                              SYSCFG_BASE                                 /*!< SYSCFG base address */

/* registers definitions */
#define SYSCFG_CFG0                         REG32(SYSCFG + 0x00000000U)                 /*!< SYSCFG configuration register 0 */
#define SYSCFG_CFG1                         REG32(SYSCFG + 0x00000004U)                 /*!< SYSCFG configuration register 1 */
#define SYSCFG_EXTISS0                      REG32(SYSCFG + 0x00000008U)                 /*!< EXTI sources selection register 0 */
#define SYSCFG_EXTISS1                      REG32(SYSCFG + 0x0000000CU)                 /*!< EXTI sources selection register 1 */
#define SYSCFG_EXTISS2                      REG32(SYSCFG + 0x00000010U)                 /*!< EXTI sources selection register 2 */
#define SYSCFG_EXTISS3                      REG32(SYSCFG + 0x00000014U)                 /*!< EXTI sources selection register 3 */
#define SYSCFG_CFG2                         REG32(SYSCFG + 0x00000018U)                 /*!< SYSCFG configuration register 2 */
#define SYSCFG_STAT                         REG32(SYSCFG + 0x0000001CU)                 /*!< SYSCFG status register */
#define SYSCFG_CFG3                         REG32(SYSCFG + 0x00000020U)                 /*!< SYSCFG configuration register 3 */
#define SYSCFG_CFG4                         REG32(SYSCFG + 0x00000024U)                 /*!< SYSCFG configuration register 4 */
#define SYSCFG_CFG5                         REG32(SYSCFG + 0x00000028U)                 /*!< SYSCFG configuration register 5 */
#define SYSCFG_TCMSRAMCS                    REG32(SYSCFG + 0x00000030U)                 /*!< SYSCFG TCMSRAM control and status register */
#define SYSCFG_TCMSRAMKEY                   REG32(SYSCFG + 0x00000034U)                 /*!< SYSCFG TCMSRAM key register */
#define SYSCFG_TCMSRAMWP                    REG32(SYSCFG + 0x00000038U)                 /*!< SYSCFG TCMSRAM write protection register */
#define SYSCFG_CPSCTL                       REG32(SYSCFG + 0x0000003CU)                 /*!< SYSCFG I/O Compensation cell control/status register */
#define SYSCFG_TIMERCISEL0                  REG32(SYSCFG + 0x00000044U)                 /*!< SYSCFG TIMER input selection register 0 */
#define SYSCFG_TIMERCISEL1                  REG32(SYSCFG + 0x00000048U)                 /*!< SYSCFG TIMER input selection register 1 */
#define SYSCFG_TIMERCISEL2                  REG32(SYSCFG + 0x0000004CU)                 /*!< SYSCFG TIMER input selection register 2 */
#define SYSCFG_TIMERCISEL3                  REG32(SYSCFG + 0x00000050U)                 /*!< SYSCFG TIMER input selection register 3 */
#define SYSCFG_TIMERCISEL4                  REG32(SYSCFG + 0x00000054U)                 /*!< SYSCFG TIMER input selection register 4 */

/* SYSCFG_CFG0 bits definitions */
#define SYSCFG_CFG0_BOOT_MODE               BITS(0,2)                                   /*!< Boot mode selection */
#define SYSCFG_CFG0_FMC_SWP                 BIT(8)                                      /*!< FMC memory mapping swap */

/* SYSCFG_CFG1 bits definitions */
#define SYSCFG_CFG1_PB6FMPEN                BIT(16)                                     /*!< I2C Fm+ mode on PB6 pin enable */
#define SYSCFG_CFG1_PB7FMPEN                BIT(17)                                     /*!< I2C Fm+ mode on PB7 pin enable */
#define SYSCFG_CFG1_PB8FMPEN                BIT(18)                                     /*!< I2C Fm+ mode on PB8 pin enable */
#define SYSCFG_CFG1_PB9FMPEN                BIT(19)                                     /*!< I2C Fm+ mode on PB9 pin enable */
#define SYSCFG_CFG1_I2C0FMPEN               BIT(20)                                     /*!< I2C0 fast mode plus enable */
#define SYSCFG_CFG1_I2C1FMPEN               BIT(21)                                     /*!< I2C1 fast mode plus enable */
#define SYSCFG_CFG1_I2C2FMPEN               BIT(22)                                     /*!< I2C2 fast mode plus enable */
#define SYSCFG_CFG1_I2C3FMPEN               BIT(23)                                     /*!< I2C3 fast mode plus enable */
#define SYSCFG_CFG1_FPUINTEN_IOPIE          BIT(26)                                     /*!< Invalid operation interrupt enable */
#define SYSCFG_CFG1_FPUINTEN_DZIE           BIT(27)                                     /*!< Divide-by-zero interrupt enable */
#define SYSCFG_CFG1_FPUINTEN_UFIE           BIT(28)                                     /*!< Underflow interrupt enable */
#define SYSCFG_CFG1_FPUINTEN_OVFIE          BIT(29)                                     /*!< Overflow interrupt enable */
#define SYSCFG_CFG1_FPUINTEN_IDIE           BIT(30)                                     /*!< Input abnormal interrupt enable */
#define SYSCFG_CFG1_FPUINTEN_IXIE           BIT(31)                                     /*!< Inexact interrupt enable */

/* SYSCFG_EXTISS0 bits definitions */
#define SYSCFG_EXTISS0_EXTI0_SS             BITS(0,3)                                   /*!< EXTI 0 configuration */
#define SYSCFG_EXTISS0_EXTI1_SS             BITS(4,7)                                   /*!< EXTI 1 configuration */
#define SYSCFG_EXTISS0_EXTI2_SS             BITS(8,11)                                  /*!< EXTI 2 configuration */
#define SYSCFG_EXTISS0_EXTI3_SS             BITS(12,15)                                 /*!< EXTI 3 configuration */

/* SYSCFG_EXTISS1 bits definitions */
#define SYSCFG_EXTISS1_EXTI4_SS             BITS(0,3)                                   /*!< EXTI 4 configuration */
#define SYSCFG_EXTISS1_EXTI5_SS             BITS(4,7)                                   /*!< EXTI 5 configuration */
#define SYSCFG_EXTISS1_EXTI6_SS             BITS(8,11)                                  /*!< EXTI 6 configuration */
#define SYSCFG_EXTISS1_EXTI7_SS             BITS(12,15)                                 /*!< EXTI 7 configuration */

/* SYSCFG_EXTISS2 bits definitions */
#define SYSCFG_EXTISS2_EXTI8_SS             BITS(0,3)                                   /*!< EXTI 8 configuration */
#define SYSCFG_EXTISS2_EXTI9_SS             BITS(4,7)                                   /*!< EXTI 9 configuration */
#define SYSCFG_EXTISS2_EXTI10_SS            BITS(8,11)                                  /*!< EXTI 10 configuration */
#define SYSCFG_EXTISS2_EXTI11_SS            BITS(12,15)                                 /*!< EXTI 11 configuration */

/* SYSCFG_EXTISS3 bits definitions */
#define SYSCFG_EXTISS3_EXTI12_SS            BITS(0,3)                                   /*!< EXTI 12 configuration */
#define SYSCFG_EXTISS3_EXTI13_SS            BITS(4,7)                                   /*!< EXTI 13 configuration */
#define SYSCFG_EXTISS3_EXTI14_SS            BITS(8,11)                                  /*!< EXTI 14 configuration */
#define SYSCFG_EXTISS3_EXTI15_SS            BITS(12,15)                                 /*!< EXTI 15 configuration */

/* SYSCFG_CFG2 bits definitions */
#define SYSCFG_CFG2_LOCKUP_LOCK             BIT(0)                                      /*!< CPU lockup (Hardfault) output enable */
#define SYSCFG_CFG2_SRAM0_ECC_LOCK          BIT(1)                                      /*!< SRAM0 ECC lockup enable */
#define SYSCFG_CFG2_LVD_LOCK                BIT(2)                                      /*!< Programmable voltage detector lockup enable */
#define SYSCFG_CFG2_FLASH_ECC_LOCK          BIT(3)                                      /*!< Flash ECC lockup enable */
#define SYSCFG_CFG2_SRAM1_ECC_LOCK          BIT(4)                                      /*!< SRAM1 ECC lockup enable */
#define SYSCFG_CFG2_TCMSRAM_ECC_LOCK        BIT(5)                                      /*!< TCMSRAM ECC lockup enable */
#define SYSCFG_CFG2_PIN_RSTMD               BIT(24)                                     /*!< Pin reset mode enable */
#define SYSCFG_CFG2_TRGSEL_RSTMD            BIT(25)                                     /*!< Trigsel reset mode enable */

/* SYSCFG_STAT bits definitions */
#define SYSCFG_STAT_SRAM0ECCMEIF            BIT(0)                                      /*!< SRAM0 multi-bits non-correction event flag */
#define SYSCFG_STAT_SRAM0ECCSEIF            BIT(1)                                      /*!< SRAM0 single bit correction event flag */
#define SYSCFG_STAT_FLASHECCIF              BIT(2)                                      /*!< Flash ECC NMI interrupt flag */
#define SYSCFG_STAT_CKMNMIIF                BIT(3)                                      /*!< HXTAL clock moniotor NMI interrupt flag */
#define SYSCFG_STAT_NMIPINIF                BIT(4)                                      /*!< Interrupt flag from NMI pin */
#define SYSCFG_STAT_SRAM1ECCMEIF            BIT(5)                                      /*!< SRAM1 multi-bits non-correction event flag */
#define SYSCFG_STAT_SRAM1ECCSEIF            BIT(6)                                      /*!< SRAM1 single bit correction event flag */
#define SYSCFG_STAT_TCMSRAMECCMEIF          BIT(7)                                      /*!< TCMSRAM multi-bits non-correction event flag */
#define SYSCFG_STAT_TCMSRAMECCSEIF          BIT(8)                                      /*!< TCMSRAM single bit correction event flag */

/* SYSCFG_CFG3 bits definitions */
#define SYSCFG_CFG3_SRAM0ECCMEIE            BIT(0)                                      /*!< SRAM0 multi-bits non-correction event enable */
#define SYSCFG_CFG3_SRAM0ECCSEIE            BIT(1)                                      /*!< SRAM0 single bit correction event enable */
#define SYSCFG_CFG3_FLASHECCIE              BIT(2)                                      /*!< Flash ECC NMI interrupt enable */
#define SYSCFG_CFG3_CKMNMIIE                BIT(3)                                      /*!< HXTAL clock moniotor NMI interrupt enable */
#define SYSCFG_CFG3_NMIPINIE                BIT(4)                                      /*!< Interrupt flag from NMI pin interrupt enable */
#define SYSCFG_CFG3_SRAM0ECCSERRBITS        BITS(10,15)                                 /*!< Which one bit has an SRAM0 ECC single-bit correctable error */
#define SYSCFG_CFG3_SRAM0ECCEADDR           BITS(17,31)                                 /*!< Faulting system address where the last SRAM0 ECC event on SRAM occurred */

/* SYSCFG_CFG4 bits definitions */
#define SYSCFG_CFG4_SRAM1ECCMEIE            BIT(0)                                      /*!< SRAM1 multi-bits non-correction event enable */
#define SYSCFG_CFG4_SRAM1ECCSEIE            BIT(1)                                      /*!< SRAM1 single bit correction event enable */
#define SYSCFG_CFG4_SRAM1ECCSERRBITS        BITS(10,15)                                 /*!< Which one bit has an SRAM1 ECC single-bit correctable error */
#define SYSCFG_CFG4_SRAM1ECCEADDR           BITS(20,31)                                 /*!< Faulting system address where the last SRAM1 ECC event on SRAM occurred */

/* SYSCFG_CFG5 bits definitions */
#define SYSCFG_CFG5_TCMSRAMECCMEIE          BIT(0)                                      /*!< TCMSRAM multi-bits non-correction event enable */
#define SYSCFG_CFG5_TCMSRAMECCSEIE          BIT(1)                                      /*!< TCMSRAM single bit correction event enable */
#define SYSCFG_CFG5_TCMSRAMECCSERRBITS      BITS(10,15)                                 /*!< TCMSRAM ECC single-bit correctable error bit number */
#define SYSCFG_CFG5_TCMSRAMECCEADDR         BITS(19,31)                                 /*!< Faulting system address where the last TCMSRAM ECC event on SRAM occurred */

/* SYSCFG_TCMSRAMCS bits definitions */
#define SYSCFG_TCMSRAMCS_TCMSRAMER          BIT(0)                                      /*!< TCMSRAM erase */
#define SYSCFG_TCMSRAMCS_TCMSRAMBSY         BIT(1)                                      /*!< TCMSRAM busy flag by erase operation */

/* SYSCFG_TCMSRAMKEY bits definition */
#define SYSCFG_TCMSRAMKEY_WP_KEY            BITS(0,7)                                   /*!< TCMSRAM write protection key */

/* SYSCFG_TCMSRAMWP bits definitions */
#define SYSCFG_TCMSRAMWP_P0WPEN             BIT(0)                                      /*!< TCMSRAM page 0 write protection enable */
#define SYSCFG_TCMSRAMWP_P1WPEN             BIT(1)                                      /*!< TCMSRAM page 1 write protection enable */
#define SYSCFG_TCMSRAMWP_P2WPEN             BIT(2)                                      /*!< TCMSRAM page 2 write protection enable */
#define SYSCFG_TCMSRAMWP_P3WPEN             BIT(3)                                      /*!< TCMSRAM page 3 write protection enable */
#define SYSCFG_TCMSRAMWP_P4WPEN             BIT(4)                                      /*!< TCMSRAM page 4 write protection enable */
#define SYSCFG_TCMSRAMWP_P5WPEN             BIT(5)                                      /*!< TCMSRAM page 5 write protection enable */
#define SYSCFG_TCMSRAMWP_P6WPEN             BIT(6)                                      /*!< TCMSRAM page 6 write protection enable */
#define SYSCFG_TCMSRAMWP_P7WPEN             BIT(7)                                      /*!< TCMSRAM page 7 write protection enable */
#define SYSCFG_TCMSRAMWP_P8WPEN             BIT(8)                                      /*!< TCMSRAM page 8 write protection enable */
#define SYSCFG_TCMSRAMWP_P9WPEN             BIT(9)                                      /*!< TCMSRAM page 9 write protection enable */
#define SYSCFG_TCMSRAMWP_P10WPEN            BIT(10)                                     /*!< TCMSRAM page 10 write protection enable */
#define SYSCFG_TCMSRAMWP_P11WPEN            BIT(11)                                     /*!< TCMSRAM page 11 write protection enable */
#define SYSCFG_TCMSRAMWP_P12WPEN            BIT(12)                                     /*!< TCMSRAM page 12 write protection enable */
#define SYSCFG_TCMSRAMWP_P13WPEN            BIT(13)                                     /*!< TCMSRAM page 13 write protection enable */
#define SYSCFG_TCMSRAMWP_P14WPEN            BIT(14)                                     /*!< TCMSRAM page 14 write protection enable */
#define SYSCFG_TCMSRAMWP_P15WPEN            BIT(15)                                     /*!< TCMSRAM page 15 write protection enable */
#define SYSCFG_TCMSRAMWP_P16WPEN            BIT(16)                                     /*!< TCMSRAM page 16 write protection enable */
#define SYSCFG_TCMSRAMWP_P17WPEN            BIT(17)                                     /*!< TCMSRAM page 17 write protection enable */
#define SYSCFG_TCMSRAMWP_P18WPEN            BIT(18)                                     /*!< TCMSRAM page 18 write protection enable */
#define SYSCFG_TCMSRAMWP_P19WPEN            BIT(19)                                     /*!< TCMSRAM page 19 write protection enable */
#define SYSCFG_TCMSRAMWP_P20WPEN            BIT(20)                                     /*!< TCMSRAM page 20 write protection enable */
#define SYSCFG_TCMSRAMWP_P21WPEN            BIT(21)                                     /*!< TCMSRAM page 21 write protection enable */
#define SYSCFG_TCMSRAMWP_P22WPEN            BIT(22)                                     /*!< TCMSRAM page 22 write protection enable */
#define SYSCFG_TCMSRAMWP_P23WPEN            BIT(23)                                     /*!< TCMSRAM page 23 write protection enable */
#define SYSCFG_TCMSRAMWP_P24WPEN            BIT(24)                                     /*!< TCMSRAM page 24 write protection enable */
#define SYSCFG_TCMSRAMWP_P25WPEN            BIT(25)                                     /*!< TCMSRAM page 25 write protection enable */
#define SYSCFG_TCMSRAMWP_P26WPEN            BIT(26)                                     /*!< TCMSRAM page 26 write protection enable */
#define SYSCFG_TCMSRAMWP_P27WPEN            BIT(27)                                     /*!< TCMSRAM page 27 write protection enable */
#define SYSCFG_TCMSRAMWP_P28WPEN            BIT(28)                                     /*!< TCMSRAM page 28 write protection enable */
#define SYSCFG_TCMSRAMWP_P29WPEN            BIT(29)                                     /*!< TCMSRAM page 29 write protection enable */
#define SYSCFG_TCMSRAMWP_P30WPEN            BIT(30)                                     /*!< TCMSRAM page 30 write protection enable */
#define SYSCFG_TCMSRAMWP_P31WPEN            BIT(31)                                     /*!< TCMSRAM page 31 write protection enable */

/* SYSCFG_CPSCTL bits definitions */
#define SYSCFG_CPSCTL_CPS_EN                BIT(0)                                      /*!< I/O compensation cell enable */
#define SYSCFG_CPSCTL_CPS_RDY               BIT(8)                                      /*!< Compensation cell ready flag */

/* SYSCFG_TIMERCISEL0 bits definitions */
#define SYSCFG_TIMER7_CI0_SEL               BITS(0,3)                                   /*!< selects TIMER7_CI0 input */
#define SYSCFG_TIMER7_CI1_SEL               BITS(4,7)                                   /*!< selects TIMER7_CI1 input */
#define SYSCFG_TIMER7_CI2_SEL               BITS(8,11)                                  /*!< selects TIMER7_CI2 input */
#define SYSCFG_TIMER7_CI3_SEL               BITS(12,15)                                 /*!< selects TIMER7_CI3 input */
#define SYSCFG_TIMER0_CI0_SEL               BITS(16,19)                                 /*!< selects TIMER0_CI0 input */
#define SYSCFG_TIMER0_CI1_SEL               BITS(20,23)                                 /*!< selects TIMER0_CI1 input */
#define SYSCFG_TIMER0_CI2_SEL               BITS(24,27)                                 /*!< selects TIMER0_CI2 input */
#define SYSCFG_TIMER0_CI3_SEL               BITS(28,31)                                 /*!< selects TIMER0_CI3 input */

/* SYSCFG_TIMERCISEL1 bits definitions */
#define SYSCFG_TIMER19_CI0_SEL              BITS(0,3)                                   /*!< selects TIMER19_CI0 input */
#define SYSCFG_TIMER19_CI1_SEL              BITS(4,7)                                   /*!< selects TIMER19_CI1 input */
#define SYSCFG_TIMER19_CI2_SEL              BITS(8,11)                                  /*!< selects TIMER19_CI2 input */
#define SYSCFG_TIMER19_CI3_SEL              BITS(12,15)                                 /*!< selects TIMER19_CI3 input */

/* SYSCFG_TIMERCISEL2 bits definitions */
#define SYSCFG_TIMER2_CI0_SEL               BITS(0,3)                                   /*!< selects TIMER2_CI0 input */
#define SYSCFG_TIMER2_CI1_SEL               BITS(4,7)                                   /*!< selects TIMER2_CI1 input */
#define SYSCFG_TIMER2_CI2_SEL               BITS(8,11)                                  /*!< selects TIMER2_CI2 input */
#define SYSCFG_TIMER2_CI3_SEL               BITS(12,15)                                 /*!< selects TIMER2_CI3 input */
#define SYSCFG_TIMER1_CI0_SEL               BITS(16,19)                                 /*!< selects TIMER1_CI0 input */
#define SYSCFG_TIMER1_CI1_SEL               BITS(20,23)                                 /*!< selects TIMER1_CI1 input */
#define SYSCFG_TIMER1_CI2_SEL               BITS(24,27)                                 /*!< selects TIMER1_CI2 input */
#define SYSCFG_TIMER1_CI3_SEL               BITS(28,31)                                 /*!< selects TIMER1_CI3 input */

/* SYSCFG_TIMERCISEL3 bits definitions */
#define SYSCFG_TIMER4_CI0_SEL               BITS(0,3)                                   /*!< selects TIMER4_CI0 input */
#define SYSCFG_TIMER4_CI1_SEL               BITS(4,7)                                   /*!< selects TIMER4_CI1 input */
#define SYSCFG_TIMER4_CI2_SEL               BITS(8,11)                                  /*!< selects TIMER4_CI2 input */
#define SYSCFG_TIMER4_CI3_SEL               BITS(12,15)                                 /*!< selects TIMER4_CI3 input */
#define SYSCFG_TIMER3_CI0_SEL               BITS(16,19)                                 /*!< selects TIMER3_CI0 input */
#define SYSCFG_TIMER3_CI1_SEL               BITS(20,23)                                 /*!< selects TIMER3_CI1 input */
#define SYSCFG_TIMER3_CI2_SEL               BITS(24,27)                                 /*!< selects TIMER3_CI2 input */
#define SYSCFG_TIMER3_CI3_SEL               BITS(28,31)                                 /*!< selects TIMER3_CI3 input */

/* SYSCFG_TIMERCISEL4 bits definitions */
#define SYSCFG_TIMER14_CI0_SEL              BITS(0,3)                                   /*!< selects TIMER14_CI0 input */
#define SYSCFG_TIMER14_CI1_SEL              BITS(4,7)                                   /*!< selects TIMER14_CI1 input */
#define SYSCFG_TIMER15_CI0_SEL              BITS(8,11)                                  /*!< selects TIMER15_CI0 input */
#define SYSCFG_TIMER16_CI0_SEL              BITS(12,15)                                 /*!< selects TIMER16_CI0 input */

/* TIMER trigger selection register */
#define SYSCFG_TIMERCFG_TSCFG0              BITS(0,4)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG1              BITS(5,9)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG2              BITS(10,14)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG3              BITS(16,20)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG4              BITS(21,25)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG5              BITS(26,30)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG6              BITS(0,4)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG7              BITS(5,9)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG8              BITS(10,14)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG9              BITS(16,20)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG10             BITS(21,25)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG11             BITS(26,30)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG12             BITS(0,4)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG13             BITS(5,9)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG14             BITS(10,14)                                 /*!< TIMER trigger selection */

/* constants definitions */
/* Flash bank mode definitions */
#define SYSCFG_FLASH_BANK0_MAPPED           ((uint8_t)0x00U)                            /*!< Flash Bank 1 mapped at 0x08000000,and Flash Bank 0 mapped at 0x08040000(depend on the specific series of bank size) */
#define SYSCFG_FLASH_BANK1_MAPPED           SYSCFG_CFG0_FMC_SWP                         /*!< Flash Bank 0 mapped at 0x08000000,and Flash Bank 1 mapped at 0x08040000(depend on the specific series of bank size) */

/* Memory mapping bootmode definitions */
#define SYSCFG_MAIN_FLASH_MEMORY            ((uint8_t)0x00U)                            /*!< Main Flash memory mapped at 0x00000000 */
#define SYSCFG_SYSTEM_FLASH_MEMORY          ((uint8_t)0x01U)                            /*!< SYSCFG Flash memory mapped at 0x00000000 */
#define SYSCFG_EXMC_MEMORY                  ((uint8_t)0x02U)                            /*!< EXMC memory mapped at 0x00000000 */
#define SYSCFG_SRAM0_MEMORY                 ((uint8_t)0x03U)                            /*!< SRAM0 mapped at 0x00000000 */
#define SYSCFG_QSPI_MEMORY                  ((uint8_t)0x04U)                            /*!< QSPI memory mapped at 0x00000000 */

/* Floating point unit interrupts enable definitions */
#define SYSCFG_FPUINT_INEXACT               SYSCFG_CFG1_FPUINTEN_IXIE                   /*!< Inexact interrupt */
#define SYSCFG_FPUINT_INPUT_ABNORMAL        SYSCFG_CFG1_FPUINTEN_IDIE                   /*!< Input abnormal interrupt */
#define SYSCFG_FPUINT_OVERFLOW              SYSCFG_CFG1_FPUINTEN_OVFIE                  /*!< Overflow interrupt */
#define SYSCFG_FPUINT_UNDERFLOW             SYSCFG_CFG1_FPUINTEN_UFIE                   /*!< Underflow interrupt */
#define SYSCFG_FPUINT_DIV0                  SYSCFG_CFG1_FPUINTEN_DZIE                   /*!< Divide-by-zero interrupt */
#define SYSCFG_FPUINT_INVALID_OPERATION     SYSCFG_CFG1_FPUINTEN_IOPIE                  /*!< Invalid operation interrupt */

/* I2Cx fast mode plus enable definitions */
#define SYSCFG_I2C0_FMP                     SYSCFG_CFG1_I2C0FMPEN                       /*!< I2C0 fast mode plus enable */
#define SYSCFG_I2C1_FMP                     SYSCFG_CFG1_I2C1FMPEN                       /*!< I2C1 fast mode plus enable */
#define SYSCFG_I2C2_FMP                     SYSCFG_CFG1_I2C2FMPEN                       /*!< I2C2 fast mode plus enable */
#define SYSCFG_I2C3_FMP                     SYSCFG_CFG1_I2C3FMPEN                       /*!< I2C3 fast mode plus enable */

/* pin high current capability definitions */
#define SYSCFG_I2C_FMP_PB6                  SYSCFG_CFG1_PB6FMPEN                        /*!< I2C Fm+ mode on PB6 pin enable */
#define SYSCFG_I2C_FMP_PB7                  SYSCFG_CFG1_PB7FMPEN                        /*!< I2C Fm+ mode on PB7 pin enable */
#define SYSCFG_I2C_FMP_PB8                  SYSCFG_CFG1_PB8FMPEN                        /*!< I2C Fm+ mode on PB8 pin enable */
#define SYSCFG_I2C_FMP_PB9                  SYSCFG_CFG1_PB9FMPEN                        /*!< I2C Fm+ mode on PB9 pin enable */

/* EXTI source select definitions */
#define EXTISS0                             ((uint8_t)0x00U)                            /*!< EXTI source select register 0 */
#define EXTISS1                             ((uint8_t)0x01U)                            /*!< EXTI source select register 1 */
#define EXTISS2                             ((uint8_t)0x02U)                            /*!< EXTI source select register 2 */
#define EXTISS3                             ((uint8_t)0x03U)                            /*!< EXTI source select register 3 */

/* EXTI source select mask bits definition */
#define EXTI_SS_MASK                        BITS(0,3)                                   /*!< EXTI source select mask */

/* EXTI source select jumping step definition */
#define EXTI_SS_JSTEP                       ((uint8_t)(0x04U))                          /*!< EXTI source select jumping step */

/* EXTI source select moving step definition */
#define EXTI_SS_MSTEP(pin)                  (EXTI_SS_JSTEP * ((pin) % EXTI_SS_JSTEP))   /*!< EXTI source select moving step */

/* EXTI source port definitions */
#define EXTI_SOURCE_GPIOA                   ((uint8_t)0x00U)                            /*!< EXTI GPIOA configuration */
#define EXTI_SOURCE_GPIOB                   ((uint8_t)0x01U)                            /*!< EXTI GPIOB configuration */
#define EXTI_SOURCE_GPIOC                   ((uint8_t)0x02U)                            /*!< EXTI GPIOC configuration */
#define EXTI_SOURCE_GPIOD                   ((uint8_t)0x03U)                            /*!< EXTI GPIOD configuration */
#define EXTI_SOURCE_GPIOE                   ((uint8_t)0x04U)                            /*!< EXTI GPIOE configuration */
#define EXTI_SOURCE_GPIOF                   ((uint8_t)0x05U)                            /*!< EXTI GPIOF configuration */
#define EXTI_SOURCE_GPIOG                   ((uint8_t)0x06U)                            /*!< EXTI GPIOG configuration */

/* EXTI source pin definitions */
#define EXTI_SOURCE_PIN0                    ((uint8_t)0x00U)                            /*!< EXTI GPIO pin0 configuration */
#define EXTI_SOURCE_PIN1                    ((uint8_t)0x01U)                            /*!< EXTI GPIO pin1 configuration */
#define EXTI_SOURCE_PIN2                    ((uint8_t)0x02U)                            /*!< EXTI GPIO pin2 configuration */
#define EXTI_SOURCE_PIN3                    ((uint8_t)0x03U)                            /*!< EXTI GPIO pin3 configuration */
#define EXTI_SOURCE_PIN4                    ((uint8_t)0x04U)                            /*!< EXTI GPIO pin4 configuration */
#define EXTI_SOURCE_PIN5                    ((uint8_t)0x05U)                            /*!< EXTI GPIO pin5 configuration */
#define EXTI_SOURCE_PIN6                    ((uint8_t)0x06U)                            /*!< EXTI GPIO pin6 configuration */
#define EXTI_SOURCE_PIN7                    ((uint8_t)0x07U)                            /*!< EXTI GPIO pin7 configuration */
#define EXTI_SOURCE_PIN8                    ((uint8_t)0x08U)                            /*!< EXTI GPIO pin8 configuration */
#define EXTI_SOURCE_PIN9                    ((uint8_t)0x09U)                            /*!< EXTI GPIO pin9 configuration */
#define EXTI_SOURCE_PIN10                   ((uint8_t)0x0AU)                            /*!< EXTI GPIO pin10 configuration */
#define EXTI_SOURCE_PIN11                   ((uint8_t)0x0BU)                            /*!< EXTI GPIO pin11 configuration */
#define EXTI_SOURCE_PIN12                   ((uint8_t)0x0CU)                            /*!< EXTI GPIO pin12 configuration */
#define EXTI_SOURCE_PIN13                   ((uint8_t)0x0DU)                            /*!< EXTI GPIO pin13 configuration */
#define EXTI_SOURCE_PIN14                   ((uint8_t)0x0EU)                            /*!< EXTI GPIO pin14 configuration */
#define EXTI_SOURCE_PIN15                   ((uint8_t)0x0FU)                            /*!< EXTI GPIO pin15 configuration */

/* pin reset mode definitions */
#define SYSCFG_PIN_NRST                     SYSCFG_CFG2_PIN_RSTMD                       /*!< GPIO pin configuration will retain state across any reset event except for the POR event */
#define SYSCFG_PIN_RST                      ((uint32_t)0x00000000U)                     /*!< GPIO pin configuration is reset when any reset event occurs */

/* Trigsel cla reset mode definitions */
#define SYSCFG_TRGSEL_CLA_NRST              SYSCFG_CFG2_TRGSEL_RSTMD                    /*!< Trigsel CLA configuration will retain state across any reset event except for the POR event */
#define SYSCFG_TRGSEL_CLA_RST               ((uint32_t)0x00000000U)                     /*!< Trigsel CLA configuration is reset when any reset event occurs */

/* define the peripheral interrupt enable bit position and its register index offset */
#define SYSCFG_REGIDX_BIT(regidx, bitpos)   (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define SYSCFG_REG_VAL(interrupt)           (REG32(SYSCFG + ((uint32_t)(interrupt) >> 6)))
#define SYSCFG_BIT_POS(val)                 ((uint32_t)(val) & 0x0000001FU)

/* register offset */
#define SYSCFG_STATUS_REG_OFFSET            ((uint32_t)0x0000001CU)                     /*!< SYSCFG status register offset */
#define SYSCFG_CFG3_REG_OFFSET              ((uint32_t)0x00000020U)                     /*!< SYSCFG CFG2 register offset */
#define SYSCFG_CFG4_REG_OFFSET              ((uint32_t)0x00000024U)                     /*!< SYSCFG CFG3 register offset */
#define SYSCFG_CFG5_REG_OFFSET              ((uint32_t)0x00000028U)                     /*!< SYSCFG CFG4 register offset */

/* peripheral interrupt */
typedef enum
{
    /* SYSCFG3 interrupt */
    SYSCFG_INT_SRAM0ECCME         = SYSCFG_REGIDX_BIT(SYSCFG_CFG3_REG_OFFSET, 0U),      /*!< SRAM0 ECC multi-bits non-correction event */
    SYSCFG_INT_SRAM0ECCSE         = SYSCFG_REGIDX_BIT(SYSCFG_CFG3_REG_OFFSET, 1U),      /*!< SRAM0 ECC single bit correction event */
    SYSCFG_INT_FLASHECC           = SYSCFG_REGIDX_BIT(SYSCFG_CFG3_REG_OFFSET, 2U),      /*!< Flash ECC NMI interrupt */
    SYSCFG_INT_CKMNMI             = SYSCFG_REGIDX_BIT(SYSCFG_CFG3_REG_OFFSET, 3U),      /*!< HXTAL clock moniotor NMI interrupt */
    SYSCFG_INT_NMIPIN             = SYSCFG_REGIDX_BIT(SYSCFG_CFG3_REG_OFFSET, 4U),      /*!< NMI pin interrupt */
    /* SYSCFG4 interrupt */
    SYSCFG_INT_SRAM1ECCME         = SYSCFG_REGIDX_BIT(SYSCFG_CFG4_REG_OFFSET, 0U),      /*!< SRAM1 ECC multi-bits non-correction event */
    SYSCFG_INT_SRAM1ECCSE         = SYSCFG_REGIDX_BIT(SYSCFG_CFG4_REG_OFFSET, 1U),      /*!< SRAM1 ECC single bit correction event */
    /* SYSCFG5 interrupt */
    SYSCFG_INT_TCMSRAMECCME       = SYSCFG_REGIDX_BIT(SYSCFG_CFG5_REG_OFFSET, 0U),      /*!< TCMSRAM ECC multi-bits non-correction event */
    SYSCFG_INT_TCMSRAMECCSE       = SYSCFG_REGIDX_BIT(SYSCFG_CFG5_REG_OFFSET, 1U)       /*!< TCMSRAM ECC single bit correction event */
}syscfg_interrupt_enum;

/* peripheral interrupt flag */
typedef enum
{
    SYSCFG_INT_FLAG_SRAM0ECCME    = SYSCFG_REGIDX_BIT(SYSCFG_STATUS_REG_OFFSET, 0U),    /*!< SRAM0 ECC multi-bits non-correction event flag */
    SYSCFG_INT_FLAG_SRAM0ECCSE    = SYSCFG_REGIDX_BIT(SYSCFG_STATUS_REG_OFFSET, 1U),    /*!< SRAM0 ECC single bit correction event flag */
    SYSCFG_INT_FLAG_FLASHECC      = SYSCFG_REGIDX_BIT(SYSCFG_STATUS_REG_OFFSET, 2U),    /*!< Flash ECC NMI interrupt flag */
    SYSCFG_INT_FLAG_CKMNMI        = SYSCFG_REGIDX_BIT(SYSCFG_STATUS_REG_OFFSET, 3U),    /*!< HXTAL clock moniotor NMI interrupt flag */
    SYSCFG_INT_FLAG_NMIPIN        = SYSCFG_REGIDX_BIT(SYSCFG_STATUS_REG_OFFSET, 4U),    /*!< NMI pin interrupt flag */
    SYSCFG_INT_FLAG_SRAM1ECCME    = SYSCFG_REGIDX_BIT(SYSCFG_STATUS_REG_OFFSET, 5U),    /*!< SRAM1 ECC multi-bits non-correction event flag */
    SYSCFG_INT_FLAG_SRAM1ECCSE    = SYSCFG_REGIDX_BIT(SYSCFG_STATUS_REG_OFFSET, 6U),    /*!< SRAM1 ECC single bit correction event flag */
    SYSCFG_INT_FLAG_TCMSRAMECCME  = SYSCFG_REGIDX_BIT(SYSCFG_STATUS_REG_OFFSET, 7U),    /*!< TCMSRAM ECC multi-bits non-correction event flag */
    SYSCFG_INT_FLAG_TCMSRAMECCSE  = SYSCFG_REGIDX_BIT(SYSCFG_STATUS_REG_OFFSET, 8U)     /*!< TCMSRAM ECC single bit correction event flag */
}syscfg_flag_enum;

/* SRAM ECC single-bit correctable error bit */
typedef enum
{
    SYSCFG_SRAM0_SERRBITS         = SYSCFG_REGIDX_BIT(SYSCFG_CFG3_REG_OFFSET, 10U),     /*!< SRAM0 ECC single-bit correctable error bit */
    SYSCFG_SRAM1_SERRBITS         = SYSCFG_REGIDX_BIT(SYSCFG_CFG4_REG_OFFSET, 10U),     /*!< SRAM1 ECC single-bit correctable error bit */
    SYSCFG_TCMSRAM_SERRBITS       = SYSCFG_REGIDX_BIT(SYSCFG_CFG5_REG_OFFSET, 10U)      /*!< TCMSRAM ECC single-bit correctable error bit */
}syscfg_sram_serrbits_enum;

/* last SRAM ECC error address */
typedef enum
{
    SYSCFG_SRAM0_ERR_ADDR         = SYSCFG_REGIDX_BIT(SYSCFG_CFG3_REG_OFFSET, 17U),     /*!< SRAM0 ECC error address */
    SYSCFG_SRAM1_ERR_ADDR         = SYSCFG_REGIDX_BIT(SYSCFG_CFG4_REG_OFFSET, 20U),     /*!< SRAM1 ECC error address */
    SYSCFG_TCMSRAM_ERR_ADDR       = SYSCFG_REGIDX_BIT(SYSCFG_CFG5_REG_OFFSET, 19U)      /*!< TCMSRAM ECC error address */
}syscfg_sram_erraddr_enum;

/* TCMSRAM write protection unlock key */
#define WP_UNLOCK_KEY0                      ((uint8_t)0xCAU)                            /*!< unlock key 0 */
#define WP_UNLOCK_KEY1                      ((uint8_t)0x53U)                            /*!< unlock key 1 */
#define WP_LOCK_KEY                         ((uint8_t)0xAAU)                            /*!< lock key */

/* I/O compensation cell enable/disable */
#define SYSCFG_IO_COMPENSATION_ENABLE       ((uint32_t)0x00000001U)                     /*!< I/O compensation cell enable */
#define SYSCFG_IO_COMPENSATION_DISABLE      ((uint32_t)0x00000000U)                     /*!< I/O compensation cell disable */

/* module lockup */
#define SYSCFG_LOCKUP_LOCKUP                SYSCFG_CFG2_LOCKUP_LOCK                     /*!< CPU lockup signal connected  */
#define SYSCFG_SRAM0_LOCKUP                 SYSCFG_CFG2_SRAM0_ECC_LOCK                  /*!< SRAM0 ECC double error signal connected */
#define SYSCFG_LVD_LOCKUP                   SYSCFG_CFG2_LVD_LOCK                        /*!< LVD signal connected */
#define SYSCFG_FLASH_LOCKUP                 SYSCFG_CFG2_FLASH_ECC_LOCK                  /*!< Flash ECC double error signal connected */
#define SYSCFG_SRAM1_LOCKUP                 SYSCFG_CFG2_SRAM1_ECC_LOCK                  /*!< SRAM1 ECC double error signal connected */
#define SYSCFG_TCMSRAM_LOCKUP               SYSCFG_CFG2_TCMSRAM_ECC_LOCK                /*!< TCMSRAM ECC double error signal connected */

/* TCMSRAM page x write protection*/
#define SYSCFG_TCMSRAM_WP_PAGE0             SYSCFG_TCMSRAMWP_P0WPEN                     /*!< TCMSRAM page 0 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE1             SYSCFG_TCMSRAMWP_P1WPEN                     /*!< TCMSRAM page 1 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE2             SYSCFG_TCMSRAMWP_P2WPEN                     /*!< TCMSRAM page 2 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE3             SYSCFG_TCMSRAMWP_P3WPEN                     /*!< TCMSRAM page 3 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE4             SYSCFG_TCMSRAMWP_P4WPEN                     /*!< TCMSRAM page 4 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE5             SYSCFG_TCMSRAMWP_P5WPEN                     /*!< TCMSRAM page 5 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE6             SYSCFG_TCMSRAMWP_P6WPEN                     /*!< TCMSRAM page 6 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE7             SYSCFG_TCMSRAMWP_P7WPEN                     /*!< TCMSRAM page 7 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE8             SYSCFG_TCMSRAMWP_P8WPEN                     /*!< TCMSRAM page 8 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE9             SYSCFG_TCMSRAMWP_P9WPEN                     /*!< TCMSRAM page 9 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE10            SYSCFG_TCMSRAMWP_P10WPEN                    /*!< TCMSRAM page 10 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE11            SYSCFG_TCMSRAMWP_P11WPEN                    /*!< TCMSRAM page 11 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE12            SYSCFG_TCMSRAMWP_P12WPEN                    /*!< TCMSRAM page 12 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE13            SYSCFG_TCMSRAMWP_P13WPEN                    /*!< TCMSRAM page 13 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE14            SYSCFG_TCMSRAMWP_P14WPEN                    /*!< TCMSRAM page 14 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE15            SYSCFG_TCMSRAMWP_P15WPEN                    /*!< TCMSRAM page 15 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE16            SYSCFG_TCMSRAMWP_P16WPEN                    /*!< TCMSRAM page 16 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE17            SYSCFG_TCMSRAMWP_P17WPEN                    /*!< TCMSRAM page 17 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE18            SYSCFG_TCMSRAMWP_P18WPEN                    /*!< TCMSRAM page 18 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE19            SYSCFG_TCMSRAMWP_P19WPEN                    /*!< TCMSRAM page 19 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE20            SYSCFG_TCMSRAMWP_P20WPEN                    /*!< TCMSRAM page 20 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE21            SYSCFG_TCMSRAMWP_P21WPEN                    /*!< TCMSRAM page 21 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE22            SYSCFG_TCMSRAMWP_P22WPEN                    /*!< TCMSRAM page 22 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE23            SYSCFG_TCMSRAMWP_P23WPEN                    /*!< TCMSRAM page 23 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE24            SYSCFG_TCMSRAMWP_P24WPEN                    /*!< TCMSRAM page 24 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE25            SYSCFG_TCMSRAMWP_P25WPEN                    /*!< TCMSRAM page 25 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE26            SYSCFG_TCMSRAMWP_P26WPEN                    /*!< TCMSRAM page 26 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE27            SYSCFG_TCMSRAMWP_P27WPEN                    /*!< TCMSRAM page 27 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE28            SYSCFG_TCMSRAMWP_P28WPEN                    /*!< TCMSRAM page 28 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE29            SYSCFG_TCMSRAMWP_P29WPEN                    /*!< TCMSRAM page 29 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE30            SYSCFG_TCMSRAMWP_P30WPEN                    /*!< TCMSRAM page 30 write protection enable */
#define SYSCFG_TCMSRAM_WP_PAGE31            SYSCFG_TCMSRAMWP_P31WPEN                    /*!< TCMSRAM page 31 write protection enable */

/* TIMER input select mask bits definition */
#define TIMER_IS_MASK                       BITS(0,3)                                   /*!< TIMER source select mask */

/* TIMER input select definitions */
#define TIMERCISEL0                         ((uint8_t)0x00U)                            /*!< TIMER input select register 0 */
#define TIMERCISEL1                         ((uint8_t)0x01U)                            /*!< TIMER input select register 1 */
#define TIMERCISEL2                         ((uint8_t)0x02U)                            /*!< TIMER input select register 2 */
#define TIMERCISEL3                         ((uint8_t)0x03U)                            /*!< TIMER input select register 3 */
#define TIMERCISEL4                         ((uint8_t)0x04U)                            /*!< TIMER input select register 4 */

/* define the TIMER bit position and its register index offset */
#define TIMER_REGIDX_BIT(regidx, bitpos, value)   (((uint32_t)(regidx) << 24U) | (uint32_t)((bitpos) << 16U)\
        | ((uint32_t)(value)))
#define TIMER_REG_INDEX(val)                (((uint32_t)(val) & 0xFF000000U) >> 24U)
#define TIMER_BIT_POS(val)                  (((uint32_t)(val) & 0x00FF0000U) >> 16U)
#define TIMER_SEL_VAL(val)                  ((uint32_t)(val) & 0x000000FFU)

/* TIMERx channel input Select definitions */
typedef enum {
    TIMER7_CI0_INPUT_TIMER7_CH0         = TIMER_REGIDX_BIT(TIMERCISEL0, 0U, 0U),        /*!< select TIMER7 CH0 as TIMER7 CI0 */
    TIMER7_CI0_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 0U, 1U),        /*!< select CMP0 output as TIMER7 CI0 */
    TIMER7_CI0_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 0U, 2U),        /*!< select CMP1 output as TIMER7 CI0 */
    TIMER7_CI0_INPUT_CMP2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 0U, 3U),        /*!< select CMP2 output as TIMER7 CI0 */
    TIMER7_CI0_INPUT_CMP3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 0U, 4U),        /*!< select CMP3 output as TIMER7 CI0 */
    TIMER7_CI0_INPUT_CLA0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 0U, 5U),        /*!< select CLA0 output as TIMER7 CI0 */
    TIMER7_CI1_INPUT_TIMER7_CH1         = TIMER_REGIDX_BIT(TIMERCISEL0, 4U, 0U),        /*!< select TIMER7 CH1 as TIMER7 CI1 */
    TIMER7_CI1_INPUT_CLA1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 4U, 1U),        /*!< select CLA1 output as TIMER7 CI1 */
    TIMER7_CI2_INPUT_TIMER7_CH2         = TIMER_REGIDX_BIT(TIMERCISEL0, 8U, 0U),        /*!< select TIMER7 CH2 as TIMER7 CI2 */
    TIMER7_CI2_INPUT_CLA2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 8U, 1U),        /*!< select CLA2 output as TIMER7 CI2 */
    TIMER7_CI3_INPUT_TIMER7_CH3         = TIMER_REGIDX_BIT(TIMERCISEL0, 12U, 0U),       /*!< select TIMER7 CH3 as TIMER7 CI3 */
    TIMER7_CI3_INPUT_CLA3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 12U, 1U),       /*!< select CLA3 output as TIMER7 CI3 */
    TIMER0_CI0_INPUT_TIMER0_CH0         = TIMER_REGIDX_BIT(TIMERCISEL0, 16U, 0U),       /*!< select TIMER0 CH0 as TIMER0 CI0 */
    TIMER0_CI0_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 16U, 1U),       /*!< select CMP0 output as TIMER0 CI0 */
    TIMER0_CI0_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 16U, 2U),       /*!< select CMP1 output as TIMER0 CI0 */
    TIMER0_CI0_INPUT_CMP2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 16U, 3U),       /*!< select CMP2 output as TIMER0 CI0 */
    TIMER0_CI0_INPUT_CMP3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 16U, 4U),       /*!< select CMP3 output as TIMER0 CI0 */
    TIMER0_CI0_INPUT_CLA0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 16U, 5U),       /*!< select CLA0 output as TIMER0 CI0 */
    TIMER0_CI1_INPUT_TIMER0_CH1         = TIMER_REGIDX_BIT(TIMERCISEL0, 20U, 0U),       /*!< select TIMER0 CH1 as TIMER0 CI1 */
    TIMER0_CI1_INPUT_CLA1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 20U, 1U),       /*!< select CLA1 output as TIMER0 CI1 */
    TIMER0_CI2_INPUT_TIMER0_CH2         = TIMER_REGIDX_BIT(TIMERCISEL0, 24U, 0U),       /*!< select TIMER0 CH2 as TIMER0 CI2 */
    TIMER0_CI2_INPUT_CLA2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 24U, 1U),       /*!< select CLA2 output as TIMER0 CI2 */
    TIMER0_CI3_INPUT_TIMER0_CH3         = TIMER_REGIDX_BIT(TIMERCISEL0, 28U, 0U),       /*!< select TIMER0 CH3 as TIMER0 CI3 */
    TIMER0_CI3_INPUT_CLA3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 28U, 1U),       /*!< select CLA3 output as TIMER0 CI3 */
    TIMER19_CI0_INPUT_TIMER19_CH0        = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 0U),       /*!< select TIMER19 CH0 as TIMER19 CI0 */
    TIMER19_CI0_INPUT_CMP0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 1U),        /*!< select CMP0 output as TIMER19 CI0 */
    TIMER19_CI0_INPUT_CMP1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 2U),        /*!< select CMP1 output as TIMER19 CI0 */
    TIMER19_CI0_INPUT_CMP2_OUT          = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 3U),        /*!< select CMP2 output as TIMER19 CI0 */
    TIMER19_CI0_INPUT_CMP3_OUT          = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 4U),        /*!< select CMP3 output as TIMER19 CI0 */
    TIMER19_CI0_INPUT_CLA0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 5U),        /*!< select CLA0 output as TIMER19 CI0 */
    TIMER19_CI1_INPUT_TIMER19_CH1        = TIMER_REGIDX_BIT(TIMERCISEL1, 4U, 0U),       /*!< select TIMER19 CH1 as TIMER19 CI1 */
    TIMER19_CI1_INPUT_CLA1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL1, 4U, 1U),        /*!< select CLA1 output as TIMER19 CI1 */
    TIMER19_CI2_INPUT_TIMER19_CH2        = TIMER_REGIDX_BIT(TIMERCISEL1, 8U, 0U),       /*!< select TIMER19 CH2 as TIMER19 CI2 */
    TIMER19_CI2_INPUT_CLA2_OUT          = TIMER_REGIDX_BIT(TIMERCISEL1, 8U, 1U),        /*!< select CLA2 output as TIMER19 CI2 */
    TIMER19_CI3_INPUT_TIMER19_CH3        = TIMER_REGIDX_BIT(TIMERCISEL1, 12U, 0U),      /*!< select TIMER19 CH3 as TIMER19 CI3 */
    TIMER19_CI3_INPUT_CLA3_OUT          = TIMER_REGIDX_BIT(TIMERCISEL1, 12U, 1U),       /*!< select CLA3 output as TIMER19 CI3 */
    TIMER2_CI0_INPUT_TIMER2_CH0         = TIMER_REGIDX_BIT(TIMERCISEL2, 0U, 0U),        /*!< select TIMER2 CH0 as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 0U, 1U),        /*!< select CMP0 output as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 0U, 2U),        /*!< select CMP1 output as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 0U, 3U),        /*!< select CMP2 output as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 0U, 4U),        /*!< select CMP3 output as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP4_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 0U, 5U),        /*!< select CMP4 output as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP5_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 0U, 6U),        /*!< select CMP5 output as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP6_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 0U, 7U),        /*!< select CMP6 output as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CLA0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 0U, 8U),        /*!< select CLA0 output as TIMER2 CI0 */
    TIMER2_CI1_INPUT_TIMER2_CH1         = TIMER_REGIDX_BIT(TIMERCISEL2, 4U, 0U),        /*!< select TIMER2 CH1 as TIMER2 CI1 */
    TIMER2_CI1_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 4U, 1U),        /*!< select CMP0 output as TIMER2 CI1 */
    TIMER2_CI1_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 4U, 2U),        /*!< select CMP1 output as TIMER2 CI1 */
    TIMER2_CI1_INPUT_CMP2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 4U, 3U),        /*!< select CMP2 output as TIMER2 CI1 */
    TIMER2_CI1_INPUT_CMP3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 4U, 4U),        /*!< select CMP3 output as TIMER2 CI1 */
    TIMER2_CI1_INPUT_CMP4_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 4U, 5U),        /*!< select CMP4 output as TIMER2 CI1 */
    TIMER2_CI1_INPUT_CMP5_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 4U, 6U),        /*!< select CMP5 output as TIMER2 CI1 */
    TIMER2_CI1_INPUT_CMP6_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 4U, 7U),        /*!< select CMP6 output as TIMER2 CI1 */
    TIMER2_CI1_INPUT_CLA1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 4U, 8U),        /*!< select CLA1 output as TIMER2 CI1 */
    TIMER2_CI2_INPUT_TIMER2_CH2         = TIMER_REGIDX_BIT(TIMERCISEL2, 8U, 0U),        /*!< select TIMER2 CH2 as TIMER2 CI2 */
    TIMER2_CI2_INPUT_CMP2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 8U, 1U),        /*!< select CMP2 output as TIMER2 CI2 */
    TIMER2_CI2_INPUT_CLA2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 8U, 2U),        /*!< select CLA2 output as TIMER2 CI2 */
    TIMER2_CI3_INPUT_TIMER2_CH3         = TIMER_REGIDX_BIT(TIMERCISEL2, 12U, 0U),       /*!< select TIMER2 CH3 as TIMER2 CI3 */
    TIMER2_CI3_INPUT_CLA3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 12U, 1U),       /*!< select CLA3 output as TIMER2 CI3 */
    TIMER1_CI0_INPUT_TIMER1_CH0         = TIMER_REGIDX_BIT(TIMERCISEL2, 16U, 0U),       /*!< select TIMER1 CH0 as TIMER1 CI0 */
    TIMER1_CI0_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 16U, 1U),       /*!< select CMP0 output as TIMER1 CI0 */
    TIMER1_CI0_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 16U, 2U),       /*!< select CMP1 output as TIMER1 CI0 */
    TIMER1_CI0_INPUT_CMP2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 16U, 3U),       /*!< select CMP2 output as TIMER1 CI0 */
    TIMER1_CI0_INPUT_CMP3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 16U, 4U),       /*!< select CMP3 output as TIMER1 CI0 */
    TIMER1_CI0_INPUT_CMP4_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 16U, 5U),       /*!< select CMP4 output as TIMER1 CI0 */
    TIMER1_CI0_INPUT_CLA0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 16U, 6U),       /*!< select CLA0 output as TIMER1 CI0 */
    TIMER1_CI1_INPUT_TIMER1_CH1         = TIMER_REGIDX_BIT(TIMERCISEL2, 20U, 0U),       /*!< select TIMER1 CH1 as TIMER1 CI1 */
    TIMER1_CI1_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 20U, 1U),       /*!< select CMP0 output as TIMER1 CI1 */
    TIMER1_CI1_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 20U, 2U),       /*!< select CMP1 output as TIMER1 CI1 */
    TIMER1_CI1_INPUT_CMP2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 20U, 3U),       /*!< select CMP2 output as TIMER1 CI1 */
    TIMER1_CI1_INPUT_CMP3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 20U, 4U),       /*!< select CMP3 output as TIMER1 CI1 */
    TIMER1_CI1_INPUT_CMP5_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 20U, 5U),       /*!< select CMP5 output as TIMER1 CI1 */
    TIMER1_CI1_INPUT_CLA1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 20U, 6U),       /*!< select CLA1 output as TIMER1 CI1 */
    TIMER1_CI2_INPUT_TIMER1_CH2         = TIMER_REGIDX_BIT(TIMERCISEL2, 24U, 0U),       /*!< select TIMER1 CH2 as TIMER1 CI2 */
    TIMER1_CI2_INPUT_CMP3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 24U, 1U),       /*!< select CMP3 output as TIMER1 CI2 */
    TIMER1_CI2_INPUT_CLA2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 24U, 2U),       /*!< select CLA2 output as TIMER1 CI2 */
    TIMER1_CI3_INPUT_TIMER1_CH3         = TIMER_REGIDX_BIT(TIMERCISEL2, 28U, 0U),       /*!< select TIMER1 CH3 as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 28U, 1U),       /*!< select CMP0 output as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 28U, 2U),       /*!< select CMP1 output as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CLA3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL2, 28U, 3U),       /*!< select CLA3 output as TIMER1 CI3 */
    TIMER4_CI0_INPUT_TIMER4_CH0         = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 0U),        /*!< select TIMER4 CH0 as TIMER4 CI0 */
    TIMER4_CI0_INPUT_IRC32K             = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 1U),        /*!< select IRC32K output as TIMER4 CI0 */
    TIMER4_CI0_INPUT_LXTAL              = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 2U),        /*!< select LXTAL output as TIMER4 CI0 */
    TIMER4_CI0_INPUT_RTC_WAKEUP         = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 3U),        /*!< select RTC_WAKEUP output as TIMER4 CI0 */
    TIMER4_CI0_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 4U),        /*!< select CMP0 output as TIMER4 CI0 */
    TIMER4_CI0_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 5U),        /*!< select CMP1 output as TIMER4 CI0 */
    TIMER4_CI0_INPUT_CMP2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 6U),        /*!< select CMP2 output as TIMER4 CI0 */
    TIMER4_CI0_INPUT_CMP3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 7U),        /*!< select CMP3 output as TIMER4 CI0 */
    TIMER4_CI0_INPUT_CMP4_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 8U),        /*!< select CMP4 output as TIMER4 CI0 */
    TIMER4_CI0_INPUT_CMP5_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 9U),        /*!< select CMP5 output as TIMER4 CI0 */
    TIMER4_CI0_INPUT_CMP6_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 10U),       /*!< select CMP6 output as TIMER4 CI0 */
    TIMER4_CI0_INPUT_CLA0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 0U, 11U),       /*!< select CLA0 output as TIMER4 CI0 */
    TIMER4_CI1_INPUT_TIMER4_CH1         = TIMER_REGIDX_BIT(TIMERCISEL3, 4U, 0U),        /*!< select TIMER4 CH1 as TIMER4 CI1 */
    TIMER4_CI1_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 4U, 1U),        /*!< select CMP0 output as TIMER4 CI1 */
    TIMER4_CI1_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 4U, 2U),        /*!< select CMP1 output as TIMER4 CI1 */
    TIMER4_CI1_INPUT_CMP2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 4U, 3U),        /*!< select CMP2 output as TIMER4 CI1 */
    TIMER4_CI1_INPUT_CMP3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 4U, 4U),        /*!< select CMP3 output as TIMER4 CI1 */
    TIMER4_CI1_INPUT_CMP4_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 4U, 5U),        /*!< select CMP4 output as TIMER4 CI1 */
    TIMER4_CI1_INPUT_CMP5_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 4U, 6U),        /*!< select CMP5 output as TIMER4 CI1 */
    TIMER4_CI1_INPUT_CMP6_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 4U, 7U),        /*!< select CMP6 output as TIMER4 CI1 */
    TIMER4_CI1_INPUT_CLA1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 4U, 8U),        /*!< select CLA1 output as TIMER4 CI1 */
    TIMER4_CI2_INPUT_TIMER4_CH2         = TIMER_REGIDX_BIT(TIMERCISEL3, 8U, 0U),        /*!< select TIMER4 CH2 as TIMER4 CI2 */
    TIMER4_CI2_INPUT_CLA2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 8U, 1U),        /*!< select CLA2 output as TIMER4 CI2 */
    TIMER4_CI3_INPUT_TIMER4_CH3         = TIMER_REGIDX_BIT(TIMERCISEL3, 12U, 0U),       /*!< select TIMER4 CH3 as TIMER4 CI3 */
    TIMER4_CI3_INPUT_CLA3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 12U, 1U),       /*!< select CLA3 output as TIMER4 CI3 */
    TIMER3_CI0_INPUT_TIMER3_CH0         = TIMER_REGIDX_BIT(TIMERCISEL3, 16U, 0U),       /*!< select TIMER3 CH0 as TIMER3 CI0 */
    TIMER3_CI0_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 16U, 1U),       /*!< select CMP0 output as TIMER3 CI0 */
    TIMER3_CI0_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 16U, 2U),       /*!< select CMP1 output as TIMER3 CI0 */
    TIMER3_CI0_INPUT_CMP2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 16U, 3U),       /*!< select CMP2 output as TIMER3 CI0 */
    TIMER3_CI0_INPUT_CMP3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 16U, 4U),       /*!< select CMP3 output as TIMER3 CI0 */
    TIMER3_CI0_INPUT_CMP4_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 16U, 5U),       /*!< select CMP4 output as TIMER3 CI0 */
    TIMER3_CI0_INPUT_CMP5_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 16U, 6U),       /*!< select CMP5 output as TIMER3 CI0 */
    TIMER3_CI0_INPUT_CMP6_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 16U, 7U),       /*!< select CMP6 output as TIMER3 CI0 */
    TIMER3_CI0_INPUT_CLA0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 16U, 8U),       /*!< select CLA0 output as TIMER3 CI0 */
    TIMER3_CI1_INPUT_TIMER3_CH1         = TIMER_REGIDX_BIT(TIMERCISEL3, 20U, 0U),       /*!< select TIMER3 CH1 as TIMER3 CI1 */
    TIMER3_CI1_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 20U, 1U),       /*!< select CMP0 output as TIMER3 CI1 */
    TIMER3_CI1_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 20U, 2U),       /*!< select CMP1 output as TIMER3 CI1 */
    TIMER3_CI1_INPUT_CMP2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 20U, 3U),       /*!< select CMP2 output as TIMER3 CI1 */
    TIMER3_CI1_INPUT_CMP3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 20U, 4U),       /*!< select CMP3 output as TIMER3 CI1 */
    TIMER3_CI1_INPUT_CMP4_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 20U, 5U),       /*!< select CMP4 output as TIMER3 CI1 */
    TIMER3_CI1_INPUT_CMP5_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 20U, 6U),       /*!< select CMP5 output as TIMER3 CI1 */
    TIMER3_CI1_INPUT_CMP6_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 20U, 7U),       /*!< select CMP6 output as TIMER3 CI1 */
    TIMER3_CI1_INPUT_CLA1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 20U, 8U),       /*!< select CLA1 output as TIMER3 CI1 */
    TIMER3_CI2_INPUT_TIMER3_CH2         = TIMER_REGIDX_BIT(TIMERCISEL3, 24U, 0U),       /*!< select TIMER3 CH2 as TIMER3 CI2 */
    TIMER3_CI2_INPUT_CMP4_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 24U, 1U),       /*!< select CMP4 output as TIMER3 CI1 */
    TIMER3_CI2_INPUT_CLA2_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 24U, 2U),       /*!< select CLA2 output as TIMER3 CI2 */
    TIMER3_CI3_INPUT_TIMER3_CH3         = TIMER_REGIDX_BIT(TIMERCISEL3, 28U, 0U),       /*!< select TIMER3 CH3 as TIMER3 CI3 */
    TIMER3_CI3_INPUT_CMP5_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 28U, 1U),       /*!< select CMP5 output as TIMER3 CI3 */
    TIMER3_CI3_INPUT_CLA3_OUT           = TIMER_REGIDX_BIT(TIMERCISEL3, 28U, 2U),       /*!< select CLA3 output as TIMER3 CI3 */
    TIMER14_CI0_INPUT_TIMER14_CH0       = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 0U),        /*!< select TIMER14 CH0 as TIMER14 CI0 */
    TIMER14_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 1U),        /*!< select LXTAL as TIMER14 CI0 */
    TIMER14_CI0_INPUT_CMP0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 2U),        /*!< select CMP0 output as TIMER14 CI0 */
    TIMER14_CI0_INPUT_CMP1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 3U),        /*!< select CMP1 output as TIMER14 CI0 */
    TIMER14_CI0_INPUT_CMP4_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 4U),        /*!< select CMP4 output as TIMER14 CI0 */
    TIMER14_CI0_INPUT_CMP6_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 5U),        /*!< select CMP6 output as TIMER14 CI0 */
    TIMER14_CI0_INPUT_CLA0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 6U),        /*!< select CLA0 output as TIMER14 CI0 */
    TIMER14_CI0_INPUT_CLA1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 7U),        /*!< select CLA1 output as TIMER14 CI0 */
    TIMER14_CI0_INPUT_CLA2_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 8U),        /*!< select CLA2 output as TIMER14 CI0 */
    TIMER14_CI0_INPUT_CLA3_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 9U),        /*!< select CLA3 output as TIMER14 CI0 */
    TIMER14_CI1_INPUT_TIMER31_CH1       = TIMER_REGIDX_BIT(TIMERCISEL4, 4U, 0U),        /*!< select TIMER14 CH1 as TIMER14 CI1 */
    TIMER14_CI1_INPUT_CMP1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 4U, 1U),        /*!< select CMP1 output as TIMER14 CI1 */
    TIMER14_CI1_INPUT_CMP2_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 4U, 2U),        /*!< select CMP2 output as TIMER14 CI1 */
    TIMER14_CI1_INPUT_CMP5_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 4U, 3U),        /*!< select CMP5 output as TIMER14 CI1 */
    TIMER14_CI1_INPUT_CMP6_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 4U, 4U),        /*!< select CMP6 output as TIMER14 CI1 */
    TIMER15_CI0_INPUT_TIMER15_CH0       = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 0U),        /*!< select TIMER15 CH0 as TIMER15 CI0 */
    TIMER15_CI0_INPUT_CMP5_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 1U),        /*!< select CMP5 output as TIMER15 CI0 */
    TIMER15_CI0_INPUT_CKOUT             = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 2U),        /*!< select CKOUT as TIMER15 CI0 */
    TIMER15_CI0_INPUT_HXTAL_DIV32       = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 3U),        /*!< select HXTAL/32 as TIMER15 CI0 */
    TIMER15_CI0_INPUT_RTC_CLOCK         = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 4U),        /*!< select RTC Clock as TIMER15 CI0 */
    TIMER15_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 5U),        /*!< select LXATL as TIMER15 CI0 */
    TIMER15_CI0_INPUT_IRC32K            = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 6U),        /*!< select IARC32K as TIMER15 CI0 */
    TIMER15_CI0_INPUT_CLA0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 7U),        /*!< select CLA0 output as TIMER15 CI0 */
    TIMER15_CI0_INPUT_CLA1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 8U),        /*!< select CLA1 output as TIMER15 CI0 */
    TIMER15_CI0_INPUT_CLA2_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 9U),        /*!< select CLA2 output as TIMER15 CI0 */
    TIMER15_CI0_INPUT_CLA3_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 10U),       /*!< select CLA3 output as TIMER15 CI0 */
    TIMER15_CI0_INPUT_HXTAL             = TIMER_REGIDX_BIT(TIMERCISEL4, 8U, 11U),       /*!< select HXTAL as TIMER15 CI0 */
    TIMER16_CI0_INPUT_TIMER16_CH0       = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 0U),       /*!< select TIMER16 CH0 as TIMER16 CI0 */
    TIMER16_CI0_INPUT_CMP4_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 1U),       /*!< select CMP5 output as TIMER16 CI0 */
    TIMER16_CI0_INPUT_CKOUT             = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 2U),       /*!< select clock output as TIMER16 CI0 */
    TIMER16_CI0_INPUT_HXTAL_DIV32       = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 3U),       /*!< select HXTAL/32 as TIMER16 CI0 */
    TIMER16_CI0_INPUT_RTC_CLOCK         = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 4U),       /*!< select RTC Clock as TIMER16 CI0 */
    TIMER16_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 5U),       /*!< select LXTAL as TIMER16 CI0 */
    TIMER16_CI0_INPUT_IRC32K            = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 6U),       /*!< select IRC32K as TIMER16 CI0 */
    TIMER16_CI0_INPUT_CLA0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 7U),       /*!< select CLA0 output as TIMER16 CI0 */
    TIMER16_CI0_INPUT_CLA1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 8U),       /*!< select CLA1 output as TIMER16 CI0 */
    TIMER16_CI0_INPUT_CLA2_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 9U),       /*!< select CLA2 output as TIMER16 CI0 */
    TIMER16_CI0_INPUT_CLA3_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 10U),      /*!< select CLA3 output as TIMER16 CI0 */
    TIMER16_CI0_INPUT_HXTAL             = TIMER_REGIDX_BIT(TIMERCISEL4, 12U, 11U)       /*!< select HXTAL as TIMER16 CI0 */
} timer_channel_input_enum;

/* timer tigger source select definition */
#define TIMER_SMCFG_TRGSEL_NONE             ((uint8_t)0x00U)                            /*!< trigger input is none */
#define TIMER_SMCFG_TRGSEL_ITI0             ((uint8_t)0x01U)                            /*!< internal trigger input 0 */
#define TIMER_SMCFG_TRGSEL_ITI1             ((uint8_t)0x02U)                            /*!< internal trigger input 1 */
#define TIMER_SMCFG_TRGSEL_ITI2             ((uint8_t)0x03U)                            /*!< internal trigger input 2 */
#define TIMER_SMCFG_TRGSEL_ITI3             ((uint8_t)0x04U)                            /*!< internal trigger input 3 */
#define TIMER_SMCFG_TRGSEL_CI0F_ED          ((uint8_t)0x05U)                            /*!< TI0 edge detector */
#define TIMER_SMCFG_TRGSEL_CI0FE0           ((uint8_t)0x06U)                            /*!< filtered TIMER input 0 */
#define TIMER_SMCFG_TRGSEL_CI1FE1           ((uint8_t)0x07U)                            /*!< filtered TIMER input 1 */
#define TIMER_SMCFG_TRGSEL_ETIFP            ((uint8_t)0x08U)                            /*!< external trigger */
#define TIMER_SMCFG_TRGSEL_ITI4             ((uint8_t)0x09U)                            /*!< internal trigger input 4 */
#define TIMER_SMCFG_TRGSEL_ITI5             ((uint8_t)0x0AU)                            /*!< internal trigger input 5 */
#define TIMER_SMCFG_TRGSEL_ITI6             ((uint8_t)0x0BU)                            /*!< internal trigger input 6 */
#define TIMER_SMCFG_TRGSEL_ITI7             ((uint8_t)0x0CU)                            /*!< internal trigger input 7 */
#define TIMER_SMCFG_TRGSEL_ITI8             ((uint8_t)0x0DU)                            /*!< internal trigger input 8 */
#define TIMER_SMCFG_TRGSEL_ITI9             ((uint8_t)0x0EU)                            /*!< internal trigger input 9 */
#define TIMER_SMCFG_TRGSEL_ITI10            ((uint8_t)0x0FU)                            /*!< internal trigger input 10 */
#define TIMER_SMCFG_TRGSEL_ITI14            ((uint8_t)0x13U)                            /*!< internal trigger input 14 */

/* timer tigger mode select definition */
#define TIMER_QUAD_DECODER_MODE0            ((uint8_t)0x00U)                            /*!< quadrature decoder mode 0 */
#define TIMER_QUAD_DECODER_MODE1            ((uint8_t)0x01U)                            /*!< quadrature decoder mode 1 */
#define TIMER_QUAD_DECODER_MODE2            ((uint8_t)0x02U)                            /*!< quadrature decoder mode 2 */
#define TIMER_SLAVE_MODE_RESTART            ((uint8_t)0x03U)                            /*!< restart mode */
#define TIMER_SLAVE_MODE_PAUSE              ((uint8_t)0x04U)                            /*!< pause mode */
#define TIMER_SLAVE_MODE_EVENT              ((uint8_t)0x05U)                            /*!< event mode */
#define TIMER_SLAVE_MODE_EXTERNAL0          ((uint8_t)0x06U)                            /*!< external clock mode 0 */
#define TIMER_SLAVE_MODE_RESTART_EVENT      ((uint8_t)0x07U)                            /*!< restart + event mode */
#define TIMER_SLAVE_MODE_RESTART_PAUSE      ((uint8_t)0x08U)                            /*!< restart + pause mode */
#define TIMER_DECODER_MODE0                 ((uint8_t)0x09U)                            /*!< decoder mode 0 */
#define TIMER_DECODER_MODE1                 ((uint8_t)0x0AU)                            /*!< decoder mode 1 */
#define TIMER_DECODER_MODE2                 ((uint8_t)0x0BU)                            /*!< decoder mode 2 */
#define TIMER_DECODER_MODE3                 ((uint8_t)0x0CU)                            /*!< decoder mode 3 */
#define TIMER_QUAD_DECODER_MODE3            ((uint8_t)0x0DU)                            /*!< quadrature decoder mode 3 */
#define TIMER_QUAD_DECODER_MODE4            ((uint8_t)0x0EU)                            /*!< quadrature decoder mode 4 */
#define TIMER_SLAVE_MODE_DISABLE            ((uint8_t)0x0FU)                            /*!< slave mode disable */

#define SYSCFG_TIMERCFG0(syscfg_timerx)     REG32(SYSCFG + 0x100U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */
#define SYSCFG_TIMERCFG1(syscfg_timerx)     REG32(SYSCFG + 0x104U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */
#define SYSCFG_TIMERCFG2(syscfg_timerx)     REG32(SYSCFG + 0x108U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */

#define SYSCFG_TIMERCFG(syscfg_timerx)      ((uint32_t)(SYSCFG_BASE + 0x100U + (syscfg_timerx) * 0x0CU))

#define SYSCFG_TIMER0                       ((uint8_t)0x00U)                            /*!< SYSCFG TIMER0 */
#define SYSCFG_TIMER1                       ((uint8_t)0x01U)                            /*!< SYSCFG TIMER1 */
#define SYSCFG_TIMER2                       ((uint8_t)0x02U)                            /*!< SYSCFG TIMER2 */
#define SYSCFG_TIMER3                       ((uint8_t)0x03U)                            /*!< SYSCFG TIMER3 */
#define SYSCFG_TIMER4                       ((uint8_t)0x04U)                            /*!< SYSCFG TIMER4 */
#define SYSCFG_TIMER7                       ((uint8_t)0x05U)                            /*!< SYSCFG TIMER5 */
#define SYSCFG_TIMER14                      ((uint8_t)0x06U)                            /*!< SYSCFG TIMER6 */
#define SYSCFG_TIMER19                      ((uint8_t)0x07U)                            /*!< SYSCFG TIMER7 */

/* function declarations */
/* initialization functions */
/* reset the SYSCFG registers */
void syscfg_deinit(void);
/* enable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9) */
void syscfg_i2c_fast_mode_plus_enable(uint32_t i2c_fmp_enable);
/* disable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9) */
void syscfg_i2c_fast_mode_plus_disable(uint32_t i2c_fmp_disable);
/* configure the GPIO pin as EXTI line */
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin);
/* configure GPIO reset mode */
void syscfg_pin_reset_mode_config(uint32_t syscfg_pin_reset_mode);
/* configure Trigsel CLA reset mode */
void syscfg_trigsel_cla_reset_mode_config(uint32_t syscfg_trgsel_reset_mode);
/* enable module lockup */
void syscfg_lockup_enable(uint32_t lockup);
/* select timer channel input source */
void syscfg_timer_input_source_select(timer_channel_input_enum timer_input);

/* Memory functions */
/* switch flash Bank0 and Bank1 address */
void syscfg_flash_bank_remap_set(uint32_t value);
/* select bootmode memory mapping */
void syscfg_bootmode_memmap_select(uint32_t mem_select);
/* get SRAM ECC single correctable bit */
uint32_t syscfg_sram_ecc_single_correctable_bit_get(syscfg_sram_serrbits_enum sram);
/* get SRAM ECC error address */
uint32_t syscfg_sram_ecc_error_address_get(syscfg_sram_erraddr_enum sram);
/* erase tcmsram */
void syscfg_tcmsram_erase(void);
/* lock the TCMSRAM erase */
void syscfg_tcmsram_erase_lock(void);
/* unlock the TCMSRAM erase */
void syscfg_tcmsram_erase_unlock(void);
/* enable TCMSRAM page x write protection */
void syscfg_tcmsram_page_wp_enable(uint32_t pagex);

/* I/O compensation cell functions */
/* configure the I/O compensation cell */
void syscfg_io_compensation_config(uint32_t syscfg_cps);

/* flag and interrupt functions */
/* enable FPU interrupt */
void syscfg_fpu_interrupt_enable(uint32_t interrupt);
/* disable FPU interrupt */
void syscfg_fpu_interrupt_disable(uint32_t interrupt);
/* get the interrupt flags */
FlagStatus syscfg_interrupt_flag_get(syscfg_flag_enum int_flag);
/* clear the interrupt flags */
void syscfg_interrupt_flag_clear(syscfg_flag_enum int_flag);
/* enable the syscfg peripherals interrupt */
void syscfg_interrupt_enable(syscfg_interrupt_enum interrupt);
/* disable the syscfg peripherals interrupt */
void syscfg_interrupt_disable(syscfg_interrupt_enum interrupt);
/* get tcmsram erase busy flag */
FlagStatus syscfg_tcmsram_busy_flag_get(void);
/* get compensation cell ready flag */
FlagStatus syscfg_compensation_cell_ready_flag_get(void);
#endif /* GD32G5X3_SYSCFG_H */
