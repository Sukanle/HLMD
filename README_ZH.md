![Liencese](https://img.shields.io/badge/Liencese-Apache_2.0-blue)     ![Language](https://img.shields.io/badge/Language-C/C++-red)

# HLMD：高级宏定义库
* 这是一个 **`head-only`** 库。你只需要将 `HLMD.h` 添加到你的构建系统的头文件目录即可。

## 依赖
> [!NOTE]
> **HLMD** 最低支持 `std=c99` 或 `std=c++11` 的编译器。<br>
> 最好使用支持 `__VA_OPT__` 的编译器。

## 快速开始
要使用本库，你可以参考如下示例：
```cpp
// 你的工程文件
...
#include <HLMD/HLMD.h>
...
```

## 宏功能速查表
本仓库的大多数功能宏以 `HLMD__` + 功能名命名。例如：`HLMD_IS_EMPTY` 是一个用于检测参数是否为空的宏函数。<br>
下面是宏定义的查询表：<br>

|宏|参数/值|说明|
|-|-|-|
|`HLMD_EVAL_MIN_LEVEL`|`1.0.0` |当前 *`HLMD`* 库的**版本号**。|
|`HLMD_EVAL_MIN_LEVEL`|`0` |辅助循环宏的**最小循环层数**。|
|`HLMD_EVAL_MAX_LEVEL`|`5` |辅助循环宏的**最大循环层数**。|
|`HLMD_EVAL_MAX_DEPTH`|`243` |二级循环宏的**最大循环深度**。|
|`HLMD_EVAL_LEVEL_DEPTH`|`3` |二级循环宏**每层的深度**。|
|`HLMD_PRIMITIVE_CAT`|`head, tail, ...`|直接拼接 head 和 tail，**不展开**参数。|
|`HLMD_CAT`|`x, y`|**展开后**拼接 x 和 y，生成新标记。|
|`HLMD_GET_FIST_ARGS`|`first, ...`|获取参数包中的**第一个**参数。|
|`HLMD_GET_SEC_ARGS`|`first, second, ...`|获取参数包中的**第二个**参数。|
|`HLMD_GET_OTHER_ARGS`|`first, ...`|获取参数包中**除第一个外**的所有参数。|
|`HLMD_EMPTY`|`\`|空宏，常用作**延迟展开**的占位符。|
|`HLMD_EMPTY_ARG`|`...`|空宏，**丢弃所有参数**。|
|`HLMD_DEFER`|`id`|将宏 `id` 的展开**延迟一轮**。|
|`HLMD_EXPAND`|`...`|强制展开宏参数。|
|`HLMD_CHECK`|`...`|展开并获取第二个参数，若不存在则默认为0。|
|`HLMD_PROBE`|`x`|用于宏检测，展开为 `x, 1`。|
|`HLMD_NOT`|`x`|逻辑非，若 `x` 为 0/false/NULL/nullptr 返回1，否则返回0。|
|`HLMD_BOOL`|`x`|将 `x` 转换为1（真）或0（假），用于宏逻辑。|
|`HLMD_IF_ELSE`|`condition`|宏版 `if-else`，根据条件展开为真/假分支。|
|`HLMD_IS_EMPTY`|`...`|检测参数包是否为空。|
|`HLMD_IS_PAREN`|`x, ...`|检测参数是否带括号。|
|`HLMD_REMOVE_PAREN`|`...`|去除参数的括号（如有）。|
|`HLMD_FOR_EACH`|`macro, macro_args, ...`|对参数包中的每个参数应用 `macro`。|
|`HLMD_MANUAL_EVAL`|`level, ...`|手动指定递归宏展开的轮数。|
|`HLMD_AUTO_EVAL`|`...`|自动递归展开宏到最大层数。|
|`HLMD_DEF2STR`|`macro_define`|将宏定义转换为字符串字面量。|
|`HLMD_NUM2STR`|`num_define`|将数字宏转换为字符串字面量。|
|`HLMD_C_NULL`|`null`|将C语言中的`NULL ((void*)0)`重定向为`0`.|

> [!IMPORTANT]
> 在C语言中，如果尝试将 `NULL` 作为宏参数传递，请使用 `HLMD_C_NULL()` 包装器传递，因为 `ISO C` 要求 `NULL` 为 `((void*)0)`，这将导致连接失败，从而导致 `HLMD` 的宏定义失败。
