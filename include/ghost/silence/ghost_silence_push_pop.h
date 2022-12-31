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

#ifndef GHOST_SILENCE_PUSH_POP_H_INCLUDED
#define GHOST_SILENCE_PUSH_POP_H_INCLUDED

/* We define push and pop together since one is useless without the other. */

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_PUSH _Pragma(diagnostic push)
 *
 * Stores the current state of all warnings for a future GHOST_SILENCE_POP.
 *
 * @see GHOST_SILENCE_POP
 */

/**
 * @def GHOST_SILENCE_POP _Pragma(diagnostic pop)
 *
 * Restores the state of all warnings stored by the last unpopped
 * GHOST_SILENCE_PUSH.
 *
 * @see GHOST_SILENCE_PUSH
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_PUSH
    #ifdef GHOST_SILENCE_PUSH
        #define ghost_has_GHOST_SILENCE_PUSH 1
    #endif
#endif
#ifndef ghost_has_GHOST_SILENCE_POP
    #ifdef GHOST_SILENCE_POP
        #define ghost_has_GHOST_SILENCE_POP 1
    #endif
#endif

#if defined(__GNUC__) && !defined(__CPARSER__)
    /* Diagnostic push is not supported before GCC 4.6. */
    #if defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
        #ifndef ghost_has_GHOST_SILENCE_PUSH
            #define GHOST_SILENCE_PUSH _Pragma("GCC diagnostic push")
            #define ghost_has_GHOST_SILENCE_PUSH 1
        #endif
        #ifndef ghost_has_GHOST_SILENCE_POP
            #define GHOST_SILENCE_POP _Pragma("GCC diagnostic pop")
            #define ghost_has_GHOST_SILENCE_POP 1
        #endif
    #endif
#endif

#ifdef _MSC_VER
    /* VS2017 and earlier supports only __pragma, not _Pragma. We always use
     * __pragma for MSVC. */
    #ifndef ghost_has_GHOST_SILENCE_PUSH
        #define GHOST_SILENCE_PUSH __pragma(warning(push))
        #define ghost_has_GHOST_SILENCE_PUSH 1
    #endif
    #ifndef ghost_has_GHOST_SILENCE_POP
        #define GHOST_SILENCE_POP __pragma(warning(pop))
        #define ghost_has_GHOST_SILENCE_POP 1
    #endif
#endif

/* If we can't push warnings, we don't have these. We don't want to define them
 * to nothing because we don't want users to silence warnings without at least
 * being aware that they can't pop them. */
#ifndef ghost_has_GHOST_SILENCE_PUSH
    #define ghost_has_GHOST_SILENCE_PUSH 0
#endif
#ifndef ghost_has_GHOST_SILENCE_POP
    #define ghost_has_GHOST_SILENCE_POP 0
#endif

#endif
