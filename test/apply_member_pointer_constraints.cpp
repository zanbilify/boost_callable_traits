/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <boost/callable_traits/apply_member_pointer.hpp>
#include "test.hpp"

struct foo;

int main() {
    assert_sfinae< apply_member_pointer_t, void, foo>();
    assert_sfinae< apply_member_pointer_t, int,  int>();
    assert_sfinae< apply_member_pointer_t, void, int>();
}

