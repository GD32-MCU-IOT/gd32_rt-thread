;/*!
;    \file    startup_gd32w51x.S
;    \brief   start up file
;
;    \version 2026-04-15, V2.0.0, firmware for gd32w51x_f5hc
;*/
;
;/*
; * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
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
/*Call the main function */
  bl  main
  bx lr
.size  Reset_Handler, .-Reset_Handler

  .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler

  .section  .vectors,"a",%progbits
  .global __gVectors
__gVectors:
                    .word _sp                                     /* Top of Stack */
                    .word Reset_Handler                           /* Reset Handler */
                    .word NMI_Handler                             /* NMI Handler */
                    .word HardFault_Handler                       /* Hard Fault Handler */
                    .word MemManage_Handler                       /* MPU Fault Handler */
                    .word BusFault_Handler                        /* Bus Fault Handler */
                    .word UsageFault_Handler                      /* Usage Fault Handler */
                    .word SecureFault_Handler                     /* Secure Fault Handler */
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
                    .word LVD_IRQHandler                          /* Vector Number 17,LVD through EXTI Line detect */
                    .word TAMPER_STAMP_IRQHandler                 /* Vector Number 18,RTC Tamper and TimeStamp events interrupt */
                    .word RTC_WKUP_IRQHandler                     /* Vector Number 19,RTC Wakeup through EXTI Line */
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
                    .word DMA0_Channel6_IRQHandler                /* Vector Number 33,DMA0 Channel6 */
                    .word DMA0_Channel7_IRQHandler                /* Vector Number 34,DMA0 Channel7 */
                    .word ADC_IRQHandler                          /* Vector Number 35,ADC */
                    .word TAMPER_STAMP_S_IRQHandler               /* Vector Number 36,RTC Tamper and TimeStamp Events Security Interrupt */
                    .word RTC_WKUP_S_IRQHandler                   /* Vector Number 37,RTC Wakeup Security Interrupt */
                    .word RTC_Alarm_S_IRQHandler                  /* Vector Number 38,RTC Alarm Security Interrupt */
                    .word EXTI5_9_IRQHandler                      /* Vector Number 39,EXTI5 to EXTI9 */
                    .word TIMER0_BRK_IRQHandler                   /* Vector Number 40,TIMER0 Break */
                    .word TIMER0_UP_IRQHandler                    /* Vector Number 41,TIMER0 Update */
                    .word TIMER0_CMT_IRQHandler                   /* Vector Number 42,TIMER0 Commutation */
                    .word TIMER0_Channel_IRQHandler               /* Vector Number 43,TIMER0 Channel Capture Compare */
                    .word TIMER1_IRQHandler                       /* Vector Number 44,TIMER1 */
                    .word TIMER2_IRQHandler                       /* Vector Number 45,TIMER2 */
                    .word TIMER3_IRQHandler                       /* Vector Number 46,TIMER3 */
                    .word I2C0_EV_IRQHandler                      /* Vector Number 47,I2C0 Event */
                    .word I2C0_ER_IRQHandler                      /* Vector Number 48,I2C0 Error */
                    .word I2C1_EV_IRQHandler                      /* Vector Number 49,I2C1 Event */
                    .word I2C1_ER_IRQHandler                      /* Vector Number 50,I2C1 Error */
                    .word SPI0_IRQHandler                         /* Vector Number 51,SPI0 */
                    .word SPI1_IRQHandler                         /* Vector Number 52,SPI1/I2S1 */
                    .word USART0_IRQHandler                       /* Vector Number 53,USART0 */
                    .word USART1_IRQHandler                       /* Vector Number 54,USART1 */
                    .word USART2_IRQHandler                       /* Vector Number 55,USART2 */
                    .word EXTI10_15_IRQHandler                    /* Vector Number 56,EXTI10 to EXTI15 */
                    .word RTC_Alarm_IRQHandler                    /* Vector Number 57,RTC Alarm */
                    .word VLVDF_IRQHandler                        /* Vector Number 58,VDDA Low Voltage Detector */
                    .word 0                                       /* Vector Number 59,Reserved */
                    .word TIMER15_IRQHandler                      /* Vector Number 60,TIMER15 */
                    .word TIMER16_IRQHandler                      /* Vector Number 61,TIMER16 */
                    .word 0                                       /* Vector Number 62,Reserved */
                    .word 0                                       /* Vector Number 63,Reserved */
                    .word 0                                       /* Vector Number 64,Reserved */
                    .word SDIO_IRQHandler                         /* Vector Number 65,SDIO */
                    .word TIMER4_IRQHandler                       /* Vector Number 66,TIMER4 */
                    .word I2C0_WKUP_IRQHandler                    /* Vector Number 67,I2C0 Wakeup */
                    .word USART0_WKUP_IRQHandler                  /* Vector Number 68,USART0 Wakeup */
                    .word USART2_WKUP_IRQHandler                  /* Vector Number 69,USART2 Wakeup */
                    .word TIMER5_IRQHandler                       /* Vector Number 70,TIMER5 */
                    .word 0                                       /* Vector Number 71,Reserved */
                    .word DMA1_Channel0_IRQHandler                /* Vector Number 72,DMA1 Channel0 */
                    .word DMA1_Channel1_IRQHandler                /* Vector Number 73,DMA1 Channel1 */
                    .word DMA1_Channel2_IRQHandler                /* Vector Number 74,DMA1 Channel2 */
                    .word DMA1_Channel3_IRQHandler                /* Vector Number 75,DMA1 Channel3 */
                    .word DMA1_Channel4_IRQHandler                /* Vector Number 76,DMA1 Channel4 */
                    .word DMA1_Channel5_IRQHandler                /* Vector Number 77,DMA1 Channel5 */
                    .word DMA1_Channel6_IRQHandler                /* Vector Number 78,DMA1 Channel6 */
                    .word DMA1_Channel7_IRQHandler                /* Vector Number 79,DMA1 Channel7 */
                    .word 0                                       /* Vector Number 80,Reserved */
                    .word 0                                       /* Vector Number 81,Reserved */
                    .word WIFI11N_WKUP_IRQHandler                 /* Vector Number 82,WIFI11N wakeup interrupt */
                    .word USBFS_IRQHandler                        /* Vector Number 83,USBFS global interrupt */
                    .word 0                                       /* Vector Number 84,Reserved */
                    .word 0                                       /* Vector Number 85,Reserved */
                    .word 0                                       /* Vector Number 86,Reserved */
                    .word 0                                       /* Vector Number 87,Reserved */
                    .word 0                                       /* Vector Number 88,Reserved */
                    .word 0                                       /* Vector Number 89,Reserved */
                    .word 0                                       /* Vector Number 90,Reserved */
                    .word 0                                       /* Vector Number 91,Reserved */
                    .word USBFS_WKUP_IRQHandler                   /* Vector Number 92,USBFS_WKUP */
                    .word 0                                       /* Vector Number 93,Reserved */
                    .word DCI_IRQHandler                          /* Vector Number 94,DCI */
                    .word CAU_IRQHandler                          /* Vector Number 95,CAU */
                    .word HAU_TRNG_IRQHandler                     /* Vector Number 96,HAU and TRNG */
                    .word FPU_IRQHandler                          /* Vector Number 97,FPU */
                    .word 0                                       /* Vector Number 98,Reserved */
                    .word 0                                       /* Vector Number 99,Reserved */
                    .word 0                                       /* Vector Number 100,Reserved */
                    .word 0                                       /* Vector Number 101,Reserved */
                    .word 0                                       /* Vector Number 102,Reserved */
                    .word 0                                       /* Vector Number 103,Reserved */
                    .word 0                                       /* Vector Number 104,Reserved */
                    .word HPDF_INT0_IRQHandler                    /* Vector Number 105,HPDF global Interrupt 0 */
                    .word HPDF_INT1_IRQHandler                    /* Vector Number 106,HPDF global Interrupt 1 */
                    .word WIFI11N_INT0_IRQHandler                 /* Vector Number 107,WIFI11N global interrupt0 */
                    .word WIFI11N_INT1_IRQHandler                 /* Vector Number 108,WIFI11N global interrupt1 */
                    .word WIFI11N_INT2_IRQHandler                 /* Vector Number 109,WIFI11N global interrupt2 */
                    .word EFUSE_IRQHandler                        /* Vector Number 110,EFUSE */
                    .word QSPI_IRQHandler                         /* Vector Number 111,QUADSPI */
                    .word PKCAU_IRQHandler                        /* Vector Number 112,PKCAU */
                    .word TSI_IRQHandler                          /* Vector Number 113,TSI */
                    .word ICACHE_IRQHandler                       /* Vector Number 114,ICACHE */
                    .word TZIAC_S_IRQHandler                      /* Vector Number 115,TrustZone interrupt controller secure interrupts */
                    .word FMC_S_IRQHandler                        /* Vector Number 116,FMC */
                    .word QSPI_S_IRQHandler                       /* Vector Number 117,QSPI security interrupt */

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

  .weak SecureFault_Handler
  .thumb_set SecureFault_Handler,Default_Handler

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

  .weak LVD_IRQHandler
  .thumb_set LVD_IRQHandler,Default_Handler

  .weak TAMPER_STAMP_IRQHandler
  .thumb_set TAMPER_STAMP_IRQHandler,Default_Handler

  .weak RTC_WKUP_IRQHandler
  .thumb_set RTC_WKUP_IRQHandler,Default_Handler

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

  .weak DMA0_Channel6_IRQHandler
  .thumb_set DMA0_Channel6_IRQHandler,Default_Handler

  .weak DMA0_Channel7_IRQHandler
  .thumb_set DMA0_Channel7_IRQHandler,Default_Handler

  .weak ADC_IRQHandler
  .thumb_set ADC_IRQHandler,Default_Handler

  .weak TAMPER_STAMP_S_IRQHandler
  .thumb_set TAMPER_STAMP_S_IRQHandler,Default_Handler

  .weak RTC_WKUP_S_IRQHandler
  .thumb_set RTC_WKUP_S_IRQHandler,Default_Handler

  .weak RTC_Alarm_S_IRQHandler
  .thumb_set RTC_Alarm_S_IRQHandler,Default_Handler

  .weak EXTI5_9_IRQHandler
  .thumb_set EXTI5_9_IRQHandler,Default_Handler

  .weak TIMER0_BRK_IRQHandler
  .thumb_set TIMER0_BRK_IRQHandler,Default_Handler

  .weak TIMER0_UP_IRQHandler
  .thumb_set TIMER0_UP_IRQHandler,Default_Handler

  .weak TIMER0_CMT_IRQHandler
  .thumb_set TIMER0_CMT_IRQHandler,Default_Handler

  .weak TIMER0_Channel_IRQHandler
  .thumb_set TIMER0_Channel_IRQHandler,Default_Handler

  .weak TIMER1_IRQHandler
  .thumb_set TIMER1_IRQHandler,Default_Handler

  .weak TIMER2_IRQHandler
  .thumb_set TIMER2_IRQHandler,Default_Handler

  .weak TIMER3_IRQHandler
  .thumb_set TIMER3_IRQHandler,Default_Handler

  .weak I2C0_EV_IRQHandler
  .thumb_set I2C0_EV_IRQHandler,Default_Handler

  .weak I2C0_ER_IRQHandler
  .thumb_set I2C0_ER_IRQHandler,Default_Handler

  .weak I2C1_EV_IRQHandler
  .thumb_set I2C1_EV_IRQHandler,Default_Handler

  .weak I2C1_ER_IRQHandler
  .thumb_set I2C1_ER_IRQHandler,Default_Handler

  .weak SPI0_IRQHandler
  .thumb_set SPI0_IRQHandler,Default_Handler

  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler

  .weak USART0_IRQHandler
  .thumb_set USART0_IRQHandler,Default_Handler

  .weak USART1_IRQHandler
  .thumb_set USART1_IRQHandler,Default_Handler

  .weak USART2_IRQHandler
  .thumb_set USART2_IRQHandler,Default_Handler

  .weak EXTI10_15_IRQHandler
  .thumb_set EXTI10_15_IRQHandler,Default_Handler

  .weak RTC_Alarm_IRQHandler
  .thumb_set RTC_Alarm_IRQHandler,Default_Handler

  .weak VLVDF_IRQHandler
  .thumb_set VLVDF_IRQHandler,Default_Handler

  .weak TIMER15_IRQHandler
  .thumb_set TIMER15_IRQHandler,Default_Handler

  .weak TIMER16_IRQHandler
  .thumb_set TIMER16_IRQHandler,Default_Handler

  .weak SDIO_IRQHandler
  .thumb_set SDIO_IRQHandler,Default_Handler

  .weak TIMER4_IRQHandler
  .thumb_set TIMER4_IRQHandler,Default_Handler

  .weak I2C0_WKUP_IRQHandler
  .thumb_set I2C0_WKUP_IRQHandler,Default_Handler

  .weak USART0_WKUP_IRQHandler
  .thumb_set USART0_WKUP_IRQHandler,Default_Handler

  .weak USART2_WKUP_IRQHandler
  .thumb_set USART2_WKUP_IRQHandler,Default_Handler

  .weak TIMER5_IRQHandler
  .thumb_set TIMER5_IRQHandler,Default_Handler

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

  .weak DMA1_Channel6_IRQHandler
  .thumb_set DMA1_Channel6_IRQHandler,Default_Handler

  .weak DMA1_Channel7_IRQHandler
  .thumb_set DMA1_Channel7_IRQHandler,Default_Handler

  .weak WIFI11N_WKUP_IRQHandler
  .thumb_set WIFI11N_WKUP_IRQHandler,Default_Handler

  .weak USBFS_IRQHandler
  .thumb_set USBFS_IRQHandler,Default_Handler

  .weak USBFS_WKUP_IRQHandler
  .thumb_set USBFS_WKUP_IRQHandler,Default_Handler

  .weak DCI_IRQHandler
  .thumb_set DCI_IRQHandler,Default_Handler

  .weak CAU_IRQHandler
  .thumb_set CAU_IRQHandler,Default_Handler

  .weak HAU_TRNG_IRQHandler
  .thumb_set HAU_TRNG_IRQHandler,Default_Handler

  .weak FPU_IRQHandler
  .thumb_set FPU_IRQHandler,Default_Handler

  .weak HPDF_INT0_IRQHandler
  .thumb_set HPDF_INT0_IRQHandler,Default_Handler

  .weak HPDF_INT1_IRQHandler
  .thumb_set HPDF_INT1_IRQHandler,Default_Handler

  .weak WIFI11N_INT0_IRQHandler
  .thumb_set WIFI11N_INT0_IRQHandler,Default_Handler

  .weak WIFI11N_INT1_IRQHandler
  .thumb_set WIFI11N_INT1_IRQHandler,Default_Handler

  .weak WIFI11N_INT2_IRQHandler
  .thumb_set WIFI11N_INT2_IRQHandler,Default_Handler

  .weak EFUSE_IRQHandler
  .thumb_set EFUSE_IRQHandler,Default_Handler

  .weak QSPI_IRQHandler
  .thumb_set QSPI_IRQHandler,Default_Handler

  .weak PKCAU_IRQHandler
  .thumb_set PKCAU_IRQHandler,Default_Handler

  .weak TSI_IRQHandler
  .thumb_set TSI_IRQHandler,Default_Handler

  .weak ICACHE_IRQHandler
  .thumb_set ICACHE_IRQHandler,Default_Handler

  .weak TZIAC_S_IRQHandler
  .thumb_set TZIAC_S_IRQHandler,Default_Handler

  .weak FMC_S_IRQHandler
  .thumb_set FMC_S_IRQHandler,Default_Handler

  .weak QSPI_S_IRQHandler
  .thumb_set QSPI_S_IRQHandler,Default_Handler
