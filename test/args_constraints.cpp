
/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#include <boost/callable_traits/args.hpp>
#include "test.hpp"

struct foo;

int main() {

    assert_sfinae<boost::callable_traits::args_t, int>();
    assert_sfinae<boost::callable_traits::args_t, int &>();
    assert_sfinae<boost::callable_traits::args_t, int (* const &)()>();
    assert_sfinae<boost::callable_traits::args_t, int (foo::* &)()>();
    assert_sfinae<boost::callable_traits::args_t, int (foo::* const)()>();
    assert_sfinae<boost::callable_traits::args_t, int (foo::* const &)()>();
    assert_sfinae<boost::callable_traits::args_t, int (foo::* volatile)()>();

    auto lambda = [](){};
    assert_sfinae<boost::callable_traits::args_t, decltype(lambda)&>();
    assert_sfinae<boost::callable_traits::args_t, void>();
}

