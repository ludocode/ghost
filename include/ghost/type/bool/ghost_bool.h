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

#ifndef GHOST_BOOL_H_INCLUDED
#define GHOST_BOOL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A boolean type.
 *
 * If a bool exists as part of the language or it can be provided as a compiler
 * extension, ghost_bool will be an alias of it. Otherwise it will be `unsigned
 * char`.
 *
 * We fallback to `unsigned char` so that `sizeof(ghost_bool)==1`. On virtually
 * all modern platforms, `sizeof(bool)==1` so we match that behaviour.
 */
typedef _Bool ghost_bool;
#endif

/* We include <stdbool.h> if possible to provide the real bool, true and false
 * so that you don't have to use ghost's prefixed names. We include it even in
 * C++ so that __bool_true_false_are_defined is defined, that way the user can
 * check it if they need bool. */
#include "ghost/header/c/ghost_stdbool_h.h"

/* In C++ bool is a keyword. */
#if defined(__cplusplus)
    #ifndef ghost_has_ghost_bool
        typedef bool ghost_bool;
        #define ghost_has_ghost_bool 1
    #endif
#endif

/* We don't use bool in C23 because it is a predefined macro. It could
 * technically be defined by old user code to something else (e.g. int or
 * char; either way we don't want to use it.) */

/* In C99 we have _Bool. */
#ifndef ghost_has_ghost_bool
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 199901L
            typedef _Bool ghost_bool;
            #define ghost_has_ghost_bool 1
        #endif
    #endif
#endif

/*
 * In GNU C compilers _Bool is supported as an extension even in ANSI C.
 *
 * When compiling as ANSI C, use of _Bool throws a pedantic warning in both GCC
 * and Clang. We can use __extension__ to silence it for our typedef which can
 * then be used without warning.
 *
 * We're going to assume that any compiler that defines __GNUC__ also supports
 * both __extension__ and _Bool unless we know otherwise.
 */
#ifndef ghost_has_ghost_bool
    /* cparser doesn't support this. */
    #if defined(__GNUC__) && !defined(__CPARSER__)
        __extension__ typedef _Bool ghost_bool;
        #define ghost_has_ghost_bool 1
    #endif
#endif

/* MSVC also lets us use _Bool in VS2013 and higher. */
#ifndef ghost_has_ghost_bool
    #ifdef _MSC_VER
        #if _MSC_VER >= 1800
            typedef _Bool ghost_bool;
            #define ghost_has_ghost_bool 1
        #endif
    #endif
#endif

/*
 * Otherwise we make it unsigned char so that sizeof(ghost_bool) is 1. This
 * matches the size of C++/C99 bool on almost all architectures. This makes
 * structs containing ghost_bool binary compatible between all language
 * standards.
 *
 * (The GCC docs say that on Darwin/PowerPC sizeof(bool)==4. There are probably
 * others with similar behaviour. We'll assume for now that such platforms are
 * no longer used and that sizeof(bool)==1 on all platforms supported by
 * Ghost. We do want to eventually support everything with Ghost though so this
 * will eventually need to be fixed.)
 *
 * There is an issue here which is that old versions of GCC may throw warnings
 * after performing integer promotions on ternary branches. For example:
 *
 * ghost_bool x = some_condition ? ghost_true : ghost_false;
 *
 * The above gives a -Wconversion warning because the result of the ternary is
 * promoted to unsigned int. (Newer GCC doesn't have this problem because it
 * keeps track of the original type through promotions.)
 *
 * There isn't really a clean way to silence this warning other than just
 * casting the whole expression to ghost_bool. Unfortunately, the alternative
 * of making ghost_bool an int would make it the wrong size, so it would be
 * incompatible with code compiled as a newer C standard or as C++.
 */
#ifndef ghost_has_ghost_bool
    typedef unsigned char ghost_bool;
    #define ghost_has_ghost_bool 1
#endif

#endif
