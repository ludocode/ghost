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

#ifndef GHOST_SSET_FIND_L_H_INCLUDED
#define GHOST_SSET_FIND_L_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns an iterator to the given string with the given length in the set, or
 * null if the string is not in the set.
 *
 * See ghost_sset_it_t for example usage.
 *
 * @see ghost_sset_it_t
 */
ghost_sset_it_t ghost_sset_find_l(ghost_sset_t* set, const char* string, ghost_size_t length);
#endif

#ifndef ghost_has_ghost_sset_find_l
    #ifdef ghost_sset_find_l
        #define ghost_has_ghost_sset_find_l 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_find_l
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_find_l 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_find_l
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #include "ghost/container/common/sset/ghost_sset_it_t.h"
    #include "ghost/impl/container/common/sset/ghost_impl_sset_element_t.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_root.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_node_first_child.h"
    #include "ghost/container/generic/iwbt/ghost_iwbt_node_last_child.h"
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/language/ghost_container_of.h"
    #include "ghost/language/ghost_null.h"
    #include "ghost/string/ghost_memlcmp.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_sset_it_t ghost_sset_find_l(ghost_sset_t* ghost_impl_v_set, const char* string, ghost_size_t length) {
        ghost_iwbt_node_t* node;
        ghost_assert(ghost_impl_v_set != ghost_null, "");

        node = ghost_iwbt_root(&ghost_impl_v_set->tree);
        while (node != ghost_null) {
            ghost_impl_sset_element_t* element = ghost_container_of(node, ghost_impl_sset_element_t, node);
            int cmp = ghost_memlcmp(string, length, element->cstring, element->length);
            if (cmp > 0) {
                node = ghost_iwbt_node_last_child(node);
            } else if (cmp < 0) {
                node = ghost_iwbt_node_first_child(node);
            } else {
                return element;
            }
        }
        return ghost_null;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_sset_find_l 1
#endif

#endif
