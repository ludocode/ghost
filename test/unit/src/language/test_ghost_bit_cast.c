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

#include "ghost/language/ghost_bit_cast.h"

#ifndef ghost_has_ghost_bit_cast
    #error "ghost/language/ghost_bit_cast.h must define ghost_has_ghost_bit_cast."
#endif

#include "test_common.h"

#if !ghost_has_ghost_bit_cast
    #error "ghost_bit_cast must exist."
#endif

#include "ghost/type/float32_t/ghost_float32_t.h"
#include "ghost/type/int32_t/ghost_int32_t.h"

#if ghost_has(ghost_float32_t)
mirror() {
    ghost_int32_t x;
    ghost_float32_t y;
    ghost_int32_t z;
    x = 3;
    y = ghost_bit_cast(ghost_float32_t, ghost_int32_t, x);
    z = ghost_bit_cast(ghost_int32_t, ghost_float32_t, y);
    mirror_eq(z, 3);
    mirror_eq(0, memcmp(&x, &y, sizeof(x)));
    mirror_eq(0, memcmp(&y, &z, sizeof(y)));
}
#endif
