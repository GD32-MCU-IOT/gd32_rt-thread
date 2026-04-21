;/*!
;    \file    startup_gd32m53x.s
;    \brief   start up file
;
;    \version 2026-03-04, V1.0.0, firmware for GD32M53x
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
        DCD     sfe(CSTACK)                             ; Top of Stack
        DCD     Reset_Handler                           ; Reset Handler
        DCD     NMI_Handler                             ; NMI Handler
        DCD     HardFault_Handler                       ; Hard Fault Handler
        DCD     MemManage_Handler                       ; MPU Fault Handler
        DCD     BusFault_Handler                        ; Bus Fault Handler
        DCD     UsageFault_Handler                      ; Usage Fault Handler
        DCD     0                                       ; Reserved
        DCD     0                                       ; Reserved
        DCD     0                                       ; Reserved
        DCD     0                                       ; Reserved
        DCD     SVC_Handler                             ; SVCall Handler
        DCD     DebugMon_Handler                        ; Debug Monitor Handler
        DCD     0                                       ; Reserved
        DCD     PendSV_Handler                          ; PendSV Handler
        DCD     SysTick_Handler                         ; SysTick Handler

;               /* External interrupts handler */
        DCD     WWDGT_IRQHandler                        ; 16:Window Watchdog Timer
        DCD     LVD1_IRQHandler                         ; 17:LVD1 through EXTI Line 16 Detect
        DCD     LVD2_IRQHandler                         ; 18:LVD2 through EXTI Line 17 Detect
        DCD     0                                       ; 19:Reserved
        DCD     FMC_IRQHandler                          ; 20:FMC
        DCD     RCU_IRQHandler                          ; 21:RCU
        DCD     EXTI0_IRQHandler                        ; 22:EXTI Line 0
        DCD     EXTI1_IRQHandler                        ; 23:EXTI Line 1
        DCD     EXTI2_IRQHandler                        ; 24:EXTI Line 2
        DCD     EXTI3_IRQHandler                        ; 25:EXTI Line 3
        DCD     EXTI4_IRQHandler                        ; 26:EXTI Line 4
        DCD     DMA0_Channel0_IRQHandler                ; 27:DMA0 Channel0
        DCD     DMA0_Channel1_IRQHandler                ; 28:DMA0 Channel1
        DCD     DMA0_Channel2_IRQHandler                ; 29:DMA0 Channel2
        DCD     DMA0_Channel3_IRQHandler                ; 30:DMA0 Channel3
        DCD     DMA0_Channel4_IRQHandler                ; 31:DMA0 Channel4
        DCD     DMA0_Channel5_IRQHandler                ; 32:DMA0 Channel5
        DCD     0                                       ; 33:Reserved
        DCD     ADC0_IRQHandler                         ; 34:ADC0
        DCD     CAN_TX_IRQHandler                       ; 35:CAN TX
        DCD     CAN_RX0_IRQHandler                      ; 36:CAN RX0
        DCD     CAN_RX1_IRQHandler                      ; 37:CAN RX1
        DCD     CAN_EWMC_IRQHandler                     ; 38:CAN EWMC
        DCD     EXTI5_9_IRQHandler                      ; 39:EXTI Line 5 to EXTI Line 9
        DCD     TIMER0_BRK_IRQHandler                   ; 40:TIMER0 Break
        DCD     TIMER0_UP_IRQHandler                    ; 41:TIMER0 Update
        DCD     TIMER0_TRG_CMT_IRQHandler               ; 42:TIMER0 Trigger and Commutation
        DCD     TIMER0_Channel_IRQHandler               ; 43:TIMER0 Channel Capture Compare
        DCD     TIMER1_IRQHandler                       ; 44:TIMER1
        DCD     TIMER2_IRQHandler                       ; 45:TIMER2
        DCD     GPTIMER0_IRQHandler                     ; 46:GPTIMER0
        DCD     I2C_EV_IRQHandler                       ; 47:I2C Event
        DCD     I2C_ER_IRQHandler                       ; 48:I2C Error
        DCD     0                                       ; 49:Reserved
        DCD     0                                       ; 50:Reserved
        DCD     SPI_IRQHandler                          ; 51:SPI
        DCD     0                                       ; 52:Reserved
        DCD     UART0_IRQHandler                        ; 53:UART0
        DCD     UART1_IRQHandler                        ; 54:UART1
        DCD     0                                       ; 55:Reserved
        DCD     EXTI10_15_IRQHandler                    ; 56:EXTI Line 10 to EXTI Line 15
        DCD     0                                       ; 57:Reserved
        DCD     0                                       ; 58:Reserved
        DCD     TIMER7_BRK_IRQHandler                   ; 59:TIMER7 Break
        DCD     TIMER7_UP_IRQHandler                    ; 60:TIMER7 Update
        DCD     TIMER7_TRG_CMT_IRQHandler               ; 61:TIMER7 Trigger and Commutation
        DCD     TIMER7_Channel_IRQHandler               ; 62:TIMER7 Channel Capture Compare
        DCD     TMU_IRQHandler                          ; 63:TMU
        DCD     0                                       ; 64:Reserved
        DCD     0                                       ; 65:Reserved
        DCD     GPTIMER1_IRQHandler                     ; 66:GPTIMER1
        DCD     0                                       ; 67:Reserved
        DCD     UART2_IRQHandler                        ; 68:UART2
        DCD     UART3_IRQHandler                        ; 69:UART3
        DCD     CPTIMER0_IRQHandler                     ; 70:CPTIMER0
        DCD     CPTIMER1_IRQHandler                     ; 71:CPTIMER1
        DCD     DMA1_Channel0_IRQHandler                ; 72:DMA1 Channel0
        DCD     DMA1_Channel1_IRQHandler                ; 73:DMA1 Channel1
        DCD     DMA1_Channel2_IRQHandler                ; 74:DMA1 Channel2
        DCD     DMA1_Channel3_IRQHandler                ; 75:DMA1 Channel3
        DCD     DMA1_Channel4_IRQHandler                ; 76:DMA1 Channel4
        DCD     DMA1_Channel5_IRQHandler                ; 77:DMA1 Channel5
        DCD     DMAMUX_OVERRUN_IRQHandler               ; 78:DMAMUX Overrun
        DCD     CPTIMERW_IRQHandler                     ; 79:CPTIMERW
        DCD     0                                       ; 80:Reserved
        DCD     CFMU_IRQHandler                         ; 81:CFMU
        DCD     I2C_WKUP_IRQHandler                     ; 82:I2C Wakeup through EXTI Line 23 Detect
        DCD     FWDGT_IRQHandler                        ; 83:FWDGT through EXTI Line 22 Detect
        DCD     0                                       ; 84:Reserved
        DCD     0                                       ; 85:Reserved
        DCD     CMP0_IRQHandler                         ; 86:CMP0
        DCD     CMP1_IRQHandler                         ; 87:CMP1
        DCD     CMP2_IRQHandler                         ; 88:CMP2
        DCD     CMP3_IRQHandler                         ; 89:CMP3
        DCD     0                                       ; 90:Reserved
        DCD     ADC2_IRQHandler                         ; 91:ADC2
        DCD     0                                       ; 92:Reserved
        DCD     POC_IRQHandler                          ; 93:POC
        DCD     0                                       ; 94:Reserved
        DCD     GTOC0_IRQHandler                        ; 95:GTOC0
        DCD     GTOC1_IRQHandler                        ; 96:GTOC1
        DCD     GTOC2_IRQHandler                        ; 97:GTOC2
        DCD     GTOC3_IRQHandler                        ; 98:GTOC3
        DCD     0                                       ; 99:Reserved
        DCD     0                                       ; 100:Reserved
        DCD     CMP0_EXTI_IRQHandler                    ; 101:CMP0 through EXTI Line 18 Detect
        DCD     CMP1_EXTI_IRQHandler                    ; 102:CMP1 through EXTI Line 19 Detect
        DCD     CMP2_EXTI_IRQHandler                    ; 103:CMP2 through EXTI Line 20 Detect
        DCD     CMP3_EXTI_IRQHandler                    ; 104:CMP3 through EXTI Line 21 Detect
        DCD     0                                       ; 105:Reserved
        DCD     0                                       ; 106:Reserved
        DCD     0                                       ; 107:Reserved
        DCD     SRAMC_ECC_IRQHandler                    ; 108:SRAMC ECC

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler

            LDR     R0, =0x20000000
            ADD     R1, R0, #0x2000
            MOVS    R2, #0x0
MEM_INIT    STR     R2, [R0,#0]
            ADD     R0, R0, #0x4
            CMP     R0, R1
            BNE     MEM_INIT

        LDR     R0, = SystemInit
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

        PUBWEAK LVD1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LVD1_IRQHandler
        B LVD1_IRQHandler

        PUBWEAK LVD2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LVD2_IRQHandler
        B LVD2_IRQHandler

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
        B EXTI4_IRQHandler

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

        PUBWEAK ADC0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC0_IRQHandler
        B ADC0_IRQHandler

        PUBWEAK CAN_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN_TX_IRQHandler
        B CAN_TX_IRQHandler

        PUBWEAK CAN_RX0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN_RX0_IRQHandler
        B CAN_RX0_IRQHandler

        PUBWEAK CAN_RX1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN_RX1_IRQHandler
        B CAN_RX1_IRQHandler

        PUBWEAK CAN_EWMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN_EWMC_IRQHandler
        B CAN_EWMC_IRQHandler

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

        PUBWEAK TIMER0_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_TRG_CMT_IRQHandler
        B TIMER0_TRG_CMT_IRQHandler

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

        PUBWEAK GPTIMER0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPTIMER0_IRQHandler
        B GPTIMER0_IRQHandler

        PUBWEAK I2C_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C_EV_IRQHandler
        B I2C_EV_IRQHandler

        PUBWEAK I2C_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C_ER_IRQHandler
        B I2C_ER_IRQHandler

        PUBWEAK SPI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI_IRQHandler
        B SPI_IRQHandler

        PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART0_IRQHandler
        B UART0_IRQHandler

        PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART1_IRQHandler
        B UART1_IRQHandler

        PUBWEAK EXTI10_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI10_15_IRQHandler
        B EXTI10_15_IRQHandler

        PUBWEAK TIMER7_BRK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_BRK_IRQHandler
        B TIMER7_BRK_IRQHandler

        PUBWEAK TIMER7_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_UP_IRQHandler
        B TIMER7_UP_IRQHandler

        PUBWEAK TIMER7_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_TRG_CMT_IRQHandler
        B TIMER7_TRG_CMT_IRQHandler

        PUBWEAK TIMER7_Channel_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_Channel_IRQHandler
        B TIMER7_Channel_IRQHandler

        PUBWEAK TMU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMU_IRQHandler
        B TMU_IRQHandler

        PUBWEAK GPTIMER1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPTIMER1_IRQHandler
        B GPTIMER1_IRQHandler

        PUBWEAK UART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART2_IRQHandler
        B UART2_IRQHandler

        PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART3_IRQHandler
        B UART3_IRQHandler

        PUBWEAK CPTIMER0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CPTIMER0_IRQHandler
        B CPTIMER0_IRQHandler

        PUBWEAK CPTIMER1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CPTIMER1_IRQHandler
        B CPTIMER1_IRQHandler

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

        PUBWEAK DMAMUX_OVERRUN_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMAMUX_OVERRUN_IRQHandler
        B DMAMUX_OVERRUN_IRQHandler

        PUBWEAK CPTIMERW_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CPTIMERW_IRQHandler
        B CPTIMERW_IRQHandler

        PUBWEAK CFMU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CFMU_IRQHandler
        B CFMU_IRQHandler

        PUBWEAK I2C_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C_WKUP_IRQHandler
        B I2C_WKUP_IRQHandler

        PUBWEAK FWDGT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FWDGT_IRQHandler
        B FWDGT_IRQHandler

        PUBWEAK CMP0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP0_IRQHandler
        B CMP0_IRQHandler

        PUBWEAK CMP1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP1_IRQHandler
        B CMP1_IRQHandler

        PUBWEAK CMP2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP2_IRQHandler
        B CMP2_IRQHandler

        PUBWEAK CMP3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP3_IRQHandler
        B CMP3_IRQHandler

        PUBWEAK ADC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC2_IRQHandler
        B ADC2_IRQHandler

        PUBWEAK POC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
POC_IRQHandler
        B POC_IRQHandler

        PUBWEAK GTOC0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GTOC0_IRQHandler
        B GTOC0_IRQHandler

        PUBWEAK GTOC1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GTOC1_IRQHandler
        B GTOC1_IRQHandler

        PUBWEAK GTOC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GTOC2_IRQHandler
        B GTOC2_IRQHandler

        PUBWEAK GTOC3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GTOC3_IRQHandler
        B GTOC3_IRQHandler

        PUBWEAK CMP0_EXTI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP0_EXTI_IRQHandler
        B CMP0_EXTI_IRQHandler

        PUBWEAK CMP1_EXTI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP1_EXTI_IRQHandler
        B CMP1_EXTI_IRQHandler

        PUBWEAK CMP2_EXTI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP2_EXTI_IRQHandler
        B CMP2_EXTI_IRQHandler

        PUBWEAK CMP3_EXTI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP3_EXTI_IRQHandler
        B CMP3_EXTI_IRQHandler

        PUBWEAK SRAMC_ECC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SRAMC_ECC_IRQHandler
        B SRAMC_ECC_IRQHandler

        END
