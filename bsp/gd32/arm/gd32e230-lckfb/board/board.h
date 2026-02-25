/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2025-01-30     RT-Thread      first implementation for GD32E230
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "gd32e23x.h"
#include "gd32e23x_exti.h"

#ifdef BSP_USING_GPIO
#include "drv_gpio.h"
#endif

#ifdef RT_USING_SERIAL
#include "drv_usart.h"
#endif

#ifdef RT_USING_SPI
#include "drv_spi.h"
#endif

#ifdef RT_USING_I2C
#include "drv_hard_i2c.h"
#endif

/* <o> Internal SRAM memory size[Kbytes] <8> */
/* <i>Default: 8 */
/* GD32E230C8T6: 64KB Flash, 8KB SRAM */
#define GD32_SRAM_SIZE         8
#define GD32_SRAM_END          (0x20000000 + GD32_SRAM_SIZE * 1024)

#ifdef __ARMCC_VERSION
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_end("HEAP"))
#else /* GCC */
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#endif

#define HEAP_END          GD32_SRAM_END

#endif

