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

#ifndef GHOST_IMPL_TMMAP_PREVIOUS_H_INCLUDED
#define GHOST_IMPL_TMMAP_PREVIOUS_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMMAP_DECLARE_PREVIOUS(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, inline_attrib, noninline_attrib)
 *
 * Declares a function that returns the previous element in the map.
 */

/**
 * @def GHOST_TMMAP_DEFINE_PREVIOUS(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, inline_attrib, noninline_attrib)
 *
 * Defines a function that returns the previous element in the map.
 */

/**
 * Returns the value preceding the given value or null if the given value is
 * the first value in the map.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmmap" is replaced by the prefix of the template.
 */
value_t* ghost_tmmap_previous(ghost_tmmap_t* map, value_t* value);
#endif

#ifndef ghost_has_GHOST_TMMAP_DECLARE_PREVIOUS
    #ifndef GHOST_TMMAP_DECLARE_PREVIOUS
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_previous.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/debug/ghost_assert.h"
        #define GHOST_TMMAP_DECLARE_PREVIOUS(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            inline_attrib \
            value_t* prefix##_previous(prefix##_t* map, value_t* value) { \
                ghost_iwbt_node_t* node; \
                ghost_assert(map != ghost_null, ""); \
                node = ghost_iwbt_previous(&map->tree, &value->node_field); \
                return (node == ghost_null) ? ghost_null : ghost_container_of(node, value_t, node_field); \
            } \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMMAP_DECLARE_PREVIOUS 1
#endif

#ifndef ghost_has_GHOST_TMMAP_DEFINE_PREVIOUS
    #ifndef GHOST_TMMAP_DEFINE_PREVIOUS
        #define GHOST_TMMAP_DEFINE_PREVIOUS(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            /*nothing*/
    #endif
    #define ghost_has_GHOST_TMMAP_DEFINE_PREVIOUS 1
#endif

#endif
