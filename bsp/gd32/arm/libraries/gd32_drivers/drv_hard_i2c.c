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

/* I2C transfer timeout in milliseconds */
#ifdef BSP_I2C_XFER_TIMEOUT
#define I2C_TIMEOUT_MS          BSP_I2C_XFER_TIMEOUT
#else
#define I2C_TIMEOUT_MS          1000
#endif

/* I2C DMA transfer threshold (bytes), only use DMA when length >= this value */
#ifdef BSP_I2C_DMA_TRANS_MIN_LEN
#define I2C_DMA_TRANS_MIN_LEN   BSP_I2C_DMA_TRANS_MIN_LEN
#else
#define I2C_DMA_TRANS_MIN_LEN   4
#endif

/* F30x-specific I2C DMA compatibility (common DMA macros are in drv_dma.h) */
#if defined(SOC_SERIES_GD32F30x)
/* F30x I2C DMA enable function has a different name */
#define i2c_dma_config(periph, state)        i2c_dma_enable(periph, state)
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

#if defined(SOC_SERIES_GD32F5xx)
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

/* Compatibility macros: unify DMA request-field vs subperipheral-select differences */
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
#define gd32_i2c_dma_request_config(init_s, dma_cfg)    ((init_s)->request = (dma_cfg)->request)
#define gd32_i2c_dma_subperiph_config(periph, ch, cfg)
#elif defined(SOC_SERIES_GD32F30x)
/* F30x has fixed DMA channel mapping, no request or subperipheral selection */
#define gd32_i2c_dma_request_config(init_s, dma_cfg)
#define gd32_i2c_dma_subperiph_config(periph, ch, cfg)
#else
#define gd32_i2c_dma_request_config(init_s, dma_cfg)
#define gd32_i2c_dma_subperiph_config(periph, ch, cfg)  dma_channel_subperipheral_select(periph, ch, (cfg)->subperiph)
#endif

#if defined(SOC_SERIES_GD32H77x)
#define gd32_dma_deinit(periph, ch)                 dma_channel_deinit(periph, ch)
#else
#define gd32_dma_deinit(periph, ch)                 dma_deinit(periph, ch)
#endif

/* New I2C IP DMA macros: CTL1 registers, atomic config, frame mode, data registers, DMA control */
#if defined(SOC_SERIES_GD32F5xx)
#define I2C_CTL1_REG(periph)                 I2C_ADD_CTL1(periph)
#define I2C_CTL1_BYTENUM_GD                  I2C_ADD_CTL1_BYTENUM
#define I2C_CTL1_RELOAD_GD                   I2C_ADD_CTL1_RELOAD
#define I2C_CTL1_AUTOEND_GD                  I2C_ADD_CTL1_AUTOEND
#define I2C_CTL0_GD(periph)                  I2C_ADD_CTL0(periph)
#define I2C_TDATA_GD(periph)                 I2C_ADD_TDATA(periph)
#define I2C_RDATA_GD(periph)                 I2C_ADD_RDATA(periph)
#define I2C_FLAG_TCR_GD                      I2C_ADD_FLAG_TCR
#define MAX_RELOAD_SIZE                      255
#if defined(BSP_USING_I2C_RX_DMA) || defined(BSP_USING_I2C_TX_DMA)
#define i2c_dma_enable_gd                    i2c_add_dma_enable
#define i2c_dma_disable_gd                   i2c_add_dma_disable
#define I2C_DMA_TRANSMIT_GD                  I2C_ADD_DMA_TRANSMIT
#define I2C_DMA_RECEIVE_GD                   I2C_ADD_DMA_RECEIVE
#endif
#elif defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
#define I2C_CTL1_REG(periph)                 I2C_CTL1(periph)
#define I2C_CTL1_BYTENUM_GD                  I2C_CTL1_BYTENUM
#define I2C_CTL1_RELOAD_GD                   I2C_CTL1_RELOAD
#define I2C_CTL1_AUTOEND_GD                  I2C_CTL1_AUTOEND
#define I2C_CTL0_GD(periph)                  I2C_CTL0(periph)
#define I2C_TDATA_GD(periph)                 I2C_TDATA(periph)
#define I2C_RDATA_GD(periph)                 I2C_RDATA(periph)
#define I2C_FLAG_TCR_GD                      I2C_FLAG_TCR
#define MAX_RELOAD_SIZE                      255
#if defined(BSP_USING_I2C_RX_DMA) || defined(BSP_USING_I2C_TX_DMA)
#define i2c_dma_enable_gd                    i2c_dma_enable
#define i2c_dma_disable_gd                   i2c_dma_disable
#define I2C_DMA_TRANSMIT_GD                  I2C_DMA_TRANSMIT
#define I2C_DMA_RECEIVE_GD                   I2C_DMA_RECEIVE
#endif
#endif

/* Frame mode for multi-msg transfer */
#define GD32_I2C_FIRST_FRAME                 BIT(0)    /* First msg: START, no AUTOEND */
#define GD32_I2C_FIRST_AND_LAST_FRAME        BIT(1)    /* Only one msg: START + AUTOEND */
#define GD32_I2C_NEXT_FRAME                  BIT(2)    /* Middle msg: no START, no AUTOEND */
#define GD32_I2C_LAST_FRAME                  BIT(3)    /* Last msg: no START, AUTOEND */
#define GD32_I2C_LAST_FRAME_NO_STOP          BIT(4)    /* Last msg without STOP */
#define GD32_I2C_FIRST_FRAME_RELOAD          BIT(5)    /* First msg: START, use RELOAD for next NO_START msg */
#define GD32_I2C_NEXT_FRAME_NO_START         BIT(6)    /* Continue from RELOAD, no START needed */
#define GD32_I2C_NEXT_FRAME_RELOAD           BIT(7)    /* Middle msg: RESTART, use RELOAD for next NO_START msg */

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

/* Compile-time I2C IP capability macros */
/* GD32_I2C_HAS_LEGACY_IP: Platform has Legacy I2C IP (use I2C_DATA register) */
#if defined(SOC_SERIES_GD32F4xx) || defined(SOC_SERIES_GD32F30x) || \
    defined(SOC_SERIES_GD32F3x0) || defined(SOC_SERIES_GD32C11x) || \
    defined(SOC_SERIES_GD32E23x) || defined(SOC_SERIES_GD32E11x) || \
    defined(SOC_SERIES_GD32F5xx) || defined(SOC_SERIES_GD32E51x)
#define GD32_I2C_HAS_LEGACY_IP
#endif

/* GD32_I2C_HAS_NEW_IP: Platform has New I2C IP (use I2C_TDATA/I2C_RDATA registers) */
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || \
    defined(SOC_SERIES_GD32L23x) || defined(SOC_SERIES_GD32F50x) || \
    defined(SOC_SERIES_GD32G5x3) || defined(SOC_SERIES_GD32H77x) || \
    defined(SOC_SERIES_GD32M53x) || defined(SOC_SERIES_GD32F5xx) || \
    defined(SOC_SERIES_GD32E51x)
#define GD32_I2C_HAS_NEW_IP
#endif

#if defined GD32_I2C_HAS_NEW_IP
/* Atomic CTL1 config: NBYTES + RELOAD + AUTOEND */
#define i2c_nbytes_reload_autoend_config_gd(periph, nbytes, reload, autoend) do { \
    uint32_t _ctl1 = I2C_CTL1_REG(periph); \
    _ctl1 &= ~(I2C_CTL1_BYTENUM_GD | I2C_CTL1_RELOAD_GD | I2C_CTL1_AUTOEND_GD); \
    _ctl1 |= ((uint32_t)(nbytes) << 16); \
    if(reload) _ctl1 |= I2C_CTL1_RELOAD_GD; \
    if(autoend) _ctl1 |= I2C_CTL1_AUTOEND_GD; \
    I2C_CTL1_REG(periph) = _ctl1; \
} while(0)
#endif

#if defined(BSP_USING_I2C_RX_DMA) || defined(BSP_USING_I2C_TX_DMA)
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
#endif /* BSP_USING_I2C_*_DMA */

#if !defined(SOC_SERIES_GD32H75E) && !defined(SOC_SERIES_GD32E51x) && !defined(SOC_SERIES_GD32F3x0) \
 && !defined(SOC_SERIES_GD32F50x) && !defined(SOC_SERIES_GD32G5x3) && !defined(SOC_SERIES_GD32C11x) \
 && !defined(SOC_SERIES_GD32L23x) && !defined(SOC_SERIES_GD32E23x) && !defined(SOC_SERIES_GD32E11x) \
 && !defined(SOC_SERIES_GD32H77x) && !defined(SOC_SERIES_GD32M53x) && !defined(SOC_SERIES_GD32H7xx) \
 && !defined(SOC_SERIES_GD32F5xx) && !defined(SOC_SERIES_GD32F30x)
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

/**
 * @brief  Unified timeout wait for I2C/DMA flag or legacy control bit.
  * @param  periph      I2C peripheral (used for I2C flag check)
  * @param  flag        Flag or legacy control bit to wait for
  * @param  set         RT_TRUE = wait for flag SET, RT_FALSE = wait for flag RESET
  * @param  dma         DMA config pointer (RT_NULL for I2C, non-NULL for DMA)
  * @retval RT_EOK on success, -RT_ETIMEOUT on timeout
  */
static int gd32_timeout_wait_flag(uint32_t periph, uint32_t flag, rt_bool_t set, struct dma_config *dma)
{
    rt_tick_t timeout = rt_tick_from_millisecond(I2C_TIMEOUT_MS);
    rt_tick_t start = rt_tick_get();

    while(1)
    {
        FlagStatus status;

#if defined(BSP_USING_I2C_RX_DMA) || defined(BSP_USING_I2C_TX_DMA)
        if(dma != RT_NULL)
        {
            /* DMA flag check */
            status = dma_flag_get(dma->periph, dma->channel, flag);
        }
        else
#endif
        {
#ifdef GD32_I2C_HAS_LEGACY_IP
            if(IS_I2C_LEGACY(periph))
            {
                if(flag == I2C_CTL0_STOP)
                {
                    /* Legacy STOP is a control bit in CTL0, not a status flag. */
                    status = (I2C_CTL0(periph) & I2C_CTL0_STOP) ? SET : RESET;
                }
                else
                {
                    /* Legacy I2C flag check */
                    status = i2c_flag_get(periph, flag);
                }
            }
            else
#endif
            {
                /* New I2C flag check */
                status = i2c_flag_get_gd(periph, flag);
            }
        }

        if((set && status == SET) || (!set && status != SET))
        {
            return RT_EOK;
        }

        if(rt_tick_get() - start > timeout)
        {
            return -RT_ETIMEOUT;
        }

        rt_thread_mdelay(1);
    }
}

#if defined(BSP_USING_I2C_RX_DMA) || defined(BSP_USING_I2C_TX_DMA)
/**
  * @brief  configure DMA channel for I2C transfer.
  * @param  dma
  * @param  periph_addr
  * @param  buf
  * @param  len
  * @param  direction
  * @retval None
  */
static void gd32_i2c_dma_config_channel(struct dma_config *dma, uint32_t periph_addr, uint8_t *buf, uint16_t len, uint32_t direction)
{
    dma_single_data_parameter_struct dma_init_struct;

    rcu_periph_clock_enable(dma->rcu);
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
    /* This DMA request path requires the DMAMUX clock. */
    rcu_periph_clock_enable(RCU_DMAMUX);
#endif
    gd32_dma_deinit(dma->periph, dma->channel);
    dma_single_data_para_struct_init(&dma_init_struct);
    dma_init_struct.periph_addr = periph_addr;
    GD32_DMA_SET_MEMADDR(&dma_init_struct, (uint32_t)buf);
    dma_init_struct.direction = direction;
    dma_init_struct.number = len;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    GD32_DMA_SET_DATAWIDTH(&dma_init_struct, dma->data_width);
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    /* Configure either the DMA request field or the subperipheral selector. */
    gd32_i2c_dma_request_config(&dma_init_struct, dma);
    dma_single_data_mode_init(dma->periph, dma->channel, &dma_init_struct);
    gd32_i2c_dma_subperiph_config(dma->periph, dma->channel, dma);
    dma_circulation_disable(dma->periph, dma->channel);
    /* NOTE: Do NOT enable DMA channel here! Caller controls enable order. */
}

#ifdef GD32_I2C_HAS_NEW_IP
/**
  * @brief  calculate frame mode for new I2C DMA transfer.
  * @param  msg
  * @param  next_msg
  * @param  index
  * @param  num
  * @retval frame mode constant
  */
static uint32_t gd32_i2c_new_frame_mode(struct rt_i2c_msg *msg, struct rt_i2c_msg *next_msg, rt_uint32_t index, rt_uint32_t num)
{
    uint8_t next_has_no_start = (next_msg != RT_NULL) && (next_msg->flags & RT_I2C_NO_START);

    if(num == 1)
    {
        /* Single message */
        return (msg->flags & RT_I2C_NO_STOP) ? GD32_I2C_LAST_FRAME_NO_STOP : GD32_I2C_FIRST_AND_LAST_FRAME;
    }
    else if(index == 0)
    {
        /* First message of multiple */
        if(next_has_no_start)
            return GD32_I2C_FIRST_FRAME_RELOAD;  /* Use RELOAD for seamless continuation */
        else
            return GD32_I2C_FIRST_FRAME;
    }
    else if(index == num - 1)
    {
        /* Last message */
        return (msg->flags & RT_I2C_NO_STOP) ? GD32_I2C_LAST_FRAME_NO_STOP : GD32_I2C_LAST_FRAME;
    }
    else
    {
        /* Middle message */
        if(next_has_no_start)
            return GD32_I2C_NEXT_FRAME_RELOAD;  /* RESTART, then RELOAD for seamless continuation */
        else
            return GD32_I2C_NEXT_FRAME;
    }
}
#endif /* GD32_I2C_HAS_NEW_IP */
#endif

#ifdef GD32_I2C_HAS_NEW_IP
#if defined(BSP_USING_I2C_TX_DMA) || defined(BSP_USING_I2C_RX_DMA)
/**
    * @brief  new I2C single-message transfer (DMA or polling).
    * @param  i2c_bus
    * @param  msg
    * @param  mode
    * @param  is_read
    * @param  use_dma
    * @retval 0 on success, non-zero on error
    */
static int gd32_i2c_new_msg_xfer(const struct gd32_i2c_bus *i2c_bus, struct rt_i2c_msg *msg, uint32_t mode, uint8_t is_read, uint8_t use_dma)
{
    uint32_t i2c_periph = i2c_bus->i2c_periph;
    uint16_t shifted_addr = msg->addr << 1;
    uint16_t remaining = msg->len;
    uint8_t *p_current = msg->buf;
    uint32_t nbytes;

    /* Direction-specific parameters */
    uint32_t i2c_direction = is_read ? I2C_MASTER_RECEIVE_GD : I2C_MASTER_TRANSMIT_GD;
    const char *dir_str = is_read ? "rx" : "tx";

    struct dma_config *dma = RT_NULL;
    uint32_t data_reg = 0;
    uint32_t dma_direction = 0;
    uint32_t dma_mode = 0;

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
#ifdef RT_USING_CACHE
    /* D-Cache coherency variables for the cache-sensitive DMA path. */
    void *dma_aligned_buf = RT_NULL;
    uint8_t *dma_buf_ptr = msg->buf;
    rt_size_t aligned_size = RT_ALIGN(msg->len, 32);

    if (use_dma && msg->len > 0)
    {
        /* Check if buffer needs cache-line alignment */
        if (!RT_IS_ALIGN((rt_uint32_t)msg->buf, 32) ||
            !RT_IS_ALIGN(msg->len, 32))
        {
            /* Allocate aligned temporary buffer */
            dma_aligned_buf = rt_malloc_align(aligned_size, 32);
            if (dma_aligned_buf == RT_NULL)
            {
                LOG_E("i2c %s DMA aligned buffer alloc failed", dir_str);
                return -RT_ENOMEM;
            }
            dma_buf_ptr = (uint8_t *)dma_aligned_buf;

            /* For TX: copy data to aligned buffer */
            if (!is_read)
            {
                rt_memset(dma_aligned_buf, 0, aligned_size);
                rt_memcpy(dma_buf_ptr, msg->buf, msg->len);
            }
        }

        /* For RX: invalidate target cache lines before DMA writes memory */
        if (is_read)
        {
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)dma_buf_ptr, aligned_size);
        }
        /* For TX: flush cache to ensure DMA reads latest data */
        else
        {
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)dma_buf_ptr, aligned_size);
        }
    }
#endif
#else
    uint8_t *dma_buf_ptr = msg->buf;
#endif /* cache-sensitive DMA path */

    if(use_dma)
    {
        dma = is_read ? i2c_bus->dma_rx : i2c_bus->dma_tx;
        data_reg = is_read ? (uint32_t)&I2C_RDATA_GD(i2c_periph)
                           : (uint32_t)&I2C_TDATA_GD(i2c_periph);
        dma_direction = is_read ? DMA_PERIPH_TO_MEMORY : DMA_MEMORY_TO_PERIPH;
        dma_mode = is_read ? I2C_DMA_RECEIVE_GD : I2C_DMA_TRANSMIT_GD;
        /* Use the (possibly aligned) DMA buffer pointer */
        p_current = dma_buf_ptr;
    }

    /* Only first frame needs to wait for bus idle */
    uint8_t need_bus_idle_wait = (mode == GD32_I2C_FIRST_FRAME ||
                                   mode == GD32_I2C_FIRST_AND_LAST_FRAME ||
                                   mode == GD32_I2C_FIRST_FRAME_RELOAD);
    /* Send START unless NO_START flag */
    uint8_t need_start = !(msg->flags & RT_I2C_NO_START) &&
                          (mode != GD32_I2C_NEXT_FRAME_NO_START);
    uint8_t need_autoend = (mode == GD32_I2C_LAST_FRAME ||
                             mode == GD32_I2C_FIRST_AND_LAST_FRAME);
    /* Use RELOAD mode when next msg continues without START */
    uint8_t use_reload_for_next = (mode == GD32_I2C_FIRST_FRAME_RELOAD ||
                                    mode == GD32_I2C_NEXT_FRAME_RELOAD);
    /* Check if continuing from RELOAD */
    uint8_t continuing_from_reload = (msg->flags & RT_I2C_NO_START) != 0;

    /* Only configure address for new transfers, not when continuing from RELOAD */
    if(!continuing_from_reload)
    {
        i2c_master_addressing_gd(i2c_periph, shifted_addr, i2c_direction);
    }

    /* Wait for bus idle if starting new transfer */
    if(need_bus_idle_wait)
    {
        if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_I2CBSY_GD, RT_FALSE, RT_NULL) != 0)
        {
            LOG_E("i2c %s bus busy timeout", dir_str);
            goto error_exit;
        }
    }

    while(remaining > 0)
    {
        uint8_t is_last_chunk = (remaining <= MAX_RELOAD_SIZE);
        nbytes = is_last_chunk ? remaining : MAX_RELOAD_SIZE;

        if(use_dma)
        {
            /* Configure DMA channel */
            gd32_i2c_dma_config_channel(dma, data_reg, p_current, nbytes, dma_direction);
            i2c_dma_enable_gd(i2c_periph, dma_mode);
            dma_channel_enable(dma->periph, dma->channel);
        }

        /* Configure NBYTES + RELOAD + AUTOEND atomically */
        uint8_t set_reload = !is_last_chunk || use_reload_for_next;
        uint8_t set_autoend = is_last_chunk && need_autoend;
    #if defined GD32_I2C_HAS_NEW_IP
        i2c_nbytes_reload_autoend_config_gd(i2c_periph, nbytes, set_reload, set_autoend);
    #endif

        /* Send START only for first chunk when needed */
        if(need_start && p_current == dma_buf_ptr)
        {
            i2c_start_on_bus_gd(i2c_periph);
        }

        if(use_dma)
        {
            /* Wait for DMA FTF */
            if(gd32_timeout_wait_flag(i2c_periph, DMA_FLAG_FTF, RT_TRUE, dma) != 0)
            {
                LOG_E("i2c %s dma timeout", dir_str);
                goto error_exit_dma;
            }
            dma_flag_clear(dma->periph, dma->channel, DMA_FLAG_FTF);
            dma_channel_disable(dma->periph, dma->channel);

            p_current += nbytes;
            remaining -= nbytes;
        }
        else
        {
            /* Polling data transfer */
            if(is_read)
            {
                while(nbytes > 0)
                {
                    if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_RBNE_GD, RT_TRUE, RT_NULL) != 0)
                    {
                        LOG_E("i2c rx RBNE timeout");
                        goto error_exit;
                    }
                    *p_current++ = i2c_data_receive_gd(i2c_periph);
                    nbytes--;
                    remaining--;
                }
            }
            else
            {
                while(nbytes > 0)
                {
                    if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_TI_GD, RT_TRUE, RT_NULL) != 0)
                    {
                        LOG_E("i2c tx TI timeout");
                        goto error_exit;
                    }
                    i2c_data_transmit_gd(i2c_periph, *p_current++);
                    nbytes--;
                    remaining--;
                }
            }
        }

        /* If more data in this msg, wait for TCR before next chunk */
        if(remaining > 0)
        {
            if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_TCR_GD, RT_TRUE, RT_NULL) != 0)
            {
                LOG_E("i2c %s TCR timeout", dir_str);
                goto error_exit;
            }
        }
    }

    /* Wait for completion based on mode */
    if(need_autoend)
    {
        if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_STPDET_GD, RT_TRUE, RT_NULL) != 0)
        {
            LOG_E("i2c %s STOP timeout", dir_str);
            goto error_exit;
        }
        i2c_flag_clear_gd(i2c_periph, I2C_FLAG_STPDET_GD);
    }
    else if(use_reload_for_next)
    {
        if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_TCR_GD, RT_TRUE, RT_NULL) != 0)
        {
            LOG_E("i2c %s TCR timeout (reload)", dir_str);
            goto error_exit;
        }
    }
    else
    {
        if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_TC_GD, RT_TRUE, RT_NULL) != 0)
        {
            LOG_E("i2c %s TC timeout", dir_str);
            goto error_exit;
        }
    }

    if(use_dma)
    {
        i2c_dma_disable_gd(i2c_periph, dma_mode);
    }

#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
#ifdef RT_USING_CACHE
    /* D-Cache coherency: for RX, invalidate and copy back if needed */
    if (use_dma && is_read && msg->len > 0)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)dma_buf_ptr, aligned_size);
        if (dma_aligned_buf != RT_NULL)
        {
            rt_memcpy(msg->buf, dma_buf_ptr, msg->len);
        }
    }
    /* Free aligned temporary buffer */
    if (dma_aligned_buf != RT_NULL)
    {
        rt_free_align(dma_aligned_buf);
    }
#endif
#endif /* cache-sensitive DMA path */

    return 0;

error_exit_dma:
    dma_channel_disable(dma->periph, dma->channel);
    i2c_dma_disable_gd(i2c_periph, dma_mode);
error_exit:
    i2c_stop_on_bus_gd(i2c_periph);
#if defined(SOC_SERIES_GD32H7xx) || defined(SOC_SERIES_GD32H75E) || defined(SOC_SERIES_GD32H77x)
#ifdef RT_USING_CACHE
    if (dma_aligned_buf != RT_NULL)
    {
        rt_free_align(dma_aligned_buf);
    }
#endif
#endif
    return -RT_ETIMEOUT;
}
#endif /* BSP_USING_I2C_*_DMA */
#endif /* GD32_I2C_HAS_NEW_IP */

#ifdef GD32_I2C_HAS_LEGACY_IP
#ifdef BSP_USING_I2C_TX_DMA
/**
  * @brief  legacy I2C TX DMA transfer.
  * @param  i2c_bus
  * @param  msg
  * @retval 0 on success, non-zero on error
  */
static int gd32_i2c_legacy_dma_write(const struct gd32_i2c_bus *i2c_bus, const struct rt_i2c_msg *msg)
{
    uint32_t i2c_periph = i2c_bus->i2c_periph;
    struct dma_config *dma_tx = i2c_bus->dma_tx;
    int result;

    /* Configure DMA channel and enable I2C DMA
     * Official order: I2C DMA enable -> DMA channel enable */
    gd32_i2c_dma_config_channel(dma_tx, (uint32_t)&I2C_DATA(i2c_periph),
                                 msg->buf, msg->len, DMA_MEMORY_TO_PERIPH);
    i2c_dma_config(i2c_periph, I2C_DMA_ON);
    dma_channel_enable(dma_tx->periph, dma_tx->channel);

    /* Wait for DMA completion */
    result = gd32_timeout_wait_flag(i2c_periph, DMA_FLAG_FTF, RT_TRUE, dma_tx);
    dma_channel_disable(dma_tx->periph, dma_tx->channel);
    dma_flag_clear(dma_tx->periph, dma_tx->channel, DMA_FLAG_FTF);
    if(result != 0)
    {
        i2c_dma_config(i2c_periph, I2C_DMA_OFF);
        return result;
    }

    /* Wait for I2C BTC (Byte Transfer Complete) */
    if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_BTC, RT_TRUE, RT_NULL) != 0)
    {
        i2c_dma_config(i2c_periph, I2C_DMA_OFF);
        return -RT_ETIMEOUT;
    }

    /* Disable I2C DMA */
    i2c_dma_config(i2c_periph, I2C_DMA_OFF);

    return 0;
}
#endif /* BSP_USING_I2C_TX_DMA */
#endif /* GD32_I2C_HAS_LEGACY_IP */

#ifdef GD32_I2C_HAS_LEGACY_IP
#ifdef BSP_USING_I2C_RX_DMA
/**
  * @brief  legacy I2C RX DMA transfer.
  * @param  i2c_bus
  * @param  msg
  * @retval 0 on success, non-zero on error
  */
static int gd32_i2c_legacy_dma_read(const struct gd32_i2c_bus *i2c_bus, const struct rt_i2c_msg *msg)
{
    uint32_t i2c_periph = i2c_bus->i2c_periph;
    struct dma_config *dma_rx = i2c_bus->dma_rx;
    int result;

    /* Official style: clear ADDSEND first, then configure DMA */
    i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);

    /* Configure DMA channel */
    gd32_i2c_dma_config_channel(dma_rx, (uint32_t)&I2C_DATA(i2c_periph),
                                 msg->buf, msg->len, DMA_PERIPH_TO_MEMORY);
    i2c_dma_last_transfer_config(i2c_periph, I2C_DMALST_ON);
    i2c_dma_config(i2c_periph, I2C_DMA_ON);
    dma_channel_enable(dma_rx->periph, dma_rx->channel);

    /* Wait for DMA completion */
    result = gd32_timeout_wait_flag(i2c_periph, DMA_FLAG_FTF, RT_TRUE, dma_rx);
    dma_channel_disable(dma_rx->periph, dma_rx->channel);
    dma_flag_clear(dma_rx->periph, dma_rx->channel, DMA_FLAG_FTF);

    /* Send STOP */
    i2c_stop_on_bus(i2c_periph);

    /* Cleanup */
    i2c_dma_last_transfer_config(i2c_periph, I2C_DMALST_OFF);
    i2c_dma_config(i2c_periph, I2C_DMA_OFF);

    return result;
}
#endif /* BSP_USING_I2C_RX_DMA */
#endif /* GD32_I2C_HAS_LEGACY_IP */


#if !defined(SOC_SERIES_GD32H75E) && !defined(SOC_SERIES_GD32E51x) && !defined(SOC_SERIES_GD32F3x0) \
 && !defined(SOC_SERIES_GD32F50x) && !defined(SOC_SERIES_GD32G5x3) && !defined(SOC_SERIES_GD32C11x) \
 && !defined(SOC_SERIES_GD32L23x) && !defined(SOC_SERIES_GD32E23x) && !defined(SOC_SERIES_GD32E11x) \
 && !defined(SOC_SERIES_GD32H77x) && !defined(SOC_SERIES_GD32M53x) && !defined(SOC_SERIES_GD32H7xx) \
 && !defined(SOC_SERIES_GD32F5xx) && !defined(SOC_SERIES_GD32F30x)
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
#else
#warning "gd32_i2c_gpio_init should be defined in board_msd_init.c"
rt_weak void gd32_i2c_gpio_init(const struct gd32_i2c_bus *i2c)
{
}
#endif

/**
  * @brief  read data.
  * @param  i2c_periph
  * @param  *p_buffer
  * @param  data_byte
  * @retval 0 on success, -RT_ETIMEOUT on timeout
  */
static int8_t gd32_i2c_read(rt_uint32_t i2c_periph, rt_uint8_t *p_buffer, rt_uint16_t data_byte)
{
    if (data_byte == 0) return 1;
    /* while there is data to be read */

    while(data_byte)
    {
#ifdef GD32_I2C_HAS_LEGACY_IP
        if(IS_I2C_LEGACY(i2c_periph))
        {
            if(3 == data_byte)
            {
                /* wait until BTC bit is set */
                if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_BTC, RT_TRUE, RT_NULL) != 0)
                    return -RT_ETIMEOUT;
                /* disable acknowledge */
                i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
            }

            if(2 == data_byte)
            {
                /* wait until BTC bit is set */
                if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_BTC, RT_TRUE, RT_NULL) != 0)
                    return -RT_ETIMEOUT;
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
            if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_RBNE_GD, RT_TRUE, RT_NULL) != 0)
                return -RT_ETIMEOUT;

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
  * @retval 0 on success, -RT_ETIMEOUT on timeout
  */
static int8_t gd32_i2c_write(rt_uint32_t i2c_periph, uint8_t *p_buffer, uint16_t data_byte)
{
    if (data_byte == 0) return 1;

    while(data_byte)
    {
#ifdef GD32_I2C_HAS_LEGACY_IP
        if(IS_I2C_LEGACY(i2c_periph))
        {
            /* data transmission */
            i2c_data_transmit(i2c_periph, *p_buffer);
            /* point to the next byte to be written */
            p_buffer++;
            /* decrement the write bytes counter */
            data_byte--;
            /* wait until BTC bit is set */
            if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_BTC, RT_TRUE, RT_NULL) != 0)
                return -RT_ETIMEOUT;
        }
        else
#endif
        {
#ifdef GD32_I2C_HAS_NEW_IP
            /* wait until the transmit data buffer is empty */
            if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_TBE, RT_TRUE, RT_NULL) != 0)
                return -RT_ETIMEOUT;

            while(data_byte)
            {
                /* wait until the TI bit is set */
                if(gd32_timeout_wait_flag(i2c_periph, I2C_FLAG_TI_GD, RT_TRUE, RT_NULL) != 0)
                    return -RT_ETIMEOUT;
                /* data transmission */
                i2c_data_transmit_gd(i2c_periph, *p_buffer);
                /* point to the next byte to be written */
                p_buffer++;
                /* decrement the write bytes counter */
                data_byte--;
            }
#endif
        }
    }
    return 0;
}

#ifdef GD32_I2C_HAS_LEGACY_IP
#if defined(BSP_USING_I2C_TX_DMA) || defined(BSP_USING_I2C_RX_DMA)
static rt_ssize_t gd32_i2c_legacy_dma_xfer(struct gd32_i2c_bus *gd32_i2c,
                                           struct rt_i2c_msg msgs[],
                                           rt_uint32_t num)
{
    struct rt_i2c_msg *msg = RT_NULL;
    rt_uint16_t addr;
    rt_uint32_t i;
    rt_err_t ret = RT_ERROR;

    for(i = 0; i < num; i++)
    {
        msg = &msgs[i];
        addr = msg->addr << 1;

        if(!(msg->flags & RT_I2C_NO_START))
        {
            if(msg->flags & RT_I2C_RD)
            {
                i2c_ack_config(gd32_i2c->i2c_periph, I2C_ACK_ENABLE);
                if(msg->len == 2U)
                {
                    i2c_ackpos_config(gd32_i2c->i2c_periph, I2C_ACKPOS_NEXT);
                }

                i2c_start_on_bus(gd32_i2c->i2c_periph);
                if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_SBSEND, RT_TRUE, RT_NULL) != 0)
                {
                    ret = -RT_ERROR;
                    break;
                }

                i2c_master_addressing(gd32_i2c->i2c_periph, addr, I2C_RECEIVER);
                if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND, RT_TRUE, RT_NULL) != 0)
                {
                    ret = -RT_ERROR;
                    break;
                }

#ifdef BSP_USING_I2C_RX_DMA
                if(!(msg->len >= I2C_DMA_TRANS_MIN_LEN && msg->len >= 2 && gd32_i2c->dma_rx != RT_NULL))
#endif
                {
                    if(msg->len <= 2)
                    {
                        i2c_ack_config(gd32_i2c->i2c_periph, I2C_ACK_DISABLE);
                    }
                    i2c_flag_clear(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND);
                    if(msg->len == 1)
                    {
                        i2c_stop_on_bus(gd32_i2c->i2c_periph);
                    }
                }
            }
            else
            {
                if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_I2CBSY, RT_FALSE, RT_NULL) != 0)
                {
                    ret = -RT_ERROR;
                    break;
                }

                i2c_start_on_bus(gd32_i2c->i2c_periph);
                if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_SBSEND, RT_TRUE, RT_NULL) != 0)
                {
                    ret = -RT_ERROR;
                    break;
                }

                i2c_master_addressing(gd32_i2c->i2c_periph, addr, I2C_TRANSMITTER);
                if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND, RT_TRUE, RT_NULL) != 0)
                {
                    ret = -RT_ERROR;
                    break;
                }

                i2c_flag_clear(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND);
            }
        }

        if(msg->flags & RT_I2C_RD)
        {
#ifdef BSP_USING_I2C_RX_DMA
            if(msg->len >= I2C_DMA_TRANS_MIN_LEN && msg->len >= 2 && gd32_i2c->dma_rx != RT_NULL)
            {
                if(gd32_i2c_legacy_dma_read(gd32_i2c, msg) != 0)
                {
                    LOG_E("i2c bus dma read failed!");
                    ret = -RT_ERROR;
                    break;
                }
            }
            else
#endif
            {
                if(gd32_i2c_read(gd32_i2c->i2c_periph, msg->buf, msg->len) != 0)
                {
                    LOG_E("i2c bus read failed,i2c bus stop!");
                    ret = -RT_ERROR;
                    break;
                }
            }
        }
        else
        {
#ifdef BSP_USING_I2C_TX_DMA
            if(msg->len >= I2C_DMA_TRANS_MIN_LEN && gd32_i2c->dma_tx != RT_NULL)
            {
                if(gd32_i2c_legacy_dma_write(gd32_i2c, msg) != 0)
                {
                    LOG_E("i2c bus dma write failed,i2c bus stop!");
                    ret = -RT_ERROR;
                    break;
                }
            }
            else
#endif
            {
                if(gd32_i2c_write(gd32_i2c->i2c_periph, msg->buf, msg->len) != 0)
                {
                    LOG_E("i2c bus write failed,i2c bus stop!");
                    ret = -RT_ERROR;
                    break;
                }
            }
        }
    }

    if((ret == RT_ERROR) && (i == num))
    {
        ret = i;
    }

    if((msg != RT_NULL) && !(msg->flags & RT_I2C_NO_STOP))
    {
        int wait_result;

        if(msg->flags & RT_I2C_RD)
        {
            wait_result = gd32_timeout_wait_flag(gd32_i2c->i2c_periph,
                                                 I2C_CTL0_STOP,
                                                 RT_FALSE,
                                                 RT_NULL);
        }
        else
        {
            i2c_stop_on_bus(gd32_i2c->i2c_periph);
            wait_result = gd32_timeout_wait_flag(gd32_i2c->i2c_periph,
                                                 I2C_CTL0_STOP,
                                                 RT_FALSE,
                                                 RT_NULL);
        }

        if(wait_result != RT_EOK)
        {
            ret = wait_result;
        }
    }

    return ret;
}
#endif
#endif

#ifdef GD32_I2C_HAS_NEW_IP
#if defined(BSP_USING_I2C_TX_DMA) || defined(BSP_USING_I2C_RX_DMA)
static rt_ssize_t gd32_i2c_new_dma_xfer(struct gd32_i2c_bus *gd32_i2c,
                                        struct rt_i2c_msg msgs[],
                                        rt_uint32_t num)
{
    rt_uint32_t i;

    for(i = 0; i < num; i++)
    {
        struct rt_i2c_msg *msg = &msgs[i];
        struct rt_i2c_msg *next_msg = (i < num - 1) ? &msgs[i + 1] : RT_NULL;
        uint32_t frame_mode = gd32_i2c_new_frame_mode(msg, next_msg, i, num);
        uint8_t is_read = (msg->flags & RT_I2C_RD) != 0;
        struct dma_config *dma = is_read ? gd32_i2c->dma_rx : gd32_i2c->dma_tx;
        uint8_t use_dma = (msg->len >= I2C_DMA_TRANS_MIN_LEN && dma != RT_NULL);

        if(gd32_i2c_new_msg_xfer(gd32_i2c, msg, frame_mode, is_read, use_dma) != 0)
        {
            i2c_flag_clear_gd(gd32_i2c->i2c_periph, I2C_FLAG_STPDET_GD);
            return -RT_ERROR;
        }
    }

    return i;
}
#endif
#endif

/**
  * @brief
  * @param
  * @param
  * @param
  * @retval
  */

static rt_ssize_t gd32_i2c_master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg = RT_NULL;
    struct gd32_i2c_bus *gd32_i2c = (struct gd32_i2c_bus *)bus->priv;
    rt_uint16_t addr;
    rt_uint32_t i, w_total_byte=0, r_total_byte=0;
    rt_err_t ret = RT_ERROR;

    RT_ASSERT(bus != RT_NULL);

#if defined(BSP_USING_I2C_TX_DMA) || defined(BSP_USING_I2C_RX_DMA)
#ifdef GD32_I2C_HAS_LEGACY_IP
    if(IS_I2C_LEGACY(gd32_i2c->i2c_periph))
    {
        return gd32_i2c_legacy_dma_xfer(gd32_i2c, msgs, num);
    }
#endif

#ifdef GD32_I2C_HAS_NEW_IP
    return gd32_i2c_new_dma_xfer(gd32_i2c, msgs, num);
#endif
#endif

    for(i = 0; i < num; i++)
    {
        msg = &msgs[i];

        /* Calculate total bytes for New IP non-DMA path: only on first iteration */
        if(i == 0)
        {
            for(rt_uint32_t j = 0; j < num; j++)
            {
                if(msgs[j].flags & RT_I2C_RD)
                    r_total_byte += msgs[j].len;
                else
                    w_total_byte += msgs[j].len;
            }
        }

        /* Legacy IP + New IP non-DMA path */
        addr = msg->addr << 1;
        if(!(msg->flags & RT_I2C_NO_START))
        {
    #ifdef GD32_I2C_HAS_LEGACY_IP
            if(IS_I2C_LEGACY(gd32_i2c->i2c_periph))
            {
                if(msg->flags & RT_I2C_RD)
                {
                        /* enable acknowledge */
                    i2c_ack_config(gd32_i2c->i2c_periph, I2C_ACK_ENABLE);
                    if(msg->len == 2U)
                    {
                        /* Configure ACK position for 2-byte read */
                        i2c_ackpos_config(gd32_i2c->i2c_periph, I2C_ACKPOS_NEXT);
                    }
                    /* send the start signal */
                    i2c_start_on_bus(gd32_i2c->i2c_periph);
                    /* i2c master sends START signal successfully */
                    if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_SBSEND, RT_TRUE, RT_NULL) != 0)
                    {
                        ret = -RT_ERROR;
                        break;
                    }

                    i2c_master_addressing(gd32_i2c->i2c_periph, addr, I2C_RECEIVER);

                    if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND, RT_TRUE, RT_NULL) != 0)
                    {
                        ret = -RT_ERROR;
                        break;
                    }

                    /* Polling read: original flow */
                    /* address flag set means i2c slave sends ACK */
                    if(msg->len <= 2)
                    {
                        i2c_ack_config(gd32_i2c->i2c_periph, I2C_ACK_DISABLE);
                    }
                    i2c_flag_clear(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND);
                    if(msg->len == 1)
                    {
                        i2c_stop_on_bus(gd32_i2c->i2c_periph);
                    }

                }
                else
                {
                    /* configure slave address */
                    if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_I2CBSY, RT_FALSE, RT_NULL) != 0)
                    {
                        ret = -RT_ERROR;
                        break;
                    }
                    //i2c_transfer_byte_number_config(gd32_i2c->i2c_periph, w_total_byte);
                    /* send a start condition to I2C bus */
                    i2c_start_on_bus(gd32_i2c->i2c_periph);
                    if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_SBSEND, RT_TRUE, RT_NULL) != 0)
                    {
                        ret = -RT_ERROR;
                        break;
                    }

                    i2c_master_addressing(gd32_i2c->i2c_periph, addr, I2C_TRANSMITTER);
                    if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND, RT_TRUE, RT_NULL) != 0)
                    {
                        ret = -RT_ERROR;
                        break;
                    }

                    i2c_flag_clear(gd32_i2c->i2c_periph, I2C_FLAG_ADDSEND);
                }
            }
            else
#endif
            {
#ifdef GD32_I2C_HAS_NEW_IP
                if(msg->flags & RT_I2C_ADDR_10BIT)
                {
                    /* enable 10-bit addressing mode in master mode */
                    i2c_address10_enable_gd(gd32_i2c->i2c_periph);
                }
                else
                {
                    /* disable 10-bit addressing mode in master mode */
                    i2c_address10_disable_gd(gd32_i2c->i2c_periph);
                }

                if(msg->flags & RT_I2C_RD)
                {
                    /* configure slave address */
                    i2c_master_addressing_gd(gd32_i2c->i2c_periph, addr, I2C_MASTER_RECEIVE_GD);

                    i2c_transfer_byte_number_config_gd(gd32_i2c->i2c_periph, r_total_byte);
                    /* send a start condition to I2C bus */
                    i2c_start_on_bus_gd(gd32_i2c->i2c_periph);
                }
                else
                {
                    /* configure slave address */
                    i2c_master_addressing_gd(gd32_i2c->i2c_periph, addr, I2C_MASTER_TRANSMIT_GD);
                    if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_I2CBSY_GD, RT_FALSE, RT_NULL) != 0)
                    {
                        ret = -RT_ERROR;
                        break;
                    }
                    i2c_transfer_byte_number_config_gd(gd32_i2c->i2c_periph, w_total_byte);
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
                ret = -RT_ERROR;
                break;
            }
        }
        else
        {
            if(gd32_i2c_write(gd32_i2c->i2c_periph, msg->buf, msg->len) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!");
                ret = -RT_ERROR;
                break;
            }
        }

#ifdef GD32_I2C_HAS_NEW_IP
        if(!IS_I2C_LEGACY(gd32_i2c->i2c_periph))
        {
            if(r_total_byte != 0)
            {
                if(gd32_timeout_wait_flag(gd32_i2c->i2c_periph, I2C_FLAG_TC_GD, RT_TRUE, RT_NULL) != 0)
                {
                    ret = -RT_ERROR;
                    break;
                }
            }
        }
#endif
    }

    if((ret == RT_ERROR) && (i == num))
    {
        ret = i;
    }

#ifdef GD32_I2C_HAS_LEGACY_IP
    if(IS_I2C_LEGACY(gd32_i2c->i2c_periph))
    {
        if((msg != RT_NULL) && !(msg->flags & RT_I2C_NO_STOP))
        {
            if(msg->flags & RT_I2C_RD)
            {
                int wait_result = gd32_timeout_wait_flag(gd32_i2c->i2c_periph,
                                                         I2C_CTL0_STOP,
                                                         RT_FALSE,
                                                         RT_NULL);

                if(wait_result != RT_EOK)
                {
                    ret = wait_result;
                }
            }
            else
            {
                /* send a stop condition to I2C bus */
                i2c_stop_on_bus(gd32_i2c->i2c_periph);
                /* wait until stop condition generate */
                int wait_result = gd32_timeout_wait_flag(gd32_i2c->i2c_periph,
                                                         I2C_CTL0_STOP,
                                                         RT_FALSE,
                                                         RT_NULL);

                if(wait_result != RT_EOK)
                {
                    ret = wait_result;
                }
            }
        }
    }
    else
#endif
    {
#ifdef GD32_I2C_HAS_NEW_IP
        if((msg != RT_NULL) && !(msg->flags & RT_I2C_NO_STOP))
        {
            int wait_result = gd32_timeout_wait_flag(gd32_i2c->i2c_periph,
                                                     I2C_FLAG_TC_GD,
                                                     RT_TRUE,
                                                     RT_NULL);

            if(wait_result != RT_EOK)
            {
                ret = wait_result;
            }
            else
            {
                /* send a stop condition to I2C bus */
                i2c_stop_on_bus_gd(gd32_i2c->i2c_periph);
                /* wait until stop condition generate */
                wait_result = gd32_timeout_wait_flag(gd32_i2c->i2c_periph,
                                                     I2C_FLAG_STPDET_GD,
                                                     RT_TRUE,
                                                     RT_NULL);
                if(wait_result != RT_EOK)
                {
                    ret = wait_result;
                }
                else
                {
                    /* clear the STPDET bit */
                    i2c_flag_clear_gd(gd32_i2c->i2c_periph, I2C_FLAG_STPDET_GD);
                }
            }
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
    int i;

    for(i = 0; i < obj_num; i++)
    {

        gd32_i2c_gpio_init(&gd_i2c_config[i]);

        /* configure I2C timing. I2C speed clock=400kHz*/
#ifdef GD32_I2C_HAS_LEGACY_IP
        if(IS_I2C_LEGACY(gd_i2c_config[i].i2c_periph))
        {

            i2c_clock_config(gd_i2c_config[i].i2c_periph, 100000, I2C_DTCY_2);
            i2c_mode_addr_config(gd_i2c_config[i].i2c_periph, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, 0xa0);
            i2c_enable(gd_i2c_config[i].i2c_periph);
            i2c_ack_config(gd_i2c_config[i].i2c_periph, I2C_ACK_ENABLE);
        }else
#endif
        {
#ifdef GD32_I2C_HAS_NEW_IP

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
