/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <boost/callable_traits/detail/config.hpp>

#ifndef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
int main(){}
#else

#include <boost/callable_traits/is_noexcept.hpp>
#include "test.hpp"

template<typename Noexcept, typename NotNoexcept>
void test() {

    CT_ASSERT( is_noexcept<Safe>::value);
    CT_ASSERT(! is_noexcept<NotSafe>::value);
}

#define TEST_NOEXCEPT(not_noexcept) test<not_noexcept noexcept, not_noexcept>()

int main() {

    TEST_NOEXCEPT(int() const);
    TEST_NOEXCEPT(int(*)());
    TEST_NOEXCEPT(int(...) volatile &);
    TEST_NOEXCEPT(int(*)(...));

    struct foo;

    TEST_NOEXCEPT(int(foo::*)());
    TEST_NOEXCEPT(int(foo::*)() const volatile);
    TEST_NOEXCEPT(int(foo::*)(...));
    TEST_NOEXCEPT(int(foo::*)(...) const volatile &&);
}

#endif // #ifndef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES

