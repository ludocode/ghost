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

#ifndef GHOST_DEPRECATED_H_INCLUDED
#define GHOST_DEPRECATED_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_deprecated [[deprecated]]
 *
 * Declares an identifier as deprecated.
 *
 * If the compiler supports a deprecated annotation, using an identifier
 * annotated with ghost_deprecated will cause a compiler warning.
 *
 * Use `ghost_deprecated_reason()` if you want to specify a reason.
 *
 * @see ghost_deprecated_reason()
 */
#endif

/* TODO maybe bring back the optional message, like ghost_fatal(), and rename
 * ghost_deprecated_reason() to ghost_deprecated_msg() to match ghost_fatal_msg()
 * TODO also ghost_nodiscard */

#ifndef ghost_has_ghost_deprecated
    #ifdef ghost_deprecated
        #define ghost_has_ghost_deprecated 1
    #endif
#endif

/* C23 adds [[deprecated]]
 * We are also supposed to be able to use __has_c_attribute so we may
 * not need to check the C version.
         *TODO
         * #ifdef __has_c_attribute
         *    #if __has_c_attribute(deprecated) >= 201904L */
#ifndef ghost_has_ghost_deprecated
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
            /* https://en.cppreference.com/w/c/language/attributes/deprecated */
            #define ghost_deprecated [[__deprecated__]]
            #define ghost_has_ghost_deprecated 1
        #endif
    #endif
#endif

/* C++14 adds [[deprecated]] */
#ifndef ghost_has_ghost_deprecated
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201402L
            #define ghost_deprecated [[deprecated]]
            #define ghost_has_ghost_deprecated 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_deprecated
    /* MSVC */
    #if defined(_MSC_VER)
        #define ghost_deprecated __declspec(deprecated)
        #define ghost_has_ghost_deprecated 1

    /* GNU C */
    #elif defined(__GNUC__)
        #define ghost_deprecated __attribute__((__deprecated__))
        #define ghost_has_ghost_deprecated 1

    /* Fallback to nothing. */
    #else
        #define ghost_deprecated /*nothing*/
        #define ghost_has_ghost_deprecated 1
    #endif
#endif

#endif
