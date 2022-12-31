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

#ifndef GHOST_STORE_U8_H_INCLUDED
#define GHOST_STORE_U8_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Stores a uint8_t at the given address.
 */
void ghost_store_u8(const void* p, uint8_t v);
#endif

#ifndef ghost_has_ghost_store_u8
    #ifdef ghost_store_u8
        #define ghost_has_ghost_store_u8 1
    #endif
#endif

#ifndef ghost_has_ghost_store_u8
    #include "ghost/impl/ghost_impl_always_inline.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/type/uint8_t/ghost_uint8_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    void ghost_store_u8(void* p, ghost_uint8_t v) {
        *ghost_static_cast(ghost_uint8_t*, p) = v;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_store_u8 1
#endif

#endif
