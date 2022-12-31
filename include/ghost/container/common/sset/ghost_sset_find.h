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

#ifndef GHOST_SSET_FIND_H_INCLUDED
#define GHOST_SSET_FIND_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns an iterator to the given null-terminated string in the set, or null
 * if the string is not in the set.
 *
 * See ghost_sset_it_t for example usage.
 *
 * @see ghost_sset_it_t
 */
ghost_sset_it_t ghost_sset_find(ghost_sset_t* set, const char* cstring);
#endif

#ifndef ghost_has_ghost_sset_find
    #ifdef ghost_sset_find
        #define ghost_has_ghost_sset_find 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_find
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_find 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_find
    #include "ghost/container/common/sset/ghost_sset_find_l.h"
    #include "ghost/string/ghost_strlen.h"
    #include "ghost/impl/ghost_impl_inline.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_sset_it_t ghost_sset_find(ghost_sset_t* ghost_impl_v_set, const char* cstring) {
        return ghost_sset_find_l(ghost_impl_v_set, cstring, ghost_strlen(cstring));
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_sset_find 1
#endif

#endif
