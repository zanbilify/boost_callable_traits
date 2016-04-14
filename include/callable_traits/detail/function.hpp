/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_FUNCTION_HPP
#define CALLABLE_TRAITS_DETAIL_FUNCTION_HPP

#include <callable_traits/detail/fwd/function_fwd.hpp>
#include <callable_traits/detail/calling_conventions.hpp>
#include <callable_traits/detail/set_function_qualifiers.hpp>
#include <callable_traits/detail/qualifiers.hpp>
#include <callable_traits/detail/default_callable_traits.hpp>
#include <callable_traits/config.hpp>


#include <tuple>

#define CALLABLE_TRAITS_SPECIALIZE_FUNCTION(QUAL)                                    \
                                                                                     \
template<typename T, typename Return, typename... Args>                              \
struct function<T, Return(Args...) QUAL>                                             \
 : qualifier_traits<dummy QUAL>, default_callable_traits {                           \
                                                                                     \
    static constexpr bool value = true;                                              \
                                                                                     \
    using is_function = std::true_type;                                              \
    using is_functionish = std::true_type;                                           \
    using traits = function;                                                         \
    using return_type = Return;                                                      \
    using arg_types = std::tuple<Args...>;                                           \
    using invoke_arg_types = arg_types;                                              \
    using type = Return(Args...) QUAL;                                               \
    using function_type = Return(Args...);                                           \
    using qualified_function_type = Return(Args...) QUAL;                            \
    using remove_varargs = type;                                                     \
    using add_varargs = Return (Args..., ...) QUAL;                                  \
    using has_member_qualifiers_function = std::integral_constant<bool,              \
        !std::is_same<qualified_function_type, function_type>::value>;               \
                                                                                     \
    using qualifiers = qualifier_traits<dummy QUAL>;                                 \
                                                                                     \
    template<flags Flags>                                                            \
    using set_qualifiers = set_function_qualifiers<Flags, Return, Args...>;          \
                                                                                     \
    using remove_member_reference = set_qualifiers<qualifiers::cv_flags>;            \
                                                                                     \
    using add_member_lvalue_reference = set_qualifiers<                              \
        collapse_flags<qualifiers::q_flags, lref_>::value>;                          \
                                                                                     \
    using add_member_rvalue_reference = set_qualifiers<                              \
        collapse_flags<qualifiers::q_flags, rref_>::value>;                          \
                                                                                     \
    using add_member_const = set_qualifiers<qualifiers::q_flags | const_>;           \
    using add_member_volatile = set_qualifiers<qualifiers::q_flags | volatile_>;     \
    using add_member_cv = set_qualifiers<qualifiers::q_flags | cv_>;                 \
                                                                                     \
    using remove_member_const = set_qualifiers<                                      \
        qualifiers::ref_flags | remove_const_flag<qualifiers::cv_flags>::value>;     \
                                                                                     \
    using remove_member_volatile = set_qualifiers<                                   \
        qualifiers::ref_flags | remove_volatile_flag<qualifiers::cv_flags>::value>;  \
                                                                                     \
    using remove_member_cv = set_qualifiers<qualifiers::ref_flags>;                  \
                                                                                     \
    template<typename U>                                                             \
    using apply_member_pointer = add_member_pointer<type, U>;                        \
                                                                                     \
    using remove_member_pointer = type;                                              \
                                                                                     \
    template<typename NewReturn>                                                     \
    using apply_return = NewReturn(Args...) QUAL;                                    \
                                                                                     \
    template<template<class...> class Container>                                     \
    using expand_args = Container<Args...>;                                          \
                                                                                     \
    using clear_args = Return() QUAL;  			                         	     	 \
                                                                                     \
    template<typename... NewArgs>                                                    \
    using push_args_front = Return(NewArgs..., Args...) QUAL;                        \
                                                                                     \
	template<typename... NewArgs>                                                    \
	using push_args_back = Return(Args..., NewArgs...) QUAL;                         \
};                                                                                   \
                                                                                     \
template<typename T, typename Return, typename... Args>                              \
struct function<T, Return (Args..., ...) QUAL>                                       \
 : qualifier_traits<dummy QUAL>, default_callable_traits {                           \
                                                                                     \
    static constexpr bool value = true;                                              \
    using has_varargs = std::true_type;                                              \
    using is_function = std::true_type;                                              \
    using is_functionish = std::true_type;                                           \
    using traits = function;                                                         \
    using return_type = Return;                                                      \
    using arg_types = std::tuple<Args...>;                                           \
    using invoke_arg_types = arg_types;                                              \
    using type = Return (Args..., ...) QUAL;                                         \
    using function_type = Return(Args..., ...);                                      \
    using qualified_function_type = Return(Args..., ...) QUAL;                       \
    using remove_varargs = Return (Args...) QUAL;                                    \
    using add_varargs = type;                                                        \
                                                                                     \
    using qualifiers = qualifier_traits<dummy QUAL>;                                 \
                                                                                     \
    template<flags Flags>                                                            \
    using set_qualifiers = set_varargs_function_qualifiers<Flags, Return, Args...>;  \
                                                                                     \
    using remove_member_reference = set_qualifiers<qualifiers::cv_flags>;            \
                                                                                     \
    using add_member_lvalue_reference = set_qualifiers<                              \
        collapse_flags<qualifiers::q_flags, lref_>::value>;                          \
                                                                                     \
    using add_member_rvalue_reference = set_qualifiers<                              \
        collapse_flags<qualifiers::q_flags, rref_>::value>;                          \
                                                                                     \
    using add_member_const = set_qualifiers<qualifiers::q_flags | const_>;           \
    using add_member_volatile = set_qualifiers<qualifiers::q_flags | volatile_>;     \
    using add_member_cv = set_qualifiers<qualifiers::q_flags | cv_>;                 \
                                                                                     \
    using remove_member_const = set_qualifiers<                                      \
        qualifiers::ref_flags | remove_const_flag<qualifiers::cv_flags>::value>;     \
                                                                                     \
    using remove_member_volatile = set_qualifiers<                                   \
        qualifiers::ref_flags | remove_volatile_flag<qualifiers::cv_flags>::value>;  \
                                                                                     \
    using remove_member_cv = set_qualifiers<qualifiers::ref_flags>;                  \
                                                                                     \
    template<typename U>                                                             \
    using apply_member_pointer =                                                     \
        Return( CALLABLE_TRAITS_DEFAULT_VARARGS_CC U::*)(Args..., ...) QUAL;         \
                                                                                     \
    using remove_member_pointer = type;                                              \
                                                                                     \
    template<typename NewReturn>                                                     \
    using apply_return = NewReturn(Args..., ...) QUAL;                               \
                                                                                     \
    template<template<class...> class Container>                                     \
    using expand_args = Container<Args...>;                                          \
                                                                                     \
    using clear_args = Return() QUAL;  			                         	     	 \
                                                                                     \
    template<typename... NewArgs>                                                    \
    using push_args_front = Return(NewArgs..., Args..., ...) QUAL;                   \
                                                                                     \
	template<typename... NewArgs>                                                    \
	using push_args_back = Return(Args..., NewArgs..., ...) QUAL;                    \
}                                                                                    \
/**/

namespace callable_traits {

    namespace detail {

        template<typename U, typename T>
        struct function : default_callable_traits {};

        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(&);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(&&);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(const);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(volatile);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(const volatile);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(const &);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(volatile &);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(const volatile &);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(const &&);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(volatile &&);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(const volatile &&);

        #undef CALLABLE_TRAITS_SPECIALIZE_FUNCTION

        // function pointers

        #define CALLABLE_TRAITS_CC_TAG dummy
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC
        #define CALLABLE_TRAITS_ST
        #include <callable_traits/detail/function_cc.hpp>
        #include <callable_traits/detail/varargs_function_cc.hpp>
        #undef CALLABLE_TRAITS_ST
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC

        /* ?
        #ifdef CALLABLE_TRAITS_ENABLE_CDECL
        #define CALLABLE_TRAITS_CC_TAG cdecl_tag
        #define CALLABLE_TRAITS_VARARGS_CC __cdecl
        #define CALLABLE_TRAITS_CC __cdecl
        #define CALLABLE_TRAITS_ST
        #include <callable_traits/detail/function_cc.hpp>
        #undef CALLABLE_TRAITS_ST
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC
        #endif*/

        #ifdef CALLABLE_TRAITS_ENABLE_STDCALL
        #define CALLABLE_TRAITS_CC_TAG stdcall_tag
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC __stdcall
        #define CALLABLE_TRAITS_ST
        #include <callable_traits/detail/function_cc.hpp>
        #undef CALLABLE_TRAITS_ST
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC
        #endif

        #ifdef CALLABLE_TRAITS_ENABLE_FASTCALL
        #define CALLABLE_TRAITS_CC_TAG fastcall_tag
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC __fastcall
        #define CALLABLE_TRAITS_ST
        #include <callable_traits/detail/function_cc.hpp>
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_ST
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC
        #endif

        #ifdef CALLABLE_TRAITS_ENABLE_PASCAL
        #define CALLABLE_TRAITS_CC_TAG pascal_tag
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC
        #define CALLABLE_TRAITS_ST pascal
        #include <callable_traits/detail/function_cc.hpp>
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_ST
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC
        #endif

        template<typename U, typename T>
        struct function<U, T&> : function<T, T> {
            using traits = function;
            using base = function<T, T>;
            using type = T&;
            using remove_varargs = typename base::remove_varargs&;
            using add_varargs = typename base::add_varargs&;
            using remove_member_pointer = type;

            using remove_member_reference = invalid_type;
            using add_member_lvalue_reference = invalid_type;
            using add_member_rvalue_reference = invalid_type;
            using add_member_const = invalid_type;
            using add_member_volatile = invalid_type;
            using add_member_cv = invalid_type;
            using remove_member_const = invalid_type;
            using remove_member_volatile = invalid_type;
            using remove_member_cv = invalid_type;

            template<typename NewReturn>
            using apply_return = typename base::template apply_return<NewReturn>&;
			
            using clear_args = typename base::clear_args&;
			
			template<typename... NewArgs>
			using push_args_front = typename base::template push_args_front<NewArgs...>&;

			template<typename... NewArgs>
			using push_args_back = typename base::template push_args_back<NewArgs...>&;
        };

        template<typename U, typename T, T Value>
        struct function<U, std::integral_constant<T, Value>> {
            using traits = function<T, T>;
            static constexpr const bool value = traits::value;
        };
    }
}

#endif
