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

#ifndef GHOST_EXPAND_MORE_H_INCLUDED
#define GHOST_EXPAND_MORE_H_INCLUDED

#include "ghost/ghost_core.h"

#include "ghost/preprocessor/ghost_expand.h"

/* TODO rename these, should use GHOST_EXPAND_N to expand N args */
/* TODO move to experimental */

#if ghost_has_GHOST_EXPAND

/**
 * Performs two preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_2(...) GHOST_EXPAND(GHOST_EXPAND(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_2 1

/**
 * Performs four preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_4(...) GHOST_EXPAND_2(GHOST_EXPAND_2(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_4 1

/**
 * Performs eight preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_8(...) GHOST_EXPAND_4(GHOST_EXPAND_4(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_8 1

/**
 * Performs 16 preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_16(...) GHOST_EXPAND_8(GHOST_EXPAND_8(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_16 1

/**
 * Performs 32 preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_32(...) GHOST_EXPAND_16(GHOST_EXPAND_16(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_32 1

/**
 * Performs 64 preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_64(...) GHOST_EXPAND_32(GHOST_EXPAND_32(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_64 1

/**
 * Performs 128 preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_128(...) GHOST_EXPAND_64(GHOST_EXPAND_64(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_128 1

/**
 * Performs 256 preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_256(...) GHOST_EXPAND_128(GHOST_EXPAND_128(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_256 1

/**
 * Performs 512 preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_512(...) GHOST_EXPAND_256(GHOST_EXPAND_256(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_512 1

/**
 * Performs 1024 preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_1024(...) GHOST_EXPAND_512(GHOST_EXPAND_512(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_1024 1

/**
 * Performs 2048 preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_2048(...) GHOST_EXPAND_1024(GHOST_EXPAND_1024(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_2048 1

/**
 * Performs 4096 preprocessor expansion passes on the arguments.
 */
#define GHOST_EXPAND_4096(...) GHOST_EXPAND_2048(GHOST_EXPAND_2048(__VA_ARGS__))
#define ghost_has_GHOST_EXPAND_4096 1

#endif

#endif
