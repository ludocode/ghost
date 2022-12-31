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

#ifndef GHOST_WEAK_H_INCLUDED
#define GHOST_WEAK_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_weak
 *
 * Declares a symbol as having weak linkage.
 *
 * Any number of symbols with the same name may have weak linkage but at most
 * one can have strong (non-weak) linkage. At link time (static or dynamic),
 * for each symbol name:
 *
 * - If a matching symbol with strong linkage exists, it is used, and any
 *   matching weak symbols are discarded;
 * - Otherwise if at least one matching weak symbol exists, one is chosen
 *   arbitrarily and the others are discarded;
 * - Otherwise the address of the symbol is null. You can still take its
 *   address but dereferencing it will cause the same behaviour as
 *   dereferencing a null pointer (e.g. segmentation fault.)
 *
 * If the symbol is also hidden, weak linkage is resolved at static link time.
 * If the symbol is not hidden and a strong symbol does not exist at static
 * link time, one weak symbol is chosen arbitrarily (or none if none exist) and
 * the symbol retains its weak status for the purpose of dynamic linking where
 * the same algorithm applies again.
 *
 * In general a function declared weak cannot also be declared inline.
 * Compilers tend to treat "weak" as an indication that the symbol must be
 * replaceable so they will avoid inlining a weak function. In other words weak
 * effectively implies noinline.
 *
 * This requires a compiler and linker that support weak symbols. Check
 * `#if ghost_has(ghost_weak)` to see if it's supported.
 */
#endif

/*
 * The interaction between "weak" and "inline" is not simple and is heavily
 * compiler-dependent. Here are my notes for future reference:
 *
 * GCC 11.2.0:
 *
 * - `__attribute__((weak)) inline` causes warning: inline function ‘foo’
 *   declared weak [-Wattributes]
 * - A function declared `__attribute__((weak)) inline` is never inlined
 * - `__attribute__((weak, always_inline))` does actually inline the function
 *   where possible but causes warning: always_inline function might not be
 *   inlineable
 * - `__attribute__((weak, always_inline)) inline` does actually inline the
 *   function where possible, but gives the weak+inline warning above
 * - `#pragma weak` has different behaviour from `__attribute__((weak))`: a
 *   pragma weak function declared inline and not always_inline will actually
 *   sometimes be inlined and the resulting standalone function will be weak.
 *   This is desirable for selectany (e.g. ghost_header_inline) but the syntax
 *   is cumbersome. It's also likely to break in any future version of GCC.
 *
 * Clang 13.0.1:
 *
 * - A function declared `__attribute__((weak)) inline` is never inlined
 * - `__attribute__((weak))` and `#pragma weak` have identical behaviour
 * - `__attribute__((weak, always_inline)) inline` does actually inline the
 *   function where possible and the non-inline symbol is weak.
 */

#ifndef ghost_has_ghost_weak
    #ifdef ghost_weak
        #define ghost_has_ghost_weak 1
    #endif
#endif

/* TODO disabled on PCC for now, doesn't seem to work */
#ifndef ghost_has_ghost_weak
    #ifdef __PCC__
        #define ghost_has_ghost_weak 0
    #endif
#endif

/* g++ supports -fno-weak which disables weak symbol support. */
#ifndef ghost_has_ghost_weak
    #ifdef __GXX_WEAK__
        #if !__GXX_WEAK__
            #define ghost_has_ghost_weak 0
        #endif
    #endif
#endif

/*
 * Most GNUC compilers support __attribute__((weak)). We assume any compiler
 * that defines __GNUC__ does unless we know otherwise.
 *
 * Note that there are some platforms supported by GCC that don't support weak
 * symbols. We should turn this off for those platforms here as well. This
 * isn't implemented yet.
 */
#ifndef ghost_has_ghost_weak
    /* cparser doesn't support __attribute__((weak)). */
    #if defined(__GNUC__) && !defined(__CPARSER__)
        #define ghost_weak __attribute__((__weak__))
        #define ghost_has_ghost_weak 1
    #endif
#endif

#ifndef ghost_has_ghost_weak
    #define ghost_has_ghost_weak 0
#endif

#endif
