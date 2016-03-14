/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_FUNCTION_HPP
#define CALLABLE_TRAITS_FUNCTION_HPP

#include <callable_traits/set_function_qualifiers.hpp>
#include <callable_traits/constraints.hpp>
#include <callable_traits/has_normal_call_operator.hpp>
#include <callable_traits/tags.hpp>
#include <callable_traits/flags.hpp>
#include <tuple>

#define CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CATEGORY, QUAL)                          \
                                                                                     \
template<typename Return, typename... Args>                                          \
struct function<Return CATEGORY (Args...) QUAL>                                      \
 : public qualifier_traits<dummy QUAL> {                                             \
                                                                                     \
public:                                                                              \
                                                                                     \
    static constexpr bool value = true;                                              \
    using has_varargs = std::false_type;                                             \
    static constexpr bool is_ambiguous = false;                                      \
    using is_function_object = std::false_type;                                      \
                                                                                     \
    using dispatch_type = function;                                                  \
    using callable_traits_tag = function_tag;                                        \
    using return_type = Return;                                                      \
    using arg_types = std::tuple<Args...>;                                           \
    using type = Return CATEGORY (Args...) QUAL;                                     \
    using function_type = Return(Args...);                                           \
    using abominable_type = Return(Args...) QUAL;                                    \
    using remove_varargs = type;                                                     \
    using add_varargs = Return CATEGORY (Args..., ...) QUAL;                         \
    using class_type = invalid_type;                                                 \
    using invoke_type = invalid_type;                                                \
                                                                                     \
private:                                                                             \
                                                                                     \
    using qualifiers = qualifier_traits<dummy QUAL>;                                 \
    template<flags Flags>                                                            \
    using set_qualifiers = set_function_qualifiers<Flags, Return, Args...>;          \
                                                                                     \
public:                                                                              \
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
    using apply_class = Return(U::*)(Args...) QUAL;                                  \
                                                                                     \
    template<typename NewReturn>                                                     \
    using apply_return = NewReturn CATEGORY (Args...) QUAL;                          \
};                                                                                   \
                                                                                     \
template<typename Return, typename... Args>                                          \
struct function<Return CATEGORY (Args..., ...) QUAL>                                 \
 : public qualifier_traits<dummy QUAL> {                                             \
                                                                                     \
public:                                                                              \
                                                                                     \
    static constexpr bool value = true;                                              \
    using has_varargs = std::true_type;                                              \
    static constexpr bool is_ambiguous = false;                                      \
    using is_function_object = std::false_type;                                      \
                                                                                     \
    using dispatch_type = function;                                                  \
    using callable_traits_tag = function_tag;                                        \
    using return_type = Return;                                                      \
    using arg_types = std::tuple<Args...>;                                           \
    using type = Return CATEGORY (Args..., ...) QUAL;                                \
    using function_type = Return(Args..., ...);                                      \
    using abominable_type = Return(Args..., ...) QUAL;                               \
    using remove_varargs = Return CATEGORY (Args...) QUAL;                           \
    using add_varargs = type;                                                        \
    using class_type = invalid_type;                                                 \
    using invoke_type = invalid_type;                                                \
                                                                                     \
private:                                                                             \
                                                                                     \
    using qualifiers = qualifier_traits<dummy QUAL>;                                 \
                                                                                     \
    template<flags Flags>                                                            \
    using set_qualifiers = set_varargs_function_qualifiers<Flags, Return, Args...>;  \
                                                                                     \
public:                                                                              \
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
    using apply_class = Return(U::*)(Args..., ...) QUAL;                             \
                                                                                     \
    template<typename NewReturn>                                                     \
    using apply_return = NewReturn(Args..., ...) QUAL;                               \
}                                                                                    \
/**/

#define CALLABLE_TRAITS_PTR (*)
#define CALLABLE_TRAITS_REF (&)

namespace callable_traits {

    namespace ctdetail {

        template<typename T>
        struct function {
            static constexpr const bool is_valid = false;
            static constexpr const bool value = is_valid;
            static constexpr const bool is_ambiguous = true;
            using dispatch_type = function;
        };

        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, CALLABLE_TRAITS_EMPTY);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_PTR, CALLABLE_TRAITS_EMPTY);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_REF, CALLABLE_TRAITS_EMPTY);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, &);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, &&);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, const);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, volatile);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, const volatile);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, const &);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, volatile &);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, const volatile &);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, const &&);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, volatile &&);
        CALLABLE_TRAITS_SPECIALIZE_FUNCTION(CALLABLE_TRAITS_EMPTY, const volatile &&);

        template<typename T, T Value>
        struct function<std::integral_constant<T, Value> > {
            using dispatch_type = function<T>;
        };
    }
}

#undef CLBL_SPECIALIZE_FUNCTION

#endif