;/*!
;    \file    startup_gd32m53x.S
;    \brief   start up file
;
;    \version 2026-03-04, V1.0.0, firmware for GD32M53x
;*/
;
;/*
; * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
; * Copyright (c) 2026, GigaDevice Semiconductor Inc.
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

  .syntax unified
  .cpu cortex-m33
  .fpu fpv5-sp-d16
  .thumb

.global  Default_Handler

/* necessary symbols defined in linker script to initialize data */
.word  _sidata
.word  _sdata
.word  _edata
.word  _sbss
.word  _ebss

  .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function

/* reset Handler */
Reset_Handler:
  ldr     r0, =0x1FFFF7E0
  ldr     r2, [r0]
  ldr     r0, =0xFFFF0000
  and     r2, r2, r0
  lsr     r2, r2, #16
  lsl     r2, r2, #10
  ldr     r1, =0x20000000
  mov     r0, #0x00
SRAM_INIT:
  stm     r1!, {r0}
  subs    r2, r2, #4
  cmp     r2, #0x00
  bne     SRAM_INIT

  movs r1, #0
  b DataInit

CopyData:
  ldr r3, =_sidata
  ldr r3, [r3, r1]
  str r3, [r0, r1]
  adds r1, r1, #4

DataInit:
  ldr r0, =_sdata
  ldr r3, =_edata
  adds r2, r0, r1
  cmp r2, r3
  bcc CopyData
  ldr r2, =_sbss
  b Zerobss

FillZerobss:
  movs r3, #0
  str r3, [r2], #4

Zerobss:
  ldr r3, = _ebss
  cmp r2, r3
  bcc FillZerobss
/* Call SystemInit function */
  bl  SystemInit
/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl  entry

  bx lr

.size  Reset_Handler, .-Reset_Handler

.section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler

   .section  .isr_vector,"a",%progbits
   .global __gVectors

__gVectors:
                    .word _estack                                 /* Top of Stack */
                    .word Reset_Handler                           /* Reset Handler */
                    .word NMI_Handler                             /* NMI Handler */
                    .word HardFault_Handler                       /* Hard Fault Handler */
                    .word MemManage_Handler                       /* MPU Fault Handler */
                    .word BusFault_Handler                        /* Bus Fault Handler */
                    .word UsageFault_Handler                      /* Usage Fault Handler */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word SVC_Handler                             /* SVCall Handler */
                    .word DebugMon_Handler                        /* Debug Monitor Handler */
                    .word 0                                       /* Reserved */
                    .word PendSV_Handler                          /* PendSV Handler */
                    .word SysTick_Handler                         /* SysTick Handler */

                    /* External interrupts handler */
                    .word WWDGT_IRQHandler                        /* Vector Number 16,Window Watchdog Timer */
                    .word LVD1_IRQHandler                         /* Vector Number 17,LVD1 through EXTI Line 16 Detect */
                    .word LVD2_IRQHandler                         /* Vector Number 18,LVD2 through EXTI Line 17 Detect */
                    .word 0                                       /* Vector Number 19,Reserved */
                    .word FMC_IRQHandler                          /* Vector Number 20,FMC */
                    .word RCU_IRQHandler                          /* Vector Number 21,RCU */
                    .word EXTI0_IRQHandler                        /* Vector Number 22,EXTI Line 0 */
                    .word EXTI1_IRQHandler                        /* Vector Number 23,EXTI Line 1 */
                    .word EXTI2_IRQHandler                        /* Vector Number 24,EXTI Line 2 */
                    .word EXTI3_IRQHandler                        /* Vector Number 25,EXTI Line 3 */
                    .word EXTI4_IRQHandler                        /* Vector Number 26,EXTI Line 4 */
                    .word DMA0_Channel0_IRQHandler                /* Vector Number 27,DMA0 Channel0 */
                    .word DMA0_Channel1_IRQHandler                /* Vector Number 28,DMA0 Channel1 */
                    .word DMA0_Channel2_IRQHandler                /* Vector Number 29,DMA0 Channel2 */
                    .word DMA0_Channel3_IRQHandler                /* Vector Number 30,DMA0 Channel3 */
                    .word DMA0_Channel4_IRQHandler                /* Vector Number 31,DMA0 Channel4 */
                    .word DMA0_Channel5_IRQHandler                /* Vector Number 32,DMA0 Channel5 */
                    .word 0                                       /* Vector Number 33,Reserved */
                    .word ADC0_IRQHandler                         /* Vector Number 34,ADC0 */
                    .word CAN_TX_IRQHandler                       /* Vector Number 35,CAN TX */
                    .word CAN_RX0_IRQHandler                      /* Vector Number 36,CAN RX0 */
                    .word CAN_RX1_IRQHandler                      /* Vector Number 37,CAN RX1 */
                    .word CAN_EWMC_IRQHandler                     /* Vector Number 38,CAN EWMC */
                    .word EXTI5_9_IRQHandler                      /* Vector Number 39,EXTI Line 5 to EXTI Line 9 */
                    .word TIMER0_BRK_IRQHandler                   /* Vector Number 40,TIMER0 Break */
                    .word TIMER0_UP_IRQHandler                    /* Vector Number 41,TIMER0 Update */
                    .word TIMER0_TRG_CMT_IRQHandler               /* Vector Number 42,TIMER0 Trigger and Commutation */
                    .word TIMER0_Channel_IRQHandler               /* Vector Number 43,TIMER0 Channel Capture Compare */
                    .word TIMER1_IRQHandler                       /* Vector Number 44,TIMER1 */
                    .word TIMER2_IRQHandler                       /* Vector Number 45,TIMER2 */
                    .word GPTIMER0_IRQHandler                     /* Vector Number 46,GPTIMER0 */
                    .word I2C_EV_IRQHandler                       /* Vector Number 47,I2C Event */
                    .word I2C_ER_IRQHandler                       /* Vector Number 48,I2C Error */
                    .word 0                                       /* Vector Number 49,Reserved */
                    .word 0                                       /* Vector Number 50,Reserved */
                    .word SPI_IRQHandler                          /* Vector Number 51,SPI */
                    .word 0                                       /* Vector Number 52,Reserved */
                    .word UART0_IRQHandler                        /* Vector Number 53,UART0 */
                    .word UART1_IRQHandler                        /* Vector Number 54,UART1 */
                    .word 0                                       /* Vector Number 55,Reserved */
                    .word EXTI10_15_IRQHandler                    /* Vector Number 56,EXTI Line 10 to EXTI Line 15 */
                    .word 0                                       /* Vector Number 57,Reserved */
                    .word 0                                       /* Vector Number 58,Reserved */
                    .word TIMER7_BRK_IRQHandler                   /* Vector Number 59,TIMER7 Break */
                    .word TIMER7_UP_IRQHandler                    /* Vector Number 60,TIMER7 Update */
                    .word TIMER7_TRG_CMT_IRQHandler               /* Vector Number 61,TIMER7 Trigger and Commutation */
                    .word TIMER7_Channel_IRQHandler               /* Vector Number 62,TIMER7 Channel Capture Compare */
                    .word TMU_IRQHandler                          /* Vector Number 63,TMU */
                    .word 0                                       /* Vector Number 64,Reserved */
                    .word 0                                       /* Vector Number 65,Reserved */
                    .word GPTIMER1_IRQHandler                     /* Vector Number 66,GPTIMER1 */
                    .word 0                                       /* Vector Number 67,Reserved */
                    .word UART2_IRQHandler                        /* Vector Number 68,UART2 */
                    .word UART3_IRQHandler                        /* Vector Number 69,UART3 */
                    .word CPTIMER0_IRQHandler                     /* Vector Number 70,CPTIMER0 */
                    .word CPTIMER1_IRQHandler                     /* Vector Number 71,CPTIMER1 */
                    .word DMA1_Channel0_IRQHandler                /* Vector Number 72,DMA1 Channel0 */
                    .word DMA1_Channel1_IRQHandler                /* Vector Number 73,DMA1 Channel1 */
                    .word DMA1_Channel2_IRQHandler                /* Vector Number 74,DMA1 Channel2 */
                    .word DMA1_Channel3_IRQHandler                /* Vector Number 75,DMA1 Channel3 */
                    .word DMA1_Channel4_IRQHandler                /* Vector Number 76,DMA1 Channel4 */
                    .word DMA1_Channel5_IRQHandler                /* Vector Number 77,DMA1 Channel5 */
                    .word DMAMUX_OVERRUN_IRQHandler               /* Vector Number 78,DMAMUX Overrun */
                    .word CPTIMERW_IRQHandler                     /* Vector Number 79,CPTIMERW */
                    .word 0                                       /* Vector Number 80,Reserved */
                    .word CFMU_IRQHandler                         /* Vector Number 81,CFMU */
                    .word I2C_WKUP_IRQHandler                     /* Vector Number 82,I2C Wakeup through EXTI Line 23 Detect */
                    .word FWDGT_IRQHandler                        /* Vector Number 83,FWDGT through EXTI Line 22 Detect */
                    .word 0                                       /* Vector Number 84,Reserved */
                    .word 0                                       /* Vector Number 85,Reserved */
                    .word CMP0_IRQHandler                         /* Vector Number 86,CMP0 */
                    .word CMP1_IRQHandler                         /* Vector Number 87,CMP1 */
                    .word CMP2_IRQHandler                         /* Vector Number 88,CMP2 */
                    .word CMP3_IRQHandler                         /* Vector Number 89,CMP3 */
                    .word 0                                       /* Vector Number 90,Reserved */
                    .word ADC2_IRQHandler                         /* Vector Number 91,ADC2 */
                    .word 0                                       /* Vector Number 92,Reserved */
                    .word POC_IRQHandler                          /* Vector Number 93,POC */
                    .word 0                                       /* Vector Number 94,Reserved */
                    .word GTOC0_IRQHandler                        /* Vector Number 95,GTOC0 */
                    .word GTOC1_IRQHandler                        /* Vector Number 96,GTOC1 */
                    .word GTOC2_IRQHandler                        /* Vector Number 97,GTOC2 */
                    .word GTOC3_IRQHandler                        /* Vector Number 98,GTOC3 */
                    .word 0                                       /* Vector Number 99,Reserved */
                    .word 0                                       /* Vector Number 100,Reserved */
                    .word CMP0_EXTI_IRQHandler                    /* Vector Number 101,CMP0 through EXTI Line 18 Detect */
                    .word CMP1_EXTI_IRQHandler                    /* Vector Number 102,CMP1 through EXTI Line 19 Detect */
                    .word CMP2_EXTI_IRQHandler                    /* Vector Number 103,CMP2 through EXTI Line 20 Detect */
                    .word CMP3_EXTI_IRQHandler                    /* Vector Number 104,CMP3 through EXTI Line 21 Detect */
                    .word 0                                       /* Vector Number 105,Reserved */
                    .word 0                                       /* Vector Number 106,Reserved */
                    .word 0                                       /* Vector Number 107,Reserved */
                    .word SRAMC_ECC_IRQHandler                    /* Vector Number 108,SRAMC ECC */

  .size   __gVectors, . - __gVectors

  .weak NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler

  .weak BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler

  .weak UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler

  .weak SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

  .weak PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak WWDGT_IRQHandler
  .thumb_set WWDGT_IRQHandler,Default_Handler

  .weak LVD1_IRQHandler
  .thumb_set LVD1_IRQHandler,Default_Handler

  .weak LVD2_IRQHandler
  .thumb_set LVD2_IRQHandler,Default_Handler

  .weak FMC_IRQHandler
  .thumb_set FMC_IRQHandler,Default_Handler

  .weak RCU_IRQHandler
  .thumb_set RCU_IRQHandler,Default_Handler

  .weak EXTI0_IRQHandler
  .thumb_set EXTI0_IRQHandler,Default_Handler

  .weak EXTI1_IRQHandler
  .thumb_set EXTI1_IRQHandler,Default_Handler

  .weak EXTI2_IRQHandler
  .thumb_set EXTI2_IRQHandler,Default_Handler

  .weak EXTI3_IRQHandler
  .thumb_set EXTI3_IRQHandler,Default_Handler

  .weak EXTI4_IRQHandler
  .thumb_set EXTI4_IRQHandler,Default_Handler

  .weak DMA0_Channel0_IRQHandler
  .thumb_set DMA0_Channel0_IRQHandler,Default_Handler

  .weak DMA0_Channel1_IRQHandler
  .thumb_set DMA0_Channel1_IRQHandler,Default_Handler

  .weak DMA0_Channel2_IRQHandler
  .thumb_set DMA0_Channel2_IRQHandler,Default_Handler

  .weak DMA0_Channel3_IRQHandler
  .thumb_set DMA0_Channel3_IRQHandler,Default_Handler

  .weak DMA0_Channel4_IRQHandler
  .thumb_set DMA0_Channel4_IRQHandler,Default_Handler

  .weak DMA0_Channel5_IRQHandler
  .thumb_set DMA0_Channel5_IRQHandler,Default_Handler

  .weak ADC0_IRQHandler
  .thumb_set ADC0_IRQHandler,Default_Handler

  .weak CAN_TX_IRQHandler
  .thumb_set CAN_TX_IRQHandler,Default_Handler

  .weak CAN_RX0_IRQHandler
  .thumb_set CAN_RX0_IRQHandler,Default_Handler

  .weak CAN_RX1_IRQHandler
  .thumb_set CAN_RX1_IRQHandler,Default_Handler

  .weak CAN_EWMC_IRQHandler
  .thumb_set CAN_EWMC_IRQHandler,Default_Handler

  .weak EXTI5_9_IRQHandler
  .thumb_set EXTI5_9_IRQHandler,Default_Handler

  .weak TIMER0_BRK_IRQHandler
  .thumb_set TIMER0_BRK_IRQHandler,Default_Handler

  .weak TIMER0_UP_IRQHandler
  .thumb_set TIMER0_UP_IRQHandler,Default_Handler

  .weak TIMER0_TRG_CMT_IRQHandler
  .thumb_set TIMER0_TRG_CMT_IRQHandler,Default_Handler

  .weak TIMER0_Channel_IRQHandler
  .thumb_set TIMER0_Channel_IRQHandler,Default_Handler

  .weak TIMER1_IRQHandler
  .thumb_set TIMER1_IRQHandler,Default_Handler

  .weak TIMER2_IRQHandler
  .thumb_set TIMER2_IRQHandler,Default_Handler

  .weak GPTIMER0_IRQHandler
  .thumb_set GPTIMER0_IRQHandler,Default_Handler

  .weak I2C_EV_IRQHandler
  .thumb_set I2C_EV_IRQHandler,Default_Handler

  .weak I2C_ER_IRQHandler
  .thumb_set I2C_ER_IRQHandler,Default_Handler

  .weak SPI_IRQHandler
  .thumb_set SPI_IRQHandler,Default_Handler

  .weak UART0_IRQHandler
  .thumb_set UART0_IRQHandler,Default_Handler

  .weak UART1_IRQHandler
  .thumb_set UART1_IRQHandler,Default_Handler

  .weak EXTI10_15_IRQHandler
  .thumb_set EXTI10_15_IRQHandler,Default_Handler

  .weak TIMER7_BRK_IRQHandler
  .thumb_set TIMER7_BRK_IRQHandler,Default_Handler

  .weak TIMER7_UP_IRQHandler
  .thumb_set TIMER7_UP_IRQHandler,Default_Handler

  .weak TIMER7_TRG_CMT_IRQHandler
  .thumb_set TIMER7_TRG_CMT_IRQHandler,Default_Handler

  .weak TIMER7_Channel_IRQHandler
  .thumb_set TIMER7_Channel_IRQHandler,Default_Handler

  .weak TMU_IRQHandler
  .thumb_set TMU_IRQHandler,Default_Handler

  .weak GPTIMER1_IRQHandler
  .thumb_set GPTIMER1_IRQHandler,Default_Handler

  .weak UART2_IRQHandler
  .thumb_set UART2_IRQHandler,Default_Handler

  .weak UART3_IRQHandler
  .thumb_set UART3_IRQHandler,Default_Handler

  .weak CPTIMER0_IRQHandler
  .thumb_set CPTIMER0_IRQHandler,Default_Handler

  .weak CPTIMER1_IRQHandler
  .thumb_set CPTIMER1_IRQHandler,Default_Handler

  .weak DMA1_Channel0_IRQHandler
  .thumb_set DMA1_Channel0_IRQHandler,Default_Handler

  .weak DMA1_Channel1_IRQHandler
  .thumb_set DMA1_Channel1_IRQHandler,Default_Handler

  .weak DMA1_Channel2_IRQHandler
  .thumb_set DMA1_Channel2_IRQHandler,Default_Handler

  .weak DMA1_Channel3_IRQHandler
  .thumb_set DMA1_Channel3_IRQHandler,Default_Handler

  .weak DMA1_Channel4_IRQHandler
  .thumb_set DMA1_Channel4_IRQHandler,Default_Handler

  .weak DMA1_Channel5_IRQHandler
  .thumb_set DMA1_Channel5_IRQHandler,Default_Handler

  .weak DMAMUX_OVERRUN_IRQHandler
  .thumb_set DMAMUX_OVERRUN_IRQHandler,Default_Handler

  .weak CPTIMERW_IRQHandler
  .thumb_set CPTIMERW_IRQHandler,Default_Handler

  .weak CFMU_IRQHandler
  .thumb_set CFMU_IRQHandler,Default_Handler

  .weak I2C_WKUP_IRQHandler
  .thumb_set I2C_WKUP_IRQHandler,Default_Handler

  .weak FWDGT_IRQHandler
  .thumb_set FWDGT_IRQHandler,Default_Handler

  .weak CMP0_IRQHandler
  .thumb_set CMP0_IRQHandler,Default_Handler

  .weak CMP1_IRQHandler
  .thumb_set CMP1_IRQHandler,Default_Handler

  .weak CMP2_IRQHandler
  .thumb_set CMP2_IRQHandler,Default_Handler

  .weak CMP3_IRQHandler
  .thumb_set CMP3_IRQHandler,Default_Handler

  .weak ADC2_IRQHandler
  .thumb_set ADC2_IRQHandler,Default_Handler

  .weak POC_IRQHandler
  .thumb_set POC_IRQHandler,Default_Handler

  .weak GTOC0_IRQHandler
  .thumb_set GTOC0_IRQHandler,Default_Handler

  .weak GTOC1_IRQHandler
  .thumb_set GTOC1_IRQHandler,Default_Handler

  .weak GTOC2_IRQHandler
  .thumb_set GTOC2_IRQHandler,Default_Handler

  .weak GTOC3_IRQHandler
  .thumb_set GTOC3_IRQHandler,Default_Handler

  .weak CMP0_EXTI_IRQHandler
  .thumb_set CMP0_EXTI_IRQHandler,Default_Handler

  .weak CMP1_EXTI_IRQHandler
  .thumb_set CMP1_EXTI_IRQHandler,Default_Handler

  .weak CMP2_EXTI_IRQHandler
  .thumb_set CMP2_EXTI_IRQHandler,Default_Handler

  .weak CMP3_EXTI_IRQHandler
  .thumb_set CMP3_EXTI_IRQHandler,Default_Handler

  .weak SRAMC_ECC_IRQHandler
  .thumb_set SRAMC_ECC_IRQHandler,Default_Handler
