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

#ifndef GHOST_STATIC_INIT_H_INCLUDED
#define GHOST_STATIC_INIT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_static_init(unique_name) [[constructor]] void unique_name(void)
 *
 * Defines a block of code that will be run during static initialization.
 *
 * This occurs when a shared object is loaded by the dynamic linker, which is
 * at startup (before main()) for an executable and its dependent libraries, or
 * upon dlopen() or LoadLibrary() for a library loaded at runtime.
 *
 * The block is run at the same time as C++ constructors of objects with
 * static storage duration. The order of initialization is unspecified (even
 * for initializers in the same translation unit.)
 *
 * Use it at file scope like this:
 *
 *     ghost_static_init(my_unique_name) {
 *         // this code will run before main()
 *         foo();
 *         bar();
 *     }
 *
 * The block requires a name that must be unique to the linker and must not
 * start with an underscore. A static initializer block with a given name can
 * only appear in one translation unit.
 */
#endif

/* PCC 1.1.0 defines __GNUC__ but this seems to be buggy so we just disable it.
 * It does work in the PCC 1.2.0 development version. */
#ifndef ghost_has_ghost_static_init
    #ifdef __PCC__
        #if __PCC__ < 1 || (__PCC__ == 1 && __PCC_MINOR__ <= 1)
            #define ghost_has_ghost_static_init 0
        #endif
    #endif
#endif

/* cparser has __attribute__((__constructor__)) but it only works on non-static
 * functions.
 *     https://github.com/libfirm/cparser/issues/54 */
#ifndef ghost_has_ghost_static_init
    #ifdef __CPARSER__
        #define ghost_static_init(name) \
            __attribute__((__constructor__)) \
            void name(void)
        #define ghost_has_ghost_static_init 1
    #endif
#endif

/* GNU C, use a static function with __attribute__((__constructor__)). For ELF
 * this puts a pointer to the function in the ".init_array" section. Dynamic
 * linkers run all functions in that section upon loading a shared object. */
#ifndef ghost_has_ghost_static_init
    #ifdef __GNUC__
        #define ghost_static_init(name) \
            __attribute__((__constructor__)) \
            static void name(void)
        #define ghost_has_ghost_static_init 1
    #endif
#endif

/* TinyCC doesn't support __attribute__((constructor)) but it does support
 * __attribute__((section(".init_array"))). We can do the above manually.
 * I haven't tested other platforms so for now we limit it to Linux. */
#ifndef ghost_has_ghost_static_init
    #if defined(__TINYC__) && defined(__linux__)
        #include "ghost/preprocessor/ghost_concat.h"
        #define ghost_static_init(name) \
            static void GHOST_CONCAT(ghost_static_init_FN_, name)(void); \
            __attribute__((__section__(".init_array"))) static void (*name)(void) = \
                    &GHOST_CONCAT(ghost_static_init_FN_, name); \
            static void GHOST_CONCAT(ghost_static_init_FN_, name)(void); \
        #define ghost_has_ghost_static_init 1
    #endif
#endif

/* MSVC C, place a pointer to the function in a user initialization section
 * (.CRT$XCU), and add a linker pragma to prevent it from being stripped by
 * whole-program optimization. */
#ifndef ghost_has_ghost_static_init
    #ifdef _MSC_VER

        /* cdecl function names are mangled on MSVC on architectures where it
         * differs from stdcall (in addition to C++ name mangling.)
         *     https://devblogs.microsoft.com/oldnewthing/20150102-00/?p=43233 */
        #ifndef GHOST_IMPL_STATIC_INIT_DECORATE_CDECL
            #if defined(_M_AMD64) || defined(_M_ALPHA)
                #define GHOST_IMPL_STATIC_INIT_DECORATE_CDECL(fn) #fn
            #elif defined(_M_IX86)
                #define GHOST_IMPL_STATIC_INIT_DECORATE_CDECL(fn) "_" #fn
            #elif defined(_M_IA64)
                #define GHOST_IMPL_STATIC_INIT_DECORATE_CDECL(fn) "." #fn
            #elif defined(_M_PPC)
                #define GHOST_IMPL_STATIC_INIT_DECORATE_CDECL(fn) ".." #fn
            #endif
        #endif

        #ifdef GHOST_IMPL_STATIC_INIT_DECORATE_CDECL
            #include "ghost/language/ghost_extern_c.h"
            #include "ghost/preprocessor/ghost_concat.h"
            #define ghost_static_init(name) \
                static void __cdecl GHOST_CONCAT(ghost_static_init_FN_, name)(void); \
                __pragma(section(".CRT$XCU", read)) \
                ghost_extern_c __declspec(allocate(".CRT$XCU")) void (__cdecl *name)(void) = \
                        &GHOST_CONCAT(ghost_static_init_FN_, name); \
                __pragma(comment(linker, "/include:" GHOST_IMPL_STATIC_INIT_DECORATE_CDECL(name))) \
                static void __cdecl GHOST_CONCAT(ghost_static_init_FN_, name)(void)
            #define ghost_has_ghost_static_init 1
        #endif
    #endif
#endif

/* C++, use the constructor of a static instance of a class. */
#ifndef ghost_has_ghost_static_init
    #ifdef __cplusplus
        #include "ghost/language/ghost_hidden.h"
        #include "ghost/preprocessor/ghost_concat.h"
        #define ghost_static_init(name) \
            static ghost_hidden struct name { \
                ghost_hidden name(); \
            } GHOST_CONCAT(ghost_impl_static_init_INSTANCE_, name); \
            name::name()
        #define ghost_has_ghost_static_init 1
    #endif
#endif

/* Otherwise the compiler doesn't support a way of defining a static
 * initializer. */
#ifndef ghost_has_ghost_static_init
    #define ghost_has_ghost_static_init 0
#endif

#endif
