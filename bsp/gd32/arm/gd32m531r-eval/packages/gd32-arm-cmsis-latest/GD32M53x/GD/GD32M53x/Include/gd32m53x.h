/*!
    \file    gd32m53x.h
    \brief   general definitions for gd32m53x

    \version 2026-03-04, V1.0.0, firmware for GD32M53x
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

#ifndef GD32M53X_H
#define GD32M53X_H

#ifdef __cplusplus
extern "C" {
#endif

/* define gd32m53x */
#if !defined (GD32M53X)
#error "Please select chip type in project configuration"
/* #define GD32M53X */
#endif /* define gd32m53x */

#if !defined (GD32M53X)
#error "Please select the target gd32m53x device used in your application (in gd32m53x.h file)"
#endif /* undefine gd32m53x tip */

/* define value of high speed crystal oscillator (HXTAL) in Hz */
#if !defined  HXTAL_VALUE
#define HXTAL_VALUE    (8000000U) /* !< from 4M to 32M *!< value of the external oscillator in Hz*/
#endif /* high speed crystal oscillator value */

/* define startup timeout value of high speed crystal oscillator (HXTAL) */
#if !defined  (HXTAL_STARTUP_TIMEOUT)
#define HXTAL_STARTUP_TIMEOUT   ((uint16_t)0x0FFFF)
#endif /* high speed crystal oscillator startup timeout */

/* define value of internal 32MHz RC oscillator (IRC32M) in Hz */
#if !defined  (IRC32M_VALUE)
#define IRC32M_VALUE  ((uint32_t)32000000)
#endif /* internal 32MHz RC oscillator value */

/* define startup timeout value of internal 32MHz RC oscillator (IRC32M) */
#if !defined  (IRC32M_STARTUP_TIMEOUT)
#define IRC32M_STARTUP_TIMEOUT   ((uint16_t)0x0500)
#endif /* internal 32MHz RC oscillator startup timeout */

/* define value of internal 32KHz RC oscillator(IRC32K) in Hz */
#if !defined  (IRC32K_VALUE)
#define IRC32K_VALUE  ((uint32_t)32000)
#endif /* internal 32KHz RC oscillator value */

/* GD32M53x firmware library version number */
#define __GD32M53X_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __GD32M53X_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __GD32M53X_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __GD32M53X_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __GD32M53X_STDPERIPH_VERSION        ((__GD32M53X_STDPERIPH_VERSION_MAIN << 24)\
                                             |(__GD32M53X_STDPERIPH_VERSION_SUB1 << 16)\
                                             |(__GD32M53X_STDPERIPH_VERSION_SUB2 << 8)\
                                             |(__GD32M53X_STDPERIPH_VERSION_RC))

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
typedef enum IRQn {
    /* Cortex-M33 processor exceptions numbers */
    NonMaskableInt_IRQn          = -14,    /*!< non mask-able interrupt */
    HardFault_IRQn               = -13,    /*!< hard-fault interrupt */
    MemoryManagement_IRQn        = -12,    /*!< 4 Cortex-M33 memory management interrupt */
    BusFault_IRQn                = -11,    /*!< 5 Cortex-M33 bus fault interrupt */
    UsageFault_IRQn              = -10,    /*!< 6 Cortex-M33 usage fault interrupt */
    SVCall_IRQn                  = -5,     /*!< 11 Cortex-M33 sv call interrupt */
    DebugMonitor_IRQn            = -4,     /*!< 12 Cortex-M33 debug monitor interrupt */
    PendSV_IRQn                  = -2,     /*!< 14 Cortex-M33 pend sv interrupt */
    SysTick_IRQn                 = -1,     /*!< 15 Cortex-M33 system tick interrupt */

    /* interrupt numbers */
    WWDGT_IRQn                   = 0,      /*!< window watchdog timer interrupt */
    LVD1_IRQn                    = 1,      /*!< LVD1 through EXTI line 16 detect interrupt */
    LVD2_IRQn                    = 2,      /*!< LVD2 through EXTI line 17 detect interrupt */
    FMC_IRQn                     = 4,      /*!< FMC interrupt */
    RCU_IRQn                     = 5,      /*!< RCU interrupt */
    EXTI0_IRQn                   = 6,      /*!< EXTI line 0 interrupt */
    EXTI1_IRQn                   = 7,      /*!< EXTI line 1 interrupt */
    EXTI2_IRQn                   = 8,      /*!< EXTI line 2 interrupt */
    EXTI3_IRQn                   = 9,      /*!< EXTI line 3 interrupt */
    EXTI4_IRQn                   = 10,     /*!< EXTI line 4 interrupt */
    DMA0_Channel0_IRQn           = 11,     /*!< DMA0 channel0 interrupt */
    DMA0_Channel1_IRQn           = 12,     /*!< DMA0 channel1 interrupt */
    DMA0_Channel2_IRQn           = 13,     /*!< DMA0 channel2 interrupt */
    DMA0_Channel3_IRQn           = 14,     /*!< DMA0 channel3 interrupt */
    DMA0_Channel4_IRQn           = 15,     /*!< DMA0 channel4 interrupt */
    DMA0_Channel5_IRQn           = 16,     /*!< DMA0 channel5 interrupt  */
    ADC0_IRQn                    = 18,     /*!< ADC0 interrupt */
    CAN_TX_IRQn                  = 19,     /*!< CAN TX interrupt */
    CAN_RX0_IRQn                 = 20,     /*!< CAN RX0 interrupt */
    CAN_RX1_IRQn                 = 21,     /*!< CAN RX1 interrupt */
    CAN_EWMC_IRQn                = 22,     /*!< CAN EWMC interrupt */
    EXTI5_9_IRQn                 = 23,     /*!< EXTI[9:5] interrupts */
    TIMER0_BRK_IRQn              = 24,     /*!< TIMER0 break  interrupt */
    TIMER0_UP_IRQn               = 25,     /*!< TIMER0 update interrupt */
    TIMER0_TRG_CMT_IRQn          = 26,     /*!< TIMER0 trigger and channel commutation interrupt */
    TIMER0_Channel_IRQn          = 27,     /*!< TIMER0 channel capture compare interrupt */
    TIMER1_IRQn                  = 28,     /*!< TIMER1 interrupt */
    TIMER2_IRQn                  = 29,     /*!< TIMER2 interrupt */
    GPTIMER0_IRQn                = 30,     /*!< GPTIMER0 interrupt */
    I2C_EV_IRQn                  = 31,     /*!< I2C event interrupt */
    I2C_ER_IRQn                  = 32,     /*!< I2C error interrupt */
    SPI_IRQn                     = 35,     /*!< SPI interrupt */
    UART0_IRQn                   = 37,     /*!< UART0 interrupt */
    UART1_IRQn                   = 38,     /*!< UART1 interrupt */
    EXTI10_15_IRQn               = 40,     /*!< EXTI[15:10] interrupts */
    TIMER7_BRK_IRQn              = 43,     /*!< TIMER7 break interrupt */
    TIMER7_UP_IRQn               = 44,     /*!< TIMER7 update interrupt */
    TIMER7_TRG_CMT_IRQn          = 45,     /*!< TIMER7 trigger and commutation interrupt */
    TIMER7_Channel_IRQn          = 46,     /*!< TIMER7 channel capture compare interrupt */
    TMU_IRQn                     = 47,     /*!< TMU interrupt */
    GPTIMER1_IRQn                = 50,     /*!< GPTIMER1 interrupt */
    UART2_IRQn                   = 52,     /*!< UART2 interrupt */
    UART3_IRQn                   = 53,     /*!< UART3 interrupt */
    CPTIMER0_IRQn                = 54,     /*!< CPTIMER0 global interrupt */
    CPTIMER1_IRQn                = 55,     /*!< CPTIMER1 global interrupt */
    DMA1_Channel0_IRQn           = 56,     /*!< DMA1 channel0 global interrupt */
    DMA1_Channel1_IRQn           = 57,     /*!< DMA1 channel1 global interrupt */
    DMA1_Channel2_IRQn           = 58,     /*!< DMA1 channel2 global interrupt */
    DMA1_Channel3_IRQn           = 59,     /*!< DMA1 channel3 global interrupt */
    DMA1_Channel4_IRQn           = 60,     /*!< DMA1 channel4 global interrupt */
    DMA1_Channel5_IRQn           = 61,     /*!< DMA1 channel5 global interrupt */
    DMAMUX_OVERRUN_IRQn          = 62,     /*!< DMAMUX overrun interrupt */
    CPTIMERW_IRQn                = 63,     /*!< CPTIMERW global interrupt */
    CFMU_IRQn                    = 65,     /*!< CFMU interrupt */
    I2C_WKUP_IRQn                = 66,     /*!< I2C wakeup through EXTI line 23 detect interrupt*/
    FWDGT_IRQn                   = 67,     /*!< FWDGT through EXTI line 22 detect interrupt */
    CMP0_IRQn                    = 70,     /*!< CMP0 interrupt */
    CMP1_IRQn                    = 71,     /*!< CMP1 interrupt */
    CMP2_IRQn                    = 72,     /*!< CMP2 interrupt */
    CMP3_IRQn                    = 73,     /*!< CMP3 interrupt */
    ADC2_IRQn                    = 75,     /*!< ADC2 interrupt */
    POC_IRQn                     = 77,     /*!< POC global interrupt */
    GTOC0_IRQn                   = 79,     /*!< GTOC0 interrupt */
    GTOC1_IRQn                   = 80,     /*!< GTOC1 interrupt */
    GTOC2_IRQn                   = 81,     /*!< GTOC2 interrupt */
    GTOC3_IRQn                   = 82,     /*!< GTOC3 interrupt */
    CMP0_EXTI_IRQn               = 85,     /*!< CMP0 through EXTI line 18 detect interrupt */
    CMP1_EXTI_IRQn               = 86,     /*!< CMP1 through EXTI line 19 detect interrupt */
    CMP2_EXTI_IRQn               = 87,     /*!< CMP2 through EXTI line 20 detect interrupt */
    CMP3_EXTI_IRQn               = 88,     /*!< CMP3 through EXTI line 21 detect interrupt */
    SRAMC_ECC_IRQn               = 92,     /*!< SRAMC_ECC interrupt */
} IRQn_Type;

/* includes */
#include "core_cm33.h"
#include "system_gd32m53x.h"
#include <stdint.h>
#ifdef FW_DEBUG_ERR_REPORT
#include "gd32m53x_err_report.h"
#endif /* FW_DEBUG_ERR_REPORT */

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
#define FLASH_BASE            ((uint32_t)0x08000000U)               /*!< main FLASH base address */
#define SRAM_BASE             ((uint32_t)0x20000000U)               /*!< SRAM base address */

/* peripheral memory map */
#define APB1_BUS_BASE         ((uint32_t)0x40000000U)               /*!< apb1 base address */
#define APB2_BUS_BASE         ((uint32_t)0x40010000U)               /*!< apb2 base address */
#define AHB1_BUS_BASE         ((uint32_t)0x40020000U)               /*!< ahb1 base address */
#define AHB2_BUS_BASE         ((uint32_t)0x48000000U)               /*!< ahb2 base address */

/* advanced peripheral bus 1 memory map */
#define CPTIMER_BASE          (APB1_BUS_BASE + 0x00000000U)         /*!< CPTIMER base address */
#define WWDGT_BASE            (APB1_BUS_BASE + 0x00002C00U)         /*!< WWDGT base address */
#define FWDGT_BASE            (APB1_BUS_BASE + 0x00003000U)         /*!< FWDGT base address */
#define UART_BASE             (APB1_BUS_BASE + 0x00004C00U)         /*!< UART base address */
#define I2C_BASE              (APB1_BUS_BASE + 0x00005400U)         /*!< I2C base address */
#define PMU_BASE              (APB1_BUS_BASE + 0x00007000U)         /*!< PMU base address */
#define DAC_BASE              (APB1_BUS_BASE + 0x00007400U)         /*!< DAC base address */
#define CFMU_BASE             (APB1_BUS_BASE + 0x0000C800U)         /*!< CFMU base address */
#define CPTIMERW_BASE         (APB1_BUS_BASE + 0x0000E000U)         /*!< CPTIMERW base address */

/* advanced peripheral bus 2 memory map */
#define SYSCFG_BASE           (APB2_BUS_BASE + 0x00000000U)         /*!< SYSCFG base address */
#define EXTI_BASE             (APB2_BUS_BASE + 0x00000400U)         /*!< EXTI base address */
#define ADC_BASE              (APB2_BUS_BASE + 0x00002000U)         /*!< ADC base address */
#define TIMER_BASE            (APB2_BUS_BASE + 0x00002C00U)         /*!< TIMER base address */
#define SPI_BASE              (APB2_BUS_BASE + 0x00003000U)         /*!< SPI base address */
#define GPTIMER_BASE          (APB2_BUS_BASE + 0x00006000U)         /*!< GPTIMER base address */
#define CMP_BASE              (APB2_BUS_BASE + 0x00007C00U)         /*!< CMP base address */
#define EVIC_BASE             (APB2_BUS_BASE + 0x00008400U)         /*!< CMP base address */
#define CAN_BASE              (APB2_BUS_BASE + 0x0000A000U)         /*!< CAN base address */

/* advanced high performance bus 1 memory map */
#define DMA_BASE              (AHB1_BUS_BASE + 0x00000000U)         /*!< DMA base address */
#define DMAMUX_BASE           (AHB1_BUS_BASE + 0x00000800U)         /*!< DMAMUX base address */
#define RCU_BASE              (AHB1_BUS_BASE + 0x00001000U)         /*!< RCU base address */
#define FMC_BASE              (AHB1_BUS_BASE + 0x00002000U)         /*!< FMC base address */
#define CRC_BASE              (AHB1_BUS_BASE + 0x00003000U)         /*!< CRC base address */

/* advanced high performance bus 2 memory map */
#define GPIO_BASE             (AHB2_BUS_BASE + 0x00000000U)         /*!< GPIO base address */
#define POC_BASE              (AHB2_BUS_BASE + 0x00004400U)         /*!< POC base address */
#define GTOC_BASE             (AHB2_BUS_BASE + 0x00004800U)         /*!< GTOC base address */
#define SVPWM_BASE            (AHB2_BUS_BASE + 0x00024000U)         /*!< SVPWM base address */
#define TMU_BASE              (AHB2_BUS_BASE + 0x00024400U)         /*!< TMU base address */

/* option byte and debug memory map */
#define OB_BASE               ((uint32_t)0x1FFFF800U)               /*!< OB base address */
#define DBG_BASE              ((uint32_t)0xE0044000U)               /*!< DBG base address */

/* define marco USE_STDPERIPH_DRIVER */
#if !defined  USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER
#endif
#ifdef USE_STDPERIPH_DRIVER
#include "gd32m53x_libopt.h"
#endif /* USE_STDPERIPH_DRIVER */

#ifdef __cplusplus
}
#endif

#endif /* GD32M53X_H */
