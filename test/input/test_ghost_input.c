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

#include <stdio.h>

#include "ghost/io/ghost_is_input_echo.h"
#include "ghost/io/ghost_is_input_echo_ex.h"
#include "ghost/io/ghost_isatty.h"
#include "ghost/io/ghost_fileno.h"
#include "ghost/io/ghost_set_input_echo.h"
#include "ghost/io/ghost_set_input_echo_ex.h"
#include "ghost/debug/ghost_ensure.h"
#include "ghost/format/ghost_format_z.h"

static void test_isatty(void) {
    puts("Testing ghost_isatty()");
    printf("ghost_isatty(): %s\n\n", ghost_isatty(ghost_fileno(stdin)) ? "true" : "false");
}

static void test_ghost_input_echo(void) {
    char username[256];
    char password[256];
    char email[256];
    ghost_bool error;

    puts("Testing ghost_set_input_echo()");
    if (!ghost_isatty(ghost_fileno(stdin))) {
        puts("ERROR: Cannot test ghost_set_input_echo() because isatty(stdin) is false.");
        exit(EXIT_FAILURE);
    }

    puts("Enter credentials:");

    fputs("    Username: ", stdout);
    fflush(stdout);
    fgets(username, sizeof(username), stdin);

    ghost_set_input_echo(false);
    fputs("    Password: ", stdout);
    fflush(stdout);
    fgets(password, sizeof(password), stdin);
    putc('\n', stdout);

    // make sure echo reports off
    ghost_ensure(!ghost_is_input_echo());

    // test turning echo back on, checking for errors this time
    error = true;
    ghost_set_input_echo_ex(true, &error);
    ghost_ensure(!error);
    fputs("    Email: ", stdout);
    fflush(stdout);
    fgets(email, sizeof(email), stdin);

    // make sure echo reports on, checking for errors again
    error = true;
    ghost_ensure(ghost_is_input_echo_ex(&error));
    ghost_ensure(!error);

    // print the credentials back
    // (note that we don't bother trimming the line feeds on the end)
    printf("Received credentials:\n");
    printf("    Username: %s", username);
    // don't echo the password just in case someone entered their real password...
    printf("    Password: <%" GHOST_PRIdZ " bytes>\n", strlen(password));
    printf("    Email: %s", email);
    putc('\n', stdout);
}

int main(void) {
    putc('\n', stdout);

    test_isatty();
    test_ghost_input_echo();

    puts("Done.\n");
}
