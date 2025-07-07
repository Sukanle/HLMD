/*
 * Copyright 2025 Sukanle
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HLMD_LIB
#define HLMD_LIB

#define HLMD_LIB_VERSION 1.0.1  /* The current version of the HLMD library. */
#define HLMD_EVAL_MIN_LEVEL 0   /* The minimum cycle level of the auxiliary loop macro. */
#define HLMD_EVAL_MAX_LEVEL 5   /* The minimum cycle level of the auxiliary loop macro. */
#define HLMD_EVAL_MAX_DEPTH 243 /* The maximum cycle level of the auxiliary loop macro. */
#define HLMD_EVAL_LEVEL_DEPTH 3 /* The maximum cycle level of the auxiliary loop macro. */

#define HLMD_PRIMITIVE_CAT(head, tail, ...) head##tail              /* Generate a new token by directly concatenating the head and tail without unfolding. */
#define HLMD_CAT(head, tail)  HLMD_PRIMITIVE_CAT(head, tail)        /* After unfolding, splice the head and tail to generate a new token. */

#define HLMD_GET_FIRST_ARGS(first, ...) first            /* Get the first one in the parameter package. */
#define HLMD_GET_SECOND_ARGS(first, second, ...) second /* Get the second argument. */
#define HLMD_GET_OTHER_ARGS(first, ...) __VA_ARGS__     /* Get the parameter package outside of the first one. */

#define __HLMD_IIF(condition) HLMD_PRIMITIVE_CAT(__HLMD_IIF_, condition)
#define __HLMD_IIF_1(t, ...) HLMD_GET_FIRST_ARGS(t, ...)
#define __HLMD_IIF_0(t, ...) HLMD_GET_OTHER_ARGS(t, ...)

#define HLMD_EMPTY()        /* An empty macro that is often used as a placeholder for delayed expansion. */
#define HLMD_EMPTY_ARG(...) /* An empty macro that discards all arguments. */

#define HLMD_DEFER(id) id HLMD_EMPTY() /* Delay the expansion of the macro id by one round. */
#define HLMD_EXPAND(...) __VA_ARGS__   /* Force macro arguments to expand. */

#define HLMD_CHECK(...) HLMD_EXPAND(HLMD_GET_SECOND_ARGS(__VA_ARGS__, 0)) /* Expand and get the second argument, defaulting to 0 if not present. */
#define HLMD_PROBE(x) x, 1                                                /* Used for macro detection, expands to x, 1. */

#define HLMD_NOT(x) HLMD_CHECK(HLMD_PRIMITIVE_CAT(__HLMD_NOT_, x)) /* Logical NOT, returns 1 if x is `0, false, NULL, nullptr`, otherwise 0. */
#define __HLMD_NOT_0 HLMD_PROBE()
#define __HLMD_NOT_false HLMD_PROBE()
#define __HLMD_NOT___null HLMD_PROBE()
#define __HLMD_NOT_nullptr HLMD_PROBE()

#define HLMD_BOOL(x) HLMD_NOT(HLMD_CHECK(HLMD_CAT(__HLMD_NOT_, x)))                                          /* Convert x to 1 (true) or 0 (false) for macro logic. */
#define HLMD_IF_ELSE(condition) HLMD_CAT(__HLMD_IF_, HLMD_NOT(HLMD_CHECK(HLMD_CAT(__HLMD_NOT_, condition)))) /* Macro-based if-else, expands to true/false branch based on condition. */
#define __HLMD_IF_1(...) __VA_ARGS__ HLMD_EMPTY_ARG
#define __HLMD_IF_0(...) HLMD_EXPAND
#define __HLMD_0_BRANCH(...) __VA_ARGS__
#define __HLMD_IF_TRUE() true
#define __HLMD_IF_FASLE() false

#define HLMD_IS_EMPTY(...) HLMD_CHECK(HLMD_CAT(HLMD_PRIMITIVE_CAT(__HLMD_IS_EMPTY_, __VA_ARGS__), 0)) /* Check if the parameter pack is empty. */
#define __HLMD_IS_EMPTY_0 HLMD_PROBE()

#define HLMD_IS_PAREN(x, ...) HLMD_CHECK(HLMD__VA_OPT__(, 0, ) __HLMD_IS_PAREN_PROBE x)                                 /* Check if the argument is parenthesized. */
#define HLMD_REMOVE_PAREN(...) HLMD_IF_ELSE(HLMD_IS_PAREN(__VA_ARGS__))(HLMD_EXPAND __VA_ARGS__)(__VA_ARGS__)           /* Remove parentheses from the argument if present. */
#define HLMD_REMOVE_PAREN_ARGS(...) HLMD_IF_ELSE(HLMD_IS_PAREN(__VA_ARGS__))(HLMD_EMPTY_ARG __VA_ARGS__)(__VA_ARGS__)   /* Remove parentheses and parameters, if any. */
#define __HLMD_IS_PAREN_PROBE(...) HLMD_PROBE()

/* Simulate the '__VA_OPT__' behavior: expand to 'empty_tuple' if the parameter package is empty, or 'data_tuple' otherwise (remove parentheses). */
#define HLMD__VA_OPT__(data_tuple, empty_tuple, ...) \
    HLMD_REMOVE_PAREN(HLMD_IF_ELSE(HLMD_IS_EMPTY(__VA_ARGS__))(empty_tuple)(data_tuple))

/* Apply macro to each argument in the parameter pack. */
#define HLMD_FOR_EACH(macro, macro_args, ...)                                                    \
    HLMD_CAT(__HLMD_FOR_EACH_,HLMD_IS_EMPTY(HLMD_REMOVE_PAREN(HLMD_GET_FIST_ARGS(__VA_ARGS__)))) \
    (macro, macro_args, __VA_ARGS__)
#define __HLMD_FOR_EACH_0(macro, macro_args, ...) \
    __HLMD_FOR_EACH_1(macro, macro_args)          \
    HLMD_DEFER(__HLMD_FOR_EACH_N)()(macro, __VA_ARGS__)
#define __HLMD_FOR_EACH_1(macro, macro_args, ...) \
    HLMD_IF_ELSE(HLMD_IS_PAREN(macro_args))(macro macro_args)(macro(macro_args))
#define __HLMD_FOR_EACH_N() HLMD_FOR_EACH

#define HLMD_EVAL_MANUAL(level, ...) HLMD_CAT(__HLMD_EVAL, level)(__VA_ARGS__) /* Manually specify the number of recursive macro expansion rounds. */
#define HLMD_EVAL_AUTO(...) HLMD_EVAL_MANUAL(HLMD_EVAL_MAX_LEVEL, __VA_ARGS__) /* Automatically expand macros up to the maximum level. */

#define __HLMD_EVAL5(...) __HLMD_EVAL4(__HLMD_EVAL4(__HLMD_EVAL4(__VA_ARGS__)))
#define __HLMD_EVAL4(...) __HLMD_EVAL3(__HLMD_EVAL3(__HLMD_EVAL3(__VA_ARGS__)))
#define __HLMD_EVAL3(...) __HLMD_EVAL2(__HLMD_EVAL2(__HLMD_EVAL2(__VA_ARGS__)))
#define __HLMD_EVAL2(...) __HLMD_EVAL1(__HLMD_EVAL1(__HLMD_EVAL1(__VA_ARGS__)))
#define __HLMD_EVAL1(...) __HLMD_EVAL0(__HLMD_EVAL0(__HLMD_EVAL0(__VA_ARGS__)))
#define __HLMD_EVAL0(...) __VA_ARGS__

#define HLMD_DEF2STR(macro_define) #macro_define          /* Convert macro definition to string literal. */
#define HLMD_NUM2STR(num_define) HLMD_DEF2STR(num_define) /* Convert number macro to string literal. */

#ifndef __cplusplus
#define HLMD_C_NULL(null) HLMD_REMOVE_PAREN_ARGS null /* Redirect NULL ((void*)0) in C to 0. */
#else
#define HLMD_C_NULL(null) null
#endif


#define HLMD_LIST_PUSH_BACK(args,...) HLMD_EXPAND args HLMD__VA_OPT__((,), (), __VA_ARGS__) __VA_ARGS__

#endif
