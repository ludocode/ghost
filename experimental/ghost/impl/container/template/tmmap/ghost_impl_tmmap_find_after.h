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

#ifndef GHOST_IMPL_TMMAP_FIND_AFTER_H_INCLUDED
#define GHOST_IMPL_TMMAP_FIND_AFTER_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMMAP_DECLARE_FIND_AFTER(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Declares a function that finds a map value by key, or the value before it if
 * it were in the map.
 */
/* TODO rename all find_after() to something better, like find_last_or_after(), find_last_or_next() */

/**
 * @def GHOST_TMMAP_DEFINE_FIND_AFTER(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)
 *
 * Defines a function that finds a map value by key, or the value after it if
 * it were in the map.
 */

/**
 * Finds the last value with the given key, or if no matching value exists,
 * finds the value that would be immediately following it if one were in the
 * map.
 *
 * If no such value exists (i.e. the tree is empty or all values have keys
 * smaller than the given key), null is returned.
 *
 * This is a template function that must be instantiated. The prefix
 * "ghost_tmmap" is replaced by the prefix of the template.
 *
 * @param found If not null, this is set to true if the value's key is equal
 *              to the given key (i.e. a value with a matching key was found)
 *              and false otherwise.
 */
value_t* ghost_tmmap_find_after(prefix##_t* map, key_t key, bool* /*nullable*/ found);
#endif

#ifndef ghost_has_GHOST_TMMAP_DECLARE_FIND_AFTER
    #ifndef GHOST_TMMAP_DECLARE_FIND_AFTER
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMMAP_DECLARE_FIND_AFTER(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            noninline_attrib \
            value_t* prefix##_find_after(prefix##_t* map, key_t key, ghost_bool* /*nullable*/ equal); \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMMAP_DECLARE_FIND_AFTER 1
#endif

#ifndef ghost_has_GHOST_TMMAP_DEFINE_FIND_AFTER
    #ifndef GHOST_TMMAP_DEFINE_FIND_AFTER
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_root.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_first_child.h"
        #include "ghost/container/generic/iwbt/ghost_iwbt_node_last_child.h"
        #include "ghost/language/ghost_container_of.h"
        #include "ghost/language/ghost_unreachable.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #define GHOST_TMMAP_DEFINE_FIND_AFTER(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
            GHOST_IMPL_FUNCTION_OPEN \
            \
            noninline_attrib \
            value_t* prefix##_find_after(prefix##_t* map, key_t key, ghost_bool* /*nullable*/ equal) { \
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
                /* step into the tree until we find a match. */ \
                for (;;) { \
                    value_t* value = ghost_container_of(node, value_t, node_field); \
                    int cmp = compare_fn(key, value_key_fn(value)); \
                    ghost_iwbt_log(("cmp: %i\n", cmp)); \
                    if (cmp > 0) { \
                        next_node = ghost_iwbt_node_last_child(node); \
                        if (next_node == ghost_null) { \
                            node = ghost_iwbt_next(&map->tree, node); \
                            return (node == ghost_null) ? ghost_null : \
                                    ghost_container_of(node, value_t, node_field); \
                        } \
                        node = next_node; \
                    } else if (cmp < 0) { \
                        next_node = ghost_iwbt_node_first_child(node); \
                        if (next_node == ghost_null) \
                            return value; \
                        node = next_node; \
                    } else { \
                        /* found a match. keep searching right for the last match. */ \
                        value_t* match = value; \
                        *equal = ghost_true; \
                        node = ghost_iwbt_node_last_child(node); \
                        for (;;) { \
                            if (node == ghost_null) \
                                return match; \
                            value = ghost_container_of(node, value_t, node_field); \
                            cmp = compare_fn(key, value_key_fn(value)); \
                            if (cmp > 0) { \
                                /* we're right of the first match. this key can't possibly be smaller. */ \
                                ghost_unreachable(ghost_null); \
                            } else if (cmp < 0) { \
                                node = ghost_iwbt_node_first_child(node); \
                            } else { \
                                match = value; \
                                node = ghost_iwbt_node_last_child(node); \
                            } \
                        } \
                    } \
                } \
                \
                ghost_unreachable(ghost_null); \
            } \
            \
            GHOST_IMPL_FUNCTION_CLOSE
    #endif
    #define ghost_has_GHOST_TMMAP_DEFINE_FIND_AFTER 1
#endif

#endif
