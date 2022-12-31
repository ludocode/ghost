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

#ifndef GHOST_STDIO_H_H_INCLUDED
#define GHOST_STDIO_H_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Includes <stdio.h> if possible.
 *
 * <stdio.h> declares input/output functions: files, string formatting, etc.
 */
#endif

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* Allow the user to override the include path */
#ifndef ghost_has_ghost_stdio_h
    #ifdef GHOST_STDIO_H
        #include GHOST_STDIO_H
        #define ghost_has_ghost_stdio_h 1
    #endif
#endif

/* See if we can detect whether it exists. */
#ifndef ghost_has_ghost_stdio_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<stdio.h>)
            #include <stdio.h>
            #define ghost_has_ghost_stdio_h 1
        #else
            #define ghost_has_ghost_stdio_h 0
        #endif
    #endif
#endif

/* It should exist if we're hosted. */
#ifndef ghost_has_ghost_stdio_h
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include <stdio.h>
        #define ghost_has_ghost_stdio_h 1
    #else
        #define ghost_has_ghost_stdio_h 0
    #endif
#endif

/* Also include the C++ alternate if it exists. */
#ifdef __cplusplus
    #if ghost_has_ghost_stdio_h
        #include "ghost/preprocessor/ghost_has_include.h"
        #if ghost_has(ghost_has_include)
            #if __has_include(<cstdio>)
                #include <cstdio>
            #endif
        #else
            #include <cstdio>
        #endif
    #endif
#endif

#endif
