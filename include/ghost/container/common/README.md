This folder contains small general-purpose non-template containers of common concrete types.

The goal here is to provide popular containers (e.g. vector, map) for common types (e.g. integer, string, void pointer.) Such containers are generally useful in almost all programs.

The implementations here are small and share most of their code to minimize compiled code size. All of these containers are bitwise-movable (even the string, which has an internal buffer for small strings.)

TODO: Many containers are missing at the moment. This will take some time to implement.

The `void*` containers are weakly-typed: you can store arbitrary pointers in them. When getting values out of them, the returned `void*` can be implicitly cast to a typed pointer even in C++.

For those containers that take custom comparisons or hash functions, function pointer callbacks are used.

These are designed for simplicity, versatility and small compiled code size. They are great for general-purpose use. If you need better performance or if you want more strongly-typed containers, consider using the container templates in `ghost/container/template/` which can help you avoid void pointer casting and function pointer indirection. Alternatively, use a more powerful container library like [Pottery](https://github.com/ludocode/pottery).
