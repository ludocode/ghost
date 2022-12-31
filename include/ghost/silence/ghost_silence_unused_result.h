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

#ifndef GHOST_SILENCE_UNUSED_RESULT_H_INCLUDED
#define GHOST_SILENCE_UNUSED_RESULT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_UNUSED_RESULT
 *
 * Silences warnings about discarding the result of a nodiscard function.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_UNUSED_RESULT
    #ifdef GHOST_SILENCE_UNUSED_RESULT
        #define ghost_has_GHOST_SILENCE_UNUSED_RESULT 1
    #endif
#endif

/* GCC/Clang -Wunused-result */
#ifndef ghost_has_GHOST_SILENCE_UNUSED_RESULT
    #if defined(__GNUC__) && !defined(__CPARSER__)
        /* _Pragma GCC diagnostic is supported since GCC 4.2 */
        #if defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
            #define GHOST_SILENCE_UNUSED_RESULT \
                    _Pragma("GCC diagnostic ignored \"-Wunused-result\"")
            #define ghost_has_GHOST_SILENCE_UNUSED_RESULT 1
        #endif
    #endif
#endif

/*
 * MSVC C4834 in /W1
 *
 * warning C4834: discarding return value of function with 'nodiscard' attribute
 *
 *     https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c4834
 *
 * Note that this doesn't warn about _Check_return_. The Microsoft compiler
 * ignores _Check_return_. It's only used during static analysis and I don't
 * know of any way to silence it there.
 */
#ifndef ghost_has_GHOST_SILENCE_UNUSED_RESULT
    #ifdef _MSC_VER
        #define GHOST_SILENCE_UNUSED_RESULT __pragma(warning(disable:4834))
        #define ghost_has_GHOST_SILENCE_UNUSED_RESULT 1
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_UNUSED_RESULT
    #define GHOST_SILENCE_UNUSED_RESULT /*nothing*/
    #define ghost_has_GHOST_SILENCE_UNUSED_RESULT 1
#endif

#endif
