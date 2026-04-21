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

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000800

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000400

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

;               /* reset Vector Mapped to at Address 0 */
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                      ; Top of Stack
                DCD     Reset_Handler                     ; Reset Handler
                DCD     NMI_Handler                       ; NMI Handler
                DCD     HardFault_Handler                 ; Hard Fault Handler
                DCD     MemManage_Handler                 ; MPU Fault Handler
                DCD     BusFault_Handler                  ; Bus Fault Handler
                DCD     UsageFault_Handler                ; Usage Fault Handler
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     SVC_Handler                       ; SVCall Handler
                DCD     DebugMon_Handler                  ; Debug Monitor Handler
                DCD     0                                 ; Reserved
                DCD     PendSV_Handler                    ; PendSV Handler
                DCD     SysTick_Handler                   ; SysTick Handler

;               /* external interrupts handler */
                DCD     WWDGT_IRQHandler                  ; 16:Window Watchdog Timer
                DCD     LVD1_IRQHandler                   ; 17:LVD1 through EXTI Line 16 Detect
                DCD     LVD2_IRQHandler                   ; 18:LVD2 through EXTI Line 17 Detect
                DCD     0                                 ; 19:Reserved
                DCD     FMC_IRQHandler                    ; 20:FMC
                DCD     RCU_IRQHandler                    ; 21:RCU
                DCD     EXTI0_IRQHandler                  ; 22:EXTI Line 0
                DCD     EXTI1_IRQHandler                  ; 23:EXTI Line 1
                DCD     EXTI2_IRQHandler                  ; 24:EXTI Line 2
                DCD     EXTI3_IRQHandler                  ; 25:EXTI Line 3
                DCD     EXTI4_IRQHandler                  ; 26:EXTI Line 4
                DCD     DMA0_Channel0_IRQHandler          ; 27:DMA0 Channel0
                DCD     DMA0_Channel1_IRQHandler          ; 28:DMA0 Channel1
                DCD     DMA0_Channel2_IRQHandler          ; 29:DMA0 Channel2
                DCD     DMA0_Channel3_IRQHandler          ; 30:DMA0 Channel3
                DCD     DMA0_Channel4_IRQHandler          ; 31:DMA0 Channel4
                DCD     DMA0_Channel5_IRQHandler          ; 32:DMA0 Channel5
                DCD     0                                 ; 33:Reserved
                DCD     ADC0_IRQHandler                   ; 34:ADC0
                DCD     CAN_TX_IRQHandler                 ; 35:CAN TX
                DCD     CAN_RX0_IRQHandler                ; 36:CAN RX0
                DCD     CAN_RX1_IRQHandler                ; 37:CAN RX1
                DCD     CAN_EWMC_IRQHandler               ; 38:CAN EWMC
                DCD     EXTI5_9_IRQHandler                ; 39:EXTI Line 5 to EXTI Line 9
                DCD     TIMER0_BRK_IRQHandler             ; 40:TIMER0 Break
                DCD     TIMER0_UP_IRQHandler              ; 41:TIMER0 Update
                DCD     TIMER0_TRG_CMT_IRQHandler         ; 42:TIMER0 Trigger and Commutation
                DCD     TIMER0_Channel_IRQHandler         ; 43:TIMER0 Channel Capture Compare
                DCD     TIMER1_IRQHandler                 ; 44:TIMER1
                DCD     TIMER2_IRQHandler                 ; 45:TIMER2
                DCD     GPTIMER0_IRQHandler               ; 46:GPTIMER0
                DCD     I2C_EV_IRQHandler                 ; 47:I2C Event
                DCD     I2C_ER_IRQHandler                 ; 48:I2C Error
                DCD     0                                 ; 49:Reserved
                DCD     0                                 ; 50:Reserved
                DCD     SPI_IRQHandler                    ; 51:SPI
                DCD     0                                 ; 52:Reserved
                DCD     UART0_IRQHandler                  ; 53:UART0
                DCD     UART1_IRQHandler                  ; 54:UART1
                DCD     0                                 ; 55:Reserved
                DCD     EXTI10_15_IRQHandler              ; 56:EXTI Line 10 to EXTI Line 15
                DCD     0                                 ; 57:Reserved
                DCD     0                                 ; 58:Reserved
                DCD     TIMER7_BRK_IRQHandler             ; 59:TIMER7 Break
                DCD     TIMER7_UP_IRQHandler              ; 60:TIMER7 Update
                DCD     TIMER7_TRG_CMT_IRQHandler         ; 61:TIMER7 Trigger and Commutation
                DCD     TIMER7_Channel_IRQHandler         ; 62:TIMER7 Channel Capture Compare
                DCD     TMU_IRQHandler                    ; 63:TMU
                DCD     0                                 ; 64:Reserved
                DCD     0                                 ; 65:Reserved
                DCD     GPTIMER1_IRQHandler               ; 66:GPTIMER1
                DCD     0                                 ; 67:Reserved
                DCD     UART2_IRQHandler                  ; 68:UART2
                DCD     UART3_IRQHandler                  ; 69:UART3
                DCD     CPTIMER0_IRQHandler               ; 70:CPTIMER0
                DCD     CPTIMER1_IRQHandler               ; 71:CPTIMER1
                DCD     DMA1_Channel0_IRQHandler          ; 72:DMA1 Channel0
                DCD     DMA1_Channel1_IRQHandler          ; 73:DMA1 Channel1
                DCD     DMA1_Channel2_IRQHandler          ; 74:DMA1 Channel2
                DCD     DMA1_Channel3_IRQHandler          ; 75:DMA1 Channel3
                DCD     DMA1_Channel4_IRQHandler          ; 76:DMA1 Channel4
                DCD     DMA1_Channel5_IRQHandler          ; 77:DMA1 Channel5
                DCD     DMAMUX_OVERRUN_IRQHandler         ; 78:DMAMUX Overrun
                DCD     CPTIMERW_IRQHandler               ; 79:CPTIMERW
                DCD     0                                 ; 80:Reserved
                DCD     CFMU_IRQHandler                   ; 81:CFMU
                DCD     I2C_WKUP_IRQHandler               ; 82:I2C Wakeup through EXTI Line 23 Detect
                DCD     FWDGT_IRQHandler                  ; 83:FWDGT through EXTI Line 22 Detect
                DCD     0                                 ; 84:Reserved
                DCD     0                                 ; 85:Reserved
                DCD     CMP0_IRQHandler                   ; 86:CMP0
                DCD     CMP1_IRQHandler                   ; 87:CMP1
                DCD     CMP2_IRQHandler                   ; 88:CMP2
                DCD     CMP3_IRQHandler                   ; 89:CMP3
                DCD     0                                 ; 90:Reserved
                DCD     ADC2_IRQHandler                   ; 91:ADC2
                DCD     0                                 ; 92:Reserved
                DCD     POC_IRQHandler                    ; 93:POC
                DCD     0                                 ; 94:Reserved
                DCD     GTOC0_IRQHandler                  ; 95:GTOC0
                DCD     GTOC1_IRQHandler                  ; 96:GTOC1
                DCD     GTOC2_IRQHandler                  ; 97:GTOC2
                DCD     GTOC3_IRQHandler                  ; 98:GTOC3
                DCD     0                                 ; 99:Reserved
                DCD     0                                 ; 100:Reserved
                DCD     CMP0_EXTI_IRQHandler              ; 101:CMP0 through EXTI Line 18 Detect
                DCD     CMP1_EXTI_IRQHandler              ; 102:CMP1 through EXTI Line 19 Detect
                DCD     CMP2_EXTI_IRQHandler              ; 103:CMP2 through EXTI Line 20 Detect
                DCD     CMP3_EXTI_IRQHandler              ; 104:CMP3 through EXTI Line 21 Detect
                DCD     0                                 ; 105:Reserved
                DCD     0                                 ; 106:Reserved
                DCD     0                                 ; 107:Reserved
                DCD     SRAMC_ECC_IRQHandler              ; 108:SRAMC ECC
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

;/* reset Handler */
Reset_Handler   PROC
                EXPORT  Reset_Handler                     [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                IMPORT |Image$$RW_IRAM1$$RW$$Base|

                LDR     R0, =|Image$$RW_IRAM1$$RW$$Base|
                ADD     R1, R0, #0x2000
                MOVS    R2, #0x0
MEM_INIT        STR     R2, [R0,#0]
                ADD     R0, R0, #0x4
                CMP     R0, R1
                BNE     MEM_INIT

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

;/* dummy Exception Handlers */
NMI_Handler\
                PROC
                EXPORT  NMI_Handler                             [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler                       [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler                       [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler                        [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler                      [WEAK]
                B       .
                ENDP
SVC_Handler\
                PROC
                EXPORT  SVC_Handler                             [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler                        [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler                          [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler                         [WEAK]
                B       .
                ENDP

Default_Handler PROC
;               /* external interrupts handler */
                EXPORT  WWDGT_IRQHandler                        [WEAK]
                EXPORT  LVD1_IRQHandler                         [WEAK]
                EXPORT  LVD2_IRQHandler                         [WEAK]
                EXPORT  FMC_IRQHandler                          [WEAK]
                EXPORT  RCU_IRQHandler                          [WEAK]
                EXPORT  EXTI0_IRQHandler                        [WEAK]
                EXPORT  EXTI1_IRQHandler                        [WEAK]
                EXPORT  EXTI2_IRQHandler                        [WEAK]
                EXPORT  EXTI3_IRQHandler                        [WEAK]
                EXPORT  EXTI4_IRQHandler                        [WEAK]
                EXPORT  DMA0_Channel0_IRQHandler                [WEAK]
                EXPORT  DMA0_Channel1_IRQHandler                [WEAK]
                EXPORT  DMA0_Channel2_IRQHandler                [WEAK]
                EXPORT  DMA0_Channel3_IRQHandler                [WEAK]
                EXPORT  DMA0_Channel4_IRQHandler                [WEAK]
                EXPORT  DMA0_Channel5_IRQHandler                [WEAK]
                EXPORT  ADC0_IRQHandler                         [WEAK]
                EXPORT  CAN_TX_IRQHandler                       [WEAK]
                EXPORT  CAN_RX0_IRQHandler                      [WEAK]
                EXPORT  CAN_RX1_IRQHandler                      [WEAK]
                EXPORT  CAN_EWMC_IRQHandler                     [WEAK]
                EXPORT  EXTI5_9_IRQHandler                      [WEAK]
                EXPORT  TIMER0_BRK_IRQHandler                   [WEAK]
                EXPORT  TIMER0_UP_IRQHandler                    [WEAK]
                EXPORT  TIMER0_TRG_CMT_IRQHandler               [WEAK]
                EXPORT  TIMER0_Channel_IRQHandler               [WEAK]
                EXPORT  TIMER1_IRQHandler                       [WEAK]
                EXPORT  TIMER2_IRQHandler                       [WEAK]
                EXPORT  GPTIMER0_IRQHandler                     [WEAK]
                EXPORT  I2C_EV_IRQHandler                       [WEAK]
                EXPORT  I2C_ER_IRQHandler                       [WEAK]
                EXPORT  SPI_IRQHandler                          [WEAK]
                EXPORT  UART0_IRQHandler                        [WEAK]
                EXPORT  UART1_IRQHandler                        [WEAK]
                EXPORT  EXTI10_15_IRQHandler                    [WEAK]
                EXPORT  TIMER7_BRK_IRQHandler                   [WEAK]
                EXPORT  TIMER7_UP_IRQHandler                    [WEAK]
                EXPORT  TIMER7_TRG_CMT_IRQHandler               [WEAK]
                EXPORT  TIMER7_Channel_IRQHandler               [WEAK]
                EXPORT  TMU_IRQHandler                          [WEAK]
                EXPORT  GPTIMER1_IRQHandler                     [WEAK]
                EXPORT  UART2_IRQHandler                        [WEAK]
                EXPORT  UART3_IRQHandler                        [WEAK]
                EXPORT  CPTIMER0_IRQHandler                     [WEAK]
                EXPORT  CPTIMER1_IRQHandler                     [WEAK]
                EXPORT  DMA1_Channel0_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler                [WEAK]
                EXPORT  DMAMUX_OVERRUN_IRQHandler               [WEAK]
                EXPORT  CPTIMERW_IRQHandler                     [WEAK]
                EXPORT  CFMU_IRQHandler                         [WEAK]
                EXPORT  I2C_WKUP_IRQHandler                     [WEAK]
                EXPORT  FWDGT_IRQHandler                        [WEAK]
                EXPORT  CMP0_IRQHandler                         [WEAK]
                EXPORT  CMP1_IRQHandler                         [WEAK]
                EXPORT  CMP2_IRQHandler                         [WEAK]
                EXPORT  CMP3_IRQHandler                         [WEAK]
                EXPORT  ADC2_IRQHandler                         [WEAK]
                EXPORT  POC_IRQHandler                          [WEAK]
                EXPORT  GTOC0_IRQHandler                        [WEAK]
                EXPORT  GTOC1_IRQHandler                        [WEAK]
                EXPORT  GTOC2_IRQHandler                        [WEAK]
                EXPORT  GTOC3_IRQHandler                        [WEAK]
                EXPORT  CMP0_EXTI_IRQHandler                    [WEAK]
                EXPORT  CMP1_EXTI_IRQHandler                    [WEAK]
                EXPORT  CMP2_EXTI_IRQHandler                    [WEAK]
                EXPORT  CMP3_EXTI_IRQHandler                    [WEAK]
                EXPORT  SRAMC_ECC_IRQHandler                    [WEAK]

;/* external interrupts handler */
WWDGT_IRQHandler
LVD1_IRQHandler
LVD2_IRQHandler
FMC_IRQHandler
RCU_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA0_Channel0_IRQHandler
DMA0_Channel1_IRQHandler
DMA0_Channel2_IRQHandler
DMA0_Channel3_IRQHandler
DMA0_Channel4_IRQHandler
DMA0_Channel5_IRQHandler
ADC0_IRQHandler
CAN_TX_IRQHandler
CAN_RX0_IRQHandler
CAN_RX1_IRQHandler
CAN_EWMC_IRQHandler
EXTI5_9_IRQHandler
TIMER0_BRK_IRQHandler
TIMER0_UP_IRQHandler
TIMER0_TRG_CMT_IRQHandler
TIMER0_Channel_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
GPTIMER0_IRQHandler
I2C_EV_IRQHandler
I2C_ER_IRQHandler
SPI_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
EXTI10_15_IRQHandler
TIMER7_BRK_IRQHandler
TIMER7_UP_IRQHandler
TIMER7_TRG_CMT_IRQHandler
TIMER7_Channel_IRQHandler
TMU_IRQHandler
GPTIMER1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
CPTIMER0_IRQHandler
CPTIMER1_IRQHandler
DMA1_Channel0_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMAMUX_OVERRUN_IRQHandler
CPTIMERW_IRQHandler
CFMU_IRQHandler
I2C_WKUP_IRQHandler
FWDGT_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
CMP2_IRQHandler
CMP3_IRQHandler
ADC2_IRQHandler
POC_IRQHandler
GTOC0_IRQHandler
GTOC1_IRQHandler
GTOC2_IRQHandler
GTOC3_IRQHandler
CMP0_EXTI_IRQHandler
CMP1_EXTI_IRQHandler
CMP2_EXTI_IRQHandler
CMP3_EXTI_IRQHandler
SRAMC_ECC_IRQHandler

                B       .
                ENDP

                ALIGN

; user Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF

                END
