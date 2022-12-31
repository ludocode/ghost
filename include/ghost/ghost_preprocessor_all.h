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

#ifndef GHOST_PREPROCESSOR_ALL_H_INCLUDED
#define GHOST_PREPROCESSOR_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes everything in `ghost/preprocessor/`.
 *
 * This is all of Ghost's preprocessor macros.
 *
 * These are all simple macros so they will have minimal effect on compile
 * time. There's no real downside to including them all. Many of them are
 * already included by other Ghost headers anyway.
 *
 * We don't include them in ghost_common.h simply because they aren't used
 * (and, in the opinion of some, shouldn't be used) in typical C code. Note
 * that many of them will be included indirectly anyway to implement other
 * parts of Ghost.
 */

/* TODO */
#include "ghost/preprocessor/ghost_not.h"

#endif
