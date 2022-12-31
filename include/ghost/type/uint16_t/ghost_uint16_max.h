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

#ifndef GHOST_UINT16_MAX_H_INCLUDED
#define GHOST_UINT16_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_UINT16_MAX 65535
 *
 * The maximum value of ghost_uint16_t (always exactly 65535 if it exists.)
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_UINT16_MAX
    #ifdef GHOST_UINT16_MAX
        #define ghost_has_GHOST_UINT16_MAX 1
    #endif
#endif

/* ghost_uint16_t is required. */
#ifndef ghost_has_GHOST_UINT16_MAX
    #include "ghost/type/uint16_t/ghost_uint16_t.h"
    #if !ghost_has(ghost_uint16_t)
        #define ghost_has_GHOST_UINT16_MAX 0
    #endif
#endif

/* <stdint.h> has UINT16_MAX in C99. It might be backported. */
#ifndef ghost_has_GHOST_UINT16_MAX
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef UINT16_MAX
        #define GHOST_UINT16_MAX UINT16_MAX
        #define ghost_has_GHOST_UINT16_MAX 1
    #endif
#endif

/* GNU C compilers define __UINT16_MAX__. */
#ifndef ghost_has_GHOST_UINT16_MAX
    #ifdef __UINT16_MAX__
        #define GHOST_UINT16_MAX __UINT16_MAX__
        #define ghost_has_GHOST_UINT16_MAX 1
    #endif
#endif

/* Define it ourselves, provided we can declare constants properly. */
#ifndef ghost_has_GHOST_UINT16_MAX
    #include "ghost/type/uint16_t/ghost_uint16_c.h"
    #if ghost_has(GHOST_UINT16_C)
        #define GHOST_UINT16_MAX GHOST_UINT16_C(65535)
        #define ghost_has_GHOST_UINT16_MAX 1
    #endif
#endif

/* Otherwise we have no way to define it. */
#ifndef ghost_has_GHOST_UINT16_MAX
    #define ghost_has_GHOST_UINT16_MAX 0
#endif

/* Test max from sizeof (uint16_t is not allowed to have padding bits) */
#if ghost_has(GHOST_UINT16_MAX)
    #include "ghost/debug/ghost_static_assert.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/type/char/ghost_char_width.h"
    ghost_static_assert(GHOST_UINT16_MAX ==
                ((((ghost_static_cast(ghost_uint16_t, 1U) << (sizeof(ghost_uint16_t) * GHOST_CHAR_WIDTH - 1)) - 1U) << 1) + 1U),
            "GHOST_UINT16_MAX is incorrect");
#endif

#endif
