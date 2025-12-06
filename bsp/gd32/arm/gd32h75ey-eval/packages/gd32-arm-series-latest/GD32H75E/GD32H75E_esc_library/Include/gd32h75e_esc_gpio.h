/*!
    \file    gd32h75e_esc_gpio.h
    \brief   ESC gpio driver basic configuration

    \version 2025-01-24, V1.1.0, firmware for GD32H75E
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

#ifndef  GD32H75E_ESC_GPIO_H
#define  GD32H75E_ESC_GPIO_H

#include "gd32h75e.h"
/* ESC GPIO definitions */
#define  ESC_GPIO                        (uint32_t)0x3500                 /*!< ESC GPIO base address */

/* registers definitions */
#define  GPIO0_OMODE0                    ESC_GPIO + 0x00                  /*!< ESC GPIO Port output mode register0 register */
#define  GPIO0_OMODE1                    ESC_GPIO + 0x04                  /*!< ESC GPIO Port output mode register1 register */
#define  GPIO1_OMODE0                    ESC_GPIO + 0x08                  /*!< ESC GPIO Port output mode register2 register */
#define  GPIO1_OMODE1                    ESC_GPIO + 0x0C                  /*!< ESC GPIO Port output mode register3 register */
#define  GPIO0_PUD0                      ESC_GPIO + 0x10                  /*!< ESC GPIO Port pull-up/down register0 register */
#define  GPIO0_PUD1                      ESC_GPIO + 0x14                  /*!< ESC GPIO Port pull-up/down register1 register */
#define  GPIO1_PUD0                      ESC_GPIO + 0x18                  /*!< ESC GPIO Port pull-up/down register2 register */
#define  GPIO1_PUD1                      ESC_GPIO + 0x1C                  /*!< ESC GPIO Port pull-up/down register3 register */
#define  EXMC_CTL                        ESC_GPIO + 0x20                  /*!< ESC EXMC control register */

/* bits definitions */
/* GPIO0_OMODE0 */
#define  GPIO0_OMODE0_OM015              BITS(30,31)                       /*!< pin IO11 output mode bits */
#define  GPIO0_OMODE0_OM014              BITS(28,29)                       /*!< pin OE_EXT output mode bits */
#define  GPIO0_OMODE0_OM013              BITS(26,27)                       /*!< pin IO4 output mode bits */
#define  GPIO0_OMODE0_OM012              BITS(24,25)                       /*!< pin IO5 output mode bits */
#define  GPIO0_OMODE0_OM011              BITS(22,23)                       /*!< pin IO6 output mode bits */
#define  GPIO0_OMODE0_OM010              BITS(20,21)                       /*!< pin LATCH_IN output mode bits */
#define  GPIO0_OMODE0_OM008              BITS(16,17)                       /*!< pin WD_STATE output mode bits */
#define  GPIO0_OMODE0_OM007              BITS(14,15)                       /*!< pin IO7 output mode bits */
#define  GPIO0_OMODE0_OM006              BITS(12,13)                       /*!< pin IO8 output mode bits */
#define  GPIO0_OMODE0_OM005              BITS(10,11)                       /*!< pin EOF output mode bits */
#define  GPIO0_OMODE0_OM004              BITS(8,9)                         /*!< pin SOF output mode bits */
#define  GPIO0_OMODE0_OM002              BITS(4,5)                         /*!< pin IO18 output mode bits */
#define  GPIO0_OMODE0_OM001              BITS(2,3)                         /*!< pin IO17 output mode bits */
#define  GPIO0_OMODE0_OM000              BITS(0,1)                         /*!< pin IO16 output mode bits */

/* GPIO0_OMODE1 */
#define  GPIO0_OMODE1_OM017              BITS(2,3)                         /*!< pin IO13 output mode bits */
#define  GPIO0_OMODE1_OM016              BITS(0,1)                         /*!< pin IO12 output mode bits */

/* GPIO1_OMODE0 */
#define  GPIO1_OMODE0_OM115              BITS(30,31)                       /*!< pin LINKACTLED0 output mode bits */
#define  GPIO1_OMODE0_OM114              BITS(28,29)                       /*!< pin LINKACTLED1 output mode bits */
#define  GPIO1_OMODE0_OM113              BITS(26,27)                       /*!< pin EESIZE output mode bits */
#define  GPIO1_OMODE0_OM111              BITS(22,23)                       /*!< pin EESCL output mode bits */
#define  GPIO1_OMODE0_OM110              BITS(20,21)                       /*!< pin EESDA output mode bits */
#define  GPIO1_OMODE0_OM108              BITS(16,17)                       /*!< pin IO2 output mode bits */
#define  GPIO1_OMODE0_OM107              BITS(14,15)                       /*!< pin IO1 output mode bits */
#define  GPIO1_OMODE0_OM106              BITS(12,13)                       /*!< pin IO0 output mode bits */
#define  GPIO1_OMODE0_OM105              BITS(10,11)                       /*!< pin WD_TRIG output mode bits */
#define  GPIO1_OMODE0_OM103              BITS(6,7)                         /*!< pin IO9 output mode bits */
#define  GPIO1_OMODE0_OM102              BITS(4,5)                         /*!< pin IO15 output mode bits */
#define  GPIO1_OMODE0_OM101              BITS(2,3)                         /*!< pin IO14 output mode bits */
#define  GPIO1_OMODE0_OM100              BITS(0,1)                         /*!< pin IO10 output mode bits */

/* GPIO1_OMODE1 */
#define  GPIO1_OMODE1_OM117              BITS(2,3)                         /*!< pin OUTVALID output mode bits */
#define  GPIO1_OMODE1_OM116              BITS(0,1)                         /*!< pin IO3 output mode bits */

/* GPIO0_PUD0 */
#define  GPIO0_PUD0_PUD015               BITS(30,31)                       /*!< pin IO11 pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD014               BITS(28,29)                       /*!< pin OE_EXT pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD013               BITS(26,27)                       /*!< pin IO4 pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD012               BITS(24,25)                       /*!< pin IO5 pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD011               BITS(22,23)                       /*!< pin IO6 pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD010               BITS(20,21)                       /*!< pin LATCH_IN pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD009               BITS(18,19)                       /*!< pin SYNC1_LATCH1 pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD008               BITS(16,17)                       /*!< pin WD_STATE pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD007               BITS(14,15)                       /*!< pin IO7 pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD006               BITS(12,13)                       /*!< pin IO8 pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD005               BITS(10,11)                       /*!< pin EOF pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD004               BITS(8,9)                         /*!< pin SOF pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD002               BITS(4,5)                         /*!< pin IO18 pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD001               BITS(2,3)                         /*!< pin IO17 pull-up or pull-down bits */
#define  GPIO0_PUD0_PUD000               BITS(0,1)                         /*!< pin IO16 pull-up or pull-down bits */

/* GPIO0_PUD1 */
#define  GPIO0_PUD1_PUD017               BITS(2,3)                         /*!< pin IO13 pull-up or pull-down bits */
#define  GPIO0_PUD1_PUD016               BITS(0,1)                         /*!< pin IO12 pull-up or pull-down bits */

/* GPIO1_PUD0 */
#define  GPIO1_PUD0_PUD115               BITS(30,31)                       /*!< pin LINKACTLED0 pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD114               BITS(28,29)                       /*!< pin LINKACTLED1 pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD113               BITS(26,27)                       /*!< pin EESIZE pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD112               BITS(24,25)                       /*!< pin IRQ pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD111               BITS(22,23)                       /*!< pin EESCL pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD110               BITS(20,21)                       /*!< pin EESDA pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD109               BITS(18,19)                       /*!< pin TESTMODE pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD108               BITS(16,17)                       /*!< pin IO2 pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD107               BITS(14,15)                       /*!< pin IO1 pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD106               BITS(12,13)                       /*!< pin IO0 pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD105               BITS(10,11)                       /*!< pin WD_TRIG pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD104               BITS(8,9)                         /*!< pin SYNC0_LATCH0 pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD103               BITS(6,7)                         /*!< pin IO9 pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD102               BITS(4,5)                         /*!< pin IO15 pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD101               BITS(2,3)                         /*!< pin IO14 pull-up or pull-down bits */
#define  GPIO1_PUD0_PUD100               BITS(0,1)                         /*!< pin IO10 pull-up or pull-down bits */

/* GPIO1_PUD1 */
#define  GPIO1_PUD1_PUD117               BITS(2,3)                         /*!< pin OUTVALID pull-up or pull-down bits */
#define  GPIO1_PUD1_PUD116               BITS(0,1)                         /*!< pin IO3 pull-up or pull-down bits */

/* EXMC_CTL */
#define  EXMC_CTL_EXMCHSIZE              BITS(2,1)                         /*!< EXMC hsize bits */
#define  EXMC_CTL_EXMCTYPE               BITS(0)                           /*!< EXMC TYPE bits */

#endif /* GD32H75E_ESC_GPIO_H */