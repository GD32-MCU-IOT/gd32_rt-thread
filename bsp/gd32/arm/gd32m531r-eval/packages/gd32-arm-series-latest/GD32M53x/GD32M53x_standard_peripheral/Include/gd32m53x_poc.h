/*!
    \file    gd32m53x_poc.h
    \brief   POC driver

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

#ifndef GD32M53X_POC_H
#define GD32M53X_POC_H

#include "gd32m53x.h"

/* POC definitions */
#define POC                                   POC_BASE                               /*!< POC base address */

/* registers definitions */
#define POC_STAT0                             REG32(POC + 0x00000000U)               /*!< POC status register 0 */
#define POC_IN0DCFG                           REG32(POC + 0x00000004U)               /*!< POC input 0 detection configuration register */
#define POC_IN1DCFG                           REG32(POC + 0x00000008U)               /*!< POC input 1 detection configuration register */
#define POC_IN2DCFG                           REG32(POC + 0x0000000CU)               /*!< POC input 2 detection configuration register */
#define POC_IN3DCFG                           REG32(POC + 0x00000010U)               /*!< POC input 3 detection configuration register */
#define POC_IN4DCFG                           REG32(POC + 0x00000014U)               /*!< POC input 4 detection configuration register */
#define POC_IN5DCFG                           REG32(POC + 0x00000018U)               /*!< POC input 5 detection configuration register */
#define POC_CTL0                              REG32(POC + 0x00000020U)               /*!< POC control register 0 */
#define POC_SWDRG                             REG32(POC + 0x00000024U)               /*!< POC software disabling request generation register */
#define POC_CDCFG0                            REG32(POC + 0x00000028U)               /*!< POC complementary detection configuration register 0 */
#define POC_CDCFG1                            REG32(POC + 0x0000002CU)               /*!< POC complementary detection configuration register 1 */
#define POC_ODMODE0                           REG32(POC + 0x00000040U)               /*!< POC output disable mode register 0 */
#define POC_ODMODE1                           REG32(POC + 0x00000044U)               /*!< POC output disable mode register 1 */
#define POC_REQSEL0                           REG32(POC + 0x00000048U)               /*!< POC request selection register 0 */
#define POC_REQSEL1                           REG32(POC + 0x0000004CU)               /*!< POC request selection register 1 */
#define POC_STAT1                             REG32(POC + 0x00000060U)               /*!< POC status register 1 */
#define POC_CTL1                              REG32(POC + 0x00000064U)               /*!< POC control register 1 */
#define POC_EXTCTL0                           REG32(POC + 0x00000068U)               /*!< POC extended control register 0 */
#define POC_EXTCTL1                           REG32(POC + 0x0000006CU)               /*!< POC extended control register 1 */
#define POC_IN0DMK                            REG32(POC + 0x00000070U)               /*!< POC input 0 detection mask register */
#define POC_IN1DMK                            REG32(POC + 0x00000074U)               /*!< POC input 1 detection mask register */
#define POC_IN2DMK                            REG32(POC + 0x00000078U)               /*!< POC input 2 detection mask register */
#define POC_IN3DMK                            REG32(POC + 0x0000007CU)               /*!< POC input 3 detection mask register */
#define POC_IN4DMK                            REG32(POC + 0x00000080U)               /*!< POC input 4 detection mask register */
#define POC_IN5DMK                            REG32(POC + 0x00000084U)               /*!< POC input 5 detection mask register */
#define POC_CMP0DMK                           REG32(POC + 0x00000090U)               /*!< POC comparator 0 detection mask register */
#define POC_CMP1DMK                           REG32(POC + 0x00000094U)               /*!< POC comparator 1 detection mask register */
#define POC_CMP2DMK                           REG32(POC + 0x00000098U)               /*!< POC comparator 2 detection mask register */
#define POC_CMP3DMK                           REG32(POC + 0x0000009CU)               /*!< POC comparator 3 detection mask register */

/* registers byte definitions */
#define POC_IN0DCFG_7_0                         REG8(POC + 0x00000004U)              /*!< POC input 0 detection configuration register 0-7 bits */
#define POC_IN0DCFG_15_8                        REG8(POC + 0x00000005U)              /*!< POC input 0 detection configuration register 15-8 bits */
#define POC_IN1DCFG_7_0                         REG8(POC + 0x00000008U)              /*!< POC input 1 detection configuration register 0-7 bits */
#define POC_IN1DCFG_15_8                        REG8(POC + 0x00000009U)              /*!< POC input 1 detection configuration register 15-8 bits */
#define POC_IN2DCFG_7_0                         REG8(POC + 0x0000000CU)              /*!< POC input 2 detection configuration register 0-7 bits */
#define POC_IN2DCFG_15_8                        REG8(POC + 0x0000000DU)              /*!< POC input 2 detection configuration register 15-8 bits */
#define POC_IN3DCFG_7_0                         REG8(POC + 0x00000010U)              /*!< POC input 3 detection configuration register 0-7 bits */
#define POC_IN3DCFG_15_8                        REG8(POC + 0x00000011U)              /*!< POC input 3 detection configuration register 15-8 bits */
#define POC_IN4DCFG_7_0                         REG8(POC + 0x00000014U)              /*!< POC input 4 detection configuration register 0-7 bits */
#define POC_IN4DCFG_15_8                        REG8(POC + 0x00000015U)              /*!< POC input 4 detection configuration register 15-8 bits */
#define POC_IN5DCFG_7_0                         REG8(POC + 0x00000018U)              /*!< POC input 5 detection configuration register 0-7 bits */
#define POC_IN5DCFG_15_8                        REG8(POC + 0x00000019U)              /*!< POC input 5 detection configuration register 15-8 bits */
#define POC_ODMODE0_TIMER0                      REG8(POC + 0x00000040U)              /*!< POC output disable mode register 0 for TIMER0 */
#define POC_ODMODE0_TIMER7                      REG8(POC + 0x00000041U)              /*!< POC output disable mode register 0 for TIMER7 */
#define POC_ODMODE1_TIMER1                      REG8(POC + 0x00000044U)              /*!< POC output disable mode register 1 for TIMER1 */
#define POC_ODMODE1_TIMER2                      REG8(POC + 0x00000045U)              /*!< POC output disable mode register 1 for TIMER2 */
#define POC_ODMODE1_GPTIMER0                    REG8(POC + 0x00000046U)              /*!< POC output disable mode register 1 for GPTIMER0 */
#define POC_ODMODE1_GPTIMER1                    REG8(POC + 0x00000047U)              /*!< POC output disable mode register 1 for GPTIMER1 */
#define POC_REQSEL0_TIMER0                      REG8(POC + 0x00000048U)              /*!< POC request selection register 0 for TIMER0 */
#define POC_REQSEL0_TIMER7                      REG8(POC + 0x00000049U)              /*!< POC request selection register 0 for TIMER7 */
#define POC_REQSEL1_TIMER1                      REG8(POC + 0x0000004CU)              /*!< POC request selection register 1 for TIMER1 */
#define POC_REQSEL1_TIMER2                      REG8(POC + 0x0000004DU)              /*!< POC request selection register 1 for TIMER2 */
#define POC_REQSEL1_GPTIMER0                    REG8(POC + 0x0000004EU)              /*!< POC request selection register 1 for GPTIMER0 */
#define POC_REQSEL1_GPTIMER1                    REG8(POC + 0x0000004FU)              /*!< POC request selection register 1 for GPTIMER1 */
#define POC_EXTCTL0_TIMER0                      REG8(POC + 0x00000068U)              /*!< POC extended control register 0 for TIMER0 */
#define POC_EXTCTL0_TIMER7                      REG8(POC + 0x00000069U)              /*!< POC extended control register 0 for TIMER7 */
#define POC_EXTCTL1_TIMER1                      REG8(POC + 0x0000006CU)              /*!< POC extended control register 1 for TIMER1 */
#define POC_EXTCTL1_TIMER2                      REG8(POC + 0x0000006DU)              /*!< POC extended control register 1 for TIMER2 */
#define POC_EXTCTL1_GPTIMER0                    REG8(POC + 0x0000006EU)              /*!< POC extended control register 1 for GPTIMER0 */
#define POC_EXTCTL1_GPTIMER1                    REG8(POC + 0x0000006FU)              /*!< POC extended control register 1 for GPTIMER1 */

/* bits definitions */
/* POC_STAT0 */
#define POC_STAT0_IN0IF                      BIT(0)                                  /*!< POC_IN0 input interrupt flag */
#define POC_STAT0_IN1IF                      BIT(1)                                  /*!< POC_IN1 input interrupt flag */
#define POC_STAT0_IN2IF                      BIT(2)                                  /*!< POC_IN2 input interrupt flag */
#define POC_STAT0_IN3IF                      BIT(3)                                  /*!< POC_IN3 input interrupt flag */
#define POC_STAT0_IN4IF                      BIT(4)                                  /*!< POC_IN4 input interrupt flag */
#define POC_STAT0_IN5IF                      BIT(5)                                  /*!< POC_IN5 input interrupt flag */
#define POC_STAT0_HXTALSDF                   BIT(8)                                  /*!< HXTAL stuck detection flag */
#define POC_STAT0_LOCKUPDF                   BIT(9)                                  /*!< CPU LOCKUP detection flag */
#define POC_STAT0_TIMER0_CCIF                BIT(16)                                 /*!< TIMER0 concurrent conduction interrupt flag */
#define POC_STAT0_TIMER7_CCIF                BIT(17)                                 /*!< TIMER7 concurrent conduction interrupt flag */

/* POC_INnDCFG (n=0..5) */
#define POC_INnDCFG_INDMSEL                   BITS(0,3)                              /*!< POC_INn input detection mode selection */
#define POC_INnDCFG_INDSNUM                   BITS(4,7)                              /*!< POC_INn input detection sampling numbert */
#define POC_INnDCFG_INIE                      BIT(8)                                 /*!< POC_INn input interrupt enable */
#define POC_INnDCFG_INDREN                    BIT(9)                                 /*!< POC_INn disabling request enable */
#define POC_INnDCFG_INPL                      BIT(15)                                /*!< Polarity of POC_INn pin input */

/* POC_CTL0 */
#define POC_CTL0_HXTALS_DREN                  BIT(0)                                 /*!< HXTAL stuck disabling request enable */
#define POC_CTL0_LOCKUP_DREN                  BIT(1)                                 /*!< CPU LOCKUP disabling request enable */

/* POC_SWDRG */
#define POC_SWDRG_TIMER0_SWDRG                 BIT(0)                                /*!< software generates the disabling request for TIMER0 */
#define POC_SWDRG_TIMER7_SWDRG                 BIT(1)                                /*!< software generates the disabling request for TIMER7 */
#define POC_SWDRG_TIMER1_SWDRG                 BIT(2)                                /*!< software generates the disabling request for TIMER1 */
#define POC_SWDRG_TIMER2_SWDRG                 BIT(3)                                /*!< software generates the disabling request for TIMER2 */
#define POC_SWDRG_GPTIMER0_SWDRG               BIT(4)                                /*!< software generates the disabling request for GPTIMER0 */
#define POC_SWDRG_GPTIMER1_SWDRG               BIT(5)                                /*!< software generates the disabling request for GPTIMER1 */

/* POC_CDCFG0 */
#define POC_CDCFG0_TIMER0_CH0_APSEL            BIT(0)                                /*!< TIMER0_CH0 active polarity selection */
#define POC_CDCFG0_TIMER0_MCH0_APSEL           BIT(1)                                /*!< TIMER0_MCH0 active polarity selection */
#define POC_CDCFG0_TIMER0_CH1_APSEL            BIT(2)                                /*!< TIMER0_CH1 active polarity selection */
#define POC_CDCFG0_TIMER0_MCH1_APSEL           BIT(3)                                /*!< TIMER0_MCH1 active polarity selection */
#define POC_CDCFG0_TIMER0_CH2_APSEL            BIT(4)                                /*!< TIMER0_CH2 active polarity selection */
#define POC_CDCFG0_TIMER0_MCH2_APSEL           BIT(5)                                /*!< TIMER0_MCH2 active polarity selection */
#define POC_CDCFG0_TIMER0_PSELEN               BIT(7)                                /*!< TIMER0 polarity selection enable */
#define POC_CDCFG0_TIMER0_CCIE                 BIT(8)                                /*!< TIMER0 concurrent conduction interrupt enable */
#define POC_CDCFG0_TIMER0_CCDREN               BIT(9)                                /*!< TIMER0 concurrent conduction disabling request enable */

/* POC_CDCFG1 */
#define POC_CDCFG1_TIMER7_CH0_APSEL            BIT(0)                                /*!< TIMER7_CH0 active polarity selection */
#define POC_CDCFG1_TIMER7_MCH0_APSEL           BIT(1)                                /*!< TIMER7_MCH0 active polarity selection */
#define POC_CDCFG1_TIMER7_CH1_APSEL            BIT(2)                                /*!< TIMER7_CH1 active polarity selection */
#define POC_CDCFG1_TIMER7_MCH1_APSEL           BIT(3)                                /*!< TIMER7_MCH1 active polarity selection */
#define POC_CDCFG1_TIMER7_CH2_APSEL            BIT(4)                                /*!< TIMER7_CH2 active polarity selection */
#define POC_CDCFG1_TIMER7_MCH2_APSEL           BIT(5)                                /*!< TIMER7_MCH2 active polarity selection */
#define POC_CDCFG1_TIMER7_PSELEN               BIT(7)                                /*!< TIMER7 polarity selection enable */
#define POC_CDCFG1_TIMER7_CCIE                 BIT(8)                                /*!< TIMER7 concurrent conduction interrupt enable */
#define POC_CDCFG1_TIMER7_CCDREN               BIT(9)                                /*!< TIMER7 concurrent conduction disabling request enable */

/* POC_ODMODE0 */
#define POC_ODMODE0_TIMER0_OSEL0               BITS(0,1)                             /*!< Output selection for TIMER0_CH0/ TIMER0_MCH0 pin */
#define POC_ODMODE0_TIMER0_OSEL1               BITS(2,3)                             /*!< Output selection for TIMER0_CH1/ TIMER0_MCH1 pin */
#define POC_ODMODE0_TIMER0_OSEL2               BITS(4,5)                             /*!< Output selection for TIMER0_CH2/ TIMER0_MCH2 pin */
#define POC_ODMODE0_TIMER0_OSEL3               BITS(6,7)                             /*!< Output selection for TIMER0_CH3/ TIMER0_MCH3 pin */
#define POC_ODMODE0_TIMER7_OSEL0               BITS(8,9)                             /*!< Output selection for TIMER7_CH0/ TIMER7_MCH0 pin */
#define POC_ODMODE0_TIMER7_OSEL1               BITS(10,11)                           /*!< Output selection for TIMER7_CH1/ TIMER7_MCH1 pin */
#define POC_ODMODE0_TIMER7_OSEL2               BITS(12,13)                           /*!< Output selection for TIMER7_CH2/ TIMER7_MCH2 pin */
#define POC_ODMODE0_TIMER7_OSEL3               BITS(14,15)                           /*!< Output selection for TIMER7_CH3/ TIMER7_MCH3 pin */

/* POC_ODMODE1 */
#define POC_ODMODE1_TIMER1_OSEL0               BITS(0,1)                             /*!< Output selection for TIMER1_CH0 pin */
#define POC_ODMODE1_TIMER1_OSEL1               BITS(2,3)                             /*!< Output selection for TIMER1_CH1 pin */
#define POC_ODMODE1_TIMER1_OSEL2               BITS(4,5)                             /*!< Output selection for TIMER1_CH2 pin */
#define POC_ODMODE1_TIMER1_OSEL3               BITS(6,7)                             /*!< Output selection for TIMER1_CH3 pin */
#define POC_ODMODE1_TIMER2_OSEL0               BITS(8,9)                             /*!< Output selection for TIMER2_CH0 pin */
#define POC_ODMODE1_TIMER2_OSEL1               BITS(10,11)                           /*!< Output selection for TIMER2_CH1 pin */
#define POC_ODMODE1_TIMER2_OSEL2               BITS(12,13)                           /*!< Output selection for TIMER2_CH2 pin */
#define POC_ODMODE1_TIMER2_OSEL3               BITS(14,15)                           /*!< Output selection for TIMER2_CH3 pin */
#define POC_ODMODE1_GPTIMER0_OSEL0             BITS(16,17)                           /*!< Output selection for GPTIMER0_CH0 pin */
#define POC_ODMODE1_GPTIMER0_OSEL1             BITS(18,19)                           /*!< Output selection for GPTIMER0_CH1 pin */
#define POC_ODMODE1_GPTIMER1_OSEL0             BITS(24,25)                           /*!< Output selection for GPTIMER1_CH0 pin */
#define POC_ODMODE1_GPTIMER1_OSEL1             BITS(26,27)                           /*!< Output selection for GPTIMER1_CH1 pin */

/* POC_REQSEL0 */
#define POC_REQSEL0_TIMER0_IN0DRSEL            BIT(0)                                /*!< POC_IN0 disabling request select TIMER0 */
#define POC_REQSEL0_TIMER0_IN1DRSEL            BIT(1)                                /*!< POC_IN1 disabling request select TIMER0 */
#define POC_REQSEL0_TIMER0_IN2DRSEL            BIT(2)                                /*!< POC_IN2 disabling request select TIMER0 */
#define POC_REQSEL0_TIMER0_IN3DRSEL            BIT(3)                                /*!< POC_IN3 disabling request select TIMER0 */
#define POC_REQSEL0_TIMER0_IN4DRSEL            BIT(4)                                /*!< POC_IN4 disabling request select TIMER0 */
#define POC_REQSEL0_TIMER0_IN5DRSEL            BIT(5)                                /*!< POC_IN5 disabling request select TIMER0 */
#define POC_REQSEL0_TIMER0_CMPDRSEL            BIT(6)                                /*!< CMPn (n=0,1,2,3) disabling request select TIMER0 */
#define POC_REQSEL0_TIMER7_IN0DRSEL            BIT(8)                                /*!< POC_IN0 disabling request select TIMER7 */
#define POC_REQSEL0_TIMER7_IN1DRSEL            BIT(9)                                /*!< POC_IN1 disabling request select TIMER7 */
#define POC_REQSEL0_TIMER7_IN2DRSEL            BIT(10)                               /*!< POC_IN2 disabling request select TIMER7 */
#define POC_REQSEL0_TIMER7_IN3DRSEL            BIT(11)                               /*!< POC_IN3 disabling request select TIMER7 */
#define POC_REQSEL0_TIMER7_IN4DRSEL            BIT(12)                               /*!< POC_IN4 disabling request select TIMER7 */
#define POC_REQSEL0_TIMER7_IN5DRSEL            BIT(13)                               /*!< POC_IN5 disabling request select TIMER7 */
#define POC_REQSEL0_TIMER7_CMPDRSEL            BIT(14)                               /*!< CMPn (n=0,1,2,3) disabling request select TIMER7 */

/* POC_REQSEL1 */
#define POC_REQSEL1_TIMER1_IN0DRSEL            BIT(0)                                /*!< POC_IN0 disabling request select TIMER1 */
#define POC_REQSEL1_TIMER1_IN1DRSEL            BIT(1)                                /*!< POC_IN1 disabling request select TIMER1 */
#define POC_REQSEL1_TIMER1_IN2DRSEL            BIT(2)                                /*!< POC_IN2 disabling request select TIMER1 */
#define POC_REQSEL1_TIMER1_IN3DRSEL            BIT(3)                                /*!< POC_IN3 disabling request select TIMER1 */
#define POC_REQSEL1_TIMER1_IN4DRSEL            BIT(4)                                /*!< POC_IN4 disabling request select TIMER1 */
#define POC_REQSEL1_TIMER1_IN5DRSEL            BIT(5)                                /*!< POC_IN5 disabling request select TIMER1 */
#define POC_REQSEL1_TIMER1_CMPDRSEL            BIT(6)                                /*!< CMPn (n=0,1,2,3) disabling request select TIMER1 */
#define POC_REQSEL1_TIMER2_IN0DRSEL            BIT(8)                                /*!< POC_IN0 disabling request select TIMER2 */
#define POC_REQSEL1_TIMER2_IN1DRSEL            BIT(9)                                /*!< POC_IN1 disabling request select TIMER2 */
#define POC_REQSEL1_TIMER2_IN2DRSEL            BIT(10)                               /*!< POC_IN2 disabling request select TIMER2 */
#define POC_REQSEL1_TIMER2_IN3DRSEL            BIT(11)                               /*!< POC_IN3 disabling request select TIMER2 */
#define POC_REQSEL1_TIMER2_IN4DRSEL            BIT(12)                               /*!< POC_IN4 disabling request select TIMER2 */
#define POC_REQSEL1_TIMER2_IN5DRSEL            BIT(13)                               /*!< POC_IN5 disabling request select TIMER2 */
#define POC_REQSEL1_TIMER2_CMPDRSEL            BIT(14)                               /*!< CMPn (n=0,1,2,3) disabling request select TIMER2 */
#define POC_REQSEL1_GPTIMER0_IN0DRSEL          BIT(16)                               /*!< POC_IN0 disabling request select GPTIMER0 */
#define POC_REQSEL1_GPTIMER0_IN1DRSEL          BIT(17)                               /*!< POC_IN1 disabling request select GPTIMER0 */
#define POC_REQSEL1_GPTIMER0_IN2DRSEL          BIT(18)                               /*!< POC_IN2 disabling request select GPTIMER0 */
#define POC_REQSEL1_GPTIMER0_IN3DRSEL          BIT(19)                               /*!< POC_IN3 disabling request select GPTIMER0 */
#define POC_REQSEL1_GPTIMER0_IN4DRSEL          BIT(20)                               /*!< POC_IN4 disabling request select GPTIMER0 */
#define POC_REQSEL1_GPTIMER0_IN5DRSEL          BIT(21)                               /*!< POC_IN5 disabling request select GPTIMER0 */
#define POC_REQSEL1_GPTIMER0_CMPDRSEL          BIT(22)                               /*!< CMPn (n=0,1,2,3) disabling request select GPTIMER0 */
#define POC_REQSEL1_GPTIMER1_IN0DRSEL          BIT(24)                               /*!< POC_IN0 disabling request select GPTIMER1 */
#define POC_REQSEL1_GPTIMER1_IN1DRSEL          BIT(25)                               /*!< POC_IN1 disabling request select GPTIMER1 */
#define POC_REQSEL1_GPTIMER1_IN2DRSEL          BIT(26)                               /*!< POC_IN2 disabling request select GPTIMER1 */
#define POC_REQSEL1_GPTIMER1_IN3DRSEL          BIT(27)                               /*!< POC_IN3 disabling request select GPTIMER1 */
#define POC_REQSEL1_GPTIMER1_IN4DRSEL          BIT(28)                               /*!< POC_IN4 disabling request select GPTIMER1 */
#define POC_REQSEL1_GPTIMER1_IN5DRSEL          BIT(29)                               /*!< POC_IN5 disabling request select GPTIMER1 */
#define POC_REQSEL1_GPTIMER1_CMPDRSEL          BIT(30)                               /*!< CMPn (n=0,1,2,3) disabling request select GPTIMER1 */

/* POC_STAT1 */
#define POC_STAT1_CMP0DF                       BIT(0)                                /*!< comparator 0 detection flag */
#define POC_STAT1_CMP1DF                       BIT(1)                                /*!< comparator 1 detection flag */
#define POC_STAT1_CMP2DF                       BIT(2)                                /*!< comparator 2 detection flag */
#define POC_STAT1_CMP3DF                       BIT(3)                                /*!< comparator 3 detection flag */

/* POC_CTL1 */
#define POC_CTL1_CMP0DREN                     BIT(0)                                 /*!< comparator 0 disabling request enable */
#define POC_CTL1_CMP1DREN                     BIT(1)                                 /*!< comparator 1 disabling request enable */
#define POC_CTL1_CMP2DREN                     BIT(2)                                 /*!< comparator 2 disabling request enable */
#define POC_CTL1_CMP3DREN                     BIT(3)                                 /*!< comparator 3 disabling request enable */

/* POC_EXTCTL0 */
#define POC_EXTCTL0_TIMER0_CMP0DREN           BIT(0)                                 /*!< comparator 0 disabling request enable for TIMER0 */
#define POC_EXTCTL0_TIMER0_CMP1DREN           BIT(1)                                 /*!< comparator 1 disabling request enable for TIMER0 */
#define POC_EXTCTL0_TIMER0_CMP2DREN           BIT(2)                                 /*!< comparator 2 disabling request enable for TIMER0 */
#define POC_EXTCTL0_TIMER0_CMP3DREN           BIT(3)                                 /*!< comparator 3 disabling request enable for TIMER0 */
#define POC_EXTCTL0_TIMER7_CMP0DREN           BIT(8)                                 /*!< comparator 0 disabling request enable for TIMER7 */
#define POC_EXTCTL0_TIMER7_CMP1DREN           BIT(9)                                 /*!< comparator 1 disabling request enable for TIMER7 */
#define POC_EXTCTL0_TIMER7_CMP2DREN           BIT(10)                                /*!< comparator 2 disabling request enable for TIMER7 */
#define POC_EXTCTL0_TIMER7_CMP3DREN           BIT(11)                                /*!< comparator 3 disabling request enable for TIMER7 */

/* POC_EXTCTL1 */
#define POC_EXTCTL1_TIMER1_CMP0DREN           BIT(0)                                 /*!< comparator 0 disabling request enable for TIMER1 */
#define POC_EXTCTL1_TIMER1_CMP1DREN           BIT(1)                                 /*!< comparator 1 disabling request enable for TIMER1 */
#define POC_EXTCTL1_TIMER1_CMP2DREN           BIT(2)                                 /*!< comparator 2 disabling request enable for TIMER1 */
#define POC_EXTCTL1_TIMER1_CMP3DREN           BIT(3)                                 /*!< comparator 3 disabling request enable for TIMER1 */
#define POC_EXTCTL1_TIMER2_CMP0DREN           BIT(8)                                 /*!< comparator 0 disabling request enable for TIMER2 */
#define POC_EXTCTL1_TIMER2_CMP1DREN           BIT(9)                                 /*!< comparator 1 disabling request enable for TIMER2 */
#define POC_EXTCTL1_TIMER2_CMP2DREN           BIT(10)                                /*!< comparator 2 disabling request enable for TIMER2 */
#define POC_EXTCTL1_TIMER2_CMP3DREN           BIT(11)                                /*!< comparator 3 disabling request enable for TIMER2 */
#define POC_EXTCTL1_GPTIMER0_CMP0DREN         BIT(16)                                /*!< comparator 0 disabling request enable for GPTIMER0 */
#define POC_EXTCTL1_GPTIMER0_CMP1DREN         BIT(17)                                /*!< comparator 1 disabling request enable for GPTIMER0 */
#define POC_EXTCTL1_GPTIMER0_CMP2DREN         BIT(18)                                /*!< comparator 2 disabling request enable for GPTIMER0 */
#define POC_EXTCTL1_GPTIMER0_CMP3DREN         BIT(19)                                /*!< comparator 3 disabling request enable for GPTIMER0 */
#define POC_EXTCTL1_GPTIMER1_CMP0DREN         BIT(24)                                /*!< comparator 0 disabling request enable for GPTIMER1 */
#define POC_EXTCTL1_GPTIMER1_CMP1DREN         BIT(25)                                /*!< comparator 1 disabling request enable for GPTIMER1 */
#define POC_EXTCTL1_GPTIMER1_CMP2DREN         BIT(26)                                /*!< comparator 2 disabling request enable for GPTIMER1 */
#define POC_EXTCTL1_GPTIMER1_CMP3DREN         BIT(27)                                /*!< comparator 3 disabling request enable for GPTIMER1 */

/* POC_INnDMK (n=0..5) */
#define POC_INnDMK_INMKSEL                    BITS(0,4)                              /*!< POC_INn input detection mask selection */

/* POC_CMPnDMK (n=0..3) */
#define POC_CMPnDMK_CMPMKSEL                 BITS(0,4)                               /*!< Comparator n output detection mask selection */

/* constants definitions */
/* disabling request source */
typedef struct {
    uint8_t req_pocin0;                                                              /*!< request from POC_IN0 pin input detection */
    uint8_t req_pocin1;                                                              /*!< request from POC_IN1 pin input detection */
    uint8_t req_pocin2;                                                              /*!< request from POC_IN2 pin input detection */
    uint8_t req_pocin3;                                                              /*!< request from POC_IN3 pin input detection */
    uint8_t req_pocin4;                                                              /*!< request from POC_IN4 pin input detection */
    uint8_t req_pocin5;                                                              /*!< request from POC_IN5 pin input detection */
    uint8_t req_comparator;                                                          /*!< request from comparator output detection */
} poc_request_struct;

/* POC input pin */
typedef enum {
    POC_IN0 = 0,                                                                     /*!< POC_IN0 input pin */
    POC_IN1,                                                                         /*!< POC_IN1 input pin */
    POC_IN2,                                                                         /*!< POC_IN2 input pin */
    POC_IN3,                                                                         /*!< POC_IN3 input pin */
    POC_IN4,                                                                         /*!< POC_IN4 input pin */
    POC_IN5                                                                          /*!< POC_IN5 input pin */
} poc_pin_enum;

/* comparator output */
typedef enum {
    CMP0_OUT = 0,                                                                    /*!< comparator 0 output */
    CMP1_OUT,                                                                        /*!< comparator 1 output */
    CMP2_OUT,                                                                        /*!< comparator 2 output */
    CMP3_OUT                                                                         /*!< comparator 3 output */
} cmp_output_enum;

/* poc target timer */
typedef enum {
    TARGET_TIMER0 = 0,                                                               /*!< TIMER0 */
    TARGET_TIMER7,                                                                   /*!< TIMER7 */
    TARGET_TIMER1,                                                                   /*!< TIMER1 */
    TARGET_TIMER2,                                                                   /*!< TIMER2 */
    TARGET_GPTIMER0,                                                                 /*!< GPTIMER0 */
    TARGET_GPTIMER1                                                                  /*!< GPTIMER1 */
} target_timer_enum;

/* poc interrupt */
typedef enum {
    POC_INT_IN0 = 0,                                                                 /*!< POC_IN0 input detection interrupt */
    POC_INT_IN1,                                                                     /*!< POC_IN1 input detection interrupt */
    POC_INT_IN2,                                                                     /*!< POC_IN2 input detection interrupt */
    POC_INT_IN3,                                                                     /*!< POC_IN3 input detection interrupt */
    POC_INT_IN4,                                                                     /*!< POC_IN4 input detection interrupt */
    POC_INT_IN5,                                                                     /*!< POC_IN5 input detection interrupt */
    POC_INT_TIMER0CC,                                                                /*!< TIMER0 concurrent conduction detection interrupt */
    POC_INT_TIMER7CC                                                                 /*!< TIMER7 concurrent conduction detection interrupt */
} poc_interrupt_enum;

/* poc timer complementary detection struct definitions */
typedef struct {
    uint32_t ccdreqstatus;                                                           /*!< concurrent conduction disabling request status */
    uint32_t polarityselen;                                                          /*!< timer polarity selection enable  */
    uint32_t mch2polarity;                                                           /*!< multi mode channel 2 active polarity selection */
    uint32_t ch2polarity;                                                            /*!< channel 2 active polarity selection */
    uint32_t mch1polarity;                                                           /*!< multi mode channel 1 active polarity selection */
    uint32_t ch1polarity;                                                            /*!< channel 1 active polarity selection */
    uint32_t mch0polarity;                                                           /*!< multi mode channel 0 active polarity selection */
    uint32_t ch0polarity;                                                            /*!< channel 0 active polarity selection */
} poc_complementary_detection_struct;

/* POC_INn input detection mode */
#define INnDCFG_INDMSEL(regval)               (BITS(0,3) & ((uint32_t)(regval) << 0))
#define POC_EDGE_DETECTION_DIV1               INnDCFG_INDMSEL(0)                     /*!< Sampling frequency is fHCLK and generate a request on the falling edge (INPL=0) or rising edge (INPL=1) */
#define POC_LEVEL_DETECTION_DIV8              INnDCFG_INDMSEL(1)                     /*!< Sampling frequency is fHCLK/8 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times */
#define POC_LEVEL_DETECTION_DIV16             INnDCFG_INDMSEL(2)                     /*!< Sampling frequency is fHCLK/16 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times */
#define POC_LEVEL_DETECTION_DIV128            INnDCFG_INDMSEL(3)                     /*!< Sampling frequency is fHCLK/128 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times */
#define POC_LEVEL_DETECTION_DIV1              INnDCFG_INDMSEL(4)                     /*!< Sampling frequency is fHCLK and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times */
#define POC_LEVEL_DETECTION_DIV2              INnDCFG_INDMSEL(5)                     /*!< Sampling frequency is fHCLK/2 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times */
#define POC_LEVEL_DETECTION_DIV4              INnDCFG_INDMSEL(6)                     /*!< Sampling frequency is fHCLK/4 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times */
#define POC_LEVEL_DETECTION_DIV256            INnDCFG_INDMSEL(7)                     /*!< Sampling frequency is fHCLK/256 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times */
#define POC_LEVEL_DETECTION_DIV512            INnDCFG_INDMSEL(8)                     /*!< Sampling frequency is fHCLK/512 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times */
#define POC_LEVEL_DETECTION_DIV32             INnDCFG_INDMSEL(9)                     /*!< Sampling frequency is fHCLK/32 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times */
#define POC_LEVEL_DETECTION_DIV64             INnDCFG_INDMSEL(10)                    /*!< Sampling frequency is fHCLK/64 and generate a request when the low level (INPL=0) or high level (INPL=1) is continuously sampled a certain number of times */
#define POC_EDGE_DETECTION_DIV2               INnDCFG_INDMSEL(11)                    /*!< Sampling frequency is fHCLK/2 and generate a request on the falling edge (INPL=0) or rising edge (INPL=1) */
#define POC_EDGE_DETECTION_DIV4               INnDCFG_INDMSEL(12)                    /*!< Sampling frequency is fHCLK/4 and generate a request on the falling edge (INPL=0) or rising edge (INPL=1) */

/* POC_INn input detection sampling number */
#define INnDCFG_INDSNUM(regval)               (BITS(4,7) & ((uint32_t)(regval) << 4))
#define POC_SAMPLING_NUM_16_TIMES             INnDCFG_INDSNUM(0)                     /*!< sampling number is 16 times */
#define POC_SAMPLING_NUM_4_TIMES              INnDCFG_INDSNUM(1)                     /*!< sampling number is 4 times */
#define POC_SAMPLING_NUM_8_TIMES              INnDCFG_INDSNUM(2)                     /*!< sampling number is 8 times */
#define POC_SAMPLING_NUM_9_TIMES              INnDCFG_INDSNUM(3)                     /*!< sampling number is 9 times */
#define POC_SAMPLING_NUM_10_TIMES             INnDCFG_INDSNUM(4)                     /*!< sampling number is 10 times */
#define POC_SAMPLING_NUM_11_TIMES             INnDCFG_INDSNUM(5)                     /*!< sampling number is 11 times */
#define POC_SAMPLING_NUM_12_TIMES             INnDCFG_INDSNUM(6)                     /*!< sampling number is 12 times */
#define POC_SAMPLING_NUM_13_TIMES             INnDCFG_INDSNUM(7)                     /*!< sampling number is 13 times */
#define POC_SAMPLING_NUM_14_TIMES             INnDCFG_INDSNUM(8)                     /*!< sampling number is 14 times */
#define POC_SAMPLING_NUM_15_TIMES             INnDCFG_INDSNUM(9)                     /*!< sampling number is 15 times */

/* output disable mode */
#define POC_TIMER_CHANNEL_OUT                 ((uint8_t)0x00U)                       /*!< timer channel output */
#define POC_HIGH_IMPEDANCE_OUT                ((uint8_t)0x01U)                       /*!< High-impedance output */
#define POC_GPIO_OUT                          ((uint8_t)0x02U)                       /*!< GPIO output */

/* polarity of POC_INn input */
#define INnDCFG_INPL(regval)                  (BIT(15) & ((uint32_t)(regval) << 15U))
#define POC_INPUT_POLARITY_NONINVERTED        INnDCFG_INPL(0)                        /*!< POC_INn input not inverted */
#define POC_INPUT_POLARITY_INVERTED           INnDCFG_INPL(1)                        /*!< POC_INn input inverted */

/* POC_INn disabling request status */
#define INnDCFG_INDREN(regval)                (BIT(9) & ((uint32_t)(regval) << 9U))
#define POC_INn_DREQ_DISABLE                  INnDCFG_INDREN(0)                      /*!< POC_INn disabling request disable */
#define POC_INn_DREQ_ENABLE                   INnDCFG_INDREN(1)                      /*!< POC_INn disabling request enable */

/* HXTAL stuck disabling request status */
#define CTL0_HXTALS_DREN(regval)              (BIT(0) & ((uint32_t)(regval) << 0U))
#define HXTALS_DREQ_DISABLE                   CTL0_HXTALS_DREN(0)                    /*!< HXTAL stuck disabling request disable */
#define HXTALS_DREQ_ENABLE                    CTL0_HXTALS_DREN(1)                    /*!< HXTAL stuck disabling request enable */

/* CPU LOCKUP disabling request status */
#define CTL0_LOCKUP_DREN(regval)              (BIT(1) & ((uint32_t)(regval) << 1U))
#define LOCKUP_DREQ_DISABLE                   CTL0_LOCKUP_DREN(0)                    /*!< CPU LOCKUP disabling request disable */
#define LOCKUP_DREQ_ENABLE                    CTL0_LOCKUP_DREN(1)                    /*!< CPU LOCKUP disabling request enable */

/* TIMER concurrent conduction disabling request status */
#define CDCFG_TIMER_CCDREN(regval)            (BIT(9) & ((uint32_t)(regval) << 9U))
#define TIMER_CCDREQ_DISABLE                   CDCFG_TIMER_CCDREN(0)                 /*!< TIMER concurrent conduction disabling request disable */
#define TIMER_CCDREQ_ENABLE                    CDCFG_TIMER_CCDREN(1)                 /*!< TIMER concurrent conduction disabling request enable */

/* TIMER polarity selection enable */
#define CDCFG_TIMER_PSELEN(regval)            (BIT(7) & ((uint32_t)(regval) << 7U))
#define TIMER_POLARITY_SELECTION_DISABLE       CDCFG_TIMER_PSELEN(0)                 /*!< TIMER polarity selection is enabled */
#define TIMER_POLARITY_SELECTION_ENABLE        CDCFG_TIMER_PSELEN(1)                 /*!< TIMER polarity selection is disabled */

/* multi mode channel 2 active polarity */
#define CDCFG_MCH2_APSEL(regval)              (BIT(5) & ((uint32_t)(regval) << 5U))
#define MCH2_POLARITY_HIGH                     CDCFG_MCH2_APSEL(0)                   /*!< multi mode channel 2 active polarity is high*/
#define MCH2_POLARITY_LOW                      CDCFG_MCH2_APSEL(1)                   /*!< multi mode channel 2 active polarity is low */

/* channel 2 active polarity */
#define CDCFG_CH2_APSEL(regval)              (BIT(4) & ((uint32_t)(regval) << 4U))
#define CH2_POLARITY_HIGH                     CDCFG_CH2_APSEL(0)                     /*!< channel 2 active polarity is high*/
#define CH2_POLARITY_LOW                      CDCFG_CH2_APSEL(1)                     /*!< channel 2 active polarity is low */

/* multi mode channel 1 active polarity */
#define CDCFG_MCH1_APSEL(regval)              (BIT(3) & ((uint32_t)(regval) << 3U))
#define MCH1_POLARITY_HIGH                     CDCFG_MCH1_APSEL(0)                   /*!< multi mode channel 1 active polarity is high*/
#define MCH1_POLARITY_LOW                      CDCFG_MCH1_APSEL(1)                   /*!< multi mode channel 1 active polarity is low */

/* channel 1 active polarity */
#define CDCFG_CH1_APSEL(regval)              (BIT(2) & ((uint32_t)(regval) << 2U))
#define CH1_POLARITY_HIGH                     CDCFG_CH1_APSEL(0)                     /*!< channel 1 active polarity is high*/
#define CH1_POLARITY_LOW                      CDCFG_CH1_APSEL(1)                     /*!< channel 1 active polarity is low */

/* multi mode channel 0 active polarity */
#define CDCFG_MCH0_APSEL(regval)              (BIT(1) & ((uint32_t)(regval) << 1U))
#define MCH0_POLARITY_HIGH                     CDCFG_MCH0_APSEL(0)                   /*!< multi mode channel 0 active polarity is high*/
#define MCH0_POLARITY_LOW                      CDCFG_MCH0_APSEL(1)                   /*!< multi mode channel 0 active polarity is low */

/* channel 0 active polarity */
#define CDCFG_CH0_APSEL(regval)              (BIT(0) & ((uint32_t)(regval) << 0U))
#define CH0_POLARITY_HIGH                     CDCFG_CH0_APSEL(0)                     /*!< channel 0 active polarity is high*/
#define CH0_POLARITY_LOW                      CDCFG_CH0_APSEL(1)                     /*!< channel 0 active polarity is low */

/* request select target timer */
#define TARGET_TIMER_NOT_SELECTED            ((uint8_t)0x00U)                        /*!< target timer is not selected */
#define TARGET_TIMER_SELECTED                ((uint8_t)0x01U)                        /*!< target timer is selected */

/* comparator 0 disabling request status */
#define CTL1_CMP0DREN(regval)                  (BIT(0) & ((uint32_t)(regval) << 0U))
#define CMP0_DREQ_DISABLE                      CTL1_CMP0DREN(0)                      /*!< comparator 0 disabling request disable */
#define CMP0_DREQ_ENABLE                       CTL1_CMP0DREN(1)                      /*!< comparator 0 disabling request enable */

/* comparator 1 disabling request status */
#define CTL1_CMP1DREN(regval)                  (BIT(1) & ((uint32_t)(regval) << 1U))
#define CMP1_DREQ_DISABLE                      CTL1_CMP1DREN(0)                      /*!< comparator 1 disabling request disable */
#define CMP1_DREQ_ENABLE                       CTL1_CMP1DREN(1)                      /*!< comparator 1 disabling request enable */

/* comparator 2 disabling request status */
#define CTL1_CMP2DREN(regval)                  (BIT(2) & ((uint32_t)(regval) << 2U))
#define CMP2_DREQ_DISABLE                      CTL1_CMP2DREN(0)                      /*!< comparator 2 disabling request disable */
#define CMP2_DREQ_ENABLE                       CTL1_CMP2DREN(1)                      /*!< comparator 2 disabling request enable */

/* comparator 3 disabling request status */
#define CTL1_CMP3DREN(regval)                  (BIT(3) & ((uint32_t)(regval) << 3U))
#define CMP3_DREQ_DISABLE                      CTL1_CMP3DREN(0)                      /*!< comparator 3 disabling request disable */
#define CMP3_DREQ_ENABLE                       CTL1_CMP3DREN(1)                      /*!< comparator 3 disabling request enable */

/* detection mask source selection */
#define DMK_MKSEL(regval)                    (BITS(0, 4) & ((uint32_t)(regval) << 0U))
#define POC_REQUEST_NOT_MASKED                DMK_MKSEL(0)                           /*!< detection is not masked */
#define POC_MASK_SOURCE_TIMER0_CH0            DMK_MKSEL(1)                           /*!< detection is masked by TIMER0_CH0 */
#define POC_MASK_SOURCE_TIMER0_CH1            DMK_MKSEL(2)                           /*!< detection is masked by TIMER0_CH1 */
#define POC_MASK_SOURCE_TIMER0_CH2            DMK_MKSEL(3)                           /*!< detection is masked by TIMER0_CH2 */
#define POC_MASK_SOURCE_TIMER0_CH3            DMK_MKSEL(4)                           /*!< detection is masked by TIMER0_CH3 */
#define POC_MASK_SOURCE_TIMER0_MCH0           DMK_MKSEL(5)                           /*!< detection is masked by TIMER0_MCH0 */
#define POC_MASK_SOURCE_TIMER0_MCH1           DMK_MKSEL(6)                           /*!< detection is masked by TIMER0_MCH1 */
#define POC_MASK_SOURCE_TIMER0_MCH2           DMK_MKSEL(7)                           /*!< detection is masked by TIMER0_MCH2 */
#define POC_MASK_SOURCE_TIMER0_MCH3           DMK_MKSEL(8)                           /*!< detection is masked by TIMER0_MCH3 */
#define POC_MASK_SOURCE_TIMER7_CH0            DMK_MKSEL(9)                           /*!< detection is masked by TIMER7_CH0 */
#define POC_MASK_SOURCE_TIMER7_CH1            DMK_MKSEL(10)                          /*!< detection is masked by TIMER7_CH1 */
#define POC_MASK_SOURCE_TIMER7_CH2            DMK_MKSEL(11)                          /*!< detection is masked by TIMER7_CH2 */
#define POC_MASK_SOURCE_TIMER7_CH3            DMK_MKSEL(12)                          /*!< detection is masked by TIMER7_CH3 */
#define POC_MASK_SOURCE_TIMER7_MCH0           DMK_MKSEL(13)                          /*!< detection is masked by TIMER7_MCH0 */
#define POC_MASK_SOURCE_TIMER7_MCH1           DMK_MKSEL(14)                          /*!< detection is masked by TIMER7_MCH1 */
#define POC_MASK_SOURCE_TIMER7_MCH2           DMK_MKSEL(15)                          /*!< detection is masked by TIMER7_MCH2 */
#define POC_MASK_SOURCE_TIMER7_MCH3           DMK_MKSEL(16)                          /*!< detection is masked by TIMER7_MCH3 */
#define POC_MASK_SOURCE_TIMER1_CH0            DMK_MKSEL(17)                          /*!< detection is masked by TIMER1_CH0 */
#define POC_MASK_SOURCE_TIMER1_CH1            DMK_MKSEL(18)                          /*!< detection is masked by TIMER1_CH1 */
#define POC_MASK_SOURCE_TIMER1_CH2            DMK_MKSEL(19)                          /*!< detection is masked by TIMER1_CH2 */
#define POC_MASK_SOURCE_TIMER1_CH3            DMK_MKSEL(20)                          /*!< detection is masked by TIMER1_CH3 */
#define POC_MASK_SOURCE_TIMER2_CH0            DMK_MKSEL(21)                          /*!< detection is masked by TIMER2_CH0 */
#define POC_MASK_SOURCE_TIMER2_CH1            DMK_MKSEL(22)                          /*!< detection is masked by TIMER2_CH1 */
#define POC_MASK_SOURCE_TIMER2_CH2            DMK_MKSEL(23)                          /*!< detection is masked by TIMER2_CH2 */
#define POC_MASK_SOURCE_TIMER2_CH3            DMK_MKSEL(24)                          /*!< detection is masked by TIMER2_CH3 */
#define POC_MASK_SOURCE_GPTIMER0_CH0          DMK_MKSEL(25)                          /*!< detection is masked by GPTIMER0_CH0 */
#define POC_MASK_SOURCE_GPTIMER0_CH1          DMK_MKSEL(26)                          /*!< detection is masked by GPTIMER0_CH1 */
#define POC_MASK_SOURCE_GPTIMER1_CH0          DMK_MKSEL(27)                          /*!< detection is masked by GPTIMER1_CH0 */
#define POC_MASK_SOURCE_GPTIMER1_CH1          DMK_MKSEL(28)                          /*!< detection is masked by GPTIMER1_CH1 */

/* POC flags */
#define POC_FLAG_IN0IF                   POC_STAT0_IN0IF                             /*!< POC_IN0 input detection flag */
#define POC_FLAG_IN1IF                   POC_STAT0_IN1IF                             /*!< POC_IN1 input detection flag */
#define POC_FLAG_IN2IF                   POC_STAT0_IN2IF                             /*!< POC_IN2 input detection flag */
#define POC_FLAG_IN3IF                   POC_STAT0_IN3IF                             /*!< POC_IN3 input detection flag */
#define POC_FLAG_IN4IF                   POC_STAT0_IN4IF                             /*!< POC_IN4 input detection flag */
#define POC_FLAG_IN5IF                   POC_STAT0_IN5IF                             /*!< POC_IN5 input detection flag */
#define POC_FLAG_HXTALSDF                POC_STAT0_HXTALSDF                          /*!< HXTAL stuck detection flag */
#define POC_FLAG_LOCKUPDF                POC_STAT0_LOCKUPDF                          /*!< CPU LOCKUP detection flag */
#define POC_FLAG_TIMER0_CCIF             POC_STAT0_TIMER0_CCIF                       /*!< TIMER0 concurrent conduction flag */
#define POC_FLAG_TIMER7_CCIF             POC_STAT0_TIMER7_CCIF                       /*!< TIMER7 concurrent conduction flag */
#define POC_FLAG_CMP0DF                 (POC_STAT1_CMP0DF << 24U)                    /*!< comparator 0 detection flag */
#define POC_FLAG_CMP1DF                 (POC_STAT1_CMP1DF << 24U)                    /*!< comparator 1 detection flag */
#define POC_FLAG_CMP2DF                 (POC_STAT1_CMP2DF << 24U)                    /*!< comparator 2 detection flag */
#define POC_FLAG_CMP3DF                 (POC_STAT1_CMP3DF << 24U)                    /*!< comparator 3 detection flag */

/* POC interrupt flags */
#define POC_INT_FLAG_IN0IF                   POC_STAT0_IN0IF                         /*!< POC_IN0 input interrupt flag */
#define POC_INT_FLAG_IN1IF                   POC_STAT0_IN1IF                         /*!< POC_IN1 input interrupt flag */
#define POC_INT_FLAG_IN2IF                   POC_STAT0_IN2IF                         /*!< POC_IN2 input interrupt flag */
#define POC_INT_FLAG_IN3IF                   POC_STAT0_IN3IF                         /*!< POC_IN3 input interrupt flag */
#define POC_INT_FLAG_IN4IF                   POC_STAT0_IN4IF                         /*!< POC_IN4 input interrupt flag */
#define POC_INT_FLAG_IN5IF                   POC_STAT0_IN5IF                         /*!< POC_IN5 input interrupt flag */
#define POC_INT_FLAG_TIMER0_CCIF             POC_STAT0_TIMER0_CCIF                   /*!< TIMER0 concurrent conduction interrupt flag */
#define POC_INT_FLAG_TIMER7_CCIF             POC_STAT0_TIMER7_CCIF                   /*!< TIMER7 concurrent conduction interrupt flag */

/* function declarations */
/* deinitialize POC */
void poc_deinit(void);
/* configure POC_INn input detection */
void poc_input_detection_config(poc_pin_enum poc_pin, uint32_t detection_mode, uint32_t sampling_number);
/* configure POC_INn disabling request status */
void poc_input_dreq_status_config(poc_pin_enum poc_pin, uint32_t indreq_status);
/* configure POC_INn input polarity */
void poc_input_polarity_config(poc_pin_enum poc_pin, uint32_t input_polarity);
/* configure system fault disabling request status */
void poc_sys_fault_dreq_status_config(uint32_t hxtalsdreq_status, uint32_t lockupdreq_status);
/* generate software disabling request for timer */
void poc_software_request_generate(target_timer_enum target_timer);
/* stop software disabling request for timer */
void poc_software_request_stop(target_timer_enum target_timer);
/* initialize POC complementary detection struct */
void poc_complementary_detection_struct_para_init(poc_complementary_detection_struct *detpara);
/* configure TIMER0 complementary channel detection */
void poc_timer0_complementary_detection_config(poc_complementary_detection_struct *detpara);
/* configure TIMER7 complementary channel detection */
void poc_timer7_complementary_detection_config(poc_complementary_detection_struct *detpara);

/* select output disable mode for TIMER0 */
void poc_timer0_output_disable_mode_select(uint8_t ch0mch0_pin_mode, uint8_t ch1mch1_pin_mode, uint8_t ch2mch2_pin_mode, uint8_t ch3mch3_pin_mode);
/* select output disable mode for TIMER7 */
void poc_timer7_output_disable_mode_select(uint8_t ch0mch0_pin_mode, uint8_t ch1mch1_pin_mode, uint8_t ch2mch2_pin_mode, uint8_t ch3mch3_pin_mode);
/* select output disable mode for TIMER1 */
void poc_timer1_output_disable_mode_select(uint8_t ch0_pin_mode, uint8_t ch1_pin_mode, uint8_t ch2_pin_mode, uint8_t ch3_pin_mode);
/* select output disable mode for TIMER2 */
void poc_timer2_output_disable_mode_select(uint8_t ch0_pin_mode, uint8_t ch1_pin_mode, uint8_t ch2_pin_mode, uint8_t ch3_pin_mode);
/* select output disable mode for GPTIMER0 */
void poc_gptimer0_output_disable_mode_select(uint8_t ch0_pin_mode, uint8_t ch1_pin_mode);
/* select output disable mode for GPTIMER1 */
void poc_gptimer1_output_disable_mode_select(uint8_t ch0_pin_mode, uint8_t ch1_pin_mode);

/* initialize POC request struct */
void poc_request_struct_para_init(poc_request_struct *request);
/* request select target timer */
void poc_request_select(poc_request_struct *request, target_timer_enum target_timer);

/* configure comparator disabling request status */
void poc_cmp_dreq_status_config(uint32_t cmp0dreq_status, uint32_t cmp1dreq_status, uint32_t cmp2dreq_status, uint32_t cmp3dreq_status);

/* configure comparator disabling request status for target timer */
void poc_cmp_dreq_status_extended_config(uint32_t cmp0dreq_status, uint32_t cmp1dreq_status, uint32_t cmp2dreq_status, uint32_t cmp3dreq_status,
                                         target_timer_enum target_timer);

/* mask POC_INn input detection */
void poc_input_detection_mask(poc_pin_enum poc_pin, uint32_t mask_source);

/* mask comparator output detection */
void poc_cmp_output_detection_mask(cmp_output_enum cmp_output, uint32_t mask_source);

/* get the POC flag */
FlagStatus poc_flag_get(uint32_t flag);

/* clear the POC flag */
void poc_flag_clear(uint32_t flag);

/* enable POC interrupt */
void poc_interrupt_enable(poc_interrupt_enum interrupt);

/* disable POC interrupt */
void poc_interrupt_disable(poc_interrupt_enum interrupt);

/* get POC interrupt flag */
FlagStatus poc_interrupt_flag_get(uint32_t int_flag);

/* clear POC interrupt flag */
void poc_interrupt_flag_clear(uint32_t int_flag);

#endif /* GD32M53X_POC_H */
