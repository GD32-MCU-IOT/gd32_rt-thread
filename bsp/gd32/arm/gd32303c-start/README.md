# GD32F303CCT6 最小系统 BSP 说明

## 简介

本 BSP 适配 GD32F303CCT6 最小系统，使用 GD32F30X HD 启动文件，最高系统时钟为 120 MHz。

默认配置只保留 GPIO 状态灯、UART1 控制台和 MSH 命令行；不适配 I2C、SPI、ADC、RTC、看门狗、USB 或 UART DMA。

## 硬件资源

- MCU：GD32F303CCT6，256 KB Flash，48 KB SRAM
- 状态灯：PB14
- 控制台：USART1，PA2 为 TX，PA3 为 RX，115200-8-N-1
- 调试下载：GD-Link

使用 USB 转 TTL 模块时，将模块 RX 接 PA2、模块 TX 接 PA3，并与开发板共地。

## 默认功能

| 功能 | 默认状态 | 说明 |
|:---|:---:|:---|
| GPIO | 启用 | PB14 每 500 ms 翻转一次，作为系统运行指示。 |
| UART1 | 启用 | PA2/PA3，作为 `uart1` 控制台。 |
| FINSH/MSH | 启用 | 复位后可通过串口使用 MSH。 |
| I2C/SPI/ADC/RTC/WDT/USB/DMA | 未启用 | 最小系统不包含这些外设适配。 |

## 构建

在 BSP 目录运行：

```powershell
pkgs --update
scons
```

`rtconfig.py` 不包含机器相关的工具链路径。请将 `arm-none-eabi-*` 工具加入 `PATH`，或将 `RTT_EXEC_PATH` 设置为 ARM GCC 的 `bin` 目录。GCC 构建生成 `rtthread.elf` 和 `rtthread.bin`。链接脚本已按 256 KB Flash 和 48 KB SRAM 配置。

需要重新生成 IDE 工程时，运行：

```powershell
scons --target=mdk5
scons --target=iar
```

生成 MDK 或 IAR 工程前，将 `RTT_CC` 分别设置为 `keil` 或 `iar`，并将 `RTT_EXEC_PATH` 设置为相应工具链的安装根目录。生成的工程分别使用已校正的 `link.sct` 和 `link.icf` 内存布局。

## 下载与验证

使用 GD-Link 将 `rtthread.bin` 下载到 `0x08000000`。打开串口工具并设置为 115200-8-N-1，复位后应看到 RT-Thread 启动信息以及：

```text
GD32F303CCT6 RT-Thread BSP
System clock: 120000000 Hz
UART1 console and MSH are ready.
msh >
```

在 `msh >` 提示符下执行：

```text
help
list_thread
```

命令应正常返回，且 `list_thread` 应包含 `tshell`。PB14 状态灯在命令执行期间持续闪烁。

