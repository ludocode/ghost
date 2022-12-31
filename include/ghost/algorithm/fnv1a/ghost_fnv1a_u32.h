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

#ifndef GHOST_FNV1A_U32_H_INCLUDED
#define GHOST_FNV1A_U32_H_INCLUDED

#include "ghost/ghost_core.h"

#ifndef ghost_has_ghost_fnv1a_u32
    #ifdef ghost_fnv1a_u32
        #define ghost_has_ghost_fnv1a_u32 1
    #endif
#endif

#ifndef ghost_has_ghost_fnv1a_u32
    #include "ghost/type/uint32_t/ghost_uint32_t.h"
    #include "ghost/type/uint32_t/ghost_uint32_c.h"
    #if !ghost_has(ghost_uint32_t) || !ghost_has(GHOST_UINT32_C)
        #define ghost_has_ghost_fnv1a_u32 0
    #endif
#endif

#ifndef ghost_has_ghost_fnv1a_u32
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    ghost_uint32_t ghost_fnv1a_u32(const void* bytes, ghost_size_t length) GHOST_IMPL_DEF({
        ghost_uint32_t hash = GHOST_UINT32_C(2166136261);
        ghost_size_t i;
        for (i = 0; i < length; ++i)
            hash = (hash ^ (ghost_static_cast(const unsigned char*, bytes)[i] & 0xFFU)) * GHOST_UINT32_C(16777619);
        return hash;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_fnv1a_u32 1
#endif

#endif
