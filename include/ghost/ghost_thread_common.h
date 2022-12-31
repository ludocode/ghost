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

#ifndef GHOST_THREAD_COMMON_H_INCLUDED
#define GHOST_THREAD_COMMON_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes common threading headers.
 *
 * This includes mutex, condition, once, thread-specific storage, etc. It does
 * not, however, include one of Ghost's mechanisms for creating or managing
 * threads. You should choose and include only one of the following:
 *
 * - ghost/thread/ghost_vthread_all.h
 * - ghost/thread/ghost_ithread_all.h
 * - ghost/thread/ghost_vpthread_all.h
 *
 * By including only one thread, you reduce the risk of calling a function of
 * the wrong type that would otherwise compile (for example, calling
 * ghost_vpthread_exit() in a thread created with ghost_ithread_create().)
 */

#include "ghost/thread/ghost_mutex.h"
#include "ghost/thread/ghost_condition.h"
#include "ghost/thread/ghost_once.h"
#include "ghost/thread/ghost_tss.h"
#include "ghost/thread/ghost_thread_id.h"
#include "ghost/thread/ghost_thread_yield.h"

#endif
