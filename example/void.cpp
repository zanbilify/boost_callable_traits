/*

Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/callable_traits.hpp>

struct foo {
    void operator()() const {}
};

namespace ct = callable_traits;

int main() {

    using args = ct::args<foo>;
    using expected_args = std::tuple<>;
    static_assert(std::is_same<args, expected_args>{}, "");

    using signature = ct::signature<foo>;
    using expected_signature = void();
    static_assert(std::is_same<signature, expected_signature>{}, "");

    return 0;
}