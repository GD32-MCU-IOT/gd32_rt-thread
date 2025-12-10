#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2025, GD32-MCU-IOT Organization
#
# SPDX-License-Identifier: Apache-2.0
#
# GD32 BSP Build Wrapper
# 用途：在调用 bsp_buildings.py 前进行路径验证和错误处理
#

import os
import sys
import subprocess

def verify_bsp_paths():
    """验证所有 BSP 路径是否存在"""
    rtt_root = os.getcwd()
    srtt_bsp_env = os.getenv('SRTT_BSP')
    
    if not srtt_bsp_env:
        print("❌ 错误：SRTT_BSP 环境变量未设置")
        return False
    
    srtt_bsp = srtt_bsp_env.split(',')
    print(f"\n=== GD32 BSP 路径验证 ===")
    print(f"工作目录: {rtt_root}")
    print(f"待编译 BSP 数量: {len(srtt_bsp)}\n")
    
    all_valid = True
    for idx, bsp in enumerate(srtt_bsp, 1):
        bsp = bsp.strip()
        bsp_path = os.path.join(rtt_root, 'bsp', bsp)
        
        print(f"[{idx}/{len(srtt_bsp)}] 验证: {bsp}")
        
        # 检查目录是否存在
        if not os.path.exists(bsp_path):
            print(f"  ❌ 目录不存在: {bsp_path}")
            all_valid = False
            continue
        
        if not os.path.isdir(bsp_path):
            print(f"  ❌ 路径存在但不是目录: {bsp_path}")
            all_valid = False
            continue
        
        # 检查 Kconfig 是否存在
        kconfig_path = os.path.join(bsp_path, 'Kconfig')
        has_kconfig = os.path.exists(kconfig_path)
        
        # 检查 SConstruct 是否存在
        sconstruct_path = os.path.join(bsp_path, 'SConstruct')
        has_sconstruct = os.path.exists(sconstruct_path)
        
        print(f"  ✅ 目录存在")
        print(f"     路径: {bsp_path}")
        print(f"     Kconfig: {'✓' if has_kconfig else '✗'}")
        print(f"     SConstruct: {'✓' if has_sconstruct else '✗'}")
        
        # 列出目录内容（用于调试）
        try:
            files = os.listdir(bsp_path)
            print(f"     文件数: {len(files)}")
        except Exception as e:
            print(f"  ⚠️ 无法列出目录内容: {e}")
        
        print()
    
    return all_valid

def main():
    """主函数"""
    print("\n" + "="*70)
    print("  GD32 BSP CI 编译包装脚本")
    print("="*70 + "\n")
    
    # 步骤 1: 验证路径
    if not verify_bsp_paths():
        print("\n❌ BSP 路径验证失败！")
        print("   请检查以下内容：")
        print("   1. BSP 目录是否已提交到 Git")
        print("   2. GitHub Actions checkout 是否正确")
        print("   3. gd32_bsp_config.json 中的路径配置")
        sys.exit(1)
    
    print("✅ 所有 BSP 路径验证通过！\n")
    print("="*70)
    print("  开始调用 RT-Thread 编译脚本")
    print("="*70 + "\n")
    
    # 步骤 2: 调用原始编译脚本
    try:
        result = subprocess.run(
            [sys.executable, 'tools/ci/bsp_buildings.py'],
            check=False  # 不自动抛异常，我们自己处理返回值
        )
        
        if result.returncode != 0:
            print(f"\n❌ bsp_buildings.py 执行失败，退出码: {result.returncode}")
            sys.exit(result.returncode)
        
        print("\n✅ 编译完成")
        
    except Exception as e:
        print(f"\n❌ 调用 bsp_buildings.py 时发生异常: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

if __name__ == "__main__":
    main()
