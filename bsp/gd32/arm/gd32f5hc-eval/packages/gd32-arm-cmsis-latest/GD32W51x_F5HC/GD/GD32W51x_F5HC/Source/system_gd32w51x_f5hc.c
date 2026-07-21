/*!
    \file    system_gd32w51x_f5hc.c
    \brief   CMSIS Cortex-M33 Device Peripheral Access Layer Source File for
             gd32w51x_f5hc Device Series
*/

/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 * Copyright (c) 2026, GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This file refers the CMSIS standard, some adjustments are made according to GigaDevice chips */

#include "gd32w51x_f5hc.h"

#if (defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3))
#include "partition_gd32w51x_f5hc.h"
#include "main.h"
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */

/* system frequency define */
#define __IRC16M          (IRC16M_VALUE)            /* internal 16 MHz RC oscillator frequency */
#define __HXTAL           (HXTAL_VALUE)             /* high speed crystal oscillator frequency */
#define __SYS_OSC_CLK     (__IRC16M)                /* main oscillator frequency */
#if defined (GD32F5HC)
#define __IRC48M          (IRC48M_VALUE)            /* internal 48 MHz RC oscillator frequency */
#endif

/* select a system clock by uncommenting the following line */
#if  defined (GD32F5HC)
//#define __SYSTEM_CLOCK_IRC16M                       (uint32_t)(__IRC16M)
//#define __SYSTEM_CLOCK_HXTAL                        (uint32_t)(__HXTAL)
//#define __SYSTEM_CLOCK_IRC48M                       (uint32_t)(__IRC48M)
//#define __SYSTEM_CLOCK_120M_PLLP_IRC16M             (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_120M_PLLP_HXTAL              (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_168M_PLLP_IRC16M             (uint32_t)(168000000)
//#define __SYSTEM_CLOCK_168M_PLLP_HXTAL              (uint32_t)(168000000)
//#define __SYSTEM_CLOCK_180M_PLLP_IRC16M             (uint32_t)(180000000)
//#define __SYSTEM_CLOCK_180M_PLLP_IRC48M             (uint32_t)(180000000)
//#define __SYSTEM_CLOCK_180M_PLLP_HXTAL              (uint32_t)(180000000)
//#define __SYSTEM_CLOCK_200M_PLLP_IRC16M             (uint32_t)(200000000)
//#define __SYSTEM_CLOCK_200M_PLLP_IRC48M             (uint32_t)(200000000)
#define __SYSTEM_CLOCK_200M_PLLP_HXTAL              (uint32_t)(200000000)
#else
//#define __SYSTEM_CLOCK_IRC16M                       (uint32_t)(__IRC16M)
//#define __SYSTEM_CLOCK_HXTAL                        (uint32_t)(__HXTAL)
//#define __SYSTEM_CLOCK_120M_PLLP_IRC16M             (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_120M_PLLP_HXTAL              (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_168M_PLLP_IRC16M             (uint32_t)(168000000)
//#define __SYSTEM_CLOCK_168M_PLLP_HXTAL              (uint32_t)(168000000)
//#define __SYSTEM_CLOCK_180M_PLLP_IRC16M             (uint32_t)(180000000)
#define __SYSTEM_CLOCK_180M_PLLP_HXTAL              (uint32_t)(180000000)
#endif

#define HXTALSTB_DELAY      {                                  \
                                volatile uint32_t i;           \
                                for(i=0U; i<0x2000U; i++){       \
                                }                              \
                            }

/* The following is to prevent Vcore fluctuations caused by frequency switching.
   It is strongly recommended to include it to avoid issues caused by self-removal. */
#define RCU_MODIFY_DE_2(__delay)    do{                                     \
                                        volatile uint32_t i,reg;            \
                                        if(0U != (__delay)){                   \
                                            /* Insert a software delay */   \
                                            for(i=0U; i<(__delay); i++){       \
                                            }                               \
                                            reg = RCU_CFG0;                 \
                                            reg &= ~(RCU_CFG0_AHBPSC);      \
                                            reg |= RCU_AHB_CKSYS_DIV2;      \
                                            /* AHB = SYSCLK/2 */            \
                                            RCU_CFG0 = reg;                 \
                                            /* Insert a software delay */   \
                                            for(i=0U; i<(__delay); i++){       \
                                            }                               \
                                            reg = RCU_CFG0;                 \
                                            reg &= ~(RCU_CFG0_AHBPSC);      \
                                            reg |= RCU_AHB_CKSYS_DIV4;      \
                                            /* AHB = SYSCLK/4 */            \
                                            RCU_CFG0 = reg;                 \
                                            /* Insert a software delay */   \
                                            for(i=0U; i<(__delay); i++){       \
                                            }                               \
                                        }                                   \
                                    }while(0U)

/* The following is to prevent Vcore fluctuations caused by frequency switching.
   It is strongly recommended to include it to avoid issues caused by self-removal. */
#define RCU_MODIFY_UP_1(__delay)    do{                                     \
                                        volatile uint32_t i,reg;            \
                                        if(0U != (__delay)){                \
                                            /* Insert a software delay */   \
                                            for(i=0U; i<(__delay); i++){    \
                                            }                               \
                                            reg = RCU_CFG0;                 \
                                            reg &= ~(RCU_CFG0_AHBPSC);      \
                                            reg |= RCU_AHB_CKSYS_DIV1;      \
                                            RCU_CFG0 = reg;                 \
                                            /* Insert a software delay */   \
                                            for(i=0U; i<(__delay); i++){    \
                                            }                               \
                                        }                                   \
                                    }while(0U)

#define SEL_IRC16M      0x00U
#define SEL_HXTAL       0x01U
#define SEL_PLLP        0x02U
#if defined (GD32F5HC)
#define SEL_IRC48M      0x04U
#else
#define SEL_PLLDIG      0x03U
#endif

#if (defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)) || SYS_NS
/* set the system clock frequency and declare the system clock configuration function */
#ifdef __SYSTEM_CLOCK_IRC16M
uint32_t SystemCoreClock = __SYSTEM_CLOCK_IRC16M;
static void system_clock_16m_irc16m(void);
#elif defined (__SYSTEM_CLOCK_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_HXTAL;
static void system_clock_hxtal(void);
#elif defined (__SYSTEM_CLOCK_120M_PLLP_IRC16M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLLP_IRC16M;
static void system_clock_120m_irc16m(void);
#elif defined (__SYSTEM_CLOCK_120M_PLLP_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLLP_HXTAL;
static void system_clock_120m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_168M_PLLP_IRC16M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_168M_PLLP_IRC16M;
static void system_clock_168m_irc16m(void);
#elif defined (__SYSTEM_CLOCK_168M_PLLP_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_168M_PLLP_HXTAL;
static void system_clock_168m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_180M_PLLP_IRC16M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_180M_PLLP_IRC16M;
static void system_clock_180m_irc16m(void);
#elif defined (__SYSTEM_CLOCK_180M_PLLP_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_180M_PLLP_HXTAL;
static void system_clock_180m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_IRC48M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_IRC48M;
static void system_clock_48m_irc48m(void);
#elif defined (__SYSTEM_CLOCK_180M_PLLP_IRC48M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_180M_PLLP_IRC48M;
static void system_clock_180m_irc48m(void);
#elif defined (__SYSTEM_CLOCK_200M_PLLP_IRC16M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_200M_PLLP_IRC16M;
static void system_clock_200m_irc16m(void);
#elif defined (__SYSTEM_CLOCK_200M_PLLP_IRC48M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_200M_PLLP_IRC48M;
static void system_clock_200m_irc48m(void);
#elif defined (__SYSTEM_CLOCK_200M_PLLP_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_200M_PLLP_HXTAL;
static void system_clock_200m_hxtal(void);
#endif /* __SYSTEM_CLOCK_IRC16M */

/* configure the system clock */
static void system_clock_config(void);
static void _soft_delay_(uint32_t time);

/* software delay to prevent the impact of Vcore fluctuations.
   It is strongly recommended to include it to avoid issues caused by self-removal. */
static void _soft_delay_(uint32_t time)
{
    __IO uint32_t i;
    for(i = 0U; i < time * 10U; i++) {
    }
}
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)  || SYS_NS */
/*!
    \brief      setup the microcontroller system, initialize the system
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
void SystemInit(void)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    /* configure SAU region attributes */
    sau_region_config();
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3) */

#if (defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)) || SYS_NS

    /* FPU settings */
#if (__FPU_PRESENT == 1U) && (__FPU_USED == 1U)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */

#if (defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3))
    SCB_NS->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif /* (defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)) */

#endif

    /* reset the RCU clock configuration to the default reset state */
    /* set IRC16MEN bit */
    RCU_CTL |= RCU_CTL_IRC16MEN;

#if defined (GD32F5HC)
    while(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)) {
    }
    if(RCU_SCSS_PLLP == (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
        RCU_MODIFY_DE_2(0x50U);
    }
#else
    while(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)) {
    }
    if(RCU_SCSS_PLLP == (RCU_CFG0 & RCU_CFG0_SCSS)) {
        RCU_MODIFY_DE_2(0x50U);
    }
#endif
    _soft_delay_(200U);
    /* reset RCU_CTL register */
#if defined (GD32F5HC)
    RCU_CFG0 &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    RCU_CTL &= ~(RCU_CTL_HXTALEN | RCU_CTL_CKMEN | RCU_CTL_PLLEN | RCU_CTL_RCUPRIP);
    RCU_CTL &= ~(RCU_CTL_PLLI2SEN | RCU_CTL_IRC48MEN);
    /* reset PLLCFG register */
    RCU_PLLCFG = 0x00041400U;
#else
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CTL &= ~(RCU_CTL_HXTALEN | RCU_CTL_CKMEN | RCU_CTL_PLLEN | RCU_CTL_PLLDIGEN | RCU_CTL_RFCKMEN | RCU_CTL_RCUPRIP);
    RCU_CTL &= ~(RCU_CTL_HXTALENPLL);
    RCU_CTL &= ~(RCU_CTL_PLLI2SEN | RCU_CTL_PLLDIGPU);
    RCU_CTL &= ~(RCU_CTL_HXTALENI2S);
    RCU_CTL &= ~(RCU_CTL_HXTALPU | RCU_CTL_HXTALREADY);
    RCU_CTL |= RCU_CTL_HXTALBPS;
    /* reset PLLCFG register */
    RCU_PLLCFG = 0x03000000U;
    RCU_CTL |= RCU_CTL_HXTALBPS;
#endif

    /* reset CFG0 register */
    RCU_CFG0 = 0x00009400U;
    /* reset CFG1 register */
    RCU_CFG1 = 0x00000000U;
    /* reset ADDCTL register */
    RCU_ADDCTL = 0x00000000U;
    /* reset PLL register */
    RCU_PLL = 0x00003010U;
    /* disable all interrupts */
    RCU_INT = 0x00000000U;

    /* configure the system clock source, PLL multiplier and divider factors,
       AHB/APBx prescalers and flash settings */
    system_clock_config();
    /* enable ICACHE */
    ICACHE_CTL |= ICACHE_CTL_EN;
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)  || SYS_NS */
}
/*!
    \brief      configure the system clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
#if (defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)) || SYS_NS
static void system_clock_config(void)
{
#ifdef __SYSTEM_CLOCK_IRC16M
    system_clock_16m_irc16m();
#elif defined (__SYSTEM_CLOCK_HXTAL)
    system_clock_hxtal();
#elif defined (__SYSTEM_CLOCK_120M_PLLP_IRC16M)
    system_clock_120m_irc16m();
#elif defined (__SYSTEM_CLOCK_120M_PLLP_HXTAL)
    system_clock_120m_hxtal();
#elif defined (__SYSTEM_CLOCK_168M_PLLP_IRC16M)
    system_clock_168m_irc16m();
#elif defined (__SYSTEM_CLOCK_168M_PLLP_HXTAL)
    system_clock_168m_hxtal();
#elif defined (__SYSTEM_CLOCK_180M_PLLP_IRC16M)
    system_clock_180m_irc16m();
#elif defined (__SYSTEM_CLOCK_180M_PLLP_HXTAL)
    system_clock_180m_hxtal();
#elif defined (__SYSTEM_CLOCK_IRC48M)
    system_clock_48m_irc48m();
#elif defined (__SYSTEM_CLOCK_180M_PLLP_IRC48M)
    system_clock_180m_irc48m();
#elif defined (__SYSTEM_CLOCK_200M_PLLP_IRC16M)
    system_clock_200m_irc16m();
#elif defined (__SYSTEM_CLOCK_200M_PLLP_IRC48M)
    system_clock_200m_irc48m();
#elif defined (__SYSTEM_CLOCK_200M_PLLP_HXTAL)
    system_clock_200m_hxtal();
#endif /* __SYSTEM_CLOCK_IRC16M */
}

#ifdef __SYSTEM_CLOCK_IRC16M
/*!
    \brief      configure the system clock to 16M by IRC16M
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_16m_irc16m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    /* enable IRC16M */
    RCU_CTL |= RCU_CTL_IRC16MEN;

    /* wait until IRC16M is stable or the startup time is longer than IRC16M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC16MSTB);
    } while((0U == stab_flag) && (IRC16M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)) {
        while(1) {
        }
    }
    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

#if defined (GD32F5HC)
    /* select IRC16M as system clock */
    RCU_CFG0 &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    RCU_CFG0 |= RCU_CKSYSSRC_IRC16M;

    /* wait until IRC16M is selected as system clock */
    while(RCU_SCSS_IRC16M != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }
#else
    /* select IRC16M as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_IRC16M;

    /* wait until IRC16M is selected as system clock */
    while(RCU_SCSS_IRC16M != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
#endif
}

#elif defined (__SYSTEM_CLOCK_IRC48M)
/*!
    \brief      configure the system clock to 48M by IRC48M
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_48m_irc48m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC48M */
    RCU_CTL |= RCU_CTL_IRC48MEN;

    /* wait until IRC48M is stable or the startup time is longer than IRC48M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC48MSTB);
    } while((0U == stab_flag) && (IRC48M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC48MSTB)) {
        while(1) {
        }
    }
    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    reg_temp = RCU_CFG0;
    /* select IRC48M as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_IRC48M;
    RCU_CFG0 = reg_temp;

    /* wait until IRC48M is selected as system clock */
    while(RCU_SCSS_IRC48M != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }
}

#elif defined (__SYSTEM_CLOCK_HXTAL)
/*!
    \brief      configure the system clock to HXTAL
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

#if defined (GD32F5HC)
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
#else
    /* power up the HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;
    HXTALSTB_DELAY
    RCU_CTL |= RCU_CTL_HXTALREADY;
#endif

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }
    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

#if defined (GD32F5HC)
    reg_temp = RCU_CFG0;
    /* select HXTAL as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_HXTAL;
    RCU_CFG0 = reg_temp;

    /* wait until HXTAL is selected as system clock */
    while(RCU_SCSS_HXTAL != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }
#else
    reg_temp = RCU_CFG0;
    /* select HXTAL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_HXTAL;
    RCU_CFG0 = reg_temp;

    /* wait until HXTAL is selected as system clock */
    while(RCU_SCSS_HXTAL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
#endif
}

#elif defined (__SYSTEM_CLOCK_120M_PLLP_IRC16M)
/*!
    \brief      configure the system clock to 120M by PLL which selects IRC16M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_120m_irc16m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC16M */
    RCU_CTL |= RCU_CTL_IRC16MEN;

    /* wait until IRC16M is stable or the startup time is longer than IRC16M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC16MSTB);
    } while((0U == stab_flag) && (IRC16M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)) {
        while(1) {
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC16M is stable */
    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

#if  defined (GD32F5HC)
    /* AHB = SYSCLK/2. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
#else
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
#endif
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* configure the main PLL, PSC = 16, PLL_N = 240, PLL_P = 2 */
    RCU_PLL = (16U | (240U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_IRC16M));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

#if defined (GD32F5HC)
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }
#else
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
#endif

#if  defined (GD32F5HC)
    /* modify AHB clock to SYSCLK */
    RCU_MODIFY_UP_1(0x50U);
#endif
}

#elif defined (__SYSTEM_CLOCK_120M_PLLP_HXTAL)
/*!
    \brief      configure the system clock to 120M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_120m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

#if defined (GD32F5HC)
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
#else
    /* power up the HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;
    HXTALSTB_DELAY
    RCU_CTL |= RCU_CTL_HXTALREADY;
#endif

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

#if  defined (GD32F5HC)
    /* AHB = SYSCLK/2. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
#else
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
#endif
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;
#if defined (GD32F5HC)
    /* configure the main PLL, PSC = 25, PLL_N = 240, PLL_P = 2 */
    RCU_PLL = (25U | (240U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_HXTAL));
#else
    /* Configure the main PLL, PSC = 40, PLL_N = 240, PLL_P = 2 */
    RCU_PLL = (40U | (240U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_HXTAL));
#endif
    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

#if defined (GD32F5HC)
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }
#else
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
#endif

#if  defined (GD32F5HC)
    /* modify AHB clock to SYSCLK */
    RCU_MODIFY_UP_1(0x50U);
#endif
}

#elif defined (__SYSTEM_CLOCK_168M_PLLP_IRC16M)
/*!
    \brief      configure the system clock to 168M by PLL which selects IRC16M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_168m_irc16m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC16M */
    RCU_CTL |= RCU_CTL_IRC16MEN;

    /* wait until IRC16M is stable or the startup time is longer than IRC16M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC16MSTB);
    } while((0U == stab_flag) && (IRC16M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)) {
        while(1) {
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC16M is stable */
    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

#if  defined (GD32F5HC)
    /* AHB = SYSCLK/2. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
#else
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
#endif
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* Configure the main PLL, PSC = 16, PLL_N = 336, PLL_P = 2 */
    RCU_PLL = (16U | (336U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_IRC16M));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

#if defined (GD32F5HC)
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }
#else
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
#endif

#if  defined (GD32F5HC)
    /* modify AHB clock to SYSCLK */
    RCU_MODIFY_UP_1(0x50U);
#endif
}

#elif defined (__SYSTEM_CLOCK_168M_PLLP_HXTAL)
/*!
    \brief      configure the system clock to 168M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_168m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

#if defined (GD32F5HC)
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
#else
    /* power up the HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;
    HXTALSTB_DELAY
    RCU_CTL |= RCU_CTL_HXTALREADY;
#endif

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

#if  defined (GD32F5HC)
    /* AHB = SYSCLK/2. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
#else
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
#endif
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;
#if defined (GD32F5HC)
    /* configure the main PLL, PSC = 25, PLL_N = 336, PLL_P = 2 */
    RCU_PLL = (25U | (336U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_HXTAL));
#else
    /* configure the main PLL, PSC = 40, PLL_N = 336, PLL_P = 2 */
    RCU_PLL = (40U | (336U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_HXTAL));
#endif
    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

#if defined (GD32F5HC)
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }
#else
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
#endif

#if  defined (GD32F5HC)
    /* modify AHB clock to SYSCLK */
    RCU_MODIFY_UP_1(0x50U);
#endif
}

#elif defined (__SYSTEM_CLOCK_180M_PLLP_IRC16M)
/*!
    \brief      configure the system clock to 180M by PLL which selects IRC16M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_180m_irc16m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC16M */
    RCU_CTL |= RCU_CTL_IRC16MEN;

    /* wait until IRC16M is stable or the startup time is longer than IRC16M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC16MSTB);
    } while((0U == stab_flag) && (IRC16M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)) {
        while(1) {
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC16M is stable */
    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

#if  defined (GD32F5HC)
    /* AHB = SYSCLK/2. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
#else
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
#endif
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* configure the main PLL, PSC = 16, PLL_N = 360, PLL_P = 2 */
    RCU_PLL = (16U | (360U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_IRC16M));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

#if defined (GD32F5HC)
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }
#else
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
#endif

#if  defined (GD32F5HC)
    /* modify AHB clock to SYSCLK */
    RCU_MODIFY_UP_1(0x50U);
#endif
}

#elif defined (__SYSTEM_CLOCK_200M_PLLP_IRC16M)
/*!
    \brief      configure the system clock to 200M by PLL which selects IRC16M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_200m_irc16m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC16M */
    RCU_CTL |= RCU_CTL_IRC16MEN;

    /* wait until IRC16M is stable or the startup time is longer than IRC16M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC16MSTB);
    } while((0U == stab_flag) && (IRC16M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)) {
        while(1) {
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC16M is stable */
    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

    /* AHB = SYSCLK/2. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* configure the main PLL, PSC = 16, PLL_N = 400, PLL_P = 2 */
    RCU_PLL = (16U | (400U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_IRC16M));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

#if defined (GD32F5HC)
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }
#else
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
#endif

    /* modify AHB clock to SYSCLK */
    RCU_MODIFY_UP_1(0x50U);
}

#elif defined (__SYSTEM_CLOCK_180M_PLLP_HXTAL)
/*!
    \brief      configure the system clock to 180M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_180m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;


#if defined (GD32F5HC)
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
#else
    /* power up the HXTAL */
    RCU_CTL |= RCU_CTL_HXTALPU;
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    RCU_CTL |= RCU_CTL_HXTALENPLL;
    HXTALSTB_DELAY
    RCU_CTL |= RCU_CTL_HXTALREADY;
#endif
    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

#if  defined (GD32F5HC)
    /* AHB = SYSCLK/2. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
#else
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
#endif
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;
#if defined (GD32F5HC)
    /* configure the main PLL, PSC = 25, PLL_N = 360, PLL_P = 2 */
    RCU_PLL = (25U | (360U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_HXTAL));
#else
    /* configure the main PLL, PSC = 40, PLL_N = 360, PLL_P = 2 */
    RCU_PLL = (40U | (360U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_HXTAL));
#endif
    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

#if defined (GD32F5HC)
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }
#else
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
#endif

#if  defined (GD32F5HC)
    /* modify AHB clock to SYSCLK */
    RCU_MODIFY_UP_1(0x50U);
#endif
}


#elif defined (__SYSTEM_CLOCK_200M_PLLP_HXTAL)
/*!
    \brief      configure the system clock to 200M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_200m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* HXTAL is stable */
    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

    /* AHB = SYSCLK/2. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* configure the main PLL, PSC = 25, PLL_N = 400, PLL_P = 2 */
    RCU_PLL = (25U | (400U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_HXTAL));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }

    /* modify AHB clock to SYSCLK */
    RCU_MODIFY_UP_1(0x50U);
}

#elif defined (__SYSTEM_CLOCK_180M_PLLP_IRC48M)
/*!
    \brief      configure the system clock to 180M by PLL which selects IRC48M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_180m_irc48m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC48M */
    RCU_CTL |= RCU_CTL_IRC48MEN;

    /* wait until IRC48M is stable or the startup time is longer than IRC48M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC48MSTB);
    } while((0U == stab_flag) && (IRC48M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC48MSTB)) {
        while(1) {
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC48M is stable */
    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

#if  defined (GD32F5HC)
    /* AHB = SYSCLK/2. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
#else
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
#endif
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* configure the main PLL, PSC = 48, PLL_N = 360, PLL_P = 2 */
    RCU_PLL = (48U | (360U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_IRC48M));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }

#if  defined (GD32F5HC)
    /* modify AHB clock to SYSCLK */
    RCU_MODIFY_UP_1(0x50U);
#endif
}

#elif defined (__SYSTEM_CLOCK_200M_PLLP_IRC48M)
/*!
    \brief      configure the system clock to 200M by PLL which selects IRC48M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_200m_irc48m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC48M */
    RCU_CTL |= RCU_CTL_IRC48MEN;

    /* wait until IRC48M is stable or the startup time is longer than IRC48M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC48MSTB);
    } while((0U == stab_flag) && (IRC48M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC48MSTB)) {
        while(1) {
        }
    }

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC48M is stable */
    /* reset the RCU_CFG0 AHBPSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_AHBPSC;
    /* reset the RCU_CFG0 APB1PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB1PSC;
    /* reset the RCU_CFG0 APB2PSC bits */
    RCU_CFG0 &= ~ RCU_CFG0_APB2PSC;

    /* AHB = SYSCLK/2. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/4 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV4;

    /* configure the main PLL, PSC = 48, PLL_N = 400, PLL_P = 2 */
    RCU_PLL = (48U | (400U << 6U) | (((2U >> 1U) - 1U) << 16U) |
               (RCU_PLLSRC_IRC48M));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~(RCU_CFG0_SCS | RCU_CFG0_SCS_1);
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & (RCU_CFG0_SCSS | RCU_CFG0_SCSS_1))) {
    }

    /* modify AHB clock to SYSCLK */
    RCU_MODIFY_UP_1(0x50U);
}
#endif /* __SYSTEM_CLOCK_IRC16M */

/*!
    \brief      update the SystemCoreClock with current core clock retrieved from cpu registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemCoreClockUpdate(void)
{
    uint32_t sws;
    uint32_t pllpsc, plln, pllsel, pllp, ck_src, idx, clk_exp;

    /* exponent of AHB, APB1 and APB2 clock divider */
    const uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

    sws = GET_BITS(RCU_CFG0, 2, 3);
    switch(sws) {
    /* IRC16M is selected as CK_SYS */
    case SEL_IRC16M:
        SystemCoreClock = IRC16M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        SystemCoreClock = HXTAL_VALUE;
        break;
#if defined (GD32F5HC)
    /* IRC48M is selected as CK_SYS */
    case SEL_IRC48M:
        SystemCoreClock = IRC48M_VALUE;
        break;
#endif
    /* PLLP is selected as CK_SYS */
    case SEL_PLLP:
        /* get the value of PLLPSC[5:0] */
        pllpsc = GET_BITS(RCU_PLL, 0U, 5U);
        plln = GET_BITS(RCU_PLL, 6U, 14U);
        pllp = (GET_BITS(RCU_PLL, 16U, 17U) + 1U) * 2U;
#if defined (GD32F5HC)
        /* PLL clock source selection, HXTAL or IRC16M */
        pllsel = (RCU_PLL & (RCU_PLL_PLLSEL | RCU_PLL_PLLSEL_1));
        if(RCU_PLLSRC_HXTAL == pllsel) {
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC16M == pllsel) {
            ck_src = IRC16M_VALUE;
        } else {
            ck_src = IRC48M_VALUE;
        }
#else
        /* PLL clock source selection, HXTAL or IRC16M */
        pllsel = (RCU_PLL & RCU_PLL_PLLSEL);
        if(RCU_PLLSRC_HXTAL == pllsel) {
            ck_src = HXTAL_VALUE;
        } else {
            ck_src = IRC16M_VALUE;
        }
#endif
        SystemCoreClock = ((ck_src / pllpsc) * plln) / pllp;
        break;
    /* IRC16M is selected as CK_SYS */
    default:
        SystemCoreClock = IRC16M_VALUE;
        break;
    }
    /* calculate AHB clock frequency */
    idx = GET_BITS(RCU_CFG0, 4, 7);
    clk_exp = ahb_exp[idx];
    SystemCoreClock = SystemCoreClock >> clk_exp;
}
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)  || SYS_NS */

#ifdef __FIRMWARE_VERSION_DEFINE
/*!
    \brief      get firmware version
    \param[in]  none
    \param[out] none
    \retval     firmware version
*/
uint32_t gd32w51x_f5hc_firmware_version_get(void)
{
    return (uint32_t)__gd32w51x_f5hc_STDPERIPH_VERSION;
}
#endif /* __FIRMWARE_VERSION_DEFINE */

