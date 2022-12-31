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

#ifndef GHOST_DEPRECATED_REASON_H_INCLUDED
#define GHOST_DEPRECATED_REASON_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_deprecated_reason("reason") [[deprecated("reason")]]
 *
 * Declares an identifier as deprecated with the given reason.
 *
 * If the compiler supports a deprecated annotation, using an identifier
 * annotated with ghost_deprecated_reason() will cause a compiler warning.
 * Additionally, if the compiler supports adding a reason, the given reason
 * will be provided in the warning message.
 *
 * The reason is optional but the parentheses are required. Use
 * `ghost_deprecated` if you don't want to specify a reason.
 *
 * @see ghost_deprecated
 */
#endif

/* TODO get rid of this, make ghost_deprecated() take optional message */
/* TODO or don't, deprecated without () is really convenient */

#ifndef ghost_has_ghost_deprecated_reason
    #ifdef ghost_deprecated_reason
        #define ghost_has_ghost_deprecated_reason 1
    #endif
#endif

#ifndef ghost_has_ghost_deprecated_reason
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        /* This will apparently be supported in C23. We disable this for now. */
        #if 0 /* GHOST_STDC_VERSION > 202000L // C23 */
        /* We are also supposed to be able to use __has_c_attribute so we may
         * not need to check the C version. */
        #ifdef __has_c_attribute
            #if __has_c_attribute(deprecated) >= 201904L
                /* https://en.cppreference.com/w/c/language/attributes/deprecated */
                #define ghost_deprecated_reason(x) [[deprecated(x)]]
                #define ghost_has_ghost_deprecated_reason 1
            #endif
        #endif
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_deprecated_reason
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201402L
            #define ghost_deprecated_reason(x) [[deprecated(x)]]
            #define ghost_has_ghost_deprecated_reason 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_deprecated_reason
    #if defined(_MSC_VER)
        #define ghost_deprecated_reason(x) __declspec(deprecated(x))
        #define ghost_has_ghost_deprecated_reason 1

    #elif defined(__GNUC__)
        #define ghost_deprecated_reason(x) __attribute__((__deprecated__(x)))
        #define ghost_has_ghost_deprecated_reason 1

    #else
        #define ghost_deprecated_reason /*nothing*/
        #define ghost_has_ghost_deprecated_reason 1
    #endif
#endif

#endif
