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

#ifndef GHOST_IMPL_IWBT_SANITY_CHECK_H_INCLUDED
#define GHOST_IMPL_IWBT_SANITY_CHECK_H_INCLUDED

#include "ghost/ghost_core.h"

#include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_common.h"
#include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
#include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
#include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_common.h"
#include "ghost/type/size_t/ghost_size_t.h"
#include "ghost/debug/ghost_assert.h"
#include "ghost/impl/ghost_impl_inline.h"
#include "ghost/impl/ghost_impl_function.h"
#include "ghost/language/ghost_null.h"
#include "ghost/language/ghost_discard.h"

GHOST_IMPL_FUNCTION_OPEN

#if GHOST_IWBT_DEBUG
ghost_impl_function
void ghost_impl_iwbt_sanity_check_node(ghost_iwbt_t* tree, ghost_iwbt_node_t* node) GHOST_IMPL_DEF({
    ghost_size_t left_weight = ghost_impl_iwbt_weight(node->ghost_impl_v_first_child);
    ghost_size_t right_weight = ghost_impl_iwbt_weight(node->ghost_impl_v_last_child);

    /* Make sure the weight is correct and the tree is balanced */
    ghost_assert(node->ghost_impl_v_weight > 1, "");
    ghost_assert(node->ghost_impl_v_weight == left_weight + right_weight, "");
    ghost_assert(left_weight * GHOST_IWBT_DELTA >= right_weight, "");
    ghost_assert(right_weight * GHOST_IWBT_DELTA >= left_weight, "");

    /* Check left child */
    if (node->ghost_impl_v_first_child != ghost_null) {
        ghost_assert(node->ghost_impl_v_first_child->ghost_impl_v_parent == node, "");
        ghost_impl_iwbt_sanity_check_node(tree, node->ghost_impl_v_first_child);
    }

    /* Check right child */
    if (node->ghost_impl_v_last_child != ghost_null) {
        ghost_assert(node->ghost_impl_v_last_child->ghost_impl_v_parent == node, "");
        ghost_impl_iwbt_sanity_check_node(tree, node->ghost_impl_v_last_child);
    }
})
#endif

/*
 * Sanity check recurses over the entire tree, checking every node to make
 * sure its weight is correct, its nodes are consistent and it is properly
 * balanced.
 */
ghost_impl_inline
void ghost_impl_iwbt_sanity_check(ghost_iwbt_t* tree) {
    ghost_discard(tree);
    #if GHOST_IWBT_DEBUG
    ghost_assert(tree != ghost_null, "");
    ghost_iwbt_node_t* node = tree->ghost_impl_v_root;
    if (node == ghost_null)
        return;
    ghost_assert(node->ghost_impl_v_parent == ghost_null, "");
    ghost_impl_iwbt_sanity_check_node(tree, node);
    /*ghost_iwbt_log(("sanity check PASS\n")); */
    #endif
}

GHOST_IMPL_FUNCTION_CLOSE

#endif
