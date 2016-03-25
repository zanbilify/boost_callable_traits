/*

Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

//useless MSVC /Wall warnings
#pragma warning(disable: 4514 4711)

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/callable_traits.hpp>

struct foo {

    template<typename... Args>
    std::enable_if_t<sizeof...(Args) >= 4, int>
    operator()(Args...) const {
        return{};
    }

    template<typename... Args>
    std::enable_if_t<sizeof...(Args) < 4, char>
        operator()(Args...) const {
        return{};
    }
};

namespace ct = callable_traits;

int main() {

    using args = ct::args<foo>;
    using expected_args = std::tuple<ct::unknown>;
    static_assert(std::is_same<args, expected_args>{}, "");

    using signature = ct::signature<foo>;
    using expected_signature = ct::unknown(ct::unknown);
    static_assert(std::is_same<signature, expected_signature>{}, "");
    
    return 0;
}