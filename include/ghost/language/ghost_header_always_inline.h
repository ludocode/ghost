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

#ifndef GHOST_HEADER_ALWAYS_INLINE_H_INCLUDED
#define GHOST_HEADER_ALWAYS_INLINE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_header_always_inline [[selectany]] [[always_inline]] inline
 *
 * Declares an always-inline function that can appear in multiple translation
 * units (e.g. in a header file) using the best linkage mechanism available.
 *
 * This is useful for defining very small or performance-sensitive functions in
 * header files and in header-only libraries.
 *
 * Example:
 *
 *     ghost_header_always_inline
 *     void foo(...) {
 *         ...
 *     }
 *
 * If the implementation supports a form of automatic "selectany" or "linkonce"
 * linkage with always_inline (e.g. COMDAT linkage), this will use it.
 * Otherwise it will declare the function static always_inline.
 *
 * A standalone definition will be emitted if required (for example if the
 * function cannot be inlined) but otherwise may or may not be emitted
 * depending on the implementation.
 *
 * Note that static functions and function inlining can cause code bloat. If
 * the function should not or cannot be inlined (for example if it is large, if
 * its address is taken, if it is variadic, etc.), consider using
 * ghost_header_function instead.
 *
 * Note that always_inline functions are inlined even in unoptimized debug
 * builds. Consider using ghost_header_inline instead.
 *
 * If you are supporting both C and C++ you will want to ensure the function is
 * in an `extern "C"` block. If not, an additional name-mangled definition may
 * be emitted in C++.
 *
 * @see ghost_header_inline
 * @see ghost_header_function
 * @see ghost_header_noinline
 */
#endif

#ifndef ghost_has_ghost_header_always_inline
    #ifdef ghost_header_always_inline
        #define ghost_has_ghost_header_always_inline 1
    #endif
#endif

/* C++ rules */
#ifndef ghost_has_ghost_header_always_inline
    #if defined(__cplusplus)
        #include "ghost/language/ghost_always_inline.h"
        #define ghost_header_always_inline ghost_always_inline
        #define ghost_has_ghost_header_always_inline 1
    #endif
#endif

/* MSVC >=2015 always uses COMDAT linkage even in C. */
#ifndef ghost_has_ghost_header_always_inline
    #if defined(_MSC_VER)
        #if _MSC_VER >= 1900
            #include "ghost/language/ghost_always_inline.h"
            #define ghost_header_always_inline ghost_always_inline
            #define ghost_has_ghost_header_always_inline 1
        #endif
    #endif
#endif

/* Use static always_inline if we have always_inline */
#ifndef ghost_has_ghost_header_always_inline
    #include "ghost/language/ghost_always_inline.h"
    #if ghost_has(ghost_always_inline)
        #define ghost_header_always_inline ghost_always_inline static
        #define ghost_has_ghost_header_always_inline 1
    #endif
#endif

/* Otherwise use static maybe_unused. */
#ifndef ghost_has_ghost_header_always_inline
    #include "ghost/language/ghost_maybe_unused.h"
    #define ghost_header_always_inline ghost_maybe_unused static
    #define ghost_has_ghost_header_always_inline 1
#endif

#endif
