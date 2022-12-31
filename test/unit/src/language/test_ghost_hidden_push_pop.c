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

#include "ghost/language/ghost_hidden_push_pop.h"

#ifndef ghost_has_GHOST_HIDDEN_PUSH
    #error "ghost/language/ghost_hidden_push_pop.h must define ghost_has_GHOST_HIDDEN_PUSH."
#endif
#ifndef ghost_has_GHOST_HIDDEN_POP
    #error "ghost/language/ghost_hidden_push_pop.h must define ghost_has_GHOST_HIDDEN_POP."
#endif

#include "test_common.h"

#if !ghost_has_GHOST_HIDDEN_PUSH
    #error "GHOST_HIDDEN_PUSH must exist."
#endif

#if !ghost_has_GHOST_HIDDEN_POP
    #error "GHOST_HIDDEN_POP must exist."
#endif

/* We just test that we can declare a function with this. */

GHOST_HIDDEN_PUSH
int test_GHOST_HIDDEN_PUSH_pop_fn(void);
int test_GHOST_HIDDEN_PUSH_pop_fn(void) {
    return 11;
}
GHOST_HIDDEN_POP

mirror() {
    mirror_eq(11, test_GHOST_HIDDEN_PUSH_pop_fn());
}
