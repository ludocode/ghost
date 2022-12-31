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

#ifndef GHOST_REMOVE_QUALS_H_INCLUDED
#define GHOST_REMOVE_QUALS_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * ghost_remove_quals(T) -- Remove qualifiers from a type
 *
 * This is similar to typeof except it removes qualifiers from a type, in
 * particular const and volatile. This can be used anywhere a type name is
 * expected.
 *
 * In C this also removes restrict and _Atomic. This behaviour is not
 * (currently) portable to C++.
 *
 * This is a compiler extension that is not (yet) available in standard C.
 * Check `ghost_has(ghost_remove_quals)` to see if this is implemented.
 */
#endif

#ifndef ghost_has_ghost_remove_quals
    #ifdef ghost_remove_quals
        #define ghost_has_ghost_remove_quals 1
    #endif
#endif

/* This whole feature is experimental. We want to match the C23 name but C23 is
 * not ready yet, and in the meantime it may get renamed to something like
 * typeof_unqual or even removed entirely. */
/*TODO move to experimental/ */
#ifndef ghost_has_ghost_remove_quals
    #if GHOST_EXPERIMENTAL
        #define ghost_has_ghost_remove_quals 0
    #endif
#endif

/* C23 will have remove_quals() as a keyword. */
#ifndef ghost_has_ghost_remove_quals
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
            #define ghost_remove_quals(T) remove_quals(T)
            #define ghost_has_ghost_remove_quals 1
        #endif
    #endif
#endif

/* C++11 has decltype(). We wrap it to remove cv-qualifiers. We also remove
 * references; see ghost_typeof() for details. */
#ifndef ghost_has_ghost_remove_quals
    #ifdef __cplusplus
        #if __cplusplus >= 201103L
            #include "ghost/header/cxx/ghost_cxx_type_traits_h.h"
            #if ghost_has(ghost_cxx_type_traits_h)
                /*
                 * https://en.cppreference.com/w/cpp/language/decltype
                 * https://en.cppreference.com/w/cpp/types/remove_reference
                 * https://en.cppreference.com/w/cpp/types/remove_cv
                 */
                #define ghost_remove_quals(T) \
                        std::remove_cv<std::remove_reference<decltype(T)>::type>::type
                #define ghost_has_ghost_remove_quals 1
            #endif
        #endif
    #endif
#endif

/* Otherwise we don't have support for ghost_remove_quals(). */
#ifndef ghost_has_ghost_remove_quals
    #define ghost_has_ghost_remove_quals 0
#endif

#endif
