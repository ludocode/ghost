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

#ifndef GHOST_WINDOWS_H_H_INCLUDED
#define GHOST_WINDOWS_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes <Windows.h> lean and mean (with some safety wrapping around it) if
 * it's available.
 *
 * <Windows.h> declares most of the Win32 API for Windows.
 *
 * Like all Ghost headers, you can include this header on any platform. Check
 * `#if ghost_has(ghost_windows_h)` to determine whether <Windows.h> was
 * actually included.
 *
 * We define only WIN32_LEAN_AND_MEAN and NOMINMAX to give a good balance
 * between safety, portability and compile-time overhead. We also undefine them
 * afterwards to avoid namespace pollution and to prevent a later include of
 * <Windows.h> from being inadvertently lean-and-mean.
 *
 * We don't define UNICODE or STRICT even though you should almost certainly be
 * using them. These macros need to be defined project-wide as part of the
 * buildsystem. They are defined by default for new Visual Studio projects,
 * probably CMake generated projects, etc.
 *
 * Note that the GDI+ headers expect min and max macros which are disabled by
 * NOMINMAX. Use the separate ghost_gdiplus_h.h header to work around this.
 *
 * @see ghost_gdiplus_h.h
 */

#ifndef ghost_has_ghost_windows_h
    #ifndef _WIN32
        #define ghost_has_ghost_windows_h 0
    #endif
#endif

/* Allow the user to override the include path */
#ifndef ghost_has_ghost_windows_h
    #ifdef GHOST_WINDOWS_H
        #include GHOST_WINDOWS_H
        #define ghost_has_ghost_windows_h 1
    #endif
#endif

/* Include it with proper safeties */
#ifndef ghost_has_ghost_windows_h
    #ifdef GHOST_IMPL_WINDOWS_H_DEFINED_WIN32_LEAN_AND_MEAN
        #error
    #endif
    #ifdef GHOST_IMPL_WINDOWS_H_DEFINED_NOMINMAX
        #error
    #endif

    #ifndef NOMINMAX
        #define GHOST_IMPL_WINDOWS_H_DEFINED_NOMINMAX
        #define NOMINMAX
    #endif
    #ifndef WIN32_LEAN_AND_MEAN
        #define GHOST_IMPL_WINDOWS_H_DEFINED_WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    /*
     * If we have __has_include, we check that the file actually exists, and we
     * check several casings of Windows.h in order to add some safety when
     * building on a case-sensitive filesystem. (This is probably not terribly
     * useful, especially considering MSVC doesn't appear to support
     * __has_include in C mode.)
     */
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<Windows.h>)
            #include <Windows.h>
            #define ghost_has_ghost_windows_h 1
        #elif __has_include(<windows.h>)
            #include <windows.h>
            #define ghost_has_ghost_windows_h 1
        #elif __has_include(<WINDOWS.H>)
            #include <WINDOWS.H>
            #define ghost_has_ghost_windows_h 1
        #else
            #define ghost_has_ghost_windows_h 0
        #endif
    #else
        #include <Windows.h>
        #define ghost_has_ghost_windows_h 1
    #endif

    #ifdef GHOST_IMPL_WINDOWS_H_DEFINED_WIN32_LEAN_AND_MEAN
        #undef GHOST_IMPL_WINDOWS_H_DEFINED_WIN32_LEAN_AND_MEAN
        #undef WIN32_LEAN_AND_MEAN
    #endif
    #ifdef GHOST_IMPL_WINDOWS_H_DEFINED_NOMINMAX
        #undef GHOST_IMPL_WINDOWS_H_DEFINED_NOMINMAX
        #undef NOMINMAX
    #endif
#endif

#endif
