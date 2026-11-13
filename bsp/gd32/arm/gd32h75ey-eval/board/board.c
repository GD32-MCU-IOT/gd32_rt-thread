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

#if defined(SOC_SERIES_GD32H75E)
static void mpu_config(void)
{
    /* Guard 0x60000000-0xDFFFFFFF (unused external memory window) to stop
     * M7 speculative access from hanging cache maintenance in DMA scenarios. */
    MPU->CTRL = 0U;
    MPU->RNR = 0U;
    MPU->RBAR = 0x00000000U;
    MPU->RASR =
        (0U << MPU_RASR_XN_Pos) |
        (0U << MPU_RASR_AP_Pos) |
        (0U << MPU_RASR_TEX_Pos) |
        (1U << MPU_RASR_S_Pos) |
        (0U << MPU_RASR_C_Pos) |
        (0U << MPU_RASR_B_Pos) |
        (0x87U << MPU_RASR_SRD_Pos) |
        (31U << MPU_RASR_SIZE_Pos) |
        (1U << MPU_RASR_ENABLE_Pos);
    MPU->CTRL = MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_ENABLE_Msk;
    __DSB();
    __ISB();
}
#endif

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

#if defined(SOC_SERIES_GD32H75E)
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
