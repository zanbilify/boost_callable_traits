<!--
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
-->

# CallableTraits

![Build Status](https://travis-ci.org/badair/callable_traits.svg?branch=master)

[![Gitter](https://badges.gitter.im/badair/callable_traits.svg)](https://gitter.im/badair/callable_traits?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

<a target="_blank" href="http://melpon.org/wandbox/permlink/IKBYJ5EE4umXo9qb">![Try it online][badge.wandbox]</a>

CallableTraits is a small, header-only library providing a uniform and comprehensive interface for the type-level manipulation of all callable types in C++.

## Documentation [Here](http://badair.github.io/callable_traits/index.html)

## Compatibility

CallableTraits is currently tested and working on the following platforms, unless otherwise noted:
- GNU/Linux
  - clang 3.5 and later (both libc++ and libstdc++)
  - gcc 5.2 and later
- OSX
  - Apple Xcode 6.3 and later
  - open-source clang 3.5 and later should work, but is not tested
- Windows
  - Microsoft Visual Studio 2015 (native MSVC)
  - MinGW32 gcc 5.3 (other versions not tested)
  - clang-cl in Visual Studio's LLVM toolkit cannot build CallableTraits tests because of [this curious bug](http://stackoverflow.com/questions/36026352/compiler-attribute-stuck-on-a-function-type-is-there-a-workaround-for-this-cla). I filed a bug report, but I should be able to work around it when I find the time to do so.

I do not know the compatibility of CallableTraits for other/older compilers, but the `stdlib` implementation must include `std::index_sequence` and friends.

## Building the tests and examples

First, you'll need a recent version of [CMake](https://cmake.org/). These commands assume that `git` and `cmake` are available in your environment path. If you need help with this, [message me on Gitter](https://gitter.im/badair/callable_traits).

__GNU/Linux/OSX__

Open a shell and enter the following commands:

```shell
git clone http://github.com/badair/callable_traits
cd callable_traits
mkdir build
cd build
cmake ..
make check
```
If your system doesn't have a default C++ compiler, or your default C++ compiler is too old, you'll need to point CMake to a compatible C++ compiler like this, before running `make check`:

```shell
cmake .. -DCMAKE_CXX_COMPILER=/path/to/compiler
```

CMake should yell at you if your compiler is too old.

__Windows__

Cygwin/MSYS/MSYS2 users should refer to the Linux section. For Visual Studio 2015, fire up `cmd.exe` and enter the following commands:

```shell
git clone http://github.com/badair/callable_traits
cd callable_traits
mkdir build
cd build
cmake .. -G"Visual Studio 14 2015 Win64"
```
Then, open the generated `callable_traits.sln` solution file in Visual Studio.

## See Also

CallableTraits is a spin-off of a sillier, messier, more experimental project of mine called [CLBL](https://github.com/badair/CLBL), which has a storied commit history.

## License
Please see [LICENSE.md](LICENSE.md).

<!-- Links -->
[badge.Wandbox]: https://img.shields.io/badge/try%20it-online-blue.svg
[example.Wandbox]: http://melpon.org/wandbox/permlink/TlioDiz6yYNxZFnv

