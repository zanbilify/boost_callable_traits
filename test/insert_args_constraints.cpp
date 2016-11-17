/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#include <boost/callable_traits/insert_args.hpp>
#include <tuple>
#include "test.hpp"

struct foo;

template<std::size_t I, typename T>
struct is_substitution_failure_insert_args {

    template<typename>
    static auto test(...) -> std::true_type;

    template<typename U,
        boost::callable_traits::insert_args_t<I, U, int, int>* = nullptr>
    static auto test(int) -> std::false_type;

    static constexpr bool value = decltype(test<T>(0))::value;
};

template<std::size_t I, typename T>
void assert_sfinae_insert_args() {
    CT_ASSERT(is_substitution_failure_insert_args<I, T>::value);
}

int main() {

    auto lambda = [](){};

    //SFINAE because parameter list not present/cannot be manipulated
    assert_sfinae_insert_args<0, decltype(lambda)>();
    assert_sfinae_insert_args<0, decltype(lambda)&>();
    assert_sfinae_insert_args<0, int>();
    assert_sfinae_insert_args<0, int &>();
    assert_sfinae_insert_args<0, int (* const &)()>();
    assert_sfinae_insert_args<0, int (foo::* &)()>();
    assert_sfinae_insert_args<0, int (foo::* const)()>();
    assert_sfinae_insert_args<0, int (foo::* const &)()>();
    assert_sfinae_insert_args<0, int (foo::* volatile)()>();
    assert_sfinae_insert_args<0, void>();
    assert_sfinae_insert_args<0, void*>();
    assert_sfinae_insert_args<0, void(**)()>();

    //SFINAE because index is out of range
    assert_sfinae_insert_args<17, void()>();
    assert_sfinae_insert_args<1, void()>();
    assert_sfinae_insert_args<2, void(int)>();
}
