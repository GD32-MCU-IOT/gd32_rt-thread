/*
 * Copyright (c) 2026 GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2026-07-02     Zhiwei Zhang  First version for GD32F527I-EVAL LVGL port
 */

/*
 * Minimal LVGL configuration for the GD32F527I-EVAL board.
 *
 * Only the options that differ from the LVGL v8.3 defaults are set here.
 * Every other macro falls back to its default value defined in
 * lv_conf_internal.h. The RT-Thread integration (tick source, heap,
 * assert, sprintf) is provided by lv_rt_thread_conf.h that ships with
 * the LVGL RT-Thread package.
 *
 * This file is picked up by lv_conf_internal.h through the
 * __has_include("lv_conf.h") mechanism, so the directory that contains
 * it must be on the global include path (added by the ports SConscript).
 */

#ifndef LV_CONF_H
#define LV_CONF_H

/* Pull in the RT-Thread integration (LV_TICK_CUSTOM, LV_MEM_CUSTOM, ...). */
#include "lv_rt_thread_conf.h"

/*====================
   COLOR SETTINGS
 *====================*/

/* On-board LCD is driven by the TLI in RGB565 format. */
#define LV_COLOR_DEPTH          16

/*====================
   HAL SETTINGS
 *====================*/

/* Display refresh period — 33ms matches the official GD32F527 demo.
 * The RT-Thread Kconfig default of 5ms is far too aggressive: IPA
 * transfers overlap and cause visible ghosting/tearing. */
#undef  LV_DISP_DEF_REFR_PERIOD
#define LV_DISP_DEF_REFR_PERIOD 33

/*====================
   MEMORY SETTINGS
 *====================*/

/* LVGL internal heap — 64KB, matching both official demos. */
#define LV_MEM_SIZE             (64U * 1024U)

/*====================
   RESOLUTION
 *====================*/

#define MY_DISP_HOR_RES         480
#define MY_DISP_VER_RES         272

#endif /* LV_CONF_H */
