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
#elif defined(SOC_SERIES_GD32W51x_F5HC)
#include "config/w51x_f5hc/dma_config.h"
#include "config/w51x_f5hc/uart_config.h"
#include "config/w51x_f5hc/spi_config.h"
#include "config/w51x_f5hc/i2c_config.h"
#elif defined(SOC_SERIES_GD32F4xx)
#include "config/f4xx/dma_config.h"
#include "config/f4xx/uart_config.h"
#include "config/f4xx/spi_config.h"
#include "config/f4xx/i2c_config.h"
#elif defined(SOC_SERIES_GD32F5xx)
#include "config/f527/dma_config.h"
#include "config/f527/uart_config.h"
#include "config/f527/spi_config.h"
#include "config/f527/i2c_config.h"
#elif defined(SOC_SERIES_GD32H7xx)
#include "config/h7xx/dma_config.h"
#include "config/h7xx/uart_config.h"
#include "config/h7xx/spi_config.h"
#include "config/h7xx/i2c_config.h"
#elif defined(SOC_SERIES_GD32H77x)
#include "config/h77x/dma_config.h"
#include "config/h77x/uart_config.h"
#include "config/h77x/spi_config.h"
#include "config/h77x/i2c_config.h"
#elif defined(SOC_SERIES_GD32H75E)
#include "config/h75e/dma_config.h"
#include "config/h75e/uart_config.h"
#include "config/h75e/spi_config.h"
#include "config/h75e/i2c_config.h"
#elif defined(SOC_SERIES_GD32F30x)
#include "config/f30x/dma_config.h"
#include "config/f30x/uart_config.h"
#include "config/f30x/spi_config.h"
#include "config/f30x/i2c_config.h"
#elif defined(SOC_SERIES_GD32F20x)
#include "config/f20x/dma_config.h"
#include "config/f20x/uart_config.h"
#include "config/f20x/spi_config.h"
#include "config/f20x/i2c_config.h"
#elif defined(SOC_SERIES_GD32E51x)
#include "config/e51x/dma_config.h"
#include "config/e51x/uart_config.h"
#include "config/e51x/i2c_config.h"
#include "config/e51x/spi_config.h"
#elif defined(SOC_SERIES_GD32L23x)
#include "config/l23x/dma_config.h"
#include "config/l23x/uart_config.h"
#include "config/l23x/spi_config.h"
#include "config/l23x/i2c_config.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
