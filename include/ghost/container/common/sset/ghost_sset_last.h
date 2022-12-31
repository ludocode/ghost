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

#ifndef GHOST_SSET_LAST_H_INCLUDED
#define GHOST_SSET_LAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns an iterator to the last element in the set.
 *
 * See ghost_sset_it_t for example usage.
 *
 * @see ghost_sset_it_t
 */
ghost_sset_it_t ghost_sset_last(ghost_sset_t* set);
#endif

#ifndef ghost_has_ghost_sset_last
    #ifdef ghost_sset_last
        #define ghost_has_ghost_sset_last 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_last
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_last 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_last
    #include "ghost/container/common/sset/ghost_sset_it_t.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_last.h"
    #include "ghost/impl/container/common/sset/ghost_impl_sset_element_t.h"
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/language/ghost_container_of.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_sset_it_t ghost_sset_last(ghost_sset_t* ghost_impl_v_set) {
        ghost_iwbt_node_t* ghost_impl_v_last = ghost_iwbt_last(&ghost_impl_v_set->tree);
        return ghost_container_of(ghost_impl_v_last, ghost_impl_sset_element_t, node);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_sset_last 1
#endif

#endif
