/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ expand_args_right
#include <boost/callable_traits/expand_args_right.hpp>

namespace ct = boost::callable_traits;

void f(int, char);

template<typename...> struct foo{};

int main() {

    using args = ct::expand_args_right_t<decltype(f), foo, void*>;
    static_assert(std::is_same<args, foo<void*, int, char>>::value, "");
}
//]
