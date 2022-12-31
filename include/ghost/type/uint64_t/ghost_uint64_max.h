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

#ifndef GHOST_UINT64_MAX_H_INCLUDED
#define GHOST_UINT64_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_UINT64_MAX 18446744073709551615
 *
 * The maximum value of ghost_uint64_t (always exactly 18446744073709551615 if it exists.)
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_UINT64_MAX
    #ifdef GHOST_UINT64_MAX
        #define ghost_has_GHOST_UINT64_MAX 1
    #endif
#endif

/* ghost_uint64_t is required. */
#ifndef ghost_has_GHOST_UINT64_MAX
    #include "ghost/type/uint64_t/ghost_uint64_t.h"
    #if !ghost_has(ghost_uint64_t)
        #define ghost_has_GHOST_UINT64_MAX 0
    #endif
#endif

/* <stdint.h> has UINT64_MAX in C99. It might be backported. */
#ifndef ghost_has_GHOST_UINT64_MAX
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef UINT64_MAX
        #define GHOST_UINT64_MAX UINT64_MAX
        #define ghost_has_GHOST_UINT64_MAX 1
    #endif
#endif

/* GNU C compilers define __UINT64_MAX__. */
#ifndef ghost_has_GHOST_UINT64_MAX
    #ifdef __UINT64_MAX__
        #define GHOST_UINT64_MAX __UINT64_MAX__
        #define ghost_has_GHOST_UINT64_MAX 1
    #endif
#endif

/* Define it ourselves, provided we can declare constants properly. */
#ifndef ghost_has_GHOST_UINT64_MAX
    #include "ghost/type/uint64_t/ghost_uint64_c.h"
    #if ghost_has(GHOST_UINT64_C)
        #define GHOST_UINT64_MAX GHOST_UINT64_C(18446744073709551615)
        #define ghost_has_GHOST_UINT64_MAX 1
    #endif
#endif

/* Otherwise we have no way to define it. */
#ifndef ghost_has_GHOST_UINT64_MAX
    #define ghost_has_GHOST_UINT64_MAX 0
#endif

/* Test max from sizeof (uint64_t is not allowed to have padding bits) */
#if ghost_has(GHOST_UINT64_MAX)
    #include "ghost/debug/ghost_static_assert.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/type/char/ghost_char_width.h"
    ghost_static_assert(GHOST_UINT64_MAX ==
                ((((ghost_static_cast(ghost_uint64_t, 1U) << (sizeof(ghost_uint64_t) * GHOST_CHAR_WIDTH - 1)) - 1U) << 1) + 1U),
            "GHOST_UINT64_MAX is incorrect");
#endif

#endif
