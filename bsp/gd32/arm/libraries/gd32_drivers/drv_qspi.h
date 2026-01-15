/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-20     BruceOu      first implementation
 */

#ifndef __DRV_QSPI_H__
#define __DRV_QSPI_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

struct gd32_qspi_bus
{
    uint32_t spi_periph;
    rcu_periph_enum spi_clk;
    const char *bus_name;
    struct rt_spi_bus *spi_bus;
};

void gd32_qspi_init(struct gd32_qspi_bus *gd32_qspi);

rt_err_t rt_hw_qspi_device_attach(const char *bus_name,
                                  const char *device_name,
                                  rt_base_t cs_pin,
                                  rt_uint8_t data_line_width,
                                  void (*enter_qspi_mode)(struct rt_qspi_device *device),
                                  void (*exit_qspi_mode)(struct rt_qspi_device *device));

#ifdef __cplusplus
}
#endif

#endif /* __DRV_QSPI_H__ */
