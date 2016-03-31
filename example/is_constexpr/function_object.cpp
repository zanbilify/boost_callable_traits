/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <callable_traits/callable_traits.hpp>

namespace ct = callable_traits;

//this is a constexpr function object (non-templated)
struct zero {

    constexpr auto operator()() {
        return 0;
    }
};

static_assert(ct::is_constexpr<zero>(), "");
static_assert(ct::is_constexpr(zero{}), "");



//this is a constexpr function object (templated)
struct subtract {

    // For callable_traits::is_constexpr, generic function objects
    // only need to be SFINAE-friendly if the body of the operator()
    // function accesses member names besides "type" and "value".
    // Unary/binary operators and constructor calls are okay to use.
    template<typename T1, typename T2>
    constexpr auto operator()(T1, T2) {
        return T1{} - T2{};
    }
};

static_assert(ct::is_constexpr<subtract>(), "");
static_assert(ct::is_constexpr(subtract{}), "");



//this is NOT a constexpr function object
struct add {
    template<typename T1, typename T2>
    auto operator()(T1, T2) {
        return T1{} + T2{};
    }
};

static_assert(!ct::is_constexpr<add>(), "");
static_assert(!ct::is_constexpr(add{}), "");




/*
// The case below fails to compile, because lambdas are not trivially
// default constructible. (Note: This restriction also applies to the
// argument types). Error message: "Cannot perform constexpr checks
// with this type, because it is not trivially default constructible."

auto multiply = [](auto t1, auto t2) -> decltype(t1.value * t2.value) {
    return t1.value * t2.value;
};

static_assert(!ct::is_constexpr<decltype(multiply)>(), "");
static_assert(!ct::is_constexpr(multiply), "");
*/



int main() {}