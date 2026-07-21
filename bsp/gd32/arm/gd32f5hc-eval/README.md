# GD32W51x_F5HC-EVAL 开发板 BSP 说明

## 简介

GD32W51x_F5HC-EVAL 评估板使用 GD32W51x_F5HC 系列作为主控制器。该评估板是兆易创新推出的一款基于 ARM Cortex-M33 内核的开发板，具有丰富的板载资源，可以充分发挥 GD32W51x_F5HC 系列芯片的性能。

该开发板常用 **板载资源** 如下：

- **MCU**: GD32W51x_F5HC 系列，ARM Cortex-M33 内核
- **内存**:
  - 片内 SRAM：320KB
- **板载外设**:
  - LED
  - 按键
- **调试接口**: CMSIS-DAP (板载 DAP-Link)

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** | **备注**                              |
|:------------ |:------------:|:------------------------------------- |
| GPIO         | 支持         | PA0, PA1... ---> PIN: 0, 1...         |
| UART         | 支持         | UART0 - UART2，支持 DMA               |
| SPI          | 支持         | SPI0 - SPI1，支持 DMA                 |
| I2C          | 支持         | I2C0 - I2C1（硬件 I2C），支持 DMA     |
| Soft I2C     | 支持         | 软件模拟 I2C（bit-bang）              |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

  本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果。

- 进阶使用

  本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 为开发者提供 MDK5 工程，支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用调试器连接开发板到 PC，使用 USB2TTL 连接 USART2（Console），并给开发板供电。

#### 编译下载

双击 **project.uvprojx** 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 CMSIS-DAP 仿真器下载程序，在通过 CMSIS-DAP 连接开发板的基础上，点击下载按钮即可下载程序到开发板。
>
> EVAL 板载 DAP-Link，可直接使用板子 DAP-Link 下载。

#### 运行结果

下载程序成功之后，系统会自动运行，LED 闪烁。

连接开发板对应串口到 PC，在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     5.2.1 build Jun  3 2026
 2006 - 2024 Copyright by RT-Thread team
msh />
```

### 进阶使用

此 BSP 当前默认开启 GPIO、UART0、UART1、UART2（Console）、SPI1 和 I2C1 功能。如果需调整外设功能或启用更多片上资源（如 DMA），需要利用 ENV 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入 `menuconfig` 命令配置工程，配置好之后保存退出。

3. 输入 `pkgs --update` 命令更新软件包。

4. 输入 `scons --target=mdk5` 命令重新生成工程。

#### DMA 支持

本 BSP 的 UART、SPI、I2C 均支持 DMA 传输模式，可通过 menuconfig 开启。DMA 通道分配如下：

| DMA 通道       | 外设        | 方向 |
|:-------------- |:----------- |:---- |
| DMA0 Channel0  | I2C0 RX     | 接收 |
| DMA0 Channel1  | UART2 RX    | 接收 |
| DMA0 Channel2  | I2C1 RX     | 接收 |
| DMA0 Channel3  | SPI1 RX     | 接收 |
| DMA0 Channel4  | SPI1 TX     | 发送 |
| DMA0 Channel5  | SPI0 TX     | 发送 |
| DMA0 Channel6  | I2C0 TX     | 发送 |
| DMA0 Channel7  | I2C1 TX     | 发送 |
| DMA1 Channel2  | UART0 RX    | 接收 |
| DMA1 Channel7  | UART0 TX    | 发送 |

## 注意事项

- 若 MDK 编译无法运行，请更新 MDK 至较新的版本（MDK538 版本测试通过）。
- README 中"支持"表示 BSP 已提供对应驱动与板级初始化入口，具体功能是否可直接联调还取决于外设连接和测试器件。
