/*!
    \file    gd32w51x_f5hc_adc.h
    \brief   definitions for the ADC
    
    \version 2026-04-15, V2.0.0, firmware for gd32w51x_f5hc
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


#ifndef gd32w51x_f5hc_ADC_H
#define gd32w51x_f5hc_ADC_H

#include "gd32w51x_f5hc.h"

/* ADC definitions */
#define ADC                             ADC_BASE

/* registers definitions */
#define ADC_STAT                        REG32(ADC + 0x00000000U)             /*!< ADC status register */
#define ADC_CTL0                        REG32(ADC + 0x00000004U)             /*!< ADC control register 0 */
#define ADC_CTL1                        REG32(ADC + 0x00000008U)             /*!< ADC control register 1 */
#define ADC_SAMPT0                      REG32(ADC + 0x0000000CU)             /*!< ADC sampling time register 0 */
#define ADC_SAMPT1                      REG32(ADC + 0x00000010U)             /*!< ADC sampling time register 1 */
#define ADC_IOFF0                       REG32(ADC + 0x00000014U)             /*!< ADC inserted channel data offset register 0 */
#define ADC_IOFF1                       REG32(ADC + 0x00000018U)             /*!< ADC inserted channel data offset register 1 */
#define ADC_IOFF2                       REG32(ADC + 0x0000001CU)             /*!< ADC inserted channel data offset register 2 */
#define ADC_IOFF3                       REG32(ADC + 0x00000020U)             /*!< ADC inserted channel data offset register 3 */
#define ADC_WD0HT                       REG32(ADC + 0x00000024U)             /*!< ADC watchdog 0 high threshold register */
#define ADC_WD0LT                       REG32(ADC + 0x00000028U)             /*!< ADC watchdog 0 low threshold register */
#define ADC_RSQ0                        REG32(ADC + 0x0000002CU)             /*!< ADC routine sequence register 0 */
#define ADC_RSQ1                        REG32(ADC + 0x00000030U)             /*!< ADC routine sequence register 1 */
#define ADC_RSQ2                        REG32(ADC + 0x00000034U)             /*!< ADC routine sequence register 2 */
#define ADC_ISQ                         REG32(ADC + 0x00000038U)             /*!< ADC inserted sequence register */
#if defined(GD32F5HC)
#define ADC_LDATA0                      REG32(ADC + 0x0000003CU)             /*!< ADC latch data register 0 */
#define ADC_LDATA1                      REG32(ADC + 0x00000040U)             /*!< ADC latch data register 1 */
#define ADC_LDATA2                      REG32(ADC + 0x00000044U)             /*!< ADC latch data register 2 */
#define ADC_LDATA3                      REG32(ADC + 0x00000048U)             /*!< ADC latch data register 3 */
#endif /* defined(GD32F5HC) */
#define ADC_RDATA                       REG32(ADC + 0x0000004CU)             /*!< ADC routine data register */
#if defined(GD32F5HC)
#define ADC_IDATA                       REG32(ADC + 0x00000050U)             /*!< ADC inserted data register */
#else
#define ADC_IDATA0                      REG32(ADC + 0x0000003CU)             /*!< ADC inserted data register 0 */
#define ADC_IDATA1                      REG32(ADC + 0x00000040U)             /*!< ADC inserted data register 1 */
#define ADC_IDATA2                      REG32(ADC + 0x00000044U)             /*!< ADC inserted data register 2 */
#define ADC_IDATA3                      REG32(ADC + 0x00000048U)             /*!< ADC inserted data register 3 */
#endif /* defined(GD32F5HC) */
#if defined(GD32F5HC)
#define ADC_LDCTL                       REG32(ADC + 0x00000054U)             /*!< ADC latch data control register */
#endif /* defined(GD32F5HC) */
#define ADC_OVSAMPCTL                   REG32(ADC + 0x00000080U)             /*!< ADC oversampling control register */
#define ADC_CCTL                        REG32(ADC + 0x00000304U)             /*!< ADC commom control register */

/* bits definitions */
/* ADC_STAT */
#define ADC_STAT_WD0E                   BIT(0)                              /*!< analog watchdog 0 event flag */
#if defined(GD32F5HC)
#define ADC_STAT_EORC                   BIT(1)                              /*!< routine channel end of conversion */
#else
#define ADC_STAT_EOC                    BIT(1)                              /*!< end of sequence conversion */
#endif /* defined(GD32F5HC) */
#define ADC_STAT_EOIC                   BIT(2)                              /*!< inserted channel end of sequence conversion */
#define ADC_STAT_STIC                   BIT(3)                              /*!< inserted channel start flag */
#define ADC_STAT_STRC                   BIT(4)                              /*!< routine channel start flag */
#define ADC_STAT_ROVF                   BIT(5)                              /*!< routine data register overflow */
#if defined(GD32F5HC)
#define ADC_STAT_IOVF                   BIT(6)                              /*!< inserted data register overflow flag */
#endif

/* ADC_CTL0 */
#define ADC_CTL0_WD0CHSEL               BITS(0, 4)                          /*!< analog watchdog 0 channel select bits */
#if defined(GD32F5HC)
#define ADC_CTL0_EORCIE                 BIT(5)                              /*!< interrupt enable for EORC */
#else
#define ADC_CTL0_EOCIE                  BIT(5)                              /*!< interrupt enable for EOC */
#endif /* defined(GD32F5HC) */
#define ADC_CTL0_WD0EIE                 BIT(6)                              /*!< analog watchdog 0 interrupt enable */
#define ADC_CTL0_EOICIE                 BIT(7)                              /*!< interrupt enable for inserted channels */
#define ADC_CTL0_SM                     BIT(8)                              /*!< scan mode */
#define ADC_CTL0_WD0SC                  BIT(9)                              /*!< when in scan mode, analog watchdog 0 is effective on a single channel */
#define ADC_CTL0_ICA                    BIT(10)                             /*!< automatic inserted sequence conversion */
#define ADC_CTL0_DISRC                  BIT(11)                             /*!< discontinuous mode on routine channels */
#define ADC_CTL0_DISIC                  BIT(12)                             /*!< discontinuous mode on inserted channels */
#define ADC_CTL0_DISNUM                 BITS(13, 15)                        /*!< discontinuous mode channel count */
#define ADC_CTL0_IWD0EN                 BIT(22)                             /*!< analog watchdog 0 enable on inserted channels */
#define ADC_CTL0_RWD0EN                 BIT(23)                             /*!< analog watchdog 0 enable on routine channels */
#define ADC_CTL0_ROVFIE                 BIT(26)                             /*!< interrupt enable for routine data register overflow */
#if defined(GD32F5HC)
#define ADC_CTL0_IOVFIE                 BIT(27)                             /*!< interrupt enable for inserted data register overflow */
#endif /* defined(GD32F5HC) */

/* ADC_CTL1 */
#define ADC_CTL1_ADCON                  BIT(0)                              /*!< ADC converter on */
#define ADC_CTL1_CTN                    BIT(1)                              /*!< continuous conversion */
#if defined(GD32F5HC)
#define ADC_CTL1_IDMA                   BIT(7)                              /*!< DMA request enable for inserted channel */
#endif /* defined(GD32F5HC) */
#define ADC_CTL1_RDMA                   BIT(8)                              /*!< DMA request enable for routine channel */
#define ADC_CTL1_RDDM                   BIT(9)                              /*!< DMA disable mode for routine channel*/
#define ADC_CTL1_EORCM                  BIT(10)                             /*!< end of conversion mode for routine channel */
#define ADC_CTL1_DAL                    BIT(11)                             /*!< data alignment */
#if defined(GD32F5HC)
#define ADC_CTL1_IDDM                   BIT(13)                             /*!< DMA disable mode for routine channel */
#endif /* defined(GD32F5HC) */
#define ADC_CTL1_ETSIC                  BITS(16, 19)                        /*!< external trigger select for inserted channel */
#define ADC_CTL1_ETMIC                  BITS(20, 21)                        /*!< external trigger enable for inserted channel */
#define ADC_CTL1_SWICST                 BIT(22)                             /*!< start on inserted channel */
#define ADC_CTL1_ETSRC                  BITS(24, 27)                        /*!< external trigger select for routine channel */
#define ADC_CTL1_ETMRC                  BITS(28, 29)                        /*!< external trigger enable for routine channel */
#define ADC_CTL1_SWRCST                 BIT(30)                             /*!< start on routine channel */

/* ADC_SAMPTx x=0..1 */
#define ADC_SAMPTX_SPTN                 BITS(0, 2)                          /*!< channel x sample time selection */

/* ADC_IOFFx x=0..3 */
#define ADC_IOFFX_IOFF                  BITS(0, 11)                         /*!< data offset for inserted channel x */

#if defined(GD32F5HC)
/* ADC_WDHT */
#define ADC_WD0HT_WD0HT                 BITS(0, 19)                         /*!< analog watchdog 0 high threshold */
#else
/* ADC_WDHT */
#define ADC_WD0HT_WD0HT                 BITS(0, 11)                         /*!< analog watchdog 0 high threshold */
#endif /* defined(GD32F5HC) */

#if defined(GD32F5HC)
/* ADC_WD0LT */
#define ADC_WD0LT_WD0LT                 BITS(0, 19)                         /*!< analog watchdog 0 low threshold */
#else
/* ADC_WD0LT */
#define ADC_WD0LT_WD0LT                 BITS(0, 11)                         /*!< analog watchdog 0 low threshold */
#endif /* defined(GD32F5HC) */

/* ADC_RSQx */
#define ADC_RSQX_RSQN                   BITS(0, 4)                          /*!< x(x = 0..11) conversion in routine sequence */
#define ADC_RSQ0_RL                     BITS(20, 23)                        /*!< routine channel sequence length */

/* ADC_ISQ */
#define ADC_ISQ_ISQN                    BITS(0, 4)                          /*!< x conversion in inserted sequence */
#define ADC_ISQ_IL                      BITS(20, 21)                        /*!< inserted sequence length */

#if defined(GD32F5HC)
/* ADC_LDATAx x=0..3*/
#define ADC_LDATAX_LDATAN               BITS(0, 15)                         /*!< latch data channel x conversion data */
#endif /* defined(GD32F5HC) */

/* ADC_RDATA */
#define ADC_RDATA_RDATA                 BITS(0, 15)                         /*!< routine data */

#if defined(GD32F5HC)
/* ADC_IDATA*/
#define ADC_IDATA_IDATAN                BITS(0, 15)                         /*!< inserted conversion data */
#else
/* ADC_IDATAx x=0..3*/
#define ADC_IDATAX_IDATAN               BITS(0, 15)                         /*!< inserted channel x conversion data */
#endif /* defined(GD32F5HC) */

#if defined(GD32F5HC)
/* ADC_LDCTL */                                           
#define ADC_LDCTL_COVSELx               BITS(0,3)                            /*!< ADC_LDATAx register conversion source selection */
#define ADC_LDCTL_SEQSELx               BIT(7)                               /*!< ADC_LDATAx register sequence source selection */
#endif /* defined(GD32F5HC) */

/* ADC_OVSAMPCTL */
#define ADC_OVSAMPCTL_OVSEN             BIT(0)                              /*!< oversampling enable */
#define ADC_OVSAMPCTL_OVSR              BITS(2, 4)                          /*!< oversampling ratio */
#define ADC_OVSAMPCTL_OVSS              BITS(5, 8)                          /*!< oversampling shift */
#define ADC_OVSAMPCTL_TOVS              BIT(9)                              /*!< triggered oversampling */

/* ADC_CCTL */
#define ADC_CCTL_ADCCK                  BITS(16, 18)                        /*!< ADC clock */
#define ADC_CCTL_VBATEN                 BIT(22)                             /*!< channel 11 (1/4 voltate of external battery) enable of ADC */
#if defined(GD32F5HC)
#define ADC_CCTL_INREFEN                BIT(23)                             /*!< channel 10 (internal reference voltage) enable of ADC */
#define ADC_CCTL_TSVEN                  BIT(24)                             /*!< channel 9 (temperature sensor) enable of ADC */
#else
#define ADC_CCTL_TSVREN                 BIT(23)                             /*!< channel 9 (temperature sensor) and 10 (internal reference voltage) enable of ADC */
#endif /* defined(GD32F5HC) */


/* constants definitions */
/* ADC_CTL0 register value */
#define CTL0_DISNUM(regval)             (BITS(13, 15) & ((uint32_t)(regval) << 13)) /*!< number of conversions in discontinuous mode */

/* ADC special function definitions */
#define ADC_SCAN_MODE                   ADC_CTL0_SM                                 /*!< scan mode */
#define ADC_INSERTED_CHANNEL_AUTO       ADC_CTL0_ICA                                /*!< inserted sequence convert automatically */
#define ADC_CONTINUOUS_MODE             ADC_CTL1_CTN                                /*!< continuous mode */

/* temperature sensor channel, internal reference voltage channel, VBAT channel */
#define ADC_CHANNEL_INTERNAL_VBAT       ADC_CCTL_VBATEN                             /*!< VBAT channel */
#if defined(GD32F5HC)
#define ADC_CHANNEL_INTERNAL_VREFINT    ADC_CCTL_INREFEN                            /*!< vrefint channel */
#define ADC_CHANNEL_INTERNAL_TEMPSENSOR ADC_CCTL_TSVEN                              /*!< temperature sensor channel */
#else
#define ADC_CHANNEL_INTERNAL_TEMP_VREF  ADC_CCTL_TSVREN                             /*!< vrefint and temperature sensor channel */
#endif /* defined(GD32F5HC) */

/* ADC data alignment */
#define ADC_DATAALIGN_RIGHT             ((uint32_t)0x00000000U)                     /*!< LSB alignment */
#define ADC_DATAALIGN_LEFT              ADC_CTL1_DAL                                /*!< MSB alignment */

/* external trigger mode for routine and inserted  sequence */
#define EXTERNAL_TRIGGER_DISABLE        ((uint32_t)0x00000000U)                     /*!< external trigger disable */
#define EXTERNAL_TRIGGER_RISING         ((uint32_t)0x00000001U)                     /*!< rising edge of external trigger */
#define EXTERNAL_TRIGGER_FALLING        ((uint32_t)0x00000002U)                     /*!< falling edge of external trigger */
#define EXTERNAL_TRIGGER_RISING_FALLING ((uint32_t)0x00000003U)                     /*!< rising and falling edge of external trigger */

/* ADC external trigger select for routine sequence */
#define CTL1_ETSRC(regval)              (BITS(24, 27) & ((uint32_t)(regval) << 24))
#define ADC_EXTTRIG_ROUTINE_T0_CH0      CTL1_ETSRC(0)                               /*!< TIMER0 CH0 event select */
#define ADC_EXTTRIG_ROUTINE_T0_CH1      CTL1_ETSRC(1)                               /*!< TIMER0 CH1 event select */
#define ADC_EXTTRIG_ROUTINE_T0_CH2      CTL1_ETSRC(2)                               /*!< TIMER0 CH2 event select */
#define ADC_EXTTRIG_ROUTINE_T1_CH1      CTL1_ETSRC(3)                               /*!< TIMER1 CH1 event select */
#define ADC_EXTTRIG_ROUTINE_T1_CH2      CTL1_ETSRC(4)                               /*!< TIMER1 CH2 event select */
#define ADC_EXTTRIG_ROUTINE_T1_CH3      CTL1_ETSRC(5)                               /*!< TIMER1 CH3 event select */
#define ADC_EXTTRIG_ROUTINE_T1_TRGO     CTL1_ETSRC(6)                               /*!< TIMER1 TRGO event select */
#define ADC_EXTTRIG_ROUTINE_T2_CH0      CTL1_ETSRC(7)                               /*!< TIMER2 CH0 event select */
#define ADC_EXTTRIG_ROUTINE_T2_TRGO     CTL1_ETSRC(8)                               /*!< TIMER2 TRGO event select */
#define ADC_EXTTRIG_ROUTINE_T3_CH3      CTL1_ETSRC(9)                               /*!< TIMER3 CH3 event select */
#define ADC_EXTTRIG_ROUTINE_T4_CH0      CTL1_ETSRC(10)                              /*!< TIMER4 CH0 event select */
#define ADC_EXTTRIG_ROUTINE_T4_CH1      CTL1_ETSRC(11)                              /*!< TIMER4 CH1 event select */
#define ADC_EXTTRIG_ROUTINE_T4_CH2      CTL1_ETSRC(12)                              /*!< TIMER4 CH2 event select */
#define ADC_EXTTRIG_ROUTINE_EXTI_11     CTL1_ETSRC(15)                              /*!< external interrupt line 11 select  */

/* ADC external trigger select for inserted sequence */
#define CTL1_ETSIC(regval)              (BITS(16, 19) & ((uint32_t)(regval) << 16))
#define ADC_EXTTRIG_INSERTED_T0_CH3     CTL1_ETSIC(0)                               /*!< TIMER0 CH3 event select */
#define ADC_EXTTRIG_INSERTED_T0_TRGO    CTL1_ETSIC(1)                               /*!< TIMER0 TRGO event */
#define ADC_EXTTRIG_INSERTED_T1_CH0     CTL1_ETSIC(2)                               /*!< TIMER1 CH0 event select */
#define ADC_EXTTRIG_INSERTED_T1_TRGO    CTL1_ETSIC(3)                               /*!< TIMER1 TRGO event */
#define ADC_EXTTRIG_INSERTED_T2_CH1     CTL1_ETSIC(4)                               /*!< TIMER2 CH1 event select */
#define ADC_EXTTRIG_INSERTED_T2_CH3     CTL1_ETSIC(5)                               /*!< TIMER2 CH3 event select */
#define ADC_EXTTRIG_INSERTED_T3_CH0     CTL1_ETSIC(6)                               /*!< TIMER3 CH0 event select */
#define ADC_EXTTRIG_INSERTED_T3_CH1     CTL1_ETSIC(7)                               /*!< TIMER3 CH1 event select */
#define ADC_EXTTRIG_INSERTED_T3_CH2     CTL1_ETSIC(8)                               /*!< TIMER3 CH2 event select */
#define ADC_EXTTRIG_INSERTED_T3_TRGO    CTL1_ETSIC(9)                               /*!< TIMER3 TRGO event select */
#define ADC_EXTTRIG_INSERTED_T4_CH3     CTL1_ETSIC(10)                              /*!< TIMER4 CH3 event select */
#define ADC_EXTTRIG_INSERTED_T4_TRGO    CTL1_ETSIC(11)                              /*!< TIMER4 TRGO event select */
#define ADC_EXTTRIG_INSERTED_EXTI_15    CTL1_ETSIC(15)                              /*!< external interrupt line 15 */

/* ADC channel sample time */
#define SAMPTX_SPT(regval)              (BITS(0, 2) & ((uint32_t)(regval) << 0))    /*!< write value to ADC_SAMPTX_SPT bit field */
#define ADC_SAMPLETIME_1POINT5          SAMPTX_SPT(0)                               /*!< 1.5 sampling cycles */
#define ADC_SAMPLETIME_14POINT5         SAMPTX_SPT(1)                               /*!< 14.5 sampling cycles */
#define ADC_SAMPLETIME_27POINT5         SAMPTX_SPT(2)                               /*!< 27.5 sampling cycles */
#define ADC_SAMPLETIME_55POINT5         SAMPTX_SPT(3)                               /*!< 55.5 sampling cycles */
#define ADC_SAMPLETIME_83POINT5         SAMPTX_SPT(4)                               /*!< 83.5 sampling cycles */
#define ADC_SAMPLETIME_111POINT5        SAMPTX_SPT(5)                               /*!< 111.5 sampling cycles */
#define ADC_SAMPLETIME_143POINT5        SAMPTX_SPT(6)                               /*!< 143.5 sampling cycles */
#define ADC_SAMPLETIME_479POINT5        SAMPTX_SPT(7)                               /*!< 479.5 sampling cycles */

/* ADC_IOFFX register value */
#define IOFFX_IOFF(regval)              (BITS(0, 11) & ((uint32_t)(regval) << 0))   /*!< write value to ADC_IOFFX_IOFF bit field */

#if defined(GD32F5HC)
/* ADC_WD0HT register value */
#define WD0HT_WD0HT(regval)             (BITS(0, 19) & ((uint32_t)(regval) << 0))   /*!< write value to ADC_WD0HT_WD0HT bit field */
#else
/* ADC_WD0HT register value */
#define WD0HT_WD0HT(regval)             (BITS(0, 11) & ((uint32_t)(regval) << 0))   /*!< write value to ADC_WD0HT_WD0HT bit field */
#endif /* defined(GD32F5HC) */

#if defined(GD32F5HC)
/* ADC_WD0LT register value */
#define WD0LT_WD0LT(regval)             (BITS(0, 19) & ((uint32_t)(regval) << 0))   /*!< write value to ADC_WD0LT_WD0LT bit field */
#else
/* ADC_WD0LT register value */
#define WD0LT_WD0LT(regval)             (BITS(0, 11) & ((uint32_t)(regval) << 0))   /*!< write value to ADC_WD0LT_WD0LT bit field */
#endif /* defined(GD32F5HC) */

/* ADC_RSQX register value */
#define RSQ0_RL(regval)                 (BITS(20, 23) & ((uint32_t)(regval) << 20)) /*!< write value to ADC_RSQ0_RL bit field */

/* ADC_ISQ register value */
#define ISQ_IL(regval)                  (BITS(20, 21) & ((uint32_t)(regval) << 20)) /*!< write value to ADC_ISQ_IL bit field */

/* ADC_OVSAMPCTL register value */
/* oversampling shift */
#define OVSAMPCTL_OVSS(regval)          (BITS(5, 8) & ((uint32_t)(regval) << 5))    /*!< write value to ADC_OVSAMPCTL_OVSS bit field */
#define ADC_OVERSAMPLING_SHIFT_NONE     OVSAMPCTL_OVSS(0)                           /*!< no oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_1B       OVSAMPCTL_OVSS(1)                           /*!< 1-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_2B       OVSAMPCTL_OVSS(2)                           /*!< 2-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_3B       OVSAMPCTL_OVSS(3)                           /*!< 3-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_4B       OVSAMPCTL_OVSS(4)                           /*!< 4-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_5B       OVSAMPCTL_OVSS(5)                           /*!< 5-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_6B       OVSAMPCTL_OVSS(6)                           /*!< 6-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_7B       OVSAMPCTL_OVSS(7)                           /*!< 7-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_8B       OVSAMPCTL_OVSS(8)                           /*!< 8-bit oversampling shift */

/* oversampling ratio */
#define OVSAMPCTL_OVSR(regval)          (BITS(2, 4) & ((uint32_t)(regval) << 2))    /*!< write value to ADC_OVSAMPCTL_OVSR bit field */
#define ADC_OVERSAMPLING_RATIO_MUL2     OVSAMPCTL_OVSR(0)                           /*!< oversampling ratio multiple 2 */
#define ADC_OVERSAMPLING_RATIO_MUL4     OVSAMPCTL_OVSR(1)                           /*!< oversampling ratio multiple 4 */
#define ADC_OVERSAMPLING_RATIO_MUL8     OVSAMPCTL_OVSR(2)                           /*!< oversampling ratio multiple 8 */
#define ADC_OVERSAMPLING_RATIO_MUL16    OVSAMPCTL_OVSR(3)                           /*!< oversampling ratio multiple 16 */
#define ADC_OVERSAMPLING_RATIO_MUL32    OVSAMPCTL_OVSR(4)                           /*!< oversampling ratio multiple 32 */
#define ADC_OVERSAMPLING_RATIO_MUL64    OVSAMPCTL_OVSR(5)                           /*!< oversampling ratio multiple 64 */
#define ADC_OVERSAMPLING_RATIO_MUL128   OVSAMPCTL_OVSR(6)                           /*!< oversampling ratio multiple 128 */
#define ADC_OVERSAMPLING_RATIO_MUL256   OVSAMPCTL_OVSR(7)                           /*!< oversampling ratio multiple 256 */

/* triggered oversampling */
#define ADC_OVERSAMPLING_ALL_CONVERT    ((uint32_t)0x00000000U)                     /*!< all oversampled conversions for a channel are done consecutively after a trigger */
#define ADC_OVERSAMPLING_ONE_CONVERT    ADC_OVSAMPCTL_TOVS                          /*!< each oversampled conversion for a channel needs a trigger */

/* ADC channel sequence definitions */
#define ADC_ROUTINE_CHANNEL             ((uint8_t)0x01U)                            /*!< ADC routine channel sequence */
#define ADC_INSERTED_CHANNEL            ((uint8_t)0x02U)                            /*!< ADC inserted channel sequence */
#define ADC_ROUTINE_INSERTED_CHANNEL    ((uint8_t)0x03U)                            /*!< both routine and inserted channel sequence */
#define ADC_CHANNEL_DISCON_DISABLE      ((uint8_t)0x04U)                            /*!< disable discontinuous mode of routine & inserted sequence */

/* ADC inserted channel definitions */
#define ADC_INSERTED_CHANNEL_0          ((uint8_t)0x00U)                            /*!< ADC inserted channel 0 */
#define ADC_INSERTED_CHANNEL_1          ((uint8_t)0x01U)                            /*!< ADC inserted channel 1 */
#define ADC_INSERTED_CHANNEL_2          ((uint8_t)0x02U)                            /*!< ADC inserted channel 2 */
#define ADC_INSERTED_CHANNEL_3          ((uint8_t)0x03U)                            /*!< ADC inserted channel 3 */


/* ADC channel definitions */
#define ADC_CHANNEL_0                   ((uint8_t)0x00U)                            /*!< ADC channel 0 */
#define ADC_CHANNEL_1                   ((uint8_t)0x01U)                            /*!< ADC channel 1 */
#define ADC_CHANNEL_2                   ((uint8_t)0x02U)                            /*!< ADC channel 2 */
#define ADC_CHANNEL_3                   ((uint8_t)0x03U)                            /*!< ADC channel 3 */
#define ADC_CHANNEL_4                   ((uint8_t)0x04U)                            /*!< ADC channel 4 */
#define ADC_CHANNEL_5                   ((uint8_t)0x05U)                            /*!< ADC channel 5 */
#define ADC_CHANNEL_6                   ((uint8_t)0x06U)                            /*!< ADC channel 6 */
#define ADC_CHANNEL_7                   ((uint8_t)0x07U)                            /*!< ADC channel 7 */
#define ADC_CHANNEL_8                   ((uint8_t)0x08U)                            /*!< ADC channel 8 */
#define ADC_CHANNEL_9                   ((uint8_t)0x09U)                            /*!< ADC channel 9 */
#define ADC_CHANNEL_10                  ((uint8_t)0x0AU)                            /*!< ADC channel 10 */
#define ADC_CHANNEL_11                  ((uint8_t)0x0BU)                            /*!< ADC channel 11 */
#if defined(GD32F5HC)
#define ADC_CHANNEL_12                  ((uint8_t)0x0CU)                            /*!< ADC channel 12 */
#define ADC_CHANNEL_13                  ((uint8_t)0x0DU)                            /*!< ADC channel 13 */
#define ADC_CHANNEL_14                  ((uint8_t)0x0EU)                            /*!< ADC channel 14 */
#endif /* defined(GD32F5HC) */

#if defined(GD32F5HC)
/* ADC latch data definitions */
#define ADC_LATCH_DATA_0                ((uint8_t)0x00U)                            /*!< ADC latch data 0 */
#define ADC_LATCH_DATA_1                ((uint8_t)0x01U)                            /*!< ADC latch data 1 */
#define ADC_LATCH_DATA_2                ((uint8_t)0x02U)                            /*!< ADC latch data 2 */
#define ADC_LATCH_DATA_3                ((uint8_t)0x03U)                            /*!< ADC latch data 3 */
#endif /* defined(GD32F5HC) */

/* ADC status flag */
#define ADC_FLAG_WD0E                   ADC_STAT_WD0E                               /*!< analog watchdog 0 event flag */
#if defined(GD32F5HC)
#define ADC_FLAG_EORC                   ADC_STAT_EORC                               /*!< end of routine sequence conversion */
#else
#define ADC_FLAG_EOC                    ADC_STAT_EOC                                /*!< end of conversion */
#endif /* defined(GD32F5HC) */
#define ADC_FLAG_EOIC                   ADC_STAT_EOIC                               /*!< end of inserted sequence conversion */
#define ADC_FLAG_STIC                   ADC_STAT_STIC                               /*!< inserted sequence start flag */
#define ADC_FLAG_STRC                   ADC_STAT_STRC                               /*!< routine sequence start flag */
#define ADC_FLAG_ROVF                   ADC_STAT_ROVF                               /*!< routine data register overflow */
#if defined(GD32F5HC)
#define ADC_FLAG_IOVF                   ADC_STAT_IOVF                               /*!< inserted data register overflow */
#endif /* defined(GD32F5HC) */

/* ADC interrupt flag */
#define ADC_INT_WD0E                    ADC_CTL0_WD0EIE                             /*!< analog watchdog 0 event interrupt */
#if defined(GD32F5HC)
#define ADC_INT_EORC                    ADC_CTL0_EORCIE                             /*!< end of routine sequence conversion interrupt */
#else
#define ADC_INT_EOC                     ADC_CTL0_EOCIE                              /*!< end of sequence conversion interrupt */
#endif /* defined(GD32F5HC) */
#define ADC_INT_EOIC                    ADC_CTL0_EOICIE                             /*!< end of inserted sequence conversion interrupt */
#define ADC_INT_ROVF                    ADC_CTL0_ROVFIE                             /*!< routine data register overflow */
#if defined(GD32F5HC)
#define ADC_INT_IOVF                    ADC_CTL0_IOVFIE                             /*!< inserted data register overflow */
#endif /* defined(GD32F5HC) */

/* ADC interrupt flag */
#define ADC_INT_FLAG_WD0E               ADC_STAT_WD0E                               /*!< analog watchdog 0 event interrupt */
#if defined(GD32F5HC)
#define ADC_INT_FLAG_EORC               ADC_STAT_EORC                               /*!< end of routine sequence conversion interrupt */
#else
#define ADC_INT_FLAG_EOC                ADC_STAT_EOC                                /*!< end of sequence conversion interrupt */
#endif /* defined(GD32F5HC) */
#define ADC_INT_FLAG_EOIC               ADC_STAT_EOIC                               /*!< end of inserted sequence conversion interrupt */
#define ADC_INT_FLAG_ROVF               ADC_STAT_ROVF                               /*!< routine data register overflow */
#if defined(GD32F5HC)
#define ADC_INT_FLAG_IOVF               ADC_STAT_IOVF                               /*!< inserted data register overflow */
#endif /* defined(GD32F5HC) */

/* configure the ADC clock */
#define CCTL_ADCCK(regval)              (BITS(16,18) & ((uint32_t)(regval) << 16))
#define ADC_ADCCK_PCLK2_DIV2            CCTL_ADCCK(0)                               /*!< PCLK2 div2 */
#define ADC_ADCCK_PCLK2_DIV4            CCTL_ADCCK(1)                               /*!< PCLK2 div4 */
#define ADC_ADCCK_PCLK2_DIV6            CCTL_ADCCK(2)                               /*!< PCLK2 div6 */
#define ADC_ADCCK_PCLK2_DIV8            CCTL_ADCCK(3)                               /*!< PCLK2 div8 */
#define ADC_ADCCK_HCLK_DIV5             CCTL_ADCCK(4)                               /*!< HCLK div5 */
#define ADC_ADCCK_HCLK_DIV6             CCTL_ADCCK(5)                               /*!< HCLK div6 */
#define ADC_ADCCK_HCLK_DIV10            CCTL_ADCCK(6)                               /*!< HCLK div10 */
#define ADC_ADCCK_HCLK_DIV20            CCTL_ADCCK(7)                               /*!< HCLK div20 */

/* end of conversion mode */
#define ADC_EORC_SET_SEQUENCE           ((uint8_t)0x00U)                            /*!< only at the end of a sequence of routine conversions, the EORC bit is set */
#define ADC_EORC_SET_CONVERSION         ADC_CTL1_EORCM                              /*!< at the end of each routine conversion, the EORC bit is set */

/* function declarations */
/* ADC deinitialization and initialization functions */
/* reset ADC */
void adc_deinit(void);
/* configure the ADC clock */
void adc_clock_config(uint32_t prescaler);
/* enable ADC interface */
void adc_enable(void);
/* disable ADC interface */
void adc_disable(void);

/* ADC DMA functions */
/* enable DMA request */
void adc_dma_mode_enable(uint8_t adc_sequence);
/* disable DMA request */
void adc_dma_mode_disable(uint8_t adc_sequence);
/* when DMA=1, the DMA engine issues a request at end of each conversion */
void adc_dma_request_after_last_enable(uint8_t adc_sequence);
/* the DMA engine is disabled after the end of transfer signal from DMA controller is detected */
void adc_dma_request_after_last_disable(uint8_t adc_sequence);
/* configure end of conversion mode */
void adc_end_of_conversion_config(uint32_t end_selection);
/* enable or disable ADC internal channels */
void adc_internal_channel_config(uint32_t internal_channel, ControlStatus newvalue);

/* ADC special function functions */
/* configure ADC discontinuous mode */
void adc_discontinuous_mode_config(uint8_t adc_sequence, uint8_t length);
/* enable or disable ADC special function */
void adc_special_function_config(uint32_t function, ControlStatus newvalue);

/* ADC channel configuration functions */
/* configure ADC data alignment */
void adc_data_alignment_config(uint32_t data_alignment);
/* configure the length of routine sequence or inserted sequence */
void adc_channel_length_config(uint8_t adc_sequence, uint32_t length);
/* configure ADC routine channel */
void adc_routine_channel_config(uint8_t rank, uint8_t adc_channel, uint32_t sample_time);
/* configure ADC inserted channel */
void adc_inserted_channel_config(uint8_t rank, uint8_t adc_channel, uint32_t sample_time);
/* configure ADC inserted channel offset */
void adc_inserted_channel_offset_config(uint8_t inserted_channel, uint16_t offset);

/* ADC external trigger functions */
/* configure ADC external trigger */
void adc_external_trigger_config(uint8_t adc_sequence, uint32_t trigger_mode);
/* configure ADC external trigger source */
void adc_external_trigger_source_config(uint8_t adc_sequence, uint32_t external_trigger_source);
/* enable ADC software trigger */
void adc_software_trigger_enable(uint8_t adc_sequence);


/* ADC data read functions */
/* read ADC routine sequence data register */
uint16_t adc_routine_data_read(void);
#if defined(GD32F5HC)
/* read ADC inserted sequence data register */
uint16_t adc_inserted_data_read(void);
#else
/* read ADC inserted sequence data register */
uint16_t adc_inserted_data_read(uint8_t inserted_channel);
#endif /* defined(GD32F5HC) */
#if defined(GD32F5HC)
/* read ADC latch data register */
uint16_t adc_latch_data_read(uint8_t latch_data);
/* configure ADC latch data source */
void adc_latch_data_source_config(uint8_t latch_data, uint8_t adc_sequence,uint8_t rank);
#endif /* defined(GD32F5HC) */

/* ADC analog watchdog functions */
/* enable ADC analog watchdog single channel */
void adc_watchdog0_single_channel_enable(uint8_t adc_channel);
/* configure ADC analog watchdog sequence channel */
void adc_watchdog0_sequence_channel_enable(uint8_t adc_sequence);
/* disable ADC analog watchdog */
void adc_watchdog0_disable(void);
/* configure ADC analog watchdog threshold */
void adc_watchdog0_threshold_config(uint32_t low_threshold, uint32_t high_threshold);

/* ADC oversample functions */
/* configure ADC oversample mode */
void adc_oversample_mode_config(uint32_t mode, uint16_t shift, uint8_t ratio);
/* enable ADC oversample mode */
void adc_oversample_mode_enable(void);
/* disable ADC oversample mode */
void adc_oversample_mode_disable(void);

/* flag and interrupt functions */
/* get the ADC flag */
FlagStatus adc_flag_get(uint32_t flag);
/* clear the ADC flag */
void adc_flag_clear(uint32_t flag);
/* enable ADC interrupt */
void adc_interrupt_enable(uint32_t interrupt);
/* disable ADC interrupt */
void adc_interrupt_disable(uint32_t interrupt);
/* get the ADC interrupt */
FlagStatus adc_interrupt_flag_get(uint32_t int_flag);
/* clear the ADC flag */
void adc_interrupt_flag_clear(uint32_t int_flag);

#endif /* gd32w51x_f5hc_ADC_H */

