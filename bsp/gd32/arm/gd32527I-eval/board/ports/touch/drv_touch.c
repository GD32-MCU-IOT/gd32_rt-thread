/*
 * Copyright (c) 2026 GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-02     RT-Thread    resistive touch panel driver for GD32F527I-EVAL
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_TOUCH

#include "drv_touch.h"
#include "drv_lcd.h"
#include "gd32f5xx.h"
#include <stdlib.h>

#define DBG_TAG              "drv.touch"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

/* ADS7843/XPT2046-compatible controller wired to a bit-banged SPI bus */

/* SPI SCK pin: PH6 */
#define TP_SCK_RCU           RCU_GPIOH
#define TP_SCK_PORT          GPIOH
#define TP_SCK_PIN           GPIO_PIN_6
/* SPI MOSI pin: PF9 */
#define TP_MOSI_RCU          RCU_GPIOF
#define TP_MOSI_PORT         GPIOF
#define TP_MOSI_PIN          GPIO_PIN_9
/* SPI MISO pin: PH7 */
#define TP_MISO_RCU          RCU_GPIOH
#define TP_MISO_PORT         GPIOH
#define TP_MISO_PIN          GPIO_PIN_7
/* SPI chip select pin: PF6 */
#define TP_CS_RCU            RCU_GPIOF
#define TP_CS_PORT           GPIOF
#define TP_CS_PIN            GPIO_PIN_6
/* pen interrupt (touch detect) pin: PI3 */
#define TP_PEN_RCU           RCU_GPIOI
#define TP_PEN_PORT          GPIOI
#define TP_PEN_PIN           GPIO_PIN_3

#define TP_SCK_LOW()         gpio_bit_reset(TP_SCK_PORT, TP_SCK_PIN)
#define TP_SCK_HIGH()        gpio_bit_set(TP_SCK_PORT, TP_SCK_PIN)
#define TP_MOSI_LOW()        gpio_bit_reset(TP_MOSI_PORT, TP_MOSI_PIN)
#define TP_MOSI_HIGH()       gpio_bit_set(TP_MOSI_PORT, TP_MOSI_PIN)
#define TP_MISO_READ()       gpio_input_bit_get(TP_MISO_PORT, TP_MISO_PIN)
#define TP_CS_LOW()          gpio_bit_reset(TP_CS_PORT, TP_CS_PIN)
#define TP_CS_HIGH()         gpio_bit_set(TP_CS_PORT, TP_CS_PIN)
#define TP_PEN_READ()        gpio_input_bit_get(TP_PEN_PORT, TP_PEN_PIN)

/* controller command bytes: read X+ / read Y+ (12-bit, differential) */
#define TP_CMD_READ_X        0x90
#define TP_CMD_READ_Y        0xD0

/* touch AD calibration values for the on-board panel (from vendor BSP) */
#define TP_AD_LEFT           300
#define TP_AD_RIGHT          3850
#define TP_AD_TOP            220
#define TP_AD_BOTTOM         3850

/* median filter parameters */
#define TP_FILTER_READS      5   /* number of samples per filtered read */
#define TP_FILTER_DROP       1   /* drop this many lowest and highest samples */
#define TP_AD_ERR_RANGE      50  /* max delta between two consecutive reads */

static void _tp_delay(rt_uint16_t n)
{
    volatile rt_uint16_t i;
    for (i = 0; i < n; i++)
    {
        __NOP();
    }
}

/*!
    \brief    configure the bit-banged SPI and pen interrupt GPIO
*/
static void _tp_gpio_config(void)
{
    rcu_periph_clock_enable(TP_SCK_RCU);
    rcu_periph_clock_enable(TP_MOSI_RCU);
    rcu_periph_clock_enable(TP_MISO_RCU);
    rcu_periph_clock_enable(TP_CS_RCU);
    rcu_periph_clock_enable(TP_PEN_RCU);

    gpio_mode_set(TP_SCK_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, TP_SCK_PIN);
    gpio_output_options_set(TP_SCK_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, TP_SCK_PIN);

    gpio_mode_set(TP_MOSI_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, TP_MOSI_PIN);
    gpio_output_options_set(TP_MOSI_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, TP_MOSI_PIN);

    gpio_mode_set(TP_MISO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, TP_MISO_PIN);

    gpio_mode_set(TP_CS_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, TP_CS_PIN);
    gpio_output_options_set(TP_CS_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, TP_CS_PIN);

    gpio_mode_set(TP_PEN_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, TP_PEN_PIN);

    TP_CS_HIGH();
}

/*!
    \brief    generate the start condition on the bit-banged SPI bus
*/
static void _tp_start(void)
{
    TP_SCK_LOW();
    TP_CS_HIGH();
    TP_MOSI_HIGH();
    TP_SCK_HIGH();
    TP_CS_LOW();
}

/*!
    \brief    write one command byte to the touch controller (MSB first)
*/
static void _tp_write(rt_uint8_t data)
{
    rt_uint8_t i;

    TP_SCK_LOW();
    for (i = 0; i < 8; i++)
    {
        if ((data >> (7 - i)) & 0x01)
        {
            TP_MOSI_HIGH();
        }
        else
        {
            TP_MOSI_LOW();
        }
        TP_SCK_LOW();
        TP_SCK_HIGH();
        TP_SCK_LOW();
    }
}

/*!
    \brief    read a 12-bit conversion result from the touch controller (MSB first)
*/
static rt_uint16_t _tp_read(void)
{
    rt_uint8_t  i;
    rt_uint16_t value = 0;

    for (i = 0; i < 12; i++)
    {
        value <<= 1;
        TP_SCK_HIGH();
        TP_SCK_LOW();
        if (RESET != TP_MISO_READ())
        {
            value += 1;
        }
    }

    return value;
}

/*!
    \brief    read a single raw AD value for the selected channel
*/
static rt_uint16_t _tp_read_channel(rt_uint8_t cmd)
{
    if (RESET != TP_PEN_READ())
    {
        /* pen is up */
        return 0;
    }

    _tp_start();
    _tp_write(0x00);
    _tp_write(cmd);
    return _tp_read();
}

/*!
    \brief    read a channel several times, sort, drop extremes and average
*/
static rt_uint16_t _tp_filter(rt_uint8_t cmd)
{
    rt_uint16_t buf[TP_FILTER_READS];
    rt_uint16_t i, j, tmp, sum;

    for (i = 0; i < TP_FILTER_READS; i++)
    {
        buf[i] = _tp_read_channel(cmd);
    }

    /* ascending sort */
    for (i = 0; i < TP_FILTER_READS - 1; i++)
    {
        for (j = i + 1; j < TP_FILTER_READS; j++)
        {
            if (buf[i] > buf[j])
            {
                tmp    = buf[i];
                buf[i] = buf[j];
                buf[j] = tmp;
            }
        }
    }

    sum = 0;
    for (i = TP_FILTER_DROP; i < TP_FILTER_READS - TP_FILTER_DROP; i++)
    {
        sum += buf[i];
    }

    return sum / (TP_FILTER_READS - 2 * TP_FILTER_DROP);
}

/*!
    \brief    get a stable pair of raw AD samples for both axes
    \retval   RT_TRUE when two consecutive reads agree, RT_FALSE otherwise
*/
static rt_bool_t _tp_read_ad(rt_int16_t *ad_x, rt_int16_t *ad_y)
{
    rt_uint16_t x1, y1, x2, y2;

    x1 = _tp_filter(TP_CMD_READ_X);
    y1 = _tp_filter(TP_CMD_READ_Y);
    x2 = _tp_filter(TP_CMD_READ_X);
    y2 = _tp_filter(TP_CMD_READ_Y);

    if ((abs((int)x1 - (int)x2) > TP_AD_ERR_RANGE) ||
        (abs((int)y1 - (int)y2) > TP_AD_ERR_RANGE))
    {
        return RT_FALSE;
    }

    *ad_x = (rt_int16_t)((x1 + x2) / 2);
    *ad_y = (rt_int16_t)((y1 + y2) / 2);
    return RT_TRUE;
}

/*!
    \brief    map a raw X AD value to an LCD X coordinate
*/
static rt_int16_t _tp_map_x(rt_int16_t ad_x)
{
    rt_int32_t v = ad_x - TP_AD_LEFT;

    v = v * (LCD_WIDTH - 1) / (TP_AD_RIGHT - TP_AD_LEFT);
    if (v < 0)
    {
        v = 0;
    }
    if (v > LCD_WIDTH - 1)
    {
        v = LCD_WIDTH - 1;
    }
    return (rt_int16_t)v;
}

/*!
    \brief    map a raw Y AD value to an LCD Y coordinate
*/
static rt_int16_t _tp_map_y(rt_int16_t ad_y)
{
    rt_int32_t v = ad_y - TP_AD_TOP;

    v = v * (LCD_HEIGHT - 1) / (TP_AD_BOTTOM - TP_AD_TOP);
    if (v < 0)
    {
        v = 0;
    }
    if (v > LCD_HEIGHT - 1)
    {
        v = LCD_HEIGHT - 1;
    }
    return (rt_int16_t)v;
}

rt_bool_t gd32_touch_read(rt_int16_t *out_x, rt_int16_t *out_y)
{
    rt_int16_t ad_x = 0, ad_y = 0;

    if (RESET != TP_PEN_READ())
    {
        /* pen is up, nothing pressed */
        return RT_FALSE;
    }

    if (!_tp_read_ad(&ad_x, &ad_y))
    {
        return RT_FALSE;
    }

    /* the panel is mounted with both axes reversed relative to the LCD scan */
    *out_x = (LCD_WIDTH - 1) - _tp_map_x(ad_x);
    *out_y = (LCD_HEIGHT - 1) - _tp_map_y(ad_y);

    return RT_TRUE;
}

static int rt_hw_touch_init(void)
{
    _tp_gpio_config();
    _tp_delay(1000);

    LOG_I("resistive touch panel init ok");
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_touch_init);

#endif /* BSP_USING_TOUCH */
