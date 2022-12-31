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

#ifndef GHOST_TYPEOF_H_INCLUDED
#define GHOST_TYPEOF_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * ghost_typeof(T) -- Use the type of an expression as a typename
 *
 * This is similar to sizeof except it evaluates to the type of an expression
 * rather than its size. This can be used anywhere a type name is expected.
 *
 * ghost_typeof() preserves all qualifiers including const, volatile, restrict,
 * _Atomic, etc. Use ghost_remove_quals() if you want to strip qualifiers.
 *
 * This is a compiler extension that is not (yet) available in standard C.
 * Check `ghost_has(ghost_typeof)` to see if this is implemented.
 *
 * @see ghost_remove_quals
 */
#endif

/* ghost_typeof() requires parentheses. We fully parenthesize all
 * implementations below to make sure it can't be used without them (the way
 * sizeof is for example.) */

#ifndef ghost_has_ghost_typeof
    #ifdef ghost_typeof
        #define ghost_has_ghost_typeof 1
    #endif
#endif

/* C23 will have typeof! */
#ifndef ghost_has_ghost_typeof
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
            #define ghost_typeof(T) typeof(T)
            #define ghost_has_ghost_typeof 1
        #endif
    #endif
#endif

/* Compiler-specific extensions */
#ifndef ghost_has_ghost_typeof
    #ifdef __GNUC__
        /* https://gcc.gnu.org/onlinedocs/gcc/Typeof.html */
        #define ghost_typeof(T) __typeof__(T)
        #define ghost_has_ghost_typeof 1
    #endif
#endif

/*
 * C++11 has decltype() but it's not exactly the same as typeof(). If the
 * argument is parenthesized it returns references to lvalues and r-value
 * references to xvalues. We need to strip these references.
 *
 *     https://en.cppreference.com/w/cpp/language/decltype
 *
 * Note that this will strip a reference even if the type truly is a reference,
 * e.g. ghost_typeof(int&) is int, not int&. ghost_typeof() exists for
 * compatibility with C. If you are using C++ references or other C++ types,
 * you should use decltype() directly.
 *
 * See the comparisons between typeof() and decltype() here:
 *
 *     https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2899.htm#existing-decltype
 *     https://thephd.dev/ever-closer-c23-improvements#c-has-decltype-why-not-decltype
 */
#ifndef ghost_has_ghost_typeof
    #ifdef __cplusplus
        #if __cplusplus >= 201103L
            #include "ghost/header/cxx/ghost_cxx_type_traits_h.h"
            #if ghost_has(ghost_cxx_type_traits_h)
                /* https://en.cppreference.com/w/cpp/language/decltype
                 * https://en.cppreference.com/w/cpp/types/remove_reference */
                #define ghost_typeof(T) std::remove_reference<decltype(T)>::type
                #define ghost_has_ghost_typeof 1
            #endif
        #endif
    #endif
#endif

/* Otherwise we don't have support for ghost_typeof(). */
#ifndef ghost_has_ghost_typeof
    #define ghost_has_ghost_typeof 0
#endif

#endif
