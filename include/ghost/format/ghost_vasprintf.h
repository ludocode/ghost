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

#ifndef GHOST_VASPRINTF_H_INCLUDED
#define GHOST_VASPRINTF_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Writes the given format string to an allocated string.
 *
 * Ghost always sets str to null on error.
 */
int ghost_vasprintf(char** restrict /*out*/ str, const char* restrict format, va_list args);
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
#ifndef ghost_has_ghost_vasprintf
    #if GHOST_MALLOC_SYSTEM
        #include "ghost/header/c/ghost_stdio_h.h"
        #include "ghost/detect/ghost_libc.h"
        #if ghost_has(ghost_stdio_h) && (\
                defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
                defined(__DragonFly__) || defined(__APPLE__))
            #define ghost_vasprintf vasprintf
            #define ghost_has_ghost_vasprintf 1
        #endif
    #endif
#endif

/*
 * Apple also provides it but declares it conditionally.
 */
#ifndef ghost_has_ghost_vasprintf
    #if defined(__APPLE_) && GHOST_MALLOC_SYSTEM
        #include "ghost/header/c/ghost_stdio_h.h"
        #if ghost_has(ghost_stdio_h)
            #include "ghost/header/c/ghost_stdarg_h.h"
            #include "ghost/language/ghost_dllimport.h"
            #include "ghost/language/ghost_restrict.h"
            #include "ghost/impl/ghost_impl_libc_asm.h"
            #include "ghost/impl/ghost_impl_libc_noexcept.h"
            #if GHOST_IMPL_LIBC_ASM
                ghost_dllimport
                int ghost_vasprintf(char** ghost_restrict /*out*/ str, const char* ghost_restrict format, va_list args)
                    ghost_impl_libc_noexcept(ghost_impl_libc_asm("vasprintf"));
            #else
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/preprocessor/ghost_nothing.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                int ghost_vasprintf(char** ghost_restrict /*out*/ str, const char* ghost_restrict format, va_list args) {
                    ghost_dllimport
                    extern int vasprintf(char** ghost_restrict /*out*/ str, const char* ghost_restrict format, va_list args)
                        ghost_impl_libc_noexcept(GHOST_NOTHING);
                    return vasprintf(str, format, args);
                }
                GHOST_IMPL_FUNCTION_CLOSE
            #endif
            #define ghost_has_ghost_vasprintf 1
        #endif
    #endif
#endif

/*
 * glibc and uClibc provide this function but:
 *
 * - It's only defined under _GNU_SOURCE;
 * - It leaves str undefined on error;
 * - It's not defined by some other Linux libcs (like musl.)
 *
 * We fix up these problems here.
 *
 *     https://man.archlinux.org/man/vasprintf.3.en
 */
#ifndef ghost_has_ghost_vasprintf
    #if GHOST_MALLOC_SYSTEM
        #include "ghost/detect/ghost_libc.h"
        #include "ghost/impl/ghost_impl_glibc_compat.h"

        /* Don't use this if we want to be compatible with non-glibc */
        #if ghost_has(ghost_stdio_h) && defined(__GLIBC__) && GHOST_GLIBC_COMPAT == 0
            #include "ghost/header/c/ghost_stdarg_h.h"
            #include "ghost/impl/ghost_impl_libc_asm.h"
            #include "ghost/impl/ghost_impl_libc_noexcept.h"
            #include "ghost/language/ghost_restrict.h"
            #include "ghost/language/ghost_dllimport.h"

            #if GHOST_IMPL_LIBC_ASM
                ghost_dllimport
                int ghost_vasprintf(char** ghost_restrict /*out*/ str, const char* ghost_restrict format, va_list args)
                    ghost_impl_libc_noexcept(ghost_impl_libc_asm("vasprintf"));
            #else
                #include "ghost/language/ghost_null.h"
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/preprocessor/ghost_nothing.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                int ghost_vasprintf(char** ghost_restrict /*out*/ str, const char* ghost_restrict format, va_list args) {
                    int ret;

                    ghost_dllimport
                    extern int vasprintf(char** ghost_restrict /*out*/ str, const char* ghost_restrict format, va_list args)
                        ghost_impl_libc_noexcept(GHOST_NOTHING);

                    ret = vasprintf(str, format, args);

                    /* Explicitly null out str on error */
                    if (ret < 0)
                        *str = ghost_null;
                    return ret;
                }
                GHOST_IMPL_FUNCTION_CLOSE
            #endif
            #define ghost_has_ghost_vasprintf 1
        #endif
    #endif
#endif

/* Otherwise implement it with vsnprintf(). */
#ifndef ghost_has_ghost_vasprintf
    #include "ghost/format/ghost_vsnprintf.h"
    #include "ghost/malloc/ghost_memdup.h"
    #include "ghost/malloc/ghost_free.h"
    #include "ghost/malloc/ghost_alloc_array.h"
    #include "ghost/language/ghost_va_copy.h"
    #if ghost_has(ghost_vsnprintf) && ghost_has(ghost_memdup) && \
            ghost_has(ghost_free) && ghost_has(ghost_alloc_array) && \
            ghost_has(ghost_va_copy)

        /* We first try to format to a small stack-allocated buffer to try to
         * avoid formatting twice. You can override the size of this buffer if
         * you like. */
        #ifndef GHOST_VSNPRINTF_STACK_BUFFER_SIZE
            #define GHOST_VSNPRINTF_STACK_BUFFER_SIZE 128
        #endif

        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/language/ghost_restrict.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/string/ghost_memcpy.h"
        #include "ghost/debug/ghost_assert.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_function
        int ghost_vasprintf(char** ghost_restrict /*out*/ str,
                const char* ghost_restrict format, va_list args)
        #if !GHOST_EMIT_DEFS
        ;
        #else
        {
            /* Try to format to a stack-allocated buffer */
            char buffer[GHOST_VSNPRINTF_STACK_BUFFER_SIZE];
            va_list temp_args;
            int ret;
            size_t size;

            ghost_va_copy(temp_args, args);
            ret = ghost_vsnprintf(buffer, sizeof(buffer), format, temp_args);
            va_end(temp_args);
            if (ret == -1) {
                *str = ghost_null;
                return ret;
            }
            ghost_assert(ret >= 1, "vsnprintf() returned negative size"); /* make sure size isn't "negative" */

            /* If it fit, allocate a copy */
            size = 1 + ghost_static_cast(size_t, ret);
            if (size <= sizeof(buffer)) {
                ghost_assert(buffer[size - 1] == '\0', "vsnprintf() did not null-terminate");
                *str = ghost_static_cast(char*, ghost_memdup(buffer, size));
                if (*str == ghost_null)
                    return -1;
                return ret;
            }

            /* Otherwise allocate the correct size and re-format. */
            *str = ghost_alloc_array(char, size);
            if (*str == ghost_null)
                return -1;
            ret = ghost_vsnprintf(*str, size, format, args);
            if (ret == -1) {
                /* This shouldn't be possible; it worked the first time. We
                 * check anyway to be sure. */
                ghost_free(*str);
                *str = ghost_null;
                return ret;
            }
            ghost_assert(1 + ghost_static_cast(size_t, ret) == size, "vsnprintf() size changed");
            ghost_assert((*str)[size - 1] == '\0', "vsnprintf() did not null-terminate");
            return ret;
        }
        #endif
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_vasprintf 1
    #endif
#endif

#ifndef ghost_has_ghost_vasprintf
    #define ghost_has_ghost_vasprintf 0
#endif

#endif
