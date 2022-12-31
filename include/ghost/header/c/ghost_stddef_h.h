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

#ifndef GHOST_STDDEF_H_H_INCLUDED
#define GHOST_STDDEF_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes <stddef.h> if possible.
 *
 * Use ghost_has(ghost_stddef_h) to check whether it was included.
 */

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* Allow the user to override the include path for <stddef.h> */
#ifndef ghost_has_ghost_stddef_h
    #ifdef GHOST_STDDEF_H
        #include GHOST_STDDEF_H
        #define ghost_has_ghost_stddef_h 1
    #endif
#endif

/* <stddef.h> is supposed to exist even in freestanding since forever. It's
 * usually provided by the compiler, not the libc. */
#ifndef ghost_has_ghost_stddef_h

    /* If we can check whether the header exists, we check. */
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<stddef.h>)
            #include <stddef.h>
            #define ghost_has_ghost_stddef_h 1
        #else
            #define ghost_has_ghost_stddef_h 0
        #endif

    /* Otherwise we assume it exists. */
    #else
        #include <stddef.h>
        #define ghost_has_ghost_stddef_h 1
    #endif
#endif

/* Also include the C++ alternate if it exists. */
#ifdef __cplusplus
    #if ghost_has_ghost_stddef_h
        #include "ghost/preprocessor/ghost_has_include.h"
        #if ghost_has(ghost_has_include)
            #if __has_include(<cstddef>)
                #include <cstddef>
            #endif
        #else
            #include <cstddef>
        #endif
    #endif
#endif

#endif
