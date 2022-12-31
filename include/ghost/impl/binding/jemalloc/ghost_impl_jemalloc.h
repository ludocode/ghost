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

#ifndef GHOST_IMPL_JEMALLOC_H_INCLUDED
#define GHOST_IMPL_JEMALLOC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_USE_JEMALLOC
 *
 * Pre-define this to 1 if you intend to link against jemalloc and want Ghost to
 * use its non-standard API extensions.
 *
 * The default is 0.
 *
 * If this is 1, Ghost's allocation wrappers will use the jemalloc API. This
 * can provide better performance and more functionality such as
 * ghost_malloc_size() and ghost_malloc_good_size() on platforms that don't
 * otherwise support such functions.
 *
 *     https://jemalloc.net/jemalloc.3.html
 *
 * Note that jemalloc is not public-domain-equivalent. By enabling this you are
 * responsible for complying with the jemalloc license.
 *
 * FreeBSD provides jemalloc's extended functions as part of the standard API
 * so on FreeBSD, Ghost will include <malloc_np.h> and use those functions even
 * if this is 0. Set this to 1 if you want Ghost to include
 * <jemalloc/jemalloc.h> instead.
 */
#endif

/* We set this to 0 even on FreeBSD which uses jemalloc as the system
 * allocator. We have different checks to use the extended API on FreeBSD. */
#ifndef GHOST_USE_JEMALLOC
    #define GHOST_USE_JEMALLOC 0
#endif

#endif
