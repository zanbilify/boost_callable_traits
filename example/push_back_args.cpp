/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ push_back_args
#include <boost/callable_traits/push_back_args.hpp>

namespace ct = boost::callable_traits;

int main() {

    using f = void(int, char);
    using test = ct::push_back_args_t<f, long, void*>;
    using expect = void(int, char, long, void*);
    static_assert(std::is_same<test, expect>::value, "");
}
//]
