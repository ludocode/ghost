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

#ifndef GHOST_IMPL_TMAP_INSERT_H_INCLUDED
#define GHOST_IMPL_TMAP_INSERT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMAP_DECLARE_INSERT(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Declares a function that inserts a value into a map.
 */

/**
 * @def GHOST_TMAP_DEFINE_INSERT(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Defines a function that inserts a value into a map.
 */

/**
 * Inserts the given value, replacing a previous value with the given key and
 * returning it.
 *
 * If no value with a matching key previously existed in the map, null is
 * returned.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmap" is replaced by the prefix of the template.
 *
 * @return The previous value or null
 */
value_t* ghost_tmap_insert(ghost_tmap_t* map, value_t* value);
#endif

#ifndef ghost_has_GHOST_TMAP_DECLARE_INSERT
    #ifndef GHOST_TMAP_DECLARE_INSERT
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMAP_DECLARE_INSERT(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            noninline_attrib \
            value_t* prefix##_insert(prefix##_t* map, value_t* value); \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMAP_DECLARE_INSERT 1
#endif

#ifndef ghost_has_GHOST_TMAP_DEFINE_INSERT
    #ifndef GHOST_TMAP_DEFINE_INSERT
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_replace.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_insert_after.h"
        #include "ghost/language/ghost_container_of.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMAP_DEFINE_INSERT(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            \
            noninline_attrib \
            value_t* prefix##_insert(prefix##_t* map, value_t* value) { \
                ghost_bool equal; \
                value_t* before; \
                ghost_assert(map != ghost_null, ""); \
                ghost_assert(value != ghost_null, ""); \
                \
                before = prefix##_find_before(map, value_key_fn(value), &equal); \
                \
                if (equal) { \
                    ghost_assert(before != ghost_null, ""); \
                    ghost_iwbt_replace(&map->tree, &before->node_field, &value->node_field); \
                    return before; \
                } \
                \
                ghost_iwbt_insert_after(&map->tree, \
                        (before == ghost_null) ? ghost_null : &before->node_field, \
                        &value->node_field); \
                return ghost_null; \
            } \
            \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMAP_DEFINE_INSERT 1
#endif

#endif
