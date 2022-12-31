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

#ifndef GHOST_SSET_IT_LENGTH_H_INCLUDED
#define GHOST_SSET_IT_LENGTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the length of string pointed to by the given string set iterator.
 *
 * @see ghost_sset_it_t
 */
size_t ghost_sset_it_length(ghost_sset_it_t it);
#endif

#ifndef ghost_has_ghost_sset_it_length
    #ifdef ghost_sset_it_length
        #define ghost_has_ghost_sset_it_length 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_sset_it_length
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_it_length 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_it_length
    #include "ghost/container/common/sset/ghost_sset_it_t.h"
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_size_t ghost_sset_it_length(ghost_sset_it_t it) {
        return it->length;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_sset_it_length 1
#endif

#endif
