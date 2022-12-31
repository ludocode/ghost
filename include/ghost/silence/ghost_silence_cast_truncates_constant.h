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

#ifndef GHOST_SILENCE_CAST_TRUNCATES_CONSTANT_H_INCLUDED
#define GHOST_SILENCE_CAST_TRUNCATES_CONSTANT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_CAST_TRUNCATES_CONSTANT
 *
 * Silences warnings about casts truncating a constant value.
 *
 * MSVC under /W3 warns about constant truncations even if explicitly cast.
 *
 * For example:
 *
 *     unsigned short x = (unsigned short)(SHRT_MAX + 1);
 *
 * This causes "C4310: cast truncates constant value". In older versions of
 * MSVC, using static_cast<>() caused C4309 instead. Ghost silences the
 * necessary warnings for the current language and compiler version.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_CAST_TRUNCATES_CONSTANT
    #ifdef GHOST_SILENCE_CAST_TRUNCATES_CONSTANT
        #define ghost_has_GHOST_SILENCE_CAST_TRUNCATES_CONSTANT 1
    #endif
#endif

/* MSVC */
#ifndef ghost_has_GHOST_SILENCE_CAST_TRUNCATES_CONSTANT
    #ifdef _MSC_VER
        #if _MSC_VER < 1920 && defined(__cplusplus)
            /* In MSVC 2017 and earlier, static_cast<>() caused C4309 instead
             * of C4310 so we silence both. This silences all constant
             * truncations, not just casts, but we have no choice. */
            #define GHOST_SILENCE_CAST_TRUNCATES_CONSTANT \
                    __pragma(warning(disable:4309)) \
                    __pragma(warning(disable:4310))
        #else
            /* C4310: cast truncates constant value */
            #define GHOST_SILENCE_CAST_TRUNCATES_CONSTANT \
                    __pragma(warning(disable:4310))
        #endif
        #define ghost_has_GHOST_SILENCE_CAST_TRUNCATES_CONSTANT 1
    #endif
#endif

/* GCC and Clang have no comparable warning. */

#ifndef ghost_has_GHOST_SILENCE_CAST_TRUNCATES_CONSTANT
    #define GHOST_SILENCE_CAST_TRUNCATES_CONSTANT /*nothing*/
    #define ghost_has_GHOST_SILENCE_CAST_TRUNCATES_CONSTANT 1
#endif

#endif
