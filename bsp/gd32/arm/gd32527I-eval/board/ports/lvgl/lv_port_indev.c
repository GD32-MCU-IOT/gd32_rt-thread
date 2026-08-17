/*
 * Copyright (c) 2026 GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-02     RT-Thread    LVGL input (touch) port for GD32F527I-EVAL
 */

#include <rtthread.h>
#include <lvgl.h>

#define DBG_TAG              "lv.indev"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#ifdef BSP_USING_TOUCH
#include "drv_touch.h"
#endif

static void touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
#ifdef BSP_USING_TOUCH
    static rt_int16_t last_x = 0;
    static rt_int16_t last_y = 0;
    rt_int16_t x = 0, y = 0;

    if (gd32_touch_read(&x, &y))
    {
        last_x = x;
        last_y = y;
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }

    /* report the last known coordinates (LVGL requirement on release) */
    data->point.x = last_x;
    data->point.y = last_y;
#else
    data->state = LV_INDEV_STATE_RELEASED;
#endif
}

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    lv_indev_drv_register(&indev_drv);

    LOG_I("LVGL input port init ok");
}
