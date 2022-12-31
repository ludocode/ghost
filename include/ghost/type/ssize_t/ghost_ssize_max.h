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

#ifndef GHOST_SSIZE_MAX_H_INCLUDED
#define GHOST_SSIZE_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SSIZE_MAX SIZE_MAX
 *
 * The maximum value of ghost_ssize_t.
 */
#endif

/* SSIZE_MAX is usually in <limits.h>. */
#include "ghost/header/c/ghost_limits_h.h"

#ifndef ghost_has_GHOST_SSIZE_MAX
    #ifdef GHOST_SSIZE_MAX
        #define ghost_has_GHOST_SSIZE_MAX 1
    #endif
#endif

/* If we don't have ghost_ssize_t, we don't have a max. */
#ifndef ghost_has_GHOST_SSIZE_MAX
    #include "ghost/type/ssize_t/ghost_ssize_t.h"
    #if !ghost_has_ghost_ssize_t
        #define ghost_has_GHOST_SSIZE_MAX 0
    #endif
#endif

/* SSIZE_MAX is in POSIX but it requires feature-test macros to be defined. */
#ifndef ghost_has_GHOST_SSIZE_MAX
    #ifdef SSIZE_MAX
        #define GHOST_SSIZE_MAX SSIZE_MAX
        #define ghost_has_GHOST_SSIZE_MAX 1
    #endif
#endif

/* Otherwise if we've figured out the width and it's the same as size_t we try
 * to define it based on SIZE_MAX. */
#ifndef ghost_has_GHOST_SSIZE_MAX
    #include "ghost/type/ssize_t/ghost_ssize_width.h"
    #include "ghost/type/size_t/ghost_size_width.h"
    #include "ghost/type/size_t/ghost_size_max.h"
    #if defined(GHOST_SSIZE_WIDTH) && defined(GHOST_SIZE_WIDTH) && defined(GHOST_SIZE_MAX)
        #if GHOST_SIZE_WIDTH == GHOST_SSIZE_WIDTH
            #define GHOST_SSIZE_MAX (GHOST_SIZE_MAX / 2)
            #define ghost_has_GHOST_SSIZE_MAX 1
        #endif
    #endif
#endif

/* Otherwise we don't have it. We could compare it to the widths of int, long,
 * etc. but for now there's no point. */
#ifndef ghost_has_GHOST_SSIZE_MAX
    #define ghost_has_GHOST_SSIZE_MAX 0
#endif

#endif
