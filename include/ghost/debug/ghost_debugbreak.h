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

#ifndef GHOST_DEBUGBREAK_H_INCLUDED
#define GHOST_DEBUGBREAK_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def ghost_debugbreak() __debugbreak
 *
 * Causes the debugger to break.
 *
 * This is a way of defining a breakpoint within the code itself. If the
 * program is running under a debugger, the debugger will break when executing
 * ghost_debugbreak(). If the program is not running under a debugger, the
 * system may pause the program and prompt the user to attach a debugger, or it
 * may deliver it a signal or otherwise kill the program.
 *
 * If a debugbreak instruction is supported, no other side effects should
 * occur. It should be safe for the developer to resume execution from
 * ghost_debugbreak().
 *
 * If a debugbreak instruction is not supported, this aborts the program via
 * ghost_abort().
 *
 * @see ghost_abort
 */

/* This implementation is fairly primitive at the moment. I'm looking to expand
 * it but I want to be able to actually test the additions. In the meantime
 * there are probably better third-party implementations of this. */

#ifndef ghost_has_ghost_debugbreak
    #ifdef ghost_debugbreak
        #define ghost_has_ghost_debugbreak 1
    #endif
#endif

/* Microsoft has __debugbreak() */
#ifndef ghost_has_ghost_debugbreak
    #ifdef _MSC_VER
        /* https://docs.microsoft.com/en-us/cpp/intrinsics/debugbreak */
        #include <intrin.h>
        #define ghost_debugbreak() __debugbreak()
        #define ghost_has_ghost_debugbreak 1
    #endif
#endif

/* Clang (in recent versions) has __builtin_debugtrap(). We use this builtin on
 * any compiler that declares support for it. */
#ifndef ghost_has_ghost_debugbreak
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        /* https://clang.llvm.org/docs/LanguageExtensions.html#builtin-debugtrap */
        #if __has_builtin(__builtin_debugtrap)
            #define ghost_debugbreak() __builtin_debugtrap()
            #define ghost_has_ghost_debugbreak 1
        #endif
    #endif
#endif

/* Use GNU inline assembly where possible to trigger a break instruction. */
#ifndef ghost_has_ghost_debugbreak
    #if defined(__GNUC__) && !defined(__chibicc__)

        #ifndef GHOST_DEBUGBREAK_IMPL_ASM
            #if defined(__i386__) || defined(__x86_64__)
                /* "int3" is supposedly the best way to do this:
                 *     https://stackoverflow.com/questions/173618/is-there-a-portable-equivalent-to-debugbreak-debugbreak#comment112451699_49079078 */
                #define GHOST_DEBUGBREAK_IMPL_ASM "int3"
            #elif defined(__aarch64__)
                #define GHOST_DEBUGBREAK_IMPL_ASM ".inst 0xd4200000"
            #elif defined(__thumb__)
                #define GHOST_DEBUGBREAK_IMPL_ASM ".inst 0xde01"
            #elif defined(__arm__)
                #define GHOST_DEBUGBREAK_IMPL_ASM ".inst 0xe7f001f0"
            #endif
        #endif

        #ifdef GHOST_DEBUGBREAK_IMPL_ASM
            #include "ghost/impl/ghost_impl_always_inline.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            void ghost_debugbreak(void) {
                __asm__ __volatile__ (GHOST_DEBUGBREAK_IMPL_ASM);
            }
            GHOST_IMPL_FUNCTION_CLOSE
            #define ghost_has_ghost_debugbreak 1
            #undef GHOST_DEBUGBREAK_IMPL_ASM
        #endif

    #endif
#endif

/* See if we can raise a trap signal. SIGTRAP is not required in any C standard
 * but it's required by POSIX. It's supposed to be a macro (?) so we can test
 * for it. */
#ifndef ghost_has_ghost_debugbreak
    #include "ghost/header/c/ghost_signal_h.h"
    #ifdef SIGTRAP
        #ifdef __cplusplus
            #define ghost_debugbreak() ::raise(SIGTRAP)
        #else
            #define ghost_debugbreak() raise(SIGTRAP)
        #endif
        #define ghost_has_ghost_debugbreak 1
    #endif
#endif

/*
 * Note that we don't use __builtin_trap() directly. It causes an invalid
 * instruction from which it's not safe to resume and it causes the compiler to
 * optimize away any code following the trap so it's no better than abort().
 * ghost_abort() will use __builtin_trap() anyway if it doesn't have anything
 * else so we just use ghost_abort().
 */

/* If we don't have any of the above, we map ghost_debugbreak() to
 * ghost_abort(). The debugger won't be able to resume execution after this but
 * we don't have any other way of stopping the program. */
#ifndef ghost_has_ghost_debugbreak
    #include "ghost/debug/ghost_abort.h"
    #if ghost_has(ghost_abort)
        #define ghost_debugbreak ghost_abort
        #define ghost_has_ghost_debugbreak 1
    #endif
#endif

#ifndef ghost_has_ghost_debugbreak
    #define ghost_has_ghost_debugbreak 0
#endif

#endif
