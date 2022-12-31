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

#include "ghost/preprocessor/ghost_not.h"

#ifndef ghost_has_GHOST_NOT
    #error "ghost/preprocessor/ghost_not.h must define ghost_has_GHOST_NOT."
#endif

#include "test_common.h"

#if ghost_has_GHOST_NOT
mirror() {
/* TODO why is this disabled? */
#if 1
    /* Only a 0 is converted to 1. */
    mirror_eq_i(1, GHOST_NOT(0));
    #define TEST_GHOST_NOT_0 0
    mirror_eq_i(1, GHOST_NOT(TEST_GHOST_NOT_0));

    /* Any other non-string text including blank becomes 0. */
    mirror_eq_i(0, GHOST_NOT(1));
    mirror_eq_i(0, GHOST_NOT());
    mirror_eq_i(0, GHOST_NOT(ghost_has_GHOST_NOT));
    mirror_eq_i(0, GHOST_NOT(ghost_impl_not_undefined_identifier));

    /* These cause compiler errors.
     *mirror_eq_i(0, GHOST_NOT(1, 2));
     *mirror_eq_i(0, GHOST_NOT("string")); */
#endif
}
#endif
