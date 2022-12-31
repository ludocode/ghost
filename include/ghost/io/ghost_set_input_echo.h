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

#ifndef GHOST_SET_INPUT_ECHO_H_INCLUDED
#define GHOST_SET_INPUT_ECHO_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Sets whether standard input will echo entered characters.
 *
 * Use this to disable echo when prompting the user for a password or when
 * otherwise making a simple text-based user interface.
 *
 * If you want to restore the previous echo state afterwards, call
 * ghost_is_input_echo() first.
 *
 * If any error occurs, Ghost will abort the program (via ghost_fatal().) Call
 * ghost_set_input_echo_ex() if you want to handle errors yourself.
 *
 * Such errors may occur if standard input is not a tty. You can check whether
 * `ghost_isatty(ghost_fileno(stdin))` returns true to determine if it's a tty.
 *
 * @param enabled Whether echo should be enabled
 * @param error Will be set to true if an error occurred, false otherwise; or
 *              aborts on error if null
 *
 * @see ghost_set_input_echo_ex()
 * @see ghost_is_input_echo()
 * @see ghost_fatal()
 */
void ghost_set_input_echo(bool enabled, bool* /*nullable*/ error);
#endif

#ifndef ghost_has_ghost_set_input_echo
    #ifdef ghost_set_input_echo
        #define ghost_has_ghost_set_input_echo 1
    #endif
#endif

/* We just wrap ghost_set_input_echo_ex() and pass NULL as the error flag. It
 * will abort on error. */
#ifndef ghost_has_ghost_set_input_echo
    #include "ghost/io/ghost_set_input_echo_ex.h"
    #if ghost_has(ghost_set_input_echo_ex)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/type/bool/ghost_bool.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_set_input_echo(ghost_bool ghost_impl_v_enabled) {
            ghost_set_input_echo_ex(ghost_impl_v_enabled, ghost_null);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_set_input_echo 1
    #endif
#endif

#ifndef ghost_has_ghost_set_input_echo
    #define ghost_has_ghost_set_input_echo 0
#endif

#endif
