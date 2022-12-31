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

#ifndef GHOST_IMPL_IWBT_INSERT_INTO_EMPTY_TREE_H_INCLUDED
#define GHOST_IMPL_IWBT_INSERT_INTO_EMPTY_TREE_H_INCLUDED

#include "ghost/ghost_core.h"

#include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
#include "ghost/type/size_t/ghost_size_t.h"
#include "ghost/impl/ghost_impl_inline.h"
#include "ghost/language/ghost_null.h"

GHOST_IMPL_FUNCTION_OPEN

/*
 * A helper function to insert a node into an empty tree.
 */
ghost_impl_function
void ghost_impl_iwbt_insert_into_empty_tree(ghost_iwbt_t* tree, ghost_iwbt_node_t* node) GHOST_IMPL_DEF({
    ghost_iwbt_log(("inserting %p into empty tree\n", ghost_static_cast(void*, node)));
    ghost_assert(tree->ghost_impl_v_root == ghost_null, "");
    tree->ghost_impl_v_root = node;
    node->ghost_impl_v_parent = ghost_null;
    node->ghost_impl_v_first_child = ghost_null;
    node->ghost_impl_v_last_child = ghost_null;
    node->ghost_impl_v_weight = 2;
})

GHOST_IMPL_FUNCTION_CLOSE

#endif
