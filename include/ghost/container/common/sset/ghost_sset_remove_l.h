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

#ifndef GHOST_SSET_REMOVE_L_H_INCLUDED
#define GHOST_SSET_REMOVE_L_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Removes the string with the given length from the given set of strings if it
 * exists in the set.
 *
 * The copy contained in the set is freed.
 *
 * If the string is already in the set, the set is not changed and false is
 * returned.
 *
 * @return True if the string was removed, or false if the string was not in
 *         the set
 */
bool ghost_sset_remove_l(ghost_sset_t* set, const char* string, size_t length);
#endif

#ifndef ghost_has_ghost_sset_remove_l
    #ifdef ghost_sset_remove_l
        #define ghost_has_ghost_sset_remove_l 1
    #endif
#endif

#ifndef ghost_has_ghost_sset_remove_l
    #include "ghost/container/common/sset/ghost_sset_t.h"
    #if !ghost_has(ghost_sset_t)
        #define ghost_has_ghost_sset_remove_l 0
    #endif
#endif

#ifndef ghost_has_ghost_sset_remove_l
    #include "ghost/container/common/sset/ghost_sset_find_l.h"
    #include "ghost/container/common/sset/ghost_sset_remove_it.h"
    #include "ghost/type/bool/ghost_bool.h"
    #include "ghost/type/bool/ghost_true.h"
    #include "ghost/type/bool/ghost_false.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/language/ghost_null.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    ghost_bool ghost_sset_remove_l(ghost_sset_t* set, const char* string, size_t length) GHOST_IMPL_DEF({
        ghost_sset_it_t it = ghost_sset_find_l(set, string, length);
        if (it == ghost_null)
            return ghost_false;
        ghost_sset_remove_it(set, it);
        return ghost_true;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_sset_remove_l 1
#endif

#endif
