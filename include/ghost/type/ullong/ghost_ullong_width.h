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

#ifndef GHOST_ULLONG_WIDTH_H_INCLUDED
#define GHOST_ULLONG_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_ULLONG_WIDTH ULLONG_WIDTH
 *
 * The width of signed long long in bits.
 */
#endif

#ifndef ghost_has_GHOST_ULLONG_WIDTH
    #ifdef GHOST_ULLONG_WIDTH
        #define ghost_has_GHOST_ULLONG_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_ULLONG_WIDTH
    #include "ghost/type/ullong/ghost_ullong.h"
    #if !ghost_has(ghost_ullong)
        #define ghost_has_GHOST_ULLONG_WIDTH 0
    #endif
#endif

/* C23 adds ULLONG_WIDTH to <limits.h>. It might be backported. */
#ifndef ghost_has_GHOST_ULLONG_WIDTH
    #ifdef ULLONG_WIDTH
        #define GHOST_ULLONG_WIDTH ULLONG_WIDTH
        #define ghost_has_GHOST_ULLONG_WIDTH 1
    #endif
#endif

/* Assume it's the same as GHOST_LLONG_WIDTH if we have it. */
#ifndef ghost_has_GHOST_ULLONG_WIDTH
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_SIGNED_UNSIGNED_SAME_WIDTH
        #include "ghost/type/llong/ghost_llong_width.h"
        #if ghost_has(GHOST_LLONG_WIDTH)
            #define GHOST_ULLONG_WIDTH GHOST_LLONG_WIDTH
            #define ghost_has_GHOST_ULLONG_WIDTH 1
        #endif
    #endif
#endif

/* Otherwise we don't know the width. */
#ifndef ghost_has_GHOST_ULLONG_WIDTH
    #define ghost_has_GHOST_ULLONG_WIDTH 0
#endif

/* Test width with sizeof, assuming no padding bits */
#if ghost_has(GHOST_ULLONG_WIDTH)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(sizeof(ghost_ullong) * GHOST_CHAR_WIDTH == GHOST_ULLONG_WIDTH,
                "GHOST_ULLONG_WIDTH is incorrect");
    #endif
#endif

#endif
