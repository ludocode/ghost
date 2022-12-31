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

#ifndef GHOST_HIDDEN_PUSH_POP_H_INCLUDED
#define GHOST_HIDDEN_PUSH_POP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_HIDDEN_PUSH
 *
 * Declares all subsequent functions as being hidden from the dynamic linker
 * until GHOST_HIDDEN_POP.
 *
 * This is the default on Windows. On UNIX systems it is recommended to build
 * with `-fvisibility=hidden` to make this the default. You can use this if you
 * want a specific set of symbols hidden regardless of the compiler's
 * visibility setting.
 *
 * In particular, this is useful for wrapping functions that may or may not be
 * static depending on available compiler features (like the `ghost_header_*`
 * attributes) since compiler warnings are issued if a static function is
 * directly annotated ghost_hidden.
 *
 * @see GHOST_HIDDEN_POP
 * @see ghost_hidden
 */

/**
 * @def GHOST_HIDDEN_POP
 *
 * Ends a previous GHOST_HIDDEN_PUSH.
 *
 * @see GHOST_HIDDEN_PUSH
 */
#endif

#ifndef ghost_has_GHOST_HIDDEN_PUSH
    #ifdef GHOST_HIDDEN_PUSH
        #define ghost_has_GHOST_HIDDEN_PUSH 1
    #endif
#endif
#ifndef ghost_has_GHOST_HIDDEN_POP
    #ifdef GHOST_HIDDEN_POP
        #define ghost_has_GHOST_HIDDEN_POP 1
    #endif
#endif

/* GNUC compilers are supposed to implement _Pragma(GCC visibility push(...)).
 * (cparser doesn't support _Pragma.) */
#if defined(__GNUC__) && !defined(__CPARSER__)
    #ifdef GHOST_IMPL_HIDDEN_PUSH_PRAGMA
        #error
    #endif

    #include "ghost/detect/ghost_gcc.h"
    #if GHOST_GCC
        /* GCC visibility push has been around since at least GCC 4.2. */
        #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
            #define GHOST_IMPL_HIDDEN_PUSH_PRAGMA
        #endif
    #else
        /* Assume the compiler supports it */
        #define GHOST_IMPL_HIDDEN_PUSH_PRAGMA
    #endif

    #ifdef GHOST_IMPL_HIDDEN_PUSH_PRAGMA
        #undef GHOST_IMPL_HIDDEN_PUSH_PRAGMA
        #ifndef ghost_has_GHOST_HIDDEN_PUSH
            #define GHOST_HIDDEN_PUSH _Pragma("GCC visibility push(hidden)")
            #define ghost_has_GHOST_HIDDEN_PUSH 1
        #endif
        #ifndef ghost_has_GHOST_HIDDEN_POP
            #define GHOST_HIDDEN_POP _Pragma("GCC visibility pop")
            #define ghost_has_GHOST_HIDDEN_POP 1
        #endif
    #endif
#endif

#ifndef ghost_has_GHOST_HIDDEN_PUSH
    #define GHOST_HIDDEN_PUSH /*nothing*/
    #define ghost_has_GHOST_HIDDEN_PUSH 1
#endif
#ifndef ghost_has_GHOST_HIDDEN_POP
    #define GHOST_HIDDEN_POP /*nothing*/
    #define ghost_has_GHOST_HIDDEN_POP 1
#endif

#endif
