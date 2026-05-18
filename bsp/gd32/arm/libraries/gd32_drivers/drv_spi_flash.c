/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-31     BruceOu      first implementation
 * 2023-06-03     CX           fixed sf probe error bug
 * 2024-05-30     godmial      refactor driver for multi-SPI bus auto-mount
 */
#include <board.h>
#include "drv_spi.h"
#include "dev_spi_flash.h"

#ifdef RT_USING_SFUD
#include "dev_spi_flash_sfud.h"
#endif

#if defined(BSP_USING_QSPI)
#include "drv_qspi.h"
#endif

#include <rthw.h>
#include <finsh.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#endif

struct spi_flash_config
{
    const char *bus_name;
    const char *device_name;
    const char *flash_name;
    rt_base_t   cs_pin;
};

static const struct spi_flash_config flash_configs[] =
{
#if defined(BSP_USING_SPI0) && defined(BSP_SPI0_FLASH_CS_PIN)
    {
        .bus_name    = "spi0",
        .device_name = "spi00",
        .flash_name  = "gd25q_spi0",
        .cs_pin      = BSP_SPI0_FLASH_CS_PIN,
    },
#endif

#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_FLASH_CS_PIN)
    {
        .bus_name    = "spi1",
        .device_name = "spi10",
        .flash_name  = "gd25q_spi1",
        .cs_pin      = BSP_SPI1_FLASH_CS_PIN,
    },
#endif

#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_FLASH_CS_PIN)
    {
        .bus_name    = "spi2",
        .device_name = "spi20",
        .flash_name  = "gd25q_spi2",
        .cs_pin      = BSP_SPI2_FLASH_CS_PIN,
    },
#endif

#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_FLASH_CS_PIN)
    {
        .bus_name    = "spi3",
        .device_name = "spi30",
        .flash_name  = "gd25q_spi3",
        .cs_pin      = BSP_SPI3_FLASH_CS_PIN,
    },
#endif

#if defined(BSP_USING_SPI4) && defined(BSP_SPI4_FLASH_CS_PIN)
    {
        .bus_name    = "spi4",
        .device_name = "spi40",
        .flash_name  = "gd25q_spi4",
        .cs_pin      = BSP_SPI4_FLASH_CS_PIN,
    },
#endif
};

#if defined(BSP_USING_QSPI) && defined(RT_USING_SFUD)
struct qspi_flash_config
{
    const char *bus_name;
    const char *device_name;
    const char *flash_name;
    rt_base_t   cs_pin;
    rt_uint8_t  data_line_width;
};

static const struct qspi_flash_config qspi_flash_configs[] =
{
#if defined(BSP_USING_QSPI0) && defined(BSP_QSPI0_FLASH_CS_PIN)
    {
        .bus_name        = "qspi0",
        .device_name     = "qspi00",
        .flash_name      = "gd25q_qspi0",
        .cs_pin          = BSP_QSPI0_FLASH_CS_PIN,
        .data_line_width = 4,
    },
#endif
};
#endif


static int spi_flash_init(void)
{
    int result = RT_EOK;

    for (size_t i = 0; i < sizeof(flash_configs) / sizeof(flash_configs[0]); i++)
    {
        const struct spi_flash_config *cfg = &flash_configs[i];

        if (rt_hw_spi_device_attach(cfg->bus_name, cfg->device_name, cfg->cs_pin) != RT_EOK)
        {
            rt_kprintf("Failed to attach device %s on bus %s\n", cfg->device_name, cfg->bus_name);
            if (result == RT_EOK)
            {
                result = -RT_ERROR;
            }
            continue;
        }

#ifdef RT_USING_SFUD
        if (RT_NULL == rt_sfud_flash_probe(cfg->flash_name, cfg->device_name))
        {
            rt_kprintf("SFUD probe failed: %s\n", cfg->flash_name);
            if (result == RT_EOK)
            {
                result = -RT_ERROR;
            }
            continue;
        }
#endif
    }

    return result;
}
INIT_COMPONENT_EXPORT(spi_flash_init);

#if defined(BSP_USING_QSPI) && defined(RT_USING_SFUD)
static int qspi_flash_init(void)
{
    int result = RT_EOK;

    for (size_t i = 0; i < sizeof(qspi_flash_configs) / sizeof(qspi_flash_configs[0]); i++)
    {
        const struct qspi_flash_config *cfg = &qspi_flash_configs[i];

        if (rt_hw_qspi_device_attach(cfg->bus_name, cfg->device_name,
                                     cfg->cs_pin, cfg->data_line_width,
                                     RT_NULL, RT_NULL) != RT_EOK)
        {
            rt_kprintf("Failed to attach QSPI device %s on bus %s\n", cfg->device_name, cfg->bus_name);
            if (result == RT_EOK)
            {
                result = -RT_ERROR;
            }
            continue;
        }

#ifdef RT_USING_SFUD
        if (RT_NULL == rt_sfud_flash_probe(cfg->flash_name, cfg->device_name))
        {
            rt_kprintf("SFUD probe failed: %s\n", cfg->flash_name);
            if (result == RT_EOK)
            {
                result = -RT_ERROR;
            }
            continue;
        }
#endif
    }

    return result;
}
INIT_COMPONENT_EXPORT(qspi_flash_init);
#endif
