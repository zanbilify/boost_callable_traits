/*<-

Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

->*/

#include <callable_traits/config.hpp>
#ifdef CALLABLE_TRAITS_DISABLE_BIND
int main(){ return 0; };
#else

//[ bind_1

/* In this example, the last _1 placeholder in the bind
expression forces all other _1 slots to accept ScaryMonster,
because ScaryMonster is the narrowest of all _1 parameters. */

#include <cassert>
#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/bind.hpp>
#include <callable_traits/args.hpp>
#include <callable_traits/function_type.hpp>

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
#endif
