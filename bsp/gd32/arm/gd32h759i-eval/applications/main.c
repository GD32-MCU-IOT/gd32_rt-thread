/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-03-17     RT-Thread    first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string.h>

/* Test Feature Switches - comment out to disable */
#define GD32_I2C_EEPROM_TEST
#define GD32_SPI_POLL_TEST
#define GD32_SPI_DMA_TEST
#define GD32_UART_TEST
#define GD32_GPIO_EXTI_TEST

/* GD32H759I-EVAL has 2 LEDs */
#define LED1_PIN    GET_PIN(F, 10)   /* LED1 on PF10 */
#define LED2_PIN    GET_PIN(A, 6)    /* LED2 on PA6  */

#ifdef GD32_I2C_EEPROM_TEST
#include "at24cxx.h"
#define BUFFER_SIZE    256
#define I2C_SERIAL     "hwi2c1"
rt_uint8_t i2c_buffer_write[BUFFER_SIZE];
rt_uint8_t i2c_buffer_read[BUFFER_SIZE];
static uint8_t i2c_24c02_test(void);
#endif

#if defined(GD32_SPI_POLL_TEST) || defined(GD32_SPI_DMA_TEST)
#define SPI_BUS_NAME     "spi3"
#define SPI_DEV_NAME     "spi03"
#define SPI_CS_PIN       GET_PIN(F, 6)

static uint8_t cmd_read_id = 0x9F;
static uint8_t cmd_wren = 0x06;
static uint8_t id_buf[4] = {0};

static void spi_init_device(void);
#endif

#ifdef GD32_SPI_POLL_TEST
/* SPI polling mode test - transfer below BSP_SPI_DMA_TRANS_MIN_LEN */
#define SPI_POLL_TEST_SIZE    8
static void spi_poll_sample(void);
#endif

#ifdef GD32_SPI_DMA_TEST
/* SPI DMA mode test - transfer >= BSP_SPI_DMA_TRANS_MIN_LEN */
#define SPI_DMA_TEST_SIZE     200
static uint8_t tx_buffer[SPI_DMA_TEST_SIZE];
static uint8_t rx_buffer[SPI_DMA_TEST_SIZE];
static void spi_dma_sample(void);
#endif

#ifdef GD32_UART_TEST
#define SAMPLE_UART_NAME    "uart1"
static struct rt_semaphore rx_sem;
static rt_device_t serial;
static int uart_sample(int argc, char *argv[]);
#endif

#ifdef GD32_GPIO_EXTI_TEST
/* GD32H759I-EVAL keys */
#define WAKEUP_PIN_NUM   GET_PIN(A, 0)
#define TAMPER_PIN       GET_PIN(C, 13)
#define USER_PIN         GET_PIN(F, 8)

static void pin_irq_sample(void);
#endif

int main(void)
{
    int count = 1;

    /* set LED pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);

    rt_kprintf("Hello GD32H759I!\n");
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

#if defined(GD32_SPI_POLL_TEST) || defined(GD32_SPI_DMA_TEST)
    rt_kprintf("\n--- SPI Flash Test ---\n");
    spi_init_device();
#endif

#ifdef GD32_SPI_POLL_TEST
    spi_poll_sample();
#endif

#ifdef GD32_SPI_DMA_TEST
    spi_dma_sample();
#endif

#ifdef GD32_UART_TEST
    rt_kprintf("\n--- UART Test ---\n");
    uart_sample(0, 0);
#endif

#ifdef GD32_GPIO_EXTI_TEST
    rt_kprintf("\n--- GPIO EXTI Test ---\n");
    pin_irq_sample();
#endif

    while (count++)
    {
        /* turn on LED1 */
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        /* turn off LED1 */
        rt_pin_write(LED1_PIN, PIN_LOW);

        /* turn on LED2 */
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        /* turn off LED2 */
        rt_pin_write(LED2_PIN, PIN_LOW);
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

#if defined(GD32_SPI_POLL_TEST) || defined(GD32_SPI_DMA_TEST)
/**
 * @brief Initialize SPI device - shared by polling and DMA tests
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
    spi_dev->bus->owner = spi_dev;

    /* Read Flash ID */
    rt_spi_send_then_recv(spi_dev, &cmd_read_id, 1, id_buf, 3);
    rt_kprintf("SPI Flash ID: 0x%02X 0x%02X 0x%02X\n", id_buf[0], id_buf[1], id_buf[2]);
}
#endif

#ifdef GD32_SPI_POLL_TEST
/**
 * @brief SPI Flash (GD25Q16) polling mode test - transfer < 16 bytes
 */
static void spi_poll_sample(void)
{
    uint8_t erase_cmd[4] = {0x20, 0x00, 0x10, 0x00};   /* Sector Erase at 0x001000 */
    uint8_t write_cmd[4] = {0x02, 0x00, 0x10, 0x00};   /* Page Program at 0x001000 */
    uint8_t read_cmd[4]  = {0x03, 0x00, 0x10, 0x00};   /* Read Data at 0x001000 */
    uint8_t poll_tx[SPI_POLL_TEST_SIZE];
    uint8_t poll_rx[SPI_POLL_TEST_SIZE];

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

    /* Write data using polling mode (< 16 bytes) */
    start = rt_tick_get();
    rt_spi_send_then_send(spi_dev, write_cmd, 4, poll_tx, SPI_POLL_TEST_SIZE);
    end = rt_tick_get();
    rt_kprintf("[Poll] SPI Write %d bytes: %d ticks\n", SPI_POLL_TEST_SIZE, end - start);
    rt_thread_mdelay(50);   /* wait for write to complete */

    /* Read data using polling mode */
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

#ifdef GD32_SPI_DMA_TEST
/**
 * @brief SPI Flash (GD25Q16) DMA mode test - transfer >= 16 bytes
 */
static void spi_dma_sample(void)
{
#ifndef BSP_SPI3_USING_DMA
    rt_kprintf("[DMA] Warning: BSP_SPI3_USING_DMA not enabled!\n");
    rt_kprintf("[DMA] Test will use polling mode instead.\n");
    rt_kprintf("[DMA] Enable 'Enable SPI3 DMA' in menuconfig to use DMA.\n\n");
#endif

    uint8_t erase_cmd[4] = {0x20, 0x00, 0x00, 0x00};   /* Sector Erase at 0x000000 */
    uint8_t write_cmd[4] = {0x02, 0x00, 0x00, 0x00};   /* Page Program at 0x000000 */
    uint8_t read_cmd[4]  = {0x03, 0x00, 0x00, 0x00};   /* Read Data at 0x000000 */

    struct rt_spi_device *spi_dev = RT_NULL;
    rt_tick_t start, end;
    int i;

    /* initialize tx buffer with test pattern */
    for (i = 0; i < SPI_DMA_TEST_SIZE; i++) {
        tx_buffer[i] = i;
    }
    rt_memset(rx_buffer, 0, SPI_DMA_TEST_SIZE);

    /* find SPI device */
    spi_dev = (struct rt_spi_device *)rt_device_find(SPI_DEV_NAME);
    if (spi_dev == RT_NULL) {
        rt_kprintf("[DMA] SPI device %s not found!\n", SPI_DEV_NAME);
        return;
    }

    /* Write Enable */
    rt_spi_transfer(spi_dev, &cmd_wren, id_buf, 1);

    /* Erase Sector */
    rt_spi_transfer(spi_dev, erase_cmd, id_buf, 4);
    rt_thread_mdelay(100);  /* wait for erase to complete */

    /* Write Enable */
    rt_spi_transfer(spi_dev, &cmd_wren, id_buf, 1);

    /* Write data using DMA mode (>= 16 bytes) */
    start = rt_tick_get();
    rt_spi_send_then_send(spi_dev, write_cmd, 4, tx_buffer, SPI_DMA_TEST_SIZE);
    end = rt_tick_get();
#ifdef BSP_SPI3_USING_DMA
    rt_kprintf("[DMA] SPI Write %d bytes: %d ticks\n", SPI_DMA_TEST_SIZE, end - start);
#else
    rt_kprintf("[Poll] SPI Write %d bytes: %d ticks\n", SPI_DMA_TEST_SIZE, end - start);
#endif
    rt_thread_mdelay(50);   /* wait for write to complete */

    /* Read data using DMA mode */
    start = rt_tick_get();
    rt_spi_send_then_recv(spi_dev, read_cmd, 4, rx_buffer, SPI_DMA_TEST_SIZE);
    end = rt_tick_get();
#ifdef BSP_SPI3_USING_DMA
    rt_kprintf("[DMA] SPI Read %d bytes: %d ticks\n", SPI_DMA_TEST_SIZE, end - start);
#else
    rt_kprintf("[Poll] SPI Read %d bytes: %d ticks\n", SPI_DMA_TEST_SIZE, end - start);
#endif

    /* Verify data */
    if (memcmp(rx_buffer, tx_buffer, SPI_DMA_TEST_SIZE) == 0) {
#ifdef BSP_SPI3_USING_DMA
        rt_kprintf("[DMA] SPI Flash test passed! (DMA mode)\n");
#else
        rt_kprintf("[Poll] SPI Flash test passed! (DMA not enabled)\n");
#endif
    } else {
        rt_kprintf("[DMA] SPI Flash test failed!\n");
        rt_kprintf("[DMA] First 16 bytes - TX: ");
        for (i = 0; i < 16; i++) {
            rt_kprintf("%02X ", tx_buffer[i]);
        }
        rt_kprintf("\n[DMA] First 16 bytes - RX: ");
        for (i = 0; i < 16; i++) {
            rt_kprintf("%02X ", rx_buffer[i]);
        }
        rt_kprintf("\n");
    }
}

MSH_CMD_EXPORT(spi_dma_sample, SPI Flash DMA mode test);
#endif

#ifdef GD32_UART_TEST
/* receive callback */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

static void serial_thread_entry(void *parameter)
{
    char ch;

    while (1) {
        while (rt_device_read(serial, -1, &ch, 1) != 1) {
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        }
        /* echo the received character */
        rt_device_write(serial, 0, &ch, 1);
    }
}

static int uart_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    char uart_name[RT_NAME_MAX];
    char str[] = "Hello RT-Thread UART Test!\r\n";

    if (argc == 2) {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    } else {
        rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
    }

    serial = rt_device_find(uart_name);
    if (!serial) {
        rt_kprintf("UART device %s not found!\n", uart_name);
        return RT_ERROR;
    }

    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    rt_device_set_rx_indicate(serial, uart_input);
    rt_device_write(serial, 0, str, (sizeof(str) - 1));

    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL) {
        rt_thread_startup(thread);
        rt_kprintf("UART %s echo test started. Type to see echo.\n", uart_name);
    } else {
        ret = RT_ERROR;
    }

    return ret;
}

MSH_CMD_EXPORT(uart_sample, UART echo test sample);
#endif

#ifdef GD32_GPIO_EXTI_TEST

void wakeup_key_pin_cb(void *args)
{
    rt_kprintf("Wakeup key pin pressed!\n");
}

void tamper_key_pin_cb(void *args)
{
    rt_kprintf("Tamper key pin pressed!\n");
}

void user_key_pin_cb(void *args)
{
    rt_kprintf("User key pin pressed!\n");
}

static void pin_irq_sample(void)
{
    /* Wakeup key interrupt - PA0 */
    rt_pin_mode(WAKEUP_PIN_NUM, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(WAKEUP_PIN_NUM, PIN_IRQ_MODE_FALLING, wakeup_key_pin_cb, RT_NULL);
    rt_pin_irq_enable(WAKEUP_PIN_NUM, PIN_IRQ_ENABLE);

    /* Tamper key interrupt - PC13 */
    rt_pin_mode(TAMPER_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(TAMPER_PIN, PIN_IRQ_MODE_FALLING, tamper_key_pin_cb, RT_NULL);
    rt_pin_irq_enable(TAMPER_PIN, PIN_IRQ_ENABLE);

    /* User key interrupt - PF8 */
    rt_pin_mode(USER_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(USER_PIN, PIN_IRQ_MODE_FALLING, user_key_pin_cb, RT_NULL);
    rt_pin_irq_enable(USER_PIN, PIN_IRQ_ENABLE);
}
#endif
