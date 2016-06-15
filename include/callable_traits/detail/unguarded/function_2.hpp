/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

macros used:

CALLABLE_TRAITS_INCLUDE_QUALIFIERS - the function-level qualifiers for the
    current inclusion (combinations of `const` `volatile` `&` `&&`, or nothing)

CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE - the transaction_safe specifier for
    the current include (`transaction_safe` or nothing)

CALLABLE_TRAITS_IS_TRANSACTION_SAFE - `std::true_type` or `std::false_type`,
    tied on whether CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE is `transaction_safe`

CALLABLE_TRAITS_TRANSACTION_SAFE_SPECIFIER - `transaction_safe` when
    CALLABLE_TRAITS_ENABLE_TRANSACTION_SAFE is enabled, otherwise nothing
*/



template<typename Return, typename... Args>
struct function<Return(Args...)
    CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE>
 : qualifier_traits<dummy CALLABLE_TRAITS_INCLUDE_QUALIFIERS>, default_callable_traits {
     
    static constexpr bool value = true;
    
    using is_function = std::true_type;

    using traits = function;

    using return_type = Return;

    using arg_types = std::tuple<Args...>;

    using type = Return(Args...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;

    // todo document that transaction_safe is not preserved
    using function_type = Return(Args...);

    using qualified_function_type = Return(Args...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;

    using remove_varargs = type;

    using add_varargs = Return (Args..., ...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;
    
    using is_transaction_safe = CALLABLE_TRAITS_IS_TRANSACTION_SAFE;

    using remove_transaction_safe = Return(Args...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS;

    using add_transaction_safe = Return(Args...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_TRANSACTION_SAFE_SPECIFIER;

    using qualifiers = qualifier_traits<dummy CALLABLE_TRAITS_INCLUDE_QUALIFIERS>;
    
    template<flags Flags>
    using set_qualifiers = set_function_qualifiers<Flags, Return, Args...>;
    
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
    using apply_member_pointer = add_member_pointer<type, U>;
    
    using remove_member_pointer = type;
    
    template<typename NewReturn>
    using apply_return = NewReturn(Args...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;
    
    template<template<class...> class Container>
    using expand_args = Container<Args...>;

    using clear_args = Return()
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;
    
#undef CALLABLE_TRAITS_BEGIN_PACK_MANIP
#undef CALLABLE_TRAITS_ARGS_PACK
#undef CALLABLE_TRAITS_END_PACK_MANIP

#define CALLABLE_TRAITS_BEGIN_PACK_MANIP Return(
#define CALLABLE_TRAITS_ARGS_PACK Args

#define CALLABLE_TRAITS_END_PACK_MANIP \
    ) CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE

#include <callable_traits/detail/unguarded/args_pack_manipulations.hpp>
#undef CALLABLE_TRAITS_BEGIN_PACK_MANIP
#undef CALLABLE_TRAITS_END_PACK_MANIP
};


template<typename Return, typename... Args>
struct function<Return (Args..., ...)
    CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE>
 : qualifier_traits<dummy CALLABLE_TRAITS_INCLUDE_QUALIFIERS>, default_callable_traits {
     
    static constexpr bool value = true;
    
    using has_varargs = std::true_type;
    using is_function = std::true_type;
    using traits = function;
    using return_type = Return;
    using arg_types = std::tuple<Args...>;

    using type = Return (Args..., ...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;

    // todo document that transaction_safe is not preserved
    using function_type = Return(Args..., ...);

    using qualified_function_type = Return(Args..., ...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;

    using remove_varargs = Return (Args...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;

    using add_varargs = type;

    using is_transaction_safe = CALLABLE_TRAITS_IS_TRANSACTION_SAFE;

    using remove_transaction_safe = Return(Args..., ...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS;

    using add_transaction_safe = Return(Args..., ...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_TRANSACTION_SAFE_SPECIFIER;

    using qualifiers = qualifier_traits<dummy CALLABLE_TRAITS_INCLUDE_QUALIFIERS>;
    
    template<flags Flags>
    using set_qualifiers = set_varargs_function_qualifiers<Flags, Return, Args...>;
    
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
    using apply_member_pointer =
        Return( CALLABLE_TRAITS_DEFAULT_VARARGS_CC U::*)(Args..., ...)
            CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;
        
    using remove_member_pointer = type;
    
    template<typename NewReturn>
    using apply_return = NewReturn(Args..., ...)
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;
    
    template<template<class...> class Container>
    using expand_args = Container<Args...>;

    using clear_args = Return()
        CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE;
    
#define CALLABLE_TRAITS_BEGIN_PACK_MANIP Return(
#define CALLABLE_TRAITS_ARGS_PACK Args

#define CALLABLE_TRAITS_END_PACK_MANIP \
    , ...) CALLABLE_TRAITS_INCLUDE_QUALIFIERS CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE


#include <callable_traits/detail/unguarded/args_pack_manipulations.hpp>
#undef CALLABLE_TRAITS_BEGIN_PACK_MANIP
#undef CALLABLE_TRAITS_ARGS_PACK
#undef CALLABLE_TRAITS_END_PACK_MANIP

};

/**/
