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

#ifndef GHOST_IMPL_SSET_ELEMENT_T_H_INCLUDED
#define GHOST_IMPL_SSET_ELEMENT_T_H_INCLUDED

#include "ghost/container/common/sset/ghost_sset_t.h"

#if ghost_has(ghost_sset_t)
    #include "ghost/container/generic/iwbt/ghost_iwbt_node_t.h"
    #include "ghost/language/ghost_struct_hack.h"
    #include "ghost/type/size_t/ghost_size_t.h"

    typedef struct ghost_impl_sset_element_t {
        ghost_iwbt_node_t node;
        ghost_size_t length;
        char cstring[GHOST_STRUCT_HACK];
    } ghost_impl_sset_element_t;
#endif

#endif
