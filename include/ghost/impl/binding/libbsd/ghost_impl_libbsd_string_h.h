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

#ifndef GHOST_IMPL_LIBBSD_STRING_H_H_INCLUDED
#define GHOST_IMPL_LIBBSD_STRING_H_H_INCLUDED

#include "ghost/ghost_core.h"

/*
 * Includes libbsd <bsd/string.h> (or libbsd <string.h> in overlay mode) if
 * GHOST_USE_LIBBSD is 1.
 *
 * libbsd ports various BSD features to other platforms. See e.g.
 * ghost_strlcpy() and ghost_strlcat().
 */

#include "ghost/impl/binding/libbsd/ghost_impl_libbsd_config.h"

#if GHOST_USE_LIBBSD
    #ifdef LIBBSD_OVERLAY
        #include <string.h>
    #else
        #include <bsd/string.h>
    #endif
#endif

#endif
