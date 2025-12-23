# GD32G553-EVAL BSP说明

## 简介

本文档为 GD32G553-EVAL 开发板提供的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手指南
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。

## 开发板介绍

GD32G553-EVAL 是兆易创新推出的一款基于 ARM Cortex-M33 内核的开发板，最高主频为 216MHz，该开发板具有丰富的板载资源，可以充分发挥 GD32G553 的芯片性能。

该开发板常用 **板载资源** 如下：

- MCU：GD32G553REU，主频 216MHz，512KB FLASH，128KB RAM (SRAM0: 80KB + SRAM1: 16KB + TCMSRAM: 32KB)
- 外部 RAM：无
- 外部 FLASH：W25Q128 (SPI，16MB)
- 常用外设
  - LED：4个，（LED1/PC6，LED2/PC7，LED3/PB14，LED4/PB15）
  - 按键：5个，KEY_A/PA0，KEY_B/PA1，KEY_C/PA2，KEY_D/PA3，KEY_E/PA4)
- 常用接口：RS232 转串口、以太网接口、LCD 接口等
- 调试接口，标准 JTAG/SWD

开发板更多详细信息请参考兆易创新 [GD32G553-EVAL]() 开发板介绍。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设**      | **支持情况** | **备注**                              |
| :----------------- | :----------: | :------------------------------------- |
| 串口               |     支持     | UART0                                 |
| SPI Flash          |     支持     | W25Q128                              |
| **片上外设**      | **支持情况** | **备注**                              |
| GPIO               |     支持     | PA0, PA1... PC15 ---> PIN: 0, 1...47 |
| UART               |     支持     | UART0/1/2                            |
| SPI                |     支持     | SPI0/1                               |
| I2C                |     支持     | 软件 I2C                             |

## 使用说明

### 快速上手

本 BSP 为开发者提供 MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

#### 运行结果

下载程序成功之后，系统会自动运行，观察开发板上 LED 的实际效果。LED1 闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，在串口上可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.1.1 build Dec 28 2024
 2006 - 2024 Copyright by rt-thread team
Hello GD32G553! count: 1
msh >
```

### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口0 的功能，如果需使用更多高级功能，需要利用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk5/iar` 命令重新生成工程。

## 注意事项

- 请确保固件库正确安装在packages目录下
- 编译前请运行 `pkgs --update` 更新软件包
- GD32G553 芯片有多个SRAM区域（SRAM0: 80KB, SRAM1: 16KB, TCMSRAM: 32KB），当前BSP配置使用128KB总SRAM

## 联系人信息

维护人:
- [RT-Thread](https://github.com/RT-Thread/rt-thread)

## 参考

- [GD32 MCU官网](https://www.gigadevice.com/)
- [GD32G553数据手册]()
