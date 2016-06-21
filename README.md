<!--
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
-->

# CallableTraits <a target="_blank" href="https://travis-ci.org/badair/callable_traits">![Travis status][badge.Travis]</a> <a target="_blank" href="https://ci.appveyor.com/project/badair/callable-traits">![Appveyor status][badge.Appveyor]</a> <a target="_blank" href="http://melpon.org/wandbox/permlink/nGNLJRYBsc58zqnp">![Try it online][badge.wandbox]</a> <a target="_blank" href="https://gitter.im/badair/callable_traits">![Gitter Chat][badge.Gitter]</a>

CallableTraits is a C++11/C++14/C++17 header-only library for the inspection, synthesis, and decomposition of callable types. CallableTraits fills the gaps where existing library solutions fall short, aiming to be the "complete type manipulation facility for function types" mentioned in the last section of the C++17 proposal [p0172](http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2015/p0172r0.html). CallableTraits currently supports GCC 4.8 and later, Clang 3.5 and later, AppleClang from XCode 6.3 and later, and Visual Studio 2015. More notes on compatibility [here](http://badair.github.io/callable_traits/doc/html/callable_traits/compatibility.html).

## [Documentation](http://badair.github.io/callable_traits/index.html)
* Documentation is a work in progress - see the [Issues](https://github.com/badair/callable_traits/issues) section for information about what's lacking.

Disclaimer - CallableTraits is currently version 0.4, and is not yet ready for production use. Undiscovered bugs may exist. Documentation is incomplete and may not accurately reflect the state of the code in all places. "Breaking changes" will be made before the 1.0 version is released. Development will take place on the Develop branch, and non-documentation commits merged to the Master branch will be accompanied by a version increment.

## [License](LICENSE.md)

<!-- Links -->
[badge.Appveyor]: https://ci.appveyor.com/api/projects/status/uf0l91v7l4wc4kw6/branch/master?svg=true
[badge.Gitter]: https://img.shields.io/badge/gitter-join%20chat-blue.svg
[badge.Travis]: https://travis-ci.org/badair/callable_traits.svg?branch=master
[badge.Wandbox]: https://img.shields.io/badge/try%20it-online-blue.svg

