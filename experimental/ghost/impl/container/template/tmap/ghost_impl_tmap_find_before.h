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

#ifndef GHOST_IMPL_TMAP_FIND_BEFORE_H_INCLUDED
#define GHOST_IMPL_TMAP_FIND_BEFORE_H_INCLUDED

#include "ghost/ghost_core.h"

/* TODO implement find_after() */

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMAP_DECLARE_FIND_BEFORE(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Declares a function that finds a map value by key, or the value before it if
 * it were in the map.
 */

/**
 * @def GHOST_TMAP_DEFINE_FIND_BEFORE(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Defines a function that finds a map value by key, or the value before it if
 * it were in the map.
 */

/**
 * Finds the value with the given key, or if no matching value exists, finds
 * the value that would be immediately preceeding it if it were in the map.
 *
 * In other words, this finds the value in the tree with the greatest key that
 * compares less than or equal to the given key.
 *
 * If no such value exists (i.e. the tree is empty or all values have keys
 * larger than the given key), null is returned.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmap" is replaced by the prefix of the template.
 *
 * @param found If not null, this is set to true if the value's key is equal
 *              to the given key (i.e. a value with a matching key was found)
 *              and false otherwise.
 */
value_t* ghost_tmap_find_before(prefix##_t* map, key_t key, bool* /*nullable*/ found);
#endif

#ifndef ghost_has_GHOST_TMAP_DECLARE_FIND_BEFORE
    #ifndef GHOST_TMAP_DECLARE_FIND_BEFORE
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMAP_DECLARE_FIND_BEFORE(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            noninline_attrib \
            value_t* prefix##_find_before(prefix##_t* map, key_t key, ghost_bool* /*nullable*/ equal); \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMAP_DECLARE_FIND_BEFORE 1
#endif

#ifndef ghost_has_GHOST_TMAP_DEFINE_FIND_BEFORE
    #ifndef GHOST_TMAP_DEFINE_FIND_BEFORE
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_root.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_first_child.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_last_child.h"
        #include "ghost/language/ghost_container_of.h"
        #include "ghost/language/ghost_unreachable.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/type/bool/ghost_true.h"
        #include "ghost/type/bool/ghost_false.h"
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMAP_DEFINE_FIND_BEFORE(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            \
            noninline_attrib \
            value_t* prefix##_find_before(prefix##_t* map, key_t key, ghost_bool* /*nullable*/ equal) { \
                ghost_iwbt_node_t* node; \
                ghost_iwbt_node_t* next_node; \
                \
                ghost_iwbt_log(("find before\n")); \
                ghost_assert(map != ghost_null, ""); \
                \
                if (equal != ghost_null) \
                    *equal = ghost_false; \
                \
                node = ghost_iwbt_root(&map->tree); \
                if (node == ghost_null) \
                    return ghost_null; \
                \
                for (;;) { \
                    value_t* value = ghost_container_of(node, value_t, node_field); \
                    int cmp = compare_fn(key, value_key_fn(value)); \
                    ghost_iwbt_log(("cmp: %i\n", cmp)); \
                    if (cmp > 0) { \
                        next_node = ghost_iwbt_node_last_child(node); \
                        if (next_node == ghost_null) \
                            return value; \
                        node = next_node; \
                    } else if (cmp < 0) { \
                        next_node = ghost_iwbt_node_first_child(node); \
                        if (next_node == ghost_null) { \
                            node = ghost_iwbt_previous(&map->tree, node); \
                            return (node == ghost_null) ? ghost_null : \
                                    ghost_container_of(node, value_t, node_field); \
                        } \
                        node = next_node; \
                    } else { \
                        *equal = ghost_true; \
                        return value; \
                    } \
                } \
                ghost_unreachable(ghost_null); \
            } \
            \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMAP_DEFINE_FIND_BEFORE 1
#endif

#endif
