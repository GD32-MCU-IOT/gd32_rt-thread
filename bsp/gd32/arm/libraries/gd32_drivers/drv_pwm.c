/*
 * Copyright (c) 2006-2023
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-06-05     zengjianwei       first version
 * 2026-11-17     RT-Thread         refactor driver for one device per timer, pin init moved to board
 */

#include <board.h>
#include "drv_pwm.h"

#ifdef RT_USING_PWM

/* #define DRV_DEBUG */
#define LOG_TAG "drv.pwm"
#include <rtdbg.h>

#define MAX_PERIOD  65535
#define MIN_PERIOD  3
#define MIN_PULSE   2
#define MAX_CHANNEL 4

enum
{
#ifdef BSP_USING_PWM0
    PWM0_INDEX,
#endif
#ifdef BSP_USING_PWM1
    PWM1_INDEX,
#endif
#ifdef BSP_USING_PWM2
    PWM2_INDEX,
#endif
#ifdef BSP_USING_PWM3
    PWM3_INDEX,
#endif
#ifdef BSP_USING_PWM4
    PWM4_INDEX,
#endif
#ifdef BSP_USING_PWM7
    PWM7_INDEX,
#endif
#ifdef BSP_USING_PWM8
    PWM8_INDEX,
#endif
#ifdef BSP_USING_PWM9
    PWM9_INDEX,
#endif
#ifdef BSP_USING_PWM10
    PWM10_INDEX,
#endif
#ifdef BSP_USING_PWM11
    PWM11_INDEX,
#endif
#ifdef BSP_USING_PWM12
    PWM12_INDEX,
#endif
#ifdef BSP_USING_PWM13
    PWM13_INDEX,
#endif
    PWM_INDEX_MAX
};

/* TIMER5 and TIMER6 are basic timers without output channels */
static struct gd32_pwm gd32_pwm_obj[] = {
#ifdef BSP_USING_PWM0
    {.timer_periph = TIMER0, .timer_clk = RCU_TIMER0, .name = "pwm0"},
#endif
#ifdef BSP_USING_PWM1
    {.timer_periph = TIMER1, .timer_clk = RCU_TIMER1, .name = "pwm1"},
#endif
#ifdef BSP_USING_PWM2
    {.timer_periph = TIMER2, .timer_clk = RCU_TIMER2, .name = "pwm2"},
#endif
#ifdef BSP_USING_PWM3
    {.timer_periph = TIMER3, .timer_clk = RCU_TIMER3, .name = "pwm3"},
#endif
#ifdef BSP_USING_PWM4
    {.timer_periph = TIMER4, .timer_clk = RCU_TIMER4, .name = "pwm4"},
#endif
#ifdef BSP_USING_PWM7
    {.timer_periph = TIMER7, .timer_clk = RCU_TIMER7, .name = "pwm7"},
#endif
#ifdef BSP_USING_PWM8
    {.timer_periph = TIMER8, .timer_clk = RCU_TIMER8, .name = "pwm8"},
#endif
#ifdef BSP_USING_PWM9
    {.timer_periph = TIMER9, .timer_clk = RCU_TIMER9, .name = "pwm9"},
#endif
#ifdef BSP_USING_PWM10
    {.timer_periph = TIMER10, .timer_clk = RCU_TIMER10, .name = "pwm10"},
#endif
#ifdef BSP_USING_PWM11
    {.timer_periph = TIMER11, .timer_clk = RCU_TIMER11, .name = "pwm11"},
#endif
#ifdef BSP_USING_PWM12
    {.timer_periph = TIMER12, .timer_clk = RCU_TIMER12, .name = "pwm12"},
#endif
#ifdef BSP_USING_PWM13
    {.timer_periph = TIMER13, .timer_clk = RCU_TIMER13, .name = "pwm13"},
#endif
};

#warning "gd32_pwm_gpio_init should be defined in board_msd_init.c"
rt_weak void gd32_pwm_gpio_init(struct gd32_pwm *pwm)
{
}

static rt_bool_t gd32_pwm_is_advanced(rt_uint32_t timer_periph)
{
    return (timer_periph == TIMER0 || timer_periph == TIMER7) ? RT_TRUE : RT_FALSE;
}

/* TIMER clock is twice the APB clock when the APB prescaler is not 1 */
static rt_uint32_t gd32_pwm_clock_get(rt_uint32_t timer_periph)
{
    rt_uint32_t ahb_clk = rcu_clock_freq_get(CK_AHB);
    rt_uint32_t apb_clk;

    if (timer_periph == TIMER0 || timer_periph == TIMER7 || timer_periph == TIMER8 ||
        timer_periph == TIMER9 || timer_periph == TIMER10)
    {
        apb_clk = rcu_clock_freq_get(CK_APB2);
    }
    else
    {
        apb_clk = rcu_clock_freq_get(CK_APB1);
    }

    return (apb_clk == ahb_clk) ? apb_clk : apb_clk * 2;
}

static rt_err_t drv_pwm_enable(struct gd32_pwm *pwm, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    /* channel 1~4 => TIMER_CH_0~3 */
    rt_uint16_t channel = configuration->channel - 1;

    if (!configuration->complementary)
    {
        timer_channel_output_state_config(pwm->timer_periph, channel, enable ? TIMER_CCX_ENABLE : TIMER_CCX_DISABLE);
    }
    else
    {
        /* only TIMER0/7 channel 0~2 have complementary outputs */
        if (!gd32_pwm_is_advanced(pwm->timer_periph) || channel > TIMER_CH_2)
        {
            LOG_E("%s channel %d has no complementary output", pwm->name, configuration->channel);
            return -RT_EINVAL;
        }
        timer_channel_complementary_output_state_config(pwm->timer_periph, channel,
                                                        enable ? TIMER_CCXN_ENABLE : TIMER_CCXN_DISABLE);
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_get(struct gd32_pwm *pwm, struct rt_pwm_configuration *configuration)
{
    rt_uint16_t channel = configuration->channel - 1;
    rt_uint64_t tim_clock, psc, car, chxcv;

    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock = gd32_pwm_clock_get(pwm->timer_periph) / 1000000UL;
    psc       = timer_prescaler_read(pwm->timer_periph);
    car       = TIMER_CAR(pwm->timer_periph);
    chxcv     = timer_channel_capture_value_register_read(pwm->timer_periph, channel);

    configuration->period = (car + 1) * (psc + 1) * 1000ULL / tim_clock;
    configuration->pulse  = chxcv * (psc + 1) * 1000ULL / tim_clock;

    return RT_EOK;
}

static rt_err_t drv_pwm_set(struct gd32_pwm *pwm, struct rt_pwm_configuration *configuration)
{
    rt_uint16_t channel = configuration->channel - 1;
    rt_uint64_t tim_clock, period, pulse, psc;

    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock = gd32_pwm_clock_get(pwm->timer_periph) / 1000000UL;
    period    = (rt_uint64_t)configuration->period * tim_clock / 1000ULL;
    psc       = period / MAX_PERIOD + 1;
    if (psc > MAX_PERIOD + 1)
    {
        LOG_E("%s period %u ns is too long", pwm->name, configuration->period);
        return -RT_EINVAL;
    }
    period = period / psc;

    timer_prescaler_config(pwm->timer_periph, (rt_uint16_t)(psc - 1), TIMER_PSC_RELOAD_NOW);

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    timer_autoreload_value_config(pwm->timer_periph, (rt_uint16_t)(period - 1));

    pulse = (rt_uint64_t)configuration->pulse * tim_clock / psc / 1000ULL;
    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    else if (pulse > period)
    {
        pulse = period;
    }
    timer_channel_output_pulse_value_config(pwm->timer_periph, channel, (rt_uint32_t)pulse);
    timer_counter_value_config(pwm->timer_periph, 0);

    /* Update frequency value */
    timer_event_software_generate(pwm->timer_periph, TIMER_EVENT_SRC_UPG);

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    struct gd32_pwm             *pwm           = (struct gd32_pwm *)device->parent.user_data;

    if (configuration->channel < 1 || configuration->channel > MAX_CHANNEL ||
        !(pwm->channel & (1 << (configuration->channel - 1))))
    {
        LOG_E("%s channel %d is not enabled", pwm->name, configuration->channel);
        return -RT_EINVAL;
    }

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(pwm, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(pwm, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(pwm, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(pwm, configuration);
    default:
        return -RT_EINVAL;
    }
}

static struct rt_pwm_ops drv_ops = {drv_pwm_control};

static void gd32_hw_pwm_init(struct gd32_pwm *pwm)
{
    timer_parameter_struct    timer_initpara;
    timer_oc_parameter_struct timer_ocpara;
    rt_uint16_t               channel;

    /* board level: timer clock, GPIO clock and pins */
    gd32_pwm_gpio_init(pwm);

    timer_deinit(pwm->timer_periph);

    timer_struct_para_init(&timer_initpara);
    timer_initpara.prescaler         = 119;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 15999;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(pwm->timer_periph, &timer_initpara);

    /* outputs stay disabled until PWM_CMD_ENABLE */
    timer_channel_output_struct_para_init(&timer_ocpara);
    timer_ocpara.outputstate  = TIMER_CCX_DISABLE;
    timer_ocpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    for (channel = 0; channel < MAX_CHANNEL; channel++)
    {
        if (!(pwm->channel & (1 << channel)))
        {
            continue;
        }

        timer_channel_output_config(pwm->timer_periph, channel, &timer_ocpara);
        timer_channel_output_pulse_value_config(pwm->timer_periph, channel, 7999);
        timer_channel_output_mode_config(pwm->timer_periph, channel, TIMER_OC_MODE_PWM0);
        timer_channel_output_shadow_config(pwm->timer_periph, channel, TIMER_OC_SHADOW_DISABLE);
    }

    if (gd32_pwm_is_advanced(pwm->timer_periph))
    {
        timer_primary_output_config(pwm->timer_periph, ENABLE);
    }

    timer_enable(pwm->timer_periph);
}

static void gd32_pwm_get_channel(void)
{
#ifdef BSP_USING_PWM0_CH1
    gd32_pwm_obj[PWM0_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM0_CH2
    gd32_pwm_obj[PWM0_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM0_CH3
    gd32_pwm_obj[PWM0_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM0_CH4
    gd32_pwm_obj[PWM0_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM1_CH1
    gd32_pwm_obj[PWM1_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM1_CH2
    gd32_pwm_obj[PWM1_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM1_CH3
    gd32_pwm_obj[PWM1_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM1_CH4
    gd32_pwm_obj[PWM1_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM2_CH1
    gd32_pwm_obj[PWM2_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM2_CH2
    gd32_pwm_obj[PWM2_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM2_CH3
    gd32_pwm_obj[PWM2_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM2_CH4
    gd32_pwm_obj[PWM2_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM3_CH1
    gd32_pwm_obj[PWM3_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM3_CH2
    gd32_pwm_obj[PWM3_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM3_CH3
    gd32_pwm_obj[PWM3_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM3_CH4
    gd32_pwm_obj[PWM3_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM4_CH1
    gd32_pwm_obj[PWM4_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM4_CH2
    gd32_pwm_obj[PWM4_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM4_CH3
    gd32_pwm_obj[PWM4_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM4_CH4
    gd32_pwm_obj[PWM4_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM7_CH1
    gd32_pwm_obj[PWM7_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM7_CH2
    gd32_pwm_obj[PWM7_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM7_CH3
    gd32_pwm_obj[PWM7_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM7_CH4
    gd32_pwm_obj[PWM7_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM8_CH1
    gd32_pwm_obj[PWM8_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM8_CH2
    gd32_pwm_obj[PWM8_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM9_CH1
    gd32_pwm_obj[PWM9_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM10_CH1
    gd32_pwm_obj[PWM10_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM11_CH1
    gd32_pwm_obj[PWM11_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM11_CH2
    gd32_pwm_obj[PWM11_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM12_CH1
    gd32_pwm_obj[PWM12_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM13_CH1
    gd32_pwm_obj[PWM13_INDEX].channel |= 1 << 0;
#endif
}

static int gd32_pwm_init(void)
{
    int i;
    int result = RT_EOK;

    gd32_pwm_get_channel();

    for (i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); i++)
    {
        gd32_hw_pwm_init(&gd32_pwm_obj[i]);

        /* register pwm device */
        if (rt_device_pwm_register(&gd32_pwm_obj[i].pwm_device, gd32_pwm_obj[i].name, &drv_ops, &gd32_pwm_obj[i]) == RT_EOK)
        {
            LOG_D("%s register success", gd32_pwm_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", gd32_pwm_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(gd32_pwm_init);
#endif /* RT_USING_PWM */
