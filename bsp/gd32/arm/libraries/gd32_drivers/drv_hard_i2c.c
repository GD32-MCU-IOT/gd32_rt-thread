/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-12-20     BruceOu           the first version
 */

#include "drv_hard_i2c.h"

#ifdef RT_USING_I2C

#define LOG_TAG              "drv.i2c"
#include <rtdbg.h>
#if defined(SOC_SERIES_GD32F5xx)
#include "config/f5xx/i2c_config.h"
#endif

#if !defined(BSP_USING_HARD_I2C0) && !defined(BSP_USING_HARD_I2C1) && !defined(BSP_USING_HARD_I2C2) && !defined(BSP_USING_HARD_I2C3)  && !defined(BSP_USING_HARD_I2C4)  && !defined(BSP_USING_HARD_I2C5)
#error "Please define at least one BSP_USING_I2Cx"
/* this driver can be disabled at menuconfig → RT-Thread Components → Device Drivers */
#endif

#if defined(BSP_USING_HARD_I2C0)
struct rt_i2c_bus_device i2c0;
#endif /* BSP_USING_I2C0 */

#if defined(BSP_USING_HARD_I2C1)
struct rt_i2c_bus_device i2c1;
#endif /* BSP_USING_I2C1 */

#if defined(BSP_USING_HARD_I2C2)
struct rt_i2c_bus_device i2c2;
#endif /* BSP_USING_I2C2 */

#if defined(BSP_USING_HARD_I2C3)
struct rt_i2c_bus_device i2c3;
#endif /* BSP_USING_I2C3 */

#if defined(BSP_USING_HARD_I2C4)
struct rt_i2c_bus_device i2c4;
#endif /* BSP_USING_I2C4 */

#if defined(BSP_USING_HARD_I2C5)
struct rt_i2c_bus_device i2c5;
#endif /* BSP_USING_I2C5 */

#if defined(SOC_SERIES_GD32F5xx) && \
    (defined(BSP_USING_HARD_I2C0) || defined(BSP_USING_HARD_I2C1) || defined(BSP_USING_HARD_I2C2))
#define GD32F5XX_USING_LEGACY_I2C
#endif

#if defined(SOC_SERIES_GD32F5xx) && \
    (defined(BSP_USING_HARD_I2C3) || defined(BSP_USING_HARD_I2C4) || defined(BSP_USING_HARD_I2C5))
#define GD32F5XX_USING_NEW_I2C
#endif

#if defined(GD32F5XX_USING_NEW_I2C)
#define i2c_flag_get_gd                      i2c_add_flag_get
#define i2c_timing_config_gd                 i2c_add_timing_config
#define i2c_master_clock_config_gd           i2c_add_master_clock_config
#define i2c_enable_gd                        i2c_add_enable 
#define i2c_flag_clear_gd                    i2c_add_flag_clear
#define i2c_stop_on_bus_gd                   i2c_add_stop_on_bus
#define i2c_transfer_byte_number_config_gd   i2c_add_transfer_byte_number_config
#define i2c_start_on_bus_gd                  i2c_add_start_on_bus
#define i2c_address10_enable_gd              i2c_add_address10_enable
#define i2c_address10_disable_gd             i2c_add_address10_disable
#define i2c_master_addressing_gd             i2c_add_master_addressing
#define i2c_data_transmit_gd                 i2c_add_data_transmit
#define i2c_data_receive_gd                  i2c_add_data_receive

#define I2C_FLAG_RBNE_GD                     I2C_ADD_FLAG_RBNE
#define I2C_STAT_GD                          I2C_ADD_STAT
#define I2C_STAT_TBE_GD                      I2C_ADD_STAT_TBE
#define I2C_STAT_TI_GD                       I2C_ADD_STAT_TI
#define I2C_MASTER_RECEIVE_GD                I2C_ADD_MASTER_RECEIVE
#define I2C_MASTER_TRANSMIT_GD               I2C_ADD_MASTER_TRANSMIT
#define I2C_FLAG_I2CBSY_GD                   I2C_ADD_FLAG_I2CBSY
#define I2C_FLAG_TC_GD                       I2C_ADD_FLAG_TC
#define I2C_FLAG_TI_GD                       I2C_ADD_FLAG_TI
#define I2C_FLAG_STPDET_GD                   I2C_ADD_FLAG_STPDET
#define I2C_FLAG_TBE_GD                      I2C_ADD_FLAG_TBE
#define I2C_CTL0_GD(periph)                  I2C_ADD_CTL0(periph)
#define I2C_TDATA_GD(periph)                 I2C_ADD_TDATA(periph)
#define I2C_RDATA_GD(periph)                 I2C_ADD_RDATA(periph)
#define I2C_CTL0_DENR_GD                     I2C_ADD_CTL0_DENR
#define I2C_CTL0_DENT_GD                     I2C_ADD_CTL0_DENT

#elif defined(GD32F5XX_USING_LEGACY_I2C)
#define i2c_flag_get_gd                      i2c_flag_get
#define i2c_flag_clear_gd                    i2c_flag_clear
#define i2c_data_receive_gd                  i2c_data_receive
#define i2c_data_transmit_gd                 i2c_data_transmit

#define I2C_FLAG_RBNE_GD                     I2C_FLAG_RBNE
#define I2C_STAT_GD(periph)                  I2C_STAT0(periph)
#define I2C_STAT_TBE_GD                      I2C_STAT0_TBE
#define I2C_STAT_TI_GD                       I2C_STAT0_BTC
#define I2C_FLAG_I2CBSY_GD                   I2C_FLAG_I2CBSY
#define I2C_FLAG_TC_GD                       I2C_FLAG_BTC
#define I2C_FLAG_TI_GD                       I2C_FLAG_BTC
#define I2C_FLAG_STPDET_GD                   I2C_FLAG_STPDET
#define I2C_FLAG_TBE_GD                      I2C_FLAG_TBE
#define I2C_CTL0_GD(periph)                  I2C_CTL1(periph)
#define I2C_TDATA_GD(periph)                 I2C_DATA(periph)
#define I2C_RDATA_GD(periph)                 I2C_DATA(periph)
#define I2C_CTL0_DENR_GD                     I2C_CTL1_DMAON
#define I2C_CTL0_DENT_GD                     I2C_CTL1_DMAON

#elif defined(SOC_SERIES_GD32E51x)
#define i2c_flag_get_gd                      i2c2_flag_get
#define i2c_timing_config_gd                 i2c_timing_config
#define i2c_master_clock_config_gd           i2c_master_clock_config
#define i2c_enable_gd                        i2c_enable
#define i2c_flag_clear_gd                    i2c2_flag_clear
#define i2c_data_receive_gd                  i2c_data_receive
#define i2c_data_transmit_gd                 i2c_data_transmit
#define i2c_address10_enable_gd              i2c_address10_enable
#define i2c_address10_disable_gd             i2c_address10_disable
#define i2c_master_addressing_gd             i2c2_master_addressing
#define i2c_transfer_byte_number_config_gd   i2c_transfer_byte_number_config
#define i2c_start_on_bus_gd                  i2c_start_on_bus
#define i2c_stop_on_bus_gd                   i2c_stop_on_bus

#define I2C_STAT_GD                          I2C2_STAT
#define I2C_STAT_TBE_GD                      I2C2_STAT_TBE
#define I2C_STAT_TI_GD                       I2C2_STAT_TI
#define I2C_MASTER_RECEIVE_GD                I2C2_MASTER_RECEIVE
#define I2C_MASTER_TRANSMIT_GD               I2C2_MASTER_TRANSMIT
#define I2C_FLAG_RBNE_GD                     I2C2_FLAG_RBNE
#define I2C_FLAG_I2CBSY_GD                   I2C2_FLAG_I2CBSY
#define I2C_FLAG_TC_GD                       I2C2_FLAG_TC
#define I2C_FLAG_TI_GD                       I2C2_FLAG_TI
#define I2C_FLAG_STPDET_GD                   I2C2_FLAG_STPDET
#define I2C_FLAG_TBE_GD                      I2C2_FLAG_TBE

#elif defined(SOC_SERIES_GD32M53x)
/* M53x functions don't have i2c_periph parameter (only one I2C) */
#define i2c_flag_get_gd(periph, flag)                i2c_flag_get(flag)
#define i2c_timing_config_gd(periph, psc, scl, sda)  i2c_timing_config(psc, scl, sda)
#define i2c_master_clock_config_gd(periph, h, l)     i2c_master_clock_config(h, l)
#define i2c_enable_gd(periph)                        i2c_enable()
#define i2c_flag_clear_gd(periph, flag)              i2c_flag_clear(flag)
#define i2c_data_receive_gd(periph)                  i2c_data_receive()
#define i2c_address10_enable_gd(periph)              i2c_address10_enable()
#define i2c_address10_disable_gd(periph)             i2c_address10_disable()
#define i2c_master_addressing_gd(periph, addr, dir)  i2c_master_addressing(addr, dir)
#define i2c_transfer_byte_number_config_gd(periph, n) i2c_transfer_byte_number_config(n)
#define i2c_start_on_bus_gd(periph)                  i2c_start_on_bus()
#define i2c_stop_on_bus_gd(periph)                   i2c_stop_on_bus()
/* make baseline write path compile */
#define i2c_data_transmit(periph, data)              i2c_data_transmit(data)

#define I2C_FLAG_RBNE_GD                     I2C_FLAG_RBNE
#define I2C_STAT_GD(periph)                  I2C_STAT
#define I2C_STAT_TBE_GD                      I2C_STAT_TBE
#define I2C_STAT_TI_GD                       I2C_STAT_TI
#define I2C_MASTER_RECEIVE_GD                I2C_MASTER_RECEIVE
#define I2C_MASTER_TRANSMIT_GD               I2C_MASTER_TRANSMIT
#define I2C_FLAG_I2CBSY_GD                   I2C_FLAG_I2CBSY
#define I2C_FLAG_TC_GD                       I2C_FLAG_TC
#define I2C_FLAG_TI_GD                       I2C_FLAG_TI
#define I2C_FLAG_STPDET_GD                   I2C_FLAG_STPDET
#define I2C_FLAG_TBE_GD                      I2C_FLAG_TBE

#else
#define i2c_flag_get_gd                      i2c_flag_get
#define i2c_timing_config_gd                 i2c_timing_config
#define i2c_master_clock_config_gd           i2c_master_clock_config
#define i2c_enable_gd                        i2c_enable
#define i2c_flag_clear_gd                    i2c_flag_clear
#define i2c_data_receive_gd                  i2c_data_receive
#define i2c_data_transmit_gd                 i2c_data_transmit
#define i2c_address10_enable_gd              i2c_address10_enable
#define i2c_address10_disable_gd             i2c_address10_disable
#define i2c_master_addressing_gd             i2c_master_addressing
#define i2c_transfer_byte_number_config_gd   i2c_transfer_byte_number_config
#define i2c_start_on_bus_gd                  i2c_start_on_bus
#define i2c_stop_on_bus_gd                   i2c_stop_on_bus

#define I2C_FLAG_RBNE_GD                     I2C_FLAG_RBNE
#define I2C_STAT_GD                          I2C_STAT
#define I2C_STAT_TBE_GD                      I2C_STAT_TBE
#define I2C_STAT_TI_GD                       I2C_STAT_TI
#define I2C_MASTER_RECEIVE_GD                I2C_MASTER_RECEIVE
#define I2C_MASTER_TRANSMIT_GD               I2C_MASTER_TRANSMIT
#define I2C_FLAG_I2CBSY_GD                   I2C_FLAG_I2CBSY
#define I2C_FLAG_TC_GD                       I2C_FLAG_TC
#define I2C_FLAG_TI_GD                       I2C_FLAG_TI
#define I2C_FLAG_STPDET_GD                   I2C_FLAG_STPDET
#define I2C_FLAG_TBE_GD                      I2C_FLAG_TBE

#endif

#if defined (SOC_SERIES_GD32F5xx)
#define IS_I2C_LEGACY(periph)  ((periph) == I2C0 || (periph) == I2C1 || (periph) == I2C2)
#elif defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32F3x0) || defined (SOC_SERIES_GD32F30x) \
   || defined (SOC_SERIES_GD32C11x) || defined (SOC_SERIES_GD32E23x) || defined (SOC_SERIES_GD32E11x)
#define IS_I2C_LEGACY(periph)  (1)
#elif defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32H75E) || defined (SOC_SERIES_GD32L23x) \
   || defined (SOC_SERIES_GD32F50x) || defined (SOC_SERIES_GD32G5x3) || defined (SOC_SERIES_GD32H77x) \
   || defined (SOC_SERIES_GD32M53x)
#define IS_I2C_LEGACY(periph)  (0)
#elif defined SOC_SERIES_GD32E51x 
#define IS_I2C_LEGACY(periph)  ((periph) == I2C0 || (periph) == I2C1)
#endif

#if defined(SOC_SERIES_GD32F5xx)
/* Static DMA configuration for each I2C */
#ifdef BSP_I2C0_RX_USING_DMA
static struct dma_config i2c0_dma_rx_cfg = I2C0_RX_DMA_CONFIG;
#endif
#ifdef BSP_I2C0_TX_USING_DMA
static struct dma_config i2c0_dma_tx_cfg = I2C0_TX_DMA_CONFIG;
#endif
#ifdef BSP_I2C1_RX_USING_DMA
static struct dma_config i2c1_dma_rx_cfg = I2C1_RX_DMA_CONFIG;
#endif
#ifdef BSP_I2C1_TX_USING_DMA
static struct dma_config i2c1_dma_tx_cfg = I2C1_TX_DMA_CONFIG;
#endif
#ifdef BSP_I2C2_RX_USING_DMA
static struct dma_config i2c2_dma_rx_cfg = I2C2_RX_DMA_CONFIG;
#endif
#ifdef BSP_I2C2_TX_USING_DMA
static struct dma_config i2c2_dma_tx_cfg = I2C2_TX_DMA_CONFIG;
#endif
#ifdef BSP_I2C3_RX_USING_DMA
static struct dma_config i2c3_dma_rx_cfg = I2C3_RX_DMA_CONFIG;
#endif
#ifdef BSP_I2C3_TX_USING_DMA
static struct dma_config i2c3_dma_tx_cfg = I2C3_TX_DMA_CONFIG;
#endif
#ifdef BSP_I2C4_RX_USING_DMA
static struct dma_config i2c4_dma_rx_cfg = I2C4_RX_DMA_CONFIG;
#endif
#ifdef BSP_I2C4_TX_USING_DMA
static struct dma_config i2c4_dma_tx_cfg = I2C4_TX_DMA_CONFIG;
#endif
#ifdef BSP_I2C5_RX_USING_DMA
static struct dma_config i2c5_dma_rx_cfg = I2C5_RX_DMA_CONFIG;
#endif
#ifdef BSP_I2C5_TX_USING_DMA
static struct dma_config i2c5_dma_tx_cfg = I2C5_TX_DMA_CONFIG;
#endif

/* DMA initialized flag */
static rt_bool_t i2c_dma_initialized = RT_FALSE;

#if defined(SOC_SERIES_GD32F5xx) && (defined(BSP_USING_I2C_TX_DMA) || defined(BSP_USING_I2C_RX_DMA))
static const struct gd32_i2c_bus gd_i2c_config[];
static rt_size_t gd32_i2c_get_bus_count(void);
#endif

/* GD32F5xx legacy I2C TX DMA needs a staged start; new I2C supports direct DMA. */

/**
  * @brief  Initialize DMA clock for I2C (call once)
  * @retval None
  */
static void gd32_i2c_dma_clock_init(void)
{
    if (i2c_dma_initialized) return;

#if defined(BSP_I2C0_RX_USING_DMA) || defined(BSP_I2C0_TX_USING_DMA) || \
    defined(BSP_I2C1_RX_USING_DMA) || defined(BSP_I2C1_TX_USING_DMA) || \
    defined(BSP_I2C2_RX_USING_DMA) || defined(BSP_I2C2_TX_USING_DMA) || \
    defined(BSP_I2C3_TX_USING_DMA) || defined(BSP_I2C3_RX_USING_DMA) || \
    defined(BSP_I2C4_RX_USING_DMA) || defined(BSP_I2C4_TX_USING_DMA) || \
    defined(BSP_I2C5_RX_USING_DMA) || defined(BSP_I2C5_TX_USING_DMA)
    rcu_periph_clock_enable(RCU_DMA0);
#endif

    i2c_dma_initialized = RT_TRUE;
}

#if defined(BSP_USING_I2C_RX_DMA) || defined(BSP_USING_I2C_TX_DMA)
static int gd32_i2c_dma_wait_complete(const struct dma_config *dma)
{
    rt_tick_t timeout = rt_tick_from_millisecond(I2C_DMA_TIMEOUT_MS);
    rt_tick_t start = rt_tick_get();
    int result = 0;

    while (dma_flag_get(dma->periph, dma->channel, DMA_FLAG_FTF) != SET)
    {
        if (rt_tick_get() - start > timeout)
        {
            result = -RT_ETIMEOUT;
#if defined(SOC_SERIES_GD32F5xx)
            rt_kprintf("[i2c-dma] wait ftf timeout: dma=%p periph=0x%08x ch=%d\n", dma, dma->periph, dma->channel);
#endif
            break;
        }
        rt_thread_mdelay(1);
    }

#if defined(SOC_SERIES_GD32F5xx)
    if (result == 0)
    {
        rt_kprintf("[i2c-dma] wait ftf done: dma=%p periph=0x%08x ch=%d\n", dma, dma->periph, dma->channel);
    }
#endif

    dma_channel_disable(dma->periph, dma->channel);
    dma_flag_clear(dma->periph, dma->channel, DMA_FLAG_FTF);

    return result;
}
#endif

#ifdef BSP_USING_I2C_RX_DMA
/**
  * @brief  Configure and enable DMA for I2C RX
  * @param  i2c_bus: I2C bus structure
  * @param  p_buffer: data buffer
  * @param  data_byte: number of bytes
  * @retval RT_TRUE if DMA configured, RT_FALSE otherwise
  */
static rt_bool_t gd32_i2c_dma_rx_start(const struct gd32_i2c_bus *i2c_bus, uint8_t *p_buffer, uint16_t data_byte)
{
    uint32_t i2c_periph = i2c_bus->i2c_periph;
    struct dma_config *dma_rx = i2c_bus->dma_rx;
    dma_single_data_parameter_struct dma_init_struct;

    if (data_byte < I2C_DMA_TRANS_MIN_LEN || dma_rx == RT_NULL)
    {
        return RT_FALSE;
    }

    gd32_i2c_dma_clock_init();

    dma_deinit(dma_rx->periph, dma_rx->channel);

    dma_init_struct.periph_addr = IS_I2C_LEGACY(i2c_periph) ?
                                  (uint32_t)&I2C_DATA(i2c_periph) :
                                  (uint32_t)&I2C_RDATA_GD(i2c_periph);

    dma_init_struct.memory0_addr = (uint32_t)p_buffer;
    dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
    dma_init_struct.number = data_byte;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_HIGH;
    dma_single_data_mode_init(dma_rx->periph, dma_rx->channel, &dma_init_struct);
    dma_channel_subperipheral_select(dma_rx->periph, dma_rx->channel, dma_rx->subperiph);
    dma_circulation_disable(dma_rx->periph, dma_rx->channel);

    dma_channel_enable(dma_rx->periph, dma_rx->channel);

    if (IS_I2C_LEGACY(i2c_periph))
    {
        i2c_dma_last_transfer_config(i2c_periph, I2C_DMALST_ON);
        i2c_dma_config(i2c_periph, I2C_DMA_ON);
    }
    else
    {
        I2C_CTL0_GD(i2c_periph) |= I2C_CTL0_DENR_GD;
    }

#if defined(SOC_SERIES_GD32F5xx)
    rt_kprintf("[i2c-dma] rx start: i2c=0x%08x len=%d buf=%p denr=0x%08x\n", i2c_periph, data_byte, p_buffer, I2C_CTL0_GD(i2c_periph));
#endif

    return RT_TRUE;
}

/**
  * @brief  Wait for DMA RX completion and cleanup
  * @param  i2c_bus: I2C bus structure
  * @retval 0 on success
  */
static int gd32_i2c_dma_rx_wait(const struct gd32_i2c_bus *i2c_bus)
{
    uint32_t i2c_periph = i2c_bus->i2c_periph;
    struct dma_config *dma_rx = i2c_bus->dma_rx;
    int result = gd32_i2c_dma_wait_complete(dma_rx);

#if defined(SOC_SERIES_GD32F5xx)
    rt_kprintf("[i2c-dma] rx wait enter: i2c=0x%08x result=%d stat=0x%08x ctl0=0x%08x\n",
               i2c_periph, result, I2C_STAT_GD(i2c_periph), I2C_CTL0_GD(i2c_periph));
#endif

    if (IS_I2C_LEGACY(i2c_periph))
    {
        i2c_stop_on_bus(i2c_periph);
        i2c_dma_last_transfer_config(i2c_periph, I2C_DMALST_OFF);
        i2c_dma_config(i2c_periph, I2C_DMA_OFF);
    }
    else
    {
#if defined(SOC_SERIES_GD32F5xx)
        if (result == 0)
        {
            rt_tick_t timeout = rt_tick_from_millisecond(I2C_DMA_TIMEOUT_MS);
            rt_tick_t start = rt_tick_get();

            while(!i2c_flag_get_gd(i2c_periph, I2C_FLAG_TC_GD))
            {
                if (rt_tick_get() - start > timeout)
                {
                    result = -RT_ETIMEOUT;
#if defined(SOC_SERIES_GD32F5xx)
                    rt_kprintf("[i2c-dma] rx wait tc timeout: i2c=0x%08x stat=0x%08x ctl0=0x%08x\n",
                               i2c_periph, I2C_STAT_GD(i2c_periph), I2C_CTL0_GD(i2c_periph));
#endif
                    break;
                }
                rt_thread_mdelay(1);
            }

#if defined(SOC_SERIES_GD32F5xx)
            if (result == 0)
            {
                rt_kprintf("[i2c-dma] rx wait tc done: i2c=0x%08x stat=0x%08x ctl0=0x%08x\n",
                           i2c_periph, I2C_STAT_GD(i2c_periph), I2C_CTL0_GD(i2c_periph));
            }
#endif
        }
#endif
        I2C_CTL0_GD(i2c_periph) &= ~I2C_CTL0_DENR_GD;
    }

    return result;
}
#endif /* BSP_USING_I2C_RX_DMA */

#ifdef BSP_USING_I2C_TX_DMA
/**
  * @brief  Configure and start DMA for I2C TX
  * @note   Legacy I2C TX DMA has timing issues but enabled for testing.
  * @param  i2c_bus: I2C bus structure
  * @param  p_buffer: data buffer
  * @param  data_byte: number of bytes
  * @retval RT_TRUE if DMA configured, RT_FALSE otherwise
  */
static rt_bool_t gd32_i2c_dma_tx_start(const struct gd32_i2c_bus *i2c_bus, uint8_t *p_buffer, uint16_t data_byte)
{
    uint32_t i2c_periph = i2c_bus->i2c_periph;
    struct dma_config *dma_tx = i2c_bus->dma_tx;
    dma_single_data_parameter_struct dma_init_struct;

    if (data_byte < I2C_DMA_TRANS_MIN_LEN || dma_tx == RT_NULL)
    {
        return RT_FALSE;
    }

    gd32_i2c_dma_clock_init();

    dma_deinit(dma_tx->periph, dma_tx->channel);

    dma_init_struct.periph_addr = IS_I2C_LEGACY(i2c_periph) ?
                                  (uint32_t)&I2C_DATA(i2c_periph) :
                                  (uint32_t)&I2C_TDATA_GD(i2c_periph);

    dma_init_struct.memory0_addr = (uint32_t)p_buffer;
    dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
    dma_init_struct.number = data_byte;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_HIGH;
    dma_single_data_mode_init(dma_tx->periph, dma_tx->channel, &dma_init_struct);
    dma_channel_subperipheral_select(dma_tx->periph, dma_tx->channel, dma_tx->subperiph);
    dma_circulation_disable(dma_tx->periph, dma_tx->channel);

    dma_channel_enable(dma_tx->periph, dma_tx->channel);

    if (IS_I2C_LEGACY(i2c_periph))
    {
        i2c_dma_config(i2c_periph, I2C_DMA_ON);
    }
    else
    {
        I2C_CTL0_GD(i2c_periph) |= I2C_CTL0_DENT_GD;
    }

    return RT_TRUE;
}

/**
  * @brief  Wait for I2C TX DMA completion and cleanup
  * @param  i2c_bus: I2C bus structure
  * @retval 0 on success
  */
static int gd32_i2c_dma_tx_wait(const struct gd32_i2c_bus *i2c_bus)
{
    uint32_t i2c_periph = i2c_bus->i2c_periph;
    struct dma_config *dma_tx = i2c_bus->dma_tx;
    int result = gd32_i2c_dma_wait_complete(dma_tx);

    if (IS_I2C_LEGACY(i2c_periph))
    {
        i2c_dma_config(i2c_periph, I2C_DMA_OFF);
    }
    else
    {
        I2C_CTL0_GD(i2c_periph) &= ~I2C_CTL0_DENT_GD;
    }

    return result;
}
#endif /* BSP_USING_I2C_TX_DMA */

#if defined(SOC_SERIES_GD32F5xx) && (defined(BSP_USING_I2C_TX_DMA) || defined(BSP_USING_I2C_RX_DMA))
static const struct gd32_i2c_bus *gd32_i2c_find_bus(rt_uint32_t i2c_periph)
{
    rt_size_t i;
    rt_size_t obj_num = gd32_i2c_get_bus_count();

    for (i = 0; i < obj_num; i++)
    {
        if (gd_i2c_config[i].i2c_periph == i2c_periph)
        {
            return &gd_i2c_config[i];
        }
    }

    return RT_NULL;
}
#endif

#ifdef BSP_USING_I2C_TX_DMA
static uint8_t *gd32_i2c_build_write_chain_buffer(struct rt_i2c_msg msgs[],
                                                  rt_uint32_t start,
                                                  rt_uint32_t end,
                                                  rt_uint16_t *total_len)
{
    rt_size_t merged_len = 0;
    rt_uint32_t index;
    uint8_t *merged_buf;
    uint8_t *cursor;

    for (index = start; index <= end; index++)
    {
        merged_len += msgs[index].len;
    }

    if (merged_len == 0 || merged_len > 0xFFFF)
    {
        return RT_NULL;
    }

    merged_buf = (uint8_t *)rt_malloc(merged_len);
    if (merged_buf == RT_NULL)
    {
        return RT_NULL;
    }

    cursor = merged_buf;
    for (index = start; index <= end; index++)
    {
        rt_memcpy(cursor, msgs[index].buf, msgs[index].len);
        cursor += msgs[index].len;
    }

    *total_len = (rt_uint16_t)merged_len;
    return merged_buf;
}
#endif
#endif /* SOC_SERIES_GD32F5xx */

#if !defined(SOC_SERIES_GD32H75E) && !defined(SOC_SERIES_GD32E51x) && !defined(SOC_SERIES_GD32F3x0) \
 && !defined(SOC_SERIES_GD32F50x) && !defined(SOC_SERIES_GD32G5x3) && !defined(SOC_SERIES_GD32C11x) \
 && !defined(SOC_SERIES_GD32L23x) && !defined(SOC_SERIES_GD32E23x) && !defined(SOC_SERIES_GD32E11x) \
 && !defined(SOC_SERIES_GD32H77x) && !defined(SOC_SERIES_GD32M53x) && !defined(SOC_SERIES_GD32H7xx) \
 && !defined(SOC_SERIES_GD32F5xx)
static const struct gd32_i2c_bus gd_i2c_config[] = {
#ifdef BSP_USING_HARD_I2C0
    {
    I2C0,    /* uart peripheral index */

    RCU_I2C0, RCU_GPIOB, RCU_GPIOB,    /* periph clock, scl gpio clock, sda gpio clock */
#if defined (SOC_SERIES_GD32F30x)
        GPIOB, GPIO_MODE_AF_OD, GPIO_PIN_6,            /* scl port, scl alternate, scl pin */
        GPIOB, GPIO_MODE_AF_OD, GPIO_PIN_7,           /* sda port, sda alternate, sda pin */
#else
        GPIOB, GPIO_AF_4, GPIO_PIN_6,             /* scl port, scl alternate, scl pin */
        GPIOB, GPIO_AF_4, GPIO_PIN_7,            /* sda port, sda alternate, sda pin */
#endif
        &i2c0,
        "hwi2c0",
    },
#endif

#ifdef BSP_USING_HARD_I2C1
    {
    I2C1,    /* uart peripheral index */
#if defined (SOC_SERIES_GD32F30x)
        RCU_I2C1, RCU_GPIOB, RCU_GPIOB,       /* periph clock, scl gpio clock, sda gpio clock */

        GPIOB, GPIO_MODE_AF_OD, GPIO_PIN_10,           /* scl port, scl alternate, scl pin */
        GPIOB, GPIO_MODE_AF_OD, GPIO_PIN_11,          /* sda port, sda alternate, sda pin */
#else
        RCU_I2C1, RCU_GPIOH, RCU_GPIOB,       /* periph clock, scl gpio clock, sda gpio clock */

        GPIOH, GPIO_AF_4, GPIO_PIN_4,          /* scl port, scl alternate, scl pin */
        GPIOB, GPIO_AF_4, GPIO_PIN_11,          /* sda port, sda alternate, sda pin */
#endif

        &i2c1,
        "hwi2c1",
    },
#endif

#ifdef BSP_USING_HARD_I2C2
    {
    I2C2,    /* uart peripheral index */

    RCU_I2C2, RCU_GPIOA, RCU_GPIOC,    /* periph clock, scl gpio clock, sda gpio clock */

    GPIOA, GPIO_AF_4, GPIO_PIN_8,    /* scl port, scl alternate, scl pin */
    GPIOC, GPIO_AF_4, GPIO_PIN_9,    /* sda port, sda alternate, sda pin */

        &i2c2,
        "hwi2c2",
    },
#endif

#ifdef BSP_USING_HARD_I2C3
    {
    I2C3,    /* uart peripheral index */

    RCU_I2C3, RCU_GPIOF, RCU_GPIOF,    /* periph clock, scl gpio clock, sda gpio clock */

    GPIOF, GPIO_AF_4, GPIO_PIN_14,    /* scl port, scl alternate, scl pin */
    GPIOF, GPIO_AF_4, GPIO_PIN_15,    /* sda port, sda alternate, sda pin */

        &i2c3,
        "hwi2c3",
    },
#endif
#ifdef BSP_USING_HARD_I2C4
    {
    I2C4,    /* uart peripheral index */

    RCU_I2C4, RCU_GPIOG, RCU_GPIOG,    /* periph clock, scl gpio clock, sda gpio clock */

    GPIOG, GPIO_AF_6, GPIO_PIN_7,    /* scl port, scl alternate, scl pin */
    GPIOG, GPIO_AF_6, GPIO_PIN_8,    /* sda port, sda alternate, sda pin */

        &i2c4,
        "hwi2c4",
    },
#endif
#ifdef BSP_USING_HARD_I2C5
    {
    I2C5,    /* uart peripheral index */

    RCU_I2C5, RCU_GPIOF, RCU_GPIOF,    /* periph clock, scl gpio clock, sda gpio clock */

    GPIOF, GPIO_AF_4, GPIO_PIN_11,    /* scl port, scl alternate, scl pin */
    GPIOF, GPIO_AF_4, GPIO_PIN_12,    /* sda port, sda alternate, sda pin */

        &i2c5,
        "hwi2c5",
    }
#endif
};
#else
static const struct gd32_i2c_bus gd_i2c_config[] = {
#ifdef BSP_USING_HARD_I2C0
    {
    /* uart peripheral index */
#if defined(SOC_SERIES_GD32M53x)
    I2C,
    RCU_I2C,
    I2C_EV_IRQn,
    I2C_ER_IRQn,
#else
    I2C0,
    RCU_I2C0,
#if defined(SOC_SERIES_GD32G5x3)
    I2C0_EV_WKUP_IRQn,
#else
    I2C0_EV_IRQn,
#endif
    I2C0_ER_IRQn,

#endif
    "hwi2c0",
    &i2c0,
#ifdef BSP_USING_I2C_TX_DMA
#ifdef BSP_I2C0_TX_USING_DMA
    &i2c0_dma_tx_cfg,
#else
    RT_NULL,
#endif
#endif
#ifdef BSP_USING_I2C_RX_DMA
#ifdef BSP_I2C0_RX_USING_DMA
    &i2c0_dma_rx_cfg,
#else
    RT_NULL,
#endif
#endif
    },
#endif

#ifdef BSP_USING_HARD_I2C1
    {
    I2C1,
    RCU_I2C1,
#if defined(SOC_SERIES_GD32G5x3)
    I2C1_EV_WKUP_IRQn,
#else
    I2C1_EV_IRQn,
#endif
    I2C1_ER_IRQn,
    "hwi2c1",
    &i2c1,
#ifdef BSP_USING_I2C_TX_DMA
#ifdef BSP_I2C1_TX_USING_DMA
    &i2c1_dma_tx_cfg,
#else
    RT_NULL,
#endif
#endif
#ifdef BSP_USING_I2C_RX_DMA
#ifdef BSP_I2C1_RX_USING_DMA
    &i2c1_dma_rx_cfg,
#else
    RT_NULL,
#endif
#endif
    },
#endif

#ifdef BSP_USING_HARD_I2C2
    {
    I2C2,
    RCU_I2C2,
#if defined(SOC_SERIES_GD32G5x3)
    I2C2_EV_WKUP_IRQn,
#else
    I2C2_EV_IRQn,
#endif
    I2C2_ER_IRQn,
    "hwi2c2",
    &i2c2,
#ifdef BSP_USING_I2C_TX_DMA
#ifdef BSP_I2C2_TX_USING_DMA
    &i2c2_dma_tx_cfg,
#else
    RT_NULL,
#endif
#endif
#ifdef BSP_USING_I2C_RX_DMA
#ifdef BSP_I2C2_RX_USING_DMA
    &i2c2_dma_rx_cfg,
#else
    RT_NULL,
#endif
#endif
    },
#endif

#ifdef BSP_USING_HARD_I2C3
    {
    I2C3,
    RCU_I2C3,
#if defined(SOC_SERIES_GD32G5x3)
    I2C3_EV_WKUP_IRQn,
#else
    I2C3_EV_IRQn,
#endif
    I2C3_ER_IRQn,
    "hwi2c3",
    &i2c3,
#ifdef BSP_USING_I2C_TX_DMA
#ifdef BSP_I2C3_TX_USING_DMA
    &i2c3_dma_tx_cfg,
#else
    RT_NULL,
#endif
#endif
#ifdef BSP_USING_I2C_RX_DMA
#ifdef BSP_I2C3_RX_USING_DMA
    &i2c3_dma_rx_cfg,
#else
    RT_NULL,
#endif
#endif
    },
#endif

#ifdef BSP_USING_HARD_I2C4
    {
    I2C4,
    RCU_I2C4,
    I2C4_EV_IRQn,
    I2C4_ER_IRQn,
    "hwi2c4",
    &i2c4,
#ifdef BSP_USING_I2C_TX_DMA
#ifdef BSP_I2C4_TX_USING_DMA
    &i2c4_dma_tx_cfg,
#else
    RT_NULL,
#endif
#endif
#ifdef BSP_USING_I2C_RX_DMA
#ifdef BSP_I2C4_RX_USING_DMA
    &i2c4_dma_rx_cfg,
#else
    RT_NULL,
#endif
#endif
    },
#endif

#ifdef BSP_USING_HARD_I2C5
    {
    I2C5,
    RCU_I2C5,
    I2C5_EV_IRQn,
    I2C5_ER_IRQn,
    "hwi2c5",
    &i2c5,
#ifdef BSP_USING_I2C_TX_DMA
#ifdef BSP_I2C5_TX_USING_DMA
    &i2c5_dma_tx_cfg,
#else
    RT_NULL,
#endif
#endif
#ifdef BSP_USING_I2C_RX_DMA
#ifdef BSP_I2C5_RX_USING_DMA
    &i2c5_dma_rx_cfg,
#else
    RT_NULL,
#endif
#endif
    }
#endif
};
#endif

#if defined(SOC_SERIES_GD32F5xx) && (defined(BSP_USING_I2C_TX_DMA) || defined(BSP_USING_I2C_RX_DMA))
static rt_size_t gd32_i2c_get_bus_count(void)
{
    return sizeof(gd_i2c_config) / sizeof(gd_i2c_config[0]);
}
#endif

#if !defined(SOC_SERIES_GD32H75E) && !defined(SOC_SERIES_GD32E51x) && !defined(SOC_SERIES_GD32F3x0) \
 && !defined(SOC_SERIES_GD32F50x) && !defined(SOC_SERIES_GD32G5x3) && !defined(SOC_SERIES_GD32C11x) \
 && !defined(SOC_SERIES_GD32L23x) && !defined(SOC_SERIES_GD32E23x) && !defined(SOC_SERIES_GD32E11x) \
 && !defined(SOC_SERIES_GD32H77x) && !defined(SOC_SERIES_GD32M53x) && !defined(SOC_SERIES_GD32H7xx) \
 && !defined(SOC_SERIES_GD32F5xx)
/**
  * @brief  This function initializes the i2c pin.
  * @param  i2c
  * @retval None
  */
static void gd32_i2c_gpio_init(const struct gd32_i2c_bus *i2c)
{
    /* enable I2C and GPIO clock */
    rcu_periph_clock_enable(i2c->scl_gpio_clk);
    rcu_periph_clock_enable(i2c->sda_gpio_clk);
    rcu_periph_clock_enable(i2c->i2c_clk);
#if defined (SOC_SERIES_GD32F30x)
    gpio_init(i2c->sda_port, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, i2c->sda_pin);
    gpio_init(i2c->scl_port, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, i2c->scl_pin);
	
#else

    /* configure I2C_SCL as alternate function push-pull */
    gpio_af_set(i2c->scl_port, i2c->scl_af, i2c->scl_pin);
    gpio_mode_set(i2c->scl_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, i2c->scl_pin);
#if defined (SOC_SERIES_GD32H7xx)
    gpio_output_options_set(i2c->scl_port, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, i2c->scl_pin);
    /* configure I2C_SDA as alternate function push-pull */
    gpio_af_set(i2c->sda_port, i2c->sda_af, i2c->sda_pin);
    gpio_mode_set(i2c->sda_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, i2c->sda_pin);
    gpio_output_options_set(i2c->sda_port, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ, i2c->sda_pin);
#else
    gpio_output_options_set(i2c->scl_port, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, i2c->scl_pin);
    /* configure I2C_SDA as alternate function push-pull */
    gpio_af_set(i2c->sda_port, i2c->sda_af, i2c->sda_pin);
    gpio_mode_set(i2c->sda_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, i2c->sda_pin);
    gpio_output_options_set(i2c->sda_port, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, i2c->sda_pin);
#endif
#endif
}
#endif

/**
  * @brief  read data.
  * @param  i2c_periph
  * @param  *p_buffer
  * @param  data_byte
  * @retval None
  */
static uint8_t gd32_i2c_read(rt_uint32_t i2c_periph, rt_uint8_t *p_buffer, rt_uint16_t data_byte)
{
    if (data_byte == 0) return 1;

#if defined(BSP_USING_I2C_RX_DMA) && defined(SOC_SERIES_GD32F5xx)
    const struct gd32_i2c_bus *i2c_bus = gd32_i2c_find_bus(i2c_periph);

    if ((i2c_bus != RT_NULL) &&
        ((IS_I2C_LEGACY(i2c_periph) && (I2C_CTL1(i2c_periph) & I2C_CTL1_DMAON)) ||
         (!IS_I2C_LEGACY(i2c_periph) && (I2C_CTL0_GD(i2c_periph) & I2C_CTL0_DENR_GD))))
    {
        rt_kprintf("[i2c-dma] read use dma: i2c=0x%08x len=%d stat=0x%08x ctl0=0x%08x\n",
                   i2c_periph, data_byte, I2C_STAT_GD(i2c_periph), I2C_CTL0_GD(i2c_periph));
        return gd32_i2c_dma_rx_wait(i2c_bus);
    }
#endif /* BSP_USING_I2C_RX_DMA && SOC_SERIES_GD32F5xx */

    /* while there is data to be read */
    while(data_byte)
    {
#if defined(GD32F5XX_USING_LEGACY_I2C) || defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32F30x) \
 || defined (SOC_SERIES_GD32E51x )|| defined (SOC_SERIES_GD32F3x0) || defined (SOC_SERIES_GD32C11x) \
 || defined (SOC_SERIES_GD32E23x) || defined (SOC_SERIES_GD32E11x)
        if(IS_I2C_LEGACY(i2c_periph))
        {
            if(3 == data_byte)
            {
                    /* wait until BTC bit is set */
                    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
                    /* disable acknowledge */
                    i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
            }

            if(2 == data_byte)
            {
                    /* wait until BTC bit is set */
                    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
                    /* send a stop condition to I2C bus */
                    i2c_stop_on_bus(i2c_periph);
            }
            /* wait until RBNE bit is set */
            if(i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
            {
                    /* read a byte from the EEPROM */
                    *p_buffer = i2c_data_receive(i2c_periph);
                    /* point to the next location where the byte read will be saved */
                    p_buffer++;
                    /* decrement the read bytes counter */
                    data_byte--;
            }
        }else
#endif
        {
            /* wait until the RBNE bit is set */
            while(!i2c_flag_get_gd(i2c_periph, I2C_FLAG_RBNE_GD));

            /* read a byte */
            *p_buffer = i2c_data_receive_gd(i2c_periph);
            /* point to the next location where the byte read will be saved */
            p_buffer++;
            /* decrement the read bytes counter */
            data_byte--;
        }
    }
    return 0;
}

/**
  * @brief  write data.
  * @param  i2c_periph
  * @param  *p_buffer
  * @param  data_byte
  * @retval None
  */
static uint8_t gd32_i2c_write(rt_uint32_t i2c_periph, uint8_t *p_buffer, uint16_t data_byte)
{
    if (data_byte == 0) return 1;

    while(data_byte)
    {
#if defined(GD32F5XX_USING_LEGACY_I2C) || defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32F30x) \
 || defined (SOC_SERIES_GD32C11x) || defined (SOC_SERIES_GD32E51x) || defined (SOC_SERIES_GD32F3x0) \
 || defined (SOC_SERIES_GD32E23x) || defined (SOC_SERIES_GD32E11x)
        if(IS_I2C_LEGACY(i2c_periph))
        {
#if defined(BSP_USING_I2C_TX_DMA) && defined(SOC_SERIES_GD32F5xx)
            const struct gd32_i2c_bus *i2c_bus = gd32_i2c_find_bus(i2c_periph);

            if ((i2c_bus != RT_NULL) && (I2C_CTL1(i2c_periph) & I2C_CTL1_DMAON))
            {
                return gd32_i2c_dma_tx_wait(i2c_bus);
            }

            if ((i2c_bus != RT_NULL) &&
                data_byte > 1U &&
                i2c_bus->dma_tx != RT_NULL)
            {
                i2c_data_transmit(i2c_periph, *p_buffer);
                p_buffer++;
                data_byte--;

                while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));

                if (gd32_i2c_dma_tx_start(i2c_bus, p_buffer, data_byte) == RT_TRUE)
                {
                    return gd32_i2c_dma_tx_wait(i2c_bus);
                }
            }
#endif
            /* data transmission */
            i2c_data_transmit(i2c_periph, *p_buffer);
            /* point to the next byte to be written */
            p_buffer++;
            /* decrement the write bytes counter */
            data_byte--;
            /* wait until the TI bit is set */
            while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
        }
        else
#endif
        {
#if defined(BSP_USING_I2C_TX_DMA) && defined(SOC_SERIES_GD32F5xx)
            const struct gd32_i2c_bus *i2c_bus = gd32_i2c_find_bus(i2c_periph);

            if ((i2c_bus != RT_NULL) && (I2C_CTL0_GD(i2c_periph) & I2C_CTL0_DENT_GD))
            {
                return gd32_i2c_dma_tx_wait(i2c_bus);
            }
#endif
    #if defined(GD32F5XX_USING_NEW_I2C) || defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32H75E) \
 || defined (SOC_SERIES_GD32L23x) || defined (SOC_SERIES_GD32E51x) || defined (SOC_SERIES_GD32F50x) \
 || defined (SOC_SERIES_GD32G5x3) || defined (SOC_SERIES_GD32H77x) || defined (SOC_SERIES_GD32M53x)
            /* wait until the transmit data buffer is empty */
            I2C_STAT_GD(i2c_periph) |= I2C_STAT_TBE_GD;
            while(!i2c_flag_get_gd(i2c_periph, I2C_FLAG_TBE));

            while(data_byte)
            {
        #if defined(SOC_SERIES_GD32F5xx) && (defined(BSP_USING_I2C_TX_DMA) || defined(BSP_USING_I2C_RX_DMA))
                    while(!i2c_flag_get_gd(i2c_periph, I2C_FLAG_TI_GD));
                    i2c_data_transmit_gd(i2c_periph, *p_buffer);
                    p_buffer++;
                    data_byte--;
                    if (data_byte != 0)
                    {
                        while(!i2c_flag_get_gd(i2c_periph, I2C_FLAG_TI_GD) &&
                              !i2c_flag_get_gd(i2c_periph, I2C_FLAG_TC_GD));
                    }
    #else
                /* wait until the TI bit is set */
                while(!i2c_flag_get_gd(i2c_periph, I2C_FLAG_TI_GD));
                /* data transmission */
                i2c_data_transmit(i2c_periph, *p_buffer);
                /* point to the next byte to be written */
                p_buffer++;
                /* decrement the write bytes counter */
                data_byte--;
    #endif
            }
#endif
#if defined(SOC_SERIES_GD32F5xx) && (defined(BSP_USING_I2C_TX_DMA) || defined(BSP_USING_I2C_RX_DMA))
            while(!i2c_flag_get_gd(i2c_periph, I2C_FLAG_TC_GD));
#endif
        }
    }

    if(data_byte != 0)
    {
        return 1;
    }
    return 0;
}

/**
  * @brief
  * @param
  * @param
  * @param
  * @retval
  */

static rt_ssize_t gd32_i2c_master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    static struct rt_i2c_msg *msg;
    rt_uint16_t addr;

    rt_uint32_t i,w_total_byte=0,r_total_byte=0;
    rt_err_t ret = RT_ERROR;
#if defined(SOC_SERIES_GD32F5xx)
    rt_uint32_t tx_sequence_len = 0;
    rt_uint32_t tx_sequence_end = 0;
#if defined(BSP_USING_I2C_TX_DMA)
    uint8_t *dma_chain_buf = RT_NULL;
    rt_uint16_t dma_chain_len = 0;
    rt_bool_t dma_chain_started = RT_FALSE;
#endif
#endif

    RT_ASSERT(bus != RT_NULL);

    struct gd32_i2c_bus *gd32_i2c = (struct gd32_i2c_bus *)bus->priv;

    for(i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if(msg->flags & RT_I2C_RD)
        {
            r_total_byte += msg->len;
        }else{
            w_total_byte += msg->len;
        }
    }

    for(i = 0; i < num; i++)
    {
        msg = &msgs[i];
        addr = msg->addr << 1;

#if defined(SOC_SERIES_GD32F5xx)
        rt_kprintf("[i2c-xfer] msg%u flags=0x%02x len=%u rd=%u nostart=%u\n",
                   i,
                   msg->flags,
                   msg->len,
                   !!(msg->flags & RT_I2C_RD),
                   !!(msg->flags & RT_I2C_NO_START));
#endif

    #if defined(SOC_SERIES_GD32F5xx)
        tx_sequence_len = msg->len;
        tx_sequence_end = i;

    #if defined(BSP_USING_I2C_TX_DMA)
        dma_chain_buf = RT_NULL;
        dma_chain_len = 0;
        dma_chain_started = RT_FALSE;
    #endif
    #endif

        if (!(msg->flags & RT_I2C_NO_START))
        {
#if defined(GD32F5XX_USING_LEGACY_I2C) || defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32F30x) \
 || defined (SOC_SERIES_GD32E51x) || defined (SOC_SERIES_GD32F3x0) || defined (SOC_SERIES_GD32C11x) \
 || defined (SOC_SERIES_GD32E23x) || defined (SOC_SERIES_GD32E11x)
            if(IS_I2C_LEGACY(gd32_i2c->i2c_periph))
            {
                if(msg->flags & RT_I2C_RD)
                {
                        /* enable acknowledge */
                    i2c_ack_config(gd32_i2c->i2c_periph, I2C_ACK_ENABLE);
                    if (msg->len == 2U)
                    {
                        /* Configure ACK position for 2-byte read */
                        i2c_ackpos_config(gd32_i2c->i2c_periph, I2C_ACKPOS_NEXT);
                    }
                        /* send the start signal */
                    i2c_start_on_bus(gd32_i2c->i2c_periph);
                     /* i2c master sends START signal successfully */
                    while(!i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_SBSEND));

                    i2c_master_addressing(gd32_i2c->i2c_periph, addr, I2C_RECEIVER);

                    while(!i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND));

#if defined(BSP_USING_I2C_RX_DMA) && defined(SOC_SERIES_GD32F5xx)
                    if (msg->len >= I2C_DMA_TRANS_MIN_LEN && gd32_i2c->dma_rx != RT_NULL)
                    {
                        gd32_i2c_dma_rx_start(gd32_i2c, msg->buf, msg->len);
                    }
                    else
#endif
                    if (msg->len <= 2)
                    {
                        i2c_ack_config(gd32_i2c->i2c_periph, I2C_ACK_DISABLE);
                    }
                    i2c_flag_clear(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND);
                    if (msg->len == 1)
                    {
                        i2c_stop_on_bus(gd32_i2c->i2c_periph);
                    }

               }else {
                     /* configure slave address */
                    while(i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_I2CBSY));
                     //i2c_transfer_byte_number_config(gd32_i2c->i2c_periph, w_total_byte);
                     /* send a start condition to I2C bus */
                    i2c_start_on_bus(gd32_i2c->i2c_periph);
                    while(!i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_SBSEND));

                    i2c_master_addressing(gd32_i2c->i2c_periph, addr, I2C_TRANSMITTER);
                    while(!i2c_flag_get(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND));

                    i2c_flag_clear(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND);
               }
            }else
#endif
            {
#if defined(GD32F5XX_USING_NEW_I2C) || defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32H75E) \
 || defined (SOC_SERIES_GD32L23x) || defined (SOC_SERIES_GD32E51x) || defined (SOC_SERIES_GD32F50x) \
 || defined (SOC_SERIES_GD32G5x3) || defined (SOC_SERIES_GD32H77x) || defined (SOC_SERIES_GD32M53x)
                if(msg->flags & RT_I2C_ADDR_10BIT)
                {
                        /* enable 10-bit addressing mode in master mode */
                    i2c_address10_enable_gd(gd32_i2c->i2c_periph);
                }else {
                        /* disable 10-bit addressing mode in master mode */
                    i2c_address10_disable_gd(gd32_i2c->i2c_periph);
                }

                if(msg->flags & RT_I2C_RD)
                {
    #if defined(SOC_SERIES_GD32F5xx)
                    rt_kprintf("[i2c-xfer] enter new-i2c read setup: i2c=0x%08x len=%u r_total=%u\n",
                             gd32_i2c->i2c_periph,
                             msg->len,
                             r_total_byte);
    #endif
                     /* configure slave address */
                    i2c_master_addressing_gd(gd32_i2c->i2c_periph, addr, I2C_MASTER_RECEIVE_GD);
                    i2c_transfer_byte_number_config_gd(gd32_i2c->i2c_periph, r_total_byte);
#if defined(BSP_USING_I2C_RX_DMA) && defined(SOC_SERIES_GD32F5xx)
                    if (msg->len >= I2C_DMA_TRANS_MIN_LEN && gd32_i2c->dma_rx != RT_NULL)
                    {
                        rt_kprintf("[i2c-dma] master read start dma: i2c=0x%08x len=%d addr=0x%02x\n",
                                   gd32_i2c->i2c_periph, msg->len, addr);
                        gd32_i2c_dma_rx_start(gd32_i2c, msg->buf, msg->len);
                    }
#endif
                     /* send a start condition to I2C bus */
                    i2c_start_on_bus_gd(gd32_i2c->i2c_periph);
                }else {
                     /* configure slave address */
                    i2c_master_addressing_gd(gd32_i2c->i2c_periph, addr, I2C_MASTER_TRANSMIT_GD);
                    while(i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_I2CBSY_GD));
#if defined(SOC_SERIES_GD32F5xx)
                    struct rt_i2c_msg *next_msg = RT_NULL;

                    while ((tx_sequence_end + 1) < num)
                    {
                        next_msg = &msgs[tx_sequence_end + 1];

                        if (!(next_msg->flags & RT_I2C_RD) &&
                            (next_msg->flags & RT_I2C_NO_START) &&
                            next_msg->addr == msg->addr)
                        {
                            tx_sequence_end++;
                            tx_sequence_len += next_msg->len;
                            continue;
                        }

                        break;
                    }
                    i2c_transfer_byte_number_config_gd(gd32_i2c->i2c_periph, tx_sequence_len);
#else
                    i2c_transfer_byte_number_config_gd(gd32_i2c->i2c_periph, w_total_byte);
#endif
#if defined(BSP_USING_I2C_TX_DMA) && defined(SOC_SERIES_GD32F5xx)
                    if ((tx_sequence_end != i) &&
                        (tx_sequence_len >= I2C_DMA_TRANS_MIN_LEN) &&
                        (gd32_i2c->dma_tx != RT_NULL))
                    {
                        dma_chain_buf = gd32_i2c_build_write_chain_buffer(msgs,
                                                                          i,
                                                                          tx_sequence_end,
                                                                          &dma_chain_len);
                        if (dma_chain_buf != RT_NULL &&
                            gd32_i2c_dma_tx_start(gd32_i2c, dma_chain_buf, dma_chain_len) == RT_TRUE)
                        {
                            dma_chain_started = RT_TRUE;
                        }
                        else if (dma_chain_buf != RT_NULL)
                        {
                            rt_free(dma_chain_buf);
                            dma_chain_buf = RT_NULL;
                        }
                    }
                    else if (msg->len >= I2C_DMA_TRANS_MIN_LEN &&
                             gd32_i2c->dma_tx != RT_NULL)
                    {
                        gd32_i2c_dma_tx_start(gd32_i2c, msg->buf, msg->len);
                    }
#endif
                     /* send a start condition to I2C bus */
                    i2c_start_on_bus_gd(gd32_i2c->i2c_periph);
                }
#endif
            }
        }

        if(msg->flags & RT_I2C_RD)
        {
            if(gd32_i2c_read(gd32_i2c->i2c_periph, msg->buf, msg->len) != 0)
            {
                LOG_E("i2c bus read failed,i2c bus stop!");
                goto out;
            }
#if defined(SOC_SERIES_GD32F5xx)
            rt_kprintf("[i2c-dma] master read done: i2c=0x%08x len=%d\n", gd32_i2c->i2c_periph, msg->len);
#endif
        }else {
#if defined(BSP_USING_I2C_TX_DMA) && defined(SOC_SERIES_GD32F5xx)
            if (!IS_I2C_LEGACY(gd32_i2c->i2c_periph) && dma_chain_started == RT_TRUE)
            {
                if (gd32_i2c_write(gd32_i2c->i2c_periph, dma_chain_buf, dma_chain_len) != 0)
                {
                    LOG_E("i2c bus write failed,i2c bus stop!");
                    goto out;
                }

                rt_free(dma_chain_buf);
                dma_chain_buf = RT_NULL;
                i = tx_sequence_end;
            }
            else
#endif
            if(gd32_i2c_write(gd32_i2c->i2c_periph, msg->buf, msg->len) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!");
                goto out;
            }
       }
#if defined(GD32F5XX_USING_NEW_I2C) || defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32H75E) \
 || defined (SOC_SERIES_GD32L23x) || defined (SOC_SERIES_GD32E51x) || defined (SOC_SERIES_GD32F50x) \
 || defined (SOC_SERIES_GD32G5x3) || defined (SOC_SERIES_GD32H77x) || defined (SOC_SERIES_GD32M53x)
        if(!IS_I2C_LEGACY(gd32_i2c->i2c_periph))
        {
            if(r_total_byte != 0)
            {
#if defined(SOC_SERIES_GD32F5xx)
                rt_kprintf("[i2c-xfer] wait tc before next msg/out: i2c=0x%08x msg%u stat=0x%08x ctl0=0x%08x\n",
                           gd32_i2c->i2c_periph,
                           i,
                           I2C_STAT_GD(gd32_i2c->i2c_periph),
                           I2C_CTL0_GD(gd32_i2c->i2c_periph));
#endif
                while(!i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_TC_GD));
#if defined(SOC_SERIES_GD32F5xx)
                rt_kprintf("[i2c-xfer] wait tc done: i2c=0x%08x msg%u stat=0x%08x ctl0=0x%08x\n",
                           gd32_i2c->i2c_periph,
                           i,
                           I2C_STAT_GD(gd32_i2c->i2c_periph),
                           I2C_CTL0_GD(gd32_i2c->i2c_periph));
#endif
            }
        }
#endif

    }
    ret = i;

out:
#if defined(BSP_USING_I2C_TX_DMA) && defined(SOC_SERIES_GD32F5xx)
    if (dma_chain_buf != RT_NULL)
    {
        rt_free(dma_chain_buf);
    }
#endif
#if defined(GD32F5XX_USING_LEGACY_I2C) || defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32F30x) \
 || defined (SOC_SERIES_GD32E51x) || defined (SOC_SERIES_GD32F3x0) || defined (SOC_SERIES_GD32C11x) \
 || defined (SOC_SERIES_GD32E23x) || defined (SOC_SERIES_GD32E11x)
    if(IS_I2C_LEGACY(gd32_i2c->i2c_periph))
    {

        if(!(msg->flags & RT_I2C_NO_STOP))
        {
            if(msg->flags & RT_I2C_RD)
            {
                while((I2C_CTL0(gd32_i2c->i2c_periph) & I2C_CTL0_STOP));
            }else{
                /* send a stop condition to I2C bus */
                i2c_stop_on_bus(gd32_i2c->i2c_periph);
                /* wait until stop condition generate */
                while((I2C_CTL0(gd32_i2c->i2c_periph) & I2C_CTL0_STOP));
                /* clear the STPDET bit */
            }
        }
    }else
#endif
    {
#if defined(GD32F5XX_USING_NEW_I2C) || defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32L23x) \
 || defined (SOC_SERIES_GD32H75E) || defined (SOC_SERIES_GD32E51x) || defined (SOC_SERIES_GD32F50x) \
 || defined (SOC_SERIES_GD32G5x3) || defined (SOC_SERIES_GD32H77x) || defined (SOC_SERIES_GD32M53x)
        if(!(msg->flags & RT_I2C_NO_STOP))
        {
            while(!i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_TC_GD));
            /* send a stop condition to I2C bus */
            i2c_stop_on_bus_gd(gd32_i2c->i2c_periph);
            /* wait until stop condition generate */
            while(!i2c_flag_get_gd(gd32_i2c->i2c_periph, I2C_FLAG_STPDET_GD));
            /* clear the STPDET bit */
            i2c_flag_clear_gd(gd32_i2c->i2c_periph, I2C_FLAG_STPDET_GD);
        }
#endif
    }
    return ret;
}

static const struct rt_i2c_bus_device_ops i2c_ops = {
    .master_xfer = gd32_i2c_master_xfer,
    .slave_xfer = RT_NULL,
    .i2c_bus_control = RT_NULL
};

/**
  * @brief  I2C initialization function
  * @param  None
  * @retval RT_EOK indicates successful initialization.
  */
int rt_hw_i2c_init(void)
{
    rt_size_t obj_num = sizeof(gd_i2c_config) / sizeof(gd_i2c_config[0]);
//    rt_err_t result;

    for(int i = 0; i < obj_num; i++)
    {

        gd32_i2c_gpio_init(&gd_i2c_config[i]);

        /* configure I2C timing. I2C speed clock=400kHz*/
#if defined(GD32F5XX_USING_LEGACY_I2C) || defined (SOC_SERIES_GD32F4xx) || defined (SOC_SERIES_GD32F30x) \
 || defined (SOC_SERIES_GD32E51x) || defined (SOC_SERIES_GD32F3x0) || defined (SOC_SERIES_GD32C11x) \
 || defined (SOC_SERIES_GD32E23x) || defined (SOC_SERIES_GD32E11x)
        if(IS_I2C_LEGACY(gd_i2c_config[i].i2c_periph))
        {

            i2c_clock_config(gd_i2c_config[i].i2c_periph, 100000, I2C_DTCY_2);
            i2c_mode_addr_config(gd_i2c_config[i].i2c_periph, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, 0xa0);
            i2c_enable(gd_i2c_config[i].i2c_periph);
            i2c_ack_config(gd_i2c_config[i].i2c_periph, I2C_ACK_ENABLE);
        }else
#endif
        {
#if defined(GD32F5XX_USING_NEW_I2C) || defined (SOC_SERIES_GD32H7xx) || defined (SOC_SERIES_GD32H75E) \
 || defined (SOC_SERIES_GD32G5x3) || defined (SOC_SERIES_GD32L23x) || defined (SOC_SERIES_GD32E51x) \
 || defined (SOC_SERIES_GD32F50x) || defined (SOC_SERIES_GD32H77x) || defined (SOC_SERIES_GD32M53x)
            
            i2c_timing_config_gd(gd_i2c_config[i].i2c_periph, 0x1, 0x7, 0);
            i2c_master_clock_config_gd(gd_i2c_config[i].i2c_periph, 0x2D, 0x87);

            /* enable I2C1 */
            i2c_enable_gd(gd_i2c_config[i].i2c_periph);
#endif
        }

        gd_i2c_config[i].i2c_bus->ops = &i2c_ops;
        gd_i2c_config[i].i2c_bus->priv = (void *)&gd_i2c_config[i];

        rt_i2c_bus_device_register(gd_i2c_config[i].i2c_bus, gd_i2c_config[i].device_name);
    }

    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */
