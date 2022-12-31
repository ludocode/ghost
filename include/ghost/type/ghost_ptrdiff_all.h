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

#ifndef GHOST_PTRDIFF_ALL_H_INCLUDED
#define GHOST_PTRDIFF_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines ghost_ptrdiff_t and related macros:
 *
 * - GHOST_PTRDIFF_MIN
 * - GHOST_PTRDIFF_MAX
 * - GHOST_PTRDIFF_WIDTH
 * - GHOST_PTRDIFF_C()
 *
 * This also tries to include platform headers that define the standards:
 * ptrdiff_t, PTRDIFF_MAX, etc. If these exist in the platform, Ghost's
 * definitions are wrappers for them.
 *
 * If you're looking for portable format specifiers for printing and scanning
 * ptrdiff_t (e.g. GHOST_PRIdPD), see ghost/format/ghost_format_pd.h .
 */

/**
 * An alias of ptrdiff_t (if possible), which is a signed integer type that
 * matches the result type of the difference between two pointers.
 *
 * If a platform ptrdiff_t exists (which it essentially always does),
 * ghost_ptrdiff_t is a typedef of it. In other words, you can include this and
 * simply use ptrdiff_t everywhere.
 */
typedef ptrdiff_t ghost_ptrdiff_t;

/**
 * @def GHOST_PTRDIFF_C(x) x
 *
 * Defines a preprocessor constant of type ghost_ptrdiff_t.
 */

/**
 * @def GHOST_PTRDIFF_MAX PTRDIFF_MAX
 *
 * The maximum value of ghost_ptrdiff_t.
 */

/**
 * @def GHOST_PTRDIFF_WIDTH PTRDIFF_WIDTH
 *
 * The width of ghost_ptrdiff_t in bits.
 */
#endif

/* We include system headers to make sure the real size_t, SIZE_WIDTH, etc.
 * will be defined if possible. SIZE_WIDTH will be in <stdint.h> in C23. */
#include "ghost/header/c/ghost_stddef_h.h"
#include "ghost/header/c/ghost_stdint_h.h"
#include "ghost/header/c/ghost_limits_h.h"

/* See what's pre-defined by the user */
#ifndef ghost_has_ghost_ptrdiff_t
    #ifdef ghost_ptrdiff_t
        #define ghost_has_ghost_ptrdiff_t 1
    #endif
#endif
#ifndef ghost_has_GHOST_PTRDIFF_C
    #ifdef GHOST_PTRDIFF_C
        #define ghost_has_GHOST_PTRDIFF_C 1
    #endif
#endif
#ifndef ghost_has_GHOST_PTRDIFF_MAX
    #ifdef GHOST_PTRDIFF_MAX
        #define ghost_has_GHOST_PTRDIFF_MAX 1
    #endif
#endif
#ifndef ghost_has_GHOST_PTRDIFF_MIN
    #ifdef GHOST_PTRDIFF_MIN
        #define ghost_has_GHOST_PTRDIFF_MIN 1
    #endif
#endif
#ifndef ghost_has_GHOST_PTRDIFF_WIDTH
    #ifdef GHOST_PTRDIFF_WIDTH
        #define ghost_has_GHOST_PTRDIFF_WIDTH 1
    #endif
#endif

/*
 * ptrdiff_t is in <stddef.h> which has been around since ANSI C and is
 * supposed to be available even in freestanding. It's usually provided by the
 * compiler rather than the libc. We therefore assume for now that ptrdiff_t is
 * always going to be defined and correct even if for some strange reason we
 * don't have <stddef.h>.
 *
 * If we find some esoteric platforms that don't define it we can do something
 * special later.
 */
#ifndef ghost_has_ghost_ptrdiff_t
    typedef ptrdiff_t ghost_ptrdiff_t;
    #define ghost_has_ghost_ptrdiff_t 1
#endif

/* See what we can gather from <limits.h>
 *     https://en.cppreference.com/w/c/types/limits */
#ifndef ghost_has_GHOST_PTRDIFF_MAX
    #ifdef PTRDIFF_MAX
        #define GHOST_PTRDIFF_MAX PTRDIFF_MAX
        #define ghost_has_GHOST_PTRDIFF_MAX 1
    #endif
#endif
#ifndef ghost_has_GHOST_PTRDIFF_MIN
    #ifdef PTRDIFF_MIN
        #define GHOST_PTRDIFF_MIN PTRDIFF_MIN
        #define ghost_has_GHOST_PTRDIFF_MIN 1
    #endif
#endif
#ifndef ghost_has_GHOST_PTRDIFF_WIDTH
    /* C23 adds PTRDIFF_WIDTH to <limits.h>. It might be backported. */
    #ifdef PTRDIFF_WIDTH
        #define GHOST_PTRDIFF_WIDTH PTRDIFF_WIDTH
        #define ghost_has_GHOST_PTRDIFF_WIDTH 1
    #endif
#endif

/* For whatever we're missing, for now we will assume ptrdiff_t is the same
 * size as intptr_t. This is not necessarily true on all machines so we have
 * some static asserts to verify it. */

#ifndef ghost_has_ghost_ptrdiff_t
    #include "ghost/type/intptr_t/ghost_intptr_t.h"
    #if ghost_has(ghost_intptr_t)
        typedef ghost_intptr_t ghost_ptrdiff_t;
        #define ghost_has_ghost_ptrdiff_t 1
    #endif
#endif

#ifndef ghost_has_GHOST_PTRDIFF_MAX
    #include "ghost/type/intptr_t/ghost_intptr_t.h"
    #if ghost_has(GHOST_INTPTR_MAX)
        #define GHOST_PTRDIFF_MAX GHOST_INTPTR_MAX
        #define ghost_has_GHOST_PTRDIFF_MAX 1
    #endif
#endif

#ifndef ghost_has_GHOST_PTRDIFF_MIN
    #include "ghost/type/intptr_t/ghost_intptr_t.h"
    #if ghost_has(GHOST_INTPTR_MIN)
        #define GHOST_PTRDIFF_MIN GHOST_INTPTR_MIN
        #define ghost_has_GHOST_PTRDIFF_MIN 1
    #endif
#endif

#ifndef ghost_has_GHOST_PTRDIFF_WIDTH
    #include "ghost/type/intptr_t/ghost_intptr_t.h"
    #if ghost_has(GHOST_INTPTR_WIDTH)
        #define GHOST_PTRDIFF_WIDTH GHOST_INTPTR_WIDTH
        #define ghost_has_GHOST_PTRDIFF_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_PTRDIFF_C
    #include "ghost/type/intptr_t/ghost_intptr_t.h"
    #if ghost_has(GHOST_INTPTR_C)
        #define GHOST_PTRDIFF_C GHOST_INTPTR_C
        #define ghost_has_GHOST_PTRDIFF_C 1
    #endif
#endif

/*
 * Finally, turn off anything we haven't figured out.
 */

#ifndef ghost_has_ghost_ptrdiff_t
    #define ghost_has_ghost_ptrdiff_t 0
#endif
#ifndef ghost_has_GHOST_PTRDIFF_WIDTH
    #define ghost_has_GHOST_PTRDIFF_WIDTH 0
#endif
#ifndef ghost_has_GHOST_PTRDIFF_MAX
    #define ghost_has_GHOST_PTRDIFF_MAX 0
#endif
#ifndef ghost_has_GHOST_PTRDIFF_MIN
    #define ghost_has_GHOST_PTRDIFF_MIN 0
#endif
#ifndef ghost_has_GHOST_PTRDIFF_C
    #define ghost_has_GHOST_PTRDIFF_C 0
#endif

/*
 * Sanity checks
 */

#include "ghost/debug/ghost_static_assert.h"
#include "ghost/language/ghost_static_cast.h"
#include "ghost/type/char/ghost_char_width.h"

/*
 * Test width with sizeof
 *
 * (Technically integer types are allowed to have padding bits so this test is
 * not really correct. Still, this is more likely to catch cases of Ghost
 * incorrectly determining widths than it is to fail on platforms with
 * padding so I'd rather disable the test only on those platforms that have
 * padding.)
 */
#if ghost_has_GHOST_CHAR_WIDTH
    #if ghost_has_GHOST_PTRDIFF_WIDTH
        ghost_static_assert(sizeof(ghost_ptrdiff_t) * GHOST_CHAR_WIDTH == GHOST_PTRDIFF_WIDTH,
                "GHOST_PTRDIFF_WIDTH is incorrect");
    #endif
#endif

/* We need some sort of test that min and max make sense. Unfortunately we
 * can't test with signed overflow because even compilers that support it as an
 * extension don't consider it a constant expression. */

#endif
