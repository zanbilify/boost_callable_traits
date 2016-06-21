/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>

#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
int main(){ return 0; }
#else

//[ is_lvalue_reference_member
#include <type_traits>
#include <callable_traits/is_lvalue_reference_member.hpp>

namespace ct = callable_traits;

static_assert(ct::is_lvalue_reference_member<int()&>::value, "");
static_assert(!ct::is_lvalue_reference_member<int()&&>::value, "");
static_assert(!ct::is_lvalue_reference_member<int()>::value, "");

struct foo;

static_assert(ct::is_lvalue_reference_member<int(foo::*)()&>::value, "");
static_assert(!ct::is_lvalue_reference_member<int(foo::*)()&&>::value, "");
static_assert(!ct::is_lvalue_reference_member<int(foo::*)()>::value, "");

int main() {}
//]
#endif
