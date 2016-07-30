/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP
#define CALLABLE_TRAITS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP

#include <callable_traits/detail/qualifier_flags.hpp>

#define CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(QUAL)              \
template<typename Return, typename... Args>                        \
struct set_function_qualifiers_t <                                 \
    flag_map<int QUAL>::value, Return, Args...> {                  \
                                                                   \
    using type = Return(Args...) QUAL;                             \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_varargs_function_qualifiers_t <                         \
    flag_map<int QUAL>::value, Return, Args...> {                  \
                                                                   \
    using type = Return(Args..., ...) QUAL;                        \
}                                                                  \
/**/

CALLABLE_TRAITS_DETAIL_NAMESPACE_BEGIN

        template<qualifier_flags Applied, typename Return, typename... Args>
        struct set_function_qualifiers_t {
            using type = Return(Args...);
        };

        template<qualifier_flags Applied, typename Return, typename... Args>
        struct set_varargs_function_qualifiers_t {
            using type = Return(Args..., ...);
        };

#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(volatile);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const volatile);

#ifndef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS

        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(&);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(&&);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const &);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const &&);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(volatile &);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(volatile &&);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const volatile &);
        CALLABLE_TRAITS_SET_FUNCTION_QUALIFIERS(const volatile &&);

#endif //#ifndef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
#endif //#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

        template<qualifier_flags Flags, typename... Ts>
        using set_function_qualifiers =
            typename set_function_qualifiers_t<Flags, Ts...>::type;

        template<qualifier_flags Flags, typename... Ts>
        using set_varargs_function_qualifiers =
            typename set_varargs_function_qualifiers_t<Flags, Ts...>::type;

CALLABLE_TRAITS_DETAIL_NAMESPACE_END

#endif //CALLABLE_TRAITS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP
