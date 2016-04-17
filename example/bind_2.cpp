/*<-

Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

->*/

#include <callable_traits/config.hpp>
#ifdef CALLABLE_TRAITS_DISABLE_BIND
int main(){ return 0; }
#else

//[ bind_2
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
struct ScaryMonster : Poodle, Robot, Vampire {};

auto take_vampire(const Vampire&) { return 0; }
auto take_robot(const Robot&) { return 0; }
auto take_dog(const Dog&) { return 0; }
auto take_scary_monster(const ScaryMonster&) { return 0; }

int f(int, int, int, int) { return 0; }

using namespace std::placeholders;
namespace ct = callable_traits;

int main() {

    ScaryMonster monster{};

    auto b = ct::bind(
        &f,
        ct::bind(&take_vampire, _1),
        ct::bind(&take_robot, _1),
        ct::bind(&take_dog, _1),
        ct::bind(&take_scary_monster, _1)
    );

    {
        using args = ct::args<decltype(b)>;
        using expect = std::tuple<const ScaryMonster&>;
        static_assert(std::is_same<args, expect>::value, "");
    } {
        using type = ct::function_type<decltype(b)>;
        using expect = int(const ScaryMonster&);
        static_assert(std::is_same<type, expect>::value, "");
    }

    assert(b(monster) == 0);

    return 0;
}
//]
#endif
