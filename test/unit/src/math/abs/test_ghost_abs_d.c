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

#include "ghost/math/abs/ghost_abs_d.h"

#ifndef ghost_has_ghost_abs_d
    #error "ghost/math/abs/ghost_abs_d.h must define ghost_has_ghost_abs_d."
#endif

#include "test_common.h"

/* TODO make a variant test that includes <tgmath.h> to make sure it still
 * works. need a wrapper for <tgmath.h>, some compilers e.g. cproc cannot
 * include it */
#include "ghost/preprocessor/ghost_has_include.h"
#if ghost_has(ghost_has_include)
    #include "ghost/detect/ghost_cproc.h"
    #if __has_include(<tgmath.h>) && !GHOST_CPROC

        /* MSVC gives a deprecation warning, TODO wrap this header */
        #ifdef _MSC_VER
            #include "ghost/silence/ghost_silence_push_pop.h"
            #include "ghost/silence/ghost_silence_deprecated.h"
            GHOST_SILENCE_PUSH
            GHOST_SILENCE_DEPRECATED
        #endif

        #include <tgmath.h>

        #ifdef _MSC_VER
            GHOST_SILENCE_POP
        #endif
    #endif
#endif

#if ghost_has_ghost_abs_d
mirror() {
    mirror_eqe_d(ghost_abs_d(4.0), 4.0, 0.0);
    mirror_eqe_d(ghost_abs_d(-4.0), 4.0, 0.0);
    mirror_eqe_d(ghost_abs_d(0.0), 0.0, 0.0);
    mirror_eqe_d(ghost_abs_d(-0.1), 0.1, 0.0);
}
#endif
