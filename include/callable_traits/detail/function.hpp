/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_FUNCTION_HPP
#define CALLABLE_TRAITS_DETAIL_FUNCTION_HPP

#include <callable_traits/detail/set_function_qualifiers.hpp>
#include <callable_traits/detail/qualifiers.hpp>
#include <callable_traits/detail/default_callable_traits.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/config.hpp>


#include <tuple>

#define CALLABLE_TRAITS_SPECIALIZE_FUNCTION(QUAL)                                    \
                                                                                     \
template<typename Return, typename... Args>                                          \
struct function<Return(Args...) QUAL>                                                \
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
    using is_qualified_function = std::integral_constant<bool,                       \
        !std::is_same<qualified_function_type, function_type>::value>;               \
                                                                                     \
    using qualifiers = qualifier_traits<dummy QUAL>;                                 \
                                                                                     \
    template<flags Flags>                                                            \
    using set_qualifiers = set_function_qualifiers<Flags, Return, Args...>;          \
                                                                                     \
    using remove_function_reference = set_qualifiers<qualifiers::cv_flags>;          \
                                                                                     \
    using add_function_lvalue = set_qualifiers<                                      \
        collapse_flags<qualifiers::q_flags, lref_>::value>;                          \
                                                                                     \
    using add_function_rvalue = set_qualifiers<                                      \
        collapse_flags<qualifiers::q_flags, rref_>::value>;                          \
                                                                                     \
    using add_function_const = set_qualifiers<qualifiers::q_flags | const_>;         \
    using add_function_volatile = set_qualifiers<qualifiers::q_flags | volatile_>;   \
    using add_function_cv = set_qualifiers<qualifiers::q_flags | cv_>;               \
                                                                                     \
    using remove_function_const = set_qualifiers<                                    \
        qualifiers::ref_flags | remove_const_flag<qualifiers::cv_flags>::value>;     \
                                                                                     \
    using remove_function_volatile = set_qualifiers<                                 \
        qualifiers::ref_flags | remove_volatile_flag<qualifiers::cv_flags>::value>;  \
                                                                                     \
    using remove_function_cv = set_qualifiers<qualifiers::ref_flags>;                \
                                                                                     \
    template<typename U>                                                             \
    using apply_member_pointer = add_member_pointer<type, U>;                        \
                                                                                     \
    using remove_member_pointer = type;                                              \
                                                                                     \
    template<typename NewReturn>                                                     \
    using apply_return = NewReturn(Args...) QUAL;                                    \
                                                                                     \
};                                                                                   \
                                                                                     \
template<typename Return, typename... Args>                                          \
struct function<Return (Args..., ...) QUAL>                                          \
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
    using remove_function_reference = set_qualifiers<qualifiers::cv_flags>;          \
                                                                                     \
    using add_function_lvalue = set_qualifiers<                                      \
        collapse_flags<qualifiers::q_flags, lref_>::value>;                          \
                                                                                     \
    using add_function_rvalue = set_qualifiers<                                      \
        collapse_flags<qualifiers::q_flags, rref_>::value>;                          \
                                                                                     \
    using add_function_const = set_qualifiers<qualifiers::q_flags | const_>;         \
    using add_function_volatile = set_qualifiers<qualifiers::q_flags | volatile_>;   \
    using add_function_cv = set_qualifiers<qualifiers::q_flags | cv_>;               \
                                                                                     \
    using remove_function_const = set_qualifiers<                                    \
        qualifiers::ref_flags | remove_const_flag<qualifiers::cv_flags>::value>;     \
                                                                                     \
    using remove_function_volatile = set_qualifiers<                                 \
        qualifiers::ref_flags | remove_volatile_flag<qualifiers::cv_flags>::value>;  \
                                                                                     \
    using remove_function_cv = set_qualifiers<qualifiers::ref_flags>;                \
                                                                                     \
    template<typename U>                                                             \
    using apply_member_pointer =                                                     \
        Return( CALLABLE_TRAITS_VARARGS_CC U::*)(Args..., ...) QUAL;                 \
                                                                                     \
    using remove_member_pointer = type;                                              \
                                                                                     \
    template<typename NewReturn>                                                     \
    using apply_return = NewReturn(Args..., ...) QUAL;                               \
}                                                                                    \
/**/

namespace callable_traits {

    namespace detail {

        template<typename T>
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

#undef CLBL_SPECIALIZE_FUNCTION

        template<typename T>
        struct function<T*> : function<T> {
            using traits = function;
            using type = T*;
            using base = function<T>;
            using remove_varargs = typename base::remove_varargs*;
            using add_varargs = typename base::add_varargs*;
            using remove_member_pointer = type;

            using remove_function_reference = invalid_type;
            using add_function_lvalue = invalid_type;
            using add_function_rvalue = invalid_type;
            using add_function_const =  invalid_type;
            using add_function_volatile = invalid_type;
            using add_function_cv = invalid_type;
            using remove_function_const = invalid_type;
            using remove_function_volatile = invalid_type;
            using remove_function_cv = invalid_type;

            template<typename NewReturn>
            using apply_return = typename base::template apply_return<NewReturn>*;
        };

        template<typename T>
        struct function<T&> : function<T> {
            using traits = function;
            using base = function<T>;
            using type = T&;
            using remove_varargs = typename base::remove_varargs&;
            using add_varargs = typename base::add_varargs&;
            using remove_member_pointer = type;

            using remove_function_reference = invalid_type;
            using add_function_lvalue = invalid_type;
            using add_function_rvalue = invalid_type;
            using add_function_const = invalid_type;
            using add_function_volatile = invalid_type;
            using add_function_cv = invalid_type;
            using remove_function_const = invalid_type;
            using remove_function_volatile = invalid_type;
            using remove_function_cv = invalid_type;

            template<typename NewReturn>
            using apply_return = typename base::template apply_return<NewReturn>&;
        };

        template<typename T, T Value>
        struct function<std::integral_constant<T, Value>> {
            using traits = function<T>;
            static constexpr const bool value = traits::value;
        };
    }
}

#endif
