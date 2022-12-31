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

#ifndef GHOST_IMPL_FUNCTION_WRAPPER_H_INCLUDED
#define GHOST_IMPL_FUNCTION_WRAPPER_H_INCLUDED

#include "ghost/ghost_core.h"

/*
 * This file is used to define the attributes, wrappers and configuration
 * options Ghost uses to define its own functions.
 *
 * A function defined by Ghost typically looks like this:
 *
 *     #include "ghost/impl/ghost_impl_inline.h"
 *     GHOST_IMPL_FUNCTION_OPEN
 *     ghost_impl_inline
 *     int some_function(int x) {
 *         // ...
 *     }
 *     GHOST_IMPL_FUNCTION_CLOSE
 *
 * The GHOST_IMPL_FUNCTION_OPEN/CLOSE pair wraps the function in `extern "C"`
 * and disables certain warnings.
 *
 * The ghost_impl_inline and other attributes declare the function with several
 * of: inline, always_inline, noinline, weak, static or extern depending on
 * inline emission mode, and hidden (since Ghost functions should never be
 * exposed from shared libraries.)
 *
 * Ghost functions that use the `noinline` or `function` attributes sometimes
 * look like this instead:
 *
 *     #include "ghost/impl/ghost_impl_function.h"
 *     GHOST_IMPL_FUNCTION_OPEN
 *     ghost_impl_function
 *     int some_function(int x) GHOST_IMPL_DEF({
 *         // ...
 *     })
 *     GHOST_IMPL_FUNCTION_CLOSE
 *
 * The GHOST_IMPL_DEF() macro evaluates to its arguments if GHOST_EMIT_DEFS is
 * 1 and replaces them with a semicolon otherwise. In other words it's used to
 * hide the definition and leave only a prototype when not emitting
 * definitions.
 *
 * If the function includes preprocessor directives, it might look like this
 * instead:
 *
 *     #include "ghost/impl/ghost_impl_noinline.h"
 *     GHOST_IMPL_FUNCTION_OPEN
 *     ghost_impl_noinline
 *     int some_function(int x)
 *     #if GHOST_EMIT_DEFS
 *     ;
 *     #else
 *     {
 *         // ...
 *     }
 *     #endif
 *     GHOST_IMPL_FUNCTION_CLOSE
 *
 * For larger functions, Ghost may declare only a prototype and put the
 * implementation in a separate file that gets included only under
 * GHOST_EMIT_DEFS. See ghost/qsort/impl/ghost_impl_qsort_internal.h for an
 * example of this.
 */



/*
 * This gives us GHOST_MANUAL_DEFS, GHOST_EMIT_DEFS and GHOST_IMPL_DEF(). They
 * are used for both variables and functions so they are separate.
 */
#include "ghost/impl/ghost_impl_defs.h"



/*
 * Define our function wrappers:
 *
 * - GHOST_IMPL_FUNCTION_OPEN
 * - GHOST_IMPL_FUNCTION_CLOSE
 *
 * These do `extern "C" {}` and silence some warnings.
 */

#include "ghost/language/ghost_extern_c_push_pop.h"
#include "ghost/language/ghost_hidden_push_pop.h"

/* We silence these warnings in all Ghost declarations. */
#include "ghost/silence/ghost_silence_unused_function.h"
#include "ghost/silence/ghost_silence_long_long.h"

/*
 * GCC versions before 5.1 warn about defining a non-static inline function
 * before declaring it.
 *
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=54113
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63877
 *
 * Apparently the latest Clang does under -Weverything as well and so does
 * cparser.
 *
 * In any case we define non-static non-inline functions without declarations
 * throughout Ghost so we silence this regardless.
 */
#if defined(__GNUC__)
    #include "ghost/silence/ghost_silence_missing_declarations.h"
    #define GHOST_IMPL_FUNCTION_SILENCE_MISSING_DECLARATIONS \
        GHOST_SILENCE_MISSING_DECLARATIONS
#endif

/*
 * If we have to silence any warnings, use push/pop to wrap them if we can. (If
 * we can't, we're assuming you're on a really old compiler, so we're okay with
 * these silencing pragmas leaking out into code that uses Ghost. All modern
 * compilers that support silencing warnings support some form of push/pop.)
 *
 * TODO no, if we don't have silence push/pop, silence nothing
 */
#if defined(GHOST_IMPL_FUNCTION_SILENCE_MISSING_DECLARATIONS)
    #include "ghost/silence/ghost_silence_push_pop.h"
    #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
        #define GHOST_IMPL_FUNCTION_SILENCE_PUSH GHOST_SILENCE_PUSH
        #define GHOST_IMPL_FUNCTION_SILENCE_POP GHOST_SILENCE_POP
    #endif
#endif

/* Clear anything we haven't defined. */
#ifndef GHOST_IMPL_FUNCTION_SILENCE_PUSH
    #define GHOST_IMPL_FUNCTION_SILENCE_PUSH /*nothing*/
#endif
#ifndef GHOST_IMPL_FUNCTION_SILENCE_POP
    #define GHOST_IMPL_FUNCTION_SILENCE_POP /*nothing*/
#endif
#ifndef GHOST_IMPL_FUNCTION_SILENCE_MISSING_DECLARATIONS
    #define GHOST_IMPL_FUNCTION_SILENCE_MISSING_DECLARATIONS /*nothing*/
#endif

/* Function block open */
#define GHOST_IMPL_FUNCTION_OPEN \
    GHOST_EXTERN_C_PUSH \
    GHOST_HIDDEN_PUSH \
    GHOST_IMPL_FUNCTION_SILENCE_PUSH \
    GHOST_IMPL_FUNCTION_SILENCE_MISSING_DECLARATIONS \
    GHOST_SILENCE_LONG_LONG \
    GHOST_SILENCE_UNUSED_FUNCTION

/* Function block close */
#define GHOST_IMPL_FUNCTION_CLOSE \
    GHOST_IMPL_FUNCTION_SILENCE_POP \
    GHOST_HIDDEN_POP \
    GHOST_EXTERN_C_POP

/* C++ open (used for overloads, templates, etc.) */
#define GHOST_IMPL_CXX_FUNCTION_OPEN \
    GHOST_HIDDEN_PUSH \
    GHOST_IMPL_FUNCTION_SILENCE_PUSH \
    GHOST_IMPL_FUNCTION_SILENCE_MISSING_DECLARATIONS

/* C++ close */
#define GHOST_IMPL_CXX_FUNCTION_CLOSE \
    GHOST_IMPL_FUNCTION_SILENCE_POP \
    GHOST_HIDDEN_POP

/* TODO consider making this a proper supported config option
 * Defines all Ghost functions static. */
#ifndef GHOST_STATIC_DEFS
    #define GHOST_STATIC_DEFS 0
#endif
#if GHOST_STATIC_DEFS && GHOST_MANUAL_DEFS
    #error
#endif

#ifdef _MSC_VER
__pragma(warning(disable:4505)) /* TODO remove this, make mirror do it, make a GHOST_SILENCE for it */
#endif

#endif
