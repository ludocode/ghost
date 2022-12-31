#!/usr/bin/env python

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

# Amalgamates a Ghost header and prefixes all Ghost symbols encountered.
#
# This allows the generation of a standalone portability header for third-party
# libraries, allowing you to use Ghost for portability without creating a
# dependency on it.
#
# This relies on a novel property of Ghost: any header can be included on any
# platform. If the platform doesn't have the required features to implement the
# contents of the header, it will simply be disabled.

import sys, os
import re
import getopt

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

include_regex = re.compile('#\s*include\s*"(ghost.*)"')


# We scan a root file for #include directives and recursively scan those files
# for more #include directives. Any includes of `ghost/` headers are eliminated
# and used to form a dependency graph (regardless of whether they are included
# conditionally by #if directives.) The graph is then flattened into an
# amalgamated header.
#
# At the same time, we rename any symbols of the form ghost_* or GHOST_* to
# your own library prefix.
#
# We also collect up all of the copyright lines in each header. Each unique
# line is added to a set, and then all copyright lines are written out in the
# amalgamated header.


# TODO should probably preload ghost_version.h following by ghost_config.h into
# this and ignore them during processing. they should be at the top.
all_headers = {}
leaf_headers = set()
copyrights = set()

# The preamble of each header must exactly match this text with arbitrary
# "Copyright (c)" lines in between (we only allow MIT-0 code in Ghost.) We collect
# all the unique copyright lines out and insert them into the amalgamated
# header afterwards.
COPYRIGHT_OPEN = """\
/*
 * MIT No Attribution
 *""".split("\n")
COPYRIGHT_CLOSE = """\
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
 */""".split("\n")

# We add this comment after the preamble.
AMALGAMATION_COMMENT = """\
/*
 * This is an amalgamated Ghost header.
 *
 * See the official Ghost source:
 *     https://github.com/ludocode/ghost
 */
"""

LEAF_COMMENT = """\
/*
 * The following leaf headers were amalgamated into this file:
 *
"""

def strip_copyright(lines, filename):

    # remove the opening copyright preamble
    if len(lines) < len(COPYRIGHT_OPEN) or lines[0:len(COPYRIGHT_OPEN)] != COPYRIGHT_OPEN:
        raise Exception("File has incorrect copyright preamble! " + filename)
    del lines[:len(COPYRIGHT_OPEN)]

    # store any copyright lines
    copyrightFound = False
    while len(lines) > 0 and lines[0].startswith(" * Copyright (c) "):
        copyrights.add(lines[0])
        del lines[0]
        copyrightFound = True
    if not copyrightFound:
        raise Exception("File has incorrect copyright preamble! " + filename)

    # remove the remaining copyright preamble
    if len(lines) < len(COPYRIGHT_CLOSE) or lines[0:len(COPYRIGHT_CLOSE)] != COPYRIGHT_CLOSE:
        raise Exception("File has incorrect copyright preamble! " + filename)
    del lines[:len(COPYRIGHT_CLOSE)]

    return lines

def is_continuation(lines, i):
    if i < 0 or i >= len(lines):
        return False
    if len(lines[i]) == 0:
        return False
    return lines[i][-1] == "\\"

# TODO there's a bug in here where if two C-style comments are on adjacent
# lines, the second is not stripped
def strip_comments(lines, filename):
    i = 0
    blockCommentStart = None
    while i < len(lines):
        line = lines[i]

        if not blockCommentStart and line.strip().startswith("//"):
            if line.strip().endswith("\\"):
                raise Exception("Line continuation of C++-style // comments is not supported.")
            # line contains only // comment; remove the whole line
            del lines[i]
            continue

        if len(line) <= 1:
            i += 1
            continue

        j = 0
        while j < len(line) - 1:

            if not blockCommentStart and line[j:j+2] == "//":
                if line.strip().endswith("\\"):
                    raise Exception("Line continuation of C++-style // comments is not supported.")
                # line has // comment after code; remove the comment
                lines[i] = line[:j].rstrip()
                break

            elif line[j:j+2] == "/*" and not blockCommentStart:
                blockCommentStart = (i, j)

            elif line[j:j+2] == "*/" and blockCommentStart:
                s = blockCommentStart[0]
                t = blockCommentStart[1]
                blockCommentStart = None

                if i == s:
                    # comment is on one line. remove the commment.
                    line = line[:t] + line[j+2:]
                    # If the line is blank and the previous line wasn't a
                    # continuation, remove the whole thing; otherwise remove
                    # only the commented chunk
                    if (line.strip() == "" or line.lstrip() == "\\") and not is_continuation(lines, i-1):
                        del lines[i]
                        break
                    else:
                        lines[i] = line
                        j = t - 1

                else:
                    lines[s] = lines[s][:t]
                    # Delete any extra lines
                    del lines[s + 1:i]
                    i -= i - s - 1
                    # Eliminate the comment portion of the end line
                    lines[i] = line[j+2:]
                    # Eliminate the end line if it is otherwise blank
                    if lines[i].strip() == "":
                        del lines[i]
                        i -= 1
                    # Eliminate the starting line if it is otherwise blank and
                    # the previous line wasn't a continuation
                    if lines[s].strip() == "" and not is_continuation(lines, s-1):
                        del lines[s]
                        i -= 1

            j += 1

        # Disabling this, line continuation of C-style comments is harmless
        #if blockCommentStart and line.endswith("\\"):
        #    raise Exception("Line continuation within /* */ comments is not supported.")

        i += 1

    return lines

def line_starts_with_preproc(line, preproc):
    return line.strip().startswith("#") and line.strip().strip("#").strip().startswith(preproc)


def pre_clean_header(contents, filename, has_copyright=False):
    lines = contents.split("\n")

    # remove copyright
    if has_copyright:
        lines = strip_copyright(lines, filename)

    # remove comments
    lines = strip_comments(lines, filename)

    # remove leading and trailing blank lines
    while len(lines) > 0 and lines[0].strip() == "":
        del lines[0]
    while len(lines) > 0 and lines[-1].strip() == "":
        del lines[-1]

    # try to remove the include guard
    # (Note that this assumes there are no comments above the include guard
    # because they are stripped above. If we add an option to not strip
    # comments later, this has to skip past any comments.)
    if (len(lines) >= 3 and
            lines[0].strip().startswith("#ifndef GHOST_") and lines[0].strip().endswith("_INCLUDED") and
            lines[1].strip().startswith("#define GHOST_") and lines[1].strip().endswith("_INCLUDED") and
            lines[0].strip()[8:] == lines[1].strip()[8:] and lines[-1].strip() == "#endif"):
        del lines[:2]
        del lines[-1]

    return "\n".join(lines)


def post_clean_header(contents):
    lines = contents.split("\n")

    # Remove any `#if` followed directly by `#endif`. This can happen after
    # stripping #includes, e.g. in `ghost/ghost_core.h`.
    i = 0
    while i < len(lines):
        if line_starts_with_preproc(lines[i], "if"):
            j = i + 1
            while lines[j].strip() == "":
                j += 1
            if line_starts_with_preproc(lines[j], "endif"):
                del lines[i:j+1]
                continue
        i += 1

    # remove leading and trailing blank lines again
    while len(lines) > 0 and lines[0].strip() == "":
        del lines[0]
    while len(lines) > 0 and lines[-1].strip() == "":
        del lines[-1]

    # removing any two blank lines in a row
    i = 0
    while i < len(lines) - 1:
        if lines[i].strip() == "" and lines[i+1].strip() == "":
            del lines[i]
        else:
            i += 1

    return "\n".join(lines)

def parse_file(filename, user_prefix, depth, parent):
    print("  " * depth + "Parsing " + filename)
    contents = ""
    headers = []

    # TODO take include path on command line, default to include
    if filename.startswith("ghost"):
        found = False
        for p in "include/", "experimental/":
            if os.path.isfile(p + filename):
                filename = p + filename
                found = True
                break
        if not found:
            raise Exception("Header not found: \"" + filename + "\" included by \"" + str(parent) + "\"")

    with open(filename) as infile:
        matched = False
        data = pre_clean_header(infile.read(), filename, has_copyright=(depth!=0))
        for line in data.split("\n"):
            match = include_regex.search(line)
            if match:
                #print("  " * (depth+1) + "Found dependency on " + match.group(1))
                headers.append(match.group(1))
                matched = True
            elif matched and line.strip() == "":
                # Skip the blank line following an #include line.
                matched = False
            else:
                line = line.replace("ghost_", user_prefix.lower() + "_ghost_")
                line = line.replace("GHOST_", user_prefix.upper() + "_GHOST_")
                contents += line + "\n"
                matched = False
        contents = post_clean_header(contents)

    return contents, headers

def parse_header(filename, user_prefix, depth, parent):
    if filename in all_headers:
        #print("  " * depth + "Skipping " + filename)
        return

    contents, headers = parse_file(filename, user_prefix, depth=depth, parent=parent)
    all_headers[filename] = {"contents": contents, "headers": headers}
    for child in headers:
        parse_header(child, user_prefix, depth=depth+1, parent=filename)

def write_header(outfile, filename):
    # TODO if the header is blank after stripping #include and comments, skip it (or maybe just write the comment with (empty) at the end to avoid confusion.) This will be the case for the super-headers that just include lots of others

    if all_headers[filename]["contents"].strip() == "":
        print("Skipping empty header " + filename)
        return

    print("Writing " + filename)
    outfile.write("\n")
    outfile.write("/**" + ("*" * len(filename)) + "**\n")
    outfile.write(" * " + filename + "\n")
    outfile.write(" **" + ("*" * len(filename)) + "**/\n")
    outfile.write("\n")
    outfile.write(all_headers[filename]["contents"])
    outfile.write("\n")

# We sort headers first based on dependency order, then based on
# the following logical ordering of Ghost prefixes (roughly in order of
# closeness to the compiler or platform), then alphabetically by header
# filename. Any folders not listed here go alphabetically at the end.
PREFIX_ORDER = [
    "ghost/core/ghost_version.h",
    "ghost/core/ghost_config.h",
    "ghost/core/ghost_has.h",
    "ghost/preprocessor/",
    "ghost/header/",
    "ghost/language/",
    "ghost/type/",
    "ghost/debug/",
    "ghost/string/",
    "ghost/math/",
    "ghost/serialization/",
    "ghost/malloc/",
    "ghost/thread/",
]

def prefix_index(header):
    for i in range(len(PREFIX_ORDER)):
        if header.startswith(PREFIX_ORDER[i]):
            return i
    return len(PREFIX_ORDER)

# true if this header comes before the other header
def header_before(header, other):

    # preserve dependency order
    if other in all_headers[header]["headers"]:
        #print("header",header,"NOT before",other,"due to dependency")
        return False

    # keep leaves at the end as much as possible
    if header in leaf_headers and other not in leaf_headers:
        return False
    if header not in leaf_headers and other in leaf_headers:
        return True

    # sort by folder index
    h = prefix_index(header)
    o = prefix_index(other)
    if h != o:
        #print("header",header,h<o and "before" or "NOT before",other,"due to folder")
        return h < o

    # sort alphabetically
    #print("header",header,header<other and "before" or "NOT before",other,"due to alpha")
    return header < other

def sort_headers():
    headers = []

    # First we add all headers in depth first order. The result will be mostly
    # sorted already.
    headers_set = set()
    headers_stack = []
    def add_header_impl(header):
        #print("header",header)
        if header not in headers_set:
            headers_set.add(header)
            headers.append(header)
    def add_header(header):
        if header in headers_stack:
            if header == "ghost/ghost_core.h" or header.startswith("ghost/core/"):
                # Circular includes of ghost/core/ are OK. All files in
                # ghost/core/ include ghost/ghost_core.h; ghost/core/ is
                # essentially an atomic unit. They are all macros so it doesn't
                # matter in what order they get included.
                return
            headers_stack.append(header)
            raise Exception("Circular dependency! Header:", header, "Stack:", headers_stack)
        if header in headers_set:
            return
        headers_stack.append(header)
        for child in all_headers[header]["headers"]:
            add_header(child)
        add_header_impl(header)
        headers_stack.pop()
    #print("Collecting headers in depth-first order")
    for header in all_headers:
        add_header(header)

    #for header in headers:
    #    print("depth first order:  ",header)

    # Next we do an insertion sort via swapping. This only ever compares and
    # swaps adjacent elements so it allows us to preserve dependency order.
    for i in range(1, len(headers)):
        header = headers[i]
        #print("sorting",i,header)
        for j in range(i-1, -1, -1):
            other = headers[j]
            if header_before(header, headers[j]):
                #print("moving back")
                headers[j+1], headers[j] = headers[j], headers[j+1]
            else:
                break

    for header in headers:
        print("sorted order:  ",header)

    return headers

def write_output(output_filename, user_prefix):
    with open(output_filename, "w") as outfile:

        # Write copyright
        outfile.write("\n".join(COPYRIGHT_OPEN))
        outfile.write("\n")
        for c in sorted(copyrights):
            outfile.write(c)
            outfile.write("\n")
        outfile.write("\n".join(COPYRIGHT_CLOSE))
        outfile.write("\n\n")

        # Write amalgamation comment
        outfile.write(AMALGAMATION_COMMENT)
        outfile.write("\n")

        # Write list of leaf headers
        outfile.write(LEAF_COMMENT)
        for header in sorted(leaf_headers):
            outfile.write(" *     " + header + "\n")
        outfile.write(" */\n\n")

        # Open include guard
        include_guard = user_prefix.upper() + "_GHOST_AMALGAMATED_H_INCLUDED"
        outfile.write("#ifndef " + include_guard + "\n")
        outfile.write("#define " + include_guard + "\n")
        outfile.write("\n")

        # Define config
        amalgamated = user_prefix.upper() + "_GHOST_IMPL_AMALGAMATED"
        outfile.write("#define " + amalgamated + " 1\n\n")

        # Write headers
        for header in sort_headers():
            write_header(outfile, header)

        # Close include guard
        outfile.write("\n#endif\n")

    print("Wrote " + output_filename)

# Writes a graphviz graph.
# This is useless for all but the simplest amalgamations. The full graph for
# ghost_common.h is like 300 megapixels and has a zillion lines. We could get a
# pretty graph if we eliminated any direct dependency that also exists as a
# transitive dependency but this would make the graph kind of meaningless.
def write_graph():
    with open("graph.dot", "w") as f:
        f.write("digraph G {\n")
        f.write('    rankdir="LR"\n')
        f.write('    node [shape=box]\n')

        skip_ghost_core = False

        f.write('\n')
        for h in leaf_headers:
            if skip_ghost_core and (h.startswith("ghost/core/") or h.startswith("ghost/ghost_core")):
                continue
            f.write(f'    "{h}" [color=blue fontcolor=blue]\n')

        f.write('\n')
        for k, v in all_headers.items():
            if skip_ghost_core and (k.startswith("ghost/core/") or k.startswith("ghost/ghost_core")):
                continue
            for d in sorted(v["headers"]):
                if skip_ghost_core and (d.startswith("ghost/core/") or d.startswith("ghost/ghost_core")):
                    continue
                f.write(f'    "{k}" -> "{d}"\n')
        f.write("}")

def usage():
    eprint("""
This script amalgamates all Ghost headers included by a given input file, as
well as all other Ghost headers they depend on recursively.

All Ghost identifiers are prefixed to avoid conflicts with the unamalgamated
Ghost. This allows you to include the amalgamation in a library for example.
""")
    eprint("Usage: " + sys.argv[0] + " -i <input> -o <output> -p <prefix>")
    eprint()
    eprint("    -i <input>    Input filename")
    eprint("    -o <output>   Output filename")
    eprint("    -p <prefix>   Prefix to prepend to all Ghost identifiers")

def go():
    optlist, rest = getopt.getopt(sys.argv[1:], "h?i:o:p:", ["help"])
    if len(rest) > 0:
        eprint("Unrecognized option: " + rest[0])
        usage()
        return 1

    for opt in optlist:
        if opt[0] in ["-h", "-?", "--help"]:
           usage()
           return 0

        if opt[0] == "-i":
            if opt[1] == "-":
                # TODO this doesn't work on Windows
                input_filename = "/dev/stdin"
            else:
                input_filename = opt[1]

        if opt[0] == "-o":
            output_filename = opt[1]

        if opt[0] == "-p":
            user_prefix = opt[1]

    # We discard the contents of the input file. We only want the headers it
    # includes.
    _, headers = parse_file(input_filename, user_prefix, depth=0, parent=None)
    for header in headers:
        leaf_headers.add(header)
        parse_header(header, user_prefix, depth=1, parent=None)

    write_output(output_filename, user_prefix)
    #write_graph()
    return 0

if __name__ == "__main__":
    sys.exit(go())
