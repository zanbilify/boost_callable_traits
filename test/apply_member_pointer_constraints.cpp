/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include "test.hpp"
#include <callable_traits/apply_member_pointer.hpp>

struct foo;

int main() {
    assert_sfinae<ct::apply_member_pointer_t, void, foo>();
    assert_sfinae<ct::apply_member_pointer_t, int,  int>();
    assert_sfinae<ct::apply_member_pointer_t, void, int>();
}

