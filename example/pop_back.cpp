/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ pop_back
#include <callable_traits/pop_back.hpp>

namespace ct = callable_traits;

int main() {

    using f = void(*)(int, char);
    using test = ct::args_pop_back_t<f>;
    using expect = void(*)(int);
    static_assert(std::is_same<test, expect>::value, "");
}
//]
