/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

#ifndef __cpp_generic_lambdas
int main(){ return 0; }
#else

//[ is_invokable_function_object
#include <type_traits>
#include <callable_traits/callable_traits.hpp>

namespace ct = callable_traits;

// For the purpose of this example, 'Bad' represents
// any non-arithmetic type
struct Bad {};
Bad bad{};

// non-generic callables, such as `subtract` below,
// don't have any "gotchas" when passed to
// callable_traits::is_invokable.
auto subtract = [](int x, int y) {
    return x + y;
};

static_assert(!ct::is_invokable(subtract), "");
static_assert(!ct::is_invokable(subtract, 1), "");
static_assert(ct::is_invokable(subtract, 1, 2), ""); // <-- success
static_assert(!ct::is_invokable(subtract, 1, 2, 3), "");
static_assert(!ct::is_invokable(subtract, bad, bad), "");

// Generic function objects (such as `add` and `multiply` below)
// must be SFINAE-friendly in order for failing is_invokable calls
// to actually compile. This applies to both generic lambdas and
// templated function objects. Note: MSVC does not compile this
// source code file because of the trailing return type below (MSVC
// is non-conforming in this respect)

auto add = [](auto x, auto y) -> decltype(x + y) {
    return x + y;          // ^^^^^^^^^^^^^^^^^^ explicit return type allows SFINAE
};

template<int I>
using int_c = std::integral_constant<int, I>;

static_assert(!ct::is_invokable(add), "");
static_assert(!ct::is_invokable(add, 1), "");
static_assert(ct::is_invokable(add, 1, 2), ""); // <-- success
static_assert(!ct::is_invokable(add, 1, 2, 3), "");
static_assert(!ct::is_invokable(add, bad, bad), "");

// 'multiply' isn't SFINAE-safe, because the return type depends
// on an expression in the body. However, it still works if we
// only try to call is_invokable with arguments where x * y is
// a valid expression.
auto multiply = [](auto x, auto y) {
    return x * y;
};


static_assert(!ct::is_invokable(multiply), "");
static_assert(!ct::is_invokable(multiply, 1), "");
static_assert(ct::is_invokable(multiply, 1, 2), ""); // <-- success
static_assert(!ct::is_invokable(multiply, 1, 2, 3), "");
//static_assert(!ct::is_invokable(multiply, bad, bad), "");

// The last, commented static_assert above would fail compile,
// because the call cannot be SFINAE'd away. Error message in Clang:
// "invalid operands to binary expression ('Bad' and 'Bad')"

int main() {}
//]
#endif //#ifndef __cpp_generic_lambdas
