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

#ifndef GHOST_IMPL_IWBT_REBALANCE_H_INCLUDED
#define GHOST_IMPL_IWBT_REBALANCE_H_INCLUDED

#include "ghost/ghost_core.h"

#include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
#include "ghost/type/size_t/ghost_size_t.h"
#include "ghost/impl/ghost_impl_inline.h"
#include "ghost/language/ghost_null.h"
#include "ghost/debug/ghost_assert.h"
#include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_common.h"
#include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_weight.h"

GHOST_IMPL_FUNCTION_OPEN

ghost_impl_inline
void ghost_impl_iwbt_recalculate_size(ghost_iwbt_node_t* node) {
    ghost_assert(node != ghost_null, "");
    node->ghost_impl_v_weight =
        ghost_impl_iwbt_weight(node->ghost_impl_v_first_child) +
        ghost_impl_iwbt_weight(node->ghost_impl_v_last_child);
    ghost_assert(node->ghost_impl_v_weight > 1, "");
}

/*
 * Perform a left rotation on the given node.
 *
 * When run on node x, it performs the following transformation:
 *
 *           |                 |
 *           x                 y
 *          / \               / \
 *         1   y    ---->    x   3
 *            / \           / \
 *           2   3         1   2
 */
ghost_impl_function
void ghost_impl_iwbt_rotate_left(ghost_iwbt_t* tree, ghost_iwbt_node_t* x) GHOST_IMPL_DEF({
    ghost_iwbt_node_t* y = x->ghost_impl_v_last_child;
    ghost_iwbt_log(("rotating left %p\n", ghost_static_cast(void*, x)));
    ghost_assert(x != ghost_null, "");
    ghost_assert(y != ghost_null, "");

    /* swap child pointers */
    x->ghost_impl_v_last_child = y->ghost_impl_v_first_child;
    y->ghost_impl_v_first_child = x;
    if (x->ghost_impl_v_last_child != ghost_null)
        x->ghost_impl_v_last_child->ghost_impl_v_parent = x;

    /* fix parent references */
    if (x->ghost_impl_v_parent == ghost_null) {
        ghost_assert(tree->ghost_impl_v_root == x, "");
        tree->ghost_impl_v_root = y;
    } else {
        ghost_iwbt_node_t* parent = x->ghost_impl_v_parent;
        if (parent->ghost_impl_v_first_child == x) {
            parent->ghost_impl_v_first_child = y;
        } else {
            ghost_assert(parent->ghost_impl_v_last_child == x, "");
            parent->ghost_impl_v_last_child = y;
        }
    }
    y->ghost_impl_v_parent = x->ghost_impl_v_parent;
    x->ghost_impl_v_parent = y;

    /* fixup sizes. make sure we fix the original x first since it's now
     * the child of its original y child!
     * TODO there's probably a quicker way to do this */
    ghost_impl_iwbt_recalculate_size(x);
    ghost_impl_iwbt_recalculate_size(y);
})

/*
 * Perform a right rotation on the given node.
 *
 * When run on node x, it performs the following transformation:
 *
 *           |                 |
 *           x                 y
 *          / \               / \
 *         y   3   ---->     1   x
 *        / \                   / \
 *       1   2                 2   3
 */
ghost_impl_function
void ghost_impl_iwbt_rotate_right(ghost_iwbt_t* tree, ghost_iwbt_node_t* x) GHOST_IMPL_DEF({
    ghost_iwbt_node_t* y = x->ghost_impl_v_first_child;
    ghost_iwbt_log(("rotating right %p\n", ghost_static_cast(void*, x)));
    ghost_assert(x != ghost_null, "");
    ghost_assert(y != ghost_null, "");

    /* swap child pointers */
    x->ghost_impl_v_first_child = y->ghost_impl_v_last_child;
    y->ghost_impl_v_last_child = x;
    if (x->ghost_impl_v_first_child != ghost_null)
        x->ghost_impl_v_first_child->ghost_impl_v_parent = x;

    /* fix parent reference */
    if (x->ghost_impl_v_parent == ghost_null) {
        ghost_assert(tree->ghost_impl_v_root == x, "");
        tree->ghost_impl_v_root = y;
    } else {
        ghost_iwbt_node_t* parent = x->ghost_impl_v_parent;
        if (parent->ghost_impl_v_first_child == x) {
            parent->ghost_impl_v_first_child = y;
        } else {
            ghost_assert(parent->ghost_impl_v_last_child == x, "");
            parent->ghost_impl_v_last_child = y;
        }
    }
    y->ghost_impl_v_parent = x->ghost_impl_v_parent;
    x->ghost_impl_v_parent = y;

    /* fixup sizes. make sure we fix x first since it's now the child of y! */
    ghost_impl_iwbt_recalculate_size(x);
    ghost_impl_iwbt_recalculate_size(y);
})

/*
 * Rebalance the given node.
 */
ghost_impl_function
void ghost_impl_iwbt_rebalance(ghost_iwbt_t* tree, ghost_iwbt_node_t* node) GHOST_IMPL_DEF({
    ghost_iwbt_log(("pre-rebalance tree:\n"));
    /*ghost_impl_iwbt_print(tree); */
    ghost_iwbt_log(("rebalancing starting at %p\n", ghost_static_cast(void*, node)));
    while (node != ghost_null) {
        ghost_iwbt_node_t* left = node->ghost_impl_v_first_child;
        ghost_iwbt_node_t* right = node->ghost_impl_v_last_child;

        ghost_size_t left_weight = ghost_impl_iwbt_weight(left);
        ghost_size_t right_weight = ghost_impl_iwbt_weight(right);
        ghost_assert(node->ghost_impl_v_weight == left_weight + right_weight, "");

        if (left_weight * GHOST_IWBT_DELTA < right_weight) {
            ghost_assert(right != ghost_null, ""); /* right_weight is non-zero so it can't be null */
            {
                ghost_size_t right_left_weight = ghost_impl_iwbt_weight(right->ghost_impl_v_first_child);
                ghost_size_t right_right_weight = ghost_impl_iwbt_weight(right->ghost_impl_v_last_child);
                ghost_assert(right->ghost_impl_v_weight == right_left_weight + right_right_weight, "");

                if (right_left_weight >= GHOST_IWBT_GAMMA * right_right_weight) {
                    /* double rotation */
                    ghost_iwbt_log(("DOUBLE right then left\n"));
                    ghost_impl_iwbt_rotate_right(tree, right);
                }
                ghost_impl_iwbt_rotate_left(tree, node);
            }
            node = node->ghost_impl_v_parent->ghost_impl_v_parent;

        } else if (right_weight * GHOST_IWBT_DELTA < left_weight) {
            ghost_assert(left != ghost_null, ""); /* left_weight is non-zero so it can't be null */
            {
                ghost_size_t left_left_weight = ghost_impl_iwbt_weight(left->ghost_impl_v_first_child);
                ghost_size_t left_right_weight = ghost_impl_iwbt_weight(left->ghost_impl_v_last_child);
                ghost_assert(left->ghost_impl_v_weight == left_left_weight + left_right_weight, "");

                if (left_right_weight >= GHOST_IWBT_GAMMA * left_left_weight) {
                    /* double rotation */
                    ghost_iwbt_log(("DOUBLE left then right\n"));
                    ghost_impl_iwbt_rotate_left(tree, left);
                }
                ghost_impl_iwbt_rotate_right(tree, node);
            }

            node = node->ghost_impl_v_parent->ghost_impl_v_parent;

        } else {
            node = node->ghost_impl_v_parent;
        }
    }

    ghost_iwbt_log(("post-rebalance tree:\n"));
    /*ghost_impl_iwbt_print(tree); */
    ghost_impl_iwbt_sanity_check(tree);
})

GHOST_IMPL_FUNCTION_CLOSE

#endif
