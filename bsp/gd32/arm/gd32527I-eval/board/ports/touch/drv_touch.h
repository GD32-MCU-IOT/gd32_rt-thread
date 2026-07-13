/*
 * Copyright (c) 2026 GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-02     RT-Thread    resistive touch panel driver for GD32F527I-EVAL
 */

#ifndef __DRV_TOUCH_H__
#define __DRV_TOUCH_H__

#include <rtthread.h>

/*
 * Read the current touch position mapped to LCD coordinates.
 *
 * out_x / out_y : receive the LCD pixel coordinates when the panel is pressed.
 * return        : RT_TRUE  - the panel is being touched, coordinates are valid
 *                 RT_FALSE - the panel is released, coordinates untouched
 */
rt_bool_t gd32_touch_read(rt_int16_t *out_x, rt_int16_t *out_y);

#endif /* __DRV_TOUCH_H__ */
