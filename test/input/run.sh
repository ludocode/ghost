#!/bin/bash
set -e
cd "$(dirname "$0")"
CC=${CC:-cc}
$CC -I../../include -Wall -Wextra -Wpedantic *.c -o test_ghost_input
./test_ghost_input
