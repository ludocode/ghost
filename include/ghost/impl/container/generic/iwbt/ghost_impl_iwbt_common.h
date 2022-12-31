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

#ifndef GHOST_IMPL_IWBT_COMMON_H_INCLUDED
#define GHOST_IMPL_IWBT_COMMON_H_INCLUDED

#include "ghost/ghost_core.h"

#include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
#if ghost_has(ghost_iwbt_t)

/*
 * The implementation of the tree is described in "Balancing weight-balanced
 * trees" by Yoichi Hirai, 2011:
 *
 *     https://yoichihirai.com/bst.pdf
 *
 * We use the original balance method (where weight == size + 1), not the
 * variant balance method. We use parameters (3,2) which are the only integer
 * parameters that correctly preserve balance constraints in the original
 * balance method according to the paper.
 */

/* TODO these constants need to be GHOST_IMPL */

/* The tree is unbalanced at a if `a > b*delta` for any siblings a and b. */
#define GHOST_IWBT_DELTA 3

/* We do a double rotation if `aa > ab * delta` for the children of any
 * unbalanced node a (where aa is the interior node, i.e. the opposite side of
 * a in its parent), otherwise we do a single rotation. */
#define GHOST_IWBT_GAMMA 2

#ifndef GHOST_IWBT_DEBUG
    #define GHOST_IWBT_DEBUG 0
#endif

#if GHOST_IWBT_DEBUG
    #include <stdio.h>
    #define ghost_iwbt_log(x) printf x
#else
    #define ghost_iwbt_log(x) /*nothing*/
#endif

#include "ghost/impl/ghost_impl_inline.h"

GHOST_IMPL_FUNCTION_OPEN

#if GHOST_IWBT_DEBUG
ghost_impl_inline
void ghost_impl_iwbt_print_node(ghost_iwbt_t* tree, ghost_iwbt_node_t* node, ghost_size_t depth) {
    /* print right before left, the tree is rotated 90 degrees counter-clockwise */
    if (node->ghost_impl_v_last_child)
        ghost_impl_iwbt_print_node(tree, node->ghost_impl_v_last_child, depth + 1);
    ghost_size_t i;
    for (i = 0; i < depth; ++i)
        printf("    ");
    printf("%p  weight:%zi\n", ghost_static_cast(void*, node), node->ghost_impl_v_weight);
    if (node->ghost_impl_v_first_child)
        ghost_impl_iwbt_print_node(tree, node->ghost_impl_v_first_child, depth + 1);
}

ghost_impl_inline
void ghost_impl_iwbt_print(ghost_iwbt_t* tree) {
    if (tree->ghost_impl_v_root == ghost_null) {
        printf("tree is empty.\n");
    } else {
        printf("=====\n");
        ghost_impl_iwbt_print_node(tree, tree->ghost_impl_v_root, 0);
        printf("=====\n");
    }
}
#endif

GHOST_IMPL_FUNCTION_CLOSE

#endif
#endif
