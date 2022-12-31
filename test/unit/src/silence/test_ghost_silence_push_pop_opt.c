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

#include "ghost/silence/ghost_silence_push_pop_opt.h"

#ifndef ghost_has_GHOST_SILENCE_PUSH_OPT
    #error "ghost/silence/ghost_silence_push_pop_opt.h must define ghost_has_GHOST_SILENCE_PUSH_OPT."
#endif
#ifndef ghost_has_GHOST_SILENCE_POP_OPT
    #error "ghost/silence/ghost_silence_push_pop_opt.h must define ghost_has_GHOST_SILENCE_POP_OPT."
#endif

#if !ghost_has_GHOST_SILENCE_PUSH_OPT
    #error "GHOST_SILENCE_PUSH_OPT is required."
#endif
#if !ghost_has_GHOST_SILENCE_POP_OPT
    #error "GHOST_SILENCE_POP_OPT is required."
#endif

typedef int unused;
