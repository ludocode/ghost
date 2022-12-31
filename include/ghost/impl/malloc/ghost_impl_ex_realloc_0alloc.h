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

#ifndef GHOST_IMPL_EX_REALLOC_0ALLOC_H_INCLUDED
#define GHOST_IMPL_EX_REALLOC_0ALLOC_H_INCLUDED

/*
 * @def ghost_impl_ex_realloc_0alloc()
 *
 * A non-synthetic wrapper for a system or custom realloc() function that has
 * the behaviour of the BSDs and macOS: it always tries to return an allocation
 * when size is 0.
 *
 * Don't call or override this; use ghost_realloc_0alloc() instead.
 */

#if defined(ghost_has_ghost_impl_ex_realloc_0alloc) || defined(ghost_impl_ex_realloc_0alloc)
    #error "ghost_impl_ex_realloc_0alloc() cannot be overridden or disabled. Override ghost_realloc_0alloc() or define GHOST_MALLOC_SYSTEM=0 instead."
#endif

/* ghost_realloc_0alloc() override is handled in ghost_malloc_system.h. */
#include "ghost/malloc/ghost_malloc_system.h"

/* If ghost_realloc_0alloc() is overridden, use it for ghost_impl_ex_realloc_0alloc()
 * so that other malloc functions can be synthesized from it. */
#ifdef ghost_has_ghost_realloc_0alloc
    #if ghost_has_ghost_realloc_0alloc
        #define ghost_impl_ex_realloc_0alloc ghost_realloc_0alloc
        #define ghost_has_ghost_impl_ex_realloc_0alloc 1
    #endif
#endif

/* We only wrap system functions if GHOST_MALLOC_SYSTEM is enabled. */
#ifndef ghost_has_ghost_impl_ex_realloc_0alloc
    #include "ghost/malloc/ghost_malloc_system.h"
    #if !GHOST_MALLOC_SYSTEM
        #define ghost_has_ghost_impl_ex_realloc_0alloc 0
    #endif
#endif

/* We require <stdlib.h> in a hosted environment. */
#ifndef ghost_has_ghost_impl_ex_realloc_0alloc
    #include "ghost/language/ghost_hosted.h"
    #if !GHOST_HOSTED
        #define ghost_has_ghost_impl_ex_realloc_0alloc 0
    #endif
#endif
#ifndef ghost_has_ghost_impl_ex_realloc_0alloc
    #include "ghost/header/c/ghost_stdlib_h.h"
    #if !ghost_has(ghost_stdlib_h)
        #define ghost_has_ghost_impl_ex_realloc_0alloc 0
    #endif
#endif

/* The BSDs and macOS have this behaviour. */
#ifndef ghost_has_ghost_impl_ex_realloc_0alloc
    #if defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || \
            defined(__OpenBSD__) || defined(__DragonFly__)
        #ifdef __cplusplus
            #define ghost_impl_ex_realloc_0alloc ::realloc
        #else
            #define ghost_impl_ex_realloc_0alloc realloc
        #endif
        #define ghost_has_ghost_impl_ex_realloc_0alloc 1
    #endif
#endif

/* musl libc also appears to have this behaviour at least with its new
 * allocator. I'm not sure about the old one, or why musl has two, or how it
 * gets to be configured, or whether we can detect the difference. It's safer
 * to just wrap it. */

/* Otherwise we have no system ghost_realloc_0alloc(). */
#ifndef ghost_has_ghost_impl_ex_realloc_0alloc
    #define ghost_has_ghost_impl_ex_realloc_0alloc 0
#endif

#endif
