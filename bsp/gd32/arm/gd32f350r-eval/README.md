# GD32F350R-EVAL 开发板 BSP 说明

## 简介

GD32F350R-EVAL 评估板使用 GD32F350 系列 Cortex-M4 作为主控制器。评估板使用 USB 接口提供 5V 电源，提供包括扩展引脚在内的及 Reset， Wakeup， Tamper， LED， I2C EEPROM， SPI， USART 等外设资源。

该开发板常用 **板载资源** 如下：

- GD32F350RBT6，主频 108MHz，最高 128KB FLASH，16KB RAM，Cortex-M4
- 常用外设
  - LED：4 个，LED1（PC10），LED2（PC11），LED3（PC12），LED4（PC2）
  - 按键：4 个，Reset（复位按键），Wakeup Key（用户按键，PA0），User Key（用户按键），Tamper Key（用户按键，PC13）
  - General TM * 10、Advanced TM * 1
  - 系统时钟 * 1
  - 看门狗 * 2
  - RTC * 1
  - USART/UART * 2
  - I2C * 2
  - SPI * 2
  - CAN2.0B * 1
  - USB2.0 FS * 1
  - ADC * 1
  - DAC * 1
  - 最多支持 55GPIOs
- 常用接口：USB 接口
- 调试接口：SWD

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设**   | **支持情况** | **备注**                                                      |
| :------------- | :----------: | :------------------------------------------------------------ |
| GPIO           |     支持     | PA0, PA1... ---> PIN: 0, 1...54                               |
| UART           |     支持     | UART0 - UART1                                                 |
| LED            |     支持     | LED1（PC10），LED2（PC11），LED3（PC12），LED4（PC2）           |
| I2C            |     支持     | I2C0（硬件 I2C）                                               |
| SPI            |     支持     | SPI0                                                          |
| GPIO 中断      |     支持     | 支持外部中断功能，示例：Wakeup Key（PA0）、Tamper Key（PC13）、User Key   |
| I2C EEPROM     |     支持     | AT24C02，使用 I2C0 总线                                        |
| **扩展模块**   | **支持情况** | **备注**                                                      |
| SPI Flash      |     支持     | 需外接 SPI Flash 模块到 SPI0                                   |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

  本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

  本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 为开发者提供 MDK4、MDK5 和 IAR 工程，并且支持 GCC 开发环境，也可使用 RT-Thread Studio 开发。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，使用 USB 转 232 连接 UART0，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 SWD 仿真器下载程序，在通过 SWD 连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，LED 闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.0.0 build Dec 16 2025
 2006 - 2025 Copyright by rt-thread team
Hello GD32F350R!
RT-Thread BSP adaptation successful!
System Clock: 108000000 Hz
msh >
```

### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口 0 的功能，如果需使用高级功能，需要利用 ENV 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入 `menuconfig` 命令配置工程，配置好之后保存退出。

3. 输入 `pkgs --update` 命令更新软件包。

4. 输入 `scons --target=mdk4/mdk5/iar` 命令重新生成工程。

## 注意事项

- 本 BSP 默认启用了 I2C EEPROM（AT24C02）测试、SPI Flash 测试（需外接）、UART 测试和 GPIO 中断测试功能
- SPI Flash 测试功能需要外接 SPI Flash 模块，如果开发板未配备 SPI Flash，请在 main.c 中注释掉 `#define GD32_SPI_TEST`
- I2C EEPROM 使用 I2C0（hwi2c0）总线
- SPI Flash 使用 SPI0 总线
- 串口默认使用 UART0（115200-8-1-N）
