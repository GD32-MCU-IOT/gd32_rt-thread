/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 * 2024-03-19     Evlers       remove the include of drv_usart.h
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "gd32l23x.h"
#include "drv_gpio.h"
#include "drv_hard_i2c.h"
#include "drv_usart.h"
#include "drv_spi.h"

#include "gd32l23x_exti.h"

/* Internal Flash: 256KB (0x08000000 - 0x0803FFFF) for GD32L233RC */
#define GD32_FLASH_START_ADRESS    ((uint32_t)0x08000000)
#define GD32_FLASH_SIZE            (256 * 1024)
#define GD32_FLASH_END_ADDRESS     ((uint32_t)(GD32_FLASH_START_ADRESS + GD32_FLASH_SIZE))

/* Internal SRAM memory configuration for GD32L233RC */
/* GD32L233RC series contains 32KB on-chip SRAM */
/* <o> Internal SRAM memory size[Kbytes] <8-32> */
/* <i>Default: 32 */
#ifdef __ICCARM__
/* Use *.icf ram symbol, to avoid hardcode */
extern char __ICFEDIT_region_RAM_end__;
#define GD32_SRAM_END          &__ICFEDIT_region_RAM_end__
#else 
#define GD32_SRAM_SIZE         32
#define GD32_SRAM_END          (0x20000000 + GD32_SRAM_SIZE * 1024)
#endif

/* SPI Flash CS pin definitions (software-controlled CS via GPIO) */
/* The CS pin is configured as push-pull output by rt_hw_spi_device_attach(),
   no extra GPIO setup is needed in board_msd_init.c. */
/* SPI0 CS: PD2 — shared with UART4 RX, see board_msd_init.c */
#ifndef BSP_SPI0_FLASH_CS_PIN
#define BSP_SPI0_FLASH_CS_PIN       GET_PIN(D, 2)
#endif

/* SPI1 CS: PB12 (SPI1_NSS), used as software CS together with PB13/14/15 */
#ifndef BSP_SPI1_FLASH_CS_PIN
#define BSP_SPI1_FLASH_CS_PIN       GET_PIN(B, 12)
#endif

#ifdef __ARMCC_VERSION
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#endif

#define HEAP_END          GD32_SRAM_END

#endif /* __BOARD_H__ */
