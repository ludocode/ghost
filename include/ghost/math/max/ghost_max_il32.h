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

#ifndef GHOST_MAX_IL32_H_INCLUDED
#define GHOST_MAX_IL32_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the greater of the arguments.
 */
int_least32_t ghost_max_il32(int_least32_t left, int_least32_t right);
#endif

#ifndef ghost_has_ghost_max_il32
    #ifdef ghost_max_il32
        #define ghost_has_ghost_max_il32 1
    #endif
#endif

#ifndef ghost_has_ghost_max_il32
    #include "ghost/type/int_least32_t/ghost_int_least32_t.h"
    #if ghost_has_ghost_int_least32_t
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_int_least32_t ghost_max_il32(ghost_int_least32_t left, ghost_int_least32_t right) {
            return (left > right) ? left : right;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_max_il32 1
    #endif
#endif

#ifndef ghost_has_ghost_max_il32
    #define ghost_has_ghost_max_il32 0
#endif

#endif
