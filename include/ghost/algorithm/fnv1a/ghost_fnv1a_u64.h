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

#ifndef GHOST_FNV1A_U64_H_INCLUDED
#define GHOST_FNV1A_U64_H_INCLUDED

#include "ghost/ghost_core.h"

#ifndef ghost_has_ghost_fnv1a_u64
    #ifdef ghost_fnv1a_u64
        #define ghost_has_ghost_fnv1a_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_fnv1a_u64
    #include "ghost/type/uint64_t/ghost_uint64_t.h"
    #include "ghost/type/uint64_t/ghost_uint64_c.h"
    #if !ghost_has(ghost_uint64_t) || !ghost_has(GHOST_UINT64_C)
        #define ghost_has_ghost_fnv1a_u64 0
    #endif
#endif

#ifndef ghost_has_ghost_fnv1a_u64
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    ghost_uint64_t ghost_fnv1a_u64(const void* bytes, ghost_size_t length) GHOST_IMPL_DEF({
        ghost_uint64_t hash = GHOST_UINT64_C(14695981039346656037);
        ghost_size_t i;
        for (i = 0; i < length; ++i)
            hash = (hash ^ (ghost_static_cast(const unsigned char*, bytes)[i] & 0xFFU)) * GHOST_UINT64_C(1099511628211);
        return hash;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_fnv1a_u64 1
#endif

#endif
