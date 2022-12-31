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

#ifndef GHOST_SYSCALL_H_INCLUDED
#define GHOST_SYSCALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Performs a system call.
 */
extern long ghost_syscall(long syscall_number, ...)
#endif

#ifndef ghost_has_ghost_syscall
    #ifdef ghost_syscall
        #define ghost_has_ghost_syscall 1
    #endif
#endif

/* We can't do syscalls on Cosmopolitan libc (we don't even know the OS we'll
 * be running on.) */
#ifndef ghost_has_ghost_syscall
    #ifdef __COSMOPOLITAN__
        #define ghost_has_ghost_syscall 0
    #endif
#endif

/* Windows and the Apple platforms (macOS, iOS) don't support syscalls. */
#ifndef ghost_has_ghost_syscall
    #if defined(_WIN32) || defined(__APPLE__)
        #define ghost_has_ghost_syscall 0
    #endif
#endif

/*
 * Linux and the BSDs otherwise support it. Some other systems may as well but
 * it's not in POSIX so we won't assume support for it. We can add additional
 * platforms as we discover them.
 *
 * Note that Linux is one of the only kernels that attempts to preserve binary
 * compatibility for syscalls. On virtually all other platforms, the libc is
 * the only supported mechanism for talking to the kernel.
 */
#ifndef ghost_has_ghost_syscall
    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
            defined(__DragonFly__) || defined(__linux__)
        #include "ghost/header/posix/ghost_unistd_h.h"
        #if ghost_has(ghost_unistd_h)
            #ifdef __linux__
                /* On Linux the syscall() function is not necessarily declared. We
                 * have to declare it ourselves. */
                #include "ghost/impl/ghost_impl_libc_asm.h"
                #include "ghost/impl/ghost_impl_libc_noexcept.h"
                #include "ghost/language/ghost_extern_c.h"
                #include "ghost/preprocessor/ghost_nothing.h"
                #if GHOST_IMPL_LIBC_ASM
                    ghost_extern_c
                    long ghost_syscall(long, ...)
                        ghost_impl_libc_noexcept(ghost_impl_libc_asm("syscall"));
                #else
                    /* We can't wrap this because there's no varargs syscall
                     * function. We have to declare it globally. */
                    ghost_extern_c
                    long syscall(long, ...)
                        ghost_impl_libc_noexcept(GHOST_NOTHING);
                    #define ghost_syscall syscall
                #endif
                #define ghost_has_ghost_syscall 1
            #else
                /* On other UNIX platforms we assume it's been declared in
                 * sys/syscall.h. */
                #define ghost_syscall syscall
                #define ghost_has_ghost_syscall 1
            #endif
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_syscall
    #define ghost_syscall 0
#endif

#endif
