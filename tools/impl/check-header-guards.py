#!/usr/bin/env python3

import itertools, os, sys

ok = True

fix = len(sys.argv) > 1 and sys.argv[1] == "-f"
seen = set()

def checkFile(p, name):
    with open(p) as f:
        lines = f.readlines()

    # Note: Ghost's header guards don't start with GHOST_IMPL_. This means that
    # technically, they're public identifiers that you can use. This format
    # must therefore stay the same forever.
    #
    # You can use these to check whether a header was included, but avoid
    # defining them because you may break internal implementation details of
    # Ghost.
    expected = name.replace('.', '_').upper() + "_INCLUDED"

    if expected in seen:
        print("Filenames must be unique. File would have duplicate header guard:", p)
        print("    Guard:", expected)
        if fix:
            print("Cannot fix.")
        return False
    seen.add(expected)

    guards = []
    linenums = []
    for i in range(len(lines)):
        line = lines[i]
        if line.startswith("#ifndef"):
            guards.append(line)
            linenums.append(i)
        elif line.startswith("#define"):
            guards.append(line)
            linenums.append(i)
            break
    if len(guards) != 2 or not guards[0].startswith("#ifndef") or not guards[1].startswith("#define"):
        print("Couldn't find header guards:", p)
        if fix:
            print("Cannot fix.")
        return False

    fileOk = True
    for guard in guards:
        s = guard.split(" ")
        if len(s) != 2:
            print("Extraneous tokens or whitespace in",s[0],"guard:", p)
            print("    Expected:", s[0], expected)
            print("    Actual:  ", guard.rstrip('\n'))
            fileOk = False
            break
        s[1] = s[1].rstrip('\n')
        if s[1] != expected:
            print("Incorrect",s[0],"guard:", p)
            print("    Expected:", expected)
            print("    Actual:  ", s[1])
            fileOk = False
            break

    if fix and not fileOk:
        print("Fixing...")
        lines[linenums[0]] = "#ifndef " + expected + '\n'
        lines[linenums[1]] = "#define " + expected + '\n'
        with open(p, "w") as f:
            for line in lines:
                f.write(line)

    return fileOk

for root, dirs, files in itertools.chain(os.walk("include"), os.walk("experimental")):
    for name in files:
        p = os.path.join(root, name)
        #print("Checking",p)

        if name == "README.md" or name == "TODO":
            continue

        ok = checkFile(p, name) and ok

if not ok:
    sys.exit(1)
print("All header guards are correct.")
