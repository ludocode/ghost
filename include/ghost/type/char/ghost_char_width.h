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

#ifndef GHOST_CHAR_WIDTH_H_INCLUDED
#define GHOST_CHAR_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR_WIDTH CHAR_BIT
 *
 * The number of bits in a char.
 */
#endif

#ifndef ghost_has_GHOST_CHAR_WIDTH
    #ifdef GHOST_CHAR_WIDTH
        #define ghost_has_GHOST_CHAR_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_CHAR_WIDTH
    #include "ghost/type/char/ghost_char.h"
    #if !ghost_has(ghost_char)
        #define ghost_has_GHOST_CHAR_WIDTH 0
    #endif
#endif

/* C23 adds CHAR_WIDTH but we don't bother to wrap it since it's an alias of
 * CHAR_BIT, and because char (technically only signed char, but we assume
 * unsigned char is the same width) isn't allowed to have any padding bits. */

/* CHAR_BIT should always exist in <limits.h>. */
#ifndef ghost_has_GHOST_CHAR_WIDTH
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef CHAR_BIT
        #define GHOST_CHAR_WIDTH CHAR_BIT
        #define ghost_has_GHOST_CHAR_WIDTH 1
    #endif
#endif

/* In case it doesn't, GNU C compilers define __CHAR_BIT__ */
#ifndef ghost_has_GHOST_CHAR_WIDTH
    #ifdef __CHAR_BIT__
        #define GHOST_CHAR_WIDTH __CHAR_BIT__
        #define ghost_has_GHOST_CHAR_WIDTH 1
    #endif
#endif

/* POSIX requires that CHAR_BIT is 8. We could try to detect POSIX here but
 * there's no point because we'll just assume it's 8 on all platforms. */

/* Assume CHAR_BIT is 8. */
#ifndef ghost_has_GHOST_CHAR_WIDTH
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if !GHOST_IMPL_ASSUME_8_BIT_CHAR
        #error "GHOST_CHAR_WIDTH (a.k.a. CHAR_BIT) is required."
    #endif
    #define GHOST_CHAR_WIDTH 8
    #define ghost_has_GHOST_CHAR_WIDTH 1
#endif

/* There isn't really a way to static assert this but ghost_uchar_max.h does
 * assert that the max value is correct and char isn't allowed to have padding
 * bits. */

#endif
