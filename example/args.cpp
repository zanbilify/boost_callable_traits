/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

//[ args
#include <type_traits>
#include <memory>
#include <callable_traits/callable_traits.hpp>

namespace ct = callable_traits;

// all callable types in this example use these parameter types
using expect = std::tuple<int, float&, const char*>;

template<typename T>
void test(){
    // this example shows how callable_traits::args
    // bevaves consistently for many different types
    using args = ct::args<T>;
    static_assert(std::is_same<expect, args>{}, "");
}

int main() {


    auto lamda = [](int, float&, const char*){};
    using lam = decltype(lamda);
    test<lam>();
    test<lam&>();
    test<lam&&>();
    test<lam const &>();

    struct foo;
    using pmf = void(foo::*)(int, float&, const char*);
    test<pmf>();
    test<pmf&>();
    test<pmf&&>();
    test<pmf const &>();

    using function_ptr = void(*)(int, float&, const char*);
    test<function_ptr>();
    test<function_ptr&>();
    test<function_ptr&&>();
    test<function_ptr const &>();

    using function_ref = void(&)(int, float&, const char*);
    test<function_ref>();

    using function = void(int, float&, const char*);
    test<function>();

    using abominable = void(int, float&, const char*) const;
    test<abominable>();
}
//]

