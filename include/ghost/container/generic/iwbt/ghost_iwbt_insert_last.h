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

#ifndef GHOST_IWBT_INSERT_LAST_H_INCLUDED
#define GHOST_IWBT_INSERT_LAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 */
#endif

#ifndef ghost_has_ghost_iwbt_insert_last
    #ifndef ghost_iwbt_insert_last
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_last_in_subtree.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_insert_into_empty_tree.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_insert_as_last_child.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_rebalance.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/language/ghost_null.h"
        GHOST_IMPL_FUNCTION_OPEN

        ghost_impl_function
        void ghost_iwbt_insert_last(ghost_iwbt_t* tree, ghost_iwbt_node_t* node) GHOST_IMPL_DEF({
            ghost_iwbt_log(("inserting %p last\n", ghost_static_cast(void*, node)));
            if (tree->ghost_impl_v_root == ghost_null) {
                ghost_impl_iwbt_insert_into_empty_tree(tree, node);
            } else {
                ghost_iwbt_node_t* reference = ghost_iwbt_node_last_in_subtree(tree->ghost_impl_v_root);
                ghost_impl_iwbt_insert_as_last_child(tree, reference, node);
                    ghost_iwbt_log(("%i\n",__LINE__));
                ghost_impl_iwbt_rebalance(tree, reference);
            }
        })

        GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_ghost_iwbt_insert_last 1
#endif

#endif
