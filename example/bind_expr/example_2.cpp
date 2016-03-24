/*

Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

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
struct VampireRobotPoodle : Vampire, Robot, Poodle {};

auto vampire_to_robot(Vampire) {
    return Robot{};
}

auto robot_to_dog = [](Robot){
    return Dog{};
};

struct converter {
    auto dog_to_vampire(Dog) {
        return Vampire{};
    }
};

int take_all(Vampire, Robot, Animal, Dog, Poodle, VampireRobotPoodle) {
    return 0;
}

using namespace std::placeholders;
namespace ct = callable_traits;

int main() {

    using bind_expr = decltype(
        ct::bind_expr(&take_all,
            ct::bind_expr(&converter::dog_to_vampire,
                converter{},
                ct::bind_expr(robot_to_dog,
                    ct::bind_expr(&vampire_to_robot, _1)
                )
            ),
            ct::bind_expr(&vampire_to_robot, _3),
            Animal{},
            _1,
            _2,
            _1
        )
    );

    auto bind_obj = 
        std::bind(&take_all,
            std::bind(&converter::dog_to_vampire,
                converter{},
                std::bind(robot_to_dog,
                    std::bind(&vampire_to_robot, _1)
                )
            ),
            std::bind(&vampire_to_robot, _3),
            Animal{},
            _1,
            _2,
            _1
        );

    using bind_args = ct::args<bind_expr>;
    using expected_args = std::tuple<VampireRobotPoodle, Poodle, Vampire>;
    static_assert(std::is_same<bind_args, expected_args>{}, "");

    using bind_signature = ct::signature<bind_expr>;
    using expected_signature = int(VampireRobotPoodle, Poodle, Vampire);
    static_assert(std::is_same<bind_signature, expected_signature>{}, "");
    
    assert(bind_obj(VampireRobotPoodle{}, Poodle{}, Vampire{}) == 0);

    auto fn = std::function<bind_signature>{ bind_obj };
    assert(fn(VampireRobotPoodle{}, Poodle{}, Vampire{}) == 0);

    return 0;
}