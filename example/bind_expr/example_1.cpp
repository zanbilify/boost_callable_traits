/*

Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

//useless MSVC /Wall warnings
#pragma warning(disable: 4514 4711)

#include <cassert>
#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/callable_traits.hpp>

struct Vampire {};
struct Robot {};
struct Animal {};
struct Dog : Animal {};
struct Poodle : Dog {};
struct VampireRobotPoodle : Poodle, Robot, Vampire {};

auto take_vampire(const Vampire&) { return 0; }
auto take_robot(const Robot&) { return 0; }
auto take_dog(const Dog&) { return 0; }
auto take_vampire_robot_poodle(const VampireRobotPoodle&) { return 0; }

int f(int, int, int, int) { return 0;  }

using namespace std::placeholders;
namespace ct = callable_traits;

int main() {

    using bind_expr = decltype(ct::bind_expr(
        &f,
        ct::bind_expr(&take_vampire, _1),
        ct::bind_expr(&take_robot, _1),
        ct::bind_expr(&take_dog, _1),
        ct::bind_expr(&take_vampire_robot_poodle, _1)
    ));

    auto bind_obj = std::bind(
        &f,
        std::bind(&take_vampire, _1),
        std::bind(&take_robot, _1),
        std::bind(&take_dog, _1),
        std::bind(&take_vampire_robot_poodle, _1)
    );

    using bind_args = ct::args<bind_expr>;
    using expected_args = std::tuple<const VampireRobotPoodle&>;
    static_assert(std::is_same<bind_args, expected_args>{}, "");
    
    using bind_signature = ct::signature<bind_expr>;
    using expected_signature = int(const VampireRobotPoodle&);
    static_assert(std::is_same<bind_signature, expected_signature>{}, "");

    VampireRobotPoodle vampire_robot_poodle;
    assert(bind_obj(vampire_robot_poodle) == 0);

    std::function<bind_signature> func = bind_obj;
    assert(func(vampire_robot_poodle) == 0);
    
    return 0;
}