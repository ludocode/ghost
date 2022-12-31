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

#ifndef GHOST_GDIPLUS_H_H_INCLUDED
#define GHOST_GDIPLUS_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes Windows <Gdiplus.h> if it's available with a workaround for the
 * min/max NOMINMAX problem.
 *
 * <Gdiplus.h> requires min/max macros normally defined by <Windows.h>. Ghost
 * includes <Windows.h> without those macros but does not provide alternatives.
 * Ghost therefore provides this header to include <Gdiplus.h> with workarounds
 * for this problem.
 *
 * See this for more info:
 *     https://stackoverflow.com/q/4913922
 */

#ifndef ghost_has_ghost_gdiplus_h
    #ifndef _WIN32
        #define ghost_has_ghost_gdiplus_h 0
    #endif
#endif

/* <Gdiplus.h> can only be included in C++. */
#ifndef ghost_has_ghost_gdiplus_h
    #ifndef __cplusplus
        #define ghost_has_ghost_gdiplus_h 0
    #endif
#endif

/* We include <Windows.h> first to get our NOMINMAX in and to make sure there
 * are no other conflicts. */
#ifndef ghost_has_ghost_gdiplus_h
    #include "ghost/header/windows/ghost_windows_h.h"
    #if !ghost_has(ghost_windows_h)
        #define ghost_has_ghost_gdiplus_h 0
    #endif
#endif

#ifndef ghost_has_ghost_gdiplus_h
    #define ghost_has_ghost_gdiplus_h 1

    /* We include <Windows.h> with WIN32_LEAN_AND_MEAN. It omits the following
     * header which <Gdiplus.h> apparently depends on but neglects to include. */
    #include <unknwn.h>

    #ifdef GHOST_IMPL_GDIPLUS_DEFINED_MIN
        #error
    #endif
    #ifdef GHOST_IMPL_GDIPLUS_DEFINED_MAX
        #error
    #endif

    /* We use macros instead of inline functions to avoid conflicts with any
     * other inline function workarounds that might have been defined. */
    #ifndef min
        #define GHOST_IMPL_GDIPLUS_DEFINED_MIN
        #define min(x, y) ((x) < (y) ? (x) : (y))
    #endif
    #ifndef max
        #define GHOST_IMPL_GDIPLUS_DEFINED_MAX
        #define max(x, y) ((x) > (y) ? (x) : (y))
    #endif

    /*
     * If we have __has_include, we check that the file actually exists. It's
     * possible a Windows SDK is not installed with GDI+ support.
     */
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<Gdiplus.h>)
            #include <Gdiplus.h>
            #define ghost_has_ghost_windows_h 1
        #else
            #define ghost_has_ghost_windows_h 0
        #endif
    #else
        #include <Gdiplus.h>
        #define ghost_has_ghost_windows_h 1
    #endif

    #ifdef GHOST_IMPL_GDIPLUS_DEFINED_MIN
        #undef GHOST_IMPL_GDIPLUS_DEFINED_MIN
        #undef min
    #endif
    #ifdef GHOST_IMPL_GDIPLUS_DEFINED_MAX
        #undef GHOST_IMPL_GDIPLUS_DEFINED_MAX
        #undef max
    #endif
#endif

#endif
