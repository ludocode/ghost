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

#ifndef GHOST_MEMDUP_H_INCLUDED
#define GHOST_MEMDUP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Allocates a copy of the given memory.
 */
void* ghost_memdup(const void* p, size_t size);
#endif

/* Override is handled in ghost_malloc_system.h */
#include "ghost/malloc/ghost_malloc_system.h"

/*
 * At the moment we don't bother to wrap any other memdup(). We just implement
 * our own. Some libcs or custom allocators may have a function for this
 * (in some cases called xmemdup().) Some libraries also have a function for
 * this, for example glib or OpenSSL. We could eventually let the user declare
 * that they're using these libraries (like we do with libbsd) but for now we
 * don't.
 */

#ifndef ghost_has_ghost_memdup
    #include "ghost/malloc/ghost_malloc.h"
    #if ghost_has(ghost_malloc)
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/language/ghost_expect_false.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/string/ghost_memcpy.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_auto_cast.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_malloc.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_MALLOC
        GHOST_IMPL_ATTRIB_ALLOC_SIZE((2))
        ghost_impl_function
        void* ghost_memdup(const void* p, ghost_size_t size) {
            void* ret;
            if (ghost_expect_false(p == ghost_null))
                return ghost_null;
            ret = ghost_malloc(size);
            if (ghost_expect_false(ret == ghost_null))
                return ghost_null;
            ghost_memcpy(ret, p, size);
            return ret;
        }

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_memdup(p, n) ghost_auto_cast(ghost_memdup(p, n))
        #define ghost_has_ghost_memdup 1
    #endif
#endif

#ifndef ghost_has_ghost_memdup
    #define ghost_has_ghost_memdup 0
#endif

#endif
