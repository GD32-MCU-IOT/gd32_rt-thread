/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-07     RT-Thread    first implementation for GD32H75E-EVAL
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string.h>

#define GD32H7_I2C_EEPROM_TEST
//#define GD32H7_SPI_TEST


/* defined the LED pins: LED1 and LED2 */
#define LED1_PIN    GET_PIN(C, 3)   /* LED1 on PC3 */
#define LED2_PIN    GET_PIN(C, 4)   /* LED2 on PC4 */
#define LED3_PIN    GET_PIN(C, 5)   /* LED2 on PC4 */


#ifdef GD32H7_I2C_EEPROM_TEST
#include "at24cxx.h"
#define BUFFER_SIZE    256
#define I2C_SERIAL     "hwi2c3"
rt_uint8_t buf[16];
rt_uint8_t i2c_buffer_write[BUFFER_SIZE];
rt_uint8_t i2c_buffer_read[BUFFER_SIZE];
uint8_t i2c_24c02_test(void);
#endif

#ifdef GD32H7_SPI_TEST
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

#ifdef GD32H7_I2C_EEPROM_TEST
    struct rt_i2c_bus_device *i2c0_dev;
    i2c0_dev = rt_i2c_bus_device_find(I2C_SERIAL);
    if(i2c_24c02_test() != 0){
        rt_kprintf("I2C-AT24C02 test passed!\n\r");
    }
#endif

#ifdef GD32H7_SPI_TEST
    spi_sample();
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


#ifdef GD32H7_SPI_TEST

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

#ifdef GD32H7_I2C_EEPROM_TEST

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
