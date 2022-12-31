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

#ifndef GHOST_EMIT_INLINE_H_INCLUDED
#define GHOST_EMIT_INLINE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_emit_inline extern inline
 *
 * Declares a function inline with external linkage and emits a standalone
 * definition of it in this translation unit.
 *
 * In C++, a definition is always emitted with COMDAT linkage. A C++ linker is
 * required to collapse multiple definitions of the function.
 *
 * The way to use this is to define your own inline macro, say "foo_inline",
 * like this:
 *
 *     #ifdef FOO_EMIT_INLINE
 *         #define foo_inline ghost_emit_inline
 *     #else
 *         #define foo_inline ghost_noemit_inline
 *     #endif
 *
 * Then `#define FOO_EMIT_INLINE` in exactly one translation unit which
 * includes your inline functions.
 *
 * This can be done per source file: put the above in `foo.h`, use `foo_inline`
 * throughout `foo.h`, and then `#define FOO_EMIT_INLINE` at the top of
 * `foo.c`.
 *
 * Or it can be done for your whole app or library: use `foo_inline` everwhere,
 * then you or the users of your library must put the `#define` at the top of
 * one translation unit and include all of your project's headers in it.
 *
 * @warning In order to merge inline definitions between C and C++ translation
 * units, you need to declare your functions extern "C". If you don't, C++
 * functions will be name-mangled and C ones won't so you'll end up with two
 * definitions of each function in the final link.
 *
 * @see ghost_noemit_inline
 * @see ghost_emit_always_inline
 * @see ghost_noemit_always_inline
 */

/*
 * Three different linkage models need to be supported:
 *
 *  - The C99 model, where a standalone function is emitted if and only if
 *    there is any `extern inline` or non-`inline` declaration (before or
 *    after, or in the definition itself)
 *
 *  - The GNU model, where an `inline` definition emits a standalone function
 *    and an `extern inline` definition does not, regardless of other
 *    declarations
 *
 *  - The C++ model, where an `inline` function that is used un-inlined emits a
 *    standalone function with selectany (COMDAT) linkage, requiring a C++
 *    linker to discard extra definitions
 *
 * Additional reading:
 *     https://www.greenend.org.uk/rjk/tech/inline.html
 */
#endif

#ifndef ghost_has_ghost_emit_inline
    #ifdef ghost_emit_inline
        #define ghost_has_ghost_emit_inline 1
    #endif
#endif

/* C++ rules
 * The linker will need COMDAT support to link C++ object files so we don't
 * need to worry about emitting additional definitions from C++ translation
 * units. Compilation speed will be slower because the function will be
 * compiled in all translation units. */
#ifndef ghost_has_ghost_emit_inline
    #ifdef __cplusplus
        #define ghost_emit_inline inline
        #define ghost_has_ghost_emit_inline 1
    #endif
#endif

/* MSVC >=2015 always uses COMDAT linkage even in C. Note that this doesn't
 * work on MSVC <2015 because it doesn't recognize inline or even __inline as a
 * keyword in C. */
#ifndef ghost_has_ghost_emit_inline
    #ifdef _MSC_VER
        #if _MSC_VER >= 1900
            #define ghost_emit_inline inline
            #define ghost_has_ghost_emit_inline 1
        #endif
    #endif
#endif

/* For C, we need inline. If we don't have it (or it doesn't behave properly,
 * e.g. on older versions of TinyCC), we won't have this either. */
#ifndef ghost_has_ghost_emit_inline
    #include "ghost/language/ghost_inline.h"
    #if !ghost_has(ghost_inline)
        #define ghost_has_ghost_emit_inline 0
    #endif
#endif

/* GNU rules
 * We use ghost_inline rather than inline to support code compiled as gnu89
 * which only supports __inline__. */
#ifndef ghost_has_ghost_emit_inline
    #if defined(__GNUC__) && (defined(__GNUC_GNU_INLINE__) || \
            (!defined(__GNUC_STDC_INLINE__) && !defined(__GNUC_GNU_INLINE__)))
        #define ghost_emit_inline ghost_inline
        #define ghost_has_ghost_emit_inline 1
    #endif
#endif

/* C99 rules */
#ifndef ghost_has_ghost_emit_inline
    #if defined(__STDC_VERSION__)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 199901L
            #define ghost_emit_inline extern inline
            #define ghost_has_ghost_emit_inline 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_emit_inline
    #define ghost_has_ghost_emit_inline 0
#endif

#endif
