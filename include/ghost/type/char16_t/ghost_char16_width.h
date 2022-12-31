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

#ifndef GHOST_CHAR16_WIDTH_H_INCLUDED
#define GHOST_CHAR16_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR16_WIDTH CHAR_BIT
 *
 * The width of ghost_char16_t.
 *
 * This is required to be the same width as uint_least16_t regardless of
 * whether it is a distinct type.
 */
#endif

/* TODO require the type?? */

#ifndef ghost_has_GHOST_CHAR16_WIDTH
    #ifndef GHOST_CHAR16_WIDTH
        /* TODO use uint_least16_t once we implement it. */
        #include "ghost/type/uint16_t/ghost_uint16_width.h"
        #define GHOST_CHAR16_WIDTH GHOST_UINT16_WIDTH
    #endif
    #define ghost_has_GHOST_CHAR16_WIDTH 1
#endif

/* Test width with sizeof, assuming no padding bits */
#if ghost_has(GHOST_CHAR16_WIDTH)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/type/char16_t/ghost_char16_t.h"
        #include "ghost/type/char/ghost_char_width.h"
        #include "ghost/debug/ghost_static_assert.h"
        ghost_static_assert(sizeof(ghost_char16_t) * GHOST_CHAR_WIDTH == GHOST_CHAR16_WIDTH,
                "GHOST_CHAR16_WIDTH is incorrect");
    #endif
#endif

#endif
