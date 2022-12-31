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

#ifndef GHOST_SNPRINTF_H_INCLUDED
#define GHOST_SNPRINTF_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Writes a formatted string into the given buffer, truncating if it doesn't
 * fit.
 *
 * https://en.cppreference.com/w/c/io/fprintf
 */
int ghost_snprintf(char* restrict buffer, size_t buffer_size,
        const char* restrict format, ...);
#endif

#ifndef ghost_has_ghost_snprintf
    #ifdef ghost_snprintf
        #define ghost_has_ghost_snprintf 1
    #endif
#endif

/* We're going to assume on all platforms that <stdio.h> is required. */
#ifndef ghost_has_ghost_snprintf
    #include "ghost/header/c/ghost_stdio_h.h"
    #if !ghost_has(ghost_stdio_h)
        #define ghost_has_ghost_snprintf 0
    #endif
#endif

/*
 * On MSVC this is only available as of VS2015.
 *
 *     https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/snprintf-snprintf-snprintf-l-snwprintf-snwprintf-l
 *
 * Earlier versions define _snprintf() but it doesn't behave correctly. We
 * correct the behaviour in ghost_vsnprintf() which we wrap below.
 */
#ifndef ghost_has_ghost_snprintf
    #if ghost_has(ghost_stdio_h)
        #ifdef _MSC_VER
            #if _MSC_VER >= 1900
                #define ghost_snprintf snprintf
                #define ghost_has_ghost_snprintf 1
            #endif
        #endif
    #endif
#endif

/* snprintf() is required by C99 and C++11 but some platforms (e.g. macOS, zOS)
 * still don't define it without certain feature-test macros. */
#ifndef ghost_has_ghost_snprintf
    #ifndef __APPLE__
        #ifdef __cplusplus
            #include "ghost/language/ghost_cplusplus.h"
            #if ghost_cplusplus >= 201103L
                #define ghost_snprintf snprintf
                #define ghost_has_ghost_snprintf 1
            #endif
        #elif defined(__STDC_VERSION__)
            #include "ghost/language/ghost_stdc_version.h"
            #if GHOST_STDC_VERSION >= 199901L
                #define ghost_snprintf snprintf
                #define ghost_has_ghost_snprintf 1
            #endif
        #endif
    #endif
#endif

/* snprintf() is in POSIX 2001. It requires feature test macros. */
#ifndef ghost_has_ghost_snprintf
    #if defined(_POSIX_VERSION) && defined(_POSIX_C_SOURCE)
        #if _POSIX_VERSION >= 200112L && _POSIX_C_SOURCE >= 200112L
            #include <stdio.h>
            #define ghost_snprintf snprintf
            #define ghost_has_ghost_snprintf 1
        #endif
    #endif
#endif

/* For platforms where we know it exists, we could define it ourselves, but
 * only if we have asm labels; otherwise we need to forward to
 * ghost_vsnprintf(). */

/* Wrap ghost_vsnprintf() if we have it. */
#ifndef ghost_has_ghost_snprintf
    #include "ghost/format/ghost_vsnprintf.h"
    #if ghost_has(ghost_vsnprintf)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/header/c/ghost_stdarg_h.h"
        #include "ghost/language/ghost_restrict.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        int ghost_snprintf(
                char* ghost_restrict ghost_impl_v_buffer,
                ghost_size_t ghost_impl_v_buffer_size,
                const char* ghost_restrict ghost_impl_v_format,
                ...)
        {
            va_list ghost_impl_v_args;
            int ghost_impl_v_ret;
            va_start(ghost_impl_v_args, ghost_impl_v_format);
            ghost_impl_v_ret = ghost_vsnprintf(
                    ghost_impl_v_buffer,
                    ghost_impl_v_buffer_size,
                    ghost_impl_v_format,
                    ghost_impl_v_args);
            va_end(ghost_impl_v_args);
            return ghost_impl_v_ret;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_snprintf 1
    #endif
#endif

/* Otherwise we don't have this. */
#ifndef ghost_has_ghost_snprintf
    #define ghost_has_ghost_snprintf 0
#endif

#endif
