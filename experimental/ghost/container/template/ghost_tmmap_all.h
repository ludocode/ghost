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

#ifndef GHOST_TMMAP_ALL_H_INCLUDED
#define GHOST_TMMAP_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Includes the various templates for instantiating an intrusive
 * weight-balanced tree map.
 *
 * @see GHOST_TMMAP()
 * @see GHOST_TMMAP_TYPE()
 * @see GHOST_TMMAP_HEADER()
 * @see GHOST_TMMAP_STATIC()
 * @see GHOST_TMMAP_DECLARE()
 * @see GHOST_TMMAP_DEFINE()
 */

/*
 * You can instantiate the type and function definitions separately, for
 * example if you are storing the map within your value to create nested maps.
 *
 * Use in four ways:
 *
 * - GHOST_TMMAP() -- everything automatic (same as next)
 * - GHOST_TMMAP_TYPE() + GHOST_TMMAP_HEADER() -- separate type and functions, otherwise automatic, can be used in header file (lets you nest maps of a given type)
 * - GHOST_TMMAP_TYPE() + GHOST_TMMAP_STATIC() -- separate type and functions, everything static, use for only one translation unit
 * - GHOST_TMMAP_TYPE() + GHOST_TMMAP_DECLARE() in header, GHOST_TMMAP_DEFINE() in one translation unit -- manual emission
 *
 * HEADER uses ghost_impl_inline and ghost_impl_function for automatic header-only libs
 * STATIC uses static inline and static
 * DECLARE/DEFINE uses emit/noemit for inlines
 *
 * TODO move above description to README.md
 */

/* TODO
GHOST_TMMAP() // everything with header linkage
GHOST_TMMAP_TYPE() // define the type
GHOST_TMMAP_HEADER() // declare and define functions with header linkage for a header file
GHOST_TMMAP_STATIC() // declare and define all functions static (for use in a single translation unit)
GHOST_TMMAP_DECLARE() // declare prototypes and define inline functions
GHOST_TMMAP_DEFINE() // define non-inline functions
*/
#endif

/*TODO clean up docs*/
/*
 * @file
 *
 * An intrusive weight-balanced binary tree multimap template.
 *
 * Instantiate it like this:
 *
 *     GHOST_TMMAP(prefix, key_t, value_t, node_field, value_key_fn, compare_fn)
 *
 * The parameters are:
 *
 *     - prefix: The name to use as a prefix for the type and for all functions.
 *     - key_t: The key type
 *     - value_t: The value type, containing the key and node struct
 *     - node_field: The name of the ghost_iwbt_node_t field in value_t
 *     - value_key_fn: A function or macro that gets the key for a value
 *     - compare_fn: A function or macro that compares a key to a value
 *
 * The value_key_fn function gets the key for a value. It must match the
 * following prototype:
 *
 *     key_t value_key_fn(value_t* value, prefix##_t* map);
 *
 * The compare expression compares keys. It must return less than 0 if left
 * comes before right, greater than 0 if right comes before left, and 0 if they
 * are equal. It must match the following prototype:
 *
 *     int value_compare_fn(key_t left, key_t right, prefix##_t* map);
 *
 * The map is passed as an additional context to both callbacks. If you
 * need a context for your callbacks, put the map inside your context and use
 * ghost_container_of().
 *
 * This defines a type prefix##_t which represents your map, along with
 * functions like prefix##_clear(), prefix##_insert(), prefix##_find(), etc.
 */

/* The tmmap is implemented with our type-erased iwbt tree. This
 * significantly reduces the amount of templated code. Almost all of the
 * tmmap functions are simple inline wrappers over the tree which do type
 * conversions to give it a fully typed key-value API. */

#include "ghost/container/template/tmmap/ghost_tmmap.h"
#include "ghost/container/template/tmmap/ghost_tmmap_type.h"
#include "ghost/container/template/tmmap/ghost_tmmap_header.h"
#include "ghost/container/template/tmmap/ghost_tmmap_static.h"
#include "ghost/container/template/tmmap/ghost_tmmap_declare.h"
#include "ghost/container/template/tmmap/ghost_tmmap_define.h"

#endif
