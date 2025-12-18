/*!
    \file    gd32f50x_adc.h
    \brief   definitions for the ADC

    \version 2025-11-03, V1.0.0, firmware for GD32F50x
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

#ifndef GD32F50X_ADC_H
#define GD32F50X_ADC_H

#include "gd32f50x.h"

/* ADC definitions */
#define ADC0                     ADC_BASE                         /*!< ADC0 base address */
#define ADC1                     (ADC_BASE + 0x00000400U)         /*!< ADC1 base address */
#define ADC2                     (ADC_BASE + 0x00001800U)         /*!< ADC2 base address */

/* registers definitions */
#define ADC_STAT(adcx)           REG32((adcx) + 0x00000000U)       /*!< ADC status register */
#define ADC_CTL0(adcx)           REG32((adcx) + 0x00000004U)       /*!< ADC control register 0 */
#define ADC_CTL1(adcx)           REG32((adcx) + 0x00000008U)       /*!< ADC control register 1 */
#define ADC_SAMPT0(adcx)         REG32((adcx) + 0x0000000CU)       /*!< ADC sample time register 0 */
#define ADC_SAMPT1(adcx)         REG32((adcx) + 0x00000010U)       /*!< ADC sample time register 1 */
#define ADC_IOFF0(adcx)          REG32((adcx) + 0x00000014U)       /*!< ADC inserted channel data offset register 0 */
#define ADC_IOFF1(adcx)          REG32((adcx) + 0x00000018U)       /*!< ADC inserted channel data offset register 1 */
#define ADC_IOFF2(adcx)          REG32((adcx) + 0x0000001CU)       /*!< ADC inserted channel data offset register 2 */
#define ADC_IOFF3(adcx)          REG32((adcx) + 0x00000020U)       /*!< ADC inserted channel data offset register 3 */
#define ADC_WD0HT(adcx)          REG32((adcx) + 0x00000024U)       /*!< ADC watchdog 0 high threshold register */
#define ADC_WD0LT(adcx)          REG32((adcx) + 0x00000028U)       /*!< ADC watchdog 0 low threshold register */
#define ADC_RSQ0(adcx)           REG32((adcx) + 0x0000002CU)       /*!< ADC routine sequence register 0 */
#define ADC_RSQ1(adcx)           REG32((adcx) + 0x00000030U)       /*!< ADC routine sequence register 1 */
#define ADC_RSQ2(adcx)           REG32((adcx) + 0x00000034U)       /*!< ADC routine sequence register 2 */
#define ADC_ISQ(adcx)            REG32((adcx) + 0x00000038U)       /*!< ADC inserted sequence register */
#define ADC_LDATA0(adcx)         REG32((adcx) + 0x0000003CU)       /*!< ADC latch data register 0 */
#define ADC_LDATA1(adcx)         REG32((adcx) + 0x00000040U)       /*!< ADC latch data register 1 */
#define ADC_LDATA2(adcx)         REG32((adcx) + 0x00000044U)       /*!< ADC latch data register 2 */
#define ADC_LDATA3(adcx)         REG32((adcx) + 0x00000048U)       /*!< ADC latch data register 3 */
#define ADC_RDATA(adcx)          REG32((adcx) + 0x0000004CU)       /*!< ADC routine data register */
#define ADC_IDATA(adcx)          REG32((adcx) + 0x00000050U)       /*!< ADC inserted data register */
#define ADC_LDCTL(adcx)          REG32((adcx) + 0x00000054U)       /*!< ADC latch data control register */
#define ADC_OVSAMPCTL(adcx)      REG32((adcx) + 0x00000080U)       /*!< ADC oversample control register */

/* bits definitions */
/* ADC_STAT */
#define ADC_STAT_WD0E            BIT(0)                            /*!< analog watchdog 0 event flag */
#define ADC_STAT_EORC            BIT(1)                            /*!< end flag of routine sequence conversion */
#define ADC_STAT_EOIC            BIT(2)                            /*!< end flag of inserted sequence conversion */
#define ADC_STAT_STIC            BIT(3)                            /*!< start flag of inserted sequence */
#define ADC_STAT_STRC            BIT(4)                            /*!< start flag of routine sequence */

/* ADC_CTL0 */
#define ADC_CTL0_WD0CHSEL        BITS(0,4)                         /*!< analog watchdog 0 channel select */
#define ADC_CTL0_EORCIE          BIT(5)                            /*!< interrupt enable for EORC */
#define ADC_CTL0_WD0EIE          BIT(6)                            /*!< interrupt enable for WD0E */
#define ADC_CTL0_EOICIE          BIT(7)                            /*!< interrupt enable for EOIC */
#define ADC_CTL0_SM              BIT(8)                            /*!< scan mode */
#define ADC_CTL0_WD0SC           BIT(9)                            /*!< when in scan mode, analog watchdog 0 is effective on a single channel */
#define ADC_CTL0_ICA             BIT(10)                           /*!< inserted sequence convert automatically */
#define ADC_CTL0_DISRC           BIT(11)                           /*!< discontinuous mode on routine sequence */
#define ADC_CTL0_DISIC           BIT(12)                           /*!< discontinuous mode on inserted sequence */
#define ADC_CTL0_DISNUM          BITS(13,15)                       /*!< number of conversions in discontinuous mode */
#define ADC_CTL0_SYNCM           BITS(16,19)                       /*!< sync mode selection */
#define ADC_CTL0_IWD0EN          BIT(22)                           /*!< inserted sequence analog watchdog 0 enable */
#define ADC_CTL0_RWD0EN          BIT(23)                           /*!< routine sequence analog watchdog 0 enable */

/* ADC_CTL1 */
#define ADC_CTL1_ADCON           BIT(0)                            /*!< ADC ON */
#define ADC_CTL1_CTN             BIT(1)                            /*!< continuous mode */
#define ADC_CTL1_IDMA            BIT(7)                            /*!< DMA request enable for inserted channel */
#define ADC_CTL1_RDMA            BIT(8)                            /*!< DMA request enable for routine channel */
#define ADC_CTL1_DAL             BIT(11)                           /*!< data alignment */
#define ADC_CTL1_ETMIC           BITS(13,14)                       /*!< external trigger mode for inserted channel */
#define ADC_CTL1_ETMRC           BITS(18,19)                       /*!< external trigger mode for routine channel */
#define ADC_CTL1_SWICST          BIT(21)                           /*!< software start on inserted channel */
#define ADC_CTL1_SWRCST          BIT(22)                           /*!< software start on routine channel */
#define ADC_CTL1_INREFEN         BIT(23)                           /*!< channel 17 (internal reference voltage VREFINT) enable of ADC0 */
#define ADC_CTL1_TSVEN           BIT(24)                           /*!< channel 16 (temperature sensor) enable of ADC0 */

/* ADC_SAMPTx x=0..1 */
#define ADC_SAMPTX_SPTN          BITS(0,2)                         /*!< channel x sample time selection */

/* ADC_IOFFx (x=0..3) */
#define ADC_IOFFX_IOFF           BITS(0,11)                        /*!< data offset for inserted channel x */

/* ADC_WD0HT */
#define ADC_WD0HT_WD0HT          BITS(0,19)                        /*!< high threshold for analog watchdog 0 */

/* ADC_WD0LT */
#define ADC_WD0LT_WD0LT          BITS(0,19)                        /*!< low threshold for analog watchdog 0 */

/* ADC_RSQx */
#define ADC_RSQX_RSQN            BITS(0,4)                         /*!< x conversion in routine sequence */
#define ADC_RSQ0_RL              BITS(20,23)                       /*!< routine sequence length */

/* ADC_ISQ */
#define ADC_ISQ_ISQN             BITS(0,4)                         /*!< x conversion in inserted sequence */
#define ADC_ISQ_IL               BITS(20,21)                       /*!< inserted sequence length */

/* ADC_LDATAx (x=0..3) */
#define ADC_LDATAX_LDATAN        BITS(0,15)                        /*!< inserted or routine number x conversion data */

/* ADC_RDATA */
#define ADC_RDATA_RDATA          BITS(0,15)                        /*!< routine channel data */
#define ADC_RDATA_ADC1RDATA      BITS(16,31)                       /*!< ADC1 routine channel data */

/* ADC_IDATA */
#define ADC_IDATA_IDATA          BITS(0,15)                        /*!< inserted channel data */

/* ADC_LDCTL */
#define ADC_LDCTL_COVSELx        BITS(0,3)                         /*!< the ADC_LDATAx register conversion source selection */
#define ADC_LDCTL_SEQSELx        BIT(7)                            /*!< the ADC_LDATAx register sequence source selection */

/* ADC_OVSAMPCTL */
#define ADC_OVSAMPCTL_OVSEN      BIT(0)                            /*!< oversampler enable */
#define ADC_OVSAMPCTL_OVSR       BITS(2,4)                         /*!< oversampling ratio */
#define ADC_OVSAMPCTL_OVSS       BITS(5,8)                         /*!< oversampling shift */
#define ADC_OVSAMPCTL_TOVS       BIT(9)                            /*!< triggered oversampling */
#define ADC_OVSAMPCTL_DRES       BITS(12,13)                       /*!< ADC resolution */

/* constants definitions */
/* ADC flag definitions */
#define ADC_FLAG_WD0E                                        ADC_STAT_WD0E                     /*!< analog watchdog 0 event flag */
#define ADC_FLAG_EORC                                        ADC_STAT_EORC                     /*!< end of routine sequence conversion flag */
#define ADC_FLAG_EOIC                                        ADC_STAT_EOIC                     /*!< end of inserted sequence conversion flag */
#define ADC_FLAG_STIC                                        ADC_STAT_STIC                     /*!< start of inserted sequence conversion flag */
#define ADC_FLAG_STRC                                        ADC_STAT_STRC                     /*!< start of routine sequence conversion flag */

/* ADC interrupt definitions*/
#define ADC_INT_WD0E                                         ADC_CTL0_WD0EIE                   /*!< analog watchdog 0 event interrupt */
#define ADC_INT_EORC                                         ADC_CTL0_EORCIE                   /*!< end of routine sequence conversion interrupt */
#define ADC_INT_EOIC                                         ADC_CTL0_EOICIE                   /*!< end of inserted sequence conversion interrupt */

/* ADC interrupt flag definitions*/
#define ADC_INT_FLAG_WD0E                                    ADC_STAT_WD0E                     /*!< analog watchdog 0 event interrupt flag */
#define ADC_INT_FLAG_EORC                                    ADC_STAT_EORC                     /*!< end of routine sequence conversion interrupt flag */
#define ADC_INT_FLAG_EOIC                                    ADC_STAT_EOIC                     /*!< end of inserted sequence conversion interrupt flag */

/* ADC special function definitions */
#define ADC_SCAN_MODE                                        ADC_CTL0_SM                       /*!< scan mode */
#define ADC_INSERTED_CHANNEL_AUTO                            ADC_CTL0_ICA                      /*!< inserted channel sequence convert automatically */
#define ADC_CONTINUOUS_MODE                                  ADC_CTL1_CTN                      /*!< continuous mode */

/* number of conversions in discontinuous mode*/
#define CTL0_DISNUM(regval)                                  (BITS(13,15) & ((uint32_t)(regval) << 13))

/* ADC synchronization mode selection */
#define CTL0_SYNCM(regval)                                   (BITS(16,19) & ((uint32_t)(regval) << 16))
#define ADC_MODE_FREE                                        CTL0_SYNCM(0)                     /*!< free mode */
#define ADC_DAUL_ROUTINE_PARALLEL_INSERTED_PARALLEL          CTL0_SYNCM(1)                     /*!< combined routine parallel + inserted parallel mode */
#define ADC_DAUL_ROUTINE_PARALLEL_INSERTED_ROTATION          CTL0_SYNCM(2)                     /*!< combined routine parallel + inserted trigger rotation mode */
#define ADC_DAUL_INSERTED_PARALLEL_ROUTINE_FOLLOWUP_FAST     CTL0_SYNCM(3)                     /*!< combined inserted parallel + routine follow-up fast mode */
#define ADC_DAUL_INSERTED_PARALLEL_ROUTINE_FOLLOWUP_SLOW     CTL0_SYNCM(4)                     /*!< combined inserted parallel + routine follow-up slow mode */
#define ADC_DAUL_INSERTED_PARALLEL                           CTL0_SYNCM(5)                     /*!< inserted parallel mode */
#define ADC_DAUL_ROUTINE_PARALLEL                            CTL0_SYNCM(6)                     /*!< routine parallel mode */
#define ADC_DAUL_ROUTINE_FOLLOWUP_FAST                       CTL0_SYNCM(7)                     /*!< routine follow-up fast mode */
#define ADC_DAUL_ROUTINE_FOLLOWUP_SLOW                       CTL0_SYNCM(8)                     /*!< routine follow-up slow mode */
#define ADC_DAUL_INSERTED_TRIGGER_ROTATION                   CTL0_SYNCM(9)                     /*!< inserted trigger rotation mode */

/* ADC data alignment */
#define ADC_DATAALIGN_RIGHT                                  ((uint32_t)0x00000000U)           /*!< LSB alignment */
#define ADC_DATAALIGN_LEFT                                   ADC_CTL1_DAL                      /*!< MSB alignment */

/* temperature sensor channel, internal reference voltage channel */
#define ADC_CHANNEL_INTERNAL_TEMPSENSOR                      ADC_CTL1_TSVEN                    /*!< temperature channel */
#define ADC_CHANNEL_INTERNAL_VREFINT                         ADC_CTL1_INREFEN                  /*!< internal vrefint channel */

/* external trigger mode for routine and inserted  channel */
#define EXTERNAL_TRIGGER_DISABLE                             ((uint32_t)0x00000003U)           /*!< external trigger disable */
#define EXTERNAL_TRIGGER_RISING                              ((uint32_t)0x00000001U)           /*!< rising edge of external trigger */

/* sample time */
#define SAMPTX_SPT(regval)                                   (BITS(0,2) & ((uint32_t)(regval) << 0))
#define ADC_SAMPLETIME_1POINT5                               SAMPTX_SPT(0)                     /*!< 1.5 sampling cycles */
#define ADC_SAMPLETIME_7POINT5                               SAMPTX_SPT(1)                     /*!< 7.5 sampling cycles */
#define ADC_SAMPLETIME_13POINT5                              SAMPTX_SPT(2)                     /*!< 13.5 sampling cycles */
#define ADC_SAMPLETIME_28POINT5                              SAMPTX_SPT(3)                     /*!< 28.5 sampling cycles */
#define ADC_SAMPLETIME_41POINT5                              SAMPTX_SPT(4)                     /*!< 41.5 sampling cycles */
#define ADC_SAMPLETIME_55POINT5                              SAMPTX_SPT(5)                     /*!< 55.5 sampling cycles */
#define ADC_SAMPLETIME_71POINT5                              SAMPTX_SPT(6)                     /*!< 71.5 sampling cycles */
#define ADC_SAMPLETIME_239POINT5                             SAMPTX_SPT(7)                     /*!< 239.5 sampling cycles */

/* ADC_IOFFx register value */
#define IOFFX_IOFF(regval)                                   (BITS(0,11) & ((uint32_t)(regval) << 0))

/* ADC_WD0HT register value */
#define WD0HT_WD0HT(regval)                                  (BITS(0,19) & ((uint32_t)(regval) << 0))

/* ADC_WD0LT register value */
#define WD0LT_WD0LT(regval)                                  (BITS(0,19) & ((uint32_t)(regval) << 0))

/* ADC_ISQ0 register value */
#define RSQ0_RL(regval)                                      (BITS(20,23) & ((uint32_t)(regval) << 20))

/* ADC_ISQ register value */
#define ISQ_IL(regval)                                       (BITS(20,21) & ((uint32_t)(regval) << 20))

/* ADC latch data definitions */
#define ADC_LATCH_DATA_0                                     ((uint8_t)0x00U)                  /*!< ADC latch data 0 */
#define ADC_LATCH_DATA_1                                     ((uint8_t)0x01U)                  /*!< ADC latch data 1 */
#define ADC_LATCH_DATA_2                                     ((uint8_t)0x02U)                  /*!< ADC latch data 2 */
#define ADC_LATCH_DATA_3                                     ((uint8_t)0x03U)                  /*!< ADC latch data 3 */

/* ADC resolution */
#define OVSAMPCTL_DRES(regval)                               (BITS(12,13) & ((uint32_t)(regval) << 12))
#define ADC_RESOLUTION_12B                                   OVSAMPCTL_DRES(0)                 /*!< 12-bit ADC resolution */
#define ADC_RESOLUTION_10B                                   OVSAMPCTL_DRES(1)                 /*!< 10-bit ADC resolution */
#define ADC_RESOLUTION_8B                                    OVSAMPCTL_DRES(2)                 /*!< 8-bit ADC resolution */
#define ADC_RESOLUTION_6B                                    OVSAMPCTL_DRES(3)                 /*!< 6-bit ADC resolution */

/* oversampling shift */
#define OVSAMPCTL_OVSS(regval)                               (BITS(5,8) & ((uint32_t)(regval) << 5))
#define ADC_OVERSAMPLING_SHIFT_NONE                          OVSAMPCTL_OVSS(0)                 /*!< no oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_1B                            OVSAMPCTL_OVSS(1)                 /*!< 1-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_2B                            OVSAMPCTL_OVSS(2)                 /*!< 2-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_3B                            OVSAMPCTL_OVSS(3)                 /*!< 3-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_4B                            OVSAMPCTL_OVSS(4)                 /*!< 4-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_5B                            OVSAMPCTL_OVSS(5)                 /*!< 5-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_6B                            OVSAMPCTL_OVSS(6)                 /*!< 6-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_7B                            OVSAMPCTL_OVSS(7)                 /*!< 7-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_8B                            OVSAMPCTL_OVSS(8)                 /*!< 8-bit oversampling shift */

/* oversampling ratio */
#define OVSAMPCTL_OVSR(regval)                               (BITS(2,4) & ((uint32_t)(regval) << 2))
#define ADC_OVERSAMPLING_RATIO_MUL2                          OVSAMPCTL_OVSR(0)                 /*!< oversampling ratio 2X */
#define ADC_OVERSAMPLING_RATIO_MUL4                          OVSAMPCTL_OVSR(1)                 /*!< oversampling ratio 4X */
#define ADC_OVERSAMPLING_RATIO_MUL8                          OVSAMPCTL_OVSR(2)                 /*!< oversampling ratio 8X */
#define ADC_OVERSAMPLING_RATIO_MUL16                         OVSAMPCTL_OVSR(3)                 /*!< oversampling ratio 16X */
#define ADC_OVERSAMPLING_RATIO_MUL32                         OVSAMPCTL_OVSR(4)                 /*!< oversampling ratio 32X */
#define ADC_OVERSAMPLING_RATIO_MUL64                         OVSAMPCTL_OVSR(5)                 /*!< oversampling ratio 64X */
#define ADC_OVERSAMPLING_RATIO_MUL128                        OVSAMPCTL_OVSR(6)                 /*!< oversampling ratio 128X */
#define ADC_OVERSAMPLING_RATIO_MUL256                        OVSAMPCTL_OVSR(7)                 /*!< oversampling ratio 256X */

/* triggered oversampling */
#define ADC_OVERSAMPLING_ALL_CONVERT                         ((uint32_t)0x00000000U)           /*!< all oversampled conversions for a channel are done consecutively after a trigger */
#define ADC_OVERSAMPLING_ONE_CONVERT                         ADC_OVSAMPCTL_TOVS                /*!< each oversampled conversion for a channel needs a trigger */

/* ADC channel sequence definitions */
#define ADC_ROUTINE_CHANNEL                                  ((uint8_t)0x01U)                  /*!< adc routine channel sequence */
#define ADC_INSERTED_CHANNEL                                 ((uint8_t)0x02U)                  /*!< adc inserted channel sequence */
#define ADC_ROUTINE_INSERTED_CHANNEL                         ((uint8_t)0x03U)                  /*!< both routine and inserted channel sequence */
#define ADC_CHANNEL_DISCON_DISABLE                           ((uint8_t)0x04U)                  /*!< disable discontinuous mode of routine & inserted channel */

/* ADC inserted channel definitions */
#define ADC_INSERTED_CHANNEL_0                               ((uint8_t)0x00U)                  /*!< ADC inserted channel 0 */
#define ADC_INSERTED_CHANNEL_1                               ((uint8_t)0x01U)                  /*!< ADC inserted channel 1 */
#define ADC_INSERTED_CHANNEL_2                               ((uint8_t)0x02U)                  /*!< ADC inserted channel 2 */
#define ADC_INSERTED_CHANNEL_3                               ((uint8_t)0x03U)                  /*!< ADC inserted channel 3 */

/* ADC channel definitions */
#define ADC_CHANNEL_0                                        ((uint8_t)0x00U)                  /*!< ADC channel 0 */
#define ADC_CHANNEL_1                                        ((uint8_t)0x01U)                  /*!< ADC channel 1 */
#define ADC_CHANNEL_2                                        ((uint8_t)0x02U)                  /*!< ADC channel 2 */
#define ADC_CHANNEL_3                                        ((uint8_t)0x03U)                  /*!< ADC channel 3 */
#define ADC_CHANNEL_4                                        ((uint8_t)0x04U)                  /*!< ADC channel 4 */
#define ADC_CHANNEL_5                                        ((uint8_t)0x05U)                  /*!< ADC channel 5 */
#define ADC_CHANNEL_6                                        ((uint8_t)0x06U)                  /*!< ADC channel 6 */
#define ADC_CHANNEL_7                                        ((uint8_t)0x07U)                  /*!< ADC channel 7 */
#define ADC_CHANNEL_8                                        ((uint8_t)0x08U)                  /*!< ADC channel 8 */
#define ADC_CHANNEL_9                                        ((uint8_t)0x09U)                  /*!< ADC channel 9 */
#define ADC_CHANNEL_10                                       ((uint8_t)0x0AU)                  /*!< ADC channel 10 */
#define ADC_CHANNEL_11                                       ((uint8_t)0x0BU)                  /*!< ADC channel 11 */
#define ADC_CHANNEL_12                                       ((uint8_t)0x0CU)                  /*!< ADC channel 12 */
#define ADC_CHANNEL_13                                       ((uint8_t)0x0DU)                  /*!< ADC channel 13 */
#define ADC_CHANNEL_14                                       ((uint8_t)0x0EU)                  /*!< ADC channel 14 */
#define ADC_CHANNEL_15                                       ((uint8_t)0x0FU)                  /*!< ADC channel 15 */
#define ADC_CHANNEL_16                                       ((uint8_t)0x10U)                  /*!< ADC channel 16 */
#define ADC_CHANNEL_17                                       ((uint8_t)0x11U)                  /*!< ADC channel 17 */

/* function declarations */
/* ADC deinitialization and initialization functions */
/* reset ADC */
void adc_deinit(uint32_t adc_periph);
/* enable ADC interface */
void adc_enable(uint32_t adc_periph);
/* disable ADC interface */
void adc_disable(uint32_t adc_periph);

/* ADC DMA functions */
/* enable DMA request*/
void adc_dma_mode_enable(uint32_t adc_periph, uint8_t adc_sequence);
/* disable DMA request*/
void adc_dma_mode_disable(uint32_t adc_periph, uint8_t adc_sequence);

/* ADC special function functions */
/* configure ADC discontinuous mode */
void adc_discontinuous_mode_config(uint32_t adc_periph , uint8_t adc_sequence, uint8_t length);
/* configure ADC special function */
void adc_special_function_config(uint32_t adc_periph , uint32_t function, ControlStatus newvalue);
/* enable or disable ADC internal channels */
void adc_internal_channel_config(uint32_t internal_channel, ControlStatus newvalue);

/* ADC synchronization */
/* configure the ADC sync mode */
void adc_sync_mode_config(uint32_t sync_mode);
/* read ADC0 and ADC1 routine sequence data in sync mode */
uint32_t adc_sync_routine_data_read(void);

/* ADC channel configuration functions */
/* configure ADC data alignment */
void adc_data_alignment_config(uint32_t adc_periph , uint32_t data_alignment);
/* configure the channel length of routine sequence or inserted sequence */
void adc_channel_length_config(uint32_t adc_periph , uint8_t adc_sequence, uint32_t length);
/* configure ADC routine channel */
void adc_routine_channel_config(uint32_t adc_periph , uint8_t rank, uint8_t adc_channel, uint32_t sample_time);
/* configure ADC inserted channel */
void adc_inserted_channel_config(uint32_t adc_periph , uint8_t rank, uint8_t adc_channel, uint32_t sample_time);
/* configure ADC inserted channel offset */
void adc_inserted_channel_offset_config(uint32_t adc_periph , uint8_t inserted_channel, uint16_t offset);
/* enable ADC external trigger */
void adc_external_trigger_config(uint32_t adc_periph, uint8_t adc_sequence, uint32_t trigger_mode);
/* enable ADC software trigger */
void adc_software_trigger_enable(uint32_t adc_periph , uint8_t adc_sequence);

/* ADC data read functions */
/* read ADC routine sequence data register */
uint16_t adc_routine_data_read(uint32_t adc_periph);
/* read ADC inserted sequence data register */
uint16_t adc_inserted_data_read(uint32_t adc_periph);
/* read ADC latch data register */
uint16_t adc_latch_data_read(uint32_t adc_periph, uint8_t latch_data);
/* configure ADC latch data source */
void adc_latch_data_source_config(uint32_t adc_periph, uint8_t latch_data, uint8_t adc_sequence, uint8_t rank);

/* ADC analog watchdog functions */
/* enable ADC analog watchdog 0 single channel */
void adc_watchdog0_single_channel_enable(uint32_t adc_periph, uint8_t adc_channel);
/* enable ADC analog watchdog 0 sequence channel */
void adc_watchdog0_sequence_channel_enable(uint32_t adc_periph, uint8_t adc_sequence);
/* disable ADC analog watchdog 0 */
void adc_watchdog0_disable(uint32_t adc_periph);
/* configure ADC analog watchdog 0 threshold */
void adc_watchdog0_threshold_config(uint32_t adc_periph, uint32_t low_threshold, uint32_t high_threshold);

/* ADC resolution and oversample functions */
/* configure ADC resolution */
void adc_resolution_config(uint32_t adc_periph , uint32_t resolution);
/* configure ADC oversample mode */
void adc_oversample_mode_config(uint32_t adc_periph , uint32_t mode , uint16_t shift , uint8_t ratio);
/* enable ADC oversample mode */
void adc_oversample_mode_enable(uint32_t adc_periph);
/* disable ADC oversample mode */
void adc_oversample_mode_disable(uint32_t adc_periph);

/* flag and interrupt functions */
/* get the ADC flag */
FlagStatus adc_flag_get(uint32_t adc_periph, uint32_t flag);
/* clear the ADC flag */
void adc_flag_clear(uint32_t adc_periph, uint32_t flag);
/* enable ADC interrupt */
void adc_interrupt_enable(uint32_t adc_periph, uint32_t interrupt);
/* disable ADC interrupt */
void adc_interrupt_disable(uint32_t adc_periph, uint32_t interrupt);
/* get the ADC interrupt */
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph, uint32_t int_flag);
/* clear the ADC flag */
void adc_interrupt_flag_clear(uint32_t adc_periph, uint32_t int_flag);

#endif /* gd32f50x_ADC_H */
