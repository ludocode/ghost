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

#ifndef GHOST_STRNDUP_H_INCLUDED
#define GHOST_STRNDUP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns an allocated copy of the given string limited to the given length
 * (not including the null terminator.)
 *
 * The resulting allocation will be at most `max_length + 1` bytes and will
 * always be null-terminated.
 *
 * If allocation fails, null is returned.
 */
char* ghost_strndup(const char* s, size_t max_length);
#endif

/* Override is handled in ghost_malloc_system.h */
#include "ghost/malloc/ghost_malloc_system.h"

/* If we don't have malloc, we won't have strndup either. */
/* TODO why is this necessary */
#ifndef ghost_has_ghost_strndup
    #include "ghost/malloc/ghost_malloc.h"
    #if !ghost_has_ghost_malloc
        #define ghost_has_ghost_strndup 0
    #endif
#endif

/* If we're using the system malloc, we can use a builtin strndup. It generally
 * compiles to a call to libc strndup. */
#ifndef ghost_has_ghost_strnlen
    #if GHOST_MALLOC_SYSTEM
        /* If we have __has_builtin we check. */
        #include "ghost/preprocessor/ghost_has_builtin.h"
        #if ghost_has(ghost_has_builtin)
            #if __has_builtin(__builtin_strndup)
                #define ghost_strndup __builtin_strndup
                #define ghost_has_ghost_strndup 1
            #endif
        #else
            #include "ghost/detect/ghost_gcc.h"
            #if GHOST_GCC
                /* __builtin_strndup has been around since at least GCC 4. We assume
                 * it exists if we're using the system malloc, which we've checked
                 * above. */
                #if __GNUC__ >= 4
                    #define ghost_strndup __builtin_strndup
                    #define ghost_has_ghost_strndup 1
                #endif
            #endif
        #endif
    #endif
#endif

/* If we're using the system malloc, we can also use the system strndup if we
 * have one. glibc and probably others only declare it under certain conditions
 * so we wrap it and declare it ourselves. */
#if !defined(ghost_has_ghost_strndup) && GHOST_MALLOC_SYSTEM

    /* We assume all UNIX platforms support it because it's in POSIX 2008. We
     * could add exceptions for older platforms or make this more conservative
     * if this is not accurate enough.
     * Note also that strndup will be in C23. We can add a check for it when
     * it's officially released.
     * TODO use GHOST_UNIX */
    /* TODO actually don't assume this at all, safer to use our fallback, see strdup() */
    #if defined(__unix__)
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/impl/ghost_impl_libc_noexcept.h"
        #include "ghost/preprocessor/ghost_nothing.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_malloc.h"
        #include "ghost/language/ghost_dllimport.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_MALLOC
        ghost_impl_function
        char* ghost_strndup(const char* s, ghost_size_t maxlen) {
            /* https://pubs.opengroup.org/onlinepubs/9699919799/functions/strdup.html
             * https://en.cppreference.com/w/c/string/byte/strndup */
            #if GHOST_IMPL_LIBC_ASM
                ghost_dllimport
                char* ghost_impl_ex_strndup(const char* s, ghost_size_t maxlen)
                    ghost_impl_libc_noexcept(ghost_impl_libc_asm("strndup"));
                return ghost_impl_ex_strndup(s, maxlen);
            #else
                ghost_dllimport
                char* strndup(const char* s, ghost_size_t maxlen)
                    ghost_impl_libc_noexcept(GHOST_NOTHING);
                return strndup(s, maxlen);
            #endif
        }

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_has_ghost_strndup 1
    #endif
#endif

/* Otherwise we implement our own. */
#ifndef ghost_has_ghost_strndup
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/malloc/ghost_alloc_array.h"
    #include "ghost/string/ghost_strnlen.h"
    #include "ghost/string/ghost_memcpy.h"
    #include "ghost/impl/malloc/ghost_impl_attrib_malloc.h"

    GHOST_IMPL_FUNCTION_OPEN

    GHOST_IMPL_ATTRIB_MALLOC
    ghost_impl_function
    char* ghost_strndup(const char* s, ghost_size_t maxlen) GHOST_IMPL_DEF({
        /* don't copy the null-terminator in case we're truncating;
         * write it ourselves afterwards */
        ghost_size_t len = ghost_strnlen(s, maxlen);
        char* p = ghost_bless(char, len + 1, ghost_malloc(len + 1));
        if (p) {
            ghost_memcpy(p, s, len);
            p[len] = '\000';
        }
        return p;
    })

    GHOST_IMPL_FUNCTION_CLOSE

    #define ghost_has_ghost_strndup 1
#endif

#endif
