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

#ifndef GHOST_DLLIMPORT_H_INCLUDED
#define GHOST_DLLIMPORT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_dllimport
 *
 * Declares a function as being imported from a shared (dynamically linked)
 * library.
 *
 * This is typically used in the headers of a shared library. Suppose you are
 * implementing a shared library called "foo" and you want to support both
 * Windows and UNIX systems. Do this in a common header file:
 *
 *     #ifdef FOO_BUILDING_SHAREDLIB
 *         #define FOO_PUBLIC ghost_dllexport
 *     #else
 *         #define FOO_PUBLIC ghost_dllimport
 *     #endif
 *
 * You can then annotate all functions you want to export from your shared
 * library with `FOO_PUBLIC`. When you compile your shared library, define
 * `FOO_BUILDING_SHAREDLIB`. Make sure to also compile your library with
 * `-fvisibility=hidden` on UNIX compilers in order to avoid exporting symbols
 * by default.
 *
 * The result is that when you are building your shared library, your public
 * functions will be declared exported, whereas when a user includes your
 * shared library, they will be declared imported.
 */
#endif

#ifndef ghost_has_ghost_dllimport
    #ifdef ghost_dllimport
        #define ghost_has_ghost_dllimport 1
    #endif
#endif

#ifndef ghost_has_ghost_dllimport
    #if defined(_MSC_VER)
        #define ghost_dllimport __declspec(dllimport)
    #elif defined(__MINGW32__)
        #define ghost_dllimport __attribute__((__visibility__("default"))) __attribute__((__dllimport__))
    #elif defined(__GNUC__)
        #define ghost_dllimport __attribute__((__visibility__("default")))
    #else
        #define ghost_dllimport /*nothing*/
    #endif
    #define ghost_has_ghost_dllimport 1
#endif

#endif
