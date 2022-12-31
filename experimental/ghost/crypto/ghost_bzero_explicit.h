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

#ifndef GHOST_BZERO_EXPLICIT_H_INCLUDED
#define GHOST_BZERO_EXPLICIT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A bzero() function that will not be eliminated by compiler optimizations.
 *
 * Use this to erase memory that contains sensitive information such as
 * passwords and encryption keys.
 *
 * @warning This does not erase copies of the buffer contents that may have
 *          been stored in registers, on the stack, etc.
 */
void* ghost_bzero_explicit(void* p, size_t count);
#endif

/* Security-related stuff in Ghost is experimental. */
#ifndef ghost_has_ghost_bzero_explicit
    #if !GHOST_EXPERIMENTAL
        #define ghost_has_ghost_bzero_explicit 0
    #endif
#endif

/* We'll need to detect the libc. */
#ifndef ghost_has_ghost_bzero_explicit
    #include "ghost/detect/ghost_libc.h"
#endif

/* Solaris, FreeBSD and DragonFlyBSD have explicit_bzero() in <strings.h>.
 *     https://docs.oracle.com/cd/E88353_01/html/E37843/explicit-memset-3c.html
 *     https://www.freebsd.org/cgi/man.cgi?query=explicit_bzero&apropos=0&sektion=0&manpath=FreeBSD+13.1-RELEASE+and+Ports&arch=default&format=html
 *     https://man.dragonflybsd.org/?command=explicit_bzero&section=ANY */
#ifndef ghost_has_ghost_bzero_explicit
    #if defined(__FreeBSD__) || defined(__DragonFly__) || \
            (defined(__sun) && defined(__SVR4))
        #include "ghost/header/posix/ghost_strings_h.h"
        #define ghost_bzero_explicit explicit_bzero
        #define ghost_has_ghost_bzero_explicit 1
    #endif
#endif

/* OpenBSD has explicit_bzero() in <string.h>.
 *     https://man.openbsd.org/explicit_bzero.3 */
#ifndef ghost_has_ghost_bzero_explicit
    #if defined(__OpenBSD__)
        #include "ghost/header/c/ghost_string_h.h"
        #define ghost_bzero_explicit explicit_bzero
        #define ghost_has_ghost_bzero_explicit 1
    #endif
#endif

/* NetBSD doesn't have explicit_bzero() but it does have explicit_memset(). We
 * fall back to ghost_memset_explicit() below which will use NetBSD's
 * explicit_memset(). */

/* Windows has SecureZeroMemory().
 *     https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/aa366877(v=vs.85) */
#ifndef ghost_has_ghost_bzero_explicit
    #ifdef _WIN32
        #include "ghost/header/windows/ghost_windows_h.h"
        #if ghost_has(ghost_windows_h)
            #define ghost_bzero_explicit SecureZeroMemory
            #define ghost_has_ghost_bzero_explicit 1
        #endif
    #endif
#endif

/* glibc has explicit_bzero() in <string.h> since 2.25. */
#ifndef ghost_has_ghost_bzero_explicit
    #ifdef __linux__
        #if defined(__GLIBC__) && !defined(__UCLIBC__) && GHOST_GLIBC_COMPAT == 0
            #if __GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 25)
                #include "ghost/header/c/ghost_string_h.h"
                #define ghost_bzero_explicit explicit_bzero
                #define ghost_has_ghost_bzero_explicit 1
            #endif
        #endif
    #endif
#endif

/* libbsd has explicit_bzero(). This is only defined if we're not on a recent
 * glibc, but we don't need to check this because we detect glibc above. */
#ifndef ghost_has_ghost_bzero_explicit
    #include "ghost/bindings/libbsd/ghost_libbsd_string_h.h"
    #if ghost_has(ghost_libbsd_string_h)
        #define ghost_bzero_explicit explicit_bzero
        #define ghost_has_ghost_bzero_explicit 1
    #endif
#endif

/* Otherwise we fallback to ghost_memset_explicit(). */
#ifndef ghost_has_ghost_bzero_explicit
    #include "ghost/crypto/ghost_memset_explicit.h"
    #if ghost_has(ghost_memset_explicit)
        #define ghost_bzero_explicit(p, count) ghost_memset_explicit(p, 0, count)
        #define ghost_has_ghost_bzero_explicit 1
    #endif
#endif

#ifndef ghost_has_ghost_bzero_explicit
    #define ghost_has_ghost_bzero_explicit 0
#endif

#endif
