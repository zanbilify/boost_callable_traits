/*

Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#include <cassert>
#include <type_traits>
#include <functional>
#include <iostream>
#include <sstream>
#include <memory>
#include <iostream>
#include <cstdint>
#include <callable_traits/callable_traits.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

namespace ct = callable_traits;
namespace ctd = callable_traits::detail;

struct Vampire {};
struct Robot {};
struct Animal {};
struct Dog : Animal {};
struct Poodle : Dog {};
struct ScaryMonster : Poodle, Robot, Vampire {};

int main() {

    {
        using test = ctd::best_match<
            Vampire, Robot, Poodle, Animal, Dog, int, ScaryMonster>;

        using expect = ScaryMonster;

        //expected failure
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}
