
/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#include <callable_traits/arg_at.hpp>
#include "test.hpp"

struct foo;

template<std::size_t I, typename T>
struct is_substitution_failure_arg_at {

    template<typename>
    static auto test(...) -> std::true_type;

    template<typename U,
        typename std::remove_reference<arg_at_t<I, U>>::type* = nullptr>
    static auto test(int) -> std::false_type;

    static constexpr bool value = decltype(test<T>(0))::value;
};

template<std::size_t I, typename T>
void assert_sfinae_arg_at() {
    CT_ASSERT(is_substitution_failure_arg_at<I, T>::value);
}

int main() {

    assert_sfinae_arg_at<0, int>();
    assert_sfinae_arg_at<0, int &>();
    assert_sfinae_arg_at<0, int (* const &)()>();
    assert_sfinae_arg_at<0, int (foo::* &)()>();
    assert_sfinae_arg_at<0, int (foo::* const)()>();
    assert_sfinae_arg_at<0, int (foo::* const &)()>();
    assert_sfinae_arg_at<0, int (foo::* volatile)()>();

    auto lambda = [](){};
    assert_sfinae_arg_at<0, decltype(lambda)>();
    assert_sfinae_arg_at<0, decltype(lambda)&>();
    assert_sfinae_arg_at<0, void>();

    using f = int(int, int);
    assert_sfinae_arg_at<2, f>();
    assert_sfinae_arg_at<17, f>();

    using g = int(foo::*)(int, int);
    assert_sfinae_arg_at<3, g>();
    assert_sfinae_arg_at<4, g>();
}

