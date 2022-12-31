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

#ifndef GHOST_HAS_BUILTIN_H_INCLUDED
#define GHOST_HAS_BUILTIN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_has(ghost_has_builtin)
 *
 * Detects whether __has_builtin exists and works properly.
 *
 * Ghost does not actually define ghost_has_builtin. This is a Ghost feature
 * called "ghost_has_builtin" which detects __has_builtin support. Check for a
 * builtin like this:
 *
 *     #include "ghost/preprocessor/ghost_has_builtin.h"
 *     #if ghost_has(ghost_has_builtin)
 *         #if __has_builtin(__builtin_memcmp)
 *             // the builtin almost certainly exists
 *         #else
 *             // the builtin almost certainly does not exist
 *         #endif
 *     #else
 *         // the builtin probably does not exist but you may want to do a
 *         // version check if you want to support old versions of GCC.
 *     #endif
 *
 * We say "almost certainly" above because there is some confusion about what
 * predefined identifiers are considered by compilers to be builtins, and some
 * compiler versions also have bugs that misreport whether particular builtins
 * are available on particular architectures.
 *
 * This exists to wrap compilers and libraries that improperly define
 * __has_builtin. For example Qt does this:
 *
 *  #ifndef __has_builtin
 *  #define __has_builtin(x) 0
 *  #endif
 *
 * See: https://github.com/qt/qtbase/blob/b885820c395a0bbfb0ff55ab0ee47a4703aa6b59/src/corelib/global/qcompilerdetection.h#L420-L422
 *
 * Protocol Buffers does the same. See: https://github.com/protocolbuffers/protobuf/blob/main/src/google/protobuf/port_def.inc#L113-L119 TODO permalink
 *
 * These interfere with Ghost's detection of builtins. Compilers have supported
 * builtins long before __has_builtin existed; it was only added in GCC 10.
 * Ghost therefore has fallbacks that detect builtins by other means. The above
 * hacks break this.
 *
 * Please file bug reports against Qt, Protocol Buffers and any other libraries
 * that do this. There is no reason why they can't just #ifdef __has_builtin
 * everywhere they use it.
 *
 * In addition, compilers that use GCC's preprocessor will also be using GCC's
 * __has_builtin. This gives incorrect results. We need to disable
 * __has_builtin on these compilers.
 */
#endif

#ifndef ghost_has_ghost_has_builtin
    #ifdef ghost_has_builtin
        #error "ghost_has_builtin cannot be defined. Define ghost_has_ghost_has_builtin to 1 or 0 to override Ghost's __has_builtin detection."
    #endif
#endif

/* __has_builtin support requires that #ifdef evaluate it to true. */
#ifndef ghost_has_ghost_has_builtin
    #ifndef __has_builtin
        /* __has_builtin is not defined. */
        #define ghost_has_ghost_has_builtin 0
    #endif
#endif

/*
 * Certain compilers rely on the GCC or Clang preprocessor. These preprocessors
 * support __has_builtin so they report their own support for builtins, not
 * those of the compiler that will ultimately be used.
 *
 * See this bug report:
 *
 *     https://lists.sr.ht/~mcf/cproc/%3C518d2902-3691-a8ea-c125-f13ac689ec47%40ludocode.com%3E
 *
 * Currently cproc and lcc are such compilers. We disable __has_builtin on
 * them.
 */
#ifndef ghost_has_ghost_has_builtin
    #ifdef __LCC__
        #define ghost_has_ghost_has_builtin 0
    #else
        #include "ghost/detect/ghost_cproc.h"
        #if GHOST_CPROC
            #define ghost_has_ghost_has_builtin 0
        #endif
    #endif
#endif

/*
 * Test whether __has_builtin() is always 1 by checking if some non-existent
 * builtin exists.
 */
#ifndef ghost_has_ghost_has_builtin
    #if __has_builtin(__builtin_ghost_nonexistent_builtin)
        /* __has_builtin() is lying. It's always saying 1. */
        #define ghost_has_ghost_has_builtin 0
    #endif
#endif

/*
 * Test whether __has_builtin works by checking whether it detects something.
 *
 * For now we're going to assume that any compiler that supports __has_builtin
 * will also support at least one of the below builtins. If __has_builtin
 * reports that none of them exist, we'll assume __has_builtin is broken.
 *
 * This unfortunately means that any future compiler that wants to implement
 * __has_builtin will also need to implement at least one of these in order for
 * Ghost to detect it. I don't know any other way to work around those rude
 * libraries that define __has_builtin to nonsense. We want to avoid putting
 * any limitations on future compilers so we specify lots of them.
 *
 * Note that older versions of some compilers only detected builtin functions
 * with __has_builtin, not keywords or other symbols like __builtin_launder or
 * __builtin_types_compatible_p. We make sure we have lots of functions in
 * addition to other expressions. See:
 *
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66970
 *
 * Probably the most likely to exist are those that are required to implement
 * common platform features but can't be implemented in the language itself,
 * e.g. __builtin_alloca(). See for example the list of builtins Kefir needed
 * to implement to support Linux libcs:
 *
 *     https://github.com/protopopov1122/kefir/blob/f3ce7f4380c2435f72ab380c8ebfbc59ef187ee2/README.md#built-ins
 */
#ifndef ghost_has_ghost_has_builtin
    #if \
            !__has_builtin(__builtin__Exit) && \
            !__has_builtin(__builtin_add_overflow) && \
            !__has_builtin(__builtin_alloca) && \
            !__has_builtin(__builtin_bcmp) && \
            !__has_builtin(__builtin_bit_cast) && \
            !__has_builtin(__builtin_bswap16) && \
            !__has_builtin(__builtin_bswap32) && \
            !__has_builtin(__builtin_bzero) && \
            !__has_builtin(__builtin_ceil) && \
            !__has_builtin(__builtin_choose_expr) && \
            !__has_builtin(__builtin_clear_padding) && \
            !__has_builtin(__builtin_constant_p) && \
            !__has_builtin(__builtin_ctz) && \
            !__has_builtin(__builtin_debugtrap) && \
            !__has_builtin(__builtin_expect) && \
            !__has_builtin(__builtin_fabs) && \
            !__has_builtin(__builtin_ffs) && \
            !__has_builtin(__builtin_floor) && \
            !__has_builtin(__builtin_free) && \
            !__has_builtin(__builtin_has_attribute) && \
            !__has_builtin(__builtin_huge_val) && \
            !__has_builtin(__builtin_inf) && \
            !__has_builtin(__builtin_isalnum) && \
            !__has_builtin(__builtin_isfinite) && \
            !__has_builtin(__builtin_isgreater) && \
            !__has_builtin(__builtin_isgreaterequal) && \
            !__has_builtin(__builtin_isinf) && \
            !__has_builtin(__builtin_isless) && \
            !__has_builtin(__builtin_islessequal) && \
            !__has_builtin(__builtin_islessgreater) && \
            !__has_builtin(__builtin_islower) && \
            !__has_builtin(__builtin_isnan) && \
            !__has_builtin(__builtin_isprint) && \
            !__has_builtin(__builtin_ispunct) && \
            !__has_builtin(__builtin_isspace) && \
            !__has_builtin(__builtin_isunordered) && \
            !__has_builtin(__builtin_isupper) && \
            !__has_builtin(__builtin_launder) && \
            !__has_builtin(__builtin_lround) && \
            !__has_builtin(__builtin_malloc) && \
            !__has_builtin(__builtin_memcmp) && \
            !__has_builtin(__builtin_memcpy) && \
            !__has_builtin(__builtin_memmove) && \
            !__has_builtin(__builtin_memset) && \
            !__has_builtin(__builtin_mul_overflow) && \
            !__has_builtin(__builtin_nan) && \
            !__has_builtin(__builtin_object_size) && \
            !__has_builtin(__builtin_offsetof) && \
            !__has_builtin(__builtin_popcount) && \
            !__has_builtin(__builtin_realloc) && \
            !__has_builtin(__builtin_rotateleft16) && \
            !__has_builtin(__builtin_rotateleft32) && \
            !__has_builtin(__builtin_round) && \
            !__has_builtin(__builtin_snprintf) && \
            !__has_builtin(__builtin_sprintf) && \
            !__has_builtin(__builtin_sqrt) && \
            !__has_builtin(__builtin_strcat) && \
            !__has_builtin(__builtin_strcmp) && \
            !__has_builtin(__builtin_strcpy) && \
            !__has_builtin(__builtin_strlen) && \
            !__has_builtin(__builtin_strncpy) && \
            !__has_builtin(__builtin_strnlen) && \
            !__has_builtin(__builtin_sub_overflow) && \
            !__has_builtin(__builtin_trap) && \
            !__has_builtin(__builtin_types_compatible_p) && \
            !__has_builtin(__builtin_unreachable) && \
            !__has_builtin(__builtin_va_list) && \
            !__has_builtin(__builtin_va_arg) && \
            !__has_builtin(__builtin_va_copy)
        /* __has_builtin() claims to not support any of the above builtins.
         * We'll assume it's lying. */
        #define ghost_has_ghost_has_builtin 0
    #endif
#endif

/* We've passed all the above checks so we believe __has_builtin works. */
#ifndef ghost_has_ghost_has_builtin
    #define ghost_has_ghost_has_builtin 1
#endif

#endif
