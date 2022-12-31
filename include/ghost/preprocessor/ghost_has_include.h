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

#ifndef GHOST_HAS_INCLUDE_H_INCLUDED
#define GHOST_HAS_INCLUDE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_has(ghost_has_include)
 *
 * Detects whether __has_include exists and works properly.
 *
 * Ghost does not actually define ghost_has_include. This is a Ghost feature
 * called "ghost_has_include" which detects __has_include support. Check for a
 * header like this:
 *
 *     #include "ghost/preprocessor/ghost_has_include.h"
 *     #if ghost_has(ghost_has_include)
 *         #if __has_include(<some_header.h>)
 *             // the header definitely exists
 *         #else
 *             // the header definitely does not exist
 *         #endif
 *     #else
 *         // the header may or may not exist
 *     #endif
 *
 * The reason Ghost provides this is that some ill-behaved libraries will
 * define __has_include themselves if the compiler does not. For example,
 * libbsd does this:
 *
 *     #ifndef __has_include
 *     #define __has_include(x) 1
 *     #endif
 *
 * (see https://github.com/freedesktop/libbsd/blob/8f59221c4f0383153a7c7b499fbd1344cd9ad0f1/include/bsd/sys/cdefs.h#L27-L29 )
 *
 * In libbsd's overlay mode it will do this if you include any libc header it
 * overlays. It overlays almost all standard C headers so you are almost
 * guaranteed to wind up with this hack.
 *
 * There are worse offenders still. Qt does this:
 *
 *     #ifndef __has_include
 *     #define __has_include(x) 0
 *     #endif
 *
 * (see https://github.com/qt/qtbase/blob/b885820c395a0bbfb0ff55ab0ee47a4703aa6b59/src/corelib/global/qcompilerdetection.h#L432-L434 )
 *
 * Qt's explanation for this nonsense is that the future C++ draft standard
 * forbids wrapping __has_include in a macro. If they really want to avoid
 * wrapping it there is no reason they can't just check #ifdef __has_include
 * wherever they use it.
 *
 * There are many more libraries that define __has_include: OpenImageIO, Open
 * Shading Language, etc. This lazyness infects the code of anyone else that
 * tries to interact with these libraries. Please file bug reports against Qt,
 * libbsd and any other libraries that do this.
 *
 * Ghost has different fallbacks if __has_include isn't supported. Sometimes
 * it will assume the header exists, sometimes it will not, and sometimes it
 * will use additional checks to try to determine whether it's safe to include
 * it (see ghost/header/posix/ghost_unistd_h.h for an example.) It is therefore
 * critical that __has_include is only used if it actually works properly.
 */
#endif

#ifdef ghost_has_include
    #error "ghost_has_include cannot be defined. Define ghost_has_ghost_has_include to 1 or 0 to override Ghost's __has_include detection."
#endif

/*
 * __has_include is in C23 and C++17 and is implemented as an extension by many
 * compilers. #ifdef must evaluate it to true if supported so we don't need to
 * check compiler or language versions.
 *
 * (Note that in current versions of TinyCC, #ifdef __has_include will be
 * false, but __has_include(x) will expand to 0 for any x. They do this as a
 * workaround for code that uses __has_include() without checking whether it
 * exists. This check will correctly determine whether TinyCC supports
 * __has_include.)
 */
#ifndef ghost_has_ghost_has_include
    #ifndef __has_include
        /* __has_include is not defined. */
        #define ghost_has_ghost_has_include 0
    #endif
#endif

/*
 * Check whether __has_include is 1 on an existing header.
 *
 * If we are not amalgamated, we can just check whether one of our own headers
 * exists.
 *
 * If we are amalgamated, we don't know our own header name and there are no
 * others to check so we need to check against a standard C header. We use
 * <stddef.h> for this. <stddef.h> is fundamental to C; it's required to exist
 * everywhere even in freestanding and it's typically provided by the compiler,
 * not the libc, so it always exists. If __has_include says it doesn't exist we
 * assume __has_include is broken. If there are esoteric platforms that really
 * don't have <stddef.h> we will need to add special cases for them here.
 *
 * TODO test that this works even with Cosmopolitan
 */
#ifndef ghost_has_ghost_has_include
    #if GHOST_IMPL_AMALGAMATED
        #if !__has_include(<stddef.h>)
            /* __has_include is lying. It's always saying 0. */
            #define ghost_has_ghost_has_include 0
        #endif
    #else
        #if !__has_include("ghost/ghost_core.h")
            /* __has_include is lying. It's always saying 0. */
            #define ghost_has_ghost_has_include 0
        #endif
    #endif
#endif

/* Check whether __has_include is 0 on a non-existent header. */
#ifndef ghost_has_ghost_has_include
    /* This should go without saying: don't create this header. */
    #if __has_include("ghost/impl/nonexistent/ghost_impl_nonexistent_header.h")
        /* __has_include is lying. It's always saying 1. */
        #define ghost_has_ghost_has_include 0
    #endif
#endif

/* We've passed all the above checks so we believe __has_include works. */
#ifndef ghost_has_ghost_has_include
    #define ghost_has_ghost_has_include 1
#endif

#endif
