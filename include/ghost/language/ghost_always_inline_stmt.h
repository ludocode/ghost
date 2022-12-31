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

#ifndef GHOST_ALWAYS_INLINE_STMT_H_INCLUDED
#define GHOST_ALWAYS_INLINE_STMT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_always_inline_stmt
 *
 * Declares that all function calls in the following non-declaration statement
 * should be inlined if possible.
 *
 * Example:
 *
 *     ghost_always_inline_stmt foo(bar()); // foo() and bar() will be inlined if possible
 *
 * This can't be used as part of a declaration, e.g:
 *
 *      ghost_always_inline_stmt int x = foo(bar()); // error, statement attribute cannot be used on a declaration
 *
 * A possible workaround is:
 *
 *      int x;
 *      ghost_always_inline_stmt x = foo(bar());
 */
#endif
/* TODO move this to experimental */

#ifndef ghost_has_ghost_always_inline_stmt
    #ifdef ghost_always_inline_stmt
        #define ghost_has_ghost_always_inline_stmt 1
    #endif
#endif

/* Clang 15.0+ has [[clang::always_inline]] for statements, as long as the
 * language standard supports standard attributes.
 * https://clang.llvm.org/docs/AttributeReference.html#always-inline-force-inline */
#ifdef __clang__
    /* TODO this version check won't work on e.g. Apple Clang and other variants */
    #if __clang_major__ >= 15
        #ifndef ghost_has_ghost_always_inline_stmt
            #ifdef __cplusplus
                #include "ghost/language/ghost_cplusplus.h"
                #if __cplusplus >= 201103L
                    #include "ghost/impl/language/ghost_impl_attribute_namespace_clang.h"
                    #define ghost_always_inline_stmt [[GHOST_IMPL_ATTRIBUTE_NAMESPACE_CLANG::__always_inline__]]
                    #define ghost_has_ghost_always_inline_stmt 1
                #endif
            #endif
        #endif
        #ifndef ghost_has_ghost_always_inline_stmt
            #if GHOST_IMPL_ENABLE_C23
                #include "ghost/language/ghost_stdc_version.h"
                #if ghost_has(GHOST_STDC_VERSION)
                    #if GHOST_STDC_VERSION >= 202000L
                        #include "ghost/impl/language/ghost_impl_attribute_namespace_clang.h"
                        #define ghost_always_inline_stmt [[GHOST_IMPL_ATTRIBUTE_NAMESPACE_CLANG::__always_inline__]]
                        #define ghost_has_ghost_always_inline_stmt 1
                    #endif
                #endif
            #endif
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_always_inline_stmt
    #define ghost_has_ghost_always_inline_stmt 0
#endif

#endif
