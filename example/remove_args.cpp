/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ remove_args
#include <type_traits>
#include <callable_traits/remove_args.hpp>

namespace ct = callable_traits;

template<int I>
struct N {};

struct foo {};

int main() {

    using f = int(foo::*)(N<0>, N<1>, N<2>, N<3>);
    using test = ct::remove_args_t<2, f>;
    using expect = int(foo::*)(N<0>, N<1>, N<3>);
    static_assert(std::is_same<test, expect>::value, "");
}
//]

