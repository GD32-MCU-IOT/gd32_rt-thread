/*!
    \file    GD32M53X_syscfg.h
    \brief   definitions for the SYSCFG

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

#ifndef GD32M53X_SYSCFG_H
#define GD32M53X_SYSCFG_H

#include "gd32m53x.h"

/* SYSCFG definitions */
#define SYSCFG                              SYSCFG_BASE                                     /*!< SYSCFG base address */

/* registers definitions */
#define SYSCFG_CFG0                         REG32(SYSCFG + 0x00000000U)                     /*!< Configuration register 0 */
#define SYSCFG_CFG1                         REG32(SYSCFG + 0x00000004U)                     /*!< Configuration register 1 */
#define SYSCFG_EXTISS0                      REG32(SYSCFG + 0x00000008U)                     /*!< EXTI sources selection register 0 */
#define SYSCFG_EXTISS1                      REG32(SYSCFG + 0x0000000CU)                     /*!< EXTI sources selection register 1 */
#define SYSCFG_EXTISS2                      REG32(SYSCFG + 0x00000010U)                     /*!< EXTI sources selection register 2 */
#define SYSCFG_EXTISS3                      REG32(SYSCFG + 0x00000014U)                     /*!< EXTI sources selection register 3 */
#define SYSCFG_STAT                         REG32(SYSCFG + 0x0000001CU)                     /*!< Status register */
#define SYSCFG_CFG2                         REG32(SYSCFG + 0x00000020U)                     /*!< Configuration register 2 */
#define SYSCFG_CFG3                         REG32(SYSCFG + 0x00000024U)                     /*!< Configuration register 3 */
#define SYSCFG_CFG4                         REG32(SYSCFG + 0x00000028U)                     /*!< Configuration register 4 */
#define SYSCFG_TIMERCISEL0                  REG32(SYSCFG + 0x00000034U)                     /*!< TIMER input selection register 0 */
#define SYSCFG_TIMERCISEL1                  REG32(SYSCFG + 0x00000038U)                     /*!< TIMER input selection register 1 */
#define SYSCFG_CFG5                         REG32(SYSCFG + 0x00000054U)                     /*!< Configuration register 5 */
#define SYSCFG_SRAMCFG                      REG32(SYSCFG + 0x00000068U)                     /*!< SRAM configuration register */
#define SYSCFG_PRCFG                        REG32(SYSCFG + 0x0000006CU)                     /*!< Protect configuration register */
#define SYSCFG_TADSRCFG                     REG32(SYSCFG + 0x00000070U)                     /*!< TIMERx ADC start request configuration register */
#define SYSCFG_TIMER0TRGCFG0                REG32(SYSCFG + 0x00000100U)                     /*!< TIMER0 configuration register 0 */
#define SYSCFG_TIMER0TRGCFG1                REG32(SYSCFG + 0x00000104U)                     /*!< TIMER0 configuration register 1 */
#define SYSCFG_TIMER0TRGCFG2                REG32(SYSCFG + 0x00000108U)                     /*!< TIMER0 configuration register 2 */
#define SYSCFG_TIMER1TRGCFG0                REG32(SYSCFG + 0x0000010CU)                     /*!< TIMER1 configuration register 0 */
#define SYSCFG_TIMER1TRGCFG1                REG32(SYSCFG + 0x00000110U)                     /*!< TIMER1 configuration register 1 */
#define SYSCFG_TIMER1TRGCFG2                REG32(SYSCFG + 0x00000114U)                     /*!< TIMER1 configuration register 2 */
#define SYSCFG_TIMER2TRGCFG0                REG32(SYSCFG + 0x00000118U)                     /*!< TIMER2 configuration register 0 */
#define SYSCFG_TIMER2TRGCFG1                REG32(SYSCFG + 0x0000011CU)                     /*!< TIMER2 configuration register 1 */
#define SYSCFG_TIMER2TRGCFG2                REG32(SYSCFG + 0x00000120U)                     /*!< TIMER2 configuration register 2 */
#define SYSCFG_TIMER7TRGCFG0                REG32(SYSCFG + 0x00000124U)                     /*!< TIMER7 configuration register 0 */
#define SYSCFG_TIMER7TRGCFG1                REG32(SYSCFG + 0x00000128U)                     /*!< TIMER7 configuration register 1 */
#define SYSCFG_TIMER7TRGCFG2                REG32(SYSCFG + 0x0000012CU)                     /*!< TIMER7 configuration register 2 */
#define SYSCFG_CFG6                         REG32(SYSCFG + 0x00000204U)                     /*!< Configuration register 6 */

/* SYSCFG_CFG0 bits definitions */
#define SYSCFG_CFG0_BOOT_MODE               BITS(0,1)                                       /*!< BOOT mode */

/* SYSCFG_CFG1 bits definitions */
#define SYSCFG_CFG1_I2CFMPEN                BIT(0)                                          /*!< I2C fast mode plus enable */

/* SYSCFG_EXTISS0 bits definitions */
#define SYSCFG_EXTISS0_EXTI0_SS             BITS(0,3)                                       /*!< EXTI 0 configuration */
#define SYSCFG_EXTISS0_EXTI1_SS             BITS(4,7)                                       /*!< EXTI 1 configuration */
#define SYSCFG_EXTISS0_EXTI2_SS             BITS(8,11)                                      /*!< EXTI 2 configuration */
#define SYSCFG_EXTISS0_EXTI3_SS             BITS(12,15)                                     /*!< EXTI 3 configuration */

/* SYSCFG_EXTISS1 bits definitions */
#define SYSCFG_EXTISS1_EXTI4_SS             BITS(0,3)                                       /*!< EXTI 4 configuration */
#define SYSCFG_EXTISS1_EXTI5_SS             BITS(4,7)                                       /*!< EXTI 5 configuration */
#define SYSCFG_EXTISS1_EXTI6_SS             BITS(8,11)                                      /*!< EXTI 6 configuration */
#define SYSCFG_EXTISS1_EXTI7_SS             BITS(12,15)                                     /*!< EXTI 7 configuration */

/* SYSCFG_EXTISS2 bits definitions */
#define SYSCFG_EXTISS2_EXTI8_SS             BITS(0,3)                                       /*!< EXTI 8 configuration */
#define SYSCFG_EXTISS2_EXTI9_SS             BITS(4,7)                                       /*!< EXTI 9 configuration */
#define SYSCFG_EXTISS2_EXTI10_SS            BITS(8,11)                                      /*!< EXTI 10 configuration */
#define SYSCFG_EXTISS2_EXTI11_SS            BITS(12,15)                                     /*!< EXTI 11 configuration */

/* SYSCFG_EXTISS3 bits definitions */
#define SYSCFG_EXTISS3_EXTI12_SS            BITS(0,3)                                       /*!< EXTI 12 configuration */
#define SYSCFG_EXTISS3_EXTI13_SS            BITS(4,7)                                       /*!< EXTI 13 configuration */
#define SYSCFG_EXTISS3_EXTI14_SS            BITS(8,11)                                      /*!< EXTI 14 configuration */
#define SYSCFG_EXTISS3_EXTI15_SS            BITS(12,15)                                     /*!< EXTI 15 configuration */

/* SYSCFG_STAT bits definitions */
#define SYSCFG_STAT_ECCMEIF0                BIT(0)                                          /*!< SRAM ECC multi-bit error flag */
#define SYSCFG_STAT_ECCSEIF0                BIT(1)                                          /*!< SRAM ECC single-bit error flag */
#define SYSCFG_STAT_ECCMEIF1                BIT(2)                                          /*!< CAN SRAM ECC multi-bit error flag */
#define SYSCFG_STAT_ECCSEIF1                BIT(3)                                          /*!< CAN SRAM ECC single-bit error flag */
#define SYSCFG_STAT_ECCMEIF2                BIT(4)                                          /*!< CAN filter SRAM ECC multi-bit error flag */
#define SYSCFG_STAT_ECCSEIF2                BIT(5)                                          /*!< CAN filter SRAM ECC single-bit error flag */
#define SYSCFG_STAT_ECCMEIF3                BIT(6)                                          /*!< Flash SRAM ECC multi-bit error flag */
#define SYSCFG_STAT_ECCSEIF3                BIT(7)                                          /*!< Flash SRAM ECC single-bit error flag */
#define SYSCFG_STAT_ECCMEIF4                BIT(8)                                          /*!< Flash ECC multi-bit error flag */
#define SYSCFG_STAT_HXTAL_NMIIF             BIT(26)                                         /*!< HXTAL clock monitor NMI interrupt flag */
#define SYSCFG_STAT_PIN_NMIIF               BIT(27)                                         /*!< Interrupt flag from NMI pin */
#define SYSCFG_STAT_WWDGT_NMIIF             BIT(28)                                         /*!< WWDGT NMI interrupt flag */
#define SYSCFG_STAT_FWDGT_NMIIF             BIT(29)                                         /*!< FWDGT NMI interrupt flag */

/* SYSCFG_CFG2 bits definitions */
#define SYSCFG_CFG2_ECCMEIE0                BIT(0)                                          /*!< SRAM multi-bit non-correction interrupt enable */
#define SYSCFG_CFG2_ECCSEIE0                BIT(1)                                          /*!< SRAM single-bit correction interrupt enable */
#define SYSCFG_CFG2_HXTAL_NMIIE             BIT(3)                                          /*!< HXTAL clock monitor NMI interrupt enable */
#define SYSCFG_CFG2_PIN_NMIIE               BIT(4)                                          /*!< Interrupt flag from NMI pin interrupt enable */
#define SYSCFG_CFG2_WWDGT_NMISEL            BIT(6)                                          /*!< WWDGT NMI interrupt type select */
#define SYSCFG_CFG2_FWDGT_NMISEL            BIT(7)                                          /*!< FWDGT NMI interrupt type select */
#define SYSCFG_CFG2_LVD2_NMIIE              BIT(8)                                          /*!< Low Voltage Detectors2 NMI interrupt enable */
#define SYSCFG_CFG2_LVD1_NMIIE              BIT(9)                                          /*!< Low Voltage Detectors1 NMI interrupt enable */
#define SYSCFG_CFG2_ECCSEBIT                BITS(10,15)                                     /*!< Which one bit has an ECC single-bit correction error */
#define SYSCFG_CFG2_ECCEADDR                BITS(19,31)                                     /*!< Indicates the last ECC event on SRAMC occurred */

/* SYSCFG_CFG3 bits definitions */
#define SYSCFG_CFG3_ECCMEIE1                BIT(0)                                          /*!< CAN receive FIFO SRAM multi-bit non-correction interrupt enable */
#define SYSCFG_CFG3_ECCSEIE1                BIT(1)                                          /*!< CAN receive FIFO SRAM single-bit correction interrupt enable */
#define SYSCFG_CFG3_ECCMEIE2                BIT(2)                                          /*!< CAN filter SRAM multi-bit non-correction interrupt enable */
#define SYSCFG_CFG3_ECCSEIE2                BIT(3)                                          /*!< CAN filter SRAM single-bit correction interrupt enable */

/* SYSCFG_CFG4 bits definitions */
#define SYSCFG_CFG4_ECCMEIE3                BIT(0)                                          /*!< FLASH SRAM multi-bit non-correction interrupt enable */
#define SYSCFG_CFG4_ECCSEIE3                BIT(1)                                          /*!< FLASH SRAM single-bit correction interrupt enable */
#define SYSCFG_CFG4_ECCMEIE4                BIT(2)                                          /*!< FLASH multi-bit non-correction interrupt enable */

/* SYSCFG_TIMERCISEL0 bits definitions */
#define SYSCFG_TIMER7_CI0_SEL               BITS(0,3)                                       /*!< TIMER7_CI0 input selection */
#define SYSCFG_TIMER7_CI1_SEL               BITS(4,7)                                       /*!< TIMER7_CI1 input selection */
#define SYSCFG_TIMER7_CI2_SEL               BITS(8,11)                                      /*!< TIMER7_CI2 input selection */
#define SYSCFG_TIMER7_CI3_SEL               BITS(12,15)                                     /*!< TIMER7_CI3 input selection */
#define SYSCFG_TIMER0_CI0_SEL               BITS(16,19)                                     /*!< TIMER0_CI0 input selection */
#define SYSCFG_TIMER0_CI1_SEL               BITS(20,23)                                     /*!< TIMER0_CI1 input selection */
#define SYSCFG_TIMER0_CI2_SEL               BITS(24,27)                                     /*!< TIMER0_CI2 input selection */
#define SYSCFG_TIMER0_CI3_SEL               BITS(28,31)                                     /*!< TIMER0_CI3 input selection */

/* SYSCFG_TIMERCISEL1 bits definitions */
#define SYSCFG_TIMER2_CI0_SEL               BITS(0,3)                                       /*!< TIMER2_CI0 input selection */
#define SYSCFG_TIMER2_CI1_SEL               BITS(4,7)                                       /*!< TIMER2_CI1 input selection */
#define SYSCFG_TIMER2_CI2_SEL               BITS(8,11)                                      /*!< TIMER2_CI2 input selection */
#define SYSCFG_TIMER2_CI3_SEL               BITS(12,15)                                     /*!< TIMER2_CI3 input selection */
#define SYSCFG_TIMER1_CI0_SEL               BITS(16,19)                                     /*!< TIMER1_CI0 input selection */
#define SYSCFG_TIMER1_CI1_SEL               BITS(20,23)                                     /*!< TIMER1_CI1 input selection */
#define SYSCFG_TIMER1_CI2_SEL               BITS(24,27)                                     /*!< TIMER1_CI2 input selection */
#define SYSCFG_TIMER1_CI3_SEL               BITS(28,31)                                     /*!< TIMER1_CI3 input selection */

/* SYSCFG_CFG5 bits definitions */
#define SYSCFG_CFG5_LOCKUP_LOCK             BIT(0)                                          /*!< CPU lockup (Hardfault) output enable */
#define SYSCFG_CFG5_LVD_LOCK                BIT(1)                                          /*!< Low voltage detector lock */
#define SYSCFG_CFG5_SRAM_LOCK               BIT(2)                                          /*!< SRAM ECC multi-bit error lock */
#define SYSCFG_CFG5_CANRX_LOCK              BIT(3)                                          /*!< CAN receive FIFO ECC multi-bit error lock */
#define SYSCFG_CFG5_CANFILTER_LOCK          BIT(4)                                          /*!< CAN filter ECC multi-bit error lock */
#define SYSCFG_CFG5_FLASHSRAM_LOCK          BIT(5)                                          /*!< Flash SRAM ECC multi-bit error lock */
#define SYSCFG_CFG5_FLASH_LOCK              BIT(6)                                          /*!< Flash ECC multi-bit error lock */

/* SYSCFG_SRAMCFG bits definitions */
#define SYSCFG_SRAMCFG_SRAM_REMAP_SEL       BITS(0,1)                                       /*!< The size of SRAM aliased */

/* SYSCFG_PRCFG bits definitions */
#define SYSCFG_PRCFG_PRCFG0                 BIT(0)                                          /*!< Protect configuration select 0 */
#define SYSCFG_PRCFG_PRCFG1                 BIT(1)                                          /*!< Protect configuration select 1 */
#define SYSCFG_PRCFG_PRCFG2                 BIT(3)                                          /*!< Protect configuration select 2 */
#define SYSCFG_PRCFG_PRKEY                  BITS(8,15)                                      /*!< Protect KEY */

/* SYSCFG_TADSRCFG bits definitions */
#define SYSCFG_TADSRCFG_ADCSM1SEL           BITS(0,3)                                       /*!< Select the ADC trigger source connected to ADCSM1 pin. */
#define SYSCFG_TADSRCFG_ADCSM1EN            BIT(7)                                          /*!< ADCSM1 pin output enable */
#define SYSCFG_TADSRCFG_ADCSM2SEL           BITS(8,11)                                      /*!< Select the ADC trigger source connected to ADCSM2 pin. */
#define SYSCFG_TADSRCFG_ADCSM2EN            BIT(15)                                         /*!< ADCSM2 pin output enable */

/* SYSCFG_TIMERxCFG0(x=0,7/1,2) bits definitions */
#define SYSCFG_TIMERTRGCFG_TSCFG0           BITS(0,4)                                       /*!< Quadrature decoder mode 0 configuration */
#define SYSCFG_TIMERTRGCFG_TSCFG1           BITS(5,9)                                       /*!< Quadrature decoder mode 1 configuration */
#define SYSCFG_TIMERTRGCFG_TSCFG2           BITS(10,14)                                     /*!< Quadrature decoder mode 2 configuration */
#define SYSCFG_TIMERTRGCFG_TSCFG3           BITS(16,20)                                     /*!< Restart mode configuration */
#define SYSCFG_TIMERTRGCFG_TSCFG4           BITS(21,25)                                     /*!< Pause mode configuration */
#define SYSCFG_TIMERTRGCFG_TSCFG5           BITS(26,30)                                     /*!< Event mode configuration */

/* SYSCFG_TIMERxCFG1(x=0,7/1,2) bits definitions */
#define SYSCFG_TIMERTRGCFG_TSCFG6           BITS(0,4)                                       /*!< External clock mode 0 configuration */
#define SYSCFG_TIMERTRGCFG_TSCFG7           BITS(5,9)                                       /*!< Restart + event mode configuration */
#define SYSCFG_TIMERTRGCFG_TSCFG9           BITS(16,20)                                     /*!< Decoder mode 0 configuration */
#define SYSCFG_TIMERTRGCFG_TSCFG10          BITS(21,25)                                     /*!< Decoder mode 1 configuration */
#define SYSCFG_TIMERTRGCFG_TSCFG11          BITS(26,30)                                     /*!< Decoder mode 2 configuration */

/* SYSCFG_TIMERxCFG2(x=0,7/1,2) bits definitions */
#define SYSCFG_TIMERTRGCFG_TSCFG12          BITS(0,4)                                       /*!< Decoder mode 3 configuration */
#define SYSCFG_TIMERTRGCFG_TSCFG15          BITS(16,20)                                     /*!< Internal trigger input source configuration */

/* SYSCFG_CFG6 bits definitions */
#define SYSCFG_CFG6_CK_CMP_SEL              BIT(0)                                          /*!< CK_CMP select */


/* constants definitions */
/* define the SYSCFG_REGIDX_BIT_VAL, include register index offset, bit position and value
*  [31:16] [15:8]  [7:0]
*  regidx  bitpos  value
*/
#define SYSCFG_REGIDX_BIT_VAL(regidx, bitpos, value)    (((uint32_t)(regidx) << 16U) | (uint32_t)((bitpos) << 8U) | ((uint32_t)(value)))
#define SYSCFG_REG_INDEX(val)                           (((uint32_t)(val) & 0xFFFF0000U) >> 16U)
#define SYSCFG_BIT_POS(val)                             (((uint32_t)(val) & 0x00001F00U) >> 8U)
#define SYSCFG_VALUE(val)                               ((uint32_t)(val) & 0x000000FFU)
#define SYSCFG_REG_VAL(offset)                          (REG32(SYSCFG + (((uint32_t)(offset) & 0xFFFF0000U) >> 16U)))

/* register offset */
#define SYSCFG_CFG0_OFFSET              0x00000000U                     /*!< SYSCFG_CFG0          offset */
#define SYSCFG_CFG1_OFFSET              0x00000004U                     /*!< SYSCFG_CFG1          offset */
#define SYSCFG_EXTISS0_OFFSET           0x00000008U                     /*!< SYSCFG_EXTISS0       offset */
#define SYSCFG_EXTISS1_OFFSET           0x0000000CU                     /*!< SYSCFG_EXTISS1       offset */
#define SYSCFG_EXTISS2_OFFSET           0x00000010U                     /*!< SYSCFG_EXTISS2       offset */
#define SYSCFG_EXTISS3_OFFSET           0x00000014U                     /*!< SYSCFG_EXTISS3       offset */
#define SYSCFG_STAT_OFFSET              0x0000001CU                     /*!< SYSCFG_STAT          offset */
#define SYSCFG_CFG2_OFFSET              0x00000020U                     /*!< SYSCFG_CFG2          offset */
#define SYSCFG_CFG3_OFFSET              0x00000024U                     /*!< SYSCFG_CFG3          offset */
#define SYSCFG_CFG4_OFFSET              0x00000028U                     /*!< SYSCFG_CFG4          offset */
#define SYSCFG_TIMERCISEL0_OFFSET       0x00000034U                     /*!< SYSCFG_TIMERCISEL0   offset */
#define SYSCFG_TIMERCISEL1_OFFSET       0x00000038U                     /*!< SYSCFG_TIMERCISEL1   offset */
#define SYSCFG_CFG5_OFFSET              0x00000054U                     /*!< SYSCFG_CFG5          offset */
#define SYSCFG_SRAMCFG_OFFSET           0x00000068U                     /*!< SYSCFG_SRAMCFG       offset */
#define SYSCFG_PRCFG_OFFSET             0x0000006CU                     /*!< SYSCFG_PRCFG         offset */
#define SYSCFG_TADSRCFG_OFFSET          0x00000070U                     /*!< SYSCFG_TADSRCFG      offset */
#define SYSCFG_TIMER0TRGCFG0_OFFSET     0x00000100U                     /*!< SYSCFG_TIMER0TRGCFG0 offset */
#define SYSCFG_TIMER0TRGCFG1_OFFSET     0x00000104U                     /*!< SYSCFG_TIMER0TRGCFG1 offset */
#define SYSCFG_TIMER0TRGCFG2_OFFSET     0x00000108U                     /*!< SYSCFG_TIMER0TRGCFG2 offset */
#define SYSCFG_TIMER1TRGCFG0_OFFSET     0x0000010CU                     /*!< SYSCFG_TIMER1TRGCFG0 offset */
#define SYSCFG_TIMER1TRGCFG1_OFFSET     0x00000110U                     /*!< SYSCFG_TIMER1TRGCFG1 offset */
#define SYSCFG_TIMER1TRGCFG2_OFFSET     0x00000114U                     /*!< SYSCFG_TIMER1TRGCFG2 offset */
#define SYSCFG_TIMER2TRGCFG0_OFFSET     0x00000118U                     /*!< SYSCFG_TIMER2TRGCFG0 offset */
#define SYSCFG_TIMER2TRGCFG1_OFFSET     0x0000011CU                     /*!< SYSCFG_TIMER2TRGCFG1 offset */
#define SYSCFG_TIMER2TRGCFG2_OFFSET     0x00000120U                     /*!< SYSCFG_TIMER2TRGCFG2 offset */
#define SYSCFG_TIMER7TRGCFG0_OFFSET     0x00000124U                     /*!< SYSCFG_TIMER7TRGCFG0 offset */
#define SYSCFG_TIMER7TRGCFG1_OFFSET     0x00000128U                     /*!< SYSCFG_TIMER7TRGCFG1 offset */
#define SYSCFG_TIMER7TRGCFG2_OFFSET     0x0000012CU                     /*!< SYSCFG_TIMER7TRGCFG2 offset */
#define SYSCFG_CFG6_OFFSET              0x00000204U                     /*!< SYSCFG_CFG6          offset */

/* EXTI source GPIO definitions */
typedef enum {
    /* EXTI0_SS */
    EXTI_SOURCE_EXTI0_PA8       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 0, 0U),          /*!< EXTI0 PA8 configuration */
    EXTI_SOURCE_EXTI0_PC10      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 0, 1U),          /*!< EXTI0 PC10 configuration */
    EXTI_SOURCE_EXTI0_PN2       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 0, 2U),          /*!< EXTI0 PN2 configuration */
    EXTI_SOURCE_EXTI0_PC8       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 0, 3U),          /*!< EXTI0 PC8 configuration */
    /* EXTI1_SS */
    EXTI_SOURCE_EXTI1_PA9       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 4, 0U),          /*!< EXTI1 PA9 configuration */
    EXTI_SOURCE_EXTI1_PC11      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 4, 1U),          /*!< EXTI1 PC11 configuration */
    EXTI_SOURCE_EXTI1_PE13      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 4, 2U),          /*!< EXTI1 PE13 configuration */
    EXTI_SOURCE_EXTI1_PC9       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 4, 3U),          /*!< EXTI1 PC9 configuration */
    /* EXTI2_SS */
    EXTI_SOURCE_EXTI2_PA0       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 8, 0U),          /*!< EXTI2 PA0 configuration */
    EXTI_SOURCE_EXTI2_PC12      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 8, 1U),          /*!< EXTI2 PC12 configuration */
    EXTI_SOURCE_EXTI2_PF14      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 8, 2U),          /*!< EXTI2 PF14 configuration */
    EXTI_SOURCE_EXTI2_PG12      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 8, 3U),          /*!< EXTI2 PG12 configuration */
    /* EXTI3_SS */
    EXTI_SOURCE_EXTI3_PF12      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS0_OFFSET, 12, 0U),         /*!< EXTI3 PF12 configuration */
    /* EXTI4_SS */
    EXTI_SOURCE_EXTI4_PA1       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 0, 0U),          /*!< EXTI4 PA1 configuration */
    EXTI_SOURCE_EXTI4_PE14      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 0, 1U),          /*!< EXTI4 PE14 configuration */
    EXTI_SOURCE_EXTI4_PF9       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 0, 2U),          /*!< EXTI4 PF9 configuration */
    EXTI_SOURCE_EXTI4_PF13      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 0, 3U),          /*!< EXTI4 PF13 configuration */
    /* EXTI5_SS */
    EXTI_SOURCE_EXTI5_PD8       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 4, 0U),          /*!< EXTI5 PD8 configuration */
    EXTI_SOURCE_EXTI5_PG14      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 4, 1U),          /*!< EXTI5 PG14 configuration */
    EXTI_SOURCE_EXTI5_PN7       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 4, 2U),          /*!< EXTI5 PN7 configuration */
    /* EXTI6_SS */
    EXTI_SOURCE_EXTI6_PB1       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 8, 0U),          /*!< EXTI6 PB1 configuration */
    EXTI_SOURCE_EXTI6_PC6       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 8, 1U),          /*!< EXTI6 PC6 configuration */
    EXTI_SOURCE_EXTI6_PD2       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 8, 2U),          /*!< EXTI6 PD2 configuration */
    EXTI_SOURCE_EXTI6_PG13      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 8, 3U),          /*!< EXTI6 PG13 configuration */
    /* EXTI7_SS */
    EXTI_SOURCE_EXTI7_PB0       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 12, 0U),         /*!< EXTI7 PB0 configuration */
    EXTI_SOURCE_EXTI7_PC7       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 12, 1U),         /*!< EXTI7 PC7 configuration */
    EXTI_SOURCE_EXTI7_PN5       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS1_OFFSET, 12, 2U),         /*!< EXTI7 PN5 configuration */
    /* EXTI8_SS */
    EXTI_SOURCE_EXTI8_PD4       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 0, 0U),          /*!< EXTI8 PD4 configuration */
    EXTI_SOURCE_EXTI8_PE8       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 0, 1U),          /*!< EXTI8 PE8 configuration */
    EXTI_SOURCE_EXTI8_PF8       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 0, 2U),          /*!< EXTI8 PF8 configuration */
    EXTI_SOURCE_EXTI8_PG15      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 0, 3U),          /*!< EXTI8 PG15 configuration */
    /* EXTI9_SS */
    EXTI_SOURCE_EXTI9_PD5       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 4, 0U),          /*!< EXTI9 PD5 configuration */
    EXTI_SOURCE_EXTI9_PD9       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 4, 1U),          /*!< EXTI9 PD9 configuration */
    EXTI_SOURCE_EXTI9_PE9       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 4, 2U),          /*!< EXTI9 PE9 configuration */
    EXTI_SOURCE_EXTI9_PF11      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 4, 3U),          /*!< EXTI9 PF11 configuration */
    /* EXTI10_SS */
    EXTI_SOURCE_EXTI10_PB2      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 8, 0U),          /*!< EXTI10 PB2 configuration */
    EXTI_SOURCE_EXTI10_PC0      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 8, 1U),          /*!< EXTI10 PC0 configuration */
    EXTI_SOURCE_EXTI10_PD10     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 8, 2U),          /*!< EXTI10 PD10 configuration */
    EXTI_SOURCE_EXTI10_PE10     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 8, 3U),          /*!< EXTI10 PE10 configuration */
    EXTI_SOURCE_EXTI10_PF10     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 8, 4U),          /*!< EXTI10 PF10 configuration */
    /* EXTI11_SS */
    EXTI_SOURCE_EXTI11_PC1      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 12, 0U),         /*!< EXTI11 PC1 configuration */
    EXTI_SOURCE_EXTI11_PD11     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 12, 1U),         /*!< EXTI11 PD11 configuration */
    EXTI_SOURCE_EXTI11_PG11     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS2_OFFSET, 12, 2U),         /*!< EXTI11 PG11 configuration */
    /* EXTI12_SS */
    EXTI_SOURCE_EXTI12_PC2      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS3_OFFSET, 0, 0U),          /*!< EXTI12 PC2 configuration */
    EXTI_SOURCE_EXTI12_PD12     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS3_OFFSET, 0, 1U),          /*!< EXTI12 PD12 configuration */
    EXTI_SOURCE_EXTI12_PE12     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS3_OFFSET, 0, 2U),          /*!< EXTI12 PE12 configuration */
    /* EXTI13_SS */
    EXTI_SOURCE_EXTI13_PC3      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS3_OFFSET, 4, 0U),          /*!< EXTI13 PC3 configuration */
    EXTI_SOURCE_EXTI13_PD13     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS3_OFFSET, 4, 1U),          /*!< EXTI13 PD13 configuration */
    /* EXTI14_SS */
    EXTI_SOURCE_EXTI14_PB14     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS3_OFFSET, 8, 0U),          /*!< EXTI14 PB14 configuration */
    EXTI_SOURCE_EXTI14_PC4      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS3_OFFSET, 8, 1U),          /*!< EXTI14 PC4 configuration */
    EXTI_SOURCE_EXTI14_PD14     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS3_OFFSET, 8, 2U),          /*!< EXTI14 PD14 configuration */
    EXTI_SOURCE_EXTI14_PE11     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS3_OFFSET, 8, 3U),          /*!< EXTI14 PE11 configuration */
    /* EXTI15_SS */
    EXTI_SOURCE_EXTI15_PB15     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS3_OFFSET, 12, 0U),         /*!< EXTI15 PB15 configuration */
    EXTI_SOURCE_EXTI15_PC5      = SYSCFG_REGIDX_BIT_VAL(SYSCFG_EXTISS3_OFFSET, 12, 1U),         /*!< EXTI15 PC5 configuration */
} exti_gpio_enum;

/* peripheral interrupt */
typedef enum {
    /* ECC */
    SYSCFG_INT_ECC_ME0          = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG2_OFFSET, 0, 0U),           /*!< SRAM multi-bit non-correction interrupt enable */
    SYSCFG_INT_ECC_SE0          = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG2_OFFSET, 1, 0U),           /*!< SRAM single-bit correction interrupt enable */
    SYSCFG_INT_ECC_ME1          = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG3_OFFSET, 0, 0U),           /*!< CAN receive FIFO multi-bit non-correction interrupt enable */
    SYSCFG_INT_ECC_SE1          = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG3_OFFSET, 1, 0U),           /*!< CAN receive FIFO single-bit correction interrupt enable */
    SYSCFG_INT_ECC_ME2          = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG3_OFFSET, 2, 0U),           /*!< CAN filter SRAM multi-bit non-correction interrupt enable */
    SYSCFG_INT_ECC_SE2          = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG3_OFFSET, 3, 0U),           /*!< CAN filter SRAM single-bit correction interrupt enable */
    SYSCFG_INT_ECC_ME3          = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG4_OFFSET, 0, 0U),           /*!< Flash SRAM multi-bit non-correction interrupt enable */
    SYSCFG_INT_ECC_SE3          = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG4_OFFSET, 1, 0U),           /*!< Flash SRAM single-bit correction interrupt enable */
    SYSCFG_INT_ECC_ME4          = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG4_OFFSET, 2, 0U),           /*!< Flash multi-bit non-correction interrupt enable */
    /* NMI */
    SYSCFG_INT_NMI_HXTAL        = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG2_OFFSET, 3, 0U),           /*!< HXTAL clock monitor NMI interrupt enable */
    SYSCFG_INT_NMI_PIN          = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG2_OFFSET, 4, 0U),           /*!< NMI pin interrupt enable */
    SYSCFG_INT_NMI_WWDGT        = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG2_OFFSET, 6, 0U),           /*!< WWDGT NMI interrupt enable*/
    SYSCFG_INT_NMI_FWDGT        = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG2_OFFSET, 7, 0U),           /*!< FWDGT NMI interrupt enable*/
    SYSCFG_INT_NMI_LVD2         = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG2_OFFSET, 8, 0U),           /*!< LVD2 NMI interrupt enable*/
    SYSCFG_INT_NMI_LVD1         = SYSCFG_REGIDX_BIT_VAL(SYSCFG_CFG2_OFFSET, 9, 0U),           /*!< LVD1 NMI interrupt enable*/
} syscfg_interrupt_enum;

/* peripheral interrupt flag */
#define SYSCFG_INT_FLAG_ECC_ME0             SYSCFG_STAT_ECCMEIF0                              /*!< SRAM multi-bit error flag */
#define SYSCFG_INT_FLAG_ECC_SE0             SYSCFG_STAT_ECCSEIF0                              /*!< SRAM single-bit error flag */
#define SYSCFG_INT_FLAG_ECC_ME1             SYSCFG_STAT_ECCMEIF1                              /*!< CAN FIFO SRAM multi-bit error flag */
#define SYSCFG_INT_FLAG_ECC_SE1             SYSCFG_STAT_ECCSEIF1                              /*!< CAN FIFO SRAM single-bit error flag */
#define SYSCFG_INT_FLAG_ECC_ME2             SYSCFG_STAT_ECCMEIF2                              /*!< CAN filter SRAM multi-bit error flag */
#define SYSCFG_INT_FLAG_ECC_SE2             SYSCFG_STAT_ECCSEIF2                              /*!< CAN filter SRAM single-bit error flag */
#define SYSCFG_INT_FLAG_ECC_ME3             SYSCFG_STAT_ECCMEIF3                              /*!< Flash SRAM multi-bit error flag */
#define SYSCFG_INT_FLAG_ECC_SE3             SYSCFG_STAT_ECCSEIF3                              /*!< Flash SRAM single-bit error flag */
#define SYSCFG_INT_FLAG_ECC_ME4             SYSCFG_STAT_ECCMEIF4                              /*!< Flash multi-bit error flag */
#define SYSCFG_INT_FLAG_NMI_HXTAL           SYSCFG_STAT_HXTAL_NMIIF                           /*!< HXTAL clock monitor NMI interrupt flag */
#define SYSCFG_INT_FLAG_NMI_PIN             SYSCFG_STAT_PIN_NMIIF                             /*!< NMI pin interrupt flag */
#define SYSCFG_INT_FLAG_NMI_WWDGT           SYSCFG_STAT_WWDGT_NMIIF                           /*!< WWDGT NMI interrupt flag */
#define SYSCFG_INT_FLAG_NMI_FWDGT           SYSCFG_STAT_FWDGT_NMIIF                           /*!< FWDGT NMI interrupt flag */

/* TIMERx A/D conversion start request select definitions */
typedef enum {
    /* ADCSM1 pin */
    SYSCFG_ADCSM1_TIMER0_TRGOF  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 0, 0U),     /*!< ADCSM1 Source of monitor is TIMER0_TRGOF */
    SYSCFG_ADCSM1_TIMER0_TRGUF  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 0, 1U),     /*!< ADCSM1 Source of monitor is TIMER0_TRGUF */
    SYSCFG_ADCSM1_TIMER0_TRGA   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 0, 2U),     /*!< ADCSM1 Source of monitor is TIMER0_TRGA  */
    SYSCFG_ADCSM1_TIMER0_TRGB   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 0, 3U),     /*!< ADCSM1 Source of monitor is TIMER0_TRGB  */
    SYSCFG_ADCSM1_TIMER0_TRGAB  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 0, 4U),     /*!< ADCSM1 Source of monitor is TIMER0_TRGAB */
    SYSCFG_ADCSM1_TIMER7_TRGOF  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 0, 5U),     /*!< ADCSM1 Source of monitor is TIMER7_TRGOF */
    SYSCFG_ADCSM1_TIMER7_TRGUF  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 0, 6U),     /*!< ADCSM1 Source of monitor is TIMER7_TRGUF */
    SYSCFG_ADCSM1_TIMER7_TRGA   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 0, 7U),     /*!< ADCSM1 Source of monitor is TIMER7_TRGA  */
    SYSCFG_ADCSM1_TIMER7_TRGB   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 0, 8U),     /*!< ADCSM1 Source of monitor is TIMER7_TRGB  */
    SYSCFG_ADCSM1_TIMER7_TRGAB  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 0, 9U),     /*!< ADCSM1 Source of monitor is TIMER7_TRGAB */
    /* ADCSM2 pin */
    SYSCFG_ADCSM2_TIMER0_TRGOF  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 8, 0U),     /*!< ADCSM2 Source of monitor is TIMER0_TRGOF */
    SYSCFG_ADCSM2_TIMER0_TRGUF  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 8, 1U),     /*!< ADCSM2 Source of monitor is TIMER0_TRGUF */
    SYSCFG_ADCSM2_TIMER0_TRGA   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 8, 2U),     /*!< ADCSM2 Source of monitor is TIMER0_TRGA  */
    SYSCFG_ADCSM2_TIMER0_TRGB   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 8, 3U),     /*!< ADCSM2 Source of monitor is TIMER0_TRGB  */
    SYSCFG_ADCSM2_TIMER0_TRGAB  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 8, 4U),     /*!< ADCSM2 Source of monitor is TIMER0_TRGAB */
    SYSCFG_ADCSM2_TIMER7_TRGOF  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 8, 5U),     /*!< ADCSM2 Source of monitor is TIMER7_TRGOF */
    SYSCFG_ADCSM2_TIMER7_TRGUF  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 8, 6U),     /*!< ADCSM2 Source of monitor is TIMER7_TRGUF */
    SYSCFG_ADCSM2_TIMER7_TRGA   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 8, 7U),     /*!< ADCSM2 Source of monitor is TIMER7_TRGA  */
    SYSCFG_ADCSM2_TIMER7_TRGB   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 8, 8U),     /*!< ADCSM2 Source of monitor is TIMER7_TRGB  */
    SYSCFG_ADCSM2_TIMER7_TRGAB  = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TADSRCFG_OFFSET, 8, 9U),     /*!< ADCSM2 Source of monitor is TIMER7_TRGAB */
} syscfg_adcsm_enum;

/* TIMERx channel input Select definitions */
typedef enum {
    TIMER7_CI0_INPUT_TIMER7_CH0     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL0_OFFSET, 0,  0U),      /*!< select TIMER7 CH0 as TIMER7 CI0 */
    TIMER7_CI0_INPUT_CMP1_OUT       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL0_OFFSET, 0,  1U),      /*!< select CMP1 output as TIMER7 CI0 */
    TIMER7_CI1_INPUT_TIMER7_CH1     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL0_OFFSET, 4,  0U),      /*!< select TIMER7 CH1 as TIMER7 CI1 */
    TIMER7_CI2_INPUT_TIMER7_CH2     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL0_OFFSET, 8,  0U),      /*!< select TIMER7 CH2 as TIMER7 CI2 */
    TIMER7_CI3_INPUT_TIMER7_CH3     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL0_OFFSET, 12, 0U),      /*!< select TIMER7 CH3 as TIMER7 CI3 */
    TIMER0_CI0_INPUT_TIMER0_CH0     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL0_OFFSET, 16, 0U),      /*!< select TIMER0 CH0 as TIMER0 CI0 */
    TIMER0_CI0_INPUT_CMP0_OUT       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL0_OFFSET, 16, 1U),      /*!< select CMP0 output as TIMER0 CI0 */
    TIMER0_CI1_INPUT_TIMER0_CH1     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL0_OFFSET, 20, 0U),      /*!< select TIMER0 CH1 as TIMER0 CI1 */
    TIMER0_CI2_INPUT_TIMER0_CH2     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL0_OFFSET, 24, 0U),      /*!< select TIMER0 CH2 as TIMER0 CI2 */
    TIMER0_CI3_INPUT_TIMER0_CH3     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL0_OFFSET, 28, 0U),      /*!< select TIMER0 CH3 as TIMER0 CI3 */
    TIMER2_CI0_INPUT_TIMER2_CH0     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 0,  0U),      /*!< select TIMER2 CH0 as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP0_OUT       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 0,  1U),      /*!< select CMP0 output as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP1_OUT       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 0,  2U),      /*!< select CMP1 output as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP0_1_OUT     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 0,  3U),      /*!< select CMP0 and CMP1 output as TIMER2 CI0 */
    TIMER2_CI0_INPUT_EXT_TRIGGER0   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 0,  8U),      /*!< select external trigger 0 as TIMER2 CI0 */
    TIMER2_CI0_INPUT_EXT_TRIGGER1   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 0,  9U),      /*!< select external trigger 1 as TIMER2 CI0 */
    TIMER2_CI0_INPUT_EXT_TRIGGER2   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 0,  10U),     /*!< select external trigger 2 as TIMER2 CI0 */
    TIMER2_CI0_INPUT_EXT_TRIGGER3   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 0,  11U),     /*!< select external trigger 3 as TIMER2 CI0 */
    TIMER2_CI1_INPUT_TIMER2_CH1     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 4,  0U),      /*!< select TIMER2 CH1 as TIMER2 CI1 */
    TIMER2_CI1_INPUT_EXT_TRIGGER0   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 4,  8U),      /*!< select external trigger 0 as TIMER2 CI1 */
    TIMER2_CI1_INPUT_EXT_TRIGGER1   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 4,  9U),      /*!< select external trigger 1 as TIMER2 CI1 */
    TIMER2_CI1_INPUT_EXT_TRIGGER2   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 4,  10U),     /*!< select external trigger 2 as TIMER2 CI1 */
    TIMER2_CI1_INPUT_EXT_TRIGGER3   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 4,  11U),     /*!< select external trigger 3 as TIMER2 CI1 */
    TIMER2_CI2_INPUT_TIMER2_CH2     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 8,  0U),      /*!< select TIMER2 CH2 as TIMER2 CI2 */
    TIMER2_CI3_INPUT_TIMER2_CH3     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 12, 0U),      /*!< select TIMER2 CH3 as TIMER2 CI3 */
    TIMER2_CI3_INPUT_IRC32K         = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 12, 14U),     /*!< select IRC32K as TIMER2 CI3 */
    TIMER2_CI3_INPUT_CK_OUT         = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 12, 15U),     /*!< select Clock out as TIMER2 CI3 */
    TIMER1_CI0_INPUT_TIMER1_CH0     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 16, 0U),      /*!< select TIMER1 CH0 as TIMER1 CI0 */
    TIMER1_CI0_INPUT_EXT_TRIGGER0   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 16, 8U),      /*!< select external trigger 0 as TIMER1 CI0 */
    TIMER1_CI0_INPUT_EXT_TRIGGER1   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 16, 9U),      /*!< select external trigger 1 as TIMER1 CI0 */
    TIMER1_CI0_INPUT_EXT_TRIGGER2   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 16, 10U),     /*!< select external trigger 2 as TIMER1 CI0 */
    TIMER1_CI0_INPUT_EXT_TRIGGER3   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 16, 11U),     /*!< select external trigger 3 as TIMER1 CI0 */
    TIMER1_CI1_INPUT_TIMER1_CH1     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 20, 0U),      /*!< select TIMER1 CH1 as TIMER1 CI1 */
    TIMER1_CI1_INPUT_EXT_TRIGGER0   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 20, 8U),      /*!< select external trigger 0 as TIMER1 CI1 */
    TIMER1_CI1_INPUT_EXT_TRIGGER1   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 20, 9U),      /*!< select external trigger 1 as TIMER1 CI1 */
    TIMER1_CI1_INPUT_EXT_TRIGGER2   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 20, 10U),     /*!< select external trigger 2 as TIMER1 CI1 */
    TIMER1_CI1_INPUT_EXT_TRIGGER3   = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 20, 11U),     /*!< select external trigger 3 as TIMER1 CI1 */
    TIMER1_CI2_INPUT_TIMER1_CH2     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 24, 0U),      /*!< select TIMER1 CH2 as TIMER1 CI2 */
    TIMER1_CI3_INPUT_TIMER1_CH3     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 28, 0U),      /*!< select TIMER1 CH3 as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CMP0_OUT       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 28, 1U),      /*!< select CMP0 output as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CMP1_OUT       = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 28, 2U),      /*!< select CMP1 output as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CMP0_1_OUT     = SYSCFG_REGIDX_BIT_VAL(SYSCFG_TIMERCISEL1_OFFSET, 28, 3U),      /*!< select CMP0 and CMP1 output as TIMER1 CI3 */
} timer_channel_input_enum;

/* boot mode */
#define SYSCFG_BOOT_SYSTEM_MEMORY           ((uint32_t)0x00U)                           /*!< Boot from the system memory  */
#define SYSCFG_BOOT_MAIN_FLASH              ((uint32_t)0x01U)                           /*!< boot from the main flash */

/* module lockup */
#define SYSCFG_LOCKUP_LOCKUP                SYSCFG_CFG5_LOCKUP_LOCK                     /*!< CPU lockup (Hardfault) output enable */
#define SYSCFG_LVD_LOCKUP                   SYSCFG_CFG5_LVD_LOCK                        /*!< Low voltage detector lock */
#define SYSCFG_SRAM_LOCKUP                  SYSCFG_CFG5_SRAM_LOCK                       /*!< SRAM ECC multi-bit error lock */
#define SYSCFG_CANRX_LOCK                   SYSCFG_CFG5_CANRX_LOCK                      /*!< CAN receive FIFO ECC multi-bit error lock */
#define SYSCFG_CANFILTER_LOCK               SYSCFG_CFG5_CANFILTER_LOCK                  /*!< CAN filter ECC multi-bit error lock */
#define SYSCFG_FLASHSRAM_LOCK               SYSCFG_CFG5_FLASHSRAM_LOCK                  /*!< Flash SRAM ECC multi-bit error lock */
#define SYSCFG_FLASH_LOCKUP                 SYSCFG_CFG5_FLASH_LOCK                      /*!< Flash ECC multi-bit error lock */

/* SRAM remap size definitions */
#define SRAM_REMAP_SIZE_0KB                 ((uint32_t)0x00000000U)                     /*!< SRAM Remap 0KB to 0x10000000 */
#define SRAM_REMAP_SIZE_8KB                 ((uint32_t)0x00000001U)                     /*!< SRAM Remap 8KB to 0x10000000 */
#define SRAM_REMAP_SIZE_16KB                ((uint32_t)0x00000002U)                     /*!< SRAM Remap 16KB to 0x10000000 */
#define SRAM_REMAP_SIZE_32KB                ((uint32_t)0x00000003U)                     /*!< SRAM Remap 32KB to 0x10000000 */

/* Register Write Protection definitions */
#define SYSCFG_WRITE_PROTECTION_KEY         ((uint32_t)0xA500U)                         /*!< Registers Write Protection KEY */
#define SYSCFG_WRITE_PROTECTION_REG0        SYSCFG_PRCFG_PRCFG0                         /*!< Registers Write Protection related to the clock generation circuit */
#define SYSCFG_WRITE_PROTECTION_REG1        SYSCFG_PRCFG_PRCFG1                         /*!< Registers Write Protection related to  Operating modes/ low power consumption/clock generation/Software reset registers*/
#define SYSCFG_WRITE_PROTECTION_REG2        SYSCFG_PRCFG_PRCFG2                         /*!< Registers Write Protection related to the LVD */

/* ADC signal monitor output */
#define SYSCFG_TADSRCFG_ADCSM1              SYSCFG_TADSRCFG_ADCSM1EN                    /*!< ADCSM1 pin output */
#define SYSCFG_TADSRCFG_ADCSM2              SYSCFG_TADSRCFG_ADCSM2EN                    /*!< ADCSM2 pin output */

/* timer trigger source select definition */
#define TIMER_SMCFG_TRGSEL_NONE             ((uint8_t)0x00U)                            /*!< trigger input is none */
#define TIMER_SMCFG_TRGSEL_ITI0             ((uint8_t)0x01U)                            /*!< internal trigger input 0 */
#define TIMER_SMCFG_TRGSEL_ITI1             ((uint8_t)0x02U)                            /*!< internal trigger input 1 */
#define TIMER_SMCFG_TRGSEL_ITI2             ((uint8_t)0x03U)                            /*!< internal trigger input 2 */
#define TIMER_SMCFG_TRGSEL_ITI3             ((uint8_t)0x04U)                            /*!< internal trigger input 3 */
#define TIMER_SMCFG_TRGSEL_CI0F_ED          ((uint8_t)0x05U)                            /*!< TI0 edge detector */
#define TIMER_SMCFG_TRGSEL_CI0FE0           ((uint8_t)0x06U)                            /*!< filtered TIMER input 0 */
#define TIMER_SMCFG_TRGSEL_CI1FE1           ((uint8_t)0x07U)                            /*!< filtered TIMER input 1 */
#define TIMER_SMCFG_TRGSEL_ETIFP            ((uint8_t)0x08U)                            /*!< external trigger */
#define TIMER_SMCFG_TRGSEL_CI2FE2           ((uint8_t)0x09U)                            /*!< filtered TIMER input 2 */
#define TIMER_SMCFG_TRGSEL_CI3FE3           ((uint8_t)0x0AU)                            /*!< filtered TIMER input 3 */
#define TIMER_SMCFG_TRGSEL_MCI0FEM0         ((uint8_t)0x0BU)                            /*!< filtered output of multi mode channel 0 input */
#define TIMER_SMCFG_TRGSEL_MCI1FEM1         ((uint8_t)0x0CU)                            /*!< filtered output of multi mode channel 1 input */
#define TIMER_SMCFG_TRGSEL_MCI2FEM2         ((uint8_t)0x0DU)                            /*!< filtered output of multi mode channel 2 input */
#define TIMER_SMCFG_TRGSEL_MCI3FEM3         ((uint8_t)0x0EU)                            /*!< filtered output of multi mode channel 3 input */

/* timer trigger mode select definition */
#define TIMER_QUAD_DECODER_MODE0            ((uint8_t)0x00U)                            /*!< quadrature decoder mode 0 */
#define TIMER_QUAD_DECODER_MODE1            ((uint8_t)0x01U)                            /*!< quadrature decoder mode 1 */
#define TIMER_QUAD_DECODER_MODE2            ((uint8_t)0x02U)                            /*!< quadrature decoder mode 2 */
#define TIMER_SLAVE_MODE_RESTART            ((uint8_t)0x03U)                            /*!< restart mode */
#define TIMER_SLAVE_MODE_PAUSE              ((uint8_t)0x04U)                            /*!< pause mode */
#define TIMER_SLAVE_MODE_EVENT              ((uint8_t)0x05U)                            /*!< event mode */
#define TIMER_SLAVE_MODE_EXTERNAL0          ((uint8_t)0x06U)                            /*!< external clock mode 0 */
#define TIMER_SLAVE_MODE_RESTART_EVENT      ((uint8_t)0x07U)                            /*!< restart + event mode */
#define TIMER_SLAVE_MODE_RESTART_PAUSE      ((uint8_t)0x08U)                            /*!< restart + pause mode */
#define TIMER_NONQUAD_DECODER_MODE0         ((uint8_t)0x09U)                            /*!< non-quadrature decoder mode 0 */
#define TIMER_NONQUAD_DECODER_MODE1         ((uint8_t)0x0AU)                            /*!< non-quadrature decoder mode 1 */
#define TIMER_NONQUAD_DECODER_MODE2         ((uint8_t)0x0BU)                            /*!< non-quadrature decoder mode 2 */
#define TIMER_NONQUAD_DECODER_MODE3         ((uint8_t)0x0CU)                            /*!< non-quadrature decoder mode 3 */
#define TIMER_QUAD_DECODER_MODE3            ((uint8_t)0x0DU)                            /*!< quadrature decoder mode 3 */
#define TIMER_QUAD_DECODER_MODE4            ((uint8_t)0x0EU)                            /*!< quadrature decoder mode 4 */
#define TIMER_SLAVE_MODE_DISABLE            ((uint8_t)0x0FU)                            /*!< slave mode disable */

/* definition of syscfg_timerx */
#define SYSCFG_TIMER0                       ((uint8_t)0x00U)                            /*!< SYSCFG TIMER0 */
#define SYSCFG_TIMER1                       ((uint8_t)0x01U)                            /*!< SYSCFG TIMER1 */
#define SYSCFG_TIMER2                       ((uint8_t)0x02U)                            /*!< SYSCFG TIMER2 */
#define SYSCFG_TIMER7                       ((uint8_t)0x03U)                            /*!< SYSCFG TIMER7 */

#define SYSCFG_TIMERCFG0(syscfg_timerx)     (SYSCFG + 0x100U + (syscfg_timerx) * 0x0CU)   /*!< TIMERx(x=0/1/2/7) configuration register0 base address */
#define SYSCFG_TIMERCFG1(syscfg_timerx)     (SYSCFG + 0x104U + (syscfg_timerx) * 0x0CU)   /*!< TIMERx(x=0/1/2/7) configuration register1 base address */
#define SYSCFG_TIMERCFG2(syscfg_timerx)     (SYSCFG + 0x108U + (syscfg_timerx) * 0x0CU)   /*!< TIMERx(x=0/1/2/7) configuration register2 base address */

#define SYSCFG_TIMERXCFG0(syscfg_timerx)    REG32(SYSCFG_TIMERCFG0(syscfg_timerx))   /*!< TIMERx(x=0/1/2/7) configuration register0 */
#define SYSCFG_TIMERXCFG1(syscfg_timerx)    REG32(SYSCFG_TIMERCFG1(syscfg_timerx))   /*!< TIMERx(x=0/1/2/7) configuration register1 */
#define SYSCFG_TIMERXCFG2(syscfg_timerx)    REG32(SYSCFG_TIMERCFG2(syscfg_timerx))   /*!< TIMERx(x=0/1/2/7) configuration register2 */

/* CK_CMP Selection definitions */
typedef enum {
    CK_CMP_DIV2     = 0U,      /*!< CK_CMP=fPCLK/2 */
    CK_CMP_DIV4     = 1U,      /*!< CK_CMP=fPCLK/4 */
} ck_cmp_sel_enum;


/* function declarations */
/* initialization functions */
/* reset the SYSCFG registers */
void syscfg_deinit(void);

/* enable I2Cfast mode plus */
void syscfg_i2c_fast_mode_plus_enable(void);
/* disable I2C fast mode plus */
void syscfg_i2c_fast_mode_plus_disable(void);
/* configure the GPIO pin as EXTI Line */
void syscfg_exti_line_config(exti_gpio_enum exti_gpio);
/* select timer channel input source */
void syscfg_timer_input_source_select(timer_channel_input_enum timer_input);
/* enable module lockup function (function can be disabled by system reset) */
void syscfg_lockup_enable(uint32_t lockup);
/* set SRAM remap size */
void syscfg_sram_remap_set(uint32_t size);
/* get SRAM remap size */
uint32_t syscfg_sram_remap_size_get(void);
/* set CK_CMP selection */
void syscfg_ck_cmp_sel_set(ck_cmp_sel_enum sel);
/* get CK_CMP selection */
ck_cmp_sel_enum syscfg_ck_cmp_sel_get(void);

/* enable register write function */
void syscfg_register_write_enable(uint32_t wp_reg);
/* disable register write function */
void syscfg_register_write_disable(uint32_t wp_reg);

/* select ADC signal monitor */
void syscfg_adc_signal_monitor_select(syscfg_adcsm_enum timer_signal);
/* enable ADC signal monitor output */
void syscfg_adc_signal_monitor_output_enable(uint32_t adcsm);
/* disable ADC signal monitor output */
void syscfg_adc_signal_monitor_output_disable(uint32_t adcsm);

/* get boot mode */
uint32_t syscfg_boot_mode_get(void);
/* get sram ecc error address */
uint32_t syscfg_sram_ecc_error_address_get(void);
/* get sram ecc single-bit correction error bit */
uint8_t syscfg_sram_ecc_error_bit_get(void);

/* flag and interrupt functions */
/* enable the syscfg peripherals interrupt */
void syscfg_interrupt_enable(syscfg_interrupt_enum interrupt);
/* disable the syscfg peripherals interrupt */
void syscfg_interrupt_disable(syscfg_interrupt_enum interrupt);
/* get the interrupt flags */
FlagStatus syscfg_interrupt_flag_get(uint32_t int_flag);
/* clear the interrupt flags */
void syscfg_interrupt_flag_clear(uint32_t int_flag);

#endif /* GD32M53X_SYSCFG_H */
