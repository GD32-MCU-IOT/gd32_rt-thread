#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
GD32 ARM BSP Local Build Test Script
用于本地测试 GD32 ARM 系列 BSP 的编译完整性

English: This script tests all GD32 ARM BSP builds locally to ensure
         library changes don't break existing BSPs.
中文: 此脚本用于本地测试所有 GD32 ARM BSP 编译，确保库文件修改不影响现有 BSP。
"""

import os
import sys
import json
import subprocess
import datetime
import shutil
from pathlib import Path
from typing import List, Dict, Tuple

class Color:
    """终端颜色输出"""
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    CYAN = '\033[96m'
    END = '\033[0m'
    BOLD = '\033[1m'
    
    @staticmethod
    def print_error(msg):
        print(f"{Color.RED}❌ {msg}{Color.END}")
    
    @staticmethod
    def print_success(msg):
        print(f"{Color.GREEN}✅ {msg}{Color.END}")
    
    @staticmethod
    def print_warning(msg):
        print(f"{Color.YELLOW}⚠️  {msg}{Color.END}")
    
    @staticmethod
    def print_info(msg):
        print(f"{Color.BLUE}ℹ️  {msg}{Color.END}")
    
    @staticmethod
    def print_step(msg):
        print(f"{Color.CYAN}➜ {msg}{Color.END}")

class GD32BuildTester:
    def __init__(self, config_file: str = None, clean_build: bool = None):
        """
        初始化构建测试器
        
        Args:
            config_file: 配置文件路径，默认优先使用脚本同目录下的 local_build_test.json
            clean_build: 是否执行清理编译（优先于配置文件）
        """
        self.rtt_root = self._find_rtt_root()
        self.gd32_arm_path = self.rtt_root / "bsp" / "gd32" / "arm"
        
        # 加载配置
        if config_file is None:
            # 优先使用统一配置文件 gd32_bsp_config.json
            script_dir = Path(__file__).parent
            config_file = script_dir / "gd32_bsp_config.json"
            
            # 向后兼容：如果统一配置不存在，尝试旧配置
            if not config_file.exists():
                Color.print_warning("gd32_bsp_config.json not found, trying legacy local_build_test.json")
                config_file = script_dir / "local_build_test.json"
                if not config_file.exists():
                    config_file = self.gd32_arm_path / "local_build_test.json"
        
        self.config = self._load_config(config_file)
        self.test_bsps = self.config.get("test_bsps", [])
        self.excluded_bsps = self.config.get("excluded_bsps", [])
        
        # 清理选项：命令行参数优先，否则使用配置文件
        if clean_build is not None:
            self.clean_build = clean_build
        else:
            self.clean_build = self.config.get("clean_build", False)
        
        self.clean_method = self.config.get("clean_method", "both")  # "scons" | "rmdir" | "both"
        self.keep_build_dir = self.config.get("keep_build_dir", False)
        
        # 临时 Kconfig 选项（仅在编译时生效，编译后恢复）
        self.temp_kconfig_options = self.config.get("temp_kconfig_options", [])
        if self.temp_kconfig_options:
            Color.print_info(f"Temporary Kconfig options enabled: {len(self.temp_kconfig_options)} options")
        
        # 测试结果
        self.results = {
            "success": [],
            "failed": [],
            "skipped": []
        }
        
        # 日志目录：与脚本同级的 build_logs 文件夹
        script_dir = Path(__file__).parent
        self.log_dir = script_dir / "build_logs"
        self.log_dir.mkdir(exist_ok=True)
        Color.print_info(f"Log directory: {self.log_dir}")
        
        # 统计信息
        self.start_time = None
        self.end_time = None
        
    def _find_rtt_root(self) -> Path:
        """查找 RT-Thread 根目录"""
        current = Path.cwd()
        
        # 向上查找包含 bsp 和 src 目录的路径
        while current != current.parent:
            if (current / "bsp").exists() and (current / "src").exists():
                return current
            current = current.parent
        
        Color.print_error("Cannot find RT-Thread root directory!")
        Color.print_info("Please run this script from within the RT-Thread repository")
        sys.exit(1)
    
    def _load_config(self, config_file: Path) -> Dict:
        """加载配置文件"""
        if not config_file.exists():
            Color.print_warning(f"Config file not found: {config_file}")
            Color.print_info("Using default configuration with all detected BSPs")
            # 使用默认配置
            return {
                "test_bsps": self._detect_all_bsps(),
                "excluded_bsps": [],
                "toolchain": "sourcery-arm",
                "parallel_jobs": 4
            }
        
        try:
            with open(config_file, 'r', encoding='utf-8') as f:
                raw_config = json.load(f)
                
                # 检查是否是统一配置文件（包含 'local_test' 字段）
                if 'local_test' in raw_config:
                    Color.print_success(f"Loaded unified config from: {config_file}")
                    Color.print_info("Using 'local_test' section for local build configuration")
                    config = raw_config['local_test']
                    
                    # 检查是否标记为废弃
                    if raw_config.get('_deprecated'):
                        Color.print_warning(f"⚠️  Config file is deprecated: {raw_config.get('_migration_note', '')}")
                        if raw_config.get('_new_file'):
                            Color.print_info(f"Please use: {raw_config['_new_file']}")
                else:
                    # 旧格式配置文件
                    Color.print_success(f"Loaded legacy config from: {config_file}")
                    config = raw_config
                    
                    # 检查是否标记为废弃
                    if config.get('_deprecated'):
                        Color.print_warning(f"⚠️  Config file is deprecated: {config.get('_migration_note', '')}")
                        if config.get('_new_file'):
                            Color.print_info(f"Please use: {config['_new_file']}")
                
                return config
        except Exception as e:
            Color.print_error(f"Failed to load config: {e}")
            sys.exit(1)
    
    def _detect_all_bsps(self) -> List[str]:
        """自动检测所有 GD32 ARM BSP"""
        bsps = []
        for item in self.gd32_arm_path.iterdir():
            if item.is_dir() and not item.name.startswith('.') and item.name not in ['libraries', 'tools', 'docs', 'scripts']:
                # 检查是否包含 SConstruct 文件
                if (item / "SConstruct").exists():
                    bsps.append(item.name)
        return sorted(bsps)
    
    def _check_env(self) -> bool:
        """检查编译环境"""
        Color.print_step("Checking build environment...")
        
        # 检查 scons
        try:
            result = subprocess.run(['scons', '--version'], 
                                  capture_output=True, text=True, timeout=10)
            if result.returncode == 0:
                version_line = result.stdout.splitlines()[0] if result.stdout else "Unknown version"
                Color.print_success(f"SCons found: {version_line}")
            else:
                Color.print_error("SCons not found!")
                return False
        except FileNotFoundError:
            Color.print_error("SCons not installed!")
            Color.print_info("Please install: pip install scons")
            return False
        except subprocess.TimeoutExpired:
            Color.print_error("SCons check timeout!")
            return False
        
        # 检查工具链
        gcc_name = "arm-none-eabi-gcc"
        
        try:
            result = subprocess.run([gcc_name, '--version'],
                                  capture_output=True, text=True, timeout=10)
            if result.returncode == 0:
                version_line = result.stdout.splitlines()[0] if result.stdout else "Unknown version"
                Color.print_success(f"Toolchain found: {version_line}")
            else:
                Color.print_warning(f"Toolchain '{gcc_name}' not found in PATH")
                Color.print_info("Make sure ARM GCC toolchain is in PATH or set RTT_EXEC_PATH")
                return False
        except FileNotFoundError:
            Color.print_warning(f"Toolchain '{gcc_name}' not found!")
            Color.print_info("Make sure ARM GCC toolchain is in PATH or set RTT_EXEC_PATH")
            return False
        except subprocess.TimeoutExpired:
            Color.print_error("Toolchain check timeout!")
            return False
        
        # 检查 pkgs 工具（可选，但推荐）
        try:
            result = subprocess.run(['pkgs', '--version'],
                                  capture_output=True, text=True, timeout=10)
            if result.returncode == 0:
                Color.print_success(f"RT-Thread pkgs tool found")
            else:
                Color.print_warning("pkgs tool not found (optional)")
                Color.print_info("Some BSPs may need packages. Install RT-Thread env tools if needed")
        except FileNotFoundError:
            Color.print_warning("pkgs tool not found (optional)")
            Color.print_info("Some BSPs may need packages. Install RT-Thread env tools if needed")
        except subprocess.TimeoutExpired:
            Color.print_warning("pkgs check timeout!")
        
        Color.print_success("Environment check passed!\n")
        return True
    
    def _cleanup_bsp_artifacts(self, bsp_path: Path, bsp_name: str, verbose: bool = False) -> Tuple[int, List[str]]:
        """
        清理单个 BSP 的所有编译产物和中间文件（用于提交前清理）
        
        Args:
            bsp_path: BSP 路径
            bsp_name: BSP 名称
            verbose: 是否显示详细信息
            
        Returns:
            (removed_count, removed_files)
        """
        removed_files = []
        removed_count = 0
        
        # 1. 删除 build/ 目录
        build_dir = bsp_path / "build"
        if build_dir.exists():
            try:
                shutil.rmtree(build_dir)
                removed_files.append(f"build/")
                removed_count += 1
                if verbose:
                    Color.print_info(f"    Removed: {bsp_name}/build/")
            except Exception as e:
                if verbose:
                    Color.print_warning(f"    Failed to remove {bsp_name}/build/: {e}")
        
        # 2. 删除编译输出文件
        output_patterns = [
            'rtthread.bin', 'rtthread.elf', 'rtthread.hex', 'rtthread.map',
            'rtthread.axf', 'rtthread.lst', 'rtthread.asm',
            '*.o', '*.obj', '*.d', '*.dep', '*.a', '*.lib'
        ]
        
        for pattern in output_patterns:
            for file in bsp_path.glob(pattern):
                if file.is_file():
                    try:
                        file.unlink()
                        removed_files.append(file.name)
                        removed_count += 1
                        if verbose:
                            Color.print_info(f"    Removed: {bsp_name}/{file.name}")
                    except Exception as e:
                        if verbose:
                            Color.print_warning(f"    Failed to remove {file}: {e}")
        
        # 3. 删除 .sconsign.dblite 文件
        sconsign = bsp_path / ".sconsign.dblite"
        if sconsign.exists():
            try:
                sconsign.unlink()
                removed_files.append(".sconsign.dblite")
                removed_count += 1
                if verbose:
                    Color.print_info(f"    Removed: {bsp_name}/.sconsign.dblite")
            except Exception as e:
                if verbose:
                    Color.print_warning(f"    Failed to remove .sconsign.dblite: {e}")
        
        # 4. 删除 cconfig.h (Kconfig 生成的临时文件)
        cconfig = bsp_path / "cconfig.h"
        if cconfig.exists():
            try:
                cconfig.unlink()
                removed_files.append("cconfig.h")
                removed_count += 1
                if verbose:
                    Color.print_info(f"    Removed: {bsp_name}/cconfig.h")
            except Exception as e:
                if verbose:
                    Color.print_warning(f"    Failed to remove cconfig.h: {e}")
        
        return removed_count, removed_files
    
    def cleanup_all_bsps(self, bsp_list: List[str] = None, verbose: bool = False):
        """
        清理所有（或指定）BSP 的编译产物，用于提交前清理
        
        Args:
            bsp_list: 要清理的 BSP 列表，None 表示清理所有
            verbose: 是否显示详细信息
        """
        print("\n" + "="*80)
        print(f"{Color.BOLD}🧹 Cleanup All BSP Build Artifacts{Color.END}")
        print("="*80 + "\n")
        
        # 确定要清理的 BSP 列表
        if bsp_list:
            cleanup_list = bsp_list
            Color.print_info(f"Cleaning up {len(cleanup_list)} specified BSPs...")
        else:
            cleanup_list = [bsp for bsp in self.test_bsps if bsp not in self.excluded_bsps]
            Color.print_info(f"Cleaning up all {len(cleanup_list)} BSPs...")
        
        if verbose:
            Color.print_info(f"BSPs to clean: {', '.join(cleanup_list)}\n")
        
        total_removed = 0
        total_bsps = 0
        failed_bsps = []
        
        for i, bsp_name in enumerate(cleanup_list, 1):
            bsp_path = self.gd32_arm_path / bsp_name
            
            if not bsp_path.exists():
                Color.print_warning(f"[{i}/{len(cleanup_list)}] BSP not found: {bsp_name}")
                failed_bsps.append(bsp_name)
                continue
            
            if verbose:
                print(f"\n[{i}/{len(cleanup_list)}] Cleaning {bsp_name}...")
            else:
                print(f"[{i}/{len(cleanup_list)}] {bsp_name}...", end=' ', flush=True)
            
            try:
                removed_count, removed_files = self._cleanup_bsp_artifacts(bsp_path, bsp_name, verbose)
                total_removed += removed_count
                total_bsps += 1
                
                if not verbose:
                    if removed_count > 0:
                        Color.print_success(f"✓ ({removed_count} items)")
                    else:
                        print(f"{Color.BLUE}✓ (clean){Color.END}")
                
            except Exception as e:
                if verbose:
                    Color.print_error(f"Failed to clean {bsp_name}: {e}")
                else:
                    Color.print_error(f"✗ {str(e)}")
                failed_bsps.append(bsp_name)
        
        # 打印总结
        print("\n" + "="*80)
        print(f"{Color.BOLD}Cleanup Summary{Color.END}")
        print("="*80)
        Color.print_success(f"Cleaned BSPs:     {total_bsps}/{len(cleanup_list)}")
        Color.print_info(f"Files removed:    {total_removed}")
        
        if failed_bsps:
            Color.print_error(f"Failed BSPs:      {len(failed_bsps)}")
            for bsp in failed_bsps:
                print(f"  ❌ {bsp}")
        else:
            Color.print_success("All BSPs cleaned successfully! 🎉")
        
        print("="*80 + "\n")
        Color.print_info("💡 Tip: Now you can safely commit your changes without build artifacts")
        print()
    
    def _clean_bsp(self, bsp_path: Path, bsp_name: str) -> Tuple[bool, str]:
        """
        清理 BSP 编译产物（用于清理编译）
        
        Args:
            bsp_path: BSP 路径
            bsp_name: BSP 名称
            
        Returns:
            (success, log_content)
        """
        log_content = []
        log_content.append(f"{'='*80}\n")
        log_content.append(f"Clean Log for {bsp_name}\n")
        log_content.append(f"{'='*80}\n")
        log_content.append(f"Clean Method: {self.clean_method}\n")
        log_content.append(f"Time: {datetime.datetime.now()}\n\n")
        
        try:
            # 方法 1: 使用 scons -c (推荐)
            if self.clean_method in ["scons", "both"]:
                Color.print_info(f"    Running 'scons -c' for {bsp_name}...")
                result = subprocess.run(
                    ['scons', '-c'],
                    cwd=bsp_path,
                    capture_output=True,
                    text=True,
                    timeout=60
                )
                
                log_content.append("--- SCons Clean Output ---\n")
                log_content.append(result.stdout if result.stdout else "(no output)\n")
                if result.stderr:
                    log_content.append("\n--- SCons Clean Stderr ---\n")
                    log_content.append(result.stderr)
                log_content.append("\n")
            
            # 方法 2: 删除 build/ 目录
            if self.clean_method in ["rmdir", "both"]:
                build_dir = bsp_path / "build"
                if build_dir.exists():
                    Color.print_info(f"    Removing build directory for {bsp_name}...")
                    shutil.rmtree(build_dir)
                    log_content.append(f"Removed build directory: {build_dir}\n")
                else:
                    log_content.append(f"Build directory not found (skipped): {build_dir}\n")
            
            # 方法 3: 删除输出文件
            removed_files = []
            for ext in ['bin', 'elf', 'hex', 'map', 'axf', 'lib', 'a']:
                for pattern in [f"rtthread.{ext}", f"*.{ext}"]:
                    for output_file in bsp_path.glob(pattern):
                        if output_file.is_file():
                            output_file.unlink()
                            removed_files.append(output_file.name)
            
            if removed_files:
                log_content.append(f"\nRemoved output files: {', '.join(removed_files)}\n")
            
            log_content.append("\n" + "="*80 + "\n")
            log_content.append("Clean Result: ✅ SUCCESS\n")
            log_content.append("="*80 + "\n")
            
            Color.print_success(f"    Clean {bsp_name} completed")
            return True, ''.join(log_content)
            
        except subprocess.TimeoutExpired:
            error_msg = "Clean timeout (>60s)"
            log_content.append(f"\n❌ {error_msg}\n")
            Color.print_error(f"    {bsp_name}: {error_msg}")
            return False, ''.join(log_content)
            
        except Exception as e:
            error_msg = f"Clean exception: {str(e)}"
            log_content.append(f"\n❌ {error_msg}\n")
            Color.print_error(f"    {bsp_name}: {error_msg}")
            return False, ''.join(log_content)
    
    def _extract_required_packages(self, config_content: str) -> set:
        """
        从 .config 文件内容中提取所需的软件包名称
        
        Args:
            config_content: .config 文件内容
            
        Returns:
            所需软件包名称的集合
        """
        import re
        required_packages = set()
        
        # 匹配 CONFIG_PKG_USING_XXX=y 的行（注意 CONFIG_ 前缀）
        # 排除 _LATEST_VERSION, _EXAMPLE, _SAMPLE 等后缀
        pattern = r'CONFIG_PKG_USING_([A-Z0-9_]+?)(?:_LATEST_VERSION|_EXAMPLE|_SAMPLE)?=y'
        matches = re.findall(pattern, config_content)
        
        for match in matches:
            # 跳过版本选择等配置项
            if match.endswith('_LATEST_VERSION') or match.endswith('_EXAMPLE') or match.endswith('_SAMPLE'):
                continue
            
            # 将包名转换为小写并替换下划线为连字符
            # 例如: AT24CXX -> at24cxx, GD32_ARM_CMSIS_DRIVER -> gd32-arm-cmsis-driver
            pkg_name = match.lower().replace('_', '-')
            required_packages.add(pkg_name)
            
            # 同时保留原始名称（某些包名可能保留大小写或下划线）
            required_packages.add(match.lower())  # 全小写版本
        
        return required_packages
    
    def _validate_package(self, pkg_path: Path) -> bool:
        """
        验证软件包目录是否完整有效
        
        Args:
            pkg_path: 软件包目录路径
            
        Returns:
            是否有效
        """
        if not pkg_path.exists() or not pkg_path.is_dir():
            return False
        
        # 检查是否有源文件或头文件（至少有一个）
        has_source = any(pkg_path.rglob('*.c'))
        has_header = any(pkg_path.rglob('*.h'))
        
        # 至少要有头文件或源文件
        return has_source or has_header
    
    def _check_packages_status(self, bsp_path: Path, config_content: str) -> Tuple[bool, set, set]:
        """
        检查软件包状态，判断是否需要执行 pkgs --update
        
        Args:
            bsp_path: BSP 路径
            config_content: .config 文件内容
            
        Returns:
            (need_update, required_packages, valid_existing_packages)
            - need_update: 是否需要执行 pkgs --update
            - required_packages: 所需的软件包集合
            - valid_existing_packages: 已存在且有效的软件包集合
        """
        packages_dir = bsp_path / "packages"
        required_packages = self._extract_required_packages(config_content)
        
        if not required_packages:
            # 没有配置任何软件包
            return False, set(), set()
        
        if not packages_dir.exists():
            # packages 目录不存在，需要更新
            return True, required_packages, set()
        
        # 检查已存在的软件包
        valid_existing_packages = set()
        existing_package_names = set()
        for pkg_dir in packages_dir.iterdir():
            if pkg_dir.is_dir() and not pkg_dir.name.startswith('.'):
                if self._validate_package(pkg_dir):
                    valid_existing_packages.add(pkg_dir.name)
                    # 同时记录包名的各种可能形式（用于模糊匹配）
                    existing_package_names.add(pkg_dir.name.lower())
                    existing_package_names.add(pkg_dir.name.lower().replace('-', '_'))
                    existing_package_names.add(pkg_dir.name.lower().replace('_', '-'))
        
        if not valid_existing_packages:
            # 没有有效的软件包，需要更新
            return True, required_packages, valid_existing_packages
        
        # 检查是否所有需要的包都已存在
        # 采用模糊匹配策略：检查包名的各种变体是否存在
        missing_packages = set()
        for required_pkg in required_packages:
            # 尝试多种匹配方式
            pkg_variants = {
                required_pkg,
                required_pkg.replace('-', '_'),
                required_pkg.replace('_', '-'),
            }
            
            # 检查是否有任何变体匹配
            found_exact = any(variant in existing_package_names for variant in pkg_variants)
            
            if not found_exact:
                # 未找到精确匹配，尝试部分匹配（包名可能包含版本后缀）
                # 例如: at24cxx 匹配 at24cxx-latest
                #      gd32-arm-cmsis-driver 匹配 gd32-arm-cmsis-latest
                found_partial = False
                for existing_pkg in valid_existing_packages:
                    existing_lower = existing_pkg.lower()
                    required_lower = required_pkg.lower()
                    
                    # 检查包名是否为已存在包的前缀（考虑版本后缀）
                    # 例如: "gd32-arm-cmsis" 是 "gd32-arm-cmsis-latest" 的前缀
                    if existing_lower.startswith(required_lower) or required_lower.startswith(existing_lower):
                        # 进一步检查：确保是合理的前缀匹配，不是偶然的部分重叠
                        # 分割包名，检查主要部分是否匹配
                        existing_parts = existing_lower.replace('-', ' ').replace('_', ' ').split()
                        required_parts = required_lower.replace('-', ' ').replace('_', ' ').split()
                        
                        # 检查主要部分是否大部分重叠
                        common_parts = set(existing_parts) & set(required_parts)
                        if len(common_parts) >= min(len(existing_parts), len(required_parts)) - 1:
                            found_partial = True
                            break
                
                if not found_partial:
                    missing_packages.add(required_pkg)
        
        # 如果有缺失的包，需要更新
        if missing_packages:
            Color.print_warning(f"    ⚠ Missing packages detected: {', '.join(sorted(missing_packages))}")
            return True, required_packages, valid_existing_packages
        
        # 所有需要的包都已存在
        return False, required_packages, valid_existing_packages
    
    def _backup_config_files(self, bsp_path: Path) -> List[Path]:
        """
        备份配置文件
        
        Args:
            bsp_path: BSP 路径
            
        Returns:
            备份的文件列表
        """
        backup_files = []
        config_file = bsp_path / ".config"
        rtconfig_file = bsp_path / "rtconfig.h"
        
        for f in (config_file, rtconfig_file):
            if f.exists():
                backup_path = f.with_suffix(f.suffix + ".bak")
                shutil.copy2(f, backup_path)
                backup_files.append(f)
        
        return backup_files
    
    def _restore_config_files(self, backup_files: List[Path]):
        """
        恢复配置文件
        
        Args:
            backup_files: 需要恢复的文件列表
        """
        for f in backup_files:
            backup_path = f.with_suffix(f.suffix + ".bak")
            if backup_path.exists():
                shutil.move(str(backup_path), str(f))
    
    def _patch_kconfig(self, config_file: Path, options: List[str]) -> bool:
        """
        临时修改 .config 文件
        
        Args:
            config_file: .config 文件路径
            options: 选项列表，格式如 ["CONFIG_RT_USING_I2C=y", "CONFIG_RT_USING_SPI=y"]
            
        Returns:
            是否修改成功
        """
        if not config_file.exists():
            Color.print_warning(f"Config file not found: {config_file}")
            return False
        
        try:
            # 读取原配置
            with open(config_file, 'r', encoding='utf-8') as f:
                lines = f.readlines()
            
            # 解析选项
            options_dict = {}
            for opt in options:
                if '=' in opt:
                    key, value = opt.split('=', 1)
                    options_dict[key.strip()] = value.strip()
            
            # 修改配置
            modified_lines = []
            modified_keys = set()
            
            for line in lines:
                line_stripped = line.strip()
                modified = False
                
                # 检查每个需要修改的选项
                for key, value in options_dict.items():
                    # 情况 1: # CONFIG_XXX is not set
                    if line_stripped == f"# {key} is not set":
                        if value.lower() == 'y':
                            modified_lines.append(f"{key}=y\n")
                            modified_keys.add(key)
                            modified = True
                            break
                    
                    # 情况 2: CONFIG_XXX=y 或 CONFIG_XXX=n
                    elif line_stripped.startswith(f"{key}="):
                        modified_lines.append(f"{key}={value}\n")
                        modified_keys.add(key)
                        modified = True
                        break
                
                if not modified:
                    modified_lines.append(line)
            
            # 添加不存在的选项
            for key, value in options_dict.items():
                if key not in modified_keys:
                    modified_lines.append(f"{key}={value}\n")
            
            # 写回文件
            with open(config_file, 'w', encoding='utf-8') as f:
                f.writelines(modified_lines)
            
            return True
            
        except Exception as e:
            Color.print_error(f"Failed to patch .config: {e}")
            return False
    
    def _build_bsp(self, bsp_name: str) -> Tuple[bool, str]:
        """
        编译单个 BSP
        
        Returns:
            (success, log_content)
        """
        bsp_path = self.gd32_arm_path / bsp_name
        log_file = self.log_dir / f"{bsp_name}.log"
        
        Color.print_step(f"Building {bsp_name}...")
        
        log_content = []
        log_content.append(f"{'='*80}\n")
        log_content.append(f"Build Log for {bsp_name}\n")
        log_content.append(f"{'='*80}\n")
        log_content.append(f"Time: {datetime.datetime.now()}\n")
        log_content.append(f"BSP Path: {bsp_path}\n")
        log_content.append(f"Clean Build: {self.clean_build}\n")
        if self.temp_kconfig_options:
            log_content.append(f"Temp Kconfig Options: {self.temp_kconfig_options}\n")
        log_content.append(f"{'='*80}\n\n")
        
        # 备份配置文件（如果需要临时修改）
        backup_files = []
        if self.temp_kconfig_options:
            backup_files = self._backup_config_files(bsp_path)
            if backup_files:
                Color.print_info(f"  [Backup] Config files backed up for temporary modifications")
                log_content.append("--- Config Backup ---\n")
                log_content.append(f"Backed up: {[f.name for f in backup_files]}\n\n")
        
        try:
            # 步骤 0: 清理（如果启用）
            if self.clean_build:
                Color.print_info(f"  [0/5] Cleaning {bsp_name}...")
                clean_success, clean_log = self._clean_bsp(bsp_path, bsp_name)
                log_content.append("--- Step 0: Clean ---\n")
                log_content.append(clean_log)
                log_content.append("\n")
                
                if not clean_success:
                    Color.print_warning(f"  Clean failed, but continuing build...")
            
            # 步骤 1: 配置 BSP（初次）
            step_offset = 1 if self.clean_build else 0
            Color.print_info(f"  [{step_offset}/5] Configuring {bsp_name}...")
            result = subprocess.run(
                ['scons', '--pyconfig-silent'],
                cwd=bsp_path,
                capture_output=True,
                text=True,
                timeout=60
            )
            log_content.append("--- Step 1: Configuration (Initial) ---\n")
            log_content.append(result.stdout)
            if result.stderr:
                log_content.append("=== Stderr ===\n")
                log_content.append(result.stderr)
            log_content.append("\n")
            
            # 步骤 1.5: 应用临时配置（如果有）
            if self.temp_kconfig_options:
                Color.print_info(f"  [{step_offset}+] Applying temporary Kconfig options...")
                config_file = bsp_path / ".config"
                
                if self._patch_kconfig(config_file, self.temp_kconfig_options):
                    Color.print_success(f"    ✓ Applied {len(self.temp_kconfig_options)} temporary options")
                    log_content.append("--- Step 1.5: Apply Temporary Kconfig ---\n")
                    log_content.append(f"Temporary options:\n")
                    for opt in self.temp_kconfig_options:
                        log_content.append(f"  - {opt}\n")
                    log_content.append("\n")
                    
                    # 重新生成 rtconfig.h
                    Color.print_info(f"    Regenerating rtconfig.h with temporary options...")
                    result = subprocess.run(
                        ['scons', '--pyconfig-silent'],
                        cwd=bsp_path,
                        capture_output=True,
                        text=True,
                        timeout=60
                    )
                    log_content.append("--- Regenerate rtconfig.h ---\n")
                    log_content.append(result.stdout)
                    if result.stderr:
                        log_content.append("=== Stderr ===\n")
                        log_content.append(result.stderr)
                    log_content.append("\n")
                else:
                    Color.print_warning(f"    Failed to apply temporary options, continuing with original config")
            
            # 步骤 2: 更新软件包（使用 pkgs --update）
            Color.print_info(f"  [{step_offset+1}/5] Checking packages for {bsp_name}...")
            
            # 检查是否需要更新软件包（查看 .config 中是否启用了软件包）
            rtconfig_file = bsp_path / ".config"
            need_pkgs_update = False
            required_packages = set()
            valid_existing_packages = set()
            
            if rtconfig_file.exists():
                try:
                    with open(rtconfig_file, 'r', encoding='utf-8') as f:
                        config_content = f.read()
                        
                        # 检查软件包状态
                        if 'PKG_USING_' in config_content:
                            need_pkgs_update, required_packages, valid_existing_packages = \
                                self._check_packages_status(bsp_path, config_content)
                            
                            if not need_pkgs_update and valid_existing_packages:
                                Color.print_success(f"    ✓ All required packages already exist ({len(valid_existing_packages)} packages)")
                                Color.print_info(f"      Packages: {', '.join(sorted(valid_existing_packages))}")
                                log_content.append("--- Step 2: Package Check ---\n")
                                log_content.append(f"All required packages already exist, skipping pkgs --update\n")
                                log_content.append(f"Existing packages ({len(valid_existing_packages)}): {', '.join(sorted(valid_existing_packages))}\n\n")
                        else:
                            # 没有配置任何软件包
                            need_pkgs_update = False
                            
                except Exception as e:
                    Color.print_warning(f"    Cannot read .config: {e}")
                    need_pkgs_update = True  # 读取失败时保守地执行更新
            
            if need_pkgs_update:
                if required_packages:
                    Color.print_info(f"    Running 'pkgs --update' (need packages)...")
                else:
                    Color.print_info(f"    Running 'pkgs --update' for {bsp_name}...")
                
                # 记录软件包目录更新前的状态
                packages_dir = bsp_path / "packages"
                pkg_dirs_before = set()
                if packages_dir.exists():
                    pkg_dirs_before = {d.name for d in packages_dir.iterdir() if d.is_dir() and not d.name.startswith('.')}
                
                try:
                    result = subprocess.run(
                        ['pkgs', '--update'],
                        cwd=bsp_path,
                        capture_output=True,
                        text=True,
                        timeout=300  # 5分钟超时，因为可能需要下载软件包
                    )
                    log_content.append("--- Step 2: Package Update (pkgs --update) ---\n")
                    log_content.append(result.stdout if result.stdout else "(no output)\n")
                    if result.stderr:
                        log_content.append("\n=== Stderr ===\n")
                        log_content.append(result.stderr)
                    log_content.append("\n")
                    
                    # 验证软件包是否真正下载成功
                    pkg_update_success = False
                    pkg_error_msg = None
                    
                    # 检查返回码
                    if result.returncode != 0:
                        pkg_error_msg = f"pkgs --update returned non-zero exit code: {result.returncode}"
                    else:
                        # 检查 packages 目录是否存在且有内容
                        if not packages_dir.exists():
                            pkg_error_msg = "packages directory does not exist after pkgs --update"
                        else:
                            pkg_dirs_after = {d.name for d in packages_dir.iterdir() if d.is_dir() and not d.name.startswith('.')}
                            
                            # 检查是否有新的软件包目录
                            if len(pkg_dirs_after) == 0:
                                pkg_error_msg = "packages directory is empty after pkgs --update"
                            else:
                                # 检查输出中是否有错误信息
                                output_lower = (result.stdout + result.stderr).lower()
                                error_keywords = ['error', 'failed', 'cannot', 'not found', 'timeout']
                                has_error = any(keyword in output_lower for keyword in error_keywords)
                                
                                if has_error and len(pkg_dirs_after) == len(pkg_dirs_before):
                                    # 有错误信息且软件包数量没有变化
                                    pkg_error_msg = "pkgs --update reported errors and no new packages were downloaded"
                                else:
                                    # 验证至少有一个软件包目录包含文件
                                    has_valid_pkg = False
                                    for pkg_dir in pkg_dirs_after:
                                        pkg_path = packages_dir / pkg_dir
                                        # 检查是否有源文件或头文件
                                        if any(pkg_path.rglob('*.c')) or any(pkg_path.rglob('*.h')):
                                            has_valid_pkg = True
                                            break
                                    
                                    if has_valid_pkg:
                                        pkg_update_success = True
                                        new_pkgs = pkg_dirs_after - pkg_dirs_before
                                        if new_pkgs:
                                            Color.print_success(f"    Packages updated successfully (added: {', '.join(new_pkgs)})")
                                            log_content.append(f"New packages downloaded: {', '.join(new_pkgs)}\n")
                                        else:
                                            Color.print_success(f"    Packages verified successfully ({len(pkg_dirs_after)} packages)")
                                            log_content.append(f"Existing packages verified: {', '.join(pkg_dirs_after)}\n")
                                    else:
                                        pkg_error_msg = "packages directory exists but contains no valid source files"
                    
                    # 如果验证失败，记录错误
                    if not pkg_update_success:
                        Color.print_error(f"    Package update failed: {pkg_error_msg}")
                        log_content.append(f"\n❌ Package Update Verification Failed:\n")
                        log_content.append(f"   {pkg_error_msg}\n")
                        log_content.append(f"   This may cause compilation errors if packages are required.\n\n")
                        
                        # 检查是否有必需的软件包配置
                        if 'PKG_USING_' in config_content:
                            Color.print_warning(f"    BSP has package configurations but packages failed to download!")
                            Color.print_info(f"    Please check:")
                            Color.print_info(f"      1. Network connection")
                            Color.print_info(f"      2. RT-Thread env tools installation")
                            Color.print_info(f"      3. Package source configuration")
                        
                except FileNotFoundError:
                    Color.print_warning(f"    'pkgs' command not found, skipping package update")
                    log_content.append("--- Step 2: Package Update ---\n")
                    log_content.append("WARNING: 'pkgs' command not found, skipped\n")
                    log_content.append("Please install RT-Thread env tools or add pkgs to PATH\n\n")
                except subprocess.TimeoutExpired:
                    Color.print_error(f"    Package update timeout (>300s)")
                    log_content.append("--- Step 2: Package Update ---\n")
                    log_content.append("ERROR: Package update timeout\n\n")
                except Exception as e:
                    Color.print_warning(f"    Package update failed: {e}")
                    log_content.append("--- Step 2: Package Update ---\n")
                    log_content.append(f"ERROR: {str(e)}\n\n")
            elif not rtconfig_file.exists():
                Color.print_info(f"    No .config file found, skipping package check")
                log_content.append("--- Step 2: Package Check ---\n")
                log_content.append("No .config file found\n\n")
            # else: 包已存在的情况已在前面处理（need_pkgs_update == False 且有 valid_existing_packages）
            
            # 步骤 3: 编译
            Color.print_info(f"  [{step_offset+2}/5] Compiling {bsp_name}...")
            parallel_jobs = self.config.get("parallel_jobs", 4)
            result = subprocess.run(
                ['scons', f'-j{parallel_jobs}'],
                cwd=bsp_path,
                capture_output=True,
                text=True,
                timeout=600
            )
            
            log_content.append("--- Step 3: Compilation ---\n")
            log_content.append(result.stdout)
            if result.stderr:
                log_content.append("\n=== Stderr ===\n")
                log_content.append(result.stderr)
            log_content.append("\n")
            
            # 检查编译结果
            success = False
            if (bsp_path / "rtthread.bin").exists() or (bsp_path / "rtthread.elf").exists():
                success = True
                log_content.append("="*80 + "\n")
                log_content.append("Build Result: ✅ SUCCESS\n")
                log_content.append("="*80 + "\n")
                
                # 记录编译产物大小
                for ext in ['bin', 'elf', 'hex', 'map']:
                    output_file = bsp_path / f"rtthread.{ext}"
                    if output_file.exists():
                        size = output_file.stat().st_size
                        log_content.append(f"  rtthread.{ext}: {size:,} bytes\n")
                
                Color.print_success(f"Build {bsp_name} successful ✓")
            else:
                log_content.append("="*80 + "\n")
                log_content.append("Build Result: ❌ FAILED - No output binary found\n")
                log_content.append("="*80 + "\n")
                Color.print_error(f"Build {bsp_name} failed ✗")
            
            # 步骤 4: 恢复配置文件（如果有备份）
            if backup_files:
                Color.print_info(f"  [{step_offset+3}/5] Restoring original config files...")
                self._restore_config_files(backup_files)
                Color.print_success(f"    ✓ Config files restored")
                log_content.append("\n--- Step 4: Restore Config ---\n")
                log_content.append(f"Restored: {[f.name for f in backup_files]}\n")
                log_content.append("Original configuration preserved\n\n")
            
            # 写入日志
            full_log = ''.join(log_content)
            with open(log_file, 'w', encoding='utf-8') as f:
                f.write(full_log)
            
            return success, full_log
            
        except subprocess.TimeoutExpired:
            error_msg = f"Build timeout (>600s)"
            log_content.append("\n" + "="*80 + "\n")
            log_content.append(f"Build Result: ❌ FAILED - {error_msg}\n")
            log_content.append("="*80 + "\n")
            Color.print_error(f"{bsp_name}: {error_msg}")
            
            # 恢复配置文件（即使超时也要恢复）
            if backup_files:
                self._restore_config_files(backup_files)
                log_content.append("\n--- Restore Config (on error) ---\n")
                log_content.append("Config files restored after timeout\n")
            
            full_log = ''.join(log_content)
            with open(log_file, 'w', encoding='utf-8') as f:
                f.write(full_log)
            
            return False, full_log
            
        except Exception as e:
            error_msg = f"Build exception: {str(e)}"
            log_content.append("\n" + "="*80 + "\n")
            log_content.append(f"Build Result: ❌ FAILED - {error_msg}\n")
            log_content.append("="*80 + "\n")
            Color.print_error(f"{bsp_name}: {error_msg}")
            
            # 恢复配置文件（即使异常也要恢复）
            if backup_files:
                self._restore_config_files(backup_files)
                log_content.append("\n--- Restore Config (on error) ---\n")
                log_content.append("Config files restored after exception\n")
            
            full_log = ''.join(log_content)
            with open(log_file, 'w', encoding='utf-8') as f:
                f.write(full_log)
            
            return False, full_log
    
    def run(self):
        """运行测试"""
        print("\n" + "="*80)
        print(f"{Color.BOLD}GD32 ARM BSP Local Build Test{Color.END}")
        print("="*80 + "\n")
        
        self.start_time = datetime.datetime.now()
        
        # 检查环境
        if not self._check_env():
            Color.print_error("Environment check failed!")
            Color.print_info("Please fix the environment issues and try again")
            sys.exit(1)
        
        # 过滤 BSP 列表
        test_list = [bsp for bsp in self.test_bsps if bsp not in self.excluded_bsps]
        
        Color.print_info(f"Total BSPs to test: {len(test_list)}")
        Color.print_info(f"Excluded BSPs: {len(self.excluded_bsps)}")
        if test_list:
            Color.print_info(f"Test list:\n  {', '.join(test_list)}\n")
        else:
            Color.print_error("No BSPs to test!")
            sys.exit(1)
        
        # 逐个测试
        for i, bsp_name in enumerate(test_list, 1):
            print(f"\n{'='*80}")
            print(f"[{i}/{len(test_list)}] Testing: {bsp_name}")
            print("="*80)
            
            success, log = self._build_bsp(bsp_name)
            
            if success:
                self.results["success"].append(bsp_name)
            else:
                self.results["failed"].append(bsp_name)
            
            print()
        
        self.end_time = datetime.datetime.now()
        
        # 生成报告
        self._generate_report()
    
    def _generate_report(self):
        """生成测试报告"""
        timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
        # 报告文件保存在日志目录（脚本同级的 build_logs 文件夹）
        report_file = self.log_dir / f"build_test_report_{timestamp}.html"
        json_file = self.log_dir / f"build_test_report_{timestamp}.json"
        
        total = len(self.results["success"]) + len(self.results["failed"])
        success_rate = (len(self.results["success"]) / total * 100) if total > 0 else 0
        duration = (self.end_time - self.start_time).total_seconds()
        
        # JSON 报告
        json_data = {
            "timestamp": datetime.datetime.now().isoformat(),
            "start_time": self.start_time.isoformat(),
            "end_time": self.end_time.isoformat(),
            "duration_seconds": duration,
            "total": total,
            "success": len(self.results["success"]),
            "failed": len(self.results["failed"]),
            "success_rate": success_rate,
            "results": self.results,
            "config": self.config
        }
        
        with open(json_file, 'w', encoding='utf-8') as f:
            json.dump(json_data, f, indent=2, ensure_ascii=False)
        
        # HTML 报告
        html = f"""<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>GD32 ARM BSP Build Test Report</title>
    <style>
        * {{
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }}
        body {{
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            padding: 20px;
            min-height: 100vh;
        }}
        .container {{
            max-width: 1200px;
            margin: 0 auto;
            background: white;
            padding: 40px;
            border-radius: 12px;
            box-shadow: 0 10px 40px rgba(0,0,0,0.2);
        }}
        h1 {{
            color: #333;
            border-bottom: 4px solid #667eea;
            padding-bottom: 15px;
            margin-bottom: 30px;
            font-size: 32px;
        }}
        h2 {{
            color: #555;
            margin-top: 40px;
            margin-bottom: 20px;
            font-size: 24px;
        }}
        .summary {{
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 20px;
            margin: 30px 0;
        }}
        .stat {{
            text-align: center;
            padding: 25px;
            background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);
            border-radius: 10px;
            box-shadow: 0 4px 6px rgba(0,0,0,0.1);
            transition: transform 0.2s;
        }}
        .stat:hover {{
            transform: translateY(-5px);
        }}
        .stat-value {{
            font-size: 48px;
            font-weight: bold;
            margin-bottom: 10px;
        }}
        .stat-label {{
            color: #666;
            font-size: 14px;
            text-transform: uppercase;
            letter-spacing: 1px;
        }}
        .success {{
            color: #4CAF50;
        }}
        .failed {{
            color: #f44336;
        }}
        .duration {{
            color: #2196F3;
        }}
        table {{
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
            box-shadow: 0 2px 8px rgba(0,0,0,0.1);
        }}
        th {{
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 15px;
            text-align: left;
            font-weight: 600;
        }}
        td {{
            padding: 15px;
            border-bottom: 1px solid #e0e0e0;
        }}
        tr:hover {{
            background: #f8f9fa;
        }}
        tr:last-child td {{
            border-bottom: none;
        }}
        .badge {{
            display: inline-block;
            padding: 6px 14px;
            border-radius: 20px;
            font-size: 13px;
            font-weight: 600;
        }}
        .badge-success {{
            background: #4CAF50;
            color: white;
        }}
        .badge-failed {{
            background: #f44336;
            color: white;
        }}
        .footer {{
            margin-top: 50px;
            text-align: center;
            color: #999;
            font-size: 14px;
            padding-top: 30px;
            border-top: 1px solid #e0e0e0;
        }}
        .footer p {{
            margin: 5px 0;
        }}
        a {{
            color: #667eea;
            text-decoration: none;
            transition: color 0.2s;
        }}
        a:hover {{
            color: #764ba2;
            text-decoration: underline;
        }}
        .log-link {{
            color: #2196F3;
        }}
        .index {{
            width: 60px;
            text-align: center;
            font-weight: 600;
            color: #999;
        }}
    </style>
</head>
<body>
    <div class="container">
        <h1>🔨 GD32 ARM BSP Build Test Report</h1>
        
        <div class="summary">
            <div class="stat">
                <div class="stat-value">{total}</div>
                <div class="stat-label">Total BSPs</div>
            </div>
            <div class="stat">
                <div class="stat-value success">{len(self.results["success"])}</div>
                <div class="stat-label">Success</div>
            </div>
            <div class="stat">
                <div class="stat-value failed">{len(self.results["failed"])}</div>
                <div class="stat-label">Failed</div>
            </div>
            <div class="stat">
                <div class="stat-value">{success_rate:.1f}%</div>
                <div class="stat-label">Success Rate</div>
            </div>
            <div class="stat">
                <div class="stat-value duration">{duration:.1f}s</div>
                <div class="stat-label">Duration</div>
            </div>
        </div>
        
        <h2>📊 Detailed Results</h2>
        <table>
            <thead>
                <tr>
                    <th class="index">#</th>
                    <th>BSP Name</th>
                    <th>Status</th>
                    <th>Log File</th>
                </tr>
            </thead>
            <tbody>
"""
        
        # 添加成功的 BSP
        for i, bsp in enumerate(self.results["success"], 1):
            html += f"""
                <tr>
                    <td class="index">{i}</td>
                    <td><strong>{bsp}</strong></td>
                    <td><span class="badge badge-success">✅ Success</span></td>
                    <td><a href="{bsp}.log" class="log-link">View Log</a></td>
                </tr>
"""
        
        # 添加失败的 BSP
        for i, bsp in enumerate(self.results["failed"], len(self.results["success"]) + 1):
            html += f"""
                <tr>
                    <td class="index">{i}</td>
                    <td><strong>{bsp}</strong></td>
                    <td><span class="badge badge-failed">❌ Failed</span></td>
                    <td><a href="{bsp}.log" class="log-link">View Log</a></td>
                </tr>
"""
        
        html += f"""
            </tbody>
        </table>
        
        <div class="footer">
            <p><strong>Test Information</strong></p>
            <p>Start Time: {self.start_time.strftime("%Y-%m-%d %H:%M:%S")}</p>
            <p>End Time: {self.end_time.strftime("%Y-%m-%d %H:%M:%S")}</p>
            <p>Total Duration: {duration:.2f} seconds</p>
            <p style="margin-top: 20px;">RT-Thread GD32 ARM BSP Build Test System v1.0</p>
            <p>Generated by <a href="https://github.com/RT-Thread/rt-thread" target="_blank">RT-Thread</a></p>
        </div>
    </div>
</body>
</html>
"""
        
        with open(report_file, 'w', encoding='utf-8') as f:
            f.write(html)
        
        # 打印总结
        print("\n" + "="*80)
        print(f"{Color.BOLD}Test Summary{Color.END}")
        print("="*80)
        print(f"Total BSPs:     {total}")
        Color.print_success(f"Success:        {len(self.results['success'])} ({success_rate:.1f}%)")
        if self.results["failed"]:
            Color.print_error(f"Failed:         {len(self.results['failed'])}")
        else:
            print(f"Failed:         0")
        print(f"Duration:       {duration:.2f} seconds")
        print(f"\nReports:")
        print(f"  📄 HTML: {report_file}")
        print(f"  📋 JSON: {json_file}")
        print(f"  📁 Logs: {self.log_dir}/")
        print("="*80 + "\n")
        
        if self.results["failed"]:
            Color.print_error(f"Failed BSPs ({len(self.results['failed'])}):")
            for bsp in self.results["failed"]:
                print(f"  ❌ {bsp}")
            print()
            Color.print_warning("Please check the build logs for error details")
            sys.exit(1)
        else:
            Color.print_success("All BSPs built successfully! 🎉")
            sys.exit(0)

def main():
    """主函数"""
    import argparse
    
    parser = argparse.ArgumentParser(
        description='GD32 ARM BSP Local Build Test Tool',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples / 示例:
  # Test all BSPs with default config / 使用默认配置测试所有 BSP
  python gd32_local_build_test.py
  
  # Use unified config file (recommended) / 使用统一配置文件（推荐）
  python gd32_local_build_test.py --config bsp/gd32/scripts/gd32_bsp_config.json
  
  # Clean build all BSPs / 清理编译所有 BSP
  python gd32_local_build_test.py --clean
  
  # Clean build with specific method / 使用特定方法清理编译
  python gd32_local_build_test.py --clean --clean-method both
  
  # Test with custom config / 使用自定义配置
  python gd32_local_build_test.py --config my_config.json --clean
  
  # Test specific BSPs with clean / 清理编译特定 BSP
  python gd32_local_build_test.py --bsps gd32h75ey-eval gd32h759i-eval --clean
  
  # Incremental build (fast, default) / 增量编译（快速，默认）
  python gd32_local_build_test.py --bsps gd32h75ey-eval
  
  # Clean up ALL build artifacts (before commit) / 清理所有编译产物（提交前）
  python gd32_local_build_test.py --cleanup-all
  
  # Clean up specific BSPs / 清理特定 BSP
  python gd32_local_build_test.py --cleanup-all --bsps gd32h75ey-eval gd32h759i-eval
  
  # Clean up with verbose output / 详细输出清理过程
  python gd32_local_build_test.py --cleanup-all --verbose
  
  # Test with verbose output / 详细输出
  python gd32_local_build_test.py --verbose
"""
    )
    
    parser.add_argument('--config', '-c',
                       help='Path to config JSON file / 配置文件路径',
                       default=None)
    
    parser.add_argument('--bsps', '-b',
                       nargs='+',
                       help='Specific BSPs to test / 要测试的特定 BSP',
                       default=None)
    
    parser.add_argument('--clean',
                       action='store_true',
                       help='Perform clean build (scons -c before build) / 执行清理编译')
    
    parser.add_argument('--clean-method',
                       choices=['scons', 'rmdir', 'both'],
                       default=None,
                       help='Clean method: scons (scons -c), rmdir (delete build/), both / 清理方法')
    
    parser.add_argument('--cleanup-all',
                       action='store_true',
                       help='Clean up all build artifacts (for pre-commit cleanup) / 清理所有编译产物（提交前清理）')
    
    parser.add_argument('--verbose', '-v',
                       action='store_true',
                       help='Verbose output / 详细输出')
    
    args = parser.parse_args()
    
    try:
        # 创建测试器
        tester = GD32BuildTester(
            config_file=args.config,
            clean_build=args.clean
        )
        
        # 如果指定了清理方法，覆盖配置
        if args.clean_method:
            tester.clean_method = args.clean_method
        
        # 如果指定了特定 BSP，覆盖配置
        if args.bsps:
            tester.test_bsps = args.bsps
            Color.print_info(f"Testing specific BSPs: {', '.join(args.bsps)}")
        
        # 处理 cleanup-all 命令
        if args.cleanup_all:
            tester.cleanup_all_bsps(bsp_list=args.bsps, verbose=args.verbose)
            sys.exit(0)
        
        # 显示配置信息
        if tester.clean_build:
            Color.print_warning(f"🧹 Clean build mode enabled - Method: {tester.clean_method}")
            Color.print_info(f"   All BSPs will be cleaned before build")
        else:
            Color.print_info("⚡ Incremental build mode - using cached objects")
        
        # 运行测试
        tester.run()
        
    except KeyboardInterrupt:
        print("\n")
        Color.print_warning("Test interrupted by user")
        sys.exit(130)
    except Exception as e:
        Color.print_error(f"Unexpected error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

if __name__ == '__main__':
    main()
