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

#ifndef GHOST_TMMAP_STATIC_H_INCLUDED
#define GHOST_TMMAP_STATIC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMMAP_STATIC(prefix, key_t, value_t, node_field, value_key_fn, compare_fn)
 *
 * Declares and defines functions for an intrusive weight-balanced tree
 * multimap with static linkage, intended for use in a single translation unit.
 *
 * All functions are declared either `static` or `static inline`. You generally
 * shouldn't put this in a header file. For a shared header file, use
 * GHOST_TMMAP_HEADER() instead, or consider using the separate
 * GHOST_TMMAP_DECLARE() and GHOST_TMMAP_DEFINE().
 *
 * You must have first instantiated the type with
 * GHOST_TMMAP_DECLARE_TYPE().
 *
 * @see GHOST_TMMAP_DECLARE_TYPE()
 * @see GHOST_TMMAP_HEADER()
 */
#endif

#ifndef ghost_has_GHOST_TMMAP_STATIC
    #ifndef GHOST_TMMAP_STATIC
        #include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_functions.h"
        #include "ghost/language/ghost_inline_opt.h"
        #include "ghost/language/ghost_maybe_unused.h"
        #define GHOST_TMMAP_STATIC(prefix, key_t, value_t, node_field, value_key_fn, compare_fn) \
            GHOST_IMPL_TMMAP_DECLARE_FUNCTIONS(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, ghost_maybe_unused static, static ghost_inline_opt) \
            GHOST_IMPL_TMMAP_DEFINE_FUNCTIONS (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, ghost_maybe_unused static)
    #endif
    #define ghost_has_GHOST_TMMAP_STATIC 1
#endif

#endif
