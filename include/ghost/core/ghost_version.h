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

#ifndef GHOST_VERSION_H_INCLUDED
#define GHOST_VERSION_H_INCLUDED

/* TODO move this up to ghost/ghost_version.h, don't include ghost_core in it,
 * should be the only header that doesn't */
#include "ghost/ghost_core.h"

/**
 * @def GHOST_VERSION
 *
 * A monotonically increasing integer that identifies the current version of
 * Ghost.
 *
 * This is intended for source libraries that have a dependency on Ghost and
 * need to verify that the version provided by their users is new enough.
 *
 * Ghost doesn't do releases yet so, for now, the version number does not
 * correspond to any release. It will simply be bumped sporadically as new
 * features and bug fixes are added to Ghost.
 *
 * Ghost is fairly experimental at the moment, but I eventually want to get it
 * into a stable enough state to be a "live-at-head" library. If you are
 * writing an app or shared library, your copy of Ghost can live at head (i.e.
 * always use the latest master), or you can freeze it to a specific commit. If
 * you freeze it, at least ensure that your copy of Ghost is newer (as in
 * commit date) than any of your other libraries that use it. Either way this
 * version number is not likely to be useful to you because you already control
 * your version of Ghost.
 *
 * If you are writing a library that has a dependency on Ghost (required or
 * optional), you'll need a way to check whether Ghost has a certain include
 * file or supports a particular platform feature you depend on. That's what
 * this version number is for.
 *
 * In the simplest case, you can just check the version and #error if it's not
 * new enough. Alternatively, your library can instead switch to an amalgamated
 * version of Ghost that has the features you want. See docs/amalgamate.md to
 * learn how to make your dependency on Ghost optional.
 */

#if defined(GHOST_VERSION) || defined(ghost_has_GHOST_VERSION)
    #error "GHOST_VERSION cannot be overridden."
#endif

#define GHOST_VERSION 1
#define ghost_has_GHOST_VERSION 1

#endif
