;/*!
;    \file    startup_gd32f50x.s
;    \brief   start up file
;
;    \version 2026-02-25, V1.0.4, firmware for GD32F50x
;*/
;
;/*
;    Copyright (c) 2026, GigaDevice Semiconductor Inc.
;
;    Redistribution and use in source and binary forms, with or without modification, 
;are permitted provided that the following conditions are met:
;
;    1. Redistributions of source code must retain the above copyright notice, this 
;       list of conditions and the following disclaimer.
;    2. Redistributions in binary form must reproduce the above copyright notice, 
;       this list of conditions and the following disclaimer in the documentation 
;       and/or other materials provided with the distribution.
;    3. Neither the name of the copyright holder nor the names of its contributors 
;       may be used to endorse or promote products derived from this software without 
;       specific prior written permission.
;
;    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
;AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
;WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
;IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
;INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
;NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
;PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
;WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
;ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
;OF SUCH DAMAGE.
;*/

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
                DCD     WWDGT_IRQHandler                  ; 16:window watchdog timer interrupt
                DCD     LVD_VAVD_IRQHandler               ; 17:LVD/VAVD through EXTI Line detect interrupt
                DCD     TAMPER_IRQHandler                 ; 18:Tamper through EXTI Line detect interrupt
                DCD     RTC_IRQHandler                    ; 19:RTC global interrupt
                DCD     FMC_IRQHandler                    ; 20:FMC global interrupt
                DCD     RCU_CTC_IRQHandler                ; 21:RCU and CTC interrupt
                DCD     EXTI0_IRQHandler                  ; 22:EXTI Line 0 interrupt
                DCD     EXTI1_IRQHandler                  ; 23:EXTI Line 1 interrupt
                DCD     EXTI2_IRQHandler                  ; 24:EXTI Line 2 interrupt
                DCD     EXTI3_IRQHandler                  ; 25:EXTI Line 3 interrupt
                DCD     EXTI4_IRQHandler                  ; 26:EXTI Line 4 interrupt
                DCD     DMA0_Channel0_IRQHandler          ; 27:DMA0 Channel0 global interrupt
                DCD     DMA0_Channel1_IRQHandler          ; 28:DMA0 Channel1 global interrupt
                DCD     DMA0_Channel2_IRQHandler          ; 29:DMA0 Channel2 global interrupt
                DCD     DMA0_Channel3_IRQHandler          ; 30:DMA0 Channel3 global interrupt
                DCD     DMA0_Channel4_IRQHandler          ; 31:DMA0 Channel4 global interrupt
                DCD     DMA0_Channel5_IRQHandler          ; 32:DMA0 Channel5 global interrupt
                DCD     DMA0_Channel6_IRQHandler          ; 33:DMA0 Channel6 global interrupt
                DCD     ADC0_1_IRQHandler                 ; 34:ADC0 and ADC1 global interrupt
                DCD     CAN0_TX_IRQHandler                ; 35:CAN0 TX interrupt
                DCD     CAN0_RX0_IRQHandler               ; 36:CAN0 RX0 interrupt
                DCD     CAN0_RX1_IRQHandler               ; 37:CAN0 RX1 interrupt
                DCD     CAN0_EWMC_IRQHandler              ; 38:CAN0 EWMC interrupt
                DCD     EXTI5_9_IRQHandler                ; 39:EXTI line5-9 interrupt
                DCD     TIMER0_BRK_IRQHandler             ; 40:TIMER0 break interrupt
                DCD     TIMER0_UP_IRQHandler              ; 41:TIMER0 update interrupt
                DCD     TIMER0_TRG_CMT_IRQHandler         ; 42:TIMER0 trigger and channel commutation interrupt
                DCD     TIMER0_Channel_IRQHandler         ; 43:TIMER0 channel capture compare interrupt
                DCD     TIMER1_IRQHandler                 ; 44:TIMER1 global interrupt
                DCD     TIMER2_IRQHandler                 ; 45:TIMER2 global interrupt
                DCD     TIMER3_IRQHandler                 ; 46:TIMER3 global interrupt
                DCD     I2C0_EV_IRQHandler                ; 47:I2C0 event interrupt
                DCD     I2C0_ER_IRQHandler                ; 48:I2C0 error interrupt
                DCD     I2C1_EV_IRQHandler                ; 49:I2C1 event interrupt
                DCD     I2C1_ER_IRQHandler                ; 50:I2C1 error interrupt
                DCD     SPI0_IRQHandler                   ; 51:SPI0 global interrupt
                DCD     SPI1_IRQHandler                   ; 52:SPI1 global interrupt
                DCD     USART0_IRQHandler                 ; 53:USART0 global interrupt
                DCD     USART1_IRQHandler                 ; 54:USART1 global interrupt
                DCD     USART2_IRQHandler                 ; 55:USART2 global interrupt
                DCD     EXTI10_15_IRQHandler              ; 56:EXTI line10-15 interrupt
                DCD     RTC_Alarm_IRQHandler              ; 57:RTC alarm from EXTI interrupt
                DCD     USBFS_WKUP_IRQHandler             ; 58:USBFS wakeup from EXTI interrupt
                DCD     TIMER7_BRK_IRQHandler             ; 59:TIMER7 break interrupt
                DCD     TIMER7_UP_IRQHandler              ; 60:TIMER7 update interrupt
                DCD     TIMER7_TRG_CMT_IRQHandler         ; 61:TIMER7 trigger and channel commutation interrupt
                DCD     TIMER7_Channel_IRQHandler         ; 62:TIMER7 channel capture compare interrupt
                DCD     ADC2_IRQHandler                   ; 63:ADC2 global interrupt
                DCD     0                                 ; 64 Reserved
                DCD     RCU_CKFM_IRQHandler               ; 65:RCU clock frequency monitor interrupt
                DCD     CMP_WAKEUP_IRQHandler             ; 66:CMP from EXTI interrupt
                DCD     SPI2_IRQHandler                   ; 67:SPI2 global interrupt
                DCD     UART3_IRQHandler                  ; 68:UART3 global interrupt
                DCD     UART4_IRQHandler                  ; 69:UART4 global interrupt
                DCD     TIMER5_IRQHandler                 ; 70:TIMER5 global interrupt
                DCD     TIMER6_IRQHandler                 ; 71:TIMER6 global interrupt
                DCD     DMA1_Channel0_IRQHandler          ; 72:DMA1 Channel0 global interrupt
                DCD     DMA1_Channel1_IRQHandler          ; 73:DMA1 Channel1 global interrupt
                DCD     DMA1_Channel2_IRQHandler          ; 74:DMA1 Channel2 global interrupt
                DCD     DMA1_Channel3_IRQHandler          ; 75:DMA1 Channel3 global interrupt
                DCD     DMA1_Channel4_IRQHandler          ; 76:DMA1 Channel4 global interrupt
                DCD     DAC_IRQHandler                    ; 77:DAC global interrupt
                DCD     VUVD_VOVD_IRQHandler              ; 78:VOVD and VUVD through exti line detection interrupt
                DCD     CAN1_TX_IRQHandler                ; 79:CAN1 TX interrupt
                DCD     CAN1_RX0_IRQHandler               ; 80:CAN1 RX0 interrupt
                DCD     CAN1_RX1_IRQHandler               ; 81:CAN1 RX1 interrupt
                DCD     CAN1_EWMC_IRQHandler              ; 82:CAN1 EWMC interrupt
                DCD     SRAM_ECC_IRQHandler               ; 83:SRAM ECC interrupt
                DCD     FPU_IRQHandler                    ; 84:FPU interrupt
                DCD     CMP_IRQHandler                    ; 85:CMP interrupt
                DCD     DMAMUX_IRQHandler                 ; 86:DMAMUX interrupt
                DCD     CAU_IRQHandler                    ; 87:CAU interrupt
                DCD     HAU_IRQHandler                    ; 88:HAU interrupt
                DCD     TRNG_IRQHandler                   ; 89:TRNG interrupt
                DCD     USBFS_IRQHandler                  ; 90:USBFS interrupt
                DCD     TIMER4_IRQHandler                 ; 91:Timer4 interrupt
                DCD     TIMER15_IRQHandler                ; 92:Timer15 interrupt
                DCD     TIMER16_IRQHandler                ; 93:Timer16 interrupt
                DCD     TIMER0_BRK_Channel_IRQHandler     ; 94:Timer0 channel break interrupt
                DCD     TIMER7_BRK_Channel_IRQHandler     ; 95:Timer7 channel break interrupt

__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

;/* reset Handler */
Reset_Handler    PROC
                 EXPORT  Reset_Handler                    [WEAK]
                 IMPORT  SystemInit
                 IMPORT  __main

                 LDR     R4, =0x1FFFF802
                 LDR     R5, [R4]
                 LSR     R5, R5, #3
                 ANDS    R5, R5, #0x3
                 CMP     R5, #0x3
                 BNE     SYSTEM_INIT

                 LDR     R0, =0x20000000
                 ADD     R1, R0, #0x8000
                 LDR     R2, =0x0
MEM_INIT         STRD    R2, R2, [ R0 ] , #8
                 CMP     R0, R1
                 BNE     MEM_INIT

SYSTEM_INIT
                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
                 BX      R0
                 ENDP

;/* dummy Exception Handlers */
NMI_Handler     PROC
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
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler                    [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler                   [WEAK]
                B       .
                ENDP

Default_Handler PROC
;               /* external interrupts handler */
                EXPORT  WWDGT_IRQHandler                  [WEAK]
                EXPORT  LVD_VAVD_IRQHandler               [WEAK]
                EXPORT  TAMPER_IRQHandler                 [WEAK]
                EXPORT  RTC_IRQHandler                    [WEAK]
                EXPORT  FMC_IRQHandler                    [WEAK]
                EXPORT  RCU_CTC_IRQHandler                [WEAK]
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
                EXPORT  CAN0_TX_IRQHandler                [WEAK]
                EXPORT  CAN0_RX0_IRQHandler               [WEAK]
                EXPORT  CAN0_RX1_IRQHandler               [WEAK]
                EXPORT  CAN0_EWMC_IRQHandler              [WEAK]
                EXPORT  EXTI5_9_IRQHandler                [WEAK]
                EXPORT  TIMER0_BRK_IRQHandler             [WEAK]
                EXPORT  TIMER0_UP_IRQHandler              [WEAK]
                EXPORT  TIMER0_TRG_CMT_IRQHandler         [WEAK]
                EXPORT  TIMER0_Channel_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler                 [WEAK]
                EXPORT  TIMER2_IRQHandler                 [WEAK]
                EXPORT  TIMER3_IRQHandler                 [WEAK]
                EXPORT  I2C0_EV_IRQHandler                [WEAK]
                EXPORT  I2C0_ER_IRQHandler                [WEAK]
                EXPORT  I2C1_EV_IRQHandler                [WEAK]
                EXPORT  I2C1_ER_IRQHandler                [WEAK]
                EXPORT  SPI0_IRQHandler                   [WEAK]
                EXPORT  SPI1_IRQHandler                   [WEAK]
                EXPORT  USART0_IRQHandler                 [WEAK]
                EXPORT  USART1_IRQHandler                 [WEAK]
                EXPORT  USART2_IRQHandler                 [WEAK]
                EXPORT  EXTI10_15_IRQHandler              [WEAK]
                EXPORT  RTC_Alarm_IRQHandler              [WEAK]
                EXPORT  USBFS_WKUP_IRQHandler             [WEAK]
                EXPORT  TIMER7_BRK_IRQHandler             [WEAK]
                EXPORT  TIMER7_UP_IRQHandler              [WEAK]
                EXPORT  TIMER7_TRG_CMT_IRQHandler         [WEAK]
                EXPORT  TIMER7_Channel_IRQHandler         [WEAK]
                EXPORT  ADC2_IRQHandler                   [WEAK]
                EXPORT  RCU_CKFM_IRQHandler               [WEAK]
                EXPORT  CMP_WAKEUP_IRQHandler             [WEAK]
                EXPORT  SPI2_IRQHandler                   [WEAK]
                EXPORT  UART3_IRQHandler                  [WEAK]
                EXPORT  UART4_IRQHandler                  [WEAK]
                EXPORT  TIMER5_IRQHandler                 [WEAK]
                EXPORT  TIMER6_IRQHandler                 [WEAK]
                EXPORT  DMA1_Channel0_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler          [WEAK]
                EXPORT  DAC_IRQHandler                    [WEAK]
                EXPORT  VUVD_VOVD_IRQHandler              [WEAK]
                EXPORT  CAN1_TX_IRQHandler                [WEAK]
                EXPORT  CAN1_RX0_IRQHandler               [WEAK]
                EXPORT  CAN1_RX1_IRQHandler               [WEAK]
                EXPORT  CAN1_EWMC_IRQHandler              [WEAK]
                EXPORT  SRAM_ECC_IRQHandler               [WEAK]
                EXPORT  FPU_IRQHandler                    [WEAK]
                EXPORT  CMP_IRQHandler                    [WEAK]
                EXPORT  DMAMUX_IRQHandler                 [WEAK]
                EXPORT  CAU_IRQHandler                    [WEAK]
                EXPORT  HAU_IRQHandler                    [WEAK]
                EXPORT  TRNG_IRQHandler                   [WEAK]
                EXPORT  USBFS_IRQHandler                  [WEAK]
                EXPORT  TIMER4_IRQHandler                 [WEAK]
                EXPORT  TIMER15_IRQHandler                [WEAK]
                EXPORT  TIMER16_IRQHandler                [WEAK]
                EXPORT  TIMER0_BRK_Channel_IRQHandler     [WEAK]
                EXPORT  TIMER7_BRK_Channel_IRQHandler     [WEAK]

;/* external interrupts handler */
WWDGT_IRQHandler
LVD_VAVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FMC_IRQHandler
RCU_CTC_IRQHandler
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
CAN0_TX_IRQHandler
CAN0_RX0_IRQHandler
CAN0_RX1_IRQHandler
CAN0_EWMC_IRQHandler
EXTI5_9_IRQHandler
TIMER0_BRK_IRQHandler
TIMER0_UP_IRQHandler
TIMER0_TRG_CMT_IRQHandler
TIMER0_Channel_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
I2C0_EV_IRQHandler
I2C0_ER_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
USART0_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
EXTI10_15_IRQHandler
RTC_Alarm_IRQHandler
USBFS_WKUP_IRQHandler
TIMER7_BRK_IRQHandler
TIMER7_UP_IRQHandler
TIMER7_TRG_CMT_IRQHandler
TIMER7_Channel_IRQHandler
ADC2_IRQHandler
RCU_CKFM_IRQHandler
CMP_WAKEUP_IRQHandler
SPI2_IRQHandler
UART3_IRQHandler
UART4_IRQHandler
TIMER5_IRQHandler
TIMER6_IRQHandler
DMA1_Channel0_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DAC_IRQHandler
VUVD_VOVD_IRQHandler
CAN1_TX_IRQHandler
CAN1_RX0_IRQHandler
CAN1_RX1_IRQHandler
CAN1_EWMC_IRQHandler
SRAM_ECC_IRQHandler
FPU_IRQHandler
CMP_IRQHandler
DMAMUX_IRQHandler
CAU_IRQHandler
HAU_IRQHandler
TRNG_IRQHandler
USBFS_IRQHandler
TIMER4_IRQHandler
TIMER15_IRQHandler
TIMER16_IRQHandler
TIMER0_BRK_Channel_IRQHandler
TIMER7_BRK_Channel_IRQHandler
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
