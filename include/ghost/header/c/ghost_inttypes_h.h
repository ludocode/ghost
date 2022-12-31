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

#ifndef GHOST_INTTYPES_H_H_INCLUDED
#define GHOST_INTTYPES_H_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Includes <inttypes.h> if possible.
 *
 * <inttypes.h> mostly declares format string constants like PRId32,
 * SCNoFAST16, etc.
 */
#endif

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* Allow the user to override the include path */
#ifndef ghost_has_ghost_inttypes_h
    #ifdef GHOST_INTTYPES_H
        #include GHOST_INTTYPES_H
        #define ghost_has_ghost_inttypes_h 1
    #endif
#endif

/* See if we can detect whether it exists. */
#ifndef ghost_has_ghost_inttypes_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<inttypes.h>)
            #include <inttypes.h>
            #define ghost_has_ghost_inttypes_h 1
        #else
            #define ghost_has_ghost_inttypes_h 0
        #endif
    #endif
#endif

/* <inttypes.h> is only available as of C99 and C++11. */
#ifndef ghost_has_ghost_inttypes_h
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus < 201103L
            #define ghost_has_ghost_inttypes_h 0
        #endif
    #elif !defined(__STDC_VERSION__)
        #define ghost_has_ghost_inttypes_h 0
    #endif
#endif

/* It should exist if we're hosted. */
#ifndef ghost_has_ghost_inttypes_h
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include <inttypes.h>
        #define ghost_has_ghost_inttypes_h 1
    #else
        #define ghost_has_ghost_inttypes_h 0
    #endif
#endif

/* Also include the C++ alternate if it exists. */
#ifdef __cplusplus
    #if ghost_has_ghost_inttypes_h
        #include "ghost/preprocessor/ghost_has_include.h"
        #if ghost_has(ghost_has_include)
            #if __has_include(<cinttypes>)
                #include <cinttypes>
            #endif
        #else
            #include <cinttypes>
        #endif
    #endif
#endif

#endif
