/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-22     RT-Thread    first implementation for GD32F50x
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "gd32f50x_rcu.h"

/* Function declarations */
#ifdef RT_USING_PIN
extern int rt_hw_pin_init(void);
#endif

#ifdef RT_USING_SERIAL
extern int rt_hw_usart_init(void);
#endif

#ifdef RT_USING_I2C
extern int rt_hw_i2c_init(void);
#endif

/**
 * @brief  System Clock Configuration - Configure to 120MHz
 * @param  None  
 * @retval None
 */
void SystemClock_Config(void)
{
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    NVIC_SetPriority(SysTick_IRQn, 0);
}

/**
 * This is the timer interrupt service routine.
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initial GD32 board.
 */
void rt_hw_board_init()
{
    /* NVIC Configuration */
#define NVIC_VTOR_MASK              0x3FFFFF80
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x20000000 */
    SCB->VTOR  = (0x20000000 & NVIC_VTOR_MASK);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    SCB->VTOR  = (0x08000000 & NVIC_VTOR_MASK);
#endif

    SystemClock_Config();

// #ifdef RT_USING_PIN
//     rt_hw_pin_init();
// #endif

#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler */
    /* User can add his own implementation to report the HAL error return state */
    while (1)
    {
    }
    /* USER CODE END Error_Handler */
}
