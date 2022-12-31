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

#ifndef GHOST_IS_ALIGNED_H_INCLUDED
#define GHOST_IS_ALIGNED_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * bool ghost_is_aligned(p, n)
 *
 * Returns true if the given pointer is aligned to the given power-of-two
 * numerical alignment.
 *
 * The given alignment must be a power of two.
 */
#endif

/* This is technically more of a math function than an alignment function but
 * we keep it here in language/ with the align stuff anyway. */

#ifndef ghost_has_ghost_is_aligned
    #ifdef ghost_is_aligned
        #define ghost_has_ghost_is_aligned 1
    #endif
#endif

#ifndef ghost_has_ghost_is_aligned
    #include "ghost/debug/ghost_assert.h"
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/math/is_pow2/ghost_is_pow2_z.h"
    #include "ghost/language/ghost_reinterpret_cast.h"
    #include "ghost/type/bool/ghost_bool.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/type/uintptr_t/ghost_uintptr_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_bool ghost_is_aligned(void* ghost_p, ghost_size_t ghost_required_align) {
        ghost_uintptr_t ghost_u;
        ghost_assert(ghost_is_pow2_z(ghost_required_align), "alignment is not a power of two!");
        ghost_u = ghost_reinterpret_cast(ghost_uintptr_t, ghost_p);
        return ghost_u == (ghost_u & ~ghost_required_align);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_is_aligned 1
#endif

#endif
