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

#include "ghost/detect/ghost_musl_version.h"

#ifndef ghost_has_GHOST_MUSL_VERSION
    #error "ghost/detect/ghost_musl_version.h must define ghost_has_GHOST_MUSL_VERSION."
#endif

#include "test_common.h"

#if ghost_has(GHOST_MUSL_VERSION)

#if defined(__GLIBC__)
    #error
#endif

/* 1.2.0 made time_t 64-bit on all architectures */
#if GHOST_MUSL_VERSION >= 1002000
    #include <time.h>

    mirror() {
        mirror_eq(8, sizeof(time_t));
    }
#endif

/* 1.2.3 added qsort_r() */
#if GHOST_MUSL_VERSION >= 1002003
    #include <stdlib.h>
    #include "ghost/language/ghost_array_count.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/language/ghost_null.h"

    static int test_ghost_musl_version_compare(const void* a, const void* b, void* context) {
        mirror_eq(context, ghost_null);
        const char* ca = ghost_static_cast(const char*, a);
        const char* cb = ghost_static_cast(const char*, b);
        return ghost_compare_c(*ca, *cb);
    }

    mirror() {
        char l[] = {'a', 'b', 'c', 'd', 'e'};
        qsort_r(l, 1, ghost_array_count(l), test_ghost_musl_version_compare, ghost_null);
    }

#endif

#endif
