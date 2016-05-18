/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

//[ apply_member_pointer
#include <type_traits>
#include <callable_traits/apply_member_pointer.hpp>

namespace ct = callable_traits;

struct foo;
struct bar;

using expect = int(foo::*)(int);

int main() {

    {
        using f = int(int);
        using test = ct::apply_member_pointer<f, foo>;
        using expect = int(foo::*)(int);
        static_assert(std::is_same<test, expect>::value, "");
    }

    {
        using f = int(*)(int);
        using test = ct::apply_member_pointer<f, foo>;
        using expect = int(foo::*)(int);
        static_assert(std::is_same<test, expect>::value, "");
    }
}
//]

