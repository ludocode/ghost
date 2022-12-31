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

#ifndef GHOST_IMPL_TMMAP_NEXT_MATCH_H_INCLUDED
#define GHOST_IMPL_TMMAP_NEXT_MATCH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMMAP_DECLARE_NEXT_MATCH(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, inline_attrib, noninline_attrib)
 *
 * Declares a function that returns the next element in the map.
 */
/* TODO get rid of all these docs, prefix all with IMPL */

/**
 * @def GHOST_TMMAP_DEFINE_NEXT_MATCH(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, inline_attrib, noninline_attrib)
 *
 * Defines a function that returns the next element in the map.
 */

/**
 * Returns the next value with a matching key or null if this is the last value
 * with this key.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmmap" is replaced by the prefix of the template.
 */
value_t* ghost_tmmap_next_match(ghost_tmmap_t* map, value_t* value);
#endif

#ifndef ghost_has_GHOST_TMMAP_DECLARE_NEXT_MATCH
    #ifndef GHOST_TMMAP_DECLARE_NEXT_MATCH
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_next.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/debug/ghost_assert.h"
        #define GHOST_TMMAP_DECLARE_NEXT_MATCH(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            inline_attrib \
            value_t* prefix##_next_match(prefix##_t* map, value_t* value) { \
                ghost_iwbt_node_t* next_node; \
                value_t* next_value; \
                ghost_assert(map != ghost_null, ""); \
                next_node = ghost_iwbt_next(&map->tree, &value->node_field); \
                if (next_node == ghost_null) \
                    return ghost_null; \
                next_value = ghost_container_of(next_node, value_t, node_field); \
                if (0 != compare_fn(value_key_fn(value), value_key_fn(next_value))) \
                    return ghost_null; \
                return next_value; \
            } \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMMAP_DECLARE_NEXT_MATCH 1
#endif

#ifndef ghost_has_GHOST_TMMAP_DEFINE_NEXT_MATCH
    #ifndef GHOST_TMMAP_DEFINE_NEXT_MATCH
        #define GHOST_TMMAP_DEFINE_NEXT_MATCH(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            /*nothing*/
    #endif
    #define ghost_has_GHOST_TMMAP_DEFINE_NEXT_MATCH 1
#endif

#endif
