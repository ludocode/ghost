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

#ifndef GHOST_HEADER_NOINLINE_H_INCLUDED
#define GHOST_HEADER_NOINLINE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_header_noinline [[selectany]] [[noinline]]
 *
 * Declares a noinline function that can appear in multiple translation units
 * (e.g. in a header file) using the best linkage mechanism available.
 *
 * This is useful for defining large or cold functions in header files and in
 * header-only libraries.
 *
 * Example:
 *
 *     ghost_header_noinline
 *     void foo(...) {
 *         ...
 *         ...
 *         ...
 *     }
 *
 * If the implementation supports a form of automatic "selectany" or "linkonce"
 * non-inline linkage (e.g. COMDAT linkage), this will use it. Otherwise, if
 * weak linkage is available, it will declare the function weak. Otherwise it
 * will declare the function static. The function will additionally be declared
 * noinline.
 *
 * A standalone definition may not be emitted if not needed (for example if the
 * function is not used.)
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
 * @see ghost_header_always_inline
 * @see ghost_header_inline
 * @see ghost_header_function
 * @see GHOST_HIDDEN_PUSH
 * @see GHOST_HIDDEN_POP
 */
#endif

#ifndef ghost_has_ghost_header_noinline
    #ifdef ghost_header_noinline
        #define ghost_has_ghost_header_noinline 1
    #endif
#endif

/*
 * C++ or MSVC rules
 *
 * MSVC and Clang allow both inline and noinline in C++. (GCC does not.) The
 * linker will need COMDAT support to link C++ object files so we don't need to
 * worry about emitting additional definitions from C++ translation units.
 *
 *     https://devblogs.microsoft.com/oldnewthing/20200521-00/?p=103777
 *
 * MSVC >=2015 always uses COMDAT linkage even in C. Note that this doesn't
 * work on MSVC <2015 because it doesn't recognize inline or even __inline as a
 * keyword in C.)
 */
#ifndef ghost_has_ghost_header_noinline
    #if (defined(__cplusplus) || defined(_MSC_VER)) && (defined(__clang__) || !defined(__GNUC__))
        #if defined(__cplusplus) || _MSC_VER >= 1900
            #include "ghost/language/ghost_noinline.h"
            #define ghost_header_noinline ghost_noinline inline
            #define ghost_has_ghost_header_noinline 1
        #endif
    #endif
#endif

/* Use weak noinline if we can. Weak tends to imply noinline but we declare
 * noinline anyway because if the symbol is hidden a link-time optimizer could
 * in theory resolve the weak symbol before choosing whether to inline it. */
#ifndef ghost_has_ghost_header_noinline
    #include "ghost/language/ghost_weak.h"
    #include "ghost/language/ghost_noinline.h"
    #if ghost_has(ghost_weak)
        #define ghost_header_noinline ghost_weak ghost_noinline
        #define ghost_has_ghost_header_noinline 1
    #endif
#endif

/* Use static noinline maybe_unused. Unused static functions will be discarded.
 * Link-time identical code folding may merge the remaining redundant
 * definitions. */
#ifndef ghost_has_ghost_header_noinline
    #include "ghost/language/ghost_noinline.h"
    #include "ghost/language/ghost_maybe_unused.h"
    #define ghost_header_noinline ghost_noinline ghost_maybe_unused static
    #define ghost_has_ghost_header_noinline 1
#endif

#endif
