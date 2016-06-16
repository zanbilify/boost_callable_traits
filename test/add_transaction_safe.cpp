/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

#ifndef CALLABLE_TRAITS_ENABLE_TRANSACTION_SAFE
int main(){}
#else

#include <callable_traits/add_transaction_safe.hpp>

namespace ct = callable_traits;

template<typename Safe, typename NotSafe>
void test() {

    CT_ASSERT(std::is_same<Safe, ct::add_transaction_safe_t<NotSafe>>::value);

    //sanity check
    CT_ASSERT(!std::is_same<Safe, NotSafe>::value);
}

#define TEST_TRANSACTION_SAFE(not_safe) test<not_safe transaction_safe, not_safe>()

int main() {

    TEST_TRANSACTION_SAFE(int(int) &);
    TEST_TRANSACTION_SAFE(int(*)(int));
    TEST_TRANSACTION_SAFE(int(int, ...) &&);
    TEST_TRANSACTION_SAFE(int(*)(int, ...));

    struct foo;

    TEST_TRANSACTION_SAFE(int(foo::*)(int));
    TEST_TRANSACTION_SAFE(int(foo::*)(int) const);
    TEST_TRANSACTION_SAFE(int(foo::*)(int, ...));
    TEST_TRANSACTION_SAFE(int(foo::*)(int, ...) volatile);
}

#endif

