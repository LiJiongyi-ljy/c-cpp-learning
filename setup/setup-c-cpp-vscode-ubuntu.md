# Ubuntu 用 GCC/GDB + VSCode 配置 C/C++ 教程

适用：从 Windows（MSYS2 UCRT64）转到 Ubuntu、用 VSCode 学 C/C++。目标同样是：写 `.c`/`.cpp` → 智能提示 → 编译 → 运行 → 断点调试。

> **和 Windows 最大的区别**：Ubuntu 自带 GNU 工具链，**不需要 MSYS2、不需要 MinGW、不需要配 PATH**。
> `gcc/g++/gdb` 装完就在 `/usr/bin` 里，而 `/usr/bin` 本来就在 PATH 中，所以 Windows 文档里的第 1～3 步（装 MSYS2、装 toolchain、改环境变量）在 Ubuntu 上全部省略。

---

## 0. 先确认你的 Ubuntu 环境

```bash
# 看系统版本（20.04 / 22.04 / 24.04 都可以）
lsb_release -a

# 看架构（x86_64 或 aarch64）
uname -m

# 确认是不是 WSL（有 microsoft 字样就是 WSL）
uname -r
```

---

## 1. 安装 VSCode（推荐官方 .deb）

### 方式 A：官方 .deb 包（推荐，会自动配好微软更新源）

```bash
cd ~/Downloads
wget -O code.deb https://go.microsoft.com/fwlink/?LinkID=760868
sudo apt install ./code.deb
```

装完后终端输入 `code` 就能启动。

### 方式 B：手动添加微软 APT 源（适合脚本/无图形界面）

```bash
sudo apt update && sudo apt install -y wget gpg
wget -qO- https://packages.microsoft.com/keys/microsoft.asc \
  | sudo gpg --dearmor -o /usr/share/keyrings/microsoft.gpg

sudo tee /etc/apt/sources.list.d/vscode.sources > /dev/null <<'EOF'
Types: deb
URIs: https://packages.microsoft.com/repos/code
Suites: stable
Components: main
Architectures: amd64,arm64,armhf
Signed-By: /usr/share/keyrings/microsoft.gpg
EOF

sudo apt update && sudo apt install -y code
```

> ⚠️ 不建议用 `sudo snap install code --classic`。snap 版被 AppArmor 沙箱限制，GDB 调试经常起不来（这是 Ubuntu 上最常见的"调试没反应"原因）。如果你已经装了 snap 版，先 `sudo snap remove code` 再按方式 A 重装。

---

## 2. 安装工具链（GCC / G++ / GDB / make / cmake）

```bash
sudo apt update
sudo apt install -y build-essential gdb cmake git

# 可选：C/C++ 的 man 手册与标准库文档（查函数用法很有用）
sudo apt install -y manpages-dev glibc-doc
```

`build-essential` 一个包就包含了 gcc、g++、make、libc 开发头文件，不用像 MSYS2 那样一个个装。

验证（**注意 Ubuntu 上没有 `.exe` 后缀**）：

```bash
gcc --version
g++ --version
gdb --version
make --version
cmake --version

# 看一下它们在哪（应该是 /usr/bin/...）
which gcc g++ gdb
```

能输出版本、`which gcc` 指向 `/usr/bin/gcc` 即成功。

---

## 3. 安装 VSCode 扩展

图形界面：扩展面板（Ctrl+Shift+X）搜索安装；或者直接在终端装：

```bash
code --install-extension ms-vscode.cpptools                  # C/C++（必装：IntelliSense + 调试）
code --install-extension ms-vscode.cpptools-extension-pack   # C/C++ Extension Pack（可选）
code --install-extension ms-vscode.cmake-tools               # CMake Tools（可选，多文件项目用）
```

| 扩展 | 作用 | 建议 |
|---|---|---|
| C/C++（Microsoft） | 智能提示、跳转、断点调试 | 必装 |
| C/C++ Extension Pack | 合集（含 CMake Tools、Themes） | 可选 |
| CMake Tools | 多文件/CMake 项目一键构建调试 | 学到多文件时再装 |
| Code Runner | 单文件一键运行 | 可选，调试仍建议 tasks + launch |

建一个练习目录，路径用英文无空格（习惯保持，Ubuntu 上中文路径其实也能跑）：

```bash
mkdir -p ~/cpp-learn && cd ~/cpp-learn && code .
```

---

## 4. 配置编译器路径（c_cpp_properties.json）

在 `~/cpp-learn/.vscode/c_cpp_properties.json`：

```json
{
  "configurations": [
    {
      "name": "Linux GCC",
      "compilerPath": "/usr/bin/g++",
      "compilerPathInCppMode": "/usr/bin/g++",
      "intelliSenseMode": "linux-gcc-x64",
      "includePath": ["${workspaceFolder}/**"],
      "cStandard": "c17",
      "cppStandard": "c++20",
      "defines": []
    }
  ],
  "version": 4
}
```

对照 Windows 文档的变化：

| 项 | Windows (UCRT64) | Ubuntu |
|---|---|---|
| compilerPath | `C:/msys64/ucrt64/bin/g++.exe` | `/usr/bin/g++`（C 用 `/usr/bin/gcc`） |
| intelliSenseMode | `windows-gcc-x64` | **`linux-gcc-x64`** |
| 路径分隔符 | 正斜杠 `/` 或双反斜杠 | 直接 `/` |

也可 UI 配：`Ctrl+Shift+P` → `C/C++: Edit Configurations (UI)` → Compiler path 填 `/usr/bin/g++`，IntelliSense mode 选 `linux-gcc-x64`。

> 如果是 ARM 机器（uname -m 显示 aarch64），`intelliSenseMode` 写 `linux-gcc-arm64`。

---

## 5. 配置编译任务（tasks.json）

`.vscode/tasks.json`。这里把 C 和 C++ 两个任务写在一起，`Ctrl+Shift+B` 时选一个即可：

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
        "-Wextra",
        "-std=c++20",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}"
      ],
      "options": {
        "cwd": "${fileDirname}"
      },
      "group": { "kind": "build", "isDefault": true },
      "problemMatcher": ["$gcc"],
      "detail": "用 g++ 编译当前文件（C++20）"
    },
    {
      "label": "build c",
      "type": "shell",
      "command": "gcc",
      "args": [
        "-fdiagnostics-color=always",
        "-g",
        "-Wall",
        "-Wextra",
        "-std=c17",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}"
      ],
      "options": {
        "cwd": "${fileDirname}"
      },
      "group": "build",
      "problemMatcher": ["$gcc"],
      "detail": "用 gcc 编译当前文件（C17）"
    }
  ]
}
```

和 Windows 版的区别只有一处：**输出文件名是 `${fileBasenameNoExtension}`，不要加 `.exe`**（Linux 可执行文件没后缀）。

用法：打开 `.c` / `.cpp` → `Ctrl+Shift+B` → 选 `build cpp` 或 `build c` → 同目录生成无后缀的可执行文件。

> 小提示：如果嫌每次选麻烦，可以 `Ctrl+Shift+P` → `Tasks: Run Build Task`；或者把常用的那个设成 `isDefault`（上面已把 C++ 设为默认）。

---

## 6. 配置调试（launch.json）

`.vscode/launch.json`：

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Debug C++ (Linux GDB)",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}/${fileBasenameNoExtension}",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "/usr/bin/gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "build cpp"
    },
    {
      "name": "Debug C (Linux GDB)",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}/${fileBasenameNoExtension}",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "/usr/bin/gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "build c"
    }
  ]
}
```

对照 Windows 文档的变化：

| 项 | Windows | Ubuntu |
|---|---|---|
| program | `.../xxx.exe` | `.../xxx`（无后缀） |
| externalConsole | `true`（弹独立 cmd 窗口） | **`false`**（用 VSCode 集成终端，可交互输入） |
| miDebuggerPath | `C:/msys64/ucrt64/bin/gdb.exe` | `/usr/bin/gdb` |

用法：打开源文件 → 行号左侧点红点打断点 → 按 `F5` → 顶部选择 `Debug C++ (Linux GDB)` 或 `Debug C (Linux GDB)` → 自动先编译再进 GDB。

调试时常用：`F5` 继续、`F10` 单步跳过、`F11` 单步进入、`Shift+F11` 跳出、`Ctrl+Shift+F5` 重启。左侧面板可看变量、监视、调用栈。

---

## 7. Hello World 验证

`~/cpp-learn/hello.cpp`：

```cpp
#include <iostream>

int main() {
    std::cout << "Hello from Ubuntu GCC + VSCode\n";
    return 0;
}
```

`hello.c`：

```c
#include <stdio.h>

int main(void) {
    printf("Hello C from Ubuntu GCC + VSCode\n");
    return 0;
}
```

验证流程：

1. `cd ~/cpp-learn && code .` 打开项目；
2. 打开 `hello.cpp` → `Ctrl+Shift+B` → 选 `build cpp`；
3. VSCode 集成终端（`Ctrl+\``）运行：

   ```bash
   ./hello
   ```
4. 或直接 `F5` 调试，在 `return 0;` 上打断点看是否停住；
5. 改代码后重新 `Ctrl+Shift+B` 再运行/调试。

> 如果提示 `Permission denied`，是因为生成的文件没执行权限：`chmod +x ./hello`（正常编译出来的一般有 755 权限，很少遇到）。

---

## 8. 常见问题（Ubuntu 版）

- **`gcc: command not found`** → `build-essential` 没装成功，重跑 `sudo apt install -y build-essential`；确认 `which gcc` 是 `/usr/bin/gcc`。
- **`F5` 后 GDB 无反应 / 直接退出 / 报 sandbox 错误** → 你装的是 **snap 版 VSCode**。卸载换官方 `.deb`：`sudo snap remove code` 然后按第 1 节重装。
- **能编译但 IntelliSense 划红线** → `c_cpp_properties.json` 的 `compilerPath` 没指向 `/usr/bin/g++`，或 `intelliSenseMode` 写成了 `windows-gcc-x64`（应为 `linux-gcc-x64`）。
- **调试没符号 / 不能单步** → tasks.json 必须带 `-g`；launch 的 `program` 要和 tasks 输出路径一致（**都没有 `.exe`**）。
- **`ptrace: Operation not permitted`** → Ubuntu 的 Yama 安全模块限制。一般不触发（GDB 调试自己启动的进程没问题）；真遇到就临时放开：
  ```bash
  echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
  ```
- **程序一闪而过 / 无法输入 stdin** → 确认 `externalConsole: false`（用集成终端）。想用外部终端可改成 `true` 并确保装了 `x-terminal-emulator`。
- **`#include <bits/stdc++.h>` 报错** → Ubuntu 的 GCC 自带这个头文件，若报错说明用了 clang 或编译器路径错了，检查 `compilerPath`。
- **WSL 场景** → 在 Windows 的 VSCode 里装 `WSL` 扩展，然后用 `code .` 从 WSL 终端里打开；**项目文件放在 `~/` 下，不要放 `/mnt/c/`**（跨文件系统调试/文件监听容易出问题）。
- **多个 GCC 版本共存**（比如装了 gcc-13）→ 在 tasks.json 里把 `command` 写成 `/usr/bin/g++-13`，或在终端用 `sudo update-alternatives --config g++` 切换默认版本。
- **中文乱码** → Ubuntu 默认 UTF-8，一般没问题。若终端显示乱码，检查 `locale`，确保 `LANG=zh_CN.UTF-8` 或 `en_US.UTF-8`。

---

## 9. 进阶：多文件项目用 CMake（可选）

单文件练熟后，多文件就别手写 tasks.json 了，用 CMake：

```bash
sudo apt install -y cmake        # 第 2 步已装
code --install-extension ms-vscode.cmake-tools
```

`CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.16)
project(hello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)   # 想要能调试就必须是 Debug（等价于加 -g）

add_executable(hello main.cpp foo.cpp)
```

然后：底部状态栏选编译器（GCC）→ 点 Build → 点调试按钮。或者命令行：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/hello
```

---

## 10. Windows 文档 → Ubuntu 对照速查

| Windows 步骤 | Ubuntu 对应 |
|---|---|
| 1. 装 MSYS2 | ❌ 不需要 |
| 2. `pacman -S mingw-w64-ucrt-x86_64-toolchain` | ✅ `sudo apt install -y build-essential gdb` |
| 3. 把 ucrt64/bin 加进 PATH | ❌ 不需要（`/usr/bin` 已在 PATH） |
| 4. 装 VSCode + C/C++ 扩展 | ✅ 一样（建议官方 `.deb`，别用 snap） |
| 5. c_cpp_properties.json | ✅ compilerPath `/usr/bin/g++`，mode `linux-gcc-x64` |
| 6. tasks.json | ✅ 输出文件名去掉 `.exe` |
| 7. launch.json | ✅ program 去掉 `.exe`，`externalConsole: false`，gdb 路径 `/usr/bin/gdb` |
| 8. Hello World | ✅ 运行 `./hello` 而不是 `.\hello.exe` |
| 9. 常见坑 | ✅ 最大坑：snap 版 VSCode 调试失败；其次 `.exe` 后缀、Windows 版 IntelliSense mode |
