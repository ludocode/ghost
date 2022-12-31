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

#ifndef GHOST_CLOSE_NOINTR_H_INCLUDED
#define GHOST_CLOSE_NOINTR_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A wrapper around POSIX close() that tries to handle EINTR correctly,
 * repeating the call if possible and necessary, and potentially blocking until
 * the file is actually closed regardless of any signals that may occur.
 *
 * This never returns EINTR.
 *
 * The specification of POSIX close() is fundamentally broken with regards to
 * EINTR:
 *
 *     https://www.daemonology.net/blog/2011-12-17-POSIX-close-is-broken.html
 *
 * For this reason most platforms have stronger guarantees regarding EINTR and
 * close(). These are the possibilities:
 *
 * - Linux and possibly others guarantee that close() can never return EINTR.
 *   On these platforms, the file descriptor is marked closed immediately; the
 *   actual closing of the file is either always asynchronous, or it continues
 *   asynchronously if close() is interrupted by a signal. On these platforms
 *   ghost_close_nointr() is just an alias of close().
 *
 * - HP-UX and possibly others guarantee that the file descriptor is still open
 *   if close() returns EINTR. On these platforms, it is safe to restart
 *   close(), which ghost_close_nointr() does (but this may lead to undesired
 *   blocking; see the warning below.)
 *
 * - Windows and possibly others do not support EINTR at all. On such
 *   platforms, close() or _close() cannot be interrupted, so
 *   ghost_close_nointr() is again an alias of it.
 *
 * - Other platforms may truly leave it unspecified. On such platforms, if
 *   close() returns EINTR, the program is in an unknowable and unrecoverable
 *   state. In this case ghost_close_nointr() aborts the program. (If you don't
 *   want this to happen because you're shutting down the application and you
 *   don't care about leaking file descriptors, don't use ghost_close_nointr();
 *   just call ghost_close().)
 *
 * @warning If the platform flushes on close() and blocks until flushed, this
 * may resume and continue blocking even after a signal is received. For this
 * reason you may want to only use this when reading, or you may want to call
 * fsync() first to flush any written data. You'll probably need to write
 * platform-specific code if you want to correctly handle interrupting a
 * long-running close().
 */
int ghost_close_nointr(int fd);
#endif

#ifndef ghost_has_ghost_close_nointr
    #ifdef ghost_close_nointr
        #define ghost_has_ghost_close_nointr 1
    #endif
#endif

/* We'll need ghost_close(). */
#ifndef ghost_has_ghost_close_nointr
    #include "ghost/io/ghost_close.h"
    #if !ghost_has_ghost_close
        #define ghost_has_ghost_close_nointr 0
    #endif
#endif

/* On platforms where close() never returns EINTR (because the platform
 * guarantees it or doesn't support EINTR at all), we pass it through directly. */
#ifndef ghost_has_ghost_close_nointr
    #if defined(__linux__) || defined(_WIN32)
        #define ghost_close_nointr ghost_close
        #define ghost_has_ghost_close_nointr 1
    #endif
#endif

/* Other platforms will require errno and various other headers */
#ifndef ghost_has_ghost_close_nointr
    #include "ghost/error/ghost_errno_is.h"
    #if !ghost_has_ghost_errno_is
        #define ghost_has_ghost_close_nointr 0
    #else
        #include "ghost/impl/ghost_impl_function.h"
    #endif
#endif

/* On platforms that guarantee close() can be restarted on EINTR, we restart
 * it. This means ghost_close_nointr() will keep retrying even if a signal
 * was meant to interrupt it; see the warning above. */
#ifndef ghost_has_ghost_close_nointr
    #ifdef __hpux
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_function
        int ghost_close_nointr(int fd) GHOST_IMPL_DEF({
            for (;;) {
                int ret = ghost_close(fd);
                if (ret == -1 && ghost_errno_is(EINTR))
                    continue;
                return ret;
            }
        })
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_close_nointr 1
    #endif
#endif

/* On all other platforms we treat EINTR from close() as a fatal error. */
#ifndef ghost_has_ghost_close_nointr
    #include "ghost/debug/ghost_fatal.h"
    #if ghost_has_ghost_fatal
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_function
        int ghost_close_nointr(int fd) GHOST_IMPL_DEF({
            int ret = ghost_close(fd);
            if (ret == -1 && ghost_errno_is(EINTR))
                ghost_fatal("close() returned EINTR");
            return ret;
        })
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_close_nointr 1
    #endif
#endif

#ifndef ghost_has_ghost_close_nointr
    #define ghost_has_ghost_close_nointr 0
#endif

#endif
