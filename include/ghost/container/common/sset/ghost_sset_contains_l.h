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

#ifndef GHOST_SSET_CONTAINS_L_H_INCLUDED
#define GHOST_SSET_CONTAINS_L_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns true if the string set contains the given string with the given
 * length.
 *
 * @return True if the set contains the string, false otherwise.
 */
bool ghost_sset_contains_l(ghost_sset_t* set, const char* string, size_t length);
#endif

#ifndef ghost_has_ghost_sset_init
    #ifdef ghost_sset_init
        #define ghost_has_ghost_sset_init 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_contains_l
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_contains_l 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_contains_l
    #include "ghost/container/common/sset/ghost_sset_find_l.h"
    #include "ghost/type/bool/ghost_bool.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/language/ghost_null.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_bool ghost_sset_contains_l(ghost_sset_t* set, const char* string, ghost_size_t length) {
        return ghost_null != ghost_sset_find_l(set, string, length);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_sset_contains_l 1
#endif

#endif
