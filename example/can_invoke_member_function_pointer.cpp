/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ can_invoke_member_function_pointer
#include <callable_traits/callable_traits.hpp>

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
// arguments are NOT valid to INVOKE - foo::bar can't be
// invoked like a void member function.
static_assert(!ct::can_invoke(&foo::bar, foo{}), "");

int main() {}

//]
