/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#include <callable_traits/callable_traits.hpp>

namespace ct = callable_traits;

int foo(int&& i) {
    return i;
}

// can_invoke returns std::true_type here because the
// arguments are valid to INVOKE
static_assert(ct::can_invoke(&foo, 0), "");

int i = 0;

// can_invoke returns std::false_type here because the
// arguments are NOT valid to INVOKE - foo expects an
// rvalue reference, not an lvalue reference.
static_assert(!ct::can_invoke(&foo, i), "");

int main() { return 0; }

