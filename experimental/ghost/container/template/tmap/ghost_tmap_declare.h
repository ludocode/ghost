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

#ifndef GHOST_TMAP_DECLARE_H_INCLUDED
#define GHOST_TMAP_DECLARE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMAP_DECLARE(prefix, key_t, value_t, node_field, value_key_fn, compare_fn)
 *
 * Declares functions for an intrusive weight-balanced tree map.
 *
 * You must have first instantiated the type with
 * GHOST_TMAP_DECLARE_TYPE(), and you must define functions after this
 * declaration in exactly one translation unit using GHOST_TMAP_DEFINE().
 *
 * TODO should take custom function attributes, so you can do emit/noemit, static, whatever
 *
 * @see GHOST_TMAP_DECLARE_TYPE()
 * @see GHOST_TMAP_DEFINE()
 */
#endif

#ifndef ghost_has_GHOST_TMAP_DECLARE
    #ifndef GHOST_TMAP_DECLARE
        #include "ghost/impl/container/template/tmap/ghost_impl_tmap_functions.h"
        #include "ghost/language/ghost_inline_opt.h"
        #define GHOST_TMAP_DECLARE(prefix, key_t, value_t, node_field, value_key_fn, compare_fn) \
            GHOST_IMPL_TMAP_DECLARE_FUNCTIONS(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, /*nothing*/, static ghost_inline_opt)
    #endif
    #define ghost_has_GHOST_TMAP_DECLARE 1
#endif

#endif
