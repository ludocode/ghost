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

#ifndef GHOST_MUSL_H_INCLUDED
#define GHOST_MUSL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_MUSL
 *
 * 1 if we're pretty sure we're compiling against musl libc and 0 otherwise.
 *
 * If this is 1, the version of musl is defined by GHOST_MUSL_VERSION.
 *
 * @see GHOST_MUSL_VERSION
 */
#endif

/*
 * Handle overrides for both GHOST_MUSL and GHOST_MUSL_VERSION here.
 */

#ifndef ghost_has_GHOST_MUSL_VERSION
    #ifdef GHOST_MUSL_VERSION
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

#ifndef ghost_has_GHOST_MUSL
    #ifdef GHOST_MUSL
        #define ghost_has_GHOST_MUSL 1
    #elif defined(GHOST_MUSL_VERSION)
        /* If the user has defined GHOST_MUSL_VERSION, we're musl. */
        #define GHOST_MUSL 1
        #define ghost_has_GHOST_MUSL 1
    #endif
#endif

/*
 * Try to figure out whether we're musl.
 */

/* musl only supports Linux. */
#ifndef ghost_has_GHOST_MUSL
    #ifndef __linux__
        #define GHOST_MUSL 0
        #define ghost_has_GHOST_MUSL 1
    #endif
#endif

/* We have no libc in freestanding. */
#ifndef ghost_has_GHOST_MUSL
    #include "ghost/language/ghost_hosted.h"
    #if !GHOST_HOSTED
        #define GHOST_MUSL 0
        #define ghost_has_GHOST_MUSL 1
    #endif
#endif

/* Include whatever headers are necessary to get libc declaration macros. This
 * typically includes <string.h>, and we'll need it for our below type checks
 * anyway. If we don't even have <string.h>, we're not musl. */
#ifndef ghost_has_GHOST_MUSL
    #include "ghost/detect/ghost_libc.h"
    #include "ghost/header/c/ghost_string_h.h"
    #if !ghost_has(ghost_string_h)
        #define GHOST_MUSL 0
        #define ghost_has_GHOST_MUSL 1
    #endif
#endif

/* They'll come to their senses someday. (And even if they don't, distributions
 * like Alpine could patch it into <features.h> themselves. See
 * ghost_musl_version.h for an explanation of __x_musl_version__.) */
#ifndef ghost_has_GHOST_MUSL
    #if defined(__musl__) || defined(__MUSL__) || defined(__x_musl_version__)
        #define GHOST_MUSL 1
        #define ghost_has_GHOST_MUSL 1
    #endif
#endif

/* If we're some other libc, we're not musl. */
#ifndef ghost_has_GHOST_MUSL
    /* Look at all these other libcs that play nice! */
    #if defined(__GLIBC__) || defined(__UCLIBC__) || defined(__KLIBC__) || \
            defined(__NEWLIB__) || defined(__BIONIC__) || defined(__dietlibc__) || \
            /* and some that play a bit less nice... */ \
            defined(_PDCLIB_NULL) || defined(__MLIBC_ANSI_OPTION)
        #define GHOST_MUSL 0
        #define ghost_has_GHOST_MUSL 1
    #endif
#endif

/*
 * If we can check whether headers exist, let's check for a bunch of public but
 * uncommon or extension headers that musl provides. We're also checking for
 * headers that we'll need when detecting the version. If any of these headers
 * don't exist, we're not on musl.
 *
 * (Interestingly, the default glibc on many platforms appears to exclude
 * <stropts.h>. This probably detects musl even without the libc checks above.)
 *
 * The musl source releases don't appear to provide mechanisms for configuring
 * it to exclude headers but it's possible some systems exclude certain musl
 * headers anyway. If so we should remove them from this list. This is a good
 * reason to keep this list short.
 */
#ifndef ghost_has_GHOST_MUSL
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if \
                !__has_include(<byteswap.h>) || \
                !__has_include(<elf.h>) || \
                !__has_include(<endian.h>) || \
                !__has_include(<features.h>) || \
                !__has_include(<stdio_ext.h>) || \
                !__has_include(<stropts.h>) || \
                !__has_include(<sys/syscall.h>) || \
                !__has_include(<sys/resource.h>) || \
                !__has_include(<sysexits.h>) || \
                !__has_include(<values.h>) || \
                \
                !__has_include(<bits/alltypes.h>) /* internal implementation detail of musl; see below */
            #define GHOST_MUSL 0
            #define ghost_has_GHOST_MUSL 1
        #endif
    #endif
#endif

/*
 * musl defines the types it needs by first defining e.g. __NEED_size_t, then
 * including <bits/alltypes.h> which does not have a header guard. Instead it
 * defines e.g. __DEFINED_size_t to avoid repeating typedefs.
 *
 * We detect this behaviour. size_t is in fact the only one defined by
 * <string.h> which we've included above. This could be made more robust by
 * including more headers and checking more types if there is a need.
 *
 * This is not entirely unprecedented. GMP detects musl internals for example:
 *
 *     https://gmplib.org/repo/gmp-6.2/file/tip/gmp-h.in#l268
 *
 * We're depending on an internal implementation detail of musl which they
 * could change at any time. Still, this makes Ghost a lot safer for any libcs
 * that aren't musl. It's better to fail to detect musl than it is to
 * erroneously detect something else as musl.
 */
#ifndef ghost_has_GHOST_MUSL
    #if !defined(__NEED_size_t) || !defined(__DEFINED_size_t)
        #define GHOST_MUSL 0
        #define ghost_has_GHOST_MUSL 1
    #endif
#endif

/*
 * This is just an escape hatch on the off chance that somebody is making a new
 * Linux libc that looks an awful lot like musl and needs to tell a bunch of
 * old versions of Ghost that they don't want to be mistaken for musl. I'm
 * sorry; I truly hope this never becomes necessary.
 */
#ifndef ghost_has_GHOST_MUSL
    #ifdef __NOT_MUSL__
        #define GHOST_MUSL 0
        #define ghost_has_GHOST_MUSL 1
    #endif
#endif

/* If we've passed all the above checks, we are most probably on musl. */
#ifndef ghost_has_GHOST_MUSL
    #define GHOST_MUSL 1
    #define ghost_has_GHOST_MUSL 1
#endif

#endif
