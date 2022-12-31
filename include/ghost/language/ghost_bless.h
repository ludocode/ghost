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

#ifndef GHOST_BLESS_H_INCLUDED
#define GHOST_BLESS_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_bless(Type, count, pointer) (Type*)pointer
 *
 * Starts the lifetime of an array of count objects pointed to by the given
 * pointer as the given type, returning a pointer to them.
 *
 * In C, this is just a plain cast. The count is evaluated but ignored.
 *
 * In C++, this is a form of void pointer cast used to explicitly "create"
 * objects in otherwise untyped memory. (Not run constructors, or do anything
 * actually useful; just "create" the object, telling the compiler to allow it
 * to exist.) Casting the return value of malloc() to an object in C++ is only
 * valid specifically for malloc() and friends. If you use an alternate C-style
 * allocator or implement your own, a simple cast is technically undefined
 * behaviour because the memory doesn't "exist" as that type (and it may even
 * have previously "existed" as a different type, which would otherwise violate
 * strict aliasing.) ghost_bless() is used to eliminate the undefined
 * behaviour.
 *
 * To use this for a single object, pass 1 as the count.
 *
 * @warning Beware the restrictions regarding commas in macro parameters. A
 *          type like std::pair<int,float> cannot be passed to a macro because
 *          the preprocessor will interpret it as two macro arguments; it only
 *          considers parentheses for nesting commas, not angle brackets or
 *          braces. To work around this, use a `typedef` or `using` declaration
 *          to create a type alias without commas.
 */
#endif

#ifndef ghost_has_ghost_bless
    #ifdef ghost_bless
        #define ghost_has_ghost_bless 1
    #endif
#endif

/*
 * To make a cast valid, we have to create an array of char in the returned
 * memory using placement new. This doesn't actually do anything, except by
 * rule 1 of implicit object creation, it subsequently allows the implicit
 * creation of objects within the array. This allows us to cast it to an
 * object, which then makes the object "exist". See P0593R6:
 *
 *     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p0593r6.html
 */
#ifndef ghost_has_ghost_bless
    #ifdef __cplusplus
        /* It's not entirely clear how placement new interacts with null. My
         * concern is that the compiler will assume the return value of
         * placement new is non-null and eliminate null-pointer checks after
         * it. Just in case, we check that the pointer is non-null before
         * running placement new. This should all optimize to nothing... right? */
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include <new> /* TODO wrap this in ghost/header/? is it required for placement new? */
        GHOST_IMPL_CXX_FUNCTION_OPEN
        template <typename ghost_impl_v_T>
        ghost_always_inline
        ghost_impl_v_T* ghost_bless_impl(ghost_size_t ghost_impl_v_n, void* ghost_impl_v_p) {
            if (ghost_impl_v_p)
                new (ghost_impl_v_p) char[ghost_impl_v_n * sizeof(ghost_impl_v_T)];
            return static_cast<ghost_impl_v_T*>(ghost_impl_v_p);
        }
        GHOST_IMPL_CXX_FUNCTION_CLOSE
        #define ghost_bless(T, n, p) ghost_bless_impl<T>(n, p)
        #define ghost_has_ghost_bless 1
    #endif
#endif

#ifndef ghost_has_ghost_bless
    #include "ghost/language/ghost_discard.h"
    #define ghost_bless(T, n, p) (ghost_discard(n), ((T*)(p)))
    #define ghost_has_ghost_bless 1
#endif

#endif
