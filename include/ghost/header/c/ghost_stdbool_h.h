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

#ifndef GHOST_STDBOOL_H_H_INCLUDED
#define GHOST_STDBOOL_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes <stdbool.h> if possible.
 *
 * Use ghost_has(ghost_stdbool_h) to check whether it was included.
 */

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* <stdbool.h> is supposed to exist even in freestanding. It was added as of
 * C99, but it's often available as an extension in older language standards. */

/* If we can check whether the header exists, we check. */
#ifndef ghost_has_ghost_stdbool_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<stdbool.h>)
            #include <stdbool.h>
            #define ghost_has_ghost_stdbool_h 1
        #else
            #define ghost_has_ghost_stdbool_h 0
        #endif
    #endif
#endif

/* <stdbool.h> is supposed to exist even in freestanding but it's only
 * officially available in C99 and C++11. We assume that if the compiler
 * declares C99 or C++11 support, the header will exist. */
#ifndef ghost_has_ghost_stdbool_h
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #include <stdbool.h>
            #define ghost_has_ghost_stdbool_h 1
        #endif
    #elif defined(__STDC_VERSION__)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 199901L
            #include <stdbool.h>
            #define ghost_has_ghost_stdbool_h 1
        #endif
    #endif
#endif

/* VS2012 and earlier does not have this. (VS2013 does support <stdbool.h> even
 * in ANSI C, and even though it does not support <stdint.h>.) */
#ifndef ghost_has_ghost_stdbool_h
    #ifdef _MSC_VER
        #if _MSC_VER < 1800
            #define ghost_has_ghost_stdbool_h 0
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_stdbool_h
    /* Otherwise, for now, we assume it exists. C99 has been around for decades
     * so it's probably better to just list any platforms where it doesn't
     * exist above this. */
    #include <stdbool.h>
    #define ghost_has_ghost_stdbool_h 1
#endif

#endif
