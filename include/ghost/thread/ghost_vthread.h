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

#ifndef GHOST_VTHREAD_H_INCLUDED
#define GHOST_VTHREAD_H_INCLUDED

/* Include all functions that use ghost_vthread_t. */
#include "ghost/thread/vthread/ghost_vthread_t.h"
#include "ghost/thread/vthread/ghost_vthread_id.h"
#include "ghost/thread/vthread/ghost_vthread_create.h"
#include "ghost/thread/vthread/ghost_vthread_join.h"
#include "ghost/thread/vthread/ghost_vthread_detach.h"
#include "ghost/thread/vthread/ghost_vthread_exit.h"
#include "ghost/thread/vthread/ghost_vthread_is_current.h"

/* Include functions that work on all threads. */
#include "ghost/thread/ghost_thread_yield.h"

/* Include all options used for creating threads. */
#include "ghost/thread/ghost_thread_options.h"

#endif
