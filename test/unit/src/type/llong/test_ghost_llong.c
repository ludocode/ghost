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

#include "ghost/type/llong/ghost_llong.h"

#ifndef ghost_has_ghost_llong
    #error "ghost/type/ghost_llong.h must define ghost_has_ghost_llong."
#endif

#include "test_common.h"

#if ghost_has_ghost_llong
#include "ghost/type/llong/ghost_llong_min.h"
#include "ghost/type/llong/ghost_llong_max.h"
#include "ghost/type/llong/ghost_llong_c.h"

#if ghost_has(GHOST_LLONG_MIN) && ghost_has(GHOST_LLONG_MAX) && ghost_has(GHOST_LLONG_C)
#include "ghost/language/ghost_discard.h"
#include "ghost/silence/ghost_silence_long_long.h"

GHOST_SILENCE_LONG_LONG

mirror() {
    /* make sure we can use constants without warnings */
    long long a = GHOST_LLONG_MAX;
    long long b = GHOST_LLONG_MIN;
    ghost_discard(a);
    ghost_discard(b);

    #if GHOST_LLONG_WIDTH == 64
    {
        /* make sure we can write big constants without warnings
         * note that we can't actually write -9223372036854775808 because this
         * is parsed as two tokens, a unary negative and a number, the latter
         * of which is too large to fit in signed long long. */
        long long x = GHOST_LLONG_C(9223372036854775807); /* GHOST_LLONG_MAX */
        long long y = GHOST_LLONG_C(-9223372036854775807); /* GHOST_LLONG_MIN + 1 */
        ghost_discard(x);
        ghost_discard(y);
    }
    #endif
}

#endif
#endif
