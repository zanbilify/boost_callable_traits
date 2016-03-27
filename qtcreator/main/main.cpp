/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <callable_traits/callable_traits.hpp>

struct foo{};

namespace ct = callable_traits;

using pmf = void(foo::*)();
using test = ct::add_const_qualifier<pmf>;
using expect = void(foo::*)() const;

static_assert(std::is_same<test, expect>{}, "");

int main() {
    return 0;
}
