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

#ifndef GHOST_SSET_DESTROY_H_INCLUDED
#define GHOST_SSET_DESTROY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Destroys the string set, freeing all contained strings.
 */
void ghost_sset_destroy(ghost_sset_t* set);
#endif

#ifndef ghost_has_ghost_sset_destroy
    #ifdef ghost_sset_destroy
        #define ghost_has_ghost_sset_destroy 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_destroy
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_destroy 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_destroy
    #include "ghost/container/generic/iwbt/ghost_iwbt_root.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_node_first_child.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_node_last_child.h"
    #include "ghost/impl/container/common/sset/ghost_impl_sset_element_t.h"
    #include "ghost/language/ghost_null.h"
    #include "ghost/language/ghost_container_of.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/impl/ghost_impl_inline.h"
    GHOST_IMPL_FUNCTION_OPEN

    ghost_impl_function
    void ghost_impl_sset_element_free_recursive(ghost_iwbt_node_t* node) GHOST_IMPL_DEF({
        if (node == ghost_null)
            return;
        ghost_impl_sset_element_free_recursive(ghost_iwbt_node_first_child(node));
        ghost_impl_sset_element_free_recursive(ghost_iwbt_node_last_child(node));
        ghost_free(ghost_container_of(node, ghost_impl_sset_element_t, node));
    })

    ghost_impl_inline
    void ghost_sset_destroy(ghost_sset_t* set) {
        ghost_impl_sset_element_free_recursive(ghost_iwbt_root(&set->tree));
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_sset_destroy 1
#endif

#endif
