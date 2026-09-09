/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 * 2026-08-10     RT-Thread    add I2C/SPI/UART/EXTI samples for GD32107C-EVAL
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string.h>

/* Test Feature Switches - comment out to disable */
#define GD32_I2C_EEPROM_TEST
#define GD32_SPI_POLL_TEST

/* defined the LED pins according to schematic */
#define LED2_PIN    GET_PIN(C, 0)   /* LED2 on PC0 */
#define LED3_PIN    GET_PIN(C, 2)   /* LED3 on PC2 */
#define LED4_PIN    GET_PIN(E, 0)   /* LED4 on PE0 */
#define LED5_PIN    GET_PIN(E, 1)   /* LED5 on PE1 */

#ifdef GD32_I2C_EEPROM_TEST
#include "at24cxx.h"
#define BUFFER_SIZE    256
#define I2C_SERIAL     "hwi2c0"
rt_uint8_t i2c_buffer_write[BUFFER_SIZE];
rt_uint8_t i2c_buffer_read[BUFFER_SIZE];
static uint8_t i2c_24c02_test(void);
#endif

#if defined(GD32_SPI_POLL_TEST)
#include "drv_spi.h"
/* On-board GD25Q16 flash sits on SPI0: SCK=PA5, MISO=PA6, MOSI=PA7, CS=PE3 */
#define SPI_BUS_NAME     "spi0"
#define SPI_DEV_NAME     "spi00"
#define SPI_CS_PIN       GET_PIN(E, 3)

/* small transfer below BSP_SPI_DMA_TRANS_MIN_LEN so polling mode is used */
#define SPI_POLL_TEST_SIZE    8

static uint8_t cmd_read_id = 0x9F;
static uint8_t cmd_wren = 0x06;
static uint8_t id_buf[4] = {0};

static void spi_init_device(void);
#endif

#ifdef GD32_SPI_POLL_TEST
/**
 * @brief SPI Flash polling mode test - transfer below BSP_SPI_DMA_TRANS_MIN_LEN
 */
static void spi_poll_sample(void);
#endif

int main(void)
{
    int count = 1;

    /* set LED pin mode to output */
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED5_PIN, PIN_MODE_OUTPUT);

    rt_kprintf("Hello GD32107C-EVAL!\n");
    rt_kprintf("RT-Thread BSP adaptation successful!\n");
    rt_kprintf("System Clock: %d Hz\n", SystemCoreClock);

#ifdef GD32_I2C_EEPROM_TEST
    rt_kprintf("\n--- I2C EEPROM Test ---\n");
    if (i2c_24c02_test() != 0) {
        rt_kprintf("I2C-AT24C02 test passed!\n");
    } else {
        rt_kprintf("I2C-AT24C02 test failed!\n");
    }
#endif

#if defined(GD32_SPI_POLL_TEST)
    rt_kprintf("\n--- SPI Flash Test ---\n");
    spi_init_device();
#endif

#ifdef GD32_SPI_POLL_TEST
    spi_poll_sample();
#endif

    while (1)
    {
        /* turn on LED2 */
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        /* turn off LED2, turn on LED3 */
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_pin_write(LED3_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        /* turn off LED3, turn on LED4 */
        rt_pin_write(LED3_PIN, PIN_LOW);
        rt_pin_write(LED4_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        /* turn off LED4, turn on LED5 */
        rt_pin_write(LED4_PIN, PIN_LOW);
        rt_pin_write(LED5_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        /* turn off LED5 */
        rt_pin_write(LED5_PIN, PIN_LOW);
    }

    return RT_EOK;
}

#ifdef GD32_I2C_EEPROM_TEST
/**
 * @brief I2C EEPROM (AT24C02) read/write test
 * @return 1 on success, 0 on failure
 */
static uint8_t i2c_24c02_test(void)
{
    at24cxx_device_t ati2c;
    uint16_t i;

    ati2c = at24cxx_init(I2C_SERIAL, 0x00);
    if (ati2c == RT_NULL) {
        rt_kprintf("Failed to find EEPROM device!\n");
        return 0;
    }
    rt_kprintf("Found EEPROM device on %s\n", I2C_SERIAL);

    /* initialize write buffer */
    for (i = 0; i < BUFFER_SIZE; i++) {
        i2c_buffer_write[i] = i + 8;
    }

    rt_kprintf("I2C-AT24C02 writing %d bytes...\n", BUFFER_SIZE);
    if (at24cxx_page_write(ati2c, 0x00, i2c_buffer_write, BUFFER_SIZE) != RT_EOK) {
        rt_kprintf("I2C-AT24C02 write failed!\n");
        return 0;
    }
    rt_kprintf("I2C-AT24C02 write complete.\n");

    rt_kprintf("I2C-AT24C02 reading %d bytes...\n", BUFFER_SIZE);
    if (at24cxx_page_read(ati2c, 0x00, i2c_buffer_read, BUFFER_SIZE) != RT_EOK) {
        rt_kprintf("I2C-AT24C02 read failed!\n");
        return 0;
    }
    rt_kprintf("I2C-AT24C02 read complete.\n");

    /* compare read buffer with write buffer */
    for (i = 0; i < BUFFER_SIZE; i++) {
        if (i2c_buffer_read[i] != i2c_buffer_write[i]) {
            rt_kprintf("Data mismatch at offset %d: wrote 0x%02X, read 0x%02X\n",
                       i, i2c_buffer_write[i], i2c_buffer_read[i]);
            return 0;
        }
    }
    return 1;
}
#endif

#if defined(GD32_SPI_POLL_TEST)
/**
 * @brief Initialize SPI device - shared by polling test
 */
static void spi_init_device(void)
{
    struct rt_spi_device *spi_dev = RT_NULL;
    struct rt_spi_configuration cfg;

    /* attach SPI device to bus */
    if (rt_hw_spi_device_attach(SPI_BUS_NAME, SPI_DEV_NAME, SPI_CS_PIN) != RT_EOK) {
        rt_kprintf("SPI device attach failed!\n");
        return;
    }

    /* find SPI device */
    spi_dev = (struct rt_spi_device *)rt_device_find(SPI_DEV_NAME);
    if (spi_dev == RT_NULL) {
        rt_kprintf("SPI device %s not found!\n", SPI_DEV_NAME);
        return;
    }

    /* configure SPI */
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    cfg.max_hz = 2 * 1000 * 1000;  /* 2 MHz */
    rt_spi_configure(spi_dev, &cfg);

    /* Read Flash ID */
    rt_spi_send_then_recv(spi_dev, &cmd_read_id, 1, id_buf, 3);
    rt_kprintf("SPI Flash ID: 0x%02X 0x%02X 0x%02X\n", id_buf[0], id_buf[1], id_buf[2]);
}
#endif

#ifdef GD32_SPI_POLL_TEST
/**
 * @brief SPI Flash (GD25Q16) polling mode test - transfer below BSP_SPI_DMA_TRANS_MIN_LEN
 */
static void spi_poll_sample(void)
{
    uint8_t erase_cmd[4] = {0x20, 0x00, 0x10, 0x00};   /* Sector Erase at 0x001000 */
    uint8_t write_cmd[4] = {0x02, 0x00, 0x10, 0x00};   /* Page Program at 0x001000 */
    uint8_t read_cmd[4]  = {0x03, 0x00, 0x10, 0x00};   /* Read Data at 0x001000 */
    static uint8_t poll_tx[SPI_POLL_TEST_SIZE];
    static uint8_t poll_rx[SPI_POLL_TEST_SIZE];

    struct rt_spi_device *spi_dev = RT_NULL;
    rt_tick_t start, end;
    int i;

    /* initialize poll test buffer */
    for (i = 0; i < SPI_POLL_TEST_SIZE; i++) {
        poll_tx[i] = i + 0x10;
    }
    rt_memset(poll_rx, 0, SPI_POLL_TEST_SIZE);

    /* find SPI device */
    spi_dev = (struct rt_spi_device *)rt_device_find(SPI_DEV_NAME);
    if (spi_dev == RT_NULL) {
        rt_kprintf("[Poll] SPI device %s not found!\n", SPI_DEV_NAME);
        return;
    }

    /* Write Enable */
    rt_spi_transfer(spi_dev, &cmd_wren, id_buf, 1);

    /* Erase Sector */
    rt_spi_transfer(spi_dev, erase_cmd, id_buf, 4);
    rt_thread_mdelay(100);  /* wait for erase to complete */

    /* Write Enable */
    rt_spi_transfer(spi_dev, &cmd_wren, id_buf, 1);

    /* Page Program, one full page */
    start = rt_tick_get();
    rt_spi_send_then_send(spi_dev, write_cmd, 4, poll_tx, SPI_POLL_TEST_SIZE);
    end = rt_tick_get();
    rt_kprintf("[Poll] SPI Write %d bytes: %d ticks\n", SPI_POLL_TEST_SIZE, end - start);
    rt_thread_mdelay(50);   /* wait for write to complete */

    /* Read back */
    start = rt_tick_get();
    rt_spi_send_then_recv(spi_dev, read_cmd, 4, poll_rx, SPI_POLL_TEST_SIZE);
    end = rt_tick_get();
    rt_kprintf("[Poll] SPI Read %d bytes: %d ticks\n", SPI_POLL_TEST_SIZE, end - start);

    /* Verify data */
    if (memcmp(poll_rx, poll_tx, SPI_POLL_TEST_SIZE) == 0) {
        rt_kprintf("[Poll] SPI Flash test passed!\n");
    } else {
        rt_kprintf("[Poll] SPI Flash test failed!\n");
        rt_kprintf("[Poll] TX: ");
        for (i = 0; i < SPI_POLL_TEST_SIZE; i++) {
            rt_kprintf("%02X ", poll_tx[i]);
        }
        rt_kprintf("\n[Poll] RX: ");
        for (i = 0; i < SPI_POLL_TEST_SIZE; i++) {
            rt_kprintf("%02X ", poll_rx[i]);
        }
        rt_kprintf("\n");
    }
}

MSH_CMD_EXPORT(spi_poll_sample, SPI Flash polling mode test);
#endif
