`ghost/debug/` defines tools for debugging. These wrap platform-specific features such as stopping on error (`ghost_abort()`, `ghost_debugbreak()`) and getting source code context (e.g. `GHOST_PRETTY_FUNCTION`). These are then wrapped in assertion macros to make it easy to debug code on any platform.

## Assertions

There are three assertion macros provided by Ghost, plus an optimization macro that behaves as an assertion in debug builds. These are:

- `ghost_assert()` - Like the traditional `assert()` macro: in debug, evaluates its condition and aborts if false; but elides its condition and compiles to nothing in release.
- `ghost_check()` - Like `ghost_assert()`, but it evaluates and ignores its condition in release builds (or on platforms that cannot abort) to avoid code with side effects from being stripped.
- `ghost_ensure()` - Like `ghost_assert()`, but it checks its condition and aborts if false even in release builds.
- `ghost_assume()` - Like `ghost_assert()`, but in release builds, tells the compiler to assume that the condition cannot possibly be false.

All of these macros take an optional message parameter. Upon failure, they all call `ghost_assert_fail()` with the source code context; see the next section.

Note that `ghost_assume()` is not technically a debugging macro. It is more of an optimization macro. It is meaningful beyond error checking so it is in `ghost/language/` rather than `ghost/debug/`. It just happens to behave like a debug macro in debug mode.

In debug builds, all of these macros behave the same: if the condition is false, the program aborts. `ghost_ensure()` also behaves this way in release. The behaviour of the other macros differs in release builds only. The differences can be summed up with the following table:

|                        | **Evaluates condition** | **Aborts if not condition** | **Undefined behaviour if not condition** | **Exists if no abort()**          |
|------------------------|-------------------------|-----------------------------|------------------------------------------|-----------------------------------|
| `ghost_assert()`       | NO                      | NO                          | NO (but subsequent code might be)        | YES                               |
| `ghost_check()`        | YES                     | NO                          | NO (but subsequent code might be)        | YES                               |
| `ghost_ensure()`       | YES                     | YES                         | NO (and subsequent code is not run)      | NO                                |
| `ghost_assume()`       | MAYBE                   | NO                          | YES                                      | YES                               |

An additional macro, `ghost_fatal()`, signals a fatal error in both debug and release builds. It is equivalent to `ghost_ensure(false)`, except that it evaluates to a `[[noreturn]]` expression.

## Customizing Assertion Failures

When one of the assertion macros fails (or `ghost_fatal()` is called), Ghost calls `ghost_assert_fail()`. By default this prints the details to `stderr`, attempts to trigger the debugger, and aborts the program.

You can override this function if you like. Pre-define it as a macro, or declare it as a normal function and define `ghost_has_ghost_assert_fail` to 1 to prevent Ghost from declaring and defining it.

See the documentation in [`ghost_assert_fail()`](../include/ghost/debug/ghost_assert_fail.h) for details.


### Unparenthesized Commas in Assertions

`ghost_assert()` and friends are macros. The C preprocessor only considers parentheses for nesting commas, not braces or angle brackets. This means the following C and C++ code will cause compiler errors:

```c++
ghost_assert((int[2]){1,2}[0]); // error
ghost_assert(std::is_same<int,int>::value); // error
```

These are both passing two arguments to the macro `ghost_assert()`. The preprocessor splits arguments on the comma, ignoring the surrounding braces and angle brackets. This can result in some painfully confusing compiler errors.

To work around this, add an extra set of parentheses around the condition:

```c++
ghost_assert(((int[2]){1,2}[0])); // OK
ghost_assert((std::is_same<int,int>::value)); // OK
```

The standard C `assert()` has this problem as well. C23 and C++23 are considering a change to fix it. The macro will take variadic arguments that are expanded as-is, conceptually like this:

```c
#define assert(...) ((__VA_ARGS__) ? 0 : abort())
```

This has additional implications. For example if multiple arguments are actually passed to the macro, they would be considered to be a comma operator expression, so the assertion would only check the value of the last one. In particular if a `static_assert()` with a message is converted to an `assert()` without taking this into consideration, it would be checking whether the message is true, which it always is because it's just a string. The actual implementation of `assert()` will be more complicated in order to try to work around these problems.

Ghost does not follow the C23 behaviour. Instead we prefer to keep `ghost_assert()` the same as the standard `static_assert()` where the optional second parameter is a message. In fact `ghost_static_assert()` has the same comma limitations as `ghost_assert()` because it is itself a macro. Keeping the message separate makes for nicer error messages than tacking them onto the condition with `&&`.

This unfortunately means that if C23 `assert()` is ratified, you won't be able to simply `#define assert ghost_assert`, which is something we normally aim to support for most Ghost features. We may need to provide an alternate like `ghost_stdc_assert()` for this. Even if we did match the C23 varargs behaviour, we wouldn't truly be matching the standard behaviour anyway because `<assert.h>` is designed to be re-included with different values of `NDEBUG`. This is not at all desirable for Ghost.

[See the C23/C++23 `assert()` proposal here.](https://open-std.org/JTC1/SC22/WG21/docs/papers/2022/p2264r3.html)
