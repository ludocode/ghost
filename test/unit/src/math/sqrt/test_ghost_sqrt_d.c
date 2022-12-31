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

#include "ghost/math/sqrt/ghost_sqrt_d.h"

#ifndef ghost_has_ghost_sqrt_d
    #error "ghost/math/sqrt/ghost_sqrt_d.h must define ghost_has_ghost_sqrt_d."
#endif

#include "test_common.h"

#if ghost_has_ghost_sqrt_d
mirror() {
    /* TODO make mirror_eq_d() do this, compare with tiny epsilon.
     * mirror_eqb_d() should be bitwise. */
    mirror_eqe_d(ghost_sqrt_d(4.0), 2.0, 0.0);
    mirror_eqe_d(ghost_sqrt_d(2.0), 1.4142135623730950488, 0.0);
    mirror_eqe_d(ghost_sqrt_d(1.0), 1.0, 0.0);
}
#endif
