/*!
    \file  system_gd32m53x.c
    \brief CMSIS Cortex-M33 Device Peripheral Access Layer Source File for
           GD32M53x Device Series
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

/*!
    \page    misra_violations MISRA-C:2004 violations

    \section [MISRA-C:2004]
             Violates MISRA C:2004 Rule-10.3 (Required) The value of a complex expression of integer type
             shall only be cast to a type that is not wider and of the same signedness as the underlying type of the expression.

    \section [MISRA-C:2004]
             Violates MISRA C:2004 Rule-10.4 (Required) The value of a complex expression of floating type
             shall only be cast to a floating type which is narrower or of the same size.
*/

#include "gd32m53x.h"

/* system frequency define */
#define __IRC32M          (IRC32M_VALUE)           /* internal 32 MHz RC oscillator frequency */
#define __HXTAL           (HXTAL_VALUE)            /* high speed crystal oscillator frequency */
#define __SYS_OSC_CLK     (__IRC32M)               /* main oscillator frequency */

#define VECT_TAB_OFFSET  (uint32_t)0x00            /* vector table base offset */

/* select a system clock by uncommenting the following line */
/* use IRC32M */
//#define __SYSTEM_CLOCK_IRC32M                    (uint32_t)(__IRC32M)
//#define __SYSTEM_CLOCK_24M_PLL_IRC32M            (uint32_t)(24000000)
//#define __SYSTEM_CLOCK_72M_PLL_IRC32M            (uint32_t)(72000000)
//#define __SYSTEM_CLOCK_120M_PLL_IRC32M           (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_180M_PLL_IRC32M           (uint32_t)(180000000)

/* use HXTAL */
//#define __SYSTEM_CLOCK_HXTAL                     (uint32_t)(__HXTAL)
//#define __SYSTEM_CLOCK_24M_PLL_HXTAL             (uint32_t)(24000000)
//#define __SYSTEM_CLOCK_72M_PLL_HXTAL             (uint32_t)(72000000)
//#define __SYSTEM_CLOCK_120M_PLL_HXTAL            (uint32_t)(120000000)
#define __SYSTEM_CLOCK_180M_PLL_HXTAL            (uint32_t)(180000000)

/* The following is to prevent Vcore fluctuations caused by frequency switching.
   It is strongly recommended to include it to avoid issues caused by self-removal. */
#define RCU_MODIFY_DE_2(__delay)  do{                                    \
                                      volatile uint32_t i,reg;           \
                                      if(0U != (__delay)){               \
                                          /* Insert a software delay */  \
                                          for(i=0U; i<(__delay); i++){   \
                                          }                              \
                                          reg = RCU_CFG0;                \
                                          reg &= ~(RCU_CFG0_AHBPSC);     \
                                          reg |= RCU_AHB_CKSYS_DIV2;     \
                                          /* AHB = SYSCLK/2 */           \
                                          RCU_CFG0 = reg;                \
                                          /* Insert a software delay */  \
                                          for(i=0U; i<(__delay); i++){   \
                                          }                              \
                                          reg = RCU_CFG0;                \
                                          reg &= ~(RCU_CFG0_AHBPSC);     \
                                          reg |= RCU_AHB_CKSYS_DIV4;     \
                                          /* AHB = SYSCLK/4 */           \
                                          RCU_CFG0 = reg;                \
                                          /* Insert a software delay */  \
                                          for(i=0U; i<(__delay); i++){   \
                                          }                              \
                                      }                                  \
                                  }while(0)

/* The following is to prevent Vcore fluctuations caused by frequency switching.
   It is strongly recommended to include it to avoid issues caused by self-removal. */
#define RCU_MODIFY_UP_2(__delay)  do{                                    \
                                      volatile uint32_t i,reg;           \
                                      if(0U != (__delay)){               \
                                          /* Insert a software delay */  \
                                          for(i=0U; i<(__delay); i++){   \
                                          }                              \
                                          reg = RCU_CFG0;                \
                                          reg &= ~(RCU_CFG0_AHBPSC);     \
                                          reg |= RCU_AHB_CKSYS_DIV2;     \
                                          /* AHB = SYSCLK/2 */           \
                                          RCU_CFG0 = reg;                \
                                          /* Insert a software delay */  \
                                          for(i=0U; i<(__delay); i++){   \
                                          }                              \
                                          reg = RCU_CFG0;                \
                                          reg &= ~(RCU_CFG0_AHBPSC);     \
                                          reg |= RCU_AHB_CKSYS_DIV1;     \
                                          /* AHB = SYSCLK/1 */           \
                                          RCU_CFG0 = reg;                \
                                      }                                  \
                                  }while(0)

#define SEL_IRC32M      0x00
#define SEL_HXTAL       0x01
#define SEL_PLL         0x02

/* set the system clock frequency and declare the system clock configuration function */
#ifdef __SYSTEM_CLOCK_IRC32M
uint32_t SystemCoreClock = __SYSTEM_CLOCK_IRC32M;
static void system_clock_32m_irc32m(void);
#elif defined (__SYSTEM_CLOCK_24M_PLL_IRC32M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_24M_PLL_IRC32M;
static void system_clock_24m_irc32m(void);
#elif defined (__SYSTEM_CLOCK_72M_PLL_IRC32M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_72M_PLL_IRC32M;
static void system_clock_72m_irc32m(void);
#elif defined (__SYSTEM_CLOCK_120M_PLL_IRC32M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLL_IRC32M;
static void system_clock_120m_irc32m(void);
#elif defined (__SYSTEM_CLOCK_180M_PLL_IRC32M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_180M_PLL_IRC32M;
static void system_clock_180m_irc32m(void);

#elif defined (__SYSTEM_CLOCK_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_HXTAL;
static void system_clock_hxtal(void);
#elif defined (__SYSTEM_CLOCK_24M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_24M_PLL_HXTAL;
static void system_clock_24m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_72M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_72M_PLL_HXTAL;
static void system_clock_72m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_120M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLL_HXTAL;
static void system_clock_120m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_180M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_180M_PLL_HXTAL;
static void system_clock_180m_hxtal(void);
#endif /* __SYSTEM_CLOCK_IRC32M */

/* configure the system clock */
static void system_clock_config(void);

/* software delay to prevent the impact of Vcore fluctuations.
   It is strongly recommended to include it to avoid issues caused by self-removal. */
static void _soft_delay_(uint32_t time);
static void _soft_delay_(uint32_t time)
{
    __IO uint32_t i;
    for(i=0U; i<time*10U; i++){
    }
}

/*!
    \brief      setup the micro-controller system, initialize the system
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemInit(void)
{
    /* FPU settings */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1U)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2) | (3UL)); /* set CP10 and CP11 Full Access Enable Floating-point Extension, CP0 Full access */
#endif
    /* open the protection */
    SYSCFG_PRCFG = 0x00000A503U;
    /* reset the RCU clock configuration to the default reset state */
    /* set IRC32MEN bit */
    RCU_CTL |= RCU_CTL_IRC32MEN;
    while(0U == (RCU_CTL & RCU_CTL_IRC32MSTB)) {
    }
    if(((RCU_CFG0 & RCU_CFG0_SCSS) == RCU_SCSS_PLL)){
        RCU_MODIFY_DE_2(0x50U);
    }
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    _soft_delay_(100U);
    /* reset HXTALEN, CKMEN, PLLEN bits */
    RCU_CTL &= ~(RCU_CTL_PLLEN | RCU_CTL_CKMEN | RCU_CTL_HXTALEN | RCU_CTL_HXTALBPS);
    /* disable all interrupts */
    RCU_INT = 0x00DD0000U;
    /* reset CFG0, CFG1, CFG2 registers */
    RCU_CFG0 = 0x001E0000U;
    RCU_CFG1 = 0x00000000U;
    RCU_CFG2 = 0x18000000U;
    /* reset HXTALEN, CKMEN, PLLEN, HXTALSCAL bits */
    RCU_CTL &= ~(RCU_CTL_PLLEN | RCU_CTL_CKMEN | RCU_CTL_HXTALEN | RCU_CTL_HXTALBPS | RCU_CTL_HXTALSCAL);

    /* configure the system clock */
    system_clock_config();

#ifdef VECT_TAB_SRAM
    nvic_vector_table_set(NVIC_VECTTAB_RAM, VECT_TAB_OFFSET);
#else
    nvic_vector_table_set(NVIC_VECTTAB_FLASH, VECT_TAB_OFFSET);
#endif
}

/*!
    \brief      configure the system clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_config(void)
{
#ifdef __SYSTEM_CLOCK_IRC32M
    system_clock_32m_irc32m();
#elif defined (__SYSTEM_CLOCK_24M_PLL_IRC32M)
    system_clock_24m_irc32m();
#elif defined (__SYSTEM_CLOCK_72M_PLL_IRC32M)
    system_clock_72m_irc32m();
#elif defined (__SYSTEM_CLOCK_120M_PLL_IRC32M)
    system_clock_120m_irc32m();
#elif defined (__SYSTEM_CLOCK_180M_PLL_IRC32M)
    system_clock_180m_irc32m();

#elif defined (__SYSTEM_CLOCK_HXTAL)
    system_clock_hxtal();
#elif defined (__SYSTEM_CLOCK_24M_PLL_HXTAL)
    system_clock_24m_hxtal();
#elif defined (__SYSTEM_CLOCK_72M_PLL_HXTAL)
    system_clock_72m_hxtal();
#elif defined (__SYSTEM_CLOCK_120M_PLL_HXTAL)
    system_clock_120m_hxtal();
#elif defined (__SYSTEM_CLOCK_180M_PLL_HXTAL)
    system_clock_180m_hxtal();
#endif /* __SYSTEM_CLOCK_IRC32M */
}

#ifdef __SYSTEM_CLOCK_IRC32M
/*!
    \brief      configure the system clock to 8M by IRC32M
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_32m_irc32m(void)
{
    static uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC32M */
    RCU_CTL |= RCU_CTL_IRC32MEN;

    /* wait until IRC32M is stable or the startup time is longer than IRC32M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC32MSTB);
    } while((0U == stab_flag) && (IRC32M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC32MSTB)) {
        while(1) {
        }
    }

    /* The WSCNT bits in the FMC_WS register needs to be configured correctly depend on the AHB clock frequency when reading the flash memory */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(1);

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    reg_temp = RCU_CFG0;
    /* select IRC32M as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_IRC32M;
    RCU_CFG0 = reg_temp;

    /* wait until IRC32M is selected as system clock */
    while(RCU_SCSS_IRC32M != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_24M_PLL_IRC32M)
/*!
    \brief      configure the system clock to 24M by PLL which selects IRC32M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_24m_irc32m(void)
{
    static uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC32M */
    RCU_CTL |= RCU_CTL_IRC32MEN;

    /* wait until IRC32M is stable or the startup time is longer than IRC32M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC32MSTB);
    } while((0U == stab_flag) && (IRC32M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC32MSTB)) {
        while(1) {
        }
    }

    /* The WSCNT bits in the FMC_WS register needs to be configured correctly depend on the AHB clock frequency when reading the flash memory */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(0);

    /* IRC32M is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* CK_PLL = (CK_IRC32M/8) * 6 = 24 MHz */
    RCU_CFG1 &= ~RCU_CFG1_PREDV;
    RCU_CFG1 |= RCU_PREDV_DIV8;

    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    RCU_CFG0 |= (RCU_PLLSRC_IRC32M | RCU_PLL_MUL6);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_72M_PLL_IRC32M)
/*!
    \brief      configure the system clock to 72M by PLL which selects IRC32M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_72m_irc32m(void)
{
    static uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC32M */
    RCU_CTL |= RCU_CTL_IRC32MEN;

    /* wait until IRC32M is stable or the startup time is longer than IRC32M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC32MSTB);
    } while((0U == stab_flag) && (IRC32M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC32MSTB)) {
        while(1) {
        }
    }

    /* The WSCNT bits in the FMC_WS register needs to be configured correctly depend on the AHB clock frequency when reading the flash memory */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(2);

    /* IRC32M is stable */
    /* AHB = SYSCLK /4 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_IRC32M/8) * 18 = 72 MHz */
    RCU_CFG1 &= ~RCU_CFG1_PREDV;
    RCU_CFG1 |= RCU_PREDV_DIV8;


    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    RCU_CFG0 |= (RCU_PLLSRC_IRC32M | RCU_PLL_MUL18);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    RCU_MODIFY_UP_2(0x50U);
}

#elif defined (__SYSTEM_CLOCK_120M_PLL_IRC32M)
/*!
    \brief      configure the system clock to 120M by PLL which selects IRC32M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_120m_irc32m(void)
{
    static uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC32M */
    RCU_CTL |= RCU_CTL_IRC32MEN;

    /* wait until IRC32M is stable or the startup time is longer than IRC32M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC32MSTB);
    } while((0U == stab_flag) && (IRC32M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC32MSTB)) {
        while(1) {
        }
    }

    /* The WSCNT bits in the FMC_WS register needs to be configured correctly depend on the AHB clock frequency when reading the flash memory */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(4);

    /* IRC32M is stable */
    /* AHB = SYSCLK/4 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_IRC32M/8) * 30 = 120 MHz */
    RCU_CFG1 &= ~RCU_CFG1_PREDV;
    RCU_CFG1 |= RCU_PREDV_DIV8;


    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    RCU_CFG0 |= (RCU_PLLSRC_IRC32M | RCU_PLL_MUL30);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    RCU_MODIFY_UP_2(0x50U);
}

#elif defined (__SYSTEM_CLOCK_180M_PLL_IRC32M)
/*!
    \brief      configure the system clock to 180M by PLL which selects IRC32M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_180m_irc32m(void)
{
    static uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC32M */
    RCU_CTL |= RCU_CTL_IRC32MEN;

    /* wait until IRC32M is stable or the startup time is longer than IRC32M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC32MSTB);
    } while((0U == stab_flag) && (IRC32M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC32MSTB)) {
        while(1) {
        }
    }

    /* The WSCNT bits in the FMC_WS register needs to be configured correctly depend on the AHB clock frequency when reading the flash memory */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(6);

    /* IRC32M is stable */
    /* AHB = SYSCLK/4 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_IRC32M/8) * 45 = 180 MHz */
    RCU_CFG1 &= ~RCU_CFG1_PREDV;
    RCU_CFG1 |= RCU_PREDV_DIV8;

    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    RCU_CFG0 |= (RCU_PLLSRC_IRC32M | RCU_PLL_MUL45);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    RCU_MODIFY_UP_2(0x50U);
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
    static uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

#if (HXTAL_VALUE > 10000000)
    /* enable HXTALSCAL: HXTAL > 10MHz*/
    RCU_CTL |= RCU_CTL_HXTALSCAL;
#endif

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

    /* The WSCNT bits in the FMC_WS register needs to be configured correctly depend on the AHB clock frequency when reading the flash memory */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(0);
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    reg_temp = RCU_CFG0;
    /* select HXTAL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_HXTAL;
    RCU_CFG0 = reg_temp;

    /* wait until HXTAL is selected as system clock */
    while(RCU_SCSS_HXTAL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_24M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 24M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_24m_hxtal(void)
{
    static uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

#if (HXTAL_VALUE > 10000000)
    /* enable HXTALSCAL: HXTAL > 10MHz*/
    RCU_CTL |= RCU_CTL_HXTALSCAL;
#endif

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

    /* The WSCNT bits in the FMC_WS register needs to be configured correctly depend on the AHB clock frequency when reading the flash memory */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(0);

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* CK_PLL = (CK_PREDIV) * 6 = 24 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    RCU_CFG0 |= (RCU_PLLSRC_HXTAL | RCU_PLL_MUL6);

    /* CK_PREDIV = (CK_HXTAL)/2 = 4 MHz */
    RCU_CFG1 &= ~(RCU_CFG1_PREDV);
    RCU_CFG1 |= (RCU_PREDV_DIV2);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_72M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 72M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_72m_hxtal(void)
{
    static uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

#if (HXTAL_VALUE > 10000000)
    /* enable HXTALSCAL: HXTAL > 10MHz*/
    RCU_CTL |= RCU_CTL_HXTALSCAL;
#endif

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

    /* The WSCNT bits in the FMC_WS register needs to be configured correctly depend on the AHB clock frequency when reading the flash memory */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(2);

    /* HXTAL is stable */
    /* AHB = SYSCLK/4 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_PREDIV) * 18 = 72 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    RCU_CFG0 |= (RCU_PLLSRC_HXTAL | RCU_PLL_MUL18);

    /* CK_PREDIV = (CK_HXTAL)/2 = 4 MHz */
    RCU_CFG1 &= ~(RCU_CFG1_PREDV);
    RCU_CFG1 |= (RCU_PREDV_DIV2);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    RCU_MODIFY_UP_2(0x50U);
}
#elif defined (__SYSTEM_CLOCK_120M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 120M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_120m_hxtal(void)
{
    static uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

#if (HXTAL_VALUE > 10000000)
    /* enable HXTALSCAL: HXTAL > 10MHz*/
    RCU_CTL |= RCU_CTL_HXTALSCAL;
#endif

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

    /* The WSCNT bits in the FMC_WS register needs to be configured correctly depend on the AHB clock frequency when reading the flash memory */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(4);

    /* HXTAL is stable */
    /* AHB = SYSCLK/4 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_PREDIV0) * 30 = 120 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    RCU_CFG0 |= (RCU_PLLSRC_HXTAL | RCU_PLL_MUL30);

    /* CK_PREDIV0 = (CK_HXTAL)/2 = 4 MHz */
    RCU_CFG1 &= ~RCU_CFG1_PREDV;
    RCU_CFG1 |= RCU_PREDV_DIV2;

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    RCU_MODIFY_UP_2(0x50U);
}

#elif defined (__SYSTEM_CLOCK_180M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 180M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_180m_hxtal(void)
{
    static uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

#if (HXTAL_VALUE > 10000000U)
    /* enable HXTALSCAL: HXTAL > 10MHz*/
    RCU_CTL |= RCU_CTL_HXTALSCAL;
#endif

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

    /* The WSCNT bits in the FMC_WS register needs to be configured correctly depend on the AHB clock frequency when reading the flash memory */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(6);

    /* HXTAL is stable */
    /* AHB = SYSCLK/4 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_PREDIV) * 45 = 180 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    RCU_CFG0 |= (RCU_PLLSRC_HXTAL | RCU_PLL_MUL45);

    /* CK_PREDIV = (CK_HXTAL)/2 = 4 MHz */
    RCU_CFG1 &= ~RCU_CFG1_PREDV;
    RCU_CFG1 |= RCU_PREDV_DIV2;

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    RCU_MODIFY_UP_2(0x50U);
}
#endif
/*!
    \brief      update the SystemCoreClock with current core clock retrieved from CPU registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemCoreClockUpdate(void)
{
    uint32_t sws;
    uint32_t pllsel, ck_src, idx, clk_exp;
    float pllmf;
    uint32_t predv;

    /* exponent of AHB, APB1 and APB2 clock divider */
    const uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

    sws = GET_BITS(RCU_CFG0, 2, 3);
    switch(sws) {
    /* IRC32M is selected as CK_SYS */
    case SEL_IRC32M:
        SystemCoreClock = IRC32M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        SystemCoreClock = HXTAL_VALUE;
        break;
    /* PLL is selected as CK_SYS */
    case SEL_PLL:
        /* PLL clock source selection, HXTAL or IRC32M */
        pllsel = (RCU_CFG0 & RCU_CFG0_PLLSEL);
        if(RCU_PLLSRC_HXTAL == pllsel) {
            ck_src = HXTAL_VALUE;/* PLL clock source is HXTAL */
        } else {
            ck_src = IRC32M_VALUE;/* PLL clock source is IRC32M */
        }
        predv = ((RCU_CFG1 & RCU_CFG1_PREDV) + 1U);
        pllmf = (float)((RCU_CFG0 & RCU_CFG0_PLLMF) >> ((uint32_t)17U));
        pllmf = (pllmf + 1.0f) / 2.0f;
        /* PLL multiplication factor */
        SystemCoreClock = (uint32_t)((float)ck_src * pllmf / (float)predv);
        break;
    /* IRC32M is selected as CK_SYS */
    default:
        SystemCoreClock = IRC32M_VALUE;
        break;
    }
    /* calculate AHB clock frequency */
    idx = GET_BITS(RCU_CFG0, 4, 7);
    clk_exp = ahb_exp[idx];
    SystemCoreClock >>= clk_exp;
}

#ifdef __FIRMWARE_VERSION_DEFINE
/*!
    \brief      get firmware version
    \param[in]  none
    \param[out] none
    \retval     firmware version
*/
uint32_t gd32m53x_firmware_version_get(void)
{
    return (uint32_t)__GD32M53X_STDPERIPH_VERSION;
}
#endif /* __FIRMWARE_VERSION_DEFINE */
