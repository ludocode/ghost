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

#ifndef GHOST_IMPL_TMMAP_FIND_LAST_H_INCLUDED
#define GHOST_IMPL_TMMAP_FIND_LAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMMAP_DECLARE_FIND_LAST(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Declares a function that finds a map value by key.
 */

/**
 * @def GHOST_TMMAP_DEFINE_FIND_LAST(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Defines a function that finds a map value by key.
 */

/**
 * Finds the last value in the map with the given key or returns null if no
 * such value exists.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmmap" is replaced by the prefix of the template.
 */
value_t* ghost_tmmap_find_last(ghost_tmmap_t* map, key_t key);
#endif

#ifndef ghost_has_GHOST_TMMAP_DECLARE_FIND_LAST
    #ifndef GHOST_TMMAP_DECLARE_FIND_LAST
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/type/bool/ghost_bool.h"
        #define GHOST_TMMAP_DECLARE_FIND_LAST(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            inline_attrib \
            value_t* prefix##_find_last(prefix##_t* map, key_t key) { \
                ghost_bool equal; \
                value_t* value = prefix##_find_after(map, key, &equal); \
                return equal ? value : ghost_null; \
            } \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMMAP_DECLARE_FIND_LAST 1
#endif

#ifndef ghost_has_GHOST_TMMAP_DEFINE_FIND_LAST
    #ifndef GHOST_TMMAP_DEFINE_FIND_LAST
        #define GHOST_TMMAP_DEFINE_FIND_LAST(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            /*nothing*/
    #endif
    #define ghost_has_GHOST_TMMAP_DEFINE_FIND_LAST 1
#endif

#endif
