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

#ifndef GHOST_SSIZE_MIN_H_INCLUDED
#define GHOST_SSIZE_MIN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SSIZE_MIN SIZE_MIN
 *
 * The minimum value of ghost_ssize_t.
 */
#endif

/* If we don't have ghost_ssize_t, we don't have a min. */
#ifndef ghost_has_GHOST_SSIZE_MIN
    #include "ghost/type/ssize_t/ghost_ssize_t.h"
    #if !ghost_has_ghost_ssize_t
        #define ghost_has_GHOST_SSIZE_MIN 0
    #endif
#endif

/* There's no official SSIZE_MIN. Technically ssize_t only has to support
 * a minimum value of -1 but we're interested in the real minimum value of the
 * type. Ghost assumes two's complement so we'll define it based on
 * GHOST_SSIZE_MAX. */
#ifndef ghost_has_GHOST_SSIZE_MIN
    #include "ghost/type/ssize_t/ghost_ssize_max.h"
    #ifdef GHOST_SSIZE_MAX
        #include "ghost/impl/ghost_impl_assumptions.h"
        #if GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
            #define GHOST_SSIZE_MIN (-GHOST_SSIZE_MAX - 1)
        #endif
    #endif
#endif

/* Otherwise we don't have it. We'd rather not define it than define it to -1. */
#ifndef ghost_has_GHOST_SSIZE_MIN
    #define ghost_has_GHOST_SSIZE_MIN 0
#endif

#endif
