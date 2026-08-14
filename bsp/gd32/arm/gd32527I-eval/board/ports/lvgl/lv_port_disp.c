/*
 * Copyright (c) 2026 GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-02     RT-Thread    LVGL display port for GD32F527I-EVAL (TLI RGB565)
 * 2026-07-09     RT-Thread    Rewrite to pingpong full_refresh TLI mode
 *                             matching the official lvgl_f527 demo
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <lvgl.h>
#include "drv_lcd.h"
#include "gd32f5xx.h"
#include "gd32f5xx_tli.h"

#define DBG_TAG              "lv.disp"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

/*
 * Pingpong full_refresh mode — matches the official lvgl_f527 demo.
 *
 * Two full-screen draw buffers live in SDRAM (back-to-back at 0xC0000000).
 * LVGL renders a complete frame into one buffer, then disp_flush() switches
 * the TLI layer0 framebuffer address to that buffer.  The TLI hardware
 * scans it out to the LCD panel.  When the TLI finishes one frame (line
 * mark interrupt), it notifies LVGL that the flush is done, and LVGL can
 * start rendering the next frame into the *other* buffer.
 *
 * This eliminates all tearing/ghosting because the TLI never reads from a
 * buffer that LVGL is currently writing to — they always alternate.
 */

#define SDRAM_BASE_ADDR     ((uint32_t)0xC0000000)
#define DISP_HOR_RES        LCD_WIDTH
#define DISP_VER_RES        LCD_HEIGHT
#define DISP_BUF_SIZE       (DISP_HOR_RES * DISP_VER_RES)

/* Two full-screen buffers in SDRAM, back-to-back */
static lv_color_t *buf_2_1 = (lv_color_t *)SDRAM_BASE_ADDR;
static lv_color_t *buf_2_2 = (lv_color_t *)(SDRAM_BASE_ADDR + DISP_HOR_RES * DISP_VER_RES * 2);

/* saved driver pointer for the TLI line-mark ISR */
static lv_disp_drv_t *g_disp_drv = RT_NULL;

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    /* Switch TLI layer0 framebuffer to the buffer LVGL just finished rendering.
     * tli_reload_config ensures the change takes effect at the next vertical
     * blanking interval (no mid-frame tearing). */
    TLI_LxFBADDR(LAYER0) = (uint32_t)color_p;
    tli_reload_config(TLI_REQUEST_RELOAD_EN);

    /* Set a line mark at the last line — TLI will fire an interrupt when
     * it finishes scanning this frame, then we tell LVGL it's done. */
    tli_line_mark_set(DISP_VER_RES - 1);
    g_disp_drv = disp_drv;
    tli_interrupt_enable(TLI_INT_LM);
}

/* TLI line-mark interrupt — fires when TLI finishes scanning one frame */
void TLI_IRQHandler(void)
{
    rt_interrupt_enter();

    if (RESET != tli_interrupt_flag_get(TLI_INT_FLAG_LM))
    {
        tli_interrupt_flag_clear(TLI_INT_FLAG_LM);
        tli_interrupt_disable(TLI_INT_LM);

        if (g_disp_drv != RT_NULL)
        {
            lv_disp_flush_ready(g_disp_drv);
        }
    }

    rt_interrupt_leave();
}

static void disp_clean_dcache(lv_disp_drv_t *disp_drv)
{
    /* Cortex-M33 DCache is not enabled in this BSP; no-op */
}

void lv_port_disp_init(void)
{
    static lv_disp_draw_buf_t draw_buf_dsc;
    static lv_disp_drv_t disp_drv;

    /* Initialize the draw buffer with two full-screen SDRAM buffers */
    lv_disp_draw_buf_init(&draw_buf_dsc,
                          (void *)buf_2_1,
                          (void *)buf_2_2,
                          DISP_BUF_SIZE);

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res      = DISP_HOR_RES;
    disp_drv.ver_res      = DISP_VER_RES;
    disp_drv.flush_cb     = disp_flush;
    disp_drv.draw_buf     = &draw_buf_dsc;
    disp_drv.full_refresh = 1;  /* tell LVGL to always redraw the whole screen */
    disp_drv.clean_dcache_cb = disp_clean_dcache;
    lv_disp_drv_register(&disp_drv);

    /* Enable TLI line-mark interrupt */
    nvic_irq_enable(TLI_IRQn, 2, 0);

    LOG_I("LVGL display port init ok (pingpong full_refresh TLI mode)");
}
