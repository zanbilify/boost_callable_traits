/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <memory>
#include <callable_traits/callable_traits.hpp>

namespace ct = callable_traits;

struct Vampire {};
struct Robot {};
struct Animal {};
struct Dog : Animal {};
struct Poodle : Dog {};
struct Monster : Poodle, Robot, Vampire {};

struct foo {
    Poodle make_poodle(Vampire&&, Robot, Monster, Dog, Animal) const {
        return Poodle{};
    }
};

using A = Dog(*)(          const Monster&, Vampire,   Robot,   Dog,      Animal);
using B = Dog(*&)(         Monster,        Vampire,   Robot,   Animal,   Dog, ...);
using C = Animal(&)(       Vampire,        Monster,   Robot,   Dog,      const Animal&);
using D = Poodle(foo::*)(  Vampire,        Robot,     Monster, Dog,      Animal) const;
using E = Monster(         Vampire,        Robot,     Dog,     Monster,  Monster) const volatile;

using test = ct::common_signature<A, B, C, D, E>;

using expect = Animal(
    Monster,
    Monster,
    Monster,
    Monster,
    Monster
);

static_assert(std::is_same<test, expect>{}, "");

int main(){}
