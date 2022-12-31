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

#ifndef GHOST_FALLTHROUGH_H_INCLUDED
#define GHOST_FALLTHROUGH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * @def ghost_fallthrough
 *
 * Tell the compiler not to warn if the given case statement falls through
 * (i.e. it doesn't have a break, continue or return statement.)
 *
 * This can only be used in a null statement (i.e. on its own.) It must be
 * followed by a semicolon and the next case or default label.
 */
#endif

#include "ghost/language/ghost_cplusplus.h"

#ifndef ghost_has_ghost_fallthrough
    #ifdef ghost_fallthrough
        #define ghost_has_ghost_fallthrough 1
    #endif
#endif

/* C23 adds [[__fallthrough__]]
 * We are also supposed to be able to use __has_c_attribute so we may
 * not need to check the C version. */
#ifndef ghost_has_ghost_fallthrough
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
            #define ghost_fallthrough [[__fallthrough__]]
            #define ghost_has_ghost_fallthrough 1
        #endif
    #endif
#endif

/* C++17 adds [[fallthrough]]. */
#ifndef ghost_has_ghost_fallthrough
    #if defined(__cplusplus)
        #if ghost_cplusplus >= 201703L
            #define ghost_fallthrough [[fallthrough]]
            #define ghost_has_ghost_fallthrough 1
        #endif
    #endif
#endif

/* New versions of Clang support [[clang::fallthrough]] in C++11. */
#ifndef ghost_has_ghost_fallthrough
    #ifdef __clang__
        #ifdef __cplusplus
            #include "ghost/language/ghost_cplusplus.h"
            #if ghost_cplusplus >= 201103L
                /* safe syntax is only supported since clang 8.
                 * TODO this version check won't work on e.g. Apple Clang and other variants */
                #if __clang_major__ < 8
                    #define ghost_fallthrough [[clang::fallthrough]]
                    #define ghost_has_ghost_fallthrough 1
                #else
                    #define ghost_fallthrough [[_Clang::__fallthrough__]]
                    #define ghost_has_ghost_fallthrough 1
                #endif
            #endif
        #endif
    #endif
#endif

/* Clang supports __attribute__((fallthrough)) as of version 10. */
#ifndef ghost_has_ghost_fallthrough
    #ifdef __clang__
        /* __has_attribute(fallthrough) doesn't work so we hardcode the version.
         * TODO this version check won't work on e.g. Apple Clang and other variants */
        #if __clang_major__ >= 10
            #define ghost_fallthrough __attribute__((__fallthrough__))
            #define ghost_has_ghost_fallthrough 1
        #endif
    #endif
#endif

/* GCC 7 supports __attribute__((fallthrough)).
 * We assume other __GNUC__ compilers support it (or ignore it) as well. */
#ifndef ghost_has_ghost_fallthrough
    #if defined(__GNUC__) && !defined(__clang__)
        #if __GNUC__ >= 7
            #define ghost_fallthrough __attribute__((__fallthrough__))
            #define ghost_has_ghost_fallthrough 1
        #endif
    #endif
#endif

/* We define it to nothing on older compilers. If you're using this attribute
 * you're probably using a new compiler where it actually works, so you'd be
 * getting proper fallthrough warnings there. Defining it to nothing means at
 * least your code will work on older compilers even if it gives unnecessary
 * warnings. */
#ifndef ghost_has_ghost_fallthrough
    #define ghost_fallthrough /*nothing*/
    #define ghost_has_ghost_fallthrough 1
#endif

#endif
