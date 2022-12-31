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

#ifndef GHOST_IWBT_T_H_INCLUDED
#define GHOST_IWBT_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A type-erased weight-balanced tree.
 *
 * You can initialize the tree to empty by zeroing, e.g. with GHOST_ZERO_INIT
 * or ghost_bzero(). You can also initialize it by clearing it with
 * ghost_iwbt_clear().
 *
 * The tree does not need to be de-initialized (but your nodes might.)
 *
 * @see GHOST_ZERO_INIT
 * @see ghost_bzero()
 * @see ghost_iwbt_clear()
 */
typedef struct ghost_iwbt_t ghost_iwbt_t;
#endif

#ifndef ghost_has_ghost_iwbt_t
    #ifndef ghost_iwbt_t
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
        typedef struct ghost_iwbt_t {
            ghost_iwbt_node_t* ghost_impl_v_root;
        } ghost_iwbt_t;
    #endif
    #define ghost_has_ghost_iwbt_t 1
#endif

#endif
