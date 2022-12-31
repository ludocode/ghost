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

#ifndef GHOST_IMPL_FORMAT_C99_SPECIFIERS_H_INCLUDED
#define GHOST_IMPL_FORMAT_C99_SPECIFIERS_H_INCLUDED

/*
 * @def GHOST_IMPL_FORMAT_C99_SPECIFIERS
 *
 * 1 if the C99 and C++11 format specifiers are supported, 0 otherwise.
 *
 * This includes the length modifiers "z", "hh", "ll", etc.; the conversion
 * specifier "a"; and probably some other things. See:
 *
 *     https://en.cppreference.com/w/c/io/fprintf
 *
 * These are supposed to be supported since C99 and C++11. However, they're
 * typically provided by the libc, not the compiler, so we should be able to
 * detect libc version for this. Unfortunately, compilers such as GCC warn
 * against using these in older language standards (e.g. -std=c89) even if the
 * libc supports it. We scope it to some runtimes (e.g. Windows) but otherwise
 * we mainly check the compiler and language standard.
 *
 * We may need to turn these off if we can also detect that the libc is too
 * old. Currently we don't bother.
 */

#ifdef GHOST_IMPL_FORMAT_C99_SPECIFIERS
    #error
#endif

/* MSVC supports "z" and friends as of VS2015 regardless of language standard. */
#ifndef GHOST_IMPL_FORMAT_C99_SPECIFIERS
    #ifdef _MSC_VER
        #if _MSC_VER >= 1900 /* VS 2015 */
            #define GHOST_IMPL_FORMAT_C99_SPECIFIERS 1
        #endif
    #endif
#endif

/* New format specifiers are not supported by GCC in C++11 mode until GCC 4.8
 * even though GCC 4.7 advertises full C++11 support. */
#ifndef GHOST_IMPL_FORMAT_C99_SPECIFIERS
    #if defined(__GNUC__) && defined(__cplusplus)
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 8)
                #define GHOST_IMPL_FORMAT_C99_SPECIFIERS 0
            #endif
        #endif
    #endif
#endif

/* C++11 has the new format specifiers. */
#ifndef GHOST_IMPL_FORMAT_C99_SPECIFIERS
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #define GHOST_IMPL_FORMAT_C99_SPECIFIERS 1
        #endif
    #endif
#endif

/* C99 has the new format specifiers. */
#ifndef GHOST_IMPL_FORMAT_C99_SPECIFIERS
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 202000L && !GHOST_IMPL_ENABLE_C23
            #define GHOST_IMPL_FORMAT_C99_SPECIFIERS 1
        #endif
    #endif
#endif

/* Clang seems to allow these in any language standard without warning but we
 * also need to know that the libc supports it. We scope this to only certain
 * platforms where we are sure 'z' and friends will be available. */
#ifndef GHOST_IMPL_FORMAT_C99_SPECIFIERS
    #ifdef __clang__
        #if defined(__linux__) || defined(__EMSCRIPTEN__)
            #define GHOST_IMPL_FORMAT_C99_SPECIFIERS 1
        #endif
    #endif
#endif

/* Otherwise we don't have it. */
#ifndef GHOST_IMPL_FORMAT_C99_SPECIFIERS
    #define GHOST_IMPL_FORMAT_C99_SPECIFIERS 0
#endif

#endif
