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

#ifndef GHOST_SSET_IT_STRING_H_INCLUDED
#define GHOST_SSET_IT_STRING_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the string pointed to by the given string set iterator.
 *
 * The string is null-terminated. You can also get its length with
 * ghost_sset_it_length().
 *
 * @see ghost_sset_it_t
 */
const char* ghost_sset_it_string(ghost_sset_it_t it);
#endif

#ifndef ghost_has_ghost_sset_it_string
    #ifdef ghost_sset_it_string
        #define ghost_has_ghost_sset_it_string 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_sset_it_string
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_it_string 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_it_string
    #include "ghost/container/common/sset/ghost_sset_it_t.h"
    #include "ghost/impl/ghost_impl_inline.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    const char* ghost_sset_it_string(ghost_sset_it_t it) {
        /*
         * Note: If this is causing static analysis warnings due to the use of
         * struct hack, we could do the calculation manually, i.e.
         *
         *     (char*)it + ghost_struct_hack_sizeof(it, cstring)
         *
         * Maybe we'll need to add a ghost_struct_hack_access() macro or
         * something to work around this.
         *
         * TODO use ghost_struct_hack_access() macro?
         */
        return it->cstring;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_sset_it_string 1
#endif

#endif
