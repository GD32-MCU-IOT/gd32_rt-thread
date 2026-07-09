/*!
    \file    gd32f50x.h
    \brief   general definitions for gd32f50x

    \version 2026-02-25, V1.0.4, firmware for GD32F50x
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

#ifndef GD32F50X_H
#define GD32F50X_H

#ifdef __cplusplus
 extern "C" {
#endif

/* define GD32F50x */
#if !defined (GD32F50X)
#error "Please select chip type in project configuration"
/* #define GD32F50X */
#endif /* define GD32F50X */

#if !defined (GD32F50X)
#error "Please select the target gd322f50x device used in your application (in gd32f50x.h file)"
#endif /* undefine GD32F50X tip */

/* define value of high speed crystal oscillator (HXTAL) in Hz */
#if !defined  HXTAL_VALUE
#define HXTAL_VALUE    ((uint32_t)8000000) /*!< value of the external oscillator in Hz */
#endif /* high speed crystal oscillator value */

/* define startup timeout value of high speed crystal oscillator (HXTAL) */
#if !defined  (HXTAL_STARTUP_TIMEOUT)
#define HXTAL_STARTUP_TIMEOUT   ((uint16_t)0xFFFF)
#endif /* high speed crystal oscillator startup timeout */

/* define value of internal 8MHz RC oscillator (IRC8M) in Hz */
#if !defined  (IRC8M_VALUE)
#define IRC8M_VALUE  ((uint32_t)8000000)
#endif /* internal 8MHz RC oscillator value */

/* define value of internal 8MHz RC oscillator (IRC48M) in Hz */
#if !defined  (IRC48M_VALUE)
#define IRC48M_VALUE  ((uint32_t)48000000)
#endif /* internal 8MHz RC oscillator value */

/* define startup timeout value of internal 8MHz RC oscillator (IRC8M) */
#if !defined  (IRC8M_STARTUP_TIMEOUT)
#define IRC8M_STARTUP_TIMEOUT   ((uint16_t)0x0500)
#endif /* internal 8MHz RC oscillator startup timeout */

/* define value of internal 40KHz RC oscillator(IRC40K) in Hz */
#if !defined  (IRC40K_VALUE)
#define IRC40K_VALUE  ((uint32_t)40000)
#endif /* internal 40KHz RC oscillator value */

/* define value of low speed crystal oscillator (LXTAL)in Hz */
#if !defined  (LXTAL_VALUE)
#define LXTAL_VALUE  ((uint32_t)32768)
#endif /* low speed crystal oscillator value */

/* gd32f50x firmware library version number V1.0 */
#define __gd32f50x_STDPERIPH_VERSION_MAIN   (0x00) /*!< [31:24] main version     */
#define __gd32f50x_STDPERIPH_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version     */
#define __gd32f50x_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version     */
#define __gd32f50x_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __gd32f50x_STDPERIPH_VERSION        ((__gd32f50x_STDPERIPH_VERSION_MAIN << 24)\
                                            |(__gd32f50x_STDPERIPH_VERSION_SUB1 << 16)\
                                            |(__gd32f50x_STDPERIPH_VERSION_SUB2 << 8)\
                                            |(__gd32f50x_STDPERIPH_VERSION_RC))

/* configuration of the Cortex-M33 processor and core peripherals */
#define __CM33_REV                0x0100U   /*!< Core revision r1p0 */
#define __SAUREGION_PRESENT       0U        /*!< SAU regions are not present */
#define __MPU_PRESENT             1U        /*!< MPU is present */
#define __VTOR_PRESENT            1U        /*!< VTOR is present */
#define __NVIC_PRIO_BITS          4U        /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1         /*!< FPU present */
#define __DSP_PRESENT             1         /*!< DSP present */
typedef enum IRQn
{
    /* Cortex-M33 processor exceptions numbers */
    NonMaskableInt_IRQn          = -14,    /*!< non mask-able interrupt                                  */
    HardFault_IRQn               = -13,    /*!< hard-fault interrupt                                     */
    MemoryManagement_IRQn        = -12,    /*!< 4 Cortex-M33 memory management interrupt                 */
    BusFault_IRQn                = -11,    /*!< 5 Cortex-M33 bus fault interrupt                         */
    UsageFault_IRQn              = -10,    /*!< 6 Cortex-M33 usage fault interrupt                       */
    SVCall_IRQn                  = -5,     /*!< 11 Cortex-M33 sv call interrupt                          */
    DebugMonitor_IRQn            = -4,     /*!< 12 Cortex-M33 debug monitor interrupt                    */
    PendSV_IRQn                  = -2,     /*!< 14 Cortex-M33 pend sv interrupt                          */
    SysTick_IRQn                 = -1,     /*!< 15 Cortex-M33 system tick interrupt                      */

    /* interruput numbers */
    WWDGT_IRQn                   = 0,      /*!< window watchDog timer interrupt                          */
    LVD_VAVD_IRQn                = 1,      /*!< LVD/VAVD through EXTI line detect interrupt              */
    TAMPER_IRQn                  = 2,      /*!< tamper through EXTI line detect                          */
    RTC_IRQn                     = 3,      /*!< RTC through EXTI line interrupt                          */
    FMC_IRQn                     = 4,      /*!< FMC interrupt                                            */
    RCU_CTC_IRQn                 = 5,      /*!< RCU and CTC interrupt                                    */
    EXTI0_IRQn                   = 6,      /*!< EXTI line 0 interrupt                                    */
    EXTI1_IRQn                   = 7,      /*!< EXTI line 1 interrupt                                    */
    EXTI2_IRQn                   = 8,      /*!< EXTI line 2 interrupt                                    */
    EXTI3_IRQn                   = 9,      /*!< EXTI line 3 interrupt                                    */
    EXTI4_IRQn                   = 10,     /*!< EXTI line 4 interrupt                                    */
    DMA0_Channel0_IRQn           = 11,     /*!< DMA0 channel0 interrupt                                  */
    DMA0_Channel1_IRQn           = 12,     /*!< DMA0 channel1 interrupt                                  */
    DMA0_Channel2_IRQn           = 13,     /*!< DMA0 channel2 interrupt                                  */
    DMA0_Channel3_IRQn           = 14,     /*!< DMA0 channel3 interrupt                                  */
    DMA0_Channel4_IRQn           = 15,     /*!< DMA0 channel4 interrupt                                  */
    DMA0_Channel5_IRQn           = 16,     /*!< DMA0 channel5 interrupt                                  */
    DMA0_Channel6_IRQn           = 17,     /*!< DMA0 channel6 interrupt                                  */
    ADC0_1_IRQn                  = 18,     /*!< ADC0 and ADC1 interrupt                                  */
    CAN0_TX_IRQn                 = 19,     /*!< CAN0 TX interrupt                                        */
    CAN0_RX0_IRQn                = 20,     /*!< CAN0 RX0 interrupt                                       */
    CAN0_RX1_IRQn                = 21,     /*!< CAN0 RX1 interrupt                                       */
    CAN0_EWMC_IRQn               = 22,     /*!< CAN0 EWMC interrupt                                      */
    EXTI5_9_IRQn                 = 23,     /*!< EXTI[9:5] interrupts                                     */
    TIMER0_BRK_IRQn              = 24,     /*!< TIMER0 break and TIMER8 interrupt                        */
    TIMER0_UP_IRQn               = 25,     /*!< TIMER0 update and TIMER9 interrupt                       */
    TIMER0_TRG_CMT_IRQn          = 26,     /*!< TIMER0 trigger and commutation and TIMER10 interrupt     */
    TIMER0_Channel_IRQn          = 27,     /*!< TIMER0 channel capture compare interrupt                 */
    TIMER1_IRQn                  = 28,     /*!< TIMER1 interrupt                                         */
    TIMER2_IRQn                  = 29,     /*!< TIMER2 interrupt                                         */
    TIMER3_IRQn                  = 30,     /*!< TIMER3 interrupt                                         */
    I2C0_EV_IRQn                 = 31,     /*!< I2C0 event interrupt                                     */
    I2C0_ER_IRQn                 = 32,     /*!< I2C0 error interrupt                                     */
    I2C1_EV_IRQn                 = 33,     /*!< I2C1 event interrupt                                     */
    I2C1_ER_IRQn                 = 34,     /*!< I2C1 error interrupt                                     */
    SPI0_IRQn                    = 35,     /*!< SPI0 interrupt                                           */
    SPI1_IRQn                    = 36,     /*!< SPI1 interrupt                                           */
    USART0_IRQn                  = 37,     /*!< USART0 interrupt                                         */
    USART1_IRQn                  = 38,     /*!< USART1 interrupt                                         */
    USART2_IRQn                  = 39,     /*!< USART2 interrupt                                         */
    EXTI10_15_IRQn               = 40,     /*!< EXTI[15:10] interrupts                                   */
    RTC_Alarm_IRQn               = 41,     /*!< RTC alarm interrupt                                      */
    USBFS_WKUP_IRQn              = 42,     /*!< USBFS wakeup interrupt                                   */
    TIMER7_BRK_IRQn              = 43,     /*!< TIMER7 break and TIMER11 interrupt                       */
    TIMER7_UP_IRQn               = 44,     /*!< TIMER7 update and TIMER12 interrupt                      */
    TIMER7_TRG_CMT_IRQn          = 45,     /*!< TIMER7 trigger and commutation and TIMER13 interrupt     */
    TIMER7_Channel_IRQn          = 46,     /*!< TIMER7 channel capture compare interrupt                 */
    ADC2_IRQn                    = 47,     /*!< ADC2 global interrupt                                    */
    RCU_CKFM_IRQn                = 49,     /*!< RCU clock frequency monitor interrupt                    */
    CMP_WAKEUP_IRQn              = 50,     /*!< CMP Wakeup interrupt                                     */
    SPI2_IRQn                    = 51,     /*!< SPI2 global interrupt                                    */
    UART3_IRQn                   = 52,     /*!< UART3 global interrupt                                   */
    UART4_IRQn                   = 53,     /*!< UART4 global interrupt                                   */
    TIMER5_IRQn                  = 54,     /*!< TIMER5 global interrupt                                  */
    TIMER6_IRQn                  = 55,     /*!< TIMER6 global interrupt                                  */
    DMA1_Channel0_IRQn           = 56,     /*!< DMA1 channel0 global interrupt                           */
    DMA1_Channel1_IRQn           = 57,     /*!< DMA1 channel1 global interrupt                           */
    DMA1_Channel2_IRQn           = 58,     /*!< DMA1 channel2 global interrupt                           */
    DMA1_Channel3_IRQn           = 59,     /*!< DMA1 channel3 global interrupt                           */
    DMA1_Channel4_IRQn           = 60,     /*!< DMA1 channel3 global interrupt                           */
    DAC_IRQn                     = 61,     /*!< DAC  interrupt                                           */
    PMU_VUVD_VOVD_IRQn           = 62,     /*!< PMU VUVD/VOVD interrupt                                    */
    CAN1_TX_IRQn                 = 63,     /*!< CAN1 TX interrupt                                        */
    CAN1_RX0_IRQn                = 64,     /*!< CAN1 RX0 interrupt                                       */
    CAN1_RX1_IRQn                = 65,     /*!< CAN1 RX1 interrupt                                       */
    CAN1_EWMC_IRQn               = 66,     /*!< CAN1 EWMC interrupt                                      */
    SRAM_ECC_IRQn                = 67,     /*!< System interrupt                                         */
    FPU_IRQn                     = 68,     /*!< FPU interrupt                                            */
    CMP_IRQn                     = 69,     /*!< CMP interrupt                                            */
    DMAMUX_IRQn                  = 70,     /*!< DMAMUX interrupt                                         */
    CAU_IRQn                     = 71,     /*!< CAU interrupt                                            */
    HAU_IRQn                     = 72,     /*!< HAU interrupt                                            */
    TRNG_IRQn                    = 73,     /*!< TRNG interrupt                                           */
    USBFS_IRQn                   = 74,     /*!< USBFS interrupt                                          */
    TIMER4_IRQn                  = 75,     /*!< TIMER4 interrupt                                         */
    TIMER15_IRQn                 = 76,     /*!< TIMER15 interrupt                                        */
    TIMER16_IRQn                 = 77,     /*!< TIMER16 interrupt                                        */
    TIMER0_BRK_Channel_IRQn      = 78,     /*!< TIMER0 BRK Channel interrupt                             */
    TIMER7_BRK_Channel_IRQn      = 79      /*!< TIMER7 BRK Channel interrupt                             */
} IRQn_Type;

/* includes */
#include "core_cm33.h"
#include "system_gd32f50x.h"
#include <stdint.h>
#ifdef FW_DEBUG_ERR_REPORT
#include "gd32f50x_err_report.h"
#endif /* FW_DEBUG_ERR_REPORT */

/* enum definitions */
typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;

/* bit operations */
#define REG32(addr)                  (*(volatile uint32_t *)(uint32_t)(addr))
#define REG16(addr)                  (*(volatile uint16_t *)(uint32_t)(addr))
#define REG8(addr)                   (*(volatile uint8_t *)(uint32_t)(addr))
#define BIT(x)                       ((uint32_t)((uint32_t)0x01U<<(x)))
#define BITS(start, end)             ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end))))
#define GET_BITS(regval, start, end) (((regval) & BITS((start),(end))) >> (start))

/* main flash and SRAM memory map */
#define FLASH_BASE            ((uint32_t)0x08000000U)        /*!< main FLASH base address          */
#define SRAM_BASE             ((uint32_t)0x20000000U)        /*!< SRAM0 base address               */
#define OB_BASE               ((uint32_t)0x1FFFF800U)        /*!< OB base address                  */
#define DBG_BASE              ((uint32_t)0xE0045000U)        /*!< DBG base address                 */
#define EXMC_BASE             ((uint32_t)0xA0000000U)        /*!< EXMC register base address       */

/* peripheral memory map */
#define APB1_BUS_BASE         ((uint32_t)0x40000000U)        /*!< apb1 base address                */
#define APB2_BUS_BASE         ((uint32_t)0x40010000U)        /*!< apb2 base address                */
#define AHB1_BUS_BASE         ((uint32_t)0x40018000U)        /*!< ahb1 base address                */
#define AHB3_BUS_BASE         ((uint32_t)0x60000000U)        /*!< ahb3 base address                */

/* advanced peripheral bus 1 memory map */
#define TIMER_BASE            (APB1_BUS_BASE + 0x00000000U)  /*!< TIMER base address               */
#define RTC_BASE              (APB1_BUS_BASE + 0x00002800U)  /*!< RTC base address                 */
#define WWDGT_BASE            (APB1_BUS_BASE + 0x00002C00U)  /*!< WWDGT base address               */
#define FWDGT_BASE            (APB1_BUS_BASE + 0x00003000U)  /*!< FWDGT base address               */
#define SPI_BASE              (APB1_BUS_BASE + 0x00003800U)  /*!< SPI base address                 */
#define USART_BASE            (APB1_BUS_BASE + 0x00004400U)  /*!< USART base address               */
#define I2C_BASE              (APB1_BUS_BASE + 0x00005400U)  /*!< I2C base address                 */
#define CAN_APB_RAM1_BASE     (APB1_BUS_BASE + 0x00006000U)  /*!< CAN/APB SRAM base address        */
#define BKP_BASE              (APB1_BUS_BASE + 0x00006C00U)  /*!< BKP base address                 */
#define PMU_BASE              (APB1_BUS_BASE + 0x00007000U)  /*!< PMU base address                 */
#define DAC_BASE              (APB1_BUS_BASE + 0x00007400U)  /*!< DAC base address                 */
#define CMP_BASE              (APB1_BUS_BASE + 0x00007800U)  /*!< CMP base address                 */
#define CAN_APB_RAM2_BASE     (APB1_BUS_BASE + 0x00008400U)  /*!< CAN/APB SRAM2 base address       */
#define CTC_BASE              (APB1_BUS_BASE + 0x0000C800U)  /*!< CTC base address                 */

/* advanced peripheral bus 2 memory map */
#define AFIO_BASE             (APB2_BUS_BASE + 0x00000000U)  /*!< AFIO base address                */
#define EXTI_BASE             (APB2_BUS_BASE + 0x00000400U)  /*!< EXTI base address                */
#define GPIO_BASE             (APB2_BUS_BASE + 0x00000800U)  /*!< GPIO base address                */
#define ADC_BASE              (APB2_BUS_BASE + 0x00002400U)  /*!< ADC base address                 */
#define SYSCFG_BASE           (APB2_BUS_BASE + 0x00004000U)  /*!< SYSCFG base address              */
#define TRIGSEL_BASE          (APB2_BUS_BASE + 0x00004400U)  /*!< TRIGSEL base address             */
#define CAN_BASE              (APB2_BUS_BASE + 0x00005800U)  /*!< CAN base address                 */

/* advanced high performance bus 1 memory map */
#define DMA_BASE              (AHB1_BUS_BASE + 0x00008000U)  /*!< DMA base address                 */
#define DMAMUX_BASE           (AHB1_BUS_BASE + 0x00008800U)  /*!< DMAMUX base address              */
#define RCU_BASE              (AHB1_BUS_BASE + 0x00009000U)  /*!< RCU base address                 */
#define FMC_BASE              (AHB1_BUS_BASE + 0x0000A000U)  /*!< FMC base address                 */
#define CRC_BASE              (AHB1_BUS_BASE + 0x0000B000U)  /*!< CRC base address                 */
#define CAU_BASE              (AHB1_BUS_BASE + 0x0000B400U)  /*!< CAU base address                 */
#define HAU_BASE              (AHB1_BUS_BASE + 0x0000B800U)  /*!< HAU base address                 */
#define TRNG_BASE             (AHB1_BUS_BASE + 0x0000BC00U)  /*!< TRNG base address                */
#define USBFS_BASE            (AHB1_BUS_BASE + 0x0FFE8000U)  /*!< USBFS base address               */

/* define marco USE_STDPERIPH_DRIVER */
#if !defined  USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER
#endif
#ifdef USE_STDPERIPH_DRIVER
#include "gd32f50x_libopt.h"
#endif /* USE_STDPERIPH_DRIVER */

#ifdef __cplusplus
}
#endif

#endif /* GD32F50X_H */
