/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-20     BruceOu      first implementation
 */
#include "drv_spi.h"

#ifdef RT_USING_SPI

/* GD32M53x has different SPI API, SPI driver needs adaptation */
#if defined(SOC_SERIES_GD32M53x)
#include "gd32m53x_spi.h"

#define SPI0                            SPI
#define RCU_SPI0                        RCU_SPI
#define SPI0_IRQn                       SPI_IRQn

#define spi_i2s_flag_get(periph, flag)          spi_flag_get(flag)
#define spi_i2s_data_transmit(periph, data)     spi_data_transmit(data)
#define spi_i2s_data_receive(periph)            spi_data_receive()
#define spi_crc_off(periph)                     spi_crc_off()
#define spi_init(periph, init_struct)           spi_init(init_struct)
#define spi_enable(periph)                      spi_enable()
#define spi_disable(periph)                     spi_disable()

#endif /* SOC_SERIES_GD32M53x */

/* Compatibility macros: unify H7xx vs non-H7xx SPI data register differences
 * (DMA request/subperiph/deinit macros live in drv_dma.h) */
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
#define SPI_RXDATA_REG(periph)                      SPI_RDATA(periph)
#define SPI_TXDATA_REG(periph)                      SPI_TDATA(periph)
#else
#define SPI_RXDATA_REG(periph)                      SPI_DATA(periph)
#define SPI_TXDATA_REG(periph)                      SPI_DATA(periph)
#endif

#ifndef BSP_SPI_XFER_TIMEOUT
#define BSP_SPI_XFER_TIMEOUT 1000
#endif

#if defined(BSP_USING_SPI0) || defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) || defined(BSP_USING_SPI4) || defined(BSP_USING_SPI5)
#define LOG_TAG              "drv.spi"

#include <rtdbg.h>

/**
 * @brief Wait for SPI flag with timeout
 * @param periph SPI peripheral
 * @param flag   SPI flag to wait for
 * @retval RT_EOK on success, -RT_ETIMEOUT on timeout
 */
rt_inline rt_err_t gd32_spi_wait_flag(uint32_t periph, uint32_t flag)
{
    rt_tick_t timeout = rt_tick_from_millisecond(BSP_SPI_XFER_TIMEOUT);
    rt_tick_t start = rt_tick_get();

    while (RESET == spi_i2s_flag_get(periph, flag))
    {
        if (rt_tick_get() - start > timeout)
        {
            LOG_E("spi wait flag 0x%x timeout", flag);
            return -RT_ETIMEOUT;
        }
    }
    return RT_EOK;
}

#ifdef BSP_USING_SPI0
static struct rt_spi_bus spi_bus0;
#endif
#ifdef BSP_USING_SPI1
static struct rt_spi_bus spi_bus1;
#endif
#ifdef BSP_USING_SPI2
static struct rt_spi_bus spi_bus2;
#endif
#ifdef BSP_USING_SPI3
static struct rt_spi_bus spi_bus3;
#endif
#ifdef BSP_USING_SPI4
static struct rt_spi_bus spi_bus4;
#endif
#ifdef BSP_USING_SPI5
static struct rt_spi_bus spi_bus5;
#endif

#if !defined(SOC_SERIES_GD32H75E) && !defined(SOC_SERIES_GD32E51x) && !defined(SOC_SERIES_GD32F3x0) \
 && !defined(SOC_SERIES_GD32F50x) && !defined(SOC_SERIES_GD32G5x3) && !defined(SOC_SERIES_GD32C11x) \
 && !defined(SOC_SERIES_GD32L23x) && !defined(SOC_SERIES_GD32E11x) && !defined(SOC_SERIES_GD32H77x) \
 && !defined(SOC_SERIES_GD32H7xx) && !defined(SOC_SERIES_GD32F5xx) && !defined(SOC_SERIES_GD32M53x) \
 && !defined(SOC_SERIES_GD32F30x) && !defined(SOC_SERIES_GD32W51x_F5HC) && !defined(SOC_SERIES_GD32F4xx)

static const struct gd32_spi spi_bus_obj[] = {

#ifdef BSP_USING_SPI0
    {
        SPI0,
        "spi0",
        RCU_SPI0,
        RCU_GPIOA,
        RCU_GPIOA,
        RCU_GPIOA,
        &spi_bus0,
        GPIOA,
        GPIOA,
        GPIOA,
#if defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32H7xx) || (defined SOC_SERIES_GD32F5xx)
        GPIO_AF_5,
#endif
#if defined (SOC_SERIES_GD32E23x)
        GPIO_AF_0,
#endif
        GPIO_PIN_5,
        GPIO_PIN_6,
        GPIO_PIN_7,
    },
#endif /* BSP_USING_SPI0 */

#ifdef BSP_USING_SPI1
    {
        SPI1,
        "spi1",
        RCU_SPI1,
        RCU_GPIOB,
        RCU_GPIOB,
        RCU_GPIOB,
        &spi_bus1,
        GPIOB,
        GPIOB,
        GPIOB,
#if defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32H7xx) || (defined SOC_SERIES_GD32F5xx)
        GPIO_AF_5,
#endif
#if defined SOC_SERIES_GD32E23x
        GPIO_AF_0,
#endif

        GPIO_PIN_13,
        GPIO_PIN_14,
        GPIO_PIN_15,
    },
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI2
    {
        SPI2,
        "spi2",
        RCU_SPI2,
        RCU_GPIOB,
        RCU_GPIOB,
        RCU_GPIOB,
        &spi_bus2,
        GPIOB,
        GPIOB,
        GPIOB,
#if defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32H7xx) || (defined SOC_SERIES_GD32F5xx)
        GPIO_AF_6,
#endif
        GPIO_PIN_3,
        GPIO_PIN_4,
        GPIO_PIN_5,
    },
#endif /* BSP_USING_SPI2 */

#ifdef BSP_USING_SPI3
    {
        SPI3,
        "spi3",
        RCU_SPI3,
        RCU_GPIOE,
        RCU_GPIOE,
        RCU_GPIOE,
        &spi_bus3,
        GPIOE,
        GPIOE,
        GPIOE,
#if defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32H7xx) || (defined SOC_SERIES_GD32F5xx)
        GPIO_AF_5,
#endif
        GPIO_PIN_2,
        GPIO_PIN_5,
        GPIO_PIN_6,
    },
#endif /* BSP_USING_SPI3 */

#ifdef BSP_USING_SPI4
    {
        SPI4,
        "spi4",
        RCU_SPI4,
        RCU_GPIOF,
        RCU_GPIOF,
        RCU_GPIOF,
        &spi_bus4,
        GPIOF,
        GPIOF,
        GPIOF,
#if defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32H7xx) || (defined SOC_SERIES_GD32F5xx)
        GPIO_AF_5,
#endif
        GPIO_PIN_7,
        GPIO_PIN_8,
        GPIO_PIN_9,

    },
#endif /* BSP_USING_SPI4 */

#ifdef BSP_USING_SPI5
    {
        SPI5,
        "spi5",
        RCU_SPI5,
        RCU_GPIOG,
        RCU_GPIOG,

        RCU_GPIOG,
        &spi_bus5,
        GPIOG,
        GPIOG,
        GPIOG,
#if defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32H7xx) || (defined SOC_SERIES_GD32F5xx)
        GPIO_AF_5,
#endif
        GPIO_PIN_13,
        GPIO_PIN_12,
        GPIO_PIN_14,
    }
#endif /* BSP_USING_SPI5 */
};

#else

/* Static DMA configurations - safer than compound literals for IAR/older compilers */
#ifdef BSP_SPI0_USING_DMA
static struct dma_config spi0_dma_tx_cfg = SPI0_TX_DMA_CONFIG;
static struct dma_config spi0_dma_rx_cfg = SPI0_RX_DMA_CONFIG;
#endif
#ifdef BSP_SPI1_USING_DMA
static struct dma_config spi1_dma_tx_cfg = SPI1_TX_DMA_CONFIG;
static struct dma_config spi1_dma_rx_cfg = SPI1_RX_DMA_CONFIG;
#endif
#ifdef BSP_SPI2_USING_DMA
static struct dma_config spi2_dma_tx_cfg = SPI2_TX_DMA_CONFIG;
static struct dma_config spi2_dma_rx_cfg = SPI2_RX_DMA_CONFIG;
#endif
#ifdef BSP_SPI3_USING_DMA
static struct dma_config spi3_dma_tx_cfg = SPI3_TX_DMA_CONFIG;
static struct dma_config spi3_dma_rx_cfg = SPI3_RX_DMA_CONFIG;
#endif
#ifdef BSP_SPI4_USING_DMA
static struct dma_config spi4_dma_tx_cfg = SPI4_TX_DMA_CONFIG;
static struct dma_config spi4_dma_rx_cfg = SPI4_RX_DMA_CONFIG;
#endif
#ifdef BSP_SPI5_USING_DMA
static struct dma_config spi5_dma_tx_cfg = SPI5_TX_DMA_CONFIG;
static struct dma_config spi5_dma_rx_cfg = SPI5_RX_DMA_CONFIG;
#endif

static const struct gd32_spi spi_bus_obj[] = {

#ifdef BSP_USING_SPI0
    {
        .spi_periph = SPI0,
        .spi_clk = RCU_SPI0,
        .irqn = SPI0_IRQn,
        .bus_name = "spi0",
        .spi_bus = &spi_bus0,
#ifdef BSP_USING_SPI_DMA
#ifdef BSP_SPI0_USING_DMA
        .dma_tx = &spi0_dma_tx_cfg,
        .dma_rx = &spi0_dma_rx_cfg,
#else
        .dma_tx = RT_NULL,
        .dma_rx = RT_NULL,
#endif
#endif
    },
#endif /* BSP_USING_SPI0 */

#ifdef BSP_USING_SPI1
    {
        .spi_periph = SPI1,
        .spi_clk = RCU_SPI1,
#if defined(SOC_SERIES_GD32E51x)
        .irqn = SPI1_I2S1ADD_IRQn,
#else
        .irqn = SPI1_IRQn,
#endif
        .bus_name = "spi1",
        .spi_bus = &spi_bus1,
#ifdef BSP_USING_SPI_DMA
#ifdef BSP_SPI1_USING_DMA
        .dma_tx = &spi1_dma_tx_cfg,
        .dma_rx = &spi1_dma_rx_cfg,
#else
        .dma_tx = RT_NULL,
        .dma_rx = RT_NULL,
#endif
#endif
    },
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI2
    {
        .spi_periph = SPI2,
        .spi_clk = RCU_SPI2,
#if defined(SOC_SERIES_GD32E51x)
        .irqn = SPI2_I2S2ADD_IRQn,
#else
        .irqn = SPI2_IRQn,
#endif
        .bus_name = "spi2",
        .spi_bus = &spi_bus2,
#ifdef BSP_USING_SPI_DMA
#ifdef BSP_SPI2_USING_DMA
        .dma_tx = &spi2_dma_tx_cfg,
        .dma_rx = &spi2_dma_rx_cfg,
#else
        .dma_tx = RT_NULL,
        .dma_rx = RT_NULL,
#endif
#endif
    },
#endif /* BSP_USING_SPI2 */

#ifdef BSP_USING_SPI3
    {
        .spi_periph = SPI3,
        .spi_clk = RCU_SPI3,
        .irqn = SPI3_IRQn,
        .bus_name = "spi3",
        .spi_bus = &spi_bus3,
#ifdef BSP_USING_SPI_DMA
#ifdef BSP_SPI3_USING_DMA
        .dma_tx = &spi3_dma_tx_cfg,
        .dma_rx = &spi3_dma_rx_cfg,
#else
        .dma_tx = RT_NULL,
        .dma_rx = RT_NULL,
#endif
#endif
    },
#endif /* BSP_USING_SPI3 */

#ifdef BSP_USING_SPI4
    {
        .spi_periph = SPI4,
        .spi_clk = RCU_SPI4,
        .irqn = SPI4_IRQn,
        .bus_name = "spi4",
        .spi_bus = &spi_bus4,
#ifdef BSP_USING_SPI_DMA
#ifdef BSP_SPI4_USING_DMA
        .dma_tx = &spi4_dma_tx_cfg,
        .dma_rx = &spi4_dma_rx_cfg,
#else
        .dma_tx = RT_NULL,
        .dma_rx = RT_NULL,
#endif
#endif
    },
#endif /* BSP_USING_SPI4 */

#ifdef BSP_USING_SPI5
    {
        .spi_periph = SPI5,
        .spi_clk = RCU_SPI5,
        .irqn = SPI5_IRQn,
        .bus_name = "spi5",
        .spi_bus = &spi_bus5,
#ifdef BSP_USING_SPI_DMA
#ifdef BSP_SPI5_USING_DMA
        .dma_tx = &spi5_dma_tx_cfg,
        .dma_rx = &spi5_dma_rx_cfg,
#else
        .dma_tx = RT_NULL,
        .dma_rx = RT_NULL,
#endif
#endif
    },
#endif /* BSP_USING_SPI5 */
};

#endif

/* private rt-thread spi ops function */
static rt_err_t spi_configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_ssize_t spixfer(struct rt_spi_device* device, struct rt_spi_message* message);

static struct rt_spi_ops gd32_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

#if !defined(SOC_SERIES_GD32H75E) && !defined(SOC_SERIES_GD32E51x) && !defined(SOC_SERIES_GD32F3x0) \
 && !defined(SOC_SERIES_GD32F50x) && !defined(SOC_SERIES_GD32G5x3) && !defined(SOC_SERIES_GD32C11x) \
 && !defined(SOC_SERIES_GD32L23x) && !defined(SOC_SERIES_GD32E11x) && !defined(SOC_SERIES_GD32H77x) \
 && !defined(SOC_SERIES_GD32M53x) && !defined(SOC_SERIES_GD32H7xx) && !defined(SOC_SERIES_GD32F5xx) \
 && !defined(SOC_SERIES_GD32F30x) && !defined(SOC_SERIES_GD32W51x_F5HC) && !defined(SOC_SERIES_GD32F4xx)
/**
* @brief SPI Initialization
* @param gd32_spi: SPI BUS
* @retval None
*/
static void gd32_spi_init(struct gd32_spi *gd32_spi)
{
    /* enable SPI clock */
    rcu_periph_clock_enable(gd32_spi->spi_clk);
    rcu_periph_clock_enable(gd32_spi->sck_gpio_clk);
    rcu_periph_clock_enable(gd32_spi->miso_gpio_clk);
    rcu_periph_clock_enable(gd32_spi->mosi_gpio_clk);

#if defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32H7xx) \
 || defined (SOC_SERIES_GD32E23x)
    /*GPIO pin configuration*/
    gpio_af_set(gd32_spi->sck_spi_port, gd32_spi->alt_func_num, gd32_spi->sck_pin);
    gpio_af_set(gd32_spi->miso_spi_port, gd32_spi->alt_func_num, gd32_spi->miso_pin);
    gpio_af_set(gd32_spi->mosi_spi_port, gd32_spi->alt_func_num, gd32_spi->mosi_pin);
    gpio_mode_set(gd32_spi->sck_spi_port, GPIO_MODE_AF, GPIO_PUPD_NONE, gd32_spi->sck_pin);
    gpio_mode_set(gd32_spi->miso_spi_port, GPIO_MODE_AF, GPIO_PUPD_NONE, gd32_spi->miso_pin);
    gpio_mode_set(gd32_spi->mosi_spi_port, GPIO_MODE_AF, GPIO_PUPD_NONE, gd32_spi->mosi_pin);
    #if defined (SOC_SERIES_GD32H7xx)
    gpio_output_options_set(gd32_spi->sck_spi_port, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, gd32_spi->sck_pin);
    gpio_output_options_set(gd32_spi->miso_spi_port, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, gd32_spi->miso_pin);
    gpio_output_options_set(gd32_spi->mosi_spi_port, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ, gd32_spi->mosi_pin);
    #elif defined (SOC_SERIES_GD32E23x)
    gpio_output_options_set(gd32_spi->sck_spi_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, gd32_spi->sck_pin);
    gpio_output_options_set(gd32_spi->miso_spi_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, gd32_spi->miso_pin);
    gpio_output_options_set(gd32_spi->mosi_spi_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, gd32_spi->mosi_pin);
    #else
    gpio_output_options_set(gd32_spi->sck_spi_port, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, gd32_spi->sck_pin);
    gpio_output_options_set(gd32_spi->miso_spi_port, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, gd32_spi->miso_pin);
    gpio_output_options_set(gd32_spi->mosi_spi_port, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, gd32_spi->mosi_pin);
    #endif
#else
    /* Init SPI SCK MOSI */
    gpio_init(gd32_spi->sck_spi_port, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, gd32_spi->sck_pin);
    gpio_init(gd32_spi->mosi_spi_port, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, gd32_spi->mosi_pin);

    /* Init SPI MISO */
    gpio_init(gd32_spi->miso_spi_port, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, gd32_spi->miso_pin);
#endif

}
#else
#warning "gd32_spi_init should be defined in board_msd_init.c"
rt_weak void gd32_spi_init(struct gd32_spi *gd32_spi)
{
}
#endif

#if defined(BSP_USING_SPI_DMA)
static void gd32_spi_dma_init(struct gd32_spi *spi_device)
{
    gd32_dma_single_data_parameter_struct dma_init_struct;
    uint32_t spi_periph = spi_device->spi_periph;
    
    /* Enable DMA clock (the controller is described by the .rcu field of the */

    if (spi_device->dma_tx != RT_NULL)
    {
        rcu_periph_clock_enable(spi_device->dma_tx->rcu);
    }
    if (spi_device->dma_rx != RT_NULL)
    {
        rcu_periph_clock_enable(spi_device->dma_rx->rcu);
    }

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x) \
 || defined(SOC_SERIES_GD32F50x)
    /* H7xx requires DMAMUX clock */
    rcu_periph_clock_enable(RCU_DMAMUX);
#endif

    /* Configure DMA common parameters */
    gd32_dma_single_data_para_struct_init(&dma_init_struct);
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.priority = DMA_PRIORITY_HIGH;
    GD32_DMA_SET_MEMADDR(&dma_init_struct, 0);
    dma_init_struct.number = 0;
    
    /* RX DMA configuration */
    if (spi_device->dma_rx != RT_NULL)
    {
        gd32_dma_deinit(spi_device->dma_rx->periph, spi_device->dma_rx->channel);
        
        GD32_DMA_SET_DATAWIDTH(&dma_init_struct, spi_device->dma_rx->data_width);
        dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
        dma_init_struct.periph_addr = (uint32_t)&SPI_RXDATA_REG(spi_periph);
        gd32_dma_request_config(&dma_init_struct, spi_device->dma_rx);
        
        gd32_dma_single_data_mode_init(spi_device->dma_rx->periph, spi_device->dma_rx->channel, &dma_init_struct);
        gd32_dma_subperiph_config(spi_device->dma_rx->periph, spi_device->dma_rx->channel, spi_device->dma_rx);
        gd32_dma_circulation_disable(spi_device->dma_rx->periph, spi_device->dma_rx->channel);
        gd32_dma_channel_disable(spi_device->dma_rx->periph, spi_device->dma_rx->channel);
    }
    
    /* TX DMA configuration */
    if (spi_device->dma_tx != RT_NULL)
    {
        gd32_dma_deinit(spi_device->dma_tx->periph, spi_device->dma_tx->channel);
        
        GD32_DMA_SET_DATAWIDTH(&dma_init_struct, spi_device->dma_tx->data_width);
        dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
        dma_init_struct.periph_addr = (uint32_t)&SPI_TXDATA_REG(spi_periph);
        gd32_dma_request_config(&dma_init_struct, spi_device->dma_tx);
        
        gd32_dma_single_data_mode_init(spi_device->dma_tx->periph, spi_device->dma_tx->channel, &dma_init_struct);
        gd32_dma_subperiph_config(spi_device->dma_tx->periph, spi_device->dma_tx->channel, spi_device->dma_tx);
        gd32_dma_circulation_disable(spi_device->dma_tx->periph, spi_device->dma_tx->channel);
        gd32_dma_channel_disable(spi_device->dma_tx->periph, spi_device->dma_tx->channel);
    }
}

/**
 * @brief Disable DMA channels and clear flags
 * @param spi_device: SPI device structure
 * @param spi_periph: SPI peripheral
 * @retval None
 */
rt_inline void gd32_spi_dma_cleanup(struct gd32_spi *spi_device, uint32_t spi_periph)
{
    if (spi_device->dma_rx != RT_NULL)
    {
        gd32_dma_channel_disable(spi_device->dma_rx->periph, spi_device->dma_rx->channel);
        gd32_dma_flag_clear(spi_device->dma_rx->periph, spi_device->dma_rx->channel, DMA_FLAG_FTF);
        spi_dma_disable(spi_periph, SPI_DMA_RECEIVE);
    }

    if (spi_device->dma_tx != RT_NULL)
    {
        gd32_dma_channel_disable(spi_device->dma_tx->periph, spi_device->dma_tx->channel);
        gd32_dma_flag_clear(spi_device->dma_tx->periph, spi_device->dma_tx->channel, DMA_FLAG_FTF);
        spi_dma_disable(spi_periph, SPI_DMA_TRANSMIT);
    }
}

#endif

static rt_err_t spi_configure(struct rt_spi_device* device,
                          struct rt_spi_configuration* configuration)
{
    struct rt_spi_bus * spi_bus = (struct rt_spi_bus *)device->bus;
    struct gd32_spi *spi_device = (struct gd32_spi *)spi_bus->parent.user_data;
    spi_parameter_struct spi_init_struct;
    uint32_t spi_periph = spi_device->spi_periph;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    /* Call board-level SPI GPIO initialization */
    gd32_spi_init(spi_device);
    
#if defined(BSP_USING_SPI_DMA)
    /* Call board-level DMA initialization if DMA is enabled */
    if (spi_device->dma_tx != RT_NULL || spi_device->dma_rx != RT_NULL)
    {
        gd32_spi_dma_init(spi_device);
    }
#endif

#if defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32H75E) || defined (SOC_SERIES_GD32H77x)
    /* data_width */
    if(configuration->data_width >=4 && configuration->data_width <= 32)
    {
        spi_init_struct.data_size = CFG0_DZ(configuration->data_width - 1);
    }
    else
    {
        return -RT_EIO;
    }
#else
    /* data_width */
    if(configuration->data_width <= 8)
    {
        spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    }
    else if(configuration->data_width <= 16)
    {
        spi_init_struct.frame_size = SPI_FRAMESIZE_16BIT;
    }
    else
    {
        return -RT_EIO;
    }
#endif

    /* baudrate */
    {
        rcu_clock_freq_enum spi_src;
        uint32_t spi_apb_clock;
        uint32_t max_hz;

        max_hz = configuration->max_hz;

        LOG_D("sys   freq: %d\n", rcu_clock_freq_get(CK_SYS));
        LOG_D("CK_APB2 freq: %d\n", rcu_clock_freq_get(CK_APB2));
        LOG_D("max   freq: %d\n", max_hz);

        #if defined SOC_SERIES_GD32E23x || defined SOC_SERIES_GD32L23x || defined SOC_SERIES_GD32F3x0 \
         || defined SOC_SERIES_GD32M53x || defined SOC_SERIES_GD32W51x_F5HC
        spi_src = spi_periph == SPI0? CK_APB2:CK_APB1;
        #elif defined SOC_SERIES_GD32H7xx || defined SOC_SERIES_GD32H75E || defined SOC_SERIES_GD32H77x
        /* SPI default clock source */
        if (spi_periph == SPI0 || spi_periph == SPI1 || spi_periph == SPI2)
        {
            spi_src = CK_PLL0Q;
        }
        else
        {
            spi_src = CK_APB2;
        }
        #else
        if (spi_periph == SPI1 || spi_periph == SPI2)
        {
            spi_src = CK_APB1;
        }
        else
        {
            spi_src = CK_APB2;
        }
        #endif
        spi_apb_clock = rcu_clock_freq_get(spi_src);

        if(max_hz >= spi_apb_clock/2)
        {
            spi_init_struct.prescale = SPI_PSC_2;
        }
        else if (max_hz >= spi_apb_clock/4)
        {
            spi_init_struct.prescale = SPI_PSC_4;
        }
        else if (max_hz >= spi_apb_clock/8)
        {
            spi_init_struct.prescale = SPI_PSC_8;
        }
        else if (max_hz >= spi_apb_clock/16)
        {
            spi_init_struct.prescale = SPI_PSC_16;
        }
        else if (max_hz >= spi_apb_clock/32)
        {
            spi_init_struct.prescale = SPI_PSC_32;
        }
        else if (max_hz >= spi_apb_clock/64)
        {
            spi_init_struct.prescale = SPI_PSC_64;
        }
        else if (max_hz >= spi_apb_clock/128)
        {
            spi_init_struct.prescale = SPI_PSC_128;
        }
        else
        {
            /*  min prescaler 256 */
            spi_init_struct.prescale = SPI_PSC_256;
        }
    } /* baudrate */

    switch(configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
        break;
    case RT_SPI_MODE_1:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_2EDGE;
        break;
    case RT_SPI_MODE_2:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_1EDGE;
        break;
    case RT_SPI_MODE_3:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
        break;
    }

    /* MSB or LSB */
    if(configuration->mode & RT_SPI_MSB)
    {
        spi_init_struct.endian = SPI_ENDIAN_MSB;
    }
    else
    {
        spi_init_struct.endian = SPI_ENDIAN_LSB;
    }

    spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.nss = SPI_NSS_SOFT;
#if defined SOC_SERIES_GD32L23x
    spi_fifo_access_size_config(spi_periph, SPI_BYTE_ACCESS);
#endif
    spi_crc_off(spi_periph);

#if defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32H75E) || defined (SOC_SERIES_GD32H77x)
    /* enable SPI byte access */
    spi_byte_access_enable(spi_periph);
    /* enable SPI NSS output */
    spi_nss_output_enable(spi_periph);
#elif defined (SOC_SERIES_GD32G5x3)
    /* enable SPI byte access */
    spi_fifo_access_size_config(spi_periph, SPI_BYTE_ACCESS);
    /* enable SPI NSS output */
    spi_nss_output_enable(spi_periph);
#endif

    /* init SPI */
    spi_init(spi_periph, &spi_init_struct);
    /* Enable SPI_MASTER */
    spi_enable(spi_periph);

    return RT_EOK;
}

static rt_ssize_t spixfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    struct rt_spi_bus * gd32_spi_bus = (struct rt_spi_bus *)device->bus;
    struct gd32_spi *spi_device = (struct gd32_spi *)gd32_spi_bus->parent.user_data;
    struct rt_spi_configuration * config = &device->config;
    uint32_t spi_periph = spi_device->spi_periph;

    rt_ssize_t ret = 0;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    /* take CS */
    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            rt_pin_write(device->cs_pin, PIN_HIGH);
        }
        else
        {
            rt_pin_write(device->cs_pin, PIN_LOW);
        }
    }

    LOG_D("%s transfer prepare and start", spi_device->bus_name);
    LOG_D("%s sendbuf: %X, recvbuf: %X, length: %d",
          spi_device->bus_name,
          (uint32_t)message->send_buf,
          (uint32_t)message->recv_buf, message->length);

#if defined(BSP_USING_SPI_DMA)
    /* Use DMA for large transfers if enabled */
    if ((spi_device->dma_tx != RT_NULL || spi_device->dma_rx != RT_NULL)
        && message->length >= BSP_SPI_DMA_TRANS_MIN_LEN && config->data_width <= 8)
    {
        const rt_uint8_t * send_ptr = message->send_buf;
        rt_uint8_t * recv_ptr = message->recv_buf;
        rt_uint32_t size = message->length;
        
        /* Prepare dummy buffer for TX or RX only transfers */
        static rt_uint8_t dummy_tx = 0xFF;
        static rt_uint8_t dummy_rx = 0;
        const rt_uint8_t *dma_send_ptr = send_ptr;
        rt_uint8_t *dma_recv_ptr = recv_ptr;

        LOG_D("spi DMA transfer start: %d", size);

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
        /* Cache-aligned DMA buffers (used when original buffers are not 32-byte aligned) */
        void *dma_tx_buf = RT_NULL;
        void *dma_rx_buf = RT_NULL;

        /* H7xx requires setting the data frame number before DMA transfer */
        spi_current_data_num_config(spi_periph, size);

        /* DCache coherency: ensure DMA buffers are 32-byte cache-line aligned.
         * Only needed for MCUs with DCache (H7xx series). */
        if (send_ptr != RT_NULL)
        {
            if (RT_IS_ALIGN((rt_uint32_t)send_ptr, 32) && RT_IS_ALIGN(size, 32))
            {
                dma_send_ptr = send_ptr;
            }
            else
            {
                dma_tx_buf = rt_malloc_align(RT_ALIGN(size, 32), 32);
                if (dma_tx_buf == RT_NULL)
                {
                    LOG_E("%s DMA tx alloc failed", spi_device->bus_name);
                    ret = -RT_ENOMEM;
                    goto _exit;
                }
                rt_memset(dma_tx_buf, 0, RT_ALIGN(size, 32));
                rt_memcpy(dma_tx_buf, send_ptr, size);
                dma_send_ptr = (const rt_uint8_t *)dma_tx_buf;
            }
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)dma_send_ptr, RT_ALIGN(size, 32));
        }
        
        if (recv_ptr != RT_NULL)
        {
            if (RT_IS_ALIGN((rt_uint32_t)recv_ptr, 32) && RT_IS_ALIGN(size, 32))
            {
                dma_recv_ptr = recv_ptr;
            }
            else
            {
                dma_rx_buf = rt_malloc_align(RT_ALIGN(size, 32), 32);
                if (dma_rx_buf == RT_NULL)
                {
                    LOG_E("%s DMA rx alloc failed", spi_device->bus_name);
                    if (dma_tx_buf != RT_NULL) rt_free_align(dma_tx_buf);
                    ret = -RT_ENOMEM;
                    goto _exit;
                }
                rt_memset(dma_rx_buf, 0, RT_ALIGN(size, 32));
                dma_recv_ptr = (rt_uint8_t *)dma_rx_buf;
            }
        }
#endif /* H7xx DCache */
        
        /* Configure RX DMA */
        if (spi_device->dma_rx != RT_NULL)
        {
            gd32_dma_channel_disable(spi_device->dma_rx->periph, spi_device->dma_rx->channel);
            
            if (recv_ptr != RT_NULL)
            {
                gd32_dma_memory_address_config(spi_device->dma_rx->periph, spi_device->dma_rx->channel, 
                                         DMA_MEMORY_0, (uint32_t)dma_recv_ptr);
                gd32_dma_memory_address_generation_config(spi_device->dma_rx->periph, spi_device->dma_rx->channel, DMA_MEMORY_INCREASE_ENABLE);
            }
            else
            {
                gd32_dma_memory_address_config(spi_device->dma_rx->periph, spi_device->dma_rx->channel, 
                                         DMA_MEMORY_0, (uint32_t)&dummy_rx);
                gd32_dma_memory_address_generation_config(spi_device->dma_rx->periph, spi_device->dma_rx->channel, DMA_MEMORY_INCREASE_DISABLE);
            }
            
            gd32_dma_transfer_number_config(spi_device->dma_rx->periph, spi_device->dma_rx->channel, size);
            gd32_dma_interrupt_enable(spi_device->dma_rx->periph, spi_device->dma_rx->channel, DMA_CHXCTL_FTFIE);
            gd32_dma_channel_enable(spi_device->dma_rx->periph, spi_device->dma_rx->channel);
            spi_dma_enable(spi_periph, SPI_DMA_RECEIVE);
        }
        
        /* Configure TX DMA */
        if (spi_device->dma_tx != RT_NULL)
        {
            gd32_dma_channel_disable(spi_device->dma_tx->periph, spi_device->dma_tx->channel);
            
            if (send_ptr != RT_NULL)
            {
                gd32_dma_memory_address_config(spi_device->dma_tx->periph, spi_device->dma_tx->channel, 
                                         DMA_MEMORY_0, (uint32_t)dma_send_ptr);
                gd32_dma_memory_address_generation_config(spi_device->dma_tx->periph, spi_device->dma_tx->channel, DMA_MEMORY_INCREASE_ENABLE);
            }
            else
            {
                gd32_dma_memory_address_config(spi_device->dma_tx->periph, spi_device->dma_tx->channel, 
                                         DMA_MEMORY_0, (uint32_t)&dummy_tx);
                gd32_dma_memory_address_generation_config(spi_device->dma_tx->periph, spi_device->dma_tx->channel, DMA_MEMORY_INCREASE_DISABLE);
            }
            
            gd32_dma_transfer_number_config(spi_device->dma_tx->periph, spi_device->dma_tx->channel, size);
            gd32_dma_interrupt_enable(spi_device->dma_tx->periph, spi_device->dma_tx->channel, DMA_CHXCTL_FTFIE);
            gd32_dma_channel_enable(spi_device->dma_tx->periph, spi_device->dma_tx->channel);
            spi_dma_enable(spi_periph, SPI_DMA_TRANSMIT);
        }

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
        /* H7xx requires explicit master transfer start */
        spi_master_transfer_start(spi_periph, SPI_TRANS_START);
#endif
        
        /* Wait for transfer complete with timeout */
        rt_tick_t timeout = rt_tick_from_millisecond(BSP_SPI_XFER_TIMEOUT);
        rt_tick_t start = rt_tick_get();
        
        while (1)
        {
            rt_bool_t tx_done = RT_TRUE;
            rt_bool_t rx_done = RT_TRUE;
            
            if (spi_device->dma_tx != RT_NULL)
            {
                tx_done = (gd32_dma_flag_get(spi_device->dma_tx->periph, spi_device->dma_tx->channel, DMA_FLAG_FTF) == SET);
            }
            
            if (spi_device->dma_rx != RT_NULL)
            {
                rx_done = (gd32_dma_flag_get(spi_device->dma_rx->periph, spi_device->dma_rx->channel, DMA_FLAG_FTF) == SET);
            }
            
            if (tx_done && rx_done)
            {
                break;
            }
            
            if (rt_tick_get() - start > timeout)
            {
				LOG_E("%s DMA transfer timeout", spi_device->bus_name);
                gd32_spi_dma_cleanup(spi_device, spi_periph);
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
                if (dma_tx_buf != RT_NULL) rt_free_align(dma_tx_buf);
                if (dma_rx_buf != RT_NULL) rt_free_align(dma_rx_buf);
#endif
                ret = -RT_EIO;
                goto _exit;
            }
            
            rt_thread_mdelay(1);
        }

        /* Disable DMA and clear flags */
        gd32_spi_dma_cleanup(spi_device, spi_periph);

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
        /* DCache coherency: invalidate RX buffer and copy back if re-aligned.
         * Must invalidate full cache lines (32 bytes) to avoid corrupting
         * adjacent heap metadata when size is not cache-line aligned. */
        if (recv_ptr != RT_NULL)
        {
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)dma_recv_ptr, RT_ALIGN(size, 32));
            if (dma_rx_buf != RT_NULL)
            {
                rt_memcpy(recv_ptr, dma_recv_ptr, size);
            }
        }
        
        /* Free aligned temporary buffers */
        if (dma_tx_buf != RT_NULL)
        {
            rt_free_align(dma_tx_buf);
        }
        if (dma_rx_buf != RT_NULL)
        {
            rt_free_align(dma_rx_buf);
        }
#endif /* H7xx DCache */
        
        LOG_D("spi DMA transfer finish");
    }
    else
#endif /* BSP_USING_SPI_DMA */
    {
        if(config->data_width <= 8)
        {
            const rt_uint8_t * send_ptr = message->send_buf;
            rt_uint8_t * recv_ptr = message->recv_buf;
            rt_uint32_t size = message->length;

            LOG_D("spi poll transfer start: %d\n", size);

            while(size--)
            {
                rt_uint8_t data = 0xFF;

                if(send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                /* Todo: replace register read/write by gd32f4 lib */
                /* Wait until the transmit buffer is empty */
                #if defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32H75E) || defined (SOC_SERIES_GD32H77x)
                spi_master_transfer_start(spi_periph, SPI_TRANS_START);
                if (gd32_spi_wait_flag(spi_periph, SPI_FLAG_TP) != RT_EOK)
                {
                    ret = -RT_ETIMEOUT;
                    goto _exit;
                }
                #else
                if (gd32_spi_wait_flag(spi_periph, SPI_FLAG_TBE) != RT_EOK)
                {
                    ret = -RT_ETIMEOUT;
                    goto _exit;
                }
                #endif
                /* Send the byte */
                spi_i2s_data_transmit(spi_periph, data);

                /* Wait until a data is received */
                #if defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32H75E) || defined (SOC_SERIES_GD32H77x)
                if (gd32_spi_wait_flag(spi_periph, SPI_FLAG_RP) != RT_EOK)
                {
                    ret = -RT_ETIMEOUT;
                    goto _exit;
                }
                #else
                if (gd32_spi_wait_flag(spi_periph, SPI_FLAG_RBNE) != RT_EOK)
                {
                    ret = -RT_ETIMEOUT;
                    goto _exit;
                }
                #endif
                /* Get the received data */
                data = spi_i2s_data_receive(spi_periph);

                if(recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
            LOG_D("spi poll transfer finsh\n");
        }
        else if(config->data_width <= 16)
        {
            const rt_uint16_t * send_ptr = message->send_buf;
            rt_uint16_t * recv_ptr = message->recv_buf;
            rt_uint32_t size = message->length;

            while(size--)
            {
                rt_uint16_t data = 0xFF;

                if(send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                /* Wait until the transmit buffer is empty */
                #if defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32H75E) || defined (SOC_SERIES_GD32H77x)
                spi_master_transfer_start(spi_periph, SPI_TRANS_START);
                if (gd32_spi_wait_flag(spi_periph, SPI_FLAG_TP) != RT_EOK)
                {
                    ret = -RT_ETIMEOUT;
                    goto _exit;
                }
                #else
                if (gd32_spi_wait_flag(spi_periph, SPI_FLAG_TBE) != RT_EOK)
                {
                    ret = -RT_ETIMEOUT;
                    goto _exit;
                }
                #endif
                /* Send the byte */
                spi_i2s_data_transmit(spi_periph, data);

                /* Wait until a data is received */
                #if defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32H75E) || defined (SOC_SERIES_GD32H77x)
                if (gd32_spi_wait_flag(spi_periph, SPI_FLAG_RP) != RT_EOK)
                {
                    ret = -RT_ETIMEOUT;
                    goto _exit;
                }
                #else
                if (gd32_spi_wait_flag(spi_periph, SPI_FLAG_RBNE) != RT_EOK)
                {
                    ret = -RT_ETIMEOUT;
                    goto _exit;
                }
                #endif
                /* Get the received data */
                data = spi_i2s_data_receive(spi_periph);

                if(recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
        }
        #if defined SOC_SERIES_GD32H7xx || defined (SOC_SERIES_GD32H75E) || defined (SOC_SERIES_GD32H77x)
        else if(config->data_width <= 32)
        {
            const rt_uint32_t * send_ptr = message->send_buf;
            rt_uint32_t * recv_ptr = message->recv_buf;
            rt_uint32_t size = message->length;
            /* SPI master start transfer */
            spi_master_transfer_start(spi_periph, SPI_TRANS_START);
            while(size--)
            {
                rt_uint32_t data = 0xFF;

                if(send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                /* Wait until the transmit buffer is empty */
                if (gd32_spi_wait_flag(spi_periph, SPI_FLAG_TP) != RT_EOK)
                {
                    ret = -RT_ETIMEOUT;
                    goto _exit;
                }
                /* Send the byte */
                spi_i2s_data_transmit(spi_periph, data);

                /* Wait until a data is received */
                if (gd32_spi_wait_flag(spi_periph, SPI_FLAG_RP) != RT_EOK)
                {
                    ret = -RT_ETIMEOUT;
                    goto _exit;
                }
                /* Get the received data */
                data = spi_i2s_data_receive(spi_periph);

                if(recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
        }
        #endif
        else
        {
            ret = -RT_EIO;
            goto _exit;
        }
    }

    ret = message->length;

_exit:
    /* release CS */
    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            rt_pin_write(device->cs_pin, PIN_LOW);
        else
            rt_pin_write(device->cs_pin, PIN_HIGH);
    }

    return ret;
};

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    if(cs_pin != PIN_NONE)
    {
        /* initialize the cs pin && select the slave*/
        rt_pin_mode(cs_pin, PIN_MODE_OUTPUT);
        rt_pin_write(cs_pin, PIN_HIGH);
    }

    result = rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, cs_pin, RT_NULL);

    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}

int rt_hw_spi_init(void)
{
    int result = 0;
    int i;

    for (i = 0; i < sizeof(spi_bus_obj) / sizeof(spi_bus_obj[0]); i++)
    {
        spi_bus_obj[i].spi_bus->parent.user_data = (void *)&spi_bus_obj[i];

        result = rt_spi_bus_register(spi_bus_obj[i].spi_bus, spi_bus_obj[i].bus_name, &gd32_spi_ops);

        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_bus_obj[i].bus_name);
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* BSP_USING_SPI0 || BSP_USING_SPI1 || BSP_USING_SPI2 || BSP_USING_SPI3 || BSP_USING_SPI4 || BSP_USING_SPI5 */
#endif /* RT_USING_SPI */

