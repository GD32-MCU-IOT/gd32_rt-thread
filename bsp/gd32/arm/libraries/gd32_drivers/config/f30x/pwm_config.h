/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GD32_PWM_CHANNEL_1_BIT          ((rt_uint8_t)(1U << 0))
#define GD32_PWM_CHANNEL_2_BIT          ((rt_uint8_t)(1U << 1))
#define GD32_PWM_CHANNEL_3_BIT          ((rt_uint8_t)(1U << 2))
#define GD32_PWM_CHANNEL_4_BIT          ((rt_uint8_t)(1U << 3))

#if defined(BSP_USING_PWM0_CH1)
#define PWM0_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM0_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM0_CH2)
#define PWM0_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM0_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM0_CH3)
#define PWM0_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM0_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM0_CH4)
#define PWM0_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM0_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM1_CH1)
#define PWM1_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM1_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM1_CH2)
#define PWM1_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM1_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM1_CH3)
#define PWM1_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM1_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM1_CH4)
#define PWM1_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM1_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM2_CH1)
#define PWM2_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM2_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM2_CH2)
#define PWM2_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM2_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM2_CH3)
#define PWM2_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM2_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM2_CH4)
#define PWM2_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM2_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM3_CH1)
#define PWM3_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM3_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM3_CH2)
#define PWM3_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM3_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM3_CH3)
#define PWM3_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM3_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM3_CH4)
#define PWM3_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM3_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM4_CH1)
#define PWM4_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM4_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM4_CH2)
#define PWM4_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM4_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM4_CH3)
#define PWM4_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM4_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM4_CH4)
#define PWM4_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM4_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM5_CH1)
#define PWM5_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM5_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM5_CH2)
#define PWM5_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM5_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM5_CH3)
#define PWM5_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM5_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM5_CH4)
#define PWM5_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM5_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM6_CH1)
#define PWM6_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM6_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM6_CH2)
#define PWM6_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM6_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM6_CH3)
#define PWM6_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM6_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM6_CH4)
#define PWM6_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM6_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM7_CH1)
#define PWM7_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM7_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM7_CH2)
#define PWM7_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM7_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM7_CH3)
#define PWM7_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM7_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM7_CH4)
#define PWM7_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM7_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM8_CH1)
#define PWM8_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM8_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM8_CH2)
#define PWM8_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM8_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM9_CH1)
#define PWM9_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM9_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM10_CH1)
#define PWM10_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM10_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM11_CH1)
#define PWM11_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM11_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM11_CH2)
#define PWM11_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM11_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM12_CH1)
#define PWM12_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM12_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM13_CH1)
#define PWM13_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM13_CHANNEL_1_MASK 0U
#endif

#ifdef BSP_USING_PWM0
#ifndef PWM0_CONFIG
#define PWM0_CONFIG                                  \
    {                                                \
        .timer_periph = TIMER0,                      \
        .name = "pwm0",                              \
        .timer_clk = RCU_TIMER0,                     \
        .channel_mask = (rt_uint8_t)(                \
            PWM0_CHANNEL_1_MASK |                    \
            PWM0_CHANNEL_2_MASK |                    \
            PWM0_CHANNEL_3_MASK |                    \
            PWM0_CHANNEL_4_MASK),                    \
    }
#endif
#endif

#ifdef BSP_USING_PWM1
#ifndef PWM1_CONFIG
#define PWM1_CONFIG                                  \
    {                                                \
        .timer_periph = TIMER1,                      \
        .name = "pwm1",                              \
        .timer_clk = RCU_TIMER1,                     \
        .channel_mask = (rt_uint8_t)(                \
            PWM1_CHANNEL_1_MASK |                    \
            PWM1_CHANNEL_2_MASK |                    \
            PWM1_CHANNEL_3_MASK |                    \
            PWM1_CHANNEL_4_MASK),                    \
    }
#endif
#endif

#ifdef BSP_USING_PWM2
#ifndef PWM2_CONFIG
#define PWM2_CONFIG                                  \
    {                                                \
        .timer_periph = TIMER2,                      \
        .name = "pwm2",                              \
        .timer_clk = RCU_TIMER2,                     \
        .channel_mask = (rt_uint8_t)(                \
            PWM2_CHANNEL_1_MASK |                    \
            PWM2_CHANNEL_2_MASK |                    \
            PWM2_CHANNEL_3_MASK |                    \
            PWM2_CHANNEL_4_MASK),                    \
    }
#endif
#endif

#ifdef BSP_USING_PWM3
#ifndef PWM3_CONFIG
#define PWM3_CONFIG                                  \
    {                                                \
        .timer_periph = TIMER3,                      \
        .name = "pwm3",                              \
        .timer_clk = RCU_TIMER3,                     \
        .channel_mask = (rt_uint8_t)(                \
            PWM3_CHANNEL_1_MASK |                    \
            PWM3_CHANNEL_2_MASK |                    \
            PWM3_CHANNEL_3_MASK |                    \
            PWM3_CHANNEL_4_MASK),                    \
    }
#endif
#endif

#ifdef BSP_USING_PWM4
#ifndef PWM4_CONFIG
#define PWM4_CONFIG                                  \
    {                                                \
        .timer_periph = TIMER4,                      \
        .name = "pwm4",                              \
        .timer_clk = RCU_TIMER4,                     \
        .channel_mask = (rt_uint8_t)(                \
            PWM4_CHANNEL_1_MASK |                    \
            PWM4_CHANNEL_2_MASK |                    \
            PWM4_CHANNEL_3_MASK |                    \
            PWM4_CHANNEL_4_MASK),                    \
    }
#endif
#endif

#ifdef BSP_USING_PWM5
#ifndef PWM5_CONFIG
#define PWM5_CONFIG                                  \
    {                                                \
        .timer_periph = TIMER5,                      \
        .name = "pwm5",                              \
        .timer_clk = RCU_TIMER5,                     \
        .channel_mask = (rt_uint8_t)(                \
            PWM5_CHANNEL_1_MASK |                    \
            PWM5_CHANNEL_2_MASK |                    \
            PWM5_CHANNEL_3_MASK |                    \
            PWM5_CHANNEL_4_MASK),                    \
    }
#endif
#endif

#ifdef BSP_USING_PWM6
#ifndef PWM6_CONFIG
#define PWM6_CONFIG                                  \
    {                                                \
        .timer_periph = TIMER6,                      \
        .name = "pwm6",                              \
        .timer_clk = RCU_TIMER6,                     \
        .channel_mask = (rt_uint8_t)(                \
            PWM6_CHANNEL_1_MASK |                    \
            PWM6_CHANNEL_2_MASK |                    \
            PWM6_CHANNEL_3_MASK |                    \
            PWM6_CHANNEL_4_MASK),                    \
    }
#endif
#endif

#ifdef BSP_USING_PWM7
#ifndef PWM7_CONFIG
#define PWM7_CONFIG                                  \
    {                                                \
        .timer_periph = TIMER7,                      \
        .name = "pwm7",                              \
        .timer_clk = RCU_TIMER7,                     \
        .channel_mask = (rt_uint8_t)(                \
            PWM7_CHANNEL_1_MASK |                    \
            PWM7_CHANNEL_2_MASK |                    \
            PWM7_CHANNEL_3_MASK |                    \
            PWM7_CHANNEL_4_MASK),                    \
    }
#endif
#endif

#ifdef BSP_USING_PWM8
#ifndef PWM8_CONFIG
#define PWM8_CONFIG                                  \
    {                                                \
        .timer_periph = TIMER8,                      \
        .name = "pwm8",                              \
        .timer_clk = RCU_TIMER8,                     \
        .channel_mask = (rt_uint8_t)(                \
            PWM8_CHANNEL_1_MASK |                    \
            PWM8_CHANNEL_2_MASK),                    \
    }
#endif
#endif

#ifdef BSP_USING_PWM9
#ifndef PWM9_CONFIG
#define PWM9_CONFIG                                  \
    {                                                \
        .timer_periph = TIMER9,                      \
        .name = "pwm9",                              \
        .timer_clk = RCU_TIMER9,                     \
        .channel_mask = (rt_uint8_t)(                \
            PWM9_CHANNEL_1_MASK),                    \
    }
#endif
#endif

#ifdef BSP_USING_PWM10
#ifndef PWM10_CONFIG
#define PWM10_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER10,                     \
        .name = "pwm10",                             \
        .timer_clk = RCU_TIMER10,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM10_CHANNEL_1_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM11
#ifndef PWM11_CONFIG
#define PWM11_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER11,                     \
        .name = "pwm11",                             \
        .timer_clk = RCU_TIMER11,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM11_CHANNEL_1_MASK |                   \
            PWM11_CHANNEL_2_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM12
#ifndef PWM12_CONFIG
#define PWM12_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER12,                     \
        .name = "pwm12",                             \
        .timer_clk = RCU_TIMER12,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM12_CHANNEL_1_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM13
#ifndef PWM13_CONFIG
#define PWM13_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER13,                     \
        .name = "pwm13",                             \
        .timer_clk = RCU_TIMER13,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM13_CHANNEL_1_MASK),                   \
    }
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __PWM_CONFIG_H__ */
