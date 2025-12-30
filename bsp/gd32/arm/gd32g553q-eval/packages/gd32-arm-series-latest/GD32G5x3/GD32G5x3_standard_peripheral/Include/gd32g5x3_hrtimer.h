/*!
    \file    gd32g5x3_hrtimer.h
    \brief   definitions for the HRTIMER

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

#ifndef GD32G5X3_HRTIMER_H
#define GD32G5X3_HRTIMER_H

#include "gd32g5x3.h"

/* HRTIMERy(y=0) definitions */
#define HRTIMER0                                      (HRTIMER_BASE + 0x00000000U)

/* registers definitions */
/* Master_TIMER registers definitions */
#define HRTIMER_MTCTL0(hrtimery)                     REG32((hrtimery) + 0x00000000U)                                              /*!< HRTIMER Master_TIMER control register 0 */
#define HRTIMER_MTINTF(hrtimery)                     REG32((hrtimery) + 0x00000004U)                                              /*!< HRTIMER Master_TIMER interrupt flag register */
#define HRTIMER_MTINTC(hrtimery)                     REG32((hrtimery) + 0x00000008U)                                              /*!< HRTIMER Master_TIMER interrupt flag clear register */
#define HRTIMER_MTDMAINTEN(hrtimery)                 REG32((hrtimery) + 0x0000000CU)                                              /*!< HRTIMER Master_TIMER DMA and interrupt enable register */
#define HRTIMER_MTCNT(hrtimery)                      REG32((hrtimery) + 0x00000010U)                                              /*!< HRTIMER Master_TIMER counter register */
#define HRTIMER_MTCAR(hrtimery)                      REG32((hrtimery) + 0x00000014U)                                              /*!< HRTIMER Master_TIMER counter auto reload register */
#define HRTIMER_MTCREP(hrtimery)                     REG32((hrtimery) + 0x00000018U)                                              /*!< HRTIMER Master_TIMER counter repetition register */
#define HRTIMER_MTCMP0V(hrtimery)                    REG32((hrtimery) + 0x0000001CU)                                              /*!< HRTIMER Master_TIMER compare 0 value register */
#define HRTIMER_MTCMP1V(hrtimery)                    REG32((hrtimery) + 0x00000024U)                                              /*!< HRTIMER Master_TIMER compare 1 value register */
#define HRTIMER_MTCMP2V(hrtimery)                    REG32((hrtimery) + 0x00000028U)                                              /*!< HRTIMER Master_TIMER compare 2 value register */
#define HRTIMER_MTCMP3V(hrtimery)                    REG32((hrtimery) + 0x0000002CU)                                              /*!< HRTIMER Master_TIMER compare 3 value register */

/* Slave_TIMERx(x=0..7) registers definitions */
#define HRTIMER_STXCTL0(hrtimery, slavex)            REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000000U)           /*!< HRTIMER Slave_TIMERx control register 0 */
#define HRTIMER_STXINTF(hrtimery, slavex)            REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000004U)           /*!< HRTIMER Slave_TIMERx interrupt flag register */
#define HRTIMER_STXINTC(hrtimery, slavex)            REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000008U)           /*!< HRTIMER Slave_TIMERx interrupt flag clear register */
#define HRTIMER_STXDMAINTEN(hrtimery, slavex)        REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000000CU)           /*!< HRTIMER Slave_TIMERx DMA and interrupt enable register */
#define HRTIMER_STXCNT(hrtimery, slavex)             REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000010U)           /*!< HRTIMER Slave_TIMERx counter register */
#define HRTIMER_STXCAR(hrtimery, slavex)             REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000014U)           /*!< HRTIMER Slave_TIMERx counter auto reload register */
#define HRTIMER_STXCREP(hrtimery, slavex)            REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000018U)           /*!< HRTIMER Slave_TIMERx counter repetition register */
#define HRTIMER_STXCMP0V(hrtimery, slavex)           REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000001CU)           /*!< HRTIMER Slave_TIMERx compare 0 value register */
#define HRTIMER_STXCMP0CP(hrtimery, slavex)          REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000020U)           /*!< HRTIMER Slave_TIMERx compare 0 composite register */
#define HRTIMER_STXCMP1V(hrtimery, slavex)           REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000024U)           /*!< HRTIMER Slave_TIMERx compare 1 value register */
#define HRTIMER_STXCMP2V(hrtimery, slavex)           REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000028U)           /*!< HRTIMER Slave_TIMERx compare 2 value register */
#define HRTIMER_STXCMP3V(hrtimery, slavex)           REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000002CU)           /*!< HRTIMER Slave_TIMERx compare 3 value register */
#define HRTIMER_STXCAP0V(hrtimery, slavex)           REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000030U)           /*!< HRTIMER Slave_TIMERx capture 0 value register */
#define HRTIMER_STXCAP1V(hrtimery, slavex)           REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000034U)           /*!< HRTIMER Slave_TIMERx capture 1 value register */
#define HRTIMER_STXDTCTL(hrtimery, slavex)           REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000038U)           /*!< HRTIMER Slave_TIMERx dead-time control register */
#define HRTIMER_STXCH0SET(hrtimery, slavex)          REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000003CU)           /*!< HRTIMER Slave_TIMERx channel 0 set request register */
#define HRTIMER_STXCH0RST(hrtimery, slavex)          REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000040U)           /*!< HRTIMER Slave_TIMERx channel 0 reset request register */
#define HRTIMER_STXCH1SET(hrtimery, slavex)          REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000044U)           /*!< HRTIMER Slave_TIMERx channel 1 set request register */
#define HRTIMER_STXCH1RST(hrtimery, slavex)          REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000048U)           /*!< HRTIMER Slave_TIMERx channel 1 reset request register */
#define HRTIMER_STXEXEVFCFG0(hrtimery, slavex)       REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000004CU)           /*!< HRTIMER Slave_TIMERx external event filter configuration register 0 */
#define HRTIMER_STXEXEVFCFG1(hrtimery, slavex)       REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000050U)           /*!< HRTIMER Slave_TIMERx external event filter configuration register 1 */
#define HRTIMER_STXCNTRST(hrtimery, slavex)          REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000054U)           /*!< HRTIMER Slave_TIMERx counter reset register */ 
#define HRTIMER_STXCSCTL(hrtimery, slavex)           REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000058U)           /*!< HRTIMER Slave_TIMERx carrier-signal control register */
#define HRTIMER_STXCAP0TRG(hrtimery, slavex)         REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000005CU)           /*!< HRTIMER Slave_TIMERx capture 0 trigger register */
#define HRTIMER_STXCAP1TRG(hrtimery, slavex)         REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000060U)           /*!< HRTIMER Slave_TIMERx capture 1 trigger register */
#define HRTIMER_STXCHOCTL(hrtimery, slavex)          REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000064U)           /*!< HRTIMER Slave_TIMERx channel output control register */
#define HRTIMER_STXFLTCTL(hrtimery, slavex)          REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000068U)           /*!< HRTIMER Slave_TIMERx fault control register */
#define HRTIMER_STXCTL1(hrtimery, slavex)            REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000006CU)           /*!< HRTIMER Slave_TIMERx control register 1 */
#define HRTIMER_STXEXEVFCFG2(hrtimery, slavex)       REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000070U)           /*!< HRTIMER Slave_TIMERx external event filter configuration register 2 */
#define HRTIMER_STXCAPTRGCOM(hrtimery, slavex)       REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000074U)           /*!< HRTIMER Slave_TIMERx capture trigger combination register */
#define HRTIMER_STXCNTRSTA(hrtimery, slavex)         REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x00000078U)           /*!< HRTIMER Slave_TIMERx counter reset and channel 0/1 set/reset request add register */
#define HRTIMER_STXACTL(hrtimery, slavex)            REG32((hrtimery) + (((slavex) + 0x0001U) * 0x0080U) + 0x0000007CU)           /*!< HRTIMER Slave_TIMERx additional control register */

/* common registers definitions */
#define HRTIMER_CTL0(hrtimery)                       REG32(((hrtimery) + 0x00000380U) + 0x00000000U)                              /*!< HRTIMER control register 0 */
#define HRTIMER_CTL1(hrtimery)                       REG32(((hrtimery) + 0x00000380U) + 0x00000004U)                              /*!< HRTIMER control register 1 */
#define HRTIMER_INTF(hrtimery)                       REG32(((hrtimery) + 0x00000380U) + 0x00000008U)                              /*!< HRTIMER interrupt flag register */
#define HRTIMER_INTC(hrtimery)                       REG32(((hrtimery) + 0x00000380U) + 0x0000000CU)                              /*!< HRTIMER interrupt flag clear register */
#define HRTIMER_INTEN(hrtimery)                      REG32(((hrtimery) + 0x00000380U) + 0x00000010U)                              /*!< HRTIMER interrupt enable register */
#define HRTIMER_CHOUTEN(hrtimery)                    REG32(((hrtimery) + 0x00000380U) + 0x00000014U)                              /*!< HRTIMER channel output enable register */
#define HRTIMER_CHOUTDIS(hrtimery)                   REG32(((hrtimery) + 0x00000380U) + 0x00000018U)                              /*!< HRTIMER channel output disable register */
#define HRTIMER_CHOUTDISF(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x0000001CU)                              /*!< HRTIMER channel output disable flag register */
#define HRTIMER_BMCTL(hrtimery)                      REG32(((hrtimery) + 0x00000380U) + 0x00000020U)                              /*!< HRTIMER bunch mode control register */
#define HRTIMER_BMSTRG(hrtimery)                     REG32(((hrtimery) + 0x00000380U) + 0x00000024U)                              /*!< HRTIMER bunch mode start trigger register */
#define HRTIMER_BMCMPV(hrtimery)                     REG32(((hrtimery) + 0x00000380U) + 0x00000028U)                              /*!< HRTIMER bunch mode compare value register */
#define HRTIMER_BMCAR(hrtimery)                      REG32(((hrtimery) + 0x00000380U) + 0x0000002CU)                              /*!< HRTIMER bunch mode counter auto reload register */
#define HRTIMER_EXEVCFG0(hrtimery)                   REG32(((hrtimery) + 0x00000380U) + 0x00000030U)                              /*!< HRTIMER external event configuration register 0 */
#define HRTIMER_EXEVCFG1(hrtimery)                   REG32(((hrtimery) + 0x00000380U) + 0x00000034U)                              /*!< HRTIMER external event configuration register 1 */
#define HRTIMER_EXEVDFCTL(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000038U)                              /*!< HRTIMER external event digital filter control register */
#define HRTIMER_ADCTRIGS0(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x0000003CU)                              /*!< HRTIMER trigger source 0 to ADC register */
#define HRTIMER_ADCTRIGS1(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000040U)                              /*!< HRTIMER trigger source 1 to ADC register */
#define HRTIMER_ADCTRIGS2(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000044U)                              /*!< HRTIMER trigger source 2 to ADC register */
#define HRTIMER_ADCTRIGS3(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000048U)                              /*!< HRTIMER trigger source 3 to ADC register */
#define HRTIMER_DLLCCTL(hrtimery)                    REG32(((hrtimery) + 0x00000380U) + 0x0000004CU)                              /*!< HRTIMER DLL calibration control register */
#define HRTIMER_FLTINCFG0(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000050U)                              /*!< HRTIMER fault input configuration register 0 */
#define HRTIMER_FLTINCFG1(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000054U)                              /*!< HRTIMER fault input configuration register 1 */
#define HRTIMER_DMAUPMTR(hrtimery)                   REG32(((hrtimery) + 0x00000380U) + 0x00000058U)                              /*!< HRTIMER DMA update Master_TIMER register */
#define HRTIMER_DMAUPST0R(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x0000005CU)                              /*!< HRTIMER DMA update Slave_TIMER0 register */
#define HRTIMER_DMAUPST1R(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000060U)                              /*!< HRTIMER DMA update Slave_TIMER1 register */
#define HRTIMER_DMAUPST2R(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000064U)                              /*!< HRTIMER DMA update Slave_TIMER2 register */
#define HRTIMER_DMAUPST3R(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000068U)                              /*!< HRTIMER DMA update Slave_TIMER3 register */
#define HRTIMER_DMAUPST4R(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x0000006CU)                              /*!< HRTIMER DMA update Slave_TIMER4 register */
#define HRTIMER_DMAUPST5R(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000074U)                              /*!< HRTIMER DMA update Slave_TIMER5 register */
#define HRTIMER_DMAUPST6R(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000100U)                              /*!< HRTIMER DMA update Slave_TIMER6 register */
#define HRTIMER_DMAUPST7R(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000104U)                              /*!< HRTIMER DMA update Slave_TIMER7 register */
#define HRTIMER_DMATB(hrtimery)                      REG32(((hrtimery) + 0x00000380U) + 0x00000070U)                              /*!< HRTIMER DMA transfer buffer register */
#define HRTIMER_ADCEXTTRG(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000078U)                              /*!< HRTIMER ADC extended trigger register */
#define HRTIMER_ADCTRGUPD(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x0000007CU)                              /*!< HRTIMER ADC trigger update register */
#define HRTIMER_ADCPSCR0(hrtimery)                   REG32(((hrtimery) + 0x00000380U) + 0x00000080U)                              /*!< HRTIMER ADC post scaler register 0 */
#define HRTIMER_ADCPSCR1(hrtimery)                   REG32(((hrtimery) + 0x00000380U) + 0x00000084U)                              /*!< HRTIMER ADC post scaler register 1 */
#define HRTIMER_FLTINCFG2(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x00000088U)                              /*!< HRTIMER fault input configuration register 2 */
#define HRTIMER_FLTINCFG3(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x0000008CU)                              /*!< HRTIMER fault input configuration register 3 */
#define HRTIMER_BMSTRGA(hrtimery)                    REG32(((hrtimery) + 0x00000380U) + 0x00000108U)                              /*!< HRTIMER bunch mode start trigger add register */
#define HRTIMER_FLTINCFG4(hrtimery)                  REG32(((hrtimery) + 0x00000380U) + 0x0000010CU)                              /*!< HRTIMER fault input configuration register 4 */
#define HRTIMER_ADCEXTTRGA(hrtimery)                 REG32(((hrtimery) + 0x00000380U) + 0x00000110U)                              /*!< HRTIMER ADC extended trigger add register */
#define HRTIMER_ADCTRIGS0A(hrtimery)                 REG32(((hrtimery) + 0x00000380U) + 0x00000114U)                              /*!< HRTIMER trigger source 0 to ADC add register  */
#define HRTIMER_ADCTRIGS1A(hrtimery)                 REG32(((hrtimery) + 0x00000380U) + 0x00000118U)                              /*!< HRTIMER trigger source 1 to ADC add register */
#define HRTIMER_ADCTRIGS2A(hrtimery)                 REG32(((hrtimery) + 0x00000380U) + 0x0000011CU)                              /*!< HRTIMER trigger source 2 to ADC add register */
#define HRTIMER_ADCTRIGS3A(hrtimery)                 REG32(((hrtimery) + 0x00000380U) + 0x00000120U)                              /*!< HRTIMER trigger source 3 to ADC add register */

/* bits definitions */
/* Master_TIMER registers */
/* HRTIMER_MTCTL0 */
#define HRTIMER_MTCTL0_CNTCKDIV2_0                    BITS(0,2)            /*!< counter clock division */
#define HRTIMER_MTCTL0_CTNM                           BIT(3)               /*!< continuous mode */
#define HRTIMER_MTCTL0_CNTRSTM                        BIT(4)               /*!< counter reset mode */
#define HRTIMER_MTCTL0_HALFM                          BIT(5)               /*!< half mode */
#define HRTIMER_MTCTL0_ALTM                           BITS(6,7)            /*!< alternate mode */
#define HRTIMER_MTCTL0_SYNISRC                        BITS(8,9)            /*!< synchronization input source */
#define HRTIMER_MTCTL0_SYNIRST                        BIT(10)              /*!< synchronization input reset counter */
#define HRTIMER_MTCTL0_SYNISTRT                       BIT(11)              /*!< synchronization input start counter */
#define HRTIMER_MTCTL0_SYNOPLS                        BITS(12,13)          /*!< synchronization output pulse */
#define HRTIMER_MTCTL0_SYNOSRC                        BITS(14,15)          /*!< synchronization output source */
#define HRTIMER_MTCTL0_MTCEN                          BIT(16)              /*!< the counter of Master_TIMER enable */
#define HRTIMER_MTCTL0_ST0CEN                         BIT(17)              /*!< the counter of Slave_TIMER0 enable */
#define HRTIMER_MTCTL0_ST1CEN                         BIT(18)              /*!< the counter of Slave_TIMER1 enable */
#define HRTIMER_MTCTL0_ST2CEN                         BIT(19)              /*!< the counter of Slave_TIMER2 enable */
#define HRTIMER_MTCTL0_ST3CEN                         BIT(20)              /*!< the counter of Slave_TIMER3 enable */
#define HRTIMER_MTCTL0_ST4CEN                         BIT(21)              /*!< the counter of Slave_TIMER4 enable */
#define HRTIMER_MTCTL0_ST5CEN                         BIT(22)              /*!< the counter of Slave_TIMER5 enable */
#define HRTIMER_MTCTL0_ST6CEN                         BIT(23)              /*!< the counter of Slave_TIMER6 enable */
#define HRTIMER_MTCTL0_ST7CEN                         BIT(24)              /*!< the counter of Slave_TIMER7 enable */
#define HRTIMER_MTCTL0_DACTRGS                        BITS(25,26)          /*!< trigger source to DAC */
#define HRTIMER_MTCTL0_SHWEN                          BIT(27)              /*!< shadow registers enable */
#define HRTIMER_MTCTL0_UPREP                          BIT(29)              /*!< update event generated by repetition event */
#define HRTIMER_MTCTL0_UPSEL                          BITS(30,31)          /*!< update event selection */

/* HRTIMER_MTINTF */
#define HRTIMER_MTINTF_CMP0IF                         BIT(0)               /*!< compare 0 interrupt flag */
#define HRTIMER_MTINTF_CMP1IF                         BIT(1)               /*!< compare 1 interrupt flag */
#define HRTIMER_MTINTF_CMP2IF                         BIT(2)               /*!< compare 2 interrupt flag */
#define HRTIMER_MTINTF_CMP3IF                         BIT(3)               /*!< compare 3 interrupt flag */
#define HRTIMER_MTINTF_REPIF                          BIT(4)               /*!< repetition interrupt flag */
#define HRTIMER_MTINTF_SYNIIF                         BIT(5)               /*!< synchronization input interrupt flag */
#define HRTIMER_MTINTF_UPIF                           BIT(6)               /*!< update interrupt flag */

/* HRTIMER_MTINTC */
#define HRTIMER_MTINTC_CMP0IFC                        BIT(0)               /*!< clear compare 0 interrupt flag */
#define HRTIMER_MTINTC_CMP1IFC                        BIT(1)               /*!< clear compare 1 interrupt flag */
#define HRTIMER_MTINTC_CMP2IFC                        BIT(2)               /*!< clear compare 2 interrupt flag */
#define HRTIMER_MTINTC_CMP3IFC                        BIT(3)               /*!< clear compare 3 interrupt flag */
#define HRTIMER_MTINTC_REPIFC                         BIT(4)               /*!< clear repetition interrupt flag */
#define HRTIMER_MTINTC_SYNIIFC                        BIT(5)               /*!< clear synchronization input interrupt flag */
#define HRTIMER_MTINTC_UPIFC                          BIT(6)               /*!< clear update interrupt flag */

/* HRTIMER_MTDMAINTEN */
#define HRTIMER_MTDMAINTEN_CMP0IE                     BIT(0)               /*!< compare 0 interrupt enable */
#define HRTIMER_MTDMAINTEN_CMP1IE                     BIT(1)               /*!< compare 1 interrupt enable */
#define HRTIMER_MTDMAINTEN_CMP2IE                     BIT(2)               /*!< compare 2 interrupt enable */
#define HRTIMER_MTDMAINTEN_CMP3IE                     BIT(3)               /*!< compare 3 interrupt enable */
#define HRTIMER_MTDMAINTEN_REPIE                      BIT(4)               /*!< repetition interrupt enable */
#define HRTIMER_MTDMAINTEN_SYNIIE                     BIT(5)               /*!< synchronization input interrupt enable */
#define HRTIMER_MTDMAINTEN_UPIE                       BIT(6)               /*!< update interrupt enable */
#define HRTIMER_MTDMAINTEN_CMP0DEN                    BIT(16)              /*!< compare 0 DMA request enable */
#define HRTIMER_MTDMAINTEN_CMP1DEN                    BIT(17)              /*!< compare 1 DMA request enable */
#define HRTIMER_MTDMAINTEN_CMP2DEN                    BIT(18)              /*!< compare 2 DMA request enable */
#define HRTIMER_MTDMAINTEN_CMP3DEN                    BIT(19)              /*!< compare 3 DMA request enable */
#define HRTIMER_MTDMAINTEN_REPDEN                     BIT(20)              /*!< repetition DMA request enable */
#define HRTIMER_MTDMAINTEN_SYNIDEN                    BIT(21)              /*!< synchronization input DMA request enable */
#define HRTIMER_MTDMAINTEN_UPDEN                      BIT(22)              /*!< update DMA request enable */

/* HRTIMER_MTCNT */
#define HRTIMER_MTCNT_CNT                             BITS(0,15)           /*!< the current counter value */

/* HRTIMER_MTCAR */
#define HRTIMER_MTCAR_CARL                            BITS(0,15)           /*!< counter auto reload value */

/* HRTIMER_MTCREP */
#define HRTIMER_MTCREP_CREP                           BITS(0,7)            /*!< counter repetition value */

/* HRTIMER_MTCMP0V */
#define HRTIMER_MTCMP0V_CMP0VAL                       BITS(0,15)           /*!< compare 0 value */

/* HRTIMER_MTCMP1V */
#define HRTIMER_MTCMP1V_CMP1VAL                       BITS(0,15)           /*!< compare 1 value */

/* HRTIMER_MTCMP2V */
#define HRTIMER_MTCMP2V_CMP2VAL                       BITS(0,15)           /*!< compare 2 value */

/* HRTIMER_MTCMP3V */
#define HRTIMER_MTCMP3V_CMP3VAL                       BITS(0,15)           /*!< compare 3 value */

/* Slave_TIMERx registers(x=0..7) */
/* HRTIMER_STxCTL0 */
#define HRTIMER_STXCTL0_CNTCKDIV2_0                   BITS(0,2)            /*!< counter clock division */
#define HRTIMER_STXCTL0_CTNM                          BIT(3)               /*!< continuous mode */
#define HRTIMER_STXCTL0_CNTRSTM                       BIT(4)               /*!< counter reset mode */
#define HRTIMER_STXCTL0_HALFM                         BIT(5)               /*!< half mode */
#define HRTIMER_STXCTL0_BLNMEN                        BIT(6)               /*!< balanced mode enable */
#define HRTIMER_STXCTL0_ALTM                          BITS(7,8)            /*!< alternate mode enable */
#define HRTIMER_STXCTL0_RSYNUPD                       BIT(9)               /*!< re-synchronized update */
#define HRTIMER_STXCTL0_SYNIRST                       BIT(10)              /*!< synchronization input reset counter */
#define HRTIMER_STXCTL0_SYNISTRT                      BIT(11)              /*!< synchronization input start counter */
#define HRTIMER_STXCTL0_DELCMP1M                      BITS(12,13)          /*!< compare 1 delayed mode */
#define HRTIMER_STXCTL0_DELCMP3M                      BITS(14,15)          /*!< compare 3 delayed mode */
#define HRTIMER_STXCTL0_UPBST5                        BIT(16)              /*!< update by Slave_TIMER5 update event */
#define HRTIMER_STXCTL0_UPREP                         BIT(17)              /*!< update event generated by repetition event */
#define HRTIMER_STXCTL0_UPRST                         BIT(18)              /*!< update event generated by reset event */
#define HRTIMER_STXCTL0_UPBST0                        BIT(19)              /*!< update by Slave_TIMER0 update event */
#define HRTIMER_STXCTL0_UPBST1                        BIT(20)              /*!< update by Slave_TIMER1 update event */
#define HRTIMER_STXCTL0_UPBST2                        BIT(21)              /*!< update by Slave_TIMER2 update event */
#define HRTIMER_STXCTL0_UPBST3                        BIT(22)              /*!< update by Slave_TIMER3 update event */
#define HRTIMER_STXCTL0_UPBST4                        BIT(23)              /*!< update by Slave_TIMER4 update event */
#define HRTIMER_STXCTL0_UPBMT                         BIT(24)              /*!< update by Master_TIMER update event */
#define HRTIMER_STXCTL0_DACTRGS                       BITS(25,26)          /*!< trigger source to DAC */
#define HRTIMER_STXCTL0_SHWEN                         BIT(27)              /*!< shadow registers enable */
#define HRTIMER_STXCTL0_UPSEL                         BITS(28,31)          /*!< update event selection */

/* HRTIMER_STxINTF */
#define HRTIMER_STXINTF_CMP0IF                        BIT(0)               /*!< compare 0 interrupt flag */
#define HRTIMER_STXINTF_CMP1IF                        BIT(1)               /*!< compare 1 interrupt flag */
#define HRTIMER_STXINTF_CMP2IF                        BIT(2)               /*!< compare 2 interrupt flag */
#define HRTIMER_STXINTF_CMP3IF                        BIT(3)               /*!< compare 3 interrupt flag */
#define HRTIMER_STXINTF_REPIF                         BIT(4)               /*!< repetition interrupt flag */
#define HRTIMER_STXINTF_UPIF                          BIT(6)               /*!< update interrupt flag */
#define HRTIMER_STXINTF_CAP0IF                        BIT(7)               /*!< capture 0 interrupt flag */
#define HRTIMER_STXINTF_CAP1IF                        BIT(8)               /*!< capture 1 interrupt flag */
#define HRTIMER_STXINTF_CH0OAIF                       BIT(9)               /*!< channel 0 output active interrupt flag */
#define HRTIMER_STXINTF_CH0ONAIF                      BIT(10)              /*!< channel 0 output inactive interrupt flag */
#define HRTIMER_STXINTF_CH1OAIF                       BIT(11)              /*!< channel 1 output active interrupt flag */
#define HRTIMER_STXINTF_CH1ONAIF                      BIT(12)              /*!< channel 1 output inactive interrupt flag */
#define HRTIMER_STXINTF_RSTIF                         BIT(13)              /*!< counter reset interrupt flag */
#define HRTIMER_STXINTF_DLYIIF                        BIT(14)              /*!< delayed IDLE mode entry interrupt flag */
#define HRTIMER_STXINTF_CBLNF                         BIT(16)              /*!< current balanced flag */
#define HRTIMER_STXINTF_BLNIF                         BIT(17)              /*!< balanced IDLE flag */
#define HRTIMER_STXINTF_CH0SF                         BIT(18)              /*!< channel 0 output state flag */
#define HRTIMER_STXINTF_CH1SF                         BIT(19)              /*!< channel 1 output state flag */
#define HRTIMER_STXINTF_CH0F                          BIT(20)              /*!< channel 0 output flag */
#define HRTIMER_STXINTF_CH1F                          BIT(21)              /*!< channel 1 output flag */
#define HRTIMER_STXINTF_DIR                           BIT(31)              /*!< count direction */

/* HRTIMER_STxINTC */
#define HRTIMER_STXINTC_CMP0IFC                       BIT(0)               /*!< clear compare 0 interrupt flag */
#define HRTIMER_STXINTC_CMP1IFC                       BIT(1)               /*!< clear compare 1 interrupt flag */
#define HRTIMER_STXINTC_CMP2IFC                       BIT(2)               /*!< clear compare 2 interrupt flag */
#define HRTIMER_STXINTC_CMP3IFC                       BIT(3)               /*!< clear compare 3 interrupt flag */
#define HRTIMER_STXINTC_REPIFC                        BIT(4)               /*!< clear repetition interrupt flag */
#define HRTIMER_STXINTC_UPIFC                         BIT(6)               /*!< clear update interrupt flag */
#define HRTIMER_STXINTC_CAP0IFC                       BIT(7)               /*!< clear capture 0 interrupt flag */
#define HRTIMER_STXINTC_CAP1IFC                       BIT(8)               /*!< clear capture 1 interrupt flag */
#define HRTIMER_STXINTC_CH0OAIFC                      BIT(9)               /*!< clear channel 0 output active interrupt flag */
#define HRTIMER_STXINTC_CH0ONAIFC                     BIT(10)              /*!< clear channel 0 output inactive interrupt flag */
#define HRTIMER_STXINTC_CH1OAIFC                      BIT(11)              /*!< clear channel 1 output active interrupt flag */
#define HRTIMER_STXINTC_CH1ONAIFC                     BIT(12)              /*!< clear channel 1 output inactive interrupt flag */
#define HRTIMER_STXINTC_RSTIFC                        BIT(13)              /*!< clear counter reset interrupt flag */
#define HRTIMER_STXINTC_DLYIIFC                       BIT(14)              /*!< clear delayed IDLE mode entry interrupt flag */

/* HRTIMER_STxDMAINTEN */
#define HRTIMER_STXDMAINTEN_CMP0IE                    BIT(0)               /*!< compare 0 interrupt enable */
#define HRTIMER_STXDMAINTEN_CMP1IE                    BIT(1)               /*!< compare 1 interrupt enable */
#define HRTIMER_STXDMAINTEN_CMP2IE                    BIT(2)               /*!< compare 2 interrupt enable */
#define HRTIMER_STXDMAINTEN_CMP3IE                    BIT(3)               /*!< compare 3 interrupt enable */
#define HRTIMER_STXDMAINTEN_REPIE                     BIT(4)               /*!< repetition interrupt enable */
#define HRTIMER_STXDMAINTEN_UPIE                      BIT(6)               /*!< update interrupt enable */
#define HRTIMER_STXDMAINTEN_CAP0IE                    BIT(7)               /*!< capture 0 interrupt enable */
#define HRTIMER_STXDMAINTEN_CAP1IE                    BIT(8)               /*!< capture 1 interrupt enable */
#define HRTIMER_STXDMAINTEN_CH0OAIE                   BIT(9)               /*!< channel 0 output active interrupt enable */
#define HRTIMER_STXDMAINTEN_CH0ONAIE                  BIT(10)              /*!< channel 0 output inactive interrupt enable */
#define HRTIMER_STXDMAINTEN_CH1OAIE                   BIT(11)              /*!< channel 1 output active interrupt enable */
#define HRTIMER_STXDMAINTEN_CH1ONAIE                  BIT(12)              /*!< channel 1 output inactive interrupt enable */
#define HRTIMER_STXDMAINTEN_RSTIE                     BIT(13)              /*!< counter reset interrupt enable */
#define HRTIMER_STXDMAINTEN_DLYIIE                    BIT(14)              /*!< delayed IDLE mode entry interrupt enable */
#define HRTIMER_STXDMAINTEN_CMP0DEN                   BIT(16)              /*!< compare 0 DMA request enable */
#define HRTIMER_STXDMAINTEN_CMP1DEN                   BIT(17)              /*!< compare 1 DMA request enable */
#define HRTIMER_STXDMAINTEN_CMP2DEN                   BIT(18)              /*!< compare 2 DMA request enable */
#define HRTIMER_STXDMAINTEN_CMP3DEN                   BIT(19)              /*!< compare 3 DMA request enable */
#define HRTIMER_STXDMAINTEN_REPDEN                    BIT(20)              /*!< repetition DMA request enable */
#define HRTIMER_STXDMAINTEN_UPDEN                     BIT(22)              /*!< update DMA request enable */
#define HRTIMER_STXDMAINTEN_CAP0DEN                   BIT(23)              /*!< capture 0 DMA request enable */
#define HRTIMER_STXDMAINTEN_CAP1DEN                   BIT(24)              /*!< capture 1 DMA request enable */
#define HRTIMER_STXDMAINTEN_CH0OADEN                  BIT(25)              /*!< channel 0 output active DMA request enable */
#define HRTIMER_STXDMAINTEN_CH0ONADEN                 BIT(26)              /*!< channel 0 output inactive DMA request enable */
#define HRTIMER_STXDMAINTEN_CH1OADEN                  BIT(27)              /*!< channel 1 output active DMA request enable */
#define HRTIMER_STXDMAINTEN_CH1ONADEN                 BIT(28)              /*!< channel 1 output inactive DMA request enable */
#define HRTIMER_STXDMAINTEN_RSTDEN                    BIT(29)              /*!< counter reset DMA request enable */
#define HRTIMER_STXDMAINTEN_DLYIDEN                   BIT(30)              /*!< delayed IDLE mode entry DMA request enable */

/* HRTIMER_STxCNT */
#define HRTIMER_STXCNT_CNT                            BITS(0,15)           /*!< the current counter value */

/* HRTIMER_STxCAR */
#define HRTIMER_STXCAR_CARL                           BITS(0,15)           /*!< counter auto reload value */

/* HRTIMER_STxCREP */
#define HRTIMER_STXCREP_CREP                          BITS(0,7)            /*!< counter repetition value */

/* HRTIMER_STxCMP0V */
#define HRTIMER_STXCMP0V_CMP0VAL                      BITS(0,15)           /*!< compare 0 value */

/* HRTIMER_STxCMP0CP */
#define HRTIMER_STXCMP0CP_CMP0VAL                     BITS(0,15)           /*!< compare 0 value */
#define HRTIMER_STXCMP0CP_CREP                        BITS(16,23)          /*!< counter repetition value */

/* HRTIMER_STxCMP1V */
#define HRTIMER_STXCMP1V_CMP1VAL                      BITS(0,15)           /*!< compare 1 value */

/* HRTIMER_STxCMP2V */
#define HRTIMER_STXCMP2V_CMP2VAL                      BITS(0,15)           /*!< compare 2 value */

/* HRTIMER_STxCMP3V */
#define HRTIMER_STXCMP3V_CMP3VAL                      BITS(0,15)           /*!< compare 3 value */

/* HRTIMER_STxCAP0V */
#define HRTIMER_STXCAP0V_CAP0VAL                      BITS(0,15)           /*!< capture 0 value */
#define HRTIMER_STXCAP0V_DIR                          BIT(16)              /*!< capture 0 direction status */

/* HRTIMER_STxCAP1V */
#define HRTIMER_STXCAP1V_CAP1VAL                      BITS(0,15)           /*!< capture 1 value */
#define HRTIMER_STXCAP1V_DIR                          BIT(16)              /*!< capture 1 direction status */

/* HRTIMER_STxDTCTL */
#define HRTIMER_STXDTCTL_DTRCFG8_0                    BITS(0,8)            /*!< rising edge dead-time value */
#define HRTIMER_STXDTCTL_DTRS                         BIT(9)               /*!< the sign of rising edge dead-time value */
#define HRTIMER_STXDTCTL_DTGCKDIV                     BITS(10,13)          /*!< dead time generator clock division */
#define HRTIMER_STXDTCTL_DTRSPROT                     BIT(14)              /*!< dead-time rising edge protection for sign */
#define HRTIMER_STXDTCTL_DTRSVPROT                    BIT(15)              /*!< dead-time rising edge protection for value and sign */
#define HRTIMER_STXDTCTL_DTFCFG8_0                    BITS(16,24)          /*!< falling edge dead-time value */
#define HRTIMER_STXDTCTL_DTFS                         BIT(25)              /*!< the sign of falling edge dead-time value */
#define HRTIMER_STXDTCTL_DTFSPROT                     BIT(30)              /*!< dead-time falling edge protection for sign */
#define HRTIMER_STXDTCTL_DTFSVPROT                    BIT(31)              /*!< dead-time falling edge protection for value and sign */

/* HRTIMER_STxCH0SET */
#define HRTIMER_STXCH0SET_CH0SSEV                     BIT(0)               /*!< software event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SRST                     BIT(1)               /*!< Slave_TIMERx reset event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SPER                     BIT(2)               /*!< Slave_TIMERx period event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SCMP0                    BIT(3)               /*!< Slave_TIMERx compare 0 event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SCMP1                    BIT(4)               /*!< Slave_TIMERx compare 1 event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SCMP2                    BIT(5)               /*!< Slave_TIMERx compare 2 event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SCMP3                    BIT(6)               /*!< Slave_TIMERx compare 3 event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SMTPER                   BIT(7)               /*!< Master_TIMER period event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SMTCMP0                  BIT(8)               /*!< Master_TIMER compare 0 event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SMTCMP1                  BIT(9)               /*!< Master_TIMER compare 1 event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SMTCMP2                  BIT(10)              /*!< Master_TIMER compare 2 event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SMTCMP3                  BIT(11)              /*!< Master_TIMER compare 3 event generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SSTEV0                   BIT(12)              /*!< Slave_TIMERx interconnection event 0 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SSTEV1                   BIT(13)              /*!< Slave_TIMERx interconnection event 1 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SSTEV2                   BIT(14)              /*!< Slave_TIMERx interconnection event 2 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SSTEV3                   BIT(15)              /*!< Slave_TIMERx interconnection event 3 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SSTEV4                   BIT(16)              /*!< Slave_TIMERx interconnection event 4 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SSTEV5                   BIT(17)              /*!< Slave_TIMERx interconnection event 5 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SSTEV6                   BIT(18)              /*!< Slave_TIMERx interconnection event 6 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SSTEV7                   BIT(19)              /*!< Slave_TIMERx interconnection event 7 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SSTEV8                   BIT(20)              /*!< Slave_TIMERx interconnection event 8 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SEXEV0                   BIT(21)              /*!< external event 0 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SEXEV1                   BIT(22)              /*!< external event 1 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SEXEV2                   BIT(23)              /*!< external event 2 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SEXEV3                   BIT(24)              /*!< external event 3 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SEXEV4                   BIT(25)              /*!< external event 4 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SEXEV5                   BIT(26)              /*!< external event 5 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SEXEV6                   BIT(27)              /*!< external event 6 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SEXEV7                   BIT(28)              /*!< external event 7 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SEXEV8                   BIT(29)              /*!< external event 8 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SEXEV9                   BIT(30)              /*!< external event 9 generates channel 0 set request */
#define HRTIMER_STXCH0SET_CH0SUP                      BIT(31)              /*!< update event generates channel 0 set request */

/* HRTIMER_STxCH0RST */
#define HRTIMER_STXCH0RST_CH0RSSEV                    BIT(0)               /*!< software event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSRST                    BIT(1)               /*!< Slave_TIMERx reset event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSPER                    BIT(2)               /*!< Slave_TIMERx period event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSCMP0                   BIT(3)               /*!< Slave_TIMERx compare 0 event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSCMP1                   BIT(4)               /*!< Slave_TIMERx compare 1 event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSCMP2                   BIT(5)               /*!< Slave_TIMERx compare 2 event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSCMP3                   BIT(6)               /*!< Slave_TIMERx compare 3 event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSMTPER                  BIT(7)               /*!< Master_TIMER period event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSMTCMP0                 BIT(8)               /*!< Master_TIMER compare 0 event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSMTCMP1                 BIT(9)               /*!< Master_TIMER compare 1 event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSMTCMP2                 BIT(10)              /*!< Master_TIMER compare 2 event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSMTCMP3                 BIT(11)              /*!< Master_TIMER compare 3 event generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSSTEV0                  BIT(12)              /*!< Slave_TIMERx interconnection event 0 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSSTEV1                  BIT(13)              /*!< Slave_TIMERx interconnection event 1 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSSTEV2                  BIT(14)              /*!< Slave_TIMERx interconnection event 2 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSSTEV3                  BIT(15)              /*!< Slave_TIMERx interconnection event 3 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSSTEV4                  BIT(16)              /*!< Slave_TIMERx interconnection event 4 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSSTEV5                  BIT(17)              /*!< Slave_TIMERx interconnection event 5 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSSTEV6                  BIT(18)              /*!< Slave_TIMERx interconnection event 6 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSSTEV7                  BIT(19)              /*!< Slave_TIMERx interconnection event 7 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSSTEV8                  BIT(20)              /*!< Slave_TIMERx interconnection event 8 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSEXEV0                  BIT(21)              /*!< external event 0 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSEXEV1                  BIT(22)              /*!< external event 1 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSEXEV2                  BIT(23)              /*!< external event 2 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSEXEV3                  BIT(24)              /*!< external event 3 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSEXEV4                  BIT(25)              /*!< external event 4 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSEXEV5                  BIT(26)              /*!< external event 5 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSEXEV6                  BIT(27)              /*!< external event 6 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSEXEV7                  BIT(28)              /*!< external event 7 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSEXEV8                  BIT(29)              /*!< external event 8 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSEXEV9                  BIT(30)              /*!< external event 9 generates channel 0 reset request */
#define HRTIMER_STXCH0RST_CH0RSUP                     BIT(31)              /*!< update event generates channel 0 reset request */

/* HRTIMER_STxCH1SET */
#define HRTIMER_STXCH1SET_CH1SSEV                     BIT(0)               /*!< software event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SRST                     BIT(1)               /*!< Slave_TIMERx reset event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SPER                     BIT(2)               /*!< Slave_TIMERx period event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SCMP0                    BIT(3)               /*!< Slave_TIMERx compare 0 event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SCMP1                    BIT(4)               /*!< Slave_TIMERx compare 1 event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SCMP2                    BIT(5)               /*!< Slave_TIMERx compare 2 event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SCMP3                    BIT(6)               /*!< Slave_TIMERx compare 3 event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SMTPER                   BIT(7)               /*!< Master_TIMER period event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SMTCMP0                  BIT(8)               /*!< Master_TIMER compare 0 event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SMTCMP1                  BIT(9)               /*!< Master_TIMER compare 1 event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SMTCMP2                  BIT(10)              /*!< Master_TIMER compare 2 event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SMTCMP3                  BIT(11)              /*!< Master_TIMER compare 3 event generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SSTEV0                   BIT(12)              /*!< Slave_TIMERx interconnection event 0 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SSTEV1                   BIT(13)              /*!< Slave_TIMERx interconnection event 1 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SSTEV2                   BIT(14)              /*!< Slave_TIMERx interconnection event 2 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SSTEV3                   BIT(15)              /*!< Slave_TIMERx interconnection event 3 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SSTEV4                   BIT(16)              /*!< Slave_TIMERx interconnection event 4 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SSTEV5                   BIT(17)              /*!< Slave_TIMERx interconnection event 5 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SSTEV6                   BIT(18)              /*!< Slave_TIMERx interconnection event 6 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SSTEV7                   BIT(19)              /*!< Slave_TIMERx interconnection event 7 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SSTEV8                   BIT(20)              /*!< Slave_TIMERx interconnection event 8 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SEXEV0                   BIT(21)              /*!< external event 0 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SEXEV1                   BIT(22)              /*!< external event 1 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SEXEV2                   BIT(23)              /*!< external event 2 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SEXEV3                   BIT(24)              /*!< external event 3 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SEXEV4                   BIT(25)              /*!< external event 4 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SEXEV5                   BIT(26)              /*!< external event 5 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SEXEV6                   BIT(27)              /*!< external event 6 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SEXEV7                   BIT(28)              /*!< external event 7 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SEXEV8                   BIT(29)              /*!< external event 8 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SEXEV9                   BIT(30)              /*!< external event 9 generates channel 1 set request */
#define HRTIMER_STXCH1SET_CH1SUP                      BIT(31)              /*!< update event generates channel 1 set request */

/* HRTIMER_STxCH1RST */
#define HRTIMER_STXCH1RST_CH1RSSEV                    BIT(0)               /*!< software event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSRST                    BIT(1)               /*!< Slave_TIMERx reset event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSPER                    BIT(2)               /*!< Slave_TIMERx period event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSCMP0                   BIT(3)               /*!< Slave_TIMERx compare 0 event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSCMP1                   BIT(4)               /*!< Slave_TIMERx compare 1 event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSCMP2                   BIT(5)               /*!< Slave_TIMERx compare 2 event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSCMP3                   BIT(6)               /*!< Slave_TIMERx compare 3 event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSMTPER                  BIT(7)               /*!< Master_TIMER period event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSMTCMP0                 BIT(8)               /*!< Master_TIMER compare 0 event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSMTCMP1                 BIT(9)               /*!< Master_TIMER compare 1 event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSMTCMP2                 BIT(10)              /*!< Master_TIMER compare 2 event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSMTCMP3                 BIT(11)              /*!< Master_TIMER compare 3 event generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSSTEV0                  BIT(12)              /*!< Slave_TIMERx interconnection event 0 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSSTEV1                  BIT(13)              /*!< Slave_TIMERx interconnection event 1 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSSTEV2                  BIT(14)              /*!< Slave_TIMERx interconnection event 2 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSSTEV3                  BIT(15)              /*!< Slave_TIMERx interconnection event 3 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSSTEV4                  BIT(16)              /*!< Slave_TIMERx interconnection event 4 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSSTEV5                  BIT(17)              /*!< Slave_TIMERx interconnection event 5 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSSTEV6                  BIT(18)              /*!< Slave_TIMERx interconnection event 6 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSSTEV7                  BIT(19)              /*!< Slave_TIMERx interconnection event 7 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSSTEV8                  BIT(20)              /*!< Slave_TIMERx interconnection event 8 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSEXEV0                  BIT(21)              /*!< external event 0 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSEXEV1                  BIT(22)              /*!< external event 1 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSEXEV2                  BIT(23)              /*!< external event 2 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSEXEV3                  BIT(24)              /*!< external event 3 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSEXEV4                  BIT(25)              /*!< external event 4 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSEXEV5                  BIT(26)              /*!< external event 5 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSEXEV6                  BIT(27)              /*!< external event 6 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSEXEV7                  BIT(28)              /*!< external event 7 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSEXEV8                  BIT(29)              /*!< external event 8 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSEXEV9                  BIT(30)              /*!< external event 9 generates channel 1 reset request */
#define HRTIMER_STXCH1RST_CH1RSUP                     BIT(31)              /*!< update event generates channel 1 reset request */

/* HRTIMER_STxEXEVFCFG0 */
#define HRTIMER_STXEXEVFCFG0_EXEV0MEEN                BIT(0)               /*!< external event 0 memory */
#define HRTIMER_STXEXEVFCFG0_EXEV0FM                  BITS(1,5)            /*!< external event 0 filter mode */
#define HRTIMER_STXEXEVFCFG0_EXEV1MEEN                BIT(6)               /*!< external event 1 memory */
#define HRTIMER_STXEXEVFCFG0_EXEV1FM                  BITS(7,11)           /*!< external event 1 filter mode */
#define HRTIMER_STXEXEVFCFG0_EXEV2MEEN                BIT(12)              /*!< external event 2 memory */
#define HRTIMER_STXEXEVFCFG0_EXEV2FM                  BITS(13,17)          /*!< external event 2 filter mode */
#define HRTIMER_STXEXEVFCFG0_EXEV3MEEN                BIT(18)              /*!< external event 3 memory */
#define HRTIMER_STXEXEVFCFG0_EXEV3FM                  BITS(19,23)          /*!< external event 3 filter mode */
#define HRTIMER_STXEXEVFCFG0_EXEV4MEEN                BIT(24)              /*!< external event 4 memory */
#define HRTIMER_STXEXEVFCFG0_EXEV4FM                  BITS(25,29)          /*!< external event 4 filter mode */

/* HRTIMER_STxEXEVFCFG1 */
#define HRTIMER_STXEXEVFCFG1_EXEV5MEEN                BIT(0)               /*!< external event 5 memory */
#define HRTIMER_STXEXEVFCFG1_EXEV5FM                  BITS(1,5)            /*!< external event 5 filter mode */
#define HRTIMER_STXEXEVFCFG1_EXEV6MEEN                BIT(6)               /*!< external event 6 memory */
#define HRTIMER_STXEXEVFCFG1_EXEV6FM                  BITS(7,11)           /*!< external event 6 filter mode */
#define HRTIMER_STXEXEVFCFG1_EXEV7MEEN                BIT(12)              /*!< external event 7 memory */
#define HRTIMER_STXEXEVFCFG1_EXEV7FM                  BITS(13,17)          /*!< external event 7 filter mode */
#define HRTIMER_STXEXEVFCFG1_EXEV8MEEN                BIT(18)              /*!< external event 8 memory */
#define HRTIMER_STXEXEVFCFG1_EXEV8FM                  BITS(19,23)          /*!< external event 8 filter mode */
#define HRTIMER_STXEXEVFCFG1_EXEV9MEEN                BIT(24)              /*!< external event 9 memory */
#define HRTIMER_STXEXEVFCFG1_EXEV9FM                  BITS(25,29)          /*!< external event 9 filter mode */

/* HRTIMER_STxCNTRST */
#define HRTIMER_STXCNTRST_UPRST                       BIT(1)               /*!< Slave_TIMER0 update event resets counter */
#define HRTIMER_STXCNTRST_CMP1RST                     BIT(2)               /*!< Slave_TIMER0 compare 1 event resets counter */
#define HRTIMER_STXCNTRST_CMP3RST                     BIT(3)               /*!< Slave_TIMER0 compare 3 event resets counter */
#define HRTIMER_STXCNTRST_MTPERRST                    BIT(4)               /*!< Master_TIMER period event resets counter */
#define HRTIMER_STXCNTRST_MTCMP0RST                   BIT(5)               /*!< Master_TIMER compare 0 event resets counter */
#define HRTIMER_STXCNTRST_MTCMP1RST                   BIT(6)               /*!< Master_TIMER compare 1 event resets counter */
#define HRTIMER_STXCNTRST_MTCMP2RST                   BIT(7)               /*!< Master_TIMER compare 2 event resets counter */
#define HRTIMER_STXCNTRST_MTCMP3RST                   BIT(8)               /*!< Master_TIMER compare 3 event resets counter */
#define HRTIMER_STXCNTRST_EXEV0RST                    BIT(9)               /*!< external event 0 resets counter */
#define HRTIMER_STXCNTRST_EXEV1RST                    BIT(10)              /*!< external event 1 resets counter */
#define HRTIMER_STXCNTRST_EXEV2RST                    BIT(11)              /*!< external event 2 resets counter */
#define HRTIMER_STXCNTRST_EXEV3RST                    BIT(12)              /*!< external event 3 resets counter */
#define HRTIMER_STXCNTRST_EXEV4RST                    BIT(13)              /*!< external event 4 resets counter */
#define HRTIMER_STXCNTRST_EXEV5RST                    BIT(14)              /*!< external event 5 resets counter */
#define HRTIMER_STXCNTRST_EXEV6RST                    BIT(15)              /*!< external event 6 resets counter */
#define HRTIMER_STXCNTRST_EXEV7RST                    BIT(16)              /*!< external event 7 resets counter */
#define HRTIMER_STXCNTRST_EXEV8RST                    BIT(17)              /*!< external event 8 resets counter */
#define HRTIMER_STXCNTRST_EXEV9RST                    BIT(18)              /*!< external event 9 resets counter */

/* For Slave_TIMER0 */
#define HRTIMER_ST0CNTRST_ST5CMP0RST                  BIT(0)               /*!< Slave_TIMER5 compare 0 event resets counter */
#define HRTIMER_ST0CNTRST_ST1CMP0RST                  BIT(19)              /*!< Slave_TIMER1 compare 0 event resets counter */
#define HRTIMER_ST0CNTRST_ST1CMP1RST                  BIT(20)              /*!< Slave_TIMER1 compare 1 event resets counter */
#define HRTIMER_ST0CNTRST_ST1CMP3RST                  BIT(21)              /*!< Slave_TIMER1 compare 3 event resets counter */
#define HRTIMER_ST0CNTRST_ST2CMP0RST                  BIT(22)              /*!< Slave_TIMER2 compare 0 event resets counter */
#define HRTIMER_ST0CNTRST_ST2CMP1RST                  BIT(23)              /*!< Slave_TIMER2 compare 1 event resets counter */
#define HRTIMER_ST0CNTRST_ST2CMP3RST                  BIT(24)              /*!< Slave_TIMER2 compare 3 event resets counter */
#define HRTIMER_ST0CNTRST_ST3CMP0RST                  BIT(25)              /*!< Slave_TIMER3 compare 0 event resets counter */
#define HRTIMER_ST0CNTRST_ST3CMP1RST                  BIT(26)              /*!< Slave_TIMER3 compare 1 event resets counter */
#define HRTIMER_ST0CNTRST_ST3CMP3RST                  BIT(27)              /*!< Slave_TIMER3 compare 3 event resets counter */
#define HRTIMER_ST0CNTRST_ST4CMP0RST                  BIT(28)              /*!< Slave_TIMER4 compare 0 event resets counter */
#define HRTIMER_ST0CNTRST_ST4CMP1RST                  BIT(29)              /*!< Slave_TIMER4 compare 1 event resets counter */
#define HRTIMER_ST0CNTRST_ST4CMP3RST                  BIT(30)              /*!< Slave_TIMER4 compare 3 event resets counter */
#define HRTIMER_ST0CNTRST_ST5CMP1RST                  BIT(31)              /*!< Slave_TIMER5 compare 1 event resets counter */
/* For Slave_TIMER1 */
#define HRTIMER_ST1CNTRST_ST5CMP0RST                  BIT(0)               /*!< Slave_TIMER5 compare 0 event resets counter */
#define HRTIMER_ST1CNTRST_ST0CMP0RST                  BIT(19)              /*!< Slave_TIMER0 compare 0 event resets counter */
#define HRTIMER_ST1CNTRST_ST0CMP1RST                  BIT(20)              /*!< Slave_TIMER0 compare 1 event resets counter */
#define HRTIMER_ST1CNTRST_ST0CMP3RST                  BIT(21)              /*!< Slave_TIMER0 compare 3 event resets counter */
#define HRTIMER_ST1CNTRST_ST2CMP0RST                  BIT(22)              /*!< Slave_TIMER2 compare 0 event resets counter */
#define HRTIMER_ST1CNTRST_ST2CMP1RST                  BIT(23)              /*!< Slave_TIMER2 compare 1 event resets counter */
#define HRTIMER_ST1CNTRST_ST2CMP3RST                  BIT(24)              /*!< Slave_TIMER2 compare 3 event resets counter */
#define HRTIMER_ST1CNTRST_ST3CMP0RST                  BIT(25)              /*!< Slave_TIMER3 compare 0 event resets counter */
#define HRTIMER_ST1CNTRST_ST3CMP1RST                  BIT(26)              /*!< Slave_TIMER3 compare 1 event resets counter */
#define HRTIMER_ST1CNTRST_ST3CMP3RST                  BIT(27)              /*!< Slave_TIMER3 compare 3 event resets counter */
#define HRTIMER_ST1CNTRST_ST4CMP0RST                  BIT(28)              /*!< Slave_TIMER4 compare 0 event resets counter */
#define HRTIMER_ST1CNTRST_ST4CMP1RST                  BIT(29)              /*!< Slave_TIMER4 compare 1 event resets counter */
#define HRTIMER_ST1CNTRST_ST4CMP3RST                  BIT(30)              /*!< Slave_TIMER4 compare 3 event resets counter */
#define HRTIMER_ST1CNTRST_ST5CMP1RST                  BIT(31)              /*!< Slave_TIMER5 compare 1 event resets counter */
/* For Slave_TIMER2 */
#define HRTIMER_ST2CNTRST_ST5CMP0RST                  BIT(0)               /*!< Slave_TIMER5 compare 0 event resets counter */
#define HRTIMER_ST2CNTRST_ST0CMP0RST                  BIT(19)              /*!< Slave_TIMER0 compare 0 event resets counter */
#define HRTIMER_ST2CNTRST_ST0CMP1RST                  BIT(20)              /*!< Slave_TIMER0 compare 1 event resets counter */
#define HRTIMER_ST2CNTRST_ST0CMP3RST                  BIT(21)              /*!< Slave_TIMER0 compare 3 event resets counter */
#define HRTIMER_ST2CNTRST_ST1CMP0RST                  BIT(22)              /*!< Slave_TIMER1 compare 0 event resets counter */
#define HRTIMER_ST2CNTRST_ST1CMP1RST                  BIT(23)              /*!< Slave_TIMER1 compare 1 event resets counter */
#define HRTIMER_ST2CNTRST_ST1CMP3RST                  BIT(24)              /*!< Slave_TIMER1 compare 3 event resets counter */
#define HRTIMER_ST2CNTRST_ST3CMP0RST                  BIT(25)              /*!< Slave_TIMER3 compare 0 event resets counter */
#define HRTIMER_ST2CNTRST_ST3CMP1RST                  BIT(26)              /*!< Slave_TIMER3 compare 1 event resets counter */
#define HRTIMER_ST2CNTRST_ST3CMP3RST                  BIT(27)              /*!< Slave_TIMER3 compare 3 event resets counter */
#define HRTIMER_ST2CNTRST_ST4CMP0RST                  BIT(28)              /*!< Slave_TIMER4 compare 0 event resets counter */
#define HRTIMER_ST2CNTRST_ST4CMP1RST                  BIT(29)              /*!< Slave_TIMER4 compare 1 event resets counter */
#define HRTIMER_ST2CNTRST_ST4CMP3RST                  BIT(30)              /*!< Slave_TIMER4 compare 3 event resets counter */
#define HRTIMER_ST2CNTRST_ST5CMP1RST                  BIT(31)              /*!< Slave_TIMER5 compare 1 event resets counter */
/* For Slave_TIMER3 */
#define HRTIMER_ST3CNTRST_ST5CMP0RST                  BIT(0)               /*!< Slave_TIMER5 compare 0 event resets counter */
#define HRTIMER_ST3CNTRST_ST0CMP0RST                  BIT(19)              /*!< Slave_TIMER0 compare 0 event resets counter */
#define HRTIMER_ST3CNTRST_ST0CMP1RST                  BIT(20)              /*!< Slave_TIMER0 compare 1 event resets counter */
#define HRTIMER_ST3CNTRST_ST0CMP3RST                  BIT(21)              /*!< Slave_TIMER0 compare 3 event resets counter */
#define HRTIMER_ST3CNTRST_ST1CMP0RST                  BIT(22)              /*!< Slave_TIMER1 compare 0 event resets counter */
#define HRTIMER_ST3CNTRST_ST1CMP1RST                  BIT(23)              /*!< Slave_TIMER1 compare 1 event resets counter */
#define HRTIMER_ST3CNTRST_ST1CMP3RST                  BIT(24)              /*!< Slave_TIMER1 compare 3 event resets counter */
#define HRTIMER_ST3CNTRST_ST2CMP0RST                  BIT(25)              /*!< Slave_TIMER2 compare 0 event resets counter */
#define HRTIMER_ST3CNTRST_ST2CMP1RST                  BIT(26)              /*!< Slave_TIMER2 compare 1 event resets counter */
#define HRTIMER_ST3CNTRST_ST2CMP3RST                  BIT(27)              /*!< Slave_TIMER2 compare 3 event resets counter */
#define HRTIMER_ST3CNTRST_ST4CMP0RST                  BIT(28)              /*!< Slave_TIMER4 compare 0 event resets counter */
#define HRTIMER_ST3CNTRST_ST4CMP1RST                  BIT(29)              /*!< Slave_TIMER4 compare 1 event resets counter */
#define HRTIMER_ST3CNTRST_ST4CMP3RST                  BIT(30)              /*!< Slave_TIMER4 compare 3 event resets counter */
#define HRTIMER_ST3CNTRST_ST5CMP1RST                  BIT(31)              /*!< Slave_TIMER5 compare 1 event resets counter */
/* For Slave_TIMER4 */
#define HRTIMER_ST4CNTRST_ST5CMP0RST                  BIT(0)               /*!< Slave_TIMER5 compare 0 event resets counter */
#define HRTIMER_ST4CNTRST_ST0CMP0RST                  BIT(19)              /*!< Slave_TIMER0 compare 0 event resets counter */
#define HRTIMER_ST4CNTRST_ST0CMP1RST                  BIT(20)              /*!< Slave_TIMER0 compare 1 event resets counter */
#define HRTIMER_ST4CNTRST_ST0CMP3RST                  BIT(21)              /*!< Slave_TIMER0 compare 3 event resets counter */
#define HRTIMER_ST4CNTRST_ST1CMP0RST                  BIT(22)              /*!< Slave_TIMER1 compare 0 event resets counter */
#define HRTIMER_ST4CNTRST_ST1CMP1RST                  BIT(23)              /*!< Slave_TIMER1 compare 1 event resets counter */
#define HRTIMER_ST4CNTRST_ST1CMP3RST                  BIT(24)              /*!< Slave_TIMER1 compare 3 event resets counter */
#define HRTIMER_ST4CNTRST_ST2CMP0RST                  BIT(25)              /*!< Slave_TIMER2 compare 0 event resets counter */
#define HRTIMER_ST4CNTRST_ST2CMP1RST                  BIT(26)              /*!< Slave_TIMER2 compare 1 event resets counter */
#define HRTIMER_ST4CNTRST_ST2CMP3RST                  BIT(27)              /*!< Slave_TIMER2 compare 3 event resets counter */
#define HRTIMER_ST4CNTRST_ST3CMP0RST                  BIT(28)              /*!< Slave_TIMER3 compare 0 event resets counter */
#define HRTIMER_ST4CNTRST_ST3CMP1RST                  BIT(29)              /*!< Slave_TIMER3 compare 1 event resets counter */
#define HRTIMER_ST4CNTRST_ST3CMP3RST                  BIT(30)              /*!< Slave_TIMER3 compare 3 event resets counter */
#define HRTIMER_ST4CNTRST_ST5CMP1RST                  BIT(31)              /*!< Slave_TIMER5 compare 1 event resets counter */

/* For Slave_TIMER5,6,7 */
#define HRTIMER_ST5_6_7CNTRST_ST4CMP0RST              BIT(0)               /*!< Slave_TIMER4 compare 0 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST0CMP0RST              BIT(19)              /*!< Slave_TIMER0 compare 0 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST0CMP1RST              BIT(20)              /*!< Slave_TIMER0 compare 1 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST0CMP3RST              BIT(21)              /*!< Slave_TIMER0 compare 3 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST1CMP0RST              BIT(22)              /*!< Slave_TIMER1 compare 0 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST1CMP1RST              BIT(23)              /*!< Slave_TIMER1 compare 1 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST1CMP3RST              BIT(24)              /*!< Slave_TIMER1 compare 3 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST2CMP0RST              BIT(25)              /*!< Slave_TIMER2 compare 0 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST2CMP1RST              BIT(26)              /*!< Slave_TIMER2 compare 1 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST2CMP3RST              BIT(27)              /*!< Slave_TIMER2 compare 3 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST3CMP0RST              BIT(28)              /*!< Slave_TIMER3 compare 0 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST3CMP1RST              BIT(29)              /*!< Slave_TIMER3 compare 1 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST3CMP3RST              BIT(30)              /*!< Slave_TIMER3 compare 3 event resets counter */
#define HRTIMER_ST5_6_7CNTRST_ST4CMP1RST              BIT(31)              /*!< Slave_TIMER4 compare 1 event resets counter */

/* HRTIMER_STxCSCTL */
#define HRTIMER_STXCSCTL_CSPRD                        BITS(0,3)            /*!< carrier signal period */
#define HRTIMER_STXCSCTL_CSDTY                        BITS(4,6)            /*!< carrier signal duty cycle */
#define HRTIMER_STXCSCTL_CSFSTPW                      BITS(7,10)           /*!< first carrier-signal pulse width */

/* HRTIMER_STxCAP0TRG */
#define HRTIMER_STXCAP0TRG_CP0BSW                     BIT(0)               /*!< capture 0 triggered by software */
#define HRTIMER_STXCAP0TRG_CP0BUP                     BIT(1)               /*!< capture 0 triggered by update event */
#define HRTIMER_STXCAP0TRG_CP0BEXEV0                  BIT(2)               /*!< capture 0 triggered by external event 0 */
#define HRTIMER_STXCAP0TRG_CP0BEXEV1                  BIT(3)               /*!< capture 0 triggered by external event 1 */
#define HRTIMER_STXCAP0TRG_CP0BEXEV2                  BIT(4)               /*!< capture 0 triggered by external event 2 */
#define HRTIMER_STXCAP0TRG_CP0BEXEV3                  BIT(5)               /*!< capture 0 triggered by external event 3 */
#define HRTIMER_STXCAP0TRG_CP0BEXEV4                  BIT(6)               /*!< capture 0 triggered by external event 4 */
#define HRTIMER_STXCAP0TRG_CP0BEXEV5                  BIT(7)               /*!< capture 0 triggered by external event 5 */
#define HRTIMER_STXCAP0TRG_CP0BEXEV6                  BIT(8)               /*!< capture 0 triggered by external event 6 */
#define HRTIMER_STXCAP0TRG_CP0BEXEV7                  BIT(9)               /*!< capture 0 triggered by external event 7 */
#define HRTIMER_STXCAP0TRG_CP0BEXEV8                  BIT(10)              /*!< capture 0 triggered by external event 8 */
#define HRTIMER_STXCAP0TRG_CP0BEXEV9                  BIT(11)              /*!< capture 0 triggered by external event 9 */
#define HRTIMER_STXCAP0TRG_CP0BST0A                   BIT(12)              /*!< capture 0 triggered by ST0CH0_O output inactive to active transition */
#define HRTIMER_STXCAP0TRG_CP0BST0NA                  BIT(13)              /*!< capture 0 triggered by ST0CH0_O output active to inactive transition */
#define HRTIMER_STXCAP0TRG_CP0BST0CMP0                BIT(14)              /*!< capture 0 triggered by compare 0 event of Slave_TIMER0  */
#define HRTIMER_STXCAP0TRG_CP0BST0CMP1                BIT(15)              /*!< capture 0 triggered by compare 1 event of Slave_TIMER0 */
#define HRTIMER_STXCAP0TRG_CP0BST1A                   BIT(16)              /*!< capture 0 triggered by ST1CH0_O output inactive to active transition */
#define HRTIMER_STXCAP0TRG_CP0BST1NA                  BIT(17)              /*!< capture 0 triggered by ST1CH0_O output active to inactive transition */
#define HRTIMER_STXCAP0TRG_CP0BST1CMP0                BIT(18)              /*!< capture 0 triggered by compare 0 event of Slave_TIMER1 */
#define HRTIMER_STXCAP0TRG_CP0BST1CMP1                BIT(19)              /*!< capture 0 triggered by compare 1 event of Slave_TIMER1 */
#define HRTIMER_STXCAP0TRG_CP0BST2A                   BIT(20)              /*!< capture 0 triggered by ST2CH0_O output inactive to active transition */
#define HRTIMER_STXCAP0TRG_CP0BST2NA                  BIT(21)              /*!< capture 0 triggered by ST2CH0_O output active to inactive transition */
#define HRTIMER_STXCAP0TRG_CP0BST2CMP0                BIT(22)              /*!< capture 0 triggered by compare 0 event of Slave_TIMER2 */
#define HRTIMER_STXCAP0TRG_CP0BST2CMP1                BIT(23)              /*!< capture 0 triggered by compare 1 event of Slave_TIMER2 */
#define HRTIMER_STXCAP0TRG_CP0BST3A                   BIT(24)              /*!< capture 0 triggered by ST3CH0_O output inactive to active transition */
#define HRTIMER_STXCAP0TRG_CP0BST3NA                  BIT(25)              /*!< capture 0 triggered by ST3CH0_O output active to inactive transition */
#define HRTIMER_STXCAP0TRG_CP0BST3CMP0                BIT(26)              /*!< capture 0 triggered by compare 0 event of Slave_TIMER3 */
#define HRTIMER_STXCAP0TRG_CP0BST3CMP1                BIT(27)              /*!< capture 0 triggered by compare 1 event of Slave_TIMER3 */
#define HRTIMER_STXCAP0TRG_CP0BST4A                   BIT(28)              /*!< capture 0 triggered by ST4CH0_O output inactive to active transition */
#define HRTIMER_STXCAP0TRG_CP0BST4NA                  BIT(29)              /*!< capture 0 triggered by ST4CH0_O output active to inactive transition. */
#define HRTIMER_STXCAP0TRG_CP0BST4CMP0                BIT(30)              /*!< capture 0 triggered by compare 0 event of Slave_TIMER4 */
#define HRTIMER_STXCAP0TRG_CP0BST4CMP1                BIT(31)              /*!< capture 0 triggered by compare 1 event of Slave_TIMER4 */

/* HRTIMER_STxCAP1TRG */
#define HRTIMER_STXCAP1TRG_CP1BSW                     BIT(0)               /*!< capture 1 triggered by software */
#define HRTIMER_STXCAP1TRG_CP1BUP                     BIT(1)               /*!< capture 1 triggered by update event */
#define HRTIMER_STXCAP1TRG_CP1BEXEV0                  BIT(2)               /*!< capture 1 triggered by external event 0 */
#define HRTIMER_STXCAP1TRG_CP1BEXEV1                  BIT(3)               /*!< capture 1 triggered by external event 1 */
#define HRTIMER_STXCAP1TRG_CP1BEXEV2                  BIT(4)               /*!< capture 1 triggered by external event 2 */
#define HRTIMER_STXCAP1TRG_CP1BEXEV3                  BIT(5)               /*!< capture 1 triggered by external event 3 */
#define HRTIMER_STXCAP1TRG_CP1BEXEV4                  BIT(6)               /*!< capture 1 triggered by external event 4 */
#define HRTIMER_STXCAP1TRG_CP1BEXEV5                  BIT(7)               /*!< capture 1 triggered by external event 5 */
#define HRTIMER_STXCAP1TRG_CP1BEXEV6                  BIT(8)               /*!< capture 1 triggered by external event 6 */
#define HRTIMER_STXCAP1TRG_CP1BEXEV7                  BIT(9)               /*!< capture 1 triggered by external event 7 */
#define HRTIMER_STXCAP1TRG_CP1BEXEV8                  BIT(10)              /*!< capture 1 triggered by external event 8 */
#define HRTIMER_STXCAP1TRG_CP1BEXEV9                  BIT(11)              /*!< capture 1 triggered by external event 9 */
#define HRTIMER_STXCAP1TRG_CP1BST0A                   BIT(12)              /*!< capture 1 triggered by ST0CH0_O output inactive to active transition */
#define HRTIMER_STXCAP1TRG_CP1BST0NA                  BIT(13)              /*!< capture 1 triggered by ST0CH0_O output active to inactive transition */
#define HRTIMER_STXCAP1TRG_CP1BST0CMP0                BIT(14)              /*!< capture 1 triggered by compare 0 event of Slave_TIMER0  */
#define HRTIMER_STXCAP1TRG_CP1BST0CMP1                BIT(15)              /*!< capture 1 triggered by compare 1 event of Slave_TIMER0 */
#define HRTIMER_STXCAP1TRG_CP1BST1A                   BIT(16)              /*!< capture 1 triggered by ST1CH0_O output inactive to active transition */
#define HRTIMER_STXCAP1TRG_CP1BST1NA                  BIT(17)              /*!< capture 1 triggered by ST1CH0_O output active to inactive transition */
#define HRTIMER_STXCAP1TRG_CP1BST1CMP0                BIT(18)              /*!< capture 1 triggered by compare 0 event of Slave_TIMER1 */
#define HRTIMER_STXCAP1TRG_CP1BST1CMP1                BIT(19)              /*!< capture 1 triggered by compare 1 event of Slave_TIMER1 */
#define HRTIMER_STXCAP1TRG_CP1BST2A                   BIT(20)              /*!< capture 1 triggered by ST2CH0_O output inactive to active transition */
#define HRTIMER_STXCAP1TRG_CP1BST2NA                  BIT(21)              /*!< capture 1 triggered by ST2CH0_O output active to inactive transition */
#define HRTIMER_STXCAP1TRG_CP1BST2CMP0                BIT(22)              /*!< capture 1 triggered by compare 0 event of Slave_TIMER2 */
#define HRTIMER_STXCAP1TRG_CP1BST2CMP1                BIT(23)              /*!< capture 1 triggered by compare 1 event of Slave_TIMER2 */
#define HRTIMER_STXCAP1TRG_CP1BST3A                   BIT(24)              /*!< capture 1 triggered by ST3CH0_O output inactive to active transition */
#define HRTIMER_STXCAP1TRG_CP1BST3NA                  BIT(25)              /*!< capture 1 triggered by ST3CH0_O output active to inactive transition */
#define HRTIMER_STXCAP1TRG_CP1BST3CMP0                BIT(26)              /*!< capture 1 triggered by compare 0 event of Slave_TIMER3 */
#define HRTIMER_STXCAP1TRG_CP1BST3CMP1                BIT(27)              /*!< capture 1 triggered by compare 1 event of Slave_TIMER3 */
#define HRTIMER_STXCAP1TRG_CP1BST4A                   BIT(28)              /*!< capture 1 triggered by ST4CH0_O output inactive to active transition */
#define HRTIMER_STXCAP1TRG_CP1BST4NA                  BIT(29)              /*!< capture 1 triggered by ST4CH0_O output active to inactive transition. */
#define HRTIMER_STXCAP1TRG_CP1BST4CMP0                BIT(30)              /*!< capture 1 triggered by compare 0 event of Slave_TIMER4 */
#define HRTIMER_STXCAP1TRG_CP1BST4CMP1                BIT(31)              /*!< capture 1 triggered by compare 1 event of Slave_TIMER4 */

/* HRTIMER_STxCHOCTL */
#define HRTIMER_STXCHOCTL_CH0P                        BIT(1)               /*!< channel 0 output polarity */
#define HRTIMER_STXCHOCTL_BMCH0IEN                    BIT(2)               /*!< channel 0 IDLE state enable in bunch mode */
#define HRTIMER_STXCHOCTL_ISO0                        BIT(3)               /*!< channel 0 output idle state */
#define HRTIMER_STXCHOCTL_CH0FLTOS                    BITS(4,5)            /*!< channel 0 fault output state */
#define HRTIMER_STXCHOCTL_CH0CSEN                     BIT(6)               /*!< channel 0 carrier-signal mode enable */
#define HRTIMER_STXCHOCTL_BMCH0DTI                    BIT(7)               /*!< channel 0 dead-time insert in bunch mode */
#define HRTIMER_STXCHOCTL_DTEN                        BIT(8)               /*!< dead time enable */
#define HRTIMER_STXCHOCTL_DLYISMEN                    BIT(9)               /*!< delayed IDLE state mode enable */
#define HRTIMER_STXCHOCTL_DLYISCH                     BITS(10,12)          /*!< delayed IDLE source and channel */
#define HRTIMER_STXCHOCTL_BALIAR                      BIT(14)              /*!< balanced IDLE automatic resume */
#define HRTIMER_STXCHOCTL_CH1P                        BIT(17)              /*!< channel 1 output polarity */
#define HRTIMER_STXCHOCTL_BMCH1IEN                    BIT(18)              /*!< channel 1 IDLE state enable in bunch mode */
#define HRTIMER_STXCHOCTL_ISO1                        BIT(19)              /*!< channel 1 output idle state */
#define HRTIMER_STXCHOCTL_CH1FLTOS                    BITS(20,21)          /*!< channel 1 fault output state */
#define HRTIMER_STXCHOCTL_CH1CSEN                     BIT(22)              /*!< channel 1 carrier-signal mode enable */
#define HRTIMER_STXCHOCTL_BMCH1DTI                    BIT(23)              /*!< channel 1 dead-time insert in bunch mode */

/* HRTIMER_STxFLTCTL */
#define HRTIMER_STXFLTCTL_FLT0EN                      BIT(0)               /*!< fault 0 enable */
#define HRTIMER_STXFLTCTL_FLT1EN                      BIT(1)               /*!< fault 1 enable */
#define HRTIMER_STXFLTCTL_FLT2EN                      BIT(2)               /*!< fault 2 enable */
#define HRTIMER_STXFLTCTL_FLT3EN                      BIT(3)               /*!< fault 3 enable */
#define HRTIMER_STXFLTCTL_FLT4EN                      BIT(4)               /*!< fault 4 enable */
#define HRTIMER_STXFLTCTL_FLT5EN                      BIT(5)               /*!< fault 5 enable */
#define HRTIMER_STXFLTCTL_FLT6EN                      BIT(6)               /*!< fault 6 enable */
#define HRTIMER_STXFLTCTL_FLT7EN                      BIT(7)               /*!< fault 7 enable */
#define HRTIMER_STXFLTCTL_FLTENPROT                   BIT(31)              /*!< protect fault enable */

/* HRTIMER_STXCTL1 */     
#define HRTIMER_STXCTL1_TRIGEN                        BIT(0)               /*!< two channel trigger enable */
#define HRTIMER_STXCTL1_TRIG0M                        BIT(1)               /*!< two channel TRIG0 trigger */
#define HRTIMER_STXCTL1_TRIG1M                        BIT(2)               /*!< two channel TRIG1 trigger */
#define HRTIMER_STXCTL1_CAM                           BIT(4)               /*!< center-aligned counting mode */
#define HRTIMER_STXCTL1_ROVM                          BITS(6,7)            /*!< roll-over mode */
#define HRTIMER_STXCTL1_OUTROVM                       BITS(8,9)            /*!< output roll-over mode */
#define HRTIMER_STXCTL1_ADCROVM                       BITS(10,11)          /*!< ADC roll-over mode */
#define HRTIMER_STXCTL1_BMROVM                        BITS(12,13)          /*!< bunch mode roll-over mode */
#define HRTIMER_STXCTL1_FEROVM                        BITS(14,15)          /*!< fault and event roll-over mode */
#define HRTIMER_STXCTL1_IMUPD0V                       BIT(16)              /*!< immediately update compare 0 value PWM mode */
#define HRTIMER_STXCTL1_IMUPD2V                       BIT(17)              /*!< immediately update compare 2 value PWM mode */
#define HRTIMER_STXCTL1_TRGHALFM                      BIT(20)              /*!< tiriggered-half mode */

/* HRTIMER_STXEXEVFCFG2 */
#define HRTIMER_STXEXEVFCFG2_EXTEXCEN                 BIT(0)               /*!< external event X counter enable */
#define HRTIMER_STXEXEVFCFG2_EXTEXCRST                BIT(1)               /*!< external event X counter reset */
#define HRTIMER_STXEXEVFCFG2_EXTEXRSTM                BIT(2)               /*!< external event X reset mode */
#define HRTIMER_STXEXEVFCFG2_EXTEXSEL                 BITS(4,7)            /*!< external event X selection */
#define HRTIMER_STXEXEVFCFG2_EXTEXCNTTHR              BITS(8,13)           /*!< external event X counter threshold */
#define HRTIMER_STXEXEVFCFG2_EXTEXCNT                 BITS(26,31)          /*!< external event X counter */

/* HRTIMER_STXCAPTRGCOM */
#define HRTIMER_STXCAPTRGCOM_CP0BST5A                 BIT(0)               /*!< capture 0 triggered by ST5CH0_O output inactive to active transition */
#define HRTIMER_STXCAPTRGCOM_CP0BST5NA                BIT(1)               /*!< capture 0 triggered by ST5CH0_O output active to inactive transition */
#define HRTIMER_STXCAPTRGCOM_CP0BST5CMP0              BIT(2)               /*!< capture 0 triggered by compare 0 event of Slave_TIMER5 */
#define HRTIMER_STXCAPTRGCOM_CP0BST5CMP1              BIT(3)               /*!< capture 0 triggered by compare 1 event of Slave_TIMER5 */
#define HRTIMER_STXCAPTRGCOM_CP0BST6A                 BIT(4)               /*!< capture 0 triggered by ST6CH0_O output inactive to active transition */
#define HRTIMER_STXCAPTRGCOM_CP0BST6NA                BIT(5)               /*!< capture 0 triggered by ST6CH0_O output active to inactive transition */
#define HRTIMER_STXCAPTRGCOM_CP0BST6CMP0              BIT(6)               /*!< capture 0 triggered by compare 0 event of Slave_TIMER6 */
#define HRTIMER_STXCAPTRGCOM_CP0BST6CMP1              BIT(7)               /*!< capture 0 triggered by compare 1 event of Slave_TIMER6 */
#define HRTIMER_STXCAPTRGCOM_CP0BST7A                 BIT(8)               /*!< capture 0 triggered by ST7CH0_O output inactive to active transition */
#define HRTIMER_STXCAPTRGCOM_CP0BST7NA                BIT(9)               /*!< capture 0 triggered by ST7CH0_O output active to inactive transition */
#define HRTIMER_STXCAPTRGCOM_CP0BST7CMP0              BIT(10)              /*!< capture 0 triggered by compare 0 event of Slave_TIMER7 */
#define HRTIMER_STXCAPTRGCOM_CP0BST7CMP1              BIT(11)              /*!< capture 0 triggered by compare 1 event of Slave_TIMER7 */
#define HRTIMER_STXCAPTRGCOM_CP1BST5A                 BIT(16)              /*!< capture 1 triggered by ST5CH0_O output inactive to active transition */
#define HRTIMER_STXCAPTRGCOM_CP1BST5NA                BIT(17)              /*!< capture 1 triggered by ST5CH0_O output active to inactive transition */
#define HRTIMER_STXCAPTRGCOM_CP1BST5CMP0              BIT(18)              /*!< capture 1 triggered by compare 0 event of Slave_TIMER5 */
#define HRTIMER_STXCAPTRGCOM_CP1BST5CMP1              BIT(19)              /*!< capture 1 triggered by compare 1 event of Slave_TIMER5 */
#define HRTIMER_STXCAPTRGCOM_CP1BST6A                 BIT(20)              /*!< capture 1 triggered by ST6CH0_O output inactive to active transition */
#define HRTIMER_STXCAPTRGCOM_CP1BST6NA                BIT(21)              /*!< capture 1 triggered by ST6CH0_O output active to inactive transition */
#define HRTIMER_STXCAPTRGCOM_CP1BST6CMP0              BIT(22)              /*!< capture 1 triggered by compare 0 event of Slave_TIMER6 */
#define HRTIMER_STXCAPTRGCOM_CP1BST6CMP1              BIT(23)              /*!< capture 1 triggered by compare 1 event of Slave_TIMER6 */
#define HRTIMER_STXCAPTRGCOM_CP1BST7A                 BIT(24)              /*!< capture 1 triggered by ST7CH0_O output inactive to active transition */
#define HRTIMER_STXCAPTRGCOM_CP1BST7NA                BIT(25)              /*!< capture 1 triggered by ST7CH0_O output active to inactive transition */
#define HRTIMER_STXCAPTRGCOM_CP1BST7CMP0              BIT(26)              /*!< capture 1 triggered by compare 0 event of Slave_TIMER7 */
#define HRTIMER_STXCAPTRGCOM_CP1BST7CMP1              BIT(27)              /*!< capture 1 triggered by compare 1 event of Slave_TIMER7 */

/* HRTIMER_STxCNTRSTA */  
#define HRTIMER_STxCNTRSTA_CH0SSTEV9                  BIT(16)              /*!< Slave_TIMERx interconnection event 9 generates channel 0 set request */
#define HRTIMER_STxCNTRSTA_CH0SSTEV10                 BIT(17)              /*!< Slave_TIMERx interconnection event 10 generates channel 0 set request */
#define HRTIMER_STxCNTRSTA_CH1SSTEV9                  BIT(18)              /*!< Slave_TIMERx interconnection event 9 generates channel 1 set request */
#define HRTIMER_STxCNTRSTA_CH1SSTEV10                 BIT(19)              /*!< Slave_TIMERx interconnection event 10 generates channel 1 set request */
#define HRTIMER_STxCNTRSTA_CH0SSTCNTRST               BIT(20)              /*!< Slave_TIMERx count reset event generates channel 0 set request */
#define HRTIMER_STxCNTRSTA_CH1SSTCNTRST               BIT(21)              /*!< Slave_TIMERx count reset event generates channel 1 set request */
#define HRTIMER_STxCNTRSTA_CH0RSSTEV9                 BIT(24)              /*!< Slave_TIMERx interconnection event 9 generates channel 0 reset request */
#define HRTIMER_STxCNTRSTA_CH0RSSTEV10                BIT(25)              /*!< Slave_TIMERx interconnection event 10 generates channel 0 reset request */
#define HRTIMER_STxCNTRSTA_CH1RSSTEV9                 BIT(26)              /*!< Slave_TIMERx interconnection event 9 generates channel 1 reset request */
#define HRTIMER_STxCNTRSTA_CH1RSSTEV10                BIT(27)              /*!< Slave_TIMERx interconnection event 10 generates channel 1 reset request */
#define HRTIMER_STxCNTRSTA_CH0RSSTCNTRST              BIT(28)              /*!< Slave_TIMERx count reset event generates channel 0 reset request */
#define HRTIMER_STxCNTRSTA_CH1RSSTCNTRST              BIT(29)              /*!< Slave_TIMERx count reset event generates channel 1 reset request */

/* HRTIMER_ST0CNTRSTA For Slave_TIMER0 */
#define HRTIMER_ST0CNTRSTA_ST5CMP3RST                 BIT(0)               /*!< Slave_TIMER5 compare 3 event resets counter */
#define HRTIMER_ST0CNTRSTA_ST6CMP0RST                 BIT(1)               /*!< Slave_TIMER6 compare 0 event resets counter */
#define HRTIMER_ST0CNTRSTA_ST6CMP1RST                 BIT(2)               /*!< Slave_TIMER6 compare 1 event resets counter */
#define HRTIMER_ST0CNTRSTA_ST6CMP3RST                 BIT(3)               /*!< Slave_TIMER6 compare 3 event resets counter */
#define HRTIMER_ST0CNTRSTA_ST7CMP0RST                 BIT(4)               /*!< Slave_TIMER7 compare 0 event resets counter */
#define HRTIMER_ST0CNTRSTA_ST7CMP1RST                 BIT(5)               /*!< Slave_TIMER7 compare 1 event resets counter */
#define HRTIMER_ST0CNTRSTA_ST7CMP3RST                 BIT(6)               /*!< Slave_TIMER7 compare 3 event resets counter */

/* HRTIMER_ST1CNTRSTA For Slave_TIMER1 */
#define HRTIMER_ST1CNTRSTA_ST5CMP3RST                 BIT(0)               /*!< Slave_TIMER5 compare 3 event resets counter */
#define HRTIMER_ST1CNTRSTA_ST6CMP0RST                 BIT(1)               /*!< Slave_TIMER6 compare 0 event resets counter */
#define HRTIMER_ST1CNTRSTA_ST6CMP1RST                 BIT(2)               /*!< Slave_TIMER6 compare 1 event resets counter */
#define HRTIMER_ST1CNTRSTA_ST6CMP3RST                 BIT(3)               /*!< Slave_TIMER6 compare 3 event resets counter */
#define HRTIMER_ST1CNTRSTA_ST7CMP0RST                 BIT(4)               /*!< Slave_TIMER7 compare 0 event resets counter */
#define HRTIMER_ST1CNTRSTA_ST7CMP1RST                 BIT(5)               /*!< Slave_TIMER7 compare 1 event resets counter */
#define HRTIMER_ST1CNTRSTA_ST7CMP3RST                 BIT(6)               /*!< Slave_TIMER7 compare 3 event resets counter */

/* HRTIMER_ST2CNTRSTA For Slave_TIMER1 */
#define HRTIMER_ST2CNTRSTA_ST5CMP3RST                 BIT(0)               /*!< Slave_TIMER5 compare 3 event resets counter */
#define HRTIMER_ST2CNTRSTA_ST6CMP0RST                 BIT(1)               /*!< Slave_TIMER6 compare 0 event resets counter */
#define HRTIMER_ST2CNTRSTA_ST6CMP1RST                 BIT(2)               /*!< Slave_TIMER6 compare 1 event resets counter */
#define HRTIMER_ST2CNTRSTA_ST6CMP3RST                 BIT(3)               /*!< Slave_TIMER6 compare 3 event resets counter */
#define HRTIMER_ST2CNTRSTA_ST7CMP0RST                 BIT(4)               /*!< Slave_TIMER7 compare 0 event resets counter */
#define HRTIMER_ST2CNTRSTA_ST7CMP1RST                 BIT(5)               /*!< Slave_TIMER7 compare 1 event resets counter */
#define HRTIMER_ST2CNTRSTA_ST7CMP3RST                 BIT(6)               /*!< Slave_TIMER7 compare 3 event resets counter */

/* HRTIMER_ST3CNTRSTA For Slave_TIMER1 */
#define HRTIMER_ST3CNTRSTA_ST5CMP3RST                 BIT(0)               /*!< Slave_TIMER5 compare 3 event resets counter */
#define HRTIMER_ST3CNTRSTA_ST6CMP0RST                 BIT(1)               /*!< Slave_TIMER6 compare 0 event resets counter */
#define HRTIMER_ST3CNTRSTA_ST6CMP1RST                 BIT(2)               /*!< Slave_TIMER6 compare 1 event resets counter */
#define HRTIMER_ST3CNTRSTA_ST6CMP3RST                 BIT(3)               /*!< Slave_TIMER6 compare 3 event resets counter */
#define HRTIMER_ST3CNTRSTA_ST7CMP0RST                 BIT(4)               /*!< Slave_TIMER7 compare 0 event resets counter */
#define HRTIMER_ST3CNTRSTA_ST7CMP1RST                 BIT(5)               /*!< Slave_TIMER7 compare 1 event resets counter */
#define HRTIMER_ST3CNTRSTA_ST7CMP3RST                 BIT(6)               /*!< Slave_TIMER7 compare 3 event resets counter */

/* HRTIMER_ST4CNTRSTA For Slave_TIMER1 */
#define HRTIMER_ST4CNTRSTA_ST5CMP3RST                 BIT(0)               /*!< Slave_TIMER5 compare 3 event resets counter */
#define HRTIMER_ST4CNTRSTA_ST6CMP0RST                 BIT(1)               /*!< Slave_TIMER6 compare 0 event resets counter */
#define HRTIMER_ST4CNTRSTA_ST6CMP1RST                 BIT(2)               /*!< Slave_TIMER6 compare 1 event resets counter */
#define HRTIMER_ST4CNTRSTA_ST6CMP3RST                 BIT(3)               /*!< Slave_TIMER6 compare 3 event resets counter */
#define HRTIMER_ST4CNTRSTA_ST7CMP0RST                 BIT(4)               /*!< Slave_TIMER7 compare 0 event resets counter */
#define HRTIMER_ST4CNTRSTA_ST7CMP1RST                 BIT(5)               /*!< Slave_TIMER7 compare 1 event resets counter */
#define HRTIMER_ST4CNTRSTA_ST7CMP3RST                 BIT(6)               /*!< Slave_TIMER7 compare 3 event resets counter */

/* HRTIMER_ST5CNTRSTA */  
#define HRTIMER_ST5CNTRSTA_ST4CMP3RST                 BIT(0)               /*!< Slave_TIMER4 compare 3 event resets counter */
#define HRTIMER_ST5CNTRSTA_ST6CMP0RST                 BIT(1)               /*!< Slave_TIMER6 compare 0 event resets counter */
#define HRTIMER_ST5CNTRSTA_ST6CMP1RST                 BIT(2)               /*!< Slave_TIMER6 compare 1 event resets counter */
#define HRTIMER_ST5CNTRSTA_ST6CMP3RST                 BIT(3)               /*!< Slave_TIMER6 compare 3 event resets counter */
#define HRTIMER_ST5CNTRSTA_ST7CMP0RST                 BIT(4)               /*!< Slave_TIMER7 compare 0 event resets counter */
#define HRTIMER_ST5CNTRSTA_ST7CMP1RST                 BIT(5)               /*!< Slave_TIMER7 compare 1 event resets counter */
#define HRTIMER_ST5CNTRSTA_ST7CMP3RST                 BIT(6)               /*!< Slave_TIMER7 compare 3 event resets counter */
/* HRTIMER_ST6CNTRSTA */  
#define HRTIMER_ST6CNTRSTA_ST4CMP3RST                 BIT(0)               /*!< Slave_TIMER4 compare 3 event resets counter */
#define HRTIMER_ST6CNTRSTA_ST5CMP0RST                 BIT(1)               /*!< Slave_TIMER5 compare 0 event resets counter */
#define HRTIMER_ST6CNTRSTA_ST5CMP1RST                 BIT(2)               /*!< Slave_TIMER5 compare 1 event resets counter */
#define HRTIMER_ST6CNTRSTA_ST5CMP3RST                 BIT(3)               /*!< Slave_TIMER5 compare 3 event resets counter */
#define HRTIMER_ST6CNTRSTA_ST7CMP0RST                 BIT(4)               /*!< Slave_TIMER7 compare 0 event resets counter */
#define HRTIMER_ST6CNTRSTA_ST7CMP1RST                 BIT(5)               /*!< Slave_TIMER7 compare 1 event resets counter */
#define HRTIMER_ST6CNTRSTA_ST7CMP3RST                 BIT(6)               /*!< Slave_TIMER7 compare 3 event resets counter */
/* HRTIMER_ST7CNTRSTA */  
#define HRTIMER_ST7CNTRSTA_ST4CMP3RST                 BIT(0)               /*!< Slave_TIMER4 compare 3 event resets counter */
#define HRTIMER_ST7CNTRSTA_ST5CMP0RST                 BIT(1)               /*!< Slave_TIMER5 compare 0 event resets counter */
#define HRTIMER_ST7CNTRSTA_ST5CMP1RST                 BIT(2)               /*!< Slave_TIMER5 compare 1 event resets counter */
#define HRTIMER_ST7CNTRSTA_ST5CMP3RST                 BIT(3)               /*!< Slave_TIMER5 compare 3 event resets counter */
#define HRTIMER_ST7CNTRSTA_ST6CMP0RST                 BIT(4)               /*!< Slave_TIMER6 compare 0 event resets counter */
#define HRTIMER_ST7CNTRSTA_ST6CMP1RST                 BIT(5)               /*!< Slave_TIMER6 compare 1 event resets counter */
#define HRTIMER_ST7CNTRSTA_ST6CMP3RST                 BIT(6)               /*!< Slave_TIMER6 compare 3 event resets counter */

/* HRTIMER_STxACTL */
#define HRTIMER_STXACTL_UPBST6                        BIT(0)               /*!< update by Slave_TIMER6 update event */
#define HRTIMER_STXACTL_UPBST7                        BIT(1)               /*!< update by Slave_TIMER7 update event */
#define HRTIMER_STXACTL_DTRCFG15_9                    BITS(9,15)           /*!< rising edge dead-time value configure */
#define HRTIMER_STXACTL_DTFCFG15_9                    BITS(25,31)          /*!< falling edge dead-time value configure */

/* Common registers */
/* HRTIMER_CTL0 */
#define HRTIMER_CTL0_MTUPDIS                          BIT(0)               /*!< Master_TIMER update disable */
#define HRTIMER_CTL0_ST0UPDIS                         BIT(1)               /*!< Slave_TIMER0 update disable */
#define HRTIMER_CTL0_ST1UPDIS                         BIT(2)               /*!< Slave_TIMER1 update disable */
#define HRTIMER_CTL0_ST2UPDIS                         BIT(3)               /*!< Slave_TIMER2 update disable */
#define HRTIMER_CTL0_ST3UPDIS                         BIT(4)               /*!< Slave_TIMER3 update disable */
#define HRTIMER_CTL0_ST4UPDIS                         BIT(5)               /*!< Slave_TIMER4 update disable */
#define HRTIMER_CTL0_ST5UPDIS                         BIT(6)               /*!< Slave_TIMER5 update disable */
#define HRTIMER_CTL0_ST6UPDIS                         BIT(7)               /*!< Slave_TIMER6 update disable */
#define HRTIMER_CTL0_ST7UPDIS                         BIT(8)               /*!< Slave_TIMER7 update disable */
#define HRTIMER_CTL0_ADTG0USRC0_2                     BITS(16,18)          /*!< HRTIMER_ADCTRIG0 update source */
#define HRTIMER_CTL0_ADTG1USRC0_2                     BITS(19,21)          /*!< HRTIMER_ADCTRIG1 update source */
#define HRTIMER_CTL0_ADTG2USRC0_2                     BITS(22,24)          /*!< HRTIMER_ADCTRIG2 update source */
#define HRTIMER_CTL0_ADTG3USRC0_2                     BITS(25,27)          /*!< HRTIMER_ADCTRIG3 update source */
#define HRTIMER_CTL0_ADTG0USRC3                       BIT(28)              /*!< HRTIMER_ADCTRIG0 update source */
#define HRTIMER_CTL0_ADTG1USRC3                       BIT(29)              /*!< HRTIMER_ADCTRIG1 update source */
#define HRTIMER_CTL0_ADTG2USRC3                       BIT(30)              /*!< HRTIMER_ADCTRIG2 update source */
#define HRTIMER_CTL0_ADTG3USRC3                       BIT(31)              /*!< HRTIMER_ADCTRIG3 update source */

/* HRTIMER_CTL1 */
#define HRTIMER_CTL1_MTSUP                            BIT(0)               /*!< Master_TIMER software update */
#define HRTIMER_CTL1_ST0SUP                           BIT(1)               /*!< Slave_TIMER0 software update */
#define HRTIMER_CTL1_ST1SUP                           BIT(2)               /*!< Slave_TIMER1 software update */
#define HRTIMER_CTL1_ST2SUP                           BIT(3)               /*!< Slave_TIMER2 software update */
#define HRTIMER_CTL1_ST3SUP                           BIT(4)               /*!< Slave_TIMER3 software update */
#define HRTIMER_CTL1_ST4SUP                           BIT(5)               /*!< Slave_TIMER4 software update */
#define HRTIMER_CTL1_ST5SUP                           BIT(6)               /*!< Slave_TIMER5 software update */
#define HRTIMER_CTL1_ST6SUP                           BIT(7)               /*!< Slave_TIMER6 software update */
#define HRTIMER_CTL1_MTSRST                           BIT(8)               /*!< Master_TIMER software reset */
#define HRTIMER_CTL1_ST0SRST                          BIT(9)               /*!< Slave_TIMER0 software reset */
#define HRTIMER_CTL1_ST1SRST                          BIT(10)              /*!< Slave_TIMER1 software reset */
#define HRTIMER_CTL1_ST2SRST                          BIT(11)              /*!< Slave_TIMER2 software reset */
#define HRTIMER_CTL1_ST3SRST                          BIT(12)              /*!< Slave_TIMER3 software reset */
#define HRTIMER_CTL1_ST4SRST                          BIT(13)              /*!< Slave_TIMER4 software reset */
#define HRTIMER_CTL1_ST5SRST                          BIT(14)              /*!< Slave_TIMER5 software reset */
#define HRTIMER_CTL1_ST6SRST                          BIT(15)              /*!< Slave_TIMER6 software reset */
#define HRTIMER_CTL1_EXC0                             BIT(16)              /*!< exchange Slave_TIMER0 outputs */
#define HRTIMER_CTL1_EXC1                             BIT(17)              /*!< exchange Slave_TIMER1 outputs */
#define HRTIMER_CTL1_EXC2                             BIT(18)              /*!< exchange Slave_TIMER2 outputs */
#define HRTIMER_CTL1_EXC3                             BIT(19)              /*!< exchange Slave_TIMER3 outputs */
#define HRTIMER_CTL1_EXC4                             BIT(20)              /*!< exchange Slave_TIMER4 outputs */
#define HRTIMER_CTL1_EXC5                             BIT(21)              /*!< exchange Slave_TIMER5 outputs */
#define HRTIMER_CTL1_EXC6                             BIT(22)              /*!< exchange Slave_TIMER6 outputs */
#define HRTIMER_CTL1_EXC7                             BIT(23)              /*!< exchange Slave_TIMER7 outputs */
#define HRTIMER_CTL1_ST7SUP                           BIT(28)              /*!< Slave_TIMER7 software update */
#define HRTIMER_CTL1_ST7SRST                          BIT(29)              /*!< Slave_TIMER7 software reset */

/* HRTIMER_INTF */
#define HRTIMER_INTF_FLT0IF                           BIT(0)               /*!< fault 0 interrupt flag */
#define HRTIMER_INTF_FLT1IF                           BIT(1)               /*!< fault 1 interrupt flag */
#define HRTIMER_INTF_FLT2IF                           BIT(2)               /*!< fault 2 interrupt flag */
#define HRTIMER_INTF_FLT3IF                           BIT(3)               /*!< fault 3 interrupt flag */
#define HRTIMER_INTF_FLT4IF                           BIT(4)               /*!< fault 4 interrupt flag */
#define HRTIMER_INTF_SYSFLTIF                         BIT(5)               /*!< system fault interrupt flag */
#define HRTIMER_INTF_FLT5IF                           BIT(6)               /*!< fault 5 interrupt flag */
#define HRTIMER_INTF_FLT6IF                           BIT(7)               /*!< fault 6 interrupt flag */
#define HRTIMER_INTF_FLT7IF                           BIT(8)               /*!< fault 7 interrupt flag */
#define HRTIMER_INTF_DLLCALIF                         BIT(16)              /*!< DLL calibration completed interrupt flag */
#define HRTIMER_INTF_BMPERIF                          BIT(17)              /*!< bunch mode period interrupt flag */

/* HRTIMER_INTC */
#define HRTIMER_INTC_FLT0IFC                          BIT(0)               /*!< clear fault 0 interrupt flag */
#define HRTIMER_INTC_FLT1IFC                          BIT(1)               /*!< clear fault 1 interrupt flag */
#define HRTIMER_INTC_FLT2IFC                          BIT(2)               /*!< clear fault 2 interrupt flag */
#define HRTIMER_INTC_FLT3IFC                          BIT(3)               /*!< clear fault 3 interrupt flag */
#define HRTIMER_INTC_FLT4IFC                          BIT(4)               /*!< clear fault 4 interrupt flag */
#define HRTIMER_INTC_SYSFLTIFC                        BIT(5)               /*!< clear system fault interrupt flag */
#define HRTIMER_INTC_FLT5IFC                          BIT(6)               /*!< clear fault 5 interrupt flag */
#define HRTIMER_INTC_FLT6IFC                          BIT(7)               /*!< clear fault 6 interrupt flag */
#define HRTIMER_INTC_FLT7IFC                          BIT(8)               /*!< clear fault 7 interrupt flag */
#define HRTIMER_INTC_DLLCALIFC                        BIT(16)              /*!< clear DLL calibration completed interrupt flag */
#define HRTIMER_INTC_BMPERIFC                         BIT(17)              /*!< clear bunch mode period interrupt flag */

/* HRTIMER_INTEN */
#define HRTIMER_INTEN_FLT0IE                          BIT(0)               /*!< fault 0 interrupt enable */
#define HRTIMER_INTEN_FLT1IE                          BIT(1)               /*!< fault 1 interrupt enable */
#define HRTIMER_INTEN_FLT2IE                          BIT(2)               /*!< fault 2 interrupt enable */
#define HRTIMER_INTEN_FLT3IE                          BIT(3)               /*!< fault 3 interrupt enable */
#define HRTIMER_INTEN_FLT4IE                          BIT(4)               /*!< fault 4 interrupt enable */
#define HRTIMER_INTEN_SYSFLTIE                        BIT(5)               /*!< system fault interrupt enable */
#define HRTIMER_INTEN_FLT5IE                          BIT(6)               /*!< fault 5 interrupt enable */
#define HRTIMER_INTEN_FLT6IE                          BIT(7)               /*!< fault 6 interrupt enable */
#define HRTIMER_INTEN_FLT7IE                          BIT(8)               /*!< fault 7 interrupt enable */
#define HRTIMER_INTEN_DLLCALIE                        BIT(16)              /*!< DLL calibration completed interrupt enable */
#define HRTIMER_INTEN_BMPERIE                         BIT(17)              /*!< bunch mode period interrupt enable */

/* HRTIMER_CHOUTEN */
#define HRTIMER_CHOUTEN_ST0CH0EN                      BIT(0)               /*!< Slave_TIMER0 channel 0 output (ST0CH0_O) enable */
#define HRTIMER_CHOUTEN_ST0CH1EN                      BIT(1)               /*!< Slave_TIMER0 channel 1 output (ST0CH1_O) enable */
#define HRTIMER_CHOUTEN_ST1CH0EN                      BIT(2)               /*!< Slave_TIMER1 channel 0 output (ST1CH0_O) enable */
#define HRTIMER_CHOUTEN_ST1CH1EN                      BIT(3)               /*!< Slave_TIMER1 channel 1 output (ST1CH1_O) enable */
#define HRTIMER_CHOUTEN_ST2CH0EN                      BIT(4)               /*!< Slave_TIMER2 channel 0 output (ST2CH0_O) enable */
#define HRTIMER_CHOUTEN_ST2CH1EN                      BIT(5)               /*!< Slave_TIMER2 channel 1 output (ST2CH1_O) enable */
#define HRTIMER_CHOUTEN_ST3CH0EN                      BIT(6)               /*!< Slave_TIMER3 channel 0 output (ST3CH0_O) enable */
#define HRTIMER_CHOUTEN_ST3CH1EN                      BIT(7)               /*!< Slave_TIMER3 channel 1 output (ST3CH1_O) enable */
#define HRTIMER_CHOUTEN_ST4CH0EN                      BIT(8)               /*!< Slave_TIMER4 channel 0 output (ST4CH0_O) enable */
#define HRTIMER_CHOUTEN_ST4CH1EN                      BIT(9)               /*!< Slave_TIMER4 channel 1 output (ST4CH1_O) enable */
#define HRTIMER_CHOUTEN_ST5CH0EN                      BIT(10)              /*!< Slave_TIMER5 channel 0 output (ST5CH0_O) enable */
#define HRTIMER_CHOUTEN_ST5CH1EN                      BIT(11)              /*!< Slave_TIMER5 channel 1 output (ST5CH1_O) enable */
#define HRTIMER_CHOUTEN_ST6CH0EN                      BIT(12)              /*!< Slave_TIMER6 channel 0 output (ST6CH0_O) enable */
#define HRTIMER_CHOUTEN_ST6CH1EN                      BIT(13)              /*!< Slave_TIMER6 channel 1 output (ST6CH1_O) enable */
#define HRTIMER_CHOUTEN_ST7CH0EN                      BIT(14)              /*!< Slave_TIMER7 channel 0 output (ST7CH0_O) enable */
#define HRTIMER_CHOUTEN_ST7CH1EN                      BIT(15)              /*!< Slave_TIMER7 channel 1 output (ST7CH1_O) enable */

/* HRTIMER_CHOUTDIS */
#define HRTIMER_CHOUTDIS_ST0CH0DIS                    BIT(0)               /*!< Slave_TIMER0 channel 0 output (ST0CH0_O) disable */
#define HRTIMER_CHOUTDIS_ST0CH1DIS                    BIT(1)               /*!< Slave_TIMER0 channel 1 output (ST0CH1_O) disable */
#define HRTIMER_CHOUTDIS_ST1CH0DIS                    BIT(2)               /*!< Slave_TIMER1 channel 0 output (ST1CH0_O) disable */
#define HRTIMER_CHOUTDIS_ST1CH1DIS                    BIT(3)               /*!< Slave_TIMER1 channel 1 output (ST1CH1_O) disable */
#define HRTIMER_CHOUTDIS_ST2CH0DIS                    BIT(4)               /*!< Slave_TIMER2 channel 0 output (ST2CH0_O) disable */
#define HRTIMER_CHOUTDIS_ST2CH1DIS                    BIT(5)               /*!< Slave_TIMER2 channel 1 output (ST2CH1_O) disable */
#define HRTIMER_CHOUTDIS_ST3CH0DIS                    BIT(6)               /*!< Slave_TIMER3 channel 0 output (ST3CH0_O) disable */
#define HRTIMER_CHOUTDIS_ST3CH1DIS                    BIT(7)               /*!< Slave_TIMER3 channel 1 output (ST3CH1_O) disable */
#define HRTIMER_CHOUTDIS_ST4CH0DIS                    BIT(8)               /*!< Slave_TIMER4 channel 0 output (ST4CH0_O) disable */
#define HRTIMER_CHOUTDIS_ST4CH1DIS                    BIT(9)               /*!< Slave_TIMER4 channel 1 output (ST4CH1_O) disable */
#define HRTIMER_CHOUTDIS_ST5CH0DIS                    BIT(10)              /*!< Slave_TIMER5 channel 0 output (ST5CH0_O) disable */
#define HRTIMER_CHOUTDIS_ST5CH1DIS                    BIT(11)              /*!< Slave_TIMER5 channel 1 output (ST5CH1_O) disable */
#define HRTIMER_CHOUTDIS_ST6CH0DIS                    BIT(12)              /*!< Slave_TIMER6 channel 0 output (ST6CH0_O) disable */
#define HRTIMER_CHOUTDIS_ST6CH1DIS                    BIT(13)              /*!< Slave_TIMER6 channel 1 output (ST6CH1_O) disable */
#define HRTIMER_CHOUTDIS_ST7CH0DIS                    BIT(14)              /*!< Slave_TIMER7 channel 0 output (ST7CH0_O) disable */
#define HRTIMER_CHOUTDIS_ST7CH1DIS                    BIT(15)              /*!< Slave_TIMER7 channel 1 output (ST7CH1_O) disable */

/* HRTIMER_CHOUTDISF */
#define HRTIMER_CHOUTDISF_ST0CH0DISF                  BIT(0)               /*!< Slave_TIMER0 channel 0 output (ST0CH0_O) disable flag */
#define HRTIMER_CHOUTDISF_ST0CH1DISF                  BIT(1)               /*!< Slave_TIMER0 channel 1 output (ST0CH1_O) disable flag */
#define HRTIMER_CHOUTDISF_ST1CH0DISF                  BIT(2)               /*!< Slave_TIMER1 channel 0 output (ST1CH0_O) disable flag */
#define HRTIMER_CHOUTDISF_ST1CH1DISF                  BIT(3)               /*!< Slave_TIMER1 channel 1 output (ST1CH1_O) disable flag */
#define HRTIMER_CHOUTDISF_ST2CH0DISF                  BIT(4)               /*!< Slave_TIMER2 channel 0 output (ST2CH0_O) disable flag */
#define HRTIMER_CHOUTDISF_ST2CH1DISF                  BIT(5)               /*!< Slave_TIMER2 channel 1 output (ST2CH1_O) disable flag */
#define HRTIMER_CHOUTDISF_ST3CH0DISF                  BIT(6)               /*!< Slave_TIMER3 channel 0 output (ST3CH0_O) disable flag */
#define HRTIMER_CHOUTDISF_ST3CH1DISF                  BIT(7)               /*!< Slave_TIMER3 channel 1 output (ST3CH1_O) disable flag */
#define HRTIMER_CHOUTDISF_ST4CH0DISF                  BIT(8)               /*!< Slave_TIMER4 channel 0 output (ST4CH0_O) disable flag */
#define HRTIMER_CHOUTDISF_ST4CH1DISF                  BIT(9)               /*!< Slave_TIMER4 channel 1 output (ST4CH1_O) disable flag */
#define HRTIMER_CHOUTDISF_ST5CH0DISF                  BIT(10)              /*!< Slave_TIMER5 channel 0 output (ST5CH0_O) disable flag */
#define HRTIMER_CHOUTDISF_ST5CH1DISF                  BIT(11)              /*!< Slave_TIMER5 channel 1 output (ST5CH1_O) disable flag */
#define HRTIMER_CHOUTDISF_ST6CH0DISF                  BIT(12)              /*!< Slave_TIMER6 channel 0 output (ST6CH0_O) disable flag */
#define HRTIMER_CHOUTDISF_ST6CH1DISF                  BIT(13)              /*!< Slave_TIMER6 channel 1 output (ST6CH1_O) disable flag */
#define HRTIMER_CHOUTDISF_ST7CH0DISF                  BIT(14)              /*!< Slave_TIMER7 channel 0 output (ST7CH0_O) disable flag */
#define HRTIMER_CHOUTDISF_ST7CH1DISF                  BIT(15)              /*!< Slave_TIMER7 channel 1 output (ST7CH1_O) disable flag */

/* HRTIMER_BMCTL */
#define HRTIMER_BMCTL_BMEN                            BIT(0)               /*!< bunch mode enable */
#define HRTIMER_BMCTL_BMCTN                           BIT(1)               /*!< continuous mode in bunch mode */
#define HRTIMER_BMCTL_BMCLKS                          BITS(2,5)            /*!< bunch mode clock source */
#define HRTIMER_BMCTL_BMPSC                           BITS(6,9)            /*!< bunch mode clock division */
#define HRTIMER_BMCTL_BMSE                            BIT(10)              /*!< bunch mode shadow enable */
#define HRTIMER_BMCTL_BMMT                            BIT(16)              /*!< Master_TIMER bunch mode */
#define HRTIMER_BMCTL_BMST0                           BIT(17)              /*!< Slave_TIMER0 bunch mode */
#define HRTIMER_BMCTL_BMST1                           BIT(18)              /*!< Slave_TIMER1 bunch mode */
#define HRTIMER_BMCTL_BMST2                           BIT(19)              /*!< Slave_TIMER2 bunch mode */
#define HRTIMER_BMCTL_BMST3                           BIT(20)              /*!< Slave_TIMER3 bunch mode */
#define HRTIMER_BMCTL_BMST4                           BIT(21)              /*!< Slave_TIMER4 bunch mode */
#define HRTIMER_BMCTL_BMST5                           BIT(22)              /*!< Slave_TIMER5 bunch mode */
#define HRTIMER_BMCTL_BMST6                           BIT(23)              /*!< Slave_TIMER6 bunch mode */
#define HRTIMER_BMCTL_BMST7                           BIT(24)              /*!< Slave_TIMER7 bunch mode */
#define HRTIMER_BMCTL_BMOPTF                          BIT(31)              /*!< bunch mode operating flag */

/* HRTIMER_BMSTRG */
#define HRTIMER_BMSTRG_SWTRG                          BIT(0)               /*!< software triggers bunch mode operation */
#define HRTIMER_BMSTRG_MTRST                          BIT(1)               /*!< Master_TIMER reset event triggers bunch mode operation */
#define HRTIMER_BMSTRG_MTREP                          BIT(2)               /*!< Master_TIMER repetition event triggers bunch mode operation */
#define HRTIMER_BMSTRG_MTCMP0                         BIT(3)               /*!< Master_TIMER compare 0 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_MTCMP1                         BIT(4)               /*!< Master_TIMER compare 1 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_MTCMP2                         BIT(5)               /*!< Master_TIMER compare 2 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_MTCMP3                         BIT(6)               /*!< Master_TIMER compare 3 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST0RST                         BIT(7)               /*!< Slave_TIMER0 reset event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST0REP                         BIT(8)               /*!< Slave_TIMER0 repetition event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST0CMP0                        BIT(9)               /*!< Slave_TIMER0 compare 0 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST0CMP1                        BIT(10)              /*!< Slave_TIMER0 compare 1 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST1RST                         BIT(11)              /*!< Slave_TIMER1 reset event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST1REP                         BIT(12)              /*!< Slave_TIMER1 repetition event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST1CMP0                        BIT(13)              /*!< Slave_TIMER1 compare 0 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST1CMP1                        BIT(14)              /*!< Slave_TIMER1 compare 1 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST2RST                         BIT(15)              /*!< Slave_TIMER2 reset event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST2REP                         BIT(16)              /*!< Slave_TIMER2 repetition event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST2CMP0                        BIT(17)              /*!< Slave_TIMER2 compare 0 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST2CMP1                        BIT(18)              /*!< Slave_TIMER2 compare 1 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST3RST                         BIT(19)              /*!< Slave_TIMER3 reset event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST3REP                         BIT(20)              /*!< Slave_TIMER3 repetition event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST3CMP0                        BIT(21)              /*!< Slave_TIMER3 compare 0 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST3CMP1                        BIT(22)              /*!< Slave_TIMER3 compare 1 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST4RST                         BIT(23)              /*!< Slave_TIMER4 reset event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST4REP                         BIT(24)              /*!< Slave_TIMER4 repetition event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST4CMP0                        BIT(25)              /*!< Slave_TIMER4 compare 0 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST4CMP1                        BIT(26)              /*!< Slave_TIMER4 compare 1 event triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST0EXEV6                       BIT(27)              /*!< Slave_TIMER0 period event following external event 6 triggers bunch mode operation */
#define HRTIMER_BMSTRG_ST3EXEV7                       BIT(28)              /*!< Slave_TIMER3 period event following external event 7 triggers bunch mode operation */
#define HRTIMER_BMSTRG_EXEV6                          BIT(29)              /*!< external event 6 triggers bunch mode operation */
#define HRTIMER_BMSTRG_EXEV7                          BIT(30)              /*!< external event 7 triggers bunch mode operation */
#define HRTIMER_BMSTRG_CISGN                          BIT(31)              /*!< chip internal signal triggers bunch mode operation */

/* HRTIMER_BMCMPV */
#define HRTIMER_BMCMPV_BMCMPVAL                       BITS(0,15)           /*!< bunch mode compare value */

/* HRTIMER_BMCAR */
#define HRTIMER_BMCAR_BMCARL                          BITS(0,15)           /*!< bunch mode counter auto reload value */

/* HRTIMER_EXEVCFG0 */
#define HRTIMER_EXEVCFG0_EXEV0SRC                     BITS(0,1)            /*!< external event 0 source */
#define HRTIMER_EXEVCFG0_EXEV0P                       BIT(2)               /*!< external event 0 polarity */
#define HRTIMER_EXEVCFG0_EXEV0EG                      BITS(3,4)            /*!< external event 0 edge sensitivity */
#define HRTIMER_EXEVCFG0_EXEV0FAST                    BIT(5)               /*!< external event 0 fast mode */
#define HRTIMER_EXEVCFG0_EXEV1SRC                     BITS(6,7)            /*!< external event 1 source */
#define HRTIMER_EXEVCFG0_EXEV1P                       BIT(8)               /*!< external event 1 polarity */
#define HRTIMER_EXEVCFG0_EXEV1EG                      BITS(9,10)           /*!< external event 1 edge sensitivity */
#define HRTIMER_EXEVCFG0_EXEV1FAST                    BIT(11)              /*!< external event 1 fast mode */
#define HRTIMER_EXEVCFG0_EXEV2SRC                     BITS(12,13)          /*!< external event 2 source */
#define HRTIMER_EXEVCFG0_EXEV2P                       BIT(14)              /*!< external event 2 polarity */
#define HRTIMER_EXEVCFG0_EXEV2EG                      BITS(15,16)          /*!< external event 2 edge sensitivity */
#define HRTIMER_EXEVCFG0_EXEV2FAST                    BIT(17)              /*!< external event 2 fast mode */
#define HRTIMER_EXEVCFG0_EXEV3SRC                     BITS(18,19)          /*!< external event 3 source */
#define HRTIMER_EXEVCFG0_EXEV3P                       BIT(20)              /*!< external event 3 polarity */
#define HRTIMER_EXEVCFG0_EXEV3EG                      BITS(21,22)          /*!< external event 3 edge sensitivity */
#define HRTIMER_EXEVCFG0_EXEV3FAST                    BIT(17)              /*!< external event 3 fast mode */
#define HRTIMER_EXEVCFG0_EXEV4SRC                     BITS(24,25)          /*!< external event 4 source */
#define HRTIMER_EXEVCFG0_EXEV4P                       BIT(26)              /*!< external event 4 polarity */
#define HRTIMER_EXEVCFG0_EXEV4EG                      BITS(27,28)          /*!< external event 4 edge sensitivity */
#define HRTIMER_EXEVCFG0_EXEV4FAST                    BIT(29)              /*!< external event 4 fast mode */

/* HRTIMER_EXEVCFG1 */
#define HRTIMER_EXEVCFG1_EXEV5SRC                     BITS(0,1)            /*!< external event 5 source */
#define HRTIMER_EXEVCFG1_EXEV5P                       BIT(2)               /*!< external event 5 polarity */
#define HRTIMER_EXEVCFG1_EXEV5EG                      BITS(3,4)            /*!< external event 5 edge sensitivity */
#define HRTIMER_EXEVCFG1_EXEV6SRC                     BITS(6,7)            /*!< external event 6 source */
#define HRTIMER_EXEVCFG1_EXEV6P                       BIT(8)               /*!< external event 6 polarity */
#define HRTIMER_EXEVCFG1_EXEV6EG                      BITS(9,10)           /*!< external event 6 edge sensitivity */
#define HRTIMER_EXEVCFG1_EXEV7SRC                     BITS(12,13)          /*!< external event 7 source */
#define HRTIMER_EXEVCFG1_EXEV7P                       BIT(14)              /*!< external event 7 polarity */
#define HRTIMER_EXEVCFG1_EXEV7EG                      BITS(15,16)          /*!< external event 7 edge sensitivity */
#define HRTIMER_EXEVCFG1_EXEV8SRC                     BITS(18,19)          /*!< external event 8 source */
#define HRTIMER_EXEVCFG1_EXEV8P                       BIT(20)              /*!< external event 8 polarity */
#define HRTIMER_EXEVCFG1_EXEV8EG                      BITS(21,22)          /*!< external event 8 edge sensitivity */
#define HRTIMER_EXEVCFG1_EXEV9SRC                     BITS(24,25)          /*!< external event 9 source */
#define HRTIMER_EXEVCFG1_EXEV9P                       BIT(26)              /*!< external event 9 polarity */
#define HRTIMER_EXEVCFG1_EXEV9EG                      BITS(27,28)          /*!< external event 9 edge sensitivity */

/* HRTIMER_EXEVDFCTL */
#define HRTIMER_EXEVDFCTL_EXEV5FC                     BITS(0,3)            /*!< external event 5 filter control */
#define HRTIMER_EXEVDFCTL_EXEV6FC                     BITS(6,9)            /*!< external event 6 filter control */
#define HRTIMER_EXEVDFCTL_EXEV7FC                     BITS(12,15)          /*!< external event 7 filter control */
#define HRTIMER_EXEVDFCTL_EXEV8FC                     BITS(18,21)          /*!< external event 8 filter control */
#define HRTIMER_EXEVDFCTL_EXEV9FC                     BITS(24,27)          /*!< external event 9 filter control */
#define HRTIMER_EXEVDFCTL_EXEVFDIV                    BITS(30,31)          /*!< external event digital filter clock division */

/* HRTIMER_ADCTRIGS0 */
#define HRTIMER_ADCTRIGS0_TRG0MTC0                    BIT(0)               /*!< HRTIMER_ADCTRIG0 on Master_TIMER compare 0 event */
#define HRTIMER_ADCTRIGS0_TRG0MTC1                    BIT(1)               /*!< HRTIMER_ADCTRIG0 on Master_TIMER compare 1 event */
#define HRTIMER_ADCTRIGS0_TRG0MTC2                    BIT(2)               /*!< HRTIMER_ADCTRIG0 on Master_TIMER compare 2 event */
#define HRTIMER_ADCTRIGS0_TRG0MTC3                    BIT(3)               /*!< HRTIMER_ADCTRIG0 on Master_TIMER compare 3 event */
#define HRTIMER_ADCTRIGS0_TRG0MTPER                   BIT(4)               /*!< HRTIMER_ADCTRIG0 on Master_TIMER period event */
#define HRTIMER_ADCTRIGS0_TRG0EXEV0                   BIT(5)               /*!< HRTIMER_ADCTRIG0 on external event 0 */
#define HRTIMER_ADCTRIGS0_TRG0EXEV1                   BIT(6)               /*!< HRTIMER_ADCTRIG0 on external event 1 */
#define HRTIMER_ADCTRIGS0_TRG0EXEV2                   BIT(7)               /*!< HRTIMER_ADCTRIG0 on external event 2 */
#define HRTIMER_ADCTRIGS0_TRG0EXEV3                   BIT(8)               /*!< HRTIMER_ADCTRIG0 on external event 3 */
#define HRTIMER_ADCTRIGS0_TRG0EXEV4                   BIT(9)               /*!< HRTIMER_ADCTRIG0 on external event 4 */
#define HRTIMER_ADCTRIGS0_TRG0ST0C1                   BIT(10)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER0 compare 1 event */
#define HRTIMER_ADCTRIGS0_TRG0ST0C2                   BIT(11)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER0 compare 2 event */
#define HRTIMER_ADCTRIGS0_TRG0ST0C3                   BIT(12)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER0 compare 3 event */
#define HRTIMER_ADCTRIGS0_TRG0ST0PER                  BIT(13)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER0 period event */
#define HRTIMER_ADCTRIGS0_TRG0ST0RST                  BIT(14)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER0 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS0_TRG0ST1C1                   BIT(15)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER1 compare 1 event */
#define HRTIMER_ADCTRIGS0_TRG0ST1C2                   BIT(16)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER1 compare 2 event */
#define HRTIMER_ADCTRIGS0_TRG0ST1C3                   BIT(17)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER1 compare 3 event */
#define HRTIMER_ADCTRIGS0_TRG0ST1PER                  BIT(18)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER1 period event */
#define HRTIMER_ADCTRIGS0_TRG0ST1RST                  BIT(19)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER1 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS0_TRG0ST2C1                   BIT(20)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER2 compare 1 event */
#define HRTIMER_ADCTRIGS0_TRG0ST2C2                   BIT(21)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER2 compare 2 event */
#define HRTIMER_ADCTRIGS0_TRG0ST2C3                   BIT(22)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER2 compare 3 event */
#define HRTIMER_ADCTRIGS0_TRG0ST2PER                  BIT(23)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER2 period event */
#define HRTIMER_ADCTRIGS0_TRG0ST3C1                   BIT(24)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER3 compare 1 event */
#define HRTIMER_ADCTRIGS0_TRG0ST3C2                   BIT(25)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER3 compare 2 event */
#define HRTIMER_ADCTRIGS0_TRG0ST3C3                   BIT(26)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER3 compare 3 event */
#define HRTIMER_ADCTRIGS0_TRG0ST3PER                  BIT(27)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER3 period event */
#define HRTIMER_ADCTRIGS0_TRG0ST4C1                   BIT(28)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER4 compare 1 event */
#define HRTIMER_ADCTRIGS0_TRG0ST4C2                   BIT(29)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER4 compare 2 event */
#define HRTIMER_ADCTRIGS0_TRG0ST4C3                   BIT(30)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER4 compare 3 event */
#define HRTIMER_ADCTRIGS0_TRG0ST4PER                  BIT(31)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER4 period event */

/* HRTIMER_ADCTRIGS1 */
#define HRTIMER_ADCTRIGS1_TRG1MTC0                    BIT(0)               /*!< HRTIMER_ADCTRIG1 on Master_TIMER compare 0 event */
#define HRTIMER_ADCTRIGS1_TRG1MTC1                    BIT(1)               /*!< HRTIMER_ADCTRIG1 on Master_TIMER compare 1 event */
#define HRTIMER_ADCTRIGS1_TRG1MTC2                    BIT(2)               /*!< HRTIMER_ADCTRIG1 on Master_TIMER compare 2 event */
#define HRTIMER_ADCTRIGS1_TRG1MTC3                    BIT(3)               /*!< HRTIMER_ADCTRIG1 on Master_TIMER compare 3 event */
#define HRTIMER_ADCTRIGS1_TRG1MTPER                   BIT(4)               /*!< HRTIMER_ADCTRIG1 on Master_TIMER period event */
#define HRTIMER_ADCTRIGS1_TRG1EXEV5                   BIT(5)               /*!< HRTIMER_ADCTRIG1 on external event 5 */
#define HRTIMER_ADCTRIGS1_TRG1EXEV6                   BIT(6)               /*!< HRTIMER_ADCTRIG1 on external event 6 */
#define HRTIMER_ADCTRIGS1_TRG1EXEV7                   BIT(7)               /*!< HRTIMER_ADCTRIG1 on external event 7 */
#define HRTIMER_ADCTRIGS1_TRG1EXEV8                   BIT(8)               /*!< HRTIMER_ADCTRIG1 on external event 8 */
#define HRTIMER_ADCTRIGS1_TRG1EXEV9                   BIT(9)               /*!< HRTIMER_ADCTRIG1 on external event 9 */
#define HRTIMER_ADCTRIGS1_TRG1ST0C1                   BIT(10)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER0 compare 1 event */
#define HRTIMER_ADCTRIGS1_TRG1ST0C2                   BIT(11)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER0 compare 2 event */
#define HRTIMER_ADCTRIGS1_TRG1ST0C3                   BIT(12)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER0 compare 3 event */
#define HRTIMER_ADCTRIGS1_TRG1ST0PER                  BIT(13)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER0 period event */
#define HRTIMER_ADCTRIGS1_TRG1ST1C1                   BIT(14)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER1 compare 1 event */
#define HRTIMER_ADCTRIGS1_TRG1ST1C2                   BIT(15)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER1 compare 2 event */
#define HRTIMER_ADCTRIGS1_TRG1ST1C3                   BIT(16)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER1 compare 3 event */
#define HRTIMER_ADCTRIGS1_TRG1ST1PER                  BIT(17)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER1 period event */
#define HRTIMER_ADCTRIGS1_TRG1ST2C1                   BIT(18)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER2 compare 1 event */
#define HRTIMER_ADCTRIGS1_TRG1ST2C2                   BIT(19)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER2 compare 2 event */
#define HRTIMER_ADCTRIGS1_TRG1ST2C3                   BIT(20)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER2 compare 3 event */
#define HRTIMER_ADCTRIGS1_TRG1ST2PER                  BIT(21)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER2 period event */
#define HRTIMER_ADCTRIGS1_TRG1ST2RST                  BIT(22)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER2 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS1_TRG1ST3C1                   BIT(23)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER3 compare 1 event */
#define HRTIMER_ADCTRIGS1_TRG1ST3C2                   BIT(24)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER3 compare 2 event */
#define HRTIMER_ADCTRIGS1_TRG1ST3C3                   BIT(25)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER3 compare 3 event */
#define HRTIMER_ADCTRIGS1_TRG1ST3PER                  BIT(26)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER3 period event */
#define HRTIMER_ADCTRIGS1_TRG1ST3RST                  BIT(27)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER3 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS1_TRG1ST4C1                   BIT(28)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER4 compare 1 event */
#define HRTIMER_ADCTRIGS1_TRG1ST4C2                   BIT(29)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER4 compare 2 event */
#define HRTIMER_ADCTRIGS1_TRG1ST4C3                   BIT(30)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER4 compare 3 event */
#define HRTIMER_ADCTRIGS1_TRG1ST4RST                  BIT(31)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER4 reset and counter roll-over event */

/* HRTIMER_ADCTRIGS2 */
#define HRTIMER_ADCTRIGS2_TRG2MTC0                    BIT(0)               /*!< HRTIMER_ADCTRIG2 on Master_TIMER compare 0 event */
#define HRTIMER_ADCTRIGS2_TRG2MTC1                    BIT(1)               /*!< HRTIMER_ADCTRIG2 on Master_TIMER compare 1 event */
#define HRTIMER_ADCTRIGS2_TRG2MTC2                    BIT(2)               /*!< HRTIMER_ADCTRIG2 on Master_TIMER compare 2 event */
#define HRTIMER_ADCTRIGS2_TRG2MTC3                    BIT(3)               /*!< HRTIMER_ADCTRIG2 on Master_TIMER compare 3 event */
#define HRTIMER_ADCTRIGS2_TRG2MTPER                   BIT(4)               /*!< HRTIMER_ADCTRIG2 on Master_TIMER period event */
#define HRTIMER_ADCTRIGS2_TRG2EXEV0                   BIT(5)               /*!< HRTIMER_ADCTRIG2 on external event 0 */
#define HRTIMER_ADCTRIGS2_TRG2EXEV1                   BIT(6)               /*!< HRTIMER_ADCTRIG2 on external event 1 */
#define HRTIMER_ADCTRIGS2_TRG2EXEV2                   BIT(7)               /*!< HRTIMER_ADCTRIG2 on external event 2 */
#define HRTIMER_ADCTRIGS2_TRG2EXEV3                   BIT(8)               /*!< HRTIMER_ADCTRIG2 on external event 3 */
#define HRTIMER_ADCTRIGS2_TRG2EXEV4                   BIT(9)               /*!< HRTIMER_ADCTRIG2 on external event 4 */
#define HRTIMER_ADCTRIGS2_TRG2ST0C1                   BIT(10)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER0 compare 1 event */
#define HRTIMER_ADCTRIGS2_TRG2ST0C2                   BIT(11)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER0 compare 2 event */
#define HRTIMER_ADCTRIGS2_TRG2ST0C3                   BIT(12)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER0 compare 3 event */
#define HRTIMER_ADCTRIGS2_TRG2ST0PER                  BIT(13)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER0 period event */
#define HRTIMER_ADCTRIGS2_TRG2ST0RST                  BIT(14)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER0 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS2_TRG2ST1C1                   BIT(15)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER1 compare 1 event */
#define HRTIMER_ADCTRIGS2_TRG2ST1C2                   BIT(16)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER1 compare 2 event */
#define HRTIMER_ADCTRIGS2_TRG2ST1C3                   BIT(17)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER1 compare 3 event */
#define HRTIMER_ADCTRIGS2_TRG2ST1PER                  BIT(18)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER1 period event */
#define HRTIMER_ADCTRIGS2_TRG2ST1RST                  BIT(19)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER1 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS2_TRG2ST2C1                   BIT(20)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER2 compare 1 event */
#define HRTIMER_ADCTRIGS2_TRG2ST2C2                   BIT(21)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER2 compare 2 event */
#define HRTIMER_ADCTRIGS2_TRG2ST2C3                   BIT(22)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER2 compare 3 event */
#define HRTIMER_ADCTRIGS2_TRG2ST2PER                  BIT(23)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER2 period event */
#define HRTIMER_ADCTRIGS2_TRG2ST3C1                   BIT(24)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER3 compare 1 event */
#define HRTIMER_ADCTRIGS2_TRG2ST3C2                   BIT(25)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER3 compare 2 event */
#define HRTIMER_ADCTRIGS2_TRG2ST3C3                   BIT(26)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER3 compare 3 event */
#define HRTIMER_ADCTRIGS2_TRG2ST3PER                  BIT(27)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER3 period event */
#define HRTIMER_ADCTRIGS2_TRG2ST4C1                   BIT(28)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER4 compare 1 event */
#define HRTIMER_ADCTRIGS2_TRG2ST4C2                   BIT(29)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER4 compare 2 event */
#define HRTIMER_ADCTRIGS2_TRG2ST4C3                   BIT(30)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER4 compare 3 event */
#define HRTIMER_ADCTRIGS2_TRG2ST4PER                  BIT(31)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER4 period event */

/* HRTIMER_ADCTRIGS3 */
#define HRTIMER_ADCTRIGS3_TRG3MTC0                    BIT(0)               /*!< HRTIMER_ADCTRIG3 on Master_TIMER compare 0 event */
#define HRTIMER_ADCTRIGS3_TRG3MTC1                    BIT(1)               /*!< HRTIMER_ADCTRIG3 on Master_TIMER compare 1 event */
#define HRTIMER_ADCTRIGS3_TRG3MTC2                    BIT(2)               /*!< HRTIMER_ADCTRIG3 on Master_TIMER compare 2 event */
#define HRTIMER_ADCTRIGS3_TRG3MTC3                    BIT(3)               /*!< HRTIMER_ADCTRIG3 on Master_TIMER compare 3 event */
#define HRTIMER_ADCTRIGS3_TRG3MTPER                   BIT(4)               /*!< HRTIMER_ADCTRIG3 on Master_TIMER period event */
#define HRTIMER_ADCTRIGS3_TRG3EXEV5                   BIT(5)               /*!< HRTIMER_ADCTRIG3 on external event 5 */
#define HRTIMER_ADCTRIGS3_TRG3EXEV6                   BIT(6)               /*!< HRTIMER_ADCTRIG3 on external event 6 */
#define HRTIMER_ADCTRIGS3_TRG3EXEV7                   BIT(7)               /*!< HRTIMER_ADCTRIG3 on external event 7 */
#define HRTIMER_ADCTRIGS3_TRG3EXEV8                   BIT(8)               /*!< HRTIMER_ADCTRIG3 on external event 8 */
#define HRTIMER_ADCTRIGS3_TRG3EXEV9                   BIT(9)               /*!< HRTIMER_ADCTRIG3 on external event 9 */
#define HRTIMER_ADCTRIGS3_TRG3ST0C1                   BIT(10)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER0 compare 1 event */
#define HRTIMER_ADCTRIGS3_TRG3ST0C2                   BIT(11)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER0 compare 2 event */
#define HRTIMER_ADCTRIGS3_TRG3ST0C3                   BIT(12)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER0 compare 3 event */
#define HRTIMER_ADCTRIGS3_TRG3ST0PER                  BIT(13)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER0 period event */
#define HRTIMER_ADCTRIGS3_TRG3ST1C1                   BIT(14)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER1 compare 1 event */
#define HRTIMER_ADCTRIGS3_TRG3ST1C2                   BIT(15)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER1 compare 2 event */
#define HRTIMER_ADCTRIGS3_TRG3ST1C3                   BIT(16)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER1 compare 3 event */
#define HRTIMER_ADCTRIGS3_TRG3ST1PER                  BIT(17)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER1 period event */
#define HRTIMER_ADCTRIGS3_TRG3ST2C1                   BIT(18)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER2 compare 1 event */
#define HRTIMER_ADCTRIGS3_TRG3ST2C2                   BIT(19)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER2 compare 2 event */
#define HRTIMER_ADCTRIGS3_TRG3ST2C3                   BIT(20)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER2 compare 3 event */
#define HRTIMER_ADCTRIGS3_TRG3ST2PER                  BIT(21)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER2 period event */
#define HRTIMER_ADCTRIGS3_TRG3ST2RST                  BIT(22)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER2 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS3_TRG3ST3C1                   BIT(23)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER3 compare 1 event */
#define HRTIMER_ADCTRIGS3_TRG3ST3C2                   BIT(24)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER3 compare 2 event */
#define HRTIMER_ADCTRIGS3_TRG3ST3C3                   BIT(25)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER3 compare 3 event */
#define HRTIMER_ADCTRIGS3_TRG3ST3PER                  BIT(26)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER3 period event */
#define HRTIMER_ADCTRIGS3_TRG3ST3RST                  BIT(27)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER3 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS3_TRG3ST4C1                   BIT(28)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER4 compare 1 event */
#define HRTIMER_ADCTRIGS3_TRG3ST4C2                   BIT(29)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER4 compare 2 event */
#define HRTIMER_ADCTRIGS3_TRG3ST4C3                   BIT(30)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER4 compare 3 event */
#define HRTIMER_ADCTRIGS3_TRG3ST4RST                  BIT(31)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER4 reset and counter roll-over event */

/* HRTIMER_DLLCCTL */
#define HRTIMER_DLLCCTL_CLBSTRT                       BIT(0)               /*!< DLL calibration start once */
#define HRTIMER_DLLCCTL_CLBPEREN                      BIT(1)               /*!< DLL periodic calibration enable */
#define HRTIMER_DLLCCTL_CLBPER                        BITS(2,3)            /*!< DLL calibration period */

/* HRTIMER_FLTINCFG0 */
#define HRTIMER_FLTINCFG0_FLT0INEN                    BIT(0)               /*!< fault 0 input enable */
#define HRTIMER_FLTINCFG0_FLT0INP                     BIT(1)               /*!< fault 0 input polarity */
#define HRTIMER_FLTINCFG0_FLT0INSRC0                  BIT(2)               /*!< fault 0 input source */
#define HRTIMER_FLTINCFG0_FLT0INFC                    BITS(3,6)            /*!< fault 0 input filter control */
#define HRTIMER_FLTINCFG0_FLT0INPROT                  BIT(7)               /*!< protect fault 0 input configuration */
#define HRTIMER_FLTINCFG0_FLT1INEN                    BIT(8)               /*!< fault 1 input enable */
#define HRTIMER_FLTINCFG0_FLT1INP                     BIT(9)               /*!< fault 1 input polarity */
#define HRTIMER_FLTINCFG0_FLT1INSRC0                  BIT(10)              /*!< fault 1 input source */
#define HRTIMER_FLTINCFG0_FLT1INFC                    BITS(11,14)          /*!< fault 1 input filter control */
#define HRTIMER_FLTINCFG0_FLT1INPROT                  BIT(15)              /*!< protect fault 1 input configuration */
#define HRTIMER_FLTINCFG0_FLT2INEN                    BIT(16)              /*!< fault 2 input enable */
#define HRTIMER_FLTINCFG0_FLT2INP                     BIT(17)              /*!< fault 2 input polarity */
#define HRTIMER_FLTINCFG0_FLT2INSRC0                  BIT(18)              /*!< fault 2 input source */
#define HRTIMER_FLTINCFG0_FLT2INFC                    BITS(19,22)          /*!< fault 2 input filter control */
#define HRTIMER_FLTINCFG0_FLT2INPROT                  BIT(23)              /*!< protect fault 2 input configuration */
#define HRTIMER_FLTINCFG0_FLT3INEN                    BIT(24)              /*!< fault 3 input enable */
#define HRTIMER_FLTINCFG0_FLT3INP                     BIT(25)              /*!< fault 3 input polarity */
#define HRTIMER_FLTINCFG0_FLT3INSRC0                  BIT(26)              /*!< fault 3 input source */
#define HRTIMER_FLTINCFG0_FLT3INFC                    BITS(27,30)          /*!< fault 3 input filter control */
#define HRTIMER_FLTINCFG0_FLT3INPROT                  BIT(31)              /*!< protect fault 3 input configuration */

/* HRTIMER_FLTINCFG1 */
#define HRTIMER_FLTINCFG1_FLT4INEN                    BIT(0)               /*!< fault 4 input enable */
#define HRTIMER_FLTINCFG1_FLT4INP                     BIT(1)               /*!< fault 4 input polarity */
#define HRTIMER_FLTINCFG1_FLT4INSRC0                  BIT(2)               /*!< fault 4 input source */
#define HRTIMER_FLTINCFG1_FLT4INFC                    BITS(3,6)            /*!< fault 4 input filter control */
#define HRTIMER_FLTINCFG1_FLT4INPROT                  BIT(7)               /*!< protect fault 4 input configuration */
#define HRTIMER_FLTINCFG1_FLT5INEN                    BIT(8)               /*!< fault 5 input enable */
#define HRTIMER_FLTINCFG1_FLT5INP                     BIT(9)               /*!< fault 5 input polarity */
#define HRTIMER_FLTINCFG1_FLT5INSRC0                  BIT(10)              /*!< fault 5 input source */
#define HRTIMER_FLTINCFG1_FLT5INFC                    BITS(11,14)          /*!< fault 5 input filter control */
#define HRTIMER_FLTINCFG1_FLT5INPROT                  BIT(15)              /*!< protect fault 5 input configuration */
#define HRTIMER_FLTINCFG1_FLT0INSRC1                  BIT(16)              /*!< fault 0 input source */
#define HRTIMER_FLTINCFG1_FLT1INSRC1                  BIT(17)              /*!< fault 1 input source */
#define HRTIMER_FLTINCFG1_FLT2INSRC1                  BIT(18)              /*!< fault 2 input source */
#define HRTIMER_FLTINCFG1_FLT3INSRC1                  BIT(19)              /*!< fault 3 input source */
#define HRTIMER_FLTINCFG1_FLT4INSRC1                  BIT(20)              /*!< fault 4 input source */
#define HRTIMER_FLTINCFG1_FLT5INSRC1                  BIT(21)              /*!< fault 5 input source */
#define HRTIMER_FLTINCFG1_FLT6INSRC1                  BIT(22)              /*!< fault 6 input source */
#define HRTIMER_FLTINCFG1_FLT7INSRC1                  BIT(23)              /*!< fault 7 input source */
#define HRTIMER_FLTINCFG1_FLTFDIV                     BITS(24,25)          /*!< fault input digital filter clock division */

/* HRTIMER_DMAUPMTR */
#define HRTIMER_DMAUPMTR_MTCTL0                       BIT(0)               /*!< HRTIMER_MTCTL0 update by DMA mode */
#define HRTIMER_DMAUPMTR_MTINTC                       BIT(1)               /*!< HRTIMER_MTINTC update by DMA mode */
#define HRTIMER_DMAUPMTR_MTDMAINTEN                   BIT(2)               /*!< HRTIMER_MTDMAINTEN update by DMA mode */
#define HRTIMER_DMAUPMTR_MTCNT                        BIT(3)               /*!< HRTIMER_MTCNT update by DMA mode */
#define HRTIMER_DMAUPMTR_MTCAR                        BIT(4)               /*!< HRTIMER_MTCAR update by DMA mode */
#define HRTIMER_DMAUPMTR_MTCREP                       BIT(5)               /*!< HRTIMER_MTCREP update by DMA mode */
#define HRTIMER_DMAUPMTR_MTCMP0V                      BIT(6)               /*!< HRTIMER_MTCMP0V update by DMA mode */
#define HRTIMER_DMAUPMTR_MTCMP1V                      BIT(7)               /*!< HRTIMER_MTCMP1V update by DMA mode */
#define HRTIMER_DMAUPMTR_MTCMP2V                      BIT(8)               /*!< HRTIMER_MTCMP2V update by DMA mode */
#define HRTIMER_DMAUPMTR_MTCMP3V                      BIT(9)               /*!< HRTIMER_MTCMP3V update by DMA mode */

/* HRTIMER_DMAUPSTxR */
#define HRTIMER_DMAUPSTXR_STXCTL0                     BIT(0)               /*!< HRTIMER_STxCTL0 update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXINTC                     BIT(1)               /*!< HRTIMER_STxINTC update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXDMAINTEN                 BIT(2)               /*!< HRTIMER_STxDMAINTEN update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCNT                      BIT(3)               /*!< HRTIMER_STxCNT update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCAR                      BIT(4)               /*!< HRTIMER_STxCAR update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCREP                     BIT(5)               /*!< HRTIMER_STxCREP update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCMP0V                    BIT(6)               /*!< HRTIMER_STxCMP0V update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCMP1V                    BIT(7)               /*!< HRTIMER_STxCMP1V update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCMP2V                    BIT(8)               /*!< HRTIMER_STxCMP2V update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCMP3V                    BIT(9)               /*!< HRTIMER_STxCMP3V update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXDTCTL                    BIT(10)              /*!< HRTIMER_STxDTCTL update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCH0SET                   BIT(11)              /*!< HRTIMER_STxCH0SET update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCH0RST                   BIT(12)              /*!< HRTIMER_STxCH0RST update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCH1SET                   BIT(13)              /*!< HRTIMER_STxCH1SET update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCH1RST                   BIT(14)              /*!< HRTIMER_STxCH1RST update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXEXEVFCFG0                BIT(15)              /*!< HRTIMER_STxEXEVFCFG0 update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXEXEVFCFG1                BIT(16)              /*!< HRTIMER_STxEXEVFCFG1 update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCNTRST                   BIT(17)              /*!< HRTIMER_STxCNTRST update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCSCTL                    BIT(18)              /*!< HRTIMER_STxCSCTL update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXCHOCTL                   BIT(19)              /*!< HRTIMER_STxCHOCTL update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXFLTCTL                   BIT(20)              /*!< HRTIMER_STxFLTCTL update by DMA mode */
#define HRTIMER_DMAUPSTXR_STxCTL1                     BIT(21)              /*!< HRTIMER_STxCTL1 update by DMA mode */
#define HRTIMER_DMAUPSTXR_STxEXEVFCFG2                BIT(22)              /*!< HRTIMER_STxEXEVFCFG2 update by DMA mode */
#define HRTIMER_DMAUPSTXR_STXACTL                     BIT(31)              /*!< HRTIMER_STxACTL update by DMA mode */

/* HRTIMER_DMATB */
#define HRTIMER_DMATB_DMATB                           BITS(0,31)           /*!< DMA transfer buffer */

/* HRTIMER_ADCEXTTRG */
#define HRTIMER_ADCEXTTRG_ADC4TRG4_0                  BITS(0,4)            /*!< this bit selects the ADC trigger 4 source */
#define HRTIMER_ADCEXTTRG_ADC5TRG4_0                  BITS(5,9)            /*!< this bit selects the ADC trigger 5 source */
#define HRTIMER_ADCEXTTRG_ADC6TRG4_0                  BITS(10,14)          /*!< this bit selects the ADC trigger 6 source */
#define HRTIMER_ADCEXTTRG_ADC7TRG4_0                  BITS(16,20)          /*!< this bit selects the ADC trigger 7 source */
#define HRTIMER_ADCEXTTRG_ADC8TRG4_0                  BITS(21,25)          /*!< this bit selects the ADC trigger 8 source */
#define HRTIMER_ADCEXTTRG_ADC9TRG4_0                  BITS(26,30)          /*!< this bit selects the ADC trigger 9 source */

/* HRTIMER_ADCTRGUPD */
#define HRTIMER_ADCTRGUPD_ADTG4USRC                    BITS(0,3)           /*!< ADC trigger 4 update source */ 
#define HRTIMER_ADCTRGUPD_ADTG5USRC                    BITS(4,7)           /*!< ADC trigger 5 update source */ 
#define HRTIMER_ADCTRGUPD_ADTG6USRC                    BITS(8,11)          /*!< ADC trigger 6 update source */ 
#define HRTIMER_ADCTRGUPD_ADTG7USRC                    BITS(12,15)         /*!< ADC trigger 7 update source */ 
#define HRTIMER_ADCTRGUPD_ADTG8USRC                    BITS(16,19)         /*!< ADC trigger 8 update source */ 
#define HRTIMER_ADCTRGUPD_ADTG9USRC                    BITS(20,23)         /*!< ADC trigger 9 update source */

/* HRTIMER_ADCPSCR0 */
#define HRTIMER_ADCPSCR0_ADC0PSC                      BITS(0,4)            /*!< ADC trigger 0 prescaler */
#define HRTIMER_ADCPSCR0_ADC1PSC                      BITS(6,10)           /*!< ADC trigger 1 prescaler */
#define HRTIMER_ADCPSCR0_ADC2PSC                      BITS(12,16)          /*!< ADC trigger 2 prescaler */
#define HRTIMER_ADCPSCR0_ADC3PSC                      BITS(18,22)          /*!< ADC trigger 3 prescaler */
#define HRTIMER_ADCPSCR0_ADC4PSC                      BITS(24,28)          /*!< ADC trigger 4 prescaler */

/* HRTIMER_ADCPSCR1 */
#define HRTIMER_ADCPSCR1_ADC5PSC                      BITS(0,4)            /*!< ADC trigger 5 prescaler */
#define HRTIMER_ADCPSCR1_ADC6PSC                      BITS(6,10)           /*!< ADC trigger 6 prescaler */
#define HRTIMER_ADCPSCR1_ADC7PSC                      BITS(12,16)          /*!< ADC trigger 7 prescaler */
#define HRTIMER_ADCPSCR1_ADC8PSC                      BITS(18,22)          /*!< ADC trigger 8 prescaler */
#define HRTIMER_ADCPSCR1_ADC9PSC                      BITS(24,28)          /*!< ADC trigger 9 prescaler */

/* HRTIMER_FLTINCFG2 */
#define HRTIMER_FLTINCFG2_FLT0BLKEN                   BIT(0)               /*!< fault 0 blanking enable */
#define HRTIMER_FLTINCFG2_FLT0BLKS                    BIT(1)               /*!< fault 0 blanking source */
#define HRTIMER_FLTINCFG2_FLT0CNT                     BITS(2,5)            /*!< fault 0 counter */
#define HRTIMER_FLTINCFG2_FLT0CNTRST                  BIT(6)               /*!< fault 0 counter reset */
#define HRTIMER_FLTINCFG2_FLT0RST                     BIT(7)               /*!< fault 0 reset mode */
#define HRTIMER_FLTINCFG2_FLT1BLKEN                   BIT(8)               /*!< fault 1 blanking enable */
#define HRTIMER_FLTINCFG2_FLT1BLKS                    BIT(9)               /*!< fault 1 blanking source */
#define HRTIMER_FLTINCFG2_FLT1CNT                     BITS(10,13)          /*!< fault 1 counter */
#define HRTIMER_FLTINCFG2_FLT1CNTRST                  BIT(14)              /*!< fault 1 counter reset */
#define HRTIMER_FLTINCFG2_FLT1RST                     BIT(15)              /*!< fault 1 reset mode */
#define HRTIMER_FLTINCFG2_FLT2BLKEN                   BIT(16)              /*!< fault 2 blanking enable */
#define HRTIMER_FLTINCFG2_FLT2BLKS                    BIT(17)              /*!< fault 2 blanking source */
#define HRTIMER_FLTINCFG2_FLT2CNT                     BITS(18,21)          /*!< fault 2 counter */
#define HRTIMER_FLTINCFG2_FLT2CNTRST                  BIT(22)              /*!< fault 2 counter reset */
#define HRTIMER_FLTINCFG2_FLT2RST                     BIT(23)              /*!< fault 2 reset mode */
#define HRTIMER_FLTINCFG2_FLT3BLKEN                   BIT(24)              /*!< fault 3 blanking enable */
#define HRTIMER_FLTINCFG2_FLT3BLKS                    BIT(25)              /*!< fault 3 blanking source */
#define HRTIMER_FLTINCFG2_FLT3CNT                     BITS(26,29)          /*!< fault 3 counter */
#define HRTIMER_FLTINCFG2_FLT3CNTRST                  BIT(30)              /*!< fault 3 counter reset */
#define HRTIMER_FLTINCFG2_FLT3RST                     BIT(31)              /*!< fault 3 reset mode */

/* HRTIMER_FLTINCFG3 */
#define HRTIMER_FLTINCFG3_FLT4BLKEN                   BIT(0)               /*!< fault 4 blanking enable */
#define HRTIMER_FLTINCFG3_FLT4BLKS                    BIT(1)               /*!< fault 4 blanking source */
#define HRTIMER_FLTINCFG3_FLT4CNT                     BITS(2,5)            /*!< fault 4 counter */
#define HRTIMER_FLTINCFG3_FLT4CNTRST                  BIT(6)               /*!< fault 4 counter reset */
#define HRTIMER_FLTINCFG3_FLT4RST                     BIT(7)               /*!< fault 4 reset mode */
#define HRTIMER_FLTINCFG3_FLT5BLKEN                   BIT(8)               /*!< fault 5 blanking enable */
#define HRTIMER_FLTINCFG3_FLT5BLKS                    BIT(9)               /*!< fault 5 blanking source */
#define HRTIMER_FLTINCFG3_FLT5CNT                     BITS(10,13)          /*!< fault 5 counter */
#define HRTIMER_FLTINCFG3_FLT5CNTRST                  BIT(14)              /*!< fault 5 counter reset */
#define HRTIMER_FLTINCFG3_FLT5RST                     BIT(15)              /*!< fault 5 reset mode */
#define HRTIMER_FLTINCFG3_FLT6BLKEN                   BIT(16)              /*!< fault 6 blanking enable */
#define HRTIMER_FLTINCFG3_FLT6BLKS                    BIT(17)              /*!< fault 6 blanking source */
#define HRTIMER_FLTINCFG3_FLT6CNT                     BITS(18,21)          /*!< fault 6 counter */
#define HRTIMER_FLTINCFG3_FLT6CNTRST                  BIT(22)              /*!< fault 6 counter reset */
#define HRTIMER_FLTINCFG3_FLT6RST                     BIT(23)              /*!< fault 6 reset mode */
#define HRTIMER_FLTINCFG3_FLT7BLKEN                   BIT(24)              /*!< fault 7 blanking enable */
#define HRTIMER_FLTINCFG3_FLT7BLKS                    BIT(25)              /*!< fault 7 blanking source */
#define HRTIMER_FLTINCFG3_FLT7CNT                     BITS(26,29)          /*!< fault 7 counter */
#define HRTIMER_FLTINCFG3_FLT7CNTRST                  BIT(30)              /*!< fault 7 counter reset */
#define HRTIMER_FLTINCFG3_FLT7RST                     BIT(31)              /*!< fault 7 reset mode */

/* HRTIMER_BMSTRGA */
#define HRTIMER_BMSTRGA_ST5RST                        BIT(0)               /*!< Slave_TIMER5 reset event triggers bunch mode operation */
#define HRTIMER_BMSTRGA_ST5REP                        BIT(1)               /*!< Slave_TIMER5 repetition event triggers bunch mode operation */
#define HRTIMER_BMSTRGA_ST5CMP0                       BIT(2)               /*!< Slave_TIMER5 compare 0 event triggers bunch mode operation */
#define HRTIMER_BMSTRGA_ST5CMP1                       BIT(3)               /*!< Slave_TIMER5 compare 1 event triggers bunch mode operation */
#define HRTIMER_BMSTRGA_ST6RST                        BIT(4)               /*!< Slave_TIMER6 reset event triggers bunch mode operation */
#define HRTIMER_BMSTRGA_ST6REP                        BIT(5)               /*!< Slave_TIMER6 repetition event triggers bunch mode operation */
#define HRTIMER_BMSTRGA_ST6CMP0                       BIT(6)               /*!< Slave_TIMER6 compare 0 event triggers bunch mode operation */
#define HRTIMER_BMSTRGA_ST6CMP1                       BIT(7)               /*!< Slave_TIMER6 compare 1 event triggers bunch mode operation */
#define HRTIMER_BMSTRGA_ST7RST                        BIT(8)               /*!< Slave_TIMER7 reset event triggers bunch mode operation */
#define HRTIMER_BMSTRGA_ST7REP                        BIT(9)               /*!< Slave_TIMER7 repetition event triggers bunch mode operation */
#define HRTIMER_BMSTRGA_ST7CMP0                       BIT(10)              /*!< Slave_TIMER7 compare 0 event triggers bunch mode operation */
#define HRTIMER_BMSTRGA_ST7CMP1                       BIT(11)              /*!< Slave_TIMER7 compare 1 event triggers bunch mode operation */

/* HRTIMER_FLTINCFG4 */
#define HRTIMER_FLTINCFG4_FLT6INEN                    BIT(0)               /*!< fault 6 input enable */
#define HRTIMER_FLTINCFG4_FLT6INP                     BIT(1)               /*!< fault 6 input polarity */
#define HRTIMER_FLTINCFG4_FLT6INSRC0                  BIT(2)               /*!< fault 6 input source */
#define HRTIMER_FLTINCFG4_FLT6INFC                    BITS(3,6)            /*!< fault 6 input filter control */
#define HRTIMER_FLTINCFG4_FLT6INPROT                  BIT(7)               /*!< protect fault 6 input configuration */
#define HRTIMER_FLTINCFG4_FLT7INEN                    BIT(8)               /*!< fault 7 input enable */
#define HRTIMER_FLTINCFG4_FLT7INP                     BIT(9)               /*!< fault 7 input polarity */
#define HRTIMER_FLTINCFG4_FLT7INSRC0                  BIT(10)              /*!< fault 7 input source */
#define HRTIMER_FLTINCFG4_FLT7INFC                    BITS(11,14)          /*!< fault 7 input filter control */
#define HRTIMER_FLTINCFG4_FLT7INPROT                  BIT(15)              /*!< protect fault 7 input configuration */

/* HRTIMER_ADCEXTTRGA */
#define HRTIMER_ADCEXTTRGA_ADC4TRG5                   BIT(0)               /*!< this bit selects the ADC trigger 4 source */
#define HRTIMER_ADCEXTTRGA_ADC5TRG5                   BIT(1)               /*!< this bit selects the ADC trigger 5 source */
#define HRTIMER_ADCEXTTRGA_ADC6TRG5                   BIT(2)               /*!< this bit selects the ADC trigger 6 source */
#define HRTIMER_ADCEXTTRGA_ADC7TRG5                   BIT(3)               /*!< this bit selects the ADC trigger 7 source */
#define HRTIMER_ADCEXTTRGA_ADC8TRG5                   BIT(4)               /*!< this bit selects the ADC trigger 8 source */
#define HRTIMER_ADCEXTTRGA_ADC9TRG5                   BIT(5)               /*!< this bit selects the ADC trigger 9 source */

/* HRTIMER_ADCTRIGS0A */
#define HRTIMER_ADCTRIGS0A_TRG0ST5C1                  BIT(0)               /*!< HRTIMER_ADCTRIG0 on Slave_TIMER5 compare 1 event */
#define HRTIMER_ADCTRIGS0A_TRG0ST5C2                  BIT(1)               /*!< HRTIMER_ADCTRIG0 on Slave_TIMER5 compare 2 event */
#define HRTIMER_ADCTRIGS0A_TRG0ST5C3                  BIT(2)               /*!< HRTIMER_ADCTRIG0 on Slave_TIMER5 compare 3 event */
#define HRTIMER_ADCTRIGS0A_TRG0ST5PER                 BIT(3)               /*!< HRTIMER_ADCTRIG0 on Slave_TIMER5 period event */
#define HRTIMER_ADCTRIGS0A_TRG0ST5RST                 BIT(4)               /*!< HRTIMER_ADCTRIG0 on Slave_TIMER5 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS0A_TRG0ST6C1                  BIT(8)               /*!< HRTIMER_ADCTRIG0 on Slave_TIMER6 compare 1 event */
#define HRTIMER_ADCTRIGS0A_TRG0ST6C2                  BIT(9)               /*!< HRTIMER_ADCTRIG0 on Slave_TIMER6 compare 2 event */
#define HRTIMER_ADCTRIGS0A_TRG0ST6C3                  BIT(10)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER6 compare 3 event */
#define HRTIMER_ADCTRIGS0A_TRG0ST6PER                 BIT(11)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER6 period event */
#define HRTIMER_ADCTRIGS0A_TRG0ST6RST                 BIT(12)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER6 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS0A_TRG0ST7C1                  BIT(16)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER7 compare 1 event */
#define HRTIMER_ADCTRIGS0A_TRG0ST7C2                  BIT(17)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER7 compare 2 event */
#define HRTIMER_ADCTRIGS0A_TRG0ST7C3                  BIT(18)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER7 compare 3 event */
#define HRTIMER_ADCTRIGS0A_TRG0ST7PER                 BIT(19)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER7 period event */
#define HRTIMER_ADCTRIGS0A_TRG0ST7RST                 BIT(20)              /*!< HRTIMER_ADCTRIG0 on Slave_TIMER7 reset and counter roll-over event */

/* HRTIMER_ADCTRIGS1A */
#define HRTIMER_ADCTRIGS1A_TRG1ST5C1                  BIT(0)               /*!< HRTIMER_ADCTRIG1 on Slave_TIMER5 compare 1 event */
#define HRTIMER_ADCTRIGS1A_TRG1ST5C2                  BIT(1)               /*!< HRTIMER_ADCTRIG1 on Slave_TIMER5 compare 2 event */
#define HRTIMER_ADCTRIGS1A_TRG1ST5C3                  BIT(2)               /*!< HRTIMER_ADCTRIG1 on Slave_TIMER5 compare 3 event */
#define HRTIMER_ADCTRIGS1A_TRG1ST5PER                 BIT(3)               /*!< HRTIMER_ADCTRIG1 on Slave_TIMER5 period event */
#define HRTIMER_ADCTRIGS1A_TRG1ST5RST                 BIT(4)               /*!< HRTIMER_ADCTRIG1 on Slave_TIMER5 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS1A_TRG1ST6C1                  BIT(8)               /*!< HRTIMER_ADCTRIG1 on Slave_TIMER6 compare 1 event */
#define HRTIMER_ADCTRIGS1A_TRG1ST6C2                  BIT(9)               /*!< HRTIMER_ADCTRIG1 on Slave_TIMER6 compare 2 event */
#define HRTIMER_ADCTRIGS1A_TRG1ST6C3                  BIT(10)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER6 compare 3 event */
#define HRTIMER_ADCTRIGS1A_TRG1ST6PER                 BIT(11)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER6 period event */
#define HRTIMER_ADCTRIGS1A_TRG1ST6RST                 BIT(12)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER6 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS1A_TRG1ST7C1                  BIT(16)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER7 compare 1 event */
#define HRTIMER_ADCTRIGS1A_TRG1ST7C2                  BIT(17)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER7 compare 2 event */
#define HRTIMER_ADCTRIGS1A_TRG1ST7C3                  BIT(18)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER7 compare 3 event */
#define HRTIMER_ADCTRIGS1A_TRG1ST7PER                 BIT(19)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER7 period event */
#define HRTIMER_ADCTRIGS1A_TRG1ST7RST                 BIT(20)              /*!< HRTIMER_ADCTRIG1 on Slave_TIMER7 reset and counter roll-over event */

/* HRTIMER_ADCTRIGS2A */
#define HRTIMER_ADCTRIGS2A_TRG2ST5C1                  BIT(0)               /*!< HRTIMER_ADCTRIG2 on Slave_TIMER5 compare 1 event */
#define HRTIMER_ADCTRIGS2A_TRG2ST5C2                  BIT(1)               /*!< HRTIMER_ADCTRIG2 on Slave_TIMER5 compare 2 event */
#define HRTIMER_ADCTRIGS2A_TRG2ST5C3                  BIT(2)               /*!< HRTIMER_ADCTRIG2 on Slave_TIMER5 compare 3 event */
#define HRTIMER_ADCTRIGS2A_TRG2ST5PER                 BIT(3)               /*!< HRTIMER_ADCTRIG2 on Slave_TIMER5 period event */
#define HRTIMER_ADCTRIGS2A_TRG2ST5RST                 BIT(4)               /*!< HRTIMER_ADCTRIG2 on Slave_TIMER5 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS2A_TRG2ST6C1                  BIT(8)               /*!< HRTIMER_ADCTRIG2 on Slave_TIMER6 compare 1 event */
#define HRTIMER_ADCTRIGS2A_TRG2ST6C2                  BIT(9)               /*!< HRTIMER_ADCTRIG2 on Slave_TIMER6 compare 2 event */
#define HRTIMER_ADCTRIGS2A_TRG2ST6C3                  BIT(10)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER6 compare 3 event */
#define HRTIMER_ADCTRIGS2A_TRG2ST6PER                 BIT(11)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER6 period event */
#define HRTIMER_ADCTRIGS2A_TRG2ST6RST                 BIT(12)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER6 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS2A_TRG2ST7C1                  BIT(16)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER7 compare 1 event */
#define HRTIMER_ADCTRIGS2A_TRG2ST7C2                  BIT(17)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER7 compare 2 event */
#define HRTIMER_ADCTRIGS2A_TRG2ST7C3                  BIT(18)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER7 compare 3 event */
#define HRTIMER_ADCTRIGS2A_TRG2ST7PER                 BIT(19)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER7 period event */
#define HRTIMER_ADCTRIGS2A_TRG2ST7RST                 BIT(20)              /*!< HRTIMER_ADCTRIG2 on Slave_TIMER7 reset and counter roll-over event */

/* HRTIMER_ADCTRIGS3A */
#define HRTIMER_ADCTRIGS3A_TRG3ST5C1                  BIT(0)               /*!< HRTIMER_ADCTRIG3 on Slave_TIMER5 compare 1 event */
#define HRTIMER_ADCTRIGS3A_TRG3ST5C2                  BIT(1)               /*!< HRTIMER_ADCTRIG3 on Slave_TIMER5 compare 2 event */
#define HRTIMER_ADCTRIGS3A_TRG3ST5C3                  BIT(2)               /*!< HRTIMER_ADCTRIG3 on Slave_TIMER5 compare 3 event */
#define HRTIMER_ADCTRIGS3A_TRG3ST5PER                 BIT(3)               /*!< HRTIMER_ADCTRIG3 on Slave_TIMER5 period event */
#define HRTIMER_ADCTRIGS3A_TRG3ST5RST                 BIT(4)               /*!< HRTIMER_ADCTRIG3 on Slave_TIMER5 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS3A_TRG3ST6C1                  BIT(8)               /*!< HRTIMER_ADCTRIG3 on Slave_TIMER6 compare 1 event */
#define HRTIMER_ADCTRIGS3A_TRG3ST6C2                  BIT(9)               /*!< HRTIMER_ADCTRIG3 on Slave_TIMER6 compare 2 event */
#define HRTIMER_ADCTRIGS3A_TRG3ST6C3                  BIT(10)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER6 compare 3 event */
#define HRTIMER_ADCTRIGS3A_TRG3ST6PER                 BIT(11)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER6 period event */
#define HRTIMER_ADCTRIGS3A_TRG3ST6RST                 BIT(12)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER6 reset and counter roll-over event */
#define HRTIMER_ADCTRIGS3A_TRG3ST7C1                  BIT(16)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER7 compare 1 event */
#define HRTIMER_ADCTRIGS3A_TRG3ST7C2                  BIT(17)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER7 compare 2 event */
#define HRTIMER_ADCTRIGS3A_TRG3ST7C3                  BIT(18)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER7 compare 3 event */
#define HRTIMER_ADCTRIGS3A_TRG3ST7PER                 BIT(19)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER7 period event */
#define HRTIMER_ADCTRIGS3A_TRG3ST7RST                 BIT(20)              /*!< HRTIMER_ADCTRIG3 on Slave_TIMER7 reset and counter roll-over event */


/* constants definitions */
typedef enum {COUNTER_UP = 0, COUNTER_DOWN = !COUNTER_UP} DirectionStatus;

/* HRTIMER time base parameters struct definitions */
typedef struct
{
    uint32_t period;                                                        /*!< period value, min value: 3*tHRTIMER_CK clock, max value: 0xFFFF C (1*tHRTIMER_CK) */
    uint32_t repetitioncounter;                                             /*!< the counter repetition value, 0x00~0xFF */
    uint32_t prescaler;                                                     /*!< prescaler value, refer to: counter clock division */
    uint32_t counter_mode;                                                  /*!< counter operating mode, refer to: counter operating mode */
    uint32_t counterdirection;                                              /*!< counter direction, refer to: counter direction mode */
}hrtimer_baseinit_parameter_struct;

/* waveform mode initialization parameters struct definitions */
typedef struct {
    uint32_t half_mode;                                                     /*!< specifies whether or not half mode is enabled, refer to: half mode enabling status */
    uint32_t alternate_mode;                                                /*!< specifies whether or not alternate mode is enabled, refer to: alternate mode enable status */
    uint32_t resynchronized_update;                                         /*!< specifies whether or not the update source is coming from other slave timer */
    uint32_t start_sync;                                                    /*!< specifies whether or not timer is started by a rising edge on the synchronization input, refer to: synchronous input start timer */
    uint32_t reset_sync;                                                    /*!< specifies whether or not timer is reset by a rising edge on the synchronization input, refer to: synchronous input reset timer */
    uint32_t dac_trigger;                                                   /*!< indicates whether or not the a DAC synchronization event is generated, refer to: trigger source to DAC */
    uint32_t shadow;                                                        /*!< specifies whether or not the shadow registers are enabled, refer to: shadow registers enabling status */
    uint32_t update_selection;                                              /*!< the update occurs with respect to DMA mode or STxUPINy (Slave_TIMERx only), refer to: update event selection */
    uint32_t cnt_bunch;                                                     /*!< the timer behaves during a bunch mode operation, refer to: timer behaves during a bunch mode operation */
    uint32_t repetition_update;                                             /*!< specifies whether or not registers update is triggered by the repetition event, refer to: update event generated by repetition event */
}hrtimer_timerinit_parameter_struct;

/* Slave_TIMER general behavior configuration struct definitions */
typedef struct {
    uint32_t balanced_mode;                                                 /*!< specifies whether or not the balanced mode is enabled, refer to: set balanced mode */
    uint32_t fault_enable;                                                  /*!< specifies whether or not the fault channels are enabled for the Slave_TIMER, refer to: faut channel enabled for a Slave_TIMER*/
    uint32_t fault_protect ;                                                /*!< specifies whether the write protection function is enable or not, refer to: protect fault enable */
    uint32_t deadtime_enable;                                               /*!< specifies whether or not dead time insertion is enabled for the timer, refer to: dead time enable */
    uint32_t delayed_idle;                                                  /*!< the delayed IDLE mode, refer to: set delayed IDLE state mode */
    uint32_t balanced_idle_automatic_resume;                                /*!< specifies whether or not the balanced idle automatic resumpe is enabled, refer to: balanced idle automatic resumption enable */
    uint32_t update_source;                                                 /*!< the source triggering the Slave_TIMER registers update, refer to: update is done synchronously with any other Slave_TIMER or Master_TIMER update */
    uint64_t cnt_reset;                                                     /*!< the source triggering the Slave_TIMER counter reset, refer to: Slave_TIMER counter reset */
    uint32_t reset_update;                                                  /*!< specifies whether or not registers update is triggered when the timer counter is reset, refer to: update event generated by reset event */
}hrtimer_timercfg_parameter_struct;

/* capture value struct definitions */
typedef struct {
    uint32_t value;                                                         /*!< capture value */
    uint32_t dir;                                                           /*!< count direation when captured */
}hrtimer_capture_value_struct;

/* compare unit configuration struct definitions */
typedef struct {
    uint32_t compare_value;                                                 /*!< compare value, min value: 3*tHRTIMER_CK clock, max value: 0xFFFF C (1*tHRTIMER_CK) */
    uint32_t delayed_mode;                                                  /*!< defining whether the compare register is behaving in regular mode or in delayed mode, refer to: compare 3 or 1 delayed mode */
    uint32_t timeout_value;                                                 /*!< compare value for compare 0 or 2 when compare 3 or 1 is delayed mode with time out is selected , timeout_value + compare_value must be less than 0xFFFF */
    uint32_t trigger_half;                                                  /*!< triggered half mode */
    uint32_t immediately_update_cmp0;                                       /*!< immediately update compare 0 value PWM mode */
    uint32_t immediately_update_cmp2;                                       /*!< immediately update compare 2 value PWM mode */
}hrtimer_comparecfg_parameter_struct;

/* external event filtering for Slave_TIMER configuration struct definitions */
typedef struct {
    uint32_t filter_mode;                                                   /*!< the external event filter mode for Slave_TIMER, refer to: external event filter mode */ 
    uint32_t memorized;                                                     /*!< specifies whether or not the signal is memorized, refer to: external event memorized enable */
}hrtimer_exevfilter_parameter_struct;

/* dead time configuration struct definitions */
typedef struct {
    uint32_t prescaler;                                                     /*!< dead time generator clock division, refer to: dead time prescaler */ 
    uint32_t rising_value;                                                  /*!< rising edge dead-time value, 0x0000~0xFFFF */ 
    uint32_t rising_sign;                                                   /*!< the sign of rising edge dead-time value, refer to: dead time rising sign */ 
    uint32_t rising_protect;                                                /*!< dead time rising edge protection for value and sign, refer to: dead time rising edge protection for value and sign */ 
    uint32_t risingsign_protect;                                            /*!< dead time rising edge protection for sign, refer to: dead time rising edge protection only for sign */ 
    uint32_t falling_value;                                                 /*!< falling edge dead-time value, 0x0000~0xFFFF */ 
    uint32_t falling_sign;                                                  /*!< the sign of falling edge dead-time value, refer to: dead time falling sign */ 
    uint32_t falling_protect;                                               /*!< dead time falling edge protection for value and sign, refer to: dead time falling edge protection for value and sign */
    uint32_t fallingsign_protect;                                           /*!< dead time falling edge protection for sign, refer to: dead time falling edge protection only for sign */
}hrtimer_deadtimecfg_parameter_struct;

/* carrier signal configuration struct definitions */
typedef struct {
    uint32_t period;                                                        /*!< carrier signal period: tCSPRD, 0x0~0xF. tCSPRD = (period + 1) * 16 * tHRTIMER_CK */
    uint32_t duty_cycle;                                                    /*!< carrier signal duty cycle, 0x0~0x7, duty cycle = duty_cycle/8 */
    uint32_t first_pulse;                                                   /*!< first carrier-signal pulse width: tCSFSTPW, 0x0~0xF. tCSFSTPW = (first_pulse+1) * 16 * tHRTIMER_CK */
}hrtimer_carriersignalcfg_parameter_struct;

/* synchronization configuration struct definitions */
typedef struct {
    uint32_t input_source;                                                  /*!< the external synchronization input source, refer to: the synchronization input source */
    uint32_t output_source;                                                 /*!< the source and event to be sent on the external synchronization outputs, refer to: the synchronization output source */
    uint32_t output_polarity;                                               /*!< the polarity and length of the pulse to be sent on the external synchronization outputs, refer to: the pulse on the synchronization output pad HRTIMER_SCOUT */
}hrtimer_synccfg_parameter_struct;

/* bunch mode configuration struct definitions */
typedef struct {
    uint32_t mode;                                                          /*!< the bunch mode operating mode, refer to: continuous mode in bunch mode */
    uint32_t clock_source;                                                  /*!< specifies the burst mode clock source, refer to: bunch mode clock source*/
    uint32_t prescaler;                                                     /*!< the bunch mode prescaler, refer to: bunch mode clock division */
    uint32_t shadow;                                                        /*!< specifies whether or not preload is enabled for HRTIMER_BMCMPV and HRTIMER_BMCAR registers, refer to: bunch mode shadow enable */
    uint32_t trigger[2];                                                    /*!< the event triggering the bunch operation, refer to: the event triggers bunch mode operation */
    uint32_t idle_duration;                                                 /*!< the duration of the IDLE, 0x0000~0xFFFF  */
    uint32_t period;                                                        /*!< the bunch mode period which is the sum of the IDLE and RUN duration, 0x0001~0xFFFF  */
}hrtimer_bunchmode_parameter_struct;

/* external event configuration struct definitions */
typedef struct {
    uint32_t source;                                                        /*!< the source of the external event,refer to: external event source */ 
    uint32_t polarity;                                                      /*!< the active level of external event 0 when EXEVyEG[1:0] = 2b00, refer to: external event polarity */ 
    uint32_t edge;                                                          /*!< the sensitivity of the external event, external event edge sensitivity */ 
    uint32_t fast;                                                          /*!< external event fast mode */ 
    uint32_t digital_filter;                                                /*!< external event filter control, 0x0~0xF */ 
}hrtimer_exeventcfg_parameter_struct;

/* HRTIMER event counter parameters struct definitions */
typedef struct
{
    uint32_t reset_mode;                                                    /*!< external event X reset mode */
    uint32_t counter_threshold;                                             /*!< external event X counter threshold value, 0x00~0x3F*/
    uint32_t event_source;                                                  /*!< external event X selection*/
}hrtimer_exeventcnt_parameter_struct;

/* fault input configuration struct definitions */
typedef struct {
    uint32_t source;                                                        /*!< the source of the fault input, refer to: fault input source */ 
    uint32_t polarity;                                                      /*!< the polarity of the fault input, refer to: fault input polarity */ 
    uint32_t filter;                                                        /*!< fault input filter control, 0x0~0xF */ 
    uint32_t control;                                                       /*!< fault input enable or disable, refer to: enable or disable fault */ 
    uint32_t protect ;                                                      /*!< protect fault input configuration, refer to: protect fault input configuration */
    uint32_t blanksource;                                                   /*!< fault blanking source */
    uint32_t counter;                                                       /*!< fault blanking counter */
    uint32_t resetmode;                                                     /*!< fault reset mode */
    uint32_t blanksenable;                                                  /*!< fault blank enable */
}hrtimer_faultcfg_parameter_struct;

/* ADC trigger configuration struct definitions */
typedef struct {
    uint32_t update_source;                                                 /*!< the source triggering the update of the HRTIMER_ADCTRIGSy register, refer to: HRTIMER_ADCTRIG update source */
    uint32_t trigger0_3[2];                                                 /*!< the event triggering the ADC conversion, refer to:  ADC trigger 0,2 and ADC trigger 1,3 */
    uint32_t trigger4_9;                                                    /*!< the event triggering the ADC conversion, refer to:  ADC trigger 4,6,8 and ADC trigger 5,7,9 */
}hrtimer_adctrigcfg_parameter_struct;

/* channel output configuration struct definitions */
typedef struct {
    uint32_t polarity;                                                      /*!< configure channel output polarity, refer to: channel output polarity */
    uint64_t set_request;                                                   /*!< configure the event generates channel set request, refer to channel set request */
    uint64_t reset_request;                                                 /*!< configure the event generates channel reset request, refer to: channel reset request */
    uint32_t idle_bunch;                                                    /*!< specifies whether channel output can be IDLE state in bunch mode, refer to: channel IDLE state enable in bunch mode */
    uint32_t idle_state;                                                    /*!< specifies channel output idle state, refer to channel output idle state */
    uint32_t fault_state;                                                   /*!< specifies the output level when in FAULT state, refer to: channel output in fault state */
    uint32_t carrier_mode;                                                  /*!< specifies whether or not the carrier-signal mode is enabled, refer to: channel carrier-signal mode enable */
    uint32_t deadtime_bunch;                                                /*!< specifies whether or not deadtime is inserted before output entering the IDLE state in bunch mode, refer to: channel dead-time insert in bunch mode */
}hrtimer_channel_outputcfg_parameter_struct;

/* roll over struct definitions */
typedef struct {
    uint32_t roll_over_mode;                                                /*!< roll-over mode */
    uint32_t output_roll_over_mode;                                         /*!< output roll-over mode */
    uint32_t adc_roll_over_mode;                                            /*!< ADC roll-over mode */
    uint32_t bunch_mode_roll_over_mode;                                     /*!< bunch mode roll-over mode */
    uint32_t fault_event_roll_over_mode;                                    /*!< fault and event roll-over mode */
}hrtimer_roll_over_parameter_struct;

/* roll over struct definitions */
typedef struct {
    uint32_t trigger_enable;                                                /*!< configure the double channel trigger enable */
    uint32_t trigger0;                                                      /*!< configure the double channel trigger0 */
    uint32_t trigger1;                                                      /*!< configure the double channel trigger1 */
}hrtimer_double_trigger_parameter_struct;

/* HRTIMER timer to configure */
#define HRTIMER_SLAVE_TIMER0                            ((uint32_t)0x00000000U)                                          /*!< index associated to Slave_TIMER0 */
#define HRTIMER_SLAVE_TIMER1                            ((uint32_t)0x00000001U)                                          /*!< index associated to Slave_TIMER1 */
#define HRTIMER_SLAVE_TIMER2                            ((uint32_t)0x00000002U)                                          /*!< index associated to Slave_TIMER2 */
#define HRTIMER_SLAVE_TIMER3                            ((uint32_t)0x00000003U)                                          /*!< index associated to Slave_TIMER3 */
#define HRTIMER_SLAVE_TIMER4                            ((uint32_t)0x00000004U)                                          /*!< index associated to Slave_TIMER4 */
#define HRTIMER_MASTER_TIMER                            ((uint32_t)0x00000006U)                                          /*!< index associated to Master_TIMER */
#define HRTIMER_COMMONINDEX                             ((uint32_t)0x00000007U)                                          /*!< index associated to common registers */
#define HRTIMER_SLAVE_TIMER5                            ((uint32_t)0x00000005U)                                          /*!< index associated to Slave_TIMER5 */
#define HRTIMER_SLAVE_TIMER6                            ((uint32_t)0x0000000FU)                                          /*!< index associated to Slave_TIMER6 */
#define HRTIMER_SLAVE_TIMER7                            ((uint32_t)0x00000010U)                                          /*!< index associated to Slave_TIMER7 */
                                                                                                                  
/* compare unit to configure */                                                                                   
#define HRTIMER_COMPARE0                                ((uint32_t)0x00000000U)                                          /*!< compare unit 0 */
#define HRTIMER_COMPARE1                                ((uint32_t)0x00000001U)                                          /*!< compare unit 1 */
#define HRTIMER_COMPARE2                                ((uint32_t)0x00000002U)                                          /*!< compare unit 2 */
#define HRTIMER_COMPARE3                                ((uint32_t)0x00000003U)                                          /*!< compare unit 3 */
#define HRTIMER_COMPARE0_COMPOSITE                      ((uint32_t)0x00000005U)                                          /*!< compare 0 composite unit */
                                                                                                                  
/* capture unit to configure */                                                                                   
#define HRTIMER_CAPTURE_0                               ((uint32_t)0x00000000U)                                          /*!< capture unit 0 */
#define HRTIMER_CAPTURE_1                               ((uint32_t)0x00000001U)                                          /*!< capture unit 1 */
                                                                                                                  
/* external event to configure */                                                                                 
#define HRTIMER_EXEVENT_NONE                            ((uint32_t)0x00000000U)                                          /*!< undefined event channel */
#define HRTIMER_EXEVENT_0                               ((uint32_t)0x00000001U)                                          /*!< extern event 0 */
#define HRTIMER_EXEVENT_1                               ((uint32_t)0x00000002U)                                          /*!< extern event 1 */
#define HRTIMER_EXEVENT_2                               ((uint32_t)0x00000004U)                                          /*!< extern event 2 */
#define HRTIMER_EXEVENT_3                               ((uint32_t)0x00000008U)                                          /*!< extern event 3 */
#define HRTIMER_EXEVENT_4                               ((uint32_t)0x00000010U)                                          /*!< extern event 4 */
#define HRTIMER_EXEVENT_5                               ((uint32_t)0x00000020U)                                          /*!< extern event 5 */
#define HRTIMER_EXEVENT_6                               ((uint32_t)0x00000040U)                                          /*!< extern event 6 */
#define HRTIMER_EXEVENT_7                               ((uint32_t)0x00000080U)                                          /*!< extern event 7  */
#define HRTIMER_EXEVENT_8                               ((uint32_t)0x00000100U)                                          /*!< extern event 8 */
#define HRTIMER_EXEVENT_9                               ((uint32_t)0x00000200U)                                          /*!< extern event 9 */
                                                                                                                  
/* fault to configure */                                                                                          
#define HRTIMER_FAULT_0                                 ((uint32_t)0x00000000U)                                          /*!< fault 0 */
#define HRTIMER_FAULT_1                                 ((uint32_t)0x00000001U)                                          /*!< fault 1 */
#define HRTIMER_FAULT_2                                 ((uint32_t)0x00000002U)                                          /*!< fault 2 */
#define HRTIMER_FAULT_3                                 ((uint32_t)0x00000004U)                                          /*!< fault 3 */
#define HRTIMER_FAULT_4                                 ((uint32_t)0x00000008U)                                          /*!< fault 4 */
#define HRTIMER_FAULT_5                                 ((uint32_t)0x00000010U)                                          /*!< fault 5 */
#define HRTIMER_FAULT_6                                 ((uint32_t)0x00000020U)                                          /*!< fault 6 */
#define HRTIMER_FAULT_7                                 ((uint32_t)0x00000040U)                                          /*!< fault 7 */
                                                                                                                  
/* HRTIMER_ADCTRIG to configure */                                                                               
#define HRTIMER_ADCTRIG_0                               ((uint32_t)0x00000000U)                                          /*!< HRTIMER_ADCTRIG0 */
#define HRTIMER_ADCTRIG_1                               ((uint32_t)0x00000001U)                                          /*!< HRTIMER_ADCTRIG1 */
#define HRTIMER_ADCTRIG_2                               ((uint32_t)0x00000002U)                                          /*!< HRTIMER_ADCTRIG2 */
#define HRTIMER_ADCTRIG_3                               ((uint32_t)0x00000003U)                                          /*!< HRTIMER_ADCTRIG3 */
#define HRTIMER_ADCTRIG_4                               ((uint32_t)0x00000004U)                                          /*!< HRTIMER_ADCTRIG4 */
#define HRTIMER_ADCTRIG_5                               ((uint32_t)0x00000005U)                                          /*!< HRTIMER_ADCTRIG5 */
#define HRTIMER_ADCTRIG_6                               ((uint32_t)0x00000006U)                                          /*!< HRTIMER_ADCTRIG6 */
#define HRTIMER_ADCTRIG_7                               ((uint32_t)0x00000007U)                                          /*!< HRTIMER_ADCTRIG7 */
#define HRTIMER_ADCTRIG_8                               ((uint32_t)0x00000008U)                                          /*!< HRTIMER_ADCTRIG8 */
#define HRTIMER_ADCTRIG_9                               ((uint32_t)0x00000009U)                                          /*!< HRTIMER_ADCTRIG9 */

/* channel to configure */                                                                                        
#define HRTIMER_ST0_CH0                                 ((uint32_t)0x00000001U)                                          /*!< Slave_TIMER0 channel 0 */
#define HRTIMER_ST0_CH1                                 ((uint32_t)0x00000002U)                                          /*!< Slave_TIMER0 channel 1 */
#define HRTIMER_ST1_CH0                                 ((uint32_t)0x00000004U)                                          /*!< Slave_TIMER1 channel 0 */
#define HRTIMER_ST1_CH1                                 ((uint32_t)0x00000008U)                                          /*!< Slave_TIMER1 channel 1 */
#define HRTIMER_ST2_CH0                                 ((uint32_t)0x00000010U)                                          /*!< Slave_TIMER2 channel 0 */
#define HRTIMER_ST2_CH1                                 ((uint32_t)0x00000020U)                                          /*!< Slave_TIMER2 channel 1 */
#define HRTIMER_ST3_CH0                                 ((uint32_t)0x00000040U)                                          /*!< Slave_TIMER3 channel 0 */
#define HRTIMER_ST3_CH1                                 ((uint32_t)0x00000080U)                                          /*!< Slave_TIMER3 channel 1 */
#define HRTIMER_ST4_CH0                                 ((uint32_t)0x00000100U)                                          /*!< Slave_TIMER4 channel 0 */
#define HRTIMER_ST4_CH1                                 ((uint32_t)0x00000200U)                                          /*!< Slave_TIMER4 channel 1 */
#define HRTIMER_ST5_CH0                                 ((uint32_t)0x00000400U)                                          /*!< Slave_TIMER5 channel 0 */
#define HRTIMER_ST5_CH1                                 ((uint32_t)0x00000800U)                                          /*!< Slave_TIMER5 channel 1 */
#define HRTIMER_ST6_CH0                                 ((uint32_t)0x00001000U)                                          /*!< Slave_TIMER6 channel 0 */
#define HRTIMER_ST6_CH1                                 ((uint32_t)0x00002000U)                                          /*!< Slave_TIMER6 channel 1 */
#define HRTIMER_ST7_CH0                                 ((uint32_t)0x00004000U)                                          /*!< Slave_TIMER7 channel 0 */
#define HRTIMER_ST7_CH1                                 ((uint32_t)0x00008000U)                                          /*!< Slave_TIMER7 channel 1 */
                                                                                                                  
/* the counter to enable/disable */                                                                               
#define HRTIMER_MT_COUNTER                              (HRTIMER_MTCTL0_MTCEN)                                          /*!< the counter of Master_TIMER */
#define HRTIMER_ST0_COUNTER                             (HRTIMER_MTCTL0_ST0CEN)                                         /*!< the counter of Slave_TIMER0 */
#define HRTIMER_ST1_COUNTER                             (HRTIMER_MTCTL0_ST1CEN)                                         /*!< the counter of Slave_TIMER1 */
#define HRTIMER_ST2_COUNTER                             (HRTIMER_MTCTL0_ST2CEN)                                         /*!< the counter of Slave_TIMER2 */
#define HRTIMER_ST3_COUNTER                             (HRTIMER_MTCTL0_ST3CEN)                                         /*!< the counter of Slave_TIMER3 */
#define HRTIMER_ST4_COUNTER                             (HRTIMER_MTCTL0_ST4CEN)                                         /*!< the counter of Slave_TIMER4 */
#define HRTIMER_ST5_COUNTER                             (HRTIMER_MTCTL0_ST5CEN)                                         /*!< the counter of Slave_TIMER5 */
#define HRTIMER_ST6_COUNTER                             (HRTIMER_MTCTL0_ST6CEN)                                         /*!< the counter of Slave_TIMER6 */
#define HRTIMER_ST7_COUNTER                             (HRTIMER_MTCTL0_ST7CEN)                                         /*!< the counter of Slave_TIMER7 */
                                                                                                                  
/* counter clock division */                                                                                      
#define HRTIMER_PRESCALER_MUL32                         ((uint32_t)0x00000000U)                                          /* fHRTIMER_PSSCK = fHPTIM_HPCK = 32 *fHRTIMER_CK */
#define HRTIMER_PRESCALER_MUL16                         ((uint32_t)0x00000001U)                                          /* fHRTIMER_PSSCK = fHPTIM_HPCK/2 = 16 *fHRTIMER_CK */
#define HRTIMER_PRESCALER_MUL8                          ((uint32_t)0x00000002U)                                          /* fHRTIMER_PSSCK = fHPTIM_HPCK/4 = 8 *fHRTIMER_CK */
#define HRTIMER_PRESCALER_MUL4                          ((uint32_t)0x00000003U)                                          /* fHRTIMER_PSSCK = fHPTIM_HPCK/8 = 4 *fHRTIMER_CK */
#define HRTIMER_PRESCALER_MUL2                          ((uint32_t)0x00000004U)                                          /* fHRTIMER_PSSCK = fHPTIM_HPCK/16= 2*fHRTIMER_CK */
#define HRTIMER_PRESCALER_DIV1                          ((uint32_t)0x00000005U)                                          /* fHRTIMER_PSSCK = fHPTIM_HPCK/32 = fHRTIMER_CK */
#define HRTIMER_PRESCALER_DIV2                          ((uint32_t)0x00000006U)                                          /* fHRTIMER_PSSCK = fHPTIM_HPCK/64 = fHRTIMER_CK/2 */
#define HRTIMER_PRESCALER_DIV4                          ((uint32_t)0x00000007U)                                          /* fHRTIMER_PSSCK = fHPTIM_HPCK/128 = fHRTIMER_CK/4 */

/* counter operating mode */
#define HRTIMER_COUNTER_MODE_CONTINOUS                  ((uint32_t)0x00000008U)                                          /*!< the timer operates in continuous (free-running) mode */
#define HRTIMER_COUNTER_MODE_SINGLEPULSE                ((uint32_t)0x00000000U)                                          /*!< single pulse mode: the counter can be reset only if it stops (period elapsed) */
#define HRTIMER_COUNTER_MODE_SINGLEPULSE_RETRIGGERABLE  ((uint32_t)0x00000010U)                                          /*!< single pulse mode: the counter can be reset at any time (running or stopped) */

/* counter direction mode */
#define HRTIMER_COUNTER_UP                               ((uint32_t)0x00000000U)                                          /*!< the timer operates in continuous (free-running) mode */
#define HRTIMER_COUNTER_CENTER_ALIGNED                   (HRTIMER_STXCTL1_CAM)                                          /*!< single pulse mode: the counter can be reset only if it stops (period elapsed) */

/* half mode enable status */
#define HRTIMER_HALFMODE_DISABLED                       ((uint32_t)0x00000000U)                                          /*!< half mode disable */
#define HRTIMER_HALFMODE_ENABLED                        ((uint32_t)0x00000020U)                                          /*!< half mode enable */

/* alternate mode enable status */
#define HRTIMER_ALTERNATE_MODE_DISABLED                 ((uint32_t)0x00000000U)                                          /*!< alternate mode disabled */
#define HRTIMER_ALTERNATE_MODE_TRIPLE                   ((uint32_t)0x00000080U)                                          /*!< triple alternate mode */
#define HRTIMER_ALTERNATE_MODE_QUAD                     ((uint32_t)0x00000100U)                                          /*!< quad alternate mode */

/* re-synchronized update mode */
#define HRTIMER_RSYUPD_DISABLED                         ((uint32_t)0x00000000U)                                          /*!< re-synchronized update mode disabled */
#define HRTIMER_RSYUPD_ENABLED                          (HRTIMER_STXCTL0_RSYNUPD)                                       /*!< re-synchronized update mode enabled */

/* synchronous input start timer */
#define HRTIMER_SYNISTART_DISABLED                      ((uint32_t)0x00000000U)                                          /*!< the synchronous input signal cannot start the counter */
#define HRTIMER_SYNISTART_ENABLED                       ((uint32_t)0x00000800U)                                          /*!< the synchronous input signal can start the counter */

/* synchronous input reset timer */
#define HRTIMER_SYNCRESET_DISABLED                      ((uint32_t)0x00000000U)                                          /*!< the synchronous input signal cannot reset the counter */
#define HRTIMER_SYNCRESET_ENABLED                       ((uint32_t)0x00000400U)                                          /*!< the synchronous input signal can reset the counter */

/* trigger source to DAC */
#define HRTIMER_DAC_TRIGGER_NONE                        ((uint32_t)0x00000000U)                                          /*!< no DAC trigger event generated */
#define HRTIMER_DAC_TRIGGER_DACTRIG0                    ((uint32_t)0x02000000U)                                          /*!< DAC trigger event generated on HRTIMER_DACTRIG0 */
#define HRTIMER_DAC_TRIGGER_DACTRIG1                    ((uint32_t)0x04000000U)                                          /*!< DAC trigger event generated on HRTIMER_DACTRIG1 */
#define HRTIMER_DAC_TRIGGER_DACTRIG2                    ((uint32_t)0x06000000U)                                          /*!< DAC trigger event generated on HRTIMER_DACTRIG2 */

/* shadow registers enable status */
#define HRTIMER_SHADOW_DISABLED                         ((uint32_t)0x00000000U)                                          /*!< the shadow registers are disabled: the write access is directly done into the active registers */
#define HRTIMER_SHADOW_ENABLED                          ((uint32_t)0x08000000U)                                          /*!< the shadow registers are enabled: the write access is done into the shadow registers */

/* update event selection */
#define HRTIMER_MT_ST_UPDATE_SELECTION_INDEPENDENT      ((uint32_t)0x00000000U)                                          /*!< update event generated independently from DMA mode */
#define HRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE          ((uint32_t)0x10000000U)                                          /*!< update event generated when the DMA transfer completed in DMA mode */
#define HRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE_UPDATE   ((uint32_t)0x20000000U)                                          /*!< update event generated on the update event following the DMA transfer completed in DMA mode */
#define HRTIMER_ST_UPDATE_SELECTION_STXUPIN0            ((uint32_t)0x30000000U)                                          /*!< update event generated on the rising edge of STxUPIN0 */
#define HRTIMER_ST_UPDATE_SELECTION_STXUPIN0_UPDATE     ((uint32_t)0x60000000U)                                          /*!< update event generated on the update event following the rising edge of STxUPIN0 */
#define HRTIMER_ST_UPDATE_SELECTION_STXUPIN1            ((uint32_t)0x40000000U)                                          /*!< update event generated on the rising edge of STxUPIN1 */
#define HRTIMER_ST_UPDATE_SELECTION_STXUPIN1_UPDATE     ((uint32_t)0x70000000U)                                          /*!< update event generated on the update event following the rising edge of STxUPIN1 */
#define HRTIMER_ST_UPDATE_SELECTION_STXUPIN2            ((uint32_t)0x50000000U)                                          /*!< update event generated on the rising edge of STxUPIN2 */
#define HRTIMER_ST_UPDATE_SELECTION_STXUPIN2_UPDATE     ((uint32_t)0x80000000U)                                          /*!< update event generated on the update event following the rising edge of STxUPIN2 */

/* timer behaves during a bunch mode operation */
#define HRTIMER_TIMERBUNCHNMODE_MAINTAINCLOCK           ((uint32_t)0x00000000U)                                          /*!< counter clock(HRTIMER_PSCCK) is maintained and the counter operates normally */
#define HRTIMER_TIMERBUNCHMODE_RESETCOUNTER             ((uint32_t)0x00010000U)                                          /*!< counter clock(HRTIMER_PSCCK) is stopped and the counter is reset */

/* update event generated by repetition event */
#define HRTIMER_UPDATEONREPETITION_DISABLED             ((uint32_t)0x00000000U)                                          /*!< update event generated by repetition event disable */
#define HRTIMER_UPDATEONREPETITION_ENABLED              ((uint32_t)0x20000000U)                                          /*!< update event generated by repetition event enable */

/* set balanced mode */
#define HRTIMER_STXBALANCEDMODE_DISABLED                ((uint32_t)0x00000000U)                                          /*!< balanced mode disabled */ 
#define HRTIMER_STXBALANCEDMODE_ENABLED                 ((uint32_t)0x00000040U)                                          /*!< balanced mode enabled */

/* faut channel enabled for a Slave_TIMER */
#define HRTIMER_STXFAULTENABLE_NONE                     ((uint32_t)0x00000000U)                                          /*!< no fault enabled */ 
#define HRTIMER_STXFAULTENABLE_FAULT0                   (HRTIMER_STXFLTCTL_FLT0EN)                                       /*!< fault 0 enabled */ 
#define HRTIMER_STXFAULTENABLE_FAULT1                   (HRTIMER_STXFLTCTL_FLT1EN)                                       /*!< fault 1 enabled */ 
#define HRTIMER_STXFAULTENABLE_FAULT2                   (HRTIMER_STXFLTCTL_FLT2EN)                                       /*!< fault 2 enabled */
#define HRTIMER_STXFAULTENABLE_FAULT3                   (HRTIMER_STXFLTCTL_FLT3EN)                                       /*!< fault 3 enabled */
#define HRTIMER_STXFAULTENABLE_FAULT4                   (HRTIMER_STXFLTCTL_FLT4EN)                                       /*!< fault 4 enabled */
#define HRTIMER_STXFAULTENABLE_FAULT5                   (HRTIMER_STXFLTCTL_FLT5EN)                                       /*!< fault 5 enabled */
#define HRTIMER_STXFAULTENABLE_FAULT6                   (HRTIMER_STXFLTCTL_FLT6EN)                                       /*!< fault 6 enabled */
#define HRTIMER_STXFAULTENABLE_FAULT7                   (HRTIMER_STXFLTCTL_FLT7EN)                                       /*!< fault 7 enabled */

/* protect fault enable */
#define HRTIMER_STXFAULT_PROTECT_READWRITE              ((uint32_t)0x00000000U)                                          /*!< protect disable. FLTyEN (y=0..7) is writable */
#define HRTIMER_STXFAULT_PROTECT_READONLY               (HRTIMER_STXFLTCTL_FLTENPROT)                                    /*!< protect enable. FLTyEN (y=0..7) is read-only */

/* dead time enable */
#define HRTIMER_STXDEADTIME_DISABLED                    ((uint32_t)0x00000000U)                                          /*!< channel 0 and channel 1 outputs are independent. */
#define HRTIMER_STXDEADTIME_ENABLED                     (HRTIMER_STXCHOCTL_DTEN)                                         /*!< channel 0 and channel 1 outputs are complementary and dead-time is inserted between channel 0 and channel 1 outputs */

/* set delayed IDLE state mode */
#define HRTIMER_STXDELAYED_IDLE_DISABLED                ((uint32_t)0x00000000U)                                          /*!< no action */
#define HRTIMER_STXDELAYED_IDLE_CH0_EEV57               (HRTIMER_STXCHOCTL_DLYISMEN)                                     /*!< channel 0 output delayed IDLE on external event 5 or 7 */
#define HRTIMER_STXDELAYED_IDLE_CH1_EEV57               (((uint32_t)0x00000400U) | HRTIMER_STXCHOCTL_DLYISMEN)           /*!< channel 1 output delayed IDLE on external event 5 or 7 */
#define HRTIMER_STXDELAYED_IDLE_BOTH_EEV57              (((uint32_t)0x00000800U) | HRTIMER_STXCHOCTL_DLYISMEN)           /*!< channel 0 and channel 1 output delayed IDLE on external event 5 or 7 */
#define HRTIMER_STXDELAYED_IDLE_BALANCED_EEV57          (((uint32_t)0x00000C00U) | HRTIMER_STXCHOCTL_DLYISMEN)           /*!< balanced IDLE on external event 5 or 7 */      
#define HRTIMER_STXDELAYED_IDLE_CH0_DEEV68              (((uint32_t)0x00001000U) | HRTIMER_STXCHOCTL_DLYISMEN)           /*!< channel 0 output delayed IDLE on external event 6 or 8 */
#define HRTIMER_STXDELAYED_IDLE_CH1_DEEV68              (((uint32_t)0x00001400U) | HRTIMER_STXCHOCTL_DLYISMEN)           /*!< channel 1 output delayed IDLE on external event 6 or 8 */
#define HRTIMER_STXDELAYED_IDLE_BOTH_EEV68              (((uint32_t)0x00001800U) | HRTIMER_STXCHOCTL_DLYISMEN)           /*!< channel 0 and channel 1 output delayed IDLE on external event 6 or 8 */
#define HRTIMER_STXDELAYED_IDLE_BALANCED_EEV68          (((uint32_t)0x00001C00U) | HRTIMER_STXCHOCTL_DLYISMEN)           /*!< balanced IDLE on external event 6 or 8 */

/* balanced idle automatic resumption enable */
#define HRTIMER_BALANE_IDLE_AUTOMATIC_RESUME_DISABLE    ((uint32_t)0x00000000U)                                          /*!< balanced idle automatic resumption disable */
#define HRTIMER_BALANE_IDLE_AUTOMATIC_RESUME_ENABLE     (HRTIMER_STXCHOCTL_BALIAR)                                       /*!< balanced idle automatic resumption enable */

/* update is done synchronously with any other Slave_TIMER or Master_TIMER update */
#define HRTIMER_STXUPDATETRIGGER_NONE                   ((uint32_t)0x00000000U)                                          /*!< register update is disabled */    
#define HRTIMER_STXUPDATETRIGGER_MASTER                 (HRTIMER_STXCTL0_UPBMT)                                          /*!< update by Master_TIMER update event */    
#define HRTIMER_STXUPDATETRIGGER_ST0                    (HRTIMER_STXCTL0_UPBST0)                                         /*!< update by Slave_TIMER0 update event */    
#define HRTIMER_STXUPDATETRIGGER_ST1                    (HRTIMER_STXCTL0_UPBST1)                                         /*!< update by Slave_TIMER1 update event */    
#define HRTIMER_STXUPDATETRIGGER_ST2                    (HRTIMER_STXCTL0_UPBST2)                                         /*!< update by Slave_TIMER2 update event */    
#define HRTIMER_STXUPDATETRIGGER_ST3                    (HRTIMER_STXCTL0_UPBST3)                                         /*!< update by Slave_TIMER3 update event */    
#define HRTIMER_STXUPDATETRIGGER_ST4                    (HRTIMER_STXCTL0_UPBST4)                                         /*!< update by Slave_TIMER4 update event */    
#define HRTIMER_STXUPDATETRIGGER_ST5                    (HRTIMER_STXCTL0_UPBST5)                                         /*!< update by Slave_TIMER5 update event */
#define HRTIMER_STXUPDATETRIGGER_ST6                    ((uint32_t)(0x80000000U | HRTIMER_STXACTL_UPBST6))               /*!< update by Slave_TIMER6 update event */
#define HRTIMER_STXUPDATETRIGGER_ST7                    ((uint32_t)(0x80000000U | HRTIMER_STXACTL_UPBST7))               /*!< update by Slave_TIMER7 update event */

/* Slave_TIMER counter reset */
#define HRTIMER_STXCNT_RESET_NONE                       ((uint64_t)0x0000000000000000U)                                  /*!< no counter reset trigger */
#define HRTIMER_STXCNT_RESET_OTHER4_CMP0                BIT(0)                                                           /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 0 event */
#define HRTIMER_STXCNT_RESET_ST5_CMP0                   BIT(0)                                                           /*!< the Slave_TIMER 0~4 counter is reset upon Slave_TIMER5 compare 0 event */ 
#define HRTIMER_STXCNT_RESET_UPDATE                     (HRTIMER_STXCNTRST_UPRST)                                        /*!< the Slave_TIMER counter is reset upon update event */    
#define HRTIMER_STXCNT_RESET_CMP1                       (HRTIMER_STXCNTRST_CMP1RST)                                      /*!< the Slave_TIMER counter is reset upon Slave_TIMER compare 1 event */
#define HRTIMER_STXCNT_RESET_CMP3                       (HRTIMER_STXCNTRST_CMP3RST)                                      /*!< the Slave_TIMER counter is reset upon Slave_TIMER compare 3 event */
#define HRTIMER_STXCNT_RESET_MASTER_PER                 (HRTIMER_STXCNTRST_MTPERRST)                                     /*!< the Slave_TIMER counter is reset upon Master_TIMER period event */
#define HRTIMER_STXCNT_RESET_MASTER_CMP0                (HRTIMER_STXCNTRST_MTCMP0RST)                                    /*!< the Slave_TIMER counter is reset upon Master_TIMER compare 0 event */
#define HRTIMER_STXCNT_RESET_MASTER_CMP1                (HRTIMER_STXCNTRST_MTCMP1RST)                                    /*!< the Slave_TIMER counter is reset upon Master_TIMER compare 1 event */
#define HRTIMER_STXCNT_RESET_MASTER_CMP2                (HRTIMER_STXCNTRST_MTCMP2RST)                                    /*!< the Slave_TIMER counter is reset upon Master_TIMER compare 2 event */
#define HRTIMER_STXCNT_RESET_MASTER_CMP3                (HRTIMER_STXCNTRST_MTCMP3RST)                                    /*!< the Slave_TIMER counter is reset upon Master_TIMER compare 3 event */
#define HRTIMER_STXCNT_RESET_EEV_0                      (HRTIMER_STXCNTRST_EXEV0RST)                                     /*!< the Slave_TIMER counter is reset upon external event 0 */
#define HRTIMER_STXCNT_RESET_EEV_1                      (HRTIMER_STXCNTRST_EXEV1RST)                                     /*!< the Slave_TIMER counter is reset upon external event 1 */
#define HRTIMER_STXCNT_RESET_EEV_2                      (HRTIMER_STXCNTRST_EXEV2RST)                                     /*!< the Slave_TIMER counter is reset upon external event 2 */
#define HRTIMER_STXCNT_RESET_EEV_3                      (HRTIMER_STXCNTRST_EXEV3RST)                                     /*!< the Slave_TIMER counter is reset upon external event 3 */
#define HRTIMER_STXCNT_RESET_EEV_4                      (HRTIMER_STXCNTRST_EXEV4RST)                                     /*!< the Slave_TIMER counter is reset upon external event 4 */
#define HRTIMER_STXCNT_RESET_EEV_5                      (HRTIMER_STXCNTRST_EXEV5RST)                                     /*!< the Slave_TIMER counter is reset upon external event 5 */
#define HRTIMER_STXCNT_RESET_EEV_6                      (HRTIMER_STXCNTRST_EXEV6RST)                                     /*!< the Slave_TIMER counter is reset upon external event 6 */
#define HRTIMER_STXCNT_RESET_EEV_7                      (HRTIMER_STXCNTRST_EXEV7RST)                                     /*!< the Slave_TIMER counter is reset upon external event 7 */
#define HRTIMER_STXCNT_RESET_EEV_8                      (HRTIMER_STXCNTRST_EXEV8RST)                                     /*!< the Slave_TIMER counter is reset upon external event 8 */
#define HRTIMER_STXCNT_RESET_EEV_9                      (HRTIMER_STXCNTRST_EXEV9RST)                                     /*!< the Slave_TIMER counter is reset upon external event 9 */
#define HRTIMER_STXCNT_RESET_OTHER0_CMP0                BIT(19)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 0 event */
#define HRTIMER_STXCNT_RESET_OTHER0_CMP1                BIT(20)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 1 event */
#define HRTIMER_STXCNT_RESET_OTHER0_CMP3                BIT(21)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 3 event */
#define HRTIMER_STXCNT_RESET_OTHER1_CMP0                BIT(22)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 0 event */
#define HRTIMER_STXCNT_RESET_OTHER1_CMP1                BIT(23)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 1 event */
#define HRTIMER_STXCNT_RESET_OTHER1_CMP3                BIT(24)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 3 event */
#define HRTIMER_STXCNT_RESET_OTHER2_CMP0                BIT(25)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 0 event */
#define HRTIMER_STXCNT_RESET_OTHER2_CMP1                BIT(26)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 1 event */
#define HRTIMER_STXCNT_RESET_OTHER2_CMP3                BIT(27)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 3 event */
#define HRTIMER_STXCNT_RESET_OTHER3_CMP0                BIT(28)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 0 event */
#define HRTIMER_STXCNT_RESET_OTHER3_CMP1                BIT(29)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 1 event */
#define HRTIMER_STXCNT_RESET_OTHER3_CMP3                BIT(30)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 3 event */
#define HRTIMER_STXCNT_RESET_OTHER4_CMP1                BIT(31)                                                          /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 1 event */
#define HRTIMER_STXCNT_RESET_OTHER4_CMP3                (((uint64_t)BIT(0)) << 32)                                       /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 3 event */
#define HRTIMER_STXCNT_RESET_OTHER5_CMP0                (((uint64_t)BIT(1)) << 32)                                       /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 0 event */
#define HRTIMER_STXCNT_RESET_OTHER5_CMP1                (((uint64_t)BIT(2)) << 32)                                       /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 1 event */
#define HRTIMER_STXCNT_RESET_OTHER5_CMP3                (((uint64_t)BIT(3)) << 32)                                       /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 3 event */
#define HRTIMER_STXCNT_RESET_OTHER6_CMP0                (((uint64_t)BIT(4)) << 32)                                       /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 0 event */
#define HRTIMER_STXCNT_RESET_OTHER6_CMP1                (((uint64_t)BIT(5)) << 32)                                       /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 1 event */
#define HRTIMER_STXCNT_RESET_OTHER6_CMP3                (((uint64_t)BIT(6)) << 32)                                       /*!< the Slave_TIMER counter is reset upon other Slave_TIMER compare 3 event */

/* update event generated by reset event */
#define HRTIMER_STXUPDATEONRESET_DISABLED               ((uint32_t)0x00000000U)                                          /*!< update event generated by reset event or roll-over event disable */
#define HRTIMER_STXUPDATEONRESET_ENABLED                (HRTIMER_STXCTL0_UPRST)                                          /*!< update event generated by reset event or roll-over event enable */

/* compare 3 or 1 delayed mode */
#define HRTIMER_DELAYEDMODE_DISABLE                     ((uint32_t)0x00000000U)                                          /*!< delayed mode disable */
#define HRTIMER_DELAYEDMODE_NOTIMEOUT                   ((uint32_t)0x00001000U)                                          /*!< compare event generated only if a capture has occurred */
#define HRTIMER_DELAYEDMODE_TIMEOUTCMP0                 ((uint32_t)0x00002000U)                                          /*!< compare event generated if a capture has occurred or after a compare 0 match (timeout if capture event is missing) */
#define HRTIMER_DELAYEDMODE_TIMEOUTCMP2                 ((uint32_t)0x00003000U)                                          /*!< compare event generated if a capture has occurred or after a compare 2 match (timeout if capture event is missing) */

/* capture trigger source */
#define HRTIMER_CAPTURETRIGGER_NONE                     ((uint64_t)0x0000000000000000U)                                  /*!< capture trigger is disabled */    
#define HRTIMER_CAPTURETRIGGER_UPDATE                   (HRTIMER_STXCAP0TRG_CP0BUP)                                      /*!< capture triggered by update event */    
#define HRTIMER_CAPTURETRIGGER_EXEV_0                   (HRTIMER_STXCAP0TRG_CP0BEXEV0)                                   /*!< capture triggered by external event 0 */    
#define HRTIMER_CAPTURETRIGGER_EXEV_1                   (HRTIMER_STXCAP0TRG_CP0BEXEV1)                                   /*!< capture triggered by external event 1 */    
#define HRTIMER_CAPTURETRIGGER_EXEV_2                   (HRTIMER_STXCAP0TRG_CP0BEXEV2)                                   /*!< capture triggered by external event 2 */    
#define HRTIMER_CAPTURETRIGGER_EXEV_3                   (HRTIMER_STXCAP0TRG_CP0BEXEV3)                                   /*!< capture triggered by external event 3 */    
#define HRTIMER_CAPTURETRIGGER_EXEV_4                   (HRTIMER_STXCAP0TRG_CP0BEXEV4)                                   /*!< capture triggered by external event 4 */    
#define HRTIMER_CAPTURETRIGGER_EXEV_5                   (HRTIMER_STXCAP0TRG_CP0BEXEV5)                                   /*!< capture triggered by external event 5 */    
#define HRTIMER_CAPTURETRIGGER_EXEV_6                   (HRTIMER_STXCAP0TRG_CP0BEXEV6)                                   /*!< capture triggered by external event 6 */    
#define HRTIMER_CAPTURETRIGGER_EXEV_7                   (HRTIMER_STXCAP0TRG_CP0BEXEV7)                                   /*!< capture triggered by external event 7 */    
#define HRTIMER_CAPTURETRIGGER_EXEV_8                   (HRTIMER_STXCAP0TRG_CP0BEXEV8)                                   /*!< capture triggered by external event 8 */    
#define HRTIMER_CAPTURETRIGGER_EXEV_9                   (HRTIMER_STXCAP0TRG_CP0BEXEV9)                                   /*!< capture triggered by external event 9 */    
#define HRTIMER_CAPTURETRIGGER_ST0_ACTIVE               (HRTIMER_STXCAP0TRG_CP0BST0A)                                    /*!< capture triggered by ST0CH0_O output inactive to active transition */
#define HRTIMER_CAPTURETRIGGER_ST0_INACTIVE             (HRTIMER_STXCAP0TRG_CP0BST0NA)                                   /*!< capture triggered by ST0CH0_O output active to inactive transition */
#define HRTIMER_CAPTURETRIGGER_ST0_CMP0                 (HRTIMER_STXCAP0TRG_CP0BST0CMP0)                                 /*!< capture triggered by compare 0 event of Slave_TIMER0 */
#define HRTIMER_CAPTURETRIGGER_ST0_CMP1                 (HRTIMER_STXCAP0TRG_CP0BST0CMP1)                                 /*!< capture triggered by compare 0 event of Slave_TIMER0 */
#define HRTIMER_CAPTURETRIGGER_ST1_ACTIVE               (HRTIMER_STXCAP0TRG_CP0BST1A)                                    /*!< capture triggered by ST1CH0_O output inactive to active transition */
#define HRTIMER_CAPTURETRIGGER_ST1_INACTIVE             (HRTIMER_STXCAP0TRG_CP0BST1NA)                                   /*!< capture triggered by ST1CH0_O output active to inactive transition */
#define HRTIMER_CAPTURETRIGGER_ST1_CMP0                 (HRTIMER_STXCAP0TRG_CP0BST1CMP0)                                 /*!< capture triggered by compare 0 event of Slave_TIMER1 */
#define HRTIMER_CAPTURETRIGGER_ST1_CMP1                 (HRTIMER_STXCAP0TRG_CP0BST1CMP1)                                 /*!< capture triggered by compare 0 event of Slave_TIMER1 */
#define HRTIMER_CAPTURETRIGGER_ST2_ACTIVE               (HRTIMER_STXCAP0TRG_CP0BST2A)                                    /*!< capture triggered by ST2CH0_O output inactive to active transition */
#define HRTIMER_CAPTURETRIGGER_ST2_INACTIVE             (HRTIMER_STXCAP0TRG_CP0BST2NA)                                   /*!< capture triggered by ST2CH0_O output active to inactive transition */
#define HRTIMER_CAPTURETRIGGER_ST2_CMP0                 (HRTIMER_STXCAP0TRG_CP0BST2CMP0)                                 /*!< capture triggered by compare 0 event of Slave_TIMER2 */
#define HRTIMER_CAPTURETRIGGER_ST2_CMP1                 (HRTIMER_STXCAP0TRG_CP0BST2CMP1)                                 /*!< capture triggered by compare 0 event of Slave_TIMER2 */
#define HRTIMER_CAPTURETRIGGER_ST3_ACTIVE               (HRTIMER_STXCAP0TRG_CP0BST3A)                                    /*!< capture triggered by ST3CH0_O output inactive to active transition */
#define HRTIMER_CAPTURETRIGGER_ST3_INACTIVE             (HRTIMER_STXCAP0TRG_CP0BST3NA)                                   /*!< capture triggered by ST3CH0_O output active to inactive transition */
#define HRTIMER_CAPTURETRIGGER_ST3_CMP0                 (HRTIMER_STXCAP0TRG_CP0BST3CMP0)                                 /*!< capture triggered by compare 0 event of Slave_TIMER3 */
#define HRTIMER_CAPTURETRIGGER_ST3_CMP1                 (HRTIMER_STXCAP0TRG_CP0BST3CMP1)                                 /*!< capture triggered by compare 0 event of Slave_TIMER3 */
#define HRTIMER_CAPTURETRIGGER_ST4_ACTIVE               (HRTIMER_STXCAP0TRG_CP0BST4A)                                    /*!< capture triggered by ST4CH0_O output inactive to active transition */
#define HRTIMER_CAPTURETRIGGER_ST4_INACTIVE             (HRTIMER_STXCAP0TRG_CP0BST4NA)                                   /*!< capture triggered by ST4CH0_O output active to inactive transition */
#define HRTIMER_CAPTURETRIGGER_ST4_CMP0                 (HRTIMER_STXCAP0TRG_CP0BST4CMP0)                                 /*!< capture triggered by compare 0 event of Slave_TIMER4 */
#define HRTIMER_CAPTURETRIGGER_ST4_CMP1                 (HRTIMER_STXCAP0TRG_CP0BST4CMP1)                                 /*!< capture triggered by compare 0 event of Slave_TIMER4 */
#define HRTIMER_CAPTURETRIGGER_ST5_ACTIVE               (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST5A) << 32)                /*!< capture triggered by ST5CH0_O output inactive to active transition */
#define HRTIMER_CAPTURETRIGGER_ST5_INACTIVE             (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST5NA) << 32)               /*!< capture triggered by ST5CH0_O output active to inactive transition */
#define HRTIMER_CAPTURETRIGGER_ST5_CMP0                 (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST5CMP0) << 32)             /*!< capture triggered by compare 0 event of Slave_TIMER5 */
#define HRTIMER_CAPTURETRIGGER_ST5_CMP1                 (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST5CMP1) << 32)             /*!< capture triggered by compare 0 event of Slave_TIMER5 */
#define HRTIMER_CAPTURETRIGGER_ST6_ACTIVE               (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST6A) << 32)                /*!< capture triggered by ST6CH0_O output inactive to active transition */
#define HRTIMER_CAPTURETRIGGER_ST6_INACTIVE             (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST6NA) << 32)               /*!< capture triggered by ST6CH0_O output active to inactive transition */
#define HRTIMER_CAPTURETRIGGER_ST6_CMP0                 (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST6CMP0) << 32)             /*!< capture triggered by compare 0 event of Slave_TIMER6 */
#define HRTIMER_CAPTURETRIGGER_ST6_CMP1                 (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST6CMP1) << 32)             /*!< capture triggered by compare 0 event of Slave_TIMER6 */
#define HRTIMER_CAPTURETRIGGER_ST7_ACTIVE               (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST7A) << 32)                /*!< capture triggered by ST7CH0_O output inactive to active transition */
#define HRTIMER_CAPTURETRIGGER_ST7_INACTIVE             (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST7NA) << 32)               /*!< capture triggered by ST7CH0_O output active to inactive transition */
#define HRTIMER_CAPTURETRIGGER_ST7_CMP0                 (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST7CMP0) << 32)             /*!< capture triggered by compare 0 event of Slave_TIMER7 */
#define HRTIMER_CAPTURETRIGGER_ST7_CMP1                 (((uint64_t)HRTIMER_STXCAPTRGCOM_CP0BST7CMP1) << 32)             /*!< capture triggered by compare 0 event of Slave_TIMER7 */

/* external event filter mode */
#define HRTIMER_EXEVFILTER_DISABLE                      ((uint32_t)0x00000000U)                                          /* filter mode disable */   
#define HRTIMER_EXEVFILTER_BLANKINGCMP0                 ((uint32_t)0x00000002U)                                          /*!< blanking mode. the blank is from counter reset/roll-over to HRTIMER_STxCMP0V */
#define HRTIMER_EXEVFILTER_BLANKINGCMP1                 ((uint32_t)0x00000004U)                                          /*!< blanking mode. the blank is from counter reset/roll-over to HRTIMER_STxCMP1V */
#define HRTIMER_EXEVFILTER_BLANKINGCMP2                 ((uint32_t)0x00000006U)                                          /*!< blanking mode. the blank is from counter reset/roll-over to HRTIMER_STxCMP2V */
#define HRTIMER_EXEVFILTER_BLANKINGCMP3                 ((uint32_t)0x00000008U)                                          /*!< blanking mode. the blank is from counter reset/roll-over to HRTIMER_STxCMP3V */
#define HRTIMER_EXEVFILTER_BLANKINGSRC0                 ((uint32_t)0x0000000AU)                                          /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC0 */
#define HRTIMER_EXEVFILTER_BLANKINGSRC1                 ((uint32_t)0x0000000CU)                                          /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC1 */
#define HRTIMER_EXEVFILTER_BLANKINGSRC2                 ((uint32_t)0x0000000EU)                                          /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC2 */
#define HRTIMER_EXEVFILTER_BLANKINGSRC3                 ((uint32_t)0x00000010U)                                          /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC3 */
#define HRTIMER_EXEVFILTER_BLANKINGSRC4                 ((uint32_t)0x00000012U)                                          /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC4 */
#define HRTIMER_EXEVFILTER_BLANKINGSRC5                 ((uint32_t)0x00000014U)                                          /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC5 */
#define HRTIMER_EXEVFILTER_BLANKINGSRC6                 ((uint32_t)0x00000016U)                                          /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC6 */
#define HRTIMER_EXEVFILTER_BLANKINGSRC7                 ((uint32_t)0x00000018U)                                          /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC7 */
#define HRTIMER_EXEVFILTER_WINDOWINGCMP1                ((uint32_t)0x0000001AU)                                          /*!< windowing mode. the windowing is from counter reset/roll-over to HRTIMER_STxCMP1V */
#define HRTIMER_EXEVFILTER_WINDOWINGCMP2                ((uint32_t)0x0000001CU)                                          /*!< windowing mode. the windowing is from counter reset/roll-over to HRTIMER_STxCMP2V */
#define HRTIMER_EXEVFILTER_WINDOWINGSRC                 ((uint32_t)0x0000001EU)                                          /*!< windowing mode. the windowing is from other Slave_TIMERy(not Slave_TIMERx):STWDSRC */
#define HRTIMER_EXEVFILTER_BLANKINGSRC8                 ((uint32_t)0x00000020U)                                          /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC8 */
#define HRTIMER_EXEVFILTER_BLANKINGSRC9                 ((uint32_t)0x00000022U)                                          /*!< blanking mode. the blank is from other Slave_TIMERy(not Slave_TIMERx): STBLKSRC9 */

/* external event memorized enable */
#define HRTIMER_EXEVMEMORIZED_DISABLE                   ((uint32_t)0x00000000U)                                          /*!< external event memory disable */
#define HRTIMER_EXEVMEMORIZED_ENABLE                    (HRTIMER_STXEXEVFCFG0_EXEV0MEEN)                                 /*!< external event memory  enable. the memorized event is generated as soon as the blanking period or windowing period is completed */

/* dead time prescaler */
#define HRTIMER_DEADTIME_PRESCALER_MUL32                ((uint32_t)0x00000009U)                                          /*!< fHRTIMER_DTGCK = 32* fHRTIMER_CK */
#define HRTIMER_DEADTIME_PRESCALER_MUL16                ((uint32_t)0x00000008U)                                          /*!< fHRTIMER_DTGCK = 16* fHRTIMER_CK */
#define HRTIMER_DEADTIME_PRESCALER_MUL8                 ((uint32_t)0x00000000U)                                          /*!< fHRTIMER_DTGCK = 8*fHRTIMER_CK */
#define HRTIMER_DEADTIME_PRESCALER_MUL4                 ((uint32_t)0x00000001U)                                          /*!< fHRTIMER_DTGCK = (8*fHRTIMER_CK)/2 = 4*fHRTIMER_CK */
#define HRTIMER_DEADTIME_PRESCALER_MUL2                 ((uint32_t)0x00000002U)                                          /*!< fHRTIMER_DTGCK = (8*fHRTIMER_CK)/4 = 2*fHRTIMER_CK */
#define HRTIMER_DEADTIME_PRESCALER_DIV1                 ((uint32_t)0x00000003U)                                          /*!< fHRTIMER_DTGCK = (8*fHRTIMER_CK)/8 = fHRTIMER_CK*/
#define HRTIMER_DEADTIME_PRESCALER_DIV2                 ((uint32_t)0x00000004U)                                          /*!< fHRTIMER_DTGCK = (8*fHRTIMER_CK)/16 = fHRTIMER_CK / 2 */
#define HRTIMER_DEADTIME_PRESCALER_DIV4                 ((uint32_t)0x00000005U)                                          /*!< fHRTIMER_DTGCK = (8*fHRTIMER_CK)/32 = fHRTIMER_CK / 4 */
#define HRTIMER_DEADTIME_PRESCALER_DIV8                 ((uint32_t)0x00000006U)                                          /*!< fHRTIMER_DTGCK = (8*fHRTIMER_CK)/64 = fHRTIMER_CK / 8 */
#define HRTIMER_DEADTIME_PRESCALER_DIV16                ((uint32_t)0x00000007U)                                          /*!< fHRTIMER_DTGCK = (8*fHRTIMER_CK)/128 = fHRTIMER_CK / 16 */

/* dead time rising sign */
#define HRTIMER_DEADTIME_RISINGSIGN_POSITIVE            ((uint32_t)0x00000000U)                                          /*!< the sign of rising edge dead-time value is positive */
#define HRTIMER_DEADTIME_RISINGSIGN_NEGATIVE            (HRTIMER_STXDTCTL_DTRS)                                          /*!< the sign of rising edge dead-time value is negative */

/* dead time rising edge protection for value and sign */
#define HRTIMER_DEADTIME_RISING_PROTECT_DISABLE         ((uint32_t)0x00000000U)                                          /*!< protect disable. DTRS and DTRCFG[15:0] register are writable */
#define HRTIMER_DEADTIME_RISING_PROTECT_ENABLE          (HRTIMER_STXDTCTL_DTRSVPROT)                                     /*!< protect enable. DTRS and DTRCFG[15:0] are read-only */

/* dead time rising edge protection only for sign */
#define HRTIMER_DEADTIME_RISINGSIGN_PROTECT_DISABLE     ((uint32_t)0x00000000U)                                          /*!< protect disable. DTRS bit is writable */
#define HRTIMER_DEADTIME_RISINGSIGN_PROTECT_ENABLE      (HRTIMER_STXDTCTL_DTRSPROT)                                      /*!< protect enable. DTRS bit is read-only */

/* dead time falling sign */
#define HRTIMER_DEADTIME_FALLINGSIGN_POSITIVE           ((uint32_t)0x00000000U)                                          /*!< the sign of falling edge dead-time value is positive */
#define HRTIMER_DEADTIME_FALLINGSIGN_NEGATIVE           (HRTIMER_STXDTCTL_DTFS)                                          /*!< the sign of falling edge dead-time value is negative */

/* dead time falling edge protection for value and sign */
#define HRTIMER_DEADTIME_FALLING_PROTECT_DISABLE        ((uint32_t)0x00000000U)                                          /*!< protect disable. DTFS and DTFCFG[15:0] register are writable */
#define HRTIMER_DEADTIME_FALLING_PROTECT_ENABLE         (HRTIMER_STXDTCTL_DTFSVPROT)                                     /*!< protect enable. DTFS and DTFCFG[15:0] are read-only */

/* dead time falling edge protection only for sign */
#define HRTIMER_DEADTIME_FALLINGSIGN_PROTECT_DISABLE    ((uint32_t)0x00000000U)                                          /*!< protect disable. DTFS bit is writable */
#define HRTIMER_DEADTIME_FALLINGSIGN_PROTECT_ENABLE     (HRTIMER_STXDTCTL_DTFSPROT)                                      /*!< protect enable. DTFS bit is read-only */

/* the registers that can be written by DMA mode */
#define HRTIMER_DMAMODE_NONE                            ((uint32_t)0x00000000U)                                          /*!< no register is updated by DMA mode */
#define HRTIMER_DMAMODE_CTL0                            (HRTIMER_DMAUPSTXR_STXCTL0)                                      /*!< MTCTL0 or STxCTL0 register is updated by DMA mode */
#define HRTIMER_DMAMODE_INTC                            (HRTIMER_DMAUPSTXR_STXINTC)                                      /*!< MT or STx register is updated by DMA mode */
#define HRTIMER_DMAMODE_DMAINTEN                        (HRTIMER_DMAUPSTXR_STXDMAINTEN)                                  /*!< MTINTC or STxINTC register is updated by DMA mode */
#define HRTIMER_DMAMODE_CNT                             (HRTIMER_DMAUPSTXR_STXCNT)                                       /*!< MTCNT or STxCNT register is updated by DMA mode */
#define HRTIMER_DMAMODE_CAR                             (HRTIMER_DMAUPSTXR_STXCAR)                                       /*!< MTCAR or STxCAR register is updated by DMA mode */
#define HRTIMER_DMAMODE_CREP                            (HRTIMER_DMAUPSTXR_STXCREP)                                      /*!< MTCREP or STxCREP register is updated by DMA mode */
#define HRTIMER_DMAMODE_CMP0V                           (HRTIMER_DMAUPSTXR_STXCMP0V)                                     /*!< MTCMP0V or STxCMP0V register is updated by DMA mode */
#define HRTIMER_DMAMODE_CMP1V                           (HRTIMER_DMAUPSTXR_STXCMP1V)                                     /*!< MTCMP1V or STxCMP1V register is updated by DMA mode */
#define HRTIMER_DMAMODE_CMP2V                           (HRTIMER_DMAUPSTXR_STXCMP2V)                                     /*!< MTCMP2V or STxCMP2V register is updated by DMA mode */
#define HRTIMER_DMAMODE_CMP3V                           (HRTIMER_DMAUPSTXR_STXCMP3V)                                     /*!< MTCMP3V or STxCMP3V register is updated by DMA mode */
#define HRTIMER_DMAMODE_DTCTL                           (HRTIMER_DMAUPSTXR_STXDTCTL)                                     /*!< STxDTCTL register is updated by DMA mode */
#define HRTIMER_DMAMODE_CH0SET                          (HRTIMER_DMAUPSTXR_STXCH0SET)                                    /*!< STxCH0SET register is updated by DMA mode */
#define HRTIMER_DMAMODE_CH0RST                          (HRTIMER_DMAUPSTXR_STXCH0RST)                                    /*!< STxCH0RST register is updated by DMA mode */
#define HRTIMER_DMAMODE_CH1SET                          (HRTIMER_DMAUPSTXR_STXCH1SET)                                    /*!< STxCH1SET register is updated by DMA mode */
#define HRTIMER_DMAMODE_CH1RST                          (HRTIMER_DMAUPSTXR_STXCH1RST)                                    /*!< STxCH1RST register is updated by DMA mode */
#define HRTIMER_DMAMODE_EXEVFCFG0                       (HRTIMER_DMAUPSTXR_STXEXEVFCFG0)                                 /*!< STxEXEVFCFG0 register is updated by DMA mode */
#define HRTIMER_DMAMODE_EXEVFCFG1                       (HRTIMER_DMAUPSTXR_STXEXEVFCFG1)                                 /*!< STxEXEVFCFG1 register is updated by DMA mode */
#define HRTIMER_DMAMODE_CNTRST                          (HRTIMER_DMAUPSTXR_STXCNTRST)                                    /*!< STxCNTRST register is updated by DMA mode */
#define HRTIMER_DMAMODE_CSCTL                           (HRTIMER_DMAUPSTXR_STXCSCTL)                                     /*!< STxCSCTL register is updated by DMA mode */
#define HRTIMER_DMAMODE_CHOCTL                          (HRTIMER_DMAUPSTXR_STXCHOCTL)                                    /*!< STxCHOCTL register is updated by DMA mode */
#define HRTIMER_DMAMODE_FLTCTL                          (HRTIMER_DMAUPSTXR_STXFLTCTL)                                    /*!< STxFLTCTL register is updated by DMA mode */
#define HRTIMER_DMAMODE_CTL1                            (HRTIMER_DMAUPSTXR_STxCTL1)                                      /*!< STxCTL1 register is updated by DMA mode */
#define HRTIMER_DMAMODE_EXEVFCFG2                       (HRTIMER_DMAUPSTXR_STXEXEVFCFG2)                                 /*!< STxEXEVFCFG2 register is updated by DMA mode */
#define HRTIMER_DMAMODE_ACTL                            (HRTIMER_DMAUPSTXR_STXACTL)                                      /*!< STxACTL register is updated by DMA mode */

/* the synchronization input source */
#define HRTIMER_SYNCINPUTSOURCE_DISABLE                 ((uint32_t)0x00000000U)                                          /*!< synchronization input disable */
#define HRTIMER_SYNCINPUTSOURCE_INTERNAL                ((uint32_t)0x00000200U)                                          /*!< internal signal: TIMER0_TRGO in the advanced timer TIMER0 */
#define HRTIMER_SYNCINPUTSOURCE_EXTERNAL                ((uint32_t)0x00000300U)                                          /*!< external signal: a positive pulse on the HRTIMER_SCIN pin triggers the Master_TIMER */

/* the synchronization output source */
#define HRTIMER_SYNCOUTPUTSOURCE_MTSTART                ((uint32_t)0x00000000U)                                          /*!< Master_TIMER start event to be sent to the synchronization output pad HRTIMER_SCOUT */
#define HRTIMER_SYNCOUTPUTSOURCE_MTCMP0                 ((uint32_t)0x00004000U)                                          /*!< Master_TIMER compare 0 event to be sent to the synchronization output pad HRTIMER_SCOUT*/
#define HRTIMER_SYNCOUTPUTSOURCE_ST0START               ((uint32_t)0x00008000U)                                          /*!< Slave_TIMER0 reset and start event to be sent to the synchronization output pad HRTIMER_SCOUT */
#define HRTIMER_SYNCOUTPUTSOURCE_ST0CMP0                ((uint32_t)0x0000C000U)                                          /*!< Slave_TIMER0 compare 0 event to be sent to the synchronization output pad HRTIMER_SCOUT */

/* the pulse on the synchronization output pad HRTIMER_SCOUT */
#define HRTIMER_SYNCOUTPUTPOLARITY_DISABLE              ((uint32_t)0x00000000U)                                          /*!< pulse generated disable. No pulse on HRTIMER_SCOUT */
#define HRTIMER_SYNCOUTPUTPOLARITY_POSITIVE             ((uint32_t)0x00002000U)                                          /*!< positive pulse generated on the HRTIMER_SCOUT. the length of it is 16 tHRTIMER_CK cycles */
#define HRTIMER_SYNCOUTPUTPOLARITY_NEGATIVE             ((uint32_t)0x00003000U)                                          /*!< negative pulse generated on the HRTIMER_SCOUT. the length of it is 16 tHRTIMER_CK cycles */

/* continuous mode in bunch mode */
#define HRTIMER_BUNCHMODE_SINGLE                        ((uint32_t)0x00000000U)                                          /*!< single pulse mode. the BM-counter stops by hardware when it reaches the HRTIMER_BMCAR value */
#define HRTIMER_BUNCHMODE_CONTINOUS                     (HRTIMER_BMCTL_BMCTN)                                            /*!< continuous mode. the BM-counter rolls over to zero and counts continuously when it reaches the HRTIMER_BMCAR value */

/* bunch mode clock source */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_MASTER            ((uint32_t)0x00000000U)                                          /*!< the clock source for the bunch mode counter: Master_TIMER counter reset/roll-over event */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_ST0               ((uint32_t)0x00000004U)                                          /*!< the clock source for the bunch mode counter: Slave_TIMER0 counter reset/roll-over event */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_ST1               ((uint32_t)0x00000008U)                                          /*!< the clock source for the bunch mode counter: Slave_TIMER1 counter reset/roll-over event */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_ST2               ((uint32_t)0x0000000CU)                                          /*!< the clock source for the bunch mode counter: Slave_TIMER2 counter reset/roll-over event */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_ST3               ((uint32_t)0x00000010U)                                          /*!< the clock source for the bunch mode counter: Slave_TIMER3 counter reset/roll-over event */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_ST4               ((uint32_t)0x00000014U)                                          /*!< the clock source for the bunch mode counter: Slave_TIMER4 counter reset/roll-over event */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_TIMER15_CH0_O     ((uint32_t)0x00000018U)                                          /*!< the clock source for the bunch mode counter: chip internal signal BMCLK0  */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_TIMER16_CH0_O     ((uint32_t)0x0000001CU)                                          /*!< the clock source for the bunch mode counter: chip internal signal BMCLK1 */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_TIMER6_TRGO       ((uint32_t)0x00000020U)                                          /*!< the clock source for the bunch mode counter: chip internal signal BMCLK2 */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_RESERVED          ((uint32_t)0x00000024U)                                          /*!< the clock source for the bunch mode counter: chip internal signal BMCLK3 */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_HRTIMERCK        ((uint32_t)0x00000028U)                                           /*!< the clock source for the bunch mode counter: prescaled fHRTIMER_CK clock */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_ST5               ((uint32_t)0x0000002CU)                                          /*!< the clock source for the bunch mode counter: Slave_TIMER5 counter reset/roll-over event */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_ST6               ((uint32_t)0x00000030U)                                          /*!< the clock source for the bunch mode counter: Slave_TIMER6 counter reset/roll-over event */
#define HRTIMER_BUNCHMODE_CLOCKSOURCE_ST7               ((uint32_t)0x00000034U)                                          /*!< the clock source for the bunch mode counter: Slave_TIMER7 counter reset/roll-over event */

/* bunch mode clock division */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV1                ((uint32_t)0x00000000U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV2                ((uint32_t)0x00000040U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/2 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV4                ((uint32_t)0x00000080U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/4 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV8                ((uint32_t)0x000000C0U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/8 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV16               ((uint32_t)0x00000100U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/16 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV32               ((uint32_t)0x00000140U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/32 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV64               ((uint32_t)0x00000180U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/64 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV128              ((uint32_t)0x000001C0U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/128 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV256              ((uint32_t)0x00000200U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/256 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV512              ((uint32_t)0x00000240U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/512 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV1024             ((uint32_t)0x00000280U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/1024 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV2048             ((uint32_t)0x000002C0U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/2048*/
#define HRTIMER_BUNCHMODE_PRESCALER_DIV4096             ((uint32_t)0x00000300U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/4096 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV8192             ((uint32_t)0x00000340U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/8192 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV16384            ((uint32_t)0x00000380U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/16384 */
#define HRTIMER_BUNCHMODE_PRESCALER_DIV32768            ((uint32_t)0x000003C0U)                                          /*!< fHRTIMER_BMCNTCK = fHRTIMER_CK/32768 */

/* bunch mode shadow enable */
#define HRTIMER_BUNCHMODEPRELOAD_DISABLED               ((uint32_t)0x00000000U)                                          /*!< the shadow registers for HRTIMER_BMCMPV and HRTIMER_BMCAR registers are disabled */
#define HRTIMER_BUNCHMODEPRELOAD_ENABLED                (HRTIMER_BMCTL_BMSE)                                             /*!< the shadow registers for HRTIMER_BMCMPV and HRTIMER_BMCAR registers are enabled */

/* the event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_NONE                  ((uint32_t)0x00000000U)                                          /*!< clear all triggers */
#define HRTIMER_BUNCHMODE_TRIGGER_MTRESET               (HRTIMER_BMSTRG_MTRST)                                           /*!< Master_TIMER reset event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_MTREPETITION          (HRTIMER_BMSTRG_MTREP)                                           /*!< Master_TIMER repetition event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_MTCMP0                (HRTIMER_BMSTRG_MTCMP0)                                          /*!< Master_TIMER compare 0 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_MTCMP1                (HRTIMER_BMSTRG_MTCMP1)                                          /*!< Master_TIMER compare 1 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_MTCMP2                (HRTIMER_BMSTRG_MTCMP2)                                          /*!< Master_TIMER compare 2 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_MTCMP3                (HRTIMER_BMSTRG_MTCMP3)                                          /*!< Master_TIMER compare 3 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST0RESET              (HRTIMER_BMSTRG_ST0RST)                                          /*!< Slave_TIMER0 reset event triggers bunch mode operation  */
#define HRTIMER_BUNCHMODE_TRIGGER_ST0REPETITION         (HRTIMER_BMSTRG_ST0REP)                                          /*!< Slave_TIMER0 repetition event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST0CMP0               (HRTIMER_BMSTRG_ST0CMP0)                                         /*!< Slave_TIMER0 compare 0 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST0CMP1               (HRTIMER_BMSTRG_ST0CMP1)                                         /*!< Slave_TIMER0 compare 1 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST1RESET              (HRTIMER_BMSTRG_ST1RST)                                          /*!< Slave_TIMER1 reset event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST1REPETITION         (HRTIMER_BMSTRG_ST1REP)                                          /*!< Slave_TIMER1 repetition event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST1CMP0               (HRTIMER_BMSTRG_ST1CMP0)                                         /*!< Slave_TIMER1 compare 0 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST1CMP1               (HRTIMER_BMSTRG_ST1CMP1)                                         /*!< Slave_TIMER1 compare 1 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST2RESET              (HRTIMER_BMSTRG_ST2RST)                                          /*!< Slave_TIMER2 reset event triggers bunch mode operation  */
#define HRTIMER_BUNCHMODE_TRIGGER_ST2REPETITION         (HRTIMER_BMSTRG_ST2REP)                                          /*!< Slave_TIMER2 repetition event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST2CMP0               (HRTIMER_BMSTRG_ST2CMP0)                                         /*!< Slave_TIMER2 compare 0 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST2CMP1               (HRTIMER_BMSTRG_ST2CMP1)                                         /*!< Slave_TIMER2 compare 1 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST3RESET              (HRTIMER_BMSTRG_ST3RST)                                          /*!< Slave_TIMER3 reset event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST3REPETITION         (HRTIMER_BMSTRG_ST3REP)                                          /*!< Slave_TIMER3 repetition event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST3CMP0               (HRTIMER_BMSTRG_ST3CMP0)                                         /*!< Slave_TIMER3 compare 0 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST3CMP1               (HRTIMER_BMSTRG_ST3CMP1)                                         /*!< Slave_TIMER3 compare 1 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST4RESET              (HRTIMER_BMSTRG_ST4RST)                                          /*!< Slave_TIMER4 reset event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST4REPETITION         (HRTIMER_BMSTRG_ST4REP)                                          /*!< Slave_TIMER4 repetition event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST4CMP0               (HRTIMER_BMSTRG_ST4CMP0)                                         /*!< Slave_TIMER4 compare 0 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST4CMP1               (HRTIMER_BMSTRG_ST4CMP1)                                         /*!< Slave_TIMER4 compare 1 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST0EVENT6             (HRTIMER_BMSTRG_ST0EXEV6)                                        /*!< Slave_TIMER0 period event following external event 6 triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST3EVENT7             (HRTIMER_BMSTRG_ST3EXEV7)                                        /*!< Slave_TIMER3 period event following external event 7 triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_EVENT6                (HRTIMER_BMSTRG_EXEV6)                                           /*!< external event 6 triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_EVENT7                (HRTIMER_BMSTRG_EXEV7)                                           /*!< external event 7 triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_CHIP                  (HRTIMER_BMSTRG_CISGN)                                           /*!< chip internal signal triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST5RESET              (HRTIMER_BMSTRGA_ST5RST)                                         /*!< Slave_TIMER5 reset event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST5REPETITION         (HRTIMER_BMSTRGA_ST5REP)                                         /*!< Slave_TIMER5 repetition event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST5CMP0               (HRTIMER_BMSTRGA_ST5CMP0)                                        /*!< Slave_TIMER5 compare 0 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST5CMP1               (HRTIMER_BMSTRGA_ST5CMP1)                                        /*!< Slave_TIMER5 compare 1 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST6RESET              (HRTIMER_BMSTRGA_ST6RST)                                         /*!< Slave_TIMER6 reset event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST6REPETITION         (HRTIMER_BMSTRGA_ST6REP)                                         /*!< Slave_TIMER6 repetition event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST6CMP0               (HRTIMER_BMSTRGA_ST6CMP0)                                        /*!< Slave_TIMER6 compare 0 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST6CMP1               (HRTIMER_BMSTRGA_ST6CMP1)                                        /*!< Slave_TIMER6 compare 1 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST7RESET              (HRTIMER_BMSTRGA_ST7RST)                                         /*!< Slave_TIMER7 reset event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST7REPETITION         (HRTIMER_BMSTRGA_ST7REP)                                         /*!< Slave_TIMER7 repetition event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST7CMP0               (HRTIMER_BMSTRGA_ST7CMP0)                                        /*!< Slave_TIMER7 compare 0 event triggers bunch mode operation */
#define HRTIMER_BUNCHMODE_TRIGGER_ST7CMP1               (HRTIMER_BMSTRGA_ST7CMP1)                                        /*!< Slave_TIMER7 compare 1 event triggers bunch mode operation */

/* external event source */
#define HRTIMER_EXEV_SRC0                               ((uint32_t)0x00000000U)                                          /*!< external event y source is EXEVySRC 0 */
#define HRTIMER_EXEV_SRC1                               ((uint32_t)0x00000001U)                                          /*!< external event y source is EXEVySRC 1 */
#define HRTIMER_EXEV_SRC2                               ((uint32_t)0x00000002U)                                          /*!< external event y source is EXEVySRC 2 */
#define HRTIMER_EXEV_SRC3                               ((uint32_t)0x00000003U)                                          /*!< external event y source is EXEVySRC 3 */

/* external event polarity */
#define HRTIMER_EXEV_POLARITY_HIGH                      ((uint32_t)0x00000000U)                                          /*!< external event y active at high level */
#define HRTIMER_EXEV_POLARITY_LOW                       (HRTIMER_EXEVCFG0_EXEV0P)                                       /*!< external event y active at low level */

/* external event edge sensitivity */
#define HRTIMER_EXEV_EDGE_LEVEL                         ((uint32_t)0x00000000U)                                          /*!< level active. active level is defined by EXEVyP bit */
#define HRTIMER_EXEV_EDGE_RISING                        ((uint32_t)0x00000008U)                                          /*!< rising edge active */
#define HRTIMER_EXEV_EDGE_FALLING                       ((uint32_t)0x00000010U)                                          /*!< falling edge active */
#define HRTIMER_EXEV_EDGE_BOTH                          ((uint32_t)0x00000018U)                                          /*!< both edges active */

/* external event fast mode */
#define HRTIMER_EXEV_FAST_DISABLE                      ((uint32_t)0x00000000U)                                           /*!< external event fast mode disable */
#define HRTIMER_EXEV_FAST_ENABLE                       (HRTIMER_EXEVCFG0_EXEV0FAST)                                      /*!< external event fast mode enable */

/* external event digital filter clock division */
#define HRTIMER_EXEV_PRESCALER_DIV1                     ((uint32_t)0x00000000U)                                          /*!< fHRTIMER_EXEVFCK = fHRTIMER_CK */
#define HRTIMER_EXEV_PRESCALER_DIV2                     ((uint32_t)0x40000000U)                                          /*!< fHRTIMER_EXEVFCK = fHRTIMER_CK / 2 */
#define HRTIMER_EXEV_PRESCALER_DIV4                     ((uint32_t)0x80000000U)                                          /*!< fHRTIMER_EXEVFCK = fHRTIMER_CK / 4 */
#define HRTIMER_EXEV_PRESCALER_DIV8                     ((uint32_t)0xC0000000U)                                          /*!< fHRTIMER_EXEVFCK = fHRTIMER_CK / 8 */

/* external event X reset mode */
#define HRTIMER_EXEVX_RESET_MODE0                       ((uint32_t)0x00000000U)                                          /*!< the external event counter X is reset on every reset/roll-over event */
#define HRTIMER_EXEVX_RESET_MODE1                       (HRTIMER_STXEXEVFCFG2_EXTEXRSTM)                                /*!< the external event counter X is reset on every reset/roll-over event only if no event occurs during the last counting period */

/* external event X selection */
#define HRTIMER_EXEVX_SOURCE_EXEV0                      ((uint32_t)0x00000000U)                                          /*!< external event 0 serves as the source for external event X */
#define HRTIMER_EXEVX_SOURCE_EXEV1                      ((uint32_t)0x00000010U)                                          /*!< external event 1 serves as the source for external event X */
#define HRTIMER_EXEVX_SOURCE_EXEV2                      ((uint32_t)0x00000020U)                                          /*!< external event 2 serves as the source for external event X */
#define HRTIMER_EXEVX_SOURCE_EXEV3                      ((uint32_t)0x00000030U)                                          /*!< external event 3 serves as the source for external event X */
#define HRTIMER_EXEVX_SOURCE_EXEV4                      ((uint32_t)0x00000040U)                                          /*!< external event 4 serves as the source for external event X */
#define HRTIMER_EXEVX_SOURCE_EXEV5                      ((uint32_t)0x00000050U)                                          /*!< external event 5 serves as the source for external event X */
#define HRTIMER_EXEVX_SOURCE_EXEV6                      ((uint32_t)0x00000060U)                                          /*!< external event 6 serves as the source for external event X */
#define HRTIMER_EXEVX_SOURCE_EXEV7                      ((uint32_t)0x00000070U)                                          /*!< external event 7 serves as the source for external event X */
#define HRTIMER_EXEVX_SOURCE_EXEV8                      ((uint32_t)0x00000080U)                                          /*!< external event 8 serves as the source for external event X */
#define HRTIMER_EXEVX_SOURCE_EXEV9                      ((uint32_t)0x00000090U)                                          /*!< external event 9 serves as the source for external event X */

/* immediately update compare 0 value PWM mode */
#define HRTIMER_IMMEDIATELY_UPDATE_CMP0_DISABLE         ((uint32_t)0x00000000U)                                          /*!< immediately update compare 0 value PWM mode disable */
#define HRTIMER_IMMEDIATELY_UPDATE_CMP0_ENABLE          (HRTIMER_STXCTL1_IMUPD0V)                                        /*!< immediately update compare 0 value PWM mode enable */

/* immediately update compare 2 value PWM mode */
#define HRTIMER_IMMEDIATELY_UPDATE_CMP2_DISABLE         ((uint32_t)0x00000000U)                                          /*!< immediately update compare 2 value PWM mode disable */
#define HRTIMER_IMMEDIATELY_UPDATE_CMP2_ENABLE          (HRTIMER_STXCTL1_IMUPD2V)                                        /*!< immediately update compare 2 value PWM mode enable */

/* triggered half mode */
#define HRTIMER_TRGHALFM_DISABLE                        ((uint32_t)0x00000000U)                                          /*!< triggered half mode disable */
#define HRTIMER_TRGHALFM_ENABLE                         ((uint32_t)HRTIMER_STXCTL1_TRGHALFM)                             /*!< triggered half mode enable */

/* fault input source */
#define HRTIMER_FAULT_SOURCE_PIN                        ((uint32_t)0x00000000U)                                          /*!< the source of fault input is chip external pin */
#define HRTIMER_FAULT_SOURCE_INTERNAL                   ((uint32_t)0x00000001U)                                          /*!< the source of fault input is chip internal signal(for example comparator) */
#define HRTIMER_FAULT_SOURCE_EXT_EVENT                  ((uint32_t)0x00000002U)                                          /*!< the source of fault input is external event */

/* fault input polarity */
#define HRTIMER_FAULT_POLARITY_LOW                      ((uint32_t)0x00000000U)                                          /*!< fault input active at low level */
#define HRTIMER_FAULT_POLARITY_HIGH                     (HRTIMER_FLTINCFG0_FLT0INP)                                      /*!< fault input active at high  level */

/* enable or disable fault */
#define HRTIMER_FAULT_CHANNEL_DISABLE                   ((uint32_t)0x00000000U)                                          /*!< fault channel disable */
#define HRTIMER_FAULT_CHANNEL_ENABLE                    (HRTIMER_FLTINCFG0_FLT0INEN)                                     /*!< fault channel enable */

/* protect fault input configuration */
#define HRTIMER_FAULT_PROTECT_DISABLE                   ((uint32_t)0x00000000U)                                          /*!< protect disable. FLT0INEN, FLT0INP, FLT0INSRC and FLT0INFC[3:0] is writable */
#define HRTIMER_FAULT_PROTECT_ENABLE                    (HRTIMER_FLTINCFG0_FLT0INPROT)                                   /*!< protect enable. FLT0INEN, FLT0INP, FLT0INSRC and FLT0INFC[3:0] is read-only */

/* fault input digital filter clock division */
#define HRTIMER_FAULT_PRESCALER_DIV1                    ((uint32_t)0x00000000U)                                          /*!< fHRTIMER_FLTFCK = fHRTIMER_CK */
#define HRTIMER_FAULT_PRESCALER_DIV2                    ((uint32_t)0x01000000U)                                          /*!< fHRTIMER_FLTFCK = fHRTIMER_CK/2 */
#define HRTIMER_FAULT_PRESCALER_DIV4                    ((uint32_t)0x02000000U)                                          /*!< fHRTIMER_FLTFCK = fHRTIMER_CK/4 */
#define HRTIMER_FAULT_PRESCALER_DIV8                    ((uint32_t)0x03000000U)                                          /*!< fHRTIMER_FLTFCK = fHRTIMER_CK/8 */

/* fault blanking source */
#define HRTIMER_FAULT_BLKEN_DISABLE                     ((uint32_t)0x00000000U)                                          /*!< fault blank disable */
#define HRTIMER_FAULT_BLKEN_ENABLE                      (HRTIMER_FLTINCFG2_FLT0BLKEN)                                    /*!< fault blank enable */

/* fault blanking source */
#define HRTIMER_FAULT_RST_COMP                          ((uint32_t)0x00000000U)                                          /*!< fault reset and compare windows */
#define HRTIMER_FAULT_COMP_COMP                         (HRTIMER_FLTINCFG2_FLT0BLKS)                                     /*!< fault compare and compare windows */

/* fault reset mode */
#define HRTIMER_FAULT_COUNTER_RESET_UNCONDITIONAL       ((uint32_t)0x00000000U)                                          /*!< reset the fault counter on each reset/update event */
#define HRTIMER_FAULT_COUNTER_RESET_CONDITIONAL         (HRTIMER_FLTINCFG2_FLT0RST)                                      /*!< reset the Fault counter on each reset/ update event only if no fault occurred during the last counting period */

/* HRTIMER_ADCTRIG update source */
#define HRTIMER_ADCTRGI_UPDATE_MT                       ((uint32_t)0x00000000U)                                          /*!< Master_TIMER update event */
#define HRTIMER_ADCTRGI_UPDATE_ST0                      ((uint32_t)0x00000001U)                                          /*!< Slaver_TIMER0 update event */
#define HRTIMER_ADCTRGI_UPDATE_ST1                      ((uint32_t)0x00000002U)                                          /*!< Slaver_TIMER1 update event */
#define HRTIMER_ADCTRGI_UPDATE_ST2                      ((uint32_t)0x00000003U)                                          /*!< Slaver_TIMER2 update event */
#define HRTIMER_ADCTRGI_UPDATE_ST3                      ((uint32_t)0x00000004U)                                          /*!< Slaver_TIMER3 update event */
#define HRTIMER_ADCTRGI_UPDATE_ST4                      ((uint32_t)0x00000005U)                                          /*!< Slaver_TIMER4 update event */
#define HRTIMER_ADCTRGI_UPDATE_ST5                      ((uint32_t)0x00000006U)                                          /*!< Slaver_TIMER5 update event */
#define HRTIMER_ADCTRGI_UPDATE_ST6                      ((uint32_t)0x00000007U)                                          /*!< Slaver_TIMER6 update event */
#define HRTIMER_ADCTRGI_UPDATE_ST7                      ((uint32_t)0x00000008U)                                          /*!< Slaver_TIMER7 update event */

/*  ADC trigger event */
/* ADC trigger 0,2 */
#define HRTIMER_ADCTRGI02_EVENT_NONE                    ((uint32_t)0x00000000U)                                          /*!< no ADC trigger event */
#define HRTIMER_ADCTRGI02_EVENT_MTCMP0                  (HRTIMER_ADCTRIGS0_TRG0MTC0)                                    /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Master_TIMER compare 0 */
#define HRTIMER_ADCTRGI02_EVENT_MTCMP1                  (HRTIMER_ADCTRIGS0_TRG0MTC1)                                    /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Master_TIMER compare 1 */ 
#define HRTIMER_ADCTRGI02_EVENT_MTCMP2                  (HRTIMER_ADCTRIGS0_TRG0MTC2)                                    /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Master_TIMER compare 2 */
#define HRTIMER_ADCTRGI02_EVENT_MTCMP3                  (HRTIMER_ADCTRIGS0_TRG0MTC3)                                    /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Master_TIMER compare 3 */
#define HRTIMER_ADCTRGI02_EVENT_MTPER                   (HRTIMER_ADCTRIGS0_TRG0MTPER)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Master_TIMER period */
#define HRTIMER_ADCTRGI02_EVENT_EXEV0                   (HRTIMER_ADCTRIGS0_TRG0EXEV0)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on external event 0 */
#define HRTIMER_ADCTRGI02_EVENT_EXEV1                   (HRTIMER_ADCTRIGS0_TRG0EXEV1)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on external event 1 */
#define HRTIMER_ADCTRGI02_EVENT_EXEV2                   (HRTIMER_ADCTRIGS0_TRG0EXEV2)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on external event 2 */
#define HRTIMER_ADCTRGI02_EVENT_EXEV3                   (HRTIMER_ADCTRIGS0_TRG0EXEV3)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on external event 3 */ 
#define HRTIMER_ADCTRGI02_EVENT_EXEV4                   (HRTIMER_ADCTRIGS0_TRG0EXEV4)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on external event 4 */
#define HRTIMER_ADCTRGI02_EVENT_ST0CMP1                 (HRTIMER_ADCTRIGS0_TRG0ST0C1)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER0 compare 1 */
#define HRTIMER_ADCTRGI02_EVENT_ST0CMP2                 (HRTIMER_ADCTRIGS0_TRG0ST0C2)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER0 compare 2 */
#define HRTIMER_ADCTRGI02_EVENT_ST0CMP3                 (HRTIMER_ADCTRIGS0_TRG0ST0C3)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER0 compare 3 */
#define HRTIMER_ADCTRGI02_EVENT_ST0PER                  (HRTIMER_ADCTRIGS0_TRG0ST0PER)                                  /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER0 period */
#define HRTIMER_ADCTRGI02_EVENT_ST0RST                  (HRTIMER_ADCTRIGS0_TRG0ST0RST)                                  /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER0 reset and counter roll-over event */
#define HRTIMER_ADCTRGI02_EVENT_ST1CMP1                 (HRTIMER_ADCTRIGS0_TRG0ST1C1)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER1 compare 1 */
#define HRTIMER_ADCTRGI02_EVENT_ST1CMP2                 (HRTIMER_ADCTRIGS0_TRG0ST1C2)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER1 compare 2 */
#define HRTIMER_ADCTRGI02_EVENT_ST1CMP3                 (HRTIMER_ADCTRIGS0_TRG0ST1C3)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER1 compare 3 */
#define HRTIMER_ADCTRGI02_EVENT_ST1PER                  (HRTIMER_ADCTRIGS0_TRG0ST1PER)                                  /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER1 period */
#define HRTIMER_ADCTRGI02_EVENT_ST1RST                  (HRTIMER_ADCTRIGS0_TRG0ST1RST)                                  /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER1 reset and counter roll-over event */
#define HRTIMER_ADCTRGI02_EVENT_ST2CMP1                 (HRTIMER_ADCTRIGS0_TRG0ST2C1)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER2 compare 1 */
#define HRTIMER_ADCTRGI02_EVENT_ST2CMP2                 (HRTIMER_ADCTRIGS0_TRG0ST2C2)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER2 compare 2 */
#define HRTIMER_ADCTRGI02_EVENT_ST2CMP3                 (HRTIMER_ADCTRIGS0_TRG0ST2C3)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER2 compare 3 */
#define HRTIMER_ADCTRGI02_EVENT_ST2PER                  (HRTIMER_ADCTRIGS0_TRG0ST2PER)                                  /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER2 period */
#define HRTIMER_ADCTRGI02_EVENT_ST3CMP1                 (HRTIMER_ADCTRIGS0_TRG0ST3C1)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER3 compare 1 */
#define HRTIMER_ADCTRGI02_EVENT_ST3CMP2                 (HRTIMER_ADCTRIGS0_TRG0ST3C2)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER3 compare 2 */
#define HRTIMER_ADCTRGI02_EVENT_ST3CMP3                 (HRTIMER_ADCTRIGS0_TRG0ST3C3)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER3 compare 3 */
#define HRTIMER_ADCTRGI02_EVENT_ST3PER                  (HRTIMER_ADCTRIGS0_TRG0ST3PER)                                  /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER3 period */
#define HRTIMER_ADCTRGI02_EVENT_ST4CMP1                 (HRTIMER_ADCTRIGS0_TRG0ST4C1)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER4 compare 1 */
#define HRTIMER_ADCTRGI02_EVENT_ST4CMP2                 (HRTIMER_ADCTRIGS0_TRG0ST4C2)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER4 compare 2 */
#define HRTIMER_ADCTRGI02_EVENT_ST4CMP3                 (HRTIMER_ADCTRIGS0_TRG0ST4C3)                                   /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER4 compare 3 */
#define HRTIMER_ADCTRGI02_EVENT_ST4PER                  (HRTIMER_ADCTRIGS0_TRG0ST4PER)                                  /*!< HRTIMER_ADCTRIG0 or HRTIMER_ADCTRIG2 on Slave_TIMER4 period */
#define HRTIMER_ADCTRGI02_EVENT_ST5CMP1                 (HRTIMER_ADCTRIGS0A_TRG0ST5C1)                                  /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER5 compare 1 */
#define HRTIMER_ADCTRGI02_EVENT_ST5CMP2                 (HRTIMER_ADCTRIGS0A_TRG0ST5C2)                                  /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER5 compare 2 */
#define HRTIMER_ADCTRGI02_EVENT_ST5CMP3                 (HRTIMER_ADCTRIGS0A_TRG0ST5C3)                                  /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER5 compare 3 */
#define HRTIMER_ADCTRGI02_EVENT_ST5PER                  (HRTIMER_ADCTRIGS0A_TRG0ST5PER)                                 /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER5 period */
#define HRTIMER_ADCTRGI02_EVENT_ST5RST                  (HRTIMER_ADCTRIGS0A_TRG0ST5RST)                                 /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER5 reset and counter roll-over event */
#define HRTIMER_ADCTRGI02_EVENT_ST6CMP1                 (HRTIMER_ADCTRIGS0A_TRG0ST6C1)                                  /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER6 compare 1 */
#define HRTIMER_ADCTRGI02_EVENT_ST6CMP2                 (HRTIMER_ADCTRIGS0A_TRG0ST6C2)                                  /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER6 compare 2 */
#define HRTIMER_ADCTRGI02_EVENT_ST6CMP3                 (HRTIMER_ADCTRIGS0A_TRG0ST6C3)                                  /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER6 compare 3 */
#define HRTIMER_ADCTRGI02_EVENT_ST6PER                  (HRTIMER_ADCTRIGS0A_TRG0ST6PER)                                 /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER6 period */
#define HRTIMER_ADCTRGI02_EVENT_ST6RST                  (HRTIMER_ADCTRIGS0A_TRG0ST6RST)                                 /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER6 reset and counter roll-over event */
#define HRTIMER_ADCTRGI02_EVENT_ST7CMP1                 (HRTIMER_ADCTRIGS0A_TRG0ST7C1)                                  /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER7 compare 1 */
#define HRTIMER_ADCTRGI02_EVENT_ST7CMP2                 (HRTIMER_ADCTRIGS0A_TRG0ST7C2)                                  /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER7 compare 2 */
#define HRTIMER_ADCTRGI02_EVENT_ST7CMP3                 (HRTIMER_ADCTRIGS0A_TRG0ST7C3)                                  /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER7 compare 3 */
#define HRTIMER_ADCTRGI02_EVENT_ST7PER                  (HRTIMER_ADCTRIGS0A_TRG0ST7PER)                                 /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER7 period */
#define HRTIMER_ADCTRGI02_EVENT_ST7RST                  (HRTIMER_ADCTRIGS0A_TRG0ST7RST)                                 /*!< HRTIMER_ADCTRIG0A or HRTIMER_ADCTRIG2A on Slave_TIMER7 reset and counter roll-over event */

/* ADC trigger 1,3 */
#define HRTIMER_ADCTRGI13_EVENT_NONE                    ((uint32_t)0x00000000U)                                          /*!< no ADC trigger event */
#define HRTIMER_ADCTRGI13_EVENT_MTCMP0                  (HRTIMER_ADCTRIGS1_TRG1MTC0)                                    /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Master_TIMER compare 0 */
#define HRTIMER_ADCTRGI13_EVENT_MTCMP1                  (HRTIMER_ADCTRIGS1_TRG1MTC1)                                    /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Master_TIMER compare 1 */ 
#define HRTIMER_ADCTRGI13_EVENT_MTCMP2                  (HRTIMER_ADCTRIGS1_TRG1MTC2)                                    /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Master_TIMER compare 2 */
#define HRTIMER_ADCTRGI13_EVENT_MTCMP3                  (HRTIMER_ADCTRIGS1_TRG1MTC3)                                    /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Master_TIMER compare 3 */
#define HRTIMER_ADCTRGI13_EVENT_MTPER                   (HRTIMER_ADCTRIGS1_TRG1MTPER)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Master_TIMER period */
#define HRTIMER_ADCTRGI13_EVENT_EXEV5                   (HRTIMER_ADCTRIGS1_TRG1EXEV5)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on external event 5 */
#define HRTIMER_ADCTRGI13_EVENT_EXEV6                   (HRTIMER_ADCTRIGS1_TRG1EXEV6)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on external event 6 */
#define HRTIMER_ADCTRGI13_EVENT_EXEV7                   (HRTIMER_ADCTRIGS1_TRG1EXEV7)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on external event 7 */
#define HRTIMER_ADCTRGI13_EVENT_EXEV8                   (HRTIMER_ADCTRIGS1_TRG1EXEV8)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on external event 8 */ 
#define HRTIMER_ADCTRGI13_EVENT_EXEV9                   (HRTIMER_ADCTRIGS1_TRG1EXEV9)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on external event 9 */
#define HRTIMER_ADCTRGI13_EVENT_ST0CMP1                 (HRTIMER_ADCTRIGS1_TRG1ST0C1)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER0 compare 1 */
#define HRTIMER_ADCTRGI13_EVENT_ST0CMP2                 (HRTIMER_ADCTRIGS1_TRG1ST0C2)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER0 compare 2 */
#define HRTIMER_ADCTRGI13_EVENT_ST0CMP3                 (HRTIMER_ADCTRIGS1_TRG1ST0C3)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER0 compare 3 */
#define HRTIMER_ADCTRGI13_EVENT_ST0PER                  (HRTIMER_ADCTRIGS1_TRG1ST0PER)                                  /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER0 period */
#define HRTIMER_ADCTRGI13_EVENT_ST1CMP1                 (HRTIMER_ADCTRIGS1_TRG1ST1C1)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER1 compare 1 */
#define HRTIMER_ADCTRGI13_EVENT_ST1CMP2                 (HRTIMER_ADCTRIGS1_TRG1ST1C2)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER1 compare 2 */
#define HRTIMER_ADCTRGI13_EVENT_ST1CMP3                 (HRTIMER_ADCTRIGS1_TRG1ST1C3)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER1 compare 3 */
#define HRTIMER_ADCTRGI13_EVENT_ST1PER                  (HRTIMER_ADCTRIGS1_TRG1ST1PER)                                  /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER1 period */
#define HRTIMER_ADCTRGI13_EVENT_ST2CMP1                 (HRTIMER_ADCTRIGS1_TRG1ST2C1)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER2 compare 1 */
#define HRTIMER_ADCTRGI13_EVENT_ST2CMP2                 (HRTIMER_ADCTRIGS1_TRG1ST2C2)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER2 compare 2 */
#define HRTIMER_ADCTRGI13_EVENT_ST2CMP3                 (HRTIMER_ADCTRIGS1_TRG1ST2C3)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER2 compare 3 */
#define HRTIMER_ADCTRGI13_EVENT_ST2PER                  (HRTIMER_ADCTRIGS1_TRG1ST2PER)                                  /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER2 period */
#define HRTIMER_ADCTRGI13_EVENT_ST2RST                  (HRTIMER_ADCTRIGS1_TRG1ST2RST)                                  /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER2 reset and counter roll-over event */
#define HRTIMER_ADCTRGI13_EVENT_ST3CMP1                 (HRTIMER_ADCTRIGS1_TRG1ST3C1)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER3 compare 1 */
#define HRTIMER_ADCTRGI13_EVENT_ST3CMP2                 (HRTIMER_ADCTRIGS1_TRG1ST3C2)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER3 compare 2 */
#define HRTIMER_ADCTRGI13_EVENT_ST3CMP3                 (HRTIMER_ADCTRIGS1_TRG1ST3C3)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER3 compare 3 */
#define HRTIMER_ADCTRGI13_EVENT_ST3PER                  (HRTIMER_ADCTRIGS1_TRG1ST3PER)                                  /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER3 period */
#define HRTIMER_ADCTRGI13_EVENT_ST3RST                  (HRTIMER_ADCTRIGS1_TRG1ST3RST)                                  /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER3 reset and counter roll-over event */
#define HRTIMER_ADCTRGI13_EVENT_ST4CMP1                 (HRTIMER_ADCTRIGS1_TRG1ST4C1)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER4 compare 1 */
#define HRTIMER_ADCTRGI13_EVENT_ST4CMP2                 (HRTIMER_ADCTRIGS1_TRG1ST4C2)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER4 compare 2 */
#define HRTIMER_ADCTRGI13_EVENT_ST4CMP3                 (HRTIMER_ADCTRIGS1_TRG1ST4C3)                                   /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER4 compare 3 */
#define HRTIMER_ADCTRGI13_EVENT_ST4RST                  (HRTIMER_ADCTRIGS1_TRG1ST4RST)                                  /*!< HRTIMER_ADCTRIG1 or HRTIMER_ADCTRIG3 on Slave_TIMER4 reset and counter roll-over event */
#define HRTIMER_ADCTRGI13_EVENT_ST5CMP1                 (HRTIMER_ADCTRIGS1A_TRG1ST5C1)                                  /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER5 compare 1 */
#define HRTIMER_ADCTRGI13_EVENT_ST5CMP2                 (HRTIMER_ADCTRIGS1A_TRG1ST5C2)                                  /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER5 compare 2 */
#define HRTIMER_ADCTRGI13_EVENT_ST5CMP3                 (HRTIMER_ADCTRIGS1A_TRG1ST5C3)                                  /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER5 compare 3 */
#define HRTIMER_ADCTRGI13_EVENT_ST5PER                  (HRTIMER_ADCTRIGS1A_TRG1ST5PER)                                 /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER5 period */
#define HRTIMER_ADCTRGI13_EVENT_ST5RST                  (HRTIMER_ADCTRIGS1A_TRG1ST5RST)                                 /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER5 reset and counter roll-over event */
#define HRTIMER_ADCTRGI13_EVENT_ST6CMP1                 (HRTIMER_ADCTRIGS1A_TRG1ST6C1)                                  /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER6 compare 1 */
#define HRTIMER_ADCTRGI13_EVENT_ST6CMP2                 (HRTIMER_ADCTRIGS1A_TRG1ST6C2)                                  /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER6 compare 2 */
#define HRTIMER_ADCTRGI13_EVENT_ST6CMP3                 (HRTIMER_ADCTRIGS1A_TRG1ST6C3)                                  /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER6 compare 3 */
#define HRTIMER_ADCTRGI13_EVENT_ST6PER                  (HRTIMER_ADCTRIGS1A_TRG1ST6PER)                                 /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER6 period */
#define HRTIMER_ADCTRGI13_EVENT_ST6RST                  (HRTIMER_ADCTRIGS1A_TRG1ST6RST)                                 /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER6 reset and counter roll-over event */
#define HRTIMER_ADCTRGI13_EVENT_ST7CMP1                 (HRTIMER_ADCTRIGS1A_TRG1ST7C1)                                  /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER7 compare 1 */
#define HRTIMER_ADCTRGI13_EVENT_ST7CMP2                 (HRTIMER_ADCTRIGS1A_TRG1ST7C2)                                  /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER7 compare 2 */
#define HRTIMER_ADCTRGI13_EVENT_ST7CMP3                 (HRTIMER_ADCTRIGS1A_TRG1ST7C3)                                  /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER7 compare 3 */
#define HRTIMER_ADCTRGI13_EVENT_ST7PER                  (HRTIMER_ADCTRIGS1A_TRG1ST7PER)                                 /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER7 period */
#define HRTIMER_ADCTRGI13_EVENT_ST7RST                  (HRTIMER_ADCTRIGS1A_TRG1ST7RST)                                 /*!< HRTIMER_ADCTRIG1A or HRTIMER_ADCTRIG3A on Slave_TIMER7 reset and counter roll-over event */

/* ADC trigger event */
/* ADC trigger 4,6,8 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_MASTER_CMP0         ((uint32_t)0x00000000U)                                         /*!< 000000: ADC triggered by compare 0 event of Master_TIMER */
#define HRTIMER_ADC_EXT_TRIG_468_BY_MASTER_CMP1         ((uint32_t)0x00000001U)                                         /*!< 000001: ADC triggered by compare 1 event of Master_TIMER */
#define HRTIMER_ADC_EXT_TRIG_468_BY_MASTER_CMP2         ((uint32_t)0x00000002U)                                         /*!< 000010: ADC triggered by compare 2 event of Master_TIMER */
#define HRTIMER_ADC_EXT_TRIG_468_BY_MASTER_CMP3         ((uint32_t)0x00000003U)                                         /*!< 000011: ADC triggered by compare 3 event of Master_TIMER */
#define HRTIMER_ADC_EXT_TRIG_468_BY_MASTER_PERIOD       ((uint32_t)0x00000004U)                                         /*!< 000100: ADC triggered by period event of Master_TIMER */
#define HRTIMER_ADC_EXT_TRIG_468_BY_EXEV_0              ((uint32_t)0x00000005U)                                         /*!< 000101: ADC triggered by external event 0 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_EXEV_1              ((uint32_t)0x00000006U)                                         /*!< 000110: ADC triggered by external event 1 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_EXEV_2              ((uint32_t)0x00000007U)                                         /*!< 000111: ADC triggered by external event 2 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_EXEV_3              ((uint32_t)0x00000008U)                                         /*!< 001000: ADC triggered by external event 3 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_EXEV_4              ((uint32_t)0x00000009U)                                         /*!< 001001: ADC triggered by external event 4 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST0_CMP2            ((uint32_t)0x0000000AU)                                         /*!< 001010: ADC triggered by compare 2 event of Slave_TIMER0 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST0_CMP3            ((uint32_t)0x0000000BU)                                         /*!< 001011: ADC triggered by compare 3 event of Slave_TIMER0 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST0_PERIOD          ((uint32_t)0x0000000CU)                                         /*!< 001100: ADC triggered by period event of Slave_TIMER0 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST0_RESET           ((uint32_t)0x0000000DU)                                         /*!< 001101: ADC triggered by reset and counter roll-over event of Slave_TIMER0 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST1_CMP2            ((uint32_t)0x0000000EU)                                         /*!< 001110: ADC triggered by compare 2 event of Slave_TIMER1 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST1_CMP3            ((uint32_t)0x0000000FU)                                         /*!< 001111: ADC triggered by compare 3 event of Slave_TIMER1 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST1_PERIOD          ((uint32_t)0x00000010U)                                         /*!< 010000: ADC triggered by period event of Slave_TIMER1 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST1_RESET           ((uint32_t)0x00000011U)                                         /*!< 010001: ADC triggered by reset and counter roll-over event of Slave_TIMER1 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST2_CMP2            ((uint32_t)0x00000012U)                                         /*!< 010010: ADC triggered by compare 2 event of Slave_TIMER2 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST2_CMP3            ((uint32_t)0x00000013U)                                         /*!< 010011: ADC triggered by compare 3 event of Slave_TIMER2 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST2_PERIOD          ((uint32_t)0x00000014U)                                         /*!< 010100: ADC triggered by period event of Slave_TIMER2 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST3_CMP2            ((uint32_t)0x00000015U)                                         /*!< 010101: ADC triggered by compare 2 event of Slave_TIMER3 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST3_CMP3            ((uint32_t)0x00000016U)                                         /*!< 010110: ADC triggered by compare 3 event of Slave_TIMER3 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST3_PERIOD          ((uint32_t)0x00000017U)                                         /*!< 010111: ADC triggered by period event of Slave_TIMER3 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST4_CMP2            ((uint32_t)0x00000018U)                                         /*!< 011000: ADC triggered by compare 2 event of Slave_TIMER4 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST4_CMP3            ((uint32_t)0x00000019U)                                         /*!< 011001: ADC triggered by compare 3 event of Slave_TIMER4 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST4_PERIOD          ((uint32_t)0x0000001AU)                                         /*!< 011010: ADC triggered by period event of Slave_TIMER4 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST5_CMP1            ((uint32_t)0x0000001BU)                                         /*!< 011011: ADC triggered by compare 1 event of Slave_TIMER5 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST5_CMP2            ((uint32_t)0x0000001CU)                                         /*!< 011100: ADC triggered by compare 2 event of Slave_TIMER5 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST5_CMP3            ((uint32_t)0x0000001DU)                                         /*!< 011101: ADC triggered by compare 3 event of Slave_TIMER5 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST5_PERIOD          ((uint32_t)0x0000001EU)                                         /*!< 011110: ADC triggered by period event of Slave_TIMER5 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST5_RESET           ((uint32_t)0x0000001FU)                                         /*!< 011111: ADC triggered by reset and counter roll-over event of Slave_TIMER5 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST6_CMP1            ((uint32_t)0x00000020U)                                         /*!< 100000: ADC triggered by compare 1 event of Slave_TIMER6 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST6_CMP2            ((uint32_t)0x00000021U)                                         /*!< 100001: ADC triggered by compare 2 event of Slave_TIMER6 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST6_CMP3            ((uint32_t)0x00000022U)                                         /*!< 100010: ADC triggered by compare 3 event of Slave_TIMER6 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST6_PERIOD          ((uint32_t)0x00000023U)                                         /*!< 100011: ADC triggered by period event of Slave_TIMER6 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST6_RESET           ((uint32_t)0x00000024U)                                         /*!< 100100: ADC triggered by reset and counter roll-over event of Slave_TIMER6 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST7_CMP1            ((uint32_t)0x00000025U)                                         /*!< 100101: ADC triggered by compare 1 event of Slave_TIMER7 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST7_CMP2            ((uint32_t)0x00000026U)                                         /*!< 100110: ADC triggered by compare 2 event of Slave_TIMER7 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST7_CMP3            ((uint32_t)0x00000027U)                                         /*!< 100111: ADC triggered by compare 3 event of Slave_TIMER7 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST7_PERIOD          ((uint32_t)0x00000028U)                                         /*!< 101000: ADC triggered by period event of Slave_TIMER7 */
#define HRTIMER_ADC_EXT_TRIG_468_BY_ST7_RESET           ((uint32_t)0x00000029U)                                         /*!< 101001: ADC triggered by reset and counter roll-over event of Slave_TIMER7 */

/* ADC trigger 5,7,9 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_MASTER_CMP0         ((uint32_t)0x00000000U)                                         /*!< 000000: ADC triggered by compare 0 event of Master_TIMER */
#define HRTIMER_ADC_EXT_TRIG_579_BY_MASTER_CMP1         ((uint32_t)0x00000001U)                                         /*!< 000001: ADC triggered by compare 1 event of Master_TIMER */
#define HRTIMER_ADC_EXT_TRIG_579_BY_MASTER_CMP2         ((uint32_t)0x00000002U)                                         /*!< 000010: ADC triggered by compare 2 event of Master_TIMER */
#define HRTIMER_ADC_EXT_TRIG_579_BY_MASTER_CMP3         ((uint32_t)0x00000003U)                                         /*!< 000011: ADC triggered by compare 3 event of Master_TIMER */
#define HRTIMER_ADC_EXT_TRIG_579_BY_MASTER_PERIOD       ((uint32_t)0x00000004U)                                         /*!< 000100: ADC triggered by period event of Master_TIMER */
#define HRTIMER_ADC_EXT_TRIG_579_BY_EXEV_5              ((uint32_t)0x00000005U)                                         /*!< 000101: ADC triggered by external event 5 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_EXEV_6              ((uint32_t)0x00000006U)                                         /*!< 000110: ADC triggered by external event 6 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_EXEV_7              ((uint32_t)0x00000007U)                                         /*!< 000111: ADC triggered by external event 7 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_EXEV_8              ((uint32_t)0x00000008U)                                         /*!< 001000: ADC triggered by external event 8 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_EXEV_9              ((uint32_t)0x00000009U)                                         /*!< 001001: ADC triggered by external event 9 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST0_CMP1            ((uint32_t)0x0000000AU)                                         /*!< 001010: ADC triggered by compare 1 event of Slave_TIMER0 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST0_CMP3            ((uint32_t)0x0000000BU)                                         /*!< 001011: ADC triggered by compare 3 event of Slave_TIMER0 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST0_PERIOD          ((uint32_t)0x0000000CU)                                         /*!< 001100: ADC triggered by period event of Slave_TIMER0 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST1_CMP1            ((uint32_t)0x0000000DU)                                         /*!< 001101: ADC triggered by compare 1 event of Slave_TIMER1 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST1_CMP3            ((uint32_t)0x0000000EU)                                         /*!< 001110: ADC triggered by compare 3 event of Slave_TIMER1 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST1_PERIOD          ((uint32_t)0x0000000FU)                                         /*!< 001111: ADC triggered by period event of Slave_TIMER1 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST2_CMP1            ((uint32_t)0x00000010U)                                         /*!< 010000: ADC triggered by compare 1 event of Slave_TIMER2 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST2_CMP3            ((uint32_t)0x00000011U)                                         /*!< 010001: ADC triggered by compare 3 event of Slave_TIMER2 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST2_PERIOD          ((uint32_t)0x00000012U)                                         /*!< 010010: ADC triggered by period event of Slave_TIMER2 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST2_RESET           ((uint32_t)0x00000013U)                                         /*!< 010011: ADC triggered by reset and counter roll-over event of Slave_TIMER2 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST3_CMP1            ((uint32_t)0x00000014U)                                         /*!< 010100: ADC triggered by compare 1 event of Slave_TIMER3 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST3_CMP3            ((uint32_t)0x00000015U)                                         /*!< 010101: ADC triggered by compare 3 event of Slave_TIMER3 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST3_PERIOD          ((uint32_t)0x00000016U)                                         /*!< 010110: ADC triggered by period event of Slave_TIMER3 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST3_RESET           ((uint32_t)0x00000017U)                                         /*!< 010111: ADC triggered by reset and counter roll-over event of Slave_TIMER3 */ 
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST4_CMP1            ((uint32_t)0x00000018U)                                         /*!< 011000: ADC triggered by compare 1 event of Slave_TIMER4 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST4_CMP2            ((uint32_t)0x00000019U)                                         /*!< 011001: ADC triggered by compare 2 event of Slave_TIMER4 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST4_CMP3            ((uint32_t)0x0000001AU)                                         /*!< 011010: ADC triggered by compare 3 event of Slave_TIMER4 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST4_RESET           ((uint32_t)0x0000001BU)                                         /*!< 011011: ADC triggered by reset and counter roll-over event of Slave_TIMER4 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST5_CMP1            ((uint32_t)0x0000001CU)                                         /*!< 011100: ADC triggered by compare 1 event of Slave_TIMER5 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST5_CMP2            ((uint32_t)0x0000001DU)                                         /*!< 011101: ADC triggered by compare 2 event of Slave_TIMER5 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST5_CMP3            ((uint32_t)0x0000001EU)                                         /*!< 011110: ADC triggered by compare 3 event of Slave_TIMER5 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST5_PERIOD          ((uint32_t)0x0000001FU)                                         /*!< 011111: ADC triggered by period event of Slave_TIMER5 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST6_CMP1            ((uint32_t)0x00000020U)                                         /*!< 100000: ADC triggered by compare 1 event of Slave_TIMER6 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST6_CMP2            ((uint32_t)0x00000021U)                                         /*!< 100001: ADC triggered by compare 2 event of Slave_TIMER6 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST6_CMP3            ((uint32_t)0x00000022U)                                         /*!< 100010: ADC triggered by compare 3 event of Slave_TIMER6 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST6_PERIOD          ((uint32_t)0x00000023U)                                         /*!< 100011: ADC triggered by period event of Slave_TIMER6 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST6_RESET           ((uint32_t)0x00000024U)                                         /*!< 100100: ADC triggered by reset and counter roll-over event of Slave_TIMER6 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST7_CMP1            ((uint32_t)0x00000025U)                                         /*!< 100101: ADC triggered by compare 1 event of Slave_TIMER7 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST7_CMP2            ((uint32_t)0x00000026U)                                         /*!< 100110: ADC triggered by compare 2 event of Slave_TIMER7 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST7_CMP3            ((uint32_t)0x00000027U)                                         /*!< 100111: ADC triggered by compare 3 event of Slave_TIMER7 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST7_PERIOD          ((uint32_t)0x00000028U)                                         /*!< 101000: ADC triggered by period event of Slave_TIMER7 */
#define HRTIMER_ADC_EXT_TRIG_579_BY_ST7_RESET           ((uint32_t)0x00000029U)                                         /*!< 101001: ADC triggered by reset and counter roll-over event of Slave_TIMER7 */

/* DLL calibration control */
#define HRTIMER_CALIBRATION_ONCE                        ((uint32_t)0x88888888U)                                         /*!< DLL calibration start once */
#define HRTIMER_CALIBRATION_1048576_PERIOD              ((uint32_t)0x00000000U)                                         /*!< 1048576 * tHRTIMER_CK */
#define HRTIMER_CALIBRATION_131072_PERIOD               ((uint32_t)0x00000004U)                                         /*!< 131072 * tHRTIMER_CK */
#define HRTIMER_CALIBRATION_16384_PERIOD                ((uint32_t)0x00000008U)                                         /*!< 16384 * tHRTIMER_CK  */
#define HRTIMER_CALIBRATIO_2048_PERIOD                  ((uint32_t)0x0000000CU)                                         /*!< 2048 * tHRTIMER_CK */

/* Master_TIMER and Slave_TIMER interrupt enable or disable */
#define HRTIMER_MT_ST_INT_CMP0                          HRTIMER_STXDMAINTEN_CMP0IE                                      /*!< compare 0 interrupt */
#define HRTIMER_MT_ST_INT_CMP1                          HRTIMER_STXDMAINTEN_CMP1IE                                      /*!< compare 1 interrupt */
#define HRTIMER_MT_ST_INT_CMP2                          HRTIMER_STXDMAINTEN_CMP2IE                                      /*!< compare 2 interrupt */
#define HRTIMER_MT_ST_INT_CMP3                          HRTIMER_STXDMAINTEN_CMP3IE                                      /*!< compare 3 interrupt */
#define HRTIMER_MT_ST_INT_REP                           HRTIMER_STXDMAINTEN_REPIE                                       /*!< repetition interrupt */
#define HRTIMER_MT_INT_SYNI                             HRTIMER_MTDMAINTEN_SYNIIE                                       /*!< synchronization input interrupt */
#define HRTIMER_MT_ST_INT_UPD                           HRTIMER_STXDMAINTEN_UPIE                                        /*!< update interrupt */
#define HRTIMER_ST_INT_CAP0                             HRTIMER_STXDMAINTEN_CAP0IE                                      /*!< capture 0 interrupt */
#define HRTIMER_ST_INT_CAP1                             HRTIMER_STXDMAINTEN_CAP1IE                                      /*!< capture 1 interrupt */
#define HRTIMER_ST_INT_CH0OA                            HRTIMER_STXDMAINTEN_CH0OAIE                                     /*!< channel 0 output active interrupt */
#define HRTIMER_ST_INT_CH0ONA                           HRTIMER_STXDMAINTEN_CH0ONAIE                                    /*!< channel 0 output inactive interrupt */
#define HRTIMER_ST_INT_CH1OA                            HRTIMER_STXDMAINTEN_CH1OAIE                                     /*!< channel 1 output active interrupt */
#define HRTIMER_ST_INT_CH1ONA                           HRTIMER_STXDMAINTEN_CH1ONAIE                                    /*!< channel 1 output inactive interrupt */
#define HRTIMER_ST_INT_CNTRST                           HRTIMER_STXDMAINTEN_RSTIE                                       /*!< counter reset interrupt */
#define HRTIMER_ST_INT_DLYIDLE                          HRTIMER_STXDMAINTEN_DLYIIE                                      /*!< delayed IDLE mode entry interrupt */

/* HRTIMER common interrupt */
#define HRTIMER_INT_FLT0                                HRTIMER_INTEN_FLT0IE                                            /*!< fault 0 interrupt enable */
#define HRTIMER_INT_FLT1                                HRTIMER_INTEN_FLT1IE                                            /*!< fault 1 interrupt enable */
#define HRTIMER_INT_FLT2                                HRTIMER_INTEN_FLT2IE                                            /*!< fault 2 interrupt enable */
#define HRTIMER_INT_FLT3                                HRTIMER_INTEN_FLT3IE                                            /*!< fault 3 interrupt enable */
#define HRTIMER_INT_FLT4                                HRTIMER_INTEN_FLT4IE                                            /*!< fault 4 interrupt enable */
#define HRTIMER_INT_FLT5                                HRTIMER_INTEN_FLT5IE                                            /*!< fault 5 interrupt enable */
#define HRTIMER_INT_FLT6                                HRTIMER_INTEN_FLT6IE                                            /*!< fault 6 interrupt enable */
#define HRTIMER_INT_FLT7                                HRTIMER_INTEN_FLT7IE                                            /*!< fault 7 interrupt enable */
#define HRTIMER_INT_SYSFLT                              HRTIMER_INTEN_SYSFLTIE                                          /*!< system fault interrupt */
#define HRTIMER_INT_DLLCAL                              HRTIMER_INTEN_DLLCALIE                                          /*!< DLL calibration completed interrupt */
#define HRTIMER_INT_BMPER                               HRTIMER_INTEN_BMPERIE                                           /*!< bunch mode period interrupt */

/* Master_TIMER and Slave_TIMER interrupt flag */
#define HRTIMER_MT_ST_INT_FLAG_CMP0                     HRTIMER_STXINTF_CMP0IF                                          /*!< compare 0 interrupt flag */
#define HRTIMER_MT_ST_INT_FLAG_CMP1                     HRTIMER_STXINTF_CMP1IF                                          /*!< compare 1 interrupt flag */
#define HRTIMER_MT_ST_INT_FLAG_CMP2                     HRTIMER_STXINTF_CMP2IF                                          /*!< compare 2 interrupt flag */
#define HRTIMER_MT_ST_INT_FLAG_CMP3                     HRTIMER_STXINTF_CMP3IF                                          /*!< compare 3 interrupt flag */
#define HRTIMER_MT_ST_INT_FLAG_REP                      HRTIMER_STXINTF_REPIF                                           /*!< repetition interrupt flag */
#define HRTIMER_MT_INT_FLAG_SYNI                        HRTIMER_MTINTF_SYNIIF                                           /*!< synchronization input interrupt flag */
#define HRTIMER_MT_ST_INT_FLAG_UPD                      HRTIMER_STXINTF_UPIF                                            /*!< update interrupt flag */
#define HRTIMER_ST_INT_FLAG_CAP0                        HRTIMER_STXINTF_CAP0IF                                          /*!< capture 0 interrupt flag */
#define HRTIMER_ST_INT_FLAG_CAP1                        HRTIMER_STXINTF_CAP1IF                                          /*!< capture 1 interrupt flag */
#define HRTIMER_ST_INT_FLAG_CH0OA                       HRTIMER_STXINTF_CH0OAIF                                         /*!< channel 0 output active interrupt flag */
#define HRTIMER_ST_INT_FLAG_CH0ONA                      HRTIMER_STXINTF_CH0ONAIF                                        /*!< channel 0 output inactive interrupt flag */
#define HRTIMER_ST_INT_FLAG_CH1OA                       HRTIMER_STXINTF_CH1OAIF                                         /*!< channel 1 output active interrupt flag */
#define HRTIMER_ST_INT_FLAG_CH1ONA                      HRTIMER_STXINTF_CH1ONAIF                                        /*!< channel 1 output inactive interrupt flag */
#define HRTIMER_ST_INT_FLAG_CNTRST                      HRTIMER_STXINTF_RSTIF                                           /*!< counter reset interrupt flag */
#define HRTIMER_ST_INT_FLAG_DLYIDLE                     HRTIMER_STXINTF_DLYIIF                                          /*!< delayed IDLE mode entry interrupt flag */

/* HRTIMER common interrupt flag */
#define HRTIMER_INT_FLAG_FLT0                           HRTIMER_INTF_FLT0IF                                             /*!< fault 0 interrupt flag */
#define HRTIMER_INT_FLAG_FLT1                           HRTIMER_INTF_FLT1IF                                             /*!< fault 1 interrupt flag */
#define HRTIMER_INT_FLAG_FLT2                           HRTIMER_INTF_FLT2IF                                             /*!< fault 2 interrupt flag */
#define HRTIMER_INT_FLAG_FLT3                           HRTIMER_INTF_FLT3IF                                             /*!< fault 3 interrupt flag */
#define HRTIMER_INT_FLAG_FLT4                           HRTIMER_INTF_FLT4IF                                             /*!< fault 4 interrupt flag */
#define HRTIMER_INT_FLAG_FLT5                           HRTIMER_INTF_FLT5IF                                             /*!< fault 5 interrupt flag */
#define HRTIMER_INT_FLAG_FLT6                           HRTIMER_INTF_FLT6IF                                             /*!< fault 6 interrupt flag */
#define HRTIMER_INT_FLAG_FLT7                           HRTIMER_INTF_FLT7IF                                             /*!< fault 7 interrupt flag */
#define HRTIMER_INT_FLAG_SYSFLT                         HRTIMER_INTF_SYSFLTIF                                           /*!< system fault interrupt flag */
#define HRTIMER_INT_FLAG_DLLCAL                         HRTIMER_INTF_DLLCALIF                                           /*!< DLL calibration completed interrupt flag */
#define HRTIMER_INT_FLAG_BMPER                          HRTIMER_INTF_BMPERIF                                            /*!< bunch mode period interrupt flag */

/* Master_TIMER and Slave_TIMER flag */
#define HRTIMER_MT_ST_FLAG_CMP0                         HRTIMER_STXINTF_CMP0IF                                          /*!< compare 0 flag */
#define HRTIMER_MT_ST_FLAG_CMP1                         HRTIMER_STXINTF_CMP1IF                                          /*!< compare 1 flag */
#define HRTIMER_MT_ST_FLAG_CMP2                         HRTIMER_STXINTF_CMP2IF                                          /*!< compare 2 flag */
#define HRTIMER_MT_ST_FLAG_CMP3                         HRTIMER_STXINTF_CMP3IF                                          /*!< compare 3 flag */
#define HRTIMER_MT_ST_FLAG_REP                          HRTIMER_STXINTF_REPIF                                           /*!< repetition flag */
#define HRTIMER_MT_FLAG_SYNI                            HRTIMER_MTINTF_SYNIIF                                           /*!< synchronization input flag */
#define HRTIMER_MT_ST_FLAG_UPD                          HRTIMER_STXINTF_UPIF                                            /*!< update flag */
#define HRTIMER_ST_FLAG_CAP0                            HRTIMER_STXINTF_CAP0IF                                          /*!< capture 0 flag */
#define HRTIMER_ST_FLAG_CAP1                            HRTIMER_STXINTF_CAP1IF                                          /*!< capture 1 flag */
#define HRTIMER_ST_FLAG_CH0OA                           HRTIMER_STXINTF_CH0OAIF                                         /*!< channel 0 output active flag */
#define HRTIMER_ST_FLAG_CH0ONA                          HRTIMER_STXINTF_CH0ONAIF                                        /*!< channel 0 output inactive flag */
#define HRTIMER_ST_FLAG_CH1OA                           HRTIMER_STXINTF_CH1OAIF                                         /*!< channel 1 output active flag */
#define HRTIMER_ST_FLAG_CH1ONA                          HRTIMER_STXINTF_CH1ONAIF                                        /*!< channel 1 output inactive flag */
#define HRTIMER_ST_FLAG_CNTRST                          HRTIMER_STXINTF_RSTIF                                           /*!< counter reset flag */
#define HRTIMER_ST_FLAG_DLYIDLE                         HRTIMER_STXINTF_DLYIIF                                          /*!< delayed IDLE mode entry flag */
#define HRTIMER_ST_FLAG_CBLN                            HRTIMER_STXINTF_CBLNF                                           /*!< current balanced flag */
#define HRTIMER_ST_FLAG_BLNIDLE                         HRTIMER_STXINTF_BLNIF                                           /*!< balanced IDLE flag */
#define HRTIMER_ST_FLAG_CH0OUTS                         HRTIMER_STXINTF_CH0SF                                           /*!< channel 0 output status flag */
#define HRTIMER_ST_FLAG_CH1OUTS                         HRTIMER_STXINTF_CH1SF                                           /*!< channel 1 output status flag */
#define HRTIMER_ST_FLAG_CH0OUT                          HRTIMER_STXINTF_CH0F                                            /*!< channel 0 output flag */
#define HRTIMER_ST_FLAG_CH1OUT                          HRTIMER_STXINTF_CH1F                                            /*!< channel 1 output flag */

/* HRTIMER common flag */
#define HRTIMER_FLAG_FLT0                               HRTIMER_INTF_FLT0IF                                             /*!< fault 0 flag */
#define HRTIMER_FLAG_FLT1                               HRTIMER_INTF_FLT1IF                                             /*!< fault 1 flag */
#define HRTIMER_FLAG_FLT2                               HRTIMER_INTF_FLT2IF                                             /*!< fault 2 flag */
#define HRTIMER_FLAG_FLT3                               HRTIMER_INTF_FLT3IF                                             /*!< fault 3 flag */
#define HRTIMER_FLAG_FLT4                               HRTIMER_INTF_FLT4IF                                             /*!< fault 4 flag */
#define HRTIMER_FLAG_FLT5                               HRTIMER_INTF_FLT5IF                                             /*!< fault 5 flag */
#define HRTIMER_FLAG_FLT6                               HRTIMER_INTF_FLT6IF                                             /*!< fault 6 flag */
#define HRTIMER_FLAG_FLT7                               HRTIMER_INTF_FLT7IF                                             /*!< fault 7 flag */
#define HRTIMER_FLAG_SYSFLT                             HRTIMER_INTF_SYSFLTIF                                           /*!< system fault flag */
#define HRTIMER_FLAG_DLLCAL                             HRTIMER_INTF_DLLCALIF                                           /*!< DLL calibration completed flag */
#define HRTIMER_FLAG_BMPER                              HRTIMER_INTF_BMPERIF                                            /*!< bunch mode period flag */

/* Master_TIMER and Slave_TIMER DMA request */
#define HRTIMER_MT_ST_DMA_CMP0                          HRTIMER_STXDMAINTEN_CMP0DEN                                     /*!< compare 0 DMA request */
#define HRTIMER_MT_ST_DMA_CMP1                          HRTIMER_STXDMAINTEN_CMP1DEN                                     /*!< compare 1 DMA request */
#define HRTIMER_MT_ST_DMA_CMP2                          HRTIMER_STXDMAINTEN_CMP2DEN                                     /*!< compare 2 DMA request */
#define HRTIMER_MT_ST_DMA_CMP3                          HRTIMER_STXDMAINTEN_CMP3DEN                                     /*!< compare 3 DMA request */
#define HRTIMER_MT_ST_DMA_REP                           HRTIMER_STXDMAINTEN_REPDEN                                      /*!< repetition DMA request */
#define HRTIMER_MT_DMA_SYNID                            HRTIMER_MTDMAINTEN_SYNIDEN                                      /*!< synchronization input DMA request */
#define HRTIMER_MT_ST_DMA_UPD                           HRTIMER_STXDMAINTEN_UPDEN                                       /*!< update DMA request */
#define HRTIMER_ST_DMA_CAP0                             HRTIMER_STXDMAINTEN_CAP0DEN                                     /*!< capture 0 DMA request */
#define HRTIMER_ST_DMA_CAP1                             HRTIMER_STXDMAINTEN_CAP1DEN                                     /*!< capture 1 DMA request */
#define HRTIMER_ST_DMA_CH0OA                            HRTIMER_STXDMAINTEN_CH0OADEN                                    /*!< channel 0 output active DMA request */
#define HRTIMER_ST_DMA_CH0ONA                           HRTIMER_STXDMAINTEN_CH0ONADEN                                   /*!< channel 0 output inactive DMA request */
#define HRTIMER_ST_DMA_CH1OA                            HRTIMER_STXDMAINTEN_CH1OADEN                                    /*!< channel 1 output active DMA request */
#define HRTIMER_ST_DMA_CH1ONA                           HRTIMER_STXDMAINTEN_CH1ONADEN                                   /*!< channel 1 output inactive DMA request */
#define HRTIMER_ST_DMA_CNTRST                           HRTIMER_STXDMAINTEN_RSTDEN                                      /*!< counter reset DMA request */
#define HRTIMER_ST_DMA_DLYIDLE                          HRTIMER_STXDMAINTEN_DLYIDEN                                     /*!< delay IDLE DMA request */

/* Master_TIMER or Slave_TIMER update by software */
#define HRTIMER_UPDATE_SW_MT                            (HRTIMER_CTL1_MTSUP)                                            /*!< Master_TIMER software update */
#define HRTIMER_UPDATE_SW_ST0                           (HRTIMER_CTL1_ST0SUP)                                           /*!< Slave_TIMER0 software update */
#define HRTIMER_UPDATE_SW_ST1                           (HRTIMER_CTL1_ST1SUP)                                           /*!< Slave_TIMER1 software update */
#define HRTIMER_UPDATE_SW_ST2                           (HRTIMER_CTL1_ST2SUP)                                           /*!< Slave_TIMER2 software update */
#define HRTIMER_UPDATE_SW_ST3                           (HRTIMER_CTL1_ST3SUP)                                           /*!< Slave_TIMER3 software update */
#define HRTIMER_UPDATE_SW_ST4                           (HRTIMER_CTL1_ST4SUP)                                           /*!< Slave_TIMER4 software update */
#define HRTIMER_UPDATE_SW_ST5                           (HRTIMER_CTL1_ST5SUP)                                           /*!< Slave_TIMER5 software update */
#define HRTIMER_UPDATE_SW_ST6                           (HRTIMER_CTL1_ST6SUP)                                           /*!< Slave_TIMER6 software update */
#define HRTIMER_UPDATE_SW_ST7                           (HRTIMER_CTL1_ST7SUP)                                           /*!< Slave_TIMER7 software update */

/* Master_TIMER or Slave_TIMER counter reset by software */
#define HRTIMER_COUNTER_RESET_SW_MT                     (HRTIMER_CTL1_MTSRST)                                           /*!< Master_TIMER software reset */
#define HRTIMER_COUNTER_RESET_SW_ST0                    (HRTIMER_CTL1_ST0SRST)                                          /*!< Slave_TIMER0 software reset */
#define HRTIMER_COUNTER_RESET_SW_ST1                    (HRTIMER_CTL1_ST1SRST)                                          /*!< Slave_TIMER1 software reset */
#define HRTIMER_COUNTER_RESET_SW_ST2                    (HRTIMER_CTL1_ST2SRST)                                          /*!< Slave_TIMER2 software reset */
#define HRTIMER_COUNTER_RESET_SW_ST3                    (HRTIMER_CTL1_ST3SRST)                                          /*!< Slave_TIMER3 software reset */
#define HRTIMER_COUNTER_RESET_SW_ST4                    (HRTIMER_CTL1_ST4SRST)                                          /*!< Slave_TIMER4 software reset */
#define HRTIMER_COUNTER_RESET_SW_ST5                    (HRTIMER_CTL1_ST5SRST)                                          /*!< Slave_TIMER5 software reset */
#define HRTIMER_COUNTER_RESET_SW_ST6                    (HRTIMER_CTL1_ST6SRST)                                          /*!< Slave_TIMER6 software reset */
#define HRTIMER_COUNTER_RESET_SW_ST7                    (HRTIMER_CTL1_ST7SRST)                                          /*!< Slave_TIMER7 software reset */

/* Slave_TIMER output exchange */
#define HRTIMER_OUTPUT_EXCHANGE_ST0            (HRTIMER_CTL1_EXC0)                                              /*!< Slave_TIMER0 exchange output */
#define HRTIMER_OUTPUT_EXCHANGE_ST1            (HRTIMER_CTL1_EXC1)                                              /*!< Slave_TIMER1 exchange output */
#define HRTIMER_OUTPUT_EXCHANGE_ST2            (HRTIMER_CTL1_EXC2)                                              /*!< Slave_TIMER2 exchange output */
#define HRTIMER_OUTPUT_EXCHANGE_ST3            (HRTIMER_CTL1_EXC3)                                              /*!< Slave_TIMER3 exchange output */
#define HRTIMER_OUTPUT_EXCHANGE_ST4            (HRTIMER_CTL1_EXC4)                                              /*!< Slave_TIMER4 exchange output */
#define HRTIMER_OUTPUT_EXCHANGE_ST5            (HRTIMER_CTL1_EXC5)                                              /*!< Slave_TIMER5 exchange output */
#define HRTIMER_OUTPUT_EXCHANGE_ST6            (HRTIMER_CTL1_EXC6)                                              /*!< Slave_TIMER6 exchange output */
#define HRTIMER_OUTPUT_EXCHANGE_ST7            (HRTIMER_CTL1_EXC7)                                              /*!< Slave_TIMER7 exchange output */

/* channel output polarity */
#define HRTIMER_CHANNEL_POLARITY_HIGH                   ((uint32_t)0x00000000U)                                         /*!< channel active high */
#define HRTIMER_CHANNEL_POLARITY_LOW                    (HRTIMER_STXCHOCTL_CH0P)                                        /*!< channel active low */

/* channel set request */
#define HRTIMER_CHANNEL_SET_NONE                        ((uint64_t)0x0000000000000000U)                                 /*!< clear all channel set request */
#define HRTIMER_CHANNEL_SET_RSTSYNI                     (HRTIMER_STXCH0SET_CH0SRST)                                     /*!< Slave_TIMERx reset event from synchronous input and software can generate channel set request */
#define HRTIMER_CHANNEL_SET_PER                         (HRTIMER_STXCH0SET_CH0SPER)                                     /*!< Slave_TIMERx period event can generate set request */
#define HRTIMER_CHANNEL_SET_CMP0                        (HRTIMER_STXCH0SET_CH0SCMP0)                                    /*!< Slave_TIMERx compare 0 event can generate set request */
#define HRTIMER_CHANNEL_SET_CMP1                        (HRTIMER_STXCH0SET_CH0SCMP1)                                    /*!< Slave_TIMERx compare 1 event can generate set request */
#define HRTIMER_CHANNEL_SET_CMP2                        (HRTIMER_STXCH0SET_CH0SCMP2)                                    /*!< Slave_TIMERx compare 2 event can generate set request */
#define HRTIMER_CHANNEL_SET_CMP3                        (HRTIMER_STXCH0SET_CH0SCMP3)                                    /*!< Slave_TIMERx compare 3 event can generate set request */
#define HRTIMER_CHANNEL_SET_MTPER                       (HRTIMER_STXCH0SET_CH0SMTPER)                                   /*!< Master_TIMER period event generates channel set request */
#define HRTIMER_CHANNEL_SET_MTCMP0                      (HRTIMER_STXCH0SET_CH0SMTCMP0)                                  /*!< Master_TIMER compare 0 event generates channel set request */
#define HRTIMER_CHANNEL_SET_MTCMP1                      (HRTIMER_STXCH0SET_CH0SMTCMP1)                                  /*!< Master_TIMER compare 1 event generates channel set request */
#define HRTIMER_CHANNEL_SET_MTCMP2                      (HRTIMER_STXCH0SET_CH0SMTCMP2)                                  /*!< Master_TIMER compare 2 event generates channel set request */
#define HRTIMER_CHANNEL_SET_MTCMP3                      (HRTIMER_STXCH0SET_CH0SMTCMP3)                                  /*!< Master_TIMER compare 3 event generates channel set request */
#define HRTIMER_CHANNEL_SET_STEV0                       (HRTIMER_STXCH0SET_CH0SSTEV0)                                   /*!< Slave_TIMERx interconnection event 0 generates channel set request */
#define HRTIMER_CHANNEL_SET_STEV1                       (HRTIMER_STXCH0SET_CH0SSTEV1)                                   /*!< Slave_TIMERx interconnection event 1 generates channel set request */
#define HRTIMER_CHANNEL_SET_STEV2                       (HRTIMER_STXCH0SET_CH0SSTEV2)                                   /*!< Slave_TIMERx interconnection event 2 generates channel set request */
#define HRTIMER_CHANNEL_SET_STEV3                       (HRTIMER_STXCH0SET_CH0SSTEV3)                                   /*!< Slave_TIMERx interconnection event 3 generates channel set request */
#define HRTIMER_CHANNEL_SET_STEV4                       (HRTIMER_STXCH0SET_CH0SSTEV4)                                   /*!< Slave_TIMERx interconnection event 4 generates channel set request */
#define HRTIMER_CHANNEL_SET_STEV5                       (HRTIMER_STXCH0SET_CH0SSTEV5)                                   /*!< Slave_TIMERx interconnection event 5 generates channel set request */
#define HRTIMER_CHANNEL_SET_STEV6                       (HRTIMER_STXCH0SET_CH0SSTEV6)                                   /*!< Slave_TIMERx interconnection event 6 generates channel set request */
#define HRTIMER_CHANNEL_SET_STEV7                       (HRTIMER_STXCH0SET_CH0SSTEV7)                                   /*!< Slave_TIMERx interconnection event 7 generates channel set request */
#define HRTIMER_CHANNEL_SET_STEV8                       (HRTIMER_STXCH0SET_CH0SSTEV8)                                   /*!< Slave_TIMERx interconnection event 8 generates channel set request */
#define HRTIMER_CHANNEL0_SET_STEV9                      (((uint64_t)HRTIMER_STxCNTRSTA_CH0SSTEV9) << 32)                /*!< Slave_TIMERx interconnection event 9 generates channel 0 set request */
#define HRTIMER_CHANNEL0_SET_STEV10                     (((uint64_t)HRTIMER_STxCNTRSTA_CH0SSTEV10) << 32)               /*!< Slave_TIMERx interconnection event 10 generates channel 0 set request */
#define HRTIMER_CHANNEL0_SET_STCNTRST                   (((uint64_t)HRTIMER_STxCNTRSTA_CH0SSTCNTRST) << 32)             /*!< Slave_TIMERx counter reset generates channel 0 set request */
#define HRTIMER_CHANNEL1_SET_STEV9                      (((uint64_t)HRTIMER_STxCNTRSTA_CH1SSTEV9) << 32)                /*!< Slave_TIMERx interconnection event 9 generates channel 1 set request */
#define HRTIMER_CHANNEL1_SET_STEV10                     (((uint64_t)HRTIMER_STxCNTRSTA_CH1SSTEV10) << 32)               /*!< Slave_TIMERx interconnection event 10 generates channel 1 set request */
#define HRTIMER_CHANNEL1_SET_STCNTRST                   (((uint64_t)HRTIMER_STxCNTRSTA_CH1SSTCNTRST) << 32)             /*!< Slave_TIMERx counter reset generates channel 1 set request */
#define HRTIMER_CHANNEL_SET_EXEV0                       (HRTIMER_STXCH0SET_CH0SEXEV0)                                   /*!< external event 0 generates channel set request */
#define HRTIMER_CHANNEL_SET_EXEV1                       (HRTIMER_STXCH0SET_CH0SEXEV1)                                   /*!< external event 1 generates channel set request */
#define HRTIMER_CHANNEL_SET_EXEV2                       (HRTIMER_STXCH0SET_CH0SEXEV2)                                   /*!< external event 2 generates channel set request */
#define HRTIMER_CHANNEL_SET_EXEV3                       (HRTIMER_STXCH0SET_CH0SEXEV3)                                   /*!< external event 3 generates channel set request */
#define HRTIMER_CHANNEL_SET_EXEV4                       (HRTIMER_STXCH0SET_CH0SEXEV4)                                   /*!< external event 4 generates channel set request */
#define HRTIMER_CHANNEL_SET_EXEV5                       (HRTIMER_STXCH0SET_CH0SEXEV5)                                   /*!< external event 5 generates channel set request */
#define HRTIMER_CHANNEL_SET_EXEV6                       (HRTIMER_STXCH0SET_CH0SEXEV6)                                   /*!< external event 6 generates channel set request */
#define HRTIMER_CHANNEL_SET_EXEV7                       (HRTIMER_STXCH0SET_CH0SEXEV7)                                   /*!< external event 7 generates channel set request */
#define HRTIMER_CHANNEL_SET_EXEV8                       (HRTIMER_STXCH0SET_CH0SEXEV8)                                   /*!< external event 8 generates channel set request */
#define HRTIMER_CHANNEL_SET_EXEV9                       (HRTIMER_STXCH0SET_CH0SEXEV9)                                   /*!< external event 9 generates channel set request */
#define HRTIMER_CHANNEL_SET_UPDATE                      (HRTIMER_STXCH0SET_CH0SUP)                                      /*!< update event generates channel set request */

/* channel reset request */
#define HRTIMER_CHANNEL_RESET_NONE                      ((uint64_t)0x0000000000000000U)                                 /*!< clear all channel reset request */
#define HRTIMER_CHANNEL_RESET_RSTSYNI                   (HRTIMER_STXCH0RST_CH0RSRST)                                    /*!< Slave_TIMERx reset event from synchronous input and software can generate channel reset request */
#define HRTIMER_CHANNEL_RESET_PER                       (HRTIMER_STXCH0RST_CH0RSPER)                                    /*!< Slave_TIMERx period event can generate reset request */
#define HRTIMER_CHANNEL_RESET_CMP0                      (HRTIMER_STXCH0RST_CH0RSCMP0)                                   /*!< Slave_TIMERx compare 0 event can generate reset request */
#define HRTIMER_CHANNEL_RESET_CMP1                      (HRTIMER_STXCH0RST_CH0RSCMP1)                                   /*!< Slave_TIMERx compare 1 event can generate reset request */
#define HRTIMER_CHANNEL_RESET_CMP2                      (HRTIMER_STXCH0RST_CH0RSCMP2)                                   /*!< Slave_TIMERx compare 2 event can generate reset request */
#define HRTIMER_CHANNEL_RESET_CMP3                      (HRTIMER_STXCH0RST_CH0RSCMP3)                                   /*!< Slave_TIMERx compare 3 event can generate reset request */
#define HRTIMER_CHANNEL_RESET_MTPER                     (HRTIMER_STXCH0RST_CH0RSMTPER)                                  /*!< Master_TIMER period event generates channel reset request */
#define HRTIMER_CHANNEL_RESET_MTCMP0                    (HRTIMER_STXCH0RST_CH0RSMTCMP0)                                 /*!< Master_TIMER compare 0 event generates channel reset request */
#define HRTIMER_CHANNEL_RESET_MTCMP1                    (HRTIMER_STXCH0RST_CH0RSMTCMP1)                                 /*!< Master_TIMER compare 1 event generates channel reset request */
#define HRTIMER_CHANNEL_RESET_MTCMP2                    (HRTIMER_STXCH0RST_CH0RSMTCMP2)                                 /*!< Master_TIMER compare 2 event generates channel reset request */
#define HRTIMER_CHANNEL_RESET_MTCMP3                    (HRTIMER_STXCH0RST_CH0RSMTCMP3)                                 /*!< Master_TIMER compare 3 event generates channel reset request */
#define HRTIMER_CHANNEL_RESET_STEV0                     (HRTIMER_STXCH0RST_CH0RSSTEV0)                                  /*!< Slave_TIMERx interconnection event 0 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_STEV1                     (HRTIMER_STXCH0RST_CH0RSSTEV1)                                  /*!< Slave_TIMERx interconnection event 1 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_STEV2                     (HRTIMER_STXCH0RST_CH0RSSTEV2)                                  /*!< Slave_TIMERx interconnection event 2 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_STEV3                     (HRTIMER_STXCH0RST_CH0RSSTEV3)                                  /*!< Slave_TIMERx interconnection event 3 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_STEV4                     (HRTIMER_STXCH0RST_CH0RSSTEV4)                                  /*!< Slave_TIMERx interconnection event 4 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_STEV5                     (HRTIMER_STXCH0RST_CH0RSSTEV5)                                  /*!< Slave_TIMERx interconnection event 5 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_STEV6                     (HRTIMER_STXCH0RST_CH0RSSTEV6)                                  /*!< Slave_TIMERx interconnection event 6 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_STEV7                     (HRTIMER_STXCH0RST_CH0RSSTEV7)                                  /*!< Slave_TIMERx interconnection event 7 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_STEV8                     (HRTIMER_STXCH0RST_CH0RSSTEV8)                                  /*!< Slave_TIMERx interconnection event 8 generates channel reset request */
#define HRTIMER_CHANNEL0_RESET_STEV9                    (((uint64_t)HRTIMER_STxCNTRSTA_CH0RSSTEV9) << 32)               /*!< Slave_TIMERx interconnection event 9 generates channel 0 reset request */
#define HRTIMER_CHANNEL0_RESET_STEV10                   (((uint64_t)HRTIMER_STxCNTRSTA_CH0RSSTEV10) << 32)              /*!< Slave_TIMERx interconnection event 10 generates channel 0 reset request */
#define HRTIMER_CHANNEL0_RESET_STCNTRST                 (((uint64_t)HRTIMER_STxCNTRSTA_CH0RSSTCNTRST) << 32)            /*!< Slave_TIMERx counter reset generates channel 0 reset request */
#define HRTIMER_CHANNEL1_RESET_STEV9                    (((uint64_t)HRTIMER_STxCNTRSTA_CH1RSSTEV9) << 32)               /*!< Slave_TIMERx interconnection event 9 generates channel 1 reset request */
#define HRTIMER_CHANNEL1_RESET_STEV10                   (((uint64_t)HRTIMER_STxCNTRSTA_CH1RSSTEV10) << 32)              /*!< Slave_TIMERx interconnection event 10 generates channel 1 reset request */
#define HRTIMER_CHANNEL1_RESET_STCNTRST                 (((uint64_t)HRTIMER_STxCNTRSTA_CH1RSSTCNTRST) << 32)            /*!< Slave_TIMERx counter reset generates channel 1 reset request */
#define HRTIMER_CHANNEL_RESET_EXEV0                     (HRTIMER_STXCH0RST_CH0RSEXEV0)                                  /*!< external event 0 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_EXEV1                     (HRTIMER_STXCH0RST_CH0RSEXEV1)                                  /*!< external event 1 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_EXEV2                     (HRTIMER_STXCH0RST_CH0RSEXEV2)                                  /*!< external event 2 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_EXEV3                     (HRTIMER_STXCH0RST_CH0RSEXEV3)                                  /*!< external event 3 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_EXEV4                     (HRTIMER_STXCH0RST_CH0RSEXEV4)                                  /*!< external event 4 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_EXEV5                     (HRTIMER_STXCH0RST_CH0RSEXEV5)                                  /*!< external event 5 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_EXEV6                     (HRTIMER_STXCH0RST_CH0RSEXEV6)                                  /*!< external event 6 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_EXEV7                     (HRTIMER_STXCH0RST_CH0RSEXEV7)                                  /*!< external event 7 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_EXEV8                     (HRTIMER_STXCH0RST_CH0RSEXEV8)                                  /*!< external event 8 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_EXEV9                     (HRTIMER_STXCH0RST_CH0RSEXEV9)                                  /*!< external event 9 generates channel reset request */
#define HRTIMER_CHANNEL_RESET_UPDATE                    (HRTIMER_STXCH0RST_CH0RSUP)                                     /*!< update event generates channel reset request */

/* channel IDLE state enable in bunch mode */
#define HRTIMER_CHANNEL_BUNCH_IDLE_DISABLE              ((uint32_t)0x00000000U)                                          /*!< channel output is not affected by the bunch mode */
#define HRTIMER_CHANNEL_BUNCH_IDLE_ENABLE               (HRTIMER_STXCHOCTL_BMCH0IEN)                                    /*!< channel output can be IDLE state in bunch mode */

/* channel output idle state */
#define HRTIMER_CHANNEL_IDLESTATE_INACTIVE              ((uint32_t)0x00000000U)                                          /*!< channel idle state output is inactive */
#define HRTIMER_CHANNEL_IDLESTATE_ACTIVE                (HRTIMER_STXCHOCTL_ISO0)                                        /*!< channel idle state output is active */

/* channel output in fault state */
#define HRTIMER_CHANNEL_FAULTSTATE_NONE                 ((uint32_t)0x00000000U)                                          /*!< no effect. the output is normally in Run mode when a fault event happened */
#define HRTIMER_CHANNEL_FAULTSTATE_ACTIVE               ((uint32_t)0x00000010U)                                          /*!< output is active level when in FAULT state */
#define HRTIMER_CHANNEL_FAULTSTATE_INACTIVE             ((uint32_t)0x00000020U)                                          /*!< output is inactive level when in FAULT state */
#define HRTIMER_CHANNEL_FAULTSTATE_HIGHZ                ((uint32_t)0x00000030U)                                          /*!< output is Hi-Z when in FAULT state */

/* channel carrier-signal mode enable */
#define HRTIMER_CHANNEL_CARRIER_DISABLED                ((uint32_t)0x00000000U)                                          /*!< the output is not affected by the fault input */
#define HRTIMER_CHANNEL_CARRIER_ENABLED                 (HRTIMER_STXCHOCTL_CH0CSEN)                                     /*!< output at active level when in FAULT state */

/* channel dead-time insert in bunch mode */
#define HRTIMER_CHANNEL_BUNCH_ENTRY_REGULAR             ((uint32_t)0x00000000U)                                          /*!< the output enter IDLE immediately */
#define HRTIMER_CHANNEL_BUNCH_ENTRY_DEADTIME            ((uint32_t)0x00000080U)                                          /*!< dead-time is inserted before entering the IDLE state */

/* software event generates channel set request or reset request */
#define HRTIMER_CHANNEL_SOFTWARE_SET                    ((uint32_t)0x00000001U)                                          /*!< software event cannot generate request */
#define HRTIMER_CHANNEL_SOFTWARE_RESET                  ((uint32_t)0x00000002U)                                          /*!< software event can generate request */

/* channel output level */
#define HRTIMER_CHANNEL_OUTPUT_ACTIVE                   ((uint32_t)0x00000001U)                                          /*!< channel outputs active level */
#define HRTIMER_CHANNEL_OUTPUT_INACTIVE                 ((uint32_t)0x00000002U)                                          /*!< channel outputs inactive leve */

/* channel run state */
#define HRTIMER_CHANNEL_STATE_IDLE                      ((uint32_t)0x00000001U)                                          /*!< Run state: the channel output can take the active or inactive level as programmed in the crossbar unit */
#define HRTIMER_CHANNEL_STATE_RUN                       ((uint32_t)0x00000002U)                                          /*!< Idle state: after an HRTIMER reset, when the outputs are disabled by software or during a bunch mode operation */
#define HRTIMER_CHANNEL_STATE_FAULT                     ((uint32_t)0x00000003U)                                          /*!< Fault state: when a fault happen */

/* bunch mode operating flag */
#define HRTIMER_BUNCHMODE_OPERATION_OFF                 ((uint32_t)0x00000000U)                                          /*!< normal operation. bunch mode is not operation */
#define HRTIMER_BUNCHMODE_OPERATION_ON                  ((uint32_t)0x80000000U)                                          /*!< bunch mode operation on-going. */

/* double trigger enable */
#define HRTIMER_DOUBLE_TRIG_DISABLE                    ((uint32_t)0x00000000U)                                          /*!< two channel DAC step trigger is generated on compare 1 event */
#define HRTIMER_DOUBLE_TRIG_ENABLE                     ((uint32_t)0x00000001U)                                          /*!< two channel DAC step trigger is generated on output 0 reset event */

/* two channel DAC step trigger */
#define HRTIMER_DOUBLE_TRIG0_BY_CPV1              ((uint32_t)0x00000000U)                                           /*!< two channel DAC step trigger is generated on compare 1 event */
#define HRTIMER_DOUBLE_TRIG0_BY_CH0_RESET         ((uint32_t)0x00000002U)                                           /*!< two channel DAC step trigger is generated on output 0 reset event */

/* two channel DAC reset trigger */
#define HRTIMER_DOUBLE_TRIG1_BY_CNT_RESET        ((uint32_t)0x00000000U)                                           /*!< two channel DAC reset trigger is generated on counter reset or roll-over event */
#define HRTIMER_DOUBLE_TRIG1_BY_CH0_SET          ((uint32_t)0x00000004U)                                           /*!< two channel DAC reset trigger is generated on output 0 set event */

/* roll-over mode */
#define HRTIMER_ROLLOVER_MODE0                          ((uint32_t)0x00000000U)                                          /*!< roll-over Event is generated when the counter is equal to 0 or to HRTIMER_STxCAR value */
#define HRTIMER_ROLLOVER_MODE1                          ((uint32_t)0x00000040U)                                          /*!< roll-over Event is generated when the counter is equal to 0 */
#define HRTIMER_ROLLOVER_MODE2                          ((uint32_t)0x00000080U)                                          /*!< roll-over Event is generated when the counter is equal to the HRTIMER_STxCAR value */

/* output roll-over mode */
#define HRTIMER_OUTPUT_ROLLOVER_MODE0                   ((uint32_t)0x00000000U)                                          /*!< output Roll-over Event is generated when the counter is equal to 0 or to HRTIMER_STxCAR value */
#define HRTIMER_OUTPUT_ROLLOVER_MODE1                   ((uint32_t)0x00000100U)                                          /*!< output Roll-over Event is generated when the counter is equal to 0 */    
#define HRTIMER_OUTPUT_ROLLOVER_MODE2                   ((uint32_t)0x00000200U)                                          /*!< output Roll-over Event is generated when the counter is equal to the HRTIMER_STxCAR value */

/* ADC roll-over mode */
#define HRTIMER_ADC_ROLLOVER_MODE0                      ((uint32_t)0x00000000U)                                          /*!< ADC Roll-over Event is generated when the counter is equal to 0 or to HRTIMER_STxCAR value */
#define HRTIMER_ADC_ROLLOVER_MODE1                      ((uint32_t)0x00000400U)                                          /*!< ADC Roll-over Event is generated when the counter is equal to 0 */    
#define HRTIMER_ADC_ROLLOVER_MODE2                      ((uint32_t)0x00000800U)                                          /*!< ADC Roll-over Event is generated when the counter is equal to the HRTIMER_STxCAR value */

/* bunch mode roll-over mode */
#define HRTIMER_BUNCH_MODE_ROLLOVER_MODE0               ((uint32_t)0x00000000U)                                          /*!< bunch mode Roll-over Event is generated when the counter is equal to 0 or to HRTIMER_STxCAR value */
#define HRTIMER_BUNCH_MODE_ROLLOVER_MODE1               ((uint32_t)0x00001000U)                                          /*!< bunch mode Roll-over Event is generated when the counter is equal to 0 */    
#define HRTIMER_BUNCH_MODE_ROLLOVER_MODE2               ((uint32_t)0x00002000U)                                          /*!< bunch mode Roll-over Event is generated when the counter is equal to the HRTIMER_STxCAR value */

/* fault and event roll-over mode */
#define HRTIMER_FAULT_EVENTROLLOVER_MODE0               ((uint32_t)0x00000000U)                                          /*!< fault and event Event is generated when the counter is equal to 0 or to HRTIMER_STxCAR value */
#define HRTIMER_FAULT_EVENTROLLOVER_MODE1               ((uint32_t)0x00004000U)                                          /*!< fault and event Event is generated when the counter is equal to 0 */    
#define HRTIMER_FAULT_EVENTROLLOVER_MODE2               ((uint32_t)0x00008000U)                                          /*!< fault and event Event is generated when the counter is equal to the HRTIMER_STxCAR value */

/* function declarations */
/* HRTIMER timebase configure functions */
/* deinit a HRTIMER */
void hrtimer_deinit(uint32_t hrtimer_periph);
/* configure and start DLL calibration */
void hrtimer_dll_calibration_start(uint32_t hrtimer_periph, uint32_t calform);
/* initialize HRTIMER HRTIMER time base parameters struct with a default value */
void hrtimer_baseinit_struct_para_init(hrtimer_baseinit_parameter_struct* baseinit);
/* initialize Master_TIMER and Slave_TIMER timerbase */
void hrtimer_timers_base_init(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_baseinit_parameter_struct* baseinit);
/* enable a counter */
void hrtimer_timers_counter_enable(uint32_t hrtimer_periph, uint32_t cntid);
/* disable a counter */
void hrtimer_timers_counter_disable(uint32_t hrtimer_periph, uint32_t cntid);
/* enable the Master_TIMER or Slave_TIMER update event */
void hrtimer_timers_update_event_enable(uint32_t hrtimer_periph, uint32_t timer_id);
/* disable the Master_TIMER or Slave_TIMER update event */
void hrtimer_timers_update_event_disable(uint32_t hrtimer_periph, uint32_t timer_id);
/* trigger the Master_TIMER and Slave_TIMER registers update by software */
void hrtimer_software_update(uint32_t hrtimer_periph, uint32_t timersrc);
/* reset the Master_TIMER and Slave_TIMER counter by software */
void hrtimer_software_counter_reset(uint32_t hrtimer_periph, uint32_t timerrst);
/* exchange Slave_TIMERx outputs */
void hrtimer_output_exchange(uint32_t hrtimer_periph, uint32_t timerexc);

/* HRTIMER waveform configure functions */
/* initialize waveform mode initialization parameters struct with a default value */
void hrtimer_timerinit_struct_para_init(hrtimer_timerinit_parameter_struct* timerinit);
/* initialize a timer to work in waveform mode */
void hrtimer_timers_waveform_init(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_timerinit_parameter_struct* timerinitpara);
/* initialize Slave_TIMER general behavior configuration struct with a default value */
void hrtimer_timercfg_struct_para_init(hrtimer_timercfg_parameter_struct* timercgf);
/* configure the general behavior of a Slave_TIMER which work in waveform mode */
void hrtimer_slavetimer_waveform_config(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_timercfg_parameter_struct * timercfg);
/* initialize compare unit configuration struct with a default value */
void hrtimer_comparecfg_struct_para_init(hrtimer_comparecfg_parameter_struct* comparecfg);
/* configure the compare unit of a Slave_TIMER which work in waveform mode */
void hrtimer_slavetimer_waveform_compare_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t comparex, hrtimer_comparecfg_parameter_struct* cmpcfg);
/* initialize channel output configuration struct  with a default value */
void hrtimer_channel_outputcfg_struct_para_init(hrtimer_channel_outputcfg_parameter_struct * channelcfg);
/* configure the channel output of a Slave_TIMER work in waveform mode */
void hrtimer_slavetimer_waveform_channel_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t channel, hrtimer_channel_outputcfg_parameter_struct * channelcfg);
/* software generates channel "set request" or "reset request" */
void hrtimer_slavetimer_waveform_channel_software_request(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t channel, uint32_t request);
/* get Slave_TIMER channel output level */
uint32_t hrtimer_slavetimer_waveform_channel_output_level_get(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t channel);
/* get Slave_TIMER channel run state */
uint32_t hrtimer_slavetimer_waveform_channel_state_get(uint32_t hrtimer_periph, uint32_t channel);
/* initialize dead time configuration struct with a default value */
void hrtimer_deadtimercfg_struct_para_init(hrtimer_deadtimecfg_parameter_struct * dtcfg);
/* configure the dead time for Slave_TIMER */
void hrtimer_slavetimer_deadtime_config(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_deadtimecfg_parameter_struct* dtcfg);
/* initialize carrier signal configuration struct with a default value */
void hrtimer_carriersignalcfg_struct_para_init(hrtimer_carriersignalcfg_parameter_struct* carriercfg);
/* configure the carrier signal mode for Slave_TIMER */
void hrtimer_slavetimer_carriersignal_config(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_carriersignalcfg_parameter_struct* carriercfg);
/* enable a output channel */
void hrtimer_output_channel_enable(uint32_t hrtimer_periph, uint32_t chid);
/* disable a output channel */
void hrtimer_output_channel_disable(uint32_t hrtimer_periph, uint32_t chid);

/* Master_TIMER and Slave_TIMER numerical related functions */
/* configure the compare value in Master_TIMER */
void hrtimer_mastertimer_compare_value_config(uint32_t hrtimer_periph, uint32_t comparex, uint32_t cmpvalue);
/* get the compare value in Master_TIMER */
uint32_t hrtimer_mastertimer_compare_value_get(uint32_t hrtimer_periph, uint32_t comparex);
/* configure the compare value in Slave_TIMER */
void hrtimer_slavetimer_compare_value_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t comparex, uint32_t cmpvalue);
/* get the compare value in Slave_TIMER */
uint32_t hrtimer_slavetimer_compare_value_get(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t comparex);
/* configure the counter value in Master_TIMER and Slave_TIMER */
void hrtimer_timers_counter_value_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t cntvalue);
/* get the counter value in Master_TIMER and Slave_TIMER */
uint32_t hrtimer_timers_counter_value_get(uint32_t hrtimer_periph, uint32_t timer_id);
/* configure the counter auto reload value in Master_TIMER and Slave_TIMER */
void hrtimer_timers_autoreload_value_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t carlvalue);
/* get the counter auto reload value in Master_TIMER and Slave_TIMER */
uint32_t hrtimer_timers_autoreload_value_get(uint32_t hrtimer_periph, uint32_t timer_id);
/* configure the counter repetition value in Master_TIMER and Slave_TIMER */
void hrtimer_timers_repetition_value_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t replvalue);
/* get the counter repetition value in Master_TIMER and Slave_TIMER */
uint32_t hrtimer_timers_repetition_value_get(uint32_t hrtimer_periph, uint32_t timer_id);

/* external event and synchronization configure functions */
/* initialize external event filtering for Slave_TIMER configuration struct with a default value */
void hrtimer_exevfilter_struct_para_init(hrtimer_exevfilter_parameter_struct * exevfilter);
/* configure the external event filtering for Slave_TIMER (blanking, windowing) */
void hrtimer_slavetimer_exevent_filtering_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t event_id, hrtimer_exevfilter_parameter_struct* exevfilter);
/* initialize external event configuration struct with a default value */
void hrtimer_exeventcfg_struct_para_init(hrtimer_exeventcfg_parameter_struct * exevcfg);
/* configure the an external event */
void hrtimer_exevent_config(uint32_t hrtimer_periph, uint32_t event_id, hrtimer_exeventcfg_parameter_struct* exevcfg);
/* configure external event digital filter clock division */
void hrtimer_exevent_prescaler(uint32_t hrtimer_periph, uint32_t prescaler);
/* initialize external event configuration struct with a default value */
void hrtimer_exeventx_counter_struct_para_init(hrtimer_exeventcnt_parameter_struct *exevcnt);
/* configure the external event X counter */
void hrtimer_exeventx_counter_config(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_exeventcnt_parameter_struct *exevcnt);
/* reset external event X counter by software */
void hrtimer_software_reset_exeventx_counter(uint32_t hrtimer_periph, uint32_t timer_id);
/* enable external event X counter */
void hrtimer_exeventx_counter_enable(uint32_t hrtimer_periph, uint32_t timer_id);
/* disable external event X counter */
void hrtimer_exeventx_counter_disable(uint32_t hrtimer_periph, uint32_t timer_id);
/* read external event X counter value */
uint32_t hrtimer_exeventx_counter_read(uint32_t hrtimer_periph, uint32_t timer_id);
/* initialize synchronization configuration struct with a default value */
void hrtimer_synccfg_struct_para_init(hrtimer_synccfg_parameter_struct* synccfg);
/* configure the synchronization input/output of the HRTIMER */
void hrtimer_synchronization_config(uint32_t hrtimer_periph, hrtimer_synccfg_parameter_struct* synccfg);
/* initialize double channel trigger struct */
void hrtimer_double_channel_struct_para_init(hrtimer_double_trigger_parameter_struct *doubletrigger);
/* configure Slave_TIMER in double channel */
void hrtimer_double_trigger_config(uint32_t hrtimer_periph, uint32_t timer_id, hrtimer_double_trigger_parameter_struct *doubletrigger);
/* initialize roll over struct with a default value */
void hrtimer_roll_over_struct_para_init(hrtimer_roll_over_parameter_struct *rollover);
/* configure Slave_TIMER in roll over mode */
void hrtimer_roll_over_mode_config(uint32_t hrtimer_periph, uint32_t timer_id,hrtimer_roll_over_parameter_struct *rollover);

/* fault configure functions */
/* configure the synchronization input/output of the HRTIMER */
void hrtimer_faultcfg_struct_para_init(hrtimer_faultcfg_parameter_struct * faultcfg);
/* configure the fault input */
void hrtimer_fault_config(uint32_t hrtimer_periph, uint32_t fault_id, hrtimer_faultcfg_parameter_struct* faultcfg);
/* configure the fault input digital filter clock division */
void hrtimer_fault_prescaler_config(uint32_t hrtimer_periph, uint32_t prescaler);
/* fault input enable */
void hrtimer_fault_input_enable(uint32_t hrtimer_periph, uint32_t fault_id);
/* fault input disable */
void hrtimer_fault_input_disable(uint32_t hrtimer_periph, uint32_t fault_id);
/* fault input couter reset */
void hrtimer_fault_counter_reset(uint32_t hrtimer_periph, uint32_t fault_id);
/* fault input blank enable */
void hrtimer_fault_blank_enable(uint32_t hrtimer_periph, uint32_t fault_id);
/* fault input blank disable */
void hrtimer_fault_blank_disable(uint32_t hrtimer_periph, uint32_t fault_id);

/* DMA configure functions */
/* enable the Master_TIMER and Slave_TIMER DMA request */
void hrtimer_timers_dma_enable(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t dmareq);
/* disable the Master_TIMER and Slave_TIMER DMA request */
void hrtimer_timers_dma_disable(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t dmareq);
/* configure the DMA mode for Master_TIMER or Slave_TIMER */
void hrtimer_dmamode_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t regupdate);

/* bunch mode configure functions */
/* initialize bunch mode configuration struct with a default value */
void hrtimer_bunchmode_struct_para_init(hrtimer_bunchmode_parameter_struct* bmcfg);
/* configure bunch mode for the HRTIMER */
void hrtimer_bunchmode_config(uint32_t hrtimer_periph, hrtimer_bunchmode_parameter_struct* bmcfg);
/* enable the bunch mode */
void hrtimer_bunchmode_enable(uint32_t hrtimer_periph);
/* disable the bunch mode */
void hrtimer_bunchmode_disable(uint32_t hrtimer_periph);
/* get bunch mode operating flag */
uint32_t hrtimer_bunchmode_flag_get(uint32_t hrtimer_periph);
/* bunch mode started by software */
void hrtimer_bunchmode_software_start(uint32_t hrtimer_periph);

/* configure the capture functions in Slave_TIMER */
/* configure the capture source in Slave_TIMER */
void hrtimer_slavetimer_capture_config(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t capturex, uint64_t trgsource);
/* capture triggered by software in Slave_TIMER */
void hrtimer_slavetimer_capture_software(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t capturex);
/* read the capture value */
hrtimer_capture_value_struct hrtimer_slavetimer_capture_value_read(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t capturex);

/* ADC trigger configure functions */ 
/* initialize ADC trigger configuration struct with a default value */
void hrtimer_adctrigcfg_struct_para_init(hrtimer_adctrigcfg_parameter_struct* triggercfg);
/* configure the trigger source to ADC and the update source(0..3) */
void hrtimer_adc_trigger0_3_config(uint32_t hrtimer_periph, uint32_t trigger_id, hrtimer_adctrigcfg_parameter_struct* triggercfg);
/* configure the trigger source to ADC and the update source(4..9) */
void hrtimer_adc_trigger4_9_config(uint32_t hrtimer_periph, uint32_t trigger_id, hrtimer_adctrigcfg_parameter_struct* triggercfg);
/* configure the trigger source prescaler of ADC (0..9) */
void hrtimer_adc_prescaler_config(uint32_t hrtimer_periph, uint32_t trigger_id, uint32_t psc);

/* get the Slave_TIMER counter direction */
DirectionStatus hrtimer_slavetimer_counter_direction_get(uint32_t hrtimer_periph, uint32_t timer_id);
/* TIMER interrupt and flag functions */
/* get the Master_TIMER and Slave_TIMER flag */
FlagStatus hrtimer_timers_flag_get(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t flag);
/* clear the Master_TIMER and Slave_TIMER flag */
void hrtimer_timers_flag_clear(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t flag);
/* get the common flag */
FlagStatus hrtimer_common_flag_get(uint32_t hrtimer_periph, uint32_t flag);
/* clear the common flag */
void hrtimer_common_flag_clear(uint32_t hrtimer_periph, uint32_t flag);
/* enable the Master_TIMER and Slave_TIMER interrupt */
void hrtimer_timers_interrupt_enable(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t interrupt);
/* disable the Master_TIMER and Slave_TIMER interrupt */
void hrtimer_timers_interrupt_disable(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t interrupt);
/* clear the Master_TIMER and Slave_TIMER interrupt flag */
FlagStatus hrtimer_timers_interrupt_flag_get(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t interrupt);
/* clear the Master_TIMER and Slave_TIMER interrupt flag */
void hrtimer_timers_interrupt_flag_clear(uint32_t hrtimer_periph, uint32_t timer_id, uint32_t interrupt);
/* enable the common interrupt */
void hrtimer_common_interrupt_enable(uint32_t hrtimer_periph, uint32_t interrupt);
/* disable common interrupt */
void hrtimer_common_interrupt_disable(uint32_t hrtimer_periph, uint32_t interrupt);
/* clear the common interrupt flag */
FlagStatus hrtimer_common_interrupt_flag_get(uint32_t hrtimer_periph, uint32_t interrupt);
/* clear the common interrupt flag */
void hrtimer_common_interrupt_flag_clear(uint32_t hrtimer_periph, uint32_t interrupt);

#endif /* GD32G5X3_HRTIMER_H */
