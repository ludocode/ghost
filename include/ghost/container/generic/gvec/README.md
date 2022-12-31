# Generic Vector of Bitwise-Movable Elements

This is a type-erased vector (or dynamic growable array) of arbitrary elements. The elements must be bitwise-movable and each element must be the same size.

This is not intended to be used directly. It is used to implement a vector of concrete type or a vector template. By having vectors of all types share a type-erased implementation, the volume of duplicated code is reduced, resulting in smaller binaries and faster programs.

The element size must be passed as an argument to every function call. In debug mode the vector asserts that the size matches that given upon initialization.
