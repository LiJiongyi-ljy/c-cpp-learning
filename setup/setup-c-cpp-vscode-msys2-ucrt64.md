# Windows 用 MSYS2 UCRT64 + MinGW-w64 + VSCode 配置 C/C++ 教程

适用：有 Python 基础、用 VSCode 学 C/C++。目标是在 VSCode 里写 `.c`/`.cpp`，能智能提示、编译、运行、断点调试。

> 推荐 UCRT64 而不是老 MSVCRT、也不推荐把 Cygwin/MSYS 环境混用。UCRT 更现代，Win10/11 体验更好。

---

## 1. 安装 MSYS2

1. 打开官网 https://www.msys2.org 下载 `msys2-x86_64-*.exe`（要求 64 位 Windows 10 1809+ 或更高）。
2. 安装时建议用默认路径 `C:\msys64`，全程英文、无空格、无中文。
3. 安装完成勾选"运行 MSYS2"，或开始菜单搜 **MSYS2 UCRT64** 打开终端。
   - 注意：后面所有 `pacman` 命令都在 **UCRT64** 终端里执行，不要在"MSYS2 MSYS"里装 MinGW 工具链。

---

## 2. 安装 UCRT64 MinGW-w64 工具链

在 UCRT64 终端执行：

```bash
# 首次可先更新包数据库与系统（如提示关闭终端，重开 UCRT64 再跑一次）
pacman -Syu

# 安装完整 C/C++ 工具链（含 gcc、g++、gdb、make 等）
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

- 提示选择包数量时直接回车用默认全装；
- 提示 `Proceed?` 输入 `Y` 回车。
- 可选再装构建工具：

```bash
pacman -S --needed make cmake ninja
```

装完在 UCRT64 终端验证：

```bash
gcc --version
g++ --version
gdb --version
```

UCRT64 的二进制目录默认是：

```
C:\msys64\ucrt64\bin
```

里面应有 `gcc.exe`、`g++.exe`、`gdb.exe`、`make.exe` 等。

---

## 3. 把 UCRT64 加到 Windows PATH

目的：在 CMD / PowerShell / VSCode 终端里直接调用 `gcc`、`g++`、`gdb`。

1. Win 搜索"环境变量" → "编辑账户的环境变量"或"系统属性 → 环境变量"。
2. 在"用户变量"或"系统变量"里找到 `Path` → 编辑 → 新建，添加：
   ```
   C:\msys64\ucrt64\bin
   ```
   如果你装到其他盘，改成实际路径，例如 `D:\msys64\ucrt64\bin`。
3. 确定保存，**关闭所有已开终端/VSCode**，重新打开。
4. 新开 PowerShell/CMD 验证：

```powershell
gcc --version
g++ --version
gdb --version
where gcc
```

能输出版本、`where gcc` 指向 `ucrt64\bin\gcc.exe` 即成功。

> 坑：不要把 `C:\msys64\usr\bin` 或 `C:\msys64\msys64\...` 加进全局 PATH，会和 UCRT64 的 MinGW 工具混用导致奇怪错误。

---

## 4. 安装 VSCode 与扩展

1. 安装 VSCode：https://code.visualstudio.com
2. 扩展市场装：
   - `C/C++`（Microsoft，必装，提供 IntelliSense/调试）
   - `C/C++ Extension Pack`（可选，含常用辅助）
   - `Code Runner`（可选，单文件一键运行；但调试建议用下面 tasks+launch）
3. 打开一个空项目文件夹，例如 `D:\cpp-learn`，路径尽量英文无空格。

---

## 5. 配置编译器路径（c_cpp_properties.json）

项目根目录新建 `.vscode/c_cpp_properties.json`：

C++ 为主：

```json
{
  "configurations": [
    {
      "name": "UCRT64",
      "compilerPath": "C:/msys64/ucrt64/bin/g++.exe",
      "intelliSenseMode": "windows-gcc-x64",
      "includePath": ["${workspaceFolder}/**"],
      "cStandard": "c17",
      "cppStandard": "c++20",
      "defines": []
    }
  ],
  "version": 4
}
```

如果主要写 C，把 `compilerPath` 改成：

```json
"compilerPath": "C:/msys64/ucrt64/bin/gcc.exe"
```

也可通过 UI 配：VSCode 按 `Ctrl+Shift+P` → `C/C++: Edit Configurations (UI)` → Compiler path 填 `C:/msys64/ucrt64/bin/g++.exe`，IntelliSense mode 选 `windows-gcc-x64`。

> 路径用正斜杠 `/` 最稳；若用反斜杠在 JSON 里要写成 `C:\\msys64\\ucrt64\\bin\\g++.exe`。

---

## 6. 配置编译任务（tasks.json）

单文件编译用。项目根目录 `.vscode/tasks.json`。

C++ 任务：

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build cpp",
      "type": "shell",
      "command": "g++",
      "args": [
        "-fdiagnostics-color=always",
        "-g",
        "-Wall",
        "-std=c++20",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}.exe"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

C 任务（把 label/command 换成 gcc、标准改 c17）：

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build c",
      "type": "shell",
      "command": "gcc",
      "args": [
        "-fdiagnostics-color=always",
        "-g",
        "-Wall",
        "-std=c17",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}.exe"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

使用：打开某个 `.c`/`.cpp` 文件，`Ctrl+Shift+B` 编译，生成同目录 `xxx.exe`。

---

## 7. 配置调试（launch.json）

项目根目录 `.vscode/launch.json`，用 GDB 调 UCRT64 程序：

C++ 调试：

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Debug C++ (UCRT64 GDB)",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}/${fileBasenameNoExtension}.exe",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "environment": [],
      "externalConsole": true,
      "MIMode": "gdb",
      "miDebuggerPath": "C:/msys64/ucrt64/bin/gdb.exe",
      "setupCommands": [
        {
          "description": "Enable pretty-printing",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "build cpp"
    }
  ]
}
```

C 调试把 `preLaunchTask` 改成 `build c`，`miDebuggerPath` 不变。

使用：打开源文件 → 行号左侧打断点 → `F5` 启动，VSCode 会先跑 tasks 再进 GDB。

---

## 8. Hello World 验证

`D:\cpp-learn\hello.cpp`：

```cpp
#include <iostream>

int main() {
    std::cout << "Hello from MSYS2 UCRT64 + VSCode\n";
    return 0;
}
```

`hello.c`：

```c
#include <stdio.h>

int main(void) {
    printf("Hello C from MSYS2 UCRT64 + VSCode\n");
    return 0;
}
```

验证流程：

1. 打开项目文件夹 `D:\cpp-learn`；
2. `Ctrl+Shift+B` 编译对应任务；
3. VSCode 终端运行：

   ```powershell
   .\hello.exe
   ```
4. 或者 `F5` 直接调试；
5. 改代码后重新 `Ctrl+Shift+B`，再运行/调试。

---

## 9. 常见问题

- `gcc 不是内部或外部命令`：PATH 没加对/没重开终端；确认 `where gcc` 指向 `ucrt64\bin`。
- VSCode 智能提示报错但能编译：c_cpp_properties 的 compilerPath 没指向 ucrt64 的 gcc/g++，或 intelliSenseMode 不是 `windows-gcc-x64`。
- 调试没符号/不能单步：编译任务必须带 `-g`；launch 的 program 路径要与 tasks 输出 exe 路径一致。
- 中文路径乱码/调试异常：项目目录尽量全英文、无空格。
- 多个编译器冲突：如果还装了其他 MinGW、Cygwin、Visual Studio，PATH 里把 `C:\msys64\ucrt64\bin` 置顶，或在 tasks/launch 里写绝对路径。
- 只学单文件不想配 json：装 Code Runner，但正式学指针/调试还是建议 tasks+launch。
