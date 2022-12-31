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

#ifndef GHOST_MIN_I16_H_INCLUDED
#define GHOST_MIN_I16_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the lesser of the arguments.
 */
int16_t ghost_min_i16(int16_t left, int16_t right);
#endif

#ifndef ghost_has_ghost_min_i16
    #ifdef ghost_min_i16
        #define ghost_has_ghost_min_i16 1
    #endif
#endif

#ifndef ghost_has_ghost_min_i16
    #include "ghost/type/int16_t/ghost_int16_t.h"
    #if ghost_has_ghost_int16_t
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_int16_t ghost_min_i16(ghost_int16_t left, ghost_int16_t right) {
            return (left < right) ? left : right;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_min_i16 1
    #endif
#endif

#ifndef ghost_has_ghost_min_i16
    #define ghost_has_ghost_min_i16 0
#endif

#endif
