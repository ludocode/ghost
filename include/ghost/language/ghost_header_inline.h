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

#ifndef GHOST_HEADER_INLINE_H_INCLUDED
#define GHOST_HEADER_INLINE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_header_inline [[selectany]] inline
 *
 * Declares an inline function that can appear in multiple translation units
 * (e.g. in a header file) using the best linkage mechanism available.
 *
 * This is useful for defining small functions in header files and in
 * header-only libraries.
 *
 * Example:
 *
 *     ghost_header_inline
 *     void foo(...) {
 *         ...
 *     }
 *
 * If the implementation supports a form of automatic "selectany" or "linkonce"
 * inline linkage (e.g. COMDAT linkage), this will use it. Otherwise it will
 * declare the function static inline.
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
 * If you are supporting both C and C++ you will want to ensure the function is
 * in an `extern "C"` block. If not, an additional name-mangled definition may
 * be emitted in C++.
 *
 * @see ghost_header_always_inline
 * @see ghost_header_function
 * @see ghost_header_noinline
 */
#endif

#ifndef ghost_has_ghost_header_inline
    #ifdef ghost_header_inline
        #define ghost_has_ghost_header_inline 1
    #endif
#endif

/*
 * C++ rules
 *
 * The linker will need COMDAT support to link C++ object files so we don't
 * need to worry about emitting additional definitions from C++ translation
 * units. If a C definition exists, the linker will use it; otherwise it will
 * use one of the C++ definitions.
 */
#ifndef ghost_has_ghost_header_inline
    #if defined(__cplusplus)
        #define ghost_header_inline inline
        #define ghost_has_ghost_header_inline 1
    #endif
#endif

/*
 * MSVC >=2015 always uses COMDAT linkage even in C. Note that this doesn't
 * work on MSVC <2015 because it doesn't recognize inline or even __inline as a
 * keyword in C.
 */
#ifndef ghost_has_ghost_header_inline
    #if defined(_MSC_VER)
        #if _MSC_VER >= 1900
            #define ghost_header_inline inline
            #define ghost_has_ghost_header_inline 1
        #endif
    #endif
#endif

/*
 * Unfortunately there is no easy way to declare a "selectany" or "linkonce"
 * function in C. My hope is that compilers will implement [[selectany]] on
 * functions in C to emit them with COMDAT linkage. In the meantime we fallback
 * to static.
 */

/* Use static inline if we have inline. */
#ifndef ghost_has_ghost_header_inline
    #include "ghost/language/ghost_inline.h"
    #if ghost_has(ghost_inline)
        #ifdef __PGI
            /* NVidia/PGI complains about unused static inline functions. */
            #include "ghost/language/ghost_maybe_unused.h"
            #define ghost_header_inline ghost_maybe_unused static ghost_inline
        #else
            #define ghost_header_inline static ghost_inline
        #endif
        #define ghost_has_ghost_header_inline 1
    #endif
#endif

/* Otherwise use maybe_unused static. */
#ifndef ghost_has_ghost_header_inline
    #include "ghost/language/ghost_maybe_unused.h"
    #define ghost_header_inline ghost_maybe_unused static
    #define ghost_has_ghost_header_inline 1
#endif

#endif
