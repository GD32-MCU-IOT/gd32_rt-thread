/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-03-27     RT-Thread    first implementation for GD32H7xx OSPI HyperBus PSRAM
 */

#ifndef __DRV_OSPI_H__
#define __DRV_OSPI_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

/* OSPI control commands */
#define OSPI_CTRL_CONFIG_SET      (0x01)
#define OSPI_CTRL_ADDR_SET        (0x02)
#define OSPI_CTRL_ENTER_MMAP      (0x03)
#define OSPI_CTRL_EXIT_MMAP       (0x04)

/* OSPI memory mapped base address (GD32H7xx) */
#define OSPI0_MAPPED_ADDR         (0x90000000U)
#define OSPI1_MAPPED_ADDR         (0x70000000U)

/* OSPI PSRAM max size: 256MB for memory-mapped mode */
#define OSPI_PSRAM_MAX_SIZE       (0x10000000U)

/* GSR6W28AM mode register addresses */
#define GSR6W28AM_MODE_REG1_ADDR  (0x00000002U)
#define GSR6W28AM_MODE_REG2_ADDR  (0x00000800U)
#define GSR6W28AM_MODE_REG3_ADDR  (0x00000801U)

/* OSPI driver class */
struct gd32_ospi
{
    uint32_t ospi_periph;
    const char *device_name;
    rcu_periph_enum ospi_clk;
    uint32_t mapped_addr;
};

/* OSPI device class */
struct gd32_ospi_dev
{
    struct rt_device parent;
    struct gd32_ospi *gd32_ospi_drv;
    ospi_parameter_struct ospi_param;
    uint32_t psram_addr;
};

/* OSPI PSRAM configuration structure */
struct rt_ospi_configuration
{
    uint32_t prescaler;         /* clock prescaler (0~255), OSPI_CLK = AHB_CLK / (prescaler + 1) */
    uint32_t device_size;       /* PSRAM size, e.g. OSPI_MESZ_512_MBS */
    uint32_t cs_hightime;       /* chip select high time, e.g. OSPI_CS_HIGH_TIME_3_CYCLE */
    uint32_t fifo_threshold;    /* FIFO threshold, e.g. OSPI_FIFO_THRESHOLD_5 */
    uint32_t delay_hold_cycle;  /* delay hold cycle, e.g. OSPI_DELAY_HOLD_QUARTER_CYCLE */
    uint32_t rw_recovery_time;  /* HyperBus read-write recovery time (0~255) */
    uint32_t access_time;       /* HyperBus access time (0~255) */
    uint32_t refrate;           /* refresh rate */
};

void gd32_ospi_gpio_init(const struct gd32_ospi *ospi);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_OSPI_H__ */
