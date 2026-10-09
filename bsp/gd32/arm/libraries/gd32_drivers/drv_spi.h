/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-20     BruceOu      first implementation
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

struct gd32_spi_cs
{
    uint32_t GPIOx;
    uint32_t GPIO_Pin;
};

/* gd32 spi dirver class */

#if defined(BSP_USING_SPI_DMA)
#include "drv_dma.h"
#include "drv_config.h"
#endif


struct gd32_spi
{
    uint32_t spi_periph;
    rcu_periph_enum spi_clk;
    IRQn_Type irqn;
    char *bus_name;
    struct rt_spi_bus *spi_bus;
#ifdef BSP_USING_SPI_DMA
    struct dma_config *dma_tx;
    struct dma_config *dma_rx;
#endif
};


/* This function initializes the SPI pin */
void gd32_spi_init(struct gd32_spi *gd32_spi);


rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SPI_H__ */

