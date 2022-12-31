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

#ifndef GHOST_CHAR8_WIDTH_H_INCLUDED
#define GHOST_CHAR8_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR8_WIDTH CHAR_BIT
 *
 * The width of ghost_char8_t.
 *
 * This is required to be the same width as unsigned char regardless of whether
 * it is a distinct type.
 *
 * Like char, this is 8 on all POSIX platforms.
 */
#endif

#ifndef ghost_has_GHOST_CHAR8_WIDTH
    #ifndef GHOST_CHAR8_WIDTH
        #include "ghost/type/uchar/ghost_uchar_width.h"
        #define GHOST_CHAR8_WIDTH GHOST_UCHAR_WIDTH
    #endif
    #define ghost_has_GHOST_CHAR8_WIDTH 1
#endif

/* Test width by comparing to unsigned char */
#if ghost_has(GHOST_CHAR8_WIDTH)
    #include "ghost/type/uchar/ghost_uchar_width.h"
    #include "ghost/debug/ghost_static_assert.h"
    ghost_static_assert(GHOST_UCHAR_WIDTH == GHOST_CHAR8_WIDTH,
            "GHOST_CHAR8_WIDTH is incorrect");
#endif

#endif
