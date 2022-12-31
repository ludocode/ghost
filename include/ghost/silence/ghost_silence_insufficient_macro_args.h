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

#ifndef GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS_H_INCLUDED
#define GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS
 *
 * Silences an MSVC warning about providing no arguments to a macro that takes
 * a single argument.
 *
 * GCC warns about this under -Wpedantic in strict ANSI C mode. The warning
 * can't be silenced without disabling all of -Wpedantic which this macro does
 * not do.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS
    #ifdef GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS
        #define ghost_has_GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS 1
    #endif
#endif

/* MSVC C4100 in /W4
 *     https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4100 */
#ifndef ghost_has_GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS
    #ifdef _MSC_VER
        #define GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS __pragma(warning(disable:4100))
        #define ghost_has_GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS 1
    #endif
#endif

/* For GCC this would require disabling -Wpedantic; see above. */

#ifndef ghost_has_GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS
    #define GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS /*nothing*/
    #define ghost_has_GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS 1
#endif

#endif
