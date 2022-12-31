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

#ifndef GHOST_IMPL_IWBT_WEIGHT_H_INCLUDED
#define GHOST_IMPL_IWBT_WEIGHT_H_INCLUDED

#include "ghost/ghost_core.h"

#include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
#include "ghost/type/size_t/ghost_size_t.h"
#include "ghost/impl/ghost_impl_inline.h"
#include "ghost/language/ghost_null.h"

GHOST_IMPL_FUNCTION_OPEN

/*
 * Returns the weight of the given node or 1 if null.
 */
ghost_impl_inline
ghost_size_t ghost_impl_iwbt_weight(ghost_iwbt_node_t* /*nullable*/ node) {
    return (node == ghost_null) ? 1 : node->ghost_impl_v_weight;
}

GHOST_IMPL_FUNCTION_CLOSE

#endif
