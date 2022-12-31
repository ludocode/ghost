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

#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

/* This file is defined as GHOST_CONFIG_H so it gets included by Ghost before
 * anything else. */

/* Make sure we really do come first */
#if defined(ghost_has) || defined(GHOST_VERSION) || defined(GHOST_EXPERIMENTAL)
    #error "GHOST_CONFIG_H not working?"
#endif

/* For now we just enable experimental in all builds. Later this will become a
 * variant. */
#define GHOST_EXPERIMENTAL 1

/* TODO I don't have a Windows SDK installed for VS2013 that supports GDI+ */
#ifdef _MSC_VER
    #if _MSC_VER < 1900
        #define ghost_has_ghost_gdiplus_h 0
    #endif
#endif

/* Disable some old GCC warnings that have no workarounds. */
/* TODO get rid of this whole block, Ghost internally silences what it needs and so do individual test files */
#if 0
#ifdef __GNUC__
    /* #pragma GCC diagnostic is supported since GCC 4.2. */
    #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2) && !defined(__clang__)
        /* These warnings need to be silenced on compilers before GCC 5. */
        #if __GNUC__ < 5
            /* TODO it doesn't make sense to include this here, this file is
             * included before any Ghost symbols are available. These warning
             * flags should go in the buildsystem */
            /*#include "ghost/detect/ghost_gcc.h"
            #if GHOST_GCC*/
            #ifndef __clang__
                /* see ghost_impl_detect_llong.h */
                #pragma GCC diagnostic ignored "-Wlong-long"
                /* see ghost_zero_init.h */
                #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
            #endif
        #endif
    #endif
#endif
#endif

#endif
