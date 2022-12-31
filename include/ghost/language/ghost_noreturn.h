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

#ifndef GHOST_NORETURN_H_INCLUDED
#define GHOST_NORETURN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_noreturn [[noreturn]]
 *
 * Annotates a function as never returning normally. It might infinite loop,
 * it might stop the program, it might exit the thread, it might longjmp out,
 * but it cannot return.
 *
 * If a noreturn function does return, the behaviour is undefined.
 *
 * A noreturn function must have a return type of void.
 *
 * This may not be supported on all compilers. Check ghost_has(ghost_noreturn)
 * to see if it's supported. If you want to fallback to nothing, use
 * ghost_noreturn_opt instead.
 *
 * @see ghost_noreturn
 */
#endif

/* C23 adds [[noreturn]] and deprecates _Noreturn. */
#ifndef ghost_has_ghost_noreturn
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if (GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23)
            #define ghost_noreturn [[__noreturn__]]
            #define ghost_has_ghost_noreturn 1
        #endif
    #endif
#endif

/*
 * C11 added _Noreturn.
 *
 * We don't use this under NVidia/PGI because with -Wpedantic they require that
 * _Noreturn come after a storage specifier (i.e. they want `static _Noreturn`
 * instead of `_Noreturn static`.) Ghost attributes (like C++ attributes)
 * must always come before storage specifiers. __attribute__((__noreturn__))
 * does work properly under NVidia so in C we fallback to that instead.
 */
#ifndef ghost_has_ghost_noreturn
    #if defined(__STDC_VERSION__) && !defined(__PGI)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 201112L
            #define ghost_noreturn _Noreturn
            #define ghost_has_ghost_noreturn 1
        #endif
    #endif
#endif

/* C++11 has [[noreturn]].
 *
 * We'd prefer to use [[__noreturn__]] but that isn't standard C++ yet. It
 * might make sense to avoid this if nodiscard is defined as a macro but it
 * could just as well be defined after this is included so there's no real way
 * to detect it. */
#ifndef ghost_has_ghost_noreturn
    #ifdef __cplusplus
        #include "ghost/impl/language/ghost_impl_standard_attribute.h"
        #if GHOST_IMPL_STANDARD_ATTRIBUTE
            #define ghost_noreturn [[noreturn]]
            #define ghost_has_ghost_noreturn 1
        #endif
    #endif
#endif

/* MSVC */
#ifndef ghost_has_ghost_noreturn
    #if defined(_MSC_VER)
        #define ghost_noreturn __declspec(noreturn)
        #define ghost_has_ghost_noreturn 1
    #endif
#endif

/* GCC and friends
 * PGI defines __GNUC__ but because of our workaround above we check __PGI
 * anyway in case __GNUC__ is undefined for whatever reason. */
#ifndef ghost_has_ghost_noreturn
    #if defined(__GNUC__) || defined(__PGI)
        #define ghost_noreturn __attribute__((__noreturn__))
        #define ghost_has_ghost_noreturn 1
    #endif
#endif

/* A noreturn attribute is necessary to make certain code make sense. For
 * example if a function has a non-void return type, calling a noreturn
 * function can be done instead of returning a value. A compiler that doesn't
 * support noreturn might warn or error on such code.
 *
 * For this reason if we don't have support for it, we don't implement it. Use
 * ghost_noreturn_opt if you want it to be optional. */
#ifndef ghost_has_ghost_noreturn
    #define ghost_noreturn /*nothing*/
    #define ghost_has_ghost_noreturn 1
#endif

#endif
