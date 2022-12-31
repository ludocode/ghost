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

#ifndef GHOST_STRTOK_R_H_INCLUDED
#define GHOST_STRTOK_R_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 */
char* ghost_strtok_r(char* restrict string, const char* restrict delimiters,
        char** restrict save_state);
#endif

#ifndef ghost_has_ghost_strtok_r
    #ifdef ghost_strtok_r
        #define ghost_has_ghost_strtok_r 1
    #endif
#endif

/* The BSDs and macOS support strtok_r().
 *     https://man.openbsd.org/strtok_r.3 */
#ifndef ghost_has_ghost_strtok_r
    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
            defined(__DragonFly__) || defined(__APPLE__)
        #include "ghost/header/c/ghost_string_h.h"
        #if ghost_has(ghost_string_h)
            #define ghost_strtok_r strtok_r
            #define ghost_has_ghost_strtok_r 1
        #endif
    #endif
#endif

/* Windows supports this but calls it strtok_s() instead. */
#ifndef ghost_has_ghost_strtok_r
    #ifdef _WIN32
        #include "ghost/header/c/ghost_string_h.h"
        #define ghost_strtok_r strtok_s
        #define ghost_has_ghost_strtok_r 1
    #endif
#endif

/* glibc and musl support this but only under _POSIX_C_SOURCE (or various other
 * feature test macros.) */
#ifndef ghost_has_ghost_strtok_r
    #include "ghost/detect/ghost_libc.h"
    #include "ghost/detect/ghost_glibc.h"
    #include "ghost/detect/ghost_musl.h"
    #include "ghost/impl/ghost_impl_glibc_compat.h"
    #if (defined(__GLIBC__) && GHOST_GLIBC_COMPAT == 0) || GHOST_MUSL
        #include "ghost/language/ghost_asm_label.h"
        #include "ghost/language/ghost_dllimport.h"
        #include "ghost/language/ghost_restrict.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/impl/ghost_impl_libc_noexcept.h"
        #include "ghost/preprocessor/ghost_nothing.h"

        #if GHOST_IMPL_LIBC_ASM
            #include "ghost/language/ghost_extern_c.h"
            ghost_extern_c
            ghost_dllimport
            char* ghost_strtok_r(char* ghost_restrict ghost_impl_v_str,
                    const char* ghost_restrict ghost_impl_v_delims,
                    char** ghost_restrict ghost_impl_v_state)
                ghost_impl_libc_noexcept(ghost_impl_libc_asm("strtok_r"));
        #else
            #include "ghost/impl/ghost_impl_always_inline.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            char* ghost_strtok_r(char* ghost_restrict ghost_impl_v_str,
                    const char* ghost_restrict ghost_impl_v_delims,
                    char** ghost_restrict ghost_impl_v_state)
            {
                ghost_dllimport
                char* strtok_r(char* ghost_restrict ghost_impl_v_str,
                        const char* ghost_restrict ghost_impl_v_delims,
                        char** ghost_restrict ghost_impl_v_state)
                    ghost_impl_libc_noexcept(GHOST_NOTHING);
                return strtok_r(ghost_impl_v_str, ghost_impl_v_delims, ghost_impl_v_state);
            }
            GHOST_IMPL_FUNCTION_CLOSE
        #endif
        #define ghost_has_ghost_strtok_r 1
    #endif
#endif

/* TODO it is also apparently also in POSIX-2001. We should detect this. */

/* TODO other platforms support this, beware that they may require *saveptr be
 * null on the first call. when wrapping we should do this ourselves if the
 * platform requires it. */

/* TODO test this */
/* If we don't have platform support, implement it using strsep(). */
#ifndef ghost_has_ghost_strtok_r
    #include "ghost/string/ghost_strsep.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/language/ghost_null.h"
    #include "ghost/language/ghost_restrict.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_strtok_r(char* ghost_restrict ghost_impl_v_str,
            const char* ghost_restrict ghost_impl_v_delims,
            char** ghost_restrict ghost_impl_v_state)
    GHOST_IMPL_DEF({
        char* ret;
        if (ghost_impl_v_str != ghost_null)
            *ghost_impl_v_state = ghost_impl_v_str;
        /* strsep() supports empty tokens; strtok_r() does not. loop to skip them. */
        do {
            ret = ghost_strsep(ghost_impl_v_state, ghost_impl_v_delims);
        } while (ret != ghost_null && *ret == '\0');
        return ret;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strtok_r 1
#endif

#endif
