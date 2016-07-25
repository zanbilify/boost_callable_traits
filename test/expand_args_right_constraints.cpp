/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#include <callable_traits/expand_args_right.hpp>
#include <tuple>
#include "test.hpp"

struct foo;

template<typename T>
struct is_substitution_failure_expand_args_right {

    template<typename>
    static auto test(...) -> std::true_type;

    template<typename U,
        callable_traits::expand_args_right_t<U, std::tuple, int, int>* = nullptr>
    static auto test(int) -> std::false_type;

    static constexpr bool value = decltype(test<T>(0))::value;
};

template<typename T>
void assert_sfinae_expand_args_right() {
    CT_ASSERT(is_substitution_failure_expand_args_right<T>::value);
}

int main() {

    assert_sfinae_expand_args_right<int>();
    assert_sfinae_expand_args_right<int &>();
    assert_sfinae_expand_args_right<int (* const &)()>();
    assert_sfinae_expand_args_right<int (foo::* &)()>();
    assert_sfinae_expand_args_right<int (foo::* const)()>();
    assert_sfinae_expand_args_right<int (foo::* const &)()>();
    assert_sfinae_expand_args_right<int (foo::* volatile)()>();

    auto lambda = [](){};
    assert_sfinae_expand_args_right<decltype(lambda)&>();
    assert_sfinae_expand_args_right<void>();
    assert_sfinae_expand_args_right<void*>();
    assert_sfinae_expand_args_right<void(**)()>();
}

