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
        DCD     0                                   ; Reserved
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
        DCD     LVD_VAVD_IRQHandler                 ; 17:LVD/VAVD through EXTI Line detect
        DCD     TAMPER_IRQHandler                   ; 18:Tamper through EXTI Line detect
        DCD     RTC_IRQHandler                      ; 19:RTC through EXTI Line
        DCD     FMC_IRQHandler                      ; 20:FMC
        DCD     RCU_CTC_IRQHandler                  ; 21:RCU and CTC
        DCD     EXTI0_IRQHandler                    ; 22:EXTI Line 0
        DCD     EXTI1_IRQHandler                    ; 23:EXTI Line 1
        DCD     EXTI2_IRQHandler                    ; 24:EXTI Line 2
        DCD     EXTI3_IRQHandler                    ; 25:EXTI Line 3
        DCD     EXTI4_IRQHandler                    ; 26:EXTI Line 4
        DCD     DMA0_Channel0_IRQHandler            ; 27:DMA0 Channel0 global interrupt
        DCD     DMA0_Channel1_IRQHandler            ; 28:DMA0 Channel1 global interrupt
        DCD     DMA0_Channel2_IRQHandler            ; 29:DMA0 Channel2 global interrupt
        DCD     DMA0_Channel3_IRQHandler            ; 30:DMA0 Channel3 global interrupt
        DCD     DMA0_Channel4_IRQHandler            ; 31:DMA0 Channel4 global interrupt
        DCD     DMA0_Channel5_IRQHandler            ; 32:DMA0 Channel5 global interrupt
        DCD     DMA0_Channel6_IRQHandler            ; 33:DMA0 Channel6 global interrupt
        DCD     ADC0_1_IRQHandler                   ; 34:ADC0 and ADC1 global interrupt
        DCD     CAN0_TX_IRQHandler                  ; 35:CAN0 TX interrupt
        DCD     CAN0_RX0_IRQHandler                 ; 36:CAN0 RX0 interrupt
        DCD     CAN0_RX1_IRQHandler                 ; 37:CAN0 RX1 interrupt
        DCD     CAN0_EWMC_IRQHandler                ; 38:CAN0 EWMC interrupt
        DCD     EXTI5_9_IRQHandler                  ; 39:EXTI line5-9 interrupt
        DCD     TIMER0_BRK_IRQHandler               ; 40:TIMER0 break interrupt
        DCD     TIMER0_UP_IRQHandler                ; 41:TIMER0 update interrupt
        DCD     TIMER0_TRG_CMT_IRQHandler           ; 42:TIMER0 trigger and channel commutation interrupt
        DCD     TIMER0_Channel_IRQHandler           ; 43:TIMER0 channel capture compare interrupt
        DCD     TIMER1_IRQHandler                   ; 44:TIMER1 global interrupt
        DCD     TIMER2_IRQHandler                   ; 45:TIMER2 global interrupt
        DCD     TIMER3_IRQHandler                   ; 46:TIMER3 global interrupt
        DCD     I2C0_EV_IRQHandler                  ; 47:I2C0 event interrupt
        DCD     I2C0_ER_IRQHandler                  ; 48:I2C0 error interrupt
        DCD     I2C1_EV_IRQHandler                  ; 49:I2C1 event interrupt
        DCD     I2C1_ER_IRQHandler                  ; 50:I2C1 error interrupt
        DCD     SPI0_IRQHandler                     ; 51:SPI0 global interrupt
        DCD     SPI1_IRQHandler                     ; 52:SPI1 global interrupt
        DCD     USART0_IRQHandler                   ; 53:USART0 global interrupt
        DCD     USART1_IRQHandler                   ; 54:USART1 global interrupt
        DCD     USART2_IRQHandler                   ; 55:USART2 global interrupt
        DCD     EXTI10_15_IRQHandler                ; 56:EXTI line10-15 interrupt
        DCD     RTC_Alarm_IRQHandler                ; 57:RTC alarm from EXTI interrupt
        DCD     USBFS_WKUP_IRQHandler               ; 58:USBFS wakeup from EXTI interrupt
        DCD     TIMER7_BRK_IRQHandler               ; 59:TIMER7 break interrupt
        DCD     TIMER7_UP_IRQHandler                ; 60:TIMER7 update interrupt
        DCD     TIMER7_TRG_CMT_IRQHandler           ; 61:TIMER7 trigger and channel commutation interrupt
        DCD     TIMER7_Channel_IRQHandler           ; 62:TIMER7 channel capture compare interrupt
        DCD     ADC2_IRQHandler                     ; 63:ADC2 global interrupt
        DCD     0                                   ; 64 Reserved
        DCD     RCU_IRQHandler                      ; 65:RCU global interrupt
        DCD     CMP_WAKEUP_IRQHandler               ; 66:CMP from EXTI interrupt
        DCD     SPI2_IRQHandler                     ; 67:SPI2 global interrupt
        DCD     UART3_IRQHandler                    ; 68:UART3 global interrupt
        DCD     UART4_IRQHandler                    ; 69:UART4 global interrupt
        DCD     TIMER5_IRQHandler                   ; 70:TIMER5 global interrupt
        DCD     TIMER6_IRQHandler                   ; 71:TIMER6 global interrupt
        DCD     DMA1_Channel0_IRQHandler            ; 72:DMA1 Channel0 global interrupt
        DCD     DMA1_Channel1_IRQHandler            ; 73:DMA1 Channel1 global interrupt
        DCD     DMA1_Channel2_IRQHandler            ; 74:DMA1 Channel2 global interrupt
        DCD     DMA1_Channel3_IRQHandler            ; 75:DMA1 Channel3 global interrupt
        DCD     DMA1_Channel4_IRQHandler            ; 76:DMA1 Channel4 global interrupt
        DCD     DAC_IRQHandler                      ; 77:DAC global interrupt
        DCD     VUVD_VOVD_IRQHandler                ; 78:VOVD and VUVD through exti line detection interrupt
        DCD     CAN1_TX_IRQHandler                  ; 79:CAN1 TX interrupt
        DCD     CAN1_RX0_IRQHandler                 ; 80:CAN1 RX0 interrupt
        DCD     CAN1_RX1_IRQHandler                 ; 81:CAN1 RX1 interrupt
        DCD     CAN1_EWMC_IRQHandler                ; 82:CAN1 EWMC interrupt
        DCD     SRAM_ECC_IRQHandler                 ; 83:SRAM ECC interrupt
        DCD     FPU_IRQHandler                      ; 84:FPU interrupt
        DCD     CMP_IRQHandler                      ; 85:CMP interrupt
        DCD     DMAMUX_IRQHandler                   ; 86:DMAMUX interrupt
        DCD     CAU_IRQHandler                      ; 87:CAU interrupt
        DCD     HAU_IRQHandler                      ; 88:HAU interrupt
        DCD     TRNG_IRQHandler                     ; 89:TRNG interrupt
        DCD     USBFS_IRQHandler                    ; 90:USBFS interrupt
        DCD     TIMER4_IRQHandler                   ; 91:Timer4 interrupt
        DCD     TIMER15_IRQHandler                  ; 92:Timer15 interrupt
        DCD     TIMER16_IRQHandler                  ; 93:Timer16 interrupt
        DCD	TIMER0_BRK_Channel_IRQHandler           ; 94:Timer0 channel break interrupt
        DCD     TIMER7_BRK_Channel_IRQHandler       ; 95:Timer7 channel break interrupt

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler

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
        
        PUBWEAK LVD_VAVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LVD_VAVD_IRQHandler
        B LVD_VAVD_IRQHandler
        
        PUBWEAK TAMPER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMPER_IRQHandler
        B TAMPER_IRQHandler
        
        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler
        
        PUBWEAK FMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMC_IRQHandler
        B FMC_IRQHandler
        
        PUBWEAK RCU_CTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCU_CTC_IRQHandler
        B RCU_CTC_IRQHandler
        
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
        
        PUBWEAK CAN0_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_TX_IRQHandler
        B CAN0_TX_IRQHandler
        
        PUBWEAK CAN0_RX0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_RX0_IRQHandler
        B CAN0_RX0_IRQHandler
        
        PUBWEAK CAN0_RX1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_RX1_IRQHandler
        B CAN0_RX1_IRQHandler
      
        PUBWEAK CAN0_EWMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_EWMC_IRQHandler
        B CAN0_EWMC_IRQHandler
        
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

        PUBWEAK USBFS_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBFS_WKUP_IRQHandler
        B USBFS_WKUP_IRQHandler

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

        PUBWEAK ADC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC2_IRQHandler
        B ADC2_IRQHandler

        PUBWEAK RCU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCU_IRQHandler
        B RCU_IRQHandler

        PUBWEAK CMP_WAKEUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP_WAKEUP_IRQHandler
        B CMP_IRQHandler

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

        PUBWEAK TIMER5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER5_IRQHandler
        B TIMER5_IRQHandler

        PUBWEAK TIMER6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER6_IRQHandler
        B TIMER6_IRQHandler

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

        PUBWEAK DAC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DAC_IRQHandler
        B DAC_IRQHandler

        PUBWEAK VUVD_VOVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
VUVD_VOVD_IRQHandler
        B VUVD_VOVD_IRQHandler

        PUBWEAK CAN1_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_TX_IRQHandler
        B CAN1_TX_IRQHandler

        PUBWEAK CAN1_RX0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_RX0_IRQHandler
        B CAN1_RX0_IRQHandler

        PUBWEAK CAN1_RX1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_RX1_IRQHandler
        B CAN1_RX1_IRQHandler

        PUBWEAK CAN1_EWMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_EWMC_IRQHandler
        B CAN1_EWMC_IRQHandler

        PUBWEAK SRAM_ECC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SRAM_ECC_IRQHandler
        B SRAM_ECC_IRQHandler 

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FPU_IRQHandler
        B FPU_IRQHandler

        PUBWEAK CMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP_IRQHandler
        B CMP_IRQHandler

        PUBWEAK DMAMUX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMAMUX_IRQHandler
        B DMAMUX_IRQHandler 

        PUBWEAK CAU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAU_IRQHandler
        B CAU_IRQHandler 

        PUBWEAK HAU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HAU_IRQHandler
        B HAU_IRQHandler

        PUBWEAK TRNG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TRNG_IRQHandler
        B TRNG_IRQHandler

        PUBWEAK USBFS_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBFS_IRQHandler
        B USBFS_IRQHandler

        PUBWEAK TIMER4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER4_IRQHandler
        B TIMER4_IRQHandler

        PUBWEAK TIMER15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER15_IRQHandler
        B TIMER15_IRQHandler

        PUBWEAK TIMER16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER16_IRQHandler
        B TIMER16_IRQHandler 

        PUBWEAK TIMER0_BRK_Channel_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_BRK_Channel_IRQHandler
        B TIMER0_BRK_Channel_IRQHandler

        PUBWEAK TIMER7_BRK_Channel_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_BRK_Channel_IRQHandler
        B TIMER7_BRK_Channel_IRQHandler
        
        END
