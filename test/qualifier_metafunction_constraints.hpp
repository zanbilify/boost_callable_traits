/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
*/

#ifndef PP_CAT
#define PP_CAT_(x, y) x ## y
#define PP_CAT(x, y) PP_CAT_(x, y)
#endif

auto PP_CAT(test_, CALLABLE_TRAIT_UNDER_TEST) = [](){
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, int>();
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, int &>();
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, int(&)()>();
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, int(*)()>();
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, int(* const foo::*)()>();
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, int foo::*>();
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, int (foo::* &)()>();
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, int (foo::* const)()>();
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, int (foo::* const &)()>();
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, int (foo::* volatile)()>();

    auto lambda = [](){};
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, decltype(lambda)>();
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, decltype(lambda)&>();
    assert_sfinae<callable_traits::CALLABLE_TRAIT_UNDER_TEST, void>();
};

PP_CAT(test_, CALLABLE_TRAIT_UNDER_TEST)();