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

#ifndef GHOST_SILENCE_CONSTANT_COMPARISON_H_INCLUDED
#define GHOST_SILENCE_CONSTANT_COMPARISON_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_CONSTANT_COMPARISON
 *
 * Silences warnings about constant comparisons (i.e. comparisons that can be
 * resolved at compile time.)
 *
 * MSVC under /W4 warns about constant comparisons even if one side is a macro.
 * This is hostile to configurable or machine-generated code. For example:
 *
 *     // in config.h
 *     #define FOO_COUNT 10
 *
 *     // in foo.c
 *     if (FOO_COUNT > 5) {
 *         // handle many
 *     } else {
 *         // handle few
 *     }
 *
 * This causes "C4127: comparison is constant". The above example is a bit
 * contrived since you could replace it with #if but it's not always possible
 * to do that. FOO_COUNT for example could be a variable in some configurations
 * and a constant in others. In such cases it's best to silence the warning.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_CONSTANT_COMPARISON
    #ifdef GHOST_SILENCE_CONSTANT_COMPARISON
        #define ghost_has_GHOST_SILENCE_CONSTANT_COMPARISON 1
    #endif
#endif

/* MSVC C4127 in /W4 */
#ifndef ghost_has_GHOST_SILENCE_CONSTANT_COMPARISON
    #ifdef _MSC_VER
        /* C4127: comparison is constant */
        #define GHOST_SILENCE_CONSTANT_COMPARISON __pragma(warning(disable:4127))
        #define ghost_has_GHOST_SILENCE_CONSTANT_COMPARISON 1
    #endif
#endif

/* GCC and Clang have no comparable warning. They don't seem to warn about even
 * non-macro constant comparisons like `if (5 == 5)`. */

#ifndef ghost_has_GHOST_SILENCE_CONSTANT_COMPARISON
    #define GHOST_SILENCE_CONSTANT_COMPARISON /*nothing*/
    #define ghost_has_GHOST_SILENCE_CONSTANT_COMPARISON 1
#endif

#endif
