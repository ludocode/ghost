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

#ifndef GHOST_IWBT_NODE_LAST_IN_SUBTREE_H_INCLUDED
#define GHOST_IWBT_NODE_LAST_IN_SUBTREE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the last node among the subtree rooted at this node.
 *
 * In other words, it follows last children recursively starting at the given
 * node until it finds a node with no last child.
 *
 * This cannot be called with null. It never returns null.
 */
ghost_iwbt_node_t* ghost_iwbt_node_last_in_subtree(ghost_iwbt_node_t* node);
#endif

#ifndef ghost_has_ghost_iwbt_node_last_in_subtree
    #ifndef ghost_iwbt_node_last_in_subtree
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_sanity_check.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_null.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_iwbt_node_t* ghost_iwbt_node_last_in_subtree(ghost_iwbt_node_t* ghost_impl_v_node) {
            ghost_assert(ghost_impl_v_node != ghost_null, "");
            for (;;) {
                ghost_iwbt_node_t* next = ghost_impl_v_node->ghost_impl_v_last_child;
                if (next == ghost_null)
                    break;
                ghost_impl_v_node = next;
            }
            return ghost_impl_v_node;
        }
        GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_ghost_iwbt_node_last_in_subtree 1
#endif

#endif
