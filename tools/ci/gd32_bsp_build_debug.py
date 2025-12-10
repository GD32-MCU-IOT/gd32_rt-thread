#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2025, GD32-MCU-IOT Organization
#
# SPDX-License-Identifier: Apache-2.0
#
# GD32 BSP Build Script with Enhanced Debugging
# 基于 RT-Thread bsp_buildings.py，添加了详细的调试信息
#

import os
import sys

# 在执行任何操作前，先检查关键目录
rtt_root = os.getcwd()
srtt_bsp_env = os.getenv('SRTT_BSP')

if not srtt_bsp_env:
    print("❌ 错误：SRTT_BSP 环境变量未设置")
    sys.exit(1)

srtt_bsp = srtt_bsp_env.split(',')

print("\n" + "="*80)
print("  GD32 BSP 编译前置检查")
print("="*80)
print(f"工作目录: {rtt_root}")
print(f"BSP 列表 ({len(srtt_bsp)} 个):")
for idx, bsp in enumerate(srtt_bsp, 1):
    bsp = bsp.strip()
    bsp_path = os.path.join(rtt_root, 'bsp', bsp)
    status = "✅ 存在" if os.path.exists(bsp_path) else "❌ 不存在"
    print(f"  [{idx:2d}] {status}: {bsp}")
    
    if not os.path.exists(bsp_path):
        print(f"       完整路径: {bsp_path}")
        # 检查父目录
        parent = os.path.dirname(bsp_path)
        if os.path.exists(parent):
            print(f"       父目录存在，内容:")
            try:
                for item in os.listdir(parent):
                    print(f"         - {item}")
            except Exception as e:
                print(f"         错误: {e}")

print("="*80 + "\n")

# 现在调用原始脚本，但先 patch os.chdir 函数
import functools

original_chdir = os.chdir

@functools.wraps(os.chdir)
def debug_chdir(path):
    """带调试信息的 chdir 包装函数"""
    abs_path = os.path.abspath(path)
    
    print(f"\n🔍 [DEBUG] os.chdir() 调用:")
    print(f"   目标路径: {path}")
    print(f"   绝对路径: {abs_path}")
    print(f"   路径存在: {os.path.exists(abs_path)}")
    print(f"   是否目录: {os.path.isdir(abs_path) if os.path.exists(abs_path) else 'N/A'}")
    print(f"   当前目录: {os.getcwd()}")
    
    if not os.path.exists(abs_path):
        print(f"\n❌ 错误：目标目录不存在！")
        print(f"   期望路径: {abs_path}")
        
        # 尝试找出问题
        parent = os.path.dirname(abs_path)
        if os.path.exists(parent):
            print(f"   父目录存在: {parent}")
            print(f"   父目录内容:")
            try:
                for item in sorted(os.listdir(parent)):
                    item_path = os.path.join(parent, item)
                    item_type = "DIR " if os.path.isdir(item_path) else "FILE"
                    print(f"     [{item_type}] {item}")
            except Exception as e:
                print(f"     列出失败: {e}")
        else:
            print(f"   父目录也不存在: {parent}")
        
        print(f"\n   调用堆栈:")
        import traceback
        traceback.print_stack()
        
        raise FileNotFoundError(f"目录不存在: {abs_path}")
    
    try:
        result = original_chdir(path)
        print(f"   ✅ chdir 成功，新目录: {os.getcwd()}\n")
        return result
    except Exception as e:
        print(f"   ❌ chdir 失败: {e}\n")
        raise

# 替换 os.chdir
os.chdir = debug_chdir

print("🔧 已启用 os.chdir() 调试模式\n")
print("="*80)
print("  开始执行 bsp_buildings.py")
print("="*80 + "\n")

# 导入并执行原始脚本
sys.path.insert(0, os.path.join(rtt_root, 'tools', 'ci'))

try:
    import bsp_buildings
    # bsp_buildings.py 的 main 代码在 if __name__ == "__main__" 块中
    # 我们需要直接调用它
    
    # 读取并执行脚本
    script_path = os.path.join(rtt_root, 'tools', 'ci', 'bsp_buildings.py')
    with open(script_path, 'r', encoding='utf-8') as f:
        code = f.read()
    
    # 执行脚本（在当前命名空间中）
    exec(code, {'__name__': '__main__'})
    
except Exception as e:
    print(f"\n❌ 执行失败: {e}")
    import traceback
    traceback.print_exc()
    sys.exit(1)
