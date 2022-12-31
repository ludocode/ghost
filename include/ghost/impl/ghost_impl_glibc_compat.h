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

#ifndef GHOST_IMPL_GLIBC_COMPAT_H_INCLUDED
#define GHOST_IMPL_GLIBC_COMPAT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_GLIBC_COMPAT
 *
 * Determines the level of compatibility Ghost should use for running on
 * non-glibc libcs when compiling against glibc.
 *
 * Pre-define this to a date in the form YYYYMMDD to disable the use of any
 * glibc features that are not widely available in libcs released by that
 * date that attempt to provide glibc runtime compatibility (such as musl.)
 *
 * When this is enabled, an app built against glibc should run under other
 * libcs (by manually running the appropriate dynamic loader on them or
 * through a libc6 symlink or alternate loader from a package like
 * libc6-compat) without any missing or misbehaving symbols from Ghost.
 *
 * Suppose you are building against glibc, but you want your binary to also run
 * on Alpine 3.8 or later with libc6-compat. Alpine 3.8.0 was launched with
 * musl 1.1.19 which was released on 2018-02-22, so do this:
 *
 *    #define GHOST_GLIBC_COMPAT 20180222
 *
 * With the above, Ghost won't use any glibc features that weren't available in
 * musl 1.1.19. For example musl added GNU qsort_r() in version 1.2.3 which was
 * released on 2022-04-07. This is later than 2018-06-26 so Ghost won't use
 * glibc qsort_r(). The result should therefore run on Alpine 3.8 or later.
 *
 * See Ghost's detection of GNU qsort_r() in:
 *
 *     ghost/impl/algorithm/qsort/ghost_impl_ex_gnu_qsort_r.h
 *
 * The default is 0, which means Ghost will use everything available in the
 * glibc against which it is being built.
 *
 * Set this to 1 (meaning "the beginning of time") if you want to avoid using
 * any glibc extensions that might not have ever been in any other Linux libc.
 * In this case Ghost will avoid using pretty much any GNU extension functions.
 *
 * This option has no effect if the libc you're compiling against is not glibc.
 */
#endif

#ifndef GHOST_GLIBC_COMPAT
    #define GHOST_GLIBC_COMPAT 0
#endif

#endif
