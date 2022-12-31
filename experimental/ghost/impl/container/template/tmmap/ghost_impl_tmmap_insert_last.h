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

#ifndef GHOST_IMPL_TMMAP_INSERT_LAST_H_INCLUDED
#define GHOST_IMPL_TMMAP_INSERT_LAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMMAP_DECLARE_INSERT_LAST(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Declares a function that inserts a value into a map.
 */

/**
 * @def GHOST_TMMAP_DEFINE_INSERT_LAST(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Defines a function that inserts a value into a map.
 */

/**
 * Inserts the given value as the last value in the list of values for this
 * key.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmmap" is replaced by the prefix of the template.
 *
 * @return The previous value or null
 */
void ghost_tmmap_insert_last(ghost_tmmap_t* map, value_t* value);
#endif

#ifndef ghost_has_GHOST_TMMAP_DECLARE_INSERT_LAST
    #ifndef GHOST_TMMAP_DECLARE_INSERT_LAST
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMMAP_DECLARE_INSERT_LAST(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            noninline_attrib \
            void prefix##_insert_last(prefix##_t* map, value_t* value); \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMMAP_DECLARE_INSERT_LAST 1
#endif

#ifndef ghost_has_GHOST_TMMAP_DEFINE_INSERT_LAST
    #ifndef GHOST_TMMAP_DEFINE_INSERT_LAST
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_replace.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_insert_after.h"
        #include "ghost/language/ghost_container_of.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMMAP_DEFINE_INSERT_LAST(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            \
            noninline_attrib \
            void prefix##_insert_last(prefix##_t* map, value_t* value) { \
                ghost_bool equal; \
                value_t* after; \
                ghost_assert(map != ghost_null, ""); \
                ghost_assert(value != ghost_null, ""); \
                \
                after = prefix##_find_after(map, value_key_fn(value), &equal); \
                if (equal) \
                    after = prefix##_next(map, after); \
                \
                ghost_iwbt_insert_before(&map->tree, \
                        (after == ghost_null) ? ghost_null : &after->node_field, \
                        &value->node_field); \
            } \
            \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMMAP_DEFINE_INSERT_LAST 1
#endif

#endif
