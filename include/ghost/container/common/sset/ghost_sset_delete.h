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

#ifndef GHOST_SSET_DELETE_H_INCLUDED
#define GHOST_SSET_DELETE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Deletes the string set, freeing all contained strings and freeing the set.
 *
 * The set must have been allocated with ghost_sset_new(), not
 * ghost_sset_init().
 *
 * @see ghost_sset_new()
 */
void ghost_sset_delete(ghost_sset_t* set);
#endif

#ifndef ghost_has_ghost_sset_delete
    #ifdef ghost_sset_delete
        #define ghost_has_ghost_sset_delete 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_delete
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_delete 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_delete
    #include "ghost/container/common/sset/ghost_sset_destroy.h"
    #include "ghost/impl/ghost_impl_inline.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    void ghost_sset_delete(ghost_sset_t* ghost_impl_v_set) {
        ghost_sset_destroy(ghost_impl_v_set);
        ghost_free(ghost_impl_v_set);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_sset_delete 1
#endif

#endif
