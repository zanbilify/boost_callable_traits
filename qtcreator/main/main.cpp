/*!<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

//[ result_of
#include <type_traits>
#define CALLABLE_TRAITS_ENABLE_CDECL
#include <callable_traits/add_calling_convention.hpp>

namespace ct = callable_traits;

struct foo;

int main() {

    using pmf = void(foo::*)();
    using expect = void(__cdecl foo::*)();
    static_assert(!std::is_same<pmf, expect>::value, "");
}
//]
