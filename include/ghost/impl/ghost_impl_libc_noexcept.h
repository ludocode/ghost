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

#ifndef GHOST_IMPL_LIBC_NOEXCEPT_H_INCLUDED
#define GHOST_IMPL_LIBC_NOEXCEPT_H_INCLUDED

/*
 * @def ghost_impl_libc_noexcept(label) label __attribute__((nothrow))
 *
 * This expands to the appropriate noexcept/nothrow function specifier for the
 * language standard being compiled in a way that matches how the libc declares
 * functions.
 *
 * Many libc functions are declared conditionally under feature flags like
 * _GNU_SOURCE, _BSD_SOURCE, _POSIX_C_SOURCE, or simply by the language
 * standard. For example if you compile C code with -ansi against glibc,
 * snprintf() isn't available because it was only added in C99.
 *
 * To work around this, Ghost declares many libc functions locally inside
 * wrapper functions when it determines that they exist on the platform. For
 * example, strnlen() is only declared by glibc if _GNU_SOURCE or
 * _POSIX_C_SOURCE is defined, so Ghost does something like this:
 *
 *     size_t ghost_strnlen(const char* s, size_t maxlen) {
 *         extern size_t strnlen(const char* s, size_t maxlen);
 *         return strnlen(s, maxlen);
 *     }
 *
 * (The way we prefer to work around this problem is to give functions declared
 * by Ghost a different name using asm labels. This is not possible on all
 * compilers however.)
 *
 * In cases where the function actually is declared by the libc headers, the
 * prototype declared by Ghost must exactly match that declared by the headers,
 * otherwise a compiler warning occurs.
 *
 * Some libcs declare functions noexcept, some declare them throw(), some
 * declare them __attribute__((nothrow)) (even in C), and some declare them
 * with no exception specifier. We need to match this exception specifier so
 * this macro is used to wrap it.
 *
 * This macro of course will not work in all cases. Wherever a function has
 * some weirdness in a particular libc that can't be handled by this macro,
 * that is handled specifically in the Ghost wrapper for that function.
 *
 * (For those libcs that declare their functions noexcept, usually the only
 * functions that aren't noexcept are those that have callbacks into user code.
 * qsort() is example. These are presumably designed to allow C++ exceptions to
 * propagate through them. Usually you won't see this macro on those
 * functions.)
 *
 * Annoyingly, in GCC, noexcept has to go before the __asm__ label and throw()
 * has to go after it. For this reason this macro takes an optional argument
 * that can contain an asm label which will be placed before or after the
 * noexcept specifier as needed. Note that ghost_impl_libc_asm() is used to
 * specify asm labels for libc functions since some platforms mangle the names.
 */

/* glibc does all the nothrow variations. */
#ifndef ghost_impl_libc_noexcept
    #include "ghost/detect/ghost_libc.h"
    #if defined __GLIBC__
        #ifdef __cplusplus
            #include "ghost/language/ghost_cplusplus.h"
            #if ghost_cplusplus >= 201103L
                #define ghost_impl_libc_noexcept(label) noexcept(true) label
            #else
                #define ghost_impl_libc_noexcept(label) label throw()
            #endif
        #else
            #define ghost_impl_libc_noexcept(label) label __attribute__((__nothrow__))
        #endif
    #endif
#endif

/* Other libcs, as far as we know, don't define libc functions nothrow. */
#ifndef ghost_impl_libc_noexcept
    #define ghost_impl_libc_noexcept(label) label
#endif

#endif
