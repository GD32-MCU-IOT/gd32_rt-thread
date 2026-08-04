# GD32F207I-EVAL开发板BSP说明

## 简介

GD32F207I-EVAL 是兆易创新推出的一款 GD32F20X 系列的评估板，最高主频高达 120M，该开发板具有丰富的板载资源，可以充分发挥 GD32F207IK 的芯片性能。

开发板外观如下图所示：

![board](figures/board.jpg)

该开发板常用 **板载资源** 如下：

- GD32F207IK，主频 120MHz，512KB Flash、128KB SRAM

- 常用外设

  - LED
  - 按键
  - General TM * 10 、Advanced TM * 2、Basic TM * 2
  - 系统时钟 * 1
  - 看门狗 * 2
  - RTC * 1
  - USART * 4、UART * 4
  - I2C * 3
  - SPI * 3、I2S * 2
  - SDIO * 1
  - CAN2.0B * 2
  - USB2.0 OTG FS * 1
  - 以太网MAC * 1
  - TFT-LCD接口(TLI) * 1
  - EXMC/SDRAM * 1
  - DCI * 1
  - 加密单元(CAU/HAU) * 1、真随机数发生器(TRNG) * 1

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** | **备注**                              |
|:------------ |:------------:|:------------------------------------- |
| GPIO         | 支持         | PA0, PA1... ---> PIN: 0, 1...         |
| UART         | 支持         | UART0 - UART7，支持 RX DMA            |
| SPI          | 支持         | SPI1，支持 DMA                        |
| ADC          | 支持         | ADC0 - ADC2                           |
| HWTIMER      | 支持         | TIM10 / TIM11 / TIM13                 |
| RTC          | 支持         | 支持 Alarm0/Alarm1                    |
| WDT          | 支持         | 独立看门狗 / 窗口看门狗               |
| SDIO         | 支持         | 使用 SD 卡                            |
| USB Device   | 支持         | USBFS                                 |
| USB Host     | 支持         | USBFS，支持 Udisk                     |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

  本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果。

- 进阶使用

  本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 为开发者提供 MDK5、IAR、GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用调试器连接开发板到 PC，使用 USB 转串口连接 USART0（Console），并给开发板供电。

#### 编译下载

双击 **project.uvprojx** 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 J-Link 仿真器下载程序，在通过 J-Link 连接开发板的基础上，点击下载按钮即可下载程序到开发板。

#### 运行结果

下载程序成功之后，系统会自动运行，LED 闪烁。

连接开发板对应串口到 PC，在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     5.2.x build xxx
 2006 - 2024 Copyright by RT-Thread team
msh />
```

### 进阶使用

此 BSP 当前默认开启 GPIO 和 USART0（Console）功能。如果需调整外设功能或启用更多片上资源（如 SPI、I2C、ADC、HWTIMER、RTC、WDT、SDIO、USB 等），需要利用 ENV 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入 `menuconfig` 命令配置工程，配置好之后保存退出。

3. 输入 `pkgs --update` 命令更新软件包。

4. 输入 `scons --target=mdk5` / `scons --target=iar` / `scons --target=eclipse` 命令重新生成对应工程。

## 注意事项

- 若 MDK 编译无法运行，请更新 MDK 至较新的版本，并安装 GigaDevice.GD32F20x_DFP 器件支持包。
- README 中"支持"表示 BSP 已提供对应驱动与板级初始化入口，具体功能是否可直接联调还取决于外设连接和测试器件。
