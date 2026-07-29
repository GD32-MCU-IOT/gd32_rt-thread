;/*!
;    \file    startup_gd32f5hc.s
;    \brief   start up file
;
;    \version 2026-04-15, V2.0.0, firmware for gd32w51x_f5hc
;*/
;
;/*
; * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
; * Copyright (c) 2026, GigaDevice Semiconductor Inc.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */

;/* This file refers the CMSIS standard, some adjustments are made according to GigaDevice chips */

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)                         ; top of stack
        DCD     Reset_Handler                       ; Vector Number 1,Reset Handler
        DCD     NMI_Handler                         ; Vector Number 2,NMI Handler
        DCD     HardFault_Handler                   ; Vector Number 3,Hard Fault Handler
        DCD     MemManage_Handler                   ; Vector Number 4,MPU Fault Handler
        DCD     BusFault_Handler                    ; Vector Number 5,Bus Fault Handler
        DCD     UsageFault_Handler                  ; Vector Number 6,Usage Fault Handler
        DCD     SecureFault_Handler                 ; Vector Number 7,Secure Fault Handler
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     0                                   ; Reserved
        DCD     SVC_Handler                         ; Vector Number 11,SVCall Handler
        DCD     DebugMon_Handler                    ; Vector Number 12,Debug Monitor Handler
        DCD     0                                   ; Reserved
        DCD     PendSV_Handler                      ; Vector Number 14,PendSV Handler
        DCD     SysTick_Handler                     ; Vector Number 15,SysTick Handler

        ; External Interrupts
        DCD     WWDGT_IRQHandler                    ; 16:Window Watchdog Timer
        DCD     LVD_IRQHandler                      ; 17:LVD through EXTI Line detect
        DCD     TAMPER_STAMP_LXTAL_IRQHandler       ; 18:RTC Tamper and TimeStamp events interrupt and LXTAL clock blocking
        DCD     RTC_WKUP_IRQHandler                 ; 19:RTC Wakeup through EXTI Line
        DCD     FMC_IRQHandler                      ; 20:FMC
        DCD     RCU_IRQHandler                      ; 21:RCU
        DCD     EXTI0_IRQHandler                    ; 22:EXTI Line 0
        DCD     EXTI1_IRQHandler                    ; 23:EXTI Line 1
        DCD     EXTI2_IRQHandler                    ; 24:EXTI Line 2
        DCD     EXTI3_IRQHandler                    ; 25:EXTI Line 3
        DCD     EXTI4_IRQHandler                    ; 26:EXTI Line 4
        DCD     DMA0_Channel0_IRQHandler            ; 27:DMA0 Channel0
        DCD     DMA0_Channel1_IRQHandler            ; 28:DMA0 Channel1
        DCD     DMA0_Channel2_IRQHandler            ; 29:DMA0 Channel2
        DCD     DMA0_Channel3_IRQHandler            ; 30:DMA0 Channel3
        DCD     DMA0_Channel4_IRQHandler            ; 31:DMA0 Channel4
        DCD     DMA0_Channel5_IRQHandler            ; 32:DMA0 Channel5
        DCD     DMA0_Channel6_IRQHandler            ; 33:DMA0 Channel6
        DCD     DMA0_Channel7_IRQHandler            ; 34:DMA0 Channel7
        DCD     ADC_IRQHandler                      ; 35:ADC
        DCD     TAMPER_STAMP_S_IRQHandler           ; 36:RTC Tamper and TimeStamp Events Security Interrupt
        DCD     RTC_WKUP_S_IRQHandler               ; 37:RTC wakeup security interrupt
        DCD     RTC_Alarm_S_IRQHandler              ; 38:RTC Alarm security interrupt
        DCD     EXTI5_9_IRQHandler                  ; 39:EXTI5 to EXTI9
        DCD     TIMER0_BRK_IRQHandler               ; 40:TIMER0 Break
        DCD     TIMER0_UP_IRQHandler                ; 41:TIMER0 Update
        DCD     TIMER0_CMT_IRQHandler               ; 42:TIMER0 Commutation
        DCD     TIMER0_Channel_IRQHandler           ; 43:TIMER0 Channel Capture Compare
        DCD     TIMER1_IRQHandler                   ; 44:TIMER1
        DCD     TIMER2_IRQHandler                   ; 45:TIMER2
        DCD     TIMER3_IRQHandler                   ; 46:TIMER3
        DCD     I2C0_EV_IRQHandler                  ; 47:I2C0 Event
        DCD     I2C0_ER_IRQHandler                  ; 48:I2C0 Error
        DCD     I2C1_EV_IRQHandler                  ; 49:I2C1 Event
        DCD     I2C1_ER_IRQHandler                  ; 50:I2C1 Error
        DCD     SPI0_IRQHandler                     ; 51:SPI0
        DCD     SPI1_IRQHandler                     ; 52:SPI1/I2S1
        DCD     USART0_IRQHandler                   ; 53:USART0
        DCD     USART1_IRQHandler                   ; 54:USART1
        DCD     USART2_IRQHandler                   ; 55:USART2
        DCD     EXTI10_15_IRQHandler                ; 56:EXTI10 to EXTI15
        DCD     RTC_Alarm_IRQHandler                ; 57:RTC Alarm
        DCD     VLVDF_IRQHandler                    ; 58:VDDA Low Voltage Detector
        DCD     0                                   ; 59:Reserved
        DCD     TIMER15_IRQHandler                  ; 60:TIMER15
        DCD     TIMER16_IRQHandler                  ; 61:TIMER16
        DCD     0                                   ; 62:Reserved
        DCD     0                                   ; 63:Reserved
        DCD     0                                   ; 64:Reserved
        DCD     0                                   ; 65:Reserved
        DCD     TIMER4_IRQHandler                   ; 66:TIMER4
        DCD     I2C0_WKUP_IRQHandler                ; 67:I2C0 Wakeup
        DCD     USART0_WKUP_IRQHandler              ; 68:USART0 Wakeup
        DCD     USART2_WKUP_IRQHandler              ; 69:USART2 Wakeup
        DCD     TIMER5_IRQHandler                   ; 70:TIMER5
        DCD     0                                   ; 71:Reserved
        DCD     DMA1_Channel0_IRQHandler            ; 72:DMA1 Channel0
        DCD     DMA1_Channel1_IRQHandler            ; 73:DMA1 Channel1
        DCD     DMA1_Channel2_IRQHandler            ; 74:DMA1 Chan1nel2
        DCD     DMA1_Channel3_IRQHandler            ; 75:DMA1 Channel3
        DCD     DMA1_Channel4_IRQHandler            ; 76:DMA1 Channel4
        DCD     DMA1_Channel5_IRQHandler            ; 77:DMA1 Channel5
        DCD     DMA1_Channel6_IRQHandler            ; 78:DMA1 Channel6
        DCD     DMA1_Channel7_IRQHandler            ; 79:DMA1 Channel7
        DCD     0                                   ; 80:Reserved
        DCD     I2C1_WKUP_IRQHandler                ; 81:I2C1 Wakeup
        DCD     0                                   ; 82:Reserved
        DCD     USBFS_IRQHandler                    ; 83:USBFS global interrupt
        DCD     0                                   ; 84:Reserved
        DCD     0                                   ; 85:Reserved
        DCD     0                                   ; 86:Reserved
        DCD     0                                   ; 87:Reserved
        DCD     0                                   ; 88:Reserved
        DCD     0                                   ; 89:Reserved
        DCD     0                                   ; 90:Reserved
        DCD     0                                   ; 91:Reserved
        DCD     USBFS_WKUP_IRQHandler               ; 92:USBFS_WKUP
        DCD     0                                   ; 93:Reserved
        DCD     0                                   ; 94:Reserved
        DCD     CAU_IRQHandler                      ; 95:CAU
        DCD     HAU_TRNG_IRQHandler                 ; 96:HAU and TRNG
        DCD     FPU_IRQHandler                      ; 97:FPU
        DCD     0                                   ; 98:Reserved
        DCD     0                                   ; 99:Reserved
        DCD     0                                   ; 100:Reserved
        DCD     0                                   ; 101:Reserved
        DCD     0                                   ; 102:Reserved
        DCD     0                                   ; 103:Reserved
        DCD     0                                   ; 104:Reserved
        DCD     0                                   ; 105:Reserved
        DCD     0                                   ; 106:Reserved
        DCD     0                                   ; 107:Reserved
        DCD     0                                   ; 108:Reserved
        DCD     0                                   ; 109:Reserved
        DCD     EFUSE_IRQHandler                    ; 110:EFUSE
        DCD     QSPI_IRQHandler                     ; 111:QUADSPI
        DCD     PKCAU_IRQHandler                    ; 112:PKCAU
        DCD     0                                   ; 113:Reserved
        DCD     ICACHE_IRQHandler                   ; 114:ICACHE
        DCD     TZIAC_S_IRQHandler                  ; 115:TrustZone Interrupt Controller secure interrupts
        DCD     FMC_S_IRQHandler                    ; 116:FMC
        DCD     QSPI_S_IRQHandler                   ; 117:QSPI security interrupt
                                              

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SecureFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SecureFault_Handler
        B SecureFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDGT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDGT_IRQHandler
        B WWDGT_IRQHandler

        PUBWEAK LVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LVD_IRQHandler
        B LVD_IRQHandler

        PUBWEAK TAMPER_STAMP_LXTAL_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMPER_STAMP_LXTAL_IRQHandler
        B TAMPER_STAMP_LXTAL_IRQHandler

        PUBWEAK RTC_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_WKUP_IRQHandler
        B RTC_WKUP_IRQHandler

        PUBWEAK FMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMC_IRQHandler
        B FMC_IRQHandler

        PUBWEAK RCU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCU_IRQHandler
        B RCU_IRQHandler

        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_IRQHandler
        B EXTI0_IRQHandler

        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_IRQHandler
        B EXTI1_IRQHandler

        PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_IRQHandler
        B EXTI2_IRQHandler

        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler

        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_IRQHandler
        B EXTI1_IRQHandler

        PUBWEAK DMA0_Channel0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel0_IRQHandler
        B DMA0_Channel0_IRQHandler

        PUBWEAK DMA0_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel1_IRQHandler
        B DMA0_Channel1_IRQHandler

        PUBWEAK DMA0_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel2_IRQHandler
        B DMA0_Channel2_IRQHandler

        PUBWEAK DMA0_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel3_IRQHandler
        B DMA0_Channel3_IRQHandler

        PUBWEAK DMA0_Channel4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel4_IRQHandler
        B DMA0_Channel4_IRQHandler

        PUBWEAK DMA0_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel5_IRQHandler
        B DMA0_Channel5_IRQHandler

        PUBWEAK DMA0_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel6_IRQHandler
        B DMA0_Channel6_IRQHandler

        PUBWEAK DMA0_Channel7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel7_IRQHandler
        B DMA0_Channel7_IRQHandler

        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_IRQHandler
        B ADC_IRQHandler

        PUBWEAK TAMPER_STAMP_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMPER_STAMP_S_IRQHandler
        B TAMPER_STAMP_S_IRQHandler
        
        PUBWEAK RTC_WKUP_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_WKUP_S_IRQHandler
        B RTC_WKUP_S_IRQHandler

        PUBWEAK RTC_Alarm_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_Alarm_S_IRQHandler
        B RTC_Alarm_S_IRQHandler

        PUBWEAK EXTI5_9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI5_9_IRQHandler
        B EXTI5_9_IRQHandler

        PUBWEAK TIMER0_BRK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_BRK_IRQHandler
        B TIMER0_BRK_IRQHandler

        PUBWEAK TIMER0_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_UP_IRQHandler
        B TIMER0_UP_IRQHandler

        PUBWEAK TIMER0_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_CMT_IRQHandler
        B TIMER0_CMT_IRQHandler

        PUBWEAK TIMER0_Channel_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_Channel_IRQHandler
        B TIMER0_Channel_IRQHandler

        PUBWEAK TIMER1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER1_IRQHandler
        B TIMER1_IRQHandler

        PUBWEAK TIMER2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER2_IRQHandler
        B TIMER2_IRQHandler

        PUBWEAK TIMER3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER3_IRQHandler
        B TIMER3_IRQHandler

        PUBWEAK I2C0_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_EV_IRQHandler
        B I2C0_EV_IRQHandler

        PUBWEAK I2C0_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_ER_IRQHandler
        B I2C0_ER_IRQHandler

        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler
        
        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_ER_IRQHandler    
        B I2C1_ER_IRQHandler

        PUBWEAK SPI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_IRQHandler
        B SPI0_IRQHandler

        PUBWEAK SPI1_IRQHandler 
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler 
        B SPI1_IRQHandler

        PUBWEAK USART0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART0_IRQHandler
        B USART0_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK EXTI10_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI10_15_IRQHandler
        B EXTI10_15_IRQHandler

        PUBWEAK RTC_Alarm_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_Alarm_IRQHandler
        B RTC_Alarm_IRQHandler

        PUBWEAK VLVDF_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
VLVDF_IRQHandler
        B VLVDF_IRQHandler

        PUBWEAK TIMER15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER15_IRQHandler
        B TIMER15_IRQHandler

        PUBWEAK TIMER16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER16_IRQHandler
        B TIMER16_IRQHandler

        PUBWEAK TIMER4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER4_IRQHandler
        B TIMER4_IRQHandler

        PUBWEAK I2C0_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_WKUP_IRQHandler
        B I2C0_WKUP_IRQHandler

        PUBWEAK USART0_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART0_WKUP_IRQHandler
        B USART0_WKUP_IRQHandler

        PUBWEAK USART2_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_WKUP_IRQHandler
        B USART2_WKUP_IRQHandler

        PUBWEAK TIMER5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER5_IRQHandler
        B TIMER5_IRQHandler

        PUBWEAK DMA1_Channel0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel0_IRQHandler
        B DMA1_Channel0_IRQHandler

        PUBWEAK DMA1_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel1_IRQHandler
        B DMA1_Channel1_IRQHandler

        PUBWEAK DMA1_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel2_IRQHandler
        B DMA1_Channel2_IRQHandler

        PUBWEAK DMA1_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel3_IRQHandler
        B DMA1_Channel3_IRQHandler

        PUBWEAK DMA1_Channel4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel4_IRQHandler
        B DMA1_Channel4_IRQHandler

        PUBWEAK DMA1_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel5_IRQHandler
        B DMA1_Channel5_IRQHandler

        PUBWEAK DMA1_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel6_IRQHandler
        B DMA1_Channel6_IRQHandler

        PUBWEAK DMA1_Channel7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel7_IRQHandler
        B DMA1_Channel7_IRQHandler

        PUBWEAK I2C1_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_WKUP_IRQHandler
        B I2C1_WKUP_IRQHandler

        PUBWEAK USBFS_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBFS_IRQHandler
        B USBFS_IRQHandler

        PUBWEAK USBFS_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBFS_WKUP_IRQHandler
        B USBFS_WKUP_IRQHandler

        PUBWEAK CAU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAU_IRQHandler
        B CAU_IRQHandler

        PUBWEAK HAU_TRNG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HAU_TRNG_IRQHandler
        B HAU_TRNG_IRQHandler

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FPU_IRQHandler
        B FPU_IRQHandler

        PUBWEAK EFUSE_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EFUSE_IRQHandler
        B EFUSE_IRQHandler

        PUBWEAK QSPI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
QSPI_IRQHandler
        B QSPI_IRQHandler

        PUBWEAK PKCAU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PKCAU_IRQHandler
        B PKCAU_IRQHandler

        PUBWEAK ICACHE_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ICACHE_IRQHandler
        B ICACHE_IRQHandler

        PUBWEAK TZIAC_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TZIAC_S_IRQHandler
        B TZIAC_S_IRQHandler

        PUBWEAK FMC_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMC_S_IRQHandler
        B FMC_S_IRQHandler

        PUBWEAK QSPI_S_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
QSPI_S_IRQHandler
        B QSPI_S_IRQHandler

        END