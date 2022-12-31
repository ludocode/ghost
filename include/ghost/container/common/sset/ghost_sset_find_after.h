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

#ifndef GHOST_SSET_FIND_AFTER_H_INCLUDED
#define GHOST_SSET_FIND_AFTER_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns an iterator to the given null-terminated string in the set, or if it
 * is not the set, returns an iterator to the string immediately following it
 * if it were in the set.
 *
 * @see ghost_sset_it_t
 */
ghost_sset_it_t ghost_sset_find_after(ghost_sset_t* set, const char* cstring, bool* /*nullable*/ equal);
#endif

#ifndef ghost_has_ghost_sset_find_after
    #ifdef ghost_sset_find_after
        #define ghost_has_ghost_sset_find_after 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_find_after
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_find_after 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_find_after
    #include "ghost/container/common/sset/ghost_sset_find_after_l.h"
    #include "ghost/string/ghost_strlen.h"
    #include "ghost/type/bool/ghost_bool.h"
    #include "ghost/impl/ghost_impl_inline.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_sset_it_t ghost_sset_find_after(ghost_sset_t* ghost_impl_v_set, const char* cstring, ghost_bool* equal) {
        return ghost_sset_find_after_l(ghost_impl_v_set, cstring, ghost_strlen(cstring), equal);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_sset_find_after 1
#endif

#endif
