/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string.h>

/* Test feature switches - comment out to disable */
#define GD32_I2C_EEPROM_TEST
#define GD32_SPI_TEST
#define GD32_UART_TEST
#define GD32_GPIO_EXTI_TEST

/* defined the LED pins according to schematic */
#define LED1_PIN    GET_PIN(D, 9)    /* LED1 on PD9 */
#define LED2_PIN    GET_PIN(D, 10)   /* LED2 on PD10 */
#define LED3_PIN    GET_PIN(D, 11)   /* LED3 on PD11 */
#define LED4_PIN    GET_PIN(D, 12)   /* LED4 on PD12 */

#ifdef GD32_GPIO_EXTI_TEST
#define WAKEUP_PIN_NUM   GET_PIN(A, 0)
#define USER_PIN         GET_PIN(B, 0)
#endif

#ifdef GD32_I2C_EEPROM_TEST
#include "at24cxx.h"
#define BUFFER_SIZE    256
#define I2C_SERIAL     "hwi2c0"
static rt_uint8_t i2c_buffer_write[BUFFER_SIZE];
static rt_uint8_t i2c_buffer_read[BUFFER_SIZE];
static uint8_t i2c_24c02_test(void);
#endif

#ifdef GD32_SPI_TEST
#define SPI_BUS_NAME     "spi0"
#define SPI_DEV_NAME     "spi00"
#define SPI_CS_PIN       GET_PIN(D, 8)

static uint8_t send_id = 0x9F;
static uint8_t WREN = 0x06;
static uint8_t recei_id[4] = {0};
static uint8_t tx_buffer[200];
static uint8_t rx_buffer[200];

static void spi_sample(void);
#endif

#ifdef GD32_UART_TEST
#define SAMPLE_UART_NAME    "uart0"
static struct rt_semaphore rx_sem;
static rt_device_t serial;
static int uart_sample(int argc, char *argv[]);
#endif

#ifdef GD32_GPIO_EXTI_TEST
static void pin_irq_sample(void);
#endif

int main(void)
{
    int count = 1;

    /* set LED pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);

    rt_kprintf("Hello GD32M531R-EVAL!\n");
    rt_kprintf("RT-Thread BSP adaptation successful!\n");
    rt_kprintf("System Clock: %d Hz\n", SystemCoreClock);

#ifdef GD32_I2C_EEPROM_TEST
    rt_kprintf("\n--- I2C EEPROM Test ---\n");
    if (i2c_24c02_test() != 0)
    {
        rt_kprintf("I2C-AT24C02 test passed!\n");
    }
    else
    {
        rt_kprintf("I2C-AT24C02 test failed!\n");
    }
#endif

#ifdef GD32_SPI_TEST
    rt_kprintf("\n--- SPI Flash Test ---\n");
    spi_sample();
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

        /* turn on LED3 */
        rt_pin_write(LED3_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        /* turn off LED3 */
        rt_pin_write(LED3_PIN, PIN_LOW);

        /* turn on LED4 */
        rt_pin_write(LED4_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        /* turn off LED4 */
        rt_pin_write(LED4_PIN, PIN_LOW);
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
    if (ati2c == RT_NULL)
    {
        rt_kprintf("Failed to find EEPROM device!\n");
        return 0;
    }
    rt_kprintf("Found EEPROM device on %s\n", I2C_SERIAL);

    /* initialize write buffer */
    for (i = 0; i < BUFFER_SIZE; i++)
    {
        i2c_buffer_write[i] = i + 8;
    }

    rt_kprintf("I2C-AT24C02 writing %d bytes...\n", BUFFER_SIZE);
    if (at24cxx_page_write(ati2c, 0x00, i2c_buffer_write, BUFFER_SIZE) != RT_EOK)
    {
        rt_kprintf("I2C-AT24C02 write failed!\n");
        return 0;
    }
    rt_kprintf("I2C-AT24C02 write complete.\n");

    rt_kprintf("I2C-AT24C02 reading %d bytes...\n", BUFFER_SIZE);
    if (at24cxx_page_read(ati2c, 0x00, i2c_buffer_read, BUFFER_SIZE) != RT_EOK)
    {
        rt_kprintf("I2C-AT24C02 read failed!\n");
        return 0;
    }
    rt_kprintf("I2C-AT24C02 read complete.\n");

    /* compare read buffer with write buffer */
    for (i = 0; i < BUFFER_SIZE; i++)
    {
        if (i2c_buffer_read[i] != i2c_buffer_write[i])
        {
            rt_kprintf("Data mismatch at offset %d: wrote 0x%02X, read 0x%02X\n",
                       i, i2c_buffer_write[i], i2c_buffer_read[i]);
            return 0;
        }
    }

    return 1;
}
#endif

#ifdef GD32_SPI_TEST
/**
 * @brief SPI Flash (W25Q128) read/write test
 */
static void spi_sample(void)
{
    uint8_t erase_cmd[4] = {0x20, 0x00, 0x00, 0x04};
    uint8_t write_cmd[4] = {0x02, 0x00, 0x00, 0x04};
    uint8_t read_cmd[4] = {0x03, 0x00, 0x00, 0x04};
    struct rt_spi_device *spi_dev = RT_NULL;
    struct rt_spi_configuration cfg;
    int i;

    /* initialize tx buffer with test pattern */
    for (i = 0; i < 200; i++)
    {
        tx_buffer[i] = i;
    }

    spi_dev = (struct rt_spi_device *)rt_device_find(SPI_DEV_NAME);
    if (spi_dev == RT_NULL)
    {
        struct rt_spi_device *attach_dev;

        attach_dev = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
        if (attach_dev == RT_NULL)
        {
            rt_kprintf("SPI device alloc failed!\n");
            return;
        }

        if (rt_spi_bus_attach_device_cspin(attach_dev, SPI_DEV_NAME, SPI_BUS_NAME, SPI_CS_PIN, RT_NULL) != RT_EOK)
        {
            rt_free(attach_dev);
        }

        spi_dev = (struct rt_spi_device *)rt_device_find(SPI_DEV_NAME);
        if (spi_dev == RT_NULL)
        {
            rt_kprintf("SPI device %s not found!\n", SPI_DEV_NAME);
            return;
        }
    }

    /* configure SPI */
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    cfg.max_hz = 2 * 1000 * 1000;
    rt_spi_configure(spi_dev, &cfg);

    /* Read Flash ID */
    rt_spi_send_then_recv(spi_dev, &send_id, 1, recei_id, 3);
    rt_kprintf("SPI Flash ID: 0x%02X 0x%02X 0x%02X\n", recei_id[0], recei_id[1], recei_id[2]);

    /* Write Enable */
    rt_spi_transfer(spi_dev, &WREN, recei_id, 1);

    /* Erase Sector */
    rt_spi_transfer(spi_dev, erase_cmd, recei_id, 4);
    rt_thread_mdelay(100);

    /* Write Enable */
    rt_spi_transfer(spi_dev, &WREN, recei_id, 1);

    /* Write to Page */
    rt_spi_send_then_send(spi_dev, write_cmd, 4, tx_buffer, 200);
    rt_thread_mdelay(50);

    /* Read Data */
    rt_spi_send_then_recv(spi_dev, read_cmd, 4, rx_buffer, 200);
    rt_thread_mdelay(20);

    /* Verify data */
    if (memcmp(rx_buffer, tx_buffer, 200) == 0)
    {
        rt_kprintf("SPI Flash test passed!\n");
    }
    else
    {
        rt_kprintf("SPI Flash test failed!\n");
    }
}

MSH_CMD_EXPORT(spi_sample, SPI Flash test sample);
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

    while (1)
    {
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {
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
    rt_thread_t thread = RT_NULL;

    if (argc == 2)
    {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
    }

    serial = rt_device_find(uart_name);
    if (!serial)
    {
        rt_kprintf("UART device %s not found!\n", uart_name);
        return RT_ERROR;
    }

    ret = rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    if (ret != RT_EOK)
    {
        return ret;
    }

    ret = rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    if (ret != RT_EOK)
    {
        goto err_detach_sem;
    }

    ret = rt_device_set_rx_indicate(serial, uart_input);
    if (ret != RT_EOK)
    {
        goto err_close_device;
    }

    rt_device_write(serial, 0, str, (sizeof(str) - 1));

    thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
        rt_kprintf("UART %s echo test started. Type to see echo.\n", uart_name);
        return RT_EOK;
    }

    ret = RT_ERROR;

err_close_device:
    rt_device_set_rx_indicate(serial, RT_NULL);
    rt_device_close(serial);
err_detach_sem:
    rt_sem_detach(&rx_sem);
    return ret;
}
#endif

#ifdef GD32_GPIO_EXTI_TEST
void wakeup_key_pin_cb(void *args)
{
    rt_kprintf("Wakeup key pin pressed!\n");
}

void user_key_pin_cb(void *args)
{
    rt_kprintf("User key pin pressed!\n");
}

static void pin_irq_sample(void)
{
    /* Wakeup key interrupt */
    rt_pin_mode(WAKEUP_PIN_NUM, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(WAKEUP_PIN_NUM, PIN_IRQ_MODE_FALLING, wakeup_key_pin_cb, RT_NULL);
    rt_pin_irq_enable(WAKEUP_PIN_NUM, PIN_IRQ_ENABLE);

    /* User key interrupt */
    rt_pin_mode(USER_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(USER_PIN, PIN_IRQ_MODE_FALLING, user_key_pin_cb, RT_NULL);
    rt_pin_irq_enable(USER_PIN, PIN_IRQ_ENABLE);

    rt_kprintf("GPIO EXTI initialized. Press Wakeup(PA0) or User(PB0) key.\n");
}
#endif