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

#ifndef GHOST_IMPL_TMMAP_INSERT_AFTER_H_INCLUDED
#define GHOST_IMPL_TMMAP_INSERT_AFTER_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMMAP_DECLARE_INSERT_AFTER(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Declares a function that inserts a value into a map.
 */

/**
 * @def GHOST_TMMAP_DEFINE_INSERT_AFTER(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Defines a function that inserts a value into a map.
 */

/**
 * Inserts the given value after the given reference value with a matching
 * key into the list of values for this key.
 *
 * The keys of the given values must match.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmmap" is replaced by the prefix of the template.
 *
 * @return The previous value or null
 */
void ghost_tmmap_insert_after(ghost_tmmap_t* map, value_t* reference_value, value_t* value_to_insert);
#endif

#ifndef ghost_has_GHOST_TMMAP_DECLARE_INSERT_AFTER
    #ifndef GHOST_TMMAP_DECLARE_INSERT_AFTER
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_insert_after.h"
        #define GHOST_TMMAP_DECLARE_INSERT_AFTER(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            inline_attrib \
            void prefix##_insert_after(prefix##_t* map, value_t* reference_value, value_t* value_to_insert) { \
                ghost_assert(0 == compare_fn(value_key_fn(value_to_insert), value_key_fn(reference_value)), \
                        "cannot insert after value with non-matching key"); \
                ghost_iwbt_insert_after(&map->tree, &reference_value->node_field, &value_to_insert->node_field); \
            } \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMMAP_DECLARE_INSERT_AFTER 1
#endif

#ifndef ghost_has_GHOST_TMMAP_DEFINE_INSERT_AFTER
    #ifndef GHOST_TMMAP_DEFINE_INSERT_AFTER
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_replace.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_insert_after.h"
        #include "ghost/language/ghost_container_of.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMMAP_DEFINE_INSERT_AFTER(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            /* nothing */
    #endif
    #define ghost_has_GHOST_TMMAP_DEFINE_INSERT_AFTER 1
#endif

#endif
