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

#ifndef GHOST_NODISCARD_REASON_H_INCLUDED
#define GHOST_NODISCARD_REASON_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_nodiscard("reason")
 *
 * Declares that the return value of the annotated function must not be
 * ignored.
 *
 * If the compiler supports a deprecated annotation, using an identifier
 * annotated with ghost_deprecated will cause a compiler warning.
 * Additionally, if the compiler supports adding a reason, the given reason
 * will be provided in the compiler message.
 *
 * The reason is optional but the parentheses are required. Use
 * `ghost_nodiscard` if you don't want to specify a reason.
 *
 * @see ghost_nodiscard
 */
#endif

/* TODO get rid of this, make reason optional in normal ghost_nodiscard() */
/* TODO no, keep it separate */

#ifndef ghost_has_ghost_nodiscard_reason
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        /* This will apparently be supported in C23. We disable this for now. */
        #if 0 /* GHOST_STDC_VERSION > 202000L // C23 */
        /* We are also supposed to be able to use __has_c_attribute so we may
         * not need to check the C version. */
        #ifdef __has_c_attribute
            /* https://en.cppreference.com/w/c/language/attributes */
            #if __has_c_attribute(__nodiscard__) >= 202003L
                /* https://en.cppreference.com/w/c/language/attributes/nodiscard */
                #define ghost_nodiscard_reason [[__nodiscard__(x)]]
                #define ghost_has_ghost_nodiscard_reason 1
            #endif
        #endif
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_nodiscard_reason
    #if defined(__cplusplus)
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201703L
            /* https://en.cppreference.com/w/cpp/language/attributes/nodiscard */
            #define ghost_nodiscard_reason(x) [[nodiscard(x)]]
            #define ghost_has_ghost_nodiscard_reason 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_nodiscard_reason
/*TODO */
#endif

#ifndef ghost_has_ghost_nodiscard_reason
    #if defined(__GNUC__)
        #define ghost_nodiscard_reason(x) __attribute__((__warn_unused_result__)) /* reason ignored */
        #define ghost_has_ghost_nodiscard_reason 1
    #elif defined(_MSC_VER)
        #define ghost_nodiscard_reason(x) _Check_return_ /* reason ignored */ */ */ */
        #define ghost_has_ghost_nodiscard_reason 1
    #else
        #define ghost_nodiscard_reason /*nothing*/
        #define ghost_has_ghost_nodiscard_reason 1
    #endif
#endif

#endif
