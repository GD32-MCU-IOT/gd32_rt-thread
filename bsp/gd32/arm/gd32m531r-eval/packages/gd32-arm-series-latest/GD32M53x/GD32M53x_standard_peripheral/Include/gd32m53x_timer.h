/*!
    \file    GD32M53X_timer.h
    \brief   definitions for the TIMER

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

#ifndef GD32M53X_TIMER_H
#define GD32M53X_TIMER_H

#include "gd32m53x.h"

#define REGIDX_BIT(regidx, bitpos, value)   (((uint32_t)(regidx) << 24U) | (uint32_t)((bitpos) << 16U) | ((uint32_t)(value)))
#define REG_INDEX(val)                      (((uint32_t)(val) & 0xFF000000U) >> 24U)
#define REG_BIT_POS(val)                    (((uint32_t)(val) & 0x00FF0000U) >> 16U)
#define REG_BIT_NUM(val)                    ((uint32_t)(val) & 0x000000FFU)


/* TIMERx(x=0,1,2,7) definitions */
#define TIMER0                                             TIMER_BASE
#define TIMER1                                             (TIMER_BASE + 0x00001400U)
#define TIMER2                                             (TIMER_BASE + 0x00001800U)
#define TIMER7                                             (TIMER_BASE + 0x00000800U)

/* registers definitions */
#define TIMER_CTL0(timerx)                                 REG32((timerx) + 0x00U)           /*!< TIMER control register 0 */
#define TIMER_CTL1(timerx)                                 REG32((timerx) + 0x04U)           /*!< TIMER control register 1 */
#define TIMER_SMCFG(timerx)                                REG32((timerx) + 0x08U)           /*!< TIMER slave mode configuration register */
#define TIMER_DMAINTEN(timerx)                             REG32((timerx) + 0x0CU)           /*!< TIMER DMA and interrupt enable register */
#define TIMER_INTF(timerx)                                 REG32((timerx) + 0x10U)           /*!< TIMER interrupt flag register */
#define TIMER_SWEVG(timerx)                                REG32((timerx) + 0x14U)           /*!< TIMER software event generation register */
#define TIMER_CHCTL0(timerx)                               REG32((timerx) + 0x18U)           /*!< TIMER channel control register 0 */
#define TIMER_CHCTL1(timerx)                               REG32((timerx) + 0x1CU)           /*!< TIMER channel control register 1 */
#define TIMER_CHCTL2(timerx)                               REG32((timerx) + 0x20U)           /*!< TIMER channel control register 2 */
#define TIMER_CNT(timerx)                                  REG32((timerx) + 0x24U)           /*!< TIMER counter register */
#define TIMER_PSC(timerx)                                  REG32((timerx) + 0x28U)           /*!< TIMER prescaler register */
#define TIMER_CAR(timerx)                                  REG32((timerx) + 0x2CU)           /*!< TIMER counter auto reload register */
#define TIMER_CREP(timerx)                                 REG32((timerx) + 0x30U)           /*!< TIMER counter repetition register */
#define TIMER_CH0CV(timerx)                                REG32((timerx) + 0x34U)           /*!< TIMER channel 0 capture/compare value register */
#define TIMER_CH1CV(timerx)                                REG32((timerx) + 0x38U)           /*!< TIMER channel 1 capture/compare value register */
#define TIMER_CH2CV(timerx)                                REG32((timerx) + 0x3CU)           /*!< TIMER channel 2 capture/compare value register */
#define TIMER_CH3CV(timerx)                                REG32((timerx) + 0x40U)           /*!< TIMER channel 3 capture/compare value register */
#define TIMER_CCHP(timerx)                                 REG32((timerx) + 0x44U)           /*!< TIMER complementary channel protection register */
#define TIMER_MCHCTL0(timerx)                              REG32((timerx) + 0x48U)           /*!< TIMER multi mode channel control register 0 */
#define TIMER_MCHCTL1(timerx)                              REG32((timerx) + 0x4CU)           /*!< TIMER multi mode channel control register 1 */
#define TIMER_MCHCTL2(timerx)                              REG32((timerx) + 0x50U)           /*!< TIMER multi mode channel control register 2 */
#define TIMER_MCH0CV(timerx)                               REG32((timerx) + 0x54U)           /*!< TIMER multi mode channel 0 capture or compare value register */
#define TIMER_MCH1CV(timerx)                               REG32((timerx) + 0x58U)           /*!< TIMER multi mode channel 1 capture or compare value register */
#define TIMER_MCH2CV(timerx)                               REG32((timerx) + 0x5CU)           /*!< TIMER multi mode channel 2 capture or compare value register */
#define TIMER_MCH3CV(timerx)                               REG32((timerx) + 0x60U)           /*!< TIMER multi mode channel 3 capture or compare value register */
#define TIMER_CH0COMV_ADD(timerx)                          REG32((timerx) + 0x64U)           /*!< TIMER channel 0 additional compare value register */
#define TIMER_CH1COMV_ADD(timerx)                          REG32((timerx) + 0x68U)           /*!< TIMER channel 1 additional compare value register */
#define TIMER_CH2COMV_ADD(timerx)                          REG32((timerx) + 0x6CU)           /*!< TIMER channel 2 additional compare value register */
#define TIMER_CH3COMV_ADD(timerx)                          REG32((timerx) + 0x70U)           /*!< TIMER channel 3 additional compare value register */
#define TIMER_CTL2(timerx)                                 REG32((timerx) + 0x74U)           /*!< TIMER control register 2 */
#define TIMER_AFCTL(timerx)                                REG32((timerx) + 0x8CU)           /*!< TIMER alternate function control register */
#define TIMER_IREP(timerx)                                 REG32((timerx) + 0x90U)           /*!< TIMER Interrupt Counter reption register  */
#define TIMER_ADCRCTL(timerx)                              REG32((timerx) + 0x94U)           /*!< TIMER A/D conversion start request control register */
#define TIMER_ADCCR1(timerx)                               REG32((timerx) + 0x98U)           /*!< TIMER ADC trigger compare value register1*/
#define TIMER_ADCCR2(timerx)                               REG32((timerx) + 0x9CU)           /*!< TIMER ADC trigger compare value register2*/
#define TIMER_ADCREP(timerx)                               REG32((timerx) + 0xA0U)           /*!< TIMER ADC counter repetition register */
#define TIMER_ADCTL(timerx)                                REG32((timerx) + 0xACU)           /*!< TIMER ADC contrlol register */
#define TIMER_SHUPM0(timerx)                               REG32((timerx) + 0xC4U)           /*!< TIMER shadow reg update register */
#define TIMER_SHUPM1(timerx)                               REG32((timerx) + 0xC8U)           /*!< TIMER shadow reg update register */
#define TIMER_COUMSEL(timerx)                              REG32((timerx) + 0xCCU)           /*!< TIMER counter overflow or underflow mode selection */
#define TIMER_DMACFG(timerx)                               REG32((timerx) + 0xE0U)           /*!< TIMER DMA configuration register */
#define TIMER_DMATB(timerx)                                REG32((timerx) + 0xE4U)           /*!< TIMER DMA transfer buffer register */
#define TIMER_CFG(timerx)                                  REG32((timerx) + 0xFCU)           /*!< TIMER configuration register */

/* bits definitions */
/* TIMER_CTL0 */
#define TIMER_CTL0_CEN                                     BIT(0)                            /*!< TIMER counter enable */
#define TIMER_CTL0_UPDIS                                   BIT(1)                            /*!< update disable */
#define TIMER_CTL0_UPS                                     BIT(2)                            /*!< update interrupt source */
#define TIMER_CTL0_SPM                                     BIT(3)                            /*!< single pulse mode */
#define TIMER_CTL0_DIR                                     BIT(4)                            /*!< timer counter direction */
#define TIMER_CTL0_CAM                                     BITS(5,6)                         /*!< center-aligned mode selection */
#define TIMER_CTL0_ARSE                                    BIT(7)                            /*!< auto-reload shadow enable */
#define TIMER_CTL0_CKDIV                                   BITS(8,9)                         /*!< clock division */
#define TIMER_CTL0_UPIFBUEN                                BIT(11)                           /*!< UIF bit backup */
#define TIMER_CTL0_INTREPRLD                               BIT(22)                           /*!< Interrupt repeat counter immediate reload */
#define TIMER_CTL0_ETISEL                                  BITS(24,25)                       /*!< Timer external trigger input signal selection */
#define TIMER_CTL0_INTCOSEL                                BITS(28,29)                       /*!< interrupt reption register flow source selection */
#define TIMER_CTL0_UPSSEL                                  BITS(30,31)                       /*!< update event register flow source selection */

/* TIMER_CTL1 */
#define TIMER_CTL1_CCSE                                    BIT(0)                            /*!< commutation control shadow enable */
#define TIMER_CTL1_CCUC                                    (BIT(2) | BITS(30,31))            /*!< commutation control shadow register update control */
#define TIMER_CTL1_DMAS                                    BIT(3)                            /*!< DMA request source selection */
#define TIMER_CTL1_MMC                                     BITS(4,6)                         /*!< master mode control */
#define TIMER_CTL1_TI0S                                    BIT(7)                            /*!< channel 0 trigger input selection(hall mode selection) */
#define TIMER_CTL1_ISO0                                    BIT(8)                            /*!< idle state of channel 0 output */
#define TIMER_CTL1_ISO0N                                   BIT(9)                            /*!< idle state of channel 0 complementary output */
#define TIMER_CTL1_ISO1                                    BIT(10)                           /*!< idle state of channel 1 output */
#define TIMER_CTL1_ISO1N                                   BIT(11)                           /*!< idle state of channel 1 complementary output */
#define TIMER_CTL1_ISO2                                    BIT(12)                           /*!< idle state of channel 2 output */
#define TIMER_CTL1_ISO2N                                   BIT(13)                           /*!< idle state of channel 2 complementary output */
#define TIMER_CTL1_ISO3                                    BIT(14)                           /*!< idle state of channel 3 output */
#define TIMER_CTL1_ISO3N                                   BIT(15)                           /*!< idle state of channel 2 complementary output */

/* TIMER_SMCFG */
#define TIMER_SMCFG_OCRC                                   BIT(3)                            /*!< ouput clear function source selection */
#define TIMER_SMCFG_MSM                                    BIT(7)                            /*!< master-slave mode */
#define TIMER_SMCFG_ETFC                                   BITS(8,11)                        /*!< external trigger filter control */
#define TIMER_SMCFG_ETPSC                                  BITS(12,13)                       /*!< external trigger prescaler */
#define TIMER_SMCFG_SMC1                                   BIT(14)                           /*!< part of SMC for enable external clock mode 1 */
#define TIMER_SMCFG_ETP                                    BIT(15)                           /*!< external trigger polarity */

/* TIMER_DMAINTEN */
#define TIMER_DMAINTEN_UPIE                                BIT(0)                            /*!< update interrupt enable */
#define TIMER_DMAINTEN_CH0IE                               BIT(1)                            /*!< channel 0 capture/compare interrupt enable */
#define TIMER_DMAINTEN_CH1IE                               BIT(2)                            /*!< channel 1 capture/compare interrupt enable */
#define TIMER_DMAINTEN_CH2IE                               BIT(3)                            /*!< channel 2 capture/compare interrupt enable */
#define TIMER_DMAINTEN_CH3IE                               BIT(4)                            /*!< channel 3 capture/compare interrupt enable */
#define TIMER_DMAINTEN_CMTIE                               BIT(5)                            /*!< commutation interrupt request enable */
#define TIMER_DMAINTEN_TRGIE                               BIT(6)                            /*!< trigger interrupt enable */
#define TIMER_DMAINTEN_BRKIE                               BIT(7)                            /*!< break interrupt enable */
#define TIMER_DMAINTEN_UPDEN                               BIT(8)                            /*!< update DMA request enable */
#define TIMER_DMAINTEN_CH0DEN                              BIT(9)                            /*!< channel 0 capture/compare DMA request enable */
#define TIMER_DMAINTEN_CH1DEN                              BIT(10)                           /*!< channel 1 capture/compare DMA request enable */
#define TIMER_DMAINTEN_CH2DEN                              BIT(11)                           /*!< channel 2 capture/compare DMA request enable */
#define TIMER_DMAINTEN_CH3DEN                              BIT(12)                           /*!< channel 3 capture/compare DMA request enable */
#define TIMER_DMAINTEN_CMTDEN                              BIT(13)                           /*!< commutation DMA request enable */
#define TIMER_DMAINTEN_TRGDEN                              BIT(14)                           /*!< trigger DMA request enable */
#define TIMER_DMAINTEN_FLOWIE                              BIT(18)                           /*!< FLOW interrupt enable */
#define TIMER_DMAINTEN_MCH0IE                              BIT(20)                           /*!< multi channel 0 capture/compare interrupt enable */
#define TIMER_DMAINTEN_MCH1IE                              BIT(21)                           /*!< multi channel 1 capture/compare interrupt enable */
#define TIMER_DMAINTEN_MCH2IE                              BIT(22)                           /*!< multi channel 2 capture/compare interrupt enable */
#define TIMER_DMAINTEN_MCH3IE                              BIT(23)                           /*!< multi channel 3 capture/compare interrupt enable */
#define TIMER_DMAINTEN_MCH0DEN                             BIT(24)                           /*!< multi channel 0 capture/compare DMA request enable */
#define TIMER_DMAINTEN_MCH1DEN                             BIT(25)                           /*!< multi channel 1 capture/compare DMA request enable */
#define TIMER_DMAINTEN_MCH2DEN                             BIT(26)                           /*!< multi channel 2 capture/compare DMA request enable */
#define TIMER_DMAINTEN_MCH3DEN                             BIT(27)                           /*!< multi channel 3 capture/compare DMA request enable */
#define TIMER_DMAINTEN_CH0COMADDIE                         BIT(28)                           /*!< channel0 additional capture/compare DMA request enable */
#define TIMER_DMAINTEN_CH1COMADDIE                         BIT(29)                           /*!< channel1 additional capture/compare DMA request enable */
#define TIMER_DMAINTEN_CH2COMADDIE                         BIT(30)                           /*!< channel2 additional capture/compare DMA request enable */
#define TIMER_DMAINTEN_CH3COMADDIE                         BIT(31)                           /*!< channel3 additional capture/compare DMA request enable */

/* TIMER_INTF */
#define TIMER_INTF_UPIF                                    BIT(0)                            /*!< update interrupt flag */
#define TIMER_INTF_CH0IF                                   BIT(1)                            /*!< channel 0 capture/compare interrupt flag */
#define TIMER_INTF_CH1IF                                   BIT(2)                            /*!< channel 1 capture/compare interrupt flag */
#define TIMER_INTF_CH2IF                                   BIT(3)                            /*!< channel 2 capture/compare interrupt flag */
#define TIMER_INTF_CH3IF                                   BIT(4)                            /*!< channel 3 capture/compare interrupt flag */
#define TIMER_INTF_CMTIF                                   BIT(5)                            /*!< channel commutation interrupt flag */
#define TIMER_INTF_TRGIF                                   BIT(6)                            /*!< trigger interrupt flag */
#define TIMER_INTF_BRKIF                                   BIT(7)                            /*!< break interrupt flag */
#define TIMER_INTF_CH0OF                                   BIT(9)                            /*!< channel 0 overcapture flag */
#define TIMER_INTF_CH1OF                                   BIT(10)                           /*!< channel 1 overcapture flag */
#define TIMER_INTF_CH2OF                                   BIT(11)                           /*!< channel 2 overcapture flag */
#define TIMER_INTF_CH3OF                                   BIT(12)                           /*!< channel 3 overcapture flag */
#define TIMER_INTF_SYSBIF                                  BIT(13)                           /*!< system error flag */
#define TIMER_INTF_UNDERFLOWIF                             BIT(18)                           /*!< counter under flow flag */
#define TIMER_INTF_OVERFLOWIF                              BIT(19)                           /*!< counter over flow flag */
#define TIMER_INTF_MCH0IF                                  BIT(20)                           /*!< multi mode channel 0 capture or compare interrupt flag */
#define TIMER_INTF_MCH1IF                                  BIT(21)                           /*!< multi mode channel 1 capture or compare interrupt flag */
#define TIMER_INTF_MCH2IF                                  BIT(22)                           /*!< multi mode channel 2 capture or compare interrupt flag */
#define TIMER_INTF_MCH3IF                                  BIT(23)                           /*!< multi mode channel 3 capture or compare interrupt flag */
#define TIMER_INTF_MCH0OF                                  BIT(24)                           /*!< multi mode channel 0 over capture flag */
#define TIMER_INTF_MCH1OF                                  BIT(25)                           /*!< multi mode channel 1 over capture flag */
#define TIMER_INTF_MCH2OF                                  BIT(26)                           /*!< multi mode channel 2 over capture flag */
#define TIMER_INTF_MCH3OF                                  BIT(27)                           /*!< multi mode channel 3 over capture flag */
#define TIMER_INTF_CH0COMADDIF                             BIT(28)                           /*!< channel 0 additional compare interrupt flag */
#define TIMER_INTF_CH1COMADDIF                             BIT(29)                           /*!< channel 1 additional compare interrupt flag */
#define TIMER_INTF_CH2COMADDIF                             BIT(30)                           /*!< channel 2 additional compare interrupt flag */
#define TIMER_INTF_CH3COMADDIF                             BIT(31)                           /*!< channel 3 additional compare interrupt flag */

/* TIMER_SWEVG */
#define TIMER_SWEVG_UPG                                    BIT(0)                            /*!< update event generate */
#define TIMER_SWEVG_CH0G                                   BIT(1)                            /*!< channel 0 capture or compare event generation */
#define TIMER_SWEVG_CH1G                                   BIT(2)                            /*!< channel 1 capture or compare event generation */
#define TIMER_SWEVG_CH2G                                   BIT(3)                            /*!< channel 2 capture or compare event generation */
#define TIMER_SWEVG_CH3G                                   BIT(4)                            /*!< channel 3 capture or compare event generation */
#define TIMER_SWEVG_CMTG                                   BIT(5)                            /*!< channel commutation event generation */
#define TIMER_SWEVG_TRGG                                   BIT(6)                            /*!< trigger event generation */
#define TIMER_SWEVG_BRKG                                   BIT(7)                            /*!< break event generation */
#define TIMER_SWEVG_MCH0G                                  BIT(20)                           /*!< multi mode channel 0 capture or compare event generation */
#define TIMER_SWEVG_MCH1G                                  BIT(21)                           /*!< multi mode channel 1 capture or compare event generation */
#define TIMER_SWEVG_MCH2G                                  BIT(22)                           /*!< multi mode channel 2 capture or compare event generation */
#define TIMER_SWEVG_MCH3G                                  BIT(23)                           /*!< multi mode channel 3 capture or compare event generation */
#define TIMER_SWEVG_CH0COMADDG                             BIT(28)                           /*!< channel 0 additional compare event generation */
#define TIMER_SWEVG_CH1COMADDG                             BIT(29)                           /*!< channel 1 additional compare event generation */
#define TIMER_SWEVG_CH2COMADDG                             BIT(30)                           /*!< channel 2 additional compare event generation */
#define TIMER_SWEVG_CH3COMADDG                             BIT(31)                           /*!< channel 3 additional compare event generation */

/* TIMER_CHCTL0 */
/* output compare mode */
#define TIMER_CHCTL0_CH0MS                                 (BITS(0,1) | BIT(30))             /*!< channel 0 mode selection */
#define TIMER_CHCTL0_CH0COMFEN                             BIT(2)                            /*!< channel 0 output compare fast enable */
#define TIMER_CHCTL0_CH0COMSEN                             BIT(3)                            /*!< channel 0 output compare shadow enable */
#define TIMER_CHCTL0_CH0COMCTL                             (BITS(4,6) | BIT(16))             /*!< channel 0 output compare control */
#define TIMER_CHCTL0_CH0COMCEN                             BIT(7)                            /*!< channel 0 output compare clear enable */
#define TIMER_CHCTL0_CH1MS                                 (BITS(8,9) | BIT(31))             /*!< channel 1 mode selection */
#define TIMER_CHCTL0_CH1COMFEN                             BIT(10)                           /*!< channel 1 output compare fast enable */
#define TIMER_CHCTL0_CH1COMSEN                             BIT(11)                           /*!< channel 1 output compare shadow enable */
#define TIMER_CHCTL0_CH1COMCTL                             (BITS(12,14) | BIT(24))           /*!< channel 1 output compare control  */
#define TIMER_CHCTL0_CH1COMCEN                             BIT(15)                           /*!< channel 1 output compare clear enable */
#define TIMER_CHCTL0_CH0COMADDSEN                          BIT(28)                           /*!< channel 0 additional compare output shadow enable */
#define TIMER_CHCTL0_CH1COMADDSEN                          BIT(29)                           /*!< channel 1 additional compare output shadow enable */
/* input capture mode */
#define TIMER_CHCTL0_CH0CAPPSC                             BITS(2,3)                         /*!< channel 0 input capture prescaler */
#define TIMER_CHCTL0_CH0CAPFLT                             BITS(4,7)                         /*!< channel 0 input capture filter control */
#define TIMER_CHCTL0_CH1CAPPSC                             BITS(10,11)                       /*!< channel 1 input capture prescaler */
#define TIMER_CHCTL0_CH1CAPFLT                             BITS(12,15)                       /*!< channel 1 input capture filter control */

/* TIMER_CHCTL1 */
/* output compare mode */
#define TIMER_CHCTL1_CH2MS                                 (BITS(0,1) | BIT(30))             /*!< channel 2 mode selection */
#define TIMER_CHCTL1_CH2COMFEN                             BIT(2)                            /*!< channel 2 output compare fast enable */
#define TIMER_CHCTL1_CH2COMSEN                             BIT(3)                            /*!< channel 2 output compare shadow enable */
#define TIMER_CHCTL1_CH2COMCTL                             (BITS(4,6) | BIT(16))             /*!< channel 2 output compare control  */
#define TIMER_CHCTL1_CH2COMCEN                             BIT(7)                            /*!< channel 2 output compare clear enable */
#define TIMER_CHCTL1_CH3MS                                 (BITS(8,9) | BIT(31))             /*!< channel 3 mode selection */
#define TIMER_CHCTL1_CH3COMFEN                             BIT(10)                           /*!< channel 3 output compare fast enable */
#define TIMER_CHCTL1_CH3COMSEN                             BIT(11)                           /*!< channel 3 output compare shadow enable */
#define TIMER_CHCTL1_CH3COMCTL                             (BITS(12,14) | BIT(24))           /*!< channel 3 output compare control  */
#define TIMER_CHCTL1_CH3COMCEN                             BIT(15)                           /*!< channel 3 output compare clear enable */
#define TIMER_CHCTL1_CH2COMADDSEN                          BIT(28)                           /*!< channel 2 additional compare output shadow enable */
#define TIMER_CHCTL1_CH3COMADDSEN                          BIT(29)                           /*!< channel 3 additional compare output shadow enable */
/* input capture mode */
#define TIMER_CHCTL1_CH2CAPPSC                             BITS(2,3)                         /*!< channel 2 input capture prescaler */
#define TIMER_CHCTL1_CH2CAPFLT                             BITS(4,7)                         /*!< channel 2 input capture filter control */
#define TIMER_CHCTL1_CH3CAPPSC                             BITS(10,11)                       /*!< channel 3 input capture prescaler */
#define TIMER_CHCTL1_CH3CAPFLT                             BITS(12,15)                       /*!< channel 3 input capture filter control */

/* TIMER_CHCTL2 */
#define TIMER_CHCTL2_CH0EN                                 BIT(0)                            /*!< channel 0 capture/compare function enable */
#define TIMER_CHCTL2_CH0P                                  BIT(1)                            /*!< channel 0 capture/compare function polarity */
#define TIMER_CHCTL2_MCH0EN                                BIT(2)                            /*!< multi mode channel 0 capture or compare function enable */
#define TIMER_CHCTL2_MCH0P                                 BIT(3)                            /*!< multi mode channel 0 complementary output polarity */
#define TIMER_CHCTL2_CH1EN                                 BIT(4)                            /*!< channel 1 capture/compare function enable */
#define TIMER_CHCTL2_CH1P                                  BIT(5)                            /*!< channel 1 capture/compare function polarity */
#define TIMER_CHCTL2_MCH1EN                                BIT(6)                            /*!< multi mode channel 1 capture or compare function enable */
#define TIMER_CHCTL2_MCH1P                                 BIT(7)                            /*!< multi mode channel 1 complementary output polarity */
#define TIMER_CHCTL2_CH2EN                                 BIT(8)                            /*!< channel 2 capture/compare function enable */
#define TIMER_CHCTL2_CH2P                                  BIT(9)                            /*!< channel 2 capture/compare function polarity */
#define TIMER_CHCTL2_MCH2EN                                BIT(10)                           /*!< multi mode channel 2 capture or compare function enable */
#define TIMER_CHCTL2_MCH2P                                 BIT(11)                           /*!< multi mode channel 2 complementary output polarity */
#define TIMER_CHCTL2_CH3EN                                 BIT(12)                           /*!< channel 3 capture/compare function enable */
#define TIMER_CHCTL2_CH3P                                  BIT(13)                           /*!< channel 3 capture/compare function polarity */
#define TIMER_CHCTL2_MCH3EN                                BIT(14)                           /*!< multi mode channel 3 capture or compare function enable */
#define TIMER_CHCTL2_MCH3P                                 BIT(15)                           /*!< multi mode channel 3 complementary output polarity */
#define TIMER_CHCTL2_CH0PERFOREN                           BIT(28)                           /*!< Channel 0 match moment O0CPRE level (composite/asymmetric PWM mode) */
#define TIMER_CHCTL2_CH1PERFOREN                           BIT(29)                           /*!< Channel 1 match moment O0CPRE level (composite/asymmetric PWM mode) */
#define TIMER_CHCTL2_CH2PERFOREN                           BIT(30)                           /*!< Channel 2 match moment O0CPRE level (composite/asymmetric PWM mode) */
#define TIMER_CHCTL2_CH3PERFOREN                           BIT(31)                           /*!< Channel 3 match moment O0CPRE level (composite/asymmetric PWM mode) */

/* TIMER_CNT */
#define TIMER_CNT_CNT                                      BITS(0,15)                        /*!< 16 bit timer counter */
#define TIMER_CNT_UPIFBU                                   BIT(31)                           /*!< UPIF bit back up */

/* TIMER_PSC */
#define TIMER_PSC_PSC                                      BITS(0,15)                        /*!< prescaler value of the counter clock */

/* TIMER_CAR */
#define TIMER_CAR_CARL                                     BITS(0,15)                        /*!< 16 bit counter auto reload value */

/* TIMER_CREP */
#define TIMER_CREP_CREP                                    BITS(0,7)                         /*!< counter repetition value */

/* TIMER_CH0CV */
#define TIMER_CH0CV_CH0VAL                                 BITS(0,15)                        /*!< 16 bit capture/compare value of channel 0 */

/* TIMER_CH1CV */
#define TIMER_CH1CV_CH1VAL                                 BITS(0,15)                        /*!< 16 bit capture/compare value of channel 1 */

/* TIMER_CH2CV */
#define TIMER_CH2CV_CH2VAL                                 BITS(0,15)                        /*!< 16 bit capture/compare value of channel 2 */

/* TIMER_CH3CV */
#define TIMER_CH3CV_CH3VAL                                 BITS(0,15)                        /*!< 16 bit capture/compare value of channel 3 */

/* TIMER_CCHP */
#define TIMER_CCHP_DTCFG                                   BITS(0,7)                         /*!< dead time configure */
#define TIMER_CCHP_PROT                                    BITS(8,9)                         /*!< complementary register protect control */
#define TIMER_CCHP_IOS                                     BIT(10)                           /*!< idle mode off-state configure */
#define TIMER_CCHP_ROS                                     BIT(11)                           /*!< run mode off-state configure */
#define TIMER_CCHP_BRKEN                                   BIT(12)                           /*!< break enable */
#define TIMER_CCHP_BRKP                                    BIT(13)                           /*!< break polarity */
#define TIMER_CCHP_OAEN                                    BIT(14)                           /*!< output automatic enable */
#define TIMER_CCHP_POEN                                    BIT(15)                           /*!< primary output enable */
#define TIMER_CCHP_BRKF                                    BITS(16,19)                       /*!< break signal filter */

/* TIMER_MCHCTL0 */
/* output compare mode */
#define TIMER_MCHCTL0_MCH0MS                               (BITS(0,1) | BIT(30))             /*!< multi mode channel 0 mode selection */
#define TIMER_MCHCTL0_MCH0COMFEN                           BIT(2)                            /*!< multi mode channel 0 output compare fast enable */
#define TIMER_MCHCTL0_MCH0COMSEN                           BIT(3)                            /*!< multi mode channel 0 output compare shadow enable */
#define TIMER_MCHCTL0_MCH0COMCTL                           BITS(4,6)                         /*!< multi mode channel 0 output compare control  */
#define TIMER_MCHCTL0_MCH0COMCEN                           BIT(7)                            /*!< multi mode channel 0 output compare clear enable */
#define TIMER_MCHCTL0_MCH1MS                               (BITS(8,9) | BIT(31))             /*!< multi mode channel 1 mode selection */
#define TIMER_MCHCTL0_MCH1COMFEN                           BIT(10)                           /*!< multi mode channel 1 output compare fast enable */
#define TIMER_MCHCTL0_MCH1COMSEN                           BIT(11)                           /*!< multi mode channel 1 output compare shadow enable */
#define TIMER_MCHCTL0_MCH1COMCTL                           BITS(12,14)                       /*!< multi mode channel 1 output compare control  */
#define TIMER_MCHCTL0_MCH1COMCEN                           BIT(15)                           /*!< multi mode channel 1 output compare clear enable */
/* input capture mode */
#define TIMER_MCHCTL0_MCH0CAPPSC                           BITS(2,3)                         /*!< multi mode channel 0 input capture prescaler */
#define TIMER_MCHCTL0_MCH0CAPFLT                           BITS(4,7)                         /*!< multi mode channel 0 input capture filter control */
#define TIMER_MCHCTL0_MCH1CAPPSC                           BITS(10,11)                       /*!< multi mode channel 1 input capture prescaler */
#define TIMER_MCHCTL0_MCH1CAPFLT                           BITS(12,15)                       /*!< multi mode channel 1 input capture filter control */

/* TIMER_MCHCTL1 */
/* output compare mode */
#define TIMER_MCHCTL1_MCH2MS                               (BITS(0,1) | BIT(30))             /*!< multi mode channel 2 mode selection */
#define TIMER_MCHCTL1_MCH2COMFEN                           BIT(2)                            /*!< multi mode channel 2 output compare fast enable */
#define TIMER_MCHCTL1_MCH2COMSEN                           BIT(3)                            /*!< multi mode channel 2 output compare shadow enable */
#define TIMER_MCHCTL1_MCH2COMCTL                           BITS(4,6)                         /*!< multi mode channel 2 output compare control  */
#define TIMER_MCHCTL1_MCH2COMCEN                           BIT(7)                            /*!< multi mode channel 2 output compare clear enable */
#define TIMER_MCHCTL1_MCH3MS                               (BITS(8,9) | BIT(31))             /*!< multi mode channel 3 mode selection */
#define TIMER_MCHCTL1_MCH3COMFEN                           BIT(10)                           /*!< multi mode channel 3 output compare fast enable */
#define TIMER_MCHCTL1_MCH3COMSEN                           BIT(11)                           /*!< multi mode channel 3 output compare shadow enable */
#define TIMER_MCHCTL1_MCH3COMCTL                           BITS(12,14)                       /*!< multi mode channel 3 output compare control  */
#define TIMER_MCHCTL1_MCH3COMCEN                           BIT(15)                           /*!< multi mode channel 3 output compare clear enable */
/* input capture mode */
#define TIMER_MCHCTL1_MCH2CAPPSC                           BITS(2,3)                         /*!< multi mode channel 2 input capture prescaler */
#define TIMER_MCHCTL1_MCH2CAPFLT                           BITS(4,7)                         /*!< multi mode channel 2 input capture filter control */
#define TIMER_MCHCTL1_MCH3CAPPSC                           BITS(10,11)                       /*!< multi mode channel 3 input capture prescaler */
#define TIMER_MCHCTL1_MCH3CAPFLT                           BITS(12,15)                       /*!< multi mode channel 3 input capture filter control */

/* TIMER_MCHCTL2 */
#define TIMER_MCHCTL2_MCH0FP                               BITS(0,1)                         /*!< multi mode channel 0 capture or compare function polarity */
#define TIMER_MCHCTL2_MCH1FP                               BITS(2,3)                         /*!< multi mode channel 1 capture or compare function polarity */
#define TIMER_MCHCTL2_MCH2FP                               BITS(4,5)                         /*!< multi mode channel 2 capture or compare function polarity */
#define TIMER_MCHCTL2_MCH3FP                               BITS(6,7)                         /*!< multi mode channel 3 capture or compare function polarity */

/* TIMER_MCH0CV */
#define TIMER_MCH0CV_MCH0VAL                               BITS(0,15)                        /*!< 16 bit capture or compare value of multi mode channel 0 */

/* TIMER_MCH1CV */
#define TIMER_MCH1CV_MCH1VAL                               BITS(0,15)                        /*!< 16 bit capture or compare value of multi mode channel 1 */

/* TIMER_MCH2CV */
#define TIMER_MCH2CV_MCH2VAL                               BITS(0,15)                        /*!< 16 bit capture or compare value of multi mode channel 2 */

/* TIMER_MCH3CV */
#define TIMER_MCH3CV_MCH3VAL                               BITS(0,15)                        /*!< 16 bit capture or compare value of multi mode channel 3 */

/* TIMER_CH0COMV_ADD */
#define TIMER_CH0COMV_ADD_CH0COMVAL_ADD                    BITS(0,15)                        /*!< additional compare value of channel 0 */

/* TIMER_CH1COMV_ADD */
#define TIMER_CH1COMV_ADD_CH1COMVAL_ADD                    BITS(0,15)                        /*!< additional compare value of channel 1 */

/* TIMER_CH2COMV_ADD */
#define TIMER_CH2COMV_ADD_CH2COMVAL_ADD                    BITS(0,15)                        /*!< additional compare value of channel 2 */

/* TIMER_CH3COMV_ADD */
#define TIMER_CH3COMV_ADD_CH3COMVAL_ADD                    BITS(0,15)                        /*!< additional compare value of channel 3 */

/*TIMER_CTL2*/
#define TIMER_CTL2_CH0OMPSEL                               BITS(8,9)                         /*!< channel 0 output march pulse select */
#define TIMER_CTL2_CH1OMPSEL                               BITS(10,11)                       /*!< channel 1 output march pulse select */
#define TIMER_CTL2_CH2OMPSEL                               BITS(12,13)                       /*!< channel 2 output march pulse select */
#define TIMER_CTL2_CH3OMPSEL                               BITS(14,15)                       /*!< channel 3 output march pulse select */
#define TIMER_CTL2_MCH0MSEL                                BITS(20,21)                       /*!< multi mode channel 0 mode select */
#define TIMER_CTL2_MCH1MSEL                                BITS(22,23)                       /*!< multi mode channel 1 mode select */
#define TIMER_CTL2_MCH2MSEL                                BITS(24,25)                       /*!< multi mode channel 2 mode select */
#define TIMER_CTL2_MCH3MSEL                                BITS(26,27)                       /*!< multi mode channel 3 mode select */

/* TIMER_AFCTL*/
#define TIMER_AFCTL_BRKIN0EN                               BIT(0)                            /*!< BREAK PIN  input enable */
#define TIMER_AFCTL_BRKCMP0EN                              BIT(1)                            /*!< BREAK CMP0 input enbale */
#define TIMER_AFCTL_BRKCMP1EN                              BIT(2)                            /*!< BREAK CMP1 input enbale */
#define TIMER_AFCTL_BRKCMP2EN                              BIT(3)                            /*!< BREAK CMP2 input enbale */
#define TIMER_AFCTL_BRKCMP3EN                              BIT(4)                            /*!< BREAK CMP3 input enbale */
#define TIMER_AFCTL_BRKIN0P                                BIT(8)                            /*!< BREAK PIN  input polarity */
#define TIMER_AFCTL_BRKCMP0P                               BIT(9)                            /*!< BREAK CMP0 input polarity */
#define TIMER_AFCTL_BRKCMP1P                               BIT(10)                           /*!< BREAK CMP1 input polarity */
#define TIMER_AFCTL_BRKCMP2P                               BIT(11)                           /*!< BREAK CMP2 input polarity */
#define TIMER_AFCTL_BRKCMP3P                               BIT(12)                           /*!< BREAK CMP3 input polarity */
#define TIMER_AFCTL_OCRINSEL                               BITS(16,18)                       /*!< ocref clr input source selection */

/* TIMER_IREP*/
#define TIMER_IREP_IREP                                    BIT(0,7)                          /*!< interrupt reption value */

/* TIMER_ADCRCTL*/
#define TIMER_ADCRCTL_ADT2DWGTEN                           BIT(4)                            /*!< the CNT down-count TIMERx_TRGB enable */
#define TIMER_ADCRCTL_ADT2UPGTEN                           BIT(5)                            /*!< the CNT up-count TIMERx_TRGB enable */
#define TIMER_ADCRCTL_ADT1DWGTEN                           BIT(6)                            /*!< the CNT down-count TIMERx_TRGA enable */
#define TIMER_ADCRCTL_ADT1UPGTEN                           BIT(7)                            /*!< the CNT up-count TIMERx_TRGA enable */

/*TIMER_ADCCR1*/
#define TIMER_ADCCR1_ADTCV1                                BITS(0,15)                        /*!< ADC event compare1 value */

/*TIMER_ADCCR2*/
#define TIMER_ADCCR2_ADTCV2                                BITS(0,15)                        /*!< ADC event compare2 value */

/*TIMER_ADCREP*/
#define TIMER_ADCREP_ADCREPA                               BITS(0,3)                         /*!< ADC TIMERx_TRGA repeat count setting */
#define TIMER_ADCREP_ADCREPB                               BITS(4,7)                         /*!< ADC TIMERx_TRGB repeat count setting */
#define TIMER_ADCREP_ADCREPAB                              BITS(8,11)                        /*!< ADC TIMERx_TRGAB repeat count setting */

/*TIMER_ADCTL*/
#define TIMER_ADCTL_ADCREPAMD                              BIT(0)                            /*!< ADC TIMERx_TRGA repeat counter decrement mode setting */
#define TIMER_ADCTL_ADCREPBMD                              BIT(1)                            /*!< ADC TIMERx_TRGB repeat counter decrement mode setting */
#define TIMER_ADCTL_ADTSUF                                 BIT(6)                            /*!< ADC trigger signal TIMERx_TRGUF enable when TIMERx_CNT underflow */
#define TIMER_ADCTL_ADTSOF                                 BIT(7)                            /*!< ADC trigger signal TIMERx_TRGOF enable when TIMERx_CNT overflow */
#define TIMER_ADCTL_ADTPREEN1                              BIT(8)                            /*!< ADTCV1[15:0] preload enable */
#define TIMER_ADCTL_ADTPREEN2                              BIT(9)                            /*!< ADTCV2[15:0] preload enable */
#define TIMER_ADCTL_ADREPRLD                               BIT(15)                           /*!< ADC repeat count reload immediately */

/*TIMER_SHUPM0*/
#define TIMER_SHUPM0_CH0CVUPSEL                            BITS(0,2)                         /*!< Channel 0 capture/compare value update mode selection */
#define TIMER_SHUPM0_CH0COMV_ADDUPSEL                      BITS(3,5)                         /*!< Channel 0 additional comparison value update mode selection */
#define TIMER_SHUPM0_CH1CVUPSEL                            BITS(6,8)                         /*!< Channel 1 capture/compare value update mode selection */
#define TIMER_SHUPM0_CH1COMV_ADDUPSEL                      BITS(9,11)                        /*!< Channel 1 additional comparison value update mode selection */
#define TIMER_SHUPM0_CH2CVUPSEL                            BITS(12,14)                       /*!< Channel 2 capture/compare value update mode selection */
#define TIMER_SHUPM0_CH2COMV_ADDUPSEL                      BITS(16,18)                       /*!< Channel 2 additional comparison value update mode selection */
#define TIMER_SHUPM0_CH3CVUPSEL                            BITS(19,21)                       /*!< Channel 3 capture/compare value update mode selection */
#define TIMER_SHUPM0_CH3COMV_ADDUPSEL                      BITS(22,24)                       /*!< Channel 3 additional comparison value update mode selection */
#define TIMER_SHUPM0_ADCCR1UPSEL                           BITS(26,27)                       /*!< ADC triggered comparison value 1 update mode selection */
#define TIMER_SHUPM0_ADCCR2UPSEL                           BITS(28,29)                       /*!< ADC triggered comparison value 2 update mode selection */
#define TIMER_SHUPM0_CARUPSEL                              BITS(30,31)                       /*!< the counter auto reload value update mode selection */

/*TIMER_SHUPM1*/
#define TIMER_SHUPM1_MCH0CVUPSEL                           BITS(0,1)                         /*!< multi mode channel 0 capture/compare value update mode selection */
#define TIMER_SHUPM1_MCH1CVUPSEL                           BITS(2,3)                         /*!< multi mode channel 1 capture/compare value update mode selection */
#define TIMER_SHUPM1_MCH2CVUPSEL                           BITS(4,5)                         /*!< multi mode channel 2 capture/compare value update mode selection */
#define TIMER_SHUPM1_MCH3CVUPSEL                           BITS(6,7)                         /*!< multi mode channel 3 capture/compare value update mode selection */

/* TIMER_COUMSEL */
#define TIMER_COUMSEL_BRKAUMS                              BITS(2,3)                         /*!< break automatic output function mode selection */

/* TIMER_DMACFG */
#define TIMER_DMACFG_DMATA                                 BITS(0,5)                         /*!< DMA transfer access start address */
#define TIMER_DMACFG_DMATC                                 BITS(8,13)                        /*!< DMA transfer count */

/* TIMER_DMATB */
#define TIMER_DMATB_DMATB                                  BITS(0,31)                        /*!< DMA transfer buffer address */

/* TIMER_CFG */
#define TIMER_CFG_OUTSEL                                   BIT(0)                            /*!< the output value selection */
#define TIMER_CFG_CHVSEL                                   BIT(1)                            /*!< write CHxVAL register selection */

/* constants definitions */
/* TIMER init parameter struct definitions */
typedef struct {
    uint16_t prescaler;                                                                      /*!< prescaler value */
    uint16_t alignedmode;                                                                    /*!< aligned mode */
    uint16_t counterdirection;                                                               /*!< counter direction */
    uint32_t period;                                                                         /*!< period value */
    uint16_t clockdivision;                                                                  /*!< clock division value */
    uint8_t  repetitioncounter;                                                              /*!< the counter repetition value */
} timer_parameter_struct;

/* break parameter struct definitions */
typedef struct {
    uint16_t runoffstate;                                                                    /*!< run mode off-state */
    uint16_t ideloffstate;                                                                   /*!< idle mode off-state */
    uint16_t deadtime;                                                                       /*!< dead time */
    uint16_t breakpolarity;                                                                  /*!< break polarity */
    uint16_t outputautostate;                                                                /*!< output automatic enable */
    uint16_t protectmode;                                                                    /*!< complementary register protect control */
    uint16_t breakstate;                                                                     /*!< break enable */
    uint16_t breakfilter;                                                                    /*!< break filter */
} timer_break_parameter_struct;

/* channel output parameter struct definitions */
typedef struct {
    uint16_t outputstate;                                                                    /*!< channel output state */
    uint16_t outputnstate;                                                                   /*!< channel complementary output state */
    uint16_t ocpolarity;                                                                     /*!< channel output polarity */
    uint16_t ocnpolarity;                                                                    /*!< channel complementary output polarity */
    uint16_t ocidlestate;                                                                    /*!< idle state of channel output */
    uint16_t ocnidlestate;                                                                   /*!< idle state of channel complementary output */
} timer_oc_parameter_struct;

/* multi mode channel output parameter struct definitions */
typedef struct {
    uint16_t outputmode;                                                                     /*!< multi mode channel output mode selection */
    uint16_t outputstate;                                                                    /*!< multi mode channel output state */
    uint16_t ocpolarity;                                                                     /*!< multi mode channel output polarity */
} timer_omc_parameter_struct;

/* channel input parameter struct definitions */
typedef struct {
    uint16_t icpolarity;                                                                     /*!< channel input polarity */
    uint16_t icselection;                                                                    /*!< channel input mode selection */
    uint16_t icprescaler;                                                                    /*!< channel input capture prescaler */
    uint16_t icfilter;                                                                       /*!< channel input capture filter control */
} timer_ic_parameter_struct;

/* TIMER interrupt enable or disable */
#define TIMER_INT_UP                                       TIMER_DMAINTEN_UPIE               /*!< update interrupt */
#define TIMER_INT_CH0                                      TIMER_DMAINTEN_CH0IE              /*!< channel 0 capture or compare interrupt */
#define TIMER_INT_CH1                                      TIMER_DMAINTEN_CH1IE              /*!< channel 1 capture or compare interrupt */
#define TIMER_INT_CH2                                      TIMER_DMAINTEN_CH2IE              /*!< channel 2 capture or compare interrupt */
#define TIMER_INT_CH3                                      TIMER_DMAINTEN_CH3IE              /*!< channel 3 capture or compare interrupt */
#define TIMER_INT_CMT                                      TIMER_DMAINTEN_CMTIE              /*!< channel commutation interrupt flag */
#define TIMER_INT_TRG                                      TIMER_DMAINTEN_TRGIE              /*!< trigger interrupt */
#define TIMER_INT_BRK                                      TIMER_DMAINTEN_BRKIE              /*!< break interrupt */
#define TIMER_INT_FLOW                                     TIMER_DMAINTEN_FLOWIE             /*!< flow interrupt */
#define TIMER_INT_MCH0                                     TIMER_DMAINTEN_MCH0IE             /*!< multi mode channel 0 capture or compare interrupt */
#define TIMER_INT_MCH1                                     TIMER_DMAINTEN_MCH1IE             /*!< multi mode channel 1 capture or compare interrupt */
#define TIMER_INT_MCH2                                     TIMER_DMAINTEN_MCH2IE             /*!< multi mode channel 2 capture or compare interrupt */
#define TIMER_INT_MCH3                                     TIMER_DMAINTEN_MCH3IE             /*!< multi mode channel 3 capture or compare interrupt */
#define TIMER_INT_CH0COMADD                                TIMER_DMAINTEN_CH0COMADDIE        /*!< channel 0 additional compare interrupt */
#define TIMER_INT_CH1COMADD                                TIMER_DMAINTEN_CH1COMADDIE        /*!< channel 1 additional compare interrupt */
#define TIMER_INT_CH2COMADD                                TIMER_DMAINTEN_CH2COMADDIE        /*!< channel 2 additional compare interrupt */
#define TIMER_INT_CH3COMADD                                TIMER_DMAINTEN_CH3COMADDIE        /*!< channel 3 additional compare interrupt */

/* TIMER interrupt flag */
#define TIMER_INT_FLAG_UP                                  TIMER_INTF_UPIF                   /*!< update interrupt flag */
#define TIMER_INT_FLAG_CH0                                 TIMER_INTF_CH0IF                  /*!< channel 0 interrupt flag */
#define TIMER_INT_FLAG_CH1                                 TIMER_INTF_CH1IF                  /*!< channel 1 interrupt flag */
#define TIMER_INT_FLAG_CH2                                 TIMER_INTF_CH2IF                  /*!< channel 2 interrupt flag */
#define TIMER_INT_FLAG_CH3                                 TIMER_INTF_CH3IF                  /*!< channel 3 interrupt flag */
#define TIMER_INT_FLAG_CMT                                 TIMER_INTF_CMTIF                  /*!< channel commutation interrupt flag */
#define TIMER_INT_FLAG_TRG                                 TIMER_INTF_TRGIF                  /*!< trigger interrupt flag */
#define TIMER_INT_FLAG_BRK                                 TIMER_INTF_BRKIF                  /*!< break interrupt flag */
#define TIMER_INT_FLAG_SYSB                                TIMER_INTF_SYSBIF                 /*!< system source break interrupt flag */
#define TIMER_INT_FLAG_UNDERFLOW                           TIMER_INTF_UNDERFLOWIF            /*!< TIMER counter underflow interrupt flag */
#define TIMER_INT_FLAG_OVERFLOW                            TIMER_INTF_OVERFLOWIF             /*!< TIMER counter overflow interrupt flag */
#define TIMER_INT_FLAG_MCH0                                TIMER_INTF_MCH0IF                 /*!< multi mode channel 0 capture or compare interrupt flag */
#define TIMER_INT_FLAG_MCH1                                TIMER_INTF_MCH1IF                 /*!< multi mode channel 1 capture or compare interrupt flag */
#define TIMER_INT_FLAG_MCH2                                TIMER_INTF_MCH2IF                 /*!< multi mode channel 2 capture or compare interrupt flag */
#define TIMER_INT_FLAG_MCH3                                TIMER_INTF_MCH3IF                 /*!< multi mode channel 3 capture or compare interrupt flag */
#define TIMER_INT_FLAG_CH0COMADD                           TIMER_INTF_CH0COMADDIF            /*!< channel 0 additional compare interrupt flag */
#define TIMER_INT_FLAG_CH1COMADD                           TIMER_INTF_CH1COMADDIF            /*!< channel 1 additional compare interrupt flag */
#define TIMER_INT_FLAG_CH2COMADD                           TIMER_INTF_CH2COMADDIF            /*!< channel 2 additional compare interrupt flag */
#define TIMER_INT_FLAG_CH3COMADD                           TIMER_INTF_CH3COMADDIF            /*!< channel 3 additional compare interrupt flag */

/* TIMER flag */
#define TIMER_FLAG_UP                                      TIMER_INTF_UPIF                   /*!< update flag */
#define TIMER_FLAG_CH0                                     TIMER_INTF_CH0IF                  /*!< channel 0 capture or compare flag */
#define TIMER_FLAG_CH1                                     TIMER_INTF_CH1IF                  /*!< channel 1 capture or compare flag */
#define TIMER_FLAG_CH2                                     TIMER_INTF_CH2IF                  /*!< channel 2 capture or compare flag */
#define TIMER_FLAG_CH3                                     TIMER_INTF_CH3IF                  /*!< channel 3 capture or compare flag */
#define TIMER_FLAG_CMT                                     TIMER_INTF_CMTIF                  /*!< channel commutation flag */
#define TIMER_FLAG_TRG                                     TIMER_INTF_TRGIF                  /*!< trigger flag */
#define TIMER_FLAG_BRK                                     TIMER_INTF_BRKIF                  /*!< break flag */
#define TIMER_FLAG_CH0O                                    TIMER_INTF_CH0OF                  /*!< channel 0 overcapture flag */
#define TIMER_FLAG_CH1O                                    TIMER_INTF_CH1OF                  /*!< channel 1 overcapture flag */
#define TIMER_FLAG_CH2O                                    TIMER_INTF_CH2OF                  /*!< channel 2 overcapture flag */
#define TIMER_FLAG_CH3O                                    TIMER_INTF_CH3OF                  /*!< channel 3 overcapture flag */
#define TIMER_FLAG_SYSB                                    TIMER_INTF_SYSBIF                 /*!< system error flag */
#define TIMER_FLAG_UNDERFLOW                               TIMER_INTF_UNDERFLOWIF            /*!< TIMER counter underflow interrupt flag */
#define TIMER_FLAG_OVERFLOW                                TIMER_INTF_OVERFLOWIF             /*!< TIMER counter overflow interrupt flag */
#define TIMER_FLAG_MCH0                                    TIMER_INTF_MCH0IF                 /*!< multi mode channel 0 capture or compare flag */
#define TIMER_FLAG_MCH1                                    TIMER_INTF_MCH1IF                 /*!< multi mode channel 1 capture or compare flag */
#define TIMER_FLAG_MCH2                                    TIMER_INTF_MCH2IF                 /*!< multi mode channel 2 capture or compare flag */
#define TIMER_FLAG_MCH3                                    TIMER_INTF_MCH3IF                 /*!< multi mode channel 3 capture or compare flag */
#define TIMER_FLAG_MCH0O                                   TIMER_INTF_MCH0OF                 /*!< multi mode channel 0 overcapture flag */
#define TIMER_FLAG_MCH1O                                   TIMER_INTF_MCH1OF                 /*!< multi mode channel 1 overcapture flag */
#define TIMER_FLAG_MCH2O                                   TIMER_INTF_MCH2OF                 /*!< multi mode channel 2 overcapture flag */
#define TIMER_FLAG_MCH3O                                   TIMER_INTF_MCH3OF                 /*!< multi mode channel 3 overcapture flag */
#define TIMER_FLAG_CH0COMADD                               TIMER_INTF_CH0COMADDIF            /*!< channel 0 additional compare interrupt flag */
#define TIMER_FLAG_CH1COMADD                               TIMER_INTF_CH1COMADDIF            /*!< channel 1 additional compare interrupt flag */
#define TIMER_FLAG_CH2COMADD                               TIMER_INTF_CH2COMADDIF            /*!< channel 2 additional compare interrupt flag */
#define TIMER_FLAG_CH3COMADD                               TIMER_INTF_CH3COMADDIF            /*!< channel 3 additional compare interrupt flag */

/* TIMER DMA source */
#define TIMER_DMA_UPD                                      TIMER_DMAINTEN_UPDEN              /*!< update DMA request */
#define TIMER_DMA_CH0D                                     TIMER_DMAINTEN_CH0DEN             /*!< channel 0 capture or compare DMA request */
#define TIMER_DMA_CH1D                                     TIMER_DMAINTEN_CH1DEN             /*!< channel 1 capture or compare DMA request */
#define TIMER_DMA_CH2D                                     TIMER_DMAINTEN_CH2DEN             /*!< channel 2 capture or compare DMA request */
#define TIMER_DMA_CH3D                                     TIMER_DMAINTEN_CH3DEN             /*!< channel 3 capture or compare DMA request */
#define TIMER_DMA_CMTD                                     TIMER_DMAINTEN_CMTDEN             /*!< commutation DMA request */
#define TIMER_DMA_TRGD                                     TIMER_DMAINTEN_TRGDEN             /*!< trigger DMA request */
#define TIMER_DMA_MCH0D                                    TIMER_DMAINTEN_MCH0DEN            /*!< multi mode channel 0 capture or compare DMA request */
#define TIMER_DMA_MCH1D                                    TIMER_DMAINTEN_MCH1DEN            /*!< multi mode channel 1 capture or compare DMA request */
#define TIMER_DMA_MCH2D                                    TIMER_DMAINTEN_MCH2DEN            /*!< multi mode channel 2 capture or compare DMA request */
#define TIMER_DMA_MCH3D                                    TIMER_DMAINTEN_MCH3DEN            /*!< multi mode channel 3 capture or compare DMA request */

/* channel DMA request source selection */
#define TIMER_DMAREQUEST_CHANNELEVENT                      ((uint32_t)0x00000000U)           /*!< DMA request of channel y is sent when channel y event occurs */
#define TIMER_DMAREQUEST_UPDATEEVENT                       ((uint32_t)0x00000001U)           /*!< DMA request of channel y is sent when update event occurs */

/* DMA access base address */
#define DMACFG_DMATA(regval)                               (BITS(0, 5) & ((uint32_t)(regval) << 0U))
#define TIMER_DMACFG_DMATA_CTL0                            DMACFG_DMATA(0)                   /*!< DMA transfer address is TIMER_CTL0 */
#define TIMER_DMACFG_DMATA_CTL1                            DMACFG_DMATA(1)                   /*!< DMA transfer address is TIMER_CTL1 */
#define TIMER_DMACFG_DMATA_SMCFG                           DMACFG_DMATA(2)                   /*!< DMA transfer address is TIMER_SMCFG */
#define TIMER_DMACFG_DMATA_DMAINTEN                        DMACFG_DMATA(3)                   /*!< DMA transfer address is TIMER_DMAINTEN */
#define TIMER_DMACFG_DMATA_INTF                            DMACFG_DMATA(4)                   /*!< DMA transfer address is TIMER_INTF */
#define TIMER_DMACFG_DMATA_SWEVG                           DMACFG_DMATA(5)                   /*!< DMA transfer address is TIMER_SWEVG */
#define TIMER_DMACFG_DMATA_CHCTL0                          DMACFG_DMATA(6)                   /*!< DMA transfer address is TIMER_CHCTL0 */
#define TIMER_DMACFG_DMATA_CHCTL1                          DMACFG_DMATA(7)                   /*!< DMA transfer address is TIMER_CHCTL1 */
#define TIMER_DMACFG_DMATA_CHCTL2                          DMACFG_DMATA(8)                   /*!< DMA transfer address is TIMER_CHCTL2 */
#define TIMER_DMACFG_DMATA_CNT                             DMACFG_DMATA(9)                   /*!< DMA transfer address is TIMER_CNT */
#define TIMER_DMACFG_DMATA_PSC                             DMACFG_DMATA(10)                  /*!< DMA transfer address is TIMER_PSC */
#define TIMER_DMACFG_DMATA_CAR                             DMACFG_DMATA(11)                  /*!< DMA transfer address is TIMER_CAR */
#define TIMER_DMACFG_DMATA_CREP                            DMACFG_DMATA(12)                  /*!< DMA transfer address is TIMER_CREP */
#define TIMER_DMACFG_DMATA_CH0CV                           DMACFG_DMATA(13)                  /*!< DMA transfer address is TIMER_CH0CV */
#define TIMER_DMACFG_DMATA_CH1CV                           DMACFG_DMATA(14)                  /*!< DMA transfer address is TIMER_CH1CV */
#define TIMER_DMACFG_DMATA_CH2CV                           DMACFG_DMATA(15)                  /*!< DMA transfer address is TIMER_CH2CV */
#define TIMER_DMACFG_DMATA_CH3CV                           DMACFG_DMATA(16)                  /*!< DMA transfer address is TIMER_CH3CV */
#define TIMER_DMACFG_DMATA_CCHP                            DMACFG_DMATA(17)                  /*!< DMA transfer address is TIMER_CCHP */
#define TIMER_DMACFG_DMATA_MCHCTL0                         DMACFG_DMATA(18)                  /*!< DMA transfer address is TIMER_MCHCTL0 */
#define TIMER_DMACFG_DMATA_MCHCTL1                         DMACFG_DMATA(19)                  /*!< DMA transfer address is TIMER_MCHCTL1 */
#define TIMER_DMACFG_DMATA_MCHCTL2                         DMACFG_DMATA(20)                  /*!< DMA transfer address is TIMER_MCHCTL2 */
#define TIMER_DMACFG_DMATA_MCH0CV                          DMACFG_DMATA(21)                  /*!< DMA transfer address is TIMER_MCH0CV */
#define TIMER_DMACFG_DMATA_MCH1CV                          DMACFG_DMATA(22)                  /*!< DMA transfer address is TIMER_MCH1CV */
#define TIMER_DMACFG_DMATA_MCH2CV                          DMACFG_DMATA(23)                  /*!< DMA transfer address is TIMER_MCH2CV */
#define TIMER_DMACFG_DMATA_MCH3CV                          DMACFG_DMATA(24)                  /*!< DMA transfer address is TIMER_MCH3CV */
#define TIMER_DMACFG_DMATA_CH0COMV_ADD                     DMACFG_DMATA(25)                  /*!< DMA transfer address is TIMER_CH0COMV_ADD */
#define TIMER_DMACFG_DMATA_CH1COMV_ADD                     DMACFG_DMATA(26)                  /*!< DMA transfer address is TIMER_CH1COMV_ADD */
#define TIMER_DMACFG_DMATA_CH2COMV_ADD                     DMACFG_DMATA(27)                  /*!< DMA transfer address is TIMER_CH2COMV_ADD */
#define TIMER_DMACFG_DMATA_CH3COMV_ADD                     DMACFG_DMATA(28)                  /*!< DMA transfer address is TIMER_CH3COMV_ADD */
#define TIMER_DMACFG_DMATA_CTL2                            DMACFG_DMATA(29)                  /*!< DMA transfer address is TIMER_CTL2 */
#define TIMER_DMACFG_DMATA_AFCTL                           DMACFG_DMATA(35)                  /*!< DMA transfer address is TIMER_AFCTL1 */
#define TIMER_DMACFG_DMATA_IREP                            DMACFG_DMATA(36)                  /*!< DMA transfer address is TIMER_IREP */
#define TIMER_DMACFG_DMATA_ADCRCTL                         DMACFG_DMATA(37)                  /*!< DMA transfer address is TIMER_ADCRCTL */
#define TIMER_DMACFG_DMATA_ADCCR1                          DMACFG_DMATA(38)                  /*!< DMA transfer address is TIMER_ADCCR1 */
#define TIMER_DMACFG_DMATA_ADCCR2                          DMACFG_DMATA(39)                  /*!< DMA transfer address is TIMER_ADCCR2 */
#define TIMER_DMACFG_DMATA_ADCREP                          DMACFG_DMATA(40)                  /*!< DMA transfer address is TIMER_ADCREP */
#define TIMER_DMACFG_DMATA_ADCTL                           DMACFG_DMATA(43)                  /*!< DMA transfer address is TIMER_ADCTL */
#define TIMER_DMACFG_DMATA_SHUPM0                          DMACFG_DMATA(49)                  /*!< DMA transfer address is TIMER_SHUPM0 */
#define TIMER_DMACFG_DMATA_SHUPM1                          DMACFG_DMATA(50)                  /*!< DMA transfer address is TIMER_SHUPM1 */
#define TIMER_DMACFG_DMATA_COUMSEL                         DMACFG_DMATA(51)                  /*!< DMA transfer address is TIMER_COUMSEL */

/* DMA access burst length */
#define DMACFG_DMATC(regval)                               (BITS(8, 13) & ((uint32_t)(regval) << 8U))
#define TIMER_DMACFG_DMATC_1TRANSFER                       DMACFG_DMATC(0)                   /*!< DMA transfer 1 time */
#define TIMER_DMACFG_DMATC_2TRANSFER                       DMACFG_DMATC(1)                   /*!< DMA transfer 2 times */
#define TIMER_DMACFG_DMATC_3TRANSFER                       DMACFG_DMATC(2)                   /*!< DMA transfer 3 times */
#define TIMER_DMACFG_DMATC_4TRANSFER                       DMACFG_DMATC(3)                   /*!< DMA transfer 4 times */
#define TIMER_DMACFG_DMATC_5TRANSFER                       DMACFG_DMATC(4)                   /*!< DMA transfer 5 times */
#define TIMER_DMACFG_DMATC_6TRANSFER                       DMACFG_DMATC(5)                   /*!< DMA transfer 6 times */
#define TIMER_DMACFG_DMATC_7TRANSFER                       DMACFG_DMATC(6)                   /*!< DMA transfer 7 times */
#define TIMER_DMACFG_DMATC_8TRANSFER                       DMACFG_DMATC(7)                   /*!< DMA transfer 8 times */
#define TIMER_DMACFG_DMATC_9TRANSFER                       DMACFG_DMATC(8)                   /*!< DMA transfer 9 times */
#define TIMER_DMACFG_DMATC_10TRANSFER                      DMACFG_DMATC(9)                   /*!< DMA transfer 10 times */
#define TIMER_DMACFG_DMATC_11TRANSFER                      DMACFG_DMATC(10)                  /*!< DMA transfer 11 times */
#define TIMER_DMACFG_DMATC_12TRANSFER                      DMACFG_DMATC(11)                  /*!< DMA transfer 12 times */
#define TIMER_DMACFG_DMATC_13TRANSFER                      DMACFG_DMATC(12)                  /*!< DMA transfer 13 times */
#define TIMER_DMACFG_DMATC_14TRANSFER                      DMACFG_DMATC(13)                  /*!< DMA transfer 14 times */
#define TIMER_DMACFG_DMATC_15TRANSFER                      DMACFG_DMATC(14)                  /*!< DMA transfer 15 times */
#define TIMER_DMACFG_DMATC_16TRANSFER                      DMACFG_DMATC(15)                  /*!< DMA transfer 16 times */
#define TIMER_DMACFG_DMATC_17TRANSFER                      DMACFG_DMATC(16)                  /*!< DMA transfer 17 times */
#define TIMER_DMACFG_DMATC_18TRANSFER                      DMACFG_DMATC(17)                  /*!< DMA transfer 18 times */
#define TIMER_DMACFG_DMATC_19TRANSFER                      DMACFG_DMATC(18)                  /*!< DMA transfer 19 times */
#define TIMER_DMACFG_DMATC_20TRANSFER                      DMACFG_DMATC(19)                  /*!< DMA transfer 20 times */
#define TIMER_DMACFG_DMATC_21TRANSFER                      DMACFG_DMATC(20)                  /*!< DMA transfer 21 times */
#define TIMER_DMACFG_DMATC_22TRANSFER                      DMACFG_DMATC(21)                  /*!< DMA transfer 22 times */
#define TIMER_DMACFG_DMATC_23TRANSFER                      DMACFG_DMATC(22)                  /*!< DMA transfer 23 times */
#define TIMER_DMACFG_DMATC_24TRANSFER                      DMACFG_DMATC(23)                  /*!< DMA transfer 24 times */
#define TIMER_DMACFG_DMATC_25TRANSFER                      DMACFG_DMATC(24)                  /*!< DMA transfer 25 times */
#define TIMER_DMACFG_DMATC_26TRANSFER                      DMACFG_DMATC(25)                  /*!< DMA transfer 26 times */
#define TIMER_DMACFG_DMATC_27TRANSFER                      DMACFG_DMATC(26)                  /*!< DMA transfer 27 times */
#define TIMER_DMACFG_DMATC_28TRANSFER                      DMACFG_DMATC(27)                  /*!< DMA transfer 28 times */
#define TIMER_DMACFG_DMATC_29TRANSFER                      DMACFG_DMATC(28)                  /*!< DMA transfer 29 times */
#define TIMER_DMACFG_DMATC_30TRANSFER                      DMACFG_DMATC(29)                  /*!< DMA transfer 30 times */
#define TIMER_DMACFG_DMATC_31TRANSFER                      DMACFG_DMATC(30)                  /*!< DMA transfer 31 times */
#define TIMER_DMACFG_DMATC_32TRANSFER                      DMACFG_DMATC(31)                  /*!< DMA transfer 32 times */
#define TIMER_DMACFG_DMATC_33TRANSFER                      DMACFG_DMATC(32)                  /*!< DMA transfer 33 times */
#define TIMER_DMACFG_DMATC_34TRANSFER                      DMACFG_DMATC(33)                  /*!< DMA transfer 34 times */
#define TIMER_DMACFG_DMATC_35TRANSFER                      DMACFG_DMATC(34)                  /*!< DMA transfer 35 times */
#define TIMER_DMACFG_DMATC_36TRANSFER                      DMACFG_DMATC(35)                  /*!< DMA transfer 36 times */
#define TIMER_DMACFG_DMATC_37TRANSFER                      DMACFG_DMATC(36)                  /*!< DMA transfer 37 times */
#define TIMER_DMACFG_DMATC_38TRANSFER                      DMACFG_DMATC(37)                  /*!< DMA transfer 38 times */
#define TIMER_DMACFG_DMATC_39TRANSFER                      DMACFG_DMATC(38)                  /*!< DMA transfer 39 times */
#define TIMER_DMACFG_DMATC_40TRANSFER                      DMACFG_DMATC(39)                  /*!< DMA transfer 40 times */
#define TIMER_DMACFG_DMATC_41TRANSFER                      DMACFG_DMATC(40)                  /*!< DMA transfer 41 times */
#define TIMER_DMACFG_DMATC_42TRANSFER                      DMACFG_DMATC(41)                  /*!< DMA transfer 42 times */
#define TIMER_DMACFG_DMATC_43TRANSFER                      DMACFG_DMATC(42)                  /*!< DMA transfer 43 times */
#define TIMER_DMACFG_DMATC_44TRANSFER                      DMACFG_DMATC(43)                  /*!< DMA transfer 44 times */
#define TIMER_DMACFG_DMATC_45TRANSFER                      DMACFG_DMATC(44)                  /*!< DMA transfer 45 times */
#define TIMER_DMACFG_DMATC_46TRANSFER                      DMACFG_DMATC(45)                  /*!< DMA transfer 46 times */
#define TIMER_DMACFG_DMATC_47TRANSFER                      DMACFG_DMATC(46)                  /*!< DMA transfer 47 times */
#define TIMER_DMACFG_DMATC_48TRANSFER                      DMACFG_DMATC(47)                  /*!< DMA transfer 48 times */
#define TIMER_DMACFG_DMATC_49TRANSFER                      DMACFG_DMATC(48)                  /*!< DMA transfer 49 times */
#define TIMER_DMACFG_DMATC_50TRANSFER                      DMACFG_DMATC(49)                  /*!< DMA transfer 50 times */
#define TIMER_DMACFG_DMATC_51TRANSFER                      DMACFG_DMATC(50)                  /*!< DMA transfer 51 times */
#define TIMER_DMACFG_DMATC_52TRANSFER                      DMACFG_DMATC(51)                  /*!< DMA transfer 51 times */

/* TIMER software event generation source */
#define TIMER_EVENT_SRC_UPG                                TIMER_SWEVG_UPG                   /*!< update event generation */
#define TIMER_EVENT_SRC_CH0G                               TIMER_SWEVG_CH0G                  /*!< channel 0 capture or compare event generation */
#define TIMER_EVENT_SRC_CH1G                               TIMER_SWEVG_CH1G                  /*!< channel 1 capture or compare event generation */
#define TIMER_EVENT_SRC_CH2G                               TIMER_SWEVG_CH2G                  /*!< channel 2 capture or compare event generation */
#define TIMER_EVENT_SRC_CH3G                               TIMER_SWEVG_CH3G                  /*!< channel 3 capture or compare event generation */
#define TIMER_EVENT_SRC_CMTG                               TIMER_SWEVG_CMTG                  /*!< channel commutation event generation */
#define TIMER_EVENT_SRC_TRGG                               TIMER_SWEVG_TRGG                  /*!< trigger event generation */
#define TIMER_EVENT_SRC_BRKG                               TIMER_SWEVG_BRKG                  /*!< break event generation */
#define TIMER_EVENT_SRC_MCH0G                              TIMER_SWEVG_MCH0G                 /*!< multi mode channel 0 capture or compare event generation */
#define TIMER_EVENT_SRC_MCH1G                              TIMER_SWEVG_MCH1G                 /*!< multi mode channel 1 capture or compare event generation */
#define TIMER_EVENT_SRC_MCH2G                              TIMER_SWEVG_MCH2G                 /*!< multi mode channel 2 capture or compare event generation */
#define TIMER_EVENT_SRC_MCH3G                              TIMER_SWEVG_MCH3G                 /*!< multi mode channel 3 capture or compare event generation */
#define TIMER_EVENT_SRC_CH0COMADDG                         TIMER_SWEVG_CH0COMADDG            /*!< channel 0 additional compare event generation */
#define TIMER_EVENT_SRC_CH1COMADDG                         TIMER_SWEVG_CH1COMADDG            /*!< channel 1 additional compare event generation */
#define TIMER_EVENT_SRC_CH2COMADDG                         TIMER_SWEVG_CH2COMADDG            /*!< channel 2 additional compare event generation */
#define TIMER_EVENT_SRC_CH3COMADDG                         TIMER_SWEVG_CH3COMADDG            /*!< channel 3 additional compare event generation */

/* center-aligned mode selection */
#define CTL0_CAM(regval)                                   ((uint32_t)(BITS(5, 6) & ((uint32_t)(regval) << 5U)))
#define TIMER_COUNTER_EDGE                                 CTL0_CAM(0)                       /*!< edge-aligned mode */
#define TIMER_COUNTER_CENTER_DOWN                          CTL0_CAM(1)                       /*!< center-aligned and counting down assert mode */
#define TIMER_COUNTER_CENTER_UP                            CTL0_CAM(2)                       /*!< center-aligned and counting up assert mode */
#define TIMER_COUNTER_CENTER_BOTH                          CTL0_CAM(3)                       /*!< center-aligned and counting up/down assert mode */

#define TIMER_PSC_RELOAD_NOW                               ((uint32_t)0x00000000U)           /*!< the prescaler is loaded right now */
#define TIMER_PSC_RELOAD_UPDATE                            ((uint32_t)0x00000001U)           /*!< the prescaler is loaded at next update event */

/* count direction */
#define TIMER_COUNTER_UP                                   ((uint32_t)0x0000U)               /*!< counter up direction */
#define TIMER_COUNTER_DOWN                                 ((uint32_t)TIMER_CTL0_DIR)        /*!< counter down direction */

/* specify division ratio between TIMER clock and dead-time and sampling clock */
#define CTL0_CKDIV(regval)                                 ((uint32_t)(BITS(8, 9) & ((uint32_t)(regval) << 8U)))
#define TIMER_CKDIV_DIV1                                   CTL0_CKDIV(0)                     /*!< clock division value is 1,fDTS=fTIMER_CK */
#define TIMER_CKDIV_DIV2                                   CTL0_CKDIV(1)                     /*!< clock division value is 2,fDTS= fTIMER_CK/2 */
#define TIMER_CKDIV_DIV4                                   CTL0_CKDIV(2)                     /*!< clock division value is 4, fDTS= fTIMER_CK/4 */

/* single pulse mode */
#define TIMER_SP_MODE_SINGLE                               ((uint32_t)0x00000000U)           /*!< single pulse mode */
#define TIMER_SP_MODE_REPETITIVE                           ((uint32_t)0x00000001U)           /*!< repetitive pulse mode */

/* update source */
#define TIMER_UPDATE_SRC_REGULAR                           ((uint32_t)0x00000000U)           /*!< update interrupt generate only by counter overflow/underflow */
#define TIMER_UPDATE_SRC_GLOBAL                            ((uint32_t)0x00000001U)           /*!< update interrupt generate by setting of UPG bit or the counter overflow/underflow,or the slave mode controller trigger */

/* update event source selection */
#define TIMER_UPDATE_EVENT_REGULAR                         ((uint32_t)0x00000000U)           /*!< update event generate only by counter overflow/underflow */
#define TIMER_UPDATE_EVENT_GLOBAL                          ((uint32_t)0x00000001U)           /*!< update event generate by setting of UPG bit or the counter overflow/underflow,or the slave mode controller trigger */

/* update source selection */
#define CTL0_UPS_SEL(regval)                               ((uint32_t)(BITS(30, 31)&((uint32_t)(regval) << 30U)))
#define TIMER_UPS_SEL_FLOW                                 CTL0_UPS_SEL(0)                   /*!< update event source select counter flow event */
#define TIMER_UPS_SEL_OVERFLOW                             CTL0_UPS_SEL(1)                   /*!< update event source select counter overflow event */
#define TIMER_UPS_SEL_UNDERFLOW                            CTL0_UPS_SEL(2)                   /*!< update event source select counter underflow event */

/* interrupt source selection*/
#define CTL0_INT_SEL(regval)                               ((uint32_t)(BITS(28, 29)&((uint32_t)(regval) << 28U)))
#define TIMER_INT_SEL_FLOW                                 CTL0_INT_SEL(0)                   /*!< interrupt source select counter flow event */
#define TIMER_INT_SEL_OVERFLOW                             CTL0_INT_SEL(1)                   /*!< interrupt source select counter overflow event */
#define TIMER_INT_SEL_UNDERFLOW                            CTL0_INT_SEL(2)                   /*!< interrupt source select counter underflow event */

/* etr source selection*/
#define CTL0_ETI_SEL(regval)                               ((uint32_t)(BITS(24, 25)&((uint32_t)(regval) << 24U)))
#define TIMER_ETI_SEL_ETI1                                 CTL0_ETI_SEL(0)                   /*!< TIMERX etr source select TIMER_ETI1 */
#define TIMER_ETI_SEL_ETI2                                 CTL0_ETI_SEL(1)                   /*!< TIMERX etr source select TIMER_ETI2 */
#define TIMER_ETI_SEL_ETI3                                 CTL0_ETI_SEL(2)                   /*!< TIMERX etr source select TIMER_ETI3 */
#define TIMER_ETI_SEL_ETI4                                 CTL0_ETI_SEL(3)                   /*!< TIMERX etr source select TIMER_ETI4 */

/* run mode off-state configure */
#define TIMER_ROS_STATE_ENABLE                             ((uint16_t)TIMER_CCHP_ROS)        /*!< when POEN bit is set, the channel output signals (CHx_O/CHx_ON) are enabled, with relationship to CHxEN/CHxNEN bits */
#define TIMER_ROS_STATE_DISABLE                            ((uint16_t)0x0000U)               /*!< when POEN bit is set, the channel output signals (CHx_O/CHx_ON) are disabled */

/* idle mode off-state configure */
#define TIMER_IOS_STATE_ENABLE                             ((uint16_t)TIMER_CCHP_IOS)        /*!< when POEN bit is reset, he channel output signals (CHx_O/CHx_ON) are enabled, with relationship to CHxEN/CHxNEN bits */
#define TIMER_IOS_STATE_DISABLE                            ((uint16_t)0x0000U)               /*!< when POEN bit is reset, the channel output signals (CHx_O/CHx_ON) are disabled */

/* break input polarity */
#define TIMER_BREAK_POLARITY_LOW                           ((uint16_t)0x0000U)               /*!< break input polarity is low */
#define TIMER_BREAK_POLARITY_HIGH                          ((uint16_t)TIMER_CCHP_BRKP)       /*!< break input polarity is high */

/* output automatic enable */
#define TIMER_OUTAUTO_ENABLE                               ((uint16_t)TIMER_CCHP_OAEN)       /*!< output automatic enable */
#define TIMER_OUTAUTO_DISABLE                              ((uint16_t)0x0000U)               /*!< output automatic disable */

/* complementary register protect control */
#define CCHP_PROT(regval)                                  ((uint16_t)(BITS(8, 9) & ((uint32_t)(regval) << 8U)))
#define TIMER_CCHP_PROT_OFF                                CCHP_PROT(0)                      /*!< protect disable */
#define TIMER_CCHP_PROT_0                                  CCHP_PROT(1)                      /*!< PROT mode 0 */
#define TIMER_CCHP_PROT_1                                  CCHP_PROT(2)                      /*!< PROT mode 1 */
#define TIMER_CCHP_PROT_2                                  CCHP_PROT(3)                      /*!< PROT mode 2 */

/* break input enable */
#define TIMER_BREAK_ENABLE                                 ((uint16_t)TIMER_CCHP_BRKEN)      /*!< break input enable */
#define TIMER_BREAK_DISABLE                                ((uint16_t)0x0000U)               /*!< break input disable */

/* TIMER channel n(n=0,1,2,3) */
#define TIMER_CH_0                                         ((uint16_t)0x0000U)               /*!< TIMER channel 0 */
#define TIMER_CH_1                                         ((uint16_t)0x0001U)               /*!< TIMER channel 1 */
#define TIMER_CH_2                                         ((uint16_t)0x0002U)               /*!< TIMER channel 2 */
#define TIMER_CH_3                                         ((uint16_t)0x0003U)               /*!< TIMER channel 3 */
#define TIMER_MCH_0                                        ((uint16_t)0x0010U)               /*!< TIMER multi mode channel 0 */
#define TIMER_MCH_1                                        ((uint16_t)0x0011U)               /*!< TIMER multi mode channel 1 */
#define TIMER_MCH_2                                        ((uint16_t)0x0012U)               /*!< TIMER multi mode channel 2 */
#define TIMER_MCH_3                                        ((uint16_t)0x0013U)               /*!< TIMER multi mode channel 3 */

/* channel enable state */
#define TIMER_CCX_ENABLE                                   ((uint16_t)0x0001U)               /*!< channel enable */
#define TIMER_CCX_DISABLE                                  ((uint16_t)0x0000U)               /*!< channel disable */

/* channel complementary output enable state */
#define TIMER_CCXN_ENABLE                                  ((uint16_t)0x0004U)               /*!< channel complementary enable */
#define TIMER_CCXN_DISABLE                                 ((uint16_t)0x0000U)               /*!< channel complementary disable */

/* multi mode channel enable state */
#define TIMER_MCCX_ENABLE                                  ((uint16_t)0x0004U)               /*!< multi mode channel enable */
#define TIMER_MCCX_DISABLE                                 ((uint16_t)0x0000U)               /*!< multi mode channel disable */

/* channel output polarity */
#define TIMER_OC_POLARITY_HIGH                             ((uint16_t)0x0000U)               /*!< channel output polarity is high */
#define TIMER_OC_POLARITY_LOW                              ((uint16_t)0x0002U)               /*!< channel output polarity is low */

/* channel complementary output polarity */
#define TIMER_OCN_POLARITY_HIGH                            ((uint16_t)0x0000U)               /*!< channel complementary output polarity is high */
#define TIMER_OCN_POLARITY_LOW                             ((uint16_t)0x0008U)               /*!< channel complementary output polarity is low */

/* multi mode channel output polarity */
#define TIMER_OMC_POLARITY_HIGH                            ((uint16_t)0x0000U)               /*!< multi mode channel output polarity is high */
#define TIMER_OMC_POLARITY_LOW                             ((uint16_t)0x0001U)               /*!< multi mode channel output polarity is low */

/* idle state of channel output */
#define TIMER_OC_IDLE_STATE_HIGH                           ((uint16_t)0x0100U)               /*!< idle state of channel output is high */
#define TIMER_OC_IDLE_STATE_LOW                            ((uint16_t)0x0000U)               /*!< idle state of channel output is low */

/* idle state of channel complementary output */
#define TIMER_OCN_IDLE_STATE_HIGH                          ((uint16_t)0x0200U)               /*!< idle state of channel complementary output is high */
#define TIMER_OCN_IDLE_STATE_LOW                           ((uint16_t)0x0000U)               /*!< idle state of channel complementary output is low */

/* idle state of multi mode channel output */
#define TIMER_OMC_IDLE_STATE_HIGH                          ((uint16_t)0x0100U)               /*!< idle state of multi mode channel output is high */
#define TIMER_OMC_IDLE_STATE_LOW                           ((uint16_t)0x0000U)               /*!< idle state of multi mode channel output is low */

/* channel output compare mode */
#define TIMER_OC_MODE(regval)                              ((BITS(4, 6) & ((uint32_t)(regval) << 4U)) | (BIT(16) & ((uint32_t)(regval) << 13U)))
#define TIMER_OC_MODE_TIMING                               (TIMER_OC_MODE(0))                /*!< timing mode */
#define TIMER_OC_MODE_ACTIVE                               (TIMER_OC_MODE(1))                /*!< active mode */
#define TIMER_OC_MODE_INACTIVE                             (TIMER_OC_MODE(2))                /*!< inactive mode */
#define TIMER_OC_MODE_TOGGLE                               (TIMER_OC_MODE(3))                /*!< toggle mode */
#define TIMER_OC_MODE_LOW                                  (TIMER_OC_MODE(4))                /*!< force low mode */
#define TIMER_OC_MODE_HIGH                                 (TIMER_OC_MODE(5))                /*!< force high mode */
#define TIMER_OC_MODE_PWM0                                 (TIMER_OC_MODE(6))                /*!< PWM0 mode */
#define TIMER_OC_MODE_PWM1                                 (TIMER_OC_MODE(7))                /*!< PWM1 mode */
#define TIMER_OC_MODE_COMPOSITE_PWM0                       (TIMER_OC_MODE(8))                /*!< COMPOSITE pwm mode0 */
#define TIMER_OC_MODE_COMPOSITE_PWM1                       (TIMER_OC_MODE(9))                /*!< COMPOSITE pwm mode1 */
#define TIMER_OC_MODE_ASYMMETRIC_PWM0                      (TIMER_OC_MODE(10))               /*!< ASYMMETRIC pwm mode0 */
#define TIMER_OC_MODE_ASYMMETRIC_PWM1                      (TIMER_OC_MODE(11))               /*!< ASYMMETRIC pwm mode1 */

/* channel output compare shadow enable */
#define TIMER_OC_SHADOW_ENABLE                             ((uint16_t)0x0008U)               /*!< channel output shadow state enable */
#define TIMER_OC_SHADOW_DISABLE                            ((uint16_t)0x0000U)               /*!< channel output shadow state disable */

/* channel output compare fast enable */
#define TIMER_OC_FAST_ENABLE                               ((uint16_t)0x0004U)                /*!< channel output fast function enable */
#define TIMER_OC_FAST_DISABLE                              ((uint16_t)0x0000U)                /*!< channel output fast function disable */

/* channel output compare clear enable */
#define TIMER_OC_CLEAR_ENABLE                              ((uint16_t)0x0080U)               /*!< channel output clear function enable */
#define TIMER_OC_CLEAR_DISABLE                             ((uint16_t)0x0000U)               /*!< channel output clear function disable */

/* channel control shadow register update control */
#define CTL1_CCUC(regval)                                  ((BIT(2) & ((uint32_t)(regval) << 2U)) | (BITS(30, 31) & ((uint32_t)(regval) << 29U)))
#define TIMER_UPDATECTL_CCU                                CTL1_CCUC(0)                      /*!< the shadow registers update by when CMTG bit is set */
#define TIMER_UPDATECTL_CCUTRI                             CTL1_CCUC(1)                      /*!< the shadow registers update by when CMTG bit is set or an rising edge of TRGI occurs */
#define TIMER_UPDATECTL_CCUOVERFLOW                        CTL1_CCUC(4)                      /*!< the shadow registers update by when the overflow event occurs */
#define TIMER_UPDATECTL_CCUUNDERFLOW                       CTL1_CCUC(5)                      /*!< the shadow registers update by when the underflow event occurs */
#define TIMER_UPDATECTL_CCUFLOW                            CTL1_CCUC(6)                      /*!< the shadow registers update by when the overflow or underflow event occurs */

/* channel input capture polarity */
#define TIMER_IC_POLARITY_RISING                           ((uint16_t)0x0000U)               /*!< input capture rising edge */
#define TIMER_IC_POLARITY_FALLING                          ((uint16_t)0x0002U)               /*!< input capture falling edge */
#define TIMER_IC_POLARITY_BOTH_EDGE                        ((uint16_t)0x000AU)               /*!< input capture both edge */

/* TIMER input capture selection */
#define TIMER_IC_SELECTION_DIRECTTI                        ((uint32_t)0x0001U)               /*!< channel y is configured as input and icy is mapped on CIy */
#define TIMER_IC_SELECTION_INDIRECTTI                      ((uint32_t)0x0002U)               /*!< channel y is configured as input and icy is mapped on opposite input */
#define TIMER_IC_SELECTION_ITS                             ((uint32_t)0x0003U)               /*!< channel y is configured as input and icy is mapped on ITS */
#define TIMER_IC_SELECTION_PAIR                            ((uint16_t)0x0004U)               /*!< channel n is configured as input and icy is mapped on the other channel of same pair */

/* channel input capture prescaler */
#define TIMER_IC_PSC_DIV1                                  ((uint16_t)0x0000U)               /*!< no prescaler */
#define TIMER_IC_PSC_DIV2                                  ((uint16_t)0x0004U)               /*!< divided by 2 */
#define TIMER_IC_PSC_DIV4                                  ((uint16_t)0x0008U)               /*!< divided by 4 */
#define TIMER_IC_PSC_DIV8                                  ((uint16_t)0x000CU)               /*!< divided by 8 */

/* ocref source selection */
#define TIMER_SMCFG_OCPRE_ETI                              ((uint32_t)TIMER_SMCFG_OCRC)      /*!< external other peripheral input */
#define TIMER_SMCFG_OCPRE_CLR_INPUT                        ((uint32_t)0x00000000U)           /*!< external pin input */

/* master mode control */
#define CTL1_MMC(regval)                                   ((BITS(4, 6) & ((uint32_t)(regval) << 4U))|((BIT(25) & (uint32_t)(regval) << 22)))
#define TIMER_TRI_OUT_SRC_RESET                            CTL1_MMC(0)                       /*!< the UPG bit as trigger output */
#define TIMER_TRI_OUT_SRC_ENABLE                           CTL1_MMC(1)                       /*!< the counter enable signal TIMER_CTL0_CEN as trigger output */
#define TIMER_TRI_OUT_SRC_UPDATE                           CTL1_MMC(2)                       /*!< update event as trigger output */
#define TIMER_TRI_OUT_SRC_CH0                              CTL1_MMC(3)                       /*!< a capture or a compare match occurred in channel 0 as trigger output TRGO */
#define TIMER_TRI_OUT_SRC_O0CPRE                           CTL1_MMC(4)                       /*!< O0CPRE as trigger output */
#define TIMER_TRI_OUT_SRC_O1CPRE                           CTL1_MMC(5)                       /*!< O1CPRE as trigger output */
#define TIMER_TRI_OUT_SRC_O2CPRE                           CTL1_MMC(6)                       /*!< O2CPRE as trigger output */
#define TIMER_TRI_OUT_SRC_O3CPRE                           CTL1_MMC(7)                       /*!< O3CPRE as trigger output */

/* master slave mode selection */
#define TIMER_MASTER_SLAVE_MODE_ENABLE                     ((uint32_t)0x00000001U)           /*!< master slave mode enable */
#define TIMER_MASTER_SLAVE_MODE_DISABLE                    ((uint32_t)0x00000000U)           /*!< master slave mode disable */

/* external trigger prescaler */
#define SMCFG_ETPSC(regval)                                (BITS(12, 13) & ((uint32_t)(regval) << 12U))
#define TIMER_EXT_TRI_PSC_OFF                              SMCFG_ETPSC(0)                    /*!< no divided */
#define TIMER_EXT_TRI_PSC_DIV2                             SMCFG_ETPSC(1)                    /*!< divided by 2 */
#define TIMER_EXT_TRI_PSC_DIV4                             SMCFG_ETPSC(2)                    /*!< divided by 4 */
#define TIMER_EXT_TRI_PSC_DIV8                             SMCFG_ETPSC(3)                    /*!< divided by 8 */

/* external trigger polarity */
#define TIMER_ETP_FALLING                                  ((uint32_t)TIMER_SMCFG_ETP)       /*!< active low or falling edge active */
#define TIMER_ETP_RISING                                   ((uint32_t)0x00000000U)           /*!< active high or rising edge active */

/* channel 0 trigger input selection */
#define TIMER_HALLINTERFACE_ENABLE                         ((uint32_t)0x00000000U)           /*!< TIMER hall sensor mode enable */
#define TIMER_HALLINTERFACE_DISABLE                        ((uint32_t)0x00000001U)           /*!< TIMER hall sensor mode disable */

/* TIMERx(x=0,1,2,3,4,7) write cc register selection */
#define TIMER_CHVSEL_ENABLE                                ((uint16_t)0x0002U)               /*!< write CHxVAL register selection enable */
#define TIMER_CHVSEL_DISABLE                               ((uint16_t)0x0000U)               /*!< write CHxVAL register selection disable */

/* the output value selection */
#define TIMER_OUTSEL_ENABLE                                ((uint16_t)0x0001U)               /*!< output value selection enable */
#define TIMER_OUTSEL_DISABLE                               ((uint16_t)0x0000U)               /*!< output value selection disable */

/* channel additional output compare shadow enable */
#define TIMER_ADD_SHADOW_ENABLE                            ((uint16_t)0x0001U)               /*!< channel additional output shadow state enable */
#define TIMER_ADD_SHADOW_DISABLE                           ((uint16_t)0x0000U)               /*!< channel additional output shadow state disable */

/* channel output compare shadow enable */
#define TIMER_OMC_SHADOW_ENABLE                            ((uint16_t)0x0008U)               /*!< multi mode channel output shadow state enable */
#define TIMER_OMC_SHADOW_DISABLE                           ((uint16_t)0x0000U)               /*!< multi mode channel output shadow state disable */

/* channel output compare fast enable */
#define TIMER_OMC_FAST_ENABLE                              ((uint16_t)0x0004U)                /*!< channel output fast function enable */
#define TIMER_OMC_FAST_DISABLE                             ((uint16_t)0x0000U)                /*!< channel output fast function disable */

/* channel output compare clear enable */
#define TIMER_OMC_CLEAR_ENABLE                             ((uint16_t)0x0080U)               /*!< multi mode channel output clear function enable */
#define TIMER_OMC_CLEAR_DISABLE                            ((uint16_t)0x0000U)               /*!< multi mode channel output clear function disable */

/* TIMER output value selection */
#define TIMER_PULSE_OUTPUT_NORMAL                          ((uint16_t)0x0000U)               /*!< channel output normal */
#define TIMER_PULSE_OUTPUT_CNT_UP                          ((uint16_t)0x0001U)               /*!< pulse output only when counting up */
#define TIMER_PULSE_OUTPUT_CNT_DOWN                        ((uint16_t)0x0002U)               /*!< pulse output only when counting down */
#define TIMER_PULSE_OUTPUT_CNT_BOTH                        ((uint16_t)0x0003U)               /*!< pulse output when counting up or down */
#define TIMER_PULSE_OUTPUT_MASK                            ((uint16_t)0x0003U)               /*!< pulse output mode mask */

/* multi mode channel input capture polarity */
#define TIMER_IMC_POLARITY_RISING                          ((uint16_t)0x0000U)               /*!< multi mode channel input capture rising edge */
#define TIMER_IMC_POLARITY_FALLING                         ((uint16_t)0x0001U)               /*!< multi mode channel input capture falling edge */
#define TIMER_IMC_POLARITY_BOTH_EDGE                       ((uint16_t)0x0003U)               /*!< multi mode channel input capture both edge */

/* TIMER multi mode channel mode selection */
#define TIMER_MCH_MODE_INDEPENDENTLY                       ((uint16_t)0x0000U)               /*!< multi mode channel work in independently mode */
#define TIMER_MCH_MODE_COMPLEMENTARY                       ((uint16_t)0x0003U)               /*!< multi mode channel work in complementary output mode */
#define TIMER_MCH_MODE_MASK                                ((uint16_t)0x0003U)               /*!< multi mode channel mode mask */

/* TIEMR break input pin polarity config */
#define TIMER_BRKIN_POLARITY_INVERTED                      TIMER_AFCTL_BRKIN0P               /*!< TIMER break external input polarity is active low */
#define TIMER_BRKIN_POLARITY_NONINVERTED                   ((uint16_t)0x0000U)               /*!< TIMER break external input polarity is active high */

/* TIEMR break input pin enable */
#define TIEMR_BRKIN_ENABLE                                 TIMER_AFCTL_BRKIN0E               /*!< TIMER break external input enable */
#define TIEMR_BRKIN_DISABLE                                ((uint16_t)0x0000U)               /*!< TIMER break external input disable */

/* TIMER break input from CMP source */
#define TIMER_BRKIN_CMP0                                   ((uint32_t)0x00000000U)               /*!< TIMER break CMP0 */
#define TIMER_BRKIN_CMP1                                   ((uint32_t)0x00000001U)               /*!< TIMER break CMP1 */
#define TIMER_BRKIN_CMP2                                   ((uint32_t)0x00000002U)               /*!< TIMER break CMP2 */
#define TIMER_BRKIN_CMP3                                   ((uint32_t)0x00000003U)               /*!< TIMER break CMP3 */

/* TIMER break input from CMP enable */
#define TIMER_BRKIN_CMP_ENABLE                             ((uint16_t)0x0000U)               /*!< TIMER break CMPx enable */
#define TIMER_BRKIN_CMP_DISABLE                            ((uint16_t)0x0001U)               /*!< TIMER break CMPx disable*/

/* TIMER break input from CMP polarity config */
#define TIMER_BRKIN_CMP_INVERTED                           ((uint16_t)0x0001U)               /*!< TIMER break input signal from CMP is inverted */
#define TIMER_BRKIN_CMP_NONINVERTED                        ((uint16_t)0x0000U)               /*!< TIMER break input signal from CMP is not inverted */

/* TIMER ocref_clr internal signal source selection */
#define AFCTL_OCRSEL(regval)                               (BITS(16, 18) & ((uint32_t)(regval) << 16U))
#define TIMER_OCPRE_CLR_CMP0                               AFCTL_OCRSEL(0)                   /*!< TIMER ocref_clr source select cmp0 */
#define TIMER_OCPRE_CLR_CMP1                               AFCTL_OCRSEL(1)                   /*!< TIMER ocref_clr source select cmp1 */
#define TIMER_OCPRE_CLR_CMP2                               AFCTL_OCRSEL(2)                   /*!< TIMER ocref_clr source select cmp2 */
#define TIMER_OCPRE_CLR_CMP3                               AFCTL_OCRSEL(3)                   /*!< TIMER ocref_clr source select cmp3 */

/* TIMER adc compare event repeation register select */
#define TIMER_ADC_COMPARE1                                 ((uint16_t)0x0000U)               /*!< select TIMER_ADCCR1 */
#define TIMER_ADC_COMPARE2                                 ((uint16_t)0x0001U)               /*!< select TIMER_ADCCR2 */

/* TIMER adc compare repeat source select */
#define TIMER_ADC_REPA                                     ((uint16_t)0x0000U)               /*!< select TIMER_ADCCR1 compare event reption register REPA */
#define TIMER_ADC_REPB                                     ((uint16_t)0x0001U)               /*!< select TIMER_ADCCR2 compare event reption register REPB */
#define TIMER_ADC_REPAB                                    ((uint16_t)0x0002U)               /*!< select TIMER_ADCCR1 or TIMER_ADCCR2 compare event reption register REPAB */

/* TIMER adc compare repeat counter decrement mode setting */
#define TIMER_ADC_REP_DEC_UNDERFLOW                        ((uint16_t)0x0000U)               /*!< ADC REPA/B decrement when cnt underflow */
#define TIMER_ADC_REP_DEC_OVERFLOW                         ((uint16_t)0x0001U)               /*!< ADC REPA/B decrement when cnt overflow */

/* TIMER shadow register selection */
#define TIMER_CH0CV_UPSEL                                  REGIDX_BIT(0, 0, 3)               /*!< select the TIMER_CH0CV register */
#define TIMER_CH0CV_ADD_UPSEL                              REGIDX_BIT(0, 3, 3)               /*!< select the TIMER_CH0COMV_ADD register */
#define TIMER_CH1CV_UPSEL                                  REGIDX_BIT(0, 6, 3)               /*!< select the TIMER_CH1CV register */
#define TIMER_CH1CV_ADD_UPSEL                              REGIDX_BIT(0, 9, 3)               /*!< select the TIMER_CH1COMV_ADD register */
#define TIMER_CH2CV_UPSEL                                  REGIDX_BIT(0, 12,3)               /*!< select the TIMER_CH2CV register */
#define TIMER_CH2CV_ADD_UPSEL                              REGIDX_BIT(0, 16,3)               /*!< select the TIMER_CH2COMV_ADD register */
#define TIMER_CH3CV_UPSEL                                  REGIDX_BIT(0, 19,3)               /*!< select the TIMER_CH3CV register */
#define TIMER_CH3CV_ADD_UPSEL                              REGIDX_BIT(0, 22,3)               /*!< select the TIMER_CH3COMV_ADD register */
#define TIMER_ADCCR1_UPSEL                                 REGIDX_BIT(0, 26,2)               /*!< select the TIMER_ADCCR1 register */
#define TIMER_ADCCR2_UPSEL                                 REGIDX_BIT(0, 28,2)               /*!< select the TIMER_ADCCR2 register */
#define TIMER_CAR_UPSEL                                    REGIDX_BIT(0, 30,2)               /*!< select the TIMER_CAR register */
#define TIMER_MCH0CV_UPSEL                                 REGIDX_BIT(1, 0, 2)               /*!< select the TIMER_MCH0CV register */
#define TIMER_MCH1CV_UPSEL                                 REGIDX_BIT(1, 2, 2)               /*!< select the TIMER_MCH1CV register */
#define TIMER_MCH2CV_UPSEL                                 REGIDX_BIT(1, 4, 2)               /*!< select the TIMER_MCH2CV register */
#define TIMER_MCH3CV_UPSEL                                 REGIDX_BIT(1, 6, 2)               /*!< select the TIMER_MCH3CV register */

/* TIMER register update event selection */
#define TIMER_UPDATE_MASK1                                 ((uint32_t)0x00000007U)               /*!< select the reg upmode mask1 */
#define TIMER_UPDATE_MASK2                                 ((uint32_t)0x00000003U)               /*!< select the reg upmode mask2 */
#define TIMER_UPDATE_GLOBAL                                ((uint32_t)0x00000000U)               /*!< select the reg upmode gloal reload */
#define TIMER_UPDATE_NEXT_OVERFLOW                         ((uint32_t)0x00000001U)               /*!< select the reg upmode at next overflow event */
#define TIMER_UPDATE_NEXT_UNDERFLOW                        ((uint32_t)0x00000002U)               /*!< select the reg upmode at next underflow event */
#define TIMER_UPDATE_NEXT_FLOW                             ((uint32_t)0x00000003U)               /*!< select the reg upmode at next flow event */
#define TIMER_UPDATE_NEXT_ADDCOMPARE_EVENT                 ((uint32_t)0x00000004U)               /*!< select the reg upmode at next add value compare event */

/* break automatic output function mode selection */
#define BRKAU_MODE(regval)                                 (BITS(2, 3) & ((uint32_t)(regval) << 2U))
#define TIMER_BRKAU_MODE_FLOW                              BRKAU_MODE(0)                     /*!< select the break auto recover at next flow event */
#define TIMER_BRKAU_MODE_OVERFLOW                          BRKAU_MODE(1)                     /*!< select the break auto recover at next overflow event */
#define TIMER_BRKAU_MODE_UNDERFLOW                         BRKAU_MODE(2)                     /*!< select the break auto recover at next underflow event */
#define TIMER_BRKAU_MODE_UPADATE_EVENT                     BRKAU_MODE(3)                     /*!< select the break auto recover at next update event */

/* reference signal output clear signal mode selection */
#define TIMER_REFCL_MODE_FLOW                              ((uint16_t)0x0000U)               /*!< select output clear recover at next flow event */
#define TIMER_REFCL_MODE_UPDATE_EVENT                      ((uint16_t)0x0003U)               /*!< select output clear recover at next update event */

/* function declarations */
/* TIMER timebase */
/* deinit a TIMER */
void timer_deinit(uint32_t timer_periph);
/* initialize TIMER init parameter struct */
void timer_struct_para_init(timer_parameter_struct *initpara);
/* initialize TIMER counter */
void timer_init(uint32_t timer_periph, timer_parameter_struct *initpara);
/* enable a TIMER */
void timer_enable(uint32_t timer_periph);
/* disable a TIMER */
void timer_disable(uint32_t timer_periph);
/* enable the auto reload shadow function */
void timer_auto_reload_shadow_enable(uint32_t timer_periph);
/* disable the auto reload shadow function */
void timer_auto_reload_shadow_disable(uint32_t timer_periph);
/* enable the update event */
void timer_update_event_enable(uint32_t timer_periph);
/* disable the update event */
void timer_update_event_disable(uint32_t timer_periph);
/* set TIMER counter alignment mode */
void timer_counter_alignment(uint32_t timer_periph, uint16_t aligned);
/* set TIMER counter up direction */
void timer_counter_up_direction(uint32_t timer_periph);
/* set TIMER counter down direction */
void timer_counter_down_direction(uint32_t timer_periph);
/* enable upif backup */
void timer_upif_backup_enable(uint32_t timer_periph);
/* disable upif backup */
void timer_upif_backup_disable(uint32_t timer_periph);
/* select the timer_interrupt source selection */
void timer_flow_interrupt_source_select(uint32_t timer_periph, uint32_t source);
/* select the timer update event source selection */
void timer_update_source_select(uint32_t timer_periph, uint32_t source);
/* select the TIMER ETI */
void timer_external_input_source_select(uint32_t timer_periph, uint32_t source);
/* configure TIMER prescaler */
void timer_prescaler_config(uint32_t timer_periph, uint16_t prescaler, uint32_t pscreload);
/* configure timer update repetition register value */
void timer_update_repetition_value_config(uint32_t timer_periph, uint16_t repetition);
/* configure timer flow interrupt repetition register value */
void timer_flow_interrupt_repetition_value_config(uint32_t timer_periph, uint16_t repetition);
/* flow interrupt repetition value reload */
void timer_flow_interrupt_repetition_value_reload(uint32_t timer_periph);
/* configure TIMER autoreload register value */
void timer_autoreload_value_config(uint32_t timer_periph, uint32_t autoreload);
/* get TIMER autoreload register value */
uint32_t timer_autoreload_value_read(uint32_t timer_periph);
/* configure TIMER counter register value */
void timer_counter_value_config(uint32_t timer_periph, uint32_t counter);
/* read TIMER counter value */
uint32_t timer_counter_read(uint32_t timer_periph);
/* read TIMER prescaler value */
uint16_t timer_prescaler_read(uint32_t timer_periph);
/* configure TIMER single pulse mode */
void timer_single_pulse_mode_config(uint32_t timer_periph, uint32_t spmode);
/* configure TIMER update event source */
void timer_update_source_config(uint32_t timer_periph, uint32_t update);
/* enable or disable channel capture/compare control shadow register */
void timer_channel_control_shadow_config(uint32_t timer_periph, ControlStatus newvalue);
/* configure TIMER channel control shadow register update control */
void timer_channel_control_shadow_update_config(uint32_t timer_periph, uint32_t ccuctl);
/* configure TIMER ocref_clr source */
void timer_ocpre_clr_source_select(uint32_t timer_periph, uint32_t ocrsel);
/* configure TIMER ocref_clr selection */
void timer_ocpre_clr_int_source_select(uint32_t timer_periph, uint32_t selection);

/* TIMER DMA and event */
/* enable the TIMER DMA */
void timer_dma_enable(uint32_t timer_periph, uint32_t dma);
/* disable the TIMER DMA */
void timer_dma_disable(uint32_t timer_periph, uint32_t dma);
/* channel DMA request source selection */
void timer_channel_dma_request_source_select(uint32_t timer_periph, uint32_t dma_request);
/* configure the TIMER DMA transfer */
void timer_dma_transfer_config(uint32_t timer_periph, uint32_t dma_baseaddr, uint32_t dma_lenth);
/* software generate events */
void timer_event_software_generate(uint32_t timer_periph, uint32_t event);

/* TIMER channel complementary protection */
/* initialize TIMER break parameter struct */
void timer_break_struct_para_init(timer_break_parameter_struct *breakpara);
/* configure TIMER break function */
void timer_break_config(uint32_t timer_periph, timer_break_parameter_struct *breakpara);
/* enable TIMER break function */
void timer_break_enable(uint32_t timer_periph);
/* disable TIMER break function */
void timer_break_disable(uint32_t timer_periph);
/* enable TIMER output automatic function */
void timer_automatic_output_enable(uint32_t timer_periph);
/* disable TIMER output automatic function */
void timer_automatic_output_disable(uint32_t timer_periph);
/* enable or disable TIMER primary output function */
void timer_primary_output_config(uint32_t timer_periph, ControlStatus newvalue);
/* break external input enable */
void timer_break_external_input_enable(uint32_t timer_periph);
/* break cmp enable */
void timer_break_cmp_enable(uint32_t timer_periph, uint32_t break_cmp);
/* break external input disable */
void timer_break_external_input_disable(uint32_t timer_periph);
/* break cmp disable */
void timer_break_cmp_disable(uint32_t timer_periph, uint32_t break_cmp);
/* configure TIMER break external input polarity */
void timer_break_external_input_polarity_config(uint32_t timer_periph, uint32_t polarity);
/* configure TIMER break cmp polarity */
void timer_break_cmp_polarity_config(uint32_t timer_periph, uint32_t break_cmp, uint32_t polarity);
/* break auto recover event selection */
void timer_break_auto_recover_event_select(uint32_t timer_periph, uint32_t event);

/* TIMER channel output */
/* initialize TIMER channel output parameter struct */
void timer_channel_output_struct_para_init(timer_oc_parameter_struct *ocpara);
/* configure TIMER channel output function */
void timer_channel_output_config(uint32_t timer_periph, uint16_t channel, timer_oc_parameter_struct *ocpara);
/* configure TIMER channel output compare mode */
void timer_channel_output_mode_config(uint32_t timer_periph, uint16_t channel, uint32_t ocmode);
/* configure TIMER channel output pulse value */
void timer_channel_output_pulse_value_config(uint32_t timer_periph, uint16_t channel, uint32_t pulse);
/* configure TIMER channel output shadow function */
void timer_channel_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow);
/* configure TIMER channel output fast function */
void timer_channel_output_compare_fast_config(uint32_t timer_periph, uint16_t channel, uint16_t ocfast);
/* configure TIMER channel output clear function */
void timer_channel_output_clear_config(uint32_t timer_periph, uint16_t channel, uint16_t occlear);
/* configure TIMER channel output polarity */
void timer_channel_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocpolarity);
/* configure TIMER channel complementary output polarity */
void timer_channel_complementary_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnpolarity);
/* configure TIMER channel enable state */
void timer_channel_output_state_config(uint32_t timer_periph, uint16_t channel, uint32_t state);
/* configure TIMER channel complementary output enable state */
void timer_channel_complementary_output_state_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnstate);
/* initialize TIMER multi mode channel output parameter struct */
void timer_multi_mode_channel_output_parameter_struct_init(timer_omc_parameter_struct *omcpara);
/* configure TIMER multi mode channel output function */
void timer_multi_mode_channel_output_config(uint32_t timer_periph, uint16_t channel, timer_omc_parameter_struct *omcpara);
/* select multi mode channel mode */
void timer_multi_mode_channel_mode_config(uint32_t timer_periph, uint32_t channel, uint32_t multi_mode_sel);
/* configure TIMER write CHxVAL register selection */
void timer_write_chxval_register_config(uint32_t timer_periph, uint16_t ccsel);
/* configure TIMER output value selection */
void timer_output_value_selection_config(uint32_t timer_periph, uint16_t outsel);
/* configure TIMER output match pulse selection */
void timer_output_match_pulse_select(uint32_t timer_periph, uint32_t channel, uint16_t pulsesel);
/* configure the TIMER composite PWM mode output pulse value*/
void timer_channel_composite_pwm_pulse_config(uint32_t timer_periph, uint32_t channel, uint32_t pulse, uint32_t add_pulse);
/* configure the TIMER asymmetric PWM mode output pulse value*/
void timer_channel_asymmetric_pwm_pulse_config(uint32_t timer_periph, uint32_t channel, uint32_t pulse, uint32_t add_pulse);
/* configure TIMER channel additional compare value */
void timer_channel_additional_compare_value_config(uint32_t timer_periph, uint16_t channel, uint32_t value);
/* read TIMER channel additional compare value */
uint16_t timer_channel_additional_compare_value_read(uint32_t timer_periph, uint16_t channel);
/* configure TIMER channel additional output shadow function */
void timer_channel_additional_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t aocshadow);
/* configure TIMER channel period point match moment OxCPRE level in the composite PWM or asymmetric PWM mode */
void timer_channel_composite_asymmetric_pwm_level_config(uint32_t timer_periph, uint16_t channel, ControlStatus newvalue);

/* TIMER channel input */
/* initialize TIMER channel input parameter struct */
void timer_channel_input_struct_para_init(timer_ic_parameter_struct *icpara);
/* configure TIMER input capture parameter */
void timer_input_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct *icpara);
/* configure TIMER channel input capture prescaler value */
void timer_channel_input_capture_prescaler_config(uint32_t timer_periph, uint16_t channel, uint16_t prescaler);
/* read TIMER channel capture compare register value */
uint32_t timer_channel_capture_value_register_read(uint32_t timer_periph, uint16_t channel);
/* configure TIMER input pwm capture function */
void timer_input_pwm_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct *icpwm);
/* configure TIMER hall sensor mode */
void timer_hall_mode_config(uint32_t timer_periph, uint32_t hallmode);


/* TIMER master and external clock mode */
/* select TIMER input trigger source */
void timer_input_trigger_source_select(uint32_t timer_periph, uint32_t intrigger);
/* select TIMER master mode output trigger source*/
void timer_master_output_trigger_source_select(uint32_t timer_periph, uint32_t outrigger);
/* select TIMER slave mode */
void timer_slave_mode_select(uint32_t timer_periph, uint32_t slavemode);
/* configure TIMER master slave mode */
void timer_master_slave_mode_config(uint32_t timer_periph, uint32_t masterslave);
/* configure TIMER external trigger input */
void timer_external_trigger_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);
/* configure TIMER quadrature decoder mode */
void timer_quadrature_decoder_mode_config(uint32_t timer_periph, uint32_t decomode, uint16_t ic0polarity, uint16_t ic1polarity);
/* configure TIMER non-quadrature decoder mode */
void timer_non_quadrature_decoder_mode_config(uint32_t timer_periph, uint32_t decomode, uint16_t ic0polarity, uint16_t ic1polarity);
/* configure TIMER internal clock mode */
void timer_internal_clock_config(uint32_t timer_periph);
/* configure TIMER the internal trigger as external clock input */
void timer_internal_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t intrigger);
/* configure TIMER the external trigger as external clock input */
void timer_external_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t extrigger, uint16_t extpolarity, uint32_t extfilter);
/* configure TIMER slave mode input */
void timer_slave_mode_input_config(uint32_t timer_periph, uint32_t channel, uint16_t extpolarity, uint32_t extfilter);
/* configure TIMER the external clock mode0 */
void timer_external_clock_mode0_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);
/* configure TIMER the external clock mode1 */
void timer_external_clock_mode1_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);
/* disable TIMER the external clock mode1 */
void timer_external_clock_mode1_disable(uint32_t timer_periph);

/* TIMER adc trigger config*/
/* enable compare produce ADC signal */
void timer_trigger_adc_compare_enable(uint32_t timer_periph, uint32_t compare_time);
/* disable compare produce ADC signal */
void timer_trigger_adc_compare_disable(uint32_t timer_periph, uint32_t compare_time);
/* enable flow produce flow signal*/
void timer_trigger_adc_flow_enable(uint32_t timer_periph, uint32_t flow_timer);
/* disable flow produce flow signal */
void timer_trigger_adc_flow_disable(uint32_t timer_periph, uint32_t flow_timer);
/* configure adc trigger compare value register value  */
void timer_trigger_adc_compare_value_config(uint32_t timer_periph, uint32_t compare,  uint16_t value);
/*configure the TIMER trigger ADC repetition register value */
void timer_trigger_adc_repetition_value_config(uint32_t timer_periph, uint32_t timer_adc_crep, uint16_t value);
/* select adc repetition_decrement source */
void timer_trigger_adc_repetition_decrement_select(uint32_t timer_periph, uint32_t timer_adc_crep, uint16_t source);
/* reload adc repetition register value */
void timer_trigger_adc_repetition_value_reload(uint32_t timer_periph);
/* enable adc compare register shadow function */
void timer_trigger_adc_compare_value_shadow_enable(uint32_t timer_periph, uint32_t timer_adc_cmpval);
/* disable adc compare register shadow function */
void timer_trigger_adc_compare_value_shadow_disable(uint32_t timer_periph, uint32_t timer_adc_cmpval);
/* configure ADC trigger signal monitoring function */
void timer_trigger_adc_monitor_config(uint32_t timer_periph, uint32_t adcsm, uint32_t adcsm_sel, ControlStatus newvalue);

/* TIMER register update method config */
/* register update event selection */
void timer_register_update_event_select(uint32_t timer_periph, uint32_t reg, uint32_t event);

/* TIMER interrupt and flag */
/* get TIMER flags */
FlagStatus timer_flag_get(uint32_t timer_periph, uint32_t flag);
/* clear TIMER flags */
void timer_flag_clear(uint32_t timer_periph, uint32_t flag);
/* enable the TIMER interrupt */
void timer_interrupt_enable(uint32_t timer_periph, uint32_t interrupt);
/* disable the TIMER interrupt */
void timer_interrupt_disable(uint32_t timer_periph, uint32_t interrupt);
/* get timer interrupt flag */
FlagStatus timer_interrupt_flag_get(uint32_t timer_periph, uint32_t int_flag);
/* clear TIMER interrupt flag */
void timer_interrupt_flag_clear(uint32_t timer_periph, uint32_t int_flag);

#endif /* GD32M53X_TIMER_H */
