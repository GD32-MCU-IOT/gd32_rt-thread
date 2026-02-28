# GD32E113V-EVAL BSP 说明

## 简介

GD32E113V-EVAL 是兆易创新推出的基于 GD32E113V 系列 MCU 的评估板。本 BSP 支持 RT-Thread 操作系统。

### 开发板外观

<!-- 可添加开发板图片 -->

### 核心规格

| 硬件资源 | 描述 |
| --- | --- |
| MCU | GD32E113VBT6, ARM Cortex-M4, 主频 72MHz |
| SRAM | 32KB |
| Flash | 128KB |
| FPU | 单精度浮点运算单元 (FPv4-SP) |

## 支持的外设

本 BSP 目前支持以下外设：

| 外设 | 支持情况 | 备注 |
| --- | :---: | --- |
| GPIO | 支持 | |
| USART | 支持 | USART0, USART1 |
| SPI | 支持 | SPI0, SPI1 |
| I2C | 支持 | 硬件 I2C0, I2C1 |
| ADC | 支持 | ADC0 |
| RTC | 支持 | |
| TIMER | 支持 | TIMER0, TIMER1, TIMER2, TIMER5, TIMER6, TIMER13-16 |
| PWM | 支持 | |
| WDT | 支持 | WWDGT, FWDGT |
| DMA | 支持 | 7个通道 |

## 编译说明

### Windows 环境

1. 安装 [Env 工具](https://www.rt-thread.org/download.html#download-rt-thread-env-tool)
2. 安装 ARM GCC 工具链
3. 打开 Env 终端，进入 BSP 目录
4. 运行 `pkgs --update` 更新软件包
5. 运行 `scons` 编译

### 编译命令

```bash
# 更新软件包
pkgs --update

# 编译
scons

# 清理
scons -c

# 生成 Keil MDK 工程
scons --target=mdk5

# 生成 IAR 工程
scons --target=iar
```

### 配置选项

使用 `menuconfig` 配置 BSP：

```bash
menuconfig
```

## 使用说明

### 串口连接

默认使用 USART0 作为控制台，波特率 115200，引脚配置：

| 功能 | 引脚 |
| --- | --- |
| USART0_TX | PA9 |
| USART0_RX | PA10 |

### LED 指示灯

| LED | 引脚 | 说明 |
| --- | --- | --- |
| LED1 | PC0 | 用户 LED |
| LED2 | PC2 | 用户 LED |

## 注意事项

1. 本 BSP 基于 GD32E11x 固件库开发
2. GD32E113V 为 ARM Cortex-M4 内核，支持 FPU
3. 系统时钟默认配置为 72MHz

## 联系信息

维护人：RT-Thread 团队

## 参考资料

- [RT-Thread 文档中心](https://www.rt-thread.org/document/site/)
- [GD32E11x 用户手册](http://www.gd32mcu.com/)
- [RT-Thread GD32 驱动开发指南](https://github.com/RT-Thread/rt-thread)
