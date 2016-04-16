/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <callable_traits/can_invoke_constexpr.hpp>

#ifdef CALLABLE_TRAITS_DISABLE_CONSTEXPR_CHECKS
int main(){ return 0; }
#else

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

struct foo1 {
    int operator()() const {
        return 0;
    }
};

struct foo2 {
    constexpr int operator()(int) const {
        return 1;
    }
    constexpr int operator()() const {
        return 1;
    }
};

struct foo3 {
    constexpr int bar(int) const {
        return 1;
    }
};

constexpr int bar(const int&) {
    return 1;
}

using foo4 = std::integral_constant<decltype(&bar), &bar>;

using foo1_pmf = std::integral_constant<decltype(&foo1::operator()), &foo1::operator()>;
using foo3_pmf = std::integral_constant<decltype(&foo3::bar), &foo3::bar>;

namespace ct = callable_traits;

CT_ASSERT(!ct::can_invoke_constexpr(foo1{}));
CT_ASSERT(!ct::can_invoke_constexpr(foo1{}, 0));

CT_ASSERT( ct::can_invoke_constexpr(foo2{}));
CT_ASSERT( ct::can_invoke_constexpr(foo2{}, 0));

CT_ASSERT(!ct::can_invoke_constexpr(foo4{}));
CT_ASSERT( ct::can_invoke_constexpr(foo4{}, 0));

CT_ASSERT(!ct::can_invoke_constexpr(foo1_pmf{}, foo1{}));
CT_ASSERT(!ct::can_invoke_constexpr(foo1_pmf{}, foo1{}, 0));

CT_ASSERT(!ct::can_invoke_constexpr(foo3_pmf{}, foo3{}));
CT_ASSERT( ct::can_invoke_constexpr(foo3_pmf{}, foo3{}, 0));

int main() {}

#endif
