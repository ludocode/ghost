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

#include "ghost/type/ullong/ghost_ullong.h"

#ifndef ghost_has_ghost_ullong
    #error "ghost/type/ullong/ghost_ullong.h must define ghost_has_ghost_ullong."
#endif

#include "test_common.h"

#if ghost_has_ghost_ullong
#include "ghost/type/ullong/ghost_ullong_max.h"
#include "ghost/type/ullong/ghost_ullong_c.h"

#if ghost_has(GHOST_ULLONG_MAX) && ghost_has(GHOST_ULLONG_C)
#include "ghost/language/ghost_discard.h"
#include "ghost/silence/ghost_silence_long_long.h"

GHOST_SILENCE_LONG_LONG

mirror() {
    /* make sure we can use constants without warnings */
    unsigned long long a = GHOST_ULLONG_MAX;
    ghost_discard(a);

    #if GHOST_LLONG_WIDTH == 64
    {
        /* make sure we can write big constants without warnings */
        unsigned long long x = GHOST_ULLONG_C(18446744073709551615); /* GHOST_ULLONG_MAX */
        ghost_discard(x);
    }
    #endif
}

#endif
#endif
