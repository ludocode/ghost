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

#ifndef GHOST_UCHAR_H_H_INCLUDED
#define GHOST_UCHAR_H_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Includes <uchar.h> if possible.
 *
 * <uchar.h> defines a few types like `mbstate_t` and `uchar<N>_t` as well as
 * UTF conversion functions.
 */
#endif

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* Allow the user to override the include path for <uchar.h> */
#ifndef ghost_has_ghost_uchar_h
    #ifdef GHOST_UHCAR_H
        #include GHOST_UHCAR_H
        #define ghost_has_ghost_uchar_h 1
    #endif
#endif

/*
 * See if we can detect whether it exists. This may backport features (like
 * char8_t) to older language standards.
 *
 * It might also not be allowed to be included in older language standards even
 * if the file exists. If we find any such platforms we'll have to disable them
 * here.
 */
#ifndef ghost_has_ghost_uchar_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<uchar.h>)
            #include <uchar.h>
            #define ghost_has_ghost_uchar_h 1
        #else
            #define ghost_has_ghost_uchar_h 0
        #endif
    #endif
#endif

/* <uchar.h> exists as of C11 and C++11. It's not required to exist in
 * freestanding. */
#ifndef ghost_has_ghost_uchar_h
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #include <uchar.h>
            #define ghost_has_ghost_uchar_h 1
        #endif
    #elif defined(__STDC_VERSION__)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 201112L
            #include <uchar.h>
            #define ghost_has_ghost_uchar_h 1
        #endif
    #endif
#endif

/* Otherwise we don't believe it exists. */
#ifndef ghost_has_ghost_uchar_h
    #define ghost_has_ghost_uchar_h 0
#endif

/* Also include the C++ alternate if it exists. */
#ifdef __cplusplus
    #if ghost_has_ghost_uchar_h
        #include "ghost/preprocessor/ghost_has_include.h"
        #if ghost_has(ghost_has_include)
            #if __has_include(<cuchar>)
                #include <cuchar>
            #endif
        #else
            /* <cuchar> was added in C++11 but many compilers that claim to
             * support C++11 don't have it. For example it wasn't added to
             * libstdc++ until GCC 6. For now if we don't have __has_include
             * we skip it. */
        #endif
    #endif
#endif

#endif
