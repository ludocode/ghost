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

#ifndef GHOST_STRDUP_H_INCLUDED
#define GHOST_STRDUP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns an allocated copy of the given string.
 */
char* ghost_strdup(const char* s);
#endif

/* Override is handled in ghost_malloc_system.h */
#include "ghost/malloc/ghost_malloc_system.h"

/* If we're using the system malloc, we can use a builtin strdup. It generally
 * compiles to a call to libc strdup. */
#if 0/*TODO*/
#ifndef ghost_has_ghost_strdup
    #if GHOST_MALLOC_SYSTEM
        /* If we have __has_builtin we check. */
        #include "ghost/preprocessor/ghost_has_builtin.h"
        #if ghost_has(ghost_has_builtin)
            #if __has_builtin(__builtin_strdup)
                #define ghost_strdup __builtin_strdup
                #define ghost_has_ghost_strdup 1
            #endif
        #else
            #include "ghost/detect/ghost_gcc.h"
            #if GHOST_GCC
                /* __builtin_strdup has been around since at least GCC 4. We assume
                 * it exists if we're using the system malloc, which we've checked
                 * above. */
                #if __GNUC__ >= 4
                    #define ghost_strdup __builtin_strdup
                    #define ghost_has_ghost_strdup 1
                #endif
            #endif
        #endif
    #endif
#endif
#endif

/* strdup is in C23, but it's provided by the libc, not the compiler. It's
 * possible to use third-party C23 compilers with old libcs which would mean
 * strdup() would not exist. There isn't really a way to detect this. For now
 * we don't bother checking for C23. We try to detect libc strdup below. */

/* Windows supports strdup but it's a deprecated alias to _strdup. */
#ifndef ghost_has_ghost_strdup
    #if GHOST_MALLOC_SYSTEM
        #ifdef _WIN32
            #include "ghost/header/c/ghost_string_h.h"
            #include "ghost/impl/ghost_impl_always_inline.h"
            #include "ghost/impl/malloc/ghost_impl_attrib_malloc.h"

            GHOST_IMPL_FUNCTION_OPEN

            GHOST_IMPL_ATTRIB_MALLOC
            ghost_impl_always_inline
            char* ghost_strdup(const char* s) {
                return _strdup(s);
            }

            GHOST_IMPL_FUNCTION_CLOSE

            #define ghost_has_ghost_strdup 1
        #endif
    #endif
#endif

/* Linux libcs have this, but glibc and others only declare it under certain
 * conditions so we wrap it and declare it ourselves. */
#ifndef ghost_has_ghost_strdup
    #if GHOST_MALLOC_SYSTEM
        #ifdef __linux__
            #include "ghost/impl/ghost_impl_always_inline.h"
            #include "ghost/impl/ghost_impl_libc_asm.h"
            #include "ghost/impl/ghost_impl_libc_noexcept.h"
            #include "ghost/preprocessor/ghost_nothing.h"
            #include "ghost/impl/malloc/ghost_impl_attrib_malloc.h"
            #include "ghost/language/ghost_dllimport.h"

            GHOST_IMPL_FUNCTION_OPEN

            GHOST_IMPL_ATTRIB_MALLOC
            ghost_impl_always_inline
            char* ghost_strdup(const char* s) {
                /* https://pubs.opengroup.org/onlinepubs/9699919799/functions/strdup.html
                 * https://en.cppreference.com/w/c/string/byte/strdup */
                #if GHOST_IMPL_LIBC_ASM
                    ghost_dllimport
                    char* ghost_impl_ex_strdup(const char* s)
                        ghost_impl_libc_noexcept(ghost_impl_libc_asm("strdup"));
                    return ghost_impl_ex_strdup(s);
                #else
                    ghost_dllimport
                    char* strdup(const char* s)
                        ghost_impl_libc_noexcept(GHOST_NOTHING);
                    return strdup(s);
                #endif
            }

            GHOST_IMPL_FUNCTION_CLOSE

            #define ghost_has_ghost_strdup 1
        #endif
    #endif
#endif

/* Many other platforms surely support strdup(). We should at least detect
 * POSIX 2008 support and use it, and we can add support for more platforms as
 * Ghost improves support for them. In the meantime the below plain C
 * implementation will work everywhere. */

/* Otherwise, provided we have malloc(), we implement our own. */
#ifndef ghost_has_ghost_strdup
    #include "ghost/malloc/ghost_malloc.h"
    #if ghost_has(ghost_malloc)
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_bless.h"
        #include "ghost/string/ghost_memcpy.h"
        #include "ghost/string/ghost_strlen.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_malloc.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_MALLOC
        ghost_impl_function
        char* ghost_strdup(const char* s) {
            /* include the null-terminator */
            ghost_size_t size = ghost_strlen(s) + 1;
            char* p = ghost_bless(char, size, ghost_malloc(size));
            if (p)
                ghost_memcpy(p, s, size);
            return p;
        }

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_has_ghost_strdup 1
    #endif
#endif

/* Without malloc() we have no strdup(). */
#ifndef ghost_has_ghost_strdup
    #define ghost_has_ghost_strdup 0
#endif

#endif
