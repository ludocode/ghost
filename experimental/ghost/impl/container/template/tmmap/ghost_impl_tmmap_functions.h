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

#ifndef GHOST_IMPL_TMMAP_FUNCTIONS_H_INCLUDED
#define GHOST_IMPL_TMMAP_FUNCTIONS_H_INCLUDED

#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_any.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_clear.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_count.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_find_after.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_find_before.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_find_first.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_find_last.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_first.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_insert_after.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_insert_before.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_insert_first.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_insert_last.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_is_empty.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_last.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_next.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_next_match.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_previous.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_previous_match.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_remove.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_remove_all_with_key.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_remove_any.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_remove_first.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_remove_last.h"
#include "ghost/impl/container/template/tmmap/ghost_impl_tmmap_swap.h"

/* Declare functions */
#ifdef GHOST_IMPL_TMMAP_DECLARE_FUNCTIONS
    #error
#endif
#define GHOST_IMPL_TMMAP_DECLARE_FUNCTIONS(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_ANY                 (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_CLEAR               (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_COUNT               (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_FIND_AFTER          (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_FIND_BEFORE         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_FIND_FIRST          (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_FIND_LAST           (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_FIRST               (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_INSERT_AFTER        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_INSERT_BEFORE       (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_INSERT_FIRST        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_INSERT_LAST         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_IS_EMPTY            (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_LAST                (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_NEXT                (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_NEXT_MATCH          (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_PREVIOUS            (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_PREVIOUS_MATCH      (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_REMOVE              (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_REMOVE_ALL_WITH_KEY (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_REMOVE_ANY          (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_REMOVE_FIRST        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_REMOVE_LAST         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMMAP_DECLARE_SWAP                (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)

/* Define functions */
#ifdef GHOST_IMPL_TMMAP_DEFINE_FUNCTIONS
    #error
#endif
#define GHOST_IMPL_TMMAP_DEFINE_FUNCTIONS(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_ANY                 (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_CLEAR               (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_COUNT               (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_FIND_AFTER          (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_FIND_BEFORE         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_FIND_FIRST          (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_FIND_LAST           (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_FIRST               (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_INSERT_AFTER        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_INSERT_BEFORE       (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_INSERT_FIRST        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_INSERT_LAST         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_IS_EMPTY            (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_LAST                (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_NEXT                (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_NEXT_MATCH          (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_PREVIOUS            (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_PREVIOUS_MATCH      (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_REMOVE              (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_REMOVE_ALL_WITH_KEY (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_REMOVE_ANY          (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_REMOVE_FIRST        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_REMOVE_LAST         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMMAP_DEFINE_SWAP                (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib)

#endif
