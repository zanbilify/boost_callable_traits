/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/


// NOTE: This does not compile in MSVC, which can't handle
// the trailing return type on the generic lambda 'add'

#include <type_traits>
#include <callable_traits/callable_traits.hpp>

namespace ct = callable_traits;

// For the purpose of this example, 'Bad' represents
// any non-arithmetic type
struct Bad {};
Bad bad{};

// non-generic callables, such as `subtract` below,
// don't have any "gotchas" when passed to
// callable_traits::can_invoke.
auto subtract = [](int x, int y) {
    return x + y;
};

static_assert(!ct::can_invoke(subtract), "");
static_assert(!ct::can_invoke(subtract, 1), "");
static_assert(ct::can_invoke(subtract, 1, 2), ""); // <-- success
static_assert(!ct::can_invoke(subtract, 1, 2, 3), "");
static_assert(!ct::can_invoke(subtract, bad, bad), "");

// Generic function objects (such as `add` and `multiply` below)
// must be SFINAE-friendly in order for failing can_invoke calls
// to actually compile. This applies to both generic lambdas and
// templated function objects. Note: MSVC does not compile this
// source code file because of the trailing return type below (MSVC
// is non-conforming in this respect)

auto add = [](auto x, auto y) -> decltype(x + y) {
    return x + y;          // ^^^^^^^^^^^^^^^^^^ explicit return type allows SFINAE
};

template<int I>
using int_c = std::integral_constant<int, I>;

static_assert(!ct::can_invoke(add), "");
static_assert(!ct::can_invoke(add, 1), "");
static_assert(ct::can_invoke(add, 1, 2), ""); // <-- success
static_assert(!ct::can_invoke(add, 1, 2, 3), "");
static_assert(!ct::can_invoke(add, bad, bad), "");

// 'multiply' isn't SFINAE-safe, because the return type depends
// on an expression in the body. However, it still works if we
// only try to call can_invoke with arguments where x * y is
// a valid expression.
auto multiply = [](auto x, auto y) {
    return x * y;
};


static_assert(!ct::can_invoke(multiply), "");
static_assert(!ct::can_invoke(multiply, 1), "");
static_assert(ct::can_invoke(multiply, 1, 2), ""); // <-- success
static_assert(!ct::can_invoke(multiply, 1, 2, 3), "");
//static_assert(!ct::can_invoke(multiply, bad, bad), "");

// The last, commented static_assert above would fail compile,
// because the call cannot be SFINAE'd away. Error message in Clang:
// "invalid operands to binary expression ('Bad' and 'Bad')"

int main() {}
