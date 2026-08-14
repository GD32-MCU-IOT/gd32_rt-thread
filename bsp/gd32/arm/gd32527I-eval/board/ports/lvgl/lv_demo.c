/*
 * Copyright (c) 2026 GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-02     RT-Thread    LVGL demo entry for GD32F527I-EVAL
 */

#include <rtthread.h>
#include <lvgl.h>

#define DBG_TAG              "lv.demo"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

/*
 * lv_user_gui_init() is always called by the LVGL RT-Thread port thread, so it
 * must always be defined even when the demo UI is disabled.
 */
#if defined(BSP_USING_LVGL_DEMO)

#if LV_USE_DEMO_WIDGETS
#include "lv_demos.h"
#else

/* a small self-contained demo that also verifies the touch panel works */

static void btn_event_cb(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    static rt_uint32_t cnt = 0;

    cnt++;
    lv_label_set_text_fmt(label, "Touched: %u", cnt);
}

static void gd32_lvgl_demo(void)
{
    lv_obj_t *scr = lv_scr_act();

    /* title label centered near the top */
    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "GD32F527I-EVAL\nRT-Thread + LVGL");
    lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    /* button with a counter to prove the touch panel is alive */
    lv_obj_t *btn = lv_btn_create(scr);
    lv_obj_set_size(btn, 200, 60);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 30);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, RT_NULL);

    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Touch me");
    lv_obj_center(btn_label);
}
#endif /* LV_USE_DEMO_WIDGETS */

void lv_user_gui_init(void)
{
#if LV_USE_DEMO_WIDGETS
    lv_demo_widgets();
#else
    gd32_lvgl_demo();
#endif
    LOG_I("LVGL demo UI created");
}

#endif /* BSP_USING_LVGL_DEMO */

#if !defined(BSP_USING_LVGL_DEMO)
/*
 * The LVGL RT-Thread port thread always calls lv_user_gui_init(). Provide a
 * no-op here so the application can drive the UI on its own when the built-in
 * demo is disabled.
 */
void lv_user_gui_init(void)
{
}
#endif /* !BSP_USING_LVGL_DEMO */
