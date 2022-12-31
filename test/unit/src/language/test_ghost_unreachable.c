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

#include "ghost/language/ghost_unreachable.h"

#ifndef ghost_has_ghost_unreachable
    #error "ghost/language/ghost_unreachable.h must define ghost_has_ghost_unreachable."
#endif

#include "test_common.h"

#if !ghost_has_ghost_unreachable
    #error "ghost_unreachable must exist."
#endif

#include "mirror/mirror.h"
#include "ghost/language/ghost_discard.h"

extern int test_ghost_unreachable;
int test_ghost_unreachable = 2;

static int test_ghost_unreachable_provable(void) {
    if (test_ghost_unreachable == 1) {
        return 1;
    } else if (test_ghost_unreachable == 2) {
        return 2;
    } else if (test_ghost_unreachable == 3) {
        return 3;
    } else {
        return 0;
    }
    ghost_unreachable(0);
}

static int test_ghost_unreachable_provable_infinite_loop(void) {
    for (;;) {
    }
    ghost_unreachable(0);
}

static int test_ghost_unreachable_unprovable(void) {
    switch (test_ghost_unreachable) {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        default:
            break;
    }
    ghost_unreachable(0);
}

mirror() {
    mirror_eq(2, test_ghost_unreachable_provable());
    mirror_eq(2, test_ghost_unreachable_unprovable());

    ghost_discard(&test_ghost_unreachable_provable_infinite_loop);
}
