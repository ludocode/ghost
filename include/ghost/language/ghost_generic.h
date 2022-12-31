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

#ifndef GHOST_GENERIC_H_INCLUDED
#define GHOST_GENERIC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_generic _Generic
 *
 * A wrapper that detects whether support for _Generic exists and silences
 * warnings.
 *
 * Use ghost_has(ghost_generic) to see if _Generic is supported. If it is, you
 * can simply use _Generic directly, or use ghost_generic to silence warnings
 * in case _Generic is an extension.
 */
#endif

/* With Clang we can test for _Generic support directly and ignore language
 * version. Clang allows _Generic under any language standard (even in C++) and
 * emits no warnings. */
/* TODO see if this is 1 even under -std=c98 -Wpedantic, may need __extension__ to silence warnings
 * TODO see what version of clang __has_feature was added, may need a fallback
 * TODO really not need __extension__? */
#ifndef ghost_has_ghost_generic
    #if defined(__clang__) && defined(__has_feature)
        #if __has_feature(c_generic_selections)
            #define ghost_generic _Generic
            #define ghost_has_ghost_generic 1
        #else
            #define ghost_has_ghost_generic 0
        #endif
    #endif
#endif

/* _Generic was added in C11. */
#ifndef ghost_has_ghost_generic
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 201112L
            #include "ghost/detect/ghost_gcc.h"
            #if GHOST_GCC
                /* _Generic was only added in GCC 4.9 even though C11 support
                 * is advertised by 4.7 and 4.8. */
                #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9)
                    #define ghost_generic _Generic
                    #define ghost_has_ghost_generic 1
                #endif
            #else
                #define ghost_generic _Generic
                #define ghost_has_ghost_generic 1
            #endif
        #endif
    #endif
#endif

/* GCC allows us to use _Generic in older C language standards (but not in
 * C++.) We use __extension__ to silence compiler warnings about it. */
#ifndef ghost_has_ghost_generic
    #ifndef __cplusplus
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* _Generic was added in GCC 4.9. */
            #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9)
                #define ghost_generic __extension__ _Generic
                #define ghost_has_ghost_generic 1
            #endif
        #endif
    #endif
#endif

/*
 * TODO maybe we need to check the MSVC version, _Generic is only available
 * under VS2019 tools I think
 *     https://docs.microsoft.com/en-us/cpp/c-language/generic-selection
 *     https://docs.microsoft.com/en-us/cpp/overview/install-c17-support
 */

#ifndef ghost_has_ghost_generic
    #define ghost_has_ghost_generic 0
#endif

#endif
