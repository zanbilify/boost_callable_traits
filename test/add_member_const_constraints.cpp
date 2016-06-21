/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#include <type_traits>
#include <functional>
#include <tuple>
#include "test.hpp"
#include <callable_traits/add_member_const.hpp>

struct foo;

namespace ct = callable_traits;

int main() {
    assert_sfinae<ct::add_member_const_t, int>();
    assert_sfinae<ct::add_member_const_t, int &>();
    assert_sfinae<ct::add_member_const_t, int(&)()>();
    assert_sfinae<ct::add_member_const_t, int(*)()>();
    assert_sfinae<ct::add_member_const_t, int(* const foo::*)()>();
    assert_sfinae<ct::add_member_const_t, int foo::*>();
    assert_sfinae<ct::add_member_const_t, int (foo::* &)()>();
    assert_sfinae<ct::add_member_const_t, int (foo::* const)()>();
    assert_sfinae<ct::add_member_const_t, int (foo::* const &)()>();
    assert_sfinae<ct::add_member_const_t, int (foo::* volatile)()>();

    auto lambda = [](){};
    assert_sfinae<ct::add_member_const_t, decltype(lambda)>();
    assert_sfinae<ct::add_member_const_t, decltype(lambda)&>();
    assert_sfinae<ct::add_member_const_t, void>();
}
