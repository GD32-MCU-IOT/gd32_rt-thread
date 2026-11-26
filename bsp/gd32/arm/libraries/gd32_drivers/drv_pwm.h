/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-17     RT-Thread    first implementation
 */

#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_PWM
/* gd32 pwm driver class, one device per timer */
struct gd32_pwm
{
    struct rt_device_pwm pwm_device;
    rt_uint32_t          timer_periph; /* TIMERx */
    const char          *name;
    rcu_periph_enum      timer_clk;    /* RCU_TIMERx */
    rt_uint8_t           channel_mask; /* bit0~bit3: channel 1~4 (TIMER_CH_0~3) enabled */
};

/* This function initializes the PWM pins */
rt_err_t gd32_pwm_gpio_init(rt_uint32_t timer_periph, rt_uint8_t channel_mask);
#endif /* RT_USING_PWM */

#ifdef __cplusplus
}
#endif

#endif /* __DRV_PWM_H__ */
