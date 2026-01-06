/*!
    \file    gd32l23x_adc.h
    \brief   definitions for the ADC

    \version 2025-08-08, V2.3.0, firmware for GD32L23x, add support for GD32L235
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

#ifndef GD32L23X_ADC_H
#define GD32L23X_ADC_H

#include "gd32l23x.h"

/* ADC definitions */
#define ADC                                    ADC_BASE                                    /*!< ADC base address */

/* registers definitions */
#define ADC_STAT                               REG32(ADC + 0x00000000U)                    /*!< ADC status register */
#define ADC_CTL0                               REG32(ADC + 0x00000004U)                    /*!< ADC control register 0 */
#define ADC_CTL1                               REG32(ADC + 0x00000008U)                    /*!< ADC control register 1 */
#define ADC_SAMPT0                             REG32(ADC + 0x0000000CU)                    /*!< ADC sample time register 0 */
#define ADC_SAMPT1                             REG32(ADC + 0x00000010U)                    /*!< ADC sample time register 1 */
#define ADC_IOFF0                              REG32(ADC + 0x00000014U)                    /*!< ADC inserted channel data offset register 0 */
#define ADC_IOFF1                              REG32(ADC + 0x00000018U)                    /*!< ADC inserted channel data offset register 1 */
#define ADC_IOFF2                              REG32(ADC + 0x0000001CU)                    /*!< ADC inserted channel data offset register 2 */
#define ADC_IOFF3                              REG32(ADC + 0x00000020U)                    /*!< ADC inserted channel data offset register 3 */
#define ADC_WDHT                               REG32(ADC + 0x00000024U)                    /*!< ADC watchdog high threshold register */
#define ADC_WDLT                               REG32(ADC + 0x00000028U)                    /*!< ADC watchdog low threshold register */
#define ADC_RSQ0                               REG32(ADC + 0x0000002CU)                    /*!< ADC routine sequence register 0 */
#define ADC_RSQ1                               REG32(ADC + 0x00000030U)                    /*!< ADC routine sequence register 1 */
#define ADC_RSQ2                               REG32(ADC + 0x00000034U)                    /*!< ADC routine sequence register 2 */
#define ADC_ISQ                                REG32(ADC + 0x00000038U)                    /*!< ADC inserted sequence register */
#define ADC_IDATA0                             REG32(ADC + 0x0000003CU)                    /*!< ADC inserted data register 0 */
#define ADC_IDATA1                             REG32(ADC + 0x00000040U)                    /*!< ADC inserted data register 1 */
#define ADC_IDATA2                             REG32(ADC + 0x00000044U)                    /*!< ADC inserted data register 2 */
#define ADC_IDATA3                             REG32(ADC + 0x00000048U)                    /*!< ADC inserted data register 3 */
#define ADC_RDATA                              REG32(ADC + 0x0000004CU)                    /*!< ADC routine data register */
#define ADC_OVSAMPCTL                          REG32(ADC + 0x00000080U)                    /*!< ADC oversampling control register */
#define ADC_CCTL                               REG32(ADC + 0x000000C0U)                    /*!< ADC charge control register */
#ifdef GD32L235
    #define ADC_DIFCTL                         REG32(ADC + 0x000000C4U)                    /*!< ADC differential mode control register */
#endif

/* bits definitions */
/* ADC_STAT */
#define ADC_STAT_WDE                           BIT(0)                                      /*!< analog watchdog event flag */
#define ADC_STAT_EOC                           BIT(1)                                      /*!< end of sequence conversion */
#define ADC_STAT_EOIC                          BIT(2)                                      /*!< end of inserted sequence conversion */
#define ADC_STAT_STIC                          BIT(3)                                      /*!< inserted sequence start flag */
#define ADC_STAT_STRC                          BIT(4)                                      /*!< routine sequence start flag */

/* ADC_CTL0 */
#define ADC_CTL0_WDCHSEL                       BITS(0, 4)                                  /*!< analog watchdog channel select bits */
#define ADC_CTL0_EOCIE                         BIT(5)                                      /*!< interrupt enable for EOC */
#define ADC_CTL0_WDEIE                         BIT(6)                                      /*!< analog watchdog interrupt enable */
#define ADC_CTL0_EOICIE                        BIT(7)                                      /*!< interrupt enable for inserted channels */
#define ADC_CTL0_SM                            BIT(8)                                      /*!< scan mode */
#define ADC_CTL0_WDSC                          BIT(9)                                      /*!< when in scan mode, analog watchdog is effective on a single channel */
#define ADC_CTL0_ICA                           BIT(10)                                     /*!< automatic inserted sequence conversion */
#define ADC_CTL0_DISRC                         BIT(11)                                     /*!< discontinuous mode on routine channels */
#define ADC_CTL0_DISIC                         BIT(12)                                     /*!< discontinuous mode on inserted channels */
#define ADC_CTL0_DISNUM                        BITS(13, 15)                                /*!< discontinuous mode channel count */
#define ADC_CTL0_IWDEN                         BIT(22)                                     /*!< analog watchdog enable on inserted channels */
#define ADC_CTL0_RWDEN                         BIT(23)                                     /*!< analog watchdog enable on routine channels */
#define ADC_CTL0_DRES                          BITS(24, 25)                                /*!< ADC resolution */

/* ADC_CTL1 */
#define ADC_CTL1_ADCON                         BIT(0)                                      /*!< ADC converter on */
#define ADC_CTL1_CTN                           BIT(1)                                      /*!< continuous conversion */
#define ADC_CTL1_CLB                           BIT(2)                                      /*!< ADC calibration */
#define ADC_CTL1_RSTCLB                        BIT(3)                                      /*!< reset calibration */
#ifdef GD32L235
    #define ADC_CTL1_CALNUM                    BITS(4, 6)                                  /*!< ADC calibration times */
#endif
#define ADC_CTL1_DMA                           BIT(8)                                      /*!< dma request enable */
#define ADC_CTL1_DAL                           BIT(11)                                     /*!< data alignment */
#define ADC_CTL1_ETSIC                         BITS(12, 14)                                /*!< external trigger select for inserted channel */
#define ADC_CTL1_ETEIC                         BIT(15)                                     /*!< external trigger enable for inserted channel */
#define ADC_CTL1_ETSRC                         BITS(17, 19)                                /*!< external trigger select for routine channel */
#define ADC_CTL1_ETERC                         BIT(20)                                     /*!< external trigger enable for routine channel */
#define ADC_CTL1_SWICST                        BIT(21)                                     /*!< start on inserted channels */
#define ADC_CTL1_SWRCST                        BIT(22)                                     /*!< start on routine channels */
#define ADC_CTL1_TSVEN                         BIT(23)                                     /*!< channel 16(temperature sensor)enable of ADC */
#define ADC_CTL1_INREFEN                       BIT(24)                                     /*!< channel 17(internal reference voltage)enable of ADC */
#define ADC_CTL1_VBATEN                        BIT(25)                                     /*!< channel 18(1/3 voltage of external battery)enable of ADC */
#define ADC_CTL1_VSLCDEN                       BIT(26)                                     /*!< channel 19(1/3 voltage of VSLCD)enable of ADC */

/* ADC_SAMPTx x=0..1 */
#define ADC_SAMPTX_SPTN                        BITS(0, 2)                                  /*!< channel n(n=0..19) sampling time selection */

/* ADC_IOFFx x=0..3 */
#define ADC_IOFFX_IOFF                         BITS(0, 11)                                 /*!< data offset for inserted channel x */

/* ADC_WDHT */
#define ADC_WDHT_WDHT                          BITS(0, 11)                                 /*!< analog watchdog high threshold */

/* ADC_WDLT */
#define ADC_WDLT_WDLT                          BITS(0, 11)                                 /*!< analog watchdog low threshold */

/* ADC_RSQx */
#define ADC_RSQX_RSQN                          BITS(0, 4)                                  /*!< x(x = 0..15) conversion in routine sequence */
#define ADC_RSQ0_RL                            BITS(20, 23)                                /*!< routine channel sequence length */

/* ADC_ISQ */
#define ADC_ISQ_ISQN                           BITS(0, 4)                                  /*!< x conversion in inserted sequence */
#define ADC_ISQ_IL                             BITS(20, 21)                                /*!< inserted sequence length */

/* ADC_IDATAx x=0..3*/
#define ADC_IDATAX_IDATAN                      BITS(0, 15)                                 /*!< inserted channel x conversion data */

/* ADC_RDATA */
#define ADC_RDATA_RDATA                        BITS(0, 15)                                 /*!< routine sequence data */

/* ADC_OVSAMPCTL */
#define ADC_OVSAMPCTL_OVSEN                    BIT(0)                                      /*!< oversampling enable */
#define ADC_OVSAMPCTL_OVSR                     BITS(2, 4)                                  /*!< oversampling ratio */
#define ADC_OVSAMPCTL_OVSS                     BITS(5, 8)                                  /*!< oversampling shift */
#define ADC_OVSAMPCTL_TOVS                     BIT(9)                                      /*!< triggered oversampling */

/* ADC_CCTL */
#define ADC_CCTL_CCNT                          BITS(0, 11)                                 /*!< ADC charge pulse width counter */
#define ADC_CCTL_CHARGE                        BIT(16)                                     /*!< ADC charge status */

#ifdef GD32L235
    /* ADC_DIFCTL */
    #define ADC_DIFCTL_DIFCTL                  BITS(0, 19)                                 /*!< Differential mode for channel 17..0 */
#endif

/* constants definitions */
/* ADC flag definitions */
#define ADC_FLAG_WDE                           ADC_STAT_WDE                                /*!< analog watchdog event flag */
#define ADC_FLAG_EOC                           ADC_STAT_EOC                                /*!< end of sequence conversion */
#define ADC_FLAG_EOIC                          ADC_STAT_EOIC                               /*!< end of inserted sequence conversion */
#define ADC_FLAG_STIC                          ADC_STAT_STIC                               /*!< inserted sequence start flag */
#define ADC_FLAG_STRC                          ADC_STAT_STRC                               /*!< routine sequence start flag */
#define ADC_FLAG_CHARGE                        ADC_CCTL_CHARGE                             /*!< ADC charge flag */

/* ADC_CTL0 register value */
#define CTL0_DISNUM(regval)                    (BITS(13, 15) & ((uint32_t)(regval) << 13)) /*!< write value to ADC_CTL0_DISNUM bit field */

/* ADC special function definitions */
#define ADC_SCAN_MODE                          ADC_CTL0_SM                                 /*!< scan mode */
#define ADC_INSERTED_CHANNEL_AUTO              ADC_CTL0_ICA                                /*!< inserted sequence convert automatically */
#define ADC_CONTINUOUS_MODE                    ADC_CTL1_CTN                                /*!< continuous mode */

/* ADC calibration times */
#define CTL1_CALNUM(regval)                    (BITS(4,6) & ((uint32_t)(regval) << 4U))    /*!< write value to ADC_CTL1_CLBNUM bit field */
#define ADC_CALIBRATION_NUM1                   CTL1_CALNUM(0)                              /*!< ADC calibration 1 time */
#define ADC_CALIBRATION_NUM2                   CTL1_CALNUM(1)                              /*!< ADC calibration 2 times */
#define ADC_CALIBRATION_NUM4                   CTL1_CALNUM(2)                              /*!< ADC calibration 4 times */
#define ADC_CALIBRATION_NUM8                   CTL1_CALNUM(3)                              /*!< ADC calibration 8 times */
#define ADC_CALIBRATION_NUM16                  CTL1_CALNUM(4)                              /*!< ADC calibration 16 times */
#define ADC_CALIBRATION_NUM32                  CTL1_CALNUM(5)                              /*!< ADC calibration 32 times */

/* temperature sensor channel, internal reference voltage channel, VBAT channel and VSLCD channel */
#define ADC_TEMP_CHANNEL_SWITCH                ADC_CTL1_TSVEN                              /*!< temperature channel */
#define ADC_INTERNAL_CHANNEL_SWITCH            ADC_CTL1_INREFEN                            /*!< internal Vref channel */
#define ADC_VBAT_CHANNEL_SWITCH                ADC_CTL1_VBATEN                             /*!< VBAT channel */
#define ADC_VSLCD_CHANNEL_SWITCH               ADC_CTL1_VSLCDEN                            /*!< VSLCD channel */

/* ADC data alignment */
#define ADC_DATAALIGN_RIGHT                    ((uint32_t)0x00000000U)                     /*!< LSB alignment */
#define ADC_DATAALIGN_LEFT                     ADC_CTL1_DAL                                /*!< MSB alignment */

/* ADC external trigger select for routine sequence */
#define CTL1_ETSRC(regval)                     (BITS(17, 19) & ((uint32_t)(regval) << 17))
#define ADC_EXTTRIG_ROUTINE_T8_CH0             CTL1_ETSRC(0)                               /*!< TIMER8 CH0 event select */
#define ADC_EXTTRIG_ROUTINE_T8_CH1             CTL1_ETSRC(1)                               /*!< TIMER8 CH1 event select */
#ifdef GD32L235
    #define ADC_EXTTRIG_ROUTINE_T0_CH2         CTL1_ETSRC(2)                               /*!< TIMER0 CH2 event select */
#endif
#define ADC_EXTTRIG_ROUTINE_T1_CH1             CTL1_ETSRC(3)                               /*!< TIMER1 CH1 event select */
#define ADC_EXTTRIG_ROUTINE_T2_TRGO            CTL1_ETSRC(4)                               /*!< TIMER2 TRGO event select */
#define ADC_EXTTRIG_ROUTINE_T11_CH0            CTL1_ETSRC(5)                               /*!< TIMER11 CH0 event select */
#define ADC_EXTTRIG_ROUTINE_EXTI_11            CTL1_ETSRC(6)                               /*!< external interrupt line 11 select  */
#define ADC_EXTTRIG_ROUTINE_NONE               CTL1_ETSRC(7)                               /*!< software trigger select  */

/* ADC external trigger select for inserted sequence */
#define CTL1_ETSIC(regval)                     (BITS(12, 14) & ((uint32_t)(regval) << 12))
#ifdef GD32L235
    #define ADC_EXTTRIG_INSERTED_T0_TRGO       CTL1_ETSIC(0)                               /*!< TIMER0 TRGO event select */
    #define ADC_EXTTRIG_INSERTED_T0_CH3        CTL1_ETSIC(1)                               /*!< TIMER0 CH3 event select */
    #define ADC_EXTTRIG_INSERTED_T14_TRGO      CTL1_ETSIC(5)                               /*!< TIMER14 TRGO event select */
#endif
#define ADC_EXTTRIG_INSERTED_T1_TRGO           CTL1_ETSIC(2)                               /*!< TIMER1 TRGO event select */
#define ADC_EXTTRIG_INSERTED_T1_CH0            CTL1_ETSIC(3)                               /*!< TIMER1 CH0 event select */
#define ADC_EXTTRIG_INSERTED_T2_CH3            CTL1_ETSIC(4)                               /*!< TIMER2 CH3 event select */
#define ADC_EXTTRIG_INSERTED_EXTI_15           CTL1_ETSIC(6)                               /*!< external interrupt line 15 */
#define ADC_EXTTRIG_INSERTED_NONE              CTL1_ETSIC(7)                               /*!< software trigger select */

/* ADC channel sample time */
#define SAMPTX_SPT(regval)                     (BITS(0, 2) & ((uint32_t)(regval) << 0))    /*!< write value to ADC_SAMPTX_SPT bit field */
#define ADC_SAMPLETIME_2POINT5                 SAMPTX_SPT(0)                               /*!< 2.5 sampling cycles */
#define ADC_SAMPLETIME_7POINT5                 SAMPTX_SPT(1)                               /*!< 7.5 sampling cycles */
#define ADC_SAMPLETIME_13POINT5                SAMPTX_SPT(2)                               /*!< 13.5 sampling cycles */
#define ADC_SAMPLETIME_28POINT5                SAMPTX_SPT(3)                               /*!< 28.5 sampling cycles */
#define ADC_SAMPLETIME_41POINT5                SAMPTX_SPT(4)                               /*!< 41.5 sampling cycles */
#define ADC_SAMPLETIME_55POINT5                SAMPTX_SPT(5)                               /*!< 55.5 sampling cycles */
#define ADC_SAMPLETIME_71POINT5                SAMPTX_SPT(6)                               /*!< 71.5 sampling cycles */
#define ADC_SAMPLETIME_239POINT5               SAMPTX_SPT(7)                               /*!< 239.5 sampling cycles */

/* ADC_IOFFX register value */
#define IOFFX_IOFF(regval)                     (BITS(0, 11) & ((uint32_t)(regval) << 0))   /*!< write value to ADC_IOFFX_IOFF bit field */

/* ADC_WDHT register value */
#define WDHT_WDHT(regval)                      (BITS(0, 11) & ((uint32_t)(regval) << 0))   /*!< write value to ADC_WDHT_WDHT bit field */

/* ADC_WDLT register value */
#define WDLT_WDLT(regval)                      (BITS(0, 11) & ((uint32_t)(regval) << 0))   /*!< write value to ADC_WDLT_WDLT bit field */

/* ADC_RSQX register value */
#define RSQ0_RL(regval)                        (BITS(20, 23) & ((uint32_t)(regval) << 20)) /*!< write value to ADC_RSQ0_RL bit field */

/* ADC_ISQ register value */
#define ISQ_IL(regval)                         (BITS(20, 21) & ((uint32_t)(regval) << 20)) /*!< write value to ADC_ISQ_IL bit field */

/* ADC_CCTL register value */
#define CCTL_CCNT(regval)                      (BITS(0, 11) & ((uint32_t)(regval) << 0))   /*!< write value to ADC_CCTL_CCNT bit field */

/* ADC_OVSAMPCTL register value */
/* ADC resolution configure */
#define CTL0_DRES(regval)                      (BITS(24, 25) & ((uint32_t)(regval) << 24))
#define ADC_RESOLUTION_12B                     CTL0_DRES(0)                                /*!< 12-bit ADC resolution */
#define ADC_RESOLUTION_10B                     CTL0_DRES(1)                                /*!< 10-bit ADC resolution */
#define ADC_RESOLUTION_8B                      CTL0_DRES(2)                                /*!< 8-bit ADC resolution */
#define ADC_RESOLUTION_6B                      CTL0_DRES(3)                                /*!< 6-bit ADC resolution */

/* oversampling shift */
#define OVSAMPCTL_OVSS(regval)                 (BITS(5, 8) & ((uint32_t)(regval) << 5))    /*!< write value to ADC_OVSAMPCTL_OVSS bit field */
#define ADC_OVERSAMPLING_SHIFT_NONE            OVSAMPCTL_OVSS(0)                           /*!< no oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_1B              OVSAMPCTL_OVSS(1)                           /*!< 1-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_2B              OVSAMPCTL_OVSS(2)                           /*!< 2-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_3B              OVSAMPCTL_OVSS(3)                           /*!< 3-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_4B              OVSAMPCTL_OVSS(4)                           /*!< 4-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_5B              OVSAMPCTL_OVSS(5)                           /*!< 5-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_6B              OVSAMPCTL_OVSS(6)                           /*!< 6-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_7B              OVSAMPCTL_OVSS(7)                           /*!< 7-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_8B              OVSAMPCTL_OVSS(8)                           /*!< 8-bit oversampling shift */

/* oversampling ratio */
#define OVSAMPCTL_OVSR(regval)                 (BITS(2, 4) & ((uint32_t)(regval) << 2))    /*!< write value to ADC_OVSAMPCTL_OVSR bit field */
#define ADC_OVERSAMPLING_RATIO_MUL2            OVSAMPCTL_OVSR(0)                           /*!< oversampling ratio multiple 2 */
#define ADC_OVERSAMPLING_RATIO_MUL4            OVSAMPCTL_OVSR(1)                           /*!< oversampling ratio multiple 4 */
#define ADC_OVERSAMPLING_RATIO_MUL8            OVSAMPCTL_OVSR(2)                           /*!< oversampling ratio multiple 8 */
#define ADC_OVERSAMPLING_RATIO_MUL16           OVSAMPCTL_OVSR(3)                           /*!< oversampling ratio multiple 16 */
#define ADC_OVERSAMPLING_RATIO_MUL32           OVSAMPCTL_OVSR(4)                           /*!< oversampling ratio multiple 32 */
#define ADC_OVERSAMPLING_RATIO_MUL64           OVSAMPCTL_OVSR(5)                           /*!< oversampling ratio multiple 64 */
#define ADC_OVERSAMPLING_RATIO_MUL128          OVSAMPCTL_OVSR(6)                           /*!< oversampling ratio multiple 128 */
#define ADC_OVERSAMPLING_RATIO_MUL256          OVSAMPCTL_OVSR(7)                           /*!< oversampling ratio multiple 256 */

/* triggered oversampling */
#define ADC_OVERSAMPLING_ALL_CONVERT           ((uint32_t)0x00000000U)                     /*!< all oversampled conversions for a channel are done consecutively after a trigger */
#define ADC_OVERSAMPLING_ONE_CONVERT           ADC_OVSAMPCTL_TOVS                          /*!< each oversampled conversion for a channel needs a trigger */

/* ADC channel sequence definitions */
#define ADC_ROUTINE_CHANNEL                    ((uint8_t)0x01U)                            /*!< ADC routine sequence */
#define ADC_INSERTED_CHANNEL                   ((uint8_t)0x02U)                            /*!< ADC inserted sequence */
#define ADC_ROUTINE_INSERTED_CHANNEL           ((uint8_t)0x03U)                            /*!< both routine and inserted sequence */
#define ADC_CHANNEL_DISCON_DISABLE             ((uint8_t)0x04U)                            /*!< disable discontinuous mode of routine & inserted sequence */

/* ADC inserted channel definitions */
#define ADC_INSERTED_CHANNEL_0                 ((uint8_t)0x00U)                            /*!< ADC inserted channel 0 */
#define ADC_INSERTED_CHANNEL_1                 ((uint8_t)0x01U)                            /*!< ADC inserted channel 1 */
#define ADC_INSERTED_CHANNEL_2                 ((uint8_t)0x02U)                            /*!< ADC inserted channel 2 */
#define ADC_INSERTED_CHANNEL_3                 ((uint8_t)0x03U)                            /*!< ADC inserted channel 3 */

/* ADC channel definitions */
#define ADC_CHANNEL_0                          ((uint8_t)0x00U)                            /*!< ADC channel 0 */
#define ADC_CHANNEL_1                          ((uint8_t)0x01U)                            /*!< ADC channel 1 */
#define ADC_CHANNEL_2                          ((uint8_t)0x02U)                            /*!< ADC channel 2 */
#define ADC_CHANNEL_3                          ((uint8_t)0x03U)                            /*!< ADC channel 3 */
#define ADC_CHANNEL_4                          ((uint8_t)0x04U)                            /*!< ADC channel 4 */
#define ADC_CHANNEL_5                          ((uint8_t)0x05U)                            /*!< ADC channel 5 */
#define ADC_CHANNEL_6                          ((uint8_t)0x06U)                            /*!< ADC channel 6 */
#define ADC_CHANNEL_7                          ((uint8_t)0x07U)                            /*!< ADC channel 7 */
#define ADC_CHANNEL_8                          ((uint8_t)0x08U)                            /*!< ADC channel 8 */
#define ADC_CHANNEL_9                          ((uint8_t)0x09U)                            /*!< ADC channel 9 */
#define ADC_CHANNEL_10                         ((uint8_t)0x0AU)                            /*!< ADC channel 10 */
#define ADC_CHANNEL_11                         ((uint8_t)0x0BU)                            /*!< ADC channel 11 */
#define ADC_CHANNEL_12                         ((uint8_t)0x0CU)                            /*!< ADC channel 12 */
#define ADC_CHANNEL_13                         ((uint8_t)0x0DU)                            /*!< ADC channel 13 */
#define ADC_CHANNEL_14                         ((uint8_t)0x0EU)                            /*!< ADC channel 14 */
#define ADC_CHANNEL_15                         ((uint8_t)0x0FU)                            /*!< ADC channel 15 */
#define ADC_CHANNEL_16                         ((uint8_t)0x10U)                            /*!< ADC channel 16 */
#define ADC_CHANNEL_17                         ((uint8_t)0x11U)                            /*!< ADC channel 17 */
#define ADC_CHANNEL_18                         ((uint8_t)0x12U)                            /*!< ADC channel 18 */
#define ADC_CHANNEL_19                         ((uint8_t)0x13U)                            /*!< ADC channel 19 */

#ifdef GD32L235
    /* Differential mode for channel n(n=0..14) */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_0    ((uint32_t)0x00000001U)                     /*!< ADC channel 0 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_1    ((uint32_t)0x00000002U)                     /*!< ADC channel 1 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_2    ((uint32_t)0x00000004U)                     /*!< ADC channel 2 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_3    ((uint32_t)0x00000008U)                     /*!< ADC channel 3 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_4    ((uint32_t)0x00000010U)                     /*!< ADC channel 4 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_5    ((uint32_t)0x00000020U)                     /*!< ADC channel 5 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_6    ((uint32_t)0x00000040U)                     /*!< ADC channel 6 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_7    ((uint32_t)0x00000080U)                     /*!< ADC channel 7 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_8    ((uint32_t)0x00000100U)                     /*!< ADC channel 8 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_9    ((uint32_t)0x00000200U)                     /*!< ADC channel 9 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_10   ((uint32_t)0x00000400U)                     /*!< ADC channel 10 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_11   ((uint32_t)0x00000800U)                     /*!< ADC channel 11 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_12   ((uint32_t)0x00001000U)                     /*!< ADC channel 12 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_13   ((uint32_t)0x00002000U)                     /*!< ADC channel 13 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_14   ((uint32_t)0x00004000U)                     /*!< ADC channel 14 differential mode */
    #define ADC_DIFFERENTIAL_MODE_CHANNEL_ALL  ((uint32_t)0x00007FFFU)                     /*!< all ADC channeln(n=0..14) differential mode */
#endif

/* ADC interrupt definitions */
#define ADC_INT_WDE                            ADC_STAT_WDE                                /*!< analog watchdog event interrupt */
#define ADC_INT_EOC                            ADC_STAT_EOC                                /*!< end of sequence conversion interrupt */
#define ADC_INT_EOIC                           ADC_STAT_EOIC                               /*!< end of inserted sequence conversion interrupt */

/* ADC interrupt flag */
#define ADC_INT_FLAG_WDE                       ADC_STAT_WDE                                /*!< analog watchdog event interrupt */
#define ADC_INT_FLAG_EOC                       ADC_STAT_EOC                                /*!< end of sequence conversion interrupt */
#define ADC_INT_FLAG_EOIC                      ADC_STAT_EOIC                               /*!< end of inserted sequence conversion interrupt */

/* function declarations */
/* ADC deinitialization and initialization functions */
/* reset ADC */
void adc_deinit(void);
/* enable ADC interface */
void adc_enable(void);
/* disable ADC interface */
void adc_disable(void);

/* ADC calibration and DMA functions */
#ifdef GD32L235
    /* configure ADC calibration number */
    void adc_calibration_number(uint32_t clb_num);
#endif
/* ADC calibration and reset calibration */
void adc_calibration_enable(void);
/* enable DMA request */
void adc_dma_mode_enable(void);
/* disable DMA request */
void adc_dma_mode_disable(void);

/* ADC special function functions */
/* configure ADC discontinuous mode */
void adc_discontinuous_mode_config(uint8_t adc_sequence, uint8_t length);
/* configure ADC special function */
void adc_special_function_config(uint32_t function, ControlStatus newvalue);
/* configure temperature sensor, internal reference voltage channel, VBAT channel or VSLCD channel */
void adc_channel_16_to_19(uint32_t function, ControlStatus newvalue);

/* ADC channel configuration functions */
/* configure ADC data alignment */
void adc_data_alignment_config(uint32_t data_alignment);
/* configure the channel length of routine sequence or inserted sequence */
void adc_channel_length_config(uint8_t adc_sequence, uint32_t length);
/* configure ADC routine channel */
void adc_routine_channel_config(uint8_t rank, uint8_t adc_channel, uint32_t sample_time);
/* configure ADC inserted channel */
void adc_inserted_channel_config(uint8_t rank, uint8_t adc_channel, uint32_t sample_time);
/* configure ADC inserted channel offset */
void adc_inserted_channel_offset_config(uint8_t inserted_channel, uint16_t offset);
#ifdef GD32L235
    /* configure differential mode for ADC channel */
    void adc_channel_differential_mode_config(uint32_t adc_channel, ControlStatus newvalue);
#endif

/* ADC external trigger functions */
/* configure ADC external trigger */
void adc_external_trigger_config(uint8_t adc_sequence, ControlStatus newvalue);
/* configure ADC external trigger source */
void adc_external_trigger_source_config(uint8_t adc_sequence, uint32_t external_trigger_source);
/* enable ADC software trigger */
void adc_software_trigger_enable(uint8_t adc_sequence);

/* ADC data read functions */
/* read ADC routine sequence data register */
uint16_t adc_routine_data_read(void);
/* read ADC inserted sequence data register */
uint16_t adc_inserted_data_read(uint8_t inserted_channel);

/* ADC analog watchdog functions */
/* enable ADC analog watchdog single channel */
void adc_watchdog_single_channel_enable(uint8_t adc_channel);
/* enable ADC analog watchdog sequence channel */
void adc_watchdog_sequence_channel_enable(uint8_t adc_sequence);
/* disable ADC analog watchdog */
void adc_watchdog_disable(void);
/* configure ADC analog watchdog threshold */
void adc_watchdog_threshold_config(uint16_t low_threshold, uint16_t high_threshold);

/* ADC resolution and oversample functions */
/* configure ADC resolution */
void adc_resolution_config(uint32_t resolution);
/* configure ADC oversample mode */
void adc_oversample_mode_config(uint32_t mode, uint16_t shift, uint8_t ratio);
/* enable ADC oversample mode */
void adc_oversample_mode_enable(void);
/* disable ADC oversample mode */
void adc_oversample_mode_disable(void);

/* ADC charge control functions */
/* configure ADC charge pulse width counter */
void adc_charge_pulse_width_counter(uint32_t value);
/* get the ADC charge flag */
FlagStatus adc_charge_flag_get(uint32_t flag);

/* flag and interrupt functions */
/* get ADC flag */
FlagStatus adc_flag_get(uint32_t flag);
/* clear ADC flag */
void adc_flag_clear(uint32_t flag);
/* enable ADC interrupt */
void adc_interrupt_enable(uint32_t interrupt);
/* disable ADC interrupt */
void adc_interrupt_disable(uint32_t interrupt);
/* get ADC interrupt flag */
FlagStatus adc_interrupt_flag_get(uint32_t int_flag);
/* clear ADC interrupt flag */
void adc_interrupt_flag_clear(uint32_t int_flag);

#endif /* GD32L23X_ADC_H */
