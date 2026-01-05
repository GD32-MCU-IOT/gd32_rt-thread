/*!
    \file  system_gd32l23x.c
    \brief CMSIS Cortex-M23 Device Peripheral Access Layer Source File for
           GD32L23x Device Series
*/

/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 * Copyright (c) 2025, GigaDevice Semiconductor Inc.
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

#include "gd32l23x.h"

/* system frequency define */
#define __IRC16M            (IRC16M_VALUE)            /* internal 16 MHz RC oscillator frequency */
#define __HXTAL             (HXTAL_VALUE)             /* high speed crystal oscillator frequency */
#define __IRC32K            (IRC32K_VALUE)            /*  internal 32 KHz RC oscillator frequency */
#define __SYS_OSC_CLK       (__IRC16M)                /* main oscillator frequency */

#define VECT_TAB_OFFSET  (uint32_t)0x00000000U        /* vector table base offset */

/* select a system clock by uncommenting the following line */
//#define __SYSTEM_CLOCK_8M_HXTAL              (__HXTAL)
//#define __SYSTEM_CLOCK_16M_IRC16M            (__IRC16M)
#define __SYSTEM_CLOCK_64M_PLL_HXTAL         (uint32_t)(64000000)
//#define __SYSTEM_CLOCK_64M_PLL_IRC16M        (uint32_t)(64000000)

#define HXTALSTB_DELAY          {                                 \
                                   volatile uint32_t i;           \
                                   for(i=0; i<0x2000; i++){       \
                                   }                              \
                                }

/* The following is to prevent Vcore fluctuations caused by frequency switching. 
   It is strongly recommended to include it to avoid issues caused by self-removal. */
#define RCU_MODIFY_DE_2(__delay)  do{                                     \
                                      volatile uint32_t i,reg;            \
                                      if(0 != __delay){                   \
                                          /* Insert a software delay */   \
                                          for(i=0; i<__delay; i++){       \
                                          }                               \
                                          reg = RCU_CFG0;                 \
                                          reg &= ~(RCU_CFG0_AHBPSC);     \
                                          reg |= RCU_AHB_CKSYS_DIV2;     \
                                          /* AHB = SYSCLK/2 */           \
                                          RCU_CFG0 = reg;                \
                                          /* Insert a software delay */  \
                                          for(i=0; i<__delay; i++){      \
                                          }                              \
                                          reg = RCU_CFG0;                \
                                          reg &= ~(RCU_CFG0_AHBPSC);     \
                                          reg |= RCU_AHB_CKSYS_DIV4;     \
                                          /* AHB = SYSCLK/4 */           \
                                          RCU_CFG0 = reg;                \
                                          /* Insert a software delay */  \
                                          for(i=0; i<__delay; i++){      \
                                          }                              \
                                      }                                  \
                                  }while(0)

#define SEL_IRC16M      0x00
#define SEL_HXTAL       0x01
#define SEL_PLL         0x02
#define SEL_IRC32K      0x03

/* set the system clock frequency and declare the system clock configuration function */
#ifdef __SYSTEM_CLOCK_8M_HXTAL
uint32_t SystemCoreClock = __SYSTEM_CLOCK_8M_HXTAL;
static void system_clock_8m_hxtal(void);

#elif defined (__SYSTEM_CLOCK_64M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_64M_PLL_HXTAL;
static void system_clock_64m_hxtal(void);

#elif defined (__SYSTEM_CLOCK_64M_PLL_IRC16M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_64M_PLL_IRC16M;
static void system_clock_64m_irc16m(void);

#else
uint32_t SystemCoreClock = __SYSTEM_CLOCK_16M_IRC16M;
static void system_clock_16m_irc16m(void);
#endif /* __SYSTEM_CLOCK_16M_HXTAL */

/* configure the system clock */
static void system_clock_config(void);
/* software delay to prevent the impact of Vcore fluctuations.
   It is strongly recommended to include it to avoid issues caused by self-removal. */
static void _soft_delay_(uint32_t time)
{
    __IO uint32_t i;
    for(i=0; i<time*10; i++){
    }
}

/*!
    \brief      setup the microcontroller system, initialize the system
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemInit(void)
{
    /* enable IRC16M */
    RCU_CTL |= RCU_CTL_IRC16MEN;
    while(0U == (RCU_CTL & RCU_CTL_IRC16MSTB)) {
    }
    if(((RCU_CFG0 & RCU_CFG0_SCSS) == RCU_SCSS_PLL)){
        RCU_MODIFY_DE_2(0x50);
    }
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    _soft_delay_(10);
#ifdef  GD32L235
    RCU_CFG1 &= ~RCU_CFG1_SCS_2;
#endif
    RCU_CTL &= ~(RCU_CTL_HXTALEN | RCU_CTL_CKMEN | RCU_CTL_PLLEN | RCU_CTL_HXTALBPS);
    /* reset RCU */
    RCU_CFG0 &= ~(RCU_CFG0_SCS | RCU_CFG0_AHBPSC | RCU_CFG0_APB1PSC | RCU_CFG0_APB2PSC | \
                  RCU_CFG0_ADCPSC | RCU_CFG0_CKOUTSEL | RCU_CFG0_CKOUTDIV);
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF | RCU_CFG0_PLLMF_6 | RCU_CFG0_PLLDV);

    RCU_CFG1 &= ~(RCU_CFG1_PREDV);
#ifdef  GD32L235
    RCU_CFG1 &= ~RCU_CFG1_SCS_2;
#endif
    RCU_CFG2 = 0x00000000U;
    RCU_INT = 0x00000000U;

    /* configure system clock */
    system_clock_config();
}

/*!
    \brief      configure the system clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_config(void)
{
#ifdef __SYSTEM_CLOCK_8M_HXTAL
    system_clock_8m_hxtal();
#elif defined (__SYSTEM_CLOCK_64M_PLL_HXTAL)
    system_clock_64m_hxtal();
#elif defined (__SYSTEM_CLOCK_64M_PLL_IRC16M)
    system_clock_64m_irc16m();
#else
    system_clock_16m_irc16m();
#endif /* __SYSTEM_CLOCK_16M_HXTAL */
}

#ifdef __SYSTEM_CLOCK_8M_HXTAL
/*!
    \brief      configure the system clock to 8M by HXTAL
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_8m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    HXTALSTB_DELAY
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

    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    reg_temp = RCU_CFG0;
    /* select HXTAL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_HXTAL;
    RCU_CFG0 = reg_temp;

    /* wait until HXTAL is selected as system clock */
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_HXTAL) {
    }
}

#elif defined (__SYSTEM_CLOCK_64M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 64M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_64m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    HXTALSTB_DELAY
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
        
#ifdef  GD32L235
    /* set the wait state counter value */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | FMC_WAIT_STATE_2;
#else
    /* set the wait state counter value */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | FMC_WAIT_STATE_1;
#endif


    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    RCU_CFG1 &= ~(RCU_CFG1_PREDV);
    /* PLL = HXTAL * 8 = 64 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF | RCU_CFG0_PLLDV);
    RCU_CFG0 |= (RCU_PLLSRC_HXTAL | RCU_PLL_MUL8);

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
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_PLL) {
    }
}

#elif defined (__SYSTEM_CLOCK_64M_PLL_IRC16M)
/*!
    \brief      configure the system clock to 72M by PLL which selects IRC16M/2 as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_64m_irc16m(void)
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

#ifdef  GD32L235
    /* set the wait state counter value */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | FMC_WAIT_STATE_2;
#else
    /* set the wait state counter value */
    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | FMC_WAIT_STATE_1;
#endif

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    RCU_CFG1 &= ~(RCU_CFG1_PREDV);
    /* PLL = IRC16M * 4 = 64 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    RCU_CFG0 |= (RCU_PLLSRC_IRC16M | RCU_PLL_MUL4);

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
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_PLL) {
    }
}

#else
/*!
    \brief      configure the system clock to 16M by IRC16M
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_16m_irc16m(void)
{
    __IO uint32_t reg_temp;
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    reg_temp = RCU_CFG0;
    /* select IRC16M as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_IRC16M;
    RCU_CFG0 = reg_temp;

    /* wait until IRC16M is selected as system clock */
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_IRC16M) {
    }
}
#endif /* __SYSTEM_CLOCK_16M_HXTAL */

/*!
    \brief      update the SystemCoreClock with current core clock retrieved from cpu registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemCoreClockUpdate(void)
{
    uint32_t sws = 0U, sws0 = 0U, sws1 = 0U;
    uint32_t pllmf = 0U, pllmf6 = 0U, pllsel = 0U, prediv = 0U, idx = 0U, clk_exp = 0U;
    /* exponent of AHB clock divider */
    const uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

    sws0 = GET_BITS(RCU_CFG0, 2, 3);
    sws1 = (RCU_CFG1 & BIT(17)) >> 15; 
    sws = ( sws0 | sws1 );
    switch(sws) {
    /* IRC16M is selected as CK_SYS */
    case SEL_IRC16M:
        SystemCoreClock = IRC16M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        SystemCoreClock = HXTAL_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_IRC32K:
        SystemCoreClock = IRC32K_VALUE;
        break;
    /* PLL is selected as CK_SYS */
    case SEL_PLL:
        /* get the value of PLLMF[5:0] */
        pllmf = GET_BITS(RCU_CFG0, 18, 23);
        pllmf6 = GET_BITS(RCU_CFG0, 27, 27);
        pllmf = ((pllmf6 << 6) + pllmf);
        /* high 16 bits */
        if(14U < pllmf) {
            pllmf += 1U;
        } else if(15U == pllmf) {
            pllmf = 16U;
        } else {
            pllmf += 2U;
        }

        /* PLL clock source selection, HXTAL or IRC16M_VALUE or IRC48M_VALUE */
        pllsel = GET_BITS(RCU_CFG0, 16, 17);
        if(0U == pllsel) {
            prediv = (GET_BITS(RCU_CFG1, 0, 3) + 1U);
            SystemCoreClock = (IRC16M_VALUE / prediv) * pllmf;
        } else if(1U == pllsel) {
            prediv = (GET_BITS(RCU_CFG1, 0, 3) + 1U);
            SystemCoreClock = (HXTAL_VALUE / prediv) * pllmf;
        } else {
            prediv = (GET_BITS(RCU_CFG1, 0, 3) + 1U);
            SystemCoreClock = (IRC48M_VALUE / prediv) * pllmf;
        }
        break;
    /* IRC16M is selected as CK_SYS */
    default:
        SystemCoreClock = IRC16M_VALUE;
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
uint32_t gd32l23x_firmware_version_get(void)
{
    return __GD32L23X_STDPERIPH_VERSION;
}
#endif /* __FIRMWARE_VERSION_DEFINE */
