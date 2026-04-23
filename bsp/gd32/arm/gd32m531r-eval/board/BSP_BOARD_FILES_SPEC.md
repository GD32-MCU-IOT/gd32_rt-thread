# GD32 ARM BSP 板级文件规范指南

## 一、板级目录（board/）文件清单

```
board/
├── board.c                      # 板级初始化源文件
├── board.h                      # 板级头文件
├── board_msd_init.c            # MSD（大容量存储设备）初始化
├── gd32f50x_libopt.h           # GD32库选项配置
├── Kconfig                      # 硬件配置菜单定义
├── SConscript                   # SCons编译脚本
└── linker_scripts/
    ├── link.ld                  # GNU LD 链接脚本
    ├── link.sct                 # ARM Compiler 6 链接脚本
    └── link.icf                 # IAR 链接脚本
```

---

## 二、文件分类：通用文件 vs MCU特定文件

### 2.1 通用文件（无需MCU特定修改）

| 文件 | 目的 | 说明 |
|------|------|------|
| **SConscript** | 编译脚本 | 定义如何编译 board.c 和 board_msd_init.c，通常无需改动 |
| **Kconfig** | 配置菜单 | 定义硬件外设选项（UART、SPI、I2C等），可复用结构 |

### 2.2 MCU特定文件（需根据MCU修改）

#### A. 内存配置相关（**必须修改**）

| 文件 | 字段 | 说明 | 示例 |
|------|------|------|------|
| **board.h** | `GD32_SRAM_SIZE` | 内存大小（KB） | `#define GD32_SRAM_SIZE 128` |
| **board.h** | `GD32_SRAM_END` | 内存结束地址 | `0x20000000 + 128*1024 = 0x20020000` |
| **link.ld** | `_estack` | 栈顶地址 | `_estack = 0x20020000;` |
| **link.ld** | `DATA LENGTH` | RAM大小 | `LENGTH = 128K` |
| **link.sct** | `RW_IRAM1 SIZE` | RAM大小（十六进制） | `0x00020000` (128KB) |
| **link.icf** | `region_RAM_end` | RAM结束地址 | `0x2001FFFF` |

#### B. MCU型号相关（**需要修改**）

| 文件 | 字段 | 说明 | 示例 |
|------|------|------|------|
| **SConscript** | `CPPDEFINES` | MCU宏定义 | `['GD32F50X', 'GD32F503VG']` |
| **board.h** | 注释说明 | SRAM容量注释 | `/* GD32F503V series contains up to 128KB on-chip SRAM */` |
| **gd32fXXx_libopt.h** | 头文件定义 | MCU库选项 | 包含相应MCU的头文件配置 |
| **Kconfig** | `SOC_SERIES_GDXXx` | SOC系列 | `config SOC_SERIES_GD32F50x` |

#### C. 硬件功能相关（**可选修改**）

| 文件 | 内容 | 说明 |
|------|------|------|
| **board.c** | 初始化函数 | SystemClock_Config、rt_hw_board_init 等 |
| **board_msd_init.c** | MSD初始化 | 根据开发板是否有存储设备决定是否启用 |
| **Kconfig** | 外设配置菜单 | UART0/1/2、SPI0/1/2、I2C0/1/2 等可用外设 |

#### D. 编译工具链相关（**需要匹配**）

| 文件 | 工具链 | 说明 |
|------|--------|------|
| **link.ld** | GCC | 用于 GCC 编译器 |
| **link.sct** | ARM Compiler 6 | 用于 Keil MDK v5 |
| **link.icf** | IAR EWB | 用于 IAR Embedded Workbench |

---

## 三、适配新MCU的检查清单

### 步骤 1：确定MCU参数
- [ ] MCU型号（如 GD32F503VG、GD32H75EY 等）
- [ ] 内存大小（Flash ROM、SRAM）
- [ ] 可用外设（UART、SPI、I2C 数量）
- [ ] 工作频率（如 120MHz）

### 步骤 2：修改内存配置（最关键）
- [ ] 更新 **link.ld** 中的 `_estack` 地址
- [ ] 更新 **link.ld** 中的 `DATA LENGTH`
- [ ] 更新 **link.sct** 中的 `RW_IRAM1` 大小
- [ ] 更新 **link.icf** 中的 `region_RAM_end` 地址
- [ ] 更新 **board.h** 中的 `GD32_SRAM_SIZE`
- [ ] 验证：栈顶地址 = RAM起始 + RAM大小

### 步骤 3：修改MCU相关宏定义
- [ ] 更新 **SConscript** 中的 `CPPDEFINES`（芯片系列和型号）
- [ ] 更新 **board.h** 中的内存容量注释
- [ ] 更新 **Kconfig** 中的 `SOC_SERIES_GDXXx` 名称
- [ ] 更新 **gd32fXXx_libopt.h** 文件名（如有）

### 步骤 4：配置硬件外设（Kconfig）
- [ ] 根据MCU可用的UART通道修改 Kconfig
- [ ] 根据MCU可用的SPI通道修改 Kconfig
- [ ] 根据MCU可用的I2C通道修改 Kconfig
- [ ] 根据开发板的周边器件修改 Kconfig（SPI Flash、EEPROM等）

### 步骤 5：验证编译脚本
- [ ] 检查 **SConscript** 中 `group = DefineGroup(...)` 的 group 名称为 'Drivers'
- [ ] 确保 CPPPATH 指向正确的目录
- [ ] 核实依赖关系声明无误

### 步骤 6：测试编译
```bash
scons -j4           # 或其他编译命令
```

---

## 四、常见MCU的内存配置对照表

| MCU型号 | Flash | SRAM | RAM结束地址 | link.sct大小 | link.icf地址 |
|--------|-------|------|-----------|------------|-----------|
| GD32F50x (192KB) | 512KB | 192KB | 0x20030000 | 0x00030000 | 0x2002FFFF |
| GD32F50x (128KB) | 512KB | 128KB | 0x20020000 | 0x00020000 | 0x2001FFFF |
| GD32H75E | 2MB | 512KB | 0x20080000 | 0x00080000 | 0x2007FFFF |
| GD32H759I | 2MB | 384KB | 0x20060000 | 0x00060000 | 0x2005FFFF |

---

## 五、关键数值换算公式

### RAM大小转换
```
128 KB = 128 × 1024 = 131,072 字节 = 0x20000（十六进制）
192 KB = 192 × 1024 = 196,608 字节 = 0x30000（十六进制）
```

### 内存地址计算
```
RAM结束地址 = RAM起始地址 + RAM大小 - 1
例如：0x20000000 + 0x20000 - 1 = 0x2001FFFF

link.sct大小 = RAM大小（十六进制）
例如：128KB → 0x00020000

link.icf地址 = RAM起始 + RAM大小 - 1
例如：0x20000000 + 128×1024 - 1 = 0x2001FFFF
```

---

## 六、文件修改示例

### 示例：从 192KB 改为 128KB

**1. board.h**
```c
/* 改前 */
#define GD32_SRAM_SIZE         192

/* 改后 */
#define GD32_SRAM_SIZE         128
```

**2. link.ld**
```ld
/* 改前 */
_estack = 0x20030000;
DATA (rw) : ORIGIN = 0x20000000, LENGTH = 192K

/* 改后 */
_estack = 0x20020000;
DATA (rw) : ORIGIN = 0x20000000, LENGTH = 128K
```

**3. link.sct**
```
/* 改前 */
RW_IRAM1 0x20000000 0x00030000

/* 改后 */
RW_IRAM1 0x20000000 0x00020000
```

**4. link.icf**
```
/* 改前 */
define symbol __ICFEDIT_region_RAM_end__ = 0x2002FFFF;

/* 改后 */
define symbol __ICFEDIT_region_RAM_end__ = 0x2001FFFF;
```

**5. SConscript**
```python
/* 改前 */
CPPDEFINES = ['GD32F50X', 'GD32F503VG']

/* 保持不变 - MCU型号宏定义 */
```

---

## 七、验证清单

编译前，请确保：
- [ ] 四个链接脚本的内存大小**互相一致**
- [ ] board.h 中的 `GD32_SRAM_SIZE` **与链接脚本匹配**
- [ ] SConscript 中的 MCU 宏定义**正确**
- [ ] Kconfig 中的 SOC_SERIES **与实际MCU对应**
- [ ] 所有文件的**编码格式为UTF-8**
- [ ] 没有**重复的宏定义**

---

## 八、常见错误及排查

| 现象 | 原因 | 解决方案 |
|------|------|--------|
| 链接错误：内存溢出 | RAM大小配置不一致 | 检查四个链接脚本是否都改过 |
| 编译错误：未定义宏 | SConscript 中 CPPDEFINES 错误 | 验证MCU型号宏是否正确 |
| 运行时栈溢出 | `_estack` 地址错误 | 重新计算：起始地址 + RAM大小 |
| Keil工程显示异常 | Kconfig 配置菜单错误 | 参考其他正确的项目的 Kconfig 格式 |

---

**最后更新**：2025年12月23日  
**适用于**：RT-Thread GD32 ARM BSP 系列
