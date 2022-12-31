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

#ifndef GHOST_TSS_H_INCLUDED
#define GHOST_TSS_H_INCLUDED

/*
 * @file
 *
 * Includes all files related to ghost_tss.
 */

#include "ghost/thread/tss/ghost_tss_t.h"
#include "ghost/thread/tss/ghost_tss_init.h"
#include "ghost/thread/tss/ghost_tss_init_dtor.h"
#include "ghost/thread/tss/ghost_tss_destroy.h"
#include "ghost/thread/tss/ghost_tss_set.h"
#include "ghost/thread/tss/ghost_tss_get.h"

#ifndef ghost_has_ghost_tss
    /* note that we don't require init_dtor */
    #if ghost_has(ghost_tss_t) && \
            ghost_has(ghost_tss_init) && ghost_has(ghost_tss_destroy) && \
            ghost_has(ghost_tss_set) && ghost_has(ghost_tss_get)
        #define ghost_has_ghost_tss 1
    #else
        #define ghost_has_ghost_tss 0
    #endif
#endif

#endif
