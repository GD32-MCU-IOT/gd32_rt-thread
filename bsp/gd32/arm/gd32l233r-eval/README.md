# GD32L233R-EVAL 开发板 BSP 说明

## 简介

GD32L233R-EVAL 评估板使用 GD32L233RC 系列 Cortex-M23 低功耗微控制器作为主控制器。评估板使用 Mini USB 接口提供 5V 电源。提供包括扩展引脚在内的及 Reset、Boot、Wakeup、Tamper、LED、I2C EEPROM、SPI Flash、UART 等外设资源。

该开发板常用 **板载资源** 如下：

- GD32L233RC，主频 64MHz，256KB FLASH，32KB RAM，Cortex-M23
- 常用外设
  - LED：4 个，LED1（PC7），LED2（PC8），LED3（PC9），LED4（PC11）
  - 按键：2 个，Wakeup Key（用户按键，PA0），Tamper Key（用户按键，PC13）
  - General Timer * 7、Advanced Timer * 1、Basic Timer * 2
  - Low Power Timer * 1
  - 系统时钟 * 1
  - 看门狗 * 2
  - RTC * 1
  - USART * 2 + UART * 3（USART0、USART1、UART3、UART4、LPUART）
  - I2C * 3（I2C0、I2C1、I2C2）
  - SPI * 2（SPI0、SPI1）
  - CAN2.0B * 1
  - ADC * 1（12-bit）
  - DAC * 1（12-bit）
  - Comparator * 2
  - TRNG * 1
  - 最多支持 51 GPIOs
- 常用接口：Mini USB 接口
- 调试接口：GD-LINK

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设**   | **支持情况** | **备注**                                                      |
| :------------- | :----------: | :------------------------------------------------------------ |
| GPIO           |     支持     | PA0, PA1... ---> PIN: 0, 1...50                               |
| UART           |     支持     | UART0 (USART0)、UART1 (USART1)、UART3、UART4                  |
| LED            |     支持     | LED1（PC7），LED2（PC8），LED3（PC9），LED4（PC11）            |
| I2C            |     支持     | I2C0、I2C1、I2C2（硬件 I2C）                                   |
| SPI            |     支持     | SPI0、SPI1                                                    |
| GPIO 中断      |     支持     | 支持外部中断功能，示例：Wakeup Key（PA0）、Tamper Key（PC13）   |
| **扩展模块**   | **支持情况** | **备注**                                                      |
| I2C EEPROM     |     支持     | AT24C02，使用 I2C1 总线（hwi2c1）                              |
| SPI Flash      |     支持     | GD25Q Flash，使用 SPI0 总线，CS 引脚为 PD2                     |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

  本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

  本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 为开发者提供 MDK4、MDK5 和 IAR 工程，并且支持 GCC 开发环境，也可使用 RT-Thread Studio 开发。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，使用 USB 转串口连接 UART1（PA2-TX、PA3-RX），打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 GD-Link  仿真器下载程序，在通过 GD-Link  连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，LED 闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.2.1 build Jan  5 2026
 2006 - 2024 Copyright by rt-thread team
Hello GD32L233RC!
RT-Thread BSP adaptation successful!
System Clock: 64000000 Hz
msh >
```

### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口 1（USART1）的功能，如果需使用高级功能，需要利用 ENV 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入 `menuconfig` 命令配置工程，配置好之后保存退出。

3. 输入 `pkgs --update` 命令更新软件包。

4. 输入 `scons --target=mdk4/mdk5/iar` 命令重新生成工程。

## 注意事项

- 本 BSP 默认启用了 I2C EEPROM（AT24C02）测试、SPI Flash（GD25Q）测试、UART 测试和 GPIO 中断测试功能
- I2C EEPROM 使用 I2C1（hwi2c1）总线，引脚为 PB10（SCL）、PB11（SDA）
- SPI Flash 使用 SPI0 总线，引脚为 PB3（SCK）、PB4（MISO）、PB5（MOSI）、PD2（CS）
- 由于引脚复用冲突，SPI0 的 CS（PD2）与 UART4 的 RX（PD2）共用引脚，运行时只能启用其中一个外设
- 串口默认使用 UART1（USART1，115200-8-1-N），引脚为 PA2（TX）、PA3（RX）
- LED 引脚：LED1（PC7）、LED2（PC8）、LED3（PC9）、LED4（PC11）
- 按键引脚：Wakeup（PA0）、Tamper（PC13）
