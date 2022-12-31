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

#ifndef GHOST_IWBT_INDEX_H_INCLUDED
#define GHOST_IWBT_INDEX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Gets the index of the given node.
 *
 * TODO should this accept null? probably not, maybe a separate rank function
 * should accept null? or that's way too confusing, probably it should be
 * index_opt() or something
 */
#endif

#ifndef ghost_has_ghost_iwbt_index
    #ifndef ghost_iwbt_index
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_sanity_check.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/language/ghost_null.h"
        GHOST_IMPL_FUNCTION_OPEN

        ghost_impl_function
        ghost_size_t ghost_iwbt_index(ghost_iwbt_t* tree, ghost_iwbt_node_t* node) GHOST_IMPL_DEF({
            ghost_size_t i;
            ghost_iwbt_node_t* parent;

            ghost_assert(tree != ghost_null, "");
            ghost_assert(node != ghost_null, "");
            ghost_discard(tree);

            i = 0;
            if (node->ghost_impl_v_first_child)
                i += node->ghost_impl_v_first_child->ghost_impl_v_weight - 1;

            parent = node->ghost_impl_v_parent;
            while (parent) {
                if (node == parent->ghost_impl_v_last_child) {
                    i += 1;
                    if (parent->ghost_impl_v_first_child != ghost_null)
                        i += parent->ghost_impl_v_first_child->ghost_impl_v_weight - 1;
                }
                node = parent;
                parent = node->ghost_impl_v_parent;
            }

            return i;
        })

        GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_ghost_iwbt_index 1
#endif

#endif
