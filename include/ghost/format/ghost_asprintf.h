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

#ifndef GHOST_ASPRINTF_H_INCLUDED
#define GHOST_ASPRINTF_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Writes the given format string to an allocated string, returning the length
 * of the string (not including the null-terminator.)
 *
 * On error, str is set to null and -1 is returned.
 */
int ghost_asprintf(char** restrict /*out*/ str, const char* restrict format, ...);
#endif

/* Override is handled in ghost_malloc_system.h */
#include "ghost/malloc/ghost_malloc_system.h"

/*
 * The BSDs provide this function. They all set str to null on error.
 *
 *     https://man.openbsd.org/OpenBSD-5.8/asprintf.3
 *     https://man.netbsd.org/asprintf.3
 *     https://leaf.dragonflybsd.org/cgi/web-man?section=3&command=printf
 *     https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/asprintf.3.html
 */
#ifndef ghost_has_ghost_asprintf
    #if GHOST_MALLOC_SYSTEM
        #include "ghost/header/c/ghost_stdio_h.h"
        #include "ghost/detect/ghost_libc.h"
        #if ghost_has(ghost_stdio_h) && (defined(__FreeBSD__) || defined(__NetBSD__) || \
                defined(__OpenBSD__) || defined(__DragonFly__))
            #define ghost_asprintf asprintf
            #define ghost_has_ghost_asprintf 1
        #endif
    #endif
#endif

/* Apple also provides this but declares it conditionally. We declare it
 * ourselves only if we have asm labels; otherwise we have to forward to
 * vasprintf() anyway so we use our fallback below. */
#ifndef ghost_has_ghost_asprintf
    #if defined(__APPLE__) && GHOST_MALLOC_SYSTEM
        #include "ghost/header/c/ghost_stdio_h.h"
        #if ghost_has(ghost_stdio_h)
            #include "ghost/language/ghost_dllimport.h"
            #include "ghost/language/ghost_restrict.h"
            #include "ghost/impl/ghost_impl_libc_asm.h"
            #include "ghost/impl/ghost_impl_libc_noexcept.h"
            #if GHOST_IMPL_LIBC_ASM
                #include "ghost/language/ghost_extern_c.h"
                ghost_extern_c
                ghost_dllimport
                /* TODO attribute format */
                int ghost_asprintf(char** ghost_restrict /*out*/ str, const char* ghost_restrict format, ...)
                    ghost_impl_libc_noexcept(ghost_impl_libc_asm("asprintf"));
                #define ghost_has_ghost_asprintf 1
            #endif
        #endif
    #endif
#endif

/* glibc provides this function with several caveats; see ghost_vasprintf().
 * Instead of implementing the same workarounds here, we just wrap ghost_vasprintf(). */

/* Otherwise wrap ghost_vasprintf() if we have it. */
#ifndef ghost_has_ghost_asprintf
    #include "ghost/format/ghost_vasprintf.h"
    #if ghost_has(ghost_vasprintf)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/header/c/ghost_stdarg_h.h"
        #include "ghost/language/ghost_restrict.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        int ghost_asprintf(char** ghost_restrict /*out*/ str, const char* ghost_restrict format, ...) {
            va_list args;
            int ret;
            va_start(args, format);
            ret = ghost_vasprintf(str, format, args);
            va_end(args);
            return ret;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_asprintf 1
    #endif
#endif

#ifndef ghost_has_ghost_asprintf
    #define ghost_has_ghost_asprintf 0
#endif

#endif
