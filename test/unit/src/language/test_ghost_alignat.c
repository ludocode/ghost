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

#include "ghost/language/ghost_alignat.h"

#ifndef ghost_has_ghost_alignat
    #error "ghost/language/ghost_alignat.h must define ghost_has_ghost_alignat."
#endif

#include "test_common.h"

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

/* TODO suffix is not implemented yet */
mirror_0(/*suffix("stack")*/) {
    struct foo a;
    struct foo b;
    char padding = 0;
    mirror_eq(0, ghost_reinterpret_cast(ghost_uintptr_t, &a) & (16u - 1u));
    ghost_discard(padding);
    mirror_eq(0, ghost_reinterpret_cast(ghost_uintptr_t, &b) & (16u - 1u));
}

struct bar {
    struct foo f1;
    char c;
    struct foo f2;
};

mirror_0(/*suffix("struct")*/) {
    struct bar b;
    mirror_eq(0, ghost_reinterpret_cast(ghost_uintptr_t, &b.f1) & (16u - 1u));
    mirror_eq(0, ghost_reinterpret_cast(ghost_uintptr_t, &b.f2) & (16u - 1u));
}
#endif
