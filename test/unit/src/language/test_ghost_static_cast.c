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

#include "ghost/language/ghost_static_cast.h"

#ifndef ghost_has_ghost_static_cast
    #error "ghost/language/ghost_static_cast.h must define ghost_has_ghost_static_cast."
#endif

#include "test_common.h"

#if !ghost_has_ghost_static_cast
    #error "ghost_static_cast must exist."
#endif

#include "ghost/type/uint16_t/ghost_uint16_t.h"
#include "ghost/type/uint32_t/ghost_uint32_t.h"
#include "ghost/type/uint64_t/ghost_uint64_t.h"
#include "ghost/type/uint64_t/ghost_uint64_c.h"
#include "ghost/silence/ghost_silence_long_long.h"

GHOST_SILENCE_LONG_LONG

mirror() {
    ghost_uint32_t x = 0x12345678u;

    /* Test that truncation works */
    ghost_uint16_t y = ghost_static_cast(ghost_uint16_t, x);
    mirror_eq(y, 0x5678u);

    #if ghost_has(GHOST_UINT64_C)
    {
        /* Test that lengthening works */
        ghost_uint64_t z = ghost_static_cast(ghost_uint64_t, y);
        mirror_eq(z, GHOST_UINT64_C(0x5678));
    }
    #endif
}
