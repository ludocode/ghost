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

#ifndef GHOST_IWBT_INSERT_AT_H_INCLUDED
#define GHOST_IWBT_INSERT_AT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Inserts a node at the given index.
 */
#endif

#ifndef ghost_has_ghost_iwbt_insert_at
    #ifndef ghost_iwbt_insert_at
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_count.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_at.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_insert_before.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_sanity_check.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_null.h"
        GHOST_IMPL_FUNCTION_OPEN

        ghost_impl_function
        void ghost_iwbt_insert_at(ghost_iwbt_t* ghost_impl_v_tree,
                ghost_size_t ghost_impl_v_index,
                ghost_iwbt_node_t* ghost_impl_v_node) GHOST_IMPL_DEF(
        {
            ghost_iwbt_log(("inserting %p at %zi\n", ghost_static_cast(void*, ghost_impl_v_node), ghost_impl_v_index));
            if (ghost_impl_v_tree->ghost_impl_v_root == ghost_null) {
                ghost_impl_iwbt_insert_into_empty_tree(ghost_impl_v_tree, ghost_impl_v_node);
            } else if (ghost_impl_v_index == ghost_iwbt_count(ghost_impl_v_tree)) {
                ghost_iwbt_insert_last(ghost_impl_v_tree, ghost_impl_v_node);
            } else {
                ghost_iwbt_insert_before(ghost_impl_v_tree, ghost_iwbt_at(ghost_impl_v_tree, ghost_impl_v_index), ghost_impl_v_node);
            }
        })

        GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_ghost_iwbt_insert_at 1
#endif

#endif
