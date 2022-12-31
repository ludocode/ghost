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

#ifndef GHOST_DLLEXPORT_H_INCLUDED
#define GHOST_DLLEXPORT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_dllexport
 *
 * Declares a function as being exported from the shared (dynamically linked)
 * library that is currently being built.
 *
 * See ghost_dllimport for usage instructions.
 *
 * @see ghost_dllimport
 */
#endif

#ifndef ghost_has_ghost_dllexport
    #ifdef ghost_dllexport
        #define ghost_has_ghost_dllexport 1
    #endif
#endif

#ifndef ghost_has_ghost_dllexport
    #if defined(_MSC_VER)
        #define ghost_dllexport __declspec(dllexport)
    #elif defined(__TINYC__) && defined(_WIN32)
        #define ghost_dllexport __attribute__((__dllexport__))
    #elif defined(__MINGW32__)
        #define ghost_dllexport __attribute__((__visibility__("default"))) __attribute__((__dllexport__))
    #elif defined(__GNUC__)
        /* TODO: should this also have __attribute__((__externally_visible__))? */
        #define ghost_dllexport __attribute__((__visibility__("default")))
    #else
        #define ghost_dllexport /*nothing*/
    #endif
    #define ghost_has_ghost_dllexport 1
#endif

#endif
