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

#ifndef GHOST_SSET_H_INCLUDED
#define GHOST_SSET_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * A set of strings, implemented as a weight-balanced tree.
 */
#endif

#ifndef ghost_has_ghost_sset
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if ghost_has(ghost_sset_t)
        #include "ghost/container/common/sset/ghost_sset_contains.h"
        #include "ghost/container/common/sset/ghost_sset_contains_l.h"
        #include "ghost/container/common/sset/ghost_sset_destroy.h"
        #include "ghost/container/common/sset/ghost_sset_find.h"
        #include "ghost/container/common/sset/ghost_sset_find_after.h"
        #include "ghost/container/common/sset/ghost_sset_find_after_l.h"
        #include "ghost/container/common/sset/ghost_sset_find_before.h"
        #include "ghost/container/common/sset/ghost_sset_find_before_l.h"
        #include "ghost/container/common/sset/ghost_sset_find_l.h"
        #include "ghost/container/common/sset/ghost_sset_first.h"
        #include "ghost/container/common/sset/ghost_sset_init.h"
        #include "ghost/container/common/sset/ghost_sset_insert.h"
        #include "ghost/container/common/sset/ghost_sset_insert_l.h"
        #include "ghost/container/common/sset/ghost_sset_it_length.h"
        #include "ghost/container/common/sset/ghost_sset_it_string.h"
        #include "ghost/container/common/sset/ghost_sset_it_t.h"
        #include "ghost/container/common/sset/ghost_sset_last.h"
        #include "ghost/container/common/sset/ghost_sset_next.h"
        #include "ghost/container/common/sset/ghost_sset_previous.h"
        #include "ghost/container/common/sset/ghost_sset_remove.h"
        #include "ghost/container/common/sset/ghost_sset_remove_all.h"
        #include "ghost/container/common/sset/ghost_sset_remove_it.h"
        #include "ghost/container/common/sset/ghost_sset_remove_l.h"
        #define ghost_has_ghost_sset 1
    #else
        #define ghost_has_ghost_sset 0
    #endif
#endif

#endif
