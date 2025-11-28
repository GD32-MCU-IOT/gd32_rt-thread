#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
GD32H75E固件库验证脚本
验证packages目录下的固件库文件完整性
"""

import os
import sys

def check_packages_structure():
    """检查packages目录结构"""
    base_path = os.path.dirname(os.path.abspath(__file__))
    packages_path = os.path.join(base_path, "packages")
    
    print("=== GD32H75E 固件库结构验证 ===")
    print(f"基础路径: {base_path}")
    print(f"包路径: {packages_path}")
    print()
    
    # 检查主要目录
    required_dirs = [
        "packages/gd32-arm-cmsis-latest/GD32H75E",
        "packages/gd32-arm-series-latest/GD32H75E"
    ]
    
    all_exists = True
    for dir_path in required_dirs:
        full_path = os.path.join(base_path, dir_path)
        if os.path.exists(full_path):
            print(f"✅ {dir_path}")
        else:
            print(f"❌ {dir_path}")
            all_exists = False
    
    print()
    
    # 检查关键文件
    key_files = [
        "packages/gd32-arm-cmsis-latest/GD32H75E/GD/GD32H75E/Include/gd32h75e.h",
        "packages/gd32-arm-cmsis-latest/GD32H75E/GD/GD32H75E/Include/system_gd32h75e.h",
        "packages/gd32-arm-series-latest/GD32H75E/Include/gd32h75e_rcu.h",
        "packages/gd32-arm-series-latest/GD32H75E/Include/gd32h75e_gpio.h",
        "packages/gd32-arm-series-latest/GD32H75E/Include/gd32h75e_usart.h",
        "packages/gd32-arm-series-latest/GD32H75E/Source/gd32h75e_rcu.c",
        "packages/gd32-arm-series-latest/GD32H75E/Source/gd32h75e_gpio.c",
        "packages/gd32-arm-series-latest/GD32H75E/Source/gd32h75e_usart.c"
    ]
    
    print("关键文件检查:")
    for file_path in key_files:
        full_path = os.path.join(base_path, file_path)
        if os.path.exists(full_path):
            print(f"✅ {file_path}")
        else:
            print(f"❌ {file_path}")
            all_exists = False
    
    print()
    
    # 统计文件数量
    if all_exists:
        cmsis_path = os.path.join(base_path, "packages/gd32-arm-cmsis-latest/GD32H75E")
        series_path = os.path.join(base_path, "packages/gd32-arm-series-latest/GD32H75E")
        
        cmsis_count = count_files(cmsis_path)
        series_count = count_files(series_path)
        
        print("文件统计:")
        print(f"CMSIS库文件数: {cmsis_count}")
        print(f"标准外设库文件数: {series_count}")
        print(f"总文件数: {cmsis_count + series_count}")
        print()
    
    if all_exists:
        print("🎉 固件库拷贝验证通过!")
        return True
    else:
        print("❌ 固件库拷贝不完整，请检查!")
        return False

def count_files(path):
    """递归计算目录下的文件数量"""
    count = 0
    for root, dirs, files in os.walk(path):
        count += len(files)
    return count

if __name__ == "__main__":
    if check_packages_structure():
        sys.exit(0)
    else:
        sys.exit(1)
