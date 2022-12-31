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

#ifndef GHOST_STRERROR_R_H_INCLUDED
#define GHOST_STRERROR_R_H_INCLUDED

#include "ghost/ghost_core.h"

/* pretty much any unix seems to support this. we just need to make sure we
 * don't get the GNU-specific version rather than the XSI version. this is for
 * the XSI version. */

/* https://linux.die.net/man/3/strerror_r
 * https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/strerror_r.3.html
 * https://man.openbsd.org/strerror.3 */

/* the windows implementation can wrap strerror_s(). it's the same thing but
 * with a different argument order. */

/* on any other platform we can implement this ourselves (assuming strerror()
 * returns constant or threadlocal storage), just use strerror() and copy the
 * string out */

/* also note C11 has strerror_s:
 * https://en.cppreference.com/w/c/string/byte/strerror
 * should probably just wrap ghost_strerror_s as fallback
 * TODO */
#define ghost_has_ghost_strerror_r 0

#endif
