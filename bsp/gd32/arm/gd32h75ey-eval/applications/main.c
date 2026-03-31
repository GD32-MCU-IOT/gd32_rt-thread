/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
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

#define GD32_I2C_EEPROM_TEST

/* Note: The h75ey eval board not support SPI flash, if you want to test this function,
 *       please connect the SPI to SPI flash.
 */
//#define GD32_SPI_TEST

#define GD32_UART_TEST
#define GD32_UART_DMA_TEST

#define GD32_GPIO_EXTI_TEST


/* defined the LED pins: LED1 and LED2 */
#define LED1_PIN    GET_PIN(C, 3)   /* LED1 on PC3 */
#define LED2_PIN    GET_PIN(C, 4)   /* LED2 on PC4 */
#define LED3_PIN    GET_PIN(C, 5)   /* LED2 on PC4 */

#ifdef GD32_I2C_EEPROM_TEST
#include "at24cxx.h"
#define BUFFER_SIZE    256
#define I2C_SERIAL     "hwi2c3"
rt_uint8_t buf[16];
rt_uint8_t i2c_buffer_write[BUFFER_SIZE];
rt_uint8_t i2c_buffer_read[BUFFER_SIZE];
uint8_t i2c_24c02_test(void);
#endif

#ifdef GD32_SPI_TEST
#define BUS_NAME     "spi2"
#define SPI_NAME     "spi00"

uint8_t send_id = 0x9F;
uint8_t WREN = 0x06;
uint8_t WRITE = 0x02;
uint8_t READ = 0x03;
uint8_t SE = 0x20;
uint8_t recei_id[4] = {0};
uint8_t  tx_buffer[200];
uint8_t  rx_buffer[200];

static void spi_sample(void);
#endif

#ifdef GD32_UART_TEST
#define SAMPLE_UART_NAME    "uart0"
static struct rt_semaphore  rx_sem;
static rt_device_t serial;

static int uart_sample(int argc, char *argv[]);
#endif

#ifdef GD32_UART_DMA_TEST
/* UART DMA test: DMA RX + DMA TX echo on uart3 */
#define UART_DMA_NAME      "uart3"
#define RX_BUF_SIZE        256
#define TX_BUF_SIZE        256
#define DMA_TX_TIMEOUT     rt_tick_from_millisecond(1000)  /* 1 second timeout */

static struct rt_semaphore uart_dma_rx_sem;
static struct rt_semaphore uart_dma_tx_sem;
static struct rt_mutex uart_dma_tx_mutex;
static rt_device_t uart_dma_serial;
static rt_uint8_t uart_dma_rx_buf[RX_BUF_SIZE];
static rt_uint8_t uart_dma_tx_buf[TX_BUF_SIZE];

/* Initialization flag to prevent re-initialization */
static rt_bool_t uart_dma_initialized = RT_FALSE;

/* Statistics */
static rt_uint32_t total_rx_bytes = 0;
static rt_uint32_t total_tx_bytes = 0;
static rt_uint32_t rx_count = 0;
static rt_uint32_t tx_count = 0;
static rt_uint32_t tx_timeout_count = 0;

/* Forward declarations */
static rt_err_t uart_dma_rx_indicate(rt_device_t dev, rt_size_t size);
static rt_err_t uart_dma_tx_done(rt_device_t dev, void *buffer);
static rt_ssize_t uart_dma_send(const rt_uint8_t *buf, rt_size_t len);
static void uart_dma_thread_entry(void *parameter);
static int uart_dma_sample(int argc, char *argv[]);
#endif

#ifdef GD32_GPIO_EXTI_TEST
#define WAKEUP_PIN_NUM   GET_PIN(A, 0)
#define TAMPER_PIN       GET_PIN(C, 13)

static void pin_irq_sample(void);
#endif

int main(void)
{
    int count = 1;

    /* set LED pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);

    rt_kprintf("Hello GD32H75E!\n");
    rt_kprintf("RT-Thread BSP adaptation successful!\n");
    rt_kprintf("System Clock: %d Hz\n", SystemCoreClock);

#ifdef GD32_I2C_EEPROM_TEST
    struct rt_i2c_bus_device *i2c0_dev;
    i2c0_dev = rt_i2c_bus_device_find(I2C_SERIAL);
    if(i2c_24c02_test() != 0){
        rt_kprintf("I2C-AT24C02 test passed!\n\r");
    }
#endif

#ifdef GD32_SPI_TEST
    spi_sample();
#endif

#ifdef GD32_UART_TEST
    uart_sample(0, 0);
#endif

#ifdef GD32_UART_DMA_TEST
    uart_dma_sample(0, RT_NULL);
#endif

#ifdef GD32_GPIO_EXTI_TEST
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
    }

    return RT_EOK;
}


#ifdef GD32_SPI_TEST

static void spi_sample(void)
{

    uint8_t address[4] = {0x20,00,00,04};
    uint8_t waddress[4] = {0x02,00,00,04};
    uint8_t raddress[4] = {0x03,00,00,04};
    
    static struct rt_spi_device *spi_dev = RT_NULL;
    struct rt_spi_configuration cfg;
    
    for(int i = 0; i < 200; i ++){
            tx_buffer[i] = i;
        }
    
    spi_dev = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    rt_hw_spi_device_attach(BUS_NAME, SPI_NAME, GET_PIN(D, 3));
//    rt_spi_bus_attach_device_cspin(spi_dev, SPI_NAME, BUS_NAME, GET_PIN(A, 4), RT_NULL);

    cfg.data_width = 8;
    cfg.mode   = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    cfg.max_hz =  2 *1000 *1000;

    spi_dev = (struct rt_spi_device *)rt_device_find(SPI_NAME);
    spi_dev->bus->owner = spi_dev;
    if (RT_NULL == spi_dev)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", SPI_NAME);
    }
    rt_spi_configure(spi_dev, &cfg);

    /* READ FLASH ID */
    rt_spi_send_then_recv((struct rt_spi_device *)spi_dev, (uint8_t *)&send_id, 1,(uint8_t *)recei_id, 3);
    rt_kprintf("use rt_spi_transfer_message() read gd25q ID is:%x,%x,%x\n", recei_id[0], recei_id[1],recei_id[2]);

    /* WRITE ENABLE */
    rt_spi_transfer((struct rt_spi_device *)spi_dev, (uint8_t *)&WREN,(uint8_t *)recei_id, 1);

    /* ERASE SECTOR */
    rt_spi_transfer((struct rt_spi_device *)spi_dev, (uint8_t *)address,(uint8_t *)recei_id, 4);
    rt_thread_mdelay(100);

    /* WRITE ENABLE */
    rt_spi_transfer((struct rt_spi_device *)spi_dev, (uint8_t *)&WREN,(uint8_t *)recei_id, 1);

    /* WRITE TO PAGE */
    rt_spi_send_then_send((struct rt_spi_device *)spi_dev, (uint8_t *)waddress, 4,(uint8_t *)tx_buffer, 200);
    rt_thread_mdelay(50);

    /* READ TO BUFFER */
    rt_spi_send_then_recv((struct rt_spi_device *)spi_dev, (uint8_t *)raddress, 4,(uint8_t *)rx_buffer, 200);
    rt_thread_mdelay(20);

    if(0 == memcmp(rx_buffer, tx_buffer, 200)) {
        rt_kprintf("spi flash write and read test success.\r\n");
    } else {
        rt_kprintf("spi flash write and read test failed.\r\n");
    }

}

MSH_CMD_EXPORT(spi_sample, dspi_sample);
#endif

#ifdef GD32_I2C_EEPROM_TEST

uint8_t i2c_24c02_test(void)
{
    at24cxx_device_t ati2c;
    ati2c = at24cxx_init(I2C_SERIAL, 0x00);
    
    if (ati2c != NULL)
    {
       rt_kprintf("\r\n Found eeprom \r\n");
    
    }
    uint16_t i;
    uint8_t i2c_buffer_write[BUFFER_SIZE];
    uint8_t i2c_buffer_read[BUFFER_SIZE];

    rt_kprintf("\r\n I2C-AT24C02 writing...\r\n");

    /* initialize i2c_buffer_write */
    for(i = 0; i < BUFFER_SIZE; i++) {
        i2c_buffer_write[i] = i+8;
    }
    /* EEPROM data write */
    if(at24cxx_page_write(ati2c,0x00,i2c_buffer_write, BUFFER_SIZE) == RT_EOK) {
           rt_kprintf("I2C-AT24C02 Finish writing...\r\n");
    }
    
    rt_kprintf("I2C-AT24C02 reading...\r\n");
    /* EEPROM data read */
    if(at24cxx_page_read(ati2c,0x00,i2c_buffer_read, BUFFER_SIZE) == RT_EOK) {
           rt_kprintf("I2C-AT24C02 Finish reading...\r\n");
    }
    
    /* compare the read buffer and write buffer */
    for(i = 0; i < BUFFER_SIZE; i++) {
        if(i2c_buffer_read[i] != i2c_buffer_write[i]) {
            rt_kprintf("0x%02X ", i2c_buffer_read[i]);
            rt_kprintf("\r\n rr:data read and write aren't matching.\n\r");
            return 0;
        }
    }
    return 1;
}
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

        /* echothe recived ch */
        rt_device_write(serial, 0, &ch, 1);
    }
}

static int uart_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    char uart_name[RT_NAME_MAX];
    char str[] = "hello RT-Thread!\r\n";

    if (argc == 2) {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    } else {
        rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
    }

    serial = rt_device_find(uart_name);
    if (!serial) {
        rt_kprintf("find %s failed!\n", uart_name);
        return RT_ERROR;
    }

    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    rt_device_set_rx_indicate(serial, uart_input);
    rt_device_write(serial, 0, str, (sizeof(str) - 1));

    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);

    if (thread != RT_NULL) {
        rt_thread_startup(thread);
    } else {
        ret = RT_ERROR;
    }

    return ret;
}
#endif

#ifdef GD32_UART_DMA_TEST
/* TX complete callback */
static rt_err_t uart_dma_tx_done(rt_device_t dev, void *buffer)
{
    rt_sem_release(&uart_dma_tx_sem);
    return RT_EOK;
}

static rt_err_t uart_dma_rx_indicate(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&uart_dma_rx_sem);
    return RT_EOK;
}

/* DMA TX send with mutex and completion wait */
static rt_ssize_t uart_dma_send(const rt_uint8_t *buf, rt_size_t len)
{
    rt_ssize_t sent;
    rt_err_t ret;

    rt_mutex_take(&uart_dma_tx_mutex, RT_WAITING_FOREVER);

    if (len > TX_BUF_SIZE)
    {
        len = TX_BUF_SIZE;
    }
    rt_memcpy(uart_dma_tx_buf, buf, len);

    sent = rt_device_write(uart_dma_serial, 0, uart_dma_tx_buf, len);
    if (sent < 0)
    {
        /* Device write error */
        rt_kprintf("[UART DMA] TX write error! ret=%d\n", sent);
        rt_mutex_release(&uart_dma_tx_mutex);
        return sent;
    }
    else if (sent > 0)
    {
        /* Wait for TX completion with timeout to avoid infinite blocking */
        ret = rt_sem_take(&uart_dma_tx_sem, DMA_TX_TIMEOUT);
        if (ret == -RT_ETIMEOUT)
        {
            tx_timeout_count++;
            rt_kprintf("[UART DMA] TX timeout! count=%d\n", tx_timeout_count);
            sent = -RT_ETIMEOUT;  /* Indicate failure */
        }
        else
        {
            tx_count++;
            total_tx_bytes += sent;
        }
    }

    rt_mutex_release(&uart_dma_tx_mutex);

    return sent;
}

static void uart_dma_thread_entry(void *parameter)
{
    rt_ssize_t len;

    while (1)
    {
        /* wait for DMA RX data */
        rt_sem_take(&uart_dma_rx_sem, RT_WAITING_FOREVER);

        /* read data in batch */
        len = rt_device_read(uart_dma_serial, 0, uart_dma_rx_buf, RX_BUF_SIZE);
        if (len < 0)
        {
            /* Read error, skip this iteration */
            rt_kprintf("[UART DMA] RX read error! ret=%d\n", len);
            continue;
        }
        else if (len > 0)
        {
            rx_count++;
            total_rx_bytes += len;

            /* Echo back using DMA TX */
            uart_dma_send(uart_dma_rx_buf, (rt_size_t)len);
        }
    }
}

/**
 * @brief UART DMA sample - DMA RX + DMA TX echo test
 * @param argc argument count
 * @param argv argument vector, argv[1] = uart name (optional, default "uart3")
 * @return RT_EOK on success, RT_ERROR on failure
 */
static int uart_dma_sample(int argc, char *argv[])
{
    char uart_name[RT_NAME_MAX];
    char str[] = "hello RT-Thread UART DMA!\r\n";
    rt_err_t ret;
    rt_thread_t thread;

    /* Prevent re-initialization */
    if (uart_dma_initialized)
    {
        rt_kprintf("UART DMA sample already initialized!\n\r");
        return RT_EOK;
    }

    if (argc >= 2) {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    } else {
        rt_strncpy(uart_name, UART_DMA_NAME, RT_NAME_MAX);
    }

    /* find uart device */
    uart_dma_serial = rt_device_find(uart_name);
    if (!uart_dma_serial)
    {
        rt_kprintf("UART device %s not found!\n\r", uart_name);
        return RT_ERROR;
    }

    /* Initialize semaphores and mutex */
    ret = rt_sem_init(&uart_dma_rx_sem, "dmarxsem", 0, RT_IPC_FLAG_FIFO);
    if (ret != RT_EOK)
    {
        rt_kprintf("Failed to init rx semaphore!\n\r");
        return RT_ERROR;
    }

    ret = rt_sem_init(&uart_dma_tx_sem, "dmatxsem", 0, RT_IPC_FLAG_FIFO);
    if (ret != RT_EOK)
    {
        rt_kprintf("Failed to init tx semaphore!\n\r");
        goto err_detach_rx_sem;
    }

    ret = rt_mutex_init(&uart_dma_tx_mutex, "dmatxmtx", RT_IPC_FLAG_PRIO);
    if (ret != RT_EOK)
    {
        rt_kprintf("Failed to init tx mutex!\n\r");
        goto err_detach_tx_sem;
    }

    /* Open with DMA RX + DMA TX */
    ret = rt_device_open(uart_dma_serial, RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s failed! ret=%d\n\r", uart_name, ret);
        goto err_detach_mutex;
    }

    rt_device_set_rx_indicate(uart_dma_serial, uart_dma_rx_indicate);
    rt_device_set_tx_complete(uart_dma_serial, uart_dma_tx_done);

    /* Send initial message via DMA */
    uart_dma_send((const rt_uint8_t *)str, sizeof(str) - 1);

    /* Create echo thread */
    thread = rt_thread_create("dmauart", uart_dma_thread_entry, RT_NULL, 1024, 25, 10);
    if (thread == RT_NULL)
    {
        rt_kprintf("Failed to create dmauart thread!\n\r");
        goto err_close_device;
    }

    rt_thread_startup(thread);
    uart_dma_initialized = RT_TRUE;
    rt_kprintf("UART DMA RX + DMA TX on %s (115200,8N1)\n\r", uart_name);
    rt_kprintf("Commands: dma_tx <data>, loopback [n], uart_stat, uart_clear\n\r");

    return RT_EOK;

err_close_device:
    rt_device_set_rx_indicate(uart_dma_serial, RT_NULL);
    rt_device_set_tx_complete(uart_dma_serial, RT_NULL);
    rt_device_close(uart_dma_serial);
err_detach_mutex:
    rt_mutex_detach(&uart_dma_tx_mutex);
err_detach_tx_sem:
    rt_sem_detach(&uart_dma_tx_sem);
err_detach_rx_sem:
    rt_sem_detach(&uart_dma_rx_sem);
    uart_dma_serial = RT_NULL;
    return RT_ERROR;
}

MSH_CMD_EXPORT(uart_dma_sample, UART DMA echo test sample);

/* DMA TX test command: dma_tx <data> */
static void uart_dma_tx_test(int argc, char *argv[])
{
    const char *data;
    rt_size_t len;

    if (!uart_dma_initialized)
    {
        rt_kprintf("Error: UART DMA not initialized! Run uart_dma_sample first.\n");
        return;
    }

    if (argc < 2)
    {
        rt_kprintf("Usage: dma_tx <data>\n");
        return;
    }

    data = argv[1];
    len = strlen(data);

    rt_kprintf("DMA TX: sending %d bytes\n", len);
    uart_dma_send((const rt_uint8_t *)data, len);
    uart_dma_send((const rt_uint8_t *)"\r\n", 2);
    rt_kprintf("DMA TX done!\n");
}
MSH_CMD_EXPORT_ALIAS(uart_dma_tx_test, dma_tx, DMA TX test <data>);

/* Loopback test: send data and verify echo */
static void uart_loopback_test(int argc, char *argv[])
{
    rt_uint8_t test_buf[64];
    int i, count = 10;

    if (!uart_dma_initialized)
    {
        rt_kprintf("Error: UART DMA not initialized! Run uart_dma_sample first.\n");
        return;
    }

    if (argc > 1)
    {
        count = atoi(argv[1]);
    }

    for (i = 0; i < count; i++)
    {
        /* Fill with pattern */
        rt_snprintf((char *)test_buf, sizeof(test_buf), "TEST%04d\r\n", i);

        /* Send via DMA */
        uart_dma_send(test_buf, strlen((char *)test_buf));

        /* Small delay for echo processing */
        rt_thread_mdelay(50);
    }

    rt_kprintf("Loopback test done! Check uart_stat for results.\n");
}
MSH_CMD_EXPORT_ALIAS(uart_loopback_test, loopback, Loopback test [count]);

/* Show statistics */
static void uart_stat(int argc, char *argv[])
{
    if (!uart_dma_initialized)
    {
        rt_kprintf("Error: UART DMA not initialized! Run uart_dma_sample first.\n");
        return;
    }

    rt_kprintf("UART Statistics (DMA RX + DMA TX):\n");
    rt_kprintf("  RX count: %d, bytes: %d\n", rx_count, total_rx_bytes);
    rt_kprintf("  TX count: %d, bytes: %d\n", tx_count, total_tx_bytes);
    rt_kprintf("  TX timeout: %d\n", tx_timeout_count);
}
MSH_CMD_EXPORT_ALIAS(uart_stat, uart_stat, Show UART statistics);

/* Clear statistics */
static void uart_stat_clear(int argc, char *argv[])
{
    if (!uart_dma_initialized)
    {
        rt_kprintf("Error: UART DMA not initialized! Run uart_dma_sample first.\n");
        return;
    }

    total_rx_bytes = 0;
    total_tx_bytes = 0;
    rx_count = 0;
    tx_count = 0;
    tx_timeout_count = 0;
    rt_kprintf("Statistics cleared.\n");
}
MSH_CMD_EXPORT_ALIAS(uart_stat_clear, uart_clear, Clear UART statistics);
#endif /* GD32_UART_DMA_TEST */

#ifdef GD32_GPIO_EXTI_TEST

void wakeup_key_pin_cb(void *args)
{
    rt_kprintf("Wakeup key pin pressed!\n");
}

void tamper_key_pin_cb(void *args)
{
    rt_kprintf("Tamper key pin pressed!\n");
}

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
}
#endif
