/*!<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

//[ calling_convention_cdecl

#define CALLABLE_TRAITS_ENABLE_CDECL

#include <type_traits>
#include <callable_traits/has_calling_convention.hpp>
#include <callable_traits/add_calling_convention.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    //depending on your platform, pmf may alrady have an implicit __cdecl
    using pmf = void(foo::*)();
    using expect = void(__cdecl foo::*)();
    using test = ct::add_calling_convention<pmf, ct::cdecl_tag>;

    static_assert(std::is_same<test, expect>::value, "");
    static_assert(ct::has_calling_convention<expect, ct::cdecl_tag>(), "");
    static_assert(ct::has_calling_convention<test, ct::cdecl_tag>(), "");
}
//]
