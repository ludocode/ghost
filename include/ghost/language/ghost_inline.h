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

#ifndef GHOST_INLINE_H_INCLUDED
#define GHOST_INLINE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_inline inline
 *
 * Defines `ghost_inline` as `inline` or equivalent.
 *
 * `inline` was originally intended as an optimization hint to the compiler.
 * Modern compilers generally ignore it for the purpose of optimization but it
 * still serves as an important specifier related to linkage.
 *
 * `inline` has different meanings in C versus C++. This macro does not attempt
 * to differentiate them; it merely wraps old pre-standardization synonyms such
 * as `__inline` and `__inline__`.
 *
 * In C, this may or may not emit a standalone definition of the function
 * depending on what additional linkage specifiers are given and on other
 * compiler-specific settings. You should either combine this with `static` or
 * use ghost_inline_emit and ghost_inline_no_emit instead. These let you
 * explicitly declare linkage and declare whether or not the compiler should
 * emit a standalone definition. Alternatively, just use ghost_header_inline to
 * make it fully automatic.
 *
 * In C++ this implies vague (COMDAT) linkage unless you also specify internal
 * linkage (by the static keyword or via anonymous namespace.)
 *
 * @see ghost_inline_emit
 * @see ghost_inline_no_emit
 */
#endif

#ifndef ghost_has_ghost_inline
    #ifdef ghost_inline
        #define ghost_has_ghost_inline 1
    #endif
#endif

/* TinyCC 9.27 ignores the inline keyword, which is fine for static functions
 * but it breaks C99 inline emit/noemit semantics. It does behave properly in
 * mob though and we (currently) only support mob. */

/* TODO check above
 * TinyCC declares C99 support but it doesn't properly support C99 inline semantics. It
 * just ignores the inline keyword. This leads to duplicate definitions if we
 * try to use it without static. We disable ghost_inline on TinyCC so that we
 * know we need a fallback.
 * TODO new versions of tinycc may have fixed this but the old version in Arch
 * doesn't, see if this can be fixed
 * TODO make sure all the other inline attribs support this */
#if 0
#ifndef ghost_has_ghost_inline
    #ifdef __TINYC__
        #define ghost_has_ghost_inline 0
    #endif
#endif
#endif

/* C99 has inline keyword */
#ifndef ghost_has_ghost_inline
    #ifdef __STDC_VERSION__
        #if __STDC_VERSION__ >= 199901L
            #define ghost_inline inline
            #define ghost_has_ghost_inline 1
        #endif
    #endif
#endif

/* C++ has inline keyword */
#ifndef ghost_has_ghost_inline
    #ifdef cplusplus
        #define ghost_inline inline
        #define ghost_has_ghost_inline 1
    #endif
#endif

/* GNU C compilers (GCC, Clang) support __inline__ */
#ifndef ghost_has_ghost_inline
    #ifdef __GNUC__
        #define ghost_inline __inline__
        #define ghost_has_ghost_inline 1
    #endif
#endif

/* MSVC >=2015 supports __inline */
#ifndef ghost_has_ghost_inline
    #if defined(_MSC_VER)
        /* MSVC <2015 doesn't recognize inline or even __inline as keywords in
         * C. There doesn't appear to be a way to declare an inline function in
         * C in MSVC 2013. */
        #if _MSC_VER >= 1900
            #define ghost_inline __inline
            #define ghost_has_ghost_inline 1
        #endif
    #endif
#endif

/*
 * Without any of the above, we have no way to specify inline.
 */
#ifndef ghost_has_ghost_inline
    #define ghost_has_ghost_inline 0
#endif

#endif
