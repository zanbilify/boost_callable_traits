/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_PMF_HPP
#define CALLABLE_TRAITS_PMF_HPP

#include <callable_traits/set_function_qualifiers.hpp>
#include <callable_traits/tags.hpp>
#include <callable_traits/qualifiers.hpp>
#include <tuple>

#define CALLABLE_TRAITS_SPECIALIZE_PMF(QUAL)                                         \
                                                                                     \
template<typename Return, typename T, typename... Args>                              \
struct pmf<Return(T::*)(Args...) QUAL>                                               \
 : public qualifier_traits<dummy QUAL> {                                             \
                                                                                     \
public:                                                                              \
                                                                                     \
    static constexpr bool value = true;                                              \
    using has_varargs = std::false_type;                                             \
    static constexpr bool is_ambiguous = false;                                      \
    using is_member_pointer = std::true_type;                                        \
    using is_function_object = std::false_type;                                      \
    using is_member_function_pointer = std::true_type;                               \
    using is_function_reference = std::false_type;                                   \
    using is_function_pointer = std::false_type;                                     \
    using is_function = std::false_type;                                             \
    using is_function_general = std::false_type;                                     \
                                                                                     \
    using traits = pmf;                                                              \
    using return_type = Return;                                                      \
    using arg_types = std::tuple<Args...>;                                           \
    using type = Return(T::*)(Args...) QUAL;                                         \
    using function_type = Return(Args...);                                           \
    using abominable_type = Return(Args...) QUAL;                                    \
    using remove_varargs = type;                                                     \
    using add_varargs = Return(CALLABLE_TRAITS_VARARGS_CC T::*)(Args..., ...) QUAL;  \
    using class_type = T;                                                            \
    using invoke_type = T QUAL;                                                      \
                                                                                     \
private:                                                                             \
                                                                                     \
    using qualifiers = qualifier_traits<dummy QUAL>;                                 \
    template<flags Flags>                                                            \
    using set_qualifiers = set_function_qualifiers<Flags, Return, Args...> T::*;     \
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
    using apply_member_pointer = Return(U::*)(Args...) QUAL;                         \
                                                                                     \
    template<typename NewReturn>                                                     \
    using apply_return = NewReturn(T::*)(Args...) QUAL;                              \
};                                                                                   \
                                                                                     \
template<typename Return, typename T, typename... Args>                              \
struct pmf<Return(CALLABLE_TRAITS_VARARGS_CC T::*)(Args..., ...) QUAL>               \
 : public qualifier_traits<dummy QUAL> {                                             \
                                                                                     \
public:                                                                              \
                                                                                     \
    static constexpr bool value = true;                                              \
    using has_varargs = std::true_type;                                              \
    static constexpr bool is_ambiguous = false;                                      \
    using is_member_pointer = std::true_type;                                        \
    using is_function_object = std::false_type;                                      \
    using is_member_function_pointer = std::true_type;                               \
    using is_function_reference = std::false_type;                                   \
    using is_function_pointer = std::false_type;                                     \
    using is_function = std::false_type;                                             \
    using is_function_general = std::false_type;                                     \
                                                                                     \
    using traits = pmf;                                                              \
    using return_type = Return;                                                      \
    using arg_types = std::tuple<Args...>;                                           \
    using type = Return(CALLABLE_TRAITS_VARARGS_CC T::*)(Args..., ...) QUAL;         \
    using function_type = Return(Args..., ...);                                      \
    using abominable_type = Return(Args..., ...) QUAL;                               \
    using remove_varargs = Return(T::*)(Args...) QUAL;                               \
    using add_varargs = type;                                                        \
    using class_type = T;                                                            \
    using invoke_type = T QUAL;                                                      \
                                                                                     \
private:                                                                             \
                                                                                     \
    using qualifiers = qualifier_traits<dummy QUAL>;                                 \
                                                                                     \
    template<flags Flags>                                                            \
    using set_qualifiers =                                                           \
        set_varargs_member_function_qualifiers<Flags, T, Return, Args...>;           \
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
    using apply_member_pointer =                                                     \
        Return(CALLABLE_TRAITS_VARARGS_CC U::*)(Args..., ...) QUAL;                  \
                                                                                     \
    template<typename NewReturn>                                                     \
    using apply_return =                                                             \
        NewReturn(CALLABLE_TRAITS_VARARGS_CC T::*)(Args..., ...) QUAL;               \
}                                                                                    \
/**/

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct pmf {
            static constexpr const bool is_valid = false;
            static constexpr const bool value = is_valid;
            static constexpr const bool is_ambiguous = true;
            using traits = pmf;
        };

        CALLABLE_TRAITS_SPECIALIZE_PMF(CALLABLE_TRAITS_EMPTY);
        CALLABLE_TRAITS_SPECIALIZE_PMF(&);
        CALLABLE_TRAITS_SPECIALIZE_PMF(&&);
        CALLABLE_TRAITS_SPECIALIZE_PMF(const);
        CALLABLE_TRAITS_SPECIALIZE_PMF(volatile);
        CALLABLE_TRAITS_SPECIALIZE_PMF(const volatile);
        CALLABLE_TRAITS_SPECIALIZE_PMF(const &);
        CALLABLE_TRAITS_SPECIALIZE_PMF(volatile &);
        CALLABLE_TRAITS_SPECIALIZE_PMF(const volatile &);
        CALLABLE_TRAITS_SPECIALIZE_PMF(const &&);
        CALLABLE_TRAITS_SPECIALIZE_PMF(volatile &&);
        CALLABLE_TRAITS_SPECIALIZE_PMF(const volatile &&);
    }
}

#undef CALLABLE_TRAITS_SPECIALIZE_PMF

#endif