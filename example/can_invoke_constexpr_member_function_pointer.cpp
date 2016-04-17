/*!<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>
#ifdef CALLABLE_TRAITS_DISABLE_CONSTEXPR_CHECKS
int main(){ return 0; }
#else

//[ can_invoke_constexpr_member_function_pointer
#include <type_traits>
#include <callable_traits/can_invoke_constexpr.hpp>

// NOTE: Due to non-compliance in MSVC, can_invoke_constexpr
// always returns std::false_type on that compiler, which
// causes a static assert below to fail.

namespace ct = callable_traits;

struct foo {
    constexpr int bar(int) const {
        return 1;
    }
};

using pmf_constant = std::integral_constant<decltype(&foo::bar), &foo::bar>;

// can_invoke_constexpr returns true here because foo::bar
// is constexpr, and the arguments are valid to INVOKE
static_assert(ct::can_invoke_constexpr(pmf_constant{}, foo{}, 0), "");

// can_invoke_constexpr returns false here because even though
// foo::bar is constexpr, the arguments do not obey INVOKE rules
static_assert(!ct::can_invoke_constexpr(pmf_constant{}, foo{}), "");

int main() {}
//]
#endif
