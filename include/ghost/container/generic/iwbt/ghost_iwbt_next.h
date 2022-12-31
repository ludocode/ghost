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

#ifndef GHOST_IWBT_NEXT_H_INCLUDED
#define GHOST_IWBT_NEXT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 */
#endif

#ifndef ghost_has_ghost_iwbt_next
    #ifndef ghost_iwbt_next
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_first_in_subtree.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_sanity_check.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_null.h"
        GHOST_IMPL_FUNCTION_OPEN

        /* TODO remove tree parameter? or separate this out into always_inline function that ignores tree parameter */
        ghost_impl_function
        ghost_iwbt_node_t* ghost_iwbt_next(ghost_iwbt_t* tree, ghost_iwbt_node_t* node) GHOST_IMPL_DEF({
            ghost_discard(tree);
            ghost_iwbt_log(("next of %p\n", ghost_static_cast(void*, node)));

            /* If we have a right child, we return its leftmost leaf. */
            if (node->ghost_impl_v_last_child != ghost_null) {
                ghost_iwbt_log(("we have a right child, so we're finding its leftmost leaf\n"));
                return ghost_iwbt_node_first_in_subtree(node->ghost_impl_v_last_child);
            }

            /* Otherwise we walk up until we are the left child of a parent. */
            for (;;) {
                ghost_iwbt_node_t* parent = node->ghost_impl_v_parent;
                if (parent == ghost_null)
                    break;
                ghost_iwbt_log(("found parent %p\n", ghost_static_cast(void*, parent)));
                if (parent->ghost_impl_v_first_child == node) {
                    ghost_iwbt_log(("node is left child, so next is parent %p\n", ghost_static_cast(void*, parent)));
                    return parent;
                }
                node = parent;
            }

            /* If we haven't found anything, we are the last node in the list. */
            ghost_iwbt_log(("no more parents. no next.\n"));
            return ghost_null;
        })

        GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_ghost_iwbt_next 1
#endif

#endif
