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

#ifndef GHOST_SSET_IT_T_H_INCLUDED
#define GHOST_SSET_IT_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * An iterator into a set of strings.
 *
 * Use this to iterate through all strings in a string set. For example:
 *
 *     for (ghost_sset_it_t it = ghost_sset_first(sset); it; it = ghost_sset_next(sset, it)) {
 *         const char* str = ghost_sset_it_string(it);
 *         // do something with str
 *     }
 *
 * Iterators are not invalidated by insertions or removals of other elements so
 * you can conditionally remove elements as long as you fetch the next element
 * first. For example:
 *
 *     for (ghost_sset_it_t it = ghost_sset_first(sset); it;) {
 *         ghost_sset_it_t next = ghost_sset_next(sset, it);
 *         const char* str = ghost_sset_it_string(it);
 *         if (some_condition(str)) {
 *             ghost_sset_remove_it(sset, it);
 *         }
 *         it = next;
 *     }
 *
 * @see ghost_sset_it_string()
 * @see ghost_sset_it_length()
 * @see ghost_sset_first()
 * @see ghost_sset_next()
 */
typedef /*unspecified*/ ghost_sset_t;
#endif

#ifndef ghost_has_ghost_sset_it_t
    #ifdef ghost_sset_it_t
        #define ghost_has_ghost_sset_it_t 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_sset_it_t
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_it_t 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_it_t
    #include "ghost/impl/container/common/sset/ghost_impl_sset_element_t.h"
    typedef ghost_impl_sset_element_t* ghost_sset_it_t;
    #define ghost_has_ghost_sset_it_t 1
#endif

#endif
