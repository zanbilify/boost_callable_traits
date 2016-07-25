/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#include <callable_traits/remove_args.hpp>
#include <tuple>
#include "test.hpp"

struct foo;

template<std::size_t I, typename T, std::size_t Count>
struct is_substitution_failure_remove_args {

    template<typename>
    static auto test(...) -> std::true_type;

    template<typename U,
        callable_traits::remove_args_t<I, U, Count>* = nullptr>
    static auto test(int) -> std::false_type;

    static constexpr bool value = decltype(test<T>(0))::value;
};

template<std::size_t I, typename T, std::size_t Count = 1>
void assert_sfinae_remove_args() {
    CT_ASSERT(is_substitution_failure_remove_args<I, T, Count>::value);
}

int main() {

    auto lambda = [](){};

    //SFINAE because parameter list not present/cannot be manipulated
    assert_sfinae_remove_args<0, decltype(lambda)>();
    assert_sfinae_remove_args<0, decltype(lambda)&>();
    assert_sfinae_remove_args<0, int>();
    assert_sfinae_remove_args<0, int &>();
    assert_sfinae_remove_args<0, int (* const &)()>();
    assert_sfinae_remove_args<0, int (foo::* &)()>();
    assert_sfinae_remove_args<0, int (foo::* const)()>();
    assert_sfinae_remove_args<0, int (foo::* const &)()>();
    assert_sfinae_remove_args<0, int (foo::* volatile)()>();
    assert_sfinae_remove_args<0, void>();
    assert_sfinae_remove_args<0, void*>();
    assert_sfinae_remove_args<0, void(**)()>();

    //SFINAE because index is out of range
    assert_sfinae_remove_args<17, void()>();
    assert_sfinae_remove_args<1, void()>();
    assert_sfinae_remove_args<2, void(int)>();
    assert_sfinae_remove_args<1, void(foo::*)(int)>();
    assert_sfinae_remove_args<2, void(foo::*)(int, int) const>();

    //SFINAE because index + count is out of range
    assert_sfinae_remove_args<0, void()>();
    assert_sfinae_remove_args<0, void(int), 2>();
    assert_sfinae_remove_args<0, void(foo::*)(int) volatile, 2>();
    assert_sfinae_remove_args<0, void(foo::*)(int, int), 3>();
    assert_sfinae_remove_args<1, void(foo::*)(int, int), 2>();
}
