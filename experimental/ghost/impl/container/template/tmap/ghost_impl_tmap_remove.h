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

#ifndef GHOST_IMPL_TMAP_REMOVE_H_INCLUDED
#define GHOST_IMPL_TMAP_REMOVE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMAP_DECLARE_REMOVE(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, inline_attrib, noninline_attrib)
 *
 * Declares a function that removes a value from a map.
 */

/**
 * @def GHOST_TMAP_DEFINE_REMOVE(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, inline_attrib, noninline_attrib)
 *
 * Defines a function that removes a value from a map.
 */

/**
 * Removes the given value from the given map.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmap" is replaced by the prefix of the template.
 */
void ghost_tmap_remove(ghost_tmap_t* map, value_t* value);
#endif

#ifndef ghost_has_GHOST_TMAP_DECLARE_REMOVE
    #ifndef GHOST_TMAP_DECLARE_REMOVE
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_remove.h"
        #include "ghost/debug/ghost_assert.h"
        #define GHOST_TMAP_DECLARE_REMOVE(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            inline_attrib \
            void prefix##_remove(prefix##_t* map, value_t* value) { \
                ghost_assert(map != ghost_null, ""); \
                ghost_assert(value != ghost_null, ""); \
                ghost_iwbt_remove(&map->tree, &value->node_field); \
            } \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMAP_DECLARE_REMOVE 1
#endif

#ifndef ghost_has_GHOST_TMAP_DEFINE_REMOVE
    #ifndef GHOST_TMAP_DEFINE_REMOVE
        #define GHOST_TMAP_DEFINE_REMOVE(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            /*nothing*/
    #endif
    #define ghost_has_GHOST_TMAP_DEFINE_REMOVE 1
#endif

#endif
