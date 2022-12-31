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

#ifndef GHOST_SILENCE_STRINGOP_TRUNCATION_H_INCLUDED
#define GHOST_SILENCE_STRINGOP_TRUNCATION_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_STRINGOP_TRUNCATION
 *
 * Silences warnings about truncating a string.
 *
 * Example:
 *
 *     char buf[4];
 *     strncpy(buf, "hello", sizeof(buf)); // warning: string truncated
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_STRINGOP_TRUNCATION
    #ifdef GHOST_SILENCE_STRINGOP_TRUNCATION
        #define ghost_has_GHOST_SILENCE_STRINGOP_TRUNCATION 1
    #endif
#endif

/* GCC -Wstringop-truncation is available since GCC 8 */
#ifndef ghost_has_GHOST_SILENCE_STRINGOP_TRUNCATION
    #if defined(__GNUC__) && !defined(__CPARSER__) && !defined(__clang__)
        #if __GNUC__ >= 8
            #define GHOST_SILENCE_STRINGOP_TRUNCATION \
                    _Pragma("GCC diagnostic ignored \"-Wstringop-truncation\"")
            #define ghost_has_GHOST_SILENCE_STRINGOP_TRUNCATION 1
        #endif
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_STRINGOP_TRUNCATION
    #define GHOST_SILENCE_STRINGOP_TRUNCATION /*nothing*/
    #define ghost_has_GHOST_SILENCE_STRINGOP_TRUNCATION 1
#endif

#endif
