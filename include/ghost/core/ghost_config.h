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

#ifndef GHOST_CONFIG_H_INCLUDED
#define GHOST_CONFIG_H_INCLUDED

/**
 * @file
 *
 * Contains general configuration options for Ghost.
 */



/**
 * @def GHOST_CONFIG_H
 *
 * Pre-define this to a header name to have Ghost include it before Ghost
 * configures or defines any features.
 *
 * This can be used to configure Ghost or to override any Ghost features by
 * defining or disabling them beforehand.
 *
 * Your header name should be in quotes (or angle brackets) as in a normal
 * `#include` statement. This means you may need extra escaping, e.g.:
 *
 *     -DGHOST_CONFIG_H='"my_ghost_config.h"'
 */
#ifdef GHOST_CONFIG_H
    #include GHOST_CONFIG_H
#endif



/*
 * We include ghost_core.h AFTER including the user's custom header. This
 * ensures the user's custom header always comes before anything in Ghost.
 */
#include "ghost/ghost_core.h"



/*
 * Main configuration options
 */

/**
 * @def GHOST_EXPERIMENTAL
 *
 * Pre-define this to 1 to enable Ghost's experimental features.
 *
 * Experimental features are those that have not been extensively tested or
 * that may have their interface change in the future.
 *
 * Ghost may alter or remove any feature marked experimental at any time.
 */
#ifndef GHOST_EXPERIMENTAL
    #define GHOST_EXPERIMENTAL 0
#endif



/*
 * Internal config
 */

/*
 * This is an internal configuration option of Ghost used to generate
 * documentation. Don't define this.
 */
/* TODO rename to GHOST_IMPL_DOCUMENTATION */
#ifndef GHOST_DOCUMENTATION
    #define GHOST_DOCUMENTATION 0
#endif

/*
 * This is an internal configuration option of Ghost used to detect when Ghost
 * is amalgamated. Don't define this; it's defined automatically in
 * amalgamations.
 */
#ifndef GHOST_IMPL_AMALGAMATED
    #define GHOST_IMPL_AMALGAMATED 0
#endif

/*
 * This enables the experimental C2x (C23) support. By default it matches
 * GHOST_EXPERIMENTAL.
 *
 * C23 support will be locked behind this until the standard is approved. Once
 * approved, we'll start unlocking features from this one-by-one as they become
 * supported in implementations.
 *
 * The value of __STDC_VERSION__ for C23 won't be defined until some time
 * around when the standard is ratified. In the meantime we do this:
 *
 *     #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
 */
/* TODO why IMPL? rename to GHOST_ENABLE_C2X */
/* TODO maybe get rid of this entirely, just use GHOST_EXPERIMENTAL */
#ifndef GHOST_IMPL_ENABLE_C23
    #define GHOST_IMPL_ENABLE_C23 GHOST_EXPERIMENTAL
#endif

/*
 * This enables the experimental C++2a (C++23) support. By default it matches
 * GHOST_EXPERIMENTAL.
 *
 * C++23 support will be locked behind this until the standard is approved.
 * Once approved, we'll start unlocking features from this one-by-one as they
 * become supported in implementations.
 *
 * The value of __cplusplus for C23 won't be defined until some time around
 * when the standard is ratified. In the meantime we do this:
 *
 *     #if ghost_cplusplus > 202000L && GHOST_ENABLE_CXX23
 */
#ifndef GHOST_ENABLE_CXX23
    #define GHOST_ENABLE_CXX23 GHOST_EXPERIMENTAL
#endif



#endif
