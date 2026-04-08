/*!
    \file    gd32m53x_Cctimer.h
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

#ifndef GD32M53X_CPTIMERW_H
#define GD32M53X_CPTIMERW_H

#include "gd32m53x.h"

/* CPTIMERW definitions */
#define CPTIMERW                                    CPTIMERW_BASE


/* registers definitions */
#define CPTIMERW_CTL0                               REG32((CPTIMERW) + 0x00U)            /*!< CPTIMERW control register 0 */
#define CPTIMERW_CTL1                               REG32((CPTIMERW) + 0x04U)            /*!< CPTIMERW control register 1 */
#define CPTIMERW_PSC                                REG32((CPTIMERW) + 0x08U)            /*!< CPTIMERW prescaler register */
#define CPTIMERW_CNT                                REG32((CPTIMERW) + 0x0CU)            /*!< CPTIMERW counter register */
#define CPTIMERW_INTEN                              REG32((CPTIMERW) + 0x10U)            /*!< CPTIMERW interrupt enable register */
#define CPTIMERW_INTF                               REG32((CPTIMERW) + 0x14U)            /*!< CPTIMERW interrupt flag register */
#define CPTIMERW_SWEVG                              REG32((CPTIMERW) + 0x18U)            /*!< CPTIMERW software event generate register */
#define CPTIMERW_ICH0CV                             REG32((CPTIMERW) + 0x1CU)            /*!< CPTIMERW intput capture channel 0 capture value register */
#define CPTIMERW_ICH1CV                             REG32((CPTIMERW) + 0x20U)            /*!< CPTIMERW intput capture channel 1 capture value register */
#define CPTIMERW_OCH0CV                             REG32((CPTIMERW) + 0x24U)            /*!< CPTIMERW output compare channel 0 compare value register */
#define CPTIMERW_OCH1CV                             REG32((CPTIMERW) + 0x28U)            /*!< CPTIMERW output compare channel 1 compare value register */
#define CPTIMERW_OCH2CV                             REG32((CPTIMERW) + 0x2CU)            /*!< CPTIMERW output compare channel 2 compare value register */
#define CPTIMERW_OCH3CV                             REG32((CPTIMERW) + 0x30U)            /*!< CPTIMERW output compare channel 3 compare value register */
#define CPTIMERW_CAR                                REG32((CPTIMERW) + 0x34U)            /*!< CPTIMERW counter auto reload register */

/* CPTIMERW_CTL0 */
#define CPTIMERW_CTL0_CEN                           BIT(0)                               /*!< CPTIMERW counter enable */
#define CPTIMERW_CTL0_CNTWSEL                       BIT(11)                              /*!< counter width slection */
#define CPTIMERW_CTL0_CLRSSEL                       BITS(12,13)                          /*!< counter clear source selection */
#define CPTIMERW_CTL0_CKDIV                         BITS(14,15)                          /*!< intput capture channel 1 clock division */

/* CPTIMERW_CTL1 */
#define CPTIMERW_CTL1_ICH0ES                        BITS(0,1)                            /*!< intput capture channel 0 edge select */
#define CPTIMERW_CTL1_ICH1ES                        BITS(2,3)                            /*!< intput capture channel 1 edge select */
#define CPTIMERW_CTL1_ICH0EN                        BIT(4)                               /*!< intput capture channel 0 enable */
#define CPTIMERW_CTL1_ICH1EN                        BIT(5)                               /*!< intput capture channel 1 enable */
#define CPTIMERW_CTL1_OCH0MS                        BITS(6,7)                            /*!< output compare channel 0 output mode */
#define CPTIMERW_CTL1_OCH1MS                        BITS(8,9)                            /*!< output compare channel 1 output mode */
#define CPTIMERW_CTL1_OCH0EN                        BIT(10)                              /*!< output compare channel 0 enable */
#define CPTIMERW_CTL1_OCH1EN                        BIT(11)                              /*!< output compare channel 1 enable */
#define CPTIMERW_CTL1_OCH2EN                        BIT(12)                              /*!< output compare channel 2 enable  */
#define CPTIMERW_CTL1_OCH3EN                        BIT(13)                              /*!< output compare channel 3 enable  */
#define CPTIMERW_CTL1_ICH0FLT                       BITS(16,19)                          /*!< intput capture channel 0 filter control */
#define CPTIMERW_CTL1_ICH1FLT                       BITS(22,25)                          /*!< intput capture channel 1 filter control */

/* CPTIMERW_INTEN */
#define CPTIMERW_INTEN_ICH0IE                       BIT(0)                               /*!< intput capture channel 0 interrupt flag */
#define CPTIMERW_INTEN_ICH1IE                       BIT(1)                               /*!< intput capture channel 1 interrupt flag */
#define CPTIMERW_INTEN_OCH0IE                       BIT(2)                               /*!< output compare channel 0 interrupt flag */
#define CPTIMERW_INTEN_OCH1IE                       BIT(3)                               /*!< output compare channel 1 interrupt flag */
#define CPTIMERW_INTEN_OCH2IE                       BIT(4)                               /*!< output compare channel 2 interrupt flag */
#define CPTIMERW_INTEN_OCH3IE                       BIT(5)                               /*!< output compare channel 3 interrupt flag */
#define CPTIMERW_INTEN_UPIE                         BIT(6)                               /*!< update interrupt flag */

/* CPTIMERW_INTF */
#define CPTIMERW_INTF_ICH0IF                        BIT(0)                               /*!< intput capture channel 0 interrupt flag */
#define CPTIMERW_INTF_ICH1IF                        BIT(1)                               /*!< intput capture channel 1 interrupt flag */
#define CPTIMERW_INTF_OCH0IF                        BIT(2)                               /*!< output compare channel 0 interrupt flag */
#define CPTIMERW_INTF_OCH1IF                        BIT(3)                               /*!< output compare channel 1 interrupt flag */
#define CPTIMERW_INTF_OCH2IF                        BIT(4)                               /*!< output compare channel 2 interrupt flag */
#define CPTIMERW_INTF_OCH3IF                        BIT(5)                               /*!< output compare channel 3 interrupt flag */
#define CPTIMERW_INTF_UPIF                          BIT(6)                               /*!< update interrupt flag */

/* CPTIMERW_SWEVG */
#define CPTIMERW_SWEVG_UPG                          BIT(0)                               /*!< update software event generate */

/* constants definitions */
/* CPTIMER init parameter struct definitions */
typedef struct {
    uint32_t width;                                                                      /*!< counter bit width */
    uint32_t prescaler;                                                                  /*!< counter prescaler value */
    uint32_t period;                                                                     /*!< counter autoreload value */
    uint32_t clear_source;                                                               /*!< counter clear source */
    uint32_t clockdivision;                                                              /*!< input capture clock division value */
} cptimerw_init_parameter_struct;

/* channel input parameter struct definitions */
typedef struct {
    uint32_t icedge;                                                                     /*!< channel input edge */
    uint8_t icfilter;                                                                    /*!< channel input capture filter control */
} cptimerw_ic_parameter_struct;

/* counter bit width */
#define CTL0_CNTWSEL(regval)                        (BIT(11) & ((uint32_t)(regval) << 11U))
#define CPTIMERW_CNT_WIDTH_16BIT                    CTL0_CNTWSEL(1)                      /*!< counter width is 16 bits */
#define CPTIMERW_CNT_WIDTH_32BIT                    CTL0_CNTWSEL(0)                      /*!< counter width is 32 bits */

/* counter clear source */
#define CTL0_CLRSSEL(regval)                        (BITS(12, 13) & ((uint32_t)(regval) << 12U))
#define CPTIMERW_CNT_CLEAR_DISABLE                  CTL0_CLRSSEL(0)                      /*!< counter clear disable */
#define CPTIMERW_CNT_CLEAR_ICH0                     CTL0_CLRSSEL(1)                      /*!< counter clear at intput capture channel 0 event */
#define CPTIMERW_CNT_CLEAR_ICH1                     CTL0_CLRSSEL(2)                      /*!< counter clear at intput capture channel 1 event */

/* ouput compare channel */
#define CPTIMERW_OCH0                               ((uint16_t)0x0000U)                  /*!< cptimerw output compare channel 0 */
#define CPTIMERW_OCH1                               ((uint16_t)0x0001U)                  /*!< cptimerw output compare channel 1 */
#define CPTIMERW_OCH2                               ((uint16_t)0x0002U)                  /*!< cptimerw output compare channel 2 */
#define CPTIMERW_OCH3                               ((uint16_t)0x0003U)                  /*!< cptimerw output compare channel 3 */

/* ouput compare channel output mode */
#define CTL1_OCH0MS(regval)                         (BITS(6, 7) & ((uint32_t)(regval) << 6U))
#define CPTIMERW_OC_MODE_MANTAIN                    CTL1_OCH0MS(0)                       /*!< output level mantain */
#define CPTIMERW_OC_MODE_LOW_TOGGLE                 CTL1_OCH0MS(1)                       /*!< initial level is low and toggle on compare match */
#define CPTIMERW_OC_MODE_HIGH_TOGGLE                CTL1_OCH0MS(2)                       /*!< initial level is high and toggle on compare match */
#define CPTIMERW_OC_MODE_DISABLE                    CTL1_OCH0MS(3)                       /*!< output disable */

/* ouput compare channel enable state */
#define CPTIMERW_OCX_ENABLE                         ((uint16_t)0x0001U)                  /*!< ouput compare channel enable */
#define CPTIMERW_OCX_DISABLE                        ((uint16_t)0x0000U)                  /*!< ouput compare channel disable */

/* input capture channel */
#define CPTIMERW_ICH0                               ((uint16_t)0x0000U)                  /*!< cptimerw intput capture channel 0 */
#define CPTIMERW_ICH1                               ((uint16_t)0x0001U)                  /*!< cptimerw intput capture channel 1 */

/* input capture sample clock division */
#define CTL0_CLOCK_DIV(regval)                      (BITS(14, 15) & ((uint32_t)(regval) << 14U))
#define CPTIMERW_CKDIV_DIV1                         CTL0_CLOCK_DIV(0)                    /*!< clock division value is 1, fICSCK=fCK_CPTIMERW */
#define CPTIMERW_CKDIV_DIV2                         CTL0_CLOCK_DIV(1)                    /*!< clock division value is 2, fICSCK=fCK_CPTIMERW/2 */
#define CPTIMERW_CKDIV_DIV4                         CTL0_CLOCK_DIV(2)                    /*!< clock division value is 4, fICSCK=fCK_CPTIMERW/4 */

/* intput capture edge */
#define CTL1_ICH0ES(regval)                         (BITS(0, 1) & ((uint32_t)(regval) << 0U))
#define CPTIMERW_IC_RISING_EDGE                     CTL1_ICH0ES(0)                       /*!< intput capture rising edge */
#define CPTIMERW_IC_FALLING_EDGE                    CTL1_ICH0ES(1)                       /*!< intput capture falling edge */
#define CPTIMERW_IC_BOTH_EDGE                       CTL1_ICH0ES(2)                       /*!< intput capture both edge */
#define CPTIMERW_IC_DISABLE                         CTL1_ICH0ES(3)                       /*!< intput capture disable */

/* intput capture channel enable state */
#define CPTIMERW_ICX_ENABLE                         ((uint16_t)0x0001U)                  /*!< intput capture channel enable */
#define CPTIMERW_ICX_DISABLE                        ((uint16_t)0x0000U)                  /*!< intput capture channel disable */

/* CPTIMERW interrupt enable or disable */
#define CPTIMERW_INT_UP                             CPTIMERW_INTEN_UPIE                  /*!< update interrupt */
#define CPTIMERW_INT_ICH0                           CPTIMERW_INTEN_ICH0IE                /*!< intput capture channel 0 interrupt */
#define CPTIMERW_INT_ICH1                           CPTIMERW_INTEN_ICH1IE                /*!< intput capture channel 1 interrupt */
#define CPTIMERW_INT_OCH0                           CPTIMERW_INTEN_OCH0IE                /*!< output compare channel 0 interrupt */
#define CPTIMERW_INT_OCH1                           CPTIMERW_INTEN_OCH1IE                /*!< output compare channel 1 interrupt */
#define CPTIMERW_INT_OCH2                           CPTIMERW_INTEN_OCH2IE                /*!< output compare channel 2 interrupt */
#define CPTIMERW_INT_OCH3                           CPTIMERW_INTEN_OCH3IE                /*!< output compare channel 3 interrupt */

/* CPTIMERW interrupt flag */
#define CPTIMERW_INT_FLAG_UP                        CPTIMERW_INTF_UPIF                   /*!< update interrupt flag */
#define CPTIMERW_INT_FLAG_ICH0                      CPTIMERW_INTF_ICH0IF                 /*!< intput capture channel 0 interrupt flag */
#define CPTIMERW_INT_FLAG_ICH1                      CPTIMERW_INTF_ICH1IF                 /*!< intput capture channel 1 interrupt flag */
#define CPTIMERW_INT_FLAG_OCH0                      CPTIMERW_INTF_OCH0IF                 /*!< output compare channel 0 interrupt flag */
#define CPTIMERW_INT_FLAG_OCH1                      CPTIMERW_INTF_OCH1IF                 /*!< output compare channel 1 interrupt flag */
#define CPTIMERW_INT_FLAG_OCH2                      CPTIMERW_INTF_OCH2IF                 /*!< output compare channel 2 interrupt flag */
#define CPTIMERW_INT_FLAG_OCH3                      CPTIMERW_INTF_OCH3IF                 /*!< output compare channel 3 interrupt flag */

/* CPTIMERW flag */
#define CPTIMERW_FLAG_UP                            CPTIMERW_INTF_UPIF                   /*!< update flag */
#define CPTIMERW_FLAG_ICH0                          CPTIMERW_INTF_ICH0IF                 /*!< intput capture channel 0 capture flag */
#define CPTIMERW_FLAG_ICH1                          CPTIMERW_INTF_ICH1IF                 /*!< intput capture channel 1 capture flag */
#define CPTIMERW_FLAG_OCH0                          CPTIMERW_INTF_OCH0IF                 /*!< output compare channel 0 match flag */
#define CPTIMERW_FLAG_OCH1                          CPTIMERW_INTF_OCH1IF                 /*!< output compare channel 1 match flag */
#define CPTIMERW_FLAG_OCH2                          CPTIMERW_INTF_OCH2IF                 /*!< output compare channel 2 match flag */
#define CPTIMERW_FLAG_OCH3                          CPTIMERW_INTF_OCH3IF                 /*!< output compare channel 3 match flag */

/* CPTIMERW software event generation source */
#define CPTIMERW_EVENT_SRC_UPG                      CPTIMERW_SWEVG_UPG                   /*!< update event generation */


/* function declarations */
/* CPTIMERW timebase */
/* deinit a CPTIMERW */
void cptimerw_deinit(void);
/* initialize CPTIMERW init parameter struct */
void cptimerw_struct_para_init(cptimerw_init_parameter_struct *initpara);
/* initialize CPTIMERW counter */
void cptimerw_init(cptimerw_init_parameter_struct *initpara);
/* configure CPTIMERW autoreload register value */
void cptimerw_autoreload_value_config(uint32_t autoreload);
/* configure CPTIMERW prescaler */
void cptimerw_prescaler_config(uint16_t prescaler);
/* configure CPTIMERW counter value */
void cptimerw_counter_value_config(uint32_t value);
/* configure CPTIMERW counter clear source */
void cptimerw_counter_clear_source_config(uint32_t clear_source);
/* read CPTIMERW counter value */
uint32_t cptimerw_counter_read(void);
/* read CPTIMERW prescaler value */
uint16_t cptimerw_prescaler_read(void);
/* enable CPTIMERW */
void cptimerw_enable(void);
/* disable CPTIMERW */
void cptimerw_disable(void);

/* CPTIMERW channel output compare config */
/* select CPTIMERW channel output compare mode */
void cptimerw_channel_output_mode_select(uint32_t channel, uint32_t mode);
/* configure CPTIMERW channel output compare value */
void cptimerw_channel_output_compare_value_config(uint32_t channel, uint32_t ochcv);
/* configure CPTIMERW output compare channel enable state */
void cptimerw_channel_output_state_config(uint32_t channel, uint32_t state);

/* CPTIMERW input capture config */
/* initialize CPTIMERW channel input capture parameter struct */
void cptimerw_channel_input_struct_para_init(cptimerw_ic_parameter_struct *icpara);
/* configure CPTIMERW input capture parameter */
void cptimerw_input_capture_config(uint16_t channel, cptimerw_ic_parameter_struct *icpara);
/* read CPTIMERW channel input capture value */
uint32_t cptimerw_channel_capture_value_register_read(uint16_t channel);

/* software generate events */
void cptimerw_event_software_generate(uint32_t event);

/* CPTIMERW interrupt and flag */
/* get CPTIMERW flags */
FlagStatus cptimerw_flag_get(uint32_t flag);
/* clear CPTIMERW flags */
void cptimerw_flag_clear(uint32_t flag);
/* enable CPTIMERW interrupt */
void cptimerw_interrupt_enable(uint32_t interrupt);
/* disable CPTIMERW interrupt */
void cptimerw_interrupt_disable(uint32_t interrupt);
/* get CPTIMERW interrupt flag */
FlagStatus cptimerw_interrupt_flag_get(uint32_t int_flag);
/* clear CPTIMERW interrupt flag */
void cptimerw_interrupt_flag_clear(uint32_t int_flag);

#endif /* GD32M53X_CPTIMERW_H */
