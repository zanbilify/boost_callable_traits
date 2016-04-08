/*!<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/
//[ remove_member_pointer
#include <type_traits>
#include <callable_traits/callable_traits.hpp>

namespace ct = callable_traits;

struct foo;

template<typename T, typename Expect>
void test() {
    using U = ct::remove_member_pointer<T>;
    static_assert(std::is_same<Expect, U>{}, "");
}

int main() {

    {
        using T = int(foo::*)(int) const;
        using expect = int(int) const;
        test<T, expect>();
    } {
        using T = int foo::*;
        using expect = int;
        test<T, expect>();
    } {
        using T = int(int);
        test<T, T>();
    } {
        using T = int(*)(int);
        test<T, T>();
    } {
        using T = int(&)(int);
        test<T, T>();
    }
}
//]
