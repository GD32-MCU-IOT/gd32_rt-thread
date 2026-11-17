/*
 * Copyright (c) 2006-2023
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-06-05     zengjianwei       first version
 * 2025-06-23     Yucai Liu         Support for non-complementary PWM output with advanced timers
 * 2026-11-17     RT-Thread         refactor driver for one device per timer, pin init moved to board
 */

#include <board.h>
#include "drv_pwm.h"
#include "drv_config.h"

#ifdef RT_USING_PWM

/* #define DRV_DEBUG */
#define LOG_TAG "drv.pwm"
#include <rtdbg.h>

#define MAX_PERIOD  65535
#define MIN_PERIOD  3
#define MIN_PULSE   2
#define MAX_CHANNEL 4

static struct gd32_pwm gd32_pwm_obj[] = {
#ifdef BSP_USING_PWM0
    PWM0_CONFIG,
#endif
#ifdef BSP_USING_PWM1
    PWM1_CONFIG,
#endif
#ifdef BSP_USING_PWM2
    PWM2_CONFIG,
#endif
#ifdef BSP_USING_PWM3
    PWM3_CONFIG,
#endif
#ifdef BSP_USING_PWM4
    PWM4_CONFIG,
#endif
#ifdef BSP_USING_PWM5
    PWM5_CONFIG,
#endif
#ifdef BSP_USING_PWM6
    PWM6_CONFIG,
#endif
#ifdef BSP_USING_PWM7
    PWM7_CONFIG,
#endif
#ifdef BSP_USING_PWM8
    PWM8_CONFIG,
#endif
#ifdef BSP_USING_PWM9
    PWM9_CONFIG,
#endif
#ifdef BSP_USING_PWM10
    PWM10_CONFIG,
#endif
#ifdef BSP_USING_PWM11
    PWM11_CONFIG,
#endif
#ifdef BSP_USING_PWM12
    PWM12_CONFIG,
#endif
#ifdef BSP_USING_PWM13
    PWM13_CONFIG,
#endif
#ifdef BSP_USING_PWM14
    PWM14_CONFIG,
#endif
#ifdef BSP_USING_PWM15
    PWM15_CONFIG,
#endif
#ifdef BSP_USING_PWM16
    PWM16_CONFIG,
#endif
#ifdef BSP_USING_PWM22
    PWM22_CONFIG,
#endif
#ifdef BSP_USING_PWM23
    PWM23_CONFIG,
#endif
#ifdef BSP_USING_PWM30
    PWM30_CONFIG,
#endif
#ifdef BSP_USING_PWM31
    PWM31_CONFIG,
#endif
#ifdef BSP_USING_PWM40
    PWM40_CONFIG,
#endif
#ifdef BSP_USING_PWM41
    PWM41_CONFIG,
#endif
#ifdef BSP_USING_PWM42
    PWM42_CONFIG,
#endif
#ifdef BSP_USING_PWM43
    PWM43_CONFIG,
#endif
#ifdef BSP_USING_PWM44
    PWM44_CONFIG,
#endif
};

#warning "gd32_pwm_gpio_init should be defined in board_msd_init.c"
rt_weak rt_err_t gd32_pwm_gpio_init(rt_uint32_t timer_periph, rt_uint8_t channel_mask)
{
    RT_UNUSED(timer_periph);
    RT_UNUSED(channel_mask);

    LOG_E("board-level gd32_pwm_gpio_init() is not implemented");
    return -RT_ENOSYS;
}

static rt_bool_t gd32_pwm_is_advanced(rt_uint32_t timer_periph)
{
    return (timer_periph == TIMER0 || timer_periph == TIMER7) ? RT_TRUE : RT_FALSE;
}

/* timers with the POEN bit in TIMERx_CCHP */
static rt_bool_t gd32_pwm_has_primary_output(rt_uint32_t timer_periph)
{
#if defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H77x
    return (timer_periph == TIMER0 || timer_periph == TIMER7 || timer_periph == TIMER14 ||
            timer_periph == TIMER15 || timer_periph == TIMER16 || timer_periph == TIMER40 ||
            timer_periph == TIMER41 || timer_periph == TIMER42 || timer_periph == TIMER43 ||
            timer_periph == TIMER44) ? RT_TRUE : RT_FALSE;
#else
    return gd32_pwm_is_advanced(timer_periph);
#endif
}

/* GD32H7xx/H77x: TIMER0/7 MCH0~3 and TIMER14~16/40~44 MCH0; others: TIMER0/7 CH0~2 */
static rt_bool_t gd32_pwm_has_complementary(rt_uint32_t timer_periph, rt_uint16_t channel)
{
#if defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H77x
    if (gd32_pwm_is_advanced(timer_periph))
    {
        return RT_TRUE;
    }
    return ((channel == TIMER_CH_0) && gd32_pwm_has_primary_output(timer_periph)) ? RT_TRUE : RT_FALSE;
#else
    return (gd32_pwm_is_advanced(timer_periph) && (channel <= TIMER_CH_2)) ? RT_TRUE : RT_FALSE;
#endif
}

/* TIMER clock is twice the APB clock when the APB prescaler is not 1,
 * GD32H7xx/H77x with TIMERSEL set: four times the APB clock when the APB prescaler is above 4 */
static rt_uint32_t gd32_pwm_clock_get(rt_uint32_t timer_periph)
{
    rt_uint32_t ahb_clk = rcu_clock_freq_get(CK_AHB);
    rt_uint32_t apb_clk;

#if defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H77x
    if (timer_periph == TIMER0 || timer_periph == TIMER7 || timer_periph == TIMER14 ||
        timer_periph == TIMER15 || timer_periph == TIMER16 || timer_periph == TIMER40 ||
        timer_periph == TIMER41 || timer_periph == TIMER42 || timer_periph == TIMER43 ||
        timer_periph == TIMER44)
#else
    if (timer_periph == TIMER0 || timer_periph == TIMER7 || timer_periph == TIMER8 ||
        timer_periph == TIMER9 || timer_periph == TIMER10)
#endif
    {
        apb_clk = rcu_clock_freq_get(CK_APB2);
    }
    else
    {
        apb_clk = rcu_clock_freq_get(CK_APB1);
    }

#if defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H77x
    if (RCU_CFG1 & RCU_CFG1_TIMERSEL)
    {
        return (apb_clk * 4 >= ahb_clk) ? ahb_clk : apb_clk * 4;
    }
#endif

    return (apb_clk == ahb_clk) ? apb_clk : apb_clk * 2;
}

/* channel 1~4 => TIMER_CH_0~3, the channel must be enabled in Kconfig */
static rt_err_t pwm_resolve_channel(const struct gd32_pwm *pwm, const struct rt_pwm_configuration *configuration,
                                    rt_uint16_t *resolved_channel)
{
    rt_uint16_t channel;

    if ((pwm == RT_NULL) || (configuration == RT_NULL) || (resolved_channel == RT_NULL))
    {
        LOG_E("invalid argument to resolve channel");
        return -RT_EINVAL;
    }

    if ((configuration->channel >= 1U) && (configuration->channel <= MAX_CHANNEL))
    {
        channel = (rt_uint16_t)(configuration->channel - 1U);
        if ((pwm->channel_mask & (1U << channel)) != 0U)
        {
            *resolved_channel = channel;
            return RT_EOK;
        }
    }

    LOG_E("%s channel %u is not enabled", pwm->name, configuration->channel);
    return -RT_EINVAL;
}

static rt_err_t drv_pwm_enable(struct gd32_pwm *pwm, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    rt_uint16_t channel;
    rt_err_t    result;

    result = pwm_resolve_channel(pwm, configuration, &channel);
    if (result != RT_EOK)
    {
        return result;
    }

    if (!configuration->complementary)
    {
        timer_channel_output_state_config(pwm->timer_periph, channel, enable ? TIMER_CCX_ENABLE : TIMER_CCX_DISABLE);
    }
    else
    {
        if (!gd32_pwm_has_complementary(pwm->timer_periph, channel))
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
    rt_uint16_t channel;
    rt_uint64_t tim_clock, psc, car, chxcv;
    rt_err_t    result;

    result = pwm_resolve_channel(pwm, configuration, &channel);
    if (result != RT_EOK)
    {
        return result;
    }

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
    rt_uint16_t channel;
    rt_uint64_t tim_clock, period, pulse, psc;
    rt_err_t    result;

    result = pwm_resolve_channel(pwm, configuration, &channel);
    if (result != RT_EOK)
    {
        return result;
    }

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
    struct rt_pwm_configuration *configuration;
    struct gd32_pwm             *pwm;

    if ((device == RT_NULL) || (arg == RT_NULL))
    {
        LOG_E("invalid argument to pwm control");
        return -RT_EINVAL;
    }

    configuration = (struct rt_pwm_configuration *)arg;
    pwm           = (struct gd32_pwm *)device;

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
        LOG_E("%s unsupported cmd %d", pwm->name, cmd);
        return -RT_EINVAL;
    }
}

static struct rt_pwm_ops drv_ops = {
    .control = drv_pwm_control,
};

static rt_err_t gd32_hw_pwm_init(struct gd32_pwm *pwm)
{
    timer_parameter_struct    timer_initpara;
    timer_oc_parameter_struct timer_ocpara;
    rt_uint16_t               channel;
    rt_err_t                  result;

    rcu_periph_clock_enable(pwm->timer_clk);

    /* board level: GPIO clock and pins */
    result = gd32_pwm_gpio_init(pwm->timer_periph, pwm->channel_mask);
    if (result != RT_EOK)
    {
        LOG_E("%s gpio init failed: %d", pwm->name, result);
        return result;
    }

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
        if ((pwm->channel_mask & (1U << channel)) == 0U)
        {
            continue;
        }

        timer_channel_output_config(pwm->timer_periph, channel, &timer_ocpara);
        timer_channel_output_pulse_value_config(pwm->timer_periph, channel, 7999);
        timer_channel_output_mode_config(pwm->timer_periph, channel, TIMER_OC_MODE_PWM0);
        timer_channel_output_shadow_config(pwm->timer_periph, channel, TIMER_OC_SHADOW_DISABLE);

#if defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H77x
        /* MCHx is independent after reset, select complementary mode for complementary output */
        if (gd32_pwm_has_complementary(pwm->timer_periph, channel))
        {
            timer_multi_mode_channel_mode_config(pwm->timer_periph, channel, TIMER_MCH_MODE_COMPLEMENTARY);
        }
#endif

#ifdef SOC_SERIES_GD32H77x
        if (gd32_pwm_is_advanced(pwm->timer_periph))
        {
            timer_channel_primary_output_config(pwm->timer_periph, channel, ENABLE);
        }
#endif
    }

    if (gd32_pwm_has_primary_output(pwm->timer_periph))
    {
        timer_primary_output_config(pwm->timer_periph, ENABLE);
    }

    timer_enable(pwm->timer_periph);

    return RT_EOK;
}

static int gd32_pwm_init(void)
{
    rt_size_t i;
    int       result = RT_EOK;

    for (i = 0; i < sizeof(gd32_pwm_obj) / sizeof(gd32_pwm_obj[0]); i++)
    {
        if (gd32_pwm_obj[i].channel_mask == 0U)
        {
            LOG_E("%s has no PWM channel enabled", gd32_pwm_obj[i].name);
            result = -RT_ERROR;
            continue;
        }

        if (gd32_hw_pwm_init(&gd32_pwm_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", gd32_pwm_obj[i].name);
            result = -RT_ERROR;
            continue;
        }

        /* register pwm device */
        if (rt_device_pwm_register(&gd32_pwm_obj[i].pwm_device, gd32_pwm_obj[i].name, &drv_ops, RT_NULL) == RT_EOK)
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
