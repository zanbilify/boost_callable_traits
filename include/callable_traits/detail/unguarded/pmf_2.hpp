/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

*/

template<typename Return, typename T, typename... Args>
struct set_member_function_qualifiers_t<
    flag_map<int CALLABLE_TRAITS_INCLUDE_QUALIFIERS>::value,
    false,
    CALLABLE_TRAITS_CC_TAG, T, Return, Args...> {

    using type = Return(CALLABLE_TRAITS_CC T::*)(Args...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS;
};

#define CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE
#define CALLABLE_TRAITS_IS_TRANSACTION_SAFE std::false_type
#include <callable_traits/detail/unguarded/pmf_3.hpp>

#undef CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE
#undef CALLABLE_TRAITS_IS_TRANSACTION_SAFE


#ifdef CALLABLE_TRAITS_ENABLE_TRANSACTION_SAFE

template<typename Return, typename T, typename... Args>
struct set_member_function_qualifiers_t<
    flag_map<int CALLABLE_TRAITS_INCLUDE_QUALIFIERS>::value,
    true,
    CALLABLE_TRAITS_CC_TAG, T, Return, Args...> {

    using type = Return(CALLABLE_TRAITS_CC T::*)(Args...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_TRANSACTION_SAFE_SPECIFIER;
};

#define CALLABLE_TRAITS_IS_TRANSACTION_SAFE std::true_type
#define CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE transaction_safe
#include <callable_traits/detail/unguarded/pmf_3.hpp>
#endif

#undef CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE
#undef CALLABLE_TRAITS_IS_TRANSACTION_SAFE
