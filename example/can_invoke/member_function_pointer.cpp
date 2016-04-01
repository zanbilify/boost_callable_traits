/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <callable_traits/callable_traits.hpp>

// NOTE: Due to non-compliance in MSVC, can_invoke_constexpr
// always returns std::false_type on that compiler, which
// causes a static assert below to fail.

namespace ct = callable_traits;

struct foo {
    int bar(int) const {
        return 1;
    }
};

// can_invoke returns std::true_type here because the
// arguments are valid to INVOKE
static_assert(ct::can_invoke(&foo::bar, foo{}, 0), "");


// can_invoke returns std::false_type here because the
// arguments are NOT valid to INVOKE
static_assert(!ct::can_invoke_constexpr(&foo::bar, foo{}), "");

int main() { return 0; }
