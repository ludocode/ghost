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

#ifndef GHOST_IVEC_T_H_INCLUDED
#define GHOST_IVEC_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A vector of ints.
 */
typedef /*unspecified*/ ghost_ivec_t;
#endif

#ifndef ghost_has_ghost_ivec_t
    #ifdef ghost_ivec_t
        #define ghost_has_ghost_ivec_t 1
    #endif
#endif

/* We require Ghost's generic vector. It will require malloc() among other
 * things. */
#ifndef ghost_has_ghost_ivec_t
    #include "ghost/container/generic/gvec/ghost_gvec_t.h"
    #if ghost_has(ghost_gvec_t)
        typedef struct {
            ghost_gvec_t ghost_impl_v_gvec;
        } ghost_ivec_t;
        #define ghost_has_ghost_ivec_t 1
    #endif
#endif

#ifndef ghost_has_ghost_ivec_t
    #define ghost_has_ghost_ivec_t 0
#endif

#endif

