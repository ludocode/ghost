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

#ifndef GHOST_IMPL_TMMAP_REMOVE_ALL_WITH_KEY_H_INCLUDED
#define GHOST_IMPL_TMMAP_REMOVE_ALL_WITH_KEY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMMAP_DECLARE_REMOVE_ALL_WITH_KEY(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 */

/**
 * @def GHOST_TMMAP_DEFINE_REMOVE_ALL_WITH_KEY(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 */

/**
 * Removes all values with the given key from the map.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmmap" is replaced by the prefix of the template.
 *
 * @return The previous value or null
 */
void ghost_tmmap_remove_all_with_key(ghost_tmmap_t* map, key_t key);
#endif

#ifndef ghost_has_GHOST_TMMAP_DECLARE_REMOVE_ALL_WITH_KEY
    #ifndef GHOST_TMMAP_DECLARE_REMOVE_ALL_WITH_KEY
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMMAP_DECLARE_REMOVE_ALL_WITH_KEY(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            noninline_attrib \
            void prefix##_remove_all_with_key(prefix##_t* map, key_t key); \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMMAP_DECLARE_REMOVE_ALL_WITH_KEY 1
#endif

#ifndef ghost_has_GHOST_TMMAP_DEFINE_REMOVE_ALL_WITH_KEY
    #ifndef GHOST_TMMAP_DEFINE_REMOVE_ALL_WITH_KEY
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_replace.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_insert_after.h"
        #include "ghost/language/ghost_container_of.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMMAP_DEFINE_REMOVE_ALL_WITH_KEY(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            \
            noninline_attrib \
            void prefix##_remove_all_with_key(prefix##_t* map, key_t key) { \
                value_t* value; \
                for (value = prefix##_find_first(map, key); value != ghost_null;) { \
                    value_t* next_value = prefix##_next_match(map, value); \
                    prefix##_remove(map, value); \
                    value = next_value; \
                } \
            } \
            \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMMAP_DEFINE_REMOVE_ALL_WITH_KEY 1
#endif

#endif
