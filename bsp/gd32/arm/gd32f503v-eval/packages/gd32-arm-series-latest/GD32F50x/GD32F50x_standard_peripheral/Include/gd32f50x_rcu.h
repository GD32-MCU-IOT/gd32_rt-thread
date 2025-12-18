/*!
    \file    gd32f50x_rcu.h
    \brief   definitions for the RCU

    \version 2025-11-03, V1.0.0, firmware for GD32F50x
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

#ifndef GD32F50X_RCU_H
#define GD32F50X_RCU_H

#include "gd32f50x.h"

/* RCU definitions */
#define RCU                             RCU_BASE                  /*!< RCU base address */

/* registers definitions */
#define RCU_CTL                         REG32(RCU + 0x00U)        /*!< control register */
#define RCU_CFG0                        REG32(RCU + 0x04U)        /*!< clock configuration register 0 */
#define RCU_INT                         REG32(RCU + 0x08U)        /*!< clock interrupt register */
#define RCU_APB2RST                     REG32(RCU + 0x0CU)        /*!< APB2 reset register */
#define RCU_APB1RST                     REG32(RCU + 0x10U)        /*!< APB1 reset register */
#define RCU_AHBEN                       REG32(RCU + 0x14U)        /*!< AHB1 enable register */
#define RCU_APB2EN                      REG32(RCU + 0x18U)        /*!< APB2 enable register */
#define RCU_APB1EN                      REG32(RCU + 0x1CU)        /*!< APB1 enable register */
#define RCU_BDCTL                       REG32(RCU + 0x20U)        /*!< backup domain control register */
#define RCU_RSTSCK                      REG32(RCU + 0x24U)        /*!< reset source / clock register */
#define RCU_AHBRST                      REG32(RCU + 0x28U)        /*!< AHB reset register */
#define RCU_CFG1                        REG32(RCU + 0x2CU)        /*!< clock configuration register 1 */
#define RCU_PLLBWCFG                    REG32(RCU + 0x30U)        /*!< PLL bandwidth configuration register */
#define RCU_DSV                         REG32(RCU + 0x34U)        /*!< deep-sleep mode voltage register */
#define RCU_CKFMCFG0                    REG32(RCU + 0x40U)        /*!< clock frequency monitor configuration register 0 */
#define RCU_CKFMCFG1                    REG32(RCU + 0x44U)        /*!< clock frequency monitor configuration register 1 */
#define RCU_CKFMCFG2                    REG32(RCU + 0x48U)        /*!< clock frequency monitor configuration register 2 */
#define RCU_CKFMCFG3                    REG32(RCU + 0x4CU)        /*!< clock frequency monitor configuration register 3 */
#define RCU_ADDCTL                      REG32(RCU + 0xC0U)        /*!< additional clock control register */
#define RCU_ADDINT                      REG32(RCU + 0xCCU)        /*!< additional clock interrupt register */
#define RCU_ADDAPB1RST                  REG32(RCU + 0xE0U)        /*!< APB1 additional reset register */
#define RCU_ADDAPB1EN                   REG32(RCU + 0xE4U)        /*!< APB1 additional enable register */
#define RCU_LOCK                        REG32(RCU + 0x100U)       /*!< lock register */

/* bits definitions */
/* RCU_CTL */
#define RCU_CTL_IRC8MEN                 BIT(0)                    /*!< internal high speed oscillator enable */
#define RCU_CTL_IRC8MSTB                BIT(1)                    /*!< IRC8M high speed internal oscillator stabilization flag */
#define RCU_CTL_IRC8MADJ                BITS(3,7)                 /*!< high speed internal oscillator clock trim adjust value */
#define RCU_CTL_IRC8MCALIB              BITS(8,15)                /*!< high speed internal oscillator calibration value register */
#define RCU_CTL_HXTALEN                 BIT(16)                   /*!< external high speed oscillator enable */
#define RCU_CTL_HXTALSTB                BIT(17)                   /*!< external crystal oscillator clock stabilization flag */
#define RCU_CTL_HXTALBPS                BIT(18)                   /*!< external crystal oscillator clock bypass mode enable */
#define RCU_CTL_HCKMEN                  BIT(19)                   /*!< HXTAL clock monitor enable */
#define RCU_CTL_PLL0EN                  BIT(24)                   /*!< PLL0 enable */
#define RCU_CTL_PLL0STB                 BIT(25)                   /*!< PLL0 clock stabilization flag */
#define RCU_CTL_PLL1EN                  BIT(26)                   /*!< PLL1 enable */
#define RCU_CTL_PLL1STB                 BIT(27)                   /*!< PLL1 clock stabilization flag */

/* RCU_CFG0 */
#define RCU_CFG0_SCS                    BITS(0,1)                 /*!< system clock switch */
#define RCU_CFG0_SCSS                   BITS(2,3)                 /*!< system clock switch status */
#define RCU_CFG0_AHBPSC                 BITS(4,7)                 /*!< AHB prescaler selection */
#define RCU_CFG0_APB1PSC                BITS(8,10)                /*!< APB1 prescaler selection */
#define RCU_CFG0_APB2PSC                BITS(11,13)               /*!< APB2 prescaler selection */
#define RCU_CFG0_ADCPSC                 BITS(14,15)               /*!< ADC prescaler selection */
#define RCU_CFG0_PREDIV0_LSB            BIT(17)                   /*!< the LSB of PREDIV0 division factor */
#define RCU_CFG0_PLL0MF_0_3             BITS(18,21)               /*!< PLL0 clock multiplication factor bit0 to bit 3*/
#define RCU_CFG0_USBFSPSC               BITS(22,23)               /*!< USBFS clock prescaler selection */
#define RCU_CFG0_CKOUTSEL               BITS(24,26)               /*!< CKOUT clock source selection */
#define RCU_CFG0_ADCPSC_2               BIT(28)                   /*!< bit 2 of ADCPSC */
#define RCU_CFG0_PLL0MF_4_5             BITS(29,30)               /*!< PLL0 clock multiplication factor bit4 to bit 5 */
#define RCU_CFG0_USBFSPSC_2             BIT(31)                   /*!< bit 2 of USBFSPSC */

/* RCU_INT */
#define RCU_INT_IRC40KSTBIF             BIT(0)                    /*!< IRC40K stabilization interrupt flag */
#define RCU_INT_LXTALSTBIF              BIT(1)                    /*!< LXTAL stabilization interrupt flag */
#define RCU_INT_IRC8MSTBIF              BIT(2)                    /*!< IRC8M stabilization interrupt flag */
#define RCU_INT_HXTALSTBIF              BIT(3)                    /*!< HXTAL stabilization interrupt flag */
#define RCU_INT_PLL0STBIF               BIT(4)                    /*!< PLL0 stabilization interrupt flag */
#define RCU_INT_PLL1STBIF               BIT(5)                    /*!< PLL1 stabilization interrupt flag */
#define RCU_INT_HCKMIF                  BIT(7)                    /*!< HXTAL clock stuck interrupt flag */
#define RCU_INT_IRC40KSTBIE             BIT(8)                    /*!< IRC40K stabilization interrupt enable */
#define RCU_INT_LXTALSTBIE              BIT(9)                    /*!< LXTAL stabilization interrupt enable */
#define RCU_INT_IRC8MSTBIE              BIT(10)                   /*!< IRC8M stabilization interrupt enable */
#define RCU_INT_HXTALSTBIE              BIT(11)                   /*!< HXTAL stabilization interrupt enable */
#define RCU_INT_PLL0STBIE               BIT(12)                   /*!< PLL0 stabilization interrupt enable */
#define RCU_INT_PLL1STBIE               BIT(13)                   /*!< PLL1 stabilization interrupt enable */
#define RCU_INT_LCKMIE                  BIT(15)                   /*!< LXTAL clock stuck interrupt enable */
#define RCU_INT_IRC40KSTBIC             BIT(16)                   /*!< IRC40K stabilization interrupt clear */
#define RCU_INT_LXTALSTBIC              BIT(17)                   /*!< LXTAL stabilization interrupt clear */
#define RCU_INT_IRC8MSTBIC              BIT(18)                   /*!< IRC8M stabilization interrupt clear */
#define RCU_INT_HXTALSTBIC              BIT(19)                   /*!< HXTAL stabilization interrupt clear */
#define RCU_INT_PLL0STBIC               BIT(20)                   /*!< PLL0 stabilization interrupt clear */
#define RCU_INT_PLL1STBIC               BIT(21)                   /*!< PLL1 stabilization interrupt clear */
#define RCU_INT_HCKMIC                  BIT(23)                   /*!< HXTAL clock stuck interrupt clear */
#define RCU_INT_LCKMIC                  BIT(24)                   /*!< LXTAL clock stuck interrupt clear */
#define RCU_INT_LCKMIF                  BIT(25)                   /*!< LXTAL clock stuck interrupt flag */

/* RCU_APB2RST */
#define RCU_APB2RST_AFRST               BIT(0)                    /*!< alternate function I/O reset */
#define RCU_APB2RST_PARST               BIT(2)                    /*!< GPIO port A reset */
#define RCU_APB2RST_PBRST               BIT(3)                    /*!< GPIO port B reset */
#define RCU_APB2RST_PCRST               BIT(4)                    /*!< GPIO port C reset */
#define RCU_APB2RST_PDRST               BIT(5)                    /*!< GPIO port D reset */
#define RCU_APB2RST_PERST               BIT(6)                    /*!< GPIO port E reset */
#define RCU_APB2RST_ADC0RST             BIT(9)                    /*!< ADC0 reset */
#define RCU_APB2RST_ADC1RST             BIT(10)                   /*!< ADC1 reset */
#define RCU_APB2RST_TIMER0RST           BIT(11)                   /*!< TIMER0 reset */
#define RCU_APB2RST_SPI0RST             BIT(12)                   /*!< SPI0 reset */
#define RCU_APB2RST_TIMER7RST           BIT(13)                   /*!< TIMER7 reset */
#define RCU_APB2RST_USART0RST           BIT(14)                   /*!< USART0 reset */
#define RCU_APB2RST_ADC2RST             BIT(15)                   /*!< ADC2 reset */
#define RCU_APB2RST_TIMER15RST          BIT(20)                   /*!< TIMER15 reset */
#define RCU_APB2RST_TRIGSELRST          BIT(24)                   /*!< TRIGSEL reset */
#define RCU_APB2RST_SYSCFGRST           BIT(25)                   /*!< SYSCFG reset */
#define RCU_APB2RST_CAN0RST             BIT(26)                   /*!< CAN0 reset */
#define RCU_APB2RST_CAN1RST             BIT(27)                   /*!< CAN1 reset */

/* RCU_APB1RST */
#define RCU_APB1RST_TIMER1RST           BIT(0)                    /*!< TIMER1 reset */
#define RCU_APB1RST_TIMER2RST           BIT(1)                    /*!< TIMER2 reset */
#define RCU_APB1RST_TIMER3RST           BIT(2)                    /*!< TIMER3 reset */
#define RCU_APB1RST_TIMER4RST           BIT(3)                    /*!< TIMER4 reset */
#define RCU_APB1RST_TIMER5RST           BIT(4)                    /*!< TIMER5 reset */
#define RCU_APB1RST_TIMER6RST           BIT(5)                    /*!< TIMER6 reset */
#define RCU_APB1RST_TIMER16RST          BIT(6)                    /*!< TIMER16 reset */
#define RCU_APB1RST_WWDGTRST            BIT(11)                   /*!< WWDGT reset */
#define RCU_APB1RST_SPI1RST             BIT(14)                   /*!< SPI1 reset */
#define RCU_APB1RST_SPI2RST             BIT(15)                   /*!< SPI2 reset */
#define RCU_APB1RST_USART1RST           BIT(17)                   /*!< USART1 reset */
#define RCU_APB1RST_USART2RST           BIT(18)                   /*!< USART2 reset */
#define RCU_APB1RST_UART3RST            BIT(19)                   /*!< UART3 reset */
#define RCU_APB1RST_UART4RST            BIT(20)                   /*!< UART4 reset */
#define RCU_APB1RST_I2C0RST             BIT(21)                   /*!< I2C0 reset */
#define RCU_APB1RST_I2C1RST             BIT(22)                   /*!< I2C1 reset */
#define RCU_APB1RST_CMPRST              BIT(23)                   /*!< CMP reset */
#define RCU_APB1RST_BKPIRST             BIT(27)                   /*!< backup interface reset */
#define RCU_APB1RST_PMURST              BIT(28)                   /*!< PMU reset */
#define RCU_APB1RST_DACRST              BIT(29)                   /*!< DAC reset */

/* RCU_AHBEN */
#define RCU_AHBEN_DMA0EN                BIT(0)                    /*!< DMA0 clock enable */
#define RCU_AHBEN_DMA1EN                BIT(1)                    /*!< DMA1 clock enable */
#define RCU_AHBEN_SRAMSPEN              BIT(2)                    /*!< SRAM clock enable when sleep mode */
#define RCU_AHBEN_FMCSPEN               BIT(4)                    /*!< FMC clock enable when sleep mode */
#define RCU_AHBEN_CRCEN                 BIT(6)                    /*!< CRC clock enable */
#define RCU_AHBEN_EXMCEN                BIT(8)                    /*!< EXMC clock enable */
#define RCU_AHBEN_USBFSEN               BIT(12)                   /*!< USBFS clock enable */
#define RCU_AHBEN_CAUEN                 BIT(16)                   /*!< CAU clock enable */
#define RCU_AHBEN_HAUEN                 BIT(17)                   /*!< HAU clock enable */
#define RCU_AHBEN_TRNGEN                BIT(18)                   /*!< TRNG clock enable */
#define RCU_AHBEN_DMAMUXEN              BIT(19)                   /*!< DMAMUXEN clock enable */

/* RCU_APB2EN */
#define RCU_APB2EN_AFEN                 BIT(0)                    /*!< alternate function IO clock enable */
#define RCU_APB2EN_PAEN                 BIT(2)                    /*!< GPIO port A clock enable */
#define RCU_APB2EN_PBEN                 BIT(3)                    /*!< GPIO port B clock enable */
#define RCU_APB2EN_PCEN                 BIT(4)                    /*!< GPIO port C clock enable */
#define RCU_APB2EN_PDEN                 BIT(5)                    /*!< GPIO port D clock enable */
#define RCU_APB2EN_PEEN                 BIT(6)                    /*!< GPIO port E clock enable */
#define RCU_APB2EN_ADC0EN               BIT(9)                    /*!< ADC0 clock enable */
#define RCU_APB2EN_ADC1EN               BIT(10)                   /*!< ADC1 clock enable */
#define RCU_APB2EN_TIMER0EN             BIT(11)                   /*!< TIMER0 clock enable */
#define RCU_APB2EN_SPI0EN               BIT(12)                   /*!< SPI0 clock enable */
#define RCU_APB2EN_TIMER7EN             BIT(13)                   /*!< TIMER7 clock enable */
#define RCU_APB2EN_USART0EN             BIT(14)                   /*!< USART0 clock enable */
#define RCU_APB2EN_ADC2EN               BIT(15)                   /*!< ADC2 clock enable */
#define RCU_APB2EN_TIMER15EN            BIT(20)                   /*!< TIMER15 clock enable */
#define RCU_APB2EN_TRIGSELEN            BIT(24)                   /*!< TRIGSEL clock enable */
#define RCU_APB2EN_SYSCFGEN             BIT(25)                   /*!< SYSCFG clock enable */
#define RCU_APB2EN_CAN0EN               BIT(26)                   /*!< CAN0 clock enable */
#define RCU_APB2EN_CAN1EN               BIT(27)                   /*!< CAN1 clock enable */

/* RCU_APB1EN */
#define RCU_APB1EN_TIMER1EN             BIT(0)                    /*!< TIMER1 clock enable */
#define RCU_APB1EN_TIMER2EN             BIT(1)                    /*!< TIMER2 clock enable */
#define RCU_APB1EN_TIMER3EN             BIT(2)                    /*!< TIMER3 clock enable */
#define RCU_APB1EN_TIMER4EN             BIT(3)                    /*!< TIMER4 clock enable */
#define RCU_APB1EN_TIMER5EN             BIT(4)                    /*!< TIMER5 clock enable */
#define RCU_APB1EN_TIMER6EN             BIT(5)                    /*!< TIMER6 clock enable */
#define RCU_APB1EN_TIMER16EN            BIT(6)                    /*!< TIMER16 clock enable */
#define RCU_APB1EN_WWDGTEN              BIT(11)                   /*!< WWDGT clock enable */
#define RCU_APB1EN_SPI1EN               BIT(14)                   /*!< SPI1 clock enable */
#define RCU_APB1EN_SPI2EN               BIT(15)                   /*!< SPI2 clock enable */
#define RCU_APB1EN_USART1EN             BIT(17)                   /*!< USART1 clock enable */
#define RCU_APB1EN_USART2EN             BIT(18)                   /*!< USART2 clock enable */
#define RCU_APB1EN_UART3EN              BIT(19)                   /*!< UART3 clock enable */
#define RCU_APB1EN_UART4EN              BIT(20)                   /*!< UART4 clock enable */
#define RCU_APB1EN_I2C0EN               BIT(21)                   /*!< I2C0 clock enable */
#define RCU_APB1EN_I2C1EN               BIT(22)                   /*!< I2C1 clock enable */
#define RCU_APB1EN_CMPEN                BIT(23)                   /*!< CMP clock enable */
#define RCU_APB1EN_BKPIEN               BIT(27)                   /*!< backup interface clock enable */
#define RCU_APB1EN_PMUEN                BIT(28)                   /*!< PMU clock enable */
#define RCU_APB1EN_DACEN                BIT(29)                   /*!< DAC clock enable */

/* RCU_BDCTL */
#define RCU_BDCTL_LXTALEN               BIT(0)                    /*!< LXTAL enable */
#define RCU_BDCTL_LXTALSTB              BIT(1)                    /*!< low speed crystal oscillator stabilization flag */
#define RCU_BDCTL_LXTALBPS              BIT(2)                    /*!< LXTAL bypass mode enable */
#define RCU_BDCTL_LXTALDRI              BITS(3,4)                 /*!< LXTAL drive capability */
#define RCU_BDCTL_LCKMEN                BIT(5)                    /*!< LXTAL clock monitor enable */
#define RCU_BDCTL_LCKMD                 BIT(6)                    /*!< LXTAL clock failure detection */
#define RCU_BDCTL_LXTALRDYRST           BIT(7)                    /*!< LXTAL ready reset */
#define RCU_BDCTL_RTCSRC                BITS(8,9)                 /*!< RTC clock entry selection */
#define RCU_BDCTL_RTCEN                 BIT(15)                   /*!< RTC clock enable */
#define RCU_BDCTL_BKPRST                BIT(16)                   /*!< backup domain reset */

/* RCU_RSTSCK */
#define RCU_RSTSCK_IRC40KEN             BIT(0)                    /*!< IRC40K enable */
#define RCU_RSTSCK_IRC40KSTB            BIT(1)                    /*!< IRC40K stabilization flag */
#define RCU_RSTSCK_RSTFC                BIT(24)                   /*!< reset flag clear */
#define RCU_RSTSCK_EPRSTF               BIT(26)                   /*!< external pin reset flag */
#define RCU_RSTSCK_PORRSTF              BIT(27)                   /*!< power reset flag */
#define RCU_RSTSCK_SWRSTF               BIT(28)                   /*!< software reset flag */
#define RCU_RSTSCK_FWDGTRSTF            BIT(29)                   /*!< free watchdog timer reset flag */
#define RCU_RSTSCK_WWDGTRSTF            BIT(30)                   /*!< window watchdog timer reset flag */
#define RCU_RSTSCK_LPRSTF               BIT(31)                   /*!< low-power reset flag */

/* RCU_AHBRST */
#define RCU_AHBEN_USBFSRST              BIT(12)                   /*!< USBFS reset */
#define RCU_AHBEN_CAURST                BIT(16)                   /*!< CAU reset */
#define RCU_AHBEN_HAURST                BIT(17)                   /*!< HAU reset */
#define RCU_AHBEN_TRNGRST               BIT(18)                   /*!< TRNG reset */
#define RCU_AHBEN_DMAMUXRST             BIT(19)                   /*!< DMAMUXEN reset */
#define RCU_AHBEN_DMA0RST               BIT(20)                   /*!< DMA0 reset */
#define RCU_AHBEN_DMA1RST               BIT(21)                   /*!< DMA1 reset */

/* RCU_CFG1 */
#define RCU_CFG1_PREDIV0                BITS(0,3)                /*!< PREDIV0 division factor */
#define RCU_CFG1_PREDIV1                BITS(4,7)                /*!< PREDIV1 division factor */
#define RCU_CFG1_PLL1MF                 BITS(8,13)               /*!< PLL1 clock multiplication factor */
#define RCU_CFG1_PLL1SEL                BIT(16)                  /*!< PLL1 input clock source selection */
#define RCU_CFG1_I2S1SEL                BIT(17)                  /*!< I2S1 clock source selection */
#define RCU_CFG1_I2S2SEL                BIT(18)                  /*!< I2S2 clock source selection  */
#define RCU_CFG1_HXTALRDYRST            BIT(19)                  /*!< HXTAL ready reset */
#define RCU_CFG1_PLL0SEL                BITS(20,21)              /*!< PLL0 input clock source selection */
#define RCU_CFG1_IRC40KCALIB            BITS(24,28)              /*!< internal 40KHz RC oscillator calibration value register */
#define RCU_CFG1_ADCPSC_3               BIT(29)                  /*!< bit 4 of ADCPSC */

/* RCU_PLLBWCFG */
#define RCU_PLLBWCFG_PLL0_BW_CFG        BITS(0,3)                 /*!< PLL0 bandwidth configuration */
#define RCU_PLLBWCFG_PLL1_BW_CFG        BITS(8,11)                /*!< PLL1 bandwidth configuration */

/* RCU_DSV */
#define RCU_DSV_SWDLY                   BITS(16,20)               /*!< switch delay time */
#define RCU_DSV_DSLPVS                  BITS(0,2)                 /*!< deep-sleep mode voltage select */

/* RCU_CKFMCFG0 */
#define RCU_CKFMCFG0_IRC8MCKFMEN        BIT(0)                    /*!< IRC8M clock frequency monitor enable */
#define RCU_CKFMCFG0_IRC8MCKFMC         BITS(1,2)                 /*!< IRC8M clock frequency monitor configuration */
#define RCU_CKFMCFG0_IRC8MCKFFF         BIT(3)                    /*!< IRC8M clock frequency failure flag */
#define RCU_CKFMCFG0_IRC8MCKFFC         BIT(4)                    /*!< IRC8M clock frequency failure flag clear */
#define RCU_CKFMCFG0_IRC8MCKFFIE        BIT(5)                    /*!< IRC8M clock frequency failure interrupt enable */

/* RCU_CKFMCFG1 */
#define RCU_CKFMCFG1_HXTALCKFMEN        BIT(0)                    /*!< HXTAL clock frequency monitor enable */
#define RCU_CKFMCFG1_HXTALCKFMAX        BITS(1,12)                /*!< HXTAL clock frequency monitor configuration maximum value*/
#define RCU_CKFMCFG1_HXTALCKFMIN        BITS(13,24)               /*!< HXTAL clock frequency monitor configuration minimum value */
#define RCU_CKFMCFG1_HXTALCKFFIE        BIT(25)                   /*!< HXTAL clock frequency failure interrupt enable */
#define RCU_CKFMCFG1_HXTALCKFFF         BIT(30)                   /*!< HXTAL clock frequency failure flag */
#define RCU_CKFMCFG1_HXTALCKFFC         BIT(31)                   /*!< HXTAL clock frequency failure flag clear */

/* RCU_CKFMCFG2 */
#define RCU_CKFMCFG2_PLL0PCKFMEN        BIT(0)                    /*!< PLL0P clock frequency monitor enable */
#define RCU_CKFMCFG2_PLL0PCKFMAX        BITS(1,10)                /*!< PLL0P clock frequency monitor configuration maximum value */
#define RCU_CKFMCFG2_PLL0PCKFMIN        BITS(12,21)               /*!< PLL0P clock frequency monitor configuration minimum value */
#define RCU_CKFMCFG2_PLL0PCKFFIE        BIT(23)                   /*!< PLL0P clock frequency failure interrupt enable */
#define RCU_CKFMCFG2_PLL0PCKFFF         BIT(30)                   /*!< PLL0P clock frequency failure flag */
#define RCU_CKFMCFG2_PLL0PCKFFC         BIT(31)                   /*!< PLL0P clock frequency failure flag clear */

/* RCU_CKFMCFG3 */
#define RCU_CKFMCFG3_PLL1CKFMEN         BIT(0)                    /*!< PLL1 clock frequency monitor enable */
#define RCU_CKFMCFG3_PLL1CKFMAX         BITS(1,10)                /*!< PLL1 clock frequency monitor configuration maximum value */
#define RCU_CKFMCFG3_PLL1CKFMIN         BITS(12,21)               /*!< PLL1 clock frequency monitor configuration minimum value */
#define RCU_CKFMCFG3_PLL1CKFFIE         BIT(23)                   /*!< PLL1 clock frequency failure interrupt enable */
#define RCU_CKFMCFG3_PLL1CKFFF          BIT(30)                   /*!< PLL1 clock frequency failure flag */
#define RCU_CKFMCFG3_PLL1CKFFC          BIT(31)                   /*!< PLL1 clock frequency failure flag clear */

/* RCU_ADDCTL */
#define RCU_ADDCTL_CK48MSEL             BIT(0)                    /*!< 48MHz clock selection */
#define RCU_ADDCTL_FMCSEL               BITS(1,2)                 /*!< FMC clock  selection */
#define RCU_ADDCTL_I2S1DIV              BITS(3,7)                 /*!< I2S1 clock prescaler selection */
#define RCU_ADDCTL_PLL0DIV              BITS(8,11)                /*!< PLL0 clock prescaler selection */
#define RCU_ADDCTL_FMCDIV               BITS(12,15)               /*!< FMC clock prescaler selection */
#define RCU_ADDCTL_IRC48MEN             BIT(16)                   /*!< internal 48MHz RC oscillator enable */
#define RCU_ADDCTL_IRC48MSTB            BIT(17)                   /*!< internal 48MHz RC oscillator clock stabilization flag */
#define RCU_ADDCTL_I2S2DIV              BITS(18,22)               /*!< I2S2 clock prescaler selection */
#define RCU_ADDCTL_IRC48MCAL            BITS(24,31)               /*!< internal 48MHz RC oscillator calibration value register */

/* RCU_ADDINT */
#define RCU_ADDINT_IRC48MSTBIF          BIT(6)                    /*!< IRC48M stabilization interrupt flag */
#define RCU_ADDINT_IRC48MSTBIE          BIT(14)                   /*!< internal 48 MHz RC oscillator stabilization interrupt enable */
#define RCU_ADDINT_IRC48MSTBIC          BIT(22)                   /*!< internal 48 MHz RC oscillator stabilization interrupt clear */

/* RCU_ADDAPB1RST */
#define RCU_ADDAPB1RST_CTCRST           BIT(27)                   /*!< CTC reset */

/* RCU_ADDAPB1EN */
#define RCU_ADDAPB1EN_CTCEN             BIT(27)                   /*!< CTC clock enable */

/* RCU_LOCKREG */
#define RCU_LOCK_LOCK                   BIT(31)                   /*!< RCU register lock bit */

/* constants definitions */
/* define the peripheral clock enable bit position and its register index offset */
#define RCU_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define RCU_REG_VAL(periph)             (REG32(RCU + ((uint32_t)(periph) >> 6)))
#define RCU_BIT_POS(val)                ((uint32_t)(val) & 0x1FU)

/* register offset */
/* peripherals enable */
#define AHBEN_REG_OFFSET                0x14U                     /*!< AHB enable register offset */
#define APB1EN_REG_OFFSET               0x1CU                     /*!< APB1 enable register offset */
#define APB2EN_REG_OFFSET               0x18U                     /*!< APB2 enable register offset */
#define ADD_APB1EN_REG_OFFSET           0xE4U                     /*!< APB1 additional enable register offset */

/* peripherals reset */
#define AHBRST_REG_OFFSET               0x28U                     /*!< AHB reset register offset */
#define APB1RST_REG_OFFSET              0x10U                     /*!< APB1 reset register offset */
#define APB2RST_REG_OFFSET              0x0CU                     /*!< APB2 reset register offset */
#define ADD_APB1RST_REG_OFFSET          0xE0U                     /*!< APB1 additional reset register offset */
#define RSTSCK_REG_OFFSET               0x24U                     /*!< reset source/clock register offset */

/* clock control */
#define CTL_REG_OFFSET                  0x00U                     /*!< control register offset */
#define BDCTL_REG_OFFSET                0x20U                     /*!< backup domain control register offset */
#define ADDCTL_REG_OFFSET               0xC0U                     /*!< additional clock control register offset */

/* clock stabilization and stuck interrupt */
#define INT_REG_OFFSET                  0x08U                     /*!< clock interrupt register offset */
#define ADDINT_REG_OFFSET               0xCCU                     /*!< additional clock interrupt register offset */

/* configuration register */
#define CFG0_REG_OFFSET                 0x04U                     /*!< clock configuration register 0 offset */
#define CFG1_REG_OFFSET                 0x2CU                     /*!< clock configuration register 1 offset */

/* CLKMONITOR register */
#define CKFMCFG0_REG_OFFSET             0x40U                     /*!< CKFMCFG0 register  offset */
#define CKFMCFG1_REG_OFFSET             0x44U                     /*!< CKFMCFG1 register  offset */
#define CKFMCFG2_REG_OFFSET             0x48U                     /*!< CKFMCFG2 register  offset */
#define CKFMCFG3_REG_OFFSET             0x4CU                     /*!< CKFMCFG3 register  offset */

/* peripheral clock enable */
typedef enum {
    /* AHB peripherals */
    RCU_DMA0      = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 0U),                   /*!< DMA0 clock */
    RCU_DMA1      = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 1U),                   /*!< DMA1 clock */
    RCU_CRC       = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 6U),                   /*!< CRC clock */
    RCU_EXMC      = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 8U),                   /*!< EXMC clock */
    RCU_USBFS     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 12U),                  /*!< USBFS clock */
    RCU_CAU       = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 16U),                  /*!< CAU clock */
    RCU_HAU       = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 17U),                  /*!< HAU clock */
    RCU_TRNG      = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 18U),                  /*!< TRNG clock */
    RCU_DMAMUX    = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 19U),                  /*!< DMAMUX clock */

    /* APB1 peripherals */
    RCU_TIMER1    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 0U),                  /*!< TIMER1 clock */
    RCU_TIMER2    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 1U),                  /*!< TIMER2 clock */
    RCU_TIMER3    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 2U),                  /*!< TIMER3 clock */
    RCU_TIMER4    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 3U),                  /*!< TIMER4 clock */
    RCU_TIMER5    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 4U),                  /*!< TIMER5 clock */
    RCU_TIMER6    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 5U),                  /*!< TIMER6 clock */
    RCU_TIMER16   = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 6U),                  /*!< TIMER16 clock */
    RCU_WWDGT     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 11U),                 /*!< WWDGT clock */
    RCU_SPI1      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 14U),                 /*!< SPI1 clock */
    RCU_SPI2      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 15U),                 /*!< SPI2 clock */
    RCU_USART1    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 17U),                 /*!< USART1 clock */
    RCU_USART2    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 18U),                 /*!< USART2 clock */
    RCU_UART3     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 19U),                 /*!< UART3 clock */
    RCU_UART4     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 20U),                 /*!< UART4 clock */
    RCU_I2C0      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 21U),                 /*!< I2C0 clock */
    RCU_I2C1      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 22U),                 /*!< I2C1 clock */
    RCU_CMP       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 23U),                 /*!< CMP clock */
    RCU_BKPI      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 27U),                 /*!< BKPI clock */
    RCU_PMU       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 28U),                 /*!< PMU clock */
    RCU_DAC       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 29U),                 /*!< DAC clock */
    RCU_RTC       = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 15U),                  /*!< RTC clock */
    RCU_CTC       = RCU_REGIDX_BIT(ADD_APB1EN_REG_OFFSET, 27U),             /*!< CTC clock */

    /* APB2 peripherals */
    RCU_AF        = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 0U),                  /*!< alternate function clock */
    RCU_GPIOA     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 2U),                  /*!< GPIOA clock */
    RCU_GPIOB     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 3U),                  /*!< GPIOB clock */
    RCU_GPIOC     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 4U),                  /*!< GPIOC clock */
    RCU_GPIOD     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 5U),                  /*!< GPIOD clock */
    RCU_GPIOE     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 6U),                  /*!< GPIOE clock */
    RCU_ADC0      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 9U),                  /*!< ADC0 clock */
    RCU_ADC1      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 10U),                 /*!< ADC1 clock */
    RCU_TIMER0    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 11U),                 /*!< TIMER0 clock */
    RCU_SPI0      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 12U),                 /*!< SPI0 clock */
    RCU_TIMER7    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 13U),                 /*!< TIMER7 clock */
    RCU_USART0    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 14U),                 /*!< USART0 clock */
    RCU_ADC2      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 15U),                 /*!< ADC2 clock */
    RCU_TIMER15   = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 20U),                 /*!< TIMER15 clock */
    RCU_TRIGSEL   = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 24U),                 /*!< TRIGSEL clock */
    RCU_SYSCFG    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 25U),                 /*!< SYSCFG clock */
    RCU_CAN0      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 26U),                 /*!< CAN0 clock */
    RCU_CAN1      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 27U)                  /*!< CAN1 clock */
} rcu_periph_enum;

/* peripheral clock enable when sleep mode*/
typedef enum {
    /* AHB peripherals */
    RCU_SRAM_SLP     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 2U),                /*!< SRAM interface clock enable when sleep mode */
    RCU_FMC_SLP      = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 4U)                 /*!< FMC clock enable when sleep mode */
} rcu_periph_sleep_enum;

/* peripherals reset */
typedef enum {
    /* AHB peripherals */
    RCU_USBFSRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 12U),              /*!< USBFS clock reset */
    RCU_CAURST       = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 16U),              /*!< CAU clock reset */
    RCU_HAURST       = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 17U),              /*!< HAU clock reset */
    RCU_TRNGRST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 18U),              /*!< TRNG clock reset */
    RCU_DMAMUXRST    = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 19U),              /*!< DMAMUX clock reset */
    RCU_DMA0RST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 20U),              /*!< DMA0X clock reset */
    RCU_DMA1RST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 21U),              /*!< DMA1 clock reset */

    /* APB1 peripherals */
    RCU_TIMER1RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 0U),              /*!< TIMER1 clock reset */
    RCU_TIMER2RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 1U),              /*!< TIMER2 clock reset */
    RCU_TIMER3RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 2U),              /*!< TIMER3 clock reset */
    RCU_TIMER4RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 3U),              /*!< TIMER4 clock reset */
    RCU_TIMER5RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 4U),              /*!< TIMER5 clock reset */
    RCU_TIMER6RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 5U),              /*!< TIMER6 clock reset */
    RCU_TIMER16RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 6U),              /*!< TIMER16 clock reset */
    RCU_WWDGTRST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 11U),             /*!< WWDGT clock reset */
    RCU_SPI1RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 14U),             /*!< SPI1 clock reset */
    RCU_SPI2RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 15U),             /*!< SPI2 clock reset */
    RCU_USART1RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 17U),             /*!< USART1 clock reset */
    RCU_USART2RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 18U),             /*!< USART2 clock reset */
    RCU_UART3RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 19U),             /*!< UART3 clock reset */
    RCU_UART4RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 20U),             /*!< UART4 clock reset */
    RCU_I2C0RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 21U),             /*!< I2C0 clock reset */
    RCU_I2C1RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 22U),             /*!< I2C1 clock reset */
    RCU_CMPRST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 23U),             /*!< CMP clock reset */
    RCU_BKPIRST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 27U),             /*!< BKPI clock reset */
    RCU_PMURST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 28U),             /*!< PMU clock reset */
    RCU_DACRST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 29U),             /*!< DAC clock reset */
    RCU_CTCRST       = RCU_REGIDX_BIT(ADD_APB1RST_REG_OFFSET, 27U),         /*!< CTC clock reset */

    /* APB2 peripherals */
    RCU_AFRST        = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 0U),              /*!< alternate function clock reset */
    RCU_GPIOARST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 2U),              /*!< GPIOA clock reset */
    RCU_GPIOBRST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 3U),              /*!< GPIOB clock reset */
    RCU_GPIOCRST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 4U),              /*!< GPIOC clock reset */
    RCU_GPIODRST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 5U),              /*!< GPIOD clock reset */
    RCU_GPIOERST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 6U),              /*!< GPIOE clock reset */
    RCU_ADC0RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 9U),              /*!< ADC0 clock reset */
    RCU_ADC1RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 10U),             /*!< ADC1 clock reset */
    RCU_TIMER0RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 11U),             /*!< TIMER0 clock reset */
    RCU_SPI0RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 12U),             /*!< SPI0 clock reset */
    RCU_TIMER7RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 13U),             /*!< TIMER7 clock reset */
    RCU_USART0RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 14U),             /*!< USART0 clock reset */
    RCU_ADC2RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 15U),             /*!< ADC2 clock reset */
    RCU_TIMER15RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 20U),             /*!< TIMER15 clock reset */
    RCU_TRIGSELRST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 24U),             /*!< TRIGSEL clock reset */
    RCU_SYSCFGRST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 25U),             /*!< SYSCFG clock reset */
    RCU_CAN0RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 26U),             /*!< CAN0 clock reset */
    RCU_CAN1RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 27U)              /*!< CAN1 clock reset */
} rcu_periph_reset_enum;

/* clock stabilization, peripheral reset and clock frequency failure flags */
typedef enum {
    /* clock stabilization flags */
    RCU_FLAG_IRC8MSTB      = RCU_REGIDX_BIT(CTL_REG_OFFSET, 1U),            /*!< IRC8M stabilization flag */
    RCU_FLAG_HXTALSTB      = RCU_REGIDX_BIT(CTL_REG_OFFSET, 17U),           /*!< HXTAL stabilization flag */
    RCU_FLAG_PLL0STB       = RCU_REGIDX_BIT(CTL_REG_OFFSET, 25U),           /*!< PLL0 stabilization flag */
    RCU_FLAG_PLL1STB       = RCU_REGIDX_BIT(CTL_REG_OFFSET, 27U),           /*!< PLL1 stabilization flag */
    RCU_FLAG_LXTALSTB      = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 1U),          /*!< LXTAL stabilization flag */
    RCU_FLAG_IRC40KSTB     = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 1U),         /*!< IRC40K stabilization flag */
    RCU_FLAG_IRC48MSTB     = RCU_REGIDX_BIT(ADDCTL_REG_OFFSET, 17U),        /*!< IRC48M stabilization flag */
    /* reset source flags */
    RCU_FLAG_EPRST         = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 26U),        /*!< external PIN reset flag */
    RCU_FLAG_PORRST        = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 27U),        /*!< power reset flag */
    RCU_FLAG_SWRST         = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 28U),        /*!< software reset flag */
    RCU_FLAG_FWDGTRST      = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 29U),        /*!< FWDGT reset flag */
    RCU_FLAG_WWDGTRST      = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 30U),        /*!< WWDGT reset flag */
    RCU_FLAG_LPRST         = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 31U),        /*!< low-power reset flag */
    /* clock frequency failure flag */
    RCU_FLAG_IRC8MCKFF     = RCU_REGIDX_BIT(CKFMCFG0_REG_OFFSET, 3U),       /*!< IRC8M clock frequency failure flag */
    RCU_FLAG_HXTALCKFF     = RCU_REGIDX_BIT(CKFMCFG1_REG_OFFSET, 30U),      /*!< HXTAL clock frequency failure flag */
    RCU_FLAG_PLL0PCKFF     = RCU_REGIDX_BIT(CKFMCFG2_REG_OFFSET, 30U),      /*!< PLL0P clock frequency failure flag */
    RCU_FLAG_PLL1CKFF      = RCU_REGIDX_BIT(CKFMCFG3_REG_OFFSET, 30U)       /*!< PLL1 clock frequency failure flag */
} rcu_flag_enum;

/* clock stabilization and clock stuck interrupt flags */
typedef enum {
    RCU_INT_FLAG_IRC40KSTB = RCU_REGIDX_BIT(INT_REG_OFFSET, 0U),            /*!< IRC40K stabilization interrupt flag */
    RCU_INT_FLAG_LXTALSTB  = RCU_REGIDX_BIT(INT_REG_OFFSET, 1U),            /*!< LXTAL stabilization interrupt flag */
    RCU_INT_FLAG_IRC8MSTB  = RCU_REGIDX_BIT(INT_REG_OFFSET, 2U),            /*!< IRC8M stabilization interrupt flag */
    RCU_INT_FLAG_HXTALSTB  = RCU_REGIDX_BIT(INT_REG_OFFSET, 3U),            /*!< HXTAL stabilization interrupt flag */
    RCU_INT_FLAG_PLL0STB   = RCU_REGIDX_BIT(INT_REG_OFFSET, 4U),            /*!< PLL0 stabilization interrupt flag */
    RCU_INT_FLAG_PLL1STB   = RCU_REGIDX_BIT(INT_REG_OFFSET, 5U),            /*!< PLL1 stabilization interrupt flag */
    RCU_INT_FLAG_HCKM      = RCU_REGIDX_BIT(INT_REG_OFFSET, 7U),            /*!< HXTAL clock stuck interrupt flag */
    RCU_INT_FLAG_LCKM      = RCU_REGIDX_BIT(INT_REG_OFFSET, 25U),           /*!< LXTAL clock stuck interrupt flag */
    RCU_INT_FLAG_IRC48MSTB = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 6U)          /*!< IRC48M stabilization interrupt flag */
} rcu_int_flag_enum;

/* clock frequency failure flags clear */
typedef enum {
    RCU_FLAG_IRC8MCKFF_CLR      = RCU_REGIDX_BIT(CKFMCFG0_REG_OFFSET, 4U),   /*!< IRC8M clock frequency failure interrupt flag clear */
    RCU_FLAG_HXTALCKFF_CLR      = RCU_REGIDX_BIT(CKFMCFG1_REG_OFFSET, 31U),  /*!< HXTAL clock frequency failure interrupt flag clear */
    RCU_FLAG_PLL0PCKFF_CLR      = RCU_REGIDX_BIT(CKFMCFG2_REG_OFFSET, 31U),  /*!< PLL0P clock frequency failure interrupt flag clear */
    RCU_FLAG_PLL1CKFF_CLR       = RCU_REGIDX_BIT(CKFMCFG3_REG_OFFSET, 31U)   /*!< PLL1 clock frequency failure interrupt flag clear */
} rcu_flag_clear_enum;

/* clock stabilization and clock stuck interrupt flags clear */
typedef enum {
    RCU_INT_FLAG_IRC40KSTB_CLR = RCU_REGIDX_BIT(INT_REG_OFFSET, 16U),       /*!< IRC40K stabilization interrupt flags clear */
    RCU_INT_FLAG_LXTALSTB_CLR  = RCU_REGIDX_BIT(INT_REG_OFFSET, 17U),       /*!< LXTAL stabilization interrupt flags clear */
    RCU_INT_FLAG_IRC8MSTB_CLR  = RCU_REGIDX_BIT(INT_REG_OFFSET, 18U),       /*!< IRC8M stabilization interrupt flags clear */
    RCU_INT_FLAG_HXTALSTB_CLR  = RCU_REGIDX_BIT(INT_REG_OFFSET, 19U),       /*!< HXTAL stabilization interrupt flags clear */
    RCU_INT_FLAG_PLL0STB_CLR   = RCU_REGIDX_BIT(INT_REG_OFFSET, 20U),       /*!< PLL0 stabilization interrupt flags clear */
    RCU_INT_FLAG_PLL1STB_CLR   = RCU_REGIDX_BIT(INT_REG_OFFSET, 21U),       /*!< PLL1 stabilization interrupt flags clear */
    RCU_INT_FLAG_HCKM_CLR      = RCU_REGIDX_BIT(INT_REG_OFFSET, 23U),       /*!< HXTAL clock stuck interrupt flags clear */
    RCU_INT_FLAG_LCKM_CLR      = RCU_REGIDX_BIT(INT_REG_OFFSET, 24U),       /*!< LXTAL clock stuck interrupt flags clear */
    RCU_INT_FLAG_IRC48MSTB_CLR = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 22U)     /*!< internal 48 MHz RC oscillator stabilization interrupt clear */
} rcu_int_flag_clear_enum;

/* clock stabilization, clock stuck and frequency failure interrupt enable or disable */
typedef enum {
    RCU_INT_IRC40KSTB       = RCU_REGIDX_BIT(INT_REG_OFFSET, 8U),           /*!< IRC40K stabilization interrupt */
    RCU_INT_LXTALSTB        = RCU_REGIDX_BIT(INT_REG_OFFSET, 9U),           /*!< LXTAL stabilization interrupt */
    RCU_INT_IRC8MSTB        = RCU_REGIDX_BIT(INT_REG_OFFSET, 10U),          /*!< IRC8M stabilization interrupt */
    RCU_INT_HXTALSTB        = RCU_REGIDX_BIT(INT_REG_OFFSET, 11U),          /*!< HXTAL stabilization interrupt */
    RCU_INT_PLL0STB         = RCU_REGIDX_BIT(INT_REG_OFFSET, 12U),          /*!< PLL0 stabilization interrupt */
    RCU_INT_PLL1STB         = RCU_REGIDX_BIT(INT_REG_OFFSET, 13U),          /*!< PLL1 stabilization interrupt */
    RCU_INT_LCKM            = RCU_REGIDX_BIT(INT_REG_OFFSET, 15U),          /*!< LXTAL clock stuck interrupt */
    RCU_INT_IRC48MSTB       = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 14U),       /*!< internal 48 MHz RC oscillator stabilization interrupt */
    RCU_INT_IRC8MCKFF       = RCU_REGIDX_BIT(CKFMCFG0_REG_OFFSET, 5U),      /*!< IRC8M clock frequency failure interrupt */
    RCU_INT_HXTALCKFF       = RCU_REGIDX_BIT(CKFMCFG1_REG_OFFSET, 25U),     /*!< HXTAL clock frequency failure interrupt */
    RCU_INT_PLL0PCKFF       = RCU_REGIDX_BIT(CKFMCFG2_REG_OFFSET, 23U),     /*!< PLL0P clock frequency failure interrupt */
    RCU_INT_PLL1CKFF        = RCU_REGIDX_BIT(CKFMCFG3_REG_OFFSET, 23U)      /*!< PLL1 clock frequency failure interrupt */
} rcu_int_enum;

/* oscillator types */
typedef enum {
    RCU_HXTAL      = RCU_REGIDX_BIT(CTL_REG_OFFSET, 16U),                   /*!< HXTAL */
    RCU_LXTAL      = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 0U),                  /*!< LXTAL */
    RCU_IRC8M      = RCU_REGIDX_BIT(CTL_REG_OFFSET, 0U),                    /*!< IRC8M */
    RCU_IRC48M     = RCU_REGIDX_BIT(ADDCTL_REG_OFFSET, 16U),                /*!< IRC48M */
    RCU_IRC40K     = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 0U),                 /*!< IRC40K */
    RCU_PLL0_CK    = RCU_REGIDX_BIT(CTL_REG_OFFSET, 24U),                   /*!< PLL0 */
    RCU_PLL1_CK    = RCU_REGIDX_BIT(CTL_REG_OFFSET, 26U)                    /*!< PLL1 */
} rcu_osci_type_enum;

/* rcu clock frequency */
typedef enum {
    CK_SYS      = 0,                                                        /*!< system clock */
    CK_AHB,                                                                 /*!< AHB clock */
    CK_APB1,                                                                /*!< APB1 clock */
    CK_APB2,                                                                /*!< APB2 clock */
    CK_PLL0                                                                 /*!< PLL0 clock */
} rcu_clock_freq_enum;

/* clock frequency monitor */
typedef enum {
    RCU_IRC8MCKFM   = RCU_REGIDX_BIT(CKFMCFG0_REG_OFFSET, 0U),              /*!< IRC8M clock frequency monitor */
    RCU_HXTALCKFM   = RCU_REGIDX_BIT(CKFMCFG1_REG_OFFSET, 0U),              /*!< HXTAL clock frequency monitor */
    RCU_PLL0PCKFM   = RCU_REGIDX_BIT(CKFMCFG2_REG_OFFSET, 0U),              /*!< PLL0P clock frequency monitor */
    RCU_PLL1CKFM    = RCU_REGIDX_BIT(CKFMCFG3_REG_OFFSET, 0U)               /*!< PLL1 clock frequency monitor */
} rcu_ckfm_enum;

/* RCU_CFG0 register bit define */
/* system clock source select */
#define CFG0_SCS(regval)                (BITS(0,1) & ((uint32_t)(regval) << 0))
#define RCU_CKSYSSRC_IRC8M              CFG0_SCS(0)                         /*!< system clock source select IRC8M */
#define RCU_CKSYSSRC_HXTAL              CFG0_SCS(1)                         /*!< system clock source select HXTAL */
#define RCU_CKSYSSRC_PLL0P              CFG0_SCS(2)                         /*!< system clock source select PLL0P */

/* system clock source select status */
#define CFG0_SCSS(regval)               (BITS(2,3) & ((uint32_t)(regval) << 2))
#define RCU_SCSS_IRC8M                  CFG0_SCSS(0)                        /*!< system clock source select IRC8M */
#define RCU_SCSS_HXTAL                  CFG0_SCSS(1)                        /*!< system clock source select HXTAL */
#define RCU_SCSS_PLL0P                  CFG0_SCSS(2)                        /*!< system clock source select PLL0P */

/* AHB prescaler selection */
#define CFG0_AHBPSC(regval)             (BITS(4,7) & ((uint32_t)(regval) << 4))
#define RCU_AHB_CKSYS_DIV1              CFG0_AHBPSC(0)                      /*!< AHB prescaler select CK_SYS */
#define RCU_AHB_CKSYS_DIV2              CFG0_AHBPSC(8)                      /*!< AHB prescaler select CK_SYS/2 */
#define RCU_AHB_CKSYS_DIV4              CFG0_AHBPSC(9)                      /*!< AHB prescaler select CK_SYS/4 */
#define RCU_AHB_CKSYS_DIV8              CFG0_AHBPSC(10)                     /*!< AHB prescaler select CK_SYS/8 */
#define RCU_AHB_CKSYS_DIV16             CFG0_AHBPSC(11)                     /*!< AHB prescaler select CK_SYS/16 */
#define RCU_AHB_CKSYS_DIV64             CFG0_AHBPSC(12)                     /*!< AHB prescaler select CK_SYS/64 */
#define RCU_AHB_CKSYS_DIV128            CFG0_AHBPSC(13)                     /*!< AHB prescaler select CK_SYS/128 */
#define RCU_AHB_CKSYS_DIV256            CFG0_AHBPSC(14)                     /*!< AHB prescaler select CK_SYS/256 */
#define RCU_AHB_CKSYS_DIV512            CFG0_AHBPSC(15)                     /*!< AHB prescaler select CK_SYS/512 */

/* APB1 prescaler selection */
#define CFG0_APB1PSC(regval)            (BITS(8,10) & ((uint32_t)(regval) << 8))
#define RCU_APB1_CKAHB_DIV1             CFG0_APB1PSC(0)                     /*!< APB1 prescaler select CK_AHB */
#define RCU_APB1_CKAHB_DIV2             CFG0_APB1PSC(4)                     /*!< APB1 prescaler select CK_AHB/2 */
#define RCU_APB1_CKAHB_DIV4             CFG0_APB1PSC(5)                     /*!< APB1 prescaler select CK_AHB/4 */
#define RCU_APB1_CKAHB_DIV8             CFG0_APB1PSC(6)                     /*!< APB1 prescaler select CK_AHB/8 */
#define RCU_APB1_CKAHB_DIV16            CFG0_APB1PSC(7)                     /*!< APB1 prescaler select CK_AHB/16 */

/* APB2 prescaler selection */
#define CFG0_APB2PSC(regval)            (BITS(11,13) & ((uint32_t)(regval) << 11))
#define RCU_APB2_CKAHB_DIV1             CFG0_APB2PSC(0)                     /*!< APB2 prescaler select CK_AHB */
#define RCU_APB2_CKAHB_DIV2             CFG0_APB2PSC(4)                     /*!< APB2 prescaler select CK_AHB/2 */
#define RCU_APB2_CKAHB_DIV4             CFG0_APB2PSC(5)                     /*!< APB2 prescaler select CK_AHB/4 */
#define RCU_APB2_CKAHB_DIV8             CFG0_APB2PSC(6)                     /*!< APB2 prescaler select CK_AHB/8 */
#define RCU_APB2_CKAHB_DIV16            CFG0_APB2PSC(7)                     /*!< APB2 prescaler select CK_AHB/16 */

/* ADC prescaler select */
#define RCU_CKADC_CKAPB2_DIV2           ((uint32_t)0x00000000U)             /*!< ADC prescaler select CK_APB2/2 */
#define RCU_CKADC_CKAPB2_DIV4           ((uint32_t)0x00000001U)             /*!< ADC prescaler select CK_APB2/4 */
#define RCU_CKADC_CKAPB2_DIV6           ((uint32_t)0x00000002U)             /*!< ADC prescaler select CK_APB2/6 */
#define RCU_CKADC_CKAPB2_DIV8           ((uint32_t)0x00000003U)             /*!< ADC prescaler select CK_APB2/8 */
#define RCU_CKADC_CKAPB2_DIV12          ((uint32_t)0x00000005U)             /*!< ADC prescaler select CK_APB2/12 */
#define RCU_CKADC_CKAPB2_DIV16          ((uint32_t)0x00000007U)             /*!< ADC prescaler select CK_APB2/16 */
#define RCU_CKADC_CKAHB_DIV3            ((uint32_t)0x00000008U)             /*!< ADC prescaler select CK_AHB/3 */
#define RCU_CKADC_CKAHB_DIV5            ((uint32_t)0x0000000CU)             /*!< ADC prescaler select CK_AHB/5 */
#define RCU_CKADC_CKAHB_DIV6            ((uint32_t)0x0000000DU)             /*!< ADC prescaler select CK_AHB/6 */
#define RCU_CKADC_CKAHB_DIV10           ((uint32_t)0x0000000EU)             /*!< ADC prescaler select CK_AHB/10 */
#define RCU_CKADC_CKAHB_DIV20           ((uint32_t)0x0000000FU)             /*!< ADC prescaler select CK_AHB/20 */

/* PLL0 clock multiplication factor */
#define CFG0_PLL0MF(regval)             ((BITS(18,21) & ((uint32_t)((uint32_t)(regval) & 0x0FU) << 18U)) | (BITS(29,30) & ((uint32_t)((uint32_t)(regval) & 0x30U) << 25U)))
#define RCU_PLL0_MUL4                   CFG0_PLL0MF(4)                      /*!< PLL0 source clock multiply by 4 */
#define RCU_PLL0_MUL5                   CFG0_PLL0MF(5)                      /*!< PLL0 source clock multiply by 5 */
#define RCU_PLL0_MUL6                   CFG0_PLL0MF(6)                      /*!< PLL0 source clock multiply by 6 */
#define RCU_PLL0_MUL7                   CFG0_PLL0MF(7)                      /*!< PLL0 source clock multiply by 7 */
#define RCU_PLL0_MUL8                   CFG0_PLL0MF(8)                      /*!< PLL0 source clock multiply by 8 */
#define RCU_PLL0_MUL9                   CFG0_PLL0MF(9)                      /*!< PLL0 source clock multiply by 9 */
#define RCU_PLL0_MUL10                  CFG0_PLL0MF(10)                     /*!< PLL0 source clock multiply by 10 */
#define RCU_PLL0_MUL11                  CFG0_PLL0MF(11)                     /*!< PLL0 source clock multiply by 11 */
#define RCU_PLL0_MUL12                  CFG0_PLL0MF(12)                     /*!< PLL0 source clock multiply by 12 */
#define RCU_PLL0_MUL13                  CFG0_PLL0MF(13)                     /*!< PLL0 source clock multiply by 13 */
#define RCU_PLL0_MUL14                  CFG0_PLL0MF(14)                     /*!< PLL0 source clock multiply by 14 */
#define RCU_PLL0_MUL15                  CFG0_PLL0MF(15)                     /*!< PLL0 source clock multiply by 15 */
#define RCU_PLL0_MUL16                  CFG0_PLL0MF(16)                     /*!< PLL0 source clock multiply by 16 */
#define RCU_PLL0_MUL17                  CFG0_PLL0MF(17)                     /*!< PLL0 source clock multiply by 17 */
#define RCU_PLL0_MUL18                  CFG0_PLL0MF(18)                     /*!< PLL0 source clock multiply by 18 */
#define RCU_PLL0_MUL19                  CFG0_PLL0MF(19)                     /*!< PLL0 source clock multiply by 19 */
#define RCU_PLL0_MUL20                  CFG0_PLL0MF(20)                     /*!< PLL0 source clock multiply by 20 */
#define RCU_PLL0_MUL21                  CFG0_PLL0MF(21)                     /*!< PLL0 source clock multiply by 21 */
#define RCU_PLL0_MUL22                  CFG0_PLL0MF(22)                     /*!< PLL0 source clock multiply by 22 */
#define RCU_PLL0_MUL23                  CFG0_PLL0MF(23)                     /*!< PLL0 source clock multiply by 23 */
#define RCU_PLL0_MUL24                  CFG0_PLL0MF(24)                     /*!< PLL0 source clock multiply by 24 */
#define RCU_PLL0_MUL25                  CFG0_PLL0MF(25)                     /*!< PLL0 source clock multiply by 25 */
#define RCU_PLL0_MUL26                  CFG0_PLL0MF(26)                     /*!< PLL0 source clock multiply by 26 */
#define RCU_PLL0_MUL27                  CFG0_PLL0MF(27)                     /*!< PLL0 source clock multiply by 27 */
#define RCU_PLL0_MUL28                  CFG0_PLL0MF(28)                     /*!< PLL0 source clock multiply by 28 */
#define RCU_PLL0_MUL29                  CFG0_PLL0MF(29)                     /*!< PLL0 source clock multiply by 29 */
#define RCU_PLL0_MUL30                  CFG0_PLL0MF(30)                     /*!< PLL0 source clock multiply by 30 */
#define RCU_PLL0_MUL31                  CFG0_PLL0MF(31)                     /*!< PLL0 source clock multiply by 31 */
#define RCU_PLL0_MUL32                  CFG0_PLL0MF(32)                     /*!< PLL0 source clock multiply by 32 */
#define RCU_PLL0_MUL33                  CFG0_PLL0MF(33)                     /*!< PLL0 source clock multiply by 33 */
#define RCU_PLL0_MUL34                  CFG0_PLL0MF(34)                     /*!< PLL0 source clock multiply by 34 */
#define RCU_PLL0_MUL35                  CFG0_PLL0MF(35)                     /*!< PLL0 source clock multiply by 35 */
#define RCU_PLL0_MUL36                  CFG0_PLL0MF(36)                     /*!< PLL0 source clock multiply by 36 */
#define RCU_PLL0_MUL37                  CFG0_PLL0MF(37)                     /*!< PLL0 source clock multiply by 37 */
#define RCU_PLL0_MUL38                  CFG0_PLL0MF(38)                     /*!< PLL0 source clock multiply by 38 */
#define RCU_PLL0_MUL39                  CFG0_PLL0MF(39)                     /*!< PLL0 source clock multiply by 39 */
#define RCU_PLL0_MUL40                  CFG0_PLL0MF(40)                     /*!< PLL0 source clock multiply by 40 */
#define RCU_PLL0_MUL41                  CFG0_PLL0MF(41)                     /*!< PLL0 source clock multiply by 41 */
#define RCU_PLL0_MUL42                  CFG0_PLL0MF(42)                     /*!< PLL0 source clock multiply by 42 */
#define RCU_PLL0_MUL43                  CFG0_PLL0MF(43)                     /*!< PLL0 source clock multiply by 43 */
#define RCU_PLL0_MUL44                  CFG0_PLL0MF(44)                     /*!< PLL0 source clock multiply by 44 */
#define RCU_PLL0_MUL45                  CFG0_PLL0MF(45)                     /*!< PLL0 source clock multiply by 45 */
#define RCU_PLL0_MUL46                  CFG0_PLL0MF(46)                     /*!< PLL0 source clock multiply by 46 */
#define RCU_PLL0_MUL47                  CFG0_PLL0MF(47)                     /*!< PLL0 source clock multiply by 47 */
#define RCU_PLL0_MUL48                  CFG0_PLL0MF(48)                     /*!< PLL0 source clock multiply by 48 */
#define RCU_PLL0_MUL49                  CFG0_PLL0MF(49)                     /*!< PLL0 source clock multiply by 49 */
#define RCU_PLL0_MUL50                  CFG0_PLL0MF(50)                     /*!< PLL0 source clock multiply by 50 */
#define RCU_PLL0_MUL51                  CFG0_PLL0MF(51)                     /*!< PLL0 source clock multiply by 51 */
#define RCU_PLL0_MUL52                  CFG0_PLL0MF(52)                     /*!< PLL0 source clock multiply by 52 */
#define RCU_PLL0_MUL53                  CFG0_PLL0MF(53)                     /*!< PLL0 source clock multiply by 53 */
#define RCU_PLL0_MUL54                  CFG0_PLL0MF(54)                     /*!< PLL0 source clock multiply by 54 */
#define RCU_PLL0_MUL55                  CFG0_PLL0MF(55)                     /*!< PLL0 source clock multiply by 55 */
#define RCU_PLL0_MUL56                  CFG0_PLL0MF(56)                     /*!< PLL0 source clock multiply by 56 */
#define RCU_PLL0_MUL57                  CFG0_PLL0MF(57)                     /*!< PLL0 source clock multiply by 57 */
#define RCU_PLL0_MUL58                  CFG0_PLL0MF(58)                     /*!< PLL0 source clock multiply by 58 */
#define RCU_PLL0_MUL59                  CFG0_PLL0MF(59)                     /*!< PLL0 source clock multiply by 59 */
#define RCU_PLL0_MUL60                  CFG0_PLL0MF(60)                     /*!< PLL0 source clock multiply by 60 */
#define RCU_PLL0_MUL61                  CFG0_PLL0MF(61)                     /*!< PLL0 source clock multiply by 61 */
#define RCU_PLL0_MUL62                  CFG0_PLL0MF(62)                     /*!< PLL0 source clock multiply by 62 */
#define RCU_PLL0_MUL63                  CFG0_PLL0MF(63)                     /*!< PLL0 source clock multiply by 63 */

/* USBFS prescaler select */
#define USBPSC_2                        RCU_CFG0_USBFSPSC_2
#define CFG0_USBPSC(regval)             (BITS(22,23) & ((uint32_t)(regval) << 22U))
#define RCU_CKUSB_CKPLL0_DIV2           CFG0_USBPSC(1)                      /*!< USBFS prescaler select CK_PLL0/2 */
#define RCU_CKUSB_CKPLL0_DIV3           CFG0_USBPSC(0)                      /*!< USBFS prescaler select CK_PLL0/3 */
#define RCU_CKUSB_CKPLL0_DIV4           CFG0_USBPSC(3)                      /*!< USBFS prescaler select CK_PLL0/4 */
#define RCU_CKUSB_CKPLL0_DIV5           CFG0_USBPSC(2)                      /*!< USBFS prescaler select CK_PLL0/5 */
#define RCU_CKUSB_CKPLL0_DIV6           (USBPSC_2 | CFG0_USBPSC(0))         /*!< USBFS prescaler select CK_PLL0/6 */
#define RCU_CKUSB_CKPLL0_DIV7           (USBPSC_2 | CFG0_USBPSC(1))         /*!< USBFS prescaler select CK_PLL0/7 */
#define RCU_CKUSB_CKPLL0_DIV8           (USBPSC_2 | CFG0_USBPSC(2))         /*!< USBFS prescaler select CK_PLL0/8 */

/* CKOUT Clock source selection */
#define CFG0_CKOUTSEL(regval)           (BITS(24,26) & ((uint32_t)(regval) << 24U))
#define RCU_CKOUTSRC_CKSYS              CFG0_CKOUTSEL(0)                   /*!< system clock selected */
#define RCU_CKOUTSRC_IRC8M              CFG0_CKOUTSEL(1)                   /*!< internal 8M RC oscillator clock selected */
#define RCU_CKOUTSRC_HXTAL              CFG0_CKOUTSEL(2)                   /*!< high speed crystal oscillator clock (HXTAL) selected */
#define RCU_CKOUTSRC_CKPLL0_DIV2        CFG0_CKOUTSEL(3)                   /*!< CK_PLL0/2 clock selected */
#define RCU_CKOUTSRC_CKPLL1_DIV2        CFG0_CKOUTSEL(4)                   /*!< CK_PLL1/2 clock selected */
#define RCU_CKOUTSRC_LXTAL              CFG0_CKOUTSEL(5)                   /*!< LXTAL clock selected */
#define RCU_CKOUTSRC_IRC48M             CFG0_CKOUTSEL(6)                   /*!< internal 8M RC oscillator clock selected  */
#define RCU_CKOUTSRC_IRC40K             CFG0_CKOUTSEL(7)                   /*!< IRC40K clock selected */

/* LXTAL drive capability */
#define BDCTL_LXTALDRI(regval)          (BITS(3,4) & ((uint32_t)(regval) << 3U))
#define RCU_LXTAL_LOWDRI                BDCTL_LXTALDRI(0)                   /*!< lower driving capability */
#define RCU_LXTAL_MED_LOWDRI            BDCTL_LXTALDRI(1)                   /*!< medium low driving capability */
#define RCU_LXTAL_MED_HIGHDRI           BDCTL_LXTALDRI(2)                   /*!< medium high driving capability */
#define RCU_LXTAL_HIGHDRI               BDCTL_LXTALDRI(3)                   /*!< higher driving capability */

/* RTC clock entry selection */
#define BDCTL_RTCSRC(regval)            (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define RCU_RTCSRC_NONE                 BDCTL_RTCSRC(0)                     /*!< no clock selected */
#define RCU_RTCSRC_LXTAL                BDCTL_RTCSRC(1)                     /*!< RTC source clock select LXTAL  */
#define RCU_RTCSRC_IRC40K               BDCTL_RTCSRC(2)                     /*!< RTC source clock select IRC40K */
#define RCU_RTCSRC_HXTAL_DIV_128        BDCTL_RTCSRC(3)                     /*!< RTC source clock select HXTAL/128 */

/* PREDIV0 division factor */
#define CFG1_PREDIV0(regval)            (BITS(0,3) & ((uint32_t)(regval) << 0U))
#define RCU_PREDIV0_DIV1                CFG1_PREDIV0(0)                     /*!< PREDIV0 input source clock not divided */
#define RCU_PREDIV0_DIV2                CFG1_PREDIV0(1)                     /*!< PREDIV0 input source clock divided by 2 */
#define RCU_PREDIV0_DIV3                CFG1_PREDIV0(2)                     /*!< PREDIV0 input source clock divided by 3 */
#define RCU_PREDIV0_DIV4                CFG1_PREDIV0(3)                     /*!< PREDIV0 input source clock divided by 4 */
#define RCU_PREDIV0_DIV5                CFG1_PREDIV0(4)                     /*!< PREDIV0 input source clock divided by 5 */
#define RCU_PREDIV0_DIV6                CFG1_PREDIV0(5)                     /*!< PREDIV0 input source clock divided by 6 */
#define RCU_PREDIV0_DIV7                CFG1_PREDIV0(6)                     /*!< PREDIV0 input source clock divided by 7 */
#define RCU_PREDIV0_DIV8                CFG1_PREDIV0(7)                     /*!< PREDIV0 input source clock divided by 8 */
#define RCU_PREDIV0_DIV9                CFG1_PREDIV0(8)                     /*!< PREDIV0 input source clock divided by 9 */
#define RCU_PREDIV0_DIV10               CFG1_PREDIV0(9)                     /*!< PREDIV0 input source clock divided by 10 */
#define RCU_PREDIV0_DIV11               CFG1_PREDIV0(10)                    /*!< PREDIV0 input source clock divided by 11 */
#define RCU_PREDIV0_DIV12               CFG1_PREDIV0(11)                    /*!< PREDIV0 input source clock divided by 12 */
#define RCU_PREDIV0_DIV13               CFG1_PREDIV0(12)                    /*!< PREDIV0 input source clock divided by 13 */
#define RCU_PREDIV0_DIV14               CFG1_PREDIV0(13)                    /*!< PREDIV0 input source clock divided by 14 */
#define RCU_PREDIV0_DIV15               CFG1_PREDIV0(14)                    /*!< PREDIV0 input source clock divided by 15 */
#define RCU_PREDIV0_DIV16               CFG1_PREDIV0(15)                    /*!< PREDIV0 input source clock divided by 16 */

/* PREDIV1 division factor */
#define CFG1_PREDIV1(regval)            (BITS(4,7) & ((uint32_t)(regval) << 4U))
#define RCU_PREDIV1_DIV1                CFG1_PREDIV1(0)                     /*!< PREDIV1 input source clock not divided */
#define RCU_PREDIV1_DIV2                CFG1_PREDIV1(1)                     /*!< PREDIV1 input source clock divided by 2 */
#define RCU_PREDIV1_DIV3                CFG1_PREDIV1(2)                     /*!< PREDIV1 input source clock divided by 3 */
#define RCU_PREDIV1_DIV4                CFG1_PREDIV1(3)                     /*!< PREDIV1 input source clock divided by 4 */
#define RCU_PREDIV1_DIV5                CFG1_PREDIV1(4)                     /*!< PREDIV1 input source clock divided by 5 */
#define RCU_PREDIV1_DIV6                CFG1_PREDIV1(5)                     /*!< PREDIV1 input source clock divided by 6 */
#define RCU_PREDIV1_DIV7                CFG1_PREDIV1(6)                     /*!< PREDIV1 input source clock divided by 7 */
#define RCU_PREDIV1_DIV8                CFG1_PREDIV1(7)                     /*!< PREDIV1 input source clock divided by 8 */
#define RCU_PREDIV1_DIV9                CFG1_PREDIV1(8)                     /*!< PREDIV1 input source clock divided by 9 */
#define RCU_PREDIV1_DIV10               CFG1_PREDIV1(9)                     /*!< PREDIV1 input source clock divided by 10 */
#define RCU_PREDIV1_DIV11               CFG1_PREDIV1(10)                    /*!< PREDIV1 input source clock divided by 11 */
#define RCU_PREDIV1_DIV12               CFG1_PREDIV1(11)                    /*!< PREDIV1 input source clock divided by 12 */
#define RCU_PREDIV1_DIV13               CFG1_PREDIV1(12)                    /*!< PREDIV1 input source clock divided by 13 */
#define RCU_PREDIV1_DIV14               CFG1_PREDIV1(13)                    /*!< PREDIV1 input source clock divided by 14 */
#define RCU_PREDIV1_DIV15               CFG1_PREDIV1(14)                    /*!< PREDIV1 input source clock divided by 15 */
#define RCU_PREDIV1_DIV16               CFG1_PREDIV1(15)                    /*!< PREDIV1 input source clock divided by 16 */

/* PLL1 clock multiplication factor */
#define CFG1_PLL1MF(regval)             (BITS(8,13) & ((uint32_t)(regval) << 8U))
#define RCU_PLL1_MUL4                    CFG1_PLL1MF(4)                     /*!< PLL1 source clock multiply by 4 */
#define RCU_PLL1_MUL5                    CFG1_PLL1MF(5)                     /*!< PLL1 source clock multiply by 5 */
#define RCU_PLL1_MUL6                    CFG1_PLL1MF(6)                     /*!< PLL1 source clock multiply by 6 */
#define RCU_PLL1_MUL7                    CFG1_PLL1MF(7)                     /*!< PLL1 source clock multiply by 7 */
#define RCU_PLL1_MUL8                    CFG1_PLL1MF(8)                     /*!< PLL1 source clock multiply by 8 */
#define RCU_PLL1_MUL9                    CFG1_PLL1MF(9)                     /*!< PLL1 source clock multiply by 9 */
#define RCU_PLL1_MUL10                   CFG1_PLL1MF(10)                    /*!< PLL1 source clock multiply by 10 */
#define RCU_PLL1_MUL11                   CFG1_PLL1MF(11)                    /*!< PLL1 source clock multiply by 11 */
#define RCU_PLL1_MUL12                   CFG1_PLL1MF(12)                    /*!< PLL1 source clock multiply by 12 */
#define RCU_PLL1_MUL13                   CFG1_PLL1MF(13)                    /*!< PLL1 source clock multiply by 13 */
#define RCU_PLL1_MUL14                   CFG1_PLL1MF(14)                    /*!< PLL1 source clock multiply by 14 */
#define RCU_PLL1_MUL15                   CFG1_PLL1MF(15)                    /*!< PLL1 source clock multiply by 15 */
#define RCU_PLL1_MUL16                   CFG1_PLL1MF(16)                    /*!< PLL1 source clock multiply by 16 */
#define RCU_PLL1_MUL17                   CFG1_PLL1MF(17)                    /*!< PLL1 source clock multiply by 17 */
#define RCU_PLL1_MUL18                   CFG1_PLL1MF(18)                    /*!< PLL1 source clock multiply by 18 */
#define RCU_PLL1_MUL19                   CFG1_PLL1MF(19)                    /*!< PLL1 source clock multiply by 19 */
#define RCU_PLL1_MUL20                   CFG1_PLL1MF(20)                    /*!< PLL1 source clock multiply by 20 */
#define RCU_PLL1_MUL21                   CFG1_PLL1MF(21)                    /*!< PLL1 source clock multiply by 21 */
#define RCU_PLL1_MUL22                   CFG1_PLL1MF(22)                    /*!< PLL1 source clock multiply by 22 */
#define RCU_PLL1_MUL23                   CFG1_PLL1MF(23)                    /*!< PLL1 source clock multiply by 23 */
#define RCU_PLL1_MUL24                   CFG1_PLL1MF(24)                    /*!< PLL1 source clock multiply by 24 */
#define RCU_PLL1_MUL25                   CFG1_PLL1MF(25)                    /*!< PLL1 source clock multiply by 25 */
#define RCU_PLL1_MUL26                   CFG1_PLL1MF(26)                    /*!< PLL1 source clock multiply by 26 */
#define RCU_PLL1_MUL27                   CFG1_PLL1MF(27)                    /*!< PLL1 source clock multiply by 27 */
#define RCU_PLL1_MUL28                   CFG1_PLL1MF(28)                    /*!< PLL1 source clock multiply by 28 */
#define RCU_PLL1_MUL29                   CFG1_PLL1MF(29)                    /*!< PLL1 source clock multiply by 29 */
#define RCU_PLL1_MUL30                   CFG1_PLL1MF(30)                    /*!< PLL1 source clock multiply by 30 */
#define RCU_PLL1_MUL31                   CFG1_PLL1MF(31)                    /*!< PLL1 source clock multiply by 31 */
#define RCU_PLL1_MUL32                   CFG1_PLL1MF(32)                    /*!< PLL1 source clock multiply by 32 */
#define RCU_PLL1_MUL33                   CFG1_PLL1MF(33)                    /*!< PLL1 source clock multiply by 33 */
#define RCU_PLL1_MUL34                   CFG1_PLL1MF(34)                    /*!< PLL1 source clock multiply by 34 */
#define RCU_PLL1_MUL35                   CFG1_PLL1MF(35)                    /*!< PLL1 source clock multiply by 35 */
#define RCU_PLL1_MUL36                   CFG1_PLL1MF(36)                    /*!< PLL1 source clock multiply by 36 */
#define RCU_PLL1_MUL37                   CFG1_PLL1MF(37)                    /*!< PLL1 source clock multiply by 37 */
#define RCU_PLL1_MUL38                   CFG1_PLL1MF(38)                    /*!< PLL1 source clock multiply by 38 */
#define RCU_PLL1_MUL39                   CFG1_PLL1MF(39)                    /*!< PLL1 source clock multiply by 39 */
#define RCU_PLL1_MUL40                   CFG1_PLL1MF(40)                    /*!< PLL1 source clock multiply by 40 */
#define RCU_PLL1_MUL41                   CFG1_PLL1MF(41)                    /*!< PLL1 source clock multiply by 41 */
#define RCU_PLL1_MUL42                   CFG1_PLL1MF(42)                    /*!< PLL1 source clock multiply by 42 */
#define RCU_PLL1_MUL43                   CFG1_PLL1MF(43)                    /*!< PLL1 source clock multiply by 43 */
#define RCU_PLL1_MUL44                   CFG1_PLL1MF(44)                    /*!< PLL1 source clock multiply by 44 */
#define RCU_PLL1_MUL45                   CFG1_PLL1MF(45)                    /*!< PLL1 source clock multiply by 45 */
#define RCU_PLL1_MUL46                   CFG1_PLL1MF(46)                    /*!< PLL1 source clock multiply by 46 */
#define RCU_PLL1_MUL47                   CFG1_PLL1MF(47)                    /*!< PLL1 source clock multiply by 47 */
#define RCU_PLL1_MUL48                   CFG1_PLL1MF(48)                    /*!< PLL1 source clock multiply by 48 */
#define RCU_PLL1_MUL49                   CFG1_PLL1MF(49)                    /*!< PLL1 source clock multiply by 49 */
#define RCU_PLL1_MUL50                   CFG1_PLL1MF(50)                    /*!< PLL1 source clock multiply by 50 */
#define RCU_PLL1_MUL51                   CFG1_PLL1MF(51)                    /*!< PLL1 source clock multiply by 51 */
#define RCU_PLL1_MUL52                   CFG1_PLL1MF(52)                    /*!< PLL1 source clock multiply by 52 */
#define RCU_PLL1_MUL53                   CFG1_PLL1MF(53)                    /*!< PLL1 source clock multiply by 53 */
#define RCU_PLL1_MUL54                   CFG1_PLL1MF(54)                    /*!< PLL1 source clock multiply by 54 */
#define RCU_PLL1_MUL55                   CFG1_PLL1MF(55)                    /*!< PLL1 source clock multiply by 55 */
#define RCU_PLL1_MUL56                   CFG1_PLL1MF(56)                    /*!< PLL1 source clock multiply by 56 */
#define RCU_PLL1_MUL57                   CFG1_PLL1MF(57)                    /*!< PLL1 source clock multiply by 57 */
#define RCU_PLL1_MUL58                   CFG1_PLL1MF(58)                    /*!< PLL1 source clock multiply by 58 */
#define RCU_PLL1_MUL59                   CFG1_PLL1MF(59)                    /*!< PLL1 source clock multiply by 59 */
#define RCU_PLL1_MUL60                   CFG1_PLL1MF(60)                    /*!< PLL1 source clock multiply by 60 */
#define RCU_PLL1_MUL61                   CFG1_PLL1MF(61)                    /*!< PLL1 source clock multiply by 61 */
#define RCU_PLL1_MUL62                   CFG1_PLL1MF(62)                    /*!< PLL1 source clock multiply by 62 */
#define RCU_PLL1_MUL63                   CFG1_PLL1MF(63)                    /*!< PLL1 source clock multiply by 63 */

/* I2S1 clock division factor  */
#define ADDCTL_I2S1DIV(regval)           (BITS(3,7) & ((uint32_t)(regval) << 3U))
#define RCU_I2S1_DIV1                    ADDCTL_I2S1DIV(0)                  /*!< I2S1 input source clock divided by 1  */
#define RCU_I2S1_DIV2                    ADDCTL_I2S1DIV(1)                  /*!< I2S1 input source clock divided by 2  */
#define RCU_I2S1_DIV3                    ADDCTL_I2S1DIV(2)                  /*!< I2S1 input source clock divided by 3  */
#define RCU_I2S1_DIV4                    ADDCTL_I2S1DIV(3)                  /*!< I2S1 input source clock divided by 4  */
#define RCU_I2S1_DIV5                    ADDCTL_I2S1DIV(4)                  /*!< I2S1 input source clock divided by 5  */
#define RCU_I2S1_DIV6                    ADDCTL_I2S1DIV(5)                  /*!< I2S1 input source clock divided by 6  */
#define RCU_I2S1_DIV7                    ADDCTL_I2S1DIV(6)                  /*!< I2S1 input source clock divided by 7  */
#define RCU_I2S1_DIV8                    ADDCTL_I2S1DIV(7)                  /*!< I2S1 input source clock divided by 8  */
#define RCU_I2S1_DIV9                    ADDCTL_I2S1DIV(8)                  /*!< I2S1 input source clock divided by 9  */
#define RCU_I2S1_DIV10                   ADDCTL_I2S1DIV(9)                  /*!< I2S1 input source clock divided by 10  */
#define RCU_I2S1_DIV11                   ADDCTL_I2S1DIV(10)                 /*!< I2S1 input source clock divided by 11  */
#define RCU_I2S1_DIV12                   ADDCTL_I2S1DIV(11)                 /*!< I2S1 input source clock divided by 12  */
#define RCU_I2S1_DIV13                   ADDCTL_I2S1DIV(12)                 /*!< I2S1 input source clock divided by 13  */
#define RCU_I2S1_DIV14                   ADDCTL_I2S1DIV(13)                 /*!< I2S1 input source clock divided by 14  */
#define RCU_I2S1_DIV15                   ADDCTL_I2S1DIV(14)                 /*!< I2S1 input source clock divided by 15  */
#define RCU_I2S1_DIV16                   ADDCTL_I2S1DIV(15)                 /*!< I2S1 input source clock divided by 16  */
#define RCU_I2S1_DIV17                   ADDCTL_I2S1DIV(16)                 /*!< I2S1 input source clock divided by 17  */
#define RCU_I2S1_DIV18                   ADDCTL_I2S1DIV(17)                 /*!< I2S1 input source clock divided by 18  */
#define RCU_I2S1_DIV19                   ADDCTL_I2S1DIV(18)                 /*!< I2S1 input source clock divided by 19  */
#define RCU_I2S1_DIV20                   ADDCTL_I2S1DIV(19)                 /*!< I2S1 input source clock divided by 20  */
#define RCU_I2S1_DIV21                   ADDCTL_I2S1DIV(20)                 /*!< I2S1 input source clock divided by 21  */
#define RCU_I2S1_DIV22                   ADDCTL_I2S1DIV(21)                 /*!< I2S1 input source clock divided by 22  */
#define RCU_I2S1_DIV23                   ADDCTL_I2S1DIV(22)                 /*!< I2S1 input source clock divided by 23  */
#define RCU_I2S1_DIV24                   ADDCTL_I2S1DIV(23)                 /*!< I2S1 input source clock divided by 24  */
#define RCU_I2S1_DIV25                   ADDCTL_I2S1DIV(24)                 /*!< I2S1 input source clock divided by 25  */
#define RCU_I2S1_DIV26                   ADDCTL_I2S1DIV(25)                 /*!< I2S1 input source clock divided by 26  */
#define RCU_I2S1_DIV27                   ADDCTL_I2S1DIV(26)                 /*!< I2S1 input source clock divided by 27  */
#define RCU_I2S1_DIV28                   ADDCTL_I2S1DIV(27)                 /*!< I2S1 input source clock divided by 28  */
#define RCU_I2S1_DIV29                   ADDCTL_I2S1DIV(28)                 /*!< I2S1 input source clock divided by 29  */
#define RCU_I2S1_DIV30                   ADDCTL_I2S1DIV(29)                 /*!< I2S1 input source clock divided by 30  */
#define RCU_I2S1_DIV31                   ADDCTL_I2S1DIV(30)                 /*!< I2S1 input source clock divided by 31  */
#define RCU_I2S1_DIV32                   ADDCTL_I2S1DIV(31)                 /*!< I2S1 input source clock divided by 32  */

/* PLL0 clock division factor  */
#define ADDCTL_PLL0DIV(regval)           (BITS(8,11) & ((uint32_t)(regval) << 8U))
#define RCU_PLL0_DIV1                    ADDCTL_PLL0DIV(0)                  /*!< PLL0 input source clock divided by 1 */
#define RCU_PLL0_DIV2                    ADDCTL_PLL0DIV(1)                  /*!< PLL0 input source clock divided by 2 */
#define RCU_PLL0_DIV3                    ADDCTL_PLL0DIV(2)                  /*!< PLL0 input source clock divided by 3 */
#define RCU_PLL0_DIV4                    ADDCTL_PLL0DIV(3)                  /*!< PLL0 input source clock divided by 4 */
#define RCU_PLL0_DIV5                    ADDCTL_PLL0DIV(4)                  /*!< PLL0 input source clock divided by 5 */
#define RCU_PLL0_DIV6                    ADDCTL_PLL0DIV(5)                  /*!< PLL0 input source clock divided by 6 */
#define RCU_PLL0_DIV7                    ADDCTL_PLL0DIV(6)                  /*!< PLL0 input source clock divided by 7 */
#define RCU_PLL0_DIV8                    ADDCTL_PLL0DIV(7)                  /*!< PLL0 input source clock divided by 8 */
#define RCU_PLL0_DIV9                    ADDCTL_PLL0DIV(8)                  /*!< PLL0 input source clock divided by 9 */
#define RCU_PLL0_DIV10                   ADDCTL_PLL0DIV(9)                  /*!< PLL0 input source clock divided by 10 */
#define RCU_PLL0_DIV11                   ADDCTL_PLL0DIV(10)                 /*!< PLL0 input source clock divided by 11 */
#define RCU_PLL0_DIV12                   ADDCTL_PLL0DIV(11)                 /*!< PLL0 input source clock divided by 12 */
#define RCU_PLL0_DIV13                   ADDCTL_PLL0DIV(12)                 /*!< PLL0 input source clock divided by 13 */
#define RCU_PLL0_DIV14                   ADDCTL_PLL0DIV(13)                 /*!< PLL0 input source clock divided by 14 */
#define RCU_PLL0_DIV15                   ADDCTL_PLL0DIV(14)                 /*!< PLL0 input source clock divided by 15 */
#define RCU_PLL0_DIV16                   ADDCTL_PLL0DIV(15)                 /*!< PLL0 input source clock divided by 16 */

/* FMC clock division factor  */
#define ADDCTL_FMCDIV(regval)            (BITS(12,15) & ((uint32_t)(regval) << 12U))
#define RCU_FMC_DIV1                     ADDCTL_FMCDIV(0)                   /*!< FMC input source clock divided by 1 */
#define RCU_FMC_DIV2                     ADDCTL_FMCDIV(1)                   /*!< FMC input source clock divided by 2 */
#define RCU_FMC_DIV3                     ADDCTL_FMCDIV(2)                   /*!< FMC input source clock divided by 3 */
#define RCU_FMC_DIV4                     ADDCTL_FMCDIV(3)                   /*!< FMC input source clock divided by 4 */
#define RCU_FMC_DIV5                     ADDCTL_FMCDIV(4)                   /*!< FMC input source clock divided by 5 */
#define RCU_FMC_DIV6                     ADDCTL_FMCDIV(5)                   /*!< FMC input source clock divided by 6 */
#define RCU_FMC_DIV7                     ADDCTL_FMCDIV(6)                   /*!< FMC input source clock divided by 7 */
#define RCU_FMC_DIV8                     ADDCTL_FMCDIV(7)                   /*!< FMC input source clock divided by 8 */
#define RCU_FMC_DIV9                     ADDCTL_FMCDIV(8)                   /*!< FMC input source clock divided by 9 */
#define RCU_FMC_DIV10                    ADDCTL_FMCDIV(9)                   /*!< FMC input source clock divided by 10 */
#define RCU_FMC_DIV11                    ADDCTL_FMCDIV(10)                  /*!< FMC input source clock divided by 11 */
#define RCU_FMC_DIV12                    ADDCTL_FMCDIV(11)                  /*!< FMC input source clock divided by 12 */
#define RCU_FMC_DIV13                    ADDCTL_FMCDIV(12)                  /*!< FMC input source clock divided by 13 */
#define RCU_FMC_DIV14                    ADDCTL_FMCDIV(13)                  /*!< FMC input source clock divided by 14 */
#define RCU_FMC_DIV15                    ADDCTL_FMCDIV(14)                  /*!< FMC input source clock divided by 15 */
#define RCU_FMC_DIV16                    ADDCTL_FMCDIV(15)                  /*!< FMC input source clock divided by 16 */

/* I2S2 clock division factor  */
#define ADDCTL_I2S2DIV(regval)           (BITS(18,22) & ((uint32_t)(regval) << 18U))
#define RCU_I2S2_DIV1                    ADDCTL_I2S2DIV(0)                  /*!< I2S2 input source clock divided by 1  */
#define RCU_I2S2_DIV2                    ADDCTL_I2S2DIV(1)                  /*!< I2S2 input source clock divided by 2  */
#define RCU_I2S2_DIV3                    ADDCTL_I2S2DIV(2)                  /*!< I2S2 input source clock divided by 3  */
#define RCU_I2S2_DIV4                    ADDCTL_I2S2DIV(3)                  /*!< I2S2 input source clock divided by 4  */
#define RCU_I2S2_DIV5                    ADDCTL_I2S2DIV(4)                  /*!< I2S2 input source clock divided by 5  */
#define RCU_I2S2_DIV6                    ADDCTL_I2S2DIV(5)                  /*!< I2S2 input source clock divided by 6  */
#define RCU_I2S2_DIV7                    ADDCTL_I2S2DIV(6)                  /*!< I2S2 input source clock divided by 7  */
#define RCU_I2S2_DIV8                    ADDCTL_I2S2DIV(7)                  /*!< I2S2 input source clock divided by 8  */
#define RCU_I2S2_DIV9                    ADDCTL_I2S2DIV(8)                  /*!< I2S2 input source clock divided by 9  */
#define RCU_I2S2_DIV10                   ADDCTL_I2S2DIV(9)                  /*!< I2S2 input source clock divided by 10  */
#define RCU_I2S2_DIV11                   ADDCTL_I2S2DIV(10)                 /*!< I2S2 input source clock divided by 11  */
#define RCU_I2S2_DIV12                   ADDCTL_I2S2DIV(11)                 /*!< I2S2 input source clock divided by 12  */
#define RCU_I2S2_DIV13                   ADDCTL_I2S2DIV(12)                 /*!< I2S2 input source clock divided by 13  */
#define RCU_I2S2_DIV14                   ADDCTL_I2S2DIV(13)                 /*!< I2S2 input source clock divided by 14  */
#define RCU_I2S2_DIV15                   ADDCTL_I2S2DIV(14)                 /*!< I2S2 input source clock divided by 15  */
#define RCU_I2S2_DIV16                   ADDCTL_I2S2DIV(15)                 /*!< I2S2 input source clock divided by 16  */
#define RCU_I2S2_DIV17                   ADDCTL_I2S2DIV(16)                 /*!< I2S2 input source clock divided by 17  */
#define RCU_I2S2_DIV18                   ADDCTL_I2S2DIV(17)                 /*!< I2S2 input source clock divided by 18  */
#define RCU_I2S2_DIV19                   ADDCTL_I2S2DIV(18)                 /*!< I2S2 input source clock divided by 19  */
#define RCU_I2S2_DIV20                   ADDCTL_I2S2DIV(19)                 /*!< I2S2 input source clock divided by 20  */
#define RCU_I2S2_DIV21                   ADDCTL_I2S2DIV(20)                 /*!< I2S2 input source clock divided by 21  */
#define RCU_I2S2_DIV22                   ADDCTL_I2S2DIV(21)                 /*!< I2S2 input source clock divided by 22  */
#define RCU_I2S2_DIV23                   ADDCTL_I2S2DIV(22)                 /*!< I2S2 input source clock divided by 23  */
#define RCU_I2S2_DIV24                   ADDCTL_I2S2DIV(23)                 /*!< I2S2 input source clock divided by 24  */
#define RCU_I2S2_DIV25                   ADDCTL_I2S2DIV(24)                 /*!< I2S2 input source clock divided by 25  */
#define RCU_I2S2_DIV26                   ADDCTL_I2S2DIV(25)                 /*!< I2S2 input source clock divided by 26  */
#define RCU_I2S2_DIV27                   ADDCTL_I2S2DIV(26)                 /*!< I2S2 input source clock divided by 27  */
#define RCU_I2S2_DIV28                   ADDCTL_I2S2DIV(27)                 /*!< I2S2 input source clock divided by 28  */
#define RCU_I2S2_DIV29                   ADDCTL_I2S2DIV(28)                 /*!< I2S2 input source clock divided by 29  */
#define RCU_I2S2_DIV30                   ADDCTL_I2S2DIV(29)                 /*!< I2S2 input source clock divided by 30  */
#define RCU_I2S2_DIV31                   ADDCTL_I2S2DIV(30)                 /*!< I2S2 input source clock divided by 31  */
#define RCU_I2S2_DIV32                   ADDCTL_I2S2DIV(31)                 /*!< I2S2 input source clock divided by 32  */

/* FMC clock source selection */
#define ADDCTL_FMCSEL(regval)            (BITS(1,2) & ((uint32_t)(regval) << 1U))
#define RCU_FMC_CK_AHB                   ADDCTL_FMCSEL(0)                   /*!< CK_AHB clock selected as source clock of FMC */
#define RCU_FMC_CK_SYS                   ADDCTL_FMCSEL(1)                   /*!< CK_SYS clock selected as source clock of FMC */
#define RCU_FMC_CK_PLL0                  ADDCTL_FMCSEL(2)                   /*!< CK_PLL0 clock selected as source clock of FMC */
#define RCU_FMC_CK_PLL1                  ADDCTL_FMCSEL(3)                   /*!< CK_PLL1 clock selected as source clock of FMC */

/* PLL0 input clock source selection */
#define CFG1_PLL0SEL(regval)             (BITS(20,21) & ((uint32_t)(regval) << 20U))
#define RCU_PLL0SRC_IRC8M                CFG1_PLL0SEL(0)                    /*!< IRC8M clock selected as source clock of PLL0 */
#define RCU_PLL0SRC_IRC48M               CFG1_PLL0SEL(1)                    /*!< IRC48M clock selected as source clock of PLL0 */
#define RCU_PLL0SRC_HXTAL                CFG1_PLL0SEL(2)                    /*!< HXTAL clock selected as source clock of PLL0 */
#define RCU_PLL0SRC_CKPLL1               CFG1_PLL0SEL(3)                    /*!< CKPLL1 clock selected as source clock of PLL0 */

/* PLL1 input clock source selection */
#define RCU_PLL1SRC_HXTAL                ((uint32_t)0x00000000U)            /*!< HXTAL selected as PLL1 input source clock */
#define RCU_PPLL1SRC_IRC48M              RCU_CFG1_PLL1SEL                   /*!< IRC48M selected as PLL1 input source clock */

/* I2S1 clock source selection */
#define RCU_I2S1SRC_CKSYS               ((uint32_t)0x00000000U)             /*!< system clock selected as I2S1 source clock */
#define RCU_I2S1SRC_CKPLL1               RCU_CFG1_I2S1SEL                   /*!< CK_PLL1 selected as I2S1 source clock */

/* I2S2 clock source selection */
#define RCU_I2S2SRC_CKSYS               ((uint32_t)0x00000000U)             /*!< system clock selected as I2S2 source clock */
#define RCU_I2S2SRC_CKPLL1               RCU_CFG1_I2S2SEL                   /*!< CK_PLL1 selected as I2S2 source clock */

/* deep-sleep mode voltage */
#define DSV_DSLPVS(regval)              (BITS(0,2) & ((uint32_t)(regval) << 0U))
#define RCU_DEEPSLEEP_V_0               DSV_DSLPVS(0)                      /*!< core voltage is default value in deep-sleep mode */
#define RCU_DEEPSLEEP_V_1               DSV_DSLPVS(1)                      /*!< core voltage is (default value-0.05)V in deep-sleep mode */
#define RCU_DEEPSLEEP_V_2               DSV_DSLPVS(2)                      /*!< core voltage is (default value-0.1)V in deep-sleep mode */
#define RCU_DEEPSLEEP_V_3               DSV_DSLPVS(3)                      /*!< core voltage is (default value-0.15)V in deep-sleep mode */
#define RCU_DEEPSLEEP_V_4               DSV_DSLPVS(4)                      /*!< core voltage is (default value-0.2)V in deep-sleep mode */
#define RCU_DEEPSLEEP_V_5               DSV_DSLPVS(5)                      /*!< core voltage is (default value-0.25)V in deep-sleep mode */
#define RCU_DEEPSLEEP_V_6               DSV_DSLPVS(6)                      /*!< core voltage is (default value-0.3)V in deep-sleep mode(customers are not recommended to use it) */
#define RCU_DEEPSLEEP_V_7               DSV_DSLPVS(7)                      /*!< core voltage is (default value-0.35)V in deep-sleep mode(customers are not recommended to use it) */

/* when enter deep-sleep mode, switch to IRC8M clock and wait the SWDLY IRC8M counter and then enter deep-sleep mode */
#define RCU_SWDLY_COUNT(regval)         (BITS(16,20) & ((uint32_t)(regval) << 16U))

/* PLL0 bandwith configuration */
#define PLL0_BW_CFG(regval)             (BITS(0,3) & ((uint32_t)(regval) << 0U))
/* PLL1 bandwith configuration */
#define PLL1_BW_CFG(regval)             (BITS(8,11) & ((uint32_t)(regval) << 8U))

/* IRC64M clock frequency monitor configuration */
#define CKFMCFG0_IRC8MCKFMC(range)      (BITS(1,2) & ((uint32_t)(range) << 1U))
#define RCU_IRC8MCKFMC_5_PERCENT        CKFMCFG0_IRC8MCKFMC(0)             /*!< the IRC8M clock frequency monitoring range is ±5% */
#define RCU_IRC8MCKFMC_10_PERCENT       CKFMCFG0_IRC8MCKFMC(1)             /*!< the IRC8M clock frequency monitoring range is ±10% */
#define RCU_IRC8MCKFMC_15_PERCENT       CKFMCFG0_IRC8MCKFMC(2)             /*!< the IRC8M clock frequency monitoring range is ±15% */
#define RCU_IRC8MCKFMC_20_PERCENT       CKFMCFG0_IRC8MCKFMC(3)             /*!< the IRC8M clock frequency monitoring range is ±20% */

/* 48MHz clock selection */
#define RCU_CK48MSRC_CKPLL0             ((uint32_t)0x00000000U)            /*!< use CK_PLL0 clock */
#define RCU_CK48MSRC_IRC48M             RCU_ADDCTL_CK48MSEL                /*!< select IRC48M clock */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check delay before switch to IRC8M clock and enter deep-sleep mode */
#define NOT_RCU_SWITCH_DELAY(irc8m_cnt)             ((irc8m_cnt) == 0U)
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* peripherals clock and reset configure functions */
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
/* disable reset the peripherals */
void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset);
/* reset the BKP domain */
void rcu_bkp_reset_enable(void);
/* disable the BKP domain reset */
void rcu_bkp_reset_disable(void);

/* system and peripherals clock source, system reset configure functions */
/* configure the system clock source */
void rcu_system_clock_source_config(uint32_t ck_sys);
/* get the system clock source */
uint32_t rcu_system_clock_source_get(void);
/* configure the AHB clock prescaler selection */
void rcu_ahb_clock_config(uint32_t ck_ahb);
/* configure the APB1 clock prescaler selection */
void rcu_apb1_clock_config(uint32_t ck_apb1);
/* configure the APB2 clock prescaler selection */
void rcu_apb2_clock_config(uint32_t ck_apb2);
/* configure the CK_OUT clock source */
void rcu_ckout_config(uint32_t ckout_src);
/* configure the PLL0 clock */
void rcu_pll0_config(uint32_t pll0_src, uint32_t pll0_mul, uint32_t pll0_div);
/* configure the PLL1 clock */
void rcu_pll1_config(uint32_t pll1_src, uint32_t pll1_mul);
/* configure the PREDIV0 division factor */
void rcu_prediv0_config(uint32_t prediv0_div);
/* configure the PREDIV1 division factor */
void rcu_prediv1_config(uint32_t prediv1_div);
/* configure the ADC prescaler factor */
void rcu_adc_clock_config(uint32_t adc_psc);
/* configure the USBFS prescaler factor */
void rcu_usb_clock_config(uint32_t usb_psc);
/* configure the RTC clock source selection */
void rcu_rtc_clock_config(uint32_t rtc_clock_source);
/* configure the I2S1 clock source selection */
void rcu_i2s1_clock_config(uint32_t i2s_clock_source, uint32_t i2s_clock_div);
/* configure the I2S2 clock source selection */
void rcu_i2s2_clock_config(uint32_t i2s_clock_source, uint32_t i2s_clock_div);
/* configure the CK48M clock source selection */
void rcu_ck48m_clock_config(uint32_t ck48m_clock_source);
/* configure the FMC clock source selection */
void rcu_fmc_clock_config(uint32_t fmc_clock_source, uint32_t fmc_clock_div);

/* LXTAL, IRC8M, IRC40K and other oscillator configure functions */
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
/* set the IRC8M adjust value */
void rcu_irc8m_adjust_value_set(uint32_t irc8m_adjval);

/* clock monitor configure functions */
/* enable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_enable(void);
/* disable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_disable(void);
/*enable the LXTAL clock monitor */
void rcu_lxtal_clock_monitor_enable(void);
/* disable the LXTAL clock monitor */
void rcu_lxtal_clock_monitor_disable(void);

/* clock frequency monitor configure functions */
/* enable the clock frequency monitor */
void rcu_clock_freq_monitor_enable(rcu_ckfm_enum ckfm);
/* disable the clock frequency monitor */
void rcu_clock_freq_monitor_disable(rcu_ckfm_enum ckfm);
/* IRC8M clock frequency monitor range configuration */
void rcu_irc8m_freq_monitor_config(uint32_t range);
/* HXTAL clock frequency monitor threshold configuration */
void rcu_hxtal_monitor_threshold_config(uint32_t lthreshold, uint32_t hthreshold);
/* PLL0P clock frequency monitor threshold configuration */
void rcu_pll0p_monitor_threshold_config(uint32_t lthreshold, uint32_t hthreshold);
/* PLL1 clock frequency monitor threshold configuration */
void rcu_pll1_monitor_threshold_config(uint32_t lthreshold, uint32_t hthreshold);

/* voltage configure functions */
/* set the deep sleep mode voltage */
void rcu_deepsleep_voltage_set(uint32_t dsvol);
/* delay before switch to IRC8M clock and enter deep-sleep mode */
void rcu_deepsleep_switch_delay_set(uint32_t irc8m_cnt);

/* lock rcu register */
void rcu_reg_lock(void);
/* unlock rcu register */
void rcu_reg_unlock(void);
/* config PLL0/PLL1 bandwidth */
void rcu_pll_bandwidth_config(uint32_t pll0_bw, uint32_t pll1_bw);

/* clock frequency get functions */
/* get the system clock, bus and peripheral clock frequency */
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock);

/* flag & interrupt functions */
/* get the clock stabilization, peripheral reset and clock frequency failure flags */
FlagStatus rcu_flag_get(rcu_flag_enum flag);
/* clear clock frequency failure flags */
void rcu_flag_clear(rcu_flag_clear_enum flag);
/* clear all the reset flag */
void rcu_all_reset_flag_clear(void);
/* enable the clock interrupt */
void rcu_interrupt_enable(rcu_int_enum interrupt);
/* disable the clock interrupt */
void rcu_interrupt_disable(rcu_int_enum interrupt);
/* get the clock interrupt flags */
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag);
/* clear the clock interrupt flags */
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag);

#endif /* GD32F50X_RCU_H */
