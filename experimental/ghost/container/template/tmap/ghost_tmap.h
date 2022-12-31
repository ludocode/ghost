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

#ifndef GHOST_TMAP_H_INCLUDED
#define GHOST_TMAP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMAP(prefix, key_t, value_t, node_field, value_key_fn, compare_fn)
 *
 * Declares and defines an intrusive weight-balanced tree map.
 *
 * This declares the map type and declares and defines all functions with
 * Ghost's header linkage, suitable for use in a header or source file.
 *
 * This defines functions in the same way Ghost does when not using
 * GHOST_MANUAL_DEFS. Small functions are declared `ghost_header_inline` which
 * generally means `static inline`. Large functions are declared
 * `ghost_header_function` which generally means selectany/comdat/weak, this
 * way only one definition will exist in the file link.
 *
 * This minimizes code bloat automatically with no manual effort required. If
 * you're unsure of what to use, use this.
 */
#endif

#ifndef ghost_has_GHOST_TMAP
    #ifndef GHOST_TMAP
        #include "ghost/container/template/tmap/ghost_tmap_type.h"
        #define GHOST_TMAP(prefix, key_t, value_t, node_field, value_key_fn, compare_fn) \
            GHOST_TMAP_TYPE(prefix) \
            GHOST_TMAP_HEADER(prefix, key_t, value_t, node_field, value_key_fn, compare_fn)
    #endif
    #define ghost_has_GHOST_TMAP 1
#endif

#endif
