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

#include "ghost/language/ghost_discard_force.h"

#ifndef ghost_has_ghost_discard_force
    #error "ghost/language/ghost_discard_force.h must define ghost_has_ghost_discard_force."
#endif

#include "test_common.h"

#if !ghost_has_ghost_discard_force
    #error "ghost_discard_force must exist."
#endif

/* Unit tests are templated to share with ghost_discard().
 * ghost_discard_force() should be able to do everything ghost_discard() does. */
#define TEST_GHOST_DISCARD ghost_discard_force
#include "test_ghost_discard.t.h"

/* ghost_discard_force() should additionally be able to discard warn_unused_result. */

#ifdef __GNUC__
__attribute__((__warn_unused_result__)) static int bar(void) {
    return 2;
}

mirror_1(name(MIRROR_NAME "$warn_unused_result")) {
    int y;
    ghost_discard_force(bar());
    y = bar();
    ghost_discard_force(y);
}
#endif
