  .syntax unified
  .cpu cortex-m33
  .fpu softvfp
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
    LDR     r1, =0x20000000
    LDR     r2, =0x20000  /* 128K SRAM */
    MOV     r0, #0x00
SRAM_INIT:
    STM     r1!, {r0}
    SUBS    r2, r2, #4
    CMP     r2, #0x00
    BNE     SRAM_INIT

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
  bl entry
  bx lr

.size Reset_Handler, .-Reset_Handler

    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler

   .section  .isr_vector,"a",%progbits
   .global __gVectors



__gVectors:
                    .word _estack                                     /* Top of Stack */
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

                    /* external interrupts handler */
                    .word WWDGT_IRQHandler                        /* Vector Number 16,Window Watchdog Timer */
                    .word LVD_VAVD_VOVD_VUVD_IRQHandler           /* Vector Number 17,LVD/VAVD/VOVD/VUVD through EXTI line detect */
                    .word TAMPER_IRQHandler                       /* Vector Number 18,RTC Tamper and TimeStamp from EXTI interrupt, LXTAL clock stuck interrupt */
                    .word RTC_WKUP_IRQHandler                     /* Vector Number 19,RTC Wakeup from EXTI interrupt */
                    .word FMC_IRQHandler                          /* Vector Number 20,FMC global interrupt */
                    .word RCU_IRQHandler                          /* Vector Number 21,RCU global interrupt */
                    .word EXTI0_IRQHandler                        /* Vector Number 22,EXTI line 0 interrupt */
                    .word EXTI1_IRQHandler                        /* Vector Number 23,EXTI line 1 interrupt */
                    .word EXTI2_IRQHandler                        /* Vector Number 24,EXTI line 2 interrupt */
                    .word EXTI3_IRQHandler                        /* Vector Number 25,EXTI line 3 interrupt */
                    .word EXTI4_IRQHandler                        /* Vector Number 26,EXTI line 4 interrupt */
                    .word DMA0_Channel0_IRQHandler                /* Vector Number 27,DMA0 channel 0 global interrupt */
                    .word DMA0_Channel1_IRQHandler                /* Vector Number 28,DMA0 channel 1 global interrupt */
                    .word DMA0_Channel2_IRQHandler                /* Vector Number 29,DMA0 channel 2 global interrupt */
                    .word DMA0_Channel3_IRQHandler                /* Vector Number 30,DMA0 channel 3 global interrupt */
                    .word DMA0_Channel4_IRQHandler                /* Vector Number 31,DMA0 channel 4 global interrupt */
                    .word DMA0_Channel5_IRQHandler                /* Vector Number 32,DMA0 channel 5 global interrupt */
                    .word DMA0_Channel6_IRQHandler                /* Vector Number 33,DMA0 channel 6 global interrupt */
                    .word ADC0_1_IRQHandler                       /* Vector Number 34,ADC0 and ADC1 global interrupt */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word EXTI5_9_IRQHandler                      /* Vector Number 39,EXTI line5-9 interrupt */
                    .word TIMER0_BRK_IRQHandler                   /* Vector Number 40,TIMER0 break interrupt */
                    .word TIMER0_UP_IRQHandler                    /* Vector Number 41,TIMER0 update interrupt */
                    .word TIMER0_TRG_CMT_IDX_IRQHandler           /* Vector Number 42,TIMER0 trigger and commutation interrupt/TIMER0 direction change interrupt/TIMER0 index */
                    .word TIMER0_Channel_IRQHandler               /* Vector Number 43,TIMER0 capture compare interrupt */
                    .word TIMER1_IRQHandler                       /* Vector Number 44,TIMER1 global interrupt */
                    .word TIMER2_IRQHandler                       /* Vector Number 45,TIMER2 global interrupt */
                    .word TIMER3_IRQHandler                       /* Vector Number 46,TIMER3 global interrupt */
                    .word I2C0_EV_WKUP_IRQHandler                 /* Vector Number 47,I2C0 event interrupt and wakeup through EXTI interrupt */
                    .word I2C0_ER_IRQHandler                      /* Vector Number 48,I2C0 error interrupt */
                    .word I2C1_EV_WKUP_IRQHandler                 /* Vector Number 49,I2C1 event interrupt and wakeup through EXTI interrupt */
                    .word I2C1_ER_IRQHandler                      /* Vector Number 50,I2C1 error interrupt */
                    .word SPI0_IRQHandler                         /* Vector Number 51,SPI0 global interrupt */
                    .word SPI1_IRQHandler                         /* Vector Number 52,SPI1 global interrupt */
                    .word USART0_IRQHandler                       /* Vector Number 53,USART0 global interrupt and wakeup through EXTI line28 interrupt */
                    .word USART1_IRQHandler                       /* Vector Number 54,USART1 global interrupt and wakeup through EXTI line29 interrupt */
                    .word USART2_IRQHandler                       /* Vector Number 55,USART2 global interrupt and wakeup through EXTI line30 interrupt */
                    .word EXTI10_15_IRQHandler                    /* Vector Number 56,EXTI line10-15 interrupt */
                    .word RTC_Alarm_IRQHandler                    /* Vector Number 57,RTC alarm from EXTI line17 interrupt */
                    .word 0                                       /* Reserved */
                    .word TIMER7_BRK_TRS_IDX_IRQHandler           /* Vector Number 59,TIMER7 break interrupt/ transition error/ index error */
                    .word TIMER7_UP_IRQHandler                    /* Vector Number 60,TIMER7 update interrupt */
                    .word TIMER7_TRG_CMT_IDX_IRQHandler           /* Vector Number 61,TIMER7 trigger and commutation interrupt/direction change interrupt/index */
                    .word TIMER7_Channel_IRQHandler               /* Vector Number 62,TIMER7 capture compare interrupt */
                    .word ADC2_IRQHandler                         /* Vector Number 63,ADC2 global interrupt */
                    .word SYSCFG_IRQHandler                       /* Vector Number 64,SYSCFG interrupt */
                    .word LPTIMER_IRQHandler                      /* Vector Number 65,LPTIMER global interrupt */
                    .word TIMER4_IRQHandler                       /* Vector Number 66,TIMER4 global interrupt */
                    .word SPI2_IRQHandler                         /* Vector Number 67,SPI2 global interrupt */
                    .word UART3_IRQHandler                        /* Vector Number 68,UART3 global interrupt */
                    .word UART4_IRQHandler                        /* Vector Number 69,UART4 global interrupt */
                    .word TIMER5_DAC0_2_UDR_IRQHandler            /* Vector Number 70,TIMER5 global interrupt and DAC2 / DAC0 underrun error interrupt */
                    .word TIMER6_DAC1_3_UDR_IRQHandler            /* Vector Number 71,TIMER6 global interrupt and DAC3 / DAC1 underrun error interrupt */
                    .word DMA1_Channel0_IRQHandler                /* Vector Number 72,DMA1 channel0 global interrupt */
                    .word DMA1_Channel1_IRQHandler                /* Vector Number 73,DMA1 channel1 global interrupt */
                    .word DMA1_Channel2_IRQHandler                /* Vector Number 74,DMA1 channel2 global interrupt */
                    .word DMA1_Channel3_IRQHandler                /* Vector Number 75,DMA1 channel3 global interrupt */
                    .word DMA1_Channel4_IRQHandler                /* Vector Number 76,DMA1 channel4 global interrupt */
                    .word ADC3_IRQHandler                         /* Vector Number 77,ADC3 global interrupt */
                    .word 0                                       /* Reserved */
                    .word VUVD1_VOVD1_IRQHandler                  /* Vector Number 79,VUVD1 / VOVD1 interrupt */
                    .word CMP0_3_IRQHandler                       /* Vector Number 80,CMP0 / CMP1 / CMP2 / CMP3 through EXTI lines 20 / 21 / 22 / 23 interrupts */
                    .word CMP4_7_IRQHandler                       /* Vector Number 81,CMP4 / CMP5 / CMP6 / CMP7 through EXTI lines 24 / 36 / 37 / 38 interrupts */
                    .word CMP_IRQHandler                          /* Vector Number 82,CMP global interrupt */
                    .word HRTIMER_IRQ0_IRQHandler                 /* Vector Number 83,HRTIMER interrupt0 */
                    .word HRTIMER_IRQ1_IRQHandler                 /* Vector Number 84,HRTIMER interrupt1 */
                    .word HRTIMER_IRQ2_IRQHandler                 /* Vector Number 85,HRTIMER interrupt2 */
                    .word HRTIMER_IRQ3_IRQHandler                 /* Vector Number 86,HRTIMER interrupt3 */
                    .word HRTIMER_IRQ4_IRQHandler                 /* Vector Number 87,HRTIMER interrupt4 */
                    .word HRTIMER_IRQ5_IRQHandler                 /* Vector Number 88,HRTIMER interrupt5 */
                    .word HRTIMER_IRQ6_IRQHandler                 /* Vector Number 89,HRTIMER interrupt6 */
                    .word HRTIMER_IRQ7_IRQHandler                 /* Vector Number 90,HRTIMER interrupt7 */
                    .word HRTIMER_IRQ8_IRQHandler                 /* Vector Number 91,HRTIMER interrupt8 */
                    .word HRTIMER_IRQ9_IRQHandler                 /* Vector Number 92,HRTIMER interrupt9 */
                    .word TIMER19_BRK_TRS_IDX_IRQHandler          /* Vector Number 93,TIMER19 break interrupt / TIMER19 transition error / TIMER19 Index error */
                    .word TIMER19_UP_IRQHandler                   /* Vector Number 94,TIMER19 update interrupt */
                    .word TIMER19_TRG_CMT_IDX_IRQHandler          /* Vector Number 95,TIMER19 trigger and commutation interrupt / TIMER19 direction change interrupt / TIMER19 index */
                    .word TIMER19_Channel_IRQHandler              /* Vector Number 96,TIMER19 capture compare interrupt */
                    .word FPU_IRQHandler                          /* Vector Number 97,FPU global interrupt */
                    .word I2C2_EV_WKUP_IRQHandler                 /* Vector Number 98,I2C2 event interrupt and I2C2 wakeup through EXTI interrupt */
                    .word I2C2_ER_IRQHandler                      /* Vector Number 99,I2C2 error interrupt */
                    .word 0                                       /* Reserved */
                    .word CAU_IRQHandler                          /* Vector Number 101,CAU global interrupt */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word TRNG_IRQHandler                         /* Vector Number 106,TRNG global interrupt */
                    .word 0                                       /* Reserved */
                    .word I2C3_EV_WKUP_IRQHandler                 /* Vector Number 108,I2C3 event interrupt and I2C3 wakeup through EXTI line34 interrupt */
                    .word I2C3_ER_IRQHandler                      /* Vector Number 109,I2C3 error interrupt */
                    .word DMAMUX_OVR_IRQHandler                   /* Vector Number 110,DMAMUX overrun interrupt */
                    .word QSPI_IRQHandler                         /* Vector Number 111,QSPI global interrupt */
                    .word FFT_IRQHandler                          /* Vector Number 112,FFT global interrupt */
                    .word DMA1_Channel5_IRQHandler                /* Vector Number 113,DMA1 channel5 global interrupt */
                    .word DMA1_Channel6_IRQHandler                /* Vector Number 114,DMA1 channel6 global interrupt */
                    .word CLA_IRQHandler                          /* Vector Number 115,CLA interrupt */
                    .word TMU_IRQHandler                          /* Vector Number 116,TMU interrupt */
                    .word FAC_IRQHandler                          /* Vector Number 117,FAC interrupt */
                    .word HPDF_INT0_IRQHandler                    /* Vector Number 118,HPDF global interrupt 0 */
                    .word HPDF_INT1_IRQHandler                    /* Vector Number 119,HPDF global interrupt 1 */
                    .word HPDF_INT2_IRQHandler                    /* Vector Number 120,HPDF global interrupt 2 */
                    .word HPDF_INT3_IRQHandler                    /* Vector Number 121,HPDF global interrupt 3 */
                    .word TIMER14_IRQHandler                      /* Vector Number 122,TIMER14 global interrupt */
                    .word TIMER15_IRQHandler                      /* Vector Number 123,TIMER15 global interrupt */
                    .word TIMER16_IRQHandler                      /* Vector Number 124,TIMER16 global interrupt */
                    .word CAN0_WKUP_IRQHandler                    /* Vector Number 125,CAN0 wakeup through EXTI line25 interrupt */
                    .word CAN0_Message_IRQHandler                 /* Vector Number 126,CAN0 interrupt for message buffer */
                    .word CAN0_Busoff_IRQHandler                  /* Vector Number 127,CAN0 interrupt for bus off / bus off done */
                    .word CAN0_Error_IRQHandler                   /* Vector Number 128,CAN0 interrupt for error */
                    .word CAN0_FastError_IRQHandler               /* Vector Number 129,CAN0 interrupt for error in fast transmission */
                    .word CAN0_TEC_IRQHandler                     /* Vector Number 130,CAN0 interrupt for transmit warning */
                    .word CAN0_REC_IRQHandler                     /* Vector Number 131,CAN0 interrupt for receive warning */
                    .word CAN1_WKUP_IRQHandler                    /* Vector Number 132,CAN1 wakeup through EXTI line26 interrupt */
                    .word CAN1_Message_IRQHandler                 /* Vector Number 133,CAN1 interrupt for message buffer */
                    .word CAN1_Busoff_IRQHandler                  /* Vector Number 134,CAN1 interrupt for bus off / Bus off done */
                    .word CAN1_Error_IRQHandler                   /* Vector Number 135,CAN1 interrupt for error */
                    .word CAN1_FastError_IRQHandler               /* Vector Number 136,CAN1 interrupt for error in fast transmission */
                    .word CAN1_TEC_IRQHandler                     /* Vector Number 137,CAN1 interrupt for transmit warning */
                    .word CAN1_REC_IRQHandler                     /* Vector Number 138,CAN1 interrupt for receive warning */
                    .word CAN2_WKUP_IRQHandler                    /* Vector Number 139,CAN2 wakeup through EXTI line27 interrupt */
                    .word CAN2_Message_IRQHandler                 /* Vector Number 140,CAN2 interrupt for message buffer */
                    .word CAN2_Busoff_IRQHandler                  /* Vector Number 141,CAN2 interrupt for bus off / Bus off done */
                    .word CAN2_Error_IRQHandler                   /* Vector Number 142,CAN2 interrupt for error */
                    .word CAN2_FastError_IRQHandler               /* Vector Number 143,CAN2 interrupt for error in fast transmission */
                    .word CAN2_TEC_IRQHandler                     /* Vector Number 144,CAN2 interrupt for transmit warning */
                    .word CAN2_REC_IRQHandler                     /* Vector Number 145,CAN2 interrupt for receive warning */
                    .word TIMER0_DEC_IRQHandler                   /* Vector Number 146,TIMER0 DEC interrupt */
                    .word TIMER1_DEC_IRQHandler                   /* Vector Number 147,TIMER1 DEC interrupt */
                    .word TIMER2_DEC_IRQHandler                   /* Vector Number 148,TIMER2 DEC interrupt */
                    .word TIMER3_DEC_IRQHandler                   /* Vector Number 149,TIMER3 DEC interrupt */
                    .word TIMER4_DEC_IRQHandler                   /* Vector Number 150,TIMER4 DEC interrupt */
                    .word TIMER7_DEC_IRQHandler                   /* Vector Number 151,TIMER7 DEC interrupt */
                    .word TIMER19_DEC_IRQHandler                  /* Vector Number 152,TIMER19 DEC interrupt */

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

  .weak LVD_VAVD_VOVD_VUVD_IRQHandler
  .thumb_set LVD_VAVD_VOVD_VUVD_IRQHandler,Default_Handler

  .weak TAMPER_IRQHandler
  .thumb_set TAMPER_IRQHandler,Default_Handler

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

  .weak ADC0_1_IRQHandler
  .thumb_set ADC0_1_IRQHandler,Default_Handler

  .weak EXTI5_9_IRQHandler
  .thumb_set EXTI5_9_IRQHandler,Default_Handler

  .weak TIMER0_BRK_IRQHandler
  .thumb_set TIMER0_BRK_IRQHandler,Default_Handler

  .weak TIMER0_UP_IRQHandler
  .thumb_set TIMER0_UP_IRQHandler,Default_Handler

  .weak TIMER0_TRG_CMT_IDX_IRQHandler
  .thumb_set TIMER0_TRG_CMT_IDX_IRQHandler,Default_Handler

  .weak TIMER0_Channel_IRQHandler
  .thumb_set TIMER0_Channel_IRQHandler,Default_Handler

  .weak TIMER1_IRQHandler
  .thumb_set TIMER1_IRQHandler,Default_Handler

  .weak TIMER2_IRQHandler
  .thumb_set TIMER2_IRQHandler,Default_Handler

  .weak TIMER3_IRQHandler
  .thumb_set TIMER3_IRQHandler,Default_Handler

  .weak I2C0_EV_WKUP_IRQHandler
  .thumb_set I2C0_EV_WKUP_IRQHandler,Default_Handler

  .weak I2C0_ER_IRQHandler
  .thumb_set I2C0_ER_IRQHandler,Default_Handler

  .weak I2C1_EV_WKUP_IRQHandler
  .thumb_set I2C1_EV_WKUP_IRQHandler,Default_Handler

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

  .weak TIMER7_BRK_TRS_IDX_IRQHandler
  .thumb_set TIMER7_BRK_TRS_IDX_IRQHandler,Default_Handler

  .weak TIMER7_UP_IRQHandler
  .thumb_set TIMER7_UP_IRQHandler,Default_Handler

  .weak TIMER7_TRG_CMT_IDX_IRQHandler
  .thumb_set TIMER7_TRG_CMT_IDX_IRQHandler,Default_Handler

  .weak TIMER7_Channel_IRQHandler
  .thumb_set TIMER7_Channel_IRQHandler,Default_Handler

  .weak ADC2_IRQHandler
  .thumb_set ADC2_IRQHandler,Default_Handler

  .weak SYSCFG_IRQHandler
  .thumb_set SYSCFG_IRQHandler,Default_Handler

  .weak LPTIMER_IRQHandler
  .thumb_set LPTIMER_IRQHandler,Default_Handler

  .weak TIMER4_IRQHandler
  .thumb_set TIMER4_IRQHandler,Default_Handler

  .weak SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Default_Handler

  .weak UART3_IRQHandler
  .thumb_set UART3_IRQHandler,Default_Handler

  .weak UART4_IRQHandler
  .thumb_set UART4_IRQHandler,Default_Handler

  .weak TIMER5_DAC0_2_UDR_IRQHandler
  .thumb_set TIMER5_DAC0_2_UDR_IRQHandler,Default_Handler

  .weak TIMER6_DAC1_3_UDR_IRQHandler
  .thumb_set TIMER6_DAC1_3_UDR_IRQHandler,Default_Handler

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

  .weak ADC3_IRQHandler
  .thumb_set ADC3_IRQHandler,Default_Handler

  .weak VUVD1_VOVD1_IRQHandler
  .thumb_set VUVD1_VOVD1_IRQHandler,Default_Handler

  .weak CMP0_3_IRQHandler
  .thumb_set CMP0_3_IRQHandler,Default_Handler

  .weak CMP4_7_IRQHandler
  .thumb_set CMP4_7_IRQHandler,Default_Handler

  .weak CMP_IRQHandler
  .thumb_set CMP_IRQHandler,Default_Handler

  .weak HRTIMER_IRQ0_IRQHandler
  .thumb_set HRTIMER_IRQ0_IRQHandler,Default_Handler

  .weak HRTIMER_IRQ1_IRQHandler
  .thumb_set HRTIMER_IRQ1_IRQHandler,Default_Handler

  .weak HRTIMER_IRQ2_IRQHandler
  .thumb_set HRTIMER_IRQ2_IRQHandler,Default_Handler

  .weak HRTIMER_IRQ3_IRQHandler
  .thumb_set HRTIMER_IRQ3_IRQHandler,Default_Handler

  .weak HRTIMER_IRQ4_IRQHandler
  .thumb_set HRTIMER_IRQ4_IRQHandler,Default_Handler

  .weak HRTIMER_IRQ5_IRQHandler
  .thumb_set HRTIMER_IRQ5_IRQHandler,Default_Handler

  .weak HRTIMER_IRQ6_IRQHandler
  .thumb_set HRTIMER_IRQ6_IRQHandler,Default_Handler

  .weak HRTIMER_IRQ7_IRQHandler
  .thumb_set HRTIMER_IRQ7_IRQHandler,Default_Handler

  .weak HRTIMER_IRQ8_IRQHandler
  .thumb_set HRTIMER_IRQ8_IRQHandler,Default_Handler

  .weak HRTIMER_IRQ9_IRQHandler
  .thumb_set HRTIMER_IRQ9_IRQHandler,Default_Handler

  .weak TIMER19_BRK_TRS_IDX_IRQHandler
  .thumb_set TIMER19_BRK_TRS_IDX_IRQHandler,Default_Handler

  .weak TIMER19_UP_IRQHandler
  .thumb_set TIMER19_UP_IRQHandler,Default_Handler

  .weak TIMER19_TRG_CMT_IDX_IRQHandler
  .thumb_set TIMER19_TRG_CMT_IDX_IRQHandler,Default_Handler

  .weak TIMER19_Channel_IRQHandler
  .thumb_set TIMER19_Channel_IRQHandler,Default_Handler

  .weak FPU_IRQHandler
  .thumb_set FPU_IRQHandler,Default_Handler

  .weak I2C2_EV_WKUP_IRQHandler
  .thumb_set I2C2_EV_WKUP_IRQHandler,Default_Handler

  .weak I2C2_ER_IRQHandler
  .thumb_set I2C2_ER_IRQHandler,Default_Handler

  .weak CAU_IRQHandler
  .thumb_set CAU_IRQHandler,Default_Handler

  .weak TRNG_IRQHandler
  .thumb_set TRNG_IRQHandler,Default_Handler

  .weak I2C3_EV_WKUP_IRQHandler
  .thumb_set I2C3_EV_WKUP_IRQHandler,Default_Handler

  .weak I2C3_ER_IRQHandler
  .thumb_set I2C3_ER_IRQHandler,Default_Handler

  .weak DMAMUX_OVR_IRQHandler
  .thumb_set DMAMUX_OVR_IRQHandler,Default_Handler

  .weak QSPI_IRQHandler
  .thumb_set QSPI_IRQHandler,Default_Handler

  .weak FFT_IRQHandler
  .thumb_set FFT_IRQHandler,Default_Handler

  .weak DMA1_Channel5_IRQHandler
  .thumb_set DMA1_Channel5_IRQHandler,Default_Handler

  .weak DMA1_Channel6_IRQHandler
  .thumb_set DMA1_Channel6_IRQHandler,Default_Handler

  .weak CLA_IRQHandler
  .thumb_set CLA_IRQHandler,Default_Handler

  .weak TMU_IRQHandler
  .thumb_set TMU_IRQHandler,Default_Handler

  .weak FAC_IRQHandler
  .thumb_set FAC_IRQHandler,Default_Handler

  .weak HPDF_INT0_IRQHandler
  .thumb_set HPDF_INT0_IRQHandler,Default_Handler

  .weak HPDF_INT1_IRQHandler
  .thumb_set HPDF_INT1_IRQHandler,Default_Handler

  .weak HPDF_INT2_IRQHandler
  .thumb_set HPDF_INT2_IRQHandler,Default_Handler

  .weak HPDF_INT3_IRQHandler
  .thumb_set HPDF_INT3_IRQHandler,Default_Handler

  .weak TIMER14_IRQHandler
  .thumb_set TIMER14_IRQHandler,Default_Handler

  .weak TIMER15_IRQHandler
  .thumb_set TIMER15_IRQHandler,Default_Handler

  .weak TIMER16_IRQHandler
  .thumb_set TIMER16_IRQHandler,Default_Handler

  .weak CAN0_WKUP_IRQHandler
  .thumb_set CAN0_WKUP_IRQHandler,Default_Handler

  .weak CAN0_Message_IRQHandler
  .thumb_set CAN0_Message_IRQHandler,Default_Handler

  .weak CAN0_Busoff_IRQHandler
  .thumb_set CAN0_Busoff_IRQHandler,Default_Handler

  .weak CAN0_Error_IRQHandler
  .thumb_set CAN0_Error_IRQHandler,Default_Handler

  .weak CAN0_FastError_IRQHandler
  .thumb_set CAN0_FastError_IRQHandler,Default_Handler

  .weak CAN0_TEC_IRQHandler
  .thumb_set CAN0_TEC_IRQHandler,Default_Handler

  .weak CAN0_REC_IRQHandler
  .thumb_set CAN0_REC_IRQHandler,Default_Handler

  .weak CAN1_WKUP_IRQHandler
  .thumb_set CAN1_WKUP_IRQHandler,Default_Handler

  .weak CAN1_Message_IRQHandler
  .thumb_set CAN1_Message_IRQHandler,Default_Handler

  .weak CAN1_Busoff_IRQHandler
  .thumb_set CAN1_Busoff_IRQHandler,Default_Handler

  .weak CAN1_Error_IRQHandler
  .thumb_set CAN1_Error_IRQHandler,Default_Handler

  .weak CAN1_FastError_IRQHandler
  .thumb_set CAN1_FastError_IRQHandler,Default_Handler

  .weak CAN1_TEC_IRQHandler
  .thumb_set CAN1_TEC_IRQHandler,Default_Handler

  .weak CAN1_REC_IRQHandler
  .thumb_set CAN1_REC_IRQHandler,Default_Handler

  .weak CAN2_WKUP_IRQHandler
  .thumb_set CAN2_WKUP_IRQHandler,Default_Handler

  .weak CAN2_Message_IRQHandler
  .thumb_set CAN2_Message_IRQHandler,Default_Handler

  .weak CAN2_Busoff_IRQHandler
  .thumb_set CAN2_Busoff_IRQHandler,Default_Handler

  .weak CAN2_Error_IRQHandler
  .thumb_set CAN2_Error_IRQHandler,Default_Handler

  .weak CAN2_FastError_IRQHandler
  .thumb_set CAN2_FastError_IRQHandler,Default_Handler

  .weak CAN2_TEC_IRQHandler
  .thumb_set CAN2_TEC_IRQHandler,Default_Handler

  .weak CAN2_REC_IRQHandler
  .thumb_set CAN2_REC_IRQHandler,Default_Handler

  .weak TIMER0_DEC_IRQHandler
  .thumb_set TIMER0_DEC_IRQHandler,Default_Handler

  .weak TIMER1_DEC_IRQHandler
  .thumb_set TIMER1_DEC_IRQHandler,Default_Handler

  .weak TIMER2_DEC_IRQHandler
  .thumb_set TIMER2_DEC_IRQHandler,Default_Handler

  .weak TIMER3_DEC_IRQHandler
  .thumb_set TIMER3_DEC_IRQHandler,Default_Handler

  .weak TIMER4_DEC_IRQHandler
  .thumb_set TIMER4_DEC_IRQHandler,Default_Handler

  .weak TIMER7_DEC_IRQHandler
  .thumb_set TIMER7_DEC_IRQHandler,Default_Handler

  .weak TIMER19_DEC_IRQHandler
  .thumb_set TIMER19_DEC_IRQHandler,Default_Handler

