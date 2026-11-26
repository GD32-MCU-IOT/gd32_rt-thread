/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 */
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "gd32h75e_misc.h"

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

/** System Clock Configuration
*/
void SystemClock_Config(void)
{
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    NVIC_SetPriority(SysTick_IRQn, 0);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

static void mpu_config(void)
{
    mpu_region_init_struct mpu_init_struct;

    /* Guard 0x60000000-0xDFFFFFFF (unused external memory window) to stop
    * M7 speculative access from hanging cache maintenance in DMA scenarios.
    * This targets bus-stall risk during cache maintenance, not HardFault handling. */
    MPU->CTRL = 0U;

    mpu_region_struct_para_init(&mpu_init_struct);
    mpu_init_struct.region_number = MPU_REGION_NUMBER0;
    mpu_init_struct.region_base_address = 0x00000000U;
    mpu_init_struct.instruction_exec = MPU_INSTRUCTION_EXEC_PERMIT;
    mpu_init_struct.access_permission = MPU_AP_NO_ACCESS;
    mpu_init_struct.tex_type = MPU_TEX_TYPE0;
    mpu_init_struct.access_shareable = MPU_ACCESS_SHAREABLE;
    mpu_init_struct.access_cacheable = MPU_ACCESS_NON_CACHEABLE;
    mpu_init_struct.access_bufferable = MPU_ACCESS_NON_BUFFERABLE;
    mpu_init_struct.subregion_disable = 0x87U;
    mpu_init_struct.region_size = MPU_REGION_SIZE_4GB;

    mpu_region_config(&mpu_init_struct);
    mpu_region_enable();

    MPU->CTRL = MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_ENABLE_Msk;
    __DSB();
    __ISB();
}

/**
 * This function will initial GD32 board.
 */
void rt_hw_board_init()
{
    /* NVIC Configuration */
#define NVIC_VTOR_MASK              0x3FFFFF80
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x10000000 */
    SCB->VTOR  = (0x10000000 & NVIC_VTOR_MASK);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    SCB->VTOR  = (0x08000000 & NVIC_VTOR_MASK);
#endif

    SystemClock_Config();

#if defined(BSP_SCB_ENABLE_I_CACHE) || defined(BSP_SCB_ENABLE_D_CACHE)
    mpu_config();
#endif

#ifdef BSP_SCB_ENABLE_I_CACHE
    /* Enable I-Cache */
    rt_hw_cpu_icache_enable();
#endif

#ifdef BSP_SCB_ENABLE_D_CACHE
    /* Enable D-Cache */
    rt_hw_cpu_dcache_enable();
#endif

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

/*@}*/
