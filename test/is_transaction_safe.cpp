/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <boost/callable_traits/config.hpp>

#ifndef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
int main(){}
#else

#include <boost/callable_traits/is_transaction_safe.hpp>
#include "test.hpp"

template<typename Safe, typename NotSafe>
void test() {

    CT_ASSERT( is_transaction_safe<Safe>::value);
    CT_ASSERT(! is_transaction_safe<NotSafe>::value);
}

#define TEST_TRANSACTION_SAFE(not_safe) test<not_safe transaction_safe, not_safe>()

int main() {

    TEST_TRANSACTION_SAFE(int() const);
    TEST_TRANSACTION_SAFE(int(*)());
    TEST_TRANSACTION_SAFE(int(...) volatile &);
    TEST_TRANSACTION_SAFE(int(*)(...));

    struct foo;

    TEST_TRANSACTION_SAFE(int(foo::*)());
    TEST_TRANSACTION_SAFE(int(foo::*)() const volatile);
    TEST_TRANSACTION_SAFE(int(foo::*)(...));
    TEST_TRANSACTION_SAFE(int(foo::*)(...) const volatile &&);
}

#endif

