#!/bin/bash

# MIT No Attribution
#
# Copyright (c) 2022 Fraser Heavy Software
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

# This is just a sanity check to test how fast Ghost compiles in case anyone
# thinks it's crazy to use lots of header files.
#
# As of this writing, compiling all of Ghost in C takes much less time than
# compiling just `#include <iostream>` in C++. Compiling all of Ghost in C++
# takes much less time than compiling just `#include <boost/asio.h>` in C++.

set -e
cd "$(dirname "$0")"/..
export TIMEFORMAT='%Es'

# Generate a file that includes all public Ghost headers
echo "Generating Ghost super-header..."
BUILD=test/unit/.build
GHOST=$BUILD/ghost_everything.c
mkdir -p $(dirname "$GHOST")
rm -f $GHOST
for f in $(cd include ; find * -type f -name '*.h' | grep -v '^ghost/impl/'); do
    echo "#include \"$f\"" >> $GHOST
done
echo "Ghost has $(cat $GHOST|wc -l) public headers."

# Amalgamate it
echo -n "Amalgamating Ghost super-header... "
AMALG=$BUILD/ghost_amalgamated.c
time tools/amalgamate.py -i $GHOST -o $AMALG -p mylib > /dev/null

echo -n "Compiling \"ghost/ghost_common.h\" in C with GCC... "
time gcc -c -Iinclude -o $BUILD/ghost-common.o -xc - <<EOF
    #include "ghost/ghost_common.h"
EOF

echo -n "Compiling \"ghost/ghost_common.h\" in C++ with GCC... "
time gcc -c -Iinclude -o $BUILD/ghost-common.o -xc++ - <<EOF
    #include "ghost/ghost_common.h"
EOF

echo -n "Compiling \"ghost/ghost_common.h\" in C with Clang... "
time clang -c -Iinclude -o $BUILD/ghost-common.o -xc - <<EOF
    #include "ghost/ghost_common.h"
EOF

echo -n "Compiling \"ghost/ghost_common.h\" in C++ with Clang... "
time clang -c -Iinclude -o $BUILD/ghost-common.o -xc++ - <<EOF
    #include "ghost/ghost_common.h"
EOF

if which tcc > /dev/null; then
    echo -n "Compiling \"ghost/ghost_common.h\" in C with TinyCC... "
    time tcc -c -Iinclude -o $BUILD/ghost-common.o -xc - <<EOF
        #include "ghost/ghost_common.h"
EOF
fi



echo -n "Compiling all of Ghost in C with GCC... "
time gcc -c -Iinclude $GHOST -o $GHOST.o

echo -n "Compiling all of Ghost in C++ with GCC... "
time g++ -xc++ -c -Iinclude $GHOST -o $GHOST.o

echo -n "Compiling all of Ghost in C with Clang... "
time clang -c -Iinclude $GHOST -o $GHOST.o

echo -n "Compiling all of Ghost in C++ with Clang... "
time clang++ -xc++ -c -Iinclude $GHOST -o $GHOST.o

if which tcc > /dev/null; then
    echo -n "Compiling all of Ghost in C with TinyCC... "
    time tcc -c -Iinclude $GHOST -o $GHOST.o
fi


echo -n "Compiling all of Ghost amalgamated in C with GCC... "
time gcc -c -Iinclude $AMALG -o $AMALG.o

echo -n "Compiling all of Ghost amalgamated in C++ with GCC... "
time g++ -xc++ -c -Iinclude $AMALG -o $AMALG.o

echo -n "Compiling all of Ghost amalgamated in C with Clang... "
time clang -c -Iinclude $AMALG -o $AMALG.o

echo -n "Compiling all of Ghost amalgamated in C++ with Clang... "
time clang++ -xc++ -c -Iinclude $AMALG -o $AMALG.o

if which tcc > /dev/null; then
    echo -n "Compiling all of Ghost amalgamated in C with TinyCC... "
    time tcc -c -Iinclude $AMALG -o $AMALG.o
fi



echo -n "Compiling <iostream> with GCC... "
time g++ -c -o $BUILD/iostream.o -xc++ - <<EOF
    #include <iostream>
EOF

echo -n "Compiling <iostream> with Clang... "
time clang++ -c -o $BUILD/iostream.o -xc++ - <<EOF
    #include <iostream>
EOF

# Non-trivial C++ code typically includes all of these headers and more. I'm
# excluding rarely used stuff like <regex> and <thread> just to make this more
# realistic (though even then, if a class uses C++ threads internally, it has
# to include <threads> in its header to declare its privates, so it's likely to
# spread. Headers really propagate in C++.)
STL=$BUILD/stl.cxx
cat - >$STL <<EOF
    #include <algorithm>
    #include <utility>
    #include <limits>
    #include <iostream>
    #include <sstream>
    #include <memory>
    #include <type_traits>
    #include <string>
    #include <map>
    #include <set>
    #include <unordered_map>
    #include <vector>
EOF

echo -n "Compiling various STL headers with GCC... "
time gcc -c -Iinclude $STL -o $STL.o

echo -n "Compiling various STL headers with Clang... "
time clang -c -Iinclude $STL -o $STL.o



# <boost/asio.hpp> is a very commonly used library for asynchronous I/O. Lots
# of programmers swear by it. I don't know how they put up with the abysmal
# compile times.
echo -n "Compiling <boost/asio.hpp> with GCC... "
time g++ -c -o $BUILD/boost_asio.o -xc++ - <<EOF
    #include <boost/asio.hpp>
EOF

echo -n "Compiling <boost/asio.hpp> with Clang... "
time clang++ -c -o $BUILD/boost_asio.o -xc++ - <<EOF
    #include <boost/asio.hpp>
EOF



# These are admittedly some of the largest headers in Boost but I've seen Boost
# used awfully liberally in C++ code so this isn't that contrived.
BOOST=$BUILD/stl.cxx
cat - >$BOOST <<EOF
    #include <boost/asio.hpp>
    #include <boost/beast.hpp>
    #include <boost/filesystem.hpp>
    #include <boost/graph/adjacency_list.hpp>
    #include <boost/signals2.hpp>
    #include <boost/spirit/include/karma.hpp>
    #include <boost/system.hpp>
    #include <boost/thread.hpp>
EOF

echo -n "Compiling various Boost headers with GCC... "
time g++ -c -Iinclude $BOOST -o $BOOST.o

echo -n "Compiling various Boost headers with Clang... "
time clang++ -c -Iinclude $BOOST -o $BOOST.o
