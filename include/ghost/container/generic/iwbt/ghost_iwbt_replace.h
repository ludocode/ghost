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

#ifndef GHOST_IWBT_REPLACE_H_INCLUDED
#define GHOST_IWBT_REPLACE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Replace an existing node with a new one.
 *
 * The new_node must not already be in the tree.
 */
void ghost_iwbt_replace(ghost_iwbt_t* tree,
        ghost_iwbt_node_t* old_node, ghost_iwbt_node_t* new_node);
#endif

#ifndef ghost_has_ghost_iwbt_replace
    #ifndef ghost_iwbt_replace
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_sanity_check.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/language/ghost_null.h"
        GHOST_IMPL_FUNCTION_OPEN

        ghost_impl_function
        void ghost_iwbt_replace(ghost_iwbt_t* ghost_impl_v_tree,
                ghost_iwbt_node_t* ghost_impl_v_old_node,
                ghost_iwbt_node_t* ghost_impl_v_new_node) GHOST_IMPL_DEF(
        {
            ghost_iwbt_node_t* parent;

            ghost_iwbt_log(("replacing %p with %p\n",
                    ghost_static_cast(void*, ghost_impl_v_old_node),
                    ghost_static_cast(void*, ghost_impl_v_new_node)));
            ghost_impl_v_new_node->ghost_impl_v_parent = ghost_impl_v_old_node->ghost_impl_v_parent;
            ghost_impl_v_new_node->ghost_impl_v_first_child = ghost_impl_v_old_node->ghost_impl_v_first_child;
            ghost_impl_v_new_node->ghost_impl_v_last_child = ghost_impl_v_old_node->ghost_impl_v_last_child;
            ghost_impl_v_new_node->ghost_impl_v_weight = ghost_impl_v_old_node->ghost_impl_v_weight;

            parent = ghost_impl_v_new_node->ghost_impl_v_parent;
            if (parent == ghost_null) {
                ghost_assert(ghost_impl_v_tree->ghost_impl_v_root == ghost_impl_v_old_node, "");
                ghost_impl_v_tree->ghost_impl_v_root = ghost_impl_v_new_node;
            } else if (parent->ghost_impl_v_first_child == ghost_impl_v_old_node) {
                parent->ghost_impl_v_first_child = ghost_impl_v_new_node;
            } else {
                ghost_assert(parent->ghost_impl_v_last_child == ghost_impl_v_old_node, "");
                parent->ghost_impl_v_last_child = ghost_impl_v_new_node;
            }

            if (ghost_impl_v_new_node->ghost_impl_v_first_child != ghost_null)
                ghost_impl_v_new_node->ghost_impl_v_first_child->ghost_impl_v_parent = ghost_impl_v_new_node;
            if (ghost_impl_v_new_node->ghost_impl_v_last_child != ghost_null)
                ghost_impl_v_new_node->ghost_impl_v_last_child->ghost_impl_v_parent = ghost_impl_v_new_node;
        })

        GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_ghost_iwbt_replace 1
#endif

#endif
