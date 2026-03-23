/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 */

#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include <board.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_SERIES_GD32E50x)
#include "config/e50x/dma_config.h"
#include "config/e50x/uart_config.h"
#include "config/e50x/spi_config.h"
#elif defined(SOC_SERIES_GD32F5xx)
#include "config/f527/dma_config.h"
#include "config/f527/uart_config.h"
#include "config/f527/spi_config.h"
#elif defined(SOC_SERIES_GD32H7xx)
#include "config/h75e/dma_config.h"
#include "config/h75e/uart_config.h"
#include "config/h75e/spi_config.h"
#elif defined(SOC_SERIES_GD32H75E)
#include "config/h75e/dma_config.h"
#include "config/h75e/uart_config.h"
#include "config/h75e/spi_config.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
