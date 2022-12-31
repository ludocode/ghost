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

#ifndef GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS_H_INCLUDED
#define GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS
 *
 * Silences warnings about functions defined without a previous declaration.
 *
 * This warning is typically used to find non-static function definitions that
 * were not declared in a header file. The fix is usually to make it static (if
 * the function is private to the current translation unit) or declare it in a
 * header (if it's public.)
 *
 * One valid reason to silence this warning is to define non-inline weak
 * functions in header-only libraries. Another reason to silence it is that
 * some older compilers (e.g. GCC versions before 5.1) emitted this warning
 * erroneously on non-static inline functions in C:
 *
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=54113
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63877
 *
 * @see GHOST_SILENCE_MISSING_DECLARATIONS
 * @see GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS
    #ifdef GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS
        #define ghost_has_GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS 1
    #endif
#endif

/* GCC/Clang -Wmissing-prototypes -Wmissing-declarations */
#ifndef ghost_has_GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS
    #if defined(__GNUC__) && !defined(__CPARSER__)
        /* _Pragma GCC diagnostic is supported since GCC 4.2 */
        #if defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
            /* In C we need to silence both -Wmissing-declarations and
             * -Wmissing-prototypes. These warnings are used to ensure that full
             * prototypes exist in header files for all C functions.
             * GCC does not accept -Wmissing-prototypes in C++ but Clang does. */
            #if defined(__cplusplus) && !defined(__clang__)
                #define GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS \
                        _Pragma("GCC diagnostic ignored \"-Wmissing-declarations\"")
            #else
                #define GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS \
                        _Pragma("GCC diagnostic ignored \"-Wmissing-declarations\"") \
                        _Pragma("GCC diagnostic ignored \"-Wmissing-prototypes\"")
            #endif
            #define ghost_has_GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS 1
        #endif
    #endif
#endif

/* MSVC doesn't appear to have any such warning. */

#ifndef ghost_has_GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS
    #define GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS /*nothing*/
    #define ghost_has_GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS 1
#endif

#endif
