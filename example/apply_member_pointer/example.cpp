/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#include <callable_traits/callable_traits.hpp>

namespace ct = callable_traits;

struct foo;
struct bar;

using expect = int(foo::*)(int);

template<typename T>
void test() {
    using U = ct::apply_member_pointer<T, foo>;
    static_assert(std::is_same<expect, U>{}, "");
}

int main() {
    test<int(int)>();
    test<int(*)(int)>();
    test<int(*&)(int)>();
    test<int(* const)(int)>();
    test<int(&)(int)>();
    test<int(foo::*)(int)>();
    test<int(bar::*)(int)>();
}

