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

#ifndef GHOST_IWBT_NODE_T_H_INCLUDED
#define GHOST_IWBT_NODE_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Metadata for a node in an intrusive weight-balanced tree.
 *
 * Add a field of this type to a struct that you want to store in an iwbt data
 * structure.
 */
typedef struct ghost_iwbt_node_t ghost_iwbt_node_t;
#endif

#ifndef ghost_has_ghost_iwbt_node_t
    #ifndef ghost_iwbt_node_t
        #include "ghost/type/size_t/ghost_size_t.h"
        typedef struct ghost_iwbt_node_t {
            struct ghost_iwbt_node_t* ghost_impl_v_parent;
            struct ghost_iwbt_node_t* ghost_impl_v_first_child;
            struct ghost_iwbt_node_t* ghost_impl_v_last_child;
            ghost_size_t ghost_impl_v_weight;
        } ghost_iwbt_node_t;
    #endif
    #define ghost_has_ghost_iwbt_node_t 1
#endif

#endif
