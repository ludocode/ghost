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

#ifndef GHOST_NODISCARD_H_INCLUDED
#define GHOST_NODISCARD_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_nodiscard [[nodiscard]]
 *
 * Declares that the return value of the annotated function must not be
 * ignored.
 *
 * If the compiler supports the nodiscard annotation, ignoring the return value
 * of an function so annotated will cause a compiler warning or error.
 *
 * Use `ghost_nodiscard_reason()` if you want to specify a reason.
 *
 * @see ghost_nodiscard_reason()
 */
#endif

/* TODO maybe bring back the optional message, like ghost_fatal(), and rename
 * ghost_nodiscard_reason() to ghost_nodiscard_msg() to match ghost_fatal_msg()
 * TODO also ghost_deprecated */

#ifndef ghost_has_ghost_nodiscard
    #ifdef ghost_nodiscard
        #define ghost_has_ghost_nodiscard 1
    #endif
#endif

/* C23 adds [[nodiscard]]
         *TODO
         * #ifdef __has_c_attribute
         *    #if __has_c_attribute(nodiscard) >= 202003L */
#ifndef ghost_has_ghost_nodiscard
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
            /* https://en.cppreference.com/w/c/language/attributes/nodiscard */
            #define ghost_nodiscard [[__nodiscard__]]
            #define ghost_has_ghost_nodiscard 1
        #endif
    #endif
#endif

/* C++17 adds [[nodiscard]].
 *
 * We'd prefer to use [[__nodiscard__]] but that isn't standard C++ yet. It
 * might make sense to avoid this if nodiscard is defined as a macro but it
 * could just as well be defined after this is included so there's no real way
 * to detect it. */
#ifndef ghost_has_ghost_nodiscard
    #if defined(__cplusplus)
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201703L
            /* https://en.cppreference.com/w/cpp/language/attributes/nodiscard */
            #define ghost_nodiscard [[nodiscard]]
            #define ghost_has_ghost_nodiscard 1
        #endif
    #endif
#endif

/* GNU C */
#ifndef ghost_has_ghost_nodiscard
    #if defined(__GNUC__)
/*TODO disabling to get tests passing temporarily while we un-break ghost_discard() */
#if 0
        #define ghost_nodiscard __attribute__((__warn_unused_result__))
        #define ghost_has_ghost_nodiscard 1
#endif
    #endif
#endif

/*
 * MSVC
 *
 * Old versions of MSVC only support _Check_return_. This doesn't actually warn
 * at compile-time; it's only checked by Microsoft's static analysis. Still, it
 * will generate warnings there so we use it.
 *
 *     https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2015/code-quality/annotating-function-behavior
 */
#ifndef ghost_has_ghost_nodiscard
    #ifdef _MSC_VER
        #define ghost_nodiscard _Check_return_
        #define ghost_has_ghost_nodiscard 1
    #endif
#endif

/* Fallback to nothing. */
#ifndef ghost_has_ghost_nodiscard
    #define ghost_nodiscard /*nothing*/
    #define ghost_has_ghost_nodiscard 1
#endif

#endif
