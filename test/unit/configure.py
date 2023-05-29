#!/usr/bin/env python3

# MIT No Attribution
#
# Copyright (c) 2022-2023 Fraser Heavy Software
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

import shutil, os, sys, subprocess, json, itertools, platform
from os import path

globalbuild = path.join("test", ".build", "unit")



###################################################
# Determine Compiler
###################################################

# The following compilers are detected by this script:
# - GCC (gcc/g++)
# - Clang (clang/clang++)
# - NVidia/PGI compiler (nvc/nvc++)
# - MSVC (cl.exe)
# - Digital Mars C/C++ (dmc.exe)
# - Emscripten
# - TinyCC (tcc)
# - chibicc
# - kefir
# - 8cc
# - cproc
# - cparser
# - lacc
# - lcc
# TODO intel

cc = None
compilerVersion = None
compiler = "unknown"

if os.getenv("CC"):
    cc = os.getenv("CC")
elif shutil.which("cl.exe"):
    cc = "cl"
else:
    cc = "cc"

full_cc = shutil.which(cc)
if not full_cc:
    raise Exception("Compiler " + cc + " cannot be found!")

if cc.lower() == "cl" or cc.lower() == "cl.exe":
    compiler = "MSVC"
elif "cproc" in cc:
    compiler = "cproc"
elif "chibicc" in cc:
    compiler = "chibicc"
elif "8cc" in cc:
    compiler = "8cc"
elif "kefir" in cc:
    compiler = "kefir"
elif "dmc" in cc:
    compiler = "dmc"
elif "lacc" in cc:
    compiler = "lacc"
elif "lcc" in cc:
    compiler = "lcc"
elif "emcc" in cc:
    compiler = "emscripten"
elif "pcc" in cc:
    compiler = "pcc"
elif "scc" in cc:
    compiler = "scc"
else:
    # try --version
    ret = subprocess.run([cc, "--version"], universal_newlines=True,
            stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    if ret.stderr.startswith("Microsoft (R) C/C++ Optimizing Compiler"):
        compiler = "MSVC"

    elif ret.returncode == 0:
        if ret.stdout.startswith("cparser "):
            compiler = "cparser"
        elif "PGI" in ret.stdout or "NVIDIA" in ret.stdout:
            compiler = "PGI"
        elif "clang" in ret.stdout:
            compiler = "Clang"

    if compiler == "unknown":
        # try -v
        ret = subprocess.run([cc, "-v"], universal_newlines=True,
                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if ret.returncode == 0:
            for line in (ret.stdout + "\n" + ret.stderr).splitlines():
                if line.startswith("tcc "):
                    compiler = "TinyCC"
                    break
                elif line.startswith("gcc "):
                    compiler = "GCC"
                    break

if compiler == "GCC":
    ret = subprocess.run([cc, "--version"], universal_newlines=True,
            stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if ret.returncode != 0:
        raise Exception("Failed to determine GCC version")
    v = ret.stdout.splitlines()[0].split(" ")[2].split(".")
    compilerVersion = int(v[0]) * 1000000 + int(v[1]) * 1000 + int(v[2])
elif compiler == "MSVC":
    ret = subprocess.run([cc, "/?"], universal_newlines=True,
            stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if ret.returncode != 0:
        raise Exception("Failed to determine MSVC version")
    v = ret.stderr.splitlines()[0].split(" Version ")[1].split(" ")[0].split(".")
    compilerVersion = int(v[0]) * 100 + int(v[1])

print("Using " + compiler + " compiler with executable: " + cc)

if compiler == "MSVC" or compiler == "dmc":
    obj_extension = ".obj"
    exe_extension = ".exe"
elif compiler == "emscripten":
    obj_extension = ".wasm"
    exe_extension = ".wasm"
else:
    obj_extension = ".o"
    exe_extension = ""

ccache = shutil.which("ccache") and not os.getenv("CCACHE_DISABLE") and os.getenv("CI") is None

if compiler in ["pcc", "scc", "unknown"]:
    ccache = False


###################################################
# Load Cached Configuration
###################################################

config = None

configFile = path.join(globalbuild, "config.json")
if path.exists(configFile):
    try:
        with open(configFile) as infile:
            print("Loading cached configuration")
            config = json.load(infile)
        if config["cc"] != full_cc:
            print("Compiler is different. Cleaning and discarding cached configuration.")
            shutil.rmtree(globalbuild)
            config = None
    except:
        print("Error loading cached configuration. Cleaning and discarding.")
        shutil.rmtree(globalbuild)

if config is None:
    config = {
        "cc": full_cc,
        "flags": {},
    }

os.makedirs(globalbuild, exist_ok=True)



###################################################
# Compiler Probing
###################################################

flagtest_src = path.join(globalbuild, "flagtest.c")
flagtest_exe = path.join(globalbuild, "flagtest" + exe_extension)
with open(flagtest_src, "w") as out:
    out.write("""
/* include features.h via stdlib.h to test _FORTIFY_SOURCE properly */
#include <stdlib.h>

int main(int argc, char** argv) {
    /* array dereference to test for the existence of
     * sanitizer libs when using -fsanitize (libubsan)
     * compare it to another string in the array so that
     * -Wzero-as-null-pointer-constant works */
    return argv[argc - 1] == argv[0];
}
""")

def checkFlags(flags):
    if isinstance(flags, str):
        flags = [flags,]

    configArg = "|".join(flags)
    if configArg in config["flags"]:
        return config["flags"][configArg]
    print("Testing flag(s): " + " ".join(flags) + " ... ", end="")
    sys.stdout.flush()

    if compiler == "MSVC":
        cmd = [cc, "/W4", "/WX"] + flags + [flagtest_src, "/Fe" + flagtest_exe, "/Fo" + flagtest_src + ".obj"]
    elif compiler == "dmc":
        cmd = [cc] + flags + [flagtest_src, "-ooutput" + flagtest_exe]
    else:
        # We assume the compiler supports -o and -c. We don't assume anything
        # else, not even -Wall (since some compilers, e.g. scc, don't support
        # them.)
        cmd = [cc]
        if compiler != "unknown" and compiler != "scc":
            cmd += ["-Wall", "-Wextra", "-Werror"]
        cmd += flags + [flagtest_src, "-o", flagtest_exe]
    #print(" ".join(cmd))
    ret = subprocess.run(cmd, universal_newlines=True,
            stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    if ret.returncode == 0:
        print("Supported.")
        supported = True
    else:
        print("Not supported.")
        supported = False
    config["flags"][configArg] = supported
    return supported

if not checkFlags([]):
    print("ERROR: Compiler either doesn't work or doesn't support our default flags.")
    sys.exit(1)

def flagsIfSupported(flags):
    if checkFlags(flags):
        if isinstance(flags, str):
            return [flags]
        return flags
    return []

# We use -Og for all debug builds if we have it, but ONLY under GCC. It can
# sometimes improve warnings, and things run a lot faster especially under
# Valgrind, but Clang stupidly maps it to -O1 which has some optimizations
# that break debugging!
if "-Og" not in config["flags"]:
    sys.stdout.flush()
    if compiler == "MSVC" or compiler == "dmc":
        print("Testing flag(s): -Og ... Not supported.")
        config["flags"]["-Og"] = False
    elif compiler == "GCC":
        config["flags"]["-Og"] = checkFlags("-Og")
    else:
        print("Testing flag(s): -Og ... May be supported but we won't use it.")
        config["flags"]["-Og"] = False
hasOg = config["flags"]["-Og"]


###################################################
# Common Flags
###################################################

hasDeps = False

defaultCPPFlags = []
defaultLDFlags = []

if compiler == "PGI":
    defaultCPPFlags.append("--display_error_number")

    # NVIDIA/PGI warns about its own __builtin_pgi_va_start() used by va_start():
    #     warning #669-D: ellipsis with no explicit parameters is nonstandard
    defaultCPPFlags += ["--diag_suppress", "669"]

if compiler == "MSVC":
    defaultCPPFlags += [
        "/W4", "/WX",
    ]
    defaultLDFlags += [
        "Advapi32.lib", # for crypto funcs
        "/DEBUG",
    ]
elif compiler == "dmc" or compiler == "kefir":
    defaultCPPFlags += []
    defaultLDFlags += []
elif compiler != "unknown" and compiler != "scc":
    defaultCPPFlags += [
        "-Wall",
        "-g",
    ]

    # We don't treat warnings as errors with cparser because it warns about
    # lots of stuff that is silenced by other compilers, especially when
    # expanded from macros
    # Same with PCC
    # TODO we'd like this on even with these compilers, eventually, maybe...
    if compiler != "cparser" and compiler != "pcc":
        defaultCPPFlags.append("-Werror")

defaultCPPFlags += [
    "-Iinclude",
    "-Iexperimental",
    "-Itest/unit/src",
    "-Itest/unit/experimental",
    "-Itest/unit/mirror/include"
]

if compiler == "pcc":
    # In a modern development build of PCC, GHOST_CONFIG_H doesn't work.
    # Interestingly, it worked fine back in 1.1.0.
    defaultCPPFlags.append("-include \"test_config.h\"")
else:
    defaultCPPFlags.append("-DGHOST_CONFIG_H=\\\"test_config.h\\\"")

# optimization
if compiler == "MSVC":
    debugFlags = ["/Od", "/MDd"]
    releaseFlags = ["/O2", "/MD"]
elif compiler == "dmc":
    debugFlags = []
    releaseFlags = ["-o"]
elif compiler == "kefir":
    debugFlags = []
    releaseFlags = []
else:
    debugFlags = [hasOg and "-Og" or "-O0"]
    releaseFlags = ["-O2"]
debugFlags.append("-DDEBUG")
releaseFlags.append("-DNDEBUG")
if compiler == "emscripten":
    defaultCPPFlags += ["-Wno-gnu-zero-variadic-macro-arguments"]
    releaseFlags += ["-Wno-limited-postlink-optimizations"]

# We add _FORTIFY_SOURCE only if it works. (-D_FORTIFY_SOURCE=1 throws warnings
# under GCC 9.3.0 on Ubuntu 20.04, apparently because it defines
# _FORTIFY_SOURCE=2 as a built-in when compiling with -O2.)
# (lacc doesn't support -Werror and cproc doesn't pass -Werror along to its
# preprocessor so the #warning doesn't cause the check to fail.)
if compiler != "cproc" and compiler != "lacc":
    if checkFlags(debugFlags + ["-D_FORTIFY_SOURCE=2"]):
        debugFlags.append("-D_FORTIFY_SOURCE=2")
    if checkFlags(releaseFlags + ["-D_FORTIFY_SOURCE=1"]):
        releaseFlags.append("-D_FORTIFY_SOURCE=1")

# flags for specifying source language
if compiler == "MSVC":
    defaultCFlags = ["/TC"]
    defaultCXXFlags = ["/TP", "/EHsc"]
elif compiler == "dmc":
    defaultCFlags = ["-wx"]
    defaultCXXFlags = ["-wx", "-cpp", "-wc"]
else:
    defaultCFlags = []
    defaultCXXFlags = [
        "-xc++"
    ]
    if checkFlags(["-xc++", "-std=c++11"]):
        defaultCXXFlags += ["-std=c++11"]

    if checkFlags(["-xc++", "-Wmissing-declarations"]):
        defaultCXXFlags += ["-Wmissing-declarations"]

    if checkFlags(["-Wl,-lpthread"]):
        defaultLDFlags.append("-lpthread")
    if checkFlags(["-Wl,-lm"]):
        defaultLDFlags.append("-lm")
    elif checkFlags(["-lm"]):
        defaultLDFlags.append("-lm")

if compiler != "MSVC" and compiler != "dmc":
    if checkFlags(defaultCXXFlags + ["-Wold-style-cast"]):
        defaultCXXFlags.append("-Wold-style-cast")


###################################################
# Variable Flags and other supported features
###################################################

compilerSupportsCXX = False

if compiler == "MSVC":
    compilerSupportsCXX = True

if compiler != "MSVC" and compiler != "dmc":

    # TinyCC silently ignores this
    if compiler != "TinyCC":
        # A bit of duplication here: with Clang we prefer libc++ instead of
        # libstdc++, but we'll use either if they work
        if compiler == "Clang":
            if checkFlags(["-x", "c++", "-Wl,-lc++"]):
                compilerSupportsCXX = True
                defaultLDFlags.append("-lc++")
            elif checkFlags(["-x", "c++", "-Wl,-lstdc++"]):
                compilerSupportsCXX = True
                defaultLDFlags.append("-lstdc++")
        else:
            if checkFlags(["-x", "c++", "-Wl,-lstdc++"]):
                compilerSupportsCXX = True
                defaultLDFlags.append("-lstdc++")
            elif checkFlags(["-x", "c++", "-Wl,-lc++"]):
                compilerSupportsCXX = True
                defaultLDFlags.append("-lc++")
            else:
                # TODO there is no way to get nvc to compile as C++, you have
                # to use nvc++. We'll need some changes to this script to make
                # it work.
                pass

    if not os.getenv("CI"):
        # we have to force color diagnostics to get color output from ninja
        # (ninja will strip the colors if it's being piped)
        if checkFlags("-fdiagnostics-color=always"):
            defaultCPPFlags.append("-fdiagnostics-color=always")
        elif checkFlags("-fcolor-diagnostics=always"):
            defaultCPPFlags.append("-color-diagnostics=always")

    if checkFlags("-Wstrict-aliasing=3"):
        defaultCPPFlags.append("-Wstrict-aliasing=3")
    elif checkFlags("-Wstrict-aliasing=2"):
        defaultCPPFlags.append("-Wstrict-aliasing=2")
    elif checkFlags("-Wstrict-aliasing"):
        defaultCPPFlags.append("-Wstrict-aliasing")

    if checkFlags("-Wimplicit-fallthrough=5"):
        defaultCPPFlags.append("-Wimplicit-fallthrough=5")
    elif checkFlags("-Wimplicit-fallthrough"):
        defaultCPPFlags.append("-Wimplicit-fallthrough")

    extraFlags = [
        "-Wextra",
        "-Wpedantic",
        "-Wmissing-variable-declarations",
        "-Wfloat-conversion",
        "-Wconversion",
        "-Wundef",
        "-Wshadow",
        "-Wcast-qual",
        "-fPIC",
        "-fstrict-aliasing",
        "-fno-omit-frame-pointer",

        # TODO add a few more:
        #-Wconversion -Wsign-conversion -Wcast-qual -Wformat=2 -Wundef -Werror=float-equal -Wshadow -Wcast-align -Wunused -Wnull-dereference -Wdouble-promotion -Wimplicit-fallthrough -Werror=strict-prototypes -Wwrite-strings

        # TODO this is a temporary limitation of mirror, it's not stringifying
        # its checks correctly
        "-Wno-overlength-strings",

        # TODO for now we also want to ignore unused link flags (since we link
        # with e.g. pthreads even when threads are disabled.)
        #TODO this doesn't work
        "-Wno-unused-command-line-argument"
    ]
    for flag in extraFlags:
        defaultCPPFlags += flagsIfSupported(flag)

    if checkFlags("-Wpedantic"):
        defaultCPPFlags += ["-Wpedantic"]
    elif checkFlags("-pedantic"):
        defaultCPPFlags += ["-pedantic"]

    if checkFlags(defaultCXXFlags + ["-Wzero-as-null-pointer-constant"]):
        defaultCXXFlags.append("-Wzero-as-null-pointer-constant")

    # TODO we need a build without this, partly for valgrind and partly because
    # this breaks malloc_usable_size
    #if checkFlags("-fsanitize=address"):
    #    defaultCPPFlags.append("-fsanitize=address");
    #    defaultLDFlags.append("-fsanitize=address");

    hasDeps = checkFlags(["-MD", "-MF", flagtest_exe + ".d"])

    defaultCFlags += flagsIfSupported("-Wmissing-prototypes")
    defaultCFlags += flagsIfSupported("-Wc++-compat")

# Silence some warnings in old compilers that Ghost can't do automatically
if compiler == "GCC":
    if compilerVersion < 5000000:
        defaultCPPFlags += ["-Wno-long-long"] # see ghost_impl_detect_llong.h
    if compilerVersion < 5000000:
        defaultCPPFlags += ["-Wno-missing-field-initializers"] # see ghost_zero_init.h
    if compilerVersion < 4006000:
        # Versions of GCC before 4.6 don't support diagnostic push so Ghost
        # can't silence any warnings in its own implementation. Rather than
        # silencing warnings globally, we prefer to let whoever is using Ghost
        # silence warnings themselves, this way they are aware of whatever
        # warnings need to be disabled.
        defaultCPPFlags.remove("-Wconversion")
        defaultCFlags.remove("-Wmissing-prototypes")

# Many C compilers don't support something like __attribute__((constructor)) so
# we need to register unit tests manually. This adds a build step that pulls
# unit test registration functions out of all the compiled object files.
# (It would make a lot more sense to probe for this with a test for
# ghost_has(ghost_static_init) rather than listing out all these compilers.)
generateUnitTestRegistrations = \
        not compiler == "Clang" and \
        not compiler == "GCC" and \
        not compiler == "MSVC" and \
        not compiler == "PGI" and \
        not compiler == "emscripten"
if generateUnitTestRegistrations:
    defaultCPPFlags.append("-DMIRROR_MANUAL_REGISTRATION")

# cparser warns about some innocuous stuff that no other compiler warns about. For now we just silence these warnings.
if compiler == "cparser":
    defaultCFlags += [
        "-Wno-redundant-decls",
        "-Wno-empty-statement",
        "-Wno-unreachable-code", # no way to work around this, see ghost_unreachable.h
        "-Wno-missing-prototypes",
        "-Wno-unused-variable",
    ]

if platform.system() == "Darwin":
    defaultLDFlags += ["-framework", "Security"]



###################################################
# Build configuration
###################################################

builds = {}

class Build:
    def __init__(self, name, cppflags, cflags, cxxflags, ldflags):
        self.name = name
        self.cppflags = cppflags
        self.cflags = cflags
        self.cxxflags = cxxflags
        self.ldflags = ldflags
        self.run_wrapper = None
        self.exclude = False

def addBuild(name, cppflags = defaultCPPFlags, cflags = defaultCFlags, cxxflags = defaultCXXFlags, ldflags = defaultLDFlags):
    builds[name] = Build(name, cppflags[:], cflags[:], cxxflags[:], ldflags[:])

def addDebugReleaseBuilds(name, cppflags = defaultCPPFlags, cflags = defaultCFlags, cxxflags = defaultCXXFlags, ldflags = defaultLDFlags):
    addBuild(name + "-debug", cppflags + debugFlags, cflags, cxxflags, ldflags)
    addBuild(name + "-release", cppflags + releaseFlags, cflags, cxxflags, ldflags)

addDebugReleaseBuilds('default')

# MSVC variants
if compiler == "MSVC":

    # No extensions
    # This is disabled because MSVC throws warnings in its own headers, e.g. it
    # throws C4001 about single-line comments in vcruntime.h right off the bat.
    #addDebugReleaseBuilds('strict', defaultCPPFlags + ["/Za"])

    # Link-time optimization
    addDebugReleaseBuilds('lto', defaultCPPFlags + ["/GL"], defaultCFlags, defaultCXXFlags, defaultLDFlags + ["/LTCG"])

    # All files as C++
    addDebugReleaseBuilds('c++', defaultCPPFlags + defaultCXXFlags, [], [])

    # C++17 (not supported by VS2015)
    if compilerVersion >= 1916 and checkFlags(defaultCXXFlags + ["/std:c++17"]):
        addDebugReleaseBuilds('c++17', defaultCPPFlags + defaultCXXFlags + ["/std:c++17"], [], [])

    # No exceptions
    cxxFlagsNoExcept = [x for x in defaultCXXFlags if x != "/EHsc"]

    # VS2015's xlocale header uses try/catch blocks which causes errors when
    # exception support is disabled. For now we don't bother trying to work
    # around this; we just don't test the nounwind variant on it.
    if compilerVersion >= 1916:
        # MSVC warns about noexcept specifications in its own headers even
        # when we don't include them. It seems to include <exception> by
        # default with causes C4577. We assume that anyone who disables
        # exceptions will also need to disable this warning so we just
        # disable it.
        cxxFlagsNoExcept += ["/wd4577"]
        addDebugReleaseBuilds('c++-nounwind', defaultCPPFlags + cxxFlagsNoExcept, [], [])

    # Managed C++
    # TODO disabled for now. /clr throws warnings about compiling varargs
    # functions like asprintf() as native. Not sure what to do about it yet.
    #if checkFlags(cxxFlagsNoExcept + ["/clr"]):
    #    addDebugReleaseBuilds('c++-clr', defaultCPPFlags + cxxFlagsNoExcept + ["/clr"], [], []) # implies /EHa

    # New preprocessor
    # (We do most MSVC builds as the old preprocessor to make sure it works.
    # The new preprocessor is much closer in behaviour to other compilers so we
    # don't need to test it as thoroughly.)
    # Note: As above, this isn't supported by MSVC 2015 but doesn't cause the
    # build to fail. We just ignore it.
    addDebugReleaseBuilds('pp', defaultCPPFlags + ["/Zc:preprocessor"])


# TinyCC variants
if compiler == "TinyCC":
    # bounds-checking feature:
    #addDebugReleaseBuilds('bounds', defaultCPPFlags + ['-b'], defaultCFlags, defaultCXXFlags, defaultLDFlags + ['-b'])
    pass

# feature test macro variants
# Currently we only combine these with the default build. We need to rewrite
# this build generation code to support matrix builds to combine these with
# different language standards and other things, most importantly disabled asm
# labels. For now we add special cases for those below.
if compiler != "MSVC" and compiler != "dmc":
    # We need to check flags because e.g. glibc gives a deprecation warning
    # about _BSD_SOURCE. This also helps to eliminate some useless builds.
    if checkFlags("-D_POSIX_C_SOURCE=1"):
        addDebugReleaseBuilds('posix1src', defaultCPPFlags + ["-D_POSIX_C_SOURCE=1"])
    if checkFlags("-D_POSIX_C_SOURCE=200809L"):
        addDebugReleaseBuilds('posix2008src', defaultCPPFlags + ["-D_POSIX_C_SOURCE=200809L"])
    if checkFlags("-D_XOPEN_SOURCE=500"):
        addDebugReleaseBuilds('xopensrc', defaultCPPFlags + ["-D_XOPEN_SOURCE=500"])
    if checkFlags("-D_GNU_SOURCE"):
        addDebugReleaseBuilds('gnusrc', defaultCPPFlags + ["-D_GNU_SOURCE"])
    if checkFlags("-D_BSD_SOURCE"):
        addDebugReleaseBuilds('bsdsrc', defaultCPPFlags + ["-D_BSD_SOURCE"])
    if checkFlags("-D_DEFAULT_SOURCE"):
        addDebugReleaseBuilds('defaultsrc', defaultCPPFlags + ["-D_DEFAULT_SOURCE"])
    if checkFlags("-D_NETBSD_SOURCE"):
        addDebugReleaseBuilds('netbsdsrc', defaultCPPFlags + ["-D_NETBSD_SOURCE"])
    # special cases: we want to make sure we get no shadowing warnings when
    # compiling with declared functions that Ghost will need to redeclare.
    if checkFlags("-D_GNU_SOURCE"):
        addDebugReleaseBuilds('gnusrc-noasml', defaultCPPFlags + ["-D_GNU_SOURCE", "-Dghost_has_ghost_asm_label=0"])
    if checkFlags("-D_BSD_SOURCE"):
        addDebugReleaseBuilds('bsdsrc-noasml', defaultCPPFlags + ["-D_BSD_SOURCE", "-Dghost_has_ghost_asm_label=0"])
    # we also want to make sure we get no warnings about incompatible throw()
    # declarations in C++.
    if compilerSupportsCXX and checkFlags("-D_GNU_SOURCE"):
        addDebugReleaseBuilds('c++-gnusrc-noasml', defaultCPPFlags + defaultCXXFlags + ["-D_GNU_SOURCE", "-Dghost_has_ghost_asm_label=0"], [], [])

# GNU-style variants
#
# We have to disable variant builds under some compilers:
#
# - TinyCC silently ignores most of these compiler options which leads to all
#   sorts of build failures
#
# - cproc supports _Alignof/_Alignas even in C99 mode but it doesn't provide us
#   a way to detect it so we fail under -std=c99 and can't work around it
#   (TODO we should be able to work around this)
#
if compiler != "TinyCC" and compiler != "cproc" and compiler != "MSVC":

    # C builds

    # TODO get this working
    addDebugReleaseBuilds('c89', defaultCPPFlags + ["-std=c89",
#            # TODO get rid of all these extra warning flags
#            #"-Wno-pedantic","-Wfatal-errors", "-Wno-invalid-pp-token", "-Wno-extra-tokens"
#            "-Wno-error"
            ], defaultCFlags + ["-std=c89"])

    # TODO remove -Wno-pedantic
    gnu89flags = ["-std=gnu89",
            "-Wno-pedantic"
            #"-Wno-error"
            ]
    if checkFlags(gnu89flags):
        addDebugReleaseBuilds('gnu89', defaultCPPFlags, defaultCFlags + gnu89flags)

    if checkFlags("-std=c11"):
        addDebugReleaseBuilds('c11', defaultCPPFlags, defaultCFlags + ["-std=c11"])

    # We support -std=c99 on GNUC-style compilers because they have
    # platform-specific alignment specifiers (e.g. __attribute__((__aligned__()))).
    addDebugReleaseBuilds('c99', defaultCPPFlags, defaultCFlags + ["-std=c99"])

    # Link-time optimization
    # TODO disabled for now, lto build is busted
    if False:#checkFlags("-flto"):
        ltoFlags = defaultCPPFlags + ["-flto"]
        ltoDebugFlags = ltoFlags + debugFlags
        ltoReleaseFlags = ltoFlags + [x.replace("-O2", "-O3") for x in releaseFlags]
        addBuild('lto-debug', defaultCPPFlags + ltoDebugFlags, defaultCFlags, defaultCXXFlags,
                defaultCPPFlags + ltoDebugFlags + defaultLDFlags)
        addBuild('lto-release', defaultCPPFlags + ltoReleaseFlags, defaultCFlags, defaultCXXFlags,
                defaultCPPFlags + ltoReleaseFlags + defaultLDFlags)

    # Size optimization
    if checkFlags("-Os"):
        addBuild('sizeopt', defaultCPPFlags + [x.replace("-O2", "-Os") for x in releaseFlags])

    # C++ builds

    if compilerSupportsCXX:
        cxxFlagsNoVersion = [x for x in defaultCXXFlags if x != "-std=c++11"]

        # C11, with C++ files as gnu++17
        if checkFlags(["-x", "c++", "-std=gnu++17"]) and checkFlags("-std=c11"):
            addDebugReleaseBuilds('c11-gnu++17', defaultCPPFlags, defaultCFlags + ["-std=c11"], cxxFlagsNoVersion + ["-std=gnu++11"])

        # All files as C++
        addDebugReleaseBuilds('gnu++11', defaultCPPFlags + cxxFlagsNoVersion + ["-std=gnu++11"], [], [])
        # TODO get this working
        #if checkFlags(["-x", "c++", "-std=c++98"]):
        #    addDebugReleaseBuilds('c++98', defaultCPPFlags + cxxFlagsNoVersion + ["-std=c++98"], [], [])
        if checkFlags(["-x", "c++", "-std=c++17"]):
            addDebugReleaseBuilds('c++17', defaultCPPFlags + cxxFlagsNoVersion + ["-std=c++17"], [], [])
        if checkFlags(["-x", "c++", "-std=c++17", "-fno-exceptions"]):
            addDebugReleaseBuilds('c++17-noexcept', defaultCPPFlags + cxxFlagsNoVersion + ["-std=c++17", "-fno-exceptions"], [], [])

# Some configuration variants
addDebugReleaseBuilds('no-asm-label', defaultCPPFlags + ["-Dghost_has_ghost_asm_label=0"])
addDebugReleaseBuilds('no-malloc', defaultCPPFlags + ["-DGHOST_MALLOC_SYSTEM=1"])
addDebugReleaseBuilds('no-free', defaultCPPFlags + ["-Dghost_has_ghost_free=0", "-Dghost_has_ghost_aligned_free=0"])

# Note: We still link against pthreads in the no-pthreads build because we want
# to be able to fall back to C11 threads and on some libcs you must link
# pthreads to use C11 threads. Except, on FreeBSD, you need -lstdthreads, so we
# add that if necessary. Later on this should be separated out into multiple
# builds: pthreads, C11 and none, with only the necessary linker flags for
# each.
c11threadsLDFlags = []
if checkFlags(["-Wl,-lstdthreads"]):
    c11threadsLDFlags += ["-lstdthreads"]
addDebugReleaseBuilds('no-pthreads', defaultCPPFlags + ["-Dghost_has_ghost_pthread_h=0"], ldflags = defaultLDFlags + c11threadsLDFlags)

# Cosmopolitan libc
# (need to run test/fetch-dependencies.sh first, run by megatest)
# Seems to require at least GCC 6.5 to compile successfully and 8.5 to compile
# without warnings. Clang doesn't support some of the options needed (like
# -mnop-mcount, could probably be excluded but I'm trying to keep the options
# as close to recommended as possible.) We'll scope this to GCC only for now.
if os.path.exists("test/.build/cosmopolitan/cosmopolitan.h") and \
        platform.system() == "Linux" and compiler == "GCC" and compilerVersion >= 8005000:

    cosmoCPPFlags = [x for x in defaultCPPFlags if x not in [
            "-Wpedantic",
            "-Wcast-qual",
            "-Wshadow",
            "-Wundef",
            "-Wconversion",
            "-Werror",
        ]]
    cosmoCFlags = [x for x in defaultCFlags if x not in [
            "-Wc++-compat",
        ]]

    addDebugReleaseBuilds('cosmopolitan', cppflags=cosmoCPPFlags + """
            -static -fno-pie -nostdinc -gdwarf-4
            -fno-omit-frame-pointer -pg -mnop-mcount -mno-tls-direct-seg-refs
            -include test/.build/cosmopolitan/cosmopolitan.h
            -ffunction-sections -fdata-sections
        """.split(),
        cflags=cosmoCFlags,
        ldflags="""
            -no-pie
            -nostdlib
            -fuse-ld=bfd
            -Wl,-T,test/.build/cosmopolitan/ape.lds
            -Wl,--gc-sections
            -include test/.build/cosmopolitan/cosmopolitan.h
            test/.build/cosmopolitan/crt.o
            test/.build/cosmopolitan/ape-no-modify-self.o
            test/.build/cosmopolitan/cosmopolitan.a
        """.split(),
        )



###################################################
# Ninja generation
###################################################

# Gets the MIRROR_KEY for a given source file.
def get_mirror_id(src):
    # TODO cproc has identifier length limits, just generate a random number for id
#    if compiler == "cproc":
#        import random
#        return "g" + str(random.randint(1,1000000000000000000000))
    return os.path.basename(src).replace(".", "_")

# Gets the MIRROR_NAME for a given source file. We use the path of the first
# header it #includes.
def get_mirror_name(src):
    header = None
    with open(src) as f:
        for line in f.readlines():
            if line.startswith("#include"):
                header = line
                break
    header = header[header.index('"') + 1:]
    header = header[:header.index('.')]
    return header


srcs = []

for root, dirs, files in itertools.chain(os.walk("test/unit/src"), os.walk("test/unit/experimental")):
    for name in files:
        if name.endswith(".c") or name.endswith(".cxx"):
            srcs.append(os.path.join(root, name))

ninja = path.join(globalbuild, "build.ninja")
with open(ninja, "w") as out:
    out.write("# This file is auto-generated.\n")
    out.write("# Do not edit it; your changes will be erased.\n")
    out.write("\n")

    # 1.3 for GCC deps
    out.write("ninja_required_version = 1.3\n")
    out.write("\n")

    # run
    out.write("run_wrapper =\n")
    out.write("rule run\n")
    if compiler == "emscripten":
        # Running emscripten requires wasmtime installed.
        out.write(" command = $run_wrapper wasmtime $in\n")
    else:
        out.write(" command = $run_wrapper$in\n")
    out.write("\n")

    out.write("rule compile\n")
    if compiler == "MSVC":
        out.write(" command = " + cc + " /showIncludes $flags /c $in /Fo$out\n")
        out.write(" deps = msvc\n")
    elif compiler == "dmc":
        out.write(" command = " + cc + " $flags -c $in -ooutput$out\n")
        # not bothering to setup deps
    else:
        out.write(" command = ")
        if ccache:
            # ccache's direct mode doesn't work properly on most toy compilers.
            # It misses header files with tinycc, chibicc, kefir, etc. which
            # results in false positives. It's safer to just disable it
            # globally.
            out.write("CCACHE_NODIRECT=true ccache ")
        out.write(cc + " ")
        if hasDeps:
            out.write("-MD -MF $out.d ")
        out.write("$flags -c $in -o $out\n")
        out.write(" deps = gcc\n")
        out.write(" depfile = $out.d\n")
    out.write("\n")

    if generateUnitTestRegistrations:
        out.write("rule generate_unit_test_registrations\n")
        out.write(" command = test/unit/generate-unit-test-registrations.sh $out $in\n")

    out.write("rule link\n")
    if compiler == "MSVC":
        out.write(" command = " + cc.replace("cl", "link") + " @$out.rsp /OUT:$out\n")
        out.write(" rspfile = $out.rsp\n")
        out.write(" rspfile_content = $flags $in\n")
    elif compiler == "dmc":
        out.write(" command = " + cc + " @$out.rsp /ooutput $out\n")
        out.write(" rspfile = $out.rsp\n")
        out.write(" rspfile_content = $flags $in\n")
    else:
        out.write(" command = " + cc + " $in $flags -o $out\n")
    out.write("\n")

    for buildname in sorted(builds.keys()):
        build = builds[buildname]
        buildfolder = path.join(globalbuild, buildname)
        cppflags = build.cppflags
        cflags = build.cflags
        cxxflags = build.cxxflags
        ldflags = build.ldflags
        objs = []

        if compiler == "MSVC":
            # Specify a per-build PDB path so that we don't try to link at the
            # same time a PDB file is being written
            cppflags.append("/Fd" + buildfolder)
            # debug to PDB file
            cppflags += ["/Zi"]
            # Support concurrent PDB writes on VS2013 and later. On VS2012 we
            # pass -j1 to ninja in unit-vs2012.bat. Would be safer to set max
            # parallel compilations to 1 in the ninja file below but I'm not
            # bothering right now.
            # we put /FS last, it seems buggy...
            if compilerVersion >= 1800:
                cppflags += ["/FS"]

        for src in srcs:
            if src.endswith(".cxx"):
                if not compilerSupportsCXX:
                    continue
                flags = cppflags + cxxflags
                objname = src[:-4]
            else:
                flags = cppflags + cflags
                objname = src[:-2]

            mirror_id = get_mirror_id(src)
            mirror_name = get_mirror_name(src)
            #print(src, mirror_id, mirror_name)

            flags += [
                "-DMIRROR_KEY=" + mirror_id,
                "-DMIRROR_NAME=\\\"" + mirror_name + "\\\"",
            ]

            obj = path.join(buildfolder, "objs", objname + obj_extension)
            objs.append(obj)
            out.write("build " + obj + ": compile " + src + "\n")
            out.write(" flags = " + " ".join(flags) + "\n")

        if generateUnitTestRegistrations:
            src = path.join(buildfolder, "mirror_registrations.c")
            obj = path.join(buildfolder, "objs", "mirror_registrations.o")
            out.write("build " + src + ": generate_unit_test_registrations " +
                    " ".join(objs) + "\n");
            out.write("build " + obj + ": compile " + src + "\n")
            out.write(" flags = " + " ".join(cppflags + cflags) + "\n")
            objs.append(obj)

        runner = path.join(buildfolder, "runner") + exe_extension

        out.write("build " + runner + ": link " + " ".join(objs) + "\n")
        out.write(" flags = " + " ".join(ldflags) + "\n")

        # You can omit "run-" in front of any build to just build it without
        # running it. This lets you run it some other way (e.g. under gdb,
        # with/without Valgrind, etc.)
        out.write("build " + buildname + ": phony " + runner + "\n\n")

        out.write("build run-" + buildname + ": run " + runner + "\n")
        if build.run_wrapper:
            run_wrapper = build.run_wrapper
            out.write(" run_wrapper = " + run_wrapper + " ")
            if run_wrapper == "valgrind":
                out.write("--leak-check=full --error-exitcode=1 ")
                #out.write("--suppressions=tools/valgrind-suppressions ")
                out.write("--show-leak-kinds=all --errors-for-leak-kinds=all ")
        out.write("\n")

    out.write("default run-default-debug\n")
    out.write("build default: phony run-default-debug\n")
    out.write("\n")

    # add an "all" target that builds and runs everything
    out.write("build all: phony")
    for build in sorted(builds.keys()):
        if not builds[build].exclude:
            out.write(" run-")
            out.write(build)
    out.write("\n")

    # add a "more" target that builds builds more likely to reveal bugs
    out.write("build more: phony")
    for build in "default-debug", "c++-debug", "c++17-debug", "c++98-debug", "c89-debug", "gnusrc-release":
#    for variant in "default", "c++20", "c89":#, "c++-clr":
#        for conf in "debug", "release":
#            build = variant + "-" + conf
            if build in builds:
                out.write(" run-" + build)
    out.write("\n")

print("Generated " + ninja)

with open(path.join(globalbuild, "help"), "w") as out:
    out.write("\n")
    out.write("Available targets:\n")
    out.write("\n")
    out.write("    (default)\n")
    out.write("    more\n")
    out.write("    all\n")
    out.write("    clean\n")
    out.write("    help\n")
    out.write("\n")
    for build in sorted(builds.keys()):
        out.write("    run-" + build + "\n")
    out.close()

with open(configFile, "w") as out:
    json.dump(config, out, indent=4)
