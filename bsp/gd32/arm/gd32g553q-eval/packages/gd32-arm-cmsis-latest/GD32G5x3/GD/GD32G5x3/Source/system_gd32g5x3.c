/*!
    \file  system_gd32g5x3.c
    \brief CMSIS Cortex-M33 Device Peripheral Access Layer Source File for
           GD32G5x3 Device Series
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

#include "gd32g5x3.h"

/* system frequency define */
#define __IRC8M           (IRC8M_VALUE)            /* internal 8 MHz RC oscillator frequency */
#define __HXTAL           (HXTAL_VALUE)            /* high speed crystal oscillator frequency */
#define __SYS_OSC_CLK     (__IRC8M)                /* main oscillator frequency */

#define VECT_TAB_OFFSET  (uint32_t)0x00            /* vector table base offset */

/* select a system clock by uncommenting the following line */
/* use IRC8M */
//#define __SYSTEM_CLOCK_IRC8M                    (uint32_t)(__IRC8M)
//#define __SYSTEM_CLOCK_48M_PLL_IRC8M           (uint32_t)(48000000)
//#define __SYSTEM_CLOCK_96M_PLL_IRC8M           (uint32_t)(96000000)
//#define __SYSTEM_CLOCK_120M_PLL_IRC8M           (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_170M_PLL_IRC8M           (uint32_t)(170000000)
//#define __SYSTEM_CLOCK_216M_PLL_IRC8M           (uint32_t)(216000000)

/* use HXTAL = 8M */
//#define __SYSTEM_CLOCK_HXTAL                    (uint32_t)(__HXTAL)
//#define __SYSTEM_CLOCK_48M_PLL_HXTAL            (uint32_t)(48000000)
//#define __SYSTEM_CLOCK_96M_PLL_HXTAL            (uint32_t)(96000000)
//#define __SYSTEM_CLOCK_120M_PLL_HXTAL           (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_170M_PLL_HXTAL           (uint32_t)(170000000)
#define __SYSTEM_CLOCK_216M_PLL_HXTAL           (uint32_t)(216000000)

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

    
#define SEL_IRC8M           0x00U
#define SEL_HXTAL           0x01U
#define SEL_PLLP            0x03U

#define PLLPSC_REG_OFFSET   0U
#define PLLN_REG_OFFSET     6U
#define PLLP_REG_OFFSET     16U
#define PLLQ_REG_OFFSET     23U
#define PLLR_REG_OFFSET     27U

/* set the system clock frequency and declare the system clock configuration function */
#ifdef __SYSTEM_CLOCK_IRC8M
uint32_t SystemCoreClock = __SYSTEM_CLOCK_IRC8M;
static void system_clock_8m_irc8m(void);
#elif defined (__SYSTEM_CLOCK_48M_PLL_IRC8M)
#define PLLPSC              (2U - 1U)
#define PLLN                (24U)
#define PLLP                ((2U >> 1U) - 1U)
#define PLLQ                (2U)
#define PLLR                (2U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_48M_PLL_IRC8M;
static void system_clock_48m_irc8m(void);
#elif defined (__SYSTEM_CLOCK_96M_PLL_IRC8M)
#define PLLPSC              (2U - 1U)
#define PLLN                (48U)
#define PLLP                ((2U >> 1U) - 1U)
#define PLLQ                (2U)
#define PLLR                (2U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_96M_PLL_IRC8M;
static void system_clock_96m_irc8m(void);
#elif defined (__SYSTEM_CLOCK_120M_PLL_IRC8M)
#define PLLPSC              (2U - 1U)
#define PLLN                (60U)
#define PLLP                ((2U >> 1U) - 1U)
#define PLLQ                (2U)
#define PLLR                (2U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLL_IRC8M;
static void system_clock_120m_irc8m(void);
#elif defined (__SYSTEM_CLOCK_170M_PLL_IRC8M)
#define PLLPSC              (2U - 1U)
#define PLLN                (85U)
#define PLLP                ((2U >> 1U) - 1U)
#define PLLQ                (2U)
#define PLLR                (2U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_170M_PLL_IRC8M;
static void system_clock_170m_irc8m(void);
#elif defined (__SYSTEM_CLOCK_216M_PLL_IRC8M)
#define PLLPSC              (2U - 1U)
#define PLLN                (108U)
#define PLLP                ((2U >> 1U) - 1U)
#define PLLQ                (2U)
#define PLLR                (2U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_216M_PLL_IRC8M;
static void system_clock_216m_irc8m(void);
#elif defined (__SYSTEM_CLOCK_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_HXTAL;
static void system_clock_hxtal(void);
#elif defined (__SYSTEM_CLOCK_48M_PLL_HXTAL)
#define PLLPSC              (2U - 1U)
#define PLLN                (24U)
#define PLLP                ((2U >> 1U) - 1U)
#define PLLQ                (2U)
#define PLLR                (2U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_48M_PLL_HXTAL;
static void system_clock_48m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_96M_PLL_HXTAL)
#define PLLPSC              (2U - 1U)
#define PLLN                (48U)
#define PLLP                ((2U >> 1U) - 1U)
#define PLLQ                (2U)
#define PLLR                (2U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_96M_PLL_HXTAL;
static void system_clock_96m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_120M_PLL_HXTAL)
#define PLLPSC              (2U - 1U)
#define PLLN                (60U)
#define PLLP                ((2U >> 1U) - 1U)
#define PLLQ                (2U)
#define PLLR                (2U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLL_HXTAL;
static void system_clock_120m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_170M_PLL_HXTAL)
#define PLLPSC              (2U - 1U)
#define PLLN                (85U)
#define PLLP                ((2U >> 1U) - 1U)
#define PLLQ                (2U)
#define PLLR                (2U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_170M_PLL_HXTAL;
static void system_clock_170m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_216M_PLL_HXTAL)
#define PLLPSC              (2U - 1U)
#define PLLN                (108U)
#define PLLP                ((2U >> 1U) - 1U)
#define PLLQ                (2U)
#define PLLR                (2U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_216M_PLL_HXTAL;
static void system_clock_216m_hxtal(void);
#endif /* __SYSTEM_CLOCK_IRC8M */

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
    \brief      setup the micro-controller system, initialize the system
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemInit (void)
{
  /* FPU settings */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1U)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
#endif
    /* reset the RCU clock configuration to the default reset state */
    /* Set IRC8MEN bit */
    RCU_CTL |= RCU_CTL_IRC8MEN;
    while(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)){
    }
    if(((RCU_CFG0 & RCU_CFG0_SCSS) == RCU_SCSS_PLLP)){
        RCU_MODIFY_DE_2(0x50);
    }
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    _soft_delay_(200);
    /* reset HXTALEN, CKMEN and PLLEN bits */
    RCU_CTL &= ~(RCU_CTL_PLLEN | RCU_CTL_CKMEN | RCU_CTL_HXTALEN);
    /* disable all interrupts */
    RCU_INT = 0x109f0000U;

    /* reset CFG0, CFG1 and CFG2 registers */
    RCU_CFG0 = 0x00000000U;
    RCU_CFG1 = 0x00000000U;
    RCU_CFG2 = 0x00000000U;
    /* reset HXTALBPS bit */
    RCU_CTL &= ~(RCU_CTL_HXTALBPS);

    /* configure the system clock source */
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
#ifdef __SYSTEM_CLOCK_IRC8M
    system_clock_8m_irc8m();
#elif defined (__SYSTEM_CLOCK_48M_PLL_IRC8M)
    system_clock_48m_irc8m();
#elif defined (__SYSTEM_CLOCK_96M_PLL_IRC8M)
    system_clock_96m_irc8m();
#elif defined (__SYSTEM_CLOCK_120M_PLL_IRC8M)
    system_clock_120m_irc8m();
#elif defined (__SYSTEM_CLOCK_170M_PLL_IRC8M)
    system_clock_170m_irc8m();
#elif defined (__SYSTEM_CLOCK_216M_PLL_IRC8M)
    system_clock_216m_irc8m();
#elif defined (__SYSTEM_CLOCK_HXTAL)
    system_clock_hxtal();
#elif defined (__SYSTEM_CLOCK_48M_PLL_HXTAL)
    system_clock_48m_hxtal();
#elif defined (__SYSTEM_CLOCK_96M_PLL_HXTAL)
    system_clock_96m_hxtal();
#elif defined (__SYSTEM_CLOCK_120M_PLL_HXTAL)
    system_clock_120m_hxtal();
#elif defined (__SYSTEM_CLOCK_170M_PLL_HXTAL)
    system_clock_170m_hxtal();
#elif defined (__SYSTEM_CLOCK_216M_PLL_HXTAL)
    system_clock_216m_hxtal();
#endif /* __SYSTEM_CLOCK_IRC8M */
}

#ifdef __SYSTEM_CLOCK_IRC8M
/*!
    \brief      configure the system clock to 8M by IRC8M
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_8m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;
    
    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC8MSTB);
    }
    while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)){
        while(1){
        }
    }
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    reg_temp = RCU_CFG0;
    /* select IRC8M as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_IRC8M;
    RCU_CFG0 = reg_temp;
    
    /* wait until IRC8M is selected as system clock */
    while(RCU_SCSS_IRC8M != (RCU_CFG0 & RCU_CFG0_SCSS)){
    }
}

#elif defined (__SYSTEM_CLOCK_48M_PLL_IRC8M)
/*!
    \brief      configure the system clock to 48M by PLL which selects IRC8M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_48m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;

    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC8MSTB);
    }while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(1);

    /* HXTAL is stable */
    /* AHB = SYSCLK/1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB3 = AHB/1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLLP = (CK_IRC8M / 2) * 24 / 2 = 48 MHz */
    RCU_PLL &= ~(RCU_PLL_PLLSEL | RCU_PLL_PLLPSC | RCU_PLL_PLLN | RCU_PLL_PLLP | RCU_PLL_PLLQ | RCU_PLL_PLLR);
    RCU_PLL |= (RCU_PLLSRC_IRC8M | (PLLPSC << PLLPSC_REG_OFFSET) | (PLLN << PLLN_REG_OFFSET) | (PLLP << PLLP_REG_OFFSET) | (PLLQ << PLLQ_REG_OFFSET) | (PLLR << PLLR_REG_OFFSET));
    
    /* enable PLLP, PLLQ, PLLR */
    RCU_PLL |= (RCU_PLL_PLLPEN | RCU_PLL_PLLQEN | RCU_PLL_PLLREN);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)){
    }
}

#elif defined (__SYSTEM_CLOCK_96M_PLL_IRC8M)
/*!
    \brief      configure the system clock to 96M by PLL which selects IRC8M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_96m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;

    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC8MSTB);
    }while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(4);

    /* HXTAL is stable */
    /* AHB = SYSCLK/1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB3 = AHB/1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLLP = (CK_IRC8M / 2) * 48 / 2 = 96 MHz */
    RCU_PLL &= ~(RCU_PLL_PLLSEL | RCU_PLL_PLLPSC | RCU_PLL_PLLN | RCU_PLL_PLLP | RCU_PLL_PLLQ | RCU_PLL_PLLR);
    RCU_PLL |= (RCU_PLLSRC_IRC8M | (PLLPSC << PLLPSC_REG_OFFSET) | (PLLN << PLLN_REG_OFFSET) | (PLLP << PLLP_REG_OFFSET) | (PLLQ << PLLQ_REG_OFFSET) | (PLLR << PLLR_REG_OFFSET));
    
    /* enable PLLP, PLLQ, PLLR */
    RCU_PLL |= (RCU_PLL_PLLPEN | RCU_PLL_PLLQEN | RCU_PLL_PLLREN);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)){
    }
}

#elif defined (__SYSTEM_CLOCK_120M_PLL_IRC8M)
/*!
    \brief      configure the system clock to 120M by PLL which selects IRC8M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_120m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;

    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC8MSTB);
    }while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(5);

    /* HXTAL is stable */
    /* AHB = SYSCLK/1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB3 = AHB/1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLLP = (CK_IRC8M / 2) * 60 / 2 = 120 MHz */
    RCU_PLL &= ~(RCU_PLL_PLLSEL | RCU_PLL_PLLPSC | RCU_PLL_PLLN | RCU_PLL_PLLP | RCU_PLL_PLLQ | RCU_PLL_PLLR);
    RCU_PLL |= (RCU_PLLSRC_IRC8M | (PLLPSC << PLLPSC_REG_OFFSET) | (PLLN << PLLN_REG_OFFSET) | (PLLP << PLLP_REG_OFFSET) | (PLLQ << PLLQ_REG_OFFSET) | (PLLR << PLLR_REG_OFFSET));
    
    /* enable PLLP, PLLQ, PLLR */
    RCU_PLL |= (RCU_PLL_PLLPEN | RCU_PLL_PLLQEN | RCU_PLL_PLLREN);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)){
    }
}

#elif defined (__SYSTEM_CLOCK_170M_PLL_IRC8M)
/*!
    \brief      configure the system clock to 170M by PLL which selects IRC8M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_170m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;

    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC8MSTB);
    }while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(7);

    /* HXTAL is stable */
    /* AHB = SYSCLK/1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB3 = AHB/1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLLP = (CK_IRC8M / 2) * 85 / 2 = 170 MHz */
    RCU_PLL &= ~(RCU_PLL_PLLSEL | RCU_PLL_PLLPSC | RCU_PLL_PLLN | RCU_PLL_PLLP | RCU_PLL_PLLQ | RCU_PLL_PLLR);
    RCU_PLL |= (RCU_PLLSRC_IRC8M | (PLLPSC << PLLPSC_REG_OFFSET) | (PLLN << PLLN_REG_OFFSET) | (PLLP << PLLP_REG_OFFSET) | (PLLQ << PLLQ_REG_OFFSET) | (PLLR << PLLR_REG_OFFSET));
    
    /* enable PLLP, PLLQ, PLLR */
    RCU_PLL |= (RCU_PLL_PLLPEN | RCU_PLL_PLLQEN | RCU_PLL_PLLREN);

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 = 0x00027000;

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)){
    }
}

#elif defined (__SYSTEM_CLOCK_216M_PLL_IRC8M)
/*!
    \brief      configure the system clock to 216M by PLL which selects IRC8M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_216m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;

    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC8MSTB);
    }while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(7);

    /* IRC8M is stable */
    /* AHB = SYSCLK/1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB3 = AHB/1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLLP = (CK_IRC8M / 2) * 108 / 2 = 216 MHz */
    RCU_PLL &= ~(RCU_PLL_PLLSEL | RCU_PLL_PLLPSC | RCU_PLL_PLLN | RCU_PLL_PLLP | RCU_PLL_PLLQ | RCU_PLL_PLLR);
    RCU_PLL |= (RCU_PLLSRC_IRC8M | (PLLPSC << PLLPSC_REG_OFFSET) | (PLLN << PLLN_REG_OFFSET) | (PLLP << PLLP_REG_OFFSET) | (PLLQ << PLLQ_REG_OFFSET) | (PLLR << PLLR_REG_OFFSET));
    
    /* enable PLLP, PLLQ, PLLR */
    RCU_PLL |= (RCU_PLL_PLLPEN | RCU_PLL_PLLQEN | RCU_PLL_PLLREN);

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 = 0x00027000;

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)){
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

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;
    
    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));
    
    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;
    
    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_HXTAL;
    RCU_CFG0 = reg_temp;
    
    /* wait until HXTAL is selected as system clock */
    while(RCU_SCSS_HXTAL != (RCU_CFG0 & RCU_CFG0_SCSS)){
    }
}

#elif defined (__SYSTEM_CLOCK_48M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 48M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_48m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(1);

    /* HXTAL is stable */
    /* AHB = SYSCLK/1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB3 = AHB/1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLLP = (CK_HXTAL / 2) * 24 / 2 = 48MHz */
    RCU_PLL &= ~(RCU_PLL_PLLSEL | RCU_PLL_PLLPSC | RCU_PLL_PLLN | RCU_PLL_PLLP | RCU_PLL_PLLQ | RCU_PLL_PLLR);
    RCU_PLL |= (RCU_PLLSRC_HXTAL | (PLLPSC << PLLPSC_REG_OFFSET) | (PLLN << PLLN_REG_OFFSET) | (PLLP << PLLP_REG_OFFSET) | (PLLQ << PLLQ_REG_OFFSET) | (PLLR << PLLR_REG_OFFSET));
    
    /* enable PLLP, PLLQ, PLLR */
    RCU_PLL |= (RCU_PLL_PLLPEN | RCU_PLL_PLLQEN | RCU_PLL_PLLREN);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)){
    }
}

#elif defined (__SYSTEM_CLOCK_96M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 96M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_96m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(4);

    /* HXTAL is stable */
    /* AHB = SYSCLK/1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB3 = AHB/1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLLP = (CK_HXTAL / 2) * 48 / 2 = 96MHz */
    RCU_PLL &= ~(RCU_PLL_PLLSEL | RCU_PLL_PLLPSC | RCU_PLL_PLLN | RCU_PLL_PLLP | RCU_PLL_PLLQ | RCU_PLL_PLLR);
    RCU_PLL |= (RCU_PLLSRC_HXTAL | (PLLPSC << PLLPSC_REG_OFFSET) | (PLLN << PLLN_REG_OFFSET) | (PLLP << PLLP_REG_OFFSET) | (PLLQ << PLLQ_REG_OFFSET) | (PLLR << PLLR_REG_OFFSET));
    
    /* enable PLLP, PLLQ, PLLR */
    RCU_PLL |= (RCU_PLL_PLLPEN | RCU_PLL_PLLQEN | RCU_PLL_PLLREN);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)){
    }
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
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(5);

    /* HXTAL is stable */
    /* AHB = SYSCLK/1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB3 = AHB/1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLLP = (CK_HXTAL / 2) * 60 / 2 = 120MHz */
    RCU_PLL &= ~(RCU_PLL_PLLSEL | RCU_PLL_PLLPSC | RCU_PLL_PLLN | RCU_PLL_PLLP | RCU_PLL_PLLQ | RCU_PLL_PLLR);
    RCU_PLL |= (RCU_PLLSRC_HXTAL | (PLLPSC << PLLPSC_REG_OFFSET) | (PLLN << PLLN_REG_OFFSET) | (PLLP << PLLP_REG_OFFSET) | (PLLQ << PLLQ_REG_OFFSET) | (PLLR << PLLR_REG_OFFSET));
    
    /* enable PLLP, PLLQ, PLLR */
    RCU_PLL |= (RCU_PLL_PLLPEN | RCU_PLL_PLLQEN | RCU_PLL_PLLREN);

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)){
    }
}

#elif defined (__SYSTEM_CLOCK_170M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 170M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_170m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(7);

    /* HXTAL is stable */
    /* AHB = SYSCLK/1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB3 = AHB/1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLLP = (CK_HXTAL / 2) * 85 / 2 = 170MHz */
    RCU_PLL &= ~(RCU_PLL_PLLSEL | RCU_PLL_PLLPSC | RCU_PLL_PLLN | RCU_PLL_PLLP | RCU_PLL_PLLQ | RCU_PLL_PLLR);
    RCU_PLL |= (RCU_PLLSRC_HXTAL | (PLLPSC << PLLPSC_REG_OFFSET) | (PLLN << PLLN_REG_OFFSET) | (PLLP << PLLP_REG_OFFSET) | (PLLQ << PLLQ_REG_OFFSET) | (PLLR << PLLR_REG_OFFSET));
    
    /* enable PLLP, PLLQ, PLLR */
    RCU_PLL |= (RCU_PLL_PLLPEN | RCU_PLL_PLLQEN | RCU_PLL_PLLREN);

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 = 0x00027000;


    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)){
    }
}
#elif defined (__SYSTEM_CLOCK_216M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 216M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_216m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(7);

    /* HXTAL is stable */
    /* AHB = SYSCLK/1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB3 = AHB/1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLLP = (CK_HXTAL / 2) * 108 / 2 = 216 MHz */
    RCU_PLL &= ~(RCU_PLL_PLLSEL | RCU_PLL_PLLPSC | RCU_PLL_PLLN | RCU_PLL_PLLP | RCU_PLL_PLLQ | RCU_PLL_PLLR);
    RCU_PLL |= (RCU_PLLSRC_HXTAL | (PLLPSC << PLLPSC_REG_OFFSET) | (PLLN << PLLN_REG_OFFSET) | (PLLP << PLLP_REG_OFFSET) | (PLLQ << PLLQ_REG_OFFSET) | (PLLR << PLLR_REG_OFFSET));
    
    /* enable PLLP, PLLQ, PLLR */
    RCU_PLL |= (RCU_PLL_PLLPEN | RCU_PLL_PLLQEN | RCU_PLL_PLLREN);

    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 = 0x00027000;

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(RCU_SCSS_PLLP != (RCU_CFG0 & RCU_CFG0_SCSS)){
    }
}
#endif /* __SYSTEM_CLOCK_IRC8M */

/*!
    \brief      update the SystemCoreClock with current core clock retrieved from CPU registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemCoreClockUpdate (void)
{
    uint32_t sws;
    uint32_t pllsel, pllpsc, plln, pllp, ck_src, idx, clk_exp;

    /* exponent of AHB, APB1 and APB2 clock divider */
    uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

    sws = GET_BITS(RCU_CFG0, 2, 3);
    switch(sws){
    /* IRC8M is selected as CK_SYS */
    case SEL_IRC8M:
        SystemCoreClock = IRC8M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        SystemCoreClock = HXTAL_VALUE;
        break;
    /* PLL is selected as CK_SYS */
    case SEL_PLLP:
        /* PLL clock source selection, HXTAL or IRC8M */
        pllsel = (RCU_PLL & RCU_PLL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel) {
            /* PLL clock source is HXTAL */
            ck_src = HXTAL_VALUE;
        }else{
            /* PLL clock source is IRC8M */
            ck_src = IRC8M_VALUE;
        }
        
        pllpsc = (RCU_PLL & RCU_PLL_PLLPSC) + 1U;
        /* PLL input source clock */
        ck_src = ck_src / pllpsc;

        /* PLL multiplication factor */
        plln = GET_BITS(RCU_PLL, 6, 13);
        
        /* PLL P output division factor */
        pllp = (GET_BITS(RCU_PLL, 16, 17) + 1U) << 1U;
        
        SystemCoreClock = ck_src * plln / pllp;

        break;
    /* IRC8M is selected as CK_SYS */
    default:
        SystemCoreClock = IRC8M_VALUE;
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
uint32_t gd32g5x3_firmware_version_get(void)
{
    return __GD32G5X3_STDPERIPH_VERSION;
}
#endif /* __FIRMWARE_VERSION_DEFINE */
