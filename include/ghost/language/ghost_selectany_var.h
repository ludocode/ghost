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

#ifndef GHOST_SELECTANY_VAR_H_INCLUDED
#define GHOST_SELECTANY_VAR_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_selectany_var [[selectany]]
 *
 * Declares a global variable with "selectany" or "linkonce" semantics: the
 * linker will select one definition arbitrarily at static link time.
 *
 * This allows you to emit a definition of the variable in multiple translation
 * units. It's useful for declaring global variables in headers (for example in
 * a header-only library.)
 *
 * Example:
 *
 *     ghost_selectany_var int x = 5;
 *
 * Example of a singleton in a header file:
 *
 *     typedef struct {
 *         ...
 *     } foo_t;
 *     ghost_selectany_var foo_t foo_singleton;
 *
 * ghost_selectany_var cannot be implemented in standard C but it works on all
 * popular compilers and operating systems. It uses a selectany extension if
 * available and otherwise falls back to weak. Check
 * ghost_has(ghost_selectany_var) to see if it's supported.
 *
 *     https://docs.microsoft.com/en-us/cpp/cpp/selectany
 *     https://clang.llvm.org/docs/AttributeReference.html#selectany
 */
#endif

#ifndef ghost_has_ghost_selectany_var
    #ifdef ghost_selectany_var
        #define ghost_has_ghost_selectany_var 1
    #endif
#endif

/* In C++17 we can declare variables inline. */
#ifndef ghost_has_ghost_selectany_var
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201703L
            #define ghost_selectany_var inline
            #define ghost_has_ghost_selectany_var 1
        #endif
    #endif
#endif

/* MSVC has __declspec(selectany) */
#ifndef ghost_has_ghost_selectany_var
    #ifdef _MSC_VER
        #define ghost_selectany_var __declspec(selectany)
        #define ghost_has_ghost_selectany_var 1
    #endif
#endif

/*
 * Clang has __attribute__((selectany)) since 5.0.1 (not 5.0.0.) This works
 * only on variables (for now...) but it seems to work on most platforms. We
 * can detect it with __has_attribute(selectany).
 */
#ifndef ghost_has_ghost_selectany_var
    #ifdef __clang__
        #ifdef __has_attribute
            #if __has_attribute(__selectany__)
                /*
                 * __has_attribute(selectany) lies! On Clang versions before
                 * 3.6 it evaluates to 1 even though the attribute is not
                 * supported. We can't do normal version checks because the
                 * various forks of Clang all have different versioning
                 * mechanisms. Instead we do a version check on Linux only
                 * (under the assumption that this is not a fork of Clang) and
                 * otherwise assume the version of Clang is recent enough.
                 */
                #if !defined(__linux__) || __clang_major__ > 3 || \
                        (__clang_major__ == 3 && __clang_minor__ >= 6)
                    #define ghost_selectany_var __attribute__((__selectany__))
                    #define ghost_has_ghost_selectany_var 1
                #endif
            #endif
        #endif
    #endif
#endif

/* GCC also has __attribute__((selectany)) but it only works on Windows. */
#ifndef ghost_has_ghost_selectany_var
    #ifdef _WIN32
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #define ghost_selectany_var __attribute__((__selectany__))
            #define ghost_has_ghost_selectany_var 1
        #endif
    #endif
#endif

/* Fallback to [[weak]] or __attribute__((weak)) if we have it */
#ifndef ghost_has_ghost_selectany_var
    #include "ghost/language/ghost_weak.h"
    #if ghost_has(ghost_weak)
        #define ghost_selectany_var ghost_weak
        #define ghost_has_ghost_selectany_var 1
    #endif
#endif

/* Otherwise we have no support. */
#ifndef ghost_has_ghost_selectany_var
    #define ghost_has_ghost_selectany_var 0
#endif

#endif
