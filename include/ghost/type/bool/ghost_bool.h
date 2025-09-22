/*
 * MIT No Attribution
 *
 * Copyright (c) 2022-2025 Fraser Heavy Software
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
 */
typedef _Bool ghost_bool;
#endif



/* In C++ bool is a keyword. */
#if defined(__cplusplus)
    #ifndef ghost_has_ghost_bool
        typedef bool ghost_bool;
        #define ghost_has_ghost_bool 1
    #endif
#endif

/* We don't use bool in C23 because it is a predefined macro. It could
 * technically be re-defined by old user code to something else (e.g. int or
 * char; either way we don't want to use it.) _Bool is still supported in C23
 * so we use that. */

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
    /* cparser defines __GNUC__ but doesn't support this. */
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
 *
 * The biggest issue with using `unsigned char` is that implicit conversions
 * from larger integer types will truncate instead of converting to bool. For
 * example:
 *
 *     int x = 0x100;
 *     ghost_bool b = x;
 *
 * If `ghost_bool` is `unsigned char`, `b` will be 0 instead of 1. This can be
 * dangerous. You should enable truncation warnings (e.g. -Wconversion) to
 * prevent such bugs. To support compilers that don't have a bool type, correct
 * code would be a double negation:
 *
 *     int x = 0x100;
 *     ghost_bool b = !!x;
 *
 * If you'd like to use `int` instead, you can always pre-define it to
 * something else, e.g. `-Dghost_bool=int` or `#define ghost_bool int`. This
 * could make the ABI incompatible with C99 code that uses bools though, and it
 * doesn't entirely solve this problem because `int` will also truncate from
 * `long` or `long long` if those types are larger.
 *
 * This can't really be prevented in ANSI C code. It's recommended to compile
 * as at least C99, use a compiler with a bool extension in C89, or at least
 * enable truncation warnings.
 *
 *
 * Another issue is that old versions of GCC may throw warnings after
 * performing integer promotions on ternary branches. For example:
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
