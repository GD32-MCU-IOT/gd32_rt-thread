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

#if defined(BSP_USING_PWM14_CH1)
#define PWM14_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM14_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM14_CH2)
#define PWM14_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM14_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM15_CH1)
#define PWM15_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM15_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM16_CH1)
#define PWM16_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM16_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM22_CH1)
#define PWM22_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM22_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM22_CH2)
#define PWM22_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM22_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM22_CH3)
#define PWM22_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM22_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM22_CH4)
#define PWM22_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM22_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM23_CH1)
#define PWM23_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM23_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM23_CH2)
#define PWM23_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM23_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM23_CH3)
#define PWM23_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM23_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM23_CH4)
#define PWM23_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM23_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM30_CH1)
#define PWM30_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM30_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM30_CH2)
#define PWM30_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM30_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM30_CH3)
#define PWM30_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM30_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM30_CH4)
#define PWM30_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM30_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM31_CH1)
#define PWM31_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM31_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM31_CH2)
#define PWM31_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM31_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM31_CH3)
#define PWM31_CHANNEL_3_MASK GD32_PWM_CHANNEL_3_BIT
#else
#define PWM31_CHANNEL_3_MASK 0U
#endif

#if defined(BSP_USING_PWM31_CH4)
#define PWM31_CHANNEL_4_MASK GD32_PWM_CHANNEL_4_BIT
#else
#define PWM31_CHANNEL_4_MASK 0U
#endif

#if defined(BSP_USING_PWM40_CH1)
#define PWM40_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM40_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM40_CH2)
#define PWM40_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM40_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM41_CH1)
#define PWM41_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM41_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM41_CH2)
#define PWM41_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM41_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM42_CH1)
#define PWM42_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM42_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM42_CH2)
#define PWM42_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM42_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM43_CH1)
#define PWM43_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM43_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM43_CH2)
#define PWM43_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM43_CHANNEL_2_MASK 0U
#endif

#if defined(BSP_USING_PWM44_CH1)
#define PWM44_CHANNEL_1_MASK GD32_PWM_CHANNEL_1_BIT
#else
#define PWM44_CHANNEL_1_MASK 0U
#endif

#if defined(BSP_USING_PWM44_CH2)
#define PWM44_CHANNEL_2_MASK GD32_PWM_CHANNEL_2_BIT
#else
#define PWM44_CHANNEL_2_MASK 0U
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

#ifdef BSP_USING_PWM14
#ifndef PWM14_CONFIG
#define PWM14_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER14,                     \
        .name = "pwm14",                             \
        .timer_clk = RCU_TIMER14,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM14_CHANNEL_1_MASK |                   \
            PWM14_CHANNEL_2_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM15
#ifndef PWM15_CONFIG
#define PWM15_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER15,                     \
        .name = "pwm15",                             \
        .timer_clk = RCU_TIMER15,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM15_CHANNEL_1_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM16
#ifndef PWM16_CONFIG
#define PWM16_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER16,                     \
        .name = "pwm16",                             \
        .timer_clk = RCU_TIMER16,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM16_CHANNEL_1_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM22
#ifndef PWM22_CONFIG
#define PWM22_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER22,                     \
        .name = "pwm22",                             \
        .timer_clk = RCU_TIMER22,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM22_CHANNEL_1_MASK |                   \
            PWM22_CHANNEL_2_MASK |                   \
            PWM22_CHANNEL_3_MASK |                   \
            PWM22_CHANNEL_4_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM23
#ifndef PWM23_CONFIG
#define PWM23_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER23,                     \
        .name = "pwm23",                             \
        .timer_clk = RCU_TIMER23,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM23_CHANNEL_1_MASK |                   \
            PWM23_CHANNEL_2_MASK |                   \
            PWM23_CHANNEL_3_MASK |                   \
            PWM23_CHANNEL_4_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM30
#ifndef PWM30_CONFIG
#define PWM30_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER30,                     \
        .name = "pwm30",                             \
        .timer_clk = RCU_TIMER30,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM30_CHANNEL_1_MASK |                   \
            PWM30_CHANNEL_2_MASK |                   \
            PWM30_CHANNEL_3_MASK |                   \
            PWM30_CHANNEL_4_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM31
#ifndef PWM31_CONFIG
#define PWM31_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER31,                     \
        .name = "pwm31",                             \
        .timer_clk = RCU_TIMER31,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM31_CHANNEL_1_MASK |                   \
            PWM31_CHANNEL_2_MASK |                   \
            PWM31_CHANNEL_3_MASK |                   \
            PWM31_CHANNEL_4_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM40
#ifndef PWM40_CONFIG
#define PWM40_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER40,                     \
        .name = "pwm40",                             \
        .timer_clk = RCU_TIMER40,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM40_CHANNEL_1_MASK |                   \
            PWM40_CHANNEL_2_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM41
#ifndef PWM41_CONFIG
#define PWM41_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER41,                     \
        .name = "pwm41",                             \
        .timer_clk = RCU_TIMER41,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM41_CHANNEL_1_MASK |                   \
            PWM41_CHANNEL_2_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM42
#ifndef PWM42_CONFIG
#define PWM42_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER42,                     \
        .name = "pwm42",                             \
        .timer_clk = RCU_TIMER42,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM42_CHANNEL_1_MASK |                   \
            PWM42_CHANNEL_2_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM43
#ifndef PWM43_CONFIG
#define PWM43_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER43,                     \
        .name = "pwm43",                             \
        .timer_clk = RCU_TIMER43,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM43_CHANNEL_1_MASK |                   \
            PWM43_CHANNEL_2_MASK),                   \
    }
#endif
#endif

#ifdef BSP_USING_PWM44
#ifndef PWM44_CONFIG
#define PWM44_CONFIG                                 \
    {                                                \
        .timer_periph = TIMER44,                     \
        .name = "pwm44",                             \
        .timer_clk = RCU_TIMER44,                    \
        .channel_mask = (rt_uint8_t)(                \
            PWM44_CHANNEL_1_MASK |                   \
            PWM44_CHANNEL_2_MASK),                   \
    }
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __PWM_CONFIG_H__ */
