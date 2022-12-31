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

#ifndef GHOST_AUTO_CAST_H_INCLUDED
#define GHOST_AUTO_CAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_auto_cast(x) x
 *
 * Allows the given void pointer expression to be implicitly cast to a pointer
 * of any type.
 *
 * In C, implicit void pointer casts are always allowed so this does nothing.
 *
 * In C++, implicit void pointer casts are not allowed. This macro wraps the
 * void pointer in an instance of a class with an overloaded templated cast
 * operator, thereby allowing an implicit cast to happen.
 *
 * Note that using implicit void pointer casts in C causes -Wc++-compat
 * warnings under GCC/Clang. This does not (and cannot) silence such warnings.
 * If you want to use implicit void pointer casts in both C and C++ you should
 * probably not enable this warning.
 *
 * The main purpose of this is to wrap functions like ghost_malloc() or
 * ghost_vvec_at() to make them usable in C++ without casts. These functions
 * return void* but, unlike normal malloc(), you don't need to cast the return
 * value of these expressions in C++ because they wrap their return values in
 * ghost_auto_cast().
 *
 * Example:
 *
 *     foo_t* foo = ghost_malloc(sizeof(foo_t)); // no cast; legal in both C and C++
 *
 * You can use this to make your own functions implicitly cast void* the same
 * way. For example:
 *
 *     static inline void* foo_context(foo_t* foo) {
 *         return foo->context;
 *     }
 *     #define foo_context(x) ghost_auto_cast(foo_context(x))
 *
 * This can also be used to automatically cast user contexts in callback
 * functions. In C you would typically receive a callback like this:
 *
 *     void bar_callback(void* context) {
 *         bar_t* bar = context;
 *         // ...
 *     }
 *
 * Unfortunately this does not compile as C++. If you don't care about C++, you
 * don't need to worry about this of course. But there are many reasons you may
 * want to your code to compile as C++, in which case you need to work around
 * this problem.
 *
 * You could use a C-style cast, making it legal in both C and C++:
 *
 *     void bar_callback(void* context) {
 *         bar_t* bar = (bar_t*)context;
 *         // ...
 *     }
 *
 * Unfortunately this has a few problems. One is that you need to repeat the
 * type name. Another is that if warning flags or static analysis are turned
 * up you'll get warnings about not using static_cast<>().
 *
 * Instead you can do this:
 *
 *     void bar_callback(void* context) {
 *         bar_t* bar = ghost_auto_cast(context);
 *         // ...
 *     }
 *
 * This compiles cleanly in both C and C++ (as long as you aren't enabling
 * -Wc++-compat.)
 *
 * If you are uncomfortable with this magic being allowed in C++, you can
 * override this to disable the auto-casting behaviour. Simply pre-define it to
 * a no-op:
 *
 *     #define ghost_auto_cast(x) (x)
 *
 * This will prevent any auto-casting in C++. Ghost always casts void pointers
 * manually so it should compile this way without problems, but if you have
 * source dependencies that use Ghost, such an override might break them.
 *
 * TODO add unit test variant for the above override
 */
#endif

#ifndef ghost_has_ghost_auto_cast
    #ifdef ghost_auto_cast
        #define ghost_has_ghost_auto_cast 1
    #endif
#endif

/*
 * In C++ we use a wrapper class with a templated cast operator.
 *
 * See "Punching a hole in the type system":
 *
 *     https://www.scs.stanford.edu/~dm/home/papers/c++-new.html
 *
 * We make the constructor templated to ensure it is only used on void*, not
 * any other typed pointer. If you're getting an error like this:
 *
 *     error: inline function ‘ghost_impl_auto_cast_cxx::ghost_impl_auto_cast_cxx(ghost_impl_v_T)’ used but never defined
 *
 * It means you're trying to use ghost_auto_cast() on something that isn't a
 * void pointer.
 *
 * We also allow comparisons against nullptr and NULL. This way you can for
 * example call find() on a void pointer container and compare the return value
 * to null to check whether it exists in the container.
 */
#ifndef ghost_has_ghost_auto_cast
    #ifdef __cplusplus
        #include "ghost/language/ghost_always_inline.h"
        #include "ghost/impl/ghost_impl_function_wrapper.h"
        #include "ghost/language/ghost_cplusplus.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/language/ghost_discard.h"
        #include "ghost/debug/ghost_ensure.h"
        #include "ghost/detect/ghost_gcc.h"
        GHOST_IMPL_CXX_FUNCTION_OPEN

        struct ghost_impl_auto_cast_cxx {
            template <class ghost_impl_v_T>
            ghost_always_inline
            explicit
            ghost_impl_auto_cast_cxx(ghost_impl_v_T ghost_impl_v_p_arg);

            template <class ghost_impl_v_T>
            ghost_always_inline
            operator ghost_impl_v_T* () {
                return static_cast<ghost_impl_v_T*>(ghost_impl_v_p);
            }

            #if ghost_cplusplus >= 201103L
                /* weird bug in GCC 6 and 7, it thinks the nullptr_t parameter is not used */
                #if GHOST_GCC
                    #if __GNUC__ >= 6 && __GNUC__ <= 7
                        #pragma GCC diagnostic push
                        #pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
                    #endif
                #endif

                /* Allow comparisons against nullptr */
                ghost_always_inline
                bool operator==(decltype(nullptr) ghost_impl_v_n) {
                    return ghost_impl_v_p == ghost_impl_v_n;
                }

                #if GHOST_GCC
                    #if __GNUC__ >= 6 && __GNUC__ <= 7
                        #pragma GCC diagnostic pop
                    #endif
                #endif
            #endif

            /* Allow comparisons against literal zero (i.e. C++98 NULL) */
            ghost_always_inline
            bool operator==(int ghost_impl_v_n) {
                #if ghost_has(ghost_ensure)
                    ghost_ensure(ghost_impl_v_n == 0, "cannot compare auto-cast pointer against non-zero int");
                #else
                    ghost_discard(ghost_impl_v_n);
                #endif
                return ghost_impl_v_p == ghost_null;
            }

        private:
            void* ghost_impl_v_p;
        };

        template <>
        ghost_always_inline
        ghost_impl_auto_cast_cxx::ghost_impl_auto_cast_cxx(void* ghost_impl_v_p_arg)
            : ghost_impl_v_p(ghost_impl_v_p_arg)
        {}

        GHOST_IMPL_CXX_FUNCTION_CLOSE

        #define ghost_auto_cast(x) ghost_impl_auto_cast_cxx(x)
        #define ghost_has_ghost_auto_cast 1
    #endif
#endif

/*
 * In C, implicit void* casts are allowed so this does nothing.
 */

/*
 * To help ensure that this is only used in cases where it will compile in C++,
 * we try to test that the given expression is actually a void pointer.
 *
 * This is apparently buggy on NVIDIA/PGI; it warns that variables used in
 * generics are not used. We just disable it.
 *
 * It is also buggy on PCC. It considers void* and const void* the same type.
 */
#ifndef ghost_has_ghost_auto_cast
    #if !defined(__PGI) && !defined(__PCC__)
        #include "ghost/language/ghost_generic.h"
        #if ghost_has(ghost_generic)
            #define ghost_auto_cast(x) \
                ghost_generic((x), \
                    void*: (x), \
                    const void*: (x))
        #else
            #define ghost_auto_cast(x) (x)
        #endif
        #define ghost_has_ghost_auto_cast 1
    #endif
#endif

/* Otherwise this is a no-op. */
#ifndef ghost_has_ghost_auto_cast
    #define ghost_auto_cast(x) (x)
    #define ghost_has_ghost_auto_cast 1
#endif

#endif
