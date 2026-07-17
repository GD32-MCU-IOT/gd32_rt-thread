/*!
    \file  system_gd32f50x.c
    \brief CMSIS Cortex-M33 Device Peripheral Access Layer Source File for
           gd32f50x Device Series
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

#include "gd32f50x.h"

/* system frequency define */
#define __IRC8M           (IRC8M_VALUE)            /* internal 8 MHz RC oscillator frequency */
#define __HXTAL           (HXTAL_VALUE)            /* high speed crystal oscillator frequency */
#define __SYS_OSC_CLK     (__IRC8M)                /* main oscillator frequency */

#define VECT_TAB_OFFSET  (uint32_t)0x00            /* vector table base offset */

/* select a system clock by uncommenting the following line */
#if (defined(GD32F502) || defined(GD32F503) || defined(GD32F505))
//#define __SYSTEM_CLOCK_IRC8M                    (uint32_t)(__IRC8M)
//#define __SYSTEM_CLOCK_HXTAL                    (uint32_t)(__HXTAL)
//#define __SYSTEM_CLOCK_200M_PLL_IRC8M           (uint32_t)(200000000)
//#define __SYSTEM_CLOCK_200M_PLL_HXTAL           (uint32_t)(200000000)
#endif /* GD32F502 || GD32F503 || GD32F505 */

#if (defined(GD32F503) || defined(GD32F505))
//#define __SYSTEM_CLOCK_220M_PLL_IRC8M           (uint32_t)(220000000)
//#define __SYSTEM_CLOCK_220M_PLL_HXTAL           (uint32_t)(220000000)
//#define __SYSTEM_CLOCK_252M_PLL_IRC8M           (uint32_t)(252000000)
#define __SYSTEM_CLOCK_252M_PLL_HXTAL           (uint32_t)(252000000)
#endif /* GD32F503 || GD32F505 */

#if (defined(GD32F505))
//#define __SYSTEM_CLOCK_280M_PLL_IRC8M           (uint32_t)(280000000)
//#define __SYSTEM_CLOCK_280M_PLL_HXTAL           (uint32_t)(280000000)
#endif /* GD32F505 */

/* The following is to prevent Vcore fluctuations caused by frequency switching.
   It is strongly recommended to include it to avoid issues caused by self-removal. */
#define RCU_MODIFY_DE_2(__delay)   do{                                    \
                                    volatile uint32_t i, reg;             \
                                    if(0U != (__delay)){                  \
                                        /* Insert a software delay */     \
                                        for(i=0U; i<(__delay); i++){      \
                                        }                                 \
                                        reg = RCU_CFG0;                   \
                                        reg &= ~(RCU_CFG0_AHBPSC);        \
                                        reg |= RCU_AHB_CKSYS_DIV2;        \
                                        /* AHB = SYSCLK/2 */              \
                                        RCU_CFG0 = reg;                   \
                                        /* Insert a software delay */     \
                                        for(i=0U; i<(__delay); i++){      \
                                        }                                 \
                                        reg = RCU_CFG0;                   \
                                        reg &= ~(RCU_CFG0_AHBPSC);        \
                                        reg |= RCU_AHB_CKSYS_DIV4;        \
                                        /* AHB = SYSCLK/4 */              \
                                        RCU_CFG0 = reg;                   \
                                        /* Insert a software delay */     \
                                        for(i=0U; i<(__delay); i++){      \
                                        }                                 \
                                    }                                     \
                                }while(0U)

/* The following is to prevent Vcore fluctuations caused by frequency switching.
   It is strongly recommended to include it to avoid issues caused by self-removal. */
#define RCU_MODIFY_UP_2(__delay)  do{                                     \
                                      volatile uint32_t i,reg;            \
                                      if(0U != (__delay)){                \
                                          for(i=0U; i<(__delay); i++){    \
                                          }                               \
                                          reg = RCU_CFG0;                 \
                                          reg &= ~(RCU_CFG0_AHBPSC);      \
                                          reg |= RCU_AHB_CKSYS_DIV2;      \
                                          RCU_CFG0 = reg;                 \
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

#define SEL_IRC8M       0x00U
#define SEL_HXTAL       0x01U
#define SEL_PLL0P       0x02U

/* set the system clock frequency and declare the system clock configuration function */
#ifdef __SYSTEM_CLOCK_IRC8M
uint32_t SystemCoreClock = __SYSTEM_CLOCK_IRC8M;
static void system_clock_8m_irc8m(void);
#elif defined (__SYSTEM_CLOCK_200M_PLL_IRC8M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_200M_PLL_IRC8M;
static void system_clock_200m_irc8m(void);
#elif defined (__SYSTEM_CLOCK_220M_PLL_IRC8M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_220M_PLL_IRC8M;
static void system_clock_220m_irc8m(void);
#elif defined (__SYSTEM_CLOCK_252M_PLL_IRC8M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_252M_PLL_IRC8M;
static void system_clock_252m_irc8m(void);
#elif defined (__SYSTEM_CLOCK_280M_PLL_IRC8M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_280M_PLL_IRC8M;
static void system_clock_280m_irc8m(void);

#elif defined (__SYSTEM_CLOCK_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_HXTAL;
static void system_clock_hxtal(void);
#elif defined (__SYSTEM_CLOCK_200M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_200M_PLL_HXTAL;
static void system_clock_200m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_220M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_220M_PLL_HXTAL;
static void system_clock_220m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_252M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_252M_PLL_HXTAL;
static void system_clock_252m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_280M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_280M_PLL_HXTAL;
static void system_clock_280m_hxtal(void);
#endif /* __SYSTEM_CLOCK_IRC8M */

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
    /* FPU settings */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1U)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif

    /* enable no waiting time area load after system reset */
    if((RESET != (FMC_CTL0 & FMC_CTL0_LK))) {
        /* write the FMC unlock key */
        FMC_KEY0 = UNLOCK_KEY0;
        FMC_KEY0 = UNLOCK_KEY1;
    }
    FMC_CTL0 |= FMC_CTL0_NWLDE;
    FMC_CTL0 |= FMC_CTL0_LK;

    /* reset the RCU clock configuration to the default reset state */
    /* Set IRC8MEN bit */
    RCU_CTL |= RCU_CTL_IRC8MEN;
    while(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)) {
    }

    if(((RCU_CFG0 & RCU_CFG0_SCSS) == RCU_SCSS_PLL0P)) {
        RCU_MODIFY_DE_2(0x50U);
    }

    RCU_CFG0 &= ~RCU_CFG0_SCS;
    _soft_delay_(200U);

    /* reset CTL register */
    RCU_CTL &= ~(RCU_CTL_HXTALEN | RCU_CTL_HCKMEN | RCU_CTL_PLL0EN | RCU_CTL_PLL1EN);
    RCU_CTL &= ~RCU_CTL_HXTALBPS;

    /* reset CFG0 register */
    RCU_CFG0 &= ~(RCU_CFG0_SCS | RCU_CFG0_AHBPSC | RCU_CFG0_APB1PSC | RCU_CFG0_APB2PSC |
                  RCU_CFG0_ADCPSC | RCU_CFG0_PREDIV0_LSB | RCU_CFG0_PLL0MF_0_3 |
                  RCU_CFG0_USBFSPSC | RCU_CFG0_CKOUTSEL | RCU_CFG0_PLL0MF_4_5 | RCU_CFG0_USBFSPSC_2);
    /* reset INT register */
    RCU_INT = 0x01BF0000U;
    /* reset ADDINT register */
    RCU_ADDINT = 0x00400000U;
    RCU_CFG1 &= ~(RCU_CFG1_PREDIV0 | RCU_CFG1_PREDIV1 | RCU_CFG1_PLL1MF | RCU_CFG1_PLL1SEL | RCU_CFG1_PLL0SEL
                  | RCU_CFG1_I2S1SEL | RCU_CFG1_I2S2SEL | RCU_CFG1_ADCPSC_3 | RCU_CFG1_HXTALRDYRST);

    /* reset CKFMCFG0 register */
    RCU_CKFMCFG0 = 0x00000010U;
    /* reset CKFMCFG1 register */
    RCU_CKFMCFG1 = 0x80000000U;
    /* reset CKFMCFG2 register */
    RCU_CKFMCFG2 = 0x80000000U;
    /* reset CKFMCFG3 register */
    RCU_CKFMCFG3 = 0x80000000U;

    /* reset ADDCTL register */
    RCU_ADDCTL &= ~(RCU_ADDCTL_CK48MSEL | RCU_ADDCTL_FMCSEL | RCU_ADDCTL_I2S1DIV | RCU_ADDCTL_PLL0DIV
                    | RCU_ADDCTL_FMCDIV | RCU_ADDCTL_I2S2DIV);

    /* configure system clock */
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
#ifdef __SYSTEM_CLOCK_IRC8M
    system_clock_8m_irc8m();
#elif defined (__SYSTEM_CLOCK_200M_PLL_IRC8M)
    system_clock_200m_irc8m();
#elif defined (__SYSTEM_CLOCK_220M_PLL_IRC8M)
    system_clock_220m_irc8m();
#elif defined (__SYSTEM_CLOCK_252M_PLL_IRC8M)
    system_clock_252m_irc8m();
#elif defined (__SYSTEM_CLOCK_280M_PLL_IRC8M)
    system_clock_280m_irc8m();

#elif defined (__SYSTEM_CLOCK_HXTAL)
    system_clock_hxtal();
#elif defined (__SYSTEM_CLOCK_200M_PLL_HXTAL)
    system_clock_200m_hxtal();
#elif defined (__SYSTEM_CLOCK_220M_PLL_HXTAL)
    system_clock_220m_hxtal();
#elif defined (__SYSTEM_CLOCK_252M_PLL_HXTAL)
    system_clock_252m_hxtal();
#elif defined (__SYSTEM_CLOCK_280M_PLL_HXTAL)
    system_clock_280m_hxtal();
#endif /* __SYSTEM_CLOCK_IRC8M */
}

#ifdef __SYSTEM_CLOCK_IRC8M
/*!
    \brief      configure the system clock to 8M by IRC8M
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_8m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;

    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC8MSTB);
    } while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)) {
        while(1) {
        }
    }

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* select FMC clock is CK_AHB and div is 1 */
    RCU_ADDCTL &= ~(RCU_ADDCTL_FMCSEL | RCU_ADDCTL_FMCDIV);
    RCU_ADDCTL |=  RCU_FMC_CK_AHB | RCU_FMC_DIV1;

    reg_temp = RCU_CFG0;
    /* select IRC8M as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_IRC8M;
    RCU_CFG0 = reg_temp;

    /* wait until IRC8M is selected as system clock */
    while(RCU_CKSYSSRC_IRC8M != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_200M_PLL_IRC8M)
/*!
    \brief      configure the system clock to 200M by PLL0 which selects IRC8M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_200m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;

    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC8MSTB);
    } while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)) {
        while(1) {
        }
    }

    /* LDO output voltage high mode */
    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC8M is stable */
    /* AHB = SYSCLK/4. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL0P = (CK_IRC8M)/2 * 50 = 200 MHz */
    RCU_CFG1 &= ~(RCU_CFG1_PLL0SEL | RCU_CFG1_PREDIV0 | RCU_CFG1_PREDIV1);
    RCU_CFG1 |= (RCU_PLL0SRC_IRC8M  |  RCU_PREDIV0_DIV2);
    RCU_CFG0 &= ~(RCU_CFG0_PLL0MF_0_3 | RCU_CFG0_PLL0MF_4_5);
    RCU_CFG0 |= RCU_PLL0_MUL50;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    /* select FMC clock is CK_AHB and div is 1 */
    RCU_ADDCTL &= ~(RCU_ADDCTL_FMCSEL | RCU_ADDCTL_FMCDIV);
    RCU_ADDCTL |=  RCU_FMC_CK_AHB | RCU_FMC_DIV1;

    reg_temp = RCU_CFG0;
    /* select PLL0P as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0P is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    /* modify AHB clcok to SYSCLK */
    RCU_MODIFY_UP_2(0x50U);
}

#elif defined (__SYSTEM_CLOCK_220M_PLL_IRC8M)
/*!
    \brief      configure the system clock to 220M by PLL0 which selects IRC8M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_220m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;

    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC8MSTB);
    } while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)) {
        while(1) {
        }
    }

    /* LDO output voltage high mode */
    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC8M is stable */
    /* AHB = SYSCLK/4. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_IRC8M)/2 * 55 = 220 MHz */
    RCU_CFG1 &= ~(RCU_CFG1_PLL0SEL | RCU_CFG1_PREDIV0 | RCU_CFG1_PREDIV1);
    RCU_CFG1 |= (RCU_PLL0SRC_IRC8M  |  RCU_PREDIV0_DIV2);
    RCU_CFG0 &= ~(RCU_CFG0_PLL0MF_0_3 | RCU_CFG0_PLL0MF_4_5);
    RCU_CFG0 |= RCU_PLL0_MUL55;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    /* select FMC clock is CK_AHB and div is 1 */
    RCU_ADDCTL &= ~(RCU_ADDCTL_FMCSEL | RCU_ADDCTL_FMCDIV);
    RCU_ADDCTL |=  RCU_FMC_CK_AHB | RCU_FMC_DIV1;

    reg_temp = RCU_CFG0;
    /* select PLL0P as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    /* modify AHB clcok to SYSCLK */
    RCU_MODIFY_UP_2(0x50U);
}

#elif defined (__SYSTEM_CLOCK_252M_PLL_IRC8M)
/*!
    \brief      configure the system clock to 252M by PLL0 which selects IRC8M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_252m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;

    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC8MSTB);
    } while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)) {
        while(1) {
        }
    }

    /* LDO output voltage high mode */
    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC8M is stable */
    /* AHB = SYSCLK/4. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_IRC8M)/2 * 63 = 252 MHz */
    RCU_CFG1 &= ~(RCU_CFG1_PLL0SEL | RCU_CFG1_PREDIV0 | RCU_CFG1_PREDIV1);
    RCU_CFG1 |= (RCU_PLL0SRC_IRC8M  |  RCU_PREDIV0_DIV2);
    RCU_CFG0 &= ~(RCU_CFG0_PLL0MF_0_3 | RCU_CFG0_PLL0MF_4_5);
    RCU_CFG0 |= RCU_PLL0_MUL63;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    /* select FMC clock is CK_AHB and div is 1 */
    RCU_ADDCTL &= ~(RCU_ADDCTL_FMCSEL | RCU_ADDCTL_FMCDIV);
    RCU_ADDCTL |=  RCU_FMC_CK_AHB | RCU_FMC_DIV1;

    reg_temp = RCU_CFG0;
    /* select PLL0P as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    /* modify AHB clcok to SYSCLK */
    RCU_MODIFY_UP_2(0x50U);
}

#elif defined (__SYSTEM_CLOCK_280M_PLL_IRC8M)
/*!
    \brief      configure the system clock to 280M by PLL0 which selects IRC8M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_280m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;

    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC8MSTB);
    } while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC8MSTB)) {
        while(1) {
        }
    }

    /* LDO output voltage high mode */
    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    PMU_CTL0 |= PMU_CTL0_LDOVS;

    /* IRC8M is stable */
    /* AHB = SYSCLK/4. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_IRC8M)/1 * 35 = 280 MHz */
    RCU_CFG1 &= ~(RCU_CFG1_PLL0SEL | RCU_CFG1_PREDIV0 | RCU_CFG1_PREDIV1);
    RCU_CFG1 |= (RCU_PLL0SRC_IRC8M  |  RCU_PREDIV0_DIV1);
    RCU_CFG0 &= ~(RCU_CFG0_PLL0MF_0_3 | RCU_CFG0_PLL0MF_4_5);
    RCU_CFG0 |= RCU_PLL0_MUL35;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    /* select FMC clock is CK_AHB and div is 1 */
    RCU_ADDCTL &= ~(RCU_ADDCTL_FMCSEL | RCU_ADDCTL_FMCDIV);
    RCU_ADDCTL |=  RCU_FMC_CK_AHB | RCU_FMC_DIV1;

    reg_temp = RCU_CFG0;
    /* select PLL0P as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    /* modify AHB clcok to SYSCLK */
    RCU_MODIFY_UP_2(0x50U);
}

#elif defined (__SYSTEM_CLOCK_HXTAL)
/*!
    \brief      configure the system clock to HXTAL
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_hxtal(void)
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

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* select FMC clock is CK_AHB and div is 1 */
    RCU_ADDCTL &= ~(RCU_ADDCTL_FMCSEL | RCU_ADDCTL_FMCDIV);
    RCU_ADDCTL |=  RCU_FMC_CK_AHB | RCU_FMC_DIV1;

    reg_temp = RCU_CFG0;
    /* select HXTAL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_HXTAL;
    RCU_CFG0 = reg_temp;

    /* wait until HXTAL is selected as system clock */
    while(RCU_SCSS_HXTAL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_200M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 200M by PLL0 which selects HXTAL(8M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
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
    /* AHB = SYSCLK/4. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL0P = (HXTAL)/2 * 50 = 200 MHz */
    RCU_CFG1 &= ~(RCU_CFG1_PLL0SEL | RCU_CFG1_PREDIV0 | RCU_CFG1_PREDIV1);
    RCU_CFG1 |= (RCU_PLL0SRC_HXTAL  |  RCU_PREDIV0_DIV2);
    RCU_CFG0 &= ~(RCU_CFG0_PLL0MF_0_3 | RCU_CFG0_PLL0MF_4_5);
    RCU_CFG0 |= RCU_PLL0_MUL50;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    /* select FMC clock is CK_AHB and div is 1 */
    RCU_ADDCTL &= ~(RCU_ADDCTL_FMCSEL | RCU_ADDCTL_FMCDIV);
    RCU_ADDCTL |=  RCU_FMC_CK_AHB | RCU_FMC_DIV1;

    reg_temp = RCU_CFG0;
    /* select PLL0P as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0P is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    /* modify AHB clcok to SYSCLK */
    RCU_MODIFY_UP_2(0x50U);
}

#elif defined (__SYSTEM_CLOCK_220M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 220M by PLL0 which selects HXTAL(8M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_220m_hxtal(void)
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
    /* AHB = SYSCLK/4. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL0P = (HXTAL)/2 * 55 = 220 MHz */
    RCU_CFG1 &= ~(RCU_CFG1_PLL0SEL | RCU_CFG1_PREDIV0 | RCU_CFG1_PREDIV1);
    RCU_CFG1 |= (RCU_PLL0SRC_HXTAL  |  RCU_PREDIV0_DIV2);
    RCU_CFG0 &= ~(RCU_CFG0_PLL0MF_0_3 | RCU_CFG0_PLL0MF_4_5);
    RCU_CFG0 |= RCU_PLL0_MUL55;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    /* select FMC clock is CK_AHB and div is 1 */
    RCU_ADDCTL &= ~(RCU_ADDCTL_FMCSEL | RCU_ADDCTL_FMCDIV);
    RCU_ADDCTL |=  RCU_FMC_CK_AHB | RCU_FMC_DIV1;

    reg_temp = RCU_CFG0;
    /* select PLL0P as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    /* modify AHB clcok to SYSCLK */
    RCU_MODIFY_UP_2(0x50U);
}

#elif defined (__SYSTEM_CLOCK_252M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 252M by PLL0 which selects HXTAL(8M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_252m_hxtal(void)
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
    /* AHB = SYSCLK/4. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL0P = (HXTAL)/2 * 63 = 252 MHz */
    RCU_CFG1 &= ~(RCU_CFG1_PLL0SEL | RCU_CFG1_PREDIV0 | RCU_CFG1_PREDIV1);
    RCU_CFG1 |= (RCU_PLL0SRC_HXTAL  |  RCU_PREDIV0_DIV2);
    RCU_CFG0 &= ~(RCU_CFG0_PLL0MF_0_3 | RCU_CFG0_PLL0MF_4_5);
    RCU_CFG0 |= RCU_PLL0_MUL63;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    /* select FMC clock is CK_AHB and div is 1 */
    RCU_ADDCTL &= ~(RCU_ADDCTL_FMCSEL | RCU_ADDCTL_FMCDIV);
    RCU_ADDCTL |=  RCU_FMC_CK_AHB | RCU_FMC_DIV1;

    reg_temp = RCU_CFG0;
    /* select PLL0P as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    /* modify AHB clcok to SYSCLK */
    RCU_MODIFY_UP_2(0x50U);
}

#elif defined (__SYSTEM_CLOCK_280M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 280M by PLL0 which selects HXTAL(8M) as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_280m_hxtal(void)
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
    /* AHB = SYSCLK/4. AHB clock will be modified to SYSCLK after frequency switching finished to prevent Vcore fluctuations */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV4;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL0P = (HXTAL)/1 * 35 = 280 MHz */
    RCU_CFG1 &= ~(RCU_CFG1_PLL0SEL | RCU_CFG1_PREDIV0 | RCU_CFG1_PREDIV1);
    RCU_CFG1 |= (RCU_PLL0SRC_HXTAL  |  RCU_PREDIV0_DIV1);
    RCU_CFG0 &= ~(RCU_CFG0_PLL0MF_0_3 | RCU_CFG0_PLL0MF_4_5);
    RCU_CFG0 |= RCU_PLL0_MUL35;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    /* select FMC clock is CK_AHB and div is 1 */
    RCU_ADDCTL &= ~(RCU_ADDCTL_FMCSEL | RCU_ADDCTL_FMCDIV);
    RCU_ADDCTL |=  RCU_FMC_CK_AHB | RCU_FMC_DIV1;

    reg_temp = RCU_CFG0;
    /* select PLL0P as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }

    /* modify AHB clcok to SYSCLK */
    RCU_MODIFY_UP_2(0x50U);
}
#endif /* __SYSTEM_CLOCK_IRC8M */

/*!
    \brief      update the SystemCoreClock with current core clock retrieved from cpu registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemCoreClockUpdate(void)
{
    uint32_t sws;
    uint32_t ck_src, idx, clk_exp;
    /* exponent of AHB, APB1 and APB2 clock divider */
    const uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
    uint32_t pll0sel, pll1sel, prediv0, pll0mf, prediv1, pll1mf, pll0div;

    sws = GET_BITS(RCU_CFG0, 2, 3);
    switch(sws) {
    /* IRC8M is selected as CK_SYS */
    case SEL_IRC8M:
        SystemCoreClock = IRC8M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        SystemCoreClock = HXTAL_VALUE;
        break;
    /* PLL0P is selected as CK_SYS */
    case SEL_PLL0P:
        /* PLL0 clock source selection, IRC8M, IRC48M, HXTAL, or PLL1*/
        pll0sel = (RCU_CFG1 & RCU_CFG1_PLL0SEL);

        if(RCU_PLL0SRC_IRC8M == pll0sel) {
            /* PLL0 clock source is IRC8M*/
            ck_src = IRC8M_VALUE;
        } else if(RCU_PLL0SRC_IRC48M == pll0sel) {
            /* PLL0 clock source is IRC48M*/
            ck_src = IRC48M_VALUE;
        } else if(RCU_PLL0SRC_HXTAL == pll0sel) {
            /* PLL0 clock source is HXTAL*/
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLL0SRC_CKPLL1 == pll0sel) {
            /* PLL1 clock source is HXTAL or IRC48M */
            pll1sel = (RCU_CFG1 & RCU_CFG1_PLL1SEL);

            if(RCU_PLL1SRC_HXTAL == pll1sel) {
                /* PLL1 clock source is HXTAL */
                ck_src = HXTAL_VALUE;
            } else {
                /* PLL1 clock source is IRC48M */
                ck_src = IRC48M_VALUE;
            }

            prediv1 = ((RCU_CFG1 & RCU_CFG1_PREDIV1) >> 4U) + 1U;
            /* PLL1 multiplication factor */
            pll1mf = (uint32_t)((RCU_CFG1 & RCU_CFG1_PLL1MF) >> 8U);
            ck_src = (ck_src / prediv1) * pll1mf;
        } else {
        }

        /* PLL0 multiplication factor */
        prediv0 = ((RCU_CFG1 & RCU_CFG1_PREDIV0)) + 1U;
        /* PLL1 multiplication factor */
        pll0mf = GET_BITS(RCU_CFG0, 18, 21);
        pll0mf |= GET_BITS(RCU_CFG0, 29, 30) << 4U;
        pll0div = GET_BITS(RCU_ADDCTL, 8, 11) + 1U;
        SystemCoreClock = ((ck_src / prediv0) * pll0mf) / pll0div;
        break;
    default:
        /* should not be here */
        break;
    }

    /* calculate AHB clock frequency */
    idx = GET_BITS(RCU_CFG0, 4, 7);
    clk_exp = ahb_exp[idx];
    SystemCoreClock = SystemCoreClock >> clk_exp;
}

#ifdef __FIRMWARE_VERSION_DEFINE
/*!
    \brief      get firmware version
    \param[in]  none
    \param[out] none
    \retval     firmware version
*/
uint32_t gd32f50x_firmware_version_get(void)
{
    return (uint32_t)__gd32f50x_STDPERIPH_VERSION;
}
#endif /* __FIRMWARE_VERSION_DEFINE */
