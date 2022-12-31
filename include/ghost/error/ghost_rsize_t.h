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

#ifndef GHOST_RSIZE_T_H_INCLUDED
#define GHOST_RSIZE_T_H_INCLUDED

#include "ghost/ghost_core.h"

/* TODO break this up like the others. actually can get rid of _C() and _MAX, they are the same as size_t. should probably get rid of this file entirely, just have ghost_rsize_t and GHOST_RSIZE_BOUNDS */

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines ghost_rsize_t and related macros:
 *
 * - GHOST_RSIZE_WIDTH
 * - GHOST_RSIZE_BOUNDS
 * - GHOST_RSIZE_C()
 *
 * This file is in ghost/error/ rather than ghost/type/ because, like errno_t,
 * rsize_t is part of the rarely implemented error-checking interfaces in C11
 * Annex K.
 */

/**
 * An alias of size_t, matching the behaviour of C11 Annex K rsize_t.
 */
typedef rsize_t ghost_rsize_t;

/**
 * @def GHOST_RSIZE_WIDTH RSIZE_WIDTH
 *
 * The width in bits of ghost_rsize_t.
 *
 * This is the same as GHOST_SIZE_WIDTH.
 */

/**
 * @def GHOST_RSIZE_BOUNDS RSIZE_MAX
 *
 * An alias of RSIZE_MAX, the maximum value accepted by bounds-checked
 * functions (not necessarily the largest value that can be stored in
 * ghost_rsize_t.)
 *
 * Note that this does not necessarily match the value of SIZE_MAX or
 * GHOST_SIZE_MAX. This is instead the maximum value accepted by bounds-checked
 * C11 Annex K functions. The type may be able to store larger values, and if
 * so, bounds-checked functions call the constraint handler upon receiving such
 * values.
 *
 * For these reasons Ghost calls this GHOST_RSIZE_BOUNDS instead of
 * GHOST_RSIZE_MAX in order to avoid mistaking this value as the storage limit
 * of rsize_t, as in the other GHOST_*_MAX constants.
 *
 * If a real RSIZE_MAX is not available, Ghost uses half the value of SIZE_MAX
 * (rounded down) in order to guard against negative values being cast to
 * unsigned.
 *
 * Ghost intentionally does not define GHOST_RSIZE_MAX so that it isn't
 * mistaken as either SIZE_MAX or RSIZE_MAX. rsize_t is an alias of size_t so
 * if you want the integer limit of rsize_t, use GHOST_SIZE_MAX instead.
 */

/**
 * @def GHOST_RSIZE_C(x) x
 *
 * Defines a preprocessor constant that can be used as a value of type
 * ghost_rsize_t.
 */
#endif

/*
 * ghost_rsize_t
 */

#ifndef ghost_has_ghost_rsize_t
    #ifdef ghost_rsize_t
        #define ghost_has_ghost_rsize_t 1
    #endif
#endif

/* rsize_t is defined as an alias of size_t. We don't use any real rsize_t
 * because we can't safely detect whether it exists. (We can't even rely on
 * e.g. the RSIZE_MAX macro because macOS defines RSIZE_MAX without defining
 * rsize_t!) */
#ifndef ghost_has_ghost_rsize_t
    #include "ghost/type/size_t/ghost_size_t.h"
    typedef ghost_size_t ghost_rsize_t;
    #define ghost_has_ghost_rsize_t 1
#endif

/**
 * GHOST_RSIZE_WIDTH
 */

#ifndef ghost_has_GHOST_RSIZE_WIDTH
    #ifdef GHOST_RSIZE_WIDTH
        #define ghost_has_GHOST_RSIZE_WIDTH 1
    #endif
#endif

/* There's no proper RSIZE_WIDTH yet but rsize_t is supposed to be a typedef of
 * the same type as size_t (and ours always is above) so we map it to
 * SIZE_WIDTH. */
#ifndef ghost_has_GHOST_RSIZE_WIDTH
    #include "ghost/type/size_t/ghost_size_width.h"
    #include "ghost/debug/ghost_static_assert.h"
    #if ghost_has(GHOST_SIZE_WIDTH)
        ghost_static_assert(sizeof(ghost_rsize_t) * CHAR_BIT == GHOST_SIZE_WIDTH,
                "GHOST_RSIZE_WIDTH does not match width of ghost_rsize_t");
        #define GHOST_RSIZE_WIDTH GHOST_SIZE_WIDTH
        #define ghost_has_GHOST_RSIZE_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_RSIZE_WIDTH
    #define ghost_has_GHOST_RSIZE_WIDTH 0
#endif

/**
 * GHOST_RSIZE_BOUNDS
 */

#ifndef ghost_has_GHOST_RSIZE_BOUNDS
    #ifdef GHOST_RSIZE_BOUNDS
        #define ghost_has_GHOST_RSIZE_BOUNDS 1
    #endif
#endif

#ifndef ghost_has_GHOST_RSIZE_BOUNDS
    /* As above we check whether RSIZE_MAX was defined instead of checking the
     * C11 Annex K macros. */
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef RSIZE_MAX
        #define GHOST_RSIZE_BOUNDS RSIZE_MAX
        #define ghost_has_GHOST_RSIZE_BOUNDS 1
    #endif
#endif

#ifndef ghost_has_GHOST_RSIZE_BOUNDS
    /* Assume it's half the of SIZE_MAX to guard against "negative" values. */
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/type/size_t/ghost_size_max.h"
    #if ghost_has(GHOST_SIZE_MAX)
        #define GHOST_RSIZE_BOUNDS (GHOST_SIZE_MAX >> 1)
        #define ghost_has_GHOST_RSIZE_BOUNDS 1
    #endif
#endif

#ifndef ghost_has_GHOST_RSIZE_BOUNDS
    #define ghost_has_GHOST_RSIZE_BOUNDS 0
#endif

/*
 * GHOST_RSIZE_C()
 */

#ifndef ghost_has_GHOST_RSIZE_C
    #ifdef GHOST_RSIZE_C
        #define ghost_has_GHOST_RSIZE_C 1
    #endif
#endif

#ifndef ghost_has_GHOST_RSIZE_C
    #include "ghost/type/size_t/ghost_size_c.h"
    #if ghost_has(GHOST_SIZE_C)
        #define GHOST_RSIZE_C GHOST_SIZE_C
        #define ghost_has_GHOST_RSIZE_C 1
    #endif
#endif

#ifndef ghost_has_GHOST_RSIZE_C
    #define ghost_has_GHOST_RSIZE_C 0
#endif

#endif
