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

#ifndef GHOST_ASSERT_FAIL_H_INCLUDED
#define GHOST_ASSERT_FAIL_H_INCLUDED

#include "ghost/ghost_core.h"

/* TODO rename this to something more descriptive like ghost_handle_fatal_error() */

#if GHOST_DOCUMENTATION
/**
 * Handles an assertion failure or fatal error, ultimately aborting the
 * program.
 *
 * This is called from the following macros:
 *
 * - ghost_assert()
 * - ghost_check()
 * - ghost_ensure()
 * - ghost_assume()
 * - ghost_fatal()
 *
 * The default behaviour prints details to stderr, attempts to trigger a
 * debugger if in a debug build, and aborts.
 *
 * Override this in order to trigger special handling when a fatal error
 * occurs. You could for example show a message dialog to the user, send a bug
 * report, write to a log, restart your process, etc. Beware that multiple
 * threads may call this simultaneously. If you override this, your function
 * must be annotated noreturn if possible (see ghost_noreturn_opt.)
 *
 * One useful way to override this is to eliminate all of the context strings
 * to reduce the size of your build. Like this:
 *
 *     #define ghost_assert_fail(...) ghost_abort()
 *
 * @see ghost_noreturn_opt
 * @see ghost_assert()
 * @see ghost_check()
 * @see ghost_ensure()
 * @see ghost_assume()
 * @see ghost_fatal()
 * @see ghost_abort()
 */
[[noreturn]]
void ghost_assert_fail(
        const char* /*nullable*/ assertion,
        const char* /*nullable*/ message,
        const char* file,
        int line,
        const char* /*nullable*/ function);
#endif

#include "ghost/debug/ghost_debug.h"

#ifndef ghost_has_ghost_assert_fail
    #ifdef ghost_assert_fail
        #define ghost_has_ghost_assert_fail 1
    #endif
#endif

#ifndef ghost_has_ghost_assert_fail
    #include "ghost/debug/ghost_debugbreak.h"
    #include "ghost/debug/ghost_abort.h"
    #if ghost_has_ghost_debugbreak || ghost_has_ghost_abort
        #include "ghost/debug/ghost_abort.h"
        #include "ghost/language/ghost_noreturn_opt.h"
        #include "ghost/language/ghost_cold.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/language/ghost_discard.h"
        #include "ghost/header/c/ghost_stdio_h.h"
        #include "ghost/io/ghost_flockfile.h"
        #include "ghost/io/ghost_ftrylockfile.h"

        /*
         * Without <stdio.h> we won't be able to print messages so we
         * force-inline this to allow the compiler to elide them.
         * This is pulled out due to this chibicc bug:
         *     https://github.com/rui314/chibicc/issues/99
         */
        #ifdef GHOST_IMPL_ASSERT_FAIL_LINKAGE
            #error
        #endif
        #if ghost_has_ghost_stdio_h
            #include "ghost/impl/ghost_impl_noinline.h"
            #define GHOST_IMPL_ASSERT_FAIL_LINKAGE ghost_cold ghost_impl_noinline
        #else
            #include "ghost/impl/ghost_impl_always_inline.h"
            #define GHOST_IMPL_ASSERT_FAIL_LINKAGE ghost_impl_always_inline
        #endif

        GHOST_IMPL_FUNCTION_OPEN
        ghost_noreturn_opt
        GHOST_IMPL_ASSERT_FAIL_LINKAGE
        void ghost_assert_fail(
                const char* /*nullable*/ assertion,
                const char* /*nullable*/ message,
                const char* file, int line, const char* function)
        #undef GHOST_IMPL_ASSERT_FAIL_LINKAGE
        #if !GHOST_EMIT_DEFS
        ;
        #else
        {
            #if ghost_has(ghost_stdio_h)
                /* file should never be null or blank but we check anyway to
                 * make sure our crash handler doesn't crash and we print
                 * something nice. */
                if (file == ghost_null || file[0] == '\0')
                    file = "(unknown file)";
                if (function == ghost_null || function[0] == '\0')
                    function = "(unknown function)";

                /*
                 * We flush stdout to make sure logs are up to date up to
                 * the point of the crash, at least for this thread.
                 *
                 * Obviously this won't help if you are writing logs to a file
                 * but in that case you probably need to override this to write
                 * the assertion to your log as well.
                 */
                fflush(stdout);

                /*
                 * If we can lock streams, we try to lock both stdout and
                 * stderr in order to stop output from all background threads
                 * before printing our message.
                 *
                 * flockfile() is required to be recursive so it doesn't
                 * matter if these are already locked or if they have been
                 * mapped to the same stream.
                 *
                 * We lock stderr first because we have to have it locked
                 * (fprintf() would do it for us if we didn't.) We then only
                 * try to lock stdout. We don't want to deadlock on the
                 * off-chance that some other thread is also trying to lock
                 * both in the opposite order.
                 *
                 * This means there's potential for some other thread to write
                 * stuff interleaved with our assertion message if we fail to
                 * lock stdout. Still, it's not safe to lock both, and some
                 * messy logs is better than a deadlock.
                 */
                #if ghost_has(ghost_flockfile)
                    ghost_flockfile(stderr);
                #endif
                #if ghost_has(ghost_ftrylockfile)
                    if (0 == ghost_ftrylockfile(stdout)) {
                        /* If we successfully locked, flush again just in case
                         * some other thread wrote stuff between our previous
                         * flush and lock. (Don't flush if we didn't lock
                         * because flush will require a lock!) */
                        fflush(stdout);
                    }
                #endif

                /* We print everything in one call in case the platform doesn't
                 * have flockfile(). We lead with a newline in case a previous
                 * line wasn't ended. */
                if (assertion != ghost_null && assertion[0] != '\0') {
                    if (message != ghost_null && message[0] != '\0') {
                        fprintf(stderr, "\nAssertion failed at %s:%d in %s:\n    %s\n    %s\n",
                                file, line, function, assertion, message);
                    } else {
                        fprintf(stderr, "\nAssertion failed at %s:%d in %s:\n    %s\n",
                                file, line, function, assertion);
                    }
                } else {
                    if (message != ghost_null && message[0] != '\0') {
                        fprintf(stderr, "\nFatal error at %s:%d in %s:\n    %s\n",
                                file, line, function, message);
                    } else {
                        fprintf(stderr, "\nFatal error at %s:%d in %s\n",
                                file, line, function);
                    }
                }

                /* We don't unlock the streams. We don't want other threads to
                 * be able to print anything in between our error message and
                 * abort. */
            #else
                /* Without <stdio.h> we have no way to print an error message.
                 * If you want to print something, override ghost_assert_fail(). */
                ghost_discard(assertion);
                ghost_discard(message);
                ghost_discard(file);
                ghost_discard(line);
                ghost_discard(function);
            #endif

            /* On some platforms debugbreak can prompt the user to attach a
             * debugger. You probably don't want that to happen in production.
             * In a debug build, or if we can't abort, we trigger the debugger
             * but otherwise we just abort(). */
            #if GHOST_DEBUG || !ghost_has(ghost_abort)
                ghost_debugbreak();
            #endif

            /* Even if we triggered the debugger, we don't actually want to be
             * able to resume execution from a failed assert so we always abort
             * if we can to prevent that. */
            #if ghost_has(ghost_abort)
                ghost_abort();
            #endif
        }
        #endif
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_assert_fail 1
    #endif
#endif

#ifndef ghost_has_ghost_assert_fail
    #define ghost_has_ghost_assert_fail 0
#endif

#endif
