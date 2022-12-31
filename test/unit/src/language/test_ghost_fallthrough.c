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

#include "ghost/language/ghost_fallthrough.h"

#ifndef ghost_has_ghost_fallthrough
    #error "ghost/language/ghost_fallthrough.h must define ghost_has_ghost_fallthrough."
#endif

#include "test_common.h"

#if !ghost_has_ghost_fallthrough
    #error "ghost_fallthrough must exist."
#endif

/* ghost_fallthrough falls back to nothing which means older compilers may
 * still warn. We may need to disable the below test on some old compilers. */

mirror() {
    int x = 2;
    switch (x) {
        case 1: mirror_check(1); ghost_fallthrough;
        case 2: mirror_check(1); ghost_fallthrough;
        case 3: mirror_check(1); ghost_fallthrough;
        case 4: mirror_check(1);
            break;
        default:
            mirror_error();
    }
}
