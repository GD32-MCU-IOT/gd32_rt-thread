/*!
    \file    gd32m53x_rcu.c
    \brief   RCU driver

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

#ifndef GD32M53X_RCU_H
#define GD32M53X_RCU_H

#include "gd32m53x.h"

/* RCU definitions */
#define RCU                             RCU_BASE                              /*!< RCU base address */

/* registers definitions */
#define RCU_CTL                         REG32(RCU + 0x00000000U)              /*!< control register */
#define RCU_CFG0                        REG32(RCU + 0x00000004U)              /*!< clock configuration register 0 */
#define RCU_INT                         REG32(RCU + 0x00000008U)              /*!< clock interrupt register */
#define RCU_APB2RST                     REG32(RCU + 0x0000000CU)              /*!< APB2 reset register */
#define RCU_APB1RST                     REG32(RCU + 0x00000010U)              /*!< APB1 reset register */
#define RCU_AHBEN                       REG32(RCU + 0x00000014U)              /*!< AHB1 enable register */
#define RCU_APB2EN                      REG32(RCU + 0x00000018U)              /*!< APB2 enable register */
#define RCU_APB1EN                      REG32(RCU + 0x0000001CU)              /*!< APB1 enable register */
#define RCU_RSTSCK                      REG32(RCU + 0x00000024U)              /*!< reset source / clock register */
#define RCU_AHBRST                      REG32(RCU + 0x00000028U)              /*!< AHB reset register */
#define RCU_CFG1                        REG32(RCU + 0x0000002CU)              /*!< clock configuration register 1 */
#define RCU_CFG2                        REG32(RCU + 0x00000030U)              /*!< clock configuration register 2 */

/* bits definitions */
/* RCU_CTL */
#define RCU_CTL_IRC32MEN                BIT(0)                                /*!< internal high speed oscillator enable */
#define RCU_CTL_IRC32MSTB               BIT(1)                                /*!< IRC32M high speed internal oscillator stabilization flag */
#define RCU_CTL_IRC32MADJ               BITS(3,7)                             /*!< internal 32M RC oscillator clock trim adjust value */
#define RCU_CTL_IRC32MCALIB             BITS(8,15)                            /*!< internal 32M RC oscillator calibration value */
#define RCU_CTL_HXTALEN                 BIT(16)                               /*!< external high speed oscillator enable */
#define RCU_CTL_HXTARST                 BIT(17)                               /*!< External high speed oscillator ready reset */
#define RCU_CTL_HXTALSTB                BIT(18)                               /*!< external crystal oscillator clock stabilization flag */
#define RCU_CTL_HXTALBPS                BIT(19)                               /*!< external crystal oscillator clock bypass mode enable */
#define RCU_CTL_CKMEN                   BIT(20)                               /*!< HXTAL clock monitor enable */
#define RCU_CTL_PLLMEN                  BIT(21)                               /*!< PLL clock monitor enable */
#define RCU_CTL_HXTALSCAL               BIT(22)                               /*!< HXTAL frequency scale select */
#define RCU_CTL_PLLEN                   BIT(24)                               /*!< PLL enable */
#define RCU_CTL_PLLSTB                  BIT(25)                               /*!< PLL clock stabilization flag */

/* RCU_CFG0 */
#define RCU_CFG0_SCS                    BITS(0,1)                             /*!< system clock switch */
#define RCU_CFG0_SCSS                   BITS(2,3)                             /*!< system clock switch status */
#define RCU_CFG0_AHBPSC                 BITS(4,7)                             /*!< AHB prescaler selection */
#define RCU_CFG0_APB1PSC                BITS(8,10)                            /*!< APB1 prescaler selection */
#define RCU_CFG0_APB2PSC                BITS(11,13)                           /*!< APB2 prescaler selection */
#define RCU_CFG0_PLLSEL                 BIT(16)                               /*!< PLL clock source selection */
#define RCU_CFG0_PLLMF                  BITS(17,23)                           /*!< PLL clock multiplication factor */
#define RCU_CFG0_CKOUTSEL               BITS(24,26)                           /*!< CKOUT clock source selection */
#define RCU_CFG0_CKOUTDIV               BITS(28,30)                           /*!< CK_OUT divider which the CK_OUT frequency can be reduced */
#define RCU_CFG0_PLLDV                  BIT(31)                               /*!< CK_PLL divide by 1 or 8 for CK_OUT */

/* RCU_INT */
#define RCU_INT_IRC32KSTBIF             BIT(0)                                /*!< IRC32K stabilization interrupt flag */
#define RCU_INT_IRC32MSTBIF             BIT(2)                                /*!< IRC32M stabilization interrupt flag */
#define RCU_INT_HXTALSTBIF              BIT(3)                                /*!< HXTAL stabilization interrupt flag */
#define RCU_INT_PLLSTBIF                BIT(4)                                /*!< PLL stabilization interrupt flag */
#define RCU_INT_PLLMIF                  BIT(6)                                /*!< PLL clock monitor interrupt flag */
#define RCU_INT_CKMIF                   BIT(7)                                /*!< HXTAL clock stuck interrupt flag */
#define RCU_INT_IRC32KSTBIE             BIT(8)                                /*!< IRC32K stabilization interrupt enable */
#define RCU_INT_IRC32MSTBIE             BIT(10)                               /*!< IRC32M stabilization interrupt enable */
#define RCU_INT_HXTALSTBIE              BIT(11)                               /*!< HXTAL stabilization interrupt enable */
#define RCU_INT_PLLSTBIE                BIT(12)                               /*!< PLL stabilization interrupt enable */
#define RCU_INT_PLLMIE                  BIT(14)                               /*!< PLL clock monitor interrupt enable */
#define RCU_INT_IRC32KSTBIC             BIT(16)                               /*!< IRC32K stabilization interrupt clear */
#define RCU_INT_IRC32MSTBIC             BIT(18)                               /*!< IRC32M stabilization interrupt clear */
#define RCU_INT_HXTALSTBIC              BIT(19)                               /*!< HXTAL stabilization interrupt clear */
#define RCU_INT_PLLSTBIC                BIT(20)                               /*!< PLL stabilization interrupt clear */
#define RCU_INT_PLLMIC                  BIT(22)                               /*!< PLL clock monitor interrupt clear */
#define RCU_INT_CKMIC                   BIT(23)                               /*!< HXTAL clock stuck interrupt clear */

/* RCU_APB2RST */
#define RCU_APB2RST_CFGRST              BIT(0)                                /*!< system configuration reset */
#define RCU_APB2RST_CMPRST              BIT(1)                                /*!< comparator reset */
#define RCU_APB2RST_ADC0RST             BIT(8)                                /*!< ADC0 reset */
#define RCU_APB2RST_ADC2RST             BIT(9)                                /*!< ADC2 reset */
#define RCU_APB2RST_TIMER0RST           BIT(11)                               /*!< TIMER0 reset */
#define RCU_APB2RST_SPIRST              BIT(12)                               /*!< SPI reset */
#define RCU_APB2RST_TIMER7RST           BIT(13)                               /*!< TIMER7 reset */
#define RCU_APB2RST_TIMER1RST           BIT(16)                               /*!< TIMER1 reset */
#define RCU_APB2RST_TIMER2RST           BIT(17)                               /*!< TIMER2 reset */
#define RCU_APB2RST_GPTIMER0RST         BIT(21)                               /*!< GPTIMER0 reset */
#define RCU_APB2RST_GPTIMER1RST         BIT(22)                               /*!< GPTIMER1 reset */
#define RCU_APB2RST_CANRST              BIT(30)                               /*!< CAN reset */

/* RCU_APB1RST */
#define RCU_APB1RST_CPTIMER0RST         BIT(0)                                /*!< CPTIMER0 reset */
#define RCU_APB1RST_CPTIMER1RST         BIT(1)                                /*!< CPTIMER1 reset */
#define RCU_APB1RST_CPTIMERWRST         BIT(4)                                /*!< CPTIMERW reset */
#define RCU_APB1RST_WWDGTRST            BIT(12)                               /*!< WWDGT reset */
#define RCU_APB1RST_UART0RST            BIT(16)                               /*!< UART0 reset */
#define RCU_APB1RST_UART1RST            BIT(17)                               /*!< UART1 reset */
#define RCU_APB1RST_UART2RST            BIT(18)                               /*!< UART2 reset */
#define RCU_APB1RST_UART3RST            BIT(19)                               /*!< UART3 reset */
#define RCU_APB1RST_I2CRST              BIT(21)                               /*!< I2C reset */
#define RCU_APB1RST_CFMURST             BIT(24)                               /*!< CFMU reset */
#define RCU_APB1RST_PMURST              BIT(28)                               /*!< PMU reset */
#define RCU_APB1RST_DACRST              BIT(29)                               /*!< DAC reset */

/* RCU_AHBEN */
#define RCU_AHBEN_DMA0EN                BIT(0)                                /*!< DMA0 clock enable */
#define RCU_AHBEN_DMA1EN                BIT(1)                                /*!< DMA1 clock enable */
#define RCU_AHBEN_SRAMSPEN              BIT(2)                                /*!< SRAM clock enable when sleep mode */
#define RCU_AHBEN_DMAMUXEN              BIT(3)                                /*!< DMAMUX clock enable */
#define RCU_AHBEN_CRCEN                 BIT(6)                                /*!< CRC clock enable */
#define RCU_AHBEN_PAEN                  BIT(16)                               /*!< GPIOA clock enable */
#define RCU_AHBEN_PBEN                  BIT(17)                               /*!< GPIOB clock enable */
#define RCU_AHBEN_PCEN                  BIT(18)                               /*!< GPIOC clock enable */
#define RCU_AHBEN_PDEN                  BIT(19)                               /*!< GPIOD clock enable */
#define RCU_AHBEN_PEEN                  BIT(20)                               /*!< GPIOE clock enable */
#define RCU_AHBEN_PFEN                  BIT(21)                               /*!< GPIOF clock enable */
#define RCU_AHBEN_PGEN                  BIT(22)                               /*!< GPIOG clock enable */
#define RCU_AHBEN_PNEN                  BIT(23)                               /*!< GPION clock enable */
#define RCU_AHBEN_POCEN                 BIT(26)                               /*!< POC clock enable */
#define RCU_AHBEN_GTOCEN                BIT(27)                               /*!< GTOC clock enable */
#define RCU_AHBEN_SVPWMEN               BIT(28)                               /*!< SVPWM clock enable */
#define RCU_AHBEN_TMUEN                 BIT(29)                               /*!< TMU clock enable */

/* RCU_APB2EN */
#define RCU_APB2EN_CFGEN                BIT(0)                                /*!< System configuration clock enable */
#define RCU_APB2EN_CMPEN                BIT(1)                                /*!< Comparator clock enable */
#define RCU_APB2EN_ADC0EN               BIT(8)                                /*!< ADC0 clock enable */
#define RCU_APB2EN_ADC2EN               BIT(9)                                /*!< ADC2 clock enable */
#define RCU_APB2EN_TIMER0EN             BIT(11)                               /*!< TIMER0 clock enable */
#define RCU_APB2EN_SPIEN                BIT(12)                               /*!< SPI clock enable */
#define RCU_APB2EN_TIMER7EN             BIT(13)                               /*!< TIMER7 clock enable */
#define RCU_APB2EN_TIMER1EN             BIT(16)                               /*!< TIMER1 clock enable */
#define RCU_APB2EN_TIMER2EN             BIT(17)                               /*!< TIMER2 clock enable */
#define RCU_APB2EN_GPTIMER0EN           BIT(21)                               /*!< GPTIMER0 clock enable */
#define RCU_APB2EN_GPTIMER1EN           BIT(22)                               /*!< GPTIMER1 clock enable */
#define RCU_APB2EN_EVICEN               BIT(24)                               /*!< EVIC clock enable */
#define RCU_APB2EN_CANEN                BIT(30)                               /*!< CAN clock enable */

/* RCU_APB1EN */
#define RCU_APB1EN_CPTIMER0EN           BIT(0)                                /*!< CPTIMER0 clock enable */
#define RCU_APB1EN_CPTIMER1EN           BIT(1)                                /*!< CPTIMER1 clock enable */
#define RCU_APB1EN_CPTIMERWEN           BIT(4)                                /*!< CPTIMERW clock enable */
#define RCU_APB1EN_WWDGTEN              BIT(12)                               /*!< WWDGT clock enable */
#define RCU_APB1EN_UART0EN              BIT(16)                               /*!< UART0 clock enable */
#define RCU_APB1EN_UART1EN              BIT(17)                               /*!< UART1 clock enable */
#define RCU_APB1EN_UART2EN              BIT(18)                               /*!< UART2 clock enable */
#define RCU_APB1EN_UART3EN              BIT(19)                               /*!< UART3 clock enable */
#define RCU_APB1EN_I2CEN                BIT(21)                               /*!< I2C clock enable */
#define RCU_APB1EN_CFMUEN               BIT(24)                               /*!< CFMU clock enable */
#define RCU_APB1EN_PMUEN                BIT(28)                               /*!< PMU clock enable */
#define RCU_APB1EN_DACEN                BIT(29)                               /*!< DAC clock enable */

/* RCU_RSTSCK */
#define RCU_RSTSCK_IRC32KEN             BIT(0)                                /*!< IRC32K enable */
#define RCU_RSTSCK_IRC32KSTB            BIT(1)                                /*!< IRC32K stabilization flag */
#define RCU_RSTSCK_LOCKUPRSTEN          BIT(10)                               /*!< CPU lock-up reset enable */
#define RCU_RSTSCK_LOHRSTEN             BIT(13)                               /*!< lost of HXTAL reset enable */
#define RCU_RSTSCK_LOPRSTEN             BIT(14)                               /*!< lost of PLL reset enable */
#define RCU_RSTSCK_LVD0RSTF             BIT(16)                               /*!< low voltage 0 detect error reset flag */
#define RCU_RSTSCK_LOCKUPRSTF           BIT(18)                               /*!< CPU lock-up error reset flag */
#define RCU_RSTSCK_LVD1RSTF             BIT(19)                               /*!< low voltage 1 detect error reset flag */
#define RCU_RSTSCK_LVD2RSTF             BIT(20)                               /*!< low voltage 2 detect error reset flag */
#define RCU_RSTSCK_LOHRSTF              BIT(21)                               /*!< lost of HXTAL error reset flag */
#define RCU_RSTSCK_LOPRSTF              BIT(22)                               /*!< lost of PLL error reset flag */
#define RCU_RSTSCK_V11RSTF              BIT(23)                               /*!< 1.1V domain power reset flag */
#define RCU_RSTSCK_RSTFC                BIT(24)                               /*!< reset flag clear */
#define RCU_RSTSCK_OBLRSTF              BIT(25)                               /*!< option byte loader reset flag */
#define RCU_RSTSCK_EPRSTF               BIT(26)                               /*!< external pin reset flag */
#define RCU_RSTSCK_PORRSTF              BIT(27)                               /*!< power reset flag */
#define RCU_RSTSCK_SWRSTF               BIT(28)                               /*!< software reset flag */
#define RCU_RSTSCK_FWDGTRSTF            BIT(29)                               /*!< free watchdog timer reset flag */
#define RCU_RSTSCK_WWDGTRSTF            BIT(30)                               /*!< window watchdog timer reset flag */
#define RCU_RSTSCK_LPRSTF               BIT(31)                               /*!< low-power reset flag */

/* RCU_AHBRST */
#define RCU_AHBRST_DMA0RST              BIT(0)                                /*!< DMA0 reset */
#define RCU_AHBRST_DMA1RST              BIT(1)                                /*!< DMA1 reset */
#define RCU_AHBRST_DMAMUXRST            BIT(3)                                /*!< DMAMUX reset */
#define RCU_AHBRST_CRCRST               BIT(6)                                /*!< CRC reset */
#define RCU_AHBRST_PARST                BIT(16)                               /*!< GPIO port A reset */
#define RCU_AHBRST_PBRST                BIT(17)                               /*!< GPIO port B reset */
#define RCU_AHBRST_PCRST                BIT(18)                               /*!< GPIO port C reset */
#define RCU_AHBRST_PDRST                BIT(19)                               /*!< GPIO port D reset */
#define RCU_AHBRST_PERST                BIT(20)                               /*!< GPIO port E reset */
#define RCU_AHBRST_PFRST                BIT(21)                               /*!< GPIO port F reset */
#define RCU_AHBRST_PGRST                BIT(22)                               /*!< GPIO port G reset */
#define RCU_AHBRST_PNRST                BIT(23)                               /*!< GPIO port N reset */
#define RCU_AHBRST_POCRST               BIT(26)                               /*!< POC reset */
#define RCU_AHBRST_GTOCRST              BIT(27)                               /*!< GTOC reset */
#define RCU_AHBRST_SVPWMRST             BIT(28)                               /*!< SVPWMRST reset */
#define RCU_AHBRST_TMURST               BIT(29)                               /*!< TMU reset */

/* RCU_CFG1 */
#define RCU_CFG1_PREDV                  BITS(0,2)                             /*!< CK_HXTAL divider previous PLL */

/* RCU_CFG2 */
#define RCU_CFG2_I2CSEL                 BITS(8,9)                             /*!< IIC clock source selection */
#define RCU_CFG2_ADCSEL                 BITS(25,26)                           /*!< ADC clock source selection */
#define RCU_CFG2_ADCPSC                 BITS(27,31)                           /*!< ADC prescaler selection */

/* constants definitions */
/* define the peripheral clock enable bit position and its register index offset */
#define RCU_REGIDX_BIT(regidx, bitpos)      (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define RCU_REG_VAL(periph)                 (REG32(RCU + ((uint32_t)(periph) >> 6)))
#define RCU_BIT_POS(val)                    ((uint32_t)(val) & 0x0000001FU)

/* register offset */
/* peripherals enable */
#define AHBEN_REG_OFFSET                ((uint32_t)0x00000014U)              /*!< AHB enable register offset */
#define APB1EN_REG_OFFSET               ((uint32_t)0x0000001CU)              /*!< APB1 enable register offset */
#define APB2EN_REG_OFFSET               ((uint32_t)0x00000018U)              /*!< APB2 enable register offset */

/* peripherals reset */
#define AHBRST_REG_OFFSET               ((uint32_t)0x00000028U)              /*!< AHB reset register offset */
#define APB1RST_REG_OFFSET              ((uint32_t)0x00000010U)              /*!< APB1 reset register offset */
#define APB2RST_REG_OFFSET              ((uint32_t)0x0000000CU)              /*!< APB2 reset register offset */
#define RSTSCK_REG_OFFSET               ((uint32_t)0x00000024U)              /*!< reset source/clock register offset */

/* clock control */
#define CTL_REG_OFFSET                  ((uint32_t)0x00000000U)              /*!< control register offset */
/* clock stabilization and stuck interrupt */
#define INT_REG_OFFSET                  ((uint32_t)0x00000008U)              /*!< clock interrupt register offset */

/* configuration register */
#define CFG1_REG_OFFSET                 ((uint32_t)0x0000002CU)              /*!< clock configuration register 1 offset */
#define CFG2_REG_OFFSET                 ((uint32_t)0x00000030U)              /*!< clock configuration register 2 offset */

/* peripheral clock enable */
typedef enum {
    /* AHB peripherals */
    RCU_DMA0          = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 0U),                /*!< DMA0 clock */
    RCU_DMA1          = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 1U),                /*!< DMA1 clock */
    RCU_DMAMUX        = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 3U),                /*!< DMAMUX clock */
    RCU_CRC           = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 6U),                /*!< CRC clock */
    RCU_GPIOA         = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 16U),               /*!< GPIOA clock */
    RCU_GPIOB         = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 17U),               /*!< GPIOB clock */
    RCU_GPIOC         = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 18U),               /*!< GPIOC clock */
    RCU_GPIOD         = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 19U),               /*!< GPIOD clock */
    RCU_GPIOE         = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 20U),               /*!< GPIOE clock */
    RCU_GPIOF         = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 21U),               /*!< GPIOF clock */
    RCU_GPIOG         = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 22U),               /*!< GPIOG clock */
    RCU_GPION         = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 23U),               /*!< GPION clock */
    RCU_POC           = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 26U),               /*!< POC clock */
    RCU_GTOC          = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 27U),               /*!< GTOC clock */
    RCU_SVPWM         = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 28U),               /*!< SVPWM clock */
    RCU_TMU           = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 29U),               /*!< TMU clock */
    /* APB2 peripherals */
    RCU_SYSCFG        = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 0U),               /*!< SYSCFG clock */
    RCU_CMP           = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 1U),               /*!< CMP clock */
    RCU_ADC0          = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 8U),               /*!< ADC0 clock */
    RCU_ADC2          = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 9U),               /*!< ADC2 clock */
    RCU_TIMER0        = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 11U),              /*!< TIMER0 clock */
    RCU_SPI           = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 12U),              /*!< SPI clock */
    RCU_TIMER7        = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 13U),              /*!< TIMER7 clock */
    RCU_TIMER1        = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 16U),              /*!< TIMER1 clock */
    RCU_TIMER2        = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 17U),              /*!< TIMER2 clock */
    RCU_GPTIMER0      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 21U),              /*!< GPTIMER0 clock */
    RCU_GPTIMER1      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 22U),              /*!< GPTIMER1 clock */
    RCU_EVIC          = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 24U),              /*!< EVIC clock*/
    RCU_CAN           = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 30U),              /*!< CAN clock */
    /* APB1 peripherals */
    RCU_CPTIMER0      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 0U),               /*!< CPTIMER0 clock */
    RCU_CPTIMER1      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 1U),               /*!< CPTIMER1 clock */
    RCU_CPTIMERW      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 4U),               /*!< CPTIMERW clock */
    RCU_WWDGT         = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 12U),              /*!< WWDGT clock */
    RCU_UART0         = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 16U),              /*!< UART0 clock */
    RCU_UART1         = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 17U),              /*!< UART1 clock */
    RCU_UART2         = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 18U),              /*!< UART2 clock */
    RCU_UART3         = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 19U),              /*!< UART3 clock */
    RCU_I2C           = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 21U),              /*!< I2C clock */
    RCU_CFMU          = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 24U),              /*!< CFMU clock */
    RCU_PMU           = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 28U),              /*!< PMU clock */
    RCU_DAC           = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 29U),              /*!< DAC clock */
} rcu_periph_enum;

/* peripherals reset */
typedef enum {
    /* AHB peripherals */
    RCU_DMA0RST       = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 0U),                /*!< DMA0 clock reset */
    RCU_DMA1RST       = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 1U),                /*!< DMA1 clock reset */
    RCU_DMAMUXRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 3U),                /*!< DMAMUX clock reset */
    RCU_CRCRST        = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 6U),                /*!< CRC clock reset */
    RCU_GPIOARST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 16U),               /*!< GPIOA clock reset */
    RCU_GPIOBRST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 17U),               /*!< GPIOB clock reset */
    RCU_GPIOCRST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 18U),               /*!< GPIOC clock reset */
    RCU_GPIODRST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 19U),               /*!< GPIOD clock reset */
    RCU_GPIOERST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 20U),               /*!< GPIOE clock reset */
    RCU_GPIOFRST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 21U),               /*!< GPIOF clock reset */
    RCU_GPIOGRST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 22U),               /*!< GPIOG clock reset */
    RCU_GPIONRST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 23U),               /*!< GPION clock reset */
    RCU_POCRST        = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 26U),               /*!< POC clock reset */
    RCU_GTOCRST       = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 27U),               /*!< GTOC clock reset */
    RCU_SVPWMRST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 28U),               /*!< SVPWM clock reset */
    RCU_TMURST        = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 29U),               /*!< TMU clock reset */
    /* APB2 peripherals */
    RCU_SYSCFGRST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 0U),               /*!< system configuration reset */
    RCU_CMPRST        = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 1U),               /*!< Comparator reset */
    RCU_ADC0RST       = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 8U),               /*!< ADC0 clock reset */
    RCU_ADC2RST       = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 9U),               /*!< ADC2 clock reset */
    RCU_TIMER0RST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 11U),              /*!< TIMER0 clock reset */
    RCU_SPIRST        = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 12U),              /*!< SPI clock reset */
    RCU_TIMER7RST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 13U),              /*!< TIMER7 clock reset */
    RCU_TIMER1RST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 16U),              /*!< TIMER1 clock reset */
    RCU_TIMER2RST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 17U),              /*!< TIMER2 clock reset */
    RCU_GPTIMER0RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 21U),              /*!< GPTIMER0 clock reset */
    RCU_GPTIMER1RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 22U),              /*!< GPTIMER1 clock reset */
    RCU_CANRST        = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 30U),              /*!< CAN clock reset */
    /* APB1 peripherals */
    RCU_CPTIMER0RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 0U),               /*!< CPTIMER0 clock reset */
    RCU_CPTIMER1RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 1U),               /*!< CPTIMER1 clock reset */
    RCU_CPTIMERWRST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 4U),               /*!< CPTIMERW clock reset */
    RCU_WWDGTRST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 12U),              /*!< WWDGT clock reset */
    RCU_UART0RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 16U),              /*!< UART0 clock reset */
    RCU_UART1RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 17U),              /*!< UART1 clock reset */
    RCU_UART2RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 18U),              /*!< UART2 clock reset */
    RCU_UART3RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 19U),              /*!< UART3 clock reset */
    RCU_I2CRST        = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 21U),              /*!< I2C clock reset */
    RCU_CFMURST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 24U),              /*!< CFMU clock reset */
    RCU_PMURST        = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 28U),              /*!< PMU clock reset */
    RCU_DACRST        = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 29U),              /*!< DAC clock reset */
} rcu_periph_reset_enum;

/* peripheral clock enable when sleep mode*/
typedef enum {
    /* AHB peripherals */
    RCU_SRAM_SLP           = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 2U),            /*!< SRAM clock */
    RCU_FMC_SLP            = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 4U),            /*!< FMC clock */
} rcu_periph_sleep_enum;

/* clock stabilization and peripheral reset flags */
typedef enum {
    /* clock stabilization flags */
    RCU_FLAG_IRC32MSTB         = RCU_REGIDX_BIT(CTL_REG_OFFSET, 1U),         /*!< IRC32M stabilization flag */
    RCU_FLAG_HXTALSTB          = RCU_REGIDX_BIT(CTL_REG_OFFSET, 18U),        /*!< HXTAL stabilization flag */
    RCU_FLAG_PLLSTB            = RCU_REGIDX_BIT(CTL_REG_OFFSET, 25U),        /*!< PLL stabilization flag */
    /* reset source flags */
    RCU_FLAG_IRC32KSTB         = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 1U),      /*!< IRC32K stabilization flag */
    RCU_FLAG_LVD0RST           = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 16U),     /*!< low voltage0 detect error reset flag */
    RCU_FLAG_LOCKUPRST         = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 18U),     /*!< CPU LOCK UP error reset flag */
    RCU_FLAG_LVD1RST           = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 19U),     /*!< low voltage1 detect error reset flag */
    RCU_FLAG_LVD2RST           = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 20U),     /*!< low voltage2 detect error reset flag */
    RCU_FLAG_LOHRST            = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 21U),     /*!< lost of HXTAL error reset flag */
    RCU_FLAG_LOPRST            = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 22U),     /*!< lost of PLL error reset flag */
    RCU_FLAG_V11RST            = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 23U),     /*!< 1.1V domain Power reset flag */
    RCU_FLAG_RSTFC             = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 24U),     /*!< reset flag clear */
    RCU_FLAG_OBLRST            = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 25U),     /*!< option byte loader reset flag */
    RCU_FLAG_EPRST             = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 26U),     /*!< external PIN reset flag */
    RCU_FLAG_PORRST            = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 27U),     /*!< power reset flag */
    RCU_FLAG_SWRST             = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 28U),     /*!< software reset flag */
    RCU_FLAG_FWDGTRST          = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 29U),     /*!< FWDGT reset flag */
    RCU_FLAG_WWDGTRST          = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 30U),     /*!< WWDGT reset flag */
    RCU_FLAG_LPRST             = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 31U),     /*!< low-power reset flag */
} rcu_flag_enum;

/* clock stabilization and ckm interrupt flags */
typedef enum {
    RCU_INT_FLAG_IRC32KSTB     = RCU_REGIDX_BIT(INT_REG_OFFSET, 0U),         /*!< IRC32K stabilization interrupt flag */
    RCU_INT_FLAG_IRC32MSTB     = RCU_REGIDX_BIT(INT_REG_OFFSET, 2U),         /*!< IRC32M stabilization interrupt flag */
    RCU_INT_FLAG_HXTALSTB      = RCU_REGIDX_BIT(INT_REG_OFFSET, 3U),         /*!< HXTAL stabilization interrupt flag */
    RCU_INT_FLAG_PLLSTB        = RCU_REGIDX_BIT(INT_REG_OFFSET, 4U),         /*!< PLL stabilization interrupt flag */
    RCU_INT_FLAG_PLLM          = RCU_REGIDX_BIT(INT_REG_OFFSET, 6U),         /*!< PLL clock monitor interrupt flag */
    RCU_INT_FLAG_CKM           = RCU_REGIDX_BIT(INT_REG_OFFSET, 7U),         /*!< HXTAL clock stuck interrupt flag */
} rcu_int_flag_enum;

/* clock stabilization and stuck interrupt flags clear */
typedef enum {
    RCU_INT_FLAG_IRC32KSTB_CLR = RCU_REGIDX_BIT(INT_REG_OFFSET, 16U),        /*!< IRC32K stabilization interrupt flag clear */
    RCU_INT_FLAG_IRC32MSTB_CLR = RCU_REGIDX_BIT(INT_REG_OFFSET, 18U),        /*!< IRC32M stabilization interrupt flag clear */
    RCU_INT_FLAG_HXTALSTB_CLR  = RCU_REGIDX_BIT(INT_REG_OFFSET, 19U),        /*!< HXTAL stabilization interrupt flag clear */
    RCU_INT_FLAG_PLLSTB_CLR    = RCU_REGIDX_BIT(INT_REG_OFFSET, 20U),        /*!< PLL stabilization interrupt flag clear */
    RCU_INT_FLAG_PLLM_CLR      = RCU_REGIDX_BIT(INT_REG_OFFSET, 22U),        /*!< PLL clock monitor interrupt clear */
    RCU_INT_FLAG_CKM_CLR       = RCU_REGIDX_BIT(INT_REG_OFFSET, 23U),        /*!< CKM interrupt flag clear */
} rcu_int_flag_clear_enum;

/* clock stabilization interrupt enable or disable */
typedef enum {
    RCU_INT_IRC32KSTB          = RCU_REGIDX_BIT(INT_REG_OFFSET, 8U),         /*!< IRC32K stabilization interrupt enable */
    RCU_INT_IRC32MSTB          = RCU_REGIDX_BIT(INT_REG_OFFSET, 10U),        /*!< IRC32M stabilization interrupt enable */
    RCU_INT_HXTALSTB           = RCU_REGIDX_BIT(INT_REG_OFFSET, 11U),        /*!< HXTAL stabilization interrupt enable */
    RCU_INT_PLLSTB             = RCU_REGIDX_BIT(INT_REG_OFFSET, 12U),        /*!< PLL stabilization interrupt enable */
    RCU_INT_PLLM               = RCU_REGIDX_BIT(INT_REG_OFFSET, 14U),        /*!< PLL clock monitor interrupt enable */
} rcu_int_enum;

/* oscillator types */
typedef enum {
    RCU_HXTAL                  = RCU_REGIDX_BIT(CTL_REG_OFFSET, 16U),        /*!< HXTAL */
    RCU_IRC32M                 = RCU_REGIDX_BIT(CTL_REG_OFFSET, 0U),         /*!< IRC32M */
    RCU_IRC32K                 = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 0U),      /*!< IRC32K */
    RCU_PLL_CK                 = RCU_REGIDX_BIT(CTL_REG_OFFSET, 24U),        /*!< PLL */
} rcu_osci_type_enum;

/* rcu clock frequency */
typedef enum {
    CK_SYS      = 0U,                                                        /*!< system clock */
    CK_AHB,                                                                  /*!< AHB clock */
    CK_APB1,                                                                 /*!< APB1 clock */
    CK_APB2,                                                                 /*!< APB2 clock */
} rcu_clock_freq_enum;

/* HXTAL frequency scale select */
#define HXTAL_SCALE_1M_TO_10M           ((uint32_t)0x00000000U)              /*!< HXTAL scale is 1M-10MHz */
#define HXTAL_SCALE_10M_TO_24M          RCU_CTL_HXTALSCAL                    /*!< HXTAL scale is 10M-24MHz */

/* RCU_CFG0 register bit define */
/* system clock source select */
#define CFG0_SCS(regval)                (BITS(0,1) & ((uint32_t)(regval) << 0))
#define RCU_CKSYSSRC_IRC32M             CFG0_SCS(0)                          /*!< system clock source select IRC32M */
#define RCU_CKSYSSRC_HXTAL              CFG0_SCS(1)                          /*!< system clock source select HXTAL */
#define RCU_CKSYSSRC_PLL                CFG0_SCS(2)                          /*!< system clock source select PLL */

/* system clock source select status */
#define CFG0_SCSS(regval)               (BITS(2,3) & ((uint32_t)(regval) << 2))
#define RCU_SCSS_IRC32M                 CFG0_SCSS(0)                         /*!< system clock source select IRC32M */
#define RCU_SCSS_HXTAL                  CFG0_SCSS(1)                         /*!< system clock source select HXTAL */
#define RCU_SCSS_PLL                    CFG0_SCSS(2)                         /*!< system clock source select PLL */

/* AHB prescaler selection */
#define CFG0_AHBPSC(regval)             (BITS(4,7) & ((uint32_t)(regval) << 4))
#define RCU_AHB_CKSYS_DIV1              CFG0_AHBPSC(0)                       /*!< AHB prescaler select CK_SYS */
#define RCU_AHB_CKSYS_DIV2              CFG0_AHBPSC(8)                       /*!< AHB prescaler select CK_SYS/2 */
#define RCU_AHB_CKSYS_DIV4              CFG0_AHBPSC(9)                       /*!< AHB prescaler select CK_SYS/4 */
#define RCU_AHB_CKSYS_DIV8              CFG0_AHBPSC(10)                      /*!< AHB prescaler select CK_SYS/8 */
#define RCU_AHB_CKSYS_DIV16             CFG0_AHBPSC(11)                      /*!< AHB prescaler select CK_SYS/16 */
#define RCU_AHB_CKSYS_DIV64             CFG0_AHBPSC(12)                      /*!< AHB prescaler select CK_SYS/64 */
#define RCU_AHB_CKSYS_DIV128            CFG0_AHBPSC(13)                      /*!< AHB prescaler select CK_SYS/128 */
#define RCU_AHB_CKSYS_DIV256            CFG0_AHBPSC(14)                      /*!< AHB prescaler select CK_SYS/256 */
#define RCU_AHB_CKSYS_DIV512            CFG0_AHBPSC(15)                      /*!< AHB prescaler select CK_SYS/512 */

/* APB1 prescaler selection */
#define CFG0_APB1PSC(regval)            (BITS(8,10) & ((uint32_t)(regval) << 8))
#define RCU_APB1_CKAHB_DIV1             CFG0_APB1PSC(0)                      /*!< APB1 prescaler select CK_AHB */
#define RCU_APB1_CKAHB_DIV2             CFG0_APB1PSC(4)                      /*!< APB1 prescaler select CK_AHB/2 */
#define RCU_APB1_CKAHB_DIV4             CFG0_APB1PSC(5)                      /*!< APB1 prescaler select CK_AHB/4 */
#define RCU_APB1_CKAHB_DIV8             CFG0_APB1PSC(6)                      /*!< APB1 prescaler select CK_AHB/8 */
#define RCU_APB1_CKAHB_DIV16            CFG0_APB1PSC(7)                      /*!< APB1 prescaler select CK_AHB/16 */

/* APB2 prescaler selection */
#define CFG0_APB2PSC(regval)            (BITS(11,13) & ((uint32_t)(regval) << 11))
#define RCU_APB2_CKAHB_DIV1             CFG0_APB2PSC(0)                      /*!< APB2 prescaler select CK_AHB */
#define RCU_APB2_CKAHB_DIV2             CFG0_APB2PSC(4)                      /*!< APB2 prescaler select CK_AHB/2 */
#define RCU_APB2_CKAHB_DIV4             CFG0_APB2PSC(5)                      /*!< APB2 prescaler select CK_AHB/4 */
#define RCU_APB2_CKAHB_DIV8             CFG0_APB2PSC(6)                      /*!< APB2 prescaler select CK_AHB/8 */
#define RCU_APB2_CKAHB_DIV16            CFG0_APB2PSC(7)                      /*!< APB2 prescaler select CK_AHB/16 */

/* RCU system reset */
#define RCU_SYSRST_LOCKUP               RCU_RSTSCK_LOCKUPRSTEN               /*!< CPU lock-up reset */
#define RCU_SYSRST_LOH                  RCU_RSTSCK_LOHRSTEN                  /*!< lost of HXTAL error reset */
#define RCU_SYSRST_LOP                  RCU_RSTSCK_LOPRSTEN                  /*!< lost of PLL reset */

/* ADC prescaler select */
#define CFG2_ADCPSC(regval)             (BITS(27,31) & ((uint32_t)(regval) << 27))
#define RCU_CK_ADCPRE_DIV2              CFG2_ADCPSC(0)                       /*!< ADC prescaler select CK_ADCPRE/2 */
#define RCU_CK_ADCPRE_DIV3              CFG2_ADCPSC(1)                       /*!< ADC prescaler select CK_ADCPRE/3 */
#define RCU_CK_ADCPRE_DIV4              CFG2_ADCPSC(2)                       /*!< ADC prescaler select CK_ADCPRE/4 */
#define RCU_CK_ADCPRE_DIV5              CFG2_ADCPSC(3)                       /*!< ADC prescaler select CK_ADCPRE/5 */
#define RCU_CK_ADCPRE_DIV6              CFG2_ADCPSC(4)                       /*!< ADC prescaler select CK_ADCPRE/6 */
#define RCU_CK_ADCPRE_DIV7              CFG2_ADCPSC(5)                       /*!< ADC prescaler select CK_ADCPRE/7 */
#define RCU_CK_ADCPRE_DIV8              CFG2_ADCPSC(6)                       /*!< ADC prescaler select CK_ADCPRE/8 */
#define RCU_CK_ADCPRE_DIV9              CFG2_ADCPSC(7)                       /*!< ADC prescaler select CK_ADCPRE/9 */
#define RCU_CK_ADCPRE_DIV10             CFG2_ADCPSC(8)                       /*!< ADC prescaler select CK_ADCPRE/10 */
#define RCU_CK_ADCPRE_DIV11             CFG2_ADCPSC(9)                       /*!< ADC prescaler select CK_ADCPRE/11 */
#define RCU_CK_ADCPRE_DIV12             CFG2_ADCPSC(10)                      /*!< ADC prescaler select CK_ADCPRE/12 */
#define RCU_CK_ADCPRE_DIV13             CFG2_ADCPSC(11)                      /*!< ADC prescaler select CK_ADCPRE/13 */
#define RCU_CK_ADCPRE_DIV14             CFG2_ADCPSC(12)                      /*!< ADC prescaler select CK_ADCPRE/14 */
#define RCU_CK_ADCPRE_DIV15             CFG2_ADCPSC(13)                      /*!< ADC prescaler select CK_ADCPRE/15 */
#define RCU_CK_ADCPRE_DIV16             CFG2_ADCPSC(14)                      /*!< ADC prescaler select CK_ADCPRE/16 */
#define RCU_CK_ADCPRE_DIV17             CFG2_ADCPSC(15)                      /*!< ADC prescaler select CK_ADCPRE/17 */
#define RCU_CK_ADCPRE_DIV18             CFG2_ADCPSC(16)                      /*!< ADC prescaler select CK_ADCPRE/18 */
#define RCU_CK_ADCPRE_DIV19             CFG2_ADCPSC(17)                      /*!< ADC prescaler select CK_ADCPRE/19 */
#define RCU_CK_ADCPRE_DIV20             CFG2_ADCPSC(18)                      /*!< ADC prescaler select CK_ADCPRE/20 */
#define RCU_CK_ADCPRE_DIV21             CFG2_ADCPSC(19)                      /*!< ADC prescaler select CK_ADCPRE/21 */
#define RCU_CK_ADCPRE_DIV22             CFG2_ADCPSC(20)                      /*!< ADC prescaler select CK_ADCPRE/22 */
#define RCU_CK_ADCPRE_DIV23             CFG2_ADCPSC(21)                      /*!< ADC prescaler select CK_ADCPRE/23 */
#define RCU_CK_ADCPRE_DIV24             CFG2_ADCPSC(22)                      /*!< ADC prescaler select CK_ADCPRE/24 */
#define RCU_CK_ADCPRE_DIV25             CFG2_ADCPSC(23)                      /*!< ADC prescaler select CK_ADCPRE/25 */
#define RCU_CK_ADCPRE_DIV26             CFG2_ADCPSC(24)                      /*!< ADC prescaler select CK_ADCPRE/26 */
#define RCU_CK_ADCPRE_DIV27             CFG2_ADCPSC(25)                      /*!< ADC prescaler select CK_ADCPRE/27 */
#define RCU_CK_ADCPRE_DIV28             CFG2_ADCPSC(26)                      /*!< ADC prescaler select CK_ADCPRE/28 */
#define RCU_CK_ADCPRE_DIV29             CFG2_ADCPSC(27)                      /*!< ADC prescaler select CK_ADCPRE/29 */
#define RCU_CK_ADCPRE_DIV30             CFG2_ADCPSC(28)                      /*!< ADC prescaler select CK_ADCPRE/30 */
#define RCU_CK_ADCPRE_DIV31             CFG2_ADCPSC(29)                      /*!< ADC prescaler select CK_ADCPRE/31 */
#define RCU_CK_ADCPRE_DIV32             CFG2_ADCPSC(30)                      /*!< ADC prescaler select CK_ADCPRE/32 */

/* CK_ADC clock source selection */
#define CFG2_ADCSEL(regval)             (BITS(25,26) & ((uint32_t)(regval) << 25))
#define RCU_CK_ADCPRE_PCLK2             CFG2_ADCSEL(0)                       /*!< CK_ADC clock source select PCLK2 */
#define RCU_CK_ADCPRE_HXTAL             CFG2_ADCSEL(1)                       /*!< CK_ADC clock source select HXTAL */
#define RCU_CK_ADCPRE_PLL               CFG2_ADCSEL(2)                       /*!< CK_ADC clock source select PLL */
#define RCU_CK_ADCPRE_IRC32M            CFG2_ADCSEL(3)                       /*!< CK_ADC clock source select IRC32M */

/* CK_I2C clock source selection */
#define CFG2_I2CSEL(regval)             (BITS(8,9) & ((uint32_t)(regval) << 8))
#define RCU_CKI2C_PCLK1                 CFG2_I2CSEL(0)                       /*!< CK_I2C clock source select PCLK1 */
#define RCU_CKI2C_PLL                   CFG2_I2CSEL(1)                       /*!< CK_I2C clock source select PLL */
#define RCU_CKI2C_IRC32M                CFG2_I2CSEL(2)                       /*!< CK_I2C clock source select IRC32M */
#define RCU_CKI2C_HXTAL                 CFG2_I2CSEL(3)                       /*!< CK_I2C clock source select HXTAL */

/* PLL clock source selection */
#define RCU_PLLSRC_HXTAL                ((uint32_t)0x00000000U)              /*!< HXTAL is selected as clock source of PLL */
#define RCU_PLLSRC_IRC32M               RCU_CFG0_PLLSEL                      /*!< IRC32M clock is selected as clock source of PLL */

/* PLL clock multiplication factor */
#define CFG0_PLLMF(regval)              (BITS(17,23) & ((uint32_t)(regval) << 17))
#define RCU_PLL_MUL4                    CFG0_PLLMF(7)                        /*!< PLL clock source multiply by 4 */
#define RCU_PLL_MUL4POINT5              CFG0_PLLMF(8)                        /*!< PLL clock source multiply by 4.5 */
#define RCU_PLL_MUL5                    CFG0_PLLMF(9)                        /*!< PLL clock source multiply by 5 */
#define RCU_PLL_MUL5POINT5              CFG0_PLLMF(10)                       /*!< PLL clock source multiply by 5.5 */
#define RCU_PLL_MUL6                    CFG0_PLLMF(11)                       /*!< PLL clock source multiply by 6 */
#define RCU_PLL_MUL6POINT5              CFG0_PLLMF(12)                       /*!< PLL clock source multiply by 6.5 */
#define RCU_PLL_MUL7                    CFG0_PLLMF(13)                       /*!< PLL clock source multiply by 7 */
#define RCU_PLL_MUL7POINT5              CFG0_PLLMF(14)                       /*!< PLL clock source multiply by 7.5 */
#define RCU_PLL_MUL8                    CFG0_PLLMF(15)                       /*!< PLL clock source multiply by 8 */
#define RCU_PLL_MUL8POINT5              CFG0_PLLMF(16)                       /*!< PLL clock source multiply by 8.5 */
#define RCU_PLL_MUL9                    CFG0_PLLMF(17)                       /*!< PLL clock source multiply by 9 */
#define RCU_PLL_MUL9POINT5              CFG0_PLLMF(18)                       /*!< PLL clock source multiply by 9.5 */
#define RCU_PLL_MUL10                   CFG0_PLLMF(19)                       /*!< PLL clock source multiply by 10 */
#define RCU_PLL_MUL10POINT5             CFG0_PLLMF(20)                       /*!< PLL clock source multiply by 10.5 */
#define RCU_PLL_MUL11                   CFG0_PLLMF(21)                       /*!< PLL clock source multiply by 11 */
#define RCU_PLL_MUL11POINT5             CFG0_PLLMF(22)                       /*!< PLL clock source multiply by 11.5 */
#define RCU_PLL_MUL12                   CFG0_PLLMF(23)                       /*!< PLL clock source multiply by 12 */
#define RCU_PLL_MUL12POINT5             CFG0_PLLMF(24)                       /*!< PLL clock source multiply by 12.5 */
#define RCU_PLL_MUL13                   CFG0_PLLMF(25)                       /*!< PLL clock source multiply by 13 */
#define RCU_PLL_MUL13POINT5             CFG0_PLLMF(26)                       /*!< PLL clock source multiply by 13.5 */
#define RCU_PLL_MUL14                   CFG0_PLLMF(27)                       /*!< PLL clock source multiply by 14 */
#define RCU_PLL_MUL14POINT5             CFG0_PLLMF(28)                       /*!< PLL clock source multiply by 14.5 */
#define RCU_PLL_MUL15                   CFG0_PLLMF(29)                       /*!< PLL clock source multiply by 15 */
#define RCU_PLL_MUL15POINT5             CFG0_PLLMF(30)                       /*!< PLL clock source multiply by 15.5 */
#define RCU_PLL_MUL16                   CFG0_PLLMF(31)                       /*!< PLL clock source multiply by 16 */
#define RCU_PLL_MUL16POINT5             CFG0_PLLMF(32)                       /*!< PLL clock source multiply by 16.5 */
#define RCU_PLL_MUL17                   CFG0_PLLMF(33)                       /*!< PLL clock source multiply by 17 */
#define RCU_PLL_MUL17POINT5             CFG0_PLLMF(34)                       /*!< PLL clock source multiply by 17.5 */
#define RCU_PLL_MUL18                   CFG0_PLLMF(35)                       /*!< PLL clock source multiply by 18 */
#define RCU_PLL_MUL18POINT5             CFG0_PLLMF(36)                       /*!< PLL clock source multiply by 18.5 */
#define RCU_PLL_MUL19                   CFG0_PLLMF(37)                       /*!< PLL clock source multiply by 19 */
#define RCU_PLL_MUL19POINT5             CFG0_PLLMF(38)                       /*!< PLL clock source multiply by 19.5 */
#define RCU_PLL_MUL20                   CFG0_PLLMF(39)                       /*!< PLL clock source multiply by 20 */
#define RCU_PLL_MUL20POINT5             CFG0_PLLMF(40)                       /*!< PLL clock source multiply by 20.5 */
#define RCU_PLL_MUL21                   CFG0_PLLMF(41)                       /*!< PLL clock source multiply by 21 */
#define RCU_PLL_MUL21POINT5             CFG0_PLLMF(42)                       /*!< PLL clock source multiply by 21.5 */
#define RCU_PLL_MUL22                   CFG0_PLLMF(43)                       /*!< PLL clock source multiply by 22 */
#define RCU_PLL_MUL22POINT5             CFG0_PLLMF(44)                       /*!< PLL clock source multiply by 22.5 */
#define RCU_PLL_MUL23                   CFG0_PLLMF(45)                       /*!< PLL clock source multiply by 23 */
#define RCU_PLL_MUL23POINT5             CFG0_PLLMF(46)                       /*!< PLL clock source multiply by 23.5 */
#define RCU_PLL_MUL24                   CFG0_PLLMF(47)                       /*!< PLL clock source multiply by 24 */
#define RCU_PLL_MUL24POINT5             CFG0_PLLMF(48)                       /*!< PLL clock source multiply by 24.5 */
#define RCU_PLL_MUL25                   CFG0_PLLMF(49)                       /*!< PLL clock source multiply by 25 */
#define RCU_PLL_MUL25POINT5             CFG0_PLLMF(50)                       /*!< PLL clock source multiply by 25.5 */
#define RCU_PLL_MUL26                   CFG0_PLLMF(51)                       /*!< PLL clock source multiply by 26 */
#define RCU_PLL_MUL26POINT5             CFG0_PLLMF(52)                       /*!< PLL clock source multiply by 26.5 */
#define RCU_PLL_MUL27                   CFG0_PLLMF(53)                       /*!< PLL clock source multiply by 27 */
#define RCU_PLL_MUL27POINT5             CFG0_PLLMF(54)                       /*!< PLL clock source multiply by 27.5 */
#define RCU_PLL_MUL28                   CFG0_PLLMF(55)                       /*!< PLL clock source multiply by 28 */
#define RCU_PLL_MUL28POINT5             CFG0_PLLMF(56)                       /*!< PLL clock source multiply by 28.5 */
#define RCU_PLL_MUL29                   CFG0_PLLMF(57)                       /*!< PLL clock source multiply by 29 */
#define RCU_PLL_MUL29POINT5             CFG0_PLLMF(58)                       /*!< PLL clock source multiply by 29.5 */
#define RCU_PLL_MUL30                   CFG0_PLLMF(59)                       /*!< PLL clock source multiply by 30 */
#define RCU_PLL_MUL30POINT5             CFG0_PLLMF(60)                       /*!< PLL clock source multiply by 30.5 */
#define RCU_PLL_MUL31                   CFG0_PLLMF(61)                       /*!< PLL clock source multiply by 31 */
#define RCU_PLL_MUL31POINT5             CFG0_PLLMF(62)                       /*!< PLL clock source multiply by 31.5 */
#define RCU_PLL_MUL32                   CFG0_PLLMF(63)                       /*!< PLL clock source multiply by 32 */
#define RCU_PLL_MUL32POINT5             CFG0_PLLMF(64)                       /*!< PLL clock source multiply by 32.5 */
#define RCU_PLL_MUL33                   CFG0_PLLMF(65)                       /*!< PLL clock source multiply by 33 */
#define RCU_PLL_MUL33POINT5             CFG0_PLLMF(66)                       /*!< PLL clock source multiply by 33.5 */
#define RCU_PLL_MUL34                   CFG0_PLLMF(67)                       /*!< PLL clock source multiply by 34 */
#define RCU_PLL_MUL34POINT5             CFG0_PLLMF(68)                       /*!< PLL clock source multiply by 34.5 */
#define RCU_PLL_MUL35                   CFG0_PLLMF(69)                       /*!< PLL clock source multiply by 35 */
#define RCU_PLL_MUL35POINT5             CFG0_PLLMF(70)                       /*!< PLL clock source multiply by 35.5 */
#define RCU_PLL_MUL36                   CFG0_PLLMF(71)                       /*!< PLL clock source multiply by 36 */
#define RCU_PLL_MUL36POINT5             CFG0_PLLMF(72)                       /*!< PLL clock source multiply by 36.5 */
#define RCU_PLL_MUL37                   CFG0_PLLMF(73)                       /*!< PLL clock source multiply by 37 */
#define RCU_PLL_MUL37POINT5             CFG0_PLLMF(74)                       /*!< PLL clock source multiply by 37.5 */
#define RCU_PLL_MUL38                   CFG0_PLLMF(75)                       /*!< PLL clock source multiply by 38 */
#define RCU_PLL_MUL38POINT5             CFG0_PLLMF(76)                       /*!< PLL clock source multiply by 38.5 */
#define RCU_PLL_MUL39                   CFG0_PLLMF(77)                       /*!< PLL clock source multiply by 39 */
#define RCU_PLL_MUL39POINT5             CFG0_PLLMF(78)                       /*!< PLL clock source multiply by 39.5 */
#define RCU_PLL_MUL40                   CFG0_PLLMF(79)                       /*!< PLL clock source multiply by 40 */
#define RCU_PLL_MUL40POINT5             CFG0_PLLMF(80)                       /*!< PLL clock source multiply by 40.5 */
#define RCU_PLL_MUL41                   CFG0_PLLMF(81)                       /*!< PLL clock source multiply by 41 */
#define RCU_PLL_MUL41POINT5             CFG0_PLLMF(82)                       /*!< PLL clock source multiply by 41.5 */
#define RCU_PLL_MUL42                   CFG0_PLLMF(83)                       /*!< PLL clock source multiply by 42 */
#define RCU_PLL_MUL42POINT5             CFG0_PLLMF(84)                       /*!< PLL clock source multiply by 42.5 */
#define RCU_PLL_MUL43                   CFG0_PLLMF(85)                       /*!< PLL clock source multiply by 43 */
#define RCU_PLL_MUL43POINT5             CFG0_PLLMF(86)                       /*!< PLL clock source multiply by 43.5 */
#define RCU_PLL_MUL44                   CFG0_PLLMF(87)                       /*!< PLL clock source multiply by 44 */
#define RCU_PLL_MUL44POINT5             CFG0_PLLMF(88)                       /*!< PLL clock source multiply by 44.5 */
#define RCU_PLL_MUL45                   CFG0_PLLMF(89)                       /*!< PLL clock source multiply by 45 */
#define RCU_PLL_MUL45POINT5             CFG0_PLLMF(90)                       /*!< PLL clock source multiply by 45.5 */
#define RCU_PLL_MUL46                   CFG0_PLLMF(91)                       /*!< PLL clock source multiply by 46 */
#define RCU_PLL_MUL46POINT5             CFG0_PLLMF(92)                       /*!< PLL clock source multiply by 46.5 */
#define RCU_PLL_MUL47                   CFG0_PLLMF(93)                       /*!< PLL clock source multiply by 47 */
#define RCU_PLL_MUL47POINT5             CFG0_PLLMF(94)                       /*!< PLL clock source multiply by 47.5 */
#define RCU_PLL_MUL48                   CFG0_PLLMF(95)                       /*!< PLL clock source multiply by 48 */
#define RCU_PLL_MUL48POINT5             CFG0_PLLMF(96)                       /*!< PLL clock source multiply by 48.5 */
#define RCU_PLL_MUL49                   CFG0_PLLMF(97)                       /*!< PLL clock source multiply by 49 */
#define RCU_PLL_MUL49POINT5             CFG0_PLLMF(98)                       /*!< PLL clock source multiply by 49.5 */
#define RCU_PLL_MUL50                   CFG0_PLLMF(99)                       /*!< PLL clock source multiply by 50 */
#define RCU_PLL_MUL50POINT5             CFG0_PLLMF(100)                      /*!< PLL clock source multiply by 50.5 */
#define RCU_PLL_MUL51                   CFG0_PLLMF(101)                      /*!< PLL clock source multiply by 51 */
#define RCU_PLL_MUL51POINT5             CFG0_PLLMF(102)                      /*!< PLL clock source multiply by 51.5 */
#define RCU_PLL_MUL52                   CFG0_PLLMF(103)                      /*!< PLL clock source multiply by 52 */
#define RCU_PLL_MUL52POINT5             CFG0_PLLMF(104)                      /*!< PLL clock source multiply by 52.5 */
#define RCU_PLL_MUL53                   CFG0_PLLMF(105)                      /*!< PLL clock source multiply by 53 */
#define RCU_PLL_MUL53POINT5             CFG0_PLLMF(106)                      /*!< PLL clock source multiply by 53.5 */
#define RCU_PLL_MUL54                   CFG0_PLLMF(107)                      /*!< PLL clock source multiply by 54 */
#define RCU_PLL_MUL54POINT5             CFG0_PLLMF(108)                      /*!< PLL clock source multiply by 54.5 */
#define RCU_PLL_MUL55                   CFG0_PLLMF(109)                      /*!< PLL clock source multiply by 55 */
#define RCU_PLL_MUL55POINT5             CFG0_PLLMF(110)                      /*!< PLL clock source multiply by 55.5 */
#define RCU_PLL_MUL56                   CFG0_PLLMF(111)                      /*!< PLL clock source multiply by 56 */
#define RCU_PLL_MUL56POINT5             CFG0_PLLMF(112)                      /*!< PLL clock source multiply by 56.5 */
#define RCU_PLL_MUL57                   CFG0_PLLMF(113)                      /*!< PLL clock source multiply by 57 */
#define RCU_PLL_MUL57POINT5             CFG0_PLLMF(114)                      /*!< PLL clock source multiply by 57.5 */
#define RCU_PLL_MUL58                   CFG0_PLLMF(115)                      /*!< PLL clock source multiply by 58 */
#define RCU_PLL_MUL58POINT5             CFG0_PLLMF(116)                      /*!< PLL clock source multiply by 58.5 */
#define RCU_PLL_MUL59                   CFG0_PLLMF(117)                      /*!< PLL clock source multiply by 59 */
#define RCU_PLL_MUL59POINT5             CFG0_PLLMF(118)                      /*!< PLL clock source multiply by 59.5 */
#define RCU_PLL_MUL60                   CFG0_PLLMF(119)                      /*!< PLL clock source multiply by 60 */
#define RCU_PLL_MUL60POINT5             CFG0_PLLMF(120)                      /*!< PLL clock source multiply by 60.5 */
#define RCU_PLL_MUL61                   CFG0_PLLMF(121)                      /*!< PLL clock source multiply by 61 */
#define RCU_PLL_MUL61POINT5             CFG0_PLLMF(122)                      /*!< PLL clock source multiply by 61.5 */
#define RCU_PLL_MUL62                   CFG0_PLLMF(123)                      /*!< PLL clock source multiply by 62 */
#define RCU_PLL_MUL62POINT5             CFG0_PLLMF(124)                      /*!< PLL clock source multiply by 62.5 */
#define RCU_PLL_MUL63                   CFG0_PLLMF(125)                      /*!< PLL clock source multiply by 63 */
#define RCU_PLL_MUL63POINT5             CFG0_PLLMF(126)                      /*!< PLL clock source multiply by 63.5 */
#define RCU_PLL_MUL64                   CFG0_PLLMF(127)                      /*!< PLL clock source multiply by 64 */

/* CKOUT Clock source selection */
#define CFG0_CKOUTSEL(regval)           (BITS(24,26) & ((uint32_t)(regval) << 24))
#define RCU_CKOUTSRC_NONE               CFG0_CKOUTSEL(0)                     /*!< no clock is selected */
#define RCU_CKOUTSRC_IRC32K             CFG0_CKOUTSEL(2)                     /*!< IRC32K is selected as CK_OUT clock source */
#define RCU_CKOUTSRC_CKSYS              CFG0_CKOUTSEL(4)                     /*!< system clock is selected as CK_OUT clock source */
#define RCU_CKOUTSRC_IRC32M             CFG0_CKOUTSEL(5)                     /*!< IRC32M is selected as CK_OUT clock source */
#define RCU_CKOUTSRC_HXTAL              CFG0_CKOUTSEL(6)                     /*!< HXTAL is selected as CK_OUT clock source */
#define RCU_CKOUTSRC_CKPLL_DIV1         (RCU_CFG0_PLLDV | CFG0_CKOUTSEL(7))  /*!< CK_PLL is selected as CK_OUT clock source */
#define RCU_CKOUTSRC_CKPLL_DIV8         CFG0_CKOUTSEL(7)                     /*!< CK_PLL/8 is selected as CK_OUT clock source */

/* CK_OUT divider */
#define CFG0_CKOUTDIV(regval)           (BITS(28,30) & ((uint32_t)(regval) << 28))
#define RCU_CKOUT_DIV1                  CFG0_CKOUTDIV(0)                     /*!< CK_OUT is divided by 1 */
#define RCU_CKOUT_DIV2                  CFG0_CKOUTDIV(1)                     /*!< CK_OUT is divided by 2 */
#define RCU_CKOUT_DIV4                  CFG0_CKOUTDIV(2)                     /*!< CK_OUT is divided by 4 */
#define RCU_CKOUT_DIV8                  CFG0_CKOUTDIV(3)                     /*!< CK_OUT is divided by 8 */
#define RCU_CKOUT_DIV16                 CFG0_CKOUTDIV(4)                     /*!< CK_OUT is divided by 16 */
#define RCU_CKOUT_DIV32                 CFG0_CKOUTDIV(5)                     /*!< CK_OUT is divided by 32 */
#define RCU_CKOUT_DIV64                 CFG0_CKOUTDIV(6)                     /*!< CK_OUT is divided by 64 */
#define RCU_CKOUT_DIV128                CFG0_CKOUTDIV(7)                     /*!< CK_OUT is divided by 128 */

/* PREDV0 division factor */
#define CFG1_PREDV(regval)              (BITS(0,2) & ((uint32_t)(regval) << 0))
#define RCU_PREDV_DIV1                  CFG1_PREDV(0)                        /*!< PREDV input clock source not divided */
#define RCU_PREDV_DIV2                  CFG1_PREDV(1)                        /*!< PREDV input clock source divided by 2 */
#define RCU_PREDV_DIV3                  CFG1_PREDV(2)                        /*!< PREDV input clock source divided by 3 */
#define RCU_PREDV_DIV4                  CFG1_PREDV(3)                        /*!< PREDV input clock source divided by 4 */
#define RCU_PREDV_DIV5                  CFG1_PREDV(4)                        /*!< PREDV input clock source divided by 5 */
#define RCU_PREDV_DIV6                  CFG1_PREDV(5)                        /*!< PREDV input clock source divided by 6 */
#define RCU_PREDV_DIV7                  CFG1_PREDV(6)                        /*!< PREDV input clock source divided by 7 */
#define RCU_PREDV_DIV8                  CFG1_PREDV(7)                        /*!< PREDV input clock source divided by 8 */

/* I2C clock source selection */
#define CFG2_I2CSRC(regval)             (BITS(8,9) & ((uint32_t)(regval) << 8))
#define RCU_CKI2CSRC_PCLK1              CFG2_I2CSRC(0)                       /*!< PCLK1 is selected as I2C clock source */
#define RCU_CKI2CSRC_PLL                CFG2_I2CSRC(1)                       /*!< PLL is selected as I2C clock source */
#define RCU_CKI2CSRC_IRC32M             CFG2_I2CSRC(2)                       /*!< IRC32M is selected as I2C clock source */
#define RCU_CKI2CSRC_HXTAL              CFG2_I2CSRC(3)                       /*!< HXTAL is selected as I2C clock source */

/* function declarations */
/* peripherals clock configure functions */
/* deinitialize the RCU */
void rcu_deinit(void);
/* enable the peripherals clock */
void rcu_periph_clock_enable(rcu_periph_enum periph);
/* disable the peripherals clock */
void rcu_periph_clock_disable(rcu_periph_enum periph);
/* reset the peripherals */
void rcu_periph_reset_enable(rcu_periph_reset_enum periph_reset);
/* disable reset the peripheral */
void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset);
/* enable the peripherals clock when in sleep mode */
void rcu_periph_clock_sleep_enable(rcu_periph_sleep_enum periph);
/* disable the peripherals clock when in sleep mode */
void rcu_periph_clock_sleep_disable(rcu_periph_sleep_enum periph);

/* system and peripherals clock source, system reset configure functions */
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
/* configure the CK_OUT clock source and divider */
void rcu_ckout_config(uint32_t ckout_src, uint32_t ckout_div);
/* configure the PLL clock source selection and PLL multiply factor */
void rcu_pll_config(uint32_t pll_src, uint32_t predv_div, uint32_t pll_mul);
/* enable RCU system reset */
void rcu_system_reset_enable(uint32_t reset_source);
/* disable RCU system reset */
void rcu_system_reset_disable(uint32_t reset_source);
/* configure the CK_ADCPRE clock source and division factor */
void rcu_adc_clock_config(uint32_t ck_adc, uint32_t adc_psc);
/* configure the I2C division factor */
void rcu_i2c_clock_source_config(uint32_t ck_i2c);

/* IRC32M, PLL and other oscillator configure functions */
/* wait for oscillator stabilization flags is SET or oscillator startup is timeout */
ErrStatus rcu_osci_stab_wait(rcu_osci_type_enum osci);
/* turn on the oscillator */
void rcu_osci_on(rcu_osci_type_enum osci);
/* turn off the oscillator */
void rcu_osci_off(rcu_osci_type_enum osci);
/* enable the oscillator bypass mode, HXTALEN must be reset before it */
void rcu_osci_bypass_mode_enable(void);
/* disable the oscillator bypass mode, HXTALEN must be reset before it */
void rcu_osci_bypass_mode_disable(void);
/* configure the HXTAL frequency scale select */
void rcu_hxtal_frequency_scale_select(uint32_t hxtal_scal);
/* set the IRC32M adjust value */
void rcu_irc32m_adjust_value_set(uint32_t irc32m_adjval);

/* clock monitor configure functions */
/* enable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_enable(void);
/* disable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_disable(void);
/* enable the PLL clock monitor */
void rcu_pll_clock_monitor_enable(void);
/* disable the PLL clock monitor */
void rcu_pll_clock_monitor_disable(void);

/* clock frequency get functions */
/* get the system clock, bus and peripheral clock frequency */
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock);

/* flag & interrupt functions */
/* get the clock stabilization and peripheral reset flags */
FlagStatus rcu_flag_get(rcu_flag_enum flag);
/* clear the reset flag */
void rcu_all_reset_flag_clear(void);
/* get the clock stabilization interrupt and ckm flags */
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag);
/* clear the interrupt flags */
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag);
/* enable the stabilization interrupt */
void rcu_interrupt_enable(rcu_int_enum interrupt);
/* disable the stabilization interrupt */
void rcu_interrupt_disable(rcu_int_enum interrupt);

#endif /* GD32M53X_RCU_H */
