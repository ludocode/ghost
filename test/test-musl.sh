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

set -e
cd $(dirname $0)/..

# This script downloads all supported versions of musl, builds their header
# files and tests that ghost/detect/ghost_musl_version.h properly detects the
# version.
#
# The version detection in ghost_musl_version.h is improved by __has_include()
# support. The below tests assume this is supported. If you run this with an
# old compiler that doesn't have __has_include() you'll get errors. This could
# be made an option later.
#
# Additional arguments to this script will be forwarded to the compiler. Pass
# e.g. -ansi, -std=c11, -D_BSD_SOURCE, etc. to test that detection is reliable
# under various language standards and feature flags. See calls to this script
# in test/megatest.sh .

CC=${CC:-cc}
ARGS="$@"

test_musl() {
    version=$1
    expected_ghost_musl_version=$2
    expected_hash=$3

    echo
    echo "Checking musl $version"

    filename=musl-$version.tar.gz
    cachefile=~/.cache/downloads/$filename
    mkdir -p ~/.cache/downloads
    if ! [ -e $cachefile ]; then
        url="https://musl.libc.org/releases/$filename"
        echo "Downloading $url"
        curl -Lo $cachefile "$url"
    else
        echo "$filename in cache"
    fi

    actual_hash=$(sha256sum $cachefile|cut -d\  -f1)
    if [ "$expected_hash" != "$actual_hash" ]; then
        echo "ERROR: Hash mismatch! $cachefile"
        echo "    Expected: $expected_hash"
        echo "    Actual:   $actual_hash"
        exit 1
    fi

    echo "Building musl-$version headers"
    mkdir -p test/.build/musl
    pushd test/.build/musl > /dev/null
    tar xzf $cachefile
    cd musl-$version
    ./configure --prefix=../install-musl-$version > /dev/null
    make install-headers > /dev/null
    popd > /dev/null
    musl_headers=test/.build/musl/install-musl-$version/include

    echo "Compiling ghost_musl.h"
    ghost_musl=$(echo '#include "ghost/detect/ghost_musl_version.h"' \
        | $CC -Wall -Wextra -Werror -Wpedantic -nostdinc \
            -Iinclude -isystem $musl_headers -xc $ARGS - -dM -E \
        | grep "^#define GHOST_MUSL "|sed 's/^#define GHOST_MUSL //')

    echo "#define GHOST_MUSL $ghost_musl"
    if [ "$ghost_musl" != 1 ]; then
        echo "ERROR: GHOST_MUSL is not 1"
        exit 1
    fi

    actual_ghost_musl_version=$(echo '#include "ghost/detect/ghost_musl_version.h"' \
        | $CC -Wall -Wextra -Werror -Wpedantic -nostdinc \
            -Iinclude -isystem $musl_headers -xc $ARGS - -dM -E \
        | grep "^#define GHOST_MUSL_VERSION "|sed 's/^#define GHOST_MUSL_VERSION //')

    echo "#define GHOST_MUSL_VERSION $actual_ghost_musl_version"
    if [ "$expected_ghost_musl_version" != "$actual_ghost_musl_version" ]; then
        echo "ERROR: Version mismatch in GHOST_MUSL_VERSION!"
        echo "    Expected: $expected_ghost_musl_version"
        echo "    Actual:   $actual_ghost_musl_version"
        exit 1
    fi

    major=$(echo $version|sed 's/\..*//')
    minor=$(echo $version|sed 's/.*\.\(.*\)\..*/\1/')
    patch=$(echo $version|sed 's/.*\.//')
    calculated_ghost_musl_version=$(echo "$major * 1000000 + $minor * 1000 + $patch"|bc)
    if [ "$expected_ghost_musl_version" != "$calculated_ghost_musl_version" ]; then
        echo "(acceptable mismatch)"
    fi
}

# We don't bother detecting versions before 1.0.0.
test_musl 0.9.15 1 4a7baab8f295511196dee48d33b8b82a159a81233facb89433707c792033cbe7

test_musl 1.0.0 1000000 1ad7f45d2972daff19c9e6a92714e6d70f4aad003cd8c3d1e6113432114c1a32
test_musl 1.0.1 1000001 119cddd23bae40ed672307696c0ec3bc59a9abdc7d4b1153fbffa0eca422a431

# 1.0.2 through 1.0.4 are detected as 1.0.1
test_musl 1.0.2 1000001 b21109858acc25c345efd4fa8257918edd0b576a0c4c632a42d997b429690f8a
test_musl 1.0.3 1000001 95c58674a22e7e705b163362e25660aa8178c3047bc12ab779fe43f16bd0581d
test_musl 1.0.4 1000001 df94d1a4a02895e169d528904b1b074bfe7ebad78eb9419f59d10c0b7aa71272

test_musl 1.0.5 1000005 acb8f9179bf1f9fc6f1cba3a30e5c686f2e18983db08005094d4a98d29e1446e

test_musl 1.1.0 1001000 de1b43019e5361d7577e5e0213e9dde591853e9da5d4a7cd75e2e0d78bf60820
test_musl 1.1.1 1001001 9dd75d6512e44d5a13254e246db56c90365894b05bab2b1127e44a31e4fd7c36
test_musl 1.1.2 1001002 dac94112b9a22d2657cd3f36ca0d62ee1eb10707a22bfc97d5746147ef92852b
test_musl 1.1.3 1001003 4ef8a7559b947808d41dbea98e24d9f36be38326fb2754a91a35520b4ca4af9f
test_musl 1.1.4 1001004 658c65ad3c3a9b281a96c5281e75720c758d91fcaae35ab987f2fdfb4f88f5cd
test_musl 1.1.5 1001005 352362b1724cc9740f4c3ce0fe02aae45e4de9809ea4ac961f31aedc11b87393
test_musl 1.1.6 1001006 5a0160c55c540d5b90158617a57647f1b03209f58d9ee70dbce19d1115b4f1b4
test_musl 1.1.7 1001007 d8e0aae287ecf8aa6500d3ed4131f33d216a7857dc7649a89125ffca6bf91599

# 1.1.8 is detected as 1.1.7
test_musl 1.1.8 1001007 fa928506415b9c555977daaf874c190eaf7fbbd16028cc5c5f33a00a83227813

test_musl 1.1.9 1001009 00bf7173caf972c88cd07cb0d420c082a2f35efcccc1a81f8909bec2d030283e

# 1.1.10 and 1.1.11 are detected as 1.1.9
test_musl 1.1.10 1001009 45bbe9b1c7f7a0f743477af1e103b6889bfe4dd9815e16f6c89f6c90831c8b7c
test_musl 1.1.11 1001009 bb9e6da51b7b12641f5d1abb39705c6c6c1b2fbd20002362948aa736a0aa353f

test_musl 1.1.12 1001012 720b83c7e276b4b679c0bffe9509340d5f81fd601508e607e708177df0d31c0e
test_musl 1.1.13 1001013 bbacdc64f557d0c4857f7d2daf592c32c29aec1babbb94fcf01a2e05bed15013

# 1.1.14 is detected as 1.1.13
test_musl 1.1.14 1001013 35f6c00c84a6091bd5dab29eedde7508dae755ead92dcc0239f3677d1055b9b5

test_musl 1.1.15 1001015 97e447c7ee2a7f613186ec54a93054fe15469fe34d7d323080f7ef38f5ecb0fa
test_musl 1.1.16 1001016 937185a5e5d721050306cf106507a006c3f1f86d86cd550024ea7be909071011
test_musl 1.1.17 1001017 c8aa51c747a600704bed169340bf3e03742ceee027ea0051dd4b6cc3c5f51464

# 1.1.18 is detected as 1.1.17
test_musl 1.1.18 1001017 d017ee5d01aec0c522a1330fdff06b1e428cb409e1db819cc4935d5da4a5a118

test_musl 1.1.19 1001019 db59a8578226b98373f5b27e61f0dd29ad2456f4aa9cec587ba8c24508e4c1d9
test_musl 1.1.20 1001020 44be8771d0e6c6b5f82dd15662eb2957c9a3173a19a8b49966ac0542bbd40d61
test_musl 1.1.21 1001021 c742b66f6f49c9e5f52f64d8b79fecb5a0f6e0203fca176c70ca20f6be285f44
test_musl 1.1.22 1001022 8b0941a48d2f980fd7036cfbd24aa1d414f03d9a0652ecbd5ec5c7ff1bee29e3
test_musl 1.1.23 1001023 8a0feb41cef26c97dde382c014e68b9bb335c094bbc1356f6edaaf6b79bd14aa
test_musl 1.1.24 1001024 1370c9a812b2cf2a7d92802510cca0058cc37e66a7bedd70051f0a34015022a3

test_musl 1.2.0 1002000 c6de7b191139142d3f9a7b5b702c9cae1b5ee6e7f57e582da9328629408fd4e8
test_musl 1.2.1 1002001 68af6e18539f646f9c41a3a2bb25be4a5cfa5a8f65f0bb647fd2bbfdf877e84b
test_musl 1.2.2 1002002 aec1ca7128576753111a1e66a0404127fff07683f8884f1677cd29aa4074e640
test_musl 1.2.3 1002003 7d5b0b6062521e4627e099e4c9dc8248d32a30285e959b7eecaa780cf8cfd4a4
