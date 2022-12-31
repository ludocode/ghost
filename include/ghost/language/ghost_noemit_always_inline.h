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

#ifndef GHOST_NOEMIT_ALWAYS_INLINE_H_INCLUDED
#define GHOST_NOEMIT_ALWAYS_INLINE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_noemit_always_inline inline [[always_inline]]
 *
 * Declares a function inline with external linkage without
 * emitting a definition of it with external linkage in this translation unit,
 * and suggests to the compiler that it should always try to inline it
 * regardless of optimization settings or heuristics.
 *
 * On modern compilers, the function will be inlined wherever possible even if
 * optimizations are off. This can make debugging difficult. See @ref
 * ghost_always_inline for more details.
 *
 * In C++, a definition is always emitted with COMDAT linkage. A C++ linker is
 * required to collapse multiple definitions of the function.
 *
 * @warning In order to merge inline definitions between C and C++ translation
 * units, you need to declare your functions extern "C". If you don't, C++
 * functions will be name-mangled and C ones won't so you'll end up with two
 * definitions of each function in the final link.
 *
 * See ghost_emit_inline for usage instructions.
 *
 * @see ghost_emit_always_inline
 * @see ghost_emit_inline
 * @see ghost_noemit_inline
 */
#endif

#ifndef ghost_has_ghost_noemit_always_inline
    #ifdef ghost_noemit_always_inline
        #define ghost_has_ghost_noemit_always_inline 1
    #endif
#endif

/* We need ghost_always_inline, which falls back to inline. If we don't have
 * inline (or it doesn't behave properly, e.g. on older versions of TinyCC), we
 * won't have this either. */
#ifndef ghost_has_ghost_emit_always_inline
    #include "ghost/language/ghost_always_inline.h"
    #if !ghost_has(ghost_always_inline)
        #define ghost_has_ghost_emit_always_inline 0
    #endif
#endif

/*
 * C++ rules
 *
 * The linker will need COMDAT support to link C++ object files so we don't
 * need to worry about emitting additional definitions from C++ translation
 * units. Compilation speed will be slower because the function will be
 * compiled in all translation units.
 */
#ifndef ghost_has_ghost_noemit_always_inline
    #ifdef __cplusplus
        #define ghost_noemit_always_inline ghost_always_inline
        #define ghost_has_ghost_noemit_always_inline 1
    #endif
#endif

/* MSVC >=2015 always uses COMDAT linkage even in C. */
#ifndef ghost_has_ghost_noemit_always_inline
    #ifdef _MSC_VER
        #if _MSC_VER >= 1900
            #define ghost_noemit_always_inline ghost_always_inline
            #define ghost_has_ghost_noemit_always_inline 1
        #endif
    #endif
#endif

/* GNU rules */
#ifndef ghost_has_ghost_noemit_always_inline
    #if defined(__GNUC__) && (defined(__GNUC_GNU_INLINE__) || \
            (!defined(__GNUC_STDC_INLINE__) && !defined(__GNUC_GNU_INLINE__)))
        #define ghost_noemit_always_inline extern ghost_always_inline
        #define ghost_has_ghost_noemit_always_inline 1
    #endif
#endif

/* C99 rules */
#ifndef ghost_has_ghost_noemit_always_inline
    #if defined(__STDC_VERSION__)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 199901L
            #define ghost_noemit_always_inline ghost_always_inline
            #define ghost_has_ghost_noemit_always_inline 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_noemit_always_inline
    #define ghost_has_ghost_noemit_always_inline 0
#endif

#endif
