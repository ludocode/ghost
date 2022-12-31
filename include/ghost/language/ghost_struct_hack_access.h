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

#ifndef GHOST_STRUCT_HACK_ACCESS_H_INCLUDED
#define GHOST_STRUCT_HACK_ACCESS_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_struct_hack_access(pointer_to_struct, flexible_member_name, flexible_member_type)
 *
 * This is used to access the flexible array member of a struct that was
 * declared with GHOST_STRUCT_HACK.
 *
 * In language standards that don't support flexible array members (like C++),
 * static analysis tools may give spurious out-of-bounds warnings since they
 * may not recognize the struct hack. This access wrapper silences these
 * out-of-bounds warnings.
 *
 * You can of course ignore this and access the array directly if you don't get
 * these warnings.
 *
 * You must pass the name and type of the flexible array member. See the
 * example in GHOST_STRUCT_HACK.
 *
 * @see GHOST_STRUCT_HACK
 */
#endif

#ifndef ghost_has_ghost_struct_hack_access
    #ifdef ghost_struct_hack_access
        #define ghost_has_ghost_struct_hack_access 1
    #endif
#endif

#ifndef ghost_has_ghost_struct_hack_access
    /* TODO this is not implemented yet */
    #if 0
    #include "ghost/language/ghost_offsetof.h"
    #define ghost_struct_hack_access(pointer_to_struct, flexible_member_name, flexible_member_type)
    #define ghost_has_ghost_struct_hack_access 1
    #endif
#endif

#ifndef ghost_has_ghost_struct_hack_access
    #define ghost_has_ghost_struct_hack_access 0
#endif

#endif
