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

#ifndef GHOST_STRSEP_H_INCLUDED
#define GHOST_STRSEP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Splits a string into tokens separated by any character from the given set of
 * delimiters, replacing the delimiters with null terminators in the string.
 *
 * The string pointed to is searched for any character in the given delimiter
 * set.
 *
 * - If a delimiter is found, the character is replaced by a null-terminator,
 *   the string pointer is updated to the start of the next token, and the
 *   token is returned.
 *
 * - If a delimiter is not found, the remaining token is returned and the
 *   string pointed to is updated to null.
 *
 * - If the string pointed to is null, null is returned.
 *
 * In other words you can just loop on this passing the same arguments each
 * time until you get null.
 *
 * This is a better replacement for strtok(). It still has the limitation that
 * it modifies the given string, but it is re-entrant, it is simpler to use
 * than strtok_r(), and it supports empty tokens.
 */
char* ghost_strsep(char** restrict string, const char* restrict delimiters);
#endif

/* TODO glibc has this
 * TODO the BSDs have this, does libbsd? */

#ifndef ghost_has_ghost_strsep
    #ifdef ghost_strsep
        #define ghost_has_ghost_strsep 1
    #endif
#endif

/*
 * The BSDs and macOS provide strsep().
 *
 *     https://man.openbsd.org/strsep
 *     https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/strsep.3.html
 */
#ifndef ghost_has_ghost_strsep
    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
            defined(__DragonFly__) || defined(__APPLE__)
        #include "ghost/header/c/ghost_string_h.h"
        #define ghost_strsep strsep
        #define ghost_has_ghost_strsep 1
    #endif
#endif

/* Linux glibc/uClibc provide strsep() but they hide it under _GNU_SOURCE. */
#ifndef ghost_has_ghost_strsep
    #ifdef __linux__
        #include "ghost/detect/ghost_libc.h"
        #include "ghost/impl/ghost_impl_glibc_compat.h"
        #if defined(__GLIBC__) && GHOST_GLIBC_COMPAT == 0
            #include "ghost/language/ghost_asm_label.h"
            #include "ghost/language/ghost_dllimport.h"
            #include "ghost/impl/ghost_impl_libc_asm.h"
            #include "ghost/impl/ghost_impl_libc_noexcept.h"
            #include "ghost/preprocessor/ghost_nothing.h"
            #if GHOST_IMPL_LIBC_ASM
                #include "ghost/language/ghost_extern_c.h"
                ghost_extern_c
                ghost_dllimport
                char* ghost_strsep(char** sp, const char* delimiters)
                    ghost_impl_libc_noexcept(ghost_impl_libc_asm("strsep"));
            #else
                #include "ghost/impl/ghost_impl_always_inline.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                char* ghost_strsep(char** sp, const char* delimiters) {
                    ghost_dllimport
                    char* strsep(char** sp, const char* delimiters)
                        ghost_impl_libc_noexcept(GHOST_NOTHING);
                    return strsep(sp, delimiters);
                }
                GHOST_IMPL_FUNCTION_CLOSE
            #endif
            #define ghost_has_ghost_strsep 1
        #endif
    #endif
#endif

/* Otherwise implement in plain C. */
#ifndef ghost_has_ghost_strsep
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/language/ghost_null.h"

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_strsep(char** sp, const char* delimiters) GHOST_IMPL_DEF({
        char* token;
        char* s = *sp;
        if (s == ghost_null) {
            /* no tokens left. */
            return ghost_null;
        }

        token = s;
        while (*s != '\000') {
            const char* k;
            for (k = delimiters; *k != '\000'; ++k) {
                if (*s == *k) {
                    /* found a delimiter! */
                    *s = '\000';
                    *sp = s + 1;
                    return token;
                }
            }
            ++s;
        }

        /* no delimiter, this is the last token. */
        *sp = ghost_null;
        return token;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strsep 1
#endif

#endif
