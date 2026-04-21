/*!
    \file    gd32m53x_adc.h
    \brief   definitions for the ADC

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

#ifndef GD32M53X_ADC_H
#define GD32M53X_ADC_H

#include "gd32m53x.h"

/* ADC definitions */
#define ADC0                                ADC_BASE                                        /*!< ADC0 base address */
#define ADC2                                (ADC_BASE + 0x00000400U)                        /*!< ADC2 base address */

/* registers definitions */
#define ADC_EOCCTL(adcx)                    REG32((adcx) + 0x00000000U)                     /*!< software EOC control register */
#define ADC_CTL0(adcx)                      REG32((adcx) + 0x00000004U)                     /*!< control register 0 */
#define ADC_GPCGF0(adcx)                    REG32((adcx) + 0x00000008U)                     /*!< group config register 0 */
#define ADC_GPCGF1(adcx)                    REG32((adcx) + 0x0000000CU)                     /*!< group config register 1 */
#define ADC_CHSEL0(adcx)                    REG32((adcx) + 0x00000010U)                     /*!< channel selection register 0 */
#define ADC_CHSEL1(adcx)                    REG32((adcx) + 0x00000014U)                     /*!< channel selection register 1 */
#define ADC_SAMPR0(adcx)                    REG32((adcx) + 0x00000020U)                     /*!< sample time register 0 */
#define ADC_SAMPR1(adcx)                    REG32((adcx) + 0x00000024U)                     /*!< sample time register 1 */
#define ADC_SAMPR2(adcx)                    REG32((adcx) + 0x00000028U)                     /*!< sample time register 2, only for ADC2 */
#define ADC_CHPRI0(adcx)                    REG32((adcx) + 0x00000030U)                     /*!< channel priority register 0 */
#define ADC_CHPRI1(adcx)                    REG32((adcx) + 0x00000034U)                     /*!< channel priority register 1 */
#define ADC_ADDT0(adcx)                     REG32((adcx) + 0x00000040U)                     /*!< channel addition value config register 0 */
#define ADC_ADDT1(adcx)                     REG32((adcx) + 0x00000044U)                     /*!< channel addition value config register 1, only for ADC2 */
#define ADC_SDDATA(adcx)                    REG32((adcx) + 0x00000050U)                     /*!< self-diagnosis data register */
#define ADC_GP1BIDATA(adcx)                 REG32((adcx) + 0x00000060U)                     /*!< Group_pri1 bifurcate data register */
#define ADC_GP1BIDATA1(adcx)                REG32((adcx) + 0x00000064U)                     /*!< Group_pri1 bifurcate data register 1 */
#define ADC_GP1BIDATA2(adcx)                REG32((adcx) + 0x00000068U)                     /*!< Group_pri1 bifurcate data register 2 */
#define ADC_GP2BIDATA(adcx)                 REG32((adcx) + 0x0000006CU)                     /*!< Group_pri2 bifurcate data register */
#define ADC_GP2BIDATA1(adcx)                REG32((adcx) + 0x00000070U)                     /*!< Group_pri2 bifurcate data register 1 */
#define ADC_GP2BIDATA2(adcx)                REG32((adcx) + 0x00000074U)                     /*!< Group_pri2 bifurcate data register 2 */
#define ADC_GP3BIDATA(adcx)                 REG32((adcx) + 0x00000078U)                     /*!< Group_pri3 bifurcate data register */
#define ADC_GP3BIDATA1(adcx)                REG32((adcx) + 0x0000007CU)                     /*!< Group_pri3 bifurcate data register 1 */
#define ADC_GP3BIDATA2(adcx)                REG32((adcx) + 0x00000080U)                     /*!< Group_pri3 bifurcate data register 2 */
#define ADC_GP4BIDATA(adcx)                 REG32((adcx) + 0x00000084U)                     /*!< Group_pri4 bifurcate data register */
#define ADC_GP4BIDATA1(adcx)                REG32((adcx) + 0x00000088U)                     /*!< Group_pri4 bifurcate data register 1 */
#define ADC_GP4BIDATA2(adcx)                REG32((adcx) + 0x0000008CU)                     /*!< Group_pri4 bifurcate data register 2 */
#define ADC_GP1DMAR(adcx)                   REG32((adcx) + 0x00000090U)                     /*!< Group_pri1 data DMA register */
#define ADC_GP2DMAR(adcx)                   REG32((adcx) + 0x00000094U)                     /*!< Group_pri2 data DMA register */
#define ADC_GP3DMAR(adcx)                   REG32((adcx) + 0x00000098U)                     /*!< Group_pri3 data DMA register */
#define ADC_GP4DMAR(adcx)                   REG32((adcx) + 0x0000009CU)                     /*!< Group_pri4 data DMA register */
#define ADC_CH0DATA(adcx)                   REG32((adcx) + 0x000000A0U)                     /*!< channel 0 data register */
#define ADC_CH1DATA(adcx)                   REG32((adcx) + 0x000000A4U)                     /*!< channel 1 data register */
#define ADC_CH2DATA(adcx)                   REG32((adcx) + 0x000000A8U)                     /*!< channel 2 data register */
#define ADC_CH3DATA(adcx)                   REG32((adcx) + 0x000000ACU)                     /*!< channel 3 data register */
#define ADC_CH4DATA(adcx)                   REG32((adcx) + 0x000000B0U)                     /*!< channel 4 data register */
#define ADC_CH5DATA(adcx)                   REG32((adcx) + 0x000000B4U)                     /*!< channel 5 data register */
#define ADC_CH6DATA(adcx)                   REG32((adcx) + 0x000000B8U)                     /*!< channel 6 data register */
#define ADC_CH7DATA(adcx)                   REG32((adcx) + 0x000000BCU)                     /*!< channel 7 data register, only for ADC2 */
#define ADC_CH8DATA(adcx)                   REG32((adcx) + 0x000000C0U)                     /*!< channel 8 data register, only for ADC2 */
#define ADC_CH9DATA(adcx)                   REG32((adcx) + 0x000000C4U)                     /*!< channel 9 data register, only for ADC2 */
#define ADC_TEMPDATA(adcx)                  REG32((adcx) + 0x000000C8U)                     /*!< temperature sensor channel data register, only for ADC2 */
#define ADC_VINTDATA(adcx)                  REG32((adcx) + 0x000000CCU)                     /*!< internal reference voltage channel data register, only for ADC2 */
#define ADC_WDCTL(adcx)                     REG32((adcx) + 0x00000100U)                     /*!< watchdog control register */
#define ADC_WDATHOLD(adcx)                  REG32((adcx) + 0x00000104U)                     /*!< watchdog A threshold register */
#define ADC_WDBTHOLD(adcx)                  REG32((adcx) + 0x00000108U)                     /*!< watchdog B threshold register */
#define ADC_WDACHCFG(adcx)                  REG32((adcx) + 0x0000010CU)                      /*!< watchdog A channel config register */
#define ADC_WDACHSTAT(adcx)                 REG32((adcx) + 0x00000110U)                     /*!< watchdog A channel status register */
#define ADC_CTL1(adcx)                      REG32((adcx) + 0x00000150U)                     /*!< control register 1 */
#define ADC_SHCTL                           REG32((ADC0) + 0x00000160U)                     /*!< sample-and-hold control register */
#define ADC_DMACTL(adcx)                    REG32((adcx) + 0x00000170U)                     /*!< DMA control register */
#define ADC_BITRGCTL(adcx)                  REG32((adcx) + 0x00000180U)                     /*!< bifurcate trigger control register */

/* bits definitions */
/* ADC_EOCCTL */
#define ADC_EOCCTL_EVICG1SEL                BIT(0)                                          /*!< EVIC trigger signal select from Group_pri1 */
#define ADC_EOCCTL_GP1SWST                  BIT(1)                                          /*!< software start conversion of Group_pri1 */
#define ADC_EOCCTL_EOC1RIE                  BIT(2)                                          /*!< interrupt enable for EOC1RF */
#define ADC_EOCCTL_EOC1F                    BIT(3)                                          /*!< end of Group_pri1 conversion flag */
#define ADC_EOCCTL_EOC1RF                   BIT(4)                                          /*!< end of Group_pri1 conversion round flag */
#define ADC_EOCCTL_EOC1RCNT                 BITS(5,7)                                       /*!< end of Group_pri1 conversion round counts */
#define ADC_EOCCTL_EVICG2SEL                BIT(8)                                          /*!< EVIC trigger signal select from Group_pri2 */
#define ADC_EOCCTL_GP2SWST                  BIT(9)                                          /*!< software start conversion of Group_pri2 */
#define ADC_EOCCTL_EOC2RIE                  BIT(10)                                         /*!< interrupt enable for EOC2RF */
#define ADC_EOCCTL_EOC2F                    BIT(11)                                         /*!< end of Group_pri2 conversion flag */
#define ADC_EOCCTL_EOC2RF                   BIT(12)                                         /*!< end of Group_pri2 conversion round flag */
#define ADC_EOCCTL_EOC2RCNT                 BITS(13,15)                                     /*!< end of Group_pri2 conversion round counts */
#define ADC_EOCCTL_EVICG3SEL                BIT(16)                                         /*!< EVIC trigger signal select from Group_pri3 */
#define ADC_EOCCTL_GP3SWST                  BIT(17)                                         /*!< software start conversion of Group_pri3 */
#define ADC_EOCCTL_EOC3RIE                  BIT(18)                                         /*!< interrupt enable for EOC3RF */
#define ADC_EOCCTL_EOC3F                    BIT(19)                                         /*!< end of Group_pri3 conversion flag */
#define ADC_EOCCTL_EOC3RF                   BIT(20)                                         /*!< end of Group_pri3 conversion round flag */
#define ADC_EOCCTL_EOC3RCNT                 BITS(21,23)                                     /*!< end of Group_pri3 conversion round counts */
#define ADC_EOCCTL_EVICG4SEL                BIT(24)                                         /*!< EVIC trigger signal select from Group_pri4 */
#define ADC_EOCCTL_GP4SWST                  BIT(25)                                         /*!< software start conversion of Group_pri4 */
#define ADC_EOCCTL_EOC4RIE                  BIT(26)                                         /*!< interrupt enable for EOC4RF */
#define ADC_EOCCTL_EOC4F                    BIT(27)                                         /*!< end of Group_pri4 conversion flag */
#define ADC_EOCCTL_EOC4RF                   BIT(28)                                         /*!< end of Group_pri4 conversion round flag */
#define ADC_EOCCTL_EOC4RCNT                 BITS(29,31)                                     /*!< end of Group_pri4 conversion round counts */

/* ADC_CTL0 */
#define ADC_CTL0_LPGCNT                     BIT(0)                                          /*!< enable lowest-priority group scan continuous */
#define ADC_CTL0_GPRIEN                     BIT(3)                                          /*!< enable group priority */
#define ADC_CTL0_CHRSEL                     BITS(4,8)                                       /*!< select precharge and discharge */
#define ADC_CTL0_CHRSEL_MODE                BIT(8)                                          /*!< A/D disconnection detection assist mode */
#define ADC_CTL0_CHRSEL_PERIOD              BITS(4,7)                                       /*!< A/D disconnection detection assist period */
#define ADC_CTL0_DAL                        BIT(9)                                          /*!< data storage alignment mode */
#define ADC_CTL0_SDSEN                      BIT(10)                                         /*!< enable self-diagnosis */
#define ADC_CTL0_SDSFIX                     BIT(11)                                         /*!< enable fix mode for self-diagnosis voltage */
#define ADC_CTL0_SDVOG                      BITS(12,13)                                     /*!< configure fix voltage for self-diagnosis conversion */
#define ADC_CTL0_ACDATA                     BIT(14)                                         /*!< enable automatic clearing data registers */
#define ADC_CTL0_ASDATA                     BIT(15)                                         /*!< enable automatic setting data registers */
#define ADC_CTL0_ADDEN                      BIT(16)                                         /*!< addition function enable */
#define ADC_CTL0_PROCF                      BIT(19)                                         /*!< A/D conversion process flag */
#define ADC_CTL0_GSCAN                      BITS(20,21)                                     /*!< group scan mode */
#define ADC_CTL0_ADDSEL                     BIT(22)                                         /*!< A/D conversion data addition mode selection */
#define ADC_CTL0_GP3EN                      BIT(23)                                         /*!< enable A/D conversion operation for Group_pri3 */
#define ADC_CTL0_GP4EN                      BIT(24)                                         /*!< enable A/D conversion operation for Group_pri4 */
#define ADC_CTL0_EVICCTL                    BITS(28,30)                                     /*!< EVIC link signal control */
#define ADC_CTL0_SWEND                      BIT(31)                                         /*!< software end conversion of Group_pri1/pri2/pri3/pri4 */

/* ADC_GPCGF0 */
#define ADC_GPCGF0_G1TRGEN                  BIT(0)                                          /*!< enable Group_pri1 synchronous or asynchronous trigger */
#define ADC_GPCGF0_GP1TRGTY                 BIT(1)                                          /*!< group_pri1 trigger type select */
#define ADC_GPCGF0_GP1TRGSRC                BITS(2,7)                                       /*!< synchronous trigger source for Group_pri1 */
#define ADC_GPCGF0_GP1TRGED                 BITS(8,9)                                       /*!< trigger edge select of Group_pri1 */
#define ADC_GPCGF0_G2TRGEN                  BIT(16)                                         /*!< enable Group_pri2 synchronous or asynchronous trigger */
#define ADC_GPCGF0_GP2TRGTY                 BIT(17)                                         /*!< Group_pri2 trigger type select */
#define ADC_GPCGF0_GP2TRGSRC                BITS(18,23)                                     /*!< synchronous trigger source for Group_pri2 */
#define ADC_GPCGF0_GP2TRGED                 BITS(24,25)                                     /*!< trigger edge select of Group_pri2 */
#define ADC_GPCGF0_GP2RTCH                  BIT(28)                                         /*!< Group_pri2 rescan channel select */
#define ADC_GPCGF0_GP2RTEN                  BIT(29)                                         /*!< enable Group_pri2 rescan */

/* ADC_GPCGF1 */
#define ADC_GPCGF1_G3TRGEN                  BIT(0)                                          /*!< enable Group_pri3 synchronous or asynchronous trigger */
#define ADC_GPCGF1_GP3TRGTY                 BIT(1)                                          /*!< Group_pri3 trigger type select */
#define ADC_GPCGF1_GP3TRGSRC                BITS(2,7)                                       /*!< synchronous trigger source for Group_pri3 */
#define ADC_GPCGF1_GP3TRGED                 BITS(8,9)                                       /*!< trigger edge select of Group_pri3 */
#define ADC_GPCGF1_GP3RTCH                  BIT(12)                                         /*!< Group_pri3 rescan channel select */
#define ADC_GPCGF1_GP3RTEN                  BIT(13)                                         /*!< enable Group_pri3 rescan */
#define ADC_GPCGF1_G4TRGEN                  BIT(16)                                         /*!< enable Group_pri4 synchronous or asynchronous trigger */
#define ADC_GPCGF1_GP4TRGTY                 BIT(17)                                         /*!< Group_pri4 trigger type select */
#define ADC_GPCGF1_GP4TRGSRC                BITS(18,23)                                     /*!< synchronous trigger source for Group_pri4 */
#define ADC_GPCGF1_GP4TRGED                 BITS(24,25)                                     /*!< trigger edge select of Group_pri4 */
#define ADC_GPCGF1_GP4RTCH                  BIT(28)                                         /*!< Group_pri4 rescan channel select */
#define ADC_GPCGF1_GP4RTEN                  BIT(29)                                         /*!< enable Group_pri4 rescan */

/* ADC_CHSEL0 */
#define ADC_CHANNEL_GP1_ALL                 BITS(0,11)                                      /*!< All channel in Group_pri1 */
#define ADC_CHANNEL_GP2_ALL                 BITS(16,27)                                     /*!< All channel in Group_pri2 */
#define ADC_CHSEL0_GP1CH0                   BIT(0)                                          /*!< select channel ADCx_IN0 in Group_pri1 */
#define ADC_CHSEL0_GP1CH1                   BIT(1)                                          /*!< select channel ADCx_IN1 in Group_pri1 */
#define ADC_CHSEL0_GP1CH2                   BIT(2)                                          /*!< select channel ADCx_IN2 in Group_pri1 */
#define ADC_CHSEL0_GP1CH3                   BIT(3)                                          /*!< select channel ADCx_IN3 in Group_pri1 */
#define ADC_CHSEL0_GP1CH4                   BIT(4)                                          /*!< select channel ADCx_IN4 in Group_pri1 */
#define ADC_CHSEL0_GP1CH5                   BIT(5)                                          /*!< select channel ADCx_IN5 in Group_pri1 */
#define ADC_CHSEL0_GP1CH6                   BIT(6)                                          /*!< select channel ADCx_IN6 in Group_pri1 */
#define ADC_CHSEL0_GP1CH7                   BIT(7)                                          /*!< select channel ADCx_IN7 in Group_pri1 */
#define ADC_CHSEL0_GP1CH8                   BIT(8)                                          /*!< select channel ADCx_IN8 in Group_pri1 */
#define ADC_CHSEL0_GP1CH9                   BIT(9)                                          /*!< select channel ADCx_IN9 in Group_pri1 */
#define ADC_CHSEL0_GP1TEMP                  BIT(10)                                         /*!< select temperature sensor channel in Group_pri1 */
#define ADC_CHSEL0_GP1VINT                  BIT(11)                                         /*!< select internal reference voltage channel in Group_pri1 */
#define ADC_CHSEL0_GP2CH0                   BIT(16)                                         /*!< select channel ADCx_IN0 in Group_pri2 */
#define ADC_CHSEL0_GP2CH1                   BIT(17)                                         /*!< select channel ADCx_IN1 in Group_pri2 */
#define ADC_CHSEL0_GP2CH2                   BIT(18)                                         /*!< select channel ADCx_IN2 in Group_pri2 */
#define ADC_CHSEL0_GP2CH3                   BIT(19)                                         /*!< select channel ADCx_IN3 in Group_pri2 */
#define ADC_CHSEL0_GP2CH4                   BIT(20)                                         /*!< select channel ADCx_IN4 in Group_pri2 */
#define ADC_CHSEL0_GP2CH5                   BIT(21)                                         /*!< select channel ADCx_IN5 in Group_pri2 */
#define ADC_CHSEL0_GP2CH6                   BIT(22)                                         /*!< select channel ADCx_IN6 in Group_pri2 */
#define ADC_CHSEL0_GP2CH7                   BIT(23)                                         /*!< select channel ADCx_IN7 in Group_pri2 */
#define ADC_CHSEL0_GP2CH8                   BIT(24)                                         /*!< select channel ADCx_IN8 in Group_pri2 */
#define ADC_CHSEL0_GP2CH9                   BIT(25)                                         /*!< select channel ADCx_IN9 in Group_pri2 */
#define ADC_CHSEL0_GP2TEMP                  BIT(26)                                         /*!< select temperature sensor channel in Group_pri2 */
#define ADC_CHSEL0_GP2VINT                  BIT(27)                                         /*!< select internal reference voltage channel in Group_pri2 */

/* ADC_CHSEL1 */
#define ADC_CHANNEL_GP3_ALL                 BITS(0,11)                                      /*!< All channel in Group_pri3 */
#define ADC_CHANNEL_GP4_ALL                 BITS(16,27)                                     /*!< All channel in Group_pri4 */
#define ADC_CHSEL0_GP3CH0                   BIT(0)                                          /*!< select channel ADCx_IN0 in Group_pri3 */
#define ADC_CHSEL0_GP3CH1                   BIT(1)                                          /*!< select channel ADCx_IN1 in Group_pri3 */
#define ADC_CHSEL0_GP3CH2                   BIT(2)                                          /*!< select channel ADCx_IN2 in Group_pri3 */
#define ADC_CHSEL0_GP3CH3                   BIT(3)                                          /*!< select channel ADCx_IN3 in Group_pri3 */
#define ADC_CHSEL0_GP3CH4                   BIT(4)                                          /*!< select channel ADCx_IN4 in Group_pri3 */
#define ADC_CHSEL0_GP3CH5                   BIT(5)                                          /*!< select channel ADCx_IN5 in Group_pri3 */
#define ADC_CHSEL0_GP3CH6                   BIT(6)                                          /*!< select channel ADCx_IN6 in Group_pri3 */
#define ADC_CHSEL0_GP3CH7                   BIT(7)                                          /*!< select channel ADCx_IN7 in Group_pri3 */
#define ADC_CHSEL0_GP3CH8                   BIT(8)                                          /*!< select channel ADCx_IN8 in Group_pri3 */
#define ADC_CHSEL0_GP3CH9                   BIT(9)                                          /*!< select channel ADCx_IN9 in Group_pri3 */
#define ADC_CHSEL0_GP3TEMP                  BIT(10)                                         /*!< select temperature sensor channel in Group_pri3 */
#define ADC_CHSEL0_GP3VINT                  BIT(11)                                         /*!< select internal reference voltage channel in Group_pri3 */
#define ADC_CHSEL0_GP4CH0                   BIT(16)                                         /*!< select channel ADCx_IN0 in Group_pri4 */
#define ADC_CHSEL0_GP4CH1                   BIT(17)                                         /*!< select channel ADCx_IN1 in Group_pri4 */
#define ADC_CHSEL0_GP4CH2                   BIT(18)                                         /*!< select channel ADCx_IN2 in Group_pri4 */
#define ADC_CHSEL0_GP4CH3                   BIT(19)                                         /*!< select channel ADCx_IN3 in Group_pri4 */
#define ADC_CHSEL0_GP4CH4                   BIT(20)                                         /*!< select channel ADCx_IN4 in Group_pri4 */
#define ADC_CHSEL0_GP4CH5                   BIT(21)                                         /*!< select channel ADCx_IN5 in Group_pri4 */
#define ADC_CHSEL0_GP4CH6                   BIT(22)                                         /*!< select channel ADCx_IN6 in Group_pri4 */
#define ADC_CHSEL0_GP4CH7                   BIT(23)                                         /*!< select channel ADCx_IN7 in Group_pri4 */
#define ADC_CHSEL0_GP4CH8                   BIT(24)                                         /*!< select channel ADCx_IN8 in Group_pri4 */
#define ADC_CHSEL0_GP4CH9                   BIT(25)                                         /*!< select channel ADCx_IN9 in Group_pri4 */
#define ADC_CHSEL0_GP4TEMP                  BIT(26)                                         /*!< select temperature sensor channel in Group_pri4 */
#define ADC_CHSEL0_GP4VINT                  BIT(27)                                         /*!< select internal reference voltage channel in Group_pri4 */

/* ADC_SAMPR0 */
#define ADC_SAMPR0_SPT00                    BITS(0,7)                                       /*!< sample time config for channel ADCx_IN0 */
#define ADC_SAMPR0_SPT01                    BITS(8,15)                                      /*!< sample time config for channel ADCx_IN1 */
#define ADC_SAMPR0_SPT02                    BITS(16,23)                                     /*!< sample time config for channel ADCx_IN2 */
#define ADC_SAMPR0_SPT03                    BITS(24,31)                                     /*!< sample time config for channel ADCx_IN3 */

/* ADC_SAMPR1 */
#define ADC_SAMPR1_SPT04                    BITS(0,7)                                       /*!< sample time config for channel ADCx_IN4 */
#define ADC_SAMPR1_SPT05                    BITS(8,15)                                      /*!< sample time config for channel ADCx_IN5 */
#define ADC_SAMPR1_SPT06                    BITS(16,23)                                     /*!< sample time config for channel ADCx_IN6 */
#define ADC_SAMPR1_SPT07                    BITS(24,31)                                     /*!< sample time config for channel ADCx_IN7 */

/* ADC_SAMPR2 */
#define ADC_SAMPR2_SPT08                    BITS(0,7)                                       /*!< sample time config for channel ADCx_IN8 */
#define ADC_SAMPR2_SPT09                    BITS(8,15)                                      /*!< sample time config for channel ADCx_IN9 */
#define ADC_SAMPR2_SPTTEMP                  BITS(16,23)                                     /*!< sample time config for the temperature sensor channel */
#define ADC_SAMPR2_SPTVINT                  BITS(24,31)                                     /*!< sample time config for the internal voltage channel */

/* ADC_CHPRI0 */
#define ADC_CHPRI0_PRI0                    BITS(0,3)                                       /*!< the 1th priority of the selected channel */
#define ADC_CHPRI0_PRI1                    BITS(4,7)                                       /*!< the 2th priority of the selected channel */
#define ADC_CHPRI0_PRI2                    BITS(8,11)                                      /*!< the 3th priority of the selected channel */
#define ADC_CHPRI0_PRI3                    BITS(12,15)                                     /*!< the 4th priority of the selected channel */
#define ADC_CHPRI0_PRI4                    BITS(16,19)                                     /*!< the 5th priority of the selected channel */
#define ADC_CHPRI0_PRI5                    BITS(20,23)                                     /*!< the 6th priority of the selected channel */
#define ADC_CHPRI0_PRI6                    BITS(24,27)                                     /*!< the 7th priority of the selected channel */
#define ADC_CHPRI0_PRI7                    BITS(28,31)                                     /*!< the 8th priority of the selected channel */

/* ADC_CHPRI1 */
#define ADC_CHPRI1_PRI8                    BITS(0,3)                                       /*!< the 9th priority of the selected channel */
#define ADC_CHPRI1_PRI9                    BITS(4,7)                                       /*!< the 10th priority of the selected channel */
#define ADC_CHPRI1_PRI10                   BITS(8,11)                                      /*!< the 11th priority of the selected channel */
#define ADC_CHPRI1_PRI11                   BITS(12,15)                                     /*!< the 12th priority of the selected channel */

/* ADC_ADDT0 */
#define ADC_ADDT0_CH0ADDT                   BITS(0,3)                                       /*!< the total addition conversion times of ADCx_IN0 */
#define ADC_ADDT0_CH1ADDT                   BITS(4,7)                                       /*!< the total addition conversion times of ADCx_IN1 */
#define ADC_ADDT0_CH2ADDT                   BITS(8,11)                                      /*!< the total addition conversion times of ADCx_IN2 */
#define ADC_ADDT0_CH3ADDT                   BITS(12,15)                                     /*!< the total addition conversion times of ADCx_IN3 */
#define ADC_ADDT0_CH4ADDT                   BITS(16,19)                                     /*!< the total addition conversion times of ADCx_IN4 */
#define ADC_ADDT0_CH5ADDT                   BITS(20,23)                                     /*!< the total addition conversion times of ADCx_IN5 */
#define ADC_ADDT0_CH6ADDT                   BITS(24,27)                                     /*!< the total addition conversion times of ADCx_IN6 */
#define ADC_ADDT0_CH7ADDT                   BITS(28,31)                                     /*!< the total addition conversion times of ADCx_IN7 */

/* ADC_ADDT1 */
#define ADC_ADDT1_CH8ADDT                   BITS(0,3)                                       /*!< the total addition conversion times of ADCx_IN8 */
#define ADC_ADDT1_CH9ADDT                   BITS(4,7)                                       /*!< the total addition conversion times of ADCx_IN9 */
#define ADC_ADDT1_TEMPADDT                  BITS(8,11)                                      /*!< the total addition conversion times of temperature sensor channel */
#define ADC_ADDT1_VINTADDT                  BITS(12,15)                                     /*!< the total addition conversion times of internal reference voltage channel */

/* ADC_SDDATA */
#define ADC_SDDATA_SDDATA_LSB               BITS(0,11)                                      /*!< LSB alignment (DAL=0): self-diagnosis channel data */
#define ADC_SDDATA_SDSTA_LSB                BITS(14,15)                                     /*!< LSB alignment (DAL=0): voltage status converted by self-diagnosis */
#define ADC_SDDATA_SDDATA_MSB               BITS(4,15)                                      /*!< MSB alignment (DAL=1): self-diagnosis channel data */
#define ADC_SDDATA_SDSTA_MSB                BITS(0,1)                                       /*!< MSB alignment (DAL=1): voltage status converted by self-diagnosis */

/* ADC_GPxBIDATA, x=1,2,3,4 */
#define ADC_GPXBIDATA_BIDATA                BITS(0,15)                                      /*!< the data by the second trigger in bifurcate trigger mode */

/* ADC_GPxBIDATA1, x=1,2,3,4 */
#define ADC_GPXBIDATA1_BIDATA1              BITS(0,15)                                      /*!< the data by the first trigger in extended bifurcate trigger mode */

/* ADC_GPxBIDATA2, x=1,2,3,4 */
#define ADC_GPXBIDATA2_BIDATA2              BITS(0,15)                                      /*!< the data by the second trigger in extended bifurcate trigger mode */

/* ADC_GPxDMAR, x=1,2,3,4 */
#define ADC_GPXDMAR_GDATA                   BITS(0,15)                                      /*!< the data of Group_prix which can be accessed by DMA */

/* ADC_CHxDATA, for ADC0, x=0..6, for ADC2, x=0..9 */
#define ADC_CHXDATA_GDATA                   BITS(0,15)                                      /*!< channel x data */

/* ADC_VINTDATA */
#define ADC_VINTDATA_VINTDATA               BITS(0,15)                                      /*!< internal reference voltage channel data */

/* ADC_TEMPDATA */
#define ADC_TEMPDATA_TEMPDATA               BITS(0,15)                                      /*!< temperature sensor channel data */

/* ADC_WDCTL */
#define ADC_WDCTL_WDAEN                     BIT(0)                                          /*!< watchdog A enable */
#define ADC_WDCTL_WDAIE                     BIT(1)                                          /*!< interrupt enable for watchdog A */
#define ADC_WDCTL_WDBEN                     BIT(2)                                          /*!< watchdog B enable */
#define ADC_WDCTL_WDBIE                     BIT(3)                                          /*!< interrupt enable for watchdog B */
#define ADC_WDCTL_WDBCM                     BIT(4)                                          /*!< watchdog B compare conditions mode */
#define ADC_WDCTL_WINEN                     BIT(5)                                          /*!< window mode enable */
#define ADC_WDCTL_WDABCC                    BITS(6,7)                                       /*!< watchdog A/B complex conditions configuration */
#define ADC_WDCTL_WDBEF                     BIT(17)                                         /*!< analog watchdog B event flag */
#define ADC_WDCTL_WDAMF                     BIT(18)                                         /*!< analog watchdog A compare monitor flag */
#define ADC_WDCTL_WDBMF                     BIT(19)                                         /*!< analog watchdog B compare monitor flag */
#define ADC_WDCTL_WDABMF                    BIT(20)                                         /*!< analog watchdog A/B complex compare monitor flag */
#define ADC_WDCTL_WDBCHSEL                  BITS(28,31)                                     /*!< analog watchdog B channel select */

/* ADC_WDATHOLD*/
#define ADC_WDATHOLD_WDALT                  BITS(0,15)                                      /*!< low threshold for analog watchdog A */
#define ADC_WDATHOLD_WDAHT                  BITS(16,31)                                     /*!< high threshold for analog watchdog A */

/* ADC_WDBTHOLD*/
#define ADC_WDBTHOLD_WDBLT                  BITS(0,15)                                      /*!< low threshold for analog watchdog B */
#define ADC_WDBTHOLD_WDBHT                  BITS(16,31)                                     /*!< high threshold for analog watchdog B */

/* ADC_WDACHCFG */
#define ADC_WDACHCFG_WDACH0M                BIT(0)                                          /*!< channel ADCx_IN0 watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDACH1M                BIT(1)                                          /*!< channel ADCx_IN1 watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDACH2M                BIT(2)                                          /*!< channel ADCx_IN2 watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDACH3M                BIT(3)                                          /*!< channel ADCx_IN3 watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDACH4M                BIT(4)                                          /*!< channel ADCx_IN4 watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDACH5M                BIT(5)                                          /*!< channel ADCx_IN5 watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDACH6M                BIT(6)                                          /*!< channel ADCx_IN6 watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDACH7M                BIT(7)                                          /*!< channel ADCx_IN7 watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDACH8M                BIT(8)                                          /*!< channel ADCx_IN8 watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDACH9M                BIT(9)                                          /*!< channel ADCx_IN9 watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDATEMPM               BIT(10)                                         /*!< temperature sensor channel watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDAVINTM               BIT(11)                                         /*!< internal reference voltage channel watchdog A compare conditions mode */
#define ADC_WDACHCFG_WDACH0                 BIT(16)                                         /*!< select ADCx_IN0 for watchdog A */
#define ADC_WDACHCFG_WDACH1                 BIT(17)                                         /*!< select ADCx_IN1 for watchdog A */
#define ADC_WDACHCFG_WDACH2                 BIT(18)                                         /*!< select ADCx_IN2 for watchdog A */
#define ADC_WDACHCFG_WDACH3                 BIT(19)                                         /*!< select ADCx_IN3 for watchdog A */
#define ADC_WDACHCFG_WDACH4                 BIT(20)                                         /*!< select ADCx_IN4 for watchdog A */
#define ADC_WDACHCFG_WDACH5                 BIT(21)                                         /*!< select ADCx_IN5 for watchdog A */
#define ADC_WDACHCFG_WDACH6                 BIT(22)                                         /*!< select ADCx_IN6 for watchdog A */
#define ADC_WDACHCFG_WDACH7                 BIT(23)                                         /*!< select ADCx_IN7 for watchdog A */
#define ADC_WDACHCFG_WDACH8                 BIT(24)                                         /*!< select ADCx_IN8 for watchdog A */
#define ADC_WDACHCFG_WDACH9                 BIT(25)                                         /*!< select ADCx_IN9 for watchdog A */
#define ADC_WDACHCFG_WDATEMP                BIT(26)                                         /*!< select temperature sensor channel for watchdog A */
#define ADC_WDACHCFG_WDAVINT                BIT(27)                                         /*!< select internal reference voltage channel for watchdog A */

/* ADC_WDACHSTAT*/
#define ADC_WDACHSTAT_CH0CMPF               BIT(0)                                          /*!< channel ADCx_IN0 compare status in watchdog A */
#define ADC_WDACHSTAT_CH1CMPF               BIT(1)                                          /*!< channel ADCx_IN1 compare status in watchdog A */
#define ADC_WDACHSTAT_CH2CMPF               BIT(2)                                          /*!< channel ADCx_IN2 compare status in watchdog A */
#define ADC_WDACHSTAT_CH3CMPF               BIT(3)                                          /*!< channel ADCx_IN3 compare status in watchdog A */
#define ADC_WDACHSTAT_CH4CMPF               BIT(4)                                          /*!< channel ADCx_IN4 compare status in watchdog A */
#define ADC_WDACHSTAT_CH5CMPF               BIT(5)                                          /*!< channel ADCx_IN5 compare status in watchdog A */
#define ADC_WDACHSTAT_CH6CMPF               BIT(6)                                          /*!< channel ADCx_IN6 compare status in watchdog A */
#define ADC_WDACHSTAT_CH7CMPF               BIT(7)                                          /*!< channel ADCx_IN7 compare status in watchdog A */
#define ADC_WDACHSTAT_CH8CMPF               BIT(8)                                          /*!< channel ADCx_IN8 compare status in watchdog A */
#define ADC_WDACHSTAT_CH9CMPF               BIT(9)                                          /*!< channel ADCx_IN9 compare status in watchdog A */
#define ADC_WDACHSTAT_TEMPCMPF              BIT(10)                                         /*!< temperature sensor channel compare status in watchdog A */
#define ADC_WDACHSTAT_VINTCMPF              BIT(11)                                         /*!< internal reference voltage channel compare status in watchdog A */

/* ADC_CTL1 */
#define ADC_CTL1_ADCON                      BIT(13)                                         /*!< ADC on or off */
#define ADC_CTL1_DRES                       BITS(14,15)                                     /*!< ADC resolution */

/* ADC_SHCTL */
#define ADC_SHCTL_SHEN                      BITS(0,2)                                       /*!< channel-dedicated Sample-and-Hold circuit bypass select */
#define ADC_SHCTL_SH00EN                    BIT(0)                                          /*!< enable channel ADCx_IN0 sample-and-hold circuit */
#define ADC_SHCTL_SH01EN                    BIT(1)                                          /*!< enable channel ADCx_IN1 sample-and-hold circuit */
#define ADC_SHCTL_SH02EN                    BIT(2)                                          /*!< enable channel ADCx_IN2 sample-and-hold circuit */
#define ADC_SHCTL_SHMD                      BIT(16)                                         /*!< channel-dedicated sample-and-hold circuit operating mode */
#define ADC_SHCTL_SHEND                     BIT(17)                                         /*!< software end sample-and-hold circuit in constant sampling mode */
#define ADC_SHCTL_SHSTART                   BIT(18)                                         /*!< software start sample-and-hold circuit in constant sampling mode */
#define ADC_SHCTL_SHHTIME                   BITS(20,23)                                     /*!< the hold time of sample-and-hold circuit */
#define ADC_SHCTL_SHSTIME                   BITS(24,31)                                     /*!< the sample time of sample-and-hold circuit */

/* ADC_DMACTL */
#define ADC_DMACTL_GP1OVRIE                 BIT(3)                                          /*!< DMA overrun detect interrupt enable of Group_pri1 */
#define ADC_DMACTL_OVREN1                   BIT(4)                                          /*!< DMA overrun detect enable of Group_pri1 */
#define ADC_DMACTL_GP1OVRF                  BIT(5)                                          /*!< DMA overrun flag of Group_pri1 */
#define ADC_DMACTL_GP1DDM                   BIT(6)                                          /*!< DMA disable mode of Group_pri1 */
#define ADC_DMACTL_DMAEN1                   BIT(7)                                          /*!< DMA request enable of Group_pri1 */
#define ADC_DMACTL_GP2OVRIE                 BIT(11)                                         /*!< DMA overrun detect interrupt enable of Group_pri2 */
#define ADC_DMACTL_OVREN2                   BIT(12)                                         /*!< DMA overrun detect enable of Group_pri2 */
#define ADC_DMACTL_GP2OVRF                  BIT(13)                                         /*!< DMA overrun flag of Group_pri2 */
#define ADC_DMACTL_GP2DDM                   BIT(14)                                         /*!< DMA disable mode of Group_pri2 */
#define ADC_DMACTL_DMAEN2                   BIT(15)                                         /*!< DMA request enable of Group_pri2 */
#define ADC_DMACTL_GP3OVRIE                 BIT(19)                                         /*!< DMA overrun detect interrupt enable of Group_pri3 */
#define ADC_DMACTL_OVREN3                   BIT(20)                                         /*!< DMA overrun detect enable of Group_pri3 */
#define ADC_DMACTL_GP3OVRF                  BIT(21)                                         /*!< DMA overrun flag of Group_pri3 */
#define ADC_DMACTL_GP3DDM                   BIT(22)                                         /*!< DMA disable mode of Group_pri3 */
#define ADC_DMACTL_DMAEN3                   BIT(23)                                         /*!< DMA request enable of Group_pri3 */
#define ADC_DMACTL_GP4OVRIE                 BIT(27)                                         /*!< DMA overrun detect interrupt enable of Group_pri4 */
#define ADC_DMACTL_OVREN4                   BIT(28)                                         /*!< DMA overrun detect enable of Group_pri4 */
#define ADC_DMACTL_GP4OVRF                  BIT(29)                                         /*!< DMA overrun flag of Group_pri4 */
#define ADC_DMACTL_GP4DDM                   BIT(30)                                         /*!< DMA disable mode of Group_pri4 */
#define ADC_DMACTL_DMAEN4                   BIT(31)                                         /*!< DMA request enable of Group_pri4 */

/* ADC_BITRGCTL */
#define ADC_BITRGCTL_GP1BITGRS              BIT(1)                                          /*!< enable the next trigger restore of Group_pri1 */
#define ADC_BITRGCTL_GP1BIMEN               BIT(2)                                          /*!< enable bifurcate trigger mode of Group_pri1 */
#define ADC_BITRGCTL_GP1BICHSEL             BITS(3,7)                                       /*!< select bifurcate trigger channel of Group_pri1 */
#define ADC_BITRGCTL_GP2BITGRS              BIT(9)                                          /*!< enable the next trigger restore of Group_pri2 */
#define ADC_BITRGCTL_GP2BIMEN               BIT(10)                                         /*!< enable bifurcate trigger mode of Group_pri2 */
#define ADC_BITRGCTL_GP2BICHSEL             BITS(11,15)                                     /*!< select bifurcate trigger channel of Group_pri2 */
#define ADC_BITRGCTL_GP3BITGRS              BIT(17)                                         /*!< enable the next trigger restore of Group_pri3 */
#define ADC_BITRGCTL_GP3BIMEN               BIT(18)                                         /*!< enable bifurcate trigger mode of Group_pri3 */
#define ADC_BITRGCTL_GP3BICHSEL             BITS(19,23)                                     /*!< select bifurcate trigger channel of Group_pri3 */
#define ADC_BITRGCTL_GP4BITGRS              BIT(25)                                         /*!< enable the next trigger restore of Group_pri4 */
#define ADC_BITRGCTL_GP4BIMEN               BIT(26)                                         /*!< enable bifurcate trigger mode of Group_pri4 */
#define ADC_BITRGCTL_GP4BICHSEL             BITS(27,31)                                     /*!< select bifurcate trigger channel of Group_pri4 */

/* constants definitions */
/* ADC group select enumeration */
typedef enum {
    ADC_GROUP_PRI4 = 0,                                                                     /*!< select Group_pri4 */
    ADC_GROUP_PRI3,                                                                         /*!< select Group_pri3 */
    ADC_GROUP_PRI2,                                                                         /*!< select Group_pri2 */
    ADC_GROUP_PRI1,                                                                         /*!< select Group_pri1 */
} adc_group_select_enum;

/* ADC channel select enumeration */
typedef enum {
    ADC_CHANNEL_IN0 = 0,                                                                    /*!< select channel 0 (ADCx_IN0) */
    ADC_CHANNEL_IN1,                                                                        /*!< select channel 1 (ADCx_IN1) */
    ADC_CHANNEL_IN2,                                                                        /*!< select channel 2 (ADCx_IN2) */
    ADC_CHANNEL_IN3,                                                                        /*!< select channel 3 (ADCx_IN3) */
    ADC_CHANNEL_IN4,                                                                        /*!< select channel 4 (ADCx_IN4) */
    ADC_CHANNEL_IN5,                                                                        /*!< select channel 5 (ADCx_IN5) */
    ADC_CHANNEL_IN6,                                                                        /*!< select channel 6 (ADCx_IN6) */
    ADC_CHANNEL_IN7,                                                                        /*!< select channel 7 (ADCx_IN7), only for ADC2 */
    ADC_CHANNEL_IN8,                                                                        /*!< select channel 8 (ADCx_IN8), only for ADC2 */
    ADC_CHANNEL_IN9,                                                                        /*!< select channel 9 (ADCx_IN9), only for ADC2 */
    ADC_CHANNEL_TEMPERATURE,                                                                /*!< select temperature sensor channel, only for ADC2 */
    ADC_CHANNEL_VINT,                                                                       /*!< select internal reference voltage, only for ADC2 */
    ADC_CHANNEL_ALL,                                                                        /*!< select all channel */
} adc_channel_select_enum;

/* ADC bifurcate data select enumeration */
typedef enum {
    ADC_BIFURCATE_DATA = 0,                                                                 /*!< select Group_pri x bifurcate data register (ADC_GPxBIDATA) */
    ADC_EXTENDED_BIFURCATE_DATA_1,                                                          /*!< select Group_pri x bifurcate data register 1 (ADC_GPxBIDATA1) */
    ADC_EXTENDED_BIFURCATE_DATA_2,                                                          /*!< select Group_pri x bifurcate data register 2 (ADC_GPxBIDATA2) */
} adc_bifurcate_data_enum;

/* ADC disconnect detect mode enumeration */
typedef enum {
    ADC_DISCHARGE_MODE = 0,                                                                 /*!< select discharge mode  */
    ADC_PRECHARGE_MODE,                                                                     /*!< select precharge mode  */
    ADC_PRECHARGE_DISCHARGE_MODE_DISABLE,                                                   /*!< disable precharge and discharge mode */
} adc_disc_detect_mode_enum;

/* ADC self-diagnosis mode enumeration */
typedef enum {
    ADC_SELF_DIAGNOSIS_MODE_ROTATION = 0,                                                   /*!< select rotation mode for self-diagnosis voltage */
    ADC_SELF_DIAGNOSIS_MODE_FIXED,                                                          /*!< select fixed mode for self-diagnosis voltage */
} adc_self_diag_mode_enum;

/* ADC self-diagnosis voltage select enumeration in fixed mode */
typedef enum {
    ADC_SELF_DIAG_0_V = 1,                                                                  /*!< uses the voltage of 0 V for self-diagnosis */
    ADC_SELF_DIAG_1_2_VREF,                                                                 /*!< uses the voltage of reference power supply VREFP/2 for self-diagnosis */
    ADC_SELF_DIAG_VREF,                                                                     /*!< uses the voltage of reference power supply VREFP for self-diagnosis */
} adc_self_diag_fixed_voltage_enum;

/* ADC restart channel select enumeration for Group_pri x */
typedef enum {
    ADC_RESTART_ON_BEGINNING = 0,                                                           /*!< rescan the lower priority group scanning from initial channel */
    ADC_RESTART_ON_BREAKING,                                                                /*!< rescan the lower priority group scanning from the last aborted channel */
} adc_restart_channel_enum;

/* analog watchdog select enumeration */
typedef enum {
    ADC_WATCHDOG_A = 0,                                                                     /*!< select analog watchdog A select */
    ADC_WATCHDOG_B,                                                                         /*!< select analog watchdog B select */
    ADC_WATCHDOG_A_B                                                                        /*!< select analog watchdog A and watchdog B */
} adc_watchdog_select_enum;

/* analog watchdog compare mode enumeration */
typedef enum {
    ADC_OUT_WINDOW = 0,                                                                     /*!< When the WINEN is 0,WDLT[15:0] value > A/D-converted value,When the WINEN is 1,A/D-converted value < WDLT[15:0] value or WDHT[15:0] < A/D-converted value */
    ADC_IN_WINDOW                                                                           /*!< When the WINEN is 0,WDLT[15:0] value < A/D-converted value,When the WINEN is 1,WDLT[15:0] value < A/D-converted value < WDHT[15:0] value */
} adc_watchdog_compare_condition_enum;

/* ADC oversample mode enumeration */
typedef enum {
    ADC_ACCUMULATION_MODE = 0,                                                              /*!< accumulation data mode */
    ADC_AVERAGE_MODE,                                                                       /*!< average data mode */
} adc_oversample_mode_enum;

/* interrupt select enumeration */
typedef enum {
    ADC_INT_EOC1RF = 0,                                                                     /*!< interrupt for EOC1RF */
    ADC_INT_EOC2RF,                                                                         /*!< interrupt for EOC2RF */
    ADC_INT_EOC3RF,                                                                         /*!< interrupt for EOC3RF */
    ADC_INT_EOC4RF,                                                                         /*!< interrupt for EOC4RF */
    ADC_INT_WDA_CHSTAT,                                                                     /*!< interrupt for watchdog A */
    ADC_INT_WDBEF,                                                                          /*!< interrupt for watchdog B */
    ADC_INT_GP1OVRF,                                                                        /*!< DMA overflow detect interrupt of Group_pri1 */
    ADC_INT_GP2OVRF,                                                                        /*!< DMA overflow detect interrupt of Group_pri2 */
    ADC_INT_GP3OVRF,                                                                        /*!< DMA overflow detect interrupt of Group_pri3 */
    ADC_INT_GP4OVRF                                                                         /*!< DMA overflow detect interrupt of Group_pri4 */
} adc_interrupt_enum;

/* interrupt flag select enumeration */
typedef enum {
    ADC_INT_FLAG_EOC1RF = 0,                                                                     /*!< interrupt for EOC1RF */
    ADC_INT_FLAG_EOC2RF,                                                                         /*!< interrupt for EOC2RF */
    ADC_INT_FLAG_EOC3RF,                                                                         /*!< interrupt for EOC3RF */
    ADC_INT_FLAG_EOC4RF,                                                                         /*!< interrupt for EOC4RF */
    ADC_INT_FLAG_WDA_CHSTAT,                                                                     /*!< interrupt for watchdog A */
    ADC_INT_FLAG_WDBEF,                                                                          /*!< interrupt for watchdog B */
    ADC_INT_FLAG_GP1OVRF,                                                                        /*!< DMA overflow detect interrupt of Group_pri1 */
    ADC_INT_FLAG_GP2OVRF,                                                                        /*!< DMA overflow detect interrupt of Group_pri2 */
    ADC_INT_FLAG_GP3OVRF,                                                                        /*!< DMA overflow detect interrupt of Group_pri3 */
    ADC_INT_FLAG_GP4OVRF                                                                         /*!< DMA overflow detect interrupt of Group_pri4 */
} adc_interrupt_flag_enum;

/* evevt select enumeration */
typedef enum {
    ADC_FLAG_EOC1F = 0,                                                                     /*!< end of Group_pri1 conversion flag */
    ADC_FLAG_EOC1RF,                                                                        /*!< end of Group_pri1 conversion round flag */
    ADC_FLAG_EOC2F,                                                                         /*!< end of Group_pri2 conversion flag */
    ADC_FLAG_EOC2RF,                                                                        /*!< end of Group_pri2 conversion round flag */
    ADC_FLAG_EOC3F,                                                                         /*!< end of Group_pri3 conversion flag */
    ADC_FLAG_EOC3RF,                                                                        /*!< end of Group_pri3 conversion round flag */
    ADC_FLAG_EOC4F,                                                                         /*!< end of Group_pri4 conversion flag */
    ADC_FLAG_EOC4RF,                                                                        /*!< end of Group_pri4 conversion round flag */
    ADC_FLAG_PROC,                                                                          /*!< A/D conversion process flag */
    ADC_FLAG_WDAMF,                                                                         /*!< analog watchdog A compare monitor flag */
    ADC_FLAG_WDBMF,                                                                         /*!< analog watchdog B compare monitor flag */
    ADC_FLAG_WDABMF,                                                                        /*!< analog watchdog A/B complex compare monitor flag */
    ADC_FLAG_GP1OVRF,                                                                       /*!< DMA overflow flag of Group_pri1 */
    ADC_FLAG_GP2OVRF,                                                                       /*!< DMA overflow flag of Group_pri2 */
    ADC_FLAG_GP3OVRF,                                                                       /*!< DMA overflow flag of Group_pri3 */
    ADC_FLAG_GP4OVRF,                                                                       /*!< DMA overflow flag of Group_pri4 */
    ADC_FLAG_WDBEF,                                                                         /*!< analog watchdog B event flag */
    ADC_FLAG_WDA_CH0CMPF,                                                                   /*!< channel ADCx_IN0 compare status in watchdog A */
    ADC_FLAG_WDA_CH1CMPF,                                                                   /*!< channel ADCx_IN1 compare status in watchdog A */
    ADC_FLAG_WDA_CH2CMPF,                                                                   /*!< channel ADCx_IN2 compare status in watchdog A */
    ADC_FLAG_WDA_CH3CMPF,                                                                   /*!< channel ADCx_IN3 compare status in watchdog A */
    ADC_FLAG_WDA_CH4CMPF,                                                                   /*!< channel ADCx_IN4 compare status in watchdog A */
    ADC_FLAG_WDA_CH5CMPF,                                                                   /*!< channel ADCx_IN5 compare status in watchdog A */
    ADC_FLAG_WDA_CH6CMPF,                                                                   /*!< channel ADCx_IN6 compare status in watchdog A */
    ADC_FLAG_WDA_CH7CMPF,                                                                   /*!< channel ADCx_IN7 compare status in watchdog A */
    ADC_FLAG_WDA_CH8CMPF,                                                                   /*!< channel ADCx_IN8 compare status in watchdog A */
    ADC_FLAG_WDA_CH9CMPF,                                                                   /*!< channel ADCx_IN9 compare status in watchdog A */
    ADC_FLAG_WDA_TEMPCMPF,                                                                  /*!< temperature sensor channel compare status in watchdog A */
    ADC_FLAG_WDA_VINTCMPF,                                                                  /*!< internal reference voltage channel compare status in watchdog A */
    ADC_FLAG_WDA_ALL_CHCMPF,                                                                /*!< all channel compare status in watchdog A */
} adc_event_flag_enum;

/* ADC oversample mode enumeration */
typedef enum {
    ADC_EVIC_LINK_SOURCE_EOCRF_FLAG = 0,                                                    /*!< EVIC trigger signal selects EOCxRF */
    ADC_EVIC_LINK_SOURCE_EOCF_FLAG,                                                         /*!< EVIC trigger signal selects EOCxF */
} adc_evic_link_source_enum;

/* ADC data alignment */
#define ADC_DATAALIGN_RIGHT                     ((uint32_t)0x00000000U)                         /*!< LSB alignment */
#define ADC_DATAALIGN_LEFT                      ADC_CTL0_DAL                                    /*!< MSB alignment */

/* ADC resolution */
#define CTL1_DRES(regval)                       (BITS(14, 15) & ((uint32_t)(regval) << 14))     /*!< write value to ADC_CTL1_DRES bit field */
#define ADC_RESOLUTION_12B                      CTL1_DRES(0)                                    /*!< 12-bit ADC resolution */
#define ADC_RESOLUTION_10B                      CTL1_DRES(1)                                    /*!< 10-bit ADC resolution */
#define ADC_RESOLUTION_8B                       CTL1_DRES(2)                                    /*!< 8-bit ADC resolution */
#define ADC_RESOLUTION_6B                       CTL1_DRES(3)                                    /*!< 6-bit ADC resolution */

/* total addition conversion times */
#define ADC_OVERSAMPLING_RATIO_MUL_1            ((uint32_t)0x00000000U)                         /*!< 1-time conversion */
#define ADC_OVERSAMPLING_RATIO_MUL_2            ((uint32_t)0x00000001U)                         /*!< 2-time conversion */
#define ADC_OVERSAMPLING_RATIO_MUL_3            ((uint32_t)0x00000002U)                         /*!< 3-time conversion */
#define ADC_OVERSAMPLING_RATIO_MUL_4            ((uint32_t)0x00000003U)                         /*!< 4-time conversion */
#define ADC_OVERSAMPLING_RATIO_MUL_8            ((uint32_t)0x00000004U)                         /*!< 8-time conversion */
#define ADC_OVERSAMPLING_RATIO_MUL_16           ((uint32_t)0x00000005U)                         /*!< 16-time conversion */
#define ADC_OVERSAMPLING_RATIO_MUL_32           ((uint32_t)0x00000006U)                         /*!< 32-time conversion */
#define ADC_OVERSAMPLING_RATIO_MUL_64           ((uint32_t)0x00000007U)                         /*!< 64-time conversion */

/* Scan Mode Select */
#define CTL0_GSCAN(regval)                      (BITS(20, 21) & ((uint32_t)(regval) << 20))     /*!< write value to ADC_CTL0_GSCAN bit field */
#define ADC_GROUP_PRI1_SCAN_ONCE                CTL0_GSCAN(0)                                   /*!< select Group_pri1 scan once mode */
#define ADC_GROUPS_SCAN                         CTL0_GSCAN(1)                                   /*!< select groups scan mode */
#define ADC_GROUP_PRI1_SCAN_CONTINUE            CTL0_GSCAN(2)                                   /*!< select Group_pri1 scan continuous mode */

/* ADC to EVIC link signal select */
#define CTL0_EVICCTL(regval)                    (BITS(28, 30) & ((uint32_t)(regval) << 28))     /*!< EVIC link signal select */
#define ADC_EVIC_LINK_GROUP_PRI1                CTL0_EVICCTL(0)                                 /*!< an event signal is generated when scanning for Group_pri1 is completed */
#define ADC_EVIC_LINK_GROUP_PRI2                CTL0_EVICCTL(1)                                 /*!< an event signal is generated when scanning for Group_pri2 is completed */
#define ADC_EVIC_LINK_GROUP_PRI3                CTL0_EVICCTL(2)                                 /*!< an event signal is generated when scanning for Group_pri3 is completed */
#define ADC_EVIC_LINK_GROUP_PRI4                CTL0_EVICCTL(3)                                 /*!< an event signal is generated when scanning for Group_pri4 is completed */
#define ADC_EVIC_LINK_GROUP_ALL                 CTL0_EVICCTL(4)                                 /*!< an event signal is generated when scanning for all Group_pri is completed */

/* select the A/D conversion start synchronous trigger source for Group_prix (x=1,2,3,4) */
#define TRIGR_GP3TRGSRC(regval)                 (BITS(0, 5) & ((uint32_t)(regval) << 0))        /*!< write value to ADC_GPCFG_GPxTRGSRC bit field */
#define ADC_SYNCTRIG_SOURCE_TIMER0_TRGOF        TRIGR_GP3TRGSRC(1)                              /*!< select TIMER0_TRGOF for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER0_TRGUF        TRIGR_GP3TRGSRC(2)                              /*!< select TIMER0_TRGUF for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER0_TRGA         TRIGR_GP3TRGSRC(3)                              /*!< select TIMER0_TRGA for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER0_TRGB         TRIGR_GP3TRGSRC(4)                              /*!< select TIMER0_TRGB for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER0_TRGAB        TRIGR_GP3TRGSRC(5)                              /*!< select TIMER0_TRGAB for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER0_TRGAORB      TRIGR_GP3TRGSRC(6)                              /*!< select TIMER0_TRGA_OR_B for ADC extend bifurcate trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER0_TRGO         TRIGR_GP3TRGSRC(7)                              /*!< select TIMER0_TRGO for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER7_TRGOF        TRIGR_GP3TRGSRC(9)                              /*!< select TIMER7_TRGOF for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER7_TRGUF        TRIGR_GP3TRGSRC(10)                             /*!< select TIMER7_TRGUF for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER7_TRGA         TRIGR_GP3TRGSRC(11)                             /*!< select TIMER7_TRGA for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER7_TRGB         TRIGR_GP3TRGSRC(12)                             /*!< select TIMER7_TRGB for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER7_TRGAB        TRIGR_GP3TRGSRC(13)                             /*!< select TIMER7_TRGAB for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER7_TRGAORB      TRIGR_GP3TRGSRC(14)                             /*!< select TIMER7_TRGA_OR_B for ADC extend bifurcate trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER7_TRGO         TRIGR_GP3TRGSRC(15)                             /*!< select TIMER7_TRGO for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER1_TRGO         TRIGR_GP3TRGSRC(23)                             /*!< select TIMER1_TRGO for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_TIMER2_TRGO         TRIGR_GP3TRGSRC(31)                             /*!< select TIMER2_TRGO for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_GPTIMER0_TRGA       TRIGR_GP3TRGSRC(35)                             /*!< select GPTIMER0_TRGA for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_GPTIMER0_TRGB       TRIGR_GP3TRGSRC(36)                             /*!< select GPTIMER0_TRGB for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_GPTIMER0_TRGAB      TRIGR_GP3TRGSRC(37)                             /*!< select GPTIMER0_TRGAB for ADC extend bifurcate trigger source */
#define ADC_SYNCTRIG_SOURCE_GPTIMER1_TRGA       TRIGR_GP3TRGSRC(43)                             /*!< select GPTIMER1_TRGA for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_GPTIMER1_TRGB       TRIGR_GP3TRGSRC(44)                             /*!< select GPTIMER1_TRGB for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_GPTIMER1_TRGAB      TRIGR_GP3TRGSRC(45)                             /*!< select GPTIMER1_TRGAB for ADC extend bifurcate trigger source */
#define ADC_SYNCTRIG_SOURCE_EVIC_EVSEL0         TRIGR_GP3TRGSRC(49)                             /*!< select EVIC_EVSEL0 for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_EVIC_EVSEL1         TRIGR_GP3TRGSRC(50)                             /*!< select EVIC_EVSEL1 for ADC trigger source */
#define ADC_SYNCTRIG_SOURCE_EVIC_EVSEL0_OR_1    TRIGR_GP3TRGSRC(51)                             /*!< select EVIC_EVSEL0 or EVIC_EVSEL1 for ADC trigger source */

/* trigger edge select of Group_pri x */
#define TRIGR_EXTEN_HIGH(regval)                (BITS(8, 9) & ((uint32_t)(regval) << 8))        /*!< write value to ADC_GPCFG_GP2TRGED bit field */
#define ADC_EXTERNAL_TRIG_RISING_EDGE           TRIGR_EXTEN_HIGH(1)                             /*!< Rising edge of external trigger enable */
#define ADC_EXTERNAL_TRIG_FAILING_EDGE          TRIGR_EXTEN_HIGH(2)                             /*!< Falling edge of external trigger enable */
#define ADC_EXTERNAL_TRIG_BOTH_EDGE             TRIGR_EXTEN_HIGH(3)                             /*!< Rising and falling edge of external trigger enable */

/* watchdog A/B complex conditions configuration */
#define CTRLR_CMPAB(regval)                     (BITS(6, 7) & ((uint32_t)(regval) << 6))        /*!< write value to ADC_WDCTL_WDABCC bit field */
#define ADC_WATCHDOG_MATCH_A_OR_B               CTRLR_CMPAB(0)                                  /*!< (watchdog A condition matched) OR (watchdog B condition matched) */
#define ADC_WATCHDOG_MATCH_A_XOR_B              CTRLR_CMPAB(1)                                  /*!< (watchdog A condition matched) XOR (watchdog B condition matched) */
#define ADC_WATCHDOG_MATCH_A_AND_B              CTRLR_CMPAB(2)                                  /*!< (watchdog A condition matched) AND (watchdog B condition matched) */

/* ADC SH channel select */
#define ADC_SH_CHANNEL_IN0                     ADC_SHCTL_SH00EN                                /*!< enable channel ADC0_IN0 sample-and-hold circuit */
#define ADC_SH_CHANNEL_IN1                     ADC_SHCTL_SH01EN                                /*!< enable channel ADC0_IN1 sample-and-hold circuit */
#define ADC_SH_CHANNEL_IN2                     ADC_SHCTL_SH02EN                                /*!< enable channel ADC0_IN2 sample-and-hold circuit */

/* function declarations */
/* A/D converter configuration functions */
/* reset ADC */
void adc_deinit(uint32_t adc_periph);
/* enable ADC interface */
void adc_enable(uint32_t adc_periph);
/* disable ADC interface */
void adc_disable(uint32_t adc_periph);
/* configure ADC data alignment */
void adc_data_alignment_config(uint32_t adc_periph, uint32_t data_alignment);
/* configure ADC resolution */
void adc_resolution_config(uint32_t adc_periph, uint32_t resolution);

/* ADC self-diagnosis functions */
/* enable self-diagnosis */
void adc_self_diagnosis_enable(uint32_t adc_periph);
/* disable self-diagnosis */
void adc_self_diagnosis_disable(uint32_t adc_periph);
/* config self-diagnosis */
void adc_self_diagnosis_mode_config(uint32_t adc_periph, adc_self_diag_mode_enum mode, adc_self_diag_fixed_voltage_enum voltage_select);

/* ADC disconnection detection functions */
/* configure disconnection detection assist mode */
void adc_disconnect_detect_mode_config(uint32_t adc_periph, adc_disc_detect_mode_enum mode);
/* configure disconnect detect period */
void adc_disconnect_detect_period_config(uint32_t adc_periph, uint32_t period);

/* ADC data registers automatic clear or set functions */
/* enable automatic clearing data registers */
void adc_data_auto_clear_enable(uint32_t adc_periph);
/* disable automatic clearing data registers */
void adc_data_auto_clear_disable(uint32_t adc_periph);
/* enable automatic setting data registers */
void adc_data_auto_set_enable(uint32_t adc_periph);
/* disable automatic setting data registers */
void adc_data_auto_set_disable(uint32_t adc_periph);

/* ADC sample and hold functions */
/* configure ADC sample-and-hold channel */
void adc_sample_hold_channel_config(uint32_t channel, ControlStatus ctl);
/* configure ADC sample time for sample-and-hold circuits */
void adc_sh_sample_time_config(uint8_t sample_time);
/* configure ADC hold time for sample-and-hold circuits */
void adc_sh_hold_time_config(uint8_t hold_time);
/* enable ADC constant sampling mode for sample-and-hold circuits */
void adc_sh_constant_sampling_mode_enable(void);
/* disable ADC constant sampling mode for sample-and-hold circuits */
void adc_sh_constant_sampling_mode_disable(void);
/* software start sample-and-hold circuit in constant sampling mode */
void adc_sh_constant_sampling_start(void);
/* software end sample-and-hold circuit in constant sampling mode */
void adc_sh_constant_sampling_stop(void);

/* ADC analog watchdog functions */
/* enable ADC analog watchdog */
void adc_watchdog_enable(uint32_t adc_periph, adc_watchdog_select_enum window);
/* disable ADC analog watchdog */
void adc_watchdog_disable(uint32_t adc_periph, adc_watchdog_select_enum window);
/* configure ADC analog watchdog A channel */
void adc_watchdog_a_channel_config(uint32_t adc_periph, adc_channel_select_enum channel, adc_watchdog_compare_condition_enum compare_mode);
/* deselect ADC analog watchdog A channel */
void adc_watchdog_a_channel_deselect(uint32_t adc_periph, adc_channel_select_enum channel);
/* configure ADC analog watchdog B channel */
void adc_watchdog_b_channel_config(uint32_t adc_periph, adc_channel_select_enum channel, adc_watchdog_compare_condition_enum compare_mode);
/* configure ADC analog watchdog A threshold */
void adc_watchdog_a_threshold_config(uint32_t adc_periph, uint16_t low_threshold, uint16_t high_threshold);
/* configure ADC analog watchdog B threshold */
void adc_watchdog_b_threshold_config(uint32_t adc_periph, uint16_t low_threshold, uint16_t high_threshold);
/* enable ADC analog watchdog window function */
void adc_watchdog_window_mode_enable(uint32_t adc_periph);
/* disable ADC analog watchdog window function */
void adc_watchdog_window_mode_disable(uint32_t adc_periph);
/* configure ADC analog watchdog complex conditions */
void adc_watchdog_complex_condition_config(uint32_t adc_periph, uint32_t mode);

/* ADC oversample functions */
/* configure ADC oversample channel */
void adc_oversample_channel_config(uint32_t adc_periph, adc_channel_select_enum channel, uint32_t ratio);
/* configure ADC oversample mode */
void adc_oversample_mode_config(uint32_t adc_periph, adc_oversample_mode_enum mode);
/* enable ADC oversample mode */
void adc_oversample_mode_enable(uint32_t adc_periph);
/* disable ADC oversample mode */
void adc_oversample_mode_disable(uint32_t adc_periph);

/* ADC group scan configure functions */
/* configure the ADC scan mode */
void adc_group_scan_mode_config(uint32_t adc_periph, uint32_t scan_mode);
/* enable group priority control */
void adc_group_priority_control_enable(uint32_t adc_periph);
/* disable group priority control */
void adc_group_priority_control_disable(uint32_t adc_periph);
/* enable A/D conversion operation for Group_pri3 */
void adc_group_pri3_enable(uint32_t adc_periph);
/* disable A/D conversion operation for Group_pri3 */
void adc_group_pri3_disable(uint32_t adc_periph);
/* enable A/D conversion operation for Group_pri4 */
void adc_group_pri4_enable(uint32_t adc_periph);
/* disable A/D conversion operation for Group_pri4 */
void adc_group_pri4_disable(uint32_t adc_periph);
/* enable lowest-priority group scan continuous */
void adc_group_lowest_priority_continuous_enable(uint32_t adc_periph);
/* disable lowest-priority group scan continuous */
void adc_group_lowest_priority_continuous_disable(uint32_t adc_periph);
/* enable low-priority group restart */
void adc_group_restart_enable(uint32_t adc_periph, adc_group_select_enum group, adc_restart_channel_enum restart_ch);
/* disable low-priority group restart */
void adc_group_restart_disable(uint32_t adc_periph, adc_group_select_enum group);
/* select ADC channel for Group_pri x */
void adc_group_channel_config(uint32_t adc_periph, adc_group_select_enum group, adc_channel_select_enum channel, uint32_t sample_time);
/* deselecte ADC group channel */
void adc_group_channel_deselect(uint32_t adc_periph, adc_group_select_enum group, adc_channel_select_enum channel);
/* config end of Group_prix conversion round counts flag */
void adc_group_end_flag_round_config(uint32_t adc_periph, adc_group_select_enum group, uint8_t num);
/* enable ADC external trigger */
void adc_group_external_trigger_enable(uint32_t adc_periph, adc_group_select_enum group);
/* config ADC external trigger edge */
void adc_group_extern_trigger_edge_config(uint32_t adc_periph, adc_group_select_enum group, uint32_t edge_sel);
/* disable ADC external trigger */
void adc_group_external_trigger_disable(uint32_t adc_periph, adc_group_select_enum group);
/* enable ADC synchronous trigger */
void adc_group_synchronous_trigger_enable(uint32_t adc_periph, adc_group_select_enum group);
/* configure ADC external trigger source */
void adc_group_synchronous_trigger_source_config(uint32_t adc_periph, adc_group_select_enum group, uint32_t external_trigger_source);
/* enable ADC asynchronous trigger */
void adc_group_asynchronous_trigger_enable(uint32_t adc_periph, adc_group_select_enum group);
/* enable ADC software trigger */
void adc_group_software_trigger_enable(uint32_t adc_periph, adc_group_select_enum group);
/* software end conversion of all groups */
void adc_group_software_end_conversion(uint32_t adc_periph);

/* ADC group bifurcate configure functions */
/* enable ADC bifurcate trigger mode for Group_pri x */
void adc_group_bifurcate_mode_enable(uint32_t adc_periph, adc_group_select_enum group);
/* disable ADC bifurcate trigger mode for Group_pri x */
void adc_group_bifurcate_mode_disable(uint32_t adc_periph, adc_group_select_enum group);
/* ADC bifurcate trigger channel select */
void adc_group_bifurcate_channel_select(uint32_t adc_periph, adc_group_select_enum group, adc_channel_select_enum channel);
/* extend bifurcate trigger source select */
void adc_group_bifurcate_extend_trigger_select(uint32_t adc_periph, adc_group_select_enum group, uint32_t trigger_source);
/* enable restore of the next trigger during the current A/D conversion round */
void adc_group_bifurcate_trigger_restart_enable(uint32_t adc_periph, adc_group_select_enum group);
/* disable restore of the next trigger during the current A/D conversion round */
void adc_group_bifurcate_trigger_restart_disable(uint32_t adc_periph, adc_group_select_enum group);

/* ADC group DMA configure functions */
/* enable DMA request */
void adc_group_dma_mode_enable(uint32_t adc_periph, adc_group_select_enum group);
/* disable DMA request */
void adc_group_dma_mode_disable(uint32_t adc_periph, adc_group_select_enum group);
/* when DMA=1, the DMA engine issues a request at end of each scan conversion */
void adc_group_dma_request_after_last_enable(uint32_t adc_periph, adc_group_select_enum group);
/* the DMA engine is disabled after the end of transfer signal from DMA controller is detected */
void adc_group_dma_request_after_last_disable(uint32_t adc_periph, adc_group_select_enum group);
/* enable dma overrun detect */
void adc_group_dma_overrun_detect_enable(uint32_t adc_periph, adc_group_select_enum group);
/* disable dma overrun detect */
void adc_group_dma_overrun_detect_disable(uint32_t adc_periph, adc_group_select_enum group);

/* ADC channel configure functions */
/* channel priority config */
void adc_channel_priority_config(uint32_t adc_periph, uint8_t rank, adc_channel_select_enum adc_channel);
/* configure ADC sample time */
void adc_channel_sample_time_config(uint32_t adc_periph, adc_channel_select_enum channel, uint32_t sample_time);

/* ADC to EVIC trigger functions */
/* select which event as the EVIC link signal */
void adc_evic_link_signal_event_config(uint32_t adc_periph, uint32_t linksignal);
/* select EVIC link signal source for Gruop_pri x */
void adc_group_evic_link_signal_source(uint32_t adc_periph, adc_group_select_enum group, adc_evic_link_source_enum signal_src);

/* ADC data read functions */
/* read ADC channel data register */
uint16_t adc_channel_data_read(uint32_t adc_periph, adc_channel_select_enum channel);
/* read ADC self-diagnosis data */
uint16_t adc_self_diagnosis_data_read(uint32_t adc_periph);
/* read ADC self-diagnosis status */
uint16_t adc_self_diagnosis_status_read(uint32_t adc_periph);
/* read ADC bifurcate data register */
uint16_t adc_bifurcate_data_read(uint32_t adc_periph, adc_group_select_enum group, adc_bifurcate_data_enum channel);

/* flag and interrupt functions */
/* get the ADC flag */
FlagStatus adc_flag_get(uint32_t adc_periph, adc_event_flag_enum flag);
/* clear the ADC flag */
void adc_flag_clear(uint32_t adc_periph, adc_event_flag_enum flag);
/* enable ADC interrupt */
void adc_interrupt_enable(uint32_t adc_periph, adc_interrupt_enum interrupt);
/* disable ADC interrupt */
void adc_interrupt_disable(uint32_t adc_periph, adc_interrupt_enum interrupt);
/* get the ADC interrupt */
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph, adc_interrupt_flag_enum int_flag);
/* clear the ADC flag */
void adc_interrupt_flag_clear(uint32_t adc_periph, adc_interrupt_flag_enum int_flag);

#endif /* GD32M53X_ADC_H */
