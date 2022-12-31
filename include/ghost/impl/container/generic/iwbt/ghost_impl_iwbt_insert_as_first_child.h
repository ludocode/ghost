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

#ifndef GHOST_IMPL_IWBT_INSERT_AS_FIRST_CHILD_H_INCLUDED
#define GHOST_IMPL_IWBT_INSERT_AS_FIRST_CHILD_H_INCLUDED

#include "ghost/ghost_core.h"

#include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
#include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_rebalance.h"
#include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_increment_to_root.h"
#include "ghost/type/size_t/ghost_size_t.h"
#include "ghost/impl/ghost_impl_inline.h"
#include "ghost/language/ghost_null.h"

GHOST_IMPL_FUNCTION_OPEN

/*
 * A helper function to insert a node as the first child of a node that doesn't
 * have one.
 */
ghost_impl_function
void ghost_impl_iwbt_insert_as_first_child(ghost_iwbt_t* tree,
        ghost_iwbt_node_t* parent,
        ghost_iwbt_node_t* new_node) GHOST_IMPL_DEF(
{
    ghost_iwbt_log(("inserting %p as first child of %p\n",
            ghost_static_cast(void*, new_node),
            ghost_static_cast(void*, parent)));

    ghost_assert(parent != ghost_null, "");
    ghost_assert(parent->ghost_impl_v_first_child == ghost_null, "");
    parent->ghost_impl_v_first_child = new_node;

    new_node->ghost_impl_v_parent = parent;
    new_node->ghost_impl_v_first_child = ghost_null;
    new_node->ghost_impl_v_last_child = ghost_null;
    new_node->ghost_impl_v_weight = 2;

    ghost_impl_iwbt_increment_to_root(parent);
            ghost_iwbt_log(("%i\n",__LINE__));
    ghost_impl_iwbt_rebalance(tree, parent);
})

GHOST_IMPL_FUNCTION_CLOSE

#endif
