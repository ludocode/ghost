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

#include "ghost/language/ghost_auto_cast.h"

#ifndef ghost_has_ghost_auto_cast
    #error "ghost/language/ghost_auto_cast.h must define ghost_has_ghost_auto_cast."
#endif
#if !ghost_has_ghost_auto_cast
#error "ghost_auto_cast must exist."
#endif

#include "test_common.h"

#include "ghost/language/ghost_null.h"

#include "ghost/silence/ghost_silence_cxx_compat.h"
#include "ghost/silence/ghost_silence_push_pop_opt.h"
GHOST_SILENCE_PUSH_OPT
GHOST_SILENCE_CXX_COMPAT

mirror_1(it("should implicitly cast to typed pointer")) {
    int a = 7;
    int* b = &a;
    void* c = b;
    int* d = ghost_auto_cast(c);
    mirror_eq_i(*d, 7);
}

mirror_1(it("should be comparable to nullptr")) {
    int x;
    void* p = ghost_null;
    mirror_check(p == ghost_null);
    mirror_check(ghost_null == p);
    p = &x;
    mirror_check(p != ghost_null);
    mirror_check(ghost_null != p);
}

/* This should cause a compiler error in C11 and a compiler or linker error in
 * C++. ghost_auto_cast() can only be used on void*. */
#if 0
mirror() {
    int a = 7;
    int* b = &a;
    int* c = ghost_auto_cast(b);
    mirror_eq_i(*c, 7);
}
#endif

GHOST_SILENCE_POP_OPT
