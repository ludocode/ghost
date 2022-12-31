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

#ifndef GHOST_MAYBE_UNUSED_H_INCLUDED
#define GHOST_MAYBE_UNUSED_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_maybe_unused [[maybe_unused]]
 *
 * Declares that a variable or function may not be used intentionally.
 *
 * This prevents the compiler from warning about an unused symbol.
 */
#endif

#include "ghost/language/ghost_cplusplus.h"

/* C++17 adds [[maybe_unused]] */
#ifndef ghost_has_ghost_maybe_unused
    #if defined(__cplusplus)
        #if ghost_cplusplus >= 201703L
            #define ghost_maybe_unused [[maybe_unused]]
            #define ghost_has_ghost_maybe_unused 1
        #endif
    #endif
#endif

/* GNU C has __attribute__((unused)) */
#ifndef ghost_has_ghost_maybe_unused
    #if defined(__GNUC__)
        #define ghost_maybe_unused __attribute__((__unused__))
        #define ghost_has_ghost_maybe_unused 1
    #endif
#endif

/* Otherwise we assume it's harmless to ignore this. */
#ifndef ghost_has_ghost_maybe_unused
    #define ghost_maybe_unused /*nothing*/
    #define ghost_has_ghost_maybe_unused 1
#endif

#endif
