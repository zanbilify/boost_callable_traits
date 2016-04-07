/*<-

Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

->*/

//[ bind_example1
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
struct ScaryMonster : Vampire, Robot, Poodle {};

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

int take_all(Vampire, Robot, Animal, Dog, Poodle, ScaryMonster) {
    return 0;
}

using namespace std::placeholders;
namespace ct = callable_traits;

int main() {

    auto b =
        ct::bind(&take_all,
            ct::bind(&converter::dog_to_vampire,
                converter{},
                ct::bind(robot_to_dog,
                    ct::bind(&vampire_to_robot, _1)
                )
            ),
            ct::bind(&vampire_to_robot, _3),
            Animal{},
            _1,
            _2,
            _1
        );

    /*` the last _1 placeholder in this bind expression forces
    all other _1 slots to accept ScaryMonster, the
    narrowest of all _1 parameters. */

    {
        using args = ct::args<decltype(b)>;
        using expect = std::tuple<ScaryMonster, Poodle, Vampire>;
        static_assert(std::is_same<args, expect>::value, "");
    } {
        using type = ct::function_type<decltype(b)>;
        using expect = int(ScaryMonster, Poodle, Vampire);
        static_assert(std::is_same<type, expect>::value, "");
    }

    assert(b(ScaryMonster{}, Poodle{}, Vampire{}) == 0);

    return 0;
}
//]
