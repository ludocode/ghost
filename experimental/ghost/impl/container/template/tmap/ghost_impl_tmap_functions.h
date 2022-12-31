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

#ifndef GHOST_IMPL_TMAP_FUNCTIONS_H_INCLUDED
#define GHOST_IMPL_TMAP_FUNCTIONS_H_INCLUDED

#include "ghost/impl/container/template/tmap/ghost_impl_tmap_any.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_clear.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_count.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_find.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_find_before.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_first.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_insert.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_is_empty.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_last.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_next.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_previous.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_remove.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_remove_any.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_remove_key.h"
#include "ghost/impl/container/template/tmap/ghost_impl_tmap_swap.h"

/* Declare functions */
#ifdef GHOST_IMPL_TMAP_DECLARE_FUNCTIONS
    #error
#endif
#define GHOST_IMPL_TMAP_DECLARE_FUNCTIONS(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_ANY          (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_CLEAR        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_COUNT        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_FIND         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_FIND_BEFORE  (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_FIRST        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_INSERT       (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_IS_EMPTY     (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_LAST         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_NEXT         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_PREVIOUS     (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_REMOVE       (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_REMOVE_ANY   (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_REMOVE_KEY   (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib) \
    GHOST_TMAP_DECLARE_SWAP         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib, inline_attrib)

/* Define functions */
#ifdef GHOST_IMPL_TMAP_DEFINE_FUNCTIONS
    #error
#endif
#define GHOST_IMPL_TMAP_DEFINE_FUNCTIONS(prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_ANY          (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_CLEAR        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_COUNT        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_FIND         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_FIND_BEFORE  (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_FIRST        (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_INSERT       (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_IS_EMPTY     (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_LAST         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_NEXT         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_PREVIOUS     (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_REMOVE       (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_REMOVE_ANY   (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_REMOVE_KEY   (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib) \
    GHOST_TMAP_DEFINE_SWAP         (prefix, key_t, value_t, node_field, value_key_fn, compare_fn, noninline_attrib)

#endif
