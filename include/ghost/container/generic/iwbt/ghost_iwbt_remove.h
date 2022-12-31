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

#ifndef GHOST_IWBT_REMOVE_H_INCLUDED
#define GHOST_IWBT_REMOVE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Remove the given node.
 */
#endif

#ifndef ghost_has_ghost_iwbt_remove
    #ifndef ghost_iwbt_remove
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_first_in_subtree.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_last_in_subtree.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_sanity_check.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_decrement_to_root.h"
        #include "ghost/impl/container/generic/iwbt/ghost_impl_iwbt_rebalance.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_null.h"
        GHOST_IMPL_FUNCTION_OPEN

        ghost_impl_function
        void ghost_iwbt_remove(ghost_iwbt_t* ghost_impl_v_tree, ghost_iwbt_node_t* ghost_impl_v_node) GHOST_IMPL_DEF({
            ghost_iwbt_node_t* parent = ghost_impl_v_node->ghost_impl_v_parent;
            ghost_iwbt_log(("removing %p\n", ghost_static_cast(void*, ghost_impl_v_node)));
            ghost_impl_iwbt_sanity_check(ghost_impl_v_tree);

            /* if the ghost_impl_v_node has no children, we can remove it directly. */
            if (ghost_impl_v_node->ghost_impl_v_weight == 2) {
                ghost_assert(ghost_impl_v_node->ghost_impl_v_first_child == ghost_null, "");
                ghost_assert(ghost_impl_v_node->ghost_impl_v_last_child == ghost_null, "");

                if (parent == ghost_null) {
                    ghost_assert(ghost_impl_v_tree->ghost_impl_v_root == ghost_impl_v_node, "");
                    ghost_impl_v_tree->ghost_impl_v_root = ghost_null;
                } else {
                    if (parent->ghost_impl_v_first_child == ghost_impl_v_node) {
                        parent->ghost_impl_v_first_child = ghost_null;
                    } else {
                        ghost_assert(parent->ghost_impl_v_last_child == ghost_impl_v_node, "");
                        parent->ghost_impl_v_last_child = ghost_null;
                    }
                    ghost_impl_iwbt_decrement_to_root(parent);
                    ghost_iwbt_log(("%i\n",__LINE__));
                    ghost_impl_iwbt_rebalance(ghost_impl_v_tree, parent);
                }
                ghost_impl_iwbt_sanity_check(ghost_impl_v_tree);
                return;
            }

            /* If the ghost_impl_v_node has only one child, we can replace it with that child. */
            if (ghost_impl_v_node->ghost_impl_v_first_child == ghost_null || ghost_impl_v_node->ghost_impl_v_last_child == ghost_null) {
                ghost_iwbt_node_t* child = (ghost_impl_v_node->ghost_impl_v_first_child != ghost_null) ? ghost_impl_v_node->ghost_impl_v_first_child : ghost_impl_v_node->ghost_impl_v_last_child;
                ghost_assert(child->ghost_impl_v_parent == ghost_impl_v_node, "");

                if (parent == ghost_null) {
                    ghost_assert(ghost_impl_v_tree->ghost_impl_v_root == ghost_impl_v_node, "");
                    ghost_impl_v_tree->ghost_impl_v_root = child;
                    child->ghost_impl_v_parent = ghost_null;
                    ghost_impl_iwbt_sanity_check(ghost_impl_v_tree);
                } else {
                    if (parent->ghost_impl_v_first_child == ghost_impl_v_node) {
                        parent->ghost_impl_v_first_child = child;
                    } else {
                        ghost_assert(parent->ghost_impl_v_last_child == ghost_impl_v_node, "");
                        parent->ghost_impl_v_last_child = child;
                    }
                    child->ghost_impl_v_parent = parent;
                    ghost_impl_iwbt_decrement_to_root(parent);
                    ghost_iwbt_log(("%i\n",__LINE__));
                    ghost_impl_iwbt_rebalance(ghost_impl_v_tree, parent);
                }
                ghost_impl_iwbt_sanity_check(ghost_impl_v_tree);
                return;
            }

            /* Otherwise we replace it with an adjacent child, chosen from the side
             * with the most entries. Since the ghost_impl_v_node has two children and the
             * replacement is adjacent, the replacement will have at most one child and
             * it will be pointing away from us. */
            {
                ghost_iwbt_node_t* replacement;
                ghost_iwbt_node_t* replacement_child;
                ghost_iwbt_node_t* replacement_parent;
                if (ghost_impl_v_node->ghost_impl_v_first_child->ghost_impl_v_weight > ghost_impl_v_node->ghost_impl_v_last_child->ghost_impl_v_weight) {
                    replacement = ghost_iwbt_node_last_in_subtree(ghost_impl_v_node->ghost_impl_v_first_child);
                    ghost_assert(replacement != ghost_null, "");
                    ghost_assert(replacement->ghost_impl_v_last_child == ghost_null, "");
                    replacement_child = replacement->ghost_impl_v_first_child;
                } else {
                    replacement = ghost_iwbt_node_first_in_subtree(ghost_impl_v_node->ghost_impl_v_last_child);
                    ghost_assert(replacement != ghost_null, "");
                    ghost_assert(replacement->ghost_impl_v_first_child == ghost_null, "");
                    replacement_child = replacement->ghost_impl_v_last_child;
                }
                replacement_parent = replacement->ghost_impl_v_parent;

                /* TODO we have ghost_iwbt_replace(), should share this code.
                 * just need to move it to a ghost_iwbt_impl_replace() that
                 * skips sanity checks the balancing is separate */

                /* We start by removing the replacement from the ghost_impl_v_tree. */
                if (replacement_parent->ghost_impl_v_first_child == replacement) {
                    replacement_parent->ghost_impl_v_first_child = replacement_child;
                } else {
                    ghost_assert(replacement_parent->ghost_impl_v_last_child == replacement, "");
                    replacement_parent->ghost_impl_v_last_child = replacement_child;
                }
                if (replacement_child != ghost_null) {
                    replacement_child->ghost_impl_v_parent = replacement_parent;
                }

                /* We can now replace ourselves with the replacement. */
                replacement->ghost_impl_v_first_child = ghost_impl_v_node->ghost_impl_v_first_child;
                replacement->ghost_impl_v_last_child = ghost_impl_v_node->ghost_impl_v_last_child;
                if (ghost_impl_v_node->ghost_impl_v_first_child != ghost_null)
                    ghost_impl_v_node->ghost_impl_v_first_child->ghost_impl_v_parent = replacement;
                if (ghost_impl_v_node->ghost_impl_v_last_child != ghost_null)
                    ghost_impl_v_node->ghost_impl_v_last_child->ghost_impl_v_parent = replacement;
                if (parent == ghost_null) {
                    ghost_assert(ghost_impl_v_tree->ghost_impl_v_root == ghost_impl_v_node, "");
                    ghost_impl_v_tree->ghost_impl_v_root = replacement;
                    replacement->ghost_impl_v_parent = ghost_null;
                } else {
                    if (parent->ghost_impl_v_first_child == ghost_impl_v_node) {
                        parent->ghost_impl_v_first_child = replacement;
                    } else {
                        ghost_assert(parent->ghost_impl_v_last_child == ghost_impl_v_node, "");
                        parent->ghost_impl_v_last_child = replacement;
                    }
                    replacement->ghost_impl_v_parent = ghost_impl_v_node->ghost_impl_v_parent;
                }

                /* Lastly, we re-calculate sizes and rebalance. If the replacement parent
                 * was not us, then it is some ghost_impl_v_node deeper in the ghost_impl_v_tree, so that's where we
                 * need to start. Otherwise we start at the replacement. */
                {
                    ghost_iwbt_node_t* fix = (replacement_parent != ghost_impl_v_node) ? replacement_parent : replacement;

                    /* TODO: maybe remove this, decrement, increment, etc. and make it all part of rebalance */
                    ghost_iwbt_node_t* recalculate = fix;
                    while (recalculate != ghost_null) {
                        ghost_impl_iwbt_recalculate_size(recalculate);
                        recalculate = recalculate->ghost_impl_v_parent;
                    }

                    ghost_iwbt_log(("%i\n",__LINE__));
                    ghost_impl_iwbt_rebalance(ghost_impl_v_tree, fix);
                    ghost_impl_iwbt_sanity_check(ghost_impl_v_tree);
                }
            }
        })

        GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_ghost_iwbt_remove 1
#endif

#endif
