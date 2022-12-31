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

#ifndef GHOST_CONST_CAST_H_INCLUDED
#define GHOST_CONST_CAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * @def ghost_const_cast(Type, value) (Type)(value)
 *
 * Casts value to Type, removing any const qualifier.
 *
 * Unlike C++ const_cast<>(), this must not be used to cast away volatile.
 *
 * @see ghost_cast
 * @see ghost_static_cast
 * @see ghost_reinterpret_cast
 */
#endif

#ifndef ghost_has_ghost_const_cast
    #ifdef ghost_const_cast
        #define ghost_has_ghost_const_cast 1
    #endif
#endif

/* C++ */
#ifndef ghost_has_ghost_const_cast
    #ifdef __cplusplus
        #define ghost_const_cast(Type, value) (const_cast<Type>(value))
        #define ghost_has_ghost_const_cast 1
    #endif
#endif

/*
 * There isn't really a sane way to cast that avoids -Wcast-qual
 * warnings in C.
 *
 * We do it by casting through a uintptr_t. We cast through void*
 * before and after to ensure both the source and destination types are
 * pointers (and to handle the technically allowed case of typed
 * pointers having a different representation than void*.)
 *
 * If we have compiler support for checking types, we verify that the types are
 * the same. Otherwise, we don't check, which means this may be able to convert
 * any pointer type to any other pointer type (though compilers may warn if
 * casting away volatile.) This makes it a bit more powerful than you might
 * expect, but it's not really much more powerful than a naked pointer cast
 * anyway.
 *
 * Note that this doesn't cast through volatile because we don't want
 * to add volatile if it doesn't already have it. This means it can't
 * cast away volatile without triggering a -Wcast-qual warning. I'm not
 * sure how to handle this yet. We could just cast straight to
 * uintptr_t without the first cast to const void* but this would allow
 * ghost_const_cast() to cast ints (and even floats!) to pointers.
 * Maybe the best option is to add a separate ghost_volatile_cast().
 */

/*
 * TODO we may need to pull out __builtin_types_compatible_p into e.g.
 * ghost_types_compatible() in order to support more compilers or to disable it
 * on old GCC versions. It may also be possible to emulate it with _Generic:
 *     https://github.com/exebook/generic-print/issues/2#issuecomment-786065600
 * We may need to add const to Type below in the check if doing this
 *
 * #define ghost_types_compatible(T, U) _Generic(ghost_compound_literal(T), U: 1, default: 0)
 *
 * also in C++ std::is_same<T, U>::value in <type_traits>
 *
 * maybe call it ghost_types_match() because these latter two will probably require constness to match
 */

#ifndef ghost_has_ghost_const_cast
    #ifdef __GNUC__
        #include "ghost/debug/ghost_static_assert_expr.h"
        #include "ghost/type/uintptr_t/ghost_uintptr_t.h"
        #include "ghost/language/ghost_typeof.h"
        #if ghost_has(ghost_typeof)
            /* TODO make this work */
            #define ghost_const_cast(Type, value) ( \
                    /*ghost_static_assert_expr(__builtin_types_compatible_p(const Type, ghost_typeof(value))),*/ \
                    (Type)(void*)(ghost_uintptr_t)(const void*)(value) \
                )
            #define ghost_has_ghost_const_cast 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_const_cast
    #include "ghost/type/uintptr_t/ghost_uintptr_t.h"
    #define ghost_const_cast(Type, value) ((Type)(void*)(ghost_uintptr_t)(const void*)(value))
    #define ghost_has_ghost_const_cast 1
#endif

#endif
