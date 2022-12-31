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

#ifndef GHOST_SILENCE_DEPRECATED_H_INCLUDED
#define GHOST_SILENCE_DEPRECATED_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_DEPRECATED
 *
 * Silences compiler warnings about the use of deprecated declarations
 * (functions, variables, C++ classes), i.e. those annotated by
 * `[[deprecated]]` or other compiler-specific attributes.
 *
 * This does not silence warnings about the use of deprecated language
 * features.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_DEPRECATED
    #ifdef GHOST_SILENCE_DEPRECATED
        #define ghost_has_GHOST_SILENCE_DEPRECATED 1
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_DEPRECATED
    #if defined(__clang__)
        /* TODO clang has __has_warning(), use that */
    #endif
#endif

/*
 * GCC/Clang -Wdeprecated-declarations on by default
 *
 * We don't currently include -Wdeprecated in this. -Wdeprecated silences the
 * use of deprecated language features, not deprecated declarations. This can
 * make the name a bit misleading, but in my experience it's common to silence
 * a warning about using a deprecated function and rare to silence a warning
 * about a deprecated language feature. If this is a problem we could separate
 * this out into two different macros and use both here.
 */
#ifndef ghost_has_GHOST_SILENCE_DEPRECATED
    #if defined(__GNUC__) && !defined(__CPARSER__)
        /* _Pragma GCC diagnostic is supported since GCC 4.2 */
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
                #define GHOST_SILENCE_DEPRECATED _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
                #define ghost_has_GHOST_SILENCE_DEPRECATED 1
            #endif
        #else
            #define GHOST_SILENCE_DEPRECATED _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
            #define ghost_has_GHOST_SILENCE_DEPRECATED 1
        #endif
    #endif
#endif

/* MSVC C4996 in /W4 */
#ifndef ghost_has_GHOST_SILENCE_DEPRECATED
    #ifdef _MSC_VER
        /*
         * C4996, deprecated. The message varies based on what kind of
         * deprecated symbol is being used. This silences warnings from:
         *
         * - standard functions that Microsoft has deemed unsafe (e.g. strcpy());
         * - the proper names of POSIX functions (e.g. memccpy());
         * - functions marked [[deprecated]];
         * - other weird Microsoft-isms like unchecked iterators.
         */
        #define GHOST_SILENCE_DEPRECATED __pragma(warning(disable:4996))
        #define ghost_has_GHOST_SILENCE_DEPRECATED 1
    #endif
#endif

/* TODO PGI/NVidia */

/* TODO INTEL */

/* */

#ifndef ghost_has_GHOST_SILENCE_DEPRECATED
    #define GHOST_SILENCE_DEPRECATED /*nothing*/
    #define ghost_has_GHOST_SILENCE_DEPRECATED 1
#endif

#endif
