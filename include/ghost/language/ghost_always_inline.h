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

#ifndef GHOST_ALWAYS_INLINE_H_INCLUDED
#define GHOST_ALWAYS_INLINE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * @def ghost_always_inline inline [[always_inline]]
 *
 * Declares this function inline and suggests to the compiler (if possible)
 * that it should always try to inline it regardless of optimization settings
 * or heuristics.
 *
 * Example:
 *
 *     ghost_always_inline
 *     static void foo(...) {
 *         ...
 *     }
 *
 * This is a function attribute only. It can't be used to declare that a
 * particular function call must be inlined. Use ghost_always_inline_stmt for
 * that instead.
 *
 * On modern compilers, the function will be inlined wherever possible even if
 * optimizations are off. This can make debugging difficult.
 *
 * It may not be possible to inline the function. Inlining can be inhibited for
 * various reasons, some of which are compiler-specific: for example if it is
 * called through a function pointer, if it uses C++ try/catch, if it has
 * variadic arguments, or if it has inline assembly.
 *
 * Some compilers (in particular MSVC) may warn if inlining fails. To silence
 * such warnings, use GHOST_SILENCE_NOT_INLINED.
 *
 * Don't specify both `inline` and `ghost_always_inline`; `inline` is implied.
 * (Some compilers complain if an always_inline attribute is combined with
 * inline while others complain if it is not. Ghost handles this for you.)
 *
 * Don't specify `ghost_maybe_unused` since this is also implied.
 *
 * If a platform does not support it, this is simply `ghost_inline` (if that is
 * supported). In C++ this can be used alone; in C you will probably want to
 * also declare the function `static` or use another attribute instead like
 * `ghost_header_always_inline` or `ghost_[no]emit_always_inline`.
 *
 * @see GHOST_SILENCE_NOT_INLINED
 * @see ghost_emit_always_inline
 */
#endif

#ifndef ghost_has_ghost_always_inline
    #ifdef ghost_always_inline
        #define ghost_has_ghost_always_inline 1
    #endif
#endif

/*
 * Use the C++11-style extension if possible.
 *
 * We need inline also to avoid warning:
 *     "always_inline function might not be inlinable [-Werror=attributes]"
 *
 * We don't use this on NVidia/PGI because the storage specifier (e.g.
 * `static`) has to come between C++11-style attributes and `inline`. The
 * `__attribute__` fallback below has no such restriction.
 */
#ifndef ghost_has_ghost_always_inline
    #if defined(__GNUC__) && !defined(__PGI)
        #include "ghost/impl/language/ghost_impl_standard_attribute.h"
        #if GHOST_IMPL_STANDARD_ATTRIBUTE
            #include "ghost/impl/language/ghost_impl_attribute_namespace_gnu.h"
            #define ghost_always_inline [[GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU::__always_inline__]] inline
            #define ghost_has_ghost_always_inline 1
        #endif
    #endif
#endif

/* MSVC has __forceinline. It cannot be combined with inline. */
#ifndef ghost_has_ghost_always_inline
    #ifdef _MSC_VER
        /*
         * Note that this can cause /W4 warning C4717:
         *
         *     "function ... marked as __forceinline not inlined"
         *
         * You may need to silence it around functions that use this. Use
         * GHOST_SILENCE_NOT_INLINED to silence it.
         *
         * Here's a list of restrictions that will prevent a function from
         * being inlined:
         *
         *     https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4714
         *
         * Most notably, functions with try/catch, varargs, or inline assembly
         * (when not optimizing) will not be force-inlined.
         */
        #define ghost_always_inline __forceinline
        #define ghost_has_ghost_always_inline 1
    #endif
#endif

/* Assume all __GNUC__ compilers support __attribute__((__always_inline__) */
#ifndef ghost_has_ghost_always_inline
    #if defined(__GNUC__)
        /*
         * We need inline also to avoid warning:
         *     "always_inline function might not be inlinable [-Werror=attributes]"
         */
        #include "ghost/language/ghost_inline.h"
        #define ghost_always_inline ghost_inline __attribute__((__always_inline__))
        #define ghost_has_ghost_always_inline 1
    #endif
#endif

/* With no support for an always_inline compiler hint, just make it inline. */
#ifndef ghost_has_ghost_always_inline
    #include "ghost/language/ghost_inline.h"
    #if ghost_has(ghost_inline)
        #define ghost_always_inline ghost_inline
        #define ghost_has_ghost_always_inline 1
    #endif
#endif

/* If we don't have inline at all, we don't have always_inline either. */
#ifndef ghost_has_ghost_always_inline
    #define ghost_has_ghost_always_inline 0
#endif

#endif
