/*<-

Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

->*/

//[ pop_back_args
#include <callable_traits/pop_front_args.hpp>

namespace ct = callable_traits;

static_assert(std::is_same<
    ct::pop_front_args_t<int(char, short, int)>,
    int(short, int)
>::value, "");

struct foo;

static_assert(std::is_same<
    ct::pop_front_args_t<int(foo::*)(char, short, int) const, 2>,
    int(foo::*)(int) const
>::value, "");

static_assert(std::is_same<
    ct::pop_front_args_t<int(*)(char, short, int), 3>,
    int(*)()
>::value, "");

static_assert(std::is_same<
    //overflow is handled
    ct::pop_front_args_t<int(&)(char, short, int), 27>,
    int(&)()
>::value, "");

int main() {}
//]
