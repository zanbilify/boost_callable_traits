/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP
#define CALLABLE_TRAITS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP

#include <callable_traits/detail/qualifiers.hpp>
#include <callable_traits/config.hpp>

#define CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(QUAL)              \
template<typename Return, typename... Args>                        \
struct set_function_qualifiers_t <                                 \
    flag_map<int QUAL>::value, Return, Args...                     \
> {                                                                \
    using type = Return(Args...) QUAL;                             \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_varargs_function_qualifiers_t <                         \
    flag_map<int QUAL>::value, Return, Args...                     \
> {                                                                \
    using type = Return(Args..., ...) QUAL;                        \
};                                                                 \
                                                                   \
template<typename T, typename Return, typename... Args>            \
struct set_varargs_member_function_qualifiers_t <                  \
    flag_map<int QUAL>::value, T, Return, Args...                  \
> {                                                                \
    using type =                                                   \
        Return(CALLABLE_TRAITS_DEFAULT_VARARGS_CC                  \
            T::*)(Args..., ...) QUAL;                              \
}                                                                  \
/**/

namespace callable_traits {

    namespace detail {

        template<flags Applied, typename Return, typename... Args>
        struct set_function_qualifiers_t {
            using type = Return(Args...);
        };

        template<flags Applied, typename Return, typename... Args>
        struct set_varargs_function_qualifiers_t {
            using type = Return(Args..., ...);
        };

        template<flags Applied, typename T, typename Return, typename... Args>
        struct set_varargs_member_function_qualifiers_t {
            using type = Return(CALLABLE_TRAITS_DEFAULT_VARARGS_CC T::*)(Args..., ...);
        };

        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(&);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(&&);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(volatile);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const &);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const &&);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(volatile &);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(volatile &&);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const volatile);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const volatile &);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const volatile &&);

        template<flags Flags, typename... Ts>
        using set_function_qualifiers =
            typename set_function_qualifiers_t<Flags, Ts...>::type;

        template<flags Flags, typename... Ts>
        using set_varargs_function_qualifiers =
            typename set_varargs_function_qualifiers_t<Flags, Ts...>::type;

        template<flags Flags, typename... Ts>
        using set_varargs_member_function_qualifiers =
            typename set_varargs_member_function_qualifiers_t<Flags, Ts...>::type;
    }
}

#endif //CALLABLE_TRAITS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP
