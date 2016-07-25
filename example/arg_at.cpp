
/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

//[ arg_at
#include <type_traits>
#include <callable_traits/arg_at.hpp>

namespace ct = callable_traits;

int main() {

    auto lambda = [](int, char, float){};
    using lt = decltype(lambda);

    using second_param = ct::arg_at_t<1, lt>;
    static_assert(std::is_same<second_param, char>::value, "");

    // With pointer-to-member functions, the implicit "this" pointer
    // is treated as the first parameter, in the form of a reference.
    using pmf = decltype(&lt::operator());
    using object_ref = ct::arg_at_t<0, pmf>;
    static_assert(std::is_same<object_ref, lt const &>::value, "");
}
//]
