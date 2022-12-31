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

#ifndef GHOST_ARRAY_COUNT_H_INCLUDED
#define GHOST_ARRAY_COUNT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_array_count(array) sizeof(array) / sizeof(array[0])
 *
 * A macro that expands at compile-time to the number of elements in the given
 * array.
 *
 * This must not be used on a pointer or any type other than an array. Note in
 * particular that if a function declares a parameter with array syntax, that
 * parameter is actually a pointer, not an array.
 *
 * This implementation attempts to check at compile time that the argument is
 * an array.
 */
#endif

/* TODO probably need to get rid of all the static asserts, it makes the expression not constant */

#ifndef ghost_has_ghost_array_count
    #ifdef ghost_array_count
        #define ghost_has_ghost_array_count 1
    #endif
#endif

/* GNU C */
#ifndef ghost_has_ghost_array_count
    #ifdef __GNUC__
        /* We make sure x and &0[x] are not the same type to ensure this isn't
         * used on a pointer (or on a C++ object that overloads operator[].)
         * TODO make this work
         * TODO add ghost_types_compatible(), it's possible to make this using _Generic and probably C++ templates as well, see: http://www.robertgamble.net/2012/01/c11-generic-selections.html
         * TODO or maybe not, in _Generic, const int is not int so this check wouldn't work */
        /*include "ghost/debug/ghost_static_assert_expr.h"*/
        #define ghost_array_count(x) \
            (/*ghost_static_assert_expr(!__builtin_types_compatible_p(x, &0[x]),*/ \
                /*"ghost_array_count() must be used on an array (not a pointer or any other type.)"),*/ \
            (sizeof(x) / sizeof((x)[0])))
        #define ghost_has_ghost_array_count 1
    #endif
#endif

/* C++ */
#ifndef ghost_has_ghost_array_count
    #ifdef __cplusplus
        /* We need constexpr for this to work so this requires C++11. */
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #include "ghost/type/size_t/ghost_size_t.h"
            template <typename T, ghost_size_t N>
            static constexpr ghost_size_t ghost_array_count_impl(T (&)[N]) {
                return N;
            }
            #define ghost_array_count(x) ghost_array_count_impl(x)
            #define ghost_has_ghost_array_count 1
        #endif
    #endif
#endif

/*
 * Note that we don't bother with MSVC's _countof(). In C++ it does something
 * a bit like the above and in C it doesn't try to check whether the argument
 * is a pointer.
 *
 *     https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/countof-macro
 */

/*
 * There's a neat implementation for C++98 by Ivan Johnson described here:
 *
 *     https://stackoverflow.com/a/6256085
 *
 * Unfortunately it's not clear what the license is, there is some skepticism
 * about how well it works, and C++98 is pretty dead anyway so I'm not
 * including it.
 */

/* Fallback in plain C
 * TODO test this */
#ifndef ghost_has_ghost_array_count
    /* We use 0[x] instead of x[0] to ensure this isn't used on a C++ object
     * that overloads operator[]. We check that sizeof(x) is a multiple of
     * sizeof(x[0]) to try to catch cases of a pointer being passed instead of
     * an array, but this won't catch such errors if the type being pointed to
     * is small. */
    /*include "ghost/debug/ghost_static_assert_expr.h"*/
    #define ghost_array_count(x) \
        (/*ghost_static_assert_expr(sizeof(x) % sizeof(0[(x)]) == 0,*/ \
            /*"ghost_array_count() must be used on an array (not a pointer or any other type.)"),*/ \
        sizeof(x) / sizeof(0[(x)]))
    #define ghost_has_ghost_array_count 1
#endif

#endif
