/*
 * MIT No Attribution
 *
 * Copyright (c) 2022 Fraser Heavy Software
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef GHOST_COUNT_ARGS_H_INCLUDED
#define GHOST_COUNT_ARGS_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_COUNT_ARGS(...) <number of arguments>
 *
 * Expands to the number of arguments given (which is always at least one.)
 *
 * The C preprocessor doesn't really have the concept of "no arguments". If you
 * put nothing between the parentheses, this is really one argument which is
 * blank.
 *
 * In other words, this macro expands to the number of commas plus one, not
 * counting any commas in nested parentheses or other expressions. This means
 * `GHOST_COUNT_ARGS()` expands to 1, `GHOST_COUNT_ARGS(,)` expands to 2, and
 * `GHOST_COUNT_ARGS((,))` expands to 1.
 *
 * If you want to detect an empty argument list, use `GHOST_IS_BLANK()`.
 *
 * This implementation supports up to 63 arguments. (The C standard only
 * requires compilers to support up to 127 preprocessor arguments and this
 * implementation requires twice as many arguments as it can detect plus one.)
 *
 * @see GHOST_IS_BLANK
 */

/*
 * TODO apparently the C++ standard requires 256 args but MSVC still only
 * supports 127. we should check which is true and use the max args supported
 * for the current language standard or compiler.
 *     https://docs.microsoft.com/en-us/cpp/cpp/compiler-limits?view=msvc-170
 * maybe make GHOST_PP_MAX_ARGS in ghost_pp_max_args.h to say how many args are supported
 *     old gcc: https://gcc.gnu.org/onlinedocs/gcc-4.3.5/cpp/Implementation-limits.html
 *     new gcc: https://gcc.gnu.org/onlinedocs/cpp/Implementation-limits.html
 */

#ifndef ghost_has_GHOST_COUNT_ARGS
    #ifdef GHOST_COUNT_ARGS
        #define ghost_has_GHOST_COUNT_ARGS 1
    #endif
#endif

/* This requires variadic macros. */
#ifndef ghost_has_GHOST_COUNT_ARGS
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if !GHOST_PP_VA_ARGS
        #define ghost_has_GHOST_COUNT_ARGS 0
    #endif
#endif

/*
 * I'd love it if we could find a way to make this generate a compiler error if
 * you feed it more than 63 arguments. The current implementation just returns
 * the 64th argument which could silently compile to nonsense.
 *
 * A possible way to do this would be to use a larger implementation that
 * detects too many argument errors on compilers that support more arguments
 * (like GCC) and fallback to this on compilers that don't (like MSVC.)
 */

#ifndef ghost_has_GHOST_COUNT_ARGS
    #include "ghost/preprocessor/ghost_msvc_traditional.h"

    #define GHOST_COUNT_ARGS(...) \
                GHOST_COUNT_ARGS_IMPL(\
                    __VA_ARGS__, \
                    GHOST_COUNT_ARGS_IMPL_SEQUENCE, \
                    GHOST_COUNT_ARGS_IMPL_UNUSED)

    #if GHOST_MSVC_TRADITIONAL
        #include "ghost/preprocessor/ghost_expand.h"
        #define GHOST_COUNT_ARGS_IMPL(...) GHOST_EXPAND(GHOST_COUNT_ARGS_IMPL_64TH_ARG(__VA_ARGS__))
    #else
        #define GHOST_COUNT_ARGS_IMPL(...) GHOST_COUNT_ARGS_IMPL_64TH_ARG(__VA_ARGS__)
    #endif

    #define GHOST_COUNT_ARGS_IMPL_SEQUENCE \
                63, 62, 61, 60, 59, 58, 57, \
            56, 55, 54, 53, 52, 51, 50, 49, \
            48, 47, 46, 45, 44, 43, 42, 41, \
            40, 39, 38, 37, 36, 35, 34, 33, \
            32, 31, 30, 29, 28, 27, 26, 25, \
            24, 23, 22, 21, 20, 19, 18, 17, \
            16, 15, 14, 13, 12, 11, 10,  9, \
            8,  7,  6,  5,  4,  3,  2,  1

    #define GHOST_COUNT_ARGS_IMPL_64TH_ARG( \
            _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8, \
            _9, _10, _11, _12, _13, _14, _15, _16, \
            _17, _18, _19, _20, _21, _22, _23, _24, \
            _25, _26, _27, _28, _29, _30, _31, _32, \
            _33, _34, _35, _36, _37, _38, _39, _40, \
            _41, _42, _43, _44, _45, _46, _47, _48, \
            _49, _50, _51, _52, _53, _54, _55, _56, \
            _57, _58, _59, _60, _61, _62, _63, \
            x, ...) x

    #define ghost_has_GHOST_COUNT_ARGS 1
#endif

#endif
