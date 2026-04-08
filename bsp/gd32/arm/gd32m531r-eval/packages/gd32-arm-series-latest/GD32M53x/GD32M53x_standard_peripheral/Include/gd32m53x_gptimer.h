/*!
    \file    gd32m53x_gptimer.h
    \brief   definitions for the GPTIMER

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

#ifndef GD32M53X_GPTIMER_H
#define GD32M53X_GPTIMER_H

#include "gd32m53x.h"

/* GPTIMERx(x=0,1) definitions */

#define GPTIMER0                                           GPTIMER_BASE
#define GPTIMER1                                           (GPTIMER_BASE + 0x00000100U)

/* registers definitions */
#define GPTIMER_WP(timerx)                                 REG32((timerx) + 0x00U)           /*!< GPTIMER write protect register */
#define GPTIMER_SWEN(timerx)                               REG32((timerx) + 0x04U)           /*!< GPTIMER software enable register */
#define GPTIMER_SWDIS(timerx)                              REG32((timerx) + 0x08U)           /*!< GPTIMER software disable register */
#define GPTIMER_SWRST(timerx)                              REG32((timerx) + 0x0CU)           /*!< GPTIMER software reset register */
#define GPTIMER_ESSEL(timerx)                              REG32((timerx) + 0x10U)           /*!< GPTIMER counter enable source selection register */
#define GPTIMER_DSSEL(timerx)                              REG32((timerx) + 0x14U)           /*!< GPTIMER counter disable source selection register */
#define GPTIMER_RSSEL(timerx)                              REG32((timerx) + 0x18U)           /*!< GPTIMER counter reset source selection register */
#define GPTIMER_CH0CSSEL(timerx)                           REG32((timerx) + 0x1CU)           /*!< GPTIMER channel 0 capture source selection register */
#define GPTIMER_CH1CSSEL(timerx)                           REG32((timerx) + 0x20U)           /*!< GPTIMER channel 1 capture source selection register */
#define GPTIMER_CTL0(timerx)                               REG32((timerx) + 0x24U)           /*!< GPTIMER control register 0 */
#define GPTIMER_CUPEVSSEL(timerx)                          REG32((timerx) + 0x28U)           /*!< GPTIMER count up event source selection register */
#define GPTIMER_CDNEVSSEL(timerx)                          REG32((timerx) + 0x2CU)           /*!< GPTIMER count down event source selection register */
#define GPTIMER_CH0CTL(timerx)                             REG32((timerx) + 0x30U)           /*!< GPTIMER channel 0 control register */
#define GPTIMER_CH1CTL(timerx)                             REG32((timerx) + 0x34U)           /*!< GPTIMER channel 1 control register */
#define GPTIMER_CHCTL(timerx)                              REG32((timerx) + 0x38U)           /*!< GPTIMER channel control register */
#define GPTIMER_DMAINTEN(timerx)                           REG32((timerx) + 0x3CU)           /*!< GPTIMER dma and interrupt enable register */
#define GPTIMER_INTF(timerx)                               REG32((timerx) + 0x40U)           /*!< GPTIMER interrupt flag register */
#define GPTIMER_UPSSEL(timerx)                             REG32((timerx) + 0x44U)           /*!< GPTIMER update source selection register */
#define GPTIMER_CNT(timerx)                                REG32((timerx) + 0x48U)           /*!< GPTIMER counter register */
#define GPTIMER_PSC(timerx)                                REG32((timerx) + 0x4CU)           /*!< GPTIMER prescaler  register */
#define GPTIMER_CAR(timerx)                                REG32((timerx) + 0x50U)           /*!< GPTIMER counter auto reload  register */
#define GPTIMER_CH0CV(timerx)                              REG32((timerx) + 0x54U)           /*!< GPTIMER channel 0 capture/compare value register */
#define GPTIMER_CH1CV(timerx)                              REG32((timerx) + 0x58U)           /*!< GPTIMER channel 1 capture/compare value register */
#define GPTIMER_CH0COMV_ADD(timerx)                        REG32((timerx) + 0x5CU)           /*!< GPTIMER channel 0 additional compare value register */
#define GPTIMER_CH1COMV_ADD(timerx)                        REG32((timerx) + 0x60U)           /*!< GPTIMER channel 1 additional compare value register */
#define GPTIMER_DTCTL(timerx)                              REG32((timerx) + 0x64U)           /*!< GPTIMER dead-time control register */
#define GPTIMER_ADCTL(timerx)                              REG32((timerx) + 0x68U)           /*!< GPTIMER ADC trigger control register */
#define GPTIMER_ADCCR1(timerx)                             REG32((timerx) + 0x6CU)           /*!< GPTIMER ADC trigger compare value 1 register */
#define GPTIMER_ADCCR2(timerx)                             REG32((timerx) + 0x70U)           /*!< GPTIMER ADC trigger compare value 2 register */
#define GPTIMER_ADCTRGS(timerx)                            REG32((timerx) + 0x74U)           /*!< GPTIMER ADC trigger skipping register */
#define GPTIMER_ADDINTSCTL0(timerx)                        REG32((timerx) + 0x78U)           /*!< GPTIMER additional interrupt skipping control register 0 */
#define GPTIMER_ADDINTSCTL1(timerx)                        REG32((timerx) + 0x7CU)           /*!< GPTIMER additional interrupt skipping control register 1 */
#define GPTIMER_IADCTSS(timerx)                            REG32((timerx) + 0x80U)           /*!< GPTIMER interrupt and ADC trigger signal skipping register */
#define GPTIMER_CREP(timerx)                               REG32((timerx) + 0x84U)           /*!< GPTIMER counter repetition register */
#define GPTIMER_SYNRSTCTL(timerx)                          REG32((timerx) + 0x88U)           /*!< GPTIMER synchronous reset control register*/
#define GPTIMER_DMACFG(timerx)                             REG32((timerx) + 0xE0U)           /*!< GPTIMER DMA configuration register */
#define GPTIMER_DMATB(timerx)                              REG32((timerx) + 0xE4U)           /*!< GPTIMER DMA transfer buffer register */
#define GPTIMER_CFG(timerx)                                REG32((timerx) + 0xFCU)           /*!< GPTIMER configuration register */

/* bits definitions */
/* GPTIMER_WP */
#define GPTIMER_WP_WPEN                                    BIT(0)                            /*!< register write protect enable */
#define GPTIMER_WP_SWEWPEN                                 BIT(1)                            /*!< GPTIMER_SWEN write protect enable*/
#define GPTIMER_WP_SWDWPEN                                 BIT(2)                            /*!< GPTIMER_SWDIS write protect enable */
#define GPTIMER_WP_SWRWPEN                                 BIT(3)                            /*!< GPTIMER_SWRST write protect enable */
#define GPTIMER_WP_WPKEY                                   BITS(8,15)                        /*!< write protect key */

/* GPTIMER_SWEN */
#define GPTIMER_SWEN_GPTIMER0SWEN                          BIT(0)                            /*!< GPTIMER0 counter software enable */
#define GPTIMER_SWEN_GPTIMER1SWEN                          BIT(1)                            /*!< GPTIMER1 counter software enable */

/* GPTIMER_SWDIS */
#define GPTIMER_SWDIS_GPTIMER0SWDIS                        BIT(0)                            /*!< GPTIMER0 counter software disable */
#define GPTIMER_SWDIS_GPTIMER1SWDIS                        BIT(1)                            /*!< GPTIMER1 counter software disable */

/* GPTIMER_SWRST */
#define GPTIMER_SWRST_GPTIMER0SWRST                        BIT(0)                            /*!< GPTIMER0 counter software reset */
#define GPTIMER_SWRST_GPTIMER1SWRST                        BIT(1)                            /*!< GPTIMER1 counter software reset */

/* GPTIMER_ESSEL */
#define GPTIMER_ESSEL_ETI0ENCNT                            BITS(0,1)                         /*!< the ETI0 signal edge enable counter function enable */
#define GPTIMER_ESSEL_ETI1ENCNT                            BITS(2,3)                         /*!< the ETI1 signal edge enable counter function enable */
#define GPTIMER_ESSEL_ETI2ENCNT                            BITS(4,5)                         /*!< the ETI2 signal edge enable counter function enable */
#define GPTIMER_ESSEL_ETI3ENCNT                            BITS(6,7)                         /*!< the ETI3 signal edge enable counter function enable */
#define GPTIMER_ESSEL_CH0ENCNT                             BITS(8,9)                         /*!< the channel 0 signal edge enable counter function enable */
#define GPTIMER_ESSEL_CH1ENCNT                             BITS(10,11)                       /*!< the channel 1 signal edge enable counter function enable */
#define GPTIMER_ESSEL_EVSEL0ENCNT                          BIT(16)                           /*!< the EVSEL0 signal enable counter function enable */
#define GPTIMER_ESSEL_EVSEL1ENCNT                          BIT(17)                           /*!< the EVSEL1 signal enable counter function enable */
#define GPTIMER_ESSEL_EVSEL2ENCNT                          BIT(18)                           /*!< the EVSEL2 signal enable counter function enable */
#define GPTIMER_ESSEL_EVSEL3ENCNT                          BIT(19)                           /*!< the EVSEL3 signal enable counter function enable */
#define GPTIMER_ESSEL_EVSEL4ENCNT                          BIT(20)                           /*!< the EVSEL4 signal enable counter function enable */
#define GPTIMER_ESSEL_EVSEL5ENCNT                          BIT(21)                           /*!< the EVSEL5 signal enable counter function enable */
#define GPTIMER_ESSEL_EVSEL6ENCNT                          BIT(22)                           /*!< the EVSEL6 signal enable counter function enable */
#define GPTIMER_ESSEL_EVSEL7ENCNT                          BIT(23)                           /*!< the EVSEL7 signal enable counter function enable */
#define GPTIMER_ESSEL_SWENCNT                              BIT(31)                           /*!< the software signal enable counter function enable */

/* GPTIMER_DSSEL */
#define GPTIMER_DSSEL_ETI0DISCNT                           BITS(0,1)                         /*!< the ETI0 signal edge disable counter function enable */
#define GPTIMER_DSSEL_ETI1DISCNT                           BITS(2,3)                         /*!< the ETI1 signal edge disable counter function enable */
#define GPTIMER_DSSEL_ETI2DISCNT                           BITS(4,5)                         /*!< the ETI2 signal edge disable counter function enable */
#define GPTIMER_DSSEL_ETI3DISCNT                           BITS(6,7)                         /*!< the ETI3 signal edge disable counter function enable */
#define GPTIMER_DSSEL_CH0DISCNT                            BITS(8,9)                         /*!< the channel 0 signal edge disable counter function enable */
#define GPTIMER_DSSEL_CH1DISCNT                            BITS(10,11)                       /*!< the channel 1 signal edge disable counter function enable */
#define GPTIMER_DSSEL_EVSEL0DISCNT                         BIT(16)                           /*!< the EVSEL0 signal disable counter function enable */
#define GPTIMER_DSSEL_EVSEL1DISCNT                         BIT(17)                           /*!< the EVSEL1 signal disable counter function enable */
#define GPTIMER_DSSEL_EVSEL2DISCNT                         BIT(18)                           /*!< the EVSEL2 signal disable counter function enable */
#define GPTIMER_DSSEL_EVSEL3DISCNT                         BIT(19)                           /*!< the EVSEL3 signal disable counter function enable */
#define GPTIMER_DSSEL_EVSEL4DISCNT                         BIT(20)                           /*!< the EVSEL4 signal disable counter function enable */
#define GPTIMER_DSSEL_EVSEL5DISCNT                         BIT(21)                           /*!< the EVSEL5 signal disable counter function enable */
#define GPTIMER_DSSEL_EVSEL6DISCNT                         BIT(22)                           /*!< the EVSEL6 signal disable counter function enable */
#define GPTIMER_DSSEL_EVSEL7DISCNT                         BIT(23)                           /*!< the EVSEL7 signal disable counter function enable */
#define GPTIMER_DSSEL_SWDISCNT                             BIT(31)                           /*!< the software signal disable counter function enable */

/* GPTIMER_RSSEL */
#define GPTIMER_RSSEL_ETI0RSTCNT                           BITS(0,1)                         /*!< the ETI0 signal edge reset counter function enable */
#define GPTIMER_RSSEL_ETI1RSTCNT                           BITS(2,3)                         /*!< the ETI1 signal edge reset counter function enable */
#define GPTIMER_RSSEL_ETI2RSTCNT                           BITS(4,5)                         /*!< the ETI2 signal edge reset counter function enable */
#define GPTIMER_RSSEL_ETI3RSTCNT                           BITS(6,7)                         /*!< the ETI3 signal edge reset counter function enable */
#define GPTIMER_RSSEL_CH0RSTCNT                            BITS(8,9)                         /*!< the channel 0 signal edge reset counter function enable */
#define GPTIMER_RSSEL_CH1RSTCNT                            BITS(10,11)                       /*!< the channel 1 signal edge reset counter function enable */
#define GPTIMER_RSSEL_EVSEL0RSTCNT                         BIT(16)                           /*!< the EVSEL0 signal reset counter function enable */
#define GPTIMER_RSSEL_EVSEL1RSTCNT                         BIT(17)                           /*!< the EVSEL1 signal reset counter function enable */
#define GPTIMER_RSSEL_EVSEL2RSTCNT                         BIT(18)                           /*!< the EVSEL2 signal reset counter function enable */
#define GPTIMER_RSSEL_EVSEL3RSTCNT                         BIT(19)                           /*!< the EVSEL3 signal reset counter function enable */
#define GPTIMER_RSSEL_EVSEL4RSTCNT                         BIT(20)                           /*!< the EVSEL4 signal reset counter function enable */
#define GPTIMER_RSSEL_EVSEL5RSTCNT                         BIT(21)                           /*!< the EVSEL5 signal reset counter function enable */
#define GPTIMER_RSSEL_EVSEL6RSTCNT                         BIT(22)                           /*!< the EVSEL6 signal reset counter function enable */
#define GPTIMER_RSSEL_EVSEL7RSTCNT                         BIT(23)                           /*!< the EVSEL7 signal reset counter function enable */
#define GPTIMER_RSSEL_CSIRSTCNT                            BITS(24,26)                       /*!< the compares match, synchronous reset or input capture reset counter function enable */
#define GPTIMER_RSSEL_SWRSTCNT                             BIT(31)                           /*!< the software signal reset counter function enable */

/* GPTIMER_CH0CSSEL */
#define GPTIMER_CH0CSSEL_ETI0CH0IC                         BITS(0,1)                         /*!< the ETI0 signal edge as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_ETI1CH0IC                         BITS(2,3)                         /*!< the ETI1 signal edge as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_ETI2CH0IC                         BITS(4,5)                         /*!< the ETI2 signal edge as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_ETI3CH0IC                         BITS(6,7)                         /*!< the ETI3 signal edge as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_CH0CH0IC                          BITS(8,9)                         /*!< the channel 0 signal edge as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_CH1CH0IC                          BITS(10,11)                       /*!< the channel 1 signal edge as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_EVSEL0CH0IC                       BIT(16)                           /*!< the EVSEL0 signal as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_EVSEL1CH0IC                       BIT(17)                           /*!< the EVSEL1 signal as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_EVSEL2CH0IC                       BIT(18)                           /*!< the EVSEL2 signal as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_EVSEL3CH0IC                       BIT(19)                           /*!< the EVSEL3 signal as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_EVSEL4CH0IC                       BIT(20)                           /*!< the EVSEL4 signal as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_EVSEL5CH0IC                       BIT(21)                           /*!< the EVSEL5 signal as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_EVSEL6CH0IC                       BIT(22)                           /*!< the EVSEL6 signal as the channel 0 input capture source enable */
#define GPTIMER_CH0CSSEL_EVSEL7CH0IC                       BIT(23)                           /*!< the EVSEL7 signal as the channel 0 input capture source enable */

/* GPTIMER_CH1CSSEL */
#define GPTIMER_CH1CSSEL_ETI0CH0IC                         BITS(0,1)                         /*!< the ETI0 signal edge as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_ETI1CH0IC                         BITS(2,3)                         /*!< the ETI1 signal edge as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_ETI2CH0IC                         BITS(4,5)                         /*!< the ETI2 signal edge as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_ETI3CH0IC                         BITS(6,7)                         /*!< the ETI3 signal edge as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_CH0CH0IC                          BITS(8,9)                         /*!< the channel 0 signal edge as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_CH1CH0IC                          BITS(10,11)                       /*!< the channel 1 signal edge as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_EVSEL0CH0IC                       BIT(16)                           /*!< the EVSEL0 signal as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_EVSEL1CH0IC                       BIT(17)                           /*!< the EVSEL1 signal as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_EVSEL2CH0IC                       BIT(18)                           /*!< the EVSEL2 signal as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_EVSEL3CH0IC                       BIT(19)                           /*!< the EVSEL3 signal as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_EVSEL4CH0IC                       BIT(20)                           /*!< the EVSEL4 signal as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_EVSEL5CH0IC                       BIT(21)                           /*!< the EVSEL5 signal as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_EVSEL6CH0IC                       BIT(22)                           /*!< the EVSEL6 signal as the channel 1 input capture source enable */
#define GPTIMER_CH1CSSEL_EVSEL7CH0IC                       BIT(23)                           /*!< the EVSEL7 signal as the channel 1 input capture source enable */

/* GPTIMER_CTL0 */
#define GPTIMER_CTL0_CEN                                   BIT(0)                            /*!< counter enable */
#define GPTIMER_CTL0_UPDIS                                 BIT(1)                            /*!< update event disable */
#define GPTIMER_CTL0_SPM                                   BIT(3)                            /*!< single pulse mode */
#define GPTIMER_CTL0_DIR                                   BIT(4)                            /*!< direction */
#define GPTIMER_CTL0_FDIR                                  BIT(5)                            /*!< force the counting direction */
#define GPTIMER_CTL0_CAM                                   BIT(6)                            /*!< counter align mode selection */
#define GPTIMER_CTL0_ARSE                                  BIT(7)                            /*!< auto-reload shadow enable */
#define GPTIMER_CTL0_CKDIV                                 BITS(8,9)                         /*!< clock division */
#define GPTIMER_CTL0_CCSOEN                                BIT(16)                           /*!< the counter cycle synchronization signal output enable */
#define GPTIMER_CTL0_CKSSEL                                BITS(24,26)                       /*!< clock source selection */
#define GPTIMER_CTL0_CKESEL                                BITS(28,29)                       /*!< effective edge selection when ETIx(x = 0, 1, 2, 3) is selected as the clock */

/* GPTIMER_CUPEVSSEL */
#define GPTIMER_CUPEVSSEL_ETI0CUPS                         BITS(0,1)                         /*!< the ETI0 signal edge as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_ETI1CUPS                         BITS(2,3)                         /*!< the ETI1 signal edge as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_ETI2CUPS                         BITS(4,5)                         /*!< the ETI2 signal edge as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_ETI3CUPS                         BITS(6,7)                         /*!< the ETI3 signal edge as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_CH0CUPS                          BITS(8,9)                         /*!< the channel 0 signal edge as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_CH1CUPS                          BITS(10,11)                       /*!< the channel 1 signal edge as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_EVSEL0CUPS                       BIT(16)                           /*!< the EVSEL0 signal as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_EVSEL1CUPS                       BIT(17)                           /*!< the EVSEL1 signal as the count up event source function enablee */
#define GPTIMER_CUPEVSSEL_EVSEL2CUPS                       BIT(18)                           /*!< the EVSEL2 signal as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_EVSEL3CUPS                       BIT(19)                           /*!< the EVSEL3 signal as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_EVSEL4CUPS                       BIT(20)                           /*!< the EVSEL4 signal as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_EVSEL5CUPS                       BIT(21)                           /*!< the EVSEL5 signal as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_EVSEL6CUPS                       BIT(22)                           /*!< the EVSEL6 signal as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_EVSEL7CUPS                       BIT(23)                           /*!< the EVSEL7 signal as the count up event source function enable */
#define GPTIMER_CUPEVSSEL_INTLCUPS                         BITS(24,27)                       /*!< The input level as the count up event source function enable */

/* GPTIMER_CDNEVSSEL */
#define GPTIMER_CDNEVSSEL_ETI0CDWS                         BITS(0,1)                         /*!< the ETI0 signal edge as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_ETI1CDWS                         BITS(2,3)                         /*!< the ETI1 signal edge as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_ETI2CDWS                         BITS(4,5)                         /*!< the ETI2 signal edge as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_ETI3CDWS                         BITS(6,7)                         /*!< the ETI3 signal edge as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_CH0CDWS                          BITS(8,9)                         /*!< the channel 0 signal edge as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_CH1CDWS                          BITS(10,11)                       /*!< the channel 1 signal edge as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_EVSEL0CDWS                       BIT(16)                           /*!< the EVSEL0 signal as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_EVSEL1CDWS                       BIT(17)                           /*!< the EVSEL1 signal as the count down event source function enablee */
#define GPTIMER_CDNEVSSEL_EVSEL2CDWS                       BIT(18)                           /*!< the EVSEL2 signal as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_EVSEL3CDWS                       BIT(19)                           /*!< the EVSEL3 signal as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_EVSEL4CDWS                       BIT(20)                           /*!< the EVSEL4 signal as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_EVSEL5CDWS                       BIT(21)                           /*!< the EVSEL5 signal as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_EVSEL6CDWS                       BIT(22)                           /*!< the EVSEL6 signal as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_EVSEL7CDWS                       BIT(23)                           /*!< the EVSEL7 signal as the count down event source function enable */
#define GPTIMER_CDNEVSSEL_INTLCDWS                         BITS(24,27)                       /*!< The input level as the count down event source function enable */

/* GPTIMER_CH0CTL */
#define GPTIMER_CH0CTL_CH0COMDW                            BITS(0,1)                         /*!< channel 0 compare match output level control when counter count down */
#define GPTIMER_CH0CTL_CH0COMUP                            BITS(2,3)                         /*!< channel 0 compare match output level control when counter count up */
#define GPTIMER_CH0CTL_CH0ACOMDW                           BITS(4,5)                         /*!< channel 0 additional compare match output level control when counter count down */
#define GPTIMER_CH0CTL_CH0ACOMUP                           BITS(6,7)                         /*!< channel 0 additional compare match output level control when counter count up */
#define GPTIMER_CH0CTL_CH0EFF                              BIT(8)                            /*!< channel 0 output control in invalid or not when the end of the cycle and comparison match occur simultaneously */
#define GPTIMER_CH0CTL_CH0OUTM                             BITS(12,13)                       /*!< channel 0 output mode */
#define GPTIMER_CH0CTL_CH0OUTCTL                           BIT(14)                           /*!< channel 0 output control setting */
#define GPTIMER_CH0CTL_CH0REDUTY                           BIT(15)                           /*!< channel 0 output level selection when counter release from 0% or 100% duty */
#define GPTIMER_CH0CTL_CH0ENDOUT                           BITS(16,17)                       /*!< channel 0 output level selection at the end of the period */
#define GPTIMER_CH0CTL_CH0ENOUT                            BIT(18)                           /*!< channel 0 output initial level selection when counter enable */
#define GPTIMER_CH0CTL_CH0DISOUT                           BIT(19)                           /*!< channel 0 output level selection when counter disable */
#define GPTIMER_CH0CTL_CH0OUT                              BIT(20)                           /*!< channel 0 output level selection when counter enable or disable */
#define GPTIMER_CH0CTL_CH0INVSOUT                          BITS(21,22)                       /*!< channel 0 invalid level setting when GTOC sends a stop output request */
#define GPTIMER_CH0CTL_CH0CAPPSC                           BITS(26,27)                       /*!< channel 0 input capture prescaler */
#define GPTIMER_CH0CTL_CH0CAPFLT                           BITS(28,31)                       /*!< channel 0 input capture filter control */

/* GPTIMER_CH1CTL */
#define GPTIMER_CH1CTL_CH1COMDW                            BITS(0,1)                         /*!< channel 1 compare match output level control when counter count down */
#define GPTIMER_CH1CTL_CH1COMUP                            BITS(2,3)                         /*!< channel 1 compare match output level control when counter count up */
#define GPTIMER_CH1CTL_CH1ACOMDW                           BITS(4,5)                         /*!< channel 1 additional compare match output level control when counter count down */
#define GPTIMER_CH1CTL_CH1ACOMUP                           BITS(6,7)                         /*!< channel 1 additional compare match output level control when counter count up */
#define GPTIMER_CH1CTL_CH1EFF                              BIT(8)                            /*!< channel 1 output control in invalid or not when the end of the cycle and comparison match occur simultaneously */
#define GPTIMER_CH1CTL_CH1OUTM                             BITS(12,13)                       /*!< channel 1 output mode */
#define GPTIMER_CH1CTL_CH1OUTCTL                           BIT(14)                           /*!< channel 1 output control setting */
#define GPTIMER_CH1CTL_CH1REDUTY                           BIT(15)                           /*!< channel 1 output level selection when counter release from 0% or 100% duty */
#define GPTIMER_CH1CTL_CH1ENDOUT                           BITS(16,17)                       /*!< channel 1 output level selection at the end of the period */
#define GPTIMER_CH1CTL_CH1ENOUT                            BIT(18)                           /*!< channel 1 output initial level selection when counter enable */
#define GPTIMER_CH1CTL_CH1DISOUT                           BIT(19)                           /*!< channel 1 output level selection when counter disable */
#define GPTIMER_CH1CTL_CH1OUT                              BIT(20)                           /*!< channel 1 output level selection when counter enable or disable */
#define GPTIMER_CH1CTL_CH1INVSOUT                          BITS(21,22)                       /*!< channel 1 invalid level setting when GTOC sends a stop output request */
#define GPTIMER_CH1CTL_CH1CAPPSC                           BITS(26,27)                       /*!< channel 1 input capture prescaler */
#define GPTIMER_CH1CTL_CH1CAPFLT                           BITS(28,31)                       /*!< channel 1 input capture filter control */

/* GPTIMER_CHCTL */
#define GPTIMER_CHCTL_CH0EN                                BIT(0)                            /*!< channel 0 capture/compare enable */
#define GPTIMER_CHCTL_CH0SEL                               BIT(1)                            /*!< channel 0 capture/compare select */
#define GPTIMER_CHCTL_CH0COMSEN                            BIT(4)                            /*!< channel 0 compare output shadow enable */
#define GPTIMER_CHCTL_CH0COMADDSEN                         BIT(5)                            /*!< channel 0 additional compare output shadow enable */
#define GPTIMER_CHCTL_CH0SEN                               BIT(6)                            /*!< channel 0 output shadow enable */
#define GPTIMER_CHCTL_CH1EN                                BIT(8)                            /*!< channel 1 capture/compare enable */
#define GPTIMER_CHCTL_CH1SEL                               BIT(9)                            /*!< channel 1 capture/compare selection */
#define GPTIMER_CHCTL_CH1COMSEN                            BIT(12)                           /*!< channel 1 compare output shadow enable */
#define GPTIMER_CHCTL_CH1COMADDSEN                         BIT(13)                           /*!< channel 1 additional compare output shadow enable */
#define GPTIMER_CHCTL_CH1SEN                               BIT(14)                           /*!< channel 1 output shadow enable */
#define GPTIMER_CHCTL_CH1MSEL                              BIT(16)                           /*!< channel 1 mode selection */
#define GPTIMER_CHCTL_DTEN                                 BIT(17)                           /*!< the insertion of the dead time enable */
#define GPTIMER_CHCTL_STORESEL                             BIT(20)                           /*!< stop output recovery time selection */

/* GPTIMER_DMAINTEN */
#define GPTIMER_DMAINTEN_CH0IE                             BIT(0)                            /*!< channel 0 capture/compare interrupt enable */
#define GPTIMER_DMAINTEN_CH1IE                             BIT(1)                            /*!< channel 1 capture/compare interrupt enable */
#define GPTIMER_DMAINTEN_OFIE                              BIT(2)                            /*!< counter overflow interrupt enable */
#define GPTIMER_DMAINTEN_UFIE                              BIT(3)                            /*!< counter underflow interrupt enable */
#define GPTIMER_DMAINTEN_CH0COMADDIE                       BIT(4)                            /*!< channel 0 additional compare interrupt enable */
#define GPTIMER_DMAINTEN_CH1COMADDIE                       BIT(5)                            /*!< channel 1 additional compare interrupt enable */
#define GPTIMER_DMAINTEN_RSIE                              BIT(7)                            /*!< reset interrupt enable */
#define GPTIMER_DMAINTEN_CHHOUTDET                         BIT(13)                           /*!< channel 0 and channel 1 simultaneously output high level output off detection enable */
#define GPTIMER_DMAINTEN_CHLOUTDET                         BIT(14)                           /*!< channel 0 and channel 1 simultaneously output low level output off detection enable */
#define GPTIMER_DMAINTEN_RCENDIE                           BIT(15)                           /*!< repetition count end interrupt enable */
#define GPTIMER_DMAINTEN_CH0DEN                            BIT(16)                           /*!< channel 0 capture / compare DMA request enable */
#define GPTIMER_DMAINTEN_CH1DEN                            BIT(17)                           /*!< channel 1 capture / compare DMA request enable */
#define GPTIMER_DMAINTEN_OVUNDEN                           BITS(18,19)                       /*!< counter overflow / underflow DMA request enable */
#define GPTIMER_DMAINTEN_CH0COMADDEN                       BIT(20)                           /*!< channel 0 additional compare DMA request enable */
#define GPTIMER_DMAINTEN_CH1COMADDEN                       BIT(21)                           /*!< channel 1 additional compare DMA request enable */
#define GPTIMER_DMAINTEN_RCENDEN                           BIT(22)                           /*!< repetition count end DMA request enable */
#define GPTIMER_DMAINTEN_CLOSSEL                           BITS(24,25)                       /*!< closing output source selection from GTOC */

/* GPTIMER_INTF */
#define GPTIMER_INTF_CH0IF                                 BIT(0)                            /*!< channel 0 capture/compare interrupt flag */
#define GPTIMER_INTF_CH1IF                                 BIT(1)                            /*!< channel 1 capture/compare interrupt flag */
#define GPTIMER_INTF_OFIF                                  BIT(2)                            /*!< the counter overflow interrupt flag */
#define GPTIMER_INTF_UFIF                                  BIT(3)                            /*!< the counter underflow interrupt flag */
#define GPTIMER_INTF_CH0COMADDIF                           BIT(4)                            /*!< channel 0 additional compare interrupt flag */
#define GPTIMER_INTF_CH1COMADDIF                           BIT(5)                            /*!< channel 1 additional compare interrupt flag */
#define GPTIMER_INTF_RSIF                                  BIT(7)                            /*!< reset interrupt flag */
#define GPTIMER_INTF_ADT1CMUF                              BIT(8)                            /*!< ADTCV1[15:0] compare match (counting up only) flag */
#define GPTIMER_INTF_ADT1CMDF                              BIT(9)                            /*!< ADTCV1[15:0] compare match (counting down only) flag */
#define GPTIMER_INTF_ADT2CMUF                              BIT(10)                           /*!< ADTCV2[15:0] compare match (counting up only) flag */
#define GPTIMER_INTF_ADT2CMDF                              BIT(11)                           /*!< ADTCV2[15:0] compare match (counting down only) flag */
#define GPTIMER_INTF_CHHOUTF                               BIT(13)                           /*!< channel 0 and channel 1 simultaneously output high level flag */
#define GPTIMER_INTF_CHLOUTF                               BIT(14)                           /*!< channel 0 and channel 1 simultaneously output low level flag */
#define GPTIMER_INTF_RCENDIF                               BIT(15)                           /*!< repetition count end interrupt flag */
#define GPTIMER_INTF_DIRF                                  BIT(16)                           /*!< the counter direction flag */
#define GPTIMER_INTF_OSTF                                  BIT(24)                           /*!< output stop flag */

/* GPTIMER_UPSSEL */
#define GPTIMER_UPSSEL_CH0CVUPSEL                          BITS(0,1)                         /*!< channel 0 capture/compare value update mode selection */
#define GPTIMER_UPSSEL_CH0COMV_ADDUPSEL                    BITS(2,4)                         /*!< channel 0 additional comparison value update mode selection */
#define GPTIMER_UPSSEL_CH1CVUPSEL                          BITS(5,6)                         /*!< channel 1 capture/compare value update mode selection */
#define GPTIMER_UPSSEL_CH1COMV_ADDUPSEL                    BITS(7,9)                         /*!< channel 1 additional comparison value update mode selection */
#define GPTIMER_UPSSEL_ADCCR1UPSEL                         BITS(10,11)                       /*!< the ADC triggered comparison value 1 update mode selection */
#define GPTIMER_UPSSEL_ADCCR2UPSEL                         BITS(12,13)                       /*!< the ADC triggered comparison value 2 update mode selection */
#define GPTIMER_UPSSEL_CARUPSEL                            BITS(14,15)                       /*!< the counter auto reload value update mode selection, used to set when the counter auto reload value will be automatically overloaded */
#define GPTIMER_UPSSEL_GLBUPSEL                            BITS(16,17)                       /*!< global update mode update source selection */
#define GPTIMER_UPSSEL_CH0UPSEL                            BITS(24,25)                       /*!< channel 0 output mode update source selection */
#define GPTIMER_UPSSEL_CH1UPSEL                            BITS(26,27)                       /*!< channel 1 output mode update source selection */

/* GPTIMER_DTCTL */
#define GPTIMER_DTCTL_REDTCFG                              BITS(0,7)                         /*!< the rising edge dead time configuration */
#define GPTIMER_DTCTL_REDTSEN                              BIT(8)                            /*!< the rising edge dead time shadow register enable */
#define GPTIMER_DTCTL_FEDTCFG                              BITS(16,23)                       /*!< the falling edge dead time configuration */
#define GPTIMER_DTCTL_FEDTSEN                              BIT(24)                           /*!< the falling edge dead time shadow register is enabled */
#define GPTIMER_DTCTL_DTASYEN                              BIT(31)                           /*!< dead time asymmetric mode enable */

/* GPTIMER_ADCTL */
#define GPTIMER_ADCTL_ADTCV1SSEL                           BITS(0,2)                         /*!< the ADC conversion request skipping source selection and the trigger signal generated by ADTCV1[15:0] */
#define GPTIMER_ADCTL_ADTCV2SSEL                           BITS(4,6)                         /*!< the ADC conversion request skipping source selection and the trigger signal generated by ADTCV2[15:0] */
#define GPTIMER_ADCTL_ADTCV1SEN                            BIT(8)                            /*!< the ADTCV1[15:0] shadow register enable */
#define GPTIMER_ADCTL_ADTCV2SEN                            BIT(9)                            /*!< the ADTCV2[15:0] shadow register enable */
#define GPTIMER_ADCTL_ADT1UPGTEN                           BIT(12)                           /*!< the ADTCV1[15:0] comparison match (count up only) generate trigger enable */
#define GPTIMER_ADCTL_ADT1DWGTEN                           BIT(13)                           /*!< the ADTCV1[15:0] comparison match (count down only) generate trigger enable */
#define GPTIMER_ADCTL_ADT2UPGTEN                           BIT(14)                           /*!< the ADTCV2[15:0] comparison match (count up only) generate trigger enable */
#define GPTIMER_ADCTL_ADT2DWGTEN                           BIT(15)                           /*!< the ADTCV2[15:0] comparison match (count down only) generate trigger enable */
#define GPTIMER_ADCTL_ADCMS3SEL                            BIT(16)                           /*!< ADC triggers monitoring signal 3 selection */
#define GPTIMER_ADCTL_ADCMS3EN                             BIT(20)                           /*!< ADC triggers monitoring signal 3 enable */
#define GPTIMER_ADCTL_ADCMS4SEL                            BIT(24)                           /*!< ADC triggers monitoring signal 4 selection */
#define GPTIMER_ADCTL_ADCMS4EN                             BIT(28)                           /*!< ADC triggers monitoring signal 4 enable */

/* GPTIMER_ADCTRGS */
#define GPTIMER_ADCTRGS_ADCC1SKSEL                         BITS(0,1)                         /*!< the ADC skipping counter 1 skipping source selection */
#define GPTIMER_ADCTRGS_ADCC1SVAL                          BITS(4,7)                         /*!< the ADC skipping counter 1 skipping value */
#define GPTIMER_ADCTRGS_ADCC1IVAL                          BITS(8,11)                        /*!< the ADC skipping counter 1 Initial value */
#define GPTIMER_ADCTRGS_ADCC1VAL                           BITS(12,15)                       /*!< this bit-field indicates the current ADC skipping counter 1 value */
#define GPTIMER_ADCTRGS_ADCC2SKSEL                         BITS(16,17)                       /*!< the ADC skipping counter 2 skipping source selection */
#define GPTIMER_ADCTRGS_ADCC2SVAL                          BITS(20,23)                       /*!< the ADC skipping counter 2 skipping value */
#define GPTIMER_ADCTRGS_ADCC2IVAL                          BITS(24,27)                       /*!< the ADC skipping counter 2 Initial value */
#define GPTIMER_ADCTRGS_ADCC2VAL                           BITS(28,31)                       /*!< this bit-field indicates the current ADC skipping counter 2 value */

/* GPTIMER_ADDINTSCTL0 */
#define GPTIMER_ADDINTSCTL0_ADDC1SKSEL                     BITS(0,1)                         /*!< the additional interrupt skipping counter 1 skipping source selection */
#define GPTIMER_ADDINTSCTL0_ADDC1SVAL                      BITS(4,7)                         /*!< the additional interrupt skipping counter 1 skipping value */
#define GPTIMER_ADDINTSCTL0_ADDC1IVAL                      BITS(8,11)                        /*!< the additional interrupt skipping counter 1 Initial value */
#define GPTIMER_ADDINTSCTL0_ADDC1VAL                       BITS(12,15)                       /*!< this bit-field indicates the current additional interrupt skipping counter 1 value*/
#define GPTIMER_ADDINTSCTL0_ADDC2SKSEL                     BITS(16,17)                       /*!< the additional interrupt skipping counter 2 skipping source selection */
#define GPTIMER_ADDINTSCTL0_ADDC2SVAL                      BITS(20,23)                       /*!< the additional interrupt skipping counter 2 skipping source selection */
#define GPTIMER_ADDINTSCTL0_ADDC2IVAL                      BITS(24,27)                       /*!< the additional interrupt skipping counter 2 Initial value */
#define GPTIMER_ADDINTSCTL0_ADDC2VAL                       BITS(28,31)                       /*!< this bit-field indicates the current additional interrupt skipping counter 2 value */

/* GPTIMER_ADDINTSCTL1 */
#define GPTIMER_ADDINTSCTL1_CH0AISSEL                      BITS(0,2)                         /*!< the channel 0 input capture/compare match additional interrupt skipping function selection */
#define GPTIMER_ADDINTSCTL1_CH1AISSEL                      BITS(4,6)                         /*!< the channel 1 input capture/compare match additional interrupt skipping function selection */
#define GPTIMER_ADDINTSCTL1_CH0ADDAISSEL                   BITS(8,10)                        /*!< the channel 0 additional value compare match additional interrupt skipping function selection */
#define GPTIMER_ADDINTSCTL1_CH1ADDAISSEL                   BITS(12,14)                       /*!< the channel 1 additional value compare match additional interrupt skipping function selection */
#define GPTIMER_ADDINTSCTL1_UFAISSEL                       BITS(16,18)                       /*!< underflow additional interrupt skipping function selection */
#define GPTIMER_ADDINTSCTL1_OFAISSEL                       BITS(20,22)                       /*!< overflow additional interrupt skipping function selection */
#define GPTIMER_ADDINTSCTL1_ADT1AISSEL                     BITS(24,26)                       /*!< the trigger signal generated by ADTCV1[15:0] additional interrupt skipping function selectiont */
#define GPTIMER_ADDINTSCTL1_ADT2AISSEL                     BITS(28,30)                       /*!< the trigger signal generated by ADTCV2[15:0] additional interrupt skipping function selection */

/* GPTIMER_IADCTSS */
#define GPTIMER_IADCTSS_CH0INTSL                           BIT(0)                            /*!< the channel 0 input capture/compare match interrupt skipping link */
#define GPTIMER_IADCTSS_CH1INTSL                           BIT(1)                            /*!< the channel 1 input capture/compare match interrupt skipping link */
#define GPTIMER_IADCTSS_CH0AINTSL                          BIT(2)                            /*!< the channel 0 additional value compare match interrupt skipping link */
#define GPTIMER_IADCTSS_CH1AINTSL                          BIT(3)                            /*!< the channel 1 additional value compare match interrupt skipping link */
#define GPTIMER_IADCTSS_OUFINTSSEL                         BITS(4,5)                         /*!< overflow / underflow interrupt skip selection */
#define GPTIMER_IADCTSS_OUFINTSVAL                         BITS(8,10)                        /*!< the number of overflow / underflow interrupt skipping value */
#define GPTIMER_IADCTSS_ADT1INTSL                          BIT(12)                           /*!< the trigger signal generated by ADTCV1[15:0] interrupt skipping link */
#define GPTIMER_IADCTSS_ADT2INTSL                          BIT(13)                           /*!< the trigger signal generated by ADTCV2[15:0] interrupt skipping link */
#define GPTIMER_IADCTSS_OUFINTSC                           BITS(16,18)                       /*!< overflow / underflow interrupt skipping counter */

/* GPTIMER_CREP */
#define GPTIMER_CREP_CREP                                  BITS(0,11)                        /*!< counter repetition value */
#define GPTIMER_CREP_CNT                                   BITS(16,27)                       /*!< repeat counter current value */
#define GPTIMER_CREP_RLD                                   BIT(31)                           /*!< the repeat counter is loaded immediately */

/* GPTIMER_SYNRSTCTL */
#define GPTIMER_SYNRSTCTL_CH0RETEN                         BIT(0)                            /*!< channel 0 compare match / input capture as the other GPTIMER synchronization reset source enable */
#define GPTIMER_SYNRSTCTL_CH1RETEN                         BIT(1)                            /*!< channel 1 compare match / input capture as the other GPTIMER synchronization reset source enable */
#define GPTIMER_SYNRSTCTL_CH0ARETEN                        BIT(2)                            /*!< channel 0 additional value compare match as the other GPTIMER synchronization reset source enable */
#define GPTIMER_SYNRSTCTL_CH1ARETEN                        BIT(3)                            /*!< channel 1 additional value compare match as the other GPTIMER synchronization reset source enable */
#define GPTIMER_SYNRSTCTL_OVRETEN                          BIT(6)                            /*!< overflow as the other GPTIMER synchronization reset source enable */
#define GPTIMER_SYNRSTCTL_UNDRETEN                         BIT(7)                            /*!< underflow as the other GPTIMER synchronization reset source enable */
#define GPTIMER_SYNRSTCTL_CHSRETEN                         BIT(16)                           /*!< channel input as the other GPTIMER synchronization reset source enable */
#define GPTIMER_SYNRSTCTL_SYNCSSEL                         BIT(21)                           /*!< GPTIMER synchronization control set selection */

/* GPTIMER_DMACFG */
#define GPTIMER_DMACFG_DMATA                               BITS(0,5)                         /*!< DMA transfer access start address */
#define GPTIMER_DMACFG_DMATC                               BITS(8,13)                        /*!< DMA transfer count */

/* GPTIMER_DMATB */
#define GPTIMER_DMATB_DMATB                                BITS(0,15)                        /*!< DMA transfer buffer address */

/* GPTIMER_CFG */
#define GPTIMER_CFG_CHVSEL                                 BIT(1)                            /*!< write CHxVAL register selection */

/* constants definitions */
/* GPTIMER init parameter struct definitions */
typedef struct {
    uint32_t clock_source;                                                                   /*!< clock source */
    uint32_t clock_polarity;                                                                 /*!< clock polarity */
    uint32_t prescaler;                                                                      /*!< prescaler value */
    uint32_t alignedmode;                                                                    /*!< aligned mode */
    uint32_t counterdirection;                                                               /*!< counter direction */
    uint32_t period;                                                                         /*!< period value */
    uint32_t clockdivision;                                                                  /*!< clock division value */
    uint32_t repetitioncounter;                                                              /*!< the counter repetition value */
} gptimer_parameter_struct;

/* counter enable source parameter struct definitions */
typedef struct {
    uint32_t enable_source_eti0;                                                             /*!< eti0 as counter enable source */
    uint32_t enable_source_eti1;                                                             /*!< eti1 as counter enable source */
    uint32_t enable_source_eti2;                                                             /*!< eti2 as counter enable source */
    uint32_t enable_source_eti3;                                                             /*!< eti3 as counter enable source */
    uint32_t enable_source_ch0;                                                              /*!< channel 0 as counter enable source */
    uint32_t enable_source_ch1;                                                              /*!< channel 1 as counter enable source */
    uint32_t enable_source_evsel0;                                                           /*!< evsel0 as counter enable source */
    uint32_t enable_source_evsel1;                                                           /*!< evsel1 as counter enable source */
    uint32_t enable_source_evsel2;                                                           /*!< evsel2 as counter enable source */
    uint32_t enable_source_evsel3;                                                           /*!< evsel3 as counter enable source */
    uint32_t enable_source_evsel4;                                                           /*!< evsel4 as counter enable source */
    uint32_t enable_source_evsel5;                                                           /*!< evsel5 as counter enable source */
    uint32_t enable_source_evsel6;                                                           /*!< evsel6 as counter enable source */
    uint32_t enable_source_evsel7;                                                           /*!< evsel7 as counter enable source */
    uint32_t enable_source_software;                                                         /*!< software event as counter enable source */
} gptimer_counter_enable_source_parameter_struct;

/* counter disable source parameter struct definitions */
typedef struct {
    uint32_t disable_source_eti0;                                                            /*!< eti0 as counter disable source */
    uint32_t disable_source_eti1;                                                            /*!< eti1 as counter disable source */
    uint32_t disable_source_eti2;                                                            /*!< eti2 as counter disable source */
    uint32_t disable_source_eti3;                                                            /*!< eti3 as counter disable source */
    uint32_t disable_source_ch0;                                                             /*!< channel 0 as counter disable source */
    uint32_t disable_source_ch1;                                                             /*!< channel 1 as counter disable source */
    uint32_t disable_source_evsel0;                                                          /*!< evsel0 as counter disable source */
    uint32_t disable_source_evsel1;                                                          /*!< evsel1 as counter disable source */
    uint32_t disable_source_evsel2;                                                          /*!< evsel2 as counter disable source */
    uint32_t disable_source_evsel3;                                                          /*!< evsel3 as counter disable source */
    uint32_t disable_source_evsel4;                                                          /*!< evsel4 as counter disable source */
    uint32_t disable_source_evsel5;                                                          /*!< evsel5 as counter disable source */
    uint32_t disable_source_evsel6;                                                          /*!< evsel6 as counter disable source */
    uint32_t disable_source_evsel7;                                                          /*!< evsel7 as counter disable source */
    uint32_t disable_source_software;                                                        /*!< software event as counter disable source */
} gptimer_counter_disable_source_parameter_struct;

/* counter reset source parameter struct definitions */
typedef struct {
    uint32_t reset_source_eti0;                                                              /*!< eti0 as counter reset source */
    uint32_t reset_source_eti1;                                                              /*!< eti1 as counter reset source */
    uint32_t reset_source_eti2;                                                              /*!< eti2 as counter reset source */
    uint32_t reset_source_eti3;                                                              /*!< eti3 as counter reset source */
    uint32_t reset_source_ch0;                                                               /*!< channel 0 as counter reset source */
    uint32_t reset_source_ch1;                                                               /*!< channel 1 as counter reset source */
    uint32_t reset_source_evsel0;                                                            /*!< evsel0 as counter reset source */
    uint32_t reset_source_evsel1;                                                            /*!< evsel1 as counter reset source */
    uint32_t reset_source_evsel2;                                                            /*!< evsel2 as counter reset source */
    uint32_t reset_source_evsel3;                                                            /*!< evsel3 as counter reset source */
    uint32_t reset_source_evsel4;                                                            /*!< evsel4 as counter reset source */
    uint32_t reset_source_evsel5;                                                            /*!< evsel5 as counter reset source */
    uint32_t reset_source_evsel6;                                                            /*!< evsel6 as counter reset source */
    uint32_t reset_source_evsel7;                                                            /*!< elcn as counter reset source */
    uint32_t reset_source_com_cap_sync;                                                      /*!< copmare, capture or synchronous reset event as counter reset source */
    uint32_t reset_source_software;                                                          /*!< software event counter reset source */
} gptimer_counter_reset_source_parameter_struct;

/* channel capture source parameter struct definitions */
typedef struct {
    uint32_t capture_source_eti0;                                                            /*!< eti0 as capture source */
    uint32_t capture_source_eti1;                                                            /*!< eti1 as capture source */
    uint32_t capture_source_eti2;                                                            /*!< eti2 as capture source */
    uint32_t capture_source_eti3;                                                            /*!< eti3 as capture source */
    uint32_t capture_source_ch0;                                                             /*!< channel 0 as capture source */
    uint32_t capture_source_ch1;                                                             /*!< channel 1 as capture source */
    uint32_t capture_source_evsel0;                                                          /*!< evsel0 as capture source */
    uint32_t capture_source_evsel1;                                                          /*!< evsel1 as capture source */
    uint32_t capture_source_evsel2;                                                          /*!< evsel2 as capture source */
    uint32_t capture_source_evsel3;                                                          /*!< evsel3 as capture source */
    uint32_t capture_source_evsel4;                                                          /*!< evsel4 as capture source */
    uint32_t capture_source_evsel5;                                                          /*!< evsel5 as capture source */
    uint32_t capture_source_evsel6;                                                          /*!< evsel6 as capture source */
    uint32_t capture_source_evsel7;                                                          /*!< evsel7 as capture source */
} gptimer_capture_source_parameter_struct;

/* counter count up source parameter struct definitions */
typedef struct {
    uint32_t up_count_source_eti0;                                                           /*!< eti0 as up count source */
    uint32_t up_count_source_eti1;                                                           /*!< eti1 as up count source */
    uint32_t up_count_source_eti2;                                                           /*!< eti2 as up count source */
    uint32_t up_count_source_eti3;                                                           /*!< eti3 as up count source */
    uint32_t up_count_source_ch0;                                                            /*!< channel 0 as up count source */
    uint32_t up_count_source_ch1;                                                            /*!< channel 1 as up count source */
    uint32_t up_count_source_evsel0;                                                         /*!< evsel0 as up count source */
    uint32_t up_count_source_evsel1;                                                         /*!< evsel1 as up count source */
    uint32_t up_count_source_evsel2;                                                         /*!< evsel2 as up count source */
    uint32_t up_count_source_evsel3;                                                         /*!< evsel3 as up count source */
    uint32_t up_count_source_evsel4;                                                         /*!< evsel4 as up count source */
    uint32_t up_count_source_evsel5;                                                         /*!< evsel5 as up count source */
    uint32_t up_count_source_evsel6;                                                         /*!< evsel6 as up count source */
    uint32_t up_count_source_evsel7;                                                         /*!< evsel7 as up count source */
} gptimer_counter_up_source_parameter_struct;

/* counter count down source parameter struct definitions */
typedef struct {
    uint32_t down_count_source_eti0;                                                         /*!< eti0 as down count source */
    uint32_t down_count_source_eti1;                                                         /*!< eti1 as down count source */
    uint32_t down_count_source_eti2;                                                         /*!< eti2 as down count source */
    uint32_t down_count_source_eti3;                                                         /*!< eti3 as down count source */
    uint32_t down_count_source_ch0;                                                          /*!< channel 0 as down count source */
    uint32_t down_count_source_ch1;                                                          /*!< channel 1 as down count source */
    uint32_t down_count_source_evsel0;                                                       /*!< evsel0 as down count source */
    uint32_t down_count_source_evsel1;                                                       /*!< evsel1 as down count source */
    uint32_t down_count_source_evsel2;                                                       /*!< evsel2 as down count source */
    uint32_t down_count_source_evsel3;                                                       /*!< evsel3 as down count source */
    uint32_t down_count_source_evsel4;                                                       /*!< evsel4 as down count source */
    uint32_t down_count_source_evsel5;                                                       /*!< evsel5 as down count source */
    uint32_t down_count_source_evsel6;                                                       /*!< evsel6 as down count source */
    uint32_t down_count_source_evsel7;                                                       /*!< evsel7 as down count source */
} gptimer_counter_down_source_parameter_struct;

/* channel output parameter struct definitions */
typedef struct {
    uint32_t chxcv_up_output_level;                                                          /*!< up count chxcv match output level */
    uint32_t chxcv_down_output_level;                                                        /*!< down count chxcv match output level */
    uint32_t chxcomv_add_up_output_level;                                                    /*!< up count chxcomv_add match output level */
    uint32_t chxcomv_add_down_output_level;                                                  /*!< down count chxcomv_add match output level */
    uint32_t period_end_output_level;                                                        /*!< period end output level */
    uint32_t cnt_enable_disable_oc_en;                                                       /*!< counter start or stop output control enable */
    uint32_t cnt_enable_output_level;                                                        /*!< counter enable output initial level */
    uint32_t cnt_disable_output_level;                                                       /*!< counter disable output level */
    uint32_t output_stop_output_level;                                                       /*!< output stop output level */
    uint32_t force_duty_output_mode;                                                         /*!< force duty output mode */
    uint32_t force_duty_output_time;                                                         /*!< force duty output time */
    uint32_t force_duty_end_output_level;                                                    /*!< force duty end output level */
    uint32_t compare_period_end_priority_control;                                            /*!< compare match and period end priority control */
} gptimer_oc_parameter_struct;

/* channel complementary output output parameter struct definitions */
typedef struct {
    uint32_t complementary_mode;                                                             /*!< complementary output mode */
    uint32_t deadtime_enable;                                                                /*!< deadtime enable */
    uint32_t deadtime_mode;                                                                  /*!< deadtime mode */
    uint32_t rising_deadtime_value;                                                          /*!< rising edge deadtime value */
    uint32_t falling_deadtime_value;                                                         /*!< falling edge deadtime value */
    uint32_t rising_deadtime_shadow;                                                         /*!< rising edge deadtime shadow */
    uint32_t falling_deadtime_shadow;                                                        /*!< falling edge deadtime shadow */
} gptimer_com_oc_parameter_struct;


#define GPTIMER0_COUNT                                     BIT(0)                            /*!< GPTIMER0 counter */
#define GPTIMER1_COUNT                                     BIT(1)                            /*!< GPTIMER1 counter */

#define GPTIMER_WRITE_PROTECT_SWEN                         GPTIMER_WP_SWEWPEN                /*!< GPTIMER_SWEN register writer protect */
#define GPTIMER_WRITE_PROTECT_SWDIS                        GPTIMER_WP_SWDWPEN                /*!< GPTIMER_SWDIS register writer protect */
#define GPTIMER_WRITE_PROTECT_SWRST                        GPTIMER_WP_SWRWPEN                /*!< GPTIMER_SWRST register writer protect */
#define GPTIMER_WRITE_PROTECT_OTHER                        GPTIMER_WP_WPEN                   /*!< other register writer protect */

#define CLOCK_SOURCE_SELECT(regval)                        ((uint32_t)(BITS(24, 26) & ((uint32_t)(regval) << 24U)))
#define GPTIMER_CLOCK_SOURCE_CK_GPTIMER                    CLOCK_SOURCE_SELECT(0)            /*!< select CK_GPTIMER as clock source */
#define GPTIMER_CLOCK_SOURCE_ETI0                          CLOCK_SOURCE_SELECT(1)            /*!< select ETI0 as clock source */
#define GPTIMER_CLOCK_SOURCE_ETI1                          CLOCK_SOURCE_SELECT(2)            /*!< select ETI1 as clock source */
#define GPTIMER_CLOCK_SOURCE_ETI2                          CLOCK_SOURCE_SELECT(3)            /*!< select ETI2 as clock source */
#define GPTIMER_CLOCK_SOURCE_ETI3                          CLOCK_SOURCE_SELECT(4)            /*!< select ETI3 as clock source */

#define CLOCK_POLARITY_SELECT(regval)                      ((uint32_t)(BITS(28, 29) & ((uint32_t)(regval) << 28U)))
#define GPTIMER_CLOCK_POLARITY_RISING                      CLOCK_POLARITY_SELECT(0)          /*!< select rising edge as clock polarity */
#define GPTIMER_CLOCK_POLARITY_FALLING                     CLOCK_POLARITY_SELECT(1)          /*!< select falling edge as clock polarity */
#define GPTIMER_CLOCK_POLARITY_BOTH                        CLOCK_POLARITY_SELECT(2)          /*!< select both edge as clock polarity */

#define ETI0_TRG_EGDE(regval)                              ((uint32_t)(BITS(0, 1) & ((uint32_t)(regval) << 0U)))
#define GPTIMER_ETI0_TRG_DISABLE                           ETI0_TRG_EGDE(0)                  /*!< eti0 as trg source disable */
#define GPTIMER_ETI0_TRG_EDGE_RISING                       ETI0_TRG_EGDE(1)                  /*!< select eti0 rising edge as trg source */
#define GPTIMER_ETI0_TRG_EDGE_FALLING                      ETI0_TRG_EGDE(2)                  /*!< select eti0 falling edge as trg source */
#define GPTIMER_ETI0_TRG_EDGE_BOTH                         ETI0_TRG_EGDE(3)                  /*!< select eti0 both edge as trg source */

#define ETI1_TRG_EGDE(regval)                              ((uint32_t)(BITS(2, 3) & ((uint32_t)(regval) << 2U)))
#define GPTIMER_ETI1_TRG_DISABLE                           ETI1_TRG_EGDE(0)                  /*!< eti1 as trg source disable */
#define GPTIMER_ETI1_TRG_EDGE_RISING                       ETI1_TRG_EGDE(1)                  /*!< select eti1 rising edge as trg source */
#define GPTIMER_ETI1_TRG_EDGE_FALLING                      ETI1_TRG_EGDE(2)                  /*!< select eti1 falling edge as trg source */
#define GPTIMER_ETI1_TRG_EDGE_BOTH                         ETI1_TRG_EGDE(3)                  /*!< select eti1 both edge as trg source */

#define ETI2_TRG_EGDE(regval)                              ((uint32_t)(BITS(4, 5) & ((uint32_t)(regval) <<4U)))
#define GPTIMER_ETI2_TRG_DISABLE                           ETI2_TRG_EGDE(0)                  /*!< eti2 as trg source disable */
#define GPTIMER_ETI2_TRG_EDGE_RISING                       ETI2_TRG_EGDE(1)                  /*!< select eti2 rising edge as trg source */
#define GPTIMER_ETI2_TRG_EDGE_FALLING                      ETI2_TRG_EGDE(2)                  /*!< select eti2 falling edge as trg source */
#define GPTIMER_ETI2_TRG_EDGE_BOTH                         ETI2_TRG_EGDE(3)                  /*!< select eti2 both edge as trg source */

#define ETI3_TRG_EGDE(regval)                              ((uint32_t)(BITS(6, 7) & ((uint32_t)(regval) << 6U)))
#define GPTIMER_ETI3_TRG_DISABLE                           ETI3_TRG_EGDE(0)                  /*!< eti3 as trg source disable */
#define GPTIMER_ETI3_TRG_EDGE_RISING                       ETI3_TRG_EGDE(1)                  /*!< select eti3 rising edge as trg source */
#define GPTIMER_ETI3_TRG_EDGE_FALLING                      ETI3_TRG_EGDE(2)                  /*!< select eti3 falling edge as trg source */
#define GPTIMER_ETI3_TRG_EDGE_BOTH                         ETI3_TRG_EGDE(3)                  /*!< select eti3 both edge as trg source */

#define CH0_TRG_EGDE(regval)                               ((uint32_t)(BITS(8, 9) & ((uint32_t)(regval) << 8U)))
#define GPTIMER_CH0_TRG_DISABLE                            CH0_TRG_EGDE(0)                   /*!< channel 0 as trg source disable */
#define GPTIMER_CH0_TRG_EDGE_RISING                        CH0_TRG_EGDE(1)                   /*!< select channel 0 rising edge as trg source */
#define GPTIMER_CH0_TRG_EDGE_FALLING                       CH0_TRG_EGDE(2)                   /*!< select channel 0 falling edge as trg source */
#define GPTIMER_CH0_TRG_EDGE_BOTH                          CH0_TRG_EGDE(3)                   /*!< select channel 0 both edge as trg source */

#define CH1_TRG_EGDE(regval)                               ((uint32_t)(BITS(10, 11) & ((uint32_t)(regval) << 10U)))
#define GPTIMER_CH1_TRG_DISABLE                            CH1_TRG_EGDE(0)                   /*!< channel 1 as trg source disable */
#define GPTIMER_CH1_TRG_EDGE_RISING                        CH1_TRG_EGDE(1)                   /*!< select channel 1 rising edge as trg source */
#define GPTIMER_CH1_TRG_EDGE_FALLING                       CH1_TRG_EGDE(2)                   /*!< select channel 1 falling edge as trg source */
#define GPTIMER_CH1_TRG_EDGE_BOTH                          CH1_TRG_EGDE(3)                   /*!< select channel 1 both edge as trg source */

#define GPTIMER_EVSEL0_TRG_DISABLE                         (uint32_t)0x00000000U             /*!< EVSEL0 as trg source disable */
#define GPTIMER_EVSEL0_TRG_ENABLE                          BIT(16)                           /*!< EVSEL0 as trg source */

#define GPTIMER_EVSEL1_TRG_DISABLE                         (uint32_t)0x00000000U             /*!< EVSEL1 as trg source disable */
#define GPTIMER_EVSEL1_TRG_ENABLE                          BIT(17)                           /*!< EVSEL1 as trg source */

#define GPTIMER_EVSEL2_TRG_DISABLE                         (uint32_t)0x00000000U             /*!< EVSEL2 as trg source disable */
#define GPTIMER_EVSEL2_TRG_ENABLE                          BIT(18)                           /*!< EVSEL2 as trg source */

#define GPTIMER_EVSEL3_TRG_DISABLE                         (uint32_t)0x00000000U             /*!< EVSEL3 as trg source disable */
#define GPTIMER_EVSEL3_TRG_ENABLE                          BIT(19)                           /*!< EVSEL3 as trg source */

#define GPTIMER_EVSEL4_TRG_DISABLE                         (uint32_t)0x00000000U             /*!< EVSEL4 as trg source disable */
#define GPTIMER_EVSEL4_TRG_ENABLE                          BIT(20)                           /*!< EVSEL4 as trg source */

#define GPTIMER_EVSEL5_TRG_DISABLE                         (uint32_t)0x00000000U             /*!< EVSEL5 as trg source disable */
#define GPTIMER_EVSEL5_TRG_ENABLE                          BIT(21)                           /*!< EVSEL5 as trg source */

#define GPTIMER_EVSEL6_TRG_DISABLE                         (uint32_t)0x00000000U             /*!< EVSEL6 as trg source disable */
#define GPTIMER_EVSEL6_TRG_ENABLE                          BIT(22)                           /*!< EVSEL6 as trg source */

#define GPTIMER_EVSEL7_TRG_DISABLE                         (uint32_t)0x00000000U             /*!< EVSEL7 as trg source disable */
#define GPTIMER_EVSEL7_TRG_ENABLE                          BIT(23)                           /*!< EVSEL7 as trg source */

#define GPTIMER_SOFTWARE_TRG_DISABLE                       (uint32_t)0x00000000U             /*!< software event as trg source disable */
#define GPTIMER_SOFTWARE_TRG_ENABLE                        BIT(31)                           /*!< software event as trg source */

#define RESET_SOURCE(regval)                               ((uint32_t)(BITS(24, 26) & ((uint32_t)(regval) << 24U)))
#define GPTIMER_RESET_SOURCE_DISABLE                       RESET_SOURCE(0)                   /*!< counter reset source disable */
#define GPTIMER_RESET_SOURCE_CH1CV_CMP_CAP                 RESET_SOURCE(1)                   /*!< ch1cv compare or capture as counter reset source enable */
#define GPTIMER_RESET_SOURCE_CH0CV_CMP_CAP                 RESET_SOURCE(2)                   /*!< ch0cv compare or capture as counter reset source enable */
#define GPTIMER_RESET_SOURCE_CH1COMADD_CMP                 RESET_SOURCE(3)                   /*!< ch1comval_add compare as counter reset source enable */
#define GPTIMER_RESET_SOURCE_CH0COMADD_CMP                 RESET_SOURCE(4)                   /*!< ch0comval_add compare as counter reset source enable */
#define GPTIMER_RESET_SOURCE_SYNC_RESET                    RESET_SOURCE(5)                   /*!< sync reset as counter reset source enable */

#define COUNTER_UP_INPUT_SOURCE(regval)                    ((uint32_t)(BITS(24, 27) & ((uint32_t)(regval) << 24U)))
#define GPTIMER_COUNTER_UP_DISABLE                         COUNTER_UP_INPUT_SOURCE(0)        /*!< counter up input source disable */
#define GPTIMER_COUNTER_UP_CH0_LOW                         COUNTER_UP_INPUT_SOURCE(2)        /*!< channel 0 low as counter up input source enable */
#define GPTIMER_COUNTER_UP_CH0_HIGH                        COUNTER_UP_INPUT_SOURCE(3)        /*!< channel 0 high as counter up input source enable */
#define GPTIMER_COUNTER_UP_CH1_LOW                         COUNTER_UP_INPUT_SOURCE(4)        /*!< channel 1 low as counter up input source enable */
#define GPTIMER_COUNTER_UP_CH1_HIGH                        COUNTER_UP_INPUT_SOURCE(5)        /*!< channel 1 high as counter up input source enable */
#define GPTIMER_COUNTER_UP_ETI0_LOW                        COUNTER_UP_INPUT_SOURCE(8)        /*!< eti0 low as counter up input source enable */
#define GPTIMER_COUNTER_UP_ETI0_HIGH                       COUNTER_UP_INPUT_SOURCE(9)        /*!< eti0 high counter up input source enable */
#define GPTIMER_COUNTER_UP_ETI1_LOW                        COUNTER_UP_INPUT_SOURCE(10)       /*!< eti1 low as counter up input source enable */
#define GPTIMER_COUNTER_UP_ETI1_HIGH                       COUNTER_UP_INPUT_SOURCE(11)       /*!< eti1 high counter up input source enable */
#define GPTIMER_COUNTER_UP_ETI2_LOW                        COUNTER_UP_INPUT_SOURCE(12)       /*!< eti2 low as counter up input source enable */
#define GPTIMER_COUNTER_UP_ETI2_HIGH                       COUNTER_UP_INPUT_SOURCE(13)       /*!< eti2 high counter up input source enable */
#define GPTIMER_COUNTER_UP_ETI3_LOW                        COUNTER_UP_INPUT_SOURCE(14)       /*!< eti3 low as counter up input source enable */
#define GPTIMER_COUNTER_UP_ETI3_HIGH                       COUNTER_UP_INPUT_SOURCE(15)       /*!< eti3 high counter up input source enable */

#define COUNTER_DOWN_INPUT_SOURCE(regval)                  ((uint32_t)(BITS(24, 27) & ((uint32_t)(regval) << 24U)))
#define GPTIMER_COUNTER_DOWN_DISABLE                       COUNTER_DOWN_INPUT_SOURCE(0)      /*!< counter down input source disable */
#define GPTIMER_COUNTER_DOWN_CH0_LOW                       COUNTER_DOWN_INPUT_SOURCE(2)      /*!< channel 0 low as counter down input source enable */
#define GPTIMER_COUNTER_DOWN_CH0_HIGH                      COUNTER_DOWN_INPUT_SOURCE(3)      /*!< channel 0 high as counter down input source enable */
#define GPTIMER_COUNTER_DOWN_CH1_LOW                       COUNTER_DOWN_INPUT_SOURCE(4)      /*!< channel 1 low as counter down input source enable */
#define GPTIMER_COUNTER_DOWN_CH1_HIGH                      COUNTER_DOWN_INPUT_SOURCE(5)      /*!< channel 1 high as counter down input source enable */
#define GPTIMER_COUNTER_DOWN_ETI0_LOW                      COUNTER_DOWN_INPUT_SOURCE(8)      /*!< eti0 low as counter down input source enable */
#define GPTIMER_COUNTER_DOWN_ETI0_HIGH                     COUNTER_DOWN_INPUT_SOURCE(9)      /*!< eti0 high counter down input source enable */
#define GPTIMER_COUNTER_DOWN_ETI1_LOW                      COUNTER_DOWN_INPUT_SOURCE(10)     /*!< eti1 low as counter down input source enable */
#define GPTIMER_COUNTER_DOWN_ETI1_HIGH                     COUNTER_DOWN_INPUT_SOURCE(11)     /*!< eti1 high counter down input source enable */
#define GPTIMER_COUNTER_DOWN_ETI2_LOW                      COUNTER_DOWN_INPUT_SOURCE(12)     /*!< eti2 low as counter down input source enable */
#define GPTIMER_COUNTER_DOWN_ETI2_HIGH                     COUNTER_DOWN_INPUT_SOURCE(13)     /*!< eti2 high counter down input source enable */
#define GPTIMER_COUNTER_DOWN_ETI3_LOW                      COUNTER_DOWN_INPUT_SOURCE(14)     /*!< eti3 low as counter down input source enable */
#define GPTIMER_COUNTER_DOWN_ETI3_HIGH                     COUNTER_DOWN_INPUT_SOURCE(15)     /*!< eti3 high counter down input source enable */

/* GPTIMER interrupt enable or disable */
#define GPTIMER_INT_CH0                                    GPTIMER_DMAINTEN_CH0IE            /*!< channel 0 compare or capture interrupt */
#define GPTIMER_INT_CH1                                    GPTIMER_DMAINTEN_CH1IE            /*!< channel 1 compare or capture interrupt */
#define GPTIMER_INT_OVERFLOW                               GPTIMER_DMAINTEN_OFIE             /*!< counter overflow interrupt */
#define GPTIMER_INT_UNDERFLOW                              GPTIMER_DMAINTEN_UFIE             /*!< counter underflow interrupt */
#define GPTIMER_INT_CH0COMADD                              GPTIMER_DMAINTEN_CH0COMADDIE      /*!< channel 0 additional compare interrupt */
#define GPTIMER_INT_CH1COMADD                              GPTIMER_DMAINTEN_CH1COMADDIE      /*!< channel 1 additional compare interrupt */
#define GPTIMER_INT_RS                                     GPTIMER_DMAINTEN_RSIE             /*!< counter reset interrupt */
#define GPTIMER_INT_CREP                                   GPTIMER_DMAINTEN_RCENDIE          /*!< repetition count end interrupt */

/* GPTIMER interrupt flag */
#define GPTIMER_INT_FLAG_CH0                               GPTIMER_INT_CH0                   /*!< channel 0 compare or capture interrupt flag */
#define GPTIMER_INT_FLAG_CH1                               GPTIMER_INT_CH1                   /*!< channel 1 compare or capture interrupt flag */
#define GPTIMER_INT_FLAG_OVERFLOW                          GPTIMER_INT_OVERFLOW              /*!< counter overflow interrupt flag */
#define GPTIMER_INT_FLAG_UNDERFLOW                         GPTIMER_INT_UNDERFLOW             /*!< counter underflow interrupt flag */
#define GPTIMER_INT_FLAG_CH0COMADD                         GPTIMER_INT_CH0COMADD             /*!< channel 0 additional compare interrupt flag */
#define GPTIMER_INT_FLAG_CH1COMADD                         GPTIMER_INT_CH1COMADD             /*!< channel 1 additional compare interrupt flag */
#define GPTIMER_INT_FLAG_RS                                GPTIMER_INT_RS                    /*!< counter reset interrupt flag */
#define GPTIMER_INT_FLAG_CREP                              GPTIMER_INT_CREP                  /*!< repetition count end interrupt flag */

/* GPTIMER flag */
#define GPTIMER_FLAG_CH0                                   GPTIMER_INTF_CH0IF                /*!< channel 0 compare or capture flag */
#define GPTIMER_FLAG_CH1                                   GPTIMER_INTF_CH1IF                /*!< channel 1 compare or capture flag */
#define GPTIMER_FLAG_OVERFLOW                              GPTIMER_INTF_OFIF                 /*!< counter overflow flag */
#define GPTIMER_FLAG_UNDERFLOW                             GPTIMER_INTF_UFIF                 /*!< counter underflow flag */
#define GPTIMER_FLAG_CH0COMADD                             GPTIMER_INTF_CH0COMADDIF          /*!< channel 0 additional compare or capture flag */
#define GPTIMER_FLAG_CH1COMADD                             GPTIMER_INTF_CH1COMADDIF          /*!< channel 1 additional compare or capture flag */
#define GPTIMER_FLAG_RS                                    GPTIMER_INTF_RSIF                 /*!< counter reset flag */
#define GPTIMER_FLAG_ADT1CMU                               GPTIMER_INTF_ADT1CMUF             /*!< counter up adc ADTCV1 match flag */
#define GPTIMER_FLAG_ADT1CMD                               GPTIMER_INTF_ADT1CMDF             /*!< counter down adc ADTCV1 match flag */
#define GPTIMER_FLAG_ADT2CMU                               GPTIMER_INTF_ADT2CMUF             /*!< counter up adc ADTCV2 match flag */
#define GPTIMER_FLAG_ADT2CMD                               GPTIMER_INTF_ADT2CMDF             /*!< counter down adc ADTCV2 match flag */
#define GPTIMER_FLAG_CHHOUT                                GPTIMER_INTF_CHHOUTF              /*!< two channel both output high flag */
#define GPTIMER_FLAG_CHLOUT                                GPTIMER_INTF_CHLOUTF              /*!< two channel both output low flag */
#define GPTIMER_FLAG_RCEND                                 GPTIMER_INTF_RCENDIF              /*!< repetition count end flag */
#define GPTIMER_FLAG_DIR                                   GPTIMER_INTF_DIRF                 /*!< counter diretion flag */
#define GPTIMER_FLAG_OST                                   GPTIMER_INTF_OSTF                 /*!< output stop flag */

/* GPTIMER DMA source */
#define GPTIMER_DMA_CH0D                                   GPTIMER_DMAINTEN_CH0DEN           /*!< channel 0 capture or compare DMA request */
#define GPTIMER_DMA_CH1D                                   GPTIMER_DMAINTEN_CH1DEN           /*!< channel 1 capture or compare DMA request */
#define GPTIMER_DMA_CH0COMADD                              GPTIMER_DMAINTEN_CH0COMADDEN      /*!< channel 0 additional compare DMA request */
#define GPTIMER_DMA_CH1COMADD                              GPTIMER_DMAINTEN_CH1COMADDEN      /*!< channel 1 additional compare DMA request */
#define GPTIMER_DMA_REPED                                  GPTIMER_DMAINTEN_RCENDEN          /*!< repetition count end DMA request */
#define GPTIMER_DMA_SOURCE(regval)                         (BITS(18, 19) & ((uint32_t)(regval) << 18U))
#define GPTIMER_DMA_OVERFLOWD                              GPTIMER_DMA_SOURCE(1)             /*!< counter overflow DMA request */
#define GPTIMER_DMA_UNDERFLOWD                             GPTIMER_DMA_SOURCE(2)             /*!< counter underflow DMA request */
#define GPTIMER_DMA_OVUNFLOWD                              GPTIMER_DMA_SOURCE(3)             /*!< counter overflow/underflow DMA request */

/* DMA access base address */
#define GPTIMER_DMATA(regval)                              (BITS(0, 5) & ((uint32_t)(regval) << 0U))
#define GPTIMER_DMACFG_DMATA_WP                            GPTIMER_DMATA(0)                  /*!< DMA transfer address is GPTIMER_WP */
#define GPTIMER_DMACFG_DMATA_SWEN                          GPTIMER_DMATA(1)                  /*!< DMA transfer address is GPTIMER_SWEN */
#define GPTIMER_DMACFG_DMATA_SWDIS                         GPTIMER_DMATA(2)                  /*!< DMA transfer address is GPTIMER_SWDIS */
#define GPTIMER_DMACFG_DMATA_SWRST                         GPTIMER_DMATA(3)                  /*!< DMA transfer address is GPTIMER_SWRST */
#define GPTIMER_DMACFG_DMATA_ESSEL                         GPTIMER_DMATA(4)                  /*!< DMA transfer address is GPTIMER_ESSEL */
#define GPTIMER_DMACFG_DMATA_DSSEL                         GPTIMER_DMATA(5)                  /*!< DMA transfer address is GPTIMER_DSSEL */
#define GPTIMER_DMACFG_DMATA_RSSEL                         GPTIMER_DMATA(6)                  /*!< DMA transfer address is GPTIMER_RSSEL */
#define GPTIMER_DMACFG_DMATA_CH0CSSEL                      GPTIMER_DMATA(7)                  /*!< DMA transfer address is GPTIMER_CH0CSSEL */
#define GPTIMER_DMACFG_DMATA_CH1CSSEL                      GPTIMER_DMATA(8)                  /*!< DMA transfer address is GPTIMER_CH1CSSEL */
#define GPTIMER_DMACFG_DMATA_CTL1                          GPTIMER_DMATA(9)                  /*!< DMA transfer address is GPTIMER_CTL0 */
#define GPTIMER_DMACFG_DMATA_UPSSR                         GPTIMER_DMATA(10)                 /*!< DMA transfer address is GPTIMER_CUPEVSSEL */
#define GPTIMER_DMACFG_DMATA_DNSSR                         GPTIMER_DMATA(11)                 /*!< DMA transfer address is GPTIMER_CDNEVSSEL */
#define GPTIMER_DMACFG_DMATA_CH0CTL                        GPTIMER_DMATA(12)                 /*!< DMA transfer address is GPTIMER_CH0CTL */
#define GPTIMER_DMACFG_DMATA_CH1CTL                        GPTIMER_DMATA(13)                 /*!< DMA transfer address is GPTIMER_CH1CTL */
#define GPTIMER_DMACFG_DMATA_CHCTL                         GPTIMER_DMATA(14)                 /*!< DMA transfer address is GPTIMER_CHCTL */
#define GPTIMER_DMACFG_DMATA_DMAINTEN                      GPTIMER_DMATA(15)                 /*!< DMA transfer address is GPTIMER_DMAINTEN */
#define GPTIMER_DMACFG_DMATA_INTF                          GPTIMER_DMATA(16)                 /*!< DMA transfer address is GPTIMER_INTF */
#define GPTIMER_DMACFG_DMATA_UPSSEL                        GPTIMER_DMATA(17)                 /*!< DMA transfer address is GPTIMER_UPSSEL */
#define GPTIMER_DMACFG_DMATA_CNT                           GPTIMER_DMATA(18)                 /*!< DMA transfer address is GPTIMER_CNT */
#define GPTIMER_DMACFG_DMATA_PSC                           GPTIMER_DMATA(19)                 /*!< DMA transfer address is GPTIMER_PSC */
#define GPTIMER_DMACFG_DMATA_CAR                           GPTIMER_DMATA(20)                 /*!< DMA transfer address is GPTIMER_CAR */
#define GPTIMER_DMACFG_DMATA_CH0CV                         GPTIMER_DMATA(21)                 /*!< DMA transfer address is GPTIMER_CH0CV */
#define GPTIMER_DMACFG_DMATA_CH1CV                         GPTIMER_DMATA(22)                 /*!< DMA transfer address is GPTIMER_CH1CV */
#define GPTIMER_DMACFG_DMATA_CH0COMV_ADD                   GPTIMER_DMATA(23)                 /*!< DMA transfer address is GPTIMER_CH0COMV_ADD */
#define GPTIMER_DMACFG_DMATA_CH1COMV_ADD                   GPTIMER_DMATA(24)                 /*!< DMA transfer address is GPTIMER_CH1COMV_ADD */
#define GPTIMER_DMACFG_DMATA_DTCTL                         GPTIMER_DMATA(25)                 /*!< DMA transfer address is GPTIMER_DTCTL */
#define GPTIMER_DMACFG_DMATA_ADCTL                         GPTIMER_DMATA(26)                 /*!< DMA transfer address is GPTIMER_ADCTL */
#define GPTIMER_DMACFG_DMATA_ADCCR1                        GPTIMER_DMATA(27)                 /*!< DMA transfer address is GPTIMER_ADCCR1 */
#define GPTIMER_DMACFG_DMATA_ADCCR2                        GPTIMER_DMATA(28)                 /*!< DMA transfer address is GPTIMER_ADCCR2 */
#define GPTIMER_DMACFG_DMATA_ADCTRGS                       GPTIMER_DMATA(29)                 /*!< DMA transfer address is GPTIMER_ADCTRGS */
#define GPTIMER_DMACFG_DMATA_ADDINTSCTL0                   GPTIMER_DMATA(30)                 /*!< DMA transfer address is GPTIMER_ADDINTSCTL0 */
#define GPTIMER_DMACFG_DMATA_ADDINTSCTL1                   GPTIMER_DMATA(31)                 /*!< DMA transfer address is GPTIMER_ADDINTSCTL1 */
#define GPTIMER_DMACFG_DMATA_IADCTSS                       GPTIMER_DMATA(32)                 /*!< DMA transfer address is GPTIMER_IADCTSS */
#define GPTIMER_DMACFG_DMATA_CREP                          GPTIMER_DMATA(33)                 /*!< DMA transfer address is GPTIMER_CREP */
#define GPTIMER_DMACFG_DMATA_SYNRSTCTL                     GPTIMER_DMATA(34)                 /*!< DMA transfer address is GPTIMER_SYNRSTCTL */

/* DMA access burst length */
#define GPTIMER_DMATC(regval)                              (BITS(8, 13) & ((uint32_t)(regval) << 8U))
#define GPTIMER_DMACFG_DMATC_1TRANSFER                     GPTIMER_DMATC(0)                  /*!< DMA transfer 1 time */
#define GPTIMER_DMACFG_DMATC_2TRANSFER                     GPTIMER_DMATC(1)                  /*!< DMA transfer 2 times */
#define GPTIMER_DMACFG_DMATC_3TRANSFER                     GPTIMER_DMATC(2)                  /*!< DMA transfer 3 times */
#define GPTIMER_DMACFG_DMATC_4TRANSFER                     GPTIMER_DMATC(3)                  /*!< DMA transfer 4 times */
#define GPTIMER_DMACFG_DMATC_5TRANSFER                     GPTIMER_DMATC(4)                  /*!< DMA transfer 5 times */
#define GPTIMER_DMACFG_DMATC_6TRANSFER                     GPTIMER_DMATC(5)                  /*!< DMA transfer 6 times */
#define GPTIMER_DMACFG_DMATC_7TRANSFER                     GPTIMER_DMATC(6)                  /*!< DMA transfer 7 times */
#define GPTIMER_DMACFG_DMATC_8TRANSFER                     GPTIMER_DMATC(7)                  /*!< DMA transfer 8 times */
#define GPTIMER_DMACFG_DMATC_9TRANSFER                     GPTIMER_DMATC(8)                  /*!< DMA transfer 9 times */
#define GPTIMER_DMACFG_DMATC_10TRANSFER                    GPTIMER_DMATC(9)                  /*!< DMA transfer 10 times */
#define GPTIMER_DMACFG_DMATC_11TRANSFER                    GPTIMER_DMATC(10)                 /*!< DMA transfer 11 times */
#define GPTIMER_DMACFG_DMATC_12TRANSFER                    GPTIMER_DMATC(11)                 /*!< DMA transfer 12 times */
#define GPTIMER_DMACFG_DMATC_13TRANSFER                    GPTIMER_DMATC(12)                 /*!< DMA transfer 13 times */
#define GPTIMER_DMACFG_DMATC_14TRANSFER                    GPTIMER_DMATC(13)                 /*!< DMA transfer 14 times */
#define GPTIMER_DMACFG_DMATC_15TRANSFER                    GPTIMER_DMATC(14)                 /*!< DMA transfer 15 times */
#define GPTIMER_DMACFG_DMATC_16TRANSFER                    GPTIMER_DMATC(15)                 /*!< DMA transfer 16 times */
#define GPTIMER_DMACFG_DMATC_17TRANSFER                    GPTIMER_DMATC(16)                 /*!< DMA transfer 17 times */
#define GPTIMER_DMACFG_DMATC_18TRANSFER                    GPTIMER_DMATC(17)                 /*!< DMA transfer 18 times */
#define GPTIMER_DMACFG_DMATC_19TRANSFER                    GPTIMER_DMATC(18)                 /*!< DMA transfer 19 times */
#define GPTIMER_DMACFG_DMATC_20TRANSFER                    GPTIMER_DMATC(19)                 /*!< DMA transfer 20 times */
#define GPTIMER_DMACFG_DMATC_21TRANSFER                    GPTIMER_DMATC(20)                 /*!< DMA transfer 21 times */
#define GPTIMER_DMACFG_DMATC_22TRANSFER                    GPTIMER_DMATC(21)                 /*!< DMA transfer 22 times */
#define GPTIMER_DMACFG_DMATC_23TRANSFER                    GPTIMER_DMATC(22)                 /*!< DMA transfer 23 times */
#define GPTIMER_DMACFG_DMATC_24TRANSFER                    GPTIMER_DMATC(23)                 /*!< DMA transfer 24 times */
#define GPTIMER_DMACFG_DMATC_25TRANSFER                    GPTIMER_DMATC(24)                 /*!< DMA transfer 25 times */
#define GPTIMER_DMACFG_DMATC_26TRANSFER                    GPTIMER_DMATC(25)                 /*!< DMA transfer 26 times */
#define GPTIMER_DMACFG_DMATC_27TRANSFER                    GPTIMER_DMATC(26)                 /*!< DMA transfer 27 times */
#define GPTIMER_DMACFG_DMATC_28TRANSFER                    GPTIMER_DMATC(27)                 /*!< DMA transfer 28 times */
#define GPTIMER_DMACFG_DMATC_29TRANSFER                    GPTIMER_DMATC(28)                 /*!< DMA transfer 29 times */
#define GPTIMER_DMACFG_DMATC_30TRANSFER                    GPTIMER_DMATC(29)                 /*!< DMA transfer 30 times */
#define GPTIMER_DMACFG_DMATC_31TRANSFER                    GPTIMER_DMATC(30)                 /*!< DMA transfer 31 times */
#define GPTIMER_DMACFG_DMATC_32TRANSFER                    GPTIMER_DMATC(31)                 /*!< DMA transfer 32 times */
#define GPTIMER_DMACFG_DMATC_33TRANSFER                    GPTIMER_DMATC(32)                 /*!< DMA transfer 33 times */
#define GPTIMER_DMACFG_DMATC_34TRANSFER                    GPTIMER_DMATC(33)                 /*!< DMA transfer 34 times */
#define GPTIMER_DMACFG_DMATC_35TRANSFER                    GPTIMER_DMATC(34)                 /*!< DMA transfer 35 times */

/* center-aligned mode selection */
#define GPTIMER_COUNTER_EDGE                               ((uint32_t)0x00000000U)           /*!< edge-aligned mode */
#define GPTIMER_COUNTER_CENTER                             GPTIMER_CTL0_CAM                  /*!< center-aligned mode */

/* count direction */
#define GPTIMER_COUNTER_UP                                 ((uint32_t)0x0000U)               /*!< counter up direction */
#define GPTIMER_COUNTER_DOWN                               ((uint32_t)GPTIMER_CTL0_DIR)      /*!< counter down direction */

/* specify division ratio between GPTIMER clock and dead-time and sampling clock */
#define GPTIMER_CTL0_CKDIVSION(regval)                     ((uint32_t)(BITS(8, 9) & ((uint32_t)(regval) << 8U)))
#define GPTIMER_CKDIV_DIV1                                 GPTIMER_CTL0_CKDIVSION(0)         /*!< clock division value is 1, fDTS=fTIMER_CK */
#define GPTIMER_CKDIV_DIV2                                 GPTIMER_CTL0_CKDIVSION(1)         /*!< clock division value is 2, fDTS= fTIMER_CK/2 */
#define GPTIMER_CKDIV_DIV4                                 GPTIMER_CTL0_CKDIVSION(2)         /*!< clock division value is 4, fDTS= fTIMER_CK/4 */

/* single pulse mode */
#define GPTIMER_SP_MODE_SINGLE                             ((uint32_t)0x00000000U)           /*!< single pulse mode */
#define GPTIMER_SP_MODE_REPETITIVE                         ((uint32_t)0x00000001U)           /*!< repetitive pulse mode */

/* repetition load mode */
#define GPTIMER_UPREP_LOAD_IMMEDIATELY                     ((uint32_t)0x00000000U)           /*!< repetition load immediately */
#define GPTIMER_UPREP_LOAD_NEXT_UPEVENT                    ((uint32_t)0x00000001U)           /*!< repetition load at next update */

/* global update source selection */
#define UPS_SEL(regval)                                    ((uint32_t)(BITS(16,17)&((uint32_t)(regval) << 16U)))
#define GPTIMER_GLOBAL_UPS_SEL_FLOW                        UPS_SEL(0)                        /*!< global update event source select counter overflow / underflow event */
#define GPTIMER_GLOBAL_UPS_SEL_OVERFLOW                    UPS_SEL(1)                        /*!< global update event source select counter overflow event */
#define GPTIMER_GLOBAL_UPS_SEL_UNDERFLOW                   UPS_SEL(2)                        /*!< global update event source select counter underflow event */

/* local update source selection */
#define REG_UPS_SEL(regval)                                ((uint32_t)(BITS(0,2)&((uint32_t)(regval) << 0U)))
#define GPTIMER_LOCAL_UPS_SEL_DISABLE                      REG_UPS_SEL(0)                    /*!< local update event source select disable*/
#define GPTIMER_LOCAL_UPS_SEL_OVERFLOW                     REG_UPS_SEL(1)                    /*!< local update event source select counter overflow event*/
#define GPTIMER_LOCAL_UPS_SEL_UNDERFLOW                    REG_UPS_SEL(2)                    /*!< local update event source select counter underflow event*/
#define GPTIMER_LOCAL_UPS_SEL_FLOW                         REG_UPS_SEL(3)                    /*!< local update event source select counter flow event*/
#define GPTIMER_LOCAL_UPS_SEL_CHCOM                        REG_UPS_SEL(4)                    /*!< local update event source select channel compare event*/

/* local update register */
#define GPTIMER_LOCAL_UP_CH0CV                             ((uint32_t)0x00000001U)           /*!< CH0CV local update */
#define GPTIMER_LOCAL_UP_CH0COMV_ADD                       ((uint32_t)0x00000002U)           /*!< CH0COMV_ADD local update */
#define GPTIMER_LOCAL_UP_CH1CV                             ((uint32_t)0x00000003U)           /*!< CH1CV local update */
#define GPTIMER_LOCAL_UP_CH1COMV_ADD                       ((uint32_t)0x00000004U)           /*!< CH1COMV_ADD local update */
#define GPTIMER_LOCAL_UP_ADCCR1                            ((uint32_t)0x00000005U)           /*!< ADC triggered comparison value 1 local update */
#define GPTIMER_LOCAL_UP_ADCCR2                            ((uint32_t)0x00000006U)           /*!< ADC triggered comparison value 2 local update */
#define GPTIMER_LOCAL_UP_CAR                               ((uint32_t)0x00000007U)           /*!< car local update */
#define GPTIMER_LOCAL_UP_CH0                               ((uint32_t)0x00000008U)           /*!< channel 0 output mode local update */
#define GPTIMER_LOCAL_UP_CH1                               ((uint32_t)0x00000009U)           /*!< channel 1 output mode local update */

/* match output level selection */
#define MATCH_LEVEL_SELECT(regval)                         ((uint32_t)(BITS(0,1)&((uint32_t)(regval) << 0U)))
#define GPTIMER_MATCH_OUTPUT_KEEP                          MATCH_LEVEL_SELECT(0)             /*!< match output level keep */
#define GPTIMER_MATCH_OUTPUT_LOW                           MATCH_LEVEL_SELECT(1)             /*!< match output low level */
#define GPTIMER_MATCH_OUTPUT_HIGH                          MATCH_LEVEL_SELECT(2)             /*!< match output high level */
#define GPTIMER_MATCH_OUTPUT_TOGGLE                        MATCH_LEVEL_SELECT(3)             /*!< match output level toggle */

/* period end output level selection */
#define PERIOD_END_LEVEL_SELECT(regval)                    ((uint32_t)(BITS(16,17)&((uint32_t)(regval) << 16U)))
#define GPTIMER_PERIOD_END_OUTPUT_KEEP                     PERIOD_END_LEVEL_SELECT(0)        /*!< period end output level keep */
#define GPTIMER_PERIOD_END_OUTPUT_LOW                      PERIOD_END_LEVEL_SELECT(1)        /*!< period end output low level */
#define GPTIMER_PERIOD_END_OUTPUT_HIGH                     PERIOD_END_LEVEL_SELECT(2)        /*!< period end output high level */
#define GPTIMER_PERIOD_END_OUTPUT_TOGGLE                   PERIOD_END_LEVEL_SELECT(3)        /*!< period end output level toggle */

/* output stop output level selection */
#define OUTPUT_STOP_LEVEL_SELECT(regval)                   ((uint32_t)(BITS(21,22)&((uint32_t)(regval) << 21U)))
#define GPTIMER_OUTPUT_STOP_OUTPUT_KEEP                    OUTPUT_STOP_LEVEL_SELECT(0)       /*!< output stop output level keep */
#define GPTIMER_OUTPUT_STOP_OUTPUT_HIZ                     OUTPUT_STOP_LEVEL_SELECT(1)       /*!< output stop output Hi-Z */
#define GPTIMER_OUTPUT_STOP_OUTPUT_LOW                     OUTPUT_STOP_LEVEL_SELECT(2)       /*!< output stop output low level */
#define GPTIMER_OUTPUT_STOP_OUTPUT_HIGH                    OUTPUT_STOP_LEVEL_SELECT(3)       /*!< output stop output high level*/

/* output stop recover time select */
#define GPTIMER_OUTPUT_RECOVER_PERIOD_END                  ((uint32_t)0x00000000U)           /*!< output stop recover time is period end */
#define GPTIMER_OUTPUT_RECOVER_CREP_END                    GPTIMER_CHCTL_STORESEL            /*!< output stop recover time is crep end */

/* counter enable or disable output control */
#define GPTIMER_CNT_ENABLE_DISABLE_OC_CTL                  ((uint32_t)0x00000000U)           /*!< counter enable or disable output level is determined by CH0ENOUT bit or CH0DISOUT bit */
#define GPTIMER_CNT_ENABLE_DISABLE_OC_KEEP                 GPTIMER_CH0CTL_CH0OUT             /*!< counter enable or disable output level holding */

/* counter enable output level */
#define GPTIMER_CNT_ENABLE_OUTPUT_LOW                      ((uint32_t)0x00000000U)           /*!< counter enable output low level */
#define GPTIMER_CNT_ENABLE_OUTPUT_HIGH                     GPTIMER_CH0CTL_CH0ENOUT           /*!< counter enable output high level */

/* counter disable output level */
#define GPTIMER_CNT_DISABLE_OUTPUT_LOW                     ((uint32_t)0x00000000U)           /*!< counter disable output low level */
#define GPTIMER_CNT_DISABLE_OUTPUT_HIGH                    GPTIMER_CH0CTL_CH0DISOUT          /*!< counter disable output high level */

/* force duty output selection */
#define FORCE_DUTY_OUTPUT(regval)                          ((uint32_t)(BITS(12,13)&((uint32_t)(regval) << 12U)))
#define GPTIMER_COMPARE_DUTY_OUTPUT                        FORCE_DUTY_OUTPUT(0)              /*!< output duty by compare */
#define GPTIMER_FORCE_0_DUTY_OUTPUT                        FORCE_DUTY_OUTPUT(2)              /*!< output duty by force 0% */
#define GPTIMER_FORCE_100_DUTY_OUTPUT                      FORCE_DUTY_OUTPUT(3)              /*!< output duty by force 100% */

/* force duty end output level */
#define GPTIMER_FORCE_DUTY_END_BASE_OUTPUT_KEEP            ((uint32_t)0x00000000U)           /*!< force duty end output level keep */
#define GPTIMER_FORCE_DUTY_END_BASE_OUTPUT_COMPARE         GPTIMER_CH0CTL_CH0REDUTY          /*!< force duty end output compare level */

/* force duty output time */
#define GPTIMER_FORCE_DUTY_OUTPUT_NEXT_PERIOD              ((uint32_t)0x00000000U)           /*!< force duty output at next period */
#define GPTIMER_FORCE_DUTY_OUTPUT_IMMEDIATELY              GPTIMER_CH0CTL_CH0OUTCTL          /*!< force duty output immediately */

/* compare period end priority */
#define GPRIMER_PERIOD_END_OUTPUT_COMPARE                  ((uint32_t)0x00000000U)           /*!< period end output compare level */
#define GPRIMER_PERIOD_END_OUTPUT_KEEP                     GPTIMER_CH0CTL_CH0EFF             /*!< period end output level keep */

/* GPTIMER channel n(n=0,1) */
#define GPTIMER_CH0                                        ((uint16_t)0x0001U)               /*!< channel 0 */
#define GPTIMER_CH1                                        ((uint16_t)0x0002U)               /*!< channel 1 */

/* channel enable state */
#define GPTIMER_CHANNEL_ENABLE                             ((uint16_t)0x0001U)               /*!< channel enable */
#define GPTIMER_CHANNEL_DISABLE                            ((uint16_t)0x0000U)               /*!< channel disable */

/* channel output compare shadow enable */
#define GPTIMER_OC_SHADOW_ENABLE                           ((uint16_t)0x0001U)               /*!< channel output shadow state enable */
#define GPTIMER_OC_SHADOW_DISABLE                          ((uint16_t)0x0000U)               /*!< channel output shadow state disable */

/* channel input output select*/
#define GPTIMER_CHANNEL_OUTPUT                             ((uint32_t)0x00000000U)           /*!< channel output */
#define GPTIMER_CHANNEL_INPUT                              ((uint32_t)0x00000002U)           /*!< channel input */

/* channel input capture prescaler */
#define IC_PSC_DIV(regval)                                 ((uint32_t)(BITS(26,27)&((uint32_t)(regval) << 26U)))
#define GPTIMER_IC_PSC_DIV1                                IC_PSC_DIV(0)                     /*!< no prescaler */
#define GPTIMER_IC_PSC_DIV2                                IC_PSC_DIV(1)                     /*!< divided by 2 */
#define GPTIMER_IC_PSC_DIV4                                IC_PSC_DIV(2)                     /*!< divided by 4 */
#define GPTIMER_IC_PSC_DIV8                                IC_PSC_DIV(3)                     /*!< divided by 8 */

/* channel 1 complementary mode */
#define GPTIMER_CH1_MODE_INDEPENDENTLY                     ((uint32_t)0x00000000U)           /*!< channel 2 output mode independently */
#define GPTIMER_CH1_MODE_COMPLEMENTARY                     GPTIMER_CHCTL_CH1MSEL             /*!< channel 2 output mode complementary */

/* deadtime enable */
#define GPTIMER_DEADTIME_DISABLE                           ((uint32_t)0x00000000U)           /*!< deadtime disable */
#define GPTIMER_DEADTIME_ENABLE                            GPTIMER_CHCTL_DTEN                /*!< deadtime enable */

/* deadtime mode */
#define GPTIMER_DEADTIME_MODE_SYMMETRIC                    ((uint32_t)0x00000000U)           /*!< deadtime symmetric mode */
#define GPTIMER_DEADTIME_MODE_ASYMMETRIC                   GPTIMER_DTCTL_DTASYEN             /*!< deadtime asymmetric mode */

/* rising edge deadtime shadow */
#define GPTIMER_DT_RISING_SHADOW_DISABLE                   ((uint32_t)0x00000000U)           /*!< rising edge deadtime shadow disable */
#define GPTIMER_DT_RISING_SHADOW_ENABLE                    GPTIMER_DTCTL_REDTSEN             /*!< rising edge deadtime shadow enable */

/* falling edge deadtime shadow */
#define GPTIMER_DT_FALLING_SHADOW_DISABLE                  ((uint32_t)0x00000000U)           /*!< falling edge deadtime shadow disable */
#define GPTIMER_DT_FALLING_SHADOW_ENABLE                   GPTIMER_DTCTL_FEDTSEN             /*!< falling edge deadtime shadow enable */

/* flow skipping soucre selection */
#define FLOW_SKIP_SRC(regval)                              ((uint32_t)(BITS(4,5)&((uint32_t)(regval) << 4U)))
#define GPTIMER_FLOW_SKIP_SOURCE_NO                        FLOW_SKIP_SRC(0)                  /*!< no flow skipping */
#define GPTIMER_FLOW_SKIP_SOURCE_OVERFLOW                  FLOW_SKIP_SRC(1)                  /*!< overflow as flow skipping soucre */
#define GPTIMER_FLOW_SKIP_SOURCE_UNDERFLOW                 FLOW_SKIP_SRC(2)                  /*!< underflow as flow skipping soucre */
#define GPTIMER_FLOW_SKIP_SOURCE_FLOW                      FLOW_SKIP_SRC(3)                  /*!< overflow / underflow as flow skipping soucre */

/* interrupt skipping link register */
#define GPTIMER_SKIP_LINK_CH0CV                            GPTIMER_IADCTSS_CH0INTSL          /*!< interrupt skipping link channel 0 input capture/compare match */
#define GPTIMER_SKIP_LINK_CH1CV                            GPTIMER_IADCTSS_CH1INTSL          /*!< interrupt skipping link channel 1 input capture/compare match */
#define GPTIMER_SKIP_LINK_CH0COMV_ADD                      GPTIMER_IADCTSS_CH0AINTSL         /*!< interrupt skipping link channel 0 additional value compare match */
#define GPTIMER_SKIP_LINK_CH1COMV_ADD                      GPTIMER_IADCTSS_CH1AINTSL         /*!< interrupt skipping link channel 1 additional value compare match */
#define GPTIMER_SKIP_LINK_ADCCR1                           GPTIMER_IADCTSS_ADT1INTSL         /*!< interrupt skipping link trigger signal generated by ADTCV1[15:0] */
#define GPTIMER_SKIP_LINK_ADCCR2                           GPTIMER_IADCTSS_ADT2INTSL         /*!< interrupt skipping link trigger signal generated by ADTCV2[15:0] */

/* interrupt skipping number */
#define FLOW_SKIP_NUM(regval)                              ((uint32_t)(BITS(8,10)&((uint32_t)(regval) << 8U)))
#define GPTIMER_FLOW_SKIP_NUM_0                            FLOW_SKIP_NUM(0)                  /*!< interrupt skipping 0 */
#define GPTIMER_FLOW_SKIP_NUM_1                            FLOW_SKIP_NUM(1)                  /*!< interrupt skipping 1 */
#define GPTIMER_FLOW_SKIP_NUM_2                            FLOW_SKIP_NUM(2)                  /*!< interrupt skipping 2 */
#define GPTIMER_FLOW_SKIP_NUM_3                            FLOW_SKIP_NUM(3)                  /*!< interrupt skipping 3 */
#define GPTIMER_FLOW_SKIP_NUM_4                            FLOW_SKIP_NUM(4)                  /*!< interrupt skipping 4 */
#define GPTIMER_FLOW_SKIP_NUM_5                            FLOW_SKIP_NUM(5)                  /*!< interrupt skipping 5 */
#define GPTIMER_FLOW_SKIP_NUM_6                            FLOW_SKIP_NUM(6)                  /*!< interrupt skipping 6 */
#define GPTIMER_FLOW_SKIP_NUM_7                            FLOW_SKIP_NUM(7)                  /*!< interrupt skipping 7 */

/* GPTIMERx(x=0,1) write cc register selection */
#define GPTIMER_CHVSEL_ENABLE                              GPTIMER_CFG_CHVSEL                /*!< write CHxVAL register selection enable  */
#define GPTIMER_CHVSEL_DISABLE                             ((uint16_t)0x0000U)               /*!< write CHxVAL register selection disable */

/* GPTIMER adc_config*/
#define GPTIMER_ADC_COMPARE1                               ((uint16_t)0x0000U)               /*!< select GPTIMERx_ADCCR1 ADTCV1 */
#define GPTIMER_ADC_COMPARE2                               ((uint16_t)0x0001U)               /*!< select GPTIMERx_ADCCR2 ADTCV2 */

/* adc skipping counter */
#define GPTIMER_ADC_SKIP_COUNT1                            ((uint16_t)0x0000U)               /*!< adc skipping counter 1 */
#define GPTIMER_ADC_SKIP_COUNT2                            ((uint16_t)0x0001U)               /*!< adc skipping counter 2 */

/* adc skipping counter source */
#define ADC_SKIP_COUNT_SOURCE(regval)                      ((uint32_t)(BITS(0,1)&((uint32_t)(regval) << 0U)))
#define GPTIMER_ADC_SKIP_NO                                ADC_SKIP_COUNT_SOURCE(0)          /*!< no adc skipping counter source */
#define GPTIMER_ADC_SKIP_ADTCV1                            ADC_SKIP_COUNT_SOURCE(1)          /*!< the ADTCV1[15:0] comparison matching */
#define GPTIMER_ADC_SKIP_ADTCV2                            ADC_SKIP_COUNT_SOURCE(2)          /*!< the ADTCV2[15:0] comparison matching */
#define GPTIMER_ADC_SKIP_ADTCV1_OR_ADTCV2                  ADC_SKIP_COUNT_SOURCE(3)          /*!< the ADTCV1[15:0] or ADTCV2[15:0] comparison matching */

/* adc skipping req source selection */
#define ADC_REQ_SOURCE(regval)                             ((uint32_t)(BITS(0,2)&((uint32_t)(regval) << 0U)))
#define GPTIMER_ADC_REQ_NO                                 ADC_REQ_SOURCE(0)                 /*!< do not skipping */
#define GPTIMER_ADC_REQ_CNT1_ZERO                          ADC_REQ_SOURCE(1)                 /*!< adc req source when skipping counter 1 equal 0 */
#define GPTIMER_ADC_REQ_CNT2_ZERO                          ADC_REQ_SOURCE(2)                 /*!< adc req source when skipping counter 2 equal 0 */
#define GPTIMER_ADC_REQ_CNT1_OR_CNT2_ZERO                  ADC_REQ_SOURCE(3)                 /*!< adc req source when skipping counter 1/2 equal 0 */
#define GPTIMER_ADC_REQ_CNT1_SVAL                          ADC_REQ_SOURCE(5)                 /*!< adc req source when skipping counter 1 equal skipping value */
#define GPTIMER_ADC_REQ_CNT2_SVAL                          ADC_REQ_SOURCE(6)                 /*!< adc req source when skipping counter 2 equal skipping value */
#define GPTIMER_ADC_REQ_CNT1_OR_CNT2_SVAL                  ADC_REQ_SOURCE(7)                 /*!< adc req source when skipping counter 1/2 equal skipping value */

/* additional interrupt skipping counter */
#define GPTIMER_ADDINT_SKIP_COUNT1                         ((uint16_t)0x0000U)               /*!< additional interrupt skipping counter 1 */
#define GPTIMER_ADDINT_SKIP_COUNT2                         ((uint16_t)0x0001U)               /*!< additional interrupt skipping counter 2 */

/* additional interrupt skipping counter source */
#define ADDINT_SKIP_SOURCE(regval)                         ((uint32_t)(BITS(0,1)&((uint32_t)(regval) << 0U)))
#define GPTIMER_ADDINT_SKIP_NO                             ADDINT_SKIP_SOURCE(0)             /*!< no additional interrupt skipping counter source */
#define GPTIMER_ADDINT_SKIP_OVERFLOW                       ADDINT_SKIP_SOURCE(1)             /*!< overflow as additional skipping counter source  */
#define GPTIMER_ADDINT_SKIP_UNDERFLOW                      ADDINT_SKIP_SOURCE(2)             /*!< underflow as additional skipping counter source */
#define GPTIMER_ADDINT_SKIP_FLOW                           ADDINT_SKIP_SOURCE(3)             /*!< overflow and underflow as additional skipping counter source */

/* additional interrupt skipping req source selection */
#define ADDINT_REQ_SOURCE(regval)                          ((uint32_t)(BITS(0,2)&((uint32_t)(regval) << 0U)))
#define GPTIMER_ADDINT_REQ_NO                              ADDINT_REQ_SOURCE(0)              /*!< do not skipping */
#define GPTIMER_ADDINT_REQ_CNT1_ZERO                       ADDINT_REQ_SOURCE(1)              /*!< additional interrupt req source when skipping counter 1 equal 0 */
#define GPTIMER_ADDINT_REQ_CNT2_ZERO                       ADDINT_REQ_SOURCE(2)              /*!< additional interrupt req source when skipping counter 2 equal 0 */
#define GPTIMER_ADDINT_REQ_CNT1_OR_CNT2_ZERO               ADDINT_REQ_SOURCE(3)              /*!< additional interrupt req source when skipping counter 1/2 equal 0 */
#define GPTIMER_ADDINT_REQ_CNT1_SVAL                       ADDINT_REQ_SOURCE(5)              /*!< additional interrupt req source when skipping counter 1 equal skipping value */
#define GPTIMER_ADDINT_REQ_CNT2_SVAL                       ADDINT_REQ_SOURCE(6)              /*!< additional interrupt req source when skipping counter 2 equal skipping value */
#define GPTIMER_ADDINT_REQ_CNT1_OR_CNT2_SVAL               ADDINT_REQ_SOURCE(7)              /*!< additional interrupt req source when skipping counter 1/2 equal skipping value */

/* additional interrupt skipping event selection */
#define GPTIMER_ADDINT_SKIP_EVENT_CH0CV                    ((uint32_t)0x00000001U)           /*!< additional interrupt skipping event ch0cv */
#define GPTIMER_ADDINT_SKIP_EVENT_CH1CV                    ((uint32_t)0x00000002U)           /*!< additional interrupt skipping event ch1cv */
#define GPTIMER_ADDINT_SKIP_EVENT_CH0COMV_ADD              ((uint32_t)0x00000003U)           /*!< additional interrupt skipping event ch0comv_add */
#define GPTIMER_ADDINT_SKIP_EVENT_CH1COMV_ADD              ((uint32_t)0x00000004U)           /*!< additional interrupt skipping event ch1comv_add */
#define GPTIMER_ADDINT_SKIP_EVENT_UNDERFLOW                ((uint32_t)0x00000005U)           /*!< additional interrupt skipping event underflow */
#define GPTIMER_ADDINT_SKIP_EVENT_OVERFLOW                 ((uint32_t)0x00000006U)           /*!< additional interrupt skipping event overflow */
#define GPTIMER_ADDINT_SKIP_EVENT_ADTCV1                   ((uint32_t)0x00000007U)           /*!< additional interrupt skipping event adtcv1 */
#define GPTIMER_ADDINT_SKIP_EVENT_ADTCV2                   ((uint32_t)0x00000008U)           /*!< additional interrupt skipping event adtcv2 */

/* adc monitor signal */
#define GPTIMER_ADCSM3                                     ((uint16_t)0x0000U)               /*!< adc monitor signal 3 */
#define GPTIMER_ADCSM4                                     ((uint16_t)0x0001U)               /*!< adc monitor signal 4 */

/* adc monitor signal */
#define GPTIMER_ADSM_ADTCV1                                ((uint32_t)0x00000000U)           /*!< adc monitor signal ADTCV1 */
#define GPTIMER_ADSM_ADTCV2                                ((uint32_t)0x00000001U)           /*!< adc monitor signal ADTCV2 */

/* adc trigger signal enable */
#define GPTIMER_ADT1UEN                                    GPTIMER_ADCTL_ADT1UPGTEN          /*!< enable counter up ADTCV1[15:0] match event as adc trigger signal */
#define GPTIMER_ADT1DEN                                    GPTIMER_ADCTL_ADT1DWGTEN          /*!< enable counter down ADTCV1[15:0] match event as adc trigger signal */
#define GPTIMER_ADT2UEN                                    GPTIMER_ADCTL_ADT2UPGTEN          /*!< enable counter up ADTCV2[15:0] match event as adc trigger signal */
#define GPTIMER_ADT2DEN                                    GPTIMER_ADCTL_ADT2DWGTEN          /*!< enable counter down ADTCV2[15:0] match event as adc trigger signal */

/* output stop group selection */
#define STOP_GTOC_SELECT(regval)                           ((uint32_t)(BITS(24,25)&((uint32_t)(regval) << 24U)))
#define GPTIMER_OUTPUT_STOP_GTOC0                          STOP_GTOC_SELECT(0)               /*!< output stop GTOC0 */
#define GPTIMER_OUTPUT_STOP_GTOC1                          STOP_GTOC_SELECT(1)               /*!< output stop GTOC1 */
#define GPTIMER_OUTPUT_STOP_GTOC2                          STOP_GTOC_SELECT(2)               /*!< output stop GTOC2 */
#define GPTIMER_OUTPUT_STOP_GTOC3                          STOP_GTOC_SELECT(3)               /*!< output stop GTOC3 */

/* counter synchronization control set */
#define GPTIMER_SYNRSTCTL_SYNCSSEL_SEL(regval)            ((uint32_t)(BIT(21)&((uint32_t)(regval) << 21U)))
#define GPTIMER_SYNRSTCTL_SYNCSSEL_SET0                    GPTIMER_SYNRSTCTL_SYNCSSEL_SEL(0) /*!< synchronization control set0 */
#define GPTIMER_SYNRSTCTL_SYNCSSEL_SET1                    GPTIMER_SYNRSTCTL_SYNCSSEL_SEL(1) /*!< synchronization control set1 */

/* counter sync reset source selection */
#define GPTIMER_SYNC_RESET_CH0CV                           GPTIMER_SYNRSTCTL_CH0RETEN        /*!< ch0cv as counter sync reset source */
#define GPTIMER_SYNC_RESET_CH1CV                           GPTIMER_SYNRSTCTL_CH1RETEN        /*!< ch1cv as counter sync reset source */
#define GPTIMER_SYNC_RESET_CH0COMV_ADD                     GPTIMER_SYNRSTCTL_CH0ARETEN       /*!< ch0comval_add as counter sync reset source */
#define GPTIMER_SYNC_RESET_CH1COMV_ADD                     GPTIMER_SYNRSTCTL_CH1ARETEN       /*!< ch1comval_add as counter sync reset source */
#define GPTIMER_SYNC_RESET_OF                              GPTIMER_SYNRSTCTL_OVRETEN         /*!< overflow as counter sync reset source */
#define GPTIMER_SYNC_RESET_UF                              GPTIMER_SYNRSTCTL_UNDRETEN        /*!< underflow as counter sync reset source */
#define GPTIMER_SYNC_RESET_CH                              GPTIMER_SYNRSTCTL_CHSRETEN        /*!< channel input as counter sync reset source */

/* function declarations */
/* GPTIMER timebase */
/* deinit GPTIMER */
void gptimer_deinit(uint32_t timer_periph);
/* initialize GPTIMER init parameter struct with a default value */
void gptimer_struct_para_init(gptimer_parameter_struct *initpara);
/* initialize GPTIMER counter */
void gptimer_init(uint32_t timer_periph, gptimer_parameter_struct *initpara);
/* enable GPTIMER register write protect function */
void gptimer_register_write_protect_enable(uint32_t timer_periph, uint32_t register_protect);
/* disable GPTIMER register write protect function */
void gptimer_register_write_protect_disable(uint32_t timer_periph, uint32_t register_protect);
/* select a GPTIMER clock source */
void gptimer_clock_source_select(uint32_t timer_periph, uint32_t clock_source);
/* configure a GPTIMER clock polarity */
void gptimer_clock_polarity_config(uint32_t timer_periph, uint32_t clock_polarity);
/* software enable GPTIMER counter */
void gptimer_counter_software_enable(uint32_t timer_periph, uint32_t timer_cnt);
/* software disable GPTIMER counter */
void gptimer_counter_software_disable(uint32_t timer_periph, uint32_t timer_cnt);
/* software reset GPTIMER counter */
void gptimer_counter_software_reset(uint32_t timer_periph, uint32_t timer_cnt);
/* initialize GPTIMER counter enable source init parameter struct with a default value */
void gptimer_counter_enable_source_struct_para_init(gptimer_counter_enable_source_parameter_struct
                                                    *counter_enable_source_para);
/* config GPTIMER counter enable source */
void gptimer_counter_enable_source_config(uint32_t timer_periph,
                                          gptimer_counter_enable_source_parameter_struct *counter_enable_source_para);
/* initialize GPTIMER counter disable source init parameter struct with a default value */
void gptimer_counter_disable_source_struct_para_init(gptimer_counter_disable_source_parameter_struct
                                                     *counter_disable_source_para);
/* config GPTIMER counter disable source */
void gptimer_counter_disable_source_config(uint32_t timer_periph,
                                           gptimer_counter_disable_source_parameter_struct *counter_disable_source_para);
/* initialize GPTIMER counter reset source init parameter struct with a default value */
void gptimer_counter_reset_source_struct_para_init(gptimer_counter_reset_source_parameter_struct
                                                   *counter_reset_source_para);
/* config GPTIMER counter reset source */
void gptimer_counter_reset_source_config(uint32_t timer_periph,
                                         gptimer_counter_reset_source_parameter_struct *counter_reset_source_para);
/* initialize GPTIMER counter up source init parameter struct with a default value */
void gptimer_counter_up_source_struct_para_init(gptimer_counter_up_source_parameter_struct *counter_up_source_para);
/* config GPTIMER counter up source */
void gptimer_counter_up_source_config(uint32_t timer_periph,
                                      gptimer_counter_up_source_parameter_struct *counter_up_source_para);
/* initialize GPTIMER counter down source init parameter struct with a default value */
void gptimer_counter_down_source_struct_para_init(gptimer_counter_down_source_parameter_struct
                                                  *counter_down_source_para);
/* config GPTIMER counter down source */
void gptimer_counter_down_source_config(uint32_t timer_periph,
                                        gptimer_counter_down_source_parameter_struct *counter_down_source_para);
/* select counter up input level source */
void gptimer_counter_up_input_level_source_select(uint32_t timer_periph, uint32_t input_source);
/* select counter down input level source */
void gptimer_counter_down_input_level_source_select(uint32_t timer_periph, uint32_t input_source);

/* enable GPTIMER */
void gptimer_enable(uint32_t timer_periph);
/* disable GPTIMER */
void gptimer_disable(uint32_t timer_periph);
/* enable the auto reload shadow function */
void gptimer_auto_reload_shadow_enable(uint32_t timer_periph);
/* disable the auto reload shadow function */
void gptimer_auto_reload_shadow_disable(uint32_t timer_periph);
/* enable the update event */
void gptimer_update_event_enable(uint32_t timer_periph);
/* disable the update event */
void gptimer_update_event_disable(uint32_t timer_periph);
/* set counter alignment mode */
void gptimer_counter_alignment(uint32_t timer_periph, uint16_t aligned);
/* set counter up direction */
void gptimer_counter_up_direction(uint32_t timer_periph);
/* set counter down direction */
void gptimer_counter_down_direction(uint32_t timer_periph);
/* enable counter direction force set */
void gptimer_counter_direction_force_set_enable(uint32_t timer_periph);
/* disable counter direction force set */
void gptimer_counter_direction_force_set_disable(uint32_t timer_periph);
/* select register global update source */
void gptimer_register_global_update_source_select(uint32_t timer_periph, uint32_t source);
/* select register local update source */
void gptimer_register_local_update_source_select(uint32_t timer_periph, uint32_t reg, uint32_t source);
/* configure prescaler */
void gptimer_prescaler_config(uint32_t timer_periph, uint16_t prescaler);
/* configure update repetition register value */
void gptimer_update_repetition_value_config(uint32_t timer_periph, uint16_t repetition, uint32_t load_mode);
/* read update repetition register value */
uint16_t gptimer_update_repetition_counter_read(uint32_t timer_periph);
/* configure autoreload register value */
void gptimer_autoreload_value_config(uint32_t timer_periph, uint32_t autoreload);
/* configure counter register value */
void gptimer_counter_value_config(uint32_t timer_periph, uint32_t counter);
/* read counter value */
uint32_t gptimer_counter_read(uint32_t timer_periph);
/* read prescaler value */
uint16_t gptimer_prescaler_read(uint32_t timer_periph);
/* configure single pulse mode */
void gptimer_single_pulse_mode_config(uint32_t timer_periph, uint32_t spmode);

/* GPTIMER DMA and event */
/* enable the DMA */
void gptimer_dma_enable(uint32_t timer_periph, uint32_t dma);
/* disable the DMA */
void gptimer_dma_disable(uint32_t timer_periph, uint32_t dma);
/* configure the DMA transfer */
void gptimer_dma_transfer_config(uint32_t timer_periph, uint32_t dma_baseaddr, uint32_t dma_lenth);

/* GPTIMER channel output */
/* initialize GPTIMER channel output parameter struct with a default value */
void gptimer_channel_output_struct_para_init(gptimer_oc_parameter_struct *ocpara);
/* configure channel output mode */
void gptimer_channel_output_config(uint32_t timer_periph, uint16_t channel, gptimer_oc_parameter_struct *ocpara);
/* configure channel output force duty */
void gptimer_channel_output_force_duty_config(uint32_t timer_periph, uint16_t channel, uint32_t duty,
                                              uint32_t output_time);
/* configure channel output compare value */
void gptimer_channel_output_compare_value_config(uint32_t timer_periph, uint16_t channel, uint16_t value);
/* configure channel output additional compare value */
void gptimer_channel_output_additional_compare_value_config(uint32_t timer_periph, uint16_t channel, uint16_t value);
/* configure channel output shadow function */
void gptimer_channel_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow);
/* configure channel output additional shadow function */
void gptimer_channel_output_additional_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow);
/* configure channel output shadow function */
void gptimer_channel_output_control_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow);
/* enable two channel simultaneous output high check function */
void gptimer_two_channel_output_high_check_enable(uint32_t timer_periph);
/* disable two channel simultaneous output high check function */
void gptimer_two_channel_output_high_check_disable(uint32_t timer_periph);
/* enable two channel simultaneous output low check function */
void gptimer_two_channel_output_low_check_enable(uint32_t timer_periph);
/* disable two channel simultaneous output low check function */
void gptimer_two_channel_output_low_check_disable(uint32_t timer_periph);
/* enable counter cycle synchronization signal output */
void gptimer_period_signal_output_enable(uint32_t timer_periph);
/* disable counter cycle synchronization signal output */
void gptimer_period_signal_output_disable(uint32_t timer_periph);
/* configure stop output source */
void gptimer_stop_output_set_select(uint32_t timer_periph, uint32_t group);
/* output stop recover time select */
void gptimer_stop_output_recover_time_select(uint32_t timer_periph, uint32_t time);
/* initialize GPTIMER complementary output parameter struct with a default value*/
void gptimer_channel_complementary_output_struct_para_init(gptimer_com_oc_parameter_struct *comocpara);
/* configure GPTIMER complementary channel output function */
void gptimer_channel_complementary_output_config(uint32_t timer_periph, gptimer_com_oc_parameter_struct *comocpara);
/* configure channel input or output */
void gptimer_channel_io_direction_config(uint32_t timer_periph, uint16_t channel, uint32_t io_direction);
/* configure channel input or output enable state */
void gptimer_channel_io_state_config(uint32_t timer_periph, uint16_t channel, uint32_t state);

/* GPTIMER channel input */
/* initialize GPTIMER counter capture source init parameter struct with a default value */
void gptimer_capture_source_struct_para_init(gptimer_capture_source_parameter_struct *counter_capture_source_para);
/* config GPTIMER counter capture source */
void gptimer_capture_source_config(uint32_t timer_periph, uint16_t channel,
                                   gptimer_capture_source_parameter_struct *capture_source_para);
/* configure channel input capture filter */
void gptimer_channel_input_capture_filter_config(uint32_t timer_periph, uint32_t channel, uint32_t number);
/* configure channel input capture prescaler */
void gptimer_channel_input_capture_prescaler_config(uint32_t timer_periph, uint16_t channel, uint32_t prescaler);
/* read channel capture compare register value */
uint32_t gptimer_channel_capture_value_register_read(uint32_t timer_periph, uint16_t channel);

/* select synchronization control set */
void gptimer_counter_sync_control_select(uint32_t timer_periph, uint32_t set);
/* select counter sync reset source */
void gptimer_counter_sync_reset_source_select(uint32_t timer_periph, uint32_t source, ControlStatus newvalue);

/* GPTIMER skipping config*/
/* enable compare event produce a ADC converter trigger signal */
void gptimer_trigger_adc_compare_enable(uint32_t timer_periph, uint32_t compare_time);
/* disable compare event produce a ADC converter trigger signal */
void gptimer_trigger_adc_compare_disable(uint32_t timer_periph, uint32_t compare_time);
/* config trigger adc compare regiseter value  */
void gptimer_trigger_adc_compare_value_config(uint32_t timer_periph, uint32_t compare,  uint16_t value);
/* enable adc compare regiseter shadow function */
void gptimer_trigger_adc_compare_shadow_enable(uint32_t timer_periph, uint32_t compare);
/* disable adc compare regiseter shadow function */
void gptimer_trigger_adc_compare_shadow_disable(uint32_t timer_periph, uint32_t compare);
/* enable trigger adc adsm signal */
void gptimer_trigger_adc_adsm_enable(uint32_t timer_periph, uint32_t adsm);
/* disable trigger adc adsm signal*/
void gptimer_trigger_adc_adsm_disable(uint32_t timer_periph, uint32_t adsm);
/* select trigger adc adsm signal */
void gptimer_trigger_adc_adsm_select(uint32_t timer_periph, uint32_t adsm, uint32_t trg_source);
/* config trigger adc skipping value */
void gptimer_trigger_adc_skipping_config(uint32_t timer_periph, uint32_t skipping_count, uint32_t value, uint32_t initial_value,
                                         uint32_t skipping_source);
/* select trigger adc skipping time */
void gptimer_trigger_adc_skipping_time_select(uint32_t timer_periph, uint32_t compare,  uint32_t skipping_time);
/* read trigger adc skipping counter */
uint16_t gptimer_trigger_adc_skipping_counter_read(uint32_t timer_periph, uint32_t skipping_count);
/* config additional interrupt skipping value */
void gptimer_additional_interrupt_skipping_config(uint32_t timer_periph, uint32_t skipping_count, uint32_t value,
                                                  uint32_t initial_value, uint32_t skipping_source);
/* select additional interrupt skipping time */
void gptimer_additional_interrupt_skipping_time_select(uint32_t timer_periph, uint32_t event, uint32_t skipping_time);
/* read additional interrupt skipping counter */
uint16_t gptimer_additional_interrupt_skipping_counter_read(uint32_t timer_periph, uint32_t skipping_count);
/* select flow interrupt skipping source */
void gptimer_flow_interrupt_skipping_source_select(uint32_t timer_periph, uint32_t skipping_source);
/* enable flow interrupt skipping_link function */
void gptimer_flow_interrupt_skipping_link_enable(uint32_t timer_periph, uint32_t skipping_link_source);
/* disable flow interrupt skipping_link function */
void gptimer_flow_interrupt_skipping_link_disable(uint32_t timer_periph, uint32_t skipping_link_source);
/* configure flow interrupt repetition skipping number */
void gptimer_flow_interrupt_skipping_num_config(uint32_t timer_periph, uint32_t number);
/* read flow interrupt skipping counter value */
uint16_t gptimer_flow_interrupt_skipping_counter_read(uint32_t timer_periph);
/* configure write CHxVAL register selection */
void gptimer_write_chxval_register_config(uint32_t timer_periph, uint16_t ccsel);

/* GPTIMER interrupt and flag*/
/* get GPTIMER flags */
FlagStatus gptimer_flag_get(uint32_t timer_periph, uint32_t flag);
/* clear GPTIMER flags */
void gptimer_flag_clear(uint32_t timer_periph, uint32_t flag);
/* enable the GPTIMER interrupt */
void gptimer_interrupt_enable(uint32_t timer_periph, uint32_t interrupt);
/* disable the GPTIMER interrupt */
void gptimer_interrupt_disable(uint32_t timer_periph, uint32_t interrupt);
/* get GPTIMER interrupt flags */
FlagStatus gptimer_interrupt_flag_get(uint32_t timer_periph, uint32_t int_flag);
/* clear GPTIMER interrupt flags */
void gptimer_interrupt_flag_clear(uint32_t timer_periph, uint32_t int_flag);

#endif /* GD32M53X_GPTIMER_H */
