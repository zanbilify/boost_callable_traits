/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>

#ifndef CALLABLE_TRAITS_ENABLE_TRANSACTION_SAFE
int main(){}
#else

//[ add_transaction_safe
#include <type_traits>
#include <callable_traits/add_transaction_safe.hpp>

using callable_traits::add_transaction_safe_t;
using std::is_same_v;

using not_safe = int();
using safe = int() transaction_safe;
using safe_added = add_transaction_safe_t<not_safe>;

static_assert(is_same_v<safe, safe_added>, "");
    
int main() {}

//]
#endif

