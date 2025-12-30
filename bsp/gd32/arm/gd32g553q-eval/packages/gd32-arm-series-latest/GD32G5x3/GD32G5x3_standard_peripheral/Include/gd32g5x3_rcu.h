/*!
    \file    gd32g5x3_rcu.h
    \brief   definitions for the RCU

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

#ifndef GD32G5X3_RCU_H
#define GD32G5X3_RCU_H

#include "gd32g5x3.h"

/* RCU definitions */
#define RCU                             RCU_BASE

/* registers definitions */
#define RCU_CTL                         REG32(RCU + 0x00000000U)        /*!< control register */
#define RCU_PLL                         REG32(RCU + 0x00000004U)        /*!< PLL register */
#define RCU_CFG0                        REG32(RCU + 0x00000008U)        /*!< clock configuration register 0 */
#define RCU_INT                         REG32(RCU + 0x0000000CU)        /*!< clock interrupt register */
#define RCU_AHB1RST                     REG32(RCU + 0x00000010U)        /*!< AHB1 reset register */
#define RCU_AHB2RST                     REG32(RCU + 0x00000014U)        /*!< AHB2 reset register */
#define RCU_AHB3RST                     REG32(RCU + 0x00000018U)        /*!< AHB3 reset register */
#define RCU_APB1RST                     REG32(RCU + 0x00000020U)        /*!< APB1 reset register */
#define RCU_APB2RST                     REG32(RCU + 0x00000024U)        /*!< APB2 reset register */
#define RCU_APB3RST                     REG32(RCU + 0x00000028U)        /*!< APB3 reset register */
#define RCU_AHB1EN                      REG32(RCU + 0x00000030U)        /*!< AHB1 enable register */
#define RCU_AHB2EN                      REG32(RCU + 0x00000034U)        /*!< AHB2 enable register */
#define RCU_AHB3EN                      REG32(RCU + 0x00000038U)        /*!< AHB3 enable register */
#define RCU_APB1EN                      REG32(RCU + 0x00000040U)        /*!< APB1 enable register */
#define RCU_APB2EN                      REG32(RCU + 0x00000044U)        /*!< APB2 enable register */
#define RCU_APB3EN                      REG32(RCU + 0x00000048U)        /*!< APB3 enable register */
#define RCU_AHB1SPDPEN                  REG32(RCU + 0x00000050U)        /*!< AHB1 sleep and deep-sleep mode enable register */
#define RCU_AHB2SPDPEN                  REG32(RCU + 0x00000054U)        /*!< AHB2 sleep and deep-sleep mode enable register */
#define RCU_AHB3SPDPEN                  REG32(RCU + 0x00000058U)        /*!< AHB3 sleep and deep-sleep mode enable register */ 
#define RCU_APB1SPDPEN                  REG32(RCU + 0x00000060U)        /*!< APB1 sleep and deep-sleep mode enable register */
#define RCU_APB2SPDPEN                  REG32(RCU + 0x00000064U)        /*!< APB2 sleep and deep-sleep mode enable register */
#define RCU_APB3SPDPEN                  REG32(RCU + 0x00000068U)        /*!< APB3 sleep and deep-sleep mode enable register */
#define RCU_BDCTL                       REG32(RCU + 0x00000070U)        /*!< backup domain control register */
#define RCU_RSTSCK                      REG32(RCU + 0x00000074U)        /*!< reset source / clock register */
#define RCU_CFG1                        REG32(RCU + 0x0000008CU)        /*!< clock configuration register 1 */
#define RCU_CFG2                        REG32(RCU + 0x00000090U)        /*!< clock configuration register 2 */

/* bits definitions */
/* RCU_CTL */
#define RCU_CTL_IRC8MEN                 BIT(0)                    /*!< internal high speed oscillator enable */
#define RCU_CTL_IRC8MSTB                BIT(1)                    /*!< IRC8M high speed internal oscillator stabilization flag */
#define RCU_CTL_IRC8MADJ                BITS(3,7)                 /*!< high speed internal oscillator clock trim adjust value */
#define RCU_CTL_IRC8MCALIB              BITS(8,15)                /*!< high speed internal oscillator calibration value register */
#define RCU_CTL_HXTALEN                 BIT(16)                   /*!< external high speed oscillator enable */
#define RCU_CTL_HXTALSTB                BIT(17)                   /*!< external crystal oscillator clock stabilization flag */
#define RCU_CTL_HXTALBPS                BIT(18)                   /*!< external crystal oscillator clock bypass mode enable */
#define RCU_CTL_CKMEN                   BIT(19)                   /*!< HXTAL clock monitor enable */   
#define RCU_CTL_HXTALSTBRST             BIT(20)                   /*!< HXTAL stabilization reset */
#define RCU_CTL_PLLEN                   BIT(24)                   /*!< PLL enable */
#define RCU_CTL_PLLSTB                  BIT(25)                   /*!< PLL clock stabilization flag */

/* RCU_PLL */
#define RCU_PLL_PLLPSC                  BITS(0,3)                 /*!< The PLL VCO source clock prescaler */
#define RCU_PLL_PLLN                    BITS(6,13)                /*!< The PLL VCO clock multi factor */
#define RCU_PLL_PLLP                    BITS(16,17)               /*!< The PLLP output frequency division factor from PLL VCO clock */
#define RCU_PLL_PLLPEN                  BIT(19)                   /*!< PLL DIVP divider output enable */
#define RCU_PLL_PLLQEN                  BIT(20)                   /*!< PLL DIVQ divider output enable */
#define RCU_PLL_PLLREN                  BIT(21)                   /*!< PLL DIVR divider output enable */
#define RCU_PLL_PLLSEL                  BIT(22)                   /*!< PLL clock source selection */
#define RCU_PLL_PLLQ                    BITS(23,26)               /*!< The PLL Q output frequency division factor from PLL VCO clock */
#define RCU_PLL_PLLR                    BITS(27,31)               /*!< The PLL R output frequency division factor from PLL VCO clock */

/* RCU_CFG0 */
#define RCU_CFG0_SCS                    BITS(0,1)                 /*!< system clock switch */
#define RCU_CFG0_SCSS                   BITS(2,3)                 /*!< system clock switch status */
#define RCU_CFG0_AHBPSC                 BITS(4,7)                 /*!< AHB prescaler selection */
#define RCU_CFG0_APB1PSC                BITS(10,12)               /*!< APB1 prescaler selection */
#define RCU_CFG0_APB2PSC                BITS(13,15)               /*!< APB2 prescaler selection */
#define RCU_CFG0_CKOUTSEL               BITS(21,23)               /*!< CKOUT clock source selection */
#define RCU_CFG0_CKOUTDIV               BITS(24,26)               /*!< The CK_OUT divider which the CK_OUT frequency can be reduced */
#define RCU_CFG0_APB3PSC                BITS(27,29)               /*!< APB3 prescaler selection */

/* RCU_INT */
#define RCU_INT_IRC32KSTBIF             BIT(0)                    /*!< IRC32K stabilization interrupt flag */
#define RCU_INT_LXTALSTBIF              BIT(1)                    /*!< LXTAL stabilization interrupt flag */
#define RCU_INT_IRC8MSTBIF              BIT(2)                    /*!< IRC8M stabilization interrupt flag */
#define RCU_INT_HXTALSTBIF              BIT(3)                    /*!< HXTAL stabilization interrupt flag */
#define RCU_INT_PLLSTBIF                BIT(4)                    /*!< PLL stabilization interrupt flag */
#define RCU_INT_CKMIF                   BIT(7)                    /*!< HXTAL clock stuck interrupt flag */
#define RCU_INT_IRC32KSTBIE             BIT(8)                    /*!< IRC32K stabilization interrupt enable */
#define RCU_INT_LXTALSTBIE              BIT(9)                    /*!< LXTAL stabilization interrupt enable */
#define RCU_INT_IRC8MSTBIE              BIT(10)                   /*!< IRC8M stabilization interrupt enable */
#define RCU_INT_HXTALSTBIE              BIT(11)                   /*!< HXTAL stabilization interrupt enable */
#define RCU_INT_PLLSTBIE                BIT(12)                   /*!< PLL stabilization interrupt enable */
#define RCU_INT_IRC32KSTBIC             BIT(16)                   /*!< IRC32K stabilization interrupt clear */
#define RCU_INT_LXTALSTBIC              BIT(17)                   /*!< LXTAL stabilization interrupt clear */
#define RCU_INT_IRC8MSTBIC              BIT(18)                   /*!< IRC8M stabilization interrupt clear */
#define RCU_INT_HXTALSTBIC              BIT(19)                   /*!< HXTAL stabilization interrupt clear */
#define RCU_INT_PLLSTBIC                BIT(20)                   /*!< PLL stabilization interrupt clear */
#define RCU_INT_CKMIC                   BIT(23)                   /*!< HXTAL clock Stuck interrupt clear */
#define RCU_INT_LCKMIF                  BIT(27)                   /*!< LXTAL clock stuck interrupt flag */
#define RCU_INT_LCKMIC                  BIT(28)                   /*!< LXTAL clock stuck interrupt clear */

/* RCU_AHB1RST */
#define RCU_AHB1RST_CRCRST              BIT(12)                   /*!< CRC reset */ 
#define RCU_AHB1RST_CLARST              BIT(15)                   /*!< CLA reset */ 
#define RCU_AHB1RST_DMA0RST             BIT(21)                   /*!< DMA0 reset */
#define RCU_AHB1RST_DMA1RST             BIT(22)                   /*!< DMA1 reset */
#define RCU_AHB1RST_DMAMUXRST           BIT(23)                   /*!< DMAMUX reset */
#define RCU_AHB1RST_FFTRST              BIT(31)                   /*!< FFT reset */

/* RCU_AHB2RST */
#define RCU_AHB2RST_FACRST              BIT(1)                    /*!< FAC reset */
#define RCU_AHB2RST_CAURST              BIT(3)                    /*!< CAU reset */
#define RCU_AHB2RST_TRNGRST             BIT(6)                    /*!< TRNG reset */
#define RCU_AHB2RST_TMURST              BIT(7)                    /*!< TMU reset */
#define RCU_AHB2RST_PARST               BIT(17)                   /*!< GPIOA reset */
#define RCU_AHB2RST_PBRST               BIT(18)                   /*!< GPIOB reset */
#define RCU_AHB2RST_PCRST               BIT(19)                   /*!< GPIOC reset */
#define RCU_AHB2RST_PDRST               BIT(20)                   /*!< GPIOD reset */
#define RCU_AHB2RST_PERST               BIT(21)                   /*!< GPIOE reset */
#define RCU_AHB2RST_PFRST               BIT(22)                   /*!< GPIOF reset */
#define RCU_AHB2RST_PGRST               BIT(23)                   /*!< GPIOG reset */

/* RCU_AHB3RST */
#define RCU_AHB3RST_EXMCRST             BIT(0)                    /*!< EXMC reset */
#define RCU_AHB3RST_QSPIRST             BIT(1)                    /*!< QSPI reset */

/* RCU_APB1RST */
#define RCU_APB1RST_TIMER1RST           BIT(0)                    /*!< TIMER1 reset */
#define RCU_APB1RST_TIMER2RST           BIT(1)                    /*!< TIMER2 reset */
#define RCU_APB1RST_TIMER3RST           BIT(2)                    /*!< TIMER3 reset */
#define RCU_APB1RST_TIMER4RST           BIT(3)                    /*!< TIMER4 reset */
#define RCU_APB1RST_TIMER5RST           BIT(4)                    /*!< TIMER5 reset */
#define RCU_APB1RST_TIMER6RST           BIT(5)                    /*!< TIMER6 reset */
#define RCU_APB1RST_LPTIMERRST          BIT(9)                    /*!< LPTIMER timer reset */
#define RCU_APB1RST_WWDGTRST            BIT(11)                   /*!< WWDGT reset */
#define RCU_APB1RST_SPI1RST             BIT(14)                   /*!< SPI1 reset */
#define RCU_APB1RST_SPI2RST             BIT(15)                   /*!< SPI2 reset */
#define RCU_APB1RST_USART1RST           BIT(17)                   /*!< USART1 reset */
#define RCU_APB1RST_USART2RST           BIT(18)                   /*!< USART2 reset */
#define RCU_APB1RST_UART3RST            BIT(19)                   /*!< UART3 reset */
#define RCU_APB1RST_UART4RST            BIT(20)                   /*!< UART4 reset */
#define RCU_APB1RST_I2C0RST             BIT(21)                   /*!< I2C0 reset */
#define RCU_APB1RST_I2C1RST             BIT(22)                   /*!< I2C1 reset */
#define RCU_APB1RST_I2C2RST             BIT(23)                   /*!< I2C2 reset */
#define RCU_APB1RST_I2C3RST             BIT(24)                   /*!< I2C3 reset */
#define RCU_APB1RST_PMURST              BIT(28)                   /*!< PMU reset */

/* RCU_APB2RST */
#define RCU_APB2RST_TIMER0RST           BIT(0)                    /*!< TIMER0 reset */
#define RCU_APB2RST_TIMER7RST           BIT(1)                    /*!< TIMER7 reset */
#define RCU_APB2RST_VREFRST             BIT(2)                    /*!< VREF reset */
#define RCU_APB2RST_CMPRST              BIT(3)                    /*!< CMP reset */
#define RCU_APB2RST_USART0RST           BIT(4)                    /*!< USART0 reset */
#define RCU_APB2RST_CAN0RST             BIT(8)                    /*!< CAN0 reset */
#define RCU_APB2RST_CAN1RST             BIT(9)                    /*!< CAN1 reset */
#define RCU_APB2RST_CAN2RST             BIT(10)                   /*!< CAN2 reset */
#define RCU_APB2RST_SPI0RST             BIT(12)                   /*!< SPI0 reset */
#define RCU_APB2RST_SYSCFGRST           BIT(14)                   /*!< SYSCFG reset */
#define RCU_APB2RST_TIMER19RST          BIT(15)                   /*!< TIMER19 reset */
#define RCU_APB2RST_TIMER14RST          BIT(16)                   /*!< TIMER14 reset */
#define RCU_APB2RST_TIMER15RST          BIT(17)                   /*!< TIMER15 reset */
#define RCU_APB2RST_TIMER16RST          BIT(18)                   /*!< TIMER16 reset */
#define RCU_APB2RST_HPDFRST             BIT(19)                   /*!< HPDF reset */
#define RCU_APB2RST_HRTIMERRST          BIT(29)                   /*!< HRTIMER reset */
#define RCU_APB2RST_TRIGSELRST          BIT(31)                   /*!< TRIGSEL reset */

/* RCU_APB3RST */
#define RCU_APB3RST_ADC0RST             BIT(8)                    /*!< ADC0 reset */
#define RCU_APB3RST_ADC1RST             BIT(9)                    /*!< ADC1 reset */
#define RCU_APB3RST_ADC2RST             BIT(10)                   /*!< ADC2 reset */
#define RCU_APB3RST_ADC3RST             BIT(11)                   /*!< ADC3 reset */
#define RCU_APB3RST_DACHOLDRST          BIT(16)                   /*!< DACHOLD reset */
#define RCU_APB3RST_DAC0RST             BIT(17)                   /*!< DAC0 reset */
#define RCU_APB3RST_DAC1RST             BIT(18)                   /*!< DAC1 reset */
#define RCU_APB3RST_DAC2RST             BIT(19)                   /*!< DAC2 reset */
#define RCU_APB3RST_DAC3RST             BIT(20)                   /*!< DAC3 reset */

/* RCU_AHB1EN */
#define RCU_AHB1EN_CRCEN                BIT(12)                   /*!< CRC clock enable */ 
#define RCU_AHB1EN_CLAEN                BIT(15)                   /*!< CLA clock enable */ 
#define RCU_AHB1EN_DMA0EN               BIT(21)                   /*!< DMA0 clock enable */
#define RCU_AHB1EN_DMA1EN               BIT(22)                   /*!< DMA1 clock enable */
#define RCU_AHB1EN_DMAMUXEN             BIT(23)                   /*!< DMAMUX clock enable */
#define RCU_AHB1EN_FFTEN                BIT(31)                   /*!< FFT clock enable */

/* RCU_AHB2EN */
#define RCU_AHB2EN_FACEN                BIT(1)                    /*!< FAC clock enable */
#define RCU_AHB2EN_CAUEN                BIT(3)                    /*!< CAU clock enable */
#define RCU_AHB2EN_TRNGEN               BIT(6)                    /*!< TRNG clock enable */
#define RCU_AHB2EN_TMUEN                BIT(7)                    /*!< TMU clock enable */
#define RCU_AHB2EN_PAEN                 BIT(17)                   /*!< GPIOA clock enable */
#define RCU_AHB2EN_PBEN                 BIT(18)                   /*!< GPIOB clock enable */
#define RCU_AHB2EN_PCEN                 BIT(19)                   /*!< GPIOC clock enable */
#define RCU_AHB2EN_PDEN                 BIT(20)                   /*!< GPIOD clock enable */
#define RCU_AHB2EN_PEEN                 BIT(21)                   /*!< GPIOE clock enable */
#define RCU_AHB2EN_PFEN                 BIT(22)                   /*!< GPIOF clock enable */
#define RCU_AHB2EN_PGEN                 BIT(23)                   /*!< GPIOG clock enable */

/* RCU_AHB3EN */
#define RCU_AHB3EN_EXMCEN               BIT(0)                    /*!< EXMC clock enable */
#define RCU_AHB3EN_QSPIEN               BIT(1)                    /*!< QSPI clock enable */

/* RCU_APB1EN */
#define RCU_APB1EN_TIMER1EN             BIT(0)                    /*!< TIMER1 clock enable */
#define RCU_APB1EN_TIMER2EN             BIT(1)                    /*!< TIMER2 clock enable */
#define RCU_APB1EN_TIMER3EN             BIT(2)                    /*!< TIMER3 clock enable */
#define RCU_APB1EN_TIMER4EN             BIT(3)                    /*!< TIMER4 clock enable */
#define RCU_APB1EN_TIMER5EN             BIT(4)                    /*!< TIMER5 clock enable */
#define RCU_APB1EN_TIMER6EN             BIT(5)                    /*!< TIMER6 clock enable */
#define RCU_APB1EN_LPTIMEREN            BIT(9)                    /*!< LPTIMER timer clock enable */
#define RCU_APB1EN_WWDGTEN              BIT(11)                   /*!< WWDGT clock enable */
#define RCU_APB1EN_SPI1EN               BIT(14)                   /*!< SPI1 clock enable */
#define RCU_APB1EN_SPI2EN               BIT(15)                   /*!< SPI2 clock enable */
#define RCU_APB1EN_USART1EN             BIT(17)                   /*!< USART1 clock enable */
#define RCU_APB1EN_USART2EN             BIT(18)                   /*!< USART2 clock enable */
#define RCU_APB1EN_UART3EN              BIT(19)                   /*!< UART3 clock enable */
#define RCU_APB1EN_UART4EN              BIT(20)                   /*!< UART4 clock enable */
#define RCU_APB1EN_I2C0EN               BIT(21)                   /*!< I2C0 clock enable */
#define RCU_APB1EN_I2C1EN               BIT(22)                   /*!< I2C1 clock enable */
#define RCU_APB1EN_I2C2EN               BIT(23)                   /*!< I2C2 clock enable */
#define RCU_APB1EN_I2C3EN               BIT(24)                   /*!< I2C3 clock enable */
#define RCU_APB1EN_PMUEN                BIT(28)                   /*!< PMU clock enable */

/* RCU_APB2EN */
#define RCU_APB2EN_TIMER0EN             BIT(0)                    /*!< TIMER0 clock enable */
#define RCU_APB2EN_TIMER7EN             BIT(1)                    /*!< TIMER7 clock enable */
#define RCU_APB2EN_VREFEN               BIT(2)                    /*!< VREF clock enable */
#define RCU_APB2EN_CMPEN                BIT(3)                    /*!< CMP clock enable */
#define RCU_APB2EN_USART0EN             BIT(4)                    /*!< USART0 clock enable */
#define RCU_APB2EN_CAN0EN               BIT(8)                    /*!< CAN0 clock enable */
#define RCU_APB2EN_CAN1EN               BIT(9)                    /*!< CAN1 clock enable */
#define RCU_APB2EN_CAN2EN               BIT(10)                   /*!< CAN2 clock enable */
#define RCU_APB2EN_SPI0EN               BIT(12)                   /*!< SPI0 clock enable */
#define RCU_APB2EN_SYSCFGEN             BIT(14)                   /*!< SYSCFG clock enable */
#define RCU_APB2EN_TIMER19EN            BIT(15)                   /*!< TIMER19 clock enable */
#define RCU_APB2EN_TIMER14EN            BIT(16)                   /*!< TIMER14 clock enable */
#define RCU_APB2EN_TIMER15EN            BIT(17)                   /*!< TIMER15 clock enable */
#define RCU_APB2EN_TIMER16EN            BIT(18)                   /*!< TIMER16 clock enable */
#define RCU_APB2EN_HPDFEN               BIT(19)                   /*!< HPDF clock enable */
#define RCU_APB2EN_HRTIMEREN           BIT(29)                    /*!< HRTIMER clock enable */
#define RCU_APB2EN_TRIGSELEN            BIT(31)                   /*!< TRIGSEL clock enable */

/* RCU_APB3EN */
#define RCU_APB3EN_ADC0EN               BIT(8)                    /*!< ADC0 clock enable */
#define RCU_APB3EN_ADC1EN               BIT(9)                    /*!< ADC1 clock enable */
#define RCU_APB3EN_ADC2EN               BIT(10)                   /*!< ADC2 clock enable */
#define RCU_APB3EN_ADC3EN               BIT(11)                   /*!< ADC3 clock enable */
#define RCU_APB3EN_DACHOLDEN            BIT(16)                   /*!< DACHOLD clock enable */
#define RCU_APB3EN_DAC0EN               BIT(17)                   /*!< DAC0 clock enable */
#define RCU_APB3EN_DAC1EN               BIT(18)                   /*!< DAC1 clock enable */
#define RCU_APB3EN_DAC2EN               BIT(19)                   /*!< DAC2 clock enable */
#define RCU_APB3EN_DAC3EN               BIT(20)                   /*!< DAC3 clock enable */

/* RCU_AHB1SPDPEN */
#define RCU_AHB1SPDPEN_FMCSPDPEN        BIT(8)                    /*!< FMC clock enable when sleep and deep-sleep mode */
#define RCU_AHB1SPDPEN_CRCSPDPEN        BIT(12)                   /*!< CRC clock enable when sleep and deep-sleep mode */
#define RCU_AHB1SPDPEN_CLASPDPEN        BIT(15)                   /*!< CLA clock enable when sleep and deep-sleep mode */
#define RCU_AHB1SPDPEN_SRAM0SPDPEN      BIT(16)                   /*!< SRAM0 clock enable when sleep and deep-sleep mode */
#define RCU_AHB1SPDPEN_SRAM1SPDPEN      BIT(17)                   /*!< SRAM1 clock enable when sleep and deep-sleep mode */
#define RCU_AHB1SPDPEN_TCMSAMSPDPEN     BIT(19)                   /*!< TCMSRAM clock enable when sleep and deep-sleep mode */
#define RCU_AHB1SPDPEN_DMA0SPDPEN       BIT(21)                   /*!< DMA0 clock enable when sleep and deep-sleep mode */
#define RCU_AHB1SPDPEN_DMA1SPDPEN       BIT(22)                   /*!< DMA1 clock enable when sleep and deep-sleep mode */
#define RCU_AHB1SPDPEN_DMAMUXSPDPEN     BIT(23)                   /*!< DMAMUX clock enable when sleep and deep-sleep mode */
#define RCU_AHB1SPDPEN_FFTSPDPEN        BIT(31)                   /*!< FFT clock enable when sleep and deep-sleep mode */

/* RCU_AHB2SPDPEN */
#define RCU_AHB2SPDPEN_FACSPDPEN        BIT(1)                    /*!< FAC clock enable when sleep and deep-sleep mode */
#define RCU_AHB2SPDPEN_CAUSPDPEN        BIT(3)                    /*!< CAU clock enable when sleep and deep-sleep mode */
#define RCU_AHB2SPDPEN_TRNGSPDPEN       BIT(6)                    /*!< TRNG clock enable when sleep and deep-sleep mode */
#define RCU_AHB2SPDPEN_TMUSPDPEN        BIT(7)                    /*!< TMU clock enable when sleep and deep-sleep mode */
#define RCU_AHB2SPDPEN_PASPDPEN         BIT(17)                   /*!< GPIOA clock enable when sleep and deep-sleep mode */
#define RCU_AHB2SPDPEN_PBSPDPEN         BIT(18)                   /*!< GPIOB clock enable when sleep and deep-sleep mode */
#define RCU_AHB2SPDPEN_PCSPDPEN         BIT(19)                   /*!< GPIOC clock enable when sleep and deep-sleep mode */
#define RCU_AHB2SPDPEN_PDSPDPEN         BIT(20)                   /*!< GPIOD clock enable when sleep and deep-sleep mode */
#define RCU_AHB2SPDPEN_PESPDPEN         BIT(21)                   /*!< GPIOE clock enable when sleep and deep-sleep mode */
#define RCU_AHB2SPDPEN_PFSPDPEN         BIT(22)                   /*!< GPIOF clock enable when sleep and deep-sleep mode */
#define RCU_AHB2SPDPEN_PGSPDPEN         BIT(23)                   /*!< GPIOG clock enable when sleep and deep-sleep mode */

/* RCU_AHB3SPDPEN */
#define RCU_AHB3SPDPEN_EXMCSPDPEN       BIT(0)                    /*!< EXMC clock enable when sleep and deep-sleep mode */
#define RCU_AHB3SPDPEN_QSPISPDPEN       BIT(1)                    /*!< QSPI clock enable when sleep and deep-sleep mode */

/* RCU_APB1SPDPEN */
#define RCU_APB1SPDPEN_TIMER1SPDPEN     BIT(0)                    /*!< TIMER1 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_TIMER2SPDPEN     BIT(1)                    /*!< TIMER2 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_TIMER3SPDPEN     BIT(2)                    /*!< TIMER3 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_TIMER4SPDPEN     BIT(3)                    /*!< TIMER4 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_TIMER5SPDPEN     BIT(4)                    /*!< TIMER5 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_TIMER6SPDPEN     BIT(5)                    /*!< TIMER6 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_LPTIMERSPDPEN    BIT(9)                    /*!< LPTIMER timer clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_WWDGTSPDPEN      BIT(11)                   /*!< WWDGT clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_SPI1SPDPEN       BIT(14)                   /*!< SPI1 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_SPI2SPDPEN       BIT(15)                   /*!< SPI2 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_USART1SPDPEN     BIT(17)                   /*!< USART1 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_USART2SPDPEN     BIT(18)                   /*!< USART2 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_UART3SPDPEN      BIT(19)                   /*!< UART3 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_UART4SPDPEN      BIT(20)                   /*!< UART4 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_I2C0SPDPEN       BIT(21)                   /*!< I2C0 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_I2C1SPDPEN       BIT(22)                   /*!< I2C1 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_I2C2SPDPEN       BIT(23)                   /*!< I2C2 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_I2C3SPDPEN       BIT(24)                   /*!< I2C3 clock enable when sleep and deep-sleep mode */
#define RCU_APB1SPDPEN_PMUSPDPEN        BIT(28)                   /*!< PMU clock enable when sleep and deep-sleep mode */

/* RCU_APB2SPDPEN */
#define RCU_APB2SPDPEN_TIMER0SPDPEN     BIT(0)                    /*!< TIMER0 clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_TIMER7SPDPEN     BIT(1)                    /*!< TIMER7 clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_VREFSPDPEN       BIT(2)                    /*!< VREF clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_CMPSPDPEN        BIT(3)                    /*!< CMP clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_USART0SPDPEN     BIT(4)                    /*!< USART0 clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_CAN0SPDPEN       BIT(8)                    /*!< CAN0 clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_CAN1SPDPEN       BIT(9)                    /*!< CAN1 clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_CAN2SPDPEN       BIT(10)                   /*!< CAN2 clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_SPI0SPDPEN       BIT(12)                   /*!< SPI0 clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_SYSCFGSPDPEN     BIT(14)                   /*!< SYSCFG clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_TIMER19SPDPEN    BIT(15)                   /*!< TIMER19 clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_TIMER14SPDPEN    BIT(16)                   /*!< TIMER14 clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_TIMER15SPDPEN    BIT(17)                   /*!< TIMER15 clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_TIMER16SPDPEN    BIT(18)                   /*!< TIMER16 clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_HPDFSPDPEN       BIT(19)                   /*!< HPDF clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_HRTIMERSPDPEN    BIT(29)                   /*!< HRTIMER clock enable when sleep and deep-sleep mode */
#define RCU_APB2SPDPEN_TRIGSELSPDPEN    BIT(31)                   /*!< TRIGSEL clock enable when sleep and deep-sleep mode */

/* RCU_APB3SPDPEN */
#define RCU_APB3SPDPEN_ADC0SPDPEN       BIT(8)                    /*!< ADC0 clock enable when sleep and deep-sleep mode */
#define RCU_APB3SPDPEN_ADC1SPDPEN       BIT(9)                    /*!< ADC1 clock enable when sleep and deep-sleep mode */
#define RCU_APB3SPDPEN_ADC2SPDPEN       BIT(10)                   /*!< ADC2 clock enable when sleep and deep-sleep mode */
#define RCU_APB3SPDPEN_ADC3SPDPEN       BIT(11)                   /*!< ADC3 clock enable when sleep and deep-sleep mode */
#define RCU_APB3SPDPEN_DACHOLDSPDPEN    BIT(16)                   /*!< DACHOLD clock enable when sleep and deep-sleep mode */
#define RCU_APB3SPDPEN_DAC0SPDPEN       BIT(17)                   /*!< DAC0 clock enable when sleep and deep-sleep mode */
#define RCU_APB3SPDPEN_DAC1SPDPEN       BIT(18)                   /*!< DAC1 clock enable when sleep and deep-sleep mode */
#define RCU_APB3SPDPEN_DAC2SPDPEN       BIT(19)                   /*!< DAC2 clock enable when sleep and deep-sleep mode */
#define RCU_APB3SPDPEN_DAC3SPDPEN       BIT(20)                   /*!< DAC3 clock enable when sleep and deep-sleep mode */

/* RCU_BDCTL */
#define RCU_BDCTL_LXTALEN               BIT(0)                    /*!< LXTAL enable */
#define RCU_BDCTL_LXTALSTB              BIT(1)                    /*!< low speed crystal oscillator stabilization flag */
#define RCU_BDCTL_LXTALBPS              BIT(2)                    /*!< LXTAL bypass mode enable */
#define RCU_BDCTL_LXTALDRI              BITS(3,4)                 /*!< LXTAL drive capability */
#define RCU_BDCTL_LCKMEN                BIT(5)                    /*!< LXTAL clock monitor enable */
#define RCU_BDCTL_LCKMD                 BIT(6)                    /*!< LXTAL clock failure detection */
#define RCU_BDCTL_LXTALSTBRST           BIT(7)                    /*!< LXTAL stabilization reset */
#define RCU_BDCTL_RTCSRC                BITS(8,9)                 /*!< RTC clock entry selection */
#define RCU_BDCTL_RTCEN                 BIT(15)                   /*!< RTC clock enable */
#define RCU_BDCTL_BKPRST                BIT(16)                   /*!< backup domain reset */
#define RCU_BDCTL_LSCKOUTEN             BIT(24)                   /*!< Low speed clock output enable */
#define RCU_BDCTL_LSCKOUTSEL            BIT(25)                   /*!< Low speed clock output selection */

/* RCU_RSTSCK */
#define RCU_RSTSCK_IRC32KEN             BIT(0)                    /*!< IRC32K enable */
#define RCU_RSTSCK_IRC32KSTB            BIT(1)                    /*!< IRC32K stabilization flag */
#define RCU_RSTSCK_OBLRSTF              BIT(23)                   /*!< option byte loader reset flag */
#define RCU_RSTSCK_RSTFC                BIT(24)                   /*!< reset flag clear */
#define RCU_RSTSCK_BORRSTF              BIT(25)                   /*!< BOR reset flag */
#define RCU_RSTSCK_EPRSTF               BIT(26)                   /*!< external pin reset flag */
#define RCU_RSTSCK_PORRSTF              BIT(27)                   /*!< power reset flag */
#define RCU_RSTSCK_SWRSTF               BIT(28)                   /*!< software reset flag */
#define RCU_RSTSCK_FWDGTRSTF            BIT(29)                   /*!< free watchdog timer reset flag */
#define RCU_RSTSCK_WWDGTRSTF            BIT(30)                   /*!< window watchdog timer reset flag */
#define RCU_RSTSCK_LPRSTF               BIT(31)                   /*!< low-power reset flag */

/* RCU_CFG1 */
#define RCU_CFG1_USART0SEL              BITS(0,1)                 /*!< USART0 clock selection */
#define RCU_CFG1_CAN0SEL                BITS(8,9)                 /*!< CAN0 clock selection */
#define RCU_CFG1_CAN1SEL                BITS(10,11)               /*!< CAN1 clock selection */
#define RCU_CFG1_CAN2SEL                BITS(12,13)               /*!< CAN2 clock selection */
#define RCU_CFG1_USART1SEL              BITS(18,19)               /*!< USART1 clock selection */
#define RCU_CFG1_USART2SEL              BITS(20,21)               /*!< USART2 clock selection */
#define RCU_CFG1_HPDFAUDIOSEL           BITS(29,30)               /*!< HPDFAUDIO clock selection */
#define RCU_CFG1_HPDFSEL                BIT(31)                   /*!< HPDF clock selection */

/* RCU_CFG2 */
#define RCU_CFG2_I2C0SEL                BITS(0,1)                 /*!< CK_I2C0 clock source selection */
#define RCU_CFG2_I2C1SEL                BITS(2,3)                 /*!< CK_I2C1 clock source selection */
#define RCU_CFG2_I2C2SEL                BITS(4,5)                 /*!< CK_I2C2 clock source selection */
#define RCU_CFG2_I2C3SEL                BITS(6,7)                 /*!< CK_I2C3 clock source selection */
#define RCU_CFG2_LPTIMERSEL             BITS(9,10)                /*!< CK_LPTIMER clock source selection */
#define RCU_CFG2_TRNGPSC                BITS(13,15)               /*!< TRNG prescaler selection */
#define RCU_CFG2_QSPISEL                BITS(16,17)               /*!< CK_USART0 clock source selection */
#define RCU_CFG2_HRTIMERSEL             BIT(19)                   /*!< HRTIMER clock selection */
#define RCU_CFG2_ADC0_1_2SEL            BITS(26,27)               /*!< CK_ADC0/1/2 clock source selection */
#define RCU_CFG2_ADC3SEL                BITS(28,29)               /*!< CK_ADC3 clock source selection */

/* constants definitions */
/* define the peripheral clock enable bit position and its register index offset */
#define RCU_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define RCU_REG_VAL(periph)             (REG32(RCU + ((uint32_t)(periph) >> 6)))
#define RCU_BIT_POS(val)                ((uint32_t)(val) & 0x0000001FU)

/* register offset */
/* peripherals enable */
#define AHB1EN_REG_OFFSET               ((uint32_t)0x00000030U)                     /*!< AHB1 enable register offset */
#define AHB2EN_REG_OFFSET               ((uint32_t)0x00000034U)                     /*!< AHB2 enable register offset */
#define AHB3EN_REG_OFFSET               ((uint32_t)0x00000038U)                     /*!< AHB3 enable register offset */
#define APB1EN_REG_OFFSET               ((uint32_t)0x00000040U)                     /*!< APB1 enable register offset */
#define APB2EN_REG_OFFSET               ((uint32_t)0x00000044U)                     /*!< APB2 enable register offset */
#define APB3EN_REG_OFFSET               ((uint32_t)0x00000048U)                     /*!< APB3 enable register offset */
#define AHB1SPDPEN_REG_OFFSET           ((uint32_t)0x00000050U)                     /*!< AHB1 sleep and deep-sleep mode enable register offset */
#define AHB2SPDPEN_REG_OFFSET           ((uint32_t)0x00000054U)                     /*!< AHB2 sleep and deep-sleep mode enable register offset */
#define AHB3SPDPEN_REG_OFFSET           ((uint32_t)0x00000058U)                     /*!< AHB3 sleep and deep-sleep mode enable register offset */
#define APB1SPDPEN_REG_OFFSET           ((uint32_t)0x00000060U)                     /*!< APB1 sleep and deep-sleep mode enable register offset */
#define APB2SPDPEN_REG_OFFSET           ((uint32_t)0x00000064U)                     /*!< APB2 sleep and deep-sleep mode enable register offset */
#define APB3SPDPEN_REG_OFFSET           ((uint32_t)0x00000068U)                     /*!< APB3 sleep and deep-sleep mode enable register offset */

/* peripherals reset */
#define AHB1RST_REG_OFFSET              ((uint32_t)0x00000010U)                     /*!< AHB1 reset register offset */
#define AHB2RST_REG_OFFSET              ((uint32_t)0x00000014U)                     /*!< AHB2 reset register offset */
#define AHB3RST_REG_OFFSET              ((uint32_t)0x00000018U)                     /*!< AHB3 reset register offset */
#define APB1RST_REG_OFFSET              ((uint32_t)0x00000020U)                     /*!< APB1 reset register offset */
#define APB2RST_REG_OFFSET              ((uint32_t)0x00000024U)                     /*!< APB2 reset register offset */
#define APB3RST_REG_OFFSET              ((uint32_t)0x00000028U)                     /*!< APB3 reset register offset */
#define RSTSCK_REG_OFFSET               ((uint32_t)0x00000074U)                     /*!< reset source/clock register offset */

/* clock control */
#define CTL_REG_OFFSET                  ((uint32_t)0x00000000U)                     /*!< control register offset */
#define BDCTL_REG_OFFSET                ((uint32_t)0x00000070U)                     /*!< backup domain control register offset */

/* clock stabilization and stuck interrupt */
#define INT_REG_OFFSET                  ((uint32_t)0x0000000CU)                     /*!< clock interrupt register offset */

/* configuration register */
#define PLL_REG_OFFSET                  ((uint32_t)0x00000004U)                     /*!< PLL register offset */
#define CFG0_REG_OFFSET                 ((uint32_t)0x00000008U)                     /*!< clock configuration register 0 offset */
#define CFG1_REG_OFFSET                 ((uint32_t)0x0000008CU)                     /*!< clock configuration register 1 offset */
#define CFG2_REG_OFFSET                 ((uint32_t)0x00000090U)                     /*!< clock configuration register 2 offset */

/* peripheral clock enable */
typedef enum
{
    /* AHB1 peripherals */
    RCU_CRC        = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 12U),                        /*!< CRC clock */
    RCU_CLA        = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 15U),                        /*!< CLA clock */
    RCU_DMA0       = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 21U),                        /*!< DMA0 clock */
    RCU_DMA1       = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 22U),                        /*!< DMA1 clock */
    RCU_DMAMUX     = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 23U),                        /*!< DMAMUX clock */
    RCU_FFT        = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 31U),                        /*!< FFT clock */
    /* AHB2 peripherals */
    RCU_FAC        = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 1U),                         /*!< FAC clock */
    RCU_CAU        = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 3U),                         /*!< CAU clock */
    RCU_TRNG       = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 6U),                         /*!< TRNG clock */
    RCU_TMU        = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 7U),                         /*!< TMU clock */
    RCU_GPIOA      = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 17U),                        /*!< GPIOA clock */
    RCU_GPIOB      = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 18U),                        /*!< GPIOB clock */
    RCU_GPIOC      = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 19U),                        /*!< GPIOC clock */
    RCU_GPIOD      = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 20U),                        /*!< GPIOD clock */
    RCU_GPIOE      = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 21U),                        /*!< GPIOE clock */
    RCU_GPIOF      = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 22U),                        /*!< GPIOF clock */
    RCU_GPIOG      = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 23U),                        /*!< GPIOG clock */
    /* AHB3 peripherals */
    RCU_EXMC       = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 0U),                         /*!< EXMC clock */
    RCU_QSPI       = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 1U),                         /*!< QSPI clock */
    /* APB1 peripherals */
    RCU_TIMER1     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 0U),                         /*!< TIMER1 clock */
    RCU_TIMER2     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 1U),                         /*!< TIMER2 clock */
    RCU_TIMER3     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 2U),                         /*!< TIMER3 clock */
    RCU_TIMER4     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 3U),                         /*!< TIMER4 clock */
    RCU_TIMER5     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 4U),                         /*!< TIMER5 clock */
    RCU_TIMER6     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 5U),                         /*!< TIMER6 clock */
    RCU_LPTIMER    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 9U),                         /*!< LPTIMER clock */
    RCU_WWDGT      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 11U),                        /*!< WWDGT clock */
    RCU_SPI1       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 14U),                        /*!< SPI1 clock */
    RCU_SPI2       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 15U),                        /*!< SPI2 clock */
    RCU_USART1     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 17U),                        /*!< USART1 clock */
    RCU_USART2     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 18U),                        /*!< USART2 clock */
    RCU_UART3      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 19U),                        /*!< UART3 clock */
    RCU_UART4      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 20U),                        /*!< UART4 clock */
    RCU_I2C0       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 21U),                        /*!< I2C0 clock */
    RCU_I2C1       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 22U),                        /*!< I2C1 clock */
    RCU_I2C2       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 23U),                        /*!< I2C2 clock */
    RCU_I2C3       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 24U),                        /*!< I2C3 clock */
    RCU_PMU        = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 28U),                        /*!< PMU clock */
    /* APB2 peripherals */
    RCU_TIMER0     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 0U),                         /*!< TIMER0 clock */
    RCU_TIMER7     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 1U),                         /*!< TIMER7 clock */
    RCU_VREF       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 2U),                         /*!< VREF clock */
    RCU_CMP        = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 3U),                         /*!< CMP clock */
    RCU_USART0     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 4U),                         /*!< USART0 clock */
    RCU_CAN0       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 8U),                         /*!< CAN0 clock */
    RCU_CAN1       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 9U),                         /*!< CAN1 clock */
    RCU_CAN2       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 10U),                        /*!< CAN2 clock */
    RCU_SPI0       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 12U),                        /*!< SPI0 clock */
    RCU_SYSCFG     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 14U),                        /*!< SYSCFG clock */
    RCU_TIMER19    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 15U),                        /*!< TIMER19 clock */
    RCU_TIMER14    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 16U),                        /*!< TIMER14 clock */
    RCU_TIMER15    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 17U),                        /*!< TIMER15 clock */
    RCU_TIMER16    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 18U),                        /*!< TIMER16 clock */
    RCU_HPDF       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 19U),                        /*!< HPDF clock */
    RCU_HRTIMER   = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 29U),                         /*!< HRTIMER clock */
    RCU_TRIGSEL     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 31U),                       /*!< TRIGSEL clock */
    /* APB3 peripherals */
    RCU_ADC0       = RCU_REGIDX_BIT(APB3EN_REG_OFFSET, 8U),                         /*!< ADC0 clock */
    RCU_ADC1       = RCU_REGIDX_BIT(APB3EN_REG_OFFSET, 9U),                         /*!< ADC1 clock */
    RCU_ADC2       = RCU_REGIDX_BIT(APB3EN_REG_OFFSET, 10U),                        /*!< ADC2 clock */
    RCU_ADC3       = RCU_REGIDX_BIT(APB3EN_REG_OFFSET, 11U),                        /*!< ADC3 clock */
    RCU_DACHOLD    = RCU_REGIDX_BIT(APB3EN_REG_OFFSET, 16U),                        /*!< DACHOLD clock */
    RCU_DAC0       = RCU_REGIDX_BIT(APB3EN_REG_OFFSET, 17U),                        /*!< DAC0 clock */
    RCU_DAC1       = RCU_REGIDX_BIT(APB3EN_REG_OFFSET, 18U),                        /*!< DAC1 clock */    
    RCU_DAC2       = RCU_REGIDX_BIT(APB3EN_REG_OFFSET, 19U),                        /*!< DAC2 clock */
    RCU_DAC3       = RCU_REGIDX_BIT(APB3EN_REG_OFFSET, 20U),                        /*!< DAC3 clock */
    RCU_RTC        = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 15U)                          /*!< RTC clock */
}rcu_periph_enum;

/* peripheral clock enable when sleep and deep-sleep mode*/
typedef enum
{
    /* AHB1 peripherals */
    RCU_FMC_SLP        = RCU_REGIDX_BIT(AHB1SPDPEN_REG_OFFSET, 8U),                 /*!< FMC clock when sleep and deep-sleep mode */
    RCU_CRC_SLP        = RCU_REGIDX_BIT(AHB1SPDPEN_REG_OFFSET, 12U),                /*!< CRC clock when sleep and deep-sleep mode */
    RCU_CLA_SLP        = RCU_REGIDX_BIT(AHB1SPDPEN_REG_OFFSET, 15U),                /*!< CLA clock when sleep and deep-sleep mode */
    RCU_SRAM0_SLP      = RCU_REGIDX_BIT(AHB1SPDPEN_REG_OFFSET, 16U),                /*!< SRAM0 clock when sleep and deep-sleep mode */
    RCU_SRAM1_SLP      = RCU_REGIDX_BIT(AHB1SPDPEN_REG_OFFSET, 17U),                /*!< SRAM1 clock when sleep and deep-sleep mode */
    RCU_TCMSRAM_SLP    = RCU_REGIDX_BIT(AHB1SPDPEN_REG_OFFSET, 19U),                /*!< TCMSRAM clock when sleep and deep-sleep mode */
    RCU_DMA0_SLP       = RCU_REGIDX_BIT(AHB1SPDPEN_REG_OFFSET, 21U),                /*!< DMA0 clock when sleep and deep-sleep mode */
    RCU_DMA1_SLP       = RCU_REGIDX_BIT(AHB1SPDPEN_REG_OFFSET, 22U),                /*!< DMA1 clock when sleep and deep-sleep mode */
    RCU_DMAMUX_SLP     = RCU_REGIDX_BIT(AHB1SPDPEN_REG_OFFSET, 23U),                /*!< DMAMUX clock when sleep and deep-sleep mode */
    RCU_FFT_SLP        = RCU_REGIDX_BIT(AHB1SPDPEN_REG_OFFSET, 31U),                /*!< FFT clock when sleep and deep-sleep mode */
    /* AHB2 peripherals */
    RCU_FAC_SLP        = RCU_REGIDX_BIT(AHB2SPDPEN_REG_OFFSET, 1U),                 /*!< FAC clock when sleep and deep-sleep mode */
    RCU_CAU_SLP        = RCU_REGIDX_BIT(AHB2SPDPEN_REG_OFFSET, 3U),                 /*!< CAU clock when sleep and deep-sleep mode */
    RCU_TRNG_SLP       = RCU_REGIDX_BIT(AHB2SPDPEN_REG_OFFSET, 6U),                 /*!< TRNG clock when sleep and deep-sleep mode */
    RCU_TMU_SLP        = RCU_REGIDX_BIT(AHB2SPDPEN_REG_OFFSET, 7U),                 /*!< TMU clock when sleep and deep-sleep mode */
    RCU_GPIOA_SLP      = RCU_REGIDX_BIT(AHB2SPDPEN_REG_OFFSET, 17U),                /*!< GPIOA clock when sleep and deep-sleep mode */
    RCU_GPIOB_SLP      = RCU_REGIDX_BIT(AHB2SPDPEN_REG_OFFSET, 18U),                /*!< GPIOB clock when sleep and deep-sleep mode */
    RCU_GPIOC_SLP      = RCU_REGIDX_BIT(AHB2SPDPEN_REG_OFFSET, 19U),                /*!< GPIOC clock when sleep and deep-sleep mode */
    RCU_GPIOD_SLP      = RCU_REGIDX_BIT(AHB2SPDPEN_REG_OFFSET, 20U),                /*!< GPIOD clock when sleep and deep-sleep mode */
    RCU_GPIOE_SLP      = RCU_REGIDX_BIT(AHB2SPDPEN_REG_OFFSET, 21U),                /*!< GPIOE clock when sleep and deep-sleep mode */
    RCU_GPIOF_SLP      = RCU_REGIDX_BIT(AHB2SPDPEN_REG_OFFSET, 22U),                /*!< GPIOF clock when sleep and deep-sleep mode */
    RCU_GPIOG_SLP      = RCU_REGIDX_BIT(AHB2SPDPEN_REG_OFFSET, 23U),                /*!< GPIOG clock when sleep and deep-sleep mode */
    /* AHB3 peripherals */
    RCU_EXMC_SLP       = RCU_REGIDX_BIT(AHB3SPDPEN_REG_OFFSET, 0U),                 /*!< EXMC clock when sleep and deep-sleep mode */
    RCU_QSPI_SLP       = RCU_REGIDX_BIT(AHB3SPDPEN_REG_OFFSET, 1U),                 /*!< QSPI clock when sleep and deep-sleep mode */
    /* APB1 peripherals */
    RCU_TIMER1_SLP     = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 0U),                 /*!< TIMER1 clock when sleep and deep-sleep mode */
    RCU_TIMER2_SLP     = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 1U),                 /*!< TIMER2 clock when sleep and deep-sleep mode */
    RCU_TIMER3_SLP     = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 2U),                 /*!< TIMER3 clock when sleep and deep-sleep mode */
    RCU_TIMER4_SLP     = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 3U),                 /*!< TIMER4 clock when sleep and deep-sleep mode */
    RCU_TIMER5_SLP     = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 4U),                 /*!< TIMER5 clock when sleep and deep-sleep mode */
    RCU_TIMER6_SLP     = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 5U),                 /*!< TIMER6 clock when sleep and deep-sleep mode */
    RCU_LPTIMER_SLP    = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 9U),                 /*!< LPTIMER clock when sleep and deep-sleep mode */
    RCU_WWDGT_SLP      = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 11U),                /*!< WWDGT clock when sleep and deep-sleep mode */
    RCU_SPI1_SLP       = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 14U),                /*!< SPI1 clock when sleep and deep-sleep mode */
    RCU_SPI2_SLP       = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 15U),                /*!< SPI2 clock when sleep and deep-sleep mode */
    RCU_USART1_SLP     = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 17U),                /*!< USART1 clock when sleep and deep-sleep mode */
    RCU_USART2_SLP     = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 18U),                /*!< USART2 clock when sleep and deep-sleep mode */
    RCU_UART3_SLP      = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 19U),                /*!< UART3 clock when sleep and deep-sleep mode */
    RCU_UART4_SLP      = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 20U),                /*!< UART4 clock when sleep and deep-sleep mode */
    RCU_I2C0_SLP       = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 21U),                /*!< I2C0 clock when sleep and deep-sleep mode */
    RCU_I2C1_SLP       = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 22U),                /*!< I2C1 clock when sleep and deep-sleep mode */
    RCU_I2C2_SLP       = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 23U),                /*!< I2C2 clock when sleep and deep-sleep mode */
    RCU_I2C3_SLP       = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 24U),                /*!< I2C3 clock when sleep and deep-sleep mode */
    RCU_PMU_SLP        = RCU_REGIDX_BIT(APB1SPDPEN_REG_OFFSET, 28U),                /*!< PMU clock when sleep and deep-sleep mode */
    /* APB2 peripherals */
    RCU_TIMER0_SLP     = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 0U),                 /*!< TIMER0 clock when sleep and deep-sleep mode */
    RCU_TIMER7_SLP     = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 1U),                 /*!< TIMER7 clock when sleep and deep-sleep mode */
    RCU_VREF_SLP       = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 2U),                 /*!< VREF clock when sleep and deep-sleep mode */
    RCU_CMP_SLP        = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 3U),                 /*!< CMP clock when sleep and deep-sleep mode */
    RCU_USART0_SLP     = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 4U),                 /*!< USART0 clock when sleep and deep-sleep mode */
    RCU_CAN0_SLP       = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 8U),                 /*!< CAN0 clock when sleep and deep-sleep mode */
    RCU_CAN1_SLP       = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 9U),                 /*!< CAN1 clock when sleep and deep-sleep mode */
    RCU_CAN2_SLP       = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 10U),                /*!< CAN2 clock when sleep and deep-sleep mode */
    RCU_SPI0_SLP       = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 12U),                /*!< SPI0 clock when sleep and deep-sleep mode */
    RCU_SYSCFG_SLP     = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 14U),                /*!< SYSCFG clock when sleep and deep-sleep mode */
    RCU_TIMER19_SLP    = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 15U),                /*!< TIMER19 clock when sleep and deep-sleep mode */
    RCU_TIMER14_SLP    = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 16U),                /*!< TIMER14 clock when sleep and deep-sleep mode */
    RCU_TIMER15_SLP    = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 17U),                /*!< TIMER15 clock when sleep and deep-sleep mode */
    RCU_TIMER16_SLP    = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 18U),                /*!< TIMER16 clock when sleep and deep-sleep mode */
    RCU_HPDF_SLP       = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 19U),                /*!< HPDF clock when sleep and deep-sleep mode */
    RCU_HRTIMER_SLP   = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 29U),                 /*!< HRTIMER clock when sleep and deep-sleep mode */
    RCU_TRIGSEL_SLP     = RCU_REGIDX_BIT(APB2SPDPEN_REG_OFFSET, 31U),               /*!< TRIGSEL clock when sleep and deep-sleep mode */
    /* APB3 peripherals */
    RCU_ADC0_SLP       = RCU_REGIDX_BIT(APB3SPDPEN_REG_OFFSET, 8U),                 /*!< ADC0 clock when sleep and deep-sleep mode */
    RCU_ADC1_SLP       = RCU_REGIDX_BIT(APB3SPDPEN_REG_OFFSET, 9U),                 /*!< ADC1 clock when sleep and deep-sleep mode */
    RCU_ADC2_SLP       = RCU_REGIDX_BIT(APB3SPDPEN_REG_OFFSET, 10U),                /*!< ADC2 clock when sleep and deep-sleep mode */
    RCU_ADC3_SLP       = RCU_REGIDX_BIT(APB3SPDPEN_REG_OFFSET, 11U),                /*!< ADC3 clock when sleep and deep-sleep mode */
    RCU_DACHOLD_SLP    = RCU_REGIDX_BIT(APB3SPDPEN_REG_OFFSET, 16U),                /*!< DACHOLD clock when sleep and deep-sleep mode */
    RCU_DAC0_SLP       = RCU_REGIDX_BIT(APB3SPDPEN_REG_OFFSET, 17U),                /*!< DAC0 clock when sleep and deep-sleep mode */
    RCU_DAC1_SLP       = RCU_REGIDX_BIT(APB3SPDPEN_REG_OFFSET, 18U),                /*!< DAC1 clock when sleep and deep-sleep mode */
    RCU_DAC2_SLP       = RCU_REGIDX_BIT(APB3SPDPEN_REG_OFFSET, 19U),                /*!< DAC2 clock when sleep and deep-sleep mode */
    RCU_DAC3_SLP       = RCU_REGIDX_BIT(APB3SPDPEN_REG_OFFSET, 20U)                 /*!< DAC3 clock when sleep and deep-sleep mode */
}rcu_periph_sleep_enum;

/* peripherals reset */
typedef enum
{
    /* AHB1 peripherals */
    RCU_CRCRST        = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 12U),                    /*!< reset CRC */
    RCU_CLARST        = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 15U),                    /*!< reset CLA */
    RCU_DMA0RST       = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 21U),                    /*!< reset DMA0 */
    RCU_DMA1RST       = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 22U),                    /*!< reset DMA1 */
    RCU_DMAMUXRST     = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 23U),                    /*!< reset DMAMUX */
    RCU_FFTRST        = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 31U),                    /*!< reset FFT */
    /* AHB2 peripherals */
    RCU_FACRST        = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 1U),                     /*!< reset FAC */
    RCU_CAURST        = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 3U),                     /*!< reset CAU */
    RCU_TRNGRST       = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 6U),                     /*!< reset TRNG */
    RCU_TMURST        = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 7U),                     /*!< reset TMU */
    RCU_GPIOARST      = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 17U),                    /*!< reset GPIOA */
    RCU_GPIOBRST      = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 18U),                    /*!< reset GPIOB */
    RCU_GPIOCRST      = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 19U),                    /*!< reset GPIOC */
    RCU_GPIODRST      = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 20U),                    /*!< reset GPIOD */
    RCU_GPIOERST      = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 21U),                    /*!< reset GPIOE */
    RCU_GPIOFRST      = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 22U),                    /*!< reset GPIOF */
    RCU_GPIOGRST      = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 23U),                    /*!< reset GPIOG */
    /* AHB3 peripherals */
    RCU_EXMCRST       = RCU_REGIDX_BIT(AHB3RST_REG_OFFSET, 0U),                     /*!< reset EXMC */
    RCU_QSPIRST       = RCU_REGIDX_BIT(AHB3RST_REG_OFFSET, 1U),                     /*!< reset QSPI */
    /* APB1 peripherals */
    RCU_TIMER1RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 0U),                     /*!< reset TIMER1 */
    RCU_TIMER2RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 1U),                     /*!< reset TIMER2 */
    RCU_TIMER3RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 2U),                     /*!< reset TIMER3 */
    RCU_TIMER4RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 3U),                     /*!< reset TIMER4 */
    RCU_TIMER5RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 4U),                     /*!< reset TIMER5 */
    RCU_TIMER6RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 5U),                     /*!< reset TIMER6 */
    RCU_LPTIMERRST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 9U),                     /*!< reset LPTIMER */
    RCU_WWDGTRST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 11U),                    /*!< reset TIMER51 */
    RCU_SPI1RST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 14U),                    /*!< reset SPI1 */
    RCU_SPI2RST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 15U),                    /*!< reset SPI2 */
    RCU_USART1RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 17U),                    /*!< reset USART1 */
    RCU_USART2RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 18U),                    /*!< reset USART2 */
    RCU_UART3RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 19U),                    /*!< reset UART3 */
    RCU_UART4RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 20U),                    /*!< reset UART4 */
    RCU_I2C0RST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 21U),                    /*!< reset I2C0 */
    RCU_I2C1RST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 22U),                    /*!< reset I2C1 */
    RCU_I2C2RST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 23U),                    /*!< reset I2C2 */
    RCU_I2C3RST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 24U),                    /*!< reset I2C3 */
    RCU_PMURST        = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 28U),                    /*!< reset PMU */
    /* APB2 peripherals */
    RCU_TIMER0RST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 0U),                     /*!< reset TIMER0 */
    RCU_TIMER7RST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 1U),                     /*!< reset TIMER7 */
    RCU_VREFRST       = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 2U),                     /*!< reset VREF */
    RCU_CMPRST        = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 3U),                     /*!< reset CMP */
    RCU_USART0RST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 4U),                     /*!< reset USART0 */
    RCU_CAN0RST       = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 8U),                     /*!< reset CAN0 */
    RCU_CAN1RST       = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 9U),                     /*!< reset CAN1 */
    RCU_CAN2RST       = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 10U),                    /*!< reset CAN2 */
    RCU_SPI0RST       = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 12U),                    /*!< reset SPI0 */
    RCU_SYSCFGRST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 14U),                    /*!< reset SYSCFG */
    RCU_TIMER19RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 15U),                    /*!< reset TIMER19 */
    RCU_TIMER14RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 16U),                    /*!< reset TIMER14 */
    RCU_TIMER15RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 17U),                    /*!< reset TIMER15 */
    RCU_TIMER16RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 18U),                    /*!< reset TIMER16 */
    RCU_HPDFRST       = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 19U),                    /*!< reset HPDF */
    RCU_HRTIMERRST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 29U),                    /*!< reset HRTIMER */
    RCU_TRIGSELRST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 31U),                   /*!< reset TRIGSEL */
    /* APB3 peripherals */
    RCU_ADC0RST       = RCU_REGIDX_BIT(APB3RST_REG_OFFSET, 8U),                     /*!< reset ADC0 */
    RCU_ADC1RST       = RCU_REGIDX_BIT(APB3RST_REG_OFFSET, 9U),                     /*!< reset ADC1 */
    RCU_ADC2RST       = RCU_REGIDX_BIT(APB3RST_REG_OFFSET, 10U),                    /*!< reset ADC2 */
    RCU_ADC3RST       = RCU_REGIDX_BIT(APB3RST_REG_OFFSET, 11U),                    /*!< reset ADC3 */
    RCU_DACHOLDRST    = RCU_REGIDX_BIT(APB3RST_REG_OFFSET, 16U),                    /*!< reset DACHOLD */
    RCU_DAC0RST       = RCU_REGIDX_BIT(APB3RST_REG_OFFSET, 17U),                    /*!< reset DAC0 */
    RCU_DAC1RST       = RCU_REGIDX_BIT(APB3RST_REG_OFFSET, 18U),                    /*!< reset DAC1 */
    RCU_DAC2RST       = RCU_REGIDX_BIT(APB3RST_REG_OFFSET, 19U),                    /*!< reset DAC2 */
    RCU_DAC3RST       = RCU_REGIDX_BIT(APB3RST_REG_OFFSET, 20U)                     /*!< reset DAC3 */
}rcu_periph_reset_enum;

/* clock stabilization and peripheral reset flags */
typedef enum
{
    /* clock stabilization flags */
    RCU_FLAG_IRC8MSTB      = RCU_REGIDX_BIT(CTL_REG_OFFSET, 1U),            /*!< IRC8M stabilization flag */
    RCU_FLAG_HXTALSTB      = RCU_REGIDX_BIT(CTL_REG_OFFSET, 17U),           /*!< HXTAL stabilization flag */
    RCU_FLAG_PLLSTB        = RCU_REGIDX_BIT(CTL_REG_OFFSET, 25U),           /*!< PLL stabilization flag */
    RCU_FLAG_LXTALSTB      = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 1U),          /*!< LXTAL stabilization flag */
    RCU_FLAG_IRC32KSTB     = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 1U),         /*!< IRC32K stabilization flag */
    /* reset source flags */
    RCU_FLAG_OBLRST        = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 23U),        /*!< OBL reset flag */
    RCU_FLAG_BORRST        = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 25U),        /*!< BOR reset flag */
    RCU_FLAG_EPRST         = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 26U),        /*!< external PIN reset flag */
    RCU_FLAG_PORRST        = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 27U),        /*!< power reset flag */
    RCU_FLAG_SWRST         = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 28U),        /*!< software reset flag */
    RCU_FLAG_FWDGTRST      = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 29U),        /*!< FWDGT reset flag */
    RCU_FLAG_WWDGTRST      = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 30U),        /*!< WWDGT reset flag */
    RCU_FLAG_LPRST         = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 31U)         /*!< low-power reset flag */
}rcu_flag_enum;

/* clock stabilization and ckm interrupt flags */
typedef enum
{
    RCU_INT_FLAG_IRC32KSTB = RCU_REGIDX_BIT(INT_REG_OFFSET, 0U),            /*!< IRC32K stabilization interrupt flag */
    RCU_INT_FLAG_LXTALSTB  = RCU_REGIDX_BIT(INT_REG_OFFSET, 1U),            /*!< LXTAL stabilization interrupt flag */
    RCU_INT_FLAG_IRC8MSTB  = RCU_REGIDX_BIT(INT_REG_OFFSET, 2U),            /*!< IRC8M stabilization interrupt flag */
    RCU_INT_FLAG_HXTALSTB  = RCU_REGIDX_BIT(INT_REG_OFFSET, 3U),            /*!< HXTAL stabilization interrupt flag */
    RCU_INT_FLAG_PLLSTB    = RCU_REGIDX_BIT(INT_REG_OFFSET, 4U),            /*!< PLL stabilization interrupt flag */
    RCU_INT_FLAG_CKM       = RCU_REGIDX_BIT(INT_REG_OFFSET, 7U),            /*!< HXTAL clock stuck interrupt flag */
    RCU_INT_FLAG_LCKM      = RCU_REGIDX_BIT(INT_REG_OFFSET, 27U)            /*!< LXTAL clock stuck interrupt flag */
}rcu_int_flag_enum;

/* clock stabilization and stuck interrupt flags clear */
typedef enum
{
    RCU_INT_FLAG_IRC32KSTB_CLR = RCU_REGIDX_BIT(INT_REG_OFFSET, 16U),       /*!< IRC32K stabilization interrupt flags clear */
    RCU_INT_FLAG_LXTALSTB_CLR  = RCU_REGIDX_BIT(INT_REG_OFFSET, 17U),       /*!< LXTAL stabilization interrupt flags clear */
    RCU_INT_FLAG_IRC8MSTB_CLR  = RCU_REGIDX_BIT(INT_REG_OFFSET, 18U),       /*!< IRC8M stabilization interrupt flags clear */
    RCU_INT_FLAG_HXTALSTB_CLR  = RCU_REGIDX_BIT(INT_REG_OFFSET, 19U),       /*!< HXTAL stabilization interrupt flags clear */
    RCU_INT_FLAG_PLLSTB_CLR    = RCU_REGIDX_BIT(INT_REG_OFFSET, 20U),       /*!< PLL stabilization interrupt flags clear */
    RCU_INT_FLAG_CKM_CLR       = RCU_REGIDX_BIT(INT_REG_OFFSET, 23U),       /*!< CKM interrupt flags clear */
    RCU_INT_FLAG_LCKM_CLR      = RCU_REGIDX_BIT(INT_REG_OFFSET, 28U)        /*!< LCKM interrupt flags clear */
}rcu_int_flag_clear_enum;

/* clock stabilization interrupt enable or disable */
typedef enum
{
    RCU_INT_IRC32KSTB       = RCU_REGIDX_BIT(INT_REG_OFFSET, 8U),           /*!< IRC32K stabilization interrupt */
    RCU_INT_LXTALSTB        = RCU_REGIDX_BIT(INT_REG_OFFSET, 9U),           /*!< LXTAL stabilization interrupt */
    RCU_INT_IRC8MSTB        = RCU_REGIDX_BIT(INT_REG_OFFSET, 10U),          /*!< IRC8M stabilization interrupt */
    RCU_INT_HXTALSTB        = RCU_REGIDX_BIT(INT_REG_OFFSET, 11U),          /*!< HXTAL stabilization interrupt */
    RCU_INT_PLLSTB          = RCU_REGIDX_BIT(INT_REG_OFFSET, 12U)           /*!< PLL stabilization interrupt */
}rcu_int_enum;

/* oscillator types */
typedef enum
{
    RCU_HXTAL      = RCU_REGIDX_BIT(CTL_REG_OFFSET, 16U),                   /*!< HXTAL */
    RCU_LXTAL      = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 0U),                  /*!< LXTAL */
    RCU_IRC8M      = RCU_REGIDX_BIT(CTL_REG_OFFSET, 0U),                    /*!< IRC8M */
    RCU_IRC32K     = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 0U),                 /*!< IRC32K */
    RCU_PLL_CK     = RCU_REGIDX_BIT(CTL_REG_OFFSET, 24U)                    /*!< PLL */
}rcu_osci_type_enum;

/* rcu clock frequency */
typedef enum
{
    CK_SYS      = 0,                                                        /*!< system clock */
    CK_AHB,                                                                 /*!< AHB clock */
    CK_APB1,                                                                /*!< APB1 clock */
    CK_APB2,                                                                /*!< APB2 clock */
    CK_APB3,                                                                /*!< APB3 clock */
    CK_PLLP,                                                                /*!< PLLP clock */
    CK_PLLR,                                                                /*!< PLLR clock */
    CK_PLLQ,                                                                /*!< PLLQ clock */
    CK_USART0,                                                              /*!< USART0 clock */ 
    CK_USART1,                                                              /*!< USART1 clock */ 
    CK_USART2                                                               /*!< USART2 clock */ 
}rcu_clock_freq_enum;

typedef enum {
    IDX_USART0 = 0U,                                                        /*!< idnex of USART0 */
    IDX_USART1,                                                             /*!< idnex of USART1 */
    IDX_USART2                                                              /*!< idnex of USART2 */
} usart_idx_enum;

typedef enum {
    IDX_I2C0 = 0U,                                                          /*!< idnex of I2C0 */
    IDX_I2C1,                                                               /*!< idnex of I2C1 */
    IDX_I2C2,                                                               /*!< idnex of I2C2 */
    IDX_I2C3                                                                /*!< idnex of I2C3 */
} i2c_idx_enum;                                                             

typedef enum {
    IDX_CAN0 = 0U,                                                          /*!< idnex of CAN0 */
    IDX_CAN1,                                                               /*!< idnex of CAN1 */
    IDX_CAN2                                                                /*!< idnex of CAN2 */
} can_idx_enum;                                                             

typedef enum {
    IDX_ADC0 = 0U,                                                          /*!< idnex of ADC0 */
    IDX_ADC1,                                                               /*!< idnex of ADC1 */
    IDX_ADC2,                                                               /*!< idnex of ADC2 */
    IDX_ADC3                                                                /*!< idnex of ADC3 */
} adc_idx_enum;

/* RCU_CFG0 register bit define */
/* system clock source select */
#define CFG0_SCS(regval)                (BITS(0,1) & ((uint32_t)(regval) << 0))
#define RCU_CKSYSSRC_IRC8M              CFG0_SCS(0)                         /*!< system clock source select IRC8M */
#define RCU_CKSYSSRC_HXTAL              CFG0_SCS(1)                         /*!< system clock source select HXTAL */
#define RCU_CKSYSSRC_PLLP               CFG0_SCS(3)                         /*!< system clock source select PLL */

/* system clock source select status */
#define CFG0_SCSS(regval)               (BITS(2,3) & ((uint32_t)(regval) << 2))
#define RCU_SCSS_IRC8M                  CFG0_SCSS(0)                        /*!< system clock source select IRC8M */
#define RCU_SCSS_HXTAL                  CFG0_SCSS(1)                        /*!< system clock source select HXTAL */
#define RCU_SCSS_PLLP                   CFG0_SCSS(3)                        /*!< system clock source select PLL */

/* AHB prescaler selection */
#define CFG0_AHBPSC(regval)             (BITS(4,7) & ((uint32_t)(regval) << 4))
#define RCU_AHB_CKSYS_DIV1              CFG0_AHBPSC(0)                     /*!< AHB prescaler select CK_SYS */
#define RCU_AHB_CKSYS_DIV2              CFG0_AHBPSC(8)                     /*!< AHB prescaler select CK_SYS/2 */
#define RCU_AHB_CKSYS_DIV4              CFG0_AHBPSC(9)                     /*!< AHB prescaler select CK_SYS/4 */
#define RCU_AHB_CKSYS_DIV8              CFG0_AHBPSC(10)                    /*!< AHB prescaler select CK_SYS/8 */
#define RCU_AHB_CKSYS_DIV16             CFG0_AHBPSC(11)                    /*!< AHB prescaler select CK_SYS/16 */
#define RCU_AHB_CKSYS_DIV64             CFG0_AHBPSC(12)                    /*!< AHB prescaler select CK_SYS/64 */
#define RCU_AHB_CKSYS_DIV128            CFG0_AHBPSC(13)                    /*!< AHB prescaler select CK_SYS/128 */
#define RCU_AHB_CKSYS_DIV256            CFG0_AHBPSC(14)                    /*!< AHB prescaler select CK_SYS/256 */
#define RCU_AHB_CKSYS_DIV512            CFG0_AHBPSC(15)                    /*!< AHB prescaler select CK_SYS/512 */

/* APB1 prescaler selection */
#define CFG0_APB1PSC(regval)            (BITS(10,12) & ((uint32_t)(regval) << 10))
#define RCU_APB1_CKAHB_DIV1             CFG0_APB1PSC(0)                    /*!< APB1 prescaler select CK_AHB */
#define RCU_APB1_CKAHB_DIV2             CFG0_APB1PSC(4)                    /*!< APB1 prescaler select CK_AHB/2 */
#define RCU_APB1_CKAHB_DIV4             CFG0_APB1PSC(5)                    /*!< APB1 prescaler select CK_AHB/4 */
#define RCU_APB1_CKAHB_DIV8             CFG0_APB1PSC(6)                    /*!< APB1 prescaler select CK_AHB/8 */
#define RCU_APB1_CKAHB_DIV16            CFG0_APB1PSC(7)                    /*!< APB1 prescaler select CK_AHB/16 */

/* APB2 prescaler selection */
#define CFG0_APB2PSC(regval)            (BITS(13,15) & ((uint32_t)(regval) << 13))
#define RCU_APB2_CKAHB_DIV1             CFG0_APB2PSC(0)                    /*!< APB2 prescaler select CK_AHB */
#define RCU_APB2_CKAHB_DIV2             CFG0_APB2PSC(4)                    /*!< APB2 prescaler select CK_AHB/2 */
#define RCU_APB2_CKAHB_DIV4             CFG0_APB2PSC(5)                    /*!< APB2 prescaler select CK_AHB/4 */
#define RCU_APB2_CKAHB_DIV8             CFG0_APB2PSC(6)                    /*!< APB2 prescaler select CK_AHB/8 */
#define RCU_APB2_CKAHB_DIV16            CFG0_APB2PSC(7)                    /*!< APB2 prescaler select CK_AHB/16 */

/* APB3 prescaler selection */
#define CFG0_APB3PSC(regval)            (BITS(27,29) & ((uint32_t)(regval) << 27))
#define RCU_APB3_CKAHB_DIV1             CFG0_APB3PSC(0)                    /*!< APB3 prescaler select CK_AHB */
#define RCU_APB3_CKAHB_DIV2             CFG0_APB3PSC(4)                    /*!< APB3 prescaler select CK_AHB/2 */
#define RCU_APB3_CKAHB_DIV4             CFG0_APB3PSC(5)                    /*!< APB3 prescaler select CK_AHB/4 */
#define RCU_APB3_CKAHB_DIV8             CFG0_APB3PSC(6)                    /*!< APB3 prescaler select CK_AHB/8 */
#define RCU_APB3_CKAHB_DIV16            CFG0_APB3PSC(7)                    /*!< APB3 prescaler select CK_AHB/16 */

/* CKOUT clock source selection */
#define CFG0_CKOUTSEL(regval)           (BITS(21,23) & ((uint32_t)(regval) << 21))
#define RCU_CKOUTSRC_IRC32K             CFG0_CKOUTSEL(2)                  /*!< internal 32K RC oscillator clock selected */
#define RCU_CKOUTSRC_LXTAL              CFG0_CKOUTSEL(3)                  /*!< low speed crystal oscillator clock (LXTAL) selected */
#define RCU_CKOUTSRC_CKSYS              CFG0_CKOUTSEL(4)                  /*!< system clock selected */
#define RCU_CKOUTSRC_IRC8M              CFG0_CKOUTSEL(5)                  /*!< internal 8M RC oscillator clock selected */
#define RCU_CKOUTSRC_HXTAL              CFG0_CKOUTSEL(6)                  /*!< high speed crystal oscillator clock (HXTAL) selected */
#define RCU_CKOUTSRC_PLLP               CFG0_CKOUTSEL(7)                  /*!< CK_PLL clock selected */

/* CK_OUT divider */
#define CFG0_CKOUTDIV(regval)           (BITS(24,26) & ((uint32_t)(regval) << 24))
#define RCU_CKOUT_DIV1                  CFG0_CKOUTDIV(0)                  /*!< CK_OUT is divided by 1 */
#define RCU_CKOUT_DIV2                  CFG0_CKOUTDIV(1)                  /*!< CK_OUT is divided by 2 */
#define RCU_CKOUT_DIV4                  CFG0_CKOUTDIV(2)                  /*!< CK_OUT is divided by 4 */
#define RCU_CKOUT_DIV8                  CFG0_CKOUTDIV(3)                  /*!< CK_OUT is divided by 8 */
#define RCU_CKOUT_DIV16                 CFG0_CKOUTDIV(4)                  /*!< CK_OUT is divided by 16 */

/* RCU_PLL register bit define */
/* PLL clock source selection */
#define RCU_PLLSRC_IRC8M                ((uint32_t)0x00000000U)           /*!< HXTAL clock selected as source clock of PLL */
#define RCU_PLLSRC_HXTAL                RCU_PLL_PLLSEL                    /*!< IRC8M selected as source clock of PLL */

/* PLL P/Q/R divider output enable */
#define RCU_PLLP                        RCU_PLL_PLLPEN                    /*!< PLLP divider output enable */
#define RCU_PLLQ                        RCU_PLL_PLLQEN                    /*!< PLLQ divider output enable */
#define RCU_PLLR                        RCU_PLL_PLLREN                    /*!< PLLR divider output enable */

/* The PLL VCO source clock prescaler */
#define RCU_PLLPSC_DIV_MIN              ((uint32_t)1U)                    /*!< PLLPSC_DIV min value */
#define RCU_PLLPSC_DIV_MAX              ((uint32_t)16U)                   /*!< PLLPSC_DIV max value */

/* The PLL VCO clock multiplication factor */
#define RCU_PLLN_MUL_MIN                ((uint32_t)8U)                    /*!< PLLN_MUL min value */
#define RCU_PLLN_MUL_MAX                ((uint32_t)180U)                  /*!< PLLN_MUL max value */

/* The PLLP output frequency division factor from PLL VCO clock */
#define RCU_PLLP_DIV_MIN                ((uint32_t)2U)                    /*!< PLLP_DIV min value */
#define RCU_PLLP_DIV_MAX                ((uint32_t)8U)                    /*!< PLLP_DIV max value */

/* The PLLR output frequency division factor from PLL VCO clock */
#define RCU_PLLR_DIV_MIN                ((uint32_t)2U)                    /*!< PLLR_DIV min value */
#define RCU_PLLR_DIV_MAX                ((uint32_t)31U)                   /*!< PLLR_DIV max value */

/* The PLLQ output frequency division factor from PLL0 VCO clock */
#define RCU_PLLQ_DIV_MIN                ((uint32_t)2U)                    /*!< PLLQ_DIV min value */
#define RCU_PLLQ_DIV_MAX                ((uint32_t)15U)                   /*!< PLLQ_DIV max value */

#define CHECK_PLL_PSC_VALID(val)    (((val) >= RCU_PLLPSC_DIV_MIN)&&((val) <= RCU_PLLPSC_DIV_MAX))
#define CHECK_PLL_N_VALID(val)      (((val) >= RCU_PLLN_MUL_MIN) &&((val) <= RCU_PLLN_MUL_MAX))
#define CHECK_PLL_P_VALID(val)      (((val) >= RCU_PLLP_DIV_MIN)&&((val) <= RCU_PLLP_DIV_MAX))
#define CHECK_PLL_Q_VALID(val)      (((val) >= RCU_PLLQ_DIV_MIN)&&((val) <= RCU_PLLQ_DIV_MAX))
#define CHECK_PLL_R_VALID(val)      (((val) >= RCU_PLLR_DIV_MIN)&&((val) <= RCU_PLLR_DIV_MAX))

/* RCU_BDCTL register bit define */
/* LXTAL drive capability */
#define BDCTL_LXTALDRI(regval)       (BITS(3,4) & ((uint32_t)(regval) << 3U))
#define RCU_LXTAL_LOWDRI             BDCTL_LXTALDRI(0)                               /*!< lower driving capability */
#define RCU_LXTAL_MED_LOWDRI         BDCTL_LXTALDRI(1)                               /*!< medium low driving capability */
#define RCU_LXTAL_MED_HIGHDRI        BDCTL_LXTALDRI(2)                               /*!< medium high driving capability */
#define RCU_LXTAL_HIGHDRI            BDCTL_LXTALDRI(3)                               /*!< higher driving capability */

/* RTC clock entry selection */
#define BDCTL_RTCSRC(regval)            (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define RCU_RTCSRC_NONE                 BDCTL_RTCSRC(0)                              /*!< no clock selected */
#define RCU_RTCSRC_LXTAL                BDCTL_RTCSRC(1)                              /*!< RTC source clock select LXTAL */
#define RCU_RTCSRC_IRC32K               BDCTL_RTCSRC(2)                              /*!< RTC source clock select IRC32K */
#define RCU_RTCSRC_HXTAL_DIV32          BDCTL_RTCSRC(3)                              /*!< RTC source clock select HXTAL/32 */

/* low speed clock output source selection */
#define RCU_LSCKOUTSRC_IRC32K           (uint32_t)(0X00000000U)                      /*!< IRC32K clock selected */
#define RCU_LSCKOUTSRC_LXTAL            RCU_BDCTL_LSCKOUTSEL                         /*!< LXTAL clock selected */

/* RCU_CFG1 register bit define */
/* USARTx(x=0,1,2) clock source selection */
#define CFG1_USART0SEL(regval)          (BITS(0,1) & ((uint32_t)(regval) << 0U))
#define RCU_USARTSRC_APB                CFG1_USART0SEL(0)                            /*!< CK_USART select CK_APB */
#define RCU_USARTSRC_CKSYS              CFG1_USART0SEL(1)                            /*!< CK_USART select CK_SYS */
#define RCU_USARTSRC_LXTAL              CFG1_USART0SEL(2)                            /*!< CK_USART select CK_LXTAL */
#define RCU_USARTSRC_IRC8M              CFG1_USART0SEL(3)                            /*!< CK_USART select CK_IRC8M */

/* CANx(x=0,1,2) clock source selection */
#define CFG1_CAN0SEL(regval)            (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define RCU_CANSRC_IRC8M                CFG1_CAN0SEL(0)                              /*!< CK_CAN select IRC8M */
#define RCU_CANSRC_APB2                 CFG1_CAN0SEL(1)                              /*!< CK_CAN select CK_APB2 */
#define RCU_CANSRC_PLLQ                 CFG1_CAN0SEL(2)                              /*!< CK_CAN select PLLQ */
#define RCU_CANSRC_HXTAL                CFG1_CAN0SEL(3)                              /*!< CK_CAN select CK_HXTAL */

/* HPDF clock source selection */
#define RCU_HPDFSRC_APB2                (uint32_t)(0X00000000U)                      /*!< CK_HPDF select CK_APB2 */
#define RCU_HPDFSRC_AHB                 RCU_CFG1_HPDFSEL                             /*!< CK_HPDF select CK_AHB */

/* HPDF AUDIO clock source selection */
#define CFG1_HPDFAUDIOSEL(regval)       (BITS(29,30) & ((uint32_t)(regval) << 29U))
#define RCU_HPDFAUDIO_PLLQ              CFG1_HPDFAUDIOSEL(0)                         /*!< CK_HPDFAUDIO select IRC8M */
#define RCU_HPDFAUDIO_EHPDFAUDIOPIN     CFG1_HPDFAUDIOSEL(1)                         /*!< CK_HPDFAUDIO select external HPDF_AUDIO pin */
#define RCU_HPDFAUDIO_IRC8M             CFG1_HPDFAUDIOSEL(2)                         /*!< CK_HPDFAUDIO select CK_PLLQ */

/* RCU_CFG2 register bit define */
/* I2Cx(x=0,1,2,3) clock source selection */
#define CFG2_I2C0SRC(regval)            (BITS(0,1) & ((uint32_t)(regval) << 0))
#define RCU_I2CSRC_APB1                 CFG2_I2C0SRC(0)                              /*!< APB1 clock selected as I2C source clock */
#define RCU_I2CSRC_CKSYS                CFG2_I2C0SRC(1)                              /*!< system clock selected as I2C source clock */
#define RCU_I2CSRC_IRC8M                CFG2_I2C0SRC(2)                              /*!< CK_IRC8M clock selected as I2C source clock */

/* LPTIMER clock source selection */
#define CFG2_LPTIMERSEL(regval)         (BITS(9,10) & ((uint32_t)(regval) << 9U))
#define RCU_LPTIMERSRC_APB1             CFG2_LPTIMERSEL(0)                           /*!< CK_LPTIMER select CK_APB1 */
#define RCU_LPTIMERSRC_IRC32K           CFG2_LPTIMERSEL(1)                           /*!< CK_LPTIMER select CK_IRC32K */
#define RCU_LPTIMERSRC_LXTAL            CFG2_LPTIMERSEL(2)                           /*!< CK_LPTIMER select LXTAL */
#define RCU_LPTIMERSRC_IRC8M            CFG2_LPTIMERSEL(3)                           /*!< CK_LPTIMER select IRC8M */

/* TRNG prescaler selection */
#define CFG2_TRNGPSC(regval)            (BITS(12,15) & ((uint32_t)(regval) << 12))
#define RCU_TRNG_CKPLLQ_DIV2            CFG2_TRNGPSC(2)                              /*!< TRNG prescaler select CK_PLLQ/2 */
#define RCU_TRNG_CKPLLQ_DIV3            CFG2_TRNGPSC(3)                              /*!< TRNG prescaler select CK_PLLQ/3 */
#define RCU_TRNG_CKPLLQ_DIV4            CFG2_TRNGPSC(4)                              /*!< TRNG prescaler select CK_PLLQ/4 */
#define RCU_TRNG_CKPLLQ_DIV5            CFG2_TRNGPSC(5)                              /*!< TRNG prescaler select CK_PLLQ/5 */
#define RCU_TRNG_CKPLLQ_DIV6            CFG2_TRNGPSC(6)                              /*!< TRNG prescaler select CK_PLLQ/6 */
#define RCU_TRNG_CKPLLQ_DIV7            CFG2_TRNGPSC(7)                              /*!< TRNG prescaler select CK_PLLQ/7 */
#define RCU_TRNG_CKPLLQ_DIV8            CFG2_TRNGPSC(8)                              /*!< TRNG prescaler select CK_PLLQ/8 */
#define RCU_TRNG_CKPLLQ_DIV9            CFG2_TRNGPSC(9)                              /*!< TRNG prescaler select CK_PLLQ/9 */
#define RCU_TRNG_CKPLLQ_DIV10           CFG2_TRNGPSC(10)                             /*!< TRNG prescaler select CK_PLLQ/10 */
#define RCU_TRNG_CKPLLQ_DIV11           CFG2_TRNGPSC(11)                             /*!< TRNG prescaler select CK_PLLQ/11 */
#define RCU_TRNG_CKPLLQ_DIV12           CFG2_TRNGPSC(12)                             /*!< TRNG prescaler select CK_PLLQ/12 */
#define RCU_TRNG_CKPLLQ_DIV13           CFG2_TRNGPSC(13)                             /*!< TRNG prescaler select CK_PLLQ/13 */
#define RCU_TRNG_CKPLLQ_DIV14           CFG2_TRNGPSC(14)                             /*!< TRNG prescaler select CK_PLLQ/14 */
#define RCU_TRNG_CKPLLQ_DIV15           CFG2_TRNGPSC(15)                             /*!< TRNG prescaler select CK_PLLQ/15 */

/* QSPI clock source selection */       
#define CFG2_QSPISEL(regval)            (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define RCU_QSPISRC_CKSYS               CFG2_QSPISEL(0)                              /*!< CK_QSPI select CK_CKSYS */
#define RCU_QSPISRC_IRC8M               CFG2_QSPISEL(1)                              /*!< CK_QSPI select CK_IRC8M */
#define RCU_QSPISRC_PLLQ                CFG2_QSPISEL(2)                              /*!< CK_QSPI select PLLQ */ 
#define RCU_QSPISRC_PLLR                CFG2_QSPISEL(3)                              /*!< CK_QSPI select PLLR */

/* ADC clock source selection */
#define CFG2_ADC0_1_2SEL(regval)        (BITS(26,27) & ((uint32_t)(regval) << 26U))
#define RCU_ADCSRC_PLLR                 CFG2_ADC0_1_2SEL(1)                          /*!< CK_ADC select CK_PLLR */
#define RCU_ADCSRC_CKSYS                CFG2_ADC0_1_2SEL(2)                          /*!< CK_ADC select IRC8M */

/* HRTIMER clock source selection */
#define RCU_HRTIMERSRC_CKAPB2          ((uint32_t)0x00000000U)                       /*!< APB2 clock selected as HRTIMER source clock */
#define RCU_HRTIMERSRC_CKSYS           RCU_CFG2_HRTIMERSEL                           /*!< system clock selected as HRTIMER source clock */

/* function declarations */
/* deinitialize the RCU */
void rcu_deinit(void);
/* enable the peripherals clock */
void rcu_periph_clock_enable(rcu_periph_enum periph);
/* disable the peripherals clock */
void rcu_periph_clock_disable(rcu_periph_enum periph);
/* enable the peripherals clock when sleep mode */
void rcu_periph_clock_sleep_enable(rcu_periph_sleep_enum periph);
/* disable the peripherals clock when sleep mode */
void rcu_periph_clock_sleep_disable(rcu_periph_sleep_enum periph);
/* reset the peripherals */
void rcu_periph_reset_enable(rcu_periph_reset_enum periph_reset);
/* disable reset the peripheral */
void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset);
/* reset the BKP domain */
void rcu_bkp_reset_enable(void);
/* disable the BKP domain reset */
void rcu_bkp_reset_disable(void);

/* configure the system clock source */
void rcu_system_clock_source_config(uint32_t ck_sys);
/* get the system clock source */
uint32_t rcu_system_clock_source_get(void);
/* configure the AHB prescaler selection */
void rcu_ahb_clock_config(uint32_t ck_ahb);
/* configure the APB1 prescaler selection */
void rcu_apb1_clock_config(uint32_t ck_apb1);
/* configure the APB2 prescaler selection */
void rcu_apb2_clock_config(uint32_t ck_apb2);
/* configure the APB3 prescaler selection */
void rcu_apb3_clock_config(uint32_t ck_apb3);
/* configure the CK_OUT clock source and divider */
void rcu_ckout_config(uint32_t ckout_src, uint32_t ckout_div);
/* enable the low speed clock output */
void rcu_lsckout_enable(void);
/* disable the low speed clock output */
void rcu_lsckout_disable(void);
/* configure the LSCKOUT clock source */
void rcu_lsckout_config(uint32_t lsckout_src);

/* configure the PLLs clock source selection */
void rcu_pll_source_config(uint32_t pll_src);
/* configure the PLL */
ErrStatus rcu_pll_config(uint32_t pll_psc, uint32_t pll_n, uint32_t pll_p, uint32_t pll_q, uint32_t pll_r);
/* enable the pllp pllq pllr divider output */
void rcu_pll_clock_output_enable(uint32_t pllx);
/* disable the pllp pllq pllr divider output */
void rcu_pll_clock_output_disable(uint32_t pllx);
/* configure the RTC clock source selection */
void rcu_rtc_clock_config(uint32_t rtc_clock_source);
/* configure the USARTx(x=0,1,2) clock source selection */
void rcu_usart_clock_config(usart_idx_enum usart_idx, uint32_t ck_usart);
/* configure the I2Cx(x=0,1,2,3) clock source selection */
void rcu_i2c_clock_config(i2c_idx_enum i2c_idx, uint32_t ck_i2c);
/* configure the CANx(x=0,1,2) clock source selection */
void rcu_can_clock_config(can_idx_enum can_idx, uint32_t ck_can);
/* configure the ADCx(x=0,1,2) clock source selection */
void rcu_adc_clock_config(adc_idx_enum adc_idx, uint32_t ck_adc);
/* configure the HPDF clock source selection */
void rcu_hpdf_clock_config(uint32_t ck_hpdf);
/* configure the HPDF AUDIO clock source selection */
void rcu_hpdfaudio_clock_config(uint32_t ck_hpdfaudio);
/* configure the TRNG prescaler selection */
void rcu_trng_clock_config(uint32_t ck_trng);
/* configure the LPTIMER clock source selection */
void rcu_lptimer_clock_config(uint32_t ck_lptimer);
/* configure the QSPI clock source selection */
void rcu_qspi_clock_config(uint32_t ck_qspi);
/* configure the HRTIMER clock source selection */
void rcu_hrtimer_clock_config(uint32_t hrtimer_clock_source);

/* LXTAL, IRC8M, PLLs and other oscillator configure functions */
/* configure the LXTAL drive capability */
void rcu_lxtal_drive_capability_config(uint32_t lxtal_dricap);
/* wait for oscillator stabilization flags is SET or oscillator startup is timeout */
ErrStatus rcu_osci_stab_wait(rcu_osci_type_enum osci);
/* turn on the oscillator */
void rcu_osci_on(rcu_osci_type_enum osci);
/* turn off the oscillator */
void rcu_osci_off(rcu_osci_type_enum osci);
/* enable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it */
void rcu_osci_bypass_mode_enable(rcu_osci_type_enum osci);
/* disable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it */
void rcu_osci_bypass_mode_disable(rcu_osci_type_enum osci);
/* oscillator stabilization reset */
void rcu_osci_stablization_reset(rcu_osci_type_enum osci);
/* set the IRC8M adjust value */
void rcu_irc8m_adjust_value_set(uint32_t irc8M_adjval);

/* clock monitor configure functions */
/* enable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_enable(void);
/* disable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_disable(void);
/* enable the LXTAL clock monitor */
void rcu_lxtal_clock_monitor_enable(void);
/* disable the LXTAL clock monitor */
void rcu_lxtal_clock_monitor_disable(void);

/* clock frequency get functions */
/* get the system clock, bus and peripheral clock frequency */
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock);

/* flag & interrupt functions */
/* get the clock stabilization and peripheral reset flags */
FlagStatus rcu_flag_get(rcu_flag_enum flag);
/* clear the reset flag */
void rcu_all_reset_flag_clear(void);
/* enable the stabilization interrupt */
void rcu_interrupt_enable(rcu_int_enum interrupt);
/* disable the stabilization interrupt */
void rcu_interrupt_disable(rcu_int_enum interrupt);
/* get the clock stabilization interrupt and ckm flags */
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag);
/* clear the interrupt flags */
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag);

#endif /* GD32G5X3_RCU_H */
