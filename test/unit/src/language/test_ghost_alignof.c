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

#include "ghost/language/ghost_alignof.h"

#ifndef ghost_has_ghost_alignof
    #error "ghost/language/ghost_alignof.h must define ghost_has_ghost_alignof."
#endif

#include "test_common.h"

#if ghost_has_ghost_alignof
mirror() {
    mirror_eq(1, ghost_alignof(char));

    /* This isn't necessarily true on all platforms but we check it anyway
     * because it's probably true everywhere we care about and we want to get
     * some idea that alignof is working. */
    mirror_eq(sizeof(short), ghost_alignof(short));
    mirror_eq(sizeof(int), ghost_alignof(int));
}

/* Test extended alignment */
#include "ghost/language/ghost_alignat.h"
#if ghost_has_ghost_alignat
    #ifdef GHOST_IMPL_TEST_GHOST_ALIGNOF_EXTENDED
        #error
    #endif
    #ifdef __GNUC__
        /* On older GCC, the maximum alignment specification is platform
         * dependent, usually 16. We skip this test on these old compilers. */
        #include "ghost/detect/ghost_gcc.h"
        #if !GHOST_GCC || __GNUC__ >= 5
            #define GHOST_IMPL_TEST_GHOST_ALIGNOF_EXTENDED
        #endif
    #else
        #define GHOST_IMPL_TEST_GHOST_ALIGNOF_EXTENDED
    #endif

    #ifdef GHOST_IMPL_TEST_GHOST_ALIGNOF_EXTENDED
    struct foo {
        ghost_alignat(64) int x;
    };
    mirror() {
        mirror_eq(64, ghost_alignof(struct foo));
    }
    #endif
#endif
#endif
