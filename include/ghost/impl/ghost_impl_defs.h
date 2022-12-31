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

#ifndef GHOST_IMPL_DEFS_H_INCLUDED
#define GHOST_IMPL_DEFS_H_INCLUDED

#include "ghost/ghost_core.h"

/*
 * @file
 *
 * This file defines configuration options and helpers to control how Ghost
 * emits definitions of functions and variables.
 *
 * In C, functions and variables must be defined in exactly one translation
 * unit. Since Ghost is a header-only library, compiler extensions are used
 * where possible to provide single definitions of variables and large
 * functions. If you prefer, you can manually emit Ghost's definitions in a
 * single translation unit using these macros.
 */

/**
 * @def GHOST_MANUAL_DEFS
 *
 * Enables manual emission of function definitions.
 *
 * To manually emit definitions, pre-define GHOST_MANUAL_DEFS to 1 in all
 * translation units and pre-define GHOST_EMIT_DEFS to 1 in exactly one
 * translation unit that includes all of the Ghost headers used in your
 * project.
 *
 * This reduces compile times on all platforms and reduces code bloat on
 * platforms that don't support COMDAT or weak symbols. This guarantees that
 * only a single definition of each non-inline function will exist in the final
 * link on all platforms.
 *
 * On platforms that support selectany/weak, all non-trivial Ghost functions
 * will be declared as such, so single definitions of non-inline functions will
 * happen automatically. On other platforms, Ghost by default will fallback to
 * declaring all functions `static` or `static inline` which causes code bloat.
 * Manual emission can prevent this.
 *
 * Even on platforms that support selectany/weak, manually emitting definitions
 * can improve compilation speed because the compiler won't need to compile all
 * included Ghost functions in every translation unit.
 *
 * @warning When enabling GHOST_MANUAL_DEFS, the translation unit that enables
 *          GHOST_EMIT_DEFS must include *all* Ghost headers that are included
 *          in any other translation unit, otherwise you will get errors about
 *          missing symbols.
 *
 * @see GHOST_EMIT_DEFS
 */
#ifndef GHOST_MANUAL_DEFS
    #define GHOST_MANUAL_DEFS 0
#endif

/**
 * @def GHOST_EMIT_DEFS
 *
 * Emits manual definitions of functions in this translation unit.
 *
 * If you have enabled GHOST_MANUAL_DEFS, you must pre-define GHOST_EMIT_DEFS
 * to 1 in exactly one translation unit.
 *
 * If you have not enabled GHOST_MANUAL_DEFS, you cannot pre-define this. It
 * will be 1 automatically and function definitions will be emitted in all
 * translation units.
 *
 * @see GHOST_MANUAL_DEFS
 */
#if GHOST_MANUAL_DEFS
    #ifndef GHOST_EMIT_DEFS
        #define GHOST_EMIT_DEFS 0
    #endif
#else
    #ifdef GHOST_EMIT_DEFS
        #error "You cannot pre-define GHOST_EMIT_DEFS unless GHOST_MANUAL_DEFS is enabled."
    #endif
    /* Without manual defs, we emit definitions in all translation units. They
     * will be either static, weak or COMDAT. */
    #define GHOST_EMIT_DEFS 1
#endif

/*
 * GHOST_IMPL_DEF() is used to wrap non-inline function and variable
 * definitions.
 */
#include "ghost/preprocessor/ghost_pp_va_args.h"
#if GHOST_PP_VA_ARGS
    #if GHOST_EMIT_DEFS
        #define GHOST_IMPL_DEF(...) __VA_ARGS__
    #else
        #define GHOST_IMPL_DEF(...) ;
    #endif
#else
    #if GHOST_EMIT_DEFS
        #define GHOST_IMPL_DEF(x) x
    #else
        #define GHOST_IMPL_DEF(x) ;
    #endif
#endif

#endif
