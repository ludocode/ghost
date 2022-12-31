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

#ifndef GHOST_LIBC_H_INCLUDED
#define GHOST_LIBC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * This file includes whatever headers are necessary to get feature-declaration
 * macros from the libc.
 *
 * It can sometimes be difficult to know how to detect the libc. On GNU/Linux
 * for example, if you include only `<stddef.h>`, `__GLIBC__` won't be defined.
 * This is because `<stddef.h>` is provided by the compiler, not the libc.
 *
 * The macro `__GLIBC__` is actually defined in `<features.h>`, but this
 * non-standard header does not exist on all platforms. This is a chicken and
 * egg problem: `<features.h>` tells you the libc, but you need to already know
 * the libc to determine whether it's safe to include it.
 *
 * Ghost simplifies this by providing this file. It includes whatever is
 * necessary to activate libc detection macros.
 *
 * Note that this does *not* include Ghost's own libc detection like
 * GHOST_GLIBC and GHOST_MUSL. You need to include those specific headers to
 * get them.
 *
 * TODO get rid of this file, this libc detection is a Linux-only problem, we
 * should just include ghost_features_h if there's any chance the system might
 * be Linux.
 */
#endif

/*
 * We include <string.h>, not <features.h> to get libc declaration macros
 * (__GLIBC__, etc.) <features.h> is non-standard so we won't actually know
 * whether it exists until we've determined the libc.
 *
 * Lower-level headers like <stddef.h> are often provided by the compiler
 * rather than the libc so they won't define e.g. __GLIBC__. <string.h> is
 * always from the libc, it's been around since ancient times, and it's not
 * likely to be omitted by a partial embedded libc (for example one that
 * omits locales, datetimes, files, etc.)
 */
#include "ghost/header/c/ghost_string_h.h"

/* TODO we'd like to also include <features.h> here but ghost_features_h.h
 * uses this. Need to probably move the contents of this and ghost_features_h.h
 * to an impl/ header that does everything. Or just move the above to
 * ghost_features_h.h and add that include here. */

/* TODO either also include e.g. <sys/param.h> on FreeBSD:
 *    https://docs.freebsd.org/en/books/porters-handbook/versions/
 * or just get rid of this whole file, including this stuff is super OS-specific anyway */

#endif
