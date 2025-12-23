/*!
    \file    gd32g5x3.h
    \brief   general definitions for GD32G5x3

    \version 2025-02-10, V1.1.0, firmware for GD32G5x3
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

#ifndef GD32G5X3_H
#define GD32G5X3_H

#ifdef __cplusplus
 extern "C" {
#endif 

#if !defined (GD32G5X3)
  #define GD32G5X3
#endif /* define GD32G5X3 */
/* define GD32G5X3 */
#if !defined (GD32G5X3)
 #error "Please select the target GD32G5x3 device used in your application (in gd32g5x3.h file)"
#endif /* undefine GD32G5X3 tip */

/* define value of high speed crystal oscillator (HXTAL) in Hz */
#if !defined  HXTAL_VALUE
#define HXTAL_VALUE    ((uint32_t)8000000) /* !< from 4M to 32M *!< value of the external oscillator in Hz*/
#endif /* high speed crystal oscillator value */

/* define startup timeout value of high speed crystal oscillator (HXTAL) */
#if !defined  (HXTAL_STARTUP_TIMEOUT)
#define HXTAL_STARTUP_TIMEOUT   ((uint16_t)0x0FFFF)
#endif /* high speed crystal oscillator startup timeout */

/* define value of internal 8MHz RC oscillator (IRC8M) in Hz */
#if !defined  (IRC8M_VALUE) 
#define IRC8M_VALUE  ((uint32_t)8000000)
#endif /* internal 8MHz RC oscillator value */

/* define startup timeout value of internal 8MHz RC oscillator (IRC8M) */
#if !defined  (IRC8M_STARTUP_TIMEOUT)
#define IRC8M_STARTUP_TIMEOUT   ((uint16_t)0x0500)
#endif /* internal 8MHz RC oscillator startup timeout */

/* define value of internal 32KHz RC oscillator(IRC32K) in Hz */
#if !defined  (IRC32K_VALUE) 
#define IRC32K_VALUE  ((uint32_t)32000)
#endif /* internal 32KHz RC oscillator value */

/* define value of low speed crystal oscillator (LXTAL)in Hz */
#if !defined  (LXTAL_VALUE) 
#define LXTAL_VALUE  ((uint32_t)32768)
#endif /* low speed crystal oscillator value */

/* GD32G5x3 firmware library version number */
#define __GD32G5X3_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __GD32G5X3_STDPERIPH_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version */
#define __GD32G5X3_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __GD32G5X3_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]   release candidate */ 
#define __GD32G5X3_STDPERIPH_VERSION        ((__GD32G5X3_STDPERIPH_VERSION_MAIN << 24)\
                                            |(__GD32G5X3_STDPERIPH_VERSION_SUB1 << 16)\
                                            |(__GD32G5X3_STDPERIPH_VERSION_SUB2 << 8)\
                                            |(__GD32G5X3_STDPERIPH_VERSION_RC))

/* configuration of the Cortex-M33 processor and core peripherals */
#define __CM33_REV                0x0003U   /*!< Core revision r0p3 */
#define __SAUREGION_PRESENT       0U        /*!< SAU regions are not present */
#define __MPU_PRESENT             1U        /*!< MPU is present */
#define __VTOR_PRESENT            1U        /*!< VTOR is present */
#define __NVIC_PRIO_BITS          4U        /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1         /*!< FPU present */
#define __DSP_PRESENT             1         /*!< DSP present */

/* define interrupt number */
typedef enum IRQn
{
    /* Cortex-M33 processor exceptions numbers */
    NonMaskableInt_IRQn          = -14,    /*!< non mask-able interrupt                                                                 */
    HardFault_IRQn               = -13,    /*!< hard-fault interrupt                                                                    */
    MemoryManagement_IRQn        = -12,    /*!< 4 Cortex-M33 memory management interrupt                                                */
    BusFault_IRQn                = -11,    /*!< 5 Cortex-M33 bus fault interrupt                                                        */
    UsageFault_IRQn              = -10,    /*!< 6 Cortex-M33 usage fault interrupt                                                      */
    SVCall_IRQn                  = -5,     /*!< 11 Cortex-M33 sv call interrupt                                                         */
    DebugMonitor_IRQn            = -4,     /*!< 12 Cortex-M33 debug monitor interrupt                                                   */
    PendSV_IRQn                  = -2,     /*!< 14 Cortex-M33 pend sv interrupt                                                         */
    SysTick_IRQn                 = -1,     /*!< 15 Cortex-M33 system tick interrupt                                                     */
    /* interrupt numbers */
    WWDGT_IRQn                   = 0,      /*!< window watchDog timer interrupt                                                         */
    LVD_VAVD_VOVD_VUVD_IRQn      = 1,      /*!< LVD / VAVD / VOVD / VUVD through EXTI line detect interrupt                                */
    TAMPER_IRQn                  = 2,      /*!< tamper through EXTI line detect                                                         */
    RTC_IRQn                     = 3,      /*!< RTC through EXTI line interrupt                                                         */
    FMC_IRQn                     = 4,      /*!< FMC interrupt                                                                           */
    RCU_IRQn                     = 5,      /*!< RCU interrupt                                                                   */
    EXTI0_IRQn                   = 6,      /*!< EXTI line 0 interrupt                                                                   */
    EXTI1_IRQn                   = 7,      /*!< EXTI line 1 interrupt                                                                   */
    EXTI2_IRQn                   = 8,      /*!< EXTI line 2 interrupt                                                                   */
    EXTI3_IRQn                   = 9,      /*!< EXTI line 3 interrupt                                                                   */
    EXTI4_IRQn                   = 10,     /*!< EXTI line 4 interrupt                                                                   */
    DMA0_Channel0_IRQn           = 11,     /*!< DMA0 channel0 interrupt                                                                 */
    DMA0_Channel1_IRQn           = 12,     /*!< DMA0 channel1 interrupt                                                                 */
    DMA0_Channel2_IRQn           = 13,     /*!< DMA0 channel2 interrupt                                                                 */
    DMA0_Channel3_IRQn           = 14,     /*!< DMA0 channel3 interrupt                                                                 */
    DMA0_Channel4_IRQn           = 15,     /*!< DMA0 channel4 interrupt                                                                 */
    DMA0_Channel5_IRQn           = 16,     /*!< DMA0 channel5 interrupt                                                                 */
    DMA0_Channel6_IRQn           = 17,     /*!< DMA0 channel6 interrupt                                                                 */
    ADC0_1_IRQn                  = 18,     /*!< ADC0 and ADC1 interrupt                                                                 */
    EXTI5_9_IRQn                 = 23,     /*!< EXTI[9:5] interrupts                                                                    */
    TIMER0_BRK_IRQn              = 24,     /*!< TIMER0 break interrupt                                                                  */
    TIMER0_UP_IRQn               = 25,     /*!< TIMER0 update interrupt                                                                 */
    TIMER0_TRG_CMT_IDX_IRQn      = 26,     /*!< TIMER0 trigger and commutation interrupt/TIMER0 direction change interrupt/TIMER0 index */
    TIMER0_Channel_IRQn          = 27,     /*!< TIMER0 channel capture compare interrupt                                                */
    TIMER1_IRQn                  = 28,     /*!< TIMER1 interrupt                                                                        */
    TIMER2_IRQn                  = 29,     /*!< TIMER2 interrupt                                                                        */
    TIMER3_IRQn                  = 30,     /*!< TIMER3 interrupt                                                                        */
    I2C0_EV_WKUP_IRQn            = 31,     /*!< I2C0 event and wakeup interrupt                                                         */
    I2C0_ER_IRQn                 = 32,     /*!< I2C0 error interrupt                                                                    */
    I2C1_EV_WKUP_IRQn            = 33,     /*!< I2C1 event and wakeup interrupt                                                         */
    I2C1_ER_IRQn                 = 34,     /*!< I2C1 error interrupt                                                                    */
    SPI0_IRQn                    = 35,     /*!< SPI0 interrupt                                                                          */
    SPI1_IRQn                    = 36,     /*!< SPI1 interrupt                                                                          */
    USART0_IRQn                  = 37,     /*!< USART0 interrupt                                                                        */
    USART1_IRQn                  = 38,     /*!< USART1 interrupt                                                                        */
    USART2_IRQn                  = 39,     /*!< USART2 interrupt                                                                        */
    EXTI10_15_IRQn               = 40,     /*!< EXTI[15:10] interrupts                                                                  */
    RTC_Alarm_IRQn               = 41,     /*!< RTC alarm interrupt                                                                     */
    TIMER7_BRK_TRS_IDX_IRQn      = 43,     /*!< TIMER7 break interrupt/ transition error/ index error interrupt                         */
    TIMER7_UP_IRQn               = 44,     /*!< TIMER7 update interrupt                                                                 */
    TIMER7_TRG_CMT_IDX_IRQn      = 45,     /*!< TIMER7 trigger and commutation interrupt/direction change interrupt/index               */
    TIMER7_Channel_IRQn          = 46,     /*!< TIMER7 channel capture compare interrupt                                                */
    ADC2_IRQn                    = 47,     /*!< ADC2 global interrupt                                                                   */
    SYSCFG_IRQn                  = 48,     /*!< SYSCFG global interrupt                                                                 */
    LPTIMER_IRQn                 = 49,     /*!< LPTIMER global interrupt                                                                */
    TIMER4_IRQn                  = 50,     /*!< TIMER4 global interrupt                                                                 */
    SPI2_IRQn                    = 51,     /*!< SPI2 global interrupt                                                                   */
    UART3_IRQn                   = 52,     /*!< UART3 global interrupt                                                                  */
    UART4_IRQn                   = 53,     /*!< UART4 global interrupt                                                                  */
    TIMER5_DAC0_2_IRQn           = 54,     /*!< TIMER5 or DAC0 DAC2 global interrupt                                                    */
    TIMER6_DAC1_3_IRQn           = 55,     /*!< TIMER6 or DAC1 DAC3 global interrupt                                                    */
    DMA1_Channel0_IRQn           = 56,     /*!< DMA1 channel0 global interrupt                                                          */
    DMA1_Channel1_IRQn           = 57,     /*!< DMA1 channel1 global interrupt                                                          */
    DMA1_Channel2_IRQn           = 58,     /*!< DMA1 channel2 global interrupt                                                          */
    DMA1_Channel3_IRQn           = 59,     /*!< DMA1 channel3 global interrupt                                                          */
    DMA1_Channel4_IRQn           = 60,     /*!< DMA1 channel4 global interrupt                                                          */
    ADC3_IRQn                    = 61,     /*!< ADC3 global Interrupt                                                                   */
    VUVD1_VOVD1_IRQn             = 63,     /*!< VUVD1, VOVD1 global interrupt                                                           */
    CMP0_3_IRQn                  = 64,     /*!< CMP0, CMP1 and CMP2 and CMP3 global interrupt                                           */
    CMP4_7_IRQn                  = 65,     /*!< CMP4, CMP5 and CMP6 and CMP7 global interrupt                                           */
    CMP_IRQn                     = 66,     /*!< CMP global interrupt                                                                    */
    HRTIMER_IRQ0_IRQn            = 67,     /*!< HRTIMER_IRQ0 interrupt                                                                  */
    HRTIMER_IRQ1_IRQn            = 68,     /*!< HRTIMER_IRQ1 interrupt                                                                  */
    HRTIMER_IRQ2_IRQn            = 69,     /*!< HRTIMER_IRQ2 interrupt                                                                  */
    HRTIMER_IRQ3_IRQn            = 70,     /*!< HRTIMER_IRQ3 interrupt                                                                  */
    HRTIMER_IRQ4_IRQn            = 71,     /*!< HRTIMER_IRQ4 interrupt                                                                  */
    HRTIMER_IRQ5_IRQn            = 72,     /*!< HRTIMER_IRQ5 interrupt                                                                  */
    HRTIMER_IRQ6_IRQn            = 73,     /*!< HRTIMER_IRQ6 interrupt                                                                  */
    HRTIMER_IRQ7_IRQn            = 74,     /*!< HRTIMER_IRQ7 interrupt                                                                  */
    HRTIMER_IRQ8_IRQn            = 75,     /*!< HRTIMER_IRQ8 interrupt                                                                  */
    HRTIMER_IRQ9_IRQn            = 76,     /*!< HRTIMER_IRQ9 interrupt                                                                  */
    TIMER19_BRK_TRS_IDX_IRQn     = 77,     /*!< TIMER19 break / transition error / index error interrupt                                */
    TIMER19_UP_IRQn              = 78,     /*!< TIMER19 update interrupt                                                                */
    TIMER19_TRG_CMT_IDX_IRQn     = 79,     /*!< TIMER19 trigger and commutation interrupt                                               */
    TIMER19_Channel_IRQn         = 80,     /*!< TIMER19 channel capture compare interrupt                                               */
    FPU_IRQn                     = 81,     /*!< FPU global interrupt                                                                    */
    I2C2_EV_WKUP_IRQn            = 82,     /*!< I2C2 EV and wakeup interrupt                                                            */
    I2C2_ER_IRQn                 = 83,     /*!< I2C2 ER interrupt                                                                       */
    CAU_IRQn                     = 85,     /*!< CAU global interrupt                                                                    */
    TRNG_IRQn                    = 90,     /*!< TRNG global interrupt                                                                   */
    I2C3_EV_WKUP_IRQn            = 92,     /*!< I2C3 EV and wakeup interrupt                                                            */
    I2C3_ER_IRQn                 = 93,     /*!< I2C3 ER interrupt                                                                       */
    DMAMUX_OVR_IRQn              = 94,     /*!< DMAMUX overrun interrupt                                                                */
    QSPI_IRQn                    = 95,     /*!< QSPI interrupt                                                                          */
    FFT_IRQn                     = 96,     /*!< FFT interrupt                                                                           */
    DMA1_Channel5_IRQn           = 97,     /*!< DMA1 channel5 global interrupt                                                          */
    DMA1_Channel6_IRQn           = 98,     /*!< DMA1 channel6 global interrupt                                                          */
    CLA_IRQn                     = 99,     /*!< CLA interrupt                                                                           */
    TMU_IRQn                     = 100,    /*!< TMU interrupt                                                                           */
    FAC_IRQn                     = 101,    /*!< FAC interrupt                                                                           */
    HPDF0_IRQn                   = 102,    /*!< HPDF filiter 0 interrupt                                                                */
    HPDF1_IRQn                   = 103,    /*!< HPDF filiter 1 interrupt                                                                */
    HPDF2_IRQn                   = 104,    /*!< HPDF filiter 2 interrupt                                                                */
    HPDF3_IRQn                   = 105,    /*!< HPDF filiter 3 interrupt                                                                */
    TIMER14_IRQn                 = 106,    /*!< TIMER14 global interrupt                                                                */
    TIMER15_IRQn                 = 107,    /*!< TIMER15 global interrupt                                                                */
    TIMER16_IRQn                 = 108,    /*!< TIMER16 global interrupt                                                                */
    CAN0_WKUP_IRQn               = 109,    /*!< CAN 0 wakeup through EXTI line interrupt                                                */
    CAN0_Message_IRQn            = 110,    /*!< CAN 0 message buffer interrupt                                                          */
    CAN0_Busoff_IRQn             = 111,    /*!< CAN 0 bus off / bus off done interrupt                                                  */
    CAN0_Error_IRQn              = 112,    /*!< CAN 0 error interrupt                                                                   */
    CAN0_FastError_IRQn          = 113,    /*!< CAN 0 error in fast transmission interrupt                                              */
    CAN0_TEC_IRQn                = 114,    /*!< CAN 0 transmit warning interrupt                                                        */
    CAN0_REC_IRQn                = 115,    /*!< CAN 0 receive warning interrupt                                                         */
    CAN1_WKUP_IRQn               = 116,    /*!< CAN 1 wakeup through EXTI line interrupt                                                */
    CAN1_Message_IRQn            = 117,    /*!< CAN 1 message buffer interrupt                                                          */
    CAN1_Busoff_IRQn             = 118,    /*!< CAN 1 bus off / bus off done interrupt                                                  */
    CAN1_Error_IRQn              = 119,    /*!< CAN 1 error interrupt                                                                   */
    CAN1_FastError_IRQn          = 120,    /*!< CAN 1 error in fast transmission interrupt                                              */
    CAN1_TEC_IRQn                = 121,    /*!< CAN 1 transmit warning interrupt                                                        */
    CAN1_REC_IRQn                = 122,    /*!< CAN 1 receive warning interrupt                                                         */
    CAN2_WKUP_IRQn               = 123,    /*!< CAN 2 wakeup through EXTI line interrupt                                                */
    CAN2_Message_IRQn            = 124,    /*!< CAN 2 message buffer interrupt                                                          */
    CAN2_Busoff_IRQn             = 125,    /*!< CAN 2 bus off / bus off done interrupt                                                  */
    CAN2_Error_IRQn              = 126,    /*!< CAN 2 error interrupt                                                                   */
    CAN2_FastError_IRQn          = 127,    /*!< CAN 2 error in fast transmission interrupt                                              */
    CAN2_TEC_IRQn                = 128,    /*!< CAN 2 transmit warning interrupt                                                        */
    CAN2_REC_IRQn                = 129,    /*!< CAN 2 receive warning interrupt                                                         */
    TIMER0_DEC_IRQn              = 130,    /*!< TIMER0 DEC interrupt                                                                    */
    TIMER1_DEC_IRQn              = 131,    /*!< TIMER1 DEC interrupt                                                                    */
    TIMER2_DEC_IRQn              = 132,    /*!< TIMER2 DEC interrupt                                                                    */
    TIMER3_DEC_IRQn              = 133,    /*!< TIMER3 DEC interrupt                                                                    */
    TIMER4_DEC_IRQn              = 134,    /*!< TIMER4 DEC interrupt                                                                    */
    TIMER7_DEC_IRQn              = 135,    /*!< TIMER7 DEC interrupt                                                                    */
    TIMER19_DEC_IRQn             = 136     /*!< TIMER19 DEC interrupt                                                                   */
} IRQn_Type;

/* includes */
#include "core_cm33.h"
#include "system_gd32g5x3.h"
#include <stdint.h>

/* enum definitions */
typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;

/* bit operations */
#define REG64(addr)                  (*(volatile uint64_t *)(uint32_t)(addr))
#define REG32(addr)                  (*(volatile uint32_t *)(uint32_t)(addr))
#define REG16(addr)                  (*(volatile uint16_t *)(uint32_t)(addr))
#define REG8(addr)                   (*(volatile uint8_t *)(uint32_t)(addr))
#define BIT(x)                       ((uint32_t)((uint32_t)0x01U<<(x)))
#define BITS(start, end)             ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end)))) 
#define GET_BITS(regval, start, end) (((regval) & BITS((start),(end))) >> (start))

/* main flash and SRAM memory map */
#define FLASH_BASE            ((uint32_t)0x08000000U)       /*!< main FLASH base address */
#define SRAM_BASE             ((uint32_t)0x20000000U)       /*!< SRAM base address */

/* peripheral memory map */
#define APB1_BUS_BASE         ((uint32_t)0x40000000U)       /*!< apb1 base address */
#define APB2_BUS_BASE         ((uint32_t)0x40010000U)       /*!< apb2 base address */
#define APB3_BUS_BASE         ((uint32_t)0x50000000U)       /*!< apb3 base address */
#define AHB1_BUS_BASE         ((uint32_t)0x40020000U)       /*!< ahb1 base address */
#define AHB2_BUS_BASE         ((uint32_t)0x48000000U)       /*!< ahb2 base address */
#define AHB3_BUS_BASE         ((uint32_t)0x60000000U)       /*!< ahb3 base address */

/* advanced peripheral bus 1 memory map */
#define TIMER_BASE            (APB1_BUS_BASE + 0x00000000U) /*!< TIMER base address */
#define RTC_BASE              (APB1_BUS_BASE + 0x00002800U) /*!< RTC base address */
#define WWDGT_BASE            (APB1_BUS_BASE + 0x00002C00U) /*!< WWDGT base address */
#define FWDGT_BASE            (APB1_BUS_BASE + 0x00003000U) /*!< FWDGT base address */
#define SPI_BASE              (APB1_BUS_BASE + 0x00003800U) /*!< SPI base address */
#define USART_BASE            (APB1_BUS_BASE + 0x00004400U) /*!< USART base address */
#define I2C_BASE              (APB1_BUS_BASE + 0x00005400U) /*!< I2C base address */
#define PMU_BASE              (APB1_BUS_BASE + 0x00007000U) /*!< PMU base address */
#define LPTIMER_BASE          (APB1_BUS_BASE + 0x00009400U) /*!< LPTIMER base address */


/* advanced peripheral bus 2 memory map */
#define SYSCFG_BASE           (APB2_BUS_BASE + 0x00000000U) /*!< SYSCFG base address */
#define EXTI_BASE             (APB2_BUS_BASE + 0x00000400U) /*!< EXTI base address */
#define HRTIMER_BASE          (APB2_BUS_BASE + 0x00005800U) /*!< HRTIMER base address */
#define HPDF_BASE             (APB2_BUS_BASE + 0x00007000U) /*!< HPDF base address */
#define VREF_BASE             (APB2_BUS_BASE + 0x00007800U) /*!< VREF base address */
#define CMP_BASE              (APB2_BUS_BASE + 0x00007C00U) /*!< CMP base address */
#define TRIGSEL_BASE          (APB2_BUS_BASE + 0x00008400U) /*!< TRIGSEL base address */
#define CAN_BASE              (APB2_BUS_BASE + 0x0000A000U) /*!< CAN base address */

/* advanced high performance bus 1 memory map */
#define DMA_BASE              (AHB1_BUS_BASE + 0x00000000U) /*!< DMA base address */
#define DMAMUX_BASE           (AHB1_BUS_BASE + 0x00000800U) /*!< DMAMUX base address */
#define RCU_BASE              (AHB1_BUS_BASE + 0x00001000U) /*!< RCU base address */
#define FMC_BASE              (AHB1_BUS_BASE + 0x00002000U) /*!< FMC base address */
#define CRC_BASE              (AHB1_BUS_BASE + 0x00003000U) /*!< CRC base address */
#define FFT_BASE              (AHB1_BUS_BASE + 0x00005000U) /*!< FFT base address */
#define CLA_BASE              (AHB1_BUS_BASE + 0x00018000U) /*!< CLA base address */

/* advanced high performance bus 2 memory map */
#define GPIO_BASE             (AHB2_BUS_BASE + 0x00000000U) /*!< GPIO base address */
#define CAU_BASE              (AHB2_BUS_BASE + 0x00021000U) /*!< CAU base address */
#define TRNG_BASE             (AHB2_BUS_BASE + 0x00021800U) /*!< TRNG base address */
#define CPDM_BASE             (AHB2_BUS_BASE + 0x00022800U) /*!< CPDM base address */
#define TMU_BASE              (AHB2_BUS_BASE + 0x00024400U) /*!< TMU base address */
#define FAC_BASE              (AHB2_BUS_BASE + 0x00024800U) /*!< FAC base address */

/* advanced peripheral bus 3 memory map */
#define ADC_BASE              (APB3_BUS_BASE + 0x00000000U) /*!< ADC base address */
#define DAC_BASE              (APB3_BUS_BASE + 0x00001000U) /*!< DAC base address */

/* advanced high performance bus 3 memory map */
#define EXMC_BASE             (AHB3_BUS_BASE + 0x40000000U) /*!< EXMC base address */
#define QSPI_BASE             (AHB3_BUS_BASE + 0x40001000U) /*!< QSPI base address */

/* option byte and debug memory map */
#define OB_BASE               ((uint32_t)0x1FFFF800U)       /*!< OB base address */
#define DBG_BASE              ((uint32_t)0xE0044000U)       /*!< DBG base address */
#include "gd32g5x3_libopt.h"

#ifdef __cplusplus
}
#endif

#endif /* GD32G5X3_H */
