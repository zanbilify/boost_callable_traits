/*!<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>
#ifdef CALLABLE_TRAITS_DISABLE_CONSTEXPR_CHECKS
int main(){ return 0; }
#else

//[ is_invokable_constexpr_function_pointer
#include <type_traits>
#include <callable_traits/is_invokable_constexpr.hpp>

namespace ct = callable_traits;

constexpr int seven(int) {
    return 7;
}

using seven_c = std::integral_constant<decltype(&seven), &seven>;

// The first call to is_invokable_constexpr returns std::true_type
// because `seven` is a constexpr function, and valid INVOKE arguments
// are passed. The second call to is_invokable_constexpr returns
// std::false_type, because the arguments are not valid to INVOKE
static_assert(ct::is_invokable_constexpr(seven_c{}, 0), "");
static_assert(!ct::is_invokable_constexpr(seven_c{}, nullptr), "");

int eight(int) {
    return 7;
}

using eight_c = std::integral_constant<decltype(&eight), &eight>;

// `eight` is NOT a constexpr function, so is_invokable_constexpr
// returns `std::false_type` even for valid INVOKE arguments.
static_assert(!ct::is_invokable_constexpr(eight_c{}, 0), "");
static_assert(!ct::is_invokable_constexpr(eight_c{}, nullptr), "");

int main() {}
//]
#endif
