/*!
    \file    gd32h75e_esc_rcu.h
    \brief   ESC rcu driver basic configuration

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

#include "gd32h75e.h"

#ifndef  ESC_RCU_H
#define  ESC_RCU_H

/* ESC_RCU definitions */
#define  ESC_RCU                        ((uint32_t)0x3400U)

/* registers definitions */
#define  ESC_RCU_AHBEN                  (ESC_RCU + 0x00U)                        /* ESC_RCU AHB enable register */
#define  ESC_RCU_APBEN                  (ESC_RCU + 0x04U)                        /* ESC_RCU APB enable register */
#define  ESC_RCU_COREEN                 (ESC_RCU + 0x08U)                        /* ESC_RCU core enable register */
#define  ESC_RCU_CLKCFG                 (ESC_RCU + 0x0CU)                        /* ESC_RCU clock configuration register */
#define  ESC_RCU_RSTCFG                 (ESC_RCU + 0x10U)                        /* ESC_RCU reset configuration register */
#define  ESC_RCU_PLL_CFG_KEY            (ESC_RCU + 0x14U)                        /* ESC_RCU PLL configuration key register */
#define  ESC_RCU_PRSTF                  (ESC_RCU + 0x18U)                        /* ESC_RCU pin reset flag register */

/* bits definitions */
/* ESC_RCU_AHBEN */
#define ESC_RCU_AHBEN_OPBEN             BIT(0)                                   /*!< OPB clock enable */
#define ESC_RCU_AHBEN_GPIOEN            BIT(1)                                   /*!< GPIO clock enable */
#define ESC_RCU_AHBEN_EFUSEFUNEN        BIT(2)                                   /*!< EFUSE function clock enable */
#define ESC_RCU_AHBEN_EFUSEEN           BIT(3)                                   /*!< EFUSE clock enable */

/* ESC_RCU_APBEN */
#define ESC_RCU_APBEN_IRQEN             BIT(1)                                   /*!< IRQ clock enable */
#define ESC_RCU_APBEN_SYSCFGEN          BIT(2)                                   /*!< SYSCFG clock enable */
#define ESC_RCU_APBEN_PMUEN             BIT(4)                                   /*!< PMU clock enable */
#define ESC_RCU_APBEN_TIMEREN           BIT(5)                                   /*!< TIMER clock enable */
#define ESC_RCU_APBEN_TIMERFUNEN        BIT(6)                                   /*!< TIMER function clock enable */

/* ESC_RCU_COREEN */
#define ESC_RCU_COREEN_CORE25MEN        BIT(0)                                   /*!< EtherCAT core 25M clock enable */
#define ESC_RCU_COREEN_CORE50MEN        BIT(1)                                   /*!< EtherCAT core 50M clock enable */
#define ESC_RCU_COREEN_CORE100MEN       BIT(2)                                   /*!< EtherCAT core 100M clock enable */

/* ESC_RCU_CLKCFG */
#define ESC_RCU_CLKCFG_HXTALSTB         BIT(3)                                   /*!< High speed crystal oscillator (HXTAL) clock stabilization flag */
#define ESC_RCU_CLKCFG_PLLSTB           BIT(5)                                   /*!< PLL clock stabilization flag */
#define ESC_RCU_CLKCFG_PLLDIV           BITS(8,10)                               /*!< PLL clock frequency division factor */
#define ESC_RCU_CLKCFG_PLLN             BITS(16,21)                              /*!< PLL clock multiplication factor */
#define ESC_RCU_CLKCFG_PLLBWCTL         BITS(24,27)                              /*!< PLL band width control signal */

/* ESC_RCU_RSTCFG */
#define ESC_RCU_RSTCFG_DRST             BIT(0)                                   /*!< Digital reset */
#define ESC_RCU_RSTCFG_PHYARST          BIT(1)                                   /*!< Port A PHY reset */
#define ESC_RCU_RSTCFG_PHYBRST          BIT(2)                                   /*!< Port B PHY reset */
#define ESC_RCU_RSTCFG_ESCRST           BIT(6)                                   /*!< EtherCAT reset */
#define ESC_RCU_RSTCFG_PHYAREL          BIT(8)                                   /*!< Port A PHY release */
#define ESC_RCU_RSTCFG_PHYBREL          BIT(9)                                   /*!< Port B PHY release */

/* RCU_PLL_CFG_KEY */
#define ESC_RCU_PLL_CFG_KEY_PLL_CFG_KEY BIT(0)                                   /*!< PLL configuration key */

/* RCU_PLL_CFG_KEY */
#define ESC_RCU_PRSTF_PRSTC             BIT(0)                                   /*!< Pin reset flag clear */
#define ESC_RCU_PRSTF_PRSTF             BIT(1)                                   /*!< Pin reset flag */

/* constants definitions */
#define ESC_RCU_PLL_CFG_KEY_VALUE       (0x78B465A1U)                            /*!< PLL configuration key value */

#endif /* ESC_RCU_H */