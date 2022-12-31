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

#ifndef GHOST_SILENCE_PUSH_POP_OPT_H_INCLUDED
#define GHOST_SILENCE_PUSH_POP_OPT_H_INCLUDED

#ifndef ghost_has_GHOST_SILENCE_PUSH_OPT
    #ifdef GHOST_SILENCE_PUSH_OPT
        #define ghost_has_GHOST_SILENCE_PUSH_OPT 1
    #endif
#endif
#ifndef ghost_has_GHOST_SILENCE_POP_OPT
    #ifdef GHOST_SILENCE_POP_OPT
        #define ghost_has_GHOST_SILENCE_POP_OPT 1
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_PUSH_OPT
    #include "ghost/silence/ghost_silence_push_pop.h"
    #if ghost_has(GHOST_SILENCE_PUSH)
        #define GHOST_SILENCE_PUSH_OPT GHOST_SILENCE_PUSH
    #else
        #define GHOST_SILENCE_PUSH_OPT /*nothing*/
    #endif
    #define ghost_has_GHOST_SILENCE_PUSH_OPT 1
#endif
#ifndef ghost_has_GHOST_SILENCE_POP_OPT
    #include "ghost/silence/ghost_silence_push_pop.h"
    #if ghost_has(GHOST_SILENCE_POP)
        #define GHOST_SILENCE_POP_OPT GHOST_SILENCE_POP
    #else
        #define GHOST_SILENCE_POP_OPT /*nothing*/
    #endif
    #define ghost_has_GHOST_SILENCE_POP_OPT 1
#endif

#endif
