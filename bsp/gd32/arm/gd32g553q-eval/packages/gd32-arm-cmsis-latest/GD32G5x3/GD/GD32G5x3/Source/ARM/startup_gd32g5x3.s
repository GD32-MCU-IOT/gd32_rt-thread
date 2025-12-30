;/*!
;    \file    startup_gd32g5x3.s
;    \brief   start up file
;
;    \version 2025-02-10, V1.1.0, firmware for GD32G5x3
;*/
;
;/*
; * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
; * Copyright (c) 2025, GigaDevice Semiconductor Inc.
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

Stack_Size      EQU     0x00000400

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

__Vectors       DCD     __initial_sp                                 ; Top of Stack
                DCD     Reset_Handler                                ; Reset Handler
                DCD     NMI_Handler                                  ; NMI Handler
                DCD     HardFault_Handler                            ; Hard Fault Handler
                DCD     MemManage_Handler                            ; MPU Fault Handler
                DCD     BusFault_Handler                             ; Bus Fault Handler
                DCD     UsageFault_Handler                           ; Usage Fault Handler
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     SVC_Handler                                  ; SVCall Handler
                DCD     DebugMon_Handler                             ; Debug Monitor Handler
                DCD     0                                            ; Reserved
                DCD     PendSV_Handler                               ; PendSV Handler
                DCD     SysTick_Handler                              ; SysTick Handler

;               /* external interrupts handler */
                DCD     WWDGT_IRQHandler                             ; 16:window watchdog timer
                DCD     LVD_VAVD_VOVD_VUVD_IRQHandler                ; 17:LVD/VAVD/VOVD/VUVD through EXTI line detect
                DCD     TAMPER_IRQHandler                            ; 18:RTC Tamper and TimeStamp from EXTI interrupt, LXTAL clock stuck interrupt
                DCD     RTC_WKUP_IRQHandler                          ; 19:RTC wakeup from EXTI interrupt
                DCD     FMC_IRQHandler                               ; 20:FMC global interrupt
                DCD     RCU_IRQHandler                               ; 21:RCU global interrupt
                DCD     EXTI0_IRQHandler                             ; 22:EXTI line 0 interrupt
                DCD     EXTI1_IRQHandler                             ; 23:EXTI line 1 interrupt
                DCD     EXTI2_IRQHandler                             ; 24:EXTI line 2 interrupt
                DCD     EXTI3_IRQHandler                             ; 25:EXTI line 3 interrupt
                DCD     EXTI4_IRQHandler                             ; 26:EXTI line 4 interrupt
                DCD     DMA0_Channel0_IRQHandler                     ; 27:DMA0 channel 0 global interrupt
                DCD     DMA0_Channel1_IRQHandler                     ; 28:DMA0 channel 1 global interrupt
                DCD     DMA0_Channel2_IRQHandler                     ; 29:DMA0 channel 2 global interrupt
                DCD     DMA0_Channel3_IRQHandler                     ; 30:DMA0 channel 3 global interrupt
                DCD     DMA0_Channel4_IRQHandler                     ; 31:DMA0 channel 4 global interrupt
                DCD     DMA0_Channel5_IRQHandler                     ; 32:DMA0 channel 5 global interrupt
                DCD     DMA0_Channel6_IRQHandler                     ; 33:DMA0 channel 6 global interrupt
                DCD     ADC0_1_IRQHandler                            ; 34:ADC0 and ADC1 global interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     EXTI5_9_IRQHandler                           ; 39:EXTI line5-9 interrupt
                DCD     TIMER0_BRK_IRQHandler                        ; 40:TIMER0 break interrupt
                DCD     TIMER0_UP_IRQHandler                         ; 41:TIMER0 update interrupt
                DCD     TIMER0_TRG_CMT_IDX_IRQHandler                ; 42:TIMER0 trigger and commutation interrupt/TIMER0 direction change interrupt/TIMER0 index
                DCD     TIMER0_Channel_IRQHandler                    ; 43:TIMER0 capture compare interrupt
                DCD     TIMER1_IRQHandler                            ; 44:TIMER1 global interrupt
                DCD     TIMER2_IRQHandler                            ; 45:TIMER2 global interrupt
                DCD     TIMER3_IRQHandler                            ; 46:TIMER3 global interrupt
                DCD     I2C0_EV_WKUP_IRQHandler                      ; 47:I2C0 event interrupt and wakeup through EXTI interrupt
                DCD     I2C0_ER_IRQHandler                           ; 48:I2C0 error interrupt
                DCD     I2C1_EV_WKUP_IRQHandler                      ; 49:I2C1 event interrupt and wakeup through EXTI interrupt
                DCD     I2C1_ER_IRQHandler                           ; 50:I2C1 error interrupt
                DCD     SPI0_IRQHandler                              ; 51:SPI0 global interrupt
                DCD     SPI1_IRQHandler                              ; 52:SPI1 global interrupt
                DCD     USART0_IRQHandler                            ; 53:USART0 global interrupt and wakeup through EXTI line28 interrupt
                DCD     USART1_IRQHandler                            ; 54:USART1 global interrupt and wakeup through EXTI line29 interrupt
                DCD     USART2_IRQHandler                            ; 55:USART2 global interrupt and wakeup through EXTI line30 interrupt
                DCD     EXTI10_15_IRQHandler                         ; 56:EXTI line10-15 interrupt
                DCD     RTC_Alarm_IRQHandler                         ; 57:RTC alarm from EXTI line17 interrupt
                DCD     0                                            ; Reserved
                DCD     TIMER7_BRK_TRS_IDX_IRQHandler                ; 59:TIMER7 break interrupt/ transition error/ index error
                DCD     TIMER7_UP_IRQHandler                         ; 60:TIMER7 update interrupt
                DCD     TIMER7_TRG_CMT_IDX_IRQHandler                ; 61:TIMER7 trigger and commutation interrupt/direction change interrupt/index
                DCD     TIMER7_Channel_IRQHandler                    ; 62:TIMER7 capture compare interrupt
                DCD     ADC2_IRQHandler                              ; 63:ADC2 global interrupt
                DCD     SYSCFG_IRQHandler                            ; 64:SYSCFG interrupt
                DCD     LPTIMER_IRQHandler                           ; 65:LPTIMER global interrupt
                DCD     TIMER4_IRQHandler                            ; 66:TIMER4 global interrupt
                DCD     SPI2_IRQHandler                              ; 67:SPI2 global interrupt
                DCD     UART3_IRQHandler                             ; 68:UART3 global interrupt
                DCD     UART4_IRQHandler                             ; 69:UART4 global interrupt
                DCD     TIMER5_DAC0_2_UDR_IRQHandler                 ; 70:TIMER5 global interrupt and DAC2 / DAC0 underrun error interrupt
                DCD     TIMER6_DAC1_3_UDR_IRQHandler                 ; 71:TIMER6 global interrupt and DAC3 / DAC1 underrun error interrupt
                DCD     DMA1_Channel0_IRQHandler                     ; 72:DMA1 channel0 global interrupt
                DCD     DMA1_Channel1_IRQHandler                     ; 73:DMA1 channel1 global interrupt
                DCD     DMA1_Channel2_IRQHandler                     ; 74:DMA1 channel2 global interrupt
                DCD     DMA1_Channel3_IRQHandler                     ; 75:DMA1 channel3 global interrupt
                DCD     DMA1_Channel4_IRQHandler                     ; 76:DMA1 channel4 global interrupt
                DCD     ADC3_IRQHandler                              ; 77:ADC3 global interrupt
                DCD     0                                            ; Reserved
                DCD     VUVD1_VOVD1_IRQHandler                       ; 79:VUVD1 / VOVD1 interrupt
                DCD     CMP0_3_IRQHandler                            ; 80:CMP0 / CMP1 / CMP2 / CMP3 through EXTI lines 20 / 21 / 22 / 23 interrupts
                DCD     CMP4_7_IRQHandler                            ; 81:CMP4 / CMP5 / CMP6 / CMP7 through EXTI lines 24 / 36 / 37 / 38 interrupts
                DCD     CMP_IRQHandler                               ; 82:CMP global interrupt
                DCD     HRTIMER_IRQ0_IRQHandler                      ; 83:HRTIMER interrupt0
                DCD     HRTIMER_IRQ1_IRQHandler                      ; 84:HRTIMER interrupt1
                DCD     HRTIMER_IRQ2_IRQHandler                      ; 85:HRTIMER interrupt2
                DCD     HRTIMER_IRQ3_IRQHandler                      ; 86:HRTIMER interrupt3
                DCD     HRTIMER_IRQ4_IRQHandler                      ; 87:HRTIMER interrupt4
                DCD     HRTIMER_IRQ5_IRQHandler                      ; 88:HRTIMER interrupt5
                DCD     HRTIMER_IRQ6_IRQHandler                      ; 89:HRTIMER interrupt6
                DCD     HRTIMER_IRQ7_IRQHandler                      ; 90:HRTIMER interrupt7
                DCD     HRTIMER_IRQ8_IRQHandler                      ; 91:HRTIMER interrupt8
                DCD     HRTIMER_IRQ9_IRQHandler                      ; 92:HRTIMER interrupt9
                DCD     TIMER19_BRK_TRS_IDX_IRQHandler               ; 93:TIMER19 break interrupt / TIMER19 transition error / TIMER19 Index error
                DCD     TIMER19_UP_IRQHandler                        ; 94:TIMER19 update interrupt
                DCD     TIMER19_TRG_CMT_IDX_IRQHandler               ; 95:TIMER19 trigger and commutation interrupt / TIMER19 direction change interrupt / TIMER19 index
                DCD     TIMER19_Channel_IRQHandler                   ; 96:TIMER19 capture compare interrupt 
                DCD     FPU_IRQHandler                               ; 97:FPU global interrupt
                DCD     I2C2_EV_WKUP_IRQHandler                      ; 98:I2C2 event interrupt and I2C2 wakeup through EXTI interrupt
                DCD     I2C2_ER_IRQHandler                           ; 99:I2C2 error interrupt
                DCD     0                                            ; Reserved
                DCD     CAU_IRQHandler                               ; 101:CAU global interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     TRNG_IRQHandler                              ; 106:TRNG global interrupt
                DCD     0                                            ; Reserved
                DCD     I2C3_EV_WKUP_IRQHandler                      ; 108:I2C3 event interrupt and I2C3 wakeup through EXTI line34 interrupt
                DCD     I2C3_ER_IRQHandler                           ; 109:I2C3 error interrupt
                DCD     DMAMUX_OVR_IRQHandler                        ; 110:DMAMUX overrun interrupt  
                DCD     QSPI_IRQHandler                              ; 111:QSPI global interrupt
                DCD     FFT_IRQHandler                               ; 112:FFT global interrupt
                DCD     DMA1_Channel5_IRQHandler                     ; 113:DMA1 channel5 global interrupt
                DCD     DMA1_Channel6_IRQHandler                     ; 114:DMA1 channel6 global interrupt
                DCD     CLA_IRQHandler                               ; 115:CLA interrupt
                DCD     TMU_IRQHandler                               ; 116:TMU interrupt
                DCD     FAC_IRQHandler                               ; 117:FAC interrupt
                DCD     HPDF_INT0_IRQHandler                         ; 118:HPDF global interrupt 0
                DCD     HPDF_INT1_IRQHandler                         ; 119:HPDF global interrupt 1
                DCD     HPDF_INT2_IRQHandler                         ; 120:HPDF global interrupt 2
                DCD     HPDF_INT3_IRQHandler                         ; 121:HPDF global interrupt 3
                DCD     TIMER14_IRQHandler                           ; 122:TIMER14 global interrupt
                DCD     TIMER15_IRQHandler                           ; 123:TIMER15 global interrupt
                DCD     TIMER16_IRQHandler                           ; 124:TIMER16 global interrupt
                DCD     CAN0_WKUP_IRQHandler                         ; 125:CAN0 wakeup through EXTI line25 interrupt
                DCD     CAN0_Message_IRQHandler                      ; 126:CAN0 interrupt for message buffer
                DCD     CAN0_Busoff_IRQHandler                       ; 127:CAN0 interrupt for bus off / bus off done
                DCD     CAN0_Error_IRQHandler                        ; 128:CAN0 interrupt for error
                DCD     CAN0_FastError_IRQHandler                    ; 129:CAN0 interrupt for error in fast transmission
                DCD     CAN0_TEC_IRQHandler                          ; 130:CAN0 interrupt for transmit warning
                DCD     CAN0_REC_IRQHandler                          ; 131:CAN0 interrupt for receive warning
                DCD     CAN1_WKUP_IRQHandler                         ; 132:CAN1 wakeup through EXTI line26 interrupt
                DCD     CAN1_Message_IRQHandler                      ; 133:CAN1 interrupt for message buffer
                DCD     CAN1_Busoff_IRQHandler                       ; 134:CAN1 interrupt for bus off / Bus off done
                DCD     CAN1_Error_IRQHandler                        ; 135:CAN1 interrupt for error
                DCD     CAN1_FastError_IRQHandler                    ; 136:CAN1 interrupt for error in fast transmission
                DCD     CAN1_TEC_IRQHandler                          ; 137:CAN1 interrupt for transmit warning
                DCD     CAN1_REC_IRQHandler                          ; 138:CAN1 interrupt for receive warning
                DCD     CAN2_WKUP_IRQHandler                         ; 139:CAN2 wakeup through EXTI line27 interrupt
                DCD     CAN2_Message_IRQHandler                      ; 140:CAN2 interrupt for message buffer
                DCD     CAN2_Busoff_IRQHandler                       ; 141:CAN2 interrupt for bus off / Bus off done
                DCD     CAN2_Error_IRQHandler                        ; 142:CAN2 interrupt for error
                DCD     CAN2_FastError_IRQHandler                    ; 143:CAN2 interrupt for error in fast transmission
                DCD     CAN2_TEC_IRQHandler                          ; 144:CAN2 interrupt for transmit warning
                DCD     CAN2_REC_IRQHandler                          ; 145:CAN2 interrupt for receive warning
                DCD     TIMER0_DEC_IRQHandler                        ; 146:TIMER0 DEC interrupt
                DCD     TIMER1_DEC_IRQHandler                        ; 147:TIMER1 DEC interrupt
                DCD     TIMER2_DEC_IRQHandler                        ; 148:TIMER2 DEC interrupt
                DCD     TIMER3_DEC_IRQHandler                        ; 149:TIMER3 DEC interrupt
                DCD     TIMER4_DEC_IRQHandler                        ; 150:TIMER4 DEC interrupt
                DCD     TIMER7_DEC_IRQHandler                        ; 151:TIMER7 DEC interrupt
                DCD     TIMER19_DEC_IRQHandler                       ; 152:TIMER19 DEC interrupt

__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY
                    
                

;/* reset Handler */
Reset_Handler   PROC
                EXPORT  Reset_Handler                     [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                IMPORT |Image$$RW_IRAM1$$RW$$Base|

                LDR     r0, =0x1FFFB3E0
                LDR     r2, [r0]
                LDR     r0, = 0xFFFF0000
                AND     r2, r2, r0
                LSR     r2, r2, #16
                LSL     r2, r2, #10
                LDR     r0, =|Image$$RW_IRAM1$$RW$$Base|
                ADD     r1, r0, r2
                LDR     r2, =0x0
;MEM_INIT        STRD    r2, r2, [ r0 ] , #8
;               CMP     r0, r1
;               BNE     MEM_INIT

                LDR     r0, =SystemInit
                BLX     r0
                LDR     r0, =__main
                BX      r0
                ENDP

;/* dummy Exception Handlers */
NMI_Handler\
                PROC
                EXPORT  NMI_Handler                       [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler                 [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler                 [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler                  [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler                [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                       [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler                  [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                    [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                   [WEAK]
                B       .
                ENDP

Default_Handler PROC
;               /* external interrupts handler */
                EXPORT  WWDGT_IRQHandler                  [WEAK]
                EXPORT  LVD_VAVD_VOVD_VUVD_IRQHandler        [WEAK]
                EXPORT  TAMPER_IRQHandler                 [WEAK]
                EXPORT  RTC_WKUP_IRQHandler               [WEAK]
                EXPORT  FMC_IRQHandler                    [WEAK]
                EXPORT  RCU_IRQHandler                    [WEAK]
                EXPORT  EXTI0_IRQHandler                  [WEAK]
                EXPORT  EXTI1_IRQHandler                  [WEAK]
                EXPORT  EXTI2_IRQHandler                  [WEAK]
                EXPORT  EXTI3_IRQHandler                  [WEAK]
                EXPORT  EXTI4_IRQHandler                  [WEAK]
                EXPORT  DMA0_Channel0_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel1_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel2_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel3_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel4_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel5_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel6_IRQHandler          [WEAK]
                EXPORT  ADC0_1_IRQHandler                 [WEAK]
                EXPORT  EXTI5_9_IRQHandler                [WEAK]
                EXPORT  TIMER0_BRK_IRQHandler             [WEAK]
                EXPORT  TIMER0_UP_IRQHandler              [WEAK]
                EXPORT  TIMER0_TRG_CMT_IDX_IRQHandler     [WEAK]
                EXPORT  TIMER0_Channel_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler                 [WEAK]
                EXPORT  TIMER2_IRQHandler                 [WEAK]
                EXPORT  TIMER3_IRQHandler                 [WEAK]
                EXPORT  I2C0_EV_WKUP_IRQHandler           [WEAK]
                EXPORT  I2C0_ER_IRQHandler                [WEAK]
                EXPORT  I2C1_EV_WKUP_IRQHandler           [WEAK]
                EXPORT  I2C1_ER_IRQHandler                [WEAK]
                EXPORT  SPI0_IRQHandler                   [WEAK]
                EXPORT  SPI1_IRQHandler                   [WEAK]
                EXPORT  USART0_IRQHandler                 [WEAK]
                EXPORT  USART1_IRQHandler                 [WEAK]
                EXPORT  USART2_IRQHandler                 [WEAK]
                EXPORT  EXTI10_15_IRQHandler              [WEAK]
                EXPORT  RTC_Alarm_IRQHandler              [WEAK]
                EXPORT  TIMER7_BRK_TRS_IDX_IRQHandler     [WEAK]
                EXPORT  TIMER7_UP_IRQHandler              [WEAK]
                EXPORT  TIMER7_TRG_CMT_IDX_IRQHandler     [WEAK]
                EXPORT  TIMER7_Channel_IRQHandler         [WEAK]
                EXPORT  ADC2_IRQHandler                   [WEAK]
                EXPORT  SYSCFG_IRQHandler                 [WEAK]
                EXPORT  LPTIMER_IRQHandler                [WEAK]
                EXPORT  TIMER4_IRQHandler                 [WEAK]
                EXPORT  SPI2_IRQHandler                   [WEAK]
                EXPORT  UART3_IRQHandler                  [WEAK]
                EXPORT  UART4_IRQHandler                  [WEAK]
                EXPORT  TIMER5_DAC0_2_UDR_IRQHandler      [WEAK]
                EXPORT  TIMER6_DAC1_3_UDR_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel0_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler          [WEAK]
                EXPORT  ADC3_IRQHandler                   [WEAK]
                EXPORT  VUVD1_VOVD1_IRQHandler            [WEAK]
                EXPORT  CMP0_3_IRQHandler                 [WEAK]
                EXPORT  CMP4_7_IRQHandler                 [WEAK]
                EXPORT  CMP_IRQHandler                    [WEAK]
                EXPORT  HRTIMER_IRQ0_IRQHandler           [WEAK]
                EXPORT  HRTIMER_IRQ1_IRQHandler           [WEAK]
                EXPORT  HRTIMER_IRQ2_IRQHandler           [WEAK]
                EXPORT  HRTIMER_IRQ3_IRQHandler           [WEAK]
                EXPORT  HRTIMER_IRQ4_IRQHandler           [WEAK]
                EXPORT  HRTIMER_IRQ5_IRQHandler           [WEAK]
                EXPORT  HRTIMER_IRQ6_IRQHandler           [WEAK]
                EXPORT  HRTIMER_IRQ7_IRQHandler           [WEAK]
                EXPORT  HRTIMER_IRQ8_IRQHandler           [WEAK]
                EXPORT  HRTIMER_IRQ9_IRQHandler           [WEAK]
                EXPORT  TIMER19_BRK_TRS_IDX_IRQHandler    [WEAK]
                EXPORT  TIMER19_UP_IRQHandler             [WEAK]
                EXPORT  TIMER19_TRG_CMT_IDX_IRQHandler    [WEAK]
                EXPORT  TIMER19_Channel_IRQHandler        [WEAK]
                EXPORT  FPU_IRQHandler                    [WEAK]
                EXPORT  I2C2_EV_WKUP_IRQHandler           [WEAK]
                EXPORT  I2C2_ER_IRQHandler                [WEAK]
                EXPORT  CAU_IRQHandler                    [WEAK]
                EXPORT  TRNG_IRQHandler                   [WEAK]
                EXPORT  I2C3_EV_WKUP_IRQHandler           [WEAK]
                EXPORT  I2C3_ER_IRQHandler                [WEAK]
                EXPORT  DMAMUX_OVR_IRQHandler             [WEAK]
                EXPORT  QSPI_IRQHandler                   [WEAK]
                EXPORT  FFT_IRQHandler                    [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler          [WEAK]
                EXPORT  CLA_IRQHandler                    [WEAK]
                EXPORT  TMU_IRQHandler                    [WEAK]
                EXPORT  FAC_IRQHandler                    [WEAK]
                EXPORT  HPDF_INT0_IRQHandler              [WEAK]
                EXPORT  HPDF_INT1_IRQHandler              [WEAK]
                EXPORT  HPDF_INT2_IRQHandler              [WEAK]
                EXPORT  HPDF_INT3_IRQHandler              [WEAK]
                EXPORT  TIMER14_IRQHandler                [WEAK]
                EXPORT  TIMER15_IRQHandler                [WEAK]
                EXPORT  TIMER16_IRQHandler                [WEAK]
                EXPORT  CAN0_WKUP_IRQHandler              [WEAK]
                EXPORT  CAN0_Message_IRQHandler           [WEAK]
                EXPORT  CAN0_Busoff_IRQHandler            [WEAK]
                EXPORT  CAN0_Error_IRQHandler             [WEAK]
                EXPORT  CAN0_FastError_IRQHandler         [WEAK]
                EXPORT  CAN0_TEC_IRQHandler               [WEAK]
                EXPORT  CAN0_REC_IRQHandler               [WEAK]
                EXPORT  CAN1_WKUP_IRQHandler              [WEAK]
                EXPORT  CAN1_Message_IRQHandler           [WEAK]
                EXPORT  CAN1_Busoff_IRQHandler            [WEAK]
                EXPORT  CAN1_Error_IRQHandler             [WEAK]
                EXPORT  CAN1_FastError_IRQHandler         [WEAK]
                EXPORT  CAN1_TEC_IRQHandler               [WEAK]
                EXPORT  CAN1_REC_IRQHandler               [WEAK]
                EXPORT  CAN2_WKUP_IRQHandler              [WEAK]
                EXPORT  CAN2_Message_IRQHandler           [WEAK]
                EXPORT  CAN2_Busoff_IRQHandler            [WEAK]
                EXPORT  CAN2_Error_IRQHandler             [WEAK]
                EXPORT  CAN2_FastError_IRQHandler         [WEAK]
                EXPORT  CAN2_TEC_IRQHandler               [WEAK]
                EXPORT  CAN2_REC_IRQHandler               [WEAK]
                EXPORT  TIMER0_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER1_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER2_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER3_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER4_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER7_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER19_DEC_IRQHandler            [WEAK]

;/* external interrupts handler */
WWDGT_IRQHandler                  
LVD_VAVD_VOVD_VUVD_IRQHandler        
TAMPER_IRQHandler                 
RTC_WKUP_IRQHandler               
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
DMA0_Channel6_IRQHandler          
ADC0_1_IRQHandler                 
EXTI5_9_IRQHandler                
TIMER0_BRK_IRQHandler             
TIMER0_UP_IRQHandler              
TIMER0_TRG_CMT_IDX_IRQHandler     
TIMER0_Channel_IRQHandler         
TIMER1_IRQHandler                 
TIMER2_IRQHandler                 
TIMER3_IRQHandler                 
I2C0_EV_WKUP_IRQHandler           
I2C0_ER_IRQHandler                
I2C1_EV_WKUP_IRQHandler           
I2C1_ER_IRQHandler                
SPI0_IRQHandler                   
SPI1_IRQHandler                   
USART0_IRQHandler                 
USART1_IRQHandler                 
USART2_IRQHandler                 
EXTI10_15_IRQHandler              
RTC_Alarm_IRQHandler              
TIMER7_BRK_TRS_IDX_IRQHandler     
TIMER7_UP_IRQHandler              
TIMER7_TRG_CMT_IDX_IRQHandler     
TIMER7_Channel_IRQHandler         
ADC2_IRQHandler                   
SYSCFG_IRQHandler                 
LPTIMER_IRQHandler                
TIMER4_IRQHandler                 
SPI2_IRQHandler                   
UART3_IRQHandler                  
UART4_IRQHandler                  
TIMER5_DAC0_2_UDR_IRQHandler      
TIMER6_DAC1_3_UDR_IRQHandler      
DMA1_Channel0_IRQHandler          
DMA1_Channel1_IRQHandler          
DMA1_Channel2_IRQHandler          
DMA1_Channel3_IRQHandler          
DMA1_Channel4_IRQHandler          
ADC3_IRQHandler                   
VUVD1_VOVD1_IRQHandler            
CMP0_3_IRQHandler                 
CMP4_7_IRQHandler                 
CMP_IRQHandler                    
HRTIMER_IRQ0_IRQHandler           
HRTIMER_IRQ1_IRQHandler           
HRTIMER_IRQ2_IRQHandler           
HRTIMER_IRQ3_IRQHandler           
HRTIMER_IRQ4_IRQHandler           
HRTIMER_IRQ5_IRQHandler           
HRTIMER_IRQ6_IRQHandler           
HRTIMER_IRQ7_IRQHandler           
HRTIMER_IRQ8_IRQHandler           
HRTIMER_IRQ9_IRQHandler           
TIMER19_BRK_TRS_IDX_IRQHandler    
TIMER19_UP_IRQHandler             
TIMER19_TRG_CMT_IDX_IRQHandler    
TIMER19_Channel_IRQHandler        
FPU_IRQHandler                    
I2C2_EV_WKUP_IRQHandler           
I2C2_ER_IRQHandler                
CAU_IRQHandler                    
TRNG_IRQHandler                   
I2C3_EV_WKUP_IRQHandler           
I2C3_ER_IRQHandler                
DMAMUX_OVR_IRQHandler             
QSPI_IRQHandler                   
FFT_IRQHandler                    
DMA1_Channel5_IRQHandler          
DMA1_Channel6_IRQHandler          
CLA_IRQHandler                    
TMU_IRQHandler                    
FAC_IRQHandler                    
HPDF_INT0_IRQHandler              
HPDF_INT1_IRQHandler              
HPDF_INT2_IRQHandler              
HPDF_INT3_IRQHandler              
TIMER14_IRQHandler                
TIMER15_IRQHandler                
TIMER16_IRQHandler                
CAN0_WKUP_IRQHandler              
CAN0_Message_IRQHandler           
CAN0_Busoff_IRQHandler            
CAN0_Error_IRQHandler             
CAN0_FastError_IRQHandler         
CAN0_TEC_IRQHandler               
CAN0_REC_IRQHandler               
CAN1_WKUP_IRQHandler              
CAN1_Message_IRQHandler           
CAN1_Busoff_IRQHandler            
CAN1_Error_IRQHandler             
CAN1_FastError_IRQHandler         
CAN1_TEC_IRQHandler               
CAN1_REC_IRQHandler               
CAN2_WKUP_IRQHandler              
CAN2_Message_IRQHandler           
CAN2_Busoff_IRQHandler            
CAN2_Error_IRQHandler             
CAN2_FastError_IRQHandler         
CAN2_TEC_IRQHandler               
CAN2_REC_IRQHandler               
TIMER0_DEC_IRQHandler             
TIMER1_DEC_IRQHandler             
TIMER2_DEC_IRQHandler             
TIMER3_DEC_IRQHandler             
TIMER4_DEC_IRQHandler             
TIMER7_DEC_IRQHandler             
TIMER19_DEC_IRQHandler            

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
