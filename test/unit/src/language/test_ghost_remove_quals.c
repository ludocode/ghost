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

#include "ghost/language/ghost_remove_quals.h"

#ifndef ghost_has_ghost_remove_quals
    #error "ghost/language/ghost_remove_quals.h must define ghost_has_ghost_remove_quals."
#endif

#include "test_common.h"

/* TODO this is not working properly yet */
#if 0
#if ghost_has_ghost_remove_quals
#include "ghost/language/ghost_typeof.h"

mirror() {
    typedef ghost_remove_quals(const int) foo_t;
    foo_t x = 5;
    x = 7;
    mirror_eq(x, 7);

    #if ghost_has(ghost_typeof)
        typedef const int bar_t;
        typedef ghost_remove_quals(ghost_typeof(bar_t)) baz_t;

        baz_t y = 3;
        y = 2;
        mirror_eq(y, 2);
    #endif
}
#endif
#endif
