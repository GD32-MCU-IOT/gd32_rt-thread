/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 * 2026-03-05     RT-Thread    simplified test cases
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

/* LED pins - GD32F527I-EVAL board (per schematic) */
#define LED1_PIN    GET_PIN(F, 7)
#define LED2_PIN    GET_PIN(F, 8)
#define LED3_PIN    GET_PIN(E, 3)
#define LED4_PIN    GET_PIN(E, 2)

#ifdef GD32_GPIO_EXTI_TEST
#define WAKEUP_PIN  GET_PIN(A, 0)
#define TAMPER_PIN  GET_PIN(C, 13)
#endif

#ifdef GD32_I2C_EEPROM_TEST
#include "at24cxx.h"
#define BUFFER_SIZE    256
#define I2C_SERIAL     "hwi2c0"
static uint8_t i2c_24c02_test(void);
#endif

#if defined(GD32_SPI_POLL_TEST) || defined(GD32_SPI_DMA_TEST)
#define SPI_BUS_NAME     "spi5"
#define SPI_DEV_NAME     "spi05"
#define SPI_CS_PIN       GET_PIN(I, 8)

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
static void pin_irq_sample(void);
#endif

int main(void)
{
    /* set LED pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);

    rt_kprintf("\n\rHello GD32F527I-EVAL!\n\r");
    rt_kprintf("RT-Thread BSP adaptation successful!\n\r");
    rt_kprintf("System Clock: %d Hz\n\r", SystemCoreClock);

#ifdef GD32_I2C_EEPROM_TEST
    rt_kprintf("\n\r--- I2C EEPROM Test ---\n\r");
    if (i2c_24c02_test() != 0) {
        rt_kprintf("I2C-AT24C02 test passed!\n\r");
    } else {
        rt_kprintf("I2C-AT24C02 test failed!\n\r");
    }
#endif

#if defined(GD32_SPI_POLL_TEST) || defined(GD32_SPI_DMA_TEST)
    rt_kprintf("\n\r--- SPI Flash Test ---\n\r");
    spi_init_device();
#endif

#ifdef GD32_SPI_POLL_TEST
    spi_poll_sample();
#endif

#ifdef GD32_SPI_DMA_TEST
    spi_dma_sample();
#endif

#ifdef GD32_UART_TEST
    rt_kprintf("\n\r--- UART Test ---\n\r");
    uart_sample(0, 0);
#endif

#ifdef GD32_GPIO_EXTI_TEST
    rt_kprintf("\n\r--- GPIO EXTI Test ---\n\r");
    pin_irq_sample();
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
static uint8_t i2c_24c02_test(void)
{
    at24cxx_device_t ati2c;
    uint16_t i;
    uint8_t i2c_buffer_write[BUFFER_SIZE];
    uint8_t i2c_buffer_read[BUFFER_SIZE];

    ati2c = at24cxx_init(I2C_SERIAL, 0x00);
    if (ati2c == RT_NULL) {
        rt_kprintf("I2C bus %s not found!\n\r", I2C_SERIAL);
        return 0;
    }
    rt_kprintf("Found EEPROM on I2C bus: %s\n\r", I2C_SERIAL);

    /* initialize write buffer */
    for (i = 0; i < BUFFER_SIZE; i++) {
        i2c_buffer_write[i] = i + 8;
    }

    /* Write data */
    rt_kprintf("Writing %d bytes...\n\r", BUFFER_SIZE);
    if (at24cxx_page_write(ati2c, 0x00, i2c_buffer_write, BUFFER_SIZE) != RT_EOK) {
        rt_kprintf("Write failed!\n\r");
        return 0;
    }
    rt_kprintf("Write complete.\n\r");

    /* Read data */
    rt_kprintf("Reading %d bytes...\n\r", BUFFER_SIZE);
    if (at24cxx_page_read(ati2c, 0x00, i2c_buffer_read, BUFFER_SIZE) != RT_EOK) {
        rt_kprintf("Read failed!\n\r");
        return 0;
    }
    rt_kprintf("Read complete.\n\r");

    /* Compare */
    if (memcmp(i2c_buffer_read, i2c_buffer_write, BUFFER_SIZE) == 0) {
        return 1;
    }
    rt_kprintf("Data mismatch!\n\r");
    return 0;
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
        rt_kprintf("SPI device attach failed!\n\r");
        return;
    }

    /* find SPI device */
    spi_dev = (struct rt_spi_device *)rt_device_find(SPI_DEV_NAME);
    if (spi_dev == RT_NULL) {
        rt_kprintf("SPI device %s not found!\n\r", SPI_DEV_NAME);
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
    rt_kprintf("SPI Flash ID: 0x%02X 0x%02X 0x%02X\n\r", id_buf[0], id_buf[1], id_buf[2]);
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
        rt_kprintf("[Poll] SPI device %s not found!\n\r", SPI_DEV_NAME);
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
    rt_kprintf("[Poll] SPI Write %d bytes: %d ticks\n\r", SPI_POLL_TEST_SIZE, end - start);
    rt_thread_mdelay(50);   /* wait for write to complete */

    /* Read data using polling mode */
    start = rt_tick_get();
    rt_spi_send_then_recv(spi_dev, read_cmd, 4, poll_rx, SPI_POLL_TEST_SIZE);
    end = rt_tick_get();
    rt_kprintf("[Poll] SPI Read %d bytes: %d ticks\n\r", SPI_POLL_TEST_SIZE, end - start);

    /* Verify data */
    if (memcmp(poll_rx, poll_tx, SPI_POLL_TEST_SIZE) == 0) {
        rt_kprintf("[Poll] SPI Flash test passed!\n\r");
    } else {
        rt_kprintf("[Poll] SPI Flash test failed!\n\r");
        rt_kprintf("[Poll] TX: ");
        for (i = 0; i < SPI_POLL_TEST_SIZE; i++) {
            rt_kprintf("%02X ", poll_tx[i]);
        }
        rt_kprintf("\n\r[Poll] RX: ");
        for (i = 0; i < SPI_POLL_TEST_SIZE; i++) {
            rt_kprintf("%02X ", poll_rx[i]);
        }
        rt_kprintf("\n\r");
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
#ifndef BSP_SPI5_USING_DMA
    rt_kprintf("[DMA] Warning: BSP_SPI5_USING_DMA not enabled!\n\r");
    rt_kprintf("[DMA] Test will use polling mode instead.\n\r");
    rt_kprintf("[DMA] Enable 'Enable SPI5 DMA' in menuconfig to use DMA.\n\r\n\r");
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
        rt_kprintf("[DMA] SPI device %s not found!\n\r", SPI_DEV_NAME);
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
#ifdef BSP_SPI5_USING_DMA
    rt_kprintf("[DMA] SPI Write %d bytes: %d ticks\n\r", SPI_DMA_TEST_SIZE, end - start);
#else
    rt_kprintf("[Poll] SPI Write %d bytes: %d ticks\n\r", SPI_DMA_TEST_SIZE, end - start);
#endif
    rt_thread_mdelay(50);   /* wait for write to complete */

    /* Read data using DMA mode */
    start = rt_tick_get();
    rt_spi_send_then_recv(spi_dev, read_cmd, 4, rx_buffer, SPI_DMA_TEST_SIZE);
    end = rt_tick_get();
#ifdef BSP_SPI5_USING_DMA
    rt_kprintf("[DMA] SPI Read %d bytes: %d ticks\n\r", SPI_DMA_TEST_SIZE, end - start);
#else
    rt_kprintf("[Poll] SPI Read %d bytes: %d ticks\n\r", SPI_DMA_TEST_SIZE, end - start);
#endif

    /* Verify data */
    if (memcmp(rx_buffer, tx_buffer, SPI_DMA_TEST_SIZE) == 0) {
#ifdef BSP_SPI5_USING_DMA
        rt_kprintf("[DMA] SPI Flash test passed! (DMA mode)\n\r");
#else
        rt_kprintf("[Poll] SPI Flash test passed! (DMA not enabled)\n\r");
#endif
    } else {
        rt_kprintf("[DMA] SPI Flash test failed!\n\r");
        rt_kprintf("[DMA] First 16 bytes - TX: ");
        for (i = 0; i < 16; i++) {
            rt_kprintf("%02X ", tx_buffer[i]);
        }
        rt_kprintf("\n\r[DMA] First 16 bytes - RX: ");
        for (i = 0; i < 16; i++) {
            rt_kprintf("%02X ", rx_buffer[i]);
        }
        rt_kprintf("\n\r");
    }
}

MSH_CMD_EXPORT(spi_dma_sample, SPI Flash DMA mode test);
#endif

#ifdef GD32_UART_TEST
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
        rt_device_write(serial, 0, &ch, 1);
    }
}

static int uart_sample(int argc, char *argv[])
{
    char uart_name[RT_NAME_MAX];
    char str[] = "Hello RT-Thread UART Test!\r\n";

    if (argc == 2) {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    } else {
        rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
    }

    serial = rt_device_find(uart_name);
    if (!serial) {
        rt_kprintf("UART device %s not found!\n\r", uart_name);
        return RT_ERROR;
    }

    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    rt_device_set_rx_indicate(serial, uart_input);
    rt_device_write(serial, 0, str, (sizeof(str) - 1));

    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL) {
        rt_thread_startup(thread);
        rt_kprintf("UART %s echo test started.\n\r", uart_name);
    }

    return RT_EOK;
}

MSH_CMD_EXPORT(uart_sample, UART echo test sample);
#endif

#ifdef GD32_GPIO_EXTI_TEST
void wakeup_key_pin_cb(void *args)
{
    rt_kprintf("Wakeup key pressed!\n\r");
}

void tamper_key_pin_cb(void *args)
{
    rt_kprintf("Tamper key pressed!\n\r");
}

static void pin_irq_sample(void)
{
    rt_pin_mode(WAKEUP_PIN, PIN_MODE_INPUT_PULLDOWN);
    rt_pin_attach_irq(WAKEUP_PIN, PIN_IRQ_MODE_RISING, wakeup_key_pin_cb, RT_NULL);
    rt_pin_irq_enable(WAKEUP_PIN, PIN_IRQ_ENABLE);

    rt_pin_mode(TAMPER_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(TAMPER_PIN, PIN_IRQ_MODE_FALLING, tamper_key_pin_cb, RT_NULL);
    rt_pin_irq_enable(TAMPER_PIN, PIN_IRQ_ENABLE);

    rt_kprintf("GPIO EXTI ready. Press Wakeup(PA0) or Tamper(PC13) key.\n\r");
}
#endif
