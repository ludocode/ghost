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

#ifndef GHOST_STRUCT_HACK_H_INCLUDED
#define GHOST_STRUCT_HACK_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_STRUCT_HACK
 *
 * This is used to declare a flexible array at the end of a struct. The macro
 * expands to either nothing, 0 or 1 depending on whether flexible array
 * members are supported and what compiler extensions are available to emulate
 * them.
 *
 * C99 supports flexible array members, where the last member of a struct is
 * allowed to be an array of indeterminate size. The size of the array can vary
 * at runtime based on the size allocated for the struct. For example:
 *
 *     typedef struct {
 *         int x;
 *         char s[];
 *     } my_struct_t;
 *
 * The above can store a character buffer inline in the struct. `sizeof(struct
 * my_struct)` returns the size without the flexible member and you then add
 * the desired size of the array when allocating it:
 *
 *     const char* some_string = "Hello world!"
 *     my_struct_t* my_struct = (my_struct_t*) malloc(sizeof(my_struct_t) + strlen(some_string) + 1);
 *     my_struct->x = 1;
 *     strcpy(my_struct->s, some_string);
 *
 * Unfortunately this is not available in C++, ANSI C, or older and less
 * feature complete compilers. Some compilers support an array size of 0 as an
 * extension to declare a flexible array member. Others do not support it at
 * all, but it can be emulated by declaring the array with a size of 1 and
 * measuring the size of the struct by the offset of the flexible member.
 *
 * Ghost wraps all of these variations. Pass GHOST_STRUCT_HACK as the size of
 * the flexible array member and use ghost_struct_hack_sizeof() to determine
 * the size of the struct with the given number of elements.
 *
 *     typedef struct {
 *         int x;
 *         char s[GHOST_STRUCT_HACK];
 *     } my_struct_t;
 *
 *     const char* some_string = "Hello world!"
 *     my_struct_t* my_struct = (my_struct_t*) malloc(
 *            ghost_struct_hack_sizeof(my_struct_t, s, strlen(some_string) + 1));
 *     my_struct->x = 1;
 *     strcpy(my_struct->s, some_string);
 *
 * Though not technically legal outside of C99 or later (hence "hack"), the
 * above generally works on all platforms with all C/C++ compilers in all
 * language standards including C++, ANSI C, etc.
 *
 * Static analysis may warn about the use of the struct hack since it may
 * recognize that more than one element is being written to the array. If you
 * want to work around this, you can optionally use the
 * ghost_struct_hack_access() macro to access it. Replace the strcpy() line
 * above with this:
 *
 *     strcpy(ghost_struct_hack_access(my_struct, s, char*), some_string);
 *
 * It takes some effort to use these macros correctly, but of course it takes
 * some effort to use the struct hack correctly even in C99. These macros,
 * while cumbersome, may still be less error-prone than doing it by hand.
 *
 * @see ghost_struct_hack_sizeof()
 * @see ghost_struct_hack_access()
 */
#endif

#ifndef ghost_has_GHOST_STRUCT_HACK
    #ifdef GHOST_STRUCT_HACK
        #define ghost_has_GHOST_STRUCT_HACK 1
    #endif
#endif

/* In C99 or later, compilers are required to support flexible array members. */
#ifndef ghost_has_GHOST_STRUCT_HACK
    #if defined(__STDC_VERSION__) && !defined(__cplusplus)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 199901L
            #define GHOST_STRUCT_HACK /*nothing*/
            #define ghost_has_GHOST_STRUCT_HACK 1
        #endif
    #endif
#endif

/* GCC and Clang support this as an extension in ANSI C and C++ but they warn
 * about its use under -Wpedantic even in -std=gnu++* modes. Since there is no
 * way to determine whether -Wpedantic is on and no nice way to silence the
 * warning, we don't use it.
 *
 * The downside of this is that static analysis may warn about out-of-bounds
 * array accesses since it may not recognize this as a flexible array member.
 * If you want to force this to use an extension, predefine GHOST_STRUCT_HACK
 * to 0 and, if using pedantic warnings, silence the relevant warning yourself. */

/* Fallback to a size of 1. */
#ifndef ghost_has_GHOST_STRUCT_HACK
    #define GHOST_STRUCT_HACK 1
    #define ghost_has_GHOST_STRUCT_HACK 1
#endif

#endif
