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

#ifndef GHOST_SSET_T_H_INCLUDED
#define GHOST_SSET_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A set of strings.
 *
 * Strings are copied into the set. They are stored both null-terminated and
 * with explicit length in a weight-balanced tree.
 */
typedef /*unspecified*/ ghost_sset_t;
#endif

#ifndef ghost_has_ghost_sset_t
    #ifdef ghost_sset_t
        #define ghost_has_ghost_sset_t 1
    #endif
#endif

/*
 * We require malloc() and free(). We also require ghost_ensure() so we can
 * abort in case malloc() fails.
 *
 * (Technically we could make the set work without free() as long as we disable
 * destroy() and remove(). Probably no point in doing that.)
 */
#ifndef ghost_has_ghost_sset_t
    #include "ghost/malloc/ghost_malloc.h"
    #include "ghost/malloc/ghost_free.h"
    #include "ghost/debug/ghost_ensure.h"
    #if !ghost_has(ghost_malloc) || !ghost_has(ghost_free) || !ghost_has(ghost_ensure)
        #define ghost_has_ghost_sset_t 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_t
    #include "ghost/container/generic/iwbt/ghost_iwbt_t.h"
    typedef struct {
        ghost_iwbt_t tree;
    } ghost_sset_t;
    #define ghost_has_ghost_sset_t 1
#endif

#endif
