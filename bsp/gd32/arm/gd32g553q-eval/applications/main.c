/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-07     RT-Thread    first implementation for GD32G553Q-EVAL
 * 2024-10-09     RT-Thread    simplified main with DMA support
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* BSP driver headers for GET_PIN() */
#include "drv_gpio.h"

/* defined the LED pins according to schematic */
#define LED1_PIN    GET_PIN(E, 3)   /* LED1 on PE3 */
#define LED2_PIN    GET_PIN(E, 4)   /* LED2 on PE4 */
#define LED3_PIN    GET_PIN(E, 5)   /* LED3 on PE5 */
#define LED4_PIN    GET_PIN(E, 6)   /* LED4 on PE6 */

int main(void)
{
    /* set LED pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);

    rt_kprintf("Hello GD32G553Q-EVAL!\n");
    rt_kprintf("RT-Thread BSP adaptation successful!\n");
    rt_kprintf("System Clock: %d Hz\n", SystemCoreClock);
    rt_kprintf("\n=== DMA Adaptation Test ===\n");
    rt_kprintf("Run 'utest_run' to execute DMA tests:\n");
    rt_kprintf("  - GPIO Pin Control Test\n");
    rt_kprintf("  - I2C EEPROM DMA Test (AT24C02)\n");
    rt_kprintf("  - SPI DMA Loopback Test\n");
    rt_kprintf("  - UART DMA Echo Test\n\n");

    while (1)
    {
        /* turn on LED1 */
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        
        /* turn off LED1 */
        rt_pin_write(LED1_PIN, PIN_LOW);
        
        /* turn on LED2 */
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        
        /* turn off LED2 */
        rt_pin_write(LED2_PIN, PIN_LOW);
        
        /* turn on LED3 */
        rt_pin_write(LED3_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        
        /* turn off LED3 */
        rt_pin_write(LED3_PIN, PIN_LOW);

        /* turn on LED4 */
        rt_pin_write(LED4_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        
        /* turn off LED4 */
        rt_pin_write(LED4_PIN, PIN_LOW);
    }

    return RT_EOK;
}