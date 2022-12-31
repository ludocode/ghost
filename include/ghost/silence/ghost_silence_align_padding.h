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

#ifndef GHOST_SILENCE_ALIGN_PADDING_H_INCLUDED
#define GHOST_SILENCE_ALIGN_PADDING_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_ALIGN_PADDING
 *
 * Silences warnings about structure padding changing due to an alignment
 * specifier.
 *
 * Example:
 *
 *     struct {
 *         long x;
 *         ghost_align_at(16) char y[6];
 *     } s;
 *
 * MSVC warns on the above because it has to insert padding to align y.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_ALIGN_PADDING
    #ifdef GHOST_SILENCE_ALIGN_PADDING
        #define ghost_has_GHOST_SILENCE_ALIGN_PADDING 1
    #endif
#endif

/*
 * MSVC C4324 in /W4
 * warning C4324: structure was padded due to alignment specifier
 *
 *     https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4324
 */
#ifndef ghost_has_GHOST_SILENCE_ALIGN_PADDING
    #ifdef _MSC_VER
        #define GHOST_SILENCE_ALIGN_PADDING __pragma(warning(disable:4324))
        #define ghost_has_GHOST_SILENCE_ALIGN_PADDING 1
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_ALIGN_PADDING
    #define GHOST_SILENCE_ALIGN_PADDING /*nothing*/
    #define ghost_has_GHOST_SILENCE_ALIGN_PADDING 1
#endif

#endif
