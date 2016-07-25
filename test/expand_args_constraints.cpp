/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#include <callable_traits/expand_args.hpp>
#include <tuple>
#include "test.hpp"

struct foo;

template<typename T>
struct is_substitution_failure_expand_args {

    template<typename>
    static auto test(...) -> std::true_type;

    template<typename U,
        callable_traits::expand_args_t<U, std::tuple>* = nullptr>
    static auto test(int) -> std::false_type;

    static constexpr bool value = decltype(test<T>(0))::value;
};

template<typename T>
void assert_sfinae_expand_args() {
    CT_ASSERT(is_substitution_failure_expand_args<T>::value);
}

int main() {

    assert_sfinae_expand_args<int>();
    assert_sfinae_expand_args<int &>();
    assert_sfinae_expand_args<int (* const &)()>();
    assert_sfinae_expand_args<int (foo::* &)()>();
    assert_sfinae_expand_args<int (foo::* const)()>();
    assert_sfinae_expand_args<int (foo::* const &)()>();
    assert_sfinae_expand_args<int (foo::* volatile)()>();

    auto lambda = [](){};
    assert_sfinae_expand_args<decltype(lambda)&>();
    assert_sfinae_expand_args<void>();
    assert_sfinae_expand_args<void*>();
    assert_sfinae_expand_args<void(**)()>();
}

