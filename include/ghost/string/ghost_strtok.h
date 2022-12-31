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

#ifndef GHOST_STRTOK_H_INCLUDED
#define GHOST_STRTOK_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 */
char* ghost_strtok(char* restrict string, const char* restrict delimiters);
#endif

#ifndef ghost_has_ghost_strtok
    #ifdef ghost_strtok
        #define ghost_has_ghost_strtok 1
    #endif
#endif

/* If we're hosted, use the standard C library function. */
#ifndef ghost_has_ghost_strtok
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include "ghost/header/c/ghost_string_h.h"
        #if ghost_has_ghost_string_h
            #define ghost_strtok strtok
            #define ghost_has_ghost_strtok 1
        #endif
    #endif
#endif

/*
 * We implement this only if we have selectany variables or we are manually
 * emitting inlines.
 *
 * strtok() could (in theory) be called with shared state between different
 * translation units. If we don't properly share the state, wrong results will
 * be returned. Even though such usage is unlikely, we don't want to risk
 * incorrect behaviour.
 *
 * We don't bother trying to make the state thread-local. Using strtok()
 * concurrently from multiple threads is forbidden even on modern libcs like
 * glibc. Besides, if you don't have a libc, you probably don't have
 * conventional threads either.
 *
 * Consider porting code to strtok_r() instead. Converting code from strtok()
 * to strtok_r() is trivial, and if you're using Ghost, ghost_strtok_r() is
 * guaranteeed to exist on all platforms.
 */
/* TODO test this */
#ifndef ghost_has_ghost_strtok
    #include "ghost/language/ghost_selectany_var.h"
    #include "ghost/impl/ghost_impl_defs.h"
    #if ghost_has(ghost_selectany_var) || GHOST_MANUAL_DEFS
        #include "ghost/impl/ghost_impl_always_inline.h"
        GHOST_IMPL_FUNCTION_OPEN

        /* The global state. It's defined inside GHOST_IMPL_FUNCTION_OPEN so
         * that it has hidden visibility. */
        #if ghost_has(ghost_selectany_var)
            ghost_selectany_var
        #elif !GHOST_EMIT_DEFS
            extern
        #endif
        char** ghost_impl_strtok_state;

        #include "ghost/language/ghost_restrict.h"
        #include "ghost/string/ghost_strtok_r.h"
        #include "ghost/language/ghost_null.h"
        ghost_impl_always_inline
        char* ghost_strtok(char* ghost_restrict string, const char* ghost_restrict delimiters) {
            return ghost_strtok_r(string, delimiters, ghost_impl_strtok_state);
        }

        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_strtok 1
    #endif
#endif

#ifndef ghost_has_ghost_strtok
    #define ghost_has_ghost_strtok 0
#endif

#endif
