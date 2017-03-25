/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#include <boost/callable_traits/add_transaction_safe.hpp>
#include <tuple>
#include "test.hpp"

#ifndef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
int main(){}
#else

struct foo;

int main() {

    auto lambda = [](){};

    assert_sfinae<boost::callable_traits::add_transaction_safe_t, decltype(lambda)>();
    assert_sfinae<boost::callable_traits::add_transaction_safe_t, decltype(lambda)&>();
    assert_sfinae<boost::callable_traits::add_transaction_safe_t, int>();
    assert_sfinae<boost::callable_traits::add_transaction_safe_t, int &>();
    assert_sfinae<boost::callable_traits::add_transaction_safe_t, int (* const &)()>();
    assert_sfinae<boost::callable_traits::add_transaction_safe_t, int (foo::* &)()>();
    assert_sfinae<boost::callable_traits::add_transaction_safe_t, int (foo::* const)()>();
    assert_sfinae<boost::callable_traits::add_transaction_safe_t, int (foo::* const &)()>();
    assert_sfinae<boost::callable_traits::add_transaction_safe_t, int (foo::* volatile)()>();
    assert_sfinae<boost::callable_traits::add_transaction_safe_t, void>();
    assert_sfinae<boost::callable_traits::add_transaction_safe_t, void*>();
    assert_sfinae<boost::callable_traits::add_transaction_safe_t, void(**)()>();
}

#endif //#ifndef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
