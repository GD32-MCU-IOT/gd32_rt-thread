/*!
    \file    gd32f50x_syscfg.h
    \brief   definitions for the SYSCFG

    \version 2025-11-03, V1.0.0, firmware for GD32F50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#ifndef GD32F50X_SYSCFG_H
#define GD32F50X_SYSCFG_H

#include "gd32f50x.h"

/* peripheral definitions */
/* peripheral base addresses */
#define SYSCFG                     SYSCFG_BASE                                                     /*!< SYSCFG base address */

/* registers definitions */                            
#define SYSCFG_CFG0                            REG32((SYSCFG) + 0x00000000U)                       /*!< SYSCFG configuration register 0 */
#define SYSCFG_CFG1                            REG32((SYSCFG) + 0x00000004U)                       /*!< SYSCFG configuration register 1 */
#define SYSCFG_LKCTL                           REG32((SYSCFG) + 0x00000018U)                       /*!< SYSCFG lockup control register */
#define SYSCFG_BUSTO                           REG32((SYSCFG) + 0x0000001CU)                       /*!< SYSCFG bus timeout register */
#define SYSCFG_TIMERCISEL                      REG32((SYSCFG) + 0x00000020U)                       /*!< SYSCFG timer input selection register */
#define SYSCFG_FPUINTEN                        REG32((SYSCFG) + 0x00000024U)                       /*!< SYSCFG FPU interrupt enable register */
#define SYSCFG_SRAMWP                          REG32((SYSCFG) + 0x00000028U)                       /*!< SYSCFG SRAM write protection register */
#define SYSCFG_SRAMECCSTAT                     REG32((SYSCFG) + 0x0000002CU)                       /*!< SYSCFG SRAM ECC status register */
#define SYSCFG_SRAMECCCS                       REG32((SYSCFG) + 0x00000030U)                       /*!< SYSCFG SRAM ECC control and status register */
#define SYSCFG_BUSTOSTAT                       REG32((SYSCFG) + 0x00000034U)                       /*!< SYSCFG bus timeout status register */
#define SYSCFG_TIMER0TRGCFG0                   REG32((SYSCFG) + 0x00000100U)                       /*!< Timer0 TRG configuration register */
#define SYSCFG_TIMER0TRGCFG1                   REG32((SYSCFG) + 0x00000104U)                       /*!< Timer0 TRG configuration register */
#define SYSCFG_TIMER0TRGCFG2                   REG32((SYSCFG) + 0x00000108U)                       /*!< Timer0 TRG configuration register */
#define SYSCFG_TIMER1TRGCFG0                   REG32((SYSCFG) + 0x0000010CU)                       /*!< Timer1 TRG configuration register */
#define SYSCFG_TIMER1TRGCFG1                   REG32((SYSCFG) + 0x00000110U)                       /*!< Timer1 TRG configuration register */
#define SYSCFG_TIMER1TRGCFG2                   REG32((SYSCFG) + 0x00000114U)                       /*!< Timer1 TRG configuration register */
#define SYSCFG_TIMER2TRGCFG0                   REG32((SYSCFG) + 0x00000118U)                       /*!< Timer2 TRG configuration register */
#define SYSCFG_TIMER2TRGCFG1                   REG32((SYSCFG) + 0x0000011CU)                       /*!< Timer2 TRG configuration register */
#define SYSCFG_TIMER2TRGCFG2                   REG32((SYSCFG) + 0x00000120U)                       /*!< Timer2 TRG configuration register */
#define SYSCFG_TIMER3TRGCFG0                   REG32((SYSCFG) + 0x00000124U)                       /*!< Timer3 TRG configuration register */
#define SYSCFG_TIMER3TRGCFG1                   REG32((SYSCFG) + 0x00000128U)                       /*!< Timer3 TRG configuration register */
#define SYSCFG_TIMER3TRGCFG2                   REG32((SYSCFG) + 0x0000012CU)                       /*!< Timer3 TRG configuration register */
#define SYSCFG_TIMER4TRGCFG0                   REG32((SYSCFG) + 0x00000130U)                       /*!< Timer4 TRG configuration register */
#define SYSCFG_TIMER4TRGCFG1                   REG32((SYSCFG) + 0x00000134U)                       /*!< Timer4 TRG configuration register */
#define SYSCFG_TIMER4TRGCFG2                   REG32((SYSCFG) + 0x00000138U)                       /*!< Timer4 TRG configuration register */
#define SYSCFG_TIMER7TRGCFG0                   REG32((SYSCFG) + 0x0000013CU)                       /*!< Timer7 TRG configuration register */
#define SYSCFG_TIMER7TRGCFG1                   REG32((SYSCFG) + 0x00000140U)                       /*!< Timer7 TRG configuration register */
#define SYSCFG_TIMER7TRGCFG2                   REG32((SYSCFG) + 0x00000144U)                       /*!< Timer7 TRG configuration register */
#define SYSCFG_TIMER15TRGCFG0                  REG32((SYSCFG) + 0x00000148U)                       /*!< Timer15 TRG configuration register */
#define SYSCFG_TIMER15TRGCFG1                  REG32((SYSCFG) + 0x0000014CU)                       /*!< Timer15 TRG configuration register */
#define SYSCFG_TIMER15TRGCFG2                  REG32((SYSCFG) + 0x00000150U)                       /*!< Timer15 TRG configuration register */
#define SYSCFG_TIMER16TRGCFG0                  REG32((SYSCFG) + 0x00000154U)                       /*!< Timer16 TRG configuration register */
#define SYSCFG_TIMER16TRGCFG1                  REG32((SYSCFG) + 0x00000158U)                       /*!< Timer16 TRG configuration register */
#define SYSCFG_TIMER16TRGCFG2                  REG32((SYSCFG) + 0x0000015CU)                       /*!< Timer16 TRG configuration register */

/* bits definitions */

/* SYSCFG_CFG0 */
#define SYSCFG_CFG0_BOOT_MODE                  BITS(0,2)                                           /*!< boot mode */

/* SYSCFG_CFG1 */                              
#define SYSCFG_CFG1_I2C0FMP                    BIT(0)                                              /*!< I2C0 Fm+ enable */
#define SYSCFG_CFG1_I2C1FMP                    BIT(1)                                              /*!< I2C1 Fm+ enable */

/* SYSCFG_LKCTL */                              
#define SYSCFG_LKCTL_LVD_LOCK                  BIT(2)                                              /*!< low voltage detector lockup bit */
#define SYSCFG_LKCTL_CPU_LOCK                  BIT(6)                                              /*!< CPU lockup bit */
#define SYSCFG_LKCTL_SRAM_LOCK                 BIT(12)                                             /*!< SRAM ECC double error lockup bit */

/* SYSCFG_BUSTO */                              
#define SYSCFG_BUSTO_CPUCBUSTO                 BIT(0)                                              /*!< CPU Cbus timeout enable bit */
#define SYSCFG_BUSTO_CPUSBUSTO                 BIT(1)                                              /*!< CPU Sbus timeout enable bit */
#define SYSCFG_BUSTO_DMA0BUSTO                 BIT(2)                                              /*!< DMA0 bus timeout enable bit */
#define SYSCFG_BUSTO_DMA1BUSTO                 BIT(3)                                              /*!< DMA1 bus timeout enable bit */

/* SYSCFG_TIMERCISEL */                             
#define SYSCFG_TIMERCISEL_TIMER15_CI0_SEL      BITS(0,1)                                           /*!< TIMER15_CI0 input selection */
#define SYSCFG_TIMERCISEL_TIMER16_CI0_SEL      BITS(4,5)                                           /*!< TIMER16_CI0 input selection */

/* SYSCFG_FPUINTEN */                               
#define SYSCFG_FPUINTEN_IOPIE                  BIT(0)                                              /*!< invalid operation interrupt enable bit */
#define SYSCFG_FPUINTEN_DZIE                   BIT(1)                                              /*!< divide by 0 interrupt enable bit */
#define SYSCFG_FPUINTEN_UFIE                   BIT(2)                                              /*!< underflow interrupt enable bit */
#define SYSCFG_FPUINTEN_OVFIE                  BIT(3)                                              /*!< overflow interrupt enable bit */
#define SYSCFG_FPUINTEN_IAIE                   BIT(4)                                              /*!< input abnormal interrupt enable bit */
#define SYSCFG_FPUINTEN_IXIE                   BIT(5)                                              /*!< inexact interrupt enable bit */

/* SYSCFG_SRAMWP */                            
#define SYSCFG_SRAMWP_SRAM_P0WP                BIT(0)                                              /*!< SRAM page 0 write protection */
#define SYSCFG_SRAMWP_SRAM_P1WP                BIT(1)                                              /*!< SRAM page 1 write protection */
#define SYSCFG_SRAMWP_SRAM_P2WP                BIT(2)                                              /*!< SRAM page 2 write protection */
#define SYSCFG_SRAMWP_SRAM_P3WP                BIT(3)                                              /*!< SRAM page 3 write protection */
#define SYSCFG_SRAMWP_SRAM_P4WP                BIT(4)                                              /*!< SRAM page 4 write protection */
#define SYSCFG_SRAMWP_SRAM_P5WP                BIT(5)                                              /*!< SRAM page 5 write protection */
#define SYSCFG_SRAMWP_SRAM_P6WP                BIT(6)                                              /*!< SRAM page 6 write protection */
#define SYSCFG_SRAMWP_SRAM_P7WP                BIT(7)                                              /*!< SRAM page 7 write protection */
#define SYSCFG_SRAMWP_SRAM_P8WP                BIT(8)                                              /*!< SRAM page 8 write protection */
#define SYSCFG_SRAMWP_SRAM_P9WP                BIT(9)                                              /*!< SRAM page 9 write protection */
#define SYSCFG_SRAMWP_SRAM_P10WP               BIT(10)                                             /*!< SRAM page 10 write protection */
#define SYSCFG_SRAMWP_SRAM_P11WP               BIT(11)                                             /*!< SRAM page 11 write protection */
#define SYSCFG_SRAMWP_SRAM_P12WP               BIT(12)                                             /*!< SRAM page 12 write protection */
#define SYSCFG_SRAMWP_SRAM_P13WP               BIT(13)                                             /*!< SRAM page 13 write protection */
#define SYSCFG_SRAMWP_SRAM_P14WP               BIT(14)                                             /*!< SRAM page 14 write protection */
#define SYSCFG_SRAMWP_SRAM_P15WP               BIT(15)                                             /*!< SRAM page 15 write protection */
#define SYSCFG_SRAMWP_SRAM_P16WP               BIT(16)                                             /*!< SRAM page 16 write protection */
#define SYSCFG_SRAMWP_SRAM_P17WP               BIT(17)                                             /*!< SRAM page 17 write protection */
#define SYSCFG_SRAMWP_SRAM_P18WP               BIT(18)                                             /*!< SRAM page 18 write protection */
#define SYSCFG_SRAMWP_SRAM_P19WP               BIT(19)                                             /*!< SRAM page 19 write protection */
#define SYSCFG_SRAMWP_SRAM_P20WP               BIT(20)                                             /*!< SRAM page 20 write protection */
#define SYSCFG_SRAMWP_SRAM_P21WP               BIT(21)                                             /*!< SRAM page 21 write protection */
#define SYSCFG_SRAMWP_SRAM_P22WP               BIT(22)                                             /*!< SRAM page 22 write protection */
#define SYSCFG_SRAMWP_SRAM_P23WP               BIT(23)                                             /*!< SRAM page 23 write protection */
#define SYSCFG_SRAMWP_SRAM_P24WP               BIT(24)                                             /*!< SRAM page 24 write protection */
#define SYSCFG_SRAMWP_SRAM_P25WP               BIT(25)                                             /*!< SRAM page 25 write protection */
#define SYSCFG_SRAMWP_SRAM_P26WP               BIT(26)                                             /*!< SRAM page 26 write protection */
#define SYSCFG_SRAMWP_SRAM_P27WP               BIT(27)                                             /*!< SRAM page 27 write protection */
#define SYSCFG_SRAMWP_SRAM_P28WP               BIT(28)                                             /*!< SRAM page 28 write protection */
#define SYSCFG_SRAMWP_SRAM_P29WP               BIT(29)                                             /*!< SRAM page 29 write protection */
#define SYSCFG_SRAMWP_SRAM_P30WP               BIT(30)                                             /*!< SRAM page 30 write protection */
#define SYSCFG_SRAMWP_SRAM_P31WP               BIT(31)                                             /*!< SRAM page 31 write protection */

/* SYSCFG_SRAMECCSTAT */                               
#define SYSCFG_SRAMECCSTAT_SRAMECCMEIF         BIT(0)                                              /*!< SRAM non-correction event detected */
#define SYSCFG_SRAMECCSTAT_SRAMECCSEIF         BIT(1)                                              /*!< SRAM single bit correction event detected */

/* SYSCFG_SRAMECCCS */
#define SYSCFG_SRAMECCCS_SRAMECCMEIE           BIT(3)                                              /*!< SRAM multi-bit non-correction interrupt enable */
#define SYSCFG_SRAMECCCS_SRAMECCSEIE           BIT(4)                                              /*!< SRAM single bit correction interrupt enable */
#define SYSCFG_SRAMECCCS_SRAMECCSERRBITS       BITS(10,15)                                         /*!< which one bit has an SRAM ECC single-bit correctable error */
#define SYSCFG_SRAMECCCS_SRAMECCADDR           BITS(19,31)                                         /*!< faulting system address where the last ECC event on SRAM occurred */
                               
/* SYSCFG_BUSTOSTAT */                             
#define SYSCFG_BUSTOSTAT_CPUCBUSTOF            BIT(0)                                              /*!< CPU Cbus timeout flag */
#define SYSCFG_BUSTOSTAT_CPUSBUSTOF            BIT(1)                                              /*!< CPU Sbus timeout flag */
#define SYSCFG_BUSTOSTAT_DMA0BUSTOF            BIT(2)                                              /*!< DMA0 bus timeout flag */
#define SYSCFG_BUSTOSTAT_DMA1BUSTOF            BIT(3)                                              /*!< DMA1 bus timeout flag */

/* SYSCFG_TIMERxCFG */
#define SYSCFG_TIMERCFG_TSCFG0                 BITS(0,4)                                           /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG1                 BITS(5,9)                                           /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG2                 BITS(10,14)                                         /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG3                 BITS(16,20)                                         /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG4                 BITS(21,25)                                         /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG5                 BITS(26,30)                                         /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG6                 BITS(0,4)                                           /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG9                 BITS(16,20)                                         /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG10                BITS(21,25)                                         /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG11                BITS(26,30)                                         /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG12                BITS(0,4)                                           /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG13                BITS(5,9)                                           /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG14                BITS(10,14)                                         /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG15                BITS(16,20)                                         /*!< TIMER trigger selection */

/* constants definitions */
/* boot mode definitions */
#define BOOT_MODE(regval)                  (BITS(0,2) & ((uint32_t)(regval) << 0U))
#define SYSCFG_BOOTMODE_FLASH              BOOT_MODE(0)                                           /*!< boot from main flash */
#define SYSCFG_BOOTMODE_BOOTLOADER         BOOT_MODE(1)                                           /*!< boot from bootloader */
#define SYSCFG_BOOTMODE_SRAM               BOOT_MODE(3)                                           /*!< boot from embedded SRAM */
#define SYSCFG_BOOTMODE_OTP1               BOOT_MODE(5)                                           /*!< boot from embedded OTP1 */

/* I2Cx fast mode plus enable definitions */
#define SYSCFG_I2C0_FMP                    SYSCFG_CFG1_I2C0FMP                                    /*!< I2C0 fast mode plus enable */
#define SYSCFG_I2C1_FMP                    SYSCFG_CFG1_I2C1FMP                                    /*!< I2C1 fast mode plus enable */

/* lockup enable */
#define SYSCFG_CPU_LOCKUP                  SYSCFG_LKCTL_CPU_LOCK                                  /*!< CPU lockup signal is connected  */
#define SYSCFG_SRAM_LOCKUP                 SYSCFG_LKCTL_SRAM_LOCK                                 /*!< SRAM ECC double error signal is connected */
#define SYSCFG_LVD_LOCKUP                  SYSCFG_LKCTL_LVD_LOCK                                  /*!< LVD signal is connected */

/* bus timeout enable */
#define SYSCFG_CPUCBUS_TIMEROUT            SYSCFG_BUSTO_CPUCBUSTO                                 /*!< CPU Cbus timeout enable */
#define SYSCFG_CPUSBUS_TIMEROUT            SYSCFG_BUSTO_CPUSBUSTO                                 /*!< CPU Sbus timeout enable */
#define SYSCFG_DMA0BUS_TIMEROUT            SYSCFG_BUSTO_DMA0BUSTO                                 /*!< DMA0 bus timeout enable */
#define SYSCFG_DMA1BUS_TIMEROUT            SYSCFG_BUSTO_DMA1BUSTO                                 /*!< DMA1 bus timeout enable */

/* SRAM page write protection */
#define SYSCFG_SRAM_WP_PAGE0               SYSCFG_SRAMWP_SRAM_P0WP                                /*!< SRAM page 0 write protection */
#define SYSCFG_SRAM_WP_PAGE1               SYSCFG_SRAMWP_SRAM_P1WP                                /*!< SRAM page 1 write protection */
#define SYSCFG_SRAM_WP_PAGE2               SYSCFG_SRAMWP_SRAM_P2WP                                /*!< SRAM page 2 write protection */
#define SYSCFG_SRAM_WP_PAGE3               SYSCFG_SRAMWP_SRAM_P3WP                                /*!< SRAM page 3 write protection */
#define SYSCFG_SRAM_WP_PAGE4               SYSCFG_SRAMWP_SRAM_P4WP                                /*!< SRAM page 4 write protection */
#define SYSCFG_SRAM_WP_PAGE5               SYSCFG_SRAMWP_SRAM_P5WP                                /*!< SRAM page 5 write protection */
#define SYSCFG_SRAM_WP_PAGE6               SYSCFG_SRAMWP_SRAM_P6WP                                /*!< SRAM page 6 write protection */
#define SYSCFG_SRAM_WP_PAGE7               SYSCFG_SRAMWP_SRAM_P7WP                                /*!< SRAM page 7 write protection */
#define SYSCFG_SRAM_WP_PAGE8               SYSCFG_SRAMWP_SRAM_P8WP                                /*!< SRAM page 8 write protection */
#define SYSCFG_SRAM_WP_PAGE9               SYSCFG_SRAMWP_SRAM_P9WP                                /*!< SRAM page 9 write protection */
#define SYSCFG_SRAM_WP_PAGE10              SYSCFG_SRAMWP_SRAM_P10WP                               /*!< SRAM page 10 write protection */
#define SYSCFG_SRAM_WP_PAGE11              SYSCFG_SRAMWP_SRAM_P11WP                               /*!< SRAM page 11 write protection */
#define SYSCFG_SRAM_WP_PAGE12              SYSCFG_SRAMWP_SRAM_P12WP                               /*!< SRAM page 12 write protection */
#define SYSCFG_SRAM_WP_PAGE13              SYSCFG_SRAMWP_SRAM_P13WP                               /*!< SRAM page 13 write protection */
#define SYSCFG_SRAM_WP_PAGE14              SYSCFG_SRAMWP_SRAM_P14WP                               /*!< SRAM page 14 write protection */
#define SYSCFG_SRAM_WP_PAGE15              SYSCFG_SRAMWP_SRAM_P15WP                               /*!< SRAM page 15 write protection */
#define SYSCFG_SRAM_WP_PAGE16              SYSCFG_SRAMWP_SRAM_P16WP                               /*!< SRAM page 16 write protection */
#define SYSCFG_SRAM_WP_PAGE17              SYSCFG_SRAMWP_SRAM_P17WP                               /*!< SRAM page 17 write protection */
#define SYSCFG_SRAM_WP_PAGE18              SYSCFG_SRAMWP_SRAM_P18WP                               /*!< SRAM page 18 write protection */
#define SYSCFG_SRAM_WP_PAGE19              SYSCFG_SRAMWP_SRAM_P19WP                               /*!< SRAM page 19 write protection */
#define SYSCFG_SRAM_WP_PAGE20              SYSCFG_SRAMWP_SRAM_P20WP                               /*!< SRAM page 20 write protection */
#define SYSCFG_SRAM_WP_PAGE21              SYSCFG_SRAMWP_SRAM_P21WP                               /*!< SRAM page 21 write protection */
#define SYSCFG_SRAM_WP_PAGE22              SYSCFG_SRAMWP_SRAM_P22WP                               /*!< SRAM page 22 write protection */
#define SYSCFG_SRAM_WP_PAGE23              SYSCFG_SRAMWP_SRAM_P23WP                               /*!< SRAM page 23 write protection */
#define SYSCFG_SRAM_WP_PAGE24              SYSCFG_SRAMWP_SRAM_P24WP                               /*!< SRAM page 24 write protection */
#define SYSCFG_SRAM_WP_PAGE25              SYSCFG_SRAMWP_SRAM_P25WP                               /*!< SRAM page 25 write protection */
#define SYSCFG_SRAM_WP_PAGE26              SYSCFG_SRAMWP_SRAM_P26WP                               /*!< SRAM page 26 write protection */
#define SYSCFG_SRAM_WP_PAGE27              SYSCFG_SRAMWP_SRAM_P27WP                               /*!< SRAM page 27 write protection */
#define SYSCFG_SRAM_WP_PAGE28              SYSCFG_SRAMWP_SRAM_P28WP                               /*!< SRAM page 28 write protection */
#define SYSCFG_SRAM_WP_PAGE29              SYSCFG_SRAMWP_SRAM_P29WP                               /*!< SRAM page 29 write protection */
#define SYSCFG_SRAM_WP_PAGE30              SYSCFG_SRAMWP_SRAM_P30WP                               /*!< SRAM page 30 write protection */
#define SYSCFG_SRAM_WP_PAGE31              SYSCFG_SRAMWP_SRAM_P31WP                               /*!< SRAM page 31 write protection */

/* FPU interrupt enable */
#define SYSCFG_FPUINT_INVALID_OPERATION    SYSCFG_FPUINTEN_IOPIE                                  /*!< invalid operation interrupt enable */
#define SYSCFG_FPUINT_DIV0                 SYSCFG_FPUINTEN_DZIE                                   /*!< divide-by-zero interrupt enable */
#define SYSCFG_FPUINT_UNDERFLOW            SYSCFG_FPUINTEN_UFIE                                   /*!< underflow interrupt enable */
#define SYSCFG_FPUINT_OVERFLOW             SYSCFG_FPUINTEN_OVFIE                                  /*!< overflow interrupt enable */
#define SYSCFG_FPUINT_INPUT_ABNORMAL       SYSCFG_FPUINTEN_IAIE                                   /*!< input abnormal interrupt enable */
#define SYSCFG_FPUINT_INEXACT              SYSCFG_FPUINTEN_IXIE                                   /*!< inexact interrupt enable */

/* TIMER15_CI0 input selection */
#define TIMER15_CI0_SEL(regval)          (BITS(0,1) & ((uint32_t)(regval) << 0U))
#define TIMER16_CI0_SEL(regval)          (BITS(4,5) & ((uint32_t)(regval) << 4U))

/* TIMER channel input select mask definitions */
#define SYSCFG_TIMERCISEL_TIMER15_CI0_SEL   BITS(0,1)                                               /*!< TIMER15 CI0 input selection mask */
#define SYSCFG_TIMERCISEL_TIMER16_CI0_SEL   BITS(4,5)                                               /*!< TIMER16 CI0 input selection mask */

/* Define the TIMER bit position and selection value encoding */
#define TIMER_CHANNEL_BIT(timer_id, bitpos, value)   (((uint32_t)(timer_id) << 8U) | ((uint32_t)(bitpos) << 4U) | ((uint32_t)(value)))
#define TIMER_GET_ID(val)                   (((uint32_t)(val) & 0x0F00U) >> 8U)                     /*!< Extract timer ID */
#define TIMER_GET_BITPOS(val)               (((uint32_t)(val) & 0x00F0U) >> 4U)                     /*!< Extract bit position */
#define TIMER_GET_VALUE(val)                ((uint32_t)(val) & 0x000FU)                             /*!< Extract selection value */

/* Timer ID definitions */
#define TIMER15_ID                          0x01U                                                   /*!< TIMER15 identifier */
#define TIMER16_ID                          0x02U                                                   /*!< TIMER16 identifier */

/* TIMERx channel input select definitions */
typedef enum {
    /* TIMER15 CI0 input selections */
    TIMER15_CI0_INPUT_TIMER15_CH0       = TIMER_CHANNEL_BIT(TIMER15_ID, 0U, 0U),                   /*!< Select TIMER15_CH0 as TIMER15 CI0 */
    TIMER15_CI0_INPUT_IRC40K            = TIMER_CHANNEL_BIT(TIMER15_ID, 0U, 1U),                   /*!< Select IRC40K as TIMER15 CI0 */
    TIMER15_CI0_INPUT_LXTAL             = TIMER_CHANNEL_BIT(TIMER15_ID, 0U, 2U),                   /*!< Select LXTAL as TIMER15 CI0 */

    /* TIMER16 CI0 input selections */
    TIMER16_CI0_INPUT_TIMER16_CH0       = TIMER_CHANNEL_BIT(TIMER16_ID, 4U, 0U),                   /*!< Select TIMER16_CH0 as TIMER16 CI0 */
    TIMER16_CI0_INPUT_CKOUT             = TIMER_CHANNEL_BIT(TIMER16_ID, 4U, 3U)                    /*!< Select CKOUT as TIMER16 CI0 */
} timer_channel_input_enum;

/* timer tigger source select definition */                             
#define TIMER_SMCFG_TRGSEL_NONE             ((uint8_t)0x00U)                                       /*!< trigger input is none */
#define TIMER_SMCFG_TRGSEL_ITI0             ((uint8_t)0x01U)                                       /*!< internal trigger input 0 */
#define TIMER_SMCFG_TRGSEL_ITI1             ((uint8_t)0x02U)                                       /*!< internal trigger input 1 */
#define TIMER_SMCFG_TRGSEL_ITI2             ((uint8_t)0x03U)                                       /*!< internal trigger input 2 */
#define TIMER_SMCFG_TRGSEL_ITI3             ((uint8_t)0x04U)                                       /*!< internal trigger input 3 */
#define TIMER_SMCFG_TRGSEL_CI0F_ED          ((uint8_t)0x05U)                                       /*!< TI0 edge detector */
#define TIMER_SMCFG_TRGSEL_CI0FE0           ((uint8_t)0x06U)                                       /*!< filtered TIMER input 0 */
#define TIMER_SMCFG_TRGSEL_CI1FE1           ((uint8_t)0x07U)                                       /*!< filtered TIMER input 1 */
#define TIMER_SMCFG_TRGSEL_ETIFP            ((uint8_t)0x08U)                                       /*!< external trigger */
#define TIMER_SMCFG_TRGSEL_CI2FE2           ((uint8_t)0x09U)                                       /*!< filtered TIMER input 2 */
#define TIMER_SMCFG_TRGSEL_CI3FE3           ((uint8_t)0x0AU)                                       /*!< filtered TIMER input 3 */
#define TIMER_SMCFG_TRGSEL_MCI0FEM0         ((uint8_t)0x0BU)                                       /*!< filtered output of multi mode channel 0 input */
#define TIMER_SMCFG_TRGSEL_ITI14            ((uint8_t)0x13U)                                       /*!< internal trigger input 14 */
                                
/* timer tigger mode select definition */                               
#define TIMER_QUAD_DECODER_MODE0            ((uint8_t)0x00U)                                       /*!< quadrature decoder mode 0 */
#define TIMER_QUAD_DECODER_MODE1            ((uint8_t)0x01U)                                       /*!< quadrature decoder mode 1 */
#define TIMER_QUAD_DECODER_MODE2            ((uint8_t)0x02U)                                       /*!< quadrature decoder mode 2 */
#define TIMER_SLAVE_MODE_RESTART            ((uint8_t)0x03U)                                       /*!< restart mode */
#define TIMER_SLAVE_MODE_PAUSE              ((uint8_t)0x04U)                                       /*!< pause mode */
#define TIMER_SLAVE_MODE_EVENT              ((uint8_t)0x05U)                                       /*!< event mode */
#define TIMER_SLAVE_MODE_EXTERNAL0          ((uint8_t)0x06U)                                       /*!< external clock mode 0 */
#define TIMER_DECODER_MODE0                 ((uint8_t)0x09U)                                       /*!< decoder mode 0 */
#define TIMER_DECODER_MODE1                 ((uint8_t)0x0AU)                                       /*!< decoder mode 1 */
#define TIMER_DECODER_MODE2                 ((uint8_t)0x0BU)                                       /*!< decoder mode 2 */
#define TIMER_DECODER_MODE3                 ((uint8_t)0x0CU)                                       /*!< decoder mode 3 */
#define TIMER_QUAD_DECODER_MODE3            ((uint8_t)0x0DU)                                       /*!< quadrature decoder mode 3 */
#define TIMER_QUAD_DECODER_MODE4            ((uint8_t)0x0EU)                                       /*!< quadrature decoder mode 4 */
#define TIMER_SLAVE_MODE_DISABLE            ((uint8_t)0x0FU)                                       /*!< slave mode disable */

#define SYSCFG_TIMERCFG0(syscfg_timerx)     REG32(SYSCFG + 0x100U + (syscfg_timerx) * 0x0CU)       /*!< TIMERx configuration register */
#define SYSCFG_TIMERCFG1(syscfg_timerx)     REG32(SYSCFG + 0x104U + (syscfg_timerx) * 0x0CU)       /*!< TIMERx configuration register */
#define SYSCFG_TIMERCFG2(syscfg_timerx)     REG32(SYSCFG + 0x108U + (syscfg_timerx) * 0x0CU)       /*!< TIMERx configuration register */

#define SYSCFG_TIMERCFG(syscfg_timerx)      ((uint32_t)(SYSCFG_BASE + 0x100U + (syscfg_timerx) * 0x0CU))

#define SYSCFG_TIMER0                       ((uint8_t)0x00U)                                       /*!< SYSCFG TIMER0 */
#define SYSCFG_TIMER1                       ((uint8_t)0x01U)                                       /*!< SYSCFG TIMER1 */
#define SYSCFG_TIMER2                       ((uint8_t)0x02U)                                       /*!< SYSCFG TIMER2 */
#define SYSCFG_TIMER3                       ((uint8_t)0x03U)                                       /*!< SYSCFG TIMER3 */
#define SYSCFG_TIMER4                       ((uint8_t)0x04U)                                       /*!< SYSCFG TIMER4 */
#define SYSCFG_TIMER7                       ((uint8_t)0x05U)                                       /*!< SYSCFG TIMER5 */
#define SYSCFG_TIMER15                      ((uint8_t)0x06U)                                       /*!< SYSCFG TIMER6 */
#define SYSCFG_TIMER16                      ((uint8_t)0x07U)                                       /*!< SYSCFG TIMER7 */

/* function declarations */
/* initialization functions */
/* reset SYSCFG register values */
void syscfg_deinit(void);

/* SYSCFG configuration functions */
/* get boot mode */
uint32_t syscfg_bootmode_get(void);
/* enable I2Cx Fast Mode Plus */
void syscfg_i2c_fast_mode_plus_enable(uint32_t i2c_fmp);
/* disable I2Cx Fast Mode Plus */
void syscfg_i2c_fast_mode_plus_disable(uint32_t i2c_fmp);

/* lockup configuration functions */
/* enable module lockup function (function can be disabled by system reset) */
void syscfg_lockup_enable(uint32_t lockup);

/* bus timeout configuration functions */
/* enable bus timeout */
void syscfg_bus_timeout_enable(uint32_t busto);
/* disable bus timeout */
void syscfg_bus_timeout_disable(uint32_t busto);

/* timer input configuration functions */
/* Select TIMER channel input source */
void syscfg_timer_input_source_select(timer_channel_input_enum timer_input);

/* SRAM configuration functions */
/* enable SRAM page write protection */
void syscfg_sram_page_wp_enable(uint32_t page);

/* SRAM ECC error information functions */
/* get SRAM ECC single-bit error bit position */
uint32_t syscfg_sram_ecc_error_bit_get(void);
/* get SRAM ECC error address */
uint32_t syscfg_sram_ecc_error_addr_get(void);

/* FPU interrupt configuration functions */
/* enable FPU interrupt */
void syscfg_fpu_interrupt_enable(uint32_t interrupt);
/* disable FPU interrupt */
void syscfg_fpu_interrupt_disable(uint32_t interrupt);

/* SRAM ECC interrupt configuration functions */
/* enable SRAM ECC error interrupt */
void syscfg_sram_ecc_interrupt_enable(uint32_t sram_ecc);
/* disable SRAM ECC error interrupt */
void syscfg_sram_ecc_interrupt_disable(uint32_t sram_ecc);
/* get bus timeout flag */
FlagStatus syscfg_bus_timeout_flag_get(uint32_t bustoflag);
/* clear bus timeout flag */
void syscfg_bus_timeout_flag_clear(uint32_t bustoflag);
/* get SRAM ECC error flag */
FlagStatus syscfg_sram_ecc_flag_get(uint32_t ecc_flag);
/* clear SRAM ECC error flag */
void syscfg_sram_ecc_flag_clear(uint32_t ecc_flag);

#endif /* GD32F50X_SYSCFG_H */
