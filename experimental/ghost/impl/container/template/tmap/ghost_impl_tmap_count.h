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

#ifndef GHOST_IMPL_TMAP_COUNT_H_INCLUDED
#define GHOST_IMPL_TMAP_COUNT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMAP_DECLARE_COUNT(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, inline_attrib, noninline_attrib)
 *
 * Declares a function that returns the number of elements in a map.
 */

/**
 * @def GHOST_TMAP_DEFINE_COUNT(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, inline_attrib, noninline_attrib)
 *
 * Defines a function that returns the number of elements in a map.
 */

/**
 * Returns the number of values in the map.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmap" is replaced by the prefix of the template.
 */
size_t ghost_tmap_count(ghost_tmap_t* map);
#endif

#ifndef ghost_has_GHOST_TMAP_DECLARE_COUNT
    #ifndef GHOST_TMAP_DECLARE_COUNT
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_count.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/debug/ghost_assert.h"
        #define GHOST_TMAP_DECLARE_COUNT(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            inline_attrib \
            ghost_size_t prefix##_count(prefix##_t* map) { \
                ghost_assert(map != ghost_null, ""); \
                return ghost_iwbt_count(&map->tree); \
            } \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMAP_DECLARE_COUNT 1
#endif

#ifndef ghost_has_GHOST_TMAP_DEFINE_COUNT
    #ifndef GHOST_TMAP_DEFINE_COUNT
        #define GHOST_TMAP_DEFINE_COUNT(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            /*nothing*/
    #endif
    #define ghost_has_GHOST_TMAP_DEFINE_COUNT 1
#endif

#endif
