/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ pop_front
#include <callable_traits/pop_front.hpp>

namespace ct = callable_traits;

struct foo;

int main() {

    using f = void(foo::*)(int, char, long);
    using test = ct::args_pop_front_t<f>;
    using expect = void(foo::*)(char, long);
    static_assert(std::is_same<test, expect>::value, "");
}
//]
