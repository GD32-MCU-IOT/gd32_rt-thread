/*
 * Copyright (c) 2026 GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-02     RT-Thread    TLI RGB565 LCD driver for GD32F527I-EVAL
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_LCD

#include "drv_lcd.h"
#include "gd32f5xx.h"

#define DBG_TAG              "drv.lcd"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

/* LCD display timing for the on-board 480x272 RGB panel */
#define HORIZONTAL_SYNCHRONOUS_PULSE    41
#define HORIZONTAL_BACK_PORCH           2
#define ACTIVE_WIDTH                    LCD_WIDTH
#define HORIZONTAL_FRONT_PORCH          2

#define VERTICAL_SYNCHRONOUS_PULSE      10
#define VERTICAL_BACK_PORCH             2
#define ACTIVE_HEIGHT                   LCD_HEIGHT
#define VERTICAL_FRONT_PORCH            2

/* backlight control pin: PB15 */
#define LCD_BL_GPIO_PORT                GPIOB
#define LCD_BL_GPIO_PIN                 GPIO_PIN_15

static struct rt_device _lcd_device;
static struct rt_device_graphic_info _lcd_info;

/*!
    \brief    configure all TLI RGB signal GPIO pins as alternate function
*/
static void _tli_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);
    rcu_periph_clock_enable(RCU_GPIOH);
    rcu_periph_clock_enable(RCU_GPIOI);

    /* TLI pins alternate function (AF14) selection */
    gpio_af_set(GPIOE, GPIO_AF_14, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);

    gpio_af_set(GPIOH, GPIO_AF_14, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10
                | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

    gpio_af_set(GPIOI, GPIO_AF_14, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5
                | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10);

    gpio_af_set(GPIOG, GPIO_AF_14, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);

    gpio_af_set(GPIOF, GPIO_AF_14, GPIO_PIN_10);

    /* TLI GPIO mode configuration */
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);

    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10
                  | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10
                            | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

    gpio_mode_set(GPIOI, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2
                  | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10);
    gpio_output_options_set(GPIOI, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2
                            | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10);

    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);

    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    /* backlight control pin (PB15) as push-pull output, driven high */
    gpio_mode_set(LCD_BL_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LCD_BL_GPIO_PIN);
    gpio_output_options_set(LCD_BL_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_BL_GPIO_PIN);
    gpio_bit_set(LCD_BL_GPIO_PORT, LCD_BL_GPIO_PIN);
}

/*!
    \brief    configure the PLLSAI clock that feeds the TLI pixel clock
    \retval   RT_EOK on success, -RT_ERROR on failure
*/
static rt_err_t _tli_clock_config(void)
{
    /* PLLSAI VCO = CK_PLLSAI_input * N (240), CK_PLLSAIR = VCO / R (2)
     * N=240 matches the official lvgl_f527 demo */
    if (ERROR == rcu_pllsai_r_config(240, 2))
    {
        return -RT_ERROR;
    }

    /* TLI pixel clock = CK_PLLSAIR / 8 */
    rcu_tli_clock_div_config(RCU_PLLSAIR_DIV8);

    rcu_osci_on(RCU_PLLSAI_CK);
    if (ERROR == rcu_osci_stab_wait(RCU_PLLSAI_CK))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/*!
    \brief    initialize TLI controller and layer0 pointing to the SDRAM framebuffer
*/
static rt_err_t _tli_config(void)
{
    tli_parameter_struct       tli_init_struct;
    tli_layer_parameter_struct tli_layer_init_struct;

    rcu_periph_clock_enable(RCU_TLI);

    if (_tli_clock_config() != RT_EOK)
    {
        LOG_E("PLLSAI clock config failed");
        return -RT_ERROR;
    }

    /* TLI signal polarity configuration */
    tli_init_struct.signalpolarity_hs      = TLI_HSYN_ACTLIVE_LOW;
    tli_init_struct.signalpolarity_vs      = TLI_VSYN_ACTLIVE_LOW;
    tli_init_struct.signalpolarity_de      = TLI_DE_ACTLIVE_LOW;
    tli_init_struct.signalpolarity_pixelck = TLI_PIXEL_CLOCK_TLI;

    /* TLI display timing configuration */
    tli_init_struct.synpsz_hpsz   = HORIZONTAL_SYNCHRONOUS_PULSE - 1;
    tli_init_struct.synpsz_vpsz   = VERTICAL_SYNCHRONOUS_PULSE - 1;
    tli_init_struct.backpsz_hbpsz = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH - 1;
    tli_init_struct.backpsz_vbpsz = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH - 1;
    tli_init_struct.activesz_hasz = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH + ACTIVE_WIDTH - 1;
    tli_init_struct.activesz_vasz = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH + ACTIVE_HEIGHT - 1;
    tli_init_struct.totalsz_htsz  = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH + ACTIVE_WIDTH + HORIZONTAL_FRONT_PORCH - 1;
    tli_init_struct.totalsz_vtsz  = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH + ACTIVE_HEIGHT + VERTICAL_FRONT_PORCH - 1;

    /* background color (white, matching official demo) */
    tli_init_struct.backcolor_red   = 0xFF;
    tli_init_struct.backcolor_green = 0xFF;
    tli_init_struct.backcolor_blue  = 0xFF;
    tli_init(&tli_init_struct);

    /* TLI layer0 configuration - the visible framebuffer */
    tli_layer_init_struct.layer_window_leftpos      = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH;
    tli_layer_init_struct.layer_window_rightpos     = LCD_WIDTH + HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH - 1;
    tli_layer_init_struct.layer_window_toppos       = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH;
    tli_layer_init_struct.layer_window_bottompos    = LCD_HEIGHT + VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH - 1;
    tli_layer_init_struct.layer_ppf                 = LAYER_PPF_RGB565;
    tli_layer_init_struct.layer_sa                  = 0xFF;
    tli_layer_init_struct.layer_default_blue        = 0x00;
    tli_layer_init_struct.layer_default_green       = 0x00;
    tli_layer_init_struct.layer_default_red         = 0x00;
    tli_layer_init_struct.layer_default_alpha       = 0x00;
    tli_layer_init_struct.layer_acf1                = LAYER_ACF1_PASA;
    tli_layer_init_struct.layer_acf2                = LAYER_ACF2_PASA;
    tli_layer_init_struct.layer_frame_bufaddr       = LCD_FB_ADDR;
    tli_layer_init_struct.layer_frame_line_length   = (LCD_WIDTH * LCD_BYTES_PER_PIXEL) + 3;
    tli_layer_init_struct.layer_frame_buf_stride_offset = LCD_WIDTH * LCD_BYTES_PER_PIXEL;
    tli_layer_init_struct.layer_frame_total_line_number = LCD_HEIGHT;
    tli_layer_init(LAYER0, &tli_layer_init_struct);

    tli_layer_enable(LAYER0);
    tli_reload_config(TLI_REQUEST_RELOAD_EN);
    tli_enable();

    return RT_EOK;
}

/* ------------------------------------------------------------------------- */
/* RT-Thread graphic device operations                                       */
/* ------------------------------------------------------------------------- */

static void _lcd_set_pixel(const char *pixel, int x, int y)
{
    if ((x < 0) || (x >= LCD_WIDTH) || (y < 0) || (y >= LCD_HEIGHT))
    {
        return;
    }

    *((rt_uint16_t *)LCD_FB_ADDR + y * LCD_WIDTH + x) = *(const rt_uint16_t *)pixel;
}

static void _lcd_get_pixel(char *pixel, int x, int y)
{
    if ((x < 0) || (x >= LCD_WIDTH) || (y < 0) || (y >= LCD_HEIGHT))
    {
        return;
    }

    *(rt_uint16_t *)pixel = *((rt_uint16_t *)LCD_FB_ADDR + y * LCD_WIDTH + x);
}

static void _lcd_draw_hline(const char *pixel, int x1, int x2, int y)
{
    rt_uint16_t color = *(const rt_uint16_t *)pixel;
    rt_uint16_t *fb;

    if ((y < 0) || (y >= LCD_HEIGHT))
    {
        return;
    }
    if (x1 < 0) x1 = 0;
    if (x2 > LCD_WIDTH) x2 = LCD_WIDTH;

    fb = (rt_uint16_t *)LCD_FB_ADDR + y * LCD_WIDTH + x1;
    while (x1 < x2)
    {
        *fb++ = color;
        x1++;
    }
}

static void _lcd_draw_vline(const char *pixel, int x, int y1, int y2)
{
    rt_uint16_t color = *(const rt_uint16_t *)pixel;
    rt_uint16_t *fb;

    if ((x < 0) || (x >= LCD_WIDTH))
    {
        return;
    }
    if (y1 < 0) y1 = 0;
    if (y2 > LCD_HEIGHT) y2 = LCD_HEIGHT;

    fb = (rt_uint16_t *)LCD_FB_ADDR + y1 * LCD_WIDTH + x;
    while (y1 < y2)
    {
        *fb = color;
        fb += LCD_WIDTH;
        y1++;
    }
}

static void _lcd_blit_line(const char *pixel, int x, int y, rt_size_t size)
{
    rt_uint16_t *fb;
    const rt_uint16_t *p = (const rt_uint16_t *)pixel;
    rt_size_t i;

    if ((x < 0) || (y < 0) || (y >= LCD_HEIGHT))
    {
        return;
    }
    if ((x + (int)size) > LCD_WIDTH)
    {
        size = LCD_WIDTH - x;
    }

    /* 16-bit stores only: framebuffer is in SDRAM (Device memory on
     * Cortex-M33), so rt_memcpy could generate unaligned 32-bit access
     * that faults when x is odd. */
    fb = (rt_uint16_t *)LCD_FB_ADDR + y * LCD_WIDTH + x;
    for (i = 0; i < size; i++)
    {
        fb[i] = p[i];
    }
}

static struct rt_device_graphic_ops _lcd_ops =
{
    _lcd_set_pixel,
    _lcd_get_pixel,
    _lcd_draw_hline,
    _lcd_draw_vline,
    _lcd_blit_line,
};

static rt_err_t _lcd_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_GET_INFO:
        if (args == RT_NULL)
        {
            return -RT_ERROR;
        }
        rt_memcpy(args, &_lcd_info, sizeof(_lcd_info));
        break;

    case RTGRAPHIC_CTRL_RECT_UPDATE:
        /* TLI scans the framebuffer continuously; nothing to do here. */
        break;

    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
static struct rt_device_ops _lcd_device_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _lcd_control,
};
#endif

static int rt_hw_lcd_init(void)
{
    rt_err_t ret;

    /* clear the framebuffer to black before the TLI starts scanning it */
    rt_memset((void *)LCD_FB_ADDR, 0, LCD_FB_SIZE);

    _tli_gpio_config();

    ret = _tli_config();
    if (ret != RT_EOK)
    {
        LOG_E("TLI init failed");
        return ret;
    }
    LOG_I("TLI init done, framebuffer @ 0x%08X", LCD_FB_ADDR);

    /* fill the graphic device information */
    _lcd_info.pixel_format   = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    _lcd_info.bits_per_pixel = LCD_BITS_PER_PIXEL;
    _lcd_info.pitch          = LCD_WIDTH * LCD_BYTES_PER_PIXEL;
    _lcd_info.width          = LCD_WIDTH;
    _lcd_info.height         = LCD_HEIGHT;
    _lcd_info.framebuffer    = (rt_uint8_t *)LCD_FB_ADDR;
    _lcd_info.smem_len       = LCD_FB_SIZE;

    _lcd_device.type      = RT_Device_Class_Graphic;
    _lcd_device.user_data = &_lcd_ops;
#ifdef RT_USING_DEVICE_OPS
    _lcd_device.ops       = &_lcd_device_ops;
#else
    _lcd_device.init      = RT_NULL;
    _lcd_device.open      = RT_NULL;
    _lcd_device.close     = RT_NULL;
    _lcd_device.read      = RT_NULL;
    _lcd_device.write     = RT_NULL;
    _lcd_device.control   = _lcd_control;
#endif

    ret = rt_device_register(&_lcd_device, LCD_DEVICE_NAME, RT_DEVICE_FLAG_RDWR);
    if (ret != RT_EOK)
    {
        LOG_E("register %s device failed", LCD_DEVICE_NAME);
        return ret;
    }

    LOG_I("LCD(TLI) %dx%d RGB565 init ok, framebuffer @ 0x%08x", LCD_WIDTH, LCD_HEIGHT, LCD_FB_ADDR);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_lcd_init);

#endif /* BSP_USING_LCD */
