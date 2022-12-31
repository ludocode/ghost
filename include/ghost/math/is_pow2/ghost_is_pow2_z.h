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

#ifndef GHOST_IS_POW2_Z_H_INCLUDED
#define GHOST_IS_POW2_Z_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns true if the given value is a power of two and false otherwise.
 */
bool ghost_is_pow2_z(ghost_size_t n);
#endif

#ifndef ghost_has_ghost_is_pow2_z
    #ifdef ghost_is_pow2_z
        #define ghost_has_ghost_is_pow2_z 1
    #endif
#endif

#ifndef ghost_has_ghost_is_pow2_z
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/type/bool/ghost_bool.h"
    #if ghost_has(ghost_size_t)
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_bool ghost_is_pow2_z(ghost_size_t n) {
            return n && !(n & (n - 1));
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_is_pow2_z 1
    #endif
#endif

#ifndef ghost_has_ghost_is_pow2_z
    #define ghost_has_ghost_is_pow2_z 0
#endif

#endif
