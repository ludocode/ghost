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

#ifndef GHOST_IMPL_ASSUMPTIONS_H_INCLUDED
#define GHOST_IMPL_ASSUMPTIONS_H_INCLUDED

/*
 * This file contains some basic assumptions that we use to make Ghost work on
 * common machines in case we can't directly determine them.
 *
 * This is mostly here to document our reliance on assumptions. It might come
 * in handy if we want Ghost to support really esoteric platforms someday.
 */

/* Assume char is 8 bits. */
#ifndef GHOST_IMPL_ASSUME_8_BIT_CHAR
    #define GHOST_IMPL_ASSUME_8_BIT_CHAR 1
#endif

/* Assume two's complement representation for signed integers.
 * Note that C++20 and (most likely) C23 require two's complement.
 * The GHOST_*_MIN constants statically assert that this is true. */
#ifndef GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
    #define GHOST_IMPL_ASSUME_TWOS_COMPLEMENT 1
#endif

/* Assume signed and unsigned types are the same width. */
#ifndef GHOST_IMPL_ASSUME_SIGNED_UNSIGNED_SAME_WIDTH
    #define GHOST_IMPL_ASSUME_SIGNED_UNSIGNED_SAME_WIDTH 1
    /* TODO we may be able to static assert this everywhere we use it */
#endif

/* Assume integers have no padding bits (so the max value depends strictly on
 * width and vice versa.)
 * TODO make sure we're using this everywhere it's needed */
#ifndef GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
    #define GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS 1
#endif

#endif
