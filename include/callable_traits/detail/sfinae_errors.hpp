/*!
@copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_SFINAE_ERRORS_HPP
#define CALLABLE_TRAITS_SFINAE_ERRORS_HPP

#include <callable_traits/config.hpp>
#include <type_traits>

namespace callable_traits {

    namespace detail {

        struct sfinae_error{};

        template<typename T>
        struct success {
            static constexpr bool value = true;
            struct _ { using type = T; };
        };
    
        template<bool B, typename T>
        struct fail_if : T {

            static_assert(std::is_base_of<sfinae_error, T>::value,
                "incorrect usage of fail_if");

            static constexpr bool value = B;
        };

        template<typename T, typename... ThrowIfs>
        using sfinae_try = typename CALLABLE_TRAITS_DISJUNCTION(
            ThrowIfs...,
            success<T>
        )::_::type;
    }

#define CALLABLE_TRAITS_PP_CAT_(x, y) x ## y
#define CALLABLE_TRAITS_PP_CAT(x, y) CALLABLE_TRAITS_PP_CAT_(x, y)

#define CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(origin)     \
namespace callable_traits_ERROR {                              \
    template<typename ErrorMessage>                            \
    struct origin :                                            \
        ::callable_traits::detail::sfinae_error                \
        { struct _ {}; };                                      \
}                                                              \
/**/

#define CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(origin, name)    \
struct CALLABLE_TRAITS_PP_CAT(name, _ ){};                       \
struct name : callable_traits_ERROR::origin<                     \
    CALLABLE_TRAITS_PP_CAT(name, _ )>{};                         \
/**/

    /*** parameter manipulation errors ***/
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(parameters)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(parameters,
        index_out_of_range_for_parameter_list)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(parameters,
        cannot_determine_parameters_for_this_type)


    /*** parent class errors ***/
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(parent_class)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(parent_class,
        type_is_not_a_member_pointer)


    /*** member qualifier errors ***/
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(member_qualifiers)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(member_qualifiers,
        member_qualifiers_are_illegal_for_this_type)


    /*** varargs errors ***/
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(varargs)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(varargs,
        varargs_are_illegal_for_this_type)

    /*** transaction_safe errors ***/
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(transaction_safe_error)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(transaction_safe_error,
        transaction_safe_is_not_enabled_on_this_platform)
}
#endif // #ifndef CALLABLE_TRAITS_SFINAE_ERRORS_HPP
