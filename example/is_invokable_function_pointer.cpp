/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ is_invokable_function_pointer
#include <callable_traits/callable_traits.hpp>

namespace ct = callable_traits;

int foo(int&& i) {
    return i;
}

// is_invokable returns std::true_type here because the
// arguments are valid to INVOKE
static_assert(ct::is_invokable(&foo, 0), "");

int i = 0;

// is_invokable returns std::false_type here because the
// arguments are NOT valid to INVOKE - foo expects an
// rvalue reference, not an lvalue reference.
static_assert(!ct::is_invokable(&foo, i), "");

int main() {}
//]
