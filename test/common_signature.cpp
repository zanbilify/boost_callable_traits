/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <callable_traits/callable_traits.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

namespace ct = callable_traits;

//ct::common_signature makes MSVC crash :(
#ifndef CALLABLE_TRAITS_MSVC

namespace test1 {

    using test = ct::common_signature<
        char(int),
        short(int&&),
        int(const int&)
    >;

    using expect = int(int);

    CT_ASSERT(std::is_same<test, expect>::value);
}

namespace test2 {

    using test = ct::common_signature<
        char(),
        int()
    >;

    using expect = int();

    CT_ASSERT(std::is_same<test, expect>::value);
}

namespace test3 {

    struct Vampire {};
    struct Robot {};
    struct Animal {};
    struct Dog : Animal {};
    struct Poodle : Dog {};
    struct VampireRobotPoodle : Poodle, Robot, Vampire {};

    using test = ct::common_signature<
        Dog(VampireRobotPoodle, Vampire, Robot, Dog, Animal),
        Poodle(Vampire, VampireRobotPoodle, Robot, Dog, Animal),
        Poodle(Vampire, Robot, VampireRobotPoodle, Dog, Animal),
        VampireRobotPoodle(Vampire, Robot, Dog, VampireRobotPoodle, Animal),
        Animal(Vampire, Robot, Dog, Animal, VampireRobotPoodle)
    >;

    using expect = Animal(
        VampireRobotPoodle,
        VampireRobotPoodle,
        VampireRobotPoodle,
        VampireRobotPoodle,
        VampireRobotPoodle
    );

    CT_ASSERT(std::is_same<test, expect>::value);
}

#endif

int main() { return 0; }
