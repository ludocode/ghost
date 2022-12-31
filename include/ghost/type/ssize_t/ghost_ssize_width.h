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

#ifndef GHOST_SSIZE_WIDTH_H_INCLUDED
#define GHOST_SSIZE_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SSIZE_WIDTH SSIZE_WIDTH
 *
 * The width of ghost_ssize_t in bits.
 */
#endif

#ifndef ghost_has_GHOST_SSIZE_WIDTH
    #ifdef GHOST_SSIZE_WIDTH
        #define ghost_has_GHOST_SSIZE_WIDTH 1
    #endif
#endif

/* If we don't have ghost_ssize_t, we don't have a width. */
#ifndef ghost_has_GHOST_SSIZE_WIDTH
    #include "ghost/type/ssize_t/ghost_ssize_t.h"
    #if !ghost_has_ghost_ssize_t
        #define ghost_has_GHOST_SSIZE_WIDTH 0
    #endif
#endif

/* There doesn't appear to be any standard SSIZE_WIDTH even in POSIX. We try to
 * figure it out ourselves. */

/* Technically the width of ssize_t is allowed to differ from size_t but such
 * platforms are probably extremely uncommon. For now, if the width of size_t
 * is at least 32 bits we will assume the width of ssize_t matches it. A static
 * assert will check it below. */
#ifndef ghost_has_GHOST_SSIZE_WIDTH
    #include "ghost/type/size_t/ghost_size_width.h"
    #ifdef GHOST_SIZE_WIDTH
        #if GHOST_SIZE_WIDTH >= 32
            #define GHOST_SSIZE_WIDTH GHOST_SIZE_WIDTH
            #define ghost_has_GHOST_SSIZE_WIDTH 1
        #endif
    #endif
#endif

/* Otherwise we will need to add some platform detection code. For now we don't
 * know the width. */
#ifndef ghost_has_GHOST_SSIZE_WIDTH
    #define ghost_has_GHOST_SSIZE_WIDTH 0
#endif

/* Ensure width is correct */
#if ghost_has(GHOST_SSIZE_WIDTH)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(sizeof(ghost_ssize_t) * GHOST_CHAR_WIDTH == GHOST_SSIZE_WIDTH,
                "GHOST_SSIZE_WIDTH is incorrect");
    #endif
#endif

#endif
