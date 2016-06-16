/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ clear_args
#include <callable_traits/clear_args.hpp>

namespace ct = callable_traits;

int main() {

    using f = void(int, char);
    using cleared = ct::clear_args_t<f>;
    using expect = void();
    static_assert(std::is_same<cleared, expect>::value, "");
}
//]
