/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 * 2026-07-13     RT-Thread    simplified sample tests for new driver framework
 */

#include <stdio.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string.h>

/* Test feature switches - comment out to disable */
#define GD32_I2C_TEST
#define GD32_SPI_TEST
#define GD32_UART_TEST
#define GD32_GPIO_EXTI_TEST

/* defined the LED pins according to schematic */
#define LED1_PIN    GET_PIN(D, 4)   /* LED1 on PD4 */
#define LED2_PIN    GET_PIN(D, 5)   /* LED2 on PD5 */
#define LED3_PIN    GET_PIN(G, 3)   /* LED3 on PG3 */

#ifdef GD32_GPIO_EXTI_TEST
#define WAKEUP_PIN_NUM   GET_PIN(A, 0)   /* K1 */
#define TAMPER_PIN       GET_PIN(C, 13)  /* K2 */
#endif

#ifdef GD32_I2C_TEST
#define I2C_BUS_NAME     "hwi2c0"
#define I2C_SLAVE_ADDR   0x50   /* typical AT24Cxx EEPROM address */
static void i2c_sample(void);
#endif

#ifdef GD32_SPI_TEST
#define SPI_BUS_NAME     "spi5"
#define SPI_DEV_NAME     "spi50"
#define SPI_CS_PIN       GET_PIN(G, 9)   /* SPI5 CS on PG9 */

static uint8_t send_id = 0x9F;
static uint8_t recei_id[4] = {0};

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
    /* set LED pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);

    rt_kprintf("Hello GD32450Z-EVAL!\n");
    rt_kprintf("RT-Thread BSP adaptation successful!\n");
    rt_kprintf("System Clock: %d Hz\n", SystemCoreClock);

#ifdef GD32_I2C_TEST
    rt_kprintf("\n--- I2C0 Test ---\n");
    i2c_sample();
#endif

#ifdef GD32_SPI_TEST
    rt_kprintf("\n--- SPI5 Test ---\n");
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

    while (1)
    {
        /* turn on LED1 */
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(250);

        /* turn off LED1, turn on LED2 */
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(250);

        /* turn off LED2, turn on LED3 */
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_pin_write(LED3_PIN, PIN_HIGH);
        rt_thread_mdelay(250);

        /* turn off LED3 */
        rt_pin_write(LED3_PIN, PIN_LOW);
        rt_thread_mdelay(250);
    }

    return RT_EOK;
}

#ifdef GD32_I2C_TEST
/**
 * @brief Simple I2C0 bus probe/read-write test (no extra package required)
 */
static void i2c_sample(void)
{
    struct rt_i2c_bus_device *bus;
    struct rt_i2c_msg msgs[2];
    rt_uint8_t reg_addr = 0x00;
    rt_uint8_t tx_buf[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    rt_uint8_t rx_buf[8] = {0};

    bus = rt_i2c_bus_device_find(I2C_BUS_NAME);
    if (bus == RT_NULL) {
        rt_kprintf("I2C bus %s not found!\n", I2C_BUS_NAME);
        return;
    }
    rt_kprintf("Found I2C bus %s\n", I2C_BUS_NAME);

    /* write: [reg_addr][data...] */
    {
        rt_uint8_t wr_buf[1 + sizeof(tx_buf)];
        wr_buf[0] = reg_addr;
        rt_memcpy(&wr_buf[1], tx_buf, sizeof(tx_buf));

        msgs[0].addr  = I2C_SLAVE_ADDR;
        msgs[0].flags = RT_I2C_WR;
        msgs[0].buf   = wr_buf;
        msgs[0].len   = sizeof(wr_buf);

        if (rt_i2c_transfer(bus, msgs, 1) != 1) {
            rt_kprintf("I2C0 write failed (no device at 0x%02X?)\n", I2C_SLAVE_ADDR);
            return;
        }
    }
    rt_thread_mdelay(10);

    /* write reg addr, then read back */
    msgs[0].addr  = I2C_SLAVE_ADDR;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &reg_addr;
    msgs[0].len   = 1;

    msgs[1].addr  = I2C_SLAVE_ADDR;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = rx_buf;
    msgs[1].len   = sizeof(rx_buf);

    if (rt_i2c_transfer(bus, msgs, 2) != 2) {
        rt_kprintf("I2C0 read failed!\n");
        return;
    }

    if (rt_memcmp(tx_buf, rx_buf, sizeof(tx_buf)) == 0) {
        rt_kprintf("I2C0 write/read test passed!\n");
    } else {
        rt_kprintf("I2C0 write/read test failed (data mismatch)!\n");
    }
}
#endif

#ifdef GD32_SPI_TEST
/**
 * @brief SPI5 basic transfer test (reads JEDEC ID from whatever is on CS PG9)
 */
static void spi_sample(void)
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

    /* Read Flash-style JEDEC ID (0x9F) */
    rt_spi_send_then_recv(spi_dev, &send_id, 1, recei_id, 3);
    rt_kprintf("SPI5 ID: 0x%02X 0x%02X 0x%02X\n", recei_id[0], recei_id[1], recei_id[2]);
}

MSH_CMD_EXPORT(spi_sample, SPI5 basic test sample);
#endif

#ifdef GD32_UART_TEST
/**
 * @brief UART receive callback
 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);
    return RT_EOK;
}

/**
 * @brief UART receive thread entry
 */
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

/**
 * @brief UART echo test sample
 */
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
/**
 * @brief Wakeup key interrupt callback
 */
void wakeup_key_pin_cb(void *args)
{
    rt_kprintf("Wakeup key pin pressed!\n");
}

/**
 * @brief Tamper key interrupt callback
 */
void tamper_key_pin_cb(void *args)
{
    rt_kprintf("Tamper key pin pressed!\n");
}

/**
 * @brief GPIO external interrupt sample
 */
static void pin_irq_sample(void)
{
    /* Wakeup key interrupt */
    rt_pin_mode(WAKEUP_PIN_NUM, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(WAKEUP_PIN_NUM, PIN_IRQ_MODE_FALLING, wakeup_key_pin_cb, RT_NULL);
    rt_pin_irq_enable(WAKEUP_PIN_NUM, PIN_IRQ_ENABLE);

    /* Tamper key interrupt */
    rt_pin_mode(TAMPER_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(TAMPER_PIN, PIN_IRQ_MODE_FALLING, tamper_key_pin_cb, RT_NULL);
    rt_pin_irq_enable(TAMPER_PIN, PIN_IRQ_ENABLE);

    rt_kprintf("GPIO EXTI initialized. Press K1(PA0) or K2(PC13) key.\n");
}
#endif
