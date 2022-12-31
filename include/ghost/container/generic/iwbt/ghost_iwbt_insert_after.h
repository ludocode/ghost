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

#ifndef GHOST_IWBT_INSERT_AFTER_H_INCLUDED
#define GHOST_IWBT_INSERT_AFTER_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Inserts a node after the given reference node.
 *
 * If reference_node is null, the node is inserted at the start of the list.
 *
 * TODO probably should have insert_after_opt() to allow reference node to be null
 */
#endif

#ifndef ghost_has_ghost_iwbt_insert_after
    #ifndef ghost_iwbt_insert_after
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_insert_first.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_first_in_subtree.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_insert_as_last_child.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_insert_as_first_child.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_sanity_check.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/language/ghost_null.h"
        GHOST_IMPL_FUNCTION_OPEN

        ghost_impl_function
        void ghost_iwbt_insert_after(ghost_iwbt_t* tree,
                ghost_iwbt_node_t* reference_node,
                ghost_iwbt_node_t* node_to_insert) GHOST_IMPL_DEF(
        {
            ghost_iwbt_log(("inserting %p after %p\n",
                    ghost_static_cast(void*, node_to_insert),
                    ghost_static_cast(void*, reference_node)));

            if (reference_node == ghost_null) {
                ghost_iwbt_insert_first(tree, node_to_insert);
                return;
            }

            if (reference_node->ghost_impl_v_last_child == ghost_null) {
                ghost_impl_iwbt_insert_as_last_child(tree, reference_node, node_to_insert);
            } else {
                reference_node = ghost_iwbt_node_first_in_subtree(reference_node->ghost_impl_v_last_child);
                ghost_impl_iwbt_insert_as_first_child(tree, reference_node, node_to_insert);
            }
        })

        GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_ghost_iwbt_insert_after 1
#endif

#endif
