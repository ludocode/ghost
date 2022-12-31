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

#ifndef GHOST_LOAD_I8_H_INCLUDED
#define GHOST_LOAD_I8_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Loads the int8_t at the given address.
 */
int8_t ghost_load_i8(const void* p);
#endif

#ifndef ghost_has_ghost_load_i8
    #ifdef ghost_load_i8
        #define ghost_has_ghost_load_i8 1
    #endif
#endif

#ifndef ghost_has_ghost_load_i8
    #include "ghost/impl/ghost_impl_always_inline.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/type/int8_t/ghost_int8_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    ghost_int8_t ghost_load_i8(const void* p) {
        return *ghost_static_cast(const ghost_int8_t*, p);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_load_i8 1
#endif

#endif
