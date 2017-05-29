/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <boost/callable_traits/detail/config.hpp>
#include "test.hpp"


#ifndef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
int main(){}
#else

#include <boost/callable_traits/remove_noexcept.hpp>

template<typename Noexcept, typename NotNoexcept>
void test() {

    CT_ASSERT(std::is_same<NotNoexcept,  TRAIT(remove_noexcept, Noexcept)>::value);

    //sanity check
    CT_ASSERT(!std::is_same<NotNoexcept, Noexcept>::value);
}

#define TEST_NOEXCEPT(not_noexcept) test<not_noexcept noexcept, not_noexcept>()

int main() {

    TEST_NOEXCEPT(int(int) &);
    TEST_NOEXCEPT(int(*)(int));
    TEST_NOEXCEPT(int(int, ...) &&);
    TEST_NOEXCEPT(int(*)(int, ...));

    struct foo;

    TEST_NOEXCEPT(int(foo::*)(int));
    TEST_NOEXCEPT(int(foo::*)(int) const);
    TEST_NOEXCEPT(int(foo::*)(int, ...));
    TEST_NOEXCEPT(int(foo::*)(int, ...) volatile);
}

#endif // #ifndef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES

