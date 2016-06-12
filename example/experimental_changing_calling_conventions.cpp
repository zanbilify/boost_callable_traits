/*!<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>

//todo make this example work with GCC 6
#ifdef CALLABLE_TRAITS_GCC_AT_LEAST_6_0_0
int main(){}
#else

//[ experimental_changing_calling_conventions
#define CALLABLE_TRAITS_ENABLE_STDCALL
#define CALLABLE_TRAITS_ENABLE_FASTCALL

#include <type_traits>
#include <callable_traits/has_calling_convention.hpp>
#include <callable_traits/add_calling_convention.hpp>
#include <callable_traits/remove_calling_convention.hpp>

namespace ct = callable_traits;

int main() {

    using f = void(__fastcall *)(int);

    static_assert(ct::has_calling_convention<f, ct::fastcall_tag>(), "");
    static_assert(!ct::has_calling_convention<f, ct::stdcall_tag>(), "");

    using expect = void(__stdcall *)(int);

    static_assert(ct::has_calling_convention<expect, ct::stdcall_tag>(), "");
    static_assert(!ct::has_calling_convention<expect, ct::fastcall_tag>(), "");

    using g = ct::remove_calling_convention<f>;
    using test = ct::add_calling_convention<g, ct::stdcall_tag>;

    static_assert(ct::has_calling_convention<test, ct::stdcall_tag>(), "");
    static_assert(std::is_same<test, expect>::value, "");
}
//]
#endif
