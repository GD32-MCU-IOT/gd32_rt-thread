/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-03-27     RT-Thread    first implementation for GD32H7xx OSPI HyperBus PSRAM (GSR6W28AM)
 */
#include "drv_ospi.h"


#if defined(BSP_USING_OSPI)
#define LOG_TAG              "drv.ospi"

#include <rtdbg.h>

/* page size for buffer write (bytes) */
#define PSRAM_PAGE_SIZE        1024U

/* PLL1R configuration for OSPI 400MHz clock source */
/* PLL1R = HSE(25MHz) / PLL1PSC(5) * PLL1N(80) / PLL1R(1) = 400 MHz */
#define OSPI_PLL1PSC_REG_OFFSET    0U
#define OSPI_PLL1N_REG_OFFSET      6U
#define OSPI_PLL1P_REG_OFFSET      16U
#define OSPI_PLL1Q_REG_OFFSET      8U
#define OSPI_PLL1R_REG_OFFSET      24U
#define OSPI_PLL1PSC               5U
#define OSPI_PLL1N                 (80U - 1U)
#define OSPI_PLL1P                 (1U - 1U)
#define OSPI_PLL1Q                 (2U - 1U)
#define OSPI_PLL1R_DIV             (1U - 1U)

/* OSPI transmit/receive delay chain parameters */
#define OSPI_TCK_DELAY_CHAIN_VAL   6U
#define OSPI_RCK_DELAY_CHAIN_VAL   0x0AU

static struct gd32_ospi_dev gd32_ospi0_dev;

static struct gd32_ospi ospi0_drv = {
    .ospi_periph = OSPI0,
    .device_name = "ospi0",
    .ospi_clk    = RCU_OSPI0,
    .mapped_addr = OSPI0_MAPPED_ADDR,
};

/*!
    \brief      configure PLL1R to 400MHz for OSPI clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void _ospi_pll1r_400m_set(void)
{
    /* configure PLL1 = 400MHz */
    /* PLL select HXTAL, config PLL1 input and output range */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL1VCOSEL | RCU_PLLALL_PLL1RNG);
    RCU_PLLALL |= (RCU_PLLSRC_HXTAL | RCU_PLL1RNG_4M_8M);

    /* PLL1R = HSE(25MHz) / 5 * 80 / 1 = 400 MHz */
    RCU_PLL1 &= ~(RCU_PLL1_PLL1N | RCU_PLL1_PLL1PSC | RCU_PLL1_PLL1P | RCU_PLL1_PLL1R);
    RCU_PLL1 |= ((OSPI_PLL1N << OSPI_PLL1N_REG_OFFSET) |
                 (OSPI_PLL1PSC << OSPI_PLL1PSC_REG_OFFSET) |
                 (OSPI_PLL1P << OSPI_PLL1P_REG_OFFSET) |
                 (OSPI_PLL1R_DIV << OSPI_PLL1R_REG_OFFSET));
    RCU_PLLADDCTL &= ~(RCU_PLLADDCTL_PLL1Q);
    RCU_PLLADDCTL |= (OSPI_PLL1Q << OSPI_PLL1Q_REG_OFFSET);

    /* enable PLL1P, PLL1Q, PLL1R */
    RCU_PLLADDCTL |= RCU_PLLADDCTL_PLL1PEN | RCU_PLLADDCTL_PLL1QEN | RCU_PLLADDCTL_PLL1REN;

    /* enable PLL1 */
    RCU_CTL |= RCU_CTL_PLL1EN;

    /* wait until PLL1 is stable */
    while (0U == (RCU_CTL & RCU_CTL_PLL1STB))
    {
    }
}

/*!
    \brief      configure OSPI delay chain and DQS timing after OSPI is enabled
    \param[in]  ospi_periph: OSPIx(x=0,1)
    \param[out] none
    \retval     none
*/
static void _ospi_delay_chain_config(uint32_t ospi_periph)
{
    /* enable DQS receive clock add 1 cycle mode */
    ospi_dqs_rck_add_enable(ospi_periph);
    /* configure and enable transmit clock delay chain */
    ospi_tck_delay_chain_config(ospi_periph, OSPI_TCK_DELAY_CHAIN_VAL);
    ospi_tck_delay_chain_enable(ospi_periph);
    /* enable receive delay block and configure receive clock delay chain */
    ospi_receive_delay_block_enable(ospi_periph);
    ospi_rck_delay_chain_config(ospi_periph, OSPI_RCK_DELAY_CHAIN_VAL);
    ospi_receive_sck_delay_chain_select(ospi_periph);
}

static void _ospi_psram_hw_init(struct gd32_ospi *drv, ospi_parameter_struct *ospi_struct)
{
    ospi_hyperbus_cfg_struct hyperbus_struct;

    /* configure PLL1R 400MHz and select as OSPI clock source */
    _ospi_pll1r_400m_set();
    rcu_ospi_clock_config(RCU_OSPI_PLL1R);

    /* reset the OSPI and OSPIM peripheral */
    ospi_deinit(drv->ospi_periph);
    ospim_deinit();

    gd32_ospi_gpio_init(drv);

    /* initialize the parameters of OSPI struct */
    ospi_struct_init(ospi_struct);

    ospi_struct->prescaler        = 1U;
    ospi_struct->sample_shift     = OSPI_SAMPLE_SHIFTING_NONE;
    ospi_struct->fifo_threshold   = OSPI_FIFO_THRESHOLD_5;
    ospi_struct->dual_quad        = OSPI_DUAL_QUAD_MODE_DISABLE;
    ospi_struct->device_size      = OSPI_MESZ_512_MBS;
    ospi_struct->free_clock_run   = OSPI_CLOCK_FREE_RUN_DISABLE;
    ospi_struct->cs_hightime      = OSPI_CS_HIGH_TIME_3_CYCLE;
    ospi_struct->memory_type      = OSPI_HYPERBUS_MEMORY_MODE;
    ospi_struct->delay_hold_cycle = OSPI_DELAY_HOLD_QUARTER_CYCLE;
    ospi_struct->refrate          = 200U;

    /* initialize OSPI parameter */
    ospi_init(drv->ospi_periph, ospi_struct);

    /* configure HyperBus protocol parameters */
    hyperbus_struct.rw_recovery_time   = 40U;
    hyperbus_struct.access_time        = 7U;
    hyperbus_struct.write_zero_latency = OSPI_WRITE_ZERO_LATENCY_DISABLE;
    hyperbus_struct.latency_mode       = OSPI_VAR_INIT_LATENCY;
    ospi_hyperbus_config(drv->ospi_periph, &hyperbus_struct);

    /* enable OSPI */
    ospi_enable(drv->ospi_periph);

    /* configure delay chain and DQS timing */
    _ospi_delay_chain_config(drv->ospi_periph);
}

/*!
    \brief      read GSR6W28AM mode register via HyperBus register space
    \param[in]  drv: pointer to OSPI driver structure
    \param[in]  ospi_struct: pointer to OSPI parameter structure
    \param[in]  value: pointer to store register value
    \param[in]  addr: register address
    \param[out] none
    \retval     none
*/
static void _ospi_psram_read_register(struct gd32_ospi *drv, ospi_parameter_struct *ospi_struct,
                                      uint16_t *value, uint32_t addr)
{
    ospi_hyperbus_cmd_struct hyper_cmd_struct;

    hyper_cmd_struct.addr_space = OSPI_REGISTER_ADDRESS_SPACE;
    hyper_cmd_struct.addr_size  = OSPI_ADDRESS_32_BITS;
    hyper_cmd_struct.address    = addr;
    hyper_cmd_struct.dqs_mode   = OSPI_DQS_ENABLE;
    hyper_cmd_struct.nbdata     = 2U;

    ospi_hyperbus_cmd_config(drv->ospi_periph, ospi_struct, &hyper_cmd_struct);
    ospi_receive(drv->ospi_periph, ospi_struct, (uint8_t *)value);
}

/*!
    \brief      write GSR6W28AM mode register via HyperBus register space
    \param[in]  drv: pointer to OSPI driver structure
    \param[in]  ospi_struct: pointer to OSPI parameter structure
    \param[in]  value: pointer to register value to write
    \param[in]  addr: register address
    \param[in]  latency_mode: OSPI_VAR_INIT_LATENCY or OSPI_FIXED_LATENCY
    \param[in]  initial_latency: access time value
    \param[out] none
    \retval     none
*/
static void _ospi_psram_write_register(struct gd32_ospi *drv, ospi_parameter_struct *ospi_struct,
                                       uint16_t *value, uint32_t addr,
                                       uint32_t latency_mode, uint32_t initial_latency)
{
    ospi_hyperbus_cfg_struct hyper_cfg_struct;
    ospi_hyperbus_cmd_struct hyper_cmd_struct;

    /* configure write latency */
    hyper_cfg_struct.rw_recovery_time   = 40U;
    hyper_cfg_struct.access_time        = initial_latency;
    hyper_cfg_struct.write_zero_latency = OSPI_WRITE_ZERO_LATENCY_ENABLE;
    hyper_cfg_struct.latency_mode       = latency_mode;
    ospi_hyperbus_config(drv->ospi_periph, &hyper_cfg_struct);

    hyper_cmd_struct.addr_space = OSPI_REGISTER_ADDRESS_SPACE;
    hyper_cmd_struct.addr_size  = OSPI_ADDRESS_32_BITS;
    hyper_cmd_struct.address    = addr;
    hyper_cmd_struct.dqs_mode   = OSPI_DQS_ENABLE;
    hyper_cmd_struct.nbdata     = 2U;

    ospi_hyperbus_cmd_config(drv->ospi_periph, ospi_struct, &hyper_cmd_struct);
    ospi_transmit(drv->ospi_periph, (uint8_t *)value);

    /* restore write zero latency to disabled */
    hyper_cfg_struct.write_zero_latency = OSPI_WRITE_ZERO_LATENCY_DISABLE;
    ospi_hyperbus_config(drv->ospi_periph, &hyper_cfg_struct);
}

/*!
    \brief      read data from GSR6W28AM PSRAM via HyperBus memory space
    \param[in]  drv: pointer to OSPI driver structure
    \param[in]  ospi_struct: pointer to OSPI parameter structure
    \param[in]  pdata: pointer to buffer to store read data
    \param[in]  addr: PSRAM address to read from
    \param[in]  size: number of bytes to read
    \param[out] none
    \retval     none
*/
static void _ospi_psram_read(struct gd32_ospi *drv, ospi_parameter_struct *ospi_struct,
                             uint8_t *pdata, uint32_t addr, uint32_t size)
{
    ospi_hyperbus_cmd_struct hyper_cmd_struct;

    hyper_cmd_struct.addr_space = OSPI_MEMORY_ADDRESS_SPACE;
    hyper_cmd_struct.addr_size  = OSPI_ADDRESS_32_BITS;
    hyper_cmd_struct.address    = addr;
    hyper_cmd_struct.dqs_mode   = OSPI_DQS_ENABLE;
    hyper_cmd_struct.nbdata     = size;

    ospi_hyperbus_cmd_config(drv->ospi_periph, ospi_struct, &hyper_cmd_struct);
    ospi_receive(drv->ospi_periph, ospi_struct, pdata);
}

/*!
    \brief      write data to GSR6W28AM PSRAM via HyperBus memory space
    \param[in]  drv: pointer to OSPI driver structure
    \param[in]  ospi_struct: pointer to OSPI parameter structure
    \param[in]  pdata: pointer to data buffer to write
    \param[in]  addr: PSRAM address to write to
    \param[in]  size: number of bytes to write
    \param[out] none
    \retval     none
*/
static void _ospi_psram_write(struct gd32_ospi *drv, ospi_parameter_struct *ospi_struct,
                              uint8_t *pdata, uint32_t addr, uint32_t size)
{
    ospi_hyperbus_cmd_struct hyper_cmd_struct;

    hyper_cmd_struct.addr_space = OSPI_MEMORY_ADDRESS_SPACE;
    hyper_cmd_struct.addr_size  = OSPI_ADDRESS_32_BITS;
    hyper_cmd_struct.address    = addr;
    hyper_cmd_struct.dqs_mode   = OSPI_DQS_ENABLE;
    hyper_cmd_struct.nbdata     = size;

    ospi_hyperbus_cmd_config(drv->ospi_periph, ospi_struct, &hyper_cmd_struct);
    ospi_transmit(drv->ospi_periph, pdata);
}

/*!
    \brief      write large amount of data to GSR6W28AM PSRAM with page-based splitting
    \param[in]  drv: pointer to OSPI driver structure
    \param[in]  ospi_struct: pointer to OSPI parameter structure
    \param[in]  pdata: pointer to data buffer to write
    \param[in]  addr: PSRAM address to write to
    \param[in]  size: number of bytes to write
    \param[out] none
    \retval     none
*/
static void _ospi_psram_buffer_write(struct gd32_ospi *drv, ospi_parameter_struct *ospi_struct,
                                     uint8_t *pdata, uint32_t addr, uint32_t size)
{
    uint32_t current_size, current_addr;
    uint32_t data_offset = 0;
    uint32_t remaining_size = size;

    current_addr = addr;

    /* calculate the size between the write address and the end of the page */
    current_size = PSRAM_PAGE_SIZE - (current_addr % PSRAM_PAGE_SIZE);

    /* check if the size of the data is less than the remaining place in the page */
    if (current_size > remaining_size)
    {
        current_size = remaining_size;
    }

    _ospi_psram_write(drv, ospi_struct, &pdata[data_offset], current_addr, current_size);

    /* update the address and size variables for next page programming */
    current_addr += current_size / 2;
    data_offset += current_size;
    remaining_size -= current_size;

    while (remaining_size >= PSRAM_PAGE_SIZE)
    {
        _ospi_psram_write(drv, ospi_struct, &pdata[data_offset], current_addr, PSRAM_PAGE_SIZE);
        current_addr += PSRAM_PAGE_SIZE / 2;
        data_offset += PSRAM_PAGE_SIZE;
        remaining_size -= PSRAM_PAGE_SIZE;
    }

    /* write the remaining data less than one page */
    if (remaining_size > 0)
    {
        _ospi_psram_write(drv, ospi_struct, &pdata[data_offset], current_addr, remaining_size);
    }
}

/*!
    \brief      enable memory-mapped mode for GSR6W28AM PSRAM
    \param[in]  drv: pointer to OSPI driver structure
    \param[in]  ospi_struct: pointer to OSPI parameter structure
    \param[out] none
    \retval     none
*/
static void _ospi_psram_memorymapped_enable(struct gd32_ospi *drv, ospi_parameter_struct *ospi_struct)
{
    ospi_hyperbus_cmd_struct hyper_cmd_struct;
    ospi_memorymapped_struct memory_map_struct;

    hyper_cmd_struct.addr_space = OSPI_MEMORY_ADDRESS_SPACE;
    hyper_cmd_struct.addr_size  = OSPI_ADDRESS_32_BITS;
    hyper_cmd_struct.address    = 0;
    hyper_cmd_struct.dqs_mode   = OSPI_DQS_ENABLE;
    hyper_cmd_struct.nbdata     = 1;

    ospi_hyperbus_cmd_config(drv->ospi_periph, ospi_struct, &hyper_cmd_struct);

    memory_map_struct.timeout_activation = OSPI_TIMEOUT_COUNT_DISABLE;
    ospi_memorymapped_mode(drv->ospi_periph, &memory_map_struct);
}

/*!
    \brief      configure OSPI PSRAM with user-specified parameters
    \param[in]  ospi_dev: pointer to OSPI device structure
    \param[in]  config: pointer to configuration structure
    \param[out] none
    \retval     RT_EOK
*/
static rt_err_t _ospi_psram_config(struct gd32_ospi_dev *ospi_dev,
                                   struct rt_ospi_configuration *config)
{
    struct gd32_ospi *drv = ospi_dev->gd32_ospi_drv;
    ospi_parameter_struct *ospi_struct = &ospi_dev->ospi_param;
    ospi_hyperbus_cfg_struct hyperbus_struct;

    RT_ASSERT(drv != RT_NULL);
    RT_ASSERT(config != RT_NULL);

    /* reset the OSPI peripheral */
    ospi_deinit(drv->ospi_periph);

    /* initialize the parameters of OSPI struct */
    ospi_struct_init(ospi_struct);

    ospi_struct->prescaler        = config->prescaler;
    ospi_struct->sample_shift     = OSPI_SAMPLE_SHIFTING_NONE;
    ospi_struct->fifo_threshold   = config->fifo_threshold;
    ospi_struct->dual_quad        = OSPI_DUAL_QUAD_MODE_DISABLE;
    ospi_struct->device_size      = config->device_size;
    ospi_struct->free_clock_run   = OSPI_CLOCK_FREE_RUN_DISABLE;
    ospi_struct->cs_hightime      = config->cs_hightime;
    ospi_struct->memory_type      = OSPI_HYPERBUS_MEMORY_MODE;
    ospi_struct->delay_hold_cycle = config->delay_hold_cycle;
    ospi_struct->refrate          = config->refrate;

    /* initialize OSPI parameter */
    ospi_init(drv->ospi_periph, ospi_struct);

    /* configure HyperBus protocol parameters */
    hyperbus_struct.rw_recovery_time   = config->rw_recovery_time;
    hyperbus_struct.access_time        = config->access_time;
    hyperbus_struct.write_zero_latency = OSPI_WRITE_ZERO_LATENCY_DISABLE;
    hyperbus_struct.latency_mode       = OSPI_VAR_INIT_LATENCY;
    ospi_hyperbus_config(drv->ospi_periph, &hyperbus_struct);

    /* enable OSPI */
    ospi_enable(drv->ospi_periph);

    /* configure delay chain and DQS timing */
    _ospi_delay_chain_config(drv->ospi_periph);

    LOG_I("OSPI PSRAM reconfigured: prescaler=%d", config->prescaler);

    return RT_EOK;
}

/* RT-Thread device interface */
static rt_err_t rt_ospi_init(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    struct gd32_ospi_dev *ospi_dev = (struct gd32_ospi_dev *)dev;
    struct gd32_ospi *drv = ospi_dev->gd32_ospi_drv;

    /* initialize OSPI/OSPIM/GPIO and configure PSRAM with default HyperBus parameters */
    _ospi_psram_hw_init(drv, &ospi_dev->ospi_param);

    ospi_dev->psram_addr = 0;

    return RT_EOK;
}

static rt_err_t rt_ospi_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_ASSERT(dev != RT_NULL);

    struct gd32_ospi_dev *ospi_dev = (struct gd32_ospi_dev *)dev;
    struct gd32_ospi *drv = ospi_dev->gd32_ospi_drv;

    rcu_periph_clock_enable(drv->ospi_clk);

    return RT_EOK;
}

static rt_err_t rt_ospi_close(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    struct gd32_ospi_dev *ospi_dev = (struct gd32_ospi_dev *)dev;
    struct gd32_ospi *drv = ospi_dev->gd32_ospi_drv;

    ospi_disable(drv->ospi_periph);
    rcu_periph_clock_disable(drv->ospi_clk);

    return RT_EOK;
}

static rt_err_t rt_ospi_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    struct gd32_ospi_dev *ospi_dev = (struct gd32_ospi_dev *)dev;
    struct gd32_ospi *drv = ospi_dev->gd32_ospi_drv;

    switch (cmd)
    {
    case OSPI_CTRL_CONFIG_SET:
    {
        RT_ASSERT(args != RT_NULL);
        struct rt_ospi_configuration *config = (struct rt_ospi_configuration *)args;
        rt_err_t ret = _ospi_psram_config(ospi_dev, config);
        if (ret == RT_EOK)
        {
            ospi_dev->psram_addr = 0;
        }
        return ret;
    }

    case OSPI_CTRL_ADDR_SET:
    {
        RT_ASSERT(args != RT_NULL);
        uint32_t addr_offset = *(uint32_t *)args;
        if (addr_offset >= OSPI_PSRAM_MAX_SIZE)
        {
            LOG_E("ospi address offset 0x%08X exceeds max size", addr_offset);
            return -RT_EINVAL;
        }
        ospi_dev->psram_addr = addr_offset;
        return RT_EOK;
    }

    case OSPI_CTRL_ENTER_MMAP:
    {
        _ospi_psram_memorymapped_enable(drv, &ospi_dev->ospi_param);
        LOG_I("OSPI entered memory-mapped mode, base=0x%08X", drv->mapped_addr);
        return RT_EOK;
    }

    case OSPI_CTRL_EXIT_MMAP:
    {
        /* abort to exit memory-mapped mode */
        ospi_transmission_abort(drv->ospi_periph);
        return RT_EOK;
    }

    default:
        return -RT_EINVAL;
    }
}

static rt_ssize_t rt_ospi_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    struct gd32_ospi_dev *ospi_dev = (struct gd32_ospi_dev *)dev;
    struct gd32_ospi *drv = ospi_dev->gd32_ospi_drv;
    uint32_t addr = ospi_dev->psram_addr + (uint32_t)pos;

    if ((addr + size) > OSPI_PSRAM_MAX_SIZE)
    {
        LOG_E("ospi psram read address error: 0x%08X + %d", addr, size);
        return 0;
    }

    _ospi_psram_read(drv, &ospi_dev->ospi_param, (uint8_t *)buffer, addr, size);

    return (rt_ssize_t)size;
}

static rt_ssize_t rt_ospi_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    struct gd32_ospi_dev *ospi_dev = (struct gd32_ospi_dev *)dev;
    struct gd32_ospi *drv = ospi_dev->gd32_ospi_drv;
    uint32_t addr = ospi_dev->psram_addr + (uint32_t)pos;

    if ((addr + size) > OSPI_PSRAM_MAX_SIZE)
    {
        LOG_E("ospi psram write address error: 0x%08X + %d", addr, size);
        return 0;
    }

    _ospi_psram_buffer_write(drv, &ospi_dev->ospi_param, (uint8_t *)buffer, addr, size);

    return (rt_ssize_t)size;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops ospi_ops =
{
    rt_ospi_init,
    rt_ospi_open,
    rt_ospi_close,
    rt_ospi_read,
    rt_ospi_write,
    rt_ospi_control,
};
#endif

int rt_hw_ospi_init(void)
{
    int result = 0;

    rt_device_t device = &gd32_ospi0_dev.parent;
    gd32_ospi0_dev.gd32_ospi_drv = &ospi0_drv;
    gd32_ospi0_dev.psram_addr = 0;

    device->type = RT_Device_Class_SPIDevice;
#ifdef RT_USING_DEVICE_OPS
    device->ops = &ospi_ops;
#else
    device->init    = rt_ospi_init;
    device->open    = rt_ospi_open;
    device->close   = rt_ospi_close;
    device->read    = rt_ospi_read;
    device->write   = rt_ospi_write;
    device->control = rt_ospi_control;
#endif

    device->user_data = RT_NULL;

    result = rt_device_register(device, ospi0_drv.device_name,
                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE);
    if (result != RT_EOK)
    {
        LOG_E("OSPI device registered fail!");
        return -RT_ERROR;
    }

    LOG_I("OSPI device registered success!");

    return result;
}

INIT_BOARD_EXPORT(rt_hw_ospi_init);

#endif /* BSP_USING_OSPI */
