/*
 * GD32G553Q-EVAL UTest BSP Config Header
 * 
 * Board-specific configuration for DMA adaptation testing on GD32G553Q-EVAL
 */

#ifndef __UTEST_BSP_CONFIG_H__
#define __UTEST_BSP_CONFIG_H__

/* ==================== Board Identity ==================== */
#define UTEST_BOARD_NAME        "gd32g553q-eval"
#define UTEST_BOARD_FULL_NAME   "GD32G553Q-EVAL Development Board"
#define UTEST_MCU               "GD32G553Q (Cortex-M33, 216MHz, 512KB Flash, 128KB SRAM)"

/* ==================== GPIO Test Config ==================== */
#define UTEST_BSP_TEST_GPIO     1
#define UTEST_GPIO_LED1_PORT    GPIOB
#define UTEST_GPIO_LED1_PIN     GPIO_PIN_5   // PB5: LED1
#define UTEST_GPIO_LED1_RCU     RCU_GPIOB

/* ==================== GPIO EXTI Test Config (Optional) ==================== */
#define UTEST_BSP_TEST_GPIO_EXTI 0   // G553 不测 EXTI

/* ==================== UART DMA Test Config ==================== */
#define UTEST_BSP_TEST_UART     1
#define UTEST_UART_DEV          "uart0"
#define UTEST_UART_BAUDRATE     115200
#define UTEST_UART_RX_BUFSIZE   256
#define UTEST_UART_TX_BUFSIZE   256
#define UTEST_UART_DMA_MODE     1   // 1=DMA, 0=中断
#define UTEST_UART_TEST_SIZE    1024
#define TEST_UART_COUNT         1
#define TEST_UART_DEV1          "uart1"     /* loopback UART1 (PA2/PA3), uart0 is console */

/* ==================== SPI Flash Test Config (🔑 DMA 适配重点) ==================== */
#define UTEST_BSP_TEST_SPI_FLASH 0
#define UTEST_BSP_TEST_SPI_LOOPBACK 1   // 需短接 PB4(MISO)-PB5(MOSI)
#define UTEST_SPI_BUS           "spi2"
#define UTEST_SPI_DEV           "spi20"
#define UTEST_SPI_CS_PIN        -1              // 自动管理（驱动内部处理）
#define UTEST_SPI_FLASH_ADDR    0x00000000  // Flash 地址
#define UTEST_SPI_TEST_SIZE     256        // 256 字节测试
#define UTEST_SPI_DMA_MODE      1   // 启用 DMA
#define UTEST_SPI_TEST_DATA     0xA5   // 测试数据

/* ==================== I2C EEPROM Test Config (🔑 DMA 适配重点) ==================== */
#define UTEST_BSP_TEST_I2C_EEPROM 1
#define UTEST_I2C_BUS           "hwi2c2"      // 🆕 I2C2（新增支持）
#define UTEST_I2C_DEV_ADDR      0xA0        // AT24C02 地址
#define UTEST_I2C_EEPROM_SIZE   256         // AT24C02 容量
#define UTEST_I2C_TEST_SIZE     32          // 32 字节测试
#define UTEST_I2C_DMA_MODE      1   // 启用 DMA
#define UTEST_I2C_READ_TIMEOUT  1000
#define UTEST_I2C_WRITE_TIMEOUT 1000

/* ==================== I2C Soft Test Config ==================== */
#define UTEST_BSP_TEST_I2C_SOFT 0   // G553 不测软件 I2C

/* ==================== DMA Configuration Verification (🆕) ==================== */
#define UTEST_BSP_TEST_DMA_CONFIG 1
/* DMA Request IDs for GD32G553 */
#define UTEST_DMA_REQUEST_I2C2_RX_ID  20    // 硬件规格要求
#define UTEST_DMA_REQUEST_I2C2_TX_ID  21    // 硬件规格要求
#define UTEST_DMA_REQUEST_SPI0_RX_ID  4
#define UTEST_DMA_REQUEST_SPI0_TX_ID  5
#define UTEST_DMA_REQUEST_SPI2_RX_ID  8
#define UTEST_DMA_REQUEST_SPI2_TX_ID  9

/* DMA Macro Completeness Check */
#define UTEST_DMA_CHECK_I2C2_MACROS   1   // 验证 I2C2_RX/TX_DMA_CONFIG 宏
#define UTEST_DMA_CHECK_SPI_MACROS    1   // 验证 SPI_RX/TX_DMA_CONFIG 宏
#define UTEST_DMA_CHECK_UART_MACROS   1   // 验证 UART_RX/TX_DMA_CONFIG 宏

/* ==================== DMA-specific Functional Tests (🆕) ==================== */
#define UTEST_BSP_TEST_DMA_SPI       1    // SPI DMA 功能测试
#define UTEST_BSP_TEST_DMA_I2C       1    // I2C DMA 功能测试（I2C2 EEPROM）
#define UTEST_BSP_TEST_DMA_UART      1    // UART DMA 功能测试

#define UTEST_DMA_SPI_TRANSFER_SIZE  256  // SPI 单次传输大小
#define UTEST_DMA_I2C_TRANSFER_SIZE  32   // I2C 单次传输大小
#define UTEST_DMA_UART_TRANSFER_SIZE 512  // UART 单次传输大小

#define UTEST_DMA_TIMEOUT_MS         5000 // DMA 传输超时

/* ==================== Test Execution Order ==================== */
/* 测试顺序：配置验证 → 功能测试 */
#define UTEST_TEST_ORDER \
    UTEST_RUN(dma_config_check),     /* 配置完整性检查 */ \
    UTEST_RUN(gpio_led),              /* GPIO 基础 */ \
    UTEST_RUN(spi_flash_dma),         /* SPI DMA (Flash) */ \
    UTEST_RUN(i2c_eeprom_dma),        /* I2C DMA (EEPROM) */ \
    UTEST_RUN(uart_dma_loopback)      /* UART DMA 回环 */

/* ==================== Compatibility Macros for Generic Test Code ==================== */
/* Map UTEST_* macros to TEST_* names used by generic test code */
#ifdef UTEST_GPIO_LED1_PIN
    #define TEST_LED_PIN            UTEST_GPIO_LED1_PIN
    #define TEST_LED_PORT           UTEST_GPIO_LED1_PORT
    #define TEST_LED_RCU            UTEST_GPIO_LED1_RCU
#endif

#ifdef UTEST_UART_DEV
    #define TEST_UART_DEV           UTEST_UART_DEV
    #define TEST_UART_BAUDRATE      UTEST_UART_BAUDRATE
    #define TEST_UART_RX_BUFSIZE    UTEST_UART_RX_BUFSIZE
    #define TEST_UART_TX_BUFSIZE    UTEST_UART_TX_BUFSIZE
#endif

#ifdef UTEST_SPI_BUS
    #define TEST_SPI_BUS_NAME       UTEST_SPI_BUS
    #define TEST_SPI_DEV_NAME       UTEST_SPI_DEV
    #define TEST_SPI_CS_PIN         UTEST_SPI_CS_PIN
#endif

#ifdef UTEST_I2C_BUS
    #define TEST_I2C_BUS_NAME       UTEST_I2C_BUS
    #define TEST_I2C_ADDR           UTEST_I2C_DEV_ADDR
    #define TEST_I2C_EEPROM_SIZE    UTEST_I2C_EEPROM_SIZE
#endif

#endif /* __UTEST_BSP_CONFIG_H__ */
