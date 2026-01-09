/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-01     RT-Thread    first version for GD32F50x
 * 2026-01-04     RT-Thread    refactor based on STM32 QSPI driver and GD32 Demo
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

rt_err_t qspi_send_cmd(struct rt_qspi_device *device, rt_uint8_t cmd);

rt_ssize_t qspi_read(struct rt_qspi_device *device, rt_uint8_t cmd, 
                     rt_uint32_t addr, rt_uint8_t dummy_cycles, rt_uint8_t data_lines,
                     rt_uint8_t *buf, rt_size_t len);

rt_ssize_t qspi_write(struct rt_qspi_device *device, rt_uint8_t cmd,
                      rt_uint32_t addr, rt_uint8_t data_lines,
                      const rt_uint8_t *buf, rt_size_t len);

rt_err_t qspi_wait_busy(struct rt_qspi_device *device, rt_uint32_t timeout_ms);

rt_err_t qspi_enable_quad(struct rt_qspi_device *device);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_QSPI_H__ */
