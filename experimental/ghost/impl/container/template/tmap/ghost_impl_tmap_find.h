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

#ifndef GHOST_IMPL_TMAP_FIND_H_INCLUDED
#define GHOST_IMPL_TMAP_FIND_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMAP_DECLARE_FIND(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Declares a function that finds a map value by key.
 */

/**
 * @def GHOST_TMAP_DEFINE_FIND(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Defines a function that finds a map value by key.
 */

/**
 * Finds the value in the map with the given key or returns null if no such
 * value exists.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmap" is replaced by the prefix of the template.
 */
value_t* ghost_tmap_find(ghost_tmap_t* map, key_t key);
#endif

#ifndef ghost_has_GHOST_TMAP_DECLARE_FIND
    #ifndef GHOST_TMAP_DECLARE_FIND
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMAP_DECLARE_FIND(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            noninline_attrib \
            value_t* prefix##_find(prefix##_t* map, key_t key); \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMAP_DECLARE_FIND 1
#endif

#ifndef ghost_has_GHOST_TMAP_DEFINE_FIND
    #ifndef GHOST_TMAP_DEFINE_FIND
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_root.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_first_child.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_last_child.h"
        #include "ghost/language/ghost_container_of.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #include "ghost/language/ghost_null.h"
        #define GHOST_TMAP_DEFINE_FIND(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            \
            noninline_attrib \
            value_t* prefix##_find(prefix##_t* map, key_t key) { \
                ghost_iwbt_node_t* node; \
                ghost_assert(map != ghost_null, ""); \
                \
                node = ghost_iwbt_root(&map->tree); \
                while (node != ghost_null) { \
                    value_t* value = ghost_container_of(node, value_t, node_field); \
                    int cmp = compare_fn(key, value_key_fn(value)); \
                    if (cmp > 0) { \
                        node = ghost_iwbt_node_last_child(node); \
                    } else if (cmp < 0) { \
                        node = ghost_iwbt_node_first_child(node); \
                    } else { \
                        return value; \
                    } \
                } \
                return ghost_null; \
            } \
            \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMAP_DEFINE_FIND 1
#endif

#endif
