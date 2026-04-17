/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-02-25     iysheng           first version
 */

#include <board.h>
#include <rtdevice.h>
#include <drivers/hwtimer.h>

#ifdef BSP_USING_HWTIMER

typedef struct {
    uint32_t reg_base;
    IRQn_Type irqn;
    rcu_periph_enum rcu;
} gd32_hwtimer_data;

typedef struct {
    char dev_name[RT_NAME_MAX];
    const gd32_hwtimer_data hw_data;
    rt_hwtimer_t hwtimer_dev;
    const struct rt_hwtimer_info hwtimer_info;
} gd32_hwtimer_device;

enum timer_index_E {
#ifdef BSP_USING_HWTIMER0
    TIM0_INDEX,
#endif
#ifdef BSP_USING_HWTIMER1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_HWTIMER2
    TIM2_INDEX,
#endif
#ifdef BSP_USING_HWTIMER3
    TIM3_INDEX,
#endif
#ifdef BSP_USING_HWTIMER4
    TIM4_INDEX,
#endif
#ifdef BSP_USING_HWTIMER5
    TIM5_INDEX,
#endif
#ifdef BSP_USING_HWTIMER6
    TIM6_INDEX,
#endif
#ifdef BSP_USING_HWTIMER7
    TIM7_INDEX,
#endif
#if defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H77x
#ifdef BSP_USING_HWTIMER14
    TIM14_INDEX,
#endif
#ifdef BSP_USING_HWTIMER15
    TIM15_INDEX,
#endif
#ifdef BSP_USING_HWTIMER16
    TIM16_INDEX,
#endif
#ifdef BSP_USING_HWTIMER22
    TIM22_INDEX,
#endif
#ifdef BSP_USING_HWTIMER23
    TIM23_INDEX,
#endif
#ifdef BSP_USING_HWTIMER30
    TIM30_INDEX,
#endif
#ifdef BSP_USING_HWTIMER31
    TIM31_INDEX,
#endif
#ifdef BSP_USING_HWTIMER40
    TIM40_INDEX,
#endif
#ifdef BSP_USING_HWTIMER41
    TIM41_INDEX,
#endif
#ifdef BSP_USING_HWTIMER42
    TIM42_INDEX,
#endif
#ifdef BSP_USING_HWTIMER43
    TIM43_INDEX,
#endif
#ifdef BSP_USING_HWTIMER44
    TIM44_INDEX,
#endif
#ifdef BSP_USING_HWTIMER50
    TIM50_INDEX,
#endif
#ifdef BSP_USING_HWTIMER51
    TIM51_INDEX,
#endif
#else
#ifdef BSP_USING_HWTIMER8
    TIM8_INDEX,
#endif
#ifdef BSP_USING_HWTIMER9
    TIM9_INDEX,
#endif
#ifdef BSP_USING_HWTIMER10
    TIM10_INDEX,
#endif
#ifdef BSP_USING_HWTIMER11
    TIM11_INDEX,
#endif
#ifdef BSP_USING_HWTIMER12
    TIM12_INDEX,
#endif
#ifdef BSP_USING_HWTIMER13
    TIM13_INDEX,
#endif
#endif
};

/*
 * static void __set_timerx_freq
 * Set freq with timerx
 *
 * @param timerx the pointer of TIMER_TypeDef
 * @param freq of the timer clock
 * @retval None
 */
static void __set_timerx_freq(uint32_t timerx, uint32_t freq)
{
    uint32_t ap1freq, ap2freq;
    uint32_t prescaler;
    uint32_t temp;

#if defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H77x
    if (timerx == TIMER0 || timerx == TIMER7 || timerx == TIMER14 \
        || timerx == TIMER15 || timerx == TIMER16 || timerx == TIMER40 \
        || timerx == TIMER41 || timerx == TIMER42 || timerx == TIMER43 \
        || timerx == TIMER44)
#else
    if (timerx == TIMER0 || timerx == TIMER7 || timerx == TIMER8 \
        || timerx == TIMER9 || timerx == TIMER10)
#endif
    {
        ap2freq = rcu_clock_freq_get(CK_APB2);
        temp = RCU_CFG0 & RCU_CFG0_APB2PSC;
        temp >>= 11;
        /* whether should frequency doubling */
        temp = (temp < 4) ? 0 : 1;

        prescaler = (ap2freq << temp) / freq - 1;
    }
    else
    {
        ap1freq = rcu_clock_freq_get(CK_APB1);
        temp = RCU_CFG0 & RCU_CFG0_APB1PSC;
        temp >>= 8;
        /* whether should frequency doubling */
        temp = (temp < 4) ? 0 : 1;

        prescaler = (ap1freq << temp) / freq - 1;
    }

    timer_prescaler_config(timerx, prescaler, TIMER_PSC_RELOAD_NOW);
}

static void gd32_hwtimer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    uint32_t timer_base = (uint32_t)timer->parent.user_data;
    timer_parameter_struct initpara;

    if (state)
    {
        timer_internal_clock_config(timer_base);
        timer_struct_para_init(&initpara);
        initpara.period =  timer->info->maxcnt;
        timer_init(timer_base, &initpara);
        __set_timerx_freq(timer_base, timer->info->maxfreq);
    }
}

static rt_err_t gd32_hwtimer_start(struct rt_hwtimer_device *timer, \
    rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    uint32_t timer_base = (uint32_t)timer->parent.user_data;

    if (mode == HWTIMER_MODE_ONESHOT)
    {
        timer_single_pulse_mode_config(timer_base, TIMER_SP_MODE_SINGLE);
    }
    else if (mode == HWTIMER_MODE_PERIOD)
    {
        timer_single_pulse_mode_config(timer_base, TIMER_SP_MODE_REPETITIVE);
    }

    timer_counter_value_config(timer_base, 0);
    timer_autoreload_value_config(timer_base, cnt - 1);
    timer_enable(timer_base);

    return 0;
}

static void gd32_hwtimer_stop(struct rt_hwtimer_device *timer)
{
    uint32_t timer_base = (uint32_t)timer->parent.user_data;

    timer_disable(timer_base);
}

static rt_uint32_t gd32_hwtimer_count_get(struct rt_hwtimer_device *timer)
{
    uint32_t timer_base = (uint32_t)timer->parent.user_data;
    rt_uint32_t count;

    count = timer_counter_read(timer_base);

    return count;
}

static rt_err_t gd32_hwtimer_control(struct rt_hwtimer_device *timer, rt_uint32_t cmd, \
    void *args)
{
    int ret = RT_EOK;
    rt_int32_t freq;
    rt_hwtimer_mode_t mode;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        freq = *(rt_uint32_t *)args;
        __set_timerx_freq((uint32_t)timer->parent.user_data, freq);
        break;
    default:
        rt_kprintf("invalid cmd:%x\n", cmd);
        ret = -RT_EINVAL;
        break;
    }

    return ret;
}

static const struct rt_hwtimer_ops g_gd32_hwtimer_ops = {
    gd32_hwtimer_init,
    gd32_hwtimer_start,
    gd32_hwtimer_stop,
    gd32_hwtimer_count_get,
    gd32_hwtimer_control,
};

static gd32_hwtimer_device g_gd32_hwtimer[] = {
#ifdef BSP_USING_HWTIMER0
    {
        "timer0",
        {
             TIMER0,
             TIMER0_UP_IRQn,
             RCU_TIMER0,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER1
    {
        "timer1",
        {
             TIMER1,
             TIMER1_IRQn,
             RCU_TIMER1,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER2
    {
        "timer2",
        {
             TIMER2,
             TIMER2_IRQn,
             RCU_TIMER2,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER3
    {
        "timer3",
        {
             TIMER3,
             TIMER3_IRQn,
             RCU_TIMER3,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER4
    {
        "timer4",
        {
             TIMER4,
             TIMER4_IRQn,
             RCU_TIMER4,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER5
    {
        "timer5",
        {
             TIMER5,
#if defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H77x
             TIMER5_DAC_UDR_IRQn,
#else
             TIMER5_IRQn,
#endif
             RCU_TIMER5,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER6
    {
        "timer6",
        {
             TIMER6,
             TIMER6_IRQn,
             RCU_TIMER6,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER7
    {
        "timer7",
        {
             TIMER7,
             TIMER7_UP_IRQn,
             RCU_TIMER7,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#if defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H77x
#ifdef BSP_USING_HWTIMER14
    {
        "timer14",
        {
             TIMER14,
             TIMER14_IRQn,
             RCU_TIMER14,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER15
    {
        "timer15",
        {
             TIMER15,
             TIMER15_IRQn,
             RCU_TIMER15,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER16
    {
        "timer16",
        {
             TIMER16,
             TIMER16_IRQn,
             RCU_TIMER16,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER22
    {
        "timer22",
        {
             TIMER22,
             TIMER22_IRQn,
             RCU_TIMER22,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER23
    {
        "timer23",
        {
             TIMER23,
             TIMER23_IRQn,
             RCU_TIMER23,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER30
    {
        "timer30",
        {
             TIMER30,
             TIMER30_IRQn,
             RCU_TIMER30,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER31
    {
        "timer31",
        {
             TIMER31,
             TIMER31_IRQn,
             RCU_TIMER31,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER40
    {
        "timer40",
        {
             TIMER40,
             TIMER40_IRQn,
             RCU_TIMER40,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER41
    {
        "timer41",
        {
             TIMER41,
             TIMER41_IRQn,
             RCU_TIMER41,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER42
    {
        "timer42",
        {
             TIMER42,
             TIMER42_IRQn,
             RCU_TIMER42,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER43
    {
        "timer43",
        {
             TIMER43,
             TIMER43_IRQn,
             RCU_TIMER43,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER44
    {
        "timer44",
        {
             TIMER44,
             TIMER44_IRQn,
             RCU_TIMER44,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER50
    {
        "timer50",
        {
             TIMER50,
             TIMER50_IRQn,
             RCU_TIMER50,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER51
    {
        "timer51",
        {
             TIMER51,
             TIMER51_IRQn,
             RCU_TIMER51,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode */
        }
    },
#endif
#else
#ifdef BSP_USING_HWTIMER8
    {
        "timer8",
        {
             TIMER8,
             TIMER8_IRQn,
             RCU_TIMER8,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER9
    {
        "timer9",
        {
             TIMER9,
             TIMER9_IRQn,
             RCU_TIMER9,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER10
    {
        "timer10",
        {
             TIMER10,
             TIMER10_IRQn,
             RCU_TIMER10,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER11
    {
        "timer11",
        {
             TIMER11,
             TIMER11_IRQn,
             RCU_TIMER11,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER12
    {
        "timer12",
        {
             TIMER12,
             TIMER12_IRQn,
             RCU_TIMER12,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_HWTIMER13
    {
        "timer13",
        {
             TIMER13,
             TIMER13_IRQn,
             RCU_TIMER13,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#endif
};

#ifdef BSP_USING_HWTIMER0
void TIMER0_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM0_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM0_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER1
void TIMER1_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM1_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM1_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);

    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER2
void TIMER2_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM2_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM2_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER3
void TIMER3_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM3_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM3_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER4
void TIMER4_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM4_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM4_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER5
#if defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H77x
void TIMER5_DAC_UDR_IRQHandler(void)
#else
void TIMER5_IRQHandler(void)
#endif
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM5_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM5_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER6
void TIMER6_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM6_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM6_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER7
void TIMER7_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM7_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM7_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#if defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H77x
#ifdef BSP_USING_HWTIMER14
void TIMER14_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM14_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM14_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER15
void TIMER15_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM15_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM15_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER16
void TIMER16_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM16_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM16_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER22
void TIMER22_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM22_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM22_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER23
void TIMER23_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM23_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM23_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER30
void TIMER30_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM30_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM30_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER31
void TIMER31_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM31_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM31_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER40
void TIMER40_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM40_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM40_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER41
void TIMER41_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM41_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM41_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER42
void TIMER42_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM42_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM42_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER43
void TIMER43_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM43_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM43_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER44
void TIMER44_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM44_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM44_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER50
void TIMER50_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM50_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM50_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER51
void TIMER51_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM51_INDEX].hwtimer_dev);
    timer_flag_clear((uint32_t)g_gd32_hwtimer[TIM51_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_FLAG_UP);
    rt_interrupt_leave();
}
#endif
#endif

static int rt_hwtimer_init(void)
{
    int ret = 0, i = 0;

    for (; i < sizeof(g_gd32_hwtimer) / sizeof(g_gd32_hwtimer[0]); i++)
    {
        g_gd32_hwtimer[i].hwtimer_dev.ops = &g_gd32_hwtimer_ops;
        g_gd32_hwtimer[i].hwtimer_dev.info = &g_gd32_hwtimer[i].hwtimer_info;

        rcu_periph_clock_enable(g_gd32_hwtimer[i].hw_data.rcu);
        NVIC_SetPriority(g_gd32_hwtimer[i].hw_data.irqn, 0);
        NVIC_EnableIRQ(g_gd32_hwtimer[i].hw_data.irqn);
        timer_interrupt_enable(g_gd32_hwtimer[i].hw_data.reg_base, TIMER_INT_UP);
        ret = rt_device_hwtimer_register(&g_gd32_hwtimer[i].hwtimer_dev, \
            g_gd32_hwtimer[i].dev_name, (void *)g_gd32_hwtimer[i].hw_data.reg_base);
        if (RT_EOK != ret)
        {
            rt_kprintf("failed register %s, err=%d\n", g_gd32_hwtimer[i].dev_name, \
                ret);
            break;
        }
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hwtimer_init);
#endif
