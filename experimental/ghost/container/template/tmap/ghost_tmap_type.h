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

#ifndef GHOST_TMAP_TYPE_H_INCLUDED
#define GHOST_TMAP_TYPE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_TMAP_TYPE(prefix)
 *
 * Declares an intrusive weight-balanced tree map type with the given prefix.
 */

/**
 * An intrusive weight-balanced tree map type with the given prefix.
 *
 * The map must be initialized by zeroing (via e.g. GHOST_ZERO_INIT) or by
 * calling ghost_tmap_clear(). The map does not need to be de-initialized
 * (but you are responsible for freeing the contents if necessary.)
 *
 * @see ghost_tmap_clear()
 */
typedef /*unspecified*/ ghost_tmap_t;
#endif

#ifndef ghost_has_GHOST_TMAP_TYPE
    #ifndef GHOST_TMAP_TYPE
        #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
        #define GHOST_TMAP_TYPE(prefix) \
            typedef struct prefix##_t { \
                ghost_iwbt_t tree; \
            } prefix##_t;
    #endif
    #define ghost_has_GHOST_TMAP_TYPE 1
#endif

#endif
