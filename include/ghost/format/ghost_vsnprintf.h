/*
 * MIT No Attribution
 *
 * Copyright (c) 2022-2023 Fraser Heavy Software
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

#ifndef GHOST_VSNPRINTF_H_INCLUDED
#define GHOST_VSNPRINTF_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Writes a formatted string into the given buffer, truncating if it doesn't
 * fit.
 *
 * https://en.cppreference.com/w/c/io/fprintf
 */
int ghost_vsnprintf(char* restrict buffer, size_t buffer_size,
        const char* restrict format, va_list args);
#endif

#ifndef ghost_has_ghost_vsnprintf
    #ifdef ghost_vsnprintf
        #define ghost_has_ghost_vsnprintf 1
    #endif
#endif

#ifndef ghost_has_ghost_vsnprintf
    #include "ghost/header/c/ghost_stdio_h.h"
    #if !ghost_has(ghost_stdio_h)
        #define ghost_has_ghost_vsnprintf 0
    #endif
#endif

/* In MSVC 2013 and earlier, _vsnprintf() returns a negative value when the
 * string is truncated. We need to call _vscprintf() to calculate the correct
 * return value. */
#ifndef ghost_has_ghost_vsnprintf
    #ifdef _MSC_VER
        #if _MSC_VER < 1900
            #include "ghost/impl/ghost_impl_function.h"
            #include "ghost/language/ghost_restrict.h"
            #include "ghost/language/ghost_expect_true.h"
            #include "ghost/type/size_t/ghost_size_t.h"
            #include "ghost/header/c/ghost_stdarg_h.h"

            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_function
            int ghost_vsnprintf(
                    char* ghost_restrict ghost_impl_v_buffer,
                    ghost_size_t ghost_impl_v_buffer_size,
                    const char* ghost_restrict ghost_impl_v_format,
                    va_list ghost_impl_v_args)
            #if !GHOST_EMIT_DEFS
            ;
            #else
            {
                #pragma warning(push)
                #pragma warning(disable:4996) /* _vsnprintf() is "unsafe" */
                int ghost_impl_v_ret = _vsnprintf(
                        ghost_impl_v_buffer,
                        ghost_impl_v_buffer_size,
                        ghost_impl_v_format,
                        ghost_impl_v_args);
                #pragma warning(pop)

                if (ghost_impl_v_ret < 0) {
                    /* _vsnprintf() does not null-terminate on truncation. We
                    * null-terminate it ourselves. */
                    if (ghost_expect_true(ghost_impl_v_buffer_size > 0))
                        ghost_impl_v_buffer[ghost_impl_v_buffer_size - 1] = '\000';

                    /* Calculate the correct length */
                    ghost_impl_v_ret = _vscprintf(ghost_impl_v_format, ghost_impl_v_args);
                }

                return ghost_impl_v_ret;
            }
            #endif
            GHOST_IMPL_FUNCTION_CLOSE

            #define ghost_has_ghost_vsnprintf 1
        #endif
    #endif
#endif

/* In MSVC 2015+, vsnprintf() exists and has the proper C99 return value. It
 * apparently does not cause "unsafe" warnings either.
 *     https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/snprintf-snprintf-snprintf-l-snwprintf-snwprintf-l */
#ifndef ghost_has_ghost_vsnprintf
    #ifdef _MSC_VER
        #if _MSC_VER >= 1900
            #define ghost_vsnprintf vsnprintf
            #define ghost_has_ghost_vsnprintf 1
        #endif
    #endif
#endif

/* vsnprintf() is required by C99 and C++11 but some platforms (e.g. macOS,
 * zOS) still don't define it without certain feature-test macros. */
#ifndef ghost_has_ghost_vsnprintf
    #ifndef __APPLE__
        #ifdef __cplusplus
            #include "ghost/language/ghost_cplusplus.h"
            #if ghost_cplusplus >= 201103L
                #define ghost_vsnprintf vsnprintf
                #define ghost_has_ghost_vsnprintf 1
            #endif
        #elif defined(__STDC_VERSION__)
            #include "ghost/language/ghost_stdc_version.h"
            #if GHOST_STDC_VERSION >= 199901L
                #define ghost_vsnprintf vsnprintf
                #define ghost_has_ghost_vsnprintf 1
            #endif
        #endif
    #endif
#endif

/* vsnprintf() is in POSIX 2001. It requires feature test macros. */
#ifndef ghost_has_ghost_vsnprintf
    #if defined(_POSIX_VERSION) && defined(_POSIX_C_SOURCE)
        #if _POSIX_VERSION >= 200112L && _POSIX_C_SOURCE >= 200112L
            #include <stdio.h>
            #define ghost_vsnprintf vsnprintf
            #define ghost_has_ghost_vsnprintf 1
        #endif
    #endif
#endif

/* For those platforms where we know it exists, we define it ourselves. */

/* Some libcs (e.g. glibc, Emscripten) don't define vsnprintf() in C89 mode.
 * If we haven't detected it above but we believe it exists, we'll declare it
 * ourselves. */
#ifndef ghost_has_ghost_vsnprintf
    #ifdef GHOST_IMPL_VSNPRINTF_HAVE_LIBC
        #error
    #endif
    #include "ghost/detect/ghost_libc.h"
    #if defined(__APPLE__) || defined(__GLIBC__) || defined(__EMSCRIPTEN__)
        #include "ghost/header/c/ghost_stdarg_h.h"
        #include "ghost/language/ghost_dllimport.h"
        #include "ghost/language/ghost_restrict.h"
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/impl/ghost_impl_libc_noexcept.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #if GHOST_IMPL_LIBC_ASM
            #include "ghost/language/ghost_extern_c.h"
            ghost_extern_c
            ghost_dllimport
            int ghost_vsnprintf(
                    char* ghost_restrict ghost_impl_v_buffer,
                    ghost_size_t ghost_impl_v_buffer_size,
                    const char* ghost_restrict ghost_impl_v_format,
                    va_list ghost_impl_v_args)
                ghost_impl_libc_noexcept(ghost_impl_libc_asm("vsnprintf"));
        #else
            #include "ghost/impl/ghost_impl_always_inline.h"
            #include "ghost/preprocessor/ghost_nothing.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            int ghost_vsnprintf(
                    char* ghost_restrict ghost_impl_v_buffer,
                    ghost_size_t ghost_impl_v_buffer_size,
                    const char* ghost_restrict ghost_impl_v_format,
                    va_list ghost_impl_v_args)
            {
                ghost_dllimport
                extern int vsnprintf(
                        char* ghost_restrict ghost_impl_v_buffer,
                        ghost_size_t ghost_impl_v_buffer_size,
                        const char* ghost_restrict ghost_impl_v_format,
                        va_list ghost_impl_v_args)
                    ghost_impl_libc_noexcept(GHOST_NOTHING);
                return vsnprintf(
                        ghost_impl_v_buffer,
                        ghost_impl_v_buffer_size,
                        ghost_impl_v_format,
                        ghost_impl_v_args);
            }
            GHOST_IMPL_FUNCTION_CLOSE
        #endif
        #define ghost_has_ghost_vsnprintf 1
    #endif
#endif

/* If we have snprintf() and not vsnprintf(), it may be possible to emulate it
 * by manually walking through the format string and passing each argument with
 * its format specifier individually through snprintf(). We don't bother doing
 * this yet. */

/* Otherwise we don't have it. */
#ifndef ghost_has_ghost_vsnprintf
    #define ghost_has_ghost_vsnprintf 0
#endif

#endif
