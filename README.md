![Liecense](https://img.shields.io/badge/Liencese-Apache_2.0-blue)     ![Language](https://img.shields.io/badge/Language-C/C++-red)

# HLMD: High-Level Macro Definitions
* This is a **`Head-Only`** library. All you need to do is add `HLMD.h` to the header directory of your build system

## Depend
> [!NOTE]
> **HLMD** minimum support is for compilers that support `std=c99` or `std=c++11`.<br>
## Fast to Start
To use this library, you can refer to the following documents:
```cpp
// you project file
...
#include <HLMD/HLMD.h>
...
```
## Macro WIKI
Most of the features in this repository have `HLMD__` + `feature name`.For exmaple: `HLMD_IS_EMPTY` is a macro function to check params is empty.<br>
Below is a query table for macro definitions:<br>
|Macro|Params/Value|description|
|-|-|-|
|`HLMD_EVAL_MIN_LEVEL`|`1.0.0` |The current **version** of the *`HLMD`* liburay.|
|`HLMD_EVAL_MIN_LEVEL`|`0` |The **minimum** cycle **level** of the auxiliary loop macro.|
|`HLMD_EVAL_MAX_LEVEL`|`5` |The **maximum** cycle **level** of the auxiliary loop macro.|
|`HLMD_EVAL_MAX_DEPTH`|`243` |The **maximum** loop **depth** of the secondary loop macro.|
|`HLMD_EVAL_LEVEL_DEPTH`|`3` |The **depth** of **each level** of the **secondary** loop macro.|
|`HLMD_PRIMITIVE_CAT`|`head, tail, ...`|Generate a new token by directly concatenating the head and tail **without unfolding**.|
|`HLMD_CAT`|`x, y`|**After unfolding**, splice the head and tail to generate a new token.|
|`HLMD_GET_FIST_ARGS`|`first, ...`|Get the **first** one in the parameter package.|
|`HLMD_GET_SECOND_ARGS`|`first, second, ...`|Get the **second** argument.|
|`HLMD_GET_OTHER_ARGS`|`first, ...`|Get the parameter package **outside of** the first one.|
|`HLMD_EMPTY`|`\`|An empty macro that is often used as a **placeholder** for **delayed expansion**.|
|`HLMD_EMPTY_ARG`|`...`|An empty macro that **discards** all arguments.|
|`HLMD_DEFER`|`id`|**Delay** the expansion of the macro `id` by one round.|
|`HLMD_EXPAND`|`...`|Force macro arguments to **expand**.|
|`HLMD_CHECK`|`...`|Expand and get the second argument, defaulting to 0 if not present.|
|`HLMD_PROBE`|`x`|Used for macro detection, expands to `x, 1`.|
|`HLMD_NOT`|`x`|Logical NOT, returns 1 if `x` is `0`,`false`,`NULL`,`nullptr`, otherwise `0`.|
|`HLMD_BOOL`|`x`|Convert `x` to `1 (true)` or `0 (false)` for macro logic.|
|`HLMD_IF_ELSE`|`condition`|Macro-based `if-else`, expands to true/false branch based on `condition`.|
|`HLMD_IS_EMPTY`|`...`|Check if the parameter pack is empty.|
|`HLMD_IS_PAREN`|`x, ...`|Check if the argument is parenthesized.|
|`HLMD_REMOVE_PAREN`|`...`|Remove parentheses from the argument if present.|
|`HLMD_REMOVE_PAREN_ARGS`|`...`|Remove parentheses and parameters, if any.|
|`HLMD__VA_OPT__`|`data_tuple, empty_tuple, ...`|Simulate the `__VA_OPT__` behavior: expand to 'empty_tuple' if the parameter package is empty, or 'data_tuple' otherwise (remove parentheses).|
|`HLMD_FOR_EACH`|`macro, macro_args, ...`|Apply `macro` to each argument in the parameter pack.|
|`HLMD_EVAL_MANUAL`|`level, ...`|Manually specify the number of recursive macro expansion rounds.|
|`HLMD_EVAL_AUTO`|`...`|Automatically expand macros up to the maximum level.|
|`HLMD_DEF2STR`|`macro_define`|Convert macro definition to string literal.|
|`HLMD_NUM2STR`|`num_define`|Convert number macro to string literal.|
|`HLMD_C_NULL`|`null`|Redirect `NULL ((void*)0)` in C to `0`.|

> [!IMPORTANT]
> In C, if you try to pass `NULL` as a macro parameter, use the `HLMD_C_NULL()` wrapper pass, because `ISO C` requires `NULL` to be `((void*)0)`, which will result in the failure to concatenate and thus the macro definition of `HLMD`.
