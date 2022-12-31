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

#include "ghost/language/ghost_alignas.h"

#ifndef ghost_has_ghost_alignas
    #error "ghost/language/ghost_alignas.h must define ghost_has_ghost_alignas."
#endif

#include "test_common.h"

/* Test based on test_ghost_alignat.c */
#if ghost_has_ghost_alignas
#include "ghost/language/ghost_alignat.h"
#if ghost_has_ghost_alignat
#include "ghost/language/ghost_reinterpret_cast.h"
#include "ghost/language/ghost_discard.h"
#include "ghost/type/uintptr_t/ghost_uintptr_t.h"

/* Old versions of GCC (<4.7 or so) only support alignment up to 16 bytes. We
 * test with 16 byte alignment and use padding in between two structs to ensure
 * at least one of them needs to be shifted to the proper alignment. */

struct foo {
    ghost_alignat(16) int x;
};

struct bar {
    ghost_alignas(struct foo) int x;
};

mirror() {
    struct bar a;
    int padding = 0;
    struct bar b;
    mirror_eq_up(0, ghost_reinterpret_cast(ghost_uintptr_t, &a) & (16u - 1u));
    ghost_discard(padding);
    mirror_eq_up(0, ghost_reinterpret_cast(ghost_uintptr_t, &b) & (16u - 1u));
}
#endif
#endif
