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

#ifndef GHOST_IMPL_QSORT_CONFIG_H_INCLUDED
#define GHOST_IMPL_QSORT_CONFIG_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_QSORT_FORCE_INTERNAL
 *
 * Define this to 1 to always use Ghost's internal qsort implementation for all
 * qsort functions regardless of what's available on the platform.
 *
 * The default is 0.
 */
#ifndef GHOST_QSORT_FORCE_INTERNAL
    #define GHOST_QSORT_FORCE_INTERNAL 0
#endif

/**
 * @def GHOST_QSORT_DISABLE_INTERNAL
 *
 * Define this to 1 to prevent Ghost's internal qsort implementation from being
 * used.
 *
 * Enabling this makes it possible for Ghost qsort() functions to not exist.
 * Use ghost_has() to check.
 *
 * The default is 0.
 */
#ifndef GHOST_QSORT_DISABLE_INTERNAL
    #define GHOST_QSORT_DISABLE_INTERNAL 0
#endif

/**
 * @def GHOST_QSORT_DISABLE_SYSTEM
 *
 * Define this to 1 to disable the automatic detection of any system qsort()
 * function (including the standard libc qsort().)
 *
 * The default is 0.
 */
#ifndef GHOST_QSORT_DISABLE_SYSTEM
    #define GHOST_QSORT_DISABLE_SYSTEM 0
#endif

#if GHOST_QSORT_FORCE_INTERNAL && GHOST_QSORT_DISABLE_INTERNAL
    #error "GHOST_QSORT_FORCE_INTERNAL and GHOST_QSORT_DISABLE_INTERNAL cannot both be enabled."
#endif

/* Decide whether to use __cdecl in the definition of ghost_win_qsort_s(). On
 * Windows we require it to match the definition of the platform qsort_s().
 * This is also normally the default calling convention so you don't normally
 * have to specify cdecl on your callback function. We assume the same
 * behaviour is desired on other platforms where cdecl is not the default: if
 * we specified cdecl when it's not the default, you'd have to make your
 * callback explicitly cdecl. So on other platforms we don't use it. */
#ifndef GHOST_WIN_QSORT_S_USE_CDECL
    #ifdef _WIN32
        #define GHOST_WIN_QSORT_S_USE_CDECL 1
    #else
        #define GHOST_WIN_QSORT_S_USE_CDECL 0
    #endif
#endif

/* Actually define cdecl. I suppose you could use this if you wanted your
 * ghost_win_qsort_r() callback to also conditionally be cdecl. */
#ifndef GHOST_WIN_QSORT_S_CDECL
    #if GHOST_WIN_QSORT_S_USE_CDECL
        #ifdef _MSC_VER
            #define GHOST_WIN_QSORT_S_CDECL __cdecl
        #elif defined(__GNUC__)
            #define GHOST_WIN_QSORT_S_CDECL __attribute__(__cdecl__)
        #endif
    #endif
#endif
#ifndef GHOST_WIN_QSORT_S_CDECL
    #define GHOST_WIN_QSORT_S_CDECL /*nothing*/
#endif

#endif
