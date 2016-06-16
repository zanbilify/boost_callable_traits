/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_LIKE_FUNCTION_HPP
#define CALLABLE_TRAITS_IS_LIKE_FUNCTION_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T>
    struct is_like_function
        : detail::bool_type<detail::function<T>::value> {

        using type = detail::bool_type<detail::function<T>::value>;
    };

    #ifdef CALLABLE_TRAITS_DISABLE_VARIABLE_TEMPLATES

    template<typename T>
    struct is_like_function_v {
        static_assert(sizeof(T) < 1,
            "Variable templates not supported on this compiler.");
    };

    #else

    template<typename T>
    constexpr bool is_like_function_v = detail::function<T>::value;

    #endif
}

#endif // CALLABLE_TRAITS_IS_LIKE_FUNCTION_HPP

