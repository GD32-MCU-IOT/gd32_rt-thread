# GD32E235C-EVAL 开发板 BSP 说明

## 简介

GD32E235C-EVAL 评估板使用 GD32E235C8T6 系列 Cortex-M23 作为主控制器。评估板使用 USB 接口提供 5V 电源。提供包括扩展引脚在内的及 Reset、Boot、按键、LED、I2C、SPI 接口等外设资源。

该开发板常用 **板载资源** 如下：

- GD32E235C8T6，主频 72MHz，64KB FLASH，8KB RAM，Cortex-M23，LQFP48 封装
- 常用外设
  - LED：4 个，LED1（PA8）、LED2（PA11）、LED3（PA12）、LED4（PA15）
  - 按键：2 个，Wakeup 按键（PA0）、Tamper 按键（PC13）
  - General TM * 5
  - 系统时钟 * 1
  - 看门狗 * 2
  - RTC * 1
  - USART/UART * 2（USART0、USART1）
  - I2C * 2（I2C0、I2C1）
  - SPI * 2（SPI0、SPI1）
  - ADC * 1
  - 比较器 * 1
  - 最多支持 37 GPIOs（LQFP48封装）
- 常用接口：USB 接口
- 调试接口：SWD

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设**   | **支持情况** | **备注**                                                      |
| :------------- | :----------: | :------------------------------------------------------------ |
| GPIO           |     支持     | PA0, PA1... ---> PIN: 0, 1...                                 |
| UART           |     支持     | UART0（PA9/PA10），UART1（PA14/PA15），支持 DMA                |
| LED            |     支持     | LED1（PA8）、LED2（PA11）、LED3（PA12）、LED4（PA15）          |
| I2C            |     支持     | I2C0（PB6/PB7），I2C1（PB10/PB11），支持 DMA                    |
| SPI            |     支持     | SPI0（PA5/PA6/PA7），SPI1（PB13/PB14/PB15），支持 DMA           |
| GPIO 中断      |     支持     | Wakeup（PA0）、Tamper（PC13）外部中断                          |
| ADC            |     支持     | 可通过 Kconfig 开启 ADC0                                        |
| WDT            |     支持     | 可通过 Kconfig 开启看门狗                                       |
| **扩展模块**   | **支持情况** | **备注**                                                      |
| I2C EEPROM     |     支持     | AT24C02，默认使用 I2C1（hwi2c1），可选 I2C0                     |
| SPI Flash      |     支持     | W25Q16，可选 SPI0 或 SPI1，需在 Kconfig 中开启                 |

### GD32E23x 系列驱动引脚映射

| **外设** | **引脚**     | **GPIO_AF**  | **备注**           |
| :------- | :----------- | :----------- | :----------------- |
| LED1     | PA8          | -            | 输出模式           |
| LED2     | PA11         | -            | 输出模式           |
| LED3     | PA12         | -            | 输出模式           |
| LED4     | PA15         | -            | 输出模式           |
| Wakeup   | PA0          | -            | 外部中断，下降沿   |
| Tamper   | PC13         | -            | 外部中断，下降沿   |
| USART0   | PA9 (TX)     | GPIO_AF_1    | 默认控制台         |
| USART0   | PA10 (RX)    | GPIO_AF_1    |                    |
| USART1   | PA14 (TX)    | GPIO_AF_1    |                    |
| USART1   | PA15 (RX)    | GPIO_AF_1    |                    |
| SPI0     | PA5 (SCK)    | GPIO_AF_0    |                    |
| SPI0     | PA6 (MISO)   | GPIO_AF_0    |                    |
| SPI0     | PA7 (MOSI)   | GPIO_AF_0    |                    |
| SPI1     | PB13 (SCK)   | GPIO_AF_0    |                    |
| SPI1     | PB14 (MISO)  | GPIO_AF_0    |                    |
| SPI1     | PB15 (MOSI)  | GPIO_AF_0    |                    |
| I2C0     | PB6 (SCL)    | GPIO_AF_1    |                    |
| I2C0     | PB7 (SDA)    | GPIO_AF_1    |                    |
| I2C1     | PB10 (SCL)   | GPIO_AF_1    |                    |
| I2C1     | PB11 (SDA)   | GPIO_AF_1    |                    |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

  本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果。

- 进阶使用

  本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 为开发者提供 MDK5、IAR 工程，并且支持 GCC 开发环境，也可使用 RT-Thread Studio 开发。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，使用 USB 转 TTL 模块连接 UART0（PA9/PA10），打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 CMSIS-DAP 仿真器下载程序，在通过仿真器连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，LED1-LED4 依次闪烁。

连接开发板对应串口到 PC，在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.2.1 build Jan 30 2025
 2006 - 2025 Copyright by rt-thread team

Hello GD32E235C!
RT-Thread BSP adaptation successful!
System Clock: 72000000 Hz

msh >
```

如果开启了 I2C EEPROM 测试（`GD32_I2C_EEPROM_TEST`），还会看到 EEPROM 测试信息：

```bash
 Found eeprom
 I2C-AT24C02 writing...
I2C-AT24C02 Finish writing...
I2C-AT24C02 reading...
I2C-AT24C02 Finish reading...
I2C-AT24C02 test passed!
```

### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口 0 的功能，如果需使用高级功能，需要利用 ENV 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入 `menuconfig` 命令配置工程，配置好之后保存退出。

3. 输入 `pkgs --update` 命令更新软件包。

4. 输入 `scons --target=mdk5/iar` 命令重新生成工程。

## 固件库使用说明

本 BSP 需要使用 GD32E23x 固件库。请手动将固件库文件拷贝到以下目录：

- CMSIS 文件：`packages/gd32-arm-cmsis-latest/GD32E23x/`
- 外设库文件：`packages/gd32-arm-series-latest/GD32E23x/`

固件库可以从 GigaDevice 官网下载：
https://www.gd32mcu.com/cn/download/7?kw=GD32E23x

## 注意事项

- 本 BSP 基于 GD32E235C8T6 芯片（64KB FLASH，8KB RAM，LQFP48 封装）
- 如果要使用 SPI Flash 或 I2C EEPROM 功能，需要在 Kconfig 中开启对应外设并外接相应模块
- 串口默认使用 UART0（115200-8-1-N），引脚为 PA9 (TX)、PA10 (RX)
- LED 使用 PA8、PA11、PA12、PA15 引脚，按键使用 PA0（Wakeup）和 PC13（Tamper）
- GD32E23x 系列使用 Cortex-M23 内核，与 E230 系列共用固件库
- I2C EEPROM 测试默认使用 I2C1（hwi2c1），可在 Kconfig 中切换到 I2C0
- main.c 中定义了测试宏 `GD32_I2C_EEPROM_TEST`、`GD32_UART_TEST`、`GD32_GPIO_EXTI_TEST`，可按需开启
