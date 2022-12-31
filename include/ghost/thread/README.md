# Threading

This is Ghost's threading library.

Ghost's naming conventions for its threading functions are fairly similar to the C11 concurrency support library, with the notable exception that we aren't allergic to vowels.

## Features

### Mutex and Condition

Ghost mutex and condition have many backends:

- `c11`: The standard C11 `mtx_t`, `cnd_t` in `<threads.h>`  https://en.cppreference.com/w/c/thread

- `pthreads`: The standard POSIX threading API: `pthread_mutex_t`, `pthread_condition_t` in `<pthread.h>`

- `winslim`: Windows `SRWLOCK`, `CONDITION_VARIABLE`, etc. (light weight, available since windows Vista)  https://docs.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--locks

- `wincs`: Windows `CRITICAL_SECTION`, `CONDITION_VARIABLE`, etc. (slower, supports recursive)  https://docs.microsoft.com/en-us/windows/win32/sync/critical-section-objects

- `futex`: Linux futex syscall or Windows `WaitOnAddress()` with atomic operations (ultra lightweight, few features) -- This is currently experimental and not used by default.

The Ghost API provides wrappers such as `ghost_mutex_t`. You can use these directly and let Ghost autodetect the platform, or you can choose via macros which backend you'd like Ghost to use.

Ghost declares which backend it is using with macros. For example `GHOST_MUTEX_C11` will be 1 if the C11 backend is being used and 0 otherwise.

TODO fast futex implementations of mutex and condition are not implemented yet.

TODO timing functions are not implemented yet. In the meantime Ghost mutex types are typedefs of the underlying types so you can use platform-specific functions like `pthread_mutex_timedlock()` directly where available.


### Threads

Ghost provides portable wrappers for threads.

Platforms differ in thread support in one key respect: the return value of a thread. On some platforms, threads return `void*`; on others they return `int`. Ghost implements both on all platforms. This makes it easy not only to implement new code but also to port existing code that relies on a particular thread return type. Ghost also provides threads that return `void` for convenience.

The following thread types are available:

- `ghost_vpthread_t`: A handle to a thread returning `void*`. Use this to pass as much information as you like back (via an allocated pointer for example) to a joining thread. On any platform without pthreads (e.g. Windows), this uses auxiliary storage to pass the return value.

- `ghost_ithread_t`: A handle to a thread returning `int`. Use this if you only want to pass an int to a joining thread, for example to return a status code.

- `ghost_vthread_t`: A handle to a thread returning `void`. Use this if you don't care to pass anything via thread return values. This gives you the smallest code and avoids any inefficiencies from mismatched return types.

These thread types are not interchangeable. If you create a thread with `ghost_vpthread_create()`, you must join it with `ghost_vpthread_join()`, exit it with `ghost_vpthread_exit()`, and so on. Ghost protects against misuse by using different types: using the wrong join, detach or id function will not compile. Unfortunately, exit does not take a thread handle so using the wrong exit function may simply crash at runtime. It is critical to be consistent with your thread types.

You can configure which threading backend to use. For example if you want to use pthreads on a platform where it isn't normally detected (such as pthreads-win32 on Windows), pre-define `GHOST_THREAD_PTHREADS` to 1. See `ghost/thread/ghost_thread_config.h` for details.


### Thread IDs

On some platforms, the concept of a thread identifier (for comparing threads) is separate from that of a thread handle (for joining or detaching it.) For this reason Ghost separates the concepts as well.

`ghost_thread_id_t` is a thread identifier. You can get the current thread identifier with `ghost_thread_id_current()`, compare it with `ghost_thread_id_equal()`, or check whether a given id matches the current thread with `ghost_thread_id_is_current()`. This lets you easily assert for example that a callback is being called on the main thread.


## Unsupported Features

### Timed Waits

Ghost does not currently supported timed mutex lock, timed condition wait or timed thread join.

One reason for this is that not all platforms support them. In particular neither `SRWLOCK` nor `CRITICAL_SECTION` on Windows support timed lock. This makes a timed lock function almost pointless in Ghost.

A bigger reason is that platforms differ in how the timeout should be specified.

Windows tends to offer relative timeouts and some platforms (e.g. Solaris) provide this as an extension to pthreads. This is cumbersome in condition loops because in each iteration you need to calculate the elapsed time and subtract it from the time remaining.

POSIX 2004 and C11 only offer absolute timeouts based on a realtime clock. A realtime clock can be unsafe because if the clock is changed in between choosing a time and sleeping, the thread could sleep far longer than intended.

Newer POSIX supports sleeping on a monotonic clock in some cases. This is probably the best solution but it is not widely supported.

In general, timed wait functions are not a good way to use multi-threading. You should prefer to design your threading in a way that timed waits are never necessary.

### Native Thread Exit

Ghost does not currently have a way to exit from native threads. `ghost_ithread_exit()`, `ghost_vpthread_exit()` and `ghost_vthread_exit()` can only be called from threads created by Ghost with the matching type.

It can be occasionally useful to exit from threads created by the system. For example, you may want to exit from the main thread while leaving other threads running. Returning from `main()` would instead exit the process.

Ghost does not implement this because it is not straightforward to do it portably. Not all threads are created equal. For example, Windows has several thread creation mechanisms: `CreateThread()`, `_beginthread()` and `_beginthreadex()`. These must be exited by the corresponding exit function: `ExitThread()`, `_endthread()` and `_endthreadex()`. Using the wrong one can crash or leak resources. [Microsoft's documentation warns](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/beginthread-beginthreadex):

> For an executable file linked with Libcmt.lib, do not call the Win32 `ExitThread` API so that you don't prevent the run-time system from reclaiming allocated resources. `_endthread` and `_endthreadex` reclaim allocated thread resources and then call `ExitThread`.

If you really need to exit a native thread, it is best to do the portability yourself.
