# Windows + MSYS2 UCRT64 + VS Code：C 语言学习环境配置

> 适用对象：已经有 Python 基础，现在开始学习 C 语言。  
> 目标：在 Windows 上使用 **MSYS2 UCRT64 + GCC + GDB + VS Code**，完成 C 程序的编写、编译、运行、断点调试和 IntelliSense。
>
> 本教程以 **C17** 为主，不混用 Cygwin、MSYS、旧版 MinGW 等工具链。

---

## 0. 推荐的最终环境

本教程最终使用：

- 编辑器：VS Code
- C 编译器：GCC
- C 标准：C17
- 调试器：GDB
- 工具链：MSYS2 UCRT64
- 项目目录示例：`D:\c-learn`

核心目录：

```text
C:\msys64\ucrt64\bin
```

其中应包含：

```text
gcc.exe
gdb.exe
g++.exe
make.exe
```

### 为什么选择 UCRT64？

你原来的配置文档选择 UCRT64 是合理的。UCRT64 是目前 Windows + MSYS2 环境中很适合初学者的 GCC 工具链之一。

本教程学习 C 时只使用：

```text
UCRT64
```

不要在同一个项目里混用：

```text
MSYS
MINGW32
Cygwin
其他 MinGW
Visual Studio 的 cl.exe
```

这样可以减少编译器和运行库冲突。

---

# 1. 安装 MSYS2

进入 MSYS2 官网：

https://www.msys2.org/

安装时建议：

```text
C:\msys64
```

尽量不要安装到：

```text
C:\Program Files\...
```

也尽量避免中文路径。

安装完成后，从开始菜单打开：

```text
MSYS2 UCRT64
```

注意：后续安装 GCC、GDB 等工具时，优先在 **MSYS2 UCRT64** 终端中操作。

---

# 2. 更新 MSYS2

第一次打开 UCRT64 后：

```bash
pacman -Syu
```

如果系统提示关闭终端，请按照提示关闭。

然后重新打开：

```text
MSYS2 UCRT64
```

再次执行：

```bash
pacman -Syu
```

直到系统更新完成。

---

# 3. 安装 C 工具链

执行：

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

出现：

```text
Proceed? [Y/n]
```

输入：

```text
Y
```

然后等待安装完成。

这个工具链会提供 GCC、GDB 等我们后面学习 C 所需要的工具。

---

# 4. 验证 GCC 和 GDB

在 **MSYS2 UCRT64** 终端执行：

```bash
gcc --version
```

然后：

```bash
gdb --version
```

再执行：

```bash
which gcc
```

正常情况下应该看到类似：

```text
/ucrt64/bin/gcc
```

再执行：

```bash
which gdb
```

应该看到：

```text
/ucrt64/bin/gdb
```

Windows 对应目录是：

```text
C:\msys64\ucrt64\bin
```

---

# 5. 配置 Windows PATH

为了让 VS Code、PowerShell 等能够直接找到 GCC，可以将：

```text
C:\msys64\ucrt64\bin
```

加入 Windows 的用户 PATH。

操作：

```text
Windows 搜索
→ 环境变量
→ 编辑账户的环境变量
→ Path
→ 新建
→ C:\msys64\ucrt64\bin
```

保存后：

**完全关闭 VS Code 和已经打开的 PowerShell/CMD，再重新打开。**

然后在 PowerShell 执行：

```powershell
gcc --version
```

```powershell
gdb --version
```

```powershell
where.exe gcc
```

正常情况下 `where.exe gcc` 应该指向：

```text
C:\msys64\ucrt64\bin\gcc.exe
```

如果出现其他 GCC，例如：

```text
C:\mingw64\bin\gcc.exe
```

说明你的电脑可能存在多个 GCC，需要处理 PATH 冲突。

---

# 6. 一个重要原则：不要把 MSYS 放进 PATH

不要添加：

```text
C:\msys64\usr\bin
```

也不要把：

```text
C:\msys64\usr\bin
C:\msys64\mingw64\bin
C:\msys64\mingw32\bin
```

和 UCRT64 混在一起使用。

我们学习 C 时统一使用：

```text
C:\msys64\ucrt64\bin
```

---

# 7. 安装 VS Code

安装：

https://code.visualstudio.com/

推荐安装扩展：

## 必装

### C/C++

Microsoft 官方扩展：

```text
C/C++
```

它负责：

- IntelliSense
- 语法检查
- 自动补全
- 跳转定义
- GDB 调试

## 可选

```text
C/C++ Extension Pack
```

初学阶段不是必须。

### Code Runner

可以安装：

```text
Code Runner
```

但不建议把它作为主要的学习方式。

学习 C 的过程中，我们需要理解：

```text
源代码
↓
编译
↓
可执行文件
↓
运行
↓
调试
```

因此推荐使用 VS Code 的：

```text
tasks.json
+
launch.json
```

而不是完全依赖 Code Runner。

---

# 8. 创建第一个 C 项目

例如创建：

```text
D:\c-learn
```

目录结构：

```text
D:\c-learn
│
├── .vscode
│   ├── c_cpp_properties.json
│   ├── tasks.json
│   └── launch.json
│
└── hello.c
```

VS Code：

```text
File
→ Open Folder
→ D:\c-learn
```

---

# 9. 配置 IntelliSense

创建：

```text
D:\c-learn\.vscode\c_cpp_properties.json
```

内容：

```json
{
    "configurations": [
        {
            "name": "UCRT64",
            "compilerPath": "C:/msys64/ucrt64/bin/gcc.exe",
            "intelliSenseMode": "windows-gcc-x64",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "cStandard": "c17",
            "defines": []
        }
    ],
    "version": 4
}
```

这里有一个重要改进：

**学习 C 时直接使用 `gcc.exe`，而不是 `g++.exe`。**

你原来的文档虽然同时给出了 C 和 C++ 配置，但 C 学习阶段没有必要先把两套配置混在一起。

---

# 10. 配置 C 编译任务

创建：

```text
D:\c-learn\.vscode\tasks.json
```

使用：

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build C",
            "type": "shell",
            "command": "C:/msys64/ucrt64/bin/gcc.exe",
            "args": [
                "-std=c17",
                "-Wall",
                "-Wextra",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}.exe"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": [
                "$gcc"
            ]
        }
    ]
}
```

这里我建议使用 GCC 的**绝对路径**：

```text
C:/msys64/ucrt64/bin/gcc.exe
```

这样即使电脑中以后安装了其他 GCC，也不容易出现 VS Code 调用了错误编译器的问题。

---

# 11. 为什么这些参数很重要？

我们的编译命令实际上相当于：

```bash
gcc -std=c17 -Wall -Wextra -g hello.c -o hello.exe
```

逐个理解：

### `-std=c17`

使用 C17 标准。

你目前学习 C，不需要一开始纠结各种 C 标准。

先统一：

```text
C17
```

即可。

---

### `-Wall`

打开常见警告。

例如：

```c
int x;

printf("%d", y);
```

如果存在明显问题，编译器会提醒你。

---

### `-Wextra`

进一步打开额外警告。

学习阶段非常有价值。

你应该逐渐形成一个习惯：

> **看到 warning 不要无视，要理解 warning 为什么出现。**

---

### `-g`

生成调试信息。

没有：

```text
-g
```

GDB 的断点、变量查看、单步调试会受到影响。

---

# 12. 配置 GDB 调试

创建：

```text
D:\c-learn\.vscode\launch.json
```

内容：

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug C",
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
            "preLaunchTask": "Build C"
        }
    ]
}
```

这里的：

```json
"preLaunchTask": "Build C"
```

必须和 `tasks.json` 中的：

```json
"label": "Build C"
```

完全一致。

---

# 13. 写第一个 C 程序

创建：

```text
hello.c
```

输入：

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, C!\n");

    return 0;
}
```

---

# 14. 编译

打开：

```text
hello.c
```

按：

```text
Ctrl + Shift + B
```

VS Code 会执行：

```bash
gcc -std=c17 -Wall -Wextra -g hello.c -o hello.exe
```

如果没有错误，目录中会出现：

```text
hello.exe
```

---

# 15. 运行

在 VS Code 终端：

```powershell
.\hello.exe
```

应该看到：

```text
Hello, C!
```

---

# 16. 调试

在：

```c
printf("Hello, C!\n");
```

这一行左侧点击一下，设置断点。

然后按：

```text
F5
```

VS Code 会：

```text
编译
↓
启动 GDB
↓
运行程序
↓
停在断点
```

之后可以学习：

```text
Step Over
Step Into
Step Out
Continue
```

以及观察：

```text
Variables
Watch
Call Stack
```

这些内容会在学习函数、指针、数组、结构体时非常重要。

---

# 17. 推荐的 C 学习工作流

以后写 C 程序时，建议固定使用：

```text
写代码
↓
Ctrl + Shift + B
↓
看编译器 warning/error
↓
修改代码
↓
重新编译
↓
运行
↓
需要时 F5 调试
```

不要形成：

```text
代码有问题
↓
疯狂点击运行
↓
不知道错误在哪里
```

C 的编译器和 GDB 本身就是学习工具。

---

# 18. 如何检查环境是否真正配置成功

依次检查：

### ① GCC

```powershell
gcc --version
```

### ② GDB

```powershell
gdb --version
```

### ③ GCC 路径

```powershell
where.exe gcc
```

应该包含：

```text
C:\msys64\ucrt64\bin\gcc.exe
```

### ④ VS Code IntelliSense

打开：

```c
#include <stdio.h>
```

如果 `stdio.h` 能正常识别，并且：

```c
printf
```

有自动补全/提示，说明 IntelliSense 基本正常。

### ⑤ 编译

```text
Ctrl + Shift + B
```

能够生成：

```text
hello.exe
```

### ⑥ 运行

```powershell
.\hello.exe
```

能够输出：

```text
Hello, C!
```

### ⑦ 调试

```text
F5
```

能够进入断点。

满足这 7 项，就可以正式开始学习 C。

---

# 19. 常见问题

## 问题 1：gcc 不是内部或外部命令

检查：

```powershell
where.exe gcc
```

如果找不到：

```text
C:\msys64\ucrt64\bin\gcc.exe
```

检查 PATH。

修改 PATH 后必须重新打开 VS Code/终端。

---

## 问题 2：VS Code 有红色波浪线，但程序可以编译

检查：

```text
.vscode/c_cpp_properties.json
```

确认：

```json
"compilerPath": "C:/msys64/ucrt64/bin/gcc.exe"
```

以及：

```json
"intelliSenseMode": "windows-gcc-x64"
```

---

## 问题 3：F5 无法调试

检查：

```json
"miDebuggerPath": "C:/msys64/ucrt64/bin/gdb.exe"
```

以及：

```json
"preLaunchTask": "Build C"
```

是否和：

```text
tasks.json
```

里的：

```json
"label": "Build C"
```

一致。

同时确认编译参数里有：

```text
-g
```

---

## 问题 4：电脑里有多个 gcc

执行：

```powershell
where.exe gcc
```

如果出现多个结果，例如：

```text
C:\xxx\gcc.exe
C:\msys64\ucrt64\bin\gcc.exe
```

可能产生工具链冲突。

本教程的 VS Code 配置已经使用：

```text
C:/msys64/ucrt64/bin/gcc.exe
```

因此 VS Code 项目本身不会依赖 PATH 中哪个 GCC 排在前面。

---

# 20. 目前不要急着安装太多东西

学习基础 C 时，你暂时不需要：

```text
CMake
Ninja
vcpkg
Conan
复杂的 C/C++ 项目模板
```

它们以后做大型项目时再学习。

现在最重要的是：

```text
C 语法
↓
变量
↓
数据类型
↓
输入输出
↓
条件
↓
循环
↓
函数
↓
数组
↓
字符串
↓
指针
↓
结构体
↓
动态内存
↓
文件
↓
多文件项目
↓
Make/CMake
```

---

# 21. 针对 Python 学习者的学习路线

因为你已经有 Python 基础，所以不要把 C 当成完全陌生的编程语言。

可以采用：

```text
Python 概念
        ↓
C 中对应概念
        ↓
理解两者底层差异
```

例如：

| Python | C |
|---|---|
| `x = 10` | `int x = 10;` |
| `print(x)` | `printf("%d", x);` |
| `if` | `if` |
| `for` | `for` |
| `while` | `while` |
| `def` | 函数 |
| `list` | 数组 / 动态数据结构 |
| `str` | `char[]` / `char *` |
| 对象引用 | 指针 |
| 垃圾回收 | 手动内存管理 |
| 异常机制 | C 没有 Python 式异常机制 |

真正需要重点理解的是：

```text
变量在内存中的位置
        ↓
地址
        ↓
指针
        ↓
数组
        ↓
函数参数
        ↓
动态内存
```

这是 Python 学习者进入 C 时最值得投入时间的部分。

---

# 22. 第一个学习目标

完成环境配置后，不建议马上学指针。

先完成：

## 第一阶段：C 基础

```text
1. C 程序结构
2. main 函数
3. printf
4. scanf
5. 变量
6. 数据类型
7. 运算符
8. if / else
9. for
10. while
11. 函数
```

然后进入：

## 第二阶段：C 的核心

```text
12. 数组
13. 字符串
14. 指针
15. 指针与数组
16. 指针与函数
17. 结构体
18. 动态内存
```

最后：

## 第三阶段：真正开始“像 C 程序员一样”写程序

```text
19. 文件操作
20. 多文件编程
21. .h / .c
22. Makefile
23. CMake
24. GDB
25. 数据结构
```

---

# 23. 一个非常重要的学习原则

不要只记：

```c
printf("%d", x);
```

而要逐渐问自己：

> `x` 在内存哪里？

> `x` 占多少字节？

> `printf` 为什么需要 `%d`？

> 如果 `x` 是 `double` 呢？

> 如果我想获得 `x` 的地址怎么办？

> 如果函数修改 `x`，为什么有时候需要传 `&x`？

当你开始问这些问题时，才真正进入 C 的核心。

---

# 24. 配置完成后的第一课

环境确认无误后，从下面这个程序开始：

```c
#include <stdio.h>

int main(void)
{
    int age = 20;

    printf("My age is %d.\n", age);

    return 0;
}
```

然后我们再逐步学习：

```text
int
↓
变量
↓
printf
↓
%d
↓
内存
↓
地址
↓
指针
```

这样可以充分利用你已有的 Python 基础，同时把 C 最重要的“内存模型”真正建立起来。
