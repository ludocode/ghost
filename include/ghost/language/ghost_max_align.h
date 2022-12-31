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

#ifndef GHOST_MAX_ALIGN_H_INCLUDED
#define GHOST_MAX_ALIGN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_max_align alignof(max_align_t)
 *
 * The largest fundamental alignment of the platform.
 *
 * This is the largest alignment of any fundamental (scalar) type. Memory
 * allocated by malloc() and friends is guaranteed to be sufficiently aligned
 * for any type up to this value.
 */
#endif

/* TODO: We may want to provide another ghost keyword to align as maximum
 * alignment (maybe ghost_alignat_max?):
 *     https://stackoverflow.com/a/19883859 */

/* C11 _Alignof(max_align_t) */
#ifndef ghost_has_ghost_max_align
    #ifdef __STDC_VERSION__
        #if __STDC_VERSION__ >= 201112L
            /* https://en.cppreference.com/w/c/language/_Alignof
             * https://en.cppreference.com/w/c/types/max_align_t */
            #define ghost_max_align _Alignof(max_align_t)
            #define ghost_has_ghost_max_align 1
        #endif
    #endif
#endif

/* C++11 alignof, alignas */
#ifndef ghost_has_ghost_max_align
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L || defined(_MSC_VER)
            /* https://en.cppreference.com/w/cpp/language/alignof
             * https://en.cppreference.com/w/cpp/types/max_align_t */
            #define ghost_max_align alignof(max_align_t)
            #define ghost_has_ghost_max_align 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_max_align

    /* GNU-style __BIGGEST_ALIGNMENT__ */
    #ifdef __BIGGEST_ALIGNMENT__
        #define ghost_max_align __BIGGEST_ALIGNMENT__
        #define ghost_has_ghost_max_align 1

    /*
     * TinyCC defines max_align_t as the larger of long long and long double
     * but it's not available by default since TinyCC defaults to C99 mode.
     * We supply a similar definition here as a fallback.
     *
     * Note that GCC and friends define __BIGGEST_ALIGNMENT__ as 16 on both
     * 32-bit and 64-bit. On 64-bit the below is also 16, but on 32-bit it's 4.
     * This may cause incompatibilities when linking together translation units
     * compiled with different compilers.
     */
    #elif defined(__TINYC__)
        #define ghost_max_align _Alignof(union {long long ghost_a; long double ghost_b;})
        #define ghost_has_ghost_max_align 1

    /* MSVC hardcoded values
     * See "fundamental alignment" here:
     *     https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/malloc */
    #elif defined(_MSC_VER)
        #if defined(_M_X64) || defined(_M_ARM64)
            #define ghost_max_align 16
            #define ghost_has_ghost_max_align 1
        #elif defined(_M_IX86) || defined(_M_ARM)
            #define ghost_max_align 8
            #define ghost_has_ghost_max_align 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_max_align
    #define ghost_has_ghost_max_align 0
#endif

#endif
