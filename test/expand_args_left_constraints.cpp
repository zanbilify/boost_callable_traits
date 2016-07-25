/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#include <callable_traits/expand_args_left.hpp>
#include <tuple>
#include "test.hpp"

struct foo;

template<typename T>
struct is_substitution_failure_expand_args_left {

    template<typename>
    static auto test(...) -> std::true_type;

    template<typename U,
        callable_traits::expand_args_left_t<U, std::tuple, int, int>* = nullptr>
    static auto test(int) -> std::false_type;

    static constexpr bool value = decltype(test<T>(0))::value;
};

template<typename T>
void assert_sfinae_expand_args_left() {
    CT_ASSERT(is_substitution_failure_expand_args_left<T>::value);
}

int main() {

    assert_sfinae_expand_args_left<int>();
    assert_sfinae_expand_args_left<int &>();
    assert_sfinae_expand_args_left<int (* const &)()>();
    assert_sfinae_expand_args_left<int (foo::* &)()>();
    assert_sfinae_expand_args_left<int (foo::* const)()>();
    assert_sfinae_expand_args_left<int (foo::* const &)()>();
    assert_sfinae_expand_args_left<int (foo::* volatile)()>();

    auto lambda = [](){};
    assert_sfinae_expand_args_left<decltype(lambda)&>();
    assert_sfinae_expand_args_left<void>();
    assert_sfinae_expand_args_left<void*>();
    assert_sfinae_expand_args_left<void(**)()>();
}

