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

#include "ghost/language/ghost_weak.h"

#ifndef ghost_has_ghost_weak
    #error "ghost/language/ghost_weak.h must define ghost_has_ghost_weak."
#endif

#include "test_common.h"

#if ghost_has_ghost_weak

extern int test_ghost_weak_var;
int test_ghost_weak_fn(void);

/* These are defined in both test_ghost_weak.c and test_ghost_weak_2.c.
 * Duplicate symbol linker errors must not occur. */
ghost_weak int test_ghost_weak_var = 13;
ghost_weak int test_ghost_weak_fn(void) {
    return 13;
}

mirror() {
    mirror_eq(test_ghost_weak_var, test_ghost_weak_fn());
}

/* This symbol is not defined anywhere. Its address is null. (Apparently this
 * isn't allowed on macOS unless we pass `-undefined dynamic_lookup` to the
 * linker. I haven't bothered trying this; just disabling it.) */
#ifndef __APPLE__
ghost_weak extern int test_ghost_weak_missing_var;
mirror_1(name(MIRROR_NAME "$missing")) {
    mirror_eq(ghost_null, &test_ghost_weak_missing_var);
}
#endif

#endif
