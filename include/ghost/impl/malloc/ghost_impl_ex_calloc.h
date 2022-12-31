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

#ifndef GHOST_IMPL_EX_CALLOC_H_INCLUDED
#define GHOST_IMPL_EX_CALLOC_H_INCLUDED

/*
 * @def ghost_impl_ex_calloc()
 *
 * A non-synthetic wrapper for a system or custom calloc() that allocates even
 * when either or both arguments are 0.
 *
 * Don't call or override this; use ghost_calloc() instead.
 */

#if defined(ghost_has_ghost_impl_ex_calloc) || defined(ghost_impl_ex_calloc)
    #error "ghost_impl_ex_calloc() cannot be overridden or disabled. Override ghost_calloc() or define GHOST_MALLOC_SYSTEM to 0 instead."
#endif

/* ghost_calloc() override is handled in ghost_malloc_system.h. */
#include "ghost/malloc/ghost_malloc_system.h"

/* If ghost_calloc() is overridden, use it for ghost_impl_ex_calloc() so
 * that other malloc functions can be synthesized from it. */
#ifdef ghost_has_ghost_calloc
    #if ghost_has_ghost_calloc
        #define ghost_impl_ex_calloc ghost_calloc
        #define ghost_has_ghost_impl_ex_calloc 1
    #endif
#endif

/* We only wrap system functions if GHOST_MALLOC_SYSTEM is enabled. */
#ifndef ghost_has_ghost_impl_ex_calloc
    #include "ghost/malloc/ghost_malloc_system.h"
    #if !GHOST_MALLOC_SYSTEM
        #define ghost_has_ghost_impl_ex_calloc 0
    #endif
#endif

/* We also require <stdlib.h> in a hosted environment. */
#ifndef ghost_has_ghost_impl_ex_calloc
    #include "ghost/language/ghost_hosted.h"
    #if !GHOST_HOSTED
        #define ghost_has_ghost_impl_ex_calloc 0
    #endif
#endif
#ifndef ghost_has_ghost_impl_ex_calloc
    #include "ghost/header/c/ghost_stdlib_h.h"
    #if !ghost_has(ghost_stdlib_h)
        #define ghost_has_ghost_impl_ex_calloc 0
    #endif
#endif

/* On platforms that allocate on 0, we can pass it through directly. */

/* Windows, macOS, BSDs */
#ifndef ghost_has_ghost_impl_ex_calloc
    #ifdef _WIN32
        #ifdef __cplusplus
            #define ghost_impl_ex_calloc ::calloc
        #else
            #define ghost_impl_ex_calloc calloc
        #endif
        #define ghost_has_ghost_impl_ex_calloc 1
    #endif
#endif

/* Linux libcs (those I've tested) */
#ifndef ghost_has_ghost_impl_ex_calloc
    #ifdef __linux__
        #include "ghost/detect/ghost_glibc.h"
        #include "ghost/detect/ghost_musl.h"
        #if GHOST_GLIBC || GHOST_MUSL
            #ifdef __cplusplus
                #define ghost_impl_ex_calloc ::calloc
            #else
                #define ghost_impl_ex_calloc calloc
            #endif
            #define ghost_has_ghost_impl_ex_calloc 1
        #endif
    #endif
#endif

/* Otherwise we can't confirm that the system calloc() allocates on size 0. */
#ifndef ghost_has_ghost_impl_ex_calloc
    #define ghost_has_ghost_impl_ex_calloc 0
#endif

#endif
