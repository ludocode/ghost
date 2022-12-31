#!/bin/bash
set -e
cd "$(dirname "$0")"/..
mkdir -p test/.build
cd test/.build
mkdir -p ~/.cache/downloads

# Fetch mirror
# TODO

# Fetch cosmopolitan libc
cosmopolitan="$HOME/.cache/downloads/cosmopolitan-amalgamation-2.1.1.zip"
if ! [ -e $cosmopolitan ]; then
    curl -L -o "$cosmopolitan" \
        "https://github.com/jart/cosmopolitan/releases/download/2.1.1/cosmopolitan-amalgamation-2.1.1.zip"
fi
expected_hash=b36781c7cd6763402c085f29e31ab53f5df4c066dbdde83c808dea978757115a
actual_hash=$(sha256sum "$cosmopolitan"|cut -d\  -f1)
if [ "$expected_hash" != "$actual_hash" ]; then
    echo "ERROR: Hash mismatch! $cosmopolitan"
    echo "    Expected: $expected_hash"
    echo "    Actual:   $actual_hash"
    exit 1
fi
rm -rf cosmopolitan
mkdir -p cosmopolitan
cd cosmopolitan
unzip "$cosmopolitan"
sed -i '/#define IFNAMSIZ 16/d' cosmopolitan.h # fix redefined symbol error
cd ..

echo "Done."
