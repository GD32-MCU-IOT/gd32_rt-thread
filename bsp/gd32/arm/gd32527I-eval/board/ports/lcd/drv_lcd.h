/*
 * Copyright (c) 2026 GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-02     RT-Thread    TLI RGB565 LCD driver for GD32F527I-EVAL
 */

#ifndef __DRV_LCD_H__
#define __DRV_LCD_H__

#include <rtthread.h>
#include <board.h>

/* GD32F527I-EVAL on-board 4.3" RGB LCD (480x272, RGB565) driven by TLI */
#define LCD_WIDTH               480
#define LCD_HEIGHT              272
#define LCD_BITS_PER_PIXEL      16
#define LCD_BYTES_PER_PIXEL     (LCD_BITS_PER_PIXEL / 8)

/* the framebuffer scanned by TLI layer0 lives at the beginning of the SDRAM */
#define LCD_FB_ADDR             (EXT_SDRAM_BEGIN)
#define LCD_FB_SIZE             (LCD_WIDTH * LCD_HEIGHT * LCD_BYTES_PER_PIXEL)

/* graphic device name registered with the RT-Thread device framework */
#define LCD_DEVICE_NAME         "lcd"

#endif /* __DRV_LCD_H__ */
