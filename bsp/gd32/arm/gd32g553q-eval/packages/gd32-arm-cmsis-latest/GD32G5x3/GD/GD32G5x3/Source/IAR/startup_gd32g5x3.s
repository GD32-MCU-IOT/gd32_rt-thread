;/*!
;    \file    startup_gd32g5x3.s
;    \brief   start up file

;    \version 2025-02-10, V1.1.0, firmware for GD32G5x3
;*/

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

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
                DCD     sfe(CSTACK)                                  ; top of stack
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
                DCD     WWDGT_IRQHandler                             ; 16:Window Watchdog Timer
                DCD     LVD_VAVD_VOVD_VUVD_IRQHandler                   ; 17:LVD/AVD/OVD/UVD through EXTI line detect
                DCD     TAMPER_IRQHandler                            ; 18:RTC Tamper and TimeStamp from EXTI interrupt, LXTAL clock stuck interrupt
                DCD     RTC_WKUP_IRQHandler                          ; 19:RTC Wakeup from EXTI interrupt
                DCD     FMC_IRQHandler                               ; 20:FMC global interrupt
                DCD     RCU_IRQHandler                               ; 21:RCU global interrupt
                DCD     EXTI0_IRQHandler                             ; 22:EXTI line 0 interrupt
                DCD     EXTI1_IRQHandler                             ; 23:EXTI line 1 interrupt
                DCD     EXTI2_IRQHandler                             ; 24:EXTI line 2 interrupt
                DCD     EXTI3_IRQHandler                             ; 25:EXTI line 3 interrupt
                DCD     EXTI4_IRQHandler                             ; 26:EXTI line 4 interrupt
                DCD     DMA0_Channel0_IRQHandler                     ; 27:DMA0 Channel 0 global interrupt
                DCD     DMA0_Channel1_IRQHandler                     ; 28:DMA0 Channel 1 global interrupt
                DCD     DMA0_Channel2_IRQHandler                     ; 29:DMA0 Channel 2 global interrupt
                DCD     DMA0_Channel3_IRQHandler                     ; 30:DMA0 Channel 3 global interrupt
                DCD     DMA0_Channel4_IRQHandler                     ; 31:DMA0 Channel 4 global interrupt
                DCD     DMA0_Channel5_IRQHandler                     ; 32:DMA0 Channel 5 global interrupt
                DCD     DMA0_Channel6_IRQHandler                     ; 33:DMA0 Channel 6 global interrupt
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
                DCD     EXTI10_15_IRQHandler                         ; 56:EXTI1 line10-15 interrupt
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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler

                 LDR     r0, = 0x1FFFB3E0
                 LDR     r2, [r0]
                 LDR     r0, = 0xFFFF0000
                 AND     r2, r2, r0
                 LSR     r2, r2, #16
                 LSL     r2, r2, #10
                 LDR     r1, =0x20000000
                 MOV     r0, #0x00
MEM_INIT         STM     r1!, {r0}
                 SUBS    r2, r2, #4
                 CMP     r2, #0x00
                 BNE     MEM_INIT

                 LDR     r0, =SystemInit
                 BLX     r0
                 LDR     r0, =__iar_program_start
                 BX      r0

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

        PUBWEAK LVD_VAVD_VOVD_VUVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LVD_VAVD_VOVD_VUVD_IRQHandler
        B LVD_VAVD_VOVD_VUVD_IRQHandler

        PUBWEAK TAMPER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMPER_IRQHandler
        B TAMPER_IRQHandler

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

        PUBWEAK DMA0_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel6_IRQHandler
        B DMA0_Channel6_IRQHandler

        PUBWEAK ADC0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC0_1_IRQHandler
        B ADC0_1_IRQHandler

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

        PUBWEAK TIMER0_TRG_CMT_IDX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_TRG_CMT_IDX_IRQHandler
        B TIMER0_TRG_CMT_IDX_IRQHandler

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

        PUBWEAK I2C0_EV_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_EV_WKUP_IRQHandler
        B I2C0_EV_WKUP_IRQHandler

        PUBWEAK I2C0_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_ER_IRQHandler
        B I2C0_ER_IRQHandler

        PUBWEAK I2C1_EV_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_EV_WKUP_IRQHandler
        B I2C1_EV_WKUP_IRQHandler

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

        PUBWEAK TIMER7_BRK_TRS_IDX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_BRK_TRS_IDX_IRQHandler
        B TIMER7_BRK_TRS_IDX_IRQHandler

        PUBWEAK TIMER7_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_UP_IRQHandler
        B TIMER7_UP_IRQHandler

        PUBWEAK TIMER7_TRG_CMT_IDX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_TRG_CMT_IDX_IRQHandler
        B TIMER7_TRG_CMT_IDX_IRQHandler

        PUBWEAK TIMER7_Channel_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_Channel_IRQHandler
        B TIMER7_Channel_IRQHandler

        PUBWEAK ADC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC2_IRQHandler
        B ADC2_IRQHandler

        PUBWEAK SYSCFG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SYSCFG_IRQHandler
        B SYSCFG_IRQHandler

        PUBWEAK LPTIMER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIMER_IRQHandler
        B LPTIMER_IRQHandler

        PUBWEAK TIMER4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER4_IRQHandler
        B TIMER4_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART3_IRQHandler
        B UART3_IRQHandler

        PUBWEAK UART4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART4_IRQHandler
        B UART4_IRQHandler

        PUBWEAK TIMER5_DAC0_2_UDR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER5_DAC0_2_UDR_IRQHandler
        B TIMER5_DAC0_2_UDR_IRQHandler

        PUBWEAK TIMER6_DAC1_3_UDR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER6_DAC1_3_UDR_IRQHandler
        B TIMER6_DAC1_3_UDR_IRQHandler

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

        PUBWEAK ADC3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC3_IRQHandler
        B ADC3_IRQHandler

        PUBWEAK VUVD1_VOVD1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
VUVD1_VOVD1_IRQHandler
        B VUVD1_VOVD1_IRQHandler

        PUBWEAK CMP0_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP0_3_IRQHandler
        B CMP0_3_IRQHandler

        PUBWEAK CMP4_7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP4_7_IRQHandler
        B CMP4_7_IRQHandler

        PUBWEAK CMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP_IRQHandler
        B CMP_IRQHandler

        PUBWEAK HRTIMER_IRQ0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HRTIMER_IRQ0_IRQHandler
        B HRTIMER_IRQ0_IRQHandler

        PUBWEAK HRTIMER_IRQ1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HRTIMER_IRQ1_IRQHandler
        B HRTIMER_IRQ1_IRQHandler

        PUBWEAK HRTIMER_IRQ2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HRTIMER_IRQ2_IRQHandler
        B HRTIMER_IRQ2_IRQHandler

        PUBWEAK HRTIMER_IRQ3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HRTIMER_IRQ3_IRQHandler
        B HRTIMER_IRQ3_IRQHandler

        PUBWEAK HRTIMER_IRQ4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HRTIMER_IRQ4_IRQHandler
        B HRTIMER_IRQ4_IRQHandler

        PUBWEAK HRTIMER_IRQ5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HRTIMER_IRQ5_IRQHandler
        B HRTIMER_IRQ5_IRQHandler

        PUBWEAK HRTIMER_IRQ6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HRTIMER_IRQ6_IRQHandler
        B HRTIMER_IRQ6_IRQHandler

        PUBWEAK HRTIMER_IRQ7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HRTIMER_IRQ7_IRQHandler
        B HRTIMER_IRQ7_IRQHandler

        PUBWEAK HRTIMER_IRQ8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HRTIMER_IRQ8_IRQHandler
        B HRTIMER_IRQ8_IRQHandler

        PUBWEAK HRTIMER_IRQ9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HRTIMER_IRQ9_IRQHandler
        B HRTIMER_IRQ9_IRQHandler

        PUBWEAK TIMER19_BRK_TRS_IDX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER19_BRK_TRS_IDX_IRQHandler
        B TIMER19_BRK_TRS_IDX_IRQHandler

        PUBWEAK TIMER19_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER19_UP_IRQHandler
        B TIMER19_UP_IRQHandler

        PUBWEAK TIMER19_TRG_CMT_IDX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER19_TRG_CMT_IDX_IRQHandler
        B TIMER19_TRG_CMT_IDX_IRQHandler

        PUBWEAK TIMER19_Channel_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER19_Channel_IRQHandler
        B TIMER19_Channel_IRQHandler

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FPU_IRQHandler
        B FPU_IRQHandler

        PUBWEAK I2C2_EV_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_EV_WKUP_IRQHandler
        B I2C2_EV_WKUP_IRQHandler

        PUBWEAK I2C2_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_ER_IRQHandler
        B I2C2_ER_IRQHandler

        PUBWEAK CAU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAU_IRQHandler
        B CAU_IRQHandler

        PUBWEAK TRNG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TRNG_IRQHandler
        B TRNG_IRQHandler

        PUBWEAK I2C3_EV_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_EV_WKUP_IRQHandler
        B I2C3_EV_WKUP_IRQHandler

        PUBWEAK I2C3_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_ER_IRQHandler
        B I2C3_ER_IRQHandler

        PUBWEAK DMAMUX_OVR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMAMUX_OVR_IRQHandler
        B DMAMUX_OVR_IRQHandler

        PUBWEAK QSPI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
QSPI_IRQHandler
        B QSPI_IRQHandler

        PUBWEAK FFT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FFT_IRQHandler
        B FFT_IRQHandler

        PUBWEAK DMA1_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel5_IRQHandler
        B DMA1_Channel5_IRQHandler

        PUBWEAK DMA1_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel6_IRQHandler
        B DMA1_Channel6_IRQHandler

        PUBWEAK CLA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CLA_IRQHandler
        B CLA_IRQHandler

        PUBWEAK TMU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMU_IRQHandler
        B TMU_IRQHandler

        PUBWEAK FAC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FAC_IRQHandler
        B FAC_IRQHandler

        PUBWEAK HPDF_INT0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDF_INT0_IRQHandler
        B HPDF_INT0_IRQHandler

        PUBWEAK HPDF_INT1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDF_INT1_IRQHandler
        B HPDF_INT1_IRQHandler

        PUBWEAK HPDF_INT2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDF_INT2_IRQHandler
        B HPDF_INT2_IRQHandler

        PUBWEAK HPDF_INT3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDF_INT3_IRQHandler
        B HPDF_INT3_IRQHandler

        PUBWEAK TIMER14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER14_IRQHandler
        B TIMER14_IRQHandler

        PUBWEAK TIMER15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER15_IRQHandler
        B TIMER15_IRQHandler

        PUBWEAK TIMER16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER16_IRQHandler
        B TIMER16_IRQHandler

        PUBWEAK CAN0_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_WKUP_IRQHandler
        B CAN0_WKUP_IRQHandler

        PUBWEAK CAN0_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_Message_IRQHandler
        B CAN0_Message_IRQHandler

        PUBWEAK CAN0_Busoff_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_Busoff_IRQHandler
        B CAN0_Busoff_IRQHandler

        PUBWEAK CAN0_Error_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_Error_IRQHandler
        B CAN0_Error_IRQHandler

        PUBWEAK CAN0_FastError_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_FastError_IRQHandler
        B CAN0_FastError_IRQHandler

        PUBWEAK CAN0_TEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_TEC_IRQHandler
        B CAN0_TEC_IRQHandler

        PUBWEAK CAN0_REC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_REC_IRQHandler
        B CAN0_REC_IRQHandler

        PUBWEAK CAN1_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_WKUP_IRQHandler
        B CAN1_WKUP_IRQHandler

        PUBWEAK CAN1_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_Message_IRQHandler
        B CAN1_Message_IRQHandler

        PUBWEAK CAN1_Busoff_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_Busoff_IRQHandler
        B CAN1_Busoff_IRQHandler

        PUBWEAK CAN1_Error_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_Error_IRQHandler
        B CAN1_Error_IRQHandler

        PUBWEAK CAN1_FastError_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_FastError_IRQHandler
        B CAN1_FastError_IRQHandler

        PUBWEAK CAN1_TEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_TEC_IRQHandler
        B CAN1_TEC_IRQHandler

        PUBWEAK CAN1_REC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_REC_IRQHandler
        B CAN1_REC_IRQHandler

        PUBWEAK CAN2_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_WKUP_IRQHandler
        B CAN2_WKUP_IRQHandler

        PUBWEAK CAN2_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_Message_IRQHandler
        B CAN2_Message_IRQHandler

        PUBWEAK CAN2_Busoff_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_Busoff_IRQHandler
        B CAN2_Busoff_IRQHandler

        PUBWEAK CAN2_Error_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_Error_IRQHandler
        B CAN2_Error_IRQHandler

        PUBWEAK CAN2_FastError_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_FastError_IRQHandler
        B CAN2_FastError_IRQHandler

        PUBWEAK CAN2_TEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_TEC_IRQHandler
        B CAN2_TEC_IRQHandler

        PUBWEAK CAN2_REC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_REC_IRQHandler
        B CAN2_REC_IRQHandler

        PUBWEAK TIMER0_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_DEC_IRQHandler
        B TIMER0_DEC_IRQHandler

        PUBWEAK TIMER1_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER1_DEC_IRQHandler
        B TIMER1_DEC_IRQHandler

        PUBWEAK TIMER2_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER2_DEC_IRQHandler
        B TIMER2_DEC_IRQHandler

        PUBWEAK TIMER3_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER3_DEC_IRQHandler
        B TIMER3_DEC_IRQHandler

        PUBWEAK TIMER4_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER4_DEC_IRQHandler
        B TIMER4_DEC_IRQHandler

        PUBWEAK TIMER7_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_DEC_IRQHandler
        B TIMER7_DEC_IRQHandler

        PUBWEAK TIMER19_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER19_DEC_IRQHandler
        B TIMER19_DEC_IRQHandler

        END
