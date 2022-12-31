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

#ifndef GHOST_SSET_INSERT_L_H_INCLUDED
#define GHOST_SSET_INSERT_L_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Adds the given string with the given length to the given set of strings (if
 * it is not already in the set.)
 *
 * The string does not need to be null-terminated.
 *
 * If the string is already in the set, the set is not changed and false is
 * returned.
 *
 * The string is copied into the set (with an added null-terminator.) If memory
 * allocation fails, the program aborts (via ghost_fatal().)
 *
 * @return True if the string was inserted, or false if the string already
 *         existed in the set
 */
bool ghost_sset_insert_l(ghost_sset_t* set, const char* string, size_t length);
#endif

#ifndef ghost_has_ghost_sset_insert_l
    #ifdef ghost_sset_insert_l
        #define ghost_has_ghost_sset_insert_l 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_insert_l
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_insert_l 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_insert_l
    #include "ghost/container/generic/iwbt/ghost_iwbt_insert_after.h"
    #include "ghost/container/common/sset/ghost_sset_find_before_l.h"
    #include "ghost/impl/container/common/sset/ghost_impl_sset_element_new.h"
    #include "ghost/type/bool/ghost_bool.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/impl/ghost_impl_function.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    ghost_bool ghost_sset_insert_l(ghost_sset_t* set, const char* string,
            ghost_size_t length) GHOST_IMPL_DEF(
    {
        ghost_bool equal;
        ghost_impl_sset_element_t* before;
        ghost_assert(set != ghost_null, "");

        before = ghost_sset_find_before_l(set, string, length, &equal);
        if (equal)
            return ghost_false;

        ghost_iwbt_insert_after(&set->tree,
                (before == ghost_null) ? ghost_null : &before->node,
                &ghost_impl_sset_element_new(string, length)->node);
        return ghost_true;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_sset_insert_l 1
#endif

#endif
