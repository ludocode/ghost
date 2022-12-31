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

#ifndef GHOST_HEADER_FUNCTION_H_INCLUDED
#define GHOST_HEADER_FUNCTION_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_header_function [[selectany]]
 *
 * Declares an ordinary function that can appear in multiple translation units
 * (e.g. in a header file) using the best linkage mechanism available.
 *
 * This is useful for defining medium or large functions in header files and in
 * header-only libraries.
 *
 * Example:
 *
 *     ghost_header_function
 *     void foo(...) {
 *         ...
 *         ...
 *     }
 *
 * If the implementation supports a form of automatic "selectany" or "linkonce"
 * non-inline linkage (e.g. COMDAT linkage), this will use it. Otherwise, if
 * weak linkage is available, it will declare the function weak. Otherwise it
 * will declare the function static.
 *
 * A standalone definition may not be emitted if not needed (for example if the
 * function is not used.)
 *
 * Note that weak linkage inhibits inlining so this can cause lost optimization
 * opportunities if used on small functions. Consider using ghost_header_inline
 * (or simply static inline) on small functions instead.
 *
 * Note that the function may still be inlined if link-time optimization
 * determines that the function is only called once, or if inlining would
 * otherwise reduce code size or improve performance. If you want to avoid
 * this, consider using ghost_header_noinline instead.
 *
 * If you are supporting both C and C++ you will want to ensure the function is
 * in an `extern "C"` block. If not, an additional name-mangled definition may
 * be emitted in C++.
 *
 * If your compiler has an option like -fvisibility=hidden, it is recommended
 * that you use it, or that you otherwise declare such functions hidden. (You
 * could use GHOST_HIDDEN_PUSH and GHOST_HIDDEN_POP.) This will resolve weak
 * linkage during the static link phase of compilation so that weak definitions
 * are not visible to the dynamic linker.
 *
 * @see ghost_header_inline
 * @see ghost_header_always_inline
 * @see ghost_header_noinline
 * @see GHOST_HIDDEN_PUSH
 * @see GHOST_HIDDEN_POP
 */
#endif

#ifndef ghost_has_ghost_header_function
    #ifdef ghost_header_function
        #define ghost_has_ghost_header_function 1
    #endif
#endif

/*
 * Unfortunately there is no easy way to declare a "selectany" or "linkonce"
 * function in C. Currently [[selectany]] only works on variables.
 *
 * My hope is that compilers will implement [[selectany]] on functions in C to
 * emit them with COMDAT linkage to better support header-only libraries. In
 * the meantime we fallback to weak or static.
 */

/*
 * In C++ we'll just declare the function inline. In modern C++ it's supposed
 * to be a linkage specifier only. It shouldn't suggest to the compiler that we
 * prefer it to be inlined.
 *
 * MSVC and Clang at least respect this (as they allow a C++ function to be
 * both inline and noinline) but GCC may not. If we determine that it's too
 * aggressive at inlining these functions we can avoid using inline under GCC.
 */
#ifndef ghost_has_ghost_header_function
    #ifdef __cplusplus
        #define ghost_header_function inline
        #define ghost_has_ghost_header_function 1
    #endif
#endif

/*
 * MSVC >=2015 always uses COMDAT linkage even in C. We'll assume that it uses
 * the same rules as C++ where inline is just a linkage specifier, not a
 * request to inline.
 */
#ifndef ghost_has_ghost_header_inline
    #if defined(_MSC_VER)
        #if _MSC_VER >= 1900
            #define ghost_header_inline inline
            #define ghost_has_ghost_header_inline 1
        #endif
    #endif
#endif

/* Use weak if we have it. This will inhibit inlining. (See ghost_weak.h for
 * details on the interactions between weak and inline.) */
#ifndef ghost_has_ghost_header_function
    #include "ghost/language/ghost_weak.h"
    #if ghost_has(ghost_weak)
        #define ghost_header_function ghost_weak
        #define ghost_has_ghost_header_function 1
    #endif
#endif

/*
 * Use static noinline maybe_unused, again inhibiting inlining. We don't
 * actually want noinline but compilers will often inline static functions that
 * are only used once. This is a problem for us because this function may be
 * called once in each of several translation units. Unused functions will be
 * discarded and, with noinline, link-time identical code folding has a chance
 * of merging the remaining redundant definitions.
 */
#ifndef ghost_has_ghost_header_function
    #include "ghost/language/ghost_maybe_unused.h"
    #include "ghost/language/ghost_noinline.h"
    #define ghost_header_function ghost_noinline ghost_maybe_unused static
    #define ghost_has_ghost_header_function 1
#endif

#endif
