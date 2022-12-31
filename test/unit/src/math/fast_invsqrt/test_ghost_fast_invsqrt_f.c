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

#include "ghost/math/fast_invsqrt/ghost_fast_invsqrt_f.h"

#if ghost_has_ghost_fast_invsqrt_f
#include "mirror/mirror.h"

#include "ghost/math/max/ghost_max_f.h"
#include "ghost/math/abs/ghost_abs_f.h"
#include "ghost/math/sqrt/ghost_sqrt_f.h"

mirror() {
    const float max_error = 0.0007F;

    /* test a bunch of arbitrary values */
    float f;
    for (f = 0.01F; f < 100.F; f *= 1.00137F) {
        /*
        printf("checking %08f: approx %08f actual %08f err %08f\n",
                f,
                ghost_fast_invsqrt_f(f),
                1.0F / ghost_sqrt_f(f),
                ghost_abs_f((ghost_fast_invsqrt_f(f) - 1.0F / ghost_sqrt_f(f)) /
                    ghost_max_f(ghost_fast_invsqrt_f(f), 1.0F / ghost_sqrt_f(f))));
                    */
        mirror_eqe_f(ghost_fast_invsqrt_f(f), 1.0F / ghost_sqrt_f(f), max_error);
    }
}
#endif
