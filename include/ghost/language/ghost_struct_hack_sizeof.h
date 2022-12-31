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

#ifndef GHOST_STRUCT_HACK_SIZEOF_H_INCLUDED
#define GHOST_STRUCT_HACK_SIZEOF_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_struct_hack_sizeof(struct_name, flexible_member_name, flexible_member_count) offsetof(struct_name, flexible_member_name[flexible_member_count])
 *
 * This is used to determine the size of a struct that was declared with
 * GHOST_STRUCT_HACK.
 *
 * You must pass the name of the struct, the name of the flexible array member
 * and the number of elements you wish to allocate for it. See the example in
 * GHOST_STRUCT_HACK.
 *
 * @see GHOST_STRUCT_HACK
 */
#endif

#ifndef ghost_has_ghost_struct_hack_sizeof
    #ifdef ghost_struct_hack_sizeof
        #define ghost_has_ghost_struct_hack_sizeof 1
    #endif
#endif

/*
 * sizeof() excludes flexible array members in C99 but includes padding leading
 * up to it. Compilers that support a size of 0 as an extension probably behave
 * the same way.
 *
 * Nevertheless, we always use offsetof() instead of sizeof() to determine the
 * size of the struct. This is to prevent writing code that works with sizeof()
 * under C99 but fails to work when this falls back to offsetof() under other
 * language standards. This could happen for example if the flexible member
 * name is misspelled, or if an expression that evaluates to the struct type is
 * used instead of the struct name.
 *
 * This also means we don't need to bother checking here whether flexible array
 * members are supported. In effect ghost_struct_hack_sizeof() is just an alias
 * of ghost_offsetof(). You can of course just use ghost_offsetof() directly if
 * you want but using this instead makes the code a lot more clear.
 *
 * TODO no, we should probably just use sizeof(), especially if we add a
 * ghost_struct_hack_access() macro. if you're not actually testing your code
 * on non-C99 compilers then you shouldn't be using this anyway, just use
 * flexible array members directly
 */
#ifndef ghost_has_ghost_struct_hack_sizeof
    #include "ghost/language/ghost_offsetof.h"
    #define ghost_struct_hack_sizeof(struct_name, member_name, count) \
        ghost_offsetof(struct_name, member_name[count])
    #define ghost_has_ghost_struct_hack_sizeof 1
#endif

#endif
