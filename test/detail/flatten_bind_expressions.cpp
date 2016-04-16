/*

Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#include <type_traits>
#include <functional>
#include <iostream>
#include <sstream>
#include <memory>
#include <iostream>
#include <cstdint>
#include <callable_traits/callable_traits.hpp>

#ifdef CALLABLE_TRAITS_DISABLE_BIND
int main(){ return 0; }
#else

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

using namespace std::placeholders;
namespace ct = callable_traits;

struct A {};
struct B {};
struct C {};
struct D {};
struct E {};
struct F {};
struct G {};

// functions `ordered_letters`, `BEEF_returns_D`, `BEEF_returns_G`,
// and `BEEF_returns_B` are used to set up a complex bind expression
// with ct::bind

auto ordered_letters(A, B, C, D, E, F, G) {
    return 0;
}

auto BEEF_returns_D(B, E, E, F) {
    return D{};
}

auto BEEF_returns_G(B, E, E, F) {
    return G{};
}

auto BEEF_returns_B(B, E, E, F) {
    return B{};
}

#define INNER_3 ct::bind(&BEEF_returns_B, B{}, _10, E{}, F{})
#define INNER_2 ct::bind(&BEEF_returns_G, INNER_3, _9, E{}, _8)
#define INNER_1 ct::bind(&BEEF_returns_D, _2, E{}, _4, _7)

int main() {

    auto root = ct::bind(&ordered_letters, _1, _2, _3, INNER_1, _5, _6, INNER_2);

    using test = decltype(root)::flattened_bind_expressions;

    using expect = std::tuple<
        decltype(root),
        decltype(INNER_1),
        decltype(INNER_2),
        decltype(INNER_3)
    >;

    CT_ASSERT(std::is_same<test, expect>::value);

    return 0;
}

#endif
