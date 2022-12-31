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

#ifndef GHOST_CXX_EXCEPTIONS_H_INCLUDED
#define GHOST_CXX_EXCEPTIONS_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CXX_EXCEPTIONS
 *
 * Defined to 1 if C++ exception support is enabled, or 0 otherwise.
 *
 * The C++ standard does not technically allow exceptions to be disabled.
 * However, some compilers provide the ability to disable them (or parts of
 * them) as an extension.
 *
 * In particular, GNU C++ compilers support `-fno-exceptions` to disable the
 * try/catch/throw keywords, and MSVC disables C++ stack unwinding unless
 * `/EHs`, `/EHa`, or some combination of them are specified.
 *
 * This macro reports whether C++ exceptions are properly supported. Use it to
 * disable try/catch/throw code when exceptions are off.
 */
#endif

#ifndef ghost_has_GHOST_CXX_EXCEPTIONS
    #ifdef GHOST_CXX_EXCEPTIONS
        #define ghost_has_GHOST_CXX_EXCEPTIONS 1
    #endif
#endif

/* C++ exceptions require C++ */
#ifndef ghost_has_GHOST_CXX_EXCEPTIONS
    #ifndef __cplusplus
        #define GHOST_CXX_EXCEPTIONS 0
        #define ghost_has_GHOST_CXX_EXCEPTIONS 1
    #endif
#endif

/* GNUC defines __cpp_exceptions to non-zero if exceptions are enabled */
#ifndef ghost_has_GHOST_CXX_EXCEPTIONS
    #ifdef __cpp_exceptions
        #if __cpp_exceptions
            #define GHOST_CXX_EXCEPTIONS 1
        #else
            #define GHOST_CXX_EXCEPTIONS 0
        #endif
        #define ghost_has_GHOST_CXX_EXCEPTIONS 1
    #elif defined(__GNUC__)
        /* undefined __cpp_exceptions from a GNUC compiler means
         * -fno-exceptions was specified. The try/catch/throw keywords cause
         * compiler errors. */
        #define GHOST_CXX_EXCEPTIONS 0
        #define ghost_has_GHOST_CXX_EXCEPTIONS 1
    #endif
#endif

/* MSVC defines _CPPUNWIND to 1 if exceptions are enabled (/EHs or /EHa)
 *     https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros */
#ifndef ghost_has_GHOST_CXX_EXCEPTIONS
    #ifdef _CPPUNWIND
        #if _CPPUNWIND
            #define GHOST_CXX_EXCEPTIONS 1
        #else
            #define GHOST_CXX_EXCEPTIONS 0
        #endif
        #define ghost_has_GHOST_CXX_EXCEPTIONS 1
    #elif defined(_MSC_VER)
        /* Undefined _CPPUNWIND from MSVC means C++ stack unwinding is
         * disabled. The try/catch/throw keywords are still allowed but they
         * work more like longjmp().
         *     https://docs.microsoft.com/en-us/cpp/build/reference/eh-exception-handling-model */
        #define GHOST_CXX_EXCEPTIONS 0
        #define ghost_has_GHOST_CXX_EXCEPTIONS 1
    #endif
#endif

/* Fallback to standard C++ */
#ifndef ghost_has_GHOST_CXX_EXCEPTIONS
    /* We haven't been able to detect exception support from the compiler.
     * We've checked for C++ above and C++ requires exceptions so we assume
     * they're enabled. */
    #define GHOST_CXX_EXCEPTIONS 1
    #define ghost_has_GHOST_CXX_EXCEPTIONS 1
#endif

#endif
