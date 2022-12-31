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

#ifndef GHOST_STDINT_H_H_INCLUDED
#define GHOST_STDINT_H_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Includes <stdint.h> if possible.
 *
 * <stdint.h> defines fixed width types like int32_t and their limits like
 * INT32_MAX.
 */
#endif

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* Allow the user to override the include path for <stdint.h> */
#ifndef ghost_has_ghost_stdint_h
    #ifdef GHOST_STDINT_H
        #include GHOST_STDINT_H
        #define ghost_has_ghost_stdint_h 1
    #endif
#endif

/* See if we can detect whether it exists. */
#ifndef ghost_has_ghost_stdint_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<stdint.h>)
            #include <stdint.h>
            #define ghost_has_ghost_stdint_h 1
        #else
            #define ghost_has_ghost_stdint_h 0
        #endif
    #endif
#endif

/* <stdint.h> is supposed to exist even in freestanding but it's only
 * officially available in C99 and C++11. We assume that if the compiler
 * declares C99 or C++11 support, the header will exist. */
#ifndef ghost_has_ghost_stdint_h
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #include <stdint.h>
            #define ghost_has_ghost_stdint_h 1
        #endif
    #elif defined(__STDC_VERSION__)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 199901L
            #include <stdint.h>
            #define ghost_has_ghost_stdint_h 1
        #endif
    #endif
#endif

/* <stdint.h> is usually available from most libcs and from freestanding
 * compilers even when compiling under older language standards. Instead of
 * listing platforms where it exists, we prefer to assume it exists and list
 * platforms where it doesn't. (Note that this is the opposite of <inttypes.h>
 * where we assume it doesn't exist in C89/C++98.) */
#ifndef ghost_has_ghost_stdint_h
    #ifdef _MSC_VER
        #if _MSC_VER < 1900 /* Visual Studio before 2015 */
            #define ghost_has_ghost_stdint_h 0
        #endif
    #endif
#endif

/* Otherwise we assume it exists. As usual, if Ghost is incorrectly detecting
 * that your platform has this, just pre-define ghost_has_ghost_stdint_h to 0. */
#ifndef ghost_has_ghost_stdint_h
    #include <stdint.h>
    #define ghost_has_ghost_stdint_h 1
#endif

/* Also include the C++ alternate if it exists. */
#ifdef __cplusplus
    #if ghost_has_ghost_stdint_h
        #include "ghost/preprocessor/ghost_has_include.h"
        #if ghost_has(ghost_has_include)
            #if __has_include(<cstdint>)
                #include <cstdint>
            #endif
        #else
            #include <cstdint>
        #endif
    #endif
#endif

#endif
