/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

*/

template<typename Ret, typename T, typename... Args>
struct add_calling_convention_t<
    Ret(T::*)(Args..., ...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS, CALLABLE_TRAITS_CC_TAG> {
    using type = Ret(CALLABLE_TRAITS_CC T::*)(Args..., ...);
};

template<typename Ret, typename T, typename... Args>
struct has_calling_convention_t<
    Ret(CALLABLE_TRAITS_VARARGS_CC T::*)(Args..., ...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS,
    CALLABLE_TRAITS_CC_TAG> {
    using type = std::true_type;
};

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int CALLABLE_TRAITS_INCLUDE_QUALIFIERS>::value, CALLABLE_TRAITS_CC_TAG, T, Return, Args...> {

    using type =
        Return(CALLABLE_TRAITS_VARARGS_CC T::*)(Args..., ...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS;
};

template<typename OriginalType, typename Return, typename T, typename... Args>
struct pmf<OriginalType, Return(CALLABLE_TRAITS_VARARGS_CC T::*)(Args..., ...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS>
 : qualifier_traits<dummy CALLABLE_TRAITS_INCLUDE_QUALIFIERS>, default_callable_traits {

    static constexpr bool value = true;

    using has_varargs = std::true_type;
    using is_member_pointer = std::true_type;
    using is_member_function_pointer = std::true_type;
    using traits = pmf;
    using return_type = Return;
    using type = Return(CALLABLE_TRAITS_VARARGS_CC T::*)(Args..., ...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS;

    using invoke_type = typename std::conditional<
        std::is_rvalue_reference<T CALLABLE_TRAITS_INCLUDE_QUALIFIERS>::value,
        T CALLABLE_TRAITS_INCLUDE_QUALIFIERS,
        typename std::add_lvalue_reference<T CALLABLE_TRAITS_INCLUDE_QUALIFIERS>::type
    >::type;

    using arg_types = std::tuple<invoke_type, Args...>;
    using non_invoke_arg_types = std::tuple<Args...>;
    using function_object_type = Return(Args..., ...);
    using function_type = Return(invoke_type, Args..., ...);
    using qualified_function_type = Return(Args..., ...) CALLABLE_TRAITS_INCLUDE_ABOMINABLE_QUALIFIERS;

    using remove_varargs = typename copy_cvr<
        Return(CALLABLE_TRAITS_CC T::*)(Args...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS,
        OriginalType
    >::type;

    using add_varargs = OriginalType;
    using class_type = T;

    using qualifiers = qualifier_traits<dummy CALLABLE_TRAITS_INCLUDE_QUALIFIERS>;

    template<flags Flags>
    using set_qualifiers = typename copy_cvr<
        set_varargs_member_function_qualifiers<
            Flags, CALLABLE_TRAITS_CC_TAG, T, Return, Args...>,
            OriginalType
        >::type;

    using remove_member_reference = set_qualifiers<qualifiers::cv_flags>;

    using add_member_lvalue_reference = set_qualifiers<
        collapse_flags<qualifiers::q_flags, lref_>::value>;

    using add_member_rvalue_reference = set_qualifiers<
        collapse_flags<qualifiers::q_flags, rref_>::value>;

    using add_member_const = set_qualifiers<qualifiers::q_flags | const_>;
    using add_member_volatile = set_qualifiers<qualifiers::q_flags | volatile_>;
    using add_member_cv = set_qualifiers<qualifiers::q_flags | cv_>;

    using remove_member_const = set_qualifiers<
        qualifiers::ref_flags | remove_const_flag<qualifiers::cv_flags>::value>;

    using remove_member_volatile = set_qualifiers<
        qualifiers::ref_flags | remove_volatile_flag<qualifiers::cv_flags>::value>;

    using remove_member_cv = set_qualifiers<qualifiers::ref_flags>;

    template<typename U>
    using apply_member_pointer = typename copy_cvr<
        Return(CALLABLE_TRAITS_VARARGS_CC U::*)(Args..., ...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS,
        OriginalType
    >::type;

    template<typename NewReturn>
    using apply_return = typename copy_cvr<
        NewReturn(CALLABLE_TRAITS_VARARGS_CC T::*)(Args..., ...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS,
        OriginalType
    >::type;

    using remove_member_pointer = qualified_function_type;

    template<template<class...> class Container>
    using expand_args = Container<invoke_type, Args...>;

    using clear_args = typename copy_cvr<
        Return(CALLABLE_TRAITS_VARARGS_CC T::*)() CALLABLE_TRAITS_INCLUDE_QUALIFIERS,
        OriginalType
    >::type;
    
#undef CALLABLE_TRAITS_BEGIN_PACK_MANIP
#undef CALLABLE_TRAITS_ARGS_PACK
#undef CALLABLE_TRAITS_END_PACK_MANIP

#define CALLABLE_TRAITS_BEGIN_PACK_MANIP \
    typename copy_cvr<Return( CALLABLE_TRAITS_VARARGS_CC T::*)(

#define CALLABLE_TRAITS_ARGS_PACK Args

#define CALLABLE_TRAITS_END_PACK_MANIP \
    , ...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS, OriginalType>::type

#include <callable_traits/detail/unguarded/args_pack_manipulations.hpp>
#undef CALLABLE_TRAITS_BEGIN_PACK_MANIP
#undef CALLABLE_TRAITS_ARGS_PACK
#undef CALLABLE_TRAITS_END_PACK_MANIP

};
