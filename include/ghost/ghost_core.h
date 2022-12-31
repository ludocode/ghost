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

#ifndef GHOST_CORE_H_INCLUDED
#define GHOST_CORE_H_INCLUDED

/**
 * @file
 *
 * Includes the core parts of Ghost, which mainly revolve around versioning and
 * feature detection.
 *
 * All other Ghost headers include this so these are available everywhere.
 */

/*
 * This header is a bit special because it's intentionally circular. All
 * headers in Ghost include this file, even the headers this includes. Any
 * Ghost header gets you all of ghost/core/.
 *
 * This is primarily so that if you include only `ghost/core/ghost_version.h`
 * (say to check the version before including anything else),
 * ghost_has(GHOST_VERSION) still works, and likewise if you include only
 * `ghost/core/ghost_has.h`, you can still check its GHOST_VERSION. In both
 * cases the config and, most importantly, the user's GHOST_CONFIG_HEADER get
 * included before anything that might use it.
 *
 * Circular includes are perfectly legal C/C++ but some static analysis tools
 * may warn about them. To preempt this we'll check the header guards for these
 * files before including them. We'll put whatever other workarounds we need to
 * silence warnings here and in ghost/core/ as well.
 */

/* ghost_config.h must come first. It includes the user's config which contains
 * pre-defined overrides. */
#ifndef GHOST_CONFIG_H_INCLUDED
    #include "ghost/core/ghost_config.h"
#endif

/* Other ghost/core/ headers follow */
#ifndef GHOST_VERSION_H
    #include "ghost/core/ghost_version.h"
#endif
#ifndef GHOST_HAS_H
    #include "ghost/core/ghost_has.h"
#endif

#endif
