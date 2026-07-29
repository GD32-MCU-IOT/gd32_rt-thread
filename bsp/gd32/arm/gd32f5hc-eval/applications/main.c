/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-27     Zhiwei Zhang first implementation for GD32W51x_F5HC-EVAL
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string.h>

/* Test Feature Switches - comment out to disable */
#ifdef PKG_USING_AT24CXX
#define GD32_I2C_EEPROM_TEST
#endif
#ifdef RT_USING_SPI
#define GD32_SPI_TEST
#endif

/* LED pins - GD32W51x_F5HC-EVAL board
 * LED1 = PB6, LED2 = PA15, LED3 = PA6, LED4 = PA1
 */
#define LED1_PIN    GET_PIN(B, 6)
#define LED2_PIN    GET_PIN(A, 15)
#define LED3_PIN    GET_PIN(A, 6)
#define LED4_PIN    GET_PIN(A, 1)

#ifdef GD32_I2C_EEPROM_TEST
#include "at24cxx.h"
#define I2C_BUFFER_SIZE    32
#define I2C_BUS_NAME       "hwi2c1"
static uint8_t i2c_basic_test(void);
#endif

#ifdef GD32_SPI_TEST
#define SPI_BUS_NAME     "spi1"
#define SPI_DEV_NAME     "spi10"
#define SPI_CS_PIN       GET_PIN(B, 12)
#define SPI_TEST_SIZE    8

static uint8_t spi_basic_test(void);
#endif

int main(void)
{
    /* set LED pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);

    rt_kprintf("\n\rHello GD32W51x_F5HC-EVAL!\n\r");
    rt_kprintf("RT-Thread BSP adaptation successful!\n\r");

#ifdef GD32_I2C_EEPROM_TEST
    rt_kprintf("\n\r--- I2C EEPROM Test ---\n\r");
    if (i2c_basic_test() != 0)
    {
        rt_kprintf("I2C EEPROM test passed!\n\r");
    }
    else
    {
        rt_kprintf("I2C EEPROM test failed!\n\r");
    }
#endif

#ifdef GD32_SPI_TEST
    rt_kprintf("\n\r--- SPI Flash Test ---\n\r");
    if (spi_basic_test() != 0)
    {
        rt_kprintf("SPI Flash test passed!\n\r");
    }
    else
    {
        rt_kprintf("SPI Flash test failed!\n\r");
    }
#endif

    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(200);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(200);
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_pin_write(LED3_PIN, PIN_HIGH);
        rt_thread_mdelay(200);
        rt_pin_write(LED3_PIN, PIN_LOW);
        rt_pin_write(LED4_PIN, PIN_HIGH);
        rt_thread_mdelay(200);
        rt_pin_write(LED4_PIN, PIN_LOW);
    }

    return RT_EOK;
}

#ifdef GD32_I2C_EEPROM_TEST
/**
 * @brief Basic I2C EEPROM write/read test
 * @return 1 on success, 0 on failure
 */
static uint8_t i2c_basic_test(void)
{
    at24cxx_device_t eeprom;
    uint8_t write_buf[I2C_BUFFER_SIZE];
    uint8_t read_buf[I2C_BUFFER_SIZE];
    uint16_t i;

    eeprom = at24cxx_init(I2C_BUS_NAME, 0x00);
    if (eeprom == RT_NULL)
    {
        rt_kprintf("I2C bus %s not found!\n\r", I2C_BUS_NAME);
        return 0;
    }
    rt_kprintf("Found EEPROM on I2C bus: %s\n\r", I2C_BUS_NAME);

    /* fill write buffer */
    for (i = 0; i < I2C_BUFFER_SIZE; i++)
    {
        write_buf[i] = (uint8_t)(i + 0x10);
    }

    /* write */
    if (at24cxx_page_write(eeprom, 0x00, write_buf, I2C_BUFFER_SIZE) != RT_EOK)
    {
        rt_kprintf("EEPROM write failed!\n\r");
        return 0;
    }

    /* read */
    rt_memset(read_buf, 0, I2C_BUFFER_SIZE);
    if (at24cxx_page_read(eeprom, 0x00, read_buf, I2C_BUFFER_SIZE) != RT_EOK)
    {
        rt_kprintf("EEPROM read failed!\n\r");
        return 0;
    }

    /* verify */
    if (memcmp(write_buf, read_buf, I2C_BUFFER_SIZE) == 0)
    {
        rt_kprintf("I2C write/read %d bytes verified OK.\n\r", I2C_BUFFER_SIZE);
        return 1;
    }

    /* find first mismatch */
    for (i = 0; i < I2C_BUFFER_SIZE; i++)
    {
        if (write_buf[i] != read_buf[i])
        {
            rt_kprintf("Mismatch at offset %d: wrote 0x%02X, read 0x%02X\n\r",
                       i, write_buf[i], read_buf[i]);
            break;
        }
    }
    return 0;
}
#endif

#ifdef GD32_SPI_TEST
/**
 * @brief Basic SPI Flash read ID + small write/read test
 * @return 1 on success, 0 on failure
 */
static uint8_t spi_basic_test(void)
{
    struct rt_spi_device *spi_dev = RT_NULL;
    struct rt_spi_configuration cfg;
    uint8_t cmd_read_id = 0x9F;
    uint8_t id_buf[3] = {0};
    uint8_t cmd_wren = 0x06;
    uint8_t dummy;
    uint8_t erase_cmd[4] = {0x20, 0x00, 0x10, 0x00};   /* Sector Erase at 0x001000 */
    uint8_t write_cmd[4] = {0x02, 0x00, 0x10, 0x00};   /* Page Program at 0x001000 */
    uint8_t read_cmd[4]  = {0x03, 0x00, 0x10, 0x00};   /* Read Data at 0x001000 */
    uint8_t tx_buf[SPI_TEST_SIZE];
    uint8_t rx_buf[SPI_TEST_SIZE];
    rt_err_t ret;
    int i;

    /* attach SPI device to bus (skip if already attached) */
    if (rt_device_find(SPI_DEV_NAME) == RT_NULL)
    {
        ret = rt_hw_spi_device_attach(SPI_BUS_NAME, SPI_DEV_NAME, SPI_CS_PIN);
        if (ret != RT_EOK)
        {
            rt_kprintf("SPI device attach failed!\n\r");
            return 0;
        }
    }

    /* find SPI device */
    spi_dev = (struct rt_spi_device *)rt_device_find(SPI_DEV_NAME);
    if (spi_dev == RT_NULL)
    {
        rt_kprintf("SPI device %s not found!\n\r", SPI_DEV_NAME);
        return 0;
    }

    /* configure SPI */
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    cfg.max_hz = 2 * 1000 * 1000;  /* 2 MHz */
    ret = rt_spi_configure(spi_dev, &cfg);
    if (ret != RT_EOK)
    {
        rt_kprintf("SPI configure failed!\n\r");
        return 0;
    }

    /* Read Flash ID */
    rt_spi_send_then_recv(spi_dev, &cmd_read_id, 1, id_buf, 3);
    rt_kprintf("SPI Flash ID: 0x%02X 0x%02X 0x%02X\n\r", id_buf[0], id_buf[1], id_buf[2]);

    if (id_buf[0] == 0x00 || id_buf[0] == 0xFF)
    {
        rt_kprintf("No SPI Flash detected!\n\r");
        return 0;
    }

    /* prepare test data */
    for (i = 0; i < SPI_TEST_SIZE; i++)
    {
        tx_buf[i] = (uint8_t)(i + 0x10);
    }
    rt_memset(rx_buf, 0, SPI_TEST_SIZE);

    /* Write Enable + Erase */
    rt_spi_transfer(spi_dev, &cmd_wren, &dummy, 1);
    rt_spi_transfer(spi_dev, erase_cmd, RT_NULL, 4);
    rt_thread_mdelay(100);

    /* Write Enable + Page Program */
    rt_spi_transfer(spi_dev, &cmd_wren, &dummy, 1);
    rt_spi_send_then_send(spi_dev, write_cmd, 4, tx_buf, SPI_TEST_SIZE);
    rt_thread_mdelay(50);

    /* Read back */
    rt_spi_send_then_recv(spi_dev, read_cmd, 4, rx_buf, SPI_TEST_SIZE);

    /* Verify */
    if (memcmp(tx_buf, rx_buf, SPI_TEST_SIZE) == 0)
    {
        rt_kprintf("SPI write/read %d bytes verified OK.\n\r", SPI_TEST_SIZE);
        return 1;
    }

    rt_kprintf("SPI data mismatch!\n\r");
    rt_kprintf("TX: ");
    for (i = 0; i < SPI_TEST_SIZE; i++)
        rt_kprintf("%02X ", tx_buf[i]);
    rt_kprintf("\n\rRX: ");
    for (i = 0; i < SPI_TEST_SIZE; i++)
        rt_kprintf("%02X ", rx_buf[i]);
    rt_kprintf("\n\r");
    return 0;
}
#endif
