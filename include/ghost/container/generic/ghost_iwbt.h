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

#ifndef GHOST_IWBT_H_INCLUDED
#define GHOST_IWBT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * A type-erased intrusive weight-balanced order-statistic binary tree.
 */
#endif

#ifndef ghost_has_ghost_iwbt
    #define ghost_has_ghost_iwbt 1

    #include "ghost/container/generic/iwbt/ghost_iwbt_root.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_at.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_clear.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_count.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_first.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_index.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_insert_after.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_insert_at.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_insert_before.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_insert_first.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_insert_last.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_is_empty.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_last.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_node_first_child.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_node_first_in_subtree.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_next.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_node_parent.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_previous.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_remove_and_next.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_remove_and_previous.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_remove_any.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_remove_at.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_remove_first.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_remove.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_remove_last.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_replace_at.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_replace.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_node_last_child.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_node_last_in_subtree.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_root.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_swap.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
#endif

#endif
