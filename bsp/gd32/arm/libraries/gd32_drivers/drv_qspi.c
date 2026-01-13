/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-12-20     BruceOu           the first version
 */

#include "drv_qspi.h"

#ifdef RT_USING_QSPI

#if defined(BSP_USING_QSPI)
#define LOG_TAG              "drv.qspi"

#include <rtdbg.h>

#ifdef BSP_USING_QSPI
static struct rt_spi_bus qspi_bus0;
#endif
static const struct gd32_qspi_bus gd32_qspi_bus_config[] = {
#ifdef BSP_USING_QSPI
    {
        SPI0,
        RCU_SPI0,
        "qspi0",
        &qspi_bus0,
    },
#endif /* BSP_USING_QSPI */
};

static rt_err_t gd32_qspi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg);
static rt_ssize_t gd32_qspi_xfer(struct rt_spi_device *device, struct rt_spi_message *msg);

static const struct rt_spi_ops gd32_qspi_ops =
{
    .configure = gd32_qspi_configure,
    .xfer = gd32_qspi_xfer,
};

static void gd32_qspi_set_lines(struct gd32_qspi_bus *bus, rt_uint8_t lines, rt_bool_t is_read)
{
    if (lines == 4)
    {
        spi_quad_enable(bus->spi_periph);
        if (is_read)
        {
            spi_quad_read_enable(bus->spi_periph);
        }
        else
        {
            spi_quad_write_enable(bus->spi_periph);
        }
    }
    else if (lines == 2)
    {
        LOG_W("2-line mode not supported, fallback to 1-line");
        spi_quad_disable(bus->spi_periph);
    }
    else
    {
        spi_quad_disable(bus->spi_periph);
    }
}

static rt_uint8_t gd32_qspi_pack_u32(rt_uint32_t value, rt_uint8_t size, rt_uint8_t *out)
{
    rt_uint8_t bytes = size / 8;

    if (bytes == 0 || bytes > 4)
    {
        return 0;
    }

    for (rt_uint8_t i = 0; i < bytes; i++)
    {
        out[i] = (value >> (8 * (bytes - 1 - i))) & 0xFF;
    }

    return bytes;
}

static rt_err_t gd32_qspi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    struct gd32_qspi_bus *bus = device->bus->parent.user_data;
    spi_parameter_struct spi_init_struct;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    gd32_qspi_init(bus);

    if (cfg->data_width > 8)
    {
        LOG_E("QSPI only supports 8-bit data width");
        return -RT_EIO;
    }

    uint32_t spi_apb_clock;
    uint32_t max_hz = cfg->max_hz;
  
    spi_apb_clock = rcu_clock_freq_get(CK_APB2);

    spi_disable(bus->spi_periph);
    
    spi_struct_para_init(&spi_init_struct);
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_struct.nss = SPI_NSS_SOFT;
    spi_init_struct.endian = (cfg->mode & RT_SPI_MSB) ? SPI_ENDIAN_MSB : SPI_ENDIAN_LSB;

    if (max_hz >= spi_apb_clock / 2)
    {
        spi_init_struct.prescale = SPI_PSC_2;
    }
    else if (max_hz >= spi_apb_clock / 4)
    {
        spi_init_struct.prescale = SPI_PSC_4;
    }
    else if (max_hz >= spi_apb_clock / 8)
    {
        spi_init_struct.prescale = SPI_PSC_8;
    }
    else if (max_hz >= spi_apb_clock / 16)
    {
        spi_init_struct.prescale = SPI_PSC_16;
    }
    else if (max_hz >= spi_apb_clock / 32)
    {
        spi_init_struct.prescale = SPI_PSC_32;
    }
    else if (max_hz >= spi_apb_clock / 64)
    {
        spi_init_struct.prescale = SPI_PSC_64;
    }
    else if (max_hz >= spi_apb_clock / 128)
    {
        spi_init_struct.prescale = SPI_PSC_128;
    }
    else
    {
        spi_init_struct.prescale = SPI_PSC_256;
    }

    switch (cfg->mode & (RT_SPI_CPHA | RT_SPI_CPOL))
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
    default:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
        break;
    }

    spi_crc_off(bus->spi_periph);
    spi_init(bus->spi_periph, &spi_init_struct);
    spi_enable(bus->spi_periph);

    uint32_t div_table[] = {2, 4, 8, 16, 32, 64, 128, 256};
    uint32_t div_idx = (spi_init_struct.prescale >> 3) & 0x7;
    uint32_t actual_hz = spi_apb_clock / div_table[div_idx];
    
    LOG_I("QSPI reconfigured: mode=%d, target=%dHz, actual=%dHz", 
          cfg->mode & (RT_SPI_CPOL | RT_SPI_CPHA), cfg->max_hz, actual_hz);

    return RT_EOK;
}

static rt_ssize_t gd32_qspi_xfer(struct rt_spi_device *device, struct rt_spi_message *msg)
{
    struct gd32_qspi_bus *bus = device->bus->parent.user_data;
    struct rt_qspi_message *qmsg = (struct rt_qspi_message *)msg;
    rt_ssize_t result = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(qmsg != RT_NULL);

    if (msg->cs_take && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        rt_pin_write(device->cs_pin, (device->config.mode & RT_SPI_CS_HIGH) ? PIN_HIGH : PIN_LOW);
    }

    if (qmsg->instruction.qspi_lines)
    {
        gd32_qspi_set_lines(bus, qmsg->instruction.qspi_lines, RT_FALSE);
        
        while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_TBE));
        spi_i2s_data_transmit(bus->spi_periph, qmsg->instruction.content);
        while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_RBNE));
        spi_i2s_data_receive(bus->spi_periph);
        
        result += 1;
    }

    if (qmsg->address.size)
    {
        rt_uint8_t addr_buf[4];
        rt_uint8_t addr_len = gd32_qspi_pack_u32(qmsg->address.content, qmsg->address.size, addr_buf);

        if (addr_len)
        {
            gd32_qspi_set_lines(bus, qmsg->address.qspi_lines, RT_FALSE);
            
            for (rt_size_t i = 0; i < addr_len; i++)
            {
                while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_TBE));
                spi_i2s_data_transmit(bus->spi_periph, addr_buf[i]);
                while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_RBNE));
                spi_i2s_data_receive(bus->spi_periph);
            }
            result += addr_len;
        }
    }

    if (qmsg->alternate_bytes.size)
    {
        rt_uint8_t alt_buf[4];
        rt_uint8_t alt_len = gd32_qspi_pack_u32(qmsg->alternate_bytes.content, qmsg->alternate_bytes.size, alt_buf);
        
        if (alt_len)
        {
            gd32_qspi_set_lines(bus, qmsg->alternate_bytes.qspi_lines, RT_FALSE);
            for (rt_size_t i = 0; i < alt_len; i++)
            {
                while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_TBE));
                spi_i2s_data_transmit(bus->spi_periph, alt_buf[i]);
                while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_RBNE));
                spi_i2s_data_receive(bus->spi_periph);
            }
            result += alt_len;
        }
    }

    if (qmsg->dummy_cycles)
    {
        rt_uint8_t dummy_lines = qmsg->address.qspi_lines ? qmsg->address.qspi_lines : 1;
        rt_uint32_t dummy_bytes_to_send = 0;

        if (dummy_lines == 4)
        {
            dummy_bytes_to_send = qmsg->dummy_cycles / 2;
            if (dummy_bytes_to_send == 0 && qmsg->dummy_cycles > 0) dummy_bytes_to_send = 1;
        }
        else
        {
            dummy_bytes_to_send = (qmsg->dummy_cycles + 7) / 8;
        }

        gd32_qspi_set_lines(bus, dummy_lines, RT_FALSE);

        for (rt_size_t i = 0; i < dummy_bytes_to_send; i++)
        {
            while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_TBE));
            spi_i2s_data_transmit(bus->spi_periph, 0xA5);
            while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_RBNE));
            spi_i2s_data_receive(bus->spi_periph);
        }
        while (SET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_TRANS));
        
        result += dummy_bytes_to_send;
    }

    if (msg->length)
    {
        rt_uint8_t data_lines = qmsg->qspi_data_lines ? qmsg->qspi_data_lines : 1;
        
        gd32_qspi_set_lines(bus, data_lines, msg->recv_buf != RT_NULL);

        if (msg->send_buf)
        {
            const rt_uint8_t *send_ptr = msg->send_buf;
            rt_uint32_t size = msg->length;
            
            while (size--)
            {
                while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_TBE));
                spi_i2s_data_transmit(bus->spi_periph, *send_ptr++);
                while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_RBNE));
                spi_i2s_data_receive(bus->spi_periph);
            }
            while (SET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_TRANS));
            result = msg->length;
        }
        else if (msg->recv_buf)
        {
            rt_uint8_t *recv_ptr = msg->recv_buf;
            rt_uint32_t size = msg->length;
            
            while (size--)
            {
                while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_TBE));
                spi_i2s_data_transmit(bus->spi_periph, 0xA5); 
                
                while (RESET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_RBNE));
                *recv_ptr++ = spi_i2s_data_receive(bus->spi_periph);
            }
            while (SET == spi_i2s_flag_get(bus->spi_periph, SPI_FLAG_TRANS));
            
            result = msg->length;
        }
    }

    if (msg->cs_release && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        rt_pin_write(device->cs_pin, (device->config.mode & RT_SPI_CS_HIGH) ? PIN_LOW : PIN_HIGH);
    }
    
    gd32_qspi_set_lines(bus, 1, RT_FALSE);

    return result;
}

rt_err_t rt_hw_qspi_device_attach(const char *bus_name,
                                  const char *device_name,
                                  rt_base_t cs_pin,
                                  rt_uint8_t data_line_width,
                                  void (*enter_qspi_mode)(struct rt_qspi_device *device),
                                  void (*exit_qspi_mode)(struct rt_qspi_device *device))
{
    struct rt_qspi_device *qspi_device = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);
    RT_ASSERT(data_line_width == 1 || data_line_width == 2 || data_line_width == 4);

    qspi_device = (struct rt_qspi_device *)rt_malloc(sizeof(struct rt_qspi_device));
    if (qspi_device == RT_NULL)
    {
        LOG_E("No memory for QSPI device!");
        result = -RT_ENOMEM;
        goto __exit;
    }

    qspi_device->enter_qspi_mode = enter_qspi_mode;
    qspi_device->exit_qspi_mode = exit_qspi_mode;
    qspi_device->config.qspi_dl_width = data_line_width;
    qspi_device->config.medium_size = 0;
    qspi_device->config.ddr_mode = 0;
    qspi_device->config.parent.data_width = 8;
    qspi_device->config.parent.mode = RT_SPI_MODE_0 | RT_SPI_MSB;
    qspi_device->config.parent.max_hz = 2 * 1000 * 1000;

    result = rt_spi_bus_attach_device_cspin(&qspi_device->parent,
                                            device_name,
                                            bus_name,
                                            cs_pin,
                                            RT_NULL);
    if (result != RT_EOK)
    {
        goto __exit;
    }

    if (cs_pin != PIN_NONE)
    {
        rt_pin_mode(cs_pin, PIN_MODE_OUTPUT);
        rt_pin_write(cs_pin, PIN_HIGH);
    }

    result = rt_spi_configure(&qspi_device->parent, &qspi_device->config.parent);
    if (result != RT_EOK)
    {
        LOG_E("Failed to apply default QSPI configuration");
        goto __exit;
    }
    
    LOG_I("Default config applied: mode=%d, freq=%dHz, %d-line", 
          qspi_device->config.parent.mode & (RT_SPI_CPOL | RT_SPI_CPHA),
          qspi_device->config.parent.max_hz,
          data_line_width);

__exit:
    if (result != RT_EOK)
    {
        if (qspi_device)
        {
            rt_free(qspi_device);
        }
        LOG_E("Failed to attach QSPI device %s to bus %s", device_name, bus_name);
    }
    else
    {
        LOG_I("QSPI device %s attached to bus %s successfully", device_name, bus_name);
    }

    return result;
}

static int rt_hw_qspi_init(void)
{
    rt_err_t result = RT_EOK;

    for (rt_size_t i = 0; i < sizeof(gd32_qspi_bus_config) / sizeof(gd32_qspi_bus_config[0]); i++)
    {
        gd32_qspi_bus_config[i].spi_bus->parent.user_data = (void *)&gd32_qspi_bus_config[i];

        result = rt_qspi_bus_register(gd32_qspi_bus_config[i].spi_bus, 
                                       gd32_qspi_bus_config[i].bus_name, 
                                       &gd32_qspi_ops);
        if (result != RT_EOK)
        {
            LOG_E("Failed to register QSPI bus %s", gd32_qspi_bus_config[i].bus_name);
            continue;
        }

        LOG_D("%s bus init done", gd32_qspi_bus_config[i].bus_name);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_qspi_init);

rt_err_t qspi_send_cmd(struct rt_qspi_device *device, rt_uint8_t cmd)
{
    struct rt_qspi_message msg;
    
    rt_memset(&msg, 0, sizeof(msg));
    msg.instruction.content = cmd;
    msg.instruction.qspi_lines = 1;
    msg.parent.cs_take = 1;
    msg.parent.cs_release = 1;
    
    rt_qspi_transfer_message(device, &msg);
    return RT_EOK;
}

rt_ssize_t qspi_read(struct rt_qspi_device *device, rt_uint8_t cmd, 
                     rt_uint32_t addr, rt_uint8_t dummy_cycles, rt_uint8_t data_lines,
                     rt_uint8_t *buf, rt_size_t len)
{
    struct rt_qspi_message msg;
    
    rt_memset(&msg, 0, sizeof(msg));
    msg.instruction.content = cmd;
    msg.instruction.qspi_lines = 1;

    if (cmd != 0x9F && cmd != 0x05 && cmd != 0x35)
    {
        msg.address.content = addr;
        msg.address.size = 24;
        msg.address.qspi_lines = 1;
    }
    
    msg.dummy_cycles = dummy_cycles;
    msg.qspi_data_lines = data_lines;
    msg.parent.recv_buf = buf;
    msg.parent.length = len;
    msg.parent.cs_take = 1;
    msg.parent.cs_release = 1;
    
    return rt_qspi_transfer_message(device, &msg);
}

rt_ssize_t qspi_write(struct rt_qspi_device *device, rt_uint8_t cmd,
                      rt_uint32_t addr, rt_uint8_t data_lines,
                      const rt_uint8_t *buf, rt_size_t len)
{
    struct rt_qspi_message msg;
    
    rt_memset(&msg, 0, sizeof(msg));
    msg.instruction.content = cmd;
    msg.instruction.qspi_lines = 1;

    if (cmd == 0x02 || cmd == 0x20 || cmd == 0xD8 || cmd == 0x52)
    {
        msg.address.content = addr;
        msg.address.size = 24;
        msg.address.qspi_lines = 1;
    }
    
    msg.qspi_data_lines = data_lines;
    msg.parent.send_buf = buf;
    msg.parent.length = len;
    msg.parent.cs_take = 1;
    msg.parent.cs_release = 1;
    
    return rt_qspi_transfer_message(device, &msg);
}

rt_err_t qspi_wait_busy(struct rt_qspi_device *device, rt_uint32_t timeout_ms)
{
    rt_uint32_t start = rt_tick_get();
    rt_uint8_t status;
    
    do {
        qspi_read(device, 0x05, 0, 0, 1, &status, 1);
        if ((status & 0x01) == 0)
            return RT_EOK;
        
        rt_thread_mdelay(1);
        
        if (timeout_ms > 0 && (rt_tick_get() - start) > rt_tick_from_millisecond(timeout_ms))
            return -RT_ETIMEOUT;
    } while (1);
}

rt_err_t qspi_enable_quad(struct rt_qspi_device *device)
{
    rt_uint8_t sr2;
    
    qspi_read(device, 0x35, 0, 0, 1, &sr2, 1);
    
    if (sr2 & 0x02)
        return RT_EOK;
    
    qspi_send_cmd(device, 0x06);
    
    sr2 |= 0x02;
    qspi_write(device, 0x31, 0, 1, &sr2, 1);
    
    return qspi_wait_busy(device, 1000);
}

#endif /* BSP_USING_QSPI */
#endif /* RT_USING_QSPI */
