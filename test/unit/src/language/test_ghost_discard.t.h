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

#ifndef TEST_GHOST_DISCARD
    #error "This is a template, TEST_GHOST_DISCARD should be ghost_discard() or ghost_discard_force()"
#endif

/* Test some basic discards */

mirror() {
    TEST_GHOST_DISCARD(0);

    #define TEST_GHOST_DISCARD_IMPL(x, y) (TEST_GHOST_DISCARD(x), (y))
    mirror_eq(8, TEST_GHOST_DISCARD_IMPL(7, 8));
}


/* Make sure we can discard a struct */

typedef struct {
    int x, y;
} point_t;

mirror_1(name(MIRROR_NAME "$struct")) {
    point_t p = {1, 2};
    TEST_GHOST_DISCARD(p);
}


/* Test with a nodiscard function */

#include "ghost/language/ghost_nodiscard.h"

ghost_nodiscard static int foo(void) {
    return 4;
}

mirror_1(name(MIRROR_NAME "$nodiscard")) {
    int x;
    TEST_GHOST_DISCARD(foo());
    x = foo();
    TEST_GHOST_DISCARD(x);
}
