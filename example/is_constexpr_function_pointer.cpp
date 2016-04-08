
/*!<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

//[ is_constexpr_function_pointer
#include <type_traits>
#include <callable_traits/callable_traits.hpp>

// NOTE: Due to non-compliance in MSVC, is_constexpr always
// returns std::false_type on that compiler, which causes
// the static asserts below to fail.

namespace ct = callable_traits;

constexpr int foo(const int&) {
    return 1;
}

int bar(const int&) {
    return 1;
}

// for is_constexpr calls, function pointers must
// be passed as std::integral_constants
using F = std::integral_constant<decltype(&foo), &foo>;
using B = std::integral_constant<decltype(&bar), &bar>;

static_assert(ct::is_constexpr(F{}), "");
static_assert(ct::is_constexpr<F>(), "");
static_assert(!ct::is_constexpr(B{}), "");
static_assert(!ct::is_constexpr<B>(), "");

int main() {}
//]
