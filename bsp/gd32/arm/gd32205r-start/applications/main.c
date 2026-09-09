/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 * 2026-08-06     simplify: keep LED blink and startup banner only
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* PC6 is connected to the board status LED. */
#define LED_PIN GET_PIN(C, 6)

int main(void)
{
    rt_kprintf("\r\n");
    rt_kprintf("GD32F205R-START RT-Thread BSP\r\n");
    rt_kprintf("System clock: %lu Hz\r\n", (unsigned long)SystemCoreClock);
    rt_kprintf("UART1 console and MSH are ready.\r\n");

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
