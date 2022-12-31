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

#ifndef GHOST_NOT_H_INCLUDED
#define GHOST_NOT_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_NOT(condition)
 *
 * Expands to 1 if the condition is 0, otherwise expands to 0.
 *
 * This macro coerces the given preprocessor expression into a preprocessor
 * boolean, that is 1 or 0, and returns its inverse. Only an explicit 0 is
 * is considered false and inverted to 1. Any other non-string text including
 * blank is considered true and inverted to 0.
 *
 * Note that this cannot take a string.
 *
 * This requires variadic macros. Check `#if ghost_has(GHOST_NOT)` to see
 * whether it's supported.
 */

#ifndef ghost_has_GHOST_NOT
    #ifdef GHOST_NOT
        #define ghost_has_GHOST_NOT 1
    #endif
#endif

/* This requires variadic macros. */
#ifndef ghost_has_GHOST_NOT
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if !GHOST_PP_VA_ARGS
        #define ghost_has_GHOST_NOT 0
    #endif
#endif

/* cparser's preprocessor doesn't handle this correctly. None of the stuff that
 * depends on this (like GHOST_IF_ELSE) works. We just disable this right at
 * the source to disable anything that depends on it. */
#ifndef ghost_has_GHOST_NOT
    #include "ghost/preprocessor/ghost_cparser_pp.h"
    #if GHOST_CPARSER_PP
        #define ghost_has_GHOST_NOT 0
    #endif
#endif

/*
 * GHOST_IMPL_IS_PROBE() is a macro that expands to 1 if its argument is the
 * special value GHOST_IMPL_PROBE() or 0 otherwise. In other words, it checks
 * whether its argument is the probe.
 *
 * GHOST_NOT(arg) is therefore implemented by checking whether
 * GHOST_IMPL_NOT_##arg is the probe, and GHOST_IMPL_NOT_0 is the probe.
 *
 * The "magic" is that GHOST_NOT() only takes one argument, but the probe
 * expands to two arguments to IS_PROBE(), shifting over the second argument
 * from 0 to 1.
 *
 * A better description of how the "probe" works can be read in these articles:
 *
 *     https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
 *     http://jhnet.co.uk/articles/cpp_magic
 */
#ifndef ghost_has_GHOST_NOT
    #include "ghost/preprocessor/ghost_concat.h"
    #include "ghost/preprocessor/ghost_msvc_traditional.h"

    #define GHOST_NOT_IMPL_PROBE() ~, 1

    #if GHOST_MSVC_TRADITIONAL
        #define GHOST_NOT_IMPL_IS_PROBE(...) GHOST_EXPAND(GHOST_NOT_IMPL_IS_PROBE_IMPL(__VA_ARGS__, 0, 0))
    #else
        #define GHOST_NOT_IMPL_IS_PROBE(...) GHOST_NOT_IMPL_IS_PROBE_IMPL(__VA_ARGS__, 0, )
    #endif
    #define GHOST_NOT_IMPL_IS_PROBE_IMPL(a, b, ...) b

    #define GHOST_NOT_IMPL_NOT_0 GHOST_NOT_IMPL_PROBE()
    #define GHOST_NOT(x) GHOST_NOT_IMPL_IS_PROBE(GHOST_CONCAT(GHOST_NOT_IMPL_NOT_, x))

    #define ghost_has_GHOST_NOT 1
#endif

#endif
