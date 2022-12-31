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

#ifndef GHOST_INT32_WIDTH_H_INCLUDED
#define GHOST_INT32_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INT32_WIDTH 32
 *
 * The width in bits of ghost_int32_t (always exactly 32 if it exists.)
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_INT32_WIDTH
    #ifdef GHOST_INT32_WIDTH
        #define ghost_has_GHOST_INT32_WIDTH 1
    #endif
#endif

/* ghost_int32_t is required. */
#ifndef ghost_has_GHOST_INT32_WIDTH
    #include "ghost/type/int32_t/ghost_int32_t.h"
    #if !ghost_has(ghost_int32_t)
        #define ghost_has_GHOST_INT32_WIDTH 0
    #endif
#endif

/* <stdint.h> has INT32_WIDTH in C23. It might be backported. */
#ifndef ghost_has_GHOST_INT32_WIDTH
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef INT32_WIDTH
        #define GHOST_INT32_WIDTH INT32_WIDTH
        #define ghost_has_GHOST_INT32_WIDTH 1
    #endif
#endif

/* Otherwise define it ourselves. The width is always exactly 32. */
#ifndef ghost_has_GHOST_INT32_WIDTH
    #define GHOST_INT32_WIDTH 32
    #define ghost_has_GHOST_INT32_WIDTH 1
#endif

/* Test width with sizeof (int32_t is not allowed to have padding bits) */
#if ghost_has(GHOST_INT32_WIDTH)
    #include "ghost/debug/ghost_static_assert.h"
    #include "ghost/type/char/ghost_char_width.h"
    ghost_static_assert(sizeof(ghost_int32_t) * GHOST_CHAR_WIDTH == GHOST_INT32_WIDTH,
            "GHOST_INT32_WIDTH is incorrect");
#endif

#endif
