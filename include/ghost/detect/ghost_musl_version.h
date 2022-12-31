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

#ifndef GHOST_MUSL_VERSION_H_INCLUDED
#define GHOST_MUSL_VERSION_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * @def GHOST_MUSL_VERSION (major*1000000 + minor*1000 + patch)
 *
 * A lower bound for the version of musl.
 *
 * This is defined if and only if Ghost believes that the libc is musl (i.e.
 * GHOST_MUSL is 1.)
 *
 * Use it like this:
 *
 *      #include "ghost/detect/ghost_musl_version.h"
 *      #if GHOST_MUSL
 *          #if GHOST_MUSL_VERSION >= 1002000
 *              // This is musl 1.2.0 or later.
 *          #endif
 *      #endif
 *
 * Ghost guesses the musl version by probing what header files are available
 * and what macros they define. It may be inaccurate especially if you are on
 * an esoteric architecture or if you are compiling against a customized
 * version of musl. When it is inaccurate, it should hopefully detect an
 * earlier version than the target rather than a later one.
 *
 * Remember that you can pre-define GHOST_MUSL_VERSION yourself to override
 * this if it guesses wrong, just as you can override any other Ghost symbol
 * that incorrectly detects musl support.
 *
 * If you are building your own distribution or embedded system based on musl,
 * you can add a definition of __x_musl_version__ in this format to your
 * <features.h> and Ghost will use it.
 *
 * @see GHOST_MUSL
 */
#endif

/*
 * The musl developers *love* configure scripts. They believe the only way you
 * should be able to detect what features the platform supports is by compiling
 * and running a test program.
 *
 * I *hate* configure scripts. I think "compile a test program" is a horrible
 * brain-damaged way of detecting the capabilities of the platform. Configure
 * scripts are glacially slow, they are unreliable, they take an enormous
 * amount of work to maintain, they give fuzzy information, they are a
 * ridiculous burden on source-only libraries, they are agonizing to integrate
 * with buildsystems, they don't work properly on non-UNIX platforms, and they
 * are always a cross-compilation disaster.
 *
 * I want to be able to compile my app by doing `cc *.c`. I want that to work
 * out of the box on any platform. This is half the point of Ghost.
 *
 * musl intentionally makes this impossible. Want to know if the platform
 * supports C11 threads? Or has qsort_r()? Or whether time_t is 32 or 64 bits?
 * They won't tell you. They obfuscate it on purpose.
 *
 * The only way they want you to be able to find out is to compile a test
 * program and store the results in some config file that you use in your
 * build. The idea of just compiling your code and expecting it to work (like
 * every other programming language) is just some nonsense to them.
 *
 * "Hey guys, what about the increasingly popular single-file header-only
 * libraries? Am I supposed to ship a configure script and force my users to go
 * through a per-platform install process, or have them write their own
 * configure tests and generate a config.h just to use my little header file?"
 * Go ahead, ask them. They literally do not read the question:
 *
 *     https://www.openwall.com/lists/musl/2022/04/17/1
 *     > [long rant of wrong stuff I did not read]
 *
 * They claim it's a bug to assume a platform has certain features without
 * testing it. Fine, okay, then why not just directly TELL US what features you
 * have? When they finally caved after a decade and added qsort_r(), why would
 * they not also define __has_gnu_qsort_r so we can tell with the preprocessor
 * that it's safe to use? Why does "testing" have to involve compiling a test
 * program or doing some other out-of-language hack instead of using the actual
 * features of the language?
 *
 * To their credit, they have suggested adding macros like _EXT_QSORT_R. The
 * problem is they won't to do it unless they can convince all of the other
 * libc implementations to do it too. Of course they ignore the fact that it's
 * unnecessary on every other libc because every other libc just tells us who
 * they are! And since no other libc has any urgency to actually do this, it
 * will take decades to get standardized. What are we supposed to do in the
 * meantime? They simply don't care.
 *
 * Here's the full discussion I had with the musl devs for your reading
 * pleasure:
 *
 *     https://www.openwall.com/lists/musl/2022/04/16/
 *     https://www.openwall.com/lists/musl/2022/04/17/
 *     https://www.openwall.com/lists/musl/2022/04/19/
 *
 * And here's a blog post and Hacker News discussion about it:
 *
 *     https://catfox.life/2022/04/16/the-musl-preprocessor-debate/
 *     https://news.ycombinator.com/item?id=31067059
 *
 * In the end the musl devs recommend that I ignore their features and
 * re-implement them myself. Yes, really.
 *
 * Well I'm not willing to do that. The point of Ghost is to work around
 * whatever uglyness is needed to use the platform as much as possible. I am
 * committing to that here.
 *
 * The below code attempts to define a version of musl using purely the
 * preprocessor.
 *
 * Yes, we will fail to detect backported or disabled features (like when
 * Alpine backported qsort_r() to its musl 1.2.2) and we will fail to detect
 * versions that made no preprocessor-detectable changes. That's fine. It
 * doesn't have to be perfect. It just has to be good enough to auto-configure
 * most of the time. Everything in Ghost can be configured manually so users
 * can always override it when needed. The absolute worst possible outcome of
 * all this is that Ghost auto-detects wrong and you are forced to write a
 * configure script to fix it, which is exactly what the musl devs want to
 * force you to do anyway.
 *
 * I am open to any and all hacks to better detect musl regardless of the musl
 * developers' desires. We should try to stick to the public API to avoid
 * future breakage but I'm not above detecting internal macros, their header
 * guards, the existence of internal files, etc. Please help me improve this
 * code.
 */

/*
 * The override for this is handled in ghost_musl.h. We'll also need to know
 * if we're actually on musl before trying to guess the version.
 */
#ifndef ghost_has_GHOST_MUSL_VERSION
    #include "ghost/detect/ghost_musl.h"
#endif

/* If we're not musl, we don't have a musl version. */
#ifndef ghost_has_GHOST_MUSL_VERSION
    #if !GHOST_MUSL
        #define ghost_has_GHOST_MUSL_VERSION 0
    #endif
#endif

/* In case distributions want to define the musl version themselves, we'll
 * accept __x_musl_version__ in this format. We don't want to force any
 * particular format on a future __musl_version__ macro. */
#ifndef ghost_has_GHOST_MUSL_VERSION
    #include <features.h>
    #ifdef __x_musl_version__
        #define GHOST_MUSL_VERSION __x_musl_version__
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/*
 * Our main strategy is looking for macros that were added in particular
 * versions of musl. We also test when header files were added if we have
 * __has_include.
 *
 * This detection can be fuzzy. There are many ways it can fail:
 *
 * - One of the types of macros we detect often below are syscalls. It's
 *   possible that some syscalls we detect are not available on certain
 *   architectures. If so we should fix them below.
 *
 * - It's possible that distributions will backport features to older versions
 *   of musl. For this reason we test many different macros if possible and we
 *   require that they all exist to ensure that we're not detecting a backport.
 *
 * - It's possible that distributions will remove a feature (like a syscall)
 *   or even entire headers that we depend on to detect a version.
 *
 * - There is some complexity involved when patches were made to multiple
 *   release series concurrently. For example <bits/poll.h> was added in musl
 *   1.1.7 and musl 1.0.5.
 *
 * In all cases of failed detection, the below code is designed to fallback to
 * an older version. Incorrectly detecting a newer version should be avoided as
 * much as possible.
 *
 * Most uses of GHOST_MUSL_VERSION in Ghost are to enable the use of some
 * feature of the libc. If we don't detect that it's available, Ghost has its
 * own fallbacks, so the only real downside of an incorrect version detection
 * is not using a feature of the libc that we otherwise could. If you are using
 * this version detection for something more sensitive, you will need to be
 * more careful. Please help me improve this code.
 *
 * The below checks are not written in a "cascading" way, i.e. the checks for
 * 1.2.3 don't require that all the checks for 1.2.2 pass, and so on. This is
 * in case of distribution customizations, we don't want our version checks to
 * stop counting up just because some macro from many versions ago has been
 * removed. Instead we set "baseline" checks, currently at 1.2.X and 1.1.X, and
 * all versions afterwards need only pass all of the checks in the baseline.
 * See GHOST_IMPL_MUSL_1_2_X below for example. This also lets us check in
 * reverse order, from newer to older, so the detection can stop as soon as
 * possible.
 *
 * The script test/test-musl.sh downloads all supported versions of musl,
 * builds their header files and tests that this file properly detects the
 * version. The below code was derived by diffing the x86_64 header files
 * against each other. If you are on Linux (especially on an esoteric
 * architecture) please run the script and confirm that it passes on your
 * machine.
 */



/* musl 1.2.x series */

/* musl 1.2 added an internal __REDIR() macro to rename a bunch of functions to
 * implement its time64 support. We detect this plus a few other things. */
#ifdef GHOST_IMPL_MUSL_1_2_X
    #error
#endif
#ifndef ghost_has_GHOST_MUSL_VERSION
    #include <sys/syscall.h>
    #include <sys/resource.h>
    #include <features.h>
    #if defined(__NR_pidfd_open) && defined(__NR_clone3) && \
            defined(RLIMIT_RTTIME) && \
            defined(__REDIR)
        #define GHOST_IMPL_MUSL_1_2_X
    #endif
#endif

/* musl 1.2.3 added qsort_r(), but they won't tell us they have it, which is
 * what prompted this whole ordeal in the first place. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_1_2_X)
    #include <sys/syscall.h>
    #if defined(__NR_process_madvise) && defined(__NR_epoll_pwait2) && \
            defined(__NR_mount_setattr) && defined(__NR_landlock_create_ruleset) && \
            defined(__NR_landlock_add_rule) && defined(__NR_landlock_restrict_self)
        #define GHOST_MUSL_VERSION 1002003
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.2.2 added lots of stuff but all we can detect are these syscalls. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_1_2_X)
    #include <sys/syscall.h>
    #if defined(__NR_close_range) && defined(__NR_openat2) && \
            defined(__NR_pidfd_getfd) && defined(__NR_faccessat2)
        #define GHOST_MUSL_VERSION 1002002
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.2.1 added PTHREAD_NULL. This could be backported or defined by the
 * user so this is not super accurate. The major differences between 1.2.1 and
 * 1.2.0 are not in the API anyway, they're more about optimizations in things
 * like malloc(), memcpy(), etc. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_1_2_X)
    #include <pthread.h>
    #if defined(PTHREAD_NULL)
        #define GHOST_MUSL_VERSION 1002001
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* We detected the musl 1.2 series above, so if we haven't found a later patch,
 * we're 1.2.0. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_1_2_X)
    #define GHOST_MUSL_VERSION 1002000
    #define ghost_has_GHOST_MUSL_VERSION 1
#endif



/* musl 1.1.x series */

/* musl 1.1.0 added <sys/auxv.h>. This is about the only detectable change
 * between 1.0.5 and 1.1.0, but we want to check it in all 1.1.x releases
 * anyway. We need __has_include to detect it so it's a MAYBE. */
#ifdef GHOST_IMPL_MUSL_MAYBE_1_1_X
    #error
#endif
#ifndef ghost_has_GHOST_MUSL_VERSION
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<sys/auxv.h>)
            #define GHOST_IMPL_MUSL_MAYBE_1_1_X
        #endif
    #else
        #define GHOST_IMPL_MUSL_MAYBE_1_1_X
    #endif
#endif

/* musl 1.1.24 added <bits/ipcstat.h>, various syscalls, and some <glob.h>
 * macros which we test. A few other things are not worth testing. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #ifdef GHOST_IMPL_MAYBE_MUSL_1_1_24
        #error
    #endif
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<bits/poll.h>)
            #define GHOST_IMPL_MAYBE_MUSL_1_1_24
        #endif
    #else
        #define GHOST_IMPL_MAYBE_MUSL_1_1_24
    #endif
    #ifdef GHOST_IMPL_MAYBE_MUSL_1_1_24
        #undef GHOST_IMPL_MAYBE_MUSL_1_1_24
        #include <sys/syscall.h>
        #include <glob.h>
        #if defined(__NR_open_tree) && defined(__NR_move_mount) && defined(__NR_fsopen) && \
                    defined(__NR_fsconfig) && defined(__NR_fsmount) && defined(__NR_fspick) && \
                defined(GLOB_TILDE) && defined(GLOB_TILDE_CHECK)
            #define GHOST_MUSL_VERSION 1001024
            #define ghost_has_GHOST_MUSL_VERSION 1
        #endif
    #endif
#endif

/* musl 1.1.23 */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <sys/syscall.h>
    #include <fcntl.h>
    #if defined(__NR_pidfd_send_signal) && defined(__NR_io_uring_setup) && \
                defined(__NR_io_uring_enter) && defined(__NR_io_uring_register) && \
            defined(O_TTY_INIT)
        #define GHOST_MUSL_VERSION 1001023
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.22 added a few additional sizes for huge pages. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <sys/inotify.h>
    #include <sys/mman.h>
    #if defined(IN_MASK_CREATE) && \
            defined(MAP_HUGE_32MB) && defined(MAP_HUGE_512MB)
        #define GHOST_MUSL_VERSION 1001022
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.21 has some syscalls and not much else. We normally avoid
 * networking but here we resort to checking some socket constants. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <sys/syscall.h>
    #include <sys/socket.h>
    #if defined(__NR_io_pgetevents) && defined(__NR_rseq) && \
            defined(PF_XDP) && defined(AF_XDP)
        #define GHOST_MUSL_VERSION 1001021
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.20 adds a lot of stuff to <sys/mman.h>, including huge pages. A few
 * huge page sizes are added later to 1.22 which we check above. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <sys/mman.h>
    #include <sys/msg.h>
    #include <sys/prctl.h>
    #if defined(MAP_SHARED_VALIDATE) && defined(MAP_SYNC) && defined(MAP_FIXED_NOREPLACE) && \
                defined(MAP_HUGE_SHIFT) && defined(MAP_HUGE_MASK) && \
                defined(MAP_HUGE_64KB) && defined(MAP_HUGE_1MB) && defined(MAP_HUGE_16GB) && \
            defined(MSG_STAT_ANY) && \
            defined(PR_SVE_SET_VL) && defined(PR_SVE_SET_VL_ONEXEC) && \
                defined(PR_GET_SPECULATION_CTRL) && defined(PR_SPEC_STORE_BYPASS) && \
                defined(PR_SPEC_NOT_AFFECTED) && defined(PR_SPEC_PRCTL) && \
                defined(PR_SPEC_ENABLE) && defined(PR_SPEC_FORCE_DISABLE)
        #define GHOST_MUSL_VERSION 1001020
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.19 */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <sys/syscall.h>
    #include <sys/timerfd.h>
    #include <sys/xattr.h>
    #include <dirent.h>
    #if defined(__NR_statx) && \
            defined(TFD_TIMER_CANCEL_ON_SET) && \
            defined(_DIRENT_HAVE_D_RECLEN) && defined(_DIRENT_HAVE_D_OFF) && \
                defined(_DIRENT_HAVE_D_TYPE) && \
            defined(__UAPI_DEF_XATTR)
        #define GHOST_MUSL_VERSION 1001019
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.18 made no include/ changes. It will be detected as 1.1.17. */

/* musl 1.1.17. There's a new macro in <bits/ioctl.h> as well but that might be
 * architecture-specific. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <langinfo.h>
    #include <spawn.h>
    #if defined(_NL_LOCALE_NAME) && \
            defined(POSIX_SPAWN_USEVFORK) && defined(POSIX_SPAWN_SETSID)
        #define GHOST_MUSL_VERSION 1001017
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.16 added <bits/link.h> and <bits/hwcap.h>. We detect them if we
 * have __has_include(). */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #ifdef GHOST_IMPL_MAYBE_MUSL_1_1_16
        #error
    #endif
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<bits/link.h>) && __has_include(<bits/hwcap.h>)
            #define GHOST_IMPL_MAYBE_MUSL_1_1_16
        #endif
    #else
        #define GHOST_IMPL_MAYBE_MUSL_1_1_16
    #endif
    #ifdef GHOST_IMPL_MAYBE_MUSL_1_1_16
        #undef GHOST_IMPL_MAYBE_MUSL_1_1_16
        #include <sys/syscall.h>
        #include <unistd.h>
        #if defined(__NR_pkey_mprotect) && defined(__NR_pkey_alloc) && \
                defined(__NR_pkey_free) && \
                defined(_CS_V6_ENV) && defined(_CS_V7_ENV)
            #define GHOST_MUSL_VERSION 1001016
            #define ghost_has_GHOST_MUSL_VERSION 1
        #endif
    #endif
#endif

/* musl 1.1.15 */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <sys/syscall.h>
    #if defined(__NR_copy_file_range) && defined(__NR_preadv2) && \
            defined(__NR_pwritev2)
        #define GHOST_MUSL_VERSION 1001015
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.14 made no include/ changes. It will be detected as 1.1.13. */

/* musl 1.1.13 added lots. We avoid the networking stuff. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <sys/syscall.h>
    #include <sys/mman.h>
    #include <sys/mount.h>
    #include <sys/prctl.h>
    #if defined(__NR_userfaultfd) && defined(__NR_membarrier) && \
            defined(__NR_mlock2) && \
            defined(MCL_ONFAULT) && \
            defined(MS_LAZYTIME) && \
            defined(PR_CAP_AMBIENT) && defined(PR_CAP_AMBIENT_IS_SET) && \
                defined(PR_CAP_AMBIENT_RAISE) && defined(PR_CAP_AMBIENT_LOWER) && \
                defined(PR_CAP_AMBIENT_CLEAR_ALL)
        #define GHOST_MUSL_VERSION 1001013
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.12 added some macros to <elf.h> */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <elf.h>
    #if defined(R_SH_GOT20) && defined(R_SH_GOTOFF20) && \
            defined(R_SH_GOTFUNCDESC) && defined(R_SH_GOTFUNCDEST20) && \
            defined(R_SH_GOTOFFFUNCDESC) && defined(R_SH_GOTOFFFUNCDEST20) && \
            defined(R_SH_FUNCDESC) && defined(R_SH_FUNCDESC_VALUE)
        #define GHOST_MUSL_VERSION 1001012
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.11 made isascii() into a macro. It doesn't really seem safe to
 * detect this since the macro could be backported or could come from user code
 * so we ignore it. 1.1.11 will be detected as 1.1.9. */

/* musl 1.1.10 added a few large file constants that are only available under
 * certain feature flags. It's safer to ignore them. 1.1.10 will be detected as
 * 1.1.9. */

/* musl 1.1.9. We're checking some networking constants and some prctl()
 * floating point constants here. It would be nice to not depend on networking
 * or floats but there are no other detectable changes. In any case it looks
 * like these macros aren't hidden on machines without networking or floating
 * point support. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <sys/prctl.h>
    #if defined(IP_CHECKSUM) && \
            defined(IPTOS_CLASS_MASK) && defined(IPTOS_CLASS) && defined(IPTOS_CLASS_DEFAULT) && \
            defined(PR_MPX_ENABLE_MANAGEMENT) && defined(PR_GET_FP_MODE) && defined(PR_FP_MODE_FR)
        #define GHOST_MUSL_VERSION 1001009
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.8 has no changes detectable to the preprocessor. It will appear as
 * 1.1.7. */

/* musl 1.1.7 added a lot of stuff. It added <bits/poll.h>, which was also
 * added to 1.0.5 at the same time. It also removed some syscall aliases. We
 * check that at least one of them was removed. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #ifdef GHOST_IMPL_MAYBE_MUSL_1_1_7
        #error
    #endif
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<bits/poll.h>)
            #define GHOST_IMPL_MAYBE_MUSL_1_1_7
        #endif
    #else
        #define GHOST_IMPL_MAYBE_MUSL_1_1_7
    #endif
    #ifdef GHOST_IMPL_MAYBE_MUSL_1_1_7
        #undef GHOST_IMPL_MAYBE_MUSL_1_1_7
        #include <sys/syscall.h>
        #include <sys/socket.h>
        #include <pthread.h>
        #if defined(__NR_execveat) && \
                (!defined(__NR_fstatat) || !defined(__NR_pread) || !defined(__NR_pwrite) || \
                    !defined(__NR_getdents) || !defined(__NR_fadvise)) && \
                defined(SO_INCOMING_CPU) && defined(SO_ATTACH_BPF) && defined(SO_DETACH_BPF) && \
                defined(PTHREAD_CANCEL_MASKED)
            #define GHOST_MUSL_VERSION 1001007
            #define ghost_has_GHOST_MUSL_VERSION 1
        #endif
    #endif
#endif

/* musl 1.1.6 */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <sys/syscall.h>
    #include <arpa/nameser.h>
    #if defined(__NR_kexec_file_load) && defined(__NR_bpf) && \
            defined(ns_msg_getflag)
        #define GHOST_MUSL_VERSION 1001006
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.5 added <threads.h> and <uchar.h>. It also added some new syscalls
 * and a few other testable things. We don't bother with net or math changes. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #ifdef GHOST_IMPL_MAYBE_MUSL_1_1_5
        #error
    #endif
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<threads.h>) && __has_include(<uchar.h>)
            #define GHOST_IMPL_MAYBE_MUSL_1_1_5
        #endif
    #else
        #define GHOST_IMPL_MAYBE_MUSL_1_1_5
    #endif
    #ifdef GHOST_IMPL_MAYBE_MUSL_1_1_5
        #undef GHOST_IMPL_MAYBE_MUSL_1_1_5
        #include <sys/syscall.h>
        #include <time.h>
        #include <fcntl.h>
        #if defined(__NR_seccomp) && defined(__NR_getrandom) && defined(__NR_memfd_create) && \
                defined(TIME_UTC) && defined(F_OFD_GETLK)
            #define GHOST_MUSL_VERSION 1001005
            #define ghost_has_GHOST_MUSL_VERSION 1
        #endif
    #endif
#endif

/* musl 1.1.4 added a few things. we don't bother with the <elf.h> or netinit/
 * changes.*/
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <sys/syscall.h>
    #include <sys/prctl.h>
    #if defined(__NR_renameat2) && \
            defined(PR_SET_THP_DISABLE) && defined(PR_GET_THP_DISABLE)
        #define GHOST_MUSL_VERSION 1001004
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.3 added <fmtmsg.h>. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<fmtmsg.h>)
            #define GHOST_MUSL_VERSION 1001003
            #define ghost_has_GHOST_MUSL_VERSION 1
        #endif
    #endif
#endif

/* musl 1.1.2 added lots of stuff. Syscalls are easy to test. We test a few
 * other things to make sure we're not catching backports. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <sys/syscall.h>
    #include <sys/socket.h>
    #include <sched.h>
    #if defined(__NR_sched_setattr) && defined(__NR_sched_getattr) && \
            defined(SO_BPF_EXTENSIONS) && \
            defined(SCHED_DEADLINE)
        #define GHOST_MUSL_VERSION 1001002
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* musl 1.1.1 removed many sysconf() variables. We test that we don't have
 * _SC_CHAR_BIT. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && defined(GHOST_IMPL_MUSL_MAYBE_1_1_X)
    #include <unistd.h>
    #ifndef _SC_CHAR_BIT
        #define GHOST_MUSL_VERSION 1001001
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* If we have __has_include support, we've detected musl 1.1.x series above and
 * we haven't found a later patch, so we're musl 1.1.0.
 * If we don't have __has_include support, we can't confirm that we're 1.1.0 so
 * we have no choice but to fallback to the 1.0.x series and keep looking. */
#if !defined(ghost_has_GHOST_MUSL_VERSION) && \
        defined(GHOST_IMPL_MUSL_MAYBE_1_1_X) && \
        ghost_has(ghost_has_include)
    #define GHOST_MUSL_VERSION 1001000
    #define ghost_has_GHOST_MUSL_VERSION 1
#endif



/* musl 1.0.x series */

/* musl 1.0.5 added <bits/poll.h>. It has no other detectable changes.
 * If __has_include() is not supported, 1.0.5 will be detected as 1.0.0 */
#ifndef ghost_has_GHOST_MUSL_VERSION
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<bits/poll.h>)
            #define GHOST_MUSL_VERSION 1000005
            #define ghost_has_GHOST_MUSL_VERSION 1
        #endif
    #endif
#endif

/* musl 1.0.2 through 1.0.4 have no detectable changes. The version will be
 * reported as 1.0.1 or 1.0.0 for all of them. */

/* musl 1.0.1 added <bits/resource.h>. It has no other detectable changes.
 * If __has_include() is not supported, 1.0.1 will be detected as 1.0.0 */
#ifndef ghost_has_GHOST_MUSL_VERSION
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<bits/resource.h>)
            #define GHOST_MUSL_VERSION 1000001
            #define ghost_has_GHOST_MUSL_VERSION 1
        #endif
    #endif
#endif

/* musl 1.0.0 doesn't have a ton of stuff over 0.9.9. We have a few
 * <sys/socket.h> macros and a lot of <elf.h> stuff so we pick a few at random. */
#ifndef ghost_has_GHOST_MUSL_VERSION
    #include <sys/socket.h>
    #include <elf.h>
    #if defined(SOL_IP) && defined(SOL_IPV6) && defined(SOL_ICMPV6) && \
            defined(EF_MIPS_NAN2008) && \
                defined(R_AARCH64_ABS16) && defined(R_AARCH64_JUMP26) && \
                defined(R_AARCH64_TLSDESC_ADD) && defined(R_AARCH64_TLSLD_LDST128_DTPREL_LO12_NC)
        #define GHOST_MUSL_VERSION 1000000
        #define ghost_has_GHOST_MUSL_VERSION 1
    #endif
#endif

/* 1.0.0 was first released in 2014. For now we don't bother to go back any
 * farther. We're pretty sure we're musl so we just set the version to 0.0.1. */
#ifndef ghost_has_GHOST_MUSL_VERSION
    #define GHOST_MUSL_VERSION 1
    #define ghost_has_GHOST_MUSL_VERSION 1
#endif



#undef GHOST_IMPL_MUSL_1_2_X
#undef GHOST_IMPL_MUSL_MAYBE_1_1_X

#endif
