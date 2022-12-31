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

#ifndef GHOST_INT64_MAX_H_INCLUDED
#define GHOST_INT64_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INT64_MAX 9223372036854775807
 *
 * The maximum value of ghost_int64_t (always exactly 9223372036854775807 if it exists.)
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_INT64_MAX
    #ifdef GHOST_INT64_MAX
        #define ghost_has_GHOST_INT64_MAX 1
    #endif
#endif

/* ghost_int64_t is required. */
#ifndef ghost_has_GHOST_INT64_MAX
    #include "ghost/type/int64_t/ghost_int64_t.h"
    #if !ghost_has(ghost_int64_t)
        #define ghost_has_GHOST_INT64_MAX 0
    #endif
#endif

/* <stdint.h> has INT64_MAX in C99. It might be backported. */
#ifndef ghost_has_GHOST_INT64_MAX
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef INT64_MAX
        #define GHOST_INT64_MAX INT64_MAX
        #define ghost_has_GHOST_INT64_MAX 1
    #endif
#endif

/* GNU C compilers define __INT64_MAX__. */
#ifndef ghost_has_GHOST_INT64_MAX
    #ifdef __INT64_MAX__
        #define GHOST_INT64_MAX __INT64_MAX__
        #define ghost_has_GHOST_INT64_MAX 1
    #endif
#endif

/* Define it ourselves, provided we can declare constants properly. */
#ifndef ghost_has_GHOST_INT64_MAX
    #include "ghost/type/int64_t/ghost_int64_c.h"
    #if ghost_has(GHOST_INT64_C)
        #define GHOST_INT64_MAX GHOST_INT64_C(9223372036854775807)
        #define ghost_has_GHOST_INT64_MAX 1
    #endif
#endif

/* Otherwise we have no way to define it. */
#ifndef ghost_has_GHOST_INT64_MAX
    #define ghost_has_GHOST_INT64_MAX 0
#endif

/* Test max from sizeof (int64_t is not allowed to have padding bits) */
#if ghost_has(GHOST_INT64_MAX)
    #include "ghost/debug/ghost_static_assert.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/type/char/ghost_char_width.h"
    ghost_static_assert(GHOST_INT64_MAX ==
                ((((ghost_static_cast(ghost_int64_t, 1) << (sizeof(ghost_int64_t) * GHOST_CHAR_WIDTH - 2)) - 1) << 1) + 1),
            "GHOST_INT64_MAX is incorrect");
#endif

#endif
