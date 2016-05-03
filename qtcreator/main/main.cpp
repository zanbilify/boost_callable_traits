/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>
#ifdef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS
int main(){ return 0; }
#else

//[ function_type
#include <type_traits>
#include <callable_traits/callable_traits.hpp>

namespace ct = callable_traits;

template<typename T>
void test(){

    // this example shows how callable_traits::function_type
    // bevaves consistently for many different types
    using type = ct::function_type<T>;
    using expect = void(int, float&, const char*);
    static_assert(std::is_same<expect, type>{}, "");
}

int main() {

    auto lamda = [](int, float&, const char*){};
    using lam = decltype(lamda);
    test<lam>();
    test<lam&>();
    test<lam&&>();
    test<lam const &>();

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
#endif //#ifdef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS
