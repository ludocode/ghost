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

#ifndef GHOST_SYSRANDOM_H_INCLUDED
#define GHOST_SYSRANDOM_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Gets random bytes from the system's secure random number generator suitable
 * for cryptographic purposes, storing them in the given buffer.
 *
 * This will block if the system entropy pool has not been initialized (e.g.
 * shortly after boot) or, on some systems, if the system estimates that it has
 * insufficient entropy in the pool.
 *
 * This will call ghost_fatal() (which by default aborts) if any failure occurs
 * in getting random bytes. There is no way to detect or recover from errors.
 * This author considers it too dangerous to attempt to handle such an error
 * safely. If you want to handle errors, use some other means of obtaining
 * random numbers.
 *
 * Note that this is not designed for speed. It should only be used for
 * generating long-lived keys or seeding a fast in-process cryptographic random
 * number generator. For this reason this implementation does not, for example,
 * keep /dev/random open or keep a reference to a cryptographic provider. You
 * should need system randomness rarely enough that it's better to close and
 * re-open the source each time.
 *
 * We call this "sysrandom()" instead of the Linux/FreeBSD-style "getrandom()"
 * because the parameters are different and because we want to emphasize that
 * we're getting it from the system and not an in-process pseudo-random
 * generator.
 *
 * There may be security considerations with accessing random numbers. For
 * example on some platforms this will use /dev/random which may not work in
 * chroot.
 */
void ghost_sysrandom(void* out_buffer, size_t count);
#endif

#ifndef ghost_has_ghost_sysrandom
    #ifdef ghost_sysrandom
        #define ghost_has_ghost_sysrandom 1
    #endif
#endif

/* Security-related stuff in Ghost is experimental. */
#ifndef ghost_has_ghost_sysrandom
    #if !GHOST_EXPERIMENTAL
        #define ghost_has_ghost_sysrandom 0
    #endif
#endif

/* In all cases we need to be able to abort on error. */
#ifndef ghost_has_ghost_sysrandom
    #include "ghost/debug/ghost_fatal.h"
    #if !ghost_has_ghost_fatal
        #define ghost_has_ghost_sysrandom 0
    #endif
#endif

/*
 * Windows
 *
 * Windows has RtlGenRandom() which is used by some portability libraries, e.g.
 * nemequ/portable-snippets. The MSDN documentation warns against this; it
 * suggests CryptGenRandom() instead:
 *
 *     https://learn.microsoft.com/en-us/windows/win32/api/ntsecapi/nf-ntsecapi-rtlgenrandom
 *
 * Windows also has BCryptGenRandom() since Vista SP2. This supports
 * BCRYPT_USE_SYSTEM_PREFERRED_RNG so we wouldn't need to create a provider.
 * Unfortunately this requires linking against Bcrypt.lib:
 *
 *     https://learn.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptgenrandom
 *
 * For now we do it the old way with CryptGenRandom().
 *
 *     https://docs.microsoft.com/en-us/windows/desktop/api/wincrypt/nf-wincrypt-cryptacquirecontexta
 *     https://docs.microsoft.com/en-us/windows/desktop/api/wincrypt/nf-wincrypt-cryptgenrandom
 */
#ifndef ghost_has_ghost_sysrandom
    #ifdef _WIN32
        #define ghost_has_ghost_sysrandom 1

        #include "ghost/header/windows/ghost_windows_h.h"
        #include <wincrypt.h>
        #include <winnt.h>

        #include "ghost/header/c/ghost_limits_h.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/impl/ghost_impl_noinline.h"
        #include "ghost/language/ghost_cold.h"

        GHOST_IMPL_FUNCTION_OPEN
        ghost_cold
        ghost_impl_noinline
        void ghost_sysrandom(void* bytes, ghost_size_t count) GHOST_IMPL_DEF({

            /* Our count is a size_t but the length of CryptGenRandom() is a
             * DWORD which is 32-bit unsigned. It's technically possible to
             * request more than ULONG_MAX bytes on 64-bit systems but we're
             * not going to do something silly like loop on it because such
             * code could never be properly tested. It doesn't make sense to
             * request this much system randomness so if our count is out of
             * range, we assume the count is wrong and abort. */
            if (count > MAXDWORD) {
                ghost_fatal("count out of range");
            }

            /* We pass NULL as the name and PROV_RSA_FULL as the type to get a
             * basic cryptographic provider. This will (most likely) give us
             * the default "Microsoft Base Cryptographic Provider":
             *
             *     https://learn.microsoft.com/en-us/windows/win32/seccrypto/microsoft-base-cryptographic-provider
             *
             * If we fail to acquire the provider the first time with an
             * NTE_BAD_KEYSET error, we should apparently try again with
             * CRYPT_NEWKEYSET. We also pass CRYPT_SILENT to avoid any GUI
             * prompts. */
            HCRYPTPROV provider = 0; /* <-- note: NULL doesn't work here, even though Microsoft's examples say it should */
            if (!CryptAcquireContext(&provider, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT)) {
                if (GetLastError() != NTE_BAD_KEYSET)
                    ghost_fatal("CryptAcquireContext() failed");
                if (!CryptAcquireContext(&provider, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_NEWKEYSET))
                    ghost_fatal("CryptAcquireContext(CRYPT_NEWKEYSET) failed");
            }

            if (!CryptGenRandom(provider, ghost_static_cast(DWORD, count), ghost_static_cast(BYTE*, bytes)))
                ghost_fatal("CryptGenRandom() failed");
            if (!CryptReleaseContext(provider, 0))
                ghost_fatal("CryptReleaseContext() failed");
        })
        GHOST_IMPL_FUNCTION_CLOSE
    #endif
#endif

/* Apple (macOS, iOS, watchOS) */
#ifndef ghost_has_ghost_sysrandom
    #if defined(__APPLE__)
        #define ghost_has_ghost_sysrandom 1

        /*#include "TargetConditionals.h" */
        #include <Security/SecRandom.h>
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_cold.h"
        #include "ghost/type/size_t/ghost_size_t.h"

        GHOST_IMPL_FUNCTION_OPEN
        ghost_cold
        ghost_impl_inline
        void ghost_sysrandom(void* bytes, ghost_size_t count) {
            if (errSecSuccess != SecRandomCopyBytes(kSecRandomDefault, count, bytes)) {
                ghost_fatal("SecRandomCopyBytes() failed");
            }
        }
        GHOST_IMPL_FUNCTION_CLOSE
    #endif
#endif

/*
 * FreeBSD, NetBSD and DragonFlyBSD (but not OpenBSD) have a getrandom() libc
 * call. They return the number of bytes generated and only guarantee up to 256
 * bytes at a time so we loop.
 *
 * Cosmopolitan libc also ports this system call to its various supported OSes.
 *
 * This code isn't used on Linux. It does have this syscall but we handle it
 * separately below.
 */
#ifndef ghost_has_ghost_sysrandom

    /* https://www.freebsd.org/cgi/man.cgi?query=getrandom&sektion=2&apropos=0&manpath=FreeBSD+13.0-RELEASE+and+Ports
     * https://man.netbsd.org/getrandom.2
     * https://man.dragonflybsd.org/?command=getrandom&section=2 */

    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__) \
            || defined(__COSMOPOLITAN__)
        #ifndef __COSMOPOLITAN__
            #include <sys/random.h>
        #endif
        #include "ghost/impl/ghost_impl_noinline.h"
        #include "ghost/error/ghost_errno_is.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/type/ssize_t/ghost_ssize_t.h"
        #include "ghost/language/ghost_cold.h"
        #include "ghost/language/ghost_static_cast.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_cold
        ghost_impl_noinline
        void ghost_sysrandom(void* vbytes, ghost_size_t count) GHOST_IMPL_DEF({
            char* bytes = ghost_static_cast(char*, vbytes);
            while (count > 0) {
                ghost_ssize_t ghost_impl_v_ret = getrandom(bytes, count, 0);
                if (ghost_impl_v_ret == -1) {
                    if (ghost_errno_is(EINTR))
                        continue;
                    ghost_fatal("getrandom() failed");
                }
                bytes += ghost_static_cast(ghost_size_t, ghost_impl_v_ret);
                count -= ghost_static_cast(ghost_size_t, ghost_impl_v_ret);
            }
        })
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_sysrandom 1
    #endif
#endif

/*
 * OpenBSD has getentropy(). The interface is different from getrandom() and it
 * only allows 256 bytes at a time.
 *
 * Emscripten also has getentropy() which has similar behaviour. It doesn't
 * appear to have the 256 byte limitation but we share the code anyway to keep
 * it simple.
 */
#ifndef ghost_has_ghost_sysrandom
    /* TODO Emscripten is currently not working, disable it for now */
    #if defined(__OpenBSD__) /*|| defined(__EMSCRIPTEN__)*/
        #include "ghost/header/posix/ghost_unistd_h.h"
        #include "ghost/impl/ghost_impl_noinline.h"
        #include "ghost/error/ghost_errno_is.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/type/uint8/ghost_uint8_type.h"
        #include "ghost/type/ssize_t/ghost_ssize_t.h"
        #include "ghost/language/ghost_cold.h"
        #include "ghost/language/ghost_static_cast.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_cold
        ghost_impl_noinline
        void ghost_sysrandom(void* ghost_impl_v_vp, ghost_size_t ghost_impl_v_count) GHOST_IMPL_DEF({
            uint8_t* ghost_impl_v_up = ghost_static_cast(uint8_t*, ghost_impl_v_vp);
            while (ghost_impl_v_count > 0) {
                size_t ghost_impl_v_step = (ghost_impl_v_count < 256) ? ghost_impl_v_count : 256;
                int ghost_impl_v_ret = getentropy(ghost_impl_v_up, ghost_impl_v_step);
                if (ghost_impl_v_ret != 0) {
                    /* The man page doesn't specify EINTR as a possible error
                     * (which probably has something to do with why it limits
                     * to 256 bytes.) We check just in case. */
                    if (ghost_errno_is(EINTR))
                        continue;
                    ghost_fatal("getentropy() failed");
                }
                ghost_impl_v_up += ghost_impl_v_step;
                ghost_impl_v_count -= ghost_impl_v_step;
            })
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_sysrandom 1
    #endif
#endif

/*
 * Linux 3.19 supports a getrandom() system call.
 *
 *     https://man.archlinux.org/man/getrandom.2
 *
 * We want to support older Linux (especially on Android.) We don't want to
 * depend on the libc supporting it and we want our code to run even on older
 * kernels that don't have the system call. For this reason we call the system
 * call directly if possible and if it fails we fall back to /dev/random.
 *
 * (We do for now require that the kernel headers are available and that they
 * declare the getrandom syscall. If they don't we'll just use /dev/random.
 * This probably doesn't make sense, since kernel headers that declare the
 * syscall will support it; we may need to hardcode the syscall number for
 * various architectures.)
 *
 * Only Android devices that launched with Android 7.0 (Nougat) or later
 * support the syscall (and not devices that upgraded to it):
 *
 *     https://android.stackexchange.com/a/51656
 *
 * While it seems obsolete to preserve the fallback, devices like the Fairphone
 * 2 are still supported in 2022 on kernel 3.4. There are probably a great many
 * devices (not just Android phones) stuck on old Linux kernels.
 * ghost_sysrandom() must work on all of them.
 */
#ifdef GHOST_IMPL_SYSRANDOM_LINUX_FALLBACK
    #error "You cannot pre-define GHOST_IMPL_SYSRANDOM_LINUX_FALLBACK."
#endif
#ifndef ghost_has_ghost_sysrandom
    #ifdef __linux__
        #include "ghost/system/ghost_syscall.h"
        #if ghost_has_ghost_syscall && defined(SYS_getrandom)
            #include "ghost/impl/ghost_impl_noinline.h"
            #include "ghost/type/size_t/ghost_size_t.h"
            #include "ghost/type/ssize_t/ghost_ssize_t.h"
            #include "ghost/language/ghost_cold.h"
            #include "ghost/language/ghost_static_cast.h"
            #include "ghost/error/ghost_errno_is.h"

            GHOST_IMPL_FUNCTION_OPEN

            #define GHOST_IMPL_SYSRANDOM_LINUX_FALLBACK
            ghost_cold
            ghost_impl_noinline
            void ghost_impl_sysrandom_fallback(void* bytes, ghost_size_t count);

            ghost_cold
            ghost_impl_noinline
            void ghost_sysrandom(void* vbytes, ghost_size_t count) GHOST_IMPL_DEF({
                char* bytes = ghost_static_cast(char*, vbytes);
                while (count > 0) {

                    /* Note that even though the fallback uses /dev/random and not
                     * /dev/urandom, we don't pass the GRND_RANDOM flag here.
                     * Without it getrandom() is still guaranteed to block until the
                     * entropy pool is initialized but will not block otherwise, which is
                     * is actually the behaviour we want. */
                    ghost_ssize_t ghost_impl_v_ret = ghost_syscall(SYS_getrandom, bytes, count, 0);
                    if (ghost_impl_v_ret == -1) {

                        /* On ENOSYS, fallback to /dev/random. We don't
                         * bother to cache this result. This is supposed to
                         * be called rarely so we'll just try the system
                         * call again next time. */
                        if (ghost_errno_is(ENOSYS)) {
                            ghost_impl_sysrandom_fallback(bytes, count);
                            return;
                        }

                        /* Restart on EINTR. Note that on Linux, once the entropy pool
                         * is initialized this should only be possible when requesting
                         * more than 256 bytes. */
                        if (ghost_errno_is(EINTR))
                            continue;

                        /* Unrecoverable error. */
                        ghost_fatal("syscall(SYS_getrandom) failed");
                    }
                    bytes += ghost_static_cast(ghost_size_t, ghost_impl_v_ret);
                    count -= ghost_static_cast(ghost_size_t, ghost_impl_v_ret);
                }
            })
            GHOST_IMPL_FUNCTION_CLOSE
            #define ghost_has_ghost_sysrandom 1
        #endif
    #endif
#endif

/*
 * UNIX/POSIX has /dev/random. On Linux this may be a fallback.
 *
 * Emscripten is supposed to set up a virtual device for this but for some
 * reason it doesn't work.
 */
#if !defined(ghost_has_ghost_sysrandom) || defined(GHOST_IMPL_SYSRANDOM_LINUX_FALLBACK)
    #include "ghost/detect/ghost_unix.h"
    #if (GHOST_UNIX || defined(GHOST_IMPL_SYSRANDOM_LINUX_FALLBACK)) && !defined(__EMSCRIPTEN__)

        /*
         * Open and read from /dev/random.
         *
         * This is a fallback implementation on Linux and the primary
         * implementation on any UNIX without a dedicated getrandom()-style
         * function.
         *
         * There are limitations, for example it may not work in chroot, and it
         * may block if the system decides there isn't enough entropy (see the
         * note below.)
         */

        #include "ghost/impl/ghost_impl_noinline.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/type/ssize_t/ghost_ssize_t.h"
        #include "ghost/io/ghost_close_nointr.h"

        /* TODO check which of these headers is required, wrap them properly */
        #ifndef __COSMOPOLITAN__
            #include <sys/stat.h>
            #include <fcntl.h>
        #endif

        #include "ghost/header/posix/ghost_unistd_h.h"
        #include "ghost/error/ghost_errno_is.h"
        #include "ghost/language/ghost_cold.h"
        #include "ghost/language/ghost_static_cast.h"

        GHOST_IMPL_FUNCTION_OPEN
        ghost_cold
        ghost_impl_noinline
        void
            #ifdef GHOST_IMPL_SYSRANDOM_LINUX_FALLBACK
                ghost_impl_sysrandom_fallback
            #else
                ghost_sysrandom
            #endif
                (void* vbytes, ghost_size_t count)
        #if !GHOST_EMIT_DEFS
        ;
        #else
        {
            char* bytes = ghost_static_cast(char*, vbytes);
            int fd;
            for (;;) {

                /*
                 * On at least FreeBSD and macOS, /dev/random and /dev/urandom are
                 * the same thing. On Linux, these have not yet been unified, and not
                 * for lack of trying:
                 *
                 *     https://news.ycombinator.com/item?id=30848973
                 *
                 * We'd like a device that only blocks until the entropy pool is
                 * initialized and never blocks afterwards. This is how it works on
                 * FreeBSD and macOS. On Linux this is also how the getrandom() system
                 * call behaves, but unfortunately on Linux neither /dev/random nor
                 * /dev/urandom behave this way.
                 *
                 * On Linux, /dev/urandom will never block and can technically return
                 * data before the entropy pool is initialized. Conversely, /dev/random
                 * will block until the entropy pool is initialized but will also block
                 * if an estimate of entropy in the pool falls below some threshold.
                 *
                 * To avoid the possibility of receiving data before the entropy pool
                 * is initialized (on Linux or any other UNIX), this implementation
                 * uses /dev/random everywhere.
                 *
                 * (Update: Linux is apparently finally making progress on unifying
                 * these, and the latest kernels may already do so when you read
                 * this. If so, it won't matter which one we use so we stick with
                 * /dev/random.)
                 */

                fd = open("/dev/random", O_RDONLY);
                if (fd == -1) {
                    if (ghost_errno_is(EINTR))
                        continue;
                    ghost_fatal("open(/dev/random) failed");
                }
                break;
            }

            while (count > 0) {
                ghost_ssize_t ghost_impl_v_ret = read(fd, bytes, count);
                if (ghost_impl_v_ret == -1) {
                    if (ghost_errno_is(EINTR))
                        continue;
                    ghost_fatal("read() from /dev/random failed");
                }
                bytes += ghost_static_cast(ghost_size_t, ghost_impl_v_ret);
                count -= ghost_static_cast(ghost_size_t, ghost_impl_v_ret);
            }

            ghost_close_nointr(fd);
        }
        #endif
        GHOST_IMPL_FUNCTION_CLOSE

        #ifdef GHOST_IMPL_SYSRANDOM_LINUX_FALLBACK
            #undef GHOST_IMPL_SYSRANDOM_LINUX_FALLBACK
        #else
            #define ghost_has_ghost_sysrandom 1
        #endif
    #endif
#endif

/* No support for ghost_sysrandom(). */
#ifndef ghost_has_ghost_sysrandom
    #define ghost_has_ghost_sysrandom 0
#endif

#endif
