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

#ifndef GHOST_SIGNAL_H_H_INCLUDED
#define GHOST_SIGNAL_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes <signal.h> if possible.
 */

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* If we're freestanding, we don't have <signal.h>. */
#ifndef ghost_has_ghost_signal_h
    #include "ghost/language/ghost_hosted.h"
    #if !GHOST_HOSTED
        #define ghost_has_ghost_signal_h 0
    #endif
#endif

/* Try to include it. */
#ifndef ghost_has_ghost_signal_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        /* Include <signal.h> if it exists. */
        #if __has_include(<signal.h>)
            #include <signal.h>
            #define ghost_has_ghost_signal_h 1
        #else
            #define ghost_has_ghost_signal_h 0
        #endif
    #else
        /* Assume it exists since we're hosted. */
        #include <signal.h>
        #define ghost_has_ghost_signal_h 1
    #endif
#endif

/* Also include the C++ alternate if it exists. */
#ifdef __cplusplus
    #if ghost_has_ghost_signal_h
        #include "ghost/preprocessor/ghost_has_include.h"
        #if ghost_has(ghost_has_include)
            #if __has_include(<csignal>)
                #include <csignal>
            #endif
        #else
            #include <csignal>
        #endif
    #endif
#endif

#endif
