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
#include <callable_traits/detail/function_object.hpp>
#include <callable_traits/detail/generalized_class.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/config.hpp>

#include <tuple>

#define CALLABLE_TRAITS_SPECIALIZE_FUNCTION(QUAL)                                    \
                                                                                     \
template<typename Return, typename... Args>                                          \
struct function<Return(Args...) QUAL>                                                \
 : qualifier_traits<dummy QUAL> {                                                    \
                                                                                     \
    static constexpr bool value = true;                                              \
    using has_varargs = std::false_type;                                             \
    static constexpr bool is_ambiguous = false;                                      \
    using is_member_pointer = std::false_type;                                       \
    using is_function_object = std::false_type;                                      \
    using is_member_function_pointer = std::false_type;                              \
    using is_function_reference = std::false_type;                                   \
    using is_function_pointer = std::false_type;                                     \
    using is_function = std::true_type;                                              \
    using is_function_general = std::true_type;                                      \
                                                                                     \
    using traits = function;                                                         \
    using return_type = Return;                                                      \
    using arg_types = std::tuple<Args...>;                                           \
    using type = Return(Args...) QUAL;                                               \
    using function_type = Return(Args...);                                           \
    using abominable_type = Return(Args...) QUAL;                                    \
    using remove_abominable = type;                                                  \
    using remove_varargs = type;                                                     \
    using add_varargs = Return (Args..., ...) QUAL;                                  \
    using class_type = invalid_type;                                                 \
    using invoke_type = invalid_type;                                                \
    using is_abominable_function = std::integral_constant<bool,                      \
        !std::is_same<abominable_type, function_type>::value>;                       \
                                                                                     \
    using qualifiers = qualifier_traits<dummy QUAL>;                                 \
    template<flags Flags>                                                            \
    using set_qualifiers = set_function_qualifiers<Flags, Return, Args...>;          \
                                                                                     \
    using remove_reference = set_qualifiers<qualifiers::cv_flags>;                   \
    using add_lvalue_reference = set_qualifiers<qualifiers::q_flags | lref_>;        \
    using add_rvalue_reference = set_qualifiers<qualifiers::q_flags | rref_>;        \
    using add_const = set_qualifiers<qualifiers::q_flags | const_>;                  \
    using add_volatile = set_qualifiers<qualifiers::q_flags | volatile_>;            \
    using add_cv = set_qualifiers<qualifiers::q_flags | cv_>;                        \
    using remove_const = set_qualifiers<                                             \
        qualifiers::ref_flags | remove_const<qualifiers::cv_flags>::value            \
    >;                                                                               \
    using remove_volatile = set_qualifiers<                                          \
        qualifiers::ref_flags | remove_volatile<qualifiers::cv_flags>::value         \
    >;                                                                               \
    using remove_cv = set_qualifiers<qualifiers::ref_flags>;                         \
                                                                                     \
    template<typename U>                                                             \
    using apply_member_pointer = add_member_pointer<type, U>;                        \
                                                                                     \
    template<typename NewReturn>                                                     \
    using apply_return = NewReturn(Args...) QUAL;                                    \
                                                                                     \
};                                                                                   \
                                                                                     \
template<typename Return, typename... Args>                                          \
struct function<Return (Args..., ...) QUAL>                                          \
 : qualifier_traits<dummy QUAL> {                                                    \
                                                                                     \
    static constexpr bool value = true;                                              \
    using has_varargs = std::true_type;                                              \
    static constexpr bool is_ambiguous = false;                                      \
    using is_member_pointer = std::false_type;                                       \
    using is_function_object = std::false_type;                                      \
    using is_member_function_pointer = std::false_type;                              \
    using is_function_reference = std::false_type;                                   \
    using is_function_pointer = std::false_type;                                     \
    using is_function = std::true_type;                                              \
    using is_function_general = std::true_type;                                      \
    using traits = function;                                                         \
    using return_type = Return;                                                      \
    using arg_types = std::tuple<Args...>;                                           \
    using type = Return (Args..., ...) QUAL;                                         \
    using function_type = Return(Args..., ...);                                      \
    using abominable_type = Return(Args..., ...) QUAL;                               \
    using remove_varargs = Return (Args...) QUAL;                                    \
    using add_varargs = type;                                                        \
    using class_type = invalid_type;                                                 \
    using invoke_type = invalid_type;                                                \
                                                                                     \
    using qualifiers = qualifier_traits<dummy QUAL>;                                 \
                                                                                     \
    template<flags Flags>                                                            \
    using set_qualifiers = set_varargs_function_qualifiers<Flags, Return, Args...>;  \
                                                                                     \
    using remove_reference = set_qualifiers<qualifiers::cv_flags>;                   \
    using add_lvalue_reference = set_qualifiers<qualifiers::q_flags | lref_>;        \
    using add_rvalue_reference = set_qualifiers<qualifiers::q_flags | rref_>;        \
    using add_const = set_qualifiers<qualifiers::q_flags | const_>;                  \
    using add_volatile = set_qualifiers<qualifiers::q_flags | volatile_>;            \
    using add_cv = set_qualifiers<qualifiers::q_flags | cv_>;                        \
    using remove_const = set_qualifiers<                                             \
        qualifiers::ref_flags | remove_const<qualifiers::cv_flags>::value            \
    >;                                                                               \
    using remove_volatile = set_qualifiers<                                          \
        qualifiers::ref_flags | remove_volatile<qualifiers::cv_flags>::value         \
    >;                                                                               \
    using remove_cv = set_qualifiers<qualifiers::ref_flags>;                         \
                                                                                     \
    template<typename U>                                                             \
    using apply_member_pointer =                                                     \
        Return( CALLABLE_TRAITS_VARARGS_CC U::*)(Args..., ...) QUAL;                 \
                                                                                     \
    template<typename NewReturn>                                                     \
    using apply_return = NewReturn(Args..., ...) QUAL;                               \
}                                                                                    \
/**/
namespace callable_traits {

    namespace detail {

        template<typename T>
        struct function : function_object<generalized_class<unknown>> {
            static constexpr const bool value = false;
            using traits = function;
        };

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

            using remove_reference = T*;
            using add_lvalue_reference = T*&;
            using add_rvalue_reference = T*&&;

            using add_const =  T * const;
            using add_volatile = T * volatile;
            using add_cv = T * const volatile;
            using remove_const = typename base::remove_cv *;
            using remove_volatile = typename base::remove_cv *;
            using remove_cv = typename base::remove_cv *;

            template<typename NewReturn>
            using apply_return = typename base::template apply_return<NewReturn>&;
        };

        template<typename T>
        struct function<T&> : function<T> {
            using traits = function;
            using base = function<T>;
            using type = T&;
            using remove_varargs = typename base::remove_varargs&;
            using add_varargs = typename base::add_varargs&;

            using remove_reference = T;
            using add_lvalue_reference = T&;
            using add_rvalue_reference = T&&;

            using add_const =  typename base::add_const;
            using add_volatile = typename base::add_volatile;
            using add_cv = typename base::add_cv;
            using remove_const = typename base::remove_const;
            using remove_volatile = typename base::remove_volatile;
            using remove_cv = typename base::remove_cv;

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
