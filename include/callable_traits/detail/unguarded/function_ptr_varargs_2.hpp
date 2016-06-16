/*
Copyright (c) 2016 Modified Work Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

macros used:

CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE - the transaction_safe specifier for
    the current include (`transaction_safe` or nothing)

CALLABLE_TRAITS_IS_TRANSACTION_SAFE - `std::true_type` or `std::false_type`,
    tied on whether CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE is `transaction_safe`

CALLABLE_TRAITS_TRANSACTION_SAFE_SPECIFIER - `transaction_safe` when
    CALLABLE_TRAITS_ENABLE_TRANSACTION_SAFE is enabled, otherwise nothing
*/

template<typename Ret, typename... Args>
struct has_calling_convention_t<
    CALLABLE_TRAITS_ST Ret(CALLABLE_TRAITS_VARARGS_CC*)(Args..., ...)
        CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE,
    CALLABLE_TRAITS_CC_TAG> {
    using type = std::true_type;
};

template<typename Return, typename... Args>
struct function<CALLABLE_TRAITS_ST Return(CALLABLE_TRAITS_VARARGS_CC *)(Args..., ...)
    CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE>
 : qualifier_traits<dummy>, default_callable_traits<> {

    static constexpr bool value = true;

    using is_function = std::true_type;

    using has_varargs = std::true_type;

    using traits = function;

    using return_type = Return;

    using arg_types = std::tuple<Args...>;

    using type =
        CALLABLE_TRAITS_ST Return(CALLABLE_TRAITS_VARARGS_CC *)(Args..., ...)
            CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;

    using function_type = Return(Args..., ...);

    using qualified_function_type = function_type;

    using remove_varargs =
        CALLABLE_TRAITS_ST Return(CALLABLE_TRAITS_CC *)(Args...)
            CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;

    using add_varargs = type;


    using is_transaction_safe = CALLABLE_TRAITS_IS_TRANSACTION_SAFE;

    using remove_transaction_safe = Return(CALLABLE_TRAITS_VARARGS_CC *)(Args..., ...);

    using add_transaction_safe = Return(CALLABLE_TRAITS_VARARGS_CC *)(Args..., ...)
        CALLABLE_TRAITS_TRANSACTION_SAFE_SPECIFIER;

    using remove_member_pointer = type;

    template<typename U>
    using apply_member_pointer =
        CALLABLE_TRAITS_ST Return(CALLABLE_TRAITS_VARARGS_CC U::*)(Args..., ...)
            CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;

    template<typename NewReturn>
    using apply_return =
        CALLABLE_TRAITS_ST NewReturn(CALLABLE_TRAITS_VARARGS_CC *)(Args..., ...)
            CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;

    template<template<class...> class Container>
    using expand_args = Container<Args...>;

    using clear_args =
        CALLABLE_TRAITS_ST Return(CALLABLE_TRAITS_VARARGS_CC *)()
            CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;

#undef CALLABLE_TRAITS_BEGIN_PACK_MANIP
#undef CALLABLE_TRAITS_ARGS_PACK
#undef CALLABLE_TRAITS_END_PACK_MANIP

#define CALLABLE_TRAITS_BEGIN_PACK_MANIP Return(CALLABLE_TRAITS_VARARGS_CC *)(
#define CALLABLE_TRAITS_ARGS_PACK Args
#define CALLABLE_TRAITS_END_PACK_MANIP , ...) CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE

#include <callable_traits/detail/unguarded/args_pack_manipulations.hpp>
#undef CALLABLE_TRAITS_BEGIN_PACK_MANIP
#undef CALLABLE_TRAITS_END_PACK_MANIP
};

