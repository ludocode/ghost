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

#ifndef GHOST_MEMSET_EXPLICIT_H_INCLUDED
#define GHOST_MEMSET_EXPLICIT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A memset() function that will not be eliminated by compiler optimizations.
 *
 * If you're setting memory to zero, it's recommended to use
 * ghost_bzero_explicit() instead since it is supported by more platforms.
 *
 * @warning This does not erase copies of the buffer contents that may have
 *          been stored in registers, on the stack, etc.
 */
void* ghost_memset_explicit(void* dest, int c, size_t count);
#endif

/* Security-related stuff in Ghost is experimental. */
#ifndef ghost_has_ghost_memset_explicit
    #if !GHOST_EXPERIMENTAL
        #define ghost_has_ghost_memset_explicit 0
    #endif
#endif

/* We'll need to detect the libc. */
#ifndef ghost_has_ghost_bzero_explicit
    #include "ghost/detect/ghost_libc.h"
#endif

/* C23 and C++23 are supposed to add memset_explicit(). Unfortunately this is a
 * function of the libc, not of the compiler, so there isn't necessarily an
 * easy way to tell whether it's available. We'll add this as libcs start to
 * implement it. */

/* Solaris and NetBSD have explicit_memset(). */
#ifndef ghost_has_ghost_memset_explicit
    #if defined(__NetBSD__) || \
            (defined(__sun) && defined(__SVR4))
        #include "ghost/header/c/ghost_string_h.h"
        #define ghost_memset_explicit explicit_memset
        #define ghost_has_ghost_memset_explicit 1
    #endif
#endif

/*
 * C11 Annex K has memset_s(). The C11 standard prohibits elimination of
 * memory writes from this function. FreeBSD and DragonFlyBSD implement this.
 *
 * Since it's not easy to determine whether the function is actually declared,
 * we always wrap it and declare it ourselves. For now we only do this if we
 * have asm label support for simplicity.
 *
 *     https://en.cppreference.com/w/c/string/byte/memset
 *     https://www.freebsd.org/cgi/man.cgi?query=memset_s&apropos=0&sektion=0&manpath=FreeBSD+13.1-RELEASE+and+Ports&arch=default&format=html
 *     https://man.dragonflybsd.org/?command=memset_s&section=ANY
 */
#ifndef ghost_has_ghost_memset_explicit
/* TODO if we rename it with asm_label a link-time optimizer could in theory
 * inline it without the non-elision guarantees. We should be able to detect it
 * with defined(__STDC_LIB_EXT1__) && defined(__STDC_WANT_LIB_EXT1__) but that
 * doesn't actually work on FreeBSD. Might not be worth implementing this at
 * all since most platforms have some form of explicit bzero/memset already, it
 * will be in C23/C++23, and we have our own fallback. */
#if 0
    #if defined(__STDC_LIB_EXT1__) || defined(__FreeBSD__) || defined(__DragonFly__)
        #include "ghost/language/ghost_asm_label.h"
        #if ghost_has(ghost_asm_label)
            #include "ghost/impl/ghost_impl_inline.h"
            #include "ghost/type/size_t/ghost_size_t.h"
            #include "ghost/language/ghost_static_cast.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_inline
            void ghost_memset_explicit(void* ghost_impl_v_vp, int ghost_impl_v_i, ghost_size_t ghost_impl_v_count) {
                ghost_dllimport
                extern void ghost_impl_memset_explicit_memset_s(void*, ghost_size_t, int, ghost_size_t)
                    ghost_asm_label("memset_s");
                ghost_impl_memset_explicit_memset_s(ghost_impl_v_vp, ghost_impl_v_count, ghost_impl_v_i, ghost_impl_v_count);
            }
            GHOST_IMPL_FUNCTION_CLOSE
            #define ghost_has_ghost_memset_explicit 1
        #endif
    #endif
#endif
#endif

/* Otherwise we use a slow fallback implementation with volatile. See below:
 *     https://www.cryptologie.net/article/419/zeroing-memory-compiler-optimizations-and-memset_s/ */
/* TODO make sure this is safe, this is still experimental */
/* TODO some compilers (e.g. cproc) don't support volatile */
#ifndef ghost_has_ghost_memset_explicit
    #include "ghost/impl/ghost_impl_noinline.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_noinline
    void ghost_memset_explicit(void* ghost_impl_v_vp, int ghost_impl_v_i, ghost_size_t ghost_impl_v_count) {
        unsigned char ghost_impl_v_c = ghost_static_cast(unsigned char, ghost_impl_v_i);
        volatile unsigned char* volatile ghost_impl_v_p = ghost_static_cast(volatile unsigned char* volatile, ghost_impl_v_vp);
        volatile unsigned char* volatile ghost_impl_v_end = ghost_impl_v_p + ghost_impl_v_count;
        for (; ghost_impl_v_p != ghost_impl_v_end;)
            *ghost_impl_v_p++ = ghost_impl_v_c;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_memset_explicit 1
#endif

#endif
