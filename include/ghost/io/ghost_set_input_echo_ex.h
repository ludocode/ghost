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

#ifndef GHOST_SET_INPUT_ECHO_EX_H_INCLUDED
#define GHOST_SET_INPUT_ECHO_EX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Sets whether standard input will echo entered characters.
 *
 * Use this to disable echo when prompting the user for a password or when
 * otherwise making a simple text-based user interface.
 *
 * If any error occurs, true will be stored in the error flag passed to the
 * error parameter; otherwise false will be stored. Check this flag to
 * determine whether an error occurred. Alternatively, you can pass null as
 * this flag (or call ghost_set_input_echo() instead), in which case Ghost will
 * abort the program (via ghost_fatal()) if any error occurs.
 *
 * Such errors may occur if standard input is not a tty. You can check whether
 * `ghost_isatty(ghost_fileno(stdin))` returns true to determine if it's a tty.
 *
 * If you want to restore the previous echo state afterwards, call
 * ghost_is_input_echo_ex() first.
 *
 * @param enabled Whether echo should be enabled
 * @param error Will be set to true if an error occurred, false otherwise; or
 *              aborts on error if null
 *
 * @see ghost_set_input_echo()
 * @see ghost_is_input_echo_ex()
 * @see ghost_fatal()
 */
void ghost_set_input_echo_ex(bool enabled, bool* /*nullable*/ error);
#endif

#ifndef ghost_has_ghost_set_input_echo_ex
    #ifdef ghost_set_input_echo_ex
        #define ghost_has_ghost_set_input_echo_ex 1
    #endif
#endif

/* Windows */
#ifndef ghost_has_ghost_set_input_echo_ex
    #ifdef _WIN32
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/header/windows/ghost_windows_h.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/type/bool/ghost_false.h"
        #include "ghost/type/bool/ghost_true.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/language/ghost_expect_false.h"
        #include "ghost/debug/ghost_fatal.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_function
        void ghost_set_input_echo_ex(ghost_bool ghost_impl_v_enabled, ghost_bool* ghost_impl_v_error) GHOST_IMPL_DEF({
            DWORD ghost_impl_v_mode = 0;
            HANDLE ghost_impl_v_handle = GetStdHandle(STD_INPUT_HANDLE);

            if (ghost_expect_false(0 == GetConsoleMode(ghost_impl_v_handle, &ghost_impl_v_mode))) {
                if (ghost_impl_v_error == ghost_null) {
                    ghost_fatal("Failed to GetConsoleMode() on STD_INPUT_HANDLE");
                }
                *ghost_impl_v_error = ghost_true;
                return;
            }

            if (ghost_impl_v_enabled) {
                ghost_impl_v_mode |= ENABLE_ECHO_INPUT;
            } else {
                ghost_impl_v_mode &= ~ENABLE_ECHO_INPUT;
            }

            if (ghost_expect_false(0 == SetConsoleMode(ghost_impl_v_handle, ghost_impl_v_mode))) {
                if (ghost_impl_v_error == ghost_null) {
                    ghost_fatal("Failed to SetConsoleMode() on STD_INPUT_HANDLE");
                }
                *ghost_impl_v_error = ghost_true;
                return;
            }

            if (ghost_impl_v_error != ghost_null) {
                *ghost_impl_v_error = ghost_false;
            }
        })
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_set_input_echo_ex 1
    #endif
#endif

/* POSIX */
#ifndef ghost_has_ghost_set_input_echo_ex
    #include "ghost/header/posix/ghost_unistd_h.h"
    #include "ghost/header/posix/ghost_termios_h.h"
    #include "ghost/io/ghost_fileno.h"
    #if ghost_has(ghost_unistd_h) && ghost_has(ghost_termios_h) && ghost_has(ghost_fileno)
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/type/bool/ghost_false.h"
        #include "ghost/type/bool/ghost_true.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/language/ghost_expect_false.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/debug/ghost_fatal.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_function
        void ghost_set_input_echo_ex(ghost_bool ghost_impl_v_enabled, ghost_bool* ghost_impl_v_error) GHOST_IMPL_DEF({
            struct termios ghost_impl_v_state;
            int ghost_impl_v_fd = ghost_fileno(stdin);

            if (ghost_expect_false(0 != tcgetattr(ghost_impl_v_fd, &ghost_impl_v_state))) {
                if (ghost_impl_v_error == ghost_null) {
                    ghost_fatal("Failed to tcgetattr() on stdin");
                }
                *ghost_impl_v_error = ghost_true;
                return;
            }

            if (ghost_impl_v_enabled) {
                ghost_impl_v_state.c_lflag |= ECHO;
            } else {
                ghost_impl_v_state.c_lflag &= ~ghost_static_cast(unsigned int, ECHO);
            }

            if (ghost_expect_false(0 != tcsetattr(ghost_impl_v_fd, TCSAFLUSH, &ghost_impl_v_state))) {
                if (ghost_impl_v_error == ghost_null) {
                    ghost_fatal("Failed to tcsetattr() on stdin");
                }
                *ghost_impl_v_error = ghost_true;
                return;
            }

            if (ghost_impl_v_error != ghost_null) {
                *ghost_impl_v_error = ghost_false;
            }
        })
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_set_input_echo_ex 1
    #endif
#endif

#ifndef ghost_has_ghost_set_input_echo_ex
    #define ghost_has_ghost_set_input_echo_ex 0
#endif

#endif
