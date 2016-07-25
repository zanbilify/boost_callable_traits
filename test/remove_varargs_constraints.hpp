/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#include <callable_traits/remove_varargs.hpp>
#include <tuple>
#include "test.hpp"

struct foo;

int main() {

    auto lambda = [](){};

    assert_sfinae<callable_traits::remove_varargs_t, decltype(lambda)>();
    assert_sfinae<callable_traits::remove_varargs_t, decltype(lambda)&>();
    assert_sfinae<callable_traits::remove_varargs_t, int>();
    assert_sfinae<callable_traits::remove_varargs_t, int &>();
    assert_sfinae<callable_traits::remove_varargs_t, int (* const &)()>();
    assert_sfinae<callable_traits::remove_varargs_t, int (foo::* &)()>();
    assert_sfinae<callable_traits::remove_varargs_t, int (foo::* const)()>();
    assert_sfinae<callable_traits::remove_varargs_t, int (foo::* const &)()>();
    assert_sfinae<callable_traits::remove_varargs_t, int (foo::* volatile)()>();
    assert_sfinae<callable_traits::remove_varargs_t, void>();
    assert_sfinae<callable_traits::remove_varargs_t, void*>();
    assert_sfinae<callable_traits::remove_varargs_t, void(**)()>();
}
